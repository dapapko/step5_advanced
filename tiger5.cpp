#include <string>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Tiger
{
    int age; // Age of tiger
    int size; // Size of tiger (in metres)
    int speed; // Speed of tiger (metres per second)
    string breed; // Breed (Bengal, Amur or smth like that)
    string skinColour; // Colour of skin (black, white or orange)
    bool isHungry; // A tiger can be hungry or not
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
    // running
    void run(int t_speed) {
        speed = t_speed;
        cout << "The tiger is running. Speed: " << t_speed << endl;
    }

public:
    // Friendly operator function for output. Definition.
    friend ostream &operator<<( ostream &output, const Tiger& T );
    // hunting
    void hunt(int t_speed = 30) {
        if (!isHungry) cout << "Tiger is not hungry, so he don't hunt" << endl;
        else {
            if (age <2) cout << "Tiger is hungry, he makes known about it tigress" << endl;
            else {
                cout << "Tiger is hungry, it begins to hunt." << endl;
                run(t_speed);
            }
        }
    }

    ~Tiger() {
        if (file.is_open()) file.close();
    }

    // Default constructor
    Tiger(string filename = "coffee.txt", string delim = ":")// default constructor with arguments
    {
        map<string, string> data{{"age",        "5"},
                            {"size",       "19"},
                            {"speed",      "0"},
                            {"breed",      "amur"},
                            {"skinColour", "white"},
                            {"isHungry",   "0"}};
        file_to_map(filename, data, delim);
        try { age = stoi(data["age"]); }  catch (invalid_argument) {age = 10;}
        try { speed = stoi(data["speed"]); }  catch (invalid_argument) {speed = 5;}
        try { size = stoi(data["size"]); }  catch (invalid_argument) {size = 20;}
        isHungry = data["isHungry"] == "1";
        skinColour = data["skinColour"];
        breed = data["breed"];

    }

    // copying constructor
    Tiger(Tiger const &instance):
            age(instance.age), size(instance.size),
            speed(instance.speed), breed(instance.breed),
            skinColour(instance.skinColour), isHungry(instance.isHungry)
    {}
};

// Friendly operator function for output. Implementation.
ostream &operator<<( ostream &output, const Tiger& T ) {
    output << "Breed: " << T.breed << endl;
    output << "Colour of skin: " << T.skinColour << endl;
    output << "Age: " << T.age << endl;
    output << "Speed: " << T.speed << endl;
    output << "Size: " << T.size << endl;
    output << (T.isHungry ? "The tiger is hungry" : "The tiger is not hungry") << endl;
    return output;
}


int main() {
    // Calling default constructor
    Tiger t1("tiger.txt");
    t1.hunt();
    // Tiger t2 is a copy of t1
    Tiger t2 = t1;
    // Visualization
    cout << t1 << endl;
    cout << t2;
    // Calling method of the class
    t1.hunt(50);
}