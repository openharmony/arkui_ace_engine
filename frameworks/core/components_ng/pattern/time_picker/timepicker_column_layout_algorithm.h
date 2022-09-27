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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_COLUMN_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_COLUMN_LAYOUT_ALGORITHM_H

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TimePickerColumnLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(TimePickerColumnLayoutAlgorithm, LinearLayoutAlgorithm);

public:
    explicit TimePickerColumnLayoutAlgorithm(float currentOffset) : currentOffset_(currentOffset) {}
    ~TimePickerColumnLayoutAlgorithm() override = default;

    void OnReset() override {}

    void Layout(LayoutWrapper* layoutWrapper) override;

    float GetCurrentOffset() const
    {
        return currentOffset_;
    }

private:
    float currentOffset_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(TimePickerColumnLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TIME_PICKER_TIME_PICKER_COLUMN_LAYOUT_ALGORITHM_H
