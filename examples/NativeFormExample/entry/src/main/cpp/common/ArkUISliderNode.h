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

#ifndef MYAPPLICATION_ARKUISLIDERNODE_H
#define MYAPPLICATION_ARKUISLIDERNODE_H

#include "ArkUINode.h"

#include <string>

namespace NativeModule {
class ArkUISliderNode : public ArkUINode {
public:
    ArkUISliderNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_SLIDER)) {}
    // Slider属性接口封装。
    void SetSliderValue(float value)
    {
        ArkUI_NumberValue valueItem[] = {{.f32 = value}};
        ArkUI_AttributeItem item = {.value = valueItem, .size = sizeof(valueItem) / sizeof(ArkUI_NumberValue)};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_VALUE, &item);
    }
    void SetMinValue(float value)
    {
        ArkUI_NumberValue valueItem[] = {{.f32 = value}};
        ArkUI_AttributeItem item = {.value = valueItem, .size = sizeof(valueItem) / sizeof(ArkUI_NumberValue)};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_MIN_VALUE, &item);
    }
    void SetMaxValue(float value)
    {
        ArkUI_NumberValue valueItem[] = {{.f32 = value}};
        ArkUI_AttributeItem item = {.value = valueItem, .size = sizeof(valueItem) / sizeof(ArkUI_NumberValue)};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_MAX_VALUE, &item);
    }
    void SetSliderStep(float value)
    {
        ArkUI_NumberValue valueItem[] = {{.f32 = value}};
        ArkUI_AttributeItem item = {.value = valueItem, .size = sizeof(valueItem) / sizeof(ArkUI_NumberValue)};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_STEP, &item);
    }
    void SetSliderDirection(ArkUI_SliderDirection direction)
    {
        ArkUI_NumberValue value[] = {{.i32 = direction}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_DIRECTION, &item);
    }
    void SetIsReverse(bool isReverse)
    {
        ArkUI_NumberValue value[] = {{.i32 = isReverse ? 1 : 0}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_REVERSE, &item);
    }
    void SetSliderStyle(ArkUI_SliderStyle style)
    {
        ArkUI_NumberValue value[] = {{.i32 = style}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_STYLE, &item);
    }
    void SetBlockColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_BLOCK_COLOR, &item);
    }
    void SetTrackColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_TRACK_COLOR, &item);
    }
    void SetSelectedColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_SELECTED_COLOR, &item);
    }
    void SetTrackThickness(float thickness)
    {
        ArkUI_NumberValue value[] = {{.f32 = thickness}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_TRACK_THICKNESS, &item);
    }
    void SetIsShowSteps(bool isShowSteps)
    {
        ArkUI_NumberValue value[] = {{.i32 = isShowSteps ? 1 : 0}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_SHOW_STEPS, &item);
    }
    void SetImageBlockStyle(const std::string &url)
    {
        ArkUI_NumberValue value[] = {{.i32 = ARKUI_SLIDER_BLOCK_STYLE_IMAGE}};
        ArkUI_AttributeItem item = {value, 1, .string = url.c_str()};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_BLOCK_STYLE, &item);
    }
    void SetEnableHapticFeedback(bool enableHapticFeedback)
    {
        ArkUI_NumberValue value[] = {{.i32 = enableHapticFeedback}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SLIDER_ENABLE_HAPTIC_FEEDBACK, &item);
    }
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUISLIDERNODE_H