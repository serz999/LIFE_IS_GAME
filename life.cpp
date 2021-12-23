#include "life.h"

const std::vector<bool> &Life::GetCellStates() const {
    return cell_states_;
}

int Life::GetWidth() const {
    return width_;
}

int Life::GetHeight() const {
    return height_;
}

Life::Life(int width, int height) : width_(width), height_(height), cell_states_(std::vector<bool>(width_ * height_)){
    if (width_ < 3 || height_ < 3) {
        throw LifeException("Wrong size");
    }
}



