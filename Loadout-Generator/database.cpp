#include "database.h"
void dbConnect(MYSQL* &conn)
{
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "", "pool", 3306, NULL, 0);

	if (conn) {
		std::cout << "SUCCESS\n";
	} else {
		std::cout << "FAILED\n";
	}
}