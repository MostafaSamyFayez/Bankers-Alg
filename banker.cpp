#include<iostream>
#include<vector>
#include <queue>
#include <bits/stdc++.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
bool isless(vector<int> n1, vector<int> n2) {
	for (int i = 0; i < n1.size(); i++)
	{
		if (n1[i] > n2[i])return 0;
	}
	return 1;
}
//---------------BLock 1 Safe Check------------------
queue<int> safe_check(
	int n, int m,
	vector<vector<int>> allocation,
	vector<vector<int>> need,
	vector<int>flag,
	vector<int> available)
{
	bool working = 1;
	queue<int>sequence;
	while (working) {
		working = 0;
		for (int i = 0; i < n; ++i)
		{
			if ((flag[i] == 0) && isless(need[i], available)) {
				flag[i] = 1;
				for (int k = 0; k < m; k++) {
					available[k] += allocation[i][k];
				}
				sequence.push(i);
				working = 1;
			}
		}
	}
	return sequence;
}
int main()
{
	while (1)
	{
		//---------------Block 2 Taking Input----------------------
		int n, m;
		cout << "Enter Number Of Processes: ";
		cin >> n;
		cout << "Enter Number Of Resources: ";
		cin >> m;
		vector<vector<int>> allocation(n, vector<int>(m)), max(n, vector<int>(m)), need(n, vector<int>(m));
		vector<int> available(m);
		queue<int>sequence;
		cout << endl << "Enter Allocation Matrix: \n\n";
		//Input allocation matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				cin >> allocation[i][j];
		}
		cout << endl << "Enter Maximum Matrix: \n\n";
		//Input maximum matrix
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				cin >> max[i][j];
		}
		cout << endl;
		cout << "Enter Available Vector:";
		//Input available Vector matrix
		for (int i = 0; i < m; i++) {
			cin >> available[i];
		}
		cout << endl;
		cout << "---> Need Matrix:\n   ";
		for (int i = 0; i < m; i++) {
			cout << "R" << i << " ";
		}
		cout << endl;
		//Output need matrix
		for (int i = 0; i < n; i++) {
			cout << "P" << i << "  ";
			for (int j = 0; j < m; j++)
			{
				need[i][j] = max[i][j] - allocation[i][j];
				cout << need[i][j] << "  ";
			}
			cout << endl;
		}
		cout << endl;
		//---------------Block 3 Operation----------------------
	new_operation:
		vector<int>flag(n, 0);
		cout << "*** Choose Operation Number: *** \n1)Safe State.    2)Immediate Request.   \n3)New Problem.   4)Exit!\n";
		int operation;
		cin >> operation;
		//----The Safety Algorithm 
		if (operation == 1)
		{
			sequence = safe_check(n, m, allocation, need, flag, available);
			if (sequence.size() < n)cout << "---> NO\n\n";
			else {
				cout << "---> Yes,Safe state<";
				while (1) {
					cout << "P" << sequence.front();
					sequence.pop();
					if (sequence.empty()) { cout << ">\n\n"; break; }
					cout << ",";
				}
			}
			cout << endl;
			goto new_operation;
		}

		//----The Request Algorithm
		if (operation == 3)
		{
			system("CLS");
			continue;
		}
		if (operation == 4)break;
		if (operation == 2)
		{
			//these new variables to enable re enter new request for the same  problem
			vector<vector<int>> allocation_new(n, vector<int>(m)), need_new(n, vector<int>(m));
			vector<int> available_new(m);
			vector<int>flag_new(n);
			for (int i = 0; i < m; i++) {
				available_new[i] = available[i];
			}
			for (int i = 0; i < n; i++) {
				flag_new[i] = flag[i];
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					need_new[i][j] = need[i][j];
					allocation_new[i][j] = allocation[i][j];
				}
			}
			int p;
			bool valid = 1;
			cout << "Enter Process Number: ";
			cin >> p;
			cout << "Enter Process Resources Vector: ";
			//Check if request greater than need or than available then its not valid
			for (int i = 0; i < m; i++) {
				int request;
				cin >> request;
				if ((request > need[p][i]) || (request > available[i])) valid = 0;
				available_new[i] -= request;
				allocation_new[p][i] += request;
				need_new[p][i] -= request;
			}
			if (!valid) {
				cout << "---> No\n\n";
				goto new_operation;
			}
			//Safety Check for the Request
			sequence = safe_check(n, m, allocation_new, need_new, flag_new, available_new);
			if (sequence.size() < n) {
				cout << "---> No\n\n";
				goto new_operation;
			}
			else {
				cout << "---> Yes request can be granted with safe state , Safe state <";
				while (1) {
					if(sequence.front()==p) cout<< "P" << p << "req";
					else cout << "P" << sequence.front();
					sequence.pop();
					if (sequence.empty()) { cout << ">\n\n"; break; }
					cout << ",";
				}
				goto new_operation;
			}
		}
	}
	system("pause");
}