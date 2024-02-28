#include <iostream>

// This function cannot be made constexpr because output and input can only be done at runtime.
// The versions of `operator<<` and `operator>>` that do output and input don't support constexpr.
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns height from ground after "seconds" seconds
// This function is made constepxr because it just calculates a value from its inputs and return it.
// Arithmetic can be done at compile-time, and no non-constexpr functions are called.
// Reminder: A constexpr function can be evaluated at compile-time or runtime.
//   If its arguments are constexpr, it can be called at compile-time.
//   In this case, it's called at runtime because the argument for towerHeight isn't constexpr.
// If a function can be made constexpr, it should be.
// Remember: function parameters are not constexpr, even in a constexpr function
constexpr double calculateBallHeight(double towerHeight, int seconds)
{
	constexpr double gravity{ 9.8 }; // constexpr because it's a compile-time constant

	// Using formula: [ s = u * t + (a * t^2) / 2 ], here u(initial velocity) = 0
	// These variables can't be constexpr since their initializers aren't constant expressions
	const double distanceFallen{ (gravity * (seconds * seconds)) / 2.0 };
	const double currentHeight{ towerHeight - distanceFallen };

	return currentHeight;
}

// This function cannot be made constexpr because output and input can only be done at runtime.
// The versions of `operator<<` and `operator>>` that do output and input don't support constexpr.
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// This function cannot be made constexpr because output and input can only be done at runtime.
// The versions of `operator<<` and `operator>>` that do output and input don't support constexpr.
void printCalculatedBallHeight(double towerHeight, int seconds)
{
	// height can only be const (not constexpr) because its initializer is not a constant expression
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);
}

int main()
{
	// towerHeight can only be const (not constexpr) because its initializer is not a constant expression
	const double towerHeight{ getTowerHeight() };

	printCalculatedBallHeight(towerHeight, 0);
	printCalculatedBallHeight(towerHeight, 1);
	printCalculatedBallHeight(towerHeight, 2);
	printCalculatedBallHeight(towerHeight, 3);
	printCalculatedBallHeight(towerHeight, 4);
	printCalculatedBallHeight(towerHeight, 5);

	return 0;
}
