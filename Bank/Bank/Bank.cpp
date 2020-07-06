#include <iostream>
#include <string.h>
#define NAME_LEN 20
#define MAX_ACCOUNT 100

enum AccType {
	NORMAL, DISPOSIT
};
using namespace std;

class BaseAccount {
private:
	int addAmount;
	int balance;
	const int accId;
public:
	BaseAccount(int accId, int balance, int addAmount) : accId(accId), balance(balance), addAmount(addAmount) {}
	void disposit(const int amount) {
		int addMoney = addAmount * ((balance + amount) / 100.0);

		balance += amount + addMoney;

		cout << "Add Money : " << addMoney << endl;
	}
	BaseAccount(BaseAccount& REF) : accId(REF.accId), balance(REF.balance), addAmount(REF.addAmount) {
		cout << "Copy constructor" << endl;
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
		cout << " Account ID :  " << accId << endl;
		cout << " Money : " << balance << endl;
		cout << endl;
	}

	bool compareAccId(int accId) {
		return this->accId == accId;
	}
};

class NormalAccount : public BaseAccount {
public:
	NormalAccount(int accId, int balance) : BaseAccount(accId, balance, 1) {
	}
};

class DispositAccount : public BaseAccount {
public:
	DispositAccount(int accId, int balance) : BaseAccount(accId, balance, 2) {}
};

class Account {
private:
	int id;
	const long long ssn;
	char* cusName;
	NormalAccount* normalAccount;
	DispositAccount* dispositAccount;
public:
	Account() : ssn(-1) , id(-1){
		cusName = nullptr;
		normalAccount = nullptr;
		dispositAccount = nullptr;
	}

	Account(int id, char* cusName, long long _ssn) :id(id), ssn(_ssn) {
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, cusName);
		normalAccount = nullptr;
		dispositAccount = nullptr;
	}

	Account(const Account& ref) : ssn(ref.ssn), id(ref.id), normalAccount(ref.normalAccount), dispositAccount(ref.dispositAccount) {
		cout << "Copy constructor call" << endl;
		this->cusName = new char[NAME_LEN];
		strcpy_s(this->cusName, NAME_LEN, ref.cusName);
	}

	void setNormalAccount(NormalAccount* normalAccount) { this->normalAccount = normalAccount; }
	void setDispositAccount(DispositAccount* dispositAccount) { this->dispositAccount = dispositAccount; }

	NormalAccount* getNormalAccount() const { return normalAccount; }
	DispositAccount* getDispositAccount() const { return dispositAccount; }

	void disposit(AccType type, const int amount) {
		switch (type)
		{
		case NORMAL:
			if (normalAccount == nullptr) {
				cout << "보통 계좌가 존재하지 않습니다." << endl;
				return;
			}
			normalAccount->disposit(amount);
			break;
		case DISPOSIT:
			if (dispositAccount == nullptr) {
				cout << "예금계좌가 존재하지 않습니다." << endl;
				return;
			}
			dispositAccount->disposit(amount);
			break;
		default:
			break;
		}
	}

	bool drawal(AccType type, const int amount) {
		switch (type)
		{
		case NORMAL:
			if (normalAccount == nullptr) {
				cout << "보통 계좌가 존재하지 않습니다." << endl;
				return false;
			}
			return normalAccount->drawal(amount);
		case DISPOSIT:
			if (dispositAccount == nullptr) {
				cout << "예금계좌가 존재하지 않습니다." << endl;
				return false;
			}
			return dispositAccount->drawal(amount);
		default:
			return false;
		}
	}

	void printInfo() {
		cout << endl;
		cout << " Username : " << cusName << endl;
		cout << " SSN : " << ssn << endl;
		cout << endl;

		cout << endl;
		cout << "보통계좌 정보" << endl;
		if (normalAccount == nullptr) cout << "보통 계좌가 존재하지 않습니다." << endl << endl;
		else normalAccount->printInfo();
		cout << endl;
		cout << "예금 계좌 정보" << endl;
		if (dispositAccount == nullptr) cout << "예금 계좌가 존재하지 않습니다." << endl << endl;
		else dispositAccount->printInfo();
	}

	bool ssnCheck(const long long ssn) {
		return this->ssn == ssn;
	}
	bool checkId(int id) {
		return this->id == id;
	}


	~Account() {
		if (cusName != nullptr) delete[] cusName;
		if (normalAccount != nullptr) delete normalAccount;
		if (dispositAccount != nullptr) delete dispositAccount;
	}

};


