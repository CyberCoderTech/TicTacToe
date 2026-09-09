#include <catch2/catch_test_macros.hpp>

#include "state/StateManager.hpp"
#include "ResourceManager.hpp"
#include "state/IState.hpp"


class MockState : public IState {
public:
    int eventCount = 0;
    int updateCount = 0;
    int drawCount = 0;
    sf::Time lastDt = sf::Time::Zero;

    explicit MockState(StateArguments& args) : IState(args) {}

    void HandleEvent(sf::Event& event) override {
        ++eventCount;
    }

    void Update(sf::Time dt) override {
        ++updateCount;
        lastDt = dt;
    }

    void DrawState() override {
        ++drawCount;
    }
};

TEST_CASE("StateManager operations and lifecycle", "[StateManager]") {
    sf::RenderWindow window;
    StateManager stateManager;
    ResourceManager resourceManager;
    StateArguments stateArgs{ window, stateManager, resourceManager };

    SECTION("Operations on empty StateManager do not crash") {
        sf::Event event;
        sf::Time dt = sf::seconds(1.0f);

        REQUIRE_NOTHROW(stateManager.PopState());
        REQUIRE_NOTHROW(stateManager.Event(event));
        REQUIRE_NOTHROW(stateManager.Update(dt));
        REQUIRE_NOTHROW(stateManager.Draw());
    }

    SECTION("Pushing nullptr is safely ignored") {
        sf::Event event;
        
        stateManager.PushState(nullptr);

        REQUIRE_NOTHROW(stateManager.Event(event));
    }

    SECTION("Delegation of Event, Update, and Draw to current active state") {
        auto rawState = new MockState(stateArgs);
        stateManager.PushState(std::unique_ptr<IState>(rawState));

        sf::Event event;
        sf::Time dt = sf::milliseconds(16);

        stateManager.Event(event);
        stateManager.Update(dt);
        stateManager.Draw();

        REQUIRE(rawState->eventCount == 1);
        REQUIRE(rawState->updateCount == 1);
        REQUIRE(rawState->lastDt == dt);
        REQUIRE(rawState->drawCount == 1);
    }

    SECTION("Stack LIFO order and state switching") {
        auto rawState1 = new MockState(stateArgs);
        auto rawState2 = new MockState(stateArgs);

        stateManager.PushState(std::unique_ptr<IState>(rawState1));

        sf::Time dt = sf::seconds(0.016f);
        stateManager.Update(dt);

        REQUIRE(rawState1->updateCount == 1);
        REQUIRE(rawState2->updateCount == 0);

        stateManager.PushState(std::unique_ptr<IState>(rawState2));

        stateManager.Update(dt);

        REQUIRE(rawState1->updateCount == 1);
        REQUIRE(rawState2->updateCount == 1);

        stateManager.PopState();

        stateManager.Update(dt);

        REQUIRE(rawState1->updateCount == 2);
        REQUIRE(rawState2->updateCount == 1);
    }
}