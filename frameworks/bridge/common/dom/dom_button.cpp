/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/common/dom/dom_button.h"

#include "base/log/event_report.h"
#include "core/common/ace_application_info.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {

// Button types definition
const char BUTTON_TYPE_CAPSULE[] = "capsule";
const char BUTTON_TYPE_TEXT[] = "text";
const char BUTTON_TYPE_CIRCLE[] = "circle";
const char BUTTON_TYPE_DOWNLOAD[] = "download";
const char BUTTON_TYPE_ICON[] = "icon";
const char BUTTON_TYPE_ARC[] = "arc"; // for watch

// Button children placement definition
const char PLACEMENT_START[] = "start";
const char PLACEMENT_TOP[] = "top";
const char PLACEMENT_BOTTOM[] = "bottom";

// Watch button definitions
constexpr Dimension ARC_FONT_SIZE = 19.0_fp;
constexpr Dimension ARC_FONT_MIN_SIZE = 16.0_fp;
constexpr Dimension ARC_PADDING_TOP = 8.0_vp;
constexpr Dimension ARC_PADDING_BOTTOM = 0.0_vp;
constexpr Dimension ARC_PADDING_HORIZONTAL = 30.0_vp;
constexpr Dimension WATCH_TEXT_PADDING = 2.0_vp;
constexpr Dimension WATCH_TEXT_RADIUS = 4.0_vp;
constexpr uint32_t MAX_LINES = 2;

// TV button definitions
constexpr Dimension TEXT_PADDING_HORIZONTAL = 8.0_vp;
constexpr Dimension TEXT_PADDING_VERTICAL = 0.0_vp;
constexpr Dimension TEXT_FONT_MIN_SIZE = 12.0_fp;
constexpr double TEXT_FOCUS_HEIGHT = 24.0;

constexpr uint32_t TRANSPARENT_COLOR = 0x00000000;
constexpr uint32_t METHOD_SET_PROGRESS_ARGS_SIZE = 1;
constexpr double FLEX_ITEM_SHRINK = 1.0;
constexpr double INIT_HEIGHT = -1.0;
constexpr Dimension DOWNLOAD_BORDER_WIDTH = Dimension(1.0, DimensionUnit::VP);
constexpr Dimension ICON_BUTTON_PADDING = 0.0_vp;
constexpr Dimension ICON_BUTTON_RADIUS = 0.0_vp;
constexpr Dimension INNER_PADDING = 4.0_vp;

} // namespace

void DOMButton::ResetInitializedStyle()
{
    buttonTheme_ = GetTheme<ButtonTheme>();
    if (!buttonTheme_) {
        return;
    }
    paddingChild_->SetPadding(buttonTheme_->GetPadding());
    blendOpacity_ = buttonTheme_->GetBgDisabledAlpha();
    edge_.SetColor(buttonTheme_->GetDownloadBorderColor());
    progressColor_ = buttonTheme_->GetProgressColor();
    diameter_ = buttonTheme_->GetProgressDiameter();
    innerLeftPadding_ = buttonTheme_->GetInnerPadding();
    InitButtonStyle();
    InitTextStyle();
}

DOMButton::DOMButton(NodeId nodeId, const std::string& nodeName) : DOMNode(nodeId, nodeName)
{
    std::list<RefPtr<Component>> buttonChildren;
    buttonChild_ = AceType::MakeRefPtr<ButtonComponent>(buttonChildren);
    textChild_ = AceType::MakeRefPtr<TextComponent>("");
    imageChild_ = AceType::MakeRefPtr<ImageComponent>("");
    paddingChild_ = AceType::MakeRefPtr<PaddingComponent>();
    buttonChild_->AppendChild(paddingChild_);
    isWatch_ = (SystemProperties::GetDeviceType() == DeviceType::WATCH);
    isTv_ = (SystemProperties::GetDeviceType() == DeviceType::TV);
    if (IsRightToLeft()) {
        textChild_->SetTextDirection(TextDirection::RTL);
        imageChild_->SetTextDirection(TextDirection::RTL);
    }
}

void DOMButton::InitializeStyle()
{
    ResetInitializedStyle();
}

