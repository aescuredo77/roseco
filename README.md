# roseco
Roseco: Diff-Robot base in ROS

This repository hosts the source code for the ROS < ROSECo > package.

 ![image info](./pictures/roseco3.jpg)

This is part of the practices that I am doing in the course MAstering Robot orerating System ROS in the ROBOCADEMY

## Description ##

The robot type is a diff-robot with two driving wheels and a caster wheel. 

- Teensy 4.0 .
- wifi with ESP8266.
- Bluetooh.
- Motors Controlled by i2c more detail in the electronics section.
- 3.7v Lipo battery of 6000 mah, with a Powerboost that provides us with 5 v.
- Induction charging system.
- camera Jevois
- You can add sensors or actuators, giving it great versatility.
- Optionally you can add a raspberry pi 3 or 4 with camera.

![image info](./pictures/roseco2.jpg)




## Key concepts covered ##
- The goal of this app is to practice with urdf and xacro, and implement it in gazebo to simulate.

- Create a model base in the stl.

- Create a xacro:macro

- Navigation next update

![image info](./roseco/pictures/roseco_pre.png)

## Update ##

-roseco_description

-roseco_gazebo

-roseco_control --> not finish

- electronics


[![Watch the video](./pictures/video.png)](https://www.youtube.com/watch?v=kRHV5qrDao4)




## Usage ## 


To use the `roseco` package clone this repository into the `src` folder of your catkin workspace.

Then build the workspace with `catkin_make`.




   roslaunch roseco_description view_roseco.launch 

   roslaunch roseco_gazebo roseco.launch   

   roslaunch roseco_control roseco_control.launch 


 
## Electronics : Servo motor with I2C## 

#todo
