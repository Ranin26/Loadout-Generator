#include "queryItems.h"
#include "loadout.h"
//#include <winhttp.h>
//#include <objbase.h>
//#import <msxml6.dll> raw_interfaces_only

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ofstream fout;
	fout.open("output.txt");
	Loadout* best = new Loadout[MAX_LOADOUTS];
	Pool pool;
	queryItems(pool);
	//pool.readItems();
	pool.printPool(fout);

	cout << "Calculating best loadouts. May take some time. Please wait.\n";
	pool.bestLoadouts(best);
	printLoadouts(best, fout);
	cout << "Calculations Done.\n";
	fout.close();
	return 0;
}



