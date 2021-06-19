#ifndef USER_H_
#define USER_H_

#include "../common/socket.h"
#include "../common/Protocol.h"
#include "../common/BlockingQueue.h"
#include "../common/ProtectedQueue.h"
#include "th_sender.h"
#include "ThReceiver.h"
//#include "PlayerModel.h"
#include "updates/Update.h"
#include <map>
#include <memory>

// le pasamos el socket por movimiento
// sender/receiver tendran una referencia
// al socket
class User {
private:
    Protocol protocol;
    Socket socket;
    ThSender sender;
    ThReceiver receiver;
    //PlayerModel& model;
    bool playing;
    uint8_t id;
public:
    //User(Socket socket, PlayerModel& model, BlockingQueue<std::map<int, std::pair<float, float>>>& updates);
    User(Socket socket,
         BlockingQueue<Update>& updateQueue,
         ProtectedQueue<std::unique_ptr<ClientEvent>>& eventQueue,
         uint8_t id);

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
