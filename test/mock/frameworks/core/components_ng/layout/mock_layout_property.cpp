/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/grid_property.h"
#include "core/components_ng/property/position_property.h"

namespace OHOS::Ace::NG {
LayoutProperty::LayoutProperty() = default;

LayoutProperty::~LayoutProperty() = default;

void LayoutProperty::Reset() {}

void LayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

void LayoutProperty::PaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

void LayoutProperty::MarginToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

void LayoutProperty::IgnoreLayoutSafeAreaToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{}

void LayoutProperty::SafeAreaExpandToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

void LayoutProperty::SafeAreaPaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{}

void LayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json) {}

const std::string LayoutProperty::PixelRoundToJsonValue() const
{
    return std::string();
}

RefPtr<LayoutProperty> LayoutProperty::Clone() const
{
    return nullptr;
}

void LayoutProperty::Clone(RefPtr<LayoutProperty> layoutProperty) const {}

bool LayoutProperty::DecideMirror()
{
    return false;
}

void LayoutProperty::UpdateLayoutProperty(const LayoutProperty* layoutProperty) {}

void LayoutProperty::UpdateCalcLayoutProperty(const MeasureProperty& constraint) {}

void LayoutProperty::CalcToString(
    const CalcSize& calcSize, std::pair<std::vector<std::string>, std::vector<std::string>>& result)
{}

bool LayoutProperty::IsExpandConstraintDependencySatisfied() const
{
    return false;
}

IgnoreLayoutSafeAreaOpts LayoutProperty::GenIgnoreOpts() const
{
    IgnoreLayoutSafeAreaOpts options = { .type = NG::LAYOUT_SAFE_AREA_TYPE_NONE,
        .edges = NG::LAYOUT_SAFE_AREA_TYPE_NONE };
    return options;
}

void LayoutProperty::ExpandConstraintWithSafeArea() {}

void LayoutProperty::UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint) {}

void LayoutProperty::CheckCalcLayoutConstraint(const LayoutConstraintF& parentConstraint) {}

void LayoutProperty::UpdateLayoutConstraintWithLayoutRect() {}

void LayoutProperty::CheckBorderAndPadding() {}

void LayoutProperty::CheckAspectRatio() {}

void LayoutProperty::BuildGridProperty(const RefPtr<FrameNode>& host) {}

void LayoutProperty::UpdateGridProperty(std::optional<int32_t> span, std::optional<int32_t> offset, GridSizeType type)
{}

bool LayoutProperty::UpdateGridOffset(const RefPtr<FrameNode>& host)
{
    return true;
}

void LayoutProperty::CheckSelfIdealSize(const SizeF& originMax) {}

LayoutConstraintF LayoutProperty::CreateChildConstraint() const
{
    return {};
}

void LayoutProperty::UpdateContentConstraint() {}

void LayoutProperty::ConstraintViewPosRef(ViewPosReference& posRef) {}

void LayoutProperty::ConstraintContentByPadding() {}

void LayoutProperty::ConstraintContentByBorder() {}

void LayoutProperty::ConstraintContentBySafeAreaPadding() {}

PaddingPropertyF LayoutProperty::GetOrCreateSafeAreaPadding(bool forceReCreate)
{
    return {};
}

PaddingPropertyF LayoutProperty::CreateSafeAreaPadding(bool adjustingRound)
{
    return {};
}

PaddingPropertyF LayoutProperty::CreatePaddingAndBorder(bool includeSafeAreaPadding, bool forceReCreate)
{
    return {};
}

PaddingPropertyF LayoutProperty::CreatePaddingAndBorderWithDefault(float paddingHorizontalDefault,
    float paddingVerticalDefault, float borderHorizontalDefault, float borderVerticalDefault)
{
    return {};
}

PaddingPropertyF LayoutProperty::CreatePaddingWithoutBorder(bool useRootConstraint, bool roundPixel)
{
    return {};
}

BorderWidthPropertyF LayoutProperty::CreateBorder(bool isRoundPixel)
{
    return {};
}

MarginPropertyF LayoutProperty::CreateMargin()
{
    return {};
}

MarginPropertyF LayoutProperty::CreateMarginWithoutCache()
{
    return {};
}

