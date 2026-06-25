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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H

#include <cstddef>
#include <memory>
#include <optional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/layout_policy_property.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "ui/properties/safe_area_insets.h"

namespace OHOS::Ace::NG {

class FrameNode;
class UINode;
class InspectorFilter;
class GridProperty;
class FlexItemProperty;
struct PositionProperty;
struct SafeAreaExpandOpts;
class GeometryTransition;
struct SafeAreaInsets;
using BiasPair = std::pair<float, float>;
using ChainWeightPair = std::pair<std::optional<float>, std::optional<float>>; // <horizontal,vertical>

class ACE_FORCE_EXPORT LayoutProperty : public Property {
    DECLARE_ACE_TYPE(LayoutProperty, Property);

public:
    LayoutProperty();

    ~LayoutProperty() override;

    virtual RefPtr<LayoutProperty> Clone() const;

    virtual void Reset();

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    virtual void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const {}

    virtual void FromJson(const std::unique_ptr<JsonValue>& json);

    const std::optional<LayoutConstraintF>& GetLayoutConstraint() const;
    const std::optional<LayoutConstraintF>& GetContentLayoutConstraint() const;
    const std::optional<LayoutConstraintF>& GetParentLayoutConstraint() const;
    MagicItemProperty& GetMagicItemProperty();
    const std::unique_ptr<PaddingProperty>& GetPaddingProperty() const;
    const std::unique_ptr<PaddingProperty>& GetSafeAreaPaddingProperty() const;
    const std::unique_ptr<MarginProperty>& GetMarginProperty() const;
    const std::unique_ptr<BorderWidthProperty>& GetBorderWidthProperty() const;
    const std::unique_ptr<BorderWidthProperty>& GetOuterBorderWidthProperty() const;
    const std::unique_ptr<PositionProperty>& GetPositionProperty() const;
    const std::unique_ptr<MeasureProperty>& GetCalcLayoutConstraint() const;
    const std::unique_ptr<FlexItemProperty>& GetFlexItemProperty() const;

    TextDirection GetLayoutDirection() const;

    TextDirection GetNonAutoLayoutDirection() const;

    uint32_t GetBackgroundIgnoresLayoutSafeAreaEdges() const;
    uint32_t GetLocalizedBackgroundIgnoresLayoutSafeAreaEdges() const;
    
    RefPtr<GeometryTransition> GetGeometryTransition() const;

    MeasureType GetMeasureType(MeasureType defaultType = MeasureType::MATCH_CONTENT) const;

    void LocalizedPaddingOrMarginChange(const PaddingProperty& value, std::unique_ptr<PaddingProperty>& padding);
    void UpdatePadding(const PaddingProperty& value);
    void UpdateSafeAreaPadding(const PaddingProperty& value);
    void ResetSafeAreaPadding();

    void UpdateMargin(const MarginProperty& value);

    void UpdateBorderWidth(const BorderWidthProperty& value);

    void UpdateOuterBorderWidth(const BorderWidthProperty& value);

    void UpdateAlignment(Alignment value);

    void UpdateLocalizedAlignment(std::string value);

    void UpdateLayoutGravity(Alignment value);

    void UpdateIsMirrorable(bool value);

    void UpdateLayoutWeight(float value);

    void UpdateChainWeight(const ChainWeightPair& value);

    void UpdatePixelRound(uint16_t value);
    uint16_t GetPixelRound() const;

    void UpdateLayoutDirection(TextDirection value);
    void UpdateBackgroundIgnoresLayoutSafeAreaEdges(uint32_t value);

    void UpdateGeometryTransition(const std::string& id,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true);

    void ResetGeometryTransition();

    void SetGeometryTransitionInfo(const std::string& id,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true);
    std::tuple<std::string, bool, bool> GetGeometryTransitionInfo() const;

    void UpdateAspectRatio(float ratio);
    void ResetAspectRatio();

    bool HasAspectRatio() const;
    float GetAspectRatio() const;

    bool HasFixedWidth(bool checkPercent = true) const;
    bool HasFixedHeight(bool checkPercent = true) const;

