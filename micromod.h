//
//	C++ version of micromod
//
//
namespace MicroMod
{

#define MAX_CHANNELS 16
#define MAX_INSTRUMENTS 32

struct note {
        unsigned short key;
        unsigned char instrument, effect, param;
};

struct instrument {
        unsigned char volume, fine_tune;
        unsigned long loop_start, loop_length;
        signed char *sample_data;
};

struct channel {
        struct note note;
        unsigned short period, porta_period;
        unsigned long sample_offset, sample_idx, step;
        unsigned char volume, panning, fine_tune, ampl;
        unsigned char id, instrument, assigned, porta_speed, pl_row, fx_count;
        unsigned char vibrato_type, vibrato_phase, vibrato_speed, vibrato_depth;
        unsigned char tremolo_type, tremolo_phase, tremolo_speed, tremolo_depth;
        signed char tremolo_add, vibrato_add, arpeggio_add;
};


class CMicroMod
{
public:
	CMicroMod();
	CMicroMod(signed char *data, long sampling_rate);
	//CMicroMod(char *fileName);

	// "External/interface" functions
	// Calculate the length in bytes of a module file given the 1084-byte header.
	// Returns -1 if the data is not recognised as a module.
	static long CalculateModFileLen(signed char *module_header);

	// Set the player to play the specified module data.
	// Returns -1 if the data is not recognised as a module.
	// Returns -2 if the sampling rate is less than 8000hz.
	long Initialise(signed char *data, long sampling_rate);

	// Obtains song and instrument names from the module.
	// The song name is returned as instrument 0.
	// The name is copied into the location pointed to by string,
	// and is at most 23 characters long, including the trailing null.
	void GetString(long instrument, char *string);

	// Returns the total song duration in samples at the current sampling rate.
	long CalculateSongDuration();

	// Jump directly to a specific pattern in the sequence.
	void SetPosition(long pos);

	// Calculate the specified number of samples of audio.
	// Output buffer must be zeroed.
	void GetAudio(short *output_buffer, long count);

private:
	// "Internal" functions
	void set_tempo( long tempo );
	void update_frequency( struct channel *chan );
	void tone_portamento( struct channel *chan );
	void volume_slide( struct channel *chan, long param );
	long waveform( long phase, long type );
	void vibrato( struct channel *chan );
	void tremolo( struct channel *chan );
	void trigger( struct channel *channel );
	void channel_row( struct channel *chan );
	void channel_tick( struct channel *chan );
	long sequence_row();
	long sequence_tick();
	void resample( struct channel *chan, short *buf, long offset, long count );


private:
	signed char *module_data;
	unsigned char *pattern_data, *sequence;
	long song_length, restart, num_patterns, num_channels;
	long sample_rate, c2_rate, gain, tick_len, tick_offset;
	long pattern, break_pattern, row, next_row, tick;
	long speed, pl_count, pl_channel, random_seed;
	struct instrument instruments[ MAX_INSTRUMENTS ];
	struct channel channels[ MAX_CHANNELS ];
};


}
