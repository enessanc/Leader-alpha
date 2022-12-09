#include <iostream>
#include "source/campaign/entity/World.h"
#include <clocale>
#include "config.h"
#include <chrono>
# include <spdlog/spdlog.h>



int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL,"Turkish");
    spdlog::set_level(spdlog::level::trace);
    std::cout << "Current Game Directory: "<<PROJECT_SOURCE_DIR << "\n";
    auto start = std::chrono::high_resolution_clock::now();
    Leader::World w(2);
    w.initialize_country();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (end - start);
    std::cout << "Elapsed time is " << duration.count() << " milliseconds\n";
    return EXIT_SUCCESS;
}
