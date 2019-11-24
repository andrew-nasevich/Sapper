#pragma once
class Cell
{
public:
	
	void IncNumOfBombNearby();

	void SetVisible(int visibile);

	bool IsBombed();

	bool IsMarked();

	bool ChangeMarked();

	void SetBombed(bool bombed);


	int GetNumOfBombNearby();

	bool IsVisible();

	Cell();

private:
	int numOfBomdNearby;
	bool bombed;
	bool visible;
	bool marked;
};

