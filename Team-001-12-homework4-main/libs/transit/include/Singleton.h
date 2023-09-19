#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <iostream>
#include <vector>
#include <string>
#include "IEntity.h"
using namespace std;
/**
 * Singleton
 * @brief A Singleton class to manage data of IEntity objects.
 *
 * This class is a Singleton pattern implementation to manage data of IEntity objects. It provides methods to
 * set up data, write data and get an instance of the Singleton class.
 */
class Singleton{
 public:
    /**
     * @brief Get the Singleton instance
     * @return A pointer to the Singleton instance
     */
    static Singleton* getInstance();
    /**
     * @brief Deleted copy constructor to enforce the Singleton pattern
     */
    Singleton(const Singleton&) = delete;
    /**
     * @brief Deleted assignment operator to enforce the Singleton pattern
     */
    Singleton& operator=(const Singleton&) = delete;
    /**
     * @brief Set up data for IEntity
     * @param entityData Pointer to an IEntity object
     */
    void setUpData(IEntity* entityData);
    /**
     * @brief Write the collected data to an output
     * @return Data.csv file and update the values when adding more trips
     */
    void writeData();

 protected:
    Singleton() {}
    static Singleton* theInstance;
    vector<string> entityName;
    vector<int> deliveryVolume;
    vector<float> entitySpeed;
    vector<float> tripDistance;
    vector<string> entityStrategy;
    vector<float> batteryStatus;
    vector<float> tripDuration;
};

#endif  // SINGLETON_H_

