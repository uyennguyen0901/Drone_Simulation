# Team-001-12-homework4
## Team members
<ul>
  <li>Minh Nguyen <code>nguy4793</code></li>
  <li>Minh Uyen Nguyen <code>nguy5105</code></li>
  <li>Dante Schroeder <code>schr1684</code></li>
</ul>

# Project 4
To further enhance drone functionality and efficiency, two key features have been proposed -  Battery for Drone - Charging Stations and Colect Data using:

#### Decorator/Factory

Decorator involves the a battery wrapped around the drone, which would be significantly essential in tracking flight time, and its detour when the battery is low.
The Factory feature involves the addition of recharge stations randomly add to the campus, which would allow drones to recharge quickly and efficiently between flights.

#### Singleton

The Singleton data collection feature has the ability to collect and store data from multiple drones in an efficient manner.

##### What is in this Data.csv?
<ul>
  <li>Entity Name</li>
  <li>Delivery Volume</li>
  <li>Entity Speed</li>
  <li>Trip Distance</li>
  <li>Entity Strategy</li>
  <li>Battery Status</li>
  <li>Trip Duration</li>
</ul>

## Simulation's Jobs
The simulation project involves an entire drone and robot management system meant to demonstrate the efficiency and collaboration of humans and vehicles. The simulation's main features include entity movement, energy management, and data logging. Drones are charged in this simulated world with identifying, picking up, and carrying robots to predetermined destinations. The project includes advanced pathfinding algorithms that allow Drone to explore the surroundings and avoid obstacles. The robots, on the other hand, act as the drones' cargo, ready to be picked up and carried.

The simulation relies heavily on energy management to ensure that drones can recharge their batteries at the nearest station when necessary. This complicates matters since the drones must balance their energy use with their primary mission of delivering robots. Throughout its runtime, the simulation keeps track of all scheduled trips, allowing users to query and analyze the data generated. This data can be used to evaluate the system's efficiency, identify areas for improvement, and inform future simulation iterations. Overall, the project provides a detailed insight into the dynamic interactions and logistical challenges of a drone and robot transportation system.

## Getting Started

Here is a quick overview of how to run the visualization (If you are using ssh, navigate to ssh category below):

    ```bash
    # Go to the project directory
    cd /path/to/repo/project
    
    # Build the project
    make -j
    
    # Run the project (./build/web-app <port> <web folder>)
    ./build/bin/transit_service 8081 apps/transit_service/web/
    ```
    
Navigate to http://127.0.0.1:8081 and you should see a visualization.

Navigate to http://127.0.0.1:8081/schedule.html and you should see a page to schedule the trips.

*Note: 8081 will depends on what port you used. If you use port 8082, then it will be http://127.0.0.1:8082 instead.*

# Simulation

## Schedule
You will be able to schedule the robots for a ride in this page http://127.0.0.1:8081/schedule.html. 

Type passenger name, select start and end destination, and press `Schedule Trip` button to schedule a trip. 

Now go to 3D Visualization page and select the view of the entities on top right corner.

## 3D Visualization
You will be able to watch the simulation of the drone and the passenger here http://127.0.0.1:8081.

On top right corner, you can change your camera view into locking the entities.

For more informations on build and run in different environments, click on:

<a href="https://github.umn.edu/umn-csci-3081-S23/Team-001-12-homework4/blob/main/README_Project.md">README_Project</a>

# New Features

## Battery for Drone and Charging Stations

