#ifndef FILE_IO_H_INCLUDED
#define FILE_IO_H_INCLUDED

double find_peak(double *array, int array_size);

void normalize(double *array, int array_size, double scale_to);

void convert_snd_file_format(const char *input_path, const char *output_path, int format, int to_mono);

SNDFILE* handle_sndfile_open(const char *path, int mode, SF_INFO *sfinfo, const char *msg);

void handle_format_check(SF_INFO *sfinfo, const char *msg);

#endif