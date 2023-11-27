/* 
 * =====================================================================================
 *  Author: Diego R.R.
 *  Course: CS2337.501
 *  Description: 
 *      - This header file contains global constants and functions used throughout the 
 *        program.
 *      - To enable debugging tools, simply set the appropriate flag inside the 
 *        `debug_flags` namespace to `true`.
 *
 *  Changelog:
 *  -------------------------------------------------------------------------------------
 *      Date        |               Changes
 *  -------------------------------------------------------------------------------------
 *  10/29/2023     | Changed to implement animal guessing homework.
 *  10/30/2023     | Added debug flags.
 *  10/31/2023     | trim_whitespace fixed to handle empty strings.
 *  =====================================================================================
 */

#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace global {
    // -----------------------------------------------
    // =----------------- CONSTANTS -----------------=
    namespace msgs {
        // user input
        const string OUTPUT_FILE_PATH = "Enter the path to the output file: ";
        const string ENTER_FILE_NAME = "Enter the file name: ";
        const string ENTER_FILE_NAME_AGAIN = "Enter the file name again: ";
    }  // namespace msgs

    namespace debug_flags {
        const bool stop_flow = false;

        // user input
        const bool TRIM_WHITESPACE = false;
        const bool USER_INPUT = false;

        // parser
        const bool EMPTY_FILE = true;
        const bool IGNORING_COMMENT = false;
        const bool TOKEN_LINE = false;

        // grid
        const bool MIDDLE_POINT = false;
        const bool COLLISIONS = false;
    }  // namespace debug_flags
    // =----------------- END OF CONSTANTS -----------------=
    // ------------------------------------------------------

    // ------------------------------------------------------
    // =----------------- GLOBAL FUNCTIONS -----------------=
    namespace fncs {

        /*
        *   Debug routines
        */
        namespace debug {
            inline void stop_flow(const string& fnc) {
                if (debug_flags::stop_flow) {
                    string msg =
                        "stopping flow from " + fnc + ", please enter a key to continue ...";
                    cout << "DEBUG: " << msg << endl;
                    cin.get();
                    cin.ignore(100, '\n');
                }
            }

            inline void trim_whitespace(const string& input_file_name, int first_whspace_idx,
                                        int last_whspace_idx, string trimmed_input_file_name) {
                if (debug_flags::TRIM_WHITESPACE) {
                    string msg = "trimming whitespace from \"" + input_file_name + "\"" +
                                 "\n\tfirst whitespace index: " + to_string(first_whspace_idx) +
                                 "\n\tlast whitespace index: " + to_string(last_whspace_idx) +
                                 "\n\ttrimmed string: \"" + trimmed_input_file_name + "\"";
                    cout << "DEBUG: " << msg << endl;
                }
            }
        }  // namespace debug
        
       /*
            Used to trim leading and trailing whitespaces from the user input.
        */
        inline string trim_whitespace(const string& str) {
            if (str.empty()) {
                return str;
            }
            unsigned int first = str.find_first_not_of(' ');
            unsigned int last = str.find_last_not_of(' ');
            string trimmed_str = str.substr(first, (last - first + 1));
            debug::trim_whitespace(str, first, last, trimmed_str);
            return trimmed_str;
        }

        inline string to_lower(const string& str) {
            string lower_case_str;
            for (char ch : str) {
                lower_case_str += tolower(ch);
            }
            return lower_case_str;
        }

        inline bool contains(const string& str, const string& regex) {
            string str_lower = to_lower(str);
            string regex_lower = to_lower(regex);
            return str_lower.find(regex_lower) != string::npos;
        }

    }  // namespace fncs
    // =----------------- END OF GLOBAL FUNCTIONS -----------------=
    // -------------------------------------------------------------

}  // namespace global

#endif  // GLOBAL_HPP
