//
//  main.cpp
//  RayTraceCPU
//
//  Created by Joshua Chasnov on 22/3/2022.
//

#include "RayTraceCPU.hpp"

int main(int argc, const char * argv[]) {
    camera cam(16.0 / 9.0, 90);
    return 0;
}

void writeImage() {
    std::ofstream file("output.ppm");
    
    file << "P3" << "\n";
    file << 255 << " " << 255 << "\n";
    file << 255 << "\n";
    for (int y = 0; y < 255; y++) {
        for (int x = 0; x < 255; x++) {
            file << x << " " << y << " " << 0 << "   ";
        }
        file << "\n";
    }
    
    file.close();
    
    std::ifstream f("output.ppm");
    std::cout << f.good();
}
