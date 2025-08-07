/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select/select_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/menu/menu_view.h"
#include "core/components_ng/pattern/select/select_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
void SetSelectDefaultSize(const RefPtr<FrameNode>& select)
{
    auto* pipeline = select->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    auto layoutProperty = select->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(theme->GetSelectMinWidth()), std::nullopt));
    } else {
        auto pattern = select->GetPattern<SelectPattern>();
        CHECK_NULL_VOID(pattern);
        layoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(theme->GetSelectMinWidth(pattern->GetControlSize())),
            CalcLength(theme->GetSelectDefaultHeight(pattern->GetControlSize()))));
    }
}

} // namespace

void SelectModelNG::Create(const std::vector<SelectParam>& params)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SELECT_ETS_TAG, nodeId);
    auto select = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SelectPattern>(); });
    ViewStackProcessor::GetInstance()->Push(select);

    InitSelect(AceType::RawPtr(select), params);
    auto props = select->GetPaintProperty<SelectPaintProperty>();
    if (props) {
        props->ResetFontColorSetByUser();
        props->ResetSelectedOptionBgColorSetByUser();
        props->ResetOptionBgColorSetByUser();
        props->ResetSelectedOptionFontColorSetByUser();
        props->ResetOptionFontColorSetByUser();
        props->ResetBackgroundColorSetByUser();
        props->ResetMenuBackgroundColorSetByUser();
        props->ResetTextModifierSetByUser();
        props->ResetOptionTextModifierSetByUser();
        props->ResetSelectedOptionTextModifierSetByUser();
        props->ResetArrowModifierSetByUser();
    }
}

void SelectModelNG::SetSelected(int32_t idx)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(idx);
}

void SelectModelNG::SetValue(const std::string& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetValue(value);
}

void SelectModelNG::SetFontSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontSize(value);
}

void SelectModelNG::SetFontWeight(const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontWeight(value);
}

void SelectModelNG::SetFontFamily(const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontFamily(value);
}

void SelectModelNG::SetItalicFontStyle(const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetItalicFontStyle(value);
}

void SelectModelNG::SetFontColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFontColor(color);
}

void SelectModelNG::SetSelectedOptionBgColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionBgColor(color);
}

void SelectModelNG::SetSelectedOptionFontSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontSize(value);
}

void SelectModelNG::SetSelectedOptionFontWeight(const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontWeight(value);
}

void SelectModelNG::SetSelectedOptionFontFamily(const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontFamily(value);
}

void SelectModelNG::SetSelectedOptionItalicFontStyle(const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionItalicFontStyle(value);
}

void SelectModelNG::SetSelectedOptionFontColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontColor(color);
}

void SelectModelNG::SetOptionBgColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionBgColor(color);
}

void SelectModelNG::SetOptionFontSize(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontSize(value);
}

void SelectModelNG::SetOptionFontWeight(const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontWeight(value);
}

void SelectModelNG::SetOptionFontFamily(const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontFamily(value);
}

void SelectModelNG::SetOptionItalicFontStyle(const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionItalicFontStyle(value);
}

void SelectModelNG::SetOptionFontColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontColor(color);
}

void SelectModelNG::SetOnSelect(NG::SelectEvent&& onSelect)
{
    auto hub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetSelectEvent(std::move(onSelect));
}

void SelectModelNG::SetWidth(Dimension& value)
{
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetWidth(NG::CalcLength(value));
}

void SelectModelNG::SetHeight(Dimension& value)
{
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    ViewAbstract::SetHeight(NG::CalcLength(value));
}

void SelectModelNG::SetSize(Dimension& width, Dimension& height)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }

    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetWidth(NG::CalcLength(width));
    ViewAbstract::SetHeight(NG::CalcLength(height));
}

