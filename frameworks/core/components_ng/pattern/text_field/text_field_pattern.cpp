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

#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include <algorithm>
#include <cstdint>
#include <optional>
#include <regex>
#include <stdint.h>
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/event/ace_events.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif
#ifdef ENABLE_DRAG_FRAMEWORK
#include "core/common/udmf/udmf_client.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension BORDER_DEFAULT_WIDTH = 0.0_vp;
constexpr Dimension ERROR_BORDER_WIDTH = 1.0_vp;
constexpr Dimension OVER_COUNT_BORDER_WIDTH = 1.0_vp;
constexpr Dimension INLINE_BORDER_WIDTH = 2.0_vp;
constexpr Dimension UNDERLINE_NORMAL_HEIGHT = 48.0_vp;
constexpr Dimension UNDERLINE_NORMAL_PADDING = 12.0_vp;
constexpr Dimension DEFAULT_FONT = Dimension(16, DimensionUnit::FP);
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.5f;
constexpr float DOUBLECLICK_INTERVAL_MS = 300.0f;
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr uint32_t OBSCURE_SHOW_TICKS = 3;
constexpr uint32_t FIND_TEXT_ZERO_INDEX = 1;
constexpr char16_t OBSCURING_CHARACTER = u'•';
constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*';
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
const std::string DIGIT_WHITE_LIST = "[0-9]";
const std::string PHONE_WHITE_LIST = "[\\d\\-\\+\\*\\#]+";
const std::string EMAIL_WHITE_LIST = "[\\w.\\@]";
const std::string URL_WHITE_LIST = "[a-zA-z]+://[^\\s]*";
const std::string SHOW_PASSWORD_SVG = "SYS_SHOW_PASSWORD_SVG";
const std::string HIDE_PASSWORD_SVG = "SYS_HIDE_PASSWORD_SVG";

void SwapIfLarger(int32_t& a, int32_t& b)
{
    if (a > b) {
        std::swap(a, b);
    }
}

std::string ConvertFontFamily(const std::vector<std::string>& fontFamily)
{
    std::string result;
    for (const auto& item : fontFamily) {
        result += item;
        result += ",";
    }
    result = result.substr(0, result.length() - 1);
    return result;
}

} // namespace

std::u16string TextFieldPattern::CreateObscuredText(int32_t len)
{
    std::u16string obscuredText;
    if (Localization::GetInstance()->GetLanguage() == "ar") { // ar is the abbreviation of Arabic.
        obscuredText = std::u16string(len, OBSCURING_CHARACTER_FOR_AR);
    } else {
        obscuredText = std::u16string(len, OBSCURING_CHARACTER);
    }
    return obscuredText;
}

std::u16string TextFieldPattern::CreateDisplayText(
    const std::string& content, int32_t nakedCharPosition, bool needObscureText)
{
    if (!content.empty() && needObscureText) {
        auto text =
            TextFieldPattern::CreateObscuredText(static_cast<int32_t>(StringUtils::ToWstring(content).length()));
        if (nakedCharPosition >= 0 && nakedCharPosition < static_cast<int32_t>(content.length())) {
            auto rawContent = StringUtils::Str8ToStr16(content);
            text[nakedCharPosition] = rawContent[nakedCharPosition];
        }
        return text;
    }
    return StringUtils::Str8ToStr16(content);
}

float TextFieldPattern::GetTextOrPlaceHolderFontSize()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, 0.0f);
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto textFieldLayoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    Dimension fontSize;
    if (textFieldLayoutProperty->HasFontSize() &&
        textFieldLayoutProperty->GetFontSizeValue(Dimension()).IsNonNegative()) {
        fontSize = textFieldLayoutProperty->GetFontSizeValue(Dimension());
    } else {
        return textFieldTheme ? static_cast<float>(textFieldTheme->GetFontSize().ConvertToPx())
                              : static_cast<float>(DEFAULT_FONT.ConvertToPx());
    }
    return std::min(static_cast<float>(fontSize.ConvertToPx()), contentRect_.Height());
}

TextFieldPattern::TextFieldPattern() : twinklingInterval_(TWINKLING_INTERVAL_MS)
{
    if (PipelineBase::GetCurrentContext() &&
        // for normal app add version protection, enable keyboard as default start from API 10 or higher
        PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9 &&
        // UIExtension Ability focus windowId setted by component user window, can not enable keyboard as default
        !PipelineBase::GetCurrentContext()->IsFocusWindowIdSetted()) {
        needToRequestKeyboardOnFocus_ = true;
    }
    contentController_ = MakeRefPtr<ContentController>(WeakClaim(this));
    selectController_ = MakeRefPtr<TextSelectController>(WeakClaim(this));
    selectController_->InitContentController(contentController_);
}

TextFieldPattern::~TextFieldPattern()
{
    LOGI("Destruction of text field.");
    if (textEditingController_) {
        textEditingController_->Clear();
        textEditingController_->RemoveObserver(WeakClaim(this));
    }
    CloseSelectOverlay();
    // If soft keyboard is still exist, close it.
    if (HasConnection()) {
#if defined(ENABLE_STANDARD_INPUT)
        LOGI("Destruction of text field, close input method.");
        MiscServices::InputMethodController::GetInstance()->Close();
#else
        connection_->Close(GetInstanceId());
        connection_ = nullptr;
#endif
    }
    if (isCustomKeyboardAttached_) {
        CloseCustomKeyboard();
    }
}

bool TextFieldPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    contentRect_ = dirty->GetGeometryNode()->GetContentRect();
    frameRect_ = dirty->GetGeometryNode()->GetFrameRect();
    if (!inlineState_.saveInlineState) {
        inlineState_.saveInlineState = true;
        inlineState_.frameRect = frameRect_;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textFieldLayoutAlgorithm = DynamicCast<TextFieldLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textFieldLayoutAlgorithm, false);
    auto paragraph = textFieldLayoutAlgorithm->GetParagraph();
    float paragraphWidth = 0.0f;
    if (paragraph) {
        paragraph_ = paragraph;
        paragraphWidth = paragraph->GetLongestLine();
    }
    auto errorParagraph = textFieldLayoutAlgorithm->GetErrorParagraph();
    if (errorParagraph) {
        errorParagraph_ = errorParagraph;
    }
    if (!IsDragging()) {
        dragParagraph_ = paragraph_;
    }
    auto textRect = textFieldLayoutAlgorithm->GetTextRect();
    if (!(needToRefreshSelectOverlay_ &&
            (!NearEqual(paragraphWidth, paragraphWidth_) || !NearEqual(textRect, textRect_))) ||
        (LessOrEqual(paragraphWidth, -Infinity<float>()) && LessOrEqual(paragraphWidth_, -Infinity<float>()))) {
        needToRefreshSelectOverlay_ = false;
    }
    paragraphWidth_ = paragraphWidth;
    textRect_ = textRect;
    parentGlobalOffset_ = textFieldLayoutAlgorithm->GetParentGlobalOffset();
    FireOnTextChangeEvent();
    UpdateSelectController();
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    AdjustTextInReasonableArea();
    UpdateCaretRect();
    UpdateCaretInfoToController();
    auto hostLayoutProperty =
        dirty->GetHostNode() ? dirty->GetHostNode()->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
    if (hostLayoutProperty) {
        hostLayoutProperty->ResetTextAlignChanged();
    }
    if (needToRefreshSelectOverlay_) {
        StopTwinkling();
        ProcessOverlay();
        needToRefreshSelectOverlay_ = false;
    }
    if (inlineSelectAllFlag_) {
        HandleOnSelectAll(false, true);
        inlineSelectAllFlag_ = false;
    }
    if (mouseStatus_ == MouseStatus::RELEASED) {
        mouseStatus_ = MouseStatus::NONE;
    }
    StopScrollable();
    if (IsTextArea()) {
        CheckScrollable();
    } else {
        SetScrollEnable(GreatNotEqual(textRect_.Width(), contentRect_.Width()));
    }
    UpdateScrollBarOffset();
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->ScheduleDisappearDelayTask();
        }
    }
    return true;
}

bool TextFieldPattern::HasFocus() const
{
    auto focusHub = GetFocusHub();

    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

void TextFieldPattern::UpdateCaretInfoToController() const // todo确定更新时机
{
    CHECK_NULL_VOID(HasFocus());
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    LOGD("UpdateCaretInfoToController, left %{public}f, top %{public}f, width %{public}f, height %{public}f",
        cursorInfo.left, cursorInfo.top, cursorInfo.width, cursorInfo.height);
    MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
    LOGD("Start %{public}d, end %{public}d", selectController_->GetStart(), selectController_->GetEnd());
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        StringUtils::Str8ToStr16(contentController_->GetTextValue()), selectController_->GetStartIndex(),
        selectController_->GetEndIndex());

#else
    if (HasConnection()) {
        TextEditingValue value;
        value.text = contentController_->GetTextValue();
        value.hint = GetPlaceHolder();
        value.selection.Update(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        connection_->SetEditingState(value, GetInstanceId());
    }
#endif
}

// return: true if text rect offset will NOT be further changed by caret position
void TextFieldPattern::UpdateCaretRect()
{
    CHECK_NULL_VOID(!IsSelected());
    auto focusHub = GetFocusHub();
    if (focusHub && !focusHub->IsCurrentFocus()) {
        CloseSelectOverlay(true);
        LOGW("Not on focus, cannot update caret");
        return;
    }

    selectController_->UpdateCaretOffset();
}

void TextFieldPattern::AdjustTextInReasonableArea()
{
    auto contentBottomBoundary = contentRect_.GetY() + contentRect_.GetSize().Height();
    if (textRect_.Height() > contentRect_.Height()) {
        if (textRect_.GetY() + textRect_.Height() < contentBottomBoundary) {
            auto dy = contentBottomBoundary - textRect_.GetY() - textRect_.Height();
            textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        }
    } else {
        if (textRect_.GetY() != contentRect_.GetY()) {
            auto dy = contentRect_.GetY() - textRect_.GetY();
            textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        }
    }

    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width();
    if (textRect_.Width() > contentRect_.Width()) {
        if (textRect_.GetX() + textRect_.Width() < contentRightBoundary) {
            auto dx = contentRightBoundary - textRect_.GetX() - textRect_.Width();
            textRect_.SetLeft(textRect_.GetX() + dx);
        }
    }
}

bool TextFieldPattern::IsTextArea() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, true);
    return layoutProperty->HasMaxLines() ? layoutProperty->GetMaxLinesValue(1) > 1 : true;
}

void TextFieldPattern::UpdateSelectionOffset()
{
    CHECK_NULL_VOID(IsSelected());
    selectController_->CalculateHandleOffset();
}

void TextFieldPattern::CalcCaretMetricsByPosition(
    int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity)
{
    paragraph_->CalcCaretMetricsByPosition(extent, caretCaretMetric, textAffinity);
    LOGD("result stream : %{public}s , textAffinity: %{public}d", result.ToString().c_str(), textAffinity);
    caretCaretMetric.offset.AddX(textRect_.GetX());
    caretCaretMetric.offset.AddY(textRect_.GetY());
}

bool TextFieldPattern::CursorInContentRegion()
{
    if (IsTextArea()) {
        return GreatOrEqual(selectController_->GetCaretRect().GetY(), contentRect_.GetY()) &&
               LessOrEqual(selectController_->GetCaretRect().GetY() + GetTextOrPlaceHolderFontSize(),
                   contentRect_.GetY() + contentRect_.Height());
    }
    return GreatOrEqual(selectController_->GetCaretRect().GetX(), contentRect_.GetX()) &&
           LessOrEqual(selectController_->GetCaretRect().GetX() + CURSOR_WIDTH.ConvertToPx(),
               contentRect_.GetX() + contentRect_.Width());
}

float TextFieldPattern::FitCursorInSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto safeAreaBottom = pipeline->GetSafeArea().bottom_;
    safeAreaBottom = safeAreaBottom.Combine(pipeline->GetSafeAreaManager()->GetKeyboardInset());
    CHECK_NULL_RETURN(safeAreaBottom.IsValid(), 0.0f);
    // get global height of caret
    auto host = GetHost();
    auto globalBottom = host->GetPaintRectOffset().GetY() + selectController_->GetCaretRect().Bottom();
    if (globalBottom > safeAreaBottom.start) {
        auto dy = safeAreaBottom.start - globalBottom;
        textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        selectController_->UpdateCaretOffset();
        return dy;
    }
    return 0.0f;
}

bool TextFieldPattern::OffsetInContentRegion(const Offset& offset)
{
    // real content region will minus basic padding on left and right
    return GreatOrEqual(offset.GetX(), contentRect_.GetX()) &&
           LessOrEqual(offset.GetX(), contentRect_.GetX() + contentRect_.Width());
}

void TextFieldPattern::OnScrollEndCallback()
{
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->ScheduleDisappearDelayTask();
    }
    UpdateSelectMenuVisibility(true);
}

void TextFieldPattern::OnTextAreaScroll(float offset)
{
    LOGI("OnTextAreaScroll with offset %{public}f", offset);
    if (!IsTextArea() || textRect_.Height() <= contentRect_.Height()) {
        return;
    }
    if (textRect_.GetY() + offset > contentRect_.GetY()) {
        offset = contentRect_.GetY() - textRect_.GetY();
    } else if (textRect_.GetY() + textRect_.Height() + offset < contentRect_.GetY() + contentRect_.Height()) {
        offset = contentRect_.GetY() + contentRect_.Height() - textRect_.GetY() - textRect_.Height();
    }
    currentOffset_ = textRect_.GetY() + offset;
    textRect_.SetOffset(OffsetF(textRect_.GetX(), currentOffset_));
    if (SelectOverlayIsOn()) {
        selectController_->UpdateSecondHandleOffset();
        if (!IsSingleHandle()) {
            selectController_->UpdateFirstHandleOffset();
            UpdateDoubleHandlePosition();
        } else {
            UpdateSecondHandlePosition();
            auto carectOffset = selectController_->GetCaretRect().GetOffset() + OffsetF(0.0f, offset);
            selectController_->UpdateCaretOffset(carectOffset);
        }
    } else {
        auto carectOffset = selectController_->GetCaretRect().GetOffset() + OffsetF(0.0f, offset);
        selectController_->UpdateCaretOffset(carectOffset);
    }
    UpdateScrollBarOffset();
}

