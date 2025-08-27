/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DIALOG_C_CREATEDIALOGEXAMPLE_H
#define DIALOG_C_CREATEDIALOGEXAMPLE_H

#include "ArkUIBaseNode.h"
#include "ArkUIButtonNode.h"
#include "ArkUITextNode.h"
#include "ArkUIColumnNode.h"
#include <arkui/native_dialog.h>
#include <hilog/log.h>

namespace NativeModule {
ArkUI_NativeDialogHandle dialogController;

void ShowDialog() {
    ArkUI_NativeDialogAPI_1 *dialogAPI = reinterpret_cast<ArkUI_NativeDialogAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_DIALOG, "ArkUI_NativeDialogAPI_1"));
    if (!dialogController) {
        dialogController = dialogAPI->create();
    }
    auto textNode = std::make_shared<ArkUITextNode>();
    textNode->SetTextContent("这是一个弹窗");
    textNode->SetWidth(300);
    textNode->SetHeight(300);
    dialogAPI->setContent(dialogController, textNode->GetHandle());
    dialogAPI->setContentAlignment(dialogController, static_cast<int32_t>(ARKUI_ALIGNMENT_CENTER), 0, 0);
    dialogAPI->setBackgroundColor(dialogController, 0xffffffff);
    dialogAPI->setCornerRadius(dialogController, 6, 6, 6, 6);
    dialogAPI->setModalMode(dialogController, true);
    dialogAPI->setAutoCancel(dialogController, true);
    dialogAPI->show(dialogController, false);
}

std::shared_ptr<ArkUIBaseNode> CreateDialogExample() {
    // 创建组件并挂载
    auto column = std::make_shared<ArkUIColumnNode>();
    column->SetWidth(1, true);
    column->SetHeight(1, true);
    column->SetBackgroundColor(0x33ff0000);
    column->SetPadding(20, false);
    auto button = std::make_shared<ArkUIButtonNode>();
    button->SetButtonLabel("打开弹窗");
    button->RegisterOnClick([]() {
        ShowDialog();
    });
    column->AddChild(button);
    
    return column;
}
} // namespace NativeModule
#endif //DIALOG_C_CREATEDIALOGEXAMPLE_H
