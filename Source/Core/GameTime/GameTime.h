#ifndef GEOMETRYWARS_CORE_GAMETIME_GAMETIME_H
#define GEOMETRYWARS_CORE_GAMETIME_GAMETIME_H


class GameTime
{
  public:
    static GameTime& Instance();

    void init();
    void onIdle();

    float current() const;
    float delta() const;

  private:
    GameTime();
    ~GameTime();

    GameTime(const GameTime&);
    const GameTime& operator=(const GameTime&);

  private:
    float initTime_;
    float lastUpdateTime_;
    float deltaTime_;
};


#endif // GEOMETRYWARS_CORE_GAMETIME_GAMETIME_H