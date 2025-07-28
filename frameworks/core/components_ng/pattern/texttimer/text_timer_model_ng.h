/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/texttimer/text_timer_model.h"

namespace OHOS::Ace::NG {
class TextTimerConfiguration : public CommonConfiguration {
    public:
        TextTimerConfiguration(double count, bool isCountDown, bool started, int64_t elapsedTime, bool enabled)
            : CommonConfiguration(enabled),
            count_(count),
            isCountDown_(isCountDown),
            started_(started),
            elapsedTime_(elapsedTime)
        {}
        double count_ = 60000.0;
        bool isCountDown_ = false;
        bool started_ = false;
        uint64_t elapsedTime_ = 0;
};
using TextTimerMakeCallback =
    std::function<RefPtr<FrameNode>(const TextTimerConfiguration& textTimerConfiguration)>;
class ACE_EXPORT TextTimerModelNG : public OHOS::Ace::TextTimerModel {
public:
    RefPtr<TextTimerController> Create() override;
    void SetFormat(const std::string& format) override;
    void SetIsCountDown(bool isCountDown) override;
    void SetInputCount(double count) override;
    void SetOnTimer(std::function<void(int64_t, int64_t)> && onChange) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void SetTextColorByUser(bool isSetByUser) override;
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void CreateWithResourceObj(JsTextTimerResourceType jsResourceType, const RefPtr<ResourceObject>& resObj) override;
    void SetFontSizeByUser(bool value) override;
    void SetFontWeightByUser(bool value) override;
    void SetFontFamilyByUser(bool value) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<TextTimerController> InitTextController(FrameNode* frameNode);
    static void SetIsCountDown(FrameNode* frameNode, bool isCountDown);
    static void SetInputCount(FrameNode* frameNode, double count);
    static void SetFontColor(FrameNode* frameNode, const Color& value);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontStyle(FrameNode* frameNode, Ace::FontStyle value);
    static void SetFontWeight(FrameNode* frameNode, FontWeight value);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetFormat(FrameNode* frameNode, const std::string& format);
    static void SetTextShadow(FrameNode* frameNode, const std::vector<Shadow>& value);
    static void SetBuilderFunc(FrameNode* frameNode, TextTimerMakeCallback&& jsMake);
    static void SetJSTextTimerController(FrameNode* frameNode, const RefPtr<Referenced>& controller);
    static void SetOnTimer(FrameNode* frameNode, std::function<void(int64_t, int64_t)>&& onChange);
    static RefPtr<Referenced> GetJSTextTimerController(FrameNode* frameNode);
    static void HandleTextColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void HandleFontWeight(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void HandleFontSize(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void HandleFontFamily(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void CreateWithResourceObj(
        FrameNode* frameNode, JsTextTimerResourceType jsResourceType, const RefPtr<ResourceObject>& resObj);
    static void SetTextColorByUser(FrameNode* frameNode, bool isSetByUser);
    static void SetFontSizeByUser(FrameNode* frameNode, bool value);
    static void SetFontWeightByUser(FrameNode* frameNode, bool value);
    static void SetFontFamilyByUser(FrameNode* frameNode, bool value);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TIMER_MODEL_NG_H
