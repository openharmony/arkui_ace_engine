/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
class GeneratedScrollTestNg : public ScrollTestNg {
public:
};

/**
* @tc.name: HasOptionWidth001
* @tc.desc: Test the hasOptionWidth flag and its get and set functions.
* @tc.type: FUNC
*/
HWTEST_F(GeneratedScrollTestNg, HasOptionWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Verify the default value of hasOptionWidth.
     * @tc.expected: Default value is false.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_FALSE(pattern_->GetHasOptionWidth());

    /**
     * @tc.steps: step2. Set hasOptionWidth to true and verify.
     * @tc.expected: Value is true after setting.
     */
    pattern_->SetHasOptionWidth(true);
    EXPECT_TRUE(pattern_->GetHasOptionWidth());

    /**
     * @tc.steps: step3. Set hasOptionWidth to false and verify.
     * @tc.expected: Value is false after setting.
     */
    pattern_->SetHasOptionWidth(false);
    EXPECT_FALSE(pattern_->GetHasOptionWidth());
}

/**
 * @tc.name: EnablePaging001
 * @tc.desc: Test enable paging status getter and setter.
 * @tc.type: FUNC
 */
HWTEST_F(GeneratedScrollTestNg, EnablePaging001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Verify default paging status.
     * @tc.expected: Default status is NONE.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::NONE);

    /**
     * @tc.steps: step2. Set paging status to VALID and verify.
     * @tc.expected: Status changes to VALID.
     */
    pattern_->SetEnablePaging(ScrollPagingStatus::VALID);
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::VALID);

    /**
     * @tc.steps: step3. Set paging status to INVALID and verify.
     * @tc.expected: Status changes to INVALID.
     */
    pattern_->SetEnablePaging(ScrollPagingStatus::INVALID);
    EXPECT_EQ(pattern_->GetEnablePaging(), ScrollPagingStatus::INVALID);
}

/**
 * @tc.name: InitialOffset001
 * @tc.desc: Test initial offset configuration handling.
 * @tc.type: FUNC
 */
HWTEST_F(GeneratedScrollTestNg, InitialOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check initial offset default value.
     * @tc.expected: Default offset has zero values.
     */
    CreateScroll();
    CreateContent();
    CreateScrollDone();
    auto defaultOffset = OffsetT<CalcDimension>(CalcDimension(), CalcDimension());
    EXPECT_EQ(pattern_->GetInitialOffset(), defaultOffset);

    /**
     * @tc.steps: step2. Set pixel-based initial offset.
     * @tc.expected: Offset values are stored correctly.
     */
    OffsetT<CalcDimension> pxOffset(CalcDimension(10.0_px), CalcDimension(20.0_px));
    pattern_->SetInitialOffset(pxOffset);
    EXPECT_EQ(pattern_->GetInitialOffset().GetX(), pxOffset.GetX());
    EXPECT_EQ(pattern_->GetInitialOffset().GetY(), pxOffset.GetY());

    /**
     * @tc.steps: step3. Set viewport-based initial offset.
     * @tc.expected: Offset units are preserved correctly.
     */
    OffsetT<CalcDimension> vpOffset(CalcDimension(50.0_vp), CalcDimension(100.0_vp));
    pattern_->SetInitialOffset(vpOffset);
    EXPECT_EQ(pattern_->GetInitialOffset().GetX().Unit(), DimensionUnit::VP);
    EXPECT_EQ(pattern_->GetInitialOffset().GetY().Value(), 100.0);
}

/**
 * @tc.name: NeedSetInitialOffset001
 * @tc.desc: Test initial offset application condition detection.
 * @tc.type: FUNC
 */
HWTEST_F(GeneratedScrollTestNg, NeedSetInitialOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check condition with no initial offset.
     * @tc.expected: No need to apply offset.
     */
    CreateScroll();
    CreateContent();
    EXPECT_FALSE(pattern_->NeedSetInitialOffset());

    /**
     * @tc.steps: step2. Set initial offset before initialization.
     * @tc.expected: Should apply offset before first layout.
     */
    pattern_->SetInitialOffset(OffsetT<CalcDimension>(CalcDimension(10.0_px), CalcDimension()));
    EXPECT_TRUE(pattern_->NeedSetInitialOffset());

    /**
     * @tc.steps: step3. Simulate layout completion and check again.
     * @tc.expected: Should not apply offset after initialization.
     */
    CreateScrollDone();
    EXPECT_FALSE(pattern_->NeedSetInitialOffset());
}

/**
 * @tc.name: SnapAnimation001
 * @tc.desc: Verify snap animation trigger conditions.
 * @tc.type: FUNC
 */
HWTEST_F(GeneratedScrollTestNg, SnapAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Configure valid snap parameters.
     * @tc.expected: Animation starts successfully.
     */
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = { true, true };
    ScrollModelNG model = CreateScroll();
    model.SetScrollSnap(ScrollSnapAlign::START, Dimension(0.f), snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    pattern_->SetSnapOffsets({100.0f});
    FlushUITasks();
    SnapAnimationOptions options = {
        .snapDelta = 10.f,
    };
    EXPECT_TRUE(pattern_->StartSnapAnimation(options));

    /**
     * @tc.steps: step2. Test with invalid/no snap points.
     * @tc.expected: Animation should not start.
     */
    pattern_->SetSnapOffsets({});
    FlushUITasks();
    EXPECT_FALSE(pattern_->StartSnapAnimation(options));
}

} // namespace OHOS::Ace::NG
 