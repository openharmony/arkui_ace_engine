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
#include <string>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
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
#include "core/common/recorder/node_data_cache.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
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
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"
#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
#endif
#endif
#include "core/common/udmf/udmf_client.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif
namespace OHOS::Ace::NG {
namespace {
// need to be moved to TextFieldTheme
constexpr Dimension BORDER_DEFAULT_WIDTH = 0.0_vp;
constexpr Dimension TYPING_UNDERLINE_WIDTH = 2.0_px;
constexpr Dimension ERROR_BORDER_WIDTH = 1.0_vp;
constexpr Dimension OVER_COUNT_BORDER_WIDTH = 1.0_vp;
constexpr Dimension INLINE_BORDER_WIDTH = 2.0_vp;
constexpr Dimension ERROR_UNDERLINE_WIDTH = 2.0_px;
constexpr Dimension UNDERLINE_WIDTH = 1.0_px;
constexpr Dimension UNDERLINE_NORMAL_HEIGHT = 48.0_vp;
constexpr uint32_t INLINE_DEFAULT_VIEW_MAXLINE = 3;
constexpr Dimension UNDERLINE_NORMAL_PADDING = 12.0_vp;
constexpr Dimension SCROLL_BAR_MIN_HEIGHT = 4.0_vp;
constexpr Dimension DEFAULT_FONT = Dimension(16, DimensionUnit::FP);
constexpr Dimension COUNTER_BOTTOM = 22.0_vp;
constexpr double BOTTOM_MARGIN = 22.0;
constexpr int32_t ONE_CHARACTER = 1;
constexpr int32_t ILLEGAL_VALUE = 0;
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.5f;
constexpr float DOUBLECLICK_INTERVAL_MS = 300.0f;
constexpr float DOUBLECLICK_MIN_INTERVAL_MS = 0.0f;
constexpr double VELOCITY = -1000;
constexpr double MASS = 1.0;
constexpr double STIFFNESS = 428.0;
constexpr double DAMPING = 10.0;
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr uint32_t OBSCURE_SHOW_TICKS = 3;
constexpr Dimension ERROR_TEXT_TOP_MARGIN = 8.0_vp;
constexpr Dimension ERROR_TEXT_BOTTOM_MARGIN = 8.0_vp;
constexpr uint32_t FIND_TEXT_ZERO_INDEX = 1;
constexpr char16_t OBSCURING_CHARACTER = u'•';
constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*';
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
constexpr int32_t AUTO_FILL_FAILED = 1;

// need to be moved to formatter
const std::string DIGIT_WHITE_LIST = "[0-9]";
const std::string PHONE_WHITE_LIST = "[\\d\\-\\+\\*\\#]+";
const std::string EMAIL_WHITE_LIST = "[\\w.\\@]";
const std::string URL_WHITE_LIST = "[a-zA-z]+://[^\\s]*";
const std::string SHOW_PASSWORD_SVG = "SYS_SHOW_PASSWORD_SVG";
const std::string HIDE_PASSWORD_SVG = "SYS_HIDE_PASSWORD_SVG";
constexpr int32_t DEFAULT_MODE = -1;

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

RefPtr<NodePaintMethod> TextFieldPattern::CreateNodePaintMethod()
{
    if (!textFieldContentModifier_) {
        textFieldContentModifier_ = AceType::MakeRefPtr<TextFieldContentModifier>(WeakClaim(this));
    }
    auto textFieldOverlayModifier = AceType::DynamicCast<TextFieldOverlayModifier>(GetScrollBarOverlayModifier());
    if (!textFieldOverlayModifier) {
        textFieldOverlayModifier =
            AceType::MakeRefPtr<TextFieldOverlayModifier>(WeakClaim(this), GetScrollEdgeEffect());
        SetScrollBarOverlayModifier(textFieldOverlayModifier);
    }
    if (isCustomFont_) {
        textFieldContentModifier_->SetIsCustomFont(true);
    }
    auto paint = MakeRefPtr<TextFieldPaintMethod>(WeakClaim(this), textFieldOverlayModifier, textFieldContentModifier_);
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        paint->SetScrollBar(scrollBar);
        if (scrollBar->NeedPaint()) {
            textFieldOverlayModifier->SetRect(scrollBar->GetActiveRect());
        } else if (IsNormalInlineState() && !HasFocus()) {
            auto inlineScrollRect = scrollBar->GetActiveRect();
            CalcInlineScrollRect(inlineScrollRect);
            textFieldOverlayModifier->SetRect(inlineScrollRect);
            textFieldOverlayModifier->SetOpacity(0);
        }
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, paint);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, paint);
    auto geometryNode = host->GetGeometryNode();
    auto frameOffset = geometryNode->GetFrameOffset();
    auto frameSize = geometryNode->GetFrameSize();
    if (layoutProperty->GetShowErrorTextValue(false) && errorParagraph_) {
        auto contentOffset = geometryNode->GetContentOffset();
        auto errorTextWidth = errorParagraph_->GetLongestLine();
        RectF boundsRect(contentOffset.GetX(), frameOffset.GetY(), errorTextWidth, errorParagraph_->GetHeight() +
            ERROR_TEXT_TOP_MARGIN.ConvertToPx() + ERROR_TEXT_BOTTOM_MARGIN.ConvertToPx() + frameSize.Height());
        textFieldOverlayModifier->SetBoundsRect(boundsRect);
    } else {
        if (NearEqual(maxFrameOffsetY_, 0.0f) && NearEqual(maxFrameHeight_, 0.0f)) {
            maxFrameOffsetY_ = frameOffset.GetY();
            maxFrameHeight_ = frameSize.Height();
        }
        maxFrameOffsetY_ = LessOrEqual(frameOffset.GetY(), maxFrameOffsetY_) ? frameOffset.GetY()
                                                                             : maxFrameOffsetY_ - frameOffset.GetY();
        maxFrameHeight_ = LessOrEqual(frameSize.Height(), maxFrameHeight_) ? maxFrameHeight_ : frameSize.Height();
        RectF boundsRect(frameOffset.GetX(), maxFrameOffsetY_, frameSize.Width(), maxFrameHeight_);
        textFieldOverlayModifier->SetBoundsRect(boundsRect);
    }
    return paint;
}

void TextFieldPattern::CalcInlineScrollRect(Rect& inlineScrollRect)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBar = GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    Size size(frameRect_.Width(), inlineMeasureItem_.inlineSizeHeight);
    auto positionMode_ = scrollBar->GetPositionMode();
    double mainSize = (positionMode_ == PositionMode::BOTTOM ? size.Width() : size.Height());
    auto barRegionSize_ = mainSize;
    double estimatedHeight = inlineMeasureItem_.inlineContentRectHeight;
    double activeSize = barRegionSize_ * mainSize / estimatedHeight - scrollBar->GetOutBoundary();
    auto offsetScale_ = 0.0f;
    if (NearEqual(mainSize, estimatedHeight)) {
        offsetScale_ = 0.0;
    } else {
        offsetScale_ = (barRegionSize_ - activeSize) / (estimatedHeight - mainSize);
    }
    double lastMainOffset = std::max(static_cast<double>(
        std::max(inlineMeasureItem_.inlineLastOffsetY, contentRect_.GetY() - textRect_.GetY())), 0.0);
    double activeMainOffset = std::min(offsetScale_ * lastMainOffset, barRegionSize_ - activeSize);
    inlineScrollRect.SetLeft(inlineScrollRect.GetOffset().GetX() - inlineMeasureItem_.inlineScrollRectOffsetX);
    inlineScrollRect.SetTop(activeMainOffset);
    inlineScrollRect.SetHeight(activeSize);
}

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
    auto textFieldLayoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    auto textFieldTheme = GetTheme();
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
        PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9) {
        needToRequestKeyboardOnFocus_ = true;
    }
    contentController_ = MakeRefPtr<ContentController>(WeakClaim(this));
    selectController_ = MakeRefPtr<TextSelectController>(WeakClaim(this));
    selectController_->InitContentController(contentController_);
    magnifierController_ = MakeRefPtr<MagnifierController>(WeakClaim(this));
}

TextFieldPattern::~TextFieldPattern()
{
    if (textEditingController_) {
        textEditingController_->Clear();
        textEditingController_->RemoveObserver(WeakClaim(this));
    }
    CloseSelectOverlay();
}

void TextFieldPattern::BeforeCreateLayoutWrapper()
{
    while (!inputOperations_.empty()) {
        auto operation = inputOperations_.front();
        inputOperations_.pop();
        switch (operation) {
            case InputOperation::INSERT: {
                InsertValueOperation(insertValueOperations_.front());
                insertValueOperations_.pop();
                break;
            }
            case InputOperation::DELETE_BACKWARD: {
                DeleteBackwardOperation(deleteBackwardOperations_.front());
                deleteBackwardOperations_.pop();
                break;
            }
            case InputOperation::DELETE_FORWARD: {
                DeleteForwardOperation(deleteForwardOperations_.front());
                deleteForwardOperations_.pop();
                break;
            }
            case InputOperation::CURSOR_UP: {
                CursorMoveUpOperation();
                break;
            }
            case InputOperation::CURSOR_DOWN: {
                CursorMoveDownOperation();
                break;
            }
            case InputOperation::CURSOR_LEFT: {
                CursorMoveLeftOperation();
                break;
            }
            case InputOperation::CURSOR_RIGHT: {
                CursorMoveRightOperation();
                break;
            }
        }
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
        paragraphWidth = std::max(paragraph->GetLongestLine(), 0.0f);
    }
    if (!IsDragging()) {
        dragParagraph_ = paragraph_;
    }
    auto textRect = textFieldLayoutAlgorithm->GetTextRect();
    if (!(needToRefreshSelectOverlay_ &&
            (!NearEqual(paragraphWidth, paragraphWidth_) || !NearEqual(textRect.GetSize(), textRect_.GetSize())))) {
        needToRefreshSelectOverlay_ = false;
    }
    paragraphWidth_ = paragraphWidth;
    textRect_ = textRect;

    parentGlobalOffset_ = textFieldLayoutAlgorithm->GetParentGlobalOffset();
    inlineMeasureItem_ = textFieldLayoutAlgorithm->GetInlineMeasureItem();
    auto isEditorValueChanged = FireOnTextChangeEvent();
    UpdateCancelNode();
    UpdateSelectController();
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    AdjustTextInReasonableArea();
    UpdateCaretRect(isEditorValueChanged);
    UpdateCaretInfoToController();
    auto hostLayoutProperty =
        dirty->GetHostNode() ? dirty->GetHostNode()->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
    if (hostLayoutProperty) {
        hostLayoutProperty->ResetTextAlignChanged();
    }
    if (processOverlayDelayTask_) {
        processOverlayDelayTask_();
        processOverlayDelayTask_ = nullptr;
    }
    if (needToRefreshSelectOverlay_) {
        StopTwinkling();
        ProcessOverlay();
        needToRefreshSelectOverlay_ = false;
    }
    if (inlineSelectAllFlag_) {
        HandleOnSelectAll(false, true);
        inlineSelectAllFlag_ = false;
        showSelect_ = true;
    }
    if (needSelectAll_ && !isLongPress_) {
        HandleOnSelectAll(true);
        needSelectAll_ = false;
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

void TextFieldPattern::UpdateCaretInfoToController() const
{
    CHECK_NULL_VOID(HasFocus());
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        StringUtils::Str8ToStr16(contentController_->GetTextValue()), selectController_->GetStartIndex(),
        selectController_->GetEndIndex());
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "Caret position update, left %{public}f, top %{public}f, width %{public}f, height %{public}f; "
        "selectController_ Start "
        "%{public}d, end %{public}d",
        cursorInfo.left, cursorInfo.top, cursorInfo.width, cursorInfo.height, selectController_->GetStartIndex(),
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
void TextFieldPattern::UpdateCaretRect(bool isEditorValueChanged)
{
    auto focusHub = GetFocusHub();
    if (IsSelected()) {
        selectController_->MoveFirstHandleToContentRect(selectController_->GetFirstHandleIndex());
        selectController_->MoveSecondHandleToContentRect(selectController_->GetSecondHandleIndex());
        return;
    }
    if (focusHub && !focusHub->IsCurrentFocus() && !obscuredChange_) {
        CloseSelectOverlay(true);
        return;
    }
    selectController_->MoveCaretToContentRect(
        selectController_->GetCaretIndex(), TextAffinity::DOWNSTREAM, isEditorValueChanged);
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
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, false);
    return GreatOrEqual(selectController_->GetCaretRect().GetX(), contentRect_.GetX()) &&
           LessOrEqual(selectController_->GetCaretRect().GetX() + theme->GetCursorWidth().ConvertToPx(),
               contentRect_.GetX() + contentRect_.Width());
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
    OnParentScrollStartOrEnd(true);
}

void TextFieldPattern::OnTextAreaScroll(float offset)
{
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
    UpdateHandlesOffsetOnScroll(offset);
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
    UpdateHandlesOffsetOnScroll(offset);
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
    isFocusedBeforeClick_ = true;
    focusIndex_ = FocuseIndex::TEXT;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextField %{public}d on focus", host->GetId());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto globalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
    needToRequestKeyboardInner_ = !isLongPress_ && (dragRecipientStatus_!= DragStatus::DRAGGING);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isSelectAll = layoutProperty->GetSelectAllValueValue(false);
    if (isSelectAll && !contentController_->IsEmpty()) {
        needSelectAll_ = true;
    }
    if (IsNormalInlineState()) {
        ApplyInlineStates(true);
        inlineFocusState_ = true;
        if (contentController_->IsEmpty()) {
            StartTwinkling();
        } else {
            inlineSelectAllFlag_ = true;
        }
    } else {
        StartTwinkling();
    }
    NotifyOnEditChanged(true);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    if (!visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType() &&
        !IsNormalInlineState()) {
        auto renderContext = host->GetRenderContext();
        auto textFieldTheme = GetTheme();
        CHECK_NULL_VOID(textFieldTheme);
        auto radius = textFieldTheme->GetBorderRadiusSize();
        underlineColor_ = textFieldTheme->GetUnderlineTypingColor();
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
        renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
    }
    selectController_->FireSelectEvent();
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::HandleSetSelection(int32_t start, int32_t end, bool showHandle)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleSetSelection %{public}d, %{public}d", start, end);
    StopTwinkling();
    UpdateSelection(start, end);
    if (showHandle) {
        ProcessOverlay();
    } else {
        CloseSelectOverlay();
    }
    UpdateCaretInfoToController();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleExtendAction(int32_t action)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleExtendAction %{public}d", action);
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

void TextFieldPattern::CursorMove(CaretMoveIntent direction)
{
    switch (direction) {
        case CaretMoveIntent::Left: {
            CursorMoveLeft();
            break;
        }
        case CaretMoveIntent::Right: {
            CursorMoveRight();
            break;
        }
        case CaretMoveIntent::Up: {
            CursorMoveUp();
            break;
        }
        case CaretMoveIntent::Down: {
            CursorMoveDown();
            break;
        }
        case CaretMoveIntent::LineBegin: {
            CursorMoveLineBegin();
            break;
        }
        case CaretMoveIntent::LineEnd: {
            CursorMoveLineEnd();
            break;
        }
        case CaretMoveIntent::LeftWord: {
            CursorMoveLeftWord();
            break;
        }
        case CaretMoveIntent::RightWord: {
            CursorMoveRightWord();
            break;
        }
        case CaretMoveIntent::ParagraghBegin: {
            CursorMoveToParagraphBegin();
            break;
        }
        case CaretMoveIntent::ParagraghEnd: {
            CursorMoveToParagraphEnd();
            break;
        }
        case CaretMoveIntent::Home: {
            CursorMoveHome();
            break;
        }
        case CaretMoveIntent::End: {
            CursorMoveEnd();
            break;
        }
    }
}

void TextFieldPattern::HandleSelect(CaretMoveIntent direction)
{
    CloseSelectOverlay();
    switch (direction) {
        case CaretMoveIntent::Left: {
            HandleSelectionLeft();
            break;
        }
        case CaretMoveIntent::Right: {
            HandleSelectionRight();
            break;
        }
        case CaretMoveIntent::Up: {
            HandleSelectionUp();
            break;
        }
        case CaretMoveIntent::Down: {
            HandleSelectionDown();
            break;
        }
        case CaretMoveIntent::LineBegin: {
            HandleSelectionLineBegin();
            break;
        }
        case CaretMoveIntent::LineEnd: {
            HandleSelectionLineEnd();
            break;
        }
        case CaretMoveIntent::LeftWord: {
            HandleSelectionLeftWord();
            break;
        }
        case CaretMoveIntent::RightWord: {
            HandleSelectionRightWord();
            break;
        }
        case CaretMoveIntent::Home: {
            HandleSelectionHome();
            break;
        }
        case CaretMoveIntent::End: {
            HandleSelectionEnd();
            break;
        }
        // SelectionParagraghBegin/SelectionParagraghEnd not supported yet
        default: {
            LOGW("Unsupported select operation for text field");
        }
    }
}

void TextFieldPattern::InitDisableColor()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        underlineWidth_ = UNDERLINE_WIDTH;
        underlineColor_ = IsDisabled() ? theme->GetDisableUnderlineColor() : theme->GetUnderlineColor();
        SaveUnderlineStates();
    }
    layoutProperty->UpdateIsDisabled(IsDisabled());
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

    auto getInnerPaintRectCallback = [weak = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
    auto windowFocusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->HasFocus()) {
            pattern->HandleBlurEvent();
        }
    };
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->SetOnWindowFocused(windowFocusTask);
    focusEventInitialized_ = true;
}

