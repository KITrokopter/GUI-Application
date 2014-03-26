#ifndef COLORS_HPP
#define COLORS_HPP

#include <stdint.h>
#include <QColor>

QColor parseColor(uint32_t color);
uint32_t serializeColor(QColor color);

#endif // COLORS_HPP
