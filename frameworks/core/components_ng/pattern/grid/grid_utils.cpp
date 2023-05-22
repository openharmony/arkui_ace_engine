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

const std::string UNIT_AUTO = "auto";

} // namespace

std::string GridUtils::ParseArgs(const std::string& args)
{
    if (args.empty() || args.find(UNIT_AUTO) == std::string::npos) {
        return args;
    }
    std::string rowsArgs;
    std::vector<std::string> strs;
    StringUtils::StringSplitter(args, ' ', strs);
    std::string current;
    size_t rowArgSize = strs.size();
    for (size_t i = 0; i < rowArgSize; ++i) {
        current = strs[i];
        // "auto" means 1fr in grid
        if (strs[i] == std::string(UNIT_AUTO)) {
            current = "1fr";
        }
        rowsArgs += " " + current;
    }
    return rowsArgs;
}

float GridUtils::GetMainGap(const RefPtr<GridLayoutProperty>& gridLayoutProperty, const SizeF& frameSize, Axis axis)
{
    auto scale = gridLayoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap =
        ConvertToPx(gridLayoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap =
        ConvertToPx(gridLayoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    return axis == Axis::HORIZONTAL ? columnsGap : rowsGap;
}

float GridUtils::GetCrossGap(const RefPtr<GridLayoutProperty>& gridLayoutProperty, const SizeF& frameSize, Axis axis)
{
    auto scale = gridLayoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap =
        ConvertToPx(gridLayoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap =
        ConvertToPx(gridLayoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    return axis == Axis::HORIZONTAL ? rowsGap : columnsGap;
}

} // namespace OHOS::Ace::NG