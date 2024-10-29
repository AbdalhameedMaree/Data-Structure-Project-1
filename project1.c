/*
  Abdalhameed Maree - 1220775 - section 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
  This section is used to define Doubly Linked Lists called Town and District
  where every District has a specific number of Towns.
*/
typedef struct Town
{
  int Population;
  char name[25];
  struct Town *Next;
  struct Town *Previous;
} Town;

typedef struct District
{
  int TotalTownsPopulation;
  char name[25];
  struct District *Next;
  struct District *Previous;
  struct Town *NextTown;
} District;

/*
  This section is for some general functions
*/
void menu();
void loadInputFile(District *head);
void PrintLoadedInfo();
void outputFile(District *head);
/*
  The Following Functions Are Used For Towns List
*/
void FindMinMaxTotalPopulation(District *head);
Town *BubbleSort(Town *head);
void MakeEmpty(Town *head);
Town *Find(char *name, Town *head);
int IsEmpty(Town *head);
int IsLast(Town *currentNode, Town *head);
int SizeOfLinkedList(Town *head);
void InsertLast(char *name, int population, Town *head);
void Delete(char *name, Town **head);
void DeleteList(Town *head);
/*
  The Following Functions Are Used For Districts List
*/
District *DistrictCopyLinkedList(District *head);
District *RadixSortWithLetters(District *head);
void DistrictMakeEmpty(District *head);
District *DistrictFind(char *name, District *head);
int DistrictIsEmpty(District *head);
int DistrictIsLast(District *currentNode, District *head);
int DistrictSizeOfLinkedList(District *head);
void DistrictInsertLast(char *name, Town *town, District *head);
void DistrictPrintList(District *head);
void DistrictPrintListWithoutTowns(District *head);
void DistrictDelete(char *name, District *head);
void DistrictDeleteList(District *head);
/*
  In the main function We've Declared a head for the Doubly Linked List "Districs"
  Where It'll Be used in our program as a pointer for the linked list.
  PS: head Node doesn't contain any important data in the whole program.
*/
int main()
{
  /* District head node */
  District *TempDistrict = (District *)malloc(sizeof(District));
  TempDistrict->Next = NULL;
  TempDistrict->Previous = NULL;
  TempDistrict->NextTown = NULL;

  int option;
  menu();
  scanf("%d", &option);
  int counter = 0;
  while (1)
  {
    switch (option)
    {
    case 1:
    {
      if (counter < 1)
      {
        loadInputFile(TempDistrict);
        printf("File Loaded Successfully!\n");
        counter++;
        break;
      }
      else
        printf("You can't load the file more than once\n");
      break;
    }

    case 2:
    {
      PrintLoadedInfo();
      break;
    }

    case 3:
    {
      printf("Sorting districts alphabetically...\n");
      TempDistrict = RadixSortWithLetters(TempDistrict);
      printf("Districts sorted successfully!\n");
      break;
    }

    case 4:
    {
      printf("Sorting the Towns numerically...\n");
      District *currentDistrict = TempDistrict->Next;
      while (currentDistrict != NULL)
      {
        BubbleSort(currentDistrict->NextTown);
        currentDistrict = currentDistrict->Next;
      }
      printf("Towns Sorted Successfully!\n");
      break;
    }

    case 5:
      DistrictPrintList(TempDistrict);
      break;

    case 6:
    {
      printf("Enter The District Name\n");
      char DName[30];
      scanf("%s", &DName);
      District *Test = DistrictFind(DName, TempDistrict);
      if (Test == NULL)
      {
        Town *TempTown = (Town *)malloc(sizeof(Town));
        strcpy(TempTown->name, "");
        TempTown->Population = 0;
        DistrictInsertLast(DName, TempTown, TempDistrict);
      }
      else
        printf("District already Exists! \n");
      TempDistrict = RadixSortWithLetters(TempDistrict);
      printf("District has been added Successfully!\n");
      break;
    }

    case 7:
    {
      printf("Enter The District's Name That You Want to add a Town for it\n");
      char DDName[25];
      scanf("%s", DDName);
      if (DistrictFind(DDName, TempDistrict) != NULL)
      {
        printf("Enter the Town's Name \n");
        char TownName[30];
        scanf("%s", TownName);
        printf("Enter Town's Population \n");
        int population;
        scanf("%d", &population);
        Town *TempTown = (Town *)malloc(sizeof(Town));
        strcpy(TempTown->name, TownName);
        TempTown->Population = population;
        District *d = DistrictFind(DDName, TempDistrict);
        d->TotalTownsPopulation += population;
        InsertLast(TownName, population, d->NextTown);
      }
      else
        printf("District Not Found \n");
      printf("District has been added Successfully!\n");
      break;
    }

    case 8:
    {
      printf("Enter The District's Name That You Want to remove a Town from it\n");
      char DistrictName[25];
      scanf("%s", DistrictName);
      District *DTest = DistrictFind(DistrictName, TempDistrict);
      if (DTest != NULL)
      {
        printf("Enter the Town's Name \n");
        char TownsName[25];
        scanf("%s", TownsName);
        if (Find(TownsName, DTest->NextTown) != NULL)
        {
          DTest->TotalTownsPopulation -= Find(TownsName, DTest->NextTown)->Population;
          Delete(TownsName, &DTest->NextTown);
        }
        else
        {
          printf("Town Not Found \n");
          break;
        }
      }
      else
      {
        printf("District Not Found \n");
        break;
      }

      break;
    }

    case 9:
    {
      printf("Enter The Districts Name that You Want To Remove \n");
      char Name[25];
      scanf("%s", Name);
      if (DistrictFind(Name, TempDistrict) != NULL)
        DistrictDelete(Name, TempDistrict);
      else
      {
        printf("District Not Found \n");
        break;
      }
      break;
    }

    case 10:
      FindMinMaxTotalPopulation(TempDistrict);
      break;

    case 11:
      DistrictPrintListWithoutTowns(TempDistrict);
      break;

    case 12:
    {
      printf("Enter The District's Name That Contains The Town \n");
      char DisName[25];
      scanf("%s", DisName);
      District *Temp = DistrictFind(DisName, TempDistrict);
      if (Temp != NULL)
      {
        printf("Enter the Town's Name \n");
        char TownsName[25];
        scanf("%s", TownsName);
        if (Find(TownsName, Temp->NextTown) != NULL)
        {
          Temp->TotalTownsPopulation -= Find(TownsName, Temp->NextTown)->Population;
          printf("Enter The New Town's Population \n");
          int NewPopulation;
          scanf("%d", &NewPopulation);
          Town *TempTown = Find(TownsName, Temp->NextTown);
          TempTown->Population = NewPopulation;
          Temp->TotalTownsPopulation += NewPopulation;
        }
        else
        {
          printf("Town Not Found \n");
          break;
        }
      }
      else
      {
        printf("District Not found");
      }
      break;
    }

    case 13:
      outputFile(TempDistrict);
      printf("Saved to the file succesfully!\n");
      break;

    case 14:
      printf("Exiting The Program!\n");
      exit(1);

    default:
      printf("Please enter a valid operation!\n");
      break;
    }
    menu();
    scanf("%d", &option);
  }

  return 0;
}

