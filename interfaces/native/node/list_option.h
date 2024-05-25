/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef ARKUI_NATIVE_NODE_LIST_OPTION_H
#define ARKUI_NATIVE_NODE_LIST_OPTION_H

#include <vector>
#include "core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct ArkUI_ListItemSwipeActionItem {
    void* node;

    float actionAreaDistance;
    void* onAction;
    void* onActionUserData;
    void* onEnterActionArea;
    void* onEnterActionAreaUserData;
    void* onExitActionArea;
    void* onExitActionAreaUserData;
    void* onStateChange;
    void* onStateChangeUserData;
};

struct ArkUI_ListItemSwipeActionOption {
    ArkUI_ListItemSwipeActionItem* start;
    ArkUI_ListItemSwipeActionItem* end;
    ArkUI_Int32 edgeEffect;
    void* onOffsetChange;
    void* userData;
};

struct ArkUI_ListChildrenMainSize {
    float defaultMainSize;
    std::vector<float> mainSize;
};

#ifdef __cplusplus
};
#endif
#endif // ARKUI_NATIVE_NODE_LSIT_OPTION_H