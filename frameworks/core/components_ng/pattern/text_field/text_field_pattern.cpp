/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include <ratio>
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
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_select_overlay.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint_property.h"
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
#include "parameters.h"
#endif
#endif
#include "core/common/udmf/udmf_client.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"
#endif
namespace OHOS::Ace::NG {
namespace {

const BorderRadiusProperty ZERO_BORDER_RADIUS_PROPERTY(0.0_vp);
// need to be moved to TextFieldTheme
constexpr Dimension BORDER_DEFAULT_WIDTH = 0.0_vp;
constexpr Dimension TYPING_UNDERLINE_WIDTH = 2.0_px;
constexpr Dimension OVER_COUNT_BORDER_WIDTH = 1.0_vp;
constexpr Dimension INLINE_BORDER_WIDTH = 2.0_vp;
constexpr Dimension ERROR_UNDERLINE_WIDTH = 2.0_px;
constexpr Dimension UNDERLINE_WIDTH = 1.0_px;
constexpr uint32_t INLINE_DEFAULT_VIEW_MAXLINE = 3;
constexpr Dimension SCROLL_BAR_MIN_HEIGHT = 4.0_vp;
#if defined(ENABLE_STANDARD_INPUT)
constexpr Dimension AVOID_OFFSET = 24.0_vp;
#endif
constexpr Dimension DEFAULT_FONT = Dimension(16, DimensionUnit::FP);
constexpr Dimension COUNTER_BOTTOM = 22.0_vp;
constexpr double BOTTOM_MARGIN = 22.0;
constexpr float MARGIN_ZERO = 0.0f;
constexpr int32_t ILLEGAL_VALUE = 0;
constexpr float DOUBLECLICK_INTERVAL_MS = 300.0f;
constexpr float DOUBLECLICK_MIN_INTERVAL_MS = 0.0f;
constexpr Dimension DOUBLECLICK_DISTANCE = 15.0_vp;
constexpr double VELOCITY = -1000;
constexpr double MASS = 1.0;
constexpr double STIFFNESS = 428.0;
constexpr double DAMPING = 10.0;
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr uint32_t OBSCURE_SHOW_TICKS = 1;
constexpr Dimension ERROR_TEXT_TOP_MARGIN = 8.0_vp;
constexpr Dimension ERROR_TEXT_BOTTOM_MARGIN = 8.0_vp;
constexpr uint32_t FIND_TEXT_ZERO_INDEX = 1;
constexpr char16_t OBSCURING_CHARACTER = u'•';
constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*';
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
constexpr int32_t AUTO_FILL_FAILED = 1;
#if defined(ENABLE_STANDARD_INPUT)
constexpr int32_t AUTO_FILL_CANCEL = 2;
#endif

// need to be moved to formatter
const std::string DIGIT_WHITE_LIST = "[0-9]";
const std::string PHONE_WHITE_LIST = "[\\d\\-\\+\\*\\#]+";
const std::string EMAIL_WHITE_LIST = "[\\w.\\@]";
const std::string URL_WHITE_LIST = "[a-zA-z]+://[^\\s]*";
const std::string SHOW_PASSWORD_SVG = "SYS_SHOW_PASSWORD_SVG";
const std::string HIDE_PASSWORD_SVG = "SYS_HIDE_PASSWORD_SVG";
const std::string AUTO_FILL_TEST = "persist.sys.arkui.auto.fill.input.method.enabled";
const std::string AUTO_FILL_PARAMS_USERNAME = "com.autofill.params.userName";
const std::string AUTO_FILL_PARAMS_NEWPASSWORD = "com.autofill.params.newPassword";
constexpr int32_t DEFAULT_MODE = -1;
constexpr int32_t PREVIEW_TEXT_RANGE_DEFAULT = -1;
const std::string PREVIEW_STYLE_NORMAL = "normal";
const std::string PREVIEW_STYLE_UNDERLINE = "underline";

constexpr int32_t PREVIEW_NO_ERROR = 0;
constexpr int32_t PREVIEW_NULL_POINTER = 1;
constexpr int32_t PREVIEW_BAD_PARAMETERS = -1;
constexpr double MINIMAL_OFFSET = 0.01f;

static std::unordered_map<TextContentType, std::pair<AceAutoFillType, std::string>> contentTypeMap_ = {
    {TextContentType::VISIBLE_PASSWORD,
        std::make_pair(AceAutoFillType::ACE_PASSWORD, "TextContentType.VISIBLE_PASSWORD")},
    {TextContentType::USER_NAME, std::make_pair(AceAutoFillType::ACE_USER_NAME, "TextContentType.USER_NAME")},
    {TextContentType::NEW_PASSWORD, std::make_pair(AceAutoFillType::ACE_NEW_PASSWORD, "TextContentType.NEW_PASSWORD")},
    {TextContentType::FULL_STREET_ADDRESS,
        std::make_pair(AceAutoFillType::ACE_FULL_STREET_ADDRESS, "TextContentType.FULL_STREET_ADDRESS")},
    {TextContentType::HOUSE_NUMBER, std::make_pair(AceAutoFillType::ACE_HOUSE_NUMBER, "TextContentType.HOUSE_NUMBER")},
    {TextContentType::DISTRICT_ADDRESS,
        std::make_pair(AceAutoFillType::ACE_DISTRICT_ADDRESS, "TextContentType.DISTRICT_ADDRESS")},
    {TextContentType::CITY_ADDRESS, std::make_pair(AceAutoFillType::ACE_CITY_ADDRESS, "TextContentType.CITY_ADDRESS")},
    {TextContentType::PROVINCE_ADDRESS,
        std::make_pair(AceAutoFillType::ACE_PROVINCE_ADDRESS, "TextContentType.PROVINCE_ADDRESS")},
    {TextContentType::COUNTRY_ADDRESS,
        std::make_pair(AceAutoFillType::ACE_COUNTRY_ADDRESS, "TextContentType.COUNTRY_ADDRESS")},
    {TextContentType::PERSON_FULL_NAME,
        std::make_pair(AceAutoFillType::ACE_PERSON_FULL_NAME, "TextContentType.PERSON_FULL_NAME")},
    {TextContentType::PERSON_LAST_NAME,
        std::make_pair(AceAutoFillType::ACE_PERSON_LAST_NAME, "TextContentType.PERSON_LAST_NAME")},
    {TextContentType::PERSON_FIRST_NAME,
        std::make_pair(AceAutoFillType::ACE_PERSON_FIRST_NAME, "TextContentType.PERSON_FIRST_NAME")},
    {TextContentType::PHONE_NUMBER, std::make_pair(AceAutoFillType::ACE_PHONE_NUMBER, "TextContentType.PHONE_NUMBER")},
    {TextContentType::PHONE_COUNTRY_CODE,
        std::make_pair(AceAutoFillType::ACE_PHONE_COUNTRY_CODE, "TextContentType.PHONE_COUNTRY_CODE")},
    {TextContentType::FULL_PHONE_NUMBER,
        std::make_pair(AceAutoFillType::ACE_FULL_PHONE_NUMBER, "TextContentType.FULL_PHONE_NUMBER")},
    {TextContentType::EMAIL_ADDRESS,
        std::make_pair(AceAutoFillType::ACE_EMAIL_ADDRESS, "TextContentType.EMAIL_ADDRESS")},
    {TextContentType::BANK_CARD_NUMBER,
        std::make_pair(AceAutoFillType::ACE_BANK_CARD_NUMBER, "TextContentType.BANK_CARD_NUMBER")},
    {TextContentType::ID_CARD_NUMBER,
        std::make_pair(AceAutoFillType::ACE_ID_CARD_NUMBER, "TextContentType.ID_CARD_NUMBER")},
    {TextContentType::PRECISE_TIME, std::make_pair(AceAutoFillType::ACE_PRECISE_TIME, "TextContentType.PRECISE_TIME")},
    {TextContentType::HOUR_AND_MINUTE,
        std::make_pair(AceAutoFillType::ACE_HOUR_AND_MINUTE, "TextContentType.HOUR_AND_MINUTE")},
    {TextContentType::DATE, std::make_pair(AceAutoFillType::ACE_DATE, "TextContentType.DATE")},
    {TextContentType::MONTH, std::make_pair(AceAutoFillType::ACE_MONTH, "TextContentType.MONTH")},
    {TextContentType::YEAR, std::make_pair(AceAutoFillType::ACE_YEAR, "TextContentType.YEAR")},
    {TextContentType::NICKNAME, std::make_pair(AceAutoFillType::ACE_NICKNAME, "TextContentType.NICKNAME")},
    {TextContentType::DETAIL_INFO_WITHOUT_STREET,
        std::make_pair(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET, "TextContentType.DETAIL_INFO_WITHOUT_STREET")},
    {TextContentType::FORMAT_ADDRESS,
        std::make_pair(AceAutoFillType::ACE_FORMAT_ADDRESS, "TextContentType.FORMAT_ADDRESS")},
    {TextContentType::UNSPECIFIED, std::make_pair(AceAutoFillType::ACE_UNSPECIFIED, "TextContentType.UNSPECIFIED")}};

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

void TextFieldPattern::OnAttachContext(PipelineContext* context)
{
    CHECK_NULL_VOID(context);
    SetInstanceId(context->GetInstanceId());
}

void TextFieldPattern::OnDetachContext(PipelineContext* context)
{
    SetInstanceId(INSTANCE_ID_UNDEFINED);
}

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
        RectF boundsRect(contentOffset.GetX(), frameOffset.GetY(), errorTextWidth,
            errorParagraph_->GetHeight() + ERROR_TEXT_TOP_MARGIN.ConvertToPx() +
                ERROR_TEXT_BOTTOM_MARGIN.ConvertToPx() + frameSize.Height());
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
    double lastMainOffset = std::max(
        static_cast<double>(std::max(inlineMeasureItem_.inlineLastOffsetY, contentRect_.GetY() - textRect_.GetY())),
        0.0);
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
    const std::string& content, int32_t nakedCharPosition, bool needObscureText, bool showPasswordDirectly)
{
    if (!content.empty() && needObscureText) {
        auto text =
            TextFieldPattern::CreateObscuredText(static_cast<int32_t>(StringUtils::ToWstring(content).length()));
        if (nakedCharPosition >= 0 && nakedCharPosition < static_cast<int32_t>(content.length())) {
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE) || !showPasswordDirectly) {
                auto rawContent = StringUtils::Str8ToStr16(content);
                text[nakedCharPosition] = rawContent[nakedCharPosition];
            }
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
    selectOverlay_ = MakeRefPtr<TextFieldSelectOverlay>(WeakClaim(this));
}

TextFieldPattern::~TextFieldPattern()
{
    if (textEditingController_) {
        textEditingController_->Clear();
        textEditingController_->RemoveObserver(WeakClaim(this));
    }
    CloseSelectOverlay();
    if (isCustomKeyboardAttached_) {
        CloseCustomKeyboard();
    }
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
                HandleDeleteOnCounterScene();
                break;
            }
            case InputOperation::DELETE_FORWARD: {
                DeleteForwardOperation(deleteForwardOperations_.front());
                deleteForwardOperations_.pop();
                HandleDeleteOnCounterScene();
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
            case InputOperation::SET_PREVIEW_TEXT:
                SetPreviewTextOperation(previewTextOperation.front());
                previewTextOperation.pop();
                break;
            case InputOperation::SET_PREVIEW_FINISH:
                FinishTextPreviewOperation();
                break;
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
    HandleContentSizeChange(textRect);
    textRect_ = textRect;

    if (textFieldContentModifier_) {
        textFieldContentModifier_->ContentChange();
    }

    auto oldParentGlobalOffset = parentGlobalOffset_;
    parentGlobalOffset_ = textFieldLayoutAlgorithm->GetParentGlobalOffset();
    inlineMeasureItem_ = textFieldLayoutAlgorithm->GetInlineMeasureItem();
    auto isEditorValueChanged = FireOnTextChangeEvent();
    UpdateCancelNode();
    UpdateSelectController();
    AdjustTextInReasonableArea();
    UpdateCaretRect(isEditorValueChanged);
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    UpdateCaretInfoToController();
    auto hostLayoutProperty =
        dirty->GetHostNode() ? dirty->GetHostNode()->GetLayoutProperty<TextFieldLayoutProperty>() : nullptr;
    if (hostLayoutProperty) {
        hostLayoutProperty->ResetTextAlignChanged();
    }
    ProcessOverlayAfterLayout(oldParentGlobalOffset != parentGlobalOffset_);
    if (inlineSelectAllFlag_) {
        HandleOnSelectAll(false, true);
        inlineSelectAllFlag_ = false;
        showSelect_ = true;
    }
    if (needSelectAll_ && !isLongPress_) {
        HandleOnSelectAll(false);
        needSelectAll_ = false;
    }
    if (mouseStatus_ == MouseStatus::RELEASED) {
        mouseStatus_ = MouseStatus::NONE;
    }
    StopScrollable();
    CheckScrollable();
    UpdateScrollBarOffset();
    if (config.frameSizeChange) {
        if (GetScrollBar() != nullptr) {
            GetScrollBar()->ScheduleDisappearDelayTask();
        }
    }
    return true;
}

void TextFieldPattern::HandleContentSizeChange(const RectF& textRect)
{
    if (textRect_ == textRect) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->GetOnContentSizeChange()) {
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterLayoutTask([textRect, eventHub]() {
            eventHub->FireOnContentSizeChange(textRect.Width(), textRect.Height());
        });
    }
}