void TextFieldPattern::OnTextInputScroll(float offset)
{
    if (IsTextArea() || textRect_.Width() <= contentRect_.Width()) {
        return;
    }
    if (textRect_.GetX() + offset > contentRect_.GetX()) {
        offset = contentRect_.GetX() - textRect_.GetX();
    } else if (textRect_.GetX() + textRect_.Width() + offset < contentRect_.GetX() + contentRect_.Width()) {
        offset = contentRect_.GetX() + contentRect_.Width() - textRect_.GetX() - textRect_.Width();
    }
    currentOffset_ = textRect_.GetX() + offset;
    textRect_.SetOffset(OffsetF(currentOffset_, textRect_.GetY()));
    if (SelectOverlayIsOn()) {
        selectController_->UpdateSecondHandleOffset();
        if (!IsSingleHandle()) {
            selectController_->UpdateFirstHandleOffset();
            UpdateDoubleHandlePosition();
        } else {
            UpdateSecondHandlePosition();
            auto carectOffset = selectController_->GetCaretRect().GetOffset() + OffsetF(offset, 0.0f);
            selectController_->UpdateCaretOffset(carectOffset);
        }
    } else {
        auto carectOffset = selectController_->GetCaretRect().GetOffset() + OffsetF(offset, 0.0f);
        selectController_->UpdateCaretOffset(carectOffset);
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

int32_t TextFieldPattern::ConvertTouchOffsetToCaretPosition(const Offset& localOffset)
{
    CHECK_NULL_RETURN(paragraph_, 0);
    return paragraph_->GetGlyphIndexByCoordinate(localOffset);
}

int32_t TextFieldPattern::ConvertTouchOffsetToCaretPositionNG(const Offset& localOffset)
{
    CHECK_NULL_RETURN(paragraph_, 0);
    auto offset = localOffset - Offset(textRect_.GetX(), textRect_.GetY());
    return paragraph_->GetGlyphIndexByCoordinate(offset);
}

#if defined(IOS_PLATFORM)
Offset TextFieldPattern::GetGlobalOffset() const
{
    Offset offset;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto globalOffset = host->GetPaintRectOffset() - rootOffset;
    offset = Offset(globalOffset.GetX(), globalOffset.GetY());
    return offset;
}

double TextFieldPattern::GetEditingBoxY() const
{
    return GetGlobalOffset().GetY() + frameRect_.Height();
};

double TextFieldPattern::GetEditingBoxTopY() const
{
    return GetGlobalOffset().GetY();
};

bool TextFieldPattern::GetEditingBoxModel() const
{
    bool isDeclarative = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline && pipeline->GetIsDeclarative()) {
        isDeclarative = true;
    }
    return isDeclarative;
};
#endif

void TextFieldPattern::HandleFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("TextField %{public}d on focus", host->GetId());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto globalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
    needToRequestKeyboardInner_ = !(dragRecipientStatus_ == DragStatus::DRAGGING);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsNormalInlineState()) {
        ApplyInlineStates(true);
        inlineSelectAllFlag_ = true;
        inlineFocusState_ = true;
    } else {
        StartTwinkling();
    }
    NotifyOnEditChanged(true);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        auto renderContext = host->GetRenderContext();
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto radius = textFieldTheme->GetBorderRadiusSize();
        underlineColor_ = textFieldTheme->GetUnderlineTypingColor();
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
        renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
    }
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleSetSelection(int32_t start, int32_t end, bool showHandle)
{
    // todo
    LOGI("HandleSetSelection %{public}d, %{public}d", start, end);
    StopTwinkling();
    UpdateSelection(start, end);
    AdjustTextSelectionRectOffsetX();
    if (showHandle) {
        ProcessOverlay();
    } else {
        CloseSelectOverlay();
    }
    UpdateCaretInfoToController();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::AdjustTextSelectionRectOffsetX()
{
    if (textBoxes_.empty()) {
        return;
    }
    auto contentLeftBoundary = contentRect_.GetX();
    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width();
    auto selectionStart = textBoxes_.begin()->Left() + textRect_.GetX();
    auto selectionEnd = textBoxes_.begin()->Right() + textRect_.GetX();

    float dx = 0.0f;
    if (selectionEnd < contentLeftBoundary) {
        if (selectionStart < selectionEnd) {
            dx = contentLeftBoundary - selectionStart;
        } else {
            dx = contentLeftBoundary - selectionEnd;
        }
    } else if (selectionEnd > contentRightBoundary) {
        if (selectionStart < selectionEnd) {
            dx = selectionEnd - contentRightBoundary;
        } else {
            dx = selectionStart - contentRightBoundary;
        }
    }
    textRect_.SetLeft(textRect_.GetX() + dx);
}

void TextFieldPattern::HandleExtendAction(int32_t action)
{
    LOGI("HandleExtendAction %{public}d", action);
    switch (action) {
        case ACTION_SELECT_ALL: {
            HandleOnSelectAll(false);
            break;
        }
        case ACTION_CUT: {
            HandleOnCut();
            break;
        }
        case ACTION_COPY: {
            HandleOnCopy();
            break;
        }
        case ACTION_PASTE: {
            HandleOnPaste();
            break;
        }
        default: {
            break;
        }
    }
}

void TextFieldPattern::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip)
{
    LOGI("HandleSelect, current caret position %{public}d", selectController_->GetCaretIndex());
    KeyCode code = static_cast<KeyCode>(keyCode);
    switch (code) {
        case KeyCode::KEY_DPAD_LEFT: {
            HandleSelectionLeft();
            break;
        }
        case KeyCode::KEY_DPAD_RIGHT: {
            HandleSelectionRight();
            break;
        }
        case KeyCode::KEY_DPAD_UP: {
            HandleSelectionUp();
            break;
        }
        case KeyCode::KEY_DPAD_DOWN: {
            HandleSelectionDown();
            break;
        }
        default: {
            break;
        }
    }
}

void TextFieldPattern::InitFocusEvent()
{
    CHECK_NULL_VOID(!focusEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetOrCreateFocusHub();
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleFocusEvent();
        }
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);

    auto keyTask = [weak = WeakClaim(this)](const KeyEvent& keyEvent) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(keyEvent);
    };
    focusHub->SetOnKeyEventInternal(keyTask);
    focusEventInitialized_ = true;
}

void TextFieldPattern::HandleBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    LOGI("TextField %{public}d OnBlur", host->GetId());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        auto renderContext = host->GetRenderContext();
        renderContext->UpdateBorderRadius(borderRadius_);
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        underlineWidth_ = UNDERLINE_WIDTH;
    }
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (IsNormalInlineState()) {
        if (IsTextArea() && isTextInput_) {
            layoutProperty->UpdateMaxLines(1);
        }
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
    }
    needToRequestKeyboardInner_ = false;
    isFocusedBeforeClick_ = false;
    StopTwinkling();
    CloseKeyboard(true);
    selectController_->UpdateCaretIndex(selectController_->GetCaretIndex());
    NotifyOnEditChanged(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    CloseSelectOverlay(true);
    auto context = PipelineContext::GetCurrentContext();
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_RETURN(textFieldManager, false);
    auto keyEventHandler = textFieldManager->GetKeyEventHandler();
    keyEventHandler->UpdateWeakPattern(AceType::WeakClaim(this));
    return keyEventHandler->HandleKeyEvent(event);
}

void TextFieldPattern::HandleOnUndoAction()
{
    LOGI("TextFieldPattern::HandleOnUndoAction");
    if (operationRecords_.empty()) {
        LOGW("Operation records empty, cannot undo");
        return;
    }
    auto value = operationRecords_.back();
    operationRecords_.pop_back();
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH && !(redoOperationRecords_.empty())) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    redoOperationRecords_.push_back(value);
    if (operationRecords_.empty()) {
        LOGW("No record left, clear");
        FireEventHubOnChange("");
        ClearEditingValue();
        return;
    }
    auto textEditingValue = operationRecords_.back(); // record应该包含光标、select状态、文本
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->UpdateCaretIndex(textEditingValue.caretPosition);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                    : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleOnRedoAction()
{
    LOGI("TextFieldPattern::HandleOnRedoAction");
    if (redoOperationRecords_.empty()) {
        LOGW("Redo operation records empty, cannot undo");
        return;
    }
    auto textEditingValue = redoOperationRecords_.back();
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->UpdateCaretIndex(textEditingValue.caretPosition);
    redoOperationRecords_.pop_back();
    operationRecords_.push_back(textEditingValue);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                    : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleOnSelectAll(bool isKeyEvent, bool inlineStyle)
{
    LOGI("TextFieldPattern::HandleOnSelectAll");
    auto textSize = static_cast<int32_t>(contentController_->GetWideText().length());
    if (inlineStyle) {
        if (contentController_->GetWideText().rfind(L".") < textSize - FIND_TEXT_ZERO_INDEX) {
            textSize = contentController_->GetWideText().rfind(L".");
        }
        UpdateSelection(0, textSize);
    } else {
        UpdateSelection(0, textSize);
    }
    if (IsSelected()) {
        SetIsSingleHandle(false);
    }
    ResetObscureTickCountDown();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    // move text to end
    if (IsTextArea() && GreatOrEqual(textRect_.Height(), contentRect_.Height())) {
        auto offsetY = textRect_.GetY() + textRect_.Height() - contentRect_.GetY() - contentRect_.Height();
        textRect_.SetTop(textRect_.GetY() - offsetY);
    } else if (GreatOrEqual(textRect_.Width(), contentRect_.Width())) {
        auto offsetX = textRect_.GetX() + textRect_.Width() - contentRect_.GetX() - contentRect_.Width();
        textRect_.SetLeft(textRect_.GetX() - offsetX);
    }
    selectController_->MoveSecondHandleToContentRect(textSize);
    StopTwinkling();
    if (isKeyEvent || inlineSelectAllFlag_) {
        CloseSelectOverlay(true);
        return;
    }
    ProcessOverlay(true, true);
}

void TextFieldPattern::HandleOnCopy()
{
    LOGI("TextFieldPattern::HandleOnCopy");
    CHECK_NULL_VOID(clipboard_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        LOGW("Copy option not allowed");
        return;
    }
    if (!IsSelected()) {
        LOGW("Nothing to select");
        return;
    }
    if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD) {
        LOGW("Cannot copy in password mode");
        UpdateSelection(selectController_->GetEndIndex());
        StartTwinkling();
        return;
    }
    LOGI("On copy, text selector %{public}s", selectController_->ToString().c_str());
    auto value =
        contentController_->GetSelectedValue(selectController_->GetStartIndex(), selectController_->GetEndIndex());
    if (value.empty()) {
        LOGW("Copy value is empty");
        return;
    }
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        LOGI("Copy value is %{private}s", value.c_str());
        clipboard_->SetData(value, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
    }

    selectController_->UpdateCaretIndex(selectController_->GetSecondHandleIndex());
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(value);
}

void TextFieldPattern::HandleOnPaste()
{
    LOGI("TextFieldPattern::HandleOnPaste");
    auto pasteCallback = [weak = WeakClaim(this)](const std::string& data) {
        if (data.empty()) {
            LOGW("Paste value is empty");
            return;
        }
        auto textfield = weak.Upgrade();
        CHECK_NULL_VOID(textfield);
        auto tmpHost = textfield->GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);

        auto start = textfield->selectController_->GetStartIndex();
        auto end = textfield->selectController_->GetEndIndex();

        std::wstring pasteData = StringUtils::ToWstring(data);
        textfield->StripNextLine(pasteData);
        textfield->contentController_->ReplaceSelectedValue(start, end, StringUtils::ToString(pasteData));
        auto newCaretPosition = std::clamp(std::min(start, end) + static_cast<int32_t>(pasteData.length()), 0,
            static_cast<int32_t>(textfield->contentController_->GetWideText().length()));
        textfield->ResetObscureTickCountDown();
        textfield->selectController_->UpdateCaretIndex(newCaretPosition);
        textfield->UpdateEditingValueToRecord();
        if (textfield->IsTextArea() && layoutProperty->HasMaxLength()) {
            textfield->HandleCounterBorder();
        }
        textfield->CloseSelectOverlay(true);
        auto host = textfield->GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = textfield->GetHost()->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnPaste(StringUtils::ToString(pasteData));
        host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                     : PROPERTY_UPDATE_MEASURE);
        textfield->StartTwinkling();
    };
    CHECK_NULL_VOID(clipboard_);
    clipboard_->GetData(pasteCallback);
}

void TextFieldPattern::StripNextLine(std::wstring& data)
{
    CHECK_NULL_VOID(!(data.empty() || IsTextArea()));
    std::wstring result;
    bool dataChanged = false;
    int32_t dataPtr = 0;
    while (dataPtr < static_cast<int32_t>(data.length())) {
        if (data[dataPtr] != WIDE_NEWLINE[0]) {
            result += data[dataPtr];
        } else {
            dataChanged = true;
        }
        dataPtr++;
    }
    CHECK_NULL_VOID(dataChanged);
    data = result;
}

void TextFieldPattern::HandleOnCut()
{
    LOGI("TextFieldPattern::HandleOnCut");
#if !defined(PREVIEW)
    CHECK_NULL_VOID(clipboard_);
#endif
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        LOGW("Copy option not allowed");
        return;
    }
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    SwapIfLarger(start, end);
    if (!IsSelected()) {
        LOGW("HandleOnCut nothing Selected");
        return;
    }
    auto selectedText = contentController_->GetSelectedValue(start, end);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        LOGI("Cut value is %{private}s", selectedText.c_str());
        clipboard_->SetData(selectedText, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
    }
    contentController_->erase(start, end - start);
    UpdateSelection(start);
    CloseSelectOverlay(true);
    StartTwinkling();
    UpdateEditingValueToRecord();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCut(selectedText);
    FireEventHubOnChange(contentController_->GetTextValue());
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::UpdateSelection(int32_t both)
{
    UpdateSelection(both, both);
}

void TextFieldPattern::UpdateSelection(int32_t start, int32_t end)
{
    auto startIndex = std::min(start, end);
    auto endIndex = std::max(start, end);
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(contentController_->GetWideText().length()));
    endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(contentController_->GetWideText().length()));
    if (startIndex != selectController_->GetStartIndex() || endIndex != selectController_->GetEndIndex()) {
        FireOnSelectionChange(startIndex, endIndex);
        selectController_->UpdateHandleIndex(startIndex, endIndex);
    }
}

void TextFieldPattern::FireOnSelectionChange(int32_t start, int32_t end)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnSelectionChange(start, end);
}

void TextFieldPattern::FireEventHubOnChange(const std::string& text)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetNeedFireOnChangeValue(false)) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        underlineColor_ = textFieldTheme->GetUnderlineTypingColor();
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
    }
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(text);
}

void TextFieldPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (SelectOverlayIsOn()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(info.GetTouches().front().GetLocalLocation());
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    }
}

void TextFieldPattern::HandleTouchDown(const Offset& offset)
{
    LOGI("HandleTouchDown");
    if (HasStateStyle(UI_STATE_PRESSED)) {
        return;
    }
    if (enableTouchAndHoverEffect_ && !isMousePressed_) {
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto renderContext = tmpHost->GetRenderContext();
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(textFieldTheme);
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
            auto radius = textFieldTheme->GetBorderRadiusSize();
            renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
        }
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::HandleTouchUp()
{
    LOGI("HandleTouchUp");
    if (isMousePressed_) {
        LOGI("TextFieldPattern::HandleTouchUp of mouse");
        isMousePressed_ = false;
    }
    if (enableTouchAndHoverEffect_ && !HasStateStyle(UI_STATE_PRESSED)) {
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto renderContext = tmpHost->GetRenderContext();
        if (!isOnHover_) {
            auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
                renderContext->UpdateBorderRadius(borderRadius_);
            }
            if (layoutProperty->GetShowUnderlineValue(false) && HasFocus() && IsUnspecifiedOrTextType()) {
                auto pipeline = PipelineBase::GetCurrentContext();
                CHECK_NULL_VOID(pipeline);
                auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
                CHECK_NULL_VOID(textFieldTheme);
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
        }
    }
}

#ifdef ENABLE_DRAG_FRAMEWORK
void TextFieldPattern::InitDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::VISIBLE_PASSWORD &&
        layoutProperty->GetCopyOptionsValue(CopyOptions::Local) != CopyOptions::None) {
        InitDragDropEvent();
        AddDragFrameNodeToManager(host);
    } else {
        ClearDragDropEvent();
        RemoveDragFrameNodeFromManager(host);
    }
}

std::function<void(Offset)> TextFieldPattern::GetThumbnailCallback()
{
    auto callback = [weak = WeakClaim(this)](const Offset& point) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        if (pattern->BetweenSelectedPosition(point)) {
            pattern->dragNode_ = TextDragPattern::CreateDragNode(frameNode);
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetPixelMap(nullptr);
    };
    return callback;
}

std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> TextFieldPattern::OnDragStart()
{
    auto onDragStart = [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                           const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo itemInfo;
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, itemInfo);
        auto host = pattern->GetHost();
        CHECK_NULL_RETURN(host, itemInfo);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, itemInfo);
        pattern->dragStatus_ = DragStatus::DRAGGING;
        pattern->textFieldContentModifier_->ChangeDragStatus();
        auto contentController = pattern->contentController_;
        auto selectController = pattern->selectController_;
        pattern->dragTextStart_ = selectController->GetStartIndex();
        pattern->dragTextEnd_ = selectController->GetEndIndex();
        std::string beforeStr = contentController->GetValueBeforeIndex(selectController->GetStartIndex());
        std::string selectedStr =
            contentController->GetSelectedValue(selectController->GetStartIndex(), selectController->GetEndIndex());
        std::string afterStr = contentController->GetValueAfterIndex(selectController->GetEndIndex());
        pattern->dragContents_ = { beforeStr, selectedStr, afterStr };
        itemInfo.extraInfo = selectedStr;
        RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
        event->SetData(unifiedData);
        host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                     : PROPERTY_UPDATE_MEASURE);
        return itemInfo;
    };
    return onDragStart;
}

std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> TextFieldPattern::OnDragDrop()
{
    auto onDrop = [weakPtr = WeakClaim(this)](
                      const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        if (extraParams.empty()) {
            pattern->dragStatus_ = DragStatus::ON_DROP;
            pattern->textFieldContentModifier_->ChangeDragStatus();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                         : PROPERTY_UPDATE_MEASURE);
            return;
        }
        auto data = event->GetData();
        CHECK_NULL_VOID(data);
        auto records = UdmfClient::GetInstance()->GetPlainTextRecords(data);
        std::string str;
        for (const auto& record : records) {
            str += record;
        }
        pattern->needToRequestKeyboardInner_ = true;
        pattern->dragRecipientStatus_ = DragStatus::NONE;
        if (str.empty()) {
            return;
        }
        if (pattern->dragStatus_ == DragStatus::NONE) {
            pattern->InsertValue(str);
        } else {
            auto current = pattern->selectController_->GetCaretIndex();
            auto dragTextStart = pattern->dragTextStart_;
            auto dragTextEnd = pattern->dragTextEnd_;
            if (current < dragTextStart) {
                pattern->contentController_->erase(dragTextStart, dragTextEnd - dragTextStart);
                pattern->InsertValue(str);
            } else if (current > dragTextEnd) {
                pattern->contentController_->erase(dragTextStart, dragTextEnd - dragTextStart);
                pattern->selectController_->UpdateCaretIndex(current - (dragTextEnd - dragTextStart));
                pattern->InsertValue(str);
            }
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
            host->MarkDirtyNode(pattern->IsTextArea() ? PROPERTY_UPDATE_MEASURE : PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    return onDrop;
}

void TextFieldPattern::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    gestureHub->SetTextDraggable(true);
    auto callback = GetThumbnailCallback();
    gestureHub->SetThumbnailCallback(std::move(callback));
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnDragStart()) {
        eventHub->SetOnDragStart(OnDragStart());
    }

    auto onDragEnter = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->dragStatus_ == DragStatus::ON_DROP) {
            pattern->dragStatus_ = DragStatus::NONE;
        }

        pattern->dragRecipientStatus_ = DragStatus::DRAGGING;
    };
    eventHub->SetOnDragEnter(std::move(onDragEnter));

    auto onDragMove = [weakPtr = WeakClaim(this)](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchX = event->GetX();
        auto touchY = event->GetY();
        Offset offset = Offset(touchX, touchY) - Offset(pattern->textRect_.GetX(), pattern->textRect_.GetY()) -
                        Offset(pattern->parentGlobalOffset_.GetX(), pattern->parentGlobalOffset_.GetY());
        auto position = pattern->ConvertTouchOffsetToCaretPosition(offset);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto focusHub = pattern->GetFocusHub();
        focusHub->RequestFocusImmediately();
        pattern->SetCaretPosition(position);
        pattern->StartTwinkling();
    };
    eventHub->SetOnDragMove(std::move(onDragMove));

    auto onDragLeave = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StopTwinkling();
        pattern->dragRecipientStatus_ = DragStatus::NONE;
    };
    eventHub->SetOnDragLeave(std::move(onDragLeave));

    auto onDragEnd = [weakPtr = WeakClaim(this), id = Container::CurrentId()](
                         const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(id);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        LOGD("TextFieldPattern  onDragEnd result: %{public}d dragStatus: %{public}d", event->GetResult(),
            pattern->dragStatus_);
        if (pattern->dragStatus_ == DragStatus::DRAGGING) {
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    eventHub->SetOnDragEnd(std::move(onDragEnd));

    eventHub->SetOnDrop(OnDragDrop());
}

void TextFieldPattern::ClearDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetTextDraggable(false);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(nullptr);
    eventHub->SetOnDragEnter(nullptr);
    eventHub->SetOnDragMove(nullptr);
    eventHub->SetOnDragLeave(nullptr);
    eventHub->SetOnDragEnd(nullptr);
    eventHub->SetOnDrop(nullptr);
}
#endif

