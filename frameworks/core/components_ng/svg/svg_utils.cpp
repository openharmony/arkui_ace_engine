/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/svg/svg_utils.h"

namespace OHOS::Ace::NG {

void SvgUtils::CalculateSvgConentSize(Size& svgContentSize, const Size& svgContainerSize,
    const Size& svgSize, const Rect& viewBox)
{
    if (LessOrEqual(viewBox.Width(), 0.0) || LessOrEqual(viewBox.Height(), 0.0)) {
        svgContentSize.SetWidth(LessNotEqual(svgSize.Width(), 0.0) ? svgContainerSize.Width() : svgSize.Width());
        svgContentSize.SetHeight(LessNotEqual(svgSize.Height(), 0.0) ? svgContainerSize.Height() : svgSize.Height());
        return;
    }
    if (LessNotEqual(svgSize.Width(), 0.0) && LessNotEqual(svgSize.Height(), 0.0)) {
        svgContentSize.SetWidth(svgContainerSize.Width());
        svgContentSize.SetHeight(svgContainerSize.Height());
        return;
    }
    if (LessNotEqual(svgSize.Width(), 0.0)) {
        svgContentSize.SetWidth(viewBox.Width() / viewBox.Height() * svgSize.Height());
        svgContentSize.SetHeight(svgSize.Height());
        return;
    }
    if (LessNotEqual(svgSize.Height(), 0.0)) {
        svgContentSize.SetWidth(svgSize.Width());
        svgContentSize.SetHeight(viewBox.Height() / viewBox.Width() * svgSize.Width());
        return;
    }
    svgContentSize.SetWidth(svgSize.Width());
    svgContentSize.SetHeight(svgSize.Height());
}

bool SvgUtils::IsFeatureEnable(uint32_t featureVersion, uint32_t usrConfigVersion)
{
    if (usrConfigVersion >= featureVersion) {
        return true;
    }
    return false;
}
}