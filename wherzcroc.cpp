// wherzcroc.cpp : définit le point d'entrée pour l'application console.
//

#include "common.h"
#include "ranger.h"

using namespace std;

int main(int argc, _TCHAR* argv[]){
	wstring group(L"3");
	bool status;

	CrocSession crocSession = CrocSession(group, status);
	Ranger ranger = Ranger(&crocSession);

	ranger.StartHunting();

	return 0;
}

