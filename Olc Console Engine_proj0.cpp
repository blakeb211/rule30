// Olc Console Engine_proj0.cpp : This file contains the 'main' function.
// Program execution begins and ends there.
//

#include "olcConsoleGameEngine.h"
#include <iostream>
using namespace std;

const int WIDTH = 120;
const int HEIGHT = 90;
// first 3 bools are the values of the 3 blocks in the prev generation
// fourth bool is the value of the middle block in next generation

// result is 0 in middle block below
bool rule1[3]{true, true, true};
bool rule2[3]{true, true, false};
bool rule3[3]{true, false, true};
bool rule4 [3] { false, false, false };
// result is 1 in the middle block below
bool rule5[3]{false, true, true};
bool rule6[3]{false, true, false};
bool rule7[3]{false, false, true};

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
    for (int i = 1; i < HEIGHT; i++) {
      lines[i] = create_new_line(lines[i - 1]);
    }
  };

  bool OnUserCreate() {
    // draw all the lines
    for (int yi = 0; yi < HEIGHT; yi++)
      draw_line(lines[yi], yi) ;

    return true;
  }

  void draw_line(Line& l, int ycoord) {
    for (int i = 0; i < WIDTH; i++)
      if (l.cell[i] == true)
        Draw(i, ycoord);
  }

  Line create_new_line(const Line& prev) { 
    Line nextLine = Line(); 
    nextLine = prev;
    return nextLine;
  }

  bool OnUserUpdate(float fElapsedTime) { return true; }

  private:
  vector<Line> lines;
};






int main() {
  Example demo;
  demo.ConstructConsole(WIDTH, HEIGHT, 6, 6);
  demo.Start();


  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add
//   Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project
//   and select the .sln file
