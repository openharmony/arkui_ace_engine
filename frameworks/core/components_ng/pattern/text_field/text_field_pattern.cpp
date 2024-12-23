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
#include <atomic>
#include <cstdint>
#include <optional>
#include <ratio>
#include <regex>
#include <string>
#include <utility>
#include "base/geometry/dimension.h"
#include "base/memory/type_info_base.h"
#include "base/utils/utf_helper.h"
#include "core/common/ime/constant.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_component_decorator.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/pipeline/pipeline_base.h"
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/i18n/localization.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/ime/input_method_manager.h"
#include "core/common/ime/text_edit_controller.h"
#include "core/common/ime/text_input_client.h"
#include "core/common/ime/text_input_connection.h"
#include "core/common/ime/text_input_formatter.h"
#include "core/common/ime/text_input_type.h"
#include "core/common/ime/text_selection.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/common/vibrator/vibrator_utils.h"
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
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/text/text_emoji_processor.h"
#ifndef ACE_UNITTEST
#ifdef ENABLE_STANDARD_INPUT
#include "parameters.h"

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"
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
constexpr Dimension ERROR_BORDER_WIDTH = 1.0_vp;
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
constexpr int32_t ILLEGAL_VALUE = 0;
constexpr double VELOCITY = -1000;
constexpr double MASS = 1.0;
constexpr double STIFFNESS = 428.0;
constexpr double DAMPING = 10.0;
constexpr uint32_t TWINKLING_INTERVAL_MS = 500;
constexpr uint32_t RECORD_MAX_LENGTH = 20;
constexpr uint32_t OBSCURE_SHOW_TICKS = 1;
constexpr int32_t FIND_TEXT_ZERO_INDEX = 1;
constexpr char16_t OBSCURING_CHARACTER = u'•';
constexpr char16_t OBSCURING_CHARACTER_FOR_AR = u'*';
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
const std::string INSPECTOR_PREFIX = "__SearchField__";
const std::string ERRORNODE_PREFIX = "ErrorNodeField__";
constexpr Dimension FLOATING_CARET_SHOW_ORIGIN_CARET_DISTANCE = 10.0_vp;
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
const std::string AUTO_FILL_PARAMS_USERNAME = "com.autofill.params.userName";
const std::string AUTO_FILL_PARAMS_NEWPASSWORD = "com.autofill.params.newPassword";
constexpr int32_t MAX_FILL_CONTENT_SIZE = 5;
constexpr int32_t DEFAULT_MODE = -1;
constexpr int32_t PREVIEW_TEXT_RANGE_DEFAULT = -1;
const std::string PREVIEW_STYLE_NORMAL = "normal";
const std::string PREVIEW_STYLE_UNDERLINE = "underline";

constexpr int32_t PREVIEW_NO_ERROR = 0;
constexpr int32_t PREVIEW_NULL_POINTER = 1;
constexpr int32_t PREVIEW_BAD_PARAMETERS = -1;
constexpr double MINIMAL_OFFSET = 0.01f;
constexpr int32_t KEYBOARD_DEFAULT_API = 9;
constexpr float RICH_DEFAULT_SHADOW_COLOR = 0x33000000;
constexpr float RICH_DEFAULT_ELEVATION = 120.0f;
constexpr float TIME_UNIT = 1000.0f;
constexpr float MAX_DRAG_SCROLL_SPEED = 2400.0f;
constexpr Dimension AUTO_SCROLL_HOT_ZONE_HEIGHT = 58.0_vp;
constexpr Dimension AUTO_SCROLL_HOT_ZONE_WIDTH = 26.0_vp;
constexpr float AUTO_SCROLL_HOT_AREA_LONGPRESS_DURATION = 80.0f;
constexpr Dimension AUTO_SCROLL_HOT_AREA_LONGPRESS_DISTANCE = 5.0_vp;
constexpr Dimension MOUSE_SCROLL_BAR_REGION_WIDTH = 8.0_vp;

static std::unordered_map<AceAutoFillType, TextInputType> keyBoardMap_ = {
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
    result = result.substr(0, static_cast<int32_t>(result.length()) - 1);
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
        textFieldOverlayModifier_ =
            AceType::MakeRefPtr<TextFieldOverlayModifier>(WeakClaim(this), GetScrollEdgeEffect());
        SetScrollBarOverlayModifier(textFieldOverlayModifier_);
    }
    if (!textFieldForegroundModifier_) {
        textFieldForegroundModifier_ = AceType::MakeRefPtr<TextFieldForegroundModifier>(WeakClaim(this));
    }
    if (isCustomFont_) {
        textFieldContentModifier_->SetIsCustomFont(true);
    }
    auto paint = AceType::MakeRefPtr<TextFieldPaintMethod>(
        WeakClaim(this), textFieldOverlayModifier_, textFieldContentModifier_, textFieldForegroundModifier_);
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        paint->SetScrollBar(scrollBar);
        if (scrollBar->NeedPaint()) {
            textFieldOverlayModifier_->SetRect(scrollBar->GetActiveRect());
        } else if (IsNormalInlineState() && !HasFocus()) {
            auto inlineScrollRect = scrollBar->GetActiveRect();
            CalcInlineScrollRect(inlineScrollRect);
            textFieldOverlayModifier_->SetRect(inlineScrollRect);
            textFieldOverlayModifier_->SetOpacity(0);
        }
    }
    CalculateBoundsRect();
    return paint;
}

void TextFieldPattern::CalculateBoundsRect()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto geometryNode = host->GetGeometryNode();
    auto frameOffset = geometryNode->GetFrameOffset();
    auto frameSize = geometryNode->GetFrameSize();
    bool isShowCount = IsShowCount() && !IsTextArea();
    bool isShowError = layoutProperty->GetShowErrorTextValue(false) && errorDecorator_;
    if (isShowCount && isShowError) {
        auto textWidth = std::max(errorDecorator_ ? errorDecorator_->GetContentWidth() : 0.0f, frameSize.Width());
        auto errorHeight = errorDecorator_? errorDecorator_->GetBoundHeight() : 0.0f;
        auto countHeight = counterDecorator_? counterDecorator_->GetBoundHeight() : 0.0f;
        auto bottomHeight = std::max(errorHeight, countHeight);
        RectF boundsRect(0.0f, 0.0f, textWidth, bottomHeight + frameSize.Height());
        textFieldOverlayModifier_->SetBoundsRect(boundsRect);
        textFieldForegroundModifier_->SetBoundsRect(boundsRect);
    } else if (isShowCount) {
        auto countHeight = counterDecorator_? counterDecorator_->GetBoundHeight() : 0.0f;
        RectF boundsRect(0.0f, 0.0f, frameSize.Width(), countHeight + frameSize.Height());
        textFieldOverlayModifier_->SetBoundsRect(boundsRect);
        textFieldForegroundModifier_->SetBoundsRect(boundsRect);
    } else if (isShowError) {
        auto textWidth = std::max(errorDecorator_ ? errorDecorator_->GetContentWidth() : 0.0f, frameSize.Width());
        auto errorHeight = errorDecorator_? errorDecorator_->GetBoundHeight() : 0.0f;
        RectF boundsRect(0.0f, 0.0f, textWidth, errorHeight + frameSize.Height());
        textFieldOverlayModifier_->SetBoundsRect(boundsRect);
        textFieldForegroundModifier_->SetBoundsRect(boundsRect);
    } else {
        if (NearEqual(maxFrameOffsetY_, 0.0f) && NearEqual(maxFrameHeight_, 0.0f)) {
            maxFrameOffsetY_ = frameOffset.GetY();
            maxFrameHeight_ = frameSize.Height();
        }
        maxFrameOffsetY_ = LessOrEqual(frameOffset.GetY(), maxFrameOffsetY_) ? frameOffset.GetY()
                                                                             : maxFrameOffsetY_ - frameOffset.GetY();
        maxFrameHeight_ = LessOrEqual(frameSize.Height(), maxFrameHeight_) ? maxFrameHeight_ : frameSize.Height();
        RectF boundsRect(0.0f, 0.0f, frameSize.Width(), maxFrameHeight_ + UNDERLINE_WIDTH.ConvertToPx());
        textFieldOverlayModifier_->SetBoundsRect(boundsRect);
        textFieldForegroundModifier_->SetBoundsRect(boundsRect);
    }
}

void TextFieldPattern::CalcInlineScrollRect(Rect& inlineScrollRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBar = GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    Size size(frameRect_.Width(), inlineMeasureItem_.inlineSizeHeight);
    auto positionMode_ = scrollBar->GetPositionMode();
    double mainSize = (positionMode_ == PositionMode::BOTTOM ? size.Width() : size.Height());
    auto barRegionSize = mainSize;
    double estimatedHeight = inlineMeasureItem_.inlineContentRectHeight;
    if (NearZero(estimatedHeight) || NearZero(estimatedHeight - mainSize)) {
        return;
    }
    double activeSize = barRegionSize * mainSize / estimatedHeight - scrollBar->GetOutBoundary();
    auto offsetScale = 0.0f;
    if (NearEqual(mainSize, estimatedHeight)) {
        offsetScale = 0.0;
    } else {
        offsetScale = (barRegionSize - activeSize) / (estimatedHeight - mainSize);
    }
    double lastMainOffset = std::max(
        static_cast<double>(std::max(inlineMeasureItem_.inlineLastOffsetY, contentRect_.GetY() - textRect_.GetY())),
        0.0);
    double activeMainOffset = std::min(offsetScale * lastMainOffset, barRegionSize - activeSize);
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
    const std::u16string& content, int32_t nakedCharPosition, bool needObscureText, bool showPasswordDirectly)
{
    if (!content.empty() && needObscureText) {
        auto text =
            TextFieldPattern::CreateObscuredText(static_cast<int32_t>(content.length()));
        if (nakedCharPosition >= 0 && nakedCharPosition < static_cast<int32_t>(content.length())) {
            if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE) || !showPasswordDirectly) {
                text[nakedCharPosition] = content[nakedCharPosition];
            }
        }
        return text;
    }
    return content;
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
    if (PipelineContext::GetCurrentContextSafelyWithCheck() &&
        // for normal app add version protection, enable keyboard as default start from API 10 or higher
        PipelineContext::GetCurrentContextSafelyWithCheck()->GetMinPlatformVersion() > KEYBOARD_DEFAULT_API) {
        needToRequestKeyboardOnFocus_ = true;
    }
    contentController_ = MakeRefPtr<ContentController>(WeakClaim(this));
    selectController_ = MakeRefPtr<TextSelectController>(WeakClaim(this));
    selectController_->InitContentController(contentController_);
    magnifierController_ = MakeRefPtr<MagnifierController>(WeakClaim(this));
    selectOverlay_ = MakeRefPtr<TextFieldSelectOverlay>(WeakClaim(this));
    if (SystemProperties::GetDebugEnabled()) {
        twinklingInterval_ = 3000; // 3000 : for AtuoUITest
    }
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
    RemoveTextFieldInfo();
}

void TextFieldPattern::CheckAndUpdateRecordBeforeOperation()
{
    if (operationRecords_.size() == 0 ||
        operationRecords_.back().caretPosition != selectController_->GetCaretIndex()) {
        // record the state before the operation
        // or caret position change
        UpdateEditingValueToRecord();
    }
}

void TextFieldPattern::BeforeCreateLayoutWrapper()
{
    while (!inputOperations_.empty()) {
        auto operation = inputOperations_.front();
        inputOperations_.pop();
        CheckAndUpdateRecordBeforeOperation();
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
                SetPreviewTextOperation(previewTextOperation_.front());
                previewTextOperation_.pop();
                break;
            case InputOperation::SET_PREVIEW_FINISH:
                FinishTextPreviewOperation();
                break;
        }
    }
    selectOverlay_->MarkOverlayDirty();
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
        do {
            if (!dragNode_) {
                break;
            }
            auto dragNodePattern = AceType::DynamicCast<TextDragPattern>(dragNode_->GetPattern());
            if (!dragNodePattern) {
                break;
            }
            dragNodePattern->UpdateParagraph(paragraph_);
        } while (false);
    }
    auto textRect = textFieldLayoutAlgorithm->GetTextRect();
    auto isSameSizeMouseMenu = NearEqual(paragraphWidth, paragraphWidth_) &&
                                    NearEqual(textRect.GetSize(), textRect_.GetSize()) && IsUsingMouse();
    needToRefreshSelectOverlay_ = needToRefreshSelectOverlay_ && !isSameSizeMouseMenu;
    paragraphWidth_ = paragraphWidth;
    HandleContentSizeChange(textRect);
    textRect_ = textRect;

    if (textFieldContentModifier_) {
        textFieldContentModifier_->ContentChange();
    }

    if (textFieldOverlayModifier_) {
        textFieldOverlayModifier_->ContentChange();
    }

    auto oldParentGlobalOffset = parentGlobalOffset_;
    parentGlobalOffset_ = GetPaintRectGlobalOffset();
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
    ProcessOverlayAfterLayout(oldParentGlobalOffset);
    if (inlineSelectAllFlag_ && (requestFocusReason_ != RequestFocusReason::DRAG_SELECT)) {
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
        ScheduleDisappearDelayTask();
    }
    SetAccessibilityClearAction();
    SetAccessibilityPasswordIconAction();
    SetAccessibilityUnitAction();
    if (needSelect_) {
        UpdateSelectionAndHandleVisibility();
        needSelect_ = false;
    }
    releaseInDrop_ = false;
    return true;
}

void TextFieldPattern::UpdateSelectionAndHandleVisibility()
{
    TextFieldRequestFocus(RequestFocusReason::DRAG_SELECT);
    auto start = dragTextStart_;
    auto end = dragTextEnd_;
    if (isMouseOrTouchPad(sourceTool_) && releaseInDrop_) {
        start = selectController_->GetCaretIndex()
        - contentController_->GetInsertValue().length();
        end = selectController_->GetCaretIndex();
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "UpdateSelectionAndHandleVisibility range=[%{public}d--%{public}d]",
        start, end);
    UpdateSelection(start, end);
    showSelect_ = true;

    if (!isMouseOrTouchPad(sourceTool_)) {
        ProcessOverlay({ .menuIsShow = false });
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::SetAccessibilityPasswordIconAction()
{
    CHECK_NULL_VOID(IsShowPasswordIcon());
    auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea_);
    CHECK_NULL_VOID(passwordArea);
    auto node = passwordArea->GetFrameNode();
    CHECK_NULL_VOID(node);
    auto textAccessibilityProperty = node->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(textAccessibilityProperty);
    textAccessibilityProperty->SetAccessibilityLevel("yes");
    textAccessibilityProperty->SetAccessibilityText(GetPasswordIconPromptInformation(passwordArea->IsObscured()));
}

void TextFieldPattern::SetAccessibilityClearAction()
{
    CHECK_NULL_VOID(IsShowCancelButtonMode());
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
    CHECK_NULL_VOID(cleanNodeResponseArea);
    auto stackNode = cleanNodeResponseArea->GetFrameNode();
    CHECK_NULL_VOID(stackNode);
    auto textAccessibilityProperty = stackNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(textAccessibilityProperty);
    textAccessibilityProperty->SetAccessibilityLevel("yes");
    auto layoutProperty = GetHost()->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cleanNodeStyle = layoutProperty->GetCleanNodeStyleValue(CleanNodeStyle::INPUT);
    auto hasContent = cleanNodeStyle == CleanNodeStyle::CONSTANT ||
                        (cleanNodeStyle == CleanNodeStyle::INPUT && HasText());
    textAccessibilityProperty->SetAccessibilityText(hasContent ? GetCancelImageText() : "");
}

void TextFieldPattern::SetAccessibilityUnitAction()
{
    if (!unitNode_ || !responseArea_) {
        return;
    }
    auto unitNode = AceType::DynamicCast<FrameNode>(unitNode_);
    CHECK_NULL_VOID(unitNode);
    auto unitAccessibilityProperty = unitNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(unitAccessibilityProperty);
    unitAccessibilityProperty->SetAccessibilityLevel("yes");
}

void TextFieldPattern::HandleContentSizeChange(const RectF& textRect)
{
    if (textRect_ == textRect) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!NearEqual(textRect.Height(), textRect_.Height())) {
        PlayScrollBarAppearAnimation();
        ScheduleDisappearDelayTask();
    }
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->GetOnContentSizeChange()) {
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto weak = WeakClaim(eventHub.GetRawPtr());
        pipeline->AddAfterLayoutTask([textRect, weak]() {
            auto eventHub = weak.Upgrade();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnContentSizeChange(std::max(0.0f, textRect.Width()), textRect.Height());
        });
    }
}

void TextFieldPattern::ProcessOverlayAfterLayout(const OffsetF& prevOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weak = WeakClaim(this), prevOffset]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->parentGlobalOffset_ = pattern->GetPaintRectGlobalOffset();
        if (pattern->SelectOverlayIsOn()) {
            if (pattern->IsSelected()) {
                pattern->selectOverlay_->UpdateAllHandlesOffset();
            } else {
                pattern->selectOverlay_->UpdateSecondHandleOffset();
            }
        }
        if (pattern->processOverlayDelayTask_) {
            if (pattern->HasFocus()) {
                pattern->processOverlayDelayTask_();
            }
            pattern->processOverlayDelayTask_ = nullptr;
        } else if (prevOffset != pattern->parentGlobalOffset_) {
            pattern->HandleParentGlobalOffsetChange();
        } else if (pattern->needToRefreshSelectOverlay_ && pattern->SelectOverlayIsOn()) {
            if (pattern->IsSelected()) {
                pattern->StopTwinkling();
            } else {
                pattern->StartTwinkling();
            }
            pattern->ProcessOverlay({ .menuIsShow = pattern->selectOverlay_->IsCurrentMenuVisibile() });
        }
        pattern->needToRefreshSelectOverlay_ = false;
    });
}

bool TextFieldPattern::HasFocus() const
{
    auto focusHub = GetFocusHub();

    CHECK_NULL_RETURN(focusHub, false);
    return focusHub->IsCurrentFocus();
}

void TextFieldPattern::UpdateCaretInfoToController(bool forceUpdate)
{
    CHECK_NULL_VOID(HasFocus());
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    PreviewRange miscTextConfigRange {
        miscTextConfig.value().range.start,
        miscTextConfig.value().range.end
    };
    if (!forceUpdate && lastCursorRange_ == miscTextConfigRange &&
        lastTextValue_ == contentController_->GetTextUtf16Value() &&
        NearEqual(miscTextConfig.value().cursorInfo.top, lastCursorTop_)) {
        return;
    }
    lastCursorRange_.Set(miscTextConfig.value().range.start, miscTextConfig.value().range.end);
    lastTextValue_ = contentController_->GetTextUtf16Value();
    lastCursorTop_ = miscTextConfig.value().cursorInfo.top;
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    MiscServices::InputMethodController::GetInstance()->OnCursorUpdate(cursorInfo);
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        contentController_->GetTextUtf16Value(), selectController_->GetStartIndex(),
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
        value.hint = UtfUtils::Str16ToStr8(GetPlaceHolder());
        value.selection.Update(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        connection_->SetEditingState(value, GetInstanceId());
    }
#endif
}

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
    CHECK_NULL_VOID(paragraph_);
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

bool TextFieldPattern::CheckSelectAreaVisible()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto pipeline = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, false);
    auto keyboardInset = pipeline->GetSafeAreaManager()->GetKeyboardInset();
    auto selectArea = selectOverlay_->GetSelectArea();
    auto globalOffset = GetPaintRectGlobalOffset();
    auto globalContentRect = contentRect_;
    globalContentRect.SetOffset(globalContentRect.GetOffset() + globalOffset);
    if (selectArea.Bottom() < 0) {
        return false;
    } else if (!globalContentRect.IsInnerIntersectWith(selectArea)) {
        return false;
    } else if (keyboardInset.Length() > 0 && selectArea.Top() >= keyboardInset.start) {
        return false;
    }
    return true;
}

void TextFieldPattern::OnScrollEndCallback()
{
    ScheduleDisappearDelayTask();
    if (!IsUsingMouse() && SelectOverlayIsOn() && isTextSelectionMenuShow_ && CheckSelectAreaVisible()) {
        selectOverlay_->ShowMenu();
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
    auto pipeline = host->GetContext();
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
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
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
    ACE_LAYOUT_SCOPED_TRACE("[TextField:%d] on focus", host->GetId());
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    context->AddOnAreaChangeNode(host->GetId());
    auto globalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
    UpdateTextFieldManager(Offset(globalOffset.GetX(), globalOffset.GetY()), frameRect_.Height());
    SetNeedToRequestKeyboardInner(!isLongPress_ && (dragRecipientStatus_ != DragStatus::DRAGGING) &&
        (dragStatus_ != DragStatus::DRAGGING), RequestKeyboardInnerChangeReason::FOCUS);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isSelectAll = layoutProperty->GetSelectAllValueValue(false);
    if (isSelectAll && !contentController_->IsEmpty()) {
        needSelectAll_ = true;
    }
    ProcessFocusStyle();
    ProcessAutoFillOnFocus();
    RequestKeyboardByFocusSwitch();
    ResetFirstClickAfterGetFocus();
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ?
        PROPERTY_UPDATE_MEASURE_SELF : PROPERTY_UPDATE_MEASURE);
}

void TextFieldPattern::ProcessAutoFillOnFocus()
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        return;
    }

    auto isIgnoreFocusReason =
        requestFocusReason_ == RequestFocusReason::DRAG_ENTER || requestFocusReason_ == RequestFocusReason::DRAG_MOVE ||
        requestFocusReason_ == RequestFocusReason::DRAG_END || requestFocusReason_ == RequestFocusReason::AUTO_FILL ||
        requestFocusReason_ == RequestFocusReason::CLICK || requestFocusReason_ == RequestFocusReason::MOUSE;
    if (needToRequestKeyboardOnFocus_ && !isIgnoreFocusReason && !IsModalCovered() && IsTriggerAutoFillPassword()) {
        DoProcessAutoFill();
    }
}

void TextFieldPattern::ProcessFocusStyle()
{
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
        auto textFieldTheme = GetTheme();
        CHECK_NULL_VOID(textFieldTheme);
        underlineColor_ = userUnderlineColor_.typing.value_or(textFieldTheme->GetUnderlineTypingColor());
        underlineWidth_ = TYPING_UNDERLINE_WIDTH;
    }
}

void TextFieldPattern::HandleSetSelection(int32_t start, int32_t end, bool showHandle)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleSetSelection %{public}d, %{public}d, showOverlay:%{public}d", start, end,
        showHandle);
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
        default: {
            TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "Unsupported operation of CursorMove for text field");
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
            TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "Unsupported select operation for text field");
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
        if (IsShowError()) {
            underlineColor = userUnderlineColor_.error.value_or(theme->GetErrorUnderlineColor());
        }
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
        layoutProperty->ResetTextOverflowMaxLines();
        inlineSelectAllFlag_ = false;
        inlineFocusState_ = false;
        RestorePreInlineStates();
    }
}

void TextFieldPattern::ProcBorderAndUnderlineInBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    bool isShowError = IsShowError();
    bool isUnderlineMode = IsUnderlineMode();
    if (!isShowError && isUnderlineMode) {
        underlineColor_ = userUnderlineColor_.normal.value_or(textFieldTheme->GetUnderlineColor());
        underlineWidth_ = UNDERLINE_WIDTH;
    }
    if (showCountBorderStyle_) {
        showCountBorderStyle_ = false;
        if (isShowError) {
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
    if (!isShowError || (isShowError && !isUnderlineMode && !IsInPasswordMode())) {
        HandleCounterBorder();
    }
}

void TextFieldPattern::SetNeedToRequestKeyboardInner(bool needToRequestKeyboardInner,
    RequestKeyboardInnerChangeReason reason)
{
    if (needToRequestKeyboardInner_ != needToRequestKeyboardInner) {
        TAG_LOGI(ACE_TEXT_FIELD, "Set needToRequestKeyboardInner_ to %{public}d : reason %{public}d",
            needToRequestKeyboardInner, static_cast<int32_t>(reason));
    }
    needToRequestKeyboardInner_ = needToRequestKeyboardInner;
}

void TextFieldPattern::HandleBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextField %{public}d OnBlur", host->GetId());
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    firstClickResetTask_.Cancel();
    firstClickAfterLosingFocus_ = true;
    UpdateBlurReason();
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->ClearOnFocusTextField(host->GetId());
    }

    shiftFlag_ = false;
    ProcBorderAndUnderlineInBlurEvent();
    ProcNormalInlineStateInBlurEvent();
    ModifyInnerStateInBlurEvent();
    if (magnifierController_) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
    CloseSelectOverlay(!isKeyboardClosedByUser_ && blurReason_ == BlurReason::FOCUS_SWITCH);
    StopTwinkling();
    if (((customKeyboard_ || customKeyboardBuilder_) && isCustomKeyboardAttached_)) {
        CloseKeyboard(true);
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "textfield %{public}d on blur, close custom keyboard", host->GetId());
    }
    HandleCrossPlatformInBlurEvent();
    selectController_->UpdateCaretIndex(selectController_->GetCaretIndex());
    NotifyOnEditChanged(false);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->HasOnAreaChanged()) {
        context->RemoveOnAreaChangeNode(host->GetId());
    }
    SetNeedToRequestKeyboardInner(false, RequestKeyboardInnerChangeReason::BLUR);
    if (isOnHover_) {
        RestoreDefaultMouseState();
    }
    ReportEvent();
    ScheduleDisappearDelayTask();
    requestFocusReason_ = RequestFocusReason::UNKNOWN;
}

void TextFieldPattern::ModifyInnerStateInBlurEvent()
{
    isLongPress_ = false;
    isMoveCaretAnywhere_ = false;
    isFocusedBeforeClick_ = false;
}

void TextFieldPattern::HandleCrossPlatformInBlurEvent()
{
#ifndef OHOS_PLATFORM
    if (HasConnection()) {
        CloseKeyboard(true);
    }
#endif
}

bool TextFieldPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.code == KeyCode::KEY_TAB && !contentController_->IsEmpty()) {
        if (isFocusedBeforeClick_) {
            isFocusedBeforeClick_ = false;
            HandleOnSelectAll(true);
        } else {
            CloseSelectOverlay(true);
        }
    }
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (event.code == KeyCode::KEY_TAB && HasFocus() && !needToRequestKeyboardOnFocus_ && needToRequestKeyboardInner_ &&
        textFieldManager->GetImeShow()) {
        RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::ON_KEY_EVENT);
    }
    return TextInputClient::HandleKeyEvent(event);
}

