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
#include "core/interfaces/native/implementation/menu_item_configuration_peer.h"
#include "core/components_ng/pattern/menu/menu_model_static.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class MenuItemContentModifierHelperAccessor : public StaticAccessorTest<GENERATED_ArkUIContentModifierHelperAccessor,
                                &GENERATED_ArkUIAccessors::getContentModifierHelperAccessor> {
public:
    void SetUp(void) override
    {
        SetupTheme<SelectTheme>();
    }
    void FireBuilder(SelectPattern* pattern)
    {
        auto menuNode = pattern->GetMenuNode();
        ASSERT_NE(menuNode, nullptr);
        auto menuPattern = menuNode->GetPattern<MenuPattern>();
        ASSERT_NE(menuPattern, nullptr);
        menuPattern->FireBuilder();
    }
};

static constexpr int TEST_NODE_ID = 333;
static constexpr int TEST_OBJ_ID = 1001;
static constexpr int TEST_BUILDER_ID = 1002;
static constexpr bool TEST_DEFAULT_SELECTED = false;
static constexpr int TEST_DEFAULT_INDEX = 0;

/**
 * @tc.name: menuItemContentModifierHelperAccessorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemContentModifierHelperAccessor, menuItemContentModifierHelperAccessorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->contentModifierMenuItem, nullptr);
    /**
     * @tc.steps: step1. create menu node.
     */
    const auto menuNode = MenuModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(menuNode, nullptr);
    RefPtr<FrameNode> menuItemNode = SelectModelNG::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(menuItemNode, nullptr);
    RefPtr<FrameNode> wrapperNode = MenuModelStatic::CreateFrameNode(TEST_NODE_ID);
    ASSERT_NE(wrapperNode, nullptr);
    wrapperNode->AddChild(menuNode);
    auto pattern = menuItemNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetMenuNode(wrapperNode);

    SelectParam param = {.text = "XXX", .icon = "YYY"};
    std::vector<SelectParam> params = {param};
    auto mn = pattern->GetMenuNode();
    ASSERT_NE(mn, nullptr);
    auto menuPattern = mn->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->SetSelectProperties(params);

    struct CheckEvent {
        int32_t nodeId;
        int32_t objId;
        bool selected;
        int index;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto obj = Converter::ArkCreate<Ark_Object>(TEST_OBJ_ID);
    /**
     * @tc.steps: step2. create modifierCallback.
     */
    auto modifierCallback = [](const Ark_Int32 resourceId, const Ark_NativePointer parentNode,
        const Ark_MenuItemConfiguration config, const Callback_Pointer_Void continuation) {
            auto navigationNode = reinterpret_cast<FrameNode *>(parentNode);
            checkEvent = {
                .nodeId = navigationNode->GetId(),
                .objId = config->contentModifier_.resource.resourceId,
                .selected = config->selected_,
                .index = config->index_
            };
    };

    EXPECT_CALL(*MockContainer::Current(), GetFrontend()).WillRepeatedly(Return(nullptr));

    auto builder = Converter::ArkValue<MenuItemModifierBuilder>(modifierCallback, TEST_BUILDER_ID);
    Ark_NativePointer nodePtr = reinterpret_cast<Ark_NativePointer>(menuItemNode.GetRawPtr());
    /**
     * @tc.steps: step3. call FireBuilder.
     */
    accessor_->contentModifierMenuItem(nodePtr, &obj, &builder);
    FireBuilder(pattern.GetRawPtr());

    EXPECT_EQ(checkEvent->nodeId, TEST_NODE_ID);
    EXPECT_EQ(checkEvent->objId, TEST_OBJ_ID);
    EXPECT_EQ(checkEvent->selected, TEST_DEFAULT_SELECTED);
    EXPECT_EQ(checkEvent->index, TEST_DEFAULT_INDEX);
}
}