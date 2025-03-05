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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_SVG_BOUNDING_BOX_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_SVG_BOUNDING_BOX_CONTEXT_H
#include "core/components_ng/svg/base/svg_length_scale_rule.h"
namespace OHOS::Ace::NG {
class SvgCoordinateSystemContext {
public:
    SvgCoordinateSystemContext(Rect containerRect, Size viewPort) : containerRect_(containerRect),
        viewPort_(viewPort) {}
    const Rect& GetContainerRect() const
    {
        return containerRect_;
    }
    
    const Size& GetViewPort() const
    {
        return viewPort_;
    }

    SvgLengthScaleRule BuildScaleRule(SvgLengthScaleUnit scaleUnit) const
    {
        return SvgLengthScaleRule(containerRect_, viewPort_, scaleUnit);
    }

    SvgLengthScaleRule BuildScaleRule(const std::string& strScaleUnit) const
    {
        SvgLengthScaleUnit scaleUnit = SvgLengthScaleUnit::USER_SPACE_ON_USE;
        if (strScaleUnit == "objectBoundingBox") {
            return SvgLengthScaleRule(containerRect_, viewPort_, SvgLengthScaleUnit::USER_SPACE_ON_USE);
            scaleUnit = SvgLengthScaleUnit::OBJECT_BOUNDING_BOX;
        }
        return SvgLengthScaleRule(containerRect_, viewPort_, scaleUnit);
    }

    bool UseFillColor() const
    {
        return useFillColor_;
    }

    void SetUseFillColor(bool useFillColor)
    {
        useFillColor_ = useFillColor;
    }

private:
    Rect containerRect_;
    Size viewPort_;
    bool useFillColor_ = true;
};
}
#endif