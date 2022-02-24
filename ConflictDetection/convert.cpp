#include "convert.h"

int Convert::s_FieldWidth = 1690; //1440
int Convert::s_FieldHeight = 1000; // 810

int Convert::s_RightFieldBorder = 440000;

int Convert::m_YShift = 30000;

double Convert::s_MetersInPixel = (double)s_RightFieldBorder / (double)s_FieldWidth;

double Convert::ConvertMetersToPixels(int meters) {
    //double temp2 = s_MetersInPixel;
    //double temp = std::abs(meters / s_MetersInPixel);
    return std::abs(meters / s_MetersInPixel);
}

std::tuple<int, int> Convert::TransformCoordsFromSchemeToProgramWithConvert(int z, int x) {
    return std::make_tuple(ConvertMetersToPixels(z), ConvertMetersToPixels(x) + ConvertMetersToPixels(m_YShift));
}

std::tuple<int, int> Convert::TransformCoordsFromSchemeToProgram(int z, int x) {
    return std::make_tuple(z, std::abs(x) + m_YShift);
}
