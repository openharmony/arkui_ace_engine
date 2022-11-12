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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_MOCK_LAYOUT_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_MOCK_LAYOUT_WRAPPER_H

#include "gmock/gmock.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
class MockLayoutWrapper : public LayoutWrapper {
public:
    MockLayoutWrapper();
    MOCK_METHOD0(SkipMeasureContent, double());
    MOCK_METHOD0(GetLayoutAlgorithm, const RefPtr<LayoutAlgorithmWrapper>&());
};

class MockLayoutAlgorithmWrapper : public LayoutAlgorithmWrapper {
public:
    MockLayoutAlgorithmWrapper();
    MOCK_METHOD0(GetLayoutAlgorithm, const RefPtr<LayoutAlgorithm>&());
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_MOCK_LAYOUT_WRAPPER_H