bool TextFieldPattern::HandleOnEscape()
{
    if (SelectOverlayIsOn()) {
        CloseSelectOverlay(true);
        if (!IsSelected() && HasFocus()) {
            StartTwinkling();
        }
        return true;
    }
    if (GetIsPreviewText()) {
        ResetPreviewTextState();
        return true;
    }
    if (HasFocus()) {
        StopTwinkling();
        TextFieldLostFocusToViewRoot();
    }
    return true;
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
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnUndoAction");
    if (operationRecords_.size() == 1) {
        FireEventHubOnChange(u"");
        return;
    }
    auto value = operationRecords_.back();
    operationRecords_.pop_back();
    if (redoOperationRecords_.size() >= RECORD_MAX_LENGTH) {
        redoOperationRecords_.erase(redoOperationRecords_.begin());
    }
    if (operationRecords_.size() >= 1) {
        redoOperationRecords_.push_back(value); // the initial status is not recorded
    }
    auto textEditingValue = operationRecords_.back(); // each record includes text and caret
    contentController_->SetTextValue(textEditingValue.text);
    if (value.beforeCaretPosition != -1) {
        selectController_->MoveCaretToContentRect(
            value.beforeCaretPosition, TextAffinity::DOWNSTREAM);
    } else {
        selectController_->MoveCaretToContentRect(
            textEditingValue.caretPosition, TextAffinity::DOWNSTREAM);
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleOnRedoAction()
{
    if (redoOperationRecords_.empty()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnRedoAction");
    auto textEditingValue = redoOperationRecords_.back();
    redoOperationRecords_.pop_back();
    operationRecords_.push_back(textEditingValue);
    contentController_->SetTextValue(textEditingValue.text);
    selectController_->UpdateCaretIndex(textEditingValue.caretPosition);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

bool TextFieldPattern::CanUndo()
{
    return operationRecords_.size() > 1;
}

bool TextFieldPattern::HasOperationRecords()
{
    return !operationRecords_.empty();
}

bool TextFieldPattern::CanRedo()
{
    return !redoOperationRecords_.empty();
}

void TextFieldPattern::HandleOnSelectAll(bool isKeyEvent, bool inlineStyle, bool showMenu)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnSelectAll");
    auto textSize = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    if (textSize == 0) {
        return; // no content
    }
    if (inlineStyle) {
        auto dotPos = contentController_->GetTextUtf16Value().rfind(u'.');
        if (dotPos != std::string::npos && static_cast<int32_t>(dotPos) < textSize - FIND_TEXT_ZERO_INDEX) {
            textSize = static_cast<int32_t>(dotPos);
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
    parentGlobalOffset_ = GetPaintRectGlobalOffset();
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    selectController_->MoveSecondHandleToContentRect(textSize);
    StopTwinkling();
    showSelect_ = true;
    if (isKeyEvent || inlineSelectAllFlag_ || IsUsingMouse()) {
        CloseSelectOverlay(true);
        if (inlineSelectAllFlag_ && !isKeyEvent && !IsUsingMouse()) {
            return;
        }
        if (IsSelected()) {
            selectOverlay_->SetSelectionHoldCallback();
        }
        return;
    }
    selectOverlay_->ProcessSelectAllOverlay({ .menuIsShow = showMenu, .animation = true });
}

void TextFieldPattern::HandleOnCopy(bool isUsingExternalKeyboard)
{
    CHECK_NULL_VOID(clipboard_);
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Local) == CopyOptions::None) {
        return;
    }
    if (!IsSelected() || IsInPasswordMode()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On copy, text selector %{public}s", selectController_->ToString().c_str());
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    GetEmojiSubStringRange(start, end);
    auto value = contentController_->GetSelectedValue(start, end);
    if (value.empty()) {
        return;
    }
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Local) != CopyOptions::None) {
        clipboard_->SetData(UtfUtils::Str16ToStr8(value), layoutProperty->GetCopyOptionsValue(CopyOptions::Local));
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
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, false);
    return !theme->IsTextFieldShowHandle();
}

std::string TextFieldPattern::GetCancelButton()
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    return theme->GetCancelButton();
}

std::string TextFieldPattern::GetCancelImageText()
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    return theme->GetCancelImageText();
}

std::string TextFieldPattern::GetPasswordIconPromptInformation(bool show)
{
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, "");
    return show ? theme->GetShowPasswordPromptInformation() : theme->GetHiddenPasswordPromptInformation();
}

void TextFieldPattern::UpdateShowCountBorderStyle()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMaxLength()) {
        auto textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
        auto maxLength = static_cast<int32_t>(layoutProperty->GetMaxLengthValue(Infinity<uint32_t>()));
        // if equal, the showCountBorderStyle_ is not changed
        if (textLength != maxLength) {
            showCountBorderStyle_ = textLength > maxLength;
        }
    }
}

void TextFieldPattern::HandleOnPaste()
{
    auto pasteCallback = [weak = WeakClaim(this)](const std::string& data) {
        if (data.empty()) {
            TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "HandleOnPaste fail, because data is empty");
            return;
        }
        auto textfield = weak.Upgrade();
        CHECK_NULL_VOID(textfield);
        auto host = textfield->GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        TextCommonEvent event;
        const std::u16string pasteData = UtfUtils::Str8ToStr16(data);
        eventHub->FireOnPasteWithEvent(pasteData, event);
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
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnPaste len:%{public}d", static_cast<int32_t>(pasteData.length()));
        auto originLength = static_cast<int32_t>(textfield->contentController_->GetTextUtf16Value().length());
        textfield->contentController_->ReplaceSelectedValue(start, end, pasteData);
        auto caretMoveLength =
            static_cast<int32_t>(textfield->contentController_->GetTextUtf16Value().length()) - originLength;
        auto newCaretPosition = std::clamp(std::max(start, end) + caretMoveLength, 0,
            static_cast<int32_t>(textfield->contentController_->GetTextUtf16Value().length()));
        textfield->ResetObscureTickCountDown();
        textfield->selectController_->UpdateCaretIndex(newCaretPosition);
        textfield->UpdateEditingValueToRecord(std::max(start, end));
        if (layoutProperty->HasMaxLength()) {
            textfield->CalcCounterAfterFilterInsertValue(originLength - (end - start), pasteData,
                static_cast<int32_t>(layoutProperty->GetMaxLengthValue(Infinity<uint32_t>())));
        }
        textfield->CloseSelectOverlay(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
        textfield->StartTwinkling();
        textfield->TriggerAvoidOnCaretChange();
    };
    CHECK_NULL_VOID(clipboard_);
    clipboard_->GetData(pasteCallback);
}

bool TextFieldPattern::IsShowSearch()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, false);
    return textFieldTheme->GetIsSupportSearch();
}

void TextFieldPattern::HandleOnCameraInput()
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextFieldPattern::HandleOnCameraInput");
#if defined(ENABLE_STANDARD_INPUT)
    if (textChangeListener_ == nullptr) {
        textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (!inputMethod) {
        TAG_LOGE(AceLogTag::ACE_TEXT_FIELD, "HandleOnCameraInput, inputMethod is null");
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
        auto ret = inputMethod->Attach(textChangeListener_, false, textConfig);
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
    CloseSelectOverlay(true);
    StartTwinkling();
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
    if (!dataChanged) {
        return;
    }
    data = result;
}

void TextFieldPattern::HandleOnCut()
{
#if !defined(PREVIEW)
    CHECK_NULL_VOID(clipboard_);
#endif
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Local) == CopyOptions::None) {
        return;
    }
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    GetEmojiSubStringRange(start, end);
    SwapIfLarger(start, end);
    if (!IsSelected() || IsInPasswordMode()) {
        return;
    }
    UpdateEditingValueToRecord();
    auto selectedText = contentController_->GetSelectedValue(start, end);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Local) != CopyOptions::None) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Cut value is %{private}s", UtfUtils::Str16ToStr8(selectedText).c_str());
        clipboard_->SetData(UtfUtils::Str16ToStr8(selectedText),
            layoutProperty->GetCopyOptionsValue(CopyOptions::Local));
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
    FireEventHubOnChange(contentController_->GetTextUtf16Value());
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
    startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    if (startIndex != selectController_->GetStartIndex() || endIndex != selectController_->GetEndIndex()) {
        selectController_->UpdateHandleIndex(startIndex, endIndex);
    }
}

void TextFieldPattern::FireEventHubOnChange(const std::u16string& text)
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
    PreviewText previewText {.offset = -1, .value = u""};
    if (GetIsPreviewText()) {
        previewText.offset = GetPreviewTextStart();
        previewText.value = GetPreviewTextValue();
    }
    eventHub->FireOnChange(text, previewText);
}

void TextFieldPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    CHECK_NULL_VOID(!IsDragging());
    CHECK_NULL_VOID(!info.GetTouches().empty());
    if (selectOverlay_->IsTouchAtHandle(info)) {
        return;
    }
    auto touchInfo = GetAcceptedTouchLocationInfo(info);
    CHECK_NULL_VOID(touchInfo);
    DoGestureSelection(info);
    auto touchType = touchInfo->GetTouchType();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(touchInfo->GetLocalLocation());
    } else if (touchType == TouchType::UP) {
        OnCaretMoveDone(info);
        RequestKeyboardAfterLongPress();
        isLongPress_ = false;
        isMoveCaretAnywhere_ = false;
        HandleTouchUp();
    } else if (touchType == TouchType::MOVE) {
        if (isMoveCaretAnywhere_) {
            // edit + longpress + move, show caret anywhere on fonts.
            selectController_->MoveCaretAnywhere(info.GetTouches().front().GetLocalLocation());
            ShowCaretAndStopTwinkling();
            selectOverlay_->HideMenu();
            selectOverlay_->SetIsSingleHandle(false);
            return;
        }
        if (SelectOverlayIsOn() && !moveCaretState_.isTouchCaret) {
            return;
        }
        if (!IsUsingMouse() && HasFocus()) {
            HandleTouchMove(touchInfo.value());
        }
    } else if (touchType == TouchType::CANCEL) {
        StopContentScroll();
        if (magnifierController_ && magnifierController_->GetMagnifierNodeExist()) {
            magnifierController_->RemoveMagnifierFrameNode();
        }
        ResetTouchAndMoveCaretState();
    }
}

void TextFieldPattern::HandleTouchDown(const Offset& offset)
{
    moveCaretState_.touchDownOffset = offset;
    if (HasStateStyle(UI_STATE_PRESSED)) {
        return;
    }

    if (enableTouchAndHoverEffect_ && !isMousePressed_) {
        auto lastCaretRect = selectController_->GetCaretRect();
        moveCaretState_.isTouchCaret = HasFocus() && !IsSelected() && RepeatClickCaret(offset, lastCaretRect);
        isTouchPreviewText_ = GetTouchInnerPreviewText(offset);
    }
}

void TextFieldPattern::HandleTouchUp()
{
    if (GetIsPreviewText() && isTouchPreviewText_) {
        StartTwinkling();
    }
    ResetTouchAndMoveCaretState();
    if (isMousePressed_) {
        isMousePressed_ = false;
    }
    if (magnifierController_) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
    ScheduleDisappearDelayTask();
}

void TextFieldPattern::ResetTouchAndMoveCaretState()
{
    if (moveCaretState_.isTouchCaret) {
        moveCaretState_.isTouchCaret = false;
        CheckScrollable();
        StartTwinkling();
    }
    if (moveCaretState_.isMoveCaret) {
        moveCaretState_.isMoveCaret = false;
        StopContentScroll();
        if (HasFocus()) {
            StartTwinkling();
        } else {
            StopTwinkling();
        }
    }
    FloatingCaretLand();
}

void TextFieldPattern::HandleTouchMove(const TouchLocationInfo& info)
{
    if (moveCaretState_.isTouchCaret && !moveCaretState_.isMoveCaret) {
        auto offset = info.GetLocalLocation();
        auto moveDistance = (offset - moveCaretState_.touchDownOffset).GetDistance();
        moveCaretState_.isMoveCaret = GreatNotEqual(moveDistance, moveCaretState_.minDinstance.ConvertToPx());
        if (moveCaretState_.isMoveCaret) {
            moveCaretState_.touchFingerId = info.GetFingerId();
        }
    }
    if (SelectOverlayIsOn() && moveCaretState_.isMoveCaret) {
        CloseSelectOverlay(false);
    }
    if (moveCaretState_.isMoveCaret || (GetIsPreviewText() && isTouchPreviewText_)) {
        ShowCaretAndStopTwinkling();
        UpdateCaretByTouchMove(info);
    }
}

void TextFieldPattern::StartVibratorByIndexChange(int32_t currentIndex, int32_t preIndex)
{
    CHECK_NULL_VOID(isEnableHapticFeedback_ && (currentIndex != preIndex));
    VibratorUtils::StartVibraFeedback("slide");
}

void TextFieldPattern::UpdateCaretByTouchMove(const TouchLocationInfo& info)
{
    scrollable_ = false;
    SetScrollEnabled(scrollable_);
    // limit move when preview text is shown
    auto touchOffset = info.GetLocalLocation();
    int32_t preCaretIndex = selectController_->GetCaretIndex();
    if (GetIsPreviewText()) {
        TAG_LOGI(ACE_TEXT_FIELD, "UpdateCaretByTouchMove when has previewText");
        float offsetY = IsTextArea() ? GetTextRect().GetY() : contentRect_.GetY();
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
        if (moveCaretState_.isMoveCaret) {
            StartVibratorByIndexChange(selectController_->GetCaretIndex(), preCaretIndex);
        }
    } else {
        UpdateContentScroller(touchOffset);
        auto touchCaretX = std::clamp(
            touchOffset.GetX(), static_cast<double>(contentRect_.Left()), static_cast<double>(contentRect_.Right()));
        // 1/4 line height.
        auto yOffset = PreferredLineHeight() * 0.25f;
        auto touchCaretY = std::clamp(touchOffset.GetY(), static_cast<double>(contentRect_.Top()) + yOffset,
            static_cast<double>(contentRect_.Bottom()) - yOffset);
        selectController_->UpdateCaretInfoByOffset(
            !contentScroller_.isScrolling ? Offset(touchCaretX, touchCaretY) : touchOffset,
            !contentScroller_.isScrolling);
        if (magnifierController_ && HasText()) {
            auto floatCaretRectCenter = GetFloatingCaretRect().Center();
            magnifierController_->SetLocalOffset({ floatCaretRectCenter.GetX(), floatCaretRectCenter.GetY() });
        }
        StartVibratorByIndexChange(selectController_->GetCaretIndex(), preCaretIndex);
    }

    UpdateCaretInfoToController();
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
        auto paintProperty = pattern->GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        if (pattern->BetweenSelectedPosition(point)) {
            auto manager = pattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
            CHECK_NULL_VOID(manager);
            auto selectOverlayInfo = manager->GetSelectOverlayInfo();
            CHECK_NULL_VOID(selectOverlayInfo);
            auto textFieldTheme = pattern->GetTheme();
            CHECK_NULL_VOID(textFieldTheme);
            auto info = pattern->CreateRichEditorDragInfo(*selectOverlayInfo, *paintProperty, *textFieldTheme);
            pattern->dragNode_ = TextDragPattern::CreateDragNode(frameNode);
            auto textDragPattern = pattern->dragNode_->GetPattern<TextDragPattern>();
            if (textDragPattern) {
                textDragPattern->UpdateHandleAnimationInfo(info);
                auto option = pattern->GetHost()->GetDragPreviewOption();
                option.options.shadowPath = textDragPattern->GetBackgroundPath()->ConvertToSVGString();
                option.options.shadow = Shadow(RICH_DEFAULT_ELEVATION, {0.0, 0.0}, Color(RICH_DEFAULT_SHADOW_COLOR),
                    ShadowStyle::OuterFloatingSM);
                pattern->GetHost()->SetDragPreviewOptions(option);
            }
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetPixelMap(nullptr);
    };
    return callback;
}

TextDragInfo TextFieldPattern::CreateRichEditorDragInfo(const SelectOverlayInfo& selectOverlayInfo,
    const TextFieldPaintProperty& paintProperty, const TextFieldTheme& textFieldTheme) const
{
    auto handleColor = paintProperty.GetCursorColorValue(textFieldTheme.GetCursorColor());
    auto selectedBackgroundColor = textFieldTheme.GetSelectedColor();
    auto firstIndex = selectController_->GetFirstHandleIndex();
    auto secondIndex = selectController_->GetSecondHandleIndex();
    TextDragInfo info;
    if (firstIndex > secondIndex) {
        info.secondHandle = selectOverlayInfo.firstHandle.paintRect;
        info.firstHandle = selectOverlayInfo.secondHandle.paintRect;
    } else {
        info.firstHandle = selectOverlayInfo.firstHandle.paintRect;
        info.secondHandle = selectOverlayInfo.secondHandle.paintRect;
    }
    if ((textRect_.Width() > contentRect_.Width()) ||
        paintProperty.GetInputStyleValue(InputStyle::DEFAULT) == InputStyle::INLINE) {
        info.isInline = false;
    }
    info.selectedBackgroundColor = selectedBackgroundColor;
    info.handleColor = handleColor;
    return info;
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
        pattern->sourceTool_ = event ? event->GetSourceTool() : SourceTool::UNKNOWN;
        if (!gestureHub->GetIsTextDraggable()) {
            return itemInfo;
        }
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "%{public}d TextField OnDragStart, dragStatus_ is %{public}d, dragRecipientStatus_ is %{public}d",
            host->GetId(), static_cast<int32_t>(pattern->dragStatus_),
            static_cast<int32_t>(pattern->dragRecipientStatus_));
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, itemInfo);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
        pattern->CloseHandleAndSelect();
        pattern->CloseKeyboard(true);
#endif
        pattern->SetDragMovingScrollback();
        pattern->dragStatus_ = DragStatus::DRAGGING;
        auto pipeline = pattern->GetContext();
        CHECK_NULL_RETURN(pipeline, itemInfo);
        auto dragManager = pipeline->GetDragDropManager();
        CHECK_NULL_RETURN(dragManager, itemInfo);
        if (!pattern->IsNormalInlineState() && dragManager->IsDropAllowed(host)) {
            pattern->dragRecipientStatus_ = DragStatus::DRAGGING;
        }
        auto selectedStr = pattern->GetDragStyledText();
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

std::string TextFieldPattern::GetDragStyledText()
{
    showSelect_ = false;
    selectionMode_ = SelectionMode::SELECT;
    textFieldContentModifier_->ChangeDragStatus();
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    GetEmojiSubStringRange(start, end);
    dragTextStart_ = start;
    dragTextEnd_ = end;
    std::u16string beforeStr = contentController_->GetValueBeforeIndex(start);
    std::u16string selectedStr = contentController_->GetSelectedValue(start, end);
    dragValue_ = selectedStr;
    std::u16string afterStr = contentController_->GetValueAfterIndex(end);
    dragContents_ = { beforeStr, selectedStr, afterStr };
    return UtfUtils::Str16ToStr8(selectedStr);
}

std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)> TextFieldPattern::OnDragDrop()
{
    return [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->StopContentScroll();
        pattern->sourceTool_ = event ? event->GetSourceTool() : SourceTool::UNKNOWN;
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);

        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "%{public}d TextField OnDragDrop, dragStatus_ is %{public}d, dragRecipientStatus_ is %{public}d",
            host->GetId(), static_cast<int32_t>(pattern->dragStatus_),
            static_cast<int32_t>(pattern->dragRecipientStatus_));
        if (layoutProperty->GetIsDisabledValue(false) || pattern->IsNormalInlineState() || !pattern->HasFocus()) {
            event->SetResult(DragRet::DRAG_FAIL);
            return;
        }
        if (extraParams.empty()) {
            pattern->dragStatus_ = DragStatus::ON_DROP;
            pattern->textFieldContentModifier_->ChangeDragStatus();
            host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                         : PROPERTY_UPDATE_MEASURE);
            event->SetResult(DragRet::DRAG_FAIL);
            return;
        }
        bool isCopy = false;
        if (pattern->dragStatus_ == DragStatus::DRAGGING) {
            CHECK_NULL_VOID(event);
            auto gesturePressedCodes = event->GetPressedKeyCodes();
            if ((gesturePressedCodes.size() == 1) && ((gesturePressedCodes[0] == KeyCode::KEY_CTRL_LEFT) ||
                (gesturePressedCodes[0] == KeyCode::KEY_CTRL_RIGHT))) {
                isCopy = true;
            }
        }
        auto data = event->GetData();
        CHECK_NULL_VOID(data);
        std::u16string str;
        auto arr = UdmfClient::GetInstance()->GetSpanStringRecord(data);
        if (arr.size() > 0) {
            auto spanStr = SpanString::DecodeTlv(arr);
            str += spanStr->GetU16string();
        } else {
            auto records = UdmfClient::GetInstance()->GetPlainTextRecords(data);
            if (records.empty()) {
                std::string linkUrl;
                std::string linkTitle;
                UdmfClient::GetInstance()->GetLinkRecord(data, linkUrl, linkTitle);
                if (!linkTitle.empty()) {
                    str +=  UtfUtils::Str8ToStr16(linkTitle);
                } else if (!linkUrl.empty()) {
                    str +=  UtfUtils::Str8ToStr16(linkUrl);
                }
            }
            for (const auto& record : records) {
                str +=  UtfUtils::Str8ToStr16(record);
            }
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
            if (current < dragTextStart && !isCopy) {
                pattern->contentController_->erase(dragTextStart, dragTextEnd - dragTextStart);
                pattern->InsertValue(str);
            } else if (current > dragTextEnd && !isCopy) {
                pattern->contentController_->erase(dragTextStart, dragTextEnd - dragTextStart);
                pattern->selectController_->UpdateCaretIndex(current - (dragTextEnd - dragTextStart));
                pattern->InsertValue(str);
            } else if (isCopy) {
                pattern->InsertValue(str);
            }
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
            host->MarkDirtyNode(pattern->IsTextArea() ? PROPERTY_UPDATE_MEASURE : PROPERTY_UPDATE_MEASURE_SELF);
        }
        pattern->needSelect_ = isMouseOrTouchPad(pattern->sourceTool_);
        pattern->releaseInDrop_ = true;
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
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "%{public}d TextField onDragEnter, dragStatus_ is %{public}d, dragRecipientStatus_ is %{public}d",
            host->GetId(), static_cast<int32_t>(pattern->dragStatus_),
            static_cast<int32_t>(pattern->dragRecipientStatus_));

        auto pipeline = pattern->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto dragManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragManager);
        if (pattern->IsNormalInlineState() || !dragManager->IsDropAllowed(host)) {
            return;
        }
        pattern->SetDragMovingScrollback();
        pattern->dragRecipientStatus_ = DragStatus::DRAGGING;
        pattern->ResetPreviewTextState();
        auto focusHub = pattern->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        if (pattern->TextFieldRequestFocus(RequestFocusReason::DRAG_ENTER)) {
            pattern->StartTwinkling();
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
                "%{public}d TextField onDragEnter Request Focus Success", host->GetId());
        }
    };
    eventHub->SetOnDragEnter(std::move(onDragEnter));

    auto onDragMove = [weakPtr = WeakClaim(this)](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto pipeline = pattern->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto dragManager = pipeline->GetDragDropManager();
        CHECK_NULL_VOID(dragManager);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);

        if (pattern->IsNormalInlineState() || !dragManager->IsDropAllowed(host)) {
            return;
        }
        if (!pattern->HasFocus()) {
            auto focusHub = pattern->GetFocusHub();
            CHECK_NULL_VOID(focusHub);
            if (pattern->TextFieldRequestFocus(RequestFocusReason::DRAG_MOVE)) {
                pattern->StartTwinkling();
                TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
                    "%{public}d TextField onDragMove Request Focus Success", host->GetId());
            }
        }
        auto textPaintOffset = pattern->GetPaintRectGlobalOffset();
        pattern->UpdateContentScroller(
            Offset(event->GetX(), event->GetY()) - Offset(textPaintOffset.GetX(), textPaintOffset.GetY()));
    };
    eventHub->SetOnDragMove(std::move(onDragMove));

    auto onDragLeave = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "%{public}d TextField onDragLeave, dragStatus_ is %{public}d, dragRecipientStatus_ is %{public}d",
            host->GetId(), static_cast<int32_t>(pattern->dragStatus_),
            static_cast<int32_t>(pattern->dragRecipientStatus_));
        pattern->dragRecipientStatus_ = DragStatus::NONE;
        auto focusHub = pattern->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->LostFocus();
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "%{public}d TextField onDragLeave Lost Focus", host->GetId());
        pattern->StopTwinkling();
        pattern->PauseContentScroll();
    };
    eventHub->SetOnDragLeave(std::move(onDragLeave));

    auto onDragEnd = [weakPtr = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "%{public}d TextField onDragEnd, dragStatus_ is %{public}d, dragRecipientStatus_ is %{public}d",
            host->GetId(), static_cast<int32_t>(pattern->dragStatus_),
            static_cast<int32_t>(pattern->dragRecipientStatus_));
        pattern->StopContentScroll();
        ContainerScope scope(pattern->GetHostInstanceId());
        if (pattern->dragStatus_ == DragStatus::DRAGGING && !pattern->isDetachFromMainTree_) {
            pattern->dragStatus_ = DragStatus::NONE;
            pattern->MarkContentChange();
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
                pattern->TextFieldRequestFocus(RequestFocusReason::DRAG_END);
            }
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
        if (event != nullptr && event->GetResult() != DragRet::DRAG_SUCCESS) {
            pattern->needSelect_ = true;
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

void TextFieldPattern::HandleOnDragStatusCallback(
    const DragEventType& dragEventType, const RefPtr<NotifyDragEvent>& notifyDragEvent)
{
    ScrollablePattern::HandleOnDragStatusCallback(dragEventType, notifyDragEvent);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleOnDragStatusCallback dragEventType=%{public}d", dragEventType);
    if (dragEventType == DragEventType::DROP && dragRecipientStatus_ == DragStatus::DRAGGING) {
        StopContentScroll();
        StopTwinkling();
    }
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

bool TextFieldPattern::IsHandleDragging()
{
    CHECK_NULL_RETURN(selectOverlay_, false);
    return selectOverlay_->GetIsHandleDragging();
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
    CHECK_NULL_VOID(!IsHandleDragging());
    parentGlobalOffset_ = GetPaintRectGlobalOffset();
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(selectOverlay_);
    CHECK_NULL_VOID(multipleClickRecognizer_);
    if ((selectOverlay_->IsClickAtHandle(info) && !multipleClickRecognizer_->IsRunning()) || !focusHub->IsFocusable()) {
        return;
    }
    focusIndex_ = FocuseIndex::TEXT;
    auto firstGetFocus = false;
    if (!HasFocus()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d request focus currently", host->GetId());
        firstGetFocus = true;
        if (!focusHub->IsFocusOnTouch().value_or(true) || !TextFieldRequestFocus(RequestFocusReason::CLICK)) {
            CloseSelectOverlay(true);
            StopTwinkling();
            return;
        }
    }
    firstGetFocus = firstGetFocus || firstClickAfterLosingFocus_;
    firstClickAfterLosingFocus_ = false;
    if (!firstGetFocus && CheckMousePressedOverScrollBar(info)) {
        return;
    }
    selectOverlay_->SetLastSourceType(info.GetSourceDevice());
    selectOverlay_->SetUsingMouse(info.GetSourceDevice() == SourceType::MOUSE);
    lastClickTimeStamp_ = info.GetTimeStamp();
    multipleClickRecognizer_->Start(info);
    // register click event
    if (multipleClickRecognizer_->IsTripleClick()) {
        HandleTripleClickEvent(info);
    } else if (multipleClickRecognizer_->IsDoubleClick()) {
        HandleDoubleClickEvent(info);
    } else {
        HandleSingleClickEvent(info, firstGetFocus);
    }
    if (ResetObscureTickCountDown()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    isFocusedBeforeClick_ = false;
}

bool TextFieldPattern::CheckMousePressedOverScrollBar(GestureEvent& info)
{
    if (IsMouseOverScrollBar(&info) && hasMousePressed_) {
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(layoutProperty, false);
        if (layoutProperty->GetDisplayModeValue(DisplayMode::AUTO) != DisplayMode::OFF) {
            auto touchRegion = GetScrollBar()->GetTouchRegion();
            bool reverse = info.GetLocalLocation().GetY() < touchRegion.Top();
            ScrollPage(reverse);
            return true;
        }
    }
    return false;
}

bool TextFieldPattern::HandleBetweenSelectedPosition(const GestureEvent& info)
{
    if (!IsUsingMouse() && SelectOverlayIsOn() && BetweenSelectedPosition(info.GetGlobalLocation())) {
        CHECK_NULL_RETURN(selectOverlay_, false);
        // click selected area to switch show/hide state
        selectOverlay_->ToggleMenu();
        return true;
    }
    return false;
}

void TextFieldPattern::HandleSingleClickEvent(GestureEvent& info, bool firstGetFocus)
{
    if (mouseStatus_ != MouseStatus::NONE && IsNormalInlineState()) {
        return;
    }
    if (HandleBetweenSelectedPosition(info)) {
        selectOverlay_->SwitchToOverlayMode();
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    auto lastCaretIndex = selectController_->GetCaretIndex();
    if (mouseStatus_ != MouseStatus::MOVE) {
        UpdateCaretByClick(info.GetLocalLocation());
        UpdateCaretInfoToController();
    }
    StartTwinkling();
    SetIsSingleHandle(true);
    bool needCloseOverlay = true;
    bool isRepeatClickCaret =
        RepeatClickCaret(info.GetLocalLocation(), lastCaretIndex) && !firstGetFocus;
    bool isInlineSelectAllOrEmpty = inlineSelectAllFlag_ || contentController_->IsEmpty();
    auto clickBlank = contentController_->IsEmpty() || selectController_->IsTouchAtLineEnd(info.GetLocalLocation());
    auto closeHandleAtBlank =
        clickBlank && isRepeatClickCaret && SelectOverlayIsOn() && selectOverlay_->IsSingleHandle();
    do {
        if (info.GetSourceDevice() == SourceType::MOUSE || (!isRepeatClickCaret && isInlineSelectAllOrEmpty) ||
            IsContentRectNonPositive() || closeHandleAtBlank) {
            break;
        }
        if (isRepeatClickCaret) {
            if (IsAccessibilityClick()) {
                break;
            }
            ProcessOverlay({ .animation = true });
            needCloseOverlay = false;
        } else if (needSelectAll_) {
            HandleOnSelectAll(false);
        }
    } while (false);
    if (needCloseOverlay || GetIsPreviewText()) {
        CloseSelectOverlay(true);
        StartTwinkling();
    }
    DoProcessAutoFill();
    // emulate clicking bottom of the textField
    UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
    TriggerAvoidOnCaretChange();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::DoProcessAutoFill()
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "DoProcessAutoFill");
    if (!IsNeedProcessAutoFill()) {
        if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SINGLE_CLICK)) {
            NotifyOnEditChanged(true);
        }
        return;
    }
    bool isPopup = false;
    auto isSuccess = ProcessAutoFill(isPopup);
    if (!isPopup && isSuccess) {
        SetNeedToRequestKeyboardInner(false, RequestKeyboardInnerChangeReason::AUTOFILL_PROCESS);
    } else if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SINGLE_CLICK)) {
        NotifyOnEditChanged(true);
    }
}

