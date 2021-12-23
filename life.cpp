#include "life.h"
#include "string"

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
void Life::SetStateAlive(int x, int y) {
    using namespace std;
    if (IsValid_(x,y)) {
        cell_states_[(y * width_) +x] = true;
    } else {
        throw LifeException("Wrong pos ("+ std::to_string(x) + ", " + std::to_string(y) + ")" );
    }
}
void Life::SetStateDead(int x, int y) {
    using namespace std;
    if (IsValid_(x,y)) {
        cell_states_[(y * width_) +x] = false;
    } else {
        throw LifeException("Wrong pos ("+ std::to_string(x) + ", " + std::to_string(y) + ")" );
    }
}
bool Life::IsValid_(int x, int y) const {
    return x >= 0 && y>= 0 && x< width_ && y< height_;
}

Life::operator std::string() const {
    using namespace std;
    string result;
    size_t buf_size = 0;
    for (size_t y = 0; y < height_; ++y) {
        string buffer = "|";
        size_t counter = 0;
        for (size_t x = 0; x < width_; ++x) {
            string item = cell_states_[(y * width_) + x] ? "o" : "-";
            ++counter;
            if(counter == width_) {
                buffer += item;
            } else {
                buffer += item + " ";
            }
        }
        buffer += "|";
        buf_size = buffer.size();
        result += buffer + "\n";
    }
    return std::string (buf_size, '.') + "\n" + result + std::string (buf_size, '.');
}
std::ostream &operator<<(std::ostream &os, const Life &life) {
    os << std::string(life);
    return os;
}

bool Life::GetStateCell(int x, int y) const {
    return false;
}

int Life::GetNearCellLiveCount(int x, int y) const {
    return 0;
}

bool Life::GetStateCell(int x, int y) const {
    using namespace std;
    if (x == -1) {
        x = x + width_;
    }
    if (y == -1) {
        y = y + height_;
    }
    if (x == width_) {
        x = 0;
    }
    if (y == height_) {
        y = 0;
    }
    if (IsValid_(x,y)) {
        return cell_states_[(y * width_) + x];
    } else {
        throw LifeException("Wrong pos ("+ std::to_string(x) + ", " + std::to_string(y) + ")" );
    }
}