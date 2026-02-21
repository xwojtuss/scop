#include <exception>
#include <iostream>
#include <cstdlib>
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