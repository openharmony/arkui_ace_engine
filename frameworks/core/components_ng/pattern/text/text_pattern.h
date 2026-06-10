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
#include "ui/base/macros.h"

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
#include "core/components_ng/pattern/text/span/span_group_hash_calculator.h"
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
#include "core/components_ng/pattern/rich_editor/lru_cache.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MAX_SIZE_OF_LOG = 2000;
}

struct ParagraphCacheInfo;
class InspectorFilter;
class PreviewMenuController;
class OneStepDragController;
class TextSelectionChild;
struct SelectionCopyPayload;
enum class Status { DRAGGING, FLOATING, ON_DROP, NONE };
using CalculateHandleFunc = std::function<void()>;
using ShowSelectOverlayFunc = std::function<void(const RectF&, const RectF&)>;
using ExternalDrawCallback = std::function<bool(const ExternalDrawCallbackInfo&)>;
struct SpanNodeInfo {
    RefPtr<UINode> node;
    RefPtr<UINode> containerSpanNode;
};
enum class SelectionMenuCalblackId { MENU_APPEAR, MENU_SHOW, MENU_HIDE };

// TextPattern is the base class for text render node to perform paint text.
class ACE_FORCE_EXPORT TextPattern : public virtual Pattern,
                    public TextDragBase,
                    public TextBase,
                    public TextGestureSelector,
                    public Magnifier,
                    public LayoutInfoInterface {
    DECLARE_ACE_TYPE(TextPattern, Pattern, TextDragBase, TextBase, TextGestureSelector, Magnifier);

public:
    TextPattern();
    ~TextPattern() override;
    virtual RefPtr<FrameNode> GetContentHost() const;
    RefPtr<LRUMap<uint64_t, ParagraphCacheInfo>> GetParagraphCache() { return paragraphCache_; }
    void SetParagraphCache(const RefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>& cache) { paragraphCache_ = cache; }
    const SpanGroupHashResult* GetSpanGroupHashResult() const { return spanGroupHashResult_.get(); }
    
    void InitParagraphCache();

    SelectionInfo GetSpansInfo(int32_t start, int32_t end, GetSpansMethod method);
    std::list<ResultObject> GetSpansInfoInStyledString(int32_t start, int32_t end);
    virtual int32_t GetTextContentLength();
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override;
    RefPtr<EventHub> CreateEventHub() override;
    virtual bool IsDragging() const;
    bool IsAtomicNode() const override;
    bool IsTextNode() const;
    bool DefaultSupportDrag() override;
    void OnModifyDone() override;
    void OnWindowHide() override;
    void OnWindowShow() override;
    void OnLanguageConfigurationUpdate() override;
    bool CheckMeasureFlag();
    void PreCreateLayoutWrapper();
    void BeforeCreateLayoutWrapper() override;
    void AddChildSpanItem(const RefPtr<UINode>& child);
    void SetSpanItemEvent(const RefPtr<SpanItem>& spanItem, RefPtr<FocusHub>& focusHub);
    void AddImageToSpanItem(const RefPtr<UINode>& child);
    FocusPattern GetFocusPattern() const override;
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
    void DumpTextStyleInfo5();
    void DumpInfoRes();
    void DumpSpanItem();
    void DumpScaleInfo();
    void DumpTextEngineInfo();

    bool NeedReadFontScaleFromEnv() override
    {
        return true;
    }

    void DumpParagraphsInfo();
    TextSelector GetTextSelector() const;
    const std::u16string& GetTextForDisplay() const;
    const OffsetF& GetStartOffset() const;
    const OffsetF& GetEndOffset() const;
    double GetSelectHeight() const;
    void GetGlobalOffset(Offset& offset);
    RectF GetTextContentRect(bool isActualText = false) const override;
    float GetBaselineOffset() const;
    RefPtr<TextContentModifier> GetContentModifier();
    virtual void SetTextDetectEnable(bool enable);
    // --------------- select AI detect -------------------
    bool MaybeNeedShowSelectAIDetect();
    void SetSelectDetectEnable(bool value);
    bool GetSelectDetectEnable();
    void ResetSelectDetectEnable();
    void SetSelectDetectConfig(std::vector<TextDataDetectType>& types) {}
    std::vector<TextDataDetectType> GetSelectDetectConfig();
    void ResetSelectDetectConfig() {}
    void SelectAIDetect();
    // --------------- select AI detect end -------------------
    void SetTextDetectEnableMultiThread(bool enable);
    bool GetTextDetectEnable();
    void SetTextDetectTypes(const std::string& types);
    std::string GetTextDetectTypes();
    RefPtr<DataDetectorAdapter> GetDataDetectorAdapter();
    RefPtr<DataDetectorAdapter> GetSelectDetectorAdapter();
    virtual const std::map<int32_t, AISpan>& GetAISpanMap();
    const std::u16string& GetTextForAI();
    void SetOnResult(std::function<void(const std::string&)>&& onResult);
    TextDataDetectResult GetTextDetectResult();
    virtual void MarkAISpanStyleChanged();
    void ClickAIMenuOptions(const AISpan& aiSpan,
        const std::pair<std::string, FuncVariant>& menuOption)
    {
        CHECK_NULL_VOID(dataDetectorAdapter_);
        dataDetectorAdapter_->OnClickAIMenuOption(aiSpan, menuOption);
    }
    void SetTextDetectConfig(const TextDetectConfig& textDetectConfig);
    void SetTextDetectConfigMultiThread(const TextDetectConfig& textDetectConfig);
    void ModifyAISpanStyle(TextStyle& aiSpanStyle);
    void OnVisibleChange(bool isVisible) override;
    void OnVisibleAreaChange(bool isVisible);
    std::list<RefPtr<SpanItem>> GetSpanItemChildren();
    int32_t GetPlaceholderCount();
    int32_t GetDisplayWideTextLength();

    // ===========================================================
    bool IsTextArea() const override;
    const RectF& GetTextRect() const override;
    float GetLineHeight() const override;
    std::vector<RectF> GetTextBoxes() override;
    OffsetF GetParentGlobalOffset() const override;
    const RefPtr<FrameNode>& MoveDragNode() override;
    const RefPtr<Paragraph>& GetDragParagraph() const override;
    bool CloseKeyboard(bool /* forceClose */) override;
    virtual void CloseSelectOverlay() override;
    void CloseSelectOverlay(bool animation);
    void CloseSelectOverlayMultiThread(bool animation);
    void CreateHandles() override;
    bool BetweenSelectedPosition(const Offset& globalOffset) override;
    bool BetweenContainerSelectedPosition(const Offset& globalOffset);

    // end of TextDragBase implementations
    // ===========================================================

    void InitSurfaceChangedCallback();
    void InitSurfacePositionChangedCallback();
    virtual void HandleSurfaceChanged(
        int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight);
    virtual void HandleSurfacePositionChanged(int32_t posX, int32_t posY) {};
    bool HasSurfaceChangedCallback();
    void UpdateSurfaceChangedCallbackId(int32_t id);
    bool HasSurfacePositionChangedCallback();
    void UpdateSurfacePositionChangedCallbackId(int32_t id);
    void SetOnClickEvent(GestureEventFunc&& onClick,
        double distanceThreshold = std::numeric_limits<double>::infinity());
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
    const std::vector<std::u16string>& GetDragContents() const;
    void InitSpanImageLayout(const std::vector<int32_t>& placeholderIndex,
        const std::vector<RectF>& rectsForPlaceholders, OffsetF contentOffset) override;
    const std::vector<int32_t>& GetPlaceHolderIndex();
    const std::vector<RectF>& GetRectsForPlaceholders();
    OffsetF GetContentOffset() override;
    bool IsMeasureBoundary() const override;
    void SetIsMeasureBoundary(bool isMeasureBoundary);
    void SetIsCustomFont(bool isCustomFont);
    bool GetIsCustomFont();
    void SetImageSpanNodeList(std::vector<WeakPtr<FrameNode>> imageNodeList);
    std::vector<WeakPtr<FrameNode>> GetImageSpanNodeList();
    // Deprecated: Use the TextSelectOverlay::ProcessOverlay() instead.
    // It is currently used by RichEditorPattern.
    ACE_FORCE_EXPORT virtual void UpdateSelectOverlayOrCreate(SelectOverlayInfo& selectInfo, bool animation = false);
    // Deprecated: Use the TextSelectOverlay::CheckHandleVisible() instead.
    // It is currently used by RichEditorPattern.
    virtual void CheckHandles(SelectHandleInfo& handleInfo) {};
    ACE_FORCE_EXPORT OffsetF GetDragUpperLeftCoordinates() override;
    void SetTextSelection(int32_t selectionStart, int32_t selectionEnd);
    void SetTextSelectionMultiThread(int32_t selectionStart, int32_t selectionEnd);
    bool ParseCommand(const std::string& command);

    // Deprecated: Use the TextSelectOverlay::OnHandleMove() instead.
    // It is currently used by RichEditorPattern.
    ACE_FORCE_EXPORT void OnHandleMove(const RectF& handleRect, bool isFirstHandle) override;
    virtual std::vector<ParagraphManager::ParagraphInfo> GetParagraphs() const;
    const RefPtr<ParagraphManager>& GetParagraphManager() const;
    void MarkContentChange();
    void ResetContChange();
    bool GetContChange() const;
    bool GetShowSelect() const;
    int32_t GetRecoverStart() const;
    int32_t GetRecoverEnd() const;
    ACE_FORCE_EXPORT void OnHandleAreaChanged() override;
    void RemoveAreaChangeInner();
    void ResetDragOption() override;
    virtual bool NeedShowAIDetect();
    bool IsAIDetectInitialized();
    int32_t GetDragRecordSize() override;
    void ResetDragRecordSize(int32_t size);

    void BindSelectionMenu(TextSpanType spanType, TextResponseType responseType, std::function<void()>& menuBuilder,
        const SelectMenuParam& menuParam);
    void BindPreviewMenu(TextSpanType spanType, std::function<void()>& menuBuilder, const SelectMenuParam& menuParam);
    void UnBindPreviewMenu();
    bool GetIsTouchPressed() const
    {
        return isTouchPressed_;
    }
    void IfStartVibratorByLongPress();
    void UnBindPreviewMenuByCopyOption();
    void SetEnableEventResponse();
    void HandleImageDrag(const RefPtr<ImageSpanNode>& imageNode);
    void DisableDrag(const RefPtr<ImageSpanNode>& imageNode);
    void FillPreviewMenuInJsonOneStep(const std::unique_ptr<JsonValue>& jsonValue) const;
    void SetTextController(const RefPtr<TextController>& controller);
    const RefPtr<TextController>& GetTextController();
    void CloseSelectionMenu();
    void ClearSelectionMenu();
    virtual const std::list<RefPtr<UINode>>& GetAllChildren() const;
    void StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex);
    void HandleSelectionChange(int32_t start, int32_t end);
    CopyOptions GetCopyOptions() const;
    bool IsTextInSelectionContainer() const;
    bool CheckClickedOnSpanOrText(RectF textContentRect, const Offset& localLocation);
    void SetSpanItemChildren(const std::list<RefPtr<SpanItem>>& spans);
    void SetSpanStringMode(bool isSpanStringMode);
    bool GetSpanStringMode() const;
    void AllocStyledString();
    void SetSelectionFlag(int32_t selectionStart, int32_t selectionEnd, const SelectionOptions options);
    void ActSetSelectionFlag(int32_t selectionStart, int32_t selectionEnd, const SelectionOptions options);
    bool IsShowMenu(MenuPolicy options, bool defaultValue);
    void SetStyledString(const RefPtr<SpanString>& value, bool closeSelectOverlay = true, bool isReplace = false);
    void SetStyledStringMultiThread(const RefPtr<SpanString>& value,
        bool closeSelectOverlay = true, bool isReplace = false);
    // select overlay
    virtual int32_t GetHandleIndex(const Offset& offset) const;
    std::u16string GetSelectedText(int32_t start, int32_t end, bool includeStartHalf = false,
        bool includeEndHalf = false, bool getSubstrDirectly = false) const;
    void UpdateSelectionSpanType(int32_t selectStart, int32_t selectEnd);
    virtual void CalculateHandleOffsetAndShowOverlay(bool isUsingMouse = false);
    void ResetSelection();
    virtual bool IsSelectAll();
    void HandleOnCopy();
    virtual void HandleAIMenuOption(const std::string& labelInfo = "");
    virtual void HandleOnAskCelia();
    void SetIsAskCeliaEnabled(bool isAskCeliaEnabled);
    bool IsAskCeliaEnabled() const;
    void SetIsShowAskCeliaInRightClick(bool isShowAskCeliaInRightClick);
    bool IsShowAskCeliaInRightClick() const;
    bool IsAskCeliaSupported();
    void HandleOnCopySpanString();
    SelectionCopyPayload GetSelectionCopyPayload();
    RefPtr<SpanString> GetSelectedSpanString();
    void SetDirectlyCreatedByTextModel(bool value) { directlyCreatedByTextModel_ = value; }
    virtual void HandleOnSelectAll();
    bool IsShowTranslate();
    bool IsShowSearch();
    void SetTextSelectableMode(TextSelectableMode value);
    OffsetF GetTextPaintOffset() const override;
    void SaveOldSelectedType();
    void SetTextResponseType(TextResponseType type);
    bool IsSelectedTypeChange();
    bool CheckSelectedTypeChange();
    bool IsUsingMouse();
    ACE_FORCE_EXPORT void OnSensitiveStyleChange(bool isSensitive) override;
    bool IsSetObscured() const;
    bool IsSensitiveEnable();
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo);
    void InitCustomSpanPlaceholderInfo(const std::vector<CustomSpanPlaceholderInfo>& customSpanPlaceholder);
    std::vector<CustomSpanPlaceholderInfo> GetCustomSpanPlaceholderInfo();
    TextSelectionOptions GetTextSelectionOptions();
    void ClearCustomSpanPlaceholderInfo();
    const std::list<RefPtr<UINode>>& GetChildNodes() const;
    void SetExternalParagraph(void* paragraph);
    const std::optional<void*>& GetExternalParagraph();
    void SetExternalSpanItem(const std::list<RefPtr<SpanItem>>& spans);
    void SetExternalSpanItemMultiThread(const std::list<RefPtr<SpanItem>>& spans);
    void SetExternalParagraphStyle(const std::optional<ParagraphStyle>& paragraphStyle);
    TextStyle GetTextStyle();
    ACE_FORCE_EXPORT bool DidExceedMaxLines() const override;
    bool IsOnlyFontSizeOrColorChanged();
    std::optional<ParagraphStyle> GetExternalParagraphStyle() const;
    size_t GetLineCount() const override;
    TextLineMetrics GetLineMetrics(int32_t lineNumber) override;
    std::vector<ParagraphManager::TextBox> GetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle) override;
    PositionWithAffinity GetGlyphPositionAtCoordinate(int32_t x, int32_t y) override;
    PositionWithAffinity GetCharacterPositionAtCoordinate(int32_t x, int32_t y) override;
    std::pair<TextRange, TextRange> GetGlyphRangeForCharacterRange(int32_t start, int32_t end) override;
    std::pair<TextRange, TextRange> GetCharacterRangeForGlyphRange(int32_t start, int32_t end) override;

    void OnSelectionMenuOptionsUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);
    void OnCreateMenuCallbackUpdate(const NG::OnCreateMenuCallback&& onCreateMenuCallback);
    void OnMenuItemClickCallbackUpdate(const NG::OnMenuItemClickCallback&& onMenuItemClick);
    void OnPrepareMenuCallbackUpdate(const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);
    void OnFrameNodeChanged(FrameNodeChangeInfoFlag flag) override;
    void UpdateParentGlobalOffset();
    void DumpRecord(const std::string& record, bool stateChange = false);
    void LogForFormRender(const std::string& logTag);
    void SetIsUserSetResponseRegion(bool isUserSetResponseRegion);
    size_t GetSubComponentInfos(std::vector<SubComponentInfo>& subComponentInfos);
    void ACE_FORCE_EXPORT UpdateFontColor(const Color& value);
    ACE_FORCE_EXPORT void BeforeCreatePaintWrapper() override;
    void OnTextOverflowChanged();
    void MarkDirtyNodeRender();
    void MarkDirtyNodeMeasure();
    void ChangeHandleHeight(const GestureEvent& event, bool isFirst, bool isOverlayMode);
    void ChangeFirstHandleHeight(const Offset& touchOffset, RectF& handleRect);
    void ChangeSecondHandleHeight(const Offset& touchOffset, RectF& handleRect);
    virtual void CalculateDefaultHandleHeight(float& height);
    uint64_t GetSystemTimestamp();
    void SetEnableHapticFeedback(bool isEnabled, bool flagByUser);
    bool HasContent();
    virtual bool IsEnabledObscured() const;
    void SetupMagnifier();
    ACE_FORCE_EXPORT void DoTextSelectionTouchCancel() override;
    virtual Color GetUrlSpanColor();
    ACE_FORCE_EXPORT void BeforeSyncGeometryProperties(const DirtySwapConfig& config) override;
    void RegisterAfterLayoutCallback(std::function<void()> callback);
    void UnRegisterAfterLayoutCallback();
    RefPtr<MagnifierController> GetOrCreateMagnifier();
    void StyledStringRegisterResource();
    ACE_FORCE_EXPORT void UnRegisterResource(const std::string& key) override;
    void EmplaceSymbolColorIndex(int32_t index);
    std::string GetCaretColor() const;
    std::string GetSelectedBackgroundColor() const;
    std::optional<Color> GetSelectedBgColorWhenAcrossText() const;
    void ResetCustomFontColor();
    void OnColorConfigurationUpdate() override;
    void OnColorModeChange(uint32_t colorMode) override;
    bool OnThemeScopeUpdate(int32_t themeScopeId) override;
    void OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type) override;
    bool GetOriginCaretPosition(OffsetF& offset) const;
    void ResetOriginCaretPosition();
    bool RecordOriginCaretPosition(const OffsetF& offset);
    TextDragInfo CreateTextDragInfo();
    void SetIsShowAIMenuOption(bool isShowAIMenuOption);
    bool IsShowAIMenuOption() const;
    void SetAIItemOption(const std::unordered_map<TextDataDetectType, AISpan>& aiMenuOptions);
    const std::unordered_map<TextDataDetectType, AISpan>& GetAIItemOption() const;
    virtual void UpdateAIMenuOptions();
    bool PrepareAIMenuOptions(std::unordered_map<TextDataDetectType, AISpan>& aiMenuOptions);
    bool IsAiSelected();
    virtual RefPtr<FrameNode> CreateAIEntityMenu();
    virtual bool CheckAIPreviewMenuEnable();
    void InitAiSelection(const Offset& globalOffset);
    bool PressOnEllipsisTextRange(const Offset& localOffset);
    ACE_FORCE_EXPORT bool CanAIEntityDrag() override;
    RefPtr<PreviewMenuController> GetOrCreatePreviewMenuController();
    ACE_FORCE_EXPORT void ResetAISelected(AIResetSelectionReason reason) override;
    std::function<void()> GetPreviewMenuAISpanClickrCallback(const AISpan& aiSpan);
    ACE_FORCE_EXPORT void ShowAIEntityMenuForCancel() override;
    ACE_FORCE_EXPORT bool IsPreviewMenuShow() override;
    void DragNodeDetachFromParent();
    AISpan GetSelectedAIData();
    std::pair<bool, bool> GetCopyAndSelectable();
    std::pair<int32_t, int32_t> GetSelectedStartAndEnd();
    RefPtr<TextEffect> GetTextEffect();
    RefPtr<TextEffect> GetOrCreateTextEffect(const std::u16string& content, bool& needUpdateTypography);
    void RelayoutResetOrUpdateTextEffect();
    void ResetTextEffect();
    bool ResetTextEffectBeforeLayout(bool onlyReset = true);
    bool IsNeedAskCelia() const;
    void UpdateTextSelectorSecondHandle(const RectF& rect);
    bool IsEnableMatchParent() override;
    void SetExternalDrawCallback(ExternalDrawCallback&& callback);
    const ExternalDrawCallback& GetExternalDrawCallback();
    std::optional<void*> GetDrawParagraph();
    void UpdateStyledStringByColorMode(bool needUpdateSpanStyleHash = true);
    virtual void MarkContentNodeForRender() {};
    float TextContentAlignOffsetY();
    bool AllowVisibleAreaCheck() const override;

    ACE_FORCE_EXPORT std::vector<std::pair<float, float>> GetSpecifiedContentOffsets(
        const std::string& content) override;
    std::vector<int32_t> GetSpecifiedContentIndex(const std::string& content, bool isFirst = false) const;
    ACE_FORCE_EXPORT void HighlightSpecifiedContent(
        const std::string& content, const std::vector<std::string>& nodeIds, const std::string& configs) override;
    void ResetHighLightValue();
    ACE_FORCE_EXPORT void ReportSelectedText(bool isRegister = false) override;
    void MarkMeasured(bool isMeasured);
    bool IsMeasured() const;
    ACE_FORCE_EXPORT int32_t OnInjectionEvent(const std::string& command) override;
    bool GetFallbackLineSpacingStyleOptimizeFlag();
    bool SetFallbackLineSpacingAndIncludeFontPadding(bool flag);
    virtual void ClearParagraphCache() {};

    void BindJSTextController(std::function<void()>&& bindFunc) {
        jsTextControllerBinder_ = std::move(bindFunc);
    }
