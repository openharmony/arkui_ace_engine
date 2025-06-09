/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/utils/string_expression.h"
#include "core/components_ng/layout/layout_property.h"

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/property/grid_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
// safeaAreaPadding does not provide default param
struct DefaultPaddingBorderParam {
    float horizontalPadding = 0.0f;
    float verticalPadding = 0.0f;
    float horizontalBorder = 0.0f;
    float verticalBorder = 0.0f;
};

PaddingPropertyF CombinePaddingsAndBorder(const PaddingPropertyF& safeAreaPadding, const PaddingPropertyF& padding,
    const BorderWidthPropertyF& borderWidth, const DefaultPaddingBorderParam& defaultParam)
{
    PaddingPropertyF result;
    result.left = safeAreaPadding.left.value_or(0.0f) + padding.left.value_or(defaultParam.horizontalPadding) +
                  borderWidth.leftDimen.value_or(defaultParam.horizontalBorder);
    result.right = safeAreaPadding.right.value_or(0.0f) + padding.right.value_or(defaultParam.horizontalPadding) +
                   borderWidth.rightDimen.value_or(defaultParam.horizontalBorder);
    result.top = safeAreaPadding.top.value_or(0.0f) + padding.top.value_or(defaultParam.verticalPadding) +
                 borderWidth.topDimen.value_or(defaultParam.verticalBorder);
    result.bottom = safeAreaPadding.bottom.value_or(0.0f) + padding.bottom.value_or(defaultParam.verticalPadding) +
                    borderWidth.bottomDimen.value_or(defaultParam.verticalBorder);
    return result;
}

std::string VisibleTypeToString(VisibleType type)
{
    static const LinearEnumMapNode<VisibleType, std::string> visibilityMap[] = {
        { VisibleType::VISIBLE, "Visibility.Visible" },
        { VisibleType::INVISIBLE, "Visibility.Hidden" },
        { VisibleType::GONE, "Visibility.None" },
    };
    auto idx = BinarySearchFindIndex(visibilityMap, ArraySize(visibilityMap), type);
    if (idx >= 0) {
        return visibilityMap[idx].value;
    }
    return "Visibility.Visible";
}

VisibleType StringToVisibleType(const std::string& str)
{
    static const std::unordered_map<std::string, VisibleType> uMap {
        { "Visibility.Visible", VisibleType::VISIBLE },
        { "Visibility.Hidden", VisibleType::INVISIBLE },
        { "Visibility.None", VisibleType::GONE },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return VisibleType::VISIBLE;
}

std::string TextDirectionToString(TextDirection type)
{
    static const LinearEnumMapNode<TextDirection, std::string> toStringMap[] = {
        { TextDirection::LTR, "Direction.Ltr" },
        { TextDirection::RTL, "Direction.Rtl" },
        { TextDirection::INHERIT, "Direction.Inherit" },
        { TextDirection::AUTO, "Direction.Auto" },
    };
    auto idx = BinarySearchFindIndex(toStringMap, ArraySize(toStringMap), type);
    if (idx >= 0) {
        return toStringMap[idx].value;
    }
    return "Direction.Ltr";
}

TextDirection StringToTextDirection(const std::string& str)
{
    static const std::unordered_map<std::string, TextDirection> uMap {
        { "Direction.Ltr", TextDirection::LTR },
        { "Direction.Rtl", TextDirection::RTL },
        { "Direction.Inherit", TextDirection::INHERIT },
        { "Direction.Auto", TextDirection::AUTO },
    };

    auto iter = uMap.find(str);
    if (iter != uMap.end()) {
        return iter->second;
    }
    return TextDirection::LTR;
}

void ConstrainContentByBorderAndPadding(std::optional<LayoutConstraintF>& contentConstraint,
    std::optional<LayoutConstraintF>& layoutConstraint, std::unique_ptr<BorderWidthProperty>& borderWidth,
    std::unique_ptr<PaddingProperty>& padding)
{
    if (padding) {
        auto paddingF = ConvertToPaddingPropertyF(
            *padding, contentConstraint->scaleProperty, contentConstraint->percentReference.Width());
        contentConstraint->MinusPaddingToNonNegativeSize(paddingF.left, paddingF.right, paddingF.top, paddingF.bottom);
    }
    CHECK_NULL_VOID(borderWidth);
    auto borderWidthF = ConvertToBorderWidthPropertyF(
        *borderWidth, contentConstraint->scaleProperty, layoutConstraint->percentReference.Width());
    contentConstraint->MinusPaddingToNonNegativeSize(
        borderWidthF.leftDimen, borderWidthF.rightDimen, borderWidthF.topDimen, borderWidthF.bottomDimen);
}

void TruncateSafeAreaPadding(const std::optional<float>& range, std::optional<float>& start, std::optional<float>& end)
{
    if (range && start && GreatNotEqual(start.value(), range.value())) {
        start = range;
    }
    if (range && end) {
        if (start) {
            end = std::min(range.value() - start.value(), end.value());
        } else {
            end = std::min(range, end);
        }
    }
}
} // namespace

LayoutProperty::LayoutProperty() = default;

LayoutProperty::~LayoutProperty() = default;

void LayoutProperty::Reset()
{
    layoutConstraint_.reset();
    calcLayoutConstraint_.reset();
    padding_.reset();
    safeAreaPadding_.reset();
    margin_.reset();
    borderWidth_.reset();
    outerBorderWidth_.reset();
    magicItemProperty_.Reset();
    positionProperty_.reset();
    measureType_.reset();
    layoutDirection_.reset();
    propVisibility_.reset();
    propIsBindOverlay_.reset();
    backgroundIgnoresLayoutSafeAreaEdges_.reset();
    CleanDirty();
}

void LayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    ACE_PROPERTY_TO_JSON_VALUE(calcLayoutConstraint_, MeasureProperty);
    ACE_PROPERTY_TO_JSON_VALUE(positionProperty_, PositionProperty);
    magicItemProperty_.ToJsonValue(json, filter);
    ACE_PROPERTY_TO_JSON_VALUE(flexItemProperty_, FlexItemProperty);
    ACE_PROPERTY_TO_JSON_VALUE(gridProperty_, GridProperty);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }

    PaddingToJsonValue(json, filter);
    MarginToJsonValue(json, filter);
    SafeAreaPaddingToJsonValue(json, filter);

    json->PutExtAttr("visibility",
        VisibleTypeToString(propVisibility_.value_or(VisibleType::VISIBLE)).c_str(), filter);
    json->PutExtAttr("direction", TextDirectionToString(GetLayoutDirection()).c_str(), filter);
    json->PutExtAttr("pixelRound", PixelRoundToJsonValue().c_str(), filter);
    SafeAreaExpandToJsonValue(json, filter);
    IgnoreLayoutSafeAreaToJsonValue(json, filter);
}

void LayoutProperty::PaddingToJsonValue(std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const
{
    if (padding_) {
        if (!padding_->top.has_value() || !padding_->right.has_value()
            || !padding_->left.has_value() || !padding_->bottom.has_value()) {
            auto paddingJsonValue = JsonUtil::Create(true);
            paddingJsonValue->Put("top", padding_->top.has_value()
                ? padding_->top.value().ToString().c_str() : "0.00vp");
            paddingJsonValue->Put("right", padding_->right.has_value()
                ? padding_->right.value().ToString().c_str() : "0.00vp");
            paddingJsonValue->Put("bottom", padding_->bottom.has_value()
                ? padding_->bottom.value().ToString().c_str() : "0.00vp");
            paddingJsonValue->Put("left", padding_->left.has_value()
                ? padding_->left.value().ToString().c_str() : "0.00vp");
            json->PutExtAttr("padding", paddingJsonValue->ToString().c_str(), filter);
        } else {
            json->PutExtAttr("padding", padding_->ToJsonString().c_str(), filter);
        }
    } else {
        json->PutExtAttr("padding", "0.00vp", filter);
    }
}

void LayoutProperty::MarginToJsonValue(std::unique_ptr<JsonValue>& json,
    const InspectorFilter& filter) const
{
    if (margin_) {
        if (!margin_->top.has_value() || !margin_->right.has_value()
            || !margin_->left.has_value() || !margin_->bottom.has_value()) {
            auto marginJsonValue = JsonUtil::Create(true);
            marginJsonValue->Put("top", margin_->top.has_value()
                ? margin_->top.value().ToString().c_str() : "0.00vp");
            marginJsonValue->Put("right", margin_->right.has_value()
                ? margin_->right.value().ToString().c_str() : "0.00vp");
            marginJsonValue->Put("bottom", margin_->bottom.has_value()
                ? margin_->bottom.value().ToString().c_str() : "0.00vp");
            marginJsonValue->Put("left", margin_->left.has_value()
                ? margin_->left.value().ToString().c_str() : "0.00vp");
            json->PutExtAttr("margin", marginJsonValue->ToString().c_str(), filter);
        } else {
            json->PutExtAttr("margin", margin_->ToJsonString().c_str(), filter);
        }
    } else {
        json->PutExtAttr("margin", "0.00vp", filter);
    }
}

void LayoutProperty::IgnoreLayoutSafeAreaToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (!ignoreLayoutSafeAreaOpts_) {
        json->PutExtAttr("ignoreLayoutSafeAreaOpts", "NA", filter);
        return;
    }
    json->PutExtAttr("ignoreLayoutSafeAreaOpts", ignoreLayoutSafeAreaOpts_->ToString().c_str(), filter);
}

void LayoutProperty::SafeAreaExpandToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (!safeAreaExpandOpts_) {
        json->PutExtAttr("safeAreaExpandOpts", "NA", filter);
        return;
    }
    json->PutExtAttr("safeAreaExpandOpts", safeAreaExpandOpts_->ToString().c_str(), filter);
}

void LayoutProperty::SafeAreaPaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (!safeAreaPadding_) {
        json->PutExtAttr("safeAreaPadding", "0.00vp", filter);
        return;
    }
    auto hasAllValue = safeAreaPadding_->top.has_value() && safeAreaPadding_->right.has_value() &&
                       safeAreaPadding_->left.has_value() && safeAreaPadding_->bottom.has_value();
    if (hasAllValue) {
        json->PutExtAttr("safeAreaPadding", safeAreaPadding_->ToJsonString().c_str(), filter);
        return;
    }
    auto safeAreaPaddingJsonValue = JsonUtil::Create(true);
    safeAreaPaddingJsonValue->Put(
        "top", safeAreaPadding_->top.has_value() ? safeAreaPadding_->top.value().ToString().c_str() : "0.00vp");
    safeAreaPaddingJsonValue->Put(
        "right", safeAreaPadding_->right.has_value() ? safeAreaPadding_->right.value().ToString().c_str() : "0.00vp");
    safeAreaPaddingJsonValue->Put("bottom",
        safeAreaPadding_->bottom.has_value() ? safeAreaPadding_->bottom.value().ToString().c_str() : "0.00vp");
    safeAreaPaddingJsonValue->Put(
        "left", safeAreaPadding_->left.has_value() ? safeAreaPadding_->left.value().ToString().c_str() : "0.00vp");
    json->PutExtAttr("safeAreaPadding", safeAreaPaddingJsonValue->ToString().c_str(), filter);
}

void LayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateCalcLayoutProperty(MeasureProperty::FromJson(json));
    UpdateLayoutWeight(json->GetDouble("layoutWeight"));
    UpdateAlignment(Alignment::GetAlignment(TextDirection::LTR, json->GetString("align")));
    auto padding = json->GetString("padding");
    if (padding != "0.0") {
        UpdatePadding(PaddingProperty::FromJsonString(padding));
    }
    auto margin = json->GetString("margin");
    if (margin != "0.0") {
        UpdateMargin(MarginProperty::FromJsonString(margin));
    }
    auto safeAreaPadding = json->GetString("safeAreaPadding");
    if (safeAreaPadding != "0.0") {
        UpdateSafeAreaPadding(PaddingProperty::FromJsonString(safeAreaPadding));
    }
    UpdateVisibility(StringToVisibleType(json->GetString("visibility")));
    UpdateLayoutDirection(StringToTextDirection(json->GetString("direction")));
}

const std::string LayoutProperty::PixelRoundToJsonValue() const
{
    auto res = JsonUtil::Create(true);
    if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START)) {
        res->Put("start", "PixelRoundCalcPolicy.FORCE_CEIL");
    } else if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START)) {
        res->Put("start", "PixelRoundCalcPolicy.FORCE_FLOOR");
    } else {
        res->Put("start", "PixelRoundCalcPolicy.NO_FORCE_ROUND");
    }
    if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP)) {
        res->Put("top", "PixelRoundCalcPolicy.FORCE_CEIL");
    } else if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP)) {
        res->Put("top", "PixelRoundCalcPolicy.FORCE_FLOOR");
    } else {
        res->Put("top", "PixelRoundCalcPolicy.NO_FORCE_ROUND");
    }
    if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END)) {
        res->Put("end", "PixelRoundCalcPolicy.FORCE_CEIL");
    } else if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END)) {
        res->Put("end", "PixelRoundCalcPolicy.FORCE_FLOOR");
    } else {
        res->Put("end", "PixelRoundCalcPolicy.NO_FORCE_ROUND");
    }
    if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM)) {
        res->Put("bottom", "PixelRoundCalcPolicy.FORCE_CEIL");
    } else if (pixelRoundFlag_ & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM)) {
        res->Put("bottom", "PixelRoundCalcPolicy.FORCE_FLOOR");
    } else {
        res->Put("bottom", "PixelRoundCalcPolicy.NO_FORCE_ROUND");
    }
    return res->ToString();
}

RefPtr<LayoutProperty> LayoutProperty::Clone() const
{
    auto layoutProperty = MakeRefPtr<LayoutProperty>();
    Clone(layoutProperty);
    return layoutProperty;
}

void LayoutProperty::Clone(RefPtr<LayoutProperty> layoutProperty) const
{
    layoutProperty->UpdateLayoutProperty(this);
}

bool LayoutProperty::DecideMirror()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
}

void LayoutProperty::UpdateLayoutProperty(const LayoutProperty* layoutProperty)
{
    CHECK_NULL_VOID(layoutProperty);
    layoutConstraint_ = layoutProperty->layoutConstraint_;
    if (layoutProperty->gridProperty_) {
        gridProperty_ = std::make_unique<GridProperty>(*layoutProperty->gridProperty_);
    }
    if (layoutProperty->calcLayoutConstraint_) {
        calcLayoutConstraint_ = std::make_unique<MeasureProperty>(*layoutProperty->calcLayoutConstraint_);
    }
    if (layoutProperty->padding_) {
        padding_ = std::make_unique<PaddingProperty>(*layoutProperty->padding_);
    }
    if (layoutProperty->margin_) {
        margin_ = std::make_unique<PaddingProperty>(*layoutProperty->margin_);
    }
    if (layoutProperty->borderWidth_) {
        borderWidth_ = std::make_unique<BorderWidthProperty>(*layoutProperty->borderWidth_);
    }
    magicItemProperty_ = layoutProperty->magicItemProperty_;
    if (layoutProperty->positionProperty_) {
        positionProperty_ = std::make_unique<PositionProperty>(*layoutProperty->positionProperty_);
    }
    if (layoutProperty->flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>(*layoutProperty->flexItemProperty_);
    }
    if (layoutProperty->safeAreaInsets_) {
        safeAreaInsets_ = std::make_unique<SafeAreaInsets>(*layoutProperty->safeAreaInsets_);
    }
    if (layoutProperty->safeAreaExpandOpts_) {
        safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>(*layoutProperty->safeAreaExpandOpts_);
    }
    if (layoutProperty->ignoreLayoutSafeAreaOpts_) {
        ignoreLayoutSafeAreaOpts_ =
            std::make_unique<IgnoreLayoutSafeAreaOpts>(*layoutProperty->ignoreLayoutSafeAreaOpts_);
    }
    geometryTransition_ = layoutProperty->geometryTransition_;
    propVisibility_ = layoutProperty->GetVisibility();
    measureType_ = layoutProperty->measureType_;
    layoutDirection_ = layoutProperty->layoutDirection_;
    propertyChangeFlag_ = layoutProperty->propertyChangeFlag_;
    propIsBindOverlay_ = layoutProperty->propIsBindOverlay_;
    isOverlayNode_ = layoutProperty->isOverlayNode_;
    overlayOffsetX_ = layoutProperty->overlayOffsetX_;
    overlayOffsetY_ = layoutProperty->overlayOffsetY_;
    backgroundIgnoresLayoutSafeAreaEdges_ = layoutProperty->backgroundIgnoresLayoutSafeAreaEdges_;
}

void LayoutProperty::UpdateCalcLayoutProperty(const MeasureProperty& constraint)
{
    if (!calcLayoutConstraint_) {
        calcLayoutConstraint_ = std::make_unique<MeasureProperty>(constraint);
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        return;
    }
    if (*calcLayoutConstraint_ == constraint) {
        return;
    }
    calcLayoutConstraint_->selfIdealSize = constraint.selfIdealSize;
    calcLayoutConstraint_->maxSize = constraint.maxSize;
    calcLayoutConstraint_->minSize = constraint.minSize;
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
}

std::pair<std::vector<std::string>, std::vector<std::string>> LayoutProperty::CalcToString(const CalcSize& calcSize)
{
    std::vector<std::string> widthString;
    std::vector<std::string> heightString;
    if (calcSize.Width().has_value() && !calcSize.Width()->CalcValue().empty()) {
        widthString = StringExpression::ConvertDal2Rpn(calcSize.Width()->CalcValue());
    }
    if (calcSize.Height().has_value() && !calcSize.Height()->CalcValue().empty()) {
        heightString = StringExpression::ConvertDal2Rpn(calcSize.Height()->CalcValue());
    }
    return std::pair<std::vector<std::string>, std::vector<std::string>>(widthString, heightString);
}

void LayoutProperty::ExpandConstraintWithSafeArea()
{
    auto host = GetHost();
    if (!host || !host->GetIgnoreLayoutProcess()) {
        return;
    }
    RefPtr<FrameNode> parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    IgnoreLayoutSafeAreaOpts options = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    if (ignoreLayoutSafeAreaOpts_) {
        options = *ignoreLayoutSafeAreaOpts_;
    }
    ExpandEdges sae = parent->GetAccumulatedSafeAreaExpand(true, options);
    auto parentConstraint = host->GetGeometryNode()->GetParentLayoutConstraint();
    OptionalSizeF contentSize;
    if (parentConstraint) {
        contentSize = parentConstraint->parentIdealSize;
    } else {
        auto rect = parent->GetGeometryNode()->GetFrameSize();
        auto padding = parent->GetLayoutProperty()->CreatePaddingAndBorder();
        MinusPaddingToNonNegativeSize(padding, rect);
        contentSize.SetWidth(rect.Width());
        contentSize.SetHeight(rect.Height());
    }
    layoutConstraint_->parentIdealSize.SetWidth(
        contentSize.Width().value_or(0.0f) + sae.left.value_or(0.0f) + sae.right.value_or(0.0f));
    layoutConstraint_->parentIdealSize.SetHeight(
        contentSize.Height().value_or(0.0f) + sae.top.value_or(0.0f) + sae.bottom.value_or(0.0f));
}

void LayoutProperty::UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint)
{
    layoutConstraint_ = parentConstraint;
    if (!needLazyLayout_) {
        layoutConstraint_->viewPosRef.reset();
    }
    ExpandConstraintWithSafeArea();
    if (margin_) {
        marginResult_.reset();
        auto margin = CreateMargin();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            MinusPaddingToNonNegativeSize(margin, layoutConstraint_->maxSize);
            MinusPaddingToNonNegativeSize(margin, layoutConstraint_->minSize);
            MinusPaddingToNonNegativeSize(margin, layoutConstraint_->percentReference);
        } else {
            MinusPaddingToSize(margin, layoutConstraint_->maxSize);
            MinusPaddingToSize(margin, layoutConstraint_->minSize);
            MinusPaddingToSize(margin, layoutConstraint_->percentReference);
        }
        // already has non negative protection
        MinusPaddingToSize(margin, layoutConstraint_->selfIdealSize);
        MinusPaddingToSize(margin, layoutConstraint_->parentIdealSize);
    }
    auto host = GetHost();
    if (host && host->GetParent() && InstanceOf<CustomMeasureLayoutNode>(host->GetParent()) &&
        GetLayoutPolicyProperty().has_value()) {
        if (GetLayoutPolicyProperty().value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH) ==
            LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
            layoutConstraint_->maxSize.SetWidth(std::numeric_limits<float>::infinity());
        }
        if (GetLayoutPolicyProperty().value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH) ==
            LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
            layoutConstraint_->maxSize.SetHeight(std::numeric_limits<float>::infinity());
        }
    }
    auto originMax = layoutConstraint_->maxSize;
    CheckCalcLayoutConstraint(parentConstraint);
    CheckSelfIdealSize(originMax);
    CheckBorderAndPadding();
    CheckAspectRatio();
}

void LayoutProperty::CheckCalcLayoutConstraint(const LayoutConstraintF& parentConstraint)
{
    if (calcLayoutConstraint_) {
        if (calcLayoutConstraint_->maxSize.has_value()) {
            if (!calcLayoutConstraint_->preMaxSize.has_value() ||
                calcLayoutConstraint_->preMaxSize.value() != calcLayoutConstraint_->maxSize.value()) {
                calcMaxSizeRpn_ = CalcToString(calcLayoutConstraint_->maxSize.value());
                calcLayoutConstraint_->preMaxSize = calcLayoutConstraint_->maxSize;
            }
            layoutConstraint_->UpdateMaxSizeWithCheck(ConvertToSize(calcLayoutConstraint_->maxSize.value(),
                parentConstraint.scaleProperty, parentConstraint.percentReference, calcMaxSizeRpn_));
        }
        if (calcLayoutConstraint_->minSize.has_value()) {
            if (!calcLayoutConstraint_->preMinSize.has_value() ||
                calcLayoutConstraint_->preMinSize.value() != calcLayoutConstraint_->minSize.value()) {
                calcMinSizeRpn_ = CalcToString(calcLayoutConstraint_->minSize.value());
                calcLayoutConstraint_->preMinSize = calcLayoutConstraint_->minSize;
            }
            layoutConstraint_->UpdateMinSizeWithCheck(ConvertToSize(calcLayoutConstraint_->minSize.value(),
                parentConstraint.scaleProperty, parentConstraint.percentReference, calcMinSizeRpn_));
        }
        if (calcLayoutConstraint_->selfIdealSize.has_value()) {
            if (!calcLayoutConstraint_->preSelfIdealSize.has_value() ||
                calcLayoutConstraint_->preSelfIdealSize.value() != calcLayoutConstraint_->selfIdealSize.value()) {
                calcSelfIdealSizeRpn_ = CalcToString(calcLayoutConstraint_->selfIdealSize.value());
                calcLayoutConstraint_->preSelfIdealSize = calcLayoutConstraint_->selfIdealSize;
            }
            layoutConstraint_->UpdateIllegalSelfIdealSizeWithCheck(
                ConvertToOptionalSize(calcLayoutConstraint_->selfIdealSize.value(), parentConstraint.scaleProperty,
                    parentConstraint.percentReference, calcSelfIdealSizeRpn_));
        }
    }
}

