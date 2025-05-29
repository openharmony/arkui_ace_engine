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

    const std::optional<LayoutConstraintF>& GetLayoutConstraint() const
    {
        return layoutConstraint_;
    }

    const std::optional<LayoutConstraintF>& GetContentLayoutConstraint() const
    {
        return contentConstraint_;
    }

    const std::optional<LayoutConstraintF>& GetParentLayoutConstraint() const
    {
        return parentLayoutConstraint_;
    }

    MagicItemProperty& GetMagicItemProperty()
    {
        return magicItemProperty_;
    }

    const std::unique_ptr<PaddingProperty>& GetPaddingProperty() const
    {
        return padding_;
    }

    const std::unique_ptr<PaddingProperty>& GetSafeAreaPaddingProperty() const
    {
        return safeAreaPadding_;
    }

    const std::unique_ptr<MarginProperty>& GetMarginProperty() const
    {
        return margin_;
    }

    const std::unique_ptr<BorderWidthProperty>& GetBorderWidthProperty() const
    {
        return borderWidth_;
    }

    const std::unique_ptr<BorderWidthProperty>& GetOuterBorderWidthProperty() const
    {
        return outerBorderWidth_;
    }

    const std::unique_ptr<PositionProperty>& GetPositionProperty() const
    {
        return positionProperty_;
    }

    const std::unique_ptr<MeasureProperty>& GetCalcLayoutConstraint() const
    {
        return calcLayoutConstraint_;
    }

    const std::unique_ptr<FlexItemProperty>& GetFlexItemProperty() const
    {
        return flexItemProperty_;
    }

    TextDirection GetLayoutDirection() const
    {
        return layoutDirection_.value_or(TextDirection::AUTO);
    }

    TextDirection GetNonAutoLayoutDirection() const;

    uint32_t GetBackgroundIgnoresLayoutSafeAreaEdges() const
    {
        return backgroundIgnoresLayoutSafeAreaEdges_.value_or(NG::SAFE_AREA_EDGE_NONE);
    }

    RefPtr<GeometryTransition> GetGeometryTransition() const;

    MeasureType GetMeasureType(MeasureType defaultType = MeasureType::MATCH_CONTENT) const
    {
        return measureType_.value_or(defaultType);
    }

    void LocalizedPaddingOrMarginChange(const PaddingProperty& value, std::unique_ptr<PaddingProperty>& padding);
    void UpdatePadding(const PaddingProperty& value);
    void UpdateSafeAreaPadding(const PaddingProperty& value);
    void ResetSafeAreaPadding();

    void UpdateMargin(const MarginProperty& value);

    void UpdateBorderWidth(const BorderWidthProperty& value);

    void UpdateOuterBorderWidth(const BorderWidthProperty& value);

    void UpdateAlignment(Alignment value);

    void UpdateLayoutWeight(float value);

    void UpdateChainWeight(const ChainWeightPair& value);

    void UpdatePixelRound(uint16_t value)
    {
        pixelRoundFlag_ = value;
    }

    uint16_t GetPixelRound() const {
        return pixelRoundFlag_;
    }

    void UpdateLayoutDirection(TextDirection value);
    void UpdateBackgroundIgnoresLayoutSafeAreaEdges(uint32_t value);

    void UpdateGeometryTransition(const std::string& id,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true);

    void ResetGeometryTransition();

    void UpdateAspectRatio(float ratio);
    void ResetAspectRatio();

    bool HasAspectRatio() const;
    float GetAspectRatio() const;

    bool HasFixedWidth(bool checkPercent = true) const;
    bool HasFixedHeight(bool checkPercent = true) const;

    void UpdateMeasureType(MeasureType measureType)
    {
        if (measureType_ == measureType) {
            return;
        }
        propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        measureType_ = measureType;
    }

    // user defined max, min, self size.
    void UpdateCalcLayoutProperty(const MeasureProperty& constraint);

    void UpdateUserDefinedIdealSize(const CalcSize& value);

    void UpdateLayoutPolicyProperty(const LayoutCalPolicy layoutPolicy, bool isWidth);

    bool UpdateLayoutPolicyWithCheck(const LayoutCalPolicy layoutPolicy, bool isWidth);

    std::optional<NG::LayoutPolicyProperty> GetLayoutPolicyProperty();

    void ClearUserDefinedIdealSize(bool clearWidth, bool clearHeight);

    virtual void UpdateCalcMinSize(const CalcSize& value);

    virtual void UpdateCalcMaxSize(const CalcSize& value);

    std::pair<std::vector<std::string>, std::vector<std::string>> CalcToString(const CalcSize& calcSize);

    virtual void ExpandConstraintWithSafeArea();

    void UpdateLayoutConstraint(const LayoutConstraintF& parentConstraint);

    void UpdateParentLayoutConstraint(const LayoutConstraintF& parentConstraint)
    {
        parentLayoutConstraint_ = parentConstraint;
    }

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

    void SetLayoutRect(const NG::RectF& rect)
    {
        if (layoutRect_ != rect) {
            propertyChangeFlag_ |= PROPERTY_UPDATE_MEASURE_SELF;
            layoutRect_ = rect;
        }
    }

    void ResetLayoutRect()
    {
        if (layoutRect_) {
            propertyChangeFlag_ |= PROPERTY_UPDATE_MEASURE_SELF;
            layoutRect_.reset();
        }
    }

    std::optional<NG::RectF> GetLayoutRect() const
    {
        return layoutRect_;
    }

    void BuildGridProperty(const RefPtr<FrameNode>& host);

    void UpdateContentConstraint();
    void UpdateLayoutConstraintWithLayoutRect();

    LayoutConstraintF CreateChildConstraint() const;

    LayoutConstraintF CreateContentConstraint() const;

    PaddingPropertyF CreatePaddingWithoutBorder(bool useRootConstraint = true, bool roundPixel = true);
    PaddingPropertyF CreatePaddingAndBorder(bool includeSafeAreaPadding = true, bool forceReCreate = false);
    PaddingPropertyF CreatePaddingAndBorderWithDefault(float paddingHorizontalDefault, float paddingVerticalDefault,
        float borderHorizontalDefault, float borderVerticalDefault);
    BorderWidthPropertyF CreateBorder();

    MarginPropertyF CreateMargin();
    MarginPropertyF CreateMarginWithoutCache();

    void SetHost(const WeakPtr<FrameNode>& host);
    RefPtr<FrameNode> GetHost() const;
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsBindOverlay, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_GET(Visibility, VisibleType);