class AccountManager {
private:
	Account* accounts[MAX_ACCOUNT];
	int members = 0;

	int checkAccId(AccType type, int accId) {
		switch (type)
		{
		case NORMAL:
			for (int i = 0; i < members; i++) {
				if (accounts[i]->getNormalAccount() != nullptr) {
					if (accounts[i]->getNormalAccount()->compareAccId(accId)) return true;
				}
			}
			for (int i = 0; i < members; i++) {
				if (accounts[i]->getDispositAccount() != nullptr) {
					if (accounts[i]->getDispositAccount()->compareAccId(accId)) return true;
				}
			}
			return false;
		case DISPOSIT:
			for (int i = 0; i < members; i++) {
				if (accounts[i]->getDispositAccount() != nullptr) {
					if (accounts[i]->getDispositAccount()->compareAccId(accId)) return true;
				}
			}
			for (int i = 0; i < members; i++) {
				if (accounts[i]->getNormalAccount() != nullptr) {
					if (accounts[i]->getNormalAccount()->compareAccId(accId)) return true;
				}
			}
			return false;
		default:
			cout << "Exception in Check acc ID" << endl;
			return true;
		}
	}

	int findId(const int id) { // return accId account num
		for (int i = 0; i < members; i++) {
			if (accounts[i]->checkId(id)) return i;
		}
		return -1;
	}

