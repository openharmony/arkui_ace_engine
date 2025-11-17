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
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class CheckBoxContentModifierHelperAccessor : public StaticAccessorTest<GENERATED_ArkUIContentModifierHelperAccessor,
                                &GENERATED_ArkUIAccessors::getContentModifierHelperAccessor> {
public:
    void FireBuilder(CheckBoxPattern* pattern)
    {
        pattern->FireBuilder();
    }
};

static constexpr int TEST_NODE_ID = 333;
static constexpr int TEST_OBJ_ID = 1001;
static constexpr int TEST_BUILDER_ID = 1002;
static constexpr bool TEST_DEFAULT_ENABLED = true;
static const std::string TEST_DEFAULT_NAME = "";
static constexpr bool TEST_DEFAULT_SELECTED = false;

/**
 * @tc.name: checkBoxContentModifierHelperAccessorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckBoxContentModifierHelperAccessor, checkBoxContentModifierHelperAccessorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->contentModifierCheckBox, nullptr);

    RefPtr<FrameNode> checkBoxNode = FrameNode::GetOrCreateFrameNode(
            V2::CHECKBOX_ETS_TAG, TEST_NODE_ID, []() { return AceType::MakeRefPtr<CheckBoxPattern>(); });
    ASSERT_NE(checkBoxNode, nullptr);
    auto pattern = checkBoxNode->GetPattern<CheckBoxPattern>();
    ASSERT_NE(pattern, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        int32_t resourceId;
        int32_t objId;
        std::optional<bool> enabled;
        std::optional<std::string> name;
        std::optional<bool> selected;
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
        const Ark_CheckBoxConfiguration config,
        const Callback_Pointer_Void continuation) {
            auto navigationNode = reinterpret_cast<FrameNode *>(parentNode);
            checkEvent = {
                .nodeId = navigationNode->GetId(),
                .resourceId = resourceId,
                .objId = config.contentModifier.resource.resourceId,
                .enabled = Converter::OptConvert<bool>(config.enabled),
                .name = Converter::OptConvert<std::string>(config.name),
                .selected = Converter::OptConvert<bool>(config.selected),
            };
    };

    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(nullptr));

    auto builder = Converter::ArkValue<CheckBoxModifierBuilder>(modifierCallback, TEST_BUILDER_ID);
    Ark_NativePointer nodePtr = reinterpret_cast<Ark_NativePointer>(checkBoxNode.GetRawPtr());
    accessor_->contentModifierCheckBox(nodePtr, &obj, &builder);

    FireBuilder(pattern.GetRawPtr());
    EXPECT_EQ(checkEvent->nodeId, TEST_NODE_ID);
    EXPECT_EQ(checkEvent->resourceId, TEST_BUILDER_ID);
    EXPECT_EQ(checkEvent->objId, TEST_OBJ_ID);
    EXPECT_THAT(checkEvent->enabled, Optional(TEST_DEFAULT_ENABLED));
    EXPECT_EQ(checkEvent->name, TEST_DEFAULT_NAME);
    EXPECT_THAT(checkEvent->selected, Optional(TEST_DEFAULT_SELECTED));
}

}