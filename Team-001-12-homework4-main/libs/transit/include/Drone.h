#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "PathStrategy.h"
#include "math/vector3.h"

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the speed of the drone
   * @return The speed of the drone
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the availability of the drone
   * @return The availability of the drone
   */
  bool GetAvailability() const { return available; }
  /**
   * @brief Gets the nearest entity in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
  * @brief Get the nearest station in the stations
  */
  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler,
  std::vector<IEntity*> stations);
  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Makes the drone jump
   * @param height The height at which the drone should jump
   */
  void Jump(double height);

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief Gets the strategy of the robot
   * @return The strategy of the robot
   */
  IStrategy* GetRobotStrategy() const { return toFinalDestination; }

  /**
   * @brief Gets the strategy of the drone when appoaching robot
   * @return strategy of the drone when appoaching robot
   */
  IStrategy* GetToRobotStrategy() const { return toRobot; }

  /**
  * @brief Set the Strategy of the Drone
  * @param strategyName_ Type string contain the strategy name
  **/
  virtual void SetStrategyName(std::string strategyName_) {
    strategyName = strategyName_;
  }

 /**
  * @brief Get the Strategy name of the Drone base on the Robot's Strategy
  * @return Type string of the IEntity's strategy
  **/
  virtual std::string GetStrategyName() {
    return strategyName;
  }
  /**
  * @brief set the initial percentage of the battery (500)
  * 
  * @param per the amount of battery percentage
  */
  void SetPercentage(double per) { percentage = per; }
  /**
  * @brief get percentage of battery
  * @return return percentage of battery
  */
  float GetPercentage() const {return percentage;}

 private:
  JsonObject details;
  Vector3 position;
  // Vector3 tempDestination
  Vector3 direction;
  std::string color = "None";  // None means default color
  float jumpHeight = 0;
  bool goUp = true;  // jump helper
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  float percentage;
  std::string strategyName;
  IEntity* nearestEntity = nullptr;
  IStrategy* toRobot = nullptr;
  IStrategy* toFinalDestination = nullptr;
};

#endif  // DRONE_H_
