#include "Score.h"

void scoreUpdate(Score* s)
{
    printf("%d\n", s->mAcctualScore);
    //Get rid of existing surface
    if (s->mScoreText.mTextSurface != NULL) {
        SDL_FreeSurface(s->mScoreText.mTextSurface);
        s->mScoreText.mTextSurface = NULL;
    }
    char scoreText[10];
    sprintf(scoreText, "%d", s->mAcctualScore);
    s->mScoreText.mTextSurface = TTF_RenderText_Solid(s->mScoreText.mFont, scoreText, s->mScoreText.mTextColor);
    //Update width of a surface
    TTF_SizeText(s->mScoreText.mFont, scoreText, &s->mScoreText.mBounds.w, &s->mScoreText.mBounds.h);
    //Update position of a surface
    s->mScoreText.mBounds.x = SCREEN_WIDTH / 2 - s->mScoreText.mBounds.w / 2;
    if (s->mScoreText.mTextSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
}
void scoreConstruct(Score* s)
{
    s->mAcctualScore = 20;
    s->mScoreText.mBounds.w = 50;
    s->mScoreText.mBounds.h = 50;
    s->mScoreText.mBounds.x = SCREEN_WIDTH / 2 - s->mScoreText.mBounds.w / 2;
    s->mScoreText.mBounds.y = 50;
    s->mScoreText.mTextColor.r = 255;
    s->mScoreText.mTextColor.g = 255;
    s->mScoreText.mTextColor.b = 255;
    s->mScoreText.mTextColor.a = 255;
    s->mScoreSaved = false;
    textConstruct(&s->mScoreText, "0");
}
void scoreSaveToAFile(Score* s, FILE* f)
{
    if (s->mAcctualScore > 0) {
        //Load score file
        f = fopen("cachedStats.csv", "r+");
        if (f == NULL) {
            printf("Unable to open file cachedStats.csv");
            return;
        }
        //First find if there is user with inputed nick
        //dump first header line of file
        char temp[101];
        fgets(temp, 0, f);
        bool foundedLastScore = scoreFindInFile(s, f);
        if (!foundedLastScore) {
            //Create a new score result
            scoreAddNewToFile(s, f);
            // sprintf(output, "%s;%06d\n", s->mPlayerName, s->mAcctualScore);
            // printf("%s", output);
        }
        s->mScoreSaved = true;
        //TODO: ZRÓB CZYSZCZENIE DO KOŃCA LINII
        // Close cachedStats file
        fclose(f);
    }
}

bool scoreFindInFile(Score* s, FILE* f)
{
    bool foundedPlayer = false;
    ssize_t read;
    size_t filePos = 0;
    char* line = NULL;
    while ((read = getline(&line, &filePos, f)) != -1) {
        char readedNick[MAX_NICKNAME_LENGTH];
        char score[MAX_SCORE_DIGITS];
        size_t lastScoreLength = parseLine(line, readedNick, score, s->mPlayerName);
        if (lastScoreLength > 0) {
            if (strcmp(s->mPlayerName, readedNick) == 0) {
                foundedPlayer = true;
                unsigned long long scoreInt = atoi(score);
                if (scoreInt < s->mAcctualScore) {
                    printf("score: %s", score);
                    scoreReplaceInFile(s, f, lastScoreLength);
                }
            }
        }
    }
    if (line) {
        free(line);
    }
    return foundedPlayer;
}
bool scoreReplaceInFile(Score* s, FILE* f, size_t lenOfScore)
{
    char output[MAX_SCORE_DIGITS];
    sprintf(output, "%06d\n", s->mAcctualScore);
    fseek(f, -1 + -lenOfScore * sizeof(char), SEEK_CUR);
    // fseek(f, -2*lenOfScore * sizeof(char), SEEK_CUR);
    fputs(output, f);
}
size_t parseLine(char* line, char* name, char* score, char* currentPlayerNick)
{
    int amountOfSemicolons = 0;
    bool readingScore = false;
    size_t nameLen = 0;
    size_t scoreLen = 0;
    size_t lengthOfLine = strlen(line);
    for (int i = 0; i < lengthOfLine; i++) {
        if (line[i] == ';') {
            name[nameLen] = '\0';
            readingScore = true;
            amountOfSemicolons++;
            if (amountOfSemicolons > 1)
                return scoreLen;
            else
                continue;
        }
        if (!readingScore) {
            if (line[i] == currentPlayerNick[i]) {
                name[nameLen] = line[i];
                nameLen++;
            } else {
                return 0;
            }
        } else {
            if (isdigit(line[i])) {
                score[scoreLen] = line[i];
                scoreLen++;
            } else {
                return scoreLen;
            }
        }
    }
    return scoreLen;
}

bool scoreAddNewToFile(Score* s, FILE* f)
{
    //Nicnamespace + semicolon + space for digits
    char output[MAX_NICKNAME_LENGTH + 1 + MAX_SCORE_DIGITS];
    sprintf(output, "%s;%06d\n", s->mPlayerName, s->mAcctualScore);
    fseek(f, 0, SEEK_END);
    fputs(output, f);
    return true;
}

bool uploadScoreToServer(Score* s)
{
    //Wireshark will just show that password but I don't care now
    char newbieProtection[13] = "curlPASSWORD";
    //Prepare message nick+semicolon+score
    char message[MAX_NICKNAME_LENGTH + 1 + MAX_SCORE_DIGITS];

    sprintf(message, "%s;%06d\n", s->mPlayerName, s->mAcctualScore);
    //cURL
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        //Set url
        curl_easy_setopt(curl, CURLOPT_URL, "http://sigma.ug.edu.pl/~kgzik/flappyBird/");
        //Prepare post data 21 for mode=upload&password=, 10 for password + 6 for another post field, last for message
        char postFields[21 + 13 + 6 + MAX_NICKNAME_LENGTH + 1 + MAX_SCORE_DIGITS] = "";
        //Concatenate all fields
        strcat(postFields, "mode=upload&password=");
        strcat(postFields, newbieProtection);
        strcat(postFields, "&data=");
        strcat(postFields, message);
        printf("%s", postFields);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields);
        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            printf("Unable to perform request cURL error: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

bool scoreGetHighscores(Score* s, FILE* f)
{
    f = fopen("cachedStats.csv", "w");
    if (f != NULL) {
        //Prepare curl vars
        CURL* curl;
        CURLcode res;
        //Init curl
        curl = curl_easy_init();
        if (curl) {
            //Set options
            curl_easy_setopt(curl, CURLOPT_URL, "http://sigma.ug.edu.pl/~kgzik/flappyBird/");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "mode=download");
            //Set where to write data
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)f);
            //Using internal default function in curl so that's why NULL
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);

            //Perform request
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                printf("Unable to perform request cURL error: %s\n", curl_easy_strerror(res));
            }
            curl_easy_cleanup(curl);
            fclose(f);
            return true;
        }
    } else {
        return false;
    }
}