void LayoutProperty::SetHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

RefPtr<FrameNode> LayoutProperty::GetHost() const
{
    return host_.Upgrade();
}

void LayoutProperty::OnVisibilityUpdate(VisibleType visible, bool allowTransition, bool isUserSet) {}

void LayoutProperty::UpdateIgnoreLayoutSafeAreaOpts(const IgnoreLayoutSafeAreaOpts& opts) {}

bool LayoutProperty::IsExpandConstraintNeeded()
{
    return false;
}

void LayoutProperty::UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts) {}

void LayoutProperty::UpdateSafeAreaInsets(const SafeAreaInsets& safeArea) {}

bool LayoutProperty::HasFixedWidth(bool checkPercent) const
{
    return false;
}

bool LayoutProperty::HasFixedHeight(bool checkPercent) const
{
    return false;
}

bool LayoutProperty::HasAspectRatio() const
{
    return false;
}

float LayoutProperty::GetAspectRatio() const
{
    return 0.0f;
}

void LayoutProperty::UpdateAspectRatio(float ratio) {}

void LayoutProperty::ResetAspectRatio() {}

void LayoutProperty::UpdateGeometryTransition(
    const std::string& id, bool followWithoutTransition, bool doRegisterSharedTransition)
{}

void LayoutProperty::ResetGeometryTransition() {}

void LayoutProperty::SetGeometryTransitionInfo(
    const std::string& id, bool followWithoutTransition, bool doRegisterSharedTransition)
{}

void LayoutProperty::UpdateLayoutDirection(TextDirection value) {}

void LayoutProperty::UpdateBackgroundIgnoresLayoutSafeAreaEdges(uint32_t value) {}

TextDirection LayoutProperty::GetNonAutoLayoutDirection() const
{
    return TextDirection::AUTO;
}

void LayoutProperty::UpdateLayoutWeight(float value) {}

void LayoutProperty::UpdateChainWeight(const ChainWeightPair& value) {}

void LayoutProperty::UpdateBorderWidth(const BorderWidthProperty& value) {}

void LayoutProperty::UpdateOuterBorderWidth(const BorderWidthProperty& value) {}

void LayoutProperty::UpdateAlignment(Alignment value) {}

void LayoutProperty::UpdateLocalizedAlignment(std::string value) {}

void LayoutProperty::UpdateLayoutGravity(Alignment value) {}

void LayoutProperty::UpdateIsMirrorable(bool value) {}

void LayoutProperty::UpdateMargin(const MarginProperty& value) {}

void LayoutProperty::UpdatePadding(const PaddingProperty& value) {}

void LayoutProperty::UpdateSafeAreaPadding(const PaddingProperty& value) {}

void LayoutProperty::ResetSafeAreaPadding() {}

void LayoutProperty::UpdateUserDefinedIdealSize(const CalcSize& value) {}

void LayoutProperty::UpdateLayoutPolicyProperty(const LayoutCalPolicy layoutPolicy, bool isWidth) {}

bool LayoutProperty::UpdateLayoutPolicyWithCheck(const LayoutCalPolicy layoutPolicy, bool isWidth)
{
    return true;
}

std::optional<NG::LayoutPolicyProperty> LayoutProperty::GetLayoutPolicyProperty()
{
    return layoutPolicy_;
}

void LayoutProperty::ClearUserDefinedIdealSize(bool clearWidth, bool clearHeight) {}

void LayoutProperty::UpdateCalcMinSize(const CalcSize& value) {}

void LayoutProperty::UpdateCalcMaxSize(const CalcSize& value) {}

void LayoutProperty::UpdateMarginSelfIdealSize(const SizeF& value) {}

void LayoutProperty::ResetCalcMinSize() {}

void LayoutProperty::ResetCalcMaxSize() {}

void LayoutProperty::ResetCalcMinSize(bool resetWidth) {}

void LayoutProperty::ResetCalcMaxSize(bool resetWidth) {}

void LayoutProperty::UpdateFlexGrow(float flexGrow) {}

void LayoutProperty::ResetFlexGrow() {}

void LayoutProperty::UpdateFlexShrink(float flexShrink) {}

