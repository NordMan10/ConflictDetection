#include "convert.h"

int Convert::s_FieldWidth = 1440;
int Convert::s_FieldHeight = 810;

int Convert::s_RightFieldBorder = 440000;

int Convert::m_YShift = 100;

int Convert::s_MetersInPixel = (int) std::round(s_RightFieldBorder / s_FieldWidth);

int Convert::ConvertMetersToPixels(int meters) {
    return (int) std::abs(std::round(meters / s_MetersInPixel));
}

std::tuple<int, int> Convert::TransformCoordsFromSchemeToProgram(int z, int x) {
    //qDebug() << ConvertMetersToPixels(z) << ConvertMetersToPixels(x);
    return std::make_tuple(ConvertMetersToPixels(z), ConvertMetersToPixels(x) + m_YShift);
}
