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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_CUSTOM_MODIFIER_H

#include "core/interfaces/arkoala/arkoala_api.h"

struct ArkUISwiperCustomModifier {
    ArkUINodeHandle (*createFrameNode)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*createArcFrameNode)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*createArcFrameNodeNG)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*getSwiperController)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCurrentIndex)(ArkUINodeHandle node, ArkUI_Bool original);
    ArkUI_Int32 (*getTotalCount)(ArkUINodeHandle node);
    ArkUI_Int32 (*getDirection)(ArkUINodeHandle node);
    ArkUI_Bool (*isAtStart)(ArkUINodeHandle node);
    ArkUI_Bool (*isAtEnd)(ArkUINodeHandle node);
    void (*setIndex)(ArkUINodeHandle node, ArkUI_Uint32 index);
    void (*setIndexNG)(ArkUINodeHandle node, ArkUI_Uint32 index);
    void (*setDuration)(ArkUINodeHandle node, ArkUI_Uint32 duration);
    void (*setDurationNG)(ArkUINodeHandle node, ArkUI_Uint32 duration);
    void (*setDirection)(ArkUINodeHandle node, ArkUI_Int32 axis);
    void (*setDirectionNG)(ArkUINodeHandle node, ArkUI_Int32 axis);
    void (*setDisableSwipe)(ArkUINodeHandle node, ArkUI_Bool disableSwipe);
    void (*setDisableSwipeNG)(ArkUINodeHandle node, ArkUI_Bool disableSwipe);
    void (*setDigitalCrownSensitivity)(ArkUINodeHandle node, ArkUI_Int32 sensitivity);
    void (*setDigitalCrownSensitivityNG)(ArkUINodeHandle node, ArkUI_Int32 sensitivity);
    void (*setOnChange)(ArkUINodeHandle node, void* callback);
    void (*setOnChangeNG)(ArkUINodeHandle node, void* callback);
    void (*setOnAnimationStart)(ArkUINodeHandle node, void* callback);
    void (*setOnAnimationStartNG)(ArkUINodeHandle node, void* callback);
    void (*setOnAnimationEnd)(ArkUINodeHandle node, void* callback);
    void (*setOnAnimationEndNG)(ArkUINodeHandle node, void* callback);
    void (*setOnGestureSwipe)(ArkUINodeHandle node, void* callback);
    void (*setOnGestureSwipeNG)(ArkUINodeHandle node, void* callback);
    void (*setEdgeEffect)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect);
    void (*setEdgeEffectNG)(ArkUINodeHandle node, ArkUI_Int32 edgeEffect);
    void (*setCustomContentTransition)(ArkUINodeHandle node, void* transition);
    void (*setCustomContentTransitionNG)(ArkUINodeHandle node, void* transition);
    void (*setDisableTransitionAnimation)(ArkUINodeHandle node, ArkUI_Bool isDisable);
    void (*setDisableTransitionAnimationNG)(ArkUINodeHandle node, ArkUI_Bool isDisable);
    void (*setIndicatorType)(ArkUINodeHandle node, ArkUI_Int32 indicatorType);
    void (*setIndicatorTypeNG)(ArkUINodeHandle node, ArkUI_Int32 indicatorType);
    void (*setIndicatorIsBoolean)(ArkUINodeHandle node, ArkUI_Bool isBoolean);
    void (*setIndicatorIsBooleanNG)(ArkUINodeHandle node, ArkUI_Bool isBoolean);
    void (*setShowIndicator)(ArkUINodeHandle node, ArkUI_Bool showIndicator);
    void (*setShowIndicatorNG)(ArkUINodeHandle node, ArkUI_Bool showIndicator);
    void (*setArcDotIndicatorStyle)(ArkUINodeHandle node, void* swiperArcDotParameters);
    void (*setArcDotIndicatorStyleNG)(ArkUINodeHandle node, void* swiperArcDotParameters);
    ArkUINodeHandle (*createCalendarSwiperNode)(ArkUI_Int32 nodeId);
    ArkUINodeHandle (*createStepperSwiperNode)(ArkUI_Int32 nodeId, ArkUI_Uint32 index);
    void (*swipeTo)(ArkUINodeHandle node, ArkUI_Int32 index);
    ArkUI_Bool (*isAnimationStopped)(ArkUINodeHandle node);
    void (*setCurveLinear)(ArkUINodeHandle node);
    ArkUI_Int32 (*getCurrentShownIndex)(ArkUINodeHandle node);
};

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_CUSTOM_MODIFIER_H
