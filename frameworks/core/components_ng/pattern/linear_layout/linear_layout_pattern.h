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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_PATTERN_H

#include "base/log/dump_log.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
// PagePattern is the base class for page render node.
class LinearLayoutPattern : virtual public Pattern {
    DECLARE_ACE_TYPE(LinearLayoutPattern, Pattern);

public:
    explicit LinearLayoutPattern(bool isVertical) : isVertical_(isVertical) {};
    ~LinearLayoutPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsNeedPercent() const override
    {
        return true;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LinearLayoutProperty>(isVertical_);
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<LinearLayoutAlgorithm>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return { isVertical_, true, ScopeType::FLEX };
    }

    bool GetIsVertical() const
    {
        return isVertical_;
    }

    void SetFlexMeasureResult(FlexMeasureResult measureResult, uintptr_t addr)
    {
        measureResult_ = measureResult;
        measuredAddress_ = addr;
    }

    FlexMeasureResult GetFlexMeasureResult()
    {
        return measureResult_;
    }

    void SetFlexLayoutResult(FlexLayoutResult layoutResult, uintptr_t addr)
    {
        layoutResult_ = layoutResult;
        layoutedAddress_ = addr;
    }

    bool GetMeasureLayoutPaired()
    {
        return (measuredAddress_ && layoutedAddress_ && (measuredAddress_.value() == layoutedAddress_.value()));
    }

    void DumpInfo() override
    {
        DumpLog::GetInstance().AddDesc(std::string("FlexMeasureLayoutPaired: ")
                                           .append(std::to_string(static_cast<int>(GetMeasureLayoutPaired())).c_str()));
        DumpLog::GetInstance().AddDesc(std::string("FlexFrontSpace: ")
                                           .append(std::to_string(layoutResult_.frontSpace).c_str())
                                           .append(std::string(" FlexBetweenSpace: "))
                                           .append(std::to_string(layoutResult_.betweenSpace).c_str()));
    }

    void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) override
    {
        json->Put("FlexMeasureLayoutPaired", GetMeasureLayoutPaired());
        json->Put("FlexFrontSpace", static_cast<double>(layoutResult_.frontSpace));
        json->Put("FlexBetweenSpace", static_cast<double>(layoutResult_.betweenSpace));
    }

private:
    bool isVertical_ = false;
    FlexMeasureResult measureResult_;
    FlexLayoutResult layoutResult_;
    std::optional<uintptr_t> measuredAddress_;
    std::optional<uintptr_t> layoutedAddress_;

    ACE_DISALLOW_COPY_AND_MOVE(LinearLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_LAYOUT_PATTERN_H