void DOMButton::InitButtonStyle()
{
    if (!buttonChild_) {
        return;
    }
    buttonChild_->SetLayoutFlag(LAYOUT_FLAG_EXTEND_TO_PARENT);
    buttonChild_->SetRectRadius(buttonTheme_->GetRadius());
    buttonChild_->SetMinWidth(buttonTheme_->GetMinWidth());
    buttonChild_->SetBackgroundColor(buttonTheme_->GetBgColor());
    buttonChild_->SetClickedColor(buttonTheme_->GetClickedColor());
    buttonChild_->SetFocusColor(buttonTheme_->GetBgFocusColor());
    buttonChild_->SetHoverColor(buttonTheme_->GetHoverColor());
    buttonChild_->SetFocusAnimationColor(buttonTheme_->GetBgFocusColor());
    buttonChild_->SetProgressFocusColor(buttonTheme_->GetProgressFocusColor());
}

void DOMButton::InitTextStyle()
{
    textStyle_ = buttonTheme_->GetTextStyle();
    textStyle_.SetAdaptTextSize(textStyle_.GetFontSize(), buttonTheme_->GetMinFontSize());
    textStyle_.SetMaxLines(buttonTheme_->GetTextMaxLines());
    textStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);
    textStyle_.SetTextAlign(TextAlign::LEFT);
    if (textChild_) {
        textChild_->SetTextStyle(textStyle_);
        textChild_->SetFocusColor(buttonTheme_->GetTextFocusColor());
    }
}

bool DOMButton::SetSpecializedAttr(const std::pair<std::string, std::string>& attr)
{
    static const LinearMapNode<void (*)(DOMButton&, const std::string&)> buttonAttrOperators[] = {
        { DOM_BUTTON_AUTO_FOCUS,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetAutoFocusState(StringToBool(value));
            } },
        { DOM_DISABLED, [](DOMButton& button,
                    const std::string& value) { button.buttonChild_->SetDisabledState(StringToBool(value)); } },
        { DOM_BUTTON_ICON, [](DOMButton& button, const std::string& value) { button.imageChild_->SetSrc(value); } },
        { DOM_PLACEMENT, [](DOMButton& button, const std::string& value) { button.placement_ = value; } },
        { DOM_BUTTON_TYPE, [](DOMButton& button, const std::string& value) { button.buttonType_ = value; } },
        { DOM_BUTTON_TEXT_DATA,
            [](DOMButton& button, const std::string& value) { button.textChild_->SetData(value); } },
        { DOM_BUTTON_WAITING,
            [](DOMButton& button, const std::string& value) { button.isWaiting_ = StringToBool(value); } },
    };
    auto operatorIter = BinarySearchFindIndex(buttonAttrOperators, ArraySize(buttonAttrOperators), attr.first.c_str());
    if (operatorIter != -1) {
        LOGD("Button attrs : %{public}s = %{public}s", attr.first.c_str(), attr.second.c_str());
        buttonAttrOperators[operatorIter].value(*this, attr.second);
        return true;
    }
    return false;
}

