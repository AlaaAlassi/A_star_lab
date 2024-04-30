#include <iostream>
#include <memory>
#include <vector>

struct Node
{

    Node(unsigned int i, unsigned int j, Node *parent) : i_(i), j_(j),parent_(parent){};
    unsigned int i_;
    unsigned int j_;
    Node *parent_;
};

std::shared_ptr<Node> findNextNode(std::shared_ptr<Node> currentNode, std::vector<Node>& openList, int (&grid)[4][4]){
    grid[currentNode->i_+1][currentNode->j_+1];
}

int main()
{
    // grid
    int grid[4][4] = {{0, 0, 0, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 0},
                      {0, 0, 0, 0}};

    Node startNode(0,0,nullptr);
    Node goalNode (3,3,nullptr);
    bool pathfound = false;
    std::shared_ptr<Node> currentNode = std::make_shared<Node>(startNode.i_,startNode.j_,startNode.parent_) ;
    std::vector<Node> openList={startNode};

    while (!openList.empty() || pathfound)
    {

        auto nextNode = findNextNode(currentNode,openList,grid);
        if((nextNode.i_ == goalNode.i_ )&& (nextNode.j_ == goalNode.j_)){
            pathfound = true;
        }else{
            currentNode = nextNode;
        }

    }

    return 0;
}