/*
  a Function That Shows The List Of Operations That The Program can DO!
*/
void menu()
{
  printf("1. Load the input file.\n");
  printf("2. Print the loaded information before sorting.\n");
  printf("3. Sort the districts alphabetically using Radix sort.\n");
  printf("4. Sort the towns for each district based on population in ascending order.\n");
  printf("5. Print the sorted information.\n");
  printf("6. Add a new district to the list of sorted districts.\n");
  printf("7. Add a new town to a certain district.\n");
  printf("8. Delete a town from a specific district.\n");
  printf("9. Delete a complete district.\n");
  printf("10. Calculate the population of Palestine, the max and min town population.\n");
  printf("11. Print the districts and their total population.\n");
  printf("12. Change the population of a town.\n");
  printf("13. Save to output file.\n");
  printf("14. Exit\n");
}

/*
  A Function that reads the data from a text file called "districts.txt" and store it
  in the Districs Linked List.
*/
void loadInputFile(District *head)
{
  if (head == NULL)
  {
    printf("OUT OF MEMORY!\n");
    return;
  }

  FILE *input = fopen("districts.txt", "r");
  char string[50];
  while (fgets(string, 50, input) != NULL)
  {
    char *district = strtok(string, "|");
    char *town = strtok(NULL, "|");
    char *number = strtok(NULL, "|");
    int num = atoi(number);

    if (DistrictFind(district, head) == NULL)
    {
      Town *TempTown = (Town *)malloc(sizeof(Town));
      strcpy(TempTown->name, "");
      TempTown->Population = 0;
      DistrictInsertLast(district, TempTown, head);
    }
    InsertLast(town, num, DistrictFind(district, head)->NextTown);
    DistrictFind(district, head)->TotalTownsPopulation += num;
  }
  fclose(input);
}

