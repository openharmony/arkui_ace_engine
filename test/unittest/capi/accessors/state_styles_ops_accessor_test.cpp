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

#include "accessor_test_base.h"
#include "gmock/gmock.h"

#include "core/components_ng/pattern/button/button_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const int32_t TEST_RES_ID = 123;
const int32_t TEST_NODE_ID = 1002;
const int32_t TEST_STATE_FOCUSED = 2;
const int32_t TEST_STATE_PRESSED = 3;
} // namespace

class StateStylesOpsAccessorTest : public StaticAccessorTest<GENERATED_ArkUIStateStylesOpsAccessor,
    &GENERATED_ArkUIAccessors::getStateStylesOpsAccessor> {
};

/**
 * @tc.name: onStateStyleChangeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(StateStylesOpsAccessorTest, onStateStyleChangeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->onStateStyleChange, nullptr);
    RefPtr<FrameNode> frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CHECKBOX_ETS_TAG, TEST_NODE_ID, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    static std::optional<int32_t> checkEvent;
    auto callbackSync = [](Ark_VMContext vmContext, const Ark_Int32 resourceId, const Ark_Int32 currentState) {
        checkEvent = Converter::Convert<int32_t>(currentState);
    };
    EXPECT_CALL(*themeManager_, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
    auto arkCallback = Converter::ArkValue<Callback_StateStylesChange>(nullptr, callbackSync, TEST_RES_ID);
    auto nodePtr = reinterpret_cast<Ark_NativePointer>(frameNode.GetRawPtr());
    ASSERT_NE(nodePtr, nullptr);
    Ark_Int32 allState = Converter::ArkValue<Ark_Int32>(UI_STATE_FOCUSED | UI_STATE_PRESSED);
    accessor_->onStateStyleChange(nodePtr, &arkCallback, allState);

    auto eventHub = frameNode->GetEventHub<NG::EventHub>();
    ASSERT_NE(eventHub, nullptr);

    checkEvent.reset();
    eventHub->UpdateCurrentUIState(UI_STATE_FOCUSED);
    EXPECT_EQ(checkEvent, TEST_STATE_FOCUSED);

    checkEvent.reset();
    eventHub->UpdateCurrentUIState(UI_STATE_PRESSED);
    EXPECT_EQ(checkEvent, TEST_STATE_PRESSED);
}
} // namespace OHOS::Ace::NG
