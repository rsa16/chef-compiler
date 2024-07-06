/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include <string>
#include <vector>

namespace chefc {
    namespace lexer {
        namespace utils {
            //std::string stripLine(std::string str);
            std::string joinLines(std::vector<std::string> lines, char delimiter = ' ');
            std::vector<std::string> split(std::string str, char delimiter = ' ');
            void replace(std::string& data, const std::string& match, const std::string& replaceWith);
        }
    }
}