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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODEL_NG_H

#include "core/components_ng/base/common_configuration.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/checkbox/checkbox_model.h"

namespace OHOS::Ace::NG {
class CheckBoxConfiguration : public CommonConfiguration {
    public:
        CheckBoxConfiguration(const std::string& name, bool selected, bool enabled)
            : CommonConfiguration(enabled), name_(name), selected_(selected)
        {}
        std::string name_;
        bool selected_;
};
using CheckBoxMakeCallback =
    std::function<RefPtr<FrameNode>(const CheckBoxConfiguration& checkBoxConfiguration)>;
class ACE_EXPORT CheckBoxModelNG : public OHOS::Ace::CheckBoxModel {
public:
    void Create(const std::optional<std::string>& name, const std::optional<std::string>& groupName,
        const std::string& tagName) override;
    void SetSelect(bool isSelected) override;
    void SetSelectedColor(const Color& color) override;
    void SetUnSelectedColor(const Color& color) override;
    void SetBuilder(std::optional<std::function<void(void)>>& buildFunc) override;
    void SetCheckMarkColor(const Color& color) override;
    void SetCheckMarkSize(const Dimension& size) override;
    void SetCheckMarkWidth(const Dimension& width) override;
    void SetOnChange(ChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag) override;
    void SetIsUserSetMargin(bool isUserSet) override;
    void SetChangeEvent(ChangeEvent&& changeEvent) override;
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;
    void SetCheckboxStyle(CheckBoxStyle checkboxStyle) override;
    void ResetSelectedColor() override;
    void ResetUnSelectedColor() override;
    void ResetCheckMarkColor() override;
    void CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj,
        const CheckBoxColorType checkBoxColorType) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSelect(FrameNode* frameNode, bool isSelected);
    static void SetSelectedColor(FrameNode* frameNode, const Color& color);
    static void SetSelectedColorFlagByUser(FrameNode* frameNode, const bool isByUser);
    static void SetUnSelectedColor(FrameNode* frameNode, const Color& color);
    static void SetWidth(FrameNode* frameNode, const Dimension& width);
    static void SetHeight(FrameNode* frameNode, const Dimension& height);
    static void SetCheckMarkColor(FrameNode* frameNode, const Color& color);
    static void SetCheckMarkSize(FrameNode* frameNode, const Dimension& size);
    static void SetCheckMarkWidth(FrameNode* frameNode, const Dimension& width);
    static void SetPadding(FrameNode* frameNode, const NG::PaddingProperty& padding);
    static void SetIsUserSetMargin(FrameNode* frameNode, bool isUserSet);
    static void SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion);
    static void SetBuilderFunc(FrameNode* frameNode, NG::CheckBoxMakeCallback&& jsMake);
    static void SetChangeValue(FrameNode* frameNode, bool value);
    static void SetCheckboxStyle(FrameNode* frameNode, CheckBoxStyle checkboxStyle);
    static void SetCheckboxName(FrameNode* frameNode, const std::optional<std::string>& name);
    static void SetCheckboxGroup(FrameNode* frameNode, const std::optional<std::string>& groupName);
    static void ResetSelectedColor(FrameNode* frameNode);
    static void ResetUnSelectedColor(FrameNode* frameNode);
    static void ResetCheckMarkColor(FrameNode* frameNode);

    static bool GetSelect(FrameNode* frameNode);
    static Color GetSelectedColor(FrameNode* frameNode);
    static Color GetUnSelectedColor(FrameNode* frameNode);
    static Color GetCheckMarkColor(FrameNode* frameNode);
    static Dimension GetCheckMarkSize(FrameNode* frameNode);
    static Dimension GetCheckMarkWidth(FrameNode* frameNode);
    static CheckBoxStyle GetCheckboxStyle(FrameNode* frameNode);
    static std::string GetCheckboxName(FrameNode* frameNode);
    static std::string GetCheckboxGroup(FrameNode* frameNode);

    static void SetOnChange(FrameNode* frameNode, ChangeEvent&& onChange);
    static void ResetComponentColor(FrameNode* frameNode, const CheckBoxColorType type);
    static void UpdateComponentColor(FrameNode* frameNode, const CheckBoxColorType type, const Color& color);
    static void CreateWithResourceObj(
        FrameNode* frameNode, const CheckBoxColorType type, const RefPtr<ResourceObject>& resObj);

private:
    static std::string ColorTypeToString(const CheckBoxColorType checkBoxColorType);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOX_CHECKBOX_MODEL_NG_H