bool TextFieldPattern::IsAutoFillPasswordType(const AceAutoFillType& autoFillType)
{
    return (autoFillType == AceAutoFillType::ACE_USER_NAME || autoFillType == AceAutoFillType::ACE_PASSWORD ||
            autoFillType == AceAutoFillType::ACE_NEW_PASSWORD);
}

HintToTypeWrap TextFieldPattern::GetHintType()
{
    HintToTypeWrap hintToTypeWrap;
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, hintToTypeWrap);
    auto onePlaceHolder = UtfUtils::Str16ToStr8(GetPlaceHolder());
    if (onePlaceHolder.empty()) {
        return hintToTypeWrap;
    }
    return container->PlaceHolderToType(onePlaceHolder);
}

bool TextFieldPattern::CheckAutoFillType(const AceAutoFillType& autoFillType, bool isFromKeyBoard)
{
    if (isFromKeyBoard) {
        return true;
    }
    
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto isTriggerPassword = IsTriggerAutoFillPassword();
    if (autoFillType == AceAutoFillType::ACE_UNSPECIFIED && !isTriggerPassword) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "CheckAutoFillType :autoFillType is ACE_UNSPECIFIED.");
        return false;
    } else if (isTriggerPassword) {
        auto tempAutoFillType = IsAutoFillUserName(autoFillType) ? AceAutoFillType::ACE_USER_NAME : autoFillType;
        if (!container->IsNeedToCreatePopupWindow(tempAutoFillType)) {
            return GetAutoFillTriggeredStateByType(autoFillType);
        }
    }
    return true;
}

bool TextFieldPattern::GetAutoFillTriggeredStateByType(const AceAutoFillType& autoFillType)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    CHECK_NULL_RETURN(autoFillContainerNode, false);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    CHECK_NULL_RETURN(stateHolder, false);
    if (IsAutoFillUserName(autoFillType) || autoFillType == AceAutoFillType::ACE_PASSWORD) {
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
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    CHECK_NULL_VOID(autoFillContainerNode);
    auto stateHolder = autoFillContainerNode->GetPattern<AutoFillTriggerStateHolder>();
    CHECK_NULL_VOID(stateHolder);
    if (IsAutoFillUserName(autoFillType) || autoFillType == AceAutoFillType::ACE_PASSWORD) {
        stateHolder->SetAutoFillPasswordTriggered(true);
    } else if (autoFillType == AceAutoFillType::ACE_NEW_PASSWORD) {
        stateHolder->SetAutoFillNewPasswordTriggered(true);
    }
}

AceAutoFillType TextFieldPattern::GetAutoFillType(bool isNeedToHitType)
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
        return aceInputType;
    }
    if (isNeedToHitType && !IsTriggerAutoFillPassword()) {
        auto hintToTypeWrap = GetHintType();
        return hintToTypeWrap.autoFillType;
    }
    return AceAutoFillType::ACE_UNSPECIFIED;
}

HintToTypeWrap TextFieldPattern::GetAutoFillTypeAndMetaData(bool isNeedToHitType)
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    HintToTypeWrap hintToTypeWrap;
    CHECK_NULL_RETURN(layoutProperty, hintToTypeWrap);
    auto aceContentType =
        TextContentTypeToAceAutoFillType(layoutProperty->GetTextContentTypeValue(TextContentType::UNSPECIFIED));
    auto aceInputType = ConvertToAceAutoFillType(layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
    if (aceContentType != AceAutoFillType::ACE_UNSPECIFIED) {
        hintToTypeWrap.autoFillType = aceContentType;
        return hintToTypeWrap;
    }
    if (aceInputType != AceAutoFillType::ACE_UNSPECIFIED) {
        hintToTypeWrap.autoFillType = aceInputType;
        return hintToTypeWrap;
    }
    if (isNeedToHitType && !IsTriggerAutoFillPassword()) {
        hintToTypeWrap = GetHintType();
        return hintToTypeWrap;
    }
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("type", TextInputTypeToString().c_str());
    hintToTypeWrap.metadata = jsonValue->ToString();
    return hintToTypeWrap;
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
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "don't need to auto fill.");
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto autoFillType = GetAutoFillType();
    auto container = Container::Current();
    if (container == nullptr) {
        TAG_LOGW(AceLogTag::ACE_AUTO_FILL, "Get current container is nullptr.");
        return false;
    }
    if (IsTriggerAutoFillPassword() && autoFillType == AceAutoFillType::ACE_UNSPECIFIED) {
        autoFillType = AceAutoFillType::ACE_USER_NAME;
    }
    auto onUIExtNodeDestroy = [weak = WeakPtr<FrameNode>(host)]() {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "onUIExtNodeDestroy called.");
        auto textFieldNode = weak.Upgrade();
        CHECK_NULL_VOID(textFieldNode);
        auto pageNode = textFieldNode->GetPageNode();
        CHECK_NULL_VOID(pageNode);
        auto pagePattern = pageNode->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->SetIsModalCovered(false);
    };
    auto onUIExtNodeBindingCompleted = [weak = WeakPtr<FrameNode>(host)]() {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "onUIExtNodeBindingCompleted called.");
        auto textFieldNode = weak.Upgrade();
        CHECK_NULL_VOID(textFieldNode);
        auto pageNode = textFieldNode->GetPageNode();
        CHECK_NULL_VOID(pageNode);
        auto pagePattern = pageNode->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pagePattern);
        pagePattern->SetIsModalCovered(true);
    };

    auto resultCode = container->RequestAutoFill(host, autoFillType, isNewPassWord, isPopup, autoFillSessionId_, true,
        onUIExtNodeDestroy, onUIExtNodeBindingCompleted);
    if (resultCode != AceAutoFillError::ACE_AUTO_FILL_PREVIOUS_REQUEST_NOT_FINISHED) {
        SetAutoFillTriggeredStateByType(autoFillType);
        SetFillRequestFinish(false);
    }
    return resultCode == AceAutoFillError::ACE_AUTO_FILL_SUCCESS;
}

void TextFieldPattern::HandleDoubleClickEvent(GestureEvent& info)
{
    if (GetIsPreviewText()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "refuse double click when has preview text.");
        return;
    }

    if (showSelect_) {
        SetIsSingleHandle(true);
    }
    if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::DOUBLE_CLICK)) {
        NotifyOnEditChanged(true);
    }
    if (CanChangeSelectState()) {
        selectController_->UpdateSelectByOffset(info.GetLocalLocation());
    }
    if (IsSelected()) {
        StopTwinkling();
        SetIsSingleHandle(false);
    }
    if (info.GetSourceDevice() != SourceType::MOUSE && !IsContentRectNonPositive()) {
        ProcessOverlay({ .animation = true });
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::HandleTripleClickEvent(GestureEvent& info)
{
    if (GetIsPreviewText()) {
        return;
    }

    if (showSelect_) {
        SetIsSingleHandle(true);
        CloseSelectOverlay();
    }
    if (CanChangeSelectState()) {
        selectController_->UpdateSelectPragraphByOffset(info.GetLocalLocation());
    }
    if (IsSelected()) {
        StopTwinkling();
        SetIsSingleHandle(false);
    } else {
        StartTwinkling();
    }
    if (info.GetSourceDevice() != SourceType::MOUSE && !contentController_->IsEmpty() && !IsContentRectNonPositive()) {
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    if (!context->GetTaskExecutor()) {
        return;
    }

    if (dragRecipientStatus_ == DragStatus::DRAGGING) {
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
    isCaretTwinkling_ = true;
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
    isCaretTwinkling_ = false;
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

void TextFieldPattern::ShowCaretAndStopTwinkling()
{
    cursorTwinklingTask_.Cancel();

    // Repaint and make cursor visible.
    isCaretTwinkling_ = false;
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    cursorVisible_ = true;
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
        auto autoFillType = GetAutoFillType(false);
        if (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::UNSPECIFIED ||
            keyBoardMap_.find(autoFillType) == keyBoardMap_.end() || keyboard_ != keyBoardMap_[autoFillType]) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d Keyboard type %{public}d changed to %{public}d",
                tmpHost->GetId(), (int)keyboard_, layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
            keyboard_ = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
            ResetPreviewTextState();
            needToResetKeyboard = true;
        }
    }
    if (!needToResetKeyboard && action_ != TextInputAction::UNSPECIFIED) {
        needToResetKeyboard = action_ != GetTextInputActionValue(GetDefaultTextInputAction());
    }
    action_ = GetTextInputActionValue(GetDefaultTextInputAction());
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    if (needToResetKeyboard && HasFocus()) {
        if (isCustomKeyboardAttached_) {
            RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::RESET_KEYBOARD);
            return;
        }
#if defined(ENABLE_STANDARD_INPUT)
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        CHECK_NULL_VOID(inputMethod);
        MiscServices::Configuration config;
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d Keyboard action is %{public}d",
            tmpHost->GetId(), action_);
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
            SetScrollEnabled(false);
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
    auto showBorder = layoutProperty->GetShowHighlightBorderValue(true);
    if (inputValue == DEFAULT_MODE) {
        if (showBorder) {
            HandleCounterBorder();
        }
        if (showCountBorderStyle_ && !showBorder) {
            UltralimitShake();
        }
    } else if (inputValue != ILLEGAL_VALUE) {
        if (showBorder) {
            HandleCounterBorder();
        }
        if (showCountBorderStyle_) {
            UltralimitShake();
        }
    }
}

void TextFieldPattern::ProcessUnderlineColorOnModifierDone()
{
    if (IsShowError()) {
        return;
    }
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    auto inputValue = layoutProperty->GetSetCounterValue(DEFAULT_MODE);
    if (inputValue == ILLEGAL_VALUE) {
        return;
    }
    auto showBorder = layoutProperty->GetShowHighlightBorderValue(true);
    if (inputValue != DEFAULT_MODE && !showBorder) {
        return;
    }
    if (showCountBorderStyle_ && IsUnderlineMode() && HasFocus()) {
        auto theme = GetTheme();
        CHECK_NULL_VOID(theme);
        SetUnderlineColor(
            userUnderlineColor_.error.value_or(theme->GetErrorUnderlineColor()));
    }
}

void TextFieldPattern::ProcessCounter()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (IsShowCount()) {
        AddCounterNode();
        CHECK_NULL_VOID(counterDecorator_);
        counterDecorator_->UpdateTextFieldMargin();
    } else {
        CleanCounterNode();
    }
}

void TextFieldPattern::ProcessSelection()
{
    auto textWidth = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    if (SelectOverlayIsOn()) {
        needToRefreshSelectOverlay_ = textWidth > 0;
        UpdateSelection(std::clamp(selectController_->GetStartIndex(), 0, textWidth),
            std::clamp(selectController_->GetEndIndex(), 0, textWidth));
        SetIsSingleHandle(!IsSelected());
        selectOverlay_->UpdateHandleColor();
        if (isTextChangedAtCreation_ && textWidth == 0) {
            CloseSelectOverlay();
            StartTwinkling();
        }
    } else if (HasFocus() && !IsSelected()) {
        StartTwinkling();
    } else {
        needToRefreshSelectOverlay_ = false;
    }
}

void TextFieldPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
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
    auto textFieldPaintProperty = host->GetPaintPropertyPtr<TextFieldPaintProperty>();
    if (textFieldPaintProperty && textFieldPaintProperty->HasBorderColorFlagByUser()) {
        textFieldPaintProperty->UpdateBorderColorFlagByUser(
            renderContext->GetBorderColorValue(BorderColorProperty {}));
    }
    isTransparent_ = renderContext->GetOpacityValue(1.0f) == 0.0f;
    ApplyNormalTheme();
    ApplyUnderlineTheme();
    ApplyInlineTheme();
    ProcessInnerPadding();
    ProcessNumberOfLines();

    InitClickEvent();
    InitLongPressEvent();
    InitFocusEvent();
    InitMouseEvent();
    InitTouchEvent();

    SetAccessibilityAction();
    FilterInitializeText();
    InitDisableColor();
    ProcessResponseArea();
    if (!shiftFlag_) {
        InitDragEvent();
    }
    Register2DragDropManager();
    ProcessUnderlineColorOnModifierDone();
    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }
    if (barState_.has_value() && barState_.value() != layoutProperty->GetDisplayModeValue(DisplayMode::AUTO) &&
        HasFocus() && IsNormalInlineState()) {
        lastTextRectY_ = textRect_.GetY();
    }
    if (!IsDisabled() && IsShowError()) {
        SetShowError();
    } else {
        CleanErrorNode();
    }
    // The textRect position can't be changed by only redraw.
    if (!initTextRect_) {
        auto border = GetBorderWidthProperty();
        textRect_.SetLeft(GetPaddingLeft() + GetBorderLeft(border));
        textRect_.SetTop(GetPaddingTop() + GetBorderTop(border));
        AdjustTextRectByCleanNode(textRect_);
        initTextRect_ = true;
    }
    CalculateDefaultCursor();

    ProcessSelection();
    isTextChangedAtCreation_ = false;
    if (layoutProperty->GetTypeChangedValue(false)) {
        layoutProperty->ResetTypeChanged();
        operationRecords_.clear();
        redoOperationRecords_.clear();
    }
    ProcessScroll();
    ProcessCounter();
    Register2DragDropManager();
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    if (autoFillContainerNode) {
        UpdateTextFieldInfo();
    }
    TriggerAvoidWhenCaretGoesDown();
    selectOverlay_->SetIsSupportMenuSearch(IsShowSearch());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    isModifyDone_ = true;
}

void TextFieldPattern::TriggerAvoidWhenCaretGoesDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    if (context->UsingCaretAvoidMode() && HasFocus() && textFieldManager) {
        context->AddAfterLayoutTask([weak = WeakClaim(this), manager = WeakPtr<TextFieldManagerNG>(textFieldManager)] {
            auto textField = weak.Upgrade();
            CHECK_NULL_VOID(textField);
            auto textFieldManager = manager.Upgrade();
            CHECK_NULL_VOID(textFieldManager);
            auto caretPos = textFieldManager->GetFocusedNodeCaretRect().Top() + textFieldManager->GetHeight();
            if (caretPos > textField->GetLastCaretPos()) {
                TAG_LOGI(ACE_KEYBOARD, "Caret Position Goes Down, Retrigger Avoid");
                textField->TriggerAvoidOnCaretChange();
            }
        });
    }
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
    auto aceContentType = GetAutoFillType();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto isValidType =
        (aceContentType >= AceAutoFillType::ACE_PASSWORD && aceContentType <= AceAutoFillType::ACE_FORMAT_ADDRESS) ||
        IsAutoFillUserName(aceContentType);
    if (isValidType && CheckAutoFill()) {
        container->UpdatePopupUIExtension(host, autoFillSessionId_);
    }
}

bool TextFieldPattern::FireOnTextChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto textCache = layoutProperty->GetValueValue(u"");
    auto previewTextCache = layoutProperty->GetPreviewTextValue({GetPreviewTextStart(), u""});
    PreviewText curPreviewText = {GetPreviewTextStart(), GetPreviewTextValue()};
    if (textCache == contentController_->GetTextUtf16Value() && previewTextCache.value == curPreviewText.value) {
        return false;
    }
    host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, UtfUtils::Str16ToStr8(textCache),
        UtfUtils::Str16ToStr8(contentController_->GetTextUtf16Value()));
    AutoFillValueChanged();
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    AddTextFireOnChange();
    auto context = host->GetContextRefPtr();
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
            pattern->TriggerAvoidOnCaretChange();
            if (pattern->customKeyboard_ || pattern->customKeyboardBuilder_) {
                pattern->StartTwinkling();
            }
        },
        TaskExecutor::TaskType::UI, "ArkUITextFieldScrollToSafeArea");
    return true;
}

void TextFieldPattern::AddTextFireOnChange()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    context->AddAfterLayoutTask([weak = AceType::WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto eventHub = host->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(eventHub);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateValue(pattern->GetTextContentController()->GetTextUtf16Value());
        PreviewText previewText {.offset = -1, .value = u""};
        if (pattern->GetIsPreviewText()) {
            previewText.offset = pattern->GetPreviewTextStart();
            previewText.value = pattern->GetPreviewTextValue();
        }
        layoutProperty->UpdatePreviewText(previewText);
        eventHub->FireOnChange(pattern->GetBodyTextValue(), previewText);

        pattern->RecordTextInputEvent();
    });
}

void TextFieldPattern::RecordTextInputEvent()
{
    if (!Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_TEXT_INPUT)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto inputType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    auto isPwdType = inputType == TextInputType::VISIBLE_PASSWORD || inputType == TextInputType::NUMBER_PASSWORD ||
                     inputType == TextInputType::SCREEN_LOCK_PASSWORD || inputType == TextInputType::NEW_PASSWORD;
    if (isPwdType) {
        return;
    }
    Recorder::EventParamsBuilder builder;
    builder.SetEventCategory(Recorder::EventCategory::CATEGORY_TEXT_INPUT)
        .SetEventType(Recorder::EventType::TEXT_INPUT)
        .SetId(host->GetInspectorId().value_or(""))
        .SetType(host->GetTag())
        .SetText(UtfUtils::Str16ToStr8(GetBodyTextValue()))
        .SetDescription(host->GetAutoEventParamValue(""))
        .SetHost(host);
    Recorder::EventRecorder::Get().OnEvent(std::move(builder));
}

void TextFieldPattern::FilterInitializeText()
{
    if (HasInputOperation()) {
        return;
    }
    if (HasFocus()) {
        UpdateShowCountBorderStyle();
        if (showCountBorderStyle_) {
            HandleCountStyle();
        }
    }
    if (!contentController_->IsEmpty()) {
        auto textChanged = contentController_->FilterValue();
        if (!isTextChangedAtCreation_) {
            isTextChangedAtCreation_ = textChanged;
        }
    }
    if (static_cast<int32_t>(GetTextUtf16Value().length()) < GetCaretIndex()) {
        selectController_->UpdateCaretIndex(static_cast<int32_t>(GetTextUtf16Value().length()));
    }
    UpdateShowCountBorderStyle();
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
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    PaddingPropertyF utilPadding;
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    auto left = !paddingProperty ? CalcLength(themePadding.Left()).GetDimension()
                                 : paddingProperty->left.value_or(CalcLength(themePadding.Left())).GetDimension();
    utilPadding.left = left.ConvertToPx();
    auto top = !paddingProperty ? CalcLength(themePadding.Top()).GetDimension()
                                : paddingProperty->top.value_or(CalcLength(themePadding.Top())).GetDimension();
    utilPadding.top = top.ConvertToPx();
    auto bottom = !paddingProperty ? CalcLength(themePadding.Bottom()).GetDimension()
                                   : paddingProperty->bottom.value_or(CalcLength(themePadding.Bottom())).GetDimension();
    utilPadding.bottom = bottom.ConvertToPx();
    auto right = !paddingProperty ? CalcLength(themePadding.Right()).GetDimension()
                                  : paddingProperty->right.value_or(CalcLength(themePadding.Right())).GetDimension();
    utilPadding.right = right.ConvertToPx();
    utilPadding_ = utilPadding;
    PaddingProperty paddings;
    paddings.top = NG::CalcLength(top);
    paddings.bottom = NG::CalcLength(bottom);
    paddings.left = NG::CalcLength(left);
    paddings.right = NG::CalcLength(right);
    layoutProperty->UpdatePadding(paddings);
}

void TextFieldPattern::ProcessNumberOfLines()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto layoutProperty = tmpHost->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty && layoutProperty->HasNumberOfLines());
    auto numberOfLines = layoutProperty->GetNumberOfLines().value();
    CHECK_NULL_VOID(numberOfLines > 0);
    auto lineHeight = layoutProperty->GetLineHeight().value_or(0.0_vp).ConvertToPx();
    if (LessOrEqual(lineHeight, 0.f)) {
        lineHeight = PreferredLineHeight(false);
    }
    auto lineSpacing = layoutProperty->GetLineSpacing().value_or(0.0_vp).ConvertToPx();
    auto contentHeight = numberOfLines * lineHeight + numberOfLines * lineSpacing;
    auto height = contentHeight + GetVerticalPaddingAndBorderSum();

    // get previously user defined ideal width
    std::optional<CalcLength> width = std::nullopt;
    auto &&layoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        width = layoutConstraint->selfIdealSize->Width();
    }
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(width, CalcLength(height)));
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

void TextFieldPattern::StartVibratorByLongPress()
{
    CHECK_NULL_VOID(isEnableHapticFeedback_);
    VibratorUtils::StartVibraFeedback("longPress.light");
}

void TextFieldPattern::HandleLongPress(GestureEvent& info)
{
    CHECK_NULL_VOID(!IsDragging());
    CHECK_NULL_VOID(!IsHandleDragging());
    auto focusHub = GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    if (!focusHub->IsFocusable() || IsOnUnitByPosition(info.GetLocalLocation()) || GetIsPreviewText() ||
        IsOnPasswordByPosition(info.GetLocalLocation()) || IsOnCleanNodeByPosition(info.GetLocalLocation())) {
        return;
    }
    moveCaretState_.isTouchCaret = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleLongPress %{public}d", host->GetId());
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
    StartVibratorByLongPress();
    if (BetweenSelectedPosition(info)) {
        gestureHub->SetIsTextDraggable(true);
        return;
    }
    gestureHub->SetIsTextDraggable(false);
    isLongPress_ = true;
    if (!focusHub->IsCurrentFocus()) {
        TextFieldRequestFocus(RequestFocusReason::LONG_PRESS);
    }

    auto localOffset = info.GetLocalLocation();
    if (CanChangeSelectState()) {
        selectController_->UpdateSelectWithBlank(localOffset);
        StopTwinkling();
    }
    SetIsSingleHandle(!IsSelected());
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    CloseSelectOverlay();
    longPressFingerNum_ = info.GetFingerList().size();
    if (magnifierController_ && HasText() && (longPressFingerNum_ == 1)) {
        magnifierController_->SetLocalOffset({ localOffset.GetX(), localOffset.GetY() });
    }
    StartGestureSelection(start, end, localOffset);
    TriggerAvoidOnCaretChange();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::BetweenSelectedPosition(GestureEvent& info)
{
    if (!IsSelected()) {
        return false;
    }
    auto localOffset = info.GetLocalLocation();
    auto offsetX = IsTextArea() ? contentRect_.GetX() : textRect_.GetX();
    auto offsetY = IsTextArea() ? textRect_.GetY() : contentRect_.GetY();
    Offset offset = localOffset - Offset(offsetX, offsetY);
    for (const auto& rect : selectController_->GetSelectedRects()) {
        bool isInRange = rect.IsInRegion({ offset.GetX(), offset.GetY() });
        if (isInRange) {
            return true;
        }
    }
    return false;
}

bool TextFieldPattern::CanChangeSelectState()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, false);
    Dimension fontSize = layoutProperty->GetFontSizeValue(theme->GetFontSize());
    // fontSize == 0 can not change
    return !NearZero(fontSize.Value()) && !IsContentRectNonPositive();
}

bool TextFieldPattern::IsAccessibilityClick()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return accessibilityProperty->GetAccessibilityFocusState();
}

