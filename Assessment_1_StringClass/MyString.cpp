#include "MyString.h"

MyString::~MyString()
{
	if (m_MyString != nullptr) {
		delete[] m_MyString;
	}
}

MyString::MyString(const char * str)
{
	m_MyString = new char[strlen(str) + 1];
	for (int i = 0; i <= strlen(m_MyString); i++) {
		m_MyString[i] = str[i];
	}
	m_MyString[strlen(m_MyString)] = '\0';
}

MyString::MyString(const unsigned int i)
{
	m_MyString = new char[i];
	setCharAtIndex(0, '\0');
}

MyString::MyString()
{
	m_MyString = new char[1];
	setCharAtIndex(0, '\0');
}

MyString::MyString(MyString & str)
{
	if (m_MyString == '\0') {
		delete[] m_MyString;
	}
	m_MyString = new char[str.getLength() + 1];
	for (int i = 0; i < strlen(m_MyString); i++) {
		m_MyString[i] = str.getCharAtIndex(i);
	}
	m_MyString[strlen(m_MyString)] = '\0';
}

MyString & MyString::operator=(const MyString & rhs)
{
	if (m_MyString == '\0') {
		delete[] m_MyString;
	}
	m_MyString = new char[rhs.getLength() + 1];
	for (unsigned int i = 0; i < rhs.getLength() + 1; i++) {
		m_MyString[i] = rhs.getCharAtIndex(i);
	}
	return *this;
}

MyString & MyString::operator=(const char *& rhs)
{
	if (m_MyString == '\0') {
		delete[] m_MyString;
	}
	m_MyString = new char[strlen(rhs) + 1];
	for (int i = 0; i < strlen(rhs) + 1; i++) {
		m_MyString[i] = rhs[i];
	}
	return *this;
}

const bool MyString::operator==(const char * rhs)
{
	bool answer = false;
	MyString newString = rhs;
	if ((stringCompare(newString)) == 0) {
		answer = true;
	}
	return answer;
}

const bool MyString::operator==(MyString & rhs)
{
	bool answer = false;
	if (stringCompare(rhs) == 0) {
		answer = true;
	}
	return answer;
}

void MyString::setString(const char * str)
{
	m_MyString = new char[strlen(str) + 1];
	for (int i = 0; i <= strlen(m_MyString); i++) {
		m_MyString[i] = str[i];
	}
	m_MyString[strlen(m_MyString)] = '\0';
}

void MyString::setString(MyString str)
{
	m_MyString = new char[strlen(str.stringOutput()) + 1];
	for (int i = 0; i <= strlen(m_MyString); i++) {
		m_MyString[i] = str.getCharAtIndex(i);
	}
	m_MyString[strlen(m_MyString)] = '\0';
}

const char * MyString::stringOutput()
{
	return m_MyString;
}

unsigned int MyString::getLength() const
{
	unsigned int length = 0;
	unsigned int i = 0;
	while (true) {
		if (m_MyString[i] != '\0') {
			length++;
		}
		else {
			break;
		}
		i++;
	}
	return length;
}

char MyString::getCharAtIndex(unsigned int i) const
{
	return m_MyString[i];
}

void MyString::setCharAtIndex(unsigned int i, char c) const
{
	m_MyString[i] = c;
}

int MyString::stringCompare(MyString& strB) const
{
	int answer = 2;
	MyString string1 = m_MyString;
	MyString string2 = strB;
	//convert to lower case for accurate comparison
	string1 = string1.toLowercase();
	string2 = string2.toLowercase();
	for (unsigned int i = 0; i < string1.getLength(); i++) {
		/*Check if second string ends at index, before first string.
		If it does, string 1 comes after, lexographically*/
		if (string2.getCharAtIndex(i) == '\0') {
			answer = 1;
			break;
		}
		else {
			if (string1.getCharAtIndex(i) == string2.getCharAtIndex(i)) {
				answer = 0;
				/*If all is same up until index, check that string2 doesnt carry on
				after the null terminator.
				If it does, string 2 comes after, lexographically*/
				if (i == string1.getLength() - 1 && string2.getCharAtIndex(i + 1) != '\0') {
					answer = -1;
					break;
				}
			}
			else if (string1.getCharAtIndex(i) > string2.getCharAtIndex(i)) {
				answer = 1;
				break;
			}
			else {
				answer = -1;
				break;
			}
		}
	}
	return answer;
}

int MyString::stringCompare(const char *& strB) const
{
	int answer = 2;
	MyString string1 = m_MyString;
	MyString string2 = strB;
	//convert to lower case for accurate comparison
	string1 = string1.toLowercase();
	string2 = string2.toLowercase();
	for (unsigned int i = 0; i < string1.getLength(); i++) {
		/*Check if second string ends at index, before first string.
		If it does, string 1 comes after, lexographically*/
		if (string2.getCharAtIndex(i) == '\0') {
			answer = 1;
			break;
		}
		else {
			if (string1.getCharAtIndex(i) == string2.getCharAtIndex(i)) {
				answer = 0;
				/*If all is same up until index, check that string2 doesnt carry on
				after the null terminator.
				If it does, string 2 comes after, lexographically*/
				if (i == string1.getLength() - 1 && string2.getCharAtIndex(i + 1) != '\0') {
					answer = -1;
					break;
				}
			}
			else if (string1.getCharAtIndex(i) > string2.getCharAtIndex(i)) {
				answer = 1;
				break;
			}
			else {
				answer = -1;
				break;
			}
		}
	}
	return answer;
}