void LayoutProperty::UpdateLayoutConstraintWithLayoutRect()
{
    CHECK_NULL_VOID(layoutRect_);
    auto size = layoutRect_.value().GetSize();
    layoutConstraint_ = {
        .scaleProperty = ScaleProperty::CreateScaleProperty(),
        .minSize = size,
        .maxSize = size,
        .percentReference = size,
        .selfIdealSize = OptionalSizeF(size),
    };
}

void LayoutProperty::CheckBorderAndPadding()
{
    auto selfWidth = layoutConstraint_->selfIdealSize.Width();
    auto selfHeight = layoutConstraint_->selfIdealSize.Height();
    if (!selfWidth && !selfHeight) {
        return;
    }
    auto selfWidthFloat = selfWidth.value_or(Infinity<float>());
    auto selfHeightFloat = selfHeight.value_or(Infinity<float>());
    auto paddingWithBorder = CreatePaddingAndBorder(true, true);
    auto deflateWidthF = paddingWithBorder.Width();
    auto deflateHeightF = paddingWithBorder.Height();
    if (LessOrEqual(deflateWidthF, selfWidthFloat) && LessOrEqual(deflateHeightF, selfHeightFloat)) {
        return;
    }
    if (GreatNotEqual(deflateWidthF, selfWidthFloat)) {
        layoutConstraint_->selfIdealSize.SetWidth(deflateWidthF);
    }
    if (GreatNotEqual(deflateHeightF, selfHeightFloat)) {
        layoutConstraint_->selfIdealSize.SetHeight(deflateHeightF);
    }
}

void LayoutProperty::CheckAspectRatio()
{
    if (!magicItemProperty_.HasAspectRatio()) {
        return;
    }
    auto aspectRatio = magicItemProperty_.GetAspectRatioValue();
    // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and aspectRatio are
    // all set, the height is not used.
    auto maxWidth = layoutConstraint_->maxSize.Width();
    auto maxHeight = layoutConstraint_->maxSize.Height();
    if (maxHeight > maxWidth / aspectRatio) {
        maxHeight = maxWidth / aspectRatio;
    }
    layoutConstraint_->maxSize.SetWidth(maxWidth);
    layoutConstraint_->maxSize.SetHeight(maxHeight);
    std::optional<float> selfWidth;
    std::optional<float> selfHeight;
    if (layoutConstraint_->selfIdealSize.Width()) {
        selfWidth = layoutConstraint_->selfIdealSize.Width().value();
        selfHeight = selfWidth.value() / aspectRatio;
        if (selfHeight > maxHeight) {
            selfHeight = maxHeight;
            selfWidth = selfHeight.value() * aspectRatio;
        }
    } else if (layoutConstraint_->selfIdealSize.Height()) {
        selfHeight = layoutConstraint_->selfIdealSize.Height().value();
        selfWidth = selfHeight.value() * aspectRatio;
        if (selfWidth > maxWidth) {
            selfWidth = maxWidth;
            selfHeight = selfWidth.value() / aspectRatio;
        }
    }

    if (selfHeight) {
        layoutConstraint_->selfIdealSize.SetHeight(selfHeight);
    }
    if (selfWidth) {
        layoutConstraint_->selfIdealSize.SetWidth(selfWidth);
    }
}

void LayoutProperty::BuildGridProperty(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(gridProperty_);
    auto parent = host->GetAncestorNodeOfFrame(false);
    while (parent) {
        if (parent->GetTag() == V2::GRIDCONTAINER_ETS_TAG) {
            auto containerLayout = parent->GetLayoutProperty();
            gridProperty_->UpdateContainer(containerLayout, host);
            UpdateUserDefinedIdealSize(CalcSize(CalcLength(gridProperty_->GetWidth()), std::nullopt));
            break;
        }
        parent = parent->GetAncestorNodeOfFrame(false);
    }
}

void LayoutProperty::UpdateGridProperty(std::optional<int32_t> span, std::optional<int32_t> offset, GridSizeType type)
{
    if (!gridProperty_) {
        gridProperty_ = std::make_unique<GridProperty>();
    }

    bool isSpanUpdated = (span.has_value() && gridProperty_->UpdateSpan(span.value(), type));
    bool isOffsetUpdated = (offset.has_value() && gridProperty_->UpdateOffset(offset.value(), type));
    if (isSpanUpdated || isOffsetUpdated) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

bool LayoutProperty::UpdateGridOffset(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_RETURN(gridProperty_, false);
    auto optOffset = gridProperty_->GetOffset();
    if (optOffset == UNDEFINED_DIMENSION) {
        return false;
    }

    RefPtr<FrameNode> parent = host->GetAncestorNodeOfFrame(false);
    if (!parent) {
        return false;
    }
    auto parentOffset = parent->GetOffsetRelativeToWindow();
    auto globalOffset = gridProperty_->GetContainerPosition();

    OffsetF offset(optOffset.ConvertToPx(), 0);
    offset = offset + globalOffset - parentOffset;
    const auto& geometryNode = host->GetGeometryNode();
    if (offset.GetX() == geometryNode->GetFrameOffset().GetX()) {
        return false;
    }
    offset.SetY(geometryNode->GetFrameOffset().GetY());
    geometryNode->SetFrameOffset(offset);
    return true;
}

void LayoutProperty::CheckSelfIdealSize(const SizeF& originMax)
{
    if (measureType_ == MeasureType::MATCH_PARENT) {
        layoutConstraint_->UpdateIllegalSelfIdealSizeWithCheck(layoutConstraint_->parentIdealSize);
    }
    if (!calcLayoutConstraint_) {
        return;
    }
    SizeF minSize(-1.0f, -1.0f);
    SizeF maxSize(-1.0f, -1.0f);
    if (calcLayoutConstraint_->maxSize.has_value()) {
        maxSize = ConvertToSize(calcLayoutConstraint_->maxSize.value(), layoutConstraint_->scaleProperty,
            layoutConstraint_->percentReference, calcMaxSizeRpn_);
    }
    if (calcLayoutConstraint_->minSize.has_value()) {
        minSize = ConvertToSize(calcLayoutConstraint_->minSize.value(), layoutConstraint_->scaleProperty,
            layoutConstraint_->percentReference, calcMinSizeRpn_);
    }
    if (calcLayoutConstraint_->maxSize.has_value()) {
        layoutConstraint_->selfIdealSize.UpdateWidthWhenSmaller(maxSize);
        if (GreatNotEqual(maxSize.Width(), 0.0f) && GreatOrEqual(maxSize.Width(), minSize.Width())) {
            layoutConstraint_->UpdateMaxWidthWithCheck(maxSize);
        } else if (GreatNotEqual(maxSize.Width(), 0.0f) && LessNotEqual(maxSize.Width(), minSize.Width())) {
            layoutConstraint_->maxSize.SetWidth(minSize.Width());
        } else {
            layoutConstraint_->maxSize.SetWidth(originMax.Width());
        }
        layoutConstraint_->selfIdealSize.UpdateHeightWhenSmaller(maxSize);
        if (GreatNotEqual(maxSize.Height(), 0.0f) && GreatOrEqual(maxSize.Height(), minSize.Height())) {
            layoutConstraint_->UpdateMaxHeightWithCheck(maxSize);
        } else if (GreatNotEqual(maxSize.Height(), 0.0f) && LessNotEqual(maxSize.Height(), minSize.Height())) {
            layoutConstraint_->maxSize.SetHeight(minSize.Height());
        } else {
            layoutConstraint_->maxSize.SetHeight(originMax.Height());
        }
    }
    layoutConstraint_->UpdateMinSizeWithCheck(minSize);
    layoutConstraint_->selfIdealSize.UpdateSizeWhenLarger(minSize);
}

LayoutConstraintF LayoutProperty::CreateChildConstraint() const
{
    CHECK_NULL_RETURN(layoutConstraint_, {});
    auto layoutConstraint = contentConstraint_.value();
    layoutConstraint.parentIdealSize = layoutConstraint.selfIdealSize;
    // update max size when ideal size has value.
    if (layoutConstraint.parentIdealSize.Width()) {
        layoutConstraint.maxSize.SetWidth(layoutConstraint.parentIdealSize.Width().value());
        layoutConstraint.percentReference.SetWidth(layoutConstraint.parentIdealSize.Width().value());
    }
    if (layoutConstraint.parentIdealSize.Height()) {
        layoutConstraint.maxSize.SetHeight(layoutConstraint.parentIdealSize.Height().value());
        layoutConstraint.percentReference.SetHeight(layoutConstraint.parentIdealSize.Height().value());
    }
    // for child constraint, reset current selfIdealSize and minSize.
    layoutConstraint.selfIdealSize.Reset();
    layoutConstraint.minSize.Reset();
    return layoutConstraint;
}

void LayoutProperty::UpdateContentConstraint()
{
    CHECK_NULL_VOID(layoutConstraint_);
    contentConstraint_ = layoutConstraint_.value();
    // update percent reference when parent has size.
    if (contentConstraint_->parentIdealSize.Width()) {
        contentConstraint_->percentReference.SetWidth(contentConstraint_->parentIdealSize.Width().value());
    }
    if (contentConstraint_->parentIdealSize.Height()) {
        contentConstraint_->percentReference.SetHeight(contentConstraint_->parentIdealSize.Height().value());
    }
    ConstraintContentByPadding();
    ConstraintContentByBorder();
    ConstraintContentBySafeAreaPadding();
    if (needLazyLayout_ && contentConstraint_->viewPosRef.has_value()) {
        ConstraintViewPosRef(contentConstraint_->viewPosRef.value());
    }
}

void LayoutProperty::ConstraintViewPosRef(ViewPosReference& posRef)
{
    auto axis = posRef.axis;
    float adjStart = 0.0f;
    float adjEnd = 0.0f;
    if (padding_) {
        auto paddingF = ConvertToPaddingPropertyF(
            *padding_, contentConstraint_->scaleProperty, contentConstraint_->percentReference.Width());
        adjStart = axis == Axis::HORIZONTAL ? paddingF.left.value_or(0) : paddingF.top.value_or(0);
        adjEnd = axis == Axis::HORIZONTAL ? paddingF.right.value_or(0) : paddingF.bottom.value_or(0);
    }
    if (borderWidth_) {
        auto border = ConvertToBorderWidthPropertyF(
            *borderWidth_, contentConstraint_->scaleProperty, layoutConstraint_->percentReference.Width());
        adjStart += axis == Axis::HORIZONTAL ? border.leftDimen.value_or(0) : border.topDimen.value_or(0);
        adjEnd += axis == Axis::HORIZONTAL ? border.rightDimen.value_or(0) : border.bottomDimen.value_or(0);
    }
    if (margin_) {
        auto margin = CreateMargin();
        adjStart += axis == Axis::HORIZONTAL ? margin.left.value_or(0) : margin.top.value_or(0);
        adjEnd += axis == Axis::HORIZONTAL ? margin.right.value_or(0) : margin.bottom.value_or(0);
    }
    if (posRef.referenceEdge == ReferenceEdge::START) {
        posRef.referencePos = posRef.referencePos + adjStart;
    } else {
        posRef.referencePos = posRef.referencePos - adjEnd;
    }
}

void LayoutProperty::ConstraintContentByPadding()
{
    CHECK_NULL_VOID(padding_);
    auto paddingF = ConvertToPaddingPropertyF(
        *padding_, contentConstraint_->scaleProperty, contentConstraint_->percentReference.Width());
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        contentConstraint_->MinusPaddingToNonNegativeSize(paddingF.left, paddingF.right, paddingF.top, paddingF.bottom);
    } else {
        contentConstraint_->MinusPadding(paddingF.left, paddingF.right, paddingF.top, paddingF.bottom);
    }
}