### What does it do?
In essence, drones have intrinsic limits and must be charged to be active. The team chose to improve the drone's battery and charging station technology in order to broaden its functional capabilities by providing energy management solutions. This system features battery life monitoring and conveniently accessible charging stations for in-flight recharge. Drones may monitor their remaining battery capacity to ensure they maintain optimal energy levels for continuous operation.
### Why is it significantly interesting and why you chose this design pattern?
This solution is particularly intriguing since it handles real-world drone restrictions such as restricted flying duration owing to battery limits. The drone's performance and flying time may be improved by incorporating energy management technologies, making the drone more useful and efficient in a variety of applications.
<br>
The Decorator design pattern was used to track the drone's battery state since it allows for the installation of additional features without changing the main structure of the drone. This enhances system flexibility and adaptation. The Factory design pattern was chosen for charging station management because it centralizes station development and distribution, allowing for more control and scalability.
### How does it add to the existing work?
The addition of the battery management system and charging stations improves the overall performance of the drone system. It allows drones to operate for longer periods and cover more extensive areas by efficiently managing their energy consumption. These enhancements can lead to more effective and reliable drone operations in various fields, such as delivery services, surveillance, and monitoring.
<br> 
<br>
#### Decorator
Decorator design pattern is employed in this scenario to enhance the functionality of a drone by wrapping it with a battery. 
<br>
The code contains the following key parts:
<br>
<br>
<code>BatteryDecorator.h</code>: BatteryDecorator class is based on the IEntity interface. The BatteryDecorator class is in charge of building and maintaining a drone's battery. It encircles a Drone object and provides battery functionality to it.
The BatteryDecorator class has numerous methods for dealing with battery-related procedures, including:
<br>
<ul>
	<li>Getting and setting the battery percentage.</li>
	<li>Getting the nearest charging station.</li>
	<li>Calculating the total distance of a trip.</li>
</ul>
<code>BatteryDecorator.cc</code> class implementation defined in the BatteryDecorator.h header file. The BatteryDecorator class encapsulates a Drone object in order to add battery management features.
<br>
<br>
Here's a rundown of what each method in this implementation does:
<br>
<code>BatteryDecorator::BatteryDecorator(Drone *drone)</code> - Constructor that sets the drone and the initial battery % to 500 to initialize the BatteryDecorator object.
<br>
<code>BatteryDecorator::BatteryDecorator()</code> - A destructor that frees any dynamic memory associated with the object (which is now empty).
<br>
<code>BatteryDecorator::Update()</code> - This function controls the drone's battery status and refreshes its state. It changes the color of the drone based on the battery %, determines whether the drone needs to be recharged, and transfers the drone to the nearest charging station if necessary. It also refreshes the battery % of the drone based on its activities.
<br>
<code>BatteryDecorator::GetNearestStation(vectorIEntity*> stations)</code> - This method locates the nearest charging station to the drone's current location by iterating over a list of charging stations and calculates the distance between each one. The station with the shortest distance is designated as the closest station.
<br>
<code>BatteryDecorator::totalDistance(std::vectorstd::vectorfloat>> route)</code> - Calculates the total distance of a specified path by adding the distances between consecutive points on the path.

#### Factory
ChargerFactory class is responsible for creating Charger objects, and the Charger class represents a charging station for drones.
<code>ChargerFactory.h</code>: Is responsible for producing Charger objects from JSON data and inherits from the IEntityFactory interface. It employs just one method:
<br>
<code>IEntity* CreateEntity(JsonObject& entity)</code> - Creates a Charger object (if feasible) from the provided JSON object and returns a reference to the generated IEntity.
<br>
<br>
<code>Charger.h</code> - Derives from the IEntity interface and represents a drone charging station. It employs the following techniques:
<br>
<code>Charger(JsonObject& obj)</code> - Constructor that creates a Charger object from a JSON object holding the charger's information.
<br>
<code>Charger()</code>- The Charger object's destructor.
<br>
<code>GetPosition() const</code>- Returns the charger's location.
<br>
<code>JsonObject GetDetails() const</code>- Returns the charger's information as a JSON object.
<br>
<code>float GetSpeed() const</code>- The default function for satisfying the IEntity parent class, which returns a blank float.
<br>
<code>Vector3 GetDirection() const</code>- The default function for satisfying the IEntity parent class, it returns blank Vector3.
<br>
<code>Vector3 GetDestination() const</code>- The default function for satisfying the IEntity parent class, it returns blank Vector3.

