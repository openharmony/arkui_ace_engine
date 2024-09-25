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

#include <optional>

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"

#include "reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
// Reverse-convert Ark_TextDeleteDirection
void AssignArkValue(Ark_TextDeleteDirection& dst, const TextDeleteDirection& src)
{
    switch (src) {
        case TextDeleteDirection::BACKWARD: dst = ARK_TEXT_DELETE_DIRECTION_BACKWARD; break;
        case TextDeleteDirection::FORWARD: dst = ARK_TEXT_DELETE_DIRECTION_FORWARD; break;
        default: dst = static_cast<Ark_TextDeleteDirection>(-1);
    }
}

void AssignArkValue(Ark_EnterKeyType& dst, const TextInputAction& src)
{
    switch (src) {
        case TextInputAction::GO: dst = ARK_ENTER_KEY_TYPE_GO; break;
        case TextInputAction::SEARCH: dst = ARK_ENTER_KEY_TYPE_SEARCH; break;
        case TextInputAction::SEND: dst = ARK_ENTER_KEY_TYPE_SEND; break;
        case TextInputAction::NEXT: dst = ARK_ENTER_KEY_TYPE_NEXT; break;
        case TextInputAction::DONE: dst = ARK_ENTER_KEY_TYPE_DONE; break;
        case TextInputAction::PREVIOUS: dst = ARK_ENTER_KEY_TYPE_PREVIOUS; break;
        case TextInputAction::NEW_LINE: dst = ARK_ENTER_KEY_TYPE_NEW_LINE; break;
        default:
            LOGE("Unexpected enum value in TextInputAction: %{public}d", src);
            dst = static_cast<Ark_EnterKeyType>(-1);
    }
}

void AssignArkValue(Ark_SharedTransitionEffectType& dst, const SharedTransitionEffectType& src)
{
    switch (src) {
        case SharedTransitionEffectType::SHARED_EFFECT_STATIC:
            dst = ARK_SHARED_TRANSITION_EFFECT_TYPE_STATIC; break;
        case SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE:
            dst = ARK_SHARED_TRANSITION_EFFECT_TYPE_EXCHANGE; break;
        default: dst = static_cast<Ark_SharedTransitionEffectType>(-1);
    }
}

// Reverse-convert Ark_AnimationMode
void AssignArkValue(Ark_AnimationMode& dst, const TabAnimateMode& src)
{
    switch (src) {
        case TabAnimateMode::CONTENT_FIRST: dst = ARK_ANIMATION_MODE_CONTENT_FIRST; break;
        case TabAnimateMode::ACTION_FIRST: dst = ARK_ANIMATION_MODE_ACTION_FIRST; break;
        case TabAnimateMode::NO_ANIMATION: dst = ARK_ANIMATION_MODE_NO_ANIMATION; break;
        default:
            dst = static_cast<Ark_AnimationMode>(-1);
            LOGE("Unexpected enum value in TabAnimateMode: %{public}d", src);
            break;
    }
}

// Reverse-convert Ark_BarPosition
void AssignArkValue(Ark_BarPosition& dst, const BarPosition& src)
{
    switch (src) {
        case BarPosition::START: dst = ARK_BAR_POSITION_START; break;
        case BarPosition::END: dst = ARK_BAR_POSITION_END; break;
        default:
            dst = static_cast<Ark_BarPosition>(-1);
            LOGE("Unexpected enum value in BarPosition: %{public}d", src);
            break;
    }
}

// Reverse-convert Ark_BarMode
void AssignArkValue(Ark_BarMode& dst, const TabBarMode& src)
{
    switch (src) {
        case TabBarMode::SCROLLABLE: dst = ARK_BAR_MODE_SCROLLABLE; break;
        case TabBarMode::FIXED: dst = ARK_BAR_MODE_FIXED; break;
        default:
            dst = static_cast<Ark_BarMode>(-1);
            LOGE("Unexpected enum value in TabBarMode: %{public}d", src);
            break;
    }
}

// Reverse-convert Ark_BlurStyle
void AssignArkValue(Ark_BlurStyle& dst, const BlurStyle& src)
{
    switch (src) {
        case BlurStyle::THIN: dst = ARK_BLUR_STYLE_THIN; break;
        case BlurStyle::REGULAR: dst = ARK_BLUR_STYLE_REGULAR; break;
        case BlurStyle::THICK: dst = ARK_BLUR_STYLE_THICK; break;
        case BlurStyle::BACKGROUND_THIN: dst = ARK_BLUR_STYLE_BACKGROUND_THIN; break;
        case BlurStyle::BACKGROUND_REGULAR: dst = ARK_BLUR_STYLE_BACKGROUND_REGULAR; break;
        case BlurStyle::BACKGROUND_THICK: dst = ARK_BLUR_STYLE_BACKGROUND_THICK; break;
        case BlurStyle::BACKGROUND_ULTRA_THICK: dst = ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK; break;
        case BlurStyle::NO_MATERIAL: dst = ARK_BLUR_STYLE_NONE; break;
        case BlurStyle::COMPONENT_ULTRA_THIN: dst = ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN; break;
        case BlurStyle::COMPONENT_THIN: dst = ARK_BLUR_STYLE_COMPONENT_THIN; break;
        case BlurStyle::COMPONENT_REGULAR: dst = ARK_BLUR_STYLE_COMPONENT_REGULAR; break;
        case BlurStyle::COMPONENT_THICK: dst = ARK_BLUR_STYLE_COMPONENT_THICK; break;
        case BlurStyle::COMPONENT_ULTRA_THICK: dst = ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK; break;
        default:
            dst = static_cast<Ark_BlurStyle>(-1);
            LOGE("Unexpected enum value in BlurStyle: %{public}d", src);
            break;
    }
}

void AssignArkValue(Ark_SwipeEdgeEffect& dst, const V2::SwipeEdgeEffect& src)
{
    switch (src) {
        case V2::SwipeEdgeEffect::Spring: dst = ARK_SWIPE_EDGE_EFFECT_SPRING; break;
        case V2::SwipeEdgeEffect::None: dst = ARK_SWIPE_EDGE_EFFECT_NONE; break;
        default: dst = static_cast<Ark_SwipeEdgeEffect>(-1);
            LOGE("Unexpected enum value in V2::SwipeEdgeEffect: %{public}d", src);
    }
}
} // namespace OHOS::Ace::NG::Converter