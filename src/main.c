#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "figure.h"
#include <string.h>

#define MAX_CONFETTI 70

int masterVolume = 100;
int specialVolume = 100;
int backgroundVolume = 100;

typedef struct {
    Vector2 position;
    Vector2 speed;
    Color color;
    short int shape;
} Confetti;

int configSound(){

    Vector2 mousePos;

    char volumeParse[10];

    float percentage = 0.0f;

    short int status = -1;

    //default config
    const int defaultMasterVolume = 100;
    const int defaultSpecialVolume = 100;
    const int defaultBackgroundVolume = 100;
    //default config
    
    int tempMasterVolume = masterVolume;
    int tempSpecialVolume = specialVolume;
    int tempBackgroundVolume = backgroundVolume;
    
    const int panelWidth = 500;
    const int panelHeight = 325;

    const int panelX = (GetScreenWidth()/2)-(panelWidth/2); 
    const int panelY = (GetScreenHeight()/2)-(panelHeight/2);

    Image imgReduceVolume = LoadImage("../assets/ReduceVolume.png");
    Image imgIncreaseVolume = LoadImage("../assets/IncreaseVolume.png");
    Image imgMasterSound = LoadImage("../assets/MasterVolume.png");
    Image imgBackgroundSound = LoadImage("../assets/BackgroundSound.png");
    Image imgSpecialSound = LoadImage("../assets/SpecialSound.png");
    Image imgConfirm = LoadImage("../assets/Confirm.png");
    Image imgDefault = LoadImage("../assets/Default.png");
    Image imgMenu = LoadImage("../assets/BtnMenu.png");

    const int textureConfirmX = (panelX+panelWidth/2) - imgConfirm.width;
    const int textureConfirmY = (panelY+panelHeight) - imgConfirm.height;
    
    const int textureDefaultX = textureConfirmX+imgConfirm.width+10;

    const int textureMenuX = ((panelX+panelWidth) - imgMenu.width)-10;

    Sound backgroundSound = LoadSound("../assets/menuBackground.mp3");
    Sound hoverSound = LoadSound("../assets/hover.wav");
    Sound menuSound = LoadSound("../assets/menu.mp3");
    Sound selectSound = LoadSound("../assets/select.wav");
    
    Sound *specialSound[] = {&hoverSound, &menuSound, &selectSound}; 

    const int countSpecialSound = sizeof(specialSound) / sizeof(specialSound[0]);

    //init the current config
    percentage = masterVolume * 0.01f;

    SetMasterVolume(percentage);

    percentage = backgroundVolume * 0.01f;

    SetSoundVolume(menuSound, percentage);

    percentage = specialVolume * 0.01f;

    for (int i = 0; i < countSpecialSound; i++)
    {
        SetSoundVolume((*specialSound[i]), percentage);
    }
    //init the current config

    const int textureConfigX = (panelX + (panelWidth/3))-(imgMasterSound.width/2);
    int textureY = 0;

    const int textureReduceVolumeX = textureConfigX+imgMasterSound.width;
    
    const int textVolumeX = textureReduceVolumeX + imgMasterSound.width + 10;
    
    const int textureIncreaseVolumeX = textureConfigX+imgReduceVolume.width+imgIncreaseVolume.width+70;
    const int marginY = 70;

    Texture textureMasterSound = LoadTextureFromImage(imgMasterSound);
    Texture textureBackgroundSound = LoadTextureFromImage(imgBackgroundSound);
    Texture textureReduceVolume = LoadTextureFromImage(imgReduceVolume);
    Texture textureIncreaseVolume = LoadTextureFromImage(imgIncreaseVolume);
    Texture textureSpecialSound = LoadTextureFromImage(imgSpecialSound);
    Texture textureConfirm = LoadTextureFromImage(imgConfirm);
    Texture textureDefault = LoadTextureFromImage(imgDefault);
    Texture textureMenu = LoadTextureFromImage(imgMenu);
    
    UnloadImage(imgMasterSound);
    UnloadImage(imgReduceVolume);
    UnloadImage(imgIncreaseVolume);
    UnloadImage(imgBackgroundSound);
    UnloadImage(imgDefault);
    UnloadImage(imgMenu);

    while(!WindowShouldClose() && status == -1){

        BeginDrawing();
        ClearBackground(RAYWHITE);

        mousePos = GetMousePosition();

        textureY = panelY + imgMasterSound.height;

        DrawRectangle(panelX, panelY, panelWidth, panelHeight, (Color){223, 227, 232, 255});

        DrawTexture(textureConfirm, textureConfirmX, textureConfirmY, WHITE);

        DrawTexture(textureDefault, textureDefaultX, textureConfirmY, WHITE);

        DrawTexture(textureMenu, textureMenuX, textureConfirmY, WHITE);

        sprintf(volumeParse, "%d", tempMasterVolume);
        strcat(volumeParse, "%");
        
        DrawText(volumeParse, textVolumeX, textureY, 25, BLACK);

        DrawTexture(textureMasterSound, textureConfigX, textureY, WHITE);
        
        DrawTexture(textureReduceVolume, textureReduceVolumeX, textureY, WHITE);

        DrawTexture(textureIncreaseVolume, textureIncreaseVolumeX, textureY, WHITE);

        if( tempMasterVolume + 10 <= 100  && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){textureIncreaseVolumeX, textureY, textureIncreaseVolume.width, textureIncreaseVolume.height} )){

            tempMasterVolume += 10;
            
            percentage = tempMasterVolume * 0.01f;

            SetMasterVolume(percentage);

            PlaySound(backgroundSound);
            PlaySound(hoverSound);
        }

        if( tempMasterVolume - 10 >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){textureReduceVolumeX, textureY, textureReduceVolume.width, textureReduceVolume.height} )){
            
            tempMasterVolume -= 10;
            
            percentage = tempMasterVolume * 0.01f;

            SetMasterVolume(percentage);

            PlaySound(backgroundSound);
            PlaySound(hoverSound);

        }

        //next row
        textureY += marginY;

        DrawTexture(textureBackgroundSound, textureConfigX, textureY, WHITE);

        DrawTexture(textureReduceVolume, textureReduceVolumeX, textureY, WHITE);

        DrawTexture(textureIncreaseVolume, textureIncreaseVolumeX, textureY, WHITE);
        
        sprintf(volumeParse, "%d", tempBackgroundVolume);
        strcat(volumeParse, "%");

        DrawText(volumeParse, textVolumeX, textureY, 25, BLACK);

        if( tempBackgroundVolume + 10 <= 100  && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){textureIncreaseVolumeX, textureY, textureIncreaseVolume.width, textureIncreaseVolume.height} )){

            tempBackgroundVolume += 10;

            percentage = tempBackgroundVolume * 0.01f;

            SetSoundVolume(backgroundSound, percentage);

            PlaySound(backgroundSound);

        }  

        if( tempBackgroundVolume - 10 >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){textureReduceVolumeX, textureY, textureReduceVolume.width, textureReduceVolume.height} )){
            
            tempBackgroundVolume -= 10;
            
            percentage = tempBackgroundVolume * 0.01f;

            SetSoundVolume(backgroundSound, percentage);

            PlaySound(backgroundSound);

        }

        textureY += marginY;

        DrawTexture(textureSpecialSound, textureConfigX, textureY, WHITE);

        DrawTexture(textureReduceVolume, textureReduceVolumeX, textureY, WHITE);

        DrawTexture(textureIncreaseVolume, textureIncreaseVolumeX, textureY, WHITE);

        sprintf(volumeParse, "%d", tempSpecialVolume);
        strcat(volumeParse, "%");

        DrawText(volumeParse, textVolumeX, textureY, 25, BLACK);

        if( tempSpecialVolume + 10 <= 100  && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){textureIncreaseVolumeX, textureY, textureIncreaseVolume.width, textureIncreaseVolume.height} )){

            tempSpecialVolume += 10;

            percentage = tempSpecialVolume * 0.01f;
            
            for (int i = 0; i < countSpecialSound; i++)
            {
                SetSoundVolume((*specialSound[i]), percentage);
                
            }
            
            PlaySound(hoverSound);

        }

        if( tempSpecialVolume - 10 >= 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){textureReduceVolumeX, textureY, textureReduceVolume.width, textureReduceVolume.height} )){
            
            tempSpecialVolume -= 10;
            
            percentage = tempSpecialVolume * 0.01f;

            for (int i = 0; i < countSpecialSound; i++)
            {
                SetSoundVolume((*specialSound[i]), percentage);
                
            }
            
            SetSoundVolume(hoverSound, percentage);

            PlaySound(hoverSound);

        }

        EndDrawing();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            if(CheckCollisionPointRec(mousePos, (Rectangle){textureMenuX, textureConfirmY, textureMenu.width, textureMenu.height})){

                PlaySound(menuSound);

                status = 0;
                
                WaitTime(0.3);

            }

            if(CheckCollisionPointRec(mousePos, (Rectangle){textureDefaultX, textureConfirmY, textureDefault.width, textureDefault.height})){

                PlaySound(selectSound);

                tempMasterVolume = defaultMasterVolume;

                percentage = tempMasterVolume * 0.01f;

                SetMasterVolume(percentage);

                tempBackgroundVolume = defaultBackgroundVolume;

                percentage = tempBackgroundVolume * 0.01f;

                SetSoundVolume(backgroundSound, percentage);

                tempSpecialVolume = defaultSpecialVolume;

                percentage = tempSpecialVolume * 0.01f;

                SetSoundVolume(hoverSound, percentage);

            }

            if(CheckCollisionPointRec(mousePos, (Rectangle){textureConfirmX, textureConfirmY, textureConfirm.width, textureConfirm.height})){

                PlaySound(selectSound);
                
                masterVolume = tempMasterVolume;

                backgroundVolume = tempBackgroundVolume;

                specialVolume = tempSpecialVolume;

            }   

        }

    }
    
    UnloadTexture(textureMasterSound);
    UnloadTexture(textureReduceVolume);
    UnloadTexture(textureIncreaseVolume);
    UnloadTexture(textureBackgroundSound);
    UnloadTexture(textureSpecialSound);
    UnloadTexture(textureConfirm);
    UnloadTexture(textureDefault);
    UnloadTexture(textureMenu);

    UnloadSound(backgroundSound);
    UnloadSound(hoverSound);
    UnloadSound(menuSound);
    UnloadSound(selectSound);

    return status;
}