/*
  A function used to print the data that have been read from the text file.
*/
void PrintLoadedInfo()
{

  FILE *input = fopen("districts.txt", "r");
  char string[50];
  while (fgets(string, 50, input) != NULL)
  {
    char *district = strtok(string, "|");
    char *town = strtok(NULL, "|");
    char *number = strtok(NULL, "|");
    int num = atoi(number);

    printf("%s\t%s\t%d\n", district, town, num);
  }
  fclose(input);
}

/*
  A Function that takes the data we've imported when we started the program
  and applied some operations on them and print them on a text file called "sorted_districs.txt".
*/
void outputFile(District *head)
{
  FILE *output = fopen("sorted_districts.txt", "w");
  District *currentNode = head->Next;
  int counter = DistrictSizeOfLinkedList(head);

  for (int i = 0; i < counter; i++)
  {
    int TownsNumber = SizeOfLinkedList(currentNode->NextTown);
    fprintf(output, "%s District, Population = %d\n", currentNode->name, currentNode->TotalTownsPopulation);
    Town *TempTown = currentNode->NextTown;
    for (int j = 0; j < TownsNumber + 1; j++)
    {
      if (j != 0)
        fprintf(output, "%s ,%d\n", TempTown->name, TempTown->Population);
      TempTown = TempTown->Next;
    }
    currentNode = currentNode->Next;
  }
  printf("\n");

  fclose(output);
}

/*
  A function that goes to every district and town in our linked lists and compare thier
  populations to find the minimum and muximum numper of people in a specific town, and
  sum thier population to find the total population of palestine.
*/
void FindMinMaxTotalPopulation(District *head)
{
  District *currentNode = head;
  int min = 10000000, max = 0, totalPopulation = 0;
  int DistrictSize = DistrictSizeOfLinkedList(head);
  for (int i = 0; i <= DistrictSize; i++)
  {
    Town *TestTown = currentNode->NextTown;
    while (TestTown != NULL)
    {
      if (strcmp(TestTown->name, "") == 0)
      {
        TestTown = TestTown->Next;
        continue;
      }
      if (TestTown->Population > max)
        max = TestTown->Population;
      if (TestTown->Population < min)
        min = TestTown->Population;
      totalPopulation += TestTown->Population;
      TestTown = TestTown->Next;
    }
    currentNode = currentNode->Next;
  }
  printf("Palestine Population = %d \t maximum town population = %d \t minimum town population = %d\n", totalPopulation, max, min);
}
/*
  The following functions are used for Towns Doubly Linked List
*/

/*
  This function applies the concept of bubble sort where it makes a nested for loop to compare the
  population of each town and sort them according to thier population in ascending order
*/
Town *BubbleSort(Town *head)
{
  Town *currentTown = head->Next;
  Town *tempTown;
  for (tempTown = currentTown; tempTown != NULL; tempTown = tempTown->Next)
  {
    Town *nextTown;
    for (nextTown = tempTown->Next; nextTown != NULL; nextTown = nextTown->Next)
    {
      if (nextTown->Population < tempTown->Population)
      {
        int tempPopulation = nextTown->Population;
        nextTown->Population = tempTown->Population;
        tempTown->Population = tempPopulation;
        char tempName[25];
        strcpy(tempName, nextTown->name);
        strcpy(nextTown->name, tempTown->name);
        strcpy(tempTown->name, tempName);
      }
    }
    currentTown = currentTown->Next;
  }
  return head;
}