bool DOMButton::SetSpecializedStyle(const std::pair<std::string, std::string>& style)
{
    // Static linear map should be sorted by key.
    const static LinearMapNode<void (*)(DOMButton&, const std::string&)> buttonStyleOperators[] = {
        { DOM_TEXT_ALLOW_SCALE,
            [](DOMButton& button, const std::string& value) { button.textStyle_.SetAllowScale(StringToBool(value)); } },
        { DOM_BUTTON_DEFAULT_COLOR,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetBackgroundColor(button.ParseColor(value));
                button.bgColorDefined_ = true;
            } },
        { DOM_BUTTON_BORDER_COLOR,
            [](DOMButton& button, const std::string& value) { button.edge_.SetColor(button.ParseColor(value)); } },
        { DOM_BUTTON_BORDER_WIDTH,
            [](DOMButton& button, const std::string& value) { button.edge_.SetWidth(button.ParseDimension(value)); } },
        { DOM_BUTTON_ICON_DIRECTION,
            [](DOMButton& button, const std::string& value) {
                button.imageChild_->SetMatchTextDirection(StringToBool(value));
            } },
        { DOM_BUTTON_CLICKED_COLOR,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetClickedColor(button.ParseColor(value));
            } },
        { DOM_BUTTON_PROGRESS_DIAMETER,
            [](DOMButton& button, const std::string& value) { button.diameter_ = button.ParseDimension(value); } },
        { DOM_BUTTON_DISABLE_COLOR,
            [](DOMButton& button, const std::string& value) { button.disabledColor_ = button.ParseColor(value); } },
        { DOM_BUTTON_TEXT_DISABLE_COLOR,
            [](DOMButton& button, const std::string& value) { button.disabledTextColor_ = button.ParseColor(value); } },
        { DOM_BUTTON_FOCUS_COLOR,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetFocusColor(button.ParseColor(value));
            } },
        { DOM_BUTTON_FONT_FAMILY,
            [](DOMButton& button, const std::string& value) {
                button.textStyle_.SetFontFamilies(button.ParseFontFamilies(value));
            } },
        { DOM_BUTTON_FONT_SIZE,
            [](DOMButton& button, const std::string& value) {
                button.textStyle_.SetFontSize(button.ParseDimension(value));
                button.fontSizeDefined_ = true;
            } },
        { DOM_BUTTON_FONT_STYLE,
            [](DOMButton& button, const std::string& value) {
                button.textStyle_.SetFontStyle(ConvertStrToFontStyle(value));
            } },
        { DOM_BUTTON_FONT_WEIGHT,
            [](DOMButton& button, const std::string& value) {
                button.textStyle_.SetFontWeight(ConvertStrToFontWeight(value));
            } },
        { DOM_BUTTON_HEIGHT,
            [](DOMButton& button, const std::string& value) {
                button.SetHeight(button.ParseDimension(value));
                button.buttonChild_->SetHeight(button.ParseDimension(value));
                button.heightDefined_ = true;
            } },
        { DOM_BUTTON_ICON_HEIGHT,
            [](DOMButton& button, const std::string& value) {
                button.imageChild_->SetHeight(button.ParseDimension(value));
            } },
        { DOM_BUTTON_ICON_WIDTH,
            [](DOMButton& button, const std::string& value) {
                button.imageChild_->SetWidth(button.ParseDimension(value));
            } },
        { DOM_BUTTON_INNER_PADDING,
            [](DOMButton& button, const std::string& value) {
                button.innerLeftPadding_ = button.ParseDimension(value);
            } },
        { DOM_BUTTON_MIN_WIDTH,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetMinWidth(button.ParseDimension(value));
            } },
        { DOM_BUTTON_PROGRESS_COLOR,
            [](DOMButton& button, const std::string& value) { button.progressColor_ = button.ParseColor(value); } },
        { DOM_BUTTON_PROGRESS_FOCUS_COLOR,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetProgressFocusColor(button.ParseColor(value));
            } },
        { DOM_BUTTON_RRECT_RADIUS,
            [](DOMButton& button, const std::string& value) {
                button.buttonChild_->SetRectRadius(button.ParseDimension(value));
                button.radiusDefined_ = true;
            } },
        { DOM_BUTTON_TEXT_COLOR,
            [](DOMButton& button, const std::string& value) {
                button.textStyle_.SetTextColor(button.ParseColor(value));
                button.textColorDefined_ = true;
            } },
        { DOM_BUTTON_WIDTH,
            [](DOMButton& button, const std::string& value) {
                auto width = button.ParseDimension(value);
                button.SetWidth(width);
                button.buttonChild_->SetWidth(width);
            } },
    };
    auto operatorIter =
        BinarySearchFindIndex(buttonStyleOperators, ArraySize(buttonStyleOperators), style.first.c_str());
    if (operatorIter != -1) {
        LOGD("Button styles : %{public}s = %{public}s", style.first.c_str(), style.second.c_str());
        buttonStyleOperators[operatorIter].value(*this, style.second);
        return true;
    }
    return false;
}

