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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_REFRESH_REFRESH_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_REFRESH_REFRESH_TEST_NG_H

#include "test/unittest/core/pattern/scrollable/scrollable_utils_test_ng.h"
#define private public
#define protected public
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float TRIGGER_LOADING_DISTANCE = 16.0;
constexpr float TRIGGER_REFRESH_DISTANCE = 64.0;
constexpr float TRIGGER_REFRESH_WITH_TEXT_DISTANCE = 96.0;
constexpr int32_t DEFAULT_FRICTION_RATIO = 62;
constexpr float PERCENT = 0.01;
constexpr float RATIO = DEFAULT_FRICTION_RATIO * PERCENT;
constexpr float CUSTOM_NODE_WIDTH = 100.f;
constexpr float CUSTOM_NODE_HEIGHT = 10.f;

class RefreshTestNg : public ScrollableUtilsTestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetRefresh();

    RefreshModelNG CreateRefresh();
    void CreateText();
    RefPtr<FrameNode> CreateCustomNode();

    RefPtr<RefreshPattern> pattern_;
    RefPtr<RefreshEventHub> eventHub_;
    RefPtr<RefreshLayoutProperty> layoutProperty_;
    RefPtr<RefreshAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_REFRESH_REFRESH_TEST_NG_H
