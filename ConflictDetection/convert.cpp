#include "convert.h"

int Convert::s_FieldWidth = 1680; //1440
int Convert::s_FieldHeight = 1000; // 810

int Convert::s_RightFieldBorder = 440000;

int Convert::m_YShift = 100;

double Convert::s_MetersInPixel = s_RightFieldBorder / s_FieldWidth;

int Convert::ConvertMetersToPixels(int meters) {
    return (int) std::abs(std::round(meters / s_MetersInPixel));
}

std::tuple<int, int> Convert::TransformCoordsFromSchemeToProgram(int z, int x) {
    return std::make_tuple(ConvertMetersToPixels(z), ConvertMetersToPixels(x) + m_YShift);
}
