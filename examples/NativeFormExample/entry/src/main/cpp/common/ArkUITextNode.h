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

#ifndef MYAPPLICATION_ARKUITEXTNODE_H
#define MYAPPLICATION_ARKUITEXTNODE_H

#include "ArkUINode.h"

#include <string>

namespace NativeModule {
class ArkUITextNode : public ArkUINode {
public:
    ArkUITextNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_TEXT)) {}
    // 文本属性接口封装。
    void SetFontSize(float fontSize)
    {
        ArkUI_NumberValue value[] = {{.f32 = fontSize}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_FONT_SIZE, &item);
    }
    void SetFontColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_FONT_COLOR, &item);
    }
    void SetTextContent(const std::string &content)
    {
        ArkUI_AttributeItem item = {nullptr, 0, content.c_str()};
        nativeModule_->setAttribute(handle_, NODE_TEXT_CONTENT, &item);
    }
    void SetTextAlign(ArkUI_TextAlignment align)
    {
        ArkUI_NumberValue value[] = {{.i32 = align}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_TEXT_ALIGN, &item);
    }
    
    void AnimatorToString(
        int duration = 0, int delay = 0, int iterations = 0,
        ArkUI_AnimationFillMode fill = ARKUI_ANIMATION_FILL_MODE_FORWARDS,
        ArkUI_AnimationDirection direction = ARKUI_ANIMATION_DIRECTION_REVERSE, float begin = 0.0, float end = 0.0,
        const ArkUI_ExpectedFrameRateRange& expectedFrameRateRange = { 0, 0, 0 },
        float keyframeTime = 0.0, float keyframeValue = 0.0)
    {
        SetTextContent("Animator{ dur:" + std::to_string(duration)
            + ";  delay:" + std::to_string(delay)
            + ";  iterations:" + std::to_string(iterations)
            + ";  fill:" + std::to_string(fill)
            + ";  direction:" + std::to_string(direction)
            + ";  begin:" + std::to_string(begin)
            + ";  end:" + std::to_string(end)
            + ";  expectedFrameRateRange:[ max:" +
            std::to_string(expectedFrameRateRange.max) + ", min:" +
            std::to_string(expectedFrameRateRange.min) + ", expected:" +
            std::to_string(expectedFrameRateRange.expected) + "]"
            + ";  keyframeTime:" + std::to_string(keyframeTime)
            + ";  keyframeValue:" + std::to_string(keyframeValue)
            + "}");
    }
    
    void AnimatetoToString(
        int duration = 0, float tempo = 0, int curve = 0, int delay = 0,
        int iteration = 0, ArkUI_AnimationPlayMode playmode = ARKUI_ANIMATION_PLAY_MODE_REVERSE,
        const ArkUI_ExpectedFrameRateRange& expectedFrameRateRange = { 0, 0, 0 })
    {
        SetTextContent("animateto{ dur:" + std::to_string(duration)
            + ";  tempo:" + std::to_string(tempo)
            + ";  curve:" + std::to_string(static_cast<int>(curve))
            + ";  delay:" + std::to_string(delay)
            + ";  iteration:" + std::to_string(iteration)
            + ";  playmode:" + std::to_string(static_cast<int>(playmode))
            + ";  expectedFrameRateRange:[ max:" +
            std::to_string(expectedFrameRateRange.max) + ", min:" +
            std::to_string(expectedFrameRateRange.min) + ", expected:" +
            std::to_string(expectedFrameRateRange.expected) + "]}");
    }
    
    void KeyframeAnimatetoToString(
        int durationIndex1 = 0, int durationIndex2 = 0, int delay = 0,
        int iteration = 0,
        const ArkUI_ExpectedFrameRateRange& expectedFrameRateRange = { 0, 0, 0 })
    {
        SetTextContent("KeyframeAnimateto{ dur index:" + std::to_string(durationIndex1)
            + ";  delay:" + std::to_string(delay)
            + ";  iteration:" + std::to_string(iteration)
            + ";  expectedFrameRateRange:[ max:" +
            std::to_string(expectedFrameRateRange.max) + ", min:" +
            std::to_string(expectedFrameRateRange.min) + ", expected:" +
            std::to_string(expectedFrameRateRange.expected) + "]}");
    }
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUITEXTNODE_H