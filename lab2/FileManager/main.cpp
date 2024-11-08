#include <iostream>
#include <string>
#include <fstream>
#include "windows.h"


bool readFile(const char* path) {
	std::cout << "Reading...\n";

	std::ifstream fIn;

	fIn.open(path);

	if (!fIn) {

		fIn.close();
        std::cout << "Cannot open file.\n";
		return false;
	}

    std::cout << "Read content:\n";
	std::string line;
	while (std::getline(fIn, line)) {
		std::cout << line << "\n";
	}
	fIn.close();

	return true;
}

bool writeToFile(const char* path, const char * text) {
	std::cout << "Writing...\n";

	std::ofstream fOut;

	fOut.open(path);

	if (!fOut) {
		fOut.close();
        std::cout << "Content not written.\n";
		return false;
	}

	fOut << text;
    std::cout << "Content written!\n";
	fOut.close();

	return true;
}


int main() {

	SetConsoleTitleA("F1 Write | F2 Read | F3 Exit");

	while(1)
	{
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			writeToFile("minchakov.safetxt", "Decrypted text for writing");
		}
		else if (GetAsyncKeyState(VK_F2) & 1)
		{
			readFile("minchakov.safetxt");
		}
		if(GetAsyncKeyState(VK_F3))
		{
			exit(0);
		}
	}


	return 0;
}