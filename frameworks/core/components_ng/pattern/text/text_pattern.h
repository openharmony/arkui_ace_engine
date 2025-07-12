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

#include <limits>
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
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/rich_editor_drag/preview_menu_controller.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/select_overlay/magnifier.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"
#include "core/components_ng/pattern/text/multiple_click_recognizer.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
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
#include "core/components_ng/render/text_effect.h"
#include "core/components_ng/property/property.h"
#include "core/event/ace_events.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_SIZE_OF_LOG = 2000;
}

class InspectorFilter;
class PreviewMenuController;
enum class Status { DRAGGING, FLOATING, ON_DROP, NONE };
using CalculateHandleFunc = std::function<void()>;
using ShowSelectOverlayFunc = std::function<void(const RectF&, const RectF&)>;
struct SpanNodeInfo {
    RefPtr<UINode> node;
    RefPtr<UINode> containerSpanNode;
};
enum class SelectionMenuCalblackId { MENU_APPEAR, MENU_SHOW, MENU_HIDE };

// TextPattern is the base class for text render node to perform paint text.
class TextPattern : public virtual Pattern,
                    public TextDragBase,
                    public TextBase,
                    public TextGestureSelector,
                    public Magnifier,
                    public LayoutInfoInterface {
    DECLARE_ACE_TYPE(TextPattern, Pattern, TextDragBase, TextBase, TextGestureSelector, Magnifier);

public:
    TextPattern()
    {
        selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(WeakClaim(this));
        pManager_ = AceType::MakeRefPtr<ParagraphManager>();
        ResetOriginCaretPosition();
    }

    ~TextPattern() override;

    virtual RefPtr<FrameNode> GetContentHost() const
    {
        return GetHost();
    }

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
        auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
        if (textLayoutProperty &&
            textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE) {
            return MakeRefPtr<TextLayoutAlgorithm>(
                spans_, pManager_, isSpanStringMode_, textStyle_.value_or(TextStyle()), true);
        } else {
            return MakeRefPtr<TextLayoutAlgorithm>(
                spans_, pManager_, isSpanStringMode_, textStyle_.value_or(TextStyle()));
        }
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<TextAccessibilityProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<TextEventHub>();
    }

    virtual bool IsDragging() const
    {
        return status_ == Status::DRAGGING;
    }

    bool IsAtomicNode() const override
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        return host->GetTag() == V2::SYMBOL_ETS_TAG;
    }

    bool IsTextNode() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        return host->GetTag() == V2::TEXT_ETS_TAG;
    }

    bool DefaultSupportDrag() override
    {
        return true;
    }

    void OnModifyDone() override;

    void OnWindowHide() override;

    void OnWindowShow() override;

    void PreCreateLayoutWrapper();

    void BeforeCreateLayoutWrapper() override;

    void AddChildSpanItem(const RefPtr<UINode>& child);
    void SetSpanItemEvent(const RefPtr<SpanItem>& spanItem, RefPtr<FocusHub>& focusHub);
    void AddImageToSpanItem(const RefPtr<UINode>& child);

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false };
    }

    void DumpAdvanceInfo() override;
    void DumpInfo() override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    void SetTextStyleDumpInfo(std::unique_ptr<JsonValue>& json);
    void DumpTextStyleInfo();
    void DumpTextStyleInfo2();
    void DumpTextStyleInfo3();
    void DumpTextStyleInfo4();
    void DumpSpanItem();
    void DumpScaleInfo();
    void DumpTextEngineInfo();
    void DumpParagraphsInfo();

    TextSelector GetTextSelector() const
    {
        return textSelector_;
    }

    const std::u16string& GetTextForDisplay() const
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

    RectF GetTextContentRect(bool isActualText = false) const override;

    float GetBaselineOffset() const
    {
        return baselineOffset_;
    }

    RefPtr<TextContentModifier> GetContentModifier()
    {
        return contentMod_;
    }

    virtual void SetTextDetectEnable(bool enable);
    bool GetTextDetectEnable()
    {
        return textDetectEnable_;
    }
    void SetTextDetectTypes(const std::string& types)
    {
        dataDetectorAdapter_->SetTextDetectTypes(types);
        textDetectTypes_ = types; // url value is not recorded in dataDetectorAdapter_, need to record it here
    }
    std::string GetTextDetectTypes()
    {
        return textDetectTypes_;
    }
    RefPtr<DataDetectorAdapter> GetDataDetectorAdapter()
    {
        return dataDetectorAdapter_;
    }
    virtual const std::map<int32_t, AISpan>& GetAISpanMap()
    {
        return dataDetectorAdapter_->aiSpanMap_;
    }
    const std::u16string& GetTextForAI()
    {
        return dataDetectorAdapter_->textForAI_;
    }
    void SetOnResult(std::function<void(const std::string&)>&& onResult)
    {
        dataDetectorAdapter_->onResult_ = std::move(onResult);
    }
    TextDataDetectResult GetTextDetectResult()
    {
        return dataDetectorAdapter_->textDetectResult_;
    }
    virtual void MarkAISpanStyleChanged()
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyWithOnProChange(PROPERTY_UPDATE_MEASURE);
    }
    void SetTextDetectConfig(const TextDetectConfig& textDetectConfig)
    {
        dataDetectorAdapter_->SetTextDetectTypes(textDetectConfig.types);
        dataDetectorAdapter_->onResult_ = std::move(textDetectConfig.onResult);
        dataDetectorAdapter_->entityColor_ = textDetectConfig.entityColor;
        dataDetectorAdapter_->entityDecorationType_ = textDetectConfig.entityDecorationType;
        dataDetectorAdapter_->entityDecorationColor_ = textDetectConfig.entityDecorationColor;
        dataDetectorAdapter_->entityDecorationStyle_ = textDetectConfig.entityDecorationStyle;
        auto textDetectConfigCache = dataDetectorAdapter_->textDetectConfigStr_;
        dataDetectorAdapter_->textDetectConfigStr_ = textDetectConfig.ToString();
        if (textDetectConfigCache != dataDetectorAdapter_->textDetectConfigStr_) {
            MarkAISpanStyleChanged();
        }
        dataDetectorAdapter_->enablePreviewMenu_ = textDetectConfig.enablePreviewMenu;
    }
    void ModifyAISpanStyle(TextStyle& aiSpanStyle)
    {
        TextDetectConfig textDetectConfig;
        aiSpanStyle.SetTextColor(dataDetectorAdapter_->entityColor_.value_or(textDetectConfig.entityColor));
        aiSpanStyle.SetTextDecoration(
            dataDetectorAdapter_->entityDecorationType_.value_or(textDetectConfig.entityDecorationType));
        aiSpanStyle.SetTextDecorationColor(
            dataDetectorAdapter_->entityDecorationColor_.value_or(textDetectConfig.entityColor));
        aiSpanStyle.SetTextDecorationStyle(
            dataDetectorAdapter_->entityDecorationStyle_.value_or(textDetectConfig.entityDecorationStyle));
    }

    void OnVisibleChange(bool isVisible) override;

    std::list<RefPtr<SpanItem>> GetSpanItemChildren()
    {
        return spans_;
    }

    int32_t GetDisplayWideTextLength()
    {
        return textForDisplay_.length();
    }

    // ===========================================================
    // TextDragBase implementations

    bool IsTextArea() const override
    {
        return false;
    }

    const RectF& GetTextRect() const override
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

    const RefPtr<Paragraph>& GetDragParagraph() const override
    {
        return pManager_->GetParagraphs().front().paragraph;
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
    virtual void HandleSurfaceChanged(
        int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight, WindowSizeChangeReason type);
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

    void SetOnClickEvent(GestureEventFunc&& onClick, double distanceThreshold = std::numeric_limits<double>::infinity())
    {
        onClick_ = std::move(onClick);
        distanceThreshold_ = distanceThreshold;
    }

    NG::DragDropInfo OnDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams);
    DragDropInfo OnDragStartNoChild(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams);
    void InitDragEvent();
    void ClearDragEvent();
    void UpdateSpanItemDragStatus(const std::list<ResultObject>& resultObjects, bool IsDragging);
    void OnDragMove(const RefPtr<Ace::DragEvent>& event);
    virtual std::function<void(Offset)> GetThumbnailCallback();
    std::list<ResultObject> dragResultObjects_;
    std::list<ResultObject> recoverDragResultObjects_;
    std::vector<RefPtr<SpanItem>> dragSpanItems_;
    void OnDragEnd(const RefPtr<Ace::DragEvent>& event);
    void OnDragEndNoChild(const RefPtr<Ace::DragEvent>& event);
    void CloseOperate();
    virtual void AddUdmfData(const RefPtr<Ace::DragEvent>& event);
    void ProcessNormalUdmfData(const RefPtr<UnifiedData>& unifiedData);
    void AddPixelMapToUdmfData(const RefPtr<PixelMap>& pixelMap, const RefPtr<UnifiedData>& unifiedData);

    std::u16string GetSelectedSpanText(std::u16string value, int32_t start, int32_t end, bool includeStartHalf = false,
        bool includeEndHalf = true, bool getSubstrDirectly = true) const;
    TextStyleResult GetTextStyleObject(const RefPtr<SpanNode>& node);
    SymbolSpanStyle GetSymbolSpanStyleObject(const RefPtr<SpanNode>& node);
    virtual RefPtr<UINode> GetChildByIndex(int32_t index) const;
    RefPtr<SpanItem> GetSpanItemByIndex(int32_t index) const;
    ResultObject GetTextResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end);
    virtual void SetResultObjectText(ResultObject& resultObject, const RefPtr<SpanItem>& spanItem);
    ResultObject GetSymbolSpanResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end);
    ResultObject GetImageResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end);
    std::string GetFontInJson() const;
    std::string GetBindSelectionMenuInJson() const;
    std::unique_ptr<JsonValue> GetShaderStyleInJson() const;
    virtual void FillPreviewMenuInJson(const std::unique_ptr<JsonValue>& jsonValue) const {}
    std::string GetFontSizeWithThemeInJson(const std::optional<Dimension>& value) const;

    const std::vector<std::u16string>& GetDragContents() const
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

    // Deprecated: Use the TextSelectOverlay::OnHandleMove() instead.
    // It is currently used by RichEditorPattern.
    void OnHandleMove(const RectF& handleRect, bool isFirstHandle) override;

    virtual std::vector<ParagraphManager::ParagraphInfo> GetParagraphs() const
    {
        std::vector<ParagraphManager::ParagraphInfo> res;
        CHECK_NULL_RETURN(pManager_, res);
        return pManager_->GetParagraphs();
    }

    const RefPtr<ParagraphManager>& GetParagraphManager() const
    {
        return pManager_;
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

    void OnHandleAreaChanged() override;
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
        const SelectMenuParam& menuParam);

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

    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex);

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
    void AllocStyledString()
    {
        if (!styledString_) {
            styledString_ = MakeRefPtr<MutableSpanString>(u"");
        }
    }
    void SetStyledString(const RefPtr<SpanString>& value, bool closeSelectOverlay = true);
    // select overlay
    virtual int32_t GetHandleIndex(const Offset& offset) const;
    std::u16string GetSelectedText(int32_t start, int32_t end, bool includeStartHalf = false,
        bool includeEndHalf = false, bool getSubstrDirectly = false) const;
    void UpdateSelectionSpanType(int32_t selectStart, int32_t selectEnd);
    void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    void ResetSelection();
    virtual bool IsSelectAll();
    void HandleOnCopy();
    virtual void HandleAIMenuOption(const std::string& labelInfo = "");
    void HandleOnCopySpanString();
    virtual void HandleOnSelectAll();
    bool IsShowTranslate();
    bool IsShowSearch();
    void SetTextSelectableMode(TextSelectableMode value);

    OffsetF GetTextPaintOffset() const override
    {
        return parentGlobalOffset_;
    }

    void SetTextResponseType(TextResponseType type)
    {
        textResponseType_ = type;
    }

    bool IsSelectedTypeChange()
    {
        return selectedType_.has_value() && oldSelectedType_ != selectedType_.value();
    }

    bool CheckSelectedTypeChange()
    {
        auto changed = IsSelectedTypeChange();
        if (changed) {
            oldSelectedType_ = selectedType_.value();
        }
        return changed;
    }

    bool IsUsingMouse()
    {
        return sourceType_ == SourceType::MOUSE;
    }

    void OnSensitiveStyleChange(bool isSensitive) override;

    bool IsSetObscured() const;
    bool IsSensitiveEnable();

    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo)
    {
        CopySelectionMenuParams(selectInfo, textResponseType_.value_or(TextResponseType::NONE));
    }

    void InitCustomSpanPlaceholderInfo(const std::vector<CustomSpanPlaceholderInfo>& customSpanPlaceholder)
    {
        customSpanPlaceholder_ = customSpanPlaceholder;
    }

    std::vector<CustomSpanPlaceholderInfo> GetCustomSpanPlaceholderInfo()
    {
        return customSpanPlaceholder_;
    }

    void ClearCustomSpanPlaceholderInfo()
    {
        customSpanPlaceholder_.clear();
    }

    const std::list<RefPtr<UINode>>& GetChildNodes() const
    {
        return childNodes_;
    }
    // add for capi NODE_TEXT_CONTENT_WITH_STYLED_STRING
    void SetExternalParagraph(void* paragraph)
    {
        ACE_TEXT_SCOPED_TRACE("SetExternalParagraph");
        externalParagraph_ = paragraph;
    }

    const std::optional<void*>& GetExternalParagraph()
    {
        return externalParagraph_;
    }

    void SetExternalSpanItem(const std::list<RefPtr<SpanItem>>& spans);

    void SetExternalParagraphStyle(std::optional<ParagraphStyle> paragraphStyle)
    {
        externalParagraphStyle_ = paragraphStyle;
    }

    TextStyle GetTextStyle()
    {
        return textStyle_.value_or(TextStyle());
    }

    bool DidExceedMaxLines() const override;

    std::optional<ParagraphStyle> GetExternalParagraphStyle()
    {
        return externalParagraphStyle_;
    }

    size_t GetLineCount() const override;
    TextLineMetrics GetLineMetrics(int32_t lineNumber) override;
    std::vector<ParagraphManager::TextBox> GetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle) override;
    PositionWithAffinity GetGlyphPositionAtCoordinate(int32_t x, int32_t y) override;

    void OnSelectionMenuOptionsUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);

    void OnCreateMenuCallbackUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback)
    {
        selectOverlay_->OnCreateMenuCallbackUpdate(std::move(onCreateMenuCallback));
    }

    void OnMenuItemClickCallbackUpdate(const NG::OnMenuItemClickCallback&& onMenuItemClick)
    {
        selectOverlay_->OnMenuItemClickCallbackUpdate(std::move(onMenuItemClick));
    }

    void OnPrepareMenuCallbackUpdate(const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
    {
        selectOverlay_->OnPrepareMenuCallbackUpdate(std::move(onPrepareMenuCallback));
    }
    
    void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) override;

    void UpdateParentGlobalOffset()
    {
        parentGlobalOffset_ = GetParentGlobalOffset();
    }

    void SetPrintInfo(const std::string& area, const OffsetF& paintOffset)
    {
        paintInfo_ = area + paintOffset.ToString();
    }

    void DumpRecord(const std::string& record, bool stateChange = false)
    {
        if (stateChange || frameRecord_.length() > MAX_SIZE_OF_LOG) {
            frameRecord_.clear();
        }
        frameRecord_.append("[" + record + "]");
    }

    void LogForFormRender(const std::string& logTag);

    void SetIsUserSetResponseRegion(bool isUserSetResponseRegion)
    {
        isUserSetResponseRegion_ = isUserSetResponseRegion;
    }

    size_t GetSubComponentInfos(std::vector<SubComponentInfo>& subComponentInfos);

    void UpdateFontColor(const Color& value);
    void BeforeCreatePaintWrapper() override;

    void OnTextOverflowChanged();

    void MarkDirtyNodeRender();
    void MarkDirtyNodeMeasure();
    void ChangeHandleHeight(const GestureEvent& event, bool isFirst, bool isOverlayMode);
    void ChangeFirstHandleHeight(const Offset& touchOffset, RectF& handleRect);
    void ChangeSecondHandleHeight(const Offset& touchOffset, RectF& handleRect);
    virtual void CalculateDefaultHandleHeight(float& height);

    uint64_t GetSystemTimestamp()
    {
        return static_cast<uint64_t>(
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
                .count());
    }

    void SetEnableHapticFeedback(bool isEnabled)
    {
        isEnableHapticFeedback_ = isEnabled;
    }

    bool HasContent();

    virtual bool IsEnabledObscured() const
    {
        return true;
    }
    void SetupMagnifier();
    void DoTextSelectionTouchCancel() override;

    virtual Color GetUrlSpanColor();
    void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;

    void RegisterAfterLayoutCallback(std::function<void()> callback)
    {
        afterLayoutCallback_ = callback;
    }

    void UnRegisterAfterLayoutCallback()
    {
        afterLayoutCallback_ = std::nullopt;
    }

    RefPtr<MagnifierController> GetOrCreateMagnifier()
    {
        if (!magnifierController_) {
            magnifierController_ = MakeRefPtr<MagnifierController>(WeakClaim(this));
        }
        return magnifierController_;
    }

    void UnRegisterResource(const std::string& key) override;
    void EmplaceSymbolColorIndex(int32_t index)
    {
        symbolFontColorResObjIndexArr.emplace_back(index);
    }

    std::string GetCaretColor() const;
    std::string GetSelectedBackgroundColor() const;

    void ResetCustomFontColor();
    void OnColorConfigurationUpdate() override;
    bool OnThemeScopeUpdate(int32_t themeScopeId) override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;

    bool GetOriginCaretPosition(OffsetF& offset) const;
    void ResetOriginCaretPosition();
    bool RecordOriginCaretPosition(const OffsetF& offset);
    TextDragInfo CreateTextDragInfo();

    void SetIsShowAIMenuOption(bool isShowAIMenuOption)
    {
        isShowAIMenuOption_ = isShowAIMenuOption;
    }

    bool IsShowAIMenuOption() const
    {
        return isShowAIMenuOption_;
    }

    void SetAIItemOption(const std::unordered_map<TextDataDetectType, AISpan>& aiMenuOptions)
    {
        aiMenuOptions_ = aiMenuOptions;
    }

    const std::unordered_map<TextDataDetectType, AISpan>& GetAIItemOption() const
    {
        return aiMenuOptions_;
    }
    virtual void UpdateAIMenuOptions();
    bool PrepareAIMenuOptions(std::unordered_map<TextDataDetectType, AISpan>& aiMenuOptions);
    bool IsAiSelected();
    RefPtr<FrameNode> CreateAIEntityMenu();
    void InitAiSelection(const Offset& globalOffset);
    bool CanAIEntityDrag() override;
    RefPtr<PreviewMenuController> GetOrCreatePreviewMenuController();
    void ResetAISelected(AIResetSelectionReason reason) override;

    void ShowAIEntityMenuForCancel() override;
    AISpan GetSelectedAIData();
    std::pair<bool, bool> GetCopyAndSelectable();
    std::pair<int32_t, int32_t> GetSelectedStartAndEnd();

    RefPtr<TextEffect> GetTextEffect()
    {
        return textEffect_;
    }
    RefPtr<TextEffect> GetOrCreateTextEffect(const std::u16string& content, bool& needUpdateTypography);
    void RelayoutResetOrUpdateTextEffect();
    void ResetTextEffect();
    bool ResetTextEffectBeforeLayout(bool onlyReset = true);

    virtual void HandleOnAskCelia();

    void SetIsAskCeliaEnabled(bool isAskCeliaEnabled)
    {
        isAskCeliaEnabled_ = isAskCeliaEnabled && IsNeedAskCelia();
    }
    
    bool IsAskCeliaEnabled() const
    {
        return isAskCeliaEnabled_;
    }
    bool IsNeedAskCelia() const
    {
        // placeholder and symbol not support
        auto start = GetTextSelector().GetTextStart();
        auto end = GetTextSelector().GetTextEnd();
        auto content = UtfUtils::Str16DebugToStr8(GetSelectedText(start, end));
        return !std::regex_match(content, std::regex("^\\s*$"));
    }
    void UpdateTextSelectorSecondHandle(const RectF& rect)
    {
        textSelector_.secondHandle = rect;
    }

