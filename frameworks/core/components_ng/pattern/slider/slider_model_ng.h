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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/slider/slider_event_hub.h"
#include "core/components_ng/pattern/slider/slider_model.h"

namespace OHOS::Ace::NG {
class SliderConfiguration : public CommonConfiguration {
public:
    SliderConfiguration(double value, double min, double max, double step, bool enabled)
        : CommonConfiguration(enabled), value_(value), min_(min), max_(max), step_(step)
    {}
    double value_;
    double min_;
    double max_;
    double step_;
};
using SliderMakeCallback =
    std::function<RefPtr<FrameNode>(const SliderConfiguration& sliderConfiguration)>;
class ACE_EXPORT SliderModelNG : public SliderModel {
public:
    void Create(float value, float step, float min, float max) override;
    void SetSliderMode(const SliderMode& value) override;
    void SetDirection(Axis value) override;
    void SetReverse(bool value) override;
    void SetBlockColor(const Color& value) override;
    void SetTrackBackgroundColor(const Color& value) override {};
    void SetTrackBackgroundColor(const Gradient& value, bool isResourceColor = false) override;
    void SetSelectColor(const Color& value) override;
    void SetMinLabel(float value) override;
    void SetMaxLabel(float value) override;
    void SetShowSteps(bool value) override;
    void SetShowTips(bool value, const std::optional<std::string>& content) override;
    void SetThickness(const Dimension& value) override;
    void SetBlockBorderColor(const Color& value) override;
    void SetBlockBorderWidth(const Dimension& value) override;
    void SetStepColor(const Color& value) override;
    void SetTrackBorderRadius(const Dimension& value) override;
    void SetSelectedBorderRadius(const Dimension& value) override;
    void SetBlockSize(const Dimension& width, const Dimension& height) override;
    void SetBlockType(BlockStyleType value) override;
    void SetBlockImage(const std::string& value, const std::string& bundleName, const std::string& moduleName) override;
    void SetBlockShape(const RefPtr<BasicShape>& value) override;
    void SetStepSize(const Dimension& value) override;
    void SetSliderInteractionMode(SliderInteraction mode) override;
    void SetMinResponsiveDistance(float value) override;
    void SetValidSlideRange(float fromValue, float toValue) override;
#ifdef SUPPORT_DIGITAL_CROWN
    void SetDigitalCrownSensitivity(CrownSensitivity sensitivity) override;
#endif
    void SetOnChange(SliderOnChangeEvent&& eventOnChange) override;
    void SetOnChangeEvent(SliderOnValueChangeEvent&& onChangeEvent) override;

    void ResetBlockBorderColor() override;
    void ResetBlockBorderWidth() override;
    void ResetStepColor() override;
    void ResetTrackBorderRadius() override;
    void ResetSelectedBorderRadius() override;
    void ResetBlockSize() override;
    void ResetBlockType() override;
    void ResetBlockImage() override;
    void ResetBlockShape() override;
    void ResetStepSize() override;
    void ResetSliderInteractionMode() override;
    void ResetMinResponsiveDistance() override;
    void ResetValidSlideRange() override;
#ifdef SUPPORT_DIGITAL_CROWN
    void ResetDigitalCrownSensitivity() override;
#endif

    static void SetShowTips(FrameNode* frameNode, bool value, const std::optional<std::string>& content);
    static void SetThickness(FrameNode* frameNode, const Dimension& value);
    static void SetStepSize(FrameNode* frameNode, const Dimension& value);
    static void SetBlockType(FrameNode* frameNode, BlockStyleType value);
    static void SetBlockShape(FrameNode* frameNode, const RefPtr<BasicShape>& value);
    static void SetBlockSize(FrameNode* frameNode, const Dimension& width, const Dimension& height);
    static void SetTrackBorderRadius(FrameNode* frameNode, const Dimension& value);
    static void SetStepColor(FrameNode* frameNode, const Color& value);
    static void SetBlockBorderColor(FrameNode* frameNode, const Color& value);
    static void SetBlockBorderWidth(FrameNode* frameNode, const Dimension& value);
    static void SetBlockColor(FrameNode* frameNode, const Color& value);
    static void SetTrackBackgroundColor(FrameNode* frameNode, const Gradient& value, bool isResourceColor = false);
    static void SetSelectColor(FrameNode* frameNode, const Color& value);
    static void SetShowSteps(FrameNode* frameNode, bool value);
    static void SetSliderInteractionMode(FrameNode* frameNode, SliderInteraction mode);
    static void SetMinResponsiveDistance(FrameNode* frameNode, float value);
    static void SetValidSlideRange(FrameNode* frameNode, float fromValue, float toValue);
    static void SetBlockImage(
        FrameNode* frameNode, const std::string& value, const std::string& bundleName, const std::string& moduleName);
    static void SetSelectedBorderRadius(FrameNode* frameNode, const Dimension& value);
#ifdef SUPPORT_DIGITAL_CROWN
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, CrownSensitivity sensitivity);
#endif

