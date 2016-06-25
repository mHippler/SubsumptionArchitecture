#include <iostream>
#include <vector>
using namespace std;

class Data{
public:
	Data(){}
	virtual ~Data(){}
	Data getData(){}
};

class Motor{
public:
	Motor(){	}
	virtual ~Motor(){};
	Data motorOutput;
	void setOutput(Data output){
		motorOutput = output;
	}
};

class Level{
	virtual void suppressInput(Level *levelprev) = 0;
	virtual void handleLayer() = 0;
	virtual void inhibitOutput(Level *levelPrev) = 0;
public:
	Level(){}
	virtual ~Level(){}
	Data data;
	Data dataSuppress;
	Data layerInput;
	Data dataInhibit;
	Data output;
	virtual void printLevelNumber() = 0;
	virtual void printLevelNumber(Level *level) = 0;
};

class Level0 : public Level{
public:
	Level0(){}
	virtual ~Level0(){}
	void printLevelNumber(){
		//Get data directly from Data
		layerInput = data.getData();
		handleLayer();
		//Set output directly
		output = dataInhibit;
	}
	void printLevelNumber(Level *level){
		suppressInput(level);
		handleLayer();
		inhibitOutput(level);
	}
	void suppressInput(Level *levelprev){
		//Sensor input
		Data dataIn = data.getData();
		//Previous Layer Suppress output
		Data supressIn = levelprev->dataSuppress;
		/*
		 * Input Algorithm
		 * use as input: dataIn, suressIn
		 * set as output: layerInput
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
		 * us  as input: layerInput
		 * set as output: dataInhibit
		 */
		//TODO Wie am Besten darstellen?
		dataInhibit = layerInput;
	}
	void inhibitOutput(Level *levelPrev){
		//Layer Output
		Data outputLevel = dataInhibit;
		//Previous Layer output
		Data outputPrevLevel = levelPrev->dataInhibit;
		/**
		 * Inhibit Algortihm
		 * use as input: outputLevel, outputPrevLevel
		 * set as output: output
		 */
		//TODO Wie am Besten darstellen?
		output = outputPrevLevel;
	}
};

class Level1 : public Level{
public:
	Level1(){}
	virtual ~Level1(){}
	void printLevelNumber(){
		//Get data directly from Data
		layerInput = data.getData();
		handleLayer();
		//Set output directly
		output = dataInhibit;
	}
	void printLevelNumber(Level *level){
		suppressInput(level);
		handleLayer();
		inhibitOutput(level);
	}
	void suppressInput(Level *levelprev){
		//Sensor input
		Data dataIn = data.getData();
		//Previous Layer Suppress output
		Data supressIn = levelprev->dataSuppress;
		/*
		 * Input Algorithm
		 * use as input: dataIn, suressIn
		 * set as output: layerInput
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
		 * us  as input: layerInput
		 * set as output: dataInhibit
		 */
		//TODO Wie am Besten darstellen?
		dataInhibit = layerInput;
	}
	void inhibitOutput(Level *levelPrev){
		//Layer Output
		Data outputThis = dataInhibit;
		//Previous Layer output
		Data outputPrevLevel = levelPrev->dataInhibit;
		/**
		 * Inhibit Algortihm
		 * use as input: outputLevel, outputPrevLevel
		 * set as output: output
		 */
		//TODO Wie am Besten darstellen?
		output = outputPrevLevel;
	}
};

class Level2 : public Level{
public:
	Level2(){}
	virtual ~Level2(){}
	void printLevelNumber(){
		//Get data directly from Data
		layerInput = data.getData();
		handleLayer();
		//Set output directly
		output = dataInhibit;
	}
	void printLevelNumber(Level *level){
		suppressInput(level);
		handleLayer();
		inhibitOutput(level);
	}
	void suppressInput(Level *levelprev){
		//Sensor input
		Data dataIn = data.getData();
		//Previous Layer Suppress output
		Data supressIn = levelprev->dataSuppress;
		/*
		 * Input Algorithm
		 * use as input: dataIn, suressIn
		 * set as output: layerInput
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
		 * us  as input: layerInput
		 * set as output: dataInhibit
		 */
		//TODO Wie am Besten darstellen?
		dataInhibit = layerInput;
	}
	void inhibitOutput(Level *levelPrev){
		//Layer Output
		Data outputThis = dataInhibit;
		//Previous Layer output
		Data outputPrevLevel = levelPrev->dataInhibit;
		/**
		 * Inhibit Algortihm
		 * use as input: outputLevel, outputPrevLevel
		 * set as output: output
		 */
		//TODO Wie am Besten darstellen?
		output = outputPrevLevel;
	}
};

class Controller{
	vector<Level*> levels;
	Motor motor;
public:
	Controller(){};
	virtual ~Controller(){}
	void registerLevel(Level *level){
		levels.push_back(level);
	}
	void arbitrate(){
		//Top Level (has neither S nor I)
		int i = levels.size()-1;
		levels[i]->printLevelNumber();
		//Other levels
		for(i = levels.size()-2; i >= 0; i--){
			levels[i]->printLevelNumber(levels[i+1]);
		}
		//Set final output
		motor.setOutput(levels.front()->output);
	}
};

int main() {
	//Create Level
	Level0 *level0 = new Level0();
	Level1 *level1 = new Level1();
	Level2 *level2 = new Level2();
	//Create Controller
	Controller *control = new Controller();
	//register Level
	control->registerLevel(level0);
	control->registerLevel(level1);
	control->registerLevel(level2);
	//Start subsumption procedure
	while(1){
		control->arbitrate();
	}
	return 0;
}
