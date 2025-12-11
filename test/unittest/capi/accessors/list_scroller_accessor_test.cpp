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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/interfaces/native/implementation/list_scroller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {

const double FLT_PRECISION = 0.001;
static std::vector<std::tuple<int32_t, std::pair<double, double>>> positionsValues = {
    {8, {8.0, 8.8}},
    {99, {10.0, 11.11}},
    {5, {5.0, 5.5}},
    {77, {7.0, 7.7}},
    {0, {0.0, 0.1}},
};

class StubListScrollController : public ScrollControllerBase {
public:
    StubListScrollController() = default;
    ~StubListScrollController() override = default;

    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const override
    {
        if (index < 0 || indexInGroup < 0) {
            return Rect();
        }

        auto it = std::find_if(positionsValues.begin(), positionsValues.end(),
            [index](const std::tuple<int32_t, std::pair<double, double>>& item) {
                return std::get<0>(item) == index;
            });
        if (it == positionsValues.end()) {
            return Rect();
        }

        const auto& selected_pair = std::get<1>(*it);
        double x = selected_pair.first;
        double y = selected_pair.second;

        it = std::find_if(positionsValues.begin(), positionsValues.end(),
            [indexInGroup](const std::tuple<int32_t, std::pair<double, double>>& item) {
                return std::get<0>(item) == indexInGroup;
            });
        if (it == positionsValues.end()) {
            return Rect();
        }

        const auto& selected_pair2 = std::get<1>(*it);
        double w = selected_pair2.first;
        double h = selected_pair2.second;

        return Rect(x, y, w, h);
    }

    ListItemGroupIndex GetItemIndexInGroup(double x, double y) const override
    {
        ListItemGroupIndex itemGroupIndex = { x, ListItemGroupArea::IN_FOOTER_AREA, y };
        return itemGroupIndex;
    }

    void CloseAllSwipeActions(OnFinishFunc&& onFinishCallback) override
    {
        onFinishCallback();
    }
};

class MockListScrollController : public StubListScrollController {
public:
    MockListScrollController() = default;
    ~MockListScrollController() override = default;

    MOCK_METHOD(void, JumpToItemInGroup, (int32_t, int32_t, bool, ScrollAlign, int32_t));
};
} // namespace

class ListScrollerAccessorTest : public AccessorTestBase<GENERATED_ArkUIListScrollerAccessor,
    &GENERATED_ArkUIAccessors::getListScrollerAccessor, ListScrollerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockListScrollerController_ = new MockListScrollController();
        mockListScrollerControllerKeeper_ = AceType::Claim(mockListScrollerController_);
        ASSERT_NE(mockListScrollerControllerKeeper_, nullptr);
        ASSERT_NE(peer_, nullptr);
        peer_->SetController(mockListScrollerControllerKeeper_);
        ASSERT_NE(mockListScrollerController_, nullptr);
        int dummy;
        vmContext_ = reinterpret_cast<Ark_VMContext>(&dummy);
    }

    void TearDown() override
    {
        mockListScrollerControllerKeeper_ = nullptr;
        mockListScrollerController_ = nullptr;
        vmContext_ = nullptr;
    }

    const std::pair<double, double> getPositions(const int32_t& index)
    {
        auto it = std::find_if(positionsValues.begin(), positionsValues.end(),
            [index](const std::tuple<int32_t, std::pair<double, double>>& item) {
                return std::get<0>(item) == index;
            });
        if (it == positionsValues.end()) {
            return {0.0, 0.0};
        }
        return std::get<1>(*it);
    }

    MockListScrollController *mockListScrollerController_ = nullptr;
    RefPtr<MockListScrollController> mockListScrollerControllerKeeper_ = nullptr;
    Ark_VMContext vmContext_ = nullptr;
};

static std::vector<std::tuple<int32_t, Ark_Int32>> indexValues = {
    {8, Converter::ArkValue<Ark_Int32>(8)},
    {99, Converter::ArkValue<Ark_Int32>(99)},
    {0, Converter::ArkValue<Ark_Int32>(0)},
};

static std::vector<std::tuple<int32_t, Ark_Int32>> indexInGroupValues = {
    {5, Converter::ArkValue<Ark_Int32>(5)},
    {77, Converter::ArkValue<Ark_Int32>(77)},
    {0, Converter::ArkValue<Ark_Int32>(0)},
};

