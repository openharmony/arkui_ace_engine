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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_PATTERN_H

#include <optional>

#include "core/common/container.h"
#include "core/components_ng/pattern/counter/counter_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class CounterPattern : public LinearLayoutPattern {
    DECLARE_ACE_TYPE(CounterPattern, LinearLayoutPattern);

public:
    CounterPattern() : LinearLayoutPattern(false) {};
    ~CounterPattern() override = default;

    bool HasSubNode() const
    {
        return subId_.has_value();
    }
    int32_t GetSubId()
    {
        if (!subId_.has_value()) {
            subId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return subId_.value();
    }

    bool HasContentNode() const
    {
        return contentId_.has_value();
    }
    int32_t GetContentId()
    {
        if (!contentId_.has_value()) {
            contentId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return contentId_.value();
    }

    bool HasAddNode() const
    {
        return addId_.has_value();
    }
    int32_t GetAddId()
    {
        if (!addId_.has_value()) {
            addId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return addId_.value();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CounterLayoutAlgorithm>();
    }

    FocusPattern GetFocusPattern() const override
    {
        if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FOURTEEN)) {
            return { FocusType::NODE, false, FocusStyleType::OUTER_BORDER };
        }
        return { FocusType::SCOPE, true, FocusStyleType::OUTER_BORDER };
    }

private:
    std::optional<int32_t> subId_;
    std::optional<int32_t> contentId_;
    std::optional<int32_t> addId_;
    ACE_DISALLOW_COPY_AND_MOVE(CounterPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_COUNTER_COUNTER_PATTERN_H
