#include "stdafx.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include "Stemmer.h"

#include "stdafx.h"
#include<io.h>
#include<ctime>
#include <windows.h>
using namespace std;

Stemmer::Stemmer()
{
	b = new char[INC];
	i = 0;
	i_end = 0;
}


Stemmer::~Stemmer()
{
	delete[]b;
}

void Stemmer::add(char ch)
{
	if (i == strlen(b))
	{
		char *new_b = new char[i + INC];
		for (int c = 0; c < i; c++)
			new_b[c] = b[c];
		b = new_b;
	}
	b[i++] = ch;
}

void Stemmer::add(char *w, int wLen)
{
	if (i + wLen >= strlen(b))
	{
		char* new_b = new char[i + wLen + INC];
		for (int c = 0; c < i; c++)
			new_b[c] = b[c];
		b = new_b;
	}
	for (int c = 0; c < wLen; c++)
		b[i++] = w[c];
}

char * Stemmer::toString()
{
	char* arr = new char[i_end];
	int temp = 0;
	for (temp = 0; temp < i_end; temp++)
		arr[temp] = b[temp];
	arr[temp] = '\0';
	return arr;
}

bool Stemmer::cons(int i)
{
	switch (b[i])
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
		return false;
	case 'y':
		return (i == 0) ? true : !cons(i - 1);
	default:
		return true;
	}
}

int Stemmer::m()
{
	int n = 0;
	int i = 0;
	while (true)
	{
		if (i > j)
			return n;
		if (!cons(i))
			break;
		i++;
	}
	i++;
	while (true)
	{
		while (true)
		{
			if (i > j)
				return n;
			if (cons(i))
				break;
			i++;
		}
		i++;
		n++;
		while (true)
		{
			if (i > j)
				return n;
			if (!cons(i))
				break;
			i++;
		}
		i++;
	}
}


bool Stemmer::vowelinstem()
{
	for (int i = 0; i <= j; i++)
		if (!cons(i))
			return true;
	return false;
}

bool Stemmer::doublec(int j)
{
	if (j < 1)
		return false;
	if (b[j] != b[j - 1])
		return false;
	return cons(j);
}

bool Stemmer::cvc(int i)
{
	if (i < 2 || !cons(i) || cons(i - 1) || !cons(i - 2))
		return false;
	int ch = b[i];
	if (ch == 'w' || ch == 'x' || ch == 'y')
		return false;

	return true;
}

bool Stemmer::ends(char *s)
{
	int l = strlen(s);
	int o = k - l + 1;
	if (o < 0)
		return false;
	for (int i = 0; i < l; i++)
		if (b[o + i] != s[i])
			return false;
	j = k - l;
	return true;
}

void Stemmer::setto(char *s)
{
	int l = strlen(s);
	int o = j + 1;
	for (int i = 0; i < l; i++)
		b[o + i] = s[i];
	k = j + l;
}

void Stemmer::r(char *s)
{
	if (m() > 0)
		setto(s);
}

void Stemmer::step1()
{
	if (b[k] == 's')
	{
		if (ends("sses"))
			k -= 2;
		else if (ends("ies"))
			setto("i");
		else if (b[k - 1] != 's')
			k--;
	}
	if (ends("eed"))
	{
		if (m() > 0)
			k--;
	}
	else if ((ends("ed") || ends("ing")) && vowelinstem())
	{
		k = j;
		if (ends("at"))
			setto("ate");
		else if (ends("bl"))
			setto("ble");
		else if (ends("iz"))
			setto("ize");
		else if (doublec(k))
		{
			k--;
			{
				int ch = b[k];

				if (ch == 'l' || ch == 's' || ch == 'z')
					k++;
			}
		}
		else if (m() == 1 && cvc(k))
			setto("e");
	}
}

void Stemmer::step2()
{
	if (ends("y") && vowelinstem())
		b[k] = 'i';
}