public:
    void UpdateVisibility(const VisibleType& value, bool allowTransition = false, bool isUserSet = false);
    void OnVisibilityUpdate(VisibleType visible, bool allowTransition = false, bool isUserSet = false);
    bool IsUserSetVisibility()
    {
        return isUserSetVisibility_;
    }

    void UpdateLayoutConstraint(const RefPtr<LayoutProperty>& layoutProperty);

    const std::unique_ptr<SafeAreaInsets>& GetSafeAreaInsets() const
    {
        return safeAreaInsets_;
    }

    void UpdateSafeAreaInsets(const SafeAreaInsets& safeArea);

    const std::unique_ptr<SafeAreaExpandOpts>& GetSafeAreaExpandOpts() const
    {
        return safeAreaExpandOpts_;
    }

    void UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts);

    void UpdateIgnoreLayoutSafeAreaOpts(const IgnoreLayoutSafeAreaOpts& opts);

    bool IsExpandConstraintNeeded();

    const std::unique_ptr<IgnoreLayoutSafeAreaOpts>& GetIgnoreLayoutSafeAreaOpts() const
    {
        return ignoreLayoutSafeAreaOpts_;
    }

    bool IsIgnoreOptsValid() const
    {
        return ignoreLayoutSafeAreaOpts_ && ignoreLayoutSafeAreaOpts_->NeedIgnoreLayoutSafeArea();
    }

    bool IsUsingPosition() const
    {
        return usingPosition_;
    }

    void SetUsingPosition(bool usingPosition)
    {
        usingPosition_ = usingPosition;
    }

    void SetIsOverlayNode(bool isOverlayNode)
    {
        isOverlayNode_ = isOverlayNode;
    }

    bool IsOverlayNode() const
    {
        return isOverlayNode_;
    }

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

    void UpdateNeedPositionLocalizedEdges(bool needPositionLocalizedEdges)
    {
        needPositionLocalizedEdges_ = needPositionLocalizedEdges;
    }

    bool IsPositionLocalizedEdges() const
    {
        return needPositionLocalizedEdges_;
    }

    void UpdateNeedOffsetLocalizedEdges(bool needOffsetLocalizedEdges)
    {
        needOffsetLocalizedEdges_ = needOffsetLocalizedEdges;
    }

    bool IsOffsetLocalizedEdges() const
    {
        return needOffsetLocalizedEdges_;
    }

    void ResetMarkAnchorStart()
    {
        markAnchorStart_.reset();
    }

    void UpdateMarkAnchorStart(const Dimension& markAnchorStart)
    {
        markAnchorStart_ = markAnchorStart;
    }

    void SetNeedLazyLayout(bool value)
    {
        needLazyLayout_ = true;
    }

    bool GetNeedLazyLayout() const
    {
        return needLazyLayout_;
    }

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
    void CheckIgnoreLayoutSafeArea(const TextDirection& direction);

    virtual void OnPropertyChangeMeasure() {}

    std::string LayoutInfoToString();

protected:
    void UpdateLayoutProperty(const LayoutProperty* layoutProperty);

    virtual void Clone(RefPtr<LayoutProperty> layoutProperty) const;

private:
    // This will call after ModifyLayoutConstraint.
    void CheckSelfIdealSize(const SizeF& originMax);
    void CheckCalcLayoutConstraint(const LayoutConstraintF& parentConstraint);

    void CheckAspectRatio();
    void CheckBorderAndPadding();
    void ConstraintContentByPadding();
    void ConstraintContentByBorder();
    void ConstraintContentBySafeAreaPadding();
    PaddingPropertyF CreateSafeAreaPadding();
    bool DecideMirror();

    const std::string PixelRoundToJsonValue() const;

    void PaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void MarginToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void IgnoreLayoutSafeAreaToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void SafeAreaExpandToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void SafeAreaPaddingToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    // available in measure process.
    std::optional<LayoutConstraintF> layoutConstraint_;
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

    WeakPtr<GeometryTransition> geometryTransition_;

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

    ACE_DISALLOW_COPY_AND_MOVE(LayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_PROPERTY_H
