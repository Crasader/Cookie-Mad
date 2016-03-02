#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "define.h"

#define MAP_3 0
#define MAP_4 1
#define MAP_5 2

#define TINI_DEVICE 1
#define MINI_DEVICE 2
#define MED_DEVICE 3
#define DEVICE_7INCH 4
#define DEVICE_9INCH 5

class SceneManager
{
public:
	static SceneManager* Instance()
	{
		if (_instance == NULL)
		{
			_instance = new SceneManager();
		}
		return _instance;
	}
	void setScale(const float& kx, const float& ky);
	//void setYScale(const float& k);

	float getXScale() const{ return _kX; }
	float getYScale() const{ return _kY; }

	float getSizeOfSquare() { return _minWidth; }

	void setInfoDb();
	int getScoreMapOrLock (const int& mapNumber)const;
	bool isAdvAvaiable() const{ return _isAdv; }

	void writeScoreToMap3(const int& numberClick);
	void writeScoreToMap4(const int& numberClick);
	void writeScoreToMap5(const int& numberClick);

	void setAdvAvaiable();

private:
	float _kX,_kY;
	static    SceneManager*    _instance;
	float _minWidth;
	int _maxMap;
	int _mapLocker[3];
	bool _isAdv;
	int _totalPlayMission;
	bool _isInit;

};
#endif // !SCENEMANAGER
