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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_NG_H

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CheckBoxGroupModelNG : public OHOS::Ace::CheckBoxGroupModel {
public:
    void Create(const std::optional<std::string>& groupName) override;
    void SetSelectAll(bool isSelected) override;
    void SetSelectedColor(const Color& color) override;
    void SetUnSelectedColor(const Color& color) override;
    void SetCheckMarkColor(const Color& color) override;
    void SetCheckMarkSize(const Dimension& size) override;
    void SetCheckMarkWidth(const Dimension& width) override;
    void SetOnChange(GroupChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag) override;
    void SetChangeEvent(GroupChangeEvent&& changeEvent) override;
    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;
    void SetCheckboxGroupStyle(CheckBoxStyle checkboxGroupStyle) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSelectAll(FrameNode* frameNode, bool isSelected);
    static void SetSelectedColor(FrameNode* frameNode, const Color& color);
    static void SetUnSelectedColor(FrameNode* frameNode, const Color& color);
    static void SetWidth(FrameNode* frameNode, const Dimension& width);
    static void SetHeight(FrameNode* frameNode, const Dimension& height);
    static void SetCheckMarkColor(FrameNode* frameNode, const Color& color);
    static void SetCheckMarkSize(FrameNode* frameNode, const Dimension& size);
    static void SetCheckMarkWidth(FrameNode* frameNode, const Dimension& width);
    static void SetCheckboxGroupStyle(FrameNode* frameNode, CheckBoxStyle checkboxGroupStyle);
    static void SetCheckboxGroupName(FrameNode* frameNode, const std::optional<std::string>& groupName);

    static std::string GetCheckboxGroupName(FrameNode* frameNode);
    static bool GetSelect(FrameNode* frameNode);
    static Color GetSelectedColor(FrameNode* frameNode);
    static Color GetUnSelectedColor(FrameNode* frameNode);
    static Color GetCheckMarkColor(FrameNode* frameNode);
    static Dimension GetCheckMarkSize(FrameNode* frameNode);
    static Dimension GetCheckMarkWidth(FrameNode* frameNode);
    static CheckBoxStyle GetCheckboxGroupStyle(FrameNode* frameNode);

    static void SetOnChange(FrameNode* frameNode, ChangeEvent&& onChange);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_MODEL_NG_H
