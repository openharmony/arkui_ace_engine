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

namespace {
inline float GetRowGap(const RefPtr<GridLayoutProperty>& props, float frameHeight)
{
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    return ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameHeight).value_or(0);
}

inline float GetColumnGap(const RefPtr<GridLayoutProperty>& props, float frameWidth)
{
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    return ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameWidth).value_or(0);
}
} // namespace

float GridUtils::GetMainGap(const RefPtr<GridLayoutProperty>& props, const SizeF& frameSize, Axis axis)
{
    return axis == Axis::HORIZONTAL ? GetColumnGap(props, frameSize.Width()) : GetRowGap(props, frameSize.Height());
}

float GridUtils::GetCrossGap(const RefPtr<GridLayoutProperty>& props, const SizeF& frameSize, Axis axis)
{
    return axis == Axis::HORIZONTAL ? GetRowGap(props, frameSize.Height()) : GetColumnGap(props, frameSize.Width());
}

bool GridUtils::CheckNeedCacheLayout(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    return !layoutWrapper || (layoutWrapper->CheckNeedForceMeasureAndLayout() && !layoutWrapper->CheckHasPreMeasured());
}

} // namespace OHOS::Ace::NG