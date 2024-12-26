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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LINEAR_INDICATOR_LINEAR_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LINEAR_INDICATOR_LINEAR_TEST_NG_H
#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/linear_indicator/linear_indicator_controller.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_layout_property.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_model.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_model_ng.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_pattern.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class LinearIndicatorTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void Create(const std::function<void(LinearIndicatorModelNG)>& callback = nullptr);

    RefPtr<FrameNode> frameNode_;
    RefPtr<LinearIndicatorPattern> pattern_;
    RefPtr<LinearIndicatorLayoutProperty> layoutProperty_;
    RefPtr<LinearIndicatorController> controller_;
    RefPtr<NG::LinearIndicatorTheme> theme_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_LINEAR_INDICATOR_LINEAR_TEST_NG_H
