#pragma once
#include "field.h"

class Player {
protected:
    Field& field_;
    Force force_;
    int score_;
    Point cursor_;
    

public:
    
    enum class Exception {
        pause,
        exit
    };
    enum class Type {
        human,
        computer
    } type_;
    Player(Field& field, Force force, int score = 0);
    virtual ~Player();
    virtual void Move();
    int GetScore();
    void ResetScore();
    void IncrementScore();
    Force GetForce();
    Point GetCursor();
};