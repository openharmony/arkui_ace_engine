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

#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabsEventTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabsController001
 * @tc.desc: Test Tabs controller
 * @tc.type: FUNC
 */
HWTEST_F(TabsEventTestNg, TabsController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set SetAnimationDuration to zero for avoid animation
     * @tc.expected: Show first tabContent by default
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetAnimationDuration(0.f); // for SwipeToWithoutAnimation
    });
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step2. SwipeTo second tabContent
     * @tc.expected: Show second tabContent
     */
    swiperController_->SwipeTo(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);

    /**
     * @tc.steps: step3. SwipeTo same tabContent
     * @tc.expected: Show second tabContent
     */
    swiperController_->SwipeTo(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);

    /**
     * @tc.steps: step4. SwipeTo index that greater than maxIndex
     * @tc.expected: Show first tabContent
     */
    swiperController_->SwipeTo(TABCONTENT_NUMBER);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step5. SwipeTo index that less than zero
     * @tc.expected: Show first tabContent
     */
    swiperController_->SwipeTo(-1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // for update swiper
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
}
} // namespace OHOS::Ace::NG