void Stemmer::step3()
{
	if (k == 0)
		return; /* For Bug 1 */
	switch (b[k - 1])
	{
	case 'a':
		if (ends("ational"))
		{
			r("ate");
			break;
		}
		if (ends("tional"))
		{
			r("tion");
			break;
		}
		break;
	case 'c':
		if (ends("enci"))
		{
			r("ence");
			break;
		}
		if (ends("anci"))
		{
			r("ance");
			break;
		}
		break;
	case 'e':
		if (ends("izer"))
		{
			r("ize");
			break;
		}
		break;
	case 'l':
		if (ends("bli"))
		{
			r("ble");
			break;
		}
		if (ends("alli"))
		{
			r("al");
			break;
		}
		if (ends("entli"))
		{
			r("ent");
			break;
		}
		if (ends("eli"))
		{
			r("e");
			break;
		}
		if (ends("ousli"))
		{
			r("ous");
			break;
		}
		break;
	case 'o':
		if (ends("ization"))
		{
			r("ize");
			break;
		}
		if (ends("ation"))
		{
			r("ate");
			break;
		}
		if (ends("ator"))
		{
			r("ate");
			break;
		}
		break;
	case 's':
		if (ends("alism"))
		{
			r("al");
			break;
		}
		if (ends("iveness"))
		{
			r("ive");
			break;
		}
		if (ends("fulness"))
		{
			r("ful");
			break;
		}
		if (ends("ousness"))
		{
			r("ous");
			break;
		}
		break;
	case 't':
		if (ends("aliti"))
		{
			r("al");
			break;
		}
		if (ends("iviti"))
		{
			r("ive");
			break;
		}
		if (ends("biliti"))
		{
			r("ble");
			break;
		}
		break;
	case 'g':
		if (ends("logi"))
		{
			r("log");
			break;
		}
	}
}

void Stemmer::step4()
{
	switch (b[k])
	{
	case 'e':
		if (ends("icate"))
		{
			r("ic");
			break;
		}
		if (ends("ative"))
		{
			r("");
			break;
		}
		if (ends("alize"))
		{
			r("al");
			break;
		}
		break;
	case 'i':
		if (ends("iciti"))
		{
			r("ic");
			break;
		}
		break;
	case 'l':
		if (ends("ical"))
		{
			r("ic");
			break;
		}

		if (ends("ful"))
		{
			r("");
			break;
		}
		break;
	case 's':
		if (ends("ness"))
		{
			r("");
			break;
		}
		break;
	}
}
void Stemmer::step5()
{
	if (k == 0)
		return; /* for Bug 1 */
	switch (b[k - 1])
	{
	case 'a':
		if (ends("al")) break; return;
	case 'c':
		if (ends("ance")) break;
		if (ends("ence")) break; return;
	case 'e':
		if (ends("er")) break; return;
	case 'i':
		if (ends("ic")) break; return;
	case 'l':
		if (ends("able")) break;
		if (ends("ible")) break; return;
	case 'n':
		if (ends("ant")) break;
		if (ends("ement")) break;
		if (ends("ment")) break;
		/* element etc. not stripped before the m */
		if (ends("ent")) break; return;
	case 'o':
		if (ends("ion") && j >= 0 && (b[j] == 's' || b[j] == 't')) break;
		/* j >= 0 fixes Bug 2 */
		if (ends("ou")) break; return;
		/* takes care of -ous */
	case 's':
		if (ends("ism")) break; return;
	case 't':
		if (ends("ate")) break;
		if (ends("iti")) break; return;
	case 'u':
		if (ends("ous")) break; return;
	case 'v':
		if (ends("ive")) break; return;
	case 'z':
		if (ends("ize")) break; return;
	default:
		return;
	}
	if (m() > 1)
		k = j;
}

void Stemmer::step6()
{
	j = k;
	if (b[k] == 'e')
	{
		int a = m();
		if (a > 1 || a == 1 && !cvc(k - 1))
			k--;
	}
	if (b[k] == 'l' && doublec(k) && m() > 1)
		k--;
}

void Stemmer::stem()
{
	k = i - 1;
	if (k > 1)
	{
		step1();
		step2();
		step3();
		step4();
		step5();
		step6();
	}
	i_end = k + 1;
	i = 0;
}
char lower(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch = ch + 32;
	return ch;
}
bool is_alpha(char ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	return false;
}
bool myfunction(words_list w1, words_list w2)
{

	return (w2.words > w1.words);
}
bool myfunction_index(word_index w1, word_index w2)
{
	return (w2.words > w1.words);
}
char * Stemmer::words_class()
{
	stem();
	return toString();
}


