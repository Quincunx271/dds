#include <dds/repo/repodb.hpp>

#include <catch2/catch.hpp>

using namespace std::literals;

TEST_CASE("Create a simple database") {
    // Just create and run migrations on an in-memory database
    auto repo = dds::repo_database::open(":memory:"s);
}

class repo_test_case {
public:
    dds::repo_database db = dds::repo_database::open(":memory:"s);
};

TEST_CASE_METHOD(repo_test_case, "Store a simple package") {
    db.store(dds::package_info{
        dds::package_id("foo", semver::version::parse("1.2.3")),
        {},
        dds::git_remote_listing{"http://example.com", "master", std::nullopt},
    });
    CHECK_THROWS(db.store(dds::package_info{
        dds::package_id("foo", semver::version::parse("1.2.3")),
        {},
        dds::git_remote_listing{"http://example.com", "master", std::nullopt},
    }));

    auto pkgs = db.by_name("foo");
    REQUIRE(pkgs.size() == 1);
}

TEST_CASE_METHOD(repo_test_case, "Package requirements") {
    db.store(dds::package_info{
        dds::package_id{"foo", semver::version::parse("1.2.3")},
        {
            {"bar", semver::version::parse("1.2.5")},
            {"baz", semver::version::parse("5.3.2")},
        },
        dds::git_remote_listing{"http://example.com", "master", std::nullopt},
    });
    auto pkgs = db.by_name("foo");
    REQUIRE(pkgs.size() == 1);
    CHECK(pkgs[0].name == "foo");
    auto deps = db.dependencies_of(pkgs[0]);
    CHECK(deps.size() == 2);
    CHECK(deps[0].name == "bar");
    CHECK(deps[1].name == "baz");
}

TEST_CASE_METHOD(repo_test_case, "Parse JSON repo") {
    db.import_json_str(R"({
        "version": 1,
        "packages": {
            "foo": {
                "1.2.3": {
                    "depends": {
                        "bar": "4.2.1"
                    },
                    "git": {
                        "url": "http://example.com",
                        "ref": "master"
                    }
                }
            }
        }
    })");
    auto pkgs = db.by_name("foo");
    REQUIRE(pkgs.size() == 1);
    CHECK(pkgs[0].name == "foo");
    CHECK(pkgs[0].version == semver::version::parse("1.2.3"));
    auto deps = db.dependencies_of(pkgs[0]);
    REQUIRE(deps.size() == 1);
    CHECK(deps[0].name == "bar");
    CHECK(deps[0].version == semver::version::parse("4.2.1"));
}