/*
  A Function That takes a Towns list a free it from it's data
*/
void MakeEmpty(Town *head)
{
  Town *current = head->Next;
  while (current != NULL)
  {
    Town *next = current->Next;
    free(current);
    current = next;
  }
  head->Next = NULL;
}

/*
  Find function is a very important Function where it's mission is search for a specific Town using
  the name of towns then return it, and if it doesn't find the wanted node it returns "NULL"
*/
Town *Find(char *name, Town *head)
{
  if (IsEmpty(head))
  {
    printf("EMPTY LIST!\n");
    return NULL;
  }
  Town *currentNode = head;
  while (currentNode->Next != NULL)
  {
    if (strcmp(currentNode->name, name) == 0)
      return currentNode;

    currentNode = currentNode->Next;
  }
  if (currentNode->Next == NULL && strcmp(currentNode->name, name) == 0)
    return currentNode;

  // printf("THE DATA DOESN'T EXIST IN THE LIST!\n");
  return NULL;
}

/*
  Checks for the Towns' list if it's empty or not
*/
int IsEmpty(Town *head)
{
  return head == NULL;
}

/*
  Checks if the town passed to the function is the last one in the list or not
*/
int IsLast(Town *currentNode, Town *head)
{
  return currentNode->Next == NULL;
}

/*
  A function that returns the number of Towns in a specific file
*/
int SizeOfLinkedList(Town *head)
{
  Town *currentNode = head;
  int counter = 0;
  while (!IsLast(currentNode, head))
  {
    counter++;
    currentNode = currentNode->Next;
  }
  return counter;
}

/*
  A function that takes a name and a population of some town we want to add to the last of
  a specific town list , but before doing this operation it checks if there is another town with the same
  name, If there was another node with the same name it stops the function to stop the reputation
*/
void InsertLast(char *name, int population, Town *head)
{
  Town *currentNode = head;
  Town *tempNode = (Town *)malloc(sizeof(Town));
  if (tempNode == NULL)
  {
    printf("OUT OF MEMORY!\n");
    return;
  }
  tempNode->Population = population;
  strcpy(tempNode->name, name);
  tempNode->Next = NULL;

  while (currentNode->Next != NULL)
  {
    if (strcmp(name, currentNode->Next->name) == 0)
    {
      printf("Town already Exists\n");
      free(tempNode);
      return;
    }
    currentNode = currentNode->Next;
  }

  currentNode->Next = tempNode;
  tempNode->Previous = currentNode;
}

/*
  A function that delets a specific Town by searching for it by towns name , but if it doesn't find a town with
  that name , the function will stop.
*/
void Delete(char *name, Town **head)
{
  if (IsEmpty(*head))
  {
    printf("EMPTY LIST!\n");
    return;
  }
  Town *currentNode = Find(name, *head);
  if (currentNode->Previous != NULL)
  {
    currentNode->Previous->Next = currentNode->Next;
  }
  else
  {
    *head = currentNode->Next;
    if (*head != NULL)
    {
      (*head)->Previous = NULL;
    }
  }

  if (currentNode->Next != NULL)
  {
    currentNode->Next->Previous = currentNode->Previous;
  }

  free(currentNode);
}

/*
  A Function that delets a whole towns list , but before doing this operation it checks
  if the list is empty or not , and if it's empty the function stops.
*/
void DeleteList(Town *head)
{
  if (IsEmpty(head))
  {
    // printf("EMPTY LIST!\n");
    return;
  }
  Town *currentNode = head->Next;
  head->Next = NULL;
  free(head);
  Town *tempNode;
  while (!IsLast(currentNode, head))
  {
    tempNode = currentNode;
    currentNode = tempNode->Next;
    free(tempNode);
  }
  free(currentNode);
}
/*
  The Following Functions Are Used For District List
*/