static std::vector<std::tuple<int32_t, Ark_Int32>> indexNegativeValues = {
    {-1, Converter::ArkValue<Ark_Int32>(-1)},
};

static std::vector<std::tuple<ScrollAlign, Opt_ScrollAlign>> alignValues = {
    {ScrollAlign::START, Converter::ArkValue<Opt_ScrollAlign>(ARK_SCROLL_ALIGN_START)},
    {ScrollAlign::CENTER, Converter::ArkValue<Opt_ScrollAlign>(ARK_SCROLL_ALIGN_CENTER)},
    {ScrollAlign::END, Converter::ArkValue<Opt_ScrollAlign>(ARK_SCROLL_ALIGN_END)},
    {ScrollAlign::AUTO, Converter::ArkValue<Opt_ScrollAlign>(ARK_SCROLL_ALIGN_AUTO)},
    // ScrollAlign::NONE doesn't have an equivalent in Ark_ScrollAlign (like ARK_SCROLL_ALIGN_NONE).
};

static std::vector<std::tuple<ScrollAlign, Opt_ScrollAlign>> alignInvalidValues = {
    {ScrollAlign::NONE, Converter::ArkValue<Opt_ScrollAlign>()},
    {ScrollAlign::NONE, Converter::ArkValue<Opt_ScrollAlign>(static_cast<Ark_ScrollAlign>(-1))},
};

static std::vector<std::tuple<bool, Opt_Boolean>> smoothValues = {
    {false, Converter::ArkValue<Opt_Boolean>(false)},
    {true, Converter::ArkValue<Opt_Boolean>(true)},
};

static std::vector<std::tuple<bool, Opt_Boolean>> smoothInvalidValues = {
    {false, Converter::ArkValue<Opt_Boolean>()}
};

