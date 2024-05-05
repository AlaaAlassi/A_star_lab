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

struct Point {
    Point(int i,int j):i_(i),j_(j){};
    int i_ ;
    int j_ ;
    void print(){
        cout << "i:" << i_<< ",j:" << j_ << endl;
    }
};


struct Node
{
    Node(Point coordiates):coordiates_(coordiates){};
    Point coordiates_;
    int g_val = 0;
    int f_val = 0;
    shared_ptr<Node> parent_;
    void setParent(shared_ptr<Node> parent){
        parent_ = parent;
        this->g_val = parent->g_val+1;
    }

    void setFval(int h_val){
         f_val = h_val + g_val;
    }       
    
};


class Planner
{
    Point _start;
    Point _goal;

public:
    Planner(Point start, Point goal,vector<vector<State>> &grid) : _start(start), _goal(goal){
        grid_ = &grid;
        openlist_.push_back(make_shared<Node>(_start));
    };

    vector<shared_ptr<Node>> openlist_;
    vector<vector<State>> * grid_;

    int cal_h(Point b)
    {
        return abs(_goal.i_ - b.i_) + abs(_goal.j_ - b.j_);
    }

        void addToOpenList(shared_ptr<Node> candiadateNode, shared_ptr<Node> parent)
    {
        candiadateNode->setParent(parent);
        auto hval = this->cal_h(candiadateNode->coordiates_);
        candiadateNode->setFval(hval);
        openlist_.push_back(candiadateNode);
    }

    bool isValid(int i, int j)
    {
        if (i >= grid_->size() || j >= grid_[0].size() || i < 0 || j < 0)
        {
            return false;
        }
        if ((*grid_)[i][j] == State::obstacle)
        {
            return false;
        }
        return true;
    }

    void expand(shared_ptr<Node> node)
    {
        uint numOfSteps = 4;
        int steps[numOfSteps][2] = {{1, 0},
                                    {-1, 0},
                                    {0, 1},
                                    {0, -1}};
        for (int i = 0; i < numOfSteps; i++)
        {
            int r_idx = node->coordiates_.i_ + steps[i][0];
            int c_idx = node->coordiates_.j_ + steps[i][1];
            if (isValid(r_idx, c_idx))
            {
                auto candidateNode = std::make_shared<Node>(Point(r_idx, c_idx));

                addToOpenList(candidateNode,node);
                (*grid_)[r_idx][c_idx] = State::obstacle;
            }
        }
    }

};


int main(){

    // create a map
    size_t col = 3;
    size_t row = 3;
    int map_array[col][row] = {{0, 1, 0},
                               {0, 0, 0},
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

    shared_ptr<Node> start = make_shared<Node>(Point(0,0));
    shared_ptr<Node> goal = make_shared<Node>(Point(2,2));

    Planner myPlanner(start->coordiates_,goal->coordiates_,grid);


    while (!myPlanner.openlist_.empty())
    {
        sort(myPlanner.openlist_.begin(), myPlanner.openlist_.end(), [](shared_ptr<Node> a, shared_ptr<Node> b)
             { return a->f_val > b->f_val; });
        shared_ptr <Node> node = myPlanner.openlist_.back();
        myPlanner.openlist_.pop_back();
        if (myPlanner.cal_h(node->coordiates_) == 0)
        {
            cout << "path found" << endl;
            while (node != nullptr)
            {
                cout << node->coordiates_.i_  <<"," <<node->coordiates_.j_ << " node adress " << node << " parent adress "<< node->parent_ << endl;
                node = node->parent_;
                
            }
            
            return 0;
        }
        myPlanner.expand(node);
    }
}