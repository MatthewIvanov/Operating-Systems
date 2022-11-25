#include <windows.h>
#include <iostream>
#include <vector>
using namespace std;
struct Node {
	int n;
	vector <int> vec;
};
DWORD WINAPI min_max(LPVOID node) {
	Node* obj = (Node*)node;
	int max = INT_MIN; int min = INT_MAX;
	for (size_t i = 0; i < obj->n ; i++){
		if (obj->vec[i] < min) { 
			min = obj->vec[0]; 
		}
		if (obj->vec[i] > max) {
			max = obj->vec[i];
		}
		Sleep(7);
	}
	cout << "Max_element: " << max << "  Min_element: " << min << "\n";
	return 0;
}
DWORD WINAPI average(LPVOID  node) {
	Node* obj = (Node*)node;
	double sum = 0;
	for (size_t i = 0; i <obj->n ; i++){
		sum += obj->vec[i];
		Sleep(12);
	}
	cout << "Average: " << sum / obj->n << "\n";
	return 0;
}
HANDLE MIN_MAX(Node& node) {
	HANDLE Thread;
	DWORD IDThread;
	Thread = CreateThread(NULL, 0, min_max, (void*)&node, 0, &IDThread);
		if (Thread == NULL) {
			cout << "Thread didn't start";
		}
		return Thread;
}
HANDLE AVERAGE(Node& node) {
	HANDLE Thread;
	DWORD IDThread;
	Thread = CreateThread(NULL, 0, average, (void*)&node, 0, &IDThread);
	if (Thread == NULL) {
		cout << "Thread didn't start";
	}
	return Thread;
}

int main(){
	Node node;
	int n;
	cout << "Enter count of elements: ";
	cin >> n; 
	node.n = n;
	cout << "List of elements: ";
	for (size_t i = 0; i < n; i++){
		int x;
		cin >> x;
		node.vec.push_back(x);
	}
	
	HANDLE firstThread = MIN_MAX(node);
	HANDLE secondThread = AVERAGE(node);


	WaitForSingleObject(firstThread, INFINITE);
	WaitForSingleObject(secondThread, INFINITE);



	CloseHandle(firstThread);
	CloseHandle(secondThread);

	return 0;
}