bool DOMButton::AddSpecializedEvent(int32_t pageId, const std::string& event)
{
    // Note! this map should be sorted by key.
    static const LinearMapNode<void (*)(DOMButton&, const EventMarker&)> buttonEventOperators[] = {
        { DOM_CLICK,
            [](DOMButton& button, const EventMarker& event) { button.buttonChild_->SetClickedEventId(event); } },
    };
    auto operatorIter = BinarySearchFindIndex(buttonEventOperators, ArraySize(buttonEventOperators), event.c_str());
    if (operatorIter != -1) {
        LOGD("Button events : %{public}s", event.c_str());
        buttonEventOperators[operatorIter].value(*this, EventMarker(GetNodeIdForEvent(), event, pageId));
        return true;
    }
    return false;
}

void DOMButton::CallSpecializedMethod(const std::string& method, const std::string& args)
{
    auto controller = buttonChild_->GetButtonController();
    if (!controller) {
        LOGE("Get button controller error");
        EventReport::SendComponentException(ComponentExcepType::BUTTON_COMPONENT_ERR);
        return;
    }
    if (method == DOM_BUTTON_METHOD_SET_PROGRESS) {
        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if ((!argsValue) || (!argsValue->IsArray()) || (argsValue->GetArraySize() != METHOD_SET_PROGRESS_ARGS_SIZE)) {
            return;
        }
        std::unique_ptr<JsonValue> progressValue = argsValue->GetArrayItem(0)->GetValue("progress");
        if ((!progressValue) || (!progressValue->IsNumber())) {
            return;
        }
        uint32_t progress = progressValue->GetUInt();
        controller->SetProgress(progress);
    }
}

void DOMButton::PrepareSpecializedComponent()
{
    bool isCard = AceApplicationInfo::GetInstance().GetIsCardType();
    if (isCard) {
        textStyle_.SetAllowScale(false);
        if (textStyle_.GetFontSize().Unit() == DimensionUnit::FP) {
            textStyle_.SetAllowScale(true);
        }
    }
    if (!focusColorChanged_) {
        focusColor_ = buttonChild_->GetFocusColor();
    }
    buttonChild_->SetWaitingState(false);
    paddingChild_->SetChild(textChild_);
    PrepareBoxSize();
    PrepareUniversalButton();
    PrepareBorderStyle();
    PrepareBackDecorationStyle();
    PrepareButtonState();
    PreparePseudoStyle();
    if (!isTv_) {
        textChild_->SetFocusColor(textStyle_.GetTextColor());
        if (!isWatch_) {
            PrepareClickedColor();
        }
    }
    if (fontSizeDefined_) {
        textStyle_.SetAdaptTextSize(textStyle_.GetFontSize(), textStyle_.GetFontSize());
    }
    textChild_->SetTextStyle(textStyle_);
    buttonChild_->SetBorderEdge(edge_);
    AddPadding();
}

void DOMButton::PrepareBoxSize()
{
    if (!boxComponent_) {
        return;
    }
    boxComponent_->SetDeliverMinToChild(true);
    backDecoration_ = boxComponent_->GetBackDecoration();
    if (buttonType_ == BUTTON_TYPE_ARC) {
        return;
    }
    if (GreatOrEqual(buttonChild_->GetWidth().Value(), 0.0)) {
        boxComponent_->SetWidth(buttonChild_->GetWidth().Value(), buttonChild_->GetWidth().Unit());
    }
    if (GreatOrEqual(buttonChild_->GetHeight().Value(), 0.0)) {
        boxComponent_->SetHeight(buttonChild_->GetHeight().Value(), buttonChild_->GetHeight().Unit());
    }
    // Use theme height if user not define. Circle button will calculate height when rendering.
    if ((buttonType_ != BUTTON_TYPE_CIRCLE) && (LessNotEqual(buttonChild_->GetHeight().Value(), 0.0))) {
        if ((buttonType_ == BUTTON_TYPE_DOWNLOAD) && (SystemProperties::GetDeviceType() == DeviceType::PHONE)) {
            boxComponent_->SetHeight(buttonTheme_->GetDownloadHeight().Value(),
                buttonTheme_->GetDownloadHeight().Unit());
            return;
        }
        boxComponent_->SetHeight(buttonTheme_->GetHeight().Value(), buttonTheme_->GetHeight().Unit());
    }
}