protected:
    int32_t GetClickedSpanPosition()
    {
        return clickedSpanPosition_;
    }
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnAfterModifyDone() override;
    virtual bool ClickAISpan(const PointF& textOffset, const AISpan& aiSpan);
    virtual void InitAISpanHoverEvent();
    virtual void HandleAISpanHoverEvent(const MouseInfo& info);
    void OnHover(bool isHover);
    void InitSpanMouseEvent();
    HoverInfo ConvertHoverInfoFromMouseInfo(const MouseInfo& info) const;
    void HandleSpanMouseEvent(const MouseInfo& info);
    void TriggerSpanOnHoverEvent(const HoverInfo& info, const RefPtr<SpanItem>& item, bool isOnHover);
    void TriggerSpansOnHover(const HoverInfo& info, const PointF& textOffset);
    void ExitSpansForOnHoverEvent(const HoverInfo& info);
    bool HasSpanOnHoverEvent();
    void InitMouseEvent();
    void InitFocusEvent();
    void InitHoverEvent();
    void AddIsFocusActiveUpdateEvent();
    void RemoveIsFocusActiveUpdateEvent();
    void OnIsFocusActiveUpdate(bool isFocusAcitve);
    void RecoverCopyOption();
    void InitCopyOption(const RefPtr<GestureEventHub>& gestureEventHub, const RefPtr<EventHub>& eventHub);
    void RecoverSelection();
    virtual void HandleOnCameraInput() {};
    void InitSelection(const Offset& pos);
    void GetIndexByOffset(const Offset& pos, int32_t& extend);
    void StartVibratorByLongPress();
    void HandleLongPress(GestureEvent& info);
    void HandleClickEvent(GestureEvent& info);
    void HandleSingleClickEvent(GestureEvent& info);
    void HandleClickAISpanEvent(const PointF& info);
    void HandleDoubleClickEvent(GestureEvent& info);
    void CheckOnClickEvent(GestureEvent& info);
    void HandleClickOnTextAndSpan(GestureEvent& info);
    bool TryLinkJump(const RefPtr<SpanItem>& span);
    void ActTextOnClick(GestureEvent& info);
    RectF CalcAIMenuPosition(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc);
    virtual void AdjustAIEntityRect(RectF& aiRect) {}
    bool ShowAIEntityMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc = nullptr,
        const ShowSelectOverlayFunc& showSelectOverlayFunc = nullptr);
    void SetOnClickMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc,
        const ShowSelectOverlayFunc& showSelectOverlayFunc);
    bool IsDraggable(const Offset& localOffset);
    virtual void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    void ShowSelectOverlay(const OverlayRequest& = OverlayRequest());
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    virtual void UpdateSelectorOnHandleMove(const OffsetF& localOffset, float handleHeight, bool isFirstHandle);
    void CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity = TextAffinity::DOWNSTREAM);
    void UpdateSelectionType(const SelectionInfo& selection);
    void CopyBindSelectionMenuParams(SelectOverlayInfo& selectInfo, std::shared_ptr<SelectionMenuParams> menuParams);
    virtual void OnHandleSelectionMenuCallback(
        SelectionMenuCalblackId callbackId, std::shared_ptr<SelectionMenuParams> menuParams);
    bool IsSelectedBindSelectionMenu();
    bool CheckAndClick(const RefPtr<SpanItem>& item);
    bool CalculateClickedSpanPosition(const PointF& textOffset);
    void HiddenMenu();
    std::shared_ptr<SelectionMenuParams> GetMenuParams(TextSpanType type, TextResponseType responseType);
    void AddUdmfTxtPreProcessor(const ResultObject src, ResultObject& result, bool isAppend);
    void InitKeyEvent();
    void UpdateShiftFlag(const KeyEvent& keyEvent);
    bool HandleKeyEvent(const KeyEvent& keyEvent);
    void HandleOnSelect(KeyCode code);
    void HandleSelectionUp();
    void HandleSelectionDown();
    void HandleSelection(bool isEmojiStart, int32_t end);
    double GetTextHeight(int32_t index, bool isNextLine);
    int32_t GetActualTextLength();
    bool IsSelectableAndCopy();
    void SetResponseRegion(const SizeF& frameSize, const SizeF& boundsSize);

    virtual bool CanStartAITask() const;

    void MarkDirtySelf();
    void OnAttachToMainTree() override
    {
        isDetachFromMainTree_ = false;
    }

    void OnDetachFromMainTree() override
    {
        isDetachFromMainTree_ = true;
    }

    void CreateMultipleClickRecognizer()
    {
        if (!multipleClickRecognizer_) {
            multipleClickRecognizer_ = MakeRefPtr<MultipleClickRecognizer>();
        }
    }

    bool SetActionExecSubComponent();
    void GetSubComponentInfosForAISpans(std::vector<SubComponentInfo>& subComponentInfos);
    void GetSubComponentInfosForSpans(std::vector<SubComponentInfo>& subComponentInfos);
    bool ExecSubComponent(int32_t spanId);
    void AddSubComponentInfosByDataDetectorForSpan(std::vector<SubComponentInfo>& subComponentInfos,
        const RefPtr<SpanItem>& span);
    void AddSubComponentInfoForAISpan(std::vector<SubComponentInfo>& subComponentInfos, const std::string& content,
        const AISpan& aiSpan);
    void AddSubComponentInfoForSpan(std::vector<SubComponentInfo>& subComponentInfos, const std::string& content,
        const RefPtr<SpanItem>& span);

    int32_t GetTouchIndex(const OffsetF& offset) override;
    void OnTextGestureSelectionUpdate(int32_t start, int32_t end, const TouchEventInfo& info) override;
    void OnTextGestureSelectionEnd(const TouchLocationInfo& locationInfo) override;
    void StartGestureSelection(int32_t start, int32_t end, const Offset& startOffset) override;

    void SetImageNodeGesture(RefPtr<ImageSpanNode> imageNode);
    virtual std::pair<int32_t, int32_t> GetStartAndEnd(int32_t start, const RefPtr<SpanItem>& spanItem);
    void HandleSpanStringTouchEvent(TouchEventInfo& info);
    void ShowAIEntityPreviewMenuTimer();
    bool enabled_ = true;
    Status status_ = Status::NONE;
    bool contChange_ = false;
    int32_t recoverStart_ = 0;
    int32_t recoverEnd_ = 0;
    bool aiSpanHoverEventInitialized_ = false;
    bool mouseEventInitialized_ = false;
    bool spanMouseEventInitialized_ = false;
    bool isHover_ = false;
    bool panEventInitialized_ = false;
    bool clickEventInitialized_ = false;
    bool touchEventInitialized_ = false;
    bool focusInitialized_ = false;
    bool hoverInitialized_ = false;
    bool isSpanStringMode_ = false;
    RefPtr<MutableSpanString> styledString_;
    bool keyEventInitialized_ = false;

    RefPtr<FrameNode> dragNode_;
    RefPtr<LongPressEvent> longPressEvent_;
    // Deprecated: Use the selectOverlay_ instead.
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
    RefPtr<Clipboard> clipboard_;
    RefPtr<TextContentModifier> contentMod_;
    RefPtr<TextOverlayModifier> overlayMod_;
    CopyOptions copyOption_ = CopyOptions::None;
    std::vector<int32_t> symbolFontColorResObjIndexArr;

    std::u16string textForDisplay_;
    std::string paintInfo_ = "NA";
    std::string frameRecord_ = "NA";
    std::optional<TextStyle> textStyle_;
    std::list<RefPtr<SpanItem>> spans_;
    mutable std::list<RefPtr<UINode>> childNodes_;
    float baselineOffset_ = 0.0f;
    int32_t placeholderCount_ = 0;
    SelectMenuInfo selectMenuInfo_;
    std::vector<RectF> dragBoxes_;
    std::map<std::pair<TextSpanType, TextResponseType>, std::shared_ptr<SelectionMenuParams>> selectionMenuMap_;
    std::optional<TextSpanType> selectedType_;
    SourceType sourceType_ = SourceType::NONE;
    std::function<void(bool)> isFocusActiveUpdateEvent_;

    friend class TextContentModifier;
    // properties for AI
    bool textDetectEnable_ = false;
    RefPtr<DataDetectorAdapter> dataDetectorAdapter_ = MakeRefPtr<DataDetectorAdapter>();

    OffsetF parentGlobalOffset_;
    std::optional<TextResponseType> textResponseType_;

    struct SubComponentInfoEx {
        std::optional<AISpan> aiSpan;
        WeakPtr<SpanItem> span;
    };
    std::vector<SubComponentInfoEx> subComponentInfos_;
    virtual std::vector<RectF> GetSelectedRects(int32_t start, int32_t end);
    MouseFormat currentMouseStyle_ = MouseFormat::DEFAULT;
    RefPtr<MultipleClickRecognizer> multipleClickRecognizer_;
    bool ShowShadow(const PointF& textOffset, const Color& color);
    virtual PointF GetTextOffset(const Offset& localLocation, const RectF& contentRect);
    bool hasUrlSpan_ = false;
    WeakPtr<PipelineContext> pipeline_;
    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;
    bool IsSupportAskCelia();