    static void ResetBlockBorderColor(FrameNode* frameNode);
    static void ResetBlockBorderWidth(FrameNode* frameNode);
    static void ResetStepColor(FrameNode* frameNode);
    static void ResetTrackBorderRadius(FrameNode* frameNode);
    static void ResetBlockSize(FrameNode* frameNode);
    static void ResetBlockType(FrameNode* frameNode);
    static void ResetBlockImage(FrameNode* frameNode);
    static void ResetBlockShape(FrameNode* frameNode);
    static void ResetStepSize(FrameNode* frameNode);
    static void ResetBlockColor(FrameNode* frameNode);
    static void ResetValidSlideRange(FrameNode* frameNode);
    static void ResetSelectedBorderRadius(FrameNode* frameNode);
    static void ResetSliderInteractionMode(FrameNode* frameNode);
    static void ResetMinResponsiveDistance(FrameNode* frameNode);
#ifdef SUPPORT_DIGITAL_CROWN
    static void ResetDigitalCrownSensitivity(FrameNode* frameNode);
#endif

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetOnChange(FrameNode* frameNode, SliderOnChangeEvent&& eventOnChange);
    static void SetSliderValue(FrameNode* frameNode, float value);
    static void SetMinLabel(FrameNode* frameNode, float value);
    static void SetMaxLabel(FrameNode* frameNode, float value);
    static void SetDirection(FrameNode* frameNode, Axis value);
    static void SetStep(FrameNode* frameNode, float value);
    static void SetReverse(FrameNode* frameNode, bool value);
    static void SetSliderMode(FrameNode* frameNode, const SliderMode& value);

    static Color GetBlockColor(FrameNode* frameNode);
    static Gradient GetTrackBackgroundColor(FrameNode* frameNode);
    static Color GetSelectColor(FrameNode* frameNode);
    static bool GetShowSteps(FrameNode* frameNode);
    static BlockStyleType GetBlockType(FrameNode* frameNode);
    static float GetSliderValue(FrameNode* frameNode);
    static float GetMinLabel(FrameNode* frameNode);
    static float GetMaxLabel(FrameNode* frameNode);
    static OHOS::Ace::Axis GetDirection(FrameNode* frameNode);
    static float GetStep(FrameNode* frameNode);
    static bool GetReverse(FrameNode* frameNode);
    static SliderModel::SliderMode GetSliderMode(FrameNode* frameNode);
    static std::string GetBlockImageValue(FrameNode* frameNode);
    static RefPtr<BasicShape> GetBlockShape(FrameNode* frameNode);
    static Gradient CreateSolidGradient(Color value);
    static void SetBuilderFunc(FrameNode* frameNode, SliderMakeCallback&& jsMake);
    static void SetChangeValue(FrameNode* frameNode, double value, int32_t mode);
    static Dimension GetThickness(FrameNode* frameNode);
    static RefPtr<SliderModel::SliderValidRange> GetValidSlideRange(FrameNode* frameNode);
#ifdef SUPPORT_DIGITAL_CROWN
    static CrownSensitivity GetDigitalCrownSensitivity(FrameNode* frameNode);
#endif

private:
    void SetSliderValue(float value);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SLIDER_SLIDER_MODEL_NG_H
