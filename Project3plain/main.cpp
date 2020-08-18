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
	cout << "printPool()\n";

	pool.bestLoadouts(best);
	cout << "bestLoadouts()\n";
	printLoadouts(best, fout);
	cout << "printLoadouts()\n";
	fout.close();
	return 0;
}



