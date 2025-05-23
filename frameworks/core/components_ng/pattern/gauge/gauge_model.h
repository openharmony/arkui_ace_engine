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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_H

#include <mutex>

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "frameworks/base/geometry/dimension.h"

namespace OHOS::Ace {
enum class GaugeResourceType {
    STROKE_WIDTH,
    INDICATOR_ICON,
    INDICATOR_SPACE,
};
class ACE_FORCE_EXPORT GaugeModel {
public:
    static GaugeModel* GetInstance();
    virtual ~GaugeModel() = default;

    virtual void Create(float values, float min, float max) = 0;
    virtual void SetValue(float value) = 0;
    virtual void SetStartAngle(float startAngle) = 0;
    virtual void SetEndAngle(float endAngle) = 0;
    virtual void SetColors(const std::vector<Color>& colors, const std::vector<float>& values) = 0;
    virtual void SetGradientColors(
        const std::vector<NG::ColorStopArray>& colors, const std::vector<float>& values, const NG::GaugeType& type) = 0;
    virtual void SetStrokeWidth(const Dimension& strokeWidth) = 0;
    virtual void SetLabelMarkedText(const std::string labelTextString) = 0;
    virtual void SetMarkedTextColor(const Color& color) = 0;
    virtual void SetDescription(const RefPtr<AceType>& customNode) = 0;
    virtual void SetIsShowLimitValue(bool isShowLimitValue) = 0;
    virtual void SetIsShowDescription(bool isShowDescription) = 0;
    virtual void SetShadowOptions(const NG::GaugeShadowOptions& shadowOptions) = 0;
    virtual void SetIsShowIndicator(bool isShowIndicator) = 0;
    virtual void SetIndicatorIconPath(
        const std::string& iconPath, const std::string& bundleName, const std::string& moduleName) = 0;
    virtual void SetIndicatorSpace(const Dimension& space) = 0;
    virtual void ResetGradientColors() = 0;
    virtual void ResetShadowOptions() = 0;
    virtual void ResetIndicatorIconPath() = 0;
    virtual void ResetIndicatorSpace() = 0;
    virtual void CreateWithResourceObj(GaugeResourceType jsResourceType, const RefPtr<ResourceObject>& resObj) = 0;

private:
    static std::unique_ptr<GaugeModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_H