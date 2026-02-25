#include <exception>
#include <iostream>
#include <cstdlib>

#include "app/Application.hpp"

int	main(void) {
	scene::Scene		scene;
	app::Application	app(scene);

	try {
		app.run();
	} catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}