#ifndef MATCH_H_
#define MATCH_H_

#include <map>
#include "user.h"
#include "WorldModel.h"
#include "Broadcaster.h"

class Match {
public:
    Match();
    explicit Match(int playerAmount);

    Match(const Match& other) = delete;
    Match& operator=(const Match& other) = delete;

    Match(Match&& other) noexcept;
    Match& operator=(Match&& other) noexcept;

    void addUser(Socket socket);
    void removeUser();
    void removeUsers();
    ~Match();

    void startIfShould();
    void stop();

private:
    uint8_t maxUsers;
    // cuantos jugadores pueden tener las partidas? 10 max
    std::map<uint8_t, User> users;

    WorldModel world;
    // instancia las q's necesarias
    Broadcaster updates;
    // Queue<otroAlgo>& events;
};

#endif
