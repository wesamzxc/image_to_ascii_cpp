#include <iostream>
#include <string>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


char levels[] = "$@B%W#*oabdwOQCUYXnxjft/\\|()1{}[]?-_+~i!lI;:,\"^`'.";
char brightness_to_ascii(unsigned int brightness){
	for(int step = 0; step < 51; step++){
		if(brightness < step*5){
			return levels[step];
		}
	}
	return ' ';
}

void img_to_ascii(std::string filepath){
	int w, h, num_channels;
	// Three because that's the number of channels we actually care about
	unsigned char *img = stbi_load(filepath.c_str(), &w, &h, &num_channels, 3);
	int img_size = w*h*3;
	std::string ascii = "";

	int jump = 0;
	for(unsigned char *p = img; p < img+img_size; p += 3){
		ascii += (jump % w == 0 && jump != 0) ? "\n" : "";
		int brightness = (p[0] + p[1] + p[2])/3;
		ascii += brightness_to_ascii(brightness);
		jump++;
	}
	std::ofstream file;
	file.open("out.txt");
	file << ascii;
	file.close();
	return;
}

int main(int argc, char ** argv){
	if(argc < 2){
		std::cout << "Please enter the path to an image";
		return 0;
	}

	std::string filepath = argv[1];

	img_to_ascii(filepath);
}