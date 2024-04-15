#pragma once

#include <iostream>

struct Vector2d {
    float x, y;

    Vector2d () {
        x = 0.0f;
        y = 0.0f;
    }

    Vector2d (float _x, float _y) {
        x = _x;
        y = _y;
    };
};