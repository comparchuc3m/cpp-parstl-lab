#include <execution>
#include <fstream>
#include <iostream>
#include <map>
#include <print>
#include <string>
#include <vector>

namespace {

  std::string to_lowercase(std::string const & str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
  }

  std::vector<std::string> read_words_from_file(std::string const & filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
      words.push_back(word);
    }
    return words;
  }

  std::map<std::string, std::size_t> count_word_frequencies(
      std::vector<std::string> const & words) {
    using diccionario = std::map<std::string, std::size_t>;
    return std::transform_reduce(
        std::execution::par, words.begin(), words.end(), diccionario{},  // diccionario vacío
        // Combinación de diccionarios
        [](diccionario d1, diccionario const & d2) -> diccionario {
          for (auto const & [clave, valor] : d2) {
            d1[clave] += valor;
          }
          return d1;
        },
        // Genera un diccionario con una palabra y frecuencia 1
        [](std::string const & palabra) -> diccionario {
          return diccionario{
            {to_lowercase(palabra), 1}
          };
        });
  }

  std::vector<std::tuple<std::string, std::size_t>> map_to_vector(
      std::map<std::string, std::size_t> const & word_count) {
    std::vector<std::tuple<std::string, std::size_t>> result;
    result.reserve(word_count.size());
    for (auto const & [word, count] : word_count) {
      result.emplace_back(word, count);
    }
    std::sort(std::execution::par,result.begin(), result.end(),
              [](auto const & a, auto const & b) { return std::get<1>(a) > std::get<1>(b); });
    return result;
  }

}  // namespace

int main(int argc, char * argv[]) {
  std::vector<std::string> args(argv, argv + argc);
  if (argc < 2) {
    std::cerr << "Usage: " << args[0] << " <filename>\n";
    return 1;
  }

  std::ifstream file(args[1]);
  if (!file) {
    std::cerr << "Error opening file: " << args[1] << "\n";
    return 1;
  }

  auto words = read_words_from_file(args[1]);
  std::println("Total words read: {}", words.size());
  using namespace std::chrono;
  auto start      = high_resolution_clock::now();
  auto word_count = count_word_frequencies(words);
  auto end        = high_resolution_clock::now();
  auto elapsed    = duration_cast<milliseconds>(end - start);
  std::println("Word frequency counting took {} milliseconds.", elapsed.count());

  start = high_resolution_clock::now();
  auto sorted_word_count = map_to_vector(word_count);
  end = high_resolution_clock::now();
  elapsed = duration_cast<milliseconds>(end - start);
  std::println("Mapping to vector took {} milliseconds.", elapsed.count());

  int n = 0;
  for (auto const & [w, count] : sorted_word_count) {
    std::cout << w << ": " << count << "\n";
    if (++n >= 50) {
      break;
    }
  }

  return 0;
}
