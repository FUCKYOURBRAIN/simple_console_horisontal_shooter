#include "projectile.hpp"

extern int tic;

void Projectile::draw() {
  int row, col;
  int index{};
  getmaxyx(stdscr, row, col);

  try {
    attron(COLOR_PAIR(1));
    std::string pixel{};

    for (size_t x = 0; x <= width; x++) {
      for (size_t y = 0; y <= heigth - 1; y++) {
        int index = x + (y * heigth);

        if (index >= map.size() || index >= color.size()) {
          throw std::out_of_range("index is " + std::to_string(index) + "while map.size()=" + std::to_string(map.size()) + " and color.size()=" + std::to_string(color.size()) + '\n');
          return;
        }
        pixel = map[index];
        if (pixel != " ") {
          attron(COLOR_PAIR(color[index]));
          mvprintw(y_position + y, x_position + x, pixel.data());
          attroff(COLOR_PAIR(color[index]));
        }

        // std::string msg =
        //     "tic: " + std::to_string(tic) +
        //     " x_pos: " + std::to_string(x_position) + "/" +
        //     std::to_string(col) + " x_vel: " + std::to_string(x_velocity) +
        //     " y_pos: " + std::to_string(y_position) + "/" +
        //     std::to_string(row) + " y_vel: " + std::to_string(y_velocity);

        // attron(COLOR_PAIR(1));
        // mvaddstr(row / 2, (col - msg.size()) / 2, msg.data());
        // attroff(COLOR_PAIR(1));

        // refresh();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
    }
    attroff(COLOR_PAIR(1));
  } catch (const std::out_of_range& error) {
    std::cerr << error.what() << '\n';
  } catch (const std::runtime_error& error) {
    std::cerr << error.what() << '\n';
  } catch (...) {
    std::cout << "Exception occurred";
  }
}

void Projectile::move() {
  // std::cout << "Projectile::move\n";
  // int row, col;
  // getmaxyx(stdscr, row, col);

  // std::cout << "start: " << x_position << '\n';
  x_position += 2;
  // std::cout << "stop: " << x_position << '\n';

  // if (y_position + y_velocity >= 0 &&
  //     y_position + y_velocity + heigth <= row) {
  //   y_position += y_velocity;
  // }
}

std::string Projectile::print() {
  std::cout << "Projectile::print()\n";
}

std::ostream& operator<<(std::ostream& os, const Projectile& p) {
  // os << p.print();
  // return os;
}
