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
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
namespace OHOS::Ace::NG {
class SwiperAttrTestNg : public SwiperTestNg {};

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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(CurrentIndex(0));
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
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(CurrentIndex(1));
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
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(-1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(CurrentIndex(0));
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
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(ITEM_NUMBER);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(CurrentIndex(0));
}

/**
 * @tc.name: AttrIndex005
 * @tc.desc: Test currentIndex_ when loop change to false.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex005, TestSize.Level1)
{
    /**
     * @tc.cases: Set index=0
     * @tc.expected: When loop change to false, 0 <= currentIndex_ <= totalCount - 1
     */
    SwiperModelNG model = CreateSwiper();
    model.SetIndex(0);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->currentIndex_, 0);
    pattern_->ShowPrevious();
    EXPECT_EQ(pattern_->currentIndex_, -1);
    layoutProperty_->UpdateLoop(false);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->currentIndex_, 3);
}

/**
 * @tc.name: AttrIndex006
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex006, TestSize.Level1)
{
    /**
     * @tc.cases: Set invalid index = ITEM_NUMBER - 1, loop = false, displayCount = 2
     * @tc.expected: Can not reach to ITEM_NUMBER - 1, show the item ITEM_NUMBER - 2
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayCount(2);
    model.SetIndex(ITEM_NUMBER - 1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(CurrentIndex(ITEM_NUMBER - 2));
}

/**
 * @tc.name: AttrIndex007
 * @tc.desc: Test property about index
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndex007, TestSize.Level1)
{
    /**
     * @tc.cases: Set index = ITEM_NUMBER - 2, loop = false, displayCount = 2
     * @tc.expected: Default show currentIndex_ = ITEM_NUMBER - 2 item
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayCount(2);
    model.SetIndex(ITEM_NUMBER - 2);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(CurrentIndex(ITEM_NUMBER - 2));
}

/**
 * @tc.name: AttrAutoPlay001
 * @tc.desc: Test property about autoPlay/interval/loop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrAutoPlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Do not set value
     * @tc.expected: AutoPlay is false, interval is default, isLoop is true
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetAutoPlay(true);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetAutoPlay(true);
    model.SetAutoPlayInterval(4000);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetAutoPlay(true);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
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
     * @tc.steps: step1. Do not set value
     * @tc.expected: Show indicator, indicator type is DOT
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->IsShowIndicator());
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 5); // 4 items and indicator
    EXPECT_EQ(indicatorNode_->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 4), RectF(196.05f, 768.02f, 87.9f, 31.98f)));

    auto wrapper = indicatorNode_->CreatePaintWrapper();
    auto paintMethod = AceType::DynamicCast<DotIndicatorPaintMethod>(wrapper->nodePaintImpl_);
    EXPECT_FALSE(paintMethod->dotIndicatorModifier_->indicatorMask_);
    EXPECT_EQ(paintMethod->dotIndicatorModifier_->unselectedColor_->Get(), Color::FromString("#182431"));
    EXPECT_EQ(paintMethod->dotIndicatorModifier_->selectedColor_->Get().ToColor(), Color::FromString("#007DFF"));
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(3.f);
    itemHalfSizes.emplace_back(3.f);
    itemHalfSizes.emplace_back(3.f);
    itemHalfSizes.emplace_back(3.f);
    EXPECT_EQ(paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get(), itemHalfSizes);
}

/**
 * @tc.name: AttrIndicator002
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set value
     * @tc.expected: Show indicator, indicator type is DOT
     */
    SwiperParameters swiperParameters;
    swiperParameters.dimLeft = std::make_optional<Dimension>(10.f);
    swiperParameters.dimTop = std::make_optional<Dimension>(10.f);
    swiperParameters.dimRight = std::make_optional<Dimension>(10.f);
    swiperParameters.dimBottom = std::make_optional<Dimension>(10.f);
    swiperParameters.itemWidth = std::make_optional<Dimension>(10.f);
    swiperParameters.itemHeight = std::make_optional<Dimension>(10.f);
    swiperParameters.selectedItemWidth = std::make_optional<Dimension>(10.f);
    swiperParameters.selectedItemHeight = std::make_optional<Dimension>(10.f);
    swiperParameters.maskValue = std::make_optional<bool>(true);
    swiperParameters.colorVal = std::make_optional<Color>(Color::RED);
    swiperParameters.selectedColorVal = std::make_optional<Color>(Color::GREEN);
    SwiperModelNG model = CreateSwiper();
    model.SetDotIndicatorStyle(swiperParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->IsShowIndicator());
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DOT);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 5); // 4 items and indicator
    EXPECT_EQ(indicatorNode_->GetTag(), V2::SWIPER_INDICATOR_ETS_TAG);
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 4), RectF(10.f, 10.f, 114.5f, 37.3f)));

    auto wrapper = indicatorNode_->CreatePaintWrapper();
    auto paintMethod = AceType::DynamicCast<DotIndicatorPaintMethod>(wrapper->nodePaintImpl_);
    EXPECT_TRUE(paintMethod->dotIndicatorModifier_->indicatorMask_);
    EXPECT_EQ(paintMethod->dotIndicatorModifier_->unselectedColor_->Get(), Color::RED);
    EXPECT_EQ(paintMethod->dotIndicatorModifier_->selectedColor_->Get().ToColor(), Color::GREEN);
    LinearVector<float> itemHalfSizes;
    itemHalfSizes.emplace_back(5.f);
    itemHalfSizes.emplace_back(5.f);
    itemHalfSizes.emplace_back(5.f);
    itemHalfSizes.emplace_back(5.f);
    EXPECT_EQ(paintMethod->dotIndicatorModifier_->itemHalfSizes_->Get(), itemHalfSizes);
}

