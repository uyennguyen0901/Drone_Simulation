#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"

using namespace routing;

/**
 * @class IEntity
 * @brief Represents an entity in a physical system.
 *
 * An IEntity object has a unique ID, a position, a direction, a destination,
 * and details. It also has a speed, which determines how fast the entity moves
 * in the physical system. Subclasses of IEntity can override the `Update`
 * function to implement their own movement behavior.
 */
class IEntity {
 public:
  /**
   * @brief Constructor that assigns a unique ID to the entity.
   */
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }

  /**
   * @brief Virtual destructor for IEntity.
   */
  virtual ~IEntity() { delete graph; }

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int GetId() const { return id; }

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual Vector3 GetPosition() const = 0;

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual Vector3 GetDirection() const = 0;

  /**
   * @brief Gets the destination of the entity.
   * @return The destination of the entity.
   */
  virtual Vector3 GetDestination() const = 0;

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  virtual JsonObject GetDetails() const = 0;

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  virtual std::string GetColor() const { return "None"; }

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual float GetSpeed() const = 0;

  /**
   * @brief Gets the availability of the entity.
   * @return The availability of the entity.
   */
  virtual bool GetAvailability() const {}

  /**
   * @brief Get the Strategy Name
   *
   * @return Streategy name
   */
  virtual std::string GetStrategyName() const {}

  /**
   * @brief Set the Strategy Name
   *
   * @param strategyName_ Strategy name
   */
  virtual void SetStrategyName(std::string strategyName_) {}

  /**
   * @brief Sets the availability of the entity.
   * @param choice The desired availability of the entity.
   */
  virtual void SetAvailability(bool choice) {}

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   * @param scheduler The list of all entities in the system.
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler,
  std::vector<IEntity*> stations) {}

  /**
   * @brief Sets the graph object used by the entity in the simulation.
   * @param graph The IGraph object to be used.
   */
  virtual void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void SetPosition(Vector3 pos_) {}

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void SetDirection(Vector3 dir_) {}

  /**
   *@brief Set the destination of the entity.
   *@param des_ The new destination of the entity.
   */
  virtual void SetDestination(Vector3 des_) {}

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  virtual void SetColor(std::string col_) {}

  /**
   * @brief Rotate the entity.
   * @param angle The angle to rotate the entity by.
   */
  virtual void Rotate(double angle) {}

  /**
   * @brief Make the entity jump.
   * @param height The height to make the entity jump.
   */
  virtual void Jump(double height) {}

  virtual float Random(float Min, float Max) {
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
  }
   /**
   * @brief Get the total trip distance of the entity.
   * @return The trip distance of the entity in float.
   */
  float GetTripDistance() {
    return tripDistance;
  }
  /**
   *@brief Set the total trip distance of the entity.
   *@param dis The new trip distance of the entity.
   */
  void SetTripDistance(float dis) {
    tripDistance = dis;
  }
  /**
   * @brief Get the total number of deliveries of the entity.
   * @return The total number of deliveries of the entity in int.
   */
  int GetDeliveryVolume() {
    return deliveryVolume;
  }
  /**
   * @brief Function in increment the delivery of the entity 
   * when it makes more than one trip.
   */
  void IncrementDeliveryVolume() {
    deliveryVolume++;
  }

  /**
   * @brief Get the total time for the trip of the entity.
   * @return The total time of the entity to finish the trip in float.
   */
  float GetTripDuration() {
    return tripDuration;
  }
  /**
   *@brief Set the total time for the trip of the entity.
   *@param time The new time of the entity.
   */
  void SetTripDuration(float time) {
    tripDuration = time;
  }
  /**
  * @brief get percentage of battery
  * @return return percentage of battery
  */
  float GetPercentage() const {return batteryStatus;}

  /**
  * @brief set the initial percentage of the battery (500)
  * 
  * @param per the amount of battery percentage
  */
  void SetPercentage(double per) { batteryStatus = per; }

  // /**
  //  * @brief Gets the strategy of the robot
  //  * @return The strategy of the robot
  //  */
  // virtual IStrategy* GetRobotStrategy() const {}

 protected:
  int id;
  const IGraph* graph;
  float tripDistance = 0;
  int deliveryVolume = 0;
  float tripDuration = 0;
  float batteryStatus;
};

#endif  // IENTITY_H_
