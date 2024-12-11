#define BYTE_16 16
#define BYTE_32 32
#define BYTE_64 64
#define BYTE_128 128
#define BYTE_256 256
#define BYTE_512 512
#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION 330
#define GLSL_VERSION_STR_LEN 3
#else
#define GLSL_VERSION 100
#define GLSL_VERSION_STR_LEN 3
#endif
#define DMG_STR_HELPER(x) #x
#define DMG_STR(x) DMG_STR_HELPER(x)
#define DMG_SHADER_PATH "assets/shaders/glsl" DMG_STR(GLSL_VERSION) "/"
