#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "pixel.h"

// function to parse input file and populate pixel_list vector
void read_pixels(const std::string& filename, std::vector<Pixel>& pixel_list) {
	std::ifstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream ss(line);
		std::string token;

		Pixel pixel;

		std::getline(ss, token, ',');
		pixel.x = std::stoi(token);

		std::getline(ss, token, ',');
		pixel.y = std::stoi(token);

		std::getline(ss, token, ',');
		pixel.r = std::stof(token);
		
		std::getline(ss, token, ',');
		pixel.g = std::stof(token);

		std::getline(ss, token, ',');
		pixel.b = std::stof(token);

		pixel_list.push_back(pixel);

	}

	file.close();

}

// function to calculate average betweeb r,g,b values
void average_colors(std::vector<Pixel>& pixel_list) {
	float sum_r = 0.0f, sum_g = 0.0f, sum_b = 0.0f;
	for (const Pixel& pixel : pixel_list) {
		sum_r += pixel.r;
		sum_g += pixel.g;
		sum_b += pixel.b;
	}

	float avg_r = sum_r / pixel_list.size();
	float avg_g = sum_g / pixel_list.size();
	float avg_b = sum_b / pixel_list.size();

	std::cout << "Average R: " << avg_r << std::endl;
	std::cout << "Average G: " << avg_g << std::endl;
	std::cout << "Average B: " << avg_b << std::endl;
}

// function to flip all pixels vertically
void flip_vertically(std::vector<Pixel>& pixel_list) {
	int y_max = 256;
	for (Pixel& pixel : pixel_list){
		pixel.y = y_max - 1 - pixel.y;
	}
}

// function to save pixel list in file
void save_pixels(const std::string& filename, const std::vector<Pixel>& pixel_list) {
	std::ofstream file(filename.c_str());
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		exit(EXIT_FAILURE);
	}

	for (const Pixel& pixel : pixel_list) {
		file << pixel.x << "," << pixel.y << "." << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
	}

	file.close();
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <input_file> " << std::endl;
		return EXIT_FAILURE;
	}

	std::string input_file = argv[1];
	std::vector<Pixel> pixel_list;

	// read pixels from file
	read_pixels(input_file, pixel_list);

	// calulcate average colors
	average_colors(pixel_list);

	// save flipped pixels to file
	save_pixels("flipped.dat", pixel_list);

	return EXIT_SUCCESS;
}

