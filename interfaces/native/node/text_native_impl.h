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

#ifndef FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_TEXT_NATIVE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_TEXT_NATIVE_IMPL_H

#include <vector>

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_TextMenuItem {
    const char* content;
    bool isDelContent;
    const char* icon;
    bool isDelIcon;
    const char* labelInfo;
    bool isDelLabel;
    int32_t id;
};

struct ArkUI_TextMenuItemArray {
    std::vector<ArkUI_TextMenuItem> items;
};

struct ArkUI_TextEditMenuOptions {
    ArkUI_TextCreateMenuCallback onCreateMenu;
    void* createUserData;
    ArkUI_TextPrepareMenuCallback onPrepareMenu;
    void* prepareUserData;
    ArkUI_TextMenuItemClickCallback onMenuItemClick;
    void* clickUserData;
};

struct ArkUI_TextSelectionMenuOptions {
    ArkUI_TextSpanType textSpanType;
    ArkUI_TextResponseType textResponseType;
    ArkUI_HapticFeedbackMode hapticFeedbackMode;
    ArkUI_NodeHandle contentNode;
    void* onMenuShow;
    void* onMenuShowUserData;
    void* onMenuHide;
    void* onMenuHideUserData;
};
#ifdef __cplusplus
}
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_INTERFACE_NATIVE_NODE_TEXT_NATIVE_IMPL_H