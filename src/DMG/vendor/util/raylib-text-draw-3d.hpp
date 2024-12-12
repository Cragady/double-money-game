// clang-format off
/*******************************************************************************************
*
*   raylib [text] example - Draw 3d
*
*   NOTE: Draw a 2D text in 3D space, each letter is drawn in a quad (or 2 quads if backface is set)
*   where the texture coodinates of each quad map to the texture coordinates of the glyphs
*   inside the font texture.
*
*   A more efficient approach, i believe, would be to render the text in a render texture and
*   map that texture to a plane and render that, or maybe a shader but my method allows more
*   flexibility...for example to change position of each letter individually to make somethink
*   like a wavy text effect.
*
*   Special thanks to:
*        @Nighten for the DrawTextStyle() code https://github.com/NightenDushi/Raylib_DrawTextStyle
*        Chris Camacho (codifies - http://bedroomcoders.co.uk/) for the alpha discard shader
*
*   Example originally created with raylib 3.5, last time updated with raylib 4.0
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2021-2024 Vlad Adrian (@demizdor)
*
********************************************************************************************/

#ifndef DMG_VENDOR_UTIL_RAYLIB_TEXT_DRAW_3D_HPP_
#define DMG_VENDOR_UTIL_RAYLIB_TEXT_DRAW_3D_HPP_

#include <raylib.h>
#include <rlgl.h>

#include <stddef.h>     // Required for: NULL
#include <math.h>       // Required for: sinf()

// To make it work with the older RLGL module just comment the line below
#define RAYLIB_NEW_RLGL

//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
#define LETTER_BOUNDRY_SIZE     0.25f
#define TEXT_MAX_LAYERS         32
#define LETTER_BOUNDRY_COLOR    VIOLET

namespace vutil {

static bool SHOW_LETTER_BOUNDRY = false;
static bool SHOW_TEXT_BOUNDRY = false;

//--------------------------------------------------------------------------------------
// Data Types definition
//--------------------------------------------------------------------------------------

// Configuration structure for waving the text
typedef struct WaveTextConfig {
    Vector3 waveRange;
    Vector3 waveSpeed;
    Vector3 waveOffset;
} WaveTextConfig;

//--------------------------------------------------------------------------------------
// Module Functions Declaration
//--------------------------------------------------------------------------------------
// Draw a codepoint in 3D space
void DrawTextCodepoint3D(Font font, int codepoint, Vector3 position, float fontSize, bool backface, Color tint);
// Draw a 2D text in 3D space
void DrawText3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, Color tint);
// Measure a text in 3D. For some reason `MeasureTextEx()` just doesn't seem to work so i had to use this instead.
Vector3 MeasureText3D(Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);

// Draw a 2D text in 3D space and wave the parts that start with `~~` and end with `~~`.
// This is a modified version of the original code by @Nighten found here https://github.com/NightenDushi/Raylib_DrawTextStyle
void DrawTextWave3D(Font font, const char *text, Vector3 position, float fontSize, float fontSpacing, float lineSpacing, bool backface, WaveTextConfig *config, float time, Color tint);
// Measure a text in 3D ignoring the `~~` chars.
Vector3 MeasureTextWave3D(Font font, const char *text, float fontSize, float fontSpacing, float lineSpacing);
// Generates a nice color with a random hue
Color GenerateRandomColor(float s, float v);

} // namespace vutil

#endif
