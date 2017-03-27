#include<string>
#include <vector>
using namespace std;
#pragma once
class word_index
{
public:
	int index;
	string words;
};
class words_list :public word_index
{
public:
	int count;
	string file_name;
};
class Stemmer
{
public:
	char *b;
	int i;
	int i_end;
	int j;
	int k;
	//static int INC;
public:
	Stemmer();
	~Stemmer();
	/**
	* Add a character to the word being stemmed.  When you are finished
	* adding characters, you can call stem(void) to stem the word.
	*/
	void add(char ch);

	/** Adds wLen characters to the word being stemmed contained in a portion
	* of a char[] array. This is like repeated calls of add(char ch), but
	* faster.
	*/
	void add(char* w, int wLen);


	/**
	* After a word has been stemmed, it can be retrieved by toString(),
	* or a reference to the internal buffer can be retrieved by getResultBuffer
	* and getResultLength (which is generally more efficient.)
	*/
	char *toString();


	/* cons(i) is true <=> b[i] is a consonant. */
private:
	bool cons(int i);

	/* m() measures the number of consonant sequences between 0 and j. if c is
	a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
	presence,

	<c><v>       gives 0
	<c>vc<v>     gives 1
	<c>vcvc<v>   gives 2
	<c>vcvcvc<v> gives 3
	....
	*/

	int m();

	/* vowelinstem() is true <=> 0,...j contains a vowel */

	bool vowelinstem();

	/* doublec(j) is true <=> j,(j-1) contain a double consonant. */

	bool doublec(int j);


	/* cvc(i) is true <=> i-2,i-1,i has the form consonant - vowel - consonant
	and also if the second c is not w,x or y. this is used when trying to
	restore an e at the end of a short word. e.g.

	cav(e), lov(e), hop(e), crim(e), but
	snow, box, tray.

	*/

	bool cvc(int i);

	bool ends(char * s);


	/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
	k. */

	void setto(char* s);
	/* r(s) is used further down. */

	void r(char* s);


	/* step1() gets rid of plurals and -ed or -ing. e.g.

	caresses  ->  caress
	ponies    ->  poni
	ties      ->  ti
	caress    ->  caress
	cats      ->  cat

	feed      ->  feed
	agreed    ->  agree
	disabled  ->  disable

	matting   ->  mat
	mating    ->  mate
	meeting   ->  meet
	milling   ->  mill
	messing   ->  mess

	meetings  ->  meet

	*/

	void step1();

	/* step2() turns terminal y to i when there is another vowel in the stem. */

	void step2();

	/* step3() maps double suffices to single ones. so -ization ( = -ize plus
	-ation) maps to -ize etc. note that the string before the suffix must give
	m() > 0. */

	void step3();

	/* step4() deals with -ic-, -full, -ness etc. similar strategy to step3. */

	void step4();

	/* step5() takes off -ant, -ence etc., in context <c>vcvc<v>. */

	void step5();

	/* step6() removes a final -e if m() > 1. */

	void step6();

	/** Stem the word placed into the Stemmer buffer through calls to add().
	* Returns true if the stemming process resulted in a word different
	* from the input.  You can retrieve the result with
	* getResultLength()/getResultBuffer() or toString().
	*/
public:
	void stem();

	char * words_class();

	/** Test program for demonstrating the Stemmer.  It reads text from a
	* a list of files, stems each word, and writes the result to standard
	* output. Note that the word stemmed is expected to be in lower case:
	* forcing lower case must be done outside the Stemmer class.
	* Usage: Stemmer file-name file-name ...
	*/
	void files_main(vector<string>& files);
	vector<word_index> find_words(string file_name);

	vector<words_list>count_in_file(string file_name, vector<word_index> words);

	void write_az(vector<words_list> list);

	void sort_in_az(vector<string>& files);
	string result_word(string a);

	void getFiles(string path, vector<string>& files);

	string cout_find(vector<words_list> list, int list_i);
	vector<words_list> find_in_file(string filePath3, string word, int count);
	vector<words_list> read_in_file(string filePath, string word);
	vector<words_list> find_in_two(string filePath3, string filePath4, string res_worda, string res_wordb, int num);

};

char lower(char ch);
bool is_alpha(char ch);
bool myfunction(words_list w1, words_list w2);
bool myfunction_index(word_index w1, word_index w2);
//int Stemmer::INC = 50;
static int INC = 50;