/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TABS_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TABS_CUSTOM_MODIFIER_H

#include "core/interfaces/arkoala/arkoala_api.h"

struct ArkUITabsCustomModifier {
    ArkUINodeHandle (*createFrameNode)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*createTabBarFrameNode)(ArkUI_Int32 nodeId);
    ArkUI_Int32 (*getTabBarItemType)(ArkUINodeHandle node, ArkUI_Int32 tabBarItemId);
    void (*setTabBarItemsChangeEvent)(ArkUINodeHandle node, void* callback);
    void (*setShouldPlayMaskAnimation)(ArkUINodeHandle node, ArkUI_Bool shouldPlay);
    ArkUI_Int32 (*getTabBarItemSize)(ArkUINodeHandle node);
    void (*setBarBackgroundBlurStyle)(ArkUINodeHandle node, void* styleOption);
    void (*setBarBackgroundColor)(ArkUINodeHandle node, ArkUI_Uint32 color);
    void (*setBarBackgroundEffect)(ArkUINodeHandle node, void* effectOption);
    void (*setTabBarWidth)(ArkUINodeHandle node, void* tabBarWidth);
    void (*setTabBarHeight)(ArkUINodeHandle node, void* tabBarHeight);
    void (*setDivider)(ArkUINodeHandle node, void* divider);
    void (*setEffectNodeOption)(ArkUINodeHandle node, void* option);
    void (*setTabBarMode)(ArkUINodeHandle node, ArkUI_Int32 tabBarMode);
    void (*setScrollableBarModeOptions)(ArkUINodeHandle node, void* option);
    void (*setOnChange)(ArkUINodeHandle node, void* callback);
    void (*setOnTabBarClick)(ArkUINodeHandle node, void* callback);
    void (*setOnGestureSwipe)(ArkUINodeHandle node, void* callback);
    void (*setOnAnimationStart)(ArkUINodeHandle node, void* callback);
    void (*handleBarWidth)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleBarHeight)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleDividerStrokeWidth)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleDividerColor)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleDividerStartMargin)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleDividerEndMargin)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleScrollableBarMargin)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleBarGridGutter)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleBackgroundBlurStyleInactiveColor)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleBarBackgroundColor)(ArkUINodeHandle node, void* resObjPtr);
    void (*handleBackgroundEffectInactiveColor)(ArkUINodeHandle node, void* resObjPtr);
};

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TABS_CUSTOM_MODIFIER_H