/**
 * @tc.name: AttrIndicator003
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndicator003, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DIGIT
     * @tc.expected: Show indicator, indicator type is DIGIT
     */
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    auto firstTextNode = GetChildFrameNode(indicatorNode_, 0);
    auto lastTextNode = GetChildFrameNode(indicatorNode_, 1);
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor(), INDICATOR_TEXT_FONT_COLOR);
    EXPECT_EQ(firstTextLayoutProperty->GetFontSize(), INDICATOR_TEXT_FONT_SIZE);
    EXPECT_EQ(firstTextLayoutProperty->GetFontWeight(), INDICATOR_TEXT_FONT_WEIGHT);
    EXPECT_EQ(lastTextLayoutProperty->GetTextColor(), INDICATOR_TEXT_FONT_COLOR);
    EXPECT_EQ(lastTextLayoutProperty->GetFontSize(), INDICATOR_TEXT_FONT_SIZE);
    EXPECT_EQ(lastTextLayoutProperty->GetFontWeight(), INDICATOR_TEXT_FONT_WEIGHT);
}

/**
 * @tc.name: AttrIndicator004
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrIndicator004, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DIGIT
     * @tc.expected: Show indicator, indicator type is DIGIT
     */
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.fontColor = Color::RED;
    swiperDigitalParameters.selectedFontColor = Color::GREEN;
    swiperDigitalParameters.fontSize = Dimension(12.f);
    swiperDigitalParameters.selectedFontSize = Dimension(16.f);
    swiperDigitalParameters.fontWeight = FontWeight::W500;
    swiperDigitalParameters.selectedFontWeight = FontWeight::W900;
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DIGIT);
    model.SetDigitIndicatorStyle(swiperDigitalParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::DIGIT);
    auto firstTextNode = GetChildFrameNode(indicatorNode_, 0);
    auto lastTextNode = GetChildFrameNode(indicatorNode_, 1);
    auto firstTextLayoutProperty = firstTextNode->GetLayoutProperty<TextLayoutProperty>();
    auto lastTextLayoutProperty = lastTextNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor(), Color::GREEN);
    EXPECT_EQ(firstTextLayoutProperty->GetFontSize(), Dimension(16.f));
    EXPECT_EQ(firstTextLayoutProperty->GetFontWeight(), FontWeight::W900);
    EXPECT_EQ(lastTextLayoutProperty->GetTextColor(), Color::RED);
    EXPECT_EQ(lastTextLayoutProperty->GetFontSize(), Dimension(12.f));
    EXPECT_EQ(lastTextLayoutProperty->GetFontWeight(), FontWeight::W500);
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDuration(500);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetItemSpace(Dimension(10.f));
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetCachedCount(2);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisableSwipe(true);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetCurve(Curves::SMOOTH);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f); // item size > 0
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 0.f);
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
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetDisplayCount(), 2);
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f); // item size > 0
    EXPECT_GT(GetChildWidth(frameNode_, 1), 0.f);
}

/**
 * @tc.name: AttrDisplayCount003
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount003, TestSize.Level1)
{
    /**
     * @tc.cases: Set displayCount to ITEM_NUMBER+1
     * @tc.expected: DisplayCount is ITEM_NUMBER+1, last item place has placeholder child
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(ITEM_NUMBER + 1);
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetDisplayCount(), 5);
    EXPECT_EQ(pattern_->TotalCount(), ITEM_NUMBER); // child number still is 4
    EXPECT_GT(GetChildWidth(frameNode_, 3), 0.f);   // item size > 0
    EXPECT_GT(GetChildWidth(frameNode_, 4), 0.f);   // placeholder child
}

/**
 * @tc.name: AttrDisplayCount004
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount004, TestSize.Level1)
{
    /**
     * @tc.cases: Set minsize to half of swiper width
     * @tc.expected: show 2 item in one page
     */
    SwiperModelNG model = CreateSwiper();
    model.SetMinSize(Dimension(SWIPER_WIDTH / 3));
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->IsAutoFill());
    EXPECT_EQ(pattern_->GetDisplayCount(), 2);
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f); // item size > 0
    EXPECT_GE(GetChildWidth(frameNode_, 1), 0.f); // item size > 0
    EXPECT_EQ(GetChildWidth(frameNode_, 2), 0.f);
}

