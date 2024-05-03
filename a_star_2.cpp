#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<memory>

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

struct Node_base
{
    int goal_i= 0 ;

};

struct Node
{
    Node(int i,int j, Node* parent):i_(i),j_(j),parent_(parent){};
    int i_,j_;
    bool visited = false;
    int h_val = 1000;
    int g_val = 0;
    int f_val = 1000;
    Node *parent_;
    void cal_h(Node goal){
        h_val = abs(goal.i_ - this->i_) + abs(goal.j_ - this->j_);
    }
    void cal_f(Node goal){
        cal_h(goal);
        if(parent_ == nullptr) 
            f_val = h_val;
        else{
            f_val = h_val + parent_->g_val+1;
            }
    }
};

bool isValid(int i, int j, vector<vector<State>> &grid)
{
    if (i >= grid.size() || j >= grid[0].size() || i < 0 || j < 0)
    {
        return false;
    }
    if (grid[i][j] == State::obstacle)
    {
        return false;
    }
    return true;
}

void expand(Node goal,Node &node, vector<Node> &openlist, vector<vector<State>> &grid)
{
    uint numOfSteps = 4;
    int steps[numOfSteps][2] = {{ 1,  0},
                       {-1,  0},
                       { 0,  1},
                       { 0, -1}};
    for(int i = 0; i< numOfSteps;i++){
        int r_idx = node.i_ + steps[i][0];
        int c_idx = node.j_ + steps[i][1];
        if(isValid(r_idx,c_idx,grid)){
             Node* parentPtr = new Node(node.i_, node.j_, node.parent_);
            openlist.emplace_back(r_idx,c_idx,parentPtr);
            openlist.back().cal_h(goal);
            openlist.back().cal_f(goal);
            openlist.back().visited = true;
            grid[r_idx][c_idx] = State::obstacle;

        }
    }
}

int main(){

    // create a map
    size_t col = 3;
    size_t row = 3;
    int map_array[col][row] = {{0, 0, 0},
                               {1, 1, 0},
                               {0, 1, 0}};
    vector<vector<State>> grid(row,vector<State>(col,State::empty));
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            if(map_array[i][j] ==0){
                grid[i][j] = State::empty;
            }else{
                grid[i][j] = State::obstacle;
            }
        }
    }

    Node start(0,0,nullptr);
    Node goal(2,2,nullptr);

    start.cal_f(goal);

    vector<Node> openlist = {start};

    vector<Node> path;

    while (!openlist.empty())
    {
        sort(openlist.begin(), openlist.end(), [](const Node &a, const Node &b)
             { return a.f_val > b.f_val; });
        Node node = openlist.back();
        openlist.pop_back();
        if (node.h_val == 0)
        {
            cout << "path found" << endl;
            Node *curreNode = &node;
            while(curreNode != nullptr)
            {
                cout << curreNode->i_ << " " << curreNode->j_ << " " << curreNode << " parent " << curreNode->parent_ << endl;
                curreNode = curreNode->parent_;
            }
            return 0;
        }
        expand(goal, node, openlist, grid);
    }
}