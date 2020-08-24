#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <ncurses.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

class Sprite {
 public:
  Sprite(int w, int h) : width{w}, heigth{h} {};
  Sprite(int w, int h, int px, int py)
      : width{w}, heigth{h}, x_position{px}, y_position{py} {};
  Sprite(int w, int h, int px, int py, int vx, int vy)
      : width{w},
        heigth{h},
        x_position{px},
        y_position{py},
        x_velocity{vx},
        y_velocity{vy} {};

  void up() { y_position -= 2; }
  void down() { y_position += 2; }
  void left() { x_position -= 2; }
  void right() { x_position += 2; }

  int get_x_pos() { return x_position; }
  int get_y_pos() { return y_position; }
  int get_width() { return width; }
  int get_heigth() { return heigth; }

  void switch_color(int old_color, int new_color) {
    for (size_t i = 0; i < color.size(); i++) {
      if (color[i] == old_color) { color[i] = new_color; }
    }
  }

  void move();
  void draw();

 protected:
  int width{};
  int heigth{};
  int x_position{};
  int y_position{};
  int x_velocity{};
  int y_velocity{};

  std::vector<std::string> map{};
  std::vector<int> color{};
};

#endif