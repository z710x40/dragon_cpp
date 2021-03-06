#include "DragonFileManager.h"
#include "DragonActionRecord.h"

#include <dirent.h>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <fstream>
#include <ostream>
#include <stdlib.h>
#include <time.h>


DragonFileManager::DragonFileManager()
{
    cerr<<"DragonFileManager: Starting the DragonFileManager"<<endl;
    srand (time(NULL));
}

DragonFileManager::~DragonFileManager()
{
    //dtor
}

//vector<string> DragonFileManager::__dirList;


void DragonFileManager::loadActionNamesList()
{
    std::cerr<<"DragonFileManager: open dir "<<currentpath_<<endl;

    struct dirent *ent;
    DIR *dir;
    dir = opendir(currentpath_);

    while( (ent = readdir(dir)) != NULL)
    {
        if( ( ent->d_type == DT_DIR ) & ( ent->d_name[0] != '.') )
        {
            DragonActionRecord temp(currentpath_,ent->d_name);
            dragonActionRecordList_.push_back(temp);
        }
    };

    cerr<<"DragonFileManager: loaded "<<dragonActionRecordList_.size()<<" actions\n";
}

// Set the corent path for the loading of the action, could be placed in the constructor
void DragonFileManager::setCurrentPath(char* newPath)
{
    currentpath_ = newPath;
}


unsigned int* DragonFileManager::seqLineToIntPtr(string line)
{
	cerr<<"DragonFileManager: seqLineToIntPtr from "<<line<<" \n" ;
	unsigned int seqStep[16];
	for(int tel = 0;tel<15;tel++)
	{
		seqStep[tel] = stoi(line.substr(tel*4,4+tel*4));
	}
	return seqStep;
}

// Select an action based on the actionType
void DragonFileManager::defineRandomAction(int selectedActionType)
{
  while(true)
  {	  
  	currentAction_ = (int)rand()%dragonActionRecordList_.size();
	if(dragonActionRecordList_[currentAction_].getActionType()==selectedActionType)
	{
		cerr<<"DragonFileManager: selected "<<dragonActionRecordList_[currentAction_].getActionName()<<"\n";
		return;
	}
  }
}


string DragonFileManager::getCurrentWaveFile()
{
	cerr<<"DragonFileManager: ask for "<<dragonActionRecordList_[currentAction_].getWaveName()<<endl;
	return dragonActionRecordList_[currentAction_].getWaveName();
}

string DragonFileManager::getCurrentSequenceFile()
{
	return dragonActionRecordList_[currentAction_].getSeqName();
}

int  DragonFileManager::getCurrentSequenceSteps()
{
	return dragonActionRecordList_[currentAction_].getNumberOfSteps();
}

DragonActionLine* DragonFileManager::getCurrentActionServoSteps(int pos)
{
	return dragonActionRecordList_[currentAction_].getActionAt(pos);
}