vector<word_index> Stemmer::find_words(string files)
{
	char* w = new char[501];
	Stemmer s;

	ifstream icin;
	unsigned int icin_start, icin_j = -1;
	icin.open(files.c_str());
	vector<word_index> words;
	while (true)
	{

		int ch;
		ch = icin.get();
		icin_j++;
		icin_start = icin_j;
		if (!ch)
		{
			cout << "error reading " << files.c_str();
			break;
		}
		if (is_alpha((char)ch))
		{
			int len = 0;
			while (true)
			{
				ch = lower(char(ch));
				w[len] = (char)ch;
				if (len < 500)
					len++;
				ch = icin.get();
				icin_j++;
				if (!ch)
				{
					cout << "error reading " << files.c_str();
					break;
				}
				if (!is_alpha((char)ch))
				{
					/* to test add(char ch) */
					for (int c = 0; c < len; c++)
						s.add(w[c]);

					char *u = s.words_class();
					word_index temp;
					temp.index = icin_start;
					temp.words = u;
					words.push_back(temp);
					//cout<<u<<endl;

					break;
				}
			}
		}
		if (ch < 0)
			break;

	}
	icin.close();
	delete[]w;

	return words;
}
vector<words_list> Stemmer::count_in_file(string file_name, vector<word_index> words)
{
	int sum = 1;
	int words_size = words.size();
	int* count = new int[words_size + 1];
	count[0] = sum;
	//for (int size_i = 1; size_i < words.size(); size_i++)
	//{
	//	if (words[size_i].words == words[size_i - 1].words)
	//	{
	//		count[size_i - 1]++;
	//		words.erase(words.begin() + size_i);
	//		size_i--;
	//	}
	//	else
	//		count[size_i] = sum;

	//}

	vector<words_list> cur_file;
	for (int size_i = 0; size_i < words.size(); size_i++)
	{
		words_list temp;
		temp.index = words[size_i].index;
		temp.words = words[size_i].words;
		//temp.count = count[size_i];
		temp.count = 1;
		temp.file_name = file_name;
		cur_file.push_back(temp);

		//cout << (cur_file[size_i]).index << " : " << (cur_file[size_i]).words << "  " << (cur_file[size_i]).count << "   " << (cur_file[i]).file_name << endl;
	}
	delete[]count;
	//cout << "count "<<words.size()<<" files done!\n";
	return cur_file;
}
void Stemmer::write_az(vector<words_list> list)
{
	string filePath = "C:\\data\\A_Zdata\\a.txt";
	int len = filePath.length();

	int list_i = 0;
	for (char a_z = 'a'; a_z <= 'z'; a_z++)
	{
		filePath[len - 5] = a_z;
		fstream icin;
		icin.open(filePath, fstream::out | ifstream::app);
		if (!icin)
		{
			cout << "fiel: " << filePath << " can not be opened" << endl;
			return;
		}
		for (list_i; list_i < list.size(); list_i++)
		{
			string word = list[list_i].words;
			if (word[0] == a_z)
				icin << list[list_i].index << "  " << list[list_i].words << "  " << list[list_i].count << "  " << list[list_i].file_name << "\n";
			else if (word[0] > a_z)
				break;
		}
		icin.close();
	}
	//cout << "write a_z done!\n";
}

void Stemmer::sort_in_az(vector<string>& files)
{
	for (int files_i = 0; files_i < files.size(); files_i++)
	{
		fstream icin;
		icin.open(files[files_i], fstream::in);
		if (!icin)
		{
			cout << "fiel: " << files[files_i] << " can not be opened" << endl;
			return;
		}
		vector<words_list> list_in_az;

		while (!icin.eof())
		{
			words_list temp;
			icin >> temp.index >> temp.words >> temp.count >> temp.file_name;
			list_in_az.push_back(temp);
		}
		icin.close();


		cout << files[files_i] << " is sorting...\n";
		sort(list_in_az.begin(), list_in_az.end(), myfunction);

		icin.open(files[files_i], fstream::out | ios::trunc);
		if (!icin)
		{
			cout << "fiel: " << files[files_i] << " can not be opened" << endl;
			return;
		}
		for (int list_j = 1; list_j < list_in_az.size(); list_j++)
		{
			//string word = list_in_az[list_j].words;

			icin << list_in_az[list_j].index << "  " << list_in_az[list_j].words << "  " << list_in_az[list_j].count << "  " << list_in_az[list_j].file_name << "\n";
			//icin << list_in_az[list_j].index << "  " << list_in_az[list_j].words << "  " << list_in_az[list_j].count << "  " << list_in_az[list_j].file_name << "\n";

		}
		cout << files[files_i] << " has been sorted.\n";
		icin.close();
	}
}

string Stemmer::result_word(string a)
{
	char *word = new char[a.length() + 1];
	int len = 0;
	while (len < a.length()){
		word[len] = a[len];
		len++;
	}
	word[len] = '\0';


	b = word;
	i = a.length();
	//cout << "befor word_class: " << word << endl;
	char *u = words_class();
	string res = u;

	//cout << "after word_class: " << res << endl;
	return res;
}


void Stemmer::files_main(vector<string>& files)
{
	for (int files_num = 0; files_num < files.size(); files_num++)
	{
		vector<word_index> words_string = find_words(files[files_num]);

		sort(words_string.begin(), words_string.end(), myfunction_index);
		//for (int i = 0; i < words_string.size(); i++)
		//	cout << words_string.at(i) << endl;
		//system("pause");

		vector<words_list> list = count_in_file(files[files_num], words_string);
		write_az(list);
		cout << files_num << endl;
		//system("pause");
	}

}

