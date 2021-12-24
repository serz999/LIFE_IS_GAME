#include "Game.h"
#include <iostream>

Game::Game(Life *life_ptr, size_t tile_size) : life_ptr_(life_ptr), tile_size_({(unsigned) tile_size,(unsigned) tile_size}) {
    if (life_ptr_ != nullptr) {
        window_size_.x = life_ptr_->GetWidth() * tile_size_.x;
        window_size_.y = life_ptr_->GetHeight() * tile_size_.y;
        for (int y = 0; y < life_ptr_->GetHeight(); y++) {
            for (int x = 0; x < life_ptr_->GetWidth(); x++) {
                auto tile = new sf::RectangleShape();
                tile->setSize({(float) tile_size_.x, (float) tile_size_.y});
                tile->setFillColor({0, 0, 0, 0});
                tile->setOutlineThickness(1);
                tile->setOutlineColor(sf::Color::White);
                tile->setPosition(x * tile_size_.x, y * tile_size_.y);
                tile_map_.push_back(*tile);
            }
        }
        window_.create(sf::VideoMode{window_size_.x, window_size_.y}, "MY_WINDOW");
    }
    else std::cout << "Invalid Ptr\n";
}
void Game::RenderLoop() {
    while (window_.isOpen()) {
        sf::Event event{};
        auto view = window_.getDefaultView();
        while (window_.pollEvent(event)) {
            HandleEvent(event, view);
        }
        window_.clear(sf::Color::Black);
        for (int i = 0; i < life_ptr_->GetCellStates().size(); i++) {
            if (life_ptr_->GetCellStates()[i]) tile_map_[i].setFillColor(sf::Color::White);
            else tile_map_[i].setFillColor(sf::Color::Black);
        }
        for (const auto &item: tile_map_) {
            window_.draw(item);
        }
        window_.display();
        if (!is_paused_) life_ptr_->Mutate();
        sf::sleep(sf::milliseconds(150));
    }
}
void Game::HandleEvent(sf::Event &event, sf::View &view) {
    sf::Vector2<int> mouse_pos = sf::Mouse::getPosition(window_);
    auto mouse_world_pos = window_.mapPixelToCoords(mouse_pos, view);
    if (event.type == sf::Event::LostFocus) is_focus_ = false;
    if (event.type == sf::Event::GainedFocus) is_focus_ = true;
    if (is_focus_) {
        ///window_.setTitle("Mouse pos: (" + std::to_string((int) mouse_world_pos.x / (int) tile_size_.x)
        ///+ ";" + std::to_string((int) mouse_world_pos.y / (int) tile_size_.y) + ") state - " + std::to_string(life_ptr_->GetStateCell((int) mouse_world_pos.x / (int) tile_size_.x, (int) mouse_world_pos.y / (int) tile_size_.y)));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (life_ptr_->GetStateCell((int) mouse_world_pos.x / (int) tile_size_.x,
                                        (int) mouse_world_pos.y / (int) tile_size_.y))
                life_ptr_->SetStateDead((int) mouse_world_pos.x / (int) tile_size_.x,
                                        (int) mouse_world_pos.y / (int) tile_size_.y);
            else
                life_ptr_->SetStateAlive((int) mouse_world_pos.x / (int) tile_size_.x,
                                         (int) mouse_world_pos.y / (int) tile_size_.y);
            return;
        }
    }
    switch (event.type) {
        case sf::Event::Closed:
            window_.close();
            break;
        case sf::Event::KeyPressed:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                if (is_paused_) is_paused_ = false;
                else is_paused_ = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                life_ptr_->ClearStates();
            }
            break;
    }
}
