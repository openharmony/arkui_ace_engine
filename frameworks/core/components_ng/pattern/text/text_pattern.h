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
#include "core/common/ai/data_detector_adapter.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
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
#include "core/components_ng/pattern/text/text_select_overlay.h"
#include "core/components_ng/pattern/text_drag/text_drag_base.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/event/ace_events.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
enum class Status { DRAGGING, ON_DROP, NONE };
using CalculateHandleFunc = std::function<void()>;
using ShowSelectOverlayFunc = std::function<void(const RectF&, const RectF&)>;
struct SpanNodeInfo {
    RefPtr<UINode> node;
    RefPtr<UINode> containerSpanNode;
};
// TextPattern is the base class for text render node to perform paint text.
class TextPattern : public virtual Pattern, public TextDragBase, public TextBase {
    DECLARE_ACE_TYPE(TextPattern, Pattern, TextDragBase, TextBase);

public:
    TextPattern()
    {
        selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(WeakClaim(this));
    }

    ~TextPattern() override = default;

    SelectionInfo GetSpansInfo(int32_t start, int32_t end, GetSpansMethod method);
    std::list<ResultObject> GetSpansInfoInStyledString(int32_t start, int32_t end);

    virtual int32_t GetTextContentLength();

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
        return host->GetTag() == V2::SYMBOL_ETS_TAG;
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

    RectF GetTextContentRect() const override
    {
        auto textRect = contentRect_;
        auto host = GetHost();
        CHECK_NULL_RETURN(host, textRect);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, textRect);
        if (!renderContext->GetClipEdge().value_or(true) && paragraph_ &&
            LessNotEqual(textRect.Width(), paragraph_->GetLongestLine())) {
            textRect.SetWidth(paragraph_->GetLongestLine());
        }
        return textRect;
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

    void SetTextDetectEnable(bool enable)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        dataDetectorAdapter_->frameNode_ = host;
        bool cache = textDetectEnable_;
        textDetectEnable_ = enable;
        if (cache != textDetectEnable_) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
    bool GetTextDetectEnable()
    {
        return textDetectEnable_;
    }
    void SetTextDetectTypes(const std::string& types)
    {
        dataDetectorAdapter_->SetTextDetectTypes(types);
    }
    std::string GetTextDetectTypes()
    {
        return dataDetectorAdapter_->textDetectTypes_;
    }
    RefPtr<DataDetectorAdapter> GetDataDetectorAdapter()
    {
        return dataDetectorAdapter_;
    }
    const std::map<int32_t, AISpan>& GetAISpanMap()
    {
        return dataDetectorAdapter_->aiSpanMap_;
    }
    const std::string& GetTextForAI()
    {
        return dataDetectorAdapter_->textForAI_;
    }
    void SetOnResult(std::function<void(const std::string&)>&& onResult)
    {
        dataDetectorAdapter_->onResult_ = std::move(onResult);
    }
    std::optional<TextDataDetectResult> GetTextDetectResult()
    {
        return dataDetectorAdapter_->textDetectResult_;
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
    std::list<ResultObject> recoverDragResultObjects_;
    std::vector<RefPtr<SpanItem>> dragSpanItems_;
    void OnDragEnd(const RefPtr<Ace::DragEvent>& event);
    void OnDragEndNoChild(const RefPtr<Ace::DragEvent>& event);
    void CloseOperate();
    void OnDragMove(const RefPtr<Ace::DragEvent>& event);
    void AddUdmfData(const RefPtr<Ace::DragEvent>& event);

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

    void SetImageSpanNodeList(std::vector<WeakPtr<FrameNode>> imageNodeList)
    {
        imageNodeList_ = imageNodeList;
    }

    std::vector<WeakPtr<FrameNode>> GetImageSpanNodeList()
    {
        return imageNodeList_;
    }
    // Deprecated: Use the TextSelectOverlay::ProcessOverlay() instead.
    // It is currently used by RichEditorPattern.
    virtual void UpdateSelectOverlayOrCreate(SelectOverlayInfo& selectInfo, bool animation = false);
    // Deprecated: Use the TextSelectOverlay::CheckHandleVisible() instead.
    // It is currently used by RichEditorPattern.
    virtual void CheckHandles(SelectHandleInfo& handleInfo) {};
    OffsetF GetDragUpperLeftCoordinates() override;
    void SetTextSelection(int32_t selectionStart, int32_t selectionEnd);
    void SetFadeout(const bool& left, const bool& right, const float& gradientPercent);

#ifndef USE_GRAPHIC_TEXT_GINE
    static RSTypographyProperties::TextBox ConvertRect(const Rect& rect);
#else
    static RSTextRect ConvertRect(const Rect& rect);
#endif
    // Deprecated: Use the TextSelectOverlay::OnHandleMove() instead.
    // It is currently used by RichEditorPattern.
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle) override;

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