void TextFieldPattern::ProcessOverlayAfterLayout(bool isGlobalAreaChanged)
{
    if (processOverlayDelayTask_) {
        CHECK_NULL_VOID(HasFocus());
        processOverlayDelayTask_();
        processOverlayDelayTask_ = nullptr;
        return;
    }
    if (isGlobalAreaChanged) {
        HandleParentGlobalOffsetChange();
        return;
    }
    if (needToRefreshSelectOverlay_ && SelectOverlayIsOn()) {
        StopTwinkling();
        ProcessOverlay();
        needToRefreshSelectOverlay_ = false;
    }
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
    // Adjust y.
    auto contentBottomBoundary = contentRect_.GetY() + contentRect_.GetSize().Height();
    if (textRect_.Height() > contentRect_.Height()) {
        if (textRect_.GetY() + textRect_.Height() < contentBottomBoundary) {
            auto dy = contentBottomBoundary - textRect_.GetY() - textRect_.Height();
            textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        }
        if (GreatNotEqual(textRect_.GetY(), contentRect_.GetY())) {
            auto dy = textRect_.GetY() - contentRect_.GetY();
            textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() - dy));
        }
    } else {
        if (textRect_.GetY() != contentRect_.GetY()) {
            auto dy = contentRect_.GetY() - textRect_.GetY();
            textRect_.SetOffset(OffsetF(textRect_.GetX(), textRect_.GetY() + dy));
        }
    }

    // Adjust x.
    auto contentRightBoundary = contentRect_.GetX() + contentRect_.GetSize().Width();
    if (textRect_.Width() > contentRect_.Width()) {
        if (textRect_.GetX() + textRect_.Width() < contentRightBoundary) {
            auto dx = contentRightBoundary - textRect_.GetX() - textRect_.Width();
            textRect_.SetLeft(textRect_.GetX() + dx);
        }
        if (GreatNotEqual(textRect_.GetX(), contentRect_.GetX())) {
            auto dx = textRect_.GetX() - contentRect_.GetX();
            textRect_.SetOffset(OffsetF(textRect_.GetX() - dx, textRect_.GetY()));
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
    int32_t caretPositionIndex = 0;
    if (!contentController_->IsEmpty()) {
        caretPositionIndex = paragraph_->GetGlyphIndexByCoordinate(localOffset);
    }
    return caretPositionIndex;
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
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    context->AddOnAreaChangeNode(host->GetId());
    auto globalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
    needToRequestKeyboardInner_ = !isLongPress_ && (dragRecipientStatus_ != DragStatus::DRAGGING);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isSelectAll = layoutProperty->GetSelectAllValueValue(false);
    if (isSelectAll && !contentController_->IsEmpty()) {
        needSelectAll_ = true;
    }
    bool needTwinkling = true;
    if (IsNormalInlineState()) {
        ApplyInlineTheme();
        inlineFocusState_ = true;
        if (!contentController_->IsEmpty()) {
            inlineSelectAllFlag_ = blurReason_ != BlurReason::WINDOW_BLUR;
            if (inlineSelectAllFlag_) {
                needTwinkling = false;
            }
        }
        ProcessResponseArea();
    }
    if (needTwinkling) {
        StartTwinkling();
    }
    NotifyOnEditChanged(true);
    if (!IsShowError() && IsUnderlineMode()) {
        auto renderContext = host->GetRenderContext();
        auto textFieldTheme = GetTheme();
        CHECK_NULL_VOID(textFieldTheme);
        underlineColor_ = userUnderlineColor_.typing.value_or(textFieldTheme->GetUnderlineTypingColor());
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
    }
    SetFocusStyle();
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::SetFocusStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);

    if (!paintProperty->HasBackgroundColor()) {
        auto defaultBGColor = textFieldTheme->GetBgColor();
        if (renderContext->GetBackgroundColorValue(defaultBGColor) == defaultBGColor) {
            renderContext->UpdateBackgroundColor(textFieldTheme->GetFocusBgColor());
            isFocusBGColorSet_ = true;
        }
    }

    auto defaultTextColor = textFieldTheme->GetTextColor();
    if (layoutProperty->GetTextColorValue(defaultTextColor) == defaultTextColor) {
        layoutProperty->UpdateTextColor(textFieldTheme->GetFocusTextColor());
        isFocusTextColorSet_ = true;
    }
}

void TextFieldPattern::ClearFocusStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);

    if (isFocusBGColorSet_) {
        renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
        isFocusBGColorSet_ = false;
    }

    if (isFocusTextColorSet_) {
        layoutProperty->UpdateTextColor(textFieldTheme->GetTextColor());
        isFocusTextColorSet_ = false;
    }
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
    if (IsUnderlineMode()) {
        underlineWidth_ = HasFocus() ? TYPING_UNDERLINE_WIDTH : UNDERLINE_WIDTH;
        Color underlineColor = HasFocus() ? userUnderlineColor_.typing.value_or(theme->GetUnderlineTypingColor())
            : userUnderlineColor_.normal.value_or(theme->GetUnderlineColor());
        if (userUnderlineColor_.disable) {
            underlineColor_ = IsDisabled() ? userUnderlineColor_.disable.value() : underlineColor;
        } else {
            underlineColor_ = IsDisabled() ? theme->GetDisableUnderlineColor() : underlineColor;
        }
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
    auto context = PipelineContext::GetCurrentContextSafely();
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

void TextFieldPattern::UpdateBlurReason()
{
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    blurReason_ = focusHub->GetBlurReason();
}

void TextFieldPattern::ProcNormalInlineStateInBlurEvent()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsNormalInlineState()) {
        if (IsTextArea() && isTextInput_) {
            layoutProperty->UpdateMaxLines(1);
            layoutProperty->UpdatePlaceholderMaxLines(1);
        }
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
    }
}

void TextFieldPattern::HandleBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextField %{public}d OnBlur", host->GetId());
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    UpdateBlurReason();
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField(host->GetId());
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    if (!IsShowError() && IsUnderlineMode()) {
        underlineColor_ = userUnderlineColor_.normal.value_or(textFieldTheme->GetUnderlineColor());
        underlineWidth_ = UNDERLINE_WIDTH;
    }
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    ProcNormalInlineStateInBlurEvent();
    needToRequestKeyboardInner_ = false;
    isLongPress_ = false;
    isFocusedBeforeClick_ = false;
    magnifierController_->UpdateShowMagnifier();
    CloseSelectOverlay(!isKeyboardClosedByUser_ && blurReason_ == BlurReason::FOCUS_SWITCH);
    StopTwinkling();
    if ((customKeyboard_ && isCustomKeyboardAttached_)) {
        CloseKeyboard(true);
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TextFile on blur, close custom keyboard");
    }
#ifndef OHOS_PLATFORM
    if (HasConnection()) {
        CloseKeyboard(true);
    }
#endif
    selectController_->UpdateCaretIndex(selectController_->GetCaretIndex());
    NotifyOnEditChanged(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnAreaChanged()) {
        context->RemoveOnAreaChangeNode(host->GetId());
    }
    ClearFocusStyle();
}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_TAB && isFocusedBeforeClick_ && !contentController_->IsEmpty()) {
        isFocusedBeforeClick_ = false;
        HandleOnSelectAll(false);
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
    auto textEditingValue = operationRecords_.back();
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    redoOperationRecords_.push_back(textEditingValue);
    operationRecords_.pop_back();
    FireEventHubOnChange("");
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->UpdateCaretIndex(textEditingValue.caretPosition);
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
    redoOperationRecords_.pop_back();
    operationRecords_.push_back(textEditingValue);
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->UpdateCaretIndex(textEditingValue.caretPosition);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleOnSelectAll(bool isKeyEvent, bool inlineStyle)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnSelectAll");
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
    if (!IsShowHandle() || isKeyEvent || inlineSelectAllFlag_ || IsUsingMouse()) {
        CloseSelectOverlay(true);
        if (inlineSelectAllFlag_ && !isKeyEvent && !IsUsingMouse()) {
            return;
        }
        if (IsSelected()) {
            selectOverlay_->SetSelectionHoldCallback();
        }
        return;
    }
    selectOverlay_->ProcessSelectAllOverlay({ .menuIsShow = false, .animation = true });
}

void TextFieldPattern::HandleOnCopy(bool isUsingExternalKeyboard)
{
    CHECK_NULL_VOID(clipboard_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        return;
    }
    if (!IsSelected() || IsInPasswordMode()) {
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

    if (isUsingExternalKeyboard || IsUsingMouse()) {
        CloseSelectOverlay(true);
    } else {
        selectOverlay_->HideMenu();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(value);
}

bool TextFieldPattern::IsShowHandle()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_RETURN(theme, false);
    return !theme->IsTextFieldShowHandle();
}

void TextFieldPattern::HandleOnPaste()
{
    auto pasteCallback = [weak = WeakClaim(this)](const std::string& data) {
        if (data.empty()) {
            return;
        }
        auto textfield = weak.Upgrade();
        CHECK_NULL_VOID(textfield);
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
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
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
        textfield->UpdateEditingValueToRecord();
        std::wstring pasteData = StringUtils::ToWstring(data);
        auto originLength = static_cast<int32_t>(textfield->contentController_->GetWideText().length());
        textfield->contentController_->ReplaceSelectedValue(start, end, StringUtils::ToString(pasteData));
        auto caretMoveLength =
            static_cast<int32_t>(textfield->contentController_->GetWideText().length()) - originLength;
        auto newCaretPosition = std::clamp(std::max(start, end) + caretMoveLength, 0,
            static_cast<int32_t>(textfield->contentController_->GetWideText().length()));
        textfield->ResetObscureTickCountDown();
        textfield->selectController_->UpdateCaretIndex(newCaretPosition);
        if (layoutProperty->HasMaxLength()) {
            textfield->showCountBorderStyle_ = (originLength - (end - start) + pasteData.length()) >
                                               layoutProperty->GetMaxLengthValue(Infinity<uint32_t>());
            textfield->HandleCountStyle();
        }
        textfield->CloseSelectOverlay(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        textfield->StartTwinkling();
    };
    CHECK_NULL_VOID(clipboard_);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnPaste");
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
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) == CopyOptions::None) {
        return;
    }
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    SwapIfLarger(start, end);
    if (!IsSelected() || IsInPasswordMode()) {
        return;
    }
    UpdateEditingValueToRecord();
    auto selectedText = contentController_->GetSelectedValue(start, end);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed) != CopyOptions::None) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Cut value is %{private}s", selectedText.c_str());
        clipboard_->SetData(selectedText, layoutProperty->GetCopyOptionsValue(CopyOptions::Distributed));
    }
    contentController_->erase(start, end - start);
    UpdateSelection(start);
    CloseSelectOverlay(true);
    StartTwinkling();
    HandleDeleteOnCounterScene();

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
        selectController_->UpdateHandleIndex(startIndex, endIndex);
    }
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
    if (!visible && IsUnderlineMode()) {
        underlineColor_ = userUnderlineColor_.typing.value_or(textFieldTheme->GetUnderlineTypingColor());
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
    }

    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnChange(text);
}

void TextFieldPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(!IsDragging());
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
        if (!IsUsingMouse()) {
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
    if (magnifierController_->GetShowMagnifier() && !GetIsPreviewText()) {
        magnifierController_->UpdateShowMagnifier();
    }
}

void TextFieldPattern::HandleTouchMove(const TouchEventInfo& info)
{
    if (isTouchCaret_ || GetIsPreviewText()) {
        UpdateCaretByTouchMove(info);
    }
}

void TextFieldPattern::UpdateCaretByTouchMove(const TouchEventInfo& info)
{
    scrollable_ = false;
    SetScrollEnable(scrollable_);
    // limit move when preview text is shown
    auto touchOffset = info.GetTouches().front().GetLocalLocation();
    if (GetIsPreviewText()) {
        TAG_LOGI(ACE_TEXT_FIELD, "UpdateCaretByTouchMove when has previewText");
        float offsetY = IsTextArea() ? GetTextRect().GetX() : contentRect_.GetX();
        std::vector<RectF> previewTextRects = GetPreviewTextRects();
        if (previewTextRects.empty()) {
            TAG_LOGI(ACE_TEXT_FIELD, "preview text rect error");
            return;
        }

        double limitL;
        double limitR;
        double limitT = previewTextRects.front().Top() + offsetY + MINIMAL_OFFSET;
        double limitB = previewTextRects.back().Bottom() + offsetY - MINIMAL_OFFSET;

        Offset previewTextTouchOffset;
        CalculatePreviewingTextMovingLimit(touchOffset, limitL, limitR);

        previewTextTouchOffset.SetX(std::clamp(touchOffset.GetX(), limitL, limitR));
        previewTextTouchOffset.SetY(std::clamp(touchOffset.GetY(), limitT, limitB));
        selectController_->UpdateCaretInfoByOffset(previewTextTouchOffset);
    } else {
        selectController_->UpdateCaretInfoByOffset(touchOffset);
    }
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
    } else {
        ClearDragDropEvent();
        InitDragDropEventWithOutDragStart();
    }
    AddDragFrameNodeToManager(host);
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
        pattern->dragValue_ = selectedStr;
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
        if (layoutProperty->GetIsDisabledValue(false) || pattern->IsNormalInlineState() || !pattern->HasFocus()) {
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
        pattern->needToRequestKeyboardInner_ = pattern->dragStatus_ == DragStatus::NONE;
    };
}

