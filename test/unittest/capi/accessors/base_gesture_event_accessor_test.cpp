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
std::vector<std::pair<Ark_Number, float>> arkNumberFloatXTestPlan = {
    { Converter::ArkValue<Ark_Number>(100.00f), 100.00f },
    { Converter::ArkValue<Ark_Number>(0.00f), 0.00f },
    { Converter::ArkValue<Ark_Number>(-100.00f), -100.00f },
    { Converter::ArkValue<Ark_Number>(12.34f), 12.34f },
    { Converter::ArkValue<Ark_Number>(-56.73f), -56.73f },
};
std::vector<std::pair<Ark_Number, float>> arkNumberFloatYTestPlan = {
    { Converter::ArkValue<Ark_Number>(-1.01f), -1.01f },
    { Converter::ArkValue<Ark_Number>(-0.54f), -0.54f },
    { Converter::ArkValue<Ark_Number>(0.00f), 0.00f },
    { Converter::ArkValue<Ark_Number>(0.98f), 0.98f },
    { Converter::ArkValue<Ark_Number>(1.00f), 1.00f },
};
std::vector<std::pair<Ark_Number, int32_t>> arkNumberIntTestPlan = {
    { Converter::ArkValue<Ark_Number>(100), 100 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-100), -100 },
    { Converter::ArkValue<Ark_Number>(12), 12 },
    { Converter::ArkValue<Ark_Number>(-56), -56 },
};
std::vector<int32_t> sizeArrayTestPlan = { 0, 1, 2, 3, 4, 5 };
} // namespace

class BaseGestureEventAccessorTest : public AccessorTestBase<GENERATED_ArkUIBaseGestureEventAccessor,
    &GENERATED_ArkUIAccessors::getBaseGestureEventAccessor, GeneratedModifier::SomeGestureEventPeer<bool>> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        peer_ = new GeneratedModifier::SomeGestureEventPeer<bool>();
        ASSERT_NE(peer_, nullptr);
    }
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
    std::list<FingerInfo> fingerList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        fingerList.clear();
        for (int index = 0; index < size; index++) {
            item.id = arkNumberIntTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->SetFingerList(fingerList);
        EXPECT_TRUE(peer_->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        EXPECT_EQ(peer_->GetFingerList().empty(), size == 0);
        auto result = peer_->GetFingerList();
        std::vector<FingerInfo> vec(result.begin(), result.end());
        for (int index = 0; index < size; index++) {
            auto result = vec[index].fingerId_;
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
    std::list<FingerInfo> fingerList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        fingerList.clear();
        for (int index = 0; index < size; index++) {
            item.globalX = arkNumberFloatXTestPlan[index].first;
            item.globalY = arkNumberFloatYTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->SetFingerList(fingerList);
        EXPECT_TRUE(peer_->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        EXPECT_EQ(peer_->GetFingerList().empty(), size == 0);
        std::list<FingerInfo> result = peer_->GetFingerList();
        std::vector<FingerInfo> vec(result.begin(), result.end());
        for (int index = 0; index < size; index++) {
            auto actualX = vec[index].globalLocation_.GetX();
            auto actualY = vec[index].globalLocation_.GetY();
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
    std::list<FingerInfo> fingerList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        fingerList.clear();
        for (int index = 0; index < size; index++) {
            item.localX = arkNumberFloatXTestPlan[index].first;
            item.localY = arkNumberFloatYTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->SetFingerList(fingerList);
        EXPECT_TRUE(peer_->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        EXPECT_EQ(peer_->GetFingerList().empty(), size == 0);
        std::list<FingerInfo> result = peer_->GetFingerList();
        std::vector<FingerInfo> vec(result.begin(), result.end());
        for (int index = 0; index < size; index++) {
            auto actualX = vec[index].localLocation_.GetX();
            auto actualY = vec[index].localLocation_.GetY();
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
    std::list<FingerInfo> fingerList;
    auto item = Ark_FingerInfo {
        .id = arkNumberIntTestPlan[0].first,
        .globalX = arkNumberFloatXTestPlan[0].first,
        .globalY = arkNumberFloatYTestPlan[0].first,
        .localX = arkNumberFloatXTestPlan[1].first,
        .localY = arkNumberFloatYTestPlan[1].first,
        .displayX = arkNumberFloatXTestPlan[2].first,
        .displayY = arkNumberFloatYTestPlan[2].first,
    };
    for (auto& size : sizeArrayTestPlan) {
        vectorData.clear();
        fingerList.clear();
        for (int index = 0; index < size; index++) {
            item.displayX = arkNumberFloatXTestPlan[index].first;
            item.displayY = arkNumberFloatYTestPlan[index].first;
            vectorData.push_back(item);
        }
        Converter::ArkArrayHolder<Array_FingerInfo> vectorHolder(vectorData);
        Array_FingerInfo fingerArray = vectorHolder.ArkValue();
        peer_->SetFingerList(fingerList);
        EXPECT_TRUE(peer_->GetFingerList().empty());
        accessor_->setFingerList(peer_, &fingerArray);
        EXPECT_EQ(peer_->GetFingerList().empty(), size == 0);
        std::list<FingerInfo> result = peer_->GetFingerList();
        std::vector<FingerInfo> vec(result.begin(), result.end());
        for (int index = 0; index < size; index++) {
            auto actualX = vec[index].screenLocation_.GetX();
            auto actualY = vec[index].screenLocation_.GetY();
            auto expectedX = arkNumberFloatXTestPlan[index].second;
            auto expectedY = arkNumberFloatYTestPlan[index].second;
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualX, expectedX));
            EXPECT_TRUE(LessOrEqualCustomPrecision(actualY, expectedY));
        }
    }
}
} // namespace OHOS::Ace::NG
