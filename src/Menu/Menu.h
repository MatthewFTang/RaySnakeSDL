//
// Created by Matt on 2/07/2024.
//
#pragma once
class Menu {
public:
    virtual ~Menu() = default;
    virtual void Render() = 0;
    virtual void Update() = 0;
};
