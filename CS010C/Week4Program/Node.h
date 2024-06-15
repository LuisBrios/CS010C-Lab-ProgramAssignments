#pragma once

//Class made to initialize necessary functions and data for an individual node. 
class Node{
    public:
        Node()
            :nodeData("None"),
             nodeNum(0),
             left(nullptr),
             right(nullptr)
            {
            }

        Node(const string& nodeName)
            :nodeData(nodeName),
             nodeNum(1),
             left(nullptr),
             right(nullptr)
            {
            }
            
        void SetLeft(Node* nextNode){
            left = nextNode; 
        } 

        void SetRight(Node* nextNode){
            right = nextNode; 
        } 

        void SetData(const string& nodeVal){
            nodeData = nodeVal; 
        }
        
        void SetNum(const int& nodeAmnt){
            nodeNum = nodeAmnt;
        }

        void IncNum(){
            ++nodeNum; 
        }

        void DecNum(){
            --nodeNum; 
        }

        const int& GetNum() const {
            return nodeNum; 
        }

        const string& GetData() const {
            return nodeData; 
        }

        const Node* GetLeft() const {
            return left; 
        }

        const Node* GetRight() const {
            return right; 
        }

        Node* GetLeft() {
            return left; 
        }

        Node* GetRight() {
            return right; 
        }

    private:
        string nodeData;
        int nodeNum;  
        Node* left;
        Node* right; 
};