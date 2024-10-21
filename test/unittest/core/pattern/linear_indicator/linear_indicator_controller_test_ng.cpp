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
#include "linear_indicator_test_ng.h"

namespace OHOS::Ace::NG {
using STATE = LinearIndicatorControllerDataState;

class LinearIndicatorControllerTestNg : public LinearIndicatorTestNg {};

/**
 * @tc.name: LinearIndicatorController001
 * @tc.desc: Test function of LinearIndicatorController.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorControllerTestNg, LinearIndicatorController001, TestSize.Level1)
{
    auto onChange = [](int index, float progress) {};
    Create([&](LinearIndicatorModelNG model) {
        model.SetSpace(Dimension(4.0_vp));
        model.SetStrokeWidth(Dimension(2.0_vp));
        model.SetStrokeRadius(Dimension(1.0_vp));
        model.SetTrackBackgroundColor(Color(0X0C182431));
        model.SetTrackColor(Color(0xFF007DFF));
        model.SetSpace(Dimension(10.0f));
        model.Loop(true);
        model.OnChange(onChange);
    });
    EXPECT_NE(controller_, nullptr);
    controller_->Start(0, -1);
    controller_->SetProgressValue(36.6f);
    EXPECT_EQ(controller_->animationData_.State(), STATE::ANIMATION);
    controller_->Pause();
    EXPECT_EQ(controller_->animationData_.State(), STATE::ANIMATION_PAUSE);
    controller_->Start(1, 0);
    EXPECT_EQ(controller_->animationData_.State(), STATE::ANIMATION);
    controller_->Start(2, 1);
    controller_->Stop();
    EXPECT_EQ(controller_->animationData_.State(), STATE::STOP);
}

/**
 * @tc.name: LinearIndicatorController002
 * @tc.desc: Test function of LinearIndicatorController.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorControllerTestNg, LinearIndicatorController002, TestSize.Level1)
{
    auto onChange = [](int index, float progress) {};
    Create([&](LinearIndicatorModelNG model) {
        model.Loop(true);
        model.OnChange(onChange);
    });
    EXPECT_NE(controller_, nullptr);
    controller_->Start(0, -1);
    EXPECT_EQ(controller_->animationData_.State(), STATE::ANIMATION);
    controller_->SetProgress(3, 10);
    controller_->UpdateProgressSize(2);
    controller_->StartProgressInterval(-1);
    EXPECT_EQ(controller_->animationData_.State(), STATE::INTERVAL);
    controller_->Start(3, 1);
    controller_->Pause();
    EXPECT_EQ(controller_->animationData_.State(), STATE::INTERVAL_PAUSE);
    controller_->Stop();
    EXPECT_EQ(controller_->animationData_.State(), STATE::STOP);
}

/**
 * @tc.name: LinearIndicatorController003
 * @tc.desc: Test function of LinearIndicatorController.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorControllerTestNg, LinearIndicatorController003, TestSize.Level1)
{
    auto onChange = [](int index, float progress) {};
    Create([&](LinearIndicatorModelNG model) {
        model.Loop(false);
        model.OnChange(onChange);
    });
    EXPECT_NE(controller_, nullptr);
    controller_->Start(0, -1);
    EXPECT_EQ(controller_->animationData_.State(), STATE::ANIMATION);
    controller_->ProgreAnimationEnd();
    controller_->SetProgress(2, 8);
    EXPECT_EQ(controller_->animationData_.State(), STATE::INTERVAL);
    controller_->Start(1, 9);
    controller_->GetHost()->children_.clear();
    controller_->ProgreAnimationEnd();
    EXPECT_EQ(controller_->animationData_.State(), STATE::STOP);
}
} // namespace OHOS::Ace::NG
