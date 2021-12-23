#pragma once

#include <vector>
#include <exception>
#include <stdexcept>

class LifeException : public std::runtime_error {
public:
 using std::runtime_error::runtime_error;

};

class Life {
public:
    Life(int width, int height);
    const std::vector<bool> &GetCellStates() const;
    void SetStateAlive(int x, int y);
    void SetStateDead(int x, int y);
    void SetStateCell(int x, int y) const;
    void SetNearCellLiveCount(int x, int y) const;

    void Mutate();
    int GetWidth() const;
    int GetHeight() const;

private:
    int width_;
    int height_;
    std::vector<bool> cell_states_;
};