#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prototypes
void parse(const char* file_name);

int main(void){
    parse("C:\\Users\\corey\\Music\\09 - Is It True.mp3");
    return 0;
}

// subroutines
void parse(const char* file_name) {

    // open file
    FILE* file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Couldn't open %s\n", file_name);
        return;
    }

    // get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    // reset pointer location
    rewind(file);

    // make sure file is correct size
    if (file_size < 128) {
        printf("Invalid file: %s\n", file_name);
        fclose(file);
        return;
    }

    // get ID3 tag into buffer
    fseek(file, -128, SEEK_END);
    unsigned char buffer[128];
    size_t read_size = fread(buffer, 1, sizeof(buffer), file);
    fclose(file);

    // make sure read size is correct
    if (read_size != sizeof(buffer)) {
        printf("Failed to read ID3 tag from file: %s\n", file_name);
        return;
    }

    // compare header "tag"
    if (memcmp(buffer, "TAG", 3) != 0) {
        printf("No ID3 tag found in file: %s\n", file_name);
        return;
    }

    // create string buffers for mp3 tag data
    char title[31], artist[31], album[31], year[5];

    // copy tag buffer data from into output buffers
    memcpy(title, buffer + 3, 30);
    memcpy(artist, buffer + 33, 30);
    memcpy(album, buffer + 63, 30);
    memcpy(year, buffer + 93, 4);

    // terminate strings
    title[30] = artist[30] = album[30] = year[4] = '\0';

    // output data
    printf("%s - %s (%s, %s)\n", artist, title, album, year);

}
