#ifndef CONVERT_H
#define CONVERT_H

#include <cmath>
#include <tuple>

class Convert
{
public:
    Convert() = delete;

    static int ConvertMetersToPixels(int meters);

    // Координаты передавать именно по тем осям, которые заданы в параметрах: сначала по оси Z,
    // которая горизонтальная, затем по оси X, которая вертикальная (особенности схемы)
    static std::tuple<int, int> TransformCoordsFromSchemeToProgram(int z, int x);

public:
    static int s_MetersInPixel;

    static int s_FieldWidth;
    static int s_FieldHeight;

    static int s_RightFieldBorder;
};

#endif // CONVERT_H