/*
  A Function that copies a specific District by taking the original District list's head
*/
District *DistrictCopyLinkedList(District *head)
{
  if (head == NULL)
  {
    printf("Empty List!\n");
    return head;
  }
  District *copied = (District *)malloc(sizeof(District));
  copied->Next = NULL;
  copied->Previous = NULL;
  copied->NextTown = NULL;
  District *currentNode = head;
  while (currentNode->Next)
  {
    currentNode = currentNode->Next;
    DistrictInsertLast(currentNode->name, currentNode->NextTown, copied);
    DistrictFind(currentNode->name, copied)->TotalTownsPopulation += currentNode->TotalTownsPopulation;
  }
  return copied;
}

/*
  A Function that Took me 60,000 brain cells to make that takes a District List to
  Sort the districts inside it by thier names.
*/
District *RadixSortWithLetters(District *head)
{
  District *ArrayOfLetters[128];
  for (int i = 0; i < 128; i++)
  {
    ArrayOfLetters[i] = (District *)malloc(sizeof(District));
    ArrayOfLetters[i]->Next = NULL;
  }
  if (ArrayOfLetters[127] == NULL)
  {
    printf("OUT OF MEMORY!\n");
    return NULL;
  }
  District *current = head->Next;
  District *sortedDistricts = DistrictCopyLinkedList(head);
  int maxLength = 25;
  for (int d = maxLength - 1; d >= 0; --d)
  {
    District *currentNode = sortedDistricts->Next;
    while (currentNode != NULL)
    {
      int pop = current->TotalTownsPopulation;
      int length = strlen(currentNode->name);
      char y;
      if (d < length)
      {
        y = currentNode->name[d];
      }
      else
      {
        y = '\0';
      }
      DistrictInsertLast(currentNode->name, currentNode->NextTown, ArrayOfLetters[y]);
      DistrictFind(currentNode->name, ArrayOfLetters[y])->TotalTownsPopulation = currentNode->TotalTownsPopulation;
      ArrayOfLetters[y]->TotalTownsPopulation = pop;
      currentNode = currentNode->Next;
      if (current->Next != NULL)
        current = current->Next;
    }
    DistrictMakeEmpty(sortedDistricts);
    for (int j = 0; j < 128; ++j)
    {
      District *currentNode = ArrayOfLetters[j]->Next;
      while (currentNode != NULL)
      {
        Town *currentTown = currentNode->NextTown;
        DistrictInsertLast(currentNode->name, currentNode->NextTown, sortedDistricts);
        DistrictFind(currentNode->name, sortedDistricts)->TotalTownsPopulation = currentNode->TotalTownsPopulation;
        currentNode = currentNode->Next;
      }
      DistrictMakeEmpty(ArrayOfLetters[j]);
    }
  }

  for (int i = 0; i < 128; i++)
  {
    DistrictDeleteList(ArrayOfLetters[i]);
  }

  return sortedDistricts;
}

/*
  A void function that takes a Districts list and free it from the data inside it
*/
void DistrictMakeEmpty(District *head)
{
  District *current = head->Next;
  while (current != NULL)
  {
    District *next = current->Next;
    free(current);
    current = next;
  }
  head->Next = NULL;
}

/*
  A function that we will use for quite some times that search for a specific District by it's name and returns
  it if found, else, it'll return "NULL"
*/
District *DistrictFind(char *name, District *head)
{
  if (DistrictIsEmpty(head))
  {
    printf("EMPTY LIST!\n");
    return NULL;
  }
  District *currentNode = head;
  while (currentNode->Next != NULL)
  {
    int test = strcmp(currentNode->name, name);
    if (test == 0)
      return currentNode;

    currentNode = currentNode->Next;
  }
  int test = strcmp(currentNode->name, name);
  if (currentNode->Next == NULL && test == 0)
    return currentNode;

  // printf("THE DATA DOESN'T EXIST IN THE LIST!\n");
  return NULL;
}

