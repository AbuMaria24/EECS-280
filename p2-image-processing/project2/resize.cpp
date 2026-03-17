#include <iostream>
#include <cstdlib>
#include "processing.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    cerr << "Usage: resize.exe NEW_WIDTH NEW_HEIGHT < input.ppm > output.ppm\n";
    return 1;
  }

  int newWidth = atoi(argv[1]);
  int newHeight = atoi(argv[2]);

  Image img;
  Image_init(&img, cin);

  seam_carve(&img, newWidth, newHeight);

  Image_print(&img, cout);

  return 0;
}
