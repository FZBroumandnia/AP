#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;

const auto TIME_DELIMITER = ":";
const auto HYPHEN = "-";
const auto NUMBER_SIGN = "#";
const int START_OF_DAY_HOUR = 12;
const int START_OF_DAY_MINUTE = 0;
const int END_OF_DAY_HOUR = 20;
const int END_OF_DAY_MINUTE = 0;

struct Timing
{
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
};

struct Time_block
{
    Timing time;
};

struct Task
{
    int task_duration;
    int empty_range_id;
    Timing time;
};

void push_back_2char(string &time_str, char first, char second)
{
    time_str.push_back(first);
    time_str.push_back(second);
}

Time_block new_event_from_input(string input)
{
    string start_hour, start_minute, end_hour, end_minute;
    push_back_2char(start_hour, input[0], input[1]);
    push_back_2char(start_minute, input[3], input[4]);
    push_back_2char(end_hour, input[6], input[7]);
    push_back_2char(end_minute, input[9], input[10]);

    Time_block new_event = {stoi(start_hour), stoi(start_minute), stoi(end_hour), stoi(end_minute)};
    return new_event;
}

void add_tasks_from_input(vector<Task> &tasks, vector<string> input_task_vector)
{
    for (int i = 0; i < input_task_vector.size() / 2; i++)
    {
        Task new_task = {stoi(input_task_vector[2 * i]), stoi(input_task_vector[2 * i + 1])};
        tasks.push_back(new_task);
    }
}

int start_from_12(Time_block event)
{
    if (event.time.start_hour == 12 && event.time.start_minute == 0)
        return 1;
    else
        return 0;
}

void back_to_back_events(vector<Time_block> events, int &i)
{
    if (events[i - 1].time.end_hour == events[i].time.start_hour && events[i - 1].time.end_minute == events[i].time.start_minute)
        i++;
}

Time_block new_empty_block(vector<Time_block> events, int i)
{
    Time_block new_empty_block;
    if (!i)
        new_empty_block = {START_OF_DAY_HOUR, START_OF_DAY_MINUTE, events[i].time.start_hour, events[i].time.start_minute};

    else if (i == events.size())
        new_empty_block = {events[i - 1].time.end_hour, events[i - 1].time.end_minute, END_OF_DAY_HOUR, END_OF_DAY_MINUTE};

    else
        new_empty_block = {events[i - 1].time.end_hour, events[i - 1].time.end_minute, events[i].time.start_hour, events[i].time.start_minute};
    return new_empty_block;
}

void schedule_task(vector<Time_block> empty_blocks, Task &task)
{
    task.time.start_hour = empty_blocks[task.empty_range_id - 1].time.start_hour;
    task.time.start_minute = empty_blocks[task.empty_range_id - 1].time.start_minute;
    task.time.end_hour = task.time.start_hour + (task.task_duration + task.time.start_minute) / 60;
    task.time.end_minute = (task.task_duration + task.time.start_minute) % 60;
}

void reduce_empty_block_duration(vector<Time_block> &empty_blocks, Task task)
{
    empty_blocks[task.empty_range_id - 1].time.start_hour = task.time.end_hour;
    empty_blocks[task.empty_range_id - 1].time.start_minute = task.time.end_minute;
}

void additional_zero(int minute)
{
    if (minute < 10)
        cout << "0";
    cout << minute;
}

void print_clock(int hour, int minute)
{
    cout << hour << TIME_DELIMITER;
    additional_zero(minute);
}

void print_scheduled_tasks(vector<Task> tasks)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ' ';
        print_clock(tasks[i].time.start_hour, tasks[i].time.start_minute);
        cout << HYPHEN;
        print_clock(tasks[i].time.end_hour, tasks[i].time.end_minute);
        cout << endl;
    }
}

int main()
{
    vector<Time_block> events;
    string input_string;
    while (cin >> input_string)
    {
        if (!strcmp(input_string.c_str(), NUMBER_SIGN))
            break;
        events.push_back(new_event_from_input(input_string));
    }

    vector<string> input_task_vector;
    while (cin >> input_string)
        input_task_vector.push_back(input_string);

    vector<Task> tasks;
    add_tasks_from_input(tasks, input_task_vector);

    vector<Time_block> empty_blocks;
    for (int i = 0; i <= events.size(); i++)
    {
        if (start_from_12(events[i]))
            i++;
        back_to_back_events(events, i);
        empty_blocks.push_back(new_empty_block(events, i));
    }

    for (int i = 0; i < tasks.size(); i++)
    {
        schedule_task(empty_blocks, tasks[i]);
        reduce_empty_block_duration(empty_blocks, tasks[i]);
    }

    print_scheduled_tasks(tasks);
}