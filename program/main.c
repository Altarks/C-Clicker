#include "gfx/gfx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define NUMBER_OF_MODIFIERS 18

/*
 * Author: 	    Hugo M.
 * Date:        2024-02-21
 * Description:
 * Clicker game with gfx library
 */

#define COOKIE_SIZE 250
#define PRICE_MULTIPLIER 1.15
int marging_top = 0;

struct modifier
{
    char name[50];
    int level;
    long double cost;
    long double ops;
};

/// @brief Prépare le texte à écrire
/// @param result pointeur vers le buffer de sortie
/// @param value valeur à afficher
void prepare_to_write(char *result, long double value)
{
    double value_double = value;
    if (value >= 100000000000000000)
    {
        value_double = value / 100000000000000000.0;
        sprintf(result, ":%.1f%s", value_double, "qi");
    }
    else if (value >= 100000000000000)
    {
        value_double = value / 100000000000000.0;
        sprintf(result, ":%.1f%s", value_double, "qa");
    }
    else if (value >= 100000000000)
    {
        value_double = value / 100000000000.0;
        sprintf(result, ":%.1f%c", value_double, 't');
    }
    else if (value >= 100000000)
    {
        value_double = value / 100000000.0;
        sprintf(result, ":%.1f%c", value_double, 'b');
    }
    else if (value >= 1000000)
    {
        value_double = value / 1000000.0;
        sprintf(result, ":%.1f%c", value_double, 'm');
    }
    else if (value >= 1000)
    {
        value_double = value / 1000.0;
        sprintf(result, ":%.1f%c", value_double, 'k');
    }
    else
    {
        sprintf(result, ":%d", (int)value);
    }
}

/// @brief Affiche les modificateurs
/// @param level le niveau du joueur
/// @param count le nombre de cookies
/// @param multiplier_modifier le modificateur de clic
/// @param modifiers les modificateurs
/// @param buffer un buffer pour stocker les valeurs
/// @param buffer_bis un second buffer pour stocker les valeurs
void displayModifiers(int level, long double count, struct modifier* multiplier_modifier, struct modifier* modifiers, char* buffer[100], char* buffer_bis[100])
{
    // Background
    gfx_color(215, 218, 222);
    gfx_fillrect(SCREEN_WIDTH / 2 - 20, 20  - marging_top, SCREEN_WIDTH / 2 + 750, 100 - marging_top);
    gfx_fillrect(SCREEN_WIDTH / 2 - 20, 120  - marging_top, SCREEN_WIDTH / 2 + 750, 200 - marging_top);
    for (int i = 1; i <= level; i++)
    {
        gfx_fillrect(SCREEN_WIDTH / 2 - 20, 120 + i * 100  - marging_top, SCREEN_WIDTH / 2 + 750, 200 + i * 100 - marging_top);
    }
    gfx_color(237, 241, 245);
    gfx_fillrect(SCREEN_WIDTH / 2 - 20, 220 + level * 100  - marging_top, SCREEN_WIDTH / 2 + 750, 300 + level * 100 - marging_top);
    
    // Click multiplicator
    if (count >= multiplier_modifier->cost)
    {
        gfx_color(0, 0, 0);
    }
    else
    {
        gfx_color(94, 96, 98);
    }

    strcpy(buffer_bis, "click multiplier");
    prepare_to_write(buffer, multiplier_modifier->level);
    strcat(buffer_bis, buffer);
    gfx_drawPixelString(SCREEN_WIDTH / 2, 50 - marging_top, buffer_bis, 5);

    strcpy(buffer_bis, "cost");
    prepare_to_write(buffer, multiplier_modifier->cost);
    strcat(buffer_bis, buffer);
    gfx_drawPixelString(SCREEN_WIDTH/2 + 580, 35 - marging_top, buffer_bis, 3);

    strcpy(buffer_bis, "cpc");
    prepare_to_write(buffer, multiplier_modifier->level);
    strcat(buffer_bis, buffer);
    gfx_drawPixelString(SCREEN_WIDTH/2 + 580, 70 - marging_top, buffer_bis, 3);
    
    // Modifiers
    for (int i = 0; i < level + 1; i++)
    {
        if (count >= modifiers[i].cost)
        {
            gfx_color(0, 0, 0);
        }
        else
        {
            gfx_color(94, 96, 98);
        }
        strcpy(buffer_bis, modifiers[i].name);
        prepare_to_write(buffer, modifiers[i].level);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(SCREEN_WIDTH / 2, 150 + i * 100  - marging_top, buffer_bis, 5);

        strcpy(buffer_bis, "cost");
        prepare_to_write(buffer, modifiers[i].cost);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(SCREEN_WIDTH/2 + 580, 135 + i * 100 - marging_top, buffer_bis, 3);

        strcpy(buffer_bis, "cps");
        prepare_to_write(buffer, modifiers[i].ops);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(SCREEN_WIDTH/2 + 580, 170 + i * 100 - marging_top, buffer_bis, 3);
    }
    if (level < 15)
    {
        gfx_color(94, 96, 98);
        gfx_drawPixelString(SCREEN_WIDTH / 2 + 260, 250 + level * 100  - marging_top, "locked ?", 5);
    }
}

