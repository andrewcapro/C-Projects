/*******************************************************************************
 * Filename: waterjugpuzzle.cpp
 * Author  : Andrew Capro
 * Version : 1.0
 * Date    : February 28, 2022
 * Description : Completes the water jug puzzle for any possible initial and final states
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

State pour(State s, int step, const int capacities[]){
    if (step == 1){
        int Atemp = s.a;
        s.a += s.c;
        if(s.a > capacities[0]){
            s.a = capacities[0];
            s.c -= capacities[0] - Atemp;
            if(capacities[0] - Atemp == 1){
                s.directions += "Pour " + to_string(capacities[0] - Atemp) + " gallon from C to A. " + s.to_string() + '\n';
            }
            else{
                s.directions += "Pour " + to_string(capacities[0] - Atemp) + " gallons from C to A. " + s.to_string() + '\n';
            }
        }
        else{
            int Ctemp = s.c;
            s.c = 0;
            if(Ctemp == 1){
                s.directions += "Pour " + to_string(Ctemp) + " gallon from C to A. " + s.to_string() + '\n';
            }
            else{
                s.directions += "Pour " + to_string(Ctemp) + " gallons from C to A. " + s.to_string() + '\n';
            }
        }
    }

    else if (step == 2){
    int Atemp = s.a;
    s.a += s.b;
    if(s.a > capacities[0]){
        s.a = capacities[0];
        s.b -= capacities[0] - Atemp;
        if(capacities[0] - Atemp == 1){
            s.directions += "Pour " + to_string(capacities[0] - Atemp) + " gallon from B to A. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(capacities[0] - Atemp) + " gallons from B to A. " + s.to_string() + '\n';
        }
    }
    else{
        int Btemp = s.b;
        s.b = 0;
        if(Btemp == 1){
            s.directions += "Pour " + to_string(Btemp) + " gallon from B to A. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(Btemp) + " gallons from B to A. " + s.to_string() + '\n';
            }
        }
    }

    else if (step == 3){
    int Btemp = s.b;
    s.b += s.c;
    if(s.b > capacities[1]){
        s.b = capacities[1];
        s.c -= capacities[1] - Btemp;
        if(capacities[1] - Btemp == 1){
            s.directions += "Pour " + to_string(capacities[1] - Btemp) + " gallon from C to B. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(capacities[1] - Btemp) + " gallons from C to B. " + s.to_string() + '\n';
        }
    }
    else{
        int Ctemp = s.c;
        s.c = 0;
        if(Ctemp == 1){
            s.directions += "Pour " + to_string(Ctemp) + " gallon from C to B. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(Ctemp) + " gallons from C to B. " + s.to_string() + '\n';
            }
        }   
    }

    else if (step == 4){
    int Btemp = s.b;
    s.b += s.a;
    if(s.b > capacities[1]){
        s.b = capacities[1];
        s.a -= capacities[1] - Btemp;
        if(capacities[1] - Btemp == 1){
            s.directions += "Pour " + to_string(capacities[1] - Btemp) + " gallon from A to B. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(capacities[1] - Btemp) + " gallons from A to B. " + s.to_string() + '\n';
        }
    }
    else{
        int Atemp = s.a;
        s.a = 0;
        if(Atemp == 1){
            s.directions += "Pour " + to_string(Atemp) + " gallon from A to B. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(Atemp) + " gallons from A to B. " + s.to_string() + '\n';
            }
        }
    }

    else if (step == 5){
    int Ctemp = s.c;
    s.c += s.b;
    if(s.c > capacities[2]){
        s.c = capacities[2];
        s.b -= capacities[2] - Ctemp;
        if(capacities[2] - Ctemp == 1){
            s.directions += "Pour " + to_string(capacities[2] - Ctemp) + " gallon from B to C. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(capacities[2] - Ctemp) + " gallons from B to C. " + s.to_string() + '\n';
        }
    }
    else{
        int Btemp = s.b;
        s.b = 0;
        if(Btemp == 1){
            s.directions += "Pour " + to_string(Btemp) + " gallon from B to C. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(Btemp) + " gallons from B to C. " + s.to_string() + '\n';
            }
        }
    }

    else if (step == 6){
    int Ctemp = s.c;
    s.c += s.a;
    if(s.c > capacities[2]){
        s.c = capacities[2];
        s.a -= capacities[2] - Ctemp;
        if(capacities[2] - Ctemp == 1){
            s.directions += "Pour " + to_string(capacities[2] - Ctemp) + " gallon from A to C. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(capacities[2] - Ctemp) + " gallons from A to C. " + s.to_string() + '\n';
        }
    }
    else{
        int Atemp = s.a;
        s.a = 0;
        if(Atemp == 1){
            s.directions += "Pour " + to_string(Atemp) + " gallon from A to C. " + s.to_string() + '\n';
        }
        else{
            s.directions += "Pour " + to_string(Atemp) + " gallons from A to C. " + s.to_string() + '\n';
            }
        }
    }
    return s;
}

string algorithm(State &s, int step, const int capacities[], const int goals[]){
    queue<State> q;
    //add new state(a,b,c) to queue
    q.push(s);

        bool **array = new bool*[capacities[1] + 1];
    for(int i = 0; i < capacities[1] + 1; i++){
        array[i] = new bool[capacities[0] + 1];
        fill(array[i], array[i] + capacities[0] + 1, false);
    }
    while (!q.empty()){
        State curr = q.front();
        q.pop();
        if (curr.a == goals[0] && curr.b == goals[1] && curr.c == goals[2]){
            for(int i = 0; i < capacities[1] + 1; i++){
        delete [] array[i];
    }
    delete [] array;
            return curr.directions;
        }
        if (array[curr.b][curr.a] == true){
            continue;
        }
        array[curr.b][curr.a] = true;
        for(int i = 0; i <= 6; i++){
            q.push(pour(curr, i, capacities));
        }
    }
    for(int i = 0; i < capacities[1] + 1; i++){
        delete [] array[i];
    }
    delete [] array;
    string fail = "No solution.";
    return fail;
}

int main(int argc, char * const argv[]) {
    /*State s(0, 0, 8, "Initial state.");
    cout << s.to_string() << endl;
    s.a += 3;
    s.c -= 3;
    cout << s.to_string() << endl;
    return 0;*/

    int Acap, Bcap, Ccap, Agoal, Bgoal, Cgoal;

    istringstream iss;
    ostringstream oss;

    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    iss.str(argv[1]);
    oss << argv[1];
    if(!(iss >> Acap) || Acap <= 0){
        cerr << "Error: Invalid capacity '" << oss.str() << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[2]);
    oss << argv[2];

    if(!(iss >> Bcap) || Bcap <= 0){
        cerr << "Error: Invalid capacity '" << oss.str() << "' for jug B." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[3]);
    oss << argv[3];

    if(!(iss >> Ccap) || Ccap <= 0){
        cerr << "Error: Invalid capacity '" << oss.str() << "' for jug C." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[4]);
    oss << argv[4];

    if(!(iss >> Agoal) || Agoal < 0){
        cerr << "Error: Invalid goal '" << oss.str() << "' for jug A." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[5]);
    oss << argv[5];

    if(!(iss >> Bgoal) || Bgoal < 0){
        cerr << "Error: Invalid goal '" << oss.str() << "' for jug B." << endl;
        return 1;
    }
    iss.clear();
    oss.str("");

    iss.str(argv[6]);
    oss << argv[6];

    if(!(iss >> Cgoal) || Cgoal < 0){
        cerr << "Error: Invalid goal '" << oss.str() << "' for jug C." << endl;
        return 1;
    }
    oss.str("");
    iss.clear();

    if (Agoal > Acap){
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if (Bgoal > Bcap){
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if (Cgoal > Ccap){
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }

    if((Agoal + Bgoal + Cgoal) != Ccap){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }



    int capacities[3] = {Acap, Bcap, Ccap};
    int goals[3] = {Agoal, Bgoal, Cgoal};
    string directions = "Initial state. (0, 0, " + to_string(Ccap) + ")\n";
    State initial(0,0,Ccap,directions);
    cout << algorithm(initial,1,capacities,goals);
}
