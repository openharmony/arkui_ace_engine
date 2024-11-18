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
#include "core/interfaces/arkoala/implementation/list_scroller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "node_api.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

namespace {
class StubListScrollController : public ScrollControllerBase {
public:
    StubListScrollController() = default;
    ~StubListScrollController() override = default;

    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const override
    {
        if (index < 0 || indexInGroup < 0) {
            return Rect();
        }
        return Rect(index, index, indexInGroup, indexInGroup);
    }

    ListItemGroupIndex GetItemIndexInGroup(double x, double y) const override
    {
        ListItemGroupIndex itemGroupIndex = { x, y, -1 };
        return itemGroupIndex;
    }
};

class MockListScrollController : public StubListScrollController {
public:
    MockListScrollController() = default;
    ~MockListScrollController() override = default;

    MOCK_METHOD(void, JumpToItemInGroup, (int32_t, int32_t, bool, ScrollAlign, int32_t));
    MOCK_METHOD(Rect, GetItemRectInGroup, (int32_t, int32_t), (const override));
    MOCK_METHOD(ListItemGroupIndex, GetItemIndexInGroup, (double, double), (const override));
    MOCK_METHOD(void, CloseAllSwipeActions, (OnFinishFunc&&));
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
        auto peerImpl = reinterpret_cast<GeneratedModifier::ListScrollerPeerImpl*>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->SetController(mockListScrollerControllerKeeper_);
        ASSERT_NE(mockListScrollerController_, nullptr);
    }

    void TearDown() override
    {
        mockListScrollerControllerKeeper_ = nullptr;
        mockListScrollerController_ = nullptr;
    }

    MockListScrollController *mockListScrollerController_ = nullptr;
    RefPtr<MockListScrollController> mockListScrollerControllerKeeper_ = nullptr;
};

static std::vector<std::tuple<int32_t, Ark_Number>> indexValues = {
    {8, Converter::ArkValue<Ark_Number>(8)},
    {99, Converter::ArkValue<Ark_Number>(99)},
    {0, Converter::ArkValue<Ark_Number>(0)},
};

static std::vector<std::tuple<int32_t, Ark_Number>> indexInGroupValues = {
    {5, Converter::ArkValue<Ark_Number>(5)},
    {77, Converter::ArkValue<Ark_Number>(77)},
    {0, Converter::ArkValue<Ark_Number>(0)},
};