void LayoutProperty::ConstraintContentByBorder()
{
    CHECK_NULL_VOID(borderWidth_);
    auto host = GetHost();
    if (host) {
        auto pattern = host->GetPattern();
        if (pattern && pattern->BorderUnoccupied()) {
            return;
        }
    }

    auto borderWidthF = ConvertToBorderWidthPropertyF(
        *borderWidth_, contentConstraint_->scaleProperty, layoutConstraint_->percentReference.Width());
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        contentConstraint_->MinusPaddingToNonNegativeSize(
            borderWidthF.leftDimen, borderWidthF.rightDimen, borderWidthF.topDimen, borderWidthF.bottomDimen);
    } else {
        contentConstraint_->MinusPadding(
            borderWidthF.leftDimen, borderWidthF.rightDimen, borderWidthF.topDimen, borderWidthF.bottomDimen);
    }
}

void LayoutProperty::ConstraintContentBySafeAreaPadding()
{
    CHECK_NULL_VOID(safeAreaPadding_);
    auto safeAreaPaddingF = ConvertToPaddingPropertyF(
        *safeAreaPadding_, contentConstraint_->scaleProperty, contentConstraint_->percentReference.Width(), true, true);
    contentConstraint_->MinusPaddingToNonNegativeSize(
        safeAreaPaddingF.left, safeAreaPaddingF.right, safeAreaPaddingF.top, safeAreaPaddingF.bottom);
}

PaddingPropertyF LayoutProperty::GetOrCreateSafeAreaPadding(bool forceReCreate)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, CreateSafeAreaPadding());
    const auto& geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, CreateSafeAreaPadding());
    auto& resolvedSafeAreaPadding = geometryNode->GetResolvedSingleSafeAreaPadding();
    if (forceReCreate || !resolvedSafeAreaPadding) {
        host->ResetSafeAreaPadding();
        auto safeAreaPadding = CreateSafeAreaPadding();
        geometryNode->SetResolvedSingleSafeAreaPadding(safeAreaPadding);
        return safeAreaPadding;
    }
    return *(resolvedSafeAreaPadding.get());
}

PaddingPropertyF LayoutProperty::CreateSafeAreaPadding()
{
    if (layoutConstraint_.has_value()) {
        std::optional<LayoutConstraintF> contentWithSafeArea = layoutConstraint_.value();
        ConstrainContentByBorderAndPadding(contentWithSafeArea, layoutConstraint_, borderWidth_, padding_);
        PaddingPropertyF truncatedSafeAreaPadding = ConvertToPaddingPropertyF(safeAreaPadding_,
            ScaleProperty::CreateScaleProperty(), layoutConstraint_->percentReference.Width(), true, true);
        TruncateSafeAreaPadding(
            contentWithSafeArea->selfIdealSize.Height(), truncatedSafeAreaPadding.top, truncatedSafeAreaPadding.bottom);

        bool isRtl = DecideMirror() && safeAreaPadding_ &&
                     (safeAreaPadding_->start.has_value() || safeAreaPadding_->end.has_value());
        TruncateSafeAreaPadding(contentWithSafeArea->selfIdealSize.Width(),
            isRtl ? truncatedSafeAreaPadding.right : truncatedSafeAreaPadding.left,
            isRtl ? truncatedSafeAreaPadding.left : truncatedSafeAreaPadding.right);
        return truncatedSafeAreaPadding;
    }
    return ConvertToPaddingPropertyF(
        safeAreaPadding_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth(), true, true);
}

PaddingPropertyF LayoutProperty::CreatePaddingAndBorder(bool includeSafeAreaPadding, bool forceReCreate)
{
    PaddingPropertyF safeAreaPadding;
    if (includeSafeAreaPadding) {
        safeAreaPadding = GetOrCreateSafeAreaPadding(forceReCreate);
    }
    if (layoutConstraint_.has_value()) {
        auto padding = ConvertToPaddingPropertyF(
            padding_, ScaleProperty::CreateScaleProperty(), layoutConstraint_->percentReference.Width());
        auto borderWidth = ConvertToBorderWidthPropertyF(
            borderWidth_, ScaleProperty::CreateScaleProperty(), layoutConstraint_->percentReference.Width());
        auto host = GetHost();
        if (host) {
            auto pattern = host->GetPattern();
            if (pattern && pattern->BorderUnoccupied()) {
                borderWidth = BorderWidthPropertyF();
            }
        }
        return CombinePaddingsAndBorder(safeAreaPadding, padding, borderWidth, {});
    }
    auto padding = ConvertToPaddingPropertyF(
        padding_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth());
    auto borderWidth = ConvertToBorderWidthPropertyF(
        borderWidth_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth());
    return CombinePaddingsAndBorder(safeAreaPadding, padding, borderWidth, {});
}

PaddingPropertyF LayoutProperty::CreatePaddingAndBorderWithDefault(float paddingHorizontalDefault,
    float paddingVerticalDefault, float borderHorizontalDefault, float borderVerticalDefault)
{
    auto safeAreaPadding = GetOrCreateSafeAreaPadding();
    DefaultPaddingBorderParam defaultParem = { .horizontalPadding = paddingHorizontalDefault,
        .verticalPadding = paddingVerticalDefault,
        .horizontalBorder = borderHorizontalDefault,
        .verticalBorder = borderVerticalDefault };
    if (layoutConstraint_.has_value()) {
        auto padding = ConvertToPaddingPropertyF(
            padding_, ScaleProperty::CreateScaleProperty(), layoutConstraint_->percentReference.Width());
        auto borderWidth = ConvertToBorderWidthPropertyF(
            borderWidth_, ScaleProperty::CreateScaleProperty(), layoutConstraint_->percentReference.Width());
        return CombinePaddingsAndBorder(safeAreaPadding, padding, borderWidth, defaultParem);
    }
    auto padding = ConvertToPaddingPropertyF(
        padding_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth());
    auto borderWidth = ConvertToBorderWidthPropertyF(
        borderWidth_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth());
    return CombinePaddingsAndBorder(safeAreaPadding, padding, borderWidth, defaultParem);
}

PaddingPropertyF LayoutProperty::CreatePaddingWithoutBorder(bool useRootConstraint, bool roundPixel)
{
    auto safeAreaPadding = GetOrCreateSafeAreaPadding();
    if (layoutConstraint_.has_value()) {
        auto padding = ConvertToPaddingPropertyF(
            padding_, layoutConstraint_->scaleProperty, layoutConstraint_->percentReference.Width(), roundPixel);
        auto totalPadding = CombinePaddingsAndBorder(safeAreaPadding, padding, {}, {});
        return totalPadding;
    }

    auto padding = ConvertToPaddingPropertyF(padding_, ScaleProperty::CreateScaleProperty(),
        useRootConstraint ? PipelineContext::GetCurrentRootWidth() : 0.0f, roundPixel);
    auto totalPadding = CombinePaddingsAndBorder(safeAreaPadding, padding, {}, {});
    return totalPadding;
}

BorderWidthPropertyF LayoutProperty::CreateBorder()
{
    // no pixel rounding
    if (layoutConstraint_.has_value()) {
        return ConvertToBorderWidthPropertyF(
            borderWidth_, layoutConstraint_->scaleProperty, layoutConstraint_->percentReference.Width(), false);
    }

    return ConvertToBorderWidthPropertyF(
        borderWidth_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth(), false);
}

MarginPropertyF LayoutProperty::CreateMargin()
{
    CHECK_NULL_RETURN(margin_, MarginPropertyF());
    if (!marginResult_.has_value() && margin_) {
        if (layoutConstraint_.has_value()) {
            marginResult_ = ConvertToMarginPropertyF(
                margin_, layoutConstraint_->scaleProperty, layoutConstraint_->percentReference.Width());
        } else {
            // root node
            marginResult_ = ConvertToMarginPropertyF(
                margin_, ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth());
        }
    }
    return marginResult_.value_or(MarginPropertyF());
}

MarginPropertyF LayoutProperty::CreateMarginWithoutCache()
{
    CHECK_NULL_RETURN(margin_, MarginPropertyF());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, MarginPropertyF());
    const auto& parentConstraint = host->GetGeometryNode()->GetParentLayoutConstraint();
    // no pixel rounding
    if (parentConstraint) {
        return ConvertToMarginPropertyF(
            margin_, parentConstraint->scaleProperty, parentConstraint->percentReference.Width(), false);
    }
    // the root width is not considered at present.
    return ConvertToMarginPropertyF(margin_, ScaleProperty::CreateScaleProperty(), 0.0f, false);
}

void LayoutProperty::SetHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> LayoutProperty::GetHost() const
{
    return host_.Upgrade();
}