void SelectModelNG::SetPaddings(
    const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
    const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty paddings;
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            paddings.top =
                NG::CalcLength(top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            paddings.left = NG::CalcLength(
                left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            paddings.right = NG::CalcLength(
                right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPadding(const CalcDimension& value)
{
    if (value.Unit() == DimensionUnit::CALC) {
        // padding must great or equal zero.
        ViewAbstract::SetPadding(
            NG::CalcLength(value.IsNonNegative() ? value.CalcValue() : CalcDimension().CalcValue()));
    } else {
        // padding must great or equal zero.
        ViewAbstract::SetPadding(NG::CalcLength(value.IsNonNegative() ? value : CalcDimension()));
    }
}

void SelectModelNG::SetPaddingLeft(const CalcDimension& leftValue)
{
    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    paddings.bottom = std::nullopt;

    if (!NearEqual(leftValue.Value(), 0.0)) {
        if (leftValue.Unit() == DimensionUnit::CALC) {
            paddings.left = NG::CalcLength(
                leftValue.IsNonNegative() ? leftValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.left = NG::CalcLength(leftValue.IsNonNegative() ? leftValue : CalcDimension());
        }
    }
    paddings.right = std::nullopt;
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPaddingTop(const CalcDimension& topValue)
{
    NG::PaddingProperty paddings;
    if (!NearEqual(topValue.Value(), 0.0)) {
        if (topValue.Unit() == DimensionUnit::CALC) {
            paddings.top = NG::CalcLength(
                topValue.IsNonNegative() ? topValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.top = NG::CalcLength(topValue.IsNonNegative() ? topValue : CalcDimension());
        }
    }
    paddings.bottom = std::nullopt;
    paddings.left = std::nullopt;
    paddings.right = std::nullopt;
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPaddingRight(const CalcDimension& rightValue)
{
    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    paddings.bottom = std::nullopt;
    paddings.left = std::nullopt;
    if (!NearEqual(rightValue.Value(), 0.0)) {
        if (rightValue.Unit() == DimensionUnit::CALC) {
            paddings.right = NG::CalcLength(
                rightValue.IsNonNegative() ? rightValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.right = NG::CalcLength(rightValue.IsNonNegative() ? rightValue : CalcDimension());
        }
    }
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetPaddingBottom(const CalcDimension& buttomValue)
{
    NG::PaddingProperty paddings;
    paddings.top = std::nullopt;
    if (!NearEqual(buttomValue.Value(), 0.0)) {
        if (buttomValue.Unit() == DimensionUnit::CALC) {
            paddings.bottom = NG::CalcLength(
                buttomValue.IsNonNegative() ? buttomValue.CalcValue() : CalcDimension().CalcValue());
        } else {
            paddings.bottom = NG::CalcLength(
                buttomValue.IsNonNegative() ? buttomValue : CalcDimension());
        }
    }
    paddings.left = std::nullopt;
    paddings.right = std::nullopt;
    ViewAbstract::SetPadding(paddings);
}

void SelectModelNG::SetSpace(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSpace(value);
}

void SelectModelNG::SetArrowPosition(const ArrowPosition value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetArrowPosition(value);
}

void SelectModelNG::SetMenuAlign(const MenuAlign& menuAlign)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuAlign(menuAlign);
}

void SelectModelNG::SetAvoidance(AvoidanceMode mode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetAvoidance(mode);
}

void SelectModelNG::SetSelectChangeEvent(NG::SelectChangeEvent&& selectChangeEvent)
{
    auto hub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetSelectChangeEvent(std::move(selectChangeEvent));
}

void SelectModelNG::SetValueChangeEvent(NG::ValueChangeEvent&& valueChangeEvent)
{
    auto hub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetValueChangeEvent(std::move(valueChangeEvent));
}

void SelectModelNG::SetOptionWidth(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionWidth(value);
}

void SelectModelNG::SetOptionHeight(const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionHeight(value);
}

void SelectModelNG::SetOptionWidthFitTrigger(bool isFitTrigger)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionWidthFitTrigger(isFitTrigger);
}

void SelectModelNG::SetHasOptionWidth(bool hasOptionWidth)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetHasOptionWidth(hasOptionWidth);
}

void SelectModelNG::SetControlSize(const std::optional<ControlSize>& controlSize)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    if (controlSize.has_value()) {
        auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetControlSize(controlSize.value());
    }
}

void SelectModelNG::SetDivider(const NG::SelectDivider& divider)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDivider(divider);
    pattern->SetDividerMode(std::nullopt);
}

void SelectModelNG::SetDividerStyle(const NG::SelectDivider& divider, const DividerMode& mode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDivider(divider);
    pattern->SetDividerMode(mode);
}

void SelectModelNG::SetDivider(FrameNode* frameNode, const NG::SelectDivider& divider)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetDivider(divider);
    pattern->SetDividerMode(std::nullopt);
}

void SelectModelNG::SetDividerStyle(FrameNode* frameNode, const NG::SelectDivider& divider, const DividerMode& mode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDivider(divider);
    pattern->SetDividerMode(mode);
}

void SelectModelNG::ResetDividerStyle(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto selectTheme = context->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    NG::SelectDivider divider;
    Dimension defaultMargin = -1.0_vp;
    divider.strokeWidth = selectTheme->GetDefaultDividerWidth();
    divider.color = selectTheme->GetLineColor();
    divider.startMargin = defaultMargin;
    divider.endMargin = defaultMargin;
    pattern->SetDivider(divider);
    pattern->SetDividerMode(std::nullopt);
}

void SelectModelNG::SetControlSize(FrameNode* frameNode, const std::optional<ControlSize>& controlSize)
{
    if (controlSize.has_value()) {
        auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
        CHECK_NULL_VOID(pattern);
        pattern->SetControlSize(controlSize.value());
    }
}

ControlSize SelectModelNG::GetControlSize()
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return ControlSize::NORMAL;
    }
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_RETURN(pattern, ControlSize::NORMAL);
    return pattern->GetControlSize();
}

ControlSize SelectModelNG::GetControlSize(FrameNode* frameNode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_RETURN(pattern, ControlSize::NORMAL);
    return pattern->GetControlSize();
}

RefPtr<FrameNode> SelectModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SELECT_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SelectPattern>(); });

    return frameNode;
}

