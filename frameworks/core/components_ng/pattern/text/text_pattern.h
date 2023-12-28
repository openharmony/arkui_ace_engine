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
#include <unordered_map>

#include "interfaces/inner_api/ace/ai/data_detector_interface.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_controller.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_overlay_modifier.h"
#include "core/components_ng/pattern/text/text_paint_method.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
enum class Status {DRAGGING, ON_DROP, NONE };
using CalculateHandleFunc = std::function<void()>;
using ShowSelectOverlayFunc = std::function<void(const RectF&, const RectF&)>;
// TextPattern is the base class for text render node to perform paint text.
class TextPattern : public ScrollablePattern, public TextDragBase, public TextBase {
    DECLARE_ACE_TYPE(TextPattern, ScrollablePattern, TextDragBase, TextBase);

public:
    TextPattern() = default;
    ~TextPattern() override = default;

    SelectionInfo GetSpansInfo(int32_t start, int32_t end, GetSpansMethod method);

    int32_t GetTextContentLength();

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

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextEventHub>();
    }

    bool IsDragging() const
    {
        return status_ == Status::DRAGGING;
    }

    bool IsAtomicNode() const override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        if (host->GetTag() == V2::SYMBOL_ETS_TAG) {
            return true;
        }
        return false;
    }

    bool DefaultSupportDrag() override
    {
        return true;
    }

    void OnModifyDone() override;

    void PreCreateLayoutWrapper();

    void BeforeCreateLayoutWrapper() override;

    void AddChildSpanItem(const RefPtr<UINode>& child);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false };
    }

    void DumpAdvanceInfo() override;
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

    void SetTextDetectEnable(bool enable)
    {
        bool cache = textDetectEnable_;
        textDetectEnable_ = enable;
        if (cache != textDetectEnable_) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }

    bool GetTextDetectEnable()
    {
        return textDetectEnable_;
    }

    void SetTextDetectTypes(const std::string& types);

    std::string GetTextDetectTypes()
    {
        return textDetectTypes_;
    }

    void SetOnResult(std::function<void(const std::string&)>&& onResult)
    {
        onResult_ = std::move(onResult);
    }

    void FireOnResult(const std::string& value)
    {
        if (onResult_) {
            onResult_(value);
        }
    }

    void SetTextDetectResult(const TextDataDetectResult result)
    {
        textDetectResult_ = result;
    }

    std::optional<TextDataDetectResult> GetTextDetectResult()
    {
        return textDetectResult_;
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

    std::vector<RectF> GetTextBoxes() override;
    OffsetF GetParentGlobalOffset() const override;

    OffsetF GetTextPaintOffset() const;

    const RefPtr<FrameNode>& MoveDragNode() override
    {
        return dragNode_;
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
    virtual void OnColorConfigurationUpdate() override;

    NG::DragDropInfo OnDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams);
    DragDropInfo OnDragStartNoChild(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams);
    void InitDragEvent();
    void UpdateSpanItemDragStatus(const std::list<ResultObject>& resultObjects, bool IsDragging);
    virtual std::function<void(Offset)> GetThumbnailCallback();
    std::list<ResultObject> dragResultObjects_;
    void OnDragEnd();
    void OnDragEndNoChild();
    void CloseOperate();
    void OnDragMove(const RefPtr<Ace::DragEvent>& event);

    std::string GetSelectedSpanText(std::wstring value, int32_t start, int32_t end) const;
    TextStyleResult GetTextStyleObject(const RefPtr<SpanNode>& node);
    SymbolSpanStyle GetSymbolSpanStyleObject(const RefPtr<SpanNode>& node);
    RefPtr<UINode> GetChildByIndex(int32_t index) const;
    RefPtr<SpanItem> GetSpanItemByIndex(int32_t index) const;
    ResultObject GetTextResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end);
    ResultObject GetSymbolSpanResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end);
    ResultObject GetImageResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end);

    const std::vector<std::string>& GetDragContents() const
    {
        return dragContents_;
    }

    void InitSpanImageLayout(const std::vector<int32_t>& placeholderIndex,
        const std::vector<RectF>& rectsForPlaceholders, OffsetF contentOffset) override
    {
        placeholderIndex_ = placeholderIndex;
        imageOffset_ = contentOffset;
        rectsForPlaceholders_ = rectsForPlaceholders;
    }

    const std::vector<int32_t>& GetPlaceHolderIndex()
    {
        return placeholderIndex_;
    }

    const std::vector<RectF>& GetRectsForPlaceholders()
    {
        return rectsForPlaceholders_;
    }

    OffsetF GetContentOffset() override
    {
        return imageOffset_;
    }

    const OffsetF& GetRightClickOffset() const
    {
        return mouseReleaseOffset_;
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
    virtual void CheckHandles(SelectHandleInfo& handleInfo);
    OffsetF GetDragUpperLeftCoordinates() override;
    void SetTextSelection(int32_t selectionStart, int32_t selectionEnd);

#ifndef USE_GRAPHIC_TEXT_GINE
    static RSTypographyProperties::TextBox ConvertRect(const Rect& rect);
#else
    static RSTextRect ConvertRect(const Rect& rect);
#endif
    // override SelectOverlayClient methods
    void OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle) override;
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle) override;
    void OnSelectOverlayMenuClicked(SelectOverlayMenuId menuId) override
    {
        switch (menuId) {
            case SelectOverlayMenuId::COPY:
                HandleOnCopy();
                return;
            case SelectOverlayMenuId::SELECT_ALL:
                HandleOnSelectAll();
                return;
            case SelectOverlayMenuId::CAMERA_INPUT:
                HandleOnCameraInput();
                return;
            default:
                return;
        }
    }

    RefPtr<FrameNode> GetClientHost() const override
    {
        return GetHost();
    }

    RefPtr<Paragraph> GetParagraph()
    {
        return paragraph_;
    }

    void MarkContentChange()
    {
        contChange_ = true;
    }

    void ResetContChange()
    {
        contChange_ = false;
    }

    bool GetContChange() const
    {
        return contChange_;
    }

    bool GetShowSelect() const
    {
        return showSelect_;
    }

    int32_t GetRecoverStart() const
    {
        return recoverStart_;
    }

    int32_t GetRecoverEnd() const
    {
        return recoverEnd_;
    }

    void OnAreaChangedInner() override;
    void RemoveAreaChangeInner();
    bool IsAtBottom() const override
    {
        return true;
    }

    bool IsAtTop() const override
    {
        return true;
    }

    bool UpdateCurrentOffset(float offset, int32_t source) override
    {
        return true;
    }

    virtual void UpdateScrollBarOffset() override {}

    const std::map<int32_t, AISpan>& GetAISpanMap()
    {
        return aiSpanMap_;
    }

    const std::string& GetTextForAI()
    {
        return textForAI_;
    }

    void ResetDragOption() override
    {
        CloseSelectOverlay();
        ResetSelection();
    }
    virtual bool NeedShowAIDetect();

    int32_t GetDragRecordSize() override
    {
        return dragRecordSize_;
    }

    void ResetDragRecordSize(int32_t size)
    {
        dragRecordSize_ = size;
    }

    void BindSelectionMenu(TextSpanType spanType, TextResponseType responseType, std::function<void()>& menuBuilder,
        std::function<void(int32_t, int32_t)>& onAppear, std::function<void()>& onDisappear);

    void SetTextController(const RefPtr<TextController>& controller)
    {
        textController_ = controller;
    }

    const RefPtr<TextController>& GetTextController()
    {
        return textController_;
    }

    void CloseSelectionMenu();

    void ClearSelectionMenu()
    {
        selectionMenuMap_.clear();
    }

