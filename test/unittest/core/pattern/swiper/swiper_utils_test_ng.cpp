/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {
class SwiperUtilsTestNg : public SwiperTestNg {};

/**
 * @tc.name: SwiperUtilsTest001
 * @tc.desc: Test Swiper measure and layout function, set prevMargin and nextMargin property is 50_px.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    LayoutConstraintF layoutConstraint;
    layoutConstraint.Reset();
    layoutConstraint.selfIdealSize = OptionalSize(SizeF(720.f, 1200.f));
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();
    int32_t displayCount = 3;
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(displayCount);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    layoutProperty_->UpdateShowIndicator(false);
    layoutProperty_->UpdateLoop(false);
    auto swiperLayoutAlgorithm = AceType::DynamicCast<SwiperLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    swiperLayoutAlgorithm->currentIndex_ = 1;
    for (int32_t index = 0; index < 4; index++) {
        auto childLayout = frameNode_->GetOrCreateChildByIndex(index);
        ASSERT_NE(childLayout, nullptr);
    }
}

/**
 * @tc.name: SwiperUtilsTest002
 * @tc.desc: Verify the CreateChildConstraint function when DisplayCount is -1.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest002, TestSize.Level2)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateDisplayCount(-1);
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest003
 * @tc.desc: Verify the CreateChildConstraint function when DisplayMode is AUTO_LINEAR.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest003, TestSize.Level2)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateSwiperItems();
    CreateSwiperDone();
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest004
 * @tc.desc: Verify the CreateChildConstraint function when NextMargin is normal and abnormal.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest004, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);

    layoutProperty_->UpdateNextMargin(Dimension(600));
    result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest005
 * @tc.desc: Verify the CreateChildConstraint function does not set a value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest005, TestSize.Level2)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest006
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest006, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);

    layoutProperty_->UpdateNextMargin(Dimension(600));
    result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest007
 * @tc.desc: Verify the CreateChildConstraint function when Direction is VERTICAL and does not set value for setSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest007, TestSize.Level2)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::VERTICAL);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize;
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}

/**
 * @tc.name: SwiperUtilsTest008
 * @tc.desc: Verify the CreateChildConstraint function when Direction is FREE.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperUtilsTestNg, SwiperUtilsTest008, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    layoutProperty_->UpdateIndex(1);
    layoutProperty_->UpdateItemSpace(Dimension(20));
    layoutProperty_->UpdateCachedCount(1);
    layoutProperty_->UpdateDirection(Axis::FREE);
    layoutProperty_->UpdateDisplayCount(3);
    layoutProperty_->UpdatePrevMargin(Dimension(50));
    layoutProperty_->UpdateNextMargin(Dimension(50));
    auto getAutoFill = pattern_->IsAutoFill();
    EXPECT_FALSE(getAutoFill);

    OptionalSizeF setSize = OptionalSize(SizeF(720.f, 1200.f));
    auto result = SwiperUtils::CreateChildConstraint(layoutProperty_, setSize, getAutoFill);
    EXPECT_EQ(result.parentIdealSize, setSize);
}
} // namespace OHOS::Ace::NG