void TextFieldPattern::InitTouchEvent()
{
    CHECK_NULL_VOID(!touchListener_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isUsingMouse_ = info.GetSourceDevice() == SourceType::MOUSE;
        pattern->HandleTouchEvent(info);
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchListener_);
}

void TextFieldPattern::InitClickEvent()
{
    CHECK_NULL_VOID(!clickListener_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto gesture = tmpHost->GetOrCreateGestureEventHub();
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void TextFieldPattern::HandleClickEvent(GestureEvent& info)
{
    TimeStamp clickTimeStamp = info.GetTimeStamp();
    std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout = clickTimeStamp - lastClickTimeStamp_;
    lastClickTimeStamp_ = info.GetTimeStamp();
    isUsingMouse_ = info.GetSourceDevice() == SourceType::MOUSE;
    if (timeout.count() < DOUBLECLICK_INTERVAL_MS) {
        HandleDoubleClickEvent(info); // 注册手势事件
    } else {
        HandleSingleClickEvent(info);
    }
    if (ResetObscureTickCountDown()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void TextFieldPattern::HandleSingleClickEvent(GestureEvent& info)
{
    // emulate clicking bottom of the textField
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = GetFocusHub();

    if (!focusHub->IsFocusable()) {
        LOGI("Textfield %{public}d is not focusable ,cannot request keyboard", host->GetId());
        return;
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    auto hasFocus = HasFocus();
    if (!hasFocus) {
        if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
            LOGW("Request focus failed, cannot open input method");
            CloseSelectOverlay(true);
            StopTwinkling();
            return;
        }
    }
    auto lastCaretIndex = selectController_->GetCaretIndex();
    selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation());
    StartTwinkling();
    SetIsSingleHandle(true);
    if (lastCaretIndex == selectController_->GetCaretIndex() && hasFocus && caretStatus_ == CaretStatus::SHOW &&
        info.GetSourceDevice() != SourceType::MOUSE) {
        ProcessOverlay(true, true);
    } else {
        CloseSelectOverlay(true);
    }
    if (RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleDoubleClickEvent(GestureEvent& info)
{
    selectController_->UpdateSelectByOffset(info.GetLocalLocation());
    if (IsSelected()) {
        StopTwinkling();
        SetIsSingleHandle(false);
    }
    if (info.GetSourceDevice() != SourceType::MOUSE) {
        ProcessOverlay(true, true);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::ScheduleCursorTwinkling()
{
    if (isTransparent_) {
        return;
    }
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        LOGW("context has no task executor.");
        return;
    }

    auto weak = WeakClaim(this);
    cursorTwinklingTask_.Reset([weak] {
        auto client = weak.Upgrade();
        CHECK_NULL_VOID(client);
        client->OnCursorTwinkling();
    });
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(cursorTwinklingTask_, TaskExecutor::TaskType::UI, twinklingInterval_);
}

void TextFieldPattern::StartTwinkling()
{
    if (isTransparent_) {
        return;
    }
    // Ignore the result because all ops are called on this same thread (ACE UI).
    // The only reason failed is that the task has finished.
    cursorTwinklingTask_.Cancel();

    // Show cursor right now.
    cursorVisible_ = true;
    caretStatus_ = CaretStatus::SHOW;
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCursorTwinkling();
}

void TextFieldPattern::OnCursorTwinkling()
{
    cursorTwinklingTask_.Cancel();
    cursorVisible_ = !cursorVisible_;
    auto shouldMeasure = !IsTextArea() && IsInPasswordMode() && GetTextObscured() && obscureTickCountDown_ == 1;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (shouldMeasure) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    ScheduleCursorTwinkling();
}

void TextFieldPattern::StopTwinkling()
{
    cursorTwinklingTask_.Cancel();

    // Repaint only if cursor is visible for now.
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    if (cursorVisible_) {
        cursorVisible_ = false;
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    if (ResetObscureTickCountDown()) {
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    caretStatus_ = CaretStatus::HIDE;
}

void TextFieldPattern::CheckIfNeedToResetKeyboard()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    bool needToResetKeyboard = false;
    // check unspecified  for first time entrance
    if (keyboard_ != layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        LOGI("Keyboard type changed to %{public}d", layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
        keyboard_ = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
        needToResetKeyboard = true;
    }
    if (!needToResetKeyboard && action_ != TextInputAction::UNSPECIFIED) {
        needToResetKeyboard = action_ != GetTextInputActionValue(TextInputAction::DONE);
    }
    action_ = GetTextInputActionValue(TextInputAction::DONE);
    LOGI("Keyboard action is %{public}d", action_);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    // if keyboard attached and keyboard is shown, pull up keyboard again
    if (needToResetKeyboard && imeAttached_ && imeShown_) {
        CloseKeyboard(true);
        RequestKeyboard(false, true, true);
    }
#else
    if (needToResetKeyboard && HasConnection()) {
        CloseKeyboard(true);
        RequestKeyboard(false, true, true);
    }
#endif
}

void TextFieldPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    instanceId_ = context->GetInstanceId();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE && !IsNormalInlineState()) {
        layoutProperty->UpdateTextInputType(TextInputType::TEXT);
    }
    CheckIfNeedToResetKeyboard();
    if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        underlineWidth_ = UNDERLINE_WIDTH;
        underlineColor_ =
            IsDisabled() ? textFieldTheme->GetDisableUnderlineColor() : textFieldTheme->GetUnderlineColor();
        SaveUnderlineStates();
    }
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    isTransparent_ = renderContext->GetOpacityValue(1.0f) == 0.0f;
    if (!preErrorState_ && !restoreMarginState_) {
        SavePasswordModeStates();
    }
    InitClickEvent();
    InitLongPressEvent();
    InitFocusEvent();
    InitMouseEvent();
    InitTouchEvent();
    SetAccessibilityAction();
    FilterInitializeText();
    InitSelectOverlay();
    if (responseArea_) {
        responseArea_->InitResponseArea(WeakClaim(this));
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::VISIBLE_PASSWORD) {
        InitDragDropEvent();
        AddDragFrameNodeToManager(host);
    } else {
        ClearDragDropEvent();
        RemoveDragFrameNodeFromManager(host);
    }
#endif // ENABLE_DRAG_FRAMEWORK
    context->AddOnAreaChangeNode(host->GetId());
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    if (barState_.has_value() && barState_.value() != layoutProperty->GetDisplayModeValue(DisplayMode::AUTO) &&
        HasFocus() && IsNormalInlineState()) {
        lastTextRectY_ = textRect_.GetY();
    }
    ProcessInnerPadding();
    // The textRect position can't be changed by only redraw.
    if (CheckNeedMeasure(layoutProperty->GetPropertyChangeFlag())) {
        textRect_.SetLeft(GetPaddingLeft() + GetBorderLeft());
        textRect_.SetTop(GetPaddingTop() + GetBorderTop());
    }
    CalculateDefaultCursor();
    if (renderContext->HasBackgroundColor()) {
        paintProperty->UpdateBackgroundColor(renderContext->GetBackgroundColorValue());
    }

    auto textWidth = static_cast<int32_t>(contentController_->GetWideText().length());
    if (SelectOverlayIsOn()) {
        needToRefreshSelectOverlay_ = true;
        UpdateSelection(std::clamp(selectController_->GetStartIndex(), 0, textWidth),
            std::clamp(selectController_->GetEndIndex(), 0, textWidth));
        UpdateCaretPositionWithClamp(selectController_->GetEndIndex());
        if (IsSelected()) {
            selectionMode_ = SelectionMode::SELECT;
        }
    }
    if (layoutProperty->GetTypeChangedValue(false)) {
        layoutProperty->ResetTypeChanged();
        operationRecords_.clear();
        redoOperationRecords_.clear();
    }
    if (IsTextArea() || IsNormalInlineState()) {
        SetAxis(Axis::VERTICAL);
        if (!GetScrollableEvent()) {
            AddScrollEvent();
        }
        auto barState = layoutProperty->GetDisplayModeValue(DisplayMode::AUTO);
        if (!barState_.has_value()) {
            barState_ = barState;
        }
        scrollBarVisible_ = true;
        if (barState == DisplayMode::OFF) {
            scrollBarVisible_ = false;
        }
        SetScrollBar(barState == DisplayMode::OFF ? DisplayMode::ON : barState);
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->SetMinHeight(SCROLL_BAR_MIN_HEIGHT);
            scrollBar->SetStartReservedHeight(0.0_px);
            scrollBar->SetEndReservedHeight(0.0_px);
        }
        if (textFieldOverlayModifier_) {
            textFieldOverlayModifier_->SetScrollBar(scrollBar);
            UpdateScrollBarOffset();
        }
    } else {
        SetAxis(Axis::HORIZONTAL);
        SetScrollBar(DisplayMode::OFF);
        if (!GetScrollableEvent()) {
            AddScrollEvent();
            SetScrollEnable(false);
        }
    }
    if (!IsNormalInlineState() && !IsDisabled()) {
        SetShowError();
    }
    if (IsTextArea()) {
        if (setBorderFlag_ && layoutProperty->HasMaxLength()) {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto themeManager = pipeline->GetThemeManager();
            CHECK_NULL_VOID(themeManager);
            auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
            lastDiffBorderColor_.SetColor(textFieldTheme->GetOverCountBorderColor());
            lastDiffBorderWidth_.SetBorderWidth(OVER_COUNT_BORDER_WIDTH);
            setBorderFlag_ = false;
        }
        HandleCounterBorder();
    }
    if (!IsTextArea()) {
        isTextInput_ = true;
    }
    auto inputStyle = paintProperty->GetInputStyleValue(InputStyle::DEFAULT);
    if (!inlineState_.saveInlineState) {
        inlineState_.saveInlineState = false;
        SaveInlineStates();
    }
    if (!HasFocus() && inlineState_.saveInlineState) {
        SaveInlineStates();
    }
    if (HasFocus() && IsNormalInlineState()) {
        selectionMode_ = SelectionMode::NONE;
        preInputStyle_ == InputStyle::DEFAULT ? ApplyInlineStates(true) : ApplyInlineStates(false);
    }
    if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        ApplyUnderlineStates();
    }
    if (preInputStyle_ == InputStyle::INLINE && inputStyle == InputStyle::DEFAULT &&
        (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED ||
            layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::TEXT)) {
        if (IsTextArea() && isTextInput_) {
            layoutProperty->UpdateMaxLines(1);
        }
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
    }
    preInputStyle_ = inputStyle;
}

void TextFieldPattern::CalculateDefaultCursor()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    float caretWidth = paintProperty->GetCursorWidth().has_value()
                           ? static_cast<float>(paintProperty->GetCursorWidthValue().ConvertToPx())
                           : static_cast<float>(CURSOR_WIDTH.ConvertToPx());
    selectController_->UpdateCaretWidth(caretWidth);
    if (!contentController_->IsEmpty()) {
        return;
    }
    selectController_->UpdateCaretHeight(PreferredLineHeight());
}

void TextFieldPattern::FireOnTextChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto textCache = layoutProperty->GetValueValue("");
    if (textCache != contentController_->GetTextValue()) {
        layoutProperty->UpdateValue(contentController_->GetTextValue());
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, contentController_->GetTextValue());
        eventHub->FireOnChange(contentController_->GetTextValue());
    }
}

void TextFieldPattern::FilterInitializeText()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto inputFilter = layoutProperty->GetInputFilter();
    auto inputType = layoutProperty->GetTextInputType();
    if ((inputFilter.has_value() || inputType.has_value()) && !contentController_->IsEmpty()) {
        contentController_->FilterValue();
    }
}

bool TextFieldPattern::IsDisabled()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, true);
    auto eventHub = tmpHost->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, true);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, true);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, true);
    if (!eventHub->IsEnabled()) {
        layoutProperty->UpdateTextColor(theme->GetDisableTextColor());
    }
    return !eventHub->IsEnabled();
}

void TextFieldPattern::ProcessInnerPadding()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto themePadding = textFieldTheme->GetPadding();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    auto& paddingProperty = layoutProperty->GetPaddingProperty();
    auto left = !paddingProperty
                    ? CalcLength(themePadding.Left()).GetDimension().ConvertToPx()
                    : paddingProperty->left.value_or(CalcLength(themePadding.Left())).GetDimension().ConvertToPx();
    utilPadding_.left = left;
    auto top = !paddingProperty
                   ? CalcLength(themePadding.Top()).GetDimension().ConvertToPx()
                   : paddingProperty->top.value_or(CalcLength(themePadding.Top())).GetDimension().ConvertToPx();
    utilPadding_.top = top;
            : paddingProperty->right.value_or(CalcLength(themePadding.Right())).GetDimension().ConvertToPx();
    lastBorderWidth_ = currentBorderWidth;
}