protected:
    virtual RefPtr<TextSelectOverlay> GetOrCreateSelectOverlay();
    virtual RefPtr<TextSelectOverlay> GetSelectOverlay() const;
    int32_t GetClickedSpanPosition();
    void OnAttachToFrameNode() override;
    void OnAttachToFrameNodeMultiThread();
    void OnDetachFromFrameNode(FrameNode* node) override;
    void OnDetachFromFrameNodeMultiThread(FrameNode* node);
    ACE_FORCE_EXPORT void OnAfterModifyDone() override;
    virtual bool ClickAISpan(const PointF& textOffset, const AISpan& aiSpan);
    ACE_FORCE_EXPORT virtual void InitAISpanHoverEvent();
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
    void RecoverCopyOption(CopyOptions copyOption);
    void OnContainerCopyOptionUpdate();
    CopyOptions CalcCopyOption();
    void RecoverEnableHapticFeedback();
    void RecoverEnableHapticFeedback(bool enableHapticFeedback);
    void OnContainerEnableHapticFeedbackUpdate();
    bool CalcEnableHapticFeedback();
    void RecoverSelectedBackgroundColor();
    void OnContainerSelectedBackgroundColorUpdate();
    Color CalcSelectedBackgroundColor();
    void InitCopyOptionAndOverlay();
    void InitDefaultTextDraggable();
    void InitCopyOption(const RefPtr<GestureEventHub>& gestureEventHub, const RefPtr<EventHub>& eventHub);
    void ClearTextDefaultDrag(const RefPtr<GestureEventHub>& gestureEventHub, const RefPtr<EventHub>& eventHub);
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
    void InitSelectionOnLongPress(const Offset& localOffset);
    bool TryLinkJump(const RefPtr<SpanItem>& span);
    void ActTextOnClick(GestureEvent& info);
    RectF CalcAIMenuPosition(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc);
    virtual RectF CalcAIEntityRectWithHandles();
    bool ShowAIEntityMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc = nullptr,
        const ShowSelectOverlayFunc& showSelectOverlayFunc = nullptr);
    void SetOnClickMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc,
        const ShowSelectOverlayFunc& showSelectOverlayFunc);
    bool IsDraggable(const Offset& localOffset);
    virtual void InitClickEvent(const RefPtr<GestureEventHub>& gestureHub);
    virtual void ProcessOverlay(const OverlayRequest& request = OverlayRequest());
    void ShowSelectOverlay(const OverlayRequest& = OverlayRequest());
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    ACE_FORCE_EXPORT virtual void UpdateSelectorOnHandleMove(
        const OffsetF& localOffset, float handleHeight, bool isFirstHandle);
    void CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity = TextAffinity::DOWNSTREAM);
    void UpdateSelectionType(const SelectionInfo& selection);
    void CopyBindSelectionMenuParams(SelectOverlayInfo& selectInfo, std::shared_ptr<SelectionMenuParams> menuParams);
    ACE_FORCE_EXPORT virtual void OnHandleSelectionMenuCallback(
        SelectionMenuCalblackId callbackId, std::shared_ptr<SelectionMenuParams> menuParams);
    bool IsSelectedBindSelectionMenu();
    bool CheckAndClick(const RefPtr<SpanItem>& item);
    bool CalculateClickedSpanPosition(const PointF& textOffset);
    bool SelectOverlayIsOn();
    bool IsSelectOverlayUsingMouse();
    void HideSelectionMenu(bool noAnimation = false, bool showSubMenu = false);
    void HiddenMenu();
    std::shared_ptr<SelectionMenuParams> GetMenuParams(TextSpanType type, TextResponseType responseType);
    void AddUdmfTxtPreProcessor(const ResultObject src, ResultObject& result, bool isAppend);
    void InitKeyEvent();
    void UpdateShiftFlag(const KeyEvent& keyEvent);
    bool HandleKeyEvent(const KeyEvent& keyEvent);
    bool HandleOnSelect(KeyCode code);
    void HandleSelectionUp();
    void HandleSelectionDown();
    void HandleSelection(bool isEmojiStart, int32_t end);
    double GetTextHeight(int32_t index, bool isNextLine);
    int32_t GetActualTextLength();
    bool IsSelectableAndCopy();
    void SetResponseRegion(const SizeF& frameSize, const SizeF& boundsSize);
    virtual bool CanStartAITask() const;
    virtual bool GetDefaultClipValue() const;
    void MarkDirtySelf();
    void OnAttachToMainTree() override;
    void OnAttachToMainTreeMultiThread();
    void OnDetachFromMainTree() override;
    void OnDetachFromMainTreeMultiThread();
    virtual void OnAttachToMainTreeMultiThreadExtension();
    void CreateMultipleClickRecognizer();
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
    ACE_FORCE_EXPORT int32_t GetTouchIndex(const OffsetF& offset) override;
    ACE_FORCE_EXPORT void OnTextGestureSelectionUpdate(int32_t start, int32_t end, const TouchEventInfo& info) override;
    ACE_FORCE_EXPORT void OnTextGestureSelectionEnd(const TouchLocationInfo& locationInfo) override;
    ACE_FORCE_EXPORT void StartGestureSelection(int32_t start, int32_t end, const Offset& startOffset) override;
    void SetImageNodeGesture(RefPtr<ImageSpanNode> imageNode);
    void SetImageNodePattern(RefPtr<ImageSpanNode> imageNode, const ImageSpanAttribute& imageSpanAttr);
    virtual std::pair<int32_t, int32_t> GetStartAndEnd(int32_t start, const RefPtr<SpanItem>& spanItem);
    void HandleSpanStringTouchEvent(TouchEventInfo& info);
    void ShowAIEntityPreviewMenuTimer();
    void PreviewDragNodeHideAnimation();
    RefPtr<MutableSpanString> styledString_;
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions_;
    RefPtr<FrameNode> dragNode_;
    RefPtr<LongPressEvent> longPressEvent_;
    // Deprecated: Use the selectOverlay_ instead.
    RefPtr<SelectOverlayProxy> selectOverlayProxy_;
    RefPtr<Clipboard> clipboard_;
    RefPtr<TextContentModifier> contentMod_;
    RefPtr<TextOverlayModifier> overlayMod_;
    std::vector<int32_t> symbolFontColorResObjIndexArr;
    std::u16string textForDisplay_;
    std::string frameRecord_ = "";
    std::optional<TextStyle> textStyle_;
    std::list<RefPtr<SpanItem>> spans_;
    mutable std::list<RefPtr<UINode>> childNodes_;
    std::vector<RectF> dragBoxes_;
    std::map<std::pair<TextSpanType, TextResponseType>, std::shared_ptr<SelectionMenuParams>> selectionMenuMap_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    friend class TextContentModifier;
    struct SubComponentInfoEx {
        std::optional<AISpan> aiSpan;
        WeakPtr<SpanItem> span;
    };
    // properties for AI
    RefPtr<DataDetectorAdapter> dataDetectorAdapter_;
    RefPtr<DataDetectorAdapter> selectDetectorAdapter_;
    OffsetF parentGlobalOffset_;
    std::vector<SubComponentInfoEx> subComponentInfos_;
    RefPtr<MultipleClickRecognizer> multipleClickRecognizer_;
    WeakPtr<PipelineContext> pipeline_;
    Status status_ = Status::NONE;
    CopyOptions copyOption_ = CopyOptions::None;
    SourceType sourceType_ = SourceType::NONE;
    MouseFormat currentMouseStyle_ = MouseFormat::DEFAULT;
    std::optional<TextResponseType> textResponseType_;
    std::optional<TextSpanType> selectedType_;
    TextSelectionOptions textSelectionOptions_ = {0, 0, MenuPolicy::DEFAULT};
    int32_t recoverStart_ = 0;
    int32_t recoverEnd_ = 0;
    int32_t placeholderCount_ = 0;
    float baselineOffset_ = 0.0f;
    bool enabled_ = true;
    bool contChange_ = false;
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
    bool keyEventInitialized_ = false;
    bool isShowAIMenuOption_ = false;
    bool isAskCeliaEnabled_ = false;
    bool isShowAskCeliaInRightClick_ = false;
    bool textDetectEnable_ = false;
    bool selectDetectEnabledIsUserSet_ = false;
    bool selectDetectEnabled_ = true;
    bool hasUrlSpan_ = false;
    virtual std::vector<RectF> GetSelectedRects(int32_t start, int32_t end);
    bool ShowShadow(const PointF& textOffset, const Color& color);
    virtual PointF GetTextOffset(const Offset& localLocation, const RectF& contentRect);
    void UpdatePropertyImpl(const std::string& key, RefPtr<PropertyValueBase> value) override;
    bool IsSupportAskCelia();
    void UpdateSelectionChildRegistration();
    void ClearSelectionChild();

