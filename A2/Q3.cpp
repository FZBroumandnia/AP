#include <iostream>
#include <vector>
#include <string>
using namespace std;

const auto STONE = '#';
const auto BAMBO = '*';

const vector<int> ROW_DELTA = {-1, 0, 1, 0};
const vector<int> COL_DELTA = {0, -1, 0, 1};

const int PATH_NOT_FOUND = -1;
const auto NOT_FOUND_MESSAGE = "No path found";

const auto MOVE_SAVER_BOARD_INITIAL_NUMBER = 0;

struct Cursor
{
    int row;
    int col;
    int move_number;
};
const Cursor INITIAL_CURSOR = {0, 0, 0};

enum move_types
{
    go_up,
    go_left,
    go_down,
    go_right,
};

vector<string> initial_main_board()
{
    vector<string> main_board;
    string new_line;
    while (cin >> new_line)
        main_board.push_back(new_line);
    return main_board;
}

bool repetitious_path(Cursor cursor, vector<vector<int>> moves_saver_board)
{
    if (moves_saver_board[cursor.row][cursor.col])
        return true;
    return false;
}

bool stone_crash(vector<string> main_board, Cursor cursor, int move_type)
{
    if (main_board[cursor.row + ROW_DELTA[move_type]][cursor.col + COL_DELTA[move_type]] == STONE)
        return true;
    return false;
}

bool border_crash(vector<string> main_board, Cursor cursor, int move_type)
{
    if (cursor.row + ROW_DELTA[move_type] < 0 || cursor.col + COL_DELTA[move_type] < 0)
        return true;
    if (cursor.row + ROW_DELTA[move_type] >= main_board.size() || cursor.col + COL_DELTA[move_type] >= main_board[0].size())
        return true;
    return false;
}

bool reach_bambo(vector<string> main_board, Cursor cursor, int move_type)
{
    if (main_board[cursor.row + ROW_DELTA[move_type]][cursor.col + COL_DELTA[move_type]] == BAMBO)
        return true;
    return false;
}

bool crash(vector<string> main_board, Cursor cursor, int move_type)
{
    if (!border_crash(main_board, cursor, move_type) && !stone_crash(main_board, cursor, move_type))
        return false;
    return true;
}

int shortest_path(int first_path, int second_path)
{
    if (first_path == PATH_NOT_FOUND && second_path == PATH_NOT_FOUND)
        return PATH_NOT_FOUND;
    else if (first_path == PATH_NOT_FOUND)
        return second_path;
    else if (second_path == PATH_NOT_FOUND)
        return first_path;
    else if (first_path <= second_path)
        return first_path;
    else
        return second_path;
}

vector<int> turn_90_deg(int move_type)
{
    vector<int> new_directions;
    if (move_type == go_down || move_type == go_up)
    {
        new_directions.push_back(go_left);
        new_directions.push_back(go_right);
    }
    if (move_type == go_right || move_type == go_left)
    {
        new_directions.push_back(go_up);
        new_directions.push_back(go_down);
    }
    return new_directions;
}

bool stuck_in_corner(vector<string> main_board, Cursor cursor, int move_type)
{
    if (crash(main_board, cursor, move_type))
    {
        if (crash(main_board, cursor, turn_90_deg(move_type)[0]) || crash(main_board, cursor, turn_90_deg(move_type)[1]))
            return true;
    }
    return false;
}

Cursor move_cursor(Cursor cursor, int move_type)
{
    cursor.col += COL_DELTA[move_type];
    cursor.row += ROW_DELTA[move_type];
    cursor.move_number++;
    return cursor;
}

int find_paths(vector<string> main_board, Cursor cursor, int move_type, vector<vector<int>> moves_saver_board)
{
    if (stuck_in_corner(main_board, cursor, move_type))
        return PATH_NOT_FOUND;
    while (!crash(main_board, cursor, move_type) && !reach_bambo(main_board, cursor, move_type))
    {
        cursor = move_cursor(cursor, move_type);
        if (repetitious_path(cursor, moves_saver_board))
            return PATH_NOT_FOUND;
        moves_saver_board[cursor.row][cursor.col] = cursor.move_number;
    }
    if (crash(main_board, cursor, move_type))
    {
        int first_path, second_path;
        first_path = find_paths(main_board, cursor, turn_90_deg(move_type)[0], moves_saver_board);
        second_path = find_paths(main_board, cursor, turn_90_deg(move_type)[1], moves_saver_board);
        return shortest_path(first_path, second_path);
    }
    return ++cursor.move_number;
}

int start_path_finding(vector<string> main_board)
{
    int first_path, second_path;
    vector<vector<int>> moves_saver_board(main_board.size(), vector<int>(main_board[0].size()));
    first_path = find_paths(main_board, INITIAL_CURSOR, go_down, moves_saver_board);
    second_path = find_paths(main_board, INITIAL_CURSOR, go_right, moves_saver_board);
    return shortest_path(first_path, second_path);
}

void print_result(int input)
{
    if (input == PATH_NOT_FOUND)
        cout << NOT_FOUND_MESSAGE << endl;
    else
        cout << input << endl;
}

int main()
{
    vector<string> main_board = initial_main_board();
    print_result(start_path_finding(main_board));
}
