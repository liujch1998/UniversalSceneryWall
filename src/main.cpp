#include "geometry.hpp"
#include "task.hpp"

int main (int argc, char **argv) {
	Task task;
	task.Input();
	task.Generate();
	task.Output();

	return 0;
}

