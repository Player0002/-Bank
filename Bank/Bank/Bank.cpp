#include <iostream>
#include <string.h>
#define NAME_LEN 20
#define MAX_ACCOUNT 100
using namespace std;



class AccountManager {
private:
	Account* accounts[MAX_ACCOUNT];
	int members = 0;

	int findIdx(const int accId) { // return accId account num
		for (int i = 0; i < members; i++) {
			if (accounts[i]->equal(accId)) return i;
		}
		return -1;
	}

	bool ssnCheck(const long long ssn) {
		for (int i = 0; i < members; i++) {
			if (accounts[i]->ssnCheck(ssn)) return false;
		}
		return true;
	}

public:
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
			accounts[i]->printInfo();
		}
	}

	void drawal() {
		int id, money;
		cout << "[출    금]" << endl;
		cout << "계좌ID: ";
		cin >> id;
		const int account_id = findIdx(id);
		if (account_id == -1) {
			cout << "유효하지 않은 ID 입니다." << endl;
			return;
		}
		cout << "출금액: ";
		cin >> money;

		bool isWork = accounts[account_id]->drawal(money);
		if (isWork) {
			cout << "출금이 완료되었습니다" << endl;
		}
		else {
			cout << "잔액이 부족합니다. " << endl;
		}
	}

	void disposit() {
		int id, money;
		cout << "[입    금]" << endl;
		cout << "계좌ID: ";
		cin >> id;
		const int account_id = findIdx(id);
		if (account_id == -1) {
			cout << "유효하지 않은 ID 입니다." << endl;
			return;
		}
		cout << "입금액: ";
		cin >> money;



		accounts[account_id]->disposit(money);
	}

	void create() {
		if (members >= 100) {
			cout << "OOPS 저희 은행은 더이상 계좌를 생성할 수 없습니다." << endl;
			return;
		}
		int id, money;
		long long ssn;
		char name[NAME_LEN];
		cout << "계좌ID: "; cin >> id;
		cout << "이  름: "; cin >> name;
		cout << "입금액: "; cin >> money;
		cout << "주민등록번호 (- 제외) : "; cin >> ssn;
		const int isCanUse = findIdx(id);
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
		if (!ssnCheck(ssn)) {
			cout << "이미 가입되신 고객님이십니다." << endl;
			return;
		}
		accounts[members] = new Account(id, money, name, ssn);
		members++;
	}
	void endProcess() {
		for (int i = 0; i < members; i++) delete accounts[i];
		cout << "할당 해제 및 프로그램 종료" << endl;
	}
};
class Account {
private:
	const int accID;
	const long long ssn;
	int balance;
	char* cusName;
public:
	Account() : accID(-1), ssn(-1){
		balance = -1;
		cusName = nullptr;
	}
	
	Account(int accId, int balance, char* cusName, long long _ssn) : accID(accId), ssn(_ssn) {
		this->balance = balance;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
	}

	Account(const Account& ref) : accID(ref.accID), ssn(ref.ssn), balance(ref.balance){
		cout << "Copy constructor call" << endl;
	  this->cusName = new char[NAME_LEN];
	  strcpy_s(this->cusName, NAME_LEN, ref.cusName);
	}
	
	void disposit(const int amount) {
		this->balance += amount;
	}
	
	bool drawal(const int amount) {
		if (balance >= amount) {
			this->balance -= amount;
			return true;
		}
		return false;
	}
	
	void printInfo() {
		cout << endl;
		cout << " Account ID :  " << accID << endl;
		cout << " Username : " << cusName << endl;
		cout << " Money : " << balance << endl;
		cout << " SSN : " << ssn << endl;
		cout << endl;
	}
	
	bool ssnCheck(const long long ssn){
		return this->ssn == ssn;
	}
	
	bool equal(const int accID){
		return this->accID == accID;
	}
	
	~Account() {
		if (cusName != nullptr) delete[] cusName;
	}
	
};



int main() {
	int choice = 0;
	AccountManager* manager = new AccountManager();
	while (true) {
		manager->showMenu();
		cin >> choice;
		switch (choice) {
		case 1:
			manager->create(); /* 계좌 생성 */
			break;
		case 2:
			manager->disposit(); /* 입금 */
			break;
		case 3:
			manager->drawal(); /* 출금 */
			break;
		case 4:
			manager->showAllAccount();
			break;
		case 5:
			manager->endProcess();
			delete manager;
			return 0;
		}
	}
	return 0;

}