void TextFieldPattern::ShowSelectAfterDragEvent()
{
    selectController_->UpdateHandleIndex(dragTextStart_, dragTextEnd_);
    showSelect_ = true;
    if (!IsUsingMouse()) {
        DelayProcessOverlay({ .menuIsShow = false });
    }
}

void TextFieldPattern::InitDragDropEventWithOutDragStart()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    InitDragDropCallBack();
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
    eventHub->SetDefaultOnDragStart(OnDragStart());
    InitDragDropCallBack();
    gestureHub->SetTextDraggable(true);
}

void TextFieldPattern::InitDragDropCallBack()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
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
        auto textPaintOffset = pattern->GetPaintRectGlobalOffset();
        Offset offset = Offset(touchX, touchY) - Offset(pattern->textRect_.GetX(), pattern->textRect_.GetY()) -
                        Offset(textPaintOffset.GetX(), textPaintOffset.GetY()) -
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

    auto onDragEnd = [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        ContainerScope scope(pattern->GetHostInstanceId());
        if (pattern->dragStatus_ == DragStatus::DRAGGING && !pattern->isDetachFromMainTree_) {
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);

            // Except for DRAG_SUCCESS, all of rest need to show
            auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
            CHECK_NULL_VOID(paintProperty);
            auto newDragValue =
                pattern->contentController_->GetSelectedValue(pattern->dragTextStart_, pattern->dragTextEnd_);
            auto focusHub = pattern->GetFocusHub();
            CHECK_NULL_VOID(focusHub);
            if (event != nullptr && event->GetResult() != DragRet::DRAG_SUCCESS &&
                newDragValue == pattern->dragValue_ &&
                paintProperty->GetInputStyleValue(InputStyle::DEFAULT) != InputStyle::INLINE &&
                focusHub->IsFocusable()) {
                pattern->ShowSelectAfterDragEvent();
                focusHub->RequestFocusImmediately();
            }
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
    eventHub->SetDefaultOnDragStart(nullptr);
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
        pattern->selectOverlay_->SetUsingMouse(info.GetSourceDevice() == SourceType::MOUSE);
        pattern->selectOverlay_->SetLastSourceType(info.GetSourceDevice());
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
    CHECK_NULL_VOID(!IsDragging());
    auto focusHub = GetFocusHub();
    if (!focusHub->IsFocusable()) {
        return;
    }
    if (!HasFocus()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "text field request focus currently");
        if (!focusHub->IsFocusOnTouch().value_or(true) || !focusHub->RequestFocusImmediately()) {
            CloseSelectOverlay(true);
            StopTwinkling();
            return;
        }
    }
    if (IsMouseOverScrollBar(info) && hasMousePressed_) {
        Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
        bool reverse = false;
        if (GetScrollBar()->AnalysisUpOrDown(point, reverse)) {
            ScrollPage(reverse);
        }
        return;
    }
    selectOverlay_->SetLastSourceType(info.GetSourceDevice());
    selectOverlay_->SetUsingMouse(info.GetSourceDevice() == SourceType::MOUSE);
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
    auto deltaOffset = location - clickLocation_;
    auto deltaDistance = deltaOffset.GetDistance();
    clickLocation_ = location;

    return timeout.count() >= DOUBLECLICK_MIN_INTERVAL_MS && timeout.count() < DOUBLECLICK_INTERVAL_MS &&
           deltaDistance < DOUBLECLICK_DISTANCE.ConvertToPx();
}

void TextFieldPattern::HandleSingleClickEvent(GestureEvent& info)
{
    if (mouseStatus_ != MouseStatus::NONE && IsNormalInlineState()) {
        return;
    }
    if (!IsUsingMouse() && SelectOverlayIsOn() && BetweenSelectedPosition(info.GetGlobalLocation())) {
        selectOverlay_->ShowMenu();
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
    bool needCloseOverlay = true;
    if (RepeatClickCaret(info.GetLocalLocation(), lastCaretIndex, lastCaretRect) &&
        info.GetSourceDevice() != SourceType::MOUSE) {
        if (needSelectAll_) {
            HandleOnSelectAll(false);
        } else {
            needCloseOverlay = false;
            ProcessOverlay({ .hideHandle = contentController_->IsEmpty(), .animation = true, .hideHandleLine = true });
        }
    } else if (!contentController_->IsEmpty() && info.GetSourceDevice() != SourceType::MOUSE &&
               !IsNormalInlineState()) {
        if (GetNakedCharPosition() >= 0) {
            needCloseOverlay = false;
            DelayProcessOverlay({ .menuIsShow = false, .animation = true });
        } else if (needSelectAll_) {
            HandleOnSelectAll(false);
        } else {
            needCloseOverlay = false;
            ProcessOverlay({ .menuIsShow = false, .animation = true, .hideHandleLine = true });
        }
    }
    if (needCloseOverlay || GetIsPreviewText()) {
        CloseSelectOverlay(true);
    }
    DoProcessAutoFill();
    // emulate clicking bottom of the textField
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::DoProcessAutoFill()
{
    bool isPopup = false;
    auto isSuccess = ProcessAutoFill(isPopup);
    if (!isPopup && isSuccess) {
        needToRequestKeyboardInner_ = false;
    } else if (RequestKeyboard(false, true, true)) {
        NotifyOnEditChanged(true);
    }
}

bool TextFieldPattern::IsAutoFillPasswordType(const AceAutoFillType& autoFillType)
{
    return (autoFillType == AceAutoFillType::ACE_USER_NAME || autoFillType == AceAutoFillType::ACE_PASSWORD ||
           autoFillType == AceAutoFillType::ACE_NEW_PASSWORD);
}

AceAutoFillType TextFieldPattern::GetHintType()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, AceAutoFillType::ACE_UNSPECIFIED);
    auto onePlaceHolder = GetPlaceHolder();
    if (onePlaceHolder.empty()) {
        return AceAutoFillType::ACE_UNSPECIFIED;
    }
    return container->PlaceHolderToType(onePlaceHolder);
}

bool TextFieldPattern::CheckAutoFillType(const AceAutoFillType& autoFillType, bool isFromKeyBoard)
{
    if (isFromKeyBoard) {
        return true;
    }
    if (autoFillType == AceAutoFillType::ACE_UNSPECIFIED) {
        TAG_LOGE(AceLogTag::ACE_AUTO_FILL, "CheckAutoFillType :autoFillType is ACE_UNSPECIFIED.");
        return false;
    } else if (IsAutoFillPasswordType(autoFillType)) {
        return GetAutoFillTriggeredStateByType(autoFillType);
    }
    return true;
}

bool TextFieldPattern::GetAutoFillTriggeredStateByType(const AceAutoFillType& autoFillType)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto autoFillContainerNode = host->GetFirstAutoFillContainerNode();
    CHECK_NULL_RETURN(autoFillContainerNode, false);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    CHECK_NULL_RETURN(stateHolder, false);
    if (autoFillType == AceAutoFillType::ACE_USER_NAME || autoFillType == AceAutoFillType::ACE_PASSWORD) {
        return !stateHolder->IsAutoFillPasswordTriggered();
    }
    if (autoFillType == AceAutoFillType::ACE_NEW_PASSWORD) {
        return !stateHolder->IsAutoFillNewPasswordTriggered();
    }
    return false;
}

void TextFieldPattern::SetAutoFillTriggeredStateByType(const AceAutoFillType& autoFillType)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto autoFillContainerNode = host->GetFirstAutoFillContainerNode();
    CHECK_NULL_VOID(autoFillContainerNode);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    CHECK_NULL_VOID(stateHolder);
    if (autoFillType == AceAutoFillType::ACE_USER_NAME || autoFillType == AceAutoFillType::ACE_PASSWORD) {
        stateHolder->SetAutoFillPasswordTriggered(true);
    } else if (autoFillType == AceAutoFillType::ACE_NEW_PASSWORD) {
        stateHolder->SetAutoFillNewPasswordTriggered(true);
    }
}

AceAutoFillType TextFieldPattern::GetAutoFillType()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, AceAutoFillType::ACE_UNSPECIFIED);
    auto aceContentType =
        TextContentTypeToAceAutoFillType(layoutProperty->GetTextContentTypeValue(TextContentType::UNSPECIFIED));
    auto aceInputType = ConvertToAceAutoFillType(layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
    if (aceContentType != AceAutoFillType::ACE_UNSPECIFIED) {
        return aceContentType;
    }
    if (aceInputType != AceAutoFillType::ACE_UNSPECIFIED) {
        if (IsAutoFillPasswordType(aceInputType)) {
            return aceInputType;
        } else {
            return GetHintType();
        }
    }
    return GetHintType();
}

bool TextFieldPattern::CheckAutoFill(bool isFromKeyBoard)
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    bool isEnableAutoFill = layoutProperty->GetEnableAutoFillValue(true);
    if (!isEnableAutoFill) {
        return false;
    }
    return CheckAutoFillType(GetAutoFillType(), isFromKeyBoard);
}

bool TextFieldPattern::ProcessAutoFill(bool& isPopup, bool isFromKeyBoard, bool isNewPassWord)
{
    if (!CheckAutoFill(isFromKeyBoard)) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "No need to auto fill.");
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto autoFillType = GetAutoFillType();
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    SetAutoFillTriggeredStateByType(autoFillType);
    SetFillRequestFinish(false);
    return (container->RequestAutoFill(host, autoFillType, isPopup, isNewPassWord));
}

void TextFieldPattern::HandleDoubleClickEvent(GestureEvent& info)
{
    if (GetIsPreviewText()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "refuse double click when has preview text.");
        return;
    }

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
        ProcessOverlay({ .animation = true });
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
    taskExecutor->PostDelayedTask(cursorTwinklingTask_, TaskExecutor::TaskType::UI, twinklingInterval_,
        "ArkUITextFieldCursorTwinkling");
}

void TextFieldPattern::StartTwinkling()
{
    if (isTransparent_ || !HasFocus()) {
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
        CloseKeyboard(true);
        RequestKeyboard(false, true, true);
    }
#endif
}

void TextFieldPattern::ProcessScroll()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
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
}

void TextFieldPattern::HandleDeleteOnCounterScene()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMaxLength()) {
        showCountBorderStyle_ = false;
        HandleCountStyle();
    }
}

void TextFieldPattern::HandleCountStyle()
{
    bool noDeleteOperation = deleteBackwardOperations_.empty() && deleteForwardOperations_.empty();
    if (!IsShowCount() || !noDeleteOperation) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto inputValue = layoutProperty->GetSetCounterValue(DEFAULT_MODE);
    if (inputValue == DEFAULT_MODE) {
        HandleCounterBorder();
    } else if (inputValue != ILLEGAL_VALUE) {
        auto showBorder = layoutProperty->GetShowHighlightBorderValue(true);
        if (showBorder) {
            HandleCounterBorder();
        }
        if (showCountBorderStyle_) {
            UltralimitShake();
        }
    }
}

void TextFieldPattern::ProcessCounter()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsShowCount()) {
        AddCounterNode();
    } else {
        CleanCounterNode();
    }
    UpdateCounterMargin();
}

void TextFieldPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
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
    ApplyNormalTheme();
    ApplyUnderlineTheme();
    ApplyInlineTheme();
    ProcessInnerPadding();

    InitClickEvent();
    InitLongPressEvent();
    InitFocusEvent();
    InitMouseEvent();
    InitTouchEvent();

    SetAccessibilityAction();
    FilterInitializeText();
    InitDisableColor();
    ProcessResponseArea();
    InitDragEvent();
    Register2DragDropManager();
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
    // The textRect position can't be changed by only redraw.
    if (CheckNeedMeasure(layoutProperty->GetPropertyChangeFlag()) && !HasInputOperation() &&
        (!HasFocus() || !initTextRect_)) {
        textRect_.SetLeft(GetPaddingLeft() + GetBorderLeft());
        textRect_.SetTop(GetPaddingTop() + GetBorderTop());
        initTextRect_ = true;
    }
    CalculateDefaultCursor();

    auto textWidth = static_cast<int32_t>(contentController_->GetWideText().length());
    if (SelectOverlayIsOn()) {
        needToRefreshSelectOverlay_ = true;
        UpdateSelection(std::clamp(selectController_->GetStartIndex(), 0, textWidth),
            std::clamp(selectController_->GetEndIndex(), 0, textWidth));
    } else {
        needToRefreshSelectOverlay_ = false;
    }
    if (layoutProperty->GetTypeChangedValue(false)) {
        layoutProperty->ResetTypeChanged();
        operationRecords_.clear();
        redoOperationRecords_.clear();
    }
    ProcessScroll();
    ProcessCounter();
    Register2DragDropManager();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    isModifyDone_ = true;
}

void TextFieldPattern::ApplyNormalTheme()
{
    if (IsUnderlineMode() || IsInlineMode()) {
        return;
    }
    SetThemeAttr();
}

void TextFieldPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        bool isPwdType = false;
        if (layoutProperty) {
            auto inputType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
            isPwdType = inputType == TextInputType::VISIBLE_PASSWORD || inputType == TextInputType::NUMBER_PASSWORD ||
                        inputType == TextInputType::SCREEN_LOCK_PASSWORD || inputType == TextInputType::NEW_PASSWORD;
        }
        if (!isPwdType) {
            Recorder::NodeDataCache::Get().PutString(host, inspectorId, contentController_->GetTextValue());
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

void TextFieldPattern::AutoFillValueChanged()
{
    if (IsFillRequestFinish()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto autoContentType = layoutProperty->GetTextContentTypeValue(TextContentType::UNSPECIFIED);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if (autoContentType >= TextContentType::FULL_STREET_ADDRESS && autoContentType <= TextContentType::END
        && CheckAutoFill()) {
        container->UpdatePopupUIExtension(host);
    }
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
    AutoFillValueChanged();
    eventHub->FireOnChange(contentController_->GetTextValue());
    auto context = PipelineContext::GetCurrentContextSafely();
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
            if (pattern->customKeyboard_) {
                pattern->StartTwinkling();
            }
        },
        TaskExecutor::TaskType::UI, "ArkUITextFieldScrollToSafeArea");
    return true;
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
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    BorderWidthProperty currentBorderWidth;
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
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
        pattern->selectOverlay_->SetUsingMouse(info.GetSourceDevice() == SourceType::MOUSE);
        pattern->selectOverlay_->SetLastSourceType(info.GetSourceDevice());
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    gesture->SetLongPressEvent(longPressEvent_);
}

void TextFieldPattern::HandleLongPress(GestureEvent& info)
{
    CHECK_NULL_VOID(!IsDragging());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!focusHub->IsFocusable() || IsOnUnitByPosition(info.GetGlobalLocation())
        || GetIsPreviewText()) {
        return;
    }
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
    if (!focusHub->IsCurrentFocus()) {
        focusHub->RequestFocusImmediately();
    }
    selectController_->UpdateSelectByOffset(ConvertGlobalToLocalOffset(info.GetGlobalLocation()));
    if (IsSelected()) {
        StopTwinkling();
    }
    SetIsSingleHandle(!IsSelected());
    if (shouldProcessOverlayAfterLayout) {
        DelayProcessOverlay({ .menuIsShow = true, .animation = true,  });
    } else {
        ProcessOverlay({ .animation = true });
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::IsOnUnitByPosition(const Offset& globalOffset)
{
    if (!IsShowUnit()) {
        return false;
    }
    auto unitArea = AceType::DynamicCast<UnitResponseArea>(responseArea_);
    CHECK_NULL_RETURN(unitArea, false);
    auto frameNode = unitArea->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    auto localOffset = ConvertGlobalToLocalOffset(globalOffset);
    return frameNode->GetGeometryNode()->GetFrameRect().IsInRegion({ localOffset.GetX(), localOffset.GetY() });
}

bool TextFieldPattern::IsMouseOverScrollBar(const GestureEvent& info)
{
    CHECK_NULL_RETURN(GetScrollBar(), false);
    Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
    return GetScrollBar()->InBarRectRegion(point);
}

void TextFieldPattern::UpdateCaretPositionWithClamp(const int32_t& pos)
{
    selectController_->UpdateCaretIndex(
        std::clamp(pos, 0, static_cast<int32_t>(contentController_->GetWideText().length())));
}

void TextFieldPattern::ProcessOverlay(const OverlayRequest& request)
{
    selectOverlay_->ProcessOverlay(request);
}

void TextFieldPattern::DelayProcessOverlay(const OverlayRequest& request)
{
    processOverlayDelayTask_ = [weak = WeakClaim(this), request]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ProcessOverlay(request);
    };
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
        textFieldManager->ClearOnFocusTextField(node->GetId());
    }
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->UnRegisterCallbackNG(frameNode);
        fontManager->RemoveVariationNodeNG(frameNode);
    }
    pipeline->RemoveWindowSizeChangeCallback(node->GetId());
    pipeline->RemoveOnAreaChangeNode(node->GetId());
}

void TextFieldPattern::CloseSelectOverlay()
{
    CloseSelectOverlay(false);
}

void TextFieldPattern::CloseSelectOverlay(bool animation)
{
    selectOverlay_->CloseOverlay(animation, CloseReason::CLOSE_REASON_NORMAL);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    gesture->AddTouchEvent(GetTouchListener());
}

void TextFieldPattern::InitEditingValueText(std::string content)
{
    if (HasInputOperation()) {
        return;
    }
    contentController_->SetTextValueOnly(std::move(content));
    selectController_->UpdateCaretIndex(GetWideText().length());
    if (GetIsPreviewText() && GetWideText().empty()) {
        FinishTextPreviewOperation();
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::InitValueText(std::string content)
{
    if (HasInputOperation() && content != "") {
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
            if (info.GetButton() == MouseButton::LEFT_BUTTON && info.GetAction() == MouseAction::PRESS) {
                pattern->hasMousePressed_ = true;
            } else {
                pattern->hasMousePressed_ = false;
            }
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
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    if (isHover) {
        pipeline->SetMouseStyleHoldNode(frameId);
    } else {
        int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
        windowId = GetSCBSystemWindowId();
#endif
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT, windowId);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
    isOnHover_ = isHover;
}

void TextFieldPattern::RestoreDefaultMouseState()
{
    int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = GetSCBSystemWindowId();
#endif
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto id = host->GetId();
    pipeline->SetMouseStyleHoldNode(id);
    pipeline->ChangeMouseStyle(id, MouseFormat::DEFAULT, windowId);
}

void TextFieldPattern::ChangeMouseState(
    const Offset location, const RefPtr<PipelineContext>& pipeline, int32_t frameId, bool isByPass)
{
    auto responseAreaWidth = (responseArea_ ? responseArea_->GetAreaRect().Width() : 0.0f) +
                             (cleanNodeResponseArea_ ? cleanNodeResponseArea_->GetAreaRect().Width() : 0.0f);
    auto x = location.GetX();
    auto y = location.GetY();
    int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = GetSCBSystemWindowId();
#endif
    if (GreatNotEqual(x, 0) && LessNotEqual(x, frameRect_.Width()) && GreatNotEqual(y, 0) &&
        LessNotEqual(y, frameRect_.Height())) {
        if (GreatNotEqual(location.GetX(), frameRect_.Width() - responseAreaWidth)) {
            RestoreDefaultMouseState();
        } else {
            pipeline->SetMouseStyleHoldNode(frameId);
            pipeline->ChangeMouseStyle(frameId, MouseFormat::TEXT_CURSOR, windowId, isByPass);
        }
    } else {
        RestoreDefaultMouseState();
    }
}

void TextFieldPattern::HandleMouseEvent(MouseInfo& info)
{
    CHECK_NULL_VOID(!IsDragging());
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto frameId = tmpHost->GetId();
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    info.SetStopPropagation(true);
    selectOverlay_->SetLastSourceType(info.GetSourceDevice());
    auto scrollBar = GetScrollBar();
    Point point(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY());
    int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = GetSCBSystemWindowId();
#endif
    if (scrollBar && (scrollBar->IsPressed() || scrollBar->IsHover() || scrollBar->InBarRectRegion(point))) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT, windowId);
        return;
    }
    ChangeMouseState(info.GetLocalLocation(), pipeline, frameId, info.GetAction() == MouseAction::WINDOW_LEAVE);

    selectOverlay_->SetUsingMouse(true);
    if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        HandleRightMouseEvent(info);
    } else if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        HandleLeftMouseEvent(info);
        if (IsSelected()) {
            selectOverlay_->SetSelectionHoldCallback();
        }
    }
    if (info.GetAction() == OHOS::Ace::MouseAction::RELEASE) {
        selectOverlay_->SetUsingMouse(false);
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
        OffsetF rightClickOffset = OffsetF(
            static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY()));
        selectOverlay_->SetMouseMenuOffset(rightClickOffset);
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
    auto context = tmpHost->GetContextRefPtr();
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

void TextFieldPattern::KeyboardContentTypeToInputType()
{
    if (keyboard_ != TextInputType::UNSPECIFIED) {
        return;
    }
    auto autoFillType = GetAutoFillType();
    static std::unordered_map<AceAutoFillType, TextInputType> keyBoardMap = {
        { AceAutoFillType::ACE_PASSWORD, TextInputType::VISIBLE_PASSWORD},
        { AceAutoFillType::ACE_USER_NAME, TextInputType::USER_NAME },
        { AceAutoFillType::ACE_NEW_PASSWORD, TextInputType::NEW_PASSWORD },
        { AceAutoFillType::ACE_FULL_STREET_ADDRESS, TextInputType::TEXT },
        { AceAutoFillType::ACE_HOUSE_NUMBER, TextInputType::TEXT },
        { AceAutoFillType::ACE_DISTRICT_ADDRESS, TextInputType::TEXT },
        { AceAutoFillType::ACE_CITY_ADDRESS, TextInputType::TEXT },
        { AceAutoFillType::ACE_PROVINCE_ADDRESS, TextInputType::TEXT },
        { AceAutoFillType::ACE_COUNTRY_ADDRESS, TextInputType::TEXT },
        { AceAutoFillType::ACE_PERSON_FULL_NAME, TextInputType::TEXT },
        { AceAutoFillType::ACE_PERSON_LAST_NAME, TextInputType::TEXT },
        { AceAutoFillType::ACE_PERSON_FIRST_NAME, TextInputType::TEXT },
        { AceAutoFillType::ACE_PHONE_NUMBER, TextInputType::PHONE },
        { AceAutoFillType::ACE_PHONE_COUNTRY_CODE, TextInputType::PHONE },
        { AceAutoFillType::ACE_FULL_PHONE_NUMBER, TextInputType::PHONE },
        { AceAutoFillType::ACE_EMAIL_ADDRESS, TextInputType::EMAIL_ADDRESS },
        { AceAutoFillType::ACE_BANK_CARD_NUMBER, TextInputType::NUMBER },
        { AceAutoFillType::ACE_ID_CARD_NUMBER, TextInputType::NUMBER },
        { AceAutoFillType::ACE_PRECISE_TIME, TextInputType::NUMBER },
        { AceAutoFillType::ACE_HOUR_AND_MINUTE, TextInputType::NUMBER },
        { AceAutoFillType::ACE_DATE, TextInputType::NUMBER },
        { AceAutoFillType::ACE_MONTH, TextInputType::NUMBER },
        { AceAutoFillType::ACE_YEAR, TextInputType::NUMBER },
        { AceAutoFillType::ACE_NICKNAME, TextInputType::TEXT },
        { AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET, TextInputType::TEXT },
        { AceAutoFillType::ACE_FORMAT_ADDRESS, TextInputType::TEXT }};
    if (keyBoardMap.find(autoFillType) != keyBoardMap.end()) {
        keyboard_ = keyBoardMap[autoFillType];
    }
}

bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto context = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(context, false);

    if (needShowSoftKeyboard) {
        if (customKeyboard_) {
            return RequestCustomKeyboard();
        }
    KeyboardContentTypeToInputType();
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
        if (customKeyboard_ && isCustomKeyboardAttached_) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Request Softkeyboard, Close CustomKeyboard.");
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
    auto pipeline = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, {});
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, {});
    auto windowRect = pipeline->GetCurrentWindowRect();
    double positionY = (tmpHost->GetPaintRectOffset() - pipeline->GetRootRect().GetOffset()).GetY() + windowRect.Top();
    double height = frameRect_.Height();
    auto offset = AVOID_OFFSET.ConvertToPx();
    auto textPaintOffset = GetPaintRectGlobalOffset();
    height = selectController_->GetCaretRect().Bottom() + windowRect.Top() +
             textPaintOffset.GetY() + offset - positionY;

    if (IsNormalInlineState()) {
        auto safeBoundary = theme->GetInlineBorderWidth().ConvertToPx() * 2;
        positionY += static_cast<double>(inlineMeasureItem_.inlineSizeHeight) + safeBoundary;
        height = offset;
    }

    MiscServices::CursorInfo cursorInfo { .left = selectController_->GetCaretRect().Left() + windowRect.Left() +
                                                  textPaintOffset.GetX(),
        .top = selectController_->GetCaretRect().Top() + windowRect.Top() + textPaintOffset.GetY(),
        .width = theme->GetCursorWidth().ConvertToPx(),
        .height = selectController_->GetCaretRect().Height() };
    MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)keyboard_,
        .enterKeyType = (int32_t)GetTextInputActionValue(GetDefaultTextInputAction()),
        .isTextPreviewSupported = hasSupportedPreviewText };
    MiscServices::TextConfig textConfig = { .inputAttribute = inputAttribute,
        .cursorInfo = cursorInfo,
        .range = { .start = selectController_->GetStartIndex(), .end = selectController_->GetEndIndex() },
        .windowId = pipeline->GetFocusWindowId(),
        .positionY = positionY,
        .height = height };

    if (keyboard_ == TextInputType::NUMBER_DECIMAL) {
        textConfig.inputAttribute.inputPattern = (int32_t)TextInputType::NUMBER;
    }
    return textConfig;
}
#endif

AceAutoFillType TextFieldPattern::ConvertToAceAutoFillType(TextInputType type)
{
    static std::unordered_map<TextInputType, AceAutoFillType> convertMap = {
        { TextInputType::VISIBLE_PASSWORD, AceAutoFillType::ACE_PASSWORD },
        { TextInputType::USER_NAME, AceAutoFillType::ACE_USER_NAME },
        { TextInputType::NEW_PASSWORD, AceAutoFillType::ACE_NEW_PASSWORD } };
    auto it = convertMap.find(type);
    if (it != convertMap.end()) {
        return it->second;
    }
    return AceAutoFillType::ACE_UNSPECIFIED;
}

