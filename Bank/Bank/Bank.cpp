#include <iostream>
#define NAME_LEN 20
using namespace std;
typedef struct {
	int accID;
	int balance;
	char cusName[NAME_LEN];
} Account;
Account *arr = new Account[101];
void showMenu() {
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체출력" << endl;
	cout << "5. 프로그램 종료" << endl;
	cout << "선택 : ";
}
void showAllAccount() {
	for (int i = 0; i < 101; i++) {
		if (arr[i].accID == -1) continue;
		cout << endl;
		cout << "계좌ID : " << arr[i].accID << endl;
		cout << "이   름: " << arr[i].cusName << endl;
		cout << "잔   액: " << arr[i].balance << endl;
		cout << endl;
	}
}
void drawal() {
	int id, money;
	cout << "[출    금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	cout << "출금액: ";
	cin >> money;

	if (arr[id].accID == -1) {
		cout << "유효하지 않은 ID 입니다.";
		return;
	}
	if (arr[id].balance < money) {
		cout << "잔액이 부족합니다. 현재 잔액 : " << arr[id].balance << endl;
		return;
	}
	arr[id].balance -= money;
}
void disposit() {
	int id, money;
	cout << "[입    금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	cout << "입금액: ";
	cin >> money;
	
	if (arr[id].accID == -1) {
		cout << "유효하지 않은 ID 입니다.";
		return;
	}
	arr[id].balance += money;
}
void create() {
	int id, money;
	char name[NAME_LEN];
	cout << "계좌ID: "; cin >> id;
	cout << "이  름: "; cin >> name;
	cout << "입금액: "; cin >> money;
	
	if (id < 0) { 
		cout << "사용할 수 없는 계좌번호 입니다." << endl;
		return;
	}
	if (money < 10) {
		cout << "최소한 10원 이상을 입금하셔야 합니다." << endl;
		return;
	}
	Account acc = Account();
	acc.accID = id;
	acc.balance = money;
	strcpy_s(acc.cusName, name); //이름을 넘겨주기 위해서 strcpy 사용
	arr[id] = acc;
	
}
void main() {
	for (int i = 0; i < 101; i++) arr[i] = Account{ -1, 0, 0 };
	int choice = 0;
	while (true) {
		showMenu();
		cin >> choice;
		if (choice == 5) break; //종료 시점
		switch (choice) {
		case 1:
			create(); /* 계좌 생성 */
			break;
		case 2:
			disposit(); /* 입금 */
			break;
		case 3:
			drawal(); /* 출금 */
			break;
		case 4:
			showAllAccount();
			break;
		}
	}

	delete arr;
	cout << "할당 해제 및 프로그램 종료" << endl;
}