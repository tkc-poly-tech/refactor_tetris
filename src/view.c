#include "view.h"
#include "window.h"

static void copyTable(const char from[ROWS_TABLE][COLS_TABLE], char to[ROWS_TABLE][COLS_TABLE])
{
	for (int i = 0; i < ROWS_TABLE; i++)
		for (int j = 0; j < COLS_TABLE; j++)
			to[i][j] = from[i][j];
}

static void putPieceOnTable(char pieceInTable[ROWS_TABLE][COLS_TABLE], const Piece piece, const char table[ROWS_TABLE][COLS_TABLE])
{
	copyTable(table, pieceInTable);
	for (int i = 0; i < piece.width; i++)
		for (int j = 0; j < piece.width; j++)
			if (piece.array[i][j])
				pieceInTable[piece.row + i][piece.col + j] = piece.array[i][j];
}

static void printHeader()
{
	for (int i = 0; i < COLS_TABLE - OFFSET_HEADER; i++)
		printWindow(" ");
	printWindow(FORMAT_HEADER);
}

static void printTable(const char table[ROWS_TABLE][COLS_TABLE], int (*printFunc)(const char *, ...))
{
	for (int i = 0; i < ROWS_TABLE; i++)
	{
		for (int j = 0; j < COLS_TABLE; j++)
			printFunc("%c ", (table[i][j]) ? CHAR_PIECE : CHAR_EMPTY);
		printFunc("\n");
	}
	printFunc("\n");
}

void printGame(const Piece current, const char table[ROWS_TABLE][COLS_TABLE], const int score)
{
	clearWindow();
	printHeader();
	char pieceOnTable[ROWS_TABLE][COLS_TABLE];
	putPieceOnTable(pieceOnTable, current, table);
	printTable(pieceOnTable, printWindow);
	printWindow(FORMAT_SCORE, score);
}

void printResult(const char table[ROWS_TABLE][COLS_TABLE], const int score)
{
	printTable(table, printf);
	printf(FORMAT_GAMEOVER);
	printf("\n");
	printf(FORMAT_SCORE, score);
}
