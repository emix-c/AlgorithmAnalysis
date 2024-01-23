#include <iostream> 
#include <unordered_map> 
#include <vector>
#include <fstream> 
#include<string>
using namespace std; 

int hashf(const string &key, int tableSize){ //hash function to convert string to ASCII values and then to hash value
	int value = 0; 
	for (int i = 0; i < key.length(); i++){
		value += key[i]; }
	return value % tableSize; 
}

int quadraticprob(const string&key, int tableSize, vector<string>* HashTable){ //for quadratic probing
	int sum; 
	int newindex; 
	int value = 0; 
	for (int i = 0; i < key.length(); i++){
		value += key[i];}
	

		for (int x=1; x<20; x++){ //need to find an open index in hash table
			sum=value + (x * x); 
			newindex=sum % tableSize; 
			if ((*HashTable)[newindex]=="empty"){ //check if the new index is empty
	
				break; }
			
		}
	return newindex; //return new index for element to be assigned 
	}


bool isPrime(int x){ //need to check if number is prime
    if (x <= 1) //0 and 1 are not prime
        return false;
 
    for (int i = 2; i < x; i++) //check if remainder exists b/c prime numbers can only be divided by 1
        if (x % i == 0)
            return false;
 
    return true;
}



int rehash (vector<string>* HashTable){

	int original=HashTable->size(); 

	int number=original *2; //take original hashtable size and double it 
	
	while (!isPrime(number)){ //add the number by 1 until the new table size is prime 
		number++; 
	}

	string word="empty"; 

	(HashTable)->resize(number);  //now resize 

	for (int x=original; x<(HashTable)->size(); x++){
		(*HashTable)[x]= word; //lots of empty indexes, let's fill it with "empty" so it's consistent 
	}


	


	return number; //return new table size 


}



int main(){ 

   int tablesize=31; //original size of hashtable 

   int loadf=tablesize/2; //loadfactor >=0.5 will require rehashing 

    vector<string> HashTable (tablesize, "empty"); //this is HashTable
	vector<string> words; //stores 20 words

	words.push_back("hello"); 
	words.push_back("weirdo"); 
	words.push_back("burger"); 
	words.push_back("food"); 
	words.push_back("linguini"); 
	words.push_back("mail"); 
	words.push_back("coding"); 
	words.push_back("laptop"); 
	words.push_back("MONItor");
	words.push_back("bEar");  
	words.push_back("aim high"); 
	words.push_back("go up"); 
	words.push_back("huMBle"); 
	words.push_back("bABE"); 
	words.push_back("matthEW"); 
	words.push_back("babW"); 
	words.push_back("poOhBEAr"); 
	words.push_back("shOOky"); 
	words.push_back("mickeyy"); 
	words.push_back("cAEli"); 



	int counter=0; //count how many words are inserted into hash table so that i know when rehashing is needed 
	int initialcollisions=0; //counting collisions for intiial hashtable 

	for (int x=0; x<words.size(); x++){
		if (loadf==counter){ //if half of the tablesize has been added in, load factor=0.5 so let's rehash 
			tablesize=rehash(&HashTable); //table size is updated! 
			cout << "Table has been rehashed."<<endl; 
			break; 
		}
		int index=hashf(words[x], tablesize); //for each word find index using hash function 
		if (HashTable[index]=="empty"){ //if the index is empty, can just fill it in with word
			HashTable[index]=words[x]; 
		}
		else { //if not, there is a collision 
			initialcollisions++; 
			int newindex=quadraticprob(words[x], tablesize, &HashTable); //calculate new index using quadratic probing 
			HashTable[newindex]=words[x]; //now assign the word to the new index 
			cout << "Collision fixed"<<endl; 
		}
		counter++; 
	}

	//now hash table has to start over b/c it's been rehashed 

	vector<string> Temp (tablesize, "empty"); //will store words that will be displaced during rehashing 

	//iterate through hash table and find the words that are already there and rehash them 

	for (int x=0; x<HashTable.size(); x++){
		if (HashTable[x]!="empty"){ //there is a word present at the index 
			string word=HashTable[x]; 
			HashTable[x]="empty"; //empty that index
			int index=hashf(word, tablesize); //find the new index of that word 
			if (HashTable[index]!="empty"){ //BUT if new index already has a word, store the word it has in temp vector for access later
				Temp[index]=HashTable[index]; 
				HashTable[index]=word; //now the word can be asssigned to its new index 
			}
			else{ //if new index is empty, just assign word there
				HashTable[index]=word;
			}

		}
	}

	int postcollisions=0; //counting collisions that occur after rehashing table 

	for (int x=0; x<Temp.size(); x++){ //now we look at temp vector which contains words that were recently displaced due to the rehashing
		if (Temp[x]!="empty"){ 
			string word=Temp[x]; 
			int index=hashf(word, tablesize); //find the new index for the word 
			if (HashTable[index]=="empty"){ //assign it to its new index if the index is open
				HashTable[index]=word; 
			}
			else { //if not, there's a collision and perform quadratic probing to find open index
				postcollisions++; 
				int newindex=quadraticprob(word, tablesize, &HashTable); 
				HashTable[newindex]=word; 
				cout << "Collision fixed"<<endl; 
			}
	}

}

	//now let's put in the remaining words that hadn't been hashed at all in our newly hashed table 
	for (int x=counter; x<words.size(); x++){ //start from counter, cause that's where previous hashing stopped
		int index=hashf(words[x], tablesize); 
		if (HashTable[index]=="empty"){ //if index is empty, assign word there 
			HashTable[index]= words[x]; 
		}
		else { //if not, it's another collision 
			postcollisions++;
			int newindex=quadraticprob(words[x], tablesize, &HashTable); 
			HashTable[newindex]=words[x]; 
			cout << "Collision fixed"<<endl; 
			}
	}

		
		
	//output of finished HashTable 
	/*for (int x=0; x<HashTable.size(); x++){ 
		cout << HashTable[x]<<endl; 
	}*/ 
	
	cout << "Collisions that Occurred at First Hashing: "<<initialcollisions<<endl; 
	cout <<"Collisions After Rehashing: "<< postcollisions<<endl; 
	cout << "Total Collisions: "<<initialcollisions+postcollisions<<endl; 
	









}