int calcPosYPuzzle(Texture2D *textureMinPuzzle, int quantityFigure, int quantityPuzzleLineX, int textureFigureHeight){

    int posYPuzzle = 0;
    int maxHeight = 0;

    for (int i = 0; i < quantityFigure/quantityPuzzleLineX; i++)
    {
        
        maxHeight = textureMinPuzzle[(i*quantityPuzzleLineX)].height;

        for(int j = (i*quantityPuzzleLineX)+1; j < (i*quantityPuzzleLineX)+quantityPuzzleLineX; j++){

            if(textureMinPuzzle[j].height > maxHeight){

                maxHeight = textureMinPuzzle[j].height;
                
            }

        }

        posYPuzzle += maxHeight + textureFigureHeight+3;

    }
    
    if((quantityFigure % quantityPuzzleLineX) != 0){
        
        maxHeight = textureMinPuzzle[((quantityFigure/quantityPuzzleLineX)*quantityPuzzleLineX)].height;

        for (int i = ((quantityFigure/quantityPuzzleLineX)*quantityPuzzleLineX)+1; i < quantityFigure; i++)
        {
            
            if(textureMinPuzzle[i].height > maxHeight){

                maxHeight = textureMinPuzzle[i].height;

            }
            
        }
        
        posYPuzzle += maxHeight+textureFigureHeight+3;

    }

    return posYPuzzle;
}

void calcPosXPuzzleRow(Texture2D *textureMinPuzzle, int *posXPuzzleRow, int quantityFigure, int quantityPuzzleLineX){
    
    int posXPuzzle = 0;

    int quantityFigureLast = 0;

    for (int i = 0; i < quantityFigure/quantityPuzzleLineX; i++)
    {

        for(int j = (i*quantityPuzzleLineX); j < (i*quantityPuzzleLineX)+quantityPuzzleLineX; j++){

            posXPuzzle += textureMinPuzzle[j].width;

        }

        posXPuzzleRow[i] = posXPuzzle + ((quantityPuzzleLineX-1) * 10);
        
        posXPuzzle = 0;

    }
    
    if((quantityFigure % quantityPuzzleLineX) != 0){
        
        for (int i = ((quantityFigure/quantityPuzzleLineX)*quantityPuzzleLineX); i < quantityFigure; i++)
        {
            posXPuzzle+=textureMinPuzzle[i].width;
            ++quantityFigureLast;
        }

        posXPuzzleRow[(quantityFigure-1)/quantityPuzzleLineX] = posXPuzzle + ((quantityFigureLast-1)*10);

    }

}