/// @brief Initialise la librairie graphique
void initGFX()
{
    srand(time(NULL));
    gfx_open(SCREEN_WIDTH, SCREEN_HEIGHT, "Ore Clicker");
    gfx_clear_color(255, 255, 255);
    gfx_clear();
}

/// @brief Initialise les modificateurs
/// @param modifiers pointeur vers le tableau des modificateurs
void initModifiers(struct modifier* modifiers)
{
    // Apprentice
    modifiers[0].level = 0;
    modifiers[0].cost = 100;
    modifiers[0].ops = 1;
    strcpy(modifiers[0].name, "gestion de la nature");
    // Freelancer
    modifiers[1].level = 0;
    modifiers[1].cost = 1100;
    modifiers[1].ops = 8;
    strcpy(modifiers[1].name, "agronomie");
    // Dev frontend
    modifiers[2].level = 0;
    modifiers[2].cost = 12000;
    modifiers[2].ops = 47;
    strcpy(modifiers[2].name, "genie civil");
    // Dev backend
    modifiers[3].level = 0;
    modifiers[3].cost = 130000;
    modifiers[3].ops = 260;
    strcpy(modifiers[3].name, "architecture paysage");
    // Dev fullstack
    modifiers[4].level = 0;
    modifiers[4].cost = 1400000;
    modifiers[4].ops = 1400;
    strcpy(modifiers[4].name, "technique du batiment");
    // Mobile Developer
    modifiers[5].level = 0;
    modifiers[5].cost = 20000000;
    modifiers[5].ops = 7800;
    strcpy(modifiers[5].name, "mobile dev");
    // Application Developer
    modifiers[6].level = 0;
    modifiers[6].cost = 330000000;
    modifiers[6].ops = 44000;
    strcpy(modifiers[6].name, "genie mecanique");
    // DevOps Developer
    modifiers[7].level = 0;
    modifiers[7].cost = 5100000000;
    modifiers[7].ops = 260000;
    strcpy(modifiers[7].name, "architecture");
    // Software Developer
    modifiers[8].level = 0;
    modifiers[8].cost = 75000000000;
    modifiers[8].ops = 1600000;
    strcpy(modifiers[8].name, "microtechnique");
    // Video Game Developer
    modifiers[9].level = 0;
    modifiers[9].cost = 1000000000000;
    modifiers[9].ops = 10000000;
    strcpy(modifiers[9].name, "informatique");
    // Graphic Developer
    modifiers[10].level = 0;
    modifiers[10].cost = 14000000000000;
    modifiers[10].ops = 65000000;
    strcpy(modifiers[10].name, "life science");
    // Security Developer
    modifiers[11].level = 0;
    modifiers[11].cost = 170000000000000;
    modifiers[11].ops = 430000000;
    strcpy(modifiers[11].name, "developpement territorial");
    // Data Scientist
    modifiers[12].level = 0;
    modifiers[12].cost = 2100000000000000;
    modifiers[12].ops = 2900000000;
    strcpy(modifiers[12].name, "engineering");
    // Blockchain Developer
    modifiers[13].level = 0;
    modifiers[13].cost = 26000000000000000;
    modifiers[13].ops = 21000000000;
    strcpy(modifiers[13].name, "albuchef");
    // Language Developer
    modifiers[14].level = 0;
    modifiers[14].cost = 310000000000000000;
    modifiers[14].ops = 150000000000;
    strcpy(modifiers[14].name, "malaspinas");
    // AI Developer
    modifiers[15].level = 0;
    modifiers[15].cost = 7100000000000000000;
    modifiers[15].ops = 1100000000000;
    strcpy(modifiers[15].name, "malabuchef");
    // AI
    modifiers[16].level = 0;
    modifiers[16].cost = 120000000000000000000;
    modifiers[16].ops = 8300000000000;
    strcpy(modifiers[16].name, "github copilot");
}