### Instruction to use this new feature:
Drones have limitations in terms of battery life, and the provided code represents their interactions during flights. The drone calculates the expected distance autonomously and decides whether to stop for charging or continue its journey. This feature is accessible on the web interface, allowing users and developers to interact with the drone during its flight.

The feature manages the drone's battery life and charging process throughout the simulation, enabling the drone to recharge at the nearest charging station when necessary. To achieve this, follow these steps:
<ul>
	<li>Apply the Decorator pattern to monitor the drone's battery state effectively.</li>
	<li>Enhance the drone class to include battery tracking capabilities, ensuring the drone can recognize when it needs recharging.</li>
	<li>Employ the Factory pattern for creating and managing charging stations.</li>
	<li>Distribute charging stations throughout the operational area to ensure accessibility for drones.</li>
	<li>Program drones to locate and utilize the nearest charging station when their battery levels are low.</li>
	<li>Drone turns red and takes a detour to the nearest charging station. After fully charging, it returns to green and continues the journey.</li>
	<li>Implement continuous system monitoring to ensure efficient energy management and effective drone operations.</li>
</ul>

## Collect Data
The Singleton design pattern is used to handle data that is associated with several entities in a system. The Singleton class guarantees that only one instance of itself is produced and gives a global access point to that instance.
### What does it do?
The design pattern is employed to create an instance of the Singleton class that handles and modifies data related to various entities. The <code>setUpData</code> method updates the corresponding data if a match is found; if not, it introduces a new entity along with its associated data. The <code>writeData</code> function is used to save the updated information to a CSV file.
### Why is it significantly interesting and why you chose this design pattern?
Comprehend that the provided base code is primarily designed for a drone to pick up a robot based on the information from the shedule.html page. Nonetheless, attempting to discern the type of data generated after the drone completes the trip stimulates curiosity among developers. The Singleton design plays a role in this instance because it centralizes data management for numerous entities, maintaining consistency and removing the need to create several instances of the same class. This enables the system to retain a single source of truth for data connected with diverse entities, making information administration and changes easier. Singleton ensures that a class has just one instance during the life of the program, which is useful for coordinating operations throughout the system or managing shared resources. Singleton offers a global access point to its instance, allowing access to and management of shared resources or services from any section of the application. By centralizing data or resource management, Singleton maintains consistency and decreases the complexity of managing shared resources. Singleton reduces the amount of code required to manage shared resources, making it easier to comprehend and maintain. Because the Singleton class has only one instance, it avoids potential problems caused by multiple instances inadvertently accessing or modifying the same shared resource.
### How does it add to the existing work?
The Singleton design adds a centralized, efficient, and consistent mechanism for maintaining and updating data linked to multiple entities to the current task. This facilitates the addition or modification of entities, the collection of data, and the tracking of performance indicators.
<br>
The code contains the following key parts:
<br>
<br>
Definition and implementation of the singleton class:
<br>
<code>theInstance</code>: A static reference to the Singleton class's unique instance.
<br>
<code>getInstance()</code>: A static method that returns the Singleton class's unique instance, constructing it if required.
<br>
<code>setUpData(IEntity* entity)</code>: This function accepts an IEntity pointer as an argument and, if a match is found, changes the data pertaining to that entity. If no match is detected, a new entity with its related data is added.
<br>
<code>writeData()</code>: The modified data is written to a CSV file using this function. It iterates over the list of entities, writing to the CSV file data such entity name, delivery volume, entity speed, trip distance, entity strategy, battery condition, and trip time.
<br>
<br>
Implementation of the frontend development:
<br>
<code><button>Get the CSV</button></code>: When clicked or pushed, a client development interactive element performs an action on a web page. When a user hits or pushes an HTML button, events or actions defined by main.js can be triggered.
<br>
<code>toggleCVS()</code>: A JavaScript function that invoked and sends a "writeCSV" command to an API along with an object containing a single key-value pair test: "test". This function's purpose is to call the API's writeCSV command using the provided data.
<br>
<code> else if(cmd == "writeCSV")</code>: The ReceiveCommand in transit_service.cc function handles the "writeCSV" instruction from the web server. When the "writeCSV" command is identified:
<ul>
  <li>Calling Singleton::getInstance() returns the Singleton instance.</li>
  <li>On the Singleton instance, the writeData() method is called.</li>