/**
 * @tc.name: AttrDisplayCount005
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount005, TestSize.Level1)
{
    /**
     * @tc.cases: Set displayCount to invalid 0
     * @tc.expected: DisplayCount is default 1
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(0);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetDisplayCount(), 1);
}

/**
 * @tc.name: AttrDisplayCount006
 * @tc.desc: Test property about DisplayCount
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrDisplayCount006, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set displayCount
     * @tc.expected: DisplayCount is 1
     */
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::FADE);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::NONE);
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0.f);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), SWIPER_WIDTH);
}

/**
 * @tc.name: AttrMargin002
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin002, TestSize.Level1)
{
    /**
     * @tc.cases: Set margin
     */
    SwiperModelNG model = CreateSwiper();
    model.SetPreviousMargin(Dimension(PRE_MARGIN), false);
    model.SetNextMargin(Dimension(NEXT_MARGIN), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetPrevMargin(), PRE_MARGIN);
    EXPECT_EQ(pattern_->GetNextMargin(), NEXT_MARGIN);
    EXPECT_EQ(GetChildX(frameNode_, 0), PRE_MARGIN);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), SWIPER_WIDTH - PRE_MARGIN - NEXT_MARGIN);
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
    SwiperModelNG model = CreateSwiper();
    model.SetNextMargin(Dimension(SWIPER_WIDTH + 1.f), false);
    model.SetPreviousMargin(Dimension(5), false);
    CreateSwiperItems();
    CreateSwiperDone();
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
    SwiperModelNG model = CreateSwiper();
    model.SetNextMargin(Dimension(10.f), false);
    model.SetPreviousMargin(Dimension(SWIPER_WIDTH + 1.f), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0.f);
}

/**
 * @tc.name: AttrMargin005
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin005, TestSize.Level1)
{
    /**
     * @tc.cases: Only set nextMargin
     */
    SwiperModelNG model = CreateSwiper();
    model.SetNextMargin(Dimension(NEXT_MARGIN), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetNextMargin(), NEXT_MARGIN);
    EXPECT_EQ(pattern_->GetPrevMargin(), 0.f);
}

/**
 * @tc.name: AttrMargin006
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin006, TestSize.Level1)
{
    /**
     * @tc.cases: Only set preMargin
     */
    SwiperModelNG model = CreateSwiper();
    model.SetPreviousMargin(Dimension(PRE_MARGIN), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_EQ(pattern_->GetPrevMargin(), PRE_MARGIN);
}

/**
 * @tc.name: AttrMargin007
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin007, TestSize.Level1)
{
    /**
     * @tc.cases: not support percentage
     */
    SwiperModelNG model = CreateSwiper();
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PERCENT), false);
    model.SetNextMargin(Dimension(10, DimensionUnit::PERCENT), false);
    model.SetDisplayCount(1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FLOAT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_FLOAT_EQ(pattern_->GetPrevMargin(), 0.f);
}

/**
 * @tc.name: AttrMargin008
 * @tc.desc: Test property about Margin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, AttrMargin008, TestSize.Level1)
{
    /**
     * @tc.cases: 'auto' not support previousMargin or nextMargin
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    model.ResetDisplayCount();
    model.SetPreviousMargin(Dimension(10), false);
    model.SetNextMargin(Dimension(10), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FLOAT_EQ(pattern_->GetNextMargin(), 0.f);
    EXPECT_FLOAT_EQ(pattern_->GetPrevMargin(), 0.f);
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->IsLoop());
    auto nestedScroll = pattern_->GetNestedScroll();
    EXPECT_EQ(nestedScroll.forward, NestedScrollMode::SELF_ONLY);
    EXPECT_EQ(nestedScroll.backward, NestedScrollMode::SELF_ONLY);
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
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNestedScroll(nestedOpt);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->IsLoop());
    auto nestedScroll = pattern_->GetNestedScroll();
    EXPECT_EQ(nestedScroll.forward, NestedScrollMode::SELF_FIRST);
    EXPECT_EQ(nestedScroll.backward, NestedScrollMode::SELF_FIRST);
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
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

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

/**
 * @tc.name: SwiperModelNg001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, SwiperModelNg001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndex function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetIndex(1);
    EXPECT_EQ(layoutProperty->GetIndex(), 1);

    /**
     * @tc.steps: step3.2. Test SetDisplayMode function.
     * @tc.expected: layoutProperty->GetDisplayMode() is equal to swiperDisplayMode.
     */
    model.SetDisplayMode(SwiperDisplayMode::STRETCH);
    EXPECT_EQ(layoutProperty->GetDisplayMode(), SwiperDisplayMode::STRETCH);

    /**
     * @tc.steps: step3.3. Test SetShowIndicator function.
     * @tc.expected: layoutProperty->GetIndex() is equal to 1.
     */
    model.SetShowIndicator(true);
    EXPECT_TRUE(layoutProperty->GetShowIndicator());

    /**
     * @tc.steps: step3.4. Test SetItemSpace function.
     * @tc.expected: layoutProperty->GetItemSpace() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    model.SetItemSpace(dimension);
    EXPECT_EQ(layoutProperty->GetItemSpace(), dimension);

    /**
     * @tc.steps: step3.5. Test SetCachedCount function.
     * @tc.expected:DisplayCount = -1 layoutProperty->SetCachedCount() is equal to 1.
     * @tc.expected:DisplayCount = 1 layoutProperty->SetCachedCount() is equal to 1.
     */
    model.SetCachedCount(-1);
    model.SetCachedCount(1);
    EXPECT_EQ(layoutProperty->GetCachedCount(), 1);

    /**
     * @tc.steps: step3.6. Test SetIsIndicatorCustomSize function.
     * @tc.expected: pattern->IsIndicatorCustomSize() is equal to true.
     */
    model.SetIsIndicatorCustomSize(true);
    EXPECT_TRUE(pattern->IsIndicatorCustomSize());

    /**
     * @tc.steps: step3.7. Test SetAutoPlay function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlay() is equal to true.
     */
    model.SetAutoPlay(true);
    EXPECT_TRUE(paintProperty->GetAutoPlay());

    /**
     * @tc.steps: step3.8. Test SetAutoPlayInterval function.
     * @tc.expected: SwiperPaintProperty->GetAutoPlayInterval() is equal to 1.
     */
    model.SetAutoPlayInterval(1);
    EXPECT_EQ(paintProperty->GetAutoPlayInterval(), 1);

    /**
     * @tc.steps: step3.9. Test SetDuration function.
     * @tc.expected: SwiperPaintProperty->GetDuration() is equal to 1.
     */
    model.SetDuration(1);
    EXPECT_EQ(paintProperty->GetDuration(), 1);
}