bool TextFieldPattern::CheckBlurReason()
{
    auto curFocusHub = GetFocusHub();
    CHECK_NULL_RETURN(curFocusHub, false);
    auto curBlurReason = curFocusHub->GetBlurReason();
    if (curBlurReason == BlurReason::FRAME_DESTROY) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TextFieldPattern CheckBlurReason, Close Keyboard.");
        return true;
    }
    return false;
}

void TextFieldPattern::HandleBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextField %{public}d OnBlur", host->GetId());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    if (!context->GetOnFoucs()) {
        return;
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField();
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldTheme = GetTheme();
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
            layoutProperty->UpdatePlaceholderMaxLines(1);
        }
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
    }
    needToRequestKeyboardInner_ = false;
    isLongPress_ = false;
    isFocusedBeforeClick_ = false;
    UpdateShowMagnifier();
    CloseSelectOverlay(true);
    StopTwinkling();
    if ((customKeyboardBuilder_ && isCustomKeyboardAttached_)) {
        CloseKeyboard(true);
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TextFieldPattern Blur, Close Keyboard.");
    }
    selectController_->UpdateCaretIndex(selectController_->GetCaretIndex());
    NotifyOnEditChanged(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_TAB && isFocusedBeforeClick_ && !contentController_->IsEmpty()) {
        isFocusedBeforeClick_ = false;
        HandleOnSelectAll(true);
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (event.code == KeyCode::KEY_TAB && HasFocus() && !needToRequestKeyboardOnFocus_ && needToRequestKeyboardInner_ &&
        textFieldManager->GetImeShow()) {
        RequestKeyboard(false, true, true);
    }
    return TextInputClient::HandleKeyEvent(event);
}

bool TextFieldPattern::HandleOnEscape()
{
    CloseSelectOverlay(true);
    return false;
}

bool TextFieldPattern::HandleOnTab(bool backward)
{
    return backward ? UpdateFocusBackward() : UpdateFocusForward();
}

void TextFieldPattern::HandleOnUndoAction()
{
    if (operationRecords_.empty()) {
        return;
    }
    auto value = operationRecords_.back();
    operationRecords_.pop_back();
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    redoOperationRecords_.push_back(value);
    if (operationRecords_.empty()) {
        FireEventHubOnChange("");
        ClearEditingValue();
        return;
    }
    auto textEditingValue = operationRecords_.back(); // record应该包含光标、select状态、文本
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->MoveCaretToContentRect(textEditingValue.caretPosition, TextAffinity::DOWNSTREAM);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleOnRedoAction()
{
    if (redoOperationRecords_.empty()) {
        return;
    }
    auto textEditingValue = redoOperationRecords_.back();
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->UpdateCaretIndex(textEditingValue.caretPosition);
    redoOperationRecords_.pop_back();
    operationRecords_.push_back(textEditingValue);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleOnSelectAll(bool isKeyEvent, bool inlineStyle)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextFieldPattern::HandleOnSelectAll");
    }
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
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    selectController_->MoveSecondHandleToContentRect(textSize);
    StopTwinkling();
    showSelect_ = true;
    if (isKeyEvent || inlineSelectAllFlag_) {
        CloseSelectOverlay(true);
        return;
    }
    ProcessOverlay(true, true);
}

void TextFieldPattern::HandleOnCopy()
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextFieldPattern::HandleOnCopy");
    }
    CHECK_NULL_VOID(clipboard_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        return;
    }
    if (!IsSelected()) {
        return;
    }
    if (IsInPasswordMode()) {
        UpdateSelection(selectController_->GetEndIndex());
        StartTwinkling();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On copy, text selector %{public}s", selectController_->ToString().c_str());
    auto value =
        contentController_->GetSelectedValue(selectController_->GetStartIndex(), selectController_->GetEndIndex());
    if (value.empty()) {
        return;
    }
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        clipboard_->SetData(value, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
    }

    if (!IsUsingMouse()) {
        selectController_->MoveCaretToContentRect(selectController_->GetSecondHandleIndex(), TextAffinity::UPSTREAM);
        StartTwinkling();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(value);
}

void TextFieldPattern::HandleOnPaste()
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextFieldPattern::HandleOnPaste");
    }
    auto pasteCallback = [weak = WeakClaim(this)](const std::string& data) {
        if (data.empty()) {
            return;
        }
        auto textfield = weak.Upgrade();
        auto host = textfield->GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        TextCommonEvent event;
        eventHub->FireOnPasteWithEvent(data, event);
        if (event.IsPreventDefault()) {
            textfield->CloseSelectOverlay(true);
            textfield->selectController_->ResetHandles();
            textfield->StartTwinkling();
            return;
        }

        CHECK_NULL_VOID(textfield);
        auto tmpHost = textfield->GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        int32_t start = 0;
        int32_t end = 0;
        if (textfield->IsSelected()) {
            start = textfield->selectController_->GetStartIndex();
            end = textfield->selectController_->GetEndIndex();
        } else {
            start = textfield->selectController_->GetCaretIndex();
            end = textfield->selectController_->GetCaretIndex();
        }
        std::wstring pasteData = StringUtils::ToWstring(data);
        textfield->StripNextLine(pasteData);
        auto originLength = static_cast<int32_t>(textfield->contentController_->GetWideText().length());
        textfield->contentController_->ReplaceSelectedValue(start, end, StringUtils::ToString(pasteData));
        auto caretMoveLength =
            static_cast<int32_t>(textfield->contentController_->GetWideText().length()) - originLength;
        auto newCaretPosition = std::clamp(std::max(start, end) + caretMoveLength, 0,
            static_cast<int32_t>(textfield->contentController_->GetWideText().length()));
        textfield->ResetObscureTickCountDown();
        textfield->selectController_->UpdateCaretIndex(newCaretPosition);
        textfield->UpdateEditingValueToRecord();
        if (textfield->IsTextArea() && layoutProperty->HasMaxLength()) {
            textfield->HandleCounterBorder();
        }
        auto maxlength = textfield->GetMaxLength();
        textfield->HandleInputCounterBorder(caretMoveLength, maxlength);
        textfield->CloseSelectOverlay(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        textfield->StartTwinkling();
    };
    CHECK_NULL_VOID(clipboard_);
    clipboard_->GetData(pasteCallback);
}

void TextFieldPattern::HandleOnCameraInput()
{
#if defined(ENABLE_STANDARD_INPUT)
    if (textChangeListener_ == nullptr) {
        textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (!inputMethod) {
        return;
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (imeShown_) {
        inputMethod->StartInputType(MiscServices::InputType::CAMERA_INPUT);
    } else {
        auto optionalTextConfig = GetMiscTextConfig();
        CHECK_NULL_VOID(optionalTextConfig.has_value());
        MiscServices::TextConfig textConfig = optionalTextConfig.value();
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnCameraInput set calling window id is : %{public}u",
            textConfig.windowId);
#ifdef WINDOW_SCENE_SUPPORTED
        auto systemWindowId = GetSCBSystemWindowId();
        if (systemWindowId) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "windowId From %{public}u to %{public}u.", textConfig.windowId,
                systemWindowId);
            textConfig.windowId = systemWindowId;
        }
#endif
        inputMethod->Attach(textChangeListener_, false, textConfig);
        inputMethod->StartInputType(MiscServices::InputType::CAMERA_INPUT);
        inputMethod->ShowTextInput();
    }
#endif
#endif
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
#if !defined(PREVIEW)
    CHECK_NULL_VOID(clipboard_);
#endif
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        return;
    }
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    SwapIfLarger(start, end);
    if (!IsSelected()) {
        return;
    }
    if (IsInPasswordMode()) {
        UpdateSelection(selectController_->GetEndIndex());
        StartTwinkling();
        return;
    }
    auto selectedText = contentController_->GetSelectedValue(start, end);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Cut value is %{private}s", selectedText.c_str());
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
    auto textFieldTheme = GetTheme();
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
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType == TouchType::UP) {
        RequestKeyboardAfterLongPress();
    }
    if (SelectOverlayIsOn() && !isTouchCaret_) {
        return;
    }

    if (touchType == TouchType::DOWN) {
        HandleTouchDown(info.GetTouches().front().GetLocalLocation());
    } else if (touchType == TouchType::UP) {
        HandleTouchUp();
    } else if (touchType == TouchType::MOVE) {
        if (!isUsingMouse_) {
            HandleTouchMove(info);
        }
    }
}

void TextFieldPattern::HandleTouchDown(const Offset& offset)
{
    if (HasStateStyle(UI_STATE_PRESSED)) {
        return;
    }
    if (enableTouchAndHoverEffect_ && !isMousePressed_) {
        auto lastCaretIndex = selectController_->GetCaretIndex();
        auto lastCaretRect = selectController_->GetCaretRect();
        isTouchCaret_ = RepeatClickCaret(offset, lastCaretIndex, lastCaretRect);
        auto textfieldPaintProperty = GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(textfieldPaintProperty);
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto renderContext = tmpHost->GetRenderContext();
        auto textFieldTheme = GetTheme();
        CHECK_NULL_VOID(textFieldTheme);
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType() && !IsNormalInlineState()) {
            auto radius = textFieldTheme->GetBorderRadiusSize();
            renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
        }
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::HandleTouchUp()
{
    if (isTouchCaret_) {
        isTouchCaret_ = false;
        CloseSelectOverlay(true);
        CheckScrollable();
    }
    if (isMousePressed_) {
        isMousePressed_ = false;
    }
    if (GetShowMagnifier()) {
        UpdateShowMagnifier();
    }
    if (enableTouchAndHoverEffect_ && !HasStateStyle(UI_STATE_PRESSED)) {
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto renderContext = tmpHost->GetRenderContext();
        if (!isOnHover_) {
            auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType() && !IsNormalInlineState()) {
                renderContext->UpdateBorderRadius(borderRadius_);
            }
            if (layoutProperty->GetShowUnderlineValue(false) && HasFocus() && IsUnspecifiedOrTextType() &&
                !IsNormalInlineState()) {
                auto textFieldTheme = GetTheme();
                CHECK_NULL_VOID(textFieldTheme);
                auto radius = textFieldTheme->GetBorderRadiusSize();
                renderContext->UpdateBorderRadius({ radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX() });
            }
        }
    }
}

void TextFieldPattern::HandleTouchMove(const TouchEventInfo& info)
{
    if (isTouchCaret_) {
        UpdateCaretByTouchMove(info);
    }
}

void TextFieldPattern::UpdateCaretByTouchMove(const TouchEventInfo& info)
{
    scrollable_ = false;
    SetScrollEnable(scrollable_);
    selectController_->UpdateCaretInfoByOffset(info.GetTouches().front().GetLocalLocation());
    ProcessOverlay(false, true, false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::InitDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!IsInPasswordMode() && layoutProperty->GetCopyOptionsValue(CopyOptions::Local) != CopyOptions::None &&
        host->IsDraggable()) {
        InitDragDropEvent();
        AddDragFrameNodeToManager(host);
        auto gestureEventHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureEventHub);
        gestureEventHub->SetTextDraggable(true);
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
        auto hub = host->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(hub, itemInfo);
        auto gestureHub = hub->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, itemInfo);
        if (!gestureHub->GetIsTextDraggable()) {
            return itemInfo;
        }
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, itemInfo);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        if (pattern->SelectOverlayIsOn() || pattern->imeAttached_ || pattern->showSelect_) {
            pattern->CloseHandleAndSelect();
            pattern->CloseKeyboard(true);
        }
