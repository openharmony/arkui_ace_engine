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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_ALGORITHM_H

#include <optional>

#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_info.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyColumnLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(LazyColumnLayoutAlgorithm, LayoutAlgorithm);
public:
    LazyColumnLayoutAlgorithm(RefPtr<LazyColumnLayoutInfo> info) : layoutInfo_(info) {}

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    int32_t GetTotalItemCount() const
    {
        return totalItemCount_;
    }

private:
    RefPtr<LazyColumnLayoutInfo> layoutInfo_;
    
    int32_t totalItemCount_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_ALGORITHM_H
