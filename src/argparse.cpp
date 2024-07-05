/*
  Copyright (c) 2024, Rehan Ali
  All rights reserved.

  This source code is licensed under the BSD-style license found in the
  LICENSE file in the root directory of this source tree.
*/

#include <iostream>
#include <string>
#include <sstream>

#include "argparse.h"

namespace chefc 
{   
    namespace args 
    {
        Parser::Parser(int argc, char** argv) 
            : m_parsedArgs(argc, argv)
            , m_args()
            , m_options()
        {}

        bool Parser::getFlag(std::string name)
        {
            return getOptionStructure<Flag>(name).flag;
        }


        std::string Parser::getSingleValue(std::string name)
        {
            return getOptionStructure<SingleValue>(name).value;
        }
        
        std::vector<std::string> Parser::getMultiValue(std::string name)
        {
            return getOptionStructure<MultiValue>(name).values;
        }

        void Parser::addArgument(std::string name)
        {
            m_args.insert({name, ""});
        }

        std::string Parser::getArg(std::string name)
        {
            return m_args[name];
        }

        void Parser::print_help()
        {
            printf("Usage:\n");

            printf("  %s [options] ", m_parsedArgs.programName);
            for (const auto& [key, value] : m_args) { printf("<%s> ", key.c_str()); };
            printf("\n\n");

            printf("This program was created to compile the esoteric programming Chef.\n\n");
            printf("Options:\n");
            printf( "  %-24s %-30s \n", "--help", "Displays this help message.");

            for (const auto& kv : m_options) {
                const Option& opt = std::visit(
                    [](const auto& opt) -> const Option& { return opt; },
                    kv.second);

                std::stringstream ss;
                ss << "-" << opt.name;
                if (opt.altName != "") ss << ", " << "-" << opt.altName;
                std::string cmd = ss.str();

                printf( "  %-24s %-30s \n", cmd.c_str(), opt.desc.c_str());
            }
        }

        // Utility function
        int Parser::parse()
        {
            std::vector<std::pair<int, std::string>> optionStrings;
            std::vector<std::pair<int, std::string>> argStrings;

            std::vector<std::string> argNames{m_args.size()};
            std::vector<std::string> optionStoreNames{m_options.size()};

            std::vector<std::pair<std::string, std::string>> optionNames{m_options.size()};
            std::vector<OptionVaraiant> options{m_options.size()};

            // Get CLI parameter names and sort options into vectors along
            // with names
            for (const auto& kv : m_options) {
                const Option& opt = std::visit(
                    [](const auto& opt) -> const Option& { return opt; },
                    kv.second);

                optionNames.push_back({ opt.name, opt.altName });
                optionStoreNames.push_back(kv.first);
                options.push_back(kv.second);
            }

            for (const auto& kv : m_args) {
                argNames.push_back(kv.first);
            }

            auto it = std::find(m_parsedArgs.args.begin(), m_parsedArgs.args.end(), "--help");
            if (it != m_parsedArgs.args.end())
            {
                print_help();
                return 0;
            }

            // sort arguemnts and options into separate vectors
            // check if options are valid and extra arguments are not supplied
            for (int currentIndex = 0; currentIndex < m_parsedArgs.args.size(); currentIndex++)
            {
                std::string arg = m_parsedArgs.args[currentIndex];

                if (arg.front() == '-') {
                    auto it = std::find_if(optionNames.begin(), optionNames.end(), 
                        [&arg](std::pair<std::string, std::string> pair) {
                            return pair.first == arg.substr(1) || pair.second == arg.substr(1);
                        });
                    auto index = it - optionNames.begin();

                    if (it == optionNames.end()) {
                        std::cout << "[WARN]: " << arg << " is not a valid option.\n";
                    } else {
                        optionStrings.push_back({currentIndex, arg.substr(1)});
                    };

                    if (!std::holds_alternative<Flag>(options[index])) {
                        currentIndex++;
                    }
                } else {
                    argStrings.push_back({ currentIndex, arg });
                }
            }

            int argCount = argStrings.size();
            if (argCount < m_args.size())
            {
                std::cout << "[ERROR]: " << "Not enough arguments supplied. Exiting." << "\n";
                return -1;
            } else if (argCount > m_args.size())
            {
                std::cout << "[ERROR]: " << "Too many arguments supplied. Exiting." << "\n";
                return -1;
            }

            for (const auto& [index, value] : optionStrings)
            {
                std::cout << "Option " << index << ": ";
                std::cout << value << "\n";

                for (const auto& kv : m_options) {
                    const Option& opt = std::visit(
                        [](const auto& opt) -> const Option& { return opt; },
                        kv.second);

                    if (opt.name == value || opt.altName == value)
                    {
                        if (std::holds_alternative<Flag>(kv.second)) {
                            Flag flag = std::get<Flag>(kv.second);
                            flag.flag = true;
                            m_options[kv.first] = flag;

                        } else if (std::holds_alternative<SingleValue>(kv.second)) {
                            SingleValue singleValue = std::get<SingleValue>(kv.second);
                            singleValue.value = m_parsedArgs.args[index + 1];
                            m_options[kv.first] = singleValue;
                        }

                        break;
                    };
                };
            };

            for (int argIndex = 0; const auto& [index, value] : argStrings)
            {
                std::cout << "Argument " << index << ": ";
                std::cout << value << "\n";

                m_args[argNames[argIndex]] = value;
                argIndex++;
            }

            return 0;
        }
    }
}

