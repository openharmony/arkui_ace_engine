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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/toggle/toggle_model.h"

namespace OHOS::Ace::NG {

class ToggleConfiguration : public CommonConfiguration {
    public:
        ToggleConfiguration(bool enabled, bool isOn)
            : CommonConfiguration(enabled), isOn_(isOn)
        {}
        bool isOn_;
};
class ArkUI_Toggle_Params final : public ArkUI_Params {
public:
    ToggleType toggleType;
    bool isOn;
};
using SwitchMakeCallback = std::function<RefPtr<FrameNode>(const ToggleConfiguration& toggleConfiguration)>;
class ACE_EXPORT ToggleModelNG : public OHOS::Ace::ToggleModel {
public:
    void Create(ToggleType toggleType, bool isOn) override;
    void SetSelectedColor(const std::optional<Color>& selectedColor) override;
    void SetSwitchPointColor(const Color& switchPointColor) override;
    void OnChange(ChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetBackgroundColor(const Color& color, bool flag) override;
    bool IsToggle() override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs) override;
    void OnChangeEvent(ChangeEvent&& onChangeEvent) override;
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;
    void SetHoverEffect(HoverEffectType hoverEffect) override;
    void Pop() override;
    void SetPointRadius(const Dimension& switchPointRadius) override;
    void ResetPointRadius() override;
    void SetUnselectedColor(const Color& unselectedColor) override;
    void SetTrackBorderRadius(const Dimension& borderRadius) override;
    void ResetTrackBorderRadius() override;
    static void SetPointRadius(FrameNode* frameNode, const Dimension& switchPointRadius);
    static void ResetPointRadius(FrameNode* frameNode);
    static void SetUnselectedColor(FrameNode* frameNode, const Color& unselectedColor);
    static void SetTrackBorderRadius(FrameNode* frameNode, const Dimension& borderRadius);
    static void ResetTrackBorderRadius(FrameNode* frameNode);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, ToggleType toggleType, bool isOn);
    static void SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor);
    static void SetSwitchPointColor(FrameNode* frameNode, const Color& switchPointColor);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& color);
    static void OnChange(FrameNode* frameNode, ChangeEvent&& onChange);
    static void SetHeight(FrameNode* frameNode, const Dimension& height);
    static void SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion);
    static void SetPadding(FrameNode* frameNode, const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs);
    static void SetHoverEffect(FrameNode* frameNode, HoverEffectType hoverEffect);
    static void SetSwitchIsOn(FrameNode* frameNode, bool isOn);
    static void SetBuilderFunc(FrameNode* frameNode, NG::SwitchMakeCallback&& jsMake);
    static void SetChangeValue(FrameNode* frameNode, bool value);
    static void SetToggleState(FrameNode* frameNode, bool isOn = false);

    static Color GetSelectedColor(FrameNode* frameNode);
    static Color GetSwitchPointColor(FrameNode* frameNode);
    static bool GetSwitchIsOn(FrameNode* frameNode);
    static Color GetUnselectedColor(FrameNode* frameNode);

private:
    static void ReCreateFrameNode(
        const RefPtr<FrameNode>& childFrameNode, int32_t nodeId, ToggleType toggleType, bool isOn);
    static RefPtr<FrameNode> CreateCheckboxFrameNode(int32_t nodeId, bool isOn);
    static RefPtr<FrameNode> CreateSwitchFrameNode(int32_t nodeId, bool isOn);
    static RefPtr<FrameNode> CreateButtonFrameNode(int32_t nodeId, bool isOn);
    static void AddNewChild(const RefPtr<UINode>& parentFrame, int32_t nodeId, int32_t index, ToggleType toggleType);
    static int32_t RemoveNode(const RefPtr<FrameNode>& childFrameNode, int32_t nodeId);
    static void UpdateSwitchIsOn(const RefPtr<FrameNode>& frameNode, bool isOn);
    static void UpdateCheckboxIsOn(const RefPtr<FrameNode>& frameNode, bool isOn);
    static void UpdateToggleButtonIsOn(const RefPtr<FrameNode>& frameNode, bool isOn);
    static void ReplaceAllChild(const RefPtr<FrameNode>& oldFrameNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TOGGLE_TOGGLE_MODEL_NG_H
