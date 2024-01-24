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

#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class SwiperAttrTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: AttrIndex001
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set index
     * @tc.expected: Default show(size>0) first item
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f); // item size > 0
}

/**
 * @tc.name: AttrIndex002
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex002, TestSize.Level1)
{
    /**
     * @tc.cases: Set index:1
     * @tc.expected: Default show(size>0) second item
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndex(1); });
    EXPECT_GT(GetChildWidth(frameNode_, 1), 0.f);
}

/**
 * @tc.name: AttrIndex003
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex003, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid index:-1
     * @tc.expected: Default show(size>0) first item
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndex(-1); });
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f);
}

/**
 * @tc.name: AttrIndex004
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex004, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid index:ITEM_NUMBER(index>maxIndex)
     * @tc.expected: Default show(size>0) first item
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndex(ITEM_NUMBER); });
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f);
}

/**
 * @tc.name: AttrAutoPlay001
 * @tc.desc: Test property about autoPlay/interval/loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrAutoPlay001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set value
     * @tc.expected: AutoPlay is false, interval is default, isLoop is true
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_FALSE(pattern_->IsAutoPlay());
    EXPECT_EQ(pattern_->GetInterval(), DEFAULT_INTERVAL);
    EXPECT_TRUE(pattern_->IsLoop());
}

/**
 * @tc.name: AttrAutoPlay002
 * @tc.desc: Test property about autoPlay/interval/loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrAutoPlay002, TestSize.Level1)
{
    /**
     * @tc.cases: Set autoPlay to true
     * @tc.expected: AutoPlay is true
     */
    CreateWithItem([](SwiperModelNG model) { model.SetAutoPlay(true); });
    EXPECT_TRUE(pattern_->IsAutoPlay());
}

/**
 * @tc.name: AttrAutoPlay003
 * @tc.desc: Test property about autoPlay/interval/loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrAutoPlay003, TestSize.Level1)
{
    /**
     * @tc.cases: Set autoPlay to true, set autoPlayInterval to 4000
     * @tc.expected: AutoPlayInterval is 4000
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetAutoPlay(true);
        model.SetAutoPlayInterval(4000);
    });
    EXPECT_EQ(pattern_->GetInterval(), 4000);
}

/**
 * @tc.name: AttrAutoPlay004
 * @tc.desc: Test property about autoPlay/interval/loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrAutoPlay004, TestSize.Level1)
{
    /**
     * @tc.cases: Set autoPlay to true, set loop to false
     * @tc.expected: Loop is false
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetAutoPlay(true);
        model.SetLoop(false);
    });
    EXPECT_FALSE(pattern_->IsLoop());
}

/**
 * @tc.name: AttrIndicator001
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndicator001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set value
     * @tc.expected: Show indicator, indicator type is DOT
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_TRUE(pattern_->IsShowIndicator());
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
}

/**
 * @tc.name: AttrIndicator002
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndicator002, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DIGIT
     * @tc.expected: Show indicator, indicator type is DIGIT
     */
    CreateWithItem([](SwiperModelNG model) { model.SetIndicatorType(SwiperIndicatorType::DIGIT); });
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
}

/**
 * @tc.name: AttrDuration001
 * @tc.desc: Test property about duration
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDuration001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set duration
     * @tc.expected: Duration is default
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetDuration(), DEFAULT_DURATION);
}

/**
 * @tc.name: AttrDuration002
 * @tc.desc: Test property about duration
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDuration002, TestSize.Level1)
{
    /**
     * @tc.cases: Set duration to 500
     * @tc.expected: Duration is 500
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDuration(500); });
    EXPECT_EQ(pattern_->GetDuration(), 500);
}

/**
 * @tc.name: AttrVertical001
 * @tc.desc: Test property about vertical
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrVertical001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set direction
     * @tc.expected: Axis is HORIZONTAL
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: AttrVertical002
 * @tc.desc: Test property about vertical
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrVertical002, TestSize.Level1)
{
    /**
     * @tc.cases: Set direction to VERTICAL
     * @tc.expected: Axis is VERTICAL
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDirection(Axis::VERTICAL); });
    EXPECT_EQ(pattern_->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: AttrItemSpace001
 * @tc.desc: Test property about itemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrItemSpace001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set itemSpace
     * @tc.expected: ItemSpace default is 0
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetItemSpace(), 0.f);
}

/**
 * @tc.name: AttrItemSpace002
 * @tc.desc: Test property about itemSpace
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrItemSpace002, TestSize.Level1)
{
    /**
     * @tc.cases: Set itemSpace to 10
     * @tc.expected: ItemSpace is 10
     */
    CreateWithItem([](SwiperModelNG model) { model.SetItemSpace(Dimension(10.f)); });
    EXPECT_EQ(pattern_->GetItemSpace(), 10.f);
}

