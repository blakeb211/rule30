// Olc Console Engine_proj0.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
//
// Which github is this saved to?

#include <cassert>
#include <iostream>

#include "olcConsoleGameEngineGL.h"

using namespace std;

const int WIDTH = 540;
const int HEIGHT = 320;
// first 3 bools are the values of the 3 blocks in the prev generation
// fourth bool is the value of the middle block in next generation

//// RULE 30 ELEMENTARY CELLULAR AUTOMATA
//// middle block of next generation is empty if the 4th value is false
//bool rule1[4]{true, true, true, false};
//bool rule2[4]{true, true, false, false};
//bool rule3[4]{true, false, true, false};
//bool rule4[4]{false, false, false, false};
//// middle block of next generation has a block in it if the 4th value is true
//bool rule5[4]{true, false, false, true};
//bool rule6[4]{false, true, true, true};
//bool rule7[4]{false, true, false, true};
//bool rule8[4]{false, false, true, true};

// RULE 110 ELEMENTARY CELLULAR AUTOMATA
// middle block of next generation is empty if the 4th value is false
bool rule1[4]{true, true, true, false};
bool rule2[4]{true, true, false, true};
bool rule3[4]{true, false, true, true};
bool rule4[4]{true, false, false, false};
// middle block of next generation has a block in it if the 4th value is true
bool rule5[4]{false, true, true, true};
bool rule6[4]{false, true, false, true};
bool rule7[4]{false, false, true, true};
bool rule8[4]{false, false, false, false};

struct Line {
  bool cell[WIDTH]{};

  Line() {
    // init 
    for (int i = 0; i < WIDTH; i++)
      cell[i] = false;
  }
};

class Example : public olcConsoleGameEngine {
 public:
  Example() {
    lines = vector<Line>(HEIGHT);

    // create first generation and set middle cell to true.
    lines[0] = Line();
    lines[0].cell[WIDTH / 2] = true;

    // create next generations
    for (int i = 1; i < HEIGHT / 1.20; i++) {
      lines[i] = create_next_from_prev(lines[i - 1]);
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

  Line create_next_from_prev(Line& prev) {
    // create and initialize a new line object
    Line next = Line();

    // loop through cells
    for (int i = 1; i < WIDTH - 2; i = i + 1) {
      // apply first 4 rules
      int rules_that_matched = 0;
      for (auto& rule :
           {rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8}) {
        if (prev.cell[i - 1] == rule[0] && prev.cell[i] == rule[1] &&
            prev.cell[i + 1] == rule[2]) {
          // set the middle block of the next generation to the 4th item in the
          // rule array
          next.cell[i] = rule[3];
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