void calcSpaceBetweenY(int currentPuzzleLineY, int quantityPuzzleLineX, int *spaceBetweenY, Texture2D *textureMinPuzzle){

    int maxHeight = 0;
    
    for (int i = 0; i < currentPuzzleLineY; i++)
    {
        
        maxHeight = textureMinPuzzle[(i*quantityPuzzleLineX)].height;

        for (int j = (i*quantityPuzzleLineX)+1; j < (i*quantityPuzzleLineX)+quantityPuzzleLineX; j++)
        {
            
            if(textureMinPuzzle[j].height > maxHeight){

                maxHeight = textureMinPuzzle[j].height;

            }

        }

        spaceBetweenY[i] = maxHeight;
        
    }
    
}

int menu(int page){

    Vector2 mousePos;

    Image image;
    
    float percentage = 0.0f;

    short int viewImgPuzzle = 0;
    short int pressSound = 0;
    short int playHover = 0;

    int puzzleView = -1;
    // const int minImageWidth = 299;
    // const int minImageHeight = 120;

    const int quantityPuzzleLineX = 2;
    const int quantityPuzzleLineY = 3;

    int puzzleImgWidth = 0;

    int posXPuzzle = 0;
    int posYPuzzle = 0;

    const int quantityPuzzle = 11;
    const int limitQuantityPuzzle = 6;
    const int limitPage = ((quantityPuzzle-1)/limitQuantityPuzzle)+1;
    
    int currentPuzzleLineX = 0;
    int currentPuzzleLineY = 0;

    char imageOptionParse[10];
    char figureNumber[10];
    char imageOption[35];

    int optionPuzzle = -1;
    
    Image imgPreviousPuzzle = LoadImage("../assets/BtnPreviousFigure.png");
    Image imgNextPuzzle = LoadImage("../assets/BtnNextFigure.png");
    Image imgWrong = LoadImage("../assets/BtnWrong.png");
    Image imgFigure = LoadImage("../assets/Figure.png");
    Image imgSound = LoadImage("../assets/Sound.png");

    Image loadImgPuzzle;

    Sound hover = LoadSound("../assets/hover.wav");
    Sound select = LoadSound("../assets/select.wav");
    Sound pagination = LoadSound("../assets/pagination.wav");
    Sound zoom = LoadSound("../assets/zoom.mp3");
    Sound menuBackground = LoadSound("../assets/menuBackground.mp3");

    Sound *specialSound[] = {&hover, &select, &pagination, &zoom};
    
    const int countSpecialSound = (sizeof(specialSound)/sizeof(specialSound[0]));
    
    //init the current config sound

    percentage = masterVolume * 0.01f;

    SetMasterVolume(percentage);
    
    percentage = backgroundVolume * 0.01f;

    SetSoundVolume(menuBackground, percentage);

    percentage = specialVolume * 0.01f;

    for (int i = 0; i < countSpecialSound; i++)
    {
        
        SetSoundVolume((*specialSound[i]), percentage);

    }
    
    //int the current config sound

    const int previousPuzzleX = ((GetScreenWidth()/2)-imgPreviousPuzzle.width);
    const int previousPuzzleY = (GetScreenHeight()-imgPreviousPuzzle.height)-10;

    const int nextPuzzleX = ((GetScreenWidth()/2)+imgNextPuzzle.width/3);
    const int nextPuzzleY = (GetScreenHeight()-imgNextPuzzle.height)-10;

    const int textureSoundX = nextPuzzleX + imgSound.width + 50;
    const int textureSoundY = nextPuzzleY;

    Texture2D texturePreviousPuzzle = LoadTextureFromImage(imgPreviousPuzzle);
    Texture2D textureNextPuzzle = LoadTextureFromImage(imgNextPuzzle);
    Texture2D textureWrong = LoadTextureFromImage(imgWrong);
    Texture2D textureFigure = LoadTextureFromImage(imgFigure);
    Texture2D textureSound = LoadTextureFromImage(imgSound);

    Texture2D textureMinPuzzle[limitQuantityPuzzle];

    Texture2D textureViewPuzzle;

    Rectangle figureHover;

    Image imgPuzzle[limitQuantityPuzzle];

    int spaceBetweenY[((limitQuantityPuzzle-1)/quantityPuzzleLineX)];

    int posXPuzzleRow[quantityPuzzleLineY];

    UnloadImage(imgPreviousPuzzle);
    UnloadImage(imgNextPuzzle);
    UnloadImage(imgWrong);
    UnloadImage(imgFigure);
    UnloadImage(imgSound);
    
    //init the first images
    for (int i = ((page-1)*limitQuantityPuzzle)+1;  i<=quantityPuzzle && i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle; i++)
    {   
        strcpy(imageOption, "../puzzle/minPuzzleImage");
        sprintf(imageOptionParse, "%d", i);
        strcat(imageOption, imageOptionParse); 
        strcat(imageOption, ".png");

        loadImgPuzzle = LoadImage(imageOption);

        textureMinPuzzle[((i - ((page-1)*limitQuantityPuzzle))-1)] = LoadTextureFromImage(loadImgPuzzle);

        strcpy(imageOption, "../puzzle/puzzleImage");
        strcat(imageOption, imageOptionParse);
        strcat(imageOption, ".png");
        
        imgPuzzle[((i - ((page-1)*limitQuantityPuzzle))-1)] = LoadImage(imageOption);

        UnloadImage(loadImgPuzzle);
    }

    currentPuzzleLineY = ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? (limitQuantityPuzzle / quantityPuzzleLineX)-1 : (((quantityPuzzle -  (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle) )+limitQuantityPuzzle)-1) / quantityPuzzleLineX;
                
    calcSpaceBetweenY(currentPuzzleLineY, quantityPuzzleLineX, spaceBetweenY, textureMinPuzzle);

    //posYPuzzle = ((windowHeight - (windowHeight - nextPuzzleY))/2) - ((calcPosYPuzzle(textureMinPuzzle, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX, textureFigure.height) + (currentPuzzleLineY * 10))/2);
                
    calcPosXPuzzleRow(textureMinPuzzle, posXPuzzleRow, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX);

    //posXPuzzle = (windowWidth/2) - (posXPuzzleRow[0]/2);

    //figures left ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - limitQuantityPuzzle)+limitQuantityPuzzle)

    PlaySound(menuBackground);

    while (!WindowShouldClose() && optionPuzzle == -1){

        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[0]/2);
        
        posYPuzzle = ((GetScreenHeight() - (GetScreenHeight() - nextPuzzleY))/2) - ((calcPosYPuzzle(textureMinPuzzle, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX, textureFigure.height) + (currentPuzzleLineY * 10))/2); 
        
        mousePos = GetMousePosition();

        for (int i = ((page-1)*limitQuantityPuzzle)+1;  i<=quantityPuzzle && i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle; i++)
        {   
            
            //printf("posXPuzzle %d", posXPuzzle);
            
            DrawTexture(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1], posXPuzzle, posYPuzzle, WHITE);
            
            if(CheckCollisionPointRec(mousePos, (Rectangle){posXPuzzle, posYPuzzle, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height})){
                
                DrawRectangle(posXPuzzle, posYPuzzle, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height, (Color){255, 255, 255, 70});

                if(playHover == 0){

                    playHover = 1;                
                    figureHover = (Rectangle){posXPuzzle, posYPuzzle, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height};
                }

            }else{

                DrawRectangleLines(posXPuzzle, posYPuzzle, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height, BLACK);

            }

            DrawTexture(textureFigure, ((posXPuzzle+(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width))-(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width)/2)-30, (posYPuzzle+(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height))+3, WHITE);
            
            sprintf(figureNumber, "%d", (imgPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]).width/FIGURE_SIZE * (imgPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]).height/FIGURE_SIZE);
            
            DrawText(figureNumber, ((posXPuzzle+(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width))-(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width)/2),(posYPuzzle+(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height))+3, 23,BLACK);
            
            posXPuzzle += textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width + 10;

            //next row to draw
            if((i % quantityPuzzleLineX) == 0 && (i - ((page-1)*limitQuantityPuzzle) != limitQuantityPuzzle)){
                
                //printf("posicionX %d", (windowWidth/2) - (posXPuzzleRow[((i - ((page-1)*limitQuantityPuzzle))/quantityPuzzleLineX)] / 2));
                posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[((i - ((page-1)*limitQuantityPuzzle))/quantityPuzzleLineX)] / 2);    
                posYPuzzle+=spaceBetweenY[(((i - ((page-1)*limitQuantityPuzzle))-1)/quantityPuzzleLineX)]+10+textureFigure.height+3;

            }

        }
        
        if(playHover == 1){

            PlaySound(hover);
            
            playHover = 2;
        }

        if(playHover == 2 && !CheckCollisionPointRec(mousePos, figureHover)){

            playHover = 0;

        }

        if(!IsSoundPlaying(menuBackground)){

            PlaySound(menuBackground);

        }

        if(page > 1){
            DrawTexture(texturePreviousPuzzle, previousPuzzleX, previousPuzzleY, WHITE);
        }else{
            DrawTexture(textureWrong, previousPuzzleX, previousPuzzleY, WHITE);
        }

        if(page < limitPage){
            DrawTexture(textureNextPuzzle, nextPuzzleX, nextPuzzleY, WHITE);
        }else{
            DrawTexture(textureWrong, nextPuzzleX, nextPuzzleY, WHITE);
        }

        DrawTexture(textureSound, textureSoundX, textureSoundY, WHITE);
        
        //detect next or previous page
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            
            if(CheckCollisionPointRec(mousePos, (Rectangle){textureSoundX, textureSoundY, textureSound.width, textureSound.height})){

                if(!pressSound) pressSound = 1;

            }

            if(page < limitPage && CheckCollisionPointRec(mousePos,(Rectangle){nextPuzzleX, nextPuzzleY, textureNextPuzzle.width, textureNextPuzzle.height})){
                

                ClearBackground(RAYWHITE);

                PlaySound(pagination);

                //free the previous texture and Images
                for (int i = ((page-1)*limitQuantityPuzzle)+1; i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle && i<=quantityPuzzle; i++){
                    UnloadTexture(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]);
                    UnloadImage(imgPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]);
                }

                ++page;

                for (int i = ((page-1)*limitQuantityPuzzle)+1; i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle && i<=quantityPuzzle; i++)
                {
                    //load the new images
                    strcpy(imageOption, "../puzzle/minPuzzleImage");
                    sprintf(imageOptionParse, "%d", i);
                    strcat(imageOption, imageOptionParse); 
                    strcat(imageOption, ".png");

                    loadImgPuzzle = LoadImage(imageOption);
                    
                    textureMinPuzzle[((i - ((page-1)*limitQuantityPuzzle))-1)] = LoadTextureFromImage(loadImgPuzzle);

                    strcpy(imageOption, "../puzzle/puzzleImage");
                    strcat(imageOption, imageOptionParse);
                    strcat(imageOption, ".png");
                    
                    imgPuzzle[((i - ((page-1)*limitQuantityPuzzle))-1)] = LoadImage(imageOption);

                    UnloadImage(loadImgPuzzle);

                }

                currentPuzzleLineY = ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? (limitQuantityPuzzle / quantityPuzzleLineX)-1 : (((quantityPuzzle -  (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle) )+limitQuantityPuzzle)-1) / quantityPuzzleLineX;

                calcSpaceBetweenY(currentPuzzleLineY, quantityPuzzleLineX, spaceBetweenY, textureMinPuzzle);

                posYPuzzle = ((GetScreenHeight() - (GetScreenHeight() - nextPuzzleY))/2) - ((calcPosYPuzzle(textureMinPuzzle, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX, textureFigure.height) + (currentPuzzleLineY * 10))/2);
                
                calcPosXPuzzleRow(textureMinPuzzle, posXPuzzleRow, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX);

                posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[0]/2);
                
            }  
            
            if(page > 1 && CheckCollisionPointRec(mousePos,(Rectangle){previousPuzzleX, previousPuzzleY, texturePreviousPuzzle.width, texturePreviousPuzzle.height})){
                
                ClearBackground(RAYWHITE);
                
                PlaySound(pagination);

                for (int i = ((page-1)*limitQuantityPuzzle)+1; i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle && i<=quantityPuzzle; i++){
                    UnloadTexture(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]);
                    UnloadImage(imgPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]);
                }

                --page; 

                for (int i = ((page-1)*limitQuantityPuzzle)+1; i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle && i<=quantityPuzzle; i++)
                {
                    //load the new images
                    strcpy(imageOption, "../puzzle/minPuzzleImage");
                    sprintf(imageOptionParse, "%d", i);
                    strcat(imageOption, imageOptionParse); 
                    strcat(imageOption, ".png");

                    loadImgPuzzle = LoadImage(imageOption);
                    
                    textureMinPuzzle[((i - ((page-1)*limitQuantityPuzzle))-1)] = LoadTextureFromImage(loadImgPuzzle);

                    strcpy(imageOption, "../puzzle/puzzleImage");
                    strcat(imageOption, imageOptionParse);
                    strcat(imageOption, ".png");
                    
                    imgPuzzle[((i - ((page-1)*limitQuantityPuzzle))-1)] = LoadImage(imageOption);

                    UnloadImage(loadImgPuzzle);

                }

                currentPuzzleLineY = ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? (limitQuantityPuzzle / quantityPuzzleLineX)-1 : (((quantityPuzzle -  (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle) )+limitQuantityPuzzle)-1) / quantityPuzzleLineX;

                calcSpaceBetweenY(currentPuzzleLineY, quantityPuzzleLineX, spaceBetweenY, textureMinPuzzle);

                posYPuzzle = ((GetScreenHeight() - (GetScreenHeight() - nextPuzzleY))/2) - ((calcPosYPuzzle(textureMinPuzzle, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX, textureFigure.height) + (currentPuzzleLineY * 10))/2);
                
                calcPosXPuzzleRow(textureMinPuzzle, posXPuzzleRow, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX);

                posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[0]/2);

            }  

        }

        EndDrawing();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            
            posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[0]/2);
        
            posYPuzzle = ((GetScreenHeight() - (GetScreenHeight() - nextPuzzleY))/2) - ((calcPosYPuzzle(textureMinPuzzle, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX, textureFigure.height) + (currentPuzzleLineY * 10))/2); 
        
            for (int i = ((page-1)*limitQuantityPuzzle)+1;  i<=quantityPuzzle && i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle; i++){

                //check the collision
                if(CheckCollisionPointRec(mousePos, (Rectangle){posXPuzzle, posYPuzzle,textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height })){
                    
                    PlaySound(select);
                    WaitTime(0.1);

                    optionPuzzle = i;

                    break;

                }

                posXPuzzle += textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width + 10;

                //next to check
                if((i % quantityPuzzleLineX) == 0 && (i - ((page-1)*limitQuantityPuzzle) != limitQuantityPuzzle)){
                    
                    //printf("posicionX %d", (windowWidth/2) - (posXPuzzleRow[((i - ((page-1)*limitQuantityPuzzle))/quantityPuzzleLineX)] / 2));
                    posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[((i - ((page-1)*limitQuantityPuzzle))/quantityPuzzleLineX)] / 2);    
                    posYPuzzle+=spaceBetweenY[(((i - ((page-1)*limitQuantityPuzzle))-1)/quantityPuzzleLineX)]+10+textureFigure.height+3;

                }

            }//for

        }//if

        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){

            posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[0]/2);
        
            posYPuzzle = ((GetScreenHeight() - (GetScreenHeight() - nextPuzzleY))/2) - ((calcPosYPuzzle(textureMinPuzzle, ((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle <= quantityPuzzle ? limitQuantityPuzzle : ((quantityPuzzle - (((page-1)*limitQuantityPuzzle) + limitQuantityPuzzle ))+limitQuantityPuzzle), quantityPuzzleLineX, textureFigure.height) + (currentPuzzleLineY * 10))/2); 
        
            for (int i = ((page-1)*limitQuantityPuzzle)+1;  i<=quantityPuzzle && i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle; i++){

                //check the collision
                if(!viewImgPuzzle && CheckCollisionPointRec(mousePos, (Rectangle){posXPuzzle, posYPuzzle,textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width, textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].height })){
                    
                    PlaySound(zoom);
                    
                    viewImgPuzzle = 1;

                    puzzleView = (i - ((page-1)*limitQuantityPuzzle))-1;

                    break;

                }

                posXPuzzle += textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1].width + 10;

                //next to check
                if((i % quantityPuzzleLineX) == 0 && (i - ((page-1)*limitQuantityPuzzle) != limitQuantityPuzzle)){
                    
                    //printf("posicionX %d", (windowWidth/2) - (posXPuzzleRow[((i - ((page-1)*limitQuantityPuzzle))/quantityPuzzleLineX)] / 2));
                    posXPuzzle = (GetScreenWidth()/2) - (posXPuzzleRow[((i - ((page-1)*limitQuantityPuzzle))/quantityPuzzleLineX)] / 2);    
                    posYPuzzle+=spaceBetweenY[(((i - ((page-1)*limitQuantityPuzzle))-1)/quantityPuzzleLineX)]+10+textureFigure.height+3;

                }

            }//for

        }//if 

        if(viewImgPuzzle){
            
            textureViewPuzzle = LoadTextureFromImage(imgPuzzle[puzzleView]);

            while (viewImgPuzzle)
            {
                
                BeginDrawing();
                ClearBackground(RAYWHITE);

                DrawTexture(textureViewPuzzle, (GetScreenWidth()/2)-(textureViewPuzzle.width/2), (GetScreenHeight()/2)-(textureViewPuzzle.height/2), WHITE);
                DrawRectangleLines((GetScreenWidth()/2)-(textureViewPuzzle.width/2), (GetScreenHeight()/2)-(textureViewPuzzle.height/2), textureViewPuzzle.width, textureViewPuzzle.height, BLACK);

                EndDrawing();

                if(WindowShouldClose()){

                    optionPuzzle = -1;
                    break;

                }

                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){

                    viewImgPuzzle = 0;
                    PlaySound(zoom);
                }

            }
            
            UnloadTexture(textureViewPuzzle);
        }

        if(pressSound){

            StopSound(menuBackground);

            PlaySound(select);

            WaitTime(0.1);

            configSound();
            
            percentage = masterVolume * 0.01f;

            SetMasterVolume(percentage);

            percentage = backgroundVolume * 0.01f;

            SetSoundVolume(menuBackground, percentage);

            percentage = specialVolume * 0.01f;

            for (int i = 0; i < countSpecialSound; i++)
            {
                SetSoundVolume((*specialSound[i]), percentage);    
            }
            
            ResumeSound(menuBackground);

            pressSound = 0;

        }

    }  

    UnloadTexture(textureNextPuzzle);
    UnloadTexture(texturePreviousPuzzle);
    UnloadTexture(textureWrong);
    UnloadTexture(textureFigure);
    UnloadTexture(textureSound);
    //UnloadTexture(textureViewPuzzle);

    UnloadSound(hover);
    UnloadSound(select);
    UnloadSound(pagination);
    UnloadSound(zoom);
    UnloadSound(menuBackground);

    //free the textures and images
    for (int i = ((page-1)*limitQuantityPuzzle)+1; i <= ((page-1)*limitQuantityPuzzle)+limitQuantityPuzzle && i<=quantityPuzzle; i++){
        UnloadTexture(textureMinPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]);
        UnloadImage(imgPuzzle[(i - ((page-1)*limitQuantityPuzzle))-1]);
    }
    
    return optionPuzzle;
}