RefPtr<SelectTheme> SelectModelNG::GetSelectTheme(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    return context->GetTheme<SelectTheme>(frameNode->GetThemeScopeId());
}

void SelectModelNG::SetDefaultBackGroundColor(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(Color(0x00000000));
}

void SelectModelNG::ResetComponentColor(FrameNode* frameNode, const SelectColorType& type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto selectTheme = GetSelectTheme(frameNode);
    CHECK_NULL_VOID(selectTheme);
    auto layoutProps = frameNode->GetLayoutProperty<SelectLayoutProperty>();
    CHECK_NULL_VOID(layoutProps);
    auto props = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(props);
    switch (type) {
        case SelectColorType::FONT_COLOR:
            pattern->ResetFontColor();
            break;
        case SelectColorType::BACKGROUND_COLOR:
            SetDefaultBackGroundColor(frameNode);
            break;
        case SelectColorType::SELECTED_OPTION_BG_COLOR:
            if (!layoutProps->GetShowDefaultSelectedIconValue(false)) {
                pattern->SetSelectedOptionBgColor(selectTheme->GetSelectedColor());
            }
            break;
        case SelectColorType::SELECTED_OPTION_FONT_COLOR:
            if (!layoutProps->GetShowDefaultSelectedIconValue(false)) {
                pattern->SetSelectedOptionFontColor(selectTheme->GetSelectedColorText());
            }
            break;
        case SelectColorType::OPTION_BG_COLOR:
            pattern->SetOptionBgColor(Color::TRANSPARENT);
            break;
        case SelectColorType::OPTION_FONT_COLOR:
            pattern->SetOptionFontColor(selectTheme->GetMenuFontColor());
            break;
        case SelectColorType::MENU_BACKGROUND_COLOR: {
            auto themeBgcolor =
                selectTheme->GetMenuBlendBgColor() ? selectTheme->GetBackgroundColor() : Color::TRANSPARENT;
            pattern->SetMenuBackgroundColor(themeBgcolor);
            break;
        }
        default:
            break;
    }
    frameNode->MarkModifyDone();
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SelectModelNG::CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj, const SelectColorType& type)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithColorResourceObj(frameNode, resObj, type);
}

