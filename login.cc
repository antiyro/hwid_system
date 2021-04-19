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
#include <string.h>

using namespace std;

/*unsigned int get_hdd()
{
    DWORD serialNumber = 0;
    if (GetVolumeInformation(
        NULL,
        NULL,
        NULL,
        &serialNumber,
        NULL,
        NULL,
        NULL,
        NULL))
    {
        return (serialNumber);
    }
}*/

int access()
{
    MYSQL *sock;
    MYSQL_ROW row = NULL;
    MYSQL_RES *res = NULL;

    int access = 0;
    int tries = 0;
    string password, hdd_serial, str, empty;

    //INITIALISATION DE LA DB
    sock = mysql_init(0);
    if (sock)
        cout << "Mysql initialized !" <<endl;
    else
        cout << "Mysql initialization failed" <<endl;
    
    //CONNEXION A LA DB
    if (mysql_real_connect(sock, "127.0.0.1", "root", "", "clients", 0, NULL, 0))
        cout << "Connected to database !" <<endl;
    else
    {
        cout << "Connexion failed\nPlease contact us" <<endl;
        return (0);
    }
    //FORMULAIRE D'ACCES
    while (!access)
    {
        cout << "Password : ";
        cin >> password;
        cout << "hdd_serial : ";
        cin >> hdd_serial;

        str = "SELECT password FROM clients WHERE password = '"+password+"'";
        mysql_query(sock, str.c_str());

        res = mysql_use_result(sock);
        row = mysql_fetch_row(res);

        if (row) //si le pseudo exist
        {
            mysql_free_result(res);
            //hdd_serial = to_string(get_hdd());
            //ON VERIFIE LADRESSE MAC
            str = "SELECT password FROM clients WHERE password = '"+password+"' AND hdd_serial IS NULL";
            mysql_query(sock, str.c_str());
            res = mysql_use_result(sock);
            row = mysql_fetch_row(res);

            if (row) //si l'address mac n'est pas la bonne ou quelle est egale a NULL
            {
                mysql_free_result(res);
                str = "UPDATE clients SET hdd_serial = '"+hdd_serial+"' WHERE password = '"+password+"'";
                mysql_query(sock, str.c_str());
                cout << "First connection configured with success !\nglhf !" << endl;
                return (1);
            }
            //sinon si le pseudo n'existe pas
            else
            {
                mysql_free_result(res);
                //on verifie que c'est la bonne address mac
                str = "SELECT hdd_serial FROM clients WHERE password = '"+password+"' AND hdd_serial = '"+hdd_serial+"'";
                mysql_query(sock, str.c_str());
                res = mysql_use_result(sock);
                row = mysql_fetch_row(res);
                if (row)
                {
                    mysql_free_result(res);
                    cout << "Authentification succed !\nglhf !" <<endl;
                    return (1);
                }
                else
                {
                    cout << "You don't have authorizations to run the cheats on that pc\nPlease contact if there is any problem" << endl;
                    return (0);
                }
            }
        }
        else //sinon si le pseudo n'existe pas
        {
            tries += 1;
            cout << "Invalid Password please try again\n" << endl;
            if (tries == 4)
            {
                cout << "Invalid Password\nPlease contact us\n" << endl;
                return (0);
            }
        }

    }
    return (0);
}

int main()
{
    access();
}