#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */

  /* Find all the white-space iterators (source.begin() and source.end() included) */
  std::vector<std::string::iterator> all_white_spaces = find_all(source.begin(), source.end(), [](char c) {
        return std::isspace(static_cast<unsigned char>(c));  // Since there are two overload versions of std::isspace, 
                                                            // we need to wrap it in a lambda function.
    });
  
  /* Define a lambda function: constructs the token*/
  auto binary_op = [&source](auto it1, auto it2) {
    return Token {source, it1, it2};
  };

  std::set<Token> out_Tokens;

  /* std::transform: InputIt1 first1, InputIt1 last1 (not included), InputIt2 first2, OutputIt d_first, BinaryOp binary_op */
  std::transform(all_white_spaces.begin(), all_white_spaces.end() - 1, all_white_spaces.begin() + 1, 
                  std::inserter(out_Tokens, out_Tokens.end()), binary_op);

  /* Define a lambda function to check if the token is empty. */
  auto is_empty = [](const Token& t) {
    return t.content.empty();
  };

  /* We are iterating over a set! Since the set elements are unchangeable, we need to declare the token type as const! (in is_empty) */
  std::erase_if(out_Tokens, is_empty);
  
  return out_Tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;

  /* Define a lambda function: check if the token is correctly spelled or not. */
  auto not_spelled_correctly = [& dictionary] (const Token& word) {
    return !dictionary.contains(word.content);
  };

  /* Define a lambda function: convert a Token into a Misspelling. */
  auto token_to_misspelling = [& dictionary] (const Token& word) {

    /* Define a lambda function: check if the DL distance between two words is exactly 1. */
    auto check_distance = [& word] (const std::string& dic_word) {  // Capture the outer word.
      return levenshtein(dic_word, word.content) == 1;
    };

    /* Filter the dictionary to find all words that satisfy the check_distance condition. */
    auto view = dictionary | rv::filter(check_distance);

    /* Convert the view into a set. */
    std::set<std::string> suggestions(view.begin(), view.end());
    return Misspelling {word, suggestions};
  };

  /* Define a lambda function to check if the suggestions of the misspelling is empty or not. */
  auto is_not_empty = [] (const Misspelling& mis) {
    return !mis.suggestions.empty();
  };

  /* First: find all misspelled words;
     Second: convert them from Token to Misspelling;
     Third: find all misspellings whose suggestions are not empty.
  */
  auto view = source | rv::filter(not_spelled_correctly)
                     | rv::transform(token_to_misspelling)
                     | rv::filter(is_not_empty);

  /* Convert the view into a set. */
  std::set<Misspelling> all_words_misspelled (view.begin(), view.end());

  return all_words_misspelled;
};

/* Helper methods */

#include "utils.cpp"