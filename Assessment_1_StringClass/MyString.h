#pragma once
#include <iostream>
class MyString {
private:
	char* m_MyString;
public:
	~MyString();
	MyString(char* str);
	MyString(const unsigned int i);
	MyString();

	MyString(MyString& str);

	MyString& operator=(const MyString& rhs);
	MyString& operator=(char* rhs);
	const bool operator== (char* rhs);
	const bool operator== (MyString& rhs);
	const bool operator!= (char* rhs);
	const bool operator!= (MyString& rhs);

	void setString(const char* str);
	void setString(MyString str);
	char* stringOutput();

	unsigned int getLength() const;
	char getCharAtIndex(unsigned int i) const;
	void setCharAtIndex(unsigned int i, char c) const;
	int stringCompare(MyString& strB) const;
	int stringCompare(char*& strB) const;

	MyString toLowercase();
	MyString toUppercase();

	MyString stringAppend(MyString strB);
	MyString stringPrepend(MyString strB);

	int find(char* c) const;
	int find(char* c, int startPosition) const;
	MyString subString(const unsigned int position, unsigned int returnAmount) const;
	MyString subString(const unsigned int position) const;
	MyString subReplace(const unsigned int position, const unsigned int replaceAmount, char* replacementSubString);
	MyString setToString(std::string str);
};