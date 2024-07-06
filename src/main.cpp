/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "core.h"
#include <iostream>

int main(int argc, char **argv)
{
    chefc::args::Parser parser{argc, argv};
    chefc::core::Compiler compiler{parser};

    compiler.preprocessFile();

    return 0;
}