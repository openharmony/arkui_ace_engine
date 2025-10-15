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
#include "frameworks/base/utils/utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/base_gesture_event_peer.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using ::testing::NiceMock;

namespace {
const std::vector<std::pair<Ark_Number, float>> arkNumberFloatXTestPlan = {
    { Converter::ArkValue<Ark_Float64>(100.00f), 100.00f },
    { Converter::ArkValue<Ark_Float64>(0.00f), 0.00f },
    { Converter::ArkValue<Ark_Float64>(-100.00f), -100.00f },
    { Converter::ArkValue<Ark_Float64>(12.34f), 12.34f },
    { Converter::ArkValue<Ark_Float64>(-56.73f), -56.73f },
};
const std::vector<std::pair<Ark_Number, float>> arkNumberFloatYTestPlan = {
    { Converter::ArkValue<Ark_Float64>(-1.01f), -1.01f },
    { Converter::ArkValue<Ark_Float64>(-0.54f), -0.54f },
    { Converter::ArkValue<Ark_Float64>(0.00f), 0.00f },
    { Converter::ArkValue<Ark_Float64>(0.98f), 0.98f },
    { Converter::ArkValue<Ark_Float64>(1.00f), 1.00f },
};
const std::vector<std::pair<Ark_Number, int32_t>> arkNumberIntTestPlan = {
    { Converter::ArkValue<Ark_Int32>(100), 100 },
    { Converter::ArkValue<Ark_Int32>(0), 0 },
    { Converter::ArkValue<Ark_Int32>(-100), -100 },
    { Converter::ArkValue<Ark_Int32>(12), 12 },
    { Converter::ArkValue<Ark_Int32>(-56), -56 },
};
const std::vector<int32_t> sizeArrayTestPlan = { 0, 1, 2, 3, 4, 5 };
} // namespace

class BaseGestureEventAccessorTest : public AccessorTestBase<GENERATED_ArkUIBaseGestureEventAccessor,
    &GENERATED_ArkUIAccessors::getBaseGestureEventAccessor, GeneratedModifier::BaseGestureEventPeerImpl> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        ASSERT_NE(peer_, nullptr);
        eventInfo_ = std::make_shared<OHOS::Ace::BaseGestureEvent>();
        ASSERT_NE(eventInfo_, nullptr);
        peer_->SetEventInfo(eventInfo_);
    }
    void TearDown() override
    {
        eventInfo_ = nullptr;
    }
    std::shared_ptr<OHOS::Ace::BaseGestureEvent> eventInfo_ = nullptr;
};

