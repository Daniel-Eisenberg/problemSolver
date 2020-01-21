//
// Created by Daniel Eisenberg on 21/01/2020.
//

#ifndef EX4_UTIL_H
#define EX4_UTIL_H

struct myPoint {
    int x;
    int y;
    int value;
    bool visited;

    myPoint(int x, int y, int value) {
        this->x = x;
        this->y = y;
        this->value =value;
        this->visited = false;
    }

    bool operator== (const myPoint& p) {
        return (this->x == p.x && this->y == p.y);
    }

    //return true if the point is above "this" point
    bool operator< (const myPoint& p) {
        return (this-> x == p.x && this-> y < p.y);
    }

    //return true if the point is on the right to  "this" point
    bool operator<< (const myPoint& p) {
        return (this->y == p.y && this->x < p.x);
    }

    //return true if the point is on the below "this" point
    bool operator> (const myPoint& p) {
        return (this->x == p.x && this-> y > p.y);
    }

    //return true if the point is on the left to "this" point
    bool operator>> (const myPoint& p) {
        return (this->y == p.y && this->x > p.x);
    }
};
#endif //EX4_UTIL_H
