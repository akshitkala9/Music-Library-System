#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT 100
#define MAX_LENGTH 100

char songTitles[LIMIT][MAX_LENGTH];
char songArtists[LIMIT][MAX_LENGTH];
char songCategories[LIMIT][20];
int songFavorites[LIMIT];
int songCount = 0;

void loadSongs();
void saveSongs();
void addSong();
void removeSong();
void searchSong();
void displaySongs();

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void loadSongs() {
    FILE *fp = fopen("songs.txt", "r");

    if (fp == NULL) {
        return;
    }

    while (fscanf(fp,
                  "%99[^|]|%99[^|]|%19[^|]|%d\n",
                  songTitles[songCount],
                  songArtists[songCount],
                  songCategories[songCount],
                  &songFavorites[songCount]) == 4) {

        songCount++;

        if (songCount >= LIMIT)
            break;
    }

    fclose(fp);
}

void saveSongs() {
    FILE *fp = fopen("songs.txt", "w");

    if (fp == NULL) {
        printf("Error saving songs!\n");
        return;
    }

    for (int i = 0; i < songCount; i++) {
        fprintf(fp, "%s|%s|%s|%d\n",
                songTitles[i],
                songArtists[i],
                songCategories[i],
                songFavorites[i]);
    }

    fclose(fp);
}

void addSong() {
    if (songCount >= LIMIT) {
        printf("Library is full!\n");
        return;
    }

    int choice;

    printf("Enter Song Title: ");
    fgets(songTitles[songCount], MAX_LENGTH, stdin);
    removeNewline(songTitles[songCount]);

    printf("Enter Artist Name: ");
    fgets(songArtists[songCount], MAX_LENGTH, stdin);
    removeNewline(songArtists[songCount]);

    printf("\nChoose Category:\n");
    printf("1. Rock\n");
    printf("2. Pop\n");
    printf("3. Old\n");
    printf("4. Others\n");
    printf("5. Uncategorized\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar();

    switch(choice) {
        case 1: strcpy(songCategories[songCount], "Rock"); break;
        case 2: strcpy(songCategories[songCount], "Pop"); break;
        case 3: strcpy(songCategories[songCount], "Old"); break;
        case 4: strcpy(songCategories[songCount], "Others"); break;
        default: strcpy(songCategories[songCount], "Uncategorized");
    }

    printf("Favorite? (1 = Yes, 0 = No): ");
    scanf("%d", &songFavorites[songCount]);
    getchar();

    songCount++;

    saveSongs();

    printf("Song added successfully!\n");
}

void removeSong() {
    char title[MAX_LENGTH];
    int found = 0;

    printf("Enter Song Title to Remove: ");
    fgets(title, MAX_LENGTH, stdin);
    removeNewline(title);

    for (int i = 0; i < songCount; i++) {

        if (strcmp(songTitles[i], title) == 0) {

            found = 1;

            for (int j = i; j < songCount - 1; j++) {
                strcpy(songTitles[j], songTitles[j + 1]);
                strcpy(songArtists[j], songArtists[j + 1]);
                strcpy(songCategories[j], songCategories[j + 1]);
                songFavorites[j] = songFavorites[j + 1];
            }

            songCount--;

            saveSongs();

            printf("Song removed successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Song not found!\n");
    }
}

void searchSong() {
    char keyword[MAX_LENGTH];
    int found = 0;

    printf("Enter Song Title or Artist: ");
    fgets(keyword, MAX_LENGTH, stdin);
    removeNewline(keyword);

    for (int i = 0; i < songCount; i++) {

        if (strcmp(songTitles[i], keyword) == 0 ||
            strcmp(songArtists[i], keyword) == 0) {

            printf("\n*** Song Found ***\n");
            printf("Title    : %s\n", songTitles[i]);
            printf("Artist   : %s\n", songArtists[i]);
            printf("Category : %s\n", songCategories[i]);
            printf("Favorite : %s\n",
                   songFavorites[i] ? "Yes" : "No");

            found = 1;
        }
    }

    if (!found) {
        printf("Song not found!\n");
    }
}

void displaySongs() {

    printf("\n======= MUSIC LIBRARY =======\n");

    if (songCount == 0) {
        printf("No songs available.\n");
        return;
    }

    for (int i = 0; i < songCount; i++) {

        printf("\nSong #%d\n", i + 1);
        printf("Title    : %s\n", songTitles[i]);
        printf("Artist   : %s\n", songArtists[i]);
        printf("Category : %s\n", songCategories[i]);
        printf("Favorite : %s\n",
               songFavorites[i] ? "Yes" : "No");
    }
}

int main() {

    int choice;

    loadSongs();

    do {

        printf("\n");
        printf("====================================\n");
        printf("      CPLAYER MUSIC LIBRARY\n");
        printf("====================================\n");
        printf("1. Add Song\n");
        printf("2. Remove Song\n");
        printf("3. Search Song\n");
        printf("4. Display Songs\n");
        printf("5. Exit\n");
        printf("Enter Choice: ");

        scanf("%d", &choice);
        getchar();

        switch(choice) {

            case 1:
                addSong();
                break;

            case 2:
                removeSong();
                break;

            case 3:
                searchSong();
                break;

            case 4:
                displaySongs();
                break;

            case 5:
                printf("Thank you for using CPlayer!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 5);

    return 0;
}