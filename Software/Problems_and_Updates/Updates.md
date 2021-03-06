# About Updates File

Main aim of this file is recording solved problems, recorded at 
the [Problems](https://github.com/EWA-Mechatronics/ME462-Project/blob/master/Software/Problems_and_Updates/Problems.md) file,  of the software part by dates.

### 16.06.2020

-  SB Game Manager is created for 'Prey and Predator' game scenario.

-  Fixed the issue that causes the transmited data, with pipe, lost their meanings, if the type of the data is a list. 
For example, if one wished to transmit the following list, active_sensors = ["Vision_sensor", "Distance_sensor"], by using pipe, it would be transmitted as "Vision_sensorDistance_sensor". However, now it will transmitted as "Vision_sensor,Distance_sensor" to make it possible to strip from ','.

### 15.06.2020

-  Subprocess pipe is modified to be used with inputs.

-  Created dictionary instead of variables for specific robot base speeds at subclasses of Grid class,such as Savanna and Forest, need a  in order to provide smooth calculations at manager.

### 28.05.2020

-  Status bars at the all of the windows are set to provide necessary information to the user for possible cases. (SB)

-  **Threads** are replaced with **Subprocesses** to prevent complex design. (SB) 

-  Fixed an issue that causes the manager to run in the background even when the GUI is closed. (SB)

-  All pushbuttons are made functionless, except **Stop** push button, when the **simulation is running**, to prevent confusion and multiple **Game Managers** running at the background. (SB)

-  **Start Button** can not be activated without selecting necessary variables, such as robot type and scenario. (SB)

-  Fixed an issue that causes an error when the **Stop** push button is pressed before simulation is started. (SB)
 
-  GUI now check for a second time, if the user really wants to exit or not, to prevent misscliks done. (SB)

### 27.05.2020

- Fixed the issue that causes the push buttons lost their functions after,Robot and Target initial positions are assigned. (SB)

- Previous **Game Manager** is deleted, because of design considerations. (GM)

- In order to create a sustainable design
**Game Manager** is now created as a class, which includes general funcitons that will be used by all game scenarios. (GM)

### 26.05.2020

- Instances of Robot subclasses, such as Lion() and Deer(), can be created with specified initial coordinates. (SB)

- Fixed the issue that causes the push buttons lost their original colors, when the Game Map Window was opened again after being closed. (SB)

- Initial position selection button for **Robot** is added to Game Map Window. (SB)

- Initial position selection button for **Target** is added to Game Map Window. (SB)