void DOMButton::PreparePseudoStyle()
{
    if (!HasPseudo()) {
        return;
    }
    if (HasActivePseudo()) {
        buttonChild_->SetClickedColor(buttonChild_->GetBackgroundColor());
    }
    if (HasFocusPseudo()) {
        buttonChild_->SetFocusColor(buttonChild_->GetBackgroundColor());
    }
}

void DOMButton::PrepareUniversalButton()
{
    UpdateCustomizedColorFlag();
    if (buttonType_ == BUTTON_TYPE_ICON) {
        PrepareIconButton();
    } else if (buttonType_ == BUTTON_TYPE_CAPSULE) {
        PrepareCapsuleButton();
    } else if (buttonType_ == BUTTON_TYPE_TEXT) {
        PrepareTextButton();
    } else if (buttonType_ == BUTTON_TYPE_CIRCLE) {
        PrepareCircleButton();
    } else if (buttonType_ == BUTTON_TYPE_DOWNLOAD) {
        PrepareDownloadButton();
    } else if (buttonType_ == BUTTON_TYPE_ARC) {
        PrepareArcButton();
    } else {
        PrepareDefaultButton();
    }
}

void DOMButton::PrepareDefaultButton()
{
    paddingChild_->SetPadding(Edge());
    if (!heightDefined_) {
        ResetBoxHeight(INIT_HEIGHT);
    }
    if (!imageChild_->GetSrc().empty()) {
        if (textChild_->GetData().empty()) {
            paddingChild_->SetChild(imageChild_);
            return;
        }
        textStyle_.DisableAdaptTextSize();
        PrepareChildren();
    }
}

void DOMButton::PrepareIconButton()
{
    buttonChild_->SetType(ButtonType::ICON);
    buttonChild_->SetRectRadius(ICON_BUTTON_RADIUS);
    paddingChild_->SetChild(imageChild_);
    paddingChild_->SetPadding(Edge(ICON_BUTTON_PADDING));
    ResetBoxHeight(INIT_HEIGHT);
}

void DOMButton::PrepareCapsuleButton()
{
    buttonChild_->SetType(ButtonType::CAPSULE);
    if (!radiusDefined_) {
        if (!NearZero(buttonChild_->GetHeight().Value())) {
            buttonChild_->SetRectRadius(buttonChild_->GetHeight() / 2.0);
        }
    } else {
        ResetBoxHeight(buttonChild_->GetRectRadius().Value() * 2.0, buttonChild_->GetRectRadius().Unit());
    }
    if (isCustomizedColor_ && isTv_) {
        buttonChild_->SetFocusColor(buttonChild_->GetBackgroundColor());
        textChild_->SetFocusColor(textStyle_.GetTextColor());
    }
}

void DOMButton::PrepareTextButton()
{
    buttonChild_->SetType(ButtonType::TEXT);
    if (!isCustomizedColor_) {
        buttonChild_->SetBackgroundColor(Color(TRANSPARENT_COLOR));
    }
    textStyle_.SetTextAlign(TextAlign::CENTER);
    if (isTv_) {
        textStyle_.SetAdaptTextSize(textStyle_.GetFontSize(), TEXT_FONT_MIN_SIZE);
        paddingChild_->SetPadding(Edge(TEXT_PADDING_HORIZONTAL, TEXT_PADDING_VERTICAL,
            TEXT_PADDING_HORIZONTAL, TEXT_PADDING_VERTICAL));
        if (!fontSizeDefined_) {
            ResetBoxHeight(TEXT_FOCUS_HEIGHT, DimensionUnit::VP);
            buttonChild_->SetRectRadius(Dimension(TEXT_FOCUS_HEIGHT / 2.0, DimensionUnit::VP));
        }
        return;
    }
    if (isWatch_) {
        if (!fontSizeDefined_) {
            std::vector<TextSizeGroup> preferTextSizeGroups;
            preferTextSizeGroups.push_back({ buttonTheme_->GetTextStyle().GetFontSize(), 1 });
            preferTextSizeGroups.push_back({ buttonTheme_->GetMinFontSize(), MAX_LINES, TextOverflow::ELLIPSIS });
            textStyle_.SetPreferTextSizeGroups(preferTextSizeGroups);
        }
        ResetBoxHeight(INIT_HEIGHT);
        paddingChild_->SetPadding(Edge(WATCH_TEXT_PADDING));
        buttonChild_->SetRectRadius(WATCH_TEXT_RADIUS);
        return;
    }
    if (!textColorDefined_) {
        textStyle_.SetTextColor(buttonTheme_->GetNormalTextColor());
    }
}

