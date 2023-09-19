#ifndef Charger_H_
#define Charger_H_

#include "IEntity.h"

class Charger : public IEntity {
 public:
  /**
   * @brief Chargers are created with a name
   * @param obj JSON object containing the charger's information
   */
  Charger(JsonObject& obj);
  /**
   * @brief Destructor for a charger
   */
  ~Charger() {}
  /**
   * @brief Gets the position of the charger
   * @return The position of the charger
   */
  Vector3 GetPosition() const { return position; }
  /**
   * @brief Gets the details of the charger
   * @return The details of the charger
   */
  JsonObject GetDetails() const { return details; }
  /**
   * @brief Default function to satisfy the IEntity parent class
   * @return A blank float
   */
  float GetSpeed() const {}
  /**
   * @brief Default function to satisfy the IEntity parent class
   * @return A blank Vector3
   */
  Vector3 GetDirection() const {}
  /**
   * @brief Default function to satisfy the IEntity parent class
   * @return A blank Vector3
   */
  Vector3 GetDestination() const {}

 private:
  JsonObject details;
  Vector3 position;
};

#endif  // CHARGER_H_