/**
 * @tc.name: SwiperModelNg002
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, SwiperModelNg002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();

    /**
     * @tc.steps: step3.1. Test SetLoop function.
     * @tc.expected: SwiperPaintProperty->GetLoop() is true.
     */
    model.SetLoop(true);
    EXPECT_TRUE(layoutProperty->GetLoop());

    /**
     * @tc.steps: step3.2. Test SetEnabled function.
     * @tc.expected: SwiperPaintProperty->GetEnabled() is true.
     */
    model.SetEnabled(true);
    EXPECT_TRUE(paintProperty->GetEnabled());

    /**
     * @tc.steps: step3.3. Test SetDisableSwipe function.
     * @tc.expected: layoutProperty->GetDisableSwipe() is true.
     */
    model.SetDisableSwipe(true);
    EXPECT_TRUE(layoutProperty->GetDisableSwipe());

    /**
     * @tc.steps: step3.4. Test SetEdgeEffect function.
     * @tc.expected: SwiperPaintProperty->GetEdgeEffect() is true.
     */
    model.SetEdgeEffect(EdgeEffect::FADE);
    EXPECT_EQ(paintProperty->GetEdgeEffect(), EdgeEffect::FADE);

    /**
     * @tc.steps: step3.5. Test SetOnChange function.
     * @tc.expected:pattern->changeEvent_ not null.
     */
    auto onChange = [](const BaseEventInfo* info) {};
    model.SetOnChange(std::move(onChange));
    EXPECT_NE(pattern->changeEvent_, nullptr);

    /**
     * @tc.steps: step3.6. Test SetOnAnimationStart function.
     * @tc.expected:pattern->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    model.SetOnAnimationStart(std::move(onAnimationStart));
    EXPECT_NE(pattern->animationStartEvent_, nullptr);

    /**
     * @tc.steps: step3.7. Test SetOnAnimationEnd function.
     * @tc.expected:pattern->animationEndEvent_ not null.
     */
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    model.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(pattern->animationEndEvent_, nullptr);

    /**
     * @tc.steps: step3.8 Test SetOnUnselected function.
     * @tc.expected:pattern->unselectedEvent_ not null.
     */
    auto onUnselected = [](const BaseEventInfo* info) {};
    model.SetOnUnselected(std::move(onUnselected));
    EXPECT_NE(pattern->unselectedEvent_, nullptr);

    /**
     * @tc.steps: step3.9 Test SetOnSelected function.
     * @tc.expected:pattern->selectedEvent_ not null.
     */
    auto onSelected = [](const BaseEventInfo* info) {};
    model.SetOnSelected(std::move(onSelected));
    EXPECT_NE(pattern->selectedEvent_, nullptr);

    /**
     * @tc.steps: step3.9 Test SetOnScrollStateChanged function.
     * @tc.expected:pattern->scrollStateChangedEvent_ not null.
     */
    auto onScrollStateChanged = [](const BaseEventInfo* info) {};
    model.SetOnScrollStateChanged(std::move(onScrollStateChanged));
    EXPECT_NE(eventHub->scrollStateChangedEvent_, nullptr);
}

