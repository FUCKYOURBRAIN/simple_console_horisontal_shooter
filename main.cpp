#include <ncurses.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "asteroid.hpp"
#include "projectile.hpp"
#include "ship.hpp"

static bool finished = false;
static bool endgame = false;
int tic{};

int score{};

Ship ship{8, 8};
static std::vector<Projectile> projectiles{};
static std::vector<Asteroid> asteroids{};

std::vector<std::string> space_lines{};

void colision_detection() {
  int row, col;
  getmaxyx(stdscr, row, col);

  for (size_t i = 0; i < asteroids.size(); i++) {
    if (asteroids[i].get_x_pos() <= 0 || asteroids[i].erase()) {
      asteroids.erase(asteroids.begin() + i);
    }
    if (ship.get_y_pos() <= asteroids[i].get_y_pos() &&
        ship.get_y_pos() + ship.get_heigth() >=
            asteroids[i].get_y_pos() + asteroids[i].get_heigth() &&
        ship.get_x_pos() <= asteroids[i].get_x_pos() &&
        ship.get_x_pos() + ship.get_width() >=
            asteroids[i].get_x_pos() + asteroids[i].get_width()) {
    }

    for (size_t j = 0; j < projectiles.size(); j++) {
      if (projectiles[j].get_x_pos() + projectiles[j].get_width() >= col) {
        projectiles.erase(projectiles.begin() + j);
      }

      if (asteroids[i].get_y_pos() <= projectiles[j].get_y_pos() + 1 &&
          (asteroids[i].get_y_pos() + asteroids[i].get_heigth() >=
           projectiles[j].get_y_pos() + projectiles[j].get_heigth() - 1)

          && (projectiles[j].get_x_pos() + projectiles[j].get_width()) >=
                 asteroids[i].get_x_pos() &&
          projectiles[j].get_x_pos() <= asteroids[i].get_x_pos()) {
        asteroids[i].explode();
        score++;
        projectiles.erase(projectiles.begin() + j);
      }
    }

    if (ship.get_y_pos() + ship.get_heigth() >= asteroids[i].get_y_pos() &&
        asteroids[i].get_y_pos() + asteroids[i].get_heigth() >= ship.get_y_pos()

        &&

        ship.get_x_pos() + ship.get_width() >= asteroids[i].get_x_pos() &&
        asteroids[i].get_x_pos() + asteroids[i].get_width() >=
            ship.get_x_pos()) {
      endgame = true;
    }
  }
}

void draw_screen() {
  const int SCREEN_REFRESH_TIME{15};

  // COLS = 640;
  // LINES = 480;
  setlocale(LC_ALL, "");
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_RED);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(6, COLOR_BLACK, COLOR_BLUE);
  init_pair(7, COLOR_YELLOW, COLOR_BLACK);
  init_pair(8, COLOR_BLACK, COLOR_YELLOW);
  init_pair(9, COLOR_BLACK, COLOR_BLACK);
  init_pair(10, COLOR_GREEN, COLOR_BLACK);
  init_pair(11, COLOR_GREEN, COLOR_RED);
  init_pair(12, COLOR_CYAN, COLOR_BLACK);
  // init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  // init_pair(4, COLOR_BLUE, COLOR_BLACK);
  // init_pair(5, COLOR_BLUE, COLOR_BLACK);
  // init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  // init_pair(7, COLOR_CYAN, COLOR_BLACK);xxx
  raw();
  keypad(stdscr, TRUE);
  noecho();

  int row, col;
  getmaxyx(stdscr, row, col);

  while (!finished) {
    if (!endgame) {
      if (tic % 5 == 0) {
        for (size_t j = 0; j < space_lines.size(); j++) {
          space_lines[j].erase(space_lines[j].begin());
          if (std::rand() % 50 < 2) {
            space_lines[j] += '.';
          } else {
            space_lines[j] += ' ';
          }
        }
      }

      // std::cout << row << '\n';
      for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < row; j++) {
          attron(COLOR_PAIR(1));
          mvaddch(j, i, space_lines[j][i]);
          attroff(COLOR_PAIR(1));
        }
      }

      for (size_t i = 0; i < projectiles.size(); i++) {
        projectiles[i].move();
        projectiles[i].draw();
      }

      for (size_t i = 0; i < asteroids.size(); i++) {
        asteroids[i].move();
        asteroids[i].draw();
      }

      ship.move();
      ship.draw();

      if (tic % 50 < 2) {
        asteroids.push_back(Asteroid{6, 2, 140, std::rand() % 35, -1, 0});
      } else if (tic % 80 < 2) {
        asteroids.push_back(Asteroid{6, 2, 140, std::rand() % 35, -3, 0});
      }

      std::string msg = "Score: " + std::to_string(score);
      attron(COLOR_PAIR(1));
      mvaddstr(2, (col - msg.size()) / 2, msg.data());
      attroff(COLOR_PAIR(1));
    } else {
      // std::cout << "endgame\n";      
      for (size_t i = 0; i < col; i++) {
        for (size_t j = 0; j < row; j++) {
          attron(COLOR_PAIR(12));
          mvaddch(j, i, ACS_BOARD);
          attroff(COLOR_PAIR(12));
        }
      }

      std::string msg = "Game over. Your score: " + std::to_string(score);
      attron(COLOR_PAIR(1));
      mvaddstr(row / 2, (col - msg.size()) / 2, msg.data());
      attroff(COLOR_PAIR(1));

    }
    colision_detection();
    refresh();
    tic++;
    // std::cout << tic << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(SCREEN_REFRESH_TIME));
  }
  endwin();
}

int main() {
  std::thread worker(draw_screen);

  for (size_t j = 0; j < 35; j++) {
    space_lines.push_back("");
    for (size_t i = 0; i < 140; i++) {      
      if (std::rand() % 50 < 2) {
        space_lines[j] += '.';
      } else {
        space_lines[j] += ' ';
      }
    }
  }

  char key;
  while (true) {
    key = std::cin.get();

    switch (key) {
      case 'x':
        finished = true;
        worker.join();
        return 0;
        break;
      case 'w':
        ship.up();
        break;
      case 's':
        ship.down();
        break;
      case 'a':
        ship.left();
        break;
      case 'd':
        ship.right();
        break;
      case ' ':
        projectiles.push_back(ship.shoot());
        break;
      case 'q':
        asteroids.push_back(Asteroid{6, 4, 140, std::rand() % 35, -2, 0});
        break;
      default:
        break;
    }
  }
}
