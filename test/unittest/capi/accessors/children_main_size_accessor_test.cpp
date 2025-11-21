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
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/interfaces/native/implementation/children_main_size_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;
using ::testing::NiceMock;

namespace {
class MockChildrenMainSize : public ListChildrenMainSize {
public:
    MockChildrenMainSize() = default;
    ~MockChildrenMainSize() override = default;
    MOCK_METHOD(void, ChangeData, (const int32_t, const int32_t, const std::vector<float>&), (override));
};

const float CHILDREN_DEFAULT_SIZE = 50.0f;
const Ark_Number ARK_CHILDREN_DEFAULT_SIZE = Converter::ArkValue<Ark_Number>(CHILDREN_DEFAULT_SIZE);
} // namespace

class ChildrenMainSizeTest : public AccessorTestBaseParent<GENERATED_ArkUIChildrenMainSizeAccessor,
    &GENERATED_ArkUIAccessors::getChildrenMainSizeAccessor, ChildrenMainSizePeer> {
public:
    void SetUp() override
    {
        AccessorTestBaseParent::SetUp();
        ASSERT_NE(this->accessor_->construct, nullptr);
        this->peer_ = reinterpret_cast<ChildrenMainSizePeer*>(this->accessor_->construct(&ARK_CHILDREN_DEFAULT_SIZE));
        ASSERT_NE(this->peer_, nullptr);

        mockChildrenMainSize_ = new NiceMock<MockChildrenMainSize>();
        mockChildrenMainSizeKeeper_ = AceType::Claim(mockChildrenMainSize_);
        ASSERT_NE(mockChildrenMainSizeKeeper_, nullptr);
        auto peer = reinterpret_cast<ChildrenMainSizePeer*>(peer_);
        ASSERT_NE(peer, nullptr);
        peer->SetHandler(mockChildrenMainSizeKeeper_);
        ASSERT_NE(mockChildrenMainSize_, nullptr);
    }

    void TearDown() override
    {
        AccessorTestBaseParent::TearDown();
        mockChildrenMainSizeKeeper_ = nullptr;
        mockChildrenMainSize_ = nullptr;
    }

    NiceMock<MockChildrenMainSize> *mockChildrenMainSize_ = nullptr;
    RefPtr<NiceMock<MockChildrenMainSize>> mockChildrenMainSizeKeeper_ = nullptr;
    Ark_VMContext vmContext_ = nullptr;
};

static std::vector<std::tuple<int32_t, Ark_Number>> startValues = {
    {0, Converter::ArkValue<Ark_Number>(0)},
    {1, Converter::ArkValue<Ark_Number>(1)},
};

static std::vector<std::tuple<int32_t, Opt_Number>> deleteCountValues = {
    {1, Converter::ArkValue<Opt_Number>(1)},
    {2, Converter::ArkValue<Opt_Number>(2)},
};

static std::vector<std::tuple<float, Ark_Number>> arrayValues = {
    {100.0f, Converter::ArkValue<Ark_Number>(100.0f)},
    {200.0f, Converter::ArkValue<Ark_Number>(200.0f)},
};

static std::vector<std::tuple<int32_t, Ark_Number>> startInvalidValues = {
    {-1, Converter::ArkValue<Ark_Number>(-1)}
};

static std::vector<std::tuple<int32_t, Ark_Number>> indexInvalidValues = {
    {-1, Converter::ArkValue<Ark_Number>(-1)}
};

static std::vector<std::tuple<int32_t, Ark_Number>> updateInvalidValues = {
    {-1, Converter::ArkValue<Ark_Number>(-100.0f)}
};

static std::vector<std::tuple<int32_t, Opt_Number>> deleteCountInvalidValues = {
    {0, Converter::ArkValue<Opt_Number>(-1)},
    {-1, Converter::ArkValue<Opt_Number>(Ark_Empty())},
};

