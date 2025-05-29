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
#include "core/components_ng/pattern/gauge/gauge_modifier.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
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
        if (!gaugeModifier_) {
            gaugeModifier_ = AceType::MakeRefPtr<GaugeModifier>(WeakClaim(this));
        }
        gaugeModifier_->SetUseContentModifier(UseContentModifier());
        auto paintMethod = MakeRefPtr<GaugePaintMethod>(WeakClaim(this), gaugeModifier_);
        paintMethod->SetBoundsRect();
        return paintMethod;
    }

    RefPtr<GaugeModifier> GetContentModifier(PaintWrapper* paintWrapper)
    {
        if (!gaugeModifier_) {
            gaugeModifier_ = AceType::MakeRefPtr<GaugeModifier>(WeakClaim(this));
        }
        return gaugeModifier_;
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
    void OnSensitiveStyleChange(bool isSensitive) override;

    void SetBuilderFunc(GaugeMakeCallback&& makeFunc)
    {
        if (makeFunc == nullptr) {
            makeFunc_ = std::nullopt;
            OnModifyDone();
            return;
        }
        makeFunc_ = std::move(makeFunc);
    }

    const RefPtr<FrameNode>& GetContentModifierNode() const
    {
        return contentModifierNode_;
    }

    bool UseContentModifier() const
    {
        return contentModifierNode_ != nullptr;
    }

    void UpdateStrokeWidth(const CalcDimension& strokeWidth, bool isFirstLoad = false);
    void UpdateIndicatorIconPath(const std::string& iconPath, const std::string& bundleName,
        const std::string& moduleName, bool isFirstLoad = false);
    void UpdateIndicatorSpace(const CalcDimension& space, bool isFirstLoad = false);
    void OnColorModeChange(uint32_t colorMode) override;

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    void InitDescriptionNode();
    void InitLimitValueText(int32_t valueTextId, bool isMin);
    void HideLimitValueText(int32_t valueTextId, bool isMin);
    void ObscureText(int32_t valueTextId, bool isSensitive);
    void ObscureLimitValueText(bool isSensitive);
    void InitIndicatorImage();
    void InitTitleContent();
    void FireBuilder();
    RefPtr<FrameNode> BuildContentModifierNode();
    std::optional<GaugeMakeCallback> makeFunc_;
    RefPtr<FrameNode> contentModifierNode_;

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
    RefPtr<GaugeModifier> gaugeModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(GaugePattern);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_GAUGE_PATTERN_H
