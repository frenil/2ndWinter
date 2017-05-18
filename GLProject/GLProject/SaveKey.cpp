#include "stdafx.h"
#include "SaveKey.h"



CSaveKey::CSaveKey()
{
}


CSaveKey::~CSaveKey()
{
}

void CSaveKey::KeyLoad()
{
	savebutton.clear();
	ifstream ifs("Key_data.txt");
	Key temp;
	int name;
	int con;
	float time;
	while (ifs)
	{
		ifs >> name >> con >> time;
		savebutton.push_back(Key(name, con, time));
	}
}

void CSaveKey::KeySave()
{
	ofstream ofs("Key_data.txt");
	Key temp;
	for (auto d : savebutton) {
		temp = d;
		ofs << temp.GetName() << " " << temp.GetCondition() << " " << temp.GetTime() << endl;
	}
	ofs.close();
}
