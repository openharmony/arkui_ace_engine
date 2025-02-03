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

#include <vector>
#include <tuple>

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"
#include "node_api.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

namespace GeneratedModifier {
    const GENERATED_ArkUIUnifiedDataAccessor* GetUnifiedDataAccessor();
}

namespace Converter {
    void AssignArkValue(Ark_UnifiedData& arkData, const RefPtr<UnifiedData>& data)
    {
        const auto peer = reinterpret_cast<UnifiedDataPeer*>(GeneratedModifier::GetUnifiedDataAccessor()->ctor());
        peer->unifiedData = data;
        arkData.ptr = peer;
    }
}

namespace {
    using namespace Converter;

    constexpr int32_t COUNTER_NUMBER_TEN_HANDLE = 10;

    class UnifiedDataMock : public Ace::UnifiedData {
    public:
        int64_t GetSize() override
        {
            return COUNTER_NUMBER_TEN_HANDLE;
        }
    };

    const std::vector<std::tuple<std::string, Ark_DragResult, DragRet>> testFixtureEnumDragResultValues {
        { "ARK_DRAG_RESULT_DRAG_SUCCESSFUL", ARK_DRAG_RESULT_DRAG_SUCCESSFUL, DragRet::DRAG_SUCCESS },
        { "ARK_DRAG_RESULT_DRAG_FAILED", ARK_DRAG_RESULT_DRAG_FAILED,  DragRet::DRAG_FAIL },
        { "ARK_DRAG_RESULT_DRAG_CANCELED", ARK_DRAG_RESULT_DRAG_CANCELED, DragRet::DRAG_CANCEL },
        { "ARK_DRAG_RESULT_DROP_ENABLED", ARK_DRAG_RESULT_DROP_ENABLED, DragRet::ENABLE_DROP },
        { "ARK_DRAG_RESULT_DROP_DISABLED", ARK_DRAG_RESULT_DROP_DISABLED, DragRet::DISABLE_DROP },
        { "ARK_DRAG_RESULT_INVALID", static_cast<Ark_DragResult>(-1), DragRet::DISABLE_DROP },
    };
} // namespace

class DragEventAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIDragEventAccessor,
        &GENERATED_ArkUIAccessors::getDragEventAccessor, DragEventPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        dragEvent_ = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
        ASSERT_NE(dragEvent_, nullptr);
        peer_->dragInfo = dragEvent_;
    }
    RefPtr<OHOS::Ace::DragEvent> dragEvent_ = nullptr;
};

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetWindowXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureInt32WithNegativeValues) {
        dragEvent_->SetX(expected);
        auto windowX = accessor_->getWindowX(peer_);
        EXPECT_EQ(Convert<int32_t>(windowX), expected) <<
            "Input value is: " << input << ", method: GetWindowXTest";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetWindowYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureInt32WithNegativeValues) {
        dragEvent_->SetY(expected);
        auto windowY = accessor_->getWindowY(peer_);
        EXPECT_EQ(Convert<int32_t>(windowY), expected) <<
            "Input value is: " << input << ", method: GetWindowYTest";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureInt32WithNegativeValues) {
        dragEvent_->SetX(expected);
        auto x = accessor_->getX(peer_);
        EXPECT_EQ(Convert<int32_t>(x), expected) <<
            "Input value is: " << input << ", method: GetXTest";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureInt32WithNegativeValues) {
        dragEvent_->SetY(expected);
        auto y = accessor_->getY(peer_);
        EXPECT_EQ(Convert<int32_t>(y), expected) <<
            "Input value is: " << input << ", method: GetYTest";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, SetResultTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumDragResultValues) {
        accessor_->setResult(peer_, value);
        EXPECT_EQ(dragEvent_->GetResult(), expected) <<
            "Input value is: " << input << ", method: SetResult";
    }
}

/**
 * @tc.name: setDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, setDataTest, TestSize.Level1)
{
    auto unifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    auto data = AceType::DynamicCast<UnifiedData>(unifiedData);
    auto arkUnifiedData = ArkValue<Ark_UnifiedData>(data);
    accessor_->setData(peer_, &arkUnifiedData);
    ASSERT_NE(dragEvent_->GetData(), nullptr);
    EXPECT_EQ(dragEvent_->GetData()->GetSize(), COUNTER_NUMBER_TEN_HANDLE) <<
        "Input value is: " << COUNTER_NUMBER_TEN_HANDLE << ", method: setData";
}

/**
 * @tc.name: setDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, getDataTest, TestSize.Level1)
{
    auto unifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    auto data = AceType::DynamicCast<UnifiedData>(unifiedData);
    auto arkUnifiedData = ArkValue<Ark_UnifiedData>(data);
    accessor_->setData(peer_, &arkUnifiedData);
    auto getData = accessor_->getData(peer_);
    ASSERT_NE(getData, nullptr);
    auto dataPeer = reinterpret_cast<UnifiedDataPeer*>(getData);
    ASSERT_NE(dataPeer->unifiedData, nullptr);
    EXPECT_EQ(dataPeer->unifiedData->GetSize(), COUNTER_NUMBER_TEN_HANDLE) <<
        "Input value is: " << COUNTER_NUMBER_TEN_HANDLE << ", method: getData";
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetUseCustomDropAnimationTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureBooleanValues) {
        dragEvent_->UseCustomAnimation(expected);
        auto useCustomDropAnimation = accessor_->getUseCustomDropAnimation(peer_);
        EXPECT_EQ(Convert<bool>(useCustomDropAnimation), expected) <<
            "Input value is: " << input << ", method: GetYTest";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, SetUseCustomDropAnimationTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureBooleanValues) {
        accessor_->setUseCustomDropAnimation(peer_, value);
        EXPECT_EQ(dragEvent_->IsUseCustomAnimation(), expected) <<
            "Input value is: " << input << ", method: GetYTest";
    }
}

} // namespace OHOS::Ace::NG