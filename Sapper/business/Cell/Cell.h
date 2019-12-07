#pragma once
class Cell
{
public:
	
	void IncNumOfBombNearby();

	void SetVisible(int visibile);

	bool IsBombed();

	bool IsMarked();

	bool IsVisible();

	bool ChangeMarked();

	void SetBombed(bool bombed);

	int GetNumOfBombNearby();

	Cell();

private:
	int numOfBomdNearby;

	bool bombed;

	bool visible;

	bool marked;
};

