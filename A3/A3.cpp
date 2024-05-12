#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

const auto DELIMITER = ' ';
const auto TIME_DELIMITER = ':';
const auto NF_MESSAGE = "Not Found";
const auto NO_FREE_TIME_BLOCK = -1;

struct Time
{
    int start_hour;
    int start_minute;
    int end_hour;
    int end_minute;
};
typedef vector<Time> Time_blocks;

struct Translator
{
    string name;
    Time_blocks time_blocks;
    vector<string> languages;
};
typedef vector<Translator> Translator_list;

struct Availabe_language
{
    string name;
    vector<int> translators_idx;
};
typedef vector<Availabe_language> Available_language_list;

struct Event_demanded_language
{
    string name;
    string chosen_translator;
    vector<int> translators_idx;
};
typedef vector<Event_demanded_language> Event_language_list;

struct Event
{
    string name;
    Time time;
    Event_language_list demanded_languages;
};
typedef vector<Event> Event_list;

struct Lists
{
    Event_list event_list;
    Translator_list translator_list;
};

struct Planned_event
{
    Event event;
    Translator_list translator_list;
};

vector<string> split_line(string line)
{
    stringstream new_line(line);
    string splited_str;
    vector<string> splited_vector;
    while (getline(new_line, splited_str, DELIMITER))
        splited_vector.push_back(splited_str);
    return splited_vector;
}

vector<int> split_time(string str_time)
{
    vector<int> splited_time;
    stringstream new_line(str_time);
    string splited;
    getline(new_line, splited, TIME_DELIMITER);
    splited_time.push_back(stoi(splited));
    getline(new_line, splited);
    splited_time.push_back(stoi(splited));
    return splited_time;
}

Time initial_time(vector<string> splited_vector)
{
    return {split_time(splited_vector[1])[0],
            split_time(splited_vector[1])[1],
            split_time(splited_vector[2])[0],
            split_time(splited_vector[2])[1]};
}

Translator new_translator(string line)
{
    vector<string> splited_vector = split_line(line);
    Translator new_translator;
    new_translator.name = splited_vector[0];
    new_translator.time_blocks.push_back(initial_time(splited_vector));
    for (int i = 3; i < splited_vector.size(); i++)
        new_translator.languages.push_back(splited_vector[i]);
    return new_translator;
}

Event new_event(string line)
{
    vector<string> splited_vector = split_line(line);
    Event new_event;
    new_event.name = splited_vector[0];
    new_event.time = initial_time(splited_vector);

    for (int i = 3; i < splited_vector.size(); i++)
    {
        Event_demanded_language new_event_language;
        new_event_language.name = splited_vector[i];
        new_event.demanded_languages.push_back(new_event_language);
    }
    return new_event;
}

Translator_list read_translators(fstream &input_file)
{
    Translator_list translator_list;
    int translators_num;
    string input_line;
    getline(input_file, input_line);
    translators_num = stoi(input_line);

    for (int i = 0; i < translators_num; i++)
    {
        getline(input_file, input_line);
        translator_list.push_back(new_translator(input_line));
    }
    return translator_list;
}

Event_list read_events(fstream &input_file)
{
    Event_list event_list;
    int event_num;
    string input_line;
    getline(input_file, input_line);
    event_num = stoi(input_line);
    for (int i = 0; i < event_num; i++)
    {
        getline(input_file, input_line);
        event_list.push_back(new_event(input_line));
    }
    return event_list;
}

Lists read_lists(const char *file)
{
    fstream input_file;
    input_file.open(file);

    Translator_list T_list;
    T_list = read_translators(input_file);
    Event_list E_list;
    E_list = read_events(input_file);
    return {E_list, T_list};
}

Available_language_list make_new_language(Available_language_list language_list, string translator_language, int translator_idx)
{
    Availabe_language new_language;
    new_language.name = translator_language;
    new_language.translators_idx.push_back(translator_idx);
    language_list.push_back(new_language);
    return language_list;
}

Available_language_list add_translators_idx_to_language(Available_language_list language_list, string translator_language, int translator_idx)
{
    for (int i = 0; i < language_list.size(); i++)
    {
        if (language_list[i].name == translator_language)
        {
            language_list[i].translators_idx.push_back(translator_idx);
            return language_list;
            break;
        }
    }
    language_list = make_new_language(language_list, translator_language, translator_idx);
    return language_list;
}

Available_language_list make_language_list(Translator_list T_list)
{
    Available_language_list language_list;
    for (int i = 0; i < T_list.size(); i++)
    {
        for (int j = 0; j < T_list[i].languages.size(); j++)
            language_list = add_translators_idx_to_language(language_list, T_list[i].languages[j], i);
    }
    return language_list;
}

bool is_better_language(int first_idx, int second_idx, Event_language_list language_list)
{
    if (language_list[first_idx].translators_idx.size() == language_list[second_idx].translators_idx.size())
        return second_idx < first_idx;
    if (language_list[first_idx].translators_idx.size() < language_list[second_idx].translators_idx.size())
        return false;
    return true;
}

int best_language(Event event, Available_language_list lan_list, vector<bool> chosen)
{
    int best_idx = 0;
    for (int i = 0; i < chosen.size(); i++)
    {
        if (chosen[i])
            continue;
        while (chosen[best_idx])
            best_idx++;
        if (is_better_language(best_idx, i, event.demanded_languages))
            best_idx = i;
    }
    return best_idx;
}

Event_language_list copy_translator_idx(Event_language_list event_lans, Available_language_list lan_list)
{
    for (int i = 0; i < event_lans.size(); i++)
    {
        for (int j = 0; j < lan_list.size(); j++)
        {
            if (event_lans[i].name == lan_list[j].name)
                event_lans[i].translators_idx = lan_list[j].translators_idx;
        }
    }
    return event_lans;
}

