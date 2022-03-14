#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person {
public:
  
  Person(string name, const string profession)
    : Name(name), Profession(profession) {}
  
  virtual void Walk(string destination) = 0;
  string GetProfession() {
    return Profession;
  }
  string GetName() {
    return Name;
  }
  
protected:
  string Name;
  const string Profession;
};

class Student : public Person {
public:
  
  Student(string name, string favouriteSong)
    : Person(name, "Student"), FavouriteSong(favouriteSong) {}
  
  void Learn() {
    cout << Profession << ": " << Name << " learns" << endl;
  }
  
  void Walk(string destination) override {
    cout << Profession << ": " << Name
      << " walks to: " << destination << endl;
    SingSong();
  }
  
  void SingSong() {
    cout << Profession << ": " << Name
      << " sings a song: " << FavouriteSong << endl;
  }

private:
  string FavouriteSong;
};


class Teacher : public Person {
public:
  
  Teacher(string name, string subject)
    : Person(name, "Teacher"), Subject(subject) {}
  
  void Teach() {
    cout << Profession << ": " << Name << " teaches: " << Subject << endl;
  }
  
  void Walk(string destination) override {
    cout << Profession << ": " << Name << " walks to: " << destination << endl;
  }

private:
  string Subject;
};


class Policeman : public Person {
public:
  Policeman(string name)
    : Person(name, "Policeman") {}
  
  void Check(Person& p) {
    cout << Profession << ": " << Name
      << " checks " << p.GetProfession() << ". "
      << p.GetProfession() << "'s name is: " << p.GetName() << endl;
  }
  
  void Walk(string destination) override {
    cout << Profession << ": " << Name << " walks to: " << destination << endl;
  }
};

void VisitPlaces(Person& person, vector<string> places) {
  for (const auto& p : places) {
    person.Walk(p);
  }
}

int main() {
  Teacher t("Jim", "Math");
  Student s("Ann", "We will rock you");
  Policeman p("Bob");
  
  VisitPlaces(t, {"Moscow", "London"});
  p.Check(s);
  VisitPlaces(s, {"Moscow", "London"});
  return 0;
}
