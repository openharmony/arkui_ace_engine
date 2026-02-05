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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_PATTERN_H

#include <string>
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
class CustomLayoutAlgorithmParam;
class DynamicLayoutPattern : public Pattern {
    DECLARE_ACE_TYPE(DynamicLayoutPattern, Pattern);
public:
    DynamicLayoutPattern() = default;
    explicit DynamicLayoutPattern(const RefPtr<CustomLayoutAlgorithmParam> &param) : customParams_(param) {}
    ~DynamicLayoutPattern() override = default;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    bool IsAtomicNode() const override;
    void UpdateCustomLayoutAlgorithmParam(const RefPtr<CustomLayoutAlgorithmParam> &param);
private:
    RefPtr<CustomLayoutAlgorithmParam> customParams_;
    ACE_DISALLOW_COPY_AND_MOVE(DynamicLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DYNAMIC_LAYOUT_DYNAMIC_LAYOUT_PATTERN_H