bool TextFieldPattern::IsOnUnitByPosition(const Offset& localOffset)
{
    if (!IsShowUnit()) {
        return false;
    }
    auto unitArea = AceType::DynamicCast<UnitResponseArea>(responseArea_);
    CHECK_NULL_RETURN(unitArea, false);
    auto frameNode = unitArea->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetGeometryNode()->GetFrameRect().IsInRegion({ localOffset.GetX(), localOffset.GetY() });
}

bool TextFieldPattern::IsOnPasswordByPosition(const Offset& localOffset)
{
    auto passwordArea = AceType::DynamicCast<PasswordResponseArea>(responseArea_);
    CHECK_NULL_RETURN(passwordArea, false);
    auto frameNode = passwordArea->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetGeometryNode()->GetFrameRect().IsInRegion({ localOffset.GetX(), localOffset.GetY() });
}

bool TextFieldPattern::IsOnCleanNodeByPosition(const Offset& localOffset)
{
    auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
    CHECK_NULL_RETURN(cleanNodeResponseArea, false);
    auto frameNode = cleanNodeResponseArea->GetFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetGeometryNode()->GetFrameRect().IsInRegion({ localOffset.GetX(), localOffset.GetY() });
}

bool TextFieldPattern::IsMouseOverScrollBar(const BaseEventInfo* info)
{
    CHECK_NULL_RETURN(GetScrollBar(), false);
    Point point;
    do {
        auto gestureEvent = TypeInfoHelper::DynamicCast<GestureEvent>(info);
        if (gestureEvent) {
            point = Point(gestureEvent->GetLocalLocation().GetX(), gestureEvent->GetLocalLocation().GetY());
            break;
        }
        auto mouseInfo = TypeInfoHelper::DynamicCast<MouseInfo>(info);
        if (mouseInfo) {
            point = Point(mouseInfo->GetLocalLocation().GetX(), mouseInfo->GetLocalLocation().GetY());
            break;
        }
        return false;
    } while (false);
    if (GetScrollBar()->NeedPaint() && GetScrollBar()->GetShapeMode() == ShapeMode::RECT) {
        auto barRect = GetScrollBar()->GetBarRect();
        auto mouseScrollbarRegionWidth = MOUSE_SCROLL_BAR_REGION_WIDTH.ConvertToPx();
        barRect.SetLeft(barRect.Left() + (barRect.Width() - mouseScrollbarRegionWidth));
        barRect.SetWidth(mouseScrollbarRegionWidth);
        barRect.SetHeight(frameRect_.Height());
        barRect.SetTop(0.0f);
        return barRect.IsInRegion(point);
    }
    return false;
}

void TextFieldPattern::UpdateCaretPositionWithClamp(const int32_t& pos)
{
    selectController_->UpdateCaretIndex(
        std::clamp(pos, 0, static_cast<int32_t>(contentController_->GetTextUtf16Value().length())));
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
    return layoutProperty->GetCopyOptionsValue(CopyOptions::Local) != CopyOptions::None && !IsInPasswordMode();
}

void TextFieldPattern::OnDetachFromFrameNode(FrameNode* node)
{
    CloseSelectOverlay();
    auto pipeline = GetContext();
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

void TextFieldPattern::InitEditingValueText(std::u16string content)
{
    if (HasInputOperation()) {
        return;
    }
    contentController_->SetTextValueOnly(std::move(content));
    selectController_->UpdateCaretIndex(GetTextUtf16Value().length());
    if (GetIsPreviewText() && GetTextUtf16Value().empty()) {
        FinishTextPreviewOperation();
    }
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

bool TextFieldPattern::InitValueText(std::u16string content)
{
    if (GetIsPreviewText()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Init when has previewText");
        return false;
    }
    if (HasInputOperation() && content != u"") {
        return false;
    }
    contentController_->SetTextValueOnly(std::move(content));
    selectController_->UpdateCaretIndex(GetTextUtf16Value().length());
    GetHost()->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    return true;
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
    InitPanEvent();
}

void TextFieldPattern::InitPanEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (!boxSelectPanEvent_) {
        auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {};
        auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {};
        auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {};
        GestureEventNoParameter actionCancelTask;
        boxSelectPanEvent_ = MakeRefPtr<PanEvent>(std::move(actionStartTask), std::move(actionUpdateTask),
            std::move(actionEndTask), std::move(actionCancelTask));
    }
    PanDirection panDirection = { .type = PanDirection::ALL };
    gestureHub->AddPanEvent(boxSelectPanEvent_, panDirection, 1, DEFAULT_PAN_DISTANCE);
    gestureHub->SetPanEventType(GestureTypeName::TEXTFIELD_BOXSELECT);
    gestureHub->SetOnGestureJudgeNativeBegin([weak = WeakClaim(this)](const RefPtr<NG::GestureInfo>& gestureInfo,
                                                 const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        if (gestureInfo->GetType() == GestureTypeName::BOXSELECT &&
            gestureInfo->GetInputEventType() == InputEventType::MOUSE_BUTTON) {
            return GestureJudgeResult::REJECT;
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, GestureJudgeResult::CONTINUE);
        if (gestureInfo->GetType() == GestureTypeName::TEXTFIELD_BOXSELECT &&
            gestureInfo->GetInputEventType() == InputEventType::TOUCH_SCREEN &&
            pattern->moveCaretState_.isMoveCaret) {
            return GestureJudgeResult::CONTINUE;
        }
        if (gestureInfo->GetType() == GestureTypeName::TEXTFIELD_BOXSELECT &&
            gestureInfo->GetInputEventType() != InputEventType::MOUSE_BUTTON) {
            return GestureJudgeResult::REJECT;
        }
        auto host = pattern->GetHost();
        CHECK_NULL_RETURN(host, GestureJudgeResult::CONTINUE);
        if (gestureInfo->GetType() == GestureTypeName::TEXTFIELD_BOXSELECT &&
            gestureInfo->GetInputEventType() == InputEventType::MOUSE_BUTTON &&
            host->IsDraggable() && pattern->IsPressSelectedBox()) {
            return GestureJudgeResult::REJECT;
        }
        return GestureJudgeResult::CONTINUE;
    });
}

void TextFieldPattern::OnHover(bool isHover)
{
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    auto pipeline = frame->GetContext();
    auto textFieldTheme = GetTheme();
    if (!pipeline || !textFieldTheme) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Textfield %{public}d hover can't get pipeline",
            frame->GetId());
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Textfield %{public}d %{public}s", frame->GetId(),
        isHover ? "on hover" : "exit hover");
    pipeline->SetMouseStyleHoldNode(frameId);
    if (!isHover) {
        int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
        windowId = static_cast<int32_t>(GetSCBSystemWindowId());
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
    windowId = static_cast<int32_t>(GetSCBSystemWindowId());
#endif
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto id = host->GetId();
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "RestoreDefaultMouseState id:%{public}d, winId:%{public}d", id, windowId);
    pipeline->SetMouseStyleHoldNode(id);
    pipeline->ChangeMouseStyle(id, MouseFormat::DEFAULT, windowId);
}

void TextFieldPattern::ChangeMouseState(
    const Offset location, int32_t frameId, bool isByPass)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto responseAreaWidth = (responseArea_ ? responseArea_->GetAreaRect().Width() : 0.0f) +
                             (cleanNodeResponseArea_ ? cleanNodeResponseArea_->GetAreaRect().Width() : 0.0f);
    auto x = location.GetX();
    auto y = location.GetY();
    int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = static_cast<int32_t>(GetSCBSystemWindowId());
#endif
    if (GreatNotEqual(x, 0) && LessNotEqual(x, frameRect_.Width()) && GreatNotEqual(y, 0) &&
        LessNotEqual(y, frameRect_.Height())) {
        auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
        if (!isRTL && GreatNotEqual(location.GetX(), frameRect_.Width() - responseAreaWidth)) {
            RestoreDefaultMouseState();
        } else if (isRTL && LessNotEqual(location.GetX(), responseAreaWidth)) {
            RestoreDefaultMouseState();
        } else {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "ChangeMouseState Id:%{public}d, winId:%{public}d", frameId, windowId);
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
    auto pipeline = tmpHost->GetContext();
    CHECK_NULL_VOID(pipeline);
    info.SetStopPropagation(true);
    selectOverlay_->SetLastSourceType(info.GetSourceDevice());
    auto scrollBar = GetScrollBar();
    int32_t windowId = 0;
#ifdef WINDOW_SCENE_SUPPORTED
    windowId = static_cast<int32_t>(GetSCBSystemWindowId());
#endif
    if (scrollBar && (scrollBar->IsPressed() || scrollBar->IsHover() || IsMouseOverScrollBar(&info))) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT, windowId);
        return;
    }
    ChangeMouseState(info.GetLocalLocation(), frameId, info.GetAction() == MouseAction::WINDOW_LEAVE);

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
    if (IsSelected() || GetIsPreviewText()) {
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
    if (GetIsPreviewText()) {
        return;
    }
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
    isPressSelectedBox_ =
        (IsSelected() && BetweenSelectedPosition(info.GetGlobalLocation()) && !shiftFlag_);
    if (isPressSelectedBox_ || GetIsPreviewText()) {
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
    if (!focusHub->IsFocusOnTouch().value_or(true) || !TextFieldRequestFocus(RequestFocusReason::MOUSE)) {
        StopTwinkling();
        return;
    }
    UpdateCaretByClick(info.GetLocalLocation());
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::UpdateShiftFlag(const KeyEvent& keyEvent)
{
    bool flag = false;
    if (keyEvent.action == KeyAction::DOWN) {
        if (keyEvent.HasKey(KeyCode::KEY_SHIFT_LEFT) || keyEvent.HasKey(KeyCode::KEY_SHIFT_RIGHT)) {
            flag = true;
        }
    }
    if (flag != shiftFlag_) {
        shiftFlag_ = flag;
        if (!shiftFlag_) {
            // open drag
            InitDragEvent();
        } else  {
            // close drag
            ClearDragDropEvent();
        }
    }
}

void TextFieldPattern::UpdateCaretByClick(const Offset& localOffset)
{
    if (shiftFlag_) {
        selectController_->UpdateSecondHandleInfoByMouseOffset(localOffset);
        StopTwinkling();
    } else {
        selectController_->UpdateCaretInfoByOffset(localOffset, true, false);
        StartTwinkling();
    }
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
        selectController_->UpdateCaretInfoByOffset(info.GetLocalLocation(), true, false);
        StartTwinkling();
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
    FreeMouseStyleHoldNode(info.GetLocalLocation());
    mouseStatus_ = MouseStatus::NONE;
    blockPress_ = false;
    leftMouseCanMove_ = false;
    if (HasFocus() && RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::MOUSE_RELEASE)) {
        NotifyOnEditChanged(true);
        tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextFieldPattern::FreeMouseStyleHoldNode(const Offset location)
{
    auto rect = RectF(0.0f, 0.0f, frameRect_.Width(), frameRect_.Height());
    if (!location.IsPositiveOffset() || !rect.IsInRegion({ location.GetX(), location.GetY() })) {
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto frameId = tmpHost->GetId();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "FreeMouseStyleHoldNode, id:%{public}d", frameId);
        pipeline->FreeMouseStyleHoldNode(frameId);
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
    auto safeAreaManager = context->GetSafeAreaManager();
    CHECK_NULL_VOID(safeAreaManager);
    textFieldManager->UpdateScrollableParentViewPort(tmpHost);
    if (!HasFocus()) {
        return;
    }
    textFieldManager->SetClickPosition({ offset.GetX() + selectController_->GetCaretRect().GetX(),
        offset.GetY() + selectController_->GetCaretRect().GetY() });
    textFieldManager->SetHeight(selectController_->GetCaretRect().Height());
    textFieldManager->SetClickPositionOffset(safeAreaManager->GetKeyboardOffset());
    textFieldManager->SetOnFocusTextField(WeakClaim(this));
    textFieldManager->SetUsingCustomKeyboardAvoid(keyboardAvoidance_);
    textFieldManager->SetIfFocusTextFieldIsInline(IsNormalInlineState());
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
    auto autoFillType = GetAutoFillType(false);
    if (keyBoardMap_.find(autoFillType) != keyBoardMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "Set InputType to %{public}d because of contentType", keyBoardMap_[autoFillType]);
        keyboard_ = keyBoardMap_[autoFillType];
    }
}

int32_t TextFieldPattern::GetRequestKeyboardId()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    return host->GetId();
}

bool TextFieldPattern::RequestKeyboard(bool isFocusViewChanged, bool needStartTwinkling, bool needShowSoftKeyboard)
{
    bool isFocus = HasFocus();
    if (!showKeyBoardOnFocus_ || !isFocus) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "showKeyBoardOnFocus:%{public}d, isFocus:%{public}d", showKeyBoardOnFocus_,
            isFocus);
        return false;
    }
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    if (customKeyboard_ || customKeyboardBuilder_) {
        CHECK_NULL_RETURN(needShowSoftKeyboard, true);
        return RequestCustomKeyboard();
    }
    bool ok = true;
    KeyboardContentTypeToInputType();
#if defined(ENABLE_STANDARD_INPUT)
    if (textChangeListener_ == nullptr) {
        textChangeListener_ = new OnTextChangedListenerImpl(WeakClaim(this));
    }
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    if (!inputMethod) {
        TAG_LOGE(AceLogTag::ACE_TEXT_FIELD, "RequestKeyboard, inputMethod is null");
        return false;
    }
    auto optionalTextConfig = GetMiscTextConfig();
    CHECK_NULL_RETURN(optionalTextConfig.has_value(), false);
    MiscServices::TextConfig textConfig = optionalTextConfig.value();
    ACE_LAYOUT_SCOPED_TRACE("RequestKeyboard[id:%d][WId:%u]", tmpHost->GetId(), textConfig.windowId);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "node:%{public}d, RequestKeyboard set calling window id:%{public}u"
        " inputType:%{public}d, enterKeyType:%{public}d, needKeyboard:%{public}d",
        tmpHost->GetId(), textConfig.windowId, textConfig.inputAttribute.inputPattern,
        textConfig.inputAttribute.enterKeyType, needShowSoftKeyboard);
#ifdef WINDOW_SCENE_SUPPORTED
    auto systemWindowId = GetSCBSystemWindowId();
    if (systemWindowId) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "windowId From %{public}u to %{public}u.", textConfig.windowId,
            systemWindowId);
        textConfig.windowId = systemWindowId;
    }
#endif
    if ((customKeyboard_ || customKeyboardBuilder_) && isCustomKeyboardAttached_) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Request SoftKeyboard, Close CustomKeyboard.");
        CloseCustomKeyboard();
    }
    auto context = tmpHost->GetContextRefPtr();
    if (context && context->GetTextFieldManager()) {
        auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
        textFieldManager->SetImeAttached(true);
        textFieldManager->SetLastRequestKeyboardId(GetRequestKeyboardId());
    }
    auto ret = inputMethod->Attach(textChangeListener_, needShowSoftKeyboard, textConfig);
    if (ret == MiscServices::ErrorCode::NO_ERROR) {
        auto pipeline = GetContext();
        CHECK_NULL_RETURN(pipeline, false);
        auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
        CHECK_NULL_RETURN(textFieldManager, false);
        textFieldManager->SetIsImeAttached(true);
    }
    UpdateCaretInfoToController(true);
    if (!fillContentMap_.empty()) {
        inputMethod->SendPrivateCommand(fillContentMap_);
        fillContentMap_.clear();
    }
#else
    ok = RequestKeyboardCrossPlatForm(isFocusViewChanged);
#endif
    return ok;
}

bool TextFieldPattern::RequestKeyboardCrossPlatForm(bool isFocusViewChanged)
{
#if !defined(ENABLE_STANDARD_INPUT)
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    auto context = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(context, false);
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
        value.hint = UtfUtils::Str16ToStr8(GetPlaceHolder());
        value.selection.Update(selectController_->GetStartIndex(), selectController_->GetEndIndex());
        connection_->SetEditingState(value, GetInstanceId());
    }
    connection_->Show(isFocusViewChanged, GetInstanceId());
#endif
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
    auto offset = AVOID_OFFSET.ConvertToPx();
    auto textPaintOffset = GetPaintRectGlobalOffset();
    double height = selectController_->GetCaretRect().Bottom() + windowRect.Top() +
             textPaintOffset.GetY() + offset - positionY;

    GetInlinePositionYAndHeight(positionY, height);

    auto manager = pipeline->GetSafeAreaManager();
    if (manager) {
        auto keyboardOffset = manager->GetKeyboardOffset();
        positionY -= keyboardOffset;
    }

    MiscServices::CursorInfo cursorInfo { .left = selectController_->GetCaretRect().Left() + windowRect.Left() +
                                                  textPaintOffset.GetX(),
        .top = selectController_->GetCaretRect().Top() + windowRect.Top() + textPaintOffset.GetY(),
        .width = theme->GetCursorWidth().ConvertToPx(),
        .height = selectController_->GetCaretRect().Height() };
    MiscServices::InputAttribute inputAttribute = { .inputPattern = (int32_t)keyboard_,
        .enterKeyType = (int32_t)GetTextInputActionValue(GetDefaultTextInputAction()),
        .isTextPreviewSupported = hasSupportedPreviewText_ };
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

void TextFieldPattern::GetInlinePositionYAndHeight(double& positionY, double& height) const
{
    if (IsNormalInlineState()) {
        auto theme = GetTheme();
        CHECK_NULL_VOID(theme);
        auto offset = AVOID_OFFSET.ConvertToPx();
        auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
        PaddingProperty userPadding;
        if (paintProperty->HasPaddingByUser()) {
            userPadding = paintProperty->GetPaddingByUserValue();
        } else {
            userPadding.top = CalcLength(theme->GetPadding().Top());
        }
        auto topPadding = userPadding.top->GetDimension().ConvertToPx();
        auto safeBoundary = theme->GetInlineBorderWidth().ConvertToPx() * 2;
        positionY += static_cast<double>(inlineMeasureItem_.inlineSizeHeight) + safeBoundary + topPadding;
        height = offset;

        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto pipeline = tmpHost->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
        CHECK_NULL_VOID(textFieldManager);
        TAG_LOGI(ACE_TEXT_FIELD, "SetInlineAvoidInfo positionY:%{public}f height:%{public}f sizeHeight:%{public}f",
            positionY, height, inlineMeasureItem_.inlineSizeHeight);
        textFieldManager->SetInlineTextFieldAvoidPositionYAndHeight(positionY, height);
    }
}

#endif

AceAutoFillType TextFieldPattern::ConvertToAceAutoFillType(TextInputType type)
{
    static std::unordered_map<TextInputType, AceAutoFillType> convertMap = {
        { TextInputType::VISIBLE_PASSWORD, AceAutoFillType::ACE_PASSWORD },
        { TextInputType::USER_NAME, AceAutoFillType::ACE_USER_NAME },
        { TextInputType::NEW_PASSWORD, AceAutoFillType::ACE_NEW_PASSWORD },
        { TextInputType::NUMBER_PASSWORD, AceAutoFillType::ACE_PASSWORD } };
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
        auto host = GetHost();
        CHECK_NULL_RETURN(host, false);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d Will Close Soft keyboard.", host->GetId());
        if ((customKeyboard_ || customKeyboardBuilder_) && isCustomKeyboardAttached_) {
            return CloseCustomKeyboard();
        }
#if defined(ENABLE_STANDARD_INPUT)
        auto inputMethod = MiscServices::InputMethodController::GetInstance();
        if (!inputMethod) {
            TAG_LOGE(AceLogTag::ACE_TEXT_FIELD, "CloseKeyboard, inputMethod is null");
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
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "TextField Request CustomKeyboard, Close keyboard Successfully.");
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
    CHECK_NULL_RETURN(customKeyboard_ || customKeyboardBuilder_, false);
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    ACE_LAYOUT_SCOPED_TRACE("RequestCustomKeyboard[id:%d]", frameNode->GetId());
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "RequestCustomKeyboard, id:%{public}d", frameNode->GetId());
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    overlayManager->SetCustomKeyboardOption(keyboardAvoidance_);
    if (customKeyboardBuilder_) {
        overlayManager->BindKeyboard(customKeyboardBuilder_, frameNode->GetId());
    } else {
        overlayManager->BindKeyboardWithNode(customKeyboard_, frameNode->GetId());
    }
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    if (textFieldManager) {
        textFieldManager->SetLastRequestKeyboardId(GetRequestKeyboardId());
    }
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

bool TextFieldPattern::BeforeIMEInsertValue(const std::u16string& insertValue, int32_t offset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    InsertValueInfo insertValueInfo;
    insertValueInfo.insertOffset = offset;
    insertValueInfo.insertValue = insertValue;
    return eventHub->FireOnWillInsertValueEvent(insertValueInfo);
}

void TextFieldPattern::AfterIMEInsertValue(const std::u16string& insertValue)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    InsertValueInfo insertValueInfo;
    auto offset = selectController_->GetCaretIndex();
    insertValueInfo.insertOffset = offset;
    insertValueInfo.insertValue = insertValue;
    return eventHub->FireOnDidInsertValueEvent(insertValueInfo);
}

void TextFieldPattern::CalcCounterAfterFilterInsertValue(
    int32_t curLength, const std::u16string insertValue, int32_t maxLength)
{
    bool textChange = false;
    auto result = insertValue;
    contentController_->FilterTextInputStyle(textChange, result);
    int32_t sum = curLength + static_cast<int32_t>(result.length());
    showCountBorderStyle_ = sum > maxLength;
    HandleCountStyle();
}

void TextFieldPattern::InsertValueOperation(const SourceAndValueInfo& info)
{
    auto insertValue = info.insertValue;
    auto isIME = info.isIME;
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto start = selectController_->GetStartIndex();
    auto end = selectController_->GetEndIndex();
    GetEmojiSubStringRange(start, end);
    auto caretStart = IsSelected() ? start : selectController_->GetCaretIndex();
    if (isIME) {
        auto isInsert = BeforeIMEInsertValue(insertValue, caretStart);
        CHECK_NULL_VOID(isInsert);
    }
    int32_t caretMoveLength = 0;
    bool hasInsertValue = false;
    int32_t originLength = 0;
    if (IsSelected()) {
        auto value = contentController_->GetSelectedValue(start, end);
        auto isDelete = true;
        if (isIME) {
            isDelete = BeforeIMEDeleteValue(value, TextDeleteDirection::BACKWARD, end);
        }
        end = isDelete ? end : start;
        originLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - (end - start);
        hasInsertValue = contentController_->ReplaceSelectedValue(start, end, insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - originLength);
        if (isIME && isDelete) {
            selectController_->UpdateCaretIndex(start);
            AfterIMEDeleteValue(value, TextDeleteDirection::BACKWARD);
        }
    } else {
        originLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
        hasInsertValue = contentController_->InsertValue(selectController_->GetCaretIndex(), insertValue);
        caretMoveLength = abs(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - originLength);
    }
    if (layoutProperty->HasMaxLength()) {
        CalcCounterAfterFilterInsertValue(originLength, insertValue,
            static_cast<int32_t>(layoutProperty->GetMaxLengthValue(Infinity<uint32_t>())));
    }
    selectController_->UpdateCaretIndex(caretStart + caretMoveLength);
    UpdateObscure(insertValue, hasInsertValue);
    UpdateEditingValueToRecord();
    if (isIME) {
        AfterIMEInsertValue(contentController_->GetInsertValue());
    }
    TwinklingByFocus();
}

void TextFieldPattern::TwinklingByFocus()
{
    if (HasFocus()) {
        cursorVisible_ = true;
        StartTwinkling();
        focusIndex_ = FocuseIndex::TEXT;
    } else {
        cursorVisible_ = false;
        StopTwinkling();
    }
}

bool TextFieldPattern::FinishTextPreviewByPreview(const std::u16string& insertValue)
{
    if (GetIsPreviewText()) {
        SetPreviewText(insertValue, { -1, -1 });
        FinishTextPreview();
        return true;
    }
    return false;
}

void TextFieldPattern::UpdateObscure(const std::u16string& insertValue, bool hasInsertValue)
{
    if (!IsTextArea() && IsInPasswordMode() && GetTextObscured()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        if (insertValue.length() == 1 &&
            (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED) != TextInputType::NUMBER_PASSWORD ||
                std::isdigit(insertValue[0])) &&
            hasInsertValue) {
            auto content = contentController_->GetTextUtf16Value();
            auto insertIndex = selectController_->GetCaretIndex() - 1;
            insertIndex = std::clamp(insertIndex, 0, static_cast<int32_t>(content.length()));
            auto strBeforeCaret = content.empty() ? u"" : content.substr(insertIndex, 1);
            obscureTickCountDown_ = strBeforeCaret == insertValue ? OBSCURE_SHOW_TICKS : 0;
            nakedCharPosition_ = strBeforeCaret == insertValue ? insertIndex : -1;
        } else {
            obscureTickCountDown_ = 0;
            nakedCharPosition_ = -1;
        }
    }
}

void TextFieldPattern::InsertValue(const std::u16string& insertValue, bool isIME)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!HasFocus()) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d on blur, can't insert value", host->GetId());
        auto currentFocusNode = InputMethodManager::GetInstance()->GetCurFocusNode();
        auto curFocusNode = currentFocusNode.Upgrade();
        CHECK_NULL_VOID(curFocusNode);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "curFocusNode:%{public}s, ", curFocusNode->GetTag().c_str());
        return;
    }
    if (!isEdit_ || (isIME && IsDragging())) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "textfield %{public}d NOT allow input, isEdit_ = %{public}d, IsDragging = %{public}d", host->GetId(),
            isEdit_, IsDragging());
        return;
    }
    if (focusIndex_ != FocuseIndex::TEXT && insertValue == u" ") {
        HandleSpaceEvent();
        return;
    }
    focusIndex_ = FocuseIndex::TEXT;
    if (FinishTextPreviewByPreview(insertValue)) {
        return;
    }
    inputOperations_.emplace(InputOperation::INSERT);
    SourceAndValueInfo info;
    info.insertValue = insertValue;
    info.isIME = isIME;
    insertValueOperations_.emplace(info);
    CloseSelectOverlay(true);
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::InsertValue(const std::string& insertValue, bool isIME)
{
    InsertValue(UtfUtils::Str8ToStr16(insertValue), isIME);
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
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    AnimationUtils::Animate(
        option,
        [weak = WeakClaim(context.GetRawPtr())]() {
            auto context = weak.Upgrade();
            CHECK_NULL_VOID(context);
            context->UpdateTranslateInXY({ 0.0f, 0.0f });
        },
        option.GetOnFinishEvent());
}

