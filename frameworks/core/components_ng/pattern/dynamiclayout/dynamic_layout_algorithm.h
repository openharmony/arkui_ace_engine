/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_ALGORITHM_H

#include "core/components_ng/layout/layout_algorithm.h"

namespace OHOS::Ace::NG {
class CustomLayoutAlgorithmParam;
class ACE_EXPORT DynamicLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(DynamicLayoutAlgorithm, LayoutAlgorithm);

public:
    DynamicLayoutAlgorithm() {}
    explicit DynamicLayoutAlgorithm(const RefPtr<CustomLayoutAlgorithmParam> &param);
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
private:
    RefPtr<CustomLayoutAlgorithmParam> customParams_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_ALGORITHM_H