/**
 * @tc.name: JumpToItemInGroupTestValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, JumpToItemInGroupTestValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scrollToItemInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    bool smooth = std::get<0>(smoothValues[0]);
    ScrollAlign align = std::get<0>(alignValues[0]);

    Ark_Int32 arkIndex = std::get<1>(indexValues[0]);
    Ark_Int32 arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: indexValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    for (auto&& value: indexInGroupValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    for (auto&& value: alignValues) {
        align = std::get<0>(value);
        arkAlign = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    for (auto&& value: smoothValues) {
        smooth = std::get<0>(value);
        arkSmooth = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }
}

/**
 * @tc.name: JumpToItemInGroupTestIndexInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, JumpToItemInGroupTestIndexInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scrollToItemInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    bool smooth = std::get<0>(smoothValues[0]);
    ScrollAlign align = std::get<0>(alignValues[0]);

    Ark_Int32 arkIndex = std::get<1>(indexValues[0]);
    Ark_Int32 arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: indexNegativeValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    index = std::get<0>(indexValues[0]);
    arkIndex = std::get<1>(indexValues[0]);

    for (auto&& value: indexNegativeValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }
}

/**
 * @tc.name: JumpToItemInGroupTestSmoothInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, JumpToItemInGroupTestSmoothInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scrollToItemInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    bool smooth = std::get<0>(smoothValues[0]);
    ScrollAlign align = std::get<0>(alignValues[0]);

    Ark_Int32 arkIndex = std::get<1>(indexValues[0]);
    Ark_Int32 arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: smoothValues) {
        smooth = std::get<0>(value);
        arkSmooth = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    smooth = std::get<0>(smoothValues[0]);

    EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
    accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, nullptr, &arkAlign);
}

/**
 * @tc.name: JumpToItemInGroupTestAlignInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, JumpToItemInGroupTestAlignInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->scrollToItemInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    bool smooth = std::get<0>(smoothValues[0]);
    ScrollAlign align = std::get<0>(alignValues[0]);

    Ark_Int32 arkIndex = std::get<1>(indexValues[0]);
    Ark_Int32 arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: alignInvalidValues) {
        align = std::get<0>(value);
        arkAlign = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    align = ScrollAlign::NONE;

    EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
    accessor_->scrollToItemInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup, &arkSmooth, nullptr);
}

/**
 * @tc.name: GetItemRectInGroupTestValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, GetItemRectInGroupTestValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getItemRectInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    Ark_Int32 arkIndex = std::get<1>(indexValues[0]);
    Ark_Int32 arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = Rect();

    for (auto&& value: indexValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        const auto& positions = getPositions(index);
        const auto& positionsGroup = getPositions(arkIndexInGroup);
        expectedRect = Rect(positions.first, positions.second, positionsGroup.first, positionsGroup.second);
        Ark_RectResult retVal = accessor_->getItemRectInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup);
        Rect rc = Converter::Convert<Rect>(retVal);
        EXPECT_NEAR(rc.GetOffset().GetX(), expectedRect.GetOffset().GetX(), FLT_PRECISION);
        EXPECT_NEAR(rc.GetOffset().GetY(), expectedRect.GetOffset().GetY(), FLT_PRECISION);
        EXPECT_NEAR(rc.Width(), expectedRect.Width(), FLT_PRECISION);
        EXPECT_NEAR(rc.Height(), expectedRect.Height(), FLT_PRECISION);
    }

    index = std::get<0>(indexValues[0]);
    arkIndex = std::get<1>(indexValues[0]);
    expectedRect = Rect();

    for (auto&& value: indexInGroupValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        const auto& positions = getPositions(index);
        const auto& positionsGroup = getPositions(arkIndexInGroup);
        expectedRect = Rect(positions.first, positions.second, positionsGroup.first, positionsGroup.second);
        Ark_RectResult retVal = accessor_->getItemRectInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup);
        Rect rc = Converter::Convert<Rect>(retVal);
        EXPECT_NEAR(rc.GetOffset().GetX(), expectedRect.GetOffset().GetX(), FLT_PRECISION);
        EXPECT_NEAR(rc.GetOffset().GetY(), expectedRect.GetOffset().GetY(), FLT_PRECISION);
        EXPECT_NEAR(rc.Width(), expectedRect.Width(), FLT_PRECISION);
        EXPECT_NEAR(rc.Height(), expectedRect.Height(), FLT_PRECISION);
    }
}

/**
 * @tc.name: GetItemRectInGroupTestInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, GetItemRectInGroupTestInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getItemRectInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    Ark_Int32 arkIndex = std::get<1>(indexValues[0]);
    Ark_Int32 arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = Rect();

    for (auto&& value: indexNegativeValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        Ark_RectResult retVal = accessor_->getItemRectInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup);
        Rect rc = Converter::Convert<Rect>(retVal);
        EXPECT_EQ(rc, expectedRect);
    }

    index = std::get<0>(indexValues[0]);
    arkIndex = std::get<1>(indexValues[0]);

    for (auto&& value: indexNegativeValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        Ark_RectResult retVal = accessor_->getItemRectInGroup(vmContext_, peer_, arkIndex, arkIndexInGroup);
        Rect rc = Converter::Convert<Rect>(retVal);
        EXPECT_TRUE(rc == expectedRect);
    }

    indexInGroup = std::get<0>(indexInGroupValues[0]);
    arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Ark_RectResult retVal = accessor_->getItemRectInGroup(vmContext_, peer_, -1, arkIndexInGroup);
    Rect rc = Converter::Convert<Rect>(retVal);
    EXPECT_EQ(rc, expectedRect);

    retVal = accessor_->getItemRectInGroup(vmContext_, peer_, arkIndex, -1);
    rc = Converter::Convert<Rect>(retVal);
    EXPECT_EQ(rc, expectedRect);
}

/**
 * @tc.name: GetItemIndexInGroupTestValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, GetItemIndexInGroupTestValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getVisibleListContentInfo, nullptr);

    int x = std::get<0>(indexValues[0]);
    int y = std::get<0>(indexInGroupValues[0]);
    Ark_Float64 arkX = std::get<1>(indexValues[0]);
    Ark_Float64 arkY = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = ListItemGroupIndex{x, ListItemGroupArea::IN_FOOTER_AREA, y};

    for (auto&& value: indexValues) {
        x = std::get<0>(value);
        arkX = std::get<1>(value);
        expectedRect = ListItemGroupIndex {x, ListItemGroupArea::IN_FOOTER_AREA, y};
        Ark_VisibleListContentInfo retVal = accessor_->getVisibleListContentInfo(vmContext_, peer_, arkX, arkY);
        ListItemGroupIndex rc = Converter::Convert<ListItemGroupIndex>(retVal);
        EXPECT_EQ(rc.area, expectedRect.area);
        EXPECT_EQ(rc.index, expectedRect.index);
        EXPECT_EQ(rc.indexInGroup, expectedRect.indexInGroup);
    }

    x = std::get<0>(indexValues[0]);
    arkX = std::get<1>(indexValues[0]);
    expectedRect = ListItemGroupIndex();

    for (auto&& value: indexInGroupValues) {
        y = std::get<0>(value);
        arkY = std::get<1>(value);
        expectedRect = ListItemGroupIndex {x, ListItemGroupArea::IN_FOOTER_AREA, y};
        Ark_VisibleListContentInfo retVal = accessor_->getVisibleListContentInfo(vmContext_, peer_, arkX, arkY);
        ListItemGroupIndex rc = Converter::Convert<ListItemGroupIndex>(retVal);
        EXPECT_EQ(rc.area, expectedRect.area);
        EXPECT_EQ(rc.index, expectedRect.index);
        EXPECT_EQ(rc.indexInGroup, expectedRect.indexInGroup);
    }

    y = std::get<0>(indexValues[0]);
    arkY = std::get<1>(indexValues[0]);
    expectedRect = ListItemGroupIndex();

    for (auto&& value: indexNegativeValues) {
        x = std::get<0>(value);
        arkX = std::get<1>(value);
        y = std::get<0>(value);
        arkY = std::get<1>(value);
        expectedRect = ListItemGroupIndex {x, ListItemGroupArea::IN_FOOTER_AREA, y};
        Ark_VisibleListContentInfo retVal = accessor_->getVisibleListContentInfo(vmContext_, peer_, arkX, arkY);
        ListItemGroupIndex rc = Converter::Convert<ListItemGroupIndex>(retVal);
        EXPECT_EQ(rc.area, expectedRect.area);
        EXPECT_EQ(rc.index, expectedRect.index);
        EXPECT_EQ(rc.indexInGroup, expectedRect.indexInGroup);
    }
}

/**
 * @tc.name: GetItemIndexInGroupTestInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, DISABLED_GetItemIndexInGroupTestInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getVisibleListContentInfo, nullptr);
    Ark_Float64 arkX = std::get<1>(indexValues[0]);
    Ark_Float64 arkY = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = ListItemGroupIndex();

    Ark_VisibleListContentInfo retVal = accessor_->getVisibleListContentInfo(vmContext_, peer_, -1, arkY);
    ListItemGroupIndex rc = Converter::Convert<ListItemGroupIndex>(retVal);
    EXPECT_EQ(rc.area, expectedRect.area);
    EXPECT_EQ(rc.index, expectedRect.index);
    EXPECT_EQ(rc.indexInGroup, expectedRect.indexInGroup);

    retVal = accessor_->getVisibleListContentInfo(vmContext_, peer_, arkX, -1);
    rc = Converter::Convert<ListItemGroupIndex>(retVal);
    EXPECT_EQ(rc.area, expectedRect.area);
    EXPECT_EQ(rc.index, expectedRect.index);
    EXPECT_EQ(rc.indexInGroup, expectedRect.indexInGroup);
}

/**
 * @tc.name: CloseAllSwipeActionsImplTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, CloseAllSwipeActionsImplTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->closeAllSwipeActions, nullptr);
    const int32_t contextId = 123;

    static std::optional<int32_t> checkData;
    void (*checkCallback)(const Ark_Int32 resourceId) =
        [](const Ark_Int32 resourceId) { checkData = resourceId; };
    ASSERT_FALSE(checkData.has_value());

    // setup the callback object via C-API
    auto callbackVoid = Converter::ArkValue<Callback_Void>(checkCallback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(callbackVoid);
    Ark_CloseSwipeActionOptions arkClose = {.onFinish = optCallback};
    auto arkCloseOpt = Converter::ArkValue<Opt_CloseSwipeActionOptions>(arkClose);
    accessor_->closeAllSwipeActions(vmContext_, peer_, &arkCloseOpt);

    // check the invoking result
    ASSERT_TRUE(checkData.has_value());
    EXPECT_EQ(checkData.value(), contextId);
}
} // namespace OHOS::Ace::NG