void TextFieldPattern::AdjustFloatingCaretInfo(const Offset& localOffset,
    const HandleInfoNG& caretInfo, HandleInfoNG& floatingCaretInfo)
{
    CHECK_NULL_VOID(selectController_);
    auto offsetX = localOffset.GetX();
    auto offsetY = caretInfo.rect.Top();
    floatingCaretInfo.rect.SetHeight(caretInfo.rect.Height());
    auto contentRect = GetTextContentRect();
    offsetX = std::min(std::max(contentRect.Left(), static_cast<float>(offsetX)),
        contentRect.Right() - caretInfo.rect.Width());
    offsetY = std::min(std::max(contentRect.Top(), static_cast<float>(offsetY)),
        contentRect.Bottom() - floatingCaretInfo.rect.Height());
    floatingCaretInfo.UpdateOffset({offsetX, offsetY});
    bool reachBoundary = NearEqual(contentRect.Left(), offsetX) ||
        NearEqual(contentRect.Right() - caretInfo.rect.Width(), static_cast<float>(offsetX));
    bool distanceMoreThenTenVp = floatingCaretInfo.rect.GetOffset().GetDistance(caretInfo.rect.GetOffset())
        >= FLOATING_CARET_SHOW_ORIGIN_CARET_DISTANCE.ConvertToPx();
    SetShowOriginCursor(reachBoundary ||
        (selectController_->IsTouchAtLineEndOrBegin(localOffset) && distanceMoreThenTenVp));
    SetFloatingCursorVisible(true);
}

void TextFieldPattern::FloatingCaretLand()
{
    CHECK_NULL_VOID(floatCaretState_.FloatingCursorVisible && textFieldOverlayModifier_ && selectController_);
    textFieldOverlayModifier_->StartFloatingCaretLand(selectController_->GetCaretRect().GetOffset());
}

void TextFieldPattern::CleanCounterNode()
{
    counterDecorator_.Reset();
}

void TextFieldPattern::CleanErrorNode()
{
    errorDecorator_.Reset();
}

void TextFieldPattern::UpdateEditingValueToRecord(int32_t beforeCaretPosition)
{
    if (operationRecords_.size() >= RECORD_MAX_LENGTH) {
        operationRecords_.erase(operationRecords_.begin());
    }
    TextEditingValueNG record {
        .text = contentController_->GetTextUtf16Value(),
        .caretPosition = selectController_->GetCaretIndex(),
        .beforeCaretPosition = beforeCaretPosition,
    };
    operationRecords_.emplace_back(record);
}

float TextFieldPattern::PreferredTextHeight(bool isPlaceholder, bool isAlgorithmMeasure)
{
    if (!isAlgorithmMeasure && paragraph_ && paragraph_->GetHeight() != 0.0f && paragraph_->GetLineCount() > 0) {
        return paragraph_->GetHeight() / paragraph_->GetLineCount();
    }
    RefPtr<Paragraph> paragraph;
    std::u16string textContent;
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
        textContent = u"a";
    } else {
        TextFieldLayoutAlgorithm::UpdatePlaceholderTextStyle(tmpHost, layoutProperty, textFieldTheme, textStyle, false);
        textContent = u"b";
    }
    if (adaptFontSize_.has_value()) {
        textStyle.SetFontSize(adaptFontSize_.value());
    }
    if (textStyle.GetFontSize().IsNonPositive()) {
        textStyle.SetFontSize(DEFAULT_FONT);
    }
    if (textStyle.GetLineHeight().IsNegative()) {
        textStyle.SetLineHeight(Dimension(0.0));
    }
    ParagraphStyle paraStyle { .direction =
                                   TextFieldLayoutAlgorithm::GetTextDirection(contentController_->GetTextUtf16Value()),
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = Localization::GetInstance()->GetFontLocale(),
        .wordBreak = textStyle.GetWordBreak(),
        .lineBreakStrategy = textStyle.GetLineBreakStrategy(),
        .textOverflow = textStyle.GetTextOverflow(),
        .fontSize = FontSizeConvertToPx(textStyle.GetFontSize()) };
    paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    CHECK_NULL_RETURN(paragraph, 0.0f);
    paragraph->PushStyle(textStyle);
    paragraph->AddText(textContent);
    paragraph->Build();
    paragraph->Layout(std::numeric_limits<double>::infinity());
    return paragraph->GetHeight();
}

float TextFieldPattern::FontSizeConvertToPx(const Dimension& fontSize)
{
    return fontSize.ConvertToPx();
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
    UpdateCaretInfoToController();
}

int32_t TextFieldPattern::GetWordLength(int32_t originCaretPosition, int32_t directionMove)
{
    if (contentController_->IsEmpty()) {
        return 0;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    auto wideTextValue = contentController_->GetTextUtf16Value();
    int32_t wordStart = 0;
    int32_t wordEnd = 0;
    while (directionMove == 0 ? strIndex >= 0 : strIndex <= textLength) {
        auto chr = wideTextValue[strIndex];
        // skip the special character
        if (chr == L' ' || chr == L'\n') {
            if (directionMove == 0) {
                strIndex--;
            } else {
                strIndex++;
            }
            offset++;
            continue;
        }
        // cal word length
        if (paragraph_ && paragraph_->GetWordBoundary(strIndex, wordStart, wordEnd)) {
            if (directionMove == 1) {
                offset += (wordEnd - strIndex);
            } else {
                offset += (strIndex - wordStart + 1); // when move left, actual offset should add 1
            }
            return std::clamp(offset, 0, textLength);
        } else {
            // GetWordBoundary fail
            return 0;
        }
    }
    return std::clamp(offset, 0, textLength);
}

int32_t TextFieldPattern::GetLineBeginPosition(int32_t originCaretPosition, bool needToCheckLineChanged)
{
    if (contentController_->IsEmpty()) {
        return 0;
    }
    auto wideTextValue = contentController_->GetTextUtf16Value();
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
    } while (((strIndex > 0) && (wideTextValue[strIndex] != u'\n')) &&
             (needToCheckLineChanged ? !CharLineChanged(strIndex) : true));
    if (strIndex < 0 || strIndex >= static_cast<int32_t>(wideTextValue.length())) {
        return 0;
    }
    if (strIndex > 0) {
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
    auto wideTextValue = contentController_->GetTextUtf16Value();
    int32_t textLength = static_cast<int32_t>(wideTextValue.length());
    if (originCaretPosition < 0 || originCaretPosition > textLength) {
        return originCaretPosition;
    }
    if (originCaretPosition == textLength) {
        return originCaretPosition;
    }
    int32_t moveLineEndOffset = 0;
    int32_t strIndex = 0;
    for (strIndex = originCaretPosition; (strIndex <= textLength && wideTextValue[strIndex] != u'\n') &&
                                         (needToCheckLineChanged ? !CharLineChanged(strIndex) : true);
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
    if (caretPosition < 0 || caretPosition > static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
        return true;
    }
    CaretMetricsF caretMetrics;
    CalcCaretMetricsByPosition(caretPosition, caretMetrics);
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
            GetGraphemeClusterLength(contentController_->GetTextUtf16Value(), selectController_->GetCaretIndex(),
                true));
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
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    OnCursorMoveDone(TextAffinity::DOWNSTREAM);
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
            GetGraphemeClusterLength(contentController_->GetTextUtf16Value(), selectController_->GetCaretIndex()));
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
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
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
    if (selectController_->GetCaretIndex() == static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
        return true;
    }
    int32_t originCaretPosition = selectController_->GetCaretIndex();
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    UpdateCaretPositionWithClamp(textLength);
    OnCursorMoveDone();
    return originCaretPosition != selectController_->GetCaretIndex();
}

bool TextFieldPattern::CursorMoveUpOperation()
{
    if (!IsTextArea()) {
        return CursorMoveToParagraphBegin();
    }
    auto originCaretPosition = selectController_->GetCaretIndex();
    auto offsetX = selectController_->GetCaretRect().GetX();
    // multiply by 0.5f to convert to the grapheme center point of the previous line.
    auto offsetY = selectController_->GetCaretRect().GetY() - PreferredLineHeight() * 0.5f;
    if (offsetY < textRect_.GetY()) {
        return CursorMoveToParagraphBegin();
    }
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
    if (!IsTextArea()) {
        return CursorMoveToParagraphEnd();
    }
    auto originCaretPosition = selectController_->GetCaretIndex();
    auto offsetX = selectController_->GetCaretRect().GetX();
    // multiply by 1.5f to convert to the grapheme center point of the next line.
    auto offsetY = selectController_->GetCaretRect().GetY() + PreferredLineHeight() * 1.5f;
    if (offsetY > textRect_.GetY() + textRect_.Height()) {
        return CursorMoveToParagraphEnd();
    }
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
    if (isLongPress_) {
        CancelGestureSelection();
    }
    CloseSelectOverlay(true);
    StartTwinkling();
    UpdateEditingValueToRecord();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::HandleCounterBorder()
{
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (showCountBorderStyle_) {
        if (IsUnderlineMode()) {
            underlineWidth_ = ERROR_UNDERLINE_WIDTH;
            SetUnderlineColor(userUnderlineColor_.error.value_or(theme->GetErrorUnderlineColor()));
        } else {
            if (!paintProperty->HasBorderWidthFlagByUser()) {
                paintProperty->UpdateInnerBorderWidth(OVER_COUNT_BORDER_WIDTH);
                paintProperty->UpdateInnerBorderColor(theme->GetOverCounterColor());
            } else {
                BorderColorProperty overCountBorderColor;
                overCountBorderColor.SetColor(theme->GetOverCounterColor());
                renderContext->UpdateBorderColor(overCountBorderColor);
            }
        }
    } else {
        if (IsUnderlineMode() && !IsShowError()) {
            ApplyUnderlineTheme();
            CHECK_NULL_VOID(counterDecorator_);
            counterDecorator_->UpdateTextFieldMargin();
        } else {
            SetThemeBorderAttr();
        }
    }
}

bool TextFieldPattern::ProcessFocusIndexAction()
{
    if (focusIndex_ == FocuseIndex::CANCEL) {
        CleanNodeResponseKeyEvent();
        return false;
    }
    if (focusIndex_ == FocuseIndex::UNIT) {
        if (IsShowPasswordIcon()) {
            PasswordResponseKeyEvent();
        }
        if (IsShowUnit()) {
            UnitResponseKeyEvent();
        }
        return false;
    }
    return true;
}

void TextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    if (!ProcessFocusIndexAction()) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "TextField PerformAction %{public}d", static_cast<int32_t>(action));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // If the parent node is a Search, the Search callback is executed.
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    TextFieldCommonEvent event;
    event.SetText(contentController_->GetTextUtf16Value());
    if (IsNormalInlineState() && action != TextInputAction::NEW_LINE) {
        RecordSubmitEvent();
        eventHub->FireOnSubmit(static_cast<int32_t>(action), event);
        if (event.IsKeepEditable()) {
            return;
        }
        TextFieldLostFocusToViewRoot();
        return;
    }
    if (IsTextArea() && action == TextInputAction::NEW_LINE) {
        if (!textAreaBlurOnSubmit_) {
            if (GetInputFilter() != "\n") {
                InsertValue(u"\n", true);
            }
        } else {
            CloseKeyboard(forceCloseKeyboard, false);
            TextFieldLostFocusToViewRoot();
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
        TextFieldLostFocusToViewRoot();
    }
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
    UiSessionManager::GetInstance().ReportComponentChangeEvent("event", "Textfield.onSubmit");
#endif
}

void TextFieldPattern::TextFieldLostFocusToViewRoot()
{
    CHECK_NULL_VOID(HasFocus());
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
        .SetHost(host)
        .SetDescription(host->GetAutoEventParamValue(""));
    if (!isPwdType) {
        builder.SetText(contentController_->GetTextValue());
    }
    Recorder::EventRecorder::Get().OnEvent(std::move(builder));
}

void TextFieldPattern::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
    UpdateEditingValueToRecord();
    contentController_->SetTextValue(UtfUtils::Str8ToStr16(value->text));
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

void TextFieldPattern::UpdateInputFilterErrorText(const std::u16string& errorText)
{
    if (!errorText.empty()) {
        auto tmpHost = GetHost();
        CHECK_NULL_VOID(tmpHost);
        auto textFieldEventHub = tmpHost->GetEventHub<TextFieldEventHub>();
        CHECK_NULL_VOID(textFieldEventHub);
        textFieldEventHub->FireOnInputFilterError(errorText);
    }
}

void TextFieldPattern::UpdateInputFilterErrorText(const std::string& errorText)
{
    UpdateInputFilterErrorText(UtfUtils::Str8ToStr16(errorText));
}

void TextFieldPattern::OnValueChanged(bool needFireChangeEvent, bool needFireSelectChangeEvent) {}

void TextFieldPattern::OnHandleAreaChanged()
{
    auto parentGlobalOffset = GetPaintRectGlobalOffset();
    if (parentGlobalOffset != parentGlobalOffset_) {
        parentGlobalOffset_ = parentGlobalOffset;
        UpdateTextFieldManager(Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY()), frameRect_.Height());
        HandleParentGlobalOffsetChange();
    }
}

void TextFieldPattern::HandleParentGlobalOffsetChange()
{
    selectController_->CalculateHandleOffset();
    CHECK_NULL_VOID(SelectOverlayIsOn() || selectOverlay_->SelectOverlayIsCreating());
    if (selectOverlay_->IsShowMouseMenu()) {
        CloseSelectOverlay();
        return;
    }
    if (selectOverlay_->IsHiddenHandle() && selectOverlay_->IsSingleHandle()) {
        selectOverlay_->ProcessOverlayOnAreaChanged({ .menuIsShow = false });
    } else {
        selectOverlay_->ProcessOverlay({ .menuIsShow = false });
    }
}

void TextFieldPattern::RequestKeyboardByFocusSwitch()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "%{public}d RequestKeyboardByFocusSwitch: onFocus_: %{public}d Inner: %{public}d modalCovered: %{public}d",
        host->GetId(), needToRequestKeyboardOnFocus_, needToRequestKeyboardInner_, IsModalCovered());
    if (!needToRequestKeyboardInner_ || IsModalCovered()) {
        return;
    }
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetNeedToRequestKeyboard(true);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "%{public}d add requestkeyboard task", host->GetId());
    pipeline->AddAfterLayoutTask([weak = WeakClaim(this), manager = WeakPtr<TextFieldManagerNG>(textFieldManager)]() {
        auto textField = weak.Upgrade();
        CHECK_NULL_VOID(textField);
        auto textFieldManager = manager.Upgrade();
        if (textFieldManager && !textFieldManager->GetNeedToRequestKeyboard()) {
            // already call close/attach keyboard after text field get focus, so dont request keyboard now
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Already call close/attach before attach, no need attach this time");
            return;
        }
        if (!textField->needToRequestKeyboardInner_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Not need to requestKeyboard inner");
            return;
        }
        if (!textField->RequestKeyboard(false, true, textField->needToRequestKeyboardOnFocus_)) {
            return;
        }
        textField->NotifyOnEditChanged(true);
        textField->SetNeedToRequestKeyboardInner(false, RequestKeyboardInnerChangeReason::REQUEST_KEYBOARD_SUCCESS);
    });
}

// to distiguish request keyboard not by focus switching
bool TextFieldPattern::RequestKeyboardNotByFocusSwitch(RequestKeyboardReason reason)
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "%{public}d requestKeyboard With Reason %{public}s",
        tmpHost->GetId(), TextFieldPattern::RequestKeyboardReasonToString(reason).c_str());
    if (!RequestKeyboard(false, true, true)) {
        return false;
    }
    auto context = tmpHost->GetContextRefPtr();
    CHECK_NULL_RETURN(context, true);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_RETURN(textFieldManager, true);
    textFieldManager->SetNeedToRequestKeyboard(false);
    return true;
}

bool TextFieldPattern::TextFieldRequestFocus(RequestFocusReason reason)
{
    if (HasFocus()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "%{public}d Request Focus With Reason %{public}s",
        host->GetId(), TextFieldPattern::RequestFocusReasonToString(reason).c_str());
    auto focusHub = GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    requestFocusReason_ = reason;
    return focusHub->RequestFocusImmediately();
}

std::string TextFieldPattern::RequestFocusReasonToString(RequestFocusReason reason)
{
    switch (reason) {
        case RequestFocusReason::DRAG_END: {
            return "DragEnd";
        }
        case RequestFocusReason::DRAG_MOVE: {
            return "DragMove";
        }
        case RequestFocusReason::DRAG_ENTER: {
            return "DragEnter";
        }
        case RequestFocusReason::CLICK: {
            return "Click";
        }
        case RequestFocusReason::LONG_PRESS: {
            return "LongPress";
        }
        case RequestFocusReason::AUTO_FILL: {
            return "AutoFill";
        }
        case RequestFocusReason::CLEAN_NODE: {
            return "CleanNode";
        }
        case RequestFocusReason::MOUSE: {
            return "Mouse";
        }
        case RequestFocusReason::UNKNOWN:
        default: {
            break;
        }
    }
    return "Unknown";
}

std::string TextFieldPattern::RequestKeyboardReasonToString(RequestKeyboardReason reason)
{
    switch (reason) {
        case RequestKeyboardReason::ON_KEY_EVENT: {
            return "KeyEvent";
        }
        case RequestKeyboardReason::SINGLE_CLICK: {
            return "SingleClick";
        }
        case RequestKeyboardReason::DOUBLE_CLICK: {
            return "DoubleClick";
        }
        case RequestKeyboardReason::LONG_PRESS: {
            return "LongPress";
        }
        case RequestKeyboardReason::RESET_KEYBOARD: {
            return "ResetKeyboard";
        }
        case RequestKeyboardReason::MOUSE_RELEASE: {
            return "MouseRelease";
        }
        case RequestKeyboardReason::SET_SELECTION: {
            return "SetSelection";
        }
        case RequestKeyboardReason::SEARCH_REQUEST: {
            return "SearchRequest";
        }
        case RequestKeyboardReason::AUTO_FILL_REQUEST_FAIL: {
            return "AutoFillRequestFail";
        }
        case RequestKeyboardReason::SHOW_KEYBOARD_ON_FOCUS: {
            return "ShowKeyboardOnFocus";
        }
        case RequestKeyboardReason::STYLUS_DETECTOR: {
            return "StylusDetector";
        }
        case RequestKeyboardReason::CUSTOM_KEYBOARD: {
            return "CustomKeyboard";
        }
        case RequestKeyboardReason::UNKNOWN:
        default: {
            break;
        }
    }
    return "Unknown";
}

bool TextFieldPattern::IsModalCovered()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pageNode = host->GetPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    return pagePattern->GetIsModalCovered();
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
    if (newWidth == prevWidth && newHeight == prevHeight) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "Textfield handleSurface change, new width %{public}d, new height %{public}d, prev width %{public}d, prev "
        "height %{public}d",
        newWidth, newHeight, prevWidth, prevHeight);
    if (SelectOverlayIsOn()) {
        if (selectOverlay_->IsShowMouseMenu()) {
            CloseSelectOverlay();
        } else if (newWidth != prevWidth || newHeight != prevHeight) {
            DelayProcessOverlay({ .menuIsShow = false });
        }
        selectOverlay_->RemoveAvoidKeyboardCallback();
    }
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    UpdateCaretInfoToController(true);
    if (magnifierController_->GetShowMagnifier()) {
        magnifierController_->RemoveMagnifierFrameNode();
    }
}

void TextFieldPattern::HandleSurfacePositionChanged(int32_t posX, int32_t posY)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Textfield handleSurface position change, posX %{public}d, posY %{public}d",
        posX, posY);
    UpdateCaretInfoToController();
}

void TextFieldPattern::InitSurfaceChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
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

void TextFieldPattern::GetEmojiSubStringRange(int32_t& start, int32_t& end)
{
    TextEmojiSubStringRange range = TextEmojiProcessor::CalSubU16stringRange(
        start, end - start, GetTextUtf16Value(), true);
    start = range.startIndex;
    end = range.endIndex;
}

void TextFieldPattern::DeleteBackward(int32_t length)
{
    CHECK_NULL_VOID(!IsDragging());
    ResetObscureTickCountDown();
    if (IsSelected()) {
        auto start = selectController_->GetStartIndex();
        auto end = selectController_->GetEndIndex();
        GetEmojiSubStringRange(start, end);
        auto value = contentController_->GetSelectedValue(start, end);
        auto isDelete = BeforeIMEDeleteValue(value, TextDeleteDirection::BACKWARD, end);
        CHECK_NULL_VOID(isDelete);
        Delete(start, end);
        AfterIMEDeleteValue(value, TextDeleteDirection::BACKWARD);
        showCountBorderStyle_ = false;
        HandleCountStyle();
        return;
    }
    if (selectController_->GetCaretIndex() <= 0) {
        auto isDelete = BeforeIMEDeleteValue(u"", TextDeleteDirection::BACKWARD, 0);
        CHECK_NULL_VOID(isDelete);
        AfterIMEDeleteValue(u"", TextDeleteDirection::BACKWARD);
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
    auto willDeleteLength = contentController_->GetDeleteLength(idx, length, true);
    auto value = contentController_->GetSelectedValue(idx - willDeleteLength, idx);
    auto isDelete = BeforeIMEDeleteValue(value, TextDeleteDirection::BACKWARD, idx);
    CHECK_NULL_VOID(isDelete);
    int32_t count = contentController_->Delete(selectController_->GetCaretIndex(), length, true);
    selectController_->UpdateCaretIndex(std::max(idx - count, 0));
    if (GetIsPreviewText()) {
        UpdatePreviewIndex(GetPreviewTextStart(), GetPreviewTextEnd() - length);
    }
    AfterIMEDeleteValue(value, TextDeleteDirection::BACKWARD);
    StartTwinkling();
    focusIndex_ = FocuseIndex::TEXT;
    UpdateEditingValueToRecord();
}

void TextFieldPattern::DeleteForwardOperation(int32_t length)
{
    auto caretIndex = selectController_->GetCaretIndex();
    auto willDeleteLength = contentController_->GetDeleteLength(caretIndex, length, false);
    auto value = contentController_->GetSelectedValue(caretIndex, caretIndex + willDeleteLength);
    auto isDelete = BeforeIMEDeleteValue(value, TextDeleteDirection::FORWARD, caretIndex);
    CHECK_NULL_VOID(isDelete);
    ResetObscureTickCountDown();
    contentController_->Delete(caretIndex, length, false);
    if (GetIsPreviewText()) {
        UpdatePreviewIndex(GetPreviewTextStart(), GetPreviewTextEnd() - length);
    }
    AfterIMEDeleteValue(value, TextDeleteDirection::FORWARD);
    StartTwinkling();
    focusIndex_ = FocuseIndex::TEXT;
    UpdateEditingValueToRecord();
}

void TextFieldPattern::DeleteForward(int32_t length)
{
    CHECK_NULL_VOID(!IsDragging());
    if (IsSelected()) {
        auto start = selectController_->GetStartIndex();
        auto end = selectController_->GetEndIndex();
        GetEmojiSubStringRange(start, end);
        auto value = contentController_->GetSelectedValue(start, end);
        auto isDelete = BeforeIMEDeleteValue(value, TextDeleteDirection::FORWARD, start);
        CHECK_NULL_VOID(isDelete);
        ResetObscureTickCountDown();
        Delete(start, end);
        AfterIMEDeleteValue(value, TextDeleteDirection::FORWARD);
        showCountBorderStyle_ = false;
        HandleCountStyle();
        return;
    }
    auto contentLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    if (selectController_->GetCaretIndex() >= contentLength) {
        auto isDelete = BeforeIMEDeleteValue(u"", TextDeleteDirection::FORWARD, contentLength);
        CHECK_NULL_VOID(isDelete);
        AfterIMEDeleteValue(u"", TextDeleteDirection::FORWARD);
        return;
    }
    inputOperations_.emplace(InputOperation::DELETE_FORWARD);
    deleteForwardOperations_.emplace(length);
    CloseSelectOverlay();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

bool TextFieldPattern::BeforeIMEDeleteValue(
    const std::u16string& deleteValue, TextDeleteDirection direction, int32_t offset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    DeleteValueInfo deleteValueInfo;
    deleteValueInfo.deleteOffset = offset;
    deleteValueInfo.deleteValue = deleteValue;
    deleteValueInfo.direction = direction;
    return eventHub->FireOnWillDeleteEvent(deleteValueInfo);
}

void TextFieldPattern::AfterIMEDeleteValue(const std::u16string& deleteValue, TextDeleteDirection direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    DeleteValueInfo deleteValueInfo;
    deleteValueInfo.deleteOffset = selectController_->GetCaretIndex();
    deleteValueInfo.deleteValue = deleteValue;
    deleteValueInfo.direction = direction;
    return eventHub->FireOnDidDeleteValueEvent(deleteValueInfo);
}

std::u16string TextFieldPattern::GetLeftTextOfCursor(int32_t number)
{
    auto start = selectController_->GetCaretIndex();
    if (IsSelected()) {
        start = selectController_->GetStartIndex();
    }
    return contentController_->GetSelectedValue(start - number, start);
}

std::u16string TextFieldPattern::GetRightTextOfCursor(int32_t number)
{
    auto end = selectController_->GetCaretIndex();
    if (IsSelected()) {
        end = selectController_->GetEndIndex();
    }
    return contentController_->GetSelectedValue(end, end + number);
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
        selectController_->MoveSecondHandleByKeyBoard(
            paragraph_->GetGlyphIndexByCoordinate(
                Offset(selectController_->GetCaretRect().GetX() - contentRect_.GetX(), newOffsetY)),
            TextAffinity::DOWNSTREAM);
    } else {
        selectController_->MoveSecondHandleByKeyBoard(
            static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
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
            GetGraphemeClusterLength(contentController_->GetTextUtf16Value(), selectController_->GetCaretIndex(),
                true));
    } else {
        selectController_->MoveSecondHandleByKeyBoard(selectController_->GetSecondHandleIndex() -
            GetGraphemeClusterLength(contentController_->GetTextUtf16Value(), selectController_->GetSecondHandleIndex(),
                true));
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionLeftWord()
{
    if (selectController_->GetCaretIndex() == 0) {
        return;
    }
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
        if (selectController_->GetCaretIndex() ==
            static_cast<int32_t>(contentController_->GetTextUtf16Value().length())) {
            return;
        }
        UpdateSelection(selectController_->GetCaretIndex());
        selectController_->MoveSecondHandleByKeyBoard(
            selectController_->GetSecondHandleIndex() +
            GetGraphemeClusterLength(contentController_->GetTextUtf16Value(),
                selectController_->GetSecondHandleIndex()));
    } else {
        // if currently not in select mode, move destinationOffset and caret position only
        selectController_->MoveSecondHandleByKeyBoard(
            selectController_->GetSecondHandleIndex() +
            GetGraphemeClusterLength(contentController_->GetTextUtf16Value(),
                selectController_->GetSecondHandleIndex()));
    }
    AfterSelection();
}

void TextFieldPattern::HandleSelectionRightWord()
{
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    int32_t textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    int32_t endPos = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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

void TextFieldPattern::SetCaretPosition(int32_t position, bool moveContent)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Set caret position to %{public}d", position);
    selectController_->MoveCaretToContentRect(position, TextAffinity::DOWNSTREAM, true, moveContent);
    UpdateCaretInfoToController();
    if (HasFocus() && !magnifierController_->GetShowMagnifier()) {
        StartTwinkling();
    }
    CloseSelectOverlay();
    TriggerAvoidOnCaretChange();
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::SetCaretOffset(int32_t caretPostion)
{
    SetCaretPosition(caretPostion);
    return true;
}

void TextFieldPattern::SetSelectionFlag(
    int32_t selectionStart, int32_t selectionEnd, const std::optional<SelectionOptions>& options, bool isForward)
{
    if (!HasFocus() || GetIsPreviewText()) {
        return;
    }
    auto length = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    selectionStart = std::clamp(selectionStart, 0, length);
    selectionEnd = std::clamp(selectionEnd, 0, length);
    moveCaretState_.isTouchCaret = false;
    bool isShowMenu = selectOverlay_->IsCurrentMenuVisibile();
    isTouchPreviewText_ = false;
    if (selectionStart == selectionEnd) {
        selectController_->MoveCaretToContentRect(selectionEnd, TextAffinity::DOWNSTREAM);
        StartTwinkling();
    } else {
        cursorVisible_ = false;
        showSelect_ = true;
        HandleSetSelection(selectionStart, selectionEnd, false);
        if (isForward) {
            selectController_->MoveSecondHandleToContentRect(selectionEnd);
            selectController_->MoveFirstHandleToContentRect(selectionStart, false);
        } else {
            selectController_->MoveFirstHandleToContentRect(selectionStart);
            selectController_->MoveSecondHandleToContentRect(selectionEnd);
        }
    }
    if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SET_SELECTION)) {
        NotifyOnEditChanged(true);
    }
    SetIsSingleHandle(!IsSelected());
    if (!IsShowHandle()) {
        CloseSelectOverlay(true);
    } else {
        isShowMenu = IsShowMenu(options, isShowMenu);
        if (!isShowMenu && IsUsingMouse()) {
            CloseSelectOverlay();
        } else {
            ProcessOverlay({ .menuIsShow = isShowMenu, .animation = true });
        }
    }
    TriggerAvoidWhenCaretGoesDown();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::SetSelection(int32_t start, int32_t end,
    const std::optional<SelectionOptions>& options, bool isForward)
{
    SetSelectionFlag(start, end, options, isForward);
}

bool TextFieldPattern::IsShowMenu(const std::optional<SelectionOptions>& options, bool defaultValue)
{
    if (!options.has_value()) {
        return false;
    }
    if (options.value().menuPolicy == MenuPolicy::HIDE) {
        return false;
    }
    if (options.value().menuPolicy == MenuPolicy::SHOW) {
        return true;
    }
    return defaultValue;
}

bool TextFieldPattern::OnBackPressed()
{
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, false);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "%{public}d receives back press event, %{public}d",
        tmpHost->GetId(), isCustomKeyboardAttached_);
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
    auto content = contentController_->GetTextUtf16Value();
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
        case TextInputType::URL:
            return IsTextArea() ? "TextAreaType.URL" : "InputType.URL";
        case TextInputType::VISIBLE_PASSWORD:
            return "InputType.Password";
        case TextInputType::USER_NAME:
            return "InputType.USER_NAME";
        case TextInputType::NEW_PASSWORD:
            return "InputType.NEW_PASSWORD";
        case TextInputType::NUMBER_PASSWORD:
            return "InputType.NUMBER_PASSWORD";
        case TextInputType::NUMBER_DECIMAL:
            return IsTextArea() ? "TextAreaType.NUMBER_DECIMAL" : "InputType.NUMBER_DECIMAL";
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
    if (textFieldTheme_.Upgrade()) {
        return textFieldTheme_.Upgrade();
    }
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, nullptr);
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto theme = context->GetTheme<TextFieldTheme>();
    return theme;
}