void SelectModelNG::SetColorStatus(FrameNode* frameNode, const SelectColorType& type)
{
    if (type != SelectColorType::MENU_BACKGROUND_COLOR) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto menuNode = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetDisableMenuBgColorByUser(true);
}

void SelectModelNG::CreateWithColorResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const SelectColorType& type)
{
    CHECK_NULL_VOID(frameNode);
    SetColorStatus(frameNode, type);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "select" + ModifierColorTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [type, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CHECK_NULL_VOID(resObj);
        Color result;
        auto pattern = frameNode->GetPattern<SelectPattern>();
        CHECK_NULL_VOID(pattern);
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            SelectModelNG::ResetComponentColor(AceType::RawPtr(frameNode), type);
            return;
        }
        pattern->UpdateComponentColor(result, type);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void SelectModelNG::CreateWithValueIconResourceObj(const std::vector<SelectResObjParam>& resObjVec)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    int32_t index = 0;
    for (const auto& objParam : resObjVec) {
        RefPtr<ResourceObject> resValueObj = objParam.valueResObj;
        std::string keyValue = "selectItemValue" + std::to_string(index);
        AddResObjWithCallBack(keyValue, resValueObj, index, SelectOptionType::TEXT);
        RefPtr<ResourceObject> resIconObj = objParam.iconResObj;
        std::string keyIcon = "selectItemIcon" + std::to_string(index);
        AddResObjWithCallBack(keyIcon, resIconObj, index, SelectOptionType::ICON);
        index++;
    }
}