AceAutoFillType TextFieldPattern::TextContentTypeToAceAutoFillType(const TextContentType& type)
{
    if (contentTypeMap_.find(type) != contentTypeMap_.end()) {
        return contentTypeMap_[type].first;
    }
    return contentTypeMap_[TextContentType::UNSPECIFIED].first;
}

bool TextFieldPattern::CloseKeyboard(bool forceClose)
{
    return CloseKeyboard(forceClose, forceClose);
}

bool TextFieldPattern::CloseKeyboard(bool forceClose, bool isStopTwinkling)
{
    if (forceClose) {
        if (isStopTwinkling) {
            StopTwinkling();
        }
        CloseSelectOverlay(true);
        if (customKeyboard_ && isCustomKeyboardAttached_) {
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

void TextFieldPattern::SetCustomKeyboardOption(bool supportAvoidance)
{
    keyboardAvoidance_ = supportAvoidance;
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
    CHECK_NULL_RETURN(customKeyboard_, false);
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->SetCustomKeyboardOption(keyboardAvoidance_);
    overlayManager->BindKeyboardWithNode(customKeyboard_, frameNode->GetId());
    isCustomKeyboardAttached_ = true;
    keyboardOverlay_ = overlayManager;
    auto caretHeight = selectController_->GetCaretRect().Height();
    auto safeHeight = caretHeight + selectController_->GetCaretRect().GetY();
    if (selectController_->GetCaretRect().GetY() > caretHeight) {
        safeHeight = caretHeight;
    }
    keyboardOverlay_->AvoidCustomKeyboard(frameNode->GetId(), safeHeight);
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
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (GetIsPreviewText()) {
        PreviewTextInfo info = {
            .text = insertValue,
            .range = {-1, -1}
        };
        SetPreviewTextOperation(info);
        FinishTextPreview();
    }

    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    UpdateEditingValueToRecord();
    if (IsSelected()) {
        caretStart = start;
    } else {
        caretStart = selectController_->GetCaretIndex();
    }
    int32_t caretMoveLength = 0;
    bool hasInsertValue = false;
    int32_t originLength = 0;
    if (IsSelected()) {
        originLength = static_cast<int32_t>(contentController_->GetWideText().length()) - (end - start);
        hasInsertValue = contentController_->ReplaceSelectedValue(start, end, insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);
    } else {
        originLength = static_cast<int32_t>(contentController_->GetWideText().length());
        hasInsertValue = contentController_->InsertValue(selectController_->GetCaretIndex(), insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);
    }
    if (layoutProperty->HasMaxLength()) {
        showCountBorderStyle_ = (originLength + StringUtils::ToWstring(insertValue).length()) >
                                layoutProperty->GetMaxLengthValue(Infinity<uint32_t>());
        HandleCountStyle();
    }
    selectController_->UpdateCaretIndex(caretStart + caretMoveLength);
    UpdateObscure(insertValue, hasInsertValue);
    if (HasFocus()) {
        cursorVisible_ = true;
        StartTwinkling();
    } else {
        cursorVisible_ = false;
        StopTwinkling();
    }
}

void TextFieldPattern::UpdateObscure(const std::string& insertValue, bool hasInsertValue)
{
    if (!IsTextArea() && IsInPasswordMode() && GetTextObscured()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto wideInsertValue = StringUtils::ToWstring(insertValue);
        if (wideInsertValue.length() == 1 &&
            (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::NUMBER_PASSWORD ||
                std::isdigit(insertValue[0])) &&
            hasInsertValue) {
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
}

void TextFieldPattern::InsertValue(const std::string& insertValue)
{
    if (!HasFocus()) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "text field on blur, can't insert value");
        return;
    }
    if (focusIndex_ != FocuseIndex::TEXT && insertValue == " ") {
        HandleSpaceEvent();
        return;
    }
    focusIndex_ = FocuseIndex::TEXT;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    inputOperations_.emplace(InputOperation::INSERT);
    insertValueOperations_.emplace(insertValue);
    CloseSelectOverlay(true);
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
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
        !IsInPasswordMode()) {
        MarginProperty margin;
        const auto& getMargin = layoutProperty->GetMarginProperty();
        if (!getMargin || GetMarginBottom() == MARGIN_ZERO) {
            margin.bottom = CalcLength(COUNTER_BOTTOM);
            layoutProperty->UpdateMargin(margin);
            return;
        }
        Dimension marginProperty { BOTTOM_MARGIN, DimensionUnit::VP };
        auto systemMargin = getMargin->bottom->GetDimension();
        if (systemMargin < marginProperty) {
            margin.bottom = CalcLength(marginProperty);
            margin.left = CalcLength(getMargin->left->GetDimension());
            margin.top = CalcLength(getMargin->top->GetDimension());
            margin.right = CalcLength(getMargin->right->GetDimension());
            layoutProperty->UpdateMargin(margin);
        } else {
            margin.bottom = CalcLength(systemMargin);
            margin.left = CalcLength(getMargin->left->GetDimension());
            margin.top = CalcLength(getMargin->top->GetDimension());
            margin.right = CalcLength(getMargin->right->GetDimension());
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
    if (!isAlgorithmMeasure && paragraph_ && paragraph_->GetHeight() != 0.0f && paragraph_->GetLineCount() > 0) {
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
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
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

void TextFieldPattern::OnCursorMoveDone(TextAffinity textAffinity, std::optional<Offset> offset)
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    StartTwinkling();
    CloseSelectOverlay();
    if (offset.has_value()) {
        selectController_->UpdateCaretInfoByOffset(offset.value());
    } else {
        selectController_->MoveCaretToContentRect(GetCaretIndex(), textAffinity);
    }
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
    auto newPos = GetLineBeginPosition(originCaretPosition, false);
    if (newPos == originCaretPosition && originCaretPosition > 0) {
        newPos = GetLineBeginPosition(originCaretPosition - 1, false);
    }
    UpdateCaretPositionWithClamp(newPos);
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
    auto newPos = GetLineEndPosition(originCaretPosition, false);
    if (newPos == originCaretPosition && originCaretPosition > 0) {
        newPos = GetLineEndPosition(originCaretPosition + 1, false);
    }
    UpdateCaretPositionWithClamp(newPos);
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
    auto offsetX = selectController_->GetCaretRect().GetX();
    // multiply by 0.5f to convert to the grapheme center point of the previous line.
    auto offsetY = selectController_->GetCaretRect().GetY() - PreferredLineHeight() * 0.5f;
    std::optional<Offset> offset;
    offset.emplace(Offset(offsetX, offsetY));
    OnCursorMoveDone(TextAffinity::DOWNSTREAM, offset);
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
    auto offsetX = selectController_->GetCaretRect().GetX();
    // multiply by 1.5f to convert to the grapheme center point of the next line.
    auto offsetY = selectController_->GetCaretRect().GetY() + PreferredLineHeight() * 1.5f;
    std::optional<Offset> offset;
    offset.emplace(Offset(offsetX, offsetY));
    OnCursorMoveDone(TextAffinity::DOWNSTREAM, offset);
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
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleCounterBorder()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    if (showCountBorderStyle_) {
        if (IsUnderlineMode()) {
            underlineWidth_ = ERROR_UNDERLINE_WIDTH;
            SetUnderlineColor(userUnderlineColor_.error.value_or(theme->GetErrorUnderlineColor()));
        } else {
            auto tmpHost = GetHost();
            CHECK_NULL_VOID(tmpHost);
            auto renderContext = tmpHost->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            BorderWidthProperty overCountBorderWidth;
            overCountBorderWidth.SetBorderWidth(OVER_COUNT_BORDER_WIDTH);
            BorderColorProperty overCountBorderColor;
            overCountBorderColor.SetColor(theme->GetOverCounterColor());
            layoutProperty->UpdateBorderWidth(overCountBorderWidth);
            renderContext->UpdateBorderWidth(overCountBorderWidth);
            renderContext->UpdateBorderColor(overCountBorderColor);
        }
    } else {
        if (IsUnderlineMode()) {
            ApplyUnderlineTheme();
        } else {
            SetThemeBorderAttr();
        }
    }
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    if (focusIndex_ == FocuseIndex::CANCEL) {
        CleanNodeResponseKeyEvent();
        return;
    }
    if (focusIndex_ == FocuseIndex::UNIT) {
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
        if (!textAreaBlurOnSubmit_) {
            if (GetInputFilter() != "\n") {
                InsertValue("\n");
            }
        } else {
            CloseKeyboard(forceCloseKeyboard, false);
            FocusHub::LostFocusToViewRoot();
        }
        return;
    }
    eventHub->FireOnSubmit(static_cast<int32_t>(action), event);
    RecordSubmitEvent();
    if (event.IsKeepEditable()) {
        return;
    }
    // LostFocusToViewRoot may not cause current lost focus, only stop twinkling when it is truly lost focus,
    // which will call StopTwinkling on HandleBlurEvent method.
    if (textInputBlurOnSubmit_) {
        CloseKeyboard(forceCloseKeyboard, false);
        FocusHub::LostFocusToViewRoot();
    }
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
    UpdateEditingValueToRecord();
    contentController_->SetTextValue(value->text);
    selectController_->UpdateCaretIndex(value->selection.baseOffset);
    ContainerScope scope(GetInstanceId());
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
    auto parentGlobalOffset = GetPaintRectGlobalOffset();
    if (parentGlobalOffset != parentGlobalOffset_) {
        parentGlobalOffset_ = parentGlobalOffset;
        UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
        HandleParentGlobalOffsetChange();
    }
    RequestKeyboardOnFocus();
}

void TextFieldPattern::HandleParentGlobalOffsetChange()
{
    selectController_->CalculateHandleOffset();
    CHECK_NULL_VOID(SelectOverlayIsOn() || selectOverlay_->SelectOverlayIsCreating());
    if (selectOverlay_->IsShowMouseMenu()) {
        CloseSelectOverlay();
    } else {
        selectOverlay_->ProcessOverlayOnAreaChanged({ .menuIsShow = false });
    }
}

void TextFieldPattern::RequestKeyboardOnFocus()
{
    if (!needToRequestKeyboardOnFocus_ || !needToRequestKeyboardInner_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weak = WeakClaim(this)]() {
        auto textField = weak.Upgrade();
        CHECK_NULL_VOID(textField);
        if (!textField->RequestKeyboard(false, true, true)) {
            return;
        }
        textField->NotifyOnEditChanged(true);
        textField->needToRequestKeyboardInner_ = false;
    });
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
    if (newWidth == prevWidth && newHeight == prevHeight) {
        return;
    }
    if (SelectOverlayIsOn()) {
        if (selectOverlay_->IsShowMouseMenu()) {
            CloseSelectOverlay();
        } else if (newWidth != prevWidth || newHeight != prevHeight) {
            DelayProcessOverlay({ .menuIsShow = false });
        }
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

void TextFieldPattern::DeleteBackward(int32_t length)
{
    ResetObscureTickCountDown();
    if (selectController_->GetCaretIndex() <= 0) {
        return;
    }
    UpdateEditingValueToRecord();
    if (IsSelected()) {
        Delete(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        showCountBorderStyle_ = false;
        HandleCountStyle();
        return;
    }
    inputOperations_.emplace(InputOperation::DELETE_BACKWARD);
    deleteBackwardOperations_.emplace(length);
    CloseSelectOverlay();
    ScrollToSafeArea();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::DeleteBackwardOperation(int32_t length)
{
    int32_t idx = selectController_->GetCaretIndex();
    int32_t count = contentController_->Delete(selectController_->GetCaretIndex(), length, true);
    selectController_->UpdateCaretIndex(std::max(idx - count, 0));
    if (GetIsPreviewText()) {
        UpdatePreviewIndex(GetPreviewTextStart(), GetPreviewTextEnd() - length);
    }
    StartTwinkling();
}

void TextFieldPattern::DeleteForwardOperation(int32_t length)
{
    contentController_->Delete(selectController_->GetCaretIndex(), length, false);
    if (GetIsPreviewText()) {
        UpdatePreviewIndex(GetPreviewTextStart(), GetPreviewTextEnd() - length);
    }
    StartTwinkling();
}

void TextFieldPattern::DeleteForward(int32_t length)
{
    ResetObscureTickCountDown();
    UpdateEditingValueToRecord();
    if (IsSelected()) {
        Delete(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        showCountBorderStyle_ = false;
        HandleCountStyle();
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
    if (GreatOrEqual(newOffsetY, 0.0)) {
        selectController_->MoveSecondHandleByKeyBoard(paragraph_->GetGlyphIndexByCoordinate(
            Offset(selectController_->GetCaretRect().GetX() - contentRect_.GetX(), newOffsetY)));
    } else {
        selectController_->MoveSecondHandleByKeyBoard(0);
    }
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
    if (LessOrEqual(newOffsetY, textRect_.Height())) {
        selectController_->MoveSecondHandleByKeyBoard(paragraph_->GetGlyphIndexByCoordinate(
            Offset(selectController_->GetCaretRect().GetX() - contentRect_.GetX(), newOffsetY)));
    } else {
        selectController_->MoveSecondHandleByKeyBoard(static_cast<int32_t>(contentController_->GetWideText().length()));
    }
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
    if (HasFocus() && !magnifierController_->GetShowMagnifier()) {
        StartTwinkling();
    }
    CloseSelectOverlay();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::SetSelectionFlag(
    int32_t selectionStart, int32_t selectionEnd, const std::optional<SelectionOptions>& options)
{
    if (!HasFocus()) {
        return;
    }
    isTouchCaret_ = false;
    bool isShowMenu = selectOverlay_->IsCurrentMenuVisibile();
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

    SetIsSingleHandle(!IsSelected());
    if (!IsShowHandle()) {
        CloseSelectOverlay(true);
    } else {
        if (options.has_value()) {
            if (options.value().menuPolicy == MenuPolicy::HIDE) {
                isShowMenu = false;
            } else if (options.value().menuPolicy == MenuPolicy::SHOW) {
                isShowMenu = true;
            }
        } else {
            isShowMenu = false;
        }
        if (!isShowMenu && IsUsingMouse()) {
            CloseSelectOverlay();
        } else {
            ProcessOverlay({ .menuIsShow = isShowMenu, .animation = true });
        }
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
        bool closeKeyboard = !selectOverlay_->IsCurrentMenuVisibile();
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
            return IsTextArea() ? "TextAreaType.NUMBER" : "InputType.Number";
        case TextInputType::EMAIL_ADDRESS:
            return IsTextArea() ? "TextAreaType.EMAIL" : "InputType.Email";
        case TextInputType::PHONE:
            return IsTextArea() ? "TextAreaType.PHONE_NUMBER" : "InputType.PhoneNumber";
        case TextInputType::VISIBLE_PASSWORD:
            return "InputType.Password";
        case TextInputType::USER_NAME:
            return "InputType.USER_NAME";
        case TextInputType::NEW_PASSWORD:
            return "InputType.NEW_PASSWORD";
        default:
            return isTextInput_ ? "InputType.Normal" : "TextAreaType.NORMAL";
    }
}

std::string TextFieldPattern::TextContentTypeToString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    auto contentType = layoutProperty->GetTextContentTypeValue(TextContentType::UNSPECIFIED);
    if (contentTypeMap_.find(contentType) != contentTypeMap_.end()) {
        return contentTypeMap_[contentType].second;
    }
    return contentTypeMap_[TextContentType::UNSPECIFIED].second;
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
    auto context = PipelineBase::GetCurrentContextSafely();
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
        selectOverlay_->HideMenu();
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
    if (IsTextArea()) {
        if (contentController_->IsEmpty()) {
            scrollable_ = false;
        } else {
            scrollable_ = GreatNotEqual(textRect_.Height(), contentRect_.Height());
        }
        SetScrollEnable(scrollable_);
    } else {
        SetScrollEnable(GreatNotEqual(textRect_.Width(), contentRect_.Width()));
    }
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
    auto isUnderLine = IsUnderlineMode();
    auto errorText = layoutProperty->GetErrorTextValue("");
    if (IsShowError()) { // update error state
        if (isUnderLine) {
            underlineColor_ = userUnderlineColor_.error.value_or(textFieldTheme->GetErrorUnderlineColor());
            underlineWidth_ = ERROR_UNDERLINE_WIDTH;
        } else if (passWordMode) {
            BorderWidthProperty borderWidth;
            BorderColorProperty borderColor;
            borderWidth.SetBorderWidth(textFieldTheme->GetErrorTextInputBorderWidth());
            layoutProperty->UpdateBorderWidth(borderWidth);
            borderColor.SetColor(textFieldTheme->GetPasswordErrorBorderColor());
            renderContext->UpdateBorderColor(borderColor);
            renderContext->UpdateBackgroundColor(textFieldTheme->GetPasswordErrorInputColor());
            layoutProperty->UpdateTextColor(textFieldTheme->GetPasswordErrorTextColor());
        }
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
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    MarginProperty errorMargin;
    auto errorText = layoutProperty->GetErrorTextValue("");
    if (IsShowError()) {
        CreateErrorParagraph(errorText);
        if (errorParagraph_) {
            errorParagraph_->Layout(std::numeric_limits<double>::infinity());
            auto errorTextMargin = ERROR_TEXT_TOP_MARGIN.ConvertToPx() + ERROR_TEXT_BOTTOM_MARGIN.ConvertToPx() +
                                   errorParagraph_->GetHeight();
            if (GetMarginBottom() < errorTextMargin) {
                errorMargin.bottom = CalcLength(errorTextMargin);
            }
        }
        if (paintProperty->HasMarginByUser()) {
            auto userMargin = paintProperty->GetMarginByUserValue();
            userMargin.bottom = errorMargin.bottom;
            layoutProperty->UpdateMargin(userMargin);
        } else {
            layoutProperty->UpdateMargin(errorMargin);
        }
    }
}

void TextFieldPattern::ApplyUnderlineTheme()
{
    if (!IsUnderlineMode()) {
        return;
    }
    SetThemeAttr();
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    underlineColor_ = HasFocus() ? userUnderlineColor_.typing.value_or(theme->GetUnderlineTypingColor())
                                 : userUnderlineColor_.normal.value_or(theme->GetUnderlineColor());
    underlineWidth_ = HasFocus() ? TYPING_UNDERLINE_WIDTH : UNDERLINE_WIDTH;
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

std::string TextFieldPattern::GetNormalUnderlineColorStr() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    Color normal = userUnderlineColor_.normal.value_or(theme->GetUnderlineColor());
    return normal.ColorToString();
}

std::string TextFieldPattern::GetTypingUnderlineColorStr() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    Color typing = userUnderlineColor_.typing.value_or(theme->GetUnderlineTypingColor());
    return typing.ColorToString();
}

std::string TextFieldPattern::GetDisableUnderlineColorStr() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    Color disable = userUnderlineColor_.disable.value_or(theme->GetDisableUnderlineColor());
    return disable.ColorToString();
}

std::string TextFieldPattern::GetErrorUnderlineColorStr() const
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    Color error = userUnderlineColor_.error.value_or(theme->GetErrorUnderlineColor());
    return error.ColorToString();
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

void TextFieldPattern::RestorePreInlineStates()
{
    ResetContextAttr();
    ApplyNormalTheme();
    ApplyUnderlineTheme();
    ProcessInnerPadding();
    ProcessResponseArea();
    ProcessRectPadding();
}

void TextFieldPattern::ProcessRectPadding()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_VOID(paddingProperty);
    auto top = paddingProperty->top.has_value() ? paddingProperty->top->GetDimension().ConvertToPx() : 0.0f;
    textRect_.SetTop(top);
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

void TextFieldPattern::ProcessInlinePaddingAndMargin()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    PaddingProperty userPadding;
    MarginProperty userMargin;
    if (paintProperty->HasPaddingByUser()) {
        userPadding = paintProperty->GetPaddingByUserValue();
    } else {
        auto themePadding = IsUnderlineMode() ? theme->GetUnderlinePadding() : theme->GetPadding();
        userPadding.top = CalcLength(CalcLength(themePadding.Top()).GetDimension());
        userPadding.bottom = CalcLength(CalcLength(themePadding.Bottom()).GetDimension());
        userPadding.left = CalcLength(CalcLength(themePadding.Left()).GetDimension());
        userPadding.right = CalcLength(CalcLength(themePadding.Right()).GetDimension());
    }
    if (paintProperty->HasMarginByUser()) {
        userMargin = paintProperty->GetMarginByUserValue();
    }
    MarginProperty margin;
    margin.bottom = CalcLength(userMargin.bottom->GetDimension() + userPadding.bottom->GetDimension());
    margin.right = CalcLength(userMargin.right->GetDimension() + userPadding.bottom->GetDimension());
    margin.left = CalcLength(userMargin.left->GetDimension() + userPadding.left->GetDimension());
    margin.top = CalcLength(userMargin.top->GetDimension() + userPadding.top->GetDimension());
    layoutProperty->UpdateMargin(margin);
    if (!IsTextArea()) {
        layoutProperty->UpdatePlaceholderMaxLines(layoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE));
        layoutProperty->ResetMaxLines();
    }
}

void TextFieldPattern::ApplyInlineTheme()
{
    if (!IsInlineMode()) {
        return;
    }
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
    ProcessInlinePaddingAndMargin();
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

void TextFieldPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    json->PutExtAttr("placeholder", GetPlaceHolder().c_str(), filter);
    json->PutExtAttr("text", contentController_->GetTextValue().c_str(), filter);
    json->PutExtAttr("fontSize", GetFontSize().c_str(), filter);
    json->PutExtAttr("fontColor", GetTextColor().c_str(), filter);
    json->PutExtAttr("fontStyle",
        GetItalicFontStyle() == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic", filter);
    json->PutExtAttr("fontWeight", V2::ConvertWrapFontWeightToStirng(GetFontWeight()).c_str(), filter);
    json->PutExtAttr("fontFamily", GetFontFamily().c_str(), filter);
    json->PutExtAttr("textAlign", V2::ConvertWrapTextAlignToString(GetTextAlign()).c_str(), filter);
    json->PutExtAttr("caretColor", GetCaretColor().c_str(), filter);
    json->PutExtAttr("type", TextInputTypeToString().c_str(), filter);
    json->PutExtAttr("contentType", TextContentTypeToString().c_str(), filter);
    json->PutExtAttr("placeholderColor", GetPlaceholderColor().c_str(), filter);
    json->PutExtAttr("placeholderFont", GetPlaceholderFont().c_str(), filter);
    json->PutExtAttr("enterKeyType", TextInputActionToString().c_str(), filter);
    auto maxLength = GetMaxLength();
    json->PutExtAttr("maxLength",
        GreatOrEqual(maxLength, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLength).c_str(), filter);
    json->PutExtAttr("inputFilter", GetInputFilter().c_str(), filter);
    json->PutExtAttr("copyOption", GetCopyOptionString().c_str(), filter);
    json->PutExtAttr("style", GetInputStyleString().c_str(), filter);

    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("onIconSrc", GetShowResultImageSrc().c_str());
    jsonValue->Put("offIconSrc", GetHideResultImageSrc().c_str());
    json->PutExtAttr("passwordIcon", jsonValue->ToString().c_str(), filter);
    json->PutExtAttr("showError", GetErrorTextState() ? GetErrorTextString().c_str() : "undefined", filter);
    auto maxLines = GetMaxLines();
    json->PutExtAttr("maxLines",
        GreatOrEqual(maxLines, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLines).c_str(), filter);
    json->PutExtAttr("barState", GetBarStateString().c_str(), filter);
    json->PutExtAttr("caretPosition", std::to_string(GetCaretIndex()).c_str(), filter);
    json->PutExtAttr("normalUnderlineColor", GetNormalUnderlineColorStr().c_str(), filter);
    json->PutExtAttr("typingUnderlineColor", GetTypingUnderlineColorStr().c_str(), filter);
    json->PutExtAttr("errorUnderlineColor", GetErrorUnderlineColorStr().c_str(), filter);
    json->PutExtAttr("disableUnderlineColor", GetDisableUnderlineColorStr().c_str(), filter);
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
    json->PutExtAttr("showCounter", jsonShowCounter, filter);
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
    CopyOptions copyOptionsEnum = CopyOptions::None;
    auto iter = uMap.find(copyOption);
    if (iter != uMap.end()) {
        copyOptionsEnum = iter->second;
    }
    layoutProperty->UpdateCopyOptions(copyOptionsEnum);
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

    accessibilityProperty->SetActionSetSelection([weakPtr = WeakClaim(this)](int32_t start,
                                                                             int32_t end, bool isForward) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetSelectionFlag(start, end, std::nullopt);
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
        pattern->SetSelectionFlag(current, current, std::nullopt);
        pattern->CloseSelectOverlay(true);
        pattern->StartTwinkling();
    });
    SetAccessibilityActionGetAndSetCaretPosition();
    SetAccessibilityScrollAction();
    SetAccessibilityMoveTextAction();
}

void TextFieldPattern::SetAccessibilityActionGetAndSetCaretPosition()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSetIndex([weakPtr = WeakClaim(this)](int32_t index) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetCaretPosition(index);
    });

    accessibilityProperty->SetActionGetIndex([weakPtr = WeakClaim(this)]() -> int32_t {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, -1);
        auto index = pattern->selectController_->GetCaretIndex();
        return index;
    });
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
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Stop Editing");
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (HasConnection() || isCustomKeyboardAttached_) {
#else
    if (isCustomKeyboardAttached_) {
#endif
        FocusHub::LostFocusToViewRoot();
    }
    UpdateSelection(selectController_->GetCaretIndex());
    StopTwinkling();
    CloseKeyboard(true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::DumpInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    DumpLog::GetInstance().AddDesc(std::string("Content:").append(GetTextValue()));
    DumpLog::GetInstance().AddDesc(std::string("MaxLength:").append(std::to_string(GetMaxLength())));
    DumpLog::GetInstance().AddDesc(std::string("InputFilter:").append(GetInputFilter()));
    DumpLog::GetInstance().AddDesc(std::string("CopyOption:").append(GetCopyOptionString()));
    DumpLog::GetInstance().AddDesc(std::string("TextAlign:").append(std::to_string((int32_t)GetTextAlign())));
    DumpLog::GetInstance().AddDesc(std::string("CaretPosition:").append(std::to_string(GetCaretIndex())));
    DumpLog::GetInstance().AddDesc(
        std::string("enableKeyboardOnFocus:").append(std::to_string(needToRequestKeyboardOnFocus_)));
    DumpLog::GetInstance().AddDesc(
        std::string("enableAutoFill:").append(std::to_string(layoutProperty->GetEnableAutoFillValue(true))));
    DumpLog::GetInstance().AddDesc(std::string("HasFocus:").append(std::to_string(HasFocus())));
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::TextConfig textConfig = miscTextConfig.value();
    DumpLog::GetInstance().AddDesc(std::string("RequestKeyboard calling window :")
                                       .append(std::to_string(textConfig.windowId))
                                       .append(std::string("inputType:"))
                                       .append(std::to_string(textConfig.inputAttribute.inputPattern))
                                       .append(std::string("enterKeyType:"))
                                       .append(std::to_string(textConfig.inputAttribute.enterKeyType)));
#endif
    DumpLog::GetInstance().AddDesc(textSelector_.ToString());
    if (customKeyboard_) {
        DumpLog::GetInstance().AddDesc(std::string("CustomKeyboard: true")
                                           .append(", Attached: ")
                                           .append(std::to_string(isCustomKeyboardAttached_)));
    }
    DumpLog::GetInstance().AddDesc(std::string("wordBreak:")
        .append(V2::ConvertWrapWordBreakToString(layoutProperty->GetWordBreak().value_or(WordBreak::BREAK_WORD))));
}

void TextFieldPattern::DumpAdvanceInfo()
{
    if (customKeyboard_) {
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
    auto autoFillType = GetAutoFillType();
    auto info = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    CHECK_NULL_VOID(info);
    info->SetId(host->GetId());
    info->SetDepth(host->GetDepth());
    info->SetAutoFillType(autoFillType);
    info->SetTag(host->GetTag());
    if (!autoFillUserName_.empty()) {
        viewDataWrap->SetUserSelected(true);
        info->SetValue(autoFillUserName_);
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "autoFillUserName_ : %{private}s", autoFillUserName_.c_str());
        autoFillUserName_ = "";
    } else if (!autoFillNewPassword_.empty()) {
        info->SetValue(autoFillNewPassword_);
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "autoFillNewPassword_ : %{private}s", autoFillNewPassword_.c_str());
        autoFillNewPassword_ = "";
    } else if (autoFillOtherAccount_) {
        viewDataWrap->SetOtherAccount(true);
        info->SetValue(contentController_->GetTextValue());
        autoFillOtherAccount_ = false;
    } else {
        info->SetValue(contentController_->GetTextValue());
        viewDataWrap->SetUserSelected(false);
        viewDataWrap->SetOtherAccount(false);
    }
    info->SetPlaceholder(GetPlaceHolder());
    info->SetPasswordRules(layoutProperty->GetPasswordRulesValue(""));
    info->SetEnableAutoFill(layoutProperty->GetEnableAutoFillValue(true));
    auto offsetToWindow = host->GetOffsetRelativeToWindow();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pageNodeRect = geometryNode->GetFrameRect();
    pageNodeRect.SetLeft(offsetToWindow.GetX());
    pageNodeRect.SetTop(offsetToWindow.GetY());
    info->SetPageNodeRect(pageNodeRect);
    info->SetIsFocus(HasFocus());
    viewDataWrap->AddPageNodeInfoWrap(info);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    viewDataWrap->SetPageRect(pipeline->GetRootRect());
}

void TextFieldPattern::NotifyFillRequestSuccess(RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "autoFillType:%{public}d", static_cast<int32_t>(autoFillType));
    SetFillRequestFinish(true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(nodeWrap);
    auto isFocus = nodeWrap->GetIsFocus();
    if (isFocus && !HasFocus()) {
        auto focusHub = host->GetOrCreateFocusHub();
        focusHub->RequestFocusImmediately();
        DoProcessAutoFill();
    }
    if (!contentController_ || contentController_->GetTextValue() == nodeWrap->GetValue()) {
        return;
    }
    contentController_->SetTextValue(nodeWrap->GetValue());
    NotifyOnEditChanged(true);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto type = GetAutoFillType();
    if (!(type == AceAutoFillType::ACE_NEW_PASSWORD && type == autoFillType)) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "Set last auto fill text value.");
        lastAutoFillPasswordTextValue_ = nodeWrap->GetValue();
    }
}

void TextFieldPattern::NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "errCode:%{public}d", errCode);
    SetFillRequestFinish(true);
    if (errCode == AUTO_FILL_FAILED) {
        return;
    }
#if defined(ENABLE_STANDARD_INPUT)
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "fillContent is : %{private}s", fillContent.c_str());
    std::unordered_map<std::string, MiscServices::PrivateDataValue> userNamesOrPassWordMap;
    while (errCode == AUTO_FILL_CANCEL && IsAutoFillPasswordType(GetAutoFillType())) {
        auto jsonObject = JsonUtil::ParseJsonString(fillContent);
        if (jsonObject == nullptr) {
            break;
        }
        if (jsonObject->Contains("userName")) {
            userNamesOrPassWordMap.insert(std::pair<std::string, MiscServices::PrivateDataValue>(
                AUTO_FILL_PARAMS_USERNAME, jsonObject->GetString("userName")));
        } else if (jsonObject->Contains("newPassword")) {
            userNamesOrPassWordMap.insert(std::pair<std::string, MiscServices::PrivateDataValue>(
                AUTO_FILL_PARAMS_NEWPASSWORD, jsonObject->GetString("newPassword")));
        } else {
            TAG_LOGE(AceLogTag::ACE_AUTO_FILL, "fillContent is empty");
            break;
        }
        MiscServices::InputMethodController::GetInstance()->SendPrivateCommand(userNamesOrPassWordMap);
        if (system::GetBoolParameter(AUTO_FILL_TEST, false)) {
            if (textChangeListener_ == nullptr) {
                textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
            }
            auto task = [textChangeListener = textChangeListener_, userNamesOrPassWordMap] {
                CHECK_NULL_VOID(textChangeListener);
                textChangeListener->ReceivePrivateCommand(userNamesOrPassWordMap);
            };
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostDelayedTask(task, TaskExecutor::TaskType::UI, 3000, "testInputMethodAutoFill");
        }
        break;
    }
#endif
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
    auto autoFillType = GetAutoFillType();
    if (autoFillType == AceAutoFillType::ACE_USER_NAME) {
        if (!lastAutoFillPasswordTextValue_.empty() &&
            contentController_->GetTextValue() != lastAutoFillPasswordTextValue_) {
            return true;
        }
    }
    if (AceAutoFillType::ACE_UNSPECIFIED < autoFillType && autoFillType <= AceAutoFillType::ACE_FORMAT_ADDRESS &&
        autoFillType != AceAutoFillType::ACE_USER_NAME) {
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
    return startOffset + GetPaintRectGlobalOffset();
}

void TextFieldPattern::OnColorConfigurationUpdate()
{
    colorModeChange_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->HasTextColorFlagByUser()) {
        layoutProperty->UpdateTextColor(theme->GetTextColor());
    }
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
    if (selectOverlay_->HasRenderTransform()) {
        return selectOverlay_->GetPaintRectOffsetWithTransform();
    }
    return GetPaintRectGlobalOffset();
}

