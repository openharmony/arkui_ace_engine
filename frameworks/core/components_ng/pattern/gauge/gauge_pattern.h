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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_GAUGE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_GAUGE_PATTERN_H

#include "core/common/container.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/gauge/gauge_accessibility_property.h"
#include "core/components_ng/pattern/gauge/gauge_layout_algorithm.h"
#include "core/components_ng/pattern/gauge/gauge_layout_property.h"
#include "core/components_ng/pattern/gauge/gauge_paint_method.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class GaugePattern : public Pattern {
    DECLARE_ACE_TYPE(GaugePattern, Pattern);

public:
    GaugePattern() = default;
    ~GaugePattern() override = default;

    bool IsAtomicNode() const override
    {
        return Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN) ? true : false;
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<GaugePaintMethod>(WeakClaim(this));
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<GaugePaintProperty>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<GaugeLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<GaugeLayoutAlgorithm>(indicatorIconLoadingCtx_);
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<GaugeAccessibilityProperty>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, false, FocusStyleType::OUTER_BORDER };
    }

    bool HasDescriptionNode() const
    {
        return descriptionNodeId_.has_value();
    }

    bool HasMinValueTextNode() const
    {
        return minValueTextId_.has_value();
    }

    bool HasMaxValueTextNode() const
    {
        return maxValueTextId_.has_value();
    }

    bool HasTitleChildNode() const
    {
        return titleChildId_.has_value();
    }

    int32_t GetDescriptionNodeId()
    {
        if (!descriptionNodeId_.has_value()) {
            descriptionNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return descriptionNodeId_.value();
    }

    int32_t GetMinValueTextId()
    {
        if (!minValueTextId_.has_value()) {
            minValueTextId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return minValueTextId_.value();
    }

    int32_t GetMaxValueTextId()
    {
        if (!maxValueTextId_.has_value()) {
            maxValueTextId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return maxValueTextId_.value();
    }

    int32_t GetTitleChildId()
    {
        if (!titleChildId_.has_value()) {
            titleChildId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return titleChildId_.value();
    }

    void SetDescriptionNode(const RefPtr<UINode>& descriptionNode)
    {
        descriptionNode_ = descriptionNode;
    }

    const RefPtr<CanvasImage>& GetIndicatorIconCanvasImage() const
    {
        return indicatorIconCanvasImage_;
    }

    void OnModifyDone() override;

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void InitDescriptionNode();
    void InitLimitValueText(const int32_t valueTextId, const bool isMin);
    void InitIndicatorImage();

    LoadSuccessNotifyTask CreateLoadSuccessCallback();
    DataReadyNotifyTask CreateDataReadyCallback();
    LoadFailNotifyTask CreateLoadFailCallback();
    void OnImageDataReady();
    void OnImageLoadSuccess();
    void OnImageLoadFail();

    Color GetMaxValueColor(const RefPtr<GaugePaintProperty>& gaugePaintProperty) const;
    std::optional<int32_t> descriptionNodeId_;
    std::optional<int32_t> minValueTextId_;
    std::optional<int32_t> maxValueTextId_;
    std::optional<int32_t> titleChildId_;
    RefPtr<UINode> descriptionNode_;

    RefPtr<ImageLoadingContext> indicatorIconLoadingCtx_;
    RefPtr<CanvasImage> indicatorIconCanvasImage_;

    ACE_DISALLOW_COPY_AND_MOVE(GaugePattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_GAUGE_PATTERN_H