/**
 * @tc.name: SwiperModelNg003
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, SwiperModelNg003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step3.1. Test SetIndicatorStyle function.
     * @tc.expected: SwiperPaintProperty->swiperParameters_->colorVal is swiperParameters.colorVal.
     */
    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    model.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);

    /**
     * @tc.steps: step3.2. Test SetPreviousMargin function.
     * @tc.expected: paintProperty->GetPrevMargin() is equal to dimension.
     */
    auto dimension = Dimension(-1.0);
    model.SetPreviousMargin(dimension, false);
    EXPECT_EQ(layoutProperty->GetPrevMargin(), dimension);

    /**
     * @tc.steps: step3.3. Test SetNextMargin function.
     * @tc.expected: paintProperty->GetNextMargin() is equal to dimension.
     */
    model.SetNextMargin(dimension, false);
    EXPECT_EQ(layoutProperty->GetNextMargin(), dimension);

    /**
     * @tc.steps: step3.5. Test SetIndicatorIsBoolean function.
     * @tc.expected: pattern->indicatorIsBoolean_ is true.
     */
    model.SetIndicatorIsBoolean(true);
    EXPECT_TRUE(pattern->indicatorIsBoolean_);

    /**
     * @tc.steps: step3.6. Test SetArrowStyle function.
     * @tc.expected: before set swiperArrowParameters, all result is null.
     */
    SwiperArrowParameters swiperArrowParameters;
    model.SetArrowStyle(swiperArrowParameters);

    /**
     * @tc.steps: step3.7. Test SetArrowStyle function.
     * @tc.expected: after set swiperArrowParameters, layoutProperty->IsShowBoard is true.
     */
    swiperArrowParameters.isShowBackground = true;
    swiperArrowParameters.backgroundSize = dimension;
    swiperArrowParameters.backgroundColor = Color(Color::BLUE);
    swiperArrowParameters.arrowSize = dimension;
    swiperArrowParameters.arrowColor = Color(Color::RED);
    swiperArrowParameters.isSidebarMiddle = true;
    model.SetArrowStyle(swiperArrowParameters);
    EXPECT_TRUE(layoutProperty->GetIsShowBackground());
    EXPECT_EQ(layoutProperty->GetBackgroundSize(), dimension);
    EXPECT_EQ(layoutProperty->GetBackgroundColor(), Color(Color::BLUE));
    EXPECT_EQ(layoutProperty->GetArrowSize(), dimension);
    EXPECT_EQ(layoutProperty->GetArrowColor(), Color(Color::RED));
    EXPECT_TRUE(layoutProperty->GetIsSidebarMiddle());

    /**
     * @tc.steps: step3.8. Test SetDisplayArrow function.
     * @tc.expected: layoutProperty->GetDisplayArrow() is true.
     */
    model.SetDisplayArrow(true);
    EXPECT_TRUE(layoutProperty->GetDisplayArrow());

    /**
     * @tc.steps: step3.9. Test SetHoverShow function.
     * @tc.expected: layoutProperty->GetHoverShow() is true.
     */
    model.SetHoverShow(true);
    EXPECT_TRUE(layoutProperty->GetHoverShow());
}

/**
 * @tc.name: SetMinSize001
 * @tc.desc: Swiper Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, SetMinSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateSwiper();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    /**
     * @tc.steps: step2. Calling the SetMinSize interface to set Dimension
     * @tc.expected: LayoutProperty ->GetMinSize(), equal to Dimension()
     */
    model.SetMinSize(Dimension(10));
    layoutProperty->GetMinSize();
    EXPECT_EQ(layoutProperty->GetMinSize(), Dimension(10));
}

/**
 * @tc.name: SwiperPaintProperty001
 * @tc.desc: Swiper Paint Property.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, SwiperPaintProperty001, TestSize.Level1)
{
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Test ToJsonValue function.
     * @tc.expected: Check the swiper property value
     */
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    paintProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("autoPlay"), "false");

    /**
     * @tc.steps: step2. call UpdateCalcLayoutProperty, push constraint is null.
     * @tc.expected: Return expected results.
     */
    MeasureProperty constraint;
    layoutProperty_->UpdateCalcLayoutProperty(std::move(constraint));
    EXPECT_EQ(layoutProperty_->propertyChangeFlag_, 1);

    /**
     * @tc.steps: step3. Test FromJson function.
     * @tc.expected: Check the swiper property value
     */
    auto jsonFrom = JsonUtil::Create(true);
    paintProperty_->FromJson(jsonFrom);
    EXPECT_TRUE(jsonFrom);
}

/**
 * @tc.name: ArcDotIndicator001
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ArcDotIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperArcDotParameters swiperArcDotParameters;
    swiperArcDotParameters.arcDirection = SwiperArcDirection::NINE_CLOCK_DIRECTION;
    swiperArcDotParameters.itemColor = Color::GREEN;
    swiperArcDotParameters.selectedItemColor = Color::RED;
    swiperArcDotParameters.containerColor = Color::BLUE;
    SwiperModelNG model = CreateArcSwiper();
    model.SetArcDotIndicatorStyle(swiperArcDotParameters);
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintProperty = indicatorNode_->GetPaintProperty<CircleDotIndicatorPaintProperty>();
    RefPtr<SwiperPattern> indicatorPattern = frameNode_->GetPattern<SwiperPattern>();
    indicatorPattern->OnModifyDone();
    EXPECT_EQ(pattern_->GetIndicatorType(), SwiperIndicatorType::ARC_DOT);
    EXPECT_EQ(paintProperty->GetArcDirection(), SwiperArcDirection::NINE_CLOCK_DIRECTION);
    EXPECT_EQ(paintProperty->GetColor(), Color::GREEN);
    EXPECT_EQ(paintProperty->GetSelectedColor(), Color::RED);
    EXPECT_EQ(paintProperty->GetContainerColor(), Color::BLUE);
}

/**
 * @tc.name: ArcDotIndicator001
 * @tc.desc: Test property about indicator
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ArcDotIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<ArcSwiperPattern> indicatorPattern = frameNode_->GetPattern<ArcSwiperPattern>();
    indicatorPattern->GetSwiperArcDotParameters();
    EXPECT_NE(indicatorPattern->swiperArcDotParameters_, nullptr);
}

/**
 * @tc.name: SetNestedScroll001
 * @tc.desc: Test SetNestedScroll method about NestableScrollContainer
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, SetNestedScroll001, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNestedScroll(nestedOpt);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    /**
     * @tc.steps: step1. call SetNestedScroll when parent && !nestedScroll.NeedParent() && nestedScroll_.NeedParent()
     */
    pattern_->parent_ = mockScroll;
    nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->isNestedInterrupt_ = false;
    pattern_->SetNestedScroll(nestedOpt);
    EXPECT_FALSE(pattern_->isFixedNestedScrollMode_);
    EXPECT_TRUE(pattern_->isNestedInterrupt_);
}