void LayoutProperty::OnVisibilityUpdate(VisibleType visible, bool allowTransition, bool isUserSet)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    // store the previous visibility value.
    auto preVisibility = propVisibility_;

    // update visibility value.
    propVisibility_ = visible;
    auto pipeline = host->GetContext();
    uint64_t vsyncTime = 0;
    if (pipeline) {
        vsyncTime = pipeline->GetVsyncTime();
    }
    host->AddVisibilityDumpInfo({ vsyncTime, { visible, isUserSet } });

    host->NotifyVisibleChange(preVisibility.value_or(VisibleType::VISIBLE), visible);
    if (allowTransition && preVisibility) {
        if (preVisibility.value() == VisibleType::VISIBLE && visible != VisibleType::VISIBLE) {
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->OnNodeDisappear(false);
        } else if (preVisibility.value() != VisibleType::VISIBLE && visible == VisibleType::VISIBLE) {
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->OnNodeAppear(false);
        }
    }

    auto parent = host->GetAncestorNodeOfFrame(false);
    CHECK_NULL_VOID(parent);
    // if visible is not changed to/from VisibleType::Gone, only need to update render tree.
    if (preVisibility.value_or(VisibleType::VISIBLE) != VisibleType::GONE && visible != VisibleType::GONE) {
        parent->MarkNeedSyncRenderTree();
        parent->RebuildRenderContextTree();
        return;
    }
    UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    parent->MarkNeedSyncRenderTree();
    parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void LayoutProperty::UpdateIgnoreLayoutSafeAreaOpts(const IgnoreLayoutSafeAreaOpts& opts)
{
    if (!ignoreLayoutSafeAreaOpts_) {
        ignoreLayoutSafeAreaOpts_ = std::make_unique<IgnoreLayoutSafeAreaOpts>();
    }
    if (ignoreLayoutSafeAreaOpts_->NeedUpdateWithCheck(opts)) {
        *ignoreLayoutSafeAreaOpts_ = opts;
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

bool LayoutProperty::IsExpandConstraintNeeded()
{
    if (!layoutPolicy_ || !ignoreLayoutSafeAreaOpts_ || ignoreLayoutSafeAreaOpts_->type == LAYOUT_SAFE_AREA_TYPE_NONE ||
        ignoreLayoutSafeAreaOpts_->edges == LAYOUT_SAFE_AREA_EDGE_NONE) {
        return false;
    }
    auto edges = ignoreLayoutSafeAreaOpts_->edges;
    bool res = false;
    if ((edges & LAYOUT_SAFE_AREA_EDGE_TOP) || (edges & LAYOUT_SAFE_AREA_EDGE_BOTTOM)) {
        res |= layoutPolicy_->IsHeightMatch();
    }
    if ((edges & LAYOUT_SAFE_AREA_EDGE_START) || (edges & LAYOUT_SAFE_AREA_EDGE_END)) {
        res |= layoutPolicy_->IsWidthMatch();
    }
    return res;
}

void LayoutProperty::UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts)
{
    if (!safeAreaExpandOpts_) {
        safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    }
    if (*safeAreaExpandOpts_ != opts) {
        *safeAreaExpandOpts_ = opts;
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
        safeAreaExpandOpts_->switchToNone = !opts.Expansive();
    }
}

void LayoutProperty::UpdateSafeAreaInsets(const SafeAreaInsets& safeArea)
{
    if (!safeAreaInsets_) {
        safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    }
    if (*safeAreaInsets_ != safeArea) {
        *safeAreaInsets_ = safeArea;
    }
}

bool LayoutProperty::HasFixedWidth(bool checkPercent) const
{
    CHECK_NULL_RETURN(calcLayoutConstraint_, false);
    auto&& idealSize = calcLayoutConstraint_->selfIdealSize;
    return (idealSize && idealSize->WidthFixed(checkPercent));
}

bool LayoutProperty::HasFixedHeight(bool checkPercent) const
{
    CHECK_NULL_RETURN(calcLayoutConstraint_, false);
    auto&& idealSize = calcLayoutConstraint_->selfIdealSize;
    return (idealSize && idealSize->HeightFixed(checkPercent));
}

bool LayoutProperty::HasAspectRatio() const
{
    return magicItemProperty_.HasAspectRatio();
}

float LayoutProperty::GetAspectRatio() const
{
    if (magicItemProperty_.HasAspectRatio()) {
        return magicItemProperty_.GetAspectRatioValue();
    }
    return 0.0f;
}

void LayoutProperty::UpdateAspectRatio(float ratio)
{
    if (magicItemProperty_.UpdateAspectRatio(ratio)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::ResetAspectRatio()
{
    if (magicItemProperty_.HasAspectRatio()) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        magicItemProperty_.ResetAspectRatio();
    }
}

void LayoutProperty::UpdateGeometryTransition(const std::string& id,
    bool followWithoutTransition, bool doRegisterSharedTransition)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto geometryTransitionOld = GetGeometryTransition();
    auto geometryTransitionNew =
        ElementRegister::GetInstance()->GetOrCreateGeometryTransition(id,
            followWithoutTransition, doRegisterSharedTransition);
    CHECK_NULL_VOID(geometryTransitionOld != geometryTransitionNew);
    if (geometryTransitionOld) {
        if (geometryTransitionOld->Update(host_, host_)) {
            geometryTransitionOld->OnFollowWithoutTransition();
        }
        // unregister node from old geometry transition
        geometryTransitionOld->Update(host_, nullptr);
        // register node into new geometry transition
        if (geometryTransitionNew && !geometryTransitionNew->Update(nullptr, host_)) {
            TAG_LOGE(AceLogTag::ACE_GEOMETRY_TRANSITION, "redundant node%{public}d has same geoid: %{public}s",
                host->GetId(), id.c_str());
        }
    } else if (geometryTransitionNew) {
        if (geometryTransitionNew->IsInAndOutValid()) {
            TAG_LOGE(AceLogTag::ACE_GEOMETRY_TRANSITION, "redundant node%{public}d has same geoid: %{public}s",
                host->GetId(), id.c_str());
        }
        geometryTransitionNew->Build(host_, true);
    }
    geometryTransition_ = geometryTransitionNew;

    TAG_LOGD(AceLogTag::ACE_GEOMETRY_TRANSITION, "node: %{public}d update id, old id: %{public}s, new id: %{public}s",
        host->GetId(), geometryTransitionOld ? geometryTransitionOld->GetId().c_str() : "empty",
        geometryTransitionNew ? id.c_str() : "empty");
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
}

void LayoutProperty::ResetGeometryTransition()
{
    if (!GetGeometryTransition()) {
        return;
    }
    UpdateGeometryTransition("");
}

void LayoutProperty::UpdateLayoutDirection(TextDirection value)
{
    if (layoutDirection_ == value) {
        return;
    }
    layoutDirection_ = value;
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    OnPropertyChangeMeasure();
}

void LayoutProperty::UpdateBackgroundIgnoresLayoutSafeAreaEdges(uint32_t value)
{
    if (backgroundIgnoresLayoutSafeAreaEdges_ == value) {
        return;
    }
    backgroundIgnoresLayoutSafeAreaEdges_ = value;
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
}

TextDirection LayoutProperty::GetNonAutoLayoutDirection() const
{
    auto direction = layoutDirection_.value_or(TextDirection::AUTO);
    return direction != TextDirection::AUTO
               ? direction
               : (AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR);
}

void LayoutProperty::UpdateLayoutWeight(float value)
{
    if (magicItemProperty_.UpdateLayoutWeight(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateChainWeight(const ChainWeightPair& value)
{
    if (flexItemProperty_->UpdateChainWeight(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateBorderWidth(const BorderWidthProperty& value)
{
    if (!borderWidth_) {
        borderWidth_ = std::make_unique<BorderWidthProperty>();
    }
    if (borderWidth_->UpdateWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateOuterBorderWidth(const BorderWidthProperty& value)
{
    if (!outerBorderWidth_) {
        outerBorderWidth_ = std::make_unique<BorderWidthProperty>();
    }
    if (outerBorderWidth_->UpdateWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateAlignment(Alignment value)
{
    if (!positionProperty_) {
        positionProperty_ = std::make_unique<PositionProperty>();
    }
    if (positionProperty_->UpdateAlignment(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT;
    }
}

void LayoutProperty::UpdateMargin(const MarginProperty& value)
{
    if (!margin_) {
        margin_ = std::make_unique<MarginProperty>();
    }
    if (margin_->UpdateWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdatePadding(const PaddingProperty& value)
{
    if (!padding_) {
        padding_ = std::make_unique<PaddingProperty>();
    }
    if (padding_->UpdateWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateSafeAreaPadding(const PaddingProperty& value)
{
    if (!safeAreaPadding_) {
        safeAreaPadding_ = std::make_unique<PaddingProperty>();
    }
    if (safeAreaPadding_->UpdateWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::ResetSafeAreaPadding()
{
    if (!safeAreaPadding_) {
        return;
    }
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    safeAreaPadding_.reset();
}

void LayoutProperty::UpdateUserDefinedIdealSize(const CalcSize& value)
{
    if (!calcLayoutConstraint_) {
        calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    if (calcLayoutConstraint_->UpdateSelfIdealSizeWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateLayoutPolicyProperty(const LayoutCalPolicy layoutPolicy, bool isWidth)
{
    if (!layoutPolicy_) {
        layoutPolicy_ = NG::LayoutPolicyProperty();
    }
    if (UpdateLayoutPolicyWithCheck(layoutPolicy, isWidth)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

bool LayoutProperty::UpdateLayoutPolicyWithCheck(const LayoutCalPolicy layoutPolicy, bool isWidth)
{
    if (isWidth) {
        if (layoutPolicy_->widthLayoutPolicy_ && layoutPolicy_->widthLayoutPolicy_.value() == layoutPolicy) {
            return false;
        }
        layoutPolicy_->widthLayoutPolicy_ = layoutPolicy;
    } else {
        if (layoutPolicy_->heightLayoutPolicy_ && layoutPolicy_->heightLayoutPolicy_.value() == layoutPolicy) {
            return false;
        }
        layoutPolicy_->heightLayoutPolicy_ = layoutPolicy;
    }
    return true;
}

std::optional<NG::LayoutPolicyProperty> LayoutProperty::GetLayoutPolicyProperty()
{
    return layoutPolicy_;
}

void LayoutProperty::ClearUserDefinedIdealSize(bool clearWidth, bool clearHeight)
{
    if (!calcLayoutConstraint_) {
        return;
    }
    if (calcLayoutConstraint_->ClearSelfIdealSize(clearWidth, clearHeight)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateCalcMinSize(const CalcSize& value)
{
    if (!calcLayoutConstraint_) {
        calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    if (calcLayoutConstraint_->UpdateMinSizeWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateCalcMaxSize(const CalcSize& value)
{
    if (!calcLayoutConstraint_) {
        calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    if (calcLayoutConstraint_->UpdateMaxSizeWithCheck(value)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateMarginSelfIdealSize(const SizeF& value)
{
    if (!layoutConstraint_.has_value()) {
        layoutConstraint_ = LayoutConstraintF();
    }
    if (layoutConstraint_->UpdateSelfMarginSizeWithCheck(OptionalSizeF(value))) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::ResetCalcMinSize()
{
    if (!calcLayoutConstraint_) {
        return;
    }
    if (calcLayoutConstraint_->minSize.has_value()) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
    calcLayoutConstraint_->minSize.reset();
    calcLayoutConstraint_->preMinSize.reset();
}

void LayoutProperty::ResetCalcMaxSize()
{
    if (!calcLayoutConstraint_) {
        return;
    }
    if (calcLayoutConstraint_->maxSize.has_value()) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
    calcLayoutConstraint_->maxSize.reset();
    calcLayoutConstraint_->preMaxSize.reset();
}

void LayoutProperty::ResetCalcMinSize(bool resetWidth)
{
    if (!calcLayoutConstraint_) {
        return;
    }
    CHECK_NULL_VOID(calcLayoutConstraint_->minSize.has_value());
    bool resetSizeHasValue = resetWidth ? calcLayoutConstraint_->minSize.value().Width().has_value()
                                        : calcLayoutConstraint_->minSize.value().Height().has_value();
    CHECK_NULL_VOID(resetSizeHasValue);
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    if (resetWidth) {
        calcLayoutConstraint_->minSize.value().SetWidth(std::nullopt);
    } else {
        calcLayoutConstraint_->minSize.value().SetHeight(std::nullopt);
    }
}

void LayoutProperty::ResetCalcMaxSize(bool resetWidth)
{
    if (!calcLayoutConstraint_) {
        return;
    }
    CHECK_NULL_VOID(calcLayoutConstraint_->maxSize.has_value());
    bool resetSizeHasValue = resetWidth ? calcLayoutConstraint_->maxSize.value().Width().has_value()
                                        : calcLayoutConstraint_->maxSize.value().Height().has_value();
    CHECK_NULL_VOID(resetSizeHasValue);
    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    if (resetWidth) {
        calcLayoutConstraint_->maxSize.value().SetWidth(std::nullopt);
    } else {
        calcLayoutConstraint_->maxSize.value().SetHeight(std::nullopt);
    }
}

void LayoutProperty::UpdateFlexGrow(float flexGrow)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateFlexGrow(flexGrow)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::ResetFlexGrow()
{
    if (!flexItemProperty_) {
        return;
    }
    if (flexItemProperty_->HasFlexGrow()) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
    flexItemProperty_->ResetFlexGrow();
}

void LayoutProperty::UpdateFlexShrink(float flexShrink)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateFlexShrink(flexShrink)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::ResetFlexShrink()
{
    if (!flexItemProperty_) {
        return;
    }
    if (flexItemProperty_->HasFlexShrink()) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
    flexItemProperty_->ResetFlexShrink();
}

void LayoutProperty::UpdateFlexBasis(const Dimension& flexBasis)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateFlexBasis(flexBasis)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateAlignSelf(const FlexAlign& flexAlign)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateAlignSelf(flexAlign)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::ResetAlignSelf()
{
    if (!flexItemProperty_) {
        return;
    }
    if (flexItemProperty_->HasAlignSelf()) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
    flexItemProperty_->ResetAlignSelf();
}

void LayoutProperty::UpdateAlignRules(const std::map<AlignDirection, AlignRule>& alignRules)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateAlignRules(alignRules)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateChainStyle(const ChainInfo& chainInfo)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (!chainInfo.direction.has_value()) {
        ChainInfo nullChainInfo;
        if (flexItemProperty_->UpdateHorizontalChainStyle(nullChainInfo)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
        if (flexItemProperty_->UpdateVerticalChainStyle(nullChainInfo)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }
    if (chainInfo.direction == LineDirection::HORIZONTAL) {
        if (flexItemProperty_->UpdateHorizontalChainStyle(chainInfo)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    } else {
        if (flexItemProperty_->UpdateVerticalChainStyle(chainInfo)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }
}

void LayoutProperty::UpdateBias(const BiasPair& biasPair)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateBias(biasPair)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::UpdateDisplayIndex(int32_t displayIndex)
{
    if (!flexItemProperty_) {
        flexItemProperty_ = std::make_unique<FlexItemProperty>();
    }
    if (flexItemProperty_->UpdateDisplayIndex(displayIndex)) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT;
    }
}

LayoutConstraintF LayoutProperty::CreateContentConstraint() const
{
    auto layoutConstraint = contentConstraint_.value_or(LayoutConstraintF());
    layoutConstraint.maxSize.UpdateSizeWhenSmaller(layoutConstraint.selfIdealSize.ConvertToSizeT());
    return layoutConstraint;
}

void LayoutProperty::UpdateLayoutConstraint(const RefPtr<LayoutProperty>& layoutProperty)
{
    layoutConstraint_ = layoutProperty->layoutConstraint_;
    contentConstraint_ = layoutProperty->contentConstraint_;
    gridProperty_ =
        (layoutProperty->gridProperty_) ? std::make_unique<GridProperty>(*layoutProperty->gridProperty_) : nullptr;
}

void LayoutProperty::UpdateVisibility(const VisibleType& value, bool allowTransition, bool isUserSet)
{
    isUserSetVisibility_ = isUserSet;
    if (propVisibility_.has_value()) {
        if (NearEqual(propVisibility_.value(), value)) {
            return;
        }
    }
    OnVisibilityUpdate(value, allowTransition, isUserSet);
}

void LayoutProperty::SetOverlayOffset(
    const std::optional<Dimension>& overlayOffsetX, const std::optional<Dimension>& overlayOffsetY)
{
    bool xChanged = true;
    bool yChanged = false;
    if ((!overlayOffsetX.has_value() && overlayOffsetX_.Value() == 0) ||
        (overlayOffsetX.has_value() && overlayOffsetX.value() == overlayOffsetX_)) {
        xChanged = false;
    }

    if ((!overlayOffsetY.has_value() && overlayOffsetY_.Value() == 0) ||
        (overlayOffsetY.has_value() && overlayOffsetY.value() == overlayOffsetY_)) {
        yChanged = false;
    }

    if (!xChanged && !yChanged) {
        return;
    }

    if (overlayOffsetX.has_value()) {
        overlayOffsetX_ = overlayOffsetX.value();
    } else {
        overlayOffsetX_.Reset();
    }

    if (overlayOffsetY.has_value()) {
        overlayOffsetY_ = overlayOffsetY.value();
    } else {
        overlayOffsetY_.Reset();
    }

    propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
}

void LayoutProperty::GetOverlayOffset(Dimension& overlayOffsetX, Dimension& overlayOffsetY)
{
    overlayOffsetX = overlayOffsetX_;
    overlayOffsetY = overlayOffsetY_;
}

void LayoutProperty::UpdateAllGeometryTransition(const RefPtr<UINode>& parent)
{
    std::queue<RefPtr<UINode>> q;
    q.push(parent);
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        auto frameNode = AceType::DynamicCast<FrameNode>(node);
        if (frameNode) {
            auto layoutProperty = frameNode->GetLayoutProperty();
            if (layoutProperty && layoutProperty->GetGeometryTransition()) {
                auto geometryTransitionId = layoutProperty->GetGeometryTransition()->GetId();
                layoutProperty->UpdateGeometryTransition("");
                layoutProperty->UpdateGeometryTransition(geometryTransitionId);
            }
        }
        const auto& children = node->GetChildren();
        for (const auto& child : children) {
            q.push(child);
        }
    }
}

std::pair<bool, bool> LayoutProperty::GetPercentSensitive()
{
    if (!contentConstraint_.has_value()) {
        return { false, false };
    }
    std::pair<bool, bool> res = { false, false };
    const auto& constraint = contentConstraint_.value();
    if (GreaterOrEqualToInfinity(constraint.maxSize.Height())) {
        if (calcLayoutConstraint_ && calcLayoutConstraint_->PercentHeight()) {
            res.second = true;
        }
    }
    if (GreaterOrEqualToInfinity(constraint.maxSize.Width())) {
        if (calcLayoutConstraint_ && calcLayoutConstraint_->PercentWidth()) {
            res.first = true;
        }
    }
    return res;
}

std::pair<bool, bool> LayoutProperty::UpdatePercentSensitive(bool width, bool height)
{
    if (!contentConstraint_.has_value()) {
        return { false, false };
    }
    const auto& constraint = contentConstraint_.value();
    if (GreaterOrEqualToInfinity(constraint.maxSize.Height())) {
        heightPercentSensitive_ = heightPercentSensitive_ || height;
    }
    if (GreaterOrEqualToInfinity(constraint.maxSize.Width())) {
        widthPercentSensitive_ = heightPercentSensitive_ || width;
    }
    return { widthPercentSensitive_, heightPercentSensitive_ };
}

bool LayoutProperty::ConstraintEqual(const std::optional<LayoutConstraintF>& preLayoutConstraint,
    const std::optional<LayoutConstraintF>& preContentConstraint)
{
    if (!preLayoutConstraint || !layoutConstraint_) {
        return false;
    }
    if (!preContentConstraint || !contentConstraint_) {
        return false;
    }
    bool isNeedPercent = false;
    auto host = GetHost();
    if (host) {
        auto pattern = host->GetPattern();
        isNeedPercent = pattern ? pattern->IsNeedPercent() : false;
    }
    const auto& layout = layoutConstraint_.value();
    const auto& content = contentConstraint_.value();
    if (!isNeedPercent && GreaterOrEqualToInfinity(layout.maxSize.Width()) && !widthPercentSensitive_) {
        return (layout.EqualWithoutPercentWidth(preLayoutConstraint.value()) &&
                content.EqualWithoutPercentWidth(preContentConstraint.value()));
    }
    if (!isNeedPercent && GreaterOrEqualToInfinity(layout.maxSize.Height()) && !heightPercentSensitive_) {
        return (layout.EqualWithoutPercentHeight(preLayoutConstraint.value()) &&
                content.EqualWithoutPercentHeight(preContentConstraint.value()));
    }
    return (preLayoutConstraint == layoutConstraint_ && preContentConstraint == contentConstraint_);
}

void LayoutProperty::CheckPositionLocalizedEdges(TextDirection layoutDirection)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    EdgesParam edges;
    auto positionEdges = target->GetPositionEdgesValue(EdgesParam {});
    if (!positionEdges.start.has_value() && !positionEdges.end.has_value()) {
        return;
    }
    if (positionEdges.top.has_value()) {
        edges.SetTop(positionEdges.top.value_or(Dimension(0.0)));
    }
    if (positionEdges.bottom.has_value()) {
        edges.SetBottom(positionEdges.bottom.value_or(Dimension(0.0)));
    }
    if (positionEdges.start.has_value()) {
        edges.start = positionEdges.start.value();
        if (layoutDirection == TextDirection::RTL) {
            edges.SetRight(positionEdges.start.value_or(Dimension(0.0)));
        } else {
            edges.SetLeft(positionEdges.start.value_or(Dimension(0.0)));
        }
    }
    if (positionEdges.end.has_value()) {
        edges.end = positionEdges.end.value();
        if (layoutDirection == TextDirection::RTL) {
            edges.SetLeft(positionEdges.end.value_or(Dimension(0.0)));
        } else {
            edges.SetRight(positionEdges.end.value_or(Dimension(0.0)));
        }
    }
    target->UpdatePositionEdges(edges);
}

void LayoutProperty::CheckMarkAnchorPosition(TextDirection layoutDirection)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    CalcDimension x;
    CalcDimension y;
    auto anchor = target->GetAnchorValue({});
    if (!markAnchorStart_.has_value()) {
        return;
    }
    OffsetT<Dimension> offset(Dimension(0.0), Dimension(0.0));
    if (markAnchorStart_.has_value()) {
        x = layoutDirection == TextDirection::RTL ? -markAnchorStart_.value() : markAnchorStart_.value();
        offset.SetX(x);
    }
    offset.SetY(anchor.GetY());
    target->UpdateAnchor(offset);
}

void LayoutProperty::CheckOffsetLocalizedEdges(TextDirection layoutDirection)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    EdgesParam edges;
    auto offsetEdges = target->GetOffsetEdgesValue(EdgesParam {});
    if (!offsetEdges.start.has_value() && !offsetEdges.end.has_value()) {
        return;
    }
    if (offsetEdges.top.has_value()) {
        edges.SetTop(offsetEdges.top.value_or(Dimension(0.0)));
    }
    if (offsetEdges.bottom.has_value()) {
        edges.SetBottom(offsetEdges.bottom.value_or(Dimension(0.0)));
    }
    if (offsetEdges.start.has_value()) {
        edges.start = offsetEdges.start.value();
        if (layoutDirection == TextDirection::RTL) {
            edges.SetRight(offsetEdges.start.value_or(Dimension(0.0)));
        } else {
            edges.SetLeft(offsetEdges.start.value_or(Dimension(0.0)));
        }
    }
    if (offsetEdges.end.has_value()) {
        edges.end = offsetEdges.end.value();
        if (layoutDirection == TextDirection::RTL) {
            edges.SetLeft(offsetEdges.end.value_or(Dimension(0.0)));
        } else {
            edges.SetRight(offsetEdges.end.value_or(Dimension(0.0)));
        }
    }
    target->UpdateOffsetEdges(edges);
}

void LayoutProperty::CheckLocalizedBorderRadiuses(const TextDirection& direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    BorderRadiusProperty borderRadius;
    BorderRadiusProperty borderRadiusProperty = target->GetBorderRadiusValue(BorderRadiusProperty {});
    if (!borderRadiusProperty.radiusTopStart.has_value() && !borderRadiusProperty.radiusTopEnd.has_value() &&
        !borderRadiusProperty.radiusBottomStart.has_value() && !borderRadiusProperty.radiusBottomEnd.has_value()) {
        return;
    }
    if (borderRadiusProperty.radiusTopStart.has_value()) {
        borderRadius.radiusTopStart = borderRadiusProperty.radiusTopStart;
        if (direction == TextDirection::RTL) {
            borderRadius.radiusTopRight = borderRadiusProperty.radiusTopStart;
        } else {
            borderRadius.radiusTopLeft = borderRadiusProperty.radiusTopStart;
        }
    }
    if (borderRadiusProperty.radiusTopEnd.has_value()) {
        borderRadius.radiusTopEnd = borderRadiusProperty.radiusTopEnd;
        if (direction == TextDirection::RTL) {
            borderRadius.radiusTopLeft = borderRadiusProperty.radiusTopEnd;
        } else {
            borderRadius.radiusTopRight = borderRadiusProperty.radiusTopEnd;
        }
    }
    if (borderRadiusProperty.radiusBottomStart.has_value()) {
        borderRadius.radiusBottomStart = borderRadiusProperty.radiusBottomStart;
        if (direction == TextDirection::RTL) {
            borderRadius.radiusBottomRight = borderRadiusProperty.radiusBottomStart;
        } else {
            borderRadius.radiusBottomLeft = borderRadiusProperty.radiusBottomStart;
        }
    }
    if (borderRadiusProperty.radiusBottomEnd.has_value()) {
        borderRadius.radiusBottomEnd = borderRadiusProperty.radiusBottomEnd;
        if (direction == TextDirection::RTL) {
            borderRadius.radiusBottomLeft = borderRadiusProperty.radiusBottomEnd;
        } else {
            borderRadius.radiusBottomRight = borderRadiusProperty.radiusBottomEnd;
        }
    }
    target->UpdateBorderRadius(borderRadius);
}

void LayoutProperty::CheckLocalizedOuterBorderColor(const TextDirection& direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    NG::BorderColorProperty borderColors;
    borderColors.multiValued = true;
    auto outerBorderColorProperty = target->GetOuterBorderColorValue(BorderColorProperty {});
    if (!outerBorderColorProperty.startColor.has_value() && !outerBorderColorProperty.endColor.has_value()) {
        return;
    }
    if (outerBorderColorProperty.startColor.has_value()) {
        borderColors.startColor = outerBorderColorProperty.startColor;
        if (direction == TextDirection::RTL) {
            borderColors.rightColor = outerBorderColorProperty.startColor;
        } else {
            borderColors.leftColor = outerBorderColorProperty.startColor;
        }
    }
    if (outerBorderColorProperty.endColor.has_value()) {
        borderColors.endColor = outerBorderColorProperty.endColor;
        if (direction == TextDirection::RTL) {
            borderColors.leftColor = outerBorderColorProperty.endColor;
        } else {
            borderColors.rightColor = outerBorderColorProperty.endColor;
        }
    }
    if (outerBorderColorProperty.topColor.has_value()) {
        borderColors.topColor = outerBorderColorProperty.topColor;
    }
    if (outerBorderColorProperty.bottomColor.has_value()) {
        borderColors.topColor = outerBorderColorProperty.bottomColor;
    }
    target->UpdateOuterBorderColor(borderColors);
}

void LayoutProperty::CheckLocalizedPadding(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction)
{
    CHECK_NULL_VOID(layoutProperty);
    const auto& paddingProperty = layoutProperty->GetPaddingProperty();
    CHECK_NULL_VOID(paddingProperty);
    if (!paddingProperty->start.has_value() && !paddingProperty->end.has_value()) {
        return;
    }
    PaddingProperty padding;
    if (paddingProperty->start.has_value()) {
        padding.start = paddingProperty->start;
        if (direction == TextDirection::RTL) {
            padding.right = paddingProperty->start;
        } else {
            padding.left = paddingProperty->start;
        }
    }
    if (paddingProperty->end.has_value()) {
        padding.end = paddingProperty->end;
        if (direction == TextDirection::RTL) {
            padding.left = paddingProperty->end;
        } else {
            padding.right = paddingProperty->end;
        }
    }
    if (paddingProperty->top.has_value()) {
        padding.top = paddingProperty->top;
    }
    if (paddingProperty->bottom.has_value()) {
        padding.bottom = paddingProperty->bottom;
    }
    if (padding.left.has_value() && !padding.right.has_value()) {
        padding.right = std::optional<CalcLength>(CalcLength(0));
    }
    if (!padding.left.has_value() && padding.right.has_value()) {
        padding.left = std::optional<CalcLength>(CalcLength(0));
    }
    LocalizedPaddingOrMarginChange(padding, padding_);
}

void LayoutProperty::CheckLocalizedMargin(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction)
{
    CHECK_NULL_VOID(layoutProperty);
    const auto& marginProperty = layoutProperty->GetMarginProperty();
    CHECK_NULL_VOID(marginProperty);
    if (!marginProperty->start.has_value() && !marginProperty->end.has_value()) {
        return;
    }
    MarginProperty margin;
    if (marginProperty->start.has_value()) {
        margin.start = marginProperty->start;
        if (direction == TextDirection::RTL) {
            margin.right = marginProperty->start;
        } else {
            margin.left = marginProperty->start;
        }
    }
    if (marginProperty->end.has_value()) {
        margin.end = marginProperty->end;
        if (direction == TextDirection::RTL) {
            margin.left = marginProperty->end;
        } else {
            margin.right = marginProperty->end;
        }
    }
    if (marginProperty->top.has_value()) {
        margin.top = marginProperty->top;
    }
    if (marginProperty->bottom.has_value()) {
        margin.bottom = marginProperty->bottom;
    }
    if (margin.left.has_value() && !margin.right.has_value()) {
        margin.right = std::optional<CalcLength>(CalcLength(0));
    }
    if (!margin.left.has_value() && margin.right.has_value()) {
        margin.left = std::optional<CalcLength>(CalcLength(0));
    }
    LocalizedPaddingOrMarginChange(margin, margin_);
}

void LayoutProperty::CheckLocalizedSafeAreaPadding(const TextDirection& direction)
{
    const auto& safeAreaPaddingProperty = GetSafeAreaPaddingProperty();
    CHECK_NULL_VOID(safeAreaPaddingProperty);
    if (!safeAreaPaddingProperty->start.has_value() && !safeAreaPaddingProperty->end.has_value()) {
        return;
    }
    PaddingProperty safeAreaPadding;
    if (safeAreaPaddingProperty->start.has_value()) {
        safeAreaPadding.start = safeAreaPaddingProperty->start;
        if (direction == TextDirection::RTL) {
            safeAreaPadding.right = safeAreaPaddingProperty->start;
        } else {
            safeAreaPadding.left = safeAreaPaddingProperty->start;
        }
    }
    if (safeAreaPaddingProperty->end.has_value()) {
        safeAreaPadding.end = safeAreaPaddingProperty->end;
        if (direction == TextDirection::RTL) {
            safeAreaPadding.left = safeAreaPaddingProperty->end;
        } else {
            safeAreaPadding.right = safeAreaPaddingProperty->end;
        }
    }
    if (safeAreaPaddingProperty->top.has_value()) {
        safeAreaPadding.top = safeAreaPaddingProperty->top;
    }
    if (safeAreaPaddingProperty->bottom.has_value()) {
        safeAreaPadding.bottom = safeAreaPaddingProperty->bottom;
    }
    if (safeAreaPadding.left.has_value() && !safeAreaPadding.right.has_value()) {
        safeAreaPadding.right = std::optional<CalcLength>(CalcLength(0));
    }
    if (!safeAreaPadding.left.has_value() && safeAreaPadding.right.has_value()) {
        safeAreaPadding.left = std::optional<CalcLength>(CalcLength(0));
    }
    LocalizedPaddingOrMarginChange(safeAreaPadding, safeAreaPadding_);
}

void LayoutProperty::CheckIgnoreLayoutSafeArea(const TextDirection& direction)
{
    CHECK_NULL_VOID(ignoreLayoutSafeAreaOpts_);
    auto rawEdges = ignoreLayoutSafeAreaOpts_->rawEdges;
    LayoutSafeAreaEdge edges = LAYOUT_SAFE_AREA_EDGE_NONE;
    if (rawEdges & LAYOUT_SAFE_AREA_EDGE_TOP) {
        edges |= LAYOUT_SAFE_AREA_EDGE_TOP;
    }
    if (rawEdges & LAYOUT_SAFE_AREA_EDGE_BOTTOM) {
        edges |= LAYOUT_SAFE_AREA_EDGE_BOTTOM;
    }
    if (rawEdges & LAYOUT_SAFE_AREA_EDGE_START) {
        if (direction == TextDirection::RTL) {
            edges |= LAYOUT_SAFE_AREA_EDGE_END;
        } else {
            edges |= LAYOUT_SAFE_AREA_EDGE_START;
        }
    }
    if (rawEdges & LAYOUT_SAFE_AREA_EDGE_END) {
        if (direction == TextDirection::RTL) {
            edges |= LAYOUT_SAFE_AREA_EDGE_START;
        } else {
            edges |= LAYOUT_SAFE_AREA_EDGE_END;
        }
    }

    if (edges != ignoreLayoutSafeAreaOpts_->edges) {
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
        ignoreLayoutSafeAreaOpts_->edges = edges;
    }
}

void LayoutProperty::LocalizedPaddingOrMarginChange(
    const PaddingProperty& value, std::unique_ptr<PaddingProperty>& padding)
{
    if (value != *padding || padding->start != value.start || padding->end != value.end) {
        padding->start = value.start;
        padding->end = value.end;
        padding->left = value.left;
        padding->right = value.right;
        padding->top = value.top;
        padding->bottom = value.bottom;
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE;
    }
}

void LayoutProperty::CheckLocalizedEdgeWidths(
    const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction)
{
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    auto borderWidthProperty = target->GetBorderWidth();
    CHECK_NULL_VOID(borderWidthProperty);
    if (!borderWidthProperty->startDimen.has_value() && !borderWidthProperty->endDimen.has_value()) {
        return;
    }
    BorderWidthProperty borderWidth;
    if (borderWidthProperty->startDimen.has_value()) {
        borderWidth.startDimen = borderWidthProperty->startDimen;
        if (direction == TextDirection::RTL) {
            borderWidth.rightDimen = borderWidthProperty->startDimen;
        } else {
            borderWidth.leftDimen = borderWidthProperty->startDimen;
        }
    }
    if (borderWidthProperty->endDimen.has_value()) {
        borderWidth.endDimen = borderWidthProperty->endDimen;
        if (direction == TextDirection::RTL) {
            borderWidth.leftDimen = borderWidthProperty->endDimen;
        } else {
            borderWidth.rightDimen = borderWidthProperty->endDimen;
        }
    }
    if (borderWidthProperty->topDimen.has_value()) {
        borderWidth.topDimen = borderWidthProperty->topDimen;
    }
    if (borderWidthProperty->bottomDimen.has_value()) {
        borderWidth.bottomDimen = borderWidthProperty->bottomDimen;
    }
    if (borderWidth.leftDimen.has_value() && !borderWidth.rightDimen.has_value()) {
        borderWidth.rightDimen = std::optional<Dimension>(Dimension(0));
    }
    if (!borderWidth.leftDimen.has_value() && borderWidth.rightDimen.has_value()) {
        borderWidth.leftDimen = std::optional<Dimension>(Dimension(0));
    }
    borderWidth.multiValued = true;
    layoutProperty->UpdateBorderWidth(borderWidth);
    target->UpdateBorderWidth(borderWidth);
}

void LayoutProperty::CheckLocalizedEdgeColors(const TextDirection& direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    BorderColorProperty borderColors;
    BorderColorProperty colorProperty = target->GetBorderColorValue(BorderColorProperty {});
    if (!colorProperty.startColor.has_value() && !colorProperty.endColor.has_value()) {
        return;
    }
    if (colorProperty.startColor.has_value()) {
        borderColors.startColor = colorProperty.startColor;
        if (direction == TextDirection::RTL) {
            borderColors.rightColor = colorProperty.startColor;
        } else {
            borderColors.leftColor = colorProperty.startColor;
        }
    }
    if (colorProperty.endColor.has_value()) {
        borderColors.endColor = colorProperty.endColor;
        if (direction == TextDirection::RTL) {
            borderColors.leftColor = colorProperty.endColor;
        } else {
            borderColors.rightColor = colorProperty.endColor;
        }
    }
    if (colorProperty.topColor.has_value()) {
        borderColors.topColor = colorProperty.topColor;
    }
    if (colorProperty.bottomColor.has_value()) {
        borderColors.bottomColor = colorProperty.bottomColor;
    }
    borderColors.multiValued = true;
    target->UpdateBorderColor(borderColors);
}

void LayoutProperty::CheckLocalizedBorderImageSlice(const TextDirection& direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    auto borderImage = target->GetBorderImage();
    CHECK_NULL_VOID(borderImage);
    auto borderImageProperty = borderImage.value();
    CHECK_NULL_VOID(borderImageProperty);
    auto isGreaterThanFourteen =
        AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN);
    if (isGreaterThanFourteen) {
        if (!borderImageProperty->borderImageStart_->GetBorderImageSlice().IsValid() &&
            !borderImageProperty->borderImageEnd_->GetBorderImageSlice().IsValid()) {
            return;
        }
    } else {
        if (!borderImageProperty->borderImageStart_.has_value() && !borderImageProperty->borderImageEnd_.has_value()) {
            return;
        }
    }
    Dimension leftSlice;
    Dimension rightSlice;
    Dimension startSlice;
    Dimension endSlice;
    if (isGreaterThanFourteen ? borderImageProperty->borderImageStart_->GetBorderImageSlice().IsValid()
                            : borderImageProperty->borderImageStart_.has_value()) {
        startSlice = borderImageProperty->borderImageStart_->GetBorderImageSlice();
        borderImageProperty->SetEdgeSlice(BorderImageDirection::START, startSlice);
        if (direction == TextDirection::RTL) {
            rightSlice = borderImageProperty->borderImageStart_->GetBorderImageSlice();
        } else {
            leftSlice = borderImageProperty->borderImageStart_->GetBorderImageSlice();
        }
    }
    if (isGreaterThanFourteen ? borderImageProperty->borderImageEnd_->GetBorderImageSlice().IsValid()
                            : borderImageProperty->borderImageEnd_.has_value()) {
        endSlice = borderImageProperty->borderImageEnd_->GetBorderImageSlice();
        borderImageProperty->SetEdgeSlice(BorderImageDirection::END, endSlice);
        if (direction == TextDirection::RTL) {
            leftSlice = borderImageProperty->borderImageEnd_->GetBorderImageSlice();
        } else {
            rightSlice = borderImageProperty->borderImageEnd_->GetBorderImageSlice();
        }
    }
    borderImageProperty->SetEdgeSlice(BorderImageDirection::LEFT, leftSlice);
    borderImageProperty->SetEdgeSlice(BorderImageDirection::RIGHT, rightSlice);
    target->UpdateBorderImage(borderImageProperty);
}

void LayoutProperty::CheckLocalizedBorderImageWidth(const TextDirection& direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    auto borderImage = target->GetBorderImage();
    CHECK_NULL_VOID(borderImage);
    auto borderImageProperty = borderImage.value();
    CHECK_NULL_VOID(borderImageProperty);
    auto isGreaterThanFourteen =
        AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN);
    if (isGreaterThanFourteen) {
        if (!borderImageProperty->borderImageStart_->GetBorderImageWidth().IsValid() &&
            !borderImageProperty->borderImageEnd_->GetBorderImageWidth().IsValid()) {
            return;
        }
    } else {
        if (!borderImageProperty->borderImageStart_.has_value() && !borderImageProperty->borderImageEnd_.has_value()) {
            return;
        }
    }
    Dimension leftWidth;
    Dimension rightWidth;
    Dimension startWidth;
    Dimension endWidth;
    if (isGreaterThanFourteen ? borderImageProperty->borderImageStart_->GetBorderImageWidth().IsValid()
                              : borderImageProperty->borderImageStart_.has_value()) {
        startWidth = borderImageProperty->borderImageStart_->GetBorderImageWidth();
        borderImageProperty->SetEdgeWidth(BorderImageDirection::START, startWidth);
        if (direction == TextDirection::RTL) {
            rightWidth = borderImageProperty->borderImageStart_->GetBorderImageWidth();
        } else {
            leftWidth = borderImageProperty->borderImageStart_->GetBorderImageWidth();
        }
    }
    if (isGreaterThanFourteen ? borderImageProperty->borderImageEnd_->GetBorderImageWidth().IsValid()
                              : borderImageProperty->borderImageEnd_.has_value()) {
        endWidth = borderImageProperty->borderImageEnd_->GetBorderImageWidth();
        borderImageProperty->SetEdgeWidth(BorderImageDirection::END, endWidth);
        if (direction == TextDirection::RTL) {
            leftWidth = borderImageProperty->borderImageEnd_->GetBorderImageWidth();
        } else {
            rightWidth = borderImageProperty->borderImageEnd_->GetBorderImageWidth();
        }
    }
    borderImageProperty->SetEdgeWidth(BorderImageDirection::LEFT, leftWidth);
    borderImageProperty->SetEdgeWidth(BorderImageDirection::RIGHT, rightWidth);
    target->UpdateBorderImage(borderImageProperty);
}

void LayoutProperty::CheckLocalizedBorderImageOutset(const TextDirection& direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& target = host->GetRenderContext();
    CHECK_NULL_VOID(target);
    auto borderImage = target->GetBorderImage();
    CHECK_NULL_VOID(borderImage);
    auto borderImageProperty = borderImage.value();
    CHECK_NULL_VOID(borderImageProperty);
    auto isGreaterThanFourteen =
        AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FOURTEEN);
    if (isGreaterThanFourteen) {
        if (!borderImageProperty->borderImageStart_->GetBorderImageOutset().IsValid() &&
            !borderImageProperty->borderImageEnd_->GetBorderImageOutset().IsValid()) {
            return;
        }
    } else {
        if (!borderImageProperty->borderImageStart_.has_value() && !borderImageProperty->borderImageEnd_.has_value()) {
            return;
        }
    }

    Dimension leftOutset;
    Dimension rightOutset;
    Dimension startOutset;
    Dimension endOutset;
    if (isGreaterThanFourteen ? borderImageProperty->borderImageStart_->GetBorderImageOutset().IsValid()
                              : borderImageProperty->borderImageStart_.has_value()) {
        startOutset = borderImageProperty->borderImageStart_->GetBorderImageOutset();
        borderImageProperty->SetEdgeOutset(BorderImageDirection::START, startOutset);
        if (direction == TextDirection::RTL) {
            rightOutset = borderImageProperty->borderImageStart_->GetBorderImageOutset();
        } else {
            leftOutset = borderImageProperty->borderImageStart_->GetBorderImageOutset();
        }
    }
    if (isGreaterThanFourteen ? borderImageProperty->borderImageEnd_->GetBorderImageOutset().IsValid()
                              : borderImageProperty->borderImageEnd_.has_value()) {
        endOutset = borderImageProperty->borderImageEnd_->GetBorderImageOutset();
        borderImageProperty->SetEdgeOutset(BorderImageDirection::END, endOutset);
        if (direction == TextDirection::RTL) {
            leftOutset = borderImageProperty->borderImageEnd_->GetBorderImageOutset();
        } else {
            rightOutset = borderImageProperty->borderImageEnd_->GetBorderImageOutset();
        }
    }
    borderImageProperty->SetEdgeOutset(BorderImageDirection::LEFT, leftOutset);
    borderImageProperty->SetEdgeOutset(BorderImageDirection::RIGHT, rightOutset);
    target->UpdateBorderImage(borderImageProperty);
}

std::string LayoutProperty::LayoutInfoToString()
{
    std::stringstream ss;
    if (HasAspectRatio()) {
        ss << "aspectRatio: " << magicItemProperty_.GetAspectRatioValue() << ",";
    }
    if (magicItemProperty_.GetLayoutWeight().has_value()) {
        ss << "layoutWeight: " << magicItemProperty_.GetLayoutWeight().value() << ",";
    }
    if (GetPositionProperty() && GetPositionProperty()->GetAlignment().has_value()) {
        ss << GetPositionProperty()->GetAlignment().value().ToString() << ",";
    }
    if (GetLayoutDirection() != TextDirection::AUTO) {
        ss << "layoutDirection: " << static_cast<int32_t>(GetLayoutDirection());
    }
    return ss.str();
}
RefPtr<GeometryTransition> LayoutProperty::GetGeometryTransition() const
{
    return geometryTransition_.Upgrade();
}
} // namespace OHOS::Ace::NG
