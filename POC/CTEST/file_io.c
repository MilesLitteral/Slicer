
/*******************************************************************************
*
* file_io.c
* 
* Interface functions for reading and writing audio files with libsndfile.
*
* Copyright (C) 2012 Adam James Wilson <ajw@adamjameswilson.info>.
* All rights reserved.
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <sndfile.h>
#include "file_io.h"




double find_peak(double *array, int array_size)
/*
* Return the peak amplitude in 'array'.
*/
{
	double peak = 0.0;
	double current;
	int i;
	for (i=0;i<array_size;i++)
	{
		current = fabs(array[i]);
		if (current > peak)
		{
			peak = current;
		}
	}
	/*
	printf("peak = %f\n", peak);
	*/
	return peak;
}




void normalize(double *array, int array_size, double scale_to)
/*
* Destructively scale array values a[n] by n('scale_to'/peak). 
*/
{
	if ((scale_to > 1.0) || (scale_to < 0.0))
	{
		perror("In function 'normalize()', argument 'scale_to' must be between 0.0 and 1.0.\n");
		exit(1); /* requires stdlib.h */
	}
	else
	{
		double peak = find_peak(array, array_size);
		double multiplier = (scale_to / peak);
		int i;
		for (i = 0; i < array_size; i++)
		{
			array[i] = (array[i] * multiplier);
		}
	}
}




SNDFILE* handle_sndfile_open(const char *path, int mode, SF_INFO *sfinfo, const char *msg)
{
	SNDFILE *sndfile;
	if (! (sndfile = sf_open(path, mode, sfinfo)))
	{
		perror(msg);
		printf("errno = %d.\n", errno);
		exit(1); /* requires stdlib.h */
	}
	return sndfile;
}




void handle_format_check(SF_INFO *sfinfo, const char *msg)
{
	if (! sf_format_check(sfinfo))
	{
		perror(msg);
		printf("errno = %d.\n", errno);
		exit(1); /* requires stdlib.h */
	}
}




void convert_snd_file_format(const char *input_path, const char *output_path, int format, int to_mono)
/*
* Convert between file formats, returning only channel one to the output file if
* 'to_mono' == 1, or all channels otherwise. To look up a valid sound file
* format number, see 'libsndfile_formats_as_integers.txt'.
* TO DO: check file extension in 'output_path' against 'format' and autocorrect;
* do some error checking on sf_read and sf_write; clean up corrupted out files.
*/
{
	SNDFILE *infile;
	SF_INFO sfinfo_in;

	infile = handle_sndfile_open(input_path, SFM_READ, &sfinfo_in, \
		"There was a problem opening the file specified by argument 'input_file' to function 'convert_snd_file_format'");

	/*
	printf("input file samplerate: %d\n",sfinfo_in.samplerate);
	printf("input file frames: %d\n",sfinfo_in.frames);
	printf("input file channels: %d\n",sfinfo_in.channels);
	printf("input file format: %d\n",sfinfo_in.format);
	*/
	
	SNDFILE *outfile;
	SF_INFO sfinfo_out;
	sfinfo_out.format = format;	
	sfinfo_out.samplerate = sfinfo_in.samplerate;
	
	/*
	* Channels are interleaved upon read-out. If 'to_mono' == 1, extract the
	* first channel only from the read-in array and move to an intermediary
	* array for output, else use the initial read-in array for output.
	*/
	if (to_mono == 1)
	{
		sfinfo_out.channels = 1;
		
		/***********************************************************************
		* This section is duplicated in both branches of the parent conditional
		* in order to keep memory usage as low as possible in the presence of 
		* I/O errors. An external function to encapsulate this code block would
		* likely decrease comprehensibility.
		***********************************************************************/
		/*
	 	* Check for valid format; requires SF_INFO.samplerate, SF_INFO.channels,
	 	* and SF_INFO.format to be set.
	 	*/
		handle_format_check(&sfinfo_out, \
			"An invalid sound file format was passed via the 'format' argument to function 'convert_snd_file_format'");	
		outfile = handle_sndfile_open(output_path, SFM_WRITE, &sfinfo_out, \
			"There was a problem opening the file specified by argument 'output_path' to function 'convert_snd_file_format'");
		/*
	 	* Unfortunately, libsndfile forces us to read in ALL of the data from a 
	 	* source file, even if we just want data from one of the channels.
	 	*/		
		int data_in_size = (sfinfo_in.frames * sfinfo_in.channels);
		double data_in[data_in_size];
		/*
		* We must use complementary sf_read/sf_write methods. For example, if we
		* read in audio data using 'sf_read_double', we need to write using
		* 'sf_write_double', even if we are writing to an interger PCM format;
		* libsndfile will take care of conversions between numerical types.
		*/
		sf_read_double(infile, data_in, data_in_size);
		/*
		***********************************************************************/
		
		int data_out_size = (sfinfo_in.frames / sfinfo_in.channels);
		double data_out[data_out_size];
		
		int i;
		for (i = 0; i < sfinfo_in.frames; i++)
		{
			data_out[i] = data_in[(i * sfinfo_in.channels)];
		}
		
		sf_write_double(outfile, data_out, sfinfo_in.frames);
	} 
	else
	{
		sfinfo_out.channels = sfinfo_in.channels;
		
		/***********************************************************************
		* This section is duplicated in both branches of the parent conditional
		* in order to keep memory usage as low as possible in the presence of 
		* I/O errors. An external function to encapsulate this code block would
		* likely decrease comprehensibility.
		***********************************************************************/
		/*
	 	* Check for valid format; requires SF_INFO.samplerate, SF_INFO.channels,
	 	* and SF_INFO.format to be set.
	 	*/
		handle_format_check(&sfinfo_out, \
			"An invalid sound file format was passed via the 'format' argument to function 'convert_snd_file_format'");	
		outfile = handle_sndfile_open(output_path, SFM_WRITE, &sfinfo_out, \
			"There was a problem opening the file specified by argument 'output_path' to function 'convert_snd_file_format'");
		/*
	 	* Unfortunately, libsndfile forces us to read in ALL of the data from a 
	 	* source file, even if we just want data from one of the channels.
	 	*/		
		int data_in_size = (sfinfo_in.frames * sfinfo_in.channels);
		double data_in[data_in_size];
		/*
		* We must use complementary sf_read/sf_write methods. For example, if we
		* read in audio data using 'sf_read_double', we need to write using
		* 'sf_write_double', even if we are writing to an interger PCM format;
		* libsndfile will take care of conversions between numerical types.
		*/
		sf_read_double(infile, data_in, data_in_size);
		/*
		***********************************************************************/
		
		sf_write_double(outfile, data_in, data_in_size);
	}
	
	sf_close(infile);
	sf_close(outfile);
	
	/*
	outfile = sf_open(output_path, SFM_READ, &sfinfo_out);
	printf("output file samplerate: %d\n",sfinfo_out.samplerate);
	printf("output file frames: %d\n",sfinfo_out.frames);
	printf("output file channels: %d\n",sfinfo_out.channels);
	printf("output file format: %d\n",sfinfo_out.format);
	sf_close(outfile);
	*/
}
