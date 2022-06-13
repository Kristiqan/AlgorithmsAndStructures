#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void openFile(ifstream&,string);
void readSourceFile(ifstream&);

class CafeteriaQueue
{
	struct Student
	{
		string StudentName;
		unsigned int StudentGNumber;
		int currentAttendanceWaitingPeriod;
		Student* nextInLine;

		Student(string StudentName, unsigned int StudentGNumber)
		{
			this->StudentName = StudentName;
			this->StudentGNumber = StudentGNumber;
			this->currentAttendanceWaitingPeriod = 0;
			nextInLine = nullptr;
		};
		void Print();
	};
	Student* firstInLine;
	Student* lastInLine;


	void CopyFrom(const CafeteriaQueue& other);

public:
	CafeteriaQueue();
	CafeteriaQueue(const CafeteriaQueue& other);
	CafeteriaQueue operator=(const CafeteriaQueue& other);
	~CafeteriaQueue();

	void EnqueueANewStudent(ifstream& file);
	void CurrentTimeToWait();
	bool SearchForFamiliar(string StudentName, unsigned int StudentGNumber);
	void SpecificPositionInsertion(Student* firstInLine, string StudentName, unsigned int StudentGNumber);

};

int main()
{

	ifstream sourceFile;
	openFile(sourceFile, "students.txt");
	CafeteriaQueue CafeteriaQueue;
	CafeteriaQueue.EnqueueANewStudent(sourceFile);

	sourceFile.close();

	return 0;
}


void CafeteriaQueue::Student::Print()
{
	cout << StudentName << " (Group " << StudentGNumber << ") has waited a total of " << currentAttendanceWaitingPeriod << " minutes  " << endl;
}



void CafeteriaQueue::CopyFrom(const CafeteriaQueue& other)
{
	Student* traverser = other.firstInLine;
	while (traverser != nullptr)
	{
		if (firstInLine == NULL && lastInLine == NULL)
		{
			firstInLine = traverser;
			lastInLine = traverser;
		}
		else
		{
			lastInLine->nextInLine = traverser;
			lastInLine = traverser;
		}
		traverser = traverser->nextInLine;
	}
}



CafeteriaQueue::CafeteriaQueue()
{
	firstInLine = nullptr;
	lastInLine = nullptr;
}

CafeteriaQueue::CafeteriaQueue(const CafeteriaQueue& other)
{
	Student* traverser = other.firstInLine;
	while (traverser != nullptr)
	{
		if (firstInLine == NULL && lastInLine == NULL)
		{
			firstInLine = traverser;
			lastInLine = traverser;
		}
		else
		{
			lastInLine->nextInLine = traverser;
			lastInLine = traverser;
		}
		traverser = traverser->nextInLine;
	}
}

CafeteriaQueue CafeteriaQueue::operator=(const CafeteriaQueue& other)
{
	if (this != &other)
	{
		Student* traverser = firstInLine;
		while (traverser != nullptr)
		{
			Student* prev = traverser;
			traverser = traverser->nextInLine;
			delete prev;
		}
		firstInLine = lastInLine = nullptr;
		CopyFrom(other);
	}
	return *this;
}

CafeteriaQueue::~CafeteriaQueue()
{
	Student* traverser = firstInLine;
	while (traverser != nullptr)
	{
		Student* prev = traverser;
		traverser = traverser->nextInLine;
		delete prev;
	}
	firstInLine = lastInLine = nullptr;
}




void CafeteriaQueue::EnqueueANewStudent(ifstream& file)
{
	string StudentName;
	string number;

	int count = 0;
	bool FindFirend = false;

	while (!file.eof())
	{
		getline(file, StudentName, ' ');
		getline(file, number);
		count++;
		unsigned int StudentGNumber = stoi(number);
		Student* newStudent = new Student(StudentName, StudentGNumber);
		FindFirend = SearchForFamiliar(StudentName, StudentGNumber);

		if (FindFirend == true)
		{
			SpecificPositionInsertion(firstInLine, StudentName, StudentGNumber);
		}
		else
		{
			if (firstInLine == NULL && lastInLine == NULL)
			{
				firstInLine = newStudent;
				lastInLine = newStudent;
			}
			else
			{
				lastInLine->nextInLine = newStudent;
				lastInLine = newStudent;
			}

		}
		CurrentTimeToWait();
		if (count % 2 == 0)
		{
			firstInLine->Print();
			Student* temporaryProp = firstInLine;
			firstInLine = firstInLine->nextInLine;
			if (firstInLine == NULL)
				lastInLine = NULL;

			delete (temporaryProp);
		}
	}
	while (firstInLine != nullptr)
	{
		count++;
		CurrentTimeToWait();
		if (count % 2 == 0)
		{
			firstInLine->Print();
			Student* temporaryProp = firstInLine;
			firstInLine = firstInLine->nextInLine;
			if (firstInLine == NULL)
				lastInLine = NULL;

			delete (temporaryProp);
		}
	}
}
bool CafeteriaQueue::SearchForFamiliar(string StudentName, unsigned int StudentGNumber)
{
	Student* traverser = firstInLine;
	if (traverser == NULL)
		return false;
	while (traverser != NULL)
	{
		if (traverser->StudentGNumber == StudentGNumber && traverser->StudentName != StudentName)
		{
			return true;
		}
		traverser = traverser->nextInLine;
	}
}
void CafeteriaQueue::CurrentTimeToWait()
{
	Student* traverser = firstInLine;
	int count = 0;
	while (traverser != NULL)
	{
		traverser->currentAttendanceWaitingPeriod = traverser->currentAttendanceWaitingPeriod + 1;
		traverser = traverser->nextInLine;
	}
}
void CafeteriaQueue::SpecificPositionInsertion(Student* firstInLine, string StudentName, unsigned int StudentGNumber)
{
	Student* newStudent = new Student(StudentName, StudentGNumber);
	if (StudentGNumber == firstInLine->StudentGNumber) {
		newStudent->nextInLine = firstInLine->nextInLine;
		firstInLine->nextInLine = newStudent;
		return;
	}

	Student* temporaryProp = firstInLine;
	while (temporaryProp->StudentGNumber != StudentGNumber) {
		temporaryProp = temporaryProp->nextInLine;
		if (temporaryProp == NULL) {
			return;
		}
	}
	newStudent->nextInLine = temporaryProp->nextInLine;
	temporaryProp->nextInLine = newStudent;
}


void openFile(ifstream& sourceFile, string SourceFileDestination)
{
	sourceFile.open(SourceFileDestination);
}
void readSourceFile(ifstream& sourceFile)
{
	string data;
	while (!sourceFile.eof())
	{
		getline(sourceFile, data);
		
	}
}
