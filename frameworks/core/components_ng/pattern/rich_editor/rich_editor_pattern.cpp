/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>

#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "adapter/ohos/capability/clipboard/clipboard_impl.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/clipboard/paste_data.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/share/text_share_adapter.h"
#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_base_pattern.h"
#include "core/components_ng/pattern/rich_editor/one_step_drag_controller.h"
#include "core/components_ng/pattern/rich_editor/color_mode_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_utils.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_input_ai_checker.h"

#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "refbase.h"

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif

#include "core/common/udmf/udmf_client.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif

#ifdef ENABLE_ROSEN_BACKEND
#include "core/components/custom_paint/rosen_render_custom_paint.h"
#endif

namespace OHOS::Ace::NG {

namespace {
#if defined(ENABLE_STANDARD_INPUT)
// should be moved to theme
constexpr float CARET_WIDTH = 1.5f;
constexpr float DEFAULT_CARET_HEIGHT = 18.5f;
constexpr Dimension KEYBOARD_AVOID_OFFSET = 24.0_vp;
#endif
constexpr int32_t IMAGE_SPAN_LENGTH = 1;
constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
constexpr uint32_t RICH_EDITOR_TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t RICH_EDITOR_TWINKLING_INTERVAL_MS_DEBUG = 3000;
constexpr int32_t AUTO_SCROLL_INTERVAL = 15;
constexpr Dimension CARET_BOTTOM_DISTANCE = 16.0_vp;
constexpr Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
constexpr Dimension AUTO_SCROLL_DRAG_EDGE_DISTANCE = 58.0_vp;
constexpr float MAX_DRAG_SCROLL_SPEED = 2400.0f;
constexpr float TIME_UNIT = 1000.0f;
constexpr float DOUBLE_CLICK_INTERVAL_MS = 300.0f;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr float DEFAILT_OPACITY = 0.2f;
constexpr int64_t COLOR_OPAQUE = 255;
constexpr int32_t MAX_CLICK = 3;

constexpr Color SYSTEM_CARET_COLOR = Color(0xff007dff);
constexpr Color SYSTEM_SELECT_BACKGROUND_COLOR = Color(0x33007dff);

const auto MAGNIFIER_ANIMATION_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 30.0f);
constexpr int32_t MAGNIFIER_ANIMATION_DURATION = 100;

constexpr int32_t ERROR_BAD_PARAMETERS = -1;
constexpr char PREVIEW_STYLE_NORMAL[] = "normal";
constexpr char PREVIEW_STYLE_UNDERLINE[] = "underline";
const std::u16string LINE_SEPARATOR = u"\n";
// hen do ai anaylsis, we should limit the left an right limit of the string
constexpr static int32_t AI_TEXT_RANGE_LEFT = 50;
constexpr static int32_t AI_TEXT_RANGE_RIGHT = 50;
constexpr static int32_t NONE_SELECT_TYPE = -1;

constexpr float RICH_DEFAULT_SHADOW_COLOR = 0x33000000;
constexpr float RICH_DEFAULT_ELEVATION = 120.0f;
constexpr int32_t CUSTOM_CONTENT_LENGTH = 1;
constexpr int32_t SYMBOL_CONTENT_LENGTH = 2;
constexpr int32_t PLACEHOLDER_LENGTH = 6;
const std::u16string PLACEHOLDER_MARK = u"![id";
const std::string SPACE_CHARS = "^\\s+|\\s+$";
const std::string RICHEDITOR = "RichEditor.";
const std::string EVENT = "event";
const static std::regex REMOVE_SPACE_CHARS{SPACE_CHARS};
const auto URL_SPAN_FILTER = [](const RefPtr<SpanItem>& span){ return (span->urlOnRelease); };
} // namespace

RichEditorPattern::RichEditorPattern() :
#ifndef ACE_UNITTEST
    isAPI14Plus(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)),
#else
    isAPI14Plus(true),
#endif
    isAPI16Plus(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)),
    isAPI18Plus(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)),
    isAPI20Plus(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY))
{
    selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(WeakClaim(this));
    magnifierController_ = MakeRefPtr<MagnifierController>(WeakClaim(this));
    styledString_ = MakeRefPtr<MutableSpanString>(u"");
    styledString_->SetSpanWatcher(WeakClaim(this));
    twinklingInterval_ = SystemProperties::GetDebugEnabled()
        ? RICH_EDITOR_TWINKLING_INTERVAL_MS_DEBUG : RICH_EDITOR_TWINKLING_INTERVAL_MS;
    floatingCaretState_.UpdateOriginCaretColor(GetDisplayColorMode());
    undoManager_ = std::make_unique<RichEditorUndoManager>(WeakClaim(this));
}

RichEditorPattern::~RichEditorPattern()
{
    if (isCustomKeyboardAttached_) {
        CloseCustomKeyboard();
    }
}

void RichEditorPattern::SetStyledString(const RefPtr<SpanString>& value)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetStyledString, len=%{public}d", value->GetLength());
    SEC_TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetStyledString, str=%{public}s", value->GetString().c_str());
    if (GetTextContentLength() > maxLength_.value_or(INT_MAX)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "SetStyledString: Reach the maxLength. maxLength=%{public}d", maxLength_.value_or(INT_MAX));
        return;
    }
    CHECK_NULL_VOID(value && styledString_);
    auto subValue = value;
    if (value->GetLength() != styledString_->GetLength() && value->GetLength() > maxLength_.value_or(INT_MAX)) {
        auto subLength = CalculateTruncationLength(value->GetU16string(), maxLength_.value_or(INT_MAX));
        if (subLength == 0) {
            IF_TRUE(IsPreviewTextInputting() && !previewTextRecord_.previewTextExiting, NotifyExitTextPreview(true));
            return;
        }
        subValue = value->GetSubSpanString(0, subLength);
    }
    IF_TRUE(IsPreviewTextInputting() && !previewTextRecord_.previewTextExiting, NotifyExitTextPreview(true));
    auto length = styledString_->GetLength();
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(0, length, subValue, record);
    CloseSelectOverlay();
    ResetSelection();
    styledString_->RemoveCustomSpan();
    styledString_->ReplaceSpanString(0, length, subValue);
    SetCaretPosition(styledString_->GetLength());
    SetNeedMoveCaretToContentRect();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    styledString_->AddCustomSpan();
    styledString_->SetFramNode(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ForceTriggerAvoidOnCaretChange();
    undoManager_->RecordOperation(record);
}

void RichEditorPattern::UpdateSpanItems(const std::list<RefPtr<NG::SpanItem>>& spanItems)
{
    SetSpanItemChildren(spanItems);
    ProcessStyledString();
}

void RichEditorPattern::ProcessStyledString()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::u16string textCache = textForDisplay_;
    textForDisplay_.clear();
    dataDetectorAdapter_->textForAI_.clear();
    host->Clean();
    RemoveEmptySpanItems();
    hasUrlSpan_ = false;
    for (const auto& span : spans_) {
        if (!span) {
            continue;
        }
        auto imageSpan = DynamicCast<ImageSpanItem>(span);
        if (imageSpan) {
            MountImageNode(imageSpan);
            dataDetectorAdapter_->textForAI_ += u'\n';
        } else {
            dataDetectorAdapter_->textForAI_ += span->content;
        }
        textForDisplay_ += span->content;
        auto [spanStart, spanEnd] = span->interval;
        span->rangeStart = spanStart;
        span->position = spanEnd;

        if (span->urlOnRelease) {
            hasUrlSpan_ = true;
        }
    }
    if (textForDisplay_ != textCache) {
        dataDetectorAdapter_->aiDetectInitialized_ = false;
    }
    if (CanStartAITask() && !dataDetectorAdapter_->aiDetectInitialized_) {
        dataDetectorAdapter_->StartAITask();
    }
}

void RichEditorPattern::MountImageNode(const RefPtr<ImageSpanItem>& imageItem)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(imageItem);
    auto options = imageItem->options;
    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto pattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    if (options.imagePixelMap.has_value()) {
        pattern->SetSyncLoad(true);
    } else if (options.imageAttribute.has_value()) {
        pattern->SetSyncLoad(options.imageAttribute.value().syncLoad);
    }
    auto index = host->GetChildren().size();
    imageNodes.push_back(imageNode);
    imageNode->MountToParent(host, index);
    HandleImageDrag(imageNode);
    SetImageLayoutProperty(imageNode, options);
    imageItem->nodeId_ = imageNode->GetId();
    imageNode->SetImageItem(imageItem);
}

void RichEditorPattern::SetImageLayoutProperty(RefPtr<ImageSpanNode> imageNode, const ImageSpanOptions& options)
{
    CHECK_NULL_VOID(imageNode);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    std::function<ImageSourceInfo()> createSourceInfoFunc = CreateImageSourceInfo(options);
    imageLayoutProperty->UpdateImageSourceInfo(createSourceInfoFunc());
    if (options.imageAttribute.has_value()) {
        auto imgAttr = options.imageAttribute.value();
        if (imgAttr.size.has_value()) {
            imageLayoutProperty->UpdateUserDefinedIdealSize(imgAttr.size->GetSize());
        }
        if (imgAttr.verticalAlign.has_value()) {
            imageLayoutProperty->UpdateVerticalAlign(imgAttr.verticalAlign.value());
        }
        if (imgAttr.objectFit.has_value()) {
            imageLayoutProperty->UpdateImageFit(imgAttr.objectFit.value());
        }
        if (imgAttr.marginProp.has_value()) {
            imageLayoutProperty->UpdateMargin(imgAttr.marginProp.value());
        }
        if (imgAttr.paddingProp.has_value()) {
            imageLayoutProperty->UpdatePadding(imgAttr.paddingProp.value());
        }
        if (imgAttr.borderRadius.has_value()) {
            auto imageRenderCtx = imageNode->GetRenderContext();
            imageRenderCtx->UpdateBorderRadius(imgAttr.borderRadius.value());
            imageRenderCtx->SetClipToBounds(true);
        }
        auto paintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
        if (imgAttr.colorFilterMatrix.has_value() && paintProperty) {
            paintProperty->UpdateColorFilter(imgAttr.colorFilterMatrix.value());
            paintProperty->ResetDrawingColorFilter();
        } else if (imgAttr.drawingColorFilter.has_value() && paintProperty) {
            paintProperty->UpdateDrawingColorFilter(imgAttr.drawingColorFilter.value());
            paintProperty->ResetColorFilter();
        }
    }
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    IF_PRESENT(oneStepDragController_, MarkDirtyNode(WeakClaim(RawPtr(imageNode))));
}

void RichEditorPattern::HandleStyledStringInsertion(RefPtr<SpanString> insertStyledString, const UndoRedoRecord& record,
    std::u16string& subValue, bool needReplaceInTextPreview, bool shouldCommitInput)
{
    auto changeStart = record.rangeBefore.start;
    auto changeLength = record.rangeBefore.GetLength();
    if (changeLength > 0 && (subValue.length() > 0 || !shouldCommitInput)) {
        auto start = needReplaceInTextPreview ? previewTextRecord_.replacedRange.start : caretPosition_;
        auto isUpdateCaret = !needReplaceInTextPreview;
        DeleteValueInStyledString(start, changeLength, false, isUpdateCaret);
    }
    bool isSingleHandleMoving = selectOverlay_->IsSingleHandleMoving();
    if (textSelector_.IsValid()) {
        ResetSelection();
    }
    CloseSelectOverlay();
    if (insertStyledString) {
        styledString_->InsertSpanString(changeStart, insertStyledString);
    } else {
        styledString_->InsertString(changeStart, subValue);
    }
    SetCaretPosition(changeStart + static_cast<int32_t>(subValue.length()), !needReplaceInTextPreview);
    IF_TRUE((!caretVisible_ || isSingleHandleMoving) && HasFocus(), StartTwinkling());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::InsertValueInStyledString(
    const std::u16string& insertValue, bool shouldCommitInput, bool isPaste)
{
    CHECK_NULL_VOID(styledString_);
    IF_TRUE(shouldCommitInput && previewTextRecord_.IsValid(), FinishTextPreviewInner());
    int32_t changeStart = caretPosition_;
    int32_t changeLength = 0;
    if (textSelector_.IsValid()) {
        changeStart = textSelector_.GetTextStart();
        changeLength = textSelector_.GetTextEnd() - changeStart;
        IF_TRUE(!shouldCommitInput, undoManager_->RecordPreviewInputtingStart(changeStart, changeLength));
    }
    auto subValue = insertValue;
    if (!ProcessTextTruncationOperation(subValue, shouldCommitInput)) {
        return;
    }
    auto needReplaceInTextPreview = (previewTextRecord_.needReplacePreviewText || previewTextRecord_.needReplaceText) &&
                               previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start > 0;
    if (needReplaceInTextPreview) {
        changeStart= previewTextRecord_.replacedRange.start;
        changeLength = previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start;
    }
    UndoRedoRecord record;
    bool isPreventChange = false;
    RefPtr<SpanString> insertStyledString = nullptr;
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        insertStyledString = CreateStyledStringByTextStyle(subValue, typingStyle_.value(), typingTextStyle_.value());
        undoManager_->ApplyOperationToRecord(changeStart, changeLength, insertStyledString, record);
        isPreventChange = !BeforeStyledStringChange(record);
    } else {
        undoManager_->ApplyOperationToRecord(changeStart, changeLength, subValue, record);
        isPreventChange = !BeforeStyledStringChange(record);
    }
    CHECK_NULL_VOID(!isPreventChange || previewTextRecord_.needReplacePreviewText);
    HandleStyledStringInsertion(insertStyledString, record, subValue, needReplaceInTextPreview, shouldCommitInput);
    IF_TRUE(shouldCommitInput, undoManager_->RecordInsertOperation(record));
    AfterStyledStringChange(record);
    IF_TRUE(!isPaste, OnReportRichEditorEvent("onIMEInputComplete"));
}

RefPtr<SpanString> RichEditorPattern::CreateStyledStringByTextStyle(
    const std::u16string& insertValue, const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle)
{
    auto styledString = AceType::MakeRefPtr<SpanString>(insertValue);
    auto length = styledString->GetLength();
    std::vector<RefPtr<SpanBase>> spans;
    spans.push_back(CreateFontSpanByTextStyle(updateSpanStyle, textStyle, length));
    spans.push_back(CreateDecorationSpanByTextStyle(updateSpanStyle, textStyle, length));
    if (updateSpanStyle.updateTextShadows.has_value()) {
        spans.push_back(AceType::MakeRefPtr<TextShadowSpan>(textStyle.GetTextShadows(), 0, length));
    }
    if (updateSpanStyle.updateLineHeight.has_value()) {
        spans.push_back(AceType::MakeRefPtr<LineHeightSpan>(textStyle.GetLineHeight(), 0, length));
    }
    if (updateSpanStyle.updateHalfLeading.has_value()) {
        spans.push_back(AceType::MakeRefPtr<HalfLeadingSpan>(textStyle.GetHalfLeading(), 0, length));
    }
    if (updateSpanStyle.updateLetterSpacing.has_value()) {
        spans.push_back(AceType::MakeRefPtr<LetterSpacingSpan>(textStyle.GetLetterSpacing(), 0, length));
    }
    if (updateSpanStyle.updateTextBackgroundStyle.has_value()) {
        spans.push_back(AceType::MakeRefPtr<BackgroundColorSpan>(textStyle.GetTextBackgroundStyle(), 0, length));
    }
    styledString->BindWithSpans(spans);
    return styledString;
}

RefPtr<FontSpan> RichEditorPattern::CreateFontSpanByTextStyle(
    const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length)
{
    Font font;
    if (updateSpanStyle.updateFontWeight.has_value()) {
        font.fontWeight = textStyle.GetFontWeight();
    }
    if (updateSpanStyle.updateFontSize.has_value()) {
        font.fontSize = textStyle.GetFontSize();
    }
    if (updateSpanStyle.updateItalicFontStyle.has_value()) {
        font.fontStyle = textStyle.GetFontStyle();
    }
    if (updateSpanStyle.updateFontFamily.has_value()) {
        font.fontFamilies = textStyle.GetFontFamilies();
    }
    if (updateSpanStyle.updateTextColor.has_value()) {
        font.fontColor = textStyle.GetTextColor();
    }
    return AceType::MakeRefPtr<FontSpan>(font, 0, length);
}

RefPtr<DecorationSpan> RichEditorPattern::CreateDecorationSpanByTextStyle(
    const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length)
{
    TextDecoration type = TextDecoration::NONE;
    std::optional<Color> colorOption;
    std::optional<TextDecorationStyle> styleOption;
    if (updateSpanStyle.updateTextDecoration.has_value()) {
        type = textStyle.GetTextDecoration();
    }
    if (updateSpanStyle.updateTextDecorationColor.has_value()) {
        colorOption = textStyle.GetTextDecorationColor();
    }
    if (updateSpanStyle.updateTextDecorationStyle.has_value()) {
        styleOption = textStyle.GetTextDecorationStyle();
    }
    return AceType::MakeRefPtr<DecorationSpan>(type, colorOption, styleOption, 0, length);
}

void RichEditorPattern::DeleteBackwardInStyledString(int32_t length)
{
    DeleteValueInStyledString(caretPosition_ - length, length);
}

void RichEditorPattern::DeleteForwardInStyledString(int32_t length, bool isIME)
{
    DeleteValueInStyledString(caretPosition_, length, isIME);
}

void RichEditorPattern::DeleteValueInStyledString(int32_t start, int32_t length, bool isIME, bool isUpdateCaret)
{
    CHECK_NULL_VOID(styledString_);
    if (!textSelector_.SelectNothing()) {
        start = textSelector_.GetTextStart();
        length = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    }
    auto range = TextEmojiProcessor::CalSubU16stringRange(start, length, styledString_->GetU16string(), true, true);
    start = range.startIndex;
    length = range.endIndex - range.startIndex;
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(start, length, u"", record);
    bool isPreventChange = isIME && !BeforeStyledStringChange(record);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "deleteInSS, start=%{public}d, length=%{public}d, isPreventChange=%{public}d, "
        "isPreviewTextInputting=%{public}d",
        start, length, isPreventChange, IsPreviewTextInputting());
    CHECK_NULL_VOID(!isPreventChange || IsPreviewTextInputting());
    IF_TRUE(isIME && !IsPreviewTextInputting(), undoManager_->RecordOperation(record));
    bool isSingleHandleMoving = selectOverlay_->IsSingleHandleMoving();
    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
    styledString_->RemoveString(start, length);
    if (isUpdateCaret) {
        SetCaretPosition(start, !isModifyingContent_);
    }
    if ((!caretVisible_ || isSingleHandleMoving) && HasFocus()) {
        StartTwinkling();
        if (!isEditing_ && isIME) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "previewLongPress_ is true, before RequestKeyboard");
            RequestKeyboard(false, true, true);
            HandleOnEditChanged(true);
            previewLongPress_ = false;
        }
    }
    if (isIME) {
        AfterStyledStringChange(record);
    }
    OnReportRichEditorEvent("onDeleteComplete");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

RefPtr<SpanString> RichEditorPattern::CreateStyledStringByStyleBefore(int32_t start, const std::u16string& string)
{
    auto styledString = AceType::MakeRefPtr<SpanString>(string);
    CHECK_NULL_RETURN(styledString_, styledString);
    auto stringLength = styledString->GetLength();
    CHECK_NULL_RETURN(stringLength != 0, styledString);
    auto lastStyles = styledString_->GetSpans(start - 1, 1);
    for (auto && style : lastStyles) {
        CHECK_NULL_CONTINUE(style);
        auto spanType = style->GetSpanType();
        CHECK_NULL_CONTINUE(spanType != SpanType::Image && spanType != SpanType::CustomSpan);
        auto span = style->GetSubSpan(0, stringLength);
        styledString->AddSpan(span);
    }
    return styledString;
}

bool RichEditorPattern::BeforeStyledStringChange(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_RETURN(!record.isOnlyStyleChange, true);
    auto changeStart = isUndo ? record.rangeAfter.start : record.rangeBefore.start;
    auto changeLength = isUndo ? record.rangeAfter.GetLength() : record.rangeBefore.GetLength();
    auto styledString = isUndo ? record.styledStringBefore : record.styledStringAfter;
    return BeforeStyledStringChange(changeStart, changeLength, styledString);
}

bool RichEditorPattern::BeforeStyledStringChange(int32_t start, int32_t length, const std::u16string& string)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    CHECK_NULL_RETURN(eventHub->HasOnStyledStringWillChange(), true);
    auto changeStart = std::clamp(start, 0, GetTextContentLength());
    auto styledString = CreateStyledStringByStyleBefore(changeStart, string);
    return BeforeStyledStringChange(changeStart, length, styledString);
}

bool RichEditorPattern::BeforeStyledStringChange(int32_t start, int32_t length, const RefPtr<SpanString>& styledString)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    CHECK_NULL_RETURN(eventHub->HasOnStyledStringWillChange(), true);
    auto replaceMentString = AceType::MakeRefPtr<MutableSpanString>(u"");
    replaceMentString->AppendSpanString(styledString);
    StyledStringChangeValue changeValue;
    auto changeStart = std::clamp(start, 0, GetTextContentLength());
    auto changeEnd = std::clamp(changeStart + length, 0, GetTextContentLength());
    changeValue.SetRangeBefore({ changeStart, changeEnd });
    changeValue.SetReplacementString(replaceMentString);
    if (!previewTextRecord_.newPreviewContent.empty()) {
        auto previewTextStyledString = AceType::MakeRefPtr<MutableSpanString>(previewTextRecord_.newPreviewContent);
        changeValue.SetPreviewText(previewTextStyledString);
    }
    return eventHub->FireOnStyledStringWillChange(changeValue);
}

void RichEditorPattern::AfterStyledStringChange(int32_t start, int32_t length, const std::u16string& string)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->HasOnStyledStringDidChange()) {
        StyledStringChangeValue changeValue;
        auto changeStart = std::clamp(start, 0, GetTextContentLength());
        auto changeEnd = changeStart + length;
        auto stringLength = static_cast<int32_t>(string.length());
        auto stringEnd = changeStart + stringLength;
        changeValue.SetRangeBefore({ changeStart, changeEnd });
        changeValue.SetRangeAfter({ changeStart, stringEnd });
        eventHub->FireOnStyledStringDidChange(changeValue);
    }
    ForceTriggerAvoidOnCaretChange();
}

void RichEditorPattern::AfterStyledStringChange(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_VOID(!record.isOnlyStyleChange);
    auto start = isUndo ? record.rangeAfter.start : record.rangeBefore.start;
    auto length = isUndo ? record.rangeAfter.GetLength() : record.rangeBefore.GetLength();
    auto styledString = isUndo ? record.styledStringBefore : record.styledStringAfter;
    CHECK_NULL_VOID(styledString);
    AfterStyledStringChange(start, length, styledString->GetU16string());
}

void RichEditorPattern::HandleUndoInStyledString(const UndoRedoRecord& record)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto undoRecord = record;
    undoRecord.Reverse();
    ApplyRecordInStyledString(undoRecord);
    if (record.selectionBefore.GetLength() == 0) {
        IF_TRUE(isEditing_, StartTwinkling());
    } else {
        HandleSelectionChange(undoRecord.selectionBefore.start, undoRecord.selectionBefore.end);
    }
    SetCaretPosition(undoRecord.selectionBefore.end);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::HandleRedoInStyledString(const UndoRedoRecord& record)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ApplyRecordInStyledString(record);
    SetCaretPosition(record.rangeAfter.end);
    IF_TRUE(isEditing_, StartTwinkling());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::ApplyRecordInStyledString(const UndoRedoRecord& record)
{
    CHECK_NULL_VOID(styledString_);
    auto start = record.rangeBefore.start;
    auto length = record.rangeBefore.GetLength();
    auto styledString = record.styledStringAfter;
    auto startBefore = record.rangeAfter.start;
    auto lengthBefore = record.rangeAfter.GetLength();
    CloseSelectOverlay();
    ResetSelection();
    if (record.isOnlyStyleChange) {
        std::vector<RefPtr<SpanBase>> updateSpans;
        for (const auto& spanType : record.updateSpanTypes) {
            styledString_->RemoveSpan(start, length, spanType);
            auto spansBefore = styledString->GetSpans(0, lengthBefore, spanType);
            for (auto& span : spansBefore) {
                CHECK_NULL_CONTINUE(span);
                auto spanStart = span->GetStartIndex() + startBefore;
                auto spanEnd = span->GetEndIndex() + startBefore;
                updateSpans.push_back(span->GetSubSpan(spanStart, spanEnd));
            }
        }
        paragraphCache_.Clear();
        styledString_->BindWithSpans(updateSpans);
        styledString_->NotifySpanWatcher();
    } else {
        styledString_->ReplaceSpanString(start, length, styledString);
    }
}

void RichEditorPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    copyOption_ = layoutProperty->GetCopyOption().value_or(CopyOptions::Distributed);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    ResetKeyboardIfNeed();
    context->AddOnAreaChangeNode(host->GetId());
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    instanceId_ = context->GetInstanceId();
    InitMouseEvent();
    InitAISpanHoverEvent();
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitFocusEvent(focusHub);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    InitClickEvent(gestureEventHub);
    InitLongPressEvent(gestureEventHub);
    InitTouchEvent();
    InitPanEvent();
    HandleEnabled();
    ProcessInnerPadding();
    InitScrollablePattern();
    SetAccessibilityAction();
    selectOverlay_->SetMenuTranslateIsSupport(IsShowTranslate());
    selectOverlay_->SetIsSupportMenuSearch(IsShowSearch());
    if (host->IsDraggable()) {
        InitDragDropEvent();
        AddDragFrameNodeToManager(host);
    } else {
        ClearDragDropEvent();
        RemoveDragFrameNodeFromManager(host);
    }
    Register2DragDropManager();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    bool enabledCache = eventHub->IsEnabled();
    if (textDetectEnable_ && enabledCache != enabled_) {
        enabled_ = enabledCache;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    SetIsEnableSubWindowMenu();
}

void RichEditorPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (IsDisabled()) {
        auto richEditorTheme = GetTheme<RichEditorTheme>();
        CHECK_NULL_VOID(richEditorTheme);
        auto disabledAlpha = richEditorTheme->GetDisabledAlpha();
        renderContext->OnOpacityUpdate(disabledAlpha);
    } else {
        auto opacity = renderContext->GetOpacity().value_or(1.0);
        renderContext->OnOpacityUpdate(opacity);
    }
}

void RichEditorPattern::BeforeCreateLayoutWrapper()
{
    ACE_SCOPED_TRACE("RichEditorBeforeCreateLayoutWrapper");
    if (!isSpanStringMode_) {
        TextPattern::PreCreateLayoutWrapper();
        hasUrlSpan_ = std::any_of(spans_.begin(), spans_.end(), URL_SPAN_FILTER);
    } else if (contentMod_) {
        contentMod_->ContentChange();
    }
}

void RichEditorPattern::UpdateMagnifierStateAfterLayout(bool frameSizeChange)
{
    CHECK_NULL_VOID(!selectOverlay_->GetIsHandleMoving());
    if (frameSizeChange && magnifierController_ && magnifierController_->GetMagnifierNodeExist()) {
        ResetTouchSelectState();
        ResetTouchAndMoveCaretState();
        magnifierController_->RemoveMagnifierFrameNode();
    }
}

void RichEditorPattern::UpdateGestureHotZone(const RefPtr<LayoutWrapper>& dirty)
{
    const auto& geometryNode = dirty->GetGeometryNode();
    auto paddingSize = geometryNode->GetPaddingSize();
    auto paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();

    auto hotZoneWidth = Dimension(paddingSize.Width());
    auto hotZoneHeight = Dimension(paddingSize.Height());
    auto hotZoneOffset = DimensionOffset(Offset(paddingOffset.GetX(), paddingOffset.GetY()));

    auto gestureHub = GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetResponseRegion({ { hotZoneWidth, hotZoneHeight, hotZoneOffset } });
}

void RichEditorPattern::ClearOnFocusTextField(FrameNode* node)
{
    CHECK_NULL_VOID(isAPI14Plus && node);
    auto context = node->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    IF_PRESENT(textFieldManager, ClearOnFocusTextField(node->GetId()));
}

bool RichEditorPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(!config.skipMeasure && !dirty->SkipMeasureContent(), false);
    auto originalFrameRect = frameRect_;
    frameRect_ = dirty->GetGeometryNode()->GetFrameRect();
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto richEditorLayoutAlgorithm =
        DynamicCast<RichEditorLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(richEditorLayoutAlgorithm, false);
    UpdateParentOffsetAndOverlay();
    richTextRect_ = richEditorLayoutAlgorithm->GetTextRect();
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    bool ret = TextPattern::OnDirtyLayoutWrapperSwap(dirty, config);
    UpdateScrollStateAfterLayout(config.frameSizeChange);
    UpdateMagnifierStateAfterLayout(config.frameSizeChange);
    IF_TRUE(!isRichEditorInit_, FireOnReady());
    MoveCaretOnLayoutSwap();
    HandleTasksOnLayoutSwap();
    HandleSelectOverlayOnLayoutSwap();
    IF_TRUE(originalFrameRect.GetSize() != frameRect_.GetSize(), {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "frame size change");
        TriggerAvoidOnCaretChangeNextFrame();
    });
    IF_TRUE(!isModifyingContent_, UpdateCaretInfoToController());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ret);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, ret);
    if (context->GetClipEdge().has_value()) {
        auto geometryNode = host->GetGeometryNode();
        auto frameOffset = geometryNode->GetFrameOffset();
        auto frameSize = geometryNode->GetFrameSize();
        auto height = static_cast<float>(paragraphs_.GetHeight() + std::fabs(baselineOffset_));
        if (!context->GetClipEdge().value() && LessNotEqual(frameSize.Height(), height)) {
            RectF boundsRect(frameOffset.GetX(), frameOffset.GetY(), frameSize.Width(), height);
            CHECK_NULL_RETURN(overlayMod_, ret);
            overlayMod_->SetBoundsRect(boundsRect);
        }
    }
    caretUpdateType_ = CaretUpdateType::NONE;
    IF_PRESENT(oneStepDragController_, HandleDirtyNodes());
    UpdateGestureHotZone(dirty);
    if (afterDragSelect_) {
        UpdateSelectionAndHandleVisibility();
        afterDragSelect_ = false;
    }
    releaseInDrop_ = false;
    return ret;
}

void RichEditorPattern::UpdateSelectionAndHandleVisibility()
{
    auto start = recoverStart_;
    auto end = recoverEnd_;
    if (textSelector_.GetStart() == start && textSelector_.GetEnd() == end) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isMouseOrTouchPad(sourceTool_) && releaseInDrop_) {
        start = lastCaretPosition_;
        end = insertValueLength_ + lastCaretPosition_;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "UpdateSelectionAndHandleVisibility range=[%{public}d--%{public}d]", start, end);
    textSelector_.Update(start, end);

    if (!isMouseOrTouchPad(sourceTool_)) {
        if (!selectOverlay_->IsBothHandlesShow() && !selectOverlay_->SelectOverlayIsCreating()) {
            showSelect_ = true;
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            CalculateHandleOffsetAndShowOverlay();
            selectOverlay_->ProcessOverlay({.menuIsShow = false, .animation = false});
        }
    }
    FireOnSelectionChange(start, end, true);
}

void RichEditorPattern::HandleSelectOverlayOnLayoutSwap()
{
    bool needToRefreshSelectOverlay = textSelector_.IsValid() && SelectOverlayIsOn() && !IsPreviewTextInputting();
    CHECK_NULL_VOID(needToRefreshSelectOverlay);
    auto overlayTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto selectOverlay = pattern->selectOverlay_;
        IF_PRESENT(selectOverlay, UpdateSelectOverlayOnAreaChanged());
    };
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask(overlayTask);
    } else {
        overlayTask();
    }
}

void RichEditorPattern::FireOnReady()
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnReady();
    ClearOperationRecords();
    isFirstCallOnReady_ = true;
    isRichEditorInit_ = true;
}

void RichEditorPattern::MoveCaretOnLayoutSwap()
{
    MoveCaretAfterTextChange();
    if (needMoveCaretToContentRect_ || isEditing_) {
        MoveCaretToContentRect();
        needMoveCaretToContentRect_ = false;
    }
}

std::function<ImageSourceInfo()> RichEditorPattern::CreateImageSourceInfo(const ImageSpanOptions& options)
{
    std::string src;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string bundleName;
    std::string moduleName;
    if (options.image.has_value()) {
        src = options.image.value();
    }
    if (options.imagePixelMap.has_value()) {
        pixMap = options.imagePixelMap.value();
    }
    if (options.bundleName.has_value()) {
        bundleName = options.bundleName.value();
    }
    if (options.moduleName.has_value()) {
        moduleName = options.moduleName.value();
    }
    auto createSourceInfoFunc = [src, noPixMap = !options.imagePixelMap.has_value(),
                                    isUriPureNumber = options.isUriPureNumber.value_or(false), pixMap, bundleName,
                                    moduleName]() -> ImageSourceInfo {
        ImageSourceInfo info;
#if defined(PIXEL_MAP_SUPPORTED)
        if (noPixMap) {
            info = ImageSourceInfo { src, bundleName, moduleName };
        } else {
            info = ImageSourceInfo(pixMap);
        }
#else
        info = ImageSourceInfo { src, bundleName, moduleName };
#endif
        info.SetIsUriPureNumber(isUriPureNumber);
        return info;
    };
    return std::move(createSourceInfoFunc);
}

int32_t RichEditorPattern::GetTextContentLength()
{
    if (isSpanStringMode_ && styledString_) {
        return styledString_->GetLength();
    }
    if (!spans_.empty()) {
        auto it = spans_.rbegin();
        return (*it)->position;
    }
    return 0;
}

void RichEditorPattern::SetPreviewMenuParam(TextSpanType spanType, std::function<void()>& builder, const SelectMenuParam& menuParam)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetPreviewMenuParam, spanType=%{public}d, builder=%{public}d",
        spanType, !!builder);
    if (!oneStepDragController_) {
        oneStepDragController_ = std::make_unique<OneStepDragController>(WeakClaim(this));
    }
    oneStepDragController_->SetMenuParam(spanType, builder, menuParam);
    oneStepDragController_->SetEnableEventResponse(textSelector_, imageNodes, builderNodes);
}

void RichEditorPattern::HandleImageDrag(const RefPtr<ImageSpanNode>& imageNode)
{
    DisableDrag(imageNode);
    IF_PRESENT(oneStepDragController_, EnableOneStepDrag(TextSpanType::IMAGE, imageNode));
}

void RichEditorPattern::DisableDrag(const RefPtr<ImageSpanNode>& imageNode)
{
    // Disable the image itself event
    imageNode->SetDraggable(false);
    auto gesture = imageNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    gesture->InitDragDropEvent();
    gesture->SetDragEvent(nullptr, { PanDirection::DOWN }, 0, Dimension(0));
}

void RichEditorPattern::SetGestureOptions(UserGestureOptions options, RefPtr<SpanItem> spanItem)
{
    IF_TRUE(options.onClick, spanItem->SetOnClickEvent(std::move(options.onClick)));
    IF_TRUE(options.onLongPress, spanItem->SetLongPressEvent(std::move(options.onLongPress)));
    IF_TRUE(options.onDoubleClick, spanItem->SetDoubleClickEvent(std::move(options.onDoubleClick)));
}

void RichEditorPattern::AddSpanHoverEvent(
    RefPtr<SpanItem> spanItem, const RefPtr<FrameNode>& frameNode, const SpanOptionBase& options)
{
    auto onHoverFunc = options.userMouseOption.onHover;
    CHECK_NULL_VOID(spanItem && frameNode && onHoverFunc);
    auto tag = frameNode->GetTag();
    spanItem->SetHoverEvent(std::move(onHoverFunc));
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [weak = WeakClaim(Referenced::RawPtr(spanItem)), tag](bool isHover, HoverInfo& info) {
        auto item = weak.Upgrade();
        if (item && item->onHover) {
            TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "[%{public}s] onHover status :[%{public}d]", tag.c_str(), isHover);
            item->onHover(isHover, info);
        }
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
}

int32_t RichEditorPattern::AddImageSpan(const ImageSpanOptions& options, bool isPaste, int32_t index,
    bool updateCaret)
{
    if (GetTextContentLength() >= maxLength_.value_or(INT_MAX)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "AddImageSpan: Reach the maxLength. maxLength=%{public}d", maxLength_.value_or(INT_MAX));
        return 0;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AddImageSpan, opts=%{public}s, updateCaret=%{public}d",
        options.ToString().c_str(), updateCaret);
    NotifyExitTextPreview(false);
    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto pattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_RETURN(pattern, -1);
    pattern->SetSyncLoad(true);
    int32_t insertIndex = options.offset.value_or(GetTextContentLength());
    insertIndex = std::min(insertIndex, GetTextContentLength());
    AdjustSelectorForSymbol(insertIndex, HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
    RichEditorChangeValue changeValue;
    CHECK_NULL_RETURN(BeforeAddImage(changeValue, options, insertIndex), -1);

    HandleImageDrag(imageNode);
    AddOprationWhenAddImage(insertIndex);
    int32_t spanIndex = TextSpanSplit(insertIndex);
    IF_TRUE(spanIndex == -1, spanIndex = static_cast<int32_t>(host->GetChildren().size()));

    imageNodes.push_back(imageNode);
    imageNode->MountToParent(host, spanIndex);
    auto renderContext = imageNode->GetRenderContext();
    IF_PRESENT(renderContext, SetNeedAnimateFlag(false));
    SetImageLayoutProperty(imageNode, options);
    auto spanItem = imageNode->GetSpanItem();
    // The length of the imageSpan defaults to the length of a character to calculate the position
    spanItem->content = u" ";
    spanItem->SetImageSpanOptions(options);
    spanItem->spanItemType = SpanItemType::IMAGE;
    AddSpanItem(spanItem, spanIndex);
    SetGestureOptions(options.userGestureOption, spanItem);
    auto userMouseOption = options.userMouseOption;
    if (userMouseOption.onHover) {
        spanItem->onHover_ = std::move(userMouseOption.onHover);
        hoverableNodes.push_back(imageNode);
    }
    placeholderCount_++;
    if (updateCaret) {
        SetCaretPosition(insertIndex + spanItem->content.length());
        SetNeedMoveCaretToContentRect();
    }
    ResetSelectionAfterAddSpan(isPaste);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    AfterContentChange(changeValue);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "end");
    return spanIndex;
}

HoverInfo RichEditorPattern::CreateHoverInfo(const MouseInfo& info)
{
    HoverInfo hoverInfo;
    hoverInfo.SetType(info.GetType());
    hoverInfo.SetTimeStamp(info.GetTimeStamp());
    hoverInfo.SetTarget(info.GetTarget());
    hoverInfo.SetSourceDevice(info.GetSourceDevice());
    hoverInfo.SetForce(info.GetForce());
    IF_TRUE(info.GetTiltX(), hoverInfo.SetTiltX(info.GetTiltX().value()));
    IF_TRUE(info.GetTiltY(), hoverInfo.SetTiltY(info.GetTiltY().value()));
    hoverInfo.SetSourceTool(info.GetSourceTool());
    hoverInfo.SetDeviceId(info.GetDeviceId());
    hoverInfo.SetTargetDisplayId(info.GetTargetDisplayId());
    hoverInfo.SetStopPropagation(info.IsStopPropagation());
    hoverInfo.SetPreventDefault(info.IsPreventDefault());
    hoverInfo.SetPatternName(info.GetPatternName());
    hoverInfo.SetPressedKeyCodes(info.GetPressedKeyCodes());
    hoverInfo.SetIsPostEventResult(info.GetIsPostEventResult());
    hoverInfo.SetPostEventNodeId(info.GetPostEventNodeId());
    return hoverInfo;
}

void RichEditorPattern::HandleImageHoverEvent(const MouseInfo& mouseInfo)
{
    CHECK_NULL_VOID(mouseInfo.GetAction() == MouseAction::MOVE && !isMousePressed_);
    ACE_SCOPED_TRACE("RichEditorHandleImageHoverEvent");
    PointF mouseOffset = { mouseInfo.GetLocalLocation().GetX(), mouseInfo.GetLocalLocation().GetY() };
    HoverInfo info = CreateHoverInfo(mouseInfo);
    for (auto it = hoverableNodes.begin(); it != hoverableNodes.end();) {
        auto spanNode = it->Upgrade();
        if (!spanNode) {
            it = hoverableNodes.erase(it);
            continue;
        }
        const auto& imageSpanItem = spanNode->GetSpanItem();
        if (!imageSpanItem || !imageSpanItem->onHover_) {
            it = hoverableNodes.erase(it);
            continue;
        }
        const auto& geoNode = spanNode->GetGeometryNode();
        CHECK_NULL_CONTINUE(geoNode);
        const auto& imageRect = geoNode->GetFrameRect();
        if (!imageRect.IsInRegion(mouseOffset)) {
            ++it;
            continue;
        }
        if (!lastHoverSpanItem_) {
            imageSpanItem->onHover_(true, info);
            lastHoverSpanItem_ = imageSpanItem;
            lastHoverInfo_ = info;
            return;
        }
        CHECK_NULL_VOID(Referenced::RawPtr(lastHoverSpanItem_) != Referenced::RawPtr(imageSpanItem));
        imageSpanItem->onHover_(true, info);
        lastHoverSpanItem_->onHover_(false, info);
        lastHoverSpanItem_ = imageSpanItem;
        lastHoverInfo_ = info;
        return;
    }

    if (lastHoverSpanItem_) {
        lastHoverSpanItem_->onHover_(false, info);
        lastHoverSpanItem_.Reset();
    }
}

void RichEditorPattern::AddOprationWhenAddImage(int32_t beforeCaretPos)
{
    OperationRecord record;
    record.beforeCaretPosition = beforeCaretPos;
    record.addText = u" ";
    ClearRedoOperationRecords();
    record.afterCaretPosition = record.beforeCaretPosition + 1;
    AddOperationRecord(record);
}

void RichEditorPattern::ResetSelectionAfterAddSpan(bool isPaste)
{
    if (isPaste || !textSelector_.IsValid()) {
        return;
    }
    CloseSelectOverlay();
    ResetSelection();
    if (isEditing_ && !caretVisible_) {
        StartTwinkling();
    }
}

void RichEditorPattern::AddSpanItem(const RefPtr<SpanItem>& item, int32_t offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (offset == -1) {
        offset = static_cast<int32_t>(host->GetChildren().size());
    }
    offset = std::clamp(offset, 0, static_cast<int32_t>(host->GetChildren().size()) - 1);
    auto it = spans_.begin();
    std::advance(it, offset);
    spans_.insert(it, item);
    UpdateSpanPosition();
}

void RichEditorPattern::OnAttachToFrameNode()
{
    TextPattern::OnAttachToFrameNode();
    richEditorInstanceId_ = Container::CurrentIdSafely();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameId_ = frameNode->GetId();
    frameNode->GetRenderContext()->UpdateClipEdge(true);
    frameNode->GetRenderContext()->SetClipToFrame(true);
    StylusDetectorMgr::GetInstance()->AddTextFieldFrameNode(frameNode, WeakClaim(this));
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddWindowSizeChangeCallback(frameId_);
}

void RichEditorPattern::OnDetachFromFrameNode(FrameNode* node)
{
    TextPattern::OnDetachFromFrameNode(node);
    ScrollablePattern::OnDetachFromFrameNode(node);
    ClearOnFocusTextField(node);
    auto context = GetContext();
    IF_PRESENT(context, RemoveWindowSizeChangeCallback(frameId_));
}

int32_t RichEditorPattern::AddPlaceholderSpan(const RefPtr<UINode>& customNode, const SpanOptionBase& options)
{
    if (GetTextContentLength() >= maxLength_.value_or(INT_MAX)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "AddPlaceholderSpan: Reach the maxLength. maxLength=%{public}d", maxLength_.value_or(INT_MAX));
        return 0;
    }
    CHECK_NULL_RETURN(customNode, 0);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AddPlaceholderSpan");
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "options=%{public}s", options.ToString().c_str());
    NotifyExitTextPreview(false);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    CHECK_NULL_RETURN(placeholderSpanNode, 0);
    customNode->MountToParent(placeholderSpanNode);
    SetSelfAndChildDraggableFalse(customNode);
    IF_PRESENT(oneStepDragController_, EnableOneStepDrag(TextSpanType::BUILDER, placeholderSpanNode));
    auto focusHub = placeholderSpanNode->GetOrCreateFocusHub();
    focusHub->SetFocusable(false);
    int32_t insertIndex = options.offset.value_or(GetTextContentLength());
    AdjustSelectorForSymbol(insertIndex, HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
    int32_t spanIndex = TextSpanSplit(insertIndex);
    if (spanIndex == -1) {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
    }
    builderNodes.push_back(placeholderSpanNode);
    placeholderSpanNode->MountToParent(host, spanIndex);
    auto renderContext = placeholderSpanNode->GetRenderContext();
    IF_PRESENT(renderContext, SetNeedAnimateFlag(false));
    auto spanItem = placeholderSpanNode->GetSpanItem();
    spanItem->content = u" ";
    spanItem->SetCustomNode(customNode);
    spanItem->dragBackgroundColor_ = options.dragBackgroundColor;
    spanItem->isDragShadowNeeded_ = options.isDragShadowNeeded;
    AddSpanItem(spanItem, spanIndex);
    placeholderCount_++;
    SetCaretPosition(insertIndex + spanItem->content.length());
    ResetSelectionAfterAddSpan(false);
    auto placeholderPipelineContext = placeholderSpanNode->GetContext();
    IF_PRESENT(placeholderPipelineContext, SetDoKeyboardAvoidAnimate(false));
    SetNeedMoveCaretToContentRect();
    AddOnPlaceholderHoverEvent(placeholderSpanNode);
    placeholderSpanNode->MarkModifyDone();
    placeholderSpanNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return spanIndex;
}

void RichEditorPattern::AddOnPlaceholderHoverEvent(const RefPtr<PlaceholderSpanNode>& placeholderSpanNode)
{
    CHECK_NULL_VOID(placeholderSpanNode);
    auto inputHub = placeholderSpanNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "placeholder, on hover event isHover=%{public}d", isHover);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnPlaceholderHover(isHover);
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
}

void RichEditorPattern::OnPlaceholderHover(bool isHover)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto nodeId = host->GetId();
    if (isHover) {
        pipeline->FreeMouseStyleHoldNode(nodeId);
    } else {
        pipeline->FreeMouseStyleHoldNode();
        ChangeMouseStyle(MouseFormat::TEXT_CURSOR);
    }
}

void RichEditorPattern::SetSelfAndChildDraggableFalse(const RefPtr<UINode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto frameNode = DynamicCast<FrameNode>(customNode);
    if (frameNode) {
        auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
        IF_PRESENT(gestureEventHub, SetDragForbiddenForcely(true));
    }
    for (const auto& child : customNode->GetChildren()) {
        SetSelfAndChildDraggableFalse(child);
    }
}

int32_t RichEditorPattern::AddTextSpan(TextSpanOptions options, bool isPaste, int32_t index)
{
    if (GetTextContentLength() >= maxLength_.value_or(INT_MAX)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "AddTextSpan: Reach the maxLength. maxLength=%{public}d", maxLength_.value_or(INT_MAX));
        return 0;
    }
    auto length = CalculateTruncationLength(options.value, maxLength_.value_or(INT_MAX) - GetTextContentLength());
    if (length == 0) {
        return -1;
    }
    options.value = options.value.substr(0, length);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AddTextSpan, opts=%{public}s", ToBriefString(options).c_str());
    SEC_TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AddTextSpan, opts=%{public}s", options.ToString().c_str());
    AdjustAddPosition(options);
    NotifyExitTextPreview();
    OperationRecord record;
    auto textContentLength = GetTextContentLength();
    if (options.offset.has_value()) {
        options.offset = std::clamp(options.offset.value(), 0, textContentLength);
        AdjustSelectorForSymbol(options.offset.value(), HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
    }
    record.beforeCaretPosition = std::clamp(options.offset.value_or(textContentLength), 0, textContentLength);
    record.addText = options.value;
    RichEditorChangeValue changeValue;
    CHECK_NULL_RETURN(BeforeChangeText(changeValue, options), -1);
    ClearRedoOperationRecords();
    record.afterCaretPosition = record.beforeCaretPosition + static_cast<int32_t>(options.value.length());
    AddOperationRecord(record);
    auto ret = AddTextSpanOperation(options, isPaste, index, false);
    SetNeedMoveCaretToContentRect();
    if (!previewTextRecord_.IsValid()) {
        AfterContentChange(changeValue);
    }
    return ret;
}

void RichEditorPattern::AdjustAddPosition(TextSpanOptions& options)
{
    CHECK_NULL_VOID(IsPreviewTextInputting() && options.offset.has_value());
    auto& offset = options.offset.value();
    auto delta = offset - previewTextRecord_.startOffset;
    offset -= std::min(std::max(0, delta), previewTextRecord_.endOffset - previewTextRecord_.startOffset);
}

int32_t RichEditorPattern::AddTextSpanOperation(
    const TextSpanOptions& options, bool isPaste, int32_t index, bool needLeadingMargin, bool updateCaretPosition)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());

    int32_t spanIndex = 0;
    int32_t offset = -1;
    if (options.offset.has_value()) {
        offset = TextSpanSplit(options.offset.value(), needLeadingMargin);
        if (offset == -1) {
            spanIndex = static_cast<int32_t>(host->GetChildren().size());
        } else {
            spanIndex = offset;
        }
        spanNode->MountToParent(host, offset);
    } else if (index != -1) {
        spanNode->MountToParent(host, index);
        spanIndex = index;
    } else {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
        spanNode->MountToParent(host);
    }
    auto textStyle = options.style;
    if (options.urlAddress.has_value() && options.useThemeFontColor && textStyle.has_value()) {
        textStyle.value().SetTextColor(GetUrlSpanColor());
    }
    auto spanItem = spanNode->GetSpanItem();
    spanItem->SetTextStyle(textStyle);
    spanItem->useThemeFontColor = options.useThemeFontColor;
    spanItem->useThemeDecorationColor = options.useThemeDecorationColor;
    UpdateSpanNode(spanNode, options);
    AddSpanItem(spanItem, offset);
    if (!options.style.has_value()) {
        SetDefaultColor(spanNode);
    }
    if (options.paraStyle) {
        UpdateParagraphStyle(spanNode, *options.paraStyle);
    }
    SetGestureOptions(options.userGestureOption, spanItem);
    if (updateCaretPosition && !previewTextRecord_.IsValid()) {
        if (options.offset.has_value()) {
            SetCaretPosition(options.offset.value() + options.value.length());
        } else {
            SetCaretPosition(GetTextContentLength());
        }
    }
    ResetSelectionAfterAddSpan(isPaste);
    SpanNodeFission(spanNode);
    return spanIndex;
}

void RichEditorPattern::UpdateSpanNode(RefPtr<SpanNode> spanNode, const TextSpanOptions& options)
{
    spanNode->UpdateContent(options.value);
    if (options.style.has_value()) {
        const TextStyle& textStyle = options.style.value();
        spanNode->UpdateTextColorWithoutCheck(textStyle.GetTextColor());
        spanNode->UpdateFontSize(textStyle.GetFontSize());
        spanNode->UpdateItalicFontStyle(textStyle.GetFontStyle());
        spanNode->UpdateFontWeight(textStyle.GetFontWeight());
        spanNode->UpdateFontFamily(textStyle.GetFontFamilies());
        spanNode->UpdateTextDecoration(textStyle.GetTextDecoration());
        spanNode->UpdateTextDecorationColorWithoutCheck(textStyle.GetTextDecorationColor());
        spanNode->UpdateTextDecorationStyle(textStyle.GetTextDecorationStyle());
        spanNode->UpdateTextShadow(textStyle.GetTextShadows());
        spanNode->UpdateHalfLeading(textStyle.GetHalfLeading());
        spanNode->UpdateLineHeight(textStyle.GetLineHeight());
        spanNode->UpdateLetterSpacing(textStyle.GetLetterSpacing());
        spanNode->UpdateFontFeature(textStyle.GetFontFeatures());
        UpdateTextBackgroundStyle(spanNode, textStyle.GetTextBackgroundStyle());
    }
    UpdateUrlStyle(spanNode, options.urlAddress);
}

void RichEditorPattern::UpdateTextBackgroundStyle(
    RefPtr<SpanNode>& spanNode, const std::optional<TextBackgroundStyle>& style)
{
    CHECK_NULL_VOID(style.has_value());
    TextBackgroundStyle backgroundStyle = style.value();
    backgroundStyle.needCompareGroupId = true;
    backgroundStyle.groupId = ElementRegister::GetInstance()->MakeUniqueId();
    spanNode->UpdateTextBackgroundFromParent(backgroundStyle);
}

void RichEditorPattern::UpdateUrlStyle(RefPtr<SpanNode>& spanNode, const std::optional<std::u16string>& urlAddressOpt)
{
    CHECK_NULL_VOID(spanNode && urlAddressOpt.has_value());
    auto& spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    auto& urlAddress = urlAddressOpt.value();
 
    // handle url span callback
    std::function<void()> urlOnRelease;
    if (!urlAddress.empty()) {
        urlOnRelease = [add = UtfUtils::Str16ToStr8(urlAddress)]() {
            auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->HyperlinkStartAbility(add);
        };
    }
    spanItem->SetUrlOnReleaseEvent(std::move(urlOnRelease));
    spanItem->urlAddress = urlAddress;
 
    // handle url span color
    CHECK_NULL_VOID(spanItem->useThemeFontColor);
    if (urlAddress.empty()) {
        auto theme = GetTheme<RichEditorTheme>();
        CHECK_NULL_VOID(theme);
        const auto& themeTextStyle = theme->GetTextStyle();
        const auto& textColor = themeTextStyle.GetTextColor();
        spanNode->UpdateTextColor(textColor);
        IF_TRUE(spanItem->useThemeDecorationColor, spanNode->UpdateTextDecorationColor(textColor));
    } else {
        const auto& urlSpanColor = GetUrlSpanColor();
        spanNode->UpdateTextColor(urlSpanColor);
        IF_TRUE(spanItem->useThemeDecorationColor, spanNode->UpdateTextDecorationColor(urlSpanColor));
    }
}

int32_t RichEditorPattern::AddSymbolSpan(SymbolSpanOptions options, bool isPaste, int32_t index)
{
    if (GetTextContentLength() >= maxLength_.value_or(INT_MAX) - 1) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "AddSymbolSpan: Reach the maxLength. maxLength=%{public}d", maxLength_.value_or(INT_MAX));
        return 0;
    }
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "options=%{public}s", options.ToString().c_str());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "isPaste=%{public}d, index=%{public}d", isPaste, index);

    NotifyExitTextPreview(false);
    if (options.offset.has_value()) {
        options.offset = std::clamp(options.offset.value(), 0, GetTextContentLength());
        AdjustSelectorForSymbol(options.offset.value(), HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
    }
    RichEditorChangeValue changeValue;
    CHECK_NULL_RETURN(BeforeAddSymbol(changeValue, options), -1);
    OperationRecord record;
    record.beforeCaretPosition = options.offset.value_or(static_cast<int32_t>(GetTextContentLength()));
    record.addText = u" ";
    ClearRedoOperationRecords();
    record.afterCaretPosition = record.beforeCaretPosition + 1;
    AddOperationRecord(record);
    auto ret = AddSymbolSpanOperation(options, isPaste, index);
    SetNeedMoveCaretToContentRect();
    AfterContentChange(changeValue);
    return ret;
}

int32_t RichEditorPattern::AddSymbolSpanOperation(const SymbolSpanOptions& options, bool isPaste, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);

    auto spanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId());

    int32_t insertIndex = options.offset.value_or(GetTextContentLength());
    int32_t spanIndex = TextSpanSplit(insertIndex);
    if (spanIndex == -1) {
        spanIndex = static_cast<int32_t>(host->GetChildren().size());
    }
    spanNode->MountToParent(host, spanIndex);
    spanNode->UpdateContent(options.symbolId);
    if (options.style.has_value()) {
        spanNode->UpdateFontSize(options.style.value().GetFontSize());
        spanNode->UpdateFontWeight(options.style.value().GetFontWeight());
        spanNode->UpdateSymbolColorList(options.style.value().GetSymbolColorList());
        spanNode->UpdateSymbolRenderingStrategy(options.style.value().GetRenderStrategy());
        spanNode->UpdateSymbolEffectStrategy(options.style.value().GetEffectStrategy());
        spanNode->UpdateSymbolType(options.style.value().GetSymbolType());
        spanNode->UpdateFontFamily(options.style.value().GetFontFamilies());
    }
    auto spanItem = spanNode->GetSpanItem();
    spanItem->content = u"  ";
    spanItem->spanItemType = SpanItemType::SYMBOL;
    spanItem->SetSymbolId(options.symbolId);
    spanItem->SetTextStyle(options.style);
    spanItem->SetResourceObject(options.resourceObject);
    AddSpanItem(spanItem, spanIndex);
    SetCaretPosition(insertIndex + spanItem->content.length());
    ResetSelectionAfterAddSpan(false);
    SpanNodeFission(spanNode);
    return spanIndex;
}

bool RichEditorPattern::BeforeAddSymbol(RichEditorChangeValue& changeValue, const SymbolSpanOptions& options)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);

    int32_t contentLength = GetTextContentLength();
    int32_t insertIndex = options.offset.value_or(contentLength);
    insertIndex = std::clamp(insertIndex, 0, contentLength);

    changeValue.SetRangeBefore({ insertIndex, insertIndex });
    changeValue.SetRangeAfter({ insertIndex, insertIndex + SYMBOL_SPAN_LENGTH });
    RichEditorAbstractSpanResult retInfo;
    TextInsertValueInfo info;
    CalcInsertValueObj(info, insertIndex, true);
    int32_t spanIndex = info.GetSpanIndex();
    retInfo.SetSpanIndex(spanIndex);
    retInfo.SetOffsetInSpan(0);
    retInfo.SetValueString(std::to_string(options.symbolId));
    retInfo.SetEraseLength(SYMBOL_SPAN_LENGTH);
    retInfo.SetSpanRangeStart(insertIndex);
    retInfo.SetSpanRangeEnd(insertIndex + SYMBOL_SPAN_LENGTH);
    retInfo.SetSpanType(SpanResultType::SYMBOL);

    TextStyle style = options.style.value_or(TextStyle());
    retInfo.SetSymbolSpanStyle(SymbolSpanStyle(style));
    retInfo.SetValueResource(options.resourceObject);

    changeValue.SetRichEditorReplacedSymbolSpans(retInfo);
    auto ret = eventHub->FireOnWillChange(changeValue);
    return ret;
}

void RichEditorPattern::AfterContentChange(RichEditorChangeValue& changeValue)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    if (eventHub && eventHub->HasOnDidChange()) {
        eventHub->FireOnDidChange(changeValue);
    }
    ForceTriggerAvoidOnCaretChange();
}

void RichEditorPattern::SpanNodeFission(RefPtr<SpanNode>& spanNode)
{
    auto spanItem = spanNode->GetSpanItem();
    auto wContent = spanItem->content;
    auto spanStart = spanItem->position - wContent.length();
    for (size_t i = 0; i < wContent.length(); i++) {
        if (wContent[i] == '\n') {
            TextSpanSplit(static_cast<int32_t>(spanStart + i + 1));
        }
    }
    UpdateSpanPosition();
}

void RichEditorPattern::DeleteSpans(const RangeOptions& options)
{
    IF_TRUE(previewTextRecord_.previewTextExiting, TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "exiting preview"));
    IF_TRUE(IsPreviewTextInputting() && !previewTextRecord_.previewTextExiting, NotifyExitTextPreview());
    auto length = GetTextContentLength();
    int32_t start = options.start.value_or(0);
    int32_t end = options.end.value_or(length);
    if (start > end) {
        std::swap(start, end);
    }
    start = std::max(0, start);
    end = std::min(length, end);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "delete spans range=[%{public}d, %{public}d]", start, end);
    if (start > length || end < 0 || start == end) {
        return;
    }
    AdjustSelector(start, end);
    OperationRecord record;
    record.beforeCaretPosition = start;
    std::u16string u16valueString;
    GetContentBySpans(u16valueString);
    record.deleteText = u16valueString.substr(start, end - start);
    RichEditorChangeValue changeValue;
    changeValue.SetRangeBefore({ start, end });
    changeValue.SetRangeAfter({ start, start });
    if (auto eventHub = GetEventHub<RichEditorEventHub>(); eventHub) {
        CHECK_NULL_VOID(eventHub->FireOnWillChange(changeValue));
    }
    ClearRedoOperationRecords();
    record.afterCaretPosition = start;
    AddOperationRecord(record);
    DeleteSpansOperation(start, end);
    AfterContentChange(changeValue);
}

void RichEditorPattern::DeleteSpansOperation(int32_t start, int32_t end)
{
    auto startInfo = GetSpanPositionInfo(start);
    auto endInfo = GetSpanPositionInfo(end - 1);
    if (startInfo.spanIndex_ == endInfo.spanIndex_) {
        DeleteSpanByRange(start, end, startInfo);
    } else {
        DeleteSpansByRange(start, end, startInfo, endInfo);
    }
    RemoveEmptySpanItems();
    if (textSelector_.IsValid()) {
        SetCaretPosition(textSelector_.GetTextStart());
        CloseSelectOverlay();
        ResetSelection();
    }
    SetCaretOffset(start);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetChildren().empty() || GetTextContentLength() == 0) {
        SetCaretPosition(0);
        textForDisplay_.clear();
    }
    UpdateSpanPosition();
}

void RichEditorPattern::RemoveEmptySpanItems()
{
    for (auto it = spans_.begin(); it != spans_.end();) {
        if ((*it)->content.empty()) {
            it = spans_.erase(it);
        } else {
            ++it;
        }
    }
}

void RichEditorPattern::RemoveEmptySpanNodes()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto& spanNodes = host->GetChildren();
    for (auto it = spanNodes.begin(); it != spanNodes.end();) {
        auto spanNode = AceType::DynamicCast<SpanNode>(*it);
        if (!spanNode) {
            ++it;
            continue;
        }
        if (spanNode->GetSpanItem()->content.empty()) {
            it = host->RemoveChild(spanNode);
        } else {
            ++it;
        }
    }
}

void RichEditorPattern::RemoveEmptySpans()
{
    RemoveEmptySpanItems();
    RemoveEmptySpanNodes();
}

void RichEditorPattern::DeleteSpanByRange(int32_t start, int32_t end, SpanPositionInfo info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrens = host->GetChildren();
    auto it = childrens.begin();
    std::advance(it, info.spanIndex_);
    CHECK_NULL_VOID(it != childrens.end());
    if (start == info.spanStart_ && end == info.spanEnd_) {
        ClearContent(*it);
        host->RemoveChild(*it);
    } else {
        auto spanNode = DynamicCast<SpanNode>(*it);
        CHECK_NULL_VOID(spanNode);
        auto spanItem = spanNode->GetSpanItem();
        auto beforStr = spanItem->content.substr(0, start - info.spanStart_);
        auto endStr = spanItem->content.substr(end - info.spanStart_);
        spanNode->UpdateContent(beforStr + endStr);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::DeleteSpansByRange(
    int32_t start, int32_t end, SpanPositionInfo startInfo, SpanPositionInfo endInfo)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childrens = host->GetChildren();
    CHECK_NULL_VOID(!childrens.empty());

    auto itStart = childrens.begin();
    if (startInfo.spanIndex_ >= static_cast<int32_t>(childrens.size())) {
        std::advance(itStart, static_cast<int32_t>(childrens.size()) - 1);
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "startInfo.spanIndex_ is larger than childrens size");
    } else {
        std::advance(itStart, startInfo.spanIndex_);
    }
    CHECK_NULL_VOID(itStart != childrens.end());
    auto saveStartSpan = (start == startInfo.spanStart_) ? 0 : 1;
    if (saveStartSpan) {
        auto spanNodeStart = DynamicCast<SpanNode>(*itStart);
        CHECK_NULL_VOID(spanNodeStart);
        auto spanItemStart = spanNodeStart->GetSpanItem();
        auto beforStr = spanItemStart->content.substr(0, start - startInfo.spanStart_);
        spanNodeStart->UpdateContent(beforStr);
    }
    auto itEnd = childrens.begin();
    std::advance(itEnd, endInfo.spanIndex_);
    auto delEndSpan = (end == endInfo.spanEnd_) ? 1 : 0;
    if (!delEndSpan) {
        auto spanNodeEnd = DynamicCast<SpanNode>(*itEnd);
        CHECK_NULL_VOID(spanNodeEnd);
        auto spanItemEnd = spanNodeEnd->GetSpanItem();
        auto endStr = spanItemEnd->content.substr(end - endInfo.spanStart_, endInfo.spanEnd_ - end);
        spanNodeEnd->UpdateContent(endStr);
    }
    auto startIter = childrens.begin();
    std::advance(startIter, startInfo.spanIndex_ + saveStartSpan);
    auto endIter = childrens.begin();
    std::advance(endIter, endInfo.spanIndex_);
    for (auto iter = startIter; iter != endIter; ++iter) {
        ClearContent(*iter);
        host->RemoveChild(*iter);
    }
    if (endIter != childrens.end() && delEndSpan) {
        ClearContent(*endIter);
        host->RemoveChild(*endIter);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

std::u16string RichEditorPattern::GetLeftTextOfCursor(int32_t number)
{
    if (number > caretPosition_) {
        number = caretPosition_;
    }
    auto start = caretPosition_;
    if (IsSelected()) {
        start = std::min(textSelector_.GetStart(), textSelector_.GetEnd());
    }
    return GetSelectedText(start - number, start);
}

std::u16string RichEditorPattern::GetRightTextOfCursor(int32_t number)
{
    auto end = caretPosition_;
    if (IsSelected()) {
        end = std::max(textSelector_.GetStart(), textSelector_.GetEnd());
    }
    return GetSelectedText(end, end + number);
}

int32_t RichEditorPattern::GetTextIndexAtCursor()
{
    return caretPosition_;
}

void RichEditorPattern::ClearContent(const RefPtr<UINode>& child)
{
    CHECK_NULL_VOID(child);
    if (child->GetTag() == V2::SPAN_ETS_TAG) {
        auto spanNode = DynamicCast<SpanNode>(child);
        if (spanNode) {
            spanNode->UpdateContent(u"");
            spanNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        return;
    }
    auto imageSpanNode = DynamicCast<ImageSpanNode>(child);
    if (imageSpanNode) {
        imageSpanNode->GetSpanItem()->content.clear();
        imageSpanNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto placeholderSpanNode = DynamicCast<PlaceholderSpanNode>(child);
    if (placeholderSpanNode) {
        placeholderSpanNode->GetSpanItem()->content.clear();
        placeholderSpanNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

SpanPositionInfo RichEditorPattern::GetSpanPositionInfo(int32_t position)
{
    SpanPositionInfo spanPositionInfo(-1, -1, -1, -1);
    CHECK_NULL_RETURN(!spans_.empty(), spanPositionInfo);
    position = std::clamp(position, 0, GetTextContentLength());
    // find the spanItem where the position is
    auto it = std::find_if(spans_.begin(), spans_.end(), [position](const RefPtr<SpanItem>& spanItem) {
        return (spanItem->position - static_cast<int32_t>(spanItem->content.length()) <= position) &&
               (position < spanItem->position);
    });
    if (it != spans_.end() && (*it)->unicode != 0 && (*it)->position - caretPosition_ + moveLength_ == 1) {
        it++;
        moveLength_++;
        position++;
    }

    // the position is at the end
    if (it == spans_.end()) {
        return spanPositionInfo;
    }

    spanPositionInfo.spanIndex_ = std::distance(spans_.begin(), it);
    int32_t contentLen = static_cast<int32_t>((*it)->content.length());
    spanPositionInfo.spanStart_ = (*it)->position - contentLen;
    spanPositionInfo.spanEnd_ = (*it)->position;
    spanPositionInfo.spanOffset_ = position - spanPositionInfo.spanStart_;
    return spanPositionInfo;
}

void RichEditorPattern::CopyTextSpanStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target, bool needLeadingMargin)
{
    CopyTextSpanFontStyle(source, target);
    CopyTextSpanLineStyle(source, target, needLeadingMargin);
    CopyTextSpanUrlStyle(source, target);
}

void RichEditorPattern::CopyTextSpanFontStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target)
{
    CHECK_NULL_VOID(source);
    CHECK_NULL_VOID(source->GetTag() == V2::SPAN_ETS_TAG);
    CHECK_NULL_VOID(target);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, FontSize);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextColor);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, ItalicFontStyle);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, FontWeight);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, FontFamily);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextDecoration);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextDecorationColor);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextDecorationStyle);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextCase);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, LineHeight);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, HalfLeading);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, LetterSpacing);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, FontFeature);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextShadow);
    target->GetSpanItem()->useThemeFontColor = source->GetSpanItem()->useThemeFontColor;
    target->GetSpanItem()->useThemeDecorationColor = source->GetSpanItem()->useThemeDecorationColor;
    UpdateTextBackgroundStyle(target, source->GetTextBackgroundStyle());
}

void RichEditorPattern::CopyTextSpanLineStyle(
    RefPtr<SpanNode>& source, RefPtr<SpanNode>& target, bool needLeadingMargin)
{
    CHECK_NULL_VOID(source);
    CHECK_NULL_VOID(target);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, TextAlign);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, WordBreak);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, LineBreakStrategy);
    COPY_SPAN_STYLE_IF_PRESENT(source, target, ParagraphSpacing);
    needLeadingMargin |= previewTextRecord_.previewTextHasStarted;
    if (source->HasLeadingMargin()) {
        auto leadingMargin = source->GetLeadingMarginValue({});
        if (!needLeadingMargin) {
            leadingMargin.pixmap.Reset();
        }
        target->UpdateLeadingMargin(leadingMargin);
    }
}

void RichEditorPattern::CopyTextSpanUrlStyle(RefPtr<SpanNode>& source, RefPtr<SpanNode>& target)
{
    CHECK_NULL_VOID(source && source->GetTag() == V2::SPAN_ETS_TAG);
    CHECK_NULL_VOID(target && target->GetTag() == V2::SPAN_ETS_TAG);
    const auto& sourceSpanItem = source->GetSpanItem();
    const auto& targetSpanItem = target->GetSpanItem();
    CHECK_NULL_VOID(sourceSpanItem && targetSpanItem);
    targetSpanItem->urlOnRelease = sourceSpanItem->urlOnRelease;
    targetSpanItem->urlAddress = sourceSpanItem->urlAddress;
}

void RichEditorPattern::CopyGestureOption(const RefPtr<SpanNode>& source, RefPtr<SpanNode>& target)
{
    CHECK_NULL_VOID(source);
    CHECK_NULL_VOID(target);
    auto sourceItem = source->GetSpanItem();
    CHECK_NULL_VOID(sourceItem);
    auto targetItem = target->GetSpanItem();
    CHECK_NULL_VOID(targetItem);

    if (sourceItem->onClick) {
        auto tmpClickFunc = sourceItem->onClick;
        targetItem->SetOnClickEvent(std::move(tmpClickFunc));
    }
    if (sourceItem->onLongPress) {
        auto tmpLongPressFunc = sourceItem->onLongPress;
        targetItem->SetLongPressEvent(std::move(tmpLongPressFunc));
    }
    if (sourceItem->onDoubleClick) {
        auto tmpDoubleClickFunc = sourceItem->onDoubleClick;
        targetItem->SetDoubleClickEvent(std::move(tmpDoubleClickFunc));
    }
    if (sourceItem->onHover) {
        auto tmpHoverFunc = sourceItem->onHover;
        targetItem->SetHoverEvent(std::move(tmpHoverFunc));
    }
}

int32_t RichEditorPattern::TextSpanSplit(int32_t position, bool needLeadingMargin)
{
    CHECK_NULL_RETURN(!spans_.empty(), -1);

    SpanPositionInfo positionInfo = GetSpanPositionInfo(position);
    int32_t spanIndex = positionInfo.spanIndex_;
    int32_t spanStart = positionInfo.spanStart_;
    int32_t spanEnd = positionInfo.spanEnd_;
    int32_t offsetInSpan = positionInfo.spanOffset_;
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT,
        "position=%{public}d, spanIndex=%{public}d, spanRange=[%{public}d,%{public}d], offsetInSpan=%{public}d",
        position, spanIndex, spanStart, spanEnd, offsetInSpan);

    CHECK_NULL_RETURN((offsetInSpan > 0), spanIndex);

    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto spanNode = DynamicCast<SpanNode>(host->GetChildAtIndex(spanIndex));
    CHECK_NULL_RETURN(spanNode, -1);

    auto spanItem = spanNode->GetSpanItem();
    auto spanItemContent = spanItem->content;
    offsetInSpan = std::min(offsetInSpan, static_cast<int32_t>(spanItemContent.length()));

    spanNode->UpdateContent(spanItemContent.substr(0, offsetInSpan));
    spanItem->position = spanStart + offsetInSpan;

    auto newSpanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    CHECK_NULL_RETURN(newSpanNode, -1);

    CopyTextSpanStyle(spanNode, newSpanNode, needLeadingMargin);
    CopyGestureOption(spanNode, newSpanNode);
    newSpanNode->UpdateContent(spanItemContent.substr(offsetInSpan));
    newSpanNode->MountToParent(host, spanIndex + 1);

    auto newSpanItem = newSpanNode->GetSpanItem();
    newSpanItem->rangeStart = spanStart + offsetInSpan;
    newSpanItem->position = spanEnd;

    auto spanIter = spans_.begin();
    std::advance(spanIter, spanIndex + 1);
    spans_.insert(spanIter, newSpanItem);

    return spanIndex + 1;
}

int32_t RichEditorPattern::GetCaretPosition()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "GetCaretPosition");
    return caretPosition_;
}

bool RichEditorPattern::SetCaretOffset(int32_t caretPosition)
{
    if (IsPreviewTextInputting()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "intercept operation in previewText state");
        return false;
    }
    int32_t inputCaretPosition = caretPosition;
    AdjustSelector(caretPosition, HandleType::SECOND);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "setCaretOffset, in=%{public}d, afterAdjust=%{public}d",
        inputCaretPosition, caretPosition);
    bool success = SetCaretPosition(caretPosition);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (focusHub->IsCurrentFocus()) {
        isCursorAlwaysDisplayed_ = false;
        StartTwinkling();
    }
    CloseSelectOverlay();
    ResetSelection();
    return success;
}

OffsetF RichEditorPattern::CalcCursorOffsetByPosition(
    int32_t position, float& selectLineHeight, bool downStreamFirst, bool needLineHighest)
{
    selectLineHeight = 0.0f;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0, 0));
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, OffsetF(0, 0));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = richTextRect_.GetOffset();
    needLineHighest |= IsCustomSpanInCaretPos(position, downStreamFirst);
    auto startOffset = paragraphs_.ComputeCursorOffset(position, selectLineHeight, downStreamFirst, needLineHighest);
    auto children = host->GetChildren();
    if (NearZero(selectLineHeight)) {
        if (children.empty() || GetTextContentLength() == 0) {
            return textPaintOffset - rootOffset;
        }
        if (std::all_of(children.begin(), children.end(), [](RefPtr<UINode>& node) {
                CHECK_NULL_RETURN(node, false);
                return (node->GetTag() == V2::IMAGE_ETS_TAG || node->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG);
            })) {
            bool isTail = false;
            auto it = children.begin();
            if (position >= static_cast<int32_t>(children.size())) {
                std::advance(it, (static_cast<int32_t>(children.size()) - 1));
                isTail = true;
            } else {
                std::advance(it, position);
            }
            if (it == children.end()) {
                return startOffset;
            }
            auto imageNode = DynamicCast<FrameNode>(*it);
            if (imageNode) {
                auto geometryNode = imageNode->GetGeometryNode();
                CHECK_NULL_RETURN(geometryNode, OffsetF(0.0f, 0.0f));
                startOffset = geometryNode->GetMarginFrameOffset();
                selectLineHeight = geometryNode->GetMarginFrameSize().Height();
                startOffset += isTail ? OffsetF(geometryNode->GetMarginFrameSize().Width(), 0.0f) : OffsetF(0.0f, 0.0f);
            }
            return startOffset;
        }
    }
    auto caretOffset = startOffset + textPaintOffset + rootOffset;
    CHECK_NULL_RETURN(overlayMod_, caretOffset);
    caretOffset.SetX(std::clamp(caretOffset.GetX(), 0.0f, richTextRect_.Right()));
    return caretOffset;
}

void RichEditorPattern::HandleCurrentPositionParagraphInfo(float& lastLineTop, float& paragraphSpacing)
{
    auto paragraphInfo = paragraphs_.GetParagrahInfo(caretPosition_);
    paragraphSpacing = paragraphInfo.paragraphStyle.paragraphSpacing.ConvertToPx();
    float lastLineHeight = 0.0f;
    CHECK_EQUAL_VOID(paragraphInfo.end - 1 >= paragraphInfo.start, false);
    lastLineTop = CalcCursorOffsetByPosition(paragraphInfo.end -1, lastLineHeight, true, true).GetY();
}

bool RichEditorPattern::IsCustomSpanInCaretPos(int32_t position, bool downStreamFirst)
{
    CHECK_NULL_RETURN((isSpanStringMode_ && styledString_), false);
    auto start = downStreamFirst ? position : position - 1;
    start = std::clamp(start, 0, GetTextContentLength());
    auto lastStyles = styledString_->GetSpans(start, 1);
    for (auto& style : lastStyles) {
        if (style && style->GetSpanType() == SpanType::CustomSpan) {
            return true;
        }
    }
    return false;
}

void RichEditorPattern::SetCaretPositionWithAffinity(PositionWithAffinity positionWithAffinity)
{
    auto currentPosition = static_cast<int32_t>(positionWithAffinity.position_);
    SetCaretPosition(currentPosition);
    caretAffinityPolicy_ = (positionWithAffinity.affinity_ == TextAffinity::UPSTREAM)
                                ? CaretAffinityPolicy::UPSTREAM_FIRST
                                : CaretAffinityPolicy::DOWNSTREAM_FIRST;
}

bool RichEditorPattern::SetCaretPosition(int32_t pos, bool needNotifyImf)
{
    auto correctPos = std::clamp(pos, 0, GetTextContentLength());
    IF_TRUE(!isModifyingContent_, AdjustSelector(correctPos, HandleType::SECOND));
    ResetLastClickOffset();
    caretAffinityPolicy_ = CaretAffinityPolicy::DEFAULT;
    CHECK_NULL_RETURN((pos == correctPos), false);
    if (caretPosition_ != correctPos) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "caret:%{public}d->%{public}d", caretPosition_, correctPos);
        lastCaretPosition_ = caretPosition_;
        caretPosition_ = correctPos;
        FireOnSelectionChange(caretPosition_);
        if (caretChangeListener_) {
            caretChangeListener_(caretPosition_);
        }
    }
    if (needNotifyImf) {
        UpdateCaretInfoToController();
    }
    return true;
}

void RichEditorPattern::FireOnSelectionChange(const int32_t caretPosition)
{
    if (!textSelector_.SelectNothing() || !caretTwinkling_) {
        return;
    }
    FireOnSelectionChange(caretPosition, caretPosition);
}

void RichEditorPattern::FireOnSelectionChange(const TextSelector& selector)
{
    if (selector.SelectNothing()) {
        return;
    }
    FireOnSelectionChange(selector.GetStart(), selector.GetEnd());
}

void RichEditorPattern::FireOnSelectionChange(int32_t start, int32_t end, bool isForced)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    CHECK_NULL_VOID(isForced || HasFocus() || dataDetectorAdapter_->hasClickedMenuOption_);
    bool isSingleHandle = selectOverlay_->IsSingleHandle();
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "onSelectionChange, range=[%{public}d,%{public}d], isTwinkling=%{public}d, "
        "isSingleHandle=%{public}d", start, end, caretTwinkling_, isSingleHandle);
    if (start < 0 || end < 0) {
        return;
    }
    if (start == end && !caretTwinkling_ && !isSingleHandle) {
        return;
    }
    if (start > end) {
        std::swap(start, end);
    }
    auto range = SelectionRangeInfo(start, end);
    if (range == lastSelectionRange_) {
        return;
    }
    lastSelectionRange_ = std::move(range);
    eventHub->FireOnSelectionChange(&range);
}

bool RichEditorPattern::GetCaretVisible() const
{
    return caretVisible_;
}

void RichEditorPattern::OnWindowHide()
{
    ScrollablePattern::OnWindowHide();
}

void RichEditorPattern::SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetUpdateSpanStyle");
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "updateSpanStyle=%{public}s", updateSpanStyle.ToString().c_str());
    updateSpanStyle_ = updateSpanStyle;
}

UpdateSpanStyle RichEditorPattern::GetUpdateSpanStyle()
{
    return updateSpanStyle_;
}

void RichEditorPattern::SetTypingStyle(std::optional<struct UpdateSpanStyle> typingStyle,
    std::optional<TextStyle> textStyle)
{
    typingStyle_ = typingStyle;
    typingTextStyle_ = textStyle;
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        IF_TRUE(typingStyle_->updateTextBackgroundStyle,
            typingStyle_->updateTextBackgroundStyle->needCompareGroupId = false);
        auto textBackgroundStyle = typingTextStyle_->GetTextBackgroundStyle();
        if (textBackgroundStyle) {
            textBackgroundStyle->needCompareGroupId = false;
            typingTextStyle_->SetTextBackgroundStyle(textBackgroundStyle);
        }
    }
    presetParagraph_ = nullptr;
    if (spans_.empty() || !previewTextRecord_.previewContent.empty()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

std::optional<struct UpdateSpanStyle> RichEditorPattern::GetTypingStyle()
{
    return typingStyle_;
}

void RichEditorPattern::UpdateFontFeatureTextStyle(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle)
{
    if (updateSpanStyle.updateFontFeature.has_value()) {
        spanNode->UpdateFontFeature(textStyle.GetFontFeatures());
    }
}

void RichEditorPattern::UpdateTextStyle(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle)
{
    CHECK_NULL_VOID(spanNode->GetTag() == V2::SPAN_ETS_TAG);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateFontFeatureTextStyle(spanNode, updateSpanStyle, textStyle);
    if (updateSpanStyle.updateTextColor.has_value()) {
        spanNode->UpdateTextColorWithoutCheck(textStyle.GetTextColor());
        spanNode->GetSpanItem()->useThemeFontColor = false;
    }
    if (updateSpanStyle.updateLineHeight.has_value()) {
        spanNode->UpdateLineHeight(textStyle.GetLineHeight());
    }
    if (updateSpanStyle.updateHalfLeading.has_value()) {
        spanNode->UpdateHalfLeading(textStyle.GetHalfLeading());
    }
    if (updateSpanStyle.updateLetterSpacing.has_value()) {
        spanNode->UpdateLetterSpacing(textStyle.GetLetterSpacing());
    }
    if (updateSpanStyle.updateFontSize.has_value()) {
        spanNode->UpdateFontSize(textStyle.GetFontSize());
    }
    if (updateSpanStyle.updateItalicFontStyle.has_value()) {
        spanNode->UpdateItalicFontStyle(textStyle.GetFontStyle());
    }
    if (updateSpanStyle.updateFontWeight.has_value()) {
        spanNode->UpdateFontWeight(textStyle.GetFontWeight());
    }
    if (updateSpanStyle.updateFontFamily.has_value()) {
        spanNode->UpdateFontFamily(textStyle.GetFontFamilies());
    }
    UpdateDecoration(spanNode, updateSpanStyle, textStyle);
    if (updateSpanStyle.updateTextShadows.has_value()) {
        spanNode->UpdateTextShadow(textStyle.GetTextShadows());
    }
    if (updateSpanStyle.updateTextBackgroundStyle.has_value()) {
        UpdateTextBackgroundStyle(spanNode, textStyle.GetTextBackgroundStyle());
    }
    UpdateUrlStyle(spanNode, updateSpanStyle.updateUrlAddress);

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::UpdateDecoration(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle)
{
    if (updateSpanStyle.updateTextDecoration.has_value()) {
        spanNode->UpdateTextDecoration(textStyle.GetTextDecoration());
        spanNode->GetSpanItem()->useThemeDecorationColor = false;
    }
    if (updateSpanStyle.updateTextDecorationColor.has_value()) {
        spanNode->UpdateTextDecorationColorWithoutCheck(textStyle.GetTextDecorationColor());
    }
    if (updateSpanStyle.updateTextDecorationStyle.has_value()) {
        spanNode->UpdateTextDecorationStyle(textStyle.GetTextDecorationStyle());
    }
}

void RichEditorPattern::UpdateSymbolStyle(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle)
{
    CHECK_NULL_VOID(spanNode->GetTag() == V2::SYMBOL_SPAN_ETS_TAG);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateFontFeatureTextStyle(spanNode, updateSpanStyle, textStyle);
    if (updateSpanStyle.updateSymbolFontSize.has_value()) {
        spanNode->UpdateFontSize(updateSpanStyle.updateSymbolFontSize.value());
    }
    if (updateSpanStyle.updateSymbolFontWeight.has_value()) {
        spanNode->UpdateFontWeight(updateSpanStyle.updateSymbolFontWeight.value());
    }
    if (updateSpanStyle.updateSymbolColor.has_value()) {
        spanNode->UpdateSymbolColorList(updateSpanStyle.updateSymbolColor.value());
    }
    if (updateSpanStyle.updateSymbolRenderingStrategy.has_value()) {
        spanNode->UpdateSymbolRenderingStrategy(updateSpanStyle.updateSymbolRenderingStrategy.value());
    }
    if (updateSpanStyle.updateSymbolEffectStrategy.has_value()) {
        spanNode->UpdateSymbolEffectStrategy(updateSpanStyle.updateSymbolEffectStrategy.value());
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

bool RichEditorPattern::HasSameTypingStyle(const RefPtr<SpanNode>& spanNode)
{
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, false);
    auto spanTextStyle = spanItem->GetTextStyle();
    if (spanTextStyle.has_value() && typingTextStyle_.has_value()) {
        return spanTextStyle.value() == typingTextStyle_.value();
    } else {
        return !(spanTextStyle.has_value() || typingTextStyle_.has_value());
    }
}

void RichEditorPattern::UpdateImageStyle(RefPtr<FrameNode>& imageNode, const ImageSpanAttribute& imageStyle)
{
    CHECK_NULL_VOID(imageNode);
    CHECK_NULL_VOID(imageNode->GetTag() == V2::IMAGE_ETS_TAG);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    if (updateSpanStyle_.updateImageWidth.has_value() || updateSpanStyle_.updateImageHeight.has_value()) {
        imageLayoutProperty->UpdateUserDefinedIdealSize(imageStyle.size->GetSize());
    }
    if (updateSpanStyle_.updateImageFit.has_value()) {
        imageLayoutProperty->UpdateImageFit(imageStyle.objectFit.value());
    }
    if (updateSpanStyle_.updateImageVerticalAlign.has_value()) {
        imageLayoutProperty->UpdateVerticalAlign(imageStyle.verticalAlign.value());
    }
    if (updateSpanStyle_.borderRadius.has_value()) {
        auto imageRenderCtx = imageNode->GetRenderContext();
        imageRenderCtx->UpdateBorderRadius(imageStyle.borderRadius.value());
        imageRenderCtx->SetClipToBounds(true);
    }
    if (updateSpanStyle_.marginProp.has_value()) {
        imageLayoutProperty->UpdateMargin(imageStyle.marginProp.value());
    }
    UpdateImageAttribute(imageNode, imageStyle);
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    IF_PRESENT(oneStepDragController_, MarkDirtyNode(WeakClaim((ImageSpanNode*) RawPtr(imageNode))));
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::UpdateImageAttribute(RefPtr<FrameNode>& imageNode, const ImageSpanAttribute& imageStyle)
{
    CHECK_NULL_VOID(imageNode);
    auto node = DynamicCast<ImageSpanNode>(imageNode);
    CHECK_NULL_VOID(node);
    auto imageSpanItem = DynamicCast<ImageSpanItem>(node->GetSpanItem());
    CHECK_NULL_VOID(imageSpanItem);
    imageSpanItem->options.imageAttribute = imageStyle;
    imageSpanItem->MarkDirty();
}

bool RichEditorPattern::SymbolSpanUpdateStyle(
    RefPtr<SpanNode>& spanNode, struct UpdateSpanStyle updateSpanStyle, TextStyle textStyle)
{
    if (spanNode->GetTag() == V2::SYMBOL_SPAN_ETS_TAG) {
        UpdateSymbolStyle(spanNode, updateSpanStyle_, textStyle);
        return true;
    }
    return false;
}

void RichEditorPattern::UpdateSpanStyle(
    int32_t start, int32_t end, const TextStyle& textStyle, const ImageSpanAttribute& imageStyle)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "updateSpanStyle, [%{public}d,%{public}d], %{public}s",
        start, end, ToBriefString(textStyle, imageStyle, updateSpanStyle_).c_str());
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "textStyle=%{public}s, imageStyle=%{public}s",
        textStyle.ToString().c_str(), imageStyle.ToString().c_str());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AdjustSelector(start, end);
    int32_t spanStart = 0;
    int32_t spanEnd = 0;
    for (auto it = host->GetChildren().begin(); it != host->GetChildren().end(); ++it) {
        auto spanNode = DynamicCast<SpanNode>(*it);
        auto imageNode = DynamicCast<FrameNode>(*it);
        if (!spanNode) {
            if (spanEnd != 0) {
                spanStart = spanEnd;
            }
            spanEnd = spanStart + 1;
        } else {
            spanNode->GetSpanItem()->GetIndex(spanStart, spanEnd);
        }
        if (spanEnd < start) {
            continue;
        }

        if (spanStart >= start && spanEnd <= end) {
            if (spanNode) {
                UpdateSymbolStyle(spanNode, updateSpanStyle_, textStyle);
                UpdateTextStyle(spanNode, updateSpanStyle_, textStyle);
            } else {
                UpdateImageStyle(imageNode, imageStyle);
            }
            if (spanEnd == end) {
                break;
            }
        } else if ((spanStart < start && start < spanEnd) || (spanStart < end && end < spanEnd)) {
            if (SymbolSpanUpdateStyle(spanNode, updateSpanStyle_, textStyle)) {
                continue;
            }
            auto index = spanStart < start && start < spanEnd ? start : end;
            TextSpanSplit(index, true);
            --it;
        } else if (spanStart >= end) {
            break;
        }
    }
}

RefPtr<UINode> RichEditorPattern::GetChildByIndex(int32_t index) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return host->GetChildAtIndex(index);
}

void RichEditorPattern::SetResultObjectText(ResultObject& resultObject, const RefPtr<SpanItem>& spanItem)
{
    CHECK_NULL_VOID(spanItem);
    resultObject.valueString = spanItem->content;
    if (spanItem->rangeStart <= previewTextRecord_.startOffset && spanItem->position >= previewTextRecord_.endOffset) {
        resultObject.previewText = previewTextRecord_.previewContent;
    }
    resultObject.urlAddress = spanItem->urlAddress;
}

void RichEditorPattern::GetContentBySpans(std::u16string& u16Str)
{
    uint32_t length = 1;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        length += (*iter)->content.length();
    }
    u16Str.reserve(length);

    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        u16Str.append((*iter)->content);
    }
}

void RichEditorPattern::SetSelectSpanStyle(int32_t start, int32_t end, KeyCode code, bool isStart)
{
    TextStyle spanStyle;
    struct UpdateSpanStyle updateSpanStyle;
    ImageSpanAttribute imageStyle;
    auto it = std::find_if(spans_.begin(), spans_.end(), [start](const RefPtr<SpanItem>& spanItem) {
        return (spanItem->rangeStart <= start) && (start < spanItem->position);
    });
    if (it == spans_.end()) {
        return;
    }
    std::optional<TextStyle> spanTextStyle = (*it)->GetTextStyle();
    if (spanTextStyle.has_value()) {
        spanStyle = spanTextStyle.value();
    }
    HandleSelectFontStyleWrapper(code, spanStyle);
    updateSpanStyle.updateTextColor = spanStyle.GetTextColor();
    updateSpanStyle.updateFontSize = spanStyle.GetFontSize();
    updateSpanStyle.updateItalicFontStyle = spanStyle.GetFontStyle();
    updateSpanStyle.updateFontWeight = spanStyle.GetFontWeight();
    updateSpanStyle.updateFontFamily = spanStyle.GetFontFamilies();
    updateSpanStyle.updateTextDecoration = spanStyle.GetTextDecoration();
    if (!isStart) {
        auto updateSpanStyle_ = GetUpdateSpanStyle();
        switch (code) {
            case KeyCode::KEY_B:
                updateSpanStyle.updateFontWeight = updateSpanStyle_.updateFontWeight;
                spanStyle.SetFontWeight(updateSpanStyle_.updateFontWeight.value());
                break;
            case KeyCode::KEY_I:
                updateSpanStyle.updateItalicFontStyle = updateSpanStyle_.updateItalicFontStyle;
                spanStyle.SetFontStyle(updateSpanStyle_.updateItalicFontStyle.value());
                break;
            case KeyCode::KEY_U:
                updateSpanStyle.updateTextDecoration = updateSpanStyle_.updateTextDecoration;
                spanStyle.SetTextDecoration(updateSpanStyle_.updateTextDecoration.value());
                break;
            default:
                LOGW("Unsupported select operation for HandleSelectFontStyleWrapper");
                return;
        }
    }
    SetUpdateSpanStyle(updateSpanStyle);
    UpdateSpanStyle(start, end, spanStyle, imageStyle);
}

void RichEditorPattern::GetSelectSpansPositionInfo(
    int32_t& start, int32_t& end, SpanPositionInfo& startPositionSpanInfo, SpanPositionInfo& endPositionSpanInfo)
{
    bool isText = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::find_if(spans_.begin(), spans_.end(), [&start, &end, &isText](const RefPtr<SpanItem>& spanItem) {
        if ((spanItem->rangeStart <= start) && (start < spanItem->position) && start < end) {
            if (spanItem->spanItemType == NG::SpanItemType::NORMAL && spanItem->unicode == 0) {
                isText = true;
                return true;
            }
            start += spanItem->content.length();
        }
        return false;
    });
    CHECK_EQUAL_VOID(isText, false);
    std::find_if(spans_.rbegin(), spans_.rend(), [&end](const RefPtr<SpanItem>& spanItem) {
        if ((spanItem->rangeStart < end) && (end <= spanItem->position)) {
            if (spanItem->spanItemType == NG::SpanItemType::NORMAL && spanItem->unicode == 0) {
                return true;
            }
            end = spanItem->rangeStart;
        }
        return false;
    });
    startPositionSpanInfo = GetSpanPositionInfo(start);
    startPositionSpanInfo.spanIndex_ =
        std::clamp(startPositionSpanInfo.spanIndex_, 0, static_cast<int32_t>(host->GetChildren().size()) - 1);
    if (end == GetTextContentLength()) {
        endPositionSpanInfo.spanIndex_ = spans_.size() - 1;
        auto spanIter = spans_.begin();
        endPositionSpanInfo.spanIndex_ =
            std::clamp(endPositionSpanInfo.spanIndex_, 0, static_cast<int32_t>(host->GetChildren().size()) - 1);
        std::advance(spanIter, endPositionSpanInfo.spanIndex_);
        auto contentLen = (*spanIter)->content.length();
        endPositionSpanInfo.spanStart_ = (*spanIter)->position - contentLen;
        endPositionSpanInfo.spanEnd_ = (*spanIter)->position;
        endPositionSpanInfo.spanOffset_ = contentLen;
    } else {
        endPositionSpanInfo = GetSpanPositionInfo(end);
    }
    if (endPositionSpanInfo.spanIndex_ == -1) {
        endPositionSpanInfo = startPositionSpanInfo;
    }
}

std::list<RefPtr<UINode>>::const_iterator RichEditorPattern::GetSpanNodeIter(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto spanNodeIter = host->GetChildren().begin();
    std::advance(spanNodeIter, index);
    return spanNodeIter;
}

std::list<SpanPosition> RichEditorPattern::GetSelectSpanSplit(
    SpanPositionInfo& startPositionSpanInfo, SpanPositionInfo& endPositionSpanInfo)
{
    std::list<SpanPosition> resultObjects;
    int32_t spanIndex = 0;
    auto itStart = GetSpanNodeIter(startPositionSpanInfo.spanIndex_);
    auto itEnd = GetSpanNodeIter(endPositionSpanInfo.spanIndex_);
    auto itEndNext = GetSpanNodeIter(endPositionSpanInfo.spanIndex_ + 1);
    for (auto itSelect = itStart; itSelect != itEndNext; itSelect++) {
        SpanPosition resultObject;
        auto spanNode = DynamicCast<SpanNode>(*itSelect);
        if (!spanNode || spanNode->GetTag() != V2::SPAN_ETS_TAG) {
            continue;
        }
        auto spanItem = spanNode->GetSpanItem();
        if (itSelect == itStart) {
            if (startPositionSpanInfo.spanOffset_ == 0) {
                resultObject.spanRange[RichEditorSpanRange::RANGESTART] = startPositionSpanInfo.spanStart_;
            } else {
                resultObject.spanRange[RichEditorSpanRange::RANGESTART] =
                    startPositionSpanInfo.spanStart_ + startPositionSpanInfo.spanOffset_;
            }
            resultObject.spanRange[RichEditorSpanRange::RANGEEND] = startPositionSpanInfo.spanEnd_;
            resultObject.spanIndex = spanIndex;
            spanIndex++;
            resultObjects.emplace_back(resultObject);
            continue;
        }
        if (itSelect == itEnd) {
            resultObject.spanRange[RichEditorSpanRange::RANGESTART] = endPositionSpanInfo.spanStart_;
            if (endPositionSpanInfo.spanOffset_ == static_cast<int32_t>(spanItem->content.size())) {
                resultObject.spanRange[RichEditorSpanRange::RANGEEND] = endPositionSpanInfo.spanEnd_;
            } else {
                resultObject.spanRange[RichEditorSpanRange::RANGEEND] =
                    endPositionSpanInfo.spanStart_ + endPositionSpanInfo.spanOffset_;
            }
            resultObject.spanIndex = spanIndex;
            spanIndex++;
            resultObjects.emplace_back(resultObject);
            continue;
        }
        resultObject.spanRange[RichEditorSpanRange::RANGESTART] =
            spanItem->position - spanItem->content.length();
        resultObject.spanRange[RichEditorSpanRange::RANGEEND] = spanItem->position;
        resultObject.spanIndex = spanIndex;
        spanIndex++;
        resultObjects.emplace_back(resultObject);
    }
    return resultObjects;
}

std::list<SpanPosition> RichEditorPattern::GetSelectSpanInfo(int32_t start, int32_t end)
{
    SpanPositionInfo startPositionSpanInfo(-1, -1, -1, -1);
    SpanPositionInfo endPositionSpanInfo(-1, -1, -1, -1);
    std::list<SpanPosition> resultObjects;
    int32_t spanIndex = 0;
    GetSelectSpansPositionInfo(start, end, startPositionSpanInfo, endPositionSpanInfo);
    CHECK_EQUAL_RETURN(startPositionSpanInfo.spanStart_, -1, resultObjects);
    if (startPositionSpanInfo.spanIndex_ == endPositionSpanInfo.spanIndex_) {
        SpanPosition resultObject;
        resultObject.spanRange[RichEditorSpanRange::RANGESTART] = start;
        resultObject.spanRange[RichEditorSpanRange::RANGEEND] = end;
        resultObject.spanIndex = spanIndex;
        resultObjects.emplace_back(resultObject);
    } else {
        resultObjects = GetSelectSpanSplit(startPositionSpanInfo, endPositionSpanInfo);
    }
    return resultObjects;
}

SelectionInfo RichEditorPattern::GetSpansInfoByRange(int32_t start, int32_t end)
{
    auto selectionInfo = GetSpansInfo(start, end , GetSpansMethod::GETSPANS);
    auto& resultObjects = selectionInfo.GetSelectionRef().resultObjects;
    for (auto& resObj : resultObjects) {
        CHECK_NULL_CONTINUE(resObj.type == SelectSpanType::TYPESPAN);
        auto uiNode = GetChildByIndex(resObj.spanPosition.spanIndex);
        auto spanNode = DynamicCast<SpanNode>(uiNode);
        CHECK_NULL_CONTINUE(spanNode);
        auto fontFamily = spanNode->GetFontFamily();
        IF_TRUE(!fontFamily, resObj.textStyle.fontFamily.clear());
    }
    return selectionInfo;
}

void RichEditorPattern::UpdateSelectSpanStyle(int32_t start, int32_t end, KeyCode code)
{
    std::list<SpanPosition> resultObjects;
    resultObjects = GetSelectSpanInfo(start, end);
    bool isFirstText = true;
    for (auto& spanStyleIter : resultObjects) {
        SetSelectSpanStyle(spanStyleIter.spanRange[RichEditorSpanRange::RANGESTART],
            spanStyleIter.spanRange[RichEditorSpanRange::RANGEEND], code, isFirstText);
        isFirstText = false;
    }
}

bool RichEditorPattern::CheckStyledStringRangeValid(int32_t start, int32_t length)
{
    if (!styledString_ || !styledString_->CheckRange(start, length)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "range:[%{public}d-%{public}d] is invalid or styledString is null",
            start, start + length);
        return false;
    }
    return true;
}

void RichEditorPattern::UpdateSelectStyledStringStyle(int32_t start, int32_t end, KeyCode code)
{
    auto length = end - start;
    CHECK_NULL_VOID(CheckStyledStringRangeValid(start, length));
    UndoRedoRecord record;
    undoManager_->UpdateRecordBeforeChange(start, length, record, true);
    Font updateFont;
    bool isFirstSpanStylePresent;
    switch (code) {
    case KeyCode::KEY_B: {
        auto firstFontSpan = DynamicCast<FontSpan>(styledString_->GetSpan(start, 1, SpanType::Font));
        isFirstSpanStylePresent = firstFontSpan && firstFontSpan->GetFont().fontWeight == FontWeight::BOLD;
        updateFont.fontWeight = isFirstSpanStylePresent ? FontWeight::NORMAL : FontWeight::BOLD;
        UpdateStyledStringFontStyle(start, end, updateFont);
        record.AddUpdateSpanType(SpanType::Font);
        break;
    }
    case KeyCode::KEY_I: {
        auto firstFontSpan = DynamicCast<FontSpan>(styledString_->GetSpan(start, 1, SpanType::Font));
        isFirstSpanStylePresent = firstFontSpan && firstFontSpan->GetFont().fontStyle == OHOS::Ace::FontStyle::ITALIC;
        updateFont.fontStyle = isFirstSpanStylePresent ? OHOS::Ace::FontStyle::NORMAL : OHOS::Ace::FontStyle::ITALIC;
        UpdateStyledStringFontStyle(start, end, updateFont);
        record.AddUpdateSpanType(SpanType::Font);
        break;
    }
    case KeyCode::KEY_U: {
        auto firstDecorationSpan = DynamicCast<DecorationSpan>(styledString_->GetSpan(start, 1, SpanType::Decoration));
        isFirstSpanStylePresent =
            firstDecorationSpan && firstDecorationSpan->GetTextDecorationType() == TextDecoration::UNDERLINE;
        auto updateDecorationType = isFirstSpanStylePresent ? TextDecoration::NONE : TextDecoration::UNDERLINE;
        UpdateStyledStringDecorationType(start, end, updateDecorationType);
        record.AddUpdateSpanType(SpanType::Decoration);
        break;
    }
    default:
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Unsupported key code for UpdateSelectStyledStringStyle");
        return;
    }
    undoManager_->UpdateRecordAfterChange(start, length, record);
    undoManager_->RecordOperation(record);
}

template<typename T>
void RichEditorPattern::UpdateSpansStyleInRange(int32_t start, int32_t end, const RefPtr<SpanBase>& baseSpan,
    std::function<RefPtr<T>(const RefPtr<T>&)>&& updateSpanFunc)
{
    auto length = end - start;
    CHECK_NULL_VOID(CheckStyledStringRangeValid(start, length));
    CHECK_NULL_VOID(baseSpan);
    auto spanType = baseSpan->GetSpanType();
    std::vector<RefPtr<SpanBase>> updateSpans;
    updateSpans.push_back(baseSpan);
    auto originalSpans = styledString_->GetSpans(start, length, spanType);
    for (auto& originalSpan : originalSpans) {
        auto originalTypedSpan = DynamicCast<T>(originalSpan);
        CHECK_NULL_CONTINUE(originalTypedSpan)
        updateSpans.push_back(updateSpanFunc(originalTypedSpan));
    }
    paragraphCache_.Clear();
    styledString_->BindWithSpans(updateSpans);
    styledString_->NotifySpanWatcher();
}

void RichEditorPattern::UpdateStyledStringFontStyle(int32_t start, int32_t end, const Font& font)
{
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, start, end);
    auto updateFontSpanFunc = [&font](const RefPtr<FontSpan>& oriFontSpan) -> RefPtr<FontSpan> {
        CHECK_NULL_RETURN(oriFontSpan, nullptr);
        auto fontStyle = oriFontSpan->GetFont();
        if (font.fontStyle.has_value()) {
            fontStyle.fontStyle = font.fontStyle.value();
        }
        if (font.fontWeight.has_value()) {
            fontStyle.fontWeight = font.fontWeight.value();
        }
        return AceType::MakeRefPtr<FontSpan>(fontStyle, oriFontSpan->GetStartIndex(), oriFontSpan->GetEndIndex());
    };
    UpdateSpansStyleInRange<FontSpan>(start, end, fontSpan, updateFontSpanFunc);
}

void RichEditorPattern::UpdateStyledStringDecorationType(int32_t start, int32_t end, const TextDecoration& type)
{
    std::optional<Color> colorOption;
    std::optional<TextDecorationStyle> styleOption;
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(type, colorOption, styleOption, start, end);
    auto updateDecorationSpanFunc = [&type](const RefPtr<DecorationSpan>& oriDecorationSpan) -> RefPtr<DecorationSpan> {
        CHECK_NULL_RETURN(oriDecorationSpan, nullptr);
        auto decorationColor = oriDecorationSpan->GetColor();
        auto decorationStyle = oriDecorationSpan->GetTextDecorationStyle();
        return AceType::MakeRefPtr<DecorationSpan>(type, decorationColor, decorationStyle,
            oriDecorationSpan->GetStartIndex(), oriDecorationSpan->GetEndIndex());
    };
    UpdateSpansStyleInRange<DecorationSpan>(start, end, decorationSpan, updateDecorationSpanFunc);
}

void RichEditorPattern::CloseSystemMenu()
{
    if (!SelectOverlayIsOn()) {
        return;
    }
    auto selectOverlayInfo = selectOverlay_->GetSelectOverlayInfo();
    if (selectOverlayInfo && !selectOverlayInfo->menuInfo.menuBuilder) {
        CloseSelectOverlay();
    }
}

void RichEditorPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(property);
    property->SetActionSetSelection([weakPtr = WeakClaim(this)](int32_t start, int32_t end, bool isForward) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
            "Accessibility SetSelection, range=[%{public}d,%{public}d], isForward=%{public}d", start, end, isForward);
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelection(start, end, std::nullopt, isForward);
    });

    property->SetActionSetIndex([weakPtr = WeakClaim(this)](int32_t index) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Accessibility SetCaretOffset, index=%{public}d", index);
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetCaretOffset(index);
    });

    property->SetActionGetIndex([weakPtr = WeakClaim(this)]() -> int32_t {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Accessibility GetCaretPosition");
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, -1);
        return pattern->GetCaretPosition();
    });
    SetAccessibilityEditAction();
}

void RichEditorPattern::SetAccessibilityEditAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto property = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(property);
    property->SetActionSetText([weakPtr = WeakClaim(this)](const std::string& value) {
        std::u16string u16Value = UtfUtils::Str8ToStr16(value);
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "EditAction setText, length: %{public}d",
            static_cast<int32_t>(u16Value.length()));
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->InsertValue(u16Value);
    });

    property->SetActionCopy([weakPtr = WeakClaim(this)]() {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "EditAction copy");
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnCopy();
        pattern->CloseSelectionMenu();
    });

    property->SetActionCut([weakPtr = WeakClaim(this)]() {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "EditAction cut");
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnCut();
    });

    property->SetActionPaste([weakPtr = WeakClaim(this)]() {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "EditAction paste");
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnPaste();
        pattern->CloseSelectionMenu();
    });

    property->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "EditAction clearSelection");
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CloseSelectionMenu();
        pattern->ResetSelection();
        pattern->StartTwinkling();
    });
}

bool RichEditorPattern::IsAccessibilityClick()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return accessibilityProperty->GetAccessibilityFocusState();
}

std::vector<ParagraphInfo> RichEditorPattern::GetParagraphInfo(int32_t start, int32_t end)
{
    std::vector<ParagraphInfo> res;
    auto spanNodes = GetParagraphNodes(start, end);
    CHECK_NULL_RETURN(!spanNodes.empty(), {});

    auto&& firstSpan = spanNodes.front()->GetSpanItem();
    auto paraStart = firstSpan->position - static_cast<int32_t>(firstSpan->content.length());

    for (auto it = spanNodes.begin(); it != spanNodes.end(); ++it) {
        if (it == std::prev(spanNodes.end()) || (*it)->GetSpanItem()->content.back() == u'\n') {
            ParagraphInfo info;
            auto lm = (*it)->GetLeadingMarginValue({});
            std::optional<double> spacingOpt;
            if (auto spacing = (*it)->GetParagraphSpacing(); spacing.has_value()) {
                spacingOpt = spacing.value().ConvertToFp();
            }
            res.emplace_back(ParagraphInfo {
                .leadingMarginPixmap = lm.pixmap,
                .leadingMarginSize = { lm.size.Width().ToString(),
                    lm.size.Height().ToString() },
                .textAlign = static_cast<int32_t>((*it)->GetTextAlignValue(TextAlign::START)),
                .wordBreak = static_cast<int32_t>((*it)->GetWordBreakValue(WordBreak::BREAK_WORD)),
                .lineBreakStrategy = static_cast<int32_t>((*it)->GetLineBreakStrategyValue(LineBreakStrategy::GREEDY)),
                .paragraphSpacing = spacingOpt,
                .range = { paraStart, (*it)->GetSpanItem()->position },
            });
            paraStart = (*it)->GetSpanItem()->position;
        }
    }

    return res;
}

int32_t RichEditorPattern::GetParagraphLength(const std::list<RefPtr<UINode>>& spans) const
{
    if (spans.empty()) {
        return 0;
    }
    int32_t imageSpanCnt = 0;
    for (auto it = spans.rbegin(); it != spans.rend(); ++it) {
        auto spanNode = DynamicCast<SpanNode>(*it);
        if (spanNode) {
            return spanNode->GetSpanItem()->position + imageSpanCnt;
        }
        ++imageSpanCnt;
    }
    return imageSpanCnt;
}

std::vector<RefPtr<SpanNode>> RichEditorPattern::GetParagraphNodes(int32_t start, int32_t end) const
{
    CHECK_NULL_RETURN(start != end, {});
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    CHECK_NULL_RETURN(!host->GetChildren().empty(), {});

    const auto& spans = host->GetChildren();
    int32_t length = GetParagraphLength(spans);
    std::vector<RefPtr<SpanNode>> res;

    if (start >= length) {
        return res;
    }

    auto headIt = spans.begin();
    auto flagNode = headIt;
    bool isEnd = false;
    int32_t spanEnd = -1;
    while (flagNode != spans.end()) {
        auto spanNode = DynamicCast<SpanNode>(*flagNode);
        if (spanNode) {
            auto&& info = spanNode->GetSpanItem();
            spanEnd = info->position;
            isEnd = info->content.back() == u'\n';
        } else {
            ++spanEnd;
            isEnd = false;
        }
        flagNode++;
        if (spanEnd > start) {
            break;
        }
        if (isEnd) {
            headIt = flagNode;
        }
    }
    while (headIt != flagNode) {
        auto spanNode = DynamicCast<SpanNode>(*headIt);
        if (spanNode) {
            res.emplace_back(spanNode);
        }
        headIt++;
    }
    while (flagNode != spans.end() && (spanEnd < end || !isEnd)) {
        auto spanNode = DynamicCast<SpanNode>(*flagNode);
        if (spanNode) {
            res.emplace_back(spanNode);
            auto&& info = spanNode->GetSpanItem();
            spanEnd = info->position;
            isEnd = info->content.back() == u'\n';
        } else {
            ++spanEnd;
            isEnd = false;
        }
        flagNode++;
    }

    return res;
}

void RichEditorPattern::UpdateParagraphStyle(int32_t start, int32_t end, const struct UpdateParagraphStyle& style)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "updateParagraphStyle, range=[%{public}d,%{public}d]", start, end);
    auto spanNodes = GetParagraphNodes(start, end);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "spanNode cnt=%{public}d, style=%{public}s",
        static_cast<int32_t>(spanNodes.size()), style.ToString().c_str());
    for (const auto& spanNode : spanNodes) {
        UpdateParagraphStyle(spanNode, style);
    }
}

void RichEditorPattern::UpdateParagraphStyle(RefPtr<SpanNode> spanNode, const struct UpdateParagraphStyle& style)
{
    CHECK_NULL_VOID(spanNode);
    spanNode->UpdateTextAlign(style.textAlign.value_or(TextAlign::START));
    spanNode->UpdateWordBreak(style.wordBreak.value_or(WordBreak::BREAK_WORD));
    spanNode->UpdateLineBreakStrategy(style.lineBreakStrategy.value_or(LineBreakStrategy::GREEDY));
    if (style.paragraphSpacing.has_value()) {
        spanNode->UpdateParagraphSpacing(style.paragraphSpacing.value());
    } else {
        spanNode->ResetParagraphSpacing();
    }
    auto leadingMarginValue = spanNode->GetLeadingMarginValue({});
    if (style.leadingMargin.has_value() && !leadingMarginValue.CheckLeadingMargin(style.leadingMargin.value())) {
        spanNode->GetSpanItem()->leadingMargin = *style.leadingMargin;
        spanNode->UpdateLeadingMargin(*style.leadingMargin);
    }
    IF_PRESENT(GetHost(), MarkDirtyNode(PROPERTY_UPDATE_MEASURE));
}

void RichEditorPattern::ScheduleCaretTwinkling()
{
    ContainerScope scope(richEditorInstanceId_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        return;
    }

    if (isCursorAlwaysDisplayed_) {
        return;
    }

    auto weak = WeakClaim(this);
    caretTwinklingTask_.Reset([weak, instanceId = richEditorInstanceId_] {
        ContainerScope scope(instanceId);
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnCaretTwinkling();
    });
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(caretTwinklingTask_, TaskExecutor::TaskType::UI, twinklingInterval_,
        "ArkUIRichEditorScheduleCaretTwinkling");
}

void RichEditorPattern::StartTwinkling()
{
    caretTwinklingTask_.Cancel();
    caretVisible_ = true;
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretTwinkling();
    // Fire on selecion change when caret invisible -> visible
    if (!caretTwinkling_) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "StartTwinkling");
        caretTwinkling_ = true;
        FireOnSelectionChange(caretPosition_, caretPosition_);
    }
}

void RichEditorPattern::ShowCaretWithoutTwinkling()
{
    isCursorAlwaysDisplayed_ = true;
    StartTwinkling();
}

void RichEditorPattern::OnCaretTwinkling()
{
    caretTwinklingTask_.Cancel();
    caretVisible_ = !caretVisible_;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCaretTwinkling();
}

void RichEditorPattern::StopTwinkling()
{
    if (caretTwinkling_) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "StopTwinkling");
    }
    caretTwinkling_ = false;
    isCursorAlwaysDisplayed_ = false;
    caretTwinklingTask_.Cancel();
    if (caretVisible_) {
        caretVisible_ = false;
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void RichEditorPattern::HandleClickEvent(GestureEvent& info)
{
    if (selectOverlay_->GetIsHandleMoving() || isMouseSelect_) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "click rejected, isHandleMoving=%{public}d, isMouseSelect=%{public}d",
            selectOverlay_->GetIsHandleMoving(), isMouseSelect_);
        return;
    }
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!focusHub->IsFocusable()) {
        return;
    }

    if (!HasFocus() && !focusHub->IsFocusOnTouch().value_or(true)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleClickEvent fail when IsFocusOnTouch false");
        CloseSelectOverlay();
        StopTwinkling();
        return;
    }

    selectionMenuOffsetClick_ = OffsetF(
        static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
    if (dataDetectorAdapter_->hasClickedAISpan_) {
        dataDetectorAdapter_->hasClickedAISpan_ = false;
    }
    multipleClickRecognizer_->Start(info);
    if (multipleClickRecognizer_->IsTripleClick()) {
        HandleTripleClickEvent(info);
    } else if (multipleClickRecognizer_->IsDoubleClick()) {
        HandleDoubleClickEvent(info);
    } else {
        HandleSingleClickEvent(info);
        NotifyCaretChange();
    }
}

bool RichEditorPattern::HandleClickSelection(const OHOS::Ace::GestureEvent& info)
{
    CHECK_NULL_RETURN(!selectOverlay_->GetIsHandleMoving(), true);
    if (SelectOverlayIsOn()) {
        selectOverlay_->SwitchToOverlayMode();
        selectOverlay_->ToggleMenu();
    } else {
        CalculateHandleOffsetAndShowOverlay();
        selectOverlay_->ProcessOverlay({.animation = true, .requestCode = REQUEST_RECREATE});
    }
    return true;
}

bool RichEditorPattern::IsClickEventOnlyForMenuToggle(const OHOS::Ace::GestureEvent& info)
{
    CHECK_NULL_RETURN(info.GetSourceDevice() != SourceType::MOUSE, false);
    // In preview state or single handle showing, clicking handle has toggled the menu display
    bool hasHandledMenuToggleByClick =
        selectOverlay_->IsClickAtHandle(info) && (!isEditing_ || selectOverlay_->IsSingleHandleShow());
    CHECK_NULL_RETURN(!hasHandledMenuToggleByClick, true);
    if (showSelect_ && BetweenSelection(info.GetGlobalLocation())) {
        return HandleClickSelection(info);
    }
    return false;
}

void RichEditorPattern::HandleSingleClickEvent(OHOS::Ace::GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "handleSingleClick");
    hasClicked_ = true;
    lastClickTimeStamp_ = info.GetTimeStamp();
    CHECK_NULL_VOID(!IsClickEventOnlyForMenuToggle(info));
    CHECK_NULL_VOID(!HandleUrlSpanClickEvent(info));

    Offset textOffset = ConvertTouchOffsetToTextOffset(info.GetLocalLocation());
    IF_TRUE(!isMousePressed_, HandleClickAISpanEvent(PointF(textOffset.GetX(), textOffset.GetY())));

    if (dataDetectorAdapter_->hasClickedAISpan_ || dataDetectorAdapter_->pressedByLeftMouse_) {
        IF_TRUE(SelectOverlayIsOn(), selectOverlay_->HideMenu());
        return;
    }

    HandleUserClickEvent(info);
    CHECK_NULL_VOID(!info.IsPreventDefault());
    bool isMouseClick = info.GetSourceDevice() == SourceType::MOUSE;
    bool isMouseClickWithShift = shiftFlag_ && isMouseClick && !IsPreviewTextInputting();
    if (textSelector_.IsValid() && !isMouseSelect_ && !isMouseClickWithShift) {
        CloseSelectOverlay();
        ResetSelection();
    }
    moveCaretState_.Reset();
    caretUpdateType_ = CaretUpdateType::PRESSED;
    CHECK_NULL_VOID(overlayMod_);
    RectF lastCaretRect = GetCaretRect();
    int32_t lastCaretPosition = caretPosition_;
    bool isCaretTwinkling = caretTwinkling_;
    auto position = paragraphs_.GetIndex(textOffset);
    AdjustCursorPosition(position);
    if (auto focusHub = GetFocusHub(); focusHub) {
        IF_TRUE(!isMouseClick || (blockPress_ && !isMouseClickWithShift), SetCaretPosition(position));
        IF_TRUE(isMouseClickWithShift, HandleShiftSelect(position));
        if (focusHub->IsCurrentFocus()) {
            HandleOnEditChanged(true);
        }
        if (focusHub->RequestFocusImmediately()) {
            IF_TRUE(!shiftFlag_ || textSelector_.SelectNothing(), StartTwinkling());
            RequestKeyboard(false, true, true, info.GetSourceDevice());
        }
    }
    UseHostToUpdateTextFieldManager();
    CalcCaretInfoByClick(info.GetLocalLocation());
    CHECK_NULL_VOID(!isMouseClick);
    if (IsShowSingleHandleByClick(info, lastCaretPosition, lastCaretRect, isCaretTwinkling)) {
        CreateAndShowSingleHandle();
    }
}

PointF RichEditorPattern::GetTextOffset(const Offset &localLocation, const RectF &contentRect)
{
    PointF textOffset = {static_cast<float>(localLocation.GetX()) - GetTextRect().GetX(),
                         static_cast<float>(localLocation.GetY()) - GetTextRect().GetY()};
    return textOffset;
}

std::vector<RectF> RichEditorPattern::GetSelectedRects(int32_t start, int32_t end)
{
    return paragraphs_.GetRects(start, end);
}

Offset RichEditorPattern::ConvertTouchOffsetToTextOffset(const Offset& touchOffset)
{
    richTextRect_.SetTop(richTextRect_.GetY() - std::min(baselineOffset_, 0.0f));
    richTextRect_.SetHeight(richTextRect_.Height() - std::max(baselineOffset_, 0.0f));
    return touchOffset - Offset(richTextRect_.GetX(), richTextRect_.GetY());
}

bool RichEditorPattern::IsShowSingleHandleByClick(
    const OHOS::Ace::GestureEvent& info, int32_t lastCaretPosition, const RectF& lastCaretRect, bool isCaretTwinkling)
{
    auto isAccessibilityClick = IsAccessibilityClick();
    if (!isCaretTwinkling || (info.GetSourceDevice() == SourceType::MOUSE) || isAccessibilityClick) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "isCaretTwinkling=%{public}d,sourceType=%{public}d,"
            "isAccessibilityClick=%{public}d", isCaretTwinkling, info.GetSourceDevice(), isAccessibilityClick);
        return false;
    }
    auto offset = info.GetLocalLocation();
    Offset textOffset = ConvertTouchOffsetToTextOffset(offset);
    auto position = (GetTextContentLength() == 0) ? 0 : paragraphs_.GetIndex(textOffset);
    if (position != lastCaretPosition) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "clickCaretPosition=%{public}d but lastCaretPosition=%{public}d",
            position, lastCaretPosition);
        return false;
    }
    auto paragraphEndPos = GetParagraphEndPosition(lastCaretPosition);
    if (lastCaretPosition == paragraphEndPos || IsTouchAtLineEnd(lastCaretPosition, textOffset)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "repeat click lineEnd or paragraphEndPos=%{public}d", paragraphEndPos);
        return true;
    }
    return RepeatClickCaret(offset, lastCaretRect);
}

bool RichEditorPattern::RepeatClickCaret(const Offset& offset, const RectF& lastCaretRect)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "caretTwinkling=%{public}d offset=%{public}s lastCaretRect=%{public}s",
        caretTwinkling_, offset.ToString().c_str(), lastCaretRect.ToString().c_str());
    CHECK_NULL_RETURN(caretTwinkling_, false);
    auto lastCaretHeight = lastCaretRect.Height();
    auto handleHotZone = selectOverlay_->GetHandleHotZoneRadius();
    auto caretHotZoneRect =
        RectF(lastCaretRect.GetX() - handleHotZone, lastCaretRect.GetY(), handleHotZone * 2, lastCaretHeight);
    return caretHotZoneRect.IsInRegion(PointF(offset.GetX(), offset.GetY()));
}

void RichEditorPattern::CreateAndShowSingleHandle()
{
    if (IsPreviewTextInputting()) {
        return;
    }
    textResponseType_ = TextResponseType::LONG_PRESS;
    selectOverlay_->SetIsSingleHandle(true);
    textSelector_.Update(caretPosition_);
    CalculateHandleOffsetAndShowOverlay();
    UpdateSelectionType(GetSpansInfo(caretPosition_, caretPosition_, GetSpansMethod::ONSELECT));
    selectOverlay_->ProcessOverlay({ .animation = true });
}

void RichEditorPattern::MoveCaretAndStartFocus(const Offset& textOffset)
{
    auto position = paragraphs_.GetIndex(textOffset);
    AdjustCursorPosition(position);

    auto focusHub = GetFocusHub();
    if (focusHub) {
        SetCaretPosition(position);
        if (focusHub->RequestFocusImmediately()) {
            IF_TRUE(!shiftFlag_ || textSelector_.SelectNothing(), StartTwinkling());
            if (overlayMod_) {
                RequestKeyboard(false, true, true);
            }
            HandleOnEditChanged(true);
        }
    }
    UseHostToUpdateTextFieldManager();
}

void RichEditorPattern::HandleDoubleClickEvent(OHOS::Ace::GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "HandleDoubleClickEvent");
    caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    HandleDoubleClickOrLongPress(info);
    caretUpdateType_ = CaretUpdateType::NONE;
}

bool RichEditorPattern::HandleUserGestureEvent(
    GestureEvent& info, std::function<bool(RefPtr<SpanItem> item, GestureEvent& info)>&& gestureFunc)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "HandleUserGestureEvent");
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    if (!textContentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY())) ||
        spans_.empty()) {
        return false;
    }
    PointF textOffset = { info.GetLocalLocation().GetX() - GetTextRect().GetX(),
        info.GetLocalLocation().GetY() - GetTextRect().GetY() };
    int32_t start = 0;
    bool isParagraphHead = true;
    Offset paragraphOffset(0, 0);
    for (const auto& item : spans_) {
        if (!item) {
            continue;
        }
        std::vector<RectF> selectedRects = paragraphs_.GetRects(start, item->position);
        start = item->position;
        if (isParagraphHead && !selectedRects.empty()) {
            if (item->leadingMargin.has_value()) {
                auto addWidth = item->leadingMargin.value().size.Width();
                selectedRects[0].SetLeft(selectedRects[0].GetX() - addWidth.ConvertToPx());
                selectedRects[0].SetWidth(selectedRects[0].GetSize().Width() + addWidth.ConvertToPx());
            }
            paragraphOffset.SetX(selectedRects[0].GetOffset().GetX());
            paragraphOffset.SetY(selectedRects[0].GetOffset().GetY());
            isParagraphHead = false;
        }
        if (!isParagraphHead && item->content.back() == '\n') {
            isParagraphHead = true;
        }
        for (auto&& rect : selectedRects) {
            if (!rect.IsInRegion(textOffset)) {
                continue;
            }
            info = info.SetScreenLocation(
                Offset(textOffset.GetX() - paragraphOffset.GetX(), textOffset.GetY() - paragraphOffset.GetY()));
            return gestureFunc(item, info);
        }
    }
    return false;
}

bool RichEditorPattern::ClickAISpan(const PointF& textOffset, const AISpan& aiSpan)
{
    auto calculateHandleFunc = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CalculateHandleOffsetAndShowOverlay();
    };
    auto showSelectOverlayFunc = [weak = WeakClaim(this)](const RectF& firstHandle, const RectF& secondHandle) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetCaretPosition(pattern->textSelector_.destinationOffset);
        auto focusHub = pattern->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->RequestFocusImmediately();
        IF_TRUE(!pattern->isEditing_, pattern->CloseKeyboard(true));
        pattern->ShowSelectOverlay(firstHandle, secondHandle);
    };

    std::vector<RectF> aiRects = paragraphs_.GetRects(aiSpan.start, aiSpan.end);
    for (auto&& rect : aiRects) {
        if (rect.IsInRegion(textOffset)) {
            dataDetectorAdapter_->clickedAISpan_ = aiSpan;
            if (leftMousePress_) {
                dataDetectorAdapter_->pressedByLeftMouse_ = true;
                return true;
            }
            dataDetectorAdapter_->hasClickedAISpan_ = true;
            ShowAIEntityMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
            return true;
        }
    }
    return false;
}

std::pair<int32_t, int32_t> RichEditorPattern::GetStartAndEnd(int32_t start, const RefPtr<SpanItem>& item)
{
    return isSpanStringMode_
        ? TextPattern::GetStartAndEnd(start, item)
        : std::make_pair(item->rangeStart, item->position);
}

bool RichEditorPattern::HandleUrlSpanClickEvent(const GestureEvent& info)
{
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));

    CheckClickedOnSpanOrText(textContentRect, info.GetLocalLocation());
    auto clickedSpanPosition = GetClickedSpanPosition();
    if (LessNotEqual(clickedSpanPosition, 0)) {
        return false;
    }
    auto iter = spans_.begin();
    std::advance(iter, clickedSpanPosition);
    RefPtr<SpanItem> span;
    if (iter == spans_.end()) {
        span = spans_.back();
    } else {
        span = *iter;
    }
    if (span && span->urlOnRelease) {
        span->urlOnRelease();
        return true;
    }
    return false;
}

bool RichEditorPattern::HandleUserClickEvent(GestureEvent& info)
{
    auto clickFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool {
        if (item && item->onClick) {
            item->onClick(info);
            return true;
        }
        return false;
    };
    return HandleUserGestureEvent(info, std::move(clickFunc));
}

void RichEditorPattern::CalcCaretInfoByClick(const Offset& touchOffset)
{
    auto textRect = GetTextRect();
    textRect.SetTop(textRect.GetY() - std::min(baselineOffset_, 0.0f));
    textRect.SetHeight(textRect.Height() - std::max(baselineOffset_, 0.0f));
    Offset textOffset = { touchOffset.GetX() - textRect.GetX(), touchOffset.GetY() - textRect.GetY() };
    auto [lastClickOffset, caretHeight] = CalcAndRecordLastClickCaretInfo(textOffset);
    CHECK_NULL_VOID(overlayMod_);
    DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(lastClickOffset, caretHeight);
    MoveCaretToContentRect();
}

std::pair<OffsetF, float> RichEditorPattern::CalcAndRecordLastClickCaretInfo(const Offset& textOffset)
{
    // get the caret position
    auto positionWithAffinity = paragraphs_.GetGlyphPositionAtCoordinate(textOffset);
    auto position = static_cast<int32_t>(positionWithAffinity.position_);
    // get the caret offset when click
    float caretHeight = 0.0f;
    auto lastClickOffset = paragraphs_.ComputeCursorInfoByClick(position, caretHeight,
        OffsetF(static_cast<float>(textOffset.GetX()), static_cast<float>(textOffset.GetY())));

    lastClickOffset += richTextRect_.GetOffset();
    if (isShowPlaceholder_) {
        auto [caretOffset, preferredHeight] = CalculateEmptyValueCaretRect();
        lastClickOffset = caretOffset;
    }
    SetLastClickOffset(lastClickOffset);
    caretAffinityPolicy_ = (positionWithAffinity.affinity_ == TextAffinity::UPSTREAM)
                                ? CaretAffinityPolicy::UPSTREAM_FIRST
                                : CaretAffinityPolicy::DOWNSTREAM_FIRST;
    return std::make_pair(lastClickOffset, caretHeight);
}

void RichEditorPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEventInitialized_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "click callback, sourceType=%{public}d", info.GetSourceDevice());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
        pattern->HandleClickEvent(info);
    };
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickAfterEvent(clickListener);
    clickEventInitialized_ = true;
}

void RichEditorPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    CHECK_NULL_VOID(!focusEventInitialized_);
    auto focusTask = [weak = WeakClaim(this)](FocusReason reason) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "rich editor in focus");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleFocusEvent();
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "rich editor in blur");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
    focusEventInitialized_ = true;
    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(std::move(keyTask));
}

BlurReason RichEditorPattern::GetBlurReason()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, BlurReason::FOCUS_SWITCH);
    auto curFocusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(curFocusHub, BlurReason::FOCUS_SWITCH);
    return curFocusHub->GetBlurReason();
}

void RichEditorPattern::HandleBlurEvent()
{
    auto reason = GetBlurReason();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleBlurEvent/%{public}d, blur reason=%{public}d", frameId_, reason);
    auto host = GetHost();
    ClearOnFocusTextField(RawPtr(host));
    host.Reset();
    IF_PRESENT(multipleClickRecognizer_, Stop());
    CHECK_NULL_VOID(showSelect_ || !IsSelected());
    isLongPress_ = false;
    ResetTouchSelectState();
    shiftFlag_ = false;
    moveCaretState_.Reset();
    floatingCaretState_.Reset();
    StopTwinkling();
    // The pattern handles blurevent, Need to close the softkeyboard first.
    if ((customKeyboardBuilder_ && isCustomKeyboardAttached_) || reason == BlurReason::FRAME_DESTROY) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "RichEditor Blur, Close Keyboard.");
        CloseSelectOverlay();
        ResetSelection();
        CloseKeyboard(false);
    }
    if (magnifierController_) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
    if (IsSelected() && reason == BlurReason::FOCUS_SWITCH) {
        CloseSelectOverlay();
        ResetSelection();
    } else if (IsSelected()) {
        selectOverlay_->HideMenu(true);
    } else {
        CloseSelectOverlay();
    }
    if (reason != BlurReason::WINDOW_BLUR) {
        lastSelectionRange_.reset();
    }
    HandleOnEditChanged(false);
}

void RichEditorPattern::HandleFocusEvent()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleFocusEvent/%{public}d", frameId_);
    blockKbInFloatingWindow_= false;
    UseHostToUpdateTextFieldManager();
    if (previewLongPress_ || isOnlyRequestFocus_) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleFocusEvent, previewLongPress=%{public}d,"
            "OnlyRequestFocus=%{public}d", previewLongPress_, isOnlyRequestFocus_);
        isOnlyRequestFocus_ = false;
        return;
    }
    SetIsEnableSubWindowMenu();
    if (textSelector_.SelectNothing()) {
        StartTwinkling();
    }
    auto host = GetHost();
    if (host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }

    bool clickAIMenu = dataDetectorAdapter_->hasClickedMenuOption_;
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "longPress=%{public}d, clickAIMenu=%{public}d", isLongPress_, clickAIMenu);
    bool bindKeyboard = !isLongPress_ && !clickAIMenu;
    CHECK_NULL_VOID(bindKeyboard);

    auto windowMode = GetWindowMode();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "requestKeyboard=%{public}d, windowMode=%{public}d, rightButton=%{public}d",
        needToRequestKeyboardOnFocus_, windowMode, usingMouseRightButton_);

    bool needShowSoftKeyboard = needToRequestKeyboardOnFocus_;
    needShowSoftKeyboard &= !usingMouseRightButton_; // do not show kb when mouseRightClick

    if (windowMode == WindowMode::WINDOW_MODE_FLOATING) {
        blockKbInFloatingWindow_ = needShowSoftKeyboard;
        needShowSoftKeyboard = false;
    }

    RequestKeyboard(false, true, needShowSoftKeyboard);
    HandleOnEditChanged(true);
}

void RichEditorPattern::OnFocusNodeChange(FocusReason focusReason)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "OnFocusNodeChange/%{public}d, reason=%{public}d, blockKbInFloating=%{public}d",
        frameId_, focusReason, blockKbInFloatingWindow_);
    CHECK_NULL_VOID(blockKbInFloatingWindow_);
    blockKbInFloatingWindow_= false;
    CHECK_NULL_VOID(GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING);
    CHECK_NULL_VOID(focusReason != FocusReason::WINDOW_FOCUS);
    CHECK_NULL_VOID(HasFocus() && isEditing_);
    bool clickAIMenu = dataDetectorAdapter_->hasClickedMenuOption_;
    bool bindKeyboard = !isLongPress_ && !clickAIMenu;
    CHECK_NULL_VOID(bindKeyboard);
    CHECK_NULL_VOID(needToRequestKeyboardOnFocus_ && !usingMouseRightButton_);

    RequestKeyboard(false, true, true);
}

WindowMode RichEditorPattern::GetWindowMode()
{
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, WindowMode::WINDOW_MODE_UNDEFINED);
    auto windowManager = pipelineContext->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, WindowMode::WINDOW_MODE_UNDEFINED);
    return windowManager->GetWindowMode();
}

bool RichEditorPattern::GetIsMidScene()
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, false);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, false);
    bool isMidScene = false;
    int32_t ret = windowManager->GetIsMidScene(isMidScene);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "GetIsMidScene ret=%{public}d", ret);
    return isMidScene;
}

void RichEditorPattern::UseHostToUpdateTextFieldManager()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto globalOffset = host->GetPaintRectOffsetNG(false, true) - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
}

void RichEditorPattern::OnVisibleChange(bool isVisible)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "isVisible=%{public}d", isVisible);
    TextPattern::OnVisibleChange(isVisible);
    StopTwinkling();
    CloseSelectOverlay();
    ResetSelection();
    if (!isVisible && HasFocus()) {
        CloseKeyboard(false);
    }
}

bool RichEditorPattern::CloseKeyboard(bool forceClose)
{
    if (customKeyboardBuilder_ && isCustomKeyboardAttached_) {
        return CloseCustomKeyboard();
    }
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "Request close soft keyboard.");
#if defined(ENABLE_STANDARD_INPUT)
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (!imeAttached_ && !forceClose) {
        return false;
    }
#endif
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    CHECK_NULL_RETURN(inputMethod, false);
    inputMethod->HideTextInput();
    inputMethod->Close();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    imeAttached_ = false;
#endif
#else
    if (HasConnection()) {
        connection_->Close(GetInstanceId());
        connection_ = nullptr;
    }
#endif
    return true;
}

void RichEditorPattern::HandleDraggableFlag(bool isTouchSelectArea)
{
    if (copyOption_ != CopyOptions::None && isTouchSelectArea) {
        bool isContentDraggalbe = JudgeContentDraggable();
        if (isContentDraggalbe) {
            dragBoxes_ = GetTextBoxes();
        }
        SetIsTextDraggable(isContentDraggalbe);
    } else {
        SetIsTextDraggable(false);
    }
}

void RichEditorPattern::SetIsTextDraggable(bool isTextDraggable)
{
    auto gestureHub = GetGestureEventHub();
    IF_PRESENT(gestureHub, SetIsTextDraggable(isTextDraggable));
}

bool RichEditorPattern::JudgeContentDraggable()
{
    if (!IsSelected() || copyOption_ == CopyOptions::None) {
        return false ;
    }
    auto selectInfo = GetSpansInfo(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), GetSpansMethod::ONSELECT);
    auto selResult = selectInfo.GetSelection().resultObjects;
    auto iter = std::find_if(selResult.begin(), selResult.end(), [](ResultObject& obj) { return obj.isDraggable; });
    return iter != selResult.end();
}

std::pair<OffsetF, float> RichEditorPattern::CalculateCaretOffsetAndHeight()
{
    OffsetF caretOffset;
    float caretHeight = 0.0f;
    auto caretPosition = caretPosition_;
    float caretHeightUp = 0.0f;
    auto caretBoundaryRect = GetCaretBoundaryRect();
    OffsetF caretOffsetUp = CalcCursorOffsetByPosition(caretPosition, caretHeightUp, false, false);
    if (isShowPlaceholder_) {
        auto textAlign = GetTextAlignByDirection();
        IF_TRUE(textAlign == TextAlign::END, caretOffsetUp.SetX(caretBoundaryRect.Right()));
        return { caretOffsetUp, caretHeightUp };
    }
    if (GetTextContentLength() <= 0) {
        constexpr float DEFAULT_CARET_HEIGHT = 18.5f;
        auto [caretOffset, preferredHeight] = CalculateEmptyValueCaretRect();
        caretHeight = typingTextStyle_.has_value() ? preferredHeight
            : static_cast<float>(Dimension(DEFAULT_CARET_HEIGHT, DimensionUnit::VP).ConvertToPx());
        return { caretOffset, caretHeight };
    }
    float caretHeightDown = 0.0f;
    OffsetF caretOffsetDown = CalcCursorOffsetByPosition(caretPosition, caretHeightDown, true, false);
    bool isCaretPosInLineEnd = !NearEqual(caretOffsetDown.GetX(), caretOffsetUp.GetX(), 0.5f);
    bool isShowCaretDown = isCaretPosInLineEnd;
    if ((caretAffinityPolicy_ != CaretAffinityPolicy::DEFAULT) && isCaretPosInLineEnd) {
        // show caret by click
        isShowCaretDown = (caretAffinityPolicy_ == CaretAffinityPolicy::DOWNSTREAM_FIRST);
    }
    caretOffset = isShowCaretDown ? caretOffsetDown : caretOffsetUp;
    caretHeight = isShowCaretDown ? caretHeightDown : caretHeightUp;
    // Handle caret offset at the right boundary of the content rect
    if (GreatOrEqual(caretOffset.GetX(), caretBoundaryRect.Right())) {
        auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
        CHECK_NULL_RETURN(overlayModifier, std::make_pair(caretOffset, caretHeight));
        auto caretWidth = overlayModifier->GetCaretWidth();
        caretOffset.SetX(caretOffset.GetX() - caretWidth);
    }
    return std::make_pair(caretOffset, caretHeight);
}

std::pair<OffsetF, float> RichEditorPattern::CalculateEmptyValueCaretRect()
{
    OffsetF offset;
    auto textAlign = GetTextAlignByDirection();
    switch (textAlign) {
        case TextAlign::START:
            offset.SetX(contentRect_.GetX());
            break;
        case TextAlign::CENTER:
            offset.SetX(contentRect_.GetX() + contentRect_.Width() / 2.0f);
            break;
        case TextAlign::END: {
            auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
            auto caretWidth = overlayModifier ? overlayModifier->GetCaretWidth() : 0.0f;
            offset.SetX(contentRect_.Right() - caretWidth);
            break;
        }
        default:
            break;
    }
    auto offsetY = richTextRect_.GetY();
    float caretHeight = 0.0f;
    if (!presetParagraph_) {
        PreferredParagraph();
    }
    if (presetParagraph_) {
        CaretMetricsF caretCaretMetric;
        presetParagraph_->CalcCaretMetricsByPosition(1, caretCaretMetric, TextAffinity::UPSTREAM, false);
        offsetY += caretCaretMetric.offset.GetY();
        caretHeight = caretCaretMetric.height;
    }
    offset.SetY(offsetY);
    return std::make_pair(offset, caretHeight);
}

void RichEditorPattern::UpdateModifierCaretOffsetAndHeight()
{
    CHECK_NULL_VOID(overlayMod_);
    auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_VOID(overlayModifier);
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    overlayModifier->SetCaretOffsetAndHeight(caretOffset, caretHeight);
}

void RichEditorPattern::NotifyCaretChange()
{
    CHECK_NULL_VOID(!IsSelected());
    TriggerAvoidOnCaretChange();
}

TextAlign RichEditorPattern::GetTextAlignByDirection()
{
    auto layoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, TextAlign::START);
    auto textAlign = layoutProperty->GetTextAlignValue(TextAlign::START);
    auto direction = layoutProperty->GetNonAutoLayoutDirection();
    if (direction == TextDirection::RTL) {
        if (textAlign == TextAlign::START) {
            textAlign = TextAlign::END;
        } else {
            textAlign = TextAlign::START;
        }
    }
    return textAlign;
}

void RichEditorPattern::HandleLongPress(GestureEvent& info)
{
    CHECK_NULL_VOID(!selectOverlay_->GetIsHandleMoving());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!focusHub->IsFocusable()) {
        return;
    }
    if (info.GetFingerList().size() > 1) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "More than one finger detected, ignoring this long press event");
        return;
    }
    if (sourceType_ == SourceType::MOUSE && hasUrlSpan_) {
        HandleUrlSpanShowShadow(info.GetLocalLocation(), info.GetGlobalLocation(), GetUrlPressColor());
    }

    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "HandleLongPress");
    moveCaretState_.Reset();
    caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    selectionMenuOffsetClick_ = OffsetF(
        static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
    HandleDoubleClickOrLongPress(info);
    caretUpdateType_ = CaretUpdateType::NONE;
}

bool RichEditorPattern::HandleUrlSpanShowShadow(const Offset& localLocation, const Offset& globalOffset, const Color& color)
{
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));

    auto localLocationOffset = localLocation;
    if (selectOverlay_->HasRenderTransform()) {
        localLocationOffset = ConvertGlobalToLocalOffset(globalOffset);
    }

    PointF textOffset = {static_cast<float>(localLocationOffset.GetX()) - GetTextRect().GetX(),
                         static_cast<float>(localLocationOffset.GetY()) - GetTextRect().GetY()};
    return ShowShadow(textOffset, color);
}

void RichEditorPattern::HandleDoubleClickOrLongPress(GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "caretUpdateType=%{public}d", caretUpdateType_);
    if (IsPreviewTextInputting()) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "do not handle DoubleClickOrLongPress in previewTextInputting");
        return;
    }
    if (IsDragging()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "do not handle DoubleClickOrLongPress during drag");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    textResponseType_ = TextResponseType::LONG_PRESS;
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        HandleUserLongPressEvent(info);
    } else if (caretUpdateType_ == CaretUpdateType::DOUBLE_CLICK) {
        HandleUserDoubleClickEvent(info);
    }
    bool isDoubleClick = caretUpdateType_== CaretUpdateType::DOUBLE_CLICK;
    if (isDoubleClick && info.GetSourceTool() == SourceTool::FINGER && IsSelected()) {
        showSelect_ = true;
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    }
    bool isLongPressSelectArea = BetweenSelection(info.GetGlobalLocation()) && !isDoubleClick;
    HandleDraggableFlag(isLongPressSelectArea);
    bool isLongPressByMouse = isMousePressed_ && caretUpdateType_== CaretUpdateType::LONG_PRESSED;
    if (isLongPressSelectArea && !isLongPressByMouse) {
        StartVibratorByLongPress();
    }
    bool isMouseClickWithShift = shiftFlag_ && info.GetSourceDevice() == SourceType::MOUSE;
    bool isInterceptEvent = isLongPressSelectArea || isLongPressByMouse || isMouseClickWithShift;
    if (isInterceptEvent) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "intercept longPressReason:[%{public}d, %{public}d] shiftSelect:%{public}d",
            isLongPressSelectArea, isLongPressByMouse, isMouseClickWithShift);
        return;
    }
    HandleDoubleClickOrLongPress(info, host);
    if (IsSelected()) {
        TriggerAvoidOnCaretChangeNextFrame();
    } else {
        ForceTriggerAvoidOnCaretChange(true);
    }
}

Offset RichEditorPattern::ConvertGlobalToLocalOffset(const Offset& globalOffset)
{
    auto localPoint = OffsetF(globalOffset.GetX(), globalOffset.GetY());
    selectOverlay_->RevertLocalPointWithTransform(localPoint);
    return Offset(localPoint.GetX(), localPoint.GetY());
}

void RichEditorPattern::HandleSelect(GestureEvent& info, int32_t selectStart, int32_t selectEnd)
{
    initSelector_ = { selectStart, selectEnd };
    if (IsSelected()) {
        showSelect_ = true;
    }
    FireOnSelect(selectStart, selectEnd);
    SetCaretPositionWithAffinity({ selectEnd, TextAffinity::UPSTREAM });
    MoveCaretToContentRect();
    CalculateHandleOffsetAndShowOverlay();
    if (IsShowSelectMenuUsingMouse()) {
        CloseSelectOverlay();
    }
    selectionMenuOffset_ = info.GetGlobalLocation();
}

void RichEditorPattern::HandleDoubleClickOrLongPress(GestureEvent& info, RefPtr<FrameNode> host)
{
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    isLongPress_ = true;
    auto localOffset = info.GetLocalLocation();
    if (selectOverlay_->HasRenderTransform()) {
        localOffset = ConvertGlobalToLocalOffset(info.GetGlobalLocation());
    }
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { localOffset.GetX() - textPaintOffset.GetX(), localOffset.GetY() - textPaintOffset.GetY() };
    if (caretUpdateType_ == CaretUpdateType::LONG_PRESSED) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "LONG_PRESSED and isEditing=%{public}d", isEditing_);
        if (textSelector_.IsValid()) {
            CloseSelectOverlay();
            ResetSelection();
        }
        StartVibratorByLongPress();
        editingLongPress_ = isEditing_;
        previewLongPress_ = !isEditing_;
    }
    focusHub->RequestFocusImmediately();
    InitSelection(textOffset);
    auto selectEnd = textSelector_.GetTextEnd();
    auto selectStart = textSelector_.GetTextStart();
    HandleSelect(info, selectStart, selectEnd);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    if (overlayMod_ && caretUpdateType_ == CaretUpdateType::DOUBLE_CLICK) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "double click. shall enter edit state.set 1");
        HandleOnEditChanged(true);
        RequestKeyboard(false, true, true);
    }
    bool isDoubleClickByMouse =
        info.GetSourceDevice() == SourceType::MOUSE && caretUpdateType_ == CaretUpdateType::DOUBLE_CLICK;
    bool isShowSelectOverlay = !isDoubleClickByMouse && caretUpdateType_ != CaretUpdateType::LONG_PRESSED;
    if (isShowSelectOverlay) {
        selectOverlay_->ProcessOverlay({ .menuIsShow = !selectOverlay_->GetIsHandleMoving(), .animation = true });
        StopTwinkling();
    } else if (selectStart == selectEnd && isDoubleClickByMouse) {
        StartTwinkling();
    } else {
        StopTwinkling();
    }
}

void RichEditorPattern::StartVibratorByLongPress()
{
    CHECK_NULL_VOID(isEnableHapticFeedback_);
    VibratorUtils::StartVibraFeedback("longPress.light");
}

bool RichEditorPattern::HandleUserLongPressEvent(GestureEvent& info)
{
    auto longPressFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool {
        if (item && item->onLongPress) {
            item->onLongPress(info);
            return true;
        }
        return false;
    };
    return HandleUserGestureEvent(info, std::move(longPressFunc));
}

bool RichEditorPattern::HandleUserDoubleClickEvent(GestureEvent& info)
{
    auto doubleClickFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool {
        if (item && item->onDoubleClick) {
            item->onDoubleClick(info);
            return true;
        }
        return false;
    };
    return HandleUserGestureEvent(info, std::move(doubleClickFunc));
}

void RichEditorPattern::HandleMenuCallbackOnSelectAll(bool isShowMenu)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "HandleMenuCallbackOnSelectAll");
    auto textSize = GetTextContentLength();
    textSelector_.Update(0, textSize);
    CalculateHandleOffsetAndShowOverlay();
    if (selectOverlay_->IsUsingMouse()) {
        CloseSelectOverlay();
    }
    IF_TRUE(IsSelected(), StopTwinkling());
    auto selectOverlayInfo = selectOverlay_->GetSelectOverlayInfo();
    if (selectOverlayInfo && selectOverlay_->IsUsingMouse()) {
        textResponseType_ = static_cast<TextResponseType>(selectOverlayInfo->menuInfo.responseType.value_or(0));
    } else {
        textResponseType_ = TextResponseType::LONG_PRESS;
    }
    selectMenuInfo_.showCopyAll = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    showSelect_ = true;
    if (!selectOverlay_->IsUsingMouse()) {
        selectOverlay_->ProcessOverlay({ .menuIsShow = isShowMenu, .animation = true });
    }
    SetCaretPosition(textSize);
    MoveCaretToContentRect();
    TriggerAvoidOnCaretChangeNextFrame();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!longPressEvent_);
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "long press callback, sourceType=%{public}d", info.GetSourceDevice());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gestureHub->SetLongPressEvent(longPressEvent_);

    auto onTextSelectorChange = [weak = WeakClaim(this), &selector = textSelector_]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!selector.SelectNothing()) {
            pattern->StopTwinkling();
        }
        IF_PRESENT(pattern->oneStepDragController_,
            SetEnableEventResponse(selector, pattern->imageNodes, pattern->builderNodes));
        pattern->FireOnSelectionChange(selector);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_SELECTION_UPDATE);
    };
    textSelector_.SetOnAccessibility(std::move(onTextSelectorChange));
}

void RichEditorPattern::UpdateSelector(int32_t start, int32_t end)
{
    AdjustSelector(start, end);
    textSelector_.Update(start, end);
}

void RichEditorPattern::AdjustSelector(int32_t& start, int32_t& end, SelectorAdjustPolicy policy)
{
    AdjustSelector(start, HandleType::FIRST, policy);
    AdjustSelector(end, HandleType::SECOND, policy);
}

void RichEditorPattern::AdjustSelector(int32_t& index, HandleType handleType,  SelectorAdjustPolicy policy)
{
    bool isAdjust = AdjustSelectorForSymbol(index, handleType, policy);
    CHECK_NULL_VOID(!isAdjust);
    AdjustSelectorForEmoji(index, handleType, policy);
}

bool RichEditorPattern::AdjustSelectorForSymbol(int32_t& index, HandleType handleType, SelectorAdjustPolicy policy)
{
    auto it = GetSpanIter(index);
    CHECK_NULL_RETURN((it != spans_.end()), false);
    auto spanItem = *it;
    CHECK_NULL_RETURN(spanItem, false);

    auto spanStart = spanItem->rangeStart;
    auto spanEnd = spanItem->position;
    if (spanItem->unicode != 0 && spanItem->Contains(index)) {
        auto it = SELECTOR_ADJUST_DIR_MAP.find({ handleType, policy });
        index = (it->second == MoveDirection::BACKWARD) ? spanStart : spanEnd;
        return true;
    }
    return false;
}

EmojiRelation RichEditorPattern::GetEmojiRelation(int index)
{
    auto it = GetSpanIter(index);
    CHECK_NULL_RETURN((it != spans_.end()), EmojiRelation::NO_EMOJI);
    auto spanItem = *it;
    CHECK_NULL_RETURN(spanItem, EmojiRelation::NO_EMOJI);
    int32_t emojiStartIndex;
    int32_t emojiEndIndex;
    return TextEmojiProcessor::GetIndexRelationToEmoji(index - spanItem->rangeStart, spanItem->content,
        emojiStartIndex, emojiEndIndex);
}

bool RichEditorPattern::AdjustSelectorForEmoji(int& index, HandleType handleType, SelectorAdjustPolicy policy)
{
    auto it = GetSpanIter(index);
    CHECK_NULL_RETURN((it != spans_.end()), false);
    auto spanItem = *it;
    CHECK_NULL_RETURN(spanItem, false);

    int32_t emojiStartIndex;
    int32_t emojiEndIndex;
    int32_t spanStart = spanItem->rangeStart;
    EmojiRelation relation = TextEmojiProcessor::GetIndexRelationToEmoji(index - spanStart, spanItem->content,
        emojiStartIndex, emojiEndIndex);
    if (relation != EmojiRelation::IN_EMOJI && relation != EmojiRelation::MIDDLE_EMOJI) {
        // no need adjusting when index is not warpped in emojis
        return false;
    }
    int32_t start = 0;
    int32_t end = 0;
    bool isBoundaryGet = paragraphs_.GetWordBoundary(index, start, end); // boundary from engine
    if (isBoundaryGet) {
        if (handleType == HandleType::FIRST) {
            index = start;
        } else {
            if (index > start) {
                // index to emoji, move index to end of emoji, double check "in emoji state"
                index = end;
            }
        }
    } else {
        if (relation == EmojiRelation::IN_EMOJI) {
            int32_t indexInSpan = (handleType == HandleType::FIRST) ? emojiStartIndex : emojiEndIndex;
            index = spanItem->rangeStart + indexInSpan;
        }
    }
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT,
        "index=%{public}d, handleType=%{public}d, emojiRange=[%{public}d,%{public}d] isBoundaryGet=%{public}d "\
        "boundary=[%{public}d, %{public}d]",
        index, handleType, emojiStartIndex, emojiEndIndex, isBoundaryGet, start, end);
    return true;
}

std::list<RefPtr<SpanItem>>::iterator RichEditorPattern::GetSpanIter(int32_t index)
{
    return std::find_if(spans_.begin(), spans_.end(), [index](const RefPtr<SpanItem>& spanItem) {
        return spanItem->rangeStart <= index && index < spanItem->position;
    });
}

SpanItemType RichEditorPattern::GetSpanType(int32_t index)
{
    auto it = GetSpanIter(index);
    CHECK_NULL_RETURN((it != spans_.end()), SpanItemType::NORMAL);
    auto& spanItem = *it;
    CHECK_NULL_RETURN(spanItem, SpanItemType::NORMAL);
    return spanItem->spanItemType;
}

PositionWithAffinity RichEditorPattern::GetGlyphPositionAtCoordinate(int32_t x, int32_t y)
{
    Offset offset(x, y);
    return paragraphs_.GetGlyphPositionAtCoordinate(ConvertTouchOffsetToTextOffset(offset));
}

void RichEditorPattern::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    gestureHub->SetThumbnailCallback(GetThumbnailCallback());
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragMove = [weakPtr = WeakClaim(this)](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->showSelect_ = false;
        pattern->OnDragMove(event);
    };
    eventHub->SetOnDragMove(std::move(onDragMove));
    OnDragStartAndEnd();
    onDragDropAndLeave();
}

void RichEditorPattern::OnDragStartAndEnd()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart = [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                           const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo itemInfo;
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, itemInfo);
        return pattern->HandleDragStart(event, extraParams);
    };
    eventHub->SetDefaultOnDragStart(std::move(onDragStart));
    auto onDragEnd = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                         const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(scopeId);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isDragSponsor_ = false;
        pattern->dragRange_ = { 0, 0 };
        pattern->showSelect_ = true;
        pattern->StopAutoScroll();
        pattern->ClearRedoOperationRecords();
        pattern->OnDragEnd(event);
    };
    eventHub->SetOnDragEnd(std::move(onDragEnd));
}

NG::DragDropInfo RichEditorPattern::HandleDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams)
{
    if (!isDragSponsor_) {
        isDragSponsor_ = true;
        dragRange_ = { textSelector_.GetTextStart(), textSelector_.GetTextEnd() };
    }
    sourceTool_ = event ? event->GetSourceTool() : SourceTool::UNKNOWN;
    timestamp_ = std::chrono::system_clock::now().time_since_epoch().count();
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, {});
    eventHub->SetTimestamp(timestamp_);
    showSelect_ = false;
    auto dropInfo = OnDragStart(event, extraParams);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleDragStart dragStatus=%{public}d", status_);
    return dropInfo;
}

void RichEditorPattern::onDragDropAndLeave()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragDrop = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {
        ContainerScope scope(scopeId);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<EventHub>();
        pattern->sourceTool_ = event ? event->GetSourceTool() : SourceTool::UNKNOWN;
        CHECK_NULL_VOID(eventHub && eventHub->IsEnabled());
        bool isCopy = false;
        if (pattern->status_ == Status::DRAGGING) {
            CHECK_NULL_VOID(event);
            auto gesturePressedCodes = event->GetPressedKeyCodes();
            if ((gesturePressedCodes.size() == 1) && ((gesturePressedCodes[0] == KeyCode::KEY_CTRL_LEFT) ||
                (gesturePressedCodes[0] == KeyCode::KEY_CTRL_RIGHT))) {
                isCopy = true;
            }
        }
        pattern->status_ = Status::ON_DROP;
        pattern->HandleOnDragDrop(event, isCopy);
        pattern->status_ = Status::NONE;
    };
    eventHub->SetOnDrop(std::move(onDragDrop));
    auto onDragDragLeave = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                               const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& value) {
        ContainerScope scope(scopeId);
        auto pattern = weakPtr.Upgrade();
        IF_PRESENT(pattern, StopAutoScroll());
    };
    eventHub->SetOnDragLeave(onDragDragLeave);
}

void RichEditorPattern::ClearDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    SetIsTextDraggable(false);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(nullptr);
    eventHub->SetOnDragEnter(nullptr);
    eventHub->SetOnDragMove(nullptr);
    eventHub->SetOnDragLeave(nullptr);
    eventHub->SetOnDragEnd(nullptr);
    eventHub->SetOnDrop(nullptr);
}

void RichEditorPattern::OnDragMove(const RefPtr<OHOS::Ace::DragEvent>& event)
{
    auto theme = GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(theme);
    auto touchX = event->GetX();
    auto touchY = event->GetY();
    auto textRect = GetTextRect();
    textRect.SetTop(textRect.GetY() - std::min(baselineOffset_, 0.0f));
    Offset textOffset = { touchX - textRect.GetX() - GetParentGlobalOffset().GetX(),
        touchY - textRect.GetY() - GetParentGlobalOffset().GetY() - theme->GetInsertCursorOffset().ConvertToPx() };
    auto position = isShowPlaceholder_? 0 : paragraphs_.GetIndex(textOffset);
    ResetSelection();
    CloseSelectOverlay();
    SetCaretPosition(position);
    CalcAndRecordLastClickCaretInfo(textOffset);
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    CHECK_NULL_VOID(overlayMod_);
    auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    overlayModifier->SetCaretOffsetAndHeight(caretOffset, caretHeight);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (host->GetDragPreviewOption().enableEdgeAutoScroll) {
        AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::DRAG, .showScrollbar = true };
        auto localOffset = OffsetF(touchX, touchY) - parentGlobalOffset_;
        AutoScrollByEdgeDetection(param, localOffset, EdgeDetectionStrategy::IN_BOUNDARY);
    } else if (isAutoScrollRunning_) {
        StopAutoScroll();
    }
}

void RichEditorPattern::OnDragEnd(const RefPtr<Ace::DragEvent>& event)
{
    ResetDragRecordSize(-1);
    if (status_ == Status::DRAGGING) {
        status_ = Status::NONE;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "OnDragEnd dragStatus=%{public}d", status_);
    ResetDragSpanItems();
    CHECK_NULL_VOID(!recoverDragResultObjects_.empty());
    UpdateSpanItemDragStatus(recoverDragResultObjects_, false);
    recoverDragResultObjects_.clear();
    auto focusHub = GetFocusHub();
    if (event && focusHub && event->GetResult() != DragRet::DRAG_SUCCESS && focusHub->IsFocusable()) {
        afterDragSelect_ = true;
        HandleSelectionChange(recoverStart_, recoverEnd_);
        showSelect_ = true;
        CalculateHandleOffsetAndShowOverlay();
        ResetSelection();
    }
    auto host = GetHost();
    IF_PRESENT(host, MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF));
}

RefPtr<SpanString> RichEditorPattern::ToStyledString(int32_t start, int32_t end)
{
    auto length = GetTextContentLength();
    int32_t realStart = (start == -1) ? 0 : std::clamp(start, 0, length);
    int32_t realEnd = (end == -1) ? length : std::clamp(end, 0, length);
    if (realStart > realEnd) {
        std::swap(realStart, realEnd);
    }
    RefPtr<SpanString> spanString = MakeRefPtr<SpanString>(u"");
    if (aiWriteAdapter_->GetAIWrite()) {
        SetSubSpansWithAIWrite(spanString, realStart, realEnd);
    } else {
        SetSubSpans(spanString, realStart, realEnd);
    }
    SetSubMap(spanString);
    return spanString;
}

SelectionInfo RichEditorPattern::FromStyledString(const RefPtr<SpanString>& spanString)
{
    std::list<ResultObject> resultObjects;
    int32_t start = 0;
    int32_t end = 0;
    if (spanString && !spanString->GetSpanItems().empty()) {
        auto spans = spanString->GetSpanItems();
        int32_t index = 0;
        std::for_each(spans.begin(), spans.end(),
            [&index, &resultObjects, weak = WeakClaim(this)](RefPtr<SpanItem>& item) {
                CHECK_NULL_VOID(item);
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto obj = item->GetSpanResultObject(item->interval.first, item->interval.second);
                if (AceType::InstanceOf<ImageSpanItem>(item)) {
                    obj.imageStyle = pattern->GetImageStyleBySpanItem(item);
                } else if (!AceType::InstanceOf<CustomSpanItem>(item)) {
                    obj.textStyle = pattern->GetTextStyleBySpanItem(item);
                }
                obj.spanPosition.spanIndex = index;
                ++index;
                if (obj.isInit) {
                    resultObjects.emplace_back(obj);
                }
        });
        if (spans.back()) {
            end = spans.back()->interval.second;
        }
        if (spans.front()) {
            start = spans.front()->interval.first;
        }
    }
    SelectionInfo selection;
    selection.SetSelectionEnd(end);
    selection.SetSelectionStart(start);
    selection.SetResultObjectList(resultObjects);
    return selection;
}

TextStyleResult RichEditorPattern::GetTextStyleBySpanItem(const RefPtr<SpanItem>& spanItem)
{
    TextStyleResult textStyle;
    CHECK_NULL_RETURN(spanItem, textStyle);
    auto theme = GetTheme<RichEditorTheme>();
    TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
    if (spanItem->fontStyle) {
        textStyle.fontColor = spanItem->fontStyle->GetTextColor().value_or(style.GetTextColor()).ColorToString();
        textStyle.fontSize =
            spanItem->fontStyle->GetFontSize().value_or(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP)).ConvertToFp();
        textStyle.fontStyle =
            static_cast<int32_t>(spanItem->fontStyle->GetItalicFontStyle().value_or(OHOS::Ace::FontStyle::NORMAL));
        textStyle.fontWeight = static_cast<int32_t>(spanItem->fontStyle->GetFontWeight().value_or(FontWeight::NORMAL));
        std::string fontFamilyValue;
        const std::vector<std::string> defaultFontFamily = { "HarmonyOS Sans" };
        auto fontFamily = spanItem->fontStyle->GetFontFamily().value_or(defaultFontFamily);
        for (const auto& str : fontFamily) {
            fontFamilyValue += str;
            fontFamilyValue += ",";
        }
        fontFamilyValue = fontFamilyValue.substr(0, fontFamilyValue.size() ? fontFamilyValue.size() - 1 : 0);
        textStyle.fontFamily = !fontFamilyValue.empty() ? fontFamilyValue : defaultFontFamily.front();
        textStyle.decorationType =
            static_cast<int32_t>(spanItem->fontStyle->GetTextDecoration().value_or(TextDecoration::NONE));
        textStyle.decorationColor =
            spanItem->fontStyle->GetTextDecorationColor().value_or(style.GetTextDecorationColor()).ColorToString();
        textStyle.decorationStyle =
            static_cast<int32_t>(spanItem->fontStyle->GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID));
        textStyle.fontFeature = spanItem->fontStyle->GetFontFeature().value_or(ParseFontFeatureSettings("\"pnum\" 1"));
        textStyle.letterSpacing = spanItem->fontStyle->GetLetterSpacing().value_or(Dimension()).ConvertToFp();
    }
    if (spanItem->textLineStyle) {
        textStyle.lineHeight = spanItem->textLineStyle->GetLineHeight().value_or(Dimension()).ConvertToFp();
        textStyle.halfLeading = spanItem->textLineStyle->GetHalfLeading().value_or(false);
        textStyle.lineSpacing = spanItem->textLineStyle->GetLineSpacing().value_or(Dimension()).ConvertToFp();
        textStyle.textAlign = static_cast<int32_t>(spanItem->textLineStyle->GetTextAlign().value_or(TextAlign::START));
        auto lm = spanItem->textLineStyle->GetLeadingMargin();
        if (lm.has_value()) {
            textStyle.leadingMarginSize[RichEditorLeadingRange::LEADING_START] = lm.value().size.Width().ToString();
            textStyle.leadingMarginSize[RichEditorLeadingRange::LEADING_END] = lm.value().size.Height().ToString();
        }
        textStyle.wordBreak =
            static_cast<int32_t>(spanItem->textLineStyle->GetWordBreak().value_or(WordBreak::BREAK_WORD));
        textStyle.lineBreakStrategy =
            static_cast<int32_t>(spanItem->textLineStyle->GetLineBreakStrategy().value_or(LineBreakStrategy::GREEDY));
        textStyle.paragraphSpacing = spanItem->textLineStyle->GetParagraphSpacing();
    }
    textStyle.textBackgroundStyle = spanItem->backgroundStyle;
    return textStyle;
}

ImageStyleResult RichEditorPattern::GetImageStyleBySpanItem(const RefPtr<SpanItem>& spanItem)
{
    ImageStyleResult imageStyle;
    auto imageSpanItem = DynamicCast<ImageSpanItem>(spanItem);
    CHECK_NULL_RETURN(imageSpanItem, imageStyle);
    auto imageAttributeOp = imageSpanItem->options.imageAttribute;
    CHECK_NULL_RETURN(imageAttributeOp.has_value(), imageStyle);
    auto imageSizeOp = imageAttributeOp->size;
    if (imageSizeOp.has_value() && imageSizeOp->width.has_value() && imageSizeOp->height.has_value()) {
        imageStyle.size[RichEditorImageSize::SIZEWIDTH] = imageSizeOp->width->ConvertToPx();
        imageStyle.size[RichEditorImageSize::SIZEHEIGHT] = imageSizeOp->height->ConvertToPx();
    }
    if (imageAttributeOp->verticalAlign.has_value()) {
        imageStyle.verticalAlign = static_cast<int32_t>(imageAttributeOp->verticalAlign.value());
    }
    if (imageAttributeOp->objectFit.has_value()) {
        imageStyle.objectFit = static_cast<int32_t>(imageAttributeOp->objectFit.value());
    }
    if (imageAttributeOp->marginProp.has_value()) {
        imageStyle.margin = imageAttributeOp->marginProp->ToString();
    }
    if (imageAttributeOp->borderRadius.has_value()) {
        imageStyle.borderRadius = imageAttributeOp->borderRadius->ToString();
    }
    return imageStyle;
}

void RichEditorPattern::SetSubSpansWithAIWrite(RefPtr<SpanString>& spanString, int32_t start, int32_t end)
{
    placeholderSpansMap_.clear();
    CHECK_NULL_VOID(spanString);
    std::list<RefPtr<SpanItem>> subSpans;
    std::u16string text;
    size_t index = 0;
    size_t placeholderGains = 0;
    for (const auto& spanItem : spans_) {
        if (!spanItem) {
            continue;
        }
        auto oldEnd = spanItem->position;
        auto oldStart = spanItem->rangeStart;
        if (oldEnd <= start || oldStart >= end) {
            continue;
        }
        RefPtr<SpanItem> newSpanItem = MakeRefPtr<SpanItem>();
        auto spanStart = oldStart <= start ? 0 : oldStart - start;
        auto spanEnd = oldEnd < end ? oldEnd - start : end - start;
        spanStart += static_cast<int32_t>(placeholderGains);
        if (spanItem->spanItemType == SpanItemType::NORMAL) {
            newSpanItem = spanItem->GetSameStyleSpanItem();
            newSpanItem->urlAddress = spanItem->urlAddress;
            newSpanItem->content = spanItem->content
                    .substr(std::max(start - oldStart, 0), std::min(end, oldEnd) - std::max(start, oldStart));
        } else {
            InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
            spanEnd += static_cast<int32_t>(placeholderGains);
        }
        newSpanItem->interval = {spanStart, spanEnd};
        newSpanItem->position = spanEnd;
        newSpanItem->rangeStart = spanStart;
        newSpanItem->textLineStyle->ResetLeadingMargin();
        text.append(newSpanItem->content);
        subSpans.emplace_back(newSpanItem);
    }
    spanString->SetString(text);
    spanString->SetSpanItems(std::move(subSpans));
}

void RichEditorPattern::InitPlaceholderSpansMap(
    RefPtr<SpanItem>& newSpanItem, const RefPtr<SpanItem>& spanItem, size_t& index, size_t& placeholderGains)
{
    newSpanItem->content = UtfUtils::Str8ToStr16("![id" + std::to_string(index++) + "]");
    switch (spanItem->spanItemType) {
        case SpanItemType::SYMBOL: {
            placeholderSpansMap_[newSpanItem->content] = spanItem;
            placeholderGains += PLACEHOLDER_LENGTH - SYMBOL_CONTENT_LENGTH;
            break;
        }
        case SpanItemType::CustomSpan: {
            if (!isSpanStringMode_) {
                placeholderSpansMap_[newSpanItem->content] = spanItem;
            } else {
                auto customSpanItem = DynamicCast<CustomSpanItem>(spanItem);
                placeholderSpansMap_[newSpanItem->content] = customSpanItem;
            }
            placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH;
            break;
        }
        case SpanItemType::IMAGE: {
            placeholderSpansMap_[newSpanItem->content] = spanItem;
            placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH;
            break;
        }
        default:
            break;
    }
}

void RichEditorPattern::SetSubSpans(RefPtr<SpanString>& spanString, int32_t start, int32_t end)
{
    CHECK_NULL_VOID(spanString);
    std::list<RefPtr<SpanItem>> subSpans;
    std::u16string text;
    for (const auto& spanItem : spans_) {
        if (!spanItem || spanItem->spanItemType == SpanItemType::CustomSpan ||
            spanItem->spanItemType == SpanItemType::SYMBOL) {
            continue;
        }
        auto spanEndPos = spanItem->position;
        auto spanStartPos = spanItem->rangeStart;
        if (spanEndPos > start && spanStartPos < end) {
            int32_t oldStart = spanStartPos;
            int32_t oldEnd = spanEndPos;
            auto spanStart = oldStart <= start ? 0 : oldStart - start;
            auto spanEnd = oldEnd < end ? oldEnd - start : end - start;
            auto newSpanItem = GetSameSpanItem(spanItem);
            CHECK_NULL_CONTINUE(newSpanItem);
            newSpanItem->spanItemType = spanItem->spanItemType;
            newSpanItem->interval = {spanStart, spanEnd};
            newSpanItem->position = spanEnd;
            newSpanItem->rangeStart = spanStart;
            newSpanItem->content = spanItem->content
                    .substr(std::max(start - oldStart, 0), std::min(end, oldEnd) - std::max(start, oldStart));
            text.append(newSpanItem->content);
            subSpans.emplace_back(newSpanItem);
        }
    }
    spanString->SetString(text);
    spanString->SetSpanItems(std::move(subSpans));
}

RefPtr<SpanItem> RichEditorPattern::GetSameSpanItem(const RefPtr<SpanItem>& spanItem)
{
    CHECK_NULL_RETURN(spanItem, nullptr);
    if (spanItem->spanItemType == SpanItemType::IMAGE) {
        auto imageSpanItem = DynamicCast<ImageSpanItem>(spanItem);
        CHECK_NULL_RETURN(imageSpanItem, nullptr);
        auto newSpanItem = MakeRefPtr<ImageSpanItem>();
        auto options = imageSpanItem->options;
        if (!options.imagePixelMap) {
            auto imageNode = GetImageSpanNodeBySpanItem(imageSpanItem);
            CHECK_NULL_RETURN(imageNode, nullptr);
            auto pattern = imageNode->GetPattern<ImagePattern>();
            CHECK_NULL_RETURN(pattern, nullptr);
            auto image = pattern->GetCanvasImage();
            CHECK_NULL_RETURN(image, nullptr);
            auto pixelMap = image->GetPixelMap();
            if (!pixelMap) {
                pixelMap = imageNode->GetDragPixelMap();
            }
            options.imagePixelMap = pixelMap;
        }
        newSpanItem->SetImageSpanOptions(options);
        return newSpanItem;
    } else if (spanItem->spanItemType == SpanItemType::NORMAL) {
        auto newSpanItem = spanItem->GetSameStyleSpanItem();
        newSpanItem->urlAddress = spanItem->urlAddress;
        return newSpanItem;
    }
    return nullptr;
}

RefPtr<ImageSpanNode> RichEditorPattern::GetImageSpanNodeBySpanItem(const RefPtr<ImageSpanItem>& spanItem)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto uiNodes = host->GetChildren();
    auto it = std::find_if(uiNodes.begin(), uiNodes.end(), [spanItem](const RefPtr<UINode>& uiNode) {
        auto imageSpanNode = DynamicCast<ImageSpanNode>(uiNode);
        CHECK_NULL_RETURN(imageSpanNode, false);
        return imageSpanNode->GetSpanItem() == spanItem;
    });
    CHECK_NULL_RETURN(it != uiNodes.end(), nullptr);
    return DynamicCast<ImageSpanNode>(*it);
}

void RichEditorPattern::SetSubMap(RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(spanString);
    auto subSpans = spanString->GetSpanItems();
    std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>> subMap;
    for (auto& spanItem : subSpans) {
        if (!spanItem) {
            continue;
        }
        auto start = spanItem->rangeStart;
        auto end = spanItem->position;
        std::list<RefPtr<SpanBase>> spanBases;
        if (spanItem->spanItemType == NG::SpanItemType::IMAGE) {
            spanBases = { spanString->ToImageSpan(spanItem, start, end) };
        } else if (spanItem->spanItemType == NG::SpanItemType::NORMAL) {
            spanBases = { spanString->ToFontSpan(spanItem, start, end),
                spanString->ToDecorationSpan(spanItem, start, end),
                spanString->ToBaselineOffsetSpan(spanItem, start, end),
                spanString->ToLetterSpacingSpan(spanItem, start, end),
                spanString->ToGestureSpan(spanItem, start, end),
                spanString->ToParagraphStyleSpan(spanItem, start, end),
                spanString->ToLineHeightSpan(spanItem, start, end),
                spanString->ToBackgroundColorSpan(spanItem, start, end),
                spanString->ToUrlSpan(spanItem, start, end) };
        }
        for (auto& spanBase : spanBases) {
            if (!spanBase) {
                continue;
            }
            auto it = subMap.find(spanBase->GetSpanType());
            if (it == subMap.end()) {
                subMap.insert({ spanBase->GetSpanType(), { spanBase } });
            } else {
                it->second.emplace_back(std::move(spanBase));
            }
        }
    }
    spanString->SetSpanMap(std::move(subMap));
}

void RichEditorPattern::AddSpanByPasteData(const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(spanString);
    if (spanString->GetSpansMap().empty()) {
        CompleteStyledString(const_cast<RefPtr<SpanString>&>(spanString));
    }
    if (isSpanStringMode_) {
        InsertStyledStringByPaste(spanString);
    } else {
        AddSpansByPaste(spanString->GetSpanItems());
    }

    if (aiWriteAdapter_->GetAIWrite()) {
        return;
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::CompleteStyledString(RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(spanString);
    std::u16string text;
    auto spans = spanString->GetSpanItems();
    std::for_each(spans.begin(), spans.end(), [&text](RefPtr<SpanItem>& item) {
        CHECK_NULL_VOID(item);
        text.append(item->content);
        item->position = item->interval.second;
        item->rangeStart = item->interval.first;
    });
    spanString->SetString(std::move(text));
    SetSubMap(spanString);
}

void RichEditorPattern::InsertStyledStringByPaste(const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(spanString && styledString_);
    int32_t changeStart = caretPosition_;
    int32_t changeLength = 0;
    if (textSelector_.IsValid()) {
        changeStart = textSelector_.GetTextStart();
        changeLength = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    }
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(changeStart, changeLength, spanString, record);
    CHECK_NULL_VOID(BeforeStyledStringChange(record));
    undoManager_->RecordOperation(record);
    auto subSpanString = spanString;
    int32_t startLength = maxLength_.value_or(INT_MAX) + changeLength - GetTextContentLength();
    if (spanString->GetLength() >= startLength) {
        auto range = TextEmojiProcessor::CalSubU16stringRange(
            startLength, spanString->GetLength() - startLength, spanString->GetU16string(), true, true);
        auto subLength = range.endIndex - range.startIndex;
        subSpanString = subSpanString->GetSubSpanString(0, spanString->GetLength() - subLength);
    }

    if (changeLength > 0 && subSpanString->GetLength() > 0) {
        DeleteForwardInStyledString(changeLength, false);
    }
    ResetSelection();
    styledString_->InsertSpanString(changeStart, subSpanString);
    SetCaretPosition(caretPosition_ + subSpanString->GetLength());
    AfterStyledStringChange(changeStart, changeLength, subSpanString->GetU16string());
}

void RichEditorPattern::HandleOnDragInsertStyledString(const RefPtr<SpanString>& spanString, bool isCopy)
{
    CHECK_NULL_VOID(spanString);
    int currentCaretPosition = caretPosition_;
    auto strLength = spanString->GetLength();
    insertValueLength_ = strLength;
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(currentCaretPosition, 0, spanString, record);
    if (isDragSponsor_ && !isCopy) {
        bool isInsertForward = currentCaretPosition < dragRange_.first;
        bool isInsertBackward = currentCaretPosition > dragRange_.second;
        CHECK_NULL_VOID(isInsertForward || isInsertBackward);
        CHECK_NULL_VOID(BeforeStyledStringChange(record));
        undoManager_->RecordOperation(record);
        styledString_->InsertSpanString(currentCaretPosition, spanString);
        AfterStyledStringChange(record);
        if (isInsertForward) {
            SetCaretPosition(currentCaretPosition + strLength);
            dragRange_.first += strLength;
            dragRange_.second += strLength;
        }
        DeleteValueInStyledString(dragRange_.first, strLength, true, false);
    } else {
        CHECK_NULL_VOID(BeforeStyledStringChange(record));
        undoManager_->RecordOperation(record);
        styledString_->InsertSpanString(currentCaretPosition, spanString);
        SetCaretPosition(currentCaretPosition + strLength);
        AfterStyledStringChange(record);
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void RichEditorPattern::AddSpansByPaste(const std::list<RefPtr<NG::SpanItem>>& spans)
{
    if (GetTextContentLength() >= maxLength_.value_or(INT_MAX)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "AddSpansByPaste: Reach the maxLength. maxLength=%{public}d", maxLength_.value_or(INT_MAX));
        return;
    }
    if (textSelector_.IsValid()) {
        SetCaretPosition(textSelector_.GetTextStart());
        DeleteForward(textSelector_.GetTextStart(), textSelector_.GetTextEnd() - textSelector_.GetTextStart());
        ResetSelection();
    }
    for (const auto& spanItem : spans) {
        if (!spanItem) {
            continue;
        }
        auto imageSpanItem = DynamicCast<ImageSpanItem>(spanItem);
        if (imageSpanItem) {
            auto options = imageSpanItem->options;
            options.offset = caretPosition_;
            AddImageSpan(options, true, caretPosition_, true);
        } else {
            auto options = GetTextSpanOptions(spanItem);
            AddTextSpan(options, true, caretPosition_);
        }
    }
}

int32_t RichEditorPattern::CalculateTruncationLength(const std::u16string& insertValue, int32_t start)
{
    if (!textSelector_.SelectNothing()) {
        start += textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    }
    auto truncationLength = static_cast<int32_t>(insertValue.length()) - start;
    auto range = TextEmojiProcessor::CalSubU16stringRange(start, truncationLength, insertValue, true, true);
    auto allowInsertLength = static_cast<int32_t>(insertValue.length()) - range.endIndex + range.startIndex;
    return allowInsertLength;
}

TextSpanOptions RichEditorPattern::GetTextSpanOptions(const RefPtr<SpanItem>& spanItem)
{
    CHECK_NULL_RETURN(spanItem, {});
    TextStyle textStyle = GetDefaultTextStyle();
    UseSelfStyle(spanItem->fontStyle, spanItem->textLineStyle, textStyle);
    textStyle.SetTextBackgroundStyle(spanItem->backgroundStyle);
    struct UpdateParagraphStyle paraStyle;
    paraStyle.textAlign = spanItem->textLineStyle->GetTextAlign();
    paraStyle.leadingMargin = spanItem->textLineStyle->GetLeadingMargin();
    paraStyle.wordBreak = spanItem->textLineStyle->GetWordBreak();
    paraStyle.lineBreakStrategy = spanItem->textLineStyle->GetLineBreakStrategy();
    paraStyle.paragraphSpacing = spanItem->textLineStyle->GetParagraphSpacing();
    TextSpanOptions options;
    options.value = spanItem->content;
    options.offset = caretPosition_;
    UserGestureOptions gestureOption;
    gestureOption.onClick = spanItem->onClick;
    gestureOption.onLongPress = spanItem->onLongPress;
    options.userGestureOption = gestureOption;
    options.style = textStyle;
    options.paraStyle = paraStyle;
    return options;
}

void RichEditorPattern::ResetDragSpanItems()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::unordered_set<int32_t> nodeIds;
    std::for_each(dragSpanItems_.begin(), dragSpanItems_.end(), [&nodeIds](RefPtr<SpanItem>& item) {
        CHECK_NULL_VOID(item);
        item->EndDrag();
        auto imageSpanItem = DynamicCast<ImageSpanItem>(item);
        if (imageSpanItem) {
            nodeIds.emplace(imageSpanItem->nodeId_);
            return;
        }
        auto placeholderSpanItem = DynamicCast<PlaceholderSpanItem>(item);
        if (placeholderSpanItem) {
            nodeIds.emplace(placeholderSpanItem->placeholderSpanNodeId);
        }
    });
    const auto& childrens = host->GetChildren();
    for (const auto& child : childrens) {
        auto findResult = nodeIds.find(child->GetId());
        CHECK_NULL_CONTINUE(findResult != nodeIds.end());
        auto node = DynamicCast<FrameNode>(child);
        CHECK_NULL_CONTINUE(node);
        auto renderContext = node->GetRenderContext();
        CHECK_NULL_CONTINUE(renderContext);
        renderContext->UpdateOpacity(1);
        node->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    dragSpanItems_.clear();
}

bool RichEditorPattern::SelectOverlayIsOn()
{
    return selectOverlay_->SelectOverlayIsOn();
}

void RichEditorPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
#ifdef ENABLE_STANDARD_INPUT
    InsertValue(UtfUtils::Str8ToStr16(value->text), true);
#else
    if (value->isDelete) {
        HandleOnDelete(true);
    } else {
        InsertValue(UtfUtils::Str8ToStr16(value->appendText));
    }
#endif
}

void RichEditorPattern::HandleAISpanHoverEvent(const MouseInfo& info)
{
    if (info.GetAction() != MouseAction::MOVE || !NeedShowAIDetect()) {
        return;
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar && (scrollBar->IsHover() || scrollBar->IsPressed())) {
        return;
    }
    if (dataDetectorAdapter_->aiSpanRects_.empty()) {
        for (const auto& kv : dataDetectorAdapter_->aiSpanMap_) {
            auto& aiSpan = kv.second;
            const auto& aiRects = paragraphs_.GetRects(aiSpan.start, aiSpan.end);
            dataDetectorAdapter_->aiSpanRects_.insert(
                dataDetectorAdapter_->aiSpanRects_.end(), aiRects.begin(), aiRects.end());
        }
    }

    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    PointF textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto nodeId = host->GetId();
    for (auto&& rect : dataDetectorAdapter_->aiSpanRects_) {
        if (!rect.IsInRegion(textOffset)) {
            continue;
        }
        if (currentMouseStyle_ != MouseFormat::HAND_POINTING) {
            pipeline->ChangeMouseStyle(nodeId, MouseFormat::HAND_POINTING);
            currentMouseStyle_ = MouseFormat::HAND_POINTING;
        }
        return;
    }
    if (currentMouseStyle_ != MouseFormat::TEXT_CURSOR) {
        pipeline->ChangeMouseStyle(nodeId, MouseFormat::TEXT_CURSOR);
        currentMouseStyle_ = MouseFormat::TEXT_CURSOR;
    }
}

void RichEditorPattern::InitMouseEvent()
{
    CHECK_NULL_VOID(!mouseEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "on hover event isHover=%{public}d", isHover);
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    auto hoverEvent = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent);
    mouseEventInitialized_ = true;
}

void RichEditorPattern::OnHover(bool isHover)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "isHover=%{public}d", isHover);
    if (!isHover && lastHoverSpanItem_) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "spanItem hover false");
        lastHoverSpanItem_->onHover_(false, lastHoverInfo_);
        lastHoverSpanItem_.Reset();
    }
    auto scrollBar = GetScrollBar();
    if (isHover && (!scrollBar || !scrollBar->IsPressed())) {
        ChangeMouseStyle(MouseFormat::TEXT_CURSOR);
    } else {
        ChangeMouseStyle(MouseFormat::DEFAULT, true);
        HandleUrlSpanForegroundClear();
    }
}

void RichEditorPattern::ChangeMouseStyle(MouseFormat format, bool freeMouseHoldNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto nodeId = host->GetId();
    // Do not change mouse style to text-cursor if the right-button custom menu is showing
    bool shouldPreventChange = (format == MouseFormat::TEXT_CURSOR && selectOverlay_->IsRightButtonCustomMenuShow());
    CHECK_NULL_VOID(!shouldPreventChange);
    pipeline->SetMouseStyleHoldNode(nodeId);
    pipeline->ChangeMouseStyle(nodeId, format);
    currentMouseStyle_ = format;
    IF_TRUE(freeMouseHoldNode, pipeline->FreeMouseStyleHoldNode(nodeId));
}

bool RichEditorPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard,
    SourceType sourceType)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(needShowSoftKeyboard, false);
    if (needShowSoftKeyboard && customKeyboardBuilder_) {
        return RequestCustomKeyboard();
    }
#if defined(ENABLE_STANDARD_INPUT)
    if (!EnableStandardInput(needShowSoftKeyboard, sourceType)) {
        return false;
    }
#else
    if (!UnableStandardInput(isFocusViewChanged)) {
        return false;
    }
#endif
    return true;
}

#if defined(ENABLE_STANDARD_INPUT)
#ifdef WINDOW_SCENE_SUPPORTED
uint32_t RichEditorPattern::GetSCBSystemWindowId()
{
    RefPtr<FrameNode> frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, {});
    auto focusSystemWindowId = WindowSceneHelper::GetFocusSystemWindowId(frameNode);
    return focusSystemWindowId;
}
#endif

bool RichEditorPattern::EnableStandardInput(bool needShowSoftKeyboard, SourceType sourceType)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    if (richEditTextChangeListener_ == nullptr) {
        richEditTextChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    CHECK_NULL_RETURN(inputMethod, false);
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_RETURN(miscTextConfig.has_value(), false);
    TAG_LOGD(
        AceLogTag::ACE_RICH_TEXT, "RequestKeyboard set calling window id is : %{public}u", miscTextConfig->windowId);
    MiscServices::TextConfig textconfig = miscTextConfig.value();
#ifdef WINDOW_SCENE_SUPPORTED
    auto systemWindowId = GetSCBSystemWindowId();
    if (systemWindowId) {
        miscTextConfig->windowId = systemWindowId;
    }
#endif
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (host && textFieldManager) {
        textFieldManager->SetImeAttached(true);
        textFieldManager->SetLastRequestKeyboardId(host->GetId());
    }
    OHOS::MiscServices::AttachOptions attachOptions;
    attachOptions.isShowKeyboard = needShowSoftKeyboard;
    attachOptions.requestKeyboardReason =
        static_cast<OHOS::MiscServices::RequestKeyboardReason>(static_cast<int32_t>(sourceType));
    auto ret = inputMethod->Attach(richEditTextChangeListener_, attachOptions, textconfig);
    if (ret == MiscServices::ErrorCode::NO_ERROR) {
        textFieldManager->SetIsImeAttached(true);
    }
    UpdateCaretInfoToController();
    if (context) {
        inputMethod->SetCallingWindow(context->GetWindowId());
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    imeAttached_ = true;
#endif
    return true;
}

std::optional<MiscServices::TextConfig> RichEditorPattern::GetMiscTextConfig()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, {});
    auto pipeline = tmpHost->GetContextRefPtr();
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_RETURN(pipeline && renderContext, {});

    float caretHeight = 0.0f;
    OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
    if (NearZero(caretHeight)) {
        auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
        caretHeight = overlayModifier ? overlayModifier->GetCaretHeight() : DEFAULT_CARET_HEIGHT;
    }
    if (NearZero(caretHeight)) {
        auto [caretAdjustOffset, caretAdjustHeight] = CalculateCaretOffsetAndHeight();
        caretHeight = caretAdjustHeight;
    }

    // richeditor relative to root node offset(without transform)
    auto parentGlobalOffset = renderContext->GetPaintRectWithoutTransform().GetOffset() -
        pipeline->GetRootRect().GetOffset();
    // caret top (without transform）
    auto caretTop = caretOffset.GetY() + parentGlobalOffset.GetY();
    double positionY = parentGlobalOffset.GetY();
    double height = caretTop + caretHeight + KEYBOARD_AVOID_OFFSET.ConvertToPx() - positionY;

    if (auto manager = pipeline->GetSafeAreaManager(); manager) {
        auto keyboardOffset = manager->GetKeyboardOffset();
        positionY -= keyboardOffset;
    }
    OffsetF caretLeftTopPoint(caretOffset.GetX() + parentGlobalOffset.GetX(), caretTop);
    OffsetF caretRightBottomPoint(caretLeftTopPoint.GetX() + CARET_WIDTH, caretLeftTopPoint.GetY() + caretHeight);
    HandlePointWithTransform(caretLeftTopPoint);
    HandlePointWithTransform(caretRightBottomPoint);
    // window rect relative to screen
    auto windowRect = pipeline->GetCurrentWindowRect();
    MiscServices::CursorInfo cursorInfo { .left = caretLeftTopPoint.GetX() + windowRect.Left(),
        .top = caretLeftTopPoint.GetY() + windowRect.Top(),
        .width = std::abs(caretLeftTopPoint.GetX() - caretRightBottomPoint.GetX()),
        .height = std::abs(caretLeftTopPoint.GetY() - caretRightBottomPoint.GetY()) };
    MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)TextInputType::UNSPECIFIED,
        .enterKeyType = (int32_t)GetTextInputActionValue(GetDefaultTextInputAction()),
        .isTextPreviewSupported = isTextPreviewSupported_ && (!isSpanStringMode_ || isAPI18Plus),
        .immersiveMode = static_cast<int32_t>(keyboardAppearance_) };
    auto start = textSelector_.IsValid() ? textSelector_.GetStart() : caretPosition_;
    auto end = textSelector_.IsValid() ? textSelector_.GetEnd() : caretPosition_;
    MiscServices::TextConfig textConfig = { .inputAttribute = inputAttribute,
        .cursorInfo = cursorInfo,
        .range = { .start = start, .end = end },
        .windowId = pipeline->GetFocusWindowId(),
        .positionY = positionY + windowRect.Top(),
        .height = height };
    return textConfig;
}
#else
bool RichEditorPattern::UnableStandardInput(bool isFocusViewChanged)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    if (HasConnection()) {
        connection_->Show(isFocusViewChanged, GetInstanceId());
        return true;
    }
    TextInputConfiguration config;
    config.type = TextInputType::UNSPECIFIED;
    config.action = TextInputAction::DONE;
    config.obscureText = false;
    connection_ =
        TextInputProxy::GetInstance().Attach(WeakClaim(this), config, context->GetTaskExecutor(), GetInstanceId());
    if (!HasConnection()) {
        return false;
    }
    TextEditingValue value;
    if (spans_.empty()) {
        value.text = UtfUtils::Str16ToStr8(textForDisplay_);
    } else {
        for (auto it = spans_.begin(); it != spans_.end(); it++) {
            if ((*it)->placeholderIndex < 0) {
                value.text.append(UtfUtils::Str16ToStr8((*it)->content));
            } else {
                value.text.append(" ");
            }
        }
    }
    value.selection.Update(caretPosition_, caretPosition_);
    connection_->SetEditingState(value, GetInstanceId());
    connection_->Show(isFocusViewChanged, GetInstanceId());
    return true;
}
#endif

void RichEditorPattern::OnColorConfigurationUpdate()
{
    auto colorMode = GetColorMode();
    floatingCaretState_.UpdateOriginCaretColor(GetDisplayColorMode());
    if (colorMode == ColorMode::COLOR_MODE_UNDEFINED) {
        OnCommonColorChange();
    }
}

bool RichEditorPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    IF_PRESENT(magnifierController_, SetColorModeChange(true));
    floatingCaretState_.UpdateOriginCaretColor(GetDisplayColorMode());
    OnCommonColorChange();
    return false;
}

void RichEditorPattern::OnCommonColorChange()
{
    auto host = GetHost();
    auto theme = GetTheme<RichEditorTheme>();
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(host && theme && textLayoutProperty);

    auto displayColorMode = GetDisplayColorMode();
    COLOR_MODE_LOCK(displayColorMode);

    const auto& themeTextStyle = theme->GetTextStyle();
    auto themeTextColor = themeTextStyle.GetTextColor();
    auto themeTextDecColor = themeTextStyle.GetTextDecorationColor();
    textLayoutProperty->UpdateTextColor(themeTextColor);
    textLayoutProperty->UpdateTextDecorationColor(themeTextDecColor);
    auto themeUrlSpanColor = GetUrlSpanColor();
    textLayoutProperty->UpdateUrlDefualtColor(themeUrlSpanColor);
    textLayoutProperty->UpdateUrlHoverColor(GetUrlHoverColor());
    textLayoutProperty->UpdateUrlPressedColor(GetUrlPressColor());

    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "theme, ColorMode=%{public}d, TextColor=%{public}s, DecorationColor=%{public}s",
        displayColorMode, themeTextColor.ToString().c_str(), themeTextDecColor.ToString().c_str());

    const auto& spans = host->GetChildren();
    for (const auto& uiNode : spans) {
        auto placeholderSpan = DynamicCast<PlaceholderSpanNode>(uiNode);
        if (placeholderSpan) {
            auto spanItem = placeholderSpan->GetSpanItem();
            CHECK_NULL_CONTINUE(spanItem);
            IF_PRESENT(spanItem, UpdateColorByResourceId());
        }
        auto spanNode = DynamicCast<SpanNode>(uiNode);
        CHECK_NULL_CONTINUE(spanNode);
        auto spanItem = spanNode->GetSpanItem();
        CHECK_NULL_CONTINUE(spanItem);
        auto& textColor = spanItem->urlOnRelease ? themeUrlSpanColor : themeTextColor;
        IF_TRUE(spanItem->useThemeFontColor, spanNode->UpdateTextColorWithoutCheck(textColor));
        IF_TRUE(spanItem->useThemeDecorationColor, spanNode->UpdateTextDecorationColorWithoutCheck(themeTextDecColor));
        spanNode->UpdateColorByResourceId();
    }
    paragraphCache_.Clear();
    IF_PRESENT(typingTextStyle_, UpdateColorByResourceId());
    IF_PRESENT(typingStyle_, UpdateColorByResourceId());
    IF_PRESENT(selectedBackgroundColor_, UpdateColorByResourceId());

    IF_PRESENT(magnifierController_, SetColorModeChange(true));
    auto scrollBar = GetScrollBar();
    auto scrollbarTheme = GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(scrollBar && scrollbarTheme);
    scrollBar->SetForegroundColor(scrollbarTheme->GetForegroundColor());
    scrollBar->SetBackgroundColor(scrollbarTheme->GetBackgroundColor());
}

void RichEditorPattern::UpdateCaretInfoToController()
{
    CHECK_NULL_VOID(HasFocus());
    std::u16string text = u"";
    for (auto iter = spans_.begin(); iter != spans_.end(); iter++) {
        text += (*iter)->content;
    }
    auto start = textSelector_.IsValid() ? textSelector_.GetTextStart() : caretPosition_;
    auto end = textSelector_.IsValid() ? textSelector_.GetTextEnd() : caretPosition_;
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        text, start, end);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT,
        "CursorInfo: pos=[%{public}.2f,%{public}.2f], size=[%{public}.2f,%{public}.2f], caret=%{public}d;"
        "OnSelectionChange: textLen=%{public}zu, range=[%{public}d,%{public}d]",
        cursorInfo.left, cursorInfo.top, cursorInfo.width, cursorInfo.height, caretPosition_,
        text.length(), start, end);
#else
    if (HasConnection()) {
        TextEditingValue editingValue;
        editingValue.text = UtfUtils::Str16ToStr8(text);
        editingValue.hint = "";
        editingValue.selection.Update(start, end);
        connection_->SetEditingState(editingValue, GetInstanceId());
    }
#endif
}

bool RichEditorPattern::HasConnection() const
{
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    return imeAttached_;
#else
    return connection_ != nullptr;
#endif
}

void RichEditorPattern::SetCustomKeyboardOption(bool supportAvoidance)
{
    keyboardAvoidance_ = supportAvoidance;
}

bool RichEditorPattern::RequestCustomKeyboard()
{
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "RequestCKeyboard,close softkeyboard.");
        inputMethod->RequestHideInput();
        inputMethod->Close();
    }
#else
    if (HasConnection()) {
        connection_->Close(GetInstanceId());
        connection_ = nullptr;
    }
#endif

    if (isCustomKeyboardAttached_) {
        return true;
    }
    CHECK_NULL_RETURN(customKeyboardBuilder_, false);
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->SetCustomKeyboardOption(keyboardAvoidance_);
    overlayManager->BindKeyboard(customKeyboardBuilder_, frameNode->GetId());
    isCustomKeyboardAttached_ = true;
    contentChange_ = false;
    keyboardOverlay_ = overlayManager;
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    keyboardOverlay_->AvoidCustomKeyboard(frameNode->GetId(), caretHeight);
    return true;
}

bool RichEditorPattern::CloseCustomKeyboard()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    CHECK_NULL_RETURN(keyboardOverlay_, false);
    keyboardOverlay_->CloseKeyboard(frameNode->GetId());
    isCustomKeyboardAttached_ = false;
    contentChange_ = false;
    return true;
}

int32_t RichEditorPattern::CheckPreviewTextValidate(const std::u16string& previewTextValue, const PreviewRange range)
{
    if (IsDragging()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "SetPreviewText is not allowed while dragging");
        return ERROR_BAD_PARAMETERS;
    }
    return NO_ERRORS;
}

int32_t RichEditorPattern::CheckPreviewTextValidate(const std::string& previewTextValue, const PreviewRange range)
{
    return CheckPreviewTextValidate(UtfUtils::Str8DebugToStr16(previewTextValue), range);
}

int32_t RichEditorPattern::SetPreviewText(const std::u16string& previewTextValue, const PreviewRange range)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "SetPreviewText, range=[%{public}d,%{public}d], isSSMode=%{public}d",
        range.start, range.end, isSpanStringMode_);
    CHECK_NULL_RETURN(!isSpanStringMode_ || isAPI18Plus, ERROR_BAD_PARAMETERS);
    SEC_TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "previewText=%{public}s", UtfUtils::Str16ToStr8(previewTextValue).c_str());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ERROR_BAD_PARAMETERS);
    CHECK_NULL_RETURN(!IsDragging(), ERROR_BAD_PARAMETERS);

    if (!IsPreviewTextInputting()) {
        if (!InitPreviewText(previewTextValue, range)) {
            return ERROR_BAD_PARAMETERS;
        }
    } else {
        if (!UpdatePreviewText(previewTextValue, range)) {
            return ERROR_BAD_PARAMETERS;
        }
    }
    previewTextRecord_.replacedRange.Set(previewTextRecord_.startOffset, previewTextRecord_.endOffset);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return NO_ERRORS;
}

bool RichEditorPattern::InitPreviewText(const std::u16string& previewTextValue, const PreviewRange& range)
{
    if (range.start != -1 || range.end != -1) {
        return ReplaceText(previewTextValue, range);
    }
    // interrupt touch selecting when initialize preview text
    ResetTouchSelectState();
    IF_PRESENT(magnifierController_, RemoveMagnifierFrameNode());
    auto& record = previewTextRecord_;
    record.needReplacePreviewText = true;
    record.previewTextHasStarted = true;
    record.replacedRange = range;
    record.startOffset = textSelector_.SelectNothing() ? caretPosition_ : textSelector_.GetTextStart();
    record.newPreviewContent = previewTextValue;
    auto length = static_cast<int32_t>(previewTextValue.length());
    record.endOffset = record.startOffset + length;
    auto spanCountBefore = spans_.size();
    ProcessInsertValue(previewTextValue, OperationType::IME, false);
    record.isSpanSplit = spans_.size() - spanCountBefore > 1;
    record.previewContent = record.newPreviewContent;
    record.newPreviewContent.clear();
    record.needReplacePreviewText = false;
    return true;
}

bool RichEditorPattern::ReplaceText(const std::u16string& previewTextValue, const PreviewRange& range)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "ReplaceText");
    if (range.start < 0 || range.end < range.start || range.end > GetTextContentLength()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "bad PreviewRange");
        return false;
    }
    previewTextRecord_.replacedRange = range;
    previewTextRecord_.needReplaceText = true;
    previewTextRecord_.startOffset = range.start;
    previewTextRecord_.endOffset = range.end;
    ProcessInsertValue(previewTextValue, OperationType::IME, false);
    previewTextRecord_.needReplaceText = false;
    return true;
}

// Used for text replacement, without notifying developer caret change
void RichEditorPattern::DeleteByRange(OperationRecord* const record, int32_t start, int32_t end)
{
    auto length = end - start;
    CHECK_NULL_VOID(length > 0);
    lastCaretPosition_ = caretPosition_;
    caretPosition_ = std::clamp(start, 0, GetTextContentLength());
    if (isSpanStringMode_) {
        DeleteValueInStyledString(start, length, true, false);
        return;
    }
    std::u16string deleteText = DeleteForwardOperation(length);
    if (record && deleteText.length() != 0) {
        record->deleteText = deleteText;
    }
}

bool RichEditorPattern::NotUpdateCaretInPreview(int32_t caret, const PreviewTextRecord& record)
{
    CHECK_NULL_RETURN(record.IsValid(), false);
    bool caretInSecondPos = caret == record.startOffset + 1;
    bool caretNotInEndPos = caret != record.endOffset;

    auto& curContent = record.previewContent;
    auto& newContent = record.newPreviewContent;
    auto enFilter = [](char c) { return isalpha(c) || c == '\''; };
    bool curAllEn = std::all_of(curContent.begin(), curContent.end(), enFilter);
    bool newAllEn = std::all_of(newContent.begin(), newContent.end(), enFilter);

    return caretInSecondPos && caretNotInEndPos && curAllEn && newAllEn;
}

bool RichEditorPattern::UpdatePreviewText(const std::u16string& previewTextValue, const PreviewRange& range)
{
    auto& record = previewTextRecord_;
    if (range.start == -1 && range.end == -1 && !record.previewContent.empty()) {
        record.replacedRange.Set(record.startOffset, record.endOffset);
        record.newPreviewContent = previewTextValue;
        record.needReplacePreviewText = true;
        record.needUpdateCaret = !NotUpdateCaretInPreview(caretPosition_, record);
        ProcessInsertValue(previewTextValue, OperationType::IME, false);
        record.previewContent = record.newPreviewContent;
        record.newPreviewContent.clear();
        record.endOffset = record.startOffset + static_cast<int32_t>(previewTextValue.length());
        record.needReplacePreviewText = false;
        record.needUpdateCaret = true;
    } else {
        if (range.start < record.startOffset || range.end > record.endOffset || range.end < range.start) {
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "bad PreviewRange");
            return false;
        }
        if (previewTextValue.empty() && range.start == range.end) {
            SetCaretPosition(range.end);
            return false;
        }
        auto replaceIndex = range.start - record.startOffset;
        auto replaceLength = range.end - range.start;
        auto oldContent = record.previewContent;
        auto oldPreviewLength = static_cast<int32_t>(oldContent.length());
        if (replaceIndex < 0 || replaceIndex + replaceLength > oldPreviewLength) {
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "bad replaced range ");
            return false;
        }
        auto newContent = oldContent.replace(replaceIndex, replaceLength, previewTextValue);
        record.replacedRange = range;
        record.newPreviewContent = newContent;
        record.needReplacePreviewText = true;
        ProcessInsertValue(previewTextValue, OperationType::IME, false);
        record.previewContent = record.newPreviewContent;
        record.newPreviewContent.clear();
        record.endOffset = record.startOffset + static_cast<int32_t>(newContent.length());
        record.needReplacePreviewText = false;
    }
    return true;
}

const PreviewTextInfo RichEditorPattern::GetPreviewTextInfo() const
{
    PreviewTextInfo info;
    if (!previewTextRecord_.previewContent.empty()) {
        info.value = previewTextRecord_.previewContent;
        info.offset = previewTextRecord_.startOffset;
    }
    return info;
}

void RichEditorPattern::MergeAdjacentSpans(int32_t caretPosition)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto uiNodes = host->GetChildren();
    auto it = std::find_if(uiNodes.begin(), uiNodes.end(), [caretPosition](const RefPtr<UINode>& uiNode) {
        auto spanNode = DynamicCast<SpanNode>(uiNode);
        CHECK_NULL_RETURN(spanNode, false);
        return spanNode->GetSpanItem()->position == caretPosition;
    });
    CHECK_NULL_VOID(it != uiNodes.end());
    auto beforeSpanNode = DynamicCast<SpanNode>(*it);
    ++it;
    CHECK_NULL_VOID(it != uiNodes.end());
    auto afterSpanNode = DynamicCast<SpanNode>(*it);
    CHECK_NULL_VOID(beforeSpanNode && afterSpanNode);
    CHECK_NULL_VOID(beforeSpanNode->GetTag() == V2::SPAN_ETS_TAG && afterSpanNode->GetTag() == V2::SPAN_ETS_TAG);
    auto beforeSpanItem = beforeSpanNode->GetSpanItem();
    auto afterSpanItem = afterSpanNode->GetSpanItem();
    CHECK_NULL_VOID(beforeSpanItem && afterSpanItem);
    beforeSpanNode->UpdateContent(beforeSpanItem->content + afterSpanItem->content);
    afterSpanItem->content.clear();
    RemoveEmptySpans();
}

void RichEditorPattern::FinishTextPreview()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "FinishTextPreview byImf");
    if (previewTextRecord_.previewContent.empty()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "previewContent is empty");
        RemoveEmptySpans();
        IF_TRUE(previewTextRecord_.isSpanSplit, MergeAdjacentSpans(caretPosition_));
        previewTextRecord_.Reset();
        return;
    }
    auto previewContent = previewTextRecord_.previewContent;
    FinishTextPreviewInner();
    ProcessInsertValue(previewContent, OperationType::IME, true);
}

void RichEditorPattern::FinishTextPreviewInner(bool deletePreviewText)
{
    CHECK_NULL_VOID(previewTextRecord_.previewTextHasStarted);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "FinishTextPreviewInner, deleteText=%{public}d, previewContent is empty=%{public}d", deletePreviewText,
        previewTextRecord_.previewContent.empty());
    previewTextRecord_.previewTextExiting = true;
    IF_TRUE(deletePreviewText && !previewTextRecord_.previewContent.empty(),
        DeleteByRange(nullptr, previewTextRecord_.startOffset, previewTextRecord_.endOffset));
    previewTextRecord_.Reset();
}

void RichEditorPattern::NotifyExitTextPreview(bool deletePreviewText)
{
    CHECK_NULL_VOID(previewTextRecord_.previewTextHasStarted);
    CHECK_NULL_VOID(HasFocus());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "NotifyExitTextPreview");
    FinishTextPreviewInner(deletePreviewText);
    NotifyImfFinishTextPreview();
}

void RichEditorPattern::NotifyImfFinishTextPreview()
{
#if defined(ENABLE_STANDARD_INPUT)
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(u"", caretPosition_, caretPosition_);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "notify imf that richEditor exit textPreview");
#endif
}

std::vector<RectF> RichEditorPattern::GetPreviewTextRects()
{
    auto rects = paragraphs_.GetRects(previewTextRecord_.startOffset, previewTextRecord_.endOffset,
        RectHeightPolicy::COVER_TEXT);
    auto offset = GetTextRect().GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    for (RectF& rect : rects) {
        rect += offset;
    }
    return rects;
}

PreviewTextStyle RichEditorPattern::GetPreviewTextStyle() const
{
    auto previewTextStyle = PreviewTextStyle::NORMAL;
    auto property = GetLayoutProperty<RichEditorLayoutProperty>();
    if (property && property->HasPreviewTextStyle()) {
        auto style = property->GetPreviewTextStyle();
        CHECK_NULL_RETURN(style.has_value(), previewTextStyle);
        if (style.value() == PREVIEW_STYLE_NORMAL) {
            previewTextStyle = PreviewTextStyle::NORMAL;
        } else if (style.value() == PREVIEW_STYLE_UNDERLINE) {
            previewTextStyle = PreviewTextStyle::UNDERLINE;
        } else {
            TAG_LOGW(
                AceLogTag::ACE_RICH_TEXT, "invalid previewTextStyle of RichEditorLayoutProperty");
        }
    }
    return previewTextStyle;
}

const Color& RichEditorPattern::GetPreviewTextDecorationColor() const
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, Color::TRANSPARENT);
    auto theme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(theme, Color::TRANSPARENT);
    if (GetPreviewTextStyle() == PreviewTextStyle::UNDERLINE) {
        return theme->GetPreviewUnderLineColor();
    }
    return Color::TRANSPARENT;
}

float RichEditorPattern::GetPreviewTextUnderlineWidth() const
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto theme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    return theme->GetPreviewUnderlineWidth().ConvertToPx();
}

bool RichEditorPattern::IsIMEOperation(OperationType operationType)
{
    return operationType == OperationType::IME;
}

void RichEditorPattern::InsertValue(const std::string& insertValue, bool isIME)
{
    InsertValue(UtfUtils::Str8ToStr16(insertValue), isIME);
}

void RichEditorPattern::InsertValue(const std::u16string& insertValue, bool isIME)
{
    InsertValueByOperationType(insertValue, isIME ? OperationType::IME : OperationType::DEFAULT);
}

void RichEditorPattern::InsertValueByOperationType(const std::u16string& insertValue, OperationType operationType)
{
    ProcessInsertValue(insertValue, operationType, true);
}

bool RichEditorPattern::ProcessTextTruncationOperation(std::u16string& text, bool shouldCommitInput)
{
    bool needTruncationInsertValue = shouldCommitInput || !previewTextRecord_.needReplacePreviewText;
    int32_t selectLength =
        textSelector_.SelectNothing() ? 0 : textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    int32_t previewContentLength = previewTextRecord_.previewContent.empty()
                                       ? previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start
                                       : static_cast<int32_t>(previewTextRecord_.previewContent.length());

    if (!needTruncationInsertValue || GetTextContentLength() - previewContentLength < maxLength_.value_or(INT_MAX)) {
        if (needTruncationInsertValue && text.length() != 1) {
            auto maxLength = maxLength_.value_or(INT_MAX) - GetTextContentLength() + previewContentLength;
            auto allowInsertLength =  CalculateTruncationLength(text, maxLength);
            if (allowInsertLength == 0) {
                TAG_LOGD(AceLogTag::ACE_RICH_TEXT,
                    "ProcessTextTruncation: No space to insert text. maxLength=%{public}d",
                    maxLength_.value_or(INT_MAX));
                return false;
            }
            text = text.substr(0, allowInsertLength);
            return true;
        }
        return true;
    }

    if (previewTextRecord_.needReplaceText) {
        text = text.substr(0, maxLength_.value_or(INT_MAX) + selectLength);
        return true;
    }
    if (!textSelector_.SelectNothing()) {
        auto allowInsertLength = CalculateTruncationLength(text, 0);
        if (allowInsertLength == 0) {
            TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "ProcessTextTruncation: No space to insert text. maxLength=%{public}d",
                maxLength_.value_or(INT_MAX));
            return false;
        }
        text = text.substr(0, allowInsertLength);
        return true;
    }
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "ProcessTextTruncation: maxLength=%{public}d", maxLength_.value_or(INT_MAX));
    IF_TRUE(IsPreviewTextInputting(), FinishTextPreviewInner());
    return false;
}

void RichEditorPattern::ProcessInsertValueMore(const std::u16string& text, OperationRecord record,
    OperationType operationType, RichEditorChangeValue changeValue, PreviewTextRecord preRecord)
{
    if (preRecord.needReplacePreviewText && !previewTextRecord_.needReplacePreviewText) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "previewText finished when ProcessInsertValue");
        NotifyImfFinishTextPreview();
        return;
    }
    ClearRedoOperationRecords();
    InsertValueOperation(text, &record, operationType);
    record.afterCaretPosition = caretPosition_;
    if (isDragSponsor_) {
        record.deleteCaretPostion = dragRange_.first;
    }
    AddOperationRecord(record);
    AfterContentChange(changeValue);
}

// operationType: when type is IME, it controls whether to perform ime callbacks
// shouldCommitInput: true means real input; false means preview input
void RichEditorPattern::ProcessInsertValue(const std::u16string& insertValue, OperationType operationType,
    bool shouldCommitInput)
{
    CONTENT_MODIFY_LOCK(this);
    auto text = insertValue;
    if (!ProcessTextTruncationOperation(text, shouldCommitInput)) {
        return;
    }
    bool isIME = IsIMEOperation(operationType);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "insertLen=%{public}zu, isIME=%{public}d, shouldCommitInput=%{public}d, isSpanString=%{public}d",
        insertValue.length(), isIME, shouldCommitInput, isSpanStringMode_);
    SEC_TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "insertValue=%{public}s",
        StringUtils::RestoreEscape(UtfUtils::Str16ToStr8(insertValue)).c_str());

    if (isIME && shouldCommitInput && (!isEditing_ || IsDragging())) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "NOT allow input, isEditing=%{public}d, isDragging=%{public}d",
            isEditing_, IsDragging());
        return;
    }
    if (isSpanStringMode_) {
        InsertValueInStyledString(text, shouldCommitInput);
        return;
    }
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_ + moveLength_;
    if (textSelector_.IsValid()) {
        record.beforeCaretPosition = textSelector_.GetTextStart();
    }
    record.addText = text;

    RichEditorChangeValue changeValue;
    PreviewTextRecord preRecord = previewTextRecord_;
    bool allowContentChange = BeforeChangeText(changeValue, record, RecordType::INSERT);
    if (shouldCommitInput && previewTextRecord_.IsValid()) {
        FinishTextPreviewInner();
    }
    bool allowImeInput = isIME ? BeforeIMEInsertValue(text) : true;
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "allowContentChange=%{public}d, allowImeInput=%{public}d, needReplacePreviewText=%{public}d",
        allowContentChange, allowImeInput, previewTextRecord_.needReplacePreviewText);
    bool allowPreviewText = previewTextRecord_.needReplacePreviewText;
    CHECK_NULL_VOID((allowContentChange && allowImeInput) || allowPreviewText);
    ProcessInsertValueMore(text, record, operationType, changeValue, preRecord);
}

void RichEditorPattern::InsertValueOperation(const std::u16string& insertValue, OperationRecord* const record,
    OperationType operationType)
{
    bool isSelector = textSelector_.IsValid();
    if (isSelector) {
        DeleteByRange(record, textSelector_.GetTextStart(), textSelector_.GetTextEnd());
        ResetSelection();
    } else if (previewTextRecord_.needReplacePreviewText || previewTextRecord_.needReplaceText) {
        DeleteByRange(record, previewTextRecord_.replacedRange.start, previewTextRecord_.replacedRange.end);
    }
    bool isSingleHandleMoving = selectOverlay_->IsSingleHandleMoving();
    CloseSelectOverlay();
    TextInsertValueInfo info;
    CalcInsertValueObj(info);
    IF_TRUE((!caretVisible_ || isSingleHandleMoving) && HasFocus(), StartTwinkling());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool isIME = IsIMEOperation(operationType);
    RefPtr<SpanNode> spanNode = DynamicCast<SpanNode>(host->GetChildAtIndex(info.GetSpanIndex()));
    RefPtr<SpanNode> spanNodeBefore = DynamicCast<SpanNode>(host->GetChildAtIndex(info.GetSpanIndex() - 1));
    RefPtr<SpanNode> targetSpanNode = spanNode;
    bool needCreateNewSpan = host->GetChildren().empty();
    if (info.GetOffsetInSpan() == 0) {
        bool spanNodeBeforeCanInsert = spanNodeBefore && spanNodeBefore->GetTag() == V2::SPAN_ETS_TAG;
        bool spanNodeCanInsert = spanNode && spanNode->GetTag() == V2::SPAN_ETS_TAG;
        bool insertToBeforeNode = spanNodeBeforeCanInsert && !spanNodeCanInsert;
        insertToBeforeNode |= spanNodeBeforeCanInsert && spanNodeCanInsert && !IsLineSeparatorInLast(spanNodeBefore);
        if (insertToBeforeNode) {
            auto spanItem = spanNodeBefore->GetSpanItem();
            info.SetSpanIndex(info.GetSpanIndex() - 1);
            info.SetOffsetInSpan(spanItem->position - spanItem->rangeStart);
            targetSpanNode = spanNodeBefore;
        }
        needCreateNewSpan |= !spanNodeBeforeCanInsert && !spanNodeCanInsert;
    }
    if (needCreateNewSpan) {
        CreateTextSpanNode(targetSpanNode, info, insertValue, isIME);
        return;
    }
    if (typingStyle_.has_value() && !HasSameTypingStyle(targetSpanNode)) {
        InsertDiffStyleValueInSpan(targetSpanNode, info, insertValue, isIME);
        return;
    }
    InsertValueToSpanNode(targetSpanNode, insertValue, info);
    AfterInsertValue(targetSpanNode, static_cast<int32_t>(insertValue.length()), false, isIME);
}

void RichEditorPattern::DeleteSelectOperation(OperationRecord* const record)
{
    std::u16string deleteText = DeleteForwardOperation(textSelector_.GetTextEnd() - textSelector_.GetTextStart());
    if (record && deleteText.length() != 0) {
        record->deleteText = deleteText;
    }
    CloseSelectOverlay();
    ResetSelection();
}

TextStyle RichEditorPattern::CreateTextStyleByTypingStyle()
{
    auto theme = GetTheme<RichEditorTheme>();
    auto ret = theme ? theme->GetTextStyle() : TextStyle();
    CHECK_NULL_RETURN(typingStyle_.has_value() && typingTextStyle_.has_value(), ret);
    const auto& updateSpanStyle = typingStyle_.value();
    const auto& textStyle = typingTextStyle_.value();
    IF_TRUE(updateSpanStyle.updateFontFeature, ret.SetFontFeatures(textStyle.GetFontFeatures()));
    IF_TRUE(updateSpanStyle.updateTextColor, ret.SetTextColor(textStyle.GetTextColor()));
    IF_TRUE(updateSpanStyle.updateLineHeight, ret.SetLineHeight(textStyle.GetLineHeight()));
    IF_TRUE(updateSpanStyle.updateLetterSpacing, ret.SetLetterSpacing(textStyle.GetLetterSpacing()));
    IF_TRUE(updateSpanStyle.updateFontSize, ret.SetFontSize(textStyle.GetFontSize()));
    IF_TRUE(updateSpanStyle.updateItalicFontStyle, ret.SetFontStyle(textStyle.GetFontStyle()));
    IF_TRUE(updateSpanStyle.updateFontWeight, ret.SetFontWeight(textStyle.GetFontWeight()));
    IF_TRUE(updateSpanStyle.updateFontFamily, ret.SetFontFamilies(textStyle.GetFontFamilies()));
    IF_TRUE(updateSpanStyle.updateTextShadows, ret.SetTextShadows(textStyle.GetTextShadows()));
    IF_TRUE(updateSpanStyle.updateHalfLeading, ret.SetHalfLeading(textStyle.GetHalfLeading()));
    IF_TRUE(updateSpanStyle.updateTextDecoration, ret.SetTextDecoration(textStyle.GetTextDecoration()));
    IF_TRUE(updateSpanStyle.updateTextDecorationColor, ret.SetTextDecorationColor(textStyle.GetTextDecorationColor()));
    IF_TRUE(updateSpanStyle.updateTextDecorationStyle, ret.SetTextDecorationStyle(textStyle.GetTextDecorationStyle()));
    IF_TRUE(updateSpanStyle.updateTextBackgroundStyle, ret.SetTextBackgroundStyle(textStyle.GetTextBackgroundStyle()));
    return ret;
}

void RichEditorPattern::InsertDiffStyleValueInSpan(
    RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info, const std::u16string& insertValue, bool isIME)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TextSpanOptions options;
    options.value = insertValue;
    options.offset = caretPosition_;
    options.style = CreateTextStyleByTypingStyle();
    options.useThemeFontColor = typingStyle_->useThemeFontColor;
    options.useThemeDecorationColor = typingStyle_->useThemeDecorationColor;
    auto newSpanIndex = AddTextSpanOperation(options, false, -1,  true, false);
    auto newSpanNode = DynamicCast<SpanNode>(host->GetChildAtIndex(newSpanIndex));
    CopyTextSpanLineStyle(spanNode, newSpanNode, true);
    AfterInsertValue(newSpanNode, static_cast<int32_t>(insertValue.length()), true, isIME);
}

bool RichEditorPattern::IsLineSeparatorInLast(RefPtr<SpanNode>& spanNode)
{
    std::u16string content = spanNode->GetSpanItem()->content;
    return !content.empty() && content.back() == u'\n';
}

void RichEditorPattern::InsertValueToSpanNode(
    RefPtr<SpanNode>& spanNode, const std::u16string& insertValue, const TextInsertValueInfo& info)
{
    auto spanItem = spanNode->GetSpanItem();
    CHECK_NULL_VOID(spanItem);
    auto textTemp = spanItem->content;
    auto textTempSize = static_cast<int32_t>(textTemp.size());
    if (textTempSize < info.GetOffsetInSpan() || info.GetOffsetInSpan() < 0) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "InsertValueToSpanNode error, spanSize=%{public}d, offsetInSpan=%{public}d",
            textTempSize, info.GetOffsetInSpan());
        RichEditorInfo errorInfo { RichEditorErrorType::INSERT_VALUE, textTempSize,
            static_cast<int32_t>(insertValue.length()), info.GetOffsetInSpan() };
        RichEditorErrorReport(errorInfo);
        return;
    }
    textTemp.insert(info.GetOffsetInSpan(), insertValue);
    spanNode->UpdateContent(textTemp);
    UpdateSpanPosition();
    SpanNodeFission(spanNode);
}

RefPtr<SpanNode> RichEditorPattern::InsertValueToBeforeSpan(
    RefPtr<SpanNode>& spanNodeBefore, const std::u16string& insertValue)
{
    auto spanItem = spanNodeBefore->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, spanNodeBefore);
    auto textTemp = spanItem->content;
    textTemp.append(insertValue);

    auto index = textTemp.find(LINE_SEPARATOR);
    if (index != std::u16string::npos) {
        spanNodeBefore->UpdateContent(textTemp.substr(0, index + 1));
        auto textAfter = textTemp.substr(index + 1);
        spanItem->position += static_cast<int32_t>(insertValue.length()) - static_cast<int32_t>(textAfter.length());
        if (!textAfter.empty()) {
            auto host = GetHost();
            CHECK_NULL_RETURN(spanItem, spanNodeBefore);
            TextInsertValueInfo infoAfter;
            infoAfter.SetSpanIndex(host->GetChildIndex(spanNodeBefore) + 1);
            infoAfter.SetOffsetInSpan(0);
            RefPtr<SpanNode> spanNodeAfter =
                SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
            spanNodeAfter->MountToParent(host, infoAfter.GetSpanIndex());
            spanNodeAfter->UpdateContent(textAfter);
            CopyTextSpanStyle(spanNodeBefore, spanNodeAfter);
            auto spanItemAfter = spanNodeAfter->GetSpanItem();
            spanItemAfter->position = static_cast<int32_t>(textTemp.length());
            spanItemAfter->useThemeFontColor = spanItem->useThemeFontColor;
            spanItemAfter->useThemeDecorationColor = spanItem->useThemeDecorationColor;
            AddSpanItem(spanItemAfter, host->GetChildIndex(spanNodeBefore) + 1);
            SpanNodeFission(spanNodeAfter);
            return spanNodeAfter;
        }
    } else {
        spanNodeBefore->UpdateContent(textTemp);
        spanItem->position += static_cast<int32_t>(insertValue.length());
    }
    return spanNodeBefore;
}

void RichEditorPattern::CreateTextSpanNode(
    RefPtr<SpanNode>& spanNode, const TextInsertValueInfo& info, const std::u16string& insertValue, bool isIME)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    spanNode->MountToParent(host, info.GetSpanIndex());
    auto spanItem = spanNode->GetSpanItem();
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        spanItem->useThemeFontColor = typingStyle_->useThemeFontColor;
        spanItem->useThemeDecorationColor = typingStyle_->useThemeDecorationColor;
        UpdateTextStyle(spanNode, typingStyle_.value(), typingTextStyle_.value());
        auto spanItem = spanNode->GetSpanItem();
        spanItem->SetTextStyle(typingTextStyle_);
    } else {
        spanNode->UpdateFontSize(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP));
        SetDefaultColor(spanNode);
    }
    AddSpanItem(spanItem, info.GetSpanIndex());
    spanNode->UpdateContent(insertValue);
    UpdateSpanPosition();
    SpanNodeFission(spanNode);
    AfterInsertValue(spanNode, static_cast<int32_t>(insertValue.length()), true, isIME);
}

void RichEditorPattern::SetDefaultColor(RefPtr<SpanNode>& spanNode)
{
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    Color textColor = richEditorTheme->GetTextStyle().GetTextColor();
    spanNode->UpdateTextColorWithoutCheck(textColor);
    spanNode->UpdateTextDecorationColorWithoutCheck(textColor);
    if (auto& spanItem = spanNode->GetSpanItem(); spanItem && spanItem->urlOnRelease) {
        spanNode->UpdateTextColor(GetUrlSpanColor());
    }
}

bool RichEditorPattern::BeforeIMEInsertValue(const std::u16string& insertValue)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    RichEditorInsertValue insertValueInfo;
    insertValueInfo.SetInsertOffset(caretPosition_);
    if (!previewTextRecord_.newPreviewContent.empty()) {
        insertValueInfo.SetPreviewText(previewTextRecord_.newPreviewContent);
    } else {
        insertValueInfo.SetInsertValue(insertValue);
    }
    return eventHub->FireAboutToIMEInput(insertValueInfo);
}

void RichEditorPattern::AfterInsertValue(
    const RefPtr<SpanNode>& spanNode, int32_t insertValueLength, bool isCreate, bool isIME)
{
    isTextChange_ = true;
    moveDirection_ = MoveDirection::FORWARD;
    moveLength_ += insertValueLength;
    IF_TRUE(!previewTextRecord_.needUpdateCaret, moveLength_ = 0);
    UpdateSpanPosition();
    if (isIME || aiWriteAdapter_->GetAIWrite()) {
        AfterIMEInsertValue(spanNode, insertValueLength, isCreate);
        return;
    }
    MoveCaretAfterTextChange();
}

bool RichEditorPattern::AfterIMEInsertValue(const RefPtr<SpanNode>& spanNode, int32_t insertValueLength, bool isCreate)
{
    ACE_SCOPED_TRACE("RichEditorAfterIMEInsertValue");
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);

    RichEditorAbstractSpanResult retInfo;
    retInfo.SetSpanIndex(host->GetChildIndex(spanNode));
    retInfo.SetEraseLength(insertValueLength);
    auto spanItem = spanNode->GetSpanItem();
    if (!previewTextRecord_.newPreviewContent.empty()) {
        retInfo.SetPreviewText(previewTextRecord_.newPreviewContent);
    } else {
        retInfo.SetValue(spanItem->content);
    }
    auto contentLength = static_cast<int32_t>(spanItem->content.length());
    retInfo.SetSpanRangeStart(spanItem->position - contentLength);
    retInfo.SetSpanRangeEnd(spanItem->position);
    retInfo.SetOffsetInSpan(caretPosition_ - retInfo.GetSpanRangeStart());
    retInfo.SetFontColor(spanNode->GetTextColorValue(Color::BLACK).ColorToString());
    retInfo.SetFontSize(spanNode->GetFontSizeValue(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP)).ConvertToVp());
    retInfo.SetFontStyle(spanNode->GetItalicFontStyleValue(OHOS::Ace::FontStyle::NORMAL));
    retInfo.SetFontWeight(static_cast<int32_t>(spanNode->GetFontWeightValue(FontWeight::NORMAL)));
    retInfo.SetTextStyle(GetTextStyleObject(spanNode));
    retInfo.SetUrlAddress(spanItem->urlAddress);
    std::string fontFamilyValue;
    auto fontFamily = spanNode->GetFontFamilyValue({ "HarmonyOS Sans" });
    for (const auto& str : fontFamily) {
        fontFamilyValue += str;
    }
    retInfo.SetFontFamily(fontFamilyValue);
    retInfo.SetTextDecoration(spanNode->GetTextDecorationValue(TextDecoration::NONE));
    retInfo.SetTextDecorationStyle(spanNode->GetTextDecorationStyleValue(TextDecorationStyle::SOLID));
    retInfo.SetFontFeature(spanNode->GetFontFeatureValue(ParseFontFeatureSettings("\"pnum\" 1")));
    retInfo.SetColor(spanNode->GetTextDecorationColorValue(Color::BLACK).ColorToString());
    TextRange onDidIMEInputRange{ caretPosition_, caretPosition_ + insertValueLength };
    MoveCaretAfterTextChange();
    eventHub->FireOnIMEInputComplete(retInfo);
    OnReportRichEditorEvent("onIMEInputComplete");
    eventHub->FireOnDidIMEInput(onDidIMEInputRange);
    return true;
}

bool RichEditorPattern::DoDeleteActions(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto allowDelete = eventHub->FireAboutToDelete(info);
    info.ResetRichEditorDeleteSpans();
    CalcDeleteValueObj(currentPosition, length, info);
    bool doDelete = allowDelete || IsPreviewTextInputting();
    if (doDelete) {
        bool isSingleHandleMoving = selectOverlay_->IsSingleHandleMoving();
        CloseSelectOverlay();
        ResetSelection();
        DeleteByDeleteValueInfo(info);
        IF_TRUE((!caretVisible_ || isSingleHandleMoving) && HasFocus(), StartTwinkling());
        eventHub->FireOnDeleteComplete();
        OnReportRichEditorEvent("OnDeleteComplete");
    }
    return doDelete;
}

std::pair<bool, bool> RichEditorPattern::IsEmojiOnCaretPosition(int32_t& emojiLength, bool isBackward, int32_t length)
{
    bool isEmojiOnCaretBackward = false;
    bool isEmojiOnCaretForward = false;
    std::u16string u16;
    GetContentBySpans(u16);
    auto caretPos = std::clamp(caretPosition_, 0, static_cast<int32_t>(u16.length()));
    emojiLength = TextEmojiProcessor::Delete(caretPos, length, u16, isBackward);
    if (emojiLength > 0) {
        if (isBackward) {
            isEmojiOnCaretBackward = true;
        } else {
            isEmojiOnCaretForward = true;
        }
    }
    return std::make_pair(isEmojiOnCaretBackward, isEmojiOnCaretForward);
}

void RichEditorPattern::HandleOnDelete(bool backward)
{
    if (backward) {
#if defined(PREVIEW)
        DeleteForward(1);
#else
        DeleteBackward(1);
#endif
    } else {
#if defined(PREVIEW)
        DeleteBackward(1);
#else
        DeleteForward(1);
#endif
    }
}

int32_t RichEditorPattern::CalculateDeleteLength(int32_t length, bool isBackward)
{
    // handle selector
    if (!textSelector_.SelectNothing()) {
        lastCaretPosition_ = caretPosition_;
        caretPosition_ = isBackward ? textSelector_.GetTextEnd() : textSelector_.GetTextStart();
        return textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    }

    // handle symbol, assume caret is not within symbol
    auto iter = std::find_if(spans_.begin(), spans_.end(), [index = caretPosition_, isBackward]
    (const RefPtr<SpanItem>& spanItem) {
        return isBackward
        ? (spanItem->rangeStart < index && index <= spanItem->position)
        : (spanItem->rangeStart <= index && index < spanItem->position);
    });
    CHECK_NULL_RETURN(iter == spans_.end() || !(*iter) || (*iter)->unicode == 0, SYMBOL_SPAN_LENGTH);

    // handle emoji
    int32_t emojiLength = 0;
    auto [isEmojiOnCaretBackward, isEmojiOnCaretForward] = IsEmojiOnCaretPosition(emojiLength, isBackward, length);
    if ((isBackward && isEmojiOnCaretBackward) || (!isBackward && isEmojiOnCaretForward)) {
        return emojiLength;
    }

    return length;
}

void RichEditorPattern::DeleteBackward(int32_t oriLength)
{
    int32_t length = isAPI14Plus ? std::clamp(oriLength, 0, caretPosition_) : oriLength;
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "oriLength=%{public}d, length=%{public}d, isDragging=%{public}d",
        oriLength, length, IsDragging());
    CHECK_NULL_VOID(!IsDragging());
    if (IsPreviewTextInputting()) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "do not handle DeleteBackward on previewTextInputting");
        return;
    }
    if (isSpanStringMode_) {
        DeleteBackwardInStyledString(length);
        return;
    }
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_;
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, record, RecordType::DEL_BACKWARD, length));
    std::u16string deleteText = DeleteBackwardOperation(length);
    if (deleteText.length() != 0) {
        ClearRedoOperationRecords();
        record.deleteText = deleteText;
        record.afterCaretPosition = caretPosition_;
        AddOperationRecord(record);
        AfterContentChange(changeValue);
    }
}

std::u16string RichEditorPattern::DeleteBackwardOperation(int32_t length)
{
    length = CalculateDeleteLength(length, true);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "delete length=%{public}d", length);
    std::u16string textContent;
    GetContentBySpans(textContent);

    if (static_cast<int32_t>(textContent.length()) != GetTextContentLength()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "textContent length mismatch, %{public}d vs. %{public}d",
            static_cast<int32_t>(textContent.length()), GetTextContentLength());
    }
    auto start = std::clamp(caretPosition_ - length, 0, static_cast<int32_t>(textContent.length()));
    std::u16string deleteText =
        textContent.substr(static_cast<uint32_t>(start), static_cast<uint32_t>(caretPosition_ - start));
    RichEditorDeleteValue info;
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::BACKWARD);
    if (caretPosition_ == 0) {
        info.SetLength(0);
        DoDeleteActions(0, 0, info);
        return deleteText;
    }
    info.SetOffset(caretPosition_ - length);
    info.SetLength(length);
    int32_t currentPosition = std::clamp((caretPosition_ - length), 0, static_cast<int32_t>(GetTextContentLength()));
    if (!spans_.empty()) {
        CalcDeleteValueObj(currentPosition, length, info);
        bool doDelete = DoDeleteActions(currentPosition, length, info);
        if (!doDelete) {
            return u"";
        }
    }
    auto host = GetHost();
    if (host && host->GetChildren().empty()) {
        textForDisplay_.clear();
    }
    RequestKeyboardToEdit();
    return deleteText;
}

void RichEditorPattern::DeleteForward(int32_t oriLength)
{
    int32_t length = isAPI14Plus ? std::clamp(oriLength, 0, GetTextContentLength() - caretPosition_) : oriLength;
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "oriLength=%{public}d, length=%{public}d, isDragging=%{public}d",
        oriLength, length, IsDragging());
    CHECK_NULL_VOID(!IsDragging());
    if (isSpanStringMode_) {
        DeleteForwardInStyledString(length);
        return;
    }
    if (IsPreviewTextInputting()) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "do not handle DeleteForward in previewTextInputting");
        return;
    }
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_;
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, record, RecordType::DEL_FORWARD, length));
    std::u16string deleteText = DeleteForwardOperation(length);
    if (deleteText.length() != 0) {
        ClearRedoOperationRecords();
        record.deleteText = deleteText;
        record.afterCaretPosition = caretPosition_;
        AddOperationRecord(record);
        AfterContentChange(changeValue);
    }
}

std::u16string RichEditorPattern::DeleteForwardOperation(int32_t length)
{
    length = CalculateDeleteLength(length, false);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "delete length=%{public}d", length);
    std::u16string textContent;
    GetContentBySpans(textContent);
    if (static_cast<int32_t>(textContent.length()) != GetTextContentLength()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "textContent length mismatch, %{public}d vs. %{public}d",
            static_cast<int32_t>(textContent.length()), GetTextContentLength());
    }
    auto end = std::clamp(caretPosition_ + length, 0, static_cast<int32_t>(textContent.length()));
    std::u16string deleteText = textContent.substr(
        static_cast<uint32_t>(std::clamp(caretPosition_, 0, static_cast<int32_t>(textContent.length()))),
        static_cast<uint32_t>(end - caretPosition_));
    RichEditorDeleteValue info;
    info.SetOffset(caretPosition_);
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::FORWARD);
    int32_t currentPosition = caretPosition_;
    if (currentPosition == GetTextContentLength()) {
        info.SetLength(0);
        DoDeleteActions(currentPosition, 0, info);
        return deleteText;
    }
    info.SetLength(length);
    if (!spans_.empty()) {
        CalcDeleteValueObj(currentPosition, length, info);
        bool doDelete = DoDeleteActions(currentPosition, length, info);
        if (!doDelete) {
            return u"";
        }
    }
    return deleteText;
}

void RichEditorPattern::DeleteContent(int32_t length)
{
    length = CalculateDeleteLength(length, true);
    std::u16string textContent;
    GetContentBySpans(textContent);

    auto start = std::clamp(GetTextContentLength() - length, 0, static_cast<int32_t>(textContent.length()));
    std::u16string deleteText =
        textContent.substr(static_cast<uint32_t>(start), static_cast<uint32_t>(GetTextContentLength() - start));
    RichEditorDeleteValue info;
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::BACKWARD);
    if (GetTextContentLength() == 0) {
        info.SetLength(0);
        DoDeleteActions(0, 0, info);
        return;
    }
    info.SetOffset(GetTextContentLength() - length);
    info.SetLength(length);
    int32_t currentPosition = std::clamp((GetTextContentLength() - length), 0, static_cast<int32_t>(GetTextContentLength()));
    if (!spans_.empty()) {
        CalcDeleteValueObj(currentPosition, length, info);
        bool doDelete = DoDeleteActions(currentPosition, length, info);
        if (!doDelete) {
            return;
        }
    }
    auto host = GetHost();
    if (host && host->GetChildren().empty()) {
        textForDisplay_.clear();
    }
    RequestKeyboardToEdit();
}

void RichEditorPattern::DeleteToMaxLength(std::optional<int32_t> length)
{
    if (length.value_or(INT_MAX) >= GetTextContentLength()) {
        return;
    }
    int32_t textContentLength = GetTextContentLength();
    if (isSpanStringMode_) {
        DeleteValueInStyledString(length.value_or(INT_MAX), GetTextContentLength() - length.value_or(INT_MAX));
    } else {
        while (textContentLength > length.value_or(INT_MAX)) {
            textContentLength -= CalculateDeleteLength(CUSTOM_CONTENT_LENGTH, true);
            DeleteContent(CUSTOM_CONTENT_LENGTH);
        }
    }
}

bool RichEditorPattern::OnBackPressed()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RichEditor %{public}d receives back press event, isStopBackPress=%{public}d",
        tmpHost->GetId(), isStopBackPress_);
    if (SelectOverlayIsOn()) {
        CloseSelectOverlay();
        textSelector_.Update(textSelector_.destinationOffset);
        StartTwinkling();
        return isStopBackPress_;
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (!imeShown_ && !isCustomKeyboardAttached_) {
#else
    if (!isCustomKeyboardAttached_) {
#endif
        return false;
    }
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ResetSelection();
    CloseKeyboard(false);
    FocusHub::LostFocusToViewRoot();
#if defined(ANDROID_PLATFORM)
    return false;
#else
    return isStopBackPress_;
#endif
}

void RichEditorPattern::SetInputMethodStatus(bool keyboardShown)
{
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    imeShown_ = keyboardShown;
#endif
}

bool RichEditorPattern::BeforeStatusCursorMove(bool isLeft)
{
    CHECK_NULL_RETURN(textSelector_.IsValid(), true);
    CHECK_NULL_RETURN(!selectOverlay_->IsSingleHandleShow(), true);
    SetCaretPosition(isLeft ? textSelector_.GetTextStart() : textSelector_.GetTextEnd());
    MoveCaretToContentRect();
    StartTwinkling();
    CloseSelectOverlay();
    ResetSelection();
    return false;
}

bool RichEditorPattern::CursorMoveLeft()
{
    CHECK_NULL_RETURN(BeforeStatusCursorMove(true), false);
    CloseSelectOverlay();
    ResetSelection();
    int32_t emojiLength = 0;
    int32_t caretPosition = caretPosition_;
    constexpr int32_t DELETE_COUNT = 1;
    auto [isEmojiOnCaretBackward, isEmojiOnCaretForward] = IsEmojiOnCaretPosition(emojiLength, true, DELETE_COUNT);
    if (isEmojiOnCaretBackward) {
        caretPosition = std::clamp((caretPosition_ - emojiLength), 0, static_cast<int32_t>(GetTextContentLength()));
    } else {
        caretPosition = std::clamp((caretPosition_ - 1), 0, static_cast<int32_t>(GetTextContentLength()));
    }
    AdjustSelectorForSymbol(caretPosition, HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
    if (caretPosition_ == caretPosition) {
        return false;
    }
    SetCaretPosition(caretPosition);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveRight()
{
    CHECK_NULL_RETURN(BeforeStatusCursorMove(false), false);
    CloseSelectOverlay();
    ResetSelection();
    int32_t emojiLength = 0;
    int32_t caretPosition = caretPosition_;
    constexpr int32_t DELETE_COUNT = 1;
    auto [isEmojiOnCaretBackward, isEmojiOnCaretForward] = IsEmojiOnCaretPosition(emojiLength, false, DELETE_COUNT);
    if (isEmojiOnCaretForward) {
        caretPosition = std::clamp((caretPosition_ + emojiLength), 0, static_cast<int32_t>(GetTextContentLength()));
    } else {
        caretPosition = std::clamp((caretPosition_ + 1), 0, static_cast<int32_t>(GetTextContentLength()));
    }
    AdjustSelectorForSymbol(caretPosition, HandleType::SECOND, SelectorAdjustPolicy::INCLUDE);
    if (caretPosition_ == caretPosition) {
        return false;
    }
    SetCaretPosition(caretPosition);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveUp()
{
    CloseSelectOverlay();
    ResetSelection();
    float caretHeight = 0.0f;
    float leadingMarginOffset = 0.0f;
    CaretOffsetInfo caretInfo;
    if (static_cast<int32_t>(GetTextContentLength()) > 1) {
        caretInfo = GetCaretOffsetInfoByPosition();
        int32_t caretPosition = CalcMoveUpPos(leadingMarginOffset);
        CHECK_NULL_RETURN(overlayMod_, false);
        auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
        auto currentCaretOffsetOverlay = overlayMod->GetCaretOffset();
        auto caretOffsetWidth = overlayMod->GetCaretWidth();
        auto rectLineInfo = CalcLineInfoByPosition();
        caretPosition = std::clamp(caretPosition, 0, static_cast<int32_t>(GetTextContentLength()));
        if (caretPosition_ == caretPosition) {
            caretPosition = 0;
        }
        // at line middle or line end
        bool cursorNotAtLineStart =
            NearEqual(currentCaretOffsetOverlay.GetX(), caretInfo.caretOffsetUp.GetX(), caretOffsetWidth);
        bool isEnter = NearZero(currentCaretOffsetOverlay.GetX() - richTextRect_.GetX(), rectLineInfo.GetX());
        SetCaretPosition(caretPosition);
        MoveCaretToContentRect();
        if (cursorNotAtLineStart && !isEnter) {
            OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight, false, false);
            SetLastClickOffset(caretOffset);
            caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
        }
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveDown()
{
    CloseSelectOverlay();
    ResetSelection();
    if (static_cast<int32_t>(GetTextContentLength()) > 1) {
        float caretHeight = 0.0f;
        float leadingMarginOffset = 0.0f;
        float caretHeightEnd = 0.0f;
        CaretOffsetInfo caretInfo;
        int32_t caretPositionEnd;
        caretInfo = GetCaretOffsetInfoByPosition();
        caretPositionEnd = CalcMoveDownPos(leadingMarginOffset);
        CHECK_NULL_RETURN(overlayMod_, false);
        auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
        auto caretOffsetOverlay = overlayMod->GetCaretOffset();
        auto caretOffsetWidth = overlayMod->GetCaretWidth();
        bool cursorNotAtLineStart =
            NearEqual(caretOffsetOverlay.GetX(), caretInfo.caretOffsetUp.GetX(), caretOffsetWidth);
        bool isEnter = NearZero(caretInfo.caretOffsetUp.GetX() - richTextRect_.GetX(), leadingMarginOffset);
        caretPositionEnd = std::clamp(caretPositionEnd, 0, static_cast<int32_t>(GetTextContentLength()));
        auto currentLineInfo = CalcLineInfoByPosition();
        if (caretPositionEnd <= caretPosition_) {
            OffsetF caretOffsetEnd = CalcCursorOffsetByPosition(GetTextContentLength(), caretHeightEnd);
            if (NearEqual(caretOffsetEnd.GetY() - GetTextRect().GetY(), currentLineInfo.GetY(), 0.5f)) {
                caretPositionEnd = GetTextContentLength();
            } else {
                caretPositionEnd += 1;
            }
        }
        SetCaretPosition(caretPositionEnd);
        if (cursorNotAtLineStart && caretPosition_ != 0 && !isEnter) {
            OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight, false, false);
            SetLastClickOffset(caretOffset);
            caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
        }
        MoveCaretToContentRect();
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void RichEditorPattern::CursorMoveToNextWord(CaretMoveIntent direction)
{
    CHECK_NULL_VOID(direction == CaretMoveIntent::LeftWord || direction == CaretMoveIntent::RightWord);
    bool isDirectionLeft = direction == CaretMoveIntent::LeftWord;
    auto index = caretPosition_;
    if (!textSelector_.SelectNothing()) {
        index = isDirectionLeft ? textSelector_.GetTextStart() + 1 : textSelector_.GetTextEnd() - 1;
    }
    auto newPos = isDirectionLeft ? GetLeftWordIndex(index) : GetRightWordIndex(index);
    CloseSelectOverlay();
    ResetSelection();
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    IF_TRUE(isEditing_, StartTwinkling());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

int32_t RichEditorPattern::GetLeftWordIndex(int32_t index)
{
    AdjustIndexSkipSpace(index, MoveDirection::BACKWARD);
    int32_t newPos = std::max(0, index - 1);
    AdjustWordSelection(newPos, index);
    AdjustSelector(newPos, HandleType::FIRST);
    return newPos;
}

int32_t RichEditorPattern::GetRightWordIndex(int32_t index)
{
    int32_t newPos = std::min(index + 1, GetTextContentLength());
    AdjustWordSelection(index, newPos);
    AdjustSelector(newPos, HandleType::SECOND);
    AdjustIndexSkipSpace(newPos, MoveDirection::FORWARD);
    return newPos;
}

bool RichEditorPattern::CursorMoveToParagraphBegin()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetParagraphBeginPosition(caretPosition_);
    if (newPos == caretPosition_ && caretPosition_ > 0) {
        newPos = GetParagraphBeginPosition(caretPosition_ - 1);
    }
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveToParagraphEnd()
{
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetParagraphEndPosition(caretPosition_);
    if (newPos == caretPosition_ && caretPosition_ < static_cast<int32_t>(GetTextContentLength())) {
        newPos = GetParagraphEndPosition(caretPosition_ + 1);
    }
    if (newPos == caretPosition_) {
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveHome()
{
    CloseSelectOverlay();
    ResetSelection();
    if (0 == caretPosition_) {
        return false;
    }
    SetCaretPosition(0);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveEnd()
{
    int32_t currentPositionIndex = 0;
    if (textSelector_.SelectNothing()) {
        currentPositionIndex = caretPosition_;
    } else {
        currentPositionIndex = textSelector_.GetTextEnd();
    }
    CloseSelectOverlay();
    ResetSelection();
    auto newPos = GetTextContentLength();
    if (newPos == currentPositionIndex) {
        StartTwinkling();
        return false;
    }
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

int32_t RichEditorPattern::GetLeftWordPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    bool jumpSpace = true;
    for (auto iter = spans_.rbegin(); iter != spans_.rend(); iter++) {
        auto span = *iter;
        auto content = span->content;
        if (caretPosition <= span->position - static_cast<int32_t>(content.length())) {
            continue;
        }
        int32_t position = span->position;
        for (auto iterContent = content.rbegin(); iterContent != content.rend(); iterContent++) {
            if (position-- > caretPosition) {
                continue;
            }
            if (*iterContent != u' ' || span->placeholderIndex >= 0) {
                jumpSpace = false;
            }
            if (position + 1 == caretPosition) {
                if (!(StringUtils::IsLetterOrNumberForWchar(*iterContent) ||
                        (*iterContent == u' ' && span->placeholderIndex < 0))) {
                    return std::clamp(caretPosition - 1, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            if (!jumpSpace) {
                if (!StringUtils::IsLetterOrNumberForWchar(*iterContent)) {
                    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            } else {
                if (*iterContent == u' ' && span->placeholderIndex >= 0) {
                    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            offset++;
        }
    }
    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

int32_t RichEditorPattern::GetRightWordPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    bool jumpSpace = false;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        auto span = *iter;
        auto content = span->content;
        if (caretPosition > span->position) {
            continue;
        }
        int32_t position = span->position - static_cast<int32_t>(content.length());
        for (auto iterContent = content.cbegin(); iterContent != content.cend(); iterContent++) {
            if (position++ < caretPosition) {
                continue;
            }
            if (*iterContent == u' ' && span->placeholderIndex < 0) {
                jumpSpace = true;
                offset++;
                continue;
            }
            if (position - 1 == caretPosition) {
                if (!StringUtils::IsLetterOrNumberForWchar(*iterContent)) {
                    return std::clamp(caretPosition + 1, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            if (jumpSpace) {
                if (*iterContent != u' ' || span->placeholderIndex >= 0) {
                    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            } else {
                if (!(StringUtils::IsLetterOrNumberForWchar(*iterContent) ||
                        (*iterContent == u' ' && span->placeholderIndex < 0))) {
                    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
                }
            }
            offset++;
        }
    }
    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

int32_t RichEditorPattern::GetParagraphBeginPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    for (auto iter = spans_.rbegin(); iter != spans_.rend(); iter++) {
        auto span = *iter;
        auto content = span->content;
        if (caretPosition <= span->position - static_cast<int32_t>(content.length())) {
            continue;
        }
        int32_t position = span->position;
        for (auto iterContent = content.rbegin(); iterContent != content.rend(); iterContent++) {
            if (position-- > caretPosition) {
                continue;
            }
            if (*iterContent == u'\n') {
                return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
            }
            offset++;
        }
    }
    return std::clamp(caretPosition - offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

int32_t RichEditorPattern::GetParagraphEndPosition(int32_t caretPosition)
{
    int32_t offset = 0;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        auto span = *iter;
        auto content = span->content;
        if (caretPosition > span->position) {
            continue;
        }
        int32_t position = span->position - static_cast<int32_t>(content.length());
        for (auto iterContent = content.cbegin(); iterContent != content.cend(); iterContent++) {
            if (position++ < caretPosition) {
                continue;
            }
            if (*iterContent == u'\n') {
                return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
            }
            offset++;
        }
    }
    return std::clamp(caretPosition + offset, 0, static_cast<int32_t>(GetTextContentLength()));
}

void RichEditorPattern::HandleOnSelectAll()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnSelectAll");
    CloseSelectOverlay();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    textResponseType_.reset();
    int32_t newPos = static_cast<int32_t>(GetTextContentLength());
    textSelector_.Update(0, newPos);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    IF_TRUE(IsSelected(), StopTwinkling());
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

int32_t RichEditorPattern::CaretPositionSelectEmoji(CaretMoveIntent direction)
{
    int32_t newPos = caretPosition_;
    int32_t emojiLength = 0;
    constexpr int32_t DELETE_COUNT = 1;
    if (direction == CaretMoveIntent::Left) {
        auto [isEmojiOnCaretBackward, isEmojiOnCaretForward] = IsEmojiOnCaretPosition(emojiLength, true, DELETE_COUNT);
        if (isEmojiOnCaretBackward) {
            newPos = caretPosition_ - emojiLength;
        } else {
            newPos = caretPosition_ - 1;
        }
        AdjustSelectorForSymbol(newPos, HandleType::FIRST, SelectorAdjustPolicy::INCLUDE);
        return newPos;
    }
    auto [isEmojiOnCaretBackward, isEmojiOnCaretForward] = IsEmojiOnCaretPosition(emojiLength, false, DELETE_COUNT);
    if (direction == CaretMoveIntent::Right) {
        if (isEmojiOnCaretForward) {
            newPos = caretPosition_ + emojiLength;
        } else {
            newPos = caretPosition_ + 1;
        }
        AdjustSelectorForSymbol(newPos, HandleType::SECOND, SelectorAdjustPolicy::INCLUDE);
    }
    return newPos;
}

void RichEditorPattern::HandleSelect(CaretMoveIntent direction)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "direction=%{public}d", direction);
    CloseSelectOverlay();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    int32_t newPos, fixedPos = caretPosition_;
    if (IsSelected()) {
        fixedPos = (caretPosition_ == textSelector_.GetTextStart() ? textSelector_.GetTextEnd()
                                                                   : textSelector_.GetTextStart());
    }
    newPos = HandleSelectWrapper(direction, fixedPos);
    if (newPos == -1) {
        return;
    }
    newPos = std::clamp(newPos, 0, static_cast<int32_t>(GetTextContentLength()));
    if (newPos == caretPosition_) {
        return;
    }
    UpdateSelector(fixedPos, newPos);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    SetCaretPosition(newPos);
    MoveCaretToContentRect();
    if (textSelector_.SelectNothing()) {
        StartTwinkling();
    } else {
        StopTwinkling();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::ClearOperationRecords()
{
    undoManager_->ClearUndoRedoRecords();
    ClearRedoOperationRecords();
    if (operationRecords_.empty()) {
        return;
    }
    operationRecords_.clear();
}

void RichEditorPattern::ClearRedoOperationRecords()
{
    if (redoOperationRecords_.empty()) {
        return;
    }
    redoOperationRecords_.clear();
}

void RichEditorPattern::AddOperationRecord(const OperationRecord& record)
{
    if (operationRecords_.size() >= RECORD_MAX_LENGTH) {
        // case of max length is 0
        if (operationRecords_.empty()) {
            return;
        }
        operationRecords_.erase(operationRecords_.begin());
    }
    operationRecords_.emplace_back(record);
}

void RichEditorPattern::UpdateShiftFlag(const KeyEvent& keyEvent)
{
    bool hasKeyShift = keyEvent.HasKey(KeyCode::KEY_SHIFT_LEFT) || keyEvent.HasKey(KeyCode::KEY_SHIFT_RIGHT);
    auto action = keyEvent.action;
    bool isShiftPressed = hasKeyShift && (action == KeyAction::DOWN || action == KeyAction::UP);
    if (isShiftPressed != shiftFlag_) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "UpdateShiftFlag:%{public}d by action:%{public}d", isShiftPressed, action);
        shiftFlag_ = isShiftPressed;
    }
}

bool RichEditorPattern::HandleOnEscape()
{
    CloseSelectOverlay();
    return false;
}

void RichEditorPattern::HandleOnUndoAction()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnUndoAction");
    if (isSpanStringMode_) {
        undoManager_->UndoByRecords();
        return;
    }
    if (operationRecords_.empty()) {
        return;
    }
    auto value = operationRecords_.back();
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, value, RecordType::UNDO));
    operationRecords_.pop_back();
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH && !(redoOperationRecords_.empty())) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    redoOperationRecords_.push_back(value);
    CloseSelectOverlay();
    ResetSelection();
    if (value.addText.has_value() && value.deleteCaretPostion != -1) {
        UndoDrag(value);
        AfterContentChange(changeValue);
        return;
    }
    if (value.addText.has_value() && value.deleteText.has_value()) {
        SetCaretPosition(value.afterCaretPosition);
        DeleteBackwardOperation(TextEmojiProcessor::GetCharacterNum(value.addText.value_or(u"")));
        InsertValueOperation(value.deleteText.value_or(u""));
        AfterContentChange(changeValue);
        return;
    }
    if (value.addText.has_value()) {
        SetCaretPosition(value.afterCaretPosition);
        DeleteBackwardOperation(TextEmojiProcessor::GetCharacterNum(value.addText.value_or(u"")));
    }
    if (value.deleteText.has_value()) {
        SetCaretPosition(value.afterCaretPosition);
        InsertValueOperation(value.deleteText.value_or(u""));
    }
    AfterContentChange(changeValue);
}

void RichEditorPattern::HandleOnRedoAction()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnRedoAction");
    if (isSpanStringMode_) {
        undoManager_->RedoByRecords();
        return;
    }
    if (redoOperationRecords_.empty()) {
        return;
    }
    auto value = redoOperationRecords_.back();
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, value, RecordType::REDO));
    redoOperationRecords_.pop_back();
    if (value.addText.has_value() && value.deleteCaretPostion != -1) {
        RedoDrag(value);
        AfterContentChange(changeValue);
        return;
    }
    if (value.addText.has_value() && value.deleteText.has_value()) {
        SetCaretPosition(value.beforeCaretPosition);
        DeleteForwardOperation(value.deleteText.value_or(u"").length());
        InsertValueOperation(value.addText.value_or(u""));
        operationRecords_.push_back(value);
        AfterContentChange(changeValue);
        return;
    }
    if (value.deleteText.has_value()) {
        SetCaretPosition(value.beforeCaretPosition);
        if (value.beforeCaretPosition != value.afterCaretPosition) {
            DeleteBackwardOperation(value.deleteText.value_or(u"").length());
        } else {
            DeleteForwardOperation(value.deleteText.value_or(u"").length());
        }
    }
    if (value.addText.has_value()) {
        SetCaretPosition(value.beforeCaretPosition);
        InsertValueOperation(value.addText.value_or(u""));
    }
    operationRecords_.push_back(value);
    AfterContentChange(changeValue);
}

void RichEditorPattern::CalcInsertValueObj(TextInsertValueInfo& info)
{
    if (spans_.empty()) {
        info.SetSpanIndex(0);
        info.SetOffsetInSpan(0);
        return;
    }
    auto it = std::find_if(
        spans_.begin(), spans_.end(), [caretPosition = caretPosition_ + moveLength_](const RefPtr<SpanItem>& spanItem) {
            if (spanItem->content.empty()) {
                return spanItem->position == caretPosition;
            }
            return spanItem->rangeStart <= caretPosition && caretPosition < spanItem->position;
        });
    if (it != spans_.end() && (*it)->unicode != 0 && (*it)->position - caretPosition_ + moveLength_ == 1) {
        it++;
        moveLength_++;
    }
    info.SetSpanIndex(std::distance(spans_.begin(), it));
    if (it == spans_.end()) {
        info.SetOffsetInSpan(0);
        return;
    }
    info.SetOffsetInSpan(
        caretPosition_ + moveLength_ - ((*it)->position - (*it)->content.length()));
}

void RichEditorPattern::CalcDeleteValueObj(int32_t currentPosition, int32_t length, RichEditorDeleteValue& info)
{
    auto it =
        std::find_if(spans_.begin(), spans_.end(), [caretPosition = currentPosition](const RefPtr<SpanItem>& spanItem) {
            return (spanItem->position - static_cast<int32_t>(spanItem->content.length()) <= caretPosition) &&
                   (caretPosition < spanItem->position);
        });
    while (it != spans_.end() && length > 0) {
        if ((*it)->placeholderIndex >= 0 || (*it)->unicode != 0) {
            RichEditorAbstractSpanResult spanResult;
            spanResult.SetSpanIndex(std::distance(spans_.begin(), it));
            int32_t eraseLength = 0;
            if ((*it)->unicode != 0) {
                eraseLength = DeleteValueSetSymbolSpan(*it, spanResult);
            } else if (AceType::InstanceOf<ImageSpanItem>(*it)) {
                eraseLength = DeleteValueSetImageSpan(*it, spanResult);
            } else {
                eraseLength = DeleteValueSetBuilderSpan(*it, spanResult);
            }
            currentPosition += eraseLength;
            length -= eraseLength;
            info.SetRichEditorDeleteSpans(spanResult);
        } else {
            RichEditorAbstractSpanResult spanResult;
            spanResult.SetSpanIndex(std::distance(spans_.begin(), it));
            auto eraseLength = DeleteValueSetTextSpan(*it, currentPosition, length, spanResult);
            length -= eraseLength;
            currentPosition += eraseLength;
            info.SetRichEditorDeleteSpans(spanResult);
        }
        std::advance(it, 1);
    }
}

RefPtr<SpanNode> RichEditorPattern::GetSpanNodeBySpanItem(const RefPtr<SpanItem> spanItem)
{
    RefPtr<SpanNode> spanNode;
    auto iter = std::find(spans_.begin(), spans_.end(), spanItem);
    if (iter == spans_.end()) {
        return spanNode;
    }
    auto spanIndex = std::distance(spans_.begin(), iter);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, spanNode);
    auto it = host->GetChildren().begin();
    std::advance(it, spanIndex);
    spanNode = AceType::DynamicCast<SpanNode>(*it);
    return spanNode;
}

int32_t RichEditorPattern::DeleteValueSetSymbolSpan(
    const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::SYMBOL);
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetSpanRangeStart(spanItem->position - SYMBOL_SPAN_LENGTH);
    spanResult.SetEraseLength(SYMBOL_SPAN_LENGTH);
    spanResult.SetValueString(std::to_string(spanItem->unicode));
    spanResult.SetValueResource(spanItem->GetResourceObject());
    auto spanNode = GetSpanNodeBySpanItem(spanItem);
    if (spanNode) {
        spanResult.SetSymbolSpanStyle(GetSymbolSpanStyleObject(spanNode));
    }
    return SYMBOL_SPAN_LENGTH;
}

int32_t RichEditorPattern::DeleteValueSetImageSpan(
    const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::IMAGE);
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetSpanRangeStart(spanItem->position - 1);
    spanResult.SetEraseLength(1);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, IMAGE_SPAN_LENGTH);
    auto uiNode = host->GetChildAtIndex(spanResult.GetSpanIndex());
    CHECK_NULL_RETURN(uiNode, IMAGE_SPAN_LENGTH);
    auto imageNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(imageNode, IMAGE_SPAN_LENGTH);
    auto imageRenderCtx = imageNode->GetRenderContext();
    if (imageRenderCtx->GetBorderRadius()) {
        BorderRadiusProperty brp;
        auto jsonObject = JsonUtil::Create(true);
        auto jsonBorder = JsonUtil::Create(true);
        InspectorFilter filter;
        imageRenderCtx->GetBorderRadiusValue(brp).ToJsonValue(jsonObject, jsonBorder, filter);
        spanResult.SetBorderRadius(jsonObject->GetValue("borderRadius")->IsObject()
                                       ? jsonObject->GetValue("borderRadius")->ToString()
                                       : jsonObject->GetString("borderRadius"));
    }
    auto geometryNode = imageNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, IMAGE_SPAN_LENGTH);
    auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
    CHECK_NULL_RETURN(imageLayoutProperty, IMAGE_SPAN_LENGTH);
    spanResult.SetSizeWidth(geometryNode->GetMarginFrameSize().Width());
    spanResult.SetSizeHeight(geometryNode->GetMarginFrameSize().Height());
    if (imageLayoutProperty->GetMarginProperty()) {
        spanResult.SetMargin(imageLayoutProperty->GetMarginProperty()->ToString());
    }
    if (!imageLayoutProperty->GetImageSourceInfo()->GetPixmap()) {
        spanResult.SetValueResourceStr(imageLayoutProperty->GetImageSourceInfo()->GetSrc());
    } else {
        spanResult.SetValuePixelMap(imageLayoutProperty->GetImageSourceInfo()->GetPixmap());
    }
    if (imageLayoutProperty->HasImageFit()) {
        spanResult.SetImageFit(imageLayoutProperty->GetImageFitValue());
    }
    if (imageLayoutProperty->HasVerticalAlign()) {
        spanResult.SetVerticalAlign(imageLayoutProperty->GetVerticalAlignValue());
    }
    return IMAGE_SPAN_LENGTH;
}

int32_t RichEditorPattern::DeleteValueSetBuilderSpan(
    const RefPtr<SpanItem>& spanItem, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::IMAGE);
    spanResult.SetSpanRangeEnd(spanItem->position);
    spanResult.SetSpanRangeStart(spanItem->position - 1);
    spanResult.SetEraseLength(1);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 1);
    auto uiNode = host->GetChildAtIndex(spanResult.GetSpanIndex());
    CHECK_NULL_RETURN(uiNode, 1);
    auto builderNode = AceType::DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(builderNode, 1);
    auto geometryNode = builderNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 1);
    spanResult.SetSizeWidth(geometryNode->GetMarginFrameSize().Width());
    spanResult.SetSizeHeight(geometryNode->GetMarginFrameSize().Height());
    return 1;
}

int32_t RichEditorPattern::DeleteValueSetTextSpan(
    const RefPtr<SpanItem>& spanItem, int32_t currentPosition, int32_t length, RichEditorAbstractSpanResult& spanResult)
{
    spanResult.SetSpanType(SpanResultType::TEXT);
    auto contentStartPosition
        = spanItem->position - static_cast<int32_t>(spanItem->content.length());
    spanResult.SetSpanRangeStart(contentStartPosition);
    int32_t eraseLength = 0;
    if (spanItem->position - currentPosition >= length) {
        eraseLength = length;
    } else {
        eraseLength = spanItem->position - currentPosition;
    }
    spanResult.SetSpanRangeEnd(spanItem->position);
    if (!previewTextRecord_.previewContent.empty()) {
        spanResult.SetPreviewText(previewTextRecord_.previewContent);
    } else {
        spanResult.SetValue(spanItem->content);
    }
    spanResult.SetOffsetInSpan(currentPosition - contentStartPosition);
    spanResult.SetEraseLength(eraseLength);
    spanResult.SetUrlAddress(spanItem->urlAddress);
    if (!spanItem->GetTextStyle().has_value()) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "SpanItem text style is empty.");
        return eraseLength;
    }
    spanResult.SetFontColor(spanItem->GetTextStyle()->GetTextColor().ColorToString());
    spanResult.SetFontSize(spanItem->GetTextStyle()->GetFontSize().ConvertToFp());
    spanResult.SetFontStyle(spanItem->GetTextStyle()->GetFontStyle());
    spanResult.SetFontWeight((int32_t)(spanItem->GetTextStyle()->GetFontWeight()));
    if (!spanItem->GetTextStyle()->GetFontFamilies().empty()) {
        spanResult.SetFontFamily(spanItem->GetTextStyle()->GetFontFamilies().at(0));
    }
    spanResult.SetColor(spanItem->GetTextStyle()->GetTextDecorationColor().ColorToString());
    spanResult.SetTextDecoration(spanItem->GetTextStyle()->GetTextDecoration());
    spanResult.SetTextDecorationStyle(spanItem->GetTextStyle()->GetTextDecorationStyle());
    spanResult.SetFontFeature(spanItem->GetTextStyle()->GetFontFeatures());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, eraseLength);
    auto uiNode = host->GetChildAtIndex(spanResult.GetSpanIndex());
    CHECK_NULL_RETURN(uiNode, eraseLength);
    auto spanNode = DynamicCast<SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, eraseLength);
    spanResult.SetTextStyle(GetTextStyleObject(spanNode));
    return eraseLength;
}

void RichEditorPattern::DeleteByDeleteValueInfo(const RichEditorDeleteValue& info)
{
    auto deleteSpans = info.GetRichEditorDeleteSpans();
    if (deleteSpans.empty()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ProcessDeleteNodes(deleteSpans);
    UpdateSpanPosition();
    SetCaretPosition(info.GetOffset(), false);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    OnModifyDone();
}

int32_t RichEditorPattern::ProcessDeleteNodes(std::list<RichEditorAbstractSpanResult>& deleteSpans)
{
    auto eraseLength = 0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, eraseLength);
    std::set<int32_t, std::greater<int32_t>> deleteNodes;
    for (const auto& it : deleteSpans) {
        eraseLength += it.GetEraseLength();
        switch (it.GetType()) {
            case SpanResultType::TEXT: {
                auto ui_node = host->GetChildAtIndex(it.GetSpanIndex());
                CHECK_NULL_RETURN(ui_node, eraseLength);
                auto spanNode = DynamicCast<SpanNode>(ui_node);
                CHECK_NULL_RETURN(spanNode, eraseLength);
                auto spanItem = spanNode->GetSpanItem();
                CHECK_NULL_RETURN(spanItem, eraseLength);
                auto textTemp = spanItem->content;
                auto textTempSize = static_cast<int32_t>(textTemp.size());
                if (textTempSize < it.OffsetInSpan()) {
                    TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "ProcessDeleteNodes failed, "
                        "contentLen=%{public}zu, spanItemSize=%{public}d, offsetInSpan=%{public}d",
                        textTemp.length(), textTempSize, it.OffsetInSpan());
                    RichEditorInfo errorInfo { RichEditorErrorType::DELETE_NODE, textTempSize,
                        it.GetEraseLength(), it.OffsetInSpan() };
                    RichEditorErrorReport(errorInfo);
                    continue;
                }
                textTemp.erase(it.OffsetInSpan(), it.GetEraseLength());
                if (textTemp.size() == 0) {
                    deleteNodes.emplace(it.GetSpanIndex());
                }
                spanNode->UpdateContent(textTemp);
                spanItem->position -= it.GetEraseLength();
                break;
            }
            case SpanResultType::IMAGE:
                deleteNodes.emplace(it.GetSpanIndex());
                break;
            case SpanResultType::SYMBOL:
                deleteNodes.emplace(it.GetSpanIndex());
                break;
            default:
                break;
        }
    }
    RemoveEmptySpan(deleteNodes);
    return eraseLength;
}

void RichEditorPattern::RemoveEmptySpan(std::set<int32_t, std::greater<int32_t>>& deleteSpanIndexs)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (auto index : deleteSpanIndexs) {
        host->RemoveChildAtIndex(index);
        auto it = spans_.begin();
        std::advance(it, index);
        if (it != spans_.end()) {
            spans_.erase(it);
        }
    }
}

RefPtr<GestureEventHub> RichEditorPattern::GetGestureEventHub() {
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return host->GetOrCreateGestureEventHub();
}

bool RichEditorPattern::OnKeyEvent(const KeyEvent& keyEvent)
{
    return TextInputClient::HandleKeyEvent(keyEvent);
}

void RichEditorPattern::HandleSetSelection(int32_t start, int32_t end, bool showHandle)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleSetSelection, range=[%{public}d,%{public}d], showHandle=%{public}d",
        start, end, showHandle);
    SelectionOptions options;
    options.handlePolicy = showHandle ? HandlePolicy::SHOW : HandlePolicy::HIDE;
    SetSelection(start, end, options);
}

void RichEditorPattern::HandleExtendAction(int32_t action)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleExtendAction %{public}d", action);
    switch (action) {
        case ACTION_SELECT_ALL:
            HandleMenuCallbackOnSelectAll(false);
            break;
        case ACTION_CUT:
            HandleOnCut();
            break;
        case ACTION_COPY:
            HandleOnCopy();
            break;
        case ACTION_PASTE:
            HandleOnPaste();
            break;
        default:
            break;
    }
}

void RichEditorPattern::CursorMove(CaretMoveIntent direction)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "direction=%{public}d", direction);
    switch (direction) {
        case CaretMoveIntent::Left:
            CursorMoveLeft();
            break;
        case CaretMoveIntent::Right:
            CursorMoveRight();
            break;
        case CaretMoveIntent::Up:
            CursorMoveUp();
            break;
        case CaretMoveIntent::Down:
            CursorMoveDown();
            break;
        case CaretMoveIntent::LeftWord:
            CursorMoveToNextWord(direction);
            break;
        case CaretMoveIntent::RightWord:
            CursorMoveToNextWord(direction);
            break;
        case CaretMoveIntent::ParagraghBegin:
            CursorMoveToParagraphBegin();
            break;
        case CaretMoveIntent::ParagraghEnd:
            CursorMoveToParagraphEnd();
            break;
        case CaretMoveIntent::Home:
            CursorMoveHome();
            break;
        case CaretMoveIntent::End:
            CursorMoveEnd();
            break;
        case CaretMoveIntent::LineBegin:
            CursorMoveLineBegin();
            break;
        case CaretMoveIntent::LineEnd:
            CursorMoveLineEnd();
            break;
        default:
            LOGW("Unsupported cursor move operation for rich editor");
    }
}

void RichEditorPattern::MoveCaretAfterTextChange()
{
    CHECK_NULL_VOID(isTextChange_ && moveLength_ != 0);
    isTextChange_ = false;
    switch (moveDirection_) {
        case MoveDirection::BACKWARD:
            SetCaretPosition(std::clamp((caretPosition_ - moveLength_), 0, GetTextContentLength()), false);
            break;
        case MoveDirection::FORWARD:
            SetCaretPosition(std::clamp((caretPosition_ + moveLength_), 0, GetTextContentLength()), false);
            break;
        default:
            break;
    }
    moveLength_ = 0;
}

void RichEditorPattern::InitTouchEvent()
{
    CHECK_NULL_VOID(!touchListener_);
    auto gesture = GetGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
        pattern->HandleTouchEvent(info);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchListener_);
}

void RichEditorPattern::InitPanEvent()
{
    CHECK_NULL_VOID(!panEvent_);
    auto gestureHub = GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto actionStartTask = [](const GestureEvent& info) {};
    auto actionUpdateTask = [](const GestureEvent& info) {};
    auto actionEndTask = [](const GestureEvent& info) {};
    GestureEventNoParameter actionCancelTask;
    panEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
        std::move(actionEndTask), std::move(actionCancelTask));
    PanDirection panDirection = { .type = PanDirection::ALL };
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
    gestureHub->SetPanEventType(GestureTypeName::PAN_GESTURE);
    gestureHub->SetOnGestureJudgeNativeBegin([weak = WeakClaim(this)](const RefPtr<NG::GestureInfo>& gestureInfo,
                                                 const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, GestureJudgeResult::CONTINUE);
        auto gestureType = gestureInfo->GetType();
        auto inputEventType = gestureInfo->GetInputEventType();
        bool isDraggingCaret = (gestureType == GestureTypeName::PAN_GESTURE)
            && (inputEventType == InputEventType::TOUCH_SCREEN) && pattern->moveCaretState_.isMoveCaret;
        bool isMouseSelecting = (gestureType == GestureTypeName::PAN_GESTURE)
            && (inputEventType == InputEventType::MOUSE_BUTTON) && !pattern->blockPress_;
        if (isDraggingCaret || isMouseSelecting) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "prevent pan gesture draggingCaret=%{public}d mouseSelecting=%{public}d",
                isDraggingCaret, isMouseSelecting);
            return GestureJudgeResult::CONTINUE;
        }
        CHECK_NULL_RETURN(gestureInfo->GetType() != GestureTypeName::PAN_GESTURE, GestureJudgeResult::REJECT);
        return GestureJudgeResult::CONTINUE;
    });
}

void RichEditorPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(!selectOverlay_->IsTouchAtHandle(info));
    CHECK_NULL_VOID(!info.GetTouches().empty());
    auto acceptedTouchInfo = GetAcceptedTouchLocationInfo(info);
    CHECK_NULL_VOID(acceptedTouchInfo.has_value());
    auto touchInfo = acceptedTouchInfo.value();
    auto touchType = touchInfo.GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(touchInfo);
        if (hasUrlSpan_) {
            HandleUrlSpanShowShadow(touchInfo.GetLocalLocation(), touchInfo.GetGlobalLocation(), GetUrlPressColor());
        }
    } else if (touchType == TouchType::UP) {
        IF_TRUE(status_ == Status::FLOATING, status_ = Status::NONE);
        HandleTouchUp();
        if (hasUrlSpan_) {
            HandleUrlSpanForegroundClear();
        }
    } else if (touchType == TouchType::MOVE) {
        HandleTouchMove(touchInfo);
    } else if (touchType == TouchType::CANCEL) {
        IF_PRESENT(magnifierController_, RemoveMagnifierFrameNode());
        HandleTouchCancelAfterLongPress();
        ResetTouchAndMoveCaretState();
    }
}

std::optional<TouchLocationInfo> RichEditorPattern::GetAcceptedTouchLocationInfo(const TouchEventInfo& info)
{
    const auto& touchInfos = info.GetChangedTouches();
    CHECK_NULL_RETURN(!touchInfos.empty(), std::nullopt);
    CHECK_NULL_RETURN(isTouchSelecting_ || moveCaretState_.touchFingerId.has_value(), touchInfos.front());
    const int32_t touchFingerId = isTouchSelecting_ ? selectingFingerId_ : moveCaretState_.touchFingerId.value();
    for (const auto& touchInfo : touchInfos) {
        if (touchInfo.GetFingerId() == touchFingerId) {
            return touchInfo;
        }
    }
    return std::nullopt;
}

void RichEditorPattern::HandleUrlSpanForegroundClear()
{
    CHECK_NULL_VOID(overlayMod_);
    overlayMod_->ClearSelectedForegroundColorAndRects();
    MarkDirtySelf();
}

void RichEditorPattern::HandleTouchDown(const TouchLocationInfo& info)
{
    auto sourceTool = info.GetSourceTool();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Touch down longPressState=[%{public}d, %{public}d], source=%{public}d",
        previewLongPress_, editingLongPress_, sourceTool);
    globalOffsetOnMoveStart_ = GetPaintRectGlobalOffset();
    moveCaretState_.Reset();
    ResetTouchSelectState();
    CHECK_NULL_VOID(HasFocus() && sourceTool == SourceTool::FINGER);
    auto touchDownOffset = info.GetLocalLocation();
    moveCaretState_.touchDownOffset = touchDownOffset;
    RectF lastCaretRect = GetCaretRect();
    if (RepeatClickCaret(touchDownOffset, lastCaretRect)) {
        moveCaretState_.isTouchCaret = true;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
    }
}

void RichEditorPattern::HandleTouchUp()
{
    HandleTouchUpAfterLongPress();
    ResetTouchAndMoveCaretState();
    ResetTouchSelectState();
    if (magnifierController_) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (isLongPress_) {
        isLongPress_ = false;
    }
#endif
}

void RichEditorPattern::StartFloatingCaretLand()
{
    AnimationUtils::StopAnimation(magnifierAnimation_);
    CHECK_NULL_VOID(floatingCaretState_.isFloatingCaretVisible);
    auto caretOffset = CalculateCaretOffsetAndHeight().first;
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    IF_PRESENT(overlayMod, StartFloatingCaretLand(caretOffset));
}

void RichEditorPattern::ResetTouchAndMoveCaretState()
{
    if (moveCaretState_.isMoveCaret) {
        isCursorAlwaysDisplayed_ = false;
        IF_TRUE(isEditing_, StartTwinkling());
    }
    StopAutoScroll();
    CheckScrollable();
    UpdateScrollBarOffset();
    moveCaretState_.Reset();
    StartFloatingCaretLand();
}

void RichEditorPattern::ResetTouchSelectState()
{
    selectingFingerId_ = -1;
    isTouchSelecting_ = false;
    previewLongPress_ = false;
    editingLongPress_ = false;
}

void RichEditorPattern::HandleTouchUpAfterLongPress()
{
    CHECK_NULL_VOID(editingLongPress_ || previewLongPress_);
    auto selectStart = std::min(textSelector_.GetTextStart(), GetTextContentLength());
    auto selectEnd = std::min(textSelector_.GetTextEnd(), GetTextContentLength());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "after long press textSelector=[%{public}d, %{public}d] isEditing=%{public}d",
        selectStart, selectEnd, isEditing_);
    textSelector_.Update(selectStart, selectEnd);
    FireOnSelect(selectStart, selectEnd);
    SetCaretPositionWithAffinity({ selectEnd, TextAffinity::UPSTREAM });
    CalculateHandleOffsetAndShowOverlay();
    selectOverlay_->ProcessOverlay({ .animation = true });
    FireOnSelectionChange(selectStart, selectEnd);
    IF_TRUE(IsSingleHandle(), ForceTriggerAvoidOnCaretChange());
}

void RichEditorPattern::HandleTouchCancelAfterLongPress()
{
    CHECK_NULL_VOID(editingLongPress_ || previewLongPress_);
    auto selectStart = std::min(textSelector_.GetTextStart(), GetTextContentLength());
    auto selectEnd = std::min(textSelector_.GetTextEnd(), GetTextContentLength());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "touch canceled, textSelector=[%{public}d, %{public}d] isEditing=%{public}d",
        selectStart, selectEnd, isEditing_);
    textSelector_.Update(selectStart, selectEnd);
    SetCaretPositionWithAffinity({ selectEnd, TextAffinity::UPSTREAM });
    CalculateHandleOffsetAndShowOverlay();
    selectOverlay_->ProcessOverlay({ .menuIsShow = selectOverlay_->IsCurrentMenuVisibile(), .animation = true });
    FireOnSelectionChange(selectStart, selectEnd);
}

void RichEditorPattern::HandleTouchMove(const TouchLocationInfo& info)
{
    auto originalLocaloffset = info.GetLocalLocation();
    auto offset = AdjustLocalOffsetOnMoveEvent(originalLocaloffset);
    if (previewLongPress_ || editingLongPress_) {
        if (!isTouchSelecting_) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Touch selecting start id= %{public}d", info.GetFingerId());
            showSelect_ = true;
            isTouchSelecting_ = true;
            selectingFingerId_ = info.GetFingerId();
        }
        UpdateSelectionByTouchMove(offset);
        return;
    }
    CHECK_NULL_VOID(moveCaretState_.isTouchCaret && caretTwinkling_);
    if (!moveCaretState_.isMoveCaret) {
        auto moveDistance = (offset - moveCaretState_.touchDownOffset).GetDistance();
        IF_TRUE(GreatNotEqual(moveDistance, moveCaretState_.minDistance.ConvertToPx()),
            OnMoveCaretStart(info.GetFingerId()));
    }
    UpdateCaretByTouchMove(offset);
}

void RichEditorPattern::OnMoveCaretStart(int32_t fingerId)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Move caret start id=%{public}d", fingerId);
    moveCaretState_.isMoveCaret = true;
    moveCaretState_.touchFingerId = fingerId;
    scrollable_ = false;
    SetScrollEnabled(scrollable_);
    UpdateScrollBarOffset();
    ShowCaretWithoutTwinkling();
}

void RichEditorPattern::UpdateCaretByTouchMove(const Offset& offset)
{
    CHECK_NULL_VOID(moveCaretState_.isMoveCaret);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (SelectOverlayIsOn()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Close select overlay while dragging caret");
        selectOverlay_->CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
    }
    auto touchOffset = Offset(offset.GetX(), std::max(offset.GetY(), static_cast<double>(contentRect_.GetY())));
    Offset textOffset = ConvertTouchOffsetToTextOffset(touchOffset);
    auto positionWithAffinity = paragraphs_.GetGlyphPositionAtCoordinate(textOffset);
    SetCaretPositionWithAffinity(positionWithAffinity);
    SetCaretTouchMoveOffset(offset);
    CalcAndRecordLastClickCaretInfo(textOffset);
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    auto floatingCaretCenter =
        Offset(floatingCaretState_.touchMoveOffset->GetX(), caretOffset.GetY() + caretHeight / 2);
    SetMagnifierOffsetWithAnimation(floatingCaretCenter);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::CARET, .showScrollbar = true };
    AutoScrollByEdgeDetection(param, OffsetF(offset.GetX(), offset.GetY()), EdgeDetectionStrategy::OUT_BOUNDARY);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::SetCaretTouchMoveOffset(const Offset& localOffset)
{
    double moveDistance = 0.0;
    auto positionType = GetPositionTypeFromLine();
    auto caretBoundaryRect = GetCaretBoundaryRect();
    if (positionType == PositionType::DEFAULT) {
        floatingCaretState_.UpdateByTouchMove(localOffset, moveDistance, caretBoundaryRect);
        return;
    }
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    bool isCaretAtEmptyParagraph =
        positionType == PositionType::PARAGRAPH_START && caretPosition_ == GetParagraphEndPosition(caretPosition_);
    if (isCaretAtEmptyParagraph) {
        moveDistance = std::abs(localOffset.GetX() - caretOffset.GetX());
    } else {
        moveDistance = (caretAffinityPolicy_ == CaretAffinityPolicy::DOWNSTREAM_FIRST || caretPosition_ == 0)
                        ? caretOffset.GetX() - localOffset.GetX() : localOffset.GetX() - caretOffset.GetX();
    }
    floatingCaretState_.UpdateByTouchMove(localOffset, moveDistance, caretBoundaryRect);
}

RectF RichEditorPattern::GetCaretBoundaryRect()
{
    auto caretBoundaryRect = contentRect_;
    auto overlayModifier = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_RETURN(overlayModifier, caretBoundaryRect);
    auto caretWidth = overlayModifier->GetCaretWidth();
    caretBoundaryRect.SetWidth(caretBoundaryRect.Width() - caretWidth);
    return caretBoundaryRect;
}

void RichEditorPattern::SetMagnifierLocalOffset(Offset offset)
{
    CHECK_NULL_VOID(magnifierController_);
    auto localOffset = OffsetF{ offset.GetX(), offset.GetY() };
    auto localOffsetWithTrans = localOffset;
    selectOverlay_->GetLocalPointWithTransform(localOffsetWithTrans);
    magnifierController_->SetLocalOffset(localOffsetWithTrans, localOffset);
}

void RichEditorPattern::SetMagnifierOffsetWithAnimation(Offset offset)
{
    CHECK_NULL_VOID(magnifierController_);
    auto currentLocalOffset = magnifierController_->GetLocalOffset();
    auto currentOffset = magnifierController_->GetLocalOffsetWithoutTrans().value_or(currentLocalOffset);
    if (NearEqual(currentOffset.GetY(), offset.GetY(), 0.5f) || !magnifierController_->GetShowMagnifier()) {
        SetMagnifierLocalOffset(offset);
        return;
    }
    AnimationUtils::StopAnimation(magnifierAnimation_);
    AnimationOption option{ MAGNIFIER_ANIMATION_CURVE, MAGNIFIER_ANIMATION_DURATION };
    magnifierAnimation_ = AnimationUtils::StartAnimation(option, [weak = WeakClaim(this), offset]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetMagnifierLocalOffset(offset);
    });
}

Offset RichEditorPattern::AdjustLocalOffsetOnMoveEvent(const Offset& originalOffset)
{
    auto deltaOffset = GetPaintRectGlobalOffset() - globalOffsetOnMoveStart_;
    return { originalOffset.GetX() - deltaOffset.GetX(), originalOffset.GetY() - deltaOffset.GetY() };
}

void RichEditorPattern::StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex)
{
    CHECK_NULL_VOID(isEnableHapticFeedback_ && (currentIndex != preIndex));
    VibratorUtils::StartVibraFeedback("slide");
}

bool RichEditorPattern::IsScrollBarPressed(const MouseInfo& info)
{
    auto scrollBar = GetScrollBar();
    bool isScrollBarShow = scrollBar && scrollBar->NeedPaint();
    CHECK_NULL_RETURN(isScrollBarShow, false);
    Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
    return scrollBar->InBarRectRegion(point);
}

void RichEditorPattern::HandleMouseLeftButtonMove(const MouseInfo& info)
{
    ACE_SCOPED_TRACE("RichEditorHandleMouseLeftButtonMove");
    CHECK_NULL_VOID(!IsPreviewTextInputting());
    if (blockPress_) {
        ACE_SCOPED_TRACE("RichEditorUpdateDragBoxes");
        dragBoxes_ = GetTextBoxes();
        return;
    }
    CHECK_NULL_VOID(leftMousePress_);

    auto localOffset = info.GetLocalLocation();
    const auto& globalOffset = info.GetGlobalLocation();
    auto paintOffset = GetPaintRectGlobalOffset();
    if (!selectOverlay_->HasRenderTransform()) {
        localOffset = Offset(globalOffset.GetX() - paintOffset.GetX(), globalOffset.GetY() - paintOffset.GetY());
    }
    Offset textOffset = ConvertTouchOffsetToTextOffset(localOffset);
    if (dataDetectorAdapter_->pressedByLeftMouse_) {
        dataDetectorAdapter_->pressedByLeftMouse_ = false;
        MoveCaretAndStartFocus(textOffset);
    }

    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());

    mouseStatus_ = MouseStatus::MOVE;
    HandleMouseSelect(localOffset);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::HandleMouseSelect(const Offset& localOffset)
{
    if (!textSelector_.IsValid()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "prevent mouse selecting because selection has been reset");
        return;
    }
    Offset textOffset = ConvertTouchOffsetToTextOffset(localOffset);
    auto position = GetTextContentLength() == 0 ? 0 : paragraphs_.GetIndex(textOffset);
    UpdateSelector(textSelector_.baseOffset, position);
    if (!isFirstMouseSelect_) {
        AdjustCursorPosition(position);
        SetCaretPosition(position);
        AutoScrollParam param = {
            .autoScrollEvent = AutoScrollEvent::MOUSE, .showScrollbar = true, .eventOffset = localOffset
        };
        AutoScrollByEdgeDetection(param, OffsetF(localOffset.GetX(), localOffset.GetY()),
            EdgeDetectionStrategy::OUT_BOUNDARY);
        showSelect_ = true;
    } else {
        isFirstMouseSelect_ = false;
    }
    if (textSelector_.SelectNothing()) {
        StartTwinkling();
    } else {
        StopTwinkling();
    }
    isMouseSelect_ = true;
}

void RichEditorPattern::HandleMouseLeftButtonPress(const MouseInfo& info)
{
    isMousePressed_ = true;
    auto frameNodeRange = GetSpanRangeByLocalOffset(info.GetLocalLocation());
    bool frameNodeSelected = textSelector_.ContainsRange(frameNodeRange);
    bool pressFrameNode = !frameNodeSelected && InRangeRect(info.GetGlobalLocation(), frameNodeRange);
    if (IsPreviewTextInputting() || IsScrollBarPressed(info) || BetweenSelectedPosition(info.GetGlobalLocation()) ||
        pressFrameNode) {
        blockPress_ = true;
        return;
    }
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!focusHub->IsFocusable()) {
        return;
    }
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    int32_t position = (GetTextContentLength() == 0) ? 0 : paragraphs_.GetIndex(textOffset);
    if (shiftFlag_) {
        HandleShiftSelect(position);
    } else {
        IF_TRUE(!textSelector_.SelectNothing(), ResetSelection());
        textSelector_.Update(position);
    }
    leftMousePress_ = true;
    globalOffsetOnMoveStart_ = GetPaintRectGlobalOffset();
    mouseStatus_ = MouseStatus::PRESSED;
    blockPress_ = false;
    caretUpdateType_ = CaretUpdateType::PRESSED;
    dataDetectorAdapter_->pressedByLeftMouse_ = false;
    HandleClickAISpanEvent(PointF(textOffset.GetX(), textOffset.GetY()));
    if (dataDetectorAdapter_->pressedByLeftMouse_) {
        return;
    }
    UseHostToUpdateTextFieldManager();
    MoveCaretAndStartFocus(textOffset);
    CalcCaretInfoByClick(info.GetLocalLocation());
}

void RichEditorPattern::HandleShiftSelect(int32_t position)
{
    CHECK_NULL_VOID(shiftFlag_);
    int32_t start = textSelector_.SelectNothing() ? caretPosition_ : textSelector_.baseOffset;
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleShiftSelect [%{public}d-%{public}d]", start, position);
    UpdateSelector(start, position);
    SetCaretPosition(position);
    FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::HandleMouseLeftButtonRelease(const MouseInfo& info)
{
    blockPress_ = false;
    leftMousePress_ = false;
    CHECK_NULL_VOID(!IsPreviewTextInputting());
    auto oldMouseStatus = mouseStatus_;
    mouseStatus_ = MouseStatus::RELEASED;
    isMouseSelect_ = false;
    isFirstMouseSelect_ = true;
    if (!showSelect_) {
        showSelect_ = true;
        ResetSelection();
    }
    if (dataDetectorAdapter_->pressedByLeftMouse_ && oldMouseStatus != MouseStatus::MOVE && !IsDragging()) {
        dataDetectorAdapter_->ResponseBestMatchItem(dataDetectorAdapter_->clickedAISpan_);
        dataDetectorAdapter_->pressedByLeftMouse_ = false;
        isMousePressed_ = false;
        return;
    }

    auto selectStart = std::min(textSelector_.baseOffset, textSelector_.destinationOffset);
    auto selectEnd = std::max(textSelector_.baseOffset, textSelector_.destinationOffset);
    if (selectStart != selectEnd && isMousePressed_ && oldMouseStatus == MouseStatus::MOVE) {
        FireOnSelect(selectStart, selectEnd);
    }
    StopAutoScroll();
    if (textSelector_.IsValid() && !textSelector_.StartEqualToDest() && IsSelectedBindSelectionMenu() &&
        oldMouseStatus == MouseStatus::MOVE) {
        auto offsetX = static_cast<float>(info.GetGlobalLocation().GetX());
        auto offsetY = static_cast<float>(info.GetGlobalLocation().GetY());
        selectionMenuOffsetByMouse_ = OffsetF(offsetX, offsetY);
        selectionMenuOffsetClick_ = OffsetF(offsetX, offsetY);
        ShowSelectOverlay(RectF(), RectF(), false, TextResponseType::SELECTED_BY_MOUSE);
    }
    isMousePressed_ = false;
    if (HasFocus()) {
        HandleOnEditChanged(true);
    }
}

void RichEditorPattern::HandleMouseLeftButton(const MouseInfo& info)
{
    if (info.GetAction() == MouseAction::MOVE) {
        HandleMouseLeftButtonMove(info);
    } else if (info.GetAction() == MouseAction::PRESS) {
        HandleMouseLeftButtonPress(info);
    } else if (info.GetAction() == MouseAction::RELEASE) {
        HandleMouseLeftButtonRelease(info);
    }
}

void RichEditorPattern::HandleMouseRightButton(const MouseInfo& info)
{
    CHECK_NULL_VOID(!IsPreviewTextInputting());
    IF_TRUE(IsDragging(), isInterceptMouseRightRelease_ = true);
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub && focusHub->IsFocusable());
    if (info.GetAction() == MouseAction::RELEASE && isInterceptMouseRightRelease_) {
        usingMouseRightButton_ = false;
        isMousePressed_ = false;
        isInterceptMouseRightRelease_ = false;
        return;
    }
    if (info.GetAction() == MouseAction::PRESS) {
        isMousePressed_ = true;
        usingMouseRightButton_ = true;
        CloseSelectOverlay();
    } else if (info.GetAction() == MouseAction::RELEASE) {
        auto offsetX = static_cast<float>(info.GetGlobalLocation().GetX());
        auto offsetY = static_cast<float>(info.GetGlobalLocation().GetY());
        selectionMenuOffsetByMouse_ = OffsetF(offsetX, offsetY);
        selectionMenuOffsetClick_ = OffsetF(offsetX, offsetY);
        selectOverlay_->SetIsSingleHandle(false);
        if (textSelector_.IsValid() && BetweenSelection(info.GetGlobalLocation())) {
            ShowSelectOverlay(RectF(), RectF(), IsSelectAll(), TextResponseType::RIGHT_CLICK);
            isMousePressed_ = false;
            usingMouseRightButton_ = false;
            return;
        }
        auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
        Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
            info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
        HandleClickAISpanEvent(PointF(textOffset.GetX(), textOffset.GetY()));
        if (dataDetectorAdapter_->hasClickedAISpan_) {
            dataDetectorAdapter_->hasClickedAISpan_ = false;
            isMousePressed_ = false;
            usingMouseRightButton_ = false;
            return;
        }
        if (textSelector_.IsValid()) {
            CloseSelectOverlay();
            ResetSelection();
        }
        MouseRightFocus(info);
        ShowSelectOverlay(RectF(), RectF(), IsSelectAll(), TextResponseType::RIGHT_CLICK);
        isMousePressed_ = false;
        usingMouseRightButton_ = false;
    }
}

std::pair<int32_t, int32_t> RichEditorPattern::GetSpanRangeByLocalOffset(Offset localOffset)
{
    Offset textOffset = ConvertTouchOffsetToTextOffset(localOffset);
    auto [pos, affinity] = paragraphs_.GetGlyphPositionAtCoordinate(textOffset);
    auto spanFilter = [](SpanItemType itemType) {
        return itemType == SpanItemType::IMAGE
            || itemType == SpanItemType::PLACEHOLDER
            || itemType == SpanItemType::CustomSpan; };
    auto it = std::find_if(spans_.begin(), spans_.end(),
        [pos = static_cast<int32_t>(pos), affinity = affinity, spanFilter](const RefPtr<SpanItem>& spanItem) {
            CHECK_NULL_RETURN(spanFilter(spanItem->spanItemType), false);
            return pos == (affinity == TextAffinity::UPSTREAM ? spanItem->position : spanItem->rangeStart);
        });
    bool isMouseOnTarget = it != spans_.end();
    CHECK_NULL_RETURN(isMouseOnTarget, std::make_pair(-1, -1));
    return affinity == TextAffinity::UPSTREAM ? std::make_pair(pos - 1, pos) : std::make_pair(pos, pos + 1);
}

void RichEditorPattern::MouseRightFocus(const MouseInfo& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();

    auto selectRange = GetSpanRangeByLocalOffset(info.GetLocalLocation());
    if (InRangeRect(info.GetGlobalLocation(), selectRange)) {
        selectedType_ = TextSpanType::IMAGE;
        textSelector_.Update(selectRange.first, selectRange.second);
        FireOnSelect(selectRange.first, selectRange.second);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return;
    }
    if (textSelector_.IsValid()) {
        ResetSelection();
    }
    Offset textOffset = ConvertTouchOffsetToTextOffset(info.GetLocalLocation());
    auto position = paragraphs_.GetIndex(textOffset);
    SetCaretPosition(position);
    CalcAndRecordLastClickCaretInfo(textOffset);
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    selectedType_ = TextSpanType::TEXT;
    CHECK_NULL_VOID(overlayMod_);
    DynamicCast<RichEditorOverlayModifier>(overlayMod_)->SetCaretOffsetAndHeight(caretOffset, caretHeight);
    StartTwinkling();
}

void RichEditorPattern::FireOnSelect(int32_t selectStart, int32_t selectEnd)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    if (!textSelectInfo.GetSelection().resultObjects.empty()) {
        eventHub->FireOnSelect(&textSelectInfo);
    }
    UpdateSelectionType(textSelectInfo);
}

void RichEditorPattern::UpdateSelectionType(const SelectionInfo& textSelectInfo)
{
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        TextPattern::UpdateSelectionType(GetAdjustedSelectionInfo(textSelectInfo));
    } else {
        TextPattern::UpdateSelectionType(textSelectInfo);
    }
}

SelectionInfo RichEditorPattern::GetAdjustedSelectionInfo(const SelectionInfo& textSelectInfo)
{
    auto selection = textSelectInfo.GetSelection();
    auto resultObjects = selection.resultObjects;
    std::for_each(resultObjects.begin(), resultObjects.end(), [](ResultObject& object) {
        if (object.type == SelectSpanType::TYPEIMAGE && object.valueString == u" " && object.valuePixelMap == nullptr) {
            object.type = SelectSpanType::TYPEBUILDERSPAN;
        }
    });
    SelectionInfo adjustedInfo;
    adjustedInfo.SetSelectionStart(selection.selection[RichEditorSpanRange::RANGESTART]);
    adjustedInfo.SetSelectionEnd(selection.selection[RichEditorSpanRange::RANGEEND]);
    adjustedInfo.SetResultObjectList(resultObjects);
    return adjustedInfo;
}

void RichEditorPattern::HandleMouseEvent(const MouseInfo& info)
{
    HandleImageHoverEvent(info);
    if (selectOverlay_->IsHandleShow() && info.GetAction() == MouseAction::PRESS) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Close selectOverlay when handle is showing");
        CloseSelectOverlay();
    }
    auto scrollBar = GetScrollBar();
    if (scrollBar && (scrollBar->IsHover() || scrollBar->IsPressed())) {
        ChangeMouseStyle(MouseFormat::DEFAULT);
        HandleUrlSpanForegroundClear();
        return;
    }

    if (hasUrlSpan_) {
        auto show = HandleUrlSpanShowShadow(info.GetLocalLocation(), info.GetGlobalLocation(), GetUrlHoverColor());
        if (show) {
            ChangeMouseStyle(MouseFormat::HAND_POINTING);
        } else {
            ChangeMouseStyle(MouseFormat::TEXT_CURSOR);
        }
    }

    if (currentMouseStyle_ == MouseFormat::DEFAULT && !IsDragging()) {
        ChangeMouseStyle(MouseFormat::TEXT_CURSOR);
    }

    caretUpdateType_ = CaretUpdateType::NONE;
    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        sourceType_ = info.GetSourceDevice();
        HandleMouseLeftButton(info);
    } else if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        sourceType_ = info.GetSourceDevice();
        HandleMouseRightButton(info);
    }
}

Color RichEditorPattern::GetUrlHoverColor()
{
    auto theme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(theme, Color());
    return theme->GetUrlHoverColor();
}

Color RichEditorPattern::GetUrlPressColor()
{
    auto theme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(theme, Color());
    return theme->GetUrlPressColor();
}

Color RichEditorPattern::GetUrlSpanColor()
{
    auto theme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(theme, Color());
    return theme->GetUrlDefaultColor();
}

void RichEditorPattern::TriggerAvoidOnCaretChange()
{
    CHECK_NULL_VOID(HasFocus());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    CHECK_NULL_VOID(pipeline->UsingCaretAvoidMode());
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    if (!safeAreaManager || NearZero(safeAreaManager->GetKeyboardInset().Length(), 0)) {
        return;
    }
    textFieldManager->SetHeight(GetCaretRect().Height());
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([manager = WeakPtr<TextFieldManagerNG>(textFieldManager)] {
        auto textFieldManager = manager.Upgrade();
        CHECK_NULL_VOID(textFieldManager);
        textFieldManager->TriggerAvoidOnCaretChange();
    }, TaskExecutor::TaskType::UI, "ArkUIRichEditorTriggerAvoidOnCaretChange", PriorityType::VIP);
}

void RichEditorPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    selectOverlay_->UpdateMenuOnWindowSizeChanged(type);
    CHECK_NULL_VOID(type == WindowSizeChangeReason::ROTATION);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->ResetOptionalClickPosition();
    taskExecutor->PostTask(
        [weak = WeakClaim(this), manager = WeakPtr<TextFieldManagerNG>(textFieldManager)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateParentOffsetAndOverlay();
            pattern->UpdateModifierCaretOffsetAndHeight();
            pattern->UpdateTextFieldManager(Offset(pattern->parentGlobalOffset_.GetX(),
                pattern->parentGlobalOffset_.GetY()), pattern->frameRect_.Height());
            pattern->UpdateCaretInfoToController();
            if (pattern->HasFocus()) {
                auto textFieldManager = manager.Upgrade();
                CHECK_NULL_VOID(textFieldManager);
                auto container = Container::Current();
                CHECK_NULL_VOID(container);
                auto displayInfo = container->GetDisplayInfo();
                if (displayInfo) {
                    auto dmRotation = static_cast<int32_t>(displayInfo->GetRotation());
                    textFieldManager->SetFocusFieldOrientation(dmRotation);
                    textFieldManager->SetFocusFieldAlreadyTriggerWsCallback(true);
                }
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIRichEditorOnWindowSizeChangedRotation", PriorityType::VIP);
}

void RichEditorPattern::CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType)
{
    auto selectType = selectedType_.value_or(TextSpanType::NONE);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "textSpanType=%{public}d, responseType=%{public}d", selectType, responseType);
    std::shared_ptr<SelectionMenuParams> menuParams = GetMenuParams(selectType, responseType);
    CHECK_NULL_VOID(menuParams);

    // long pressing on the image needs to set the position of the pop-up menu following the long pressing position
    if (selectType == TextSpanType::IMAGE && !selectInfo.isUsingMouse) {
        selectInfo.menuInfo.menuOffset = OffsetF(selectionMenuOffset_.GetX(), selectionMenuOffset_.GetY());
    }

    CopyBindSelectionMenuParams(selectInfo, menuParams);
}

void RichEditorPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle, bool isCopyAll,
    TextResponseType responseType, bool handleReverse)
{
    CHECK_NULL_VOID(!IsPreviewTextInputting());
    textResponseType_ = responseType;
    selectOverlay_->ProcessOverlay({.animation = true});
}

void RichEditorPattern::SetIsEnableSubWindowMenu()
{
    selectOverlay_->SetIsHostNodeEnableSubWindowMenu(true);
}

void RichEditorPattern::CheckEditorTypeChange()
{
    CHECK_NULL_VOID(selectOverlayProxy_);
    CHECK_NULL_VOID(!selectOverlayProxy_->IsClosed());
    if (selectOverlayProxy_->GetSelectOverlayMangerInfo().menuInfo.editorType.value_or(static_cast<int32_t>(
            TextSpanType::NONE)) != static_cast<int32_t>(selectedType_.value_or(TextSpanType::NONE))) {
        CloseSelectOverlay();
    }
}

void RichEditorPattern::OnCopyOperationExt(RefPtr<PasteDataMix>& pasteData)
{
    auto subSpanString =
        ToStyledString(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    std::vector<uint8_t> tlvData;
    subSpanString->EncodeTlv(tlvData);
    auto text = subSpanString->GetString();
    clipboard_->AddSpanStringRecord(pasteData, tlvData);
}

void RichEditorPattern::HandleOnCopyStyledString()
{
    RefPtr<PasteDataMix> pasteData = clipboard_->CreatePasteDataMix();
    auto subSpanString = styledString_->GetSubSpanString(textSelector_.GetTextStart(),
        textSelector_.GetTextEnd() - textSelector_.GetTextStart());
#ifdef PREVIEW
    clipboard_->SetData(subSpanString->GetString(), CopyOptions::Distributed);
#else
    std::vector<uint8_t> tlvData;
    subSpanString->EncodeTlv(tlvData);
    clipboard_->AddSpanStringRecord(pasteData, tlvData);
    clipboard_->AddTextRecord(pasteData, subSpanString->GetString());
    clipboard_->SetData(pasteData, copyOption_);
#endif
}

void RichEditorPattern::OnCopyOperation(bool isUsingExternalKeyboard)
{
    if (isSpanStringMode_) {
        HandleOnCopyStyledString();
        return;
    }
    RefPtr<PasteDataMix> pasteData = clipboard_->CreatePasteDataMix();
    auto selectStart = textSelector_.GetTextStart();
    auto selectEnd = textSelector_.GetTextEnd();
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    auto copyResultObjects = textSelectInfo.GetSelection().resultObjects;
    caretUpdateType_ = CaretUpdateType::NONE;
    if (copyResultObjects.empty()) {
        return;
    }
    for (auto resultObj = copyResultObjects.rbegin(); resultObj != copyResultObjects.rend(); ++resultObj) {
        ProcessResultObject(pasteData, *resultObj);
    }
    clipboard_->SetData(pasteData, copyOption_);
}

void RichEditorPattern::ProcessResultObject(RefPtr<PasteDataMix> pasteData, const ResultObject& result)
{
    CHECK_NULL_VOID(pasteData);
    auto multiTypeRecordImpl = AceType::MakeRefPtr<MultiTypeRecordImpl>();
    if (result.type == SelectSpanType::TYPESPAN) {
        auto data = UtfUtils::Str16ToStr8(GetSelectedSpanText(result.valueString,
            result.offsetInSpan[RichEditorSpanRange::RANGESTART], result.offsetInSpan[RichEditorSpanRange::RANGEEND]));
#ifdef PREVIEW
        clipboard_->SetData(data, CopyOptions::Distributed);
#else
        multiTypeRecordImpl->SetPlainText(data);
        EncodeTlvDataByResultObject(result, multiTypeRecordImpl->GetSpanStringBuffer());
        clipboard_->AddMultiTypeRecord(pasteData, multiTypeRecordImpl);
#endif
        return;
    }
    if (result.type == SelectSpanType::TYPEIMAGE) {
#ifdef PREVIEW
        if (result.valuePixelMap) {
            clipboard_->AddPixelMapRecord(pasteData, result.valuePixelMap);
        } else {
            clipboard_->AddImageRecord(pasteData, UtfUtils::Str16ToStr8(result.valueString));
        }
#else
        if (result.valuePixelMap) {
            multiTypeRecordImpl->SetPixelMap(result.valuePixelMap);
        } else {
            multiTypeRecordImpl->SetUri(UtfUtils::Str16ToStr8(result.valueString));
        }
        EncodeTlvDataByResultObject(result, multiTypeRecordImpl->GetSpanStringBuffer());
        clipboard_->AddMultiTypeRecord(pasteData, multiTypeRecordImpl);
#endif
    }
}

void RichEditorPattern::EncodeTlvDataByResultObject(const ResultObject& result, std::vector<uint8_t>& tlvData)
{
    auto selectStart = result.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] + result.offsetInSpan[RichEditorSpanRange::RANGESTART];
    auto selectEnd = result.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] + result.offsetInSpan[RichEditorSpanRange::RANGEEND];
    auto spanString = ToStyledString(selectStart, selectEnd);
    spanString->EncodeTlv(tlvData);
}

void RichEditorPattern::HandleOnCopy(bool isUsingExternalKeyboard)
{
    CHECK_NULL_VOID(clipboard_);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "isUsingExternalKeyboard=%{public}d, copyOption=%{public}d",
        isUsingExternalKeyboard, copyOption_);
    if (copyOption_ == CopyOptions::None) {
        return;
    }
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextCommonEvent event;
    eventHub->FireOnCopy(event);
    IF_TRUE(!event.IsPreventDefault(), OnCopyOperation(isUsingExternalKeyboard));
    if (selectOverlay_->IsUsingMouse() || isUsingExternalKeyboard) {
        CloseSelectOverlay();
    } else {
        selectOverlay_->HideMenu();
    }
}

void RichEditorPattern::ResetAfterPaste()
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "ResetAfterPaste");
    auto pasteStr = GetPasteStr();
    SetCaretSpanIndex(-1);
    StartTwinkling();
    RequestKeyboardToEdit();
    CloseSelectOverlay();
    InsertValueByPaste(pasteStr);
    ClearPasteStr();
}

void RichEditorPattern::InsertValueByPaste(const std::u16string& pasteStr)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "InsertValueByPaste");
    if (isSpanStringMode_) {
        InsertValueInStyledString(pasteStr, true, true);
        return;
    }
    InsertValueByOperationType(pasteStr, OperationType::DEFAULT);
}

void RichEditorPattern::HandleOnPaste()
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextCommonEvent event;
    eventHub->FireOnPaste(event);
    OnReportRichEditorEvent("onPasteComplete");
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "HandleOnPaste, preventDefault=%{public}d", event.IsPreventDefault());
    if (event.IsPreventDefault()) {
        CloseSelectOverlay();
        ResetSelection();
        StartTwinkling();
        RequestKeyboardToEdit();
        return;
    }
    CHECK_NULL_VOID(clipboard_);
#ifdef PREVIEW
    auto pasteCallback = [weak = WeakClaim(this)](const std::string& text) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "pasteCallback callback in previewer");
        auto richEditor = weak.Upgrade();
        CHECK_NULL_VOID(richEditor);
        richEditor->PasteStr(text);
    };
    clipboard_->GetData(pasteCallback);
#else
    auto isSpanStringMode = isSpanStringMode_;
    auto pasteCallback = [weak = WeakClaim(this), isSpanStringMode](std::vector<std::vector<uint8_t>>& arrs,
                             const std::string& text, bool& isMulitiTypeRecord) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
            "pasteCallback callback, isMulitiTypeRecord : [%{public}d], isSpanStringMode : [%{public}d]",
            isMulitiTypeRecord, isSpanStringMode);
        auto richEditor = weak.Upgrade();
        CHECK_NULL_VOID(richEditor);
        std::list<RefPtr<SpanString>> spanStrings;
        for (auto arr : arrs) {
            spanStrings.push_back(SpanString::DecodeTlv(arr));
        }
        if (!spanStrings.empty() && !isMulitiTypeRecord) {
            for (auto spanString : spanStrings) {
                richEditor->AddSpanByPasteData(spanString);
                richEditor->RequestKeyboardToEdit();
            }
            return;
        }
        richEditor->PasteStr(text);
    };
    clipboard_->GetSpanStringData(pasteCallback);
#endif
}

void RichEditorPattern::PasteStr(const std::string& text)
{
    if (text.empty()) {
        ResetSelection();
        StartTwinkling();
        CloseSelectOverlay();
        RequestKeyboardToEdit();
        return;
    }
    AddPasteStr(text);
    ResetAfterPaste();
}

void RichEditorPattern::SetCaretSpanIndex(int32_t index)
{
    caretSpanIndex_ = index;
}

void RichEditorPattern::HandleOnCut()
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "copyOption=%{public}d, textSelector_.IsValid()=%{public}d",
        copyOption_, textSelector_.IsValid());
    if (copyOption_ == CopyOptions::None) {
        return;
    }
    if (!textSelector_.IsValid()) {
        return;
    }
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextCommonEvent event;
    eventHub->FireOnCut(event);
    if (event.IsPreventDefault()) {
        CloseSelectOverlay();
        ResetSelection();
        StartTwinkling();
        RequestKeyboardToEdit();
        return;
    }

    caretUpdateType_ = CaretUpdateType::NONE;
    OnCopyOperation();
    DeleteBackward(1);
}

void RichEditorPattern::HandleOnShare()
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextCommonEvent event;
    eventHub->FireOnShare(event);
    selectOverlay_->HideMenu(true);
    auto value = selectOverlay_->GetSelectedText();
    auto shareWord = std::regex_replace(value, REMOVE_SPACE_CHARS, "");
    CHECK_NULL_VOID(!shareWord.empty());
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto containerId = pipeline->GetInstanceId();
    auto contentRect = selectOverlay_->GetSelectArea();
    TextShareAdapter::StartTextShareTask(containerId, contentRect, shareWord);
}

std::function<void(Offset)> RichEditorPattern::GetThumbnailCallback()
{
    return [wk = WeakClaim(this)](const Offset& point) {
        auto pattern = wk.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->BetweenSelectedPosition(point)) {
            return;
        }
        auto isContentDraggable = pattern->JudgeContentDraggable();
        if (!isContentDraggable) {
            TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "GetThumbnailCallback call, draggable is false");
            pattern->SetIsTextDraggable(false);
            return;
        }
        if (pattern->dragBoxes_.empty()) {
            pattern->dragBoxes_ = pattern->GetTextBoxes();
        }
        pattern->CreateDragNode();
    };
}

void RichEditorPattern::CreateDragNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto children = host->GetChildren();
    std::list<RefPtr<FrameNode>> imageChildren;
    for (const auto& child : children) {
        auto node = DynamicCast<FrameNode>(child);
        CHECK_NULL_CONTINUE(node);
        if (auto& tag = node->GetTag(); tag == V2::IMAGE_ETS_TAG || tag == V2::PLACEHOLDER_SPAN_ETS_TAG) {
            imageChildren.emplace_back(node);
        }
    }
    TextDragInfo info;
    info.maxSelectedWidth = GetMaxSelectedWidth();
    info.handleColor = GetCaretColor();
    info.selectedBackgroundColor = GetSelectedBackgroundColor();
    auto selectOverlayInfo = selectOverlay_->GetSelectOverlayInfo();
    if (selectOverlayInfo.has_value()) {
        if (selectOverlayInfo->firstHandle.isShow) {
            info.firstHandle = selectOverlayInfo->firstHandle.paintRect;
        }
        if (selectOverlayInfo->secondHandle.isShow) {
            info.secondHandle =  selectOverlayInfo->secondHandle.paintRect;
        }
    }
    if (textSelector_.GetTextEnd() - textSelector_.GetTextStart() == 1) {
        auto spanItem = GetSpanItemByPosition(textSelector_.GetTextStart());
        auto placeholderSpanItem = DynamicCast<PlaceholderSpanItem>(spanItem);
        if (placeholderSpanItem) {
            info.dragBackgroundColor = placeholderSpanItem->dragBackgroundColor_;
            info.isDragShadowNeeded = placeholderSpanItem->isDragShadowNeeded_;
        }
    }
    dragNode_ = RichEditorDragPattern::CreateDragNode(host, imageChildren, info);
    CHECK_NULL_VOID(dragNode_);
    InitDragShadow(host, dragNode_, info.isDragShadowNeeded, info.dragBackgroundColor.has_value());
    FrameNode::ProcessOffscreenNode(dragNode_);
}

float RichEditorPattern::GetMaxSelectedWidth()
{
    auto boxes = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    CHECK_NULL_RETURN(!boxes.empty(), 0.0f);
    float startX = boxes.front().Left();
    float endX = boxes.front().Right();
    for (const auto& box : boxes) {
        startX = std::min(startX, box.Left());
        endX = std::max(endX, box.Right());
    }
    startX = std::min(0.0f, startX);
    return std::abs(startX - endX);
}

void RichEditorPattern::InitDragShadow(const RefPtr<FrameNode>& host, const RefPtr<FrameNode>& dragNode,
    bool isDragShadowNeeded, bool hasDragBackgroundColor)
{
    CHECK_NULL_VOID(host && dragNode);
    auto textDragPattern = dragNode->GetPattern<TextDragPattern>();
    CHECK_NULL_VOID(textDragPattern);
    auto option = host->GetDragPreviewOption();
    if (isDragShadowNeeded) {
        option.options.shadowPath = textDragPattern->GetBackgroundPath()->ConvertToSVGString();
        option.options.shadow = Shadow(RICH_DEFAULT_ELEVATION, {0.0, 0.0}, Color(RICH_DEFAULT_SHADOW_COLOR),
            ShadowStyle::OuterFloatingSM);
        option.options.isFilled = !hasDragBackgroundColor;
    } else {
        option.options.shadowPath.clear();
        option.options.shadow.reset();
        option.options.isFilled = true;
    }
    host->SetDragPreviewOptions(option);
}

void RichEditorPattern::CreateHandles()
{
    if (IsDragging()) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "do not show handles when dragging");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CalculateHandleOffsetAndShowOverlay();
    selectOverlay_->ProcessOverlay({ .menuIsShow = selectOverlay_->IsCurrentMenuVisibile(), .animation = true });
}

void RichEditorPattern::ShowHandles(const bool isNeedShowHandles)
{
    if (!IsSelected()) {
        showSelect_ = true;
        IF_TRUE(isEditing_, StartTwinkling());
        return;
    }
    ShowHandles();
}

void RichEditorPattern::ShowHandles()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!selectOverlay_->IsBothHandlesShow() && !selectOverlay_->SelectOverlayIsCreating()) {
        showSelect_ = true;
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        CHECK_NULL_VOID(textSelector_.IsValid());
        CHECK_NULL_VOID(!isMouseSelect_);
        CalculateHandleOffsetAndShowOverlay();
        selectOverlay_->ProcessOverlay({.menuIsShow = false, .animation = false});
    }
}

void RichEditorPattern::OnAreaChangedInner()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto prevParentGlobalOffset = parentGlobalOffset_;
    UpdateParentOffsetAndOverlay();
    IF_TRUE(parentGlobalOffset_ != prevParentGlobalOffset,
        UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height()));
    IF_TRUE(parentGlobalOffset_ != prevParentGlobalOffset, UpdateCaretInfoToController());
}

void RichEditorPattern::UpdateParentOffsetAndOverlay()
{
    auto parentGlobalOffset = GetPaintRectGlobalOffset(); // offset on screen(with transformation)
    CHECK_NULL_VOID(parentGlobalOffset != parentGlobalOffset_);
    parentGlobalOffset_ = parentGlobalOffset;
    OnParentOffsetChange();
    selectOverlay_->UpdateSelectOverlayOnAreaChanged();
}


void RichEditorPattern::OnParentOffsetChange()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    IF_PRESENT(overlayManager, CloseAIEntityMenu(frameId_));
}

void RichEditorPattern::CloseSelectionMenu()
{
    // used by sdk
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "CloseSelectionMenu");
    CloseSelectOverlay();
}

void RichEditorPattern::OnDragNodeFloating()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "OnDragNodeFloating");
    status_ = Status::FLOATING;
}

void RichEditorPattern::CloseSelectOverlay()
{
    // used by inner
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "CloseSelectOverlay");
    selectOverlay_->CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
}

void RichEditorPattern::CloseHandleAndSelect()
{
    selectOverlay_->CloseOverlay(false, CloseReason::CLOSE_REASON_DRAG_FLOATING);
    showSelect_ = false;
    auto host = GetHost();
    IF_PRESENT(host, MarkDirtyNode(PROPERTY_UPDATE_RENDER));
}

void RichEditorPattern::CalculateHandleOffsetAndShowOverlay(bool isUsingMouse)
{
    auto globalOffset = GetGlobalOffset();
    if (!selectOverlay_->GetIsHandleMoving()) {
        textSelector_.ReverseTextSelector();
    }
    int32_t baseOffset = std::min(textSelector_.baseOffset, GetTextContentLength());
    int32_t destinationOffset = std::min(textSelector_.destinationOffset, GetTextContentLength());
    SizeF firstHandlePaintSize;
    SizeF secondHandlePaintSize;
    OffsetF firstHandleOffset;
    OffsetF secondHandleOffset;
    auto isSingleHandle = IsSingleHandle();
    selectOverlay_->SetIsSingleHandle(isSingleHandle);
    if (isSingleHandle) {
        auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
        // only show the second handle.
        secondHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), caretHeight };
        secondHandleOffset = caretOffset + globalOffset;
    } else {
        float startSelectHeight = 0.0f;
        float endSelectHeight = 0.0f;
        auto startOffset = CalcCursorOffsetByPosition(baseOffset, startSelectHeight, true, false);
        auto endOffset = CalcCursorOffsetByPosition(destinationOffset, endSelectHeight, false, false);
        firstHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), startSelectHeight };
        secondHandlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), endSelectHeight };
        firstHandleOffset = startOffset + globalOffset;
        secondHandleOffset = endOffset + globalOffset;
        firstHandleOffset.SetX(firstHandleOffset.GetX() - firstHandlePaintSize.Width() / 2.0f);
        secondHandleOffset.SetX(secondHandleOffset.GetX() - secondHandlePaintSize.Width() / 2.0f);
    }
    textSelector_.selectionBaseOffset = firstHandleOffset;
    textSelector_.selectionDestinationOffset = secondHandleOffset;
    textSelector_.firstHandle = RectF{ firstHandleOffset, firstHandlePaintSize };
    textSelector_.secondHandle = RectF{ secondHandleOffset, secondHandlePaintSize };
}

void RichEditorPattern::CalculateDefaultHandleHeight(float& height)
{
#ifdef ENABLE_ROSEN_BACKEND
    MeasureContext content;
    content.textContent = "a";
    content.fontSize = TEXT_DEFAULT_FONT_SIZE;
    auto fontweight = StringUtils::FontWeightToString(FontWeight::NORMAL);
    content.fontWeight = fontweight;
    height = std::max(static_cast<float>(RosenRenderCustomPaint::MeasureTextSizeInner(content).Height()), 0.0f);
#endif
}

OffsetF RichEditorPattern::GetGlobalOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, OffsetF());
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto richEditorPaintOffset = host->GetPaintRectOffsetNG(false, true);
    if (selectOverlay_->HasRenderTransform()) {
        richEditorPaintOffset = selectOverlay_->GetPaintOffsetWithoutTransform();
    }
    return richEditorPaintOffset - rootOffset;
}

bool RichEditorPattern::IsSingleHandle()
{
    CHECK_NULL_RETURN(!selectOverlay_->GetIsHandleMoving(), selectOverlay_->IsSingleHandle());
    return GetTextContentLength() == 0 || !IsSelected();
}

bool RichEditorPattern::IsHandlesShow()
{
    return selectOverlay_->IsBothHandlesShow();
}

void RichEditorPattern::ResetSelection()
{
    bool selectNothing = textSelector_.SelectNothing();
    textSelector_.Update(-1, -1);
    if (!selectNothing) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "ResetSelection");
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<RichEditorEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto textSelectInfo = GetSpansInfo(-1, -1, GetSpansMethod::ONSELECT);
        eventHub->FireOnSelect(&textSelectInfo);
        UpdateSelectionType(textSelectInfo);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

bool RichEditorPattern::BetweenSelection(const Offset& globalOffset)
{
    return InRangeRect(globalOffset, { textSelector_.GetTextStart(), textSelector_.GetTextEnd() });
}

bool RichEditorPattern::InRangeRect(const Offset& globalOffset, const std::pair<int32_t, int32_t>& range)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    CHECK_NULL_RETURN(0 <= range.first && range.first < range.second, false);
    auto offset = host->GetPaintRectOffsetNG(false, true);
    auto localOffset = globalOffset - Offset(offset.GetX(), offset.GetY());
    if (selectOverlay_->HasRenderTransform()) {
        localOffset = ConvertGlobalToLocalOffset(globalOffset);
    }
    auto eventHub = host->GetEventHub<EventHub>();
    if (GreatNotEqual(range.second, range.first)) {
        // Determine if the pan location is in the selected area
        auto rangeRects = paragraphs_.GetRects(range.first, range.second);
        auto panOffset = OffsetF(localOffset.GetX(), localOffset.GetY()) - GetTextRect().GetOffset() +
                         OffsetF(0.0, std::min(baselineOffset_, 0.0f));
        for (const auto& rangeRect : rangeRects) {
            if (rangeRect.IsInRegion(PointF(panOffset.GetX(), panOffset.GetY()))) {
                return true;
            }
        }
    }
    return false;
}

bool RichEditorPattern::BetweenSelectedPosition(const Offset& globalOffset)
{
    return copyOption_ != CopyOptions::None && BetweenSelection(globalOffset);
}

void RichEditorPattern::HandleSurfaceChanged(
    int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight, WindowSizeChangeReason type)
{
    if (newWidth != prevWidth || newHeight != prevHeight) {
        TextPattern::HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, type);
        UpdateOriginIsMenuShow(false);
    }
    UpdateCaretInfoToController();
    if (magnifierController_) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
}

void RichEditorPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY)
{
    UpdateCaretInfoToController();
}

void RichEditorPattern::DumpInfo()
{
    auto& dumpLog = DumpLog::GetInstance();
    if (customKeyboardBuilder_) {
        dumpLog.AddDesc(std::string("CustomKeyboard, Attached: ").append(std::to_string(isCustomKeyboardAttached_)));
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    dumpLog.AddDesc(std::string("caret offset: ").append(GetCaretRect().GetOffset().ToString()));
    dumpLog.AddDesc(std::string("caret height: ")
            .append(std::to_string(NearZero(GetCaretRect().Height())
                                       ? richEditorTheme->GetDefaultCaretHeight().ConvertToPx()
                                       : GetCaretRect().Height())));
    dumpLog.AddDesc(std::string("text rect: ").append(richTextRect_.ToString()));
    dumpLog.AddDesc(std::string("content rect: ").append(contentRect_.ToString()));
    auto richEditorPaintOffset = host->GetPaintRectOffsetNG(false, true);
    bool hasRenderTransform = selectOverlay_->HasRenderTransform();
    if (hasRenderTransform) {
        richEditorPaintOffset = selectOverlay_->GetPaintOffsetWithoutTransform();
    }
    dumpLog.AddDesc(std::string("hasRenderTransform: ").append(std::to_string(hasRenderTransform)));
    dumpLog.AddDesc(std::string("richEditorPaintOffset: ").append(richEditorPaintOffset.ToString()));
    auto selectOverlayInfo = selectOverlay_->GetSelectOverlayInfo();
    CHECK_NULL_VOID(selectOverlayInfo);
    dumpLog.AddDesc(std::string("selectOverlay info: ").append(selectOverlayInfo->ToString()));
    dumpLog.AddDesc(std::string("IsAIWrite: ").append(std::to_string(IsShowAIWrite())));
    dumpLog.AddDesc(std::string("keyboardAppearance: ")
            .append(std::to_string(static_cast<int32_t>(keyboardAppearance_))));
}

void RichEditorPattern::RichEditorErrorReport(RichEditorInfo& info)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [info] {
            EventReport::ReportRichEditorInfo(info);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIRichEditorErrorReport");
}

bool RichEditorPattern::HasFocus() const
{
    auto focusHub = GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

void RichEditorPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    if (!HasFocus()) {
        return;
    }
    auto context = GetHost()->GetContext();
    CHECK_NULL_VOID(context);
    auto richEditorTheme = context->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    textFieldManager->SetClickPosition({ offset.GetX() + caretOffset.GetX(), offset.GetY() + caretOffset.GetY() });
    textFieldManager->SetHeight(NearZero(caretHeight)
                                    ? richEditorTheme->GetDefaultCaretHeight().ConvertToPx()
                                    : caretHeight);
    textFieldManager->SetClickPositionOffset(safeAreaManager->GetKeyboardOffset());
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        textFieldManager->SetUsingCustomKeyboardAvoid(keyboardAvoidance_);
    }
    if (!isTextChange_) {
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ScrollToSafeArea();
        },
        TaskExecutor::TaskType::UI, "ArkUIRichEditorScrollToSafeArea", PriorityType::VIP);
}

bool RichEditorPattern::IsDisabled() const
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return !eventHub->IsEnabled();
}

void RichEditorPattern::MouseDoubleClickParagraphEnd(int32_t& index)
{
    bool isMouseDoubleClick = caretUpdateType_ == CaretUpdateType::DOUBLE_CLICK && sourceType_ == SourceType::MOUSE;
    CHECK_NULL_VOID(isMouseDoubleClick);
    auto paragraphEndPos = GetParagraphEndPosition(index);
    auto paragraphBeginPos = GetParagraphBeginPosition(index);
    bool isBeginEqualEnd = paragraphBeginPos == paragraphEndPos;
    CHECK_NULL_VOID(!isBeginEqualEnd);
    if (index == paragraphEndPos) {
        index -= 1;
    }
}

void RichEditorPattern::AdjustSelectionExcludeSymbol(int32_t& start, int32_t& end)
{
    AdjustSelectorForSymbol(start, HandleType::FIRST, SelectorAdjustPolicy::EXCLUDE);
    AdjustSelectorForSymbol(end, HandleType::SECOND, SelectorAdjustPolicy::EXCLUDE);
}

void RichEditorPattern::InitSelection(const Offset& pos)
{
    auto [currentPosition, selectType] = JudgeSelectType(pos);
    switch (selectType) {
        case SelectType::SELECT_NOTHING:
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "select nothing currentPos=%{public}d", currentPosition);
            textSelector_.Update(currentPosition, currentPosition);
            return;
        case SelectType::SELECT_BACKWARD:
            currentPosition = std::max(0, currentPosition - 1);
            break;
        case SelectType::SELECT_FORWARD:
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "exception select type");
    }
    int32_t nextPosition = std::min(currentPosition + 1, GetTextContentLength());
    AdjustSelectionExcludeSymbol(currentPosition, nextPosition);
    if (!IsCustomSpanInCaretPos(currentPosition, true)) {
        AdjustWordSelection(currentPosition, nextPosition);
    }
    AdjustSelector(currentPosition, nextPosition);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "init select [%{public}d--%{public}d]", currentPosition, nextPosition);
    textSelector_.Update(currentPosition, nextPosition);
    if (IsSelectEmpty(currentPosition, nextPosition)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "select rect is empty, select nothing");
        textSelector_.Update(currentPosition, currentPosition);
    }
}

std::pair<int32_t, SelectType> RichEditorPattern::JudgeSelectType(const Offset& pos)
{
    auto positionWithAffinity = paragraphs_.GetGlyphPositionAtCoordinate(pos);
    auto currentPosition = (GetTextContentLength() == 0) ? 0 : static_cast<int32_t>(positionWithAffinity.position_);
    auto selectType = SelectType::SELECT_NOTHING;
    CHECK_NULL_RETURN(GetTextContentLength() != 0, std::make_pair(currentPosition, selectType));
    bool isNeedSkipLineSeparator = !editingLongPress_ && IsSelectEmpty(currentPosition, currentPosition + 1);
    if (isNeedSkipLineSeparator && AdjustIndexSkipLineSeparator(currentPosition)) {
        return std::make_pair(currentPosition, SelectType::SELECT_BACKWARD);
    }
    auto height = paragraphs_.GetHeight();
    if (GreatNotEqual(pos.GetY(), height)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "touchPosY[%{public}f] > paragraphsHeight[%{public}f]", pos.GetY(), height);
        IF_TRUE(!editingLongPress_, selectType = SelectType::SELECT_BACKWARD);
        return std::make_pair(GetTextContentLength(), selectType);
    }
    TextAffinity currentAffinity = positionWithAffinity.affinity_;
    bool isTouchLineEnd = currentAffinity == TextAffinity::UPSTREAM && !IsTouchBeforeCaret(currentPosition, pos);
    if (editingLongPress_ && isTouchLineEnd) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "touchLineEnd select nothing currentAffinity=%{public}d", currentAffinity);
        return std::make_pair(currentPosition, selectType);
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "currentPosition=%{public}d, currentAffinity=%{public}d",
        currentPosition, currentAffinity);
    selectType = (currentAffinity == TextAffinity::UPSTREAM) ? SelectType::SELECT_BACKWARD : SelectType::SELECT_FORWARD;
    return std::make_pair(currentPosition, selectType);
}

bool RichEditorPattern::IsSelectEmpty(int32_t start, int32_t end)
{
    auto selectedRects = paragraphs_.GetRects(start, end);
    return selectedRects.empty() || (selectedRects.size() == 1 && NearZero((selectedRects[0].Width())));
}

bool RichEditorPattern::AdjustIndexSkipLineSeparator(int32_t& currentPosition)
{
    std::u16string contentText;
    for (auto iter = spans_.cbegin(); iter != spans_.cend(); iter++) {
        contentText.append((*iter)->content);
        CHECK_NULL_BREAK(currentPosition > (*iter)->position);
    }
    auto contentLength = static_cast<int32_t>(contentText.length());
    if (currentPosition > contentLength) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "currentPosition=%{public}d but contentLength=%{public}d",
            currentPosition, contentLength);
        return false;
    }
    auto index = currentPosition - 1;
    while (index > 0) {
        CHECK_NULL_BREAK(contentText[index] == u'\n');
        index--;
    }
    if (index != currentPosition - 1) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "skip lineSeparator %{public}d->%{public}d", currentPosition, index + 1);
        currentPosition = index + 1;
        return true;
    }
    return false;
}

bool RichEditorPattern::AdjustIndexSkipSpace(int32_t& currentPosition, const MoveDirection direction)
{
    bool isBackward = (direction == MoveDirection::BACKWARD);
    std::u16string contentText;
    GetContentBySpans(contentText);
    auto contentLength = static_cast<int32_t>(contentText.length());
    bool isPositionInvalid = (isBackward && currentPosition == 0) || (!isBackward && currentPosition == contentLength);
    if (isPositionInvalid) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "AdjustIndexSkipSpace position=%{public}d but contentLength=%{public}d",
            currentPosition, contentLength);
        return false;
    }
    int32_t index = isBackward ? (currentPosition - 1) : currentPosition;
    while (isBackward ? index >= 0 : index < contentLength) {
        CHECK_NULL_BREAK(contentText[index] == u' ' && GetSpanType(index) == SpanItemType::NORMAL);
        isBackward ? index-- : index++;
    }
    int32_t adjustedIndex = isBackward ? (index + 1) : index;
    if (adjustedIndex != currentPosition) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "skip space %{public}d->%{public}d", currentPosition, adjustedIndex);
        currentPosition = adjustedIndex;
        return true;
    }
    return false;
}

bool RichEditorPattern::ResetOnInvalidSelection(int32_t start, int32_t end)
{
    if (start < end) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetSelection failed, the selected area is empty.");
    CloseSelectOverlay();
    ResetSelection();
    StartTwinkling();
    return true;
}

bool RichEditorPattern::IsShowHandle()
{
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richEditorTheme, false);
    return !richEditorTheme->IsRichEditorShowHandle();
}

void RichEditorPattern::UpdateSelectionInfo(int32_t start, int32_t end)
{
    UpdateSelectionType(GetSpansInfo(start, end, GetSpansMethod::ONSELECT));
    auto selectOverlayInfo = selectOverlay_->GetSelectOverlayInfo();
    textResponseType_ = selectOverlayInfo
                        ? static_cast<TextResponseType>(selectOverlayInfo->menuInfo.responseType.value_or(0))
                        : TextResponseType::LONG_PRESS;
    if (IsShowHandle() && !IsUsingMouse()) {
        ResetIsMousePressed();
        sourceType_ = SourceType::TOUCH;
    }
}

void RichEditorPattern::SetSelection(int32_t start, int32_t end, const std::optional<SelectionOptions>& options,
    bool isForward)
{
    bool hasFocus = HasFocus();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "setSelection, range=[%{public}d,%{public}d], hasFocus=%{public}d, "
        "isEditing=%{public}d", start, end, hasFocus, isEditing_);
    CHECK_NULL_VOID(hasFocus);
    if (IsPreviewTextInputting()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "SetSelection failed for previewText inputting");
        return;
    }
    if (start == -1 && end == -1) {
        start = 0;
        end = GetTextContentLength();
    } else {
        start = std::clamp(start, 0, GetTextContentLength());
        end = std::clamp(end, 0, GetTextContentLength());
    }
    CHECK_NULL_VOID(!ResetOnInvalidSelection(start, end));
    UpdateSelector(start, end);

    if (textSelector_.IsValid() && !textSelector_.StartEqualToDest()) {
        StopTwinkling();
        if (start != textSelector_.GetTextStart() || end != textSelector_.GetTextEnd()) {
            FireOnSelect(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
        }
    }
    SetCaretPosition(isForward ? textSelector_.GetTextStart() : textSelector_.GetTextEnd());
    MoveCaretToContentRect();
    CalculateHandleOffsetAndShowOverlay();
    UpdateSelectionInfo(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    ProcessOverlayOnSetSelection(options);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::ProcessOverlayOnSetSelection(const std::optional<SelectionOptions>& options)
{
    if (options.has_value()) {
        auto handlePolicy = options.value().handlePolicy;
        IF_TRUE(handlePolicy == HandlePolicy::SHOW, selectOverlay_->ProcessOverlay({ .animation = true }));
        IF_TRUE(handlePolicy == HandlePolicy::HIDE, CloseSelectOverlay());
        CHECK_NULL_VOID(handlePolicy == HandlePolicy::DEFAULT);
    }
    if (!IsShowHandle()) {
        CloseSelectOverlay();
    } else if (!options.has_value() || options.value().menuPolicy == MenuPolicy::DEFAULT) {
        selectOverlay_->ProcessOverlay({ .menuIsShow = selectOverlay_->IsCurrentMenuVisibile(),
            .animation = true, .requestCode = REQUEST_RECREATE });
        IF_PRESENT(magnifierController_, RemoveMagnifierFrameNode());
    } else if (options.value().menuPolicy == MenuPolicy::HIDE) {
        if (selectOverlay_->IsUsingMouse()) {
            CloseSelectOverlay();
        } else {
            selectOverlay_->ProcessOverlay({ .menuIsShow = false, .animation = true });
        }
    } else if (options.value().menuPolicy == MenuPolicy::SHOW) {
        if (selectOverlay_->IsUsingMouse() || sourceType_ == SourceType::MOUSE) {
            selectionMenuOffsetByMouse_ = selectionMenuOffsetClick_;
        }
        selectOverlay_->ProcessOverlay({ .animation = true, .requestCode = REQUEST_RECREATE });
        IF_PRESENT(magnifierController_, RemoveMagnifierFrameNode());
    }
}

void RichEditorPattern::BindSelectionMenu(TextResponseType type, TextSpanType richEditorType,
    std::function<void()>& menuBuilder, const SelectMenuParam& menuParam)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "BindSelectionMenu spanType = %{public}d, responseType = %{public}d",
        richEditorType, type);
    TextPattern::BindSelectionMenu(richEditorType, type, menuBuilder, menuParam);
}

RefPtr<NodePaintMethod> RichEditorPattern::CreateNodePaintMethod()
{
    if (!contentMod_) {
        contentMod_ = MakeRefPtr<RichEditorContentModifier>(textStyle_, &paragraphs_, WeakClaim(this));
    }
    if (!overlayMod_) {
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
            scrollBarModifier->SetRect(scrollBar->GetActiveRect());
            scrollBarModifier->SetPositionMode(scrollBar->GetPositionMode());
            SetScrollBarOverlayModifier(scrollBarModifier);
        }
        SetEdgeEffect(EdgeEffect::FADE, GetAlwaysEnabled());
        SetEdgeEffect();
        overlayMod_ = AceType::MakeRefPtr<RichEditorOverlayModifier>(
            WeakClaim(this), GetScrollBarOverlayModifier(), GetScrollEdgeEffect());
    }

    if (GetIsCustomFont()) {
        contentMod_->SetIsCustomFont(true);
    }
    return MakeRefPtr<RichEditorPaintMethod>(WeakClaim(this), &paragraphs_, baselineOffset_, contentMod_, overlayMod_);
}

int32_t RichEditorPattern::GetHandleIndex(const Offset& offset) const
{
    CHECK_NULL_RETURN(!isShowPlaceholder_, 0);
    return paragraphs_.GetIndex(Offset(offset.GetX() + contentRect_.GetX() - richTextRect_.GetX(),
        offset.GetY() + contentRect_.GetY() - richTextRect_.GetY()));
}

std::vector<RectF> RichEditorPattern::GetTextBoxes()
{
    auto selectedRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    std::vector<RectF> res;
    res.reserve(selectedRects.size());
    for (auto&& rect : selectedRects) {
        res.emplace_back(rect);
    }
    if (!res.empty() && paragraphs_.IsSelectLineHeadAndUseLeadingMargin(textSelector_.GetTextStart())) {
        // To make drag screenshot include LeadingMarginPlaceholder when not single line
        if (res.front().GetY() != res.back().GetY()) {
            res.front().SetLeft(0.0f);
        }
    }
    return res;
}

float RichEditorPattern::GetLineHeight() const
{
    auto selectedRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    CHECK_NULL_RETURN(selectedRects.size(), 0.0f);
    return selectedRects.front().Height();
}

size_t RichEditorPattern::GetLineCount() const
{
    return paragraphs_.GetLineCount();
}

TextLineMetrics RichEditorPattern::GetLineMetrics(int32_t lineNumber)
{
    if (lineNumber < 0 || GetLineCount() == 0 || static_cast<uint32_t>(lineNumber) > GetLineCount() - 1) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT,
                "GetLineMetrics failed, lineNumber not between 0 and max lines:%{public}d", lineNumber);
        return TextLineMetrics();
    }
    auto lineMetrics = paragraphs_.GetLineMetrics(lineNumber);
    const auto& textRect = GetTextRect();
    lineMetrics.x += textRect.GetX();
    lineMetrics.y += textRect.GetY();
    lineMetrics.baseline += textRect.GetY();
    return lineMetrics;
}

std::vector<ParagraphManager::TextBox> RichEditorPattern::GetRectsForRange(
    int32_t start, int32_t end, RectHeightStyle heightStyle, RectWidthStyle widthStyle)
{
    if (start < 0 || end < 0 || start > end) {
        return {};
    }
    std::vector<ParagraphManager::TextBox> textBoxes =
        paragraphs_.GetRectsForRange(start, end, heightStyle, widthStyle);
    const auto& textRect = richTextRect_;
    std::vector<ParagraphManager::TextBox> adjustedTextBoxes;
    for (auto& textBox : textBoxes) {
        ParagraphManager::TextBox adjustedTextBox = textBox;
        adjustedTextBox.rect_.SetLeft(textBox.rect_.Left() + textRect.Left());
        adjustedTextBox.rect_.SetTop(textBox.rect_.Top() + textRect.Top());
        adjustedTextBoxes.push_back(adjustedTextBox);
    }
    return adjustedTextBoxes;
}

float RichEditorPattern::GetLetterSpacing() const
{
    auto selectedRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    CHECK_NULL_RETURN(!selectedRects.empty(), 0.0f);
    return selectedRects.front().Width();
}

void RichEditorPattern::UpdateSelectMenuInfo(SelectMenuInfo& menuInfo)
{
    bool isSupportCameraInput = false;
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    isSupportCameraInput =
        inputMethod && inputMethod->IsInputTypeSupported(MiscServices::InputType::CAMERA_INPUT);
#endif
    menuInfo.showCameraInput = !IsSelected() && isSupportCameraInput && !customKeyboardBuilder_;
    if (textResponseType_.has_value()) {
        menuInfo.responseType = static_cast<int32_t>(textResponseType_.value());
    }
}

RectF RichEditorPattern::GetCaretRect() const
{
    RectF rect;
    CHECK_NULL_RETURN(overlayMod_, rect);
    auto richEditorOverlay = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_RETURN(richEditorOverlay, rect);
    rect.SetOffset(richEditorOverlay->GetCaretOffset());
    rect.SetHeight(richEditorOverlay->GetCaretHeight());
    return rect;
}

void RichEditorPattern::ScrollToSafeArea() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->UsingCaretAvoidMode()) {
        // using TriggerAvoidOnCaretChange instead in CaretAvoidMode
        return;
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->ScrollTextFieldToSafeArea();
}

void RichEditorPattern::InitScrollablePattern()
{
    auto layoutProperty = GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto barState = layoutProperty->GetDisplayModeValue(DisplayMode::AUTO);
    CHECK_NULL_VOID(!barDisplayMode_.has_value() || barDisplayMode_.value() != barState);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "setBarState=%{public}d", barState);
    barDisplayMode_ = barState;
    if (!GetScrollableEvent()) {
        AddScrollEvent();
    }
    SetAxis(Axis::VERTICAL);
    if (barState != DisplayMode::AUTO) {
        barState = DisplayMode::ON;
    }
    SetScrollBar(barState);
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        auto richEditorTheme = GetTheme<RichEditorTheme>();
        CHECK_NULL_VOID(richEditorTheme);
        scrollBar->SetMinHeight(richEditorTheme->GetScrollbarMinHeight());
    }
    if (overlayMod_) {
        UpdateScrollBarOffset();
    }
    auto& paddingProperty = layoutProperty->GetPaddingProperty();
    if (paddingProperty) {
        auto offsetY = paddingProperty->top.has_value() ? paddingProperty->top->GetDimension().ConvertToPx() : 0.0f;
        auto offsetX = paddingProperty->left.has_value() ? paddingProperty->left->GetDimension().ConvertToPx() : 0.0f;
        richTextRect_.SetOffset(OffsetF(offsetX, offsetY));
    }
}

void RichEditorPattern::ProcessInnerPadding()
{
    auto theme = GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto themePadding = theme->GetPadding();
    auto& paddingProp = layoutProperty->GetPaddingProperty();
    auto left = !paddingProp ? CalcLength(themePadding.Left()).GetDimension()
                             : paddingProp->left.value_or(CalcLength(themePadding.Left())).GetDimension();
    auto top = !paddingProp ? CalcLength(themePadding.Top()).GetDimension()
                            : paddingProp->top.value_or(CalcLength(themePadding.Top())).GetDimension();
    auto bottom = !paddingProp ? CalcLength(themePadding.Bottom()).GetDimension()
                               : paddingProp->bottom.value_or(CalcLength(themePadding.Bottom())).GetDimension();
    auto right = !paddingProp ? CalcLength(themePadding.Right()).GetDimension()
                              : paddingProp->right.value_or(CalcLength(themePadding.Right())).GetDimension();
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(top);
    paddings.bottom = NG::CalcLength(bottom);
    paddings.left = NG::CalcLength(left);
    paddings.right = NG::CalcLength(right);
    layoutProperty->UpdatePadding(paddings);
}

void RichEditorPattern::UpdateScrollStateAfterLayout(bool shouldDisappear)
{
    bool hasTextOffsetChanged = false;
    if (GreatNotEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        auto offset = richTextRect_.GetOffset();
        offset.AddY(contentRect_.GetY() - richTextRect_.GetY());
        richTextRect_.SetOffset(offset);
        hasTextOffsetChanged = true;
    }
    if (GreatNotEqual(richTextRect_.Height(), contentRect_.Height()) &&
        LessNotEqual(richTextRect_.Bottom(), contentRect_.Bottom())) {
        auto offset = richTextRect_.GetOffset();
        offset.AddY(contentRect_.Bottom() - richTextRect_.Bottom());
        richTextRect_.SetOffset(offset);
        hasTextOffsetChanged = true;
    }
    if (LessOrEqual(richTextRect_.Height(), contentRect_.Height()) &&
        LessNotEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        richTextRect_.SetOffset(contentRect_.GetOffset());
        hasTextOffsetChanged = true;
    }
    if (hasTextOffsetChanged) {
        UpdateChildrenOffset();
    }
    StopScrollable();
    CheckScrollable();
    if (overlayMod_) {
        UpdateScrollBarOffset();
    }
    auto scrollBar = GetScrollBar();
    CHECK_NULL_VOID(scrollBar);

    if (isFirstCallOnReady_) {
        isFirstCallOnReady_ = false;
        scrollBar->ScheduleDisappearDelayTask();
        return;
    }
    if (shouldDisappear) {
        scrollBar->ScheduleDisappearDelayTask();
    }
}

bool RichEditorPattern::OnScrollCallback(float offset, int32_t source)
{
    auto scrollBar = GetScrollBar();
    if (source == SCROLL_FROM_START) {
        IF_PRESENT(scrollBar, PlayScrollBarAppearAnimation());
        if (SelectOverlayIsOn()) {
            selectOverlay_->HideMenu(true);
        }
        ScrollablePattern::RecordScrollEvent(Recorder::EventType::SCROLL_START);
        UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
            AceType::WeakClaim(this), ScrollEventType::SCROLL_START);
        return true;
    }
    if (IsReachedBoundary(offset)) {
        return false;
    }
    if (scrollBar && source == SCROLL_FROM_JUMP) {
        scrollBar->PlayScrollBarAppearAnimation();
        scrollBar->ScheduleDisappearDelayTask();
    }
    auto newOffset = MoveTextRect(offset);
    MoveFirstHandle(newOffset);
    MoveSecondHandle(newOffset);
    dataDetectorAdapter_->aiSpanRects_.clear();
    return true;
}

float RichEditorPattern::GetCrossOverHeight() const
{
    if (!keyboardAvoidance_ || !contentChange_ || AceApplicationInfo::GetInstance().
        GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN)) {
        return 0.0f;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto rootHeight = pipeline->GetRootHeight();
    auto keyboardY = rootHeight - pipeline->GetSafeAreaManager()->GetKeyboardInset().Length();
    if (GreatOrEqual(keyboardY, rootHeight)) {
        return 0.0f;
    }
    float height = contentRect_.Bottom();
    float frameY = parentGlobalOffset_.GetY() + contentRect_.GetY();
    float bottom = frameY + height;
    auto crossOverHeight = bottom - keyboardY;
    if (LessOrEqual(crossOverHeight, 0.0f)) {
        return 0.0f;
    }
    return crossOverHeight;
}

float RichEditorPattern::MoveTextRect(float offset)
{
    auto keyboardOffset = GetCrossOverHeight();
    if (GreatNotEqual(richTextRect_.Height(), contentRect_.Height() - keyboardOffset)) {
        if (GreatNotEqual(richTextRect_.GetY() + offset, contentRect_.GetY())) {
            offset = contentRect_.GetY() - richTextRect_.GetY();
        } else if (LessNotEqual(richTextRect_.Bottom() + offset, contentRect_.Bottom() - keyboardOffset)) {
            offset = contentRect_.Bottom() - keyboardOffset - richTextRect_.Bottom();
        }
    } else if (!NearEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        offset = contentRect_.GetY() - richTextRect_.GetY();
    } else {
        return 0.0f;
    }
    if (NearEqual(offset, 0.0f)) {
        return offset;
    }
    scrollOffset_ = richTextRect_.GetY() + offset;
    richTextRect_.SetOffset(OffsetF(richTextRect_.GetX(), scrollOffset_));
    UpdateScrollBarOffset();
    UpdateChildrenOffset();
    if (auto host = GetHost(); host) {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    return offset;
}

void RichEditorPattern::MoveFirstHandle(float offset)
{
    if (SelectOverlayIsOn() && !NearEqual(offset, 0.0f)) {
        textSelector_.selectionBaseOffset.AddY(offset);
        auto firstHandleOffset = textSelector_.firstHandle.GetOffset();
        firstHandleOffset.AddY(offset);
        textSelector_.firstHandle.SetOffset(firstHandleOffset);
        selectOverlay_->UpdateFirstHandleOffset();
    }
}

void RichEditorPattern::MoveSecondHandle(float offset)
{
    if (SelectOverlayIsOn() && !NearEqual(offset, 0.0f)) {
        textSelector_.selectionDestinationOffset.AddY(offset);
        auto secondHandleOffset = textSelector_.secondHandle.GetOffset();
        secondHandleOffset.AddY(offset);
        textSelector_.secondHandle.SetOffset(secondHandleOffset);
        selectOverlay_->UpdateSecondHandleOffset();
    }
}

void RichEditorPattern::SetNeedMoveCaretToContentRect()
{
    CHECK_NULL_VOID(isRichEditorInit_);
    needMoveCaretToContentRect_ = true;
}

void RichEditorPattern::MoveCaretToContentRect()
{
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    MoveCaretToContentRect(caretOffset, caretHeight);
}

void RichEditorPattern::MoveCaretToContentRect(const OffsetF& caretOffset, float caretHeight)
{
    auto keyboardOffset = GetCrossOverHeight();
    auto contentRect = GetTextContentRect();
    auto textRect = GetTextRect();
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarAppearAnimation();
        scrollBar->ScheduleDisappearDelayTask();
    }
    if (LessOrEqual(textRect.Height(), contentRect.Height() - keyboardOffset) || isShowPlaceholder_) {
        return;
    }
    if (LessNotEqual(contentRect.GetSize().Height(), caretHeight) &&
        !NearEqual(caretOffset.GetY() + caretHeight, contentRect.Bottom() - keyboardOffset)) {
        OnScrollCallback(contentRect.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight, SCROLL_FROM_NONE);
    }
    if (LessNotEqual(contentRect.GetSize().Height(), caretHeight)) {
        return;
    }
    if (LessNotEqual(caretOffset.GetY(), contentRect.GetY())) {
        if (LessOrEqual(caretOffset.GetX(), GetTextRect().GetX())) {
            OnScrollCallback(contentRect.GetY() - caretOffset.GetY() + caretHeight, SCROLL_FROM_NONE);
        } else {
            OnScrollCallback(contentRect.GetY() - caretOffset.GetY(), SCROLL_FROM_NONE);
        }
    } else if (GreatNotEqual(caretOffset.GetY() + caretHeight, contentRect.Bottom() - keyboardOffset)) {
        auto distance = contentRect.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight -
            CARET_BOTTOM_DISTANCE.ConvertToPx();
        OnScrollCallback(distance, SCROLL_FROM_NONE);
    }
}

void RichEditorPattern::MoveCaretToContentRect(float offset, int32_t source)
{
    float caretHeight = 0.0f;
    auto caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
    auto keyboardOffset = GetCrossOverHeight();
    auto contentRect = GetTextContentRect();
    auto distance = contentRect.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight - offset;
    OnScrollCallback(distance, source);
}

bool RichEditorPattern::IsCaretInContentArea()
{
    float caretHeight = 0.0f;
    auto caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
    auto keyboardOffset = GetCrossOverHeight();
    auto contentRect = GetTextContentRect();
    return GreatNotEqual(caretOffset.GetY() + caretHeight, contentRect.GetY())
        && LessNotEqual(caretOffset.GetY(), contentRect.Bottom() - keyboardOffset);
}

void RichEditorPattern::UpdateScrollBarOffset()
{
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    Size size(frameRect_.Width(), frameRect_.Height());
    auto verticalGap = frameRect_.Height() - contentRect_.Height();
    UpdateScrollBarRegion(
        contentRect_.GetY() - richTextRect_.GetY(), richTextRect_.Height() + verticalGap, size, Offset(0.0, 0.0));
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::OnScrollEndCallback()
{
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->ScheduleDisappearDelayTask();
    }
    CHECK_NULL_VOID(!selectOverlay_->GetIsHandleMoving());
    if (IsSelectAreaVisible()) {
        auto info = selectOverlay_->GetSelectOverlayInfo();
        if (info && info->menuInfo.menuBuilder) {
            selectOverlay_->ProcessOverlay({ .animation = true });
        } else {
            selectOverlay_->UpdateMenuOffset();
            selectOverlay_->ShowMenu();
        }
    }
    if (AnimateStoped()) {
        ScrollablePattern::RecordScrollEvent(Recorder::EventType::SCROLL_STOP);
        UIObserverHandler::GetInstance().NotifyScrollEventStateChange(
            AceType::WeakClaim(this), ScrollEventType::SCROLL_STOP);
    }
}

bool RichEditorPattern::IsSelectAreaVisible()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManager, false);
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    auto selectArea = GetSelectArea(SelectRectsType::ALL_LINES);

    return !selectArea.IsEmpty() && LessNotEqual(selectArea.Top(), keyboardInsert.start);
}

bool RichEditorPattern::IsReachedBoundary(float offset)
{
    auto keyboardOffset = GetCrossOverHeight();
    return (NearEqual(richTextRect_.GetY(), contentRect_.GetY()) && GreatNotEqual(offset, 0.0f)) ||
           (NearEqual(richTextRect_.GetY() + richTextRect_.Height(),
                contentRect_.GetY() + contentRect_.Height() - keyboardOffset) &&
               LessNotEqual(offset, 0.0f));
}

void RichEditorPattern::CheckScrollable()
{
    auto gestureHub = GetGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    scrollable_ = GetTextContentLength() > 0 && GreatNotEqual(richTextRect_.Height(), contentRect_.Height());
    SetScrollEnabled(scrollable_);
}

void RichEditorPattern::UpdateChildrenOffset()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<int32_t> placeholderIndex;
    for (const auto& child : spans_) {
        if (!child) {
            continue;
        }
        if (AceType::InstanceOf<ImageSpanItem>(child) || AceType::InstanceOf<PlaceholderSpanItem>(child)) {
            placeholderIndex.emplace_back(child->placeholderIndex);
        }
    }
    if (spans_.empty() || placeholderIndex.empty()) {
        return;
    }
    size_t index = 0;
    std::vector<RectF> rectsForPlaceholders = paragraphs_.GetPlaceholderRects();
    auto childrenNodes = host->GetChildren();
    auto textOffset = GetTextRect().GetOffset();
    for (const auto& child : childrenNodes) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        if (!childNode) {
            continue;
        }
        if (!(childNode->GetPattern<ImagePattern>() || childNode->GetPattern<PlaceholderSpanPattern>())) {
            continue;
        }
        if (isSpanStringMode_) {
            auto imageSpanNode = AceType::DynamicCast<ImageSpanNode>(child);
            if (imageSpanNode && imageSpanNode->GetSpanItem()) {
                index = static_cast<uint32_t>(imageSpanNode->GetSpanItem()->placeholderIndex);
            }
        }
        if (index >= rectsForPlaceholders.size()) {
            break;
        }
        auto rect = rectsForPlaceholders.at(index);
        auto geometryNode = childNode->GetGeometryNode();
        if (geometryNode) {
            geometryNode->SetMarginFrameOffset(textOffset + OffsetF(rect.Left(), rect.Top()));
            childNode->ForceSyncGeometryNode();
            childNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        ++index;
    }
}

void RichEditorPattern::AutoScrollByEdgeDetection(AutoScrollParam param, OffsetF offset, EdgeDetectionStrategy strategy)
{
    if (NearEqual(prevAutoScrollOffset_.GetY(), offset.GetY())) {
        return;
    }
    prevAutoScrollOffset_ = offset;
    auto contentRect = GetTextContentRect();
    auto isDragging = param.autoScrollEvent == AutoScrollEvent::DRAG;
    float edgeThreshold = isDragging ? AUTO_SCROLL_DRAG_EDGE_DISTANCE.ConvertToPx()
                                     : AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();
    auto maxHeight = isDragging ? frameRect_.Height() : contentRect.Height();
    if (GreatNotEqual(edgeThreshold * 2, maxHeight)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AutoScrollByEdgeDetection: hot area height is great than max height.");
        return;
    }
    float topEdgeThreshold = isDragging ? edgeThreshold : edgeThreshold + contentRect.GetY();
    float bottomThreshold = isDragging ? frameRect_.Height() - edgeThreshold : contentRect.Bottom() - edgeThreshold;
    if (param.autoScrollEvent == AutoScrollEvent::HANDLE) {
        auto handleTopOffset = offset;
        auto handleBottomOffset = OffsetF(offset.GetX(), offset.GetY() + param.handleRect.Height());
        if (GreatNotEqual(handleBottomOffset.GetY(), bottomThreshold)) {
            param.offset = bottomThreshold - handleBottomOffset.GetY();
            ScheduleAutoScroll(param);
        } else if (LessNotEqual(handleTopOffset.GetY(), topEdgeThreshold)) {
            param.offset = topEdgeThreshold - handleTopOffset.GetY();
            ScheduleAutoScroll(param);
        } else {
            StopAutoScroll();
        }
        return;
    }
    // drag and mouse
    if (GreatNotEqual(offset.GetY(), bottomThreshold)) {
        param.offset = isDragging ? -CalcDragSpeed(bottomThreshold, frameRect_.Height(), offset.GetY())
                                  : bottomThreshold - offset.GetY();
        ScheduleAutoScroll(param);
    } else if (LessNotEqual(offset.GetY(), topEdgeThreshold)) {
        param.offset = isDragging ? CalcDragSpeed(topEdgeThreshold, 0, offset.GetY())
                                  : topEdgeThreshold - offset.GetY();
        ScheduleAutoScroll(param);
    } else {
        StopAutoScroll();
    }
}

float RichEditorPattern::CalcDragSpeed(float hotAreaStart, float hotAreaEnd, float point)
{
    auto distanceRatio = (point - hotAreaStart) / (hotAreaEnd - hotAreaStart);
    auto speedFactor = Curves::SHARP->MoveInternal(distanceRatio);
    return ((MAX_DRAG_SCROLL_SPEED * speedFactor) / TIME_UNIT) * AUTO_SCROLL_INTERVAL;
}

void RichEditorPattern::ScheduleAutoScroll(AutoScrollParam param)
{
    if (GreatNotEqual(param.offset, 0.0f) && IsReachTop()) {
        return;
    }
    if (LessNotEqual(param.offset, 0.0f) && IsReachBottom()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (param.isFirstRun_) {
        param.isFirstRun_ = false;
        currentScrollParam_ = param;
        if (isAutoScrollRunning_) {
            return;
        }
    }
    autoScrollTask_.Reset([weak = WeakClaim(this)]() {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnAutoScroll(client->currentScrollParam_);
        if (client->IsReachTop() || client->IsReachBottom()) {
            client->StopAutoScroll();
        }
    });
    isAutoScrollRunning_ = true;
    taskExecutor->PostDelayedTask(autoScrollTask_, TaskExecutor::TaskType::UI, AUTO_SCROLL_INTERVAL,
        "ArkUIRichEditorScheduleAutoScroll");
}

void RichEditorPattern::OnAutoScroll(AutoScrollParam param)
{
    if (param.showScrollbar) {
        auto scrollBar = GetScrollBar();
        IF_PRESENT(scrollBar, PlayScrollBarAppearAnimation());
        param.showScrollbar = false;
    }
    CHECK_NULL_VOID(param.autoScrollEvent != AutoScrollEvent::NONE);
    auto newOffset = MoveTextRect(param.offset);
    switch (param.autoScrollEvent) {
        case AutoScrollEvent::CARET:
            break;
        case AutoScrollEvent::HANDLE: {
            param.isFirstHandle ? MoveSecondHandle(newOffset) : MoveFirstHandle(newOffset);
            selectOverlay_->OnHandleMove(param.handleRect, param.isFirstHandle);
            break;
        }
        case AutoScrollEvent::DRAG:
            break;
        case AutoScrollEvent::MOUSE: {
            auto textOffset = ConvertTouchOffsetToTextOffset(param.eventOffset);
            int32_t extend = (GetTextContentLength() == 0) ? 0 : paragraphs_.GetIndex(textOffset);
            UpdateSelector(textSelector_.baseOffset, extend);
            SetCaretPosition(std::max(textSelector_.baseOffset, extend));
            break;
        }
        default:
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Unsupported auto scroll event type");
            return;
    }
    CHECK_NULL_VOID(!NearEqual(newOffset, 0.0f));
    ScheduleAutoScroll(param);
}

void RichEditorPattern::StopAutoScroll()
{
    isAutoScrollRunning_ = false;
    autoScrollTask_.Cancel();
    prevAutoScrollOffset_ = OffsetF(0.0f, 0.0f);
    auto scrollBar = GetScrollBar();
    IF_PRESENT(scrollBar, ScheduleDisappearDelayTask());
}

bool RichEditorPattern::NeedAiAnalysis(
    const CaretUpdateType targeType, const int32_t pos, const int32_t& spanStart, const std::string& content)
{
    if (spanStart < 0) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "NeedAiAnalysis -spanStart:%{public}d, return!", spanStart);
        return false;
    }

    if (!InputAIChecker::NeedAIAnalysis(content.empty(), targeType, lastClickTimeStamp_ - lastAiPosTimeStamp_)) {
        return false;
    }

    if (IsClickBoundary(pos) && targeType == CaretUpdateType::PRESSED) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "NeedAiAnalysis IsClickBoundary, return!");
        return false;
    }
    EmojiRelation relation = GetEmojiRelation(pos);
    if (relation == EmojiRelation::IN_EMOJI || relation == EmojiRelation::MIDDLE_EMOJI ||
        relation == EmojiRelation::BEFORE_EMOJI) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "NeedAiAnalysis emoji relation=%{public}d, return!", relation);
        return false;
    }
    return true;
}

void RichEditorPattern::AdjustCursorPosition(int32_t& pos)
{
    // the rich text has some spans, the pos is belong to the whole richtext content, should use (pos - spanStarint)
    int32_t spanStart = -1;
    // get the span text by the position, maybe text is empty
    std::string content = GetPositionSpansText(pos, spanStart);

    if (NeedAiAnalysis(CaretUpdateType::PRESSED, pos, spanStart, content)) {
        int32_t aiPos = pos - spanStart;
        DataDetectorMgr::GetInstance().AdjustCursorPosition(aiPos, content, lastAiPosTimeStamp_, lastClickTimeStamp_);
        if (aiPos < 0) {
            return;
        }
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get ai pos:%{public}d--spanStart%{public}d", aiPos, spanStart);
        pos = aiPos + spanStart;
    }
}

bool RichEditorPattern::AdjustWordSelection(int32_t& start, int32_t& end)
{
    // the rich text has some spans, the pos is belong to the whole richtext content, should use (pos - spanStarint)
    int32_t spanStart = -1;
    // get the span text by the position, maybe text is empty
    std::string content = GetPositionSpansText(start, spanStart);
    if (NeedAiAnalysis(CaretUpdateType::DOUBLE_CLICK, start, spanStart, content)) {
        int32_t aiPosStart = start - spanStart;
        int32_t aiPosEnd = end - spanStart;
        DataDetectorMgr::GetInstance().AdjustWordSelection(aiPosStart, content, aiPosStart, aiPosEnd);
        if (aiPosStart < 0 || aiPosEnd < 0) {
            return false;
        }

        start = std::min(aiPosStart + spanStart, GetTextContentLength());
        end = std::min(aiPosEnd + spanStart, GetTextContentLength());
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get ai selector [%{public}d--%{public}d]", start, end);
        return true;
    }
    return false;
}

void RichEditorPattern::AdjustPlaceholderSelection(int32_t& start, int32_t& end, const Offset& touchPos)
{
    CHECK_NULL_VOID(!spans_.empty());
    if (!IsTouchBeforeCaret(start, touchPos)) {
        return;
    }
    auto it = std::find_if(spans_.begin(), spans_.end(), [start](const RefPtr<SpanItem>& spanItem) {
        return spanItem->position == start;
    });
    if (it != spans_.end()) {
        // adjust selection if touch right of image or placeholder
        auto spanIndex = std::distance(spans_.begin(), it);
        auto spanNodeBefore = DynamicCast<FrameNode>(GetChildByIndex(spanIndex));
        if (spanNodeBefore && (spanNodeBefore->GetTag() == V2::IMAGE_ETS_TAG ||
            spanNodeBefore->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG)) {
            end = start;
            --start;
            TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "get placeholder selector [%{public}d--%{public}d]", start, end);
        }
    }
}

bool RichEditorPattern::IsTouchAtLineEnd(int32_t caretPos, const Offset& textOffset)
{
    auto positionWithAffinity = paragraphs_.GetGlyphPositionAtCoordinate(textOffset);
    TextAffinity currentAffinity = positionWithAffinity.affinity_;
    return currentAffinity == TextAffinity::UPSTREAM && !IsTouchBeforeCaret(caretPos, textOffset);
}

bool RichEditorPattern::IsTouchBeforeCaret(int32_t caretPos, const Offset& textOffset) {
    CHECK_NULL_RETURN(!spans_.empty(), false);
    float selectLineHeight = 0.0f;
    OffsetF caretOffsetUp = paragraphs_.ComputeCursorOffset(caretPos, selectLineHeight);
    auto needAdjustRect = RectF{ 0, caretOffsetUp.GetY(), caretOffsetUp.GetX(), selectLineHeight };
    return needAdjustRect.IsInRegion(PointF{ textOffset.GetX(), textOffset.GetY() });
}

bool RichEditorPattern::IsClickBoundary(const int32_t position)
{
    if (InputAIChecker::IsSingleClickAtBoundary(position, GetTextContentLength())) {
        return true;
    }

    float height = 0;
    auto handleOffset = CalcCursorOffsetByPosition(position, height);
    if (InputAIChecker::IsMultiClickAtBoundary(handleOffset, TextPattern::GetTextRect())) {
        return true;
    }
    return false;
}

std::string RichEditorPattern::GetPositionSpansText(int32_t position, int32_t& startSpan)
{
    int32_t start = position - AI_TEXT_RANGE_LEFT;
    int32_t end = position + AI_TEXT_RANGE_RIGHT;

    start = std::clamp(start, 0, GetTextContentLength());
    end = std::clamp(end, 0, GetTextContentLength());
    AdjustSelector(start, end);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "caret=%{public}d, range=[%{public}d,%{public}d]", position, start, end);

    // get all the spans between start and end, then filter the valid text
    auto infos = GetSpansInfo(start, end, GetSpansMethod::ONSELECT);
    if (infos.GetSelection().resultObjects.empty()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "get spans text is null pos:%{public}d,return", position);
        return "";
    }
    auto list = infos.GetSelection().resultObjects;

    std::stringstream sstream;
    for (const auto& obj : list) {
        if (obj.type != SelectSpanType::TYPESPAN) {
            if (obj.spanPosition.spanRange[0] == position) {
                startSpan = -1;
                return "";
            } else if (obj.spanPosition.spanRange[1] <= position) {
                sstream.str("");
                startSpan = -1;
            } else {
                break;
            }
        } else {
            if (startSpan < 0) {
                startSpan = obj.spanPosition.spanRange[0] + obj.offsetInSpan[0];
            }
            // we should use the wide string deal to avoid crash
            auto wideText = obj.valueString;
            int32_t textLen = static_cast<int32_t>(wideText.length());
            if (obj.offsetInSpan[0] < textLen && obj.offsetInSpan[1] <= textLen) {
                sstream << UtfUtils::Str16ToStr8(
                    wideText.substr(obj.offsetInSpan[0], obj.offsetInSpan[1] - obj.offsetInSpan[0]));
            }
        }
    }

    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "get spans text ret spanStart:%{public}d", startSpan);
    return sstream.str();
}

bool RichEditorPattern::IsShowSelectMenuUsingMouse()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_RETURN(selectOverlayManager, false);
    return selectOverlayManager->GetSelectOverlayInfo().isUsingMouse;
}

RefPtr<FocusHub> RichEditorPattern::GetFocusHub() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    return focusHub;
}

void RichEditorPattern::HandleCursorOnDragMoved(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (HasFocus()) {
        if (!isCursorAlwaysDisplayed_) {
            isCursorAlwaysDisplayed_ = true;
            StartTwinkling();
        }
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGD(AceLogTag::ACE_RICH_TEXT,
                "In OnDragMoved, the cursor has always Displayed in the textField, id:" SEC_PLD(%{public}d),
                    SEC_PARAM(host->GetId()));
        }
        return;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "In OnDragMoved, the dragging node is moving in the richEditor, id:" SEC_PLD(%{public}d),
            SEC_PARAM(host->GetId()));
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    isOnlyRequestFocus_ = true;
    focusHub->RequestFocusImmediately();
    if (focusHub->IsCurrentFocus()) {
        ShowCaretWithoutTwinkling();
    }
};

void RichEditorPattern::HandleCursorOnDragLeaved(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "In OnDragLeaved, the dragging node has left from richEditor, id:" SEC_PLD(%{public}d),
            SEC_PARAM(host->GetId()));
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->LostFocusToViewRoot();
    StopTwinkling();
};

void RichEditorPattern::HandleCursorOnDragEnded(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    StopAutoScroll();
    if (!isCursorAlwaysDisplayed_) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "In OnDragEnded,"
            " the released location is not in the current richEditor, id:" SEC_PLD(%{public}d),
                SEC_PARAM(host->GetId()));
        IF_TRUE(HasFocus(), CloseKeyboard(false));
        focusHub->LostFocus();
        StopTwinkling();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "In OnDragEnded, the released location is in the current richEditor, id:" SEC_PLD(%{public}d),
            SEC_PARAM(host->GetId()));
    focusHub->LostFocusToViewRoot();
    isCursorAlwaysDisplayed_ = false;
    StopTwinkling();
};

void RichEditorPattern::HandleOnDragStatusCallback(
    const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    ScrollablePattern::HandleOnDragStatusCallback(dragEventType, notifyDragEvent);
    switch (dragEventType) {
        case DragEventType::MOVE:
            HandleCursorOnDragMoved(notifyDragEvent);
            break;
        case DragEventType::LEAVE:
            HandleCursorOnDragLeaved(notifyDragEvent);
            break;
        case DragEventType::DROP:
            HandleCursorOnDragEnded(notifyDragEvent);
            break;
        default:
            break;
    }
}

void RichEditorPattern::HandleOnCameraInput()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnCameraInput");
#if defined(ENABLE_STANDARD_INPUT)
    if (richEditTextChangeListener_ == nullptr) {
        richEditTextChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (!inputMethod) {
        return;
    }
    StartTwinkling();
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (imeShown_) {
        inputMethod->StartInputType(MiscServices::InputType::CAMERA_INPUT);
    } else {
        HandleOnEditChanged(true);
        auto optionalTextConfig = GetMiscTextConfig();
        CHECK_NULL_VOID(optionalTextConfig.has_value());
        MiscServices::TextConfig textConfig = optionalTextConfig.value();
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnCameraInput set calling window id is : %{public}u",
            textConfig.windowId);
#ifdef WINDOW_SCENE_SUPPORTED
        auto systemWindowId = GetSCBSystemWindowId();
        if (systemWindowId) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "windowId From %{public}u to %{public}u.", textConfig.windowId,
                systemWindowId);
            textConfig.windowId = systemWindowId;
        }
#endif
        auto ret = inputMethod->Attach(richEditTextChangeListener_, false, textConfig);
        if (ret == MiscServices::ErrorCode::NO_ERROR) {
            auto pipeline = GetContext();
            CHECK_NULL_VOID(pipeline);
            auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
            CHECK_NULL_VOID(textFieldManager);
            textFieldManager->SetIsImeAttached(true);
        }
        inputMethod->StartInputType(MiscServices::InputType::CAMERA_INPUT);
        inputMethod->ShowTextInput();
    }
    CloseSelectOverlay();
#endif
#endif
}

bool RichEditorPattern::CanStartAITask()
{
    return TextPattern::CanStartAITask() && !isEditing_ && !spans_.empty();
}

bool RichEditorPattern::NeedShowAIDetect()
{
    return TextPattern::NeedShowAIDetect() && !isEditing_ && !isShowPlaceholder_ && !spans_.empty();
}

void RichEditorPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("enableDataDetector", textDetectEnable_ ? "true" : "false", filter);
    json->PutExtAttr("dataDetectorConfig", dataDetectorAdapter_->textDetectConfigStr_.c_str(), filter);
    json->PutExtAttr("placeholder", GetPlaceHolderInJson().c_str(), filter);
    json->PutExtAttr("bindSelectionMenu", GetBindSelectionMenuInJson().c_str(), filter);
    json->PutExtAttr("stopBackPress", isStopBackPress_ ? "true" : "false", filter);
    json->PutExtAttr("keyboardAppearance", static_cast<int32_t>(keyboardAppearance_), filter);
    json->PutExtAttr("maxLength", maxLength_.value_or(INT_MAX), filter);
    json->PutExtAttr("enableHapticFeedback", isEnableHapticFeedback_ ? "true" : "false", filter);
    json->PutExtAttr("barState", static_cast<int32_t>(GetBarDisplayMode()), filter);
}

void RichEditorPattern::FillPreviewMenuInJson(const std::unique_ptr<JsonValue>& jsonValue) const
{
    IF_PRESENT(oneStepDragController_, FillJsonValue(jsonValue));
}

std::string RichEditorPattern::GetPlaceHolderInJson() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    bool hasPlaceHolder = layoutProperty && layoutProperty->HasPlaceholder()
        && !layoutProperty->GetPlaceholder().value().empty();
    CHECK_NULL_RETURN(hasPlaceHolder, "");
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("value", UtfUtils::Str16ToStr8(layoutProperty->GetPlaceholderValue(u"")).c_str());
    auto jsonFont = JsonUtil::Create(true);
    jsonFont->Put("size", GetFontSizeInJson(layoutProperty->GetPlaceholderFontSize()).c_str());
    jsonFont->Put("weight", GetFontWeightInJson(layoutProperty->GetPlaceholderFontWeight()).c_str());
    jsonFont->Put("family", GetFontFamilyInJson(layoutProperty->GetPlaceholderFontFamily()).c_str());
    jsonFont->Put("style", GetFontStyleInJson(layoutProperty->GetPlaceholderItalicFontStyle()).c_str());
    auto jsonStyle = JsonUtil::Create(true);
    jsonStyle->Put("font", jsonFont->ToString().c_str());
    jsonStyle->Put("fontColor", GetTextColorInJson(layoutProperty->GetPlaceholderTextColor()).c_str());
    jsonValue->Put("style", jsonStyle->ToString().c_str());
    return StringUtils::RestoreBackslash(jsonValue->ToString());
}

std::string RichEditorPattern::GetTextColorInJson(const std::optional<Color>& value) const
{
    CHECK_NULL_RETURN(!value, value->ColorToString());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richEditorTheme, "");
    Color textColor = richEditorTheme->GetTextStyle().GetTextColor();
    return textColor.ColorToString();
}

void RichEditorPattern::GetCaretMetrics(CaretMetricsF& caretCaretMetric)
{
    float caretHeight = 0.0f;
    OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto offset = host->GetPaintRectOffsetNG(false, true);
    caretOffset += offset;
    caretCaretMetric.offset = caretOffset;
    caretCaretMetric.height = caretHeight;
}

void RichEditorPattern::OnVirtualKeyboardAreaChanged()
{
    CHECK_NULL_VOID(SelectOverlayIsOn() && !selectOverlay_->GetIsHandleMoving() && !selectOverlay_->GetIsHandleHidden());
    float selectLineHeight = 0.0f;
    textSelector_.selectionBaseOffset.SetX(
        CalcCursorOffsetByPosition(textSelector_.GetStart(), selectLineHeight).GetX());
    textSelector_.selectionDestinationOffset.SetX(
        CalcCursorOffsetByPosition(textSelector_.GetEnd(), selectLineHeight).GetX());
    CreateHandles();
}

void RichEditorPattern::ResetDragOption()
{
    auto gestureEventHub = GetGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    if (gestureEventHub->GetIsTextDraggable()) {
        CloseSelectOverlay();
        ResetSelection();
    }
}

void RichEditorPattern::AdjustSelectRects(SelectRectsType pos, std::vector<RectF>& selectRects)
{
    if (pos == SelectRectsType::LEFT_TOP_POINT) {
        selectRects.erase(std::next(selectRects.begin()), selectRects.end());
        selectRects.front().SetSize({0, 0});
    } else if (pos == SelectRectsType::RIGHT_BOTTOM_POINT) {
        selectRects.erase(selectRects.begin(), std::prev(selectRects.end()));
        selectRects.front().SetRect({selectRects.front().Right(), selectRects.front().Bottom()}, {0, 0});
    }
}

RectF RichEditorPattern::GetSelectArea(SelectRectsType pos)
{
    RectF rect;
    auto paintOffset = selectOverlay_->GetPaintOffsetWithoutTransform();
    auto selectRects = paragraphs_.GetRects(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    auto contentRect = contentRect_;
    contentRect.SetOffset(contentRect.GetOffset() + paintOffset);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, rect);
    auto parent = host->GetAncestorNodeOfFrame(false);
    contentRect = GetVisibleContentRect(parent, contentRect);
    AppendSelectRect(selectRects);
    if (selectRects.empty()) {
        CHECK_NULL_RETURN(overlayMod_, rect);
        auto richEditorOverlay = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
        CHECK_NULL_RETURN(richEditorOverlay, rect);
        auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
        auto caretWidth = Dimension(1.5f, DimensionUnit::VP).ConvertToPx();
        auto selectRect = RectF(caretOffset + paintOffset, SizeF(caretWidth, caretHeight));
        return selectRect.IntersectRectT(contentRect);
    }
    AdjustSelectRects(pos, selectRects);
    auto frontRect = selectRects.front();
    auto backRect = selectRects.back();
    float selectAreaRight = frontRect.Right();
    float selectAreaLeft = frontRect.Left();
    if (selectRects.size() != 1) {
        std::unordered_map<float, RectF> selectLineRect;
        for (const auto& box : selectRects) {
            auto combineLineRect = box;
            auto top = box.Top();
            if (selectLineRect.find(top) == selectLineRect.end()) {
                selectLineRect.insert({ top, combineLineRect });
            } else {
                combineLineRect = combineLineRect.CombineRectT(selectLineRect[top]);
                selectLineRect.insert({ top, combineLineRect });
            }
            selectAreaRight = std::max(selectAreaRight, combineLineRect.Right());
            selectAreaLeft = std::min(selectAreaLeft, combineLineRect.Left());
        }
    }
    RectF res = { selectAreaLeft + richTextRect_.GetX() + paintOffset.GetX(),
        frontRect.GetY() + richTextRect_.GetY() + paintOffset.GetY(), selectAreaRight - selectAreaLeft,
        backRect.Bottom() - frontRect.Top() };
    return res.IntersectRectT(contentRect);
}

void RichEditorPattern::AppendSelectRect(std::vector<RectF>& selectRects)
{
    CHECK_NULL_VOID(!selectOverlay_->IsSingleHandle());
    auto startPosition = textSelector_.GetTextStart();
    auto endPosition = textSelector_.GetTextEnd();
    auto height = 0.0f;
    auto caretWidth = Dimension(1.5f, DimensionUnit::VP).ConvertToPx();
    if (paragraphs_.IsIndexAtParagraphEnd(startPosition + 1)) {
        auto offset = paragraphs_.ComputeCursorOffset(startPosition, height, false, false);
        RectF rect = RectF(offset.GetX(), offset.GetY(), caretWidth, height);
        selectRects.insert(selectRects.begin(), rect);
    }
    if (paragraphs_.IsIndexAtParagraphEnd(endPosition)) {
        auto offset = paragraphs_.ComputeCursorOffset(endPosition, height, true, false);
        RectF rect = RectF(offset.GetX(), offset.GetY(), caretWidth, height);
        selectRects.emplace_back(rect);
    }
}

bool RichEditorPattern::IsTouchInFrameArea(const PointF& touchPoint)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto viewPort = RectF(parentGlobalOffset_, frameRect_.GetSize());
    auto parent = host->GetAncestorNodeOfFrame(false);
    viewPort = GetVisibleContentRect(parent, viewPort);
    return viewPort.IsInRegion(touchPoint);
}

bool RichEditorPattern::SetPlaceholder(std::vector<std::list<RefPtr<SpanItem>>>& spanItemList)
{
    if (!spans_.empty()) {
        isShowPlaceholder_ = false;
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (!layoutProperty->HasPlaceholder() || layoutProperty->GetPlaceholder().value().empty()) {
        isShowPlaceholder_ = false;
        return false;
    }
    auto placeholderValue = layoutProperty->GetPlaceholder().value();
    auto placeholderNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    CHECK_NULL_RETURN(placeholderNode, false);
    if (layoutProperty->HasPlaceholderFontSize()) {
        placeholderNode->UpdateFontSize(layoutProperty->GetPlaceholderFontSize().value());
    }
    if (layoutProperty->HasPlaceholderFontWeight()) {
        placeholderNode->UpdateFontWeight(layoutProperty->GetPlaceholderFontWeight().value());
    }
    if (layoutProperty->HasPlaceholderFontFamily()) {
        placeholderNode->UpdateFontFamily(layoutProperty->GetPlaceholderFontFamily().value());
    }
    if (layoutProperty->HasPlaceholderItalicFontStyle()) {
        placeholderNode->UpdateItalicFontStyle(layoutProperty->GetPlaceholderItalicFontStyle().value());
    }
    if (layoutProperty->HasPlaceholderTextColor()) {
        placeholderNode->UpdateTextColorWithoutCheck(layoutProperty->GetPlaceholderTextColor().value());
    } else {
        auto theme = GetTheme<RichEditorTheme>();
        placeholderNode->UpdateTextColorWithoutCheck(theme ? theme->GetPlaceholderColor() : Color());
    }

    auto spanItem = placeholderNode->GetSpanItem();
    CHECK_NULL_RETURN(spanItem, false);
    spanItem->content = placeholderValue;
    spanItemList.clear();
    spanItemList.push_back({ { {spanItem} } });
    isShowPlaceholder_ = true;
    return true;
}

std::string RichEditorPattern::GetPlaceHolder() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto layoutProperty = host->GetLayoutProperty<RichEditorLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return UtfUtils::Str16ToStr8(layoutProperty->GetPlaceholderValue(u""));
}

Color RichEditorPattern::GetCaretColor()
{
    if (caretColor_.has_value()) {
        return caretColor_.value();
    }
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richEditorTheme, SYSTEM_CARET_COLOR);
    return richEditorTheme->GetCaretColor();
}

Color RichEditorPattern::GetSelectedBackgroundColor()
{
    Color selectedBackgroundColor;
    if (selectedBackgroundColor_.has_value()) {
        selectedBackgroundColor = selectedBackgroundColor_.value();
    } else {
        auto richEditorTheme = GetTheme<RichEditorTheme>();
        CHECK_NULL_RETURN(richEditorTheme, SYSTEM_SELECT_BACKGROUND_COLOR);
        selectedBackgroundColor = richEditorTheme->GetSelectedBackgroundColor();
    }
    // Alpha == 255 Means completely opaque
    if (selectedBackgroundColor.GetAlpha() == COLOR_OPAQUE) {
        selectedBackgroundColor = selectedBackgroundColor.ChangeOpacity(DEFAILT_OPACITY);
    }
    return selectedBackgroundColor;
}

void RichEditorPattern::HandleOnDragDropStyledString(const RefPtr<OHOS::Ace::DragEvent>& event, bool isCopy)
{
    CHECK_NULL_VOID(event);
    auto data = event->GetData();
    CHECK_NULL_VOID(data);
    auto arr = UdmfClient::GetInstance()->GetSpanStringRecord(data);
    if (!arr.empty()) {
        auto spanStr = SpanString::DecodeTlv(arr);
        if (!spanStr->GetSpanItems().empty()) {
            if (isSpanStringMode_) {
                HandleOnDragInsertStyledString(spanStr, isCopy);
                return;
            }
            AddSpanByPasteData(spanStr);
            return;
        }
    }

    auto records = UdmfClient::GetInstance()->GetPlainTextRecords(data);
    if (records.empty()) {
        return;
    }
    std::string str;
    for (const auto& record : records) {
        str += record;
    }
    if (str.empty()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "text is empty.");
        return;
    }
    if (isSpanStringMode_) {
        InsertValueInStyledString(UtfUtils::Str8ToStr16(str), true);
    } else {
        HandleOnDragDropTextOperation(UtfUtils::Str8ToStr16(str), isDragSponsor_, isCopy);
    }
}

void RichEditorPattern::HandleOnDragDrop(const RefPtr<OHOS::Ace::DragEvent>& event, bool isCopy)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextCommonEvent textCommonEvent;
    if (textCommonEvent.IsPreventDefault()) {
        CloseSelectOverlay();
        ResetSelection();
        StartTwinkling();
        return;
    }
    HandleOnDragDropStyledString(event, isCopy);
    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (focusHub->IsCurrentFocus()) {
        StartTwinkling();
    }
    afterDragSelect_ = isMouseOrTouchPad(sourceTool_);
    releaseInDrop_ = true;
}

void RichEditorPattern::DeleteForward(int32_t currentPosition, int32_t length)
{
    RichEditorDeleteValue info;
    info.SetOffset(currentPosition);
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::FORWARD);
    info.SetLength(length);
    CalcDeleteValueObj(currentPosition, length, info);
    DeleteByDeleteValueInfo(info);
    OnReportRichEditorEvent("onDeleteComplete");
}

int32_t RichEditorPattern::HandleOnDragDeleteForward()
{
    int32_t allDelLength = 0;
    SelectionInfo textSelectInfo = GetSpansInfo(dragRange_.first, dragRange_.second, GetSpansMethod::ONSELECT);
    std::list<ResultObject> dragResultObjects = textSelectInfo.GetSelection().resultObjects;
    for (auto ri = dragResultObjects.rbegin(); ri != dragResultObjects.rend(); ++ri) {
        if (SelectSpanType::TYPESPAN == ri->type || (SelectSpanType::TYPEIMAGE == ri->type && ri->valueString != u" ")) {
            int32_t spanStart = ri->offsetInSpan[RichEditorSpanRange::RANGESTART];
            int32_t spanEnd = ri->offsetInSpan[RichEditorSpanRange::RANGEEND];
            int32_t reStart = ri->spanPosition.spanRange[RichEditorSpanRange::RANGESTART];
            int32_t delStart = reStart;
            if (spanStart > 0) {
                delStart += spanStart;
            }
            int32_t delLength = spanEnd - spanStart;
            DeleteForward(delStart, delLength);
            allDelLength += delLength;
        }
    }
    return allDelLength;
}

void RichEditorPattern::HandleOnDragDropTextOperation(const std::u16string& insertValue, bool isDeleteSelect, bool isCopy)
{
    insertValueLength_ = static_cast<int32_t>(insertValue.length());
    if (!isDeleteSelect || isCopy) {
        InsertValueByOperationType(insertValue, OperationType::DRAG);
        return;
    }
    int32_t currentPosition = caretPosition_;
    int32_t strLength = static_cast<int32_t>(insertValue.length());
    OperationRecord record;
    record.addText = insertValue;
    record.beforeCaretPosition = dragRange_.first;
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, record, RecordType::DRAG));
    if (currentPosition < dragRange_.first) {
        InsertValueByOperationType(insertValue, OperationType::DRAG);
        dragRange_.first += strLength;
        dragRange_.second += strLength;
        HandleOnDragDeleteForward();
        lastCaretPosition_ = currentPosition;
    } else if (currentPosition > dragRange_.second) {
        InsertValueByOperationType(insertValue, OperationType::DRAG);
        int32_t delLength = HandleOnDragDeleteForward();
        caretPosition_ -= delLength;
        lastCaretPosition_ = currentPosition - strLength;
    } else {
        lastCaretPosition_ = dragRange_.first;
    }

    AfterContentChange(changeValue);
}

void RichEditorPattern::UndoDrag(const OperationRecord& record)
{
    if (!record.addText.has_value() || record.deleteCaretPostion == -1) {
        return;
    }
    const auto& str = record.addText.value();
    int32_t length = static_cast<int32_t>(str.length());
    DeleteForward(record.beforeCaretPosition, length);

    lastCaretPosition_ = caretPosition_;
    caretPosition_ = record.deleteCaretPostion;
    InsertValueOperation(str, nullptr, OperationType::DEFAULT);
}

void RichEditorPattern::RedoDrag(const OperationRecord& record)
{
    if (!record.addText.has_value() || record.deleteCaretPostion == -1) {
        return;
    }
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, record, RecordType::REDO));
    const auto& str = record.addText.value();
    int32_t length = static_cast<int32_t>(str.length());
    DeleteForward(record.deleteCaretPostion, length);
    lastCaretPosition_ = caretPosition_;
    caretPosition_ = record.beforeCaretPosition;
    InsertValueOperation(str, nullptr, OperationType::DRAG);
    AfterContentChange(changeValue);
}

void RichEditorPattern::HandleOnDragInsertValueOperation(const std::u16string& insertValue)
{
    InsertValueByOperationType(insertValue, OperationType::DRAG);
}

void RichEditorPattern::HandleOnDragInsertValue(const std::u16string& insertValue)
{
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_ + moveLength_;
    if (textSelector_.IsValid()) {
        record.beforeCaretPosition = textSelector_.GetTextStart();
    }
    record.addText = insertValue;
    ClearRedoOperationRecords();
    InsertValueByOperationType(insertValue, OperationType::DRAG);
    int32_t length = dragRange_.second - dragRange_.first;
    record.afterCaretPosition = record.beforeCaretPosition + length;
    record.deleteCaretPostion = dragRange_.first;
    AddOperationRecord(record);
}

bool RichEditorPattern::IsEditing()
{
    return isEditing_;
}

void RichEditorPattern::HandleOnEditChanged(bool isEditing)
{
    CHECK_NULL_VOID(isEditing_ != isEditing);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);

    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "editState->%{public}d", isEditing);
    isEditing_ = isEditing;
    eventHub->FireOnEditingChange(isEditing);

    if (CanStartAITask()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "leave edit state, start AI task");
        dataDetectorAdapter_->StartAITask();
    } else {
        if (isEditing) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "enter edit state, reset previewLongPress_");
            previewLongPress_ = false;
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void RichEditorPattern::ResetKeyboardIfNeed()
{
    bool needToResetKeyboard = false;
    auto currentAction = GetTextInputActionValue(GetDefaultTextInputAction());
    // When the enter key type changes, the keyboard needs to be reset.
    if (action_ != TextInputAction::UNSPECIFIED) {
        needToResetKeyboard = action_ != currentAction;
    }
    action_ = currentAction;
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (needToResetKeyboard) {
        // if keyboard attached or keyboard is shown, pull up keyboard again
        if (imeShown_ || isCustomKeyboardAttached_) {
            if (HasFocus()) {
                RequestKeyboard(false, true, true);
            }
            return;
        }
#if defined(ENABLE_STANDARD_INPUT)
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        CHECK_NULL_VOID(inputMethod);
        MiscServices::Configuration config;
        config.SetEnterKeyType(static_cast<MiscServices::EnterKeyType>(action_));
        config.SetTextInputType(static_cast<MiscServices::TextInputType>(keyboard_));
        inputMethod->OnConfigurationChange(config);
#endif
    }
#else
    if (needToResetKeyboard && HasConnection()) {
        CloseSelectOverlay();
        ResetSelection();
        CloseKeyboard(false);
        RequestKeyboard(false, true, true);
    }
#endif
}

void RichEditorPattern::OnTextInputActionUpdate(TextInputAction value) {}

void RichEditorPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "PerformAction, action=%{public}d", action);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // When the Enter key is triggered, perform a line feed operation.
    if (action == TextInputAction::NEW_LINE) {
        InsertValue(u"\n", true);
    }
    // Enter key type callback
    TextFieldCommonEvent event;
    auto eventHub = host->GetEventHub<RichEditorEventHub>();
    eventHub->FireOnSubmit(static_cast<int32_t>(action), event);
    // If the developer wants to keep editing, editing will not stop
    if (event.IsKeepEditable() || action == TextInputAction::NEW_LINE) {
        return;
    }
    // Exit the editing state
    StopEditing();
}

void RichEditorPattern::StopEditing()
{
    CHECK_NULL_VOID(HasFocus());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "StopEditing");

    // The selection status disappears, the cursor is hidden, and the soft keyboard is exited
    HandleBlurEvent();
    // In order to avoid the physical keyboard being able to type, you need to make sure that you lose focus
    FocusHub::LostFocusToViewRoot();
}

TextInputAction RichEditorPattern::GetDefaultTextInputAction() const
{
    // As with TextInput, it is a line break by default
    return TextInputAction::NEW_LINE;
}

void RichEditorPattern::GetChangeSpanStyle(RichEditorChangeValue& changeValue, std::optional<TextStyle>& spanTextStyle,
    std::optional<struct UpdateParagraphStyle>& spanParaStyle, std::optional<std::u16string>& urlAddress,
    const RefPtr<SpanNode>& spanNode, int32_t spanIndex)
{
    auto originalSpans = changeValue.GetRichEditorOriginalSpans();
    if (spanIndex == 0 && originalSpans.size()) {
        const RichEditorAbstractSpanResult& firstInfo = originalSpans.front();
        const RichEditorAbstractSpanResult& lastInfo = originalSpans.back();
        int32_t firstLength = static_cast<int32_t>(firstInfo.GetValue().length());
        int32_t lastLength = static_cast<int32_t>(lastInfo.GetValue().length());
        if (firstInfo.GetEraseLength() == firstLength && lastInfo.GetEraseLength() == lastLength) {
            if (spans_.size() == originalSpans.size() ||
                static_cast<int32_t>(spans_.size()) == (lastInfo.GetSpanIndex() + 1)) {
                urlAddress.reset();
                return; // all spanNode be deleted, set default style
            }
            spanIndex = lastInfo.GetSpanIndex() + 1;
        } else if (firstInfo.GetEraseLength() == firstLength) {
            spanIndex = lastInfo.GetSpanIndex();
        }
        auto it = spans_.begin();
        std::advance(it, spanIndex);
        if ((*it)->unicode != 0 || DynamicCast<PlaceholderSpanItem>(*it)) {
            return; // is not a textSpan(Image/Symbol/other)
        }
        spanTextStyle = (*it)->GetTextStyle();
        struct UpdateParagraphStyle paraStyle;
        paraStyle.textAlign = (*it)->textLineStyle->GetTextAlign();
        paraStyle.leadingMargin = (*it)->textLineStyle->GetLeadingMargin();
        paraStyle.wordBreak = (*it)->textLineStyle->GetWordBreak();
        paraStyle.lineBreakStrategy = (*it)->textLineStyle->GetLineBreakStrategy();
        paraStyle.paragraphSpacing = (*it)->textLineStyle->GetParagraphSpacing();
        spanParaStyle = paraStyle;
    } else if (spanNode && spanNode->GetSpanItem()) {
        spanTextStyle = spanNode->GetSpanItem()->GetTextStyle();
        struct UpdateParagraphStyle paraStyle;
        paraStyle.textAlign = spanNode->GetTextAlign();
        paraStyle.leadingMargin = spanNode->GetLeadingMarginValue({});
        paraStyle.wordBreak = spanNode->GetWordBreak();
        paraStyle.lineBreakStrategy = spanNode->GetLineBreakStrategy();
        paraStyle.paragraphSpacing = spanNode->GetParagraphSpacing();
        spanParaStyle = paraStyle;
    }
}

void RichEditorPattern::GetReplacedSpan(RichEditorChangeValue& changeValue, int32_t& innerPosition,
    const std::u16string& insertValue, int32_t textIndex, std::optional<TextStyle> textStyle,
    std::optional<struct UpdateParagraphStyle> paraStyle, std::optional<std::u16string> urlAddress,
    bool isCreate, bool fixDel)
{
    std::u16string originalStr;
    int32_t originalPos = 0;
    RefPtr<SpanItem> spanItem = fixDel ? GetDelPartiallySpanItem(changeValue, originalStr, originalPos) : nullptr;
    TextInsertValueInfo info;
    CalcInsertValueObj(info, textIndex, isCreate);
    int32_t spanIndex = info.GetSpanIndex();
    int32_t offsetInSpan = info.GetOffsetInSpan();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto uiNode = host->GetChildAtIndex(spanIndex);
    RefPtr<SpanNode> spanNode = DynamicCast<SpanNode>(uiNode);
    if (!isCreate && textIndex && uiNode && uiNode->GetTag() != V2::SPAN_ETS_TAG) {
        spanNode = nullptr;
        ++spanIndex; // select/create a new span When the span is not a textSpan(Image/Symbol/other)
        offsetInSpan = 0;
        spanNode = DynamicCast<SpanNode>(host->GetChildAtIndex(spanIndex));
    }

    changeValue.SetRangeAfter({ innerPosition, innerPosition + insertValue.length()});
    std::u16string textTemp = insertValue;
    if (!textStyle && !isCreate && spanNode) {
        if (typingStyle_ && !HasSameTypingStyle(spanNode)) {
            textStyle = typingTextStyle_; // create a new span When have a different typingStyle
            bool insertInSpan = textIndex && offsetInSpan;
            spanIndex = insertInSpan ? spanIndex + 1 : spanIndex;
            offsetInSpan = 0;
        } else {
            textTemp = spanNode->GetSpanItem()->content;
            textTemp.insert(offsetInSpan, insertValue);
            urlAddress = spanNode->GetSpanItem()->urlAddress;
        }
    }

    auto it = textTemp.find(LINE_SEPARATOR);
    bool containNextLine = it != std::u16string::npos && it != textTemp.size() - 1;

    if (textStyle || containNextLine) { // SpanNode Fission
        GetReplacedSpanFission(changeValue, innerPosition, textTemp, spanIndex, offsetInSpan, textStyle, paraStyle,
            urlAddress);
    } else {
        std::optional<TextStyle> spanTextStyle = textStyle ? textStyle : typingTextStyle_;
        std::optional<struct UpdateParagraphStyle> spanParaStyle = paraStyle;
        GetChangeSpanStyle(changeValue, spanTextStyle, spanParaStyle, urlAddress, spanNode, spanIndex);
        CreateSpanResult(changeValue, innerPosition, spanIndex, offsetInSpan, offsetInSpan + insertValue.length(),
            textTemp, spanTextStyle, spanParaStyle, urlAddress);
        innerPosition += static_cast<int32_t>(insertValue.length());
    }

    if (spanItem) {
        spanItem->content = originalStr;
        spanItem->position = originalPos;
    }
}

void RichEditorPattern::GetReplacedSpanFission(RichEditorChangeValue& changeValue, int32_t& innerPosition,
    std::u16string& content, int32_t startSpanIndex, int32_t offsetInSpan, std::optional<TextStyle> textStyle,
    std::optional<struct UpdateParagraphStyle> paraStyle, const std::optional<std::u16string>& urlAddress)
{
    int spanIndex = startSpanIndex;
    auto index = content.find(LINE_SEPARATOR);
    while (index != std::u16string::npos) {
        auto textAfter = content.substr(index + 1);
        if (textAfter.empty()) {
            break;
        }
        auto textBefore = content.substr(0, index + 1);
        if (offsetInSpan != static_cast<int32_t>(textBefore.length())) {
            CreateSpanResult(changeValue, innerPosition, spanIndex, offsetInSpan, textBefore.length(),
                textBefore, textStyle, paraStyle, urlAddress);
            innerPosition += textBefore.length() - offsetInSpan;
        }
        content = textAfter;
        index = content.find(LINE_SEPARATOR);
        offsetInSpan = 0;
        ++spanIndex;
    }
    CreateSpanResult(changeValue, innerPosition, spanIndex, offsetInSpan, content.length(),
        content, textStyle, paraStyle, urlAddress);
    innerPosition += static_cast<int32_t>(content.length());
}

void RichEditorPattern::CreateSpanResult(RichEditorChangeValue& changeValue, int32_t& innerPosition, int32_t spanIndex,
    int32_t offsetInSpan, int32_t endInSpan, std::u16string content, std::optional<TextStyle> textStyle,
    std::optional<struct UpdateParagraphStyle> paraStyle, const std::optional<std::u16string>& urlAddress)
{
    RichEditorAbstractSpanResult retInfo;
    if (textStyle) {
        SetTextStyleToRet(retInfo, *textStyle);
    } else {
        retInfo.SetFontColor((Color::BLACK).ColorToString());
        retInfo.SetFontSize(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP).ConvertToVp());
        retInfo.SetFontStyle(OHOS::Ace::FontStyle::NORMAL);
        retInfo.SetFontWeight(static_cast<int32_t>(FontWeight::NORMAL));
        retInfo.SetTextDecoration(TextDecoration::NONE);
        retInfo.SetColor((Color::BLACK).ColorToString());
        retInfo.SetFontFamily("HarmonyOS Sans");
    }
    IF_TRUE(urlAddress.has_value(), retInfo.SetUrlAddress(urlAddress.value()));
    retInfo.SetSpanIndex(spanIndex);
    if (!previewTextRecord_.newPreviewContent.empty()) {
        retInfo.SetPreviewText(previewTextRecord_.newPreviewContent);
    } else {
        retInfo.SetValue(content);
    }
    int32_t rangStart = std::max(0, innerPosition - offsetInSpan);
    retInfo.SetSpanRangeStart(rangStart);
    retInfo.SetSpanRangeEnd(rangStart + content.length());
    retInfo.SetOffsetInSpan(offsetInSpan);
    retInfo.SetEraseLength(endInSpan - offsetInSpan);
    if (paraStyle) {
        TextStyleResult textStyleResult = retInfo.GetTextStyle();
        textStyleResult.textAlign = static_cast<int32_t>(paraStyle->textAlign.value_or(TextAlign::START));
        if (paraStyle->leadingMargin) {
            textStyleResult.leadingMarginSize[0] = paraStyle->leadingMargin->size.Width().ToString();
            textStyleResult.leadingMarginSize[1] = paraStyle->leadingMargin->size.Height().ToString();
        }
        IF_TRUE(paraStyle->wordBreak.has_value(),
            textStyleResult.wordBreak = static_cast<int32_t>(paraStyle->wordBreak.value()));
        IF_TRUE(paraStyle->lineBreakStrategy.has_value(),
            textStyleResult.lineBreakStrategy = static_cast<int32_t>(paraStyle->lineBreakStrategy.value()));
        IF_TRUE(paraStyle->paragraphSpacing.has_value(), textStyleResult.paragraphSpacing =
            Dimension(paraStyle->paragraphSpacing.value().ConvertToFp(), DimensionUnit::FP));
        retInfo.SetTextStyle(textStyleResult);
    }
    changeValue.SetRichEditorReplacedSpans(retInfo);
}

void RichEditorPattern::SetTextStyleToRet(RichEditorAbstractSpanResult& retInfo, const TextStyle& textStyle)
{
    retInfo.SetTextDecoration(textStyle.GetTextDecoration());
    retInfo.SetFontColor(textStyle.GetTextColor().ColorToString());
    retInfo.SetColor(textStyle.GetTextDecorationColor().ColorToString());
    retInfo.SetTextDecorationStyle(textStyle.GetTextDecorationStyle());
    retInfo.SetFontSize(textStyle.GetFontSize().ConvertToVp());
    retInfo.SetFontStyle(textStyle.GetFontStyle());
    TextStyleResult textStyleResult;
    textStyleResult.lineHeight = textStyle.GetLineHeight().ConvertToVp();
    textStyleResult.halfLeading = textStyle.GetHalfLeading();
    textStyleResult.letterSpacing = textStyle.GetLetterSpacing().ConvertToVp();
    textStyleResult.textShadows = textStyle.GetTextShadows();
    textStyleResult.textBackgroundStyle = textStyle.GetTextBackgroundStyle();
    retInfo.SetTextStyle(textStyleResult);
    retInfo.SetLineHeight(textStyle.GetLineHeight().ConvertToVp());
    retInfo.SetHalfLeading(textStyle.GetHalfLeading());
    retInfo.SetLetterspacing(textStyle.GetLetterSpacing().ConvertToVp());
    retInfo.SetFontFeature(textStyle.GetFontFeatures());
    std::string fontFamilyValue;
    auto fontFamily = textStyle.GetFontFamilies();
    for (const auto& str : fontFamily) {
        fontFamilyValue += str;
    }
    retInfo.SetFontFamily(fontFamilyValue);
    retInfo.SetFontWeight((int32_t)textStyle.GetFontWeight());
}

void RichEditorPattern::CalcInsertValueObj(TextInsertValueInfo& info, int textIndex, bool isCreate)
{
    if (spans_.empty()) {
        info.SetSpanIndex(0);
        info.SetOffsetInSpan(0);
        return;
    }
    auto it = std::find_if(
        spans_.begin(), spans_.end(), [caretPosition = textIndex](const RefPtr<SpanItem>& spanItem) {
            auto spanLength = static_cast<int32_t>(spanItem->content.length());
            if (spanLength == 0) {
                return spanItem->position == caretPosition;
            }
            return (spanItem->position - spanLength <= caretPosition) && (caretPosition <= spanItem->position);
        });
    if (it == spans_.end()) {
        info.SetSpanIndex(static_cast<int32_t>(spans_.size()) - 1);
        info.SetOffsetInSpan((*spans_.rbegin())->content.length());
        return;
    }
    if (textIndex && isCreate) {
        info.SetSpanIndex(std::distance(spans_.begin(), it) + 1);
        info.SetOffsetInSpan(0);
        return;
    }
    if ((*it)->content.back() == '\n' && (*it)->position == textIndex) { // next line/span begin
        info.SetSpanIndex(std::distance(spans_.begin(), it) + 1);
        info.SetOffsetInSpan(0);
    } else {
        info.SetSpanIndex(std::distance(spans_.begin(), it));
        int32_t spanStart = (*it)->position - static_cast<int32_t>((*it)->content.length());
        info.SetOffsetInSpan(textIndex - spanStart);
    }
}

void RichEditorPattern::GetDeletedSpan(RichEditorChangeValue& changeValue, int32_t& innerPosition,
    int32_t length, RichEditorDeleteDirection direction)
{
    RichEditorDeleteValue info;
    if (!textSelector_.SelectNothing()) {
        length = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
        innerPosition = std::min(textSelector_.GetStart(), textSelector_.GetEnd());
    } else if (previewTextRecord_.NeedReplace()) {
        length = previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start;
        innerPosition = previewTextRecord_.replacedRange.start;
    } else {
        int32_t emojiLength = CalculateDeleteLength(length, (direction == RichEditorDeleteDirection::BACKWARD));
        if (direction == RichEditorDeleteDirection::BACKWARD) {
            innerPosition -= emojiLength;
        }
        if (length < emojiLength) {
            length = emojiLength;
        }
    }

    info.SetOffset(innerPosition);
    info.SetRichEditorDeleteDirection(direction);
    info.SetLength(length);
    if (!spans_.empty()) {
        CalcDeleteValueObj(innerPosition, length, info);
    }
    if (!spans_.empty() || isAPI14Plus) {
        changeValue.SetRangeBefore({ innerPosition, innerPosition + length });
        changeValue.SetRangeAfter({ innerPosition, innerPosition });
    }
    const std::list<RichEditorAbstractSpanResult>& resultList = info.GetRichEditorDeleteSpans();
    for (auto& it : resultList) {
        if (it.GetType() == SpanResultType::TEXT) {
            changeValue.SetRichEditorOriginalSpans(it);
        } else if (it.GetType() == SpanResultType::SYMBOL && textSelector_.SelectNothing() &&
            previewTextRecord_.previewContent.empty()) {
            int32_t symbolStart = it.GetSpanRangeStart();
            changeValue.SetRichEditorOriginalSpans(it);
            changeValue.SetRangeBefore({ symbolStart, symbolStart + SYMBOL_SPAN_LENGTH });
            changeValue.SetRangeAfter({ symbolStart, symbolStart });
        }
    }
}

RefPtr<SpanItem> RichEditorPattern::GetDelPartiallySpanItem(
    RichEditorChangeValue& changeValue, std::u16string& originalStr, int32_t& originalPos)
{
    RefPtr<SpanItem> retItem = nullptr;
    if (changeValue.GetRichEditorOriginalSpans().size() == 0) {
        return retItem;
    }
    std::u16string textTemp;
    auto originalSpans = changeValue.GetRichEditorOriginalSpans();
    const RichEditorAbstractSpanResult& firstResult = originalSpans.front();
    auto it = spans_.begin();
    std::advance(it, firstResult.GetSpanIndex());
    retItem = *it;
    originalStr = retItem->content;
    originalPos = retItem->position;
    retItem->content.erase(firstResult.OffsetInSpan(), firstResult.GetEraseLength());
    retItem->position -= firstResult.GetEraseLength();
    if (firstResult.GetEraseLength() != static_cast<int32_t>(firstResult.GetValue().length())) {
        return retItem;
    }

    if (firstResult.GetSpanIndex() == 0) {
        int32_t spanIndex = 0;
        for (auto& orgIt : originalSpans) {
            spanIndex = orgIt.GetSpanIndex();
            if (orgIt.GetEraseLength() != static_cast<int32_t>(orgIt.GetValue().length())) {
                // find the deleted(Partially) spanItem
                auto findIt = spans_.begin();
                std::advance(findIt, spanIndex);
                textTemp = (*findIt)->content;
                textTemp.erase(orgIt.OffsetInSpan(), orgIt.GetEraseLength());
                retItem->content = textTemp;
                retItem->position = textTemp.length();
                return retItem;
            }
        }
        if (spans_.size() == originalSpans.size() || static_cast<int32_t>(spans_.size()) == (spanIndex + 1)) {
            return retItem; // all spanNode be deleted
        }
        auto nextIt = spans_.begin();
        std::advance(nextIt, spanIndex + 1);
        if ((*nextIt)->unicode != 0 || DynamicCast<PlaceholderSpanItem>(*nextIt)) {
            return retItem; // is not a textSpan(Image/Symbol/other)
        }
        retItem->content = (*nextIt)->content;
        retItem->position = static_cast<int32_t>(retItem->content.length());
    }
    return retItem;
}

bool RichEditorPattern::BeforeChangeText(RichEditorChangeValue& changeValue, const TextSpanOptions& options)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (!eventHub->HasOnWillChange() && !eventHub->HasOnDidChange()) {
        return true;
    }
    int32_t innerPosition = caretPosition_;

   // AddTextSpan
    std::optional<TextStyle> textStyle = std::nullopt;
    if (options.style.has_value()) {
        textStyle = options.style;
    }
    if (options.offset.has_value()) {
        if (spans_.empty() || options.offset.value() < 0) {
            innerPosition = 0;
        } else if (options.offset.value() > GetTextContentLength()) {
            innerPosition = GetTextContentLength();
        } else {
            innerPosition = options.offset.value();
        }
    } else {
        innerPosition = GetTextContentLength();
    }
    // only add, do not delete
    changeValue.SetRangeBefore({ innerPosition, innerPosition });
    GetReplacedSpan(changeValue, innerPosition, options.value, innerPosition, textStyle, options.paraStyle,
        options.urlAddress, true);

    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);
    auto ret = eventHub->FireOnWillChange(changeValue);
    return ret;
}

bool RichEditorPattern::BeforeAddImage(RichEditorChangeValue& changeValue,
    const ImageSpanOptions& options, int32_t insertIndex)
{
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (!eventHub->HasOnWillChange() && !eventHub->HasOnDidChange()) {
        return true;
    }
    changeValue.SetRangeBefore({ insertIndex, insertIndex });
    changeValue.SetRangeAfter({ insertIndex, insertIndex + 1});
    RichEditorAbstractSpanResult retInfo;
    TextInsertValueInfo info;
    CalcInsertValueObj(info, insertIndex, true);
    int32_t spanIndex = info.GetSpanIndex();
    retInfo.SetSpanIndex(spanIndex);
    if (options.image) {
        retInfo.SetValueResourceStr(*options.image);
    }
    if (options.imagePixelMap) {
        retInfo.SetValuePixelMap(*options.imagePixelMap);
    }
    if (options.imageAttribute.has_value()) {
        auto imgAttr = options.imageAttribute.value();
        if (imgAttr.size.has_value()) {
            retInfo.SetSizeWidth(imgAttr.size->width.value_or(CalcDimension()).ConvertToPx());
            retInfo.SetSizeHeight(imgAttr.size->height.value_or(CalcDimension()).ConvertToPx());
        }
        if (imgAttr.verticalAlign.has_value()) {
            retInfo.SetVerticalAlign(imgAttr.verticalAlign.value());
        }
        if (imgAttr.objectFit.has_value()) {
            retInfo.SetImageFit(imgAttr.objectFit.value());
        }
        if (imgAttr.marginProp.has_value()) {
            retInfo.SetMargin(imgAttr.marginProp.value().ToString());
        }
        if (imgAttr.borderRadius.has_value()) {
            retInfo.SetBorderRadius(imgAttr.borderRadius.value().ToString());
        }
    }
    retInfo.SetOffsetInSpan(0);
    retInfo.SetEraseLength(1);
    retInfo.SetSpanRangeStart(insertIndex);
    retInfo.SetSpanRangeEnd(insertIndex + 1);
    retInfo.SetSpanType(SpanResultType::IMAGE);
    changeValue.SetRichEditorReplacedImageSpans(retInfo);
    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);
    auto ret = eventHub->FireOnWillChange(changeValue);
    return ret;
}

void RichEditorPattern::FixMoveDownChange(RichEditorChangeValue& changeValue, int32_t delLength)
{
    int32_t delSpanCount = 0;
    for (auto& it : changeValue.GetRichEditorOriginalSpans()) {
        if (it.GetEraseLength() == static_cast<int32_t>(it.GetValue().length())) {
            ++delSpanCount;
        }
    }
    for (auto& it : const_cast<std::vector<RichEditorAbstractSpanResult>&>(changeValue.GetRichEditorReplacedSpans())) {
        if (delSpanCount) {
            it.SetSpanIndex(it.GetSpanIndex() - delSpanCount);
        }
    }
}

void RichEditorPattern::BeforeUndo(
    RichEditorChangeValue& changeValue, int32_t& innerPosition, const OperationRecord& record)
{
    innerPosition = record.afterCaretPosition;
    if (record.addText.has_value() && record.deleteCaretPostion != -1) { // UndoDrag
        GetDeletedSpan(changeValue, innerPosition, record.addText.value_or(u"").length(),
            RichEditorDeleteDirection::FORWARD);
        innerPosition = record.deleteCaretPostion;
        GetReplacedSpan(changeValue, innerPosition, record.addText.value(), innerPosition, std::nullopt, std::nullopt);
    } else if (record.addText.has_value() && record.deleteText.has_value()) {
        GetDeletedSpan(changeValue, innerPosition, record.addText.value_or(u"").length(),
            RichEditorDeleteDirection::BACKWARD);
        GetReplacedSpan(
            changeValue, innerPosition, record.deleteText.value(), innerPosition, std::nullopt, std::nullopt);
    } else if (record.deleteText.has_value()) {
        GetReplacedSpan(
            changeValue, innerPosition, record.deleteText.value(), innerPosition, std::nullopt, std::nullopt);
    } else if (record.addText.has_value()) {
        GetDeletedSpan(changeValue, innerPosition, record.addText.value_or(u"").length(),
            RichEditorDeleteDirection::BACKWARD);
    }
}

void RichEditorPattern::BeforeRedo(
    RichEditorChangeValue& changeValue, int32_t& innerPosition, const OperationRecord& record)
{
    innerPosition = record.beforeCaretPosition - record.addText.value_or(u"").length();
    if (record.addText.has_value() && record.deleteCaretPostion != -1) { // RedoDrag
        innerPosition = record.deleteCaretPostion;
        GetDeletedSpan(changeValue, innerPosition, record.addText.value_or(u"").length(),
            RichEditorDeleteDirection::FORWARD);
        innerPosition = record.beforeCaretPosition;
        GetReplacedSpan(changeValue, innerPosition, record.addText.value(), innerPosition, std::nullopt, std::nullopt);
    } else if (record.addText.has_value() && record.deleteText.has_value()) {
        GetDeletedSpan(changeValue, innerPosition, record.deleteText.value_or(u"").length(),
            RichEditorDeleteDirection::FORWARD);
        GetReplacedSpan(changeValue, innerPosition, record.addText.value(), innerPosition, std::nullopt, std::nullopt);
    } else if (record.deleteText.has_value()) {
        innerPosition = record.beforeCaretPosition - record.deleteText.value_or(u"").length();
        GetDeletedSpan(changeValue, innerPosition, record.deleteText.value_or(u"").length(),
            RichEditorDeleteDirection::FORWARD);
    } else if (record.addText.has_value()) {
        innerPosition = std::min(innerPosition, record.afterCaretPosition);
        int32_t innerAddPosition = record.afterCaretPosition - static_cast<int32_t>(record.addText.value().length());
        if (changeValue.GetRichEditorOriginalSpans().empty()) {
            innerPosition = caretPosition_;
            innerAddPosition = caretPosition_;
        }
        GetReplacedSpan(changeValue, innerAddPosition, record.addText.value(), innerPosition,
            std::nullopt, std::nullopt);
    }
}

void RichEditorPattern::BeforeDrag(
    RichEditorChangeValue& changeValue, int32_t& innerPosition, const OperationRecord& record)
{
    std::u16string recordAddText = record.addText.value_or(u"");
    int length = recordAddText.length();
    int32_t nowPosition = innerPosition;
    std::optional<TextStyle> style = std::nullopt;
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        style = typingTextStyle_.value();
    }
    if (!isDragSponsor_) { // drag from outside
        GetReplacedSpan(
            changeValue, innerPosition, recordAddText, innerPosition, style, std::nullopt, std::nullopt, true, false);
    } else if (nowPosition < record.beforeCaretPosition + length) { // move up
        innerPosition = record.beforeCaretPosition;
        GetDeletedSpan(changeValue, innerPosition, length, RichEditorDeleteDirection::FORWARD);
        innerPosition = nowPosition;
        GetReplacedSpan(
            changeValue, innerPosition, recordAddText, nowPosition, style, std::nullopt, std::nullopt, true, false);
    } else { // move down
        innerPosition = record.beforeCaretPosition;
        GetDeletedSpan(changeValue, innerPosition, length, RichEditorDeleteDirection::FORWARD);
        innerPosition = nowPosition - length;
        GetReplacedSpan(
            changeValue, innerPosition, recordAddText, nowPosition, style, std::nullopt, std::nullopt, true, false);
        FixMoveDownChange(changeValue, length);
    }
}

bool RichEditorPattern::BeforeChangeText(
    RichEditorChangeValue& changeValue, const OperationRecord& record, RecordType type, int32_t delLength)
{
    int32_t innerPosition = caretPosition_;
    auto eventHub = GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    if (!eventHub->HasOnWillChange() && !eventHub->HasOnDidChange()) {
        return true;
    }

    if (RecordType::INSERT == type) {
        if (textSelector_.IsValid()) {
            GetDeletedSpan(changeValue, innerPosition,
                static_cast<int32_t>(textSelector_.GetTextEnd() - textSelector_.GetTextStart()));
        } else if (previewTextRecord_.NeedReplace()) {
            GetDeletedSpan(changeValue, innerPosition,
                static_cast<int32_t>(previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start));
        }
        if (record.addText.has_value()) {
            GetReplacedSpan(changeValue, innerPosition, record.addText.value(), innerPosition, std::nullopt, std::nullopt);
        }
    }
    if (RecordType::DEL_FORWARD == type) {
        innerPosition = record.beforeCaretPosition;
        GetDeletedSpan(changeValue, innerPosition, delLength, RichEditorDeleteDirection::FORWARD);
    }
    if (RecordType::DEL_BACKWARD == type) {
        innerPosition = record.beforeCaretPosition;
        GetDeletedSpan(changeValue, innerPosition, delLength, RichEditorDeleteDirection::BACKWARD);
    }
    if (RecordType::UNDO == type) {
        BeforeUndo(changeValue, innerPosition, record);
    }
    if (RecordType::REDO == type) {
        BeforeRedo(changeValue, innerPosition, record);
    }
    if (RecordType::DRAG == type) {
        BeforeDrag(changeValue, innerPosition, record);
    }
    bool isDelete = RecordType::DEL_FORWARD == type || RecordType::DEL_BACKWARD == type;
    if (changeValue.GetRichEditorOriginalSpans().empty() && !isDelete) {
        // only add, do not delete
        changeValue.SetRangeBefore({ caretPosition_, caretPosition_ });
    }

    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);
    auto ret = eventHub->FireOnWillChange(changeValue);
    return ret;
}

OffsetF RichEditorPattern::GetTextPaintOffset() const
{
    if (selectOverlay_->HasRenderTransform()) {
        return selectOverlay_->GetPaintRectOffsetWithTransform();
    }
    return GetPaintRectGlobalOffset();
}

OffsetF RichEditorPattern::GetPaintRectGlobalOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0.0f, 0.0f));
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, OffsetF(0.0f, 0.0f));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = host->GetPaintRectOffsetNG(false, true);
    return textPaintOffset - rootOffset;
}

void RichEditorPattern::HandlePointWithTransform(OffsetF& point)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    PointF convertPoint = { point.GetX(), point.GetY() };
    auto parent = host;
    while (parent && (parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG)) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto paintOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        if (parent != host) {
            convertPoint = convertPoint + paintOffset;
        }
        renderContext->GetPointTransform(convertPoint);
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    point = { convertPoint.GetX(), convertPoint.GetY() };
}

CaretOffsetInfo RichEditorPattern::GetCaretOffsetInfoByPosition(int32_t position)
{
    CaretOffsetInfo caretInfo;
    int32_t currrentPosition = 0;
    if (position == -1) {
        currrentPosition = caretPosition_;
    } else {
        currrentPosition = position;
    }
    caretInfo.caretOffsetUp = CalcCursorOffsetByPosition(currrentPosition, caretInfo.caretHeightUp, false, false);
    caretInfo.caretOffsetDown = CalcCursorOffsetByPosition(currrentPosition, caretInfo.caretHeightDown, true, false);
    caretInfo.caretOffsetLine = CalcCursorOffsetByPosition(currrentPosition, caretInfo.caretHeightLine);
    return caretInfo;
}

void RichEditorPattern::CalcLineSidesIndexByPosition(int32_t& startIndex, int32_t& endIndex)
{
    Offset textStartOffset;
    Offset textEndOffset;

    CHECK_NULL_VOID(overlayMod_);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize());
    float textOffsetY = richTextRect_.GetY() - (minDet / 2.0);
    auto currentCaretOffsetOverlay = overlayMod->GetCaretOffset();
    textStartOffset = Offset(0, currentCaretOffsetOverlay.GetY() - textOffsetY);
    textEndOffset = Offset(richTextRect_.Width(), currentCaretOffsetOverlay.GetY() - textOffsetY);
    startIndex = paragraphs_.GetIndex(textStartOffset);
    endIndex = paragraphs_.GetIndex(textEndOffset);
}

RectF RichEditorPattern::CalcLineInfoByPosition()
{
    int32_t startIndex = 0;
    int32_t endIndex = 0;

    CalcLineSidesIndexByPosition(startIndex, endIndex);
    if (startIndex == endIndex) {
        endIndex += 1;
    }
    auto selectedRects = paragraphs_.GetRects(startIndex, endIndex);
    CHECK_NULL_RETURN(selectedRects.size(), {});
    return selectedRects.front();
}

int32_t RichEditorPattern::CalcMoveUpPos(float& leadingMarginOffset)
{
    int32_t caretPosition;
    CaretOffsetInfo caretInfo;
    float textOffsetDownY = 0.0f;
    int32_t startIndex = 0;
    int32_t endIndex = 0;
    Offset textOffset;

    caretInfo = GetCaretOffsetInfoByPosition();
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize());
    CHECK_NULL_RETURN(overlayMod_, 0);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto caretOffsetWidth = overlayMod->GetCaretWidth();
    bool cursorNotAtLineStart = NearEqual(caretOffsetOverlay.GetX(), caretInfo.caretOffsetUp.GetX(), caretOffsetWidth);
    float textOffsetY = richTextRect_.GetY() + (minDet / 2.0); // 2.0 Cursor one half at the center position
    CalcLineSidesIndexByPosition(startIndex, endIndex);
    auto rectLineInfo = CalcLineInfoByPosition();
    leadingMarginOffset = rectLineInfo.GetX();
    if (cursorNotAtLineStart) {
        textOffsetDownY = caretInfo.caretOffsetLine.GetY() - textOffsetY;
        // lm mean leadingMargin abbr
        auto lmSizeOffset = (endIndex - startIndex <= 1 && NearEqual(rectLineInfo.Width(), richTextRect_.Width()))
                                ? rectLineInfo.GetX()
                                : 0;
        textOffset = Offset(caretInfo.caretOffsetLine.GetX() - richTextRect_.GetX() + lmSizeOffset, textOffsetDownY);
    } else {
        textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
        textOffset = Offset(caretOffsetOverlay.GetX() - richTextRect_.GetX(), textOffsetDownY);
    }
    caretPosition = paragraphs_.GetIndex(textOffset);
    return caretPosition;
}

int32_t RichEditorPattern::CalcMoveDownPos(float& leadingMarginOffset)
{
    CaretOffsetInfo caretInfo;
    float textOffsetDownY = 0.0f;
    Offset textOffset;
    int32_t caretPositionEnd;

    caretInfo = GetCaretOffsetInfoByPosition();
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize());
    CHECK_NULL_RETURN(overlayMod_, 0);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto caretOffsetWidth = overlayMod->GetCaretWidth();
    float textOffsetX = richTextRect_.GetX();
    float textOffsetY = richTextRect_.GetY() - (minDet / 2.0);
    bool cursorNotAtLineStart = NearEqual(caretOffsetOverlay.GetX(), caretInfo.caretOffsetUp.GetX(), caretOffsetWidth);
    // midle or enter
    auto rectLineInfo = CalcLineInfoByPosition();
    leadingMarginOffset = rectLineInfo.GetX();
    auto lineHeightDis = rectLineInfo.Height();
    // midle or end, first line start position,end line end position
    textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    float lastLineTop = 0.0f;
    float paragraphSpacing = 0.0f;
    HandleCurrentPositionParagraphInfo(lastLineTop, paragraphSpacing);
    if (cursorNotAtLineStart || caretPosition_ == 0) {
        IF_TRUE(NearEqual(std::floor(caretInfo.caretOffsetLine.GetY()), std::floor(lastLineTop)),
            textOffsetDownY += paragraphSpacing);
        textOffset = Offset(caretInfo.caretOffsetLine.GetX() - textOffsetX, textOffsetDownY);
    } else {
        IF_TRUE(NearEqual(std::floor(caretInfo.caretOffsetLine.GetY() + lineHeightDis), std::floor(lastLineTop)),
            textOffsetDownY += paragraphSpacing);
        textOffsetDownY += lineHeightDis;
        textOffset = Offset(caretOffsetOverlay.GetX() - textOffsetX, textOffsetDownY);
    }
    caretPositionEnd = paragraphs_.GetIndex(textOffset);
    return caretPositionEnd;
}

int32_t RichEditorPattern::CalcLineBeginPosition()
{
    float caretHeight = 0.0f;
    OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight, false, false);
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize());
    auto textOffsetY = caretOffset.GetY() - textPaintOffset.GetY() + (minDet / 2.0);
    Offset textOffset = { 0, textOffsetY };
    auto newPos = paragraphs_.GetIndex(textOffset);
    return newPos;
}

float RichEditorPattern::GetTextThemeFontSize()
{
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    auto textStyle = theme->GetTextStyle();
    return textStyle.GetFontSize().ConvertToPx();
}

int32_t RichEditorPattern::CalcLineEndPosition(int32_t index)
{
    CaretOffsetInfo caretInfo;
    int32_t realCaretOffsetY = 0;
    int32_t realLastClickOffsetY = 0;

    caretInfo = GetCaretOffsetInfoByPosition(index);
    if (NearEqual(richTextRect_.GetY(), contentRect_.GetY())) {
        realLastClickOffsetY = lastClickOffset_.GetY();
        realCaretOffsetY = caretInfo.caretOffsetDown.GetY();
    } else {
        auto scrollOffset =
            caretInfo.caretOffsetDown.GetY() - caretInfo.caretOffsetUp.GetY() + caretInfo.caretOffsetLine.GetY();
        realLastClickOffsetY = lastClickOffset_.GetY() + std::abs(richTextRect_.GetY()) + contentRect_.GetY();
        realCaretOffsetY = scrollOffset + std::abs(richTextRect_.GetY()) + contentRect_.GetY();
    }
    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize());
    Offset textOffset;
    auto rectLineInfo = CalcLineInfoByPosition();
    float textWidth = richTextRect_.Width() + rectLineInfo.GetX();
    float textPaintOffsetY = textPaintOffset.GetY() - (minDet / 2.0);
    float textOffsetClickY = realLastClickOffsetY - textPaintOffsetY;
    float textOffsetDownY = realCaretOffsetY - textPaintOffsetY;
    if (lastClickOffset_.NonNegative()) {
        textOffset = { textWidth, textOffsetClickY };
    } else {
        textOffset = { textWidth, textOffsetDownY };
    }
    auto position = paragraphs_.GetIndex(textOffset);
    return position;
}

int32_t RichEditorPattern::CalcSingleLineBeginPosition(int32_t fixedPos)
{
    float caretHeightDown = 0.0f;
    OffsetF caretOffsetDown = CalcCursorOffsetByPosition(fixedPos, caretHeightDown, true, false);
    float caretHeightUp = 0.0f;
    OffsetF caretOffsetUp = CalcCursorOffsetByPosition(fixedPos, caretHeightUp, false, false);
    bool isCaretPosInLineEnd = !NearEqual(caretOffsetDown.GetX(), caretOffsetUp.GetX(), 0.5f);

    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_RETURN(overlayMod_, false);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    bool cursorNotAtLineStart = NearEqual(caretOffsetOverlay.GetX(), caretOffsetUp.GetX(), 0.5f);

    Offset textOffset;
    if (!cursorNotAtLineStart && !lastClickOffset_.IsNegative()) {
        return fixedPos;
    } else if (isCaretPosInLineEnd && lastClickOffset_.IsNegative()) {
        return lastSelectionRange_.start_;
    } else {
        float caretHeight = 0.0f;
        OffsetF caretOffsetFixed = CalcCursorOffsetByPosition(fixedPos, caretHeight, false, false);
        textOffset = { 0, caretOffsetFixed.GetY() };
    }
    auto position = paragraphs_.GetIndex(textOffset);
    return position;
}

int32_t RichEditorPattern::CalcSingleLineEndPosition(int32_t fixedPos)
{
    auto rectLineInfo = CalcLineInfoByPosition();
    float textWidth = richTextRect_.Width() + rectLineInfo.GetX();

    float caretHeightDown = 0.0f;
    OffsetF caretOffsetDown = CalcCursorOffsetByPosition(fixedPos, caretHeightDown, true, false);
    float caretHeightUp = 0.0f;
    OffsetF caretOffsetUp = CalcCursorOffsetByPosition(fixedPos, caretHeightUp, false, false);
    bool isCaretPosInLineEnd = !NearEqual(caretOffsetDown.GetX(), caretOffsetUp.GetX(), 0.5f);

    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_RETURN(overlayMod_, false);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    bool cursorNotAtLineStart = NearEqual(caretOffsetOverlay.GetX(), caretOffsetUp.GetX(), 0.5f);

    Offset textOffset;
    if (isCaretPosInLineEnd && lastClickOffset_.IsNegative() && lastSelectionRange_.end_ > fixedPos) {
        return lastSelectionRange_.end_;
    } else if (!cursorNotAtLineStart && isCaretPosInLineEnd && fixedPos == caretPosition_) {
        textOffset = { textWidth, caretOffsetOverlay.GetY() };
    } else if (isCaretPosInLineEnd && lastSelectionRange_.end_ <= fixedPos) {
        CursorMoveLineEnd();
        return fixedPos;
    } else if (cursorNotAtLineStart && isCaretPosInLineEnd) {
        return fixedPos;
    } else {
        float caretHeight = 0.0f;
        OffsetF caretOffsetFixed = CalcCursorOffsetByPosition(fixedPos, caretHeight, false, false);
        textOffset = { textWidth, caretOffsetFixed.GetY() };
    }
    auto position = paragraphs_.GetIndex(textOffset);
    return position;
}

bool RichEditorPattern::CursorMoveLineBegin()
{
    int32_t currentPositionIndex = 0;
    if (textSelector_.SelectNothing()) {
        currentPositionIndex = caretPosition_;
    } else {
        currentPositionIndex = textSelector_.GetTextStart();
    }
    CloseSelectOverlay();
    ResetSelection();
    float caretHeightDown = 0.0f;
    Offset textOffset;

    if (0 == currentPositionIndex) {
        SetCaretPosition(currentPositionIndex);
        StartTwinkling();
        return false;
    }
    OffsetF caretOffsetDown = CalcCursorOffsetByPosition(currentPositionIndex, caretHeightDown, true, false);
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize());
    float textPaintOffsetY = textPaintOffset.GetY() - (minDet / 2.0);
    if (lastClickOffset_.NonNegative()) {
        textOffset = { 0, lastClickOffset_.GetY() - textPaintOffsetY };
    } else {
        textOffset = { 0, caretOffsetDown.GetY() - textPaintOffsetY };
    }
    auto position = paragraphs_.GetIndex(textOffset);
    AdjustCursorPosition(position);
    SetCaretPosition(position);
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

bool RichEditorPattern::CursorMoveLineEnd()
{
    int32_t position = 0;
    if (!textSelector_.SelectNothing()) {
        position = textSelector_.GetTextEnd();
        CaretOffsetInfo caretInfo = GetCaretOffsetInfoByPosition(position);
        bool cursorAtLineEnd = !NearEqual(caretInfo.caretOffsetUp.GetX(), caretInfo.caretOffsetDown.GetX(), 0.5f);
        bool cursorAfterNewLine = (position - 1) == GetParagraphEndPosition(position - 1);
        if (cursorAfterNewLine) {
            --position;
        } else if (!cursorAtLineEnd) {
            position = CalcLineEndPosition(textSelector_.GetTextEnd());
        }
    } else {
        position = CalcLineEndPosition();
    }
    CloseSelectOverlay();
    ResetSelection();
    float caretHeight = 0.0f;
    CHECK_NULL_RETURN(overlayMod_, false);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    SetCaretPosition(position);
    StartTwinkling();
    OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight, false, false);
    overlayMod->SetCaretOffsetAndHeight(caretOffset, caretHeight);
    SetLastClickOffset(caretOffset);
    caretAffinityPolicy_ = CaretAffinityPolicy::UPSTREAM_FIRST;
    MoveCaretToContentRect(caretOffset, caretHeight);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void RichEditorPattern::HandleSelectFontStyle(KeyCode code)
{
    auto start = textSelector_.GetTextStart();
    auto end = textSelector_.GetTextEnd();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Change range:[%{public}d-%{public}d] font by key:%{public}d mode:%{public}d",
        start, end, code, isSpanStringMode_);
    CHECK_NULL_VOID(!textSelector_.SelectNothing());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isSpanStringMode_) {
        UpdateSelectStyledStringStyle(start, end, code);
    } else {
        UpdateSelectSpanStyle(start, end, code);
    }
    StopTwinkling();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void RichEditorPattern::HandleOnShowMenu()
{
    CHECK_NULL_VOID(overlayMod_);
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    selectionMenuOffsetByMouse_ = OffsetF(
        parentGlobalOffset_.GetX() + caretOffsetOverlay.GetX(), parentGlobalOffset_.GetY() + caretOffsetOverlay.GetY());
    focusHub->RequestFocusImmediately();
    StartTwinkling();
    ShowSelectOverlay(RectF(), RectF(), IsSelectAll(), TextResponseType::RIGHT_CLICK);
}

PositionType RichEditorPattern::GetPositionTypeFromLine()
{
    auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
    CHECK_NULL_RETURN(overlayMod, PositionType::DEFAULT);
    auto currentCaretOffsetOverlay = overlayMod->GetCaretOffset();
    auto caretOffsetWidth = overlayMod->GetCaretWidth();
    int32_t currentParagraphStart = GetParagraphBeginPosition(caretPosition_);
    bool isParagraphStart = caretPosition_ == currentParagraphStart;
    CHECK_NULL_RETURN(!isParagraphStart, PositionType::PARAGRAPH_START);
    int32_t currentParagraphEnd = GetParagraphEndPosition(caretPosition_);
    bool isParagraphEnd = caretPosition_ == currentParagraphEnd;
    CHECK_NULL_RETURN(!isParagraphEnd, PositionType::PARAGRAPH_END);
    CaretOffsetInfo caretInfo = GetCaretOffsetInfoByPosition();
    bool isCaretAtLineMiddle = NearEqual(caretInfo.caretOffsetDown.GetX(), caretInfo.caretOffsetUp.GetX(), 0.5f);
    CHECK_NULL_RETURN(!isCaretAtLineMiddle, PositionType::DEFAULT);
    bool isCaretAtLineEnd =
        NearEqual(currentCaretOffsetOverlay.GetX(), caretInfo.caretOffsetUp.GetX(), caretOffsetWidth);
    CHECK_NULL_RETURN(!isCaretAtLineEnd, PositionType::LINE_END);
    return PositionType::LINE_START;
}

int32_t RichEditorPattern::HandleSelectWrapper(CaretMoveIntent direction, int32_t fixedPos)
{
    int32_t index = GetCaretPosition();
    switch (direction) {
        case CaretMoveIntent::Left:
            return CaretPositionSelectEmoji(CaretMoveIntent::Left);
        case CaretMoveIntent::Right:
            return CaretPositionSelectEmoji(CaretMoveIntent::Right);
        case CaretMoveIntent::Up:
            return HandleKbVerticalSelection(true);
        case CaretMoveIntent::Down:
            return HandleKbVerticalSelection(false);
        case CaretMoveIntent::LeftWord: {
            return GetLeftWordIndex(index);
        }
        case CaretMoveIntent::RightWord: {
            return GetRightWordIndex(index);
        }
        case CaretMoveIntent::ParagraghBegin:
            return HandleSelectParagraghPos(true);
        case CaretMoveIntent::ParagraghEnd:
            return HandleSelectParagraghPos(false);
        case CaretMoveIntent::LineBegin:
            return CalcSingleLineBeginPosition(fixedPos);
        case CaretMoveIntent::LineEnd:
            return CalcSingleLineEndPosition(fixedPos);
        default:
            return NONE_SELECT_TYPE;
    }
}

int32_t RichEditorPattern::HandleKbVerticalSelection(bool isUp)
{
    float caretHeight = 0.0f;
    float newCaretHeight = 0.0f;
    float careOffsetY = 0.0f;
    int32_t newPos;
    Offset textOffset;
    OffsetF caretOffset = CalcCursorOffsetByPosition(caretPosition_, caretHeight);
    auto minDet = paragraphs_.minParagraphFontSize.value_or(GetTextThemeFontSize()) / 2.0;
    auto positionType = GetPositionTypeFromLine();
    if (isUp) {
        float selectStartHeight = 0.0f;
        OffsetF selectStartOffset = CalcCursorOffsetByPosition(textSelector_.GetTextStart(), selectStartHeight);
        careOffsetY = caretOffset.GetY() - GetTextRect().GetY() - minDet;
        textOffset = Offset(caretOffset.GetX() - GetTextRect().GetX(), careOffsetY);
        CHECK_NULL_RETURN(GreatNotEqual(textOffset.GetY(), 0), 0);
        newPos = paragraphs_.GetIndex(textOffset, true);
        OffsetF newCaretOffset = CalcCursorOffsetByPosition(newPos, newCaretHeight);
        CHECK_EQUAL_RETURN(!textSelector_.SelectNothing() && textSelector_.GetTextEnd() == caretPosition_ &&
            selectStartOffset.GetY() == newCaretOffset.GetY(), true, textSelector_.GetTextStart());
    } else {
        float selectEndHeight = 0.0f;
        OffsetF selectEndOffset = CalcCursorOffsetByPosition(textSelector_.GetEnd(), selectEndHeight);
        careOffsetY = caretOffset.GetY() - GetTextRect().GetY() + caretHeight + (minDet / 2.0);
        float lastLineTop = 0.0f;
        float paragraphSpacing = 0.0f;
        HandleCurrentPositionParagraphInfo(lastLineTop, paragraphSpacing);
        if (positionType == PositionType::LINE_START) {
            auto overlayMod = DynamicCast<RichEditorOverlayModifier>(overlayMod_);
            CHECK_NULL_RETURN(overlayMod, 0);
            auto caretOffsetOverlay = overlayMod->GetCaretOffset();
            auto rectLineInfo = CalcLineInfoByPosition();
            careOffsetY += rectLineInfo.Height();
            IF_TRUE(NearEqual(std::floor(caretOffset.GetY() + rectLineInfo.Height()), std::floor(lastLineTop)),
                careOffsetY += paragraphSpacing);
            textOffset = Offset(caretOffsetOverlay.GetX() - GetTextRect().GetX(), careOffsetY);
        } else {
            IF_TRUE(NearEqual(std::floor(caretOffset.GetY()), std::floor(lastLineTop)),
                careOffsetY += paragraphSpacing);
            textOffset = Offset(caretOffset.GetX() - GetTextRect().GetX(), careOffsetY);
        }
        auto height = paragraphs_.GetHeight();
        CHECK_NULL_RETURN(LessNotEqual(textOffset.GetY(), height), GetTextContentLength());
        newPos = paragraphs_.GetIndex(textOffset, true);
        OffsetF newCaretOffset = CalcCursorOffsetByPosition(newPos, newCaretHeight);
        CHECK_EQUAL_RETURN(!textSelector_.SelectNothing() && textSelector_.GetTextStart() == caretPosition_ &&
            selectEndOffset.GetY() == newCaretOffset.GetY(), true, textSelector_.GetTextEnd());
    }
    return newPos;
}

int32_t RichEditorPattern::HandleSelectParagraghPos(bool direction)
{
    int32_t newPos = 0;
    CloseSelectOverlay();
    ResetSelection();
    if (direction) {
        newPos = GetParagraphBeginPosition(caretPosition_);
        if (newPos == caretPosition_ && caretPosition_ > 0) {
            newPos = GetParagraphBeginPosition(caretPosition_ - 1);
        }
    } else {
        newPos = GetParagraphEndPosition(caretPosition_);
        if (newPos == caretPosition_ && caretPosition_ < static_cast<int32_t>(GetTextContentLength())) {
            newPos = GetParagraphEndPosition(caretPosition_ + 1);
        }
    }
    return newPos;
}

void RichEditorPattern::HandleSelectFontStyleWrapper(KeyCode code, TextStyle& spanStyle)
{
    switch (code) {
        case KeyCode::KEY_B:
            if (spanStyle.GetFontWeight() == Ace::FontWeight::BOLD) {
                spanStyle.SetFontWeight(Ace::FontWeight::NORMAL);
            } else {
                spanStyle.SetFontWeight(Ace::FontWeight::BOLD);
            }
            break;
        case KeyCode::KEY_I:
            if (spanStyle.GetFontStyle() == OHOS::Ace::FontStyle::ITALIC) {
                spanStyle.SetFontStyle(OHOS::Ace::FontStyle::NORMAL);
            } else {
                spanStyle.SetFontStyle(OHOS::Ace::FontStyle::ITALIC);
            }
            break;
        case KeyCode::KEY_U:
            if (spanStyle.GetTextDecoration() == TextDecoration::UNDERLINE) {
                spanStyle.SetTextDecoration(TextDecoration::NONE);
            } else {
                spanStyle.SetTextDecoration(TextDecoration::UNDERLINE);
            }
            break;
        default:
            LOGW("Unsupported select operation for HandleSelectFrontStyle");
            return;
    }
}

void RichEditorPattern::AIDeleteComb(int32_t start, int32_t end, int32_t& aiPosition, bool direction)
{
    std::u16string selectTextContent;
    GetContentBySpans(selectTextContent);
    // get select content
    std::u16string selectData16 = selectTextContent.substr(static_cast<int32_t>(start), static_cast<int32_t>(end - start));
    std::string selectData = StringUtils::Str16ToStr8(selectData16);
    int32_t aiPosStart;
    int32_t aiPosEnd;
    int32_t caretPosition;
    int32_t size = 1;

    if (direction) {
        caretPosition = end - start - size;
        DataDetectorMgr::GetInstance().AdjustWordSelection(caretPosition, selectData, aiPosStart, aiPosEnd);
        aiPosition = aiPosStart + start;
    } else {
        caretPosition = 0;
        DataDetectorMgr::GetInstance().AdjustWordSelection(caretPosition, selectData, aiPosStart, aiPosEnd);
        aiPosition = aiPosEnd + start;
    }
    if (aiPosStart < 0 || aiPosEnd < 0) {
        aiPosition = GetCaretPosition();
    }
}

bool RichEditorPattern::HandleOnDeleteComb(bool backward)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnDeleteComb backward=%{public}d", backward);
    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        SetCaretPosition(textSelector_.GetTextStart());
        ResetSelection();
    }
    if (backward) {
        DeleteBackwardWord();
    } else {
        DeleteForwardWord();
    }
    MoveCaretToContentRect();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void RichEditorPattern::DeleteBackwardWord()
{
    CHECK_NULL_VOID(caretPosition_ != 0);
    int32_t startIndex = caretPosition_;
    int32_t spaceEndIndex = startIndex;
    AdjustIndexSkipSpace(spaceEndIndex, MoveDirection::BACKWARD);
    int32_t wordEndIndex = std::max(0, spaceEndIndex - 1);
    AdjustWordSelection(wordEndIndex, spaceEndIndex);
    DeleteBackward(startIndex - wordEndIndex);
}

void RichEditorPattern::DeleteForwardWord()
{
    CHECK_NULL_VOID(caretPosition_ != GetTextContentLength());
    int32_t startIndex = caretPosition_;
    int32_t spaceEndIndex = startIndex;
    AdjustIndexSkipSpace(spaceEndIndex, MoveDirection::FORWARD);
    int32_t wordEndIndex = std::min(spaceEndIndex + 1, GetTextContentLength());
    AdjustWordSelection(spaceEndIndex, wordEndIndex);
    DeleteForward(wordEndIndex - startIndex);
}

const std::list<RefPtr<UINode>>& RichEditorPattern::GetAllChildren() const
{
    childNodes_.clear();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, childNodes_);
    auto children = host->GetChildren();
    for (const auto& child: children) {
        childNodes_.push_back(child);
    }
    return childNodes_;
}

void RichEditorPattern::HandleTripleClickEvent(OHOS::Ace::GestureEvent& info)
{
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "HandleTripleClickEvent");
    CHECK_EQUAL_VOID(IsPreviewTextInputting(), true);
    CHECK_EQUAL_VOID(IsDragging(), true);
    bool isMouseClickWithShift = shiftFlag_ && info.GetSourceDevice() == SourceType::MOUSE;
    CHECK_EQUAL_VOID(isMouseClickWithShift, true);
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_EQUAL_VOID(focusHub->IsFocusable(), false);
    auto textPaintOffset = GetTextRect().GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    int32_t pos = paragraphs_.GetIndex(textOffset);

    int32_t start = 0;
    int32_t end = 0;
    auto& paragraphInfoList = paragraphs_.GetParagraphs();
    if (!paragraphInfoList.empty() && pos == paragraphInfoList.back().end) {
        start = paragraphInfoList.back().start;
        end = paragraphInfoList.back().end;
    } else {
        for (const auto& paragraph : paragraphInfoList) {
            if (pos >= paragraph.start && pos < paragraph.end) {
                start = paragraph.start;
                end = paragraph.end;
                break;
            }
        }
    }
    if (!paragraphInfoList.empty() && paragraphInfoList.back().end != end) {
        --end;
    }
    end = std::min(GetTextContentLength(), end);
    start = std::min(GetTextContentLength(), start);
    CHECK_EQUAL_VOID(start > end, true);
    TripleClickSection(info, start, end, pos);
}

void RichEditorPattern::UpdateSelectionByTouchMove(const Offset& touchOffset)
{
    // While previewing + long press and move, then shall select content.
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    Offset textOffset = ConvertTouchOffsetToTextOffset(touchOffset);
    auto positionWithAffinity = paragraphs_.GetGlyphPositionAtCoordinate(textOffset);
    SetCaretPositionWithAffinity(positionWithAffinity);
    MoveCaretToContentRect();
    int32_t currentPosition = GreatNotEqual(textOffset.GetY(), paragraphs_.GetHeight())
                                ? GetTextContentLength()
                                : caretPosition_;
    IF_TRUE(GetTextContentLength() > 0, SetMagnifierLocalOffset(touchOffset));
    auto [initSelectStart, initSelectEnd] = initSelector_;
    int32_t start = std::min(initSelectStart, currentPosition);
    int32_t end = std::max(initSelectEnd, currentPosition);
    if (start == textSelector_.GetTextStart()) {
        StartVibratorByIndexChange(end, textSelector_.GetTextEnd());
    } else {
        StartVibratorByIndexChange(start, textSelector_.GetTextStart());
    }
    HandleSelectionChange(start, end);
    TriggerAvoidOnCaretChange();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::HideMenu()
{
    selectOverlay_->HideMenu();
}

void RichEditorPattern::OnSelectionMenuOptionsUpdate(
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    selectOverlay_->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

bool RichEditorPattern::CheckTripClickEvent(GestureEvent& info)
{
    clickInfo_.push_back(info.GetTimeStamp());
    if (clickInfo_.size() > MAX_CLICK) {
        clickInfo_.erase(clickInfo_.begin());
    }
    if (clickInfo_.size() == MAX_CLICK) {
        std::chrono::duration<float, std::ratio<1, InputAIChecker::SECONDS_TO_MILLISECONDS>>
            clickTimeIntervalOne = clickInfo_[1] - clickInfo_[0];
        std::chrono::duration<float, std::ratio<1, InputAIChecker::SECONDS_TO_MILLISECONDS>>
            clickTimeIntervalTwo = clickInfo_[2] - clickInfo_[1];
        if (clickTimeIntervalOne.count() < DOUBLE_CLICK_INTERVAL_MS
            && clickTimeIntervalTwo.count() < DOUBLE_CLICK_INTERVAL_MS) {
            return true;
        }
    }
    return false;
}

void RichEditorPattern::PreferredParagraph()
{
    CHECK_NULL_VOID(typingTextStyle_.has_value());
    if (presetParagraph_) {
        presetParagraph_->Reset();
        presetParagraph_ = nullptr;
    }
    std::string textContent;
    textContent = "a";
    TextStyle textStyle;
    textStyle = typingTextStyle_.value();
    ParagraphStyle paraStyle {
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = textStyle.GetTextOverflow(),
        .fontSize = textStyle.GetFontSize().ConvertToPx(),
        .halfLeading = textStyle.GetHalfLeading(),
        .paragraphSpacing = textStyle.GetParagraphSpacing() };
    presetParagraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(presetParagraph_);
    presetParagraph_->PushStyle(textStyle);
    presetParagraph_->AddText(StringUtils::Str8ToStr16(textContent));
    presetParagraph_->Build();
    presetParagraph_->Layout(std::numeric_limits<double>::infinity());
}

void RichEditorPattern::TripleClickSection(GestureEvent& info, int32_t start, int32_t end, int32_t pos)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    textSelector_.Update(start, end);
    if (IsShowHandle()) {
        SetCaretPositionWithAffinity({ end, TextAffinity::UPSTREAM });
        MoveCaretToContentRect();
    }
    UpdateSelectionType(GetSpansInfo(start, end, GetSpansMethod::ONSELECT));
    if (info.GetSourceDevice() == SourceType::TOUCH) {
        showSelect_ = true;
        RequestKeyboard(false, true, true);
        HandleOnEditChanged(true);
        CalculateHandleOffsetAndShowOverlay();
        selectOverlay_->ProcessOverlay({ .menuIsShow = !selectOverlay_->GetIsHandleMoving(), .animation = true });
    }
    if (info.GetSourceDevice() == SourceType::TOUCH && start == end) {
        selectOverlay_->SetIsSingleHandle(true);
    }
    if (textSelector_.SelectNothing()) {
        textSelector_.Update(pos, pos);
    } else {
        StopTwinkling();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorPattern::RequestKeyboardToEdit()
{
    CHECK_NULL_VOID(!isEditing_ && HasFocus());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "request keyboard and enter edit");
    RequestKeyboard(false, true, true);
    HandleOnEditChanged(true);
}

bool RichEditorPattern::IsResponseRegionExpandingNeededForStylus(const TouchEvent& touchEvent) const
{
    if (touchEvent.sourceTool != SourceTool::PEN || touchEvent.type != TouchType::DOWN) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (!focusHub->IsFocusable() || !host->IsVisible()) {
        return false;
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto opacity = renderContext->GetOpacity();
    // if opacity is 0.0f, no need to hit frameNode.
    if (NearZero(opacity.value_or(1.0f))) {
        return false;
    }
    return true;
}

RectF RichEditorPattern::ExpandDefaultResponseRegion(RectF& rect)
{
    return rect + NG::SizeF(0, OHOS::Ace::HOT_AREA_ADJUST_SIZE.ConvertToPx() * OHOS::Ace::HOT_AREA_EXPAND_TIME) +
           NG::OffsetF(0, -OHOS::Ace::HOT_AREA_ADJUST_SIZE.ConvertToPx());
}

bool RichEditorPattern::InsertOrDeleteSpace(int32_t index)
{
    // delete or insert space
    if (index < 0 || index >= GetTextContentLength()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "index is invalid, index=%{public}d", index);
        return false;
    }
    bool success = SetCaretPosition(index);
    CHECK_NULL_RETURN(success, false);
    CloseSelectOverlay();
    ResetSelection();

    auto curIt = GetSpanIter(index);
    if (curIt != spans_.end()) {
        std::u16string curText = (*curIt)->content;
        if ((*curIt)->spanItemType == SpanItemType::NORMAL
            && index >= (*curIt)->rangeStart && curText[index - (*curIt)->rangeStart] == u' ') {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "delete forward");
            DeleteForward(1);
            return true;
        }
    }

    auto preIt = GetSpanIter(index - 1);
    if (preIt != spans_.end()) {
        std::u16string preText = (*preIt)->content;
        if ((*preIt)->spanItemType == SpanItemType::NORMAL
            && index - 1 >= (*preIt)->rangeStart && preText[index - 1 - (*preIt)->rangeStart] == u' ') {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "delete backward");
            DeleteBackward(1);
            return true;
        }
    }

    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "insert value");
    InsertValue(u" ", true);
    return true;
}

void RichEditorPattern::DeleteRange(int32_t start, int32_t end, bool isIME)
{
    if (start > end) {
        std::swap(start, end);
    }
    start = std::max(0, start);
    end = std::min(GetTextContentLength(), end);
    if (start > GetTextContentLength() || end < 0 || start == end) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "start=%{public}d, end=%{public}d, not in the range", start, end);
        return;
    }
    CHECK_NULL_VOID(!IsPreviewTextInputting());
    SetCaretPosition(start);
    auto length = end - start;
    if (isSpanStringMode_) {
        DeleteValueInStyledString(start, length, true, false);
        return;
    }
    OperationRecord record;
    record.beforeCaretPosition = caretPosition_;
    RichEditorChangeValue changeValue;
    CHECK_NULL_VOID(BeforeChangeText(changeValue, record, RecordType::DEL_FORWARD, length));
    std::u16string textContent;
    GetContentBySpans(textContent);
    auto realEnd = std::clamp(caretPosition_ + length, 0, static_cast<int32_t>(textContent.length()));
    std::u16string deleteText = textContent.substr(
        static_cast<uint32_t>(std::clamp(caretPosition_, 0, static_cast<int32_t>(textContent.length()))),
        static_cast<uint32_t>(realEnd - caretPosition_));
    if (caretPosition_ != GetTextContentLength()) {
        RichEditorDeleteValue info;
        info.SetOffset(caretPosition_);
        info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::FORWARD);
        info.SetLength(length);
        int32_t currentPosition = caretPosition_;
        if (!spans_.empty()) {
            CalcDeleteValueObj(currentPosition, length, info);
            bool doDelete = DoDeleteActions(currentPosition, length, info);
            CHECK_NULL_VOID(doDelete);
        }
    }
    CHECK_NULL_VOID(deleteText.length() != 0);
    ClearRedoOperationRecords();
    record.deleteText = deleteText;
    record.afterCaretPosition = caretPosition_;
    AddOperationRecord(record);
    AfterContentChange(changeValue);
}

void RichEditorPattern::HandleOnPageUp()
{
    HandlePageScroll(true);
}

void RichEditorPattern::HandleOnPageDown()
{
    HandlePageScroll(false);
}

void RichEditorPattern::HandlePageScroll(bool isPageUp)
{
    auto visibleRect = selectOverlay_->GetVisibleRect();
    float distance = isPageUp ? visibleRect.Height() : -visibleRect.Height();
    RectF curCaretRect = GetCaretRect();
    auto height = paragraphs_.GetHeight();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "PageScroll isPageUp:%{public}d distance:%{public}f paragraphsHeight:%{public}f",
        isPageUp, distance, height);
    CloseSelectOverlay();
    ResetSelection();
    OnScrollCallback(distance, SCROLL_FROM_JUMP);
    auto paintOffset = selectOverlay_->GetPaintOffsetWithoutTransform();
    float offsetY = isPageUp ? visibleRect.Top() : visibleRect.Bottom();
    auto localOffset = Offset(curCaretRect.GetX(), offsetY - paintOffset.GetY());
    auto textOffset = ConvertTouchOffsetToTextOffset(localOffset);
    auto positionWithAffinity = paragraphs_.GetGlyphPositionAtCoordinate(textOffset);
    // If scrolling to the first or last line, move the cursor to the beginning or end of the line
    if (isPageUp && LessOrEqual(textOffset.GetY(), 0)) {
        positionWithAffinity = PositionWithAffinity(0, TextAffinity::DOWNSTREAM);
    } else if (!isPageUp && GreatOrEqual(textOffset.GetY(), height)) {
        positionWithAffinity = PositionWithAffinity(GetTextContentLength(), TextAffinity::UPSTREAM);
    }
    SetCaretPositionWithAffinity(positionWithAffinity);
    IF_TRUE(isEditing_, StartTwinkling());
}

TextStyle RichEditorPattern::GetDefaultTextStyle()
{
    auto theme = GetTheme<RichEditorTheme>();
    TextStyle style = theme ? theme->GetTextStyle() : TextStyle();
    style.SetFontSize(Dimension(DEFAULT_TEXT_SIZE, DimensionUnit::FP));
    style.SetFontFeatures(ParseFontFeatureSettings("\"pnum\" 1"));
    style.SetFontFamilies({ "HarmonyOS Sans" });
    return style;
}

bool RichEditorPattern::IsShowTranslate()
{
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richEditorTheme, false);
    return richEditorTheme->GetTranslateIsSupport();
}

bool RichEditorPattern::IsShowSearch()
{
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(richEditorTheme, false);
    return richEditorTheme->GetSearchIsSupport();
}

bool RichEditorPattern::IsShowAIWrite()
{
    CHECK_NULL_RETURN(!textSelector_.SelectNothing(), false);
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        return false;
    }

    if (copyOption_ == CopyOptions::None) {
        return false;
    }
    auto theme = GetTheme<RichEditorTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto bundleName = theme->GetAIWriteBundleName();
    auto abilityName = theme->GetAIWriteAbilityName();
    if (bundleName.empty() || abilityName.empty()) {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Failed to obtain AI write package name!");
        return false;
    }
    aiWriteAdapter_->SetBundleName(bundleName);
    aiWriteAdapter_->SetAbilityName(abilityName);

    auto isAISupport = false;
    if (theme->GetAIWriteIsSupport() == "true") {
        isAISupport = true;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Whether the device supports AI write: %{public}d, nodeId: %{public}d",
        isAISupport, host->GetId());
    return isAISupport;
}

void RichEditorPattern::GetAIWriteInfo(AIWriteInfo& info)
{
    CHECK_NULL_VOID(!textSelector_.SelectNothing());
    info.firstHandle = textSelector_.firstHandle.ToString();
    info.secondHandle = textSelector_.secondHandle.ToString();
    info.selectStart = textSelector_.GetTextStart();
    info.selectEnd = textSelector_.GetTextEnd();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    info.componentType = host->GetTag();

    // serialize the sentenced-level text
    auto textSize = static_cast<int32_t>(GetTextForDisplay().length()) + placeholderCount_;
    RefPtr<SpanString> spanString = ToStyledString(0, textSize);
    auto contentAll = spanString->GetU16string();
    auto sentenceStart = 0;
    auto sentenceEnd = textSize;
    for (int32_t i = info.selectStart; i >= 0; --i) {
        if (aiWriteAdapter_->IsSentenceBoundary(contentAll[i])) {
            sentenceStart = i + 1;
            break;
        }
    }
    for (int32_t i = info.selectEnd; i < textSize; i++) {
        if (aiWriteAdapter_->IsSentenceBoundary(contentAll[i])) {
            sentenceEnd = i;
            break;
        }
    }
    info.start = info.selectStart - sentenceStart;
    info.end = info.selectEnd - sentenceStart;
    spanString = ToStyledString(sentenceStart, sentenceEnd);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "Sentence range=[%{public}d-%{public}d], content=" SEC_PLD(%{public}s),
        sentenceStart, sentenceEnd, SEC_PARAM(spanString->GetString().c_str()));
    spanString->EncodeTlv(info.sentenceBuffer);

    // serialize the selected text
    spanString = ToStyledString(info.selectStart, info.selectEnd);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "Selected range=[%{public}d-%{public}d], content=" SEC_PLD(%{public}s),
        info.selectStart, info.selectEnd, SEC_PARAM(spanString->GetString().c_str()));
    spanString->EncodeTlv(info.selectBuffer);
    info.selectLength = static_cast<int32_t>(aiWriteAdapter_->GetSelectLengthOnlyText(spanString->GetU16string()));
}

void RichEditorPattern::HandleOnAIWrite()
{
    aiWriteAdapter_->SetAIWrite(true);
    AIWriteInfo info;
    GetAIWriteInfo(info);
    CloseSelectOverlay();
    ResetSelection();
    CloseKeyboard(false);

    auto callback = [weak = WeakClaim(this), info](std::vector<uint8_t>& buffer) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleAIWriteResult(info.selectStart, info.selectEnd, buffer);
        auto aiWriteAdapter = pattern->aiWriteAdapter_;
        CHECK_NULL_VOID(aiWriteAdapter);
        aiWriteAdapter->CloseModalUIExtension();
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    aiWriteAdapter_->SetPipelineContext(WeakClaim(pipeline));
    aiWriteAdapter_->ShowModalUIExtension(info, callback);
}

SymbolSpanOptions RichEditorPattern::GetSymbolSpanOptions(const RefPtr<SpanItem>& spanItem)
{
    CHECK_NULL_RETURN(spanItem, {});
    TextStyle textStyle = GetDefaultTextStyle();
    UseSelfStyle(spanItem->fontStyle, spanItem->textLineStyle, textStyle);
    SymbolSpanOptions options;
    options.style = textStyle;
    options.offset = caretPosition_;
    options.resourceObject = spanItem->GetResourceObject();
    options.symbolId = spanItem->GetSymbolId();
    return options;
}

void RichEditorPattern::ReplacePlaceholderWithCustomSpan(
    const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex)
{
    if (isSpanStringMode_) {
        auto customSpanItem = DynamicCast<CustomSpanItem>(spanItem);
        auto customSpan = MakeRefPtr<CustomSpan>();
        if (customSpanItem->onMeasure.has_value()) {
            customSpan->SetOnMeasure(customSpanItem->onMeasure.value());
        }
        if (customSpanItem->onDraw.has_value()) {
            customSpan->SetOnDraw(customSpanItem->onDraw.value());
        }
        auto spanString = MakeRefPtr<MutableSpanString>(customSpan);
        InsertStyledStringByPaste(spanString);
    } else {
        auto customSpanItem = DynamicCast<PlaceholderSpanItem>(spanItem);
        CHECK_NULL_VOID(customSpanItem);
        auto customNode = customSpanItem->GetCustomNode();
        SpanOptionBase options;
        options.offset = caretPosition_;
        AddPlaceholderSpan(customNode, options);
    }
    textIndex = index + PLACEHOLDER_LENGTH;
}

void RichEditorPattern::ReplacePlaceholderWithSymbolSpan(
    const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex)
{
    auto options = GetSymbolSpanOptions(spanItem);
    options.offset = caretPosition_;
    AddSymbolSpan(options, false, caretPosition_);
    textIndex = index + PLACEHOLDER_LENGTH;
}

void RichEditorPattern::ReplacePlaceholderWithImageSpan(
    const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex)
{
    auto imageSpanItem = DynamicCast<ImageSpanItem>(spanItem);
    CHECK_NULL_VOID(imageSpanItem);
    auto options = imageSpanItem->options;
    options.offset = caretPosition_;
    if (isSpanStringMode_) {
        auto spanString = MakeRefPtr<SpanString>(options);
        InsertStyledStringByPaste(spanString);
    } else {
        AddImageSpan(options, true, caretPosition_, true);
    }
    textIndex = index + PLACEHOLDER_LENGTH;
}

void RichEditorPattern::ReplacePlaceholderWithRawSpans(
    const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex)
{
    switch (spanItem->spanItemType) {
        case SpanItemType::SYMBOL:
            ReplacePlaceholderWithSymbolSpan(spanItem, index, textIndex);
            return;
        case SpanItemType::CustomSpan:
            ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
            return;
        case SpanItemType::IMAGE:
            ReplacePlaceholderWithImageSpan(spanItem, index, textIndex);
            return;
        default:
            return;
    }
}

void RichEditorPattern::AddSpansAndReplacePlaceholder(RefPtr<SpanString>& spanString)
{
    auto content = spanString->GetU16string();
    size_t textIndex = 0;
    size_t index = content.find(PLACEHOLDER_MARK);

    while (index != std::u16string::npos) {
        if (textIndex < index) {
            auto subSpan = spanString->GetSubSpanString(textIndex, index - textIndex);
            AddSpanByPasteData(subSpan);
        }
        auto key = content.substr(index, PLACEHOLDER_LENGTH);
        if (placeholderSpansMap_.find(key) == placeholderSpansMap_.end()) {
            index = content.find(PLACEHOLDER_MARK, index + 1);
            continue;
        }
        auto spanItem = placeholderSpansMap_[key];
        if (!spanItem) {
            index = content.find(PLACEHOLDER_MARK, index + 1);
            continue;
        }
        ReplacePlaceholderWithRawSpans(spanItem, index, textIndex);
        index = content.find(PLACEHOLDER_MARK, index + 1);
    }
    if (textIndex < content.length()) {
        auto subSpan = spanString->GetSubSpanString(textIndex, content.length() - textIndex);
        AddSpanByPasteData(subSpan);
    }
}

void RichEditorPattern::InsertSpanByBackData(RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(spanString);
    if (textSelector_.IsValid()) {
        SetCaretPosition(textSelector_.GetTextStart());
        DeleteForward(textSelector_.GetTextStart(), textSelector_.GetTextEnd() - textSelector_.GetTextStart());
        ResetSelection();
    }
    if (placeholderSpansMap_.empty()) {
        AddSpanByPasteData(spanString);
    } else {
        AddSpansAndReplacePlaceholder(spanString);
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorPattern::HandleAIWriteResult(int32_t start, int32_t end, std::vector<uint8_t>& buffer)
{
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(buffer);
    if (spanString->GetSpanItems().empty()) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "Backfilling results range=[%{public}d--%{public}d], content=" SEC_PLD(%{public}s),
        start, end, SEC_PARAM(spanString->GetString().c_str()));

    textSelector_.Update(start, end);
    auto length = end - start;
    CHECK_NULL_VOID(length > 0);
    DeleteBackward(length);
    InsertSpanByBackData(spanString);
    BeforeIMEInsertValue(UtfUtils::Str8ToStr16(spanString->GetString()));
    InsertValue(u"");
}

bool RichEditorPattern::IsTextEditableForStylus() const
{
    CHECK_NULL_RETURN(!customKeyboardBuilder_, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (!focusHub->IsFocusable() || !host->IsVisible()) {
        return false;
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto opacity = renderContext->GetOpacity();
    // if opacity is 0.0f, no need to hit frameNode.
    if (NearZero(opacity.value_or(1.0f))) {
        return false;
    }
    return true;
}

void RichEditorPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    if (customKeyboardBuilder_) {
        json->Put("CustomKeyboard, Attached", std::to_string(isCustomKeyboardAttached_).c_str());
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto richEditorTheme = GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    json->Put("caret offset", GetCaretRect().GetOffset().ToString().c_str());
    json->Put("caret height",
        std::to_string(NearZero(GetCaretRect().Height()) ? richEditorTheme->GetDefaultCaretHeight().ConvertToPx()
                                                         : GetCaretRect().Height())
            .c_str());
    json->Put("text rect", richTextRect_.ToString().c_str());
    json->Put("content rect", contentRect_.ToString().c_str());
    auto richEditorPaintOffset = host->GetPaintRectOffsetNG(false, true);
    bool hasRenderTransform = selectOverlay_->HasRenderTransform();
    if (hasRenderTransform) {
        richEditorPaintOffset = selectOverlay_->GetPaintOffsetWithoutTransform();
    }
    json->Put("hasRenderTransform", std::to_string(hasRenderTransform).c_str());
    json->Put("richEditorPaintOffset", richEditorPaintOffset.ToString().c_str());
    auto selectOverlayInfo = selectOverlay_->GetSelectOverlayInfo();
    CHECK_NULL_VOID(selectOverlayInfo);
    json->Put("selectOverlay info", selectOverlayInfo->ToString().c_str());
}

RectF RichEditorPattern::GetCaretRelativeRect()
{
    CHECK_NULL_RETURN(caretTwinkling_, RectF(-1, -1, -1, -1));
    auto [caretOffset, caretHeight] = CalculateCaretOffsetAndHeight();
    CHECK_NULL_RETURN(overlayMod_, RectF(0, 0, 0, 0));
    auto caretWidth = DynamicCast<RichEditorOverlayModifier>(overlayMod_)->GetCaretWidth();
    return RectF(caretOffset.GetX(), caretOffset.GetY(), caretWidth, caretHeight);
}

void RichEditorPattern::OnReportRichEditorEvent(const std::string& event)
{
    std::string value = RICHEDITOR + event;
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(EVENT, value);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "nodeId:[%{public}d] RichEditor reportComponentChangeEvent %{public}s", frameId_,
        event.c_str());
}
} // namespace OHOS::Ace::NG
