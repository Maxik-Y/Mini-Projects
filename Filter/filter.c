#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#pragma pack(push, 1)

typedef struct
{
    uint16_t bfType;      // Тип файлу (має бути 'BM' - 0x4D42)
    uint32_t bfSize;      // Розмір файлу в байтах
    uint16_t bfReserved1; // Зарезервовано
    uint16_t bfReserved2; // Зарезервовано
    uint32_t bfOffBits;   // Зміщення до даних пікселів
} BITMAPFILEHEADER;

typedef struct
{
    uint32_t biSize;         // Розмір цього заголовка
    int32_t biWidth;         // Ширина зображення
    int32_t biHeight;        // Висота зображення (якщо додатна - зображення перевернуте, знизу вгору)
    uint16_t biPlanes;       // Кількість кольорових площин (завжди 1)
    uint16_t biBitCount;     // Кількість біт на піксель (ми очікуємо 24)
    uint32_t biCompression;  // Тип стиснення (0 - без стиснення)
    uint32_t biSizeImage;    // Розмір самих даних зображення
    int32_t biXPelsPerMeter; // Роздільна здатність по X
    int32_t biYPelsPerMeter; // Роздільна здатність по Y
    uint32_t biClrUsed;      // Кількість кольорів у палітрі
    uint32_t biClrImportant; // Важливі кольори
} BITMAPINFOHEADER;

#pragma pack(pop)

typedef struct
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGB;

void free_image(RGB **pixels, int32_t height)
{
    if (pixels == NULL)
        return;
    for (int i = 0; i < height; i++)
    {
        free(pixels[i]);
    }
    free(pixels);
}

void grayscale(RGB **pixels, BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, int padding, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = (pixels[i][j].red + pixels[i][j].green + pixels[i][j].blue) / 3;
            pixels[i][j].red = average;
            pixels[i][j].green = average;
            pixels[i][j].blue = average;
        }
    }
}

void reflect(RGB **pixels, BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, int padding, int width, int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGB temp = pixels[i][j];
            pixels[i][j].red = pixels[i][width - j - 1].red;
            pixels[i][j].green = pixels[i][width - j - 1].green;
            pixels[i][j].blue = pixels[i][width - j - 1].blue;
            pixels[i][width - j - 1].red = temp.red;
            pixels[i][width - j - 1].green = temp.green;
            pixels[i][width - j - 1].blue = temp.blue;
        }
    }
}

void blur(RGB **pixels, BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, int padding, int width, int height)
{
    RGB **temp = (RGB **)malloc(height * sizeof(RGB *));
    for (int i = 0; i < height; i++)
    {
        temp[i] = (RGB *)malloc(width * sizeof(RGB));
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = pixels[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0, sumGreen = 0, sumRed = 0;
            float count = 0.0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumBlue += temp[ni][nj].blue;
                        sumGreen += temp[ni][nj].green;
                        sumRed += temp[ni][nj].red;
                        count++;
                    }
                }
            }

            pixels[i][j].blue = round(sumBlue / count);
            pixels[i][j].green = round(sumGreen / count);
            pixels[i][j].red = round(sumRed / count);
        }
    }
}

void edges(RGB **pixels, BITMAPFILEHEADER file_header, BITMAPINFOHEADER info_header, int padding, int width, int height)
{
    RGB **temp = (RGB **)malloc(height * sizeof(RGB *));
    for (int i = 0; i < height; i++)
    {
        temp[i] = (RGB *)malloc(width * sizeof(RGB));
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = pixels[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxBlue = 0, gxGreen = 0, gxRed = 0;
            float gyBlue = 0, gyGreen = 0, gyRed = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        float blue = temp[ni][nj].blue;
                        float green = temp[ni][nj].green;
                        float red = temp[ni][nj].red;

                        int weightX = Gx[di + 1][dj + 1];
                        int weightY = Gy[di + 1][dj + 1];

                        gxBlue += blue * weightX;
                        gxGreen += green * weightX;
                        gxRed += red * weightX;

                        gyBlue += blue * weightY;
                        gyGreen += green * weightY;
                        gyRed += red * weightY;
                    }
                }
            }

            int finalBlue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int finalGreen = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int finalRed = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            pixels[i][j].blue = (finalBlue > 255) ? 255 : finalBlue;
            pixels[i][j].green = (finalGreen > 255) ? 255 : finalGreen;
            pixels[i][j].red = (finalRed > 255) ? 255 : finalRed;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./filter.exe img.bmp filter_type\n");
        return 1;
    }

    const char *input_file = argv[1];

    FILE *in = fopen(input_file, "rb");
    if (!in)
    {
        printf("Помилка: не вдалося відкрити файл %s\n", input_file);
        return 1;
    }

    BITMAPFILEHEADER file_header;
    BITMAPINFOHEADER info_header;

    fread(&file_header, sizeof(BITMAPFILEHEADER), 1, in);
    fread(&info_header, sizeof(BITMAPINFOHEADER), 1, in);

    if (file_header.bfType != 0x4D42 || info_header.biBitCount != 24 || info_header.biCompression != 0)
    {
        printf("Error: support more than 24-bit uncompressed BMP files.\n");
        fclose(in);
        return 1;
    }

    int width = info_header.biWidth;
    int height = abs(info_header.biHeight);

    int padding = (4 - (width * sizeof(RGB)) % 4) % 4;

    RGB **pixels = (RGB **)malloc(height * sizeof(RGB *));
    for (int i = 0; i < height; i++)
    {
        pixels[i] = (RGB *)malloc(width * sizeof(RGB));
    }

    fseek(in, file_header.bfOffBits, SEEK_SET);

    for (int i = 0; i < height; i++)
    {
        fread(pixels[i], sizeof(RGB), width, in);
        fseek(in, padding, SEEK_CUR);
    }

    char *output_file;

    if (strcmp(argv[2], "grayscale"))
    {
        grayscale(pixels, file_header, info_header, padding, width, height);
        output_file = "grayscale.bmp";
    }
    else if (strcmp(argv[2], "reflect"))
    {
        reflect(pixels, file_header, info_header, padding, width, height);
        output_file = "reflect.bmp";
    }
    else if (strcmp(argv[2], "blur"))
    {
        blur(pixels, file_header, info_header, padding, width, height);
        output_file = "blur.bmp";
    }
    else if (strcmp(argv[2], "edges"))
    {
        grayscale(pixels, file_header, info_header, padding, width, height);
        edges(pixels, file_header, info_header, padding, width, height);
        output_file = "edges.bmp";
    }
    else
    {
        printf("This function does not exist.\n");
    }

    FILE *out = fopen(output_file, "wb");
    if (!out)
    {
        printf("Error: failed to create file %s\n", output_file);
        free_image(pixels, height);
        return 1;
    }

    fwrite(&file_header, sizeof(BITMAPFILEHEADER), 1, out);
    fwrite(&info_header, sizeof(BITMAPINFOHEADER), 1, out);

    uint8_t zero_padding[3] = {0, 0, 0};
    for (int i = 0; i < height; i++)
    {
        fwrite(pixels[i], sizeof(RGB), width, out);
        fwrite(zero_padding, 1, padding, out);
    }
    fclose(out);
    printf("Result saved in %s\n", output_file);

    fclose(in);
    free_image(pixels, height);

    return 0;
}