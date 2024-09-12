#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

using namespace std;

class Ticket {
private:

public:
	string title;
	int urgency;
	int tps;

	Ticket() : title(""), urgency(0), tps(0) {}
	Ticket(string t, int u, int s) : title(t), urgency(u), tps(s) {}
};

class Heap{

private:
	Ticket arr[100];
	
public:
	int size;

	Heap() : size(0) {}

	void Insert(Ticket t) {
		arr[size] = t;
		UpHeapify(size);
		size++;
	}

	void UpHeapify(int i) {
		while (i > 0) {
			int p = (i - 1) / 2;
			if (arr[i].tps > arr[p].tps) {
				SwapTicket(arr[i], arr[p]);
				i = p;
			}
			else
				break;
		}
	}
	void DownHeapify(int i) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left < size && arr[left].tps > arr[largest].tps) {
			largest = left;
		}

		if (right < size && arr[right].tps > arr[largest].tps) {
			largest = right;
		}

		if (largest != i) {
			SwapTicket(arr[i], arr[largest]);
			DownHeapify(largest);
		}
	}

	Ticket ResolveTicket() {
		if (size == 0) {
			throw runtime_error("Queue is empty");
		}
		Ticket priority = arr[0];
		arr[0] = arr[size - 1];
		size--;
		DownHeapify(0);
		return priority;
	}
	void SwapTicket(Ticket& a, Ticket& b) {
		Ticket temp = a;
		a = b;
		b = temp;
	}

	Ticket* GetEverything() {
		return arr;
	}

	bool empty() {
		return size == 0;
	}
	/*
	void MaxHeapify(int arr[], int size, int index) {
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int largest;
		int temp;
		if (left < size && (arr[left] > arr[index])) {
			largest = left;
		}
		else {
			largest = index;
		}
		if (right < size && (arr[right] > arr[index])) {
			largest = right;
		}
		if (largest != index) {
			temp = arr[index];
			arr[index] = arr[largest];
			arr[largest] = temp;
			MaxHeapify(arr,size, largest);
		}
	}
	*/
};



int main() {
	
	Heap priorityqueue;
	time_t startTime = time(nullptr);

	while (true) {

		cout << "Welcome to the Ticket Managing System" << endl;
		cout << "1. Create a ticket" << endl;
		cout << "2. Resolve ticket" << endl;
		cout << "3. List all tickets" << endl;
		cout << "4. Exit" << endl;
		cout << endl;
		cout << "Select your option: ";

		int option;
		cin >> option;
		cin.ignore();
		
		if (option == 1) {
			string tle;
			int u;
			cout << "Enter the title of the ticket: ";
			getline(cin, tle);
			//cout << tle << endl;
			cout << "Enter the level of urgency (1-7): ";
			cin >> u;
			cout << u << endl;

			cin.ignore();

			time_t currentTime = time(nullptr);
			int elapsedTime = static_cast<int>(currentTime - startTime);
			int tps = ceil(pow(u, 3) / elapsedTime);

			Ticket newTicket(tle, u, tps);
			priorityqueue.Insert(newTicket);
		}
		else if (option == 2) {
			if (priorityqueue.empty()) {
				cout << "No tickets to resolve." << endl;
			}
			else {
				Ticket b = priorityqueue.ResolveTicket();
				cout << "The ticket with the title '" << b.title << "' is now resolved." << endl;
			}
		}
		else if (option == 3) {
			Ticket* a = priorityqueue.GetEverything();
			if (priorityqueue.empty()) {
				cout << "The queue is empty" << endl;
			}
			else {
				for (int i = 0; i < priorityqueue.size; i++) {
					cout << "Title: " << a[i].title << ", TPS: " << a[i].tps << " \n";
				}
			}
		}
		else if (option == 4) {
			cout << "Exit Selected" << endl;
			break;
		}
		else {
			cout << "Please choose between option 1 to 4 " << endl;
		}
	}
	
	

	/*
	int arr[] = { 1,2,3,4,5};
	int size = sizeof(arr) / sizeof(arr[0]);

	cout << "Original Array : ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	MaxHeapify(arr,size,0);

	cout << "After Heapify : ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	*/

	return 0;
}
