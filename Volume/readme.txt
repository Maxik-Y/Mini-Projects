Inputs: path to the input audio file (input.wav), path for saving the new audio file (output.wav), and a volume factor.
This program modifies the volume of a WAV audio file. It first copies the WAV file header (the first 78 bytes) 
unchanged, then reads the remainder of the file one 16-bit audio sample at a time, multiplies each sample by 
the specified factor, and writes the result to a new file.