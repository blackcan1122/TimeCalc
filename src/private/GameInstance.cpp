#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif // !RAYGUI_IMPLEMENTATION
#include "GameInstance.h"
#include "Core.h"
#include "StateMachine.h"
#include "GameMode.h"
#include "TimeCalcMode.h"
#include "TextBox.h"
#include "UIEvent.h"
#include "EventDispatcher.hpp"
#include "Button.h"



// Definition of the static member
GameInstance* GameInstance::Instance = nullptr;

GameInstance::GameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen, bool IsDebug)
	: m_ScreenWidth(ScreenWidth), m_ScreenHeight(Screenheight), m_TargetFps(TargetFps), m_Fullscreen(Fullscreen), m_IsDebug(IsDebug)
{
	std::cout << "GameInstance was Initialized" << std::endl;
}


void GameInstance::InitGameInstance(int ScreenWidth, int Screenheight, int TargetFps, bool Fullscreen, bool isDebug)
{
	if (Instance != nullptr)
	{
		std::cerr << "GameInstance was already initialized" << std::endl;
		return;
	}

	Instance = new GameInstance(ScreenWidth, Screenheight, TargetFps, Fullscreen, isDebug);
	CreateWindow();
	GameLoop();
}

GameInstance* GameInstance::GetInstance()
{
	if (Instance != nullptr)
	{
		return Instance;
	}
	std::cerr << "GameInstance was not Created, please Call InitGameInstance first" << std::endl;
}


void GameInstance::CreateWindow()
{
	if (Instance->m_Fullscreen)
	{
		SetConfigFlags(FLAG_FULLSCREEN_MODE);
	}

	InitWindow(Instance->m_ScreenWidth, Instance->m_ScreenHeight, "GameWindow");
	SetTargetFPS(Instance->m_TargetFps);
}

void GameInstance::GameLoop()
{
	StateMachine ActiveStateMachine;
	EventDispatcher UIEventDispatcher;
	

	ActiveStateMachine.RegisterState("Menu", []() {return new TimeCalcMode(false); });
	ActiveStateMachine.RegisterState("Sandbox", []() {return new TimeCalcMode(true); });
	//ActiveStateMachine.RegisterState("Pong", []() {return new PongGameMod(); });

	// Setting initial Start Mode
	ActiveStateMachine.ChangeState("Menu");
	std::cout << sizeof*(static_cast<TimeCalcMode*>(ActiveStateMachine.GetCurrentGameMode())) << std::endl;


	// Handling UI Event
	// We Use this Event to Switch GameMode which then will update in the GameLoop
	UIEventDispatcher.AddListener("UIEvent", [&ActiveStateMachine](std::shared_ptr<Event> Event) -> void
		{
			auto ButtonClickEvent = std::dynamic_pointer_cast<UIEvent>(Event);
			if (ButtonClickEvent == nullptr)
			{
				return;
			}
			Button* ClickedButton = static_cast<Button*>(ButtonClickEvent.get()->ClickedUIElement);
		
			ActiveStateMachine.ChangeState(ClickedButton->GetEventPayload());
		});

	int TestSize = MeasureText("Time Calculator", 14);
	int PlaySize = MeasureText("Play Mode", 14);
	int OptionSize = MeasureText("Option", 14);

	Button MenuButton;
	Rectangle NewRec = { 0,-50,200,100 };
	MenuButton.Construct(NewRec, "Time Calculator", LIGHTGRAY, true, 0.2)
		.SetEventPayload("Menu")
		.SetEventDispatcher(std::make_shared<EventDispatcher>(UIEventDispatcher))
		.UpdateTextPosition(100 - (TestSize / 2), 75)
		.OnHover([](Button* MenuButton)
			{
				MenuButton->UpdateButtonPosition(0, -25);
			})
		.OnHoverLeave([](Button* MenuButton)
			{
				MenuButton->UpdateButtonPosition(0, -50);
			});

	Button PlayButton;
	Rectangle NewRecPlay = { 200,-50,200,100 };
	PlayButton.Construct(NewRecPlay, "Play Mode", LIGHTGRAY, true, 0.2)
		.SetEventPayload("Menu")
		.SetEventDispatcher(std::make_shared<EventDispatcher>(UIEventDispatcher))
		.UpdateTextPosition(100 - (PlaySize / 2), 75);

	Button OptionButton;
	Rectangle NewRecOption = { 400,-50,200,100 };
	OptionButton.Construct(NewRecOption, "Option", LIGHTGRAY, true, 0.2)
		.SetEventPayload("Menu")
		.SetEventDispatcher(std::make_shared<EventDispatcher>(UIEventDispatcher))
		.UpdateTextPosition(100 - (OptionSize / 2), 75);


	// GAMELOOP //
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ActiveStateMachine.UpdateGameMode();

		// GameMode Independend
		MenuButton.Update();
		PlayButton.Update();
		OptionButton.Update();


		EndDrawing();
	}
}
