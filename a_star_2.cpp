


#include<iostream>
#include<vector>



// state enum

enum class State {empty,obstacle};
using namespace std;


// open list keeps a recored of some potenatial node to expolore 

// h is optimistic guess of how far are we from the goal

void printState(int i, int j, State state)
{
    cout << i << "," << j << ": ";
    if (state == State::empty)
    {
        cout << "empty" << endl;
    }
    else
    {
        cout << "obstacle" << endl;
    }
}

int main(){

    // create a map
    size_t col = 3;
    size_t row = 3;
    int map_array[col][row] = {{0, 1, 0},
                               {0, 1, 0},
                               {0, 0, 0}};
    vector<vector<State>> grid(row,vector<State>(col,State::empty));
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(map_array[i][j] ==0){
                grid[i][j] = State::empty;
            }else{
                grid[i][j] = State::obstacle;
                printState(i,j,grid[i][j]);
            }
        }
    }

    
}