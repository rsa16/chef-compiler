/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include <map>

namespace chefc {
    namespace args {
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

        struct Option {
            std::string name;
            std::string altName = "";
            std::string desc = "";
        };


        struct Flag : Option {
            bool flag = false;
        };
        struct SingleValue : Option {
            std::string value = "";
        };
        struct MultiValue : Option {
            std::vector<std::string> values = {};
        };

        typedef std::variant<Flag, SingleValue, MultiValue> OptionVaraiant;
        typedef std::unordered_map<std::string, OptionVaraiant> OptionMap;
        typedef std::unordered_map<std::string, std::string> ArgumentMap;

        class Parser {
        public:
            Parser(int argc, char** argv);
            
            int parse();

            void addArgument(std::string name);
            void print_help();
            
            template <typename T> 
            void addOptions(std::map<std::string, T> opts) {
                for (const auto& [name, opt] : opts)
                {
                    m_options[name] = opt;
                }
            };

            template <typename T1>
            T1 getOptionStructure(std::string name) {
                OptionVaraiant opt = m_options[name];

                // Why doesn't C++ have reflection?
                if (std::holds_alternative<T1>(opt)) {
                    T1 optClass = std::get<T1>(opt);
                    return optClass;
                } else {
                    std::cout << "shut the fuck up" << "\n";
                    return T1 { "NULL" };
                }
            }

            bool getFlag(std::string name);
            std::string getSingleValue(std::string name);
            std::vector<std::string> getMultiValue(std::string name);

            std::string getArg(std::string name);

            template <typename T> 
            void addOption(std::string name, T opt) {
                m_options[name] = opt;
            };

        private:
            ArgumentList m_parsedArgs;
            ArgumentMap m_args;
            OptionMap m_options;
        }; 
    }
}

