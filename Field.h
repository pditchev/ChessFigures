#pragma once

struct Field {
    unsigned char value{ 0 };
    bool isOccupied() const {
        return value & 128;
    }
    bool isAttacked() const {
        return value << 1;
    }
    void occupy() {
        value |= 128;
    }
    void deoccupy() {
        value &= 127;
    }
    void attack() {
        value++;
    }
    void removeAttack() {
        value--;
    }
};