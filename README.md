# Veins Vanet Simulation

###Description
Simulating safety and non-safety messages in IEEE 1609.4. Tech Stack : Mac OS El Capitan 10.11.6, Omnet++ 5.0, SUMO 0.25.0, Veins 4 alpha 2, Inet 2.5

##Directory content

* `vanets/`  - Simulation to mimic MCB protocol, it is subclassing from veins framework
* `veins/`   - Open source vehicular networks framework with some added logging for debugging

* `vanets/src/results/extractMetrics.sh` - Extracts extracts data files per metric record, per simulation file. A file is generated and stored in results_per_metric/

##Run simulation

Go inside simulation folder

`$ cd vanets/`

##Run sumo socket

`Open terminal window`

`$ ./sumo-launchd.py -vv -c sumo-gui`

##Run omnetpp simulation



* Go to omnetpp IDE (eclipse)

* Select the file `/vanets/src/omnetpp.ini`

* Click `green button with arrow` at the top to run

* On the pop up window, Select the `config file to run`. The description is on title

* Click `run button` on top left corner
(NOTE: I usally do express because it is faster)


##Stop simulation

* Click on `stop button`
* Click the `button with the flag` to conclude simulation
* Clicking the flag will finish the simulation and generate the result files under

`/vanets/src/results/`