/*
  Checks if the District we have is Empty or not.
*/
int DistrictIsEmpty(District *head)
{
  return head == NULL;
}

/*
  Checks if the District passed to it
*/
int DistrictIsLast(District *currentNode, District *head)
{
  return currentNode->Next == NULL;
}

/*
  A function that counts the number of districts we have
*/
int DistrictSizeOfLinkedList(District *head)
{
  District *currentNode = head;
  int counter = 0;
  while (!DistrictIsLast(currentNode, head))
  {
    counter++;
    currentNode = currentNode->Next;
  }
  return counter;
}

/*
  A Function that adds a new District to the list of Districts using the name and  a town
*/
void DistrictInsertLast(char *name, Town *town, District *head)
{
  District *currentNode = head;
  District *tempNode = (District *)malloc(sizeof(District));
  if (tempNode == NULL)
  {
    printf("OUT OF MEMORY!\n");
    return;
  }
  strcpy(tempNode->name, name);
  tempNode->Next = NULL;
  tempNode->NextTown = town;
  tempNode->TotalTownsPopulation += town->Population;

  while (!DistrictIsLast(currentNode, head))
    currentNode = currentNode->Next;

  currentNode->Next = tempNode;
  tempNode->Previous = currentNode;
}

/*
  A function that print the Districts list we have , using the district's name , total population
  and the town's data.
*/
void DistrictPrintList(District *head)
{
  if (head->Next == NULL)
  {
    printf("EMPTY LIST!\n");
    return;
  }

  District *currentNode = head->Next;
  int counter = DistrictSizeOfLinkedList(head);

  for (int i = 0; i < counter; i++)
  {
    int TownsNumber = SizeOfLinkedList(currentNode->NextTown);
    printf("%s District, Population = %d\n", currentNode->name, currentNode->TotalTownsPopulation);
    Town *TempTown = currentNode->NextTown;
    for (int j = 0; j < TownsNumber + 1; j++)
    {
      if (j != 0)
        printf("%s ,%d\n", TempTown->name, TempTown->Population);
      TempTown = TempTown->Next;
    }
    currentNode = currentNode->Next;
  }
  printf("\n");
}

/*
  A function that print the Districts list we have , using the district's name , total population only
*/
void DistrictPrintListWithoutTowns(District *head)
{
  if (head->Next == NULL)
  {
    printf("EMPTY LIST!\n");
    return;
  }

  District *currentNode = head->Next;
  int counter = DistrictSizeOfLinkedList(head);

  for (int i = 0; i < counter; i++)
  {
    int TownsNumber = SizeOfLinkedList(currentNode->NextTown);
    printf("%s District, Population = %d\n", currentNode->name, currentNode->TotalTownsPopulation);
    currentNode = currentNode->Next;
  }
  printf("\n");
}

/*
  A function that delets a specific District if found by searching for it, and if it's not
  found , the function will stop.
*/
void DistrictDelete(char *name, District *head)
{
  if (DistrictIsEmpty(head))
  {
    printf("EMPTY LIST!\n");
    return;
  }
  District *currentNode = DistrictFind(name, head);
  District *previousNode = currentNode->Previous;
  DeleteList(currentNode->NextTown);
  if (!DistrictIsLast(currentNode, head))
  {
    previousNode->Next = currentNode->Next;
    currentNode->Next->Previous = previousNode;
    currentNode->Next = NULL;
    currentNode->Previous = NULL;
    free(currentNode);
  }
  else
  {
    previousNode->Next = NULL;
    free(currentNode);
  }
}

/*
  A Function the Delets the whole Districts list if found
*/
void DistrictDeleteList(District *head)
{
  if (head->Next == NULL)
  {
    // printf("EMPTY LIST!\n");
    return;
  }
  District *currentNode = head->Next;
  head->Next = NULL;
  free(head);
  District *tempNode;
  while (!DistrictIsLast(currentNode, head))
  {
    DeleteList(currentNode->NextTown);
    tempNode = currentNode;
    currentNode = tempNode->Next;
    free(tempNode);
  }
  free(currentNode);
}
