#include "GUI.h"

bool GUI_Button(Rectangle rect, string text, int fontSize, Color btnColor, Color textColor) {
    bool isHover = CheckCollisionPointRec(GetMousePosition(), rect);
    if (isHover) {
        DrawRectangleRec(rect, textColor);
        DrawRectangleLinesEx(rect, 1, textColor);
        DrawText(text, (int)rect.x + 10, (int)rect.y + 10, fontSize, btnColor);
    } else {
        DrawRectangleRec(rect, btnColor);
        DrawRectangleLinesEx(rect, 1, textColor);
        DrawText(text, (int)rect.x + 10, (int)rect.y + 10, fontSize, textColor);
    }
    return isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}