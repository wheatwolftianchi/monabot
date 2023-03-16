#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <Serial.h>

// Constants for motor control
const int MOTOR_ON = 1;
const int MOTOR_OFF = 0;

// Constants for movement control
const double MOVEMENT_SPEED = 1.0; // Distance units per second
const double TURNING_SPEED = 60.0; // Degrees per second


double* calculatebearing(double Ax, double Ay, double Bx, double By, double Cx, double Cy) {
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
    double* result = new double[3];
    result[0] = angle_deg;
    result[1] = Wx;
    result[2] = Wy;
    return result;
}


// Function to calculate the angle between two points
double calculateAngle(double x1, double y1, double x2, double y2) {
    return std::atan2(y2 - y1, x2 - x1) * 180.0 / M_PI;
}

int main() {
    // Initialize current and target positions
    double currentX = 0.0;
    double currentY = 0.0;
    double targetX = 3.0;
    double targetY = 4.0;

    // Initialize current facing angle
    double currentAngle = 0.0;

    // Loop until the cart reaches the target position
    while (std::abs(currentX - targetX) > 0.01 || std::abs(currentY - targetY) > 0.01) {
        Serial serial = Serial("COM3", 9600);
        // Calculate the angle between the current position and the target position
        double targetAngle = calculateAngle(currentX, currentY, targetX, targetY);

        // Calculate the angle difference between the current facing angle and the target angle
        double angleDifference = targetAngle - currentAngle;

        // Normalize the angle difference to be within -180 to 180 degrees
        if (angleDifference > 180.0) {
            angleDifference -= 360.0;
        }
        else if (angleDifference < -180.0) {
            angleDifference += 360.0;
        }

        // Check if the cart is facing the target position
        if (std::abs(angleDifference) <= 5.0) {
            // Move the cart forward
            std::cout << "Moving forward..." << std::endl;
            serial.write("1");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 * std::abs(targetX - currentX) / MOVEMENT_SPEED));
            serial.write("0");

            // Update the current position
            currentX = targetX;
            currentY = targetY;
        }
        else {
            // Turn the cart towards the target position
            std::cout << "Turning..." << std::endl;
            if (angleDifference > 0.0) {
                // Turn to the right
                serial.write("3");
            }
            else {
                // Turn to the left
                serial.write("2");
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 * std::abs(angleDifference) / TURNING_SPEED));

            // Update the current facing angle
            currentAngle += angleDifference;
        }
    }

    std::cout << "Reached target position!" << std::endl;

    return 0;
}