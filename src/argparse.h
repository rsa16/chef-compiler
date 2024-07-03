/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include <string>
#include <vector>

namespace chefc 
{
    namespace args 
    {
        class Parser {
        public:
            Parser(int argc, char** argv);

            void setOptions();

        private:
            ArgumentList m_args;
        }; 

        struct ArgumentList {
            std::string programName;
            std::vector<std::string> args;

            // So I remember for myself, vectors that are initialized from
            // arrays need a pointer to the first element and the (hypothetical)
            // element after the last element. Also need to check that argc actually
            // has a program name in the first place.
            ArgumentList(int argc, char** argv) 
                : programName((argv && (argc >= 1)) ? argv[0] : "")
                , args((argv && (argc >= 1)) ? argv + 1 : nullptr, argc + argv)
            {}
        };

    }
}

