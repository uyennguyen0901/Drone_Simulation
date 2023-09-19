#ifndef BATTERYDECORATOR_H_
#define BATTERYDECORATOR_H_

#include <vector>
#include "Drone.h"
#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"
#include "DroneFactory.h"
#include "PathStrategy.h"
#include "Drone.h"
using namespace std;
/**
 * @brief this class inhertis from the IEntity class and is responsible for creating and updating the battery of the drone
 */
// Represents a battery in a physical system.
class BatteryDecorator : public IEntity {
 public:
  // Battery is created
  /**
  * @brief Construct a new battery object
  * 
  * @param obj details for entity
  */
  BatteryDecorator(Drone *obj);
  // Destructor
  /**
  * @brief Destructor for the battery object
  */
  ~BatteryDecorator();
  /**
  * @brief get battery's id
  * 
  * @return drone's ID
  */
  virtual int GetId() {return this->drone->GetId();}
  /**
  * @brief get battery's position
  * 
  * return drone's position
  */
  virtual Vector3 GetPosition() const {return this->drone->GetPosition();}
  /**
   * @brief get entity's direction
   * 
   * return drone's direction
   **/
  virtual Vector3 GetDirection() const {return this->drone->GetDirection();}
  /**
   * @brief get entity's destination
   * 
   * return drone's destination
   **/
  virtual Vector3 GetDestination() const {return this->drone->GetDestination();}
  /**
   * @brief get entity's details
   * 
   * return drone's details
   **/
  virtual JsonObject GetDetails() const {return this->drone->GetDetails();}
  /**
   * @brief get entity's speed
   * 
   * return drone's speed
   **/
  virtual float GetSpeed() const {return this->drone->GetSpeed();}
  /**
   * @brief get entity's availability
   * 
   * return drone's availability
   **/
  bool GetAvailability() const {return this->drone->GetAvailability();}
  /**
  * @brief get percentage of battery
  * @return return percentage of battery
  */
  float GetPercentage() const {return percentage;}
  /**
   * @brief get entity's strategy name
   * 
   * return drone's strategy name
   **/
  virtual string GetStrategyName() {return this->drone->GetStrategyName();}
  /**
   * @brief set entity's graph
   * 
   * @param igraph graph to set
   **/
  void SetGraph(const IGraph* igraph) {drone->SetGraph(igraph);}
  /**
   * @brief set entity's availability
   * 
   * @param choice choice of boolean (T or F)
   **/
  void SetAvailability(bool choice) {this->drone->SetAvailability(choice);}
  /**
   * @brief update entity
   * 
   * @param dt delta time
   * @param scheduler a vector of robot
   * @param station vector of stations
   **/
  void Update(double dt, std::vector<IEntity*> scheduler,
  std::vector<IEntity*> stations);
  /**
   * @brief set entity's position
   * 
   * @param pos_ position to be set
   **/
  void SetPosition(Vector3 pos_) {this->drone->SetPosition(pos_);}
  /**
   * @brief set entity's direction
   * 
   * @param dir_ direction to be set
   **/
  void SetDirection(Vector3 dir_) {this->drone->SetDirection(dir_);}
  /**
   * @brief set entity's destination
   * 
   * @param des_ destination to be set
   **/
  virtual void SetDestination(Vector3 des_) {this->drone->SetDestination(des_);}
  /**
   * @brief set entity's strategy name
   * 
   * @param strategyName_ name of strategy to be set
   **/
  void SetStrategyName(string strategyName_)
  {this->drone->SetStrategyName(strategyName_);}
  /**
   * @brief rotate entity
   * 
   * @param angle angle to rotate
   **/
  void Rotate(double angle) {this->drone->Rotate(angle);}
  /**
   * @brief make entity jump
   * 
   * @param height how height to jump
   **/
  void Jump(double height) {this->drone->Jump(height);}

  /**
  * @brief set the initial percentage of the battery (500)
  * 
  * @param per the amount of battery percentage
  */
  void SetPercentage(double per) { percentage = per; }

  /**
  * @brief get the neareast charging station
  * 
  * @param stations vector of the stations
  */
  void GetNearestStation(vector<IEntity*> stations);
  // /**
  // * @brief calculate the distance to travel
  // *
  // * @param path the path to calculate
  // */
  // float calculatePathDistance(std::vector<std::vector<float>> path);
  /**
  * @brief get drone's color
  * 
  * @return drone's color
  */
  string GetColor() const { return drone->GetColor(); }
  /**
  * @brief set drone's color
  * 
  * @param col_ drone's color
  */
  void SetColor(string col_) {drone->SetColor(col_);}

  // Removing the copy constructor and assignment operator
  // so that battery cannot be coppied.
  /**
  * @brief copy constructor remove
  */
  BatteryDecorator(const BatteryDecorator& batterydecorator) = delete;
  /**
  * @brief assignmet operator remove
  */
  BatteryDecorator& operator=
  (const BatteryDecorator& batterydecorator) = delete;
  /**
  * @brief Calculate the total distance of the trip
  * @param path path from drone's position to robot's position to robot's destination
  * @return total distance of the trip
  */
  float totalDistance(std::vector<std::vector<float>> path);

 private:
  float percentage;
  bool needCharge = false;
  bool checkCharge = false;
  IStrategy* toRobot = nullptr;
  // IStrategy* toFinalDestination = nullptr;
  IEntity *nearestStation;
  Drone *drone;
};

#endif  //  BATTERYDECORATOR_H_"
