#ifndef GEOMETRYWARS_CORE_GAMESCORE_GAMESCORE_H
#define GEOMETRYWARS_CORE_GAMESCORE_GAMESCORE_H


class GameScore
{
  public:
    static GameScore& Instance();
    void onIdle();
    void onEnemyKilled();
    int currentScore() const;

  private:
    GameScore();
    ~GameScore();
    GameScore(const GameScore&);
    const GameScore& operator=(const GameScore&);

  private:
    static const int cEnemyKilledPoints_;
    static const float cNoKillsPenaltyRate_;
    static const float cNoKillsPenaltyDelay_;

    float timeLastKill_;
    float timeLastPenalty_;
    int currentScore_;
};


#endif // GEOMETRYWARS_CORE_GAMESCORE_GAMESCORE_H