#include "colors.hpp"

QColor parseColor(uint32_t color)
{
    return QColor::fromHsv(color & 0xFF0000, color & 0xFF00, color & 0xFF);
}

uint32_t serializeColor(QColor color)
{
    int h, s, v;
    color.getHsv(&h, &s, &v);
    return (h << 16) |
           (s <<  8) |
           v;
}