	int ssnCheck(const long long ssn) {
		for (int i = 0; i < members; i++) {
			if (accounts[i]->ssnCheck(ssn)) return i;
		}
		return -1;
	}

public:
	void showMenu() {
		cout << "1. 계정생성" << endl;
		cout << "2. 계좌개설" << endl;
		cout << "3. 입    금" << endl;
		cout << "4. 출    금" << endl;
		cout << "5. 계좌정보 전체출력" << endl;
		cout << "6. 프로그램 종료" << endl;
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

	void drawal(AccType type) {
		int uid, id, money;
		cout << "[출    금]" << endl;
		cout << "사용자 ID : "; cin >> uid;
		uid = findId(uid);
		if (uid == -1) {
			cout << "없는 사용자 입니다." << endl;
			return;
		}
		cout << "출금액: ";
		cin >> money;

		cout << "계좌번호: ";
		cin >> id;
		int account_id = 0;
		switch (type)
		{
		case NORMAL:
			account_id = checkAccId(NORMAL, id);
			if (account_id == -1) {
				cout << "유효하지 않은 계좌 번호 입니다." << endl;
				return;
			}

			if (accounts[uid]->drawal(NORMAL, money)) {
				cout << "출금이 완료되었습니다." << endl;
				return;
			}
			else {
				cout << "잔액이 부족합니다." << endl;
				return;
			}

			break;
		case DISPOSIT:

			account_id = checkAccId(DISPOSIT, id);
			if (account_id == -1) {
				cout << "유효하지 않은 계좌 번호 입니다." << endl;
				return;
			}

			if (accounts[uid]->drawal(DISPOSIT, money)) {
				cout << "출금이 완료되었습니다." << endl;
				return;
			}
			else {
				cout << "잔액이 부족합니다." << endl;
				return;
			}
			break;
		default:
			break;
		}
	}

	void disposit(AccType type) {
		int id, money, uid, account_id;
		cout << "[입    금]" << endl;
		cout << "사용자 ID : "; cin >> uid;
		uid = findId(uid);
		if (uid == -1) {
			cout << "없는 사용자 입니다." << endl;
			return;
		}

		cout << "계좌번호: ";
		cin >> id;
		switch (type)
		{
		case NORMAL:

			account_id = checkAccId(NORMAL, id);
			if (account_id == -1) {
				cout << "유효하지 않은 ID 입니다." << endl;
				return;
			}
			cout << "입금액: ";
			cin >> money;
			accounts[uid]->disposit(NORMAL, money);
			return;
		case DISPOSIT:
			account_id = checkAccId(DISPOSIT, id);
			if (account_id == -1) {
				cout << "유효하지 않은 ID 입니다." << endl;
				return;
			}
			cout << "입금액: ";
			cin >> money;
			accounts[uid]->disposit(DISPOSIT, money);
			return;
		default:
			break;
		}
	}

	void create() {
		if (members >= 100) {
			cout << "OOPS 저희 은행은 더이상 계좌를 생성할 수 없습니다." << endl;
			return;
		}
		int id;
		long long ssn;
		char name[NAME_LEN];
		cout << "아이디 ( 정수 ) : "; cin >> id;
		cout << "이  름: "; cin >> name;
		cout << "주민등록번호 (- 제외) : "; cin >> ssn;
		if (findId(id) != -1) {
			cout << "이미 존재하는 아이디 입니다." << endl;
			return;
		}
		if (ssnCheck(ssn) != -1) {
			cout << "이미 가입되신 고객님이십니다." << endl;
			return;
		}
		accounts[members] = new Account(id, name, ssn);
		members++;
	}

	void createNormalAccount() {
		int id;
		cout << "아이디 (정수) : "; cin >> id;
		int user_id = findId(id);
		if (user_id == -1) {
			cout << "존재하지 않는 사용자 입니다." << endl;
			return;
		}
		Account* user = accounts[user_id];
		
		if (user->getNormalAccount() != nullptr) {
			cout << "이미 보통계좌가 존재합니다." << endl;
			return;
		}

		int balance;
		int accId;

		cout << "사용할 계좌번호를 입력해주세요 : "; cin >> accId;
		if (checkAccId(NORMAL, accId)) {
			cout << "중복된 계좌번호가 존재합니다." << endl;
			return;
		}
		cout << "입금할 금액을 입력해주세요 : "; cin >> balance;
		if (balance < 10) {
			cout << "10원 이상을 입금하셔야 합니다." << endl;
			return;
		}

		NormalAccount* account = new NormalAccount(accId, balance);
		user->setNormalAccount(account);
		cout << "보통계좌 개설이 완료되었습니다." << endl;
		return;
	}
	void createDispositAccount() {
		int id;
		cout << "아이디 (정수) : "; cin >> id;
		int user_id = findId(id);
		if (user_id == -1) {
			cout << "존재하지 않는 사용자 입니다." << endl;
			return;
		}
		Account* user = accounts[user_id];

		if (user->getNormalAccount() == nullptr) {
			cout << "예금계좌는 보통계좌가 존재해야 만들 수 있습니다." << endl;
			return;
		}
		if (user->getDispositAccount() != nullptr) {
			cout << "이미 예금계좌가 존재합니다." << endl;
			return;
		}

		int balance;
		int accId;

		cout << "사용할 계좌번호를 입력해주세요 : "; cin >> accId;
		if (checkAccId(DISPOSIT, accId)) {
			cout << "중복된 계좌번호가 존재합니다." << endl;
			return;
		}
		cout << "입금할 금액을 입력해주세요 : "; cin >> balance;
		if (balance < 10) {
			cout << "10원 이상을 입금하셔야 합니다." << endl;
			return;
		}

		DispositAccount* account = new DispositAccount(accId, balance);
		user->setDispositAccount(account);
		cout << "예금계좌 개설이 완료되었습니다." << endl;
		return;
	}
	~AccountManager() {
		for (int i = 0; i < members; i++) delete accounts[i];
		cout << "할당 해제 및 프로그램 종료" << endl;
	}
};



int main() {
	int choice = 0;
	AccountManager* manager = new AccountManager();

	int tid = 0;
	while (true) {
		manager->showMenu();
		cin >> choice;
		switch (choice) {
		case 1:
			manager->create(); /* 계좌 생성 */
			break;
		case 2:
			cout << endl;
			cout << "1. 보통계좌" << endl;
			cout << "2. 예금계좌" << endl;
			cout << endl;
			cin >> tid;
			switch (tid)
			{
			case 1:
				manager->createNormalAccount();
				break;
			case 2:
				manager->createDispositAccount();
				break;
			default:
				break;
			}
			break;
		case 3:
			cout << endl;
			cout << "1. 보통계좌" << endl;
			cout << "2. 예금계좌" << endl;
			cout << endl;
			cin >> tid;
			switch (tid) {
			case 1:
				manager->disposit(NORMAL);
				break;
			case 2:
				manager->disposit(DISPOSIT);
				break;
			}/* 입금 */
			break;
		case 4:
			cout << endl;
			cout << "1. 보통계좌" << endl;
			cout << "2. 예금계좌" << endl;
			cout << endl;
			cin >> tid;
			switch (tid) {
			case 1:
				manager->drawal(NORMAL);
				break;
			case 2:
				manager->drawal(DISPOSIT);
				break;
			}/* 출금 */
			break;
		case 5:
			manager->showAllAccount();
			break;
		case 6:
			delete manager;
			return 0;
		}
	}
	return 0;

}
