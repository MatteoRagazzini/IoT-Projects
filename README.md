# IoT-Projects

The repository contains 3 academic projects about IoT, SoC programming and Real Time Operating Systems.
In order to make them work, you need to rebuild exactly the same configuration on the board, following
the fritzing schemas in each project's folder.

## First project
The first project was used to get familiar with the Single-Board Micro-Controller Arduino and embedded systems in general. With the use of leds, buttons, and a potentiometer we created a game ¨led_to_bag" in which you have to press the upper button to make the led move towards the bag (white led). If you stop exactly on the white led you win otherwise, if you press the button too many times and you exceed the bag, you loose. With the potentiometer you can change the difficulty of the game by varying the time at your disposal to take the led into the bag.

![alt text](https://github.com/MatteoRagazzini/IoT-Projects/blob/master/images/prj1.png)

## Second project
The goal of the project was to realize a smart radar for seeking and tracking objects with a task approach, based on synchronous final state machines.

It's made of a sonar mounted on a servo-motor that allows 0-180° rotation, a pir to detect movement, two red leds for the alarm, three buttons and a potentiometer:

![alt text](https://github.com/MatteoRagazzini/IoT-Projects/blob/master/images/prj2.png)


## Third project
This project involves different components and programming languages. The aim of the project was the realization of a smart dumpster, accessible through a mobile app, connected to the server via http, and with an online dashboard that displays the key information about the status of the dumpster and some statistics about the usage of it. 

The schema of the environment:

![alt text](https://github.com/MatteoRagazzini/IoT-Projects/blob/master/images/prj3_env.png)

Screenshot of the mobile app:

![alt text](https://github.com/MatteoRagazzini/IoT-Projects/blob/master/images/prj3_home.jpg) ![alt text](https://github.com/MatteoRagazzini/IoT-Projects/blob/master/images/prj3_deposit.jpg)

Screnshot of the web-based dashboard:

![alt text](https://github.com/MatteoRagazzini/IoT-Projects/blob/master/images/prj3_dashboard.png)
