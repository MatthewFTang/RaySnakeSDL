#pragma once

#include "Vector2.h"

#include <cmath>
int Vector2::DistanceSquared(const Vector2 &v2) const {
    return ((x - v2.x) * (x - v2.x)) + ((y - v2.y) * (y - v2.y));
}
float Vector2::Distance(const Vector2 &v2) const {
    return (std::sqrt((float) DistanceSquared(v2)));
}
Vector2 Vector2::operator+(const Vector2 &other) const {
    return {x + other.x, y + other.y};
}
Vector2 Vector2::operator-(const Vector2 &other) const {
    return {x - other.x, y - other.y};
}
Vector2 Vector2::operator*(const Vector2 &other) const {
    return {x * other.x, y * other.y};
}
void Vector2::operator+=(const Vector2 &other) {
    x = x + other.x;
    y = y + other.y;
}
void Vector2::operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
}
void Vector2::operator*=(const Vector2 &other) {
    x *= other.x;
    y *= other.y;
}
