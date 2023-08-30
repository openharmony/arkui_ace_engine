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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H

#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_overlay_modifier.h"
#include "core/components_ng/pattern/text/text_paint_method.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
// TextPattern is the base class for text render node to perform paint text.
class TextPattern : public Pattern, public TextDragBase, public TextBase {
    DECLARE_ACE_TYPE(TextPattern, Pattern, TextDragBase, TextBase);

public:
    TextPattern() = default;
    ~TextPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TextLayoutAlgorithm>(spans_);
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TextAccessibilityProperty>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool DefaultSupportDrag() override
    {
        return true;
    }

    void OnModifyDone() override;

    void BeforeCreateLayoutWrapper() override;

    void AddChildSpanItem(const RefPtr<UINode>& child);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false };
    }

    void DumpInfo() override;

    TextSelector GetTextSelector() const
    {
        return textSelector_;
    }

    std::string GetTextForDisplay() const
    {
        return textForDisplay_;
    }

    const OffsetF& GetStartOffset() const
    {
        return textSelector_.selectionBaseOffset;
    }

    const OffsetF& GetEndOffset() const
    {
        return textSelector_.selectionDestinationOffset;
    }

    double GetSelectHeight() const
    {
        return textSelector_.GetSelectHeight();
    }

    void GetGlobalOffset(Offset& offset);

    const RectF& GetTextContentRect() const override
    {
        return contentRect_;
    }

    float GetBaselineOffset() const
    {
        return baselineOffset_;
    }

    RefPtr<TextContentModifier> GetContentModifier()
    {
        return contentMod_;
    }

    void SetMenuOptionItems(std::vector<MenuOptionsParam>&& menuOptionItems)
    {
        menuOptionItems_ = std::move(menuOptionItems);
    }

    const std::vector<MenuOptionsParam>&& GetMenuOptionItems() const
    {
        return std::move(menuOptionItems_);
    }

    void OnVisibleChange(bool isVisible) override;

    std::list<RefPtr<SpanItem>> GetSpanItemChildren()
    {
        return spans_;
    }

    int32_t GetDisplayWideTextLength()
    {
        return StringUtils::ToWstring(textForDisplay_).length();
    }

    // ===========================================================
    // TextDragBase implementations

    bool IsTextArea() const override
    {
        return false;
    }

    const RectF& GetTextRect() override
    {
        return contentRect_;
    }
    float GetLineHeight() const override;

#ifndef USE_GRAPHIC_TEXT_GINE
    std::vector<RSTypographyProperties::TextBox> GetTextBoxes() override;
#else
    std::vector<RSTextRect> GetTextBoxes() override;
#endif
    OffsetF GetParentGlobalOffset() const override;

    RefPtr<FrameNode> MoveDragNode() override
    {
        return std::move(dragNode_);
    }

    ParagraphT GetDragParagraph() const override
    {
        return { paragraph_ };
    }

    bool CloseKeyboard(bool /* forceClose */) override
    {
        return true;
    }
    virtual void CloseSelectOverlay() override;
    void CloseSelectOverlay(bool animation);
    void CreateHandles() override;

    bool BetweenSelectedPosition(const Offset& globalOffset) override;

    // end of TextDragBase implementations
    // ===========================================================

    void InitSurfaceChangedCallback();
    void InitSurfacePositionChangedCallback();
    virtual void HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight);
    virtual void HandleSurfacePositionChanged(int32_t posX, int32_t posY) {};
    bool HasSurfaceChangedCallback()
    {
        return surfaceChangedCallbackId_.has_value();
    }
    void UpdateSurfaceChangedCallbackId(int32_t id)
    {
        surfaceChangedCallbackId_ = id;
    }

    bool HasSurfacePositionChangedCallback()
    {
        return surfacePositionChangedCallbackId_.has_value();
    }
    void UpdateSurfacePositionChangedCallbackId(int32_t id)
    {
        surfacePositionChangedCallbackId_ = id;
    }

    void SetOnClickEvent(GestureEventFunc&& onClick)
    {
        onClick_ = std::move(onClick);
    }
    void OnColorConfigurationUpdate() override;

#ifdef ENABLE_DRAG_FRAMEWORK
    DragDropInfo OnDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams);
    void InitDragEvent();
    virtual std::function<void(Offset)> GetThumbnailCallback();