#endif
        pattern->dragStatus_ = DragStatus::DRAGGING;
        pattern->showSelect_ = false;
        pattern->selectionMode_ = SelectionMode::SELECT;
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
    return [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (layoutProperty->GetIsDisabledValue(false) || pattern->IsNormalInlineState()) {
            return;
        }
        if (extraParams.empty()) {
            pattern->dragStatus_ = DragStatus::ON_DROP;
            pattern->textFieldContentModifier_->ChangeDragStatus();
            host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                         : PROPERTY_UPDATE_MEASURE);
            return;
        }
        auto data = event->GetData();
        CHECK_NULL_VOID(data);
        auto records = UdmfClient::GetInstance()->GetPlainTextRecords(data);
        std::string str;
        if (records.empty()) {
            std::string linkUrl;
            std::string linkTitle;
            UdmfClient::GetInstance()->GetLinkRecord(data, linkUrl, linkTitle);
            if (!linkTitle.empty()) {
                str += linkTitle;
            } else if (!linkUrl.empty()) {
                str += linkUrl;
            }
        }
        for (const auto& record : records) {
            str += record;
        }
        pattern->needToRequestKeyboardInner_ = pattern->dragStatus_ == DragStatus::NONE;
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
            pattern->selectController_->UpdateHandleIndex(dragTextStart, dragTextEnd);
            pattern->showSelect_ = true;
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
}

void TextFieldPattern::InitDragDropEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    auto callback = GetThumbnailCallback();
    gestureHub->SetThumbnailCallback(std::move(callback));
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnDragStart()) {
        eventHub->SetOnDragStart(OnDragStart());
    } else if (gestureHub->GetTextDraggable()) {
        gestureHub->SetTextDraggable(false);
    }

    auto onDragEnter = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->showSelect_ = false;
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
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        auto touchX = event->GetX();
        auto touchY = event->GetY();
        Offset offset = Offset(touchX, touchY) - Offset(pattern->textRect_.GetX(), pattern->textRect_.GetY()) -
                        Offset(pattern->parentGlobalOffset_.GetX(), pattern->parentGlobalOffset_.GetY()) -
                        Offset(0, theme->GetInsertCursorOffset().ConvertToPx());
        auto position = pattern->ConvertTouchOffsetToCaretPosition(offset);
        pattern->SetCaretPosition(position);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
    };
    eventHub->SetOnDragMove(std::move(onDragMove));

    auto onDragLeave = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->showSelect_ = false;
        pattern->dragRecipientStatus_ = DragStatus::NONE;
    };
    eventHub->SetOnDragLeave(std::move(onDragLeave));

    auto onDragEnd = [weakPtr = WeakClaim(this), id = Container::CurrentId()](
                         const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(id);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->dragStatus_ == DragStatus::DRAGGING) {
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);

            // Except for DRAG_SUCCESS, all of rest need to show
            if (event != nullptr && event->GetResult() != DragRet::DRAG_SUCCESS) {
                auto dragTextStart = pattern->dragTextStart_;
                auto dragTextEnd = pattern->dragTextEnd_;
                pattern->selectController_->UpdateHandleIndex(dragTextStart, dragTextEnd);
                pattern->showSelect_ = true;
                pattern->ProcessOverlay(false, false, false, false);
            }
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
    gestureHub->SetIsTextDraggable(false);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(nullptr);
    eventHub->SetOnDragEnter(nullptr);
    eventHub->SetOnDragMove(nullptr);
    eventHub->SetOnDragLeave(nullptr);
    eventHub->SetOnDragEnd(nullptr);
    eventHub->SetOnDrop(nullptr);
}

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
    auto focusHub = GetFocusHub();
    if (!focusHub->IsFocusable()) {
        return;
    }
    if (!HasFocus()) {
        if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
            CloseSelectOverlay(true);
            StopTwinkling();
            return;
        }
    }

    isUsingMouse_ = info.GetSourceDevice() == SourceType::MOUSE;
    if (CheckClickLocation(info)) {
        HandleDoubleClickEvent(info); // 注册手势事件
    } else {
        HandleSingleClickEvent(info);
    }
    if (ResetObscureTickCountDown()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    isFocusedBeforeClick_ = false;
}

bool TextFieldPattern::CheckClickLocation(GestureEvent& info)
{
    TimeStamp clickTimeStamp = info.GetTimeStamp();
    std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout = clickTimeStamp - lastClickTimeStamp_;
    lastClickTimeStamp_ = info.GetTimeStamp();

    Offset location = info.GetLocalLocation();
    auto range = selectController_->GetSelectRangeByOffset(location);
    int32_t start = range.first;
    int32_t end = range.second;

    auto last_range = selectController_->GetSelectRangeByOffset(clickLocation_);
    int32_t last_start = last_range.first;
    int32_t last_end = last_range.second;
    clickLocation_ = location;

    return timeout.count() >= DOUBLECLICK_MIN_INTERVAL_MS && timeout.count() < DOUBLECLICK_INTERVAL_MS &&
           start == last_start && end == last_end;
}

void TextFieldPattern::HandleSingleClickEvent(GestureEvent& info)
{
    if (mouseStatus_ != MouseStatus::NONE && IsNormalInlineState()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    auto lastCaretIndex = selectController_->GetCaretIndex();
    auto lastCaretRect = selectController_->GetCaretRect();
    if (mouseStatus_ != MouseStatus::MOVE) {
        selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation());
    }
    StartTwinkling();
    SetIsSingleHandle(true);
    CloseSelectOverlay(true);

    if (RepeatClickCaret(info.GetLocalLocation(), lastCaretIndex, lastCaretRect) &&
        info.GetSourceDevice() != SourceType::MOUSE) {
        if (contentController_->IsEmpty()) {
            ProcessOverlay(true, true, true, true);
        } else {
            ProcessOverlay(true, true);
        }
    } else if (!contentController_->IsEmpty() && info.GetSourceDevice() != SourceType::MOUSE &&
               !IsNormalInlineState()) {
        if (GetNakedCharPosition() >= 0) {
            DelayProcessOverlay(true, true, false);
        } else if (needSelectAll_) {
            HandleOnSelectAll(true);
        } else {
            ProcessOverlay(true, true, false);
        }
    }
    auto hasRequestAutoFill = ProcessAutoFill();
    if (!hasRequestAutoFill && RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
    // emulate clicking bottom of the textField
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::CheckAutoFill()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    bool isEnableAutoFill = layoutProperty->GetEnableAutoFillValue(true);
    if (!isEnableAutoFill) {
        return false;
    }
    auto pageNode = host->GetPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    auto autoFillType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    if (autoFillType == TextInputType::USER_NAME || autoFillType == TextInputType::VISIBLE_PASSWORD) {
        return !pagePattern->IsAutoFillPasswordTriggered();
    } else if (autoFillType == TextInputType::NEW_PASSWORD) {
        return !pagePattern->IsAutoFillNewPasswordTriggered();
    }
    return false;
}

bool TextFieldPattern::ProcessAutoFill()
{
    if (!CheckAutoFill()) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "No nedd to auto fill.");
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pageNode = host->GetPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto autoFillType = ConvertToAceAutoFillType(layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    if (autoFillType == AceAutoFillType::ACE_NEW_PASSWORD) {
        pagePattern->SetAutoFillNewPasswordTriggered(true);
    } else {
        pagePattern->SetAutoFillPasswordTriggered(true);
    }
    return container->RequestAutoFill(host, autoFillType);
}

void TextFieldPattern::HandleDoubleClickEvent(GestureEvent& info)
{
    if (showSelect_) {
        SetIsSingleHandle(true);
        CloseSelectOverlay();
    }
    selectController_->UpdateSelectByOffset(info.GetLocalLocation());
    if (IsSelected()) {
        StopTwinkling();
        SetIsSingleHandle(false);
    }
    if (info.GetSourceDevice() != SourceType::MOUSE && !contentController_->IsEmpty()) {
        ProcessOverlay(true, true);
        UpdateSelectMenuVisibility(true);
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
        return;
    }

    if (isCursorAlwaysDisplayed_) {
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
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    ScheduleCursorTwinkling();
}

void TextFieldPattern::OnCursorTwinkling()
{
    cursorTwinklingTask_.Cancel();
    cursorVisible_ = !cursorVisible_;
    auto shouldMeasure = !IsTextArea() && IsInPasswordMode() && GetTextObscured() && obscureTickCountDown_ == 1;
    if (IsInPasswordMode() && GetTextObscured() && obscureTickCountDown_ > 0) {
        --obscureTickCountDown_;
    }
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
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Keyboard type changed to %{public}d",
            layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
        keyboard_ = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
        needToResetKeyboard = true;
    }
    if (!needToResetKeyboard && action_ != TextInputAction::UNSPECIFIED) {
        needToResetKeyboard = action_ != GetTextInputActionValue(GetDefaultTextInputAction());
    }
    action_ = GetTextInputActionValue(GetDefaultTextInputAction());
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Keyboard action is %{public}d", action_);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (needToResetKeyboard) {
        // if keyboard attached and keyboard is shown, pull up keyboard again
        if (imeShown_ || isCustomKeyboardAttached_) {
            RequestKeyboard(false, true, true);
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
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    CheckIfNeedToResetKeyboard();
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
    InitDisableColor();
    ProcessResponseArea();
    InitDragEvent();
    Register2DragDropManager();
    context->AddOnAreaChangeNode(host->GetId());
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    if (barState_.has_value() && barState_.value() != layoutProperty->GetDisplayModeValue(DisplayMode::AUTO) &&
        HasFocus() && IsNormalInlineState()) {
        lastTextRectY_ = textRect_.GetY();
    }
    if (!IsDisabled()) {
        SetShowError();
    }
    ProcessInnerPadding();
    // The textRect position can't be changed by only redraw.
    if (CheckNeedMeasure(layoutProperty->GetPropertyChangeFlag()) && !HasInputOperation()) {
        textRect_.SetLeft(GetPaddingLeft() + GetBorderLeft());
        textRect_.SetTop(GetPaddingTop() + GetBorderTop());
    }
    CalculateDefaultCursor();

    auto textWidth = static_cast<int32_t>(contentController_->GetWideText().length());
    if (SelectOverlayIsOn()) {
        needToRefreshSelectOverlay_ = true;
        UpdateSelection(std::clamp(selectController_->GetStartIndex(), 0, textWidth),
            std::clamp(selectController_->GetEndIndex(), 0, textWidth));
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
        scrollBarVisible_ = barState != DisplayMode::OFF;
        SetScrollBar(barState == DisplayMode::OFF ? DisplayMode::ON : barState);
        auto scrollBar = GetScrollBar();
        if (scrollBar) {
            scrollBar->SetMinHeight(SCROLL_BAR_MIN_HEIGHT);
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
    if (IsTextArea()) {
        if (setBorderFlag_ && layoutProperty->HasMaxLength()) {
            auto textFieldTheme = GetTheme();
            lastDiffBorderColor_.SetColor(textFieldTheme->GetOverCountBorderColor());
            lastDiffBorderWidth_.SetBorderWidth(OVER_COUNT_BORDER_WIDTH);
            setBorderFlag_ = false;
        }
        HandleCounterBorder();
    }
    UpdateCounterMargin();
    if (!IsTextArea()) {
        isTextInput_ = true;
    }
    auto inputStyle = paintProperty->GetInputStyleValue(InputStyle::DEFAULT);
    if (!inlineState_.saveInlineState || !HasFocus()) {
        SaveInlineStates();
    }
    if (HasFocus() && IsNormalInlineState()) {
        ApplyInlineStates(preInputStyle_ == InputStyle::DEFAULT);
    }
    if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()
        && (!IsNormalInlineState() || !HasFocus())) {
        ApplyUnderlineStates();
    }
    if (preInputStyle_ == InputStyle::INLINE && inputStyle == InputStyle::DEFAULT) {
        if (IsTextArea() && isTextInput_) {
            layoutProperty->UpdateMaxLines(1);
        }
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
        if (!GetTextBoxes().empty()) {
            UpdateSelection(0);
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    auto maxlength = GetMaxLength();
    auto originLength = static_cast<int32_t>(contentController_->GetWideText().length());
    HandleInputCounterBorder(originLength, maxlength);
    preInputStyle_ = inputStyle;
    Register2DragDropManager();
    isModifyDone_ = true;
    selectController_->FireSelectEvent();
}

void TextFieldPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        bool isPwdType = layoutProperty ? layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) ==
                                              TextInputType::VISIBLE_PASSWORD
                                        : false;
        if (!isPwdType) {
            Recorder::NodeDataCache::Get().PutString(inspectorId, contentController_->GetTextValue());
        }
    }
}

void TextFieldPattern::CalculateDefaultCursor()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    float caretWidth = paintProperty->GetCursorWidth().has_value()
                           ? static_cast<float>(paintProperty->GetCursorWidthValue().ConvertToPx())
                           : static_cast<float>(textFieldTheme->GetCursorWidth().ConvertToPx());
    selectController_->UpdateCaretWidth(caretWidth);
    if (!contentController_->IsEmpty()) {
        return;
    }
    selectController_->UpdateCaretHeight(PreferredLineHeight());
}

bool TextFieldPattern::FireOnTextChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto cleanNodeStyle = layoutProperty->GetCleanNodeStyle().value_or(CleanNodeStyle::INPUT);
    if (cleanNodeStyle == CleanNodeStyle::INPUT) {
        auto cleanNodeResponseArea = DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
        if (cleanNodeResponseArea && contentController_->IsEmpty() && cleanNodeResponseArea->IsShow()) {
            cleanNodeResponseArea->UpdateCleanNode(false);
        } else if (cleanNodeResponseArea && !contentController_->IsEmpty() && !cleanNodeResponseArea->IsShow()) {
            cleanNodeResponseArea->UpdateCleanNode(true);
        }
    }
    auto textCache = layoutProperty->GetValueValue("");
    if (textCache == contentController_->GetTextValue()) {
        return false;
    }
    layoutProperty->UpdateValue(contentController_->GetTextValue());
    host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, contentController_->GetTextValue());
    eventHub->FireOnChange(contentController_->GetTextValue());
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    taskExecutor->PostTask(
        [weak = WeakClaim(this)] {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (!pattern->HasFocus()) {
                return;
            }
            pattern->ScrollToSafeArea();
        },
        TaskExecutor::TaskType::UI);
    return true;
}

