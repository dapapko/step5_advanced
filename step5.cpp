#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class CoffeeMachine
{
    int pressure; // pressure of pump
    int temperature; // temperature (used for "warming" method)
    string colour; // colour of an instance
    int numberOfCups; // number of cups (usually 1 or 2)
    bool canMakeCappuccino; // an instance can make cappuccino or not
    int price; // price of a machine
    string model; // Model of a machine (ex.: Vitek VT-1525)
    fstream file;

    void file_to_map(string filename, map<string, string>& data, string delim) {
        file.open(filename);
        if (file.is_open()) {
            cout << "Initialization from file" << endl;
            // Initialize object using data from file
            string row;
            int j = 0;
            while (getline(file, row) && j < 7) {
                j++;
                size_t delim_pos = row.find(delim);
                string key = row.substr(0, delim_pos);
                string value = row.substr(delim_pos + 1);
                data[key] = value;
            }
        }
    }
    // Warming the machine
    void warm(int temp) {
        while(temperature < temp) {
            temperature++;
            cout << "Warming. Current temperature is " << temperature << endl;
        }
    }


    int static getValue(map<string, string>& data, string key, int def) {
        try {
            return stoi(data[key]);
        }  catch (invalid_argument) {
            return def;
        }
    }


public:
    // Make a cup of coffee
    void makeEspresso(bool hot = false) {
        cout << "Process of making coffee started" << endl;
        warm(hot ? 120 : 100);
        // It's just a notification to show how to use fields of class
        if (!canMakeCappuccino) cout << "Attention. This instance can't make cappuccino" << endl;
        cout << "Activating pump" << endl;
        cout << "Deactivating pump" << endl;
        cout << "Your drink is ready" << endl;
    }
    // Definition of a friendly operator function.
    friend ostream &operator<<( ostream &output, const CoffeeMachine& machine );

    ~CoffeeMachine() {
        if (file.is_open()) file.close();
    }

    // Default constructor
    CoffeeMachine(string filename = "coffee.txt", string delim = ":")// default constructor with arguments
    {
        map<string, string> data{{"pressure",        "15"},
                            {"temperature",       "25"},
                            {"colour",      "red"},
                            {"numberOfCups",      "3"},
                            {"canMakeCappuccino", "true"},
                            {"price",   "3500"},
                            {"model", "Vitek VT-1525"}};
        file_to_map(filename, data, delim);
        pressure = getValue(data, "pressure", 15);
        temperature = getValue(data, "temperature", 25);
        price = getValue(data, "price", 3500);
        numberOfCups = getValue(data, "numberOfCups", 3);
        canMakeCappuccino = data["canMakeCappuccino"] == "true";
        model = data["model"];
        colour = data["colour"];
    }

    // Copying constructor
    CoffeeMachine(const CoffeeMachine& instance):
            pressure(instance.pressure), temperature(instance.temperature),
            colour(instance.colour), numberOfCups(instance.numberOfCups),
            canMakeCappuccino(instance.canMakeCappuccino), price(instance.price),
            model(instance.model)
    {

    }

};

// Friendly operator function
ostream &operator<<(ostream &output, const CoffeeMachine &machine) {
    output << "Pressure: " << machine.pressure << endl;
    output << "Temperature: " << machine.pressure << endl;
    output << "Colour: " << machine.pressure << endl;
    output << "Number of cups: " << machine.numberOfCups << endl;
    output << "Price: " << machine.price << endl;
    output << "Model: " << machine.model << endl;
    output << (machine.canMakeCappuccino ? "This instance can make cappuccino" : "This instance can't make cappuccino" ) << endl;
    return output;
}


int main() {
    // Calling default constructor
   CoffeeMachine machine("coffee.txt", "|");
   // Visualization
   cout << machine;
   // Call copying constructor
   CoffeeMachine machine2 = machine;
   // Calling public method
   machine.makeEspresso(true);
}