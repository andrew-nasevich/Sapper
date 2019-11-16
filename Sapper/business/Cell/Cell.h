#pragma once
class Cell
{
public:
	
	void IncNumOfMimbNearby() { numOfBomdNearby++; }

	void SetVisible(int visibile) { this->visible = visibile; }

	bool IsBombed() { return bombed; }

	void SetBombed(bool bombed) { this->bombed = bombed; }

	int GetNumOfBombNearby() { return numOfBomdNearby; }

	bool IsVisible() { return visible; }

	Cell();

private:
	int numOfBomdNearby;
	bool bombed;
	bool visible;
};

