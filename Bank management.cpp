#include <iostream>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

class Person {
protected:
    string firstName;
    string lastName;
    int id;
public:
    Person(string firstName, string lastName, int identification) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->id = identification;
    }
    void printPerson() {
        cout << "Name: " << lastName << ", " << firstName << "\nID: " << id << "\n";
    }
};

class Student : public Person {
private:
    vector<int> testScores;

public:
    // Constructor initializes base class (Person) and sets testScores
    Student(string firstName, string lastName, int idNumber, vector<int> scores)
        : Person(firstName, lastName, idNumber), testScores(scores) {}

    // Method to calculate average and return letter grade
    char calculate() {
        if (testScores.empty()) return 'T';

        int sum = 0;
        for (int score : testScores) {
            sum += score;
        }

        int average = sum / testScores.size();

        if (average >= 90 && average <= 100) return 'O';
        if (average >= 80) return 'E';
        if (average >= 70) return 'A';
        if (average >= 55) return 'P';
        if (average >= 40) return 'D';
        return 'T';
    }
};

int main() {
    string firstName, lastName;
    int id, numScores;
    
    cin >> firstName >> lastName >> id >> numScores;
    vector<int> scores(numScores);
    
    for (int i = 0; i < numScores; i++) {
        cin >> scores[i];
    }
    
    Student* s = new Student(firstName, lastName, id, scores);
    s->printPerson();
    cout << "Grade: " << s->calculate() << endl;
    
    delete s;
    return 0;
}