void TextFieldPattern::InitLongPressEvent()
{
    CHECK_NULL_VOID(!longPressEvent_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto gesture = tmpHost->GetOrCreateGestureEventHub();
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isUsingMouse_ = info.GetSourceDevice() == SourceType::MOUSE;
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gesture->SetLongPressEvent(longPressEvent_);
}

void TextFieldPattern::HandleLongPress(GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (ResetObscureTickCountDown()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (info.GetSourceDevice() == SourceType::MOUSE) {
        return;
    }
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (BetweenSelectedPosition(info.GetGlobalLocation())) {
#ifdef ENABLE_DRAG_FRAMEWORK
        gestureHub->SetIsTextDraggable(true);
#endif
        return;
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    gestureHub->SetIsTextDraggable(false);
#endif
    auto focusHub = GetFocusHub();

    if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
        return;
    }
    selectController_->UpdateSelectByOffset(info.GetLocalLocation());
    if (IsSelected()) {
        StopTwinkling();
    }
    SetIsSingleHandle(!IsSelected());
    ProcessOverlay(true, true);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::UpdateCaretPositionWithClamp(const int32_t& pos)
{
    selectController_->UpdateCaretIndex(
        std::clamp(pos, 0, static_cast<int32_t>(contentController_->GetWideText().length())));
}

void TextFieldPattern::ProcessOverlay(bool isUpdateMenu, bool animation, bool isShowMenu)
{
    selectController_->CalculateHandleOffset();
    ShowSelectOverlayParams showOverlayParams = {
        .animation = animation, .isShowMenu = isShowMenu, .isUpdateMenu = isUpdateMenu
    };
    if (isSingleHandle_) {
        StartTwinkling();
        LOGD("Show single handle Handle info %{public}s", selectController_->GetCaretRect().ToString().c_str());
        showOverlayParams.firstHandle = std::nullopt;
        showOverlayParams.secondHandle = selectController_->GetCaretRect();
        ShowSelectOverlay(showOverlayParams);
    } else {
        LOGD("Show handles firstHandle info %{public}s, secondHandle Info %{public}s",
            selectController_->GetFirstHandleRect().ToString().c_str(),
            selectController_->GetSecondHandleRect().ToString().c_str());
        showOverlayParams.firstHandle = selectController_->GetFirstHandleRect();
        showOverlayParams.secondHandle = selectController_->GetSecondHandleRect();
        ShowSelectOverlay(showOverlayParams);
    }
}

void TextFieldPattern::ShowSelectOverlay(const ShowSelectOverlayParams& showOverlayParams)
{
    if (isTransparent_) {
        return;
    }
    auto hasDataCallback = [weak = WeakClaim(this), params = showOverlayParams](bool hasData) {
        LOGI("HasData callback from clipboard, data available ? %{public}d", hasData);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StartRequestSelectOverlay(params, hasData);
    };
    if (showOverlayParams.isUpdateMenu) {
        clipboard_->HasData(hasDataCallback);
    } else {
        StartRequestSelectOverlay(showOverlayParams);
    }
}

void TextFieldPattern::StartRequestSelectOverlay(const ShowSelectOverlayParams& params, bool isShowPaste)
{
    ClientOverlayInfo overlayInfo = {
        .animation = params.animation, .isMenuShow = params.isShowMenu, .isUpdateMenu = params.isUpdateMenu
    };
    if (params.firstHandle.has_value()) {
        auto handle = params.firstHandle.value();
        handle.SetOffset(handle.GetOffset() + GetTextPaintOffset());
        SelectHandleInfo firstHandleInfo;
        firstHandleInfo.paintRect = handle;
        overlayInfo.firstHandleInfo = firstHandleInfo;
    }
    if (params.secondHandle.has_value()) {
        auto handle = params.secondHandle.value();
        handle.SetOffset(handle.GetOffset() + GetTextPaintOffset());
        SelectHandleInfo secondHandleInfo;
        secondHandleInfo.paintRect = handle;
        overlayInfo.secondHandleInfo = secondHandleInfo;
    }
    overlayInfo.isShowPaste = isShowPaste;
    overlayInfo.isMenuShow = params.isShowMenu;
    overlayInfo.isShowMouseMenu = IsUsingMouse();
    RequestOpenSelectOverlay(overlayInfo);
    auto start = GetTextSelectController()->GetStartIndex();
    auto end = GetTextSelectController()->GetEndIndex();
    UpdateSelectInfo(contentController_->GetSelectedValue(start, end));
}

bool TextFieldPattern::OnPreShowSelectOverlay(
    SelectOverlayInfo& overlayInfo, const ClientOverlayInfo& clientInfo, bool isSelectOverlayOn)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    bool isHideSelectionMenu = layoutProperty->GetSelectionMenuHiddenValue(false);
    // right click menu
    if (IsUsingMouse()) {
        if (isHideSelectionMenu && !isSelectOverlayOn) {
            return false;
        }
        overlayInfo.rightClickOffset = GetRightClickOffset();
        overlayInfo.isUsingMouse = true;
    } else {
        if (overlayInfo.isSingleHandle && IsTextArea() && GetSelectMode() == SelectionMode::SELECT_ALL) {
            auto contentRect = GetContentRect();
            auto parentGlobalOffset = GetParentGlobalOffset();
            overlayInfo.menuInfo.menuOffset =
                OffsetF(contentRect.GetOffset().GetX() + contentRect.Width() / 2.0 + parentGlobalOffset.GetX(),
                    contentRect.GetOffset().GetY() + parentGlobalOffset.GetY());
        }
        overlayInfo.singleLineHeight = PreferredLineHeight();
    }
    auto hasTextContent = !contentController_->IsEmpty();
    overlayInfo.menuInfo.showCopy = hasTextContent && AllowCopy() && IsSelected();
    overlayInfo.menuInfo.showCut = overlayInfo.menuInfo.showCopy;
    overlayInfo.menuInfo.showCopyAll = hasTextContent && !IsSelectAll();
    auto hasData = clientInfo.isShowPaste;
    overlayInfo.menuInfo.showPaste = hasData;
    overlayInfo.menuInfo.menuIsShow = (hasTextContent || hasData) && !isHideSelectionMenu && clientInfo.isMenuShow;
    overlayInfo.isHandleLineShow = overlayInfo.isHandleLineShow && !IsSingleHandle();
    overlayInfo.menuInfo.menuDisable = isHideSelectionMenu;
    auto gesture = host->GetOrCreateGestureEventHub();
    gesture->RemoveTouchEvent(GetTouchListener());
    return true;
}

// 建议将函数名换成和overlay相关，此函数会和select中的handle产生歧义
void TextFieldPattern::UpdateFirstHandlePosition(bool needLayout)
{
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetFirstHandleOffset());
    handleInfo.needLayout = needLayout;
    proxy->UpdateFirstSelectHandleInfo(handleInfo);
}

void TextFieldPattern::UpdateSecondHandlePosition(bool needLayout)
{
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
    proxy->UpdateSecondSelectHandleInfo(handleInfo);
}

// 基于最新的代码整改
void TextFieldPattern::UpdateDoubleHandlePosition(bool firstNeedLayout, bool secondNeedLayout)
{
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    SelectHandleInfo firstHandleInfo = GetSelectHandleInfo(selectController_->GetFirstHandleOffset());
    firstHandleInfo.needLayout = firstNeedLayout;

    SelectHandleInfo secondHandleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
    secondHandleInfo.needLayout = secondNeedLayout;
    proxy->UpdateFirstAndSecondHandleInfo(firstHandleInfo, secondHandleInfo);

    auto selectionVisible = !firstHandleInfo.isShow && !secondHandleInfo.isShow && CheckSelectionRectVisible();
    proxy->SetSelectRegionVisible(selectionVisible);
}

SelectHandleInfo TextFieldPattern::GetSelectHandleInfo(OffsetF offset)
{
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(),
        selectController_->GetCaretRect().Height() };
    // 要将相对textRect的坐标转换为全局坐标
    auto paintRect = RectF(offset.GetX() + GetTextPaintOffset().GetX(), offset.GetY() + GetTextPaintOffset().GetY(),
        handlePaintSize.Width(), handlePaintSize.Height());
    return { .isShow = CheckHandleVisible(paintRect), .paintRect = paintRect };
}

bool TextFieldPattern::AllowCopy()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None &&
           layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::VISIBLE_PASSWORD;
}

void TextFieldPattern::OnDetachFromFrameNode(FrameNode* node)
{
    CloseSelectOverlay();
    ResetSelectOverlayClient();
    if (responseArea_) {
        responseArea_->DestoryArea();
        responseArea_.Reset();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        LOGD("Unregister surface change callback with id %{public}d", surfaceChangedCallbackId_.value_or(-1));
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    if (HasSurfacePositionChangedCallback()) {
        LOGD("Unregister surface position change callback with id %{public}d",
            surfacePositionChangedCallbackId_.value_or(-1));
        pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionChangedCallbackId_.value_or(-1));
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->UnRegisterCallbackNG(frameNode);
        fontManager->RemoveVariationNodeNG(frameNode);
    }
}

void TextFieldPattern::CloseSelectOverlay()
{
    CloseSelectOverlay(false);
}

void TextFieldPattern::CloseSelectOverlay(bool animation)
{
    RequestCloseSelectOverlay(animation);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    gesture->AddTouchEvent(GetTouchListener());
}

void TextFieldPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle)
{
    CHECK_NULL_VOID(SelectOverlayIsOn());
    CHECK_NULL_VOID(!contentController_->IsEmpty());
    auto localOffset = handleRect.GetOffset() - parentGlobalOffset_;
    if (isSingleHandle_) {
        selectController_->UpdateCaretInfoByOffset(Offset(localOffset.GetX(), localOffset.GetY()));
    } else {
        auto position = UpdateCaretPositionOnHandleMove(localOffset);
        if (isFirstHandle) {
            selectController_->MoveFirstHandleToContentRect(position);
            auto proxy = GetSelectOverlayProxy();
            CHECK_NULL_VOID(proxy);
            SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
            proxy->UpdateSecondSelectHandleInfo(handleInfo);
        } else {
            selectController_->MoveSecondHandleToContentRect(position);
            auto proxy = GetSelectOverlayProxy();
            CHECK_NULL_VOID(proxy);
            SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetFirstHandleOffset());
            proxy->UpdateFirstSelectHandleInfo(handleInfo);
        }
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

int32_t TextFieldPattern::UpdateCaretPositionOnHandleMove(const OffsetF& localOffset)
{
    int32_t position = 0;
    if (!IsTextArea()) {
        if (LessNotEqual(localOffset.GetX(), contentRect_.GetX())) {
            position = std::max(static_cast<int32_t>(selectController_->GetStartIndex() -
                                                     GetGraphemeClusterLength(contentController_->GetWideText(),
                                                         selectController_->GetStartIndex(), true)),
                0);
        } else if (GreatOrEqual(localOffset.GetX(), contentRect_.GetX() + contentRect_.Width())) {
            position = std::min(static_cast<int32_t>(selectController_->GetEndIndex() +
                                                     GetGraphemeClusterLength(contentController_->GetWideText(),
                                                         selectController_->GetEndIndex())),
                static_cast<int32_t>(contentController_->GetWideText().length()));
        } else {
            Offset offset(localOffset.GetX() - textRect_.GetX(), 0.0f);
            position = ConvertTouchOffsetToCaretPosition(offset);
        }
        return position;
    }
    if (LessNotEqual(localOffset.GetY(), contentRect_.GetY())) {
        position = ConvertTouchOffsetToCaretPosition(Offset(
            localOffset.GetX() - GetPaddingLeft(), localOffset.GetY() - textRect_.GetY() - PreferredLineHeight()));
    } else if (GreatOrEqual(localOffset.GetY(), contentRect_.GetY() + contentRect_.Height())) {
        position = ConvertTouchOffsetToCaretPosition(Offset(
            localOffset.GetX() - GetPaddingLeft(), localOffset.GetY() - textRect_.GetY() + PreferredLineHeight()));
    } else {
        position = ConvertTouchOffsetToCaretPosition(
            Offset(localOffset.GetX() - GetPaddingLeft(), localOffset.GetY() - textRect_.GetY()));
    }
    return position;
}

void TextFieldPattern::UpdateCopyAllStatus()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetSelectionMenuHiddenValue(false)) {
        UpdateSelectMenuInfo([weak = WeakClaim(this)](SelectMenuInfo& menuInfo) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            menuInfo.showCopyAll = !pattern->IsSelectAll();
        });
    }
}

void TextFieldPattern::OnHandleMoveDone(const RectF& /* handleRect */, bool isFirstHandle)
{
    UpdateCopyAllStatus();
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    if (!isSingleHandle_) {
        if (selectController_->GetFirstHandleIndex() == selectController_->GetSecondHandleIndex()) {
            CloseSelectOverlay(true);
            StartTwinkling();
        } else {
            auto handleInfo = GetSelectHandleInfo(selectController_->GetFirstHandleOffset());
            proxy->UpdateFirstSelectHandleInfo(handleInfo);
            handleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
            proxy->UpdateSecondSelectHandleInfo(handleInfo);
        }
        selectController_->UpdateCaretOffset();
    } else {
        auto handleInfo = GetSelectHandleInfo(selectController_->GetCaretRect().GetOffset());
        proxy->UpdateSecondSelectHandleInfo(handleInfo);
    }

    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::OnHandleClosed(bool closedByGlobalEvent)
{
    SelectOverlayClient::OnHandleClosed(closedByGlobalEvent);
    if (closedByGlobalEvent) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        selectController_->UpdateCaretIndex(selectController_->GetSecondHandleIndex());
        StartTwinkling();
    }
}

void TextFieldPattern::InitEditingValueText(std::string content)
{
    contentController_->SetTextValue(std::move(content));
    selectController_->UpdateCaretIndex(static_cast<int32_t>(StringUtils::ToWstring(content).length()));
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::InitMouseEvent()
{
    CHECK_NULL_VOID(!mouseEvent_ || !hoverEvent_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto eventHub = tmpHost->GetEventHub<TextFieldEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent_);

    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->OnHover(isHover);
        }
    };
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
}

void TextFieldPattern::OnHover(bool isHover)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    LOGI("Textfield %{public}d %{public}s", tmpHost->GetId(), isHover ? "on hover" : "exit hover");
    auto frameId = tmpHost->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    if (isHover) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR);
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
    isOnHover_ = isHover;
    if (enableTouchAndHoverEffect_) {
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto renderContext = tmpHost->GetRenderContext();
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (isOnHover_) {
            if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
            tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
            return;
        }
        isOnHover_ = false;
        if (!isMousePressed_) {
            if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
                renderContext->UpdateBorderRadius(borderRadius_);
            }
            if (layoutProperty->GetShowUnderlineValue(false) && HasFocus() && IsUnspecifiedOrTextType()) {
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
        }
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::HandleMouseEvent(MouseInfo& info)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto frameId = tmpHost->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMouseStyleHoldNode(frameId);
    auto responseAreaWidth = responseArea_ ? responseArea_->GetAreaRect().Width() : 0.0f;
    if (info.GetLocalLocation().GetX() > (frameRect_.Width() - responseAreaWidth)) {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        return;
    }
    isUsingMouse_ = true;
    if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        HandleRightMouseEvent(info);
    } else if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        HandleLeftMouseEvent(info);
    }
}

void TextFieldPattern::HandleRightMouseEvent(MouseInfo& info)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto focusHub = tmpHost->GetOrCreateFocusHub();
    if (info.GetAction() == MouseAction::RELEASE && focusHub->IsCurrentFocus()) {
        LOGI("Handle mouse right button release");
        rightClickOffset_ = OffsetF(
            static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
        ProcessOverlay();
    }
}

void TextFieldPattern::HandleLeftMouseEvent(MouseInfo& info)
{
    switch (info.GetAction()) {
        case OHOS::Ace::MouseAction::PRESS: {
            HandleLeftMousePressEvent(info);
            break;
        }
        case OHOS::Ace::MouseAction::MOVE: {
            HandleLeftMouseMoveEvent(info); // 注意鼠标拖拽的滚动效果
            break;
        }
        case OHOS::Ace::MouseAction::RELEASE: {
            HandleLeftMouseReleaseEvent(info);
            break;
        }
        default: {
        }
    }
}

void TextFieldPattern::HandleLeftMousePressEvent(MouseInfo& info)
{
    if (IsSelected() && BetweenSelectedPosition(info.GetGlobalLocation())) {
        blockPress_ = true;
        return;
    }
    auto focusHub = GetFocusHub();
    if (!focusHub->IsFocusable()) {
        return;
    }
    mouseStatus_ = MouseStatus::PRESSED;
    blockPress_ = false;
    leftMouseCanMove_ = true;
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->GetInputStyleValue(InputStyle::DEFAULT) != InputStyle::INLINE &&
        (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately())) {
        StopTwinkling();
        return;
    }
    selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation());
    StartTwinkling();
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleLeftMouseMoveEvent(MouseInfo& info)
{
    if (!leftMouseCanMove_ || blockPress_) {
        return;
    }
    mouseStatus_ = MouseStatus::MOVE;
    selectController_->UpdateSecondHandleInfoByMouseOffset(info.GetLocalLocation()); // 更新时上报事件
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleLeftMouseReleaseEvent(MouseInfo& info)
{
    if (blockPress_ && mouseStatus_ == MouseStatus::PRESSED) {
        selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation());
        StartTwinkling();
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    mouseStatus_ = MouseStatus::NONE;
    blockPress_ = false;
    leftMouseCanMove_ = false;
    if (HasFocus() && RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    if (!HasFocus()) {
        return;
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto context = tmpHost->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetClickPosition(offset);
    textFieldManager->SetHeight(height);
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
}

TextInputAction TextFieldPattern::GetDefaultTextInputAction()
{
    TextInputAction defaultTextInputAction = TextInputAction::DONE;
    if (IsTextArea()) {
        defaultTextInputAction = TextInputAction::UNSPECIFIED;
    } else {
        defaultTextInputAction = TextInputAction::DONE;
    }
    return defaultTextInputAction;
}

// todo 代整改
bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, false);
    if (needShowSoftKeyboard) {
        LOGI("Start to request keyboard");
        if (customKeyboardBulder_) {
#if defined(ENABLE_STANDARD_INPUT) && defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeAttached_ = true;
#endif
            return RequestCustomKeyboard();
        }
#if defined(ENABLE_STANDARD_INPUT)
        if (textChangeListener_ == nullptr) {
            textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
        }
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request open soft keyboard failed because input method is null.");
            return false;
        }
        auto optionalTextConfig = GetMiscTextConfig();
        CHECK_NULL_RETURN(optionalTextConfig.has_value(), false);
        MiscServices::TextConfig textConfig = optionalTextConfig.value();
        LOGI("RequestKeyboard set calling window id is : %{public}u", textConfig.windowId);
        inputMethod->Attach(textChangeListener_, needShowSoftKeyboard, textConfig);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        imeAttached_ = true;
#endif
#else
        if (!HasConnection()) {
            TextInputConfiguration config;
            config.type = keyboard_;
            config.action = GetTextInputActionValue(GetDefaultTextInputAction());
            config.inputFilter = GetInputFilter();
            config.maxLength = GetMaxLength();
            if (keyboard_ == TextInputType::VISIBLE_PASSWORD) {
                config.obscureText = textObscured_;
            }
            LOGI("Request keyboard configuration: type=%{private}d action=%{private}d obscureText=%{private}d",
                keyboard_, config.action, textObscured_);
            connection_ = TextInputProxy::GetInstance().Attach(
                WeakClaim(this), config, context->GetTaskExecutor(), GetInstanceId());

            if (!HasConnection()) {
                LOGE("Get TextInput connection error");
                return false;
            }
            TextEditingValue value;
            value.text = contentController_->GetTextValue();
            value.hint = GetPlaceHolder();
            value.selection.Update(selectController_->GetStartIndex(), selectController_->GetEndIndex());
            connection_->SetEditingState(value, GetInstanceId());
        }
        connection_->Show(isFocusViewChanged, GetInstanceId());
#endif
    }
    return true;
}

