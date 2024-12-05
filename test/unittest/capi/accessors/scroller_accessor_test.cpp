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

#include "core/interfaces/native/implementation/scroller_peer_impl.h"

#include "accessor_test_base.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class StubScrollController : public ScrollControllerBase {
public:
    StubScrollController() = default;
    ~StubScrollController() override = default;

    bool IsAtEnd() const override
    {
        return isAtEnd_;
    }

    void SetIsAtEnd(bool value)
    {
        isAtEnd_ = value;
    }

    int32_t GetItemIndex(double x, double y) const override
    {
        return static_cast<int32_t>(x + y);
    }

    Offset GetCurrentOffset() const override
    {
        constexpr double deltaX = 1.5;
        constexpr double deltaY = 3.5;
        return Offset(deltaX, deltaY);
    }

    Rect GetItemRect(int32_t index) const override
    {
        constexpr double x = 2.5;
        constexpr double y = 4.75;
        constexpr double width = 10.43;
        constexpr double height = 24;
        return Rect(x, y, width, height);
    }

    Axis GetScrollDirection() const override
    {
        return axis_;
    }

    void SetScrollDirection(const Axis& axis)
    {
        axis_ = axis;
    }

    bool AnimateTo(
        const Dimension& position, float duration, const RefPtr<Curve>& curve,
        bool smooth, bool canOverScroll = false) override
    {
        return animateTo_;
    }

    void SetAnimateToResult(bool animateTo)
    {
        animateTo_ = animateTo;
    }

private:
    bool isAtEnd_ = false;
    Axis axis_ = Axis::NONE;
    bool animateTo_ = true;
};

class MockScrollController : public StubScrollController {
public:
    MockScrollController() = default;
    ~MockScrollController() override = default;
    MOCK_METHOD(void, Fling, (double));
    MOCK_METHOD(bool, IsAtEnd, (), (const override));
    MOCK_METHOD(void, ScrollPage, (bool, bool));
    MOCK_METHOD(void, ScrollToEdge, (ScrollEdgeType, bool));
    MOCK_METHOD(void, ScrollBy, (double, double, bool));
    MOCK_METHOD(void, ScrollToIndex, (int32_t, bool, ScrollAlign, std::optional<float>));
    MOCK_METHOD(int32_t, GetItemIndex, (double, double), (const override));
    MOCK_METHOD(Offset, GetCurrentOffset, (), (const override));
    MOCK_METHOD(Rect, GetItemRect, (int32_t), (const override));
    MOCK_METHOD(Axis, GetScrollDirection, (), (const override));
    MOCK_METHOD(bool, AnimateTo, (const Dimension&, float, const RefPtr<Curve>&, bool, bool), (override));
};

class MockScrollController2 : public StubScrollController {
public:
    MockScrollController2() = default;
    ~MockScrollController2() override = default;
    MOCK_METHOD(void, ScrollToEdge, (ScrollEdgeType, float));
};

const Ark_Int32 FAKE_RES_ID(1234);
const Ark_Length RES_ARK_LENGTH = { .type = ARK_TAG_RESOURCE, .resource = FAKE_RES_ID };
} // namespace

class ScrollerAccessorTest : public AccessorTestBase<GENERATED_ArkUIScrollerAccessor,
    &GENERATED_ArkUIAccessors::getScrollerAccessor, ScrollerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockScrollerController_ = new MockScrollController();
        mockScrollerControllerKeeper_ = AceType::Claim(mockScrollerController_);
        ASSERT_NE(mockScrollerControllerKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->SetController(mockScrollerControllerKeeper_);
        ASSERT_NE(mockScrollerController_, nullptr);
    }

    void TearDown() override
    {
        mockScrollerControllerKeeper_ = nullptr;
        mockScrollerController_ = nullptr;
    }

    MockScrollController *mockScrollerController_ = nullptr;
    RefPtr<MockScrollController> mockScrollerControllerKeeper_ = nullptr;
};

