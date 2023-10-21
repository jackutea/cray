#include <stdlib.h>
#include "UpgradeUI.h"
#include "../GUI/GUI.h"

string GetOptionText(Enum_UpgradeOptionType opt) {
    switch (opt) {
        case Enum_UpgradeOptionType_BulletAtk:
            return "Bullet Atk + 1";
        case Enum_UpgradeOptionType_GunCooldown:
            return "Gun Cooldown * 0.5";
        case Enum_UpgradeOptionType_MoveSpeed:
            return "Move Speed + 3";
        default:
            return "None";
    }
}

UpgradeUI *UpgradeUI_New() {
    UpgradeUI *upgradeUI = (UpgradeUI *)malloc(sizeof(UpgradeUI));
    upgradeUI->option[0] = 0;
    upgradeUI->option[1] = 0;
    upgradeUI->option[2] = 0;
    return upgradeUI;
}

void UpgradeUI_Open(UpgradeUI *ui, Enum_UpgradeOptionType opt1, Enum_UpgradeOptionType opt2, Enum_UpgradeOptionType opt3) {
    ui->option[0] = opt1;
    ui->option[1] = opt2;
    ui->option[2] = opt3;
}

void UpgradeUI_GUI(UpgradeUI *ui) {

    // layout: 3 options
    Rectangle rect1 = (Rectangle){ 0, 0, 160, 30 };
    Rectangle rect2 = (Rectangle){ 0, 30, 160, 30 };
    Rectangle rect3 = (Rectangle){ 0, 60, 160, 30 };

    // option 1
    bool isOpt1Click = GUI_Button(rect1, GetOptionText(ui->option[0]), 14, WHITE, BLACK);
    if (isOpt1Click) {
        ui->OnUpgradeChosenHandle(ui->option[0]);
        return;
    }
    bool isOpt2Click = GUI_Button(rect2, GetOptionText(ui->option[1]), 14, WHITE, BLACK);
    if (isOpt2Click) {
        ui->OnUpgradeChosenHandle(ui->option[1]);
        return;
    }
    bool isOpt3Click = GUI_Button(rect3, GetOptionText(ui->option[2]), 14, WHITE, BLACK);
    if (isOpt3Click) {
        ui->OnUpgradeChosenHandle(ui->option[2]);
        return;
    }
}