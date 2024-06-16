#include <SFML/Graphics.h>
#include <stdbool.h>

extern const int SIMBTN_POSITION_X;
extern const int SIMBTN_POSITION_Y;
extern const sfVector2f SIMBTN_SIZE;

typedef struct
{
    bool isPaused;
    int speed;
} simState;

typedef struct
{
    int **cellsMatrix;
    simState *simulation;
} nextTickArgs;

simState initSimulation();
void drawSimBtn(sfRenderWindow *window, simState state);
void drawResetBtn(sfRenderWindow *window, bool disabled);
void drawSpeedIncreaseBtn(sfRenderWindow *window, bool disabled);
void drawSpeedDecreaseBtn(sfRenderWindow *window, bool disabled);
void drawSpeedDisplayText(sfRenderWindow *window, simState state);
bool isResetBtnClicked(sfVector2i mousePosition);
bool isSimBtnClicked(sfVector2i mousePosition);
bool isIncreaseBtnClicked(sfVector2i mousePosition);
bool isDecreaseBtnClicked(sfVector2i mousePosition);
void handleResetBtnClick(int **cellsMatrix);
void handleSimBtnClick(simState *state);
void nextTick(void *args);
void pause(int **cellsMatrix);
void increaseSpeed(simState *state);
void decreaseSpeed(simState *state);