/**
 * @tc.name: OnScrollDragEndRecursive001
 * @tc.desc: Test OnScrollDragEndRecursive method about NestableScrollContainer
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, OnScrollDragEndRecursive001, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNestedScroll(nestedOpt);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    EXPECT_CALL(*mockScroll, OnScrollDragEndRecursive()).Times(1);
    ASSERT_EQ(mockScroll->parent_.Upgrade(), nullptr);
    /**
     * @tc.steps: step1. call OnScrollDragEndRecursive in parent and nestedScroll_.NeedParent() combined condition
     */
    pattern_->parent_ = mockScroll;
    ASSERT_NE(pattern_->parent_.Upgrade(), nullptr);
    EXPECT_TRUE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();

    nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->nestedScroll_ = nestedOpt;
    ASSERT_NE(pattern_->parent_.Upgrade(), nullptr);
    EXPECT_FALSE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();

    nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->nestedScroll_ = nestedOpt;
    pattern_->parent_ = nullptr;
    EXPECT_TRUE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();

    nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    pattern_->nestedScroll_ = nestedOpt;
    EXPECT_FALSE(pattern_->nestedScroll_.NeedParent());
    pattern_->OnScrollDragEndRecursive();
}

/**
 * @tc.name: LoopChange001
 * @tc.desc: Test loop change with prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, LoopChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. loop is false
     * @tc.expected: The first node in the display area is 0
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), false);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->itemPosition_.find(-1), pattern_->itemPosition_.end());

    /**
     * @tc.steps: step2. loop changes to true
     * @tc.expected: The first node in the display area is -1
     */
    layoutProperty_->UpdateLoop(true);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_NE(pattern_->itemPosition_.find(-1), pattern_->itemPosition_.end());
}

