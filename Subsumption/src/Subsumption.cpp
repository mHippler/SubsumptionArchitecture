//============================================================================
// Name        : Subsumption.cpp
// Author      : Milena Hippler
// Description :
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class Data{
public:
	Data(){};
	virtual ~Data(){};
	Data getData(){	};
};

class Motor{
public:
	Motor(){};
	virtual ~Motor(){};
	void setOutput(Data output){};
};

class Layer{
public:
	Layer();
	virtual ~Layer();
};


class Level{
public:
	Level(){}
	virtual ~Level(){}
	//TODO rename!!!
	Data data; //Data input
	Data layerInput; //Output of suppress
	Data output; //Output for motor
	Data dataSuppress; //Output for suppress
	Data inhibitOut; //Output for inhibit
	void startLevel(Level levelPrev){}; //calls Suppressor, Layer and Inhibitor
	void startLevel(){}; //Case top level (no S and no I)
private:
	void suppressInput(Level levelPrev){}; //Suppressor
	void handleLayer(){}; //Layer
	void inhibitOutput(Level levelPrev){}; //Inhibitor
};

class Level0: public Level{
public:
	void startLevel(Level levelPrev){
		suppressInput(levelPrev);
		handleLayer();
		inhibitOutput(levelPrev);
	}
	void startLevel(){
		//Get data directly from Data
		layerInput = data.getData();
		handleLayer();
		output = inhibitOut;
	}
private:
	void suppressInput(Level levelPrev){
		//Sensor input
		Data dataIn = data.getData();
		//Previous Layer output
		Data supressIn = levelPrev.dataSuppress;

		/*
		 * Algorithm
		 * Merge to one input data
		 * set layerInput for this layer
		 */

		//TODO Wie am Besten darstellen?
		layerInput = supressIn;
	}
	void handleLayer(){
		/**
		 * Suppress Algorithm
		 * set dataSuppress for lower layer
		 */
		//TODO Wie am Besten darstellen?
		dataSuppress = layerInput;

		/**
		 * Layer Algorithm
		 * use layerInput as input
		 * set inhibitOut as output for inhibitor
		 */
		//TODO Wie am Besten darstellen?
		inhibitOut = layerInput;
	}
	void inhibitOutput(Level levelPrev){
		Data outputPrevLevel = levelPrev.inhibitOut;
		Data outputThis = inhibitOut;

		/**
		 * Algortihm
		 * Merge to one output data
		 * set output for motor
		 */
		//TODO Wie am Besten darstellen?
		output = outputPrevLevel;
	}
};

class Level1: public Level{
public:
	void startLevel(Level levelPrev){
		suppressInput(levelPrev);
		handleLayer();
		inhibitOutput(levelPrev);
	}
	void startLevel(){
		//Get data directly from Data
		layerInput = data.getData();
		handleLayer();
		output = inhibitOut;
	}
private:
	void suppressInput(Level levelPrev){
		//Sensor input
		Data dataIn = data.getData();
		//Previous Layer output
		Data supressIn = levelPrev.dataSuppress;

		/*
		 * Algorithm
		 * Merge to one input data
		 * set layerInput for this layer
		 */

		//TODO Wie am Besten darstellen?
		layerInput = supressIn;
	}
	void handleLayer(){
		/**
		 * Suppress Algorithm
		 * set dataSuppress for lower layer
		 */
		//TODO Wie am Besten darstellen?
		dataSuppress = layerInput;

		/**
		 * Layer Algorithm
		 * use layerInput as input
		 * set inhibitOut as output for inhibitor
		 */
		//TODO Wie am Besten darstellen?
		inhibitOut = layerInput;
	}
	void inhibitOutput(Level levelPrev){
		Data outputPrevLevel = levelPrev.inhibitOut;
		Data outputThis = inhibitOut;

		/**
		 * Algortihm
		 * Merge to one output data
		 * set output for motor
		 */
		//TODO Wie am Besten darstellen?
		output = outputPrevLevel;
	}
};

class Level2: public Level{
public:
	void startLevel(Level levelPrev){
		suppressInput(levelPrev);
		handleLayer();
		inhibitOutput(levelPrev);
	}
	void startLevel(){
		//Get data directly from Data
		layerInput = data.getData();
		handleLayer();
		output = inhibitOut;
	}
private:
	void suppressInput(Level levelPrev){
		//Sensor input
		Data dataIn = data.getData();
		//Previous Layer output
		Data supressIn = levelPrev.dataSuppress;

		/*
		 * Algorithm
		 * Merge to one input data
		 * set layerInput for this layer
		 */

		//TODO Wie am Besten darstellen?
		layerInput = supressIn;
	}
	void handleLayer(){
		/**
		 * Suppress Algorithm
		 * set dataSuppress for lower layer
		 */
		//TODO Wie am Besten darstellen?
		dataSuppress = layerInput;

		/**
		 * Layer Algorithm
		 * use layerInput as input
		 * set inhibitOut as output for inhibitor
		 */
		//TODO Wie am Besten darstellen?
		inhibitOut = layerInput;
	}
	void inhibitOutput(Level levelPrev){
		Data outputPrevLevel = levelPrev.inhibitOut;
		Data outputThis = inhibitOut;

		/**
		 * Algortihm
		 * Merge to one output data
		 * set output for motor
		 */
		//TODO Wie am Besten darstellen?
		output = outputPrevLevel;
	}
};


class Controller{
public:
	Controller(){};
	virtual ~Controller(){};
	void registerLevel(Level *level){
		//Adds the levels to the vector
		levels.push_back(*level);
	}
	void arbitrate(){
		int i = levels.size()-1;
		//Top Level
		levels[i].startLevel();
		//Other levels
		for(i = levels.size()-2; i >= 0; i--){
			levels[i].startLevel(levels[i+1]);
		}
		//Output from the last inhibitor of the lowest level
		motor.setOutput(levels.front().output);
	}
private:
	vector<Level> levels;
	Motor motor;
};

int main() {
	Controller *control = new Controller();
	Level0 *level0 = new Level0();
	Level1 *level1 = new Level1();;
	Level2 *level2 = new Level2();;

	//Level registrieren
	control->registerLevel(level0);
	control->registerLevel(level1);
	control->registerLevel(level2);

	//TODO Condition
	while(1){
		control->arbitrate();
	}

	return 0;
}
