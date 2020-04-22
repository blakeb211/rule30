// Olc Console Engine_proj0.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
//

#include "olcConsoleGameEngineGL.h"
#include <iostream>
#include <cassert>

using namespace std;

const int WIDTH = 540;
const int HEIGHT = 320;
// first 3 bools are the values of the 3 blocks in the prev generation
// fourth bool is the value of the middle block in next generation

// result is 0 in middle block below
bool rule1[3]{true, true, true};
bool rule2[3]{true, true, false};
bool rule3[3]{true, false, true};
bool rule4[3] { false, false, false };
// result is 1 in the middle block below
bool rule5[3]{true, false, false};
bool rule6[3]{false, true, true};
bool rule7[3]{false, true, false};
bool rule8[3]{false, false, true};

struct Line {
  bool cell[WIDTH]{};
  
  Line() {
    // initialize line
    for (int i = 0; i < WIDTH; i++)
      cell[i] = false;
  }

};

class Example : public olcConsoleGameEngine {
 public:
  Example(){ 
    lines = vector<Line>(HEIGHT);
  
    // first generation
    lines[0] = Line();
    // set middle cell to true
    lines[0].cell[WIDTH/2] = true;

    // create next generations
    for (int i = 1; i < HEIGHT / 1.20; i++) {
      lines[i] = create_new_from_prev(lines[i - 1]);
    }
  };

  bool OnUserCreate() {
    // draw all the lines
    for (int yi = 0; yi < HEIGHT; yi++)
      draw_line(lines[yi], yi);
      return true;
  }

  void draw_line(Line& l, int ycoord) {
    for (int i = 0; i < WIDTH; i++)
      if (l.cell[i] == true)
        Draw(i, ycoord);
  }

  Line create_new_from_prev(Line& prev) { 
    // create and initialize a new line object
    Line next = Line(); 

    // loop through cells
    for (int i = 1; i < WIDTH - 2; i = i + 1) {
      // apply first 4 rules
      int rules_that_matched = 0;
      for (auto& rule : {rule1, rule2, rule3, rule4}) {
        if (prev.cell[i - 1] == rule[0] && prev.cell[i] == rule[1] &&
            prev.cell[i + 1] == rule[2]) {
          next.cell[i] = false;
          rules_that_matched++;
        }
      }
      // apply last 4 rules
      for (auto& rule : {rule5, rule6, rule7, rule8}) {
        if (prev.cell[i - 1] == rule[0] && prev.cell[i] == rule[1] &&
            prev.cell[i + 1] == rule[2]) {
          next.cell[i] = true;
          rules_that_matched++;
        }
      }
      assert(rules_that_matched == 1);
    }
    return next;
  }

  bool OnUserUpdate(float fElapsedTime) { return true; }

  private:
  vector<Line> lines;
};

int main() {
  Example demo;
  demo.ConstructConsole(WIDTH, HEIGHT, 2, 2);
  demo.Start();
  return 0;
}
