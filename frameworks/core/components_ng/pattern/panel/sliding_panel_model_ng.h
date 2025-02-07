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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_MODEL_NG_H

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/panel/sliding_panel_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SlidingPanelModelNG : public OHOS::Ace::SlidingPanelModel {
public:
    void Create(bool isShow) override;
    void SetPanelType(PanelType type) override;
    void SetPanelMode(PanelMode mode) override;
    void SetHasDragBar(bool hasDragBar) override;
    void SetCustomHeight(const CalcDimension& customHeight) override;
    void SetMiniHeight(const Dimension& miniHeight) override;
    void SetHalfHeight(const Dimension& halfHeight) override;
    void SetFullHeight(const Dimension& fullHeight) override;
    void SetIsShow(bool isShow) override;
    void SetShowCloseIcon(bool showCloseIcon) override;
    void SetBackgroundMask(const Color& backgroundMask) override;
    void SetBackgroundColor(const Color& backgroundColor) override;
    void SetOnSizeChange(ChangeEvent&& changeEvent) override;
    void SetOnHeightChange(HeightChangeEvent&& onHeightChange) override;
    void Pop() override;
    void SetBorderColor(const Color& borderColor) override;
    void SetBorderWidth(const Dimension& borderWidth) override;
    void SetBorderStyle(const BorderStyle& borderStyle) override;
    void SetBorder(const BorderStyle& borderStyle, const Dimension& borderWidth) override;
    void SetModeChangeEvent(ChangeEvent&& modeChangeEvent) override;

// static methods.
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetPanelMode(FrameNode* frameNode, const std::optional<PanelMode>& mode);
    static void SetPanelMiniHeight(FrameNode* frameNode, const std::optional<Dimension>& miniHeight);
    static void SetPanelHalfHeight(FrameNode* frameNode, const std::optional<Dimension>& halfHeight);
    static void ResetPanelHalfHeight(FrameNode* frameNode);
    static void SetPanelFullHeight(FrameNode* frameNode, const std::optional<Dimension>& fullHeight);
    static void ResetPanelFullHeight(FrameNode* frameNode);
    static void SetPanelBackgroundMask(FrameNode* frameNode, const std::optional<Color>& backgroundMask);
    static void SetPanelType(FrameNode* frameNode, const std::optional<PanelType>& type);
    static void SetPanelCustomHeight(FrameNode* frameNode, const std::optional<CalcDimension>& customHeight);
    static void SetShowCloseIcon(FrameNode* frameNode, bool showCloseIcon);
    static void SetHasDragBar(FrameNode* frameNode, bool hasDragBar);
    static void SetIsShow(FrameNode* frameNode, bool isShow);
    static void SetOnSizeChange(FrameNode* frameNode, ChangeEvent&& changeEvent);
    static void SetOnHeightChange(FrameNode* frameNode, HeightChangeEvent&& onHeightChange);
    static void SetModeChangeEvent(FrameNode* frameNode, ChangeEvent&& modeChangeEvent);

private:
    static RefPtr<SlidingPanelNode> GetOrCreateSlidingPanelNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    static RefPtr<LinearLayoutProperty> GetLinearLayoutProperty();
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_MODEL_NG_H
