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

#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/animator/animator_model_ng.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
} // namespace

class AnimatorTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void AnimatorTestNg::SetUpTestSuite() {}

void AnimatorTestNg::TearDownTestSuite() {}

void AnimatorTestNg::SetUp() {}

void AnimatorTestNg::TearDown() {}

/**
 * @tc.name: Test001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AnimatorTestNg, Test001, TestSize.Level1)
{
    AnimatorModelNG aimatorModel;
    aimatorModel.AddEventListener(nullptr, EventOperation::START, "-1");
    aimatorModel.AddEventListener(nullptr, EventOperation::PAUSE, "-1");
    aimatorModel.AddEventListener(nullptr, EventOperation::REPEAT, "-1");
    aimatorModel.AddEventListener(nullptr, EventOperation::CANCEL, "-1");
    aimatorModel.AddEventListener(nullptr, EventOperation::FINISH, "-1");
    aimatorModel.AddEventListener(nullptr, EventOperation::NONE, "-1");

    auto event = []() {};
    aimatorModel.AddEventListener(event, EventOperation::START, "-1");
    aimatorModel.AddEventListener(event, EventOperation::PAUSE, "-1");
    aimatorModel.AddEventListener(event, EventOperation::REPEAT, "-1");
    aimatorModel.AddEventListener(event, EventOperation::CANCEL, "-1");
    aimatorModel.AddEventListener(event, EventOperation::FINISH, "-1");
    aimatorModel.AddEventListener(event, EventOperation::NONE, "-1");

    EXPECT_TRUE(true);
}
} // namespace OHOS::Ace::NG
