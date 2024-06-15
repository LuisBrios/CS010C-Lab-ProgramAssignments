#pragma once

//Template to allow a user to input any type of value into their choice of vector.
template <typename T> 
class stack{
    public:
        //Creates an array of type T(selected by user) with a max size of 20. 
        stack(){ 
            data = new T[MAX_SIZE]; 
        }
        //Deletes the array at the end of the code, as well as resets the pointer to null.
        ~stack(){
            delete[] data; 
            data = nullptr; 
        }
        //Pushes any value prompted by the user into the 0th index of an array. Before insertion, it moves every index up by one so that the new
        //value does not override any existing data. The size is increased to monitor if the array gets above the max size or not. If so, 
        //the function throws an exception to indicate that the stack has already reached its maximy
        void push(T val){
            if(size >= MAX_SIZE){
                throw overflow_error("Called push on full stack.");
            }
            for (int i = size; i > 0; --i){
                data[i] = data[i-1];
            }
            data[0] = val;
            ++size;  
        }
        //Removes the value of the 0th index by replacing it with the following index. This function calls an exception if there is nothing
        //to be removed in the stack. 
        void pop(){
            if (empty()){
                throw out_of_range("Called pop on empty stack.");
            }
            for (int i = 0; i < size; ++i){
                data[i] = data[i+1];
            }
            --size; 
        }
        //Removes the value of the 0th index and the 1st index by replacing them with the indexes that are 2 elements in front of them.
        //This function calls an exception if there is one element or less in the stack. 
        void pop_two(){
            if (empty()){
                throw out_of_range("Called pop_two on empty stack.");
            }
            if (size == 1){
                throw out_of_range("Called pop_two on a stack of size 1.");
            }
            for (int i = 0; i < (size-1); ++i){
                data[i] = data[i+2]; 
            }
            size -= 2; 
        } 
        //Returns the value at the top of the stack, only if it is not empty. Otherwise, an exception is made. 
        const T& top(){
            if (empty()){
                throw underflow_error("Called top on empty stack.");
            }
            return data[0];
        }
        //Checks the size of the array and returns whether or not the size is 0. 
        const bool empty(){
            if (size == 0){
                return true;
            }
            return false; 
        }
    private:
        //A pointer for the array; works for user's type. 
        T* data; 
        //Size keeps the length of the array in check; usually used to make sure it does not exceed the max size. 
        int size = 0;
        int MAX_SIZE = 20; 
};