Input: path to a memory card image file (e.g., card.raw)
Recovers lost JPEG photos from a memory card image (raw file). The program reads the file in 512-byte 
blocks, searches for unique marker bytes indicating the start of a JPEG image, and sequentially saves 
the discovered data into new files named 000.jpg, 001.jpg, and so on.