void LayoutProperty::ResetFlexShrink() {}

void LayoutProperty::UpdateFlexBasis(const Dimension& flexBasis) {}

void LayoutProperty::UpdateAlignSelf(const FlexAlign& flexAlign) {}

void LayoutProperty::ResetAlignSelf() {}

void LayoutProperty::UpdateAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) {}

void LayoutProperty::UpdateChainStyle(const ChainInfo& chainInfo) {}

void LayoutProperty::UpdateBias(const BiasPair& biasPair) {}

void LayoutProperty::UpdateDisplayIndex(int32_t displayIndex) {}

LayoutConstraintF LayoutProperty::CreateContentConstraint() const
{
    return LayoutConstraintF();
}

void LayoutProperty::UpdateLayoutConstraint(const RefPtr<LayoutProperty>& layoutProperty) {}

void LayoutProperty::UpdateVisibility(const VisibleType& value, bool allowTransition, bool isUserSet) {}

void LayoutProperty::SetOverlayOffset(
    const std::optional<Dimension>& overlayOffsetX, const std::optional<Dimension>& overlayOffsetY)
{}

void LayoutProperty::GetOverlayOffset(Dimension& overlayOffsetX, Dimension& overlayOffsetY) {}

void LayoutProperty::UpdateAllGeometryTransition(const RefPtr<UINode>& parent) {}

std::pair<bool, bool> LayoutProperty::GetPercentSensitive()
{
    return { false, false };
}

std::pair<bool, bool> LayoutProperty::UpdatePercentSensitive(bool width, bool height)
{
    return { false, false };
}

bool LayoutProperty::ConstraintEqual(const std::optional<LayoutConstraintF>& preLayoutConstraint,
    const std::optional<LayoutConstraintF>& preContentConstraint)
{
    return false;
}

void LayoutProperty::CheckPositionLocalizedEdges(TextDirection layoutDirection) {}

void LayoutProperty::CheckMarkAnchorPosition(TextDirection layoutDirection) {}

void LayoutProperty::CheckOffsetLocalizedEdges(TextDirection layoutDirection) {}

void LayoutProperty::CheckLocalizedBorderRadiuses(const TextDirection& direction) {}

void LayoutProperty::CheckLocalizedOuterBorderColor(const TextDirection& direction) {}

void LayoutProperty::CheckLocalizedPadding(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction)
{}

void LayoutProperty::CheckLocalizedMargin(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction)
{}

void LayoutProperty::CheckLocalizedSafeAreaPadding(const TextDirection& direction) {}

void LayoutProperty::CheckIgnoreLayoutSafeArea(const TextDirection& direction) {}

void LayoutProperty::CheckBackgroundLayoutSafeAreaEdges(const TextDirection& direction) {}

void LayoutProperty::LocalizedPaddingOrMarginChange(
    const PaddingProperty& value, std::unique_ptr<PaddingProperty>& padding)
{}

void LayoutProperty::CheckLocalizedEdgeWidths(
    const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction)
{}

void LayoutProperty::CheckLocalizedEdgeColors(const TextDirection& direction) {}

void LayoutProperty::CheckLocalizedBorderImageSlice(const TextDirection& direction) {}

void LayoutProperty::CheckLocalizedBorderImageWidth(const TextDirection& direction) {}

void LayoutProperty::CheckLocalizedBorderImageOutset(const TextDirection& direction) {}

std::string LayoutProperty::LayoutInfoToString()
{
    return std::string();
}

RefPtr<GeometryTransition> LayoutProperty::GetGeometryTransition() const
{
    return geometryTransition_.Upgrade();
}

void LayoutProperty::CheckLocalizedAlignment(const TextDirection& direction) {}

std::string LayoutProperty::GetAlignmentStringFromLocalized(
    TextDirection layoutDirection, std::string localizedAlignment)
{
    return "center";
}

void LayoutProperty::UpdateIsUserSetBackgroundColor(bool value)
{
    isUserSetBackgroundColor_ = value;
}
bool LayoutProperty::GetIsUserSetBackgroundColor() const
{
    return isUserSetBackgroundColor_;
}
} // namespace OHOS::Ace::NG
