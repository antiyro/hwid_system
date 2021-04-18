#include <iostream>
#define WINDOWS false
#if defined _WIN64 || defined _WIN32
#undef WINDOWS
#define WINDOWS true
# include <windows.h>
#else
# include <unistd.h>
#endif
#include <mysql/mysql.h>

using namespace std;

int main()
{
    MYSQL *sock;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;

    char access = 0;
    string password, mac_address, str;

    //INITIALISATION DE LA DB
    sock = mysql_init(0);
    if (sock)
        cout << "Mysql initialized !" <<endl;
    else
        cout << "Mysql initialization failed" <<endl;
    
    //CONNEXION A LA DB
    const char *host = "localhost";
    const char *user = "root";
    const char *pass = "";
    const char *db = "clients";
    if (mysql_real_connect(sock, "localhost", "root", "", "clients", 0, NULL, 0))
        cout << "Connected to database !" <<endl;
    else
        cout << "Connexion failed" <<endl;

    //FORMULAIRE
    while (!access)
    {
        cout << "Password : ";
        cin >> password;

        str = "SELECT pseudo FROM clients WHERE pseudo = '"+username+"'";
        mysql_query(sock, str.c_str());

        res = mysql_use_result(sock);
        row = mysql_fetch_row(res);

        if (row) //si le pseudo exist
        {
            //ON VERIFIE LADRESSE MAC
            if (//pas daddress mac on fill)
            {

            }
            else
            {
                //on verifie que c'est la bonne address mac
                if (//c la bonne )
                {
                    //access passe a 1 et on sort
                }
                else
                {
                    //tas crus tallais nous avoir? attends quon thagar fdp
                }
            }
        }
        else //pseudo invalide veuillez rentrer le pseudo quon vous a fourni
        {
            cout << ""
        }

    }
    return (0);
}