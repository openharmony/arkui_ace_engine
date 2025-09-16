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

#include <gtest/gtest.h>

#include "accessor_test_base.h"
#include "core/components_ng/pattern/text_clock/text_clock_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class TextClockContentModifierHelperAccessor : public StaticAccessorTest<GENERATED_ArkUIContentModifierHelperAccessor,
                                &GENERATED_ArkUIAccessors::getContentModifierHelperAccessor> {
public:
    void FireBuilder(TextClockPattern* pattern)
    {
        pattern->FireBuilder();
    }
};

static constexpr int TEST_NODE_ID = 333;
static constexpr int TEST_OBJ_ID = 1001;
static constexpr int TEST_BUILDER_ID = 1002;
static constexpr bool TEST_DEFAULT_ENABLED = true;
static constexpr bool TEST_DEFAULT_STARTED = true;
static constexpr float TEST_DEFAULT_TIMEZONE_OFFSET = NAN;

/**
 * @tc.name: textClockContentModifierHelperAccessorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(TextClockContentModifierHelperAccessor, textClockContentModifierHelperAccessorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->contentModifierTextClock, nullptr);

    RefPtr<FrameNode> textClockNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXTCLOCK_ETS_TAG, TEST_NODE_ID, []() { return AceType::MakeRefPtr<TextClockPattern>(); });
    ASSERT_NE(textClockNode, nullptr);
    auto pattern = textClockNode->GetPattern<TextClockPattern>();
    ASSERT_NE(pattern, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t resourceId;
        int32_t objId;
        std::optional<bool> enabled;
        std::optional<bool> started;
        std::optional<float> timeZoneOffset;
        std::optional<int64_t> timeValue;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    Ark_Object obj = {
        .resource = Ark_CallbackResource {
            .resourceId = TEST_OBJ_ID,
            .hold = [](InteropInt32){},
            .release = [](InteropInt32){},
        }
    };

    auto modifierCallback = [](const Ark_Int32 resourceId,
        const Ark_NativePointer parentNode,
        const Ark_TextClockConfiguration config,
        const Callback_Pointer_Void continuation) {
            auto navigationNode = reinterpret_cast<FrameNode *>(parentNode);
            checkEvent = {
                .nodeId = navigationNode->GetId(),
                .resourceId = resourceId,
                .objId = config.contentModifier.resource.resourceId,
                .enabled = Converter::OptConvert<bool>(config.enabled),
                .started = Converter::OptConvert<bool>(config.started),
                .timeZoneOffset = Converter::OptConvert<float>(config.timeZoneOffset),
                .timeValue = Converter::OptConvert<int64_t>(config.timeValue),
            };
    };

    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(nullptr));

    auto builder = Converter::ArkValue<TextClockModifierBuilder>(modifierCallback, TEST_BUILDER_ID);
    Ark_NativePointer nodePtr = reinterpret_cast<Ark_NativePointer>(textClockNode.GetRawPtr());
    accessor_->contentModifierTextClock(nodePtr, &obj, &builder);

    FireBuilder(pattern.GetRawPtr());
    EXPECT_EQ(checkEvent->nodeId, TEST_NODE_ID);
    EXPECT_EQ(checkEvent->resourceId, TEST_BUILDER_ID);
    EXPECT_EQ(checkEvent->objId, TEST_OBJ_ID);
    ASSERT_TRUE(checkEvent->enabled.has_value()) << "enabled is not set";
    EXPECT_EQ(checkEvent->enabled.value(), TEST_DEFAULT_ENABLED);
    ASSERT_TRUE(checkEvent->started.has_value()) << "started is not set";
    EXPECT_EQ(checkEvent->started.value(), TEST_DEFAULT_STARTED);
    ASSERT_TRUE(checkEvent->timeZoneOffset.has_value()) << "timeZoneOffset is not set";
    EXPECT_EQ(std::to_string(checkEvent->timeZoneOffset.value()), std::to_string(TEST_DEFAULT_TIMEZONE_OFFSET));
    ASSERT_TRUE(checkEvent->timeValue.has_value()) << "timeValue is not set";
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() / 1000;
    auto diff = (time - checkEvent->timeValue.value());
    EXPECT_TRUE(diff >= 0 && diff <= 1);
    textClockNode = nullptr;
}

}