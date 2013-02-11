#include <stdio.h>
#include <sqlite3.h>
// initial code from http://www.thegeekstuff.com/2009/01/vi-and-vim-macro-tutorial-how-to-record-and-play/
// jumanbyun: removed UPDATE query and the 4th column

int     main(void) {
        sqlite3 *conn;
        sqlite3_stmt    *res;
        int     error = 0;
        int     rec_count = 0;
        const char      *errMSG;
        const char      *tail;

        error = sqlite3_open("contactdb.sqlite", &conn);
        if (error) {
                puts("Can not open database");
                exit(0);
        }

        error = sqlite3_prepare_v2(conn,
                "select lastName,firstName,phonenum,email from contact",
                1000, &res, &tail);

        if (error != SQLITE_OK) {
                puts("We did not get any data!");
                exit(0);
        }

        puts("==========================");

        while (sqlite3_step(res) == SQLITE_ROW) {
                printf("%s|", sqlite3_column_text(res, 0));
                printf("%s|", sqlite3_column_text(res, 1));
                printf("%s|", sqlite3_column_text(res, 2));
                printf("%s|", sqlite3_column_text(res, 3));
                printf("\n" );

                rec_count++;
        }

        puts("==========================");
        printf("%d row(s).\n", rec_count);

        sqlite3_finalize(res);
        sqlite3_close(conn);

        return 0;
}
