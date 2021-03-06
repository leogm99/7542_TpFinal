#ifndef GAMESMONITOR_H
#define GAMESMONITOR_H

#include <map>
#include <mutex>
#include <yaml-cpp/node/node.h>
#include "match.h"
#define MAP_PATH_PREFIX "/var/cs2d/maps/"
#define MAP_EXTENSION ".yml"

/*
 * contenedor de juegos
 * varios hilos acceden de manera concurrente
 * para crear partidas, listarlas
 * unirse, etc etc, asi que deberia estar protegido
 * un monitor para esto es ideal (idea de tp3)
 */

class GamesMonitor {
private:
    std::map<std::string, Match> matches;
    std::map<int, int> matchesConfig; // config de partidas
    std::unordered_set<std::string> mapNames;
    std::mutex gamesMonitorLock;
public:
    explicit GamesMonitor(YAML::Node& config);

    GamesMonitor(const GamesMonitor& other) = delete;
    GamesMonitor& operator=(const GamesMonitor& other) = delete;

    GamesMonitor(GamesMonitor&& other) ;
    GamesMonitor& operator=(GamesMonitor&& other) ;

    bool createMatch(std::string gameName,
                     const std::string& mapName,
                     const std::function<Socket(void)> &handIn,
                     const std::function<void(int8_t)>& response);
    bool joinMatch(const std::string &gameName,
                   const std::function<Socket(void)> &handIn,
                   const std::function<void(int8_t)> &response);

    std::string listGames();
    std::string listMaps();

    void stopGames();

    ~GamesMonitor();

};


#endif
