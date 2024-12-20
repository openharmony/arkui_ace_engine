/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_AXIS_TEST_NG_H
#define FOUNDATION_ACE_TEST_CORE_PATTERN_SCROLLABLE_SCROLLABLE_AXIS_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ScrollableAxisTestNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    RefPtr<Scrollable> GetScrollable(RefPtr<FrameNode> node);
    void DragStart(RefPtr<Scrollable> scrollable);
    void DragUpdate(RefPtr<Scrollable> scrollable, float offset);
    void DragEnd(RefPtr<Scrollable> scrollable, float velocity);
};
} // namespace OHOS::Ace::NG
#endif