#if defined(ENABLE_STANDARD_INPUT)
std::optional<MiscServices::TextConfig> TextFieldPattern::GetMiscTextConfig() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, {});
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto windowRect = pipeline->GetCurrentWindowRect();
    MiscServices::CursorInfo cursorInfo { .left = selectController_->GetCaretRect().Left() + windowRect.Left() +
                                                  parentGlobalOffset_.GetX(),
        .top = selectController_->GetCaretRect().Top() + windowRect.Top() + parentGlobalOffset_.GetY(),
        .width = CURSOR_WIDTH.ConvertToPx(),
        .height = selectController_->GetCaretRect().Height() };
    MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)keyboard_,
        .enterKeyType = (int32_t)GetTextInputActionValue(TextInputAction::DONE) };
    MiscServices::TextConfig textConfig = { .inputAttribute = inputAttribute,
        .cursorInfo = cursorInfo,
        .range = { .start = selectController_->GetStartIndex(), .end = selectController_->GetEndIndex() },
        .windowId = pipeline->GetFocusWindowId() };
    return textConfig;
}
#endif

bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    LOGI("Request close soft keyboard");
    if (forceClose) {
        isKeyboardClosedByUser_ = false;
        StopTwinkling();
        CloseSelectOverlay(true);
        if (customKeyboardBulder_ && isCustomKeyboardAttached_) {
            return CloseCustomKeyboard();
        }
#if defined(ENABLE_STANDARD_INPUT)
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        if (!imeAttached_) {
            return false;
        }
#endif
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            LOGE("Request close soft keyboard failed because input method is null.");
            return false;
        }
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
    return false;
}

bool TextFieldPattern::RequestCustomKeyboard()
{
    if (isCustomKeyboardAttached_) {
        return true;
    }
    CHECK_NULL_RETURN(customKeyboardBulder_, false);
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->BindKeyboard(customKeyboardBulder_, frameNode->GetId());
    isCustomKeyboardAttached_ = true;
    return true;
}

bool TextFieldPattern::CloseCustomKeyboard()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->CloseKeyboard(frameNode->GetId());
    isCustomKeyboardAttached_ = false;
    return true;
}

void TextFieldPattern::OnTextInputActionUpdate(TextInputAction value) {}

void TextFieldPattern::InsertValue(const std::string& insertValue)
{
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("Insert value '%{public}s'", insertValue.c_str());
    }
    auto wideInsertValue = StringUtils::ToWstring(insertValue);
    LOGD("Insert length %{public}d", static_cast<int32_t>(wideInsertValue.length()));
    auto originLength = static_cast<uint32_t>(contentController_->GetWideText().length());
    if (originLength >= GetMaxLength() && !IsSelected()) {
        LOGW("Max length reached");
        return;
    }
    auto caretStart = 0;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldLayoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    // SwapIfLarger(start, end);
    if (IsSelected()) {
        LOGI("In select mode, replace selected text");
        caretStart = start;
    } else {
        caretStart = selectController_->GetCaretIndex();
    }
    int32_t caretMoveLength = 0;
    if (IsSelected()) {
        auto originLength = static_cast<int32_t>(contentController_->GetWideText().length()) - (end - start);
        contentController_->ReplaceSelectedValue(start, end, insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);
    } else {
        auto originLength = static_cast<int32_t>(contentController_->GetWideText().length());
        contentController_->InsertValue(selectController_->GetCaretIndex(), insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);
    }
    selectController_->UpdateCaretIndex(caretStart + caretMoveLength);
    if (!IsTextArea() && IsInPasswordMode() && GetTextObscured()) {
        if (wideInsertValue.length() == 1) {
            obscureTickCountDown_ = OBSCURE_SHOW_TICKS;
            nakedCharPosition_ = selectController_->GetCaretIndex() - 1;
        } else {
            obscureTickCountDown_ = 0;
            nakedCharPosition_ = -1;
        }
    }
    UpdateEditingValueToRecord();
    cursorVisible_ = true;
    selectionMode_ = SelectionMode::NONE;
    CloseSelectOverlay(true);
    StartTwinkling();
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::UpdateEditingValueToRecord()
{
    if (operationRecords_.size() >= RECORD_MAX_LENGTH) {
        // case of max length is 0
        if (operationRecords_.empty()) {
            return;
        }
        operationRecords_.erase(operationRecords_.begin());
    }
    TextEditingValueNG record {
        .text = contentController_->GetTextValue(),
        .caretPosition = selectController_->GetCaretIndex(),
    };
    operationRecords_.emplace_back(record);
}

float TextFieldPattern::PreferredTextHeight(bool isPlaceholder)
{
    if (paragraph_ && paragraph_->GetHeight() != 0.0f) {
        return paragraph_->GetHeight() / paragraph_->GetLineCount();
    }
    RefPtr<Paragraph> paragraph;
    std::string textContent;
    TextStyle textStyle;
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, 0.0f);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto pipeline = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, 0.0f);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    // use text or placeHolder value if exists, space otherwise
    if (!isPlaceholder) {
        TextFieldLayoutAlgorithm::UpdateTextStyle(tmpHost, layoutProperty, textFieldTheme, textStyle, false);
        textContent = "a";
    } else {
        TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(tmpHost, layoutProperty, textFieldTheme, textStyle, false);
        textContent = "b";
    }
    if (textStyle.GetFontSize().IsNonPositive()) {
        textStyle.SetFontSize(DEFAULT_FONT);
    }
    ParagraphStyle paraStyle { .direction =
                                   TextFieldLayoutAlgorithm::GetTextDirection(contentController_->GetTextValue()),
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow(),
        .fontSize = textStyle.GetFontSize().ConvertToPx() };
    paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph, 0.0f);
    paragraph->AddText(StringUtils::Str8ToStr16(textContent));
    paragraph->Build();
    paragraph->Layout(std::numeric_limits<double>::infinity());
    return paragraph->GetHeight();
}

float TextFieldPattern::PreferredLineHeight()
{
    return PreferredTextHeight(contentController_->IsEmpty());
}

