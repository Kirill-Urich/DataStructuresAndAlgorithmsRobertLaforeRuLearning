// classDataArray.cpp
// Объекты как элементы данных

#include <iostream>
using namespace std;

class Person {
    private:
        string lastName;
        string firstName;
        int age;
    public:
        Person(string last, string first, int a) {
            lastName = last;
            firstName = first;
            age = a;
        }
        void displayPerson() {
            cout << "Last name: " << lastName;
            cout << ". First name: " << firstName;
            cout << ". Age: " << age << endl;
        }
        string getLast() {
            return lastName;
        }
        bool operator==(Person p) {
            return lastName == p.lastName 
                && firstName == p.firstName
                && age == p.age; 
        }
        bool operator!=(Person p) {
            return lastName != p.lastName 
                || firstName != p.firstName
                || age != p.age; 
        }
};

class ClassDataArray {
    private:
        Person** a;
        int nElems;
    public:
        ClassDataArray(int max) {
            a = new Person*[max];
            nElems = 0;
        }
        Person* find(string searchName) {
            int j;
            for (j = 0; j < nElems; j++)
                if (a[j]->getLast() == searchName)
                    break;
            if (j == nElems)
                return nullptr;
            else
                return a[j];
        }
        void insert(string last, string first, int age) {
            a[nElems] = new Person(last, first, age);
            nElems++;
        }
        bool Delete(string searchName) {
            int j;
            for (j = 0; j < nElems; j++)
                if (a[j]->getLast() == searchName)
                    break;
            if (j == nElems)
                return false;
            else {
                for (int k = j; k < nElems; k++)
                    a[k] = a[k + 1];
                nElems--;
                return true;
            }
        }
        void displayA() {
            for (int j = 0; j < nElems; j++)
                a[j]->displayPerson();
        }
};

class ClassDataApp {
    public:
        static void main() {
            int maxSize = 100;
            ClassDataArray arr(maxSize);

            arr.insert("Evans", "Patty", 24);
            arr.insert("Smith", "Lorraine", 37);
            arr.insert("Yee", "Tom", 43);
            arr.insert("Adams", "Henry", 63);
            arr.insert("Hashimoto", "Sato", 21);
            arr.insert("Stimson", "Henry", 29);
            arr.insert("Velasquez", "Jose", 72);
            arr.insert("Lamarque", "Henry", 54);
            arr.insert("Vang", "Minh", 22);
            arr.insert("Creswell", "Lucinda", 18);

            arr.displayA();

            string searchKey = "Stimson";
            Person* found = arr.find(searchKey);
            // Person null_person = Person("N/A", "N/A", 0);
            if (found != nullptr) {
                cout << "Found ";
                found->displayPerson();
            }
            else
                cout << "Can't find " << searchKey << endl;
            
            cout << "Deleting Smith. Yee. and Creswell" << endl;
            arr.Delete("Smith");
            arr.Delete("Yee");
            arr.Delete("Creswell");

            arr.displayA();
        }
};

int main() {
    ClassDataApp::main();
    return 0;
}