#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "Singleton.h"
#include "IEntity.h"
#include "BatteryDecorator.h"

using namespace std;

Singleton* Singleton::theInstance = nullptr;
Singleton* Singleton::getInstance() {
    if (theInstance == nullptr) {
        theInstance = new Singleton();
    }
    return theInstance;
}
// Loops through existing entities,
// and updates the corresponding data if a match is found.
// If no match is found, it adds a new entity with its associated data.
void Singleton::setUpData(IEntity* entity) {
    bool newEntity = true;
    for (int i = 0; i < entityName.size(); i ++) {
        JsonObject tempDetails = entity->GetDetails();
        string name = tempDetails["name"];
        if (name.compare(entityName.at(i)) == 0) {
            tripDistance.at(i) = entity->GetTripDistance();
            deliveryVolume.at(i) = entity->GetDeliveryVolume();
            entitySpeed.at(i) = entity->GetSpeed();
            entityStrategy.at(i) = entity->GetStrategyName();
            batteryStatus.at(i) = entity->GetPercentage();
            tripDuration.at(i) = entity->GetTripDuration();
            newEntity = false;
            break;
        }
    }
    if (newEntity) {
        JsonObject tempDetails = entity->GetDetails();
        string name = tempDetails["name"];
        entityName.push_back(name);
        tripDistance.push_back(entity->GetTripDistance());
        deliveryVolume.push_back(entity->GetDeliveryVolume());
        entitySpeed.push_back(entity->GetSpeed());
        entityStrategy.push_back(entity->GetStrategyName());
        batteryStatus.push_back(entity->GetPercentage());
        tripDuration.push_back(entity->GetTripDuration());
    }
}

void Singleton::writeData() {
    // Print out the data
    ofstream outputFile;
    outputFile.open("Data.csv");
    outputFile << "Entity Name,Delivery Volume,Entity Speed,";
    outputFile << "Trip Distance,Entity Strategy,Battery Status,";
    outputFile << "Trip Duration" << endl;
    for (int i = 0; i < entityName.size(); i ++) {
        outputFile << entityName[i] << ",";
        outputFile << deliveryVolume[i] << ",";
        outputFile << entitySpeed[i] << ",";
        outputFile << tripDistance[i] << ",";
        if (entityName[i].compare("Drone") == 0) {
            outputFile << entityStrategy[entityName.size()-1] << ",";
        } else {
            outputFile << entityStrategy[i] << ",";
        }
        if (entityName[i].compare("Drone") == 0) {
            outputFile <<  batteryStatus[entityName.size()-1] << ",";
        } else {
            outputFile << 0.0 << ",";
        }
        outputFile << tripDuration[i] << endl;
    }
    outputFile.close();
}