OffsetF TextFieldPattern::GetPaintRectGlobalOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0.0f, 0.0f));
    auto pipeline = host->GetContextRefPtr();
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

void TextFieldPattern::OnAttachToFrameNode()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCopyOptions(CopyOptions::Distributed);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        auto host = GetHost();
        fontManager->AddFontNodeNG(host);
    }
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

void TextFieldPattern::OnObscuredChanged(bool isObscured)
{
    ResetObscureTickCountDown();
    obscuredChange_ = textObscured_ != isObscured;
    textObscured_ = isObscured;
    CloseSelectOverlay(false);
    selectController_->UpdateCaretIndex(static_cast<int32_t>(contentController_->GetWideText().length()));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (obscuredChange_) {
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->FireOnSecurityStateChanged(!isObscured);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::CreateHandles()
{
    if (IsDragging() || !HasFocus()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    showSelect_ = true;
    if (selectOverlay_->IsUseTouchAtLast()) {
        SetIsSingleHandle(!IsSelected());
        ProcessOverlay({ .menuIsShow = false });
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::NotifyOnEditChanged(bool isChanged)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (isChanged != isEdit_) {
        isEdit_ = isChanged;
        eventHub->FireOnEditChanged(isChanged);
    }
}

int32_t TextFieldPattern::GetLineCount() const
{
    return paragraph_ ? paragraph_->GetLineCount() : 0;
}

void TextFieldPattern::UpdateHandlesOffsetOnScroll(float offset)
{
    if (SelectOverlayIsOn()) {
        selectController_->UpdateSecondHandleOffset();
        if (!selectOverlay_->IsSingleHandle()) {
            selectController_->UpdateFirstHandleOffset();
            selectController_->UpdateCaretOffset();
            selectOverlay_->UpdateAllHandlesOffset();
        } else {
            auto carectOffset = selectController_->GetCaretRect().GetOffset() +
                                (IsTextArea() ? OffsetF(0.0f, offset) : OffsetF(offset, 0.0f));
            selectController_->UpdateCaretOffset(carectOffset);
            selectOverlay_->UpdateSecondHandleOffset();
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
    auto typeValue = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    return layoutProperty->GetShowUnderlineValue(false) &&
           (typeValue == TextInputType::UNSPECIFIED || typeValue == TextInputType::TEXT);
}

bool TextFieldPattern::IsShowPasswordIcon() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);

    auto textfieldTheme = GetTheme();
    bool isShowPasswordIcon = textfieldTheme->IsShowPasswordIcon();
    return layoutProperty->GetShowPasswordIconValue(isShowPasswordIcon) && IsInPasswordMode();
}

std::optional<bool> TextFieldPattern::IsShowPasswordText() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowPasswordText();
}

bool TextFieldPattern::IsShowCancelButtonMode() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return !IsNormalInlineState() && !IsTextArea() && layoutProperty->GetIsShowCancelButton().value_or(false);
}

void TextFieldPattern::CheckPasswordAreaState()
{
    auto showPasswordState = IsShowPasswordText();
    if (!showPasswordState.has_value()) {
        return;
    }
    auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea_);
    CHECK_NULL_VOID(passwordArea);
    passwordArea->SetObscured(!showPasswordState.value());
}

void TextFieldPattern::ProcessResponseArea()
{
    if (IsShowCancelButtonMode()) {
        auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
        if (cleanNodeResponseArea) {
            cleanNodeResponseArea->Refresh();
            cleanNodeResponseArea->UpdateCleanNode(cleanNodeResponseArea->IsShow());
        } else {
            cleanNodeResponseArea_ = AceType::MakeRefPtr<CleanNodeResponseArea>(WeakClaim(this));
            cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
            cleanNodeResponseArea->InitResponseArea();
            UpdateCancelNode();
        }
    } else {
        if (cleanNodeResponseArea_) {
            cleanNodeResponseArea_->ClearArea();
            cleanNodeResponseArea_.Reset();
        }
    }
    if (IsInPasswordMode()) {
        auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea_);
        if (passwordArea) {
            if (IsShowPasswordIcon()) {
                passwordArea->Refresh();
            } else {
                passwordArea->ClearArea();
            }
            CheckPasswordAreaState();
            return;
        }
        // responseArea_ may not be a password area.
        responseArea_ = AceType::MakeRefPtr<PasswordResponseArea>(WeakClaim(this), GetTextObscured());
        if (IsShowPasswordIcon()) {
            responseArea_->InitResponseArea();
        } else {
            responseArea_->ClearArea();
        }
        CheckPasswordAreaState();
        return;
    }

    if (IsUnderlineMode()) {
        responseArea_ = AceType::MakeRefPtr<UnitResponseArea>(WeakClaim(this), unitNode_);
        responseArea_->InitResponseArea();
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
    }
    if (focusIndex_ == FocuseIndex::CANCEL && HasFocus()) {
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
    CHECK_NULL_VOID(!IsDragging());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    InitEditingValueText("");
    CloseSelectOverlay();
    StartTwinkling();
    if (!HasFocus()) {
        auto focusHub = host->GetOrCreateFocusHub();
        focusHub->RequestFocusImmediately();
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::OnVirtualKeyboardAreaChanged()
{
    CHECK_NULL_VOID(SelectOverlayIsOn());
    selectController_->CalculateHandleOffset();
}

void TextFieldPattern::RegisterWindowSizeCallback()
{
    if (isOritationListenerRegisted_) {
        return;
    }
    isOritationListenerRegisted_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowSizeChangeCallback(host->GetId());
}

void TextFieldPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    CHECK_NULL_VOID(SelectOverlayIsOn());
    if (type == WindowSizeChangeReason::ROTATION) {
        selectController_->CalculateHandleOffset();
        selectOverlay_->ProcessOverlayOnAreaChanged({ .menuIsShow = false});
    }
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
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->ScrollTextFieldToSafeArea();
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
    if (focusHub->IsCurrentFocus()) {
        isCursorAlwaysDisplayed_ = true;
        StartTwinkling();
    }
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
    if (IsNormalInlineState()) {
        return;
    }
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

void TextFieldPattern::CheckTextAlignByDirection(TextAlign& textAlign, TextDirection direction)
{
    if (direction == TextDirection::RTL) {
        if (textAlign == TextAlign::START) {
            textAlign = TextAlign::END;
        } else if (textAlign == TextAlign::END) {
            textAlign = TextAlign::START;
        }
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

void TextFieldPattern::ScrollPage(bool reverse, bool smooth)
{
    float maxFrameHeight = maxFrameHeight_ - GetMarginBottom() - maxFrameOffsetY_;
    float distance = reverse ? maxFrameHeight : -maxFrameHeight;
    OnScrollCallback(distance, SCROLL_FROM_JUMP);
}

// correct after OnModifyDone
bool TextFieldPattern::IsUnderlineMode()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType() && !IsInlineMode();
}

// correct after OnModifyDone
bool TextFieldPattern::IsInlineMode()
{
    return HasFocus() && IsNormalInlineState();
}

bool TextFieldPattern::IsShowError()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto errorText = layoutProperty->GetErrorTextValue("");
    return layoutProperty->GetShowErrorTextValue(false) && !errorText.empty() && !IsNormalInlineState();
}

bool TextFieldPattern::IsShowCount()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowCounterValue(false) && !IsNormalInlineState() && !IsInPasswordMode() &&
           layoutProperty->HasMaxLength();
}

void TextFieldPattern::ResetContextAttr()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->ResetBorder();
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateBorderWidth(borderWidth);
}

void TextFieldPattern::SetThemeBorderAttr()
{
    auto host= GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    if (!paintProperty->HasBorderColorFlagByUser()) {
        BorderColorProperty borderColor;
        borderColor.SetColor(theme->GetTextInputColor());
        renderContext->UpdateBorderColor(borderColor);
    } else {
        renderContext->UpdateBorderColor(paintProperty->GetBorderColorFlagByUserValue());
    }

    if (!paintProperty->HasBorderRadiusFlagByUser()) {
        auto radius = theme->GetBorderRadius();
        BorderRadiusProperty borderRadius(radius.GetX(), radius.GetY(), radius.GetY(), radius.GetX());
        auto ultimatelyRadius = IsUnderlineMode() ?  ZERO_BORDER_RADIUS_PROPERTY : borderRadius;
        renderContext->UpdateBorderRadius(ultimatelyRadius);
    } else {
        renderContext->UpdateBorderRadius(paintProperty->GetBorderRadiusFlagByUserValue());
    }

    if (!paintProperty->HasBorderWidthFlagByUser()) {
        BorderWidthProperty borderWidth;
        borderWidth.SetBorderWidth(theme->GetTextInputWidth());
        renderContext->UpdateBorderWidth(borderWidth);
        layoutProperty->UpdateBorderWidth(borderWidth);
    } else {
        renderContext->UpdateBorderWidth(paintProperty->GetBorderWidthFlagByUserValue());
        layoutProperty->UpdateBorderWidth(paintProperty->GetBorderWidthFlagByUserValue());
    }
}

void TextFieldPattern::SetThemeAttr()
{
    auto host= GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    SetThemeBorderAttr();
    if (!paintProperty->HasBackgroundColor()) {
        auto backgroundColor = IsUnderlineMode() ? Color::TRANSPARENT : theme->GetBgColor();
        renderContext->UpdateBackgroundColor(backgroundColor);
    } else {
        renderContext->UpdateBackgroundColor(paintProperty->GetBackgroundColorValue());
    }

    if (!paintProperty->HasMarginByUser()) {
        MarginProperty margin;
        margin.SetEdges(CalcLength(0.0_vp));
        layoutProperty->UpdateMargin(margin);
    } else {
        layoutProperty->UpdateMargin(paintProperty->GetMarginByUserValue());
    }

    if (!paintProperty->HasPaddingByUser()) {
        auto themePadding = IsUnderlineMode() ? theme->GetUnderlinePadding() : theme->GetPadding();
        PaddingProperty padding;
        padding.top = CalcLength(CalcLength(themePadding.Top()).GetDimension());
        padding.bottom = CalcLength(CalcLength(themePadding.Bottom()).GetDimension());
        padding.left = CalcLength(CalcLength(themePadding.Left()).GetDimension());
        padding.right = CalcLength(CalcLength(themePadding.Right()).GetDimension());
        layoutProperty->UpdatePadding(padding);
    } else {
        layoutProperty->UpdatePadding(paintProperty->GetPaddingByUserValue());
    }

    if (!paintProperty->HasTextColorFlagByUser()) {
        layoutProperty->UpdateTextColor(theme->GetTextColor());
    } else {
        layoutProperty->UpdateTextColor(paintProperty->GetTextColorFlagByUserValue());
    }
}

const Dimension& TextFieldPattern::GetAvoidSoftKeyboardOffset() const
{
    auto textfieldTheme = GetTheme();
    if (!textfieldTheme) {
        return TextBase::GetAvoidSoftKeyboardOffset();
    }
    return textfieldTheme->GetAvoidKeyboardOffset();
}

Offset TextFieldPattern::ConvertGlobalToLocalOffset(const Offset& globalOffset)
{
    auto localOffset = globalOffset - Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY());
    if (selectOverlay_->HasRenderTransform()) {
        auto localOffsetF = OffsetF(globalOffset.GetX(), globalOffset.GetY());
        selectOverlay_->RevertLocalPointWithTransform(localOffsetF);
        localOffset.SetX(localOffsetF.GetX());
        localOffset.SetY(localOffsetF.GetY());
    }
    return localOffset;
}

