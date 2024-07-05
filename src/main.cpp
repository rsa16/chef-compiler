/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include "argparse.h"

int main(int argc, char **argv)
{
    chefc::args::Parser parser{argc, argv};

    parser.addArgument("programName");
    parser.addOptions<chefc::args::Flag>({
        { "enable_debugging", chefc::args::Flag {"W1", "warning_1", "Enables debugging for the robot."} }
    });

    parser.parse();
    return 0;
}