/**
 * @tc.name: setFingerListTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseGestureEventAccessorTest, setFingerListIdTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFingerList, nullptr);
    std::vector<Ark_FingerInfo> vectorData;
    std::list<FingerInfo> emptyList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (const auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        for (int index = 0; index < size; index++) {
            item.id = arkNumberIntTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->GetEventInfo()->SetFingerList(emptyList);
        EXPECT_TRUE(peer_->GetEventInfo()->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        auto result = peer_->GetEventInfo()->GetFingerList();
        ASSERT_EQ(result.size(), size);
        auto resultIt = result.begin();
        for (int index = 0; index < size; ++index, ++resultIt) {
            auto result = resultIt->fingerId_;
            auto expected = arkNumberIntTestPlan[index].second;
            EXPECT_EQ(result, expected);
        }
    }
}

/**
 * @tc.name: setFingerListGlobalXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseGestureEventAccessorTest, setFingerListGlobalXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFingerList, nullptr);
    std::vector<Ark_FingerInfo> vectorData;
    std::list<FingerInfo> emptyList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (const auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        for (int index = 0; index < size; index++) {
            item.globalX = arkNumberFloatXTestPlan[index].first;
            item.globalY = arkNumberFloatYTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->GetEventInfo()->SetFingerList(emptyList);
        EXPECT_TRUE(peer_->GetEventInfo()->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        auto result = peer_->GetEventInfo()->GetFingerList();
        ASSERT_EQ(result.size(), size);
        auto resultIt = result.begin();
        for (int index = 0; index < size; ++index, ++resultIt) {
            auto actualX = resultIt->globalLocation_.GetX();
            auto actualY = resultIt->globalLocation_.GetY();
            auto expectedX = arkNumberFloatXTestPlan[index].second;
            auto expectedY = arkNumberFloatYTestPlan[index].second;
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualY, expectedY));
        }
    }
}

/**
 * @tc.name: setFingerListLocalXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseGestureEventAccessorTest, setFingerListLocalXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFingerList, nullptr);
    std::vector<Ark_FingerInfo> vectorData;
    std::list<FingerInfo> emptyList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (const auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        for (int index = 0; index < size; index++) {
            item.localX = arkNumberFloatXTestPlan[index].first;
            item.localY = arkNumberFloatYTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->GetEventInfo()->SetFingerList(emptyList);
        EXPECT_TRUE(peer_->GetEventInfo()->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        auto result = peer_->GetEventInfo()->GetFingerList();
        ASSERT_EQ(result.size(), size);
        auto resultIt = result.begin();
        for (int index = 0; index < size; ++index, ++resultIt) {
            auto actualX = resultIt->localLocation_.GetX();
            auto actualY = resultIt->localLocation_.GetY();
            auto expectedX = arkNumberFloatXTestPlan[index].second;
            auto expectedY = arkNumberFloatYTestPlan[index].second;
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualY, expectedY));
        }
    }
}

/**
 * @tc.name: setFingerListDisplayXYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseGestureEventAccessorTest, setFingerListDisplayXYTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFingerList, nullptr);
    std::vector<Ark_FingerInfo> vectorData;
    std::list<FingerInfo> emptyList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (const auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        for (int index = 0; index < size; index++) {
            item.displayX = arkNumberFloatXTestPlan[index].first;
            item.displayY = arkNumberFloatYTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->GetEventInfo()->SetFingerList(emptyList);
        EXPECT_TRUE(peer_->GetEventInfo()->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        auto result = peer_->GetEventInfo()->GetFingerList();
        ASSERT_EQ(result.size(), size);
        auto resultIt = result.begin();
        for (int index = 0; index < size; ++index, ++resultIt) {
            auto actualX = resultIt->screenLocation_.GetX();
            auto actualY = resultIt->screenLocation_.GetY();
            auto expectedX = arkNumberFloatXTestPlan[index].second;
            auto expectedY = arkNumberFloatYTestPlan[index].second;
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualY, expectedY));
        }
    }
}

/**
 * @tc.name: GetFingerListTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(BaseGestureEventAccessorTest, GetFingerListTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFingerList, nullptr);
    auto eventInfo = peer_->GetEventInfo();
    ASSERT_NE(eventInfo, nullptr);
    std::list<FingerInfo> fingerInfo;
    const int fingerId = 0;
    const float expectedWindowX = 2.5f;
    const float expectedWindowY = 3.7f;
    Offset globalOffset(expectedWindowX, expectedWindowY);
    const float expectedX = 4.5f;
    const float expectedY = 5.7f;
    Offset localOffset(expectedX, expectedY);
    const float expectedDisplayX = 1.5f;
    const float expectedDisplayY = 1.7f;
    Offset screenOffset(expectedDisplayX, expectedDisplayY);
    auto item = FingerInfo {
        .fingerId_ = fingerId,
        .globalLocation_ = globalOffset,
        .localLocation_ = localOffset,
        .screenLocation_ = screenOffset,
    };
    fingerInfo.push_back(item);
    eventInfo->SetFingerList(fingerInfo);
    Array_FingerInfo fingerInfoArr = accessor_->getFingerList(peer_);
    ASSERT_EQ(static_cast<int32_t>(fingerInfoArr.length), 1);
    ASSERT_NE(fingerInfoArr.array, nullptr);
    EXPECT_EQ(Converter::Convert<float>(fingerInfoArr.array->displayX), expectedDisplayX);
    EXPECT_EQ(Converter::Convert<float>(fingerInfoArr.array->displayY), expectedDisplayY);
    EXPECT_EQ(Converter::Convert<float>(fingerInfoArr.array->globalX), expectedWindowX);
    EXPECT_EQ(Converter::Convert<float>(fingerInfoArr.array->globalY), expectedWindowY);
    EXPECT_EQ(Converter::Convert<float>(fingerInfoArr.array->localX), expectedX);
    EXPECT_EQ(Converter::Convert<float>(fingerInfoArr.array->localY), expectedY);
    EXPECT_EQ(Converter::Convert<int32_t>(fingerInfoArr.array->id), fingerId);
}
} // namespace OHOS::Ace::NG
