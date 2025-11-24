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
#include "richeditor_modifier_test.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/web/richtext_model_ng.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "test/unittest/capi/stubs/mock_web_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static const auto TEST_VALUE = "<p>Test value</p>";
static constexpr int32_t TEST_RESOURCE_ID = 1000;

class RichTextModifierTest : public ModifierTestBase<GENERATED_ArkUIRichTextModifier,
    &GENERATED_ArkUINodeModifiers::getRichTextModifier, GENERATED_ARKUI_RICH_TEXT> {
};

/**
 * @tc.name: setRichTextOptionsTest
 * @tc.desc: Check the functionality of setRichTextOptions
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModifierTest, setRichTextOptionsTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(modifier_->setRichTextOptions, nullptr);
    Ark_String text = Converter::ArkValue<Ark_String>(TEST_VALUE);

    modifier_->setRichTextOptions(node_, &text);

    auto pattern = frameNode->GetPattern<WebPattern>();
    ASSERT_EQ(pattern->GetWebData().value(), TEST_VALUE);
}

static bool g_onStartCalled = false;

/**
 * @tc.name: setOnStartTest
 * @tc.desc: Check the functionality of setOnStart
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModifierTest, DISABLED_setOnStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(modifier_->setOnStart, nullptr);

    auto onCallback = [](const Ark_Int32 resourceId) {
        EXPECT_EQ(resourceId, TEST_RESOURCE_ID);
        g_onStartCalled = true;
    };

    auto func = Converter::ArkValue<Callback_Void>(onCallback, TEST_RESOURCE_ID);
    auto optFunc = Converter::ArkValue<Opt_Callback_Void>(func);
    modifier_->setOnStart(node_, &optFunc);

    auto eventHub = frameNode->GetEventHub<NG::WebEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto event = std::make_shared<BaseEventInfo>("info");
    eventHub->FireOnPageStartedEvent(event);
    ASSERT_TRUE(g_onStartCalled);
}

static bool g_onCompleteCalled = false;

/**
 * @tc.name: setOnCompleteTest
 * @tc.desc: Check the functionality of setOnComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichTextModifierTest, DISABLED_setOnCompleteTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(modifier_->setOnComplete, nullptr);

    auto onCallback = [](const Ark_Int32 resourceId) {
        EXPECT_EQ(resourceId, TEST_RESOURCE_ID);
        g_onCompleteCalled = true;
    };

    auto func = Converter::ArkValue<Callback_Void>(onCallback, TEST_RESOURCE_ID);
    auto optFunc = Converter::ArkValue<Opt_Callback_Void>(func);
    modifier_->setOnComplete(node_, &optFunc);

    auto eventHub = frameNode->GetEventHub<NG::WebEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto event = std::make_shared<BaseEventInfo>("info");
    eventHub->FireOnPageFinishedEvent(event);
    ASSERT_TRUE(g_onCompleteCalled);
}

} // namespace OHOS::Ace::NG
