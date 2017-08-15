#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <locale>
#include <cstring>
#include "istring.h"

using namespace std;

/*********** iString **********
 Purpose: Contains nothing. to initialize
 a empty iString. initialize the field
 chars, length, and capacity.
 Returns: NULL
 ***********************************/

iString::iString(){
    this->chars = NULL; //initialize chars is NULL
    this->length = 0;  //lenght is 0
    this->capacity = 0;   //capacity is 0
}

/*********** iString  **********
 Purpose: Contains a string, to copy this to
 a iString chars field.
 Returns: NULL
 ***********************************/

iString::iString(const char *a){
    //if string is empty
    if (a == NULL){
        this->chars = NULL;
        this->length = 0;
        this->capacity = 0;
    } //if
    //if string is not empty
    else{
        this->length = strlen(a); //copy length
        this->chars = new char [this->length + 1]; //new
        strcpy(this->chars, a); //copy string
        this->capacity = this->length + 1 ;
    } //if
}

/*********** iString  **********
 Purpose: do copy constructor
 Returns: NULL
 ***********************************/

iString::iString(const iString &a){
    //if iString chars field is empty
    if (a.chars == NULL){
        this->chars = NULL;
        this->length = 0;
        this->capacity = 0;
    } //if
    //otherwise
    else{
        this->length = a.length; //copy length
        this->chars = new char [this->length + 1]; //new
        strcpy(this->chars, a.chars); //copy chars field
        this->capacity = a.capacity + 1;
    } //if
}

/*********** ~iString  **********
 Purpose: delete iString
 Returns: NULL
 ***********************************/

iString::~iString(){
    delete [ ] this->chars; //delete iString chars field
}

/*********** operator=  **********
 Purpose: do copy assignment operator "="
 Returns: iString chars filed
 ***********************************/

iString &iString::operator=(const iString &other){
    //if iString other is empty
    if (other.chars == NULL){
        //delete the original one chars field
        delete [ ] this->chars;
        this->chars = NULL;
        this->length = 0;
        this->capacity = 0;
        return *this;
    } //if
    // if original one is empty
    else if (this->chars == NULL){
        this->length = other.length;
        this->capacity = other.capacity;
        this->chars = new char [this->length + 1];
        strcpy(this->chars, other.chars);
        return *this;
    } //if
    // if original one is the same as iString other
    else  if (strcmp(this->chars, other.chars) == 0){
        return *this;
    }
    //otherwise
    else{
        //delete original one
        delete [ ] this->chars;
        this->length = other.length; //copy length
        this->chars = new char [this->length + 1]; //new
        strcpy(this->chars, other.chars); //copy string
        this->capacity = other.capacity;
        return *this;
    } //if
}

/*********** operator >>  **********
 Purpose: read a char, then store in a char array,
 then copy to the iString a
 Returns: in
 ***********************************/

istream& operator >> (istream &in, iString &a){
    char c;
    char arr[200];  //initialize a char array with 200 size
    int index = 0;
    //to check if next one is a space
    while(isspace(in.peek())){
        in.ignore();  //then ignore
    } //while
    //otherwise
    while(!isspace (in.peek())){
        in >> arr[index]; //read and store to arr
        index++; //increment index
    } //while
    arr[index] = '\0'; //add string deliminator
    int mylen = strlen(arr);
    delete [ ] a.chars;   //delete
    a.chars = new char [mylen + 1]; //new
    a.length = mylen;  //copy length
    a.capacity = a.length + 1;
    strcpy(a.chars, arr); //copy string
    return in;
}

/*********** operator<<  **********
 Purpose: Contains a iString a, and print
 the chars field
 Returns: out
 ***********************************/

ostream& operator<< (ostream &out, const iString &a){
    int pos = 0;
    while (pos < a.length){
        out << a.chars[pos]; //print chars field
        pos++;
    } //while
    return out;
}

/*********** operator+  **********
 Purpose: to add two iString together.
 Returns: iString
 ***********************************/

