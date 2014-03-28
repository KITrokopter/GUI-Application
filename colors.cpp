#include "colors.hpp"

#include <QDebug>

QColor parseColor(uint32_t color)
{
    int h, s, v;
    h = ((color & 0xFF0000) >> 16) * 2;
    s = (color & 0xFF00) >> 8;
    v = color & 0xFF;
    return QColor::fromHsv(h, s, v);
}

uint32_t serializeColor(QColor color)
{
    int h, s, v;
    color.getHsv(&h, &s, &v);
    return ((h / 2) << 16) |
           (s <<  8) |
           v;
}
