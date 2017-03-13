// merge without recuesive.cpp : Defines the entry point for the console application.
#include<iostream>
#include<cstdlib>
using std::cout; using std::cin; using std::endl;

void print_seq(int* &seq, const int& sz) {
	for (int i = 0; i < sz; ++i) {
		cout << *(seq + i) << " ";
	}
	cout << endl;
}

int merge_part(int* &seq, const int& sz) {
	int* end = seq + sz;
	int* runner1 = seq;
	int* runner2 = seq + 1;
	int jump = 1;
	int times = 0;
	int* sub_end1 = nullptr;
	int* sub_end2 = nullptr;
	int *newseq = new int[sz];
	int* porter = newseq;
	while (runner2 < end) {
		++times;
		while (runner1 < end) {
			auto hd1 = runner1;
			auto hd2 = runner2;
			sub_end1 = hd2;
			sub_end2 = ((hd1 + jump * 2) < end) ? (hd1 + jump * 2) : end;
			while (runner1 < sub_end1 || runner2 < sub_end2) {
				if (runner1 < sub_end1 && runner2 < sub_end2) {
					int* &smaller = (*runner1 > *runner2) ? runner2 : runner1;
					*(porter++) = *smaller;
					smaller+=1;
				}
				else if ((runner1 == sub_end1 && runner2 < sub_end2) || (runner1 < sub_end1 && runner2 == sub_end2)) {
					int* &noreachend = (runner1 == sub_end1) ? runner2 : runner1;
					int* &anotherend = (runner1 == sub_end1) ? sub_end2 : sub_end1;
					for (auto &i = noreachend; i < anotherend; ++i) {
						*(porter++) = *i;
					}
				}
			}
			runner1 = runner2;
			runner2 = ((runner1 + jump) < end) ? (runner1 + jump) : end;;
		}
		int* temp = seq;
		seq = newseq;
		delete[]temp;
		temp = nullptr;
		newseq = nullptr;
		newseq = new int[sz];
		porter = newseq;
		jump *= 2;
		end = seq + sz;
		runner1 = seq;
		runner2 = ((seq + jump) < end) ? (seq + jump) : end;
	}
	delete[]newseq;
	newseq = nullptr;;
	end = nullptr;
	runner1 = nullptr;
	runner2 = nullptr;
	sub_end1 = nullptr;
	sub_end2 = nullptr;
	porter = nullptr;
	return times;
}

void merge(int* &seq, const int &sz) {
	int l_sz = (int)((sz + 1) / 2);
	int r_sz = sz - l_sz;
	int* rbeg = seq + l_sz;
	int* left = new int[l_sz];
	int* right = new int[r_sz];
	for (int i = 0; i < l_sz; ++i) {
		*(left + i) = *(seq + i);
	}
	for (int i = 0; i < r_sz; ++i) {
		*(right + i) = *(rbeg + i);
	}
	int l_times = merge_part(left, l_sz);
	int r_times = merge_part(right, r_sz);
	auto runner1 = left;
	auto runner2 = right;
	auto end1 = left + l_sz;
	auto end2 = right + r_sz;
	int* newseq = new int[l_sz + r_sz];
	int* porter = newseq;
	while (runner1 < end1 || runner2 < end2) {
		if (runner1 < end1 && runner2 < end2) {
			int* &smaller = (*runner1 > *runner2) ? runner2 : runner1;
			*(porter++) = *smaller;
			smaller++;
		}
		else if ((runner1 == end1 && runner2 < end2) || (runner1 < end1 && runner2 == end2)) {
			int* &noreachend = (runner1 == end1) ? runner2 : runner1;
			int* &anotherend = (runner1 == end1) ? end2 : end1;
			for (auto &i = noreachend; i < anotherend; ++i) {
				*(porter++) = *i;
			}
		}
	}
	int* temp = seq;
	seq = newseq;
	newseq = nullptr;
	delete[]temp;
	temp = nullptr;
	delete[]left;
	left = nullptr;
	runner1 = nullptr;
	delete[]right;
	right = nullptr;
	runner2 = nullptr;
	rbeg = nullptr;
	end1 = nullptr;
	end2 = nullptr;
	porter = nullptr;
}

int main()
{
	cout << "ehter the length of the sequence: " << endl;
	int sz;
	cin >> sz;
	int *seq = new int[sz];
	cout << "enter the sequence :" << endl;
	for (int i = 0; i < sz; ++i) {
		cin >> *(seq + i);
	}
	//==============================================
	merge(seq, sz);
	print_seq(seq, sz);

	system("PAUSE");
    return 0;
}