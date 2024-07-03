/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include <string>

#include "argparse.h"

namespace chefc 
{
    namespace args 
    {
        Parser::Parser(int argc, char** argv) 
            : m_args(argc, argv)
        {}

        
    }
}

