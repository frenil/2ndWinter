#pragma once
#include "stdafx.h"
class Key
{
	int Keyname;
	int Condition;
	float time;
public:
	Key(int n,int c,float t):Keyname(n),Condition(c),time(t){}
	Key() {}
	~Key() {}
	int GetName() { return Keyname; }
	int GetCondition() { return Condition; }
	float GetTime() { return time; }

};
class CSaveKey
{
	list<Key> savebutton;
public:
	CSaveKey();
	~CSaveKey();
	void UpdateKey(int name, int con,float time){
		savebutton.push_back(Key(name, con, time));
	}
	void KeyLoad();
	void KeySave();
	Key POPKey() { 
		Key temp = savebutton.front();
		savebutton.pop_front();
		return temp; 
	}
	void Clear() { savebutton.clear(); }
	bool isEnd() { return (savebutton.begin() == savebutton.end()); }
	float GetTime() { return savebutton.front().GetTime(); }
};