/**
 * @tc.name: AttrDisplayMode001
 * @tc.desc: Test property about displayMode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayMode001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set displayMode
     * @tc.expected: IsStretch is true
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_TRUE(SwiperUtils::IsStretch(layoutProperty_));
}

/**
 * @tc.name: AttrDisplayMode002
 * @tc.desc: Test property about displayMode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayMode002, TestSize.Level1)
{
    /**
     * @tc.cases: Set displayMode to AUTO_LINEAR
     * @tc.expected: IsStretch is false
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR); });
    EXPECT_FALSE(SwiperUtils::IsStretch(layoutProperty_));
}

/**
 * @tc.name: AttrCachedCount001
 * @tc.desc: Test property about cachedCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrCachedCount001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set cachedCount
     * @tc.expected: CachedCount is 1
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(1), 1);
}

/**
 * @tc.name: AttrCachedCount002
 * @tc.desc: Test property about cachedCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrCachedCount002, TestSize.Level1)
{
    /**
     * @tc.cases: Set cachedCount to 2
     * @tc.expected: CachedCount is 2
     */
    CreateWithItem([](SwiperModelNG model) { model.SetCachedCount(2); });
    EXPECT_EQ(layoutProperty_->GetCachedCountValue(1), 2);
}

/**
 * @tc.name: AttrDisableSwipe001
 * @tc.desc: Test property about disableSwipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisableSwipe001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set disableSwipe
     * @tc.expected: DisableSwipe is false
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_FALSE(pattern_->IsDisableSwipe());
}

/**
 * @tc.name: AttrDisableSwipe002
 * @tc.desc: Test property about disableSwipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisableSwipe002, TestSize.Level1)
{
    /**
     * @tc.cases: Set disableSwipe to true
     * @tc.expected: DisableSwipe is true
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisableSwipe(true); });
    EXPECT_TRUE(pattern_->IsDisableSwipe());
}

/**
 * @tc.name: AttrCurve001
 * @tc.desc: Test property about Curve
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrCurve001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set curve
     * @tc.expected: Curve is null
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetCurve(), nullptr);
}

/**
 * @tc.name: AttrCurve002
 * @tc.desc: Test property about Curve
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrCurve002, TestSize.Level1)
{
    /**
     * @tc.cases: Set curve to SMOOTH
     * @tc.expected: Curve is SMOOTH
     */
    CreateWithItem([](SwiperModelNG model) { model.SetCurve(Curves::SMOOTH); });
    EXPECT_EQ(pattern_->GetCurve(), Curves::SMOOTH);
}

/**
 * @tc.name: AttrDisplayCount001
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set displayCount
     * @tc.expected: DisplayCount is 1
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
}

/**
 * @tc.name: AttrDisplayCount002
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount002, TestSize.Level1)
{
    /**
     * @tc.cases: Set displayCount to 2
     * @tc.expected: DisplayCount is 2
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayCount(2); });
    EXPECT_EQ(pattern_->GetDisplayCount(), 2);
}

/**
 * @tc.name: AttrDisplayCount003
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount003, TestSize.Level1)
{
    /**
     * @tc.cases: Set displayCount to invalid 0
     * @tc.expected: DisplayCount is default 1
     */
    CreateWithItem([](SwiperModelNG model) { model.SetDisplayCount(0); });
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
}

/**
 * @tc.name: AttrDisplayCount004
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount004, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set displayCount
     * @tc.expected: DisplayCount is 1
     */
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    CreateItem();
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);

    /**
     * @tc.cases: Set displayCount to invalid -1
     * @tc.expected: DisplayCount is default 1
     */
    model.SetDisplayCount(AceType::RawPtr(frameNode_), -1);
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);

    /**
     * @tc.cases: Set displayCount to 2
     * @tc.expected: DisplayCount is 2
     */
    model.SetDisplayCount(AceType::RawPtr(frameNode_), 2);
    EXPECT_EQ(pattern_->GetDisplayCount(), 2);
}

/**
 * @tc.name: AttrEdgeEffect001
 * @tc.desc: Test property about EdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set edgeEffect
     * @tc.expected: EdgeEffect is SPRING
     */
    CreateWithItem([](SwiperModelNG model) { model.SetLoop(false); });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::SPRING);
}

/**
 * @tc.name: AttrEdgeEffect002
 * @tc.desc: Test property about EdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrEdgeEffect002, TestSize.Level1)
{
    /**
     * @tc.cases: Set edgeEffect to FADE
     * @tc.expected: EdgeEffect is FADE
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::FADE);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::FADE);
}

/**
 * @tc.name: AttrEdgeEffect003
 * @tc.desc: Test property about EdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrEdgeEffect003, TestSize.Level1)
{
    /**
     * @tc.cases: Set edgeEffect to NONE
     * @tc.expected: EdgeEffect is NONE
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetEdgeEffect(EdgeEffect::NONE);
    });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::NONE);
}

/**
 * @tc.name: AttrMargin001
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set margin
     * @tc.expected: Margin is 0
     */
    CreateWithItem([](SwiperModelNG model) {});
    EXPECT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0.f);
}