#endif

    void InitSpanImageLayout(const std::vector<int32_t>& placeHolderIndex,
        const std::vector<Rect>& rectsForPlaceholders, OffsetF contentOffset) override
    {
        placeHolderIndex_ = placeHolderIndex;
        imageOffset_ = contentOffset;
        rectsForPlaceholders_ = rectsForPlaceholders;
    }

    const std::vector<int32_t>& GetPlaceHolderIndex()
    {
        return placeHolderIndex_;
    }

    const std::vector<Rect>& GetRectsForPlaceholders()
    {
        return rectsForPlaceholders_;
    }

    OffsetF GetContentOffset() override
    {
        return imageOffset_;
    }

    bool IsMeasureBoundary() const override
    {
        return isMeasureBoundary_;
    }

    void SetIsMeasureBoundary(bool isMeasureBoundary)
    {
        isMeasureBoundary_ = isMeasureBoundary;
    }

    void SetIsCustomFont(bool isCustomFont)
    {
        isCustomFont_ = isCustomFont;
    }

    bool GetIsCustomFont()
    {
        return isCustomFont_;
    }
    void UpdateSelectOverlayOrCreate(SelectOverlayInfo selectInfo, bool animation = false);
    void CheckHandles(SelectHandleInfo& handleInfo);
    OffsetF GetDragUpperLeftCoordinates() override;

#ifndef USE_GRAPHIC_TEXT_GINE
    static RSTypographyProperties::TextBox ConvertRect(const Rect& rect);
#else
    static RSTextRect ConvertRect(const Rect& rect);
#endif

protected:
    virtual void HandleOnCopy();
    void InitMouseEvent();
    void ResetSelection();
    virtual void HandleOnSelectAll();
    void InitSelection(const Offset& pos);
    void HandleLongPress(GestureEvent& info);
    void HandleClickEvent(GestureEvent& info);
    bool IsDraggable(const Offset& localOffset);
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    void ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle);
    void ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle, bool animation);
    int32_t GetGraphemeClusterLength(int32_t extend) const;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool IsSelectAll();
    virtual void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle);
    virtual void OnHandleMove(const RectF& handleRect, bool isFirstHandle);
    virtual int32_t GetHandleIndex(const Offset& offset) const;
    std::wstring GetWideText() const;
    std::string GetSelectedText(int32_t start, int32_t end) const;
    OffsetF CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight);

    bool showSelectOverlay_ = false;
    bool mouseEventInitialized_ = false;
    bool panEventInitialized_ = false;
    bool clickEventInitialized_ = false;
    bool touchEventInitialized_ = false;

    RectF contentRect_;
    RefPtr<FrameNode> dragNode_;
    RefPtr<LongPressEvent> longPressEvent_;
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
    RefPtr<Clipboard> clipboard_;
    RefPtr<TextContentModifier> contentMod_;
    RefPtr<TextOverlayModifier> overlayMod_;
    CopyOptions copyOption_ = CopyOptions::None;

    std::string textForDisplay_;
    std::optional<TextStyle> textStyle_;
    std::list<RefPtr<SpanItem>> spans_;
    TextSelector textSelector_;
    float baselineOffset_ = 0.0f;
    int32_t imageCount_ = 0;
    SelectMenuInfo selectMenuInfo_;
    bool ignoreEvent_ = false;
#ifndef USE_GRAPHIC_TEXT_GINE
    std::vector<RSTypographyProperties::TextBox> dragBoxes_;
#else
    std::vector<RSTextRect> dragBoxes_;
#endif

private:
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnAttachToFrameNode() override;
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleMouseEvent(const MouseInfo& info);
    void OnHandleTouchUp();
    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandlePanStart(const GestureEvent& info);
    void HandlePanUpdate(const GestureEvent& info);
    void HandlePanEnd(const GestureEvent& info);
    void InitTouchEvent();
    void HandleTouchEvent(const TouchEventInfo& info);
    void UpdateChildProperty(const RefPtr<SpanNode>& child) const;
    void ActSetSelection(int32_t start, int32_t end);
    void SetAccessibilityAction();
    void CollectSpanNodes(std::stack<RefPtr<UINode>> nodes, bool& isSpanHasClick);
    // to check if drag is in progress

    bool isMeasureBoundary_ = false;
    bool isMousePressed_ = false;
    bool isCustomFont_ = false;
    bool blockPress_ = false;

    RefPtr<Paragraph> paragraph_;
    std::vector<MenuOptionsParam> menuOptionItems_;
    std::vector<int32_t> placeHolderIndex_;
    std::vector<Rect> rectsForPlaceholders_;
    OffsetF imageOffset_;

    OffsetF contentOffset_;
    GestureEventFunc onClick_;
    RefPtr<DragWindow> dragWindow_;
    RefPtr<DragDropProxy> dragDropProxy_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    std::optional<int32_t> surfacePositionChangedCallbackId_;
    ACE_DISALLOW_COPY_AND_MOVE(TextPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