/// @brief Lit le fichier de sauvegarde
/// @param level le niveau du joueur
/// @param count le nombre de cookies
/// @param multiplier_modifier le modificateur de clic
/// @param modifiers les modificateurs
void readSaveFile(int* level, long double* count, struct modifier* multiplier_modifier, struct modifier* modifiers)
{
    FILE *file = fopen("save.txt", "rw");
    if (file != NULL)
    {
        int result = fscanf(file, "%d %Le %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &level, &count, &multiplier_modifier->level, &modifiers[0].level, &modifiers[1].level, &modifiers[2].level, &modifiers[3].level, &modifiers[4].level, &modifiers[5].level, &modifiers[6].level, &modifiers[7].level, &modifiers[8].level, &modifiers[9].level, &modifiers[10].level, &modifiers[11].level, &modifiers[12].level, &modifiers[13].level, &modifiers[14].level, &modifiers[15].level, &modifiers[16].level);
        if (result == 0)
        {
            printf("Error while reading the save file\n");
        }
        fclose(file);
    }
    ///
    multiplier_modifier->level *= pow(PRICE_MULTIPLIER, multiplier_modifier->level);
    for (int i = 0; i < NUMBER_OF_MODIFIERS; i++)
    {
        modifiers[i].cost *= pow(PRICE_MULTIPLIER, modifiers[i].level);
    }
}

/// @brief Écrit l'état actuel du jeu dans un fichier
/// @param level le niveau du joueur
/// @param count le nombre de cookies
/// @param multiplier_modifier le modificateur de clic
/// @param modifiers les modificateurs
void writeSaveFile(int level, long double count, struct modifier* multiplier_modifier, struct modifier* modifiers)
{
    FILE* file = fopen("save.txt", "w");
    if (file != NULL)
    {
        int result = fprintf(file, "%d %Le %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &level, &count, &multiplier_modifier->level, &modifiers[0].level, &modifiers[1].level, &modifiers[2].level, &modifiers[3].level, &modifiers[4].level, &modifiers[5].level, &modifiers[6].level, &modifiers[7].level, &modifiers[8].level, &modifiers[9].level, &modifiers[10].level, &modifiers[11].level, &modifiers[12].level, &modifiers[13].level, &modifiers[14].level, &modifiers[15].level, &modifiers[16].level);
        if (result == 0)
        {
            printf("Error while writing the save file\n");
        }
    }
    fclose(file);
}

int calculatePlayerLevel(int level, long double count)
{
    if (count >= 550 && level == 0)
    {
        return 1;
    }
    if (count >= 6000 && level == 1)
    {
        return 2;
    }
    if (count >= 65000 && level == 2)
    {
        return 3;
    }
    if (count >= 700000 && level == 3)
    {
        return 4;
    }
    if (count >= 10000000 && level == 4)
    {
        return 5;
    }
    if (count >= 165000000 && level == 5)
    {
        return 6;
    }
    if (count >= 2550000000 && level == 6)
    {
        return 7;
    }
    if (count >= 37500000000 && level == 7)
    {
        return 8;
    }
    if (count >= 500000000000 && level == 8)
    {
        return 9;
    }
    if (count >= 7000000000000 && level == 9)
    {
        return 10;
    }
    if (count >= 85000000000000 && level == 10)
    {
        return 11;
    }
    if (count >= 1050000000000000 && level == 11)
    {
        return 12;
    }
    if (count >= 13000000000000000 && level == 12)
    {
        return 13;
    }
    if (count >= 155000000000000000 && level == 13)
    {
        return 14;
    }
    if (count >= 35500000000000000000 && level == 14)
    {
        return 15;
    }
    return 0;
}


int main()
{
    long double count = 0;
    int level = 0;
    int multiplier = 1;
    int tick = 0;
    int animation_tick = 0;
    int cookie_size = COOKIE_SIZE;
    ///
    long double cookies_per_second = 0;
    /// Modificateurs
    struct modifier multiplier_modifier;
    struct modifier* modifiers = malloc(NUMBER_OF_MODIFIERS * sizeof(struct modifier));
    ///

    //* Initialisation
    initGFX();
    initModifiers(modifiers);
    multiplier_modifier.level = 1;
    multiplier_modifier.cost = 15;
    // Lecture de la sauvegarde
    readSaveFile(&level, &count, &multiplier_modifier, modifiers);

    //* Game loop
    while (1)
    {
        tick += 1;
        char input = gfx_getKey();
        //* Inputs
        if (input != 0)
        {
            if (input == '\e' || input == 'Q')
                break;
            // Scroll
            if (input == 4)
            {
                if (marging_top > 0)
                {
                    marging_top -= 25;
                }
            }
            if (input == 5)
            {
                marging_top += 25;
            }
            if (input == 1)
            { // Bouton gauche de la souris
                int x = gfx_xNow();
                int y = gfx_yNow();
                if (gfx_get_pixel_at(x, y) == MAKE_COLOR(242, 204, 157) || gfx_get_pixel_at(x, y) == MAKE_COLOR(113, 56, 18))
                {
                    multiplier = 1 + multiplier_modifier.level / 25;
                    count += 1 * multiplier_modifier.level * multiplier;
                    animation_tick = tick;
                    cookie_size = cookie_size - 10;
                }
                if (x >= SCREEN_WIDTH / 2 - 20 && x <= SCREEN_WIDTH - 140)
                {
                    // Multiplicateur de clic
                    if (y >= 20 - marging_top && y <= 100 - marging_top)
                    {
                        if (count >= multiplier_modifier.cost)
                        {
                            multiplier_modifier.level += 1;
                            count -= multiplier_modifier.cost;
                            multiplier_modifier.cost *= PRICE_MULTIPLIER;
                        }
                    }
                    /// Modificateurs
                    for (int i = 0; i < NUMBER_OF_MODIFIERS; i++)
                    {
                        if (y >= 120 + i * 100 - marging_top && y <= 200 + i * 100 - marging_top)
                        {
                            if (count >= modifiers[i].cost)
                            {
                                modifiers[i].level += 1;
                                count -= modifiers[i].cost;
                                modifiers[i].cost *= PRICE_MULTIPLIER;
                            }
                        }
                    }
                }
            }
        }

        //* Processus
        // Calcule le nombre de cookies par seconde
        cookies_per_second = 0;
        for (int i = 0; i < NUMBER_OF_MODIFIERS; i++)
        {
            cookies_per_second += modifiers[i].ops * modifiers[i].level;
        }
        // Augmente le nombre de cookies toutes les 10 centièmes de secondes
        if (tick % 100 == 0)
        {
            count += cookies_per_second/10;
        }

        // Calcule le niveau du joueur
        level = calculatePlayerLevel(level,count);

        // Reset la taille du cookie
        if ((tick - animation_tick) >= 25)
        {
            cookie_size = COOKIE_SIZE;
        }

        //* Display
        gfx_clear();
        char buffer[100];
        char buffer_bis[100];
        //* Interface
        // Dessine le cookie
        gfx_full_circle(SCREEN_WIDTH / 4 - 20, SCREEN_HEIGHT / 2, cookie_size, MAKE_COLOR(242, 204, 157));
        // et les pépites de chocolat
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 - cookie_size / 2, SCREEN_HEIGHT / 2 - cookie_size / 2.5, cookie_size / 5, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20, SCREEN_HEIGHT / 2 - 20, cookie_size / 10, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 + cookie_size / 5, SCREEN_HEIGHT / 2 + cookie_size / 2, cookie_size / 5, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 - cookie_size / 2.5, SCREEN_HEIGHT / 2 + cookie_size / 3.33, cookie_size / 6.66, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 + cookie_size / 2, SCREEN_HEIGHT / 2 - cookie_size / 2.5, cookie_size / 6.66, MAKE_COLOR(113, 56, 18));

        // Les modificateurs
        gfx_color(0, 0, 0);
        displayModifiers(level, count, &multiplier_modifier, modifiers, buffer, buffer_bis);

        //* Informations
        gfx_color(0, 0, 0);
        // Le nombre de cookies
        strcpy(buffer_bis, "count");
        prepare_to_write(buffer, count);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(20, 20, buffer_bis, 7);
        // Le nombre de cookies par seconde
        strcpy(buffer_bis, "cpc");
        prepare_to_write(buffer, cookies_per_second);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(20, 60, buffer_bis, 7);

        gfx_flush();
        usleep(1000);
    }
    gfx_flush();
    // Sauvegarde
    writeSaveFile(level, count, &multiplier_modifier, modifiers);
    return EXIT_SUCCESS;
}
