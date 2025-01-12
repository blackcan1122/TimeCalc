#pragma once
#include "raylib.h"
#include <string>


class TextInputBox
{
public:

	// Methods

	TextInputBox& Construct(Rectangle Box, Color BackgroundColor);
	TextInputBox& Construct(float x, float y, float width, float height, Color BackgroundColor);
	TextInputBox& UseBorder(bool UseBorder);
	TextInputBox& SetInitialText(std::string InitialText);
	TextInputBox& SetInitialText(char InitalText[51]);
	TextInputBox& CanBeEdited(bool IsEditable);



	TextInputBox& UpdateTextOffset(Vector2 NewTextPosition);
	TextInputBox& UpdateTextPosition();
	TextInputBox& UpdateFontSize(int NewFontSize);
	TextInputBox& UpdateFontColor(Color NewFontColor);
	TextInputBox& UpdatePosition(Vector2 NewPosition);
	TextInputBox& UpdateSize(Vector2 NewSize);
	TextInputBox& UpdateColor(Color NewColor);
	TextInputBox& UpdateTextShown(std::string Text);
	TextInputBox& UpdateBorder(int Thickness, Color BorderColor);


	void Update();

	bool bIsFocused(Vector2 MousePosition);
	bool LastActiveElement(Vector2 MousePosition);

	char StringToHold[50 + 1] = "\0";

private:

	// Member
	Rectangle Box;
	Color BoxBackgroundColor;
	std::string Text;
	Vector2 TextPosition;
	Vector2 TextOffset = { 0,0 };
	int FontSize = 8;
	Color FontColor = WHITE;
	bool IsEditable = true;

	
	int MaxChars = 5;
	
	int LetterCount = 0;

	bool bUseBorder;
	bool bHasBeenConstructed;
	bool bUsesText;

};