</ul>

### Instruction to use this new feature:
This feature is user-friendly and accessible to both clients and developers, showcasing well-crafted code. To execute it, simply click the designated button on the drone simulation HTML file once the drone has completed dropping off the robot. The Data.csv file will be created and updated automatically, providing comprehensive details regarding the collected data. The drone's data primarily contributes to the cumulative number of trips, durations, and distances. It is essential to note that the drone lacks its own movement strategy in the code, resulting in the adoption of the last robot's movement strategy. Since robots do not have significant battery-related tasks, their battery status defaults to zero, while the drone retains the current battery value.

# UML
<p align="center"> <img src="/pics/Charger%20UML%20Diagram.png" alt="Charger UML Diagram" style="height:auto;width:auto;border-radius:5px;1"></p>

The UML diagram was generated for the full system of a drone meant to pick up robots and human things while following a planned path in a transit service. This detailed graphic depicts the numerous components and their interactions, providing smooth coordination between the entities of the drone, robot, human, and helicopter. Furthermore, the UML diagram includes updates on new features like battery charging and data collecting capabilities. The UML diagram offers a clear understanding of the abilities and interactions between the components by graphically depicting the system's architecture, allowing for efficient development and maintenance of the drone-based transportation service system.

# Docker
Docker Hub is a cloud-based registry service that allows users to connect code sources, generate, and store Docker images. The URL you provided is for a repository called "team_001_12_homework4", which is managed by the user account "nguy5105".
```bash
https://hub.docker.com/repository/docker/nguy5105/team_001_12_homework4/general
```
You must have Docker installed on your machine to utilize this Docker image. After installing it, you may grab the image from the Docker Hub source and run it as a container on your local system or in the cloud.
To pull the image, you would use the following command in your terminal:
```bash
docker pull nguy5105/team_001_12_homework4:latest
```
To run the image as a container:
```bash
docker run -it --name my-container nguy5105/team_001_12_homework4:general
```
Remember to replace "my-container" with a custom name for your container instance.
# YouTube Video Presentation
Our team members will have the opportunity to display their successes and important contributions to the project in this video presentation. The presentation is organized into three sections, each concentrating on one of two important features built using the Decorator/Factory and Singleton design patterns. We hope to give a full overview of these crucial elements by leading you through the implementation process and discussing the logic behind our choices. Finally, we will show how these new features work together in operation, providing a hands-on experience as well as a glance into the expanded functionality and user experience that our project now provides.

<a href="https://www.youtube.com/embed/LEApuYWwNsk" >Team Presentation </a>
<br>
<br>
<a href="https://www.youtube.com/watch?v=3pRFoFTfA0Q">Demo video for running simulations</a>

# Sprint Retrospective
<p align="center"> <img src="/pics/Sprint_Retrospective.png" alt="Sprint Retrospective" style="height:auto;width:auto;border-radius:5px;1"></p>
The team uses this framework to reflect on their most recent sprint and organize their input into four categories:
<ul>
	<li>Good: This refers to the sprint's good features, things that went well, or accomplishments that the team is proud of. This input might assist the team in recognizing and building on the strengths.</li>
	<li>Bad: This category contains the sprint's bad characteristics, such as difficulties, obstacles, or failures that the team encountered. It is critical for the team to be open and honest about these issues in order to discover opportunities for progress.</li>
	<li>Ideas: The purpose of this area is to provide potential solutions or ideas to solve the concerns described in the "Bad" category. These might be interesting and new ideas for the team to pursue in the future.</li>
	<li>Actions: Identifying actual measures or activities that the team can do to enhance their performance in the upcoming sprint is the focus of this category.</li>
</ul>
By adhering to this framework, the team may hold a planned and productive retrospective meeting in which they can celebrate accomplishments, admit obstacles, create suggestions for improvement, and take action toward reaching their goals.