    virtual const std::list<RefPtr<UINode>>& GetAllChildren() const;

    void HandleSelectionChange(int32_t start, int32_t end);

    CopyOptions GetCopyOptions() const
    {
        return copyOption_;
    }
    bool CheckClickedOnSpanOrText(RectF textContentRect, const Offset& localLocation);

    // style string
    void SetSpanItemChildren(const std::list<RefPtr<SpanItem>>& spans)
    {
        spans_ = spans;
    }
    void SetSpanStringMode(bool isSpanStringMode)
    {
        isSpanStringMode_ = isSpanStringMode;
    }
    bool GetSpanStringMode() const
    {
        return isSpanStringMode_;
    }
    void SetStyledString(const RefPtr<SpanString>& value);
    // select overlay
    virtual int32_t GetHandleIndex(const Offset& offset) const;
    std::string GetSelectedText(int32_t start, int32_t end) const;
    void UpdateSelectionSpanType(int32_t selectStart, int32_t selectEnd);
    void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    void ResetSelection();
    bool IsSelectAll();
    void HandleOnCopy();
    virtual void HandleOnSelectAll();

    OffsetF GetTextPaintOffset() const override
    {
        return parentGlobalOffset_;
    }

    void SetTextResponseType(TextResponseType type)
    {
        textResponseType_ = type;
    }

    bool CheckSelectedTypeChange()
    {
        auto changed = selectedType_.has_value() && oldSelectedType_ != selectedType_.value();
        if (changed) {
            oldSelectedType_ = selectedType_.value();
        }
        return changed;
    }

    bool IsUsingMouse()
    {
        return sourceType_ == SourceType::MOUSE;
    }

    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo)
    {
        CopySelectionMenuParams(selectInfo, textResponseType_.value_or(TextResponseType::NONE));
    }

    std::vector<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> GetOnDrawList()
    {
        return onDraws_;
    }

    void SetOnDrawList(std::vector<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraws)
    {
        onDraws_ = onDraws;
    }

    void ClearOnDrawList()
    {
        onDraws_.clear();
    }

    void InitCustomSpan(std::vector<int32_t> customSpanIndex)
    {
        customSpanIndex_ = customSpanIndex;
    }

    std::vector<int32_t> GetCustomSpanIndex()
    {
        return customSpanIndex_;
    }

protected:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnAfterModifyDone() override;
    virtual bool ClickAISpan(const PointF& textOffset, const AISpan& aiSpan);
    void InitMouseEvent();
    void InitFocusEvent();
    void InitHoverEvent();
    void RecoverCopyOption();
    void InitCopyOption();
    void RecoverSelection();
    virtual void HandleOnCameraInput() {};
    void InitSelection(const Offset& pos);
    void HandleLongPress(GestureEvent& info);
    void HandleClickEvent(GestureEvent& info);
    void HandleSingleClickEvent(GestureEvent& info);
    void HandleClickAISpanEvent(const PointF& info);
    void HandleSpanSingleClickEvent(GestureEvent& info, RectF textContentRect, bool& isClickOnSpan);
    void HandleDoubleClickEvent(GestureEvent& info);
    void CheckOnClickEvent(GestureEvent& info);
    bool ShowUIExtensionMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc = nullptr,
        const ShowSelectOverlayFunc& showSelectOverlayFunc = nullptr);
    void SetOnClickMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc,
        const ShowSelectOverlayFunc& showSelectOverlayFunc);
    bool IsDraggable(const Offset& localOffset);
    virtual void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void ShowSelectOverlay(const OverlayRequest& = OverlayRequest());
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    virtual void UpdateSelectorOnHandleMove(const OffsetF& localOffset, float handleHeight, bool isFirstHandle);
    std::wstring GetWideText() const;
    void CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity = TextAffinity::DOWNSTREAM);
    void UpdateSelectionType(const SelectionInfo& selection);
    void CopyBindSelectionMenuParams(SelectOverlayInfo& selectInfo, std::shared_ptr<SelectionMenuParams> menuParams);
    bool IsSelectedBindSelectionMenu();
    bool CalculateClickedSpanPosition(const PointF& textOffset);
    void HiddenMenu();
    std::shared_ptr<SelectionMenuParams> GetMenuParams(TextSpanType type, TextResponseType responseType);

    virtual bool CanStartAITask()
    {
        return copyOption_ != CopyOptions::None && textDetectEnable_ && enabled_ && dataDetectorAdapter_;
    };

    Status status_ = Status::NONE;
    bool contChange_ = false;
    int32_t recoverStart_ = 0;
    int32_t recoverEnd_ = 0;
    bool enabled_ = true;
    bool mouseEventInitialized_ = false;
    bool panEventInitialized_ = false;
    bool clickEventInitialized_ = false;
    bool touchEventInitialized_ = false;
    bool focusInitialized_ = false;
    bool hoverInitialized_ = false;

    RefPtr<FrameNode> dragNode_;
    RefPtr<LongPressEvent> longPressEvent_;
    // Deprecated: Use the selectOverlay_ instead.
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
    std::map<std::pair<TextSpanType, TextResponseType>, std::shared_ptr<SelectionMenuParams>> selectionMenuMap_;
    std::optional<TextSpanType> selectedType_;
    SourceType sourceType_ = SourceType::NONE;

    // properties for AI
    bool textDetectEnable_ = false;
    RefPtr<DataDetectorAdapter> dataDetectorAdapter_ = MakeRefPtr<DataDetectorAdapter>();

    OffsetF parentGlobalOffset_;
    std::optional<TextResponseType> textResponseType_;

    friend class TextContentModifier;
