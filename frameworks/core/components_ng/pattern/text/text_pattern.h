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
class TextPattern : public Pattern, public TextDragBase {
    DECLARE_ACE_TYPE(TextPattern, Pattern, TextDragBase);

public:
    TextPattern() = default;
    ~TextPattern() override;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        if (!textContentModifier_) {
            textContentModifier_ = MakeRefPtr<TextContentModifier>(textStyle_);
        }
        if (!textOverlayModifier_) {
            textOverlayModifier_ = MakeRefPtr<TextOverlayModifier>();
        }
        auto paintMethod = MakeRefPtr<TextPaintMethod>(
            WeakClaim(this), paragraph_, baselineOffset_, textContentModifier_, textOverlayModifier_);
        auto host = GetHost();
        CHECK_NULL_RETURN(host, paintMethod);
        auto context = host->GetRenderContext();
        CHECK_NULL_RETURN(context, paintMethod);
        if (context->GetClipEdge().has_value()) {
            auto geometryNode = host->GetGeometryNode();
            auto frameOffset = geometryNode->GetFrameOffset();
            auto frameSize = geometryNode->GetFrameSize();
            auto height = static_cast<float>(paragraph_->GetHeight() + std::fabs(baselineOffset_));
            if (context->GetClipEdge().value() == false && LessNotEqual(frameSize.Height(), height)) {
                RectF boundsRect(frameOffset.GetX(), frameOffset.GetY(), frameSize.Width(), height);
                textOverlayModifier_->SetBoundsRect(boundsRect);
            }
        }
        return paintMethod;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TextLayoutAlgorithm>(spanItemChildren_, paragraph_);
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
        return textContentModifier_;
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
        return spanItemChildren_;
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

    std::vector<RSTypographyProperties::TextBox> GetTextBoxes() override;
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
    void CreateHandles() override;

    bool BetweenSelectedPosition(const Offset& globalOffset) override;

    // end of TextDragBase implementations
    // ===========================================================

    void InitSurfaceChangedCallback();
    void HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight);
    bool HasSurfaceChangedCallback()
    {
        return surfaceChangedCallbackId_.has_value();
    }
    void UpdateSurfaceChangedCallbackId(int32_t id)
    {
        surfaceChangedCallbackId_ = id;
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

    void CheckHandles(SelectHandleInfo& handleInfo);

protected:
    void HandleOnCopy();
    void InitMouseEvent();
    void ResetSelection();
    void HandleOnSelectAll();
    void InitSelection(const Offset& pos);
    void HandleLongPress(GestureEvent& info);
    void HandleClickEvent(GestureEvent& info);
    bool IsDraggable(const Offset& localOffset);
    void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    virtual void ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle);
    int32_t GetGraphemeClusterLength(int32_t extend) const;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool IsSelected() const;
    virtual void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle);
    virtual void OnHandleMove(const RectF& handleRect, bool isFirstHandle);
    std::wstring GetWideText() const;
    std::string GetSelectedText(int32_t start, int32_t end) const;
    OffsetF CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight);
    RectF contentRect_;
    WeakPtr<FrameNode> dragNodeWk_;
    RefPtr<FrameNode> dragNode_;
    RefPtr<Paragraph> paragraph_;
    RefPtr<LongPressEvent> longPressEvent_;
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
    CopyOptions copyOption_ = CopyOptions::None;
    
    OffsetF imageOffset_;
    std::string textForDisplay_;
    std::optional<TextStyle> textStyle_;
    std::list<RefPtr<SpanItem>> spanItemChildren_;
    std::vector<MenuOptionsParam> menuOptionItems_;
    std::vector<int32_t> placeHolderIndex_;
    TextSelector textSelector_;
    float baselineOffset_ = 0.0f;
    bool showSelectOverlay_ = false;
    bool clickEventInitialized_ = false;
    bool mouseEventInitialized_ = false;
    std::vector<Rect> rectsForPlaceholders_;

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
    inline RSTypographyProperties::TextBox ConvertRect(const Rect& rect);
    void UpdateChildProperty(const RefPtr<SpanNode>& child) const;
    void ActSetSelection(int32_t start, int32_t end);
    void SetAccessibilityAction();
    void CollectSpanNodes(std::stack<RefPtr<UINode>> nodes, bool& isSpanHasClick);
    void FontRegisterCallback(RefPtr<SpanNode> spanNode);
    bool IsSelectAll();
    // to check if drag is in progress

    OffsetF contentOffset_;
    GestureEventFunc onClick_;
    SelectMenuInfo selectMenuInfo_;
    bool panEventInitialized_ = false;
    RefPtr<Clipboard> clipboard_;
    RefPtr<DragWindow> dragWindow_;
    RefPtr<DragDropProxy> dragDropProxy_;
    RefPtr<TextContentModifier> textContentModifier_;
    RefPtr<TextOverlayModifier> textOverlayModifier_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    ACE_DISALLOW_COPY_AND_MOVE(TextPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