void TextFieldPattern::ContentFireOnChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(contentController_->GetTextValue());
}

void TextFieldPattern::FilterInitializeText()
{
    if (HasInputOperation()) {
        return;
    }
    if (!contentController_->IsEmpty()) {
        contentController_->FilterValue();
    }
    if (static_cast<int32_t>(GetWideText().length()) < GetCaretIndex()) {
        selectController_->UpdateCaretIndex(static_cast<int32_t>(GetWideText().length()));
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
    return !eventHub->IsEnabled();
}

void TextFieldPattern::ProcessInnerPadding()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto textFieldTheme = GetTheme();
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
    auto left = !paddingProperty ? CalcLength(themePadding.Left()).GetDimension()
                                 : paddingProperty->left.value_or(CalcLength(themePadding.Left())).GetDimension();
    utilPadding_.left = left.ConvertToPx();
    auto top = !paddingProperty ? CalcLength(themePadding.Top()).GetDimension()
                                : paddingProperty->top.value_or(CalcLength(themePadding.Top())).GetDimension();
    utilPadding_.top = top.ConvertToPx();
    auto bottom = !paddingProperty ? CalcLength(themePadding.Bottom()).GetDimension()
                                   : paddingProperty->bottom.value_or(CalcLength(themePadding.Bottom())).GetDimension();
    utilPadding_.bottom = bottom.ConvertToPx();
    auto right = !paddingProperty ? CalcLength(themePadding.Right()).GetDimension()
                                  : paddingProperty->right.value_or(CalcLength(themePadding.Right())).GetDimension();
    utilPadding_.right = right.ConvertToPx();
    lastBorderWidth_ = currentBorderWidth;

    PaddingProperty paddings;
    paddings.top = NG::CalcLength(top);
    paddings.bottom = NG::CalcLength(bottom);
    paddings.left = NG::CalcLength(left);
    paddings.right = NG::CalcLength(right);
    layoutProperty->UpdatePadding(paddings);
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
    isTouchCaret_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    bool shouldProcessOverlayAfterLayout = false;
    if (ResetObscureTickCountDown()) {
        shouldProcessOverlayAfterLayout = true;
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
        gestureHub->SetIsTextDraggable(true);
        return;
    }
    gestureHub->SetIsTextDraggable(false);
    isLongPress_ = true;
    auto focusHub = GetFocusHub();
    if (!focusHub->IsCurrentFocus()) {
        focusHub->RequestFocusImmediately();
    }
    if (isSingleHandle_) {
        CloseSelectOverlay(true);
    }
    selectController_->UpdateSelectByOffset(info.GetLocalLocation());
    if (IsSelected()) {
        StopTwinkling();
    }
    SetIsSingleHandle(!IsSelected());
    if (shouldProcessOverlayAfterLayout) {
        DelayProcessOverlay(true, true);
    } else {
        ProcessOverlay(true, true);
        UpdateSelectMenuVisibility(true);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::UpdateCaretPositionWithClamp(const int32_t& pos)
{
    selectController_->UpdateCaretIndex(
        std::clamp(pos, 0, static_cast<int32_t>(contentController_->GetWideText().length())));
}

void TextFieldPattern::ProcessOverlay(bool isUpdateMenu, bool animation, bool isShowMenu, bool isHiddenHandle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasFontSize() && NearZero(layoutProperty->GetFontSize()->Value())) {
        return;
    }
    selectController_->CalculateHandleOffset();
    ShowSelectOverlayParams showOverlayParams = {
        .animation = animation, .isShowMenu = isShowMenu, .isUpdateMenu = isUpdateMenu
    };
    if (IsSelected() && selectController_->IsHandleSamePosition()) {
        isSingleHandle_ = true;
        selectController_->UpdateCaretIndex(selectController_->GetFirstHandleIndex());
        selectController_->UpdateCaretOffset();
    }
    if (isSingleHandle_) {
        StartTwinkling();
        showOverlayParams.firstHandle = std::nullopt;
        showOverlayParams.secondHandle = selectController_->GetCaretRect();
        ShowSelectOverlay(showOverlayParams);
    } else {
        showOverlayParams.firstHandle = selectController_->GetFirstHandleRect();
        showOverlayParams.secondHandle = selectController_->GetSecondHandleRect();
        ShowSelectOverlay(showOverlayParams);
    }
    if (isHiddenHandle) {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        auto selectManager = context->GetSelectOverlayManager();
        CHECK_NULL_VOID(selectManager);
        auto selectOverlayItem = selectManager->GetSelectOverlayItem();
        auto selectOverlay = selectOverlayItem.Upgrade();
        CHECK_NULL_VOID(selectOverlay);
        auto pattern = selectOverlay->GetPattern<SelectOverlayPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->StartHiddenHandleTask(false);
    }
}

void TextFieldPattern::DelayProcessOverlay(bool isUpdateMenu, bool animation, bool isShowMenu)
{
    processOverlayDelayTask_ = [weak = WeakClaim(this), isUpdateMenu, animation, isShowMenu]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ProcessOverlay(isUpdateMenu, animation, isShowMenu);
    };
}

void TextFieldPattern::ShowSelectOverlay(const ShowSelectOverlayParams& showOverlayParams)
{
    if (isTransparent_) {
        return;
    }
    showSelect_ = true;
    auto hasDataCallback = [weak = WeakClaim(this), params = showOverlayParams](bool hasData) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HasData callback from clipboard, data available ? %{public}d", hasData);
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
        auto contentRect = GetContentRect();
        handle.SetOffset(handle.GetOffset() + GetTextPaintOffset());
        if (handle.Height() > contentRect.Height()) {
            handle.SetHeight(contentRect.Height());
        }
        SelectHandleInfo secondHandleInfo;
        secondHandleInfo.paintRect = handle;
        overlayInfo.secondHandleInfo = secondHandleInfo;
    }
    overlayInfo.isShowPaste = isShowPaste;
    overlayInfo.isMenuShow = params.isShowMenu;
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
        overlayInfo.handleReverse = selectController_->HasReverse();
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
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    isSupportCameraInput_ =
        inputMethod && inputMethod->IsInputTypeSupported(MiscServices::InputType::CAMERA_INPUT) && !IsInPasswordMode();
#else
    isSupportCameraInput_ = false;
#endif
    overlayInfo.menuInfo.showCameraInput = !IsSelected() && isSupportCameraInput_ && !customKeyboardBuilder_;
    return true;
}

void TextFieldPattern::UpdateSelectOverlaySecondHandle(bool needLayout)
{
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
    handleInfo.needLayout = needLayout;
    proxy->UpdateSecondSelectHandleInfo(handleInfo);
}

void TextFieldPattern::UpdateSelectOverlayDoubleHandle(bool firstNeedLayout, bool secondNeedLayout)
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
    return layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None && !IsInPasswordMode();
}

void TextFieldPattern::OnDetachFromFrameNode(FrameNode* node)
{
    CloseSelectOverlay();
    ResetSelectOverlayClient();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    if (HasSurfacePositionChangedCallback()) {
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
    pipeline->RemoveOnAreaChangeNode(node->GetId());
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
    SetLocalOffset(localOffset);
    if (isSingleHandle_) {
        selectController_->UpdateCaretInfoByOffset(Offset(localOffset.GetX(), localOffset.GetY()));
    } else {
        auto proxy = GetSelectOverlayProxy();
        CHECK_NULL_VOID(proxy);
        auto position = UpdateCaretPositionOnHandleMove(localOffset);
        if (isFirstHandle) {
            selectController_->MoveFirstHandleToContentRect(position);
            SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
            proxy->UpdateSecondSelectHandleInfo(handleInfo);
        } else {
            selectController_->MoveSecondHandleToContentRect(position);
            SelectHandleInfo handleInfo = GetSelectHandleInfo(selectController_->GetFirstHandleOffset());
            proxy->UpdateFirstSelectHandleInfo(handleInfo);
        }
        proxy->SetHandleReverse(selectController_->HasReverse());
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    UpdateShowMagnifier();
    auto proxy = GetSelectOverlayProxy();
    CHECK_NULL_VOID(proxy);
    if (!isSingleHandle_) {
        if (selectController_->GetFirstHandleIndex() == selectController_->GetSecondHandleIndex()) {
            UpdateSelectMenuVisibility(false);
            CloseSelectOverlay(true);
            StartTwinkling();
            selectController_->MoveCaretToContentRect(GetCaretIndex());
        } else {
            auto firstHandleInfo = GetSelectHandleInfo(selectController_->GetFirstHandleOffset());
            auto secondHandleInfo = GetSelectHandleInfo(selectController_->GetSecondHandleOffset());
            proxy->UpdateFirstAndSecondHandleInfo(firstHandleInfo, secondHandleInfo);
            proxy->SetHandleReverse(selectController_->HasReverse());
        }
    } else {
        auto handleInfo = GetSelectHandleInfo(selectController_->GetCaretRect().GetOffset());
        handleInfo.paintRect.SetWidth(selectController_->GetCaretRect().Width());
        proxy->UpdateSecondSelectHandleInfo(handleInfo);
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::OnHandleClosed(bool closedByGlobalEvent)
{
    SelectOverlayClient::OnHandleClosed(closedByGlobalEvent);
    if (closedByGlobalEvent) {
        UpdateSelectMenuVisibility(false);
    }
    if (GetShowMagnifier()) {
        UpdateShowMagnifier();
    }
}

void TextFieldPattern::InitEditingValueText(std::string content)
{
    if (HasInputOperation()) {
        return;
    }
    contentController_->SetTextValueOnly(std::move(content));
    selectController_->UpdateCaretIndex(GetWideText().length());
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Textfield %{public}d %{public}s", tmpHost->GetId(),
        isHover ? "on hover" : "exit hover");
    auto frameId = tmpHost->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    if (isHover) {
        pipeline->SetMouseStyleHoldNode(frameId);
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

void TextFieldPattern::ChangeMouseState(const Offset location, const RefPtr<PipelineContext>& pipeline, int32_t frameId)
{
    auto responseAreaWidth = (responseArea_ ? responseArea_->GetAreaRect().Width() : 0.0f) +
                             (cleanNodeResponseArea_ ? cleanNodeResponseArea_->GetAreaRect().Width() : 0.0f);
    auto x = location.GetX();
    auto y = location.GetY();
    if (GreatNotEqual(x, 0) && LessNotEqual(x, frameRect_.Width()) && GreatNotEqual(y, 0) &&
        LessNotEqual(y, frameRect_.Height())) {
        if (GreatNotEqual(location.GetX(), frameRect_.Width() - responseAreaWidth)) {
            pipeline->SetMouseStyleHoldNode(frameId);
            pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        } else {
            pipeline->SetMouseStyleHoldNode(frameId);
            pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR);
        }
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
}

void TextFieldPattern::HandleMouseEvent(MouseInfo& info)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto frameId = tmpHost->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    info.SetStopPropagation(true);
    auto scrollBar = GetScrollBar();
    if (scrollBar && (scrollBar->IsPressed() || scrollBar->IsHover())) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        return;
    }
    ChangeMouseState(info.GetLocalLocation(), pipeline, frameId);

    isUsingMouse_ = true;
    if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        HandleRightMouseEvent(info);
    } else if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        HandleLeftMouseEvent(info);
    }
    if (info.GetAction() == OHOS::Ace::MouseAction::RELEASE) {
        isUsingMouse_ = false;
    }
}

void TextFieldPattern::HandleRightMouseEvent(MouseInfo& info)
{
    if (info.GetAction() == OHOS::Ace::MouseAction::PRESS) {
        HandleRightMousePressEvent(info);
        return;
    }
    if (info.GetAction() == OHOS::Ace::MouseAction::RELEASE) {
        HandleRightMouseReleaseEvent(info);
    }
}

void TextFieldPattern::HandleRightMousePressEvent(MouseInfo& info)
{
    if (IsSelected()) {
        return;
    }
    auto focusHub = GetFocusHub();
    if (!focusHub->IsFocusable()) {
        return;
    }
    FocusAndUpdateCaretByMouse(info);
}

void TextFieldPattern::HandleRightMouseReleaseEvent(MouseInfo& info)
{
    auto focusHub = GetFocusHub();
    if (focusHub->IsCurrentFocus()) {
        rightClickOffset_ = OffsetF(
            static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
        if (SelectOverlayIsOn()) {
            CloseSelectOverlay(true);
        }
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
    FocusAndUpdateCaretByMouse(info);
}

void TextFieldPattern::FocusAndUpdateCaretByMouse(MouseInfo& info)
{
    auto focusHub = GetFocusHub();
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
        StopTwinkling();
        return;
    }
    selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation());
    StartTwinkling();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleLeftMouseMoveEvent(MouseInfo& info)
{
    if (!leftMouseCanMove_ || blockPress_) {
        return;
    }
    auto focusHub = GetFocusHub();
    if (!focusHub->IsCurrentFocus()) {
        return;
    }
    mouseStatus_ = MouseStatus::MOVE;
    selectController_->UpdateSecondHandleInfoByMouseOffset(info.GetLocalLocation()); // 更新时上报事件
    showSelect_ = true;
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleLeftMouseReleaseEvent(MouseInfo& info)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    if (blockPress_ && mouseStatus_ == MouseStatus::PRESSED) {
        selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation());
        StartTwinkling();
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    mouseStatus_ = MouseStatus::NONE;
    blockPress_ = false;
    leftMouseCanMove_ = false;
    if (HasFocus() && RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::UpdateTextFieldManager(const Offset& offset, float height)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto context = tmpHost->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->UpdateScrollableParentViewPort(tmpHost);
    if (!HasFocus()) {
        return;
    }
    textFieldManager->SetClickPosition({ offset.GetX() + selectController_->GetCaretRect().GetX(),
        offset.GetY() + selectController_->GetCaretRect().GetY() });
    textFieldManager->SetHeight(selectController_->GetCaretRect().Height());
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
}

TextInputAction TextFieldPattern::GetDefaultTextInputAction() const
{
    TextInputAction defaultTextInputAction = TextInputAction::DONE;
    if (IsTextArea() && !isTextInput_) {
        defaultTextInputAction = TextInputAction::NEW_LINE;
    } else {
        defaultTextInputAction = TextInputAction::DONE;
    }
    return defaultTextInputAction;
}

#ifdef WINDOW_SCENE_SUPPORTED
uint32_t TextFieldPattern::GetSCBSystemWindowId()
{
    RefPtr<FrameNode> frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, {});
    auto focusSystemWindowId = WindowSceneHelper::GetFocusSystemWindowId(frameNode);
    return focusSystemWindowId;
}
#endif

bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, false);

    if (needShowSoftKeyboard) {
        if (customKeyboardBuilder_) {
            return RequestCustomKeyboard();
        }
#if defined(ENABLE_STANDARD_INPUT)
        if (textChangeListener_ == nullptr) {
            textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
        }
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            return false;
        }
        auto optionalTextConfig = GetMiscTextConfig();
        CHECK_NULL_RETURN(optionalTextConfig.has_value(), false);
        MiscServices::TextConfig textConfig = optionalTextConfig.value();
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "RequestKeyboard set calling window id:%{public}u"
            "inputType: %{public}d",
            textConfig.windowId, textConfig.inputAttribute.inputPattern);
