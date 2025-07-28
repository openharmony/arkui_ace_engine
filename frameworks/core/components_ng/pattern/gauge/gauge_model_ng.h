/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/pattern/gauge/gauge_model.h"

namespace OHOS::Ace::NG {
class GaugeConfiguration : public CommonConfiguration {
    public:
        GaugeConfiguration(float value, float min, float max, bool enabled)
            : CommonConfiguration(enabled), value_(value), min_(min), max_(max)
        {}
        float value_;
        float min_;
        float max_;
};
using GaugeMakeCallback =
    std::function<RefPtr<FrameNode>(const GaugeConfiguration& gaugeConfiguration)>;
class ACE_EXPORT GaugeModelNG : public OHOS::Ace::GaugeModel {
public:
    void Create(float values, float min, float max) override;
    void SetValue(float value) override;
    void SetStartAngle(float startAngle) override;
    void SetEndAngle(float endAngle) override;
    void SetColors(const std::vector<Color>& colors, const std::vector<float>& values) override;
    void SetGradientColors(
        const std::vector<ColorStopArray>& colors, const std::vector<float>& values, const GaugeType& type) override;
    void SetStrokeWidth(const Dimension& strokeWidth) override;
    void SetLabelMarkedText(const std::string labelTextString) override;
    void SetMarkedTextColor(const Color& color) override;
    void SetDescription(const RefPtr<AceType>& customNode) override;
    void SetIsShowLimitValue(bool isShowLimitValue) override;
    void SetIsShowDescription(bool isShowDescription) override;
    void SetShadowOptions(const GaugeShadowOptions& shadowOptions) override;
    void SetIsShowIndicator(bool isShowIndicator) override;
    void SetIndicatorIconPath(
        const std::string& iconPath, const std::string& bundleName, const std::string& moduleName) override;
    void SetIndicatorSpace(const Dimension& space) override;
    void ResetGradientColors() override;
    void ResetShadowOptions() override;
    void ResetIndicatorIconPath() override;
    void ResetIndicatorSpace() override;
    void CreateWithResourceObj(GaugeResourceType jsResourceType, const RefPtr<ResourceObject>& resObj) override;
    void SetUseGradient(bool useGradient) override;
    void SetUseSpecialDefaultIndicator(bool useSpecialDefaultIndicator) override;
    void SetGradientColorModeInit() override;
    void SetGradientInit(const std::vector<NG::ColorStopArray>& colors) override;

    static void SetValue(FrameNode* frameNode, float value);
    static void SetStartAngle(FrameNode* frameNode, float value);
    static void SetEndAngle(FrameNode* frameNode, float value);
    static void SetGaugeStrokeWidth(FrameNode* frameNode, const Dimension& strokeWidth);
    static void SetShadowOptions(FrameNode* frameNode, const GaugeShadowOptions& shadowOptions);
    static void ResetShadowOptions(FrameNode* frameNode);
    static void SetIsShowIndicator(FrameNode* frameNode, bool isShowIndicator);
    static void SetIndicatorIconPath(FrameNode* frameNode,
        const std::string& iconPath, const std::string& bundleName, const std::string& moduleName);
    static void ResetIndicatorIconPath(FrameNode* frameNode);
    static void SetIndicatorSpace(FrameNode* frameNode, const Dimension& space);
    static void ResetIndicatorSpace(FrameNode* frameNode);
    static void SetColors(FrameNode* frameNode, const std::vector<Color>& colors, const std::vector<float>& values);
    static void SetGradientColors(FrameNode* frameNode, const std::vector<ColorStopArray>& colors,
        const std::vector<float>& values, const GaugeType& type);
    static void ResetGradientColors(FrameNode* frameNode);
    static void SetBuilderFunc(FrameNode* frameNode, NG::GaugeMakeCallback&& jsMake);
    static void SetUseGradient(FrameNode* frameNode, bool useGradient);
    static void CreateWithResourceObj(
        FrameNode* frameNode, GaugeResourceType jsResourceType, const RefPtr<ResourceObject>& resObj);
    static void SetGradientColorModeInit(FrameNode* frameNode);
    static void SetGradientInit(FrameNode* frameNode, const std::vector<NG::ColorStopArray>& colors);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_NG_H