protected:
    void OnAfterModifyDone() override;
    virtual void HandleOnCopy();
    void ClickAISpanOfSpan(std::map<int, OHOS::Ace::AISpan>::iterator& aiSpanIterator,
        const OHOS::Ace::RefPtr<OHOS::Ace::NG::SpanItem>& item, PointF textOffset, bool& isClickOnAISpan);
    virtual bool ClickAISpan(const PointF& textOffset, const AISpan& aiSpan);
    void InitMouseEvent();
    void ResetSelection();
    void RecoverSelection();
    virtual void HandleOnSelectAll();
    virtual void HandleOnCameraInput() {};
    void InitSelection(const Offset& pos);
    void HandleLongPress(GestureEvent& info);
    void HandleMouseEventOfAISpan(const MouseInfo& info, PointF textOffset, bool& isClickOnAISpan);
    void HandleClickEvent(GestureEvent& info);
    void HandleSingleClickEvent(GestureEvent& info);
    void HandleSpanSingleClickEvent(
        GestureEvent& info, RectF textContentRect, PointF textOffset, bool& isClickOnSpan, bool& isClickOnAISpan);
    void HandleDoubleClickEvent(GestureEvent& info);
    void InitTextDetect(int32_t startPos, std::string detectText);
    bool ShowUIExtensionMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc = nullptr,
        const ShowSelectOverlayFunc& showSelectOverlayFunc = nullptr);
    void SetOnClickMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc,
        const ShowSelectOverlayFunc& showSelectOverlayFunc);
    void ParseAIResult(const TextDataDetectResult& result, int32_t startPos);
    void ParseAIJson(const std::unique_ptr<JsonValue>& jsonValue, TextDataDetectType type, int32_t startPos,
        bool isMenuOption = false);
    void StartAITask();
    void CancelAITask()
    {
        aiDetectDelayTask_.Cancel();
    }
    bool IsDraggable(const Offset& localOffset);
    virtual void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    void ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle);
    void ShowSelectOverlay(
        const RectF& firstHandle, const RectF& secondHandle, bool animation, bool isUsingMouse = false);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool IsSelectAll();
    virtual int32_t GetHandleIndex(const Offset& offset) const;
    std::wstring GetWideText() const;
    std::string GetSelectedText(int32_t start, int32_t end) const;
    void CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity = TextAffinity::DOWNSTREAM);
    void UpdateSelectionType(const SelectionInfo& selection);
    void CopyBindSelectionMenuParams(SelectOverlayInfo& selectInfo, std::shared_ptr<SelectionMenuParams> menuParams);
    bool IsSelectedBindSelectionMenu();
    std::shared_ptr<SelectionMenuParams> GetMenuParams(TextSpanType type, TextResponseType responseType);

    virtual bool CanStartAITask()
    {
        return true;
    };

    Status status_ = Status::NONE;
    bool contChange_ = false;
    int32_t recoverStart_ = 0;
    int32_t recoverEnd_ = 0;
    bool enabled_ = true;
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
    float baselineOffset_ = 0.0f;
    int32_t placeholderCount_ = 0;
    SelectMenuInfo selectMenuInfo_;
    std::vector<RectF> dragBoxes_;

    // properties for AI
    bool textDetectEnable_ = false;
    bool aiDetectInitialized_ = false;
    bool aiDetectTypesChanged_ = false;
    bool hasClickedAISpan_ = false;
    std::string textDetectTypes_;
    std::set<std::string> textDetectTypesSet_;
    std::string textForAI_;
    std::optional<TextDataDetectResult> textDetectResult_;
    std::unordered_map<std::string, std::vector<std::string>> aiMenuOptionsMap_;
    std::function<void(const std::string&)> onResult_;
    std::function<void(const std::string&)> onClickMenu_;
    std::map<int32_t, AISpan> aiSpanMap_;
    CancelableCallback<void()> aiDetectDelayTask_;
    std::map<std::pair<TextSpanType, TextResponseType>, std::shared_ptr<SelectionMenuParams>> selectionMenuMap_;
    std::optional<TextSpanType> selectedType_;

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
    RefPtr<RenderContext> GetRenderContext();
    void ProcessBoundRectByTextShadow(RectF& rect);
    void FireOnSelectionChange(int32_t start, int32_t end);
    void HandleMouseLeftButton(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseRightButton(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftPressAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftReleaseAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftMoveAction(const MouseInfo& info, const Offset& textOffset);
    void HandleSelectionChange(int32_t start, int32_t end);
    void InitSpanItem(std::stack<RefPtr<UINode>> nodes);
    void UpdateSelectionSpanType(int32_t selectStart, int32_t selectEnd);
    int32_t GetSelectionSpanItemIndex(const MouseInfo& info);
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType);
    void RedisplaySelectOverlay();
    void ProcessBoundRectByTextMarquee(RectF& rect);
    ResultObject GetBuilderResultObject(RefPtr<UINode> uiNode, int32_t index, int32_t start, int32_t end);
    // to check if drag is in progress

    bool isMeasureBoundary_ = false;
    bool isMousePressed_ = false;
    bool isCustomFont_ = false;
    bool blockPress_ = false;
    bool hasClicked_ = false;
    bool isDoubleClick_ = false;
    TimeStamp lastClickTimeStamp_;

    RefPtr<Paragraph> paragraph_;
    std::vector<MenuOptionsParam> menuOptionItems_;
    std::vector<int32_t> placeholderIndex_;
    std::vector<RectF> rectsForPlaceholders_;
    OffsetF imageOffset_;

    OffsetF mouseReleaseOffset_;
    OffsetF contentOffset_;
    OffsetF parentGlobalOffset_;
    GestureEventFunc onClick_;
    RefPtr<DragWindow> dragWindow_;
    RefPtr<DragDropProxy> dragDropProxy_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    std::optional<int32_t> surfacePositionChangedCallbackId_;
    int32_t dragRecordSize_ = -1;
    std::optional<TextResponseType> textResponseType_;
    RefPtr<TextController> textController_;
    TextSpanType oldSelectedType_ = TextSpanType::NONE;
    ACE_DISALLOW_COPY_AND_MOVE(TextPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