void DOMButton::PrepareCircleButton()
{
    buttonChild_->SetType(ButtonType::CIRCLE);
    paddingChild_->SetPadding(Edge());
    if (!imageChild_->GetSrc().empty()) {
        paddingChild_->SetChild(imageChild_);
    }
    if (isCustomizedColor_ && isTv_) {
        buttonChild_->SetFocusColor(buttonChild_->GetBackgroundColor());
    }
}

void DOMButton::PrepareDownloadButton()
{
    buttonChild_->SetType(ButtonType::DOWNLOAD);
    if (!isWatch_) {
        edge_.SetWidth(DOWNLOAD_BORDER_WIDTH);
        buttonChild_->SetProgressColor(buttonTheme_->GetDownloadProgressColor());
        if (!isTv_) {
            if (!radiusDefined_) {
                buttonChild_->SetRectRadius(buttonTheme_->GetDownloadHeight() / 2.0);
            }
            if (!bgColorDefined_) {
                buttonChild_->SetBackgroundColor(buttonTheme_->GetDownloadBackgroundColor());
            }
            if (!textColorDefined_) {
                textStyle_.SetTextColor(buttonTheme_->GetDownloadTextColor());
            }
            if (!fontSizeDefined_) {
                textStyle_.SetFontSize(buttonTheme_->GetDownloadFontSize());
            }
        }
        return;
    }
    if (!isCustomizedColor_) {
        buttonChild_->SetBackgroundColor(Color(TRANSPARENT_COLOR));
    }
    if (!imageChild_->GetSrc().empty()) {
        paddingChild_->SetChild(imageChild_);
    }
    paddingChild_->SetPadding(Edge());
    buttonChild_->SetProgressDiameter(diameter_);
    buttonChild_->SetProgressColor(progressColor_);
    ResetBoxHeight(INIT_HEIGHT);
}

void DOMButton::PrepareArcButton()
{
    buttonChild_->SetType(ButtonType::ARC);
    textStyle_.SetAdaptTextSize(ARC_FONT_SIZE, ARC_FONT_MIN_SIZE);
    paddingChild_->SetPadding(Edge(ARC_PADDING_HORIZONTAL, ARC_PADDING_TOP,
        ARC_PADDING_HORIZONTAL, ARC_PADDING_BOTTOM));
}

void DOMButton::PrepareButtonState()
{
    UpdateCustomizedColorFlag();
    if (isWaiting_) {
        PrepareWaiting();
    } else {
        if (!textColorChanged_) {
            textColor_ = textStyle_.GetTextColor();
        }
        textStyle_.SetTextColor(textColor_);
        if (focusColorChanged_) {
            buttonChild_->SetFocusColor(focusColor_);
        }
    }

    if (buttonChild_->GetDisabledState()) {
        if (HasDisabledPseudo()) {
            buttonChild_->SetDisabledColor(buttonChild_->GetBackgroundColor());
        } else {
            PrepareDisabledBackgroundColor();
            PrepareDisabledChildStyle();
        }
    }
}

void DOMButton::PrepareDisabledBackgroundColor()
{
    if (disabledColorEffected_) {
        return;
    }
    edge_.SetColor(edge_.GetColor().BlendOpacity(blendOpacity_));
    if ((SystemProperties::GetDeviceType() == DeviceType::PHONE) && (buttonType_ == BUTTON_TYPE_DOWNLOAD)) {
        buttonChild_->SetProgressColor(buttonChild_->GetProgressColor().BlendOpacity(blendOpacity_));
    }

    // Disabled background color not defined by user.
    if (disabledColor_ == Color()) {
        Color bgColor = buttonChild_->GetBackgroundColor();
        Color customizedColor = (isWatch_ ? bgColor : bgColor.BlendOpacity(blendOpacity_));
        buttonChild_->SetDisabledColor(isCustomizedColor_ ? customizedColor : buttonTheme_->GetDisabledColor());
    } else {
        buttonChild_->SetDisabledColor(disabledColor_);
    }
    disabledColorEffected_ = true;
}

