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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_SELECTION_CONTAINER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_SELECTION_CONTAINER_PATTERN_H

#include <optional>
#include <unordered_map>

#include "core/components_ng/pattern/selection_container/selection_container_event_hub.h"
#include "core/components_ng/manager/select_content_overlay/selection_container.h"
#include "core/components_ng/pattern/selection_container/selection_select_overlay.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text_field/text_selector.h"

namespace OHOS::Ace {
class GestureEvent;
struct KeyEvent;
class SpanString;
class MutableSpanString;
enum class WindowSizeChangeReason : uint32_t;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
enum class SelectionMenuCalblackId { MENU_APPEAR, MENU_SHOW, MENU_HIDE };
class ScrollablePattern;

class ACE_FORCE_EXPORT SelectionContainerPattern : public StackPattern, public SelectionContainer, public TextBase {
    DECLARE_ACE_TYPE(SelectionContainerPattern, StackPattern, SelectionContainer, TextBase);

public:
    SelectionContainerPattern() = default;
    ~SelectionContainerPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<SelectionContainerLayoutProperty>();
    }
    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SelectionContainerEventHub>();
    }
    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true, FocusStyleType::OUTER_BORDER };
    }

    std::u16string GetSelectionText() override;
    RefPtr<FrameNode> GetHostNode() const override;
    void CloseSelectOverlay(
        bool animation = false, CloseReason reason = CloseReason::CLOSE_REASON_NORMAL) override;
    void ProcessOverlay(const OverlayRequest& request) override;
    void SwitchToOverlayMode() override;
    void ToggleMenu() override;
    void HideMenu(bool noAnimation = false, bool showSubMenu = false) override;
    void DisableMenu() override;
    void UpdateAISelectMenu() override;
    bool IsCurrentMenuVisibile() override;
    bool IsUsingMouse() override;
    void SetSourceType(SourceType sourceType) override
    {
        sourceType_ = sourceType;
    }
    void SetMouseMenuOffset(const OffsetF& offset) override;
    void UpdateHandleColor() override;
    void HandleOnCopy() override;
    void HandleOnCopyFromAI(const RefPtr<SelectionContainerChild>& child) override;
    void HandleOnSelectAll() override;
    bool GetEnableHapticFeedback() const override
    {
        return enableHapticFeedback_;
    }
    void SetEnableHapticFeedback(bool isEnabled)
    {
        enableHapticFeedback_ = isEnabled;
    }
    bool SelectOverlayIsOn() override;
    void RebuildSelectionSpanTypeByFullScan() override;
    bool IsSelectedTypeChange();
    bool CheckSelectedTypeChange();
    CopyOptions GetCopyOption() const override;
    std::optional<Color> GetSelectedBackgroundColor() const override;
    void OnModifyDone() override;
    void MarkContainerPropertyUpdate(uint32_t flags);
    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;
    std::u16string GetTextJoinSeparator() const
    {
        return textJoinStyle_ == SelectionContainerTextJoinStyle::DIRECT ? u"" : u"\n";
    }
    void SetTextJoinStyle(SelectionContainerTextJoinStyle style)
    {
        textJoinStyle_ = style;
    }
    bool FireOnWillCopy(const std::u16string& text);
    void FireOnCopy(const std::u16string& text);
    void OnSelectionRangeChanged(const std::vector<std::u16string>& selectedTexts,
        const std::vector<ChildSelectionInfo>& selectionState) override;
    void OnChildResponseTypeChanged(TextResponseType responseType) override
    {
        textResponseType_ = responseType;
    }
    void OnChildSelectedTypeSave() override
    {
        SaveOldSelectedType();
    }
    void OnChildSelectionSpanTypeChanged(
        int32_t childId, const ChildSelectionSummary& oldSummary, const ChildSelectionSummary& newSummary) override;
    void SaveOldSelectedType() override;
    void SetSelectionHoldCallback() override;
    bool IsSelectedBindSelectionMenu() const override;
    bool IsTriggerParentToScroll() override;
    bool HasScrollableParent() override;
    void TriggerScrollableParentToScroll(const OffsetF& globalPoint, bool isStopAutoScroll) override;
    void EnableMouseLeftSelectionTracking(const OffsetF& globalPoint) override;
    void StopMouseLeftSelectionTracking() override;
    void UpdateMovingChildForHandle(bool isFirstHandle);
    bool GetIsHandleDragging() override;
    bool IsClickAtHandle(const GestureEvent& info) override;
    bool IsTouchAtHandle(const TouchEventInfo& info) override;
    void UpdateAllHandlesOffset() override;
    void UpdateViewPort() override;
    void MarkOverlayDirty() override;
    bool IsShowMouseMenu() override;
    void UpdateMenuOnWindowSizeChanged(WindowSizeChangeReason type) override;
    void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) override;
    FrameNodeChangeInfoFlag CollectDescendantChangeFlags() override;
    void BindSelectionMenu(TextSpanType spanType, TextResponseType responseType,
        std::function<void()>& menuBuilder, const SelectMenuParam& menuParam);
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo);
    std::shared_ptr<SelectionMenuParams> GetMenuParams(TextSpanType spanType, TextResponseType responseType);
    void OnHandleSelectionMenuCallback(
        SelectionMenuCalblackId callbackId, std::shared_ptr<SelectionMenuParams> menuParams);
    void OnSelectionMenuOptionsUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick,
        const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);
    void SetSelectionMenuItemClickWithTextCallback(
        std::function<bool(const MenuItemParam&, const std::u16string&)>&& onMenuItemClickWithText);
    OffsetF GetContainerPaintOffsetWithTransform() const;
    bool BetweenSelectedPosition(const Offset& globalOffset) override
    {
        return SelectionContainer::BetweenSelectedPosition(globalOffset);
    }
    RefPtr<FrameNode> GetClientHost() const override
    {
        return GetHost();
    }

