#include "SceneManager.h"
#define NUMBER_PLAY_TOSHOW_ADV 5
inline int ToInt(const char* number)
{
	char *end;
	int value = strtol(number, &end, 10);
	if (end == number || *end != '\0' || errno == ERANGE)
		return 0;
	else
		return value;
}

void SceneManager::setScale(const float& kx, const float& ky)
{
	_kX = kx;
	_kY = ky;
	_minWidth = MIN(Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
	_isInit = false;
}

void SceneManager::setInfoDb()
{
	if (_isInit == true)
		return;
	_isInit = true;
	_totalPlayMission = 0;
	_isAdv = false;

	///// for testing
	//_mapLocker[MAP_3] = 0;
	//_mapLocker[MAP_4] = 0;
	//_mapLocker[MAP_5] = 0;
	//return;
	///// for testing

	_mapLocker[MAP_3] = 0;
	_mapLocker[MAP_4] = -1;
	_mapLocker[MAP_5] = -1;

	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map3.db";
	if (cocos2d::FileUtils::sharedFileUtils()->isFileExist(path) == true)
	{
		FILE* f = fopen(path.c_str(), "r");
		char buf1[12] = { 0 };
		if (!f)
		{//CCLOG("can not open file %s", path.c_str());
		}
		else
		{
			fgets(buf1, 12, f);
			// convert buf to int -> _maxmap -> read each file
			_mapLocker[MAP_3] = ToInt(buf1);
		}
		fclose(f);
	}
	else
		return;
		
	if (_mapLocker[MAP_3] > 0)
		_mapLocker[MAP_4] = 0;
	
	//// for 4
	path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map4.db";
	if (cocos2d::FileUtils::sharedFileUtils()->isFileExist(path) == true){
		_mapLocker[MAP_4] = 0;
		FILE* f = fopen(path.c_str(), "r");
		char buf2[12] = { 0 };
		if (!f)
		{//CCLOG("can not open file %s", path.c_str());
		}
		else
		{
			fgets(buf2, 12, f);
			// convert buf to int -> _maxmap -> read each file
			_mapLocker[MAP_4] = ToInt(buf2);
		}
		fclose(f);
	}
	else
		return;

	if (_mapLocker[MAP_4] > 0)
		_mapLocker[MAP_5] = 0;
	//// for 5
	path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map5.db";
	if (cocos2d::FileUtils::sharedFileUtils()->isFileExist(path) == true){	
		_mapLocker[MAP_5] = 0;
		FILE* f = fopen(path.c_str(), "r");
		char buf3[12] = { 0 };
		if (!f)
		{//CCLOG("can not open file %s", path.c_str());
		}
		else
		{
			fgets(buf3, 12, f);
			// convert buf to int -> _maxmap -> read each file
			_mapLocker[MAP_5] = ToInt(buf3);
		}
		fclose(f);
	}
	else
		return;
}

int SceneManager::getScoreMapOrLock(const int&  mapNumber) const
{
	return _mapLocker[mapNumber];
}

void SceneManager::writeScoreToMap3(const int& numberClick)
{
	if (_mapLocker[MAP_3] > 0 && _mapLocker[MAP_3] < numberClick)
		return;
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map4.db";
	if (_mapLocker[MAP_4] < 0)
	{
		_mapLocker[MAP_4] = 0;
		FILE *fp1 = fopen(path.c_str(), "w");
		if (!fp1)
		{
			//CCLOG("can not open file %s", path.c_str());
		}
		else
		{
			fputs("0", fp1);
		}
		fclose(fp1);
	}

	_mapLocker[MAP_3] = numberClick;
	path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map3.db";
	FILE *fp = fopen(path.c_str(), "w");
	char numStr[12] = { 0 };
	sprintf(numStr, "%d", numberClick);
	if (!fp)
	{
		//CCLOG("can not open file %s", path.c_str());
	}
	else
	{
		fputs(numStr, fp);
	}
	fclose(fp);
}

void SceneManager::writeScoreToMap4(const int& numberClick)
{
	if (_mapLocker[MAP_4] > 0 && _mapLocker[MAP_4] < numberClick)
		return;
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map5.db";
	if (_mapLocker[MAP_5] < 0)
	{
		_mapLocker[MAP_5] = 0;
		FILE *fp1 = fopen(path.c_str(), "w");
		if (!fp1)
		{
			//CCLOG("can not open file %s", path.c_str());
		}
		else
		{
			fputs("0", fp1);
		}
		fclose(fp1);
	}

	_mapLocker[MAP_4] = numberClick;
	path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map4.db";
	FILE *fp = fopen(path.c_str(), "w");
	char numStr[12] = { 0 };
	sprintf(numStr, "%d", numberClick);
	if (!fp)
	{
		//CCLOG("can not open file %s", path.c_str());
	}
	else
	{
		fputs(numStr, fp);
	}
	fclose(fp);
}

void SceneManager::writeScoreToMap5(const int& numberClick)
{
	_mapLocker[MAP_5] = numberClick;
	std::string path = cocos2d::FileUtils::sharedFileUtils()->getWritablePath() + "185164782_map5.db";
	FILE *fp = fopen(path.c_str(), "w");
	char numStr[12] = { 0 };
	sprintf(numStr, "%d", numberClick);
	if (!fp)
	{
		//CCLOG("can not open file %s", path.c_str());
	}
	else
	{
		fputs(numStr, fp);
	}
	fclose(fp);
}

void SceneManager::setAdvAvaiable()
{
	if (++_totalPlayMission > NUMBER_PLAY_TOSHOW_ADV)
	{
		_isAdv = true;
	}
}

SceneManager* SceneManager::_instance = NULL;