void TextFieldPattern::OnCursorMoveDone(TextAffinity textAffinity)
{
    CloseSelectOverlay();
    selectionMode_ = SelectionMode::NONE;
    selectController_->MoveCaretToContentRect(GetCaretIndex(), textAffinity);
    if (ResetObscureTickCountDown()) {
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        GetHost()->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

int32_t TextFieldPattern::GetWordLength(int32_t originCaretPosition, int32_t directionMove)
{
    if (contentController_->IsEmpty()) {
        return 0;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        LOGD("Get word length failed, the origin caret position is out of range");
        return 0;
    }
    // directionMove == 0 left, directionMove == 1 right
    // cannot get word length by current caret position and direction
    if ((directionMove == 0 && originCaretPosition == 0) || (directionMove == 1 && originCaretPosition == textLength)) {
        return 0;
    }
    int32_t offset = 0;
    int32_t strIndex = 0;
    auto wideTextValue = contentController_->GetWideText();
    for (directionMove == 0 ? strIndex = (originCaretPosition - 1) : strIndex = originCaretPosition;
         directionMove == 0 ? strIndex >= 0 : strIndex <= textLength;) {
        if ((wideTextValue[strIndex] >= L'0' && wideTextValue[strIndex] <= L'9') ||
            (wideTextValue[strIndex] >= L'a' && wideTextValue[strIndex] <= L'z') ||
            (wideTextValue[strIndex] >= L'A' && wideTextValue[strIndex] <= L'Z')) {
            offset++;
        } else {
            if (offset > 0) {
                break;
            }
            offset = 1;
            break;
        }
        if (directionMove == 0) {
            strIndex--;
        } else {
            strIndex++;
        }
    }
    return offset;
}

int32_t TextFieldPattern::GetLineBeginPosition(int32_t originCaretPosition, bool needToCheckLineChanged)
{
    if (contentController_->IsEmpty()) {
        return 0;
    }
    auto wideTextValue = contentController_->GetWideText();
    int32_t textLength = static_cast<int32_t>(wideTextValue.length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        LOGD("Get begin position failed, the origin caret position is out of range");
        return 0;
    }
    if (originCaretPosition == 0) {
        return originCaretPosition;
    }
    int32_t moveLineBeginOffset = 0;
    int32_t strIndex = originCaretPosition;
    do {
        moveLineBeginOffset++;
        strIndex--;
        // stop moving caret if reaches \n, text head or caret line changed
    } while (((strIndex > 0) && (wideTextValue[strIndex] != L'\n')) ||
             (needToCheckLineChanged && !CharLineChanged(strIndex)));
    if (strIndex < 0 || strIndex >= static_cast<int32_t>(wideTextValue.length())) {
        return 0;
    }
    if (wideTextValue[strIndex] == L'\n') {
        moveLineBeginOffset--;
    }
    if (moveLineBeginOffset > originCaretPosition) {
        return 0;
    }
    return originCaretPosition - moveLineBeginOffset;
}

int32_t TextFieldPattern::GetLineEndPosition(int32_t originCaretPosition, bool needToCheckLineChanged)
{
    if (contentController_->IsEmpty()) {
        return 0;
    }
    auto wideTextValue = contentController_->GetWideText();
    int32_t textLength = static_cast<int32_t>(wideTextValue.length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        LOGD("Get line end position failed, the origin caret position is out of range");
        return originCaretPosition;
    }
    if (originCaretPosition == textLength) {
        return originCaretPosition;
    }
    int32_t moveLineEndOffset = 0;
    int32_t strIndex = 0;
    for (strIndex = originCaretPosition; (strIndex <= textLength && wideTextValue[strIndex] != L'\n') ||
                                         (needToCheckLineChanged && !CharLineChanged(strIndex));
         strIndex++) {
        moveLineEndOffset++;
    }
    if (moveLineEndOffset > textLength - originCaretPosition) {
        return textLength;
    }
    return originCaretPosition + moveLineEndOffset;
}

bool TextFieldPattern::CharLineChanged(int32_t caretPosition)
{
    if (caretPosition < 0 || caretPosition > static_cast<int32_t>(contentController_->GetWideText().length())) {
        return true;
    }
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(selectController_->GetStartIndex(), caretMetrics);
    return !NearEqual(caretMetrics.offset.GetY(), selectController_->GetCaretRect().GetY());
}

bool TextFieldPattern::CursorMoveLeft()
{
    LOGI("Handle cursor move left");
    auto originCaretPosition = selectController_->GetCaretIndex();
    if (IsSelected()) {
        selectController_->UpdateCaretIndex(
            selectController_->GetEndIndex() - GetGraphemeClusterLength(contentController_->GetWideText(),
                                                   selectController_->GetSecondHandleIndex(), true));
        CloseSelectOverlay();
    } else {
        UpdateCaretPositionWithClamp(
            selectController_->GetCaretIndex() -
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetCaretIndex(), true));
    }
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveLeftWord()
{
    if (selectController_->GetCaretIndex() == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t leftWordLength = GetWordLength(originCaretPosition, 0);
    if (leftWordLength < 0 || leftWordLength > textLength || selectController_->GetCaretIndex() - leftWordLength < 0) {
        LOGD("Get left word length faild, the left word offset is out of range");
        return false;
    }
    if (IsSelected()) {
        selectController_->UpdateCaretIndex(selectController_->GetSecondHandleIndex() - leftWordLength);
        CloseSelectOverlay();
    } else {
        UpdateCaretPositionWithClamp(originCaretPosition - leftWordLength);
    }
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveLineBegin()
{
    if (selectController_->GetCaretIndex() == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t lineBeginPosition = GetLineBeginPosition(originCaretPosition);
    if (lineBeginPosition < 0 || lineBeginPosition > textLength) {
        LOGD("Cursor move to line begin faild, the line begin offset is out of range");
        return false;
    }
    if (selectController_->IsSelectedAll()) {
        selectController_->UpdateCaretIndex(0);
    } else if (IsTextArea()) {
        UpdateCaretPositionWithClamp(lineBeginPosition);
    } else {
        UpdateCaretPositionWithClamp(0);
    }
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveToParagraphBegin()
{
    if (selectController_->GetCaretIndex() == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    auto originCaretPosition = selectController_->GetCaretIndex();
    UpdateCaretPositionWithClamp(GetLineBeginPosition(originCaretPosition, false));
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveHome()
{
    // ctrl + home, caret move to position 0
    if (selectController_->GetCaretIndex() == 0) {
        LOGW("Caret position at beginning, cannot move to left");
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    UpdateCaretPositionWithClamp(0);
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveRight()
{
    LOGI("Handle cursor move right");
    auto originCaretPosition = selectController_->GetCaretIndex();
    if (IsSelected()) {
        CloseSelectOverlay();
        selectController_->UpdateCaretIndex(selectController_->GetEndIndex() + 1);
    } else {
        UpdateCaretPositionWithClamp(
            selectController_->GetCaretIndex() +
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetCaretIndex()));
    }
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveRightWord()
{
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t rightWordLength = GetWordLength(originCaretPosition, 1);
    if (rightWordLength < 0 || rightWordLength > textLength ||
        rightWordLength + selectController_->GetCaretIndex() > textLength) {
        LOGD("Get right word length failed, the right word offset is out of range");
        return false;
    }
    if (selectController_->IsSelectedAll()) {
        selectController_->UpdateCaretIndex(textLength);
    } else {
        UpdateCaretPositionWithClamp(originCaretPosition + rightWordLength);
    }
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveLineEnd()
{
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t lineEndPosition = GetLineEndPosition(originCaretPosition);
    if (lineEndPosition < 0 || lineEndPosition > textLength) {
        LOGD("Handle cursor move to line end failed, the line end position is out of range");
        return false;
    }
    if (selectController_->IsSelectedAll()) {
        selectController_->UpdateCaretIndex(textLength);
    } else if (IsTextArea()) {
        UpdateCaretPositionWithClamp(lineEndPosition);
    } else {
        UpdateCaretPositionWithClamp(textLength);
    }
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveToParagraphEnd()
{
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    auto originCaretPosition = selectController_->GetCaretIndex();
    UpdateCaretPositionWithClamp(GetLineEndPosition(originCaretPosition, false));
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveEnd()
{
    // ctrl end, caret to the very end
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
        LOGW("Caret position at the end, cannot move to right");
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    UpdateCaretPositionWithClamp(textLength);
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveUp()
{
    LOGI("Handle cursor move up");
    CHECK_NULL_RETURN(IsTextArea(), false);
    auto originCaretPosition = selectController_->GetCaretIndex();
    auto offsetX = selectController_->GetCaretRect().GetX() - contentRect_.GetX();
    auto offsetY = selectController_->GetCaretRect().GetY() - textRect_.GetY();
    // multiply by 0.5f to convert to the grapheme center point of the previous line.
    float verticalOffset = offsetY - PreferredLineHeight() * 0.5f;
    selectController_->UpdateCaretIndex(
        static_cast<int32_t>(paragraph_->GetGlyphIndexByCoordinate(Offset(offsetX, verticalOffset))));
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveDown()
{
    LOGI("Handle cursor move down");
    CHECK_NULL_RETURN(IsTextArea(), false);
    auto originCaretPosition = selectController_->GetCaretIndex();
    auto offsetX = selectController_->GetCaretRect().GetX() - contentRect_.GetX();
    auto offsetY = selectController_->GetCaretRect().GetY() - textRect_.GetY();
    // multiply by 1.5f to convert to the grapheme center point of the next line.
    float verticalOffset = offsetY + PreferredLineHeight() * 1.5f;
    selectController_->UpdateCaretIndex(
        static_cast<int32_t>(paragraph_->GetGlyphIndexByCoordinate(Offset(offsetX, verticalOffset))));
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

void TextFieldPattern::Delete(int32_t start, int32_t end)
{
    SwapIfLarger(start, end);
    LOGI("Handle Delete within [%{public}d, %{public}d]", start, end);
    contentController_->erase(start, end - start);
    selectController_->MoveCaretToContentRect(start);
    CloseSelectOverlay(true);
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    GetHost()->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                      : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::ClearEditingValue()
{
    contentController_->Reset();
    selectController_->UpdateCaretIndex(0);
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    tmpHost->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                    : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleCounterBorder()
{
    if (HasFocus() && IsNormalInlineState()) {
        return;
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto maxLength = GetMaxLength();
    auto currentLength = static_cast<uint32_t>(contentController_->GetWideText().length());
    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    BorderWidthProperty overCountBorderWidth;
    overCountBorderWidth.SetBorderWidth(OVER_COUNT_BORDER_WIDTH);
    BorderColorProperty currentBorderColor;
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasBorderColor()) {
        currentBorderColor = renderContext->GetBorderColor().value();
    }
    BorderColorProperty overCountBorderColor;
    overCountBorderColor.SetColor(textFieldTheme->GetOverCountBorderColor());
    if (currentLength == maxLength) {
        if (!(currentBorderWidth == overCountBorderWidth)) {
            lastDiffBorderWidth_ = currentBorderWidth;
            layoutProperty->UpdateBorderWidth(overCountBorderWidth);
            renderContext->UpdateBorderWidth(overCountBorderWidth);
        }
        if (!(currentBorderColor == overCountBorderColor)) {
            lastDiffBorderColor_ = currentBorderColor;
            renderContext->UpdateBorderColor(overCountBorderColor);
        }
    } else {
        if (currentBorderWidth == overCountBorderWidth) {
            layoutProperty->UpdateBorderWidth(lastDiffBorderWidth_);
            renderContext->UpdateBorderWidth(lastDiffBorderWidth_);
        }
        if (currentBorderColor == overCountBorderColor) {
            renderContext->UpdateBorderColor(lastDiffBorderColor_);
        }
    }
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    LOGI("PerformAction  %{public}d", static_cast<int32_t>(action));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    if (IsNormalInlineState()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto focusHub = host->GetOrCreateFocusHub();
        focusHub->LostFocus();
        eventHub->FireOnSubmit(static_cast<int32_t>(action));
        return;
    }

    if (IsTextArea()) {
        if (GetInputFilter() != "\n") {
            InsertValue("\n");
        }
        return;
    }
    eventHub->FireOnSubmit(static_cast<int32_t>(action));
    CloseKeyboard(forceCloseKeyboard);
    FocusHub::LostFocusToViewRoot();
}

void TextFieldPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
    contentController_->SetTextValue(value->text);
    selectController_->UpdateCaretIndex(value->selection.baseOffset);
    ContainerScope scope(GetInstanceId());
    UpdateEditingValueToRecord();
    CloseSelectOverlay();
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::UpdateInputFilterErrorText(const std::string& errorText)
{
    if (!errorText.empty()) {
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto textFieldEventHub = tmpHost->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(textFieldEventHub);
        textFieldEventHub->FireOnInputFilterError(errorText);
    }
}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

void TextFieldPattern::OnAreaChangedInner()
{
    auto parentGlobalOffset = GetTextPaintOffset();
    if (parentGlobalOffset != parentGlobalOffset_) {
        parentGlobalOffset_ = parentGlobalOffset;
        UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
        selectController_->UpdateCaretOffset();
        selectController_->CalculateHandleOffset();
        if (SelectOverlayIsOn()) {
            ProcessOverlay(false);
        }
    }
    RequestKeyboardOnFocus();
}

void TextFieldPattern::RequestKeyboardOnFocus()
{
    if (!needToRequestKeyboardOnFocus_ || !needToRequestKeyboardInner_) {
        return;
    }
    LOGI("RequestKeyboardOnFocus");
    if (!RequestKeyboard(false, true, true)) {
        return;
    }
    NotifyOnEditChanged(true);
    needToRequestKeyboardInner_ = false;
}

void TextFieldPattern::OnVisibleChange(bool isVisible)
{
    LOGI("visible change to %{public}d", isVisible);
    if (!isVisible) {
        LOGI("TextField is not visible");
        selectionMode_ = SelectionMode::NONE;
        CloseKeyboard(true);
        if (SelectOverlayIsOn()) {
            StartTwinkling();
        }
    }
}

void TextFieldPattern::HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    LOGI("Textfield handle surface change, new width %{public}d, new height %{public}d, prev width %{public}d, prev "
         "height %{public}d",
        newWidth, newHeight, prevWidth, prevHeight);
    CloseSelectOverlay();
    if (HasFocus() && IsSingleHandle()) {
        StartTwinkling();
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    UpdateCaretInfoToController();
}

void TextFieldPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY) const
{
    LOGI("Textfield handle surface position change, posX %{public}d, posY %{public}d", posX, posY);
    UpdateCaretInfoToController();
}

void TextFieldPattern::InitSurfaceChangedCallback()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight);
                }
            });
        LOGI("Add surface changed callback id %{public}d", callbackId);
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::InitSurfacePositionChangedCallback()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfacePositionChangedCallback()) {
        auto callbackId =
            pipeline->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfacePositionChanged(posX, posY);
                }
            });
        LOGI("Add position changed callback id %{public}d", callbackId);
        UpdateSurfacePositionChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::DeleteBackward(int32_t length)
{
    LOGI("Handle DeleteBackward %{public}d characters", length);
    ResetObscureTickCountDown();
    if (IsSelected()) {
        Delete(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        return;
    }
    if (selectController_->GetCaretIndex() <= 0) {
        LOGW("Caret position at the beginning , cannot DeleteBackward");
        return;
    }
    auto start = std::max(selectController_->GetCaretIndex() - length, 0);
    contentController_->erase(start, length);
    selectController_->UpdateCaretIndex(start);
    CloseSelectOverlay();
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    tmpHost->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                    : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::DeleteForward(int32_t length)
{
    LOGI("Handle DeleteForward %{public}d characters", length);
    ResetObscureTickCountDown();
    if (IsSelected()) {
        Delete(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        return;
    }
    if (selectController_->GetCaretIndex() >= static_cast<int32_t>(contentController_->GetWideText().length())) {
        LOGW("Caret position at the end , cannot DeleteForward");
        return;
    }
    contentController_->erase(selectController_->GetCaretIndex(), length);
    selectionMode_ = SelectionMode::NONE;
    CloseSelectOverlay();
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    tmpHost->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                    : PROPERTY_UPDATE_MEASURE);
}

std::u16string TextFieldPattern::GetLeftTextOfCursor(int32_t number)
{
    auto start = selectController_->GetCaretIndex();
    if (IsSelected()) {
        start = selectController_->GetStartIndex();
    }
    auto stringText = contentController_->GetSelectedValue(start - number, start);
    return StringUtils::Str8ToStr16(stringText);
}

std::u16string TextFieldPattern::GetRightTextOfCursor(int32_t number)
{
    auto end = selectController_->GetCaretIndex();
    if (IsSelected()) {
        end = selectController_->GetEndIndex();
    }
    auto stringText = contentController_->GetSelectedValue(end, end + number);
    return StringUtils::Str8ToStr16(stringText);
}

int32_t TextFieldPattern::GetTextIndexAtCursor()
{
    return selectController_->GetCaretIndex();
}

void TextFieldPattern::AfterSelection()
{
    LOGI("Selection %{public}s, caret position %{public}d", selectController_->ToString().c_str(),
        selectController_->GetCaretIndex());
    ResetObscureTickCountDown();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    tmpHost->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                    : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleSelectionUp()
{
    LOGI("Handle selection up");
    if (!IsTextArea()) {
        LOGW("Unsupported operation for text field");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
    }
    auto newOffsetY = selectController_->GetCaretRect().GetY() - PreferredLineHeight() * 0.5 - textRect_.GetY();
    selectController_->MoveSecondHandleToContentRect(static_cast<int32_t>(
        paragraph_->GetGlyphIndexByCoordinate(Offset(selectController_->GetCaretRect().GetX(), newOffsetY))));
    AfterSelection();
}

void TextFieldPattern::HandleSelectionDown()
{
    LOGI("Handle selection down");
    if (!IsTextArea()) {
        LOGW("Unsupported operation for text field");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
    }
    auto newOffsetY = selectController_->GetCaretRect().GetY() + PreferredLineHeight() * 1.5 - textRect_.GetY();
    selectController_->MoveSecondHandleToContentRect(static_cast<int32_t>(
        paragraph_->GetGlyphIndexByCoordinate(Offset(selectController_->GetCaretRect().GetX(), newOffsetY))));
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeft()
{
    LOGI("Handle selection left");
    if (!IsSelected()) {
        if (selectController_->GetCaretIndex() == 0) {
            LOGW("Caret position at beginning, cannot update selection to left");
            return;
        }
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(
            selectController_->GetSecondHandleIndex() -
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetCaretIndex(), true));
    } else {
        selectController_->MoveSecondHandleToContentRect(
            selectController_->GetSecondHandleIndex() - GetGraphemeClusterLength(contentController_->GetWideText(),
                                                            selectController_->GetSecondHandleIndex(), true));
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeftWord()
{
    if (selectController_->GetCaretIndex() == 0) {
        LOGW("Caret position at beginning, cannot update selection to left");
        return;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t leftWordLength = GetWordLength(selectController_->GetCaretIndex(), 0);
    if (leftWordLength < 0 || leftWordLength > textLength || selectController_->GetCaretIndex() - leftWordLength < 0) {
        LOGD("Handle select a left word failed, the left word offset is out of range");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(selectController_->GetSecondHandleIndex() - leftWordLength);
    } else {
        selectController_->MoveSecondHandleToContentRect(selectController_->GetSecondHandleIndex() - leftWordLength);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLineBegin()
{
    if (selectController_->GetCaretIndex()) {
        LOGW("Caret position at beginning, cannot update selection to left");
        return;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t lineBeginPosition = GetLineBeginPosition(selectController_->GetCaretIndex());
    if (lineBeginPosition < 0 || lineBeginPosition > textLength) {
        LOGD("Handle select line begin failed, the line begin offset is out of range");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(lineBeginPosition);
    } else {
        selectController_->MoveSecondHandleToContentRect(lineBeginPosition);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionHome()
{
    if (selectController_->GetCaretIndex() == 0) {
        LOGW("Caret position at beginning, cannot update selection to left");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(0);
    } else {
        selectController_->MoveSecondHandleToContentRect(0);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRight()
{
    LOGI("Handle selection right");
    // if currently not in select mode, reset baseOffset and move destinationOffset and caret position
    if (!IsSelected()) {
        if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
            LOGW("Caret position at the end, cannot update selection to right");
            return;
        }
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(
            selectController_->GetSecondHandleIndex() +
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetSecondHandleIndex()));
    } else {
        // if currently not in select mode, move destinationOffset and caret position only
        selectController_->MoveSecondHandleToContentRect(
            selectController_->GetSecondHandleIndex() +
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetSecondHandleIndex()));
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRightWord()
{
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (selectController_->GetCaretIndex() == textLength) {
        LOGW("Caret position at the end, cannot update selection to right");
        return;
    }
    int32_t rightWordLength = GetWordLength(selectController_->GetCaretIndex(), 1);
    if (rightWordLength < 0 || rightWordLength > textLength ||
        rightWordLength + selectController_->GetCaretIndex() > textLength) {
        LOGD("Handle select a right word failed, the right word offset is out of range");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(selectController_->GetSecondHandleIndex() + rightWordLength);
    } else {
        selectController_->MoveSecondHandleToContentRect(selectController_->GetSecondHandleIndex() + rightWordLength);
        AfterSelection();
    }
}

void TextFieldPattern::HandleSelectionLineEnd()
{
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (selectController_->GetCaretIndex() == textLength) {
        LOGW("Caret position at the end, cannot update selection to right");
        return;
    }
    int32_t lineEndPosition = GetLineEndPosition(selectController_->GetCaretIndex());
    if (lineEndPosition < 0 || lineEndPosition > textLength) {
        LOGD("Handle select a line end failed, the line end offset is out of range");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(lineEndPosition);
    } else {
        selectController_->MoveSecondHandleToContentRect(lineEndPosition);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionEnd()
{
    // shift end, select to the end of current line
    int32_t endPos = static_cast<int32_t>(contentController_->GetWideText().length());
    if (selectController_->GetCaretIndex() == endPos) {
        LOGW("Caret position at the end, cannot update selection to right");
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleToContentRect(endPos);
    } else {
        selectController_->MoveSecondHandleToContentRect(endPos);
    }
    AfterSelection();
}

void TextFieldPattern::SetCaretPosition(int32_t position)
{
    LOGI("Set caret position to %{public}d", position);
    selectController_->UpdateCaretIndex(position);
    CloseSelectOverlay();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::SetSelectionFlag(int32_t selectionStart, int32_t selectionEnd)
{
    if (!HasFocus()) {
        return;
    }
    cursorVisible_ = false;
    HandleSetSelection(selectionStart, selectionEnd, true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool TextFieldPattern::OnBackPressed()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    LOGI("Textfield %{public}d receives back press event", tmpHost->GetId());
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if ((!imeAttached_ || (imeAttached_ && !imeShown_)) && !isCustomKeyboardAttached_) {
#else
    if (!isCustomKeyboardAttached_) {
#endif
        LOGI("Ime is not attached or is hidden, return for not consuming the back press event");
        return false;
    }

    LOGI("Closing keyboard on back press");
    selectController_->ResetHandles();
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    CloseKeyboard(true);
#if defined(ANDROID_PLATFORM)
    return false;
#else
    return true;
#endif
}

int32_t TextFieldPattern::GetNakedCharPosition() const
{
    if (IsTextArea() || !IsInPasswordMode() || obscureTickCountDown_ <= 0 || !GetTextObscured()) {
        return -1;
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, -1);
    auto content = contentController_->GetTextValue();
    if (content.empty()) {
        return -1;
    }
    return nakedCharPosition_;
}

std::string TextFieldPattern::TextInputTypeToString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    switch (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        case TextInputType::NUMBER:
            return "InputType.Number";
        case TextInputType::EMAIL_ADDRESS:
            return "InputType.Email";
        case TextInputType::VISIBLE_PASSWORD:
            return "InputType.Password";
        default:
            return "InputType.Normal";
    }
}

std::string TextFieldPattern::TextInputActionToString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    switch (GetTextInputActionValue(TextInputAction::DONE)) {
        case TextInputAction::GO:
            return "EnterKeyType.Go";
        case TextInputAction::SEARCH:
            return "EnterKeyType.Search";
        case TextInputAction::SEND:
            return "EnterKeyType.Send";
        case TextInputAction::NEXT:
            return "EnterKeyType.Next";
        default:
            return "EnterKeyType.Done";
    }
}

std::string TextFieldPattern::GetPlaceholderFont() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, "");
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, "");
    auto theme = context->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, "");
    auto jsonValue = JsonUtil::Create(true);
    if (layoutProperty->GetPlaceholderItalicFontStyle().value_or(Ace::FontStyle::NORMAL) == Ace::FontStyle::NORMAL) {
        jsonValue->Put("style", "FontStyle.Normal");
    } else {
        jsonValue->Put("style", "FontStyle.Italic");
    }
    // placeholder font size not exist in theme, use normal font size by default
    if (!layoutProperty->GetPlaceholderFontSize()) {
        jsonValue->Put("size", GetFontSize().c_str());
    } else {
        jsonValue->Put("size", layoutProperty->GetPlaceholderFontSize()->ToString().c_str());
    }
    auto weight = layoutProperty->GetPlaceholderFontWeightValue(theme->GetFontWeight());
    switch (weight) {
        case FontWeight::W100:
            jsonValue->Put("weight", "100");
            break;
        case FontWeight::W200:
            jsonValue->Put("weight", "200");
            break;
        case FontWeight::W300:
            jsonValue->Put("weight", "300");
            break;
        case FontWeight::W400:
            jsonValue->Put("weight", "400");
            break;
        case FontWeight::W500:
            jsonValue->Put("weight", "500");
            break;
        case FontWeight::W600:
            jsonValue->Put("weight", "600");
            break;
        case FontWeight::W700:
            jsonValue->Put("weight", "700");
            break;
        case FontWeight::W800:
            jsonValue->Put("weight", "800");
            break;
        case FontWeight::W900:
            jsonValue->Put("weight", "900");
            break;
        default:
            jsonValue->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(weight).c_str());
    }
    auto family = layoutProperty->GetPlaceholderFontFamilyValue({ "sans-serif" });
    std::string jsonFamily = ConvertFontFamily(family);
    jsonValue->Put("fontFamily", jsonFamily.c_str());
    return jsonValue->ToString();
}

RefPtr<TextFieldTheme> TextFieldPattern::GetTheme() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, nullptr);
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto theme = context->GetTheme<TextFieldTheme>();
    return theme;
}

std::string TextFieldPattern::GetTextColor() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetTextColorValue(theme->GetTextColor()).ColorToString();
}

std::string TextFieldPattern::GetCaretColor() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, "");
    return paintProperty->GetCursorColorValue(theme->GetCursorColor()).ColorToString();
}

std::string TextFieldPattern::GetPlaceholderColor() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetPlaceholderTextColorValue(theme->GetTextColor()).ColorToString();
}

std::string TextFieldPattern::GetFontSize() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetFontSizeValue(theme->GetFontSize()).ToString();
}

Ace::FontStyle TextFieldPattern::GetItalicFontStyle() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Ace::FontStyle::NORMAL);
    return layoutProperty->GetItalicFontStyle().value_or(Ace::FontStyle::NORMAL);
}

std::string TextFieldPattern::GetShowPasswordIconString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "false");
    return layoutProperty->GetShowPasswordIconValue(false) ? "true" : "false";
}

std::string TextFieldPattern::GetInputStyleString() const
{
    std::string result = isTextInput_ ? "TextInputStyle.Default" : "TextContentStyle.DEFAULT";
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, result);
    switch (paintProperty->GetInputStyleValue(InputStyle::DEFAULT)) {
        case InputStyle::INLINE:
            result = isTextInput_ ? "TextInputStyle.Inline" : "TextContentStyle.INLINE";
            break;
        case InputStyle::DEFAULT:
        default:
            break;
    }
    return result;
}

FontWeight TextFieldPattern::GetFontWeight() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, FontWeight::NORMAL);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, FontWeight::NORMAL);
    return layoutProperty->GetFontWeightValue(theme->GetFontWeight());
}

std::string TextFieldPattern::GetFontFamily() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "HarmonyOS Sans");
    auto family = layoutProperty->GetFontFamilyValue({ "HarmonyOS Sans" });
    return ConvertFontFamily(family);
}

TextAlign TextFieldPattern::GetTextAlign() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, TextAlign::START);
    return layoutProperty->GetTextAlign().value_or(TextAlign::START);
}

uint32_t TextFieldPattern::GetMaxLength() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Infinity<uint32_t>());
    return layoutProperty->HasMaxLength() ? layoutProperty->GetMaxLengthValue(Infinity<uint32_t>())
                                          : Infinity<uint32_t>();
}