/**
 * @tc.name: flingTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, flingTest, TestSize.Level1)
{
    constexpr double validFlingValue1 = 10.5f;
    constexpr double validFlingValue2 = 55.6f;
    constexpr double invalidFlingValue = 0.0000001f;

    auto arkFlingValid1 = ArkValue<Ark_Number>(validFlingValue1);
    auto arkFlingValid2 = ArkValue<Ark_Number>(validFlingValue2);
    auto arkFlingInvalid = ArkValue<Ark_Number>(invalidFlingValue);

    ASSERT_NE(accessor_->fling, nullptr);

    EXPECT_CALL(*mockScrollerController_, Fling(validFlingValue1)).Times(1);
    accessor_->fling(peer_, &arkFlingValid1);

    EXPECT_CALL(*mockScrollerController_, Fling(validFlingValue2)).Times(1);
    accessor_->fling(peer_, &arkFlingValid2);
    accessor_->fling(peer_, &arkFlingInvalid);
    accessor_->fling(peer_, nullptr);
}

/**
 * @tc.name: isAtEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, isAtEndTest, TestSize.Level1)
{
    auto arkIsAtEndTrue = ArkValue<Ark_Boolean>(true);
    auto arkIsAtEndFalse = ArkValue<Ark_Boolean>(false);

    ASSERT_NE(accessor_->isAtEnd, nullptr);

    mockScrollerController_->SetIsAtEnd(true);
    EXPECT_CALL(*mockScrollerController_, IsAtEnd()).Times(1).WillOnce(Return(arkIsAtEndTrue));
    auto result = accessor_->isAtEnd(peer_);
    EXPECT_EQ(result, arkIsAtEndTrue);

    mockScrollerController_->SetIsAtEnd(false);
    EXPECT_CALL(*mockScrollerController_, IsAtEnd()).Times(1).WillOnce(Return(arkIsAtEndFalse));
    result = accessor_->isAtEnd(peer_);
    EXPECT_EQ(result, arkIsAtEndFalse);
}

/**
 * @tc.name: scrollPage0Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollPage0Test, TestSize.Level1)
{
    constexpr bool nextTrue = true;
    constexpr bool nextFalse = false;
    constexpr bool smooth = false;

    Ark_ScrollPageOptions options1;
    options1.next = ArkValue<Ark_Boolean>(nextTrue);
    Ark_ScrollPageOptions options2;
    options2.next = ArkValue<Ark_Boolean>(nextFalse);

    ASSERT_NE(accessor_->scrollPage0, nullptr);

    EXPECT_CALL(*mockScrollerController_, ScrollPage(!nextTrue, smooth)).Times(1);
    accessor_->scrollPage0(peer_, &options1);

    EXPECT_CALL(*mockScrollerController_, ScrollPage(!nextFalse, smooth)).Times(1);
    accessor_->scrollPage0(peer_, &options2);
    accessor_->scrollPage0(peer_, nullptr);
}

/**
 * @tc.name: scrollPage1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollPage1Test, TestSize.Level1)
{
    constexpr bool nextTrue = true;
    constexpr bool nextFalse = false;
    constexpr bool smooth = false;

    Ark_Literal_Boolean_next_Axis_direction options1;
    options1.next = ArkValue<Ark_Boolean>(nextTrue);
    options1.direction = ArkValue<Opt_Axis>(Ark_Empty());
    Ark_Literal_Boolean_next_Axis_direction options2;
    options2.next = ArkValue<Ark_Boolean>(nextFalse);
    options2.direction = ArkValue<Opt_Axis>(Ark_Empty());

    ASSERT_NE(accessor_->scrollPage1, nullptr);

    EXPECT_CALL(*mockScrollerController_, ScrollPage(!nextTrue, smooth)).Times(1);
    accessor_->scrollPage1(peer_, &options1);

    EXPECT_CALL(*mockScrollerController_, ScrollPage(!nextFalse, smooth)).Times(1);
    accessor_->scrollPage1(peer_, &options2);
    accessor_->scrollPage1(peer_, nullptr);
}

/**
 * @tc.name: scrollEdgeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollEdgeTest, TestSize.Level1)
{
    Opt_ScrollEdgeOptions emptyScrollEdgeOptions = Converter::ArkValue<Opt_ScrollEdgeOptions>(Ark_Empty());

    ASSERT_NE(accessor_->scrollEdge, nullptr);

    EXPECT_CALL(*mockScrollerController_, ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true)).Times(2);
    accessor_->scrollEdge(peer_, ARK_EDGE_TOP, nullptr);
    accessor_->scrollEdge(peer_, ARK_EDGE_START, &emptyScrollEdgeOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToEdge(ScrollEdgeType::SCROLL_NONE, true)).Times(3);
    accessor_->scrollEdge(peer_, ARK_EDGE_CENTER, &emptyScrollEdgeOptions);
    accessor_->scrollEdge(peer_, ARK_EDGE_BASELINE, nullptr);
    accessor_->scrollEdge(peer_, ARK_EDGE_MIDDLE, &emptyScrollEdgeOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true)).Times(2);
    accessor_->scrollEdge(peer_, ARK_EDGE_BOTTOM, &emptyScrollEdgeOptions);
    accessor_->scrollEdge(peer_, ARK_EDGE_END, nullptr);
}

/**
 * @tc.name: scrollEdgeOptionsValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollEdgeOptionsValidTest, TestSize.Level1)
{
    auto mockScrollerController2 = new MockScrollController2();
    auto mockScrollerControllerKeeper2 = AceType::Claim(mockScrollerController2);
    ASSERT_NE(mockScrollerControllerKeeper2, nullptr);
    ASSERT_NE(peer_, nullptr);
    peer_->SetController(mockScrollerControllerKeeper2);
    ASSERT_NE(mockScrollerController2, nullptr);

    constexpr float velocityValid = 100.45f;

    Ark_ScrollEdgeOptions scrollEdgeOptions;
    scrollEdgeOptions.velocity = Converter::ArkValue<Opt_Number>(std::optional<float>(velocityValid));
    Opt_ScrollEdgeOptions optScrollEdgeOptions = Converter::ArkValue<Opt_ScrollEdgeOptions>(
        std::optional<Ark_ScrollEdgeOptions>(scrollEdgeOptions));

    ASSERT_NE(accessor_->scrollEdge, nullptr);

    EXPECT_CALL(*mockScrollerController2, ScrollToEdge(ScrollEdgeType::SCROLL_TOP, velocityValid)).Times(1);
    accessor_->scrollEdge(peer_, ARK_EDGE_START, &optScrollEdgeOptions);

    peer_->SetController(mockScrollerControllerKeeper_);
}

/**
 * @tc.name: scrollEdgeOptionsInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollEdgeOptionsInvalidTest, TestSize.Level1)
{
    constexpr float velocityInvalid = -100.45f;

    Ark_ScrollEdgeOptions scrollEdgeOptions;
    scrollEdgeOptions.velocity = Converter::ArkValue<Opt_Number>(std::optional<float>(velocityInvalid));
    Opt_ScrollEdgeOptions optScrollEdgeOptions = Converter::ArkValue<Opt_ScrollEdgeOptions>(
        std::optional<Ark_ScrollEdgeOptions>(scrollEdgeOptions));

    ASSERT_NE(accessor_->scrollEdge, nullptr);

    EXPECT_CALL(*mockScrollerController_, ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true)).Times(1);
    accessor_->scrollEdge(peer_, ARK_EDGE_START, &optScrollEdgeOptions);
}

/**
 * @tc.name: scrollByXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollByXTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scrollBy, nullptr);

    typedef std::pair<Ark_Length, double> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), 1 },
        { Converter::ArkValue<Ark_Length>(0), 0 },
        { Converter::ArkValue<Ark_Length>(-1), -1 },
        { Converter::ArkValue<Ark_Length>(2.5f), 2.5 },
        { Converter::ArkValue<Ark_Length>(-2.5f), -2.5 },
        { Converter::ArkValue<Ark_Length>(5.0_px), 5 },
        { Converter::ArkValue<Ark_Length>(-5.0_px), -5 },
        { Converter::ArkValue<Ark_Length>(22.5_px), 22.5 },
        { Converter::ArkValue<Ark_Length>(-22.5_px), -22.5 },
        { Converter::ArkValue<Ark_Length>(7.0_vp), 7 },
        { Converter::ArkValue<Ark_Length>(-7.0_vp), -7 },
        { Converter::ArkValue<Ark_Length>(1.5_vp), 1.5 },
        { Converter::ArkValue<Ark_Length>(-1.5_vp), -1.5 },
        { Converter::ArkValue<Ark_Length>(65.0_fp), 65 },
        { Converter::ArkValue<Ark_Length>(-65.0_fp), -65 },
        { Converter::ArkValue<Ark_Length>(4.5_fp), 4.5 },
        { Converter::ArkValue<Ark_Length>(-4.5_fp), -4.5 },
        { Converter::ArkValue<Ark_Length>(0.12_pct), 0 },
        { Converter::ArkValue<Ark_Length>(-0.12_pct), 0 },
        { RES_ARK_LENGTH, 0 },
    };

    Ark_Length arkDy = Converter::ArkValue<Ark_Length>(0);

    for (const auto &[arkLength, expected]: testPlan) {
        EXPECT_CALL(*mockScrollerController_, ScrollBy(expected, 0, false)).Times(1);
        accessor_->scrollBy(peer_, &arkLength, &arkDy);
    }
}

/**
 * @tc.name: scrollByYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollByYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scrollBy, nullptr);

    typedef std::pair<Ark_Length, double> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkValue<Ark_Length>(1), 1 },
        { Converter::ArkValue<Ark_Length>(0), 0 },
        { Converter::ArkValue<Ark_Length>(-1), -1 },
        { Converter::ArkValue<Ark_Length>(2.5f), 2.5 },
        { Converter::ArkValue<Ark_Length>(-2.5f), -2.5 },
        { Converter::ArkValue<Ark_Length>(5.0_px), 5 },
        { Converter::ArkValue<Ark_Length>(-5.0_px), -5 },
        { Converter::ArkValue<Ark_Length>(22.5_px), 22.5 },
        { Converter::ArkValue<Ark_Length>(-22.5_px), -22.5 },
        { Converter::ArkValue<Ark_Length>(7.0_vp), 7 },
        { Converter::ArkValue<Ark_Length>(-7.0_vp), -7 },
        { Converter::ArkValue<Ark_Length>(1.5_vp), 1.5 },
        { Converter::ArkValue<Ark_Length>(-1.5_vp), -1.5 },
        { Converter::ArkValue<Ark_Length>(65.0_fp), 65 },
        { Converter::ArkValue<Ark_Length>(-65.0_fp), -65 },
        { Converter::ArkValue<Ark_Length>(4.5_fp), 4.5 },
        { Converter::ArkValue<Ark_Length>(-4.5_fp), -4.5 },
        { Converter::ArkValue<Ark_Length>(0.12_pct), 0 },
        { Converter::ArkValue<Ark_Length>(-0.12_pct), 0 },
        { RES_ARK_LENGTH, 0 },
    };

    Ark_Length arkDx = Converter::ArkValue<Ark_Length>(0);

    for (const auto &[arkLength, expected]: testPlan) {
        EXPECT_CALL(*mockScrollerController_, ScrollBy(0, expected, false)).Times(1);
        accessor_->scrollBy(peer_, &arkDx, &arkLength);
    }
}

/**
 * @tc.name: scrollToIndexTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToIndexTest, TestSize.Level1)
{
    constexpr int32_t indexValid = 100;
    constexpr int32_t indexInvalid = -100;
    std::optional<float> emptyOptionsRes = std::nullopt;

    Ark_Number arkIndexValid = Converter::ArkValue<Ark_Number>(indexValid);
    Ark_Number arkIndexInvalid = Converter::ArkValue<Ark_Number>(indexInvalid);
    Opt_Boolean arkSmooth = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    Opt_ScrollAlign arkAlign = Converter::ArkValue<Opt_ScrollAlign>(Ark_Empty());
    Opt_ScrollToIndexOptions arkOptions = Converter::ArkValue<Opt_ScrollToIndexOptions>(Ark_Empty());

    ASSERT_NE(accessor_->scrollToIndex, nullptr);

    EXPECT_CALL(*mockScrollerController_,
        ScrollToIndex(indexValid, false, ScrollAlign::NONE, emptyOptionsRes)).Times(1);
    accessor_->scrollToIndex(peer_, &arkIndexValid, &arkSmooth, &arkAlign, &arkOptions);
    accessor_->scrollToIndex(peer_, &arkIndexInvalid, &arkSmooth, &arkAlign, &arkOptions);
    accessor_->scrollToIndex(peer_, nullptr, &arkSmooth, &arkAlign, &arkOptions);
}

/**
 * @tc.name: scrollToIndexSmoothTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToIndexSmoothTest, TestSize.Level1)
{
    constexpr int32_t index = 100;
    std::optional<float> emptyOptionsRes = std::nullopt;

    Ark_Number arkIndex = Converter::ArkValue<Ark_Number>(index);
    Opt_Boolean arkSmoothEmpty = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    Opt_Boolean arkSmoothTrue = Converter::ArkValue<Opt_Boolean>(std::optional<bool>(true));
    Opt_Boolean arkSmoothFalse = Converter::ArkValue<Opt_Boolean>(std::optional<bool>(false));
    Opt_ScrollAlign arkAlign = Converter::ArkValue<Opt_ScrollAlign>(Ark_Empty());
    Opt_ScrollToIndexOptions arkOptions = Converter::ArkValue<Opt_ScrollToIndexOptions>(Ark_Empty());

    ASSERT_NE(accessor_->scrollToIndex, nullptr);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, false, ScrollAlign::NONE, emptyOptionsRes)).Times(3);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmoothEmpty, &arkAlign, &arkOptions);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmoothFalse, &arkAlign, &arkOptions);
    accessor_->scrollToIndex(peer_, &arkIndex, nullptr, &arkAlign, &arkOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, true, ScrollAlign::NONE, emptyOptionsRes)).Times(1);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmoothTrue, &arkAlign, &arkOptions);
}

/**
 * @tc.name: scrollToIndexAlignTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToIndexAlignTest, TestSize.Level1)
{
    constexpr int32_t index = 100;
    std::optional<float> emptyOptionsRes = std::nullopt;

    Ark_Number arkIndex = Converter::ArkValue<Ark_Number>(index);
    Opt_Boolean arkSmooth = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    Opt_ScrollAlign arkAlignEmpty = Converter::ArkValue<Opt_ScrollAlign>(Ark_Empty());
    Opt_ScrollAlign arkAlignStart = Converter::ArkValue<Opt_ScrollAlign>(
        std::optional<Ark_ScrollAlign>(ARK_SCROLL_ALIGN_START));
    Opt_ScrollAlign arkAlignCenter = Converter::ArkValue<Opt_ScrollAlign>(
        std::optional<Ark_ScrollAlign>(ARK_SCROLL_ALIGN_CENTER));
    Opt_ScrollAlign arkAlignEnd = Converter::ArkValue<Opt_ScrollAlign>(
        std::optional<Ark_ScrollAlign>(ARK_SCROLL_ALIGN_END));
    Opt_ScrollAlign arkAlignAuto = Converter::ArkValue<Opt_ScrollAlign>(
        std::optional<Ark_ScrollAlign>(ARK_SCROLL_ALIGN_AUTO));
    Opt_ScrollToIndexOptions arkOptions = Converter::ArkValue<Opt_ScrollToIndexOptions>(Ark_Empty());

    ASSERT_NE(accessor_->scrollToIndex, nullptr);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, false, ScrollAlign::NONE, emptyOptionsRes)).Times(2);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmooth, &arkAlignEmpty, &arkOptions);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmooth, nullptr, &arkOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, false, ScrollAlign::START, emptyOptionsRes)).Times(1);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmooth, &arkAlignStart, &arkOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, false, ScrollAlign::CENTER, emptyOptionsRes)).Times(1);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmooth, &arkAlignCenter, &arkOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, false, ScrollAlign::END, emptyOptionsRes)).Times(1);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmooth, &arkAlignEnd, &arkOptions);

    EXPECT_CALL(*mockScrollerController_, ScrollToIndex(index, false, ScrollAlign::AUTO, emptyOptionsRes)).Times(1);
    accessor_->scrollToIndex(peer_, &arkIndex, &arkSmooth, &arkAlignAuto, &arkOptions);
}

/**
 * @tc.name: DISABLED_scrollToIndexOptionsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, DISABLED_scrollToIndexOptionsTest, TestSize.Level1)
{
    // wait for Ark_LengthMetrics instead of Ark_CustomObject in CAPI
}

/**
 * @tc.name: getItemIndexTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, getItemIndexTest, TestSize.Level1)
{
    double x = 10;
    double y = 20;

    auto arkX = ArkValue<Ark_Number>(static_cast<float>(x));
    auto arkY = ArkValue<Ark_Number>(static_cast<float>(y));
    auto arkIndex = ArkValue<Ark_Int32>(static_cast<int32_t>(x + y));
    auto arkIndexInavid = ArkValue<Ark_Int32>(-1);

    ASSERT_NE(accessor_->getItemIndex, nullptr);

    EXPECT_CALL(*mockScrollerController_, GetItemIndex(x, y)).Times(1).WillOnce(Return(arkIndex));
    auto result = accessor_->getItemIndex(peer_, &arkX, &arkY);
    EXPECT_EQ(result, arkIndex);
    result = accessor_->getItemIndex(peer_, nullptr, &arkY);
    EXPECT_EQ(result, arkIndexInavid);
    result = accessor_->getItemIndex(peer_, &arkX, nullptr);
    EXPECT_EQ(result, arkIndexInavid);
    result = accessor_->getItemIndex(peer_, nullptr, nullptr);
    EXPECT_EQ(result, arkIndexInavid);
}

/**
 * @tc.name: DISABLED_currentOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, DISABLED_currentOffsetTest, TestSize.Level1)
{
    auto expectedOffset = Offset(1.5, 3.5);

    ASSERT_NE(accessor_->currentOffset, nullptr);

    EXPECT_CALL(*mockScrollerController_, GetCurrentOffset()).Times(1).WillOnce(Return(expectedOffset));
    accessor_->currentOffset(peer_);
    // wait for return value type change from Ark_NativePointer to another type which is acceptable to "offset" data
}

/**
 * @tc.name: DISABLED_getItemRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, DISABLED_getItemRectTest, TestSize.Level1)
{
    auto expectedRect = Rect(2.5, 4.75, 10.43, 24);
    int32_t index = 5;
    Ark_Number arkIndex = Converter::ArkValue<Ark_Number>(index);

    ASSERT_NE(accessor_->getItemRect, nullptr);

    EXPECT_CALL(*mockScrollerController_, GetItemRect(index)).Times(1).WillOnce(Return(expectedRect));
    accessor_->getItemRect(peer_, &arkIndex);
    // wait for return value type change from Ark_NativePointer to another type which is acceptable to "rect" data
}

/**
 * @tc.name: scrollToPositionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToPositionTest, TestSize.Level1)
{
    float duration = 0.0f;
    bool smooth = false;
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;

    typedef std::pair<Ark_Union_Number_String, Dimension> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1), Dimension(1, DimensionUnit::VP) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(0), Dimension(0, DimensionUnit::VP) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(2.5f), Dimension(2.5, DimensionUnit::VP) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-5px"), Dimension(-5, DimensionUnit::PX) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("22.5px"), Dimension(22.5, DimensionUnit::PX) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("7vp"), Dimension(7, DimensionUnit::VP) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("1.5vp"), Dimension(1.5, DimensionUnit::VP) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("65fp"), Dimension(65, DimensionUnit::FP) },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4.5fp"), Dimension(4.5, DimensionUnit::FP) },
    };

    ASSERT_NE(accessor_->scrollTo, nullptr);

    for (const auto &[arkOffset, expected]: testPlan) {
        Ark_ScrollOptions options;
        options.xOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(0);
        options.yOffset = arkOffset;
        options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(Ark_Empty());
        mockScrollerController_->SetScrollDirection(Axis::VERTICAL);
        mockScrollerController_->SetAnimateToResult(true);
        EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1).WillOnce(Return(Axis::VERTICAL));
        EXPECT_CALL(*mockScrollerController_, AnimateTo(expected, duration, curve, smooth, canOverScroll))
            .Times(1).WillOnce(Return(true));
        accessor_->scrollTo(peer_, &options);

        options.xOffset = arkOffset;
        options.yOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(0);
        mockScrollerController_->SetScrollDirection(Axis::HORIZONTAL);
        mockScrollerController_->SetAnimateToResult(true);
        EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1).WillOnce(Return(Axis::HORIZONTAL));
        EXPECT_CALL(*mockScrollerController_, AnimateTo(expected, duration, curve, smooth, canOverScroll))
            .Times(1).WillOnce(Return(false));
        accessor_->scrollTo(peer_, &options);
    }
}

/**
 * @tc.name: scrollToAnimationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToAnimationTest, TestSize.Level1)
{
    Dimension position = Dimension(1, DimensionUnit::VP);
    float duration = 0.0f;
    float defaultDuration = 1000.0f;
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;

    Ark_ScrollOptions options;
    options.xOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);
    options.yOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);

    ASSERT_NE(accessor_->scrollTo, nullptr);

    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_Boolean>(true)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, duration, curve, true, canOverScroll)).Times(1);
    accessor_->scrollTo(peer_, &options);

    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_Boolean>(false)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, duration, curve, false, canOverScroll)).Times(1);
    accessor_->scrollTo(peer_, &options);

    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(Ark_Empty());
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, duration, curve, false, canOverScroll)).Times(1);
    accessor_->scrollTo(peer_, &options);

    Ark_ScrollAnimationOptions scrollAnimationOptions;
    scrollAnimationOptions.canOverScroll = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    scrollAnimationOptions.curve = Converter::ArkValue<Opt_Union_Curve_ICurve>(Ark_Empty());
    scrollAnimationOptions.duration = Converter::ArkValue<Opt_Number>(Ark_Empty());
    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_ScrollAnimationOptions>(
                scrollAnimationOptions)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, defaultDuration, curve, true, canOverScroll)).Times(1);
    accessor_->scrollTo(peer_, &options);
}

/**
 * @tc.name: scrollToCanOverScrollTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToCanOverScrollTest, TestSize.Level1)
{
    Dimension position = Dimension(1, DimensionUnit::VP);
    float duration = 1000.0f;
    bool smooth = false;
    RefPtr<Curve> curve = Curves::EASE;

    Ark_ScrollOptions options;
    options.xOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);
    options.yOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);

    ASSERT_NE(accessor_->scrollTo, nullptr);

    Ark_ScrollAnimationOptions scrollAnimationOptions;
    scrollAnimationOptions.curve = Converter::ArkValue<Opt_Union_Curve_ICurve>(Ark_Empty());
    scrollAnimationOptions.duration = Converter::ArkValue<Opt_Number>(Ark_Empty());

    scrollAnimationOptions.canOverScroll = Converter::ArkValue<Opt_Boolean>(std::optional<bool>(true));
    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_ScrollAnimationOptions>(
                scrollAnimationOptions)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, duration, curve, smooth, true)).Times(1);
    accessor_->scrollTo(peer_, &options);

    scrollAnimationOptions.canOverScroll = Converter::ArkValue<Opt_Boolean>(std::optional<bool>(false));
    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_ScrollAnimationOptions>(
                scrollAnimationOptions)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, duration, curve, smooth, false)).Times(1);
    accessor_->scrollTo(peer_, &options);
}

/**
 * @tc.name: scrollToDurationTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToDurationTest, TestSize.Level1)
{
    Dimension position = Dimension(1, DimensionUnit::VP);
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;

    Ark_ScrollOptions options;
    options.xOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);
    options.yOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);

    ASSERT_NE(accessor_->scrollTo, nullptr);

    Ark_ScrollAnimationOptions scrollAnimationOptions;
    scrollAnimationOptions.curve = Converter::ArkValue<Opt_Union_Curve_ICurve>(Ark_Empty());
    scrollAnimationOptions.canOverScroll = Converter::ArkValue<Opt_Boolean>(Ark_Empty());

    scrollAnimationOptions.duration = Converter::ArkValue<Opt_Number>(std::optional<float>(100.5f));
    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_ScrollAnimationOptions>(
                scrollAnimationOptions)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, 100.5f, curve, false, canOverScroll)).Times(1);
    accessor_->scrollTo(peer_, &options);

    scrollAnimationOptions.duration = Converter::ArkValue<Opt_Number>(std::optional<float>(-1.0f));
    options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
        std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
            Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_ScrollAnimationOptions>(
                scrollAnimationOptions)));
    EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
    EXPECT_CALL(*mockScrollerController_, AnimateTo(position, 1000.0f, curve, true, canOverScroll)).Times(1);
    accessor_->scrollTo(peer_, &options);
}

/**
 * @tc.name: scrollToCurveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, scrollToCurveTest, TestSize.Level1)
{
    Dimension position = Dimension(1, DimensionUnit::VP);
    float duration = 1000.0f;
    bool smooth = false;
    bool canOverScroll = false;

    Ark_ScrollOptions options;
    options.xOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);
    options.yOffset = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1);

    ASSERT_NE(accessor_->scrollTo, nullptr);

    Ark_ScrollAnimationOptions scrollAnimationOptions;
    scrollAnimationOptions.canOverScroll = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    scrollAnimationOptions.duration = Converter::ArkValue<Opt_Number>(Ark_Empty());

    typedef std::pair<Ark_Union_Curve_ICurve, RefPtr<Curve>> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_LINEAR), Curves::LINEAR },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_EASE), Curves::EASE },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_EASE_IN), Curves::EASE_IN },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_EASE_OUT), Curves::EASE_OUT },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_EASE_IN_OUT), Curves::EASE_IN_OUT },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_FAST_OUT_SLOW_IN), Curves::FAST_OUT_SLOW_IN },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_LINEAR_OUT_SLOW_IN),
            Curves::LINEAR_OUT_SLOW_IN },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_FAST_OUT_LINEAR_IN),
            Curves::FAST_OUT_LINEAR_IN },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_EXTREME_DECELERATION),
            Curves::EXTREME_DECELERATION },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_SMOOTH), Curves::SMOOTH },
        { Converter::ArkUnion<Ark_Union_Curve_ICurve, Ark_Curve>(ARK_CURVE_FRICTION), Curves::FRICTION },
    };

    for (const auto &[arkCurve, expected]: testPlan) {
        scrollAnimationOptions.curve = Converter::ArkValue<Opt_Union_Curve_ICurve>(
            std::optional<Ark_Union_Curve_ICurve>(arkCurve));
        options.animation = Converter::ArkValue<Opt_Union_ScrollAnimationOptions_Boolean>(
            std::optional<Ark_Union_ScrollAnimationOptions_Boolean>(
                Converter::ArkUnion<Ark_Union_ScrollAnimationOptions_Boolean, Ark_ScrollAnimationOptions>(
                    scrollAnimationOptions)));
        EXPECT_CALL(*mockScrollerController_, GetScrollDirection()).Times(1);
        EXPECT_CALL(*mockScrollerController_, AnimateTo(position, duration, expected, smooth, canOverScroll))
            .Times(1);
        accessor_->scrollTo(peer_, &options);
    }
}

/**
 * @tc.name: DISABLED_scrollToICurveTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ScrollerAccessorTest, DISABLED_scrollToICurveTest, TestSize.Level1)
{
    // Ark_ICurve supporting is not implemented
}
} // namespace OHOS::Ace::NG