void SelectModelNG::AddResObjWithCallBack(
    std::string key, const RefPtr<ResourceObject>& resObj, const int32_t index, const SelectOptionType& optionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [index, optionType, weak = AceType::WeakClaim(AceType::RawPtr(pattern))](
                            const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(resObj);
        std::string result;
        switch (optionType) {
            case SelectOptionType::TEXT:
                if (!ResourceParseUtils::ParseResString(resObj, result)) {
                    return;
                }
                break;
            case SelectOptionType::ICON:
                if (!ResourceParseUtils::ParseResMedia(resObj, result)) {
                    return;
                }
                break;
            default:
                break;
        }
        pattern->UpdateMenuOption(index, result, optionType);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void SelectModelNG::CreateWithIntegerResourceObj(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithIntegerResourceObj(frameNode, resObj);
}

void SelectModelNG::CreateWithIntegerResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "selectSelected";
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(resObj);
        int32_t result;
        if (!ResourceParseUtils::ParseResInteger(resObj, result)) {
            return;
        }
        pattern->SetSelected(result);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void SelectModelNG::CreateWithStringResourceObj(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithStringResourceObj(frameNode, resObj);
}

void SelectModelNG::CreateWithStringResourceObj(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "selectValue";
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(resObj);
        std::string result;
        if (!ResourceParseUtils::ParseResString(resObj, result)) {
            return;
        }
        pattern->SetValue(result);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

std::string SelectModelNG::ModifierColorTypeToString(const SelectColorType& selectColorType)
{
    switch (selectColorType) {
        case SelectColorType::FONT_COLOR:
            return "FontColor";
        case SelectColorType::BACKGROUND_COLOR:
            return "BackgroundColor";
        case SelectColorType::SELECTED_OPTION_BG_COLOR:
            return "SelectedOptionBgColor";
        case SelectColorType::SELECTED_OPTION_FONT_COLOR:
            return "SelectedOptionFontColor";
        case SelectColorType::OPTION_BG_COLOR:
            return "OptionBgColor";
        case SelectColorType::OPTION_FONT_COLOR:
            return "OptionFontColor";
        case SelectColorType::MENU_BACKGROUND_COLOR:
            return "MenuBackgroundColor";
    }
    return "Unknown";
}

void SelectModelNG::InitSelect(FrameNode* frameNode, const std::vector<SelectParam>& params)
{
    CHECK_NULL_VOID(frameNode);
    auto select = AceType::Claim(frameNode);
    SetSelectDefaultSize(select);
    auto pattern = select->GetPattern<SelectPattern>();

    CHECK_NULL_VOID(pattern);
    auto* pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        NG::PaddingProperty paddings;
        paddings.top = std::nullopt;
        paddings.bottom = std::nullopt;
        paddings.left = NG::CalcLength(pattern->GetSelectLeftRightMargin());
        paddings.right = NG::CalcLength(pattern->GetSelectLeftRightMargin());
        ViewAbstract::SetPadding(frameNode, paddings);
    }

    pattern->BuildChild();
    // create menu node
    if (!pattern->GetMenuNode()) {
        auto menuWrapper = MenuView::Create(params, select->GetId(), V2::SELECT_ETS_TAG);
        pattern->SetMenuNode(menuWrapper);
        pattern->InitSelected();
    } else {
        auto menuNode = pattern->GetMenuNode();
        CHECK_NULL_VOID(menuNode);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        CHECK_NULL_VOID(menuPattern);
        menuPattern->UpdateSelectParam(params);
    }
    // store option pointers in select
    auto menuContainer = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuContainer);
    pattern->ClearOptions();
    auto menuPattern = menuContainer->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    auto options = menuPattern->GetOptions();
    menuPattern->SetSelectProperties(params);
    for (auto&& option : options) {
        pattern->AddOptionNode(option);
    }

    // delete menu when select node destroy
    auto destructor = [id = select->GetId(), weak = AceType::WeakClaim(AceType::RawPtr(menuContainer))]() {
        auto menuNode = weak.Upgrade();
        CHECK_NULL_VOID(menuNode);
        auto* pipeline = menuNode->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    select->PushDestroyCallbackWithTag(destructor, V2::SELECT_ETS_TAG);
}

void SelectModelNG::SetArrowPosition(FrameNode* frameNode, const ArrowPosition value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetArrowPosition(value);
}

void SelectModelNG::SetSpace(FrameNode* frameNode, const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSpace(value);
}

void SelectModelNG::SetMenuAlign(FrameNode* frameNode, const MenuAlign& menuAlign)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuAlign(menuAlign);
}

void SelectModelNG::SetAvoidance(FrameNode* frameNode, AvoidanceMode mode)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetAvoidance(mode);
}

void SelectModelNG::SetValue(FrameNode* frameNode, const std::string& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetValue(value);
}

void SelectModelNG::SetSelected(FrameNode* frameNode, int32_t idx)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(idx);
}

void SelectModelNG::SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontSize(value);
}

void SelectModelNG::SetFontWeight(FrameNode* frameNode, const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontWeight(value);
}

void SelectModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontFamily(value);
}

void SelectModelNG::SetItalicFontStyle(FrameNode* frameNode, const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetItalicFontStyle(value);
}

void SelectModelNG::SetFontColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetFontColor(color);
}

void SelectModelNG::SetSelectedOptionBgColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionBgColor(color);
}

void SelectModelNG::SetOptionFontSize(FrameNode* frameNode, const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontSize(value);
}

void SelectModelNG::SetOptionFontWeight(FrameNode* frameNode, const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontWeight(value);
}

void SelectModelNG::SetOptionFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontFamily(value);
}