void Stemmer::getFiles(string path, vector<string>& files)
{
	long hFile = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

}


vector<words_list> Stemmer::find_in_file(string filePath3, string word, int count)
{
	fstream icin;
	icin.open(filePath3, fstream::in);
	if (!icin)
	{
		cout << "file " << filePath3 << " can not be opened!" << endl;
		vector<words_list> list;
		return list;
	}
	bool find = false;
	words_list temp;
	vector<words_list> list;
	while (!icin.eof())
	{
		icin >> temp.index >> temp.words >> temp.count >> temp.file_name;
		if (temp.words == word)
		{
			find = true;
			break;
		}
	}

	if (find)
	{
		list.push_back(temp);
		if (temp.count < count)
		{
			int temp_count = temp.count;
			while (temp_count < count && !icin.eof())
			{
				icin >> temp.index >> temp.words >> temp.count >> temp.file_name;
				if (temp.words == word)
				{
					list.push_back(temp);
					temp_count += temp.count;
				}
				else
				{
					cout << "There are only " << temp_count << " " << word << endl;
					break;
				}
			}

		}

		for (int list_i = 0; list_i < list.size(); list_i++)
			cout << list[list_i].index << " " << list[list_i].words << " " << list[list_i].count << " " << list[list_i].file_name << endl;
	}
	else
		cout << word << " can not be find in thoese files\n";


	return list;
}

string Stemmer::cout_find(vector<words_list> list, int list_i)
{
	int len = list.size();
	string temp;
	if (list_i > len - 1)
		return temp;
	fstream icin;
	icin.open(list[list_i].file_name, ios::in);
	icin.seekg(list[list_i].index, ios::beg);

	string words;
	char ch;
	//icin.getline(words);
	icin >> noskipws;
	icin >> ch;

	int icin_i = 1;
	if (icin_i < list[list_i].index)
		icin.seekg(-1, ios::cur);
	while (icin_i < list[list_i].index)
	{
		icin >> ch;
		if (ch != '.')
			icin_i++;
		else
			break;
		icin.seekg(-2, ios::cur);

	}
	ch = 'a';
	while (ch != '.'&&!icin.eof())
	{
		icin >> ch;
		words.push_back(ch);

	}
	icin.close();

	return words;
}
vector<words_list> Stemmer::read_in_file(string filePath, string word)
{
	fstream icin;
	icin.open(filePath, fstream::in);
	if (!icin)
	{
		cout << "file " << filePath << " can not be opened!" << endl;
		vector<words_list> list;
		return list;
	}
	bool find = false;
	words_list temp;
	vector<words_list> list;

	while (!icin.eof())
	{
		icin >> temp.index >> temp.words >> temp.count >> temp.file_name;
		if (temp.words == word)
		{
			find = true;
			list.push_back(temp);
		}
		else
		{
			if (find)
				break;
		}
	}
	if (!find)
		cout << "There is no " << word << " in thoese files." << endl;
	icin.close();

	return list;
}
vector<words_list> Stemmer::find_in_two(string filePath3, string filePath4, string res_worda, string res_wordb, int num)
{

	vector<words_list> list_a = read_in_file(filePath3, res_worda);
	vector<words_list> list_b = read_in_file(filePath4, res_wordb);
	vector<words_list> list;
	int count_num = 0;
	string words;
	for (int a = 0; a < list_a.size(); a++)
	{
		for (int b = 0; b < list_b.size(); b++)
		{
			if (count_num >= num)
				return list;
			int len = abs(list_a[a].index - list_b[b].index);
			if (list_a[a].file_name == list_b[b].file_name && len < 50)
			{
				ifstream icin;
				char ch;
				icin.open(list_a[a].file_name, ios::in);
				icin.seekg(list_a[a].index, ios::beg);
				icin >> noskipws;
				int len_i = 0;
				for (len_i = 0; len_i < len; len_i++)
				{
					icin >> ch;
					if (ch == '.')
						break;
				}
				if (len_i < len)
					continue;
				count_num++;
				int icin_i = 1;
				if (icin_i < list_a[a].index)
					icin.seekg(-1, ios::cur);
				while (icin_i < list_a[a].index)
				{
					icin >> ch;
					if (ch != '.')
						icin_i++;
					else
						break;
					icin.seekg(-2, ios::cur);
				}
				ch = 'a';
				
				while (ch != '.'&&!icin.eof())
				{
					icin >> ch;
					words.push_back(ch);
				}
				words_list temp;
				temp.index = list_a[a].index;
				temp.file_name = list_a[a].file_name;
				temp.words = words;
				temp.count = count_num;
				list.push_back(temp);				
			}
		}
	}
	
	return list;
}


