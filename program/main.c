#include "gfx/gfx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1620
#define SCREEN_HEIGHT 1080
#define NUMBER_OF_MODIFIERS 18

/*
 * Author: 	    Hugo M.
 * Date:        2024-02-21
 * Description:
 * Clicker game with gfx library
 */

#define COOKIE_SIZE 200
#define PRICE_MULTIPLIER 1.15

struct modifier
{
    char name[50];
    int level;
    long double cost;
    long double ops;
};

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
        value_double = value / 100000.0;
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

int main()
{
    srand(time(NULL));
    gfx_open(SCREEN_WIDTH, SCREEN_HEIGHT, "Ore Clicker");
    gfx_clear_color(255, 255, 255);
    gfx_clear();

    ///
    long double count = 0;
    int level = 0;
    int multiplier = 1;
    int tick = 0;
    int animation_tick = 0;
    int cookie_size = COOKIE_SIZE;
    int marging_top = 0;
    ///
    long double cookies_per_second = 0;
    ///
    int click_multiplier = 1;
    long double click_multiplier_cost = 15;
    /// Modifiers
    struct modifier* modifiers = malloc(NUMBER_OF_MODIFIERS * sizeof(struct modifier));
    // Apprentice
    modifiers[0].level = 0;
    modifiers[0].cost = 100;
    modifiers[0].ops = 1;
    strcpy(modifiers[0].name, "apprentice");
    // Freelancer
    modifiers[1].level = 0;
    modifiers[1].cost = 1100;
    modifiers[1].ops = 8;
    strcpy(modifiers[1].name, "freelancer");
    // Dev frontend
    modifiers[2].level = 0;
    modifiers[2].cost = 12000;
    modifiers[2].ops = 47;
    strcpy(modifiers[2].name, "dev frontend");
    // Dev backend
    modifiers[3].level = 0;
    modifiers[3].cost = 130000;
    modifiers[3].ops = 260;
    strcpy(modifiers[3].name, "dev backend");
    // Dev fullstack
    modifiers[4].level = 0;
    modifiers[4].cost = 1400000;
    modifiers[4].ops = 1400;
    strcpy(modifiers[4].name, "dev fullstack");
    // Mobile Developer
    modifiers[5].level = 0;
    modifiers[5].cost = 20000000;
    modifiers[5].ops = 7800;
    strcpy(modifiers[5].name, "mobile dev");
    // Application Developer
    modifiers[6].level = 0;
    modifiers[6].cost = 330000000;
    modifiers[6].ops = 44000;
    strcpy(modifiers[6].name, "application dev");
    // DevOps Developer
    modifiers[7].level = 0;
    modifiers[7].cost = 5100000000;
    modifiers[7].ops = 260000;
    strcpy(modifiers[7].name, "devops dev");
    // Software Developer
    modifiers[8].level = 0;
    modifiers[8].cost = 75000000000;
    modifiers[8].ops = 1600000;
    strcpy(modifiers[8].name, "software dev");
    // Video Game Developer
    modifiers[9].level = 0;
    modifiers[9].cost = 1000000000000;
    modifiers[9].ops = 10000000;
    strcpy(modifiers[9].name, "video game dev");
    // Graphic Developer
    modifiers[10].level = 0;
    modifiers[10].cost = 14000000000000;
    modifiers[10].ops = 65000000;
    strcpy(modifiers[10].name, "graphic dev");
    // Security Developer
    modifiers[11].level = 0;
    modifiers[11].cost = 170000000000000;
    modifiers[11].ops = 430000000;
    strcpy(modifiers[11].name, "security dev");
    // Data Scientist
    modifiers[12].level = 0;
    modifiers[12].cost = 2100000000000000;
    modifiers[12].ops = 2900000000;
    strcpy(modifiers[12].name, "data scientist");
    // Blockchain Developer
    modifiers[13].level = 0;
    modifiers[13].cost = 26000000000000000;
    modifiers[13].ops = 21000000000;
    strcpy(modifiers[13].name, "blockchain dev");
    // Language Developer
    modifiers[14].level = 0;
    modifiers[14].cost = 310000000000000000;
    modifiers[14].ops = 150000000000;
    strcpy(modifiers[14].name, "language dev");
    // AI Developer
    modifiers[15].level = 0;
    modifiers[15].cost = 7100000000000000000;
    modifiers[15].ops = 1100000000000;
    strcpy(modifiers[15].name, "ai dev");
    // AI
    modifiers[16].level = 0;
    modifiers[16].cost = 120000000000000000000;
    modifiers[16].ops = 8300000000000;
    strcpy(modifiers[16].name, "ai");

    //* Initialize
    // Read the save file
    FILE *file = fopen("save.txt", "rw");
    if (file != NULL)
    {
        int result = fscanf(file, "%d %Le %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &level, &count, &click_multiplier, &modifiers[0].level, &modifiers[1].level, &modifiers[2].level, &modifiers[3].level, &modifiers[4].level, &modifiers[5].level, &modifiers[6].level, &modifiers[7].level, &modifiers[8].level, &modifiers[9].level, &modifiers[10].level, &modifiers[11].level, &modifiers[12].level, &modifiers[13].level, &modifiers[14].level, &modifiers[15].level, &modifiers[16].level);
        if (result == 0)
        {
            printf("Error while reading the save file\n");
        }
        fclose(file);
    }
    ///
    for (int i = 0; i < NUMBER_OF_MODIFIERS; i++)
    {
        modifiers[i].cost *= pow(PRICE_MULTIPLIER, modifiers[i].level);
    }
    ///

    //* Main loop
    while (1)
    {
        tick += 1;
        char input = gfx_getKey();
        //* Inputs
        if (input != 0)
        {
            if (input == '\e' || input == 'Q')
                break;
            // Mouse scroll
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
            { // Left-Mouse-Button
                int x = gfx_xNow();
                int y = gfx_yNow();
                if (gfx_get_pixel_at(x, y) == MAKE_COLOR(242, 204, 157) || gfx_get_pixel_at(x, y) == MAKE_COLOR(113, 56, 18))
                {
                    multiplier = 1 + click_multiplier / 25;
                    count += 1 * click_multiplier * multiplier;
                    animation_tick = tick;
                    cookie_size = cookie_size - 10;
                }
                if (x >= SCREEN_WIDTH / 2 - 20 && x <= SCREEN_WIDTH - 140)
                {
                    // Click multiplier
                    if (y >= 20 - marging_top && y <= 100 - marging_top)
                    {
                        if (count >= click_multiplier_cost)
                        {
                            click_multiplier += 1;
                            count -= click_multiplier_cost;
                            click_multiplier_cost *= PRICE_MULTIPLIER;
                        }
                    }
                    /// Modifiers
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

        //* Process
        cookies_per_second = 0;
        for (int i = 0; i < NUMBER_OF_MODIFIERS; i++)
        {
            cookies_per_second += modifiers[i].ops * modifiers[i].level;
        }
        // Player levels
        if (count >= 550 && level == 0)
        {
            level = 1;
        }
        if (count >= 6000 && level == 1)
        {
            level = 2;
        }
        if (count >= 65000 && level == 2)
        {
            level = 3;
        }
        if (count >= 700000 && level == 3)
        {
            level = 4;
        }
        if (count >= 10000000 && level == 4)
        {
            level = 5;
        }
        if (count >= 165000000 && level == 5)
        {
            level = 6;
        }
        if (count >= 2550000000 && level == 6)
        {
            level = 7;
        }
        if (count >= 37500000000 && level == 7)
        {
            level = 8;
        }
        if (count >= 500000000000 && level == 8)
        {
            level = 9;
        }
        if (count >= 7000000000000 && level == 9)
        {
            level = 10;
        }
        if (count >= 85000000000000 && level == 10)
        {
            level = 11;
        }
        if (count >= 1050000000000000 && level == 11)
        {
            level = 12;
        }
        if (count >= 13000000000000000 && level == 12)
        {
            level = 13;
        }
        if (count >= 155000000000000000 && level == 13)
        {
            level = 14;
        }
        if (count >= 35500000000000000000 && level == 14)
        {
            level = 15;
        }
    
        // Ores per second/10
        if (tick % 100 == 0)
        {
            count += cookies_per_second/10;
        }

        // Planet size
        if ((tick - animation_tick) >= 25)
        {
            cookie_size = COOKIE_SIZE;
        }

        //* Display
        gfx_clear();
        char buffer[100];
        char buffer_bis[100];
        //* Interface
        // The ore
        // The cookie
        gfx_full_circle(SCREEN_WIDTH / 4 - 20, SCREEN_HEIGHT / 2, cookie_size, MAKE_COLOR(242, 204, 157));
        // Draw the chocolate chips
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 - cookie_size / 2, SCREEN_HEIGHT / 2 - cookie_size / 2.5, cookie_size / 5, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20, SCREEN_HEIGHT / 2 - 20, cookie_size / 10, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 + cookie_size / 5, SCREEN_HEIGHT / 2 + cookie_size / 2, cookie_size / 5, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 - cookie_size / 2.5, SCREEN_HEIGHT / 2 + cookie_size / 3.33, cookie_size / 6.66, MAKE_COLOR(113, 56, 18));
        gfx_full_circle(SCREEN_WIDTH / 4 - 20 + cookie_size / 2, SCREEN_HEIGHT / 2 - cookie_size / 2.5, cookie_size / 6.66, MAKE_COLOR(113, 56, 18));
        // The modifiers
        gfx_color(215, 218, 222);
        gfx_fillrect(SCREEN_WIDTH / 2 - 20, 20  - marging_top, SCREEN_WIDTH - 140, 100 - marging_top);
        gfx_fillrect(SCREEN_WIDTH / 2 - 20, 120  - marging_top, SCREEN_WIDTH - 140, 200 - marging_top);
        for (int i = 1; i <= level; i++)
        {
            gfx_fillrect(SCREEN_WIDTH / 2 - 20, 120 + i * 100  - marging_top, SCREEN_WIDTH - 140, 200 + i * 100 - marging_top);
        }
        gfx_color(237, 241, 245);
        gfx_fillrect(SCREEN_WIDTH / 2 - 20, 220 + level * 100  - marging_top, SCREEN_WIDTH - 140, 300 + level * 100 - marging_top);

        gfx_color(0, 0, 0);
        // Click multiplicator
        if (count >= click_multiplier_cost)
        {
            gfx_color(0, 0, 0);
        }
        else
        {
            gfx_color(94, 96, 98);
        }

        strcpy(buffer_bis, "click multiplier");
        prepare_to_write(buffer, click_multiplier);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(SCREEN_WIDTH / 2, 50 - marging_top, buffer_bis, 5);

        strcpy(buffer_bis, "cost");
        prepare_to_write(buffer, click_multiplier_cost);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(SCREEN_WIDTH - 310, 35 - marging_top, buffer_bis, 3);

        strcpy(buffer_bis, "cpc");
        prepare_to_write(buffer, click_multiplier);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(SCREEN_WIDTH - 293, 70 - marging_top, buffer_bis, 3);

        /// Modifiers
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
            gfx_drawPixelString(SCREEN_WIDTH - 310, 135 + i * 100 - marging_top, buffer_bis, 3);

            strcpy(buffer_bis, "cps");
            prepare_to_write(buffer, modifiers[i].ops);
            strcat(buffer_bis, buffer);
            gfx_drawPixelString(SCREEN_WIDTH - 293, 170 + i * 100 - marging_top, buffer_bis, 3);
        }
        if (level < 15)
        {
            gfx_color(94, 96, 98);
            gfx_drawPixelString(SCREEN_WIDTH / 2 + 260, 250 + level * 100  - marging_top, "locked ?", 5);
        }

        //* Informations
        gfx_color(0, 0, 0);
        // The count
        strcpy(buffer_bis, "count");
        prepare_to_write(buffer, count);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(20, 20, buffer_bis, 7);
        // The ores per second
        strcpy(buffer_bis, "cpc");
        prepare_to_write(buffer, cookies_per_second);
        strcat(buffer_bis, buffer);
        gfx_drawPixelString(20, 60, buffer_bis, 7);

        gfx_flush();
        usleep(1000);
    }
    gfx_flush();
    // Save the count and the click multiplier
    file = fopen("save.txt", "w");
    if (file != NULL)
    {
        int result = fprintf(file, "%d %Le %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", level, count, click_multiplier, modifiers[0].level, modifiers[1].level, modifiers[2].level, modifiers[3].level, modifiers[4].level, modifiers[5].level, modifiers[6].level, modifiers[7].level, modifiers[8].level, modifiers[9].level, modifiers[10].level, modifiers[11].level, modifiers[12].level, modifiers[13].level, modifiers[14].level, modifiers[15].level, modifiers[16].level);
        if (result == 0)
        {
            printf("Error while writing the save file\n");
        }
    }
    fclose(file);
    return EXIT_SUCCESS;
}
