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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_LENGTH_SCALE_RULE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_LENGTH_SCALE_RULE_H

#include "base/geometry/rect.h"

namespace OHOS::Ace::NG {

enum class SvgLengthType {
    HORIZONTAL = 0,
    VERTICAL,
    OTHER,
};

enum class SvgLengthScaleUnit {
    USER_SPACE_ON_USE = 0,
    OBJECT_BOUNDING_BOX,
};

class SvgLengthScaleRule {
public:
    SvgLengthScaleRule(Rect baseRect, SvgLengthScaleUnit lengthScaleUnit) : baseRect_(baseRect),
        lengthScaleUnit_(lengthScaleUnit) {}
    SvgLengthScaleRule() = default;
    ~SvgLengthScaleRule() = default;
    SvgLengthScaleUnit GetLengthScaleUnit() const
    {
        return lengthScaleUnit_;
    }
    const Rect& GetBaseRect() const
    {
        return baseRect_;
    }
    bool operator==(const SvgLengthScaleRule& lengthRule)
    {
        return baseRect_ == lengthRule.GetBaseRect() && lengthScaleUnit_ == lengthRule.GetLengthScaleUnit();
    }
    void SetPathTransform(bool transform)
    {
        pathTransform_ = transform;
        return ;
    }
    bool GetPathTransform() const
    {
        return pathTransform_;
    }
private:
    Rect baseRect_;
    SvgLengthScaleUnit lengthScaleUnit_;
    bool pathTransform_ = false;
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_LENGTH_SCALE_RULE_H