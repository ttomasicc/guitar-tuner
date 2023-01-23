#include "Notes.h"
#include <Arduino.h>
#include <vector>

// Checks if the given peak is within the range for a given note
inline bool Notes::is_within_range(note note, double peak)
{
    return (peak >= note.tuning - ALLOWED_RANGE && peak <= note.tuning + ALLOWED_RANGE) ||
        (peak >= (note.tuning * 2) - ALLOWED_RANGE && peak <= (note.tuning * 2) + ALLOWED_RANGE);
};

// Returns the note for a given peak frequency; if peak doesn't match any
// note's frequency range, the function returns an invalid note
note Notes::get_note_within_range(short peak)
{
    for (note const note : standard_tuning)
    {
        if (is_within_range(note, peak))
        {
            return note;
        };
    };

    return note{"000", 0, false};
};
