#include <iostream>

#include "global_helper.h"
#include "ZL_B.h"

int main(int argc, char** argv)
{
  ZL_B* _zl_b = new ZL_B(argc, argv);

  bool loop = true;
  char cmd_input[256];
  std::cout << "main start!!" << std::endl;

  while(loop)
  {
    if(!check_std_in(10000)) continue;

    std::string              str   = get_user_input();
    std::vector<std::string> input = find_command_target(str, ' ');

    if(input.size() < 1) continue;

    if(input[0] == "finish") loop = false;
    else if(input[0] == "clear") system("clear");
    else if(input[0] == "zlb") _zl_b->control(input[1]);
  }

  safe_delete(_zl_b);

  return 0;
}