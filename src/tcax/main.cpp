/* 
 *  Copyright (C) 2011 milkyjing <milkyjing@gmail.com>
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *   
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <iostream>
#include <ctime>
#include "tcax.h"

#define TCAX_CMD_EXIT         'e'
#define TCAX_CMD_PARSE_TCC    '1'
#define TCAX_CMD_DEFAULT_PY   '2'
#define TCAX_CMD_DEFAULT_TCC  '3'
#define TCAX_CMD_EXEC_PY      'i'
#define TCAX_CMD_MENU         'm'

using namespace std;

void printMenu()
{
    cout << endl << endl;
    cout << "----------------- MENU -----------------" << endl;
    cout << "1 - parse a TCC file" << endl;
    cout << "2 - create a default tcaxPy script template" << endl;
    cout << "3 - create a default TCC file" << endl;
    cout << "m - show the menu again" << endl;
    cout << "e - exit TCAX" << endl;
    cout << endl << endl;
}

int main(int argc, char *argv[])
{
    time_t executionTime;
    int len, tcaxCmd;
    char szFilename[1024];
    char *outFilename;
    cout << "TCAX version 1.2.0 [2012-08-03] [Anniversary]" << endl;
    cout << "(C) Copyright 2009-2012 milkyjing" << endl;
    cout << endl;
    if (tcaxpy_init_python() != py_error_success) return -1;
    if (2 == argc)
    {
        executionTime = clock();
        tcax_make_out_filename_from_tcc(argv[1], &outFilename);
        if (tcax_entry(argv[1], outFilename) != 0)
        {
            delete outFilename;
            cout << "INFO: Task failed!" << endl << endl << endl;
            cout << "温馨提醒: 如果不清楚造成本错误的原因, 请保留本窗口截图以及当前特效工程," << endl;
            cout << "访问 http ://tcax.rhacg.com/forum.php?mod=forumdisplay&fid=38 发帖以获取帮助." << endl;
            cout << endl;
        }
        else
        {
            delete outFilename;
            cout << "INFO: Task has been completed!" << endl;
            printf("INFO: execution duration is %ld seconds\n", (clock() - executionTime) / CLOCKS_PER_SEC);
        }
        tcaxpy_fin_python();
        system("PAUSE");
        return 0;
    }
    printMenu();
    while (1)
    {
        cout << "Please enter a number: ";
        tcaxCmd = getchar();
        if ('\n' != tcaxCmd)
            while ('\n' != getchar()) continue;    /* read the '\n' character brought in by the enter key to avoid the gets function to read it */
        if (TCAX_CMD_EXIT == tcaxCmd)
        {
            cout << "Bye, Bye!" << endl;
            break;
        }
        else if (TCAX_CMD_PARSE_TCC == tcaxCmd)
        {
            do
            {
                printf("Please enter the TCC filename: ");
                cin.getline(szFilename, 1024);
                len = strlen(szFilename);
            }
            while (!(len > 4 && __str_ignore_case_cmp(szFilename + len - 4, ".tcc") == 0));
            executionTime = clock();
            tcax_make_out_filename_from_tcc(szFilename, &outFilename);
            if (tcax_entry(szFilename, outFilename) != 0)
            {
                delete outFilename;
                cout << "INFO: Task failed!" << endl << endl;
                cout << endl << endl;
                cout << "温馨提醒: 如果不清楚造成本错误的原因, 请保留本窗口截图以及当前特效工程," << endl;
                cout << "访问 http ://tcax.rhacg.com/forum.php?mod=forumdisplay&fid=38 发帖以获取帮助." << endl;
                cout << endl;
            }
            else
            {
                delete outFilename;
                cout << "INFO: Task has been completed!" << endl;
                printf("INFO: execution duration is %ld seconds\n\n", (clock() - executionTime) / CLOCKS_PER_SEC);
            }
        }
        else if (TCAX_CMD_DEFAULT_PY == tcaxCmd)
        {
            do
            {
                cout << "Please enter the tcaxPy script filename: ";
                cin.getline(szFilename, 1024);
                len = strlen(szFilename);
            }
            while (!(len > 3 && __str_ignore_case_cmp(szFilename + len - 3, ".py") == 0));
            if (tcaxpy_create_py_template(szFilename) != tcc_error_success)
                cout << "INFO: Task failed!" << endl << endl;
            else
                cout << "INFO: Task has been completed!" << endl << endl;
        }
        else if (TCAX_CMD_DEFAULT_TCC == tcaxCmd)
        {
            do
            {
                cout << "Please enter the TCC filename: ";
                cin.getline(szFilename, 1024);
                len = strlen(szFilename);
            }
            while (!(len > 4 && __str_ignore_case_cmp(szFilename + len - 4, ".tcc") == 0));
            if (libtcc_create_default_tcc_file(szFilename) != tcc_error_success)
                cout << "INFO: Task failed!" << endl << endl;
            else
                cout << "INFO: Task has been completed!" << endl << endl;
        }
        else if (TCAX_CMD_EXEC_PY == tcaxCmd)
        {
            do
            {
                cout << "Please enter the PY filename: ";
                cin.getline(szFilename, 1024);
                len = strlen(szFilename);
            }
            while (!(len > 3 && __str_ignore_case_cmp(szFilename + len - 3, ".py") == 0));
            if (tcaxpy_exec_py_script(szFilename) != tcc_error_success)
                cout << "INFO: Task failed!" << endl << endl;
            else
                cout << "INFO: Task has been done!" << endl;
        }
        else if (TCAX_CMD_MENU == tcaxCmd)
        {
            printMenu();
        }
        else
        {
            cout << "INFO: Invalid command!" << endl << endl;
        }
    }
    tcaxpy_fin_python();
    return 0;
}