#ifdef WINDOW_SCENE_SUPPORTED
        auto systemWindowId = GetSCBSystemWindowId();
        if (systemWindowId) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "windowId From %{public}u to %{public}u.", textConfig.windowId,
                systemWindowId);
            textConfig.windowId = systemWindowId;
        }
#endif
        if (customKeyboardBuilder_ && isCustomKeyboardAttached_) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Request Softkeyboard,Close CustomKeyboard.");
            CloseCustomKeyboard();
        }
        inputMethod->Attach(textChangeListener_, needShowSoftKeyboard, textConfig);
        UpdateKeyboardOffset(textConfig.positionY, textConfig.height);
#else
        if (!HasConnection()) {
            TextInputConfiguration config;
            config.type = keyboard_;
            config.action = GetTextInputActionValue(GetDefaultTextInputAction());
            config.inputFilter = GetInputFilter();
            config.maxLength = GetMaxLength();
            if (keyboard_ == TextInputType::VISIBLE_PASSWORD || keyboard_ == TextInputType::NEW_PASSWORD) {
                config.obscureText = textObscured_;
            }
            connection_ = TextInputProxy::GetInstance().Attach(
                WeakClaim(this), config, context->GetTaskExecutor(), GetInstanceId());

            if (!HasConnection()) {
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
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, {});
    auto windowRect = pipeline->GetCurrentWindowRect();
    double positionY = (tmpHost->GetPaintRectOffset() - pipeline->GetRootRect().GetOffset()).GetY() + windowRect.Top();
    double height = frameRect_.Height();

    if (IsNormalInlineState()) {
        auto manager = pipeline->GetSafeAreaManager();
        const double HEIGHT_OFFSET = theme->GetInlineBorderWidth().ConvertToPx() * 2 + 1;
        height = std::max(static_cast<double>(inlineMeasureItem_.inlineSizeHeight) + HEIGHT_OFFSET, height);
        positionY += frameRect_.Height();
    }

    MiscServices::CursorInfo cursorInfo { .left = selectController_->GetCaretRect().Left() + windowRect.Left() +
                                                  parentGlobalOffset_.GetX(),
        .top = selectController_->GetCaretRect().Top() + windowRect.Top() + parentGlobalOffset_.GetY(),
        .width = theme->GetCursorWidth().ConvertToPx(),
        .height = selectController_->GetCaretRect().Height() };
    MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)keyboard_,
        .enterKeyType = (int32_t)GetTextInputActionValue(GetDefaultTextInputAction()) };
    MiscServices::TextConfig textConfig = { .inputAttribute = inputAttribute,
        .cursorInfo = cursorInfo,
        .range = { .start = selectController_->GetStartIndex(), .end = selectController_->GetEndIndex() },
        .windowId = pipeline->GetFocusWindowId(),
        .positionY = positionY,
        .height = height };
    return textConfig;
}
#endif

AceAutoFillType TextFieldPattern::ConvertToAceAutoFillType(TextInputType type)
{
    static std::unordered_map<TextInputType, AceAutoFillType> convertMap = {
        { TextInputType::VISIBLE_PASSWORD, AceAutoFillType::ACE_PASSWORD },
        { TextInputType::USER_NAME, AceAutoFillType::ACE_USER_NAME },
        { TextInputType::NEW_PASSWORD, AceAutoFillType::ACE_NEW_PASSWORD } };
    if (convertMap.find(type) != convertMap.end()) {
        return convertMap[type];
    }
    return AceAutoFillType::ACE_UNSPECIFIED;
}

bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    if (forceClose) {
        StopTwinkling();
        CloseSelectOverlay(true);
        if (customKeyboardBuilder_ && isCustomKeyboardAttached_) {
            return CloseCustomKeyboard();
        }
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Request close soft keyboard.");
#if defined(ENABLE_STANDARD_INPUT)
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            return false;
        }
        inputMethod->Close();
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
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (inputMethod) {
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->BindKeyboard(customKeyboardBuilder_, frameNode->GetId());
    isCustomKeyboardAttached_ = true;
    keyboardOverlay_ = overlayManager;
    return true;
}

bool TextFieldPattern::CloseCustomKeyboard()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    CHECK_NULL_RETURN(keyboardOverlay_, false);
    keyboardOverlay_->CloseKeyboard(frameNode->GetId());
    isCustomKeyboardAttached_ = false;
    return true;
}

void TextFieldPattern::OnTextInputActionUpdate(TextInputAction value) {}

void TextFieldPattern::InsertValueOperation(const std::string& insertValue)
{
    auto caretStart = 0;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    if (IsSelected()) {
        caretStart = start;
    } else {
        caretStart = selectController_->GetCaretIndex();
    }
    int32_t caretMoveLength = 0;
    bool hasInsertValue = false;
    if (IsSelected()) {
        auto originLength = static_cast<int32_t>(contentController_->GetWideText().length()) - (end - start);
        hasInsertValue = contentController_->ReplaceSelectedValue(start, end, insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);
    } else {
        auto originLength = static_cast<int32_t>(contentController_->GetWideText().length());
        hasInsertValue = contentController_->InsertValue(selectController_->GetCaretIndex(), insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);
    }
    auto wideInsertValue = StringUtils::ToWstring(insertValue);
    selectController_->UpdateCaretIndex(caretStart + caretMoveLength);
    if (!IsTextArea() && IsInPasswordMode() && GetTextObscured()) {
        if (wideInsertValue.length() == 1 &&
            (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::NUMBER_PASSWORD ||
                std::isdigit(insertValue[0])) && hasInsertValue) {
            auto content = contentController_->GetWideText();
            auto insertIndex = selectController_->GetCaretIndex() - 1;
            insertIndex = std::clamp(insertIndex, 0, static_cast<int32_t>(content.length()));
            auto strBeforeCaret = content.empty() ? "" : StringUtils::ToString(content.substr(insertIndex, 1));
            obscureTickCountDown_ = strBeforeCaret == insertValue ? OBSCURE_SHOW_TICKS : 0;
            nakedCharPosition_ = strBeforeCaret == insertValue ? insertIndex : -1;
        } else {
            obscureTickCountDown_ = 0;
            nakedCharPosition_ = -1;
        }
    }
    UpdateEditingValueToRecord();
    cursorVisible_ = true;
    StartTwinkling();
}

void TextFieldPattern::InsertValue(const std::string& insertValue)
{
    if (focusIndex_ != FocuseIndex::TEXT && insertValue == " ") {
        HandleSpaceEvent();
        return;
    }
    focusIndex_ = FocuseIndex::TEXT;
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Insert value '%{public}s'", insertValue.c_str());
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto maxlength = GetMaxLength();
    auto originLength = static_cast<int32_t>(contentController_->GetWideText().length());
    auto pattern = host->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto textFieldLayoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto inputValue = textFieldLayoutProperty->GetSetCounterValue(DEFAULT_MODE);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    if (inputValue == DEFAULT_MODE) {
        originLength = originLength + ONE_CHARACTER;
    }
    if (textFieldLayoutProperty->GetShowCounterValue(false) && originLength == maxlength &&
        inputValue == DEFAULT_MODE) {
        UpdateCounterBorderStyle(originLength, maxlength);
    }
    bool noDeleteOperation = deleteBackwardOperations_.empty() && deleteForwardOperations_.empty();
    if (!IsShowPasswordIcon() && originLength == maxlength && noDeleteOperation && !IsSelected() &&
        textFieldLayoutProperty->GetShowCounterValue(false) && inputValue != DEFAULT_MODE &&
        inputValue != ILLEGAL_VALUE && !IsNormalInlineState()) {
        counterChange_ = true;
        UpdateOverCounterColor();
        UltralimitShake();
        return;
    }
    inputOperations_.emplace(InputOperation::INSERT);
    insertValueOperations_.emplace(insertValue);
    CloseSelectOverlay(true);
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleInputCounterBorder(int32_t& textLength, uint32_t& maxLength)
{
    auto host = GetHost();
    auto textFieldLayoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (!textFieldLayoutProperty->GetShowCounterValue(false) || IsNormalInlineState() || IsShowPasswordIcon() ||
        !textFieldLayoutProperty->HasMaxLength()) {
        return;
    }
    auto inputValue = textFieldLayoutProperty->GetSetCounterValue(DEFAULT_MODE);
    if (textLength >= maxLength && inputValue == DEFAULT_MODE) {
        UpdateCounterBorderStyle(textLength, maxLength);
    }
}

void TextFieldPattern::UpdateOverCounterColor()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto counterNode = counterTextNode_.Upgrade();
    CHECK_NULL_VOID(counterNode);
    auto textFieldLayoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(counterNode->GetLayoutProperty());
    CHECK_NULL_VOID(textLayoutProperty);
    auto showBorder = textFieldLayoutProperty->GetShowHighlightBorderValue(true);
    TextStyle countTextStyle = theme->GetOverCountTextStyle();
    countTextStyle = theme->GetOverCountTextStyle();
    countTextStyle.SetTextColor(theme->GetOverCounterColor());
    textLayoutProperty->UpdateTextColor(countTextStyle.GetTextColor());
    auto host = counterNode->GetHostNode();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    if (IsTextArea() && showBorder == true) {
        HandleCounterBorder();
    } else if (!IsTextArea() && showBorder == true) {
        underlineColor_ = theme->GetErrorUnderlineColor();
    }
    context->UpdateForegroundColor(countTextStyle.GetTextColor());
    host->MarkDirtyNode();
}

void TextFieldPattern::UpdateCounterBorderStyle(int32_t& textLength, uint32_t& maxLength)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    counterChange_ = true;
    auto showBorder = textFieldLayoutProperty->GetShowHighlightBorderValue(true);
    if (textLength >= (maxLength - ONE_CHARACTER) && !IsTextArea() && showBorder == true) {
        SetUnderlineColor(theme->GetErrorUnderlineColor());
    } else if (textLength >= maxLength && IsTextArea() && showBorder == true) {
        HandleCounterBorder();
    }
    return;
}

void TextFieldPattern::UltralimitShake()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    AnimationOption option;
    context->UpdateTranslateInXY({ -1.0, 0.0 });
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(VELOCITY, MASS, STIFFNESS, DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    AnimationUtils::Animate(
        option,
        [context]() {
            if (context) {
                context->UpdateTranslateInXY({ 0.0f, 0.0f });
            }
        },
        option.GetOnFinishEvent());
}

void TextFieldPattern::UpdateCounterMargin()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!IsTextArea() && layoutProperty->GetShowCounterValue(false) && !IsNormalInlineState() &&
        !IsShowPasswordIcon()) {
        MarginProperty margin;
        const auto& getMargin = layoutProperty->GetMarginProperty();
        if (getMargin) {
            auto systemMargin = getMargin->bottom->GetDimension();
            Dimension marginProperty { BOTTOM_MARGIN, DimensionUnit::VP };
            margin.bottom = CalcLength(marginProperty + systemMargin);
            margin.left = CalcLength(getMargin->left->GetDimension());
            margin.top = CalcLength(getMargin->top->GetDimension());
            margin.right = CalcLength(getMargin->right->GetDimension());
            layoutProperty->UpdateMargin(margin);
        }
        if (!getMargin) {
            margin.bottom = CalcLength(COUNTER_BOTTOM);
            layoutProperty->UpdateMargin(margin);
        }
    }
}

void TextFieldPattern::CleanCounterNode()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    auto textFieldLayoutProperty = pattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto counterNode = DynamicCast<UINode>(counterTextNode_.Upgrade());
    CHECK_NULL_VOID(counterNode);
    frameNode->RemoveChild(counterNode);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void TextFieldPattern::UpdateEditingValueToRecord()
{
    if (operationRecords_.size() >= RECORD_MAX_LENGTH) {
        operationRecords_.erase(operationRecords_.begin());
    }
    TextEditingValueNG record {
        .text = contentController_->GetTextValue(),
        .caretPosition = selectController_->GetCaretIndex(),
    };
    operationRecords_.emplace_back(record);
}

float TextFieldPattern::PreferredTextHeight(bool isPlaceholder, bool isAlgorithmMeasure)
{
    if (!isAlgorithmMeasure && paragraph_ && paragraph_->GetHeight() != 0.0f) {
        return paragraph_->GetHeight() / paragraph_->GetLineCount();
    }
    RefPtr<Paragraph> paragraph;
    std::string textContent;
    TextStyle textStyle;
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, 0.0f);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0.0f);
    auto textFieldTheme = GetTheme();
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

float TextFieldPattern::PreferredLineHeight(bool isAlgorithmMeasure)
{
    return PreferredTextHeight(contentController_->IsEmpty(), isAlgorithmMeasure);
}