/**
 * @tc.name: PageFlipModeTest001
 * @tc.desc: PageFlipMode property test
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, PageFlipModeTest001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    // default mode is PageFlipMode::CONTINUOUS(0)
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
    // mode is PageFlipMode::SINGLE(0)
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), 1);
    EXPECT_EQ(pattern_->GetPageFlipMode(), 1);
    // exceeding the enum range will reset to default
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), -1);
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
    // exceeding the enum range will reset to default
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), 100);
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
}

/**
 * @tc.name: ShowCachedItems013
 * @tc.desc: Test show cached items on RTL, loop = true, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems013, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(3);
    model.SetCachedCount(1);
    model.SetIndex(3);
    CreateSwiperItems(10);
    CreateSwiperDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -160.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 540.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -260.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 600.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 280.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 120.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -40.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -200.0f);

    pattern_->ChangeIndex(7, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -160.0f);
}

/**
 * @tc.name: ShowCachedItems014
 * @tc.desc: Test show cached items on RTL, loop = true, cachedCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems014, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(4);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(10);
    CreateSwiperDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].endPos, 890.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].endPos, 440.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1350.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 6);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1250.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 800.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 350.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -550.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1000.0f);

    pattern_->ChangeIndex(5, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1350.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 1350.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 900.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 450.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -450.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -1350.0f);
}

/**
 * @tc.name: ShowCachedItems015
 * @tc.desc: Test show cached items on vertical = true, loop = true, cachedCount = 1
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems015, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -800.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 1500.0f);

    pattern_->ChangeIndex(1, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -800.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -900.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1500.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -800.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 800.0f);
}

/**
 * @tc.name: ShowCachedItems016
 * @tc.desc: Test show cached items on vertical = true, loop = true, cachedCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems016, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(2);
    model.SetIndex(1);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -1540.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1540.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -870.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 670.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1440.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 2210.0f);

    pattern_->ChangeIndex(2, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -1540.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1540.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1540.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 1540.0f);
}

/**
 * @tc.name: ShowCachedItems017
 * @tc.desc: Test show cached items on vertical = true, cachedCount = 2, displayCount = 2, set nextMargin and prevMargin
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems017, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(2);
    model.SetCachedCount(2);
    model.SetIndex(4);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), false);
    model.SetItemSpace(Dimension(10, DimensionUnit::PX));
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 8);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -385.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 385.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1540.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 7);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -870.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -485.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 285.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 670.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1055.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1440.0f);

    pattern_->ChangeIndex(5, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 8);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, -385.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 385.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 1540.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 8);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -770.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -385.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 385.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 770.0f);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 1155.0f);
    EXPECT_EQ(pattern_->itemPosition_[13].startPos, 1540.0f);
}

/**
 * @tc.name: ShowCachedItems018
 * @tc.desc: Test show cached items on swipe by group, loop = true, displayCount = 3
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems018, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(true);
    model.SetSwipeByGroup(true);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(3);
    model.SetCachedCount(1);
    model.SetIndex(0);
    CreateSwiperItems(10);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 9);
    EXPECT_EQ(pattern_->itemPosition_[-3].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -320.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 640.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 12);
    EXPECT_EQ(pattern_->itemPosition_[-3].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[-2].startPos, -420.0f);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, -260.0f);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 540.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 1020.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 1180.0f);

    pattern_->ChangeIndex(3, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 9);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -320.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 640.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 800.0f);

    pattern_->UpdateCurrentOffset(-100.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 12);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -580.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -420.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -260.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -100.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 60.0f);
    EXPECT_EQ(pattern_->itemPosition_[5].startPos, 220.0f);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, 380.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, 540.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, 700.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 860.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 1020.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 1180.0f);

    pattern_->ChangeIndex(9, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 9);
    EXPECT_EQ(pattern_->itemPosition_[6].startPos, -480.0f);
    EXPECT_EQ(pattern_->itemPosition_[7].startPos, -320.0f);
    EXPECT_EQ(pattern_->itemPosition_[8].startPos, -160.0f);
    EXPECT_EQ(pattern_->itemPosition_[9].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[10].startPos, 160.0f);
    EXPECT_EQ(pattern_->itemPosition_[11].startPos, 320.0f);
    EXPECT_EQ(pattern_->itemPosition_[12].startPos, 480.0f);
    EXPECT_EQ(pattern_->itemPosition_[13].startPos, 640.0f);
    EXPECT_EQ(pattern_->itemPosition_[14].startPos, 800.0f);
}

/**
 * @tc.name: ShowCachedItems020
 * @tc.desc: Test show cached items on nextMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems020, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(0);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 940.0f);

    pattern_->ChangeIndex(2, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 470.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 940.0f);

    pattern_->UpdateCurrentOffset(5.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -935.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -465.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 5.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 475.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 945.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -940.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems021
 * @tc.desc: Test show cached items on prevMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems021, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(4);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -940.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);

    pattern_->ChangeIndex(2, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 4);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -940.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 470.0f);

    pattern_->UpdateCurrentOffset(-5.0f);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -945.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -475.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -5.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 465.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 935.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 470.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 940.0f);
}

/**
 * @tc.name: ShowCachedItems022
 * @tc.desc: Test show cached items on prevMargin and nextMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems022, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(1);
    model.SetIndex(2);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), true);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 920.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 920.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 3);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: ShowCachedItems023
 * @tc.desc: Test show cached items on prevMargin and nextMargin ignore blank
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, ShowCachedItems023, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetCachedIsShown(true);
    model.SetDisplayCount(1);
    model.SetCachedCount(3);
    model.SetIndex(2);
    model.SetPreviousMargin(Dimension(10, DimensionUnit::PX), true);
    model.SetNextMargin(Dimension(10, DimensionUnit::PX), true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    FlushUITasks();

    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 920.0f);

    pattern_->ChangeIndex(0, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 460.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, 920.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, 1380.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 1840.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    ASSERT_EQ(static_cast<int32_t>(pattern_->itemPosition_.size()), 5);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -1840.0f);
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, -1380.0f);
    EXPECT_EQ(pattern_->itemPosition_[2].startPos, -920.0f);
    EXPECT_EQ(pattern_->itemPosition_[3].startPos, -460.0f);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 0.0f);
}

/**
 * @tc.name: CheckSwiperModelNG001
 * @tc.desc: Test function about SwiperModelNG
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, CheckSwiperModelNG001, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DIGIT and  BIND mode.
     * @tc.expected: call functions and check the result
     */
    SwiperDigitalParameters swiperDigitalParameters;
    swiperDigitalParameters.dimEnd = std::make_optional(Dimension(10.0f));
    SwiperModelNG swiperModel;
    frameNode_ = swiperModel.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(Referenced::RawPtr(frameNode_));
    swiperModel.SetBindIndicator(frameNode, true);
    swiperModel.SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    swiperModel.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    swiperModel.SetCachedCount(frameNode, 2);
    swiperModel.SetLoop(frameNode, false);
    swiperModel.SetIndex(frameNode, 0);
    swiperModel.SetDirection(frameNode, OHOS::Ace::Axis::HORIZONTAL);
    swiperModel.SetAutoPlay(frameNode, false);
    swiperModel.SetDigitIndicatorStyle(frameNode, swiperDigitalParameters);
    swiperModel.SetIndicatorIsBoolean(frameNode, true);
    swiperModel.SetIsIndicatorCustomSize(frameNode, true);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    EXPECT_EQ(swiperModel.GetCachedCount(frameNode), 2);
    EXPECT_EQ(swiperModel.GetIndicatorType(frameNode), static_cast<int32_t>(SwiperIndicatorType::DIGIT));
    EXPECT_EQ(swiperModel.GetLoop(frameNode), false);
    EXPECT_EQ(swiperModel.GetIndex(frameNode), 0);
    EXPECT_EQ(swiperModel.GetDirection(frameNode), OHOS::Ace::Axis::HORIZONTAL);
    EXPECT_EQ(swiperModel.GetAutoPlay(frameNode), false);
    EXPECT_EQ(indicatorNode_, nullptr);
    IndicatorModelNG model;
    model.Create();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(indicatorNode_, nullptr);
    auto indicatorPattern = indicatorNode_->GetPattern<IndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto controller = indicatorPattern->GetIndicatorController();
    ASSERT_NE(controller, nullptr);
    controller->SetSwiperNode(frameNode_);
    EXPECT_EQ(indicatorPattern->GetNonAutoLayoutDirection(), TextDirection::LTR);
    auto overlongDotIndicatorPaintMethod = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(overlongDotIndicatorPaintMethod, nullptr);
    auto indicatorPaintMethod = indicatorPattern->CreateDotIndicatorPaintMethodInSingleMode();
    EXPECT_NE(indicatorPaintMethod, nullptr);
    indicatorPattern->OnModifyDone();
    auto dotIndicatorPaintMethod = indicatorPattern->CreateDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(dotIndicatorPaintMethod, nullptr);
    overlongDotIndicatorPaintMethod = indicatorPattern->CreateOverlongDotIndicatorPaintMethod(pattern_);
    EXPECT_NE(overlongDotIndicatorPaintMethod, nullptr);
}

