/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"

namespace OHOS::Ace::NG {
class TextClockConfiguration : public CommonConfiguration {
public:
    TextClockConfiguration(float timeZoneOffset, bool started, int64_t timeValue, bool enabled)
        : CommonConfiguration(enabled), timeZoneOffset_(timeZoneOffset), started_(started), timeValue_(timeValue)
    {}
    float timeZoneOffset_;
    bool started_;
    int64_t timeValue_;
};
using TextClockMakeCallback = std::function<RefPtr<FrameNode>(const TextClockConfiguration& textClockConfiguration)>;
class ACE_EXPORT TextClockModelNG : public OHOS::Ace::TextClockModel {
public:
    RefPtr<TextClockController> Create() override;
    void SetFormat(const std::string& format) override;
    void SetHoursWest(float hoursWest) override;
    void SetOnDateChange(std::function<void(const std::string)>&& onChange) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void ResetTextColor() override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetFontFeature(const FONT_FEATURES_LIST& value) override;
    void InitFontDefault(const TextStyle& textStyle) override;
    void SetDateTimeOptions(const ZeroPrefixType& hourType) override;
    void CreateWithTextColorResourceObj(const RefPtr<ResourceObject>& resObj) override;
    void CreateWithFontSizeResourceObj(const RefPtr<ResourceObject>& resObj) override;
    void CreateWithFontFamilyResourceObj(const RefPtr<ResourceObject>& resObj) override;
    void CreateWithFontWeightResourceObj(const RefPtr<ResourceObject>& resObj) override;
    void CreateWithFormatResourceObj(const RefPtr<ResourceObject>& resObj) override;
    void RemoveResObjByKey(const std::string& key) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<TextClockController> InitTextController(FrameNode* frameNode);
    static void SetFormat(FrameNode* frameNode, const std::string& format);
    static void SetHoursWest(FrameNode* frameNode, float hoursWest);
    static void SetFontColor(FrameNode* frameNode, const Color& value);
    static void SetFontColorByUser(FrameNode* frameNode, bool isSetByUser);
    static void ResetFontColor(FrameNode* frameNode);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& size);
    static void SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& value);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<Ace::FontWeight>& value);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetTextShadow(FrameNode* frameNode, const std::vector<Shadow>& value);
    static void SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value);
    static void SetBuilderFunc(FrameNode* frameNode, TextClockMakeCallback&& jsMake);
    static void InitFontDefault(FrameNode* frameNode, const TextStyle& textStyle);
    static void SetDateTimeOptions(FrameNode* frameNode, const std::optional<ZeroPrefixType>& hourType);
    static void SetJSTextClockController(FrameNode* frameNode, const RefPtr<Referenced>& controller);
    static RefPtr<Referenced> GetJSTextClockController(FrameNode* frameNode);
    static void SetOnDateChange(FrameNode* frameNode, std::function<void(const std::string)>&& onChange);
    static void CreateWithTextColorResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void CreateWithFontSizeResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void CreateWithFontFamilyResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void CreateWithFontWeightResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void CreateWithFormatResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_NG_H
