#include <iostream>


double getHeight()
{
    std::cout << "Enter the height of the tower in meters: ";
    double height {};
    std::cin >> height;

    return height;
}

void getGround()
{
    std::cout << "the ball is on the ground.\n";
    exit(0);
}

double computeDistance(int x_seconds)
{
    double gravity {9.8};
    return gravity * x_seconds * x_seconds / 2;
}

double computeCurrentHeight(double height, double coveredDistance)
{
    if(height > coveredDistance)
        return height - coveredDistance;
    else
        getGround();
        return 0;
}

void heightStatus(int x_seconds, double currentHeight)
{
    std::cout << "At " << x_seconds <<" seconds, the ball is at height: " << currentHeight << " meters.\n";
}

int main()
{
    double height { getHeight() };

    if(height == 0)
        getGround();

    heightStatus(0, computeCurrentHeight(height, computeDistance(0)));
    heightStatus(1, computeCurrentHeight(height, computeDistance(1)));
    heightStatus(2, computeCurrentHeight(height, computeDistance(2)));
    heightStatus(3, computeCurrentHeight(height, computeDistance(3)));
    heightStatus(4, computeCurrentHeight(height, computeDistance(4)));
    heightStatus(5, computeCurrentHeight(height, computeDistance(5)));

    return 0;
}