uint32_t TextFieldPattern::GetMaxLines() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, Infinity<uint32_t>());
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, Infinity<uint32_t>());
    if (IsNormalInlineState()) {
        return layoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE);
    }
    return layoutProperty->HasMaxLines() ? layoutProperty->GetMaxLinesValue(Infinity<uint32_t>())
                                         : Infinity<uint32_t>();
}

std::string TextFieldPattern::GetPlaceHolder() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetPlaceholderValue("");
}

std::string TextFieldPattern::GetInputFilter() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetInputFilterValue("");
}

std::string TextFieldPattern::GetErrorTextString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetErrorTextValue("");
}

bool TextFieldPattern::GetErrorTextState() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowErrorTextValue(false);
}

void TextFieldPattern::SearchRequestKeyboard()
{
    StartTwinkling();
    selectionMode_ = SelectionMode::NONE;
    if (RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
}

std::string TextFieldPattern::GetCopyOptionString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    std::string copyOptionString = "CopyOptions.None";
    switch (layoutProperty->GetCopyOptionsValue(CopyOptions::None)) {
        case CopyOptions::InApp:
            copyOptionString = "CopyOptions.InApp";
            break;
        case CopyOptions::Local:
            copyOptionString = "CopyOptions.Local";
            break;
        case CopyOptions::Distributed:
            copyOptionString = "CopyOptions.Distributed";
            break;
        case CopyOptions::None:
        default:
            break;
    }
    return copyOptionString;
}

std::string TextFieldPattern::GetBarStateString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    std::string displayModeString;
    switch (layoutProperty->GetDisplayModeValue(DisplayMode::AUTO)) {
        case DisplayMode::OFF:
            displayModeString = "BarState.OFF";
            break;
        case DisplayMode::ON:
            displayModeString = "BarState.ON";
            break;
        case DisplayMode::AUTO:
        default:
            displayModeString = "BarState.AUTO";
            break;
    }
    return displayModeString;
}

void TextFieldPattern::UpdateScrollBarOffset()
{
    if (!GetScrollBar() && !GetScrollBarProxy()) {
        return;
    }
    auto paddingHeight = GetPaddingTop() + GetPaddingBottom();
    auto paddingRight = GetPaddingRight();
    auto contentHeight = contentRect_.Height();
    if (inlineFocusState_) {
        paddingHeight = 0.0f;
        paddingRight = 0.0f;
        contentHeight = GetSingleLineHeight() * GetMaxLines();
    }
    Size size(frameRect_.Width(), contentHeight + paddingHeight);
    UpdateScrollBarRegion(
        contentRect_.GetY() - textRect_.GetY(), textRect_.Height() + paddingHeight, size, Offset(0.0, 0.0));
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->PlayScrollBarAppearAnimation();
        }
        UpdateSelectMenuVisibility(false);
        return true;
    }
    if (IsReachedBoundary(offset)) {
        return false;
    }
    OnTextInputScroll(offset);
    OnTextAreaScroll(offset);
    return true;
}

void TextFieldPattern::CheckScrollable()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (contentController_->IsEmpty()) {
        scrollable_ = false;
    } else {
        scrollable_ = GreatNotEqual(textRect_.Height(), contentRect_.Height());
    }
    SetScrollEnable(scrollable_);
}

bool TextFieldPattern::HasStateStyle(UIState state) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, false);
    return hub->HasStateStyle(state);
}

double TextFieldPattern::GetScrollBarWidth()
{
    auto scrollBar = GetScrollBar();
    double scrollBarWidth = 0.0;
    if (scrollBar) {
        scrollBarWidth = scrollBar->GetBarRect().Width();
    }
    return scrollBarWidth;
}

void TextFieldPattern::SetUnitNode(const RefPtr<NG::UINode>& unitNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(unitNode);
    if (!host->GetChildren().empty()) {
        host->Clean();
    }
    unitNode->MountToParent(host);
}

void TextFieldPattern::AddCounterNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!host->GetChildren().empty()) {
        host->Clean();
    }
    auto counterTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    counterTextNode->MountToParent(host);
    counterTextNode->MarkModifyDone();
    counterTextNode->MarkDirtyNode();
}

void TextFieldPattern::ClearCounterNode()
{
    auto host = GetHost();
    if (!host->GetChildren().empty()) {
        host->Clean();
    }
}

void TextFieldPattern::SetShowError()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto passWordMode =
        layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto visible = layoutProperty->GetShowErrorTextValue(false);

    if (visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        underlineColor_ = textFieldTheme->GetErrorUnderlineColor();
        underlineWidth_ = ERROR_UNDERLINE_WIDTH;
        preErrorState_ = true;
    }
    if (!visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        underlineWidth_ = UNDERLINE_WIDTH;
        preErrorState_ = false;
    }
    if (visible && passWordMode) {
        BorderWidthProperty borderWidth;
        BorderColorProperty borderColor;
        preErrorState_ = true;
        borderWidth.SetBorderWidth(ERROR_BORDER_WIDTH);
        layoutProperty->UpdateBorderWidth(borderWidth);
        borderColor.SetColor(textFieldTheme->GetPasswordErrorBorderColor());
        renderContext->UpdateBorderColor(borderColor);
        renderContext->UpdateBackgroundColor(textFieldTheme->GetPasswordErrorInputColor());
        layoutProperty->UpdateTextColor(textFieldTheme->GetPasswordErrorTextColor());
    }
    if (!visible && passWordMode) {
        layoutProperty->UpdateBorderWidth(passwordModeStyle_.borderwidth);
        renderContext->UpdateBorderColor(passwordModeStyle_.borderColor);
        renderContext->UpdateBackgroundColor(passwordModeStyle_.bgColor);
        layoutProperty->UpdateTextColor(passwordModeStyle_.textColor);
        preErrorState_ = false;
    }
    if (visible && !passWordMode) {
        layoutProperty->UpdateBorderWidth(passwordModeStyle_.borderwidth);
        renderContext->UpdateBorderColor(passwordModeStyle_.borderColor);
        renderContext->UpdateBackgroundColor(passwordModeStyle_.bgColor);
        layoutProperty->UpdateTextColor(passwordModeStyle_.textColor);
        preErrorState_ = true;
    }
    UpdateErrorTextMargin();
}

void TextFieldPattern::UpdateErrorTextMargin()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    MarginProperty errorMargin;
    auto errorTextCapsuleMargin = theme->GetErrorTextCapsuleMargin();
    if (layoutProperty->GetShowErrorTextValue(false) && (preErrorMargin_ < errorTextCapsuleMargin.ConvertToPx())) {
        errorMargin.bottom = CalcLength(errorTextCapsuleMargin);
        errorMargin.right = CalcLength(passwordModeStyle_.margin.right->GetDimension());
        errorMargin.left = CalcLength(passwordModeStyle_.margin.left->GetDimension());
        errorMargin.top = CalcLength(passwordModeStyle_.margin.top->GetDimension());
        layoutProperty->UpdateMargin(errorMargin);
        restoreMarginState_ = true;
    } else if (restoreMarginState_ == true) {
        errorMargin.bottom = CalcLength(preErrorMargin_);
        errorMargin.right = CalcLength(passwordModeStyle_.margin.right->GetDimension());
        errorMargin.left = CalcLength(passwordModeStyle_.margin.left->GetDimension());
        errorMargin.top = CalcLength(passwordModeStyle_.margin.top->GetDimension());
        layoutProperty->UpdateMargin(errorMargin);
        restoreMarginState_ = false;
    }
}

void TextFieldPattern::SavePasswordModeStates()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto textFieldTheme = themeManager->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    preErrorMargin_ = GetMarginBottom();
    passwordModeStyle_.bgColor = renderContext->GetBackgroundColor().value_or(textFieldTheme->GetBgColor());
    passwordModeStyle_.textColor = layoutProperty->GetTextColorValue(textFieldTheme->GetTextColor());
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        passwordModeStyle_.borderwidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
        passwordModeStyle_.borderwidth = borderWidth;
    }
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::TRANSPARENT);
    passwordModeStyle_.borderColor = renderContext->GetBorderColor().value_or(borderColor);
    auto radius = textFieldTheme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    passwordModeStyle_.radius = renderContext->GetBorderRadius().value_or(borderRadius);

    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    if (paddingProperty) {
        passwordModeStyle_.padding.left = CalcLength(paddingProperty->left->GetDimension().ConvertToPx());
        passwordModeStyle_.padding.top = CalcLength(paddingProperty->top->GetDimension().ConvertToPx());
        passwordModeStyle_.padding.bottom = CalcLength(paddingProperty->bottom->GetDimension().ConvertToPx());
        passwordModeStyle_.padding.right = CalcLength(paddingProperty->right->GetDimension().ConvertToPx());
    } else {
        passwordModeStyle_.padding.left = CalcLength(0.0);
        passwordModeStyle_.padding.top = CalcLength(0.0);
        passwordModeStyle_.padding.bottom = CalcLength(0.0);
        passwordModeStyle_.padding.right = CalcLength(0.0);
    }
    const auto& marginProperty = layoutProperty->GetMarginProperty();
    if (marginProperty) {
        passwordModeStyle_.margin.left = CalcLength(marginProperty->left->GetDimension().ConvertToPx());
        passwordModeStyle_.margin.top = CalcLength(marginProperty->top->GetDimension().ConvertToPx());
        passwordModeStyle_.margin.bottom = CalcLength(marginProperty->bottom->GetDimension().ConvertToPx());
        passwordModeStyle_.margin.right = CalcLength(marginProperty->right->GetDimension().ConvertToPx());
    } else {
        passwordModeStyle_.margin.left = CalcLength(0.0_vp);
        passwordModeStyle_.margin.top = CalcLength(0.0_vp);
        passwordModeStyle_.margin.bottom = CalcLength(0.0_vp);
        passwordModeStyle_.margin.right = CalcLength(0.0_vp);
    }
}

void TextFieldPattern::SaveUnderlineStates()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    Radius radius;
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    borderRadius_ = renderContext->GetBorderRadius().value_or(borderRadius);
}

void TextFieldPattern::ApplyUnderlineStates()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    CalcSize idealSize;
    layoutProperty->UpdatePadding({ CalcLength(UNDERLINE_NORMAL_PADDING), CalcLength(UNDERLINE_NORMAL_PADDING),
        CalcLength(0.0_vp), CalcLength(0.0_vp) });
    ProcessInnerPadding();
    if (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_NORMAL) {
        std::optional<CalcLength> height(UNDERLINE_NORMAL_HEIGHT);
        idealSize.SetHeight(height);
        layoutProperty->UpdateUserDefinedIdealSize(idealSize);
    }
    layoutProperty->UpdateFontSize(theme->GetUnderlineFontSize());
    if (!layoutProperty->HasTextColor()) {
        layoutProperty->UpdateTextColor(theme->GetUnderlineTextColor());
    }
    Radius radius;
    renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
}

float TextFieldPattern::GetMarginBottom() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, 0.0f);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    const auto& getMargin = layoutProperty->GetMarginProperty();
    if (getMargin && getMargin->bottom.has_value()) {
        return getMargin->bottom->GetDimension().ConvertToPx();
    }
    return 0.0f;
}

std::string TextFieldPattern::GetShowResultImageSrc() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, "");
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    auto showImageSource = layoutProperty->GetShowPasswordSourceInfo();
    if (showImageSource) {
        return showImageSource->GetSrc();
    }
    return SHOW_PASSWORD_SVG;
}

std::string TextFieldPattern::GetHideResultImageSrc() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, "");
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    auto hideSourceInfo = layoutProperty->GetHidePasswordSourceInfo();
    if (hideSourceInfo) {
        return hideSourceInfo->GetSrc();
    }
    return HIDE_PASSWORD_SVG;
}

void TextFieldPattern::SaveInlineStates()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    inlineState_.textColor = layoutProperty->GetTextColorValue(theme->GetTextColor());
    inlineState_.bgColor = renderContext->GetBackgroundColor().value_or(theme->GetBgColor());
    auto radius = theme->GetBorderRadius();
    BorderRadiusProperty borderRadius { radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() };
    inlineState_.radius = renderContext->GetBorderRadius().value_or(borderRadius);
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        inlineState_.borderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        inlineState_.borderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    if (renderContext->HasBorderColor()) {
        inlineState_.borderColor = renderContext->GetBorderColor().value();
        inlineState_.hasBorderColor = true;
    }
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    if (paddingProperty) {
        inlineState_.padding.left = CalcLength(paddingProperty->left->GetDimension().ConvertToPx());
        inlineState_.padding.top = CalcLength(paddingProperty->top->GetDimension().ConvertToPx());
        inlineState_.padding.bottom = CalcLength(paddingProperty->bottom->GetDimension().ConvertToPx());
        inlineState_.padding.right = CalcLength(paddingProperty->right->GetDimension().ConvertToPx());
    } else {
        inlineState_.padding.left = CalcLength(0.0_vp);
        inlineState_.padding.top = CalcLength(0.0_vp);
        inlineState_.padding.bottom = CalcLength(0.0_vp);
        inlineState_.padding.right = CalcLength(0.0_vp);
    }
    const auto& marginProperty = layoutProperty->GetMarginProperty();
    if (marginProperty) {
        inlineState_.margin.left = CalcLength(marginProperty->left->GetDimension().ConvertToPx());
        inlineState_.margin.top = CalcLength(marginProperty->top->GetDimension().ConvertToPx());
        inlineState_.margin.bottom = CalcLength(marginProperty->bottom->GetDimension().ConvertToPx());
        inlineState_.margin.right = CalcLength(marginProperty->right->GetDimension().ConvertToPx());
    } else {
        inlineState_.margin.left = CalcLength(0.0_vp);
        inlineState_.margin.top = CalcLength(0.0_vp);
        inlineState_.margin.bottom = CalcLength(0.0_vp);
        inlineState_.margin.right = CalcLength(0.0_vp);
    }
    if (inlineState_.saveInlineState) {
        inlineState_.frameRect = frameRect_;
    }
}

void TextFieldPattern::TextAreaInputRectUpdate(RectF& rect)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && !contentController_->IsEmpty()) {
        auto inputContentWidth = GetParagraph()->GetMaxIntrinsicWidth();
        switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
            case TextAlign::START:
                if (inputContentWidth < contentRect_.Width()) {
                    rect.SetWidth(inputContentWidth);
                }
                break;
            case TextAlign::CENTER:
                if (inputContentWidth < contentRect_.Width()) {
                    rect.SetLeft(
                        static_cast<float>(rect.GetX()) + contentRect_.Width() / 2.0f - inputContentWidth / 2.0f);
                    rect.SetWidth(inputContentWidth);
                }
                break;
            case TextAlign::END:
                if (inputContentWidth < contentRect_.Width()) {
                    rect.SetLeft(static_cast<float>(rect.GetX()) + contentRect_.Width() -
                                 static_cast<float>(CURSOR_WIDTH.ConvertToPx()) - inputContentWidth);
                    rect.SetWidth(inputContentWidth);
                }
                break;
            default:
                break;
        }
    }
}

void TextFieldPattern::TextIsEmptyRect(RectF& rect)
{
    rect = selectController_->CalculateEmptyValueCaretRect();
}

void TextFieldPattern::UpdateRectByAlignment(RectF& rect)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto alignment = layoutProperty->GetPositionProperty()
                         ? layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER)
                         : Alignment::CENTER;
    if (alignment == Alignment::CENTER_LEFT || alignment == Alignment::CENTER || alignment == Alignment::CENTER_RIGHT) {
        rect.SetTop(frameRect_.Height() / 2.0f - rect.Height() / 2.0f);
    } else if (alignment == Alignment::BOTTOM_LEFT || alignment == Alignment::BOTTOM_CENTER ||
               alignment == Alignment::BOTTOM_RIGHT) {
        rect.SetTop(frameRect_.Height() - rect.Height());
    } else if (alignment == Alignment::TOP_LEFT || alignment == Alignment::TOP_CENTER ||
               alignment == Alignment::TOP_RIGHT) {
        rect.SetTop(0);
    } else {
    }
    if (rect.Height() > contentRect_.Height()) {
        rect.SetTop(textRect_.GetY());
    }
}

