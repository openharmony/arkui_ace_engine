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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_SVG_FILTER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_BASE_SVG_FILTER_CONTEXT_H
#include "core/components_ng/svg/base/svg_length_scale_rule.h"
namespace OHOS::Ace::NG {
class SvgFilterContext {
public:
    SvgFilterContext(const Rect &effectFilterArea, const SvgLengthScaleRule &filterRule,
                     const SvgLengthScaleRule &primitiveRule)
        : filterArea_(effectFilterArea), filterRule_(filterRule), primitiveRule_(primitiveRule) {}
    SvgFilterContext() = default;
    ~SvgFilterContext() = default;

    const Rect& GetFilterArea() const
    {
        return filterArea_;
    }
    void SetFilterArea(Rect& filterArea)
    {
        filterArea_ = filterArea;
    }
    const SvgLengthScaleRule& GetFilterRule() const
    {
        return filterRule_;
    }
    void SetFilterRule(const SvgLengthScaleRule& filterRule)
    {
        filterRule_ = filterRule;
    }
    const SvgLengthScaleRule& GetPrimitiveRule() const
    {
        return primitiveRule_;
    }
    void SetPrimitiveRule(const SvgLengthScaleRule& primitiveRule)
    {
        primitiveRule_ = primitiveRule;
    }
private:
    Rect filterArea_;
    SvgLengthScaleRule filterRule_;
    SvgLengthScaleRule primitiveRule_;
};
}
#endif