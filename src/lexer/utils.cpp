/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "utils.h"
#include <sstream>
#include <vector>

namespace chefc {
    namespace lexer {
        namespace utils {

            std::string joinLines(std::vector<std::string> lines, char delimiter)
            {
                std::stringstream stream;
                for (std::string line : lines) {
                    stream << line << delimiter;
                }
                return stream.str();
            }

            std::vector<std::string> split(std::string str, char delimiter)
            {
                std::stringstream stream{str};
                std::vector<std::string> s;
                std::string out;

                if (str != "") {
                    while (std::getline(stream, out, delimiter)) {
                        s.push_back(out);
                    }
                } 
                return s;
            }

            void replace(std::string& data, const std::string& match, const std::string& replaceWith)
            {
                size_t pos = data.find(match);

                while (pos != std::string::npos) {
                    data.replace(pos, match.size(), replaceWith);
                    pos = data.find(match, pos + replaceWith.size());
                }
            }
        }
    }
}