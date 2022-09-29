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

#include "core/components_ng/pattern/grid/grid_utils.h"

#include <cmath>
#include <iostream>

namespace OHOS::Ace::NG {
namespace {

const char UNIT_RATIO[] = "fr";

} // namespace

std::vector<float> GridUtils::ParseArgs(const std::string& args, float size, float gap)
{
    std::vector<float> lens;
    if (args.empty()) {
        return lens;
    }
    float frSum = 0.0f;
    std::vector<std::string> strs;
    StringUtils::StringSplitter(args, ' ', strs);
    for (const auto& str : strs) {
        if (str.find(UNIT_RATIO) != std::string::npos) {
            frSum += StringUtils::StringToFloat(str);
        }
    }

    float sizeLeft = size - (strs.size() - 1) * gap;
    for (const auto& str : strs) {
        float num = StringUtils::StringToFloat(str);
        if (str.find(UNIT_RATIO) != std::string::npos) {
            lens.push_back(NearZero(frSum) ? 0.0 : sizeLeft / frSum * num);
        } else {
            lens.push_back(0.0);
        }
    }
    return lens;
}

float GridUtils::GetMainGap(const RefPtr<GridLayoutProperty>& gridLayoutProperty, const SizeF& frameSize, Axis axis)
{
    auto scale = gridLayoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(gridLayoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    auto columnsGap =
        ConvertToPx(gridLayoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    return axis == Axis::HORIZONTAL ? columnsGap : rowsGap;
}

float GridUtils::GetCrossGap(const RefPtr<GridLayoutProperty>& gridLayoutProperty, const SizeF& frameSize, Axis axis)
{
    auto scale = gridLayoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(gridLayoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    auto columnsGap =
        ConvertToPx(gridLayoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    return axis == Axis::HORIZONTAL ? rowsGap : columnsGap;
}

} // namespace OHOS::Ace::NG