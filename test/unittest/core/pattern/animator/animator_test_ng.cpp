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

#include "core/components_ng/pattern/animator/animator_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
void AnimatorModelNG::Create(const std::string& animatorId) {}

RefPtr<AnimatorInfo> AnimatorModelNG::GetAnimatorInfo(const std::string& animatorId)
{
    auto animatorInfo = AceType::MakeRefPtr<AnimatorInfo>();
    auto animator = AceType::MakeRefPtr<Animator>();
    animatorInfo->SetAnimator(animator);
    return animatorInfo;
}
} // namespace OHOS::Ace::Framework

namespace OHOS::Ace::NG {
class AnimatorTestNg : public testing::Test {};

/**
 * @tc.name: Test001
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(AnimatorTestNg, Test001, TestSize.Level1)
{
    Framework::AnimatorModelNG aimatorModel;
    aimatorModel.AddEventListener(nullptr, Framework::EventOperation::START, "-1");
    aimatorModel.AddEventListener(nullptr, Framework::EventOperation::PAUSE, "-1");
    aimatorModel.AddEventListener(nullptr, Framework::EventOperation::REPEAT, "-1");
    aimatorModel.AddEventListener(nullptr, Framework::EventOperation::CANCEL, "-1");
    aimatorModel.AddEventListener(nullptr, Framework::EventOperation::FINISH, "-1");
    aimatorModel.AddEventListener(nullptr, Framework::EventOperation::NONE, "-1");
    auto eventOperation = static_cast<Framework::EventOperation>(7); // 7 is not a valid EventOperation.
    aimatorModel.AddEventListener(nullptr, eventOperation, "-1");

    auto event = []() {};
    aimatorModel.AddEventListener(event, Framework::EventOperation::START, "-1");
    aimatorModel.AddEventListener(event, Framework::EventOperation::PAUSE, "-1");
    aimatorModel.AddEventListener(event, Framework::EventOperation::REPEAT, "-1");
    aimatorModel.AddEventListener(event, Framework::EventOperation::CANCEL, "-1");
    aimatorModel.AddEventListener(event, Framework::EventOperation::FINISH, "-1");
    aimatorModel.AddEventListener(event, Framework::EventOperation::NONE, "-1");
    aimatorModel.AddEventListener(event, eventOperation, "-1");

    EXPECT_TRUE(true);
}
} // namespace OHOS::Ace::NG
