#ifndef COLORS_HPP
#define COLORS_HPP

#include <stdint.h>
#include <QColor>

/**
 * Converts a color from the internal bit field format to a QColor.
 */
QColor parseColor(uint32_t color);

/**
 * Converts a QColor to the internal bit field format.
 */
uint32_t serializeColor(QColor color);

#endif // COLORS_HPP