void DOMButton::PrepareDisabledChildStyle()
{
    bool isWatchDownload = isWatch_ && (buttonType_ == BUTTON_TYPE_DOWNLOAD);
    if ((buttonType_ == BUTTON_TYPE_CIRCLE) || isWatchDownload || isWaiting_) {
        auto displayChild = AceType::MakeRefPtr<DisplayComponent>(paddingChild_->GetChild());
        displayChild->SetOpacity(blendOpacity_);
        paddingChild_->SetChild(displayChild);
        return;
    }

    // Disabled text color not defined by user.
    if (disabledTextColor_ == Color()) {
        Color textColor = textStyle_.GetTextColor().BlendOpacity(blendOpacity_);
        textStyle_.SetTextColor(isCustomizedColor_ ? textColor : buttonTheme_->GetTextDisabledColor());
    } else {
        textStyle_.SetTextColor(disabledTextColor_);
    }
    textColorChanged_ = true;
}

void DOMButton::PrepareClickedColor()
{
    if (buttonChild_->GetClickedColor() != buttonTheme_->GetClickedColor()) {
        return;
    }
    Color defaultClickedColor = buttonChild_->GetBackgroundColor().BlendColor(buttonTheme_->GetClickedColor());
    buttonChild_->SetClickedColor(defaultClickedColor);
}

void DOMButton::PrepareWaiting()
{
    if ((!buttonTheme_) || isWatch_ || (buttonType_ == BUTTON_TYPE_DOWNLOAD)) {
        return;
    }
    buttonChild_->SetWaitingState(true);
    buttonChild_->SetFocusColor(focusColor_.BlendOpacity(blendOpacity_));
    buttonChild_->SetFocusAnimationColor(buttonTheme_->GetBgFocusColor().BlendOpacity(blendOpacity_));
    focusColorChanged_ = true;
    if (buttonType_ == BUTTON_TYPE_CIRCLE) {
        diameter_ = LessNotEqual(buttonChild_->GetWidth().Value(), 0.0)
                        ? buttonChild_->GetRectRadius()
                        : std::min(buttonChild_->GetHeight(), buttonChild_->GetWidth()) / 2.0;
    }
    auto progressComponent = AceType::MakeRefPtr<LoadingProgressComponent>();
    progressComponent->SetDiameter(diameter_);
    progressComponent->SetProgressColor(progressColor_);
    if ((buttonType_ == BUTTON_TYPE_CIRCLE) || (buttonType_ == BUTTON_TYPE_TEXT) || textChild_->GetData().empty()) {
        paddingChild_->SetChild(progressComponent);
        return;
    }
    PrepareWaitingWithText(progressComponent);
}

void DOMButton::PrepareWaitingWithText(const RefPtr<LoadingProgressComponent>& progressComponent)
{
    if (!progressComponent) {
        return;
    }
    if (!isCustomizedColor_) {
        textStyle_.SetTextColor(buttonTheme_->GetTextWaitingColor());
        textColorChanged_ = true;
    }
    textStyle_.DisableAdaptTextSize();
    auto innerPadding = AceType::MakeRefPtr<PaddingComponent>();
    Edge edge;
    edge.SetLeft(innerLeftPadding_);
    innerPadding->SetChild(textChild_);
    innerPadding->SetPadding(edge);
    auto flexItemProgress = AceType::MakeRefPtr<FlexItemComponent>(0.0, 0.0, 0.0, progressComponent);
    auto flexItemText = AceType::MakeRefPtr<FlexItemComponent>(0.0, 0.0, 0.0, innerPadding);
    flexItemText->SetFlexShrink(FLEX_ITEM_SHRINK);
    std::list<RefPtr<Component>> children;
    children.emplace_back(flexItemProgress);
    children.emplace_back(flexItemText);
    auto rowComponent = AceType::MakeRefPtr<RowComponent>(FlexAlign::CENTER, FlexAlign::CENTER, children);
    paddingChild_->SetChild(rowComponent);
}