iString operator+(const iString &a, const iString &b){
    iString newone; //initialize a new iString
    newone.chars = NULL;
    newone.length = 0;
    newone.capacity = 0;
    //if two iStrings are empty
    if (a.chars == NULL && b.chars == NULL){
        return newone;
    }//if
    //if the first iString is empty
    else if (a.chars == NULL){
        newone.length = b.length; //copy length
        newone.capacity = b.capacity; //copy capacity
        newone.chars = new char [newone.length + 1]; //new
        strcpy(newone.chars, b.chars); //copy string
        return newone;
    } //if
    //if the second one is empty
    else if (b.chars == NULL){
        newone.length = a.length; //copy length
        newone.capacity = a.capacity; //copy capacity
        newone.chars = new char [newone.length + 1]; //new
        strcpy(newone.chars, a.chars); //copy string
        return newone;
    }//if
    //if both are not empty
    else{
        newone.length = a.length + b.length;//plus two length of iStrings
        newone.capacity = a.capacity + b.capacity; //plus two capacity of two iStrings
        newone.chars = new char [newone.length + 1]; //new
    }//if
    strcpy(newone.chars, a.chars); //copy string
    strcat(newone.chars, b.chars); //copy string
    return newone;
}

/*********** operator+  **********
 Purpose: Contains a iStrings, and a string.
 then add them together
 Returns: iString
 ***********************************/

iString operator+(const iString &a, const char *b){
    iString newone;
    newone.chars = NULL;
    newone.length = 0;
    newone.capacity = 0;
    //if two are empty
    if (a.length == 0 && (strlen(b) == 0)){
        return newone;
    }//if
    //if string b is empty
    else if ((int(strlen(b))) == 0){
        newone.length = a.length; //copy length
        newone.capacity = a.capacity; //copy capacity
        newone.chars = new char [newone.length + 1]; //new
        strcpy(newone.chars, a.chars);//copy string
        return newone;
    }//if
    //if iString a is empty
    else if (a.length == 0){
        newone.length = int (strlen(b)); //copy lenght
        newone.capacity = newone.length; //copy capacity
        newone.chars = new char [newone.length + 1]; //new
        strcpy(newone.chars, b); //copy string
        return newone;
    }//if
    //if both are not empty
    else{
        newone.length = a.length + int(strlen(b)); //copy length
        newone.capacity = a.capacity + int(strlen(b)); //copy capacity
        newone.chars = new char [newone.length + 1]; //new
    }//if
    strcpy(newone.chars, a.chars); //copy string
    strcat(newone.chars, b); //copy string
    return newone;
}

/*********** operator+  **********
 Purpose: Contains a string, and a iString a
 then add them together
 Returns: iString
 ***********************************/

iString operator+(const char *a, const iString& b){
    iString newone;
    newone.chars = NULL;
    newone.length = 0;
    newone.capacity = 0;
    // if both are empty
    if (b.length == 0 && (strlen(a) == 0)){
        return newone;
    } //if
    // if string a is empty
    else if ((int(strlen(a))) == 0){
        newone.length = b.length; //copy length
        newone.capacity = b.capacity;
        newone.chars = new char [newone.length + 1]; //new
        strcpy(newone.chars, b.chars); //copy string
        return newone;
    }//if
    //if iString b is empty
    else if (b.length == 0){
        newone.length = int (strlen(a)); //copy length
        newone.capacity = newone.length;  //copy capacity
        newone.chars = new char [newone.length + 1]; //new
        strcpy(newone.chars, a); //copy string
        return newone;
    } //if
    //otherwise
    else{
        newone.length = int(strlen(a)) + b.length; //copy length
        newone.capacity = int(strlen(a)) + b.capacity; //copy capacity
        newone.chars = new char [newone.length + 1]; //new
    }
    strcpy(newone.chars, a); //copy string
    strcat(newone.chars, b.chars); //copy string
    return newone;
}

/*********** operator~  **********
 Purpose: Contains a iString, do the function p,
 then add them together
 Returns: iString
***********************************/

iString operator~(const iString &a){
    //new a iString
    iString newone;
    newone.chars = NULL;
    newone.length = 0;
    newone.capacity = 0;
    //if iString a is empty
    if (a.length == 0){
        return newone;
    } 
    // elsse
    newone.capacity = 10;
    newone.chars = new char [newone.capacity];
    int index = 0;
    int pos = 0;
    while(index < a.length){
        //loop to control
        int i = 0;
        while (i <= index){
            //loop to control
            if (newone.length >= newone.capacity){
                newone.capacity = newone.capacity * 2; //resize capacity
                char *p = new char [newone.capacity];
                int k = 0;
	  	while(k < newone.length){
			//loop to copying
			p[k] = newone.chars[k];
			k++;
		}//while
                delete [ ] newone.chars; //delete the origin
 		newone.chars = p; //copy & paste
            } //if
            newone.chars[pos] = a.chars[i];
            i++;
            pos++;
            newone.length++;
        } //while
        index++;
    } //while
    return newone;
}
