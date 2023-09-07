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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_NG_H

#include "core/components_ng/pattern/gauge/gauge_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GaugeModelNG : public OHOS::Ace::GaugeModel {
public:
    void Create(float values, float min, float max) override;
    void SetValue(float value) override;
    void SetStartAngle(float startAngle) override;
    void SetEndAngle(float endAngle) override;
    void SetColors(const std::vector<Color>& colors, const std::vector<float>& values) override {}
    void SetGradientColors(
        const std::vector<ColorStopArray>& colors, const std::vector<float>& values, const GaugeType& type) override;
    void SetStrokeWidth(const Dimension& strokeWidth) override;
    void SetLabelMarkedText(std::string labelTextString) override;
    void SetMarkedTextColor(const Color color) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GAUGE_MODEL_NG_H