private:
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleSpanLongPressEvent(GestureEvent& info);
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
    bool IsShowHandle();
    void SetAccessibilityAction();
    void CollectSpanNodes(std::stack<SpanNodeInfo> nodes, bool& isSpanHasClick);
    void UpdateContainerChildren(const RefPtr<UINode>& parent, const RefPtr<UINode>& child);
    RefPtr<RenderContext> GetRenderContext();
    void ProcessBoundRectByTextShadow(RectF& rect);
    void FireOnSelectionChange(int32_t start, int32_t end);
    void FireOnMarqueeStateChange(const TextMarqueeState& state);
    void HandleMouseLeftButton(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseRightButton(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftPressAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftReleaseAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftMoveAction(const MouseInfo& info, const Offset& textOffset);
    void InitSpanItem(std::stack<SpanNodeInfo> nodes);
    void EnsureOverlayExists();
    int32_t GetSelectionSpanItemIndex(const MouseInfo& info);
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType);
    void ProcessBoundRectByTextMarquee(RectF& rect);
    ResultObject GetBuilderResultObject(RefPtr<UINode> uiNode, int32_t index, int32_t start, int32_t end);
    void CreateModifier();

    bool IsLineBreakOrEndOfParagraph(int32_t pos) const;
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    // SpanString
    void MountImageNode(const RefPtr<ImageSpanItem>& imageItem);
    ImageSourceInfo CreateImageSourceInfo(const ImageSpanOptions& options);
    void ProcessSpanString();
    // to check if drag is in progress
    void SetCurrentDragTool(SourceTool tool)
    {
        lastDragTool_ = tool;
    }

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { RenderContext::ContextType::CANVAS };
    }

    SourceTool GetCurrentDragTool() const
    {
        return lastDragTool_;
    }

    void AddUdmfTxtPreProcessor(const ResultObject src, ResultObject& result, bool isAppend);
    void ProcessOverlayAfterLayout();
    Offset ConvertGlobalToLocalOffset(const Offset& globalOffset);

    bool isMeasureBoundary_ = false;
    bool isMousePressed_ = false;
    bool leftMousePressed_ = false;
    bool isCustomFont_ = false;
    bool blockPress_ = false;
    bool hasClicked_ = false;
    bool isDoubleClick_ = false;
    bool isSpanStringMode_ = false;
    bool showSelected_ = false;
    int32_t clickedSpanPosition_ = -1;
    TimeStamp lastClickTimeStamp_;
    bool leftFadeout_ = false;
    bool rightFadeout_ = false;
    float gradientPercent_ = 0.0;
    bool isMarqueeRunning_ = false;
    RefPtr<Paragraph> paragraph_;
    std::vector<MenuOptionsParam> menuOptionItems_;
    std::vector<int32_t> placeholderIndex_;
    std::vector<int32_t> customSpanIndex_;
    std::vector<RectF> rectsForPlaceholders_;
    OffsetF imageOffset_;

    OffsetF contentOffset_;
    GestureEventFunc onClick_;
    RefPtr<DragWindow> dragWindow_;
    RefPtr<DragDropProxy> dragDropProxy_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    SourceTool lastDragTool_;
    std::optional<int32_t> surfacePositionChangedCallbackId_;
    int32_t dragRecordSize_ = -1;
    RefPtr<TextController> textController_;
    TextSpanType oldSelectedType_ = TextSpanType::NONE;
    mutable std::list<RefPtr<UINode>> childNodes_;
    bool isShowMenu_ = true;
    RefPtr<TextSelectOverlay> selectOverlay_;
    std::vector<WeakPtr<FrameNode>> imageNodeList_;
    std::vector<std::function<void(NG::DrawingContext&, CustomSpanOptions)>> onDraws_;
    ACE_DISALLOW_COPY_AND_MOVE(TextPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
