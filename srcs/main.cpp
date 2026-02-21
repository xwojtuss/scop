#include <exception>
#include <iostream>
#include <cstdlib>

#define ALGEBRA_IMPLEMENTATION
#include "Renderer.hpp"

int	main(void) {
	Renderer	app;

	try {
		app.run();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}