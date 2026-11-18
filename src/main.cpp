#include "graphics.h"
#include "input.h"
int main() {
  Graphics graphics{};
  Input input{};

  if (!init(graphics))
    return 0;

  while (!input.update())
    ;
}