    void UpdateMeasureType(MeasureType measureType);

    // user defined max, min, self size.
    void UpdateCalcLayoutProperty(const MeasureProperty& constraint);

    void UpdateUserDefinedIdealSize(const CalcSize& value);

    void MarkUserDefinedHeightConfigured();
    bool HasUserDefinedHeightConfig() const;

    void UpdateLayoutPolicyProperty(const LayoutCalPolicy layoutPolicy, bool isWidth);

    bool UpdateLayoutPolicyWithCheck(const LayoutCalPolicy layoutPolicy, bool isWidth);

    std::optional<NG::LayoutPolicyProperty> GetLayoutPolicyProperty();

    void ClearUserDefinedIdealSize(bool clearWidth, bool clearHeight);

    virtual void UpdateCalcMinSize(const CalcSize& value);

    virtual void UpdateCalcMaxSize(const CalcSize& value);

    void CalcToString(const CalcSize& calcSize, std::pair<std::vector<std::string>, std::vector<std::string>>& result);

    bool IsExpandConstraintDependencySatisfied() const;

    IgnoreLayoutSafeAreaOpts GenIgnoreOpts() const;

    virtual void ExpandConstraintWithSafeArea(RefPtr<FrameNode>& host);

    void UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint);

    void UpdateParentLayoutConstraint(const LayoutConstraintF& parentConstraint);

    void UpdateMarginSelfIdealSize(const SizeF& value);

    void ResetCalcMinSize();

    void ResetCalcMaxSize();

    void ResetCalcMinSize(bool resetWidth);

    void ResetCalcMaxSize(bool resetWidth);

    void UpdateFlexGrow(float flexGrow);

    void ResetFlexGrow();

    void UpdateFlexShrink(float flexShrink);

    void ResetFlexShrink();

    void UpdateFlexBasis(const Dimension& flexBasis);

    void UpdateAlignSelf(const FlexAlign& flexAlign);

    void ResetAlignSelf();

    void UpdateAlignRules(const std::map<AlignDirection, AlignRule>& alignRules);

    void UpdateChainStyle(const ChainInfo& chainInfo);

    void UpdateBias(const BiasPair& biasPair);

    void UpdateDisplayIndex(int32_t displayIndex);

    void UpdateGridProperty(
        std::optional<int32_t> span, std::optional<int32_t> offset, GridSizeType type = GridSizeType::UNDEFINED);

    bool UpdateGridOffset(const RefPtr<FrameNode>& host);

    void SetLayoutRect(const NG::RectF& rect);
    void ResetLayoutRect();
    std::optional<NG::RectF> GetLayoutRect() const;

    void BuildGridProperty(const RefPtr<FrameNode>& host);

    void UpdateContentConstraint();
    void UpdateLayoutConstraintWithLayoutRect();

    LayoutConstraintF CreateChildConstraint() const;

    LayoutConstraintF CreateContentConstraint() const;

    PaddingPropertyF CreatePaddingWithoutBorder(bool useRootConstraint = true, bool roundPixel = true);
    PaddingPropertyF CreatePaddingAndBorder(bool includeSafeAreaPadding = true, bool forceReCreate = false);
    PaddingPropertyF CreatePaddingAndBorderInner(RefPtr<FrameNode>& host,
        bool includeSafeAreaPadding, bool forceReCreate);
    PaddingPropertyF CreatePaddingAndBorderWithDefault(float paddingHorizontalDefault,
        float paddingVerticalDefault, float borderHorizontalDefault, float borderVerticalDefault);
    BorderWidthPropertyF CreateBorder(bool isRoundPixel = false);

    MarginPropertyF CreateMargin();
    MarginPropertyF CreateMarginWithoutCache();

    void SetHost(const WeakPtr<FrameNode>& host);
    RefPtr<FrameNode> GetHost() const;
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsBindOverlay, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(Visibility, VisibleType);

public:
    void UpdateVisibility(const VisibleType& value, bool allowTransition = false, bool isUserSet = false);
    void OnVisibilityUpdate(VisibleType visible, bool allowTransition = false, bool isUserSet = false);
    bool IsUserSetVisibility();

