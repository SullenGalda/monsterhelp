#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
 
#define NAME_SIZE 15
#define FILM_SIZE 50
#define WEAKNESS_SIZE 25
#define defeatedBy_SIZE 30
 
typedef struct {
  char name[NAME_SIZE];
  char film[FILM_SIZE];
  int year;
  char weakness[WEAKNESS_SIZE];
  char defeatedBy[defeatedBy_SIZE];
  float rating;
 
} Monster;
 
/*
 * Declaring storage for the database.
 */
#define MAX_MONSTERS 1024       /* should be big enough */
Monster monsters[MAX_MONSTERS];
 
void printCsvHeader(void)
/* print a CSV-compatible "monster" header to standard output */
{
 
  /*
   * ASSIGNMENT
   *
   * print each attribute name of the monster in order, followed by
   *  a ",", except for the last one, which should be followed by a
   *  newline ("\n").
   */
  printf("name,film,year,weakness,defeatedBy,rating\n");
 
 
}
 
void printCsvRow(Monster monster)
/* print a CSV-compatible "monster" row to standard output */
{
  /*
   * ASSIGNMENT
   *
   * print each attribute of the monster in order, followed by a
   *  ",", except for the last one, which should be followed by a
   *  newline ('\n').
   */
 
  printf("%s,", monster.name);
  printf("%s,", monster.film);
  printf("%d,", monster.year);
  printf("%s,", monster.weakness);
  printf("%s,", monster.defeatedBy);
  printf("%f\n", monster.rating);
 
 
}
 
void saveDatabase(Monster monsters[])
{
  /*
   * ASSIGNMENT
   *
   * print the CSV header with printCsvHeader()
   * for each monster in the monster database,
   *     print it with printCsvRow()
   */
 
  printCsvHeader();
 
  for (int i = 0; i < MAX_MONSTERS; i++) {
    printCsvRow(Monster*);
  }
 
}
 
int foundColumnName(char columnName[], char followedBy)
/* helper function used to read an expected column name */
{
  char buffer[2048];            /* longer than the longest possible column name */
  /*
   * The "%[^,\n]s" format string tells scanf() to accept anything
   * that's not a ',' or a '\n' as part of a string. Those two
   * characters *separate* data in a CSV file.
   *
   * After reading and verifying the column name, we call getchar()
   * to verify that it's followed by the char `followedBy`,
   * returning 0 if any of these errors are detected.
   */
  if (scanf("%[^,\n]s", buffer) != 1  /* didn't read one item */
      || strcmp(buffer, columnName) != 0  /* doesn't match `columnName` */
      || getchar() != followedBy) { /* not followed by expected char */
    return 0;
  }
  return 1;
}
 
 
int scanCsvHeader(void)
/* scans a CSV-compatible "monster" header for compatibility */
{
  /*
   * This function will read a CSV header line and verify its
   * correctness. Return 1 if it is correct and 0 if it is not.
   *
   * You need to confirm that each header field is occurring in
   * order.  The function foundColumnName() can do the dirty work
   * here. All you need to do is call it properly.
   *
   * Here is how you do it for the first field in the header.
   */
  if (!foundColumnName("name", ','))
    return 0;
  /*
   * ASSIGNMENT
   *
   * Now do the same for the remaining attribute names in the
   * Monster struct, except that the last attribute should have the
   * `followedBy` argument be a newline ('\n'), not a comma.
   *
   * At the very end, all of the column names have been matched, so
   * return 1 to indicate success.
   */
 
  if (!foundColumnName("film", ','))
    return 0;
 
  if (!foundColumnName("year", ','))
    return 0;
 
  if (!foundColumnName("weakness", ','))
    return 0;
 
  if (!foundColumnName("defeatedBy", ','))
    return 0;
 
  if (!foundColumnName("rating", '\n'))
    return 0;
 
  return 1;
}
 
 
int scanCsvRow(Monster * monster)
/* reads a Monster row from a CSV file */
{
  /*
   * This function calls scanf() to read every attribute on the row
   * in order using the appropriate format. The result of scanf()
   * will be 1 if the data is read successfully.
   *
   * For example, here's how you read the name. For string
   * attributes *only*, we again use the "%[^,\n]s" format string to
   * read a sequence of any characters except comma and newline.
   * Other attribute types can use the usual "%d", "%f", or
   * whatever.
   */
  if (scanf("%[^,\n]s", monster->name) != 1)
    return 0;
  getchar();                    /* skip the following comma or newline (we could check this) */
  /*
   * ASSIGNMENT
   *
   * Now do the same for the remaining attribute values in the
   * Monster struct. Be sure to that you always pass either a
   * reference (i.e. prefaced with "&") or the name of an array to
   * scanf().
   *
   * At the very end, all of the column names have been matched, so
   * return 1 to indicate success.
   */
 
  if (scanf("%[^,\n]s", monster->film) != 1)
    return 0;
  getchar();
 
  if (scanf("%d", &monster->year) != 1)
    return 0;
  getchar();
 
  if (scanf("%[^,\n]s", monster->weakness) != 1)
    return 0;
  getchar();
 
  if (scanf("%[^,\n]s", monster->defeatedBy) != 1)
    return 0;
  getchar();
 
  if (scanf("%f", &monster->rating) != 1)
    return 0;
  getchar();
 
  return 1;
}
 
 
int loadDatabase(void)
/* reads a CSV monster database on standard input, returns the number of members */
{
  /*
   * ASSIGNMENT
   *
   * Here's the pseudocode:
   *
   * call `scanCsvHeader()` to read the CSV header
   * if the CSV header is not correct,
   *     return 0
   * set `count` to 0
   * repeat the following indefinitely,
   *     call `scanCsvRow()` to read a new monster into the database
   *      at `monsters[count]`
   *     if it's not successful (i.e. at end-of-file),
   *         break out of the loop
   *     increment `count`
   * make `monsters[count].name` a zero-length string
   * return `count`
   */
 
 
  if (scanCsvHeader() == 0) {
    return 0;
 
  }
 
  int count = 0;
 
  while (1 == 1) {
 
    if (scanCsvRow(&monsters[count]) == 0) {
      break;
    }
    count++;
  }
 
  strcpy(monsters[count].name, "\0");
 
 
 
  return count;
 
}
 
 
int compareMonstersByYear(const void *monster0_vp, const void *monster1_vp)
{
  /*
   * Don't worry about this function for now. All you need to know
   * is that it's used by `qsort()` for sorting.
   */
  const Monster *monster0_p = monster0_vp;
  const Monster *monster1_p = monster1_vp;
 
  /* sort monsters by year of film release */
  return monster0_p->year - monster1_p->year;
}
 
 
int main(void)
{
  int monsterCount;
 
  monsterCount = loadDatabase();
  if (monsterCount > 0) {
    qsort(monsters, monsterCount, sizeof(Monster), compareMonstersByYear);
    saveDatabase(monsters);
  }
  return 0;
}