void SelectModelNG::SetOptionItalicFontStyle(FrameNode* frameNode, const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionItalicFontStyle(value);
}

void SelectModelNG::SetOptionBgColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionBgColor(color);
}

void SelectModelNG::SetSelectedOptionFontColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontColor(color);
}

void SelectModelNG::SetSelectedOptionFontSize(FrameNode* frameNode, const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontSize(value);
}

void SelectModelNG::SetSelectedOptionFontWeight(FrameNode* frameNode, const FontWeight& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontWeight(value);
}

void SelectModelNG::SetSelectedOptionFontFamily(FrameNode* frameNode, const std::vector<std::string>& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionFontFamily(value);
}

void SelectModelNG::SetSelectedOptionItalicFontStyle(FrameNode* frameNode, const Ace::FontStyle& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionItalicFontStyle(value);
}

void SelectModelNG::SetOptionFontColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionFontColor(color);
}

void SelectModelNG::SetOptionWidth(FrameNode* frameNode, const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionWidth(value);
}

void SelectModelNG::SetOptionHeight(FrameNode* frameNode, const Dimension& value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionHeight(value);
}

void SelectModelNG::SetOptionWidthFitTrigger(FrameNode* frameNode, bool isFitTrigger)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionWidthFitTrigger(isFitTrigger);
}

void SelectModelNG::SetHasOptionWidth(FrameNode* frameNode, bool hasOptionWidth)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetHasOptionWidth(hasOptionWidth);
}

void SelectModelNG::SetMenuBackgroundColor(const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuBackgroundColor(color);
}

void SelectModelNG::SetMenuBackgroundBlurStyle(const BlurStyleOption& blurStyle)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuBackgroundBlurStyle(blurStyle);
}

void SelectModelNG::ResetBuilderFunc(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto menuNode = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->ResetBuilderFunc();
}

void SelectModelNG::SetBuilderFunc(FrameNode* frameNode, NG::SelectMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    auto menuNode = pattern->GetMenuNode();
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetBuilderFunc(std::move(makeFunc));
}

void SelectModelNG::SetChangeValue(FrameNode* frameNode, int index, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetItemSelected(index, value);
}

void SelectModelNG::SetOnSelect(FrameNode* frameNode, NG::SelectEvent&& onSelect)
{
    CHECK_NULL_VOID(frameNode);
    auto hub = frameNode->GetOrCreateEventHub<SelectEventHub>();
    CHECK_NULL_VOID(hub);
    hub->SetSelectEvent(std::move(onSelect));
}

void SelectModelNG::SetMenuBackgroundColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuBackgroundColor(color);
}

void SelectModelNG::SetMenuBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& blurStyle)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>(frameNode);
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuBackgroundBlurStyle(blurStyle);
}

void SelectModelNG::SetLayoutDirection(TextDirection value)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLayoutDirection(value);
}

void SelectModelNG::SetLayoutDirection(FrameNode* frameNode, TextDirection value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLayoutDirection(value);
}

void SelectModelNG::ResetFontColor()
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetFontColor();
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, FontColorSetByUser, false);
}

void SelectModelNG::BackgroundColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, BackgroundColor, color);
    ViewAbstract::SetBackgroundColor(color);
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, BackgroundColorSetByUser, true);
}

void SelectModelNG::ResetBackgroundColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SelectPaintProperty, BackgroundColor, PROPERTY_UPDATE_RENDER);
    ACE_RESET_RENDER_CONTEXT(RenderContext, BackgroundColor);
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, BackgroundColorSetByUser, false);
}

void SelectModelNG::SetMenuOutline(const MenuParam& menuParam)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuOutline(menuParam);
}

void SelectModelNG::SetMenuOutline(FrameNode* frameNode, const MenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMenuOutline(menuParam);
}

