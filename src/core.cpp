/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/
#include "core.h"

namespace chefc {
    namespace core {
        Compiler::Compiler(args::Parser& parser)
        {
            std::cout << "[INFO]: " << "Setting up initial flags and values." << "\n";
            setupCommandLine(parser);

            m_debuggingEnabled = parser.getFlag("enable_debugging");
            if (m_debuggingEnabled)
                std::cout << "[DEBUG]: " << "Debugging is now enabled! Verbosity increased." << "\n";
        }

        void Compiler::setupCommandLine(args::Parser& parser)
        {
            parser.addArgument("programName");
            parser.addOptions<chefc::args::Flag>({
                { "enable_debugging", chefc::args::Flag {"W1", "warning_1", "Enables debugging for the robot."} }
            });

            parser.parse();
        }
    }
}