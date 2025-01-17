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
    SvgCoordinateSystemContext(Rect boundingBoxBase, Rect containerViewPortBase)
        : boundingBoxBase_(boundingBoxBase), containerViewPortBase_(containerViewPortBase) {}
    const Rect& GetBoundingBoxRect() const
    {
        return boundingBoxBase_;
    }
    SvgLengthScaleRule BuildScaleRule(SvgLengthScaleUnit scaleUnit) const
    {
        if (scaleUnit == SvgLengthScaleUnit::USER_SPACE_ON_USE) {
            return SvgLengthScaleRule(containerViewPortBase_, SvgLengthScaleUnit::USER_SPACE_ON_USE);
        }
        Rect boundingBoxRect(boundingBoxBase_.Left(), boundingBoxBase_.Top(),
            boundingBoxBase_.Width(), boundingBoxBase_.Height());
        return SvgLengthScaleRule(boundingBoxRect, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    }

    SvgLengthScaleRule BuildScaleRule(const std::string& scaleUnit) const
    {
        if (scaleUnit == "userSpaceOnUse") {
            return SvgLengthScaleRule(containerViewPortBase_, SvgLengthScaleUnit::USER_SPACE_ON_USE);
        }
        Rect boundingBoxRect(boundingBoxBase_.Left(), boundingBoxBase_.Top(),
            boundingBoxBase_.Width(), boundingBoxBase_.Height());
        return SvgLengthScaleRule(boundingBoxRect, SvgLengthScaleUnit::OBJECT_BOUNDING_BOX);
    }
private:
    Rect boundingBoxBase_;
    Rect containerViewPortBase_;
};
}
#endif