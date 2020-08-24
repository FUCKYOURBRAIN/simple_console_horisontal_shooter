#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "sprite.hpp"

class Projectile : public Sprite {
 public:
  Projectile(int w, int h) : Sprite{w, h} {};
  Projectile(int w, int h, int px, int py, int vx, int vy) : Sprite{w, h, px, py, vx, vy} {};
  void move();
  void draw();
  std::string print();

 private:
  std::vector<std::string> map{
     "▁","▆"};

  std::vector<int> color{7, 8};
};

#endif