private:
    void ReportSelectionChangeEvent(int32_t nodeId, const std::string& dataStr,
        const std::string& value, int32_t start, int32_t end);
    bool ReportCommandResult(int32_t nodeId, const std::string& event);
    void InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleSpanLongPressEvent(GestureEvent& info);
    void HandleMouseEvent(const MouseInfo& info);
    void OnHandleTouchUp();
    void InitTouchEvent();
    void HandleTouchEvent(const TouchEventInfo& info);
    void ActSetSelection(int32_t start, int32_t end);
    void RecordSelectedChildAndNotifyChange();
    virtual bool IsShowHandle();
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
    void HandleMouseLeftPressForLocal(const Offset& textOffset);
    bool HandleMouseLeftPressForContainer(const Offset& textOffset);
    void HandleMouseLeftReleaseAction(const MouseInfo& info, const Offset& textOffset);
    void HandleMouseLeftReleaseForLocal(const MouseInfo& info, MouseStatus oldMouseStatus, int32_t start, int32_t end);
    void HandleMouseLeftReleaseForContainer(
        const MouseInfo& info, const Offset& textOffset, MouseStatus oldMouseStatus, int32_t start, int32_t end);
    void ResetMouseReleaseState(const MouseInfo& info);
    void HandleMouseLeftMoveAction(const MouseInfo& info, const Offset& textOffset);
    void UpdateSourceType(SourceType sourceType);
    void SetMouseMenuOffset(const OffsetF& mouseMenuOffset);
    void SetSelectionHoldCallback();
    void UpdateSelectedTypeForRightClick(const MouseInfo& info);
    void InitSpanItemEvent(bool& isSpanHasClick, bool& isSpanHasLongPress);
    void InitSpanItem(std::stack<SpanNodeInfo> nodes);
    int32_t GetSelectionSpanItemIndex(const MouseInfo& info);
    bool ShouldUseDefaultTextDrag() const;
    void CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType);
    void ProcessBoundRectByTextMarquee(RectF& rect);
    ResultObject GetBuilderResultObject(RefPtr<UINode> uiNode, int32_t index, int32_t start, int32_t end);
    void CreateModifier();
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;
    ACE_FORCE_EXPORT void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override;
    void ProcessOverlayAfterLayout();
    void FlushContainerOverlayAfterLayout();
    // SpanString
    void MountImageNode(const RefPtr<ImageSpanItem>& imageItem);
    void ProcessSpanString();
    void SetCurrentDragTool(SourceTool tool);
    std::optional<RenderContext::ContextParam> GetContextParam() const override;
    SourceTool GetCurrentDragTool() const;
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
    void GetSpanItemAttributeUseForHtml(NG::FontStyle& fontStyle, NG::TextLineStyle& textLineStyle,
        NG::SymbolStyle& symbolStyle, const std::optional<TextStyle>& textStyle);
    RefPtr<TaskExecutor> GetTaskExecutorItem();
    void AsyncHandleOnCopySpanStringHtml(RefPtr<SpanString>& subSpanString);
    void AsyncHandleOnCopyWithoutSpanStringHtml(const std::string& pasteData);
    std::list<RefPtr<SpanItem>> GetSpanSelectedContent();
    bool RegularMatchNumbers(const std::u16string& content);
    void ResetMouseLeftPressedState();

    void UpdateSpanGroupHash(const std::list<RefPtr<SpanItem>>& spans);
    void UpdateSpanStyleHash(const std::list<RefPtr<SpanItem>>& spans);

    void GetPaintOffsetWithoutTransform(OffsetF& paintOffset);
    bool IsTriggerParentToScroll();
    bool HasScrollableParent();
    bool HasOrUpdateRenderTransform(bool needCreate = false);
    void DisableSelectMenu();
    void UpdateAISelectMenu();
    bool IsCurrentMenuVisibile();
    bool IsHandleDragging();
    bool IsClickAtHandle(const GestureEvent& info);
    bool IsTouchAtHandle(const TouchEventInfo& info);
    bool IsShowMouseMenu();
    void ContentChangeByDetaching(PipelineContext*) override;
    void HighlightDisappearAnimation();
    void HighlightAppearAnimation();
    bool HighlightTriggerScrollableParentToScroll(const RectF& highlightRect);
    float CalculateScrollTargetOffset(
        const RefPtr<ScrollablePattern>& scrollablePattern, const RectF& highlightInScroll, const RectF& frameRect);
    const RefPtr<ScrollablePattern> FindScrollableParentWithRelativeOffset(OffsetF& offset);
    RectF GetHighlightRect(const std::vector<std::pair<std::vector<RectF>, ParagraphStyle>>& paragraphsRects) const;
    std::u16string GetContentWithPlaceholderSpaceFillter() const;
    std::u16string TextHighlightSelectedContent(int32_t start, int32_t end) const;
    void UpdateLpxUnitFlag();

    RefPtr<ParagraphManager> pManager_;
    RefPtr<TextEffect> textEffect_;
    RefPtr<PreviewMenuController> previewController_;
    RefPtr<TextController> textController_;
    RefPtr<TextSelectOverlay> selectOverlay_;
    RefPtr<TextSelectionChild> selectionChild_;
    std::vector<int32_t> placeholderIndex_;
    std::vector<RectF> rectsForPlaceholders_;
    std::vector<WeakPtr<FrameNode>> imageNodeList_;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder_;
    std::optional<int32_t> surfaceChangedCallbackId_;
    std::optional<int32_t> surfacePositionChangedCallbackId_;
    std::optional<void*> externalParagraph_;
    std::unique_ptr<ParagraphStyle> externalParagraphStyle_;
    WeakPtr<ScrollablePattern> scrollableParent_;
    std::optional<std::function<void()>> afterLayoutCallback_;
    GestureEventFunc onClick_;
    ExternalDrawCallback externalDrawCallback_;
    std::shared_ptr<AnimationUtils::Animation> highlightAppearAnimation_;
    std::shared_ptr<AnimationUtils::Animation> highlightDisappearAnimation_;
    std::string textDetectTypes_ = "";
    Offset leftMousePressedOffset_;
    OffsetF imageOffset_;
    Offset lastLeftMouseMoveLocation_;
    // Used to record original caret position for "shift + up/down"
    // Less than 0 is invalid, initialized as invalid in constructor
    OffsetF originCaretPosition_;
    OffsetF gestureSelectTextPaintOffset_;
    double distanceThreshold_ = std::numeric_limits<double>::infinity();
    SourceTool lastDragTool_ = SourceTool::UNKNOWN;
    int32_t clickedSpanPosition_ = -1;
    int32_t dragRecordSize_ = -1;
    TextSpanType oldSelectedType_ = TextSpanType::NONE;
    Color selectedBackgroundColor_;
    // params for ai/url entity dragging
    // left mouse click(lastLeftMouseClickStyle_ = true) ==> dragging(isTryEntityDragging_ = true)
    MouseFormat lastLeftMouseClickStyle_ = MouseFormat::DEFAULT;
    int32_t highlightAppearAnimationId_ = 0;
    int32_t highlightDisappearAnimationId_ = 0;
    bool isMeasureBoundary_ = false;
    bool isTouchPressed_ = false;
    bool isMousePressed_ = false;
    bool leftMousePressed_ = false;
    bool isCustomFont_ = false;
    bool blockPress_ = false;
    bool isDoubleClick_ = false;
    bool isSensitive_ = false;
    bool hasSpanStringLongPressEvent_ = false;
    bool isEnableHapticFeedback_ = true;
    bool hapticFeedbackFlagByUser_ = false;
    bool directlyCreatedByTextModel_ = false;
    bool isContainerOverlayDirtyAfterLayout_ = false;
    bool mouseUpAndDownPointChange_ = false;
    bool urlTouchEventInitialized_ = false;
    bool urlMouseEventInitialized_ = false;
    bool spanStringTouchInitialized_ = false;
    bool moveOverClickThreshold_ = false;
    bool isMarqueeRunning_ = false;
    bool isShowMenu_ = true;
    bool isDetachFromMainTree_ = false;
    bool isUserSetResponseRegion_ = false;
    bool isAutoScrollByMouse_ = false;
    bool shiftFlag_ = false;
    bool hasRegisterFormVisibleCallback_ = false;
    bool isTryEntityDragging_ = false;
    bool isRegisteredAreaCallback_ = false;
    bool isMeasured_ = false;
    bool hasLpxUnitStyle_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(TextPattern);
    friend class OneStepDragController;
    friend class TextSelectionChild;
    std::unique_ptr<OneStepDragController> oneStepDragController_;

    // ----- multi thread state variables -----
    // ----- multi thread state variables end -----


    //hash for span string
    std::unique_ptr<SpanGroupHashResult> spanGroupHashResult_;
    RefPtr<LRUMap<uint64_t, ParagraphCacheInfo>> paragraphCache_;

    // used to keep same life cycle with TextPattern
    std::function<void()> jsTextControllerBinder_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_PATTERN_H
