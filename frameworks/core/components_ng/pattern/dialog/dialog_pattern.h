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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H

#include <cstdint>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/dialog//dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_accessibility_property.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"

namespace OHOS::Ace::NG {
class DialogPattern : public PopupBasePattern {
    DECLARE_ACE_TYPE(DialogPattern, PopupBasePattern);

public:
    DialogPattern(const RefPtr<DialogTheme>& dialogTheme, const RefPtr<UINode>& customNode)
        : dialogTheme_(dialogTheme), customNode_(customNode)
    {}
    ~DialogPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return AceType::MakeRefPtr<DialogLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<DialogEventHub>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<DialogAccessibilityProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    void BuildChild(const DialogProperties& dialogProperties);

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    const std::string& GetTitle()
    {
        return title_;
    }

    const std::string& GetMessage()
    {
        return message_;
    }

    const RefPtr<UINode>& GetCustomNode()
    {
        return customNode_;
    }

    void SetOpenAnimation(const std::optional<AnimationOption>& openAnimation)
    {
        openAnimation_ = openAnimation;
    }
    std::optional<AnimationOption> GetOpenAnimation() const
    {
        return openAnimation_;
    }

    void SetCloseAnimation(const std::optional<AnimationOption>& closeAnimation)
    {
        closeAnimation_ = closeAnimation;
    }
    std::optional<AnimationOption> GetCloseAnimation() const
    {
        return closeAnimation_;
    }

    void SetDialogProperties(const DialogProperties& param)
    {
        dialogProperties_ = param;
    }

    const DialogProperties& GetDialogProperties() const
    {
        return dialogProperties_;
    }
	
    void OnColorConfigurationUpdate() override;

private:
    void OnModifyDone() override;

    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleClick(const GestureEvent& info);
    void RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);

    void PopDialog(int32_t buttonIdx);

    // set render context properties of content frame
    void UpdateContentRenderContext(const RefPtr<FrameNode>& contentNode);

    RefPtr<FrameNode> BuildTitle(const DialogProperties& dialogProperties);
    RefPtr<FrameNode> BuildContent(const DialogProperties& dialogProperties);
    RefPtr<FrameNode> CreateDialogScroll(const DialogProperties& dialogProps);

    void UpdateDialogButtonProperty(RefPtr<FrameNode>& buttonNode);
    void AnalysisLayoutPropertyOfButton(RefPtr<OHOS::Ace::NG::FrameNode> buttonNode,
        RefPtr<OHOS::Ace::NG::LayoutProperty> layoutProps, bool useRelativeLayout, int index = 0);
    RefPtr<FrameNode> BuildButtons(const std::vector<ButtonInfo>& buttons);
    void AddButtonAndDivider(const std::vector<ButtonInfo>& buttons, RefPtr<OHOS::Ace::NG::FrameNode> container);
    RefPtr<FrameNode> CreateDivider(const Dimension dividerLength, const Dimension dividerWidth);
    RefPtr<FrameNode> CreateButton(
        const ButtonInfo& params, int32_t index, bool isCancel = false, bool useRelativeLayout = false);
    RefPtr<FrameNode> CreateButtonText(const std::string& text, const std::string& colorStr);
    // to close dialog when button is clicked
    void BindCloseCallBack(const RefPtr<GestureEventHub>& hub, int32_t buttonIdx);
    // build ActionSheet items
    RefPtr<FrameNode> BuildSheet(const std::vector<ActionSheetInfo>& sheets);
    RefPtr<FrameNode> BuildSheetItem(const ActionSheetInfo& item);
    RefPtr<FrameNode> BuildSheetInfoTitle(const std::string& title);
    RefPtr<FrameNode> BuildSheetInfoIcon(const std::string& icon);
    // build actionMenu
    RefPtr<FrameNode> BuildMenu(const std::vector<ButtonInfo>& buttons);

    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<UINode> customNode_;
    RefPtr<ClickEvent> onClick_;

    std::optional<AnimationOption> openAnimation_;
    std::optional<AnimationOption> closeAnimation_;

    // XTS inspector values
    std::string message_;
    std::string title_;

    DialogProperties dialogProperties_;

    ACE_DISALLOW_COPY_AND_MOVE(DialogPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DIALOG_DIALOG_PATTERN_H
