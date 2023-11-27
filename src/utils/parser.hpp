/*
    * parser.hpp
    * Diego R.R.
    * started: 09/28/2023
    * CS2337.501
    * functions used to parse input file
    * changelog:
        - 09/29/2023 - header file created
        - 09/01/2023 - parser documentation improved
        - 10/20/2023 - formatted code
        - 10/31/2023 - changed to implement animal guessing game
        - 11/26/2023 - implemented for conways game of life
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "global.hpp"
#include "output.hpp"

using namespace std;

namespace parser {
    namespace debug {
        void is_empty_file(bool is_empty);

        void ignoring_line(string line);

        void token_line(string token_line);
    }  // namespace debug

    const char NOT_TOKENS[] = {'#', '\n'};

    inline bool is_comment_line(ifstream& input_file) {
        return input_file.peek() == '#';
    }

    inline bool is_empty_line(ifstream& input_file) {
        return input_file.peek() == '\n';
    }

    inline bool is_file_empty(ifstream& input_file) {
        return input_file.peek() == EOF;
    }

    /*
    This function defines what is a token line which is any line that the first
   character doesn't contain any NOT_TOKENS char.

    This definition is important since when the internal pointer of the ifstream
   file is at EOF it is considered a token line (see consume_file function
   documentation for more details of it's impotance).
*/
    inline bool is_token_line(ifstream& input_file) {
        char first_line_char = input_file.peek();
        bool is_token_line = true;           // assert the first char is not a NOT_TOKENS char
        for (char not_token : NOT_TOKENS) {  // check universally for all NOT_TOKENS chars
            is_token_line = is_token_line && (first_line_char != not_token);
        }
        return is_token_line;
    }

    /*
    This function is called to assert that the internal pointer of the ifstream
   file is not at the end of the file. Note that the end of the file is a token
   line (see is_token_line function).

    If it is the case that the pointer is at the end of the file and this
   functions was called, it means the program tried to read a non-empty token
   line (e.i the rows and columns dimensions line), but the file was empty. The
   program should recover at this point asking a new input file to the user.
   Since working this without having advance tools, such as the option<type>
   feature, its a nightmare in my opinion, I decided to just assume that the
   input file will always have the expected two blocks of tokens.
*/
    inline void assert_non_empty_file(ifstream& input_file) {
        if (is_file_empty(input_file)) {
            output::error_nonexpected("input file is empty");
        }
    }


    /*
    A helper function for get_next_token_line. All comment and empty lines that
   should be ignored by the parser are handled by this function.

    One result of the state of the ifstream file passed, the function always
   advances it's internal pointer to the next token line.
*/
    inline void advance_to_token(ifstream& input_file) {
        string line;
        while (!is_token_line(input_file)) {
            getline(input_file, line);
            parser::debug::ignoring_line(line);
        }
    }

    inline bool only_whitespace(const string& str) {
        if (str.empty())  // empty is considered whitespace
            return false;
        for (char ch : str) {
            if (ch != ' ') {
                return false;
            }
        }
        return true;
    }

    /*
     * This function is used for to read lines fom the blocks of tokens.
    */
    inline string get_next_token_line(ifstream& input_file) {
        advance_to_token(input_file);
        string token_line;
        getline(input_file, token_line);

        // THIS MIGHT CAUSE BUGS SINCE IT ASSUMES THAT IT CAN KEEP READING TOKEN LINES
        if (only_whitespace(token_line))
           return get_next_token_line(input_file);

        token_line = global::fncs::trim_whitespace(token_line);
        parser::debug::token_line(token_line);
        return token_line;
    }

    /*
     * This function is used to get the rows of the soup.
    */
    inline vector<string> get_token_block(ifstream& input_file, unsigned int block_size) {
        vector<string> token_block;
        while (token_block.size() < block_size) {
            string token_line = get_next_token_line(input_file);
            token_block.push_back(token_line);
        }
        return token_block;
    }

    /*
    This function is used to read the movie titles to search tokens. Notice that
   is practically the same to get_token_block() but it doesn't have a block size
   parameter which means that the file will be consumed after this function is
   called.
*/
    inline vector<string> consume_file(ifstream& input_file) {
        vector<string> token_block;
        output::inform("reading input file ...");
        while (!is_file_empty(input_file)) {
            string token_line = get_next_token_line(input_file);
            token_block.push_back(token_line);
        }
        parser::debug::is_empty_file(token_block.empty());

        return token_block;
    }

    // ----------------------------------------
    // =--------------- DEBUG  ---------------=
    namespace debug {
        inline void is_empty_file(bool is_empty) {
            if (global::debug_flags::EMPTY_FILE) {
                output::debug("is file empty: ", is_empty ? "true" : "false");
            }
        }

        inline void ignoring_line(string line) {
            if (global::debug_flags::IGNORING_COMMENT) {
                output::debug("ignoring line: ", line);
            }
        }

        inline void token_line(string token_line) {
            if (global::debug_flags::TOKEN_LINE) {
                output::debug("token line: ", token_line);
            }
        }
    }  // namespace debug
       // =------------- END OF DEBUG -------------=
       // ------------------------------------------

}  // namespace parser

#endif  // PARSER_HPP