int32_t TextFieldPattern::SetPreviewText(const std::string &previewValue, const PreviewRange range)
{
    PreviewTextInfo info = {
        .text = previewValue,
        .range = range
    };
    if (!CheckPreviewTextValidate(info)) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "wrong info, can't show preview text");
        return PREVIEW_BAD_PARAMETERS;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, PREVIEW_NULL_POINTER);
    inputOperations_.emplace(InputOperation::SET_PREVIEW_TEXT);
    previewTextOperation.emplace(info);
    CloseSelectOverlay(true);
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    return PREVIEW_NO_ERROR;
}

void TextFieldPattern::SetPreviewTextOperation(PreviewTextInfo info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto rangeStart = info.range.start;
    auto rangeEnd = info.range.end;
    auto start = GetPreviewTextStart();
    auto end = GetPreviewTextEnd();
    if (IsSelected()) {
        start = selectController_->GetStartIndex();
        end = selectController_->GetEndIndex();
    } else {
        start = (rangeStart == PREVIEW_TEXT_RANGE_DEFAULT) ? start : rangeStart;
        end = (rangeEnd == PREVIEW_TEXT_RANGE_DEFAULT) ? end : rangeEnd;
    }

    bool hasInsertValue = false;
    auto originLength = static_cast<int32_t>(contentController_->GetWideText().length()) - (end - start);
    hasInsertValue = contentController_->ReplaceSelectedValue(start, end, info.text);
    int32_t caretMoveLength = abs(static_cast<int32_t>(contentController_->GetWideText().length()) - originLength);

    int32_t delta =
            static_cast<int32_t>(contentController_->GetWideText().length()) - originLength - (end - start);
    int32_t newCaretPosition = std::max(end, GetPreviewTextEnd()) + delta;
    newCaretPosition = std::clamp(newCaretPosition, 0,
        static_cast<int32_t>(contentController_->GetWideText().length()));
    selectController_->UpdateCaretIndex(start + caretMoveLength);

    if (layoutProperty->HasMaxLength()) {
        showCountBorderStyle_ = (originLength + StringUtils::ToWstring(info.text).length()) >
            layoutProperty->GetMaxLengthValue(Infinity<uint32_t>());
        HandleCountStyle();
    }

    UpdatePreviewIndex(start, newCaretPosition);
    hasPreviewText = true;
    cursorVisible_ = true;
    StartTwinkling();
}

