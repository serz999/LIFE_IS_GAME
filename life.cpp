#include "life.h"
#include <string>
#include <algorithm>
#include <random>

const std::vector<bool> &Life::GetCellStates() const {
    return cell_states_;
}
void Life::ClearStates() {
    std::fill(cell_states_.begin(), cell_states_.end(), false);
}
int Life::GetHeight() const {
    return height_;
}
int Life::GetWidth() const {
    return width_;
}
Life::Life(int width, int height) : width_(width), height_(height), cell_states_(std::vector<bool>(width_ * height_)) {
    if (width_ < 3 || height_ < 3) {
        throw LifeException("Wrong size");
    }
}
void Life::SetStateAlive(int x, int y) {
    if (IsValid_(x, y)) {
        cell_states_[y * width_ + x] = true;
    }
    else throw LifeException("Wrong position (" + std::to_string(x) + " " + std::to_string(y) + ")");
}
void Life::SetStateDead(int x, int y) {
    if (IsValid_(x, y)) {
        cell_states_[y * width_ + x] = false;
    }
    else throw LifeException("Wrong position (" + std::to_string(x) + " " + std::to_string(y) + ")");
}
bool Life::IsValid_(int x, int y) const {
    return x >= 0 && y >= 0 && x < width_ && y < height_;
}
bool Life::GetStateCell(int x, int y) const {
    if (x == -1) x += width_;
    if (y == -1) y += height_;
    if (x == width_) x = 0;
    if (y == height_) y = 0;
    if (IsValid_(x, y)) return cell_states_[y * width_ + x];
    else throw LifeException("Wrong position (" + std::to_string(x) + " " + std::to_string(y) + ")");
}
int Life::GetNearCellLiveCount(int x, int y) const {
    auto near_cells = GetNearCells_(x, y);
    return std::count(near_cells.begin(), near_cells.end(), true);
}
Life::operator std::string() const {
    std::string result;
    size_t buf_size = 0;
    for (size_t y = 0; y < height_; y++) {
        std::string buffer = "|";
        size_t counter = 0;
        for (size_t x = 0; x < width_; x++) {
            std::string item;
            if (cell_states_[y * width_ + x]) item = "X";
            else item = ".";
            counter++;
            if (counter == width_) buffer += item;
            else buffer += item + " ";

        }
        buffer += "|";
        buf_size = buffer.size();
        result += buffer + "\n";
    }
    return std::string(buf_size, '.') + "\n" + result + std::string(buf_size, '.');
}
std::ostream &operator<<(std::ostream &os, const Life &life) {
    os << std::string(life);
    return os;
}
std::vector<bool> Life::GetNearCells_(int x, int y) const {
    if (IsValid_(x, y)) {
        return std::vector<bool>{GetStateCell(x - 1,y - 1), GetStateCell(x,y - 1), GetStateCell(x + 1,y - 1),
                                 GetStateCell(x - 1,y), GetStateCell(x + 1,y),
                                 GetStateCell(x - 1,y + 1), GetStateCell(x,y + 1), GetStateCell(x + 1,y + 1)};
    }
    else throw LifeException("Wrong position (" + std::to_string(x) + " " + std::to_string(y) + ")");
}
void Life::Mutate() {
    Life other(this->width_, this->height_);
    for (int x = 0; x < width_; x++) {
        for (int y = 0; y < height_; y++) {
            if (GetStateCell(x, y)) {
                if (GetNearCellLiveCount(x, y) <= 1 || GetNearCellLiveCount(x, y) > 3) other.SetStateDead(x, y);
                else other.SetStateAlive(x, y);
            }
            else {
                if (GetNearCellLiveCount(x, y) == 3) other.SetStateAlive(x, y);
            }
        }
    }
    std::swap(*this, other);
}
void Life::FillRandomStates() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10000);
    std::generate(cell_states_.begin(), cell_states_.end(), [&]() {return dist6(rng) % 2;});
}