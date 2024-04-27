#include <iostream>
#include <stdlib.h>
#include <queue>
using namespace std;

class Node
{
public:
    Node *left, *right;
    int data;

public:
    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class Tree
{
public:
    Node *insertNode(Node *, int);
};

Node *Tree::insertNode(Node *root, int data)
{
    if (root == nullptr)
    {
        return new Node(data);
    }

    if (data < root->data)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        root->right = insertNode(root->right, data);
    }

    return root;
}
void BFS(Node *root)
{
    queue<Node *> q;
    q.push(root);
    int size;
    while (!q.empty())
    {
        size = q.size();
    #pragma omp parallel for
        for (int i = 0; i < size; i++)
        {
            Node *currNode;
            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << currNode->data << " ";
            }
            if (currNode->left)
            {
            #pragma omp critical
                {
                    q.push(currNode->left);
                }
            }

            if (currNode->right)
            {
                #pragma omp critical
                {
                    q.push(currNode->right);
                }
            }
        }
    }
}
void parallel_dfs(Node* root) {
    if (root == NULL) return;

    printf("%d ", root->data);

    // Parallelize the traversal of left and right subtrees
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            parallel_dfs(root->left);
        }

        #pragma omp section
        {
            parallel_dfs(root->right);
        }
    }
}
void DFS(Node *root){
    if (root == nullptr) return;

    stack<Node*> stack;
    stack.push(root);

    #pragma omp parallel
    {
        while (!stack.empty()) {
            Node* current = nullptr;
            
            #pragma omp critical
            {
                if (!stack.empty()) {
                    current = stack.top();
                    stack.pop();
                }
            }
            
            if (current != nullptr) {
                std::cout << current->data << " ";
                if (current->right != nullptr) {
                    #pragma omp critical
                    {
                        stack.push(current->right);
                    }
                }
                if (current->left != nullptr) {
                    #pragma omp critical
                    {
                        stack.push(current->left);
                    }
                }
            }
        }
    }
}
int main()
{
    Node *root = NULL;
    Tree tree;
    int noOfNodes;
    int nodeData;
    cout << "Enter number of nodes : ";
    cin >> noOfNodes;
    for (int i = 0; i < noOfNodes; i++)
    {
        cout << "Enter node data : ";
        cin >> nodeData;
        root = tree.insertNode(root, nodeData);
    }
    BFS(root);
}