void DOMButton::PrepareBorderStyle()
{
    if (!isCustomizedColor_) {
        return;
    }
    if ((buttonType_ == BUTTON_TYPE_CAPSULE) || (buttonType_ == BUTTON_TYPE_CIRCLE)) {
        edge_.SetColor(buttonTheme_->GetBorderColor());
        edge_.SetWidth(buttonTheme_->GetBorderWidth());
    }
}

void DOMButton::PrepareBackDecorationStyle()
{
    if (!backDecoration_) {
        return;
    }
    if (backDecoration_->GetImage() || backDecoration_->GetGradient().IsValid()) {
        buttonChild_->SetBackgroundColor(Color(TRANSPARENT_COLOR));
    }
    if (buttonChild_->GetType() == ButtonType::CIRCLE) {
        return;
    }
    auto border = backDecoration_->GetBorder();
    if (!HasBorderRadiusStyle() || radiusDefined_) {
        backDecoration_->SetBorderRadius(Radius(buttonChild_->GetRectRadius() + border.Top().GetWidth()));
    } else {
        buttonChild_->SetRectRadius(border.TopLeftRadius().GetX() - border.Top().GetWidth());
    }
}

void DOMButton::PrepareChildren()
{
    Edge edge;
    if (placement_ == PLACEMENT_BOTTOM) {
        edge.SetBottom(INNER_PADDING);
    } else if (placement_ == PLACEMENT_TOP) {
        edge.SetTop(INNER_PADDING);
    } else if (placement_ == PLACEMENT_START) {
        edge.SetLeft(INNER_PADDING);
    } else {
        edge.SetRight(INNER_PADDING);
        edge.SetBottom(Dimension(1.0, DimensionUnit::PX));
    }
    innerPaddingChild_ = AceType::MakeRefPtr<PaddingComponent>();
    innerPaddingChild_->SetChild(textChild_);
    innerPaddingChild_->SetPadding(edge);
    PrepareChildrenLayout();

}

void DOMButton::PrepareChildrenLayout()
{
    auto flexItemText = AceType::MakeRefPtr<FlexItemComponent>(0.0, 1.0, 0.0, innerPaddingChild_);
    auto flexItemIcon = AceType::MakeRefPtr<FlexItemComponent>(0.0, 0.0, 0.0, imageChild_);
    std::list<RefPtr<Component>> children;
    if ((placement_ == PLACEMENT_START) || (placement_ == PLACEMENT_TOP)) {
        children.emplace_back(flexItemIcon);
        children.emplace_back(flexItemText);
    } else {
        children.emplace_back(flexItemText);
        children.emplace_back(flexItemIcon);
    }
    auto flexComponent = AceType::MakeRefPtr<FlexComponent>(FlexDirection::ROW, FlexAlign::CENTER,
        FlexAlign::CENTER, children);
    if ((placement_ == PLACEMENT_TOP) || (placement_ == PLACEMENT_BOTTOM)) {
        flexComponent->SetDirection(FlexDirection::COLUMN);
    }
    flexComponent->SetMainAxisSize(MainAxisSize::MIN);
    paddingChild_->SetChild(flexComponent);
}

void DOMButton::AddPadding()
{
    RefPtr<BoxComponent> boxComponent = GetBoxComponent();
    if (!boxComponent) {
        return;
    }
    auto edge = boxComponent->GetPadding();
    if (edge == Edge::NONE) {
        return;
    }
    paddingChild_->SetPadding(edge);
    boxComponent->SetPadding(Edge());
}

void DOMButton::ResetBoxHeight(double height, DimensionUnit unit)
{
    if (!boxComponent_) {
        return;
    }
    boxComponent_->SetHeight(height, unit);
}

void DOMButton::UpdateCustomizedColorFlag()
{
    isCustomizedColor_ = buttonChild_->GetBackgroundColor() != buttonTheme_->GetBgColor();
}

} // namespace OHOS::Ace::Framework
