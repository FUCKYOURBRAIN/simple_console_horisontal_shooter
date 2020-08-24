#include "sprite.hpp"

class Asteroid : public Sprite {
 public:
  Asteroid(int w, int h) : Sprite{w, h} {};
  Asteroid(int w, int h, int px, int py, int vx, int vy) : Sprite{w, h, px, py, vx, vy} {};

  void draw();
  void move();
  void explode();
  bool erase();

 private:
  int exploded = 0;
  int exploded_tic = -1;
  std::vector<std::string> map{
      "▗", "▞", "█", "█", "▚", "▖",
      "▝", "▚", "█", "█", "▞", "▘"};
  
  std::vector<std::string> exposion1{
      "▃", "░", "▃", "▒", "▃", " ",
      " ", "▀", "▄", "▒", "░", "░"};

  std::vector<std::string> exposion2{
      "░", " ", "▒", " ", "░", " ",
      " ", "▒", "░", "░", " ", " "};

  std::vector<int> color{10, 10, 10, 10, 10, 10,
                         10, 10, 10, 10, 10, 10,
                         10, 10, 10, 10, 10, 10,
                         10, 10, 10, 10, 10, 10};
};