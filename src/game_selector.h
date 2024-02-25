#ifndef GAME_SELECTOR_H_
#define GAME_SELECTOR_H_

void (*LoadGameSelector(int))(void);
void (*UpdateGameSelector(int))(void);
void (*DrawGameSelector(int))(void);
void (*UnloadGameSelector(int))(void);
bool (*IsFinishedGameSelector(int))(void);
void GameSelector(int game_id, void (**load)(), void (**update)(), void (**draw)(), void (**unload)(), bool (**finished)());

#endif
