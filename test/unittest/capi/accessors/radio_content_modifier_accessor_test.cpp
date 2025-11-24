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
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RadioContentModifierHelperAccessor : public StaticAccessorTest<GENERATED_ArkUIContentModifierHelperAccessor,
                                &GENERATED_ArkUIAccessors::getContentModifierHelperAccessor> {
public:
    void FireBuilder(RadioPattern* pattern)
    {
        pattern->FireBuilder();
    }
};

static constexpr int TEST_NODE_ID = 333;
static constexpr int TEST_OBJ_ID = 1001;
static constexpr int TEST_BUILDER_ID = 1002;
static constexpr bool TEST_DEFAULT_ENABLED = true;
static const std::string TEST_DEFAULT_VALUE = "";
static constexpr bool TEST_DEFAULT_CHECKED = false;

/**
 * @tc.name: RadioContentModifierHelperAccessorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RadioContentModifierHelperAccessor, radioContentModifierHelperAccessorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->contentModifierRadio, nullptr);

    RefPtr<FrameNode> radioNode = FrameNode::GetOrCreateFrameNode(
            V2::DATA_PANEL_ETS_TAG, TEST_NODE_ID, []() { return AceType::MakeRefPtr<RadioPattern>(); });
    ASSERT_NE(radioNode, nullptr);
    auto pattern = radioNode->GetPattern<RadioPattern>();
    ASSERT_NE(pattern, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t resourceId;
        int32_t objId;
        std::optional<bool> enabled;
        std::optional<std::string> value;
        std::optional<bool> checked;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto obj = Converter::ArkCreate<Ark_Object>(TEST_OBJ_ID);

    auto modifierCallback = [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
        const Ark_RadioConfiguration config, const Callback_Pointer_Void continuation) {
            auto navigationNode = reinterpret_cast<FrameNode *>(parentNode);
            checkEvent = {
                .nodeId = navigationNode->GetId(),
                .resourceId = resourceId,
                .objId = config.contentModifier.resource.resourceId,
                .enabled = Converter::OptConvert<bool>(config.enabled),
                .value = Converter::OptConvert<std::string>(config.value),
                .checked = Converter::OptConvert<bool>(config.checked),
            };
    };

    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(nullptr));

    auto builder = Converter::ArkValue<RadioModifierBuilder>(modifierCallback, TEST_BUILDER_ID);
    Ark_NativePointer nodePtr = reinterpret_cast<Ark_NativePointer>(radioNode.GetRawPtr());
    accessor_->contentModifierRadio(nodePtr, &obj, &builder);

    FireBuilder(pattern.GetRawPtr());
    EXPECT_EQ(checkEvent->nodeId, TEST_NODE_ID);
    EXPECT_EQ(checkEvent->resourceId, TEST_BUILDER_ID);
    EXPECT_EQ(checkEvent->objId, TEST_OBJ_ID);
    ASSERT_TRUE(checkEvent->enabled.has_value()) << "enabled is not set";
    EXPECT_EQ(checkEvent->enabled.value(), TEST_DEFAULT_ENABLED);
    ASSERT_TRUE(checkEvent->value.has_value());
    EXPECT_EQ(checkEvent->value.value(), TEST_DEFAULT_VALUE);
    ASSERT_TRUE(checkEvent->checked.has_value()) << "checked is not set";
    EXPECT_EQ(checkEvent->checked.value(), TEST_DEFAULT_CHECKED);

    radioNode = nullptr;
}

}