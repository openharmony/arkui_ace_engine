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

#include "core/components_ng/property/calc_length.h"

#include "base/utils/string_expression.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

ScaleProperty ScaleProperty::CreateScaleProperty(PipelineBase* context)
{
    ScaleProperty scaleProperty;
    auto pipeline = context ? AceType::Claim(context) : PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, scaleProperty);
    scaleProperty.fpScale = pipeline->GetFontScale();
    scaleProperty.vpScale = static_cast<float>(pipeline->GetDipScale());
    scaleProperty.lpxScale = static_cast<float>(pipeline->GetLogicScale());
    return scaleProperty;
}

bool CalcLength::NormalizeToPx(double vpScale, double fpScale, double lpxScale, double parentLength, double& result,
    const std::vector<std::string>& rpnexp) const
{
    // don't use this function for calc.
    if (!calcValue_.empty()) {
        result = StringExpression::CalculateExp(
            calcValue_,
            [vpScale, fpScale, lpxScale, parentLength](const Dimension& dim) -> double {
                double result = -1.0;
                dim.NormalizeToPx(vpScale, fpScale, lpxScale, parentLength, result);
                return result;
            },
            rpnexp);
        return result >= 0;
    }
    return dimension_.NormalizeToPx(vpScale, fpScale, lpxScale, parentLength, result);
}

} // namespace OHOS::Ace::NG