void TextFieldPattern::FinishTextPreview()
{
    inputOperations_.emplace(InputOperation::SET_PREVIEW_FINISH);
    auto host = GetHost();
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::FinishTextPreviewOperation()
{
    if (!hasPreviewText) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "input state now is not at previewing text");
        return;
    }

    UpdateEditingValueToRecord();
    cursorVisible_ = true;
    StartTwinkling();

    hasPreviewText = false;
    previewTextStart_ = PREVIEW_TEXT_RANGE_DEFAULT;
    previewTextEnd_ = PREVIEW_TEXT_RANGE_DEFAULT;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

std::vector<RectF> TextFieldPattern::GetPreviewTextRects() const
{
    if (!GetIsPreviewText()) {
        return {};
    }
    std::vector<RectF> previewTextRects;
    CHECK_NULL_RETURN(paragraph_, previewTextRects);
    paragraph_->GetRectsForRange(GetPreviewTextStart(), GetPreviewTextEnd(), previewTextRects);
    return previewTextRects;
}

bool TextFieldPattern::NeedDrawPreviewText()
{
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);

    auto caretInfo = selectController_->GetCaretInfo();
    if (!paintProperty->HasPreviewTextStart() || !paintProperty->HasPreviewTextEnd()) {
        paintProperty->UpdatePreviewTextStart(caretInfo.index);
        paintProperty->UpdatePreviewTextEnd(caretInfo.index);
    }

    auto paintStart = paintProperty->GetPreviewTextStart();
    auto paintEnd =paintProperty->GetPreviewTextEnd();
    if (!GetIsPreviewText()) {
        if (!paintStart.has_value() || paintEnd.has_value()) {
            paintProperty->UpdatePreviewTextStart(caretInfo.index);
            paintProperty->UpdatePreviewTextEnd(caretInfo.index);
            return false;
        }

        // end paint
        if (paintStart != paintEnd || paintStart.value() != caretInfo.index) {
            paintProperty->UpdatePreviewTextStart(caretInfo.index);
            paintProperty->UpdatePreviewTextEnd(caretInfo.index);
            return true;
        }
        return false;
    }
    auto needDraw = paintStart.value() != GetPreviewTextStart() ||
                     paintEnd.value() != GetPreviewTextEnd();
    paintProperty->UpdatePreviewTextStart(GetPreviewTextStart());
    paintProperty->UpdatePreviewTextEnd(GetPreviewTextEnd());
    return needDraw;
}

bool TextFieldPattern::CheckPreviewTextValidate(PreviewTextInfo info) const
{
    auto start = info.range.start;
    auto end = info.range.end;
    if (start != end && (start == PREVIEW_TEXT_RANGE_DEFAULT || end == PREVIEW_TEXT_RANGE_DEFAULT)) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "range is not [-1,-1] or legal range");
        return false;
    }

    // unsupported insert preview text when caretIndex outside of range
    auto caretIndex = selectController_->GetCaretIndex();
    if (start != PREVIEW_TEXT_RANGE_DEFAULT && (start > caretIndex || end < caretIndex)) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "unsupported insert preview text when caretIndex outside of range");
        return false;
    }

    if (start != PREVIEW_TEXT_RANGE_DEFAULT && IsSelected()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "unsupported insert preview text when IsSelected");
        return false;
    }
    return true;
}

PreviewTextStyle TextFieldPattern::GetPreviewTextStyle() const
{
    auto defaultStyle = PreviewTextStyle::NORMAL;
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, defaultStyle);
    if (paintProperty->HasPreviewTextStyle()) {
        auto style = paintProperty->GetPreviewTextStyle();
        if (style.value() == PREVIEW_STYLE_NORMAL) {
            return PreviewTextStyle::NORMAL;
        } else if (style.value() == PREVIEW_STYLE_UNDERLINE) {
            return PreviewTextStyle::UNDERLINE;
        }
    }
    return defaultStyle;
}

void TextFieldPattern::ReceivePreviewTextStyle(const std::string& style)
{
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!style.empty()) {
        paintProperty->UpdatePreviewTextStyle(style);
    }
}

void TextFieldPattern::CalculatePreviewingTextMovingLimit(const Offset& touchOffset, double& limitL, double& limitR)
{
    float offsetX = IsTextArea() ? contentRect_.GetX() : GetTextRect().GetX();
    float offsetY = IsTextArea() ? GetTextRect().GetX() : contentRect_.GetX();
    std::vector<RectF> previewTextRects = GetPreviewTextRects();
    if (GreatNotEqual(touchOffset.GetY(), previewTextRects.back().Bottom() + offsetY)) {
        limitL = previewTextRects.back().Left() + offsetX + MINIMAL_OFFSET;
        limitR = previewTextRects.back().Right() + offsetX - MINIMAL_OFFSET;
    } else if (GreatNotEqual(touchOffset.GetY(), previewTextRects.front().Top() + offsetY)) {
        limitL = previewTextRects.front().Left() + offsetX + MINIMAL_OFFSET;
        limitR = previewTextRects.front().Right() + offsetX - MINIMAL_OFFSET;
    } else {
        for (const auto& drawRect : previewTextRects) {
            if (GreatOrEqual(touchOffset.GetY(), drawRect.Top() + offsetY)
                && LessOrEqual(touchOffset.GetY(), drawRect.Bottom() + offsetY)) {
                limitL = drawRect.Left() + offsetX + MINIMAL_OFFSET;
                limitR = drawRect.Right() + offsetX - MINIMAL_OFFSET;
                break;
            }
        }
    }
}
} // namespace OHOS::Ace::NG
