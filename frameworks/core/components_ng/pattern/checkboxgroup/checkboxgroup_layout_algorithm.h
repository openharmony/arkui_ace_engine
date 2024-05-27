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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_CHECKBOXGROUP_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_CHECKBOXGROUP_LAYOUT_ALGORITHM_H

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT CheckBoxGroupLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(CheckBoxGroupLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    CheckBoxGroupLayoutAlgorithm() = default;

    ~CheckBoxGroupLayoutAlgorithm() override = default;

    void OnReset() override {}

    std::optional<SizeF> MeasureContent(
        const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper) override;

private:
    float defaultWidth_ = 0.0f;
    float defaultHeight_ = 0.0f;
    float horizontalPadding_ = 0.0f;
    float verticalPadding_ = 0.0f;
    Dimension defaultPaddingSize_;

    void InitializeParam();

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxGroupLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CHECKBOXGROUP_CHECKBOXGROUP_LAYOUT_ALGORITHM_H
