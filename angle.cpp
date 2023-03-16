#include <iostream>
#include <cmath>

int main() {
    // Define the coordinates of the triangle vertices
    double Ax = 1, Ay = 1;
    double Bx = 3, By = 1;
    double Cx = 2, Cy = 4;

    // Calculate the vector from the base to the farthest vertex
    double Vx = Cx - Ax;
    double Vy = Cy - Ay;

    // Normalize the vector to get the direction of the triangle's facing position
    double norm = std::sqrt(Vx*Vx + Vy*Vy);
    double Fx = Vx / norm;
    double Fy = Vy / norm;

    // Calculate the angle between the positive x-axis and the facing direction
    double angle = std::atan2(Fy, Fx);
    double angle_deg = std::round(angle * 180.0 / M_PI * 10) / 10;

    // Calculate the weight center of the triangle
    double Wx = (Ax + Bx + Cx) / 3;
    double Wy = (Ay + By + Cy) / 3;

    std::cout << "The direction of the triangle's facing position is " << angle_deg << " degrees." << std::endl;
    std::cout << "The weight center of the triangle is (" << Wx << ", " << Wy << ")." << std::endl;

    return 0;
}