    void UpdateLayoutConstraint(const RefPtr<LayoutProperty>& layoutProperty);

    const std::unique_ptr<SafeAreaInsets>& GetSafeAreaInsets() const;

    void UpdateSafeAreaInsets(const SafeAreaInsets& safeArea);

    const std::unique_ptr<SafeAreaExpandOpts>& GetSafeAreaExpandOpts() const;

    void UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts);

    void UpdateIgnoreLayoutSafeAreaOpts(const IgnoreLayoutSafeAreaOpts& opts);

    bool IsExpandConstraintNeeded();

    const std::unique_ptr<IgnoreLayoutSafeAreaOpts>& GetIgnoreLayoutSafeAreaOpts() const;
    bool IsIgnoreOptsValid() const;
    bool IsUsingPosition() const;
    void SetUsingPosition(bool usingPosition);
    void SetIsOverlayNode(bool isOverlayNode);
    bool IsOverlayNode() const;

    void SetOverlayOffset(
        const std::optional<Dimension>& overlayOffsetX, const std::optional<Dimension>& overlayOffsetY);

    void GetOverlayOffset(Dimension& overlayOffsetX, Dimension& overlayOffsetY);

    static void UpdateAllGeometryTransition(const RefPtr<UINode>& parent);

    // the returned value represents whether to compare percent reference when comparing old and new layout constrains.
    // the first of returned value represents width, and the second of returned value represents height.
    virtual std::pair<bool, bool> GetPercentSensitive();
    std::pair<bool, bool> UpdatePercentSensitive(bool width, bool height);
    bool ConstraintEqual(const std::optional<LayoutConstraintF>& preLayoutConstraint,
        const std::optional<LayoutConstraintF>& preContentConstraint);

    PaddingPropertyF GetOrCreateSafeAreaPadding(bool forceReCreate = false);
    PaddingPropertyF GetOrCreateSafeAreaPaddingInner(RefPtr<FrameNode>& host, bool forceReCreate = false);

    void UpdateNeedPositionLocalizedEdges(bool needPositionLocalizedEdges);
    bool IsPositionLocalizedEdges() const;
    void UpdateNeedOffsetLocalizedEdges(bool needOffsetLocalizedEdges);
    bool IsOffsetLocalizedEdges() const;
    void ResetMarkAnchorStart();
    void UpdateMarkAnchorStart(const Dimension& markAnchorStart);
    void SetNeedLazyLayout(bool value);
    bool GetNeedLazyLayout() const;

    void ConstraintViewPosRef(ViewPosReference& viewPosRef);

    void CheckPositionLocalizedEdges(TextDirection layoutDirection);
    void CheckMarkAnchorPosition(TextDirection layoutDirection);
    void CheckOffsetLocalizedEdges(TextDirection layoutDirection);
    void CheckLocalizedBorderRadiuses(const TextDirection& direction);
    void CheckLocalizedOuterBorderColor(const TextDirection& direction);
    void CheckLocalizedPadding(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction);
    void CheckLocalizedMargin(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction);
    void CheckLocalizedEdgeWidths(const RefPtr<LayoutProperty>& layoutProperty, const TextDirection& direction);
    void CheckLocalizedEdgeColors(const TextDirection& direction);
    void CheckLocalizedBorderImageSlice(const TextDirection& direction);
    void CheckLocalizedBorderImageWidth(const TextDirection& direction);
    void CheckLocalizedBorderImageOutset(const TextDirection& direction);
    void CheckLocalizedSafeAreaPadding(const TextDirection& direction);
    void CheckLocalizedAlignment(const TextDirection& direction);
    void CheckIgnoreLayoutSafeArea(const TextDirection& direction);
    void CheckBackgroundLayoutSafeAreaEdges(const TextDirection& direction);
    bool DecideMirror();

    virtual void OnPropertyChangeMeasure() {}

    std::string LayoutInfoToString();
    std::string GetAlignmentStringFromLocalized(TextDirection layoutDirection, std::string localizedAlignment);

    void UpdateIsUserSetBackgroundColor(bool value);
    bool GetIsUserSetBackgroundColor() const;

