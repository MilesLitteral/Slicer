
/*******************************************************************************
*
* main.c
*
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <sndfile.h> // need this -- will not be included even if in file_io.h
#include "file_io.h"
#include <string.h>
//#include <fftw3.h>

double until(int current_number, double total)
{
	double leftover = total - (double)current_number;
	if (total - current_number > 4000)
	{
		return 1;
	}
	else
	{
		return leftover;
	}
}

int main()
{
	SNDFILE *infileA, *infileB, *infileC, *outfile;
	SF_INFO sfinfo_infileA, sfinfo_infileB, sfinfo_infileC, sfinfo_outfile;
	
	infileA = handle_sndfile_open("/Users/v314student/Desktop/CTEST/choir.wav", SFM_READ, &sfinfo_infileA, \
		"There was a problem opening the audio file.");

	infileB = handle_sndfile_open("/Users/v314student/Desktop/CTEST/Waterlong.wav", SFM_READ, &sfinfo_infileB, \
		"There was a problem opening the audio file.");

	infileC = handle_sndfile_open("/Users/v314student/Desktop/CTEST/ichoseasoundfileokfine.wav", SFM_READ, &sfinfo_infileC, \
		"There was a problem opening the audio file.");

	int chooser = rand() % 3;

	printf("Infile Sample Rate: %d\n\n", sfinfo_infileA.samplerate);
	printf("Infile Frames: %lld\n\n", sfinfo_infileA.frames);
	printf("Infile Channels: %d\n\n", sfinfo_infileA.channels);
	
	sfinfo_outfile.samplerate = sfinfo_infileA.samplerate;
	sfinfo_outfile.channels = sfinfo_infileA.channels;
	sfinfo_outfile.format = sfinfo_infileA.format;

	outfile = handle_sndfile_open("/Users/v314student/Desktop/CTEST/choirchunk.wav", SFM_WRITE, &sfinfo_outfile, \
		"There was a problem opening the file.");

	printf("allocating infile\n");

	double *infile_dataA;
	infile_dataA = malloc(sfinfo_infileA.frames*sizeof(double));

	double *infile_dataB;
	infile_dataB = malloc(sfinfo_infileB.frames*sizeof(double));

	double *infile_dataC;
	infile_dataC = malloc(sfinfo_infileC.frames*sizeof(double));

	printf("allocating outfile\n");

	double *outfile_data;
	outfile_data = calloc(sfinfo_infileA.frames, sizeof(double));

	printf("calling sf_read_double()\n");

	sf_read_double(infileA, infile_dataA, sfinfo_infileA.frames);
	sf_read_double(infileB, infile_dataB, sfinfo_infileB.frames);
	sf_read_double(infileC, infile_dataC, sfinfo_infileC.frames);

	// This currently determines when to write and how many sampels to write in conjunct.
	// In the future we should apply an algorithm that actually determines these inedpendently.
	int spacer = 7639; // Originally set to 7639 because it's an even multiple of our hard coded files.

	//add an array for remembering (not repeating) stuff

	double stepper = 4000;

	double fadeTime = 0.5f;
	double outputGain = 0;
	double gainProgressionPerSample = 1.0f/(fadeTime*sfinfo_infileA.samplerate);
	double fadeInStop = fadeTime*sfinfo_infileA.samplerate;
	double fadeOutBegin = (sfinfo_infileA.frames - fadeInStop);

	for (int i = 0; i < sfinfo_infileA.frames; i+=4000)
	{
		printf("top level loop, Level %d of %lld\n", i, sfinfo_infileA.frames);

		/* code */
		if (until(i, sfinfo_infileA.frames) != 1)
		{
			stepper = until(i, sfinfo_infileA.frames);
		}
		for (int j = i; j <= i + stepper; j++)
		{
			if(j < fadeInStop)
			{
				outputGain += gainProgressionPerSample;
			}

			if(j > fadeOutBegin)
			{
				outputGain -= gainProgressionPerSample;
			}
			
			//Sacred print statements
			//printf("second level loop: %d of %lld in pass %d \n", j, sfinfo_infile.frames, i);
			//printf("%f\n", infile_data[j]);
			//outfile_data[i - j] = infile_data[j]; //important shit
			int x = rand() % sfinfo_infileA.frames;

            infile_dataA[x] = infile_dataA[x] * outputGain;
            infile_dataB[x] = infile_dataB[x] * outputGain;
            infile_dataC[x] = infile_dataC[x] * outputGain;

			if(j % 7639 == 0){
				double fadeInStop = fadeTime*sfinfo_infileA.samplerate;
				double fadeOutBegin = (sfinfo_infileA.frames - fadeInStop);
				if (chooser == 0)
				{
					printf("PYONG %d\n", j);
					sf_write_double(outfile, &infile_dataA[x], 7639);
				}
				else if (chooser == 1)
				{
					printf("file b %d\n", j);
					sf_write_double(outfile, &infile_dataB[x], 7639);
				}
				else
				{
					printf("file c BIATCH %d\n", j);
					sf_write_double(outfile, &infile_dataC[x], 7639);
				}
			}
			chooser = rand() % 3;
		}
	}
	//Get the file
	//Get the size of the file
	//Get pointer pairs to indicate segments of arbitrary length throughout the file
	//Randomize those pointers
	//Allocate memory for a file equal in size to the original file
	//Write to the file from those pointers.
	//Save that file
	printf("are we sure we're sure?\n");

	printf("Freeing p\n");
	printf("Freeing infile\n");
	free(infileA);
	printf("Freeing infile_data\n");
	free(infile_dataA);
	printf("Freeing outfile\n");
	free(outfile);
	printf("Freeing outfile_data\n");
	free(outfile_data);

	printf("MASTERS OF THE UNIVERSE\n");

	
	return 0; //no errors
	
}
