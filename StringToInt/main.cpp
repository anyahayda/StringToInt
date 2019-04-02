#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <atomic>
#include <chrono>

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced() {
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}


int main(int argc, char *argv[]) {
    using std::cout;
    std::ifstream in_file("data.txt");
    std::vector<std::string> words;
    std::string word;
    int number, sum = 0;
    std::ofstream out_file("result.txt");
    while (in_file >> word)
        words.push_back(word);

    if (!strcmp(argv[1], "1")) {
        cout << "Time to convert a string into an integer number using stringstream (microseconds): " << '\n';
        auto stage1_start_time = get_current_time_fenced();
        for (auto &w: words) {
            std::stringstream to_int(w);
            to_int >> number;
            sum += number;
        }
        out_file << sum << '\n' << sum / words.size();
        auto stage2_start_time = get_current_time_fenced();
        auto stage1_time = stage2_start_time - stage1_start_time;
        std::cout << to_us(stage1_time) << std::endl;
    } else if (!strcmp(argv[1], "2")) {
        cout << "Time to convert a string into an integer number using stoi (microseconds): " << '\n';
        auto stage3_start_time = get_current_time_fenced();
        for (auto &w: words) {
            number = std::stoi(w);
            sum += number;
        }
        out_file << sum << '\n' << sum / words.size();
        auto stage4_start_time = get_current_time_fenced();
        auto stage2_time = stage4_start_time - stage3_start_time;
        std::cout << to_us(stage2_time) << std::endl;
    } else if (!strcmp(argv[1], "3")) {
        cout << "Time to convert a string into an integer number using sscanf (microseconds): " << '\n';
        auto stage5_start_time = get_current_time_fenced();
        for (auto &w: words) {
            sscanf(w.c_str(), "%d", &number);
            sum += number;
        }
        out_file << sum << '\n' << sum / words.size();
        auto finish_time = get_current_time_fenced();
        auto stage3_time = finish_time - stage5_start_time;
        std::cout << to_us(stage3_time) << std::endl;
    } else
        cout << "Write the correct number to convert the string (1, 2 or 3)";
    return 0;
}