bool all_chosen(vector<bool> chosen)
{
    for (int i = 0; i < chosen.size(); i++)
    {
        if (!chosen[i])
            return false;
    }
    return true;
}

vector<int> to_minute(Time time)
{
    vector<int> min_time;
    min_time = {time.start_hour * 60 + time.start_minute, time.end_hour * 60 + time.end_minute};
    return min_time;
}

bool has_time(Time tran_time, Time event_time)
{
    if (to_minute(tran_time)[0] <= to_minute(event_time)[0] &&
        to_minute(tran_time)[1] >= to_minute(event_time)[1])
        return true;
    return false;
}

int free_time_blocks(Translator choosen_tran, Time event_time)
{
    for (int i = 0; i < choosen_tran.time_blocks.size(); i++)
    {
        if (has_time(choosen_tran.time_blocks[i], event_time))
            return i;
    }
    return NO_FREE_TIME_BLOCK;
}

bool is_better_translator(Translator first_tran, Translator second_tran)
{
    if (first_tran.languages.size() > second_tran.languages.size())
        return true;
    if (first_tran.languages.size() == second_tran.languages.size())
    {
        if (first_tran.name.compare(second_tran.name) > 0)
            return true;
    }
    return false;
}

string best_translator(Event_demanded_language language, Translator_list translator_list)
{
    if (!language.translators_idx.size())
        return NF_MESSAGE;
    int best_idx = 0;
    for (int i = 0; i < language.translators_idx.size(); i++)
    {
        if (is_better_translator(translator_list[language.translators_idx[best_idx]], translator_list[language.translators_idx[i]]))
            best_idx = i;
    }
    return translator_list[language.translators_idx[best_idx]].name;
}

vector<int> find_busy_translators(Event_demanded_language language, Translator_list translator_list, Time event_time)
{
    vector<int> busy_tran_idx;
    for (int i = 0; i < language.translators_idx.size(); i++)
    {
        if (free_time_blocks(translator_list[language.translators_idx[i]], event_time) == NO_FREE_TIME_BLOCK)
            busy_tran_idx.push_back(i);
    }
    return busy_tran_idx;
}
Event_demanded_language extract_busy_translators(Event_demanded_language language, Translator_list translator_list, Time event_time)
{
    vector<int> busy_tran_idx = find_busy_translators(language, translator_list, event_time);
    for (int i = 0; i < busy_tran_idx.size(); i++)
        language.translators_idx.erase(language.translators_idx.begin() + busy_tran_idx[i] - i);
    return language;
}

string asign_translator(Event_demanded_language language, Translator_list translator_list, Time event_time)
{
    language = extract_busy_translators(language, translator_list, event_time);
    return best_translator(language, translator_list);
}

Translator allocate_translator_time(Translator translator, Time event_time)
{
    int block_idx = free_time_blocks(translator, event_time);
    if (block_idx != NO_FREE_TIME_BLOCK)
    {

        int end_h = translator.time_blocks[block_idx].end_hour;
        int end_m = translator.time_blocks[block_idx].end_minute;
        translator.time_blocks[block_idx].end_hour = event_time.start_hour;
        translator.time_blocks[block_idx].end_minute = event_time.start_minute;
        translator.time_blocks.push_back({event_time.end_hour, event_time.end_minute,
                                          end_h, end_m});
    }
    return translator;
}

Translator_list allocate_translators_time(const Event_demanded_language &language, Translator_list translator_list, Time event_time)
{
    for (int j = 0; j < translator_list.size(); j++)
    {
        if (translator_list[j].name == language.chosen_translator)
            translator_list[j] = allocate_translator_time(translator_list[j], event_time);
    }
    return translator_list;
}

Planned_event plan_an_event(Event event, const Available_language_list &lan_list, Translator_list tran_list)
{
    vector<bool> chosen_languages(event.demanded_languages.size(), false);
    event.demanded_languages = copy_translator_idx(event.demanded_languages, lan_list);

    while (!all_chosen(chosen_languages))
    {
        int best_lan_idx = best_language(event, lan_list, chosen_languages);
        event.demanded_languages[best_lan_idx].chosen_translator =
            asign_translator(event.demanded_languages[best_lan_idx], tran_list, event.time);
        chosen_languages[best_lan_idx] = true;
        tran_list = allocate_translators_time(event.demanded_languages[best_lan_idx], tran_list, event.time);
    }
    return {event, tran_list};
}

Event_list plan_out(Event_list event_list, const Available_language_list &lan_list, Translator_list translator_list)
{
    for (int i = 0; i < event_list.size(); i++)
    {
        Planned_event new_plan = plan_an_event(event_list[i], lan_list, translator_list);
        event_list[i] = new_plan.event;
        translator_list = new_plan.translator_list;
    }
    return event_list;
}

void print_each_event(const Event &event)
{
    cout << event.name << endl;
    for (int i = 0; i < event.demanded_languages.size(); i++)
        cout << event.demanded_languages[i].name << ": "
             << event.demanded_languages[i].chosen_translator
             << endl;
}

void print_plan(const Event_list &event_list)
{
    for (int i = 0; i < event_list.size(); i++)
        print_each_event(event_list[i]);
}

int main(int argc, char *argv[])
{
    Lists lists = read_lists(argv[1]);
    Available_language_list language_list = make_language_list(lists.translator_list);
    lists.event_list = plan_out(lists.event_list, language_list, lists.translator_list);
    print_plan(lists.event_list);
}