static std::vector<std::tuple<int32_t, Ark_Number>> indexNegativeValues = {
    {-1, Converter::ArkValue<Ark_Number>(-1)},
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

    Ark_Number arkIndex = std::get<1>(indexValues[0]);
    Ark_Number arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: indexValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    for (auto&& value: indexInGroupValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    for (auto&& value: alignValues) {
        align = std::get<0>(value);
        arkAlign = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    for (auto&& value: smoothValues) {
        smooth = std::get<0>(value);
        arkSmooth = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
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

    Ark_Number arkIndex = std::get<1>(indexValues[0]);
    Ark_Number arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: indexNegativeValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    index = std::get<0>(indexValues[0]);
    arkIndex = std::get<1>(indexValues[0]);

    for (auto&& value: indexNegativeValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    indexInGroup = std::get<0>(indexInGroupValues[0]);
    arkIndexInGroup = std::get<1>(indexInGroupValues[0]);

    EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(0);
    accessor_->scrollToItemInGroup(peer_, nullptr, &arkIndexInGroup, &arkSmooth, &arkAlign);
    accessor_->scrollToItemInGroup(peer_, &arkIndex, nullptr, &arkSmooth, &arkAlign);
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

    Ark_Number arkIndex = std::get<1>(indexValues[0]);
    Ark_Number arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: smoothValues) {
        smooth = std::get<0>(value);
        arkSmooth = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    smooth = std::get<0>(smoothValues[0]);

    EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
    accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, nullptr, &arkAlign);
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

    Ark_Number arkIndex = std::get<1>(indexValues[0]);
    Ark_Number arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    Opt_Boolean arkSmooth = std::get<1>(smoothValues[0]);
    Opt_ScrollAlign arkAlign = std::get<1>(alignValues[0]);

    for (auto&& value: alignInvalidValues) {
        align = std::get<0>(value);
        arkAlign = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
        accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, &arkAlign);
    }

    align = ScrollAlign::NONE;

    EXPECT_CALL(*mockListScrollerController_, JumpToItemInGroup(index, indexInGroup, smooth, align, 3)).Times(1);
    accessor_->scrollToItemInGroup(peer_, &arkIndex, &arkIndexInGroup, &arkSmooth, nullptr);
}

/**
 * @tc.name: GetItemRectInGroupTestValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, DISABLED_GetItemRectInGroupTestValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getItemRectInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    Ark_Number arkIndex = std::get<1>(indexValues[0]);
    Ark_Number arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = Rect();

    for (auto&& value: indexValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        expectedRect = Rect(index, index, indexInGroup, indexInGroup);
        EXPECT_CALL(*mockListScrollerController_,
            GetItemRectInGroup(index, indexInGroup)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getItemRectInGroup(peer_, &arkIndex, &arkIndexInGroup);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "rect" data
        Rect rc = *(reinterpret_cast<Rect*>(result));
        EXPECT_TRUE(rc == expectedRect);
    }

    index = std::get<0>(indexValues[0]);
    arkIndex = std::get<1>(indexValues[0]);
    expectedRect = Rect();
    
    for (auto&& value: indexInGroupValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        expectedRect = Rect(index, index, indexInGroup, indexInGroup);
        EXPECT_CALL(*mockListScrollerController_,
            GetItemRectInGroup(index, indexInGroup)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getItemRectInGroup(peer_, &arkIndex, &arkIndexInGroup);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "rect" data
        Rect rc = *(reinterpret_cast<Rect*>(result));
        EXPECT_TRUE(rc == expectedRect);
    }
}

/**
 * @tc.name: GetItemRectInGroupTestInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, DISABLED_GetItemRectInGroupTestInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getItemRectInGroup, nullptr);

    int index = std::get<0>(indexValues[0]);
    int indexInGroup = std::get<0>(indexInGroupValues[0]);
    Ark_Number arkIndex = std::get<1>(indexValues[0]);
    Ark_Number arkIndexInGroup = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = Rect();

    for (auto&& value: indexNegativeValues) {
        index = std::get<0>(value);
        arkIndex = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_,
            GetItemRectInGroup(index, indexInGroup)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getItemRectInGroup(peer_, &arkIndex, &arkIndexInGroup);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "rect" data
        Rect rc = *(reinterpret_cast<Rect*>(result));
        EXPECT_TRUE(rc == expectedRect);
    }

    index = std::get<0>(indexValues[0]);
    arkIndex = std::get<1>(indexValues[0]);

    for (auto&& value: indexNegativeValues) {
        indexInGroup = std::get<0>(value);
        arkIndexInGroup = std::get<1>(value);
        EXPECT_CALL(*mockListScrollerController_,
            GetItemRectInGroup(index, indexInGroup)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getItemRectInGroup(peer_, &arkIndex, &arkIndexInGroup);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "rect" data
        Rect rc = *(reinterpret_cast<Rect*>(result));
        EXPECT_TRUE(rc == expectedRect);
    }

    indexInGroup = std::get<0>(indexInGroupValues[0]);
    arkIndexInGroup = std::get<1>(indexInGroupValues[0]);

    EXPECT_CALL(*mockListScrollerController_, GetItemRectInGroup(index, indexInGroup)).Times(0);
    Ark_NativePointer result = accessor_->getItemRectInGroup(peer_, nullptr, &arkIndexInGroup);
    // wait for return value type change from Ark_NativePointer to another type
    // which is acceptable to "rect" data
    Rect rc = *(reinterpret_cast<Rect*>(result));
    EXPECT_TRUE(rc == expectedRect);

    EXPECT_CALL(*mockListScrollerController_, GetItemRectInGroup(index, indexInGroup)).Times(0);
    result = accessor_->getItemRectInGroup(peer_, &arkIndex, nullptr);
    // wait for return value type change from Ark_NativePointer to another type
    // which is acceptable to "rect" data
    rc = *(reinterpret_cast<Rect*>(result));
    EXPECT_TRUE(rc == expectedRect);
}

/**
 * @tc.name: GetItemIndexInGroupTestValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, DISABLED_GetItemIndexInGroupTestValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getVisibleListContentInfo, nullptr);

    int x = std::get<0>(indexValues[0]);
    int y = std::get<0>(indexInGroupValues[0]);
    Ark_Number arkX = std::get<1>(indexValues[0]);
    Ark_Number arkY = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = ListItemGroupIndex();

    for (auto&& value: indexValues) {
        x = std::get<0>(value);
        arkX = std::get<1>(value);
        expectedRect = ListItemGroupIndex {x, y, -1};
        EXPECT_CALL(*mockListScrollerController_, GetItemIndexInGroup(x, y)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getVisibleListContentInfo(peer_, &arkX, &arkY);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "ListItemGroupIndex" data
        ListItemGroupIndex rc = *(reinterpret_cast<ListItemGroupIndex*>(result));
        EXPECT_TRUE(rc.area == expectedRect.area);
        EXPECT_TRUE(rc.index == expectedRect.index);
        EXPECT_TRUE(rc.indexInGroup == expectedRect.indexInGroup);
    }

    x = std::get<0>(indexValues[0]);
    arkX = std::get<1>(indexValues[0]);
    expectedRect = ListItemGroupIndex();
    
    for (auto&& value: indexInGroupValues) {
        y = std::get<0>(value);
        arkY = std::get<1>(value);
        expectedRect = ListItemGroupIndex {x, y, -1};
        EXPECT_CALL(*mockListScrollerController_, GetItemIndexInGroup(x, y)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getVisibleListContentInfo(peer_, &arkX, &arkY);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "ListItemGroupIndex" data
        ListItemGroupIndex rc = *(reinterpret_cast<ListItemGroupIndex*>(result));
        EXPECT_TRUE(rc.area == expectedRect.area);
        EXPECT_TRUE(rc.index == expectedRect.index);
        EXPECT_TRUE(rc.indexInGroup == expectedRect.indexInGroup);
    }

    y = std::get<0>(indexValues[0]);
    arkY = std::get<1>(indexValues[0]);
    expectedRect = ListItemGroupIndex();
    
    for (auto&& value: indexNegativeValues) {
        x = std::get<0>(value);
        arkX = std::get<1>(value);
        y = std::get<0>(value);
        arkY = std::get<1>(value);
        expectedRect = ListItemGroupIndex {x, y, -1};
        EXPECT_CALL(*mockListScrollerController_, GetItemIndexInGroup(x, y)).Times(1).WillOnce(Return(expectedRect));
        Ark_NativePointer result = accessor_->getVisibleListContentInfo(peer_, &arkX, &arkY);
        // wait for return value type change from Ark_NativePointer to another type
        // which is acceptable to "ListItemGroupIndex" data
        ListItemGroupIndex rc = *(reinterpret_cast<ListItemGroupIndex*>(result));
        EXPECT_TRUE(rc.area == expectedRect.area);
        EXPECT_TRUE(rc.index == expectedRect.index);
        EXPECT_TRUE(rc.indexInGroup == expectedRect.indexInGroup);
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

    int x = std::get<0>(indexValues[0]);
    int y = std::get<0>(indexInGroupValues[0]);
    Ark_Number arkX = std::get<1>(indexValues[0]);
    Ark_Number arkY = std::get<1>(indexInGroupValues[0]);
    auto expectedRect = ListItemGroupIndex();

    EXPECT_CALL(*mockListScrollerController_, GetItemIndexInGroup(x, y)).Times(0);
    Ark_NativePointer result = accessor_->getVisibleListContentInfo(peer_, nullptr, &arkY);
    // wait for return value type change from Ark_NativePointer to another type
    // which is acceptable to "ListItemGroupIndex" data
    ListItemGroupIndex rc = *(reinterpret_cast<ListItemGroupIndex*>(result));
    EXPECT_TRUE(rc.area == expectedRect.area);
    EXPECT_TRUE(rc.index == expectedRect.index);
    EXPECT_TRUE(rc.indexInGroup == expectedRect.indexInGroup);

    EXPECT_CALL(*mockListScrollerController_, GetItemIndexInGroup(x, y)).Times(0);
    result = accessor_->getVisibleListContentInfo(peer_, &arkX, nullptr);
    // wait for return value type change from Ark_NativePointer to another type
    // which is acceptable to "ListItemGroupIndex" data
    rc = *(reinterpret_cast<ListItemGroupIndex*>(result));
    EXPECT_TRUE(rc.area == expectedRect.area);
    EXPECT_TRUE(rc.index == expectedRect.index);
    EXPECT_TRUE(rc.indexInGroup == expectedRect.indexInGroup);
}

/**
 * @tc.name: CloseAllSwipeActionsImplTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListScrollerAccessorTest, DISABLED_CloseAllSwipeActionsImplTest, TestSize.Level1)
{
    // not implemented yet
}
} // namespace OHOS::Ace::NG
