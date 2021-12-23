#pragma once

#include <vector>
#include <exception>
#include <stdexcept>
#include <ostream>

class LifeException : public std::runtime_error {
public:
 using std::runtime_error::runtime_error;

};

class Life {
public:
    Life(int width, int height);
    const std::vector<bool> &GetCellStates() const;


    explicit operator std::string() const;
    friend std::ostream &operator<<(std::ostream &os, const Life &life);


    void SetStateAlive(int x, int y);
    void SetStateDead(int x, int y);


    bool GetStateCell(int x, int y) const;
    int GetNearCellLiveCount(int x, int y) const;


    void Mutate();
    int GetWidth() const;
    int GetHeight() const;

private:
    bool IsValid_(int x, int y) const;
    std::vector<bool> GetNearCells_(int x, int y) const;
    int width_;
    int height_;
    std::vector<bool> cell_states_;
};