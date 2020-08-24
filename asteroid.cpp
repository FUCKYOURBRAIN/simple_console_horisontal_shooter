#include "asteroid.hpp"

extern int tic;

void Asteroid::draw() {
  int row, col;
  int index{};
  getmaxyx(stdscr, row, col);

  try {
    attron(COLOR_PAIR(10));
    std::string pixel{};

    for (size_t x = 0; x < width; x++) {
      for (size_t y = 0; y < heigth; y++) {
        int index = x + (y * width);

        if (!exploded) {
          if (index >= map.size() || index >= color.size()) {
            throw std::out_of_range(
                "index is " + std::to_string(index) +
                "while map.size()=" + std::to_string(map.size()) +
                " and color.size()=" + std::to_string(color.size()) + '\n');
            return;
          } else {
            pixel = map[index];
            if (pixel != " ") {
              attron(COLOR_PAIR(color[index]));
              mvprintw(y_position + y, x_position + x, pixel.data());
              attroff(COLOR_PAIR(color[index]));
            }
          }
        } else {
          if (exploded == 1) {
            if (index >= exposion1.size() || index >= color.size()) {
              throw std::out_of_range(
                  "index is " + std::to_string(index) +
                  "while exposion1.size()=" + std::to_string(exposion1.size()) +
                  " and color.size()=" + std::to_string(color.size()) + '\n');
              return;
            } else {
              pixel = exposion1[index];
              if (pixel != " ") {
                attron(COLOR_PAIR(11));
                mvprintw(y_position + y, x_position + x, pixel.data());
                attroff(COLOR_PAIR(11));
              }
            }
          }
          else {
            if (index >= exposion2.size() || index >= color.size()) {
              throw std::out_of_range(
                  "index is " + std::to_string(index) +
                  "while exposion2.size()=" + std::to_string(exposion2.size()) +
                  " and color.size()=" + std::to_string(color.size()) + '\n');
              return;
            } else {
              pixel = exposion2[index];
              if (pixel != " ") {
                attron(COLOR_PAIR(3));
                mvprintw(y_position + y, x_position + x, pixel.data());
                attroff(COLOR_PAIR(3));
              }
            }
          }

          if (tic - exploded_tic > 5 && exploded == 1) {
            exploded = 2;
          }
        }

        // refresh();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      }
    }
    attroff(COLOR_PAIR(10));
  } catch (const std::out_of_range& error) {
    std::cerr << error.what() << '\n';
  } catch (const std::runtime_error& error) {
    std::cerr << error.what() << '\n';
  } catch (...) {
    std::cout << "Exception occurred";
  }
}

void Asteroid::explode() {
  exploded = true;
  exploded_tic = tic;
}

void Asteroid::move() {
  int row, col;
  getmaxyx(stdscr, row, col);

  if (!exploded) {
    x_position += x_velocity;
  }
}

bool Asteroid::erase() {
  return (exploded && tic - exploded_tic > 10) ? true : false;
}