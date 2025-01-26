#pragma once
#include "Core.h"
#include "BaseUI.h"

class UIEvent;
class EventDispatcher;

class Button : public BaseUI
{
public:
	Button() = default;
	Button(int X, int Y, int Width, int Height, std::string InitialText, Color BackgroundColor);
	~Button() = default;

	virtual Button& Construct(Rectangle Dim, std::string InitialText, Color BackgroundColor);
	virtual Button& Construct(Rectangle Dim, std::string InitialText, Color BackgroundColor, bool Rounded, float Roundness);
	virtual Button& Construct(int X, int Y, int Width, int Height, std::string InitialText, Color BackgroundColor);
	virtual Button& Construct(int X, int Y, int Width, int Height, std::string InitialText, Color BackgroundColor, bool Rounded, float Roundness);
	
	virtual Button& SetEventDispatcher(std::shared_ptr<EventDispatcher> UsedDispatcher);
	virtual Button& SetEventPayload(std::string GameModeName);

	virtual Button& UpdateTextPosition(Vector2 NewPos);
	virtual Button& UpdateTextPosition(int X, int Y);
	virtual Button& UpdateButtonPosition(Vector2 NewPos);
	virtual Button& UpdateButtonPosition(int X, int Y);
	virtual Button& UpdateColor(Color NewColor);
	virtual Button& UpdateTextColor(Color NewTextColor);
	virtual Button& UpdateFontSize(int NewFontSize);

	virtual Button& OnHover(std::function<void(Button* ButtonClass)> callback);
	virtual Button& OnHoverLeave(std::function<void(Button* ButtonClass)> callback);

	virtual std::string GetEventPayload();
	

	virtual void Update() override;

private:

	virtual std::shared_ptr<UIEvent> OnClickEvent();
	virtual bool IsClicked(Vector2 MousePosition, bool IsHovered);

	std::shared_ptr<EventDispatcher> UsedEventDispatcher;
	std::function<void(Button* ButtonClass)> HoverCallback;
	std::function<void(Button* ButtonClass)> HoverEndCallback;

	std::string ResponsibleGameMode;
	std::string m_Text;
	Vector2 TextPosition;
	int FontSize = 14;
	bool m_IsRounded;
	bool m_WasLastHovered = false;
	float m_Roundness;
	Rectangle ButtonDim;
	Color m_BackgroundColor;
	Color m_TextColor = BLACK;
};