protected:
    void UpdateLayoutProperty(const LayoutProperty* layoutProperty);

    virtual void Clone(RefPtr<LayoutProperty> layoutProperty) const;
    std::optional<LayoutConstraintF> layoutConstraint_;

private:
    // This will call after ModifyLayoutConstraint.
    void CheckSelfIdealSize(const SizeF& originMax);
    void CheckCalcLayoutConstraint(RefPtr<FrameNode>& host, const LayoutConstraintF& parentConstraint);

    void CheckAspectRatio();
    void CheckBorderAndPadding(RefPtr<FrameNode>& host);
    void ConstraintContentByPadding();
    void ConstraintContentByBorder();
    void ConstraintContentBySafeAreaPadding();
    PaddingPropertyF CreateSafeAreaPadding(bool adjustingRound = false);
    PaddingPropertyF CreateSafeAreaPaddingInner(RefPtr<FrameNode>& host, bool adjustingRound = false);
    const std::string PixelRoundToJsonValue() const;

    void PaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void MarginToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void IgnoreLayoutSafeAreaToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void SafeAreaExpandToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void SafeAreaPaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    // available in measure process.
    std::optional<LayoutConstraintF> contentConstraint_;

    // layoutConstraint_ set by builderNode
    std::optional<LayoutConstraintF> parentLayoutConstraint_;

    std::unique_ptr<MeasureProperty> calcLayoutConstraint_;
    std::pair<std::vector<std::string>, std::vector<std::string>> calcSelfIdealSizeRpn_;
    std::pair<std::vector<std::string>, std::vector<std::string>> calcMinSizeRpn_;
    std::pair<std::vector<std::string>, std::vector<std::string>> calcMaxSizeRpn_;
    std::unique_ptr<PaddingProperty> safeAreaPadding_;
    std::unique_ptr<PaddingProperty> padding_;
    std::unique_ptr<MarginProperty> margin_;
    std::optional<MarginPropertyF> marginResult_;
    std::optional<NG::LayoutPolicyProperty> layoutPolicy_;

    std::unique_ptr<SafeAreaExpandOpts> safeAreaExpandOpts_;
    std::unique_ptr<IgnoreLayoutSafeAreaOpts> ignoreLayoutSafeAreaOpts_;
    std::unique_ptr<SafeAreaInsets> safeAreaInsets_;

    std::unique_ptr<BorderWidthProperty> borderWidth_;
    std::unique_ptr<BorderWidthProperty> outerBorderWidth_;
    MagicItemProperty magicItemProperty_;
    std::unique_ptr<PositionProperty> positionProperty_;
    std::unique_ptr<FlexItemProperty> flexItemProperty_;
    std::unique_ptr<GridProperty> gridProperty_;
    std::optional<MeasureType> measureType_;
    std::optional<TextDirection> layoutDirection_;
    std::optional<RectF> layoutRect_;
    std::optional<Dimension> markAnchorStart_;
    std::optional<uint32_t> backgroundIgnoresLayoutSafeAreaEdges_;
    std::optional<uint32_t> localizedBackgroundIgnoresLayoutSafeAreaEdges_;

    WeakPtr<GeometryTransition> geometryTransition_;

    std::tuple<std::string, bool, bool> geometryTransitionInfo_ = std::make_tuple("", false, true);

    WeakPtr<FrameNode> host_;

    bool usingPosition_ = true;

    uint16_t pixelRoundFlag_ = 0;

    bool isOverlayNode_ = false;
    Dimension overlayOffsetX_;
    Dimension overlayOffsetY_;

    bool heightPercentSensitive_ = false;
    bool widthPercentSensitive_ = false;
    bool needPositionLocalizedEdges_ = false;
    bool needOffsetLocalizedEdges_ = false;
    bool needLazyLayout_ = false;
    bool isUserSetVisibility_ = false;

    bool isUserSetBackgroundColor_ = false;
    bool userDefinedHeightConfigured_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
