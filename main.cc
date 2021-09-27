#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include <cstring>

std::mt19937_64 gen(43);
constexpr int32_t data_size {1024};

void loop(int32_t outloop, int32_t inloop){
    for(int32_t i = 0; i < outloop; ++i) {
        for(int32_t j = 0; j < inloop; ++j){
            char buf[64];
            snprintf(buf, sizeof buf, "%016lx", gen());
            char* data = (char*) malloc(sizeof(char)*data_size);
            memset(data, 0, data_size);
            auto index = random() % 900;
            memcpy(data+index, buf, sizeof buf);
            // char tmp = data[0]; // linear O(1), not needed
            free(data);
        }
    }
}

// malloc --> random read --> random write --> free

int main(int argc, char* argv[]){
    if (argc < 2 || argc > 4) {
        printf("Usage: ./main n_thread [outloop] [inloop]\n");
        return 0;
    }
    int n_thread = atoi(argv[1]);
    int32_t outloop = 1;
    int32_t inloop = 1000;
    if (argc >= 3) {
        outloop = atoi(argv[2]);
    }

    if (argc == 4) {
        inloop = atoi(argv[3]);
    }

    std::vector<std::thread> tvec;
    tvec.reserve(n_thread);

    auto tic = std::chrono::system_clock::now();
    for(int i = 0; i < n_thread; ++i) {
        tvec.emplace_back(&loop, outloop, inloop);
    }

    for(int i = 0; i < n_thread; ++i) {
        tvec[i].join();
    }
    auto toc = std::chrono::system_clock::now();
    auto duration = std::chrono::duration<double, std::milli>(toc-tic).count();
    std::cout << "Total threads: " << n_thread << ", total loop: " << outloop << "*" << inloop << ", total cost: " << duration << " (ms), each thread cost: " << duration / n_thread << " (ms)" << std::endl;

    return 0;
}
