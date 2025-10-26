#include <algorithm>
#include <chrono>
#include <execution>
#include <print>
#include <random>
#include <vector>

namespace {

  std::vector<double> generate_random_vector(std::size_t size) {
    std::vector<double> vec(size);
    std::mt19937_64 rng{42};
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    std::generate(vec.begin(), vec.end(), [&]() { return dist(rng); });
    return vec;
  }

  void inplace_square_seq(std::vector<double> & vec) {
    std::for_each(std::execution::seq, vec.begin(), vec.end(),
                  [](double & val) { val = val * val; });
  }

  void inplace_square_par(std::vector<double> & vec) {
    std::for_each(std::execution::par, vec.begin(), vec.end(),
                  [](double & val) { val = val * val; });

  }

}  // namespace

int main() {
  using namespace std::chrono;
  constexpr std::size_t vector_size = 100'000'000;
  auto const vec = generate_random_vector(vector_size);

  auto v1    = vec;
  auto start = std::chrono::high_resolution_clock::now();
  inplace_square_seq(v1);
  auto end     = std::chrono::high_resolution_clock::now();
  auto elapsed = duration_cast<microseconds>(end - start);
  std::print("In-place squaring took {} microseconds.\n", elapsed.count());
  auto n = std::count_if(v1.begin(), v1.end(), [](double val) { return val > 2500.0; });
  std::print("Number of elements greater than 2500.0: {}\n", n);

  auto v2 = vec;
  start   = std::chrono::high_resolution_clock::now();
  inplace_square_par(v2);
  end     = std::chrono::high_resolution_clock::now();
  elapsed = duration_cast<microseconds>(end - start);
  std::print("In-place squaring took {} microseconds.\n", elapsed.count());
  n = std::count_if(v2.begin(), v2.end(), [](double val) { return val > 2500.0; });
  std::print("Number of elements greater than 2500.0: {}\n", n);
}
