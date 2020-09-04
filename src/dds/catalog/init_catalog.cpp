
#include <dds/catalog/package_info.hpp>
#include <dds/catalog/init_catalog.hpp>
#include <dds/catalog/import.hpp>

#include <neo/gzip.hpp>
#include <neo/transform_io.hpp>
#include <neo/string_io.hpp>
#include <neo/inflate.hpp>

/**
 * The following array of integers is generated and contains gzip-compressed
 * JSON  encoded initial catalog. MSVC can't handle string literals over
 * 64k large, so we have to resort to using a regular char array:
 */
static constexpr const unsigned char INIT_PACKAGES_CONTENT[] = {
31,139,8,0,246,189,81,95,2,255,237,93,13,115,226,182,214,254,43,26,58,115,187,155,93,108,36,3,73,58,109,103,104,66,179,220,55,33,92,96,247,182,183,180,140,176,5,120,227,175,107,155,100,211,189,249,239,175,36,27,108,136,157,56,89,131,29,162,206,236,52,200,182,206,121,206,57,58,210,35,201,242,215,138,131,213,43,60,35,94,229,7,240,181,130,39,30,209,13,254,39,170,193,35,169,41,213,248,15,141,56,196,210,216,61,127,252,249,30,208,159,158,234,234,142,175,219,22,45,170,180,248,83,224,196,54,77,219,2,231,250,196,197,174,78,107,164,119,206,116,63,168,120,225,219,85,67,159,176,219,3,33,114,40,139,222,228,146,41,43,103,18,107,205,90,141,21,249,46,182,188,169,237,154,76,228,215,138,105,95,19,94,15,249,162,26,11,141,44,21,153,186,182,25,86,201,107,210,173,181,203,158,79,181,172,170,182,233,216,22,177,124,166,127,141,85,110,179,103,60,87,101,58,24,114,229,142,235,176,146,97,91,198,109,213,196,190,58,215,173,25,171,170,114,112,32,31,140,125,226,249,146,122,192,196,172,126,211,27,226,69,19,98,169,115,19,187,87,81,225,170,200,219,124,118,172,114,123,69,197,166,173,94,209,10,199,7,81,17,191,111,225,235,134,164,170,203,187,22,62,249,50,182,108,203,113,109,45,42,182,176,73,180,241,140,88,196,197,190,237,70,23,28,87,183,252,241,28,123,243,177,61,141,138,15,216,189,62,158,24,196,99,133,204,90,14,246,231,75,195,84,238,238,88,209,194,101,193,80,153,251,190,227,253,32,203,212,155,243,197,68,162,138,203,107,78,172,170,142,35,49,87,223,49,83,82,63,30,75,71,210,209,78,35,231,184,118,84,59,18,145,243,210,35,7,213,36,36,161,198,46,67,7,213,106,8,53,36,36,130,231,5,7,15,179,37,246,116,155,91,18,74,16,101,235,184,232,19,0,123,183,212,86,174,109,217,11,15,116,228,75,112,242,238,29,48,120,60,221,166,70,19,125,80,230,242,162,72,98,63,171,176,10,81,245,89,61,24,171,145,154,224,57,225,244,120,36,105,182,42,31,112,239,146,47,216,116,168,245,195,159,204,211,171,191,109,219,224,127,39,120,229,61,211,92,11,45,193,254,240,2,88,170,109,249,84,39,118,231,119,26,153,234,22,1,173,65,231,114,60,24,182,186,167,173,243,203,110,27,64,86,55,141,48,141,221,164,91,30,113,125,86,98,208,123,105,9,84,120,221,169,245,180,123,173,126,107,216,30,159,92,94,244,58,231,173,97,231,178,251,88,141,245,187,56,128,208,152,220,91,178,70,124,76,195,135,74,155,234,51,105,238,56,220,116,153,124,179,172,231,169,14,90,61,247,88,104,211,24,212,189,43,123,110,204,237,233,148,171,27,37,70,30,209,176,184,136,134,34,162,69,68,231,31,209,168,184,136,70,34,162,69,68,231,29,209,74,113,163,14,69,140,58,68,68,231,31,209,245,226,34,186,46,34,90,68,244,54,34,26,22,23,209,98,28,45,34,58,247,136,110,22,151,163,155,34,71,139,136,222,70,68,195,226,34,90,228,104,17,209,57,70,52,83,113,98,219,158,47,25,4,79,185,162,53,9,102,74,217,111,186,54,136,21,129,27,236,1,199,181,175,117,141,104,111,211,130,155,203,146,185,172,40,186,3,137,155,113,253,48,162,191,241,103,155,215,19,53,77,182,56,179,107,197,81,94,138,195,157,43,14,243,81,28,237,92,113,148,143,226,202,206,21,87,242,81,188,190,115,197,235,249,40,222,216,185,226,141,60,20,87,118,158,85,148,111,206,42,81,94,55,29,8,195,117,199,195,218,182,145,112,97,17,18,94,88,13,5,63,13,16,127,212,118,103,188,202,248,240,235,16,22,5,2,230,8,2,21,5,2,229,8,66,41,10,132,146,11,136,168,141,56,83,55,108,34,91,111,33,76,84,132,40,16,248,52,40,216,177,141,197,21,29,126,203,38,158,233,234,120,70,252,184,87,106,219,30,74,220,71,0,115,67,192,32,168,140,92,4,163,10,196,150,225,178,116,119,45,96,218,26,113,45,206,175,22,150,238,131,112,35,202,99,100,43,16,38,135,50,35,88,215,161,232,167,147,173,229,248,253,153,67,249,80,147,187,144,185,56,183,91,144,197,168,32,179,244,141,171,251,1,150,24,69,26,89,32,225,191,239,28,23,207,76,12,108,75,37,35,43,229,158,144,92,157,180,134,39,31,40,169,234,254,218,57,27,95,180,58,221,148,219,67,149,193,168,34,5,176,25,105,26,85,210,170,103,155,121,60,7,171,84,0,187,25,124,77,187,49,144,223,111,159,117,6,195,118,159,254,209,187,236,211,63,222,140,24,76,207,54,200,136,26,236,36,248,179,79,28,219,245,137,251,54,173,178,187,228,226,74,2,11,140,199,210,248,134,134,251,216,196,186,21,48,193,199,248,25,123,134,165,39,14,13,197,91,3,113,9,54,66,98,118,156,109,46,141,181,2,8,151,161,15,104,236,2,202,99,117,108,232,127,99,126,83,90,99,224,178,228,80,100,172,49,4,146,159,214,200,63,14,78,244,115,60,9,107,139,143,167,142,179,205,159,108,5,5,204,9,69,214,158,34,127,20,207,233,50,210,81,192,194,80,192,92,81,192,194,80,192,28,81,160,194,80,160,220,80,160,194,34,10,229,24,81,168,176,136,66,57,70,20,42,44,162,80,142,17,165,20,22,81,74,62,17,197,251,113,223,37,225,152,246,40,99,108,177,209,155,110,144,170,175,155,4,244,78,250,109,240,6,27,38,29,130,191,229,151,40,168,137,65,128,75,102,11,3,187,128,124,113,92,226,121,108,48,207,167,231,137,155,6,120,142,45,93,189,194,154,237,203,92,171,181,81,239,209,147,195,47,94,93,76,227,106,168,88,53,82,204,139,237,165,167,130,80,153,173,128,118,101,5,165,204,86,80,118,101,133,122,153,173,80,223,186,21,152,25,166,102,160,88,51,243,208,50,228,188,76,41,236,199,217,46,248,1,44,213,162,181,74,26,185,150,211,160,211,235,236,158,24,228,230,51,6,152,180,6,90,31,23,182,114,107,51,243,224,114,91,56,96,110,56,96,193,56,96,78,56,80,193,56,80,46,56,80,193,113,133,114,138,43,84,112,92,161,92,226,234,176,224,124,117,152,83,190,58,204,56,117,186,77,28,121,249,3,21,140,3,229,132,67,41,24,135,242,173,56,24,144,185,110,89,216,242,171,26,246,151,20,32,227,54,79,192,30,1,216,210,0,31,241,44,81,77,176,71,52,64,135,53,254,156,4,172,71,134,117,25,30,130,31,131,189,70,63,131,57,193,218,3,195,157,64,33,153,43,180,54,214,169,75,73,251,139,30,218,254,243,228,119,36,63,216,55,216,213,62,196,84,136,92,174,100,78,37,187,53,140,146,152,98,118,101,152,59,62,189,255,25,63,105,137,170,5,134,196,116,12,102,166,182,53,99,211,242,140,16,95,172,86,73,210,76,192,4,201,92,218,55,206,57,58,20,133,237,242,170,226,67,253,2,180,71,121,106,15,139,208,30,230,163,125,194,120,188,98,25,246,220,196,150,85,253,236,217,214,187,26,55,213,55,66,138,45,161,37,182,154,196,101,167,175,163,10,91,224,25,209,191,71,220,16,108,145,38,40,227,139,62,155,23,174,137,203,8,84,80,204,37,5,229,33,54,86,254,199,40,9,221,168,242,231,93,124,245,38,60,97,68,98,119,132,203,110,79,81,112,225,145,77,97,50,171,106,83,76,152,162,150,98,158,229,63,180,107,255,161,157,249,15,237,185,255,238,248,30,210,137,103,107,250,194,92,37,114,152,37,23,14,248,51,64,247,0,6,22,185,121,15,8,246,110,171,52,107,80,213,129,103,79,125,218,109,144,181,105,79,98,169,238,45,127,254,253,200,210,200,234,7,240,244,153,133,253,133,75,188,247,192,193,158,119,99,187,26,96,167,32,176,49,19,235,77,77,219,37,82,90,122,10,148,151,67,12,27,91,0,146,2,37,227,166,222,193,229,105,231,227,5,219,214,59,236,156,60,178,1,247,40,113,255,109,168,25,249,194,22,115,165,121,166,141,183,172,79,94,121,68,254,198,85,251,140,187,152,55,22,209,101,25,168,6,182,102,213,96,228,10,236,233,148,23,31,28,140,44,112,0,62,240,177,10,80,231,68,189,242,88,137,60,178,190,211,167,96,204,14,174,24,135,162,223,252,232,221,122,178,73,227,86,154,255,252,54,88,172,94,26,246,67,235,83,123,60,248,125,48,190,184,104,117,199,31,0,164,207,211,64,211,185,148,148,154,168,7,53,219,124,160,174,126,171,123,122,121,145,161,54,221,162,150,75,211,170,211,29,246,59,89,117,194,139,47,215,15,104,212,250,248,219,167,205,154,150,54,108,185,116,64,230,19,149,6,61,54,66,83,242,54,18,104,231,233,234,3,150,53,205,8,3,248,199,63,232,229,139,139,223,198,227,4,53,46,46,50,3,34,247,107,29,12,218,40,177,218,246,195,245,210,231,148,213,115,247,37,57,113,73,209,54,134,53,9,189,117,9,252,122,40,37,165,86,63,67,173,195,244,90,31,118,118,162,109,234,99,152,104,157,65,36,229,177,80,188,175,115,112,87,235,211,202,159,247,170,167,215,162,234,147,13,67,111,65,15,61,143,50,84,208,128,232,215,181,58,232,133,160,26,237,205,120,204,243,195,120,28,26,35,248,101,226,207,182,59,30,131,31,65,125,125,115,10,205,39,65,133,192,196,148,12,17,48,113,237,43,18,219,216,242,29,49,214,106,63,235,126,60,89,85,30,252,160,181,54,239,213,250,253,247,107,117,120,100,253,142,77,216,12,210,58,242,123,232,179,68,195,205,253,104,104,181,7,137,161,240,239,135,27,74,255,180,223,61,77,124,144,94,161,249,44,41,115,156,18,150,54,0,203,172,160,213,235,60,63,1,211,228,219,91,181,130,181,11,189,254,229,176,125,50,76,190,120,126,121,242,127,236,74,20,46,43,191,157,182,127,109,125,60,31,142,7,151,31,251,39,237,183,224,127,255,139,174,253,50,56,93,150,167,196,229,69,235,244,83,103,208,126,90,195,124,172,103,56,107,15,131,142,33,57,13,247,46,7,157,223,170,151,148,35,3,207,95,176,110,46,205,152,11,75,247,124,109,189,157,166,1,79,1,72,117,105,211,96,184,236,253,190,137,49,248,21,40,197,254,99,94,158,226,133,225,7,10,46,253,204,47,201,9,40,249,93,227,139,246,69,235,188,115,214,77,244,27,21,222,235,156,38,94,234,182,186,151,131,243,118,187,23,185,53,174,202,57,109,219,11,58,146,149,87,67,57,18,140,213,0,27,178,128,19,8,55,85,11,58,129,225,233,201,248,83,187,63,232,92,118,105,243,253,249,39,128,106,16,66,116,158,230,254,246,197,160,77,77,152,108,155,160,78,58,216,90,124,73,77,108,237,223,122,231,157,147,206,112,252,203,127,218,253,203,244,56,90,58,255,66,247,84,98,208,212,69,236,197,3,205,200,241,231,46,29,241,164,4,88,111,248,161,223,110,157,102,26,47,56,216,197,241,64,93,110,52,92,187,24,199,251,203,239,195,246,248,178,127,218,238,131,159,126,98,191,59,103,227,118,247,180,211,234,222,55,65,151,142,82,169,62,209,45,145,1,140,196,202,206,59,195,225,121,251,177,250,214,238,138,85,25,207,181,223,17,215,165,67,151,81,229,163,117,101,217,55,22,96,134,160,132,133,120,193,152,198,159,83,146,192,72,30,27,79,74,163,202,166,99,214,146,255,197,224,211,73,104,32,214,111,248,193,76,154,61,5,140,61,81,62,240,30,176,59,0,155,215,2,62,118,103,196,247,40,201,240,125,131,84,3,177,210,186,151,210,112,196,48,60,93,255,152,171,151,155,75,249,182,210,143,253,54,15,133,135,95,214,123,136,43,56,174,126,77,217,176,28,158,55,55,207,184,227,118,178,208,13,141,166,123,239,90,149,67,10,75,159,125,38,107,8,85,137,234,121,50,111,217,202,27,157,155,51,151,145,180,45,236,74,134,27,186,61,194,172,63,83,102,229,169,62,140,148,218,216,251,14,247,134,81,67,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,222,33,163,70,123,195,168,145,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,239,144,81,43,123,195,168,21,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,222,33,163,174,239,13,163,174,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,245,14,25,117,99,111,24,117,67,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,119,200,168,155,123,195,168,155,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,189,67,70,125,184,55,140,250,80,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,5,163,22,140,90,48,106,193,168,119,200,168,143,246,134,81,31,9,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,181,96,212,130,81,11,70,45,24,245,14,24,53,3,101,44,48,215,171,33,65,41,203,119,169,207,23,56,160,213,142,125,67,220,233,194,224,28,120,138,61,31,56,174,61,163,121,194,100,196,216,8,19,51,141,79,74,210,232,3,140,128,3,223,6,6,193,174,197,159,97,84,156,253,159,22,18,115,66,52,70,47,108,112,107,47,92,128,29,199,208,85,204,100,166,50,107,170,184,204,148,143,56,245,117,128,225,62,167,126,44,60,164,13,179,87,14,36,149,21,29,208,240,202,24,30,143,184,32,84,54,154,201,104,72,72,170,189,120,115,51,12,47,198,220,112,15,204,253,130,162,27,237,129,185,209,203,49,183,178,7,230,86,94,138,185,149,61,200,221,202,203,201,221,202,30,228,110,229,229,228,110,101,15,114,183,242,114,114,183,178,7,185,91,121,73,185,187,190,7,230,174,191,28,115,55,246,192,220,141,151,98,238,250,30,140,76,234,47,98,100,194,231,157,240,76,87,199,196,90,152,92,179,154,212,200,100,254,129,79,173,162,2,138,216,32,42,43,12,119,32,44,76,47,205,80,22,181,248,236,150,200,49,137,49,155,5,130,55,109,246,48,154,238,189,26,163,56,170,73,205,162,128,52,115,7,2,139,2,2,115,6,130,138,2,130,114,6,162,20,5,68,201,25,72,189,40,32,245,156,129,52,138,2,210,200,25,72,179,40,32,205,188,128,240,126,197,171,222,232,6,215,2,213,80,77,170,41,217,142,102,25,206,9,248,183,110,105,246,141,7,58,166,99,16,147,246,116,188,7,6,231,193,2,105,28,96,168,190,166,121,114,76,202,211,96,92,83,11,218,110,213,158,86,39,182,109,200,84,235,24,12,11,155,196,158,134,93,227,81,166,102,223,229,143,0,219,33,46,166,21,115,207,152,182,70,232,112,227,228,221,187,199,220,19,10,92,115,205,209,179,91,125,80,91,60,190,142,51,245,138,249,99,56,126,118,167,152,132,1,22,132,1,230,136,1,21,132,1,229,136,65,41,8,67,158,237,161,94,16,134,122,30,24,120,142,34,118,117,178,152,78,137,27,230,169,132,133,34,126,147,202,118,160,58,190,247,87,109,185,48,192,74,167,11,139,22,176,101,199,4,224,191,240,122,57,63,154,220,250,148,40,25,51,219,165,58,153,158,236,223,58,196,3,19,236,81,202,68,179,179,63,183,61,190,145,160,229,233,118,66,142,174,37,174,253,60,41,53,71,64,227,30,76,152,201,222,68,171,108,162,101,252,108,203,104,149,39,39,188,76,104,235,143,163,13,201,103,28,237,214,125,91,223,22,90,88,78,180,121,71,242,178,29,51,114,239,18,207,11,91,50,76,241,118,240,236,95,43,77,214,35,155,22,252,77,83,208,95,144,54,185,227,36,91,156,132,82,248,219,1,152,237,149,190,230,91,127,136,175,74,60,183,209,164,134,106,137,208,97,30,142,94,162,188,7,62,240,234,42,141,101,233,34,91,224,141,105,123,190,113,251,150,122,80,189,98,175,2,48,223,113,4,96,89,227,242,61,137,247,224,134,42,6,60,219,164,1,160,105,58,171,196,147,82,178,21,202,3,104,32,255,145,124,181,67,88,74,62,254,75,130,5,11,133,5,183,5,11,21,10,107,75,65,88,47,52,8,235,91,8,194,187,40,13,174,146,103,166,121,51,166,239,114,239,109,52,183,26,76,24,107,186,102,125,239,131,255,46,116,218,99,76,117,159,118,31,183,55,115,226,18,192,182,55,74,146,148,146,35,115,8,70,138,35,238,176,108,123,173,182,0,6,229,225,171,123,96,96,81,96,242,247,140,82,148,103,148,45,120,70,41,202,51,202,86,60,131,138,2,131,114,7,83,47,42,204,234,91,8,179,122,81,97,86,207,55,204,150,157,142,247,95,131,170,161,172,6,174,74,166,206,53,156,65,96,148,196,176,111,170,6,185,38,6,235,92,193,224,95,231,12,85,171,215,73,201,98,202,183,131,8,85,126,206,200,244,185,122,231,146,176,214,245,230,14,48,236,185,137,45,171,250,217,179,131,190,95,145,14,51,5,216,63,7,151,93,206,119,46,18,231,114,98,179,203,65,141,223,164,60,211,46,166,181,163,206,170,170,227,132,33,115,124,148,73,225,222,201,25,232,83,187,47,76,208,93,152,19,202,103,207,136,197,230,164,56,147,99,46,104,7,3,175,180,41,41,42,85,94,74,94,159,143,58,122,50,62,221,180,136,73,150,213,197,161,145,153,31,78,253,103,92,133,237,97,215,99,203,245,237,47,75,94,10,206,216,18,62,118,193,144,152,236,221,16,146,52,253,31,71,230,99,91,14,4,71,184,80,226,90,236,215,39,189,6,241,232,154,58,21,76,225,203,189,246,217,240,60,106,77,40,227,178,237,22,145,195,162,144,31,22,235,243,195,226,124,126,88,172,207,15,139,243,249,81,177,62,63,42,206,231,71,197,250,252,168,72,159,163,98,145,163,226,144,43,197,34,87,10,64,206,187,246,197,100,230,46,38,233,11,77,73,102,8,158,1,193,93,196,82,111,1,53,135,109,44,248,170,254,106,30,126,57,241,188,29,226,30,42,30,135,114,59,209,45,13,194,112,160,82,203,198,175,8,54,13,246,226,42,95,10,156,232,116,44,202,142,92,240,111,8,225,195,71,8,249,176,184,119,235,207,31,24,132,113,201,242,74,129,216,64,44,208,227,105,72,55,170,139,199,105,45,27,207,218,1,40,152,31,40,88,18,79,193,60,61,5,75,226,41,152,167,167,80,73,60,133,242,244,20,42,137,167,80,190,158,66,37,1,133,242,4,165,148,4,148,146,39,168,122,73,64,213,243,3,165,148,36,81,40,121,38,138,122,73,64,213,243,5,5,75,2,10,230,9,10,149,4,20,202,19,148,82,18,80,57,102,191,70,73,218,84,35,167,54,197,15,101,193,214,140,84,175,151,171,7,48,27,19,233,179,167,214,206,255,100,192,234,50,60,148,81,237,61,219,205,164,123,209,94,158,239,61,224,249,218,15,63,112,89,169,123,196,151,154,200,43,149,34,208,161,98,79,3,77,92,93,181,116,50,49,136,187,170,51,190,226,0,97,89,177,194,220,177,54,74,10,181,145,59,210,227,146,34,61,222,2,82,88,82,164,48,63,164,12,170,71,204,235,216,254,226,108,123,162,216,122,212,121,12,245,41,193,6,155,15,227,251,132,6,196,196,22,123,137,229,83,112,14,22,155,168,218,202,62,188,64,245,56,22,219,64,225,164,15,74,200,181,236,141,206,119,53,62,15,147,138,234,199,234,207,128,189,129,218,234,117,192,141,139,29,218,205,4,168,176,118,141,45,149,104,209,41,126,193,171,165,14,176,108,95,157,3,122,35,63,245,151,222,147,128,246,58,212,232,233,175,142,82,76,207,57,20,140,61,198,76,194,14,127,11,234,143,157,91,252,149,29,223,54,226,175,192,140,232,239,17,55,220,168,242,62,42,246,28,172,38,93,11,143,54,11,174,4,152,86,215,66,75,179,107,127,4,231,195,141,34,139,7,135,215,253,57,178,238,42,177,9,75,42,229,10,207,136,196,215,119,131,195,200,158,161,240,194,35,247,164,178,151,97,147,101,134,173,117,41,243,225,136,27,206,73,111,126,202,172,137,214,168,90,194,244,91,225,209,5,247,48,186,224,43,141,46,84,186,232,66,123,24,93,232,149,70,151,82,186,232,82,246,48,186,148,87,26,93,245,210,69,87,125,15,163,171,254,74,163,171,81,186,232,106,236,97,116,53,94,105,116,53,75,23,93,205,61,140,174,230,235,139,46,69,42,217,160,62,80,232,126,108,109,211,249,92,230,235,244,189,82,54,223,43,5,248,94,121,141,190,71,229,154,136,84,82,14,70,223,174,239,209,107,156,39,84,18,207,235,40,216,247,176,0,223,191,182,89,60,190,22,225,104,134,61,227,74,194,196,179,61,166,166,255,174,153,22,7,191,178,227,46,89,40,208,58,102,252,184,203,212,35,178,174,97,202,161,148,41,86,138,91,136,235,72,109,148,224,208,216,165,53,127,114,105,65,249,154,51,35,60,163,202,159,207,116,96,138,106,145,239,152,16,153,254,219,20,177,225,175,44,159,110,92,126,171,178,119,122,126,121,54,254,245,98,56,110,255,54,108,247,187,173,243,71,190,88,9,149,228,207,208,112,133,101,255,134,224,43,147,132,223,126,201,117,227,246,12,79,116,115,41,40,254,221,209,164,179,84,114,141,46,184,211,232,130,34,186,202,21,93,104,187,209,133,118,26,93,72,68,87,153,162,171,177,221,158,177,177,211,158,177,33,122,198,114,69,87,115,187,209,213,220,105,116,53,69,116,149,45,186,224,118,163,11,238,52,186,196,184,171,84,209,117,184,221,220,117,184,211,220,117,40,114,87,105,162,235,142,47,250,152,70,120,68,9,204,248,130,236,7,130,53,226,86,249,247,99,135,151,23,231,236,152,184,169,62,3,83,221,32,192,193,174,23,158,193,73,255,175,99,67,255,155,100,61,76,55,208,69,14,85,138,109,198,135,207,120,101,214,196,46,149,28,84,102,44,60,246,47,222,168,96,105,161,194,188,161,162,210,66,69,249,67,85,74,11,85,201,27,106,189,180,80,235,121,67,109,148,22,106,35,95,168,74,105,219,170,146,119,91,85,74,219,86,149,124,219,42,42,109,191,138,114,237,87,25,214,107,123,194,207,104,107,172,14,104,109,100,122,143,132,63,179,249,254,76,202,201,171,141,111,63,164,173,177,161,178,71,232,248,213,95,189,253,146,118,38,247,242,28,253,213,113,228,107,199,237,195,228,117,188,25,59,190,77,87,215,192,105,241,215,100,168,112,221,243,221,133,202,22,242,52,160,97,31,111,231,92,238,37,202,181,215,243,82,142,95,143,62,25,144,4,21,109,29,42,204,31,42,122,208,171,177,15,8,108,124,86,96,187,80,209,54,188,138,30,244,106,113,80,183,226,85,84,74,168,40,87,168,119,225,129,255,33,81,67,89,143,241,196,158,167,95,19,218,161,120,142,62,157,222,130,91,226,83,64,252,139,135,172,116,97,217,19,138,134,221,3,212,232,139,1,73,19,6,241,14,133,105,34,115,117,54,135,243,210,81,65,31,69,100,172,253,209,221,144,236,214,13,81,12,5,21,195,204,203,186,219,44,18,151,164,253,81,206,109,98,141,189,107,201,69,172,13,103,97,41,157,7,11,251,26,241,203,114,94,57,155,30,172,9,231,101,112,94,73,155,30,20,206,123,220,121,168,148,190,67,133,125,230,250,69,57,79,41,165,243,20,49,96,201,226,188,122,41,157,87,47,236,139,231,47,202,121,141,82,58,175,241,172,87,125,95,157,243,154,165,116,94,83,18,3,150,12,206,59,44,165,243,14,69,203,203,226,188,163,82,58,79,12,87,50,184,238,184,148,174,59,22,174,123,192,117,193,90,76,176,89,136,109,148,185,251,127,173,79,218,45,179,102,1,0
};

const std::vector<dds::package_info>&
dds::init_catalog_packages() noexcept {
    using std::nullopt;
    static auto pkgs = []{
        using namespace neo;
        string_dynbuf_io str_out;
        buffer_copy(str_out,
                    buffer_transform_source{
                        buffers_consumer(as_buffer(INIT_PACKAGES_CONTENT)),
                        gzip_decompressor{inflate_decompressor{}}},
                    91827);
        return dds::parse_packages_json(str_out.read_area_view());
    }();
    return pkgs;
}