int solvePuzzle(int puzzleSelected){

    char imageName[35];
    char imageParse[10];
    // -1 not change for close the window
    //1 select a new puzzle for the menu
    short int status = -1;

    float percentage = 0.0f;

    short int viewImgPuzzle = 0;

    short int winSound = 0;
    
    // general Variables
    int figureSelectionX = 0;

    Confetti confetti[MAX_CONFETTI];
    
    int userFigure = 0;

    int figureToPaint = -1;

    short int paintFigure = 0;
    
    //Btn images selection
    const int nextFigureX = 680;
    const int nextFigureY = 480;

    const int previousFigureX = 300; 
    const int previousFigureY = 480;

    //init the confetti
    for (int i = 0; i < MAX_CONFETTI; i++) {
        confetti[i].position = (Vector2){ GetRandomValue(0, GetScreenWidth()), -GetRandomValue(0, GetScreenHeight()) };
        confetti[i].speed = (Vector2){ GetRandomValue(-5, 5), GetRandomValue(5, 15) };
        confetti[i].color = (Color){ GetRandomValue(50, 255), GetRandomValue(50, 255), GetRandomValue(50, 255), 255 };
        confetti[i].shape = GetRandomValue(0, 1); // 0: Rentangle, 1: Triangle
    }

    const int figureToShow = 4;

    strcpy(imageName, "../puzzle/puzzleImage");
    sprintf(imageParse, "%d", puzzleSelected);
    strcat(imageName, imageParse);
    strcat(imageName, ".png");

    Image imgPuzzle = LoadImage(imageName);

    strcpy(imageName, "../puzzle/minPuzzleImage");
    strcat(imageName, imageParse);
    strcat(imageName, ".png");

    Image imgMinPuzzle = LoadImage(imageName);
        
    Image imgNextFigure = LoadImage("../assets/BtnNextFigure.png");

    Image imgMenu = LoadImage("../assets/BtnMenu.png");

    Image imgPreviousFigure = LoadImage("../assets/BtnPreviousFigure.png");

    Image imgWrong = LoadImage("../assets/BtnWrong.png");
    
    Image imgSound = LoadImage("../assets/Sound.png");

    const int btnMenuX = nextFigureX+imgNextFigure.width+35;

    const int btnMenuY = GetScreenHeight() - imgMenu.height;

    const int btnSoundX = btnMenuX + imgMenu.width + 15;

    Sound select = LoadSound("../assets/select.wav");
    Sound changeFigure = LoadSound("../assets/changeFigure.wav");
    Sound explotion = LoadSound("../assets/explotion.wav");
    Sound applause = LoadSound("../assets/applause.wav");
    Sound correctFigure = LoadSound("../assets/correctFigure.mp3");
    Sound invalidFigure = LoadSound("../assets/invalidFigure.wav");
    Sound zoom = LoadSound("../assets/zoom.mp3");
    Sound menu = LoadSound("../assets/menu.mp3");
    Sound gameBackground = LoadSound("../assets/gameBackground.mp3");
    
    Sound *specialSound[] = {&select, &changeFigure, &explotion, &applause, &correctFigure, &invalidFigure, 
    &zoom, &menu};

    const int countSpecialSound = sizeof(specialSound) / sizeof(specialSound[0]);

    //init the current config sound

    percentage = masterVolume * 0.01f;

    SetMasterVolume(percentage);
    
    percentage = backgroundVolume * 0.01f;

    SetSoundVolume(gameBackground, percentage);

    percentage = specialVolume * 0.01f;

    for (int i = 0; i < countSpecialSound; i++)
    {
        
        SetSoundVolume((*specialSound[i]), percentage);

    }
    
    //int the current config sound

    Rectangle sourceRect = { 0, 0, 64, 64 }; // Por ejemplo, recortar una región de 64x64 desde la esquina superior izquierda

    const int puzzleX = ((GetScreenWidth()/2)-(imgPuzzle.width/2));

    //The distance of the top of the window
    const int puzzleY = (((GetScreenHeight()-(GetScreenHeight()-previousFigureY))/2)-(imgPuzzle.height/2));

    const int imgMinPuzzleX = (previousFigureX/2) - (imgMinPuzzle.width/2);

    const int imgMinPuzzleY = (GetScreenHeight() - imgMinPuzzle.height) - ((GetScreenHeight() - imgMinPuzzle.height) - previousFigureY) + imgMinPuzzle.width >= GetScreenHeight() ? (GetScreenHeight() - imgMinPuzzle.height) - ((GetScreenHeight() - imgMinPuzzle.height) - previousFigureY) - 5 : (GetScreenHeight() - imgMinPuzzle.height) - ((GetScreenHeight() - imgMinPuzzle.height) - previousFigureY);
    
    Texture2D texturePuzzle = LoadTextureFromImage(imgPuzzle);

    Texture2D textureMinPuzzle = LoadTextureFromImage(imgMinPuzzle);

    Texture2D textureWrong = LoadTextureFromImage(imgWrong);

    Texture2D textureMenu = LoadTextureFromImage(imgMenu);

    Texture2D textureSound = LoadTextureFromImage(imgSound);

    int totalFigure = (texturePuzzle.width/FIGURE_SIZE)*(texturePuzzle.height/FIGURE_SIZE);

    int solveFigureTotal = 0;

    //array figure
    struct Figure *figureList;
    
    struct Figure *solveFigureList;
    
    // Asignar memoria dinámicamente para el arreglo de estructuras Figure
    figureList = (struct Figure *)malloc(totalFigure * sizeof(struct Figure));
    
    solveFigureList = (struct Figure *)malloc(totalFigure * sizeof(struct Figure));

    Vector2 mousePos;
    
    randomAssignFigure(figureList, totalFigure);

    Texture2D textureNextFigure = LoadTextureFromImage(imgNextFigure);

    Texture2D texturePreviousFigure = LoadTextureFromImage(imgPreviousFigure);

    UnloadImage(imgNextFigure);
    UnloadImage(imgPreviousFigure);
    UnloadImage(imgPuzzle);
    UnloadImage(imgMinPuzzle);
    UnloadImage(imgWrong);
    UnloadImage(imgMenu);
    UnloadImage(imgSound);

    PlaySound(gameBackground);

    while (!WindowShouldClose() && status == -1) {
        // Lógica del juego o aplicación aquí

        // Limpiar la pantalla
        BeginDrawing();
        ClearBackground(RAYWHITE);
                
        mousePos = GetMousePosition();
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            
            //The user win
            if(totalFigure <= 0){

                status = 1;

            }

            if(CheckCollisionPointRec(mousePos, (Rectangle){btnMenuX, btnMenuY, textureMenu.width, textureMenu.height})){

                PlaySound(menu);
                WaitTime(0.3);
                
                status = 0;

            }

            if ((userFigure < (totalFigure-figureToShow) && CheckCollisionPointRec(mousePos, (Rectangle){nextFigureX, nextFigureY, textureNextFigure.width, textureNextFigure.height}))){
                
                PlaySound(changeFigure);

                userFigure++;
                
            }

            if ((userFigure > 0 && CheckCollisionPointRec(mousePos, (Rectangle){previousFigureX, previousFigureY, texturePreviousFigure.width, texturePreviousFigure.height}))){

                PlaySound(changeFigure);

                userFigure--;

            }

            figureSelectionX = previousFigureX+texturePreviousFigure.width+10;

            for (int i = userFigure; i < userFigure+figureToShow && i < totalFigure; i++){
                
                if (CheckCollisionPointRec(mousePos, (Rectangle){figureSelectionX, nextFigureY, FIGURE_SIZE, FIGURE_SIZE})){
                    PlaySound(select);
                    paintFigure = 1;
                    figureToPaint = figureList[i].id;
                    break;
                }
                
                figureSelectionX += FIGURE_SIZE + 10;
            }

        }
        
        if(userFigure+figureToShow < totalFigure ){

            DrawTexture(textureNextFigure, nextFigureX, nextFigureY, WHITE);

        }else{
            DrawTexture(textureWrong, nextFigureX, nextFigureY, WHITE);
        }
        
        if(userFigure > 0){
            DrawTexture(texturePreviousFigure, previousFigureX, previousFigureY, WHITE);
        }else{

            DrawTexture(textureWrong, previousFigureX, previousFigureY, WHITE);
        }
        
        DrawTexture(textureMinPuzzle, imgMinPuzzleX, imgMinPuzzleY, WHITE);
        DrawTexture(textureMenu, btnMenuX, btnMenuY, WHITE);
        DrawTexture(textureSound, btnSoundX, btnMenuY, WHITE);

        if(totalFigure > 0 && CheckCollisionPointRec(mousePos, (Rectangle){imgMinPuzzleX, imgMinPuzzleY, textureMinPuzzle.width, textureMinPuzzle.height})){
                
            DrawRectangle(imgMinPuzzleX, imgMinPuzzleY, textureMinPuzzle.width, textureMinPuzzle.height, (Color){255, 255, 255, 70});

        }else{

            DrawRectangleLines(imgMinPuzzleX, imgMinPuzzleY, textureMinPuzzle.width, textureMinPuzzle.height, BLACK);

        }
                
        figureSelectionX = previousFigureX+texturePreviousFigure.width+10;

        for (int i = userFigure; i < userFigure+figureToShow && i < totalFigure; i++)
        {
            getFigure(texturePuzzle, figureList[i].id, &sourceRect);
            DrawTextureRec(texturePuzzle, sourceRect, (Vector2){ figureSelectionX, nextFigureY }, WHITE);
            DrawRectangleLines(figureSelectionX, nextFigureY, FIGURE_SIZE, FIGURE_SIZE, BLACK);
            
            figureSelectionX += FIGURE_SIZE + 10;
            
        }

        //solve list figure
        for (int i = 0; i < solveFigureTotal; i++)
        {
            getFigure(texturePuzzle, solveFigureList[i].id, &sourceRect);
            DrawTextureRec(texturePuzzle, sourceRect, (Vector2){ puzzleX+(sourceRect.x), puzzleY+(sourceRect.y) }, WHITE);

        }

        //DrawTexture(texturePuzzle, puzzleX, puzzleY, WHITE);

        //horizontal lines -
        
        for (int i = 0; i <= (texturePuzzle.height/FIGURE_SIZE); i++)
        {
            DrawLine(puzzleX, puzzleY+(FIGURE_SIZE*i), puzzleX+texturePuzzle.width, puzzleY+(FIGURE_SIZE*i), BLACK);
        }
        
        //vertical lines |

        for (int i = 0; i <= (texturePuzzle.width/FIGURE_SIZE); i++)
        {
            DrawLine(puzzleX+(FIGURE_SIZE*i), puzzleY, puzzleX+(FIGURE_SIZE*i), puzzleY+texturePuzzle.height, BLACK);
        }

        if(paintFigure){
            //mousePos = GetMousePosition();
            getFigure(texturePuzzle, figureToPaint, &sourceRect);
            DrawTextureRec(texturePuzzle, sourceRect, (Vector2){mousePos.x-FIGURE_SIZE/2, mousePos.y-FIGURE_SIZE/2}, WHITE);
        }

        if(paintFigure && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){

            getFigure(texturePuzzle, figureToPaint, &sourceRect);
            //mousePos = GetMousePosition();
            if(CheckCollisionPointRec(mousePos, (Rectangle){puzzleX+(sourceRect.x), puzzleY+(sourceRect.y), FIGURE_SIZE, FIGURE_SIZE})){
                
                getSolveFigure(solveFigureList, &figureList, figureToPaint, totalFigure, solveFigureTotal);

                ++solveFigureTotal;
                --totalFigure;

                if ((userFigure+figureToShow) > figureToShow) --userFigure;
                
                //Play Sound until reach the final figure
                //To hear more clear the winSound
                if(totalFigure > 0) PlaySound(correctFigure);

            }else if(CheckCollisionPointRec(mousePos, (Rectangle){puzzleX, puzzleY, texturePuzzle.width, texturePuzzle.height})){

                PlaySound(invalidFigure);
                
            }

            paintFigure = 0;
        }
        
        if(!IsSoundPlaying(gameBackground)){

            PlaySound(gameBackground);

        }

        //the user win
        if(totalFigure <= 0){
            
            //make darker the screen to know the puzzle is solve
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0,0,0,30});

            if(!winSound){PlaySound(explotion); PlaySound(applause); winSound = 1;}

            //update confetti
            for (int i = 0; i < MAX_CONFETTI; i++) {
                confetti[i].position.x += confetti[i].speed.x;
                confetti[i].position.y += confetti[i].speed.y;

                // reset confetti positions
                if (confetti[i].position.y > GetScreenHeight()) {
                    confetti[i].position.y = -GetRandomValue(0, GetScreenHeight());
                    confetti[i].position.x = GetRandomValue(0, GetScreenWidth());
                }
            }

            for (int i = 0; i < MAX_CONFETTI; i++) {
                if (confetti[i].shape == 0) {
                    DrawRectangle(confetti[i].position.x, confetti[i].position.y, 10, 5, confetti[i].color);
                } else {
                    DrawTriangle(
                        (Vector2){ confetti[i].position.x - 5, confetti[i].position.y },
                        (Vector2){ confetti[i].position.x, confetti[i].position.y+10 },
                        (Vector2){ confetti[i].position.x + 5, confetti[i].position.y },
                        confetti[i].color
                    );
                }
            }

        }

        // Finalizar el dibujo y mostrar en la pantalla
        EndDrawing();

        if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            //mousePos = GetMousePosition();

            if(!viewImgPuzzle && CheckCollisionPointRec(mousePos, (Rectangle){imgMinPuzzleX, imgMinPuzzleY, textureMinPuzzle.width, textureMinPuzzle.height})){
                
                PlaySound(zoom);

                viewImgPuzzle = 1;

            }

            if((userFigure < (totalFigure-figureToShow) && CheckCollisionPointRec(mousePos, (Rectangle){nextFigureX, nextFigureY, textureNextFigure.width, textureNextFigure.height}))){
                
                PlaySound(changeFigure);
                WaitTime(0.15);
                ++userFigure;
                
            }
            
            if((userFigure > 0 && CheckCollisionPointRec(mousePos, (Rectangle){previousFigureX, previousFigureY, texturePreviousFigure.width, texturePreviousFigure.height}))){
                
                PlaySound(changeFigure);
                WaitTime(0.15);
                --userFigure;
                
            }
        }

        //viewImgPuzzle
        while(viewImgPuzzle){
            
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(texturePuzzle, (GetScreenWidth()/2)-(texturePuzzle.width/2), (GetScreenHeight()/2)-(texturePuzzle.height/2), WHITE);
            DrawRectangleLines((GetScreenWidth()/2)-(texturePuzzle.width/2), (GetScreenHeight()/2)-(texturePuzzle.height/2), texturePuzzle.width, texturePuzzle.height, BLACK);
            
            EndDrawing();

            if(WindowShouldClose()){

                break;

            }

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){

                viewImgPuzzle = 0;

                PlaySound(zoom);

                WaitTime(0.1);

            }

        }//while

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, (Rectangle){btnSoundX, btnMenuY, textureSound.width, textureSound.height})){

            StopSound(gameBackground);

            PlaySound(select);

            WaitTime(0.1);

            configSound();
            
            percentage = masterVolume * 0.01f;

            SetMasterVolume(percentage);

            percentage = backgroundVolume * 0.01f;

            SetSoundVolume(gameBackground, percentage);

            percentage = specialVolume * 0.01f;

            for (int i = 0; i < countSpecialSound; i++)
            {
                SetSoundVolume((*specialSound[i]), percentage);    
            }
            
            ResumeSound(gameBackground);

        }
        
    }

    //only needed for malloc
    free(figureList);
    free(solveFigureList);

    UnloadTexture(texturePuzzle);
    UnloadTexture(textureNextFigure);
    UnloadTexture(texturePreviousFigure);
    UnloadTexture(textureWrong);
    UnloadTexture(textureMenu);
    UnloadTexture(textureSound);

    UnloadSound(select);
    UnloadSound(changeFigure);
    UnloadSound(explotion);
    UnloadSound(applause);
    UnloadSound(correctFigure);
    UnloadSound(invalidFigure);
    UnloadSound(zoom);
    UnloadSound(menu);
    UnloadSound(gameBackground);

    return status;
}  

int main(){

    const int windowWidth = 950;
    const int windowHeight = 600;
    const int limitPuzzle = 9;

    //-1 close window
    //0 back to menu
    //1 solve the puzzle
    short int status = 0;

    int puzzleSelected = 0;
    int page = 1;
    // Inicializar Raylib
    InitWindow(windowWidth, windowHeight, "Puzzle");

    Image windowIcon = LoadImage("../assets/iconExe.png");

    SetWindowIcon(windowIcon);

    UnloadImage(windowIcon);

    InitAudioDevice();

    SetTargetFPS(60);
    
    while(status != -1){

        puzzleSelected = menu(page);

        if(puzzleSelected == -1){

            CloseAudioDevice();

            CloseWindow();

            return 0;
        }
        
        page = ((puzzleSelected-1)/limitPuzzle)+1;

        status = solvePuzzle(puzzleSelected);
    }
    
    CloseAudioDevice();

    CloseWindow();

    return 0;
}