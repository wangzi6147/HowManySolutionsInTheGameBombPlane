#include <vector>
using namespace std;

//global
const int PLAT_ROWS = 6;
const int PLAT_COLS = 7;
const int plane_NUM = 2;
int totalSol = 0;
vector<vector<pair<int, int>>> record;
int planeShape[4][10][2] = { { 0, 0, -1, -2, -1, -1, -1, 0, -1, 1, -1, 2, -2, 0, -3, -1, -3, 0, -3, 1 },
	{ 0, 0, -2, 1, -1, 1, 0, 1, 1, 1, 2, 1, 0, 2, -1, 3, 0, 3, 1, 3 } ,
	{ 0, 0, 1, -2, 1, -1, 1, 0, 1, 1, 1, 2, 2, 0, 3, -1, 3, 0, 3, 1 } ,
	{ 0, 0, -2, -1, -1, -1, 0, -1, 1, -1, 2, -1, 0, -2, -1, -3, 0, -3, 1, -3 } };

int setOneplane(int** plat, int iHead, int jHead, int dir)
{
	for (int i = 0; i < 10; i++){
		if (iHead + planeShape[dir][i][0]<0 || iHead + planeShape[dir][i][0]>PLAT_ROWS - 1 || jHead + planeShape[dir][i][1]<0 || jHead + planeShape[dir][i][1]>PLAT_COLS - 1){
			return -1;
		}
		if (plat[iHead + planeShape[dir][i][0]][jHead + planeShape[dir][i][1]]>0){
			return -1;
		}
	}
	for (int i = 0; i < 10; i++){
		//record 0--->2
		plat[iHead + planeShape[dir][i][0]][jHead + planeShape[dir][i][1]] = 2;
	}
	//record head
	plat[iHead][jHead] = 1;
	return 0;
}

void deleteOneplane(int** plat, int iLastHead, int jLastHead, int lastDir)
{
	for (int i = 0; i < 10; i++){
		//record 2--->0
		plat[iLastHead + planeShape[lastDir][i][0]][jLastHead + planeShape[lastDir][i][1]] = 0;
	}
	return;
}

void recordplane(int** plat)
{
	vector<pair<int, int>> oneSol;
	for (int i = 0; i<PLAT_ROWS; i++){
		for (int j = 0; j < PLAT_COLS; j++){
			if (plat[i][j] == 1){
				oneSol.push_back(pair<int, int>(i, j));
				if (oneSol.size() == plane_NUM){
					record.push_back(oneSol);
					/*printf("one solution:");
					for (int k = 0; k < plane_NUM; k++){
					printf("{%d, %d}, ", oneSol[k].first, oneSol[k].second);
					}
					printf("\n");*/
					return;
				}
			}
		}
	}
}

void setplane(int** plat, int planeNum, int iLastHead, int jLastHead, int lastDir)
{
	//printf("current plane number: %d\n", planeNum);
	if (planeNum == plane_NUM){
		totalSol++;
		printf("current solution number: %d\n", totalSol);
		recordplane(plat);
	}
	else
	{
		for (int i = iLastHead; i < PLAT_ROWS; i++){
			for (int j = 0; j < PLAT_COLS; j++){
				if (i == iLastHead&&j <= jLastHead){
					continue;
				}
				for (int dir = 0; dir < 4; dir++){
					if (setOneplane(plat, i, j, dir)>-1){
						setplane(plat, planeNum + 1, i, j, dir);
					}
				}
			}
		}
	}
	if (lastDir>-1){
		deleteOneplane(plat, iLastHead, jLastHead, lastDir);
	}
	return;
}

int main(){
	int** plat = new int*[PLAT_ROWS];
	//init
	for (int i = 0; i < PLAT_ROWS; i++){
		plat[i] = new int[PLAT_COLS];
		for (int j = 0; j < PLAT_COLS; j++)
		{
			plat[i][j] = 0;
		}
	}

	//set plane
	setplane(plat, 0, 0, 0, -1);

	//delete
	for (int i = 0; i < PLAT_ROWS; i++){
		delete[] plat[i];
	}
	delete[] plat;

	printf("total: %d\n", totalSol);

	system("pause");

	return 0;
}
