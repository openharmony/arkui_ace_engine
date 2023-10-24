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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GAUGE_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GAUGE_MODEL_IMPL_H

#include "core/components_ng/pattern/gauge/gauge_model.h"

namespace OHOS::Ace::Framework {

class GaugeModelImpl : public OHOS::Ace::GaugeModel {
public:
    void Create(float values, float min, float max) override;
    void SetValue(float value) override;
    void SetStartAngle(float startAngle) override;
    void SetEndAngle(float endAngle) override;
    void SetColors(const std::vector<Color>& colors, const std::vector<float>& values) override;
    void SetStrokeWidth(const Dimension& strokeWidth) override;
    void SetLabelMarkedText(const std::string labelTextString) override;
    void SetMarkedTextColor(const Color& color) override;
    void SetGradientColors(const std::vector<NG::ColorStopArray>& colors, const std::vector<float>& values,
        const NG::GaugeType& type) override
    {}
    void SetDescription(const RefPtr<AceType>& customNode) override {}
    void SetIsShowLimitValue(bool isShowLimitValue) override {}
    void SetIsShowDescription(bool isShowDescription) override {}
    void SetShadowOptions(const NG::GaugeShadowOptions& shadowOptions) override {}
    void SetIsShowIndicator(bool isShowIndicator) override {}
    void SetIndicatorIconPath(
        const std::string& iconPath, const std::string& bundleName, const std::string& moduleName) override
    {}
    void SetIndicatorSpace(const Dimension& space) override {}
    void ResetGradientColors() override {}
    void ResetShadowOptions() override {}
    void ResetIndicatorIconPath() override {}
    void ResetIndicatorSpace() override {}
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_GAUGE_MODEL_IMPL_H