private:
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleSpanLongPressEvent(GestureEvent& info);
    void HandleMouseEvent(const MouseInfo& info);
    void OnHandleTouchUp();
    void InitTouchEvent();
    void HandleTouchEvent(const TouchEventInfo& info);
    void ActSetSelection(int32_t start, int32_t end);
    bool IsShowHandle();
    void InitUrlMouseEvent();
    void InitUrlTouchEvent();
    void HandleUrlMouseEvent(const MouseInfo& info);
    void HandleUrlTouchEvent(const TouchEventInfo& info);
    void InitSpanStringTouchEvent();
    void URLOnHover(bool isHover);
    bool HandleUrlClick();
    Color GetUrlHoverColor();
    Color GetUrlPressColor();
    void SetAccessibilityAction();
    void SetSpanEventFlagValue(
        const RefPtr<UINode>& code, bool& isSpanHasClick, bool& isSpanHasLongPress);
    void CollectSymbolSpanNodes(const RefPtr<SpanNode>& spanNode, const RefPtr<UINode>& node);
    void CollectSpanNodes(std::stack<SpanNodeInfo> nodes, bool& isSpanHasClick, bool& isSpanHasLongPress);
    void CollectTextSpanNodes(const RefPtr<SpanNode>& child, bool& isSpanHasClick, bool& isSpanHasLongPress);
    void UpdateContainerChildren(const RefPtr<UINode>& parent, const RefPtr<UINode>& child);
    RefPtr<RenderContext> GetRenderContext();
    void UpdateRectForSymbolShadow(RectF& rect, float offsetX, float offsetY, float blurRadius) const;
    void ProcessBoundRectByTextShadow(RectF& rect);
    void FireOnSelectionChange(int32_t start, int32_t end);
    void FireOnMarqueeStateChange(const TextMarqueeState& state);
    void HandleMouseLeftButton(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseRightButton(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftPressAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftReleaseAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftMoveAction(const MouseInfo& info, const Offset& textOffset);
    void InitSpanItemEvent(bool& isSpanHasClick, bool& isSpanHasLongPress);
    void InitSpanItem(std::stack<SpanNodeInfo> nodes);
    int32_t GetSelectionSpanItemIndex(const MouseInfo& info);
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType);
    void ProcessBoundRectByTextMarquee(RectF& rect);
    ResultObject GetBuilderResultObject(RefPtr<UINode> uiNode, int32_t index, int32_t start, int32_t end);
    void CreateModifier();

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;
    void ProcessOverlayAfterLayout();
    // SpanString
    void MountImageNode(const RefPtr<ImageSpanItem>& imageItem);
    void ProcessSpanString();
    // to check if drag is in progress
    void SetCurrentDragTool(SourceTool tool)
    {
        lastDragTool_ = tool;
    }

    std::optional<RenderContext::ContextParam> GetContextParam() const override
    {
        return RenderContext::ContextParam { .type = RenderContext::ContextType::CANVAS,
                                             .surfaceName = std::nullopt };
    }

    SourceTool GetCurrentDragTool() const
    {
        return lastDragTool_;
    }

    Offset ConvertGlobalToLocalOffset(const Offset& globalOffset);
    Offset ConvertLocalOffsetToParagraphOffset(const Offset& offset);
    void ProcessMarqueeVisibleAreaCallback();
    void ParseOriText(const std::u16string& currentText);
    bool IsMarqueeOverflow() const;
    virtual void ResetAfterTextChange();
    bool GlobalOffsetInSelectedArea(const Offset& globalOffset);
    bool LocalOffsetInSelectedArea(const Offset& localOffset);
    bool LocalOffsetInRange(const Offset& localOffset, int32_t start, int32_t end);
    void HandleOnCopyWithoutSpanString(const std::string& pasteData);
    void CheckPressedSpanPosition(const Offset& textOffset);
    void EncodeTlvNoChild(const std::string& pasteData, std::vector<uint8_t>& buff);
    void EncodeTlvFontStyleNoChild(std::vector<uint8_t>& buff);
    void EncodeTlvTextLineStyleNoChild(std::vector<uint8_t>& buff);
    void EncodeTlvSpanItems(const std::string& pasteData, std::vector<uint8_t>& buff);
    RefPtr<SpanItem> FindSpanItemByOffset(const PointF& textOffset);
    void UpdateMarqueeStartPolicy();
    void PauseSymbolAnimation();
    void ResumeSymbolAnimation();
    bool IsLocationInFrameRegion(const Offset& localOffset) const;
    void RegisterFormVisibleChangeCallback();
    void RegisterVisibleAreaChangeCallback();
    void HandleFormVisibleChange(bool visible);
    void RemoveFormVisibleChangeCallback(int32_t id);
    void GetSpanItemAttributeUseForHtml(NG::FontStyle& fontStyle,
        NG::TextLineStyle& textLineStyle, const std::optional<TextStyle>& textStyle);
    RefPtr<TaskExecutor> GetTaskExecutorItem();
    void AsyncHandleOnCopySpanStringHtml(RefPtr<SpanString>& subSpanString);
    void AsyncHandleOnCopyWithoutSpanStringHtml(const std::string& pasteData);
    std::list<RefPtr<SpanItem>> GetSpanSelectedContent();
    bool RegularMatchNumbers(const std::u16string& content);

    bool isMeasureBoundary_ = false;
    bool isMousePressed_ = false;
    bool leftMousePressed_ = false;
    bool isCustomFont_ = false;
    bool blockPress_ = false;
    bool isDoubleClick_ = false;
    bool showSelected_ = false;
    bool isSensitive_ = false;
    bool hasSpanStringLongPressEvent_ = false;
    int32_t clickedSpanPosition_ = -1;
    Offset leftMousePressedOffset_;
    bool isEnableHapticFeedback_ = true;

    bool urlTouchEventInitialized_ = false;
    bool urlMouseEventInitialized_ = false;
    bool spanStringTouchInitialized_ = false;
    bool moveOverClickThreshold_ = false;
    bool isMarqueeRunning_ = false;

    RefPtr<ParagraphManager> pManager_;
    RefPtr<TextEffect> textEffect_;
    std::vector<int32_t> placeholderIndex_;
    std::vector<RectF> rectsForPlaceholders_;
    OffsetF imageOffset_;

    OffsetF contentOffset_;
    GestureEventFunc onClick_;
    double distanceThreshold_ = std::numeric_limits<double>::infinity();
    RefPtr<DragWindow> dragWindow_;
    RefPtr<DragDropProxy> dragDropProxy_;
    RefPtr<PreviewMenuController> previewController_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    SourceTool lastDragTool_ = SourceTool::UNKNOWN;
    std::optional<int32_t> surfacePositionChangedCallbackId_;
    int32_t dragRecordSize_ = -1;
    RefPtr<TextController> textController_;
    TextSpanType oldSelectedType_ = TextSpanType::NONE;
    bool isShowMenu_ = true;
    RefPtr<TextSelectOverlay> selectOverlay_;
    std::vector<WeakPtr<FrameNode>> imageNodeList_;
    bool isDetachFromMainTree_ = false;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder_;
    std::optional<void*> externalParagraph_;
    std::optional<ParagraphStyle> externalParagraphStyle_;
    bool isUserSetResponseRegion_ = false;
    WeakPtr<ScrollablePattern> scrollableParent_;
    ACE_DISALLOW_COPY_AND_MOVE(TextPattern);
    std::optional<std::function<void()>> afterLayoutCallback_;
    Offset lastLeftMouseMoveLocation_;
    bool isAutoScrollByMouse_ = false;
    bool shiftFlag_ = false;
    std::string textDetectTypes_ = "";
    // Used to record original caret position for "shift + up/down"
    // Less than 0 is invalid, initialized as invalid in constructor
    OffsetF originCaretPosition_;
    bool hasRegisterFormVisibleCallback_ = false;
    // params for ai/url entity dragging
    // left mouse click(lastLeftMouseClickStyle_ = true) ==> dragging(isTryEntityDragging_ = true)
    MouseFormat lastLeftMouseClickStyle_ = MouseFormat::DEFAULT;
    bool isTryEntityDragging_ = false;
    bool isShowAIMenuOption_ = false;
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions_;
    bool isRegisteredAreaCallback_ = false;
    bool isAskCeliaEnabled_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