/**
 * @tc.name: CtorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, CtorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getChildDefaultSize, nullptr);

    auto retValue = Converter::Convert<float>(accessor_->getChildDefaultSize(peer_));
    EXPECT_FLOAT_EQ(retValue, CHILDREN_DEFAULT_SIZE);
}

/**
 * @tc.name: SpliceValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, SpliceValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->splice, nullptr);

    int start = std::get<0>(startValues[0]);
    Ark_Number arkStart = std::get<1>(startValues[0]);
    int deleteCount = std::get<0>(deleteCountValues[0]);
    Opt_Number arkDeleteCount = std::get<1>(deleteCountValues[0]);

    std::vector<float> array{std::get<0>(arrayValues[0]), std::get<0>(arrayValues[1])};
    auto numberArray = std::array{ std::get<1>(arrayValues[0]), std::get<1>(arrayValues[1])};
    Converter::ArkArrayHolder<Array_Number> arrayHolder(numberArray);
    Array_Number numberArrayResult = arrayHolder.ArkValue();
    Opt_Array_Number optArray = ArkValue<Opt_Array_Number>(numberArrayResult);

    for (auto&& value: startValues) {
        start = std::get<0>(value);
        arkStart = std::get<1>(value);
        EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
        accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);
    }
}

/**
 * @tc.name: SpliceInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, SpliceStartInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->splice, nullptr);

    int start = std::get<0>(startInvalidValues[0]);
    Ark_Number arkStart = std::get<1>(startInvalidValues[0]);
    int deleteCount = std::get<0>(deleteCountValues[0]);
    Opt_Number arkDeleteCount = std::get<1>(deleteCountValues[0]);

    std::vector<float> array{std::get<0>(arrayValues[0]), std::get<0>(arrayValues[1])};
    auto numberArray = std::array{ std::get<1>(arrayValues[0]), std::get<1>(arrayValues[1])};
    Converter::ArkArrayHolder<Array_Number> arrayHolder(numberArray);
    Array_Number numberArrayResult = arrayHolder.ArkValue();
    Opt_Array_Number optArray = ArkValue<Opt_Array_Number>(numberArrayResult);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(0);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(0);
    accessor_->splice(peer_, nullptr, &arkDeleteCount, &optArray);
}

/**
 * @tc.name: SpliceDeleteCountInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, SpliceDeleteCountInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->splice, nullptr);

    int start = std::get<0>(startValues[0]);
    Ark_Number arkStart = std::get<1>(startValues[0]);
    int deleteCount = std::get<0>(deleteCountInvalidValues[0]);
    Opt_Number arkDeleteCount = std::get<1>(deleteCountInvalidValues[0]);

    std::vector<float> array{std::get<0>(arrayValues[0]), std::get<0>(arrayValues[1])};
    auto numberArray = std::array{ std::get<1>(arrayValues[0]), std::get<1>(arrayValues[1])};
    Converter::ArkArrayHolder<Array_Number> arrayHolder(numberArray);
    Array_Number numberArrayResult = arrayHolder.ArkValue();
    Opt_Array_Number optArray = ArkValue<Opt_Array_Number>(numberArrayResult);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);

    deleteCount = std::get<0>(deleteCountInvalidValues[1]);
    arkDeleteCount = std::get<1>(deleteCountInvalidValues[1]);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, nullptr, &optArray);
}

/**
 * @tc.name: SpliceValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, SpliceChildrenSizeInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->splice, nullptr);

    int start = std::get<0>(startValues[0]);
    Ark_Number arkStart = std::get<1>(startValues[0]);
    int deleteCount = std::get<0>(deleteCountValues[0]);
    Opt_Number arkDeleteCount = std::get<1>(deleteCountValues[0]);

    std::vector<float> array;
    Opt_Array_Number optArray = ArkValue<Opt_Array_Number>(Ark_Empty());

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, nullptr);
}

/**
 * @tc.name: UpdateValidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, UpdateValidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->splice, nullptr);
    ASSERT_NE(accessor_->update, nullptr);

    int start = std::get<0>(startValues[0]);
    Ark_Number arkStart = std::get<1>(startValues[0]);
    int deleteCount = std::get<0>(deleteCountValues[0]);
    Opt_Number arkDeleteCount = std::get<1>(deleteCountValues[0]);

    std::vector<float> array{std::get<0>(arrayValues[0]), std::get<0>(arrayValues[1])};
    auto numberArray = std::array{ std::get<1>(arrayValues[0]), std::get<1>(arrayValues[1])};
    Converter::ArkArrayHolder<Array_Number> arrayHolder(numberArray);
    Array_Number numberArrayResult = arrayHolder.ArkValue();
    Opt_Array_Number optArray = ArkValue<Opt_Array_Number>(numberArrayResult);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);

    int index = std::get<0>(startValues[0]);
    Ark_Number arkIndex = std::get<1>(startValues[0]);
    float size = std::get<0>(arrayValues[1]);
    Ark_Number arkSize = std::get<1>(arrayValues[1]);

    std::vector<float> updateArray{size};
    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(index, 1, updateArray)).Times(1);
    accessor_->update(peer_, &arkIndex, &arkSize);
}

/**
 * @tc.name: UpdateInvalidValuesTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, UpdateInvalidValuesTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->splice, nullptr);
    ASSERT_NE(accessor_->update, nullptr);

    int start = std::get<0>(startValues[0]);
    Ark_Number arkStart = std::get<1>(startValues[0]);
    int deleteCount = std::get<0>(deleteCountValues[0]);
    Opt_Number arkDeleteCount = std::get<1>(deleteCountValues[0]);

    std::vector<float> array{std::get<0>(arrayValues[0]), std::get<0>(arrayValues[1])};
    auto numberArray = std::array{ std::get<1>(arrayValues[0]), std::get<1>(arrayValues[1])};
    Converter::ArkArrayHolder<Array_Number> arrayHolder(numberArray);
    Array_Number numberArrayResult = arrayHolder.ArkValue();
    Opt_Array_Number optArray = ArkValue<Opt_Array_Number>(numberArrayResult);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(start, deleteCount, array)).Times(1);
    accessor_->splice(peer_, &arkStart, &arkDeleteCount, &optArray);

    int index = std::get<0>(startValues[0]);
    Ark_Number arkIndex = std::get<1>(startValues[0]);
    float size = std::get<0>(arrayValues[1]);
    Ark_Number arkSize = std::get<1>(arrayValues[1]);
    std::vector<float> updateArray{size};

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(index, 1, updateArray)).Times(0);
    accessor_->update(peer_, nullptr, &arkSize);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(index, 1, updateArray)).Times(0);
    accessor_->update(peer_, &arkIndex, nullptr);

    index = std::get<0>(indexInvalidValues[0]);
    arkIndex = std::get<1>(indexInvalidValues[0]);

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(index, 1, updateArray)).Times(0);
    accessor_->update(peer_, &arkIndex, &arkSize);

    index = std::get<0>(startValues[0]);
    arkIndex = std::get<1>(startValues[0]);
    size = std::get<0>(updateInvalidValues[0]);
    arkSize = std::get<1>(updateInvalidValues[0]);
    updateArray = {size};

    EXPECT_CALL(*mockChildrenMainSize_, ChangeData(index, 1, updateArray)).Times(1);
    accessor_->update(peer_, &arkIndex, &arkSize);
}

/**
 * @tc.name: GetChildDefaultSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, GetChildDefaultSizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getChildDefaultSize, nullptr);

    auto retValue = Converter::Convert<float>(accessor_->getChildDefaultSize(peer_));
    EXPECT_FLOAT_EQ(retValue, CHILDREN_DEFAULT_SIZE);

    auto ptr = peer_->GetHandler();
    if (ptr) {
        ptr->UpdateDefaultSize(CHILDREN_DEFAULT_SIZE * 2);
    }

    retValue = Converter::Convert<float>(accessor_->getChildDefaultSize(peer_));
    EXPECT_FLOAT_EQ(retValue, CHILDREN_DEFAULT_SIZE * 2);
}

/**
 * @tc.name: SetChildDefaultSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ChildrenMainSizeTest, SetChildDefaultSizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setChildDefaultSize, nullptr);
    // valid value
    auto defSize = Converter::ArkValue<Ark_Number>(CHILDREN_DEFAULT_SIZE);
    accessor_->setChildDefaultSize(peer_, &defSize);
    auto retValue = Converter::Convert<float>(accessor_->getChildDefaultSize(peer_));
    EXPECT_FLOAT_EQ(retValue, CHILDREN_DEFAULT_SIZE);

    // invalid value
    defSize = Converter::ArkValue<Ark_Number>(-CHILDREN_DEFAULT_SIZE);
    accessor_->setChildDefaultSize(peer_, &defSize);
    retValue = Converter::Convert<float>(accessor_->getChildDefaultSize(peer_));
    EXPECT_FLOAT_EQ(retValue, CHILDREN_DEFAULT_SIZE);
}
} // namespace OHOS::Ace::NG
