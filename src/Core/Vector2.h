#pragma once
//template<typename T>
class Vector2 {
public:
    Vector2(int x, int y) : x(x), y(y){};

    int x;
    int y;

    [[nodiscard]] int DistanceSquared(const Vector2 &v2) const;
    [[nodiscard]] float Distance(const Vector2 &v2) const;

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator*(const Vector2 &other) const;

    void operator+=(const Vector2 &other);
    void operator-=(const Vector2 &other);
    void operator*=(const Vector2 &other);
};
