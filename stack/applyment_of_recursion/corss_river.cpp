/*����������Ϸ
��Ϸ����һ��6�ڣ��ְ֡����衢����Ů�����������ӣ��������С͵Ҫ�Ӻ���߶ɵ��Ӷ԰���
�ں���߽���һ��С������԰������ص��԰������ǣ�ֻ�аְ֡�����;����ܹ��ݴ���
���۳�����С����ÿ��ֻ�ܳ��ض��ˡ��ڶɺӹ����У���Ҫ����������������ķ�����
��1��	��������С͵�ֿ�ʱ��С͵���˺�һ��6�ڣ�
��2��	���ְֿ��������뿪ʱ���ְֱ���ѵŮ����
��3��	�����迴���ְ��뿪ʱ���������ѵ���ӡ�
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

string from = "fmssddpt";
string to;
vector<string> result;

bool isThiefCanHurt(const string &str) {
	return str.find('t') != string::npos && str.find('p') == string::npos && str.size() > 1;
}

bool isOnlyFatherAndDaughter(const string &str) {
	return str.find('f') != string::npos && str.find('m') == string::npos
		&& str.find('d') != string::npos;
}

bool isOnlyMomAndSon(const string &str) {
	return str.find('f') == string::npos && str.find('m') != string::npos
		&& str.find('s') != string::npos;
}

bool canTogether(const string &vec) {
	return !isOnlyMomAndSon(vec) && !isOnlyFatherAndDaughter(vec) && !isThiefCanHurt(vec);
}

bool isNotLoop(const vector<string>& result) {
	vector<string>::size_type size = result.size();
	return size < 2 || result[size - 1] != result[size - 2] && result[size - 1] != string(result[size - 2].rbegin(), result[size - 2].rend());
}

bool corss(int direction) {
	if (from.empty()) {
		map<char, string> m;
		m['f'] = "����";
		m['m'] = "ĸ��";
		m['p'] = "����";
		m['t'] = "С͵";
		m['s'] = "����";
		m['d'] = "Ů��";
		int direction = 1;
		for (auto str : result) {
			cout << (direction ? "��" : "��");
			for (auto ch : str)
				cout << m[ch] << ' ';
			cout << endl;
			direction = 1 - direction;
		}
		return true;
	}
	else {
		string *ptrVec;
		string *ptrOther;
		if (direction == 0) {
			ptrVec = &from;
			ptrOther = &to;
		}
		else if (direction == 1) {
			ptrVec = &to;
			ptrOther = &from;
		}

		static char person[3] = { 'f','m','p' };
		string::size_type pos;
		int i;
		char temp;
		for (i = 0; i < 3; ++i) {
			if ((pos = ptrVec->find(person[i])) != string::npos) {
				ptrVec->erase(pos, 1);
				ptrOther->append(1, person[i]);

				// һ����
				if (canTogether(*ptrVec) && canTogether(*ptrOther)) {
					result.push_back(string(1, person[i]));
					if (isNotLoop(result))
						if (corss(1 - direction))return true;
					result.pop_back();
				}

				// ������
				for (string::size_type j = 0; j != (*ptrVec).size(); ++j) {
					temp = (*ptrVec)[j];
					ptrVec->erase(j, 1);
					ptrOther->append(1, temp);

					if (canTogether(*ptrVec) && canTogether(*ptrOther)) {
						result.push_back(string(1, person[i]) + temp);
						if (isNotLoop(result))
							if (corss(1 - direction))return true;
						result.pop_back();
					}

					ptrOther->erase(ptrOther->size() - 1);
					ptrVec->insert(j, 1, temp);
				}

				ptrVec->insert(pos, 1, person[i]);
				ptrOther->erase(ptrOther->size() - 1);
			}
		}
		return false;
	}
}

int main() {
	corss(0);
	return 0;
}