private:
    void ApplySelectionSummaryDelta(const ChildSelectionSummary& summary, int32_t delta);
    void RecomputeSelectedTypeFromSummary();
    TextResponseType textResponseType_ = TextResponseType::NONE;
    std::map<std::pair<TextSpanType, TextResponseType>,
        std::shared_ptr<SelectionMenuParams>> selectionMenuMap_;
    std::function<bool(const MenuItemParam&, const std::u16string&)> onMenuItemClickWithText_;

    RefPtr<SelectionSelectOverlay> GetOrCreateSelectionSelectOverlay();
    void InitKeyEvent();
    bool HandleKeyEvent(const KeyEvent& keyEvent);
    void WriteClipboard(const std::u16string& clipboardText,
        const RefPtr<MutableSpanString>& mergedSpanString, bool hasSpanString, CopyOptions copyOption);
    void HandleOnCopySpanString(const RefPtr<SpanString>& spanString, CopyOptions copyOption);
    void AsyncHandleOnCopySpanStringHtml(const RefPtr<SpanString>& spanString, CopyOptions copyOption);
    void HandleOnCopyWithoutSpanString(const std::string& pasteData, CopyOptions copyOption);
    void OnSelectionMovingChildChange(const RefPtr<SelectionContainerChild>& child) override;
    void ResetScrollableParentOnScrollStop(bool isStopAutoScroll);
    void UpdateScrollableParentByChild(const RefPtr<SelectionContainerChild>& child);
    bool IsPointInScrollableViewport(const RefPtr<ScrollablePattern>& scrollablePattern, const OffsetF& globalPoint);
    bool CheckScrollableParentSize(const RefPtr<ScrollablePattern>& scrollablePattern);
    void RegisterMouseLeftSelectionNodeChangeListener();
    void UnregisterMouseLeftSelectionNodeChangeListener();
    void RefreshMouseLeftSelectionOnFrameNodeChanged();
    FrameNodeChangeInfoFlag CollectFlagsFromChildToHost(const RefPtr<FrameNode>& childHost, int32_t containerId);
    RefPtr<SelectionSelectOverlay> selectionSelectOverlay_;
    WeakPtr<ScrollablePattern> scrollableParent_;
    bool scrollableParentIsInsideContainer_ = false;
    bool isTriggerParentToScroll_ = false;
    bool mouseLeftSelectionNodeChangeListenerRegistered_ = false;
    std::optional<OffsetF> lastMouseLeftGlobalPoint_;
    std::unordered_map<int32_t, ChildSelectionSummary> childSelectionSummaryMap_;
    RefPtr<Clipboard> clipboard_;
    std::optional<TextSpanType> selectedType_;
    TextSpanType oldSelectedType_ = TextSpanType::NONE;
    int32_t selectedTextCount_ = 0;
    int32_t selectedImageCount_ = 0;
    int32_t selectedBuilderCount_ = 0;
    int32_t selectedMixedCount_ = 0;
    SourceType sourceType_ = SourceType::NONE;
    bool enableHapticFeedback_ = true;
    bool hasModifyDone_ = false;
    bool keyEventInitialized_ = false;
    uint32_t pendingContainerPropertyUpdateFlags_ = 0;
    SelectionContainerTextJoinStyle textJoinStyle_ = SelectionContainerTextJoinStyle::NEWLINE;
    std::vector<ChildSelectionInfo> lastSelectionState_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECTION_CONTAINER_SELECTION_CONTAINER_PATTERN_H
