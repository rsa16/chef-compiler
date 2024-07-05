/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include "argparse.h"
#include "lexer/utils.h"

namespace chefc {
    namespace core {
        class Compiler {
        public:
            Compiler(args::Parser& parser);
            void setupCommandLine(args::Parser& parser);

        private:
            bool m_debuggingEnabled;
        };
    }
}