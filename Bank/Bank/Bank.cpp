#include <iostream>
#define NAME_LEN 20
#define MAX_ACCOUNT 100
using namespace std;
typedef struct {
	int accID;
	int balance;
	char cusName[NAME_LEN];
} Account;
Account *accounts = new Account[MAX_ACCOUNT];
int members = 0;
int findIdx(int accId) { // return accId account num
	for (int i = 0; i < members; i++) {
		if (accounts[i].accID == accId) return i;
	}
	return -1;
}
void showMenu() {
	cout << "1. 계좌개설" << endl;
	cout << "2. 입    금" << endl;
	cout << "3. 출    금" << endl;
	cout << "4. 계좌정보 전체출력" << endl;
	cout << "5. 프로그램 종료" << endl;
	cout << "선택 : ";
}
void showAllAccount() {
	if (members == 0) {
		cout << endl;
		cout << "이런.. 저희 은행의 고객은 아무도 없군요" << endl;
		cout << endl;
		return;
	}
	for (int i = 0; i < members; i++) {
		cout << endl;
		cout << "계좌ID : " << accounts[i].accID << endl;
		cout << "이   름: " << accounts[i].cusName << endl;
		cout << "잔   액: " << accounts[i].balance << endl;
		cout << endl;
	}
}
void drawal() {
	int id, money;
	cout << "[출    금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	int account_id = findIdx(id);
	if (account_id == -1) {
		cout << "유효하지 않은 ID 입니다." << endl;
		return;
	}
	cout << "출금액: ";
	cin >> money;
	
	if (accounts[account_id].balance < money) {
		cout << "잔액이 부족합니다. 현재 잔액 : " << accounts[account_id].balance << endl;
		return;
	}
	accounts[account_id].balance -= money;
}
void disposit() {
	int id, money;
	cout << "[입    금]" << endl;
	cout << "계좌ID: ";
	cin >> id;
	int account_id = findIdx(id);
	if (account_id == -1) {
		cout << "유효하지 않은 ID 입니다." << endl;
		return;
	}
	cout << "입금액: ";
	cin >> money;


	
	accounts[account_id].balance += money;
}
void create() {
	if (members >= 100) {
		cout << "OOPS 저희 은행은 더이상 계좌를 생성할 수 없습니다." << endl;
		return;
	}
	int id, money;
	char name[NAME_LEN];
	cout << "계좌ID: "; cin >> id;
	cout << "이  름: "; cin >> name;
	cout << "입금액: "; cin >> money;
	int isCanUse = findIdx(id);
	if (id < 0) {
		cout << "사용할 수 없는 계좌번호 입니다." << endl;
		return;
	}
	if (money < 10) {
		cout << "최소한 10원 이상을 입금하셔야 합니다." << endl;
		return;
	}
	if (isCanUse != -1) {
		cout << "이미 같은 계좌번호가 존재합니다." << endl;
		return;
	}
	Account acc = Account();
	acc.accID = id;
	acc.balance = money;
	strcpy_s(acc.cusName, name); //이름을 넘겨주기 위해서 strcpy 사용
	accounts[members] = acc;
	members++;
}
void main() {
	int choice = 0;
	while (true) {
		showMenu();
		cin >> choice;
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
		case 5:
			delete accounts;
			cout << "할당 해제 및 프로그램 종료" << endl;
			return;
		}
	}

}