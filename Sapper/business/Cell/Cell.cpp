#include "Cell.h"

Cell::Cell()
{
	this->bombed = false;
	this->numOfBomdNearby = 0;
	this->visible = false;
}

void Cell::IncNumOfBombNearby() { numOfBomdNearby++; }

void Cell::SetVisible(int visibile) { this->visible = visibile; }

bool Cell::IsBombed() { return bombed; }

void Cell::SetBombed(bool bombed) { this->bombed = bombed; }

int Cell::GetNumOfBombNearby() { return numOfBomdNearby; }

bool Cell::IsVisible() { return visible; }