void TextFieldPattern::InitTheme()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    auto context = tmpHost->GetContext();
    CHECK_NULL_VOID(context);
    textFieldTheme_ = context->GetTheme<TextFieldTheme>();
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

std::string TextFieldPattern::GetMinFontSize() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetAdaptMinFontSize()->ToString();
}

std::string TextFieldPattern::GetMaxFontSize() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetAdaptMaxFontSize()->ToString();
}

std::string TextFieldPattern::GetTextIndent() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetTextIndent()->ToString();
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

std::u16string TextFieldPattern::GetPlaceHolder() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, u"");
    return layoutProperty->GetPlaceholderValue(u"");
}

std::string TextFieldPattern::GetInputFilter() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    return layoutProperty->GetInputFilterValue("");
}

std::u16string TextFieldPattern::GetErrorTextString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, u"");
    return layoutProperty->GetErrorTextValue(u"");
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
    if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SEARCH_REQUEST)) {
        NotifyOnEditChanged(true);
    }
}

std::string TextFieldPattern::GetCopyOptionString() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    std::string copyOptionString = "CopyOptions.Local";
    switch (layoutProperty->GetCopyOptionsValue(CopyOptions::Local)) {
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
            copyOptionString = "CopyOptions.None";
            break;
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

void TextFieldPattern::PlayScrollBarAppearAnimation()
{
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->PlayScrollBarAppearAnimation();
    }
}

void TextFieldPattern::ScheduleDisappearDelayTask()
{
    auto scrollBar = GetScrollBar();
    if (scrollBar) {
        scrollBar->SetPressed(false);
        scrollBar->PlayScrollBarShrinkAnimation();
        scrollBar->ScheduleDisappearDelayTask();
    }
}

bool TextFieldPattern::OnScrollCallback(float offset, int32_t source)
{
    if (source == SCROLL_FROM_START) {
        PlayScrollBarAppearAnimation();
        if (selectOverlay_->IsCurrentMenuVisibile()) {
            isTextSelectionMenuShow_ = true;
        } else if (CheckSelectAreaVisible()) {
            isTextSelectionMenuShow_ = false;
        }
        selectOverlay_->HideMenu(true);
        return true;
    }
    if (IsReachedBoundary(offset)) {
        return false;
    }
    PlayScrollBarAppearAnimation();
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
        SetScrollEnabled(scrollable_);
    } else {
        SetScrollEnabled(GreatNotEqual(textRect_.Width(), contentRect_.Width()));
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
    if (counterDecorator_ && (IsShowPasswordIcon() || IsNormalInlineState())) {
        CleanCounterNode();
        return;
    }
    if (!counterDecorator_) {
        auto counterDecorator = MakeRefPtr<CounterDecorator>(host);
        counterDecorator_ = counterDecorator;
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
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto isUnderLine = IsUnderlineMode();
    auto errorText = layoutProperty->GetErrorTextValue(u"");
    if (IsShowError()) { // update error state
        if (isUnderLine) {
            underlineColor_ = userUnderlineColor_.error.value_or(textFieldTheme->GetErrorUnderlineColor());
            underlineWidth_ = ERROR_UNDERLINE_WIDTH;
        } else if (passWordMode) {
            if (!paintProperty->HasBorderWidthFlagByUser()) {
                paintProperty->UpdateInnerBorderWidth(ERROR_BORDER_WIDTH);
                paintProperty->UpdateInnerBorderColor(textFieldTheme->GetPasswordErrorBorderColor());
            } else {
                BorderColorProperty borderColor;
                borderColor.SetColor(textFieldTheme->GetPasswordErrorBorderColor());
                renderContext->UpdateBorderColor(borderColor);
            }
            renderContext->UpdateBackgroundColor(textFieldTheme->GetPasswordErrorInputColor());
            layoutProperty->UpdateTextColor(textFieldTheme->GetPasswordErrorTextColor());
        }
    }
    UpdateErrorTextMargin();
}

float TextFieldPattern::CalcDecoratorWidth(const RefPtr<FrameNode>& decoratorNode)
{
    float decoratorWidth = 0.0f;
    CHECK_NULL_RETURN(decoratorNode, 0.0f);
    auto textPattern = decoratorNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, 0.0f);
    auto paragraphs = textPattern->GetParagraphs();
    for (auto &&info : paragraphs) {
        if (info.paragraph) {
            float width = info.paragraph->GetLongestLine();
            decoratorWidth = std::max(decoratorWidth, width);
        }
    }
    return decoratorWidth;
}

float TextFieldPattern::CalcDecoratorHeight(const RefPtr<FrameNode>& decoratorNode)
{
    CHECK_NULL_RETURN(decoratorNode, 0.0f);
    auto geometryNode = decoratorNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return geometryNode->GetFrameRect().Height();
}

void TextFieldPattern::UpdateErrorTextMargin()
{
    auto tmpHost = GetHost();
    CHECK_NULL_VOID(tmpHost);
    if (IsShowError()) {
        if (!errorDecorator_) {
            auto errorDecorator = MakeRefPtr<ErrorDecorator>(tmpHost);
            errorDecorator_ = errorDecorator;
        }
        errorDecorator_->UpdateTextFieldMargin();
    } else {
        errorDecorator_.Reset();
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
    if (IsShowError()) {
        underlineColor_ = userUnderlineColor_.error.value_or(theme->GetErrorUnderlineColor());
    } else {
        underlineColor_ = HasFocus() ? userUnderlineColor_.typing.value_or(theme->GetUnderlineTypingColor())
            : userUnderlineColor_.normal.value_or(theme->GetUnderlineColor());
    }
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
    margin.right = CalcLength(userMargin.right->GetDimension() + userPadding.right->GetDimension());
    margin.left = CalcLength(userMargin.left->GetDimension() + userPadding.left->GetDimension());
    margin.top = CalcLength(userMargin.top->GetDimension() + userPadding.top->GetDimension());
    layoutProperty->UpdateMargin(margin);
    if (!IsTextArea()) {
        layoutProperty->UpdatePlaceholderMaxLines(layoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE));
        layoutProperty->ResetMaxLines();
    }
    if (layoutProperty->HasTextOverflow()) {
        layoutProperty->UpdateTextOverflowMaxLines(layoutProperty->GetMaxViewLinesValue(INLINE_DEFAULT_VIEW_MAXLINE));
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

    if (layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL) {
        layoutProperty->UpdatePadding({ CalcLength(theme->getInlinePaddingRight()),
            CalcLength(theme->getInlinePaddingLeft()), CalcLength(0.0f), CalcLength(0.0f) });
    } else {
        layoutProperty->UpdatePadding({ CalcLength(theme->getInlinePaddingLeft()),
            CalcLength(theme->getInlinePaddingRight()), CalcLength(0.0f), CalcLength(0.0f)});
    }
    ProcessInnerPadding();
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
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("placeholder", UtfUtils::Str16ToStr8(GetPlaceHolder()).c_str(), filter);
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
    json->PutExtAttr("maxLength", GreatOrEqual(GetMaxLength(),
        Infinity<uint32_t>()) ? "INF" : std::to_string(GetMaxLength()).c_str(), filter);
    json->PutExtAttr("inputFilter", GetInputFilter().c_str(), filter);
    json->PutExtAttr("copyOption", GetCopyOptionString().c_str(), filter);
    json->PutExtAttr("style", GetInputStyleString().c_str(), filter);

    auto jsonValue = JsonUtil::Create(true);
    if (IsShowPasswordSymbol()) {
        jsonValue->Put("onIconSrc", static_cast<int64_t>(GetTheme()->GetShowSymbolId()));
        jsonValue->Put("offIconSrc", static_cast<int64_t>(GetTheme()->GetHideSymbolId()));
    } else {
        jsonValue->Put("onIconSrc", GetShowResultImageSrc().c_str());
        jsonValue->Put("offIconSrc", GetHideResultImageSrc().c_str());
    }
    json->PutExtAttr("passwordIcon", jsonValue->ToString().c_str(), filter);
    json->PutExtAttr("showError", GetErrorTextState() ? UtfUtils::Str16ToStr8(GetErrorTextString()).c_str() :
        "undefined", filter);
    json->PutExtAttr("maxLines", GreatOrEqual(GetMaxLines(),
        Infinity<uint32_t>()) ? "INF" : std::to_string(GetMaxLines()).c_str(), filter);
    json->PutExtAttr("barState", GetBarStateString().c_str(), filter);
    json->PutExtAttr("caretPosition", std::to_string(GetCaretIndex()).c_str(), filter);
    json->PutExtAttr("enablePreviewText", GetSupportPreviewText(), filter);
    ToJsonValueForOption(json, filter);
    ToJsonValueSelectOverlay(json, filter);
}

void TextFieldPattern::ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const
{
    Pattern::ToTreeJson(json, config);
    json->Put(TreeKey::CONTENT, contentController_->GetTextValue().c_str());
    json->Put(TreeKey::PLACEHOLDER, GetPlaceHolder().c_str());
}

void TextFieldPattern::ToJsonValueForOption(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto underlineColorJsonValue = JsonUtil::Create(true);
    underlineColorJsonValue->Put("normal", GetNormalUnderlineColorStr().c_str());
    underlineColorJsonValue->Put("typing", GetTypingUnderlineColorStr().c_str());
    underlineColorJsonValue->Put("error", GetErrorUnderlineColorStr().c_str());
    underlineColorJsonValue->Put("disable", GetDisableUnderlineColorStr().c_str());
    json->PutExtAttr("underlineColor", underlineColorJsonValue->ToString().c_str(), filter);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto jsonShowCounter = JsonUtil::Create(true);
    jsonShowCounter->Put("value", layoutProperty->GetShowCounterValue(false));
    auto jsonShowCounterOptions = JsonUtil::Create(true);
    jsonShowCounterOptions->Put("thresholdPercentage", layoutProperty->GetSetCounterValue(DEFAULT_MODE));
    jsonShowCounterOptions->Put("highlightBorder", layoutProperty->GetShowHighlightBorderValue(true));
    jsonShowCounter->Put("options", jsonShowCounterOptions);
    json->PutExtAttr("showCounter", jsonShowCounter, filter);
}

void TextFieldPattern::ToJsonValueSelectOverlay(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    json->PutExtAttr("CaretStatus", cursorVisible_ ? "show" : "hide", filter);
    json->PutExtAttr("CaretTwinkling", isCaretTwinkling_ ? "true" : "false", filter);
    json->PutExtAttr("caretRect", selectController_->GetCaretRect().ToString().c_str(), filter);
    json->PutExtAttr("caretWidth", std::to_string(selectController_->GetCaretRect().Width()).c_str(), filter);
    json->PutExtAttr("isShowMagnifier", magnifierController_->GetShowMagnifier() ? "true" : "false", filter);
    json->PutExtAttr("MagnifierPosition", magnifierController_->GetLocalOffset().ToString().c_str(), filter);

    auto manager = selectOverlay_->GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto selectOverlayInfo = manager->GetSelectOverlayInfo();
    CHECK_NULL_VOID(selectOverlayInfo);

    //handle info
    json->PutExtAttr("IsSingleHandle", selectOverlayInfo->isSingleHandle ? "true" : "false", filter);
    json->PutExtAttr("IsHandleReverse", selectOverlayInfo->handleReverse ? "true" : "false", filter);
    json->PutExtAttr("FirstHandleRect", selectOverlayInfo->firstHandle.paintRect.ToString().c_str(), filter);
    json->PutExtAttr("FirstHandleStartPoint",
        selectOverlayInfo->firstHandle.paintInfo.startPoint.ToString().c_str(), filter);
    json->PutExtAttr("FirstHandleEndPoint",
        selectOverlayInfo->firstHandle.paintInfo.endPoint.ToString().c_str(), filter);
    json->PutExtAttr("IsFirstHandlePaintByPoints",
        selectOverlayInfo->firstHandle.isPaintHandleWithPoints ? "true" : "false", filter);
    json->PutExtAttr("SecondHandleRect", selectOverlayInfo->secondHandle.paintRect.ToString().c_str(), filter);
    json->PutExtAttr("SecondHandleStartPoint",
        selectOverlayInfo->secondHandle.paintInfo.startPoint.ToString().c_str(), filter);
    json->PutExtAttr("SecondHandleEndPoint",
        selectOverlayInfo->secondHandle.paintInfo.endPoint.ToString().c_str(), filter);
    json->PutExtAttr("IsSecondHandlePaintByPoints",
        selectOverlayInfo->secondHandle.isPaintHandleWithPoints ? "true" : "false", filter);

    //menu
    auto menuNode = manager->GetSelectOverlayNode();
    CHECK_NULL_VOID(menuNode);
    json->PutExtAttr("MenuNode", menuNode->GetTag().c_str(), filter);
    if (menuNode->GetAncestorNodeOfFrame()) {
        json->PutExtAttr("MountOn", menuNode->GetAncestorNodeOfFrame()->GetTag().c_str(), filter);
    }
    auto menuLayoutProperty = menuNode->GetLayoutProperty();
    CHECK_NULL_VOID(menuLayoutProperty);
    auto menuVisible = static_cast<int32_t>(menuLayoutProperty->GetVisibility().value_or(VisibleType::VISIBLE));
    json->PutExtAttr("Visible", std::to_string(menuVisible).c_str(), filter);
    auto menuGeometryNode = menuNode->GetGeometryNode();
    CHECK_NULL_VOID(menuGeometryNode);
    json->PutExtAttr("MenuFrameRect", menuGeometryNode->GetFrameRect().ToString().c_str(), filter);
    json->PutExtAttr("MenuItemCount", std::to_string(selectOverlayInfo->menuOptionItems.size()).c_str(), filter);
    for (auto menuItme : selectOverlayInfo->menuOptionItems) {
        json->PutExtAttr("MenuItme", menuItme.content.value_or("").c_str(), filter);
    }
}

void TextFieldPattern::FromJson(const std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    layoutProperty->UpdatePlaceholder(UtfUtils::Str8ToStr16(json->GetString("placeholder")));
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
    CopyOptions copyOptionsEnum = CopyOptions::Local;
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
    accessibilityProperty->SetAccessibilityGroup(true);
    SetAccessibilityActionOverlayAndSelection();
    SetAccessibilityActionGetAndSetCaretPosition();
    SetAccessibilityMoveTextAction();
    SetAccessibilityErrotText();
}

void TextFieldPattern::SetAccessibilityActionOverlayAndSelection()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionSetText([weakPtr = WeakClaim(this)](const std::string& value) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->InsertValue(UtfUtils::Str8ToStr16(value));
    });

    accessibilityProperty->SetActionSetSelection([weakPtr = WeakClaim(this)](int32_t start,
                                                                             int32_t end, bool isForward) {
            const auto& pattern = weakPtr.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetSelectionFlag(start, end, std::nullopt, isForward);
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

void TextFieldPattern::SetAccessibilityErrotText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetErrorText(UtfUtils::Str16ToStr8(GetErrorTextString()));
}

void TextFieldPattern::StopEditing()
{
    if (!HasFocus()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ContainerScope scope(host->GetInstanceId());
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield %{public}d Stop Editing", host->GetId());
    FocusHub::LostFocusToViewRoot();
    UpdateSelection(selectController_->GetCaretIndex());
    StopTwinkling();
    CloseKeyboard(true);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::DumpInfo()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto& dumpLog = DumpLog::GetInstance();
    dumpLog.AddDesc(std::string("Content:").append(GetDumpTextValue()));
    dumpLog.AddDesc(std::string("autoWidth: ").append(std::to_string(layoutProperty->GetWidthAutoValue(false))));
    dumpLog.AddDesc(std::string("MaxLength:").append(std::to_string(GetMaxLength())));
    dumpLog.AddDesc(std::string("fontSize:").append(GetFontSize()));
    dumpLog.AddDesc(std::string("fontWeight:").append(V2::ConvertWrapFontWeightToStirng(GetFontWeight())));
    dumpLog.AddDesc(std::string("fontFamily:").append(GetFontFamily()));
    auto flag = GetItalicFontStyle() == Ace::FontStyle::NORMAL;
    dumpLog.AddDesc(std::string("fontStyle:").append(flag ? "FontStyle.Normal" : "FontStyle.Italic"));
    dumpLog.AddDesc(std::string("InputFilter:").append(GetInputFilter()));
    auto lineHeight = layoutProperty->GetLineHeight().value_or(0.0_vp).ConvertToPx();
    dumpLog.AddDesc(std::string("lineHeight:").append(std::to_string(lineHeight)));
    auto maxLines = GreatOrEqual(GetMaxLines(), Infinity<uint32_t>()) ? "INF" : std::to_string(GetMaxLines());
    dumpLog.AddDesc(std::string("MaxLines:").append(maxLines));
    dumpLog.AddDesc(std::string("TextIndent:").append(GetTextIndent()));
    dumpLog.AddDesc(std::string("showError:").append(GetErrorTextState() ? UtfUtils::Str16ToStr8(GetErrorTextString()) :
         "undefined"));
    dumpLog.AddDesc(std::string("CopyOption:").append(GetCopyOptionString()));
    dumpLog.AddDesc(std::string("TextAlign:").append(V2::ConvertWrapTextAlignToString(GetTextAlign())));
    dumpLog.AddDesc(std::string("CaretPosition:").append(std::to_string(GetCaretIndex())));
    dumpLog.AddDesc(std::string("type:").append(TextInputTypeToString()));
    dumpLog.AddDesc(std::string("enterKeyType:").append(TextInputActionToString()));
    dumpLog.AddDesc(std::string("HasFocus:").append(std::to_string(HasFocus())));
    dumpLog.AddDesc(std::string("enableKeyboardOnFocus:").append(std::to_string(needToRequestKeyboardOnFocus_)));
    dumpLog.AddDesc(std::string("supportPreviewText:").append(std::to_string(GetSupportPreviewText())));
    dumpLog.AddDesc(
        std::string("enableAutoFill:").append(std::to_string(layoutProperty->GetEnableAutoFillValue(true))));
    dumpLog.AddDesc(std::string("contentType:").append(TextContentTypeToString()));
    dumpLog.AddDesc(std::string("style:").append(GetInputStyleString()));
    dumpLog.AddDesc(std::string("PreviewTextStart:").append(std::to_string(GetPreviewTextStart())));
    dumpLog.AddDesc(std::string("PreviewTextEnd:").append(std::to_string(GetPreviewTextEnd())));
    dumpLog.AddDesc(std::string("PreTextValue:").append(UtfUtils::Str16ToStr8(GetPreviewTextValue())));
    dumpLog.AddDesc(textSelector_.ToString());
    dumpLog.AddDesc(std::string("wordBreak:")
            .append(V2::ConvertWrapWordBreakToString(layoutProperty->GetWordBreak().value_or(WordBreak::BREAK_WORD))));
    dumpLog.AddDesc(std::string("HeightAdaptivePolicy: ").append(V2::ConvertWrapTextHeightAdaptivePolicyToString(
        layoutProperty->GetHeightAdaptivePolicy().value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST))));
    dumpLog.AddDesc(std::string("IsAIWrite: ").append(std::to_string(IsShowAIWrite())));
    DumpPlaceHolderInfo();
    DumpScaleInfo();
    DumpTextEngineInfo();
    DumpAdvanceInfo();
}

void TextFieldPattern::DumpTextEngineInfo()
{
    auto& dumpLog = DumpLog::GetInstance();
    dumpLog.AddDesc(std::string("-----TextEngine paragraphs_ info-----"));
    CHECK_NULL_VOID(paragraph_);
    dumpLog.AddDesc(std::string("GetTextWidth:")
        .append(std::to_string(paragraph_->GetTextWidth()))
        .append(" GetHeight:")
        .append(std::to_string(paragraph_->GetHeight()))
        .append(" GetMaxWidth:")
        .append(std::to_string(paragraph_->GetMaxWidth()))
        .append(" GetMaxIntrinsicWidth:")
        .append(std::to_string(paragraph_->GetMaxIntrinsicWidth())));
    dumpLog.AddDesc(std::string("GetLineCount:")
        .append(std::to_string(paragraph_->GetLineCount()))
        .append(" GetLongestLine:")
        .append(std::to_string(paragraph_->GetLongestLine()))
        .append(" GetLongestLineWithIndent:")
        .append(std::to_string(paragraph_->GetLongestLineWithIndent())));
}

void TextFieldPattern::DumpAdvanceInfo()
{
    if (customKeyboard_ || customKeyboardBuilder_) {
        DumpLog::GetInstance().AddDesc(
            std::string("CustomKeyboard: true, Attached:").append(std::to_string(isCustomKeyboardAttached_)));
    }
    DumpLog::GetInstance().AddDesc(std::string("FontColor: ").append(GetTextColor()));
#if defined(ENABLE_STANDARD_INPUT)
    auto miscTextConfig = GetMiscTextConfig();
    CHECK_NULL_VOID(miscTextConfig.has_value());
    MiscServices::TextConfig textConfig = miscTextConfig.value();
    DumpLog::GetInstance().AddDesc(
        std::string("RequestKeyboard calling window :").append(std::to_string(textConfig.windowId)));
    MiscServices::CursorInfo cursorInfo = miscTextConfig.value().cursorInfo;
    DumpLog::GetInstance().AddDesc(std::string("cursorInfo, left:")
                                       .append(std::to_string(cursorInfo.left))
                                       .append(", top:")
                                       .append(std::to_string(cursorInfo.top))
                                       .append(", width:")
                                       .append(std::to_string(cursorInfo.width))
                                       .append(", height:")
                                       .append(std::to_string(cursorInfo.height)));
#endif
    DumpLog::GetInstance().AddDesc(std::string("textRect: ").append(contentRect_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("contentRect: ").append(contentRect_.ToString()));
}

void TextFieldPattern::DumpPlaceHolderInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("placeholder: ").append(UtfUtils::Str16ToStr8(GetPlaceHolder())));
    DumpLog::GetInstance().AddDesc(std::string("placeholderColor: ").append(GetPlaceholderColor()));
    DumpLog::GetInstance().AddDesc(std::string("placeholderFont: ").append(GetPlaceholderFont()));
}

void TextFieldPattern::DumpScaleInfo()
{
    auto& dumpLog = DumpLog::GetInstance();
    dumpLog.AddDesc(std::string("-----DumpScaleInfo-----"));
    dumpLog.AddDesc(std::string("MinFontSize:").append(GetMinFontSize()));
    dumpLog.AddDesc(std::string("MaxFontSize:").append(GetMaxFontSize()));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto fontScale = pipeline->GetFontScale();
    auto fontWeightScale = pipeline->GetFontWeightScale();
    auto followSystem = pipeline->IsFollowSystem();
    float maxFontScale = pipeline->GetMaxAppFontScale();
    auto halfLeading = pipeline->GetHalfLeading();
    dumpLog.AddDesc(std::string("fontScale: ").append(std::to_string(fontScale)));
    dumpLog.AddDesc(std::string("fontWeightScale: ").append(std::to_string(fontWeightScale)));
    dumpLog.AddDesc(std::string("IsFollowSystem: ").append(std::to_string(followSystem)));
    dumpLog.AddDesc(std::string("maxFontScale: ").append(std::to_string(maxFontScale)));
    dumpLog.AddDesc(std::string("halfLeading: ").append(std::to_string(halfLeading)));
}

std::string TextFieldPattern::GetDumpTextValue() const
{
    if (IsInPasswordMode()) {
        auto len = GetTextValue().length();
        auto passwordLen = "passwordLen:" + std::to_string(len);
        return passwordLen;
    } else {
        return GetTextValue();
    }
}