/**
 * @tc.name: AttrMargin002
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin002, TestSize.Level1)
{
    /**
     * @tc.cases: Set margin to 10,5
     * @tc.expected: Margin is 10,5
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetNextMargin(Dimension(10.f));
        model.SetPreviousMargin(Dimension(5.f));
    });
    EXPECT_EQ(pattern_->GetNextMargin(), 10.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), 5.f);
}

/**
 * @tc.name: AttrMargin003
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin003, TestSize.Level1)
{
    /**
     * @tc.cases: Set margin to invalid SWIPER_WIDTH+1 (>swiperSize)
     * @tc.expected: Margin is 0
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetNextMargin(Dimension(SWIPER_WIDTH + 1.f));
        model.SetPreviousMargin(Dimension(5));
    });
    EXPECT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0.f);
}

/**
 * @tc.name: AttrMargin004
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin004, TestSize.Level1)
{
    /**
     * @tc.cases: Set margin to invalid SWIPER_WIDTH+1 (>swiperSize)
     * @tc.expected: Margin is 0
     */
    CreateWithItem([](SwiperModelNG model) {
        model.SetNextMargin(Dimension(10.f));
        model.SetPreviousMargin(Dimension(SWIPER_WIDTH + 1.f));
    });
    EXPECT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0.f);
}

/**
 * @tc.name: AttrNestedScroll001
 * @tc.desc: Test property about NestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrNestedScroll001, TestSize.Level1)
{
    /**
     * @tc.cases: NestedScroll is default
     * @tc.expected: enableNestedScroll_ is false
     */
    CreateWithItem([](SwiperModelNG model) { model.SetLoop(false); });
    EXPECT_FALSE(pattern_->IsLoop());
    EXPECT_FALSE(pattern_->enableNestedScroll_);
}

/**
 * @tc.name: AttrNestedScroll002
 * @tc.desc: Test property about NestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrNestedScroll002, TestSize.Level1)
{
    /**
     * @tc.cases: NestedScroll is SELF_FIRST
     * @tc.expected: enableNestedScroll_ is true
     */
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateWithItem([nestedOpt](SwiperModelNG model) {
        model.SetLoop(false);
        model.SetNestedScroll(nestedOpt);
    });
    EXPECT_FALSE(pattern_->IsLoop());
    EXPECT_TRUE(pattern_->enableNestedScroll_);
}

/**
 * @tc.name: AttrDisplayArrow001
 * @tc.desc: Test property about DisplayArrow
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayArrow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper.
     */
    SwiperModelNG model;
    model.Create();
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    CreateItem();
    GetInstance();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. set invalid SwiperArrowParameters.
     * @tc.expected: check whether the properties is correct.
     */
    SwiperArrowParameters swiperArrowParameters;
    model.SetArrowStyle(AceType::RawPtr(frameNode_), swiperArrowParameters);
    EXPECT_FALSE(layoutProperty_->HasIsShowBackground());
    EXPECT_FALSE(layoutProperty_->HasBackgroundSize());
    EXPECT_FALSE(layoutProperty_->HasBackgroundColor());
    EXPECT_FALSE(layoutProperty_->HasArrowSize());
    EXPECT_FALSE(layoutProperty_->HasArrowColor());
    EXPECT_FALSE(layoutProperty_->HasIsSidebarMiddle());

    /**
     * @tc.steps: step3. set valid SwiperArrowParameters.
     * @tc.expected: check whether the properties is correct.
     */
    swiperArrowParameters.isShowBackground = false;
    swiperArrowParameters.isSidebarMiddle = false;
    swiperArrowParameters.backgroundSize = Dimension(24.0);
    swiperArrowParameters.backgroundColor = Color::BLUE;
    swiperArrowParameters.arrowSize = Dimension(24.0);
    swiperArrowParameters.arrowColor = Color::BLUE;
    model.SetArrowStyle(AceType::RawPtr(frameNode_), swiperArrowParameters);
    EXPECT_TRUE(layoutProperty_->GetIsShowBackground());
    EXPECT_TRUE(layoutProperty_->GetIsSidebarMiddle());
    EXPECT_EQ(layoutProperty_->GetBackgroundSize(), Dimension(24.0));
    EXPECT_EQ(layoutProperty_->GetBackgroundColor(), Color::BLUE);
    EXPECT_EQ(layoutProperty_->GetArrowSize(), Dimension(24.0));
    EXPECT_EQ(layoutProperty_->GetArrowColor(), Color::BLUE);
}

} // namespace OHOS::Ace::NG
