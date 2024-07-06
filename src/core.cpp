/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "core.h"

#include <fstream>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

namespace chefc {
    namespace core {
        Compiler::Compiler(args::Parser& parser)
        {
            std::cout << "[INFO]: " << "Setting up initial flags and values." << "\n";
            
            if (setupCommandLine(parser) == -1) exit(-1);

            m_fileName = parser.getArg("programName");
            m_debuggingEnabled = parser.getFlag("enable_debugging");
            if (m_debuggingEnabled)
                std::cout << "[DEBUG]: " << "Debugging is now enabled! Verbosity increased." << "\n";
        }

        int Compiler::setupCommandLine(args::Parser& parser)
        {
            parser.addArgument("programName");
            parser.addOptions<chefc::args::Flag>({
                { "enable_debugging", chefc::args::Flag {"W1", "warning_1", "Enables debugging for the robot."} }
            });

            int result = parser.parse();
            return result;
        }

        int Compiler::preprocessFile()
        {
            std::ifstream fileStream{m_fileName};
            if (!fileStream.is_open()) {
                std::cout << "[ERROR]: " << "Unable to open " << m_fileName << "!";
                std::cout << " " << "Exiting." << "\n";
                return -1;
            }

            std::vector<std::string> vec;
            for (std::string temp; std::getline(fileStream, temp);) {
                vec.push_back(temp);
            }

            std::string joinedLines = lexer::utils::joinLines(vec, ';');
            lexer::utils::replace(joinedLines, ";;", ";");
            preprocessedLines = lexer::utils::split(joinedLines, ';');

            auto it = std::find(preprocessedLines.begin() + 1, preprocessedLines.end(), "Ingredients.");
            if (it == preprocessedLines.end()) {
                fs::path absolutePath = fs::current_path() / fs::path{m_fileName};
                std::cout << "\033[" << "1;31m";
                std::cout << absolutePath.string() << "(1,0)" << ": ";
                std::cout << "Syntax Error: INGREDIENTS data sector is missing." << " ";
                std::cout << "Please check if it was spelled correctly and marked with a full stop." << "\n";
                std::cout << "\033[m";
            } else {
                preprocessedLines.erase(preprocessedLines.begin() + 1, it);
            }

            return 0;
        }
    }
}