void TextFieldPattern::DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData)
{
    CHECK_NULL_VOID(viewDataWrap);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto autoFillTypeAndMetaData = GetAutoFillTypeAndMetaData();
    auto info = PageNodeInfoWrap::CreatePageNodeInfoWrap();
    CHECK_NULL_VOID(info);
    info->SetId(host->GetId());
    info->SetDepth(host->GetDepth());
    info->SetAutoFillType(autoFillTypeAndMetaData.autoFillType);
    info->SetMetadata(autoFillTypeAndMetaData.metadata);
    info->SetTag(host->GetTag());
    auto utf8TextValue = UtfUtils::Str16ToStr8(contentController_->GetTextUtf16Value());
    if (autoFillOtherAccount_) {
        viewDataWrap->SetOtherAccount(true);
        info->SetValue(utf8TextValue);
        autoFillOtherAccount_ = false;
    } else {
        info->SetValue(utf8TextValue);
    }
    if (needsRecordData) {
        lastAutoFillTextValue_ = utf8TextValue;
    }
    info->SetPlaceholder(UtfUtils::Str16ToStr8(GetPlaceHolder()));
    info->SetPasswordRules(layoutProperty->GetPasswordRulesValue(""));
    info->SetEnableAutoFill(layoutProperty->GetEnableAutoFillValue(true));
    auto offsetToWindow = host->GetTransformRelativeOffset();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto pageNodeRect = geometryNode->GetFrameRect();
    pageNodeRect.SetLeft(offsetToWindow.GetX());
    pageNodeRect.SetTop(offsetToWindow.GetY());
    info->SetPageNodeRect(pageNodeRect);
    info->SetIsFocus(HasFocus());
    viewDataWrap->AddPageNodeInfoWrap(info);
}

void TextFieldPattern::NotifyFillRequestSuccess(RefPtr<ViewDataWrap> viewDataWrap,
    RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "autoFillType:%{public}d", static_cast<int32_t>(autoFillType));
    SetFillRequestFinish(true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(viewDataWrap);
    CHECK_NULL_VOID(nodeWrap);
    auto isFocus = nodeWrap->GetIsFocus();
    if (isFocus && !HasFocus()) {
        TextFieldRequestFocus(RequestFocusReason::AUTO_FILL);
        DoProcessAutoFill();
    }
    auto type = GetAutoFillType();
    bool fromOtherAccount = viewDataWrap->GetOtherAccount();
    if (!(type == AceAutoFillType::ACE_NEW_PASSWORD && type == autoFillType) && !fromOtherAccount) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "Set last auto fill text value.");
        lastAutoFillTextValue_ = nodeWrap->GetValue();
    }

    if (!contentController_ || contentController_->GetTextValue() == nodeWrap->GetValue()) {
        return;
    }
    contentController_->SetTextValue(UtfUtils::Str8ToStr16(nodeWrap->GetValue()));
    auto textLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    selectController_->UpdateCaretIndex(textLength);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool TextFieldPattern::ParseFillContentJsonValue(const std::unique_ptr<JsonValue>& jsonObject,
    std::unordered_map<std::string, std::variant<std::string, bool, int32_t>>& map)
{
    if (!jsonObject->IsValid() || jsonObject->IsArray() || !jsonObject->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_AUTO_FILL, "fillContent format is not right");
        return false;
    }
    auto child = jsonObject->GetChild();

    while (child && child->IsValid()) {
        if (!child->IsObject() && child->IsString()) {
            std::string strKey = child->GetKey();
            std::string strVal = child->GetString();
            if (strKey.empty()) {
                continue;
            }
            if (map.size() < MAX_FILL_CONTENT_SIZE) {
                map.insert(std::pair<std::string, std::variant<std::string, bool, int32_t> >(strKey, strVal));
            } else {
                TAG_LOGW(AceLogTag::ACE_AUTO_FILL, "fillContent is more than 5");
                break;
            }
        }
        child = child->GetNext();
    }
    return true;
}

void TextFieldPattern::NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent, bool isPopup)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "NotifyFillRequestFailed errCode:%{public}d", errCode);
    SetFillRequestFinish(true);

#if defined(ENABLE_STANDARD_INPUT)
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "fillContent is : %{private}s", fillContent.c_str());
    if (errCode == AUTO_FILL_CANCEL) {
        if (!fillContent.empty() && IsTriggerAutoFillPassword()) {
            auto jsonObject = JsonUtil::ParseJsonString(fillContent);
            CHECK_NULL_VOID(jsonObject);
            fillContentMap_.clear();
            ParseFillContentJsonValue(jsonObject, fillContentMap_);
        }
    }
    if (!isPopup || (isPopup && errCode == AUTO_FILL_CANCEL)) {
        if (RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::AUTO_FILL_REQUEST_FAIL)) {
            NotifyOnEditChanged(true);
        }
    }
#endif
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
    if (!contentController_ || contentController_->GetTextUtf16Value().empty()) {
        return false;
    }
    auto autoFillType = GetAutoFillType();
    if (IsAutoFillUserName(autoFillType)) {
        if (!lastAutoFillTextValue_.empty() &&
            contentController_->GetTextValue() != lastAutoFillTextValue_) {
            return true;
        }
    }
    if (AceAutoFillType::ACE_UNSPECIFIED < autoFillType && autoFillType <= AceAutoFillType::ACE_FORMAT_ADDRESS &&
        !IsAutoFillUserName(autoFillType)) {
        if (contentController_->GetTextValue() != lastAutoFillTextValue_) {
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
    ScrollablePattern::OnColorConfigurationUpdate();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->HasTextColorFlagByUser()) {
        layoutProperty->UpdateTextColor(theme->GetTextColor());
    }
    if (magnifierController_) {
        magnifierController_->SetColorModeChange(true);
    }

    auto colorMode = SystemProperties::GetColorMode();
    SetOriginCursorColor(colorMode == ColorMode::DARK ? Color(0x4DFFFFFF) : Color(0x4D000000));
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
    OffsetF textPaintOffset;
    textPaintOffset = host->GetPaintRectOffset();
    return textPaintOffset - rootOffset;
}

void TextFieldPattern::UpdateSelectController()
{
    selectController_->UpdateContentRect(contentRect_);
    selectController_->UpdateParagraph(paragraph_);
}

bool TextFieldPattern::RepeatClickCaret(const Offset& offset, int32_t lastCaretIndex)
{
    auto touchDownIndex = selectController_->ConvertTouchOffsetToPosition(offset);
    return lastCaretIndex == touchDownIndex && HasFocus();
}

bool TextFieldPattern::RepeatClickCaret(const Offset& offset, const RectF& lastCaretRect)
{
    auto caretRect = lastCaretRect;
    caretRect.SetLeft(caretRect.GetX() - caretRect.Height() / 2);
    caretRect.SetWidth(caretRect.Height());
    return caretRect.IsInRegion(PointF(offset.GetX(), offset.GetY()));
}

void TextFieldPattern::OnAttachToFrameNode()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    StylusDetectorMgr::GetInstance()->AddTextFieldFrameNode(frameNode, WeakClaim(this));

    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCopyOptions(CopyOptions::Local);
    auto pipeline = frameNode->GetContext();
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
    StartTwinkling();
    if (obscuredChange_) {
        selectController_->UpdateCaretIndex(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    }
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

size_t TextFieldPattern::GetLineCount() const
{
    return paragraph_ ? paragraph_->GetLineCount() : 0;
}

void TextFieldPattern::UpdateHandlesOffsetOnScroll(float offset)
{
    if (SelectOverlayIsOn()) {
        selectController_->UpdateSecondHandleOffset();
        if (!selectOverlay_->IsSingleHandle()) {
            selectController_->UpdateFirstHandleOffset();
            selectController_->UpdateCaretOffset(TextAffinity::DOWNSTREAM, false);
            selectOverlay_->UpdateAllHandlesOffset();
        } else {
            selectController_->UpdateCaretOffset(IsTextArea() ? OffsetF(0.0f, offset) : OffsetF(offset, 0.0f));
            selectOverlay_->UpdateSecondHandleOffset();
        }
    } else {
        selectController_->UpdateCaretOffset(IsTextArea() ? OffsetF(0.0f, offset) : OffsetF(offset, 0.0f));
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
    return layoutProperty->GetShowPasswordIconValue(true) && IsInPasswordMode();
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

void TextFieldPattern::AfterLayoutProcessCleanResponse(
    const RefPtr<CleanNodeResponseArea>& cleanNodeResponseArea)
{
    CHECK_NULL_VOID(cleanNodeResponseArea);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weak = WeakClaim(cleanNodeResponseArea.GetRawPtr())]() {
        auto cleanNodeResponseArea = weak.Upgrade();
        CHECK_NULL_VOID(cleanNodeResponseArea);
        cleanNodeResponseArea->UpdateCleanNode(cleanNodeResponseArea->IsShow());
    });
}

void TextFieldPattern::ProcessCancelButton()
{
    if (IsShowCancelButtonMode()) {
        auto cleanNodeResponseArea = AceType::DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
        if (cleanNodeResponseArea) {
            cleanNodeResponseArea->Refresh();
            if (cleanNodeResponseArea->IsShow()) {
                AfterLayoutProcessCleanResponse(cleanNodeResponseArea);
            } else {
                UpdateCancelNode();
            }
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
}

void TextFieldPattern::ProcessResponseArea()
{
    ProcessCancelButton();
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

void TextFieldPattern::AdjustTextRectByCleanNode(RectF& textRect)
{
    auto cleanNodeResponseArea = DynamicCast<CleanNodeResponseArea>(cleanNodeResponseArea_);
    CHECK_NULL_VOID(cleanNodeResponseArea);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cleanNodeStyle = layoutProperty->GetCleanNodeStyle().value_or(CleanNodeStyle::INPUT);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRTL && (cleanNodeStyle == CleanNodeStyle::CONSTANT ||
                     (cleanNodeStyle == CleanNodeStyle::INPUT && !contentController_->IsEmpty()))) {
        auto textFieldTheme = GetTheme();
        CHECK_NULL_VOID(textFieldTheme);
        auto themePadding = textFieldTheme->GetPadding();
        auto rightOffset = static_cast<float>(themePadding.Left().ConvertToPx());
        textRect.SetLeft(textRect.GetX() + cleanNodeResponseArea->GetIconSize() + rightOffset);
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
        if (!cleanNodeResponseArea->IsShow() || cleanNodeResponseArea->CheckUpdateCleanNode()) {
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

void TextFieldPattern::FocusForwardStopTwinkling()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    UpdateSelection(selectController_->GetCaretIndex());
    StopTwinkling();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextFieldPattern::UpdateFocusForward()
{
    if (focusIndex_ == FocuseIndex::TEXT && HasFocus()) {
        FocusForwardStopTwinkling();
        if (!CancelNodeIsShow()) {
            if (responseArea_ == nullptr || (!IsShowUnit() && !IsShowPasswordIcon())) {
                return false;
            }
            focusIndex_ = FocuseIndex::UNIT;
            PaintResponseAreaRect();
            return true;
        }
        focusIndex_ = FocuseIndex::CANCEL;
        PaintCancelRect();
        return true;
    }
    if (focusIndex_ == FocuseIndex::CANCEL && HasFocus()) {
        FocusForwardStopTwinkling();
        if (responseArea_ == nullptr || (!IsShowUnit() && !IsShowPasswordIcon())) {
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
        StartTwinkling();
        return true;
    } else if (focusIndex_ == FocuseIndex::UNIT && HasFocus()) {
        if (!CancelNodeIsShow()) {
            focusIndex_ = FocuseIndex::TEXT;
            PaintTextRect();
            StartTwinkling();
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
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto isRTL = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    RectF rect;
    if (isRTL) {
        rect = RectF(stackRect.GetX() + stackRect.Width() - imageRect.Width(),
            stackRect.GetY(), imageRect.Width(), imageRect.Height());
    } else {
        rect = RectF(stackRect.GetX(), stackRect.GetY(), imageRect.Width(), imageRect.Height());
    }
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
            float cornerRadius = paintRect.GetRect().Width() / 2;
            paintRect.SetCornerRadius(cornerRadius);
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
    InitEditingValueText(u"");
    CloseSelectOverlay();
    StartTwinkling();
    UpdateCaretInfoToController();
    if (!HasFocus()) {
        auto focusHub = host->GetOrCreateFocusHub();
        TextFieldRequestFocus(RequestFocusReason::CLEAN_NODE);
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::RegisterWindowSizeCallback()
{
    if (isOritationListenerRegisted_) {
        return;
    }
    isOritationListenerRegisted_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowSizeChangeCallback(host->GetId());
}

void TextFieldPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (type != WindowSizeChangeReason::ROTATION) {
        return;
    }
    if (SelectOverlayIsOn()) {
        selectController_->CalculateHandleOffset();
        selectOverlay_->ProcessOverlayOnAreaChanged({ .menuIsShow = false});
    }
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
            auto textField = weak.Upgrade();
            CHECK_NULL_VOID(textField);
            auto host = textField->GetHost();
            CHECK_NULL_VOID(host);
            auto nodeId = host->GetId();
            textField->parentGlobalOffset_ = textField->GetPaintRectGlobalOffset();
            textField->UpdateTextFieldManager(Offset(textField->parentGlobalOffset_.GetX(),
                textField->parentGlobalOffset_.GetY()), textField->frameRect_.Height());
            if (textField->HasFocus()) {
                textField->UpdateCaretInfoToController(true);
                TAG_LOGI(ACE_TEXT_FIELD, "%{public}d OnWindowSizeChanged change parentGlobalOffset to: %{public}s",
                    nodeId, textField->parentGlobalOffset_.ToString().c_str());
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
        TaskExecutor::TaskType::UI, "ArkUITextFieldOnWindowSizeChangedRotation");
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
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::SELECT_ETS_TAG) {
        auto selectPattern = frameNode->GetPattern<SelectPattern>();
        CHECK_NULL_VOID(selectPattern);
        selectPattern->ShowSelectMenu();
    }
}

void TextFieldPattern::ScrollToSafeArea() const
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

void TextFieldPattern::TriggerAvoidOnCaretChange()
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
    if (!safeAreaManager || NearEqual(safeAreaManager->GetKeyboardInset().Length(), 0)) {
        return;
    }
    textFieldManager->TriggerAvoidOnCaretChange();
    auto caretPos = textFieldManager->GetFocusedNodeCaretRect().Top() + textFieldManager->GetHeight();
    SetLastCaretPos(caretPos);
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
    if (isLongPress_ && HasFocus() && RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::LONG_PRESS)) {
        NotifyOnEditChanged(true);
        if (!isCustomKeyboardAttached_ || keyboardAvoidance_) {
            selectOverlay_->AddAvoidKeyboardCallback(isCustomKeyboardAttached_);
        }
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

void TextFieldPattern::ScrollPage(bool reverse, bool smooth, AccessibilityScrollType scrollType)
{
    auto border = GetBorderWidthProperty();
    float maxFrameHeight =
        frameRect_.Height() - GetPaddingTop() - GetPaddingBottom() - GetBorderTop(border) - GetBorderBottom(border);
    float distance = reverse ? maxFrameHeight : -maxFrameHeight;
    if (scrollType == AccessibilityScrollType::SCROLL_HALF) {
        distance = distance / 2.f;
    }
    OnScrollCallback(distance, SCROLL_FROM_JUMP);
}

// correct after OnModifyDone
bool TextFieldPattern::IsUnderlineMode() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetShowUnderlineValue(false) && IsUnspecifiedOrTextType() && !IsInlineMode();
}

// correct after OnModifyDone
bool TextFieldPattern::IsInlineMode() const
{
    return HasFocus() && IsNormalInlineState();
}

bool TextFieldPattern::IsShowError()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto errorText = layoutProperty->GetErrorTextValue(u"");
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);

    paintProperty->ResetInnerBorderColor();
    paintProperty->ResetInnerBorderWidth();
    if (!paintProperty->HasBorderColorFlagByUser()) {
        BorderColorProperty borderColor;
        borderColor.SetColor(Color::BLACK);
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
        borderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
        renderContext->UpdateBorderWidth(borderWidth);
        layoutProperty->UpdateBorderWidth(borderWidth);
    } else {
        renderContext->UpdateBorderWidth(paintProperty->GetBorderWidthFlagByUserValue());
        layoutProperty->UpdateBorderWidth(paintProperty->GetBorderWidthFlagByUserValue());
    }
}

PaddingProperty TextFieldPattern::GetPaddingByUserValue()
{
    PaddingProperty padding;
    auto theme = GetTheme();
    CHECK_NULL_RETURN(theme, padding);
    auto paintProperty = GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, padding);
    padding = paintProperty->GetPaddingByUserValue();
    auto themePadding = IsUnderlineMode() ? theme->GetUnderlinePadding() : theme->GetPadding();
    if (!padding.top.has_value()) {
        padding.top = CalcLength(CalcLength(themePadding.Top()).GetDimension());
    }
    if (!padding.bottom.has_value()) {
        padding.bottom = CalcLength(CalcLength(themePadding.Bottom()).GetDimension());
    }
    if (!padding.left.has_value()) {
        padding.left = CalcLength(CalcLength(themePadding.Left()).GetDimension());
    }
    if (!padding.right.has_value()) {
        padding.right = CalcLength(CalcLength(themePadding.Right()).GetDimension());
    }
    return padding;
}

void TextFieldPattern::SetThemeAttr()
{
    auto host = GetHost();
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
        layoutProperty->UpdatePadding(GetPaddingByUserValue());
    }

    if (!paintProperty->HasTextColorFlagByUser()) {
        layoutProperty->UpdateTextColor(theme->GetTextColor());
    } else {
        layoutProperty->UpdateTextColor(paintProperty->GetTextColorFlagByUserValue());
    }
    inlineFocusState_ = false;
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
    parentGlobalOffset_ = GetPaintRectGlobalOffset();
    auto localOffset = globalOffset - Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY());
    if (selectOverlay_->HasRenderTransform()) {
        auto localOffsetF = OffsetF(globalOffset.GetX(), globalOffset.GetY());
        selectOverlay_->RevertLocalPointWithTransform(localOffsetF);
        localOffset.SetX(localOffsetF.GetX());
        localOffset.SetY(localOffsetF.GetY());
    }
    return localOffset;
}

int32_t TextFieldPattern::SetPreviewText(const std::u16string &previewValue, const PreviewRange range)
{
    PreviewTextInfo info = {
        .text = previewValue,
        .range = range
    };
    auto host = GetHost();
    CHECK_NULL_RETURN(host, PREVIEW_NULL_POINTER);
    inputOperations_.emplace(InputOperation::SET_PREVIEW_TEXT);
    previewTextOperation_.emplace(info);
    CloseSelectOverlay(true);
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    return PREVIEW_NO_ERROR;
}

int32_t TextFieldPattern::SetPreviewText(const std::string &previewValue, const PreviewRange range)
{
    return SetPreviewText(UtfUtils::Str8ToStr16(previewValue), range);
}

void TextFieldPattern::SetPreviewTextOperation(PreviewTextInfo info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!hasPreviewText_) {
        auto fullStr = GetTextUtf16Value();
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FOURTEEN) && IsSelected()) {
            uint32_t startIndex = selectController_->GetStartIndex();
            uint32_t endIndex = selectController_->GetEndIndex();
            if (startIndex < fullStr.length() && endIndex < fullStr.length()) {
                fullStr.erase(startIndex, endIndex - startIndex);
            }
        }
        bodyTextInPreivewing_ = fullStr;
    }
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
    auto originLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - (end - start);
    hasInsertValue = contentController_->ReplaceSelectedValue(start, end, info.text);
    int32_t caretMoveLength = abs(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) -
        originLength);

    int32_t delta =
            static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - originLength - (end - start);
    int32_t newCaretPosition = std::max(end, GetPreviewTextEnd()) + delta;
    newCaretPosition = std::clamp(newCaretPosition, 0,
        static_cast<int32_t>(contentController_->GetTextUtf16Value().length()));
    selectController_->UpdateCaretIndex(start + caretMoveLength);

    UpdatePreviewIndex(start, newCaretPosition);
    hasPreviewText_ = true;
    if (HasFocus()) {
        cursorVisible_ = true;
        StartTwinkling();
    } else {
        cursorVisible_ = false;
        StopTwinkling();
    }
}

void TextFieldPattern::FinishTextPreview()
{
    inputOperations_.emplace(InputOperation::SET_PREVIEW_FINISH);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ScrollToSafeArea();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

void TextFieldPattern::FinishTextPreviewOperation()
{
    if (!hasPreviewText_) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "input state now is not at previewing text");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasMaxLength()) {
        int32_t len = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
        showCountBorderStyle_ = len >
            static_cast<int32_t>(layoutProperty->GetMaxLengthValue(Infinity<uint32_t>()));
        HandleCountStyle();
    }
    auto start = GetPreviewTextStart();
    auto end = GetPreviewTextEnd();
    auto previewValue = GetPreviewTextValue();
    hasPreviewText_ = false;
    auto originLength = static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) - (end - start);
    contentController_->ReplaceSelectedValue(start, end, previewValue);
    int32_t caretMoveLength = abs(static_cast<int32_t>(contentController_->GetTextUtf16Value().length()) -
        originLength);
    selectController_->UpdateCaretIndex(start + caretMoveLength);
    UpdateEditingValueToRecord();
    if (HasFocus()) {
        cursorVisible_ = true;
        StartTwinkling();
    } else {
        cursorVisible_ = false;
        StopTwinkling();
    }
    bodyTextInPreivewing_ = u"";
    previewTextStart_ = PREVIEW_TEXT_RANGE_DEFAULT;
    previewTextEnd_ = PREVIEW_TEXT_RANGE_DEFAULT;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

std::vector<RectF> TextFieldPattern::GetPreviewTextRects() const
{
    if (!GetIsPreviewText()) {
        return {};
    }
    std::vector<RectF> boxes;
    std::vector<RectF> previewTextRects;
    CHECK_NULL_RETURN(paragraph_, boxes);
    paragraph_->GetRectsForRange(GetPreviewTextStart(), GetPreviewTextEnd(), boxes);
    if (boxes.empty()) {
        return {};
    }
    RectF linerRect(boxes.front().GetOffset(), SizeF(0, boxes.front().GetSize().Height()));
    float checkedTop = boxes.front().Top();

    for (const auto& drawRect : boxes) {
        if (drawRect.Top() == checkedTop) {
            linerRect += SizeF(drawRect.GetSize().Width(), 0);
        } else {
            previewTextRects.emplace_back(linerRect);
            checkedTop = drawRect.Top();
            linerRect = drawRect;
        }
    }
    previewTextRects.emplace_back(linerRect);
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
        if (!paintStart.has_value() || !paintEnd.has_value()) {
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

int32_t TextFieldPattern::CheckPreviewTextValidate(const std::u16string& previewValue, const PreviewRange range)
{
    auto start = range.start;
    auto end = range.end;
    if (start != end && (start == PREVIEW_TEXT_RANGE_DEFAULT || end == PREVIEW_TEXT_RANGE_DEFAULT)) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "range is not [-1,-1] or legal range");
        return PREVIEW_BAD_PARAMETERS;
    }

    if (start != PREVIEW_TEXT_RANGE_DEFAULT && IsSelected()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "unsupported insert preview text when IsSelected");
        return PREVIEW_BAD_PARAMETERS;
    }
    return PREVIEW_NO_ERROR;
}

int32_t TextFieldPattern::CheckPreviewTextValidate(const std::string& previewValue, const PreviewRange range)
{
    return CheckPreviewTextValidate(UtfUtils::Str8ToStr16(previewValue), range);
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
    float offsetY = IsTextArea() ? GetTextRect().GetY() : contentRect_.GetY();
    std::vector<RectF> previewTextRects = GetPreviewTextRects();
    if (GreatNotEqual(touchOffset.GetY(), previewTextRects.back().Bottom() + offsetY)) {
        limitL = previewTextRects.back().Left() + offsetX + MINIMAL_OFFSET;
        limitR = previewTextRects.back().Right() + offsetX - MINIMAL_OFFSET;
    } else if (LessNotEqual(touchOffset.GetY(), previewTextRects.front().Top() + offsetY)) {
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

void TextFieldPattern::ResetPreviewTextState()
{
    if (!GetIsPreviewText()) {
        return;
    }
#if defined(ENABLE_STANDARD_INPUT)
    MiscServices::InputMethodController::GetInstance()->OnSelectionChange(
        StringUtils::Str8ToStr16(""), 0, 0);
    UpdateCaretInfoToController(true);
#endif
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "textfield onDragEnter when has previewText");
    FinishTextPreview();
}

void TextFieldPattern::SetShowKeyBoardOnFocus(bool value)
{
    if (showKeyBoardOnFocus_ == value) {
        return;
    }
    showKeyBoardOnFocus_ = value;

    if (!HasFocus()) {
        return;
    }

    if (value) {
        RequestKeyboardNotByFocusSwitch(RequestKeyboardReason::SHOW_KEYBOARD_ON_FOCUS);
    } else {
        CloseKeyboard(true, false);
    }
}

void TextFieldPattern::OnCaretMoveDone(const TouchEventInfo& info)
{
    if (isMoveCaretAnywhere_) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "isMoveCaretAnywhere_=1, so restore caret");
        selectController_->UpdateCaretInfoByOffset(info.GetTouches().front().GetLocalLocation());
        StartTwinkling();
    }
}

void TextFieldPattern::HiddenMenu()
{
    selectOverlay_->HideMenu();
}

void TextFieldPattern::OnSelectionMenuOptionsUpdate(
    const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick)
{
    selectOverlay_->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

bool TextFieldPattern::GetTouchInnerPreviewText(const Offset& offset) const
{
    auto touchDownIndex = selectController_->ConvertTouchOffsetToPosition(offset);
    return GetPreviewTextStart() <= touchDownIndex && touchDownIndex <= GetPreviewTextEnd() && HasFocus();
}

bool TextFieldPattern::IsResponseRegionExpandingNeededForStylus(const TouchEvent& touchEvent) const
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
    return !IsInPasswordMode();
}

RectF TextFieldPattern::ExpandDefaultResponseRegion(RectF& rect)
{
    return rect + NG::SizeF(0, OHOS::Ace::HOT_AREA_ADJUST_SIZE.ConvertToPx() * OHOS::Ace::HOT_AREA_EXPAND_TIME) +
           NG::OffsetF(0, -OHOS::Ace::HOT_AREA_ADJUST_SIZE.ConvertToPx());
}

bool TextFieldPattern::IsContentRectNonPositive()
{
    return NonPositive(contentRect_.Width());
}

void TextFieldPattern::ReportEvent()
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    if (UiSessionManager::GetInstance().GetSearchEventRegistered()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto data = JsonUtil::Create();
        data->Put("event", "onTextSearch");
        data->Put("id", host->GetId());
        data->Put("$type", host->GetTag().data());
        data->Put("inputType", static_cast<int16_t>(GetKeyboard()));
        data->Put("text", GetTextValue().data());
        data->Put("position", host->GetGeometryNode()->GetFrameRect().ToString().data());
        // report all use textfield component unfocus event,more than just the search box
        UiSessionManager::GetInstance().ReportSearchEvent(data->ToString());
    }
#endif
}

int32_t TextFieldPattern::GetTouchIndex(const OffsetF& offset)
{
    return selectOverlay_->GetCaretPositionOnHandleMove(offset, true);
}

void TextFieldPattern::StartGestureSelection(int32_t start, int32_t end, const Offset& startOffset)
{
    TextGestureSelector::StartGestureSelection(start, end, startOffset);
    StopContentScroll();
    contentScroller_.scrollingCallback = [weak = WeakClaim(this), start, end](const Offset& localOffset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto index = pattern->GetTouchIndex({ localOffset.GetX(), localOffset.GetY() });
        auto startIndex = std::min(index, start);
        auto endIndex = std::max(index, end);
        pattern->UpdateSelectionByLongPress(startIndex, endIndex, localOffset);
    };
}

void TextFieldPattern::OnTextGestureSelectionUpdate(int32_t start, int32_t end, const TouchEventInfo& info)
{
    auto localOffset = info.GetTouches().front().GetLocalLocation();
    UpdateContentScroller(localOffset);
    if (contentScroller_.isScrolling) {
        return;
    }
    if (start != selectController_->GetStartIndex()) {
        StartVibratorByIndexChange(start, selectController_->GetStartIndex());
    } else if (end != selectController_->GetEndIndex()) {
        StartVibratorByIndexChange(end, selectController_->GetEndIndex());
    }
    UpdateSelectionByLongPress(start, end, localOffset);
}

void TextFieldPattern::UpdateSelectionByLongPress(int32_t start, int32_t end, const Offset& localOffset)
{
    if (magnifierController_ && HasText() && (longPressFingerNum_ == 1)) {
        contentScroller_.updateMagniferEpsilon = 0.0f - contentScroller_.updateMagniferEpsilon;
        magnifierController_->SetLocalOffset(
            { localOffset.GetX(), localOffset.GetY() + contentScroller_.updateMagniferEpsilon });
    }
    auto firstIndex = selectController_->GetFirstHandleIndex();
    auto secondIndex = selectController_->GetSecondHandleIndex();
    bool changed = false;
    if (start != firstIndex) {
        selectController_->MoveFirstHandleToContentRect(start, false, false);
        changed = true;
    }
    if (secondIndex != end) {
        selectController_->MoveSecondHandleToContentRect(end, false, false);
        changed = true;
    }
    if (!changed) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldPattern::OnTextGenstureSelectionEnd()
{
    SetIsSingleHandle(!IsSelected());
    if (!IsContentRectNonPositive()) {
        ProcessOverlay({ .animation = true });
    }
    StopContentScroll();
}

PositionWithAffinity TextFieldPattern::GetGlyphPositionAtCoordinate(int32_t x, int32_t y)
{
    PositionWithAffinity finalResult(0, TextAffinity::UPSTREAM);
    CHECK_NULL_RETURN(paragraph_, finalResult);
    Offset offset(x, y);
    return paragraph_->GetGlyphPositionAtCoordinate(ConvertTouchOffsetToTextOffset(offset));
}

Offset TextFieldPattern::ConvertTouchOffsetToTextOffset(const Offset& touchOffset)
{
    return touchOffset - Offset(textRect_.GetX(), textRect_.GetY());
}

bool TextFieldPattern::InsertOrDeleteSpace(int32_t index)
{
    // delete or insert space.
    auto wtext = GetTextUtf16Value();
    if (index >= 0 && index < static_cast<int32_t>(wtext.length())) {
        auto ret = SetCaretOffset(index);
        if (!ret) {
            return false;
        }
        if (wtext[index] == u' ') {
            DeleteForward(1);
        } else if (index > 0 && wtext[index - 1] == u' ') {
            DeleteBackward(1);
        } else {
            InsertValue(u" ", true);
        }
        return true;
    }
    return false;
}

void TextFieldPattern::DeleteRange(int32_t start, int32_t end)
{
    auto length = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    if (start > end) {
        std::swap(start, end);
    }
    start = std::max(0, start);
    end = std::min(length, end);
    if (start > length || end < 0 || start == end) {
        return;
    }
    GetEmojiSubStringRange(start, end);
    auto value = contentController_->GetSelectedValue(start, end);
    auto isDelete = BeforeIMEDeleteValue(value, TextDeleteDirection::FORWARD, start);
    CHECK_NULL_VOID(isDelete);
    ResetObscureTickCountDown();
    CheckAndUpdateRecordBeforeOperation();
    Delete(start, end);
    AfterIMEDeleteValue(value, TextDeleteDirection::FORWARD);
    showCountBorderStyle_ = false;
    HandleCountStyle();
}

bool TextFieldPattern::IsShowAIWrite()
{
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        return false;
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    if (layoutProperty->GetCopyOptionsValue(CopyOptions::Local) == CopyOptions::None ||
        !IsUnspecifiedOrTextType()) {
        return false;
    }

    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, false);
    auto bundleName = textFieldTheme->GetAIWriteBundleName();
    auto abilityName = textFieldTheme->GetAIWriteAbilityName();
    if (bundleName.empty() || abilityName.empty()) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "Failed to obtain AI write package name!");
        return false;
    }
    aiWriteAdapter_->SetBundleName(bundleName);
    aiWriteAdapter_->SetAbilityName(abilityName);

    auto isAISupport = false;
    if (textFieldTheme->GetAIWriteIsSupport() == "true") {
        isAISupport = true;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Whether the device supports AI write: %{public}d, nodeId: %{public}d",
        isAISupport, host->GetId());
    return isAISupport;
}

void TextFieldPattern::GetAIWriteInfo(AIWriteInfo& info)
{
    // serialize the selected text
    info.selectStart = selectController_->GetStartIndex();
    info.selectEnd = selectController_->GetEndIndex();
    auto selectContent = contentController_->GetSelectedValue(info.selectStart, info.selectEnd);
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(selectContent);
    spanString->EncodeTlv(info.selectBuffer);
    info.selectLength = static_cast<int32_t>(aiWriteAdapter_->GetSelectLengthOnlyText(spanString->GetU16string()));
    TAG_LOGD(AceLogTag::ACE_TEXT_FIELD, "Selected range=[%{public}d--%{public}d], content = %{private}s",
        info.selectStart, info.selectEnd, spanString->GetString().c_str());

    // serialize the sentenced-level text
    auto textSize = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
    auto contentAll = contentController_->GetTextUtf16Value();
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
    auto sentenceContent = contentController_->GetSelectedValue(sentenceStart, sentenceEnd);
    spanString = AceType::MakeRefPtr<SpanString>(sentenceContent);
    spanString->EncodeTlv(info.sentenceBuffer);
    TAG_LOGD(AceLogTag::ACE_TEXT_FIELD, "Sentence range=[%{public}d--%{public}d], content = %{private}s",
        sentenceStart, sentenceEnd, spanString->GetString().c_str());

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    info.maxLength = static_cast<int32_t>(layoutProperty->GetMaxLengthValue(Infinity<uint32_t>()));
    info.firstHandle = selectController_->GetFirstHandleRect().ToString();
    info.secondHandle = selectController_->GetSecondHandleRect().ToString();
    info.componentType = host->GetTag();
}

void TextFieldPattern::HandleOnAIWrite()
{
    AIWriteInfo info;
    GetAIWriteInfo(info);
    CloseSelectOverlay();
    CloseKeyboard(true);

    auto callback = [weak = WeakClaim(this), info](std::vector<uint8_t>& buffer) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleAIWriteResult(info.selectStart, info.selectEnd, buffer);
        auto aiWriteAdapter = pattern->aiWriteAdapter_;
        CHECK_NULL_VOID(aiWriteAdapter);
        aiWriteAdapter->CloseModalUIExtension();
    };
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    aiWriteAdapter_->SetPipelineContext(pipeline);
    aiWriteAdapter_->ShowModalUIExtension(info, callback);
}

void TextFieldPattern::HandleAIWriteResult(int32_t start, int32_t end, std::vector<uint8_t>& buffer)
{
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(buffer);
    auto resultText = spanString->GetU16string();
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "Backfilling results range=[%{public}d--%{public}d], content = %{private}s",
        start, end, spanString->GetString().c_str());
    if (spanString->GetSpanItems().empty()) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto value = contentController_->GetSelectedValue(start, end);
    BeforeIMEDeleteValue(value, TextDeleteDirection::FORWARD, start);
    BeforeIMEInsertValue(resultText, start);
    contentController_->ReplaceSelectedValue(start, end, resultText);
    AfterIMEDeleteValue(value, TextDeleteDirection::FORWARD);
    AfterIMEInsertValue(resultText);
    CloseSelectOverlay(true);
    SetCaretPosition(start + spanString->GetLength());
    StartTwinkling();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}

bool TextFieldPattern::IsTextEditableForStylus() const
{
    CHECK_NULL_RETURN(!HasCustomKeyboard(), false);
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
    return !IsInPasswordMode();
}

void TextFieldPattern::UpdateContentScroller(const Offset& localOffset)
{
    auto scrollStep = CalcAutoScrollStepOffset(localOffset);
    // 在热区外移动
    if (!scrollStep || (!GetScrollEnabled() && !moveCaretState_.isMoveCaret)) {
        contentScroller_.OnBeforeScrollingCallback(localOffset);
        PauseContentScroll();
        contentScroller_.hotAreaOffset.reset();
        return;
    }
    contentScroller_.stepOffset = scrollStep.value();
    contentScroller_.localOffset = localOffset;
    if (contentScroller_.isScrolling) {
        return;
    }
    contentScroller_.OnBeforeScrollingCallback(localOffset);
    if (!contentScroller_.hotAreaOffset) {
        contentScroller_.hotAreaOffset = localOffset;
        ScheduleContentScroll(AUTO_SCROLL_HOT_AREA_LONGPRESS_DURATION);
    } else {
        auto hotAreaMoveDistance = (localOffset - contentScroller_.hotAreaOffset.value()).GetDistance();
        if (GreatOrEqual(hotAreaMoveDistance, AUTO_SCROLL_HOT_AREA_LONGPRESS_DISTANCE.ConvertToPx())) {
            contentScroller_.hotAreaOffset = localOffset;
            contentScroller_.autoScrollTask.Cancel();
            ScheduleContentScroll(AUTO_SCROLL_HOT_AREA_LONGPRESS_DURATION);
        }
    }
}

std::optional<float> TextFieldPattern::CalcAutoScrollStepOffset(const Offset& localOffset)
{
    auto contentRect = GetContentRect();
    auto axis = GetAxis();
    auto isVertical = (axis == Axis::VERTICAL);
    auto hotArea = isVertical ? AUTO_SCROLL_HOT_ZONE_HEIGHT.ConvertToPx() : AUTO_SCROLL_HOT_ZONE_WIDTH.ConvertToPx();
    if (isVertical) {
        if (LessOrEqual(contentRect.Height(), hotArea)) {
            hotArea = contentRect.Height() / 3.0f;
        }
    } else {
        if (LessOrEqual(contentRect.Width(), hotArea)) {
            hotArea = contentRect.Width() / 3.0f;
        }
    }
    struct HotEdge {
        float start = 0.0f;
        float end = 0.0f;
        float scrollDirection = 1.0f;
    };
    std::vector<HotEdge> hotEdges = { { contentRect.Top() + hotArea, contentRect.Top(), 1.0f },
        { contentRect.Bottom() - hotArea, contentRect.Bottom(), -1.0f },
        { contentRect.Left() + hotArea, contentRect.Left(), 1.0f },
        { contentRect.Right() - hotArea, contentRect.Right(), -1.0f } };
    auto itStart = isVertical ? hotEdges.begin() : hotEdges.begin() + 2;
    auto point = isVertical ? localOffset.GetY() : localOffset.GetX();
    std::optional<float> scrollStep;
    for (auto it = itStart; it != (itStart + 2); ++it) {
        auto speed = CalcScrollSpeed(it->start, it->end, point);
        if (!NearZero(speed)) {
            scrollStep = speed * it->scrollDirection;
            break;
        }
    }
    return scrollStep;
}

float TextFieldPattern::CalcScrollSpeed(float hotAreaStart, float hotAreaEnd, float point)
{
    auto minHotArea = std::min(hotAreaStart, hotAreaEnd);
    auto maxHotArea = std::max(hotAreaStart, hotAreaEnd);
    if (GreatNotEqual(point, minHotArea) && LessNotEqual(point, maxHotArea)) {
        auto distanceRatio = (point - hotAreaStart) / (hotAreaEnd - hotAreaStart);
        auto speedFactor = Curves::SHARP->MoveInternal(distanceRatio);
        return ((MAX_DRAG_SCROLL_SPEED * speedFactor) / TIME_UNIT) * contentScroller_.scrollInterval;
    }
    return 0.0f;
}

void TextFieldPattern::StopContentScroll()
{
    PauseContentScroll();
    contentScroller_.scrollingCallback = nullptr;
    contentScroller_.beforeScrollingCallback = nullptr;
}

void TextFieldPattern::PauseContentScroll()
{
    contentScroller_.autoScrollTask.Cancel();
    contentScroller_.isScrolling = false;
    ScheduleDisappearDelayTask();
}

void TextFieldPattern::ScheduleContentScroll(float delay)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    contentScroller_.autoScrollTask.Reset([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->contentScroller_.isScrolling = true;
        pattern->contentScroller_.hotAreaOffset = std::nullopt;
        pattern->OnScrollCallback(pattern->contentScroller_.stepOffset, SCROLL_FROM_UPDATE);
        if (pattern->contentScroller_.scrollingCallback) {
            pattern->contentScroller_.scrollingCallback(pattern->contentScroller_.localOffset);
        }
        pattern->ScheduleContentScroll(pattern->contentScroller_.scrollInterval);
    });
    taskExecutor->PostDelayedTask(contentScroller_.autoScrollTask, TaskExecutor::TaskType::UI, delay,
        "ArkUIAutoScrollControllerScheduleAutoScroll");
}

void TextFieldPattern::SetDragMovingScrollback()
{
    StopContentScroll();
    contentScroller_.scrollingCallback = [weak = WeakClaim(this)](const Offset& localOffset) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<TextFieldTheme>();
        CHECK_NULL_VOID(theme);
        Offset offset = localOffset - Offset(pattern->textRect_.GetX(), pattern->textRect_.GetY()) -
                        Offset(0, theme->GetInsertCursorOffset().ConvertToPx());
        auto position = pattern->ConvertTouchOffsetToCaretPosition(offset);
        pattern->SetCaretPosition(position, false);
        pattern->ShowCaretAndStopTwinkling();
    };
    contentScroller_.beforeScrollingCallback = contentScroller_.scrollingCallback;
}

void TextFieldPattern::OnAttachToMainTree()
{
    isDetachFromMainTree_ = false;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto autoFillContainerNode = host->GetFirstAutoFillContainerNode();
    CHECK_NULL_VOID(autoFillContainerNode);
    firstAutoFillContainerNode_ = WeakClaim(RawPtr(autoFillContainerNode));
    AddTextFieldInfo();
}

void TextFieldPattern::OnDetachFromMainTree()
{
    isDetachFromMainTree_ = true;
    RemoveTextFieldInfo();
}

TextFieldInfo TextFieldPattern::GenerateTextFieldInfo()
{
    TextFieldInfo textFieldInfo;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, textFieldInfo);
    textFieldInfo.nodeId = host->GetId();
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    CHECK_NULL_RETURN(autoFillContainerNode, textFieldInfo);
    textFieldInfo.autoFillContainerNodeId = autoFillContainerNode->GetId();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, textFieldInfo);
    textFieldInfo.enableAutoFill = layoutProperty->GetEnableAutoFillValue(true);
    textFieldInfo.inputType = layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED);
    textFieldInfo.contentType = layoutProperty->GetTextContentTypeValue(TextContentType::UNSPECIFIED);
    return textFieldInfo;
}

void TextFieldPattern::AddTextFieldInfo()
{
    CHECK_NULL_VOID(IsNeedProcessAutoFill());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    auto textFieldInfo = GenerateTextFieldInfo();
    textFieldManager->AddTextFieldInfo(textFieldInfo);
}

void TextFieldPattern::RemoveTextFieldInfo()
{
    CHECK_NULL_VOID(IsNeedProcessAutoFill());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    auto nodeId = host->GetId();
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    CHECK_NULL_VOID(autoFillContainerNode);
    auto autoFillContainerNodeId = autoFillContainerNode->GetId();
    textFieldManager->RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
}

void TextFieldPattern::UpdateTextFieldInfo()
{
    CHECK_NULL_VOID(IsNeedProcessAutoFill());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    auto textFieldInfo = GenerateTextFieldInfo();
    textFieldManager->UpdateTextFieldInfo(textFieldInfo);
}

bool TextFieldPattern::IsAutoFillUserName(const AceAutoFillType& autoFillType)
{
    auto isUserName =
        autoFillType == AceAutoFillType::ACE_USER_NAME || autoFillType == AceAutoFillType::ACE_UNSPECIFIED;
    return isUserName && HasAutoFillPasswordNode();
}

bool TextFieldPattern::HasAutoFillPasswordNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_RETURN(textFieldManager, false);
    auto nodeId = host->GetId();
    auto autoFillContainerNode = firstAutoFillContainerNode_.Upgrade();
    CHECK_NULL_RETURN(autoFillContainerNode, false);
    auto autoFillContainerNodeId = autoFillContainerNode->GetId();
    return textFieldManager->HasAutoFillPasswordNodeInContainer(autoFillContainerNodeId, nodeId);
}

bool TextFieldPattern::IsTriggerAutoFillPassword()
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto aceContentType =
        TextContentTypeToAceAutoFillType(layoutProperty->GetTextContentTypeValue(TextContentType::UNSPECIFIED));
    if (aceContentType != AceAutoFillType::ACE_UNSPECIFIED) {
        if (!IsAutoFillPasswordType(aceContentType)) {
            return false;
        } else {
            if (aceContentType == AceAutoFillType::ACE_PASSWORD ||
                aceContentType == AceAutoFillType::ACE_NEW_PASSWORD) {
                return true;
            }
            return HasAutoFillPasswordNode();
        }
    }

    auto aceInputType = ConvertToAceAutoFillType(layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED));
    if (aceInputType != AceAutoFillType::ACE_UNSPECIFIED) {
        if (aceInputType == AceAutoFillType::ACE_PASSWORD || aceInputType == AceAutoFillType::ACE_NEW_PASSWORD) {
            return true;
        }
    }
    return HasAutoFillPasswordNode();
}

bool TextFieldPattern::IsNeedProcessAutoFill()
{
    return true;
}

std::vector<RectF> TextFieldPattern::GetTextBoxesForSelect()
{
    auto selectedRects = GetTextBoxes();
    CHECK_NULL_RETURN(paragraph_, selectedRects);
    auto paragraphStyle = paragraph_->GetParagraphStyle();
    auto textAlign = TextBase::CheckTextAlignByDirection(paragraphStyle.align, paragraphStyle.direction);
    const float blankWidth = TextBase::GetSelectedBlankLineWidth();
    auto contentWidth = GetTextContentRect().Width();
    TextBase::CalculateSelectedRectEx(selectedRects, -1.0f);
    for (auto& rect : selectedRects) {
        TextBase::UpdateSelectedBlankLineRect(rect, blankWidth, textAlign, contentWidth);
    }
    return selectedRects;
}

std::optional<TouchLocationInfo> TextFieldPattern::GetAcceptedTouchLocationInfo(const TouchEventInfo& info)
{
    auto touchInfos = info.GetChangedTouches();
    if (touchInfos.empty()) {
        return std::nullopt;
    }
    if (!moveCaretState_.isMoveCaret && !IsGestureSelectingText()) {
        return touchInfos.front();
    }
    auto fingerId = moveCaretState_.isMoveCaret ? moveCaretState_.touchFingerId : GetSelectingFingerId();
    for (auto touchInfo : touchInfos) {
        if (touchInfo.GetFingerId() == fingerId) {
            return touchInfo;
        }
    }
    return std::nullopt;
}

void TextFieldPattern::DoTextSelectionTouchCancel()
{
    CHECK_NULL_VOID(magnifierController_);
    magnifierController_->RemoveMagnifierFrameNode();
    selectController_->UpdateCaretIndex(selectController_->GetCaretIndex());
    StopContentScroll();
}

float TextFieldPattern::GetVerticalPaddingAndBorderSum() const
{
    auto border = GetBorderWidthProperty();
    if (utilPadding_.has_value()) {
        return utilPadding_.value().top.value_or(0.0f) + utilPadding_.value().bottom.value_or(0.0f) +
               GetBorderTop(border) + GetBorderBottom(border);
    }
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, themePadding.Top().ConvertToPx() + themePadding.Bottom().ConvertToPx());
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(paddingProperty, themePadding.Top().ConvertToPx() + themePadding.Bottom().ConvertToPx());

    auto result = static_cast<float>(
        paddingProperty->top.value_or(CalcLength(themePadding.Top())).GetDimension().ConvertToPx() +
        paddingProperty->bottom.value_or(CalcLength(themePadding.Bottom())).GetDimension().ConvertToPx());
    return result + GetBorderTop(border) + GetBorderBottom(border);
}

float TextFieldPattern::GetHorizontalPaddingAndBorderSum() const
{
    auto border = GetBorderWidthProperty();
    if (utilPadding_.has_value()) {
        return utilPadding_.value().left.value_or(0.0f) + utilPadding_.value().right.value_or(0.0f) +
               GetBorderLeft(border) + GetBorderRight(border);
    }
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, themePadding.Left().ConvertToPx() + themePadding.Right().ConvertToPx());
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(paddingProperty, themePadding.Left().ConvertToPx() + themePadding.Right().ConvertToPx());
    auto padding = static_cast<float>(
        paddingProperty->left.value_or(CalcLength(themePadding.Left())).GetDimension().ConvertToPx() +
        paddingProperty->right.value_or(CalcLength(themePadding.Right())).GetDimension().ConvertToPx());
    return padding + GetBorderLeft(border) + GetBorderRight(border);
}

float TextFieldPattern::GetPaddingTop() const
{
    if (utilPadding_.has_value()) {
        return utilPadding_.value().top.value_or(0.0f);
    }
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, themePadding.Top().ConvertToPx());
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(paddingProperty, themePadding.Top().ConvertToPx());
    return static_cast<float>(
        paddingProperty->top.value_or(CalcLength(themePadding.Top())).GetDimension().ConvertToPx());
}

float TextFieldPattern::GetPaddingBottom() const
{
    if (utilPadding_.has_value()) {
        return utilPadding_.value().bottom.value_or(0.0f);
    }
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, themePadding.Bottom().ConvertToPx());
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(paddingProperty, themePadding.Bottom().ConvertToPx());
    return static_cast<float>(
        paddingProperty->bottom.value_or(CalcLength(themePadding.Bottom())).GetDimension().ConvertToPx());
}

float TextFieldPattern::GetPaddingLeft() const
{
    if (utilPadding_.has_value()) {
        return utilPadding_.value().left.value_or(0.0f);
    }
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, themePadding.Left().ConvertToPx());
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(paddingProperty, themePadding.Left().ConvertToPx());
    return static_cast<float>(
        paddingProperty->left.value_or(CalcLength(themePadding.Left())).GetDimension().ConvertToPx());
}

float TextFieldPattern::GetPaddingRight() const
{
    if (utilPadding_.has_value()) {
        return utilPadding_.value().right.value_or(0.0f);
    }
    auto textFieldTheme = GetTheme();
    CHECK_NULL_RETURN(textFieldTheme, 0.0f);
    auto themePadding = IsUnderlineMode() ? textFieldTheme->GetUnderlinePadding() : textFieldTheme->GetPadding();
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, themePadding.Right().ConvertToPx());
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_RETURN(paddingProperty, themePadding.Right().ConvertToPx());
    return static_cast<float>(
        paddingProperty->right.value_or(CalcLength(themePadding.Right())).GetDimension().ConvertToPx());
}

BorderWidthProperty TextFieldPattern::GetBorderWidthProperty() const
{
    BorderWidthProperty currentBorderWidth;
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, currentBorderWidth);
    if (layoutProperty->GetBorderWidthProperty() != nullptr) {
        currentBorderWidth = *(layoutProperty->GetBorderWidthProperty());
    } else {
        currentBorderWidth.SetBorderWidth(BORDER_DEFAULT_WIDTH);
    }
    return currentBorderWidth;
}

float TextFieldPattern::GetBorderLeft(BorderWidthProperty border) const
{
    auto leftBorderWidth = border.leftDimen.value_or(Dimension(0.0f));
    auto percentReferenceWidth = GetPercentReferenceWidth();
    if (leftBorderWidth.Unit() == DimensionUnit::PERCENT && percentReferenceWidth > 0) {
        return leftBorderWidth.Value() * percentReferenceWidth;
    }
    return leftBorderWidth.ConvertToPx();
}

float TextFieldPattern::GetBorderTop(BorderWidthProperty border) const
{
    auto topBorderWidth = border.topDimen.value_or(Dimension(0.0f));
    auto percentReferenceWidth = GetPercentReferenceWidth();
    if (topBorderWidth.Unit() == DimensionUnit::PERCENT && percentReferenceWidth > 0) {
        return topBorderWidth.Value() * percentReferenceWidth;
    }
    return topBorderWidth.ConvertToPx();
}

float TextFieldPattern::GetBorderBottom(BorderWidthProperty border) const
{
    auto bottomBorderWidth = border.bottomDimen.value_or(Dimension(0.0f));
    auto percentReferenceWidth = GetPercentReferenceWidth();
    if (bottomBorderWidth.Unit() == DimensionUnit::PERCENT && percentReferenceWidth > 0) {
        return bottomBorderWidth.Value() * percentReferenceWidth;
    }
    return bottomBorderWidth.ConvertToPx();
}

float TextFieldPattern::GetBorderRight(BorderWidthProperty border) const
{
    auto rightBorderWidth = border.rightDimen.value_or(Dimension(0.0f));
    auto percentReferenceWidth = GetPercentReferenceWidth();
    if (rightBorderWidth.Unit() == DimensionUnit::PERCENT && percentReferenceWidth > 0) {
        return rightBorderWidth.Value() * percentReferenceWidth;
    }
    return rightBorderWidth.ConvertToPx();
}

void TextFieldPattern::ResetFirstClickAfterGetFocus()
{
    if (!firstClickAfterLosingFocus_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    firstClickResetTask_.Cancel();
    firstClickResetTask_.Reset([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->firstClickAfterLosingFocus_ = false;
    });
    taskExecutor->PostDelayedTask(
        firstClickResetTask_, TaskExecutor::TaskType::UI, TWINKLING_INTERVAL_MS, "ResetFirstClickAfterGetFocusTask");
}
} // namespace OHOS::Ace::NG