void TextFieldPattern::ApplyInlineStates(bool focusStatus)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    layoutProperty->UpdateTextColor(theme->GetInlineTextColor());
    auto radius = theme->GetInlineRadiusSize();
    renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
    renderContext->UpdateBackgroundColor(theme->GetInlineBgColor());
    BorderWidthProperty inlineBorderWidth;
    inlineBorderWidth.SetBorderWidth(INLINE_BORDER_WIDTH);
    layoutProperty->UpdateBorderWidth(inlineBorderWidth);
    renderContext->UpdateBorderWidth(inlineBorderWidth);
    BorderColorProperty inlineBorderColor;
    inlineBorderColor.SetColor(theme->GetInlineBorderColor());
    renderContext->UpdateBorderColor(inlineBorderColor);
    auto padding = theme->GetInlineBorderWidth();
    layoutProperty->UpdatePadding(
        { CalcLength(padding), CalcLength(padding), CalcLength(padding), CalcLength(padding) });
    ProcessInnerPadding();
    SetTextRectOffset();
    MarginProperty margin;
    margin.bottom =
        CalcLength(inlineState_.padding.bottom->GetDimension() + inlineState_.margin.bottom->GetDimension());
    margin.right = CalcLength(inlineState_.padding.right->GetDimension() + inlineState_.margin.right->GetDimension());
    margin.left = CalcLength(inlineState_.padding.left->GetDimension() + inlineState_.margin.left->GetDimension());
    margin.top = CalcLength(inlineState_.padding.top->GetDimension() + inlineState_.margin.top->GetDimension());
    layoutProperty->UpdateMargin(margin);
    if (!IsTextArea()) {
        layoutProperty->ResetMaxLines();
    }
    needApplyInlineSize_ = true;
}

bool TextFieldPattern::ResetObscureTickCountDown()
{
    auto oldTickCountDown_ = obscureTickCountDown_;
    if (!IsTextArea() && GetTextObscured() && IsInPasswordMode()) {
        obscureTickCountDown_ = 0;
    }
    return oldTickCountDown_ != obscureTickCountDown_;
}

bool TextFieldPattern::IsInPasswordMode() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::VISIBLE_PASSWORD;
}

void TextFieldPattern::RestorePreInlineStates()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    layoutProperty->UpdateTextColor(inlineState_.textColor);
    layoutProperty->UpdatePadding(inlineState_.padding);
    ProcessInnerPadding();
    inlinePadding_ = 0.0f;
    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    textRect_.SetOffset(OffsetF((GetPaddingLeft() + (float)(currentBorderWidth.leftDimen->ConvertToPx())),
        (GetPaddingTop() + (float)currentBorderWidth.topDimen->ConvertToPx())));
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN) || IsNormalInlineState()) {
        textRect_.SetOffset(OffsetF(GetPaddingLeft(), GetPaddingTop()));
    }
    layoutProperty->UpdateMargin(inlineState_.margin);
    renderContext->UpdateBackgroundColor(inlineState_.bgColor);
    layoutProperty->UpdateBorderWidth(inlineState_.borderWidth);
    renderContext->UpdateBorderWidth(inlineState_.borderWidth);
    renderContext->UpdateBorderRadius(inlineState_.radius);
    if (inlineState_.hasBorderColor) {
        renderContext->UpdateBorderColor(inlineState_.borderColor);
    }
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    selectionMode_ = SelectionMode::NONE;
}

bool TextFieldPattern::IsNormalInlineState() const
{
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return paintProperty->GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE &&
           (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED ||
               layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::TEXT);
}

bool TextFieldPattern::IsUnspecifiedOrTextType() const
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto inputType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    return inputType == TextInputType::UNSPECIFIED || inputType == TextInputType::TEXT;
}

void TextFieldPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("placeholder", GetPlaceHolder().c_str());
    json->Put("text", contentController_->GetTextValue().c_str());
    json->Put("fontSize", GetFontSize().c_str());
    json->Put("fontColor", GetTextColor().c_str());
    json->Put("fontStyle", GetItalicFontStyle() == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic");
    json->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(GetFontWeight()).c_str());
    json->Put("fontFamily", GetFontFamily().c_str());
    json->Put("textAlign", V2::ConvertWrapTextAlignToString(GetTextAlign()).c_str());
    json->Put("caretColor", GetCaretColor().c_str());
    json->Put("type", TextInputTypeToString().c_str());
    json->Put("placeholderColor", GetPlaceholderColor().c_str());
    json->Put("placeholderFont", GetPlaceholderFont().c_str());
    json->Put("enterKeyType", TextInputActionToString().c_str());
    auto maxLength = GetMaxLength();
    json->Put("maxLength", GreatOrEqual(maxLength, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLength).c_str());
    json->Put("inputFilter", GetInputFilter().c_str());
    json->Put("copyOption", GetCopyOptionString().c_str());
    json->Put("style", GetInputStyleString().c_str());
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("onIconSrc", GetShowResultImageSrc().c_str());
    jsonValue->Put("offIconSrc", GetHideResultImageSrc().c_str());
    json->Put("passwordIcon", jsonValue->ToString().c_str());
    json->Put("showError", GetErrorTextState() ? GetErrorTextString().c_str() : "undefined");
    auto maxLines = GetMaxLines();
    json->Put("maxLines", GreatOrEqual(maxLines, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLines).c_str());
    json->Put("barState", GetBarStateString().c_str());
}

void TextFieldPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdatePlaceholder(json->GetString("placeholder"));
    UpdateEditingValue(json->GetString("text"), StringUtils::StringToInt(json->GetString("caretPosition")));
    FireOnTextChangeEvent();
    UpdateSelection(selectController_->GetCaretIndex());
    auto maxLines = json->GetString("maxLines");
    if (!maxLines.empty() && maxLines != "INF") {
        layoutProperty->UpdateMaxLines(StringUtils::StringToUint(maxLines));
    }
    static const std::unordered_map<std::string, CopyOptions> uMap = {
        { "CopyOptions.None", CopyOptions::None },
        { "CopyOptions.InApp", CopyOptions::InApp },
        { "CopyOptions.Local", CopyOptions::Local },
        { "CopyOptions.Distributed", CopyOptions::Distributed },
    };
    auto copyOption = json->GetString("copyOption");
    layoutProperty->UpdateCopyOptions(uMap.count(copyOption) ? uMap.at(copyOption) : CopyOptions::None);
    Pattern::FromJson(json);
}

void TextFieldPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSetText([weakPtr = WeakClaim(this)](const std::string& value) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->InsertValue(value);
    });

    accessibilityProperty->SetActionSetSelection([weakPtr = WeakClaim(this)](int32_t start, int32_t end) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelectionFlag(start, end);
    });

    accessibilityProperty->SetActionCopy([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->AllowCopy()) {
            pattern->HandleOnCopy();
            pattern->CloseSelectOverlay(true);
        }
    });

    accessibilityProperty->SetActionCut([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->AllowCopy()) {
            pattern->HandleOnCut();
            pattern->CloseSelectOverlay(true);
        }
    });

    accessibilityProperty->SetActionPaste([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnPaste();
        pattern->CloseSelectOverlay(true);
    });

    accessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto current = pattern->selectController_->GetEndIndex();
        pattern->SetInSelectMode(SelectionMode::NONE);
        pattern->UpdateSelection(current);
        pattern->SetSelectionFlag(current, current);
        pattern->CloseSelectOverlay(true);
        pattern->StartTwinkling();
    });
    SetAccessibilityScrollAction();
    SetAccessibilityMoveTextAction();
}

void TextFieldPattern::SetAccessibilityMoveTextAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionMoveText([weakPtr = WeakClaim(this)](int32_t moveUnit, bool forward) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        if (pattern->contentController_->IsEmpty()) {
            return;
        }
        int range = 0;
        if (moveUnit == 1) {
            range = 1;
        }
        auto caretPosition = forward ? pattern->selectController_->GetCaretIndex() + range
                                     : pattern->selectController_->GetCaretIndex() - range;
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        layoutProperty->UpdateCaretPosition(caretPosition);
        pattern->SetCaretPosition(caretPosition);
    });
}

void TextFieldPattern::SetAccessibilityScrollAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsScrollable()) {
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            auto offset = pattern->GetTextContentRect().Height();
            float scrollDistance =
                pattern->GetTextRect().Height() - (std::abs((pattern->GetTextRect().GetY() - offset)));
            if (offset > scrollDistance) {
                pattern->OnTextAreaScroll(-scrollDistance);
                frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
                return;
            }
            pattern->OnTextAreaScroll(-offset);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->IsScrollable()) {
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            auto offset = pattern->GetTextContentRect().Height();
            float scrollDistance = std::abs(pattern->GetTextRect().GetY() - pattern->GetTextContentRect().GetY());
            if (offset > scrollDistance) {
                pattern->OnTextAreaScroll(scrollDistance);
                frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
                return;
            }
            pattern->OnTextAreaScroll(offset);
            frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        }
    });
}

void TextFieldPattern::StopEditing()
{
    LOGI("TextFieldPattern: StopEditing");
    if (!HasFocus()) {
        return;
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (GetImeAttached() || isCustomKeyboardAttached_) {
#else
    if (isCustomKeyboardAttached_) {
#endif
        NotifyOnEditChanged(false);
    }
    UpdateSelection(selectController_->GetCaretIndex());
    StopTwinkling();
    CloseKeyboard(true);
}

bool TextFieldPattern::CheckHandleVisible(const RectF& paintRect)
{
    OffsetF offset(paintRect.GetX() - parentGlobalOffset_.GetX(), paintRect.GetY() - parentGlobalOffset_.GetY());
    return !(!contentRect_.IsInRegion({ offset.GetX(), offset.GetY() + paintRect.Height() - BOX_EPSILON }) ||
             !contentRect_.IsInRegion({ offset.GetX(), offset.GetY() + BOX_EPSILON }));
}

bool TextFieldPattern::CheckSelectionRectVisible()
{
    if (!IsSelected()) {
        return false;
    }
    std::vector<RectF> selectedRects;
    paragraph_->GetRectsForRange(selectController_->GetStartIndex(), selectController_->GetEndIndex(), selectedRects);
    if (selectedRects.empty()) {
        return false;
    }
    for (const auto& rect : selectedRects) {
        auto left = rect.Left();
        auto top = rect.Top();
        SizeF boxSize = { rect.Width(), rect.Height() };
        auto boxOffset = OffsetF(left + (IsTextArea() ? contentRect_.GetX() : textRect_.GetX()),
            top + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()) + BOX_EPSILON);
        if (contentRect_.IsIntersectWith(RectF(boxOffset, boxSize))) {
            return true;
        }
    }
    return false;
}

void TextFieldPattern::SetTextRectOffset()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (barState_.has_value() && barState_.value() != layoutProperty->GetDisplayModeValue(DisplayMode::AUTO)) {
        barState_ = layoutProperty->GetDisplayModeValue(DisplayMode::AUTO);
        textRect_.SetOffset(OffsetF(GetPaddingLeft(), lastTextRectY_));
    } else {
        textRect_.SetOffset(OffsetF(GetPaddingLeft(), GetPaddingTop()));
    }
}

void TextFieldPattern::DumpInfo()
{
    if (customKeyboardBulder_) {
        DumpLog::GetInstance().AddDesc(std::string("CustomKeyboard: true")
                                           .append(", Attached: ")
                                           .append(std::to_string(isCustomKeyboardAttached_)));
    }
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    DumpLog::GetInstance().AddDesc(std::string("cursorInfo")
                                       .append(", left:")
                                       .append(std::to_string(cursorInfo.left))
                                       .append(", top:")
                                       .append(std::to_string(cursorInfo.top))
                                       .append(", width:")
                                       .append(std::to_string(cursorInfo.width))
                                       .append(", height:")
                                       .append(std::to_string(cursorInfo.height)));
#endif
    DumpLog::GetInstance().AddDesc(std::string("textRect-->x:")
                                       .append(std::to_string(textRect_.GetX()))
                                       .append(" y:")
                                       .append(std::to_string(textRect_.GetY())));
    DumpLog::GetInstance().AddDesc(std::string("contentRect-->x:")
                                       .append(std::to_string(contentRect_.GetX()))
                                       .append(" y:")
                                       .append(std::to_string(contentRect_.GetY())));
    DumpLog::GetInstance().AddDesc(textSelector_.ToString());
}

bool TextFieldPattern::IsTouchAtLeftOffset(float currentOffsetX)
{
    return LessNotEqual(currentOffsetX, contentRect_.GetX() + contentRect_.Width() * 0.5);
}

OffsetF TextFieldPattern::GetDragUpperLeftCoordinates()
{
    if (!IsSelected()) {
        return { 0.0f, 0.0f };
    }
    auto selectRects = selectController_->GetSelectedRects();
    auto startY = selectRects.front().Top();
    auto startX = selectRects.front().Left();
    auto endY = selectRects.back().Top();
    OffsetF startOffset;
    if (NearEqual(startY, endY)) {
        startOffset = { (IsTextArea() ? contentRect_.GetX() : textRect_.GetX()) + startX,
            startY + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()) };
    } else {
        startOffset = { contentRect_.GetX(), startY + (IsTextArea() ? textRect_.GetY() : contentRect_.GetY()) };
    }

    if (startOffset.GetY() < contentRect_.GetY()) {
        startOffset.SetY(contentRect_.GetY());
    }
    if (startOffset.GetX() < contentRect_.GetX()) {
        startOffset.SetX(contentRect_.GetX());
    }
    return startOffset + parentGlobalOffset_;
}

void TextFieldPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateTextColor(theme->GetTextStyle().GetTextColor());
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::IsReachedBoundary(float offset)
{
    if (IsTextArea()) {
        return (NearEqual(textRect_.GetY(), contentRect_.GetY()) && GreatNotEqual(offset, 0.0f)) ||
               (NearEqual(textRect_.GetY() + textRect_.Height(), contentRect_.GetY() + contentRect_.Height()) &&
                   LessNotEqual(offset, 0.0f));
    }

    return (NearEqual(textRect_.GetX(), contentRect_.GetX()) && GreatNotEqual(offset, 0.0f)) ||
           (NearEqual(textRect_.GetX() + textRect_.Width(), contentRect_.GetX() + contentRect_.Width()) &&
               LessNotEqual(offset, 0.0f));
}

OffsetF TextFieldPattern::GetTextPaintOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0.0f, 0.0f));
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, OffsetF(0.0f, 0.0f));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = host->GetPaintRectOffset();
    return textPaintOffset - rootOffset;
}

void TextFieldPattern::UpdateSelectController()
{
    selectController_->UpdateContentRect(contentRect_);
    selectController_->UpdateParagraph(paragraph_);
}

bool TextFieldPattern::IsSingleHandle() const
{
    return contentController_->IsEmpty() || !IsSelected();
}

void TextFieldPattern::OnAttachToFrameNode()
{
    auto onTextSelectorChange = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_SELECTION_UPDATE);
    };
    selectController_->SetOnAccessibility(std::move(onTextSelectorChange));
}

bool TextFieldPattern::NeedPaintSelect()
{
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto firstHandle = paintProperty->GetFirstHandleInfo();
    auto secondHandle = paintProperty->GetSecondHandleInfo();
    if (!IsSelected()) {
        if (!firstHandle.has_value() || !secondHandle.has_value()) {
            paintProperty->UpdateFirstHandleInfo(selectController_->GetCaretInfo());
            paintProperty->UpdateSecondHandleInfo(selectController_->GetCaretInfo());
            return false;
        }

        if (firstHandle->index != secondHandle->index) {
            paintProperty->UpdateFirstHandleInfo(selectController_->GetCaretInfo());
            paintProperty->UpdateSecondHandleInfo(selectController_->GetCaretInfo());
            return true;
        }
    }
    auto needPaint = firstHandle != selectController_->GetFirstHandleInfo() ||
                     secondHandle != selectController_->GetSecondHandleInfo();
    paintProperty->UpdateFirstHandleInfo(selectController_->GetFirstHandleInfo());
    paintProperty->UpdateSecondHandleInfo(selectController_->GetSecondHandleInfo());
    return needPaint;
}

RefPtr<FocusHub> TextFieldPattern::GetFocusHub() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto focusHub = host->GetOrCreateFocusHub();
    return focusHub;
}

void TextFieldPattern::UpdateRecordCaretIndex(int32_t index)
{
    if (operationRecords_.empty()) {
        LOGW("Operation records empty, cannot update position");
        return;
    }
    operationRecords_.back().caretPosition = index;
}

void TextFieldPattern::OnObscuredChanged(bool isObscured)
{
    ResetObscureTickCountDown();
    textObscured_ = isObscured;
    CloseSelectOverlay(false);
    selectController_->UpdateCaretIndex(selectController_->GetCaretIndex());
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextFieldPattern::CreateHandles()
{
    ProcessOverlay(true, false, false);
}

void TextFieldPattern::NotifyOnEditChanged(bool isChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnEditChanged(isChanged);
}

int32_t TextFieldPattern::GetLineCount() const
{
    if (paragraph_) {
        return paragraph_->GetLineCount();
    }
    return 0;
}
} // namespace OHOS::Ace::NG
