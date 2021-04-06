#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>

bool dependent_has_the_dep();
bool dependent_has_direct_dep();

int main() {
    assert(!::dependent_has_the_dep() && "Leaked test_depends to final dependent");
    assert(!::dependent_has_direct_dep() && "Access to the_test_lib despite test_uses");
}
