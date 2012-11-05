#include <iostream>
#include <exception>

void function(void) {
	std::clog << "throwing exception from function" << std::endl;
	throw std::exception();
}

int main(int argc, char *argv[]) {
	try {
		__asm__ ("int $0x3");
		function();
	}
	catch(std::exception) {
		std::clog << "exception from function caught" << std::endl;
	}

	try {
		std::clog << "throwing exception from main function" << std::endl;
		throw std::exception();
	}
	catch(std::exception) {
		std::clog << "exception from main caught" << std::endl;
	}
	return 0;
}
