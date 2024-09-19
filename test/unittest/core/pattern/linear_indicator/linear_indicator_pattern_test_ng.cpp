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

class LinearIndicatorPatternTestNg : public LinearIndicatorTestNg {
};

/**
 * @tc.name: LinearIndicatorPattern001
 * @tc.desc: Test the function 'CalcProgressWidth' of the class 'LinearIndicatorPattern'.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorPatternTestNg, LinearIndicatorPattern001, TestSize.Level1)
{
    Create();
    float progressWidth = 0.5;
    auto ret = pattern_->CalcProgressWidth(progressWidth);
    EXPECT_TRUE(ret);
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    theme->defaultProgressCount_ = 0;
    float progressWidth1 = 0;
    auto ret1 = pattern_->CalcProgressWidth(progressWidth1);
    EXPECT_TRUE(ret1);
}

/**
 * @tc.name: LinearIndicatorPattern002
 * @tc.desc: Test the function 'VisibleChange' of the class 'LinearIndicatorPattern'.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorPatternTestNg, LinearIndicatorPattern002, TestSize.Level1)
{
    Create();
    pattern_->UpdateProgressNodeAtIndex(4);
    pattern_->isVisibleChangePause_ = true;
    pattern_->VisibleChange(true);
    EXPECT_FALSE(pattern_->isVisibleChangePause_);
    pattern_->isVisibleChangePause_ = false;
    pattern_->VisibleChange(false);
    EXPECT_TRUE(pattern_->isVisibleChangePause_);
}

/**
 * @tc.name: LinearIndicatorPattern003
 * @tc.desc: Test the function 'RegisterVisibleChange' of the class 'LinearIndicatorPattern'.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorPatternTestNg, LinearIndicatorPattern003, TestSize.Level1)
{
    Create();
    pattern_->OnModifyDone();
    EXPECT_FALSE(pattern_->isVisibleChangePause_);
}

/**
 * @tc.name: LinearIndicatorPattern004
 * @tc.desc: Test the function 'IsChangeLayoutPropertyAndUpdate' of the class 'LinearIndicatorPattern'.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorPatternTestNg, LinearIndicatorPattern004, TestSize.Level1)
{
    Create();
    pattern_->DumpInfo();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    theme->defaultStrokeWidth_ = 1.0_vp;
    EXPECT_TRUE(pattern_->IsChangeLayoutPropertyAndUpdate(layoutProperty_));
    theme->defaultStrokeRadius_ = 2.0_vp;
    EXPECT_TRUE(pattern_->IsChangeLayoutPropertyAndUpdate(layoutProperty_));
    theme->trackBackgroundColor_ = Color::BLACK;
    EXPECT_TRUE(pattern_->IsChangeLayoutPropertyAndUpdate(layoutProperty_));
    theme->trackColor_ = Color::RED;
    EXPECT_TRUE(pattern_->IsChangeLayoutPropertyAndUpdate(layoutProperty_));
    pattern_->direction_ = TextDirection::INHERIT;
    EXPECT_TRUE(pattern_->IsChangeLayoutPropertyAndUpdate(layoutProperty_));
}

/**
 * @tc.name: LinearIndicatorPattern005
 * @tc.desc: Test the function 'UpdateProgressNode' of the class 'LinearIndicatorPattern'.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorPatternTestNg, LinearIndicatorPattern005, TestSize.Level1)
{
    Create();
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    ASSERT_NE(theme, nullptr);
    theme->defaultProgressCount_ = 1;
    pattern_->UpdateProgressNode();
    EXPECT_FALSE(pattern_->IsChangeLayoutPropertyAndUpdate(layoutProperty_));
}

/**
 * @tc.name: LinearIndicatorLayoutproperty001
 * @tc.desc: Test the function 'ToJsonValue' of the class 'LinearIndicatorLayoutpropert'.
 * @tc.type: FUNC
 */
HWTEST_F(LinearIndicatorPatternTestNg, LinearIndicatorPattern006, TestSize.Level1)
{
    Create();
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());
    filter.filterFixed = 1;
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}
} // namespace OHOS::Ace::NG