/**
 * @tc.name: CheckSwiperModelNG002
 * @tc.desc: Test function about SwiperModelNG
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, CheckSwiperModelNG002, TestSize.Level1)
{
    /**
     * @tc.cases: Set indicator type to DOT and  BIND mode.
     * @tc.expected: call functions and check the result
     */
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperParameters swiperParameters;
    SwiperModelNG swiperModel;
    frameNode_ = swiperModel.CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    EXPECT_NE(frameNode_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(Referenced::RawPtr(frameNode_));
    swiperModel.SetBindIndicator(frameNode, true);
    swiperModel.SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    swiperModel.SetDotIndicatorStyle(frameNode, swiperParameters);
    swiperModel.SetDuration(frameNode, 10);
    swiperModel.ResetDisplayCount(frameNode);
    swiperModel.SetDisplayCount(frameNode, 2);
    swiperModel.SetAutoPlayInterval(frameNode, 10);
    swiperModel.SetDisableSwipe(frameNode, false);
    swiperModel.SetItemSpace(frameNode, Dimension { 10.f });
    swiperModel.SetShowIndicator(frameNode, false);
    swiperModel.SetDisplayArrow(frameNode, false);
    swiperModel.SetEdgeEffect(frameNode, EdgeEffect::SPRING);
    swiperModel.SetNestedScroll(frameNode, 0);
    swiperModel.SetSwiperToIndex(frameNode, 1, false);
    swiperModel.SetIndicatorInteractive(frameNode, true);
    swiperModel.SetOnChange(frameNode, onChange);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    pattern_ = frameNode_->GetPattern<SwiperPattern>();
    controller_ = pattern_->GetSwiperController();
    SwiperMarginOptions marginOptions;
    swiperModel.GetPreviousMargin(frameNode, 1, &marginOptions);
    swiperModel.GetNextMargin(frameNode, 2, &marginOptions);
    RefPtr<Curve> curve = Curves::LINEAR;
    swiperModel.SetCurve(frameNode, curve);
    EXPECT_EQ(swiperModel.GetDuration(frameNode), 10);
    EXPECT_EQ(swiperModel.GetDisplayCount(frameNode), 2);
    EXPECT_EQ(swiperModel.GetAutoPlayInterval(frameNode), 10);
    EXPECT_EQ(swiperModel.GetDisableSwipe(frameNode), false);
    EXPECT_EQ(swiperModel.GetItemSpace(frameNode), 10.0f);
    EXPECT_EQ(swiperModel.GetShowIndicator(frameNode), false);
    EXPECT_EQ(swiperModel.GetShowDisplayArrow(frameNode), 0);
    EXPECT_EQ(swiperModel.GetEffectMode(frameNode), EdgeEffect::SPRING);
}

/**
 * @tc.name: CreateDotWithResourceObj001
 * @tc.desc: Test Swiper Model CreateDotWithResourceObj
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAttrTestNg, CreateDotWithResourceObj001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    auto layoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    auto paintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();

    SwiperParameters swiperParameters;
    swiperParameters.colorVal = Color(Color::BLUE);
    model.CreateDotWithResourceObj(frameNode, swiperParameters);
    model.SetIndicatorStyle(swiperParameters);
    EXPECT_EQ(pattern->swiperParameters_->colorVal, swiperParameters.colorVal);
}
} // namespace OHOS::Ace::NG