void SelectModelNG::SetTextModifierApply(const std::function<void(WeakPtr<NG::FrameNode>)>& textApply)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextModifierApply(textApply);
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, TextModifierSetByUser, true);
}

void SelectModelNG::SetArrowModifierApply(const std::function<void(WeakPtr<NG::FrameNode>)>& arrowApply)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetArrowModifierApply(arrowApply);
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, ArrowModifierSetByUser, true);
}

void SelectModelNG::SetOptionTextModifier(const std::function<void(WeakPtr<NG::FrameNode>)>& optionApply)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOptionTextModifier(optionApply);
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, OptionTextModifierSetByUser, true);
}

void SelectModelNG::SetSelectedOptionTextModifier(
    const std::function<void(WeakPtr<NG::FrameNode>)>& optionSelectedApply)
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<SelectPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedOptionTextModifier(optionSelectedApply);
    ACE_UPDATE_PAINT_PROPERTY(SelectPaintProperty, SelectedOptionTextModifierSetByUser, true);
}

void SelectModelNG::SetShowInSubWindow(bool isShowInSubWindow)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetShowInSubWindow(frameNode, isShowInSubWindow);
}

void SelectModelNG::ResetShowInSubWindow()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    selectPattern->ResetShowInSubWindow();
}

void SelectModelNG::SetShowDefaultSelectedIcon(bool show)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetShowDefaultSelectedIcon(frameNode, show);
}

void SelectModelNG::ResetShowDefaultSelectedIcon()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    selectPattern->ResetShowDefaultSelectedIcon();
}

void SelectModelNG::SetShowInSubWindow(FrameNode* frameNode, bool isShowInSubWindow)
{
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    selectPattern->SetShowInSubWindow(isShowInSubWindow);
}

void SelectModelNG::SetArrowColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    selectPattern->SetArrowColor(color);
}

void SelectModelNG::SetShowDefaultSelectedIcon(FrameNode* frameNode, bool show)
{
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    selectPattern->SetShowDefaultSelectedIcon(show);
}

void SelectModelNG::SetOptionFontColorByUser(bool isValidValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOptionFontColorByUser(frameNode, isValidValue);
}

void SelectModelNG::SetOptionFontColorByUser(FrameNode* frameNode, bool isValidValue)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateOptionFontColorSetByUser(isValidValue);
}

void SelectModelNG::SetFontColorByUser(bool isValidValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetFontColorByUser(frameNode, isValidValue);
}

void SelectModelNG::SetFontColorByUser(FrameNode* frameNode, bool isValidValue)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateFontColorSetByUser(isValidValue);
}

void SelectModelNG::SetMenuBackgroundColorByUser(bool isValidValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetMenuBackgroundColorByUser(frameNode, isValidValue);
}

void SelectModelNG::SetMenuBackgroundColorByUser(FrameNode* frameNode, bool isValidValue)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateMenuBackgroundColorSetByUser(isValidValue);
}

void SelectModelNG::SetSelectedOptionFontColorByUser(bool isValidValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetSelectedOptionFontColorByUser(frameNode, isValidValue);
}

void SelectModelNG::SetSelectedOptionFontColorByUser(FrameNode* frameNode, bool isValidValue)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateSelectedOptionFontColorSetByUser(isValidValue);
}

void SelectModelNG::SetOptionBgColorByUser(bool isValidValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOptionBgColorByUser(frameNode, isValidValue);
}

void SelectModelNG::SetOptionBgColorByUser(FrameNode* frameNode, bool isValidValue)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateOptionBgColorSetByUser(isValidValue);
}

void SelectModelNG::SetSelectedOptionBgColorByUser(bool isValidValue)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetSelectedOptionBgColorByUser(frameNode, isValidValue);
}

void SelectModelNG::SetSelectedOptionBgColorByUser(FrameNode* frameNode, bool isValidValue)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SelectPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateSelectedOptionBgColorSetByUser(isValidValue);
}
} // namespace OHOS::Ace::NG
