#  IoT TP Project  

> Collaborators :

    Clément Seckler
    Anthony Elineau
    Jordan Lefeuvre
    Rémi Cureau

The purpose to the project is to interact with a temperature sensor. We use an Arduino and a Raspberry Pi 3+ Model A.

At first, you'll have to plug all the wires to the Arduino with the temperature sensor. 
Then, put the `Script_temperature.ino` file on the Arduino. It will be able to fetch the current temperature.
After that, clone this project and create a virtual env : 

***
`$ python3 -m venv venv`
***
On linux :
`$ . venv/bin/activate`

On Windows :
`> venv\Scripts\activate`
***
Install the dependences : 

`$ pip install Flask`

***
To execute the python project just run the bash file
`./run.sh`
***
