#ifndef __UPGRADE_UI_H_
#define __UPGRADE_UI_H_

#include "../GameDefines.h"

typedef struct UpgradeUI {
    Enum_UpgradeOptionType option[3];
    void (*OnUpgradeChosenHandle)(Enum_UpgradeOptionType);
} UpgradeUI;

UpgradeUI *UpgradeUI_New();
void UpgradeUI_Open(UpgradeUI *ui, Enum_UpgradeOptionType opt1, Enum_UpgradeOptionType opt2, Enum_UpgradeOptionType opt3);
void UpgradeUI_GUI(UpgradeUI *ui);

#endif // __UPGRADE_UI_H_