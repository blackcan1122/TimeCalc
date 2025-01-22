#include "Button.h"
#include "UIEvent.h"
#include "EventDispatcher.hpp"

Button::Button(int X, int Y, int Width, int Height, std::string InitialText, Color BackgroundColor)
{
    Construct(X, Y, Width, Height, InitialText, BackgroundColor);
}

Button& Button::Construct(Rectangle Dim, std::string InitialText, Color BackgroundColor)
{
    ButtonDim = Dim;
    m_Text = InitialText;
    m_BackgroundColor = BackgroundColor;
    return *this;
}

Button& Button::Construct(Rectangle Dim, std::string InitialText, Color BackgroundColor, bool Rounded, float Roundness)
{
    ButtonDim = Dim;
    m_Text = InitialText;
    m_BackgroundColor = BackgroundColor;
    m_IsRounded = Rounded;
    m_Roundness = Roundness;
    return *this;
}

Button& Button::Construct(int X, int Y, int Width, int Height, std::string InitialText, Color BackgroundColor)
{
    Rectangle TempRec = { X, Y, Width, Height };
    return Construct(TempRec, InitialText, BackgroundColor);
}

Button& Button::Construct(int X, int Y, int Width, int Height, std::string InitialText, Color BackgroundColor, bool Rounded, float Roundness)
{
    Rectangle TempRec = { X, Y, Width, Height };
    return Construct(TempRec, InitialText, BackgroundColor, Rounded, Roundness);
}   

Button& Button::SetEventDispatcher(std::shared_ptr<EventDispatcher> UsedDispatcher)
{
    UsedEventDispatcher = UsedDispatcher;
    return *this;
}

Button& Button::SetEventPayload(std::string GameModeName)
{
    ResponsibleGameMode = GameModeName;
    return *this;
}

Button& Button::UpdateTextPosition(Vector2 NewPos)
{
    TextPosition = NewPos;
    return *this;
}

Button& Button::UpdateTextPosition(int X, int Y)
{
    TextPosition.x = X;
    TextPosition.y = Y;
    return *this;
}

Button& Button::UpdateButtonPosition(Vector2 NewPos)
{
    ButtonDim.x = NewPos.x;
    ButtonDim.y = NewPos.y;
    return *this;
}

Button& Button::UpdateButtonPosition(int X, int Y)
{
    ButtonDim.x = X;
    ButtonDim.y = Y;
    return *this;
}

Button& Button::UpdateColor(Color NewColor)
{
    m_BackgroundColor = NewColor;
    return *this;
}

Button& Button::OnHover(std::function<void(Button* ButtonClass)> callback)
{
    HoverCallback = callback;
    return *this;
}

Button& Button::OnHoverLeave(std::function<void(Button* ButtonClass)> callback)
{
    HoverEndCallback = callback;
    return *this;
}

std::string Button::GetEventPayload()
{
    return ResponsibleGameMode;
}

void Button::Update()
{
    bool isHovered = (CheckCollisionPointRec(GetMousePosition(), ButtonDim) && IsCursorOnScreen());

    if (isHovered && m_WasLastHovered == false && HoverCallback)
    {
        HoverCallback(this);
    }

    else if (!isHovered && m_WasLastHovered == true && HoverEndCallback)
    {
        HoverEndCallback(this);
    }

    m_WasLastHovered = isHovered;

    if (IsClicked(GetMousePosition(), isHovered))
    {
        std::cout << "Dispatching Event" << std::endl;
        UsedEventDispatcher.get()->Dispatch(OnClickEvent());
    }
    if (m_IsRounded)
    {
        DrawRectangleRounded(ButtonDim, m_Roundness, 32, m_BackgroundColor);
    }
    else
    {
        DrawRectangle(ButtonDim.x, ButtonDim.y, ButtonDim.width, ButtonDim.height, m_BackgroundColor);
    }

    DrawText(m_Text.c_str(), ButtonDim.x + TextPosition.x, ButtonDim.y + TextPosition.y, 14, BLACK);
}

std::shared_ptr<UIEvent> Button::OnClickEvent()
{
    std::shared_ptr<UIEvent> EventUI = std::make_shared<UIEvent>();
    EventUI->ClickedUIElement = this;
    return EventUI;
}

bool Button::IsClicked(Vector2 MousePosition, bool IsHovered)
{
    return IsMouseButtonPressed(0) && IsHovered;
}
