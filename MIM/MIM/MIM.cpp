
// Created on 2018.12.18
// By Bruce Zhang

#include "maze.h"
#include "route.h"
#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void)
{
	int width = 0,height=0;
	char MapAutoGeneration = 'N';
	char DisplaySelect = 'a';
	NODE* initial = NULL;

	// Remove data if Maze.txt exost
	remove("Maze.txt");

	printf(
		"Welcome,\n"
		"This is a program written by Bruce Zhang and Huang Boqi.\n"
		"****************************************************************\n"
		"\nInstructions:\n"
		"1.The width and height must be odd.\n"
		"2.The width and height must be greater than 4.\n"
	    "3.The solutions of maze should less than 26"
		"(this program use alphabet to represent different solutions)\n\n");

	printf("Enter the size of maze(example:\"21*21\"):\n");
	scanf_s("%d*%d", &width, &height);
	getchar();
	fflush(stdin);

	if (width <= 3 || height <= 3)
	{
		fprintf(stderr, "Error: The width and height must be greater than 4.\n");
		system("pause");
		exit(1);
	}
	else if (width % 2 == 0 || height % 2 == 0)
	{
		fprintf(stderr, "Error: The width and height must be odd.\n");
		system("pause");
		exit(1);
	}
	else
	{
		printf("Enter 'Y' or 'y' if you want to generate a maze"
			" automatically:\n");
		MapAutoGeneration = tolower(getchar());
		getchar();
		fflush(stdin);

		// Maze generation
		if (MapAutoGeneration == 'y')
		{
			if ((initial = RandomMazeGenerate(width, height)) == NULL)
			{
				fprintf(stderr, "Program stopped due to unexpected issue.\n");
				system("pause");
				exit(1);
			}
		}
		else
		{
			printf("Notice: %c for wall, %c for way, %c for start, %c for"
				"end.\n",
				WALL, WAY,
				START, END);
			if (GetMazeInput(width, height) == 1)
			{
				fprintf(stderr, "Program stopped due to unexpected issue.\n");
				system("pause");
				exit(1);
			}
			getchar();
			fflush(stdin);
		}
		system("cls");

		// Print Initial Maze
		printf("%s\n\n", 
			MapAutoGeneration == 'y' ? "Auto generate maze:" : "User input"
			" maze:");
		MazePrint();
		MazeToTXT('\b',"Initial Maze");

		printf("\n\nPress enter to start solve function......\n");
		getchar();
		system("cls");

		// Maze solution
		if (RandomMazeSolutions() == NULL)
		{
			fprintf(stderr, "Program stopped due to unexpected issue.\n");
			system("pause");
			exit(1);
		}

		// Dynamical mouse
		printf("Enter which solution you want to show dynamically"
			"(a-z or A-Z):\n");
		DisplaySelect = tolower(getchar());
		getchar();
		fflush(stdin);
		if (DisplaySelect > 'z' || DisplaySelect < 'a')
		{
			fprintf(stderr, "Solution %c does not exist.\n", DisplaySelect);
			system("pause");
			exit(1);
		}
		else
		{
			if (DynamicDisplay(DisplaySelect) == NULL)
			{
				fprintf(stderr, "Program stopped due to unexpected issue.\n");
				system("pause");
				exit(1);
			}
		}
		// Free memory
		MazeFree(initial);
	}
	system("pause");
	return 0;
}