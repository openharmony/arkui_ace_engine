/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "components/swiper/Swiper.h"

namespace ArkUICApiDemo {

void SwiperComponent::SetSwiperLoop(int32_t loop)
{
    ArkUI_NumberValue value[] = { { .i32 = loop } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_LOOP, &item);
}

void SwiperComponent::SetSwiperAutoPlay(int32_t status)
{
    ArkUI_NumberValue value[] = { { .i32 = status } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_AUTO_PLAY, &item);
}

void SwiperComponent::SetSwiperPrevMigration(float migration, int32_t ignoreBlank)
{
    ArkUI_NumberValue value[] = { { .f32 = migration }, { .i32 = ignoreBlank } };
    ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_PREV_MARGIN, &item);
}

void SwiperComponent::SetSwiperNextMigration(float migration, int32_t ignoreBlank)
{
    ArkUI_NumberValue value[] = { { .f32 = migration }, { .i32 = ignoreBlank } };
    ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_NEXT_MARGIN, &item);
}

void SwiperComponent::SetSwiperDisplayCount(int32_t count)
{
    ArkUI_NumberValue value[] = { { .i32 = count } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_DISPLAY_COUNT, &item);
}

void SwiperComponent::SetSwiperIndex(int32_t index)
{
    ArkUI_NumberValue value[] = { { .i32 = index } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_INDEX, &item);
}

void SwiperComponent::SetSwiperVertical(int32_t vertical)
{
    ArkUI_NumberValue value[] = { { .i32 = vertical } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_VERTICAL, &item);
}

void SwiperComponent::SetSwiperEffectMode(int32_t effect)
{
    ArkUI_NumberValue value[] = { { .i32 = effect } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_EDGE_EFFECT_MODE, &item);
}

void SwiperComponent::SetSwiperNestedScroll(int32_t nestedScroll)
{
    ArkUI_NumberValue value[] = { { .i32 = nestedScroll } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_NESTED_SCROLL, &item);
}

void SwiperComponent::SetSwiperInterval(float interval)
{
    ArkUI_NumberValue value[] = { { .f32 = interval } };
    ArkUI_AttributeItem item = { value, sizeof(value) / sizeof(ArkUI_NumberValue) };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_INTERVAL, &item);
}

void SwiperComponent::SetSwiperDirection(int32_t direction)
{
    ArkUI_NumberValue value[] = { { .i32 = direction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_DIRECTION, &item);
}

void SwiperComponent::SetSwiperIndicator(ArkUI_SwiperIndicator* indicator)
{
    ArkUI_NumberValue indicator_value[] = { { .i32 = ARKUI_SWIPER_INDICATOR_TYPE_DOT } };
    ArkUI_AttributeItem indicator_item = { indicator_value, sizeof(indicator_value) / sizeof(ArkUI_NumberValue), "",
        indicator };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_INDICATOR, &indicator_item);
}

void SwiperComponent::SetSwiperToIndex(int32_t index, int32_t useAnimation)
{
    ArkUI_NumberValue value[] = { { .i32 = index }, { .i32 = useAnimation } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_SWIPE_TO_INDEX, &item);
}

void SwiperComponent::SetSwiperDuration(float duration)
{
    ArkUI_NumberValue value[] = { { .f32 = duration } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SWIPER_DURATION, &item);
}

void SwiperComponent::RegisterOnGesture(const std::function<void(ArkUI_NodeEvent* event)>& onGesture)
{
    onGesture_ = onGesture;
    _nodeAPI->registerNodeEvent(_component, NODE_SWIPER_EVENT_ON_GESTURE_SWIPE, 0, nullptr);
}

void SwiperComponent::RegisterOnChange(const std::function<void(ArkUI_NodeEvent* event)>& onChange)
{
    onChange_ = onChange;
    _nodeAPI->registerNodeEvent(_component, NODE_SWIPER_EVENT_ON_CHANGE, 0, nullptr);
}

void SwiperComponent::RegisterOnDidScrollContext(const std::function<void(ArkUI_NodeEvent* event)>& onDid)
{
    onDid_ = onDid;
    _nodeAPI->registerNodeEvent(_component, NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL, 0, nullptr);
}

void SwiperComponent::RegisterOnAnimationStart(const std::function<void(ArkUI_NodeEvent* event)>& onStart)
{
    onStart_ = onStart;
    _nodeAPI->registerNodeEvent(_component, NODE_SWIPER_EVENT_ON_ANIMATION_START, 0, nullptr);
}

void SwiperComponent::RegisterOnAnimationEnd(const std::function<void(ArkUI_NodeEvent* event)>& onEnd)
{
    onEnd_ = onEnd;
    _nodeAPI->registerNodeEvent(_component, NODE_SWIPER_EVENT_ON_ANIMATION_END, 0, nullptr);
}

void SwiperComponent::OnNodeEvent(ArkUI_NodeEvent* event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    switch (eventType) {
        case NODE_SWIPER_EVENT_ON_GESTURE_SWIPE:
            if (onGesture_) {
                onGesture_(event);
            }
            break;
        case NODE_SWIPER_EVENT_ON_CHANGE:
            if (onChange_) {
                onChange_(event);
            }
            break;
        case NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL:
            if (onDid_) {
                onDid_(event);
            }
            break;
        case NODE_SWIPER_EVENT_ON_ANIMATION_START:
            if (onStart_) {
                onStart_(event);
            }
            break;
        case NODE_SWIPER_EVENT_ON_ANIMATION_END:
            if (onEnd_) {
                onEnd_(event);
            }
            break;
        default:
            break;
    }
}
} // namespace ArkUICApiDemo