#include "database.h"
void dbConnect(MYSQL* &conn)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "", "pool", 3306, NULL, 0);

	if (conn) {
		std::cout << "SUCCESS\n";
	}
	else {
		std::cout << "FUCK\n";
	}

	/*MYSQL_ROW row;
	MYSQL_RES* res;
	if (mysql_query(conn, query))
	{
	}
	else {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res)) {
			cout << "day" << row[0] << "\n";
			cout << "title" << row[1] << "\n";
			cout << "link" << row[2] << "\n";
		}
	}
	
	const char* query = new char[512];
	stringstream ss;
	string str;
	
	ss << "INSERT INTO helmets(name,cost,fRes,eRes,cRes,chRes,armor,hp) values('" << name << "'," << cost << "," << fRes << "," << eRes << "," << cRes << "," << chRes << "," << armor << "," << hp << ");";
	str = ss.str();
	query = str.c_str();

	if (mysql_query(conn, query))
	{
		cout << "Helmet Insert failed \n";
		system("pause");
		exit(1);
	}
	else {
		cout << "Helmet Insertion successful\n";
		ss.str(std::string());
	}
	*/
}