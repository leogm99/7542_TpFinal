#ifndef USER_H_
#define USER_H_
#include "../common/socket.h"
#include "../common/Protocol.h"
#include "../common/BlockingQueue.h"
#include "th_sender.h"
#include "ThReceiver.h"
#include "PlayerModel.h"
#include <map>

// le pasamos el socket por movimiento
// sender/receiver tendran una referencia
// al socket
class User {
private:
    Protocol protocol;
    Socket socket;
    ThSender sender;
    ThReceiver receiver;
    PlayerModel& model;
    bool playing;
public:
    User(Socket socket, PlayerModel& model, BlockingQueue<std::map<int, std::pair<float, float>>>& updates);

    User(const User& other) = delete;
    User& operator=(const User& other) = delete;

    User(User&& other) noexcept;
    User& operator=(User&& other) noexcept;

    void run();

    void start();
    void join();
    void stop();

    bool isDead();

    ~User();
};

#endif