MyString MyString::toLowercase()
{
	MyString result(getLength() + 1);
	result = m_MyString;
	for (unsigned int i = 0; i < getLength(); i++) {
		if (m_MyString[i] == '\0') {
			//end of array
		}
		else if (m_MyString[i] >= 65 && m_MyString[i] <= 90) {
			//is capital
			result.setCharAtIndex(i, (result.getCharAtIndex(i) + 32));
		}
	}
	return result;
}

MyString MyString::toUppercase()
{
	MyString result(getLength() + 1);
	result = m_MyString;
	for (unsigned int i = 0; i < getLength(); i++) {
		if (m_MyString[i] == '\0') {
			//end of array
		}
		else if (m_MyString[i] >= 97 && m_MyString[i] <= 122) {
			//is capital
			result.setCharAtIndex(i, (result.getCharAtIndex(i) - 32));
		}
	}
	return result;
}

MyString MyString::stringAppend(MyString strB)
{
	MyString result((getLength()) + (strB.getLength()) + 1);
	result.setCharAtIndex(0, '\0');
	unsigned int i = 0, ii = 0;
	//fill result with the first string, up to null terminator
	while (true) {
		if (m_MyString[i] != '\0') {
			result.setCharAtIndex(i, m_MyString[i]);
			result.setCharAtIndex(i + 1, '\0');
		}
		else {
			break;
		}
		i++;
	}
	//add second string on to the end of result
	while (true) {
		if (strB.getCharAtIndex(ii) != '\0') {
			result.setCharAtIndex(i, strB.getCharAtIndex(ii));
			result.setCharAtIndex(i + 1, '\0');
		}
		else {
			break;
		}
		ii++;
		i++;
	}
	return result;
}

MyString MyString::stringPrepend(MyString strB)
{
	MyString result((getLength()) + (strB.getLength()) + 1);
	result.setCharAtIndex(0, '\0');
	unsigned int i = 0, ii = 0;
	//fill result with the first string, up to null terminator
	while (true) {
		if (strB.getCharAtIndex(i) != '\0') {
			result.setCharAtIndex(i, strB.getCharAtIndex(i));
			result.setCharAtIndex(i + 1, '\0');
		}
		else {
			break;
		}
		i++;
	}
	//add second string on to the end of result
	while (true) {
		if (m_MyString[ii] != '\0') {
			result.setCharAtIndex(i, m_MyString[ii]);
			result.setCharAtIndex(i + 1, '\0');
		}
		else {
			break;
		}
		ii++;
		i++;
	}
	return result;
}

int MyString::find(const char * c) const
{
	int result = -1; //If character not found, returns -1 as error
	bool same = false;
	for (unsigned int i = 0; i < (getLength() + 1); i++) {
		if (getCharAtIndex(i) == c[0]) {
			same = true;
			for (int k = 1; k < (strlen(c)); k++) {
				if (getCharAtIndex(i + k) == c[k]) {
					same = true;
				}
				else {
					same = false;
					break;
				}
			}
		}
		if (same == true) {
			result = i;
			break;
		}
	}
	return result;
}

int MyString::find(const char * c, int startPosition) const
{
	int result = -1; //If character not found, returns -1 as error
	bool same = false;
	for (unsigned int i = startPosition; i < (getLength() + 1); i++) {
		if (getCharAtIndex(i) == c[0]) {
			same = true;
			for (int k = 1; k < (strlen(c)); k++) {
				if (getCharAtIndex(i + k) == c[k]) {
					same = true;
				}
				else {
					same = false;
					break;
				}
			}
		}
		if (same == true) {
			result = i;
			break;
		}
	}
	return result;
}

MyString MyString::subString(const unsigned int position, unsigned int returnAmount) const
{
	MyString result(returnAmount + 1);
	unsigned int i = position;
	while (i < (position + returnAmount)) {
		result.setCharAtIndex((i - position), getCharAtIndex(i));
		result.setCharAtIndex((i - position + 1), '\0');
		i++;
	}
	return result;
}

MyString MyString::subString(const unsigned int position) const
{
	MyString result(getLength() - position + 1);
	unsigned int i = position;
	while (i < getLength()) {
		result.setCharAtIndex((i - position), getCharAtIndex(i));
		result.setCharAtIndex((i - position + 1), '\0');
		i++;
	}
	return result;
}

MyString MyString::subReplace(const unsigned int position, const unsigned int replaceAmount, char * replacementSubString)
{
	MyString result((getLength() - replaceAmount) + (const int(strlen(replacementSubString))) + 1);
	result = subString(0, position);
	result = result.stringAppend(replacementSubString);
	result = result.stringAppend(subString(position + replaceAmount));
	return result;
}

MyString MyString::setToString(std::string str)
{
	if (m_MyString == '\0') {
		delete[] m_MyString;
	}
	m_MyString = new char[str.length() + 1];
	for (int i = 0; i <= strlen(m_MyString); i++) {
		m_MyString[i] = str[i];
	}
	m_MyString[strlen(m_MyString)] = '\0';
	return *this;
}