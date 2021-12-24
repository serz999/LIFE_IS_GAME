#pragma once
#include "life.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
public:
    Game(Life *life_ptr, size_t tile_size);
    void RenderLoop();
    void HandleEvent(sf::Event &event, sf::View &view);
private:
    bool is_paused_{};
    bool is_focus_{};
    sf::RenderWindow window_;
    Life *life_ptr_;
    sf::Vector2<unsigned int> window_size_;
    sf::Vector2<unsigned int> tile_size_;
    std::vector<sf::RectangleShape> tile_map_;
};