/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cmath>
#include <vector>
#include <tuple>

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/interfaces/native/implementation/drag_event_peer.h"
#include "core/interfaces/native/implementation/unified_data_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "frameworks/base/geometry/offset.h"
#include "frameworks/base/geometry/rect.h"
#include "frameworks/core/gestures/velocity.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace AccessorTestFixtures;

namespace Converter {
    void AssignArkValue(Ark_unifiedDataChannel_UnifiedData& arkData, const RefPtr<UnifiedData>& data)
    {
        auto peer = PeerUtils::CreatePeer<unifiedDataChannel_UnifiedDataPeer>();
        peer->unifiedData = data;
        arkData = peer;
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
        { "invalid value", INVALID_ENUM_VAL<Ark_DragResult>, DragRet::DRAG_DEFAULT },
    };

    const std::vector<std::tuple<std::string, DragRet, Ark_DragResult>> testFixtureEnumArkDragResultValues {
        {  "ARK_DRAG_RESULT_DRAG_SUCCESSFUL", DragRet::DRAG_SUCCESS, ARK_DRAG_RESULT_DRAG_SUCCESSFUL },
        {  "ARK_DRAG_RESULT_DRAG_FAILED", DragRet::DRAG_FAIL, ARK_DRAG_RESULT_DRAG_FAILED },
        {  "ARK_DRAG_RESULT_DRAG_CANCELED", DragRet::DRAG_CANCEL, ARK_DRAG_RESULT_DRAG_CANCELED },
        {  "ARK_DRAG_RESULT_DROP_ENABLED", DragRet::ENABLE_DROP, ARK_DRAG_RESULT_DROP_ENABLED },
        {  "ARK_DRAG_RESULT_DROP_DISABLED", DragRet::DISABLE_DROP, ARK_DRAG_RESULT_DROP_DISABLED },
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
    Ark_VMContext vmContext_ = nullptr;
};

/**
 * @tc.name: GetWindowXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetWindowXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureNumberFloatAnythingValidValues) {
        dragEvent_->SetX(value);
        auto windowX = Convert<float>(accessor_->getWindowX(peer_));
        EXPECT_EQ(windowX, Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetWindowXTest";
    }
}

/**
 * @tc.name: GetWindowYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetWindowYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureNumberFloatAnythingValidValues) {
        dragEvent_->SetY(value);
        auto windowY = Convert<float>(accessor_->getWindowY(peer_));
        EXPECT_EQ(windowY, Convert<float>(expected)) <<
            "Input value is: " << input << ", method: GetWindowYTest";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, DISABLED_SetResultTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumDragResultValues) {
        accessor_->setResult(peer_, value);
        EXPECT_EQ(dragEvent_->GetResult(), expected) <<
            "Input value is: " << input << ", method: SetResult";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetResultTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumArkDragResultValues) {
        dragEvent_->SetResult(value);
        EXPECT_EQ(accessor_->getResult(peer_), expected) <<
            "Input value is: " << input << ", method: SetResult";
    }
}

/**
 * @tc.name: SetResultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetPreviewRectTest, TestSize.Level1)
{
    float x = 5.f;
    float y = 8.f;
    float width = 55.f;
    float height = 40.f;
    Rect rect(x, y, width, height);
    dragEvent_->SetPreviewRect(rect);
    auto arkRect = accessor_->getPreviewRect(peer_);

    auto check = [](const Opt_Length& actual, float expected) {
        auto dim = Converter::OptConvert<Dimension>(actual);
        ASSERT_TRUE(dim);
        EXPECT_FLOAT_EQ(dim.value().Value(), expected);
        EXPECT_EQ(dim.value().Unit(), DimensionUnit::VP);
    };

    check(arkRect.x, x);
    check(arkRect.y, y);
    check(arkRect.width, width);
    check(arkRect.height, height);
}

/**
 * @tc.name: SetDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, SetDataTest, TestSize.Level1)
{
    auto unifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    auto arkUnifiedData = ArkValue<Ark_unifiedDataChannel_UnifiedData>(unifiedData);
    accessor_->setData(peer_, arkUnifiedData);
    ASSERT_NE(dragEvent_->GetData(), nullptr);
    EXPECT_EQ(dragEvent_->GetData()->GetSize(), COUNTER_NUMBER_TEN_HANDLE) <<
        "Input value is: " << COUNTER_NUMBER_TEN_HANDLE << ", method: setData";
}

/**
 * @tc.name: GetDataTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetDataTest, TestSize.Level1)
{
    auto unifiedData = AceType::MakeRefPtr<UnifiedDataMock>();
    auto arkUnifiedData = ArkValue<Ark_unifiedDataChannel_UnifiedData>(unifiedData);
    accessor_->setData(peer_, arkUnifiedData);
    auto getDataOpt = accessor_->getData(peer_);
    auto getData = Converter::GetOpt(getDataOpt);
    ASSERT_NE(getData, std::nullopt);
    auto dataPeer = getData.value();
    ASSERT_NE(dataPeer, nullptr);
    ASSERT_NE(dataPeer->unifiedData, nullptr);
    EXPECT_EQ(dataPeer->unifiedData->GetSize(), COUNTER_NUMBER_TEN_HANDLE) <<
        "Input value is: " << COUNTER_NUMBER_TEN_HANDLE << ", method: getData";
}

/**
 * @tc.name: GetDataInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetDataInvalidTest, TestSize.Level1)
{
    auto dataPeerOpt = accessor_->getData(nullptr);
    auto dataPeer = Converter::GetOpt(dataPeerOpt);
    ASSERT_EQ(dataPeer, std::nullopt);
}

/**
 * @tc.name: GetUseCustomDropAnimationTest
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
 * @tc.name: SetUseCustomDropAnimationTest
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

/**
 * @tc.name: GetDisplayXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetDisplayXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureNumberFloatAnythingValidValues) {
        dragEvent_->SetScreenX(value);
        auto x = Convert<float>(accessor_->getDisplayX(peer_));
        EXPECT_FLOAT_EQ(x, Convert<float>(expected)) <<
            "Input value is: " << input << ", method: getDisplayX";
    }
}

/**
 * @tc.name: GetDisplayYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetDisplayYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureNumberFloatAnythingValidValues) {
        dragEvent_->SetScreenY(value);
        auto y = Convert<float>(accessor_->getDisplayY(peer_));
        EXPECT_FLOAT_EQ(y, Convert<float>(expected)) <<
            "Input value is: " << input << ", method: getDisplayY";
    }
}

/**
 * @tc.name: GetVelocityXTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetVelocityXTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureNumberFloatAnythingValidValues) {
        auto offset = Offset(value, 0.0);
        auto velocity = Velocity(offset);
        dragEvent_->SetVelocity(velocity);
        auto velocityX = Convert<float>(accessor_->getVelocityX(peer_));
        EXPECT_FLOAT_EQ(velocityX, Convert<float>(expected)) <<
            "Input value is: " << input << ", method: getVelocityX";
        auto arkVelocity = Convert<float>(accessor_->getVelocity(peer_));
        EXPECT_FLOAT_EQ(arkVelocity, abs(Convert<float>(expected))) <<
            "Input value is: " << input << ", method: getVelocity";
    }
}

/**
 * @tc.name: GetVelocityYTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetVelocityYTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureNumberFloatAnythingValidValues) {
        auto offset = Offset(0.0, value);
        auto velocity = Velocity(offset);
        dragEvent_->SetVelocity(velocity);
        auto velocityY = Convert<float>(accessor_->getVelocityY(peer_));
        EXPECT_FLOAT_EQ(velocityY, Convert<float>(expected)) <<
            "Input value is: " << input << ", method: getVelocityY";
        auto arkVelocity = Convert<float>(accessor_->getVelocity(peer_));
        EXPECT_FLOAT_EQ(arkVelocity, abs(Convert<float>(expected))) <<
            "Input value is: " << input << ", method: getVelocity";
    }
}

/**
 * @tc.name: GetVelocityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetVelocityTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureVelocityValues) {
        auto offset = Offset(value, value);
        auto velocity = Velocity(offset);
        dragEvent_->SetVelocity(velocity);
        auto arkVelocity = Convert<float>(accessor_->getVelocity(peer_));
        EXPECT_FLOAT_EQ(arkVelocity, abs(Convert<float>(expected))) <<
            "Input value is: " << input << ", method: getVelocity";
    }
}

/**
 * @tc.name: SetDragBehaviorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, SetDragBehaviorTest, TestSize.Level1)
{
    EXPECT_EQ(OHOS::Ace::DragBehavior::UNKNOWN, dragEvent_->GetDragBehavior());
    for (auto& [input, value, expected] : testFixtureEnumDragBehaviorValues) {
        accessor_->setDragBehavior(peer_, value);
        EXPECT_EQ(expected, dragEvent_->GetDragBehavior()) <<
            "Input value is: " << input << ", method: setDragBehavior";
    }
}

/**
 * @tc.name: SetDragBehaviorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetDragBehaviorTest, TestSize.Level1)
{
    for (auto& [input, value, expected] : testFixtureEnumArkDragBehaviorValues) {
        dragEvent_->SetDragBehavior(value);
        EXPECT_EQ(expected, accessor_->getDragBehavior(peer_)) <<
            "Input value is: " << input << ", method: getDragBehavior";
    }
}

/**
 * @tc.name: GetModifierKeyStateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, GetModifierKeyStateTest, TestSize.Level1)
{
    const std::vector<std::tuple<std::vector<std::string>, std::vector<KeyCode>, bool>> TEST_PLAN = {
        { {"ctrl"}, {KeyCode::KEY_CTRL_LEFT}, true },
        { {"ctrl"}, {KeyCode::KEY_CTRL_RIGHT}, true },
        { {"shift"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"ctrl", "shift"}, {KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_SHIFT_RIGHT}, true },
        { {"shift", "alt"}, {KeyCode::KEY_ALT_LEFT, KeyCode::KEY_SHIFT_RIGHT}, true },
        { {"shift", "ctrl", "alt"}, {KeyCode::KEY_CTRL_LEFT}, false },
        { {"fn"}, {KeyCode::KEY_CTRL_LEFT}, false }
    };

    auto getter = Converter::OptConvert<ModifierKeyStateGetter>(accessor_->getGetModifierKeyState(peer_));
    ASSERT_TRUE(getter.has_value());
    auto callback = CallbackHelper(getter.value());

    auto getResult = [&callback](const Array_String& keys) -> bool {
        auto arkResult = callback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(keys);
        return Converter::Convert<bool>(arkResult);
    };

    for (auto& [param, value, expected] : TEST_PLAN) {
        Converter::ArkArrayHolder<Array_String> stringHolder(param);
        Array_String stringArrayValues = stringHolder.ArkValue();
        dragEvent_->SetPressedKeyCodes(value);
        bool result = getResult(stringArrayValues);
        EXPECT_EQ(Converter::Convert<bool>(result), expected);
    }
}

/**
 * @tc.name: GetSummaryTestDefault
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, DISABLED_GetSummaryTestDefault, TestSize.Level1)
{
#ifdef WRONG_GEN
    ASSERT_NE(accessor_->getSummary, nullptr);
    auto checkOpt = accessor_->getSummary(peer_);
    auto check = Converter::GetOpt(checkOpt).value();
    ASSERT_NE(check, std::nullopt);
    auto checkValue = check.value();
    ASSERT_NE(checkValue, nullptr);
    EXPECT_EQ(checkValue.summary.size, 0);
    EXPECT_EQ(checkValue.summary.keys, nullptr);
    EXPECT_EQ(checkValue.summary.values, nullptr);
    EXPECT_EQ(checkValue.totalSize, 0);
#endif
}

/**
 * @tc.name: GetSummaryTestValid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(DragEventAccessorTest, DISABLED_GetSummaryTestValid, TestSize.Level1)
{
#ifdef WRONG_GEN
    std::map<std::string, int64_t> expectedMap = {
        {"a", 23},
        {"b", 45},
        {"c", 67},
    };
    ASSERT_NE(peer_->dragInfo, nullptr);
    peer_->dragInfo->SetSummary(expectedMap);

    ASSERT_NE(accessor_->getSummary, nullptr);
    auto checkOpt = accessor_->getSummary(peer_);
    auto check = Converter::GetOpt(checkOpt);
    ASSERT_NE(check, std::nullopt);
    auto checkValue = check.value();
    ASSERT_NE(checkValue, nullptr);
    EXPECT_EQ(checkValue.summary.size, expectedMap.size());
    EXPECT_EQ(checkValue.summary.keys, nullptr);
    EXPECT_EQ(checkValue.summary.values, nullptr);

    int64_t expectedTotal = 0;
    int idx = 0;
    for (auto item: expectedMap) {
        EXPECT_EQ(Converter::Convert<std::string>(check.summary.keys[idx]), item.first);
        EXPECT_EQ(Converter::Convert<int64_t>(check.summary.values[idx]), item.second);
        expectedTotal += item.second;
        idx++;
    }
    EXPECT_EQ(Converter::Convert<int64_t>(check.totalSize), expectedTotal);
#endif
}
} // namespace OHOS::Ace::NG