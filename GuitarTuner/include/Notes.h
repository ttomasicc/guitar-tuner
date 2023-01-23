#ifndef Notes_h
#define Notes_h

#include <Arduino.h>
#include <vector>

#define ALLOWED_RANGE 3

struct note
{
    char name[4];
    short tuning;
    bool valid;
};

class Notes
{
private:
    std::vector<note> standard_tuning{
        note{"E2", 82, true},  note{"A2", 110, true}, note{"D3", 146, true},
        note{"G3", 196, true}, note{"B3", 247, true}, note{"E4", 330, true}};

    inline bool is_within_range(note note, double peak);

public:
    note get_note_within_range(short peak);
};

#endif
