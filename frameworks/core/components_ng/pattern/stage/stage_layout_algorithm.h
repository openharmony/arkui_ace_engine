/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_LAYOUT_ALGORITHM_H

#include "base/memory/ace_type.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Ace::NG {
// not in use
// Stage using default BoxLayoutAlgorithm
class [[deprecated]] StageLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(StageLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    StageLayoutAlgorithm() = default;
    ~StageLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    SafeAreaInsets childInsets_;

    ACE_DISALLOW_COPY_AND_MOVE(StageLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_STAGE_LAYOUT_ALGORITHM_H