void TextFieldPattern::OnCursorMoveDone(TextAffinity textAffinity)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    CloseSelectOverlay();
    selectController_->MoveCaretToContentRect(GetCaretIndex(), textAffinity);
    if (ResetObscureTickCountDown()) {
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

int32_t TextFieldPattern::GetWordLength(int32_t originCaretPosition, int32_t directionMove)
{
    if (contentController_->IsEmpty()) {
        return 0;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        return 0;
    }
    // directionMove == 0 left, directionMove == 1 right
    // cannot get word length by current caret position and direction
    if ((directionMove == 0 && originCaretPosition == 0) || (directionMove == 1 && originCaretPosition == textLength)) {
        return 0;
    }
    int32_t offset = 0;
    int32_t strIndex = directionMove == 0 ? (originCaretPosition - 1) : originCaretPosition;
    auto wideTextValue = contentController_->GetWideText();
    if (wideTextValue[strIndex] == L' ') {
        int32_t wordStart = 0;
        int32_t wordEnd = 0;
        if (!paragraph_->GetWordBoundary(strIndex, wordStart, wordEnd)) {
            return 0;
        }
        if (directionMove == 1) {
            offset += (wordEnd - strIndex);
            return offset;
        } else {
            offset += (strIndex - wordStart + 1); // when move left, actual offset should add 1
            strIndex = (wordStart - 1);           // when move left, actual index should minus 1
        }
    }
    bool hasJumpBlank = false;
    for (; directionMove == 0 ? strIndex >= 0 : strIndex <= textLength;) {
        auto chr = wideTextValue[strIndex];
        if (StringUtils::IsLetterOrNumberForWchar(chr) || (chr == L' ' && directionMove == 1)) {
            if (directionMove == 1 && hasJumpBlank && chr != L' ') {
                return offset;
            } else if (directionMove == 1 && !hasJumpBlank && chr == L' ') {
                hasJumpBlank = true;
            }
            offset++;
        } else {
            if (offset <= 0) {
                offset = 1;
            }
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

bool TextFieldPattern::CursorMoveLeftOperation()
{
    if (focusIndex_ != FocuseIndex::TEXT) {
        return UpdateFocusBackward();
    }
    auto originCaretPosition = selectController_->GetCaretIndex();
    if (IsSelected()) {
        selectController_->UpdateCaretIndex(selectController_->GetStartIndex());
        CloseSelectOverlay();
        StartTwinkling();
    } else {
        UpdateCaretPositionWithClamp(
            selectController_->GetCaretIndex() -
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetCaretIndex(), true));
    }
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveLeft()
{
    if (inputOperations_.empty()) {
        return CursorMoveLeftOperation();
    }

    inputOperations_.emplace(InputOperation::CURSOR_LEFT);
    return false;
}

bool TextFieldPattern::CursorMoveLeftWord()
{
    if (selectController_->GetCaretIndex() == 0) {
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t leftWordLength = GetWordLength(originCaretPosition, 0);
    if (leftWordLength < 0 || leftWordLength > textLength || selectController_->GetCaretIndex() - leftWordLength < 0) {
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
        return true;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t lineBeginPosition = GetLineBeginPosition(originCaretPosition);
    if (lineBeginPosition < 0 || lineBeginPosition > textLength) {
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
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    UpdateCaretPositionWithClamp(0);
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveRightOperation()
{
    if (focusIndex_ != FocuseIndex::TEXT) {
        return UpdateFocusForward();
    }
    auto originCaretPosition = selectController_->GetCaretIndex();
    if (IsSelected()) {
        CloseSelectOverlay();
        selectController_->UpdateCaretIndex(selectController_->GetEndIndex());
        StartTwinkling();
    } else {
        UpdateCaretPositionWithClamp(
            selectController_->GetCaretIndex() +
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetCaretIndex()));
    }
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveRight()
{
    if (inputOperations_.empty()) {
        return CursorMoveRightOperation();
    }
    inputOperations_.emplace(InputOperation::CURSOR_RIGHT);
    return false;
}

bool TextFieldPattern::CursorMoveRightWord()
{
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t rightWordLength = GetWordLength(originCaretPosition, 1);
    if (rightWordLength < 0 || rightWordLength > textLength ||
        rightWordLength + selectController_->GetCaretIndex() > textLength) {
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
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t lineEndPosition = GetLineEndPosition(originCaretPosition);
    if (lineEndPosition < 0 || lineEndPosition > textLength) {
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
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    UpdateCaretPositionWithClamp(textLength);
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveUpOperation()
{
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

bool TextFieldPattern::CursorMoveUp()
{
    if (inputOperations_.empty()) {
        return CursorMoveUpOperation();
    }

    inputOperations_.emplace(InputOperation::CURSOR_UP);
    return false;
}

bool TextFieldPattern::CursorMoveDownOperation()
{
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

bool TextFieldPattern::CursorMoveDown()
{
    if (inputOperations_.empty()) {
        return CursorMoveDownOperation();
    }

    inputOperations_.emplace(InputOperation::CURSOR_DOWN);
    return false;
}

void TextFieldPattern::Delete(int32_t start, int32_t end)
{
    SwapIfLarger(start, end);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Handle Delete within [%{public}d, %{public}d]", start, end);
    contentController_->erase(start, end - start);
    UpdateSelection(start);
    selectController_->MoveCaretToContentRect(start);
    CloseSelectOverlay(true);
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleCounterBorder()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if ((HasFocus() && IsNormalInlineState())) {
        return;
    }
    auto textFieldTheme = GetTheme();
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
    overCountBorderColor.SetColor(textFieldTheme->GetOverCounterColor());
    UpdateAreaBorderStyle(currentBorderWidth, overCountBorderWidth,
        overCountBorderColor, currentBorderColor);
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

void TextFieldPattern::UpdateAreaBorderStyle(BorderWidthProperty& currentBorderWidth,
    BorderWidthProperty& overCountBorderWidth, BorderColorProperty& overCountBorderColor,
    BorderColorProperty& currentBorderColor)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto maxLength = GetMaxLength();
    auto currentLength = static_cast<uint32_t>(contentController_->GetWideText().length());
    auto showBorder = layoutProperty->GetShowHighlightBorderValue(true);
    if ((currentLength + ONE_CHARACTER) == maxLength && showBorder == true && counterChange_ == true && IsTextArea()) {
        if (!(currentBorderWidth == overCountBorderWidth)) {
            lastDiffBorderWidth_ = currentBorderWidth;
            layoutProperty->UpdateBorderWidth(overCountBorderWidth);
            renderContext->UpdateBorderWidth(overCountBorderWidth);
        }
        if (!(currentBorderColor == overCountBorderColor)) {
            lastDiffBorderColor_ = currentBorderColor;
            renderContext->UpdateBorderColor(overCountBorderColor);
        }
    }
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    if (focusIndex_ == FocuseIndex::CANCEL) {
        CleanNodeResponseKeyEvent();
        return;
    } else if (focusIndex_ == FocuseIndex::UNIT) {
        if (IsShowPasswordIcon()) {
            PasswordResponseKeyEvent();
        }
        if (IsShowUnit()) {
            UnitResponseKeyEvent();
        }
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "PerformAction  %{public}d", static_cast<int32_t>(action));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    TextFieldCommonEvent event;
    event.SetText(contentController_->GetTextValue());
    if (IsNormalInlineState() && action != TextInputAction::NEW_LINE) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        RecordSubmitEvent();
        eventHub->FireOnSubmit(static_cast<int32_t>(action), event);
        if (event.IsKeepEditable()) {
            return;
        }
        auto focusHub = host->GetOrCreateFocusHub();
        focusHub->LostFocus();
        return;
    }
    if (IsTextArea() && action == TextInputAction::NEW_LINE) {
        if (GetInputFilter() != "\n") {
            InsertValue("\n");
        }
        return;
    }
    eventHub->FireOnSubmit(static_cast<int32_t>(action), event);
    RecordSubmitEvent();
    if (event.IsKeepEditable()) {
        return;
    }
    CloseKeyboard(forceCloseKeyboard);
    FocusHub::LostFocusToViewRoot();
}

void TextFieldPattern::RecordSubmitEvent() const
{
    if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    bool isPwdType = layoutProperty ? layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) ==
                                          TextInputType::VISIBLE_PASSWORD
                                    : false;
    Recorder::EventParamsBuilder builder;
    builder.SetId(inspectorId)
        .SetType(host->GetTag())
        .SetEventType(Recorder::EventType::SEARCH_SUBMIT)
        .SetDescription(host->GetAutoEventParamValue(""));
    if (!isPwdType) {
        builder.SetText(contentController_->GetTextValue());
    }
    Recorder::EventRecorder::Get().OnEvent(std::move(builder));
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
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
    if (!RequestKeyboard(false, true, true)) {
        return;
    }
    NotifyOnEditChanged(true);
    needToRequestKeyboardInner_ = false;
}

void TextFieldPattern::OnVisibleChange(bool isVisible)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "visible change to %{public}d", isVisible);
    if (!isVisible && HasFocus()) {
        CloseKeyboard(true);
        if (SelectOverlayIsOn()) {
            StartTwinkling();
        }
    }
}

void TextFieldPattern::HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "Textfield handleSurface change, new width %{public}d, new height %{public}d, prev width %{public}d, prev "
        "height %{public}d",
        newWidth, newHeight, prevWidth, prevHeight);
    if (SelectOverlayIsOn()) {
        auto proxy = GetSelectOverlayProxy();
        proxy->ShowOrHiddenMenu(true);
        processOverlayDelayTask_ = [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ProcessOverlay(false);
        };
    }
    if (HasFocus() && IsSingleHandle()) {
        StartTwinkling();
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    UpdateCaretInfoToController();
}

void TextFieldPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY) const
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Textfield handleSurface position change, posX %{public}d, posY %{public}d",
        posX, posY);
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
        UpdateSurfacePositionChangedCallbackId(callbackId);
    }
}

void TextFieldPattern::HandleOnDelete(bool backward)
{
    if (backward) {
#if defined(PREVIEW)
        DeleteForward(GetGraphemeClusterLength(GetWideText(), GetCaretIndex()));
#else
        DeleteBackward(GetGraphemeClusterLength(GetWideText(), GetCaretIndex(), true));
#endif
    } else {
#if defined(PREVIEW)
        DeleteBackward(GetGraphemeClusterLength(GetWideText(), GetCaretIndex(), true));
#else
        DeleteForward(GetGraphemeClusterLength(GetWideText(), GetCaretIndex()));
#endif
    }
}

void TextFieldPattern::DeleteBackward(int32_t length)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    ResetObscureTickCountDown();
    if (IsSelected()) {
        Delete(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        return;
    }
    if (selectController_->GetCaretIndex() <= 0) {
        return;
    }
    inputOperations_.emplace(InputOperation::DELETE_BACKWARD);
    deleteBackwardOperations_.emplace(length);
    if (layoutProperty->HasMaxLength()) {
        if (layoutProperty->GetShowUnderlineValue(false) && !IsTextArea()) {
            auto textFieldTheme = GetTheme();
            CHECK_NULL_VOID(textFieldTheme);
            underlineColor_ = textFieldTheme->GetUnderlineColor();
        }
        counterChange_ = false;
        HandleCounterBorder();
    }
    CloseSelectOverlay();
    ScrollToSafeArea();
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::DeleteBackwardOperation(int32_t length)
{
    auto start = std::max(selectController_->GetCaretIndex() - length, 0);
    contentController_->erase(start, length);
    selectController_->UpdateCaretIndex(start);
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
}

void TextFieldPattern::DeleteForwardOperation(int32_t length)
{
    contentController_->erase(selectController_->GetCaretIndex(), length);
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsTextArea() && layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
}

void TextFieldPattern::DeleteForward(int32_t length)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Handle DeleteForward %{public}d characters", length);
    ResetObscureTickCountDown();
    if (IsSelected()) {
        Delete(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        return;
    }
    if (selectController_->GetCaretIndex() >= static_cast<int32_t>(contentController_->GetWideText().length())) {
        return;
    }
    inputOperations_.emplace(InputOperation::DELETE_FORWARD);
    deleteForwardOperations_.emplace(length);
    CloseSelectOverlay();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMaxLength()) {
        HandleCounterBorder();
    }
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Selection %{public}s, caret position %{public}d",
        selectController_->ToString().c_str(), selectController_->GetCaretIndex());
    ResetObscureTickCountDown();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    showSelect_ = IsSelected();
}

void TextFieldPattern::HandleSelectionUp()
{
    if (!IsTextArea()) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
    }
    auto newOffsetY = selectController_->GetCaretRect().GetY() - PreferredLineHeight() * 0.5 - textRect_.GetY();
    selectController_->MoveSecondHandleByKeyBoard(static_cast<int32_t>(
        paragraph_->GetGlyphIndexByCoordinate(Offset(selectController_->GetCaretRect().GetX(), newOffsetY))));
    AfterSelection();
}

void TextFieldPattern::HandleSelectionDown()
{
    if (!IsTextArea()) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
    }
    auto newOffsetY = selectController_->GetCaretRect().GetY() + PreferredLineHeight() * 1.5 - textRect_.GetY();
    selectController_->MoveSecondHandleByKeyBoard(static_cast<int32_t>(
        paragraph_->GetGlyphIndexByCoordinate(Offset(selectController_->GetCaretRect().GetX(), newOffsetY))));
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeft()
{
    if (!IsSelected()) {
        if (selectController_->GetCaretIndex() == 0) {
            return;
        }
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(
            selectController_->GetSecondHandleIndex() -
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetCaretIndex(), true));
    } else {
        selectController_->MoveSecondHandleByKeyBoard(
            selectController_->GetSecondHandleIndex() - GetGraphemeClusterLength(contentController_->GetWideText(),
                                                            selectController_->GetSecondHandleIndex(), true));
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeftWord()
{
    if (selectController_->GetCaretIndex() == 0) {
        return;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t leftWordLength = GetWordLength(selectController_->GetCaretIndex(), 0);
    if (leftWordLength < 0 || leftWordLength > textLength || selectController_->GetCaretIndex() - leftWordLength < 0) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(selectController_->GetSecondHandleIndex() - leftWordLength);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(selectController_->GetSecondHandleIndex() - leftWordLength);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLineBegin()
{
    if (selectController_->GetCaretIndex() == 0) {
        return;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    int32_t lineBeginPosition = GetLineBeginPosition(selectController_->GetCaretIndex());
    if (lineBeginPosition < 0 || lineBeginPosition > textLength) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(lineBeginPosition);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(lineBeginPosition);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionHome()
{
    if (selectController_->GetCaretIndex() == 0) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(0);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(0);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRight()
{
    // if currently not in select mode, reset baseOffset and move destinationOffset and caret position
    if (!IsSelected()) {
        if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetWideText().length())) {
            return;
        }
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(
            selectController_->GetSecondHandleIndex() +
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetSecondHandleIndex()));
    } else {
        // if currently not in select mode, move destinationOffset and caret position only
        selectController_->MoveSecondHandleByKeyBoard(
            selectController_->GetSecondHandleIndex() +
            GetGraphemeClusterLength(contentController_->GetWideText(), selectController_->GetSecondHandleIndex()));
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRightWord()
{
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (selectController_->GetCaretIndex() == textLength) {
        return;
    }
    int32_t rightWordLength = GetWordLength(selectController_->GetCaretIndex(), 1);
    if (rightWordLength < 0 || rightWordLength > textLength ||
        rightWordLength + selectController_->GetCaretIndex() > textLength) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(selectController_->GetSecondHandleIndex() + rightWordLength);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(selectController_->GetSecondHandleIndex() + rightWordLength);
        AfterSelection();
    }
}

void TextFieldPattern::HandleSelectionLineEnd()
{
    int32_t textLength = static_cast<int32_t>(contentController_->GetWideText().length());
    if (selectController_->GetCaretIndex() == textLength) {
        return;
    }
    int32_t lineEndPosition = GetLineEndPosition(selectController_->GetCaretIndex());
    if (lineEndPosition < 0 || lineEndPosition > textLength) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(lineEndPosition);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(lineEndPosition);
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionEnd()
{
    // shift end, select to the end of current line
    int32_t endPos = static_cast<int32_t>(contentController_->GetWideText().length());
    if (selectController_->GetCaretIndex() == endPos) {
        return;
    }
    if (!IsSelected()) {
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(endPos);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(endPos);
    }
    AfterSelection();
}

void TextFieldPattern::SetCaretPosition(int32_t position)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Set caret position to %{public}d", position);
    selectController_->MoveCaretToContentRect(position, TextAffinity::DOWNSTREAM);
    if (HasFocus() && !GetShowMagnifier()) {
        StartTwinkling();
    }
    CloseSelectOverlay();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::SetSelectionFlag(int32_t selectionStart, int32_t selectionEnd)
{
    if (!HasFocus()) {
        return;
    }
    if (selectionStart == selectionEnd) {
        selectController_->MoveCaretToContentRect(selectionEnd, TextAffinity::DOWNSTREAM);
        StartTwinkling();
    } else {
        cursorVisible_ = false;
        showSelect_ = true;
        HandleSetSelection(selectionStart, selectionEnd, false);
        selectController_->MoveFirstHandleToContentRect(selectionStart);
        selectController_->MoveSecondHandleToContentRect(selectionEnd);
    }
    if (RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::OnBackPressed()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Textfield %{public}d receives back press event", tmpHost->GetId());
    if (SelectOverlayIsOn()) {
        selectController_->UpdateCaretIndex(
            std::max(selectController_->GetFirstHandleIndex(), selectController_->GetSecondHandleIndex()));
        auto selectOverlayProxy = GetSelectOverlayProxy();
        CHECK_NULL_RETURN(selectOverlayProxy, false);
        bool closeKeyboard = !selectOverlayProxy->IsMenuShow();
        CloseSelectOverlay();
        StartTwinkling();
        if (!closeKeyboard) {
            return true;
        }
    }
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (!imeShown_ && !isCustomKeyboardAttached_) {
#else
    if (!isCustomKeyboardAttached_) {
#endif
        return false;
    }

    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    CloseKeyboard(true);
    FocusHub::LostFocusToViewRoot();
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
        case TextInputType::USER_NAME:
            return "InputType.USER_NAME";
        case TextInputType::NEW_PASSWORD:
            return "InputType.NEW_PASSWORD";
        default:
            return "InputType.Normal";
    }
}

std::string TextFieldPattern::TextInputActionToString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    switch (GetTextInputActionValue(GetDefaultTextInputAction())) {
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
    auto theme = GetTheme();
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
    auto context = PipelineBase::GetCurrentContext();
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
        OnParentScrollStartOrEnd(false);
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

void TextFieldPattern::AddCounterNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto counterNode = DynamicCast<UINode>(counterTextNode_.Upgrade());
    if (counterNode && (IsShowPasswordIcon() || IsNormalInlineState())) {
        CleanCounterNode();
        return;
    }
    if (!counterNode) {
        auto counterTextNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        counterTextNode_ = counterTextNode;
        counterTextNode->MountToParent(host);
        counterTextNode->MarkModifyDone();
        counterTextNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
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
    auto passWordMode = IsInPasswordMode();
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto renderContext = tmpHost->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto visible = layoutProperty->GetShowErrorTextValue(false);
    auto errorText = layoutProperty->GetErrorTextValue("");

    if (visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()
        && !errorText.empty()) {
        underlineColor_ = textFieldTheme->GetErrorUnderlineColor();
        underlineWidth_ = ERROR_UNDERLINE_WIDTH;
        preErrorState_ = true;
    }
    if (!visible && layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        underlineColor_ = textFieldTheme->GetUnderlineColor();
        underlineWidth_ = UNDERLINE_WIDTH;
        preErrorState_ = false;
    }
    if (visible && passWordMode && !errorText.empty()) {
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
    if (visible && (!passWordMode || errorText.empty())) {
        layoutProperty->UpdateBorderWidth(passwordModeStyle_.borderwidth);
        renderContext->UpdateBorderColor(passwordModeStyle_.borderColor);
        renderContext->UpdateBackgroundColor(passwordModeStyle_.bgColor);
        layoutProperty->UpdateTextColor(passwordModeStyle_.textColor);
        preErrorState_ = true;
    }
    UpdateErrorTextMargin();
}

void TextFieldPattern::CreateErrorParagraph(const std::string& content)
{
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    TextStyle errorTextStyle = theme->GetErrorTextStyle();
    std::string errorText = content;
    ParagraphStyle paraStyle { .align = TextAlign::START,
        .maxLines = 1,
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .textOverflow = TextOverflow::ELLIPSIS,
        .fontSize = errorTextStyle.GetFontSize().ConvertToPx() };
    errorParagraph_ = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_VOID(errorParagraph_);
    errorParagraph_->PushStyle(errorTextStyle);
    StringUtils::TransformStrCase(errorText, static_cast<int32_t>(errorTextStyle.GetTextCase()));
    errorParagraph_->AddText(StringUtils::Str8ToStr16(errorText));
    errorParagraph_->Build();
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
    auto errorText = layoutProperty->GetErrorTextValue("");
    if (layoutProperty->GetShowErrorTextValue(false) && !IsNormalInlineState() && !errorText.empty()) {
        CreateErrorParagraph(errorText);
        if (errorParagraph_) {
            errorParagraph_->Layout(std::numeric_limits<double>::infinity());
            auto errorTextMargin = ERROR_TEXT_TOP_MARGIN.ConvertToPx() +
                ERROR_TEXT_BOTTOM_MARGIN.ConvertToPx() + errorParagraph_->GetHeight();
            if (preErrorMargin_ < errorTextMargin) {
                errorMargin.bottom = CalcLength(errorTextMargin);
            }
        }
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
    auto textFieldTheme = GetTheme();
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
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    }
    CalcSize idealSize;
    layoutProperty->UpdatePadding({ CalcLength(UNDERLINE_NORMAL_PADDING), CalcLength(UNDERLINE_NORMAL_PADDING),
        CalcLength(0.0_vp), CalcLength(0.0_vp) });
    ProcessInnerPadding();
    if (layoutProperty->GetPropertyChangeFlag() == PROPERTY_UPDATE_NORMAL) {
        std::optional<CalcLength> height(UNDERLINE_NORMAL_HEIGHT);
        idealSize.SetHeight(height);
        layoutProperty->UpdateUserDefinedIdealSize(idealSize);
    }
    if (!layoutProperty->HasFontSize()) {
        layoutProperty->UpdateFontSize(theme->GetUnderlineFontSize());
    }
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
    if (showImageSource && !showImageSource->GetSrc().empty()) {
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
    if (hideSourceInfo && !hideSourceInfo->GetSrc().empty()) {
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
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
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
                                 static_cast<float>(theme->GetCursorWidth().ConvertToPx()) - inputContentWidth);
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

void TextFieldPattern::UpdateRectByTextAlign(RectF& rect)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->HasTextAlign()) {
        return;
    }
    switch (layoutProperty->GetTextAlignValue(TextAlign::START)) {
        case TextAlign::START:
            return;
        case TextAlign::CENTER:
            rect.SetLeft(rect.GetOffset().GetX() + (contentRect_.Width() - textRect_.Width()) * 0.5f);
            return;
        case TextAlign::END:
            rect.SetLeft(rect.GetOffset().GetX() + (contentRect_.Width() - textRect_.Width()));
            return;
        default:
            return;
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
    auto theme = GetTheme();
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
    layoutProperty->UpdatePadding({ CalcLength(0.0f), CalcLength(0.0f), CalcLength(0.0f), CalcLength(0.0f) });
    ProcessInnerPadding();
    textRect_.SetLeft(GetPaddingLeft() + GetBorderLeft());
    textRect_.SetTop(GetPaddingTop() + GetBorderTop());
    MarginProperty margin;
    margin.bottom =
        CalcLength(inlineState_.padding.bottom->GetDimension() + inlineState_.margin.bottom->GetDimension());
    margin.right = CalcLength(inlineState_.padding.right->GetDimension() + inlineState_.margin.right->GetDimension());
    margin.left = CalcLength(inlineState_.padding.left->GetDimension() + inlineState_.margin.left->GetDimension());
    margin.top = CalcLength(inlineState_.padding.top->GetDimension() + inlineState_.margin.top->GetDimension());
    layoutProperty->UpdateMargin(margin);
    if (!IsTextArea()) {
        layoutProperty->UpdatePlaceholderMaxLines(layoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE));
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
    auto inputType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    return inputType == TextInputType::VISIBLE_PASSWORD || inputType == TextInputType::NUMBER_PASSWORD ||
           inputType == TextInputType::SCREEN_LOCK_PASSWORD || inputType == TextInputType::NEW_PASSWORD;
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
    ProcessInnerPadding();
    if (layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType()) {
        ApplyUnderlineStates();
    }
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
    json->Put("caretPosition", std::to_string(GetCaretIndex()).c_str());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto jsonShowCounter = JsonUtil::Create(true);
    jsonShowCounter->Put("value", layoutProperty->GetShowCounterValue(false));
    auto jsonShowCounterOptions = JsonUtil::Create(true);
    auto counterType = layoutProperty->GetSetCounterValue(DEFAULT_MODE);
    auto showBorder = layoutProperty->GetShowHighlightBorderValue(true);
    jsonShowCounterOptions->Put("thresholdPercentage", counterType);
    jsonShowCounterOptions->Put("highlightBorder", showBorder);
    jsonShowCounter->Put("options", jsonShowCounterOptions);
    json->Put("showCounter", jsonShowCounter);
}

void TextFieldPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdatePlaceholder(json->GetString("placeholder"));
    UpdateEditingValue(json->GetString("text"), StringUtils::StringToInt(json->GetString("caretPosition")));
    FireOnTextChangeEvent();
    UpdateSelection(GetCaretIndex());
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
                // AccessibilityEventType::SCROLL_END
                return;
            }
            pattern->OnTextAreaScroll(-offset);
            // AccessibilityEventType::SCROLL_END
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
                // AccessibilityEventType::SCROLL_END
                return;
            }
            pattern->OnTextAreaScroll(offset);
            // AccessibilityEventType::SCROLL_END
        }
    });
}

void TextFieldPattern::StopEditing()
{
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::CheckHandleVisible(const RectF& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    // use global offset.
    RectF visibleContentRect(contentRect_.GetOffset() + parentGlobalOffset_, contentRect_.GetSize());
    auto parent = host->GetAncestorNodeOfFrame();
    visibleContentRect = GetVisibleContentRect(parent, visibleContentRect);
    if (!IsTextArea()) {
        auto verticalEpsilon = std::max(0.0f, paintRect.Height() - contentRect_.Height());
        return GreatOrEqual(paintRect.Top() + verticalEpsilon, visibleContentRect.Top()) &&
               LessOrEqual(paintRect.Bottom() - verticalEpsilon, visibleContentRect.Bottom()) &&
               LessOrEqual(paintRect.Left(), visibleContentRect.Right()) &&
               GreatOrEqual(paintRect.Right(), visibleContentRect.Left());
    }
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintRect.Left(), paintRect.Top() + BOX_EPSILON };
    return visibleContentRect.IsInRegion(bottomPoint) && visibleContentRect.IsInRegion(topPoint);
}

void TextFieldPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("HasFocus:").append(std::to_string(HasFocus())));
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::TextConfig textConfig = miscTextConfig.value();
    DumpLog::GetInstance().AddDesc(std::string("RequestKeyboard calling window :")
                                       .append(std::to_string(textConfig.windowId))
                                       .append(std::string("inputType:"))
                                       .append(std::to_string(textConfig.inputAttribute.inputPattern)));
#endif
    DumpLog::GetInstance().AddDesc(textSelector_.ToString());
    if (customKeyboardBuilder_) {
        DumpLog::GetInstance().AddDesc(std::string("CustomKeyboard: true")
                                           .append(", Attached: ")
                                           .append(std::to_string(isCustomKeyboardAttached_)));
    }
}

void TextFieldPattern::DumpAdvanceInfo()
{
    if (customKeyboardBuilder_) {
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

void TextFieldPattern::DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap)
{
    CHECK_NULL_VOID(viewDataWrap);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto autoFillType = ConvertToAceAutoFillType(layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
    auto info = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    CHECK_NULL_VOID(info);
    info->SetId(host->GetId());
    info->SetDepth(host->GetDepth());
    info->SetAutoFillType(autoFillType);
    info->SetTag(host->GetTag());
    info->SetValue(contentController_->GetTextValue());
    info->SetPlaceholder(GetPlaceHolder());
    info->SetPasswordRules(layoutProperty->GetPasswordRulesValue(""));
    info->SetEnableAutoFill(layoutProperty->GetEnableAutoFillValue(true));
    viewDataWrap->AddPageNodeInfoWrap(info);
}

void TextFieldPattern::NotifyFillRequestSuccess(RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "autoFillType:%{public}d", static_cast<int32_t>(autoFillType));
    CHECK_NULL_VOID(nodeWrap);
    if (!contentController_ || contentController_->GetTextValue() == nodeWrap->GetValue()) {
        return;
    }
    contentController_->SetTextValue(nodeWrap->GetValue());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    NotifyOnEditChanged(true);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto type = ConvertToAceAutoFillType(layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
    if (!(type == AceAutoFillType::ACE_NEW_PASSWORD && type == autoFillType)) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "Set last auto fill text value.");
        lastAutoFillPasswordTextValue_ = nodeWrap->GetValue();
    }
}

void TextFieldPattern::NotifyFillRequestFailed(int32_t errCode)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "errCode:%{public}d", errCode);
    if (errCode == AUTO_FILL_FAILED) {
        return;
    }
    if (RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::CheckAutoSave()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (!layoutProperty->GetEnableAutoFillValue(true)) {
        return false;
    }
    if (!contentController_ || contentController_->GetTextValue().empty()) {
        return false;
    }
    auto autoFillType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    if (autoFillType == TextInputType::USER_NAME) {
        if (!lastAutoFillPasswordTextValue_.empty() &&
            contentController_->GetTextValue() != lastAutoFillPasswordTextValue_) {
            return true;
        }
    }
    if ((autoFillType == TextInputType::VISIBLE_PASSWORD || autoFillType == TextInputType::NEW_PASSWORD)) {
        if (contentController_->GetTextValue() != lastAutoFillPasswordTextValue_) {
            return true;
        }
    }
    return false;
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

bool TextFieldPattern::RepeatClickCaret(const Offset& offset, int32_t lastCaretIndex, const RectF& lastCaretRect)
{
    auto touchDownIndex = selectController_->ConvertTouchOffsetToPosition(offset);
    if (!selectController_->CaretAtLast()) {
        return lastCaretIndex == touchDownIndex && HasFocus();
    }
    // Increase the cursor area if there is no text
    auto caretRect = lastCaretRect;
    caretRect.SetLeft(caretRect.GetX() - caretRect.Height() / 2);
    caretRect.SetWidth(caretRect.Height());
    return caretRect.IsInRegion(PointF(offset.GetX(), offset.GetY()));
}

bool TextFieldPattern::IsSingleHandle() const
{
    return contentController_->IsEmpty() || !IsSelected();
}

void TextFieldPattern::OnAttachToFrameNode()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCopyOptions(CopyOptions::Distributed);
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
    auto caretInfo = selectController_->GetCaretInfo();
    if (!IsSelected()) {
        if (!firstHandle.has_value() || !secondHandle.has_value()) {
            paintProperty->UpdateFirstHandleInfo(caretInfo);
            paintProperty->UpdateSecondHandleInfo(caretInfo);
            return false;
        }

        if (firstHandle->index != secondHandle->index || firstHandle->index != caretInfo.index) {
            paintProperty->UpdateFirstHandleInfo(caretInfo);
            paintProperty->UpdateSecondHandleInfo(caretInfo);
            return true;
        }
        return false;
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
        return;
    }
    operationRecords_.back().caretPosition = index;
}

void TextFieldPattern::OnObscuredChanged(bool isObscured)
{
    ResetObscureTickCountDown();
    obscuredChange_ = textObscured_ != isObscured;
    textObscured_ = isObscured;
    CloseSelectOverlay(false);
    selectController_->UpdateCaretIndex(static_cast<int32_t>(contentController_->GetWideText().length()));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::CreateHandles()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    showSelect_ = true;
    ProcessOverlay(true, false, false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    return paragraph_ ? paragraph_->GetLineCount() : 0;
}

void TextFieldPattern::UpdateHandlesOffsetOnScroll(float offset)
{
    if (SelectOverlayIsOn()) {
        selectController_->UpdateSecondHandleOffset();
        if (!IsSingleHandle()) {
            selectController_->UpdateFirstHandleOffset();
            selectController_->UpdateCaretOffset();
            UpdateSelectOverlayDoubleHandle();
        } else {
            auto carectOffset = selectController_->GetCaretRect().GetOffset() +
                                (IsTextArea() ? OffsetF(0.0f, offset) : OffsetF(offset, 0.0f));
            selectController_->UpdateCaretOffset(carectOffset);
            UpdateSelectOverlaySecondHandle();
        }
    } else {
        auto caretOffset = selectController_->GetCaretRect().GetOffset() +
                           (IsTextArea() ? OffsetF(0.0f, offset) : OffsetF(offset, 0.0f));
        selectController_->UpdateCaretOffset(caretOffset);
    }
}

void TextFieldPattern::CloseHandleAndSelect()
{
    CloseSelectOverlay(true);
    showSelect_ = false;
}

bool TextFieldPattern::IsShowUnit() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowUnderlineValue(false) &&
           layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) == TextInputType::UNSPECIFIED;
}

bool TextFieldPattern::IsShowPasswordIcon() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowPasswordIconValue(true) && IsInPasswordMode();
}

