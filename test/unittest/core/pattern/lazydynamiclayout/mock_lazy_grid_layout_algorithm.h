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

#ifndef FOUNDATION_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_LAZYDYNAMICLAYOUT_LAZY_CUSTOM_COLUMN_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_LAZYDYNAMICLAYOUT_LAZY_CUSTOM_COLUMN_LAYOUT_ALGORITHM_H

#ifndef private
    #define private public
#endif
#ifndef protected
    #define protected public
#endif
#include "core/components_ng/pattern/lazy_grid_layout/lazy_grid_layout_algorithm.h"

namespace OHOS::Ace::NG {

class MockLazyGridLayoutAlgorithm : public LazyGridLayoutAlgorithm {
    DECLARE_ACE_TYPE(MockLazyGridLayoutAlgorithm, LazyGridLayoutAlgorithm);
public:
    MockLazyGridLayoutAlgorithm(RefPtr<LazyGridLayoutInfo> info) : LazyGridLayoutAlgorithm(info) {}
    void Measure(LayoutWrapper* layoutWrapper) override;

private:
    void LayoutCachedItems(LayoutWrapper* layoutWrapper, float crossSize, const OffsetF& paddingOffset) override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_ENGINE_TEST_UNITTEST_CORE_PATTERN_LAZYDYNAMICLAYOUT_LAZY_CUSTOM_COLUMN_LAYOUT_ALGORITHM_H