bool TextFieldPattern::IsShowCancelButtonMode() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return !IsNormalInlineState() && !IsTextArea() && layoutProperty->GetIsShowCancelButton().value_or(false);
}

void TextFieldPattern::ProcessResponseArea()
{
    if (cleanNodeResponseArea_) {
        cleanNodeResponseArea_->ClearArea();
        cleanNodeResponseArea_.Reset();
    }
    if (IsShowCancelButtonMode()) {
        cleanNodeResponseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(WeakClaim(this));
        cleanNodeResponseArea_->InitResponseArea();
        UpdateCancelNode();
    }

    if (IsShowPasswordIcon()) {
        auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea_);
        if (passwordArea) {
            passwordArea->Refresh();
            return;
        }
        responseArea_ = AceType::MakeRefPtr<PasswordResponseArea>(WeakClaim(this), GetTextObscured());
        responseArea_->InitResponseArea();
        return;
    }

    if (IsShowUnit()) {
        responseArea_ = AceType::MakeRefPtr<UnitResponseArea>(WeakClaim(this), unitNode_);
        responseArea_->InitResponseArea();
        return;
    }

    if (responseArea_) {
        responseArea_->ClearArea();
    }
}

void TextFieldPattern::UpdateCancelNode()
{
    auto cleanNodeResponseArea = DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
    CHECK_NULL_VOID(cleanNodeResponseArea);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cleanNodeStyle = layoutProperty->GetCleanNodeStyle().value_or(CleanNodeStyle::INPUT);
    if (cleanNodeStyle == CleanNodeStyle::CONSTANT ||
        (cleanNodeStyle == CleanNodeStyle::INPUT && !contentController_->IsEmpty())) {
        if (!cleanNodeResponseArea->IsShow()) {
            cleanNodeResponseArea->UpdateCleanNode(true);
        }
    } else if (cleanNodeStyle == CleanNodeStyle::INVISIBLE ||
               (cleanNodeStyle == CleanNodeStyle::INPUT && contentController_->IsEmpty())) {
        if (cleanNodeResponseArea->IsShow()) {
            cleanNodeResponseArea->UpdateCleanNode(false);
        }
    }
}

bool TextFieldPattern::HasInputOperation()
{
    return !deleteBackwardOperations_.empty() || !deleteForwardOperations_.empty() || !insertValueOperations_.empty();
}

bool TextFieldPattern::UpdateFocusForward()
{
    if (focusIndex_ == FocuseIndex::TEXT && HasFocus()) {
        if (!CancelNodeIsShow() && responseArea_ == nullptr) {
            return false;
        }
        if (!CancelNodeIsShow()) {
            focusIndex_ = FocuseIndex::UNIT;
            PaintResponseAreaRect();
            return true;
        }
        focusIndex_ = FocuseIndex::CANCEL;
        PaintCancelRect();
        return true;
    } else if (focusIndex_ == FocuseIndex::CANCEL && HasFocus()) {
        if (responseArea_ == nullptr) {
            return false;
        }
        focusIndex_ = FocuseIndex::UNIT;
        PaintResponseAreaRect();
        return true;
    }
    return false;
}

bool TextFieldPattern::UpdateFocusBackward()
{
    if (focusIndex_ == FocuseIndex::CANCEL && HasFocus()) {
        focusIndex_ = FocuseIndex::TEXT;
        PaintTextRect();
        return true;
    } else if (focusIndex_ == FocuseIndex::UNIT && HasFocus()) {
        if (!CancelNodeIsShow()) {
            focusIndex_ = FocuseIndex::TEXT;
            PaintTextRect();
            return true;
        }
        focusIndex_ = FocuseIndex::CANCEL;
        PaintCancelRect();
        return true;
    }
    return false;
}

bool TextFieldPattern::HandleSpaceEvent()
{
    if (focusIndex_ == FocuseIndex::CANCEL) {
        CleanNodeResponseKeyEvent();
        return true;
    } else if (focusIndex_ == FocuseIndex::UNIT) {
        if (IsShowPasswordIcon()) {
            PasswordResponseKeyEvent();
        }
        if (IsShowUnit()) {
            UnitResponseKeyEvent();
        }
        return true;
    }
    return false;
}

void TextFieldPattern::PaintTextRect()
{
    RoundRect focusRect;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
}

void TextFieldPattern::GetIconPaintRect(const RefPtr<TextInputResponseArea>& responseArea, RoundRect& paintRect)
{
    auto stackNode = responseArea->GetFrameNode();
    CHECK_NULL_VOID(stackNode);
    auto stackRect = stackNode->GetGeometryNode()->GetFrameRect();
    auto imageNode = stackNode->GetFirstChild();
    CHECK_NULL_VOID(imageNode);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(imageNode);
    CHECK_NULL_VOID(imageFrameNode);
    auto imageRect = imageFrameNode->GetGeometryNode()->GetFrameRect();
    RectF rect(stackRect.GetX(), imageRect.GetY(), imageRect.Width(), imageRect.Height());
    paintRect.SetRect(rect);
}

void TextFieldPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    if (focusIndex_ == FocuseIndex::CANCEL) {
        CHECK_NULL_VOID(cleanNodeResponseArea_);
        GetIconPaintRect(cleanNodeResponseArea_, paintRect);
    } else if (focusIndex_ == FocuseIndex::UNIT) {
        if (IsShowPasswordIcon()) {
            CHECK_NULL_VOID(responseArea_);
            GetIconPaintRect(responseArea_, paintRect);
        }
        if (IsShowUnit()) {
            CHECK_NULL_VOID(responseArea_);
            auto unitResponseArea = AceType::DynamicCast<UnitResponseArea>(responseArea_);
            CHECK_NULL_VOID(unitResponseArea);
            auto unitNode = unitResponseArea->GetFrameNode();
            CHECK_NULL_VOID(unitNode);
            auto unitRect = unitNode->GetGeometryNode()->GetFrameRect();
            paintRect.SetRect(unitRect);
        }
    }
}

void TextFieldPattern::PaintCancelRect()
{
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
}

void TextFieldPattern::PaintResponseAreaRect()
{
    if (IsShowPasswordIcon()) {
        PaintPasswordRect();
    }
    if (IsShowUnit()) {
        PaintUnitRect();
    }
}

void TextFieldPattern::PaintPasswordRect()
{
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
}

void TextFieldPattern::PaintUnitRect()
{
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
}

void TextFieldPattern::CleanNodeResponseKeyEvent()
{
    ClearEditingValue();
}

void TextFieldPattern::PasswordResponseKeyEvent()
{
    auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea_);
    CHECK_NULL_VOID(passwordArea);
    passwordArea->OnPasswordIconClicked();
}

void TextFieldPattern::UnitResponseKeyEvent()
{
    auto unitArea = AceType::DynamicCast<UnitResponseArea>(responseArea_);
    CHECK_NULL_VOID(unitArea);
    auto frameNode = unitArea->GetFrameNode();
    if (frameNode->GetTag() == V2::SELECT_ETS_TAG) {
        auto selectPattern = frameNode->GetPattern<SelectPattern>();
        CHECK_NULL_VOID(selectPattern);
        selectPattern->ShowSelectMenu();
    }
}

void TextFieldPattern::ScrollToSafeArea() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->ScrollTextFieldToSafeArea();
}

RefPtr<PixelMap> TextFieldPattern::GetPixelMap()
{
    auto context = GetHost()->GetRenderContext();
    if (!context) {
        UpdateShowMagnifier();
    }
    CHECK_NULL_RETURN(context, NULL);
    auto pixelMap = context->GetThumbnailPixelMap();
    if (!pixelMap) {
        UpdateShowMagnifier();
    }
    CHECK_NULL_RETURN(pixelMap, NULL);
    return pixelMap;
}

void TextFieldPattern::ShowMenu()
{
    auto selectOverlayProxy = GetSelectOverlayProxy();
    if (selectOverlayProxy && selectOverlayProxy->IsMenuShow()) {
        return;
    }
    CloseSelectOverlay(true);
    if (IsSingleHandle()) {
        SetIsSingleHandle(true);
    } else {
        SetIsSingleHandle(false);
    }
    ProcessOverlay(true, true, true);
}

void TextFieldPattern::HandleCursorOnDragMoved(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    if (IsNormalInlineState()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (isCursorAlwaysDisplayed_) {
        if (SystemProperties::GetDebugEnabled()) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
                "In OnDragMoved, the cursor has always Displayed in the textField, id:%{public}d", host->GetId());
        }
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "In OnDragMoved, the dragging node is moving in the textField, id:%{public}d",
        host->GetId());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
    isCursorAlwaysDisplayed_ = true;
    StartTwinkling();
};

void TextFieldPattern::HandleCursorOnDragLeaved(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "In OnDragLeaved, the dragging node has left from the textField, id:%{public}d",
        host->GetId());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->LostFocus();
    isCursorAlwaysDisplayed_ = false;
    StopTwinkling();
};

void TextFieldPattern::HandleCursorOnDragEnded(const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!isCursorAlwaysDisplayed_) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "In OnDragEnded,"
            " the released location is not in the current textField, id:%{public}d",
            host->GetId());
        focusHub->LostFocus();
        StopTwinkling();
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "In OnDragEnded, the released location is in the current TextField, id:%{public}d", host->GetId());
    focusHub->RequestFocusImmediately();
    isCursorAlwaysDisplayed_ = false;
    StartTwinkling();
};

void TextFieldPattern::HandleOnDragStatusCallback(
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

void TextFieldPattern::RequestKeyboardAfterLongPress()
{
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (isLongPress_ && HasFocus() && RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
    isLongPress_ = false;
#endif
}

void TextFieldPattern::NotifyKeyboardInfo(const KeyBoardInfo& info)
{
    if (!HasFocus()) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    textFieldManager->SetImeShow(info.visible);
}

void TextFieldPattern::GetCaretMetrics(CaretMetricsF& caretCaretMetric)
{
    OffsetF offset = selectController_->GetCaretRect().GetOffset();
    float height = selectController_->GetCaretRect().Height();
    float width = selectController_->GetCaretRect().Width();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textPaintOffset = host->GetPaintRectOffset();
    caretCaretMetric.offset = offset + textPaintOffset + OffsetF(width / 2.0f, 0.0f);
    caretCaretMetric.height = height;
}
} // namespace OHOS::Ace::NG
