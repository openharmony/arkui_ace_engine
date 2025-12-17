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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/core/common/mock_theme_style.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static constexpr int TEST_RESOURCE_ID = 1000;
static constexpr int32_t NODE_ID = 555;
struct CheckEvent {
    int32_t resourceId;
    Ark_NativePointer parentNode;
};
static std::optional<RefPtr<UINode>> uiNode = std::nullopt;
static std::optional<CheckEvent> checkEventH = std::nullopt;
static std::optional<CheckEvent> checkEventF = std::nullopt;

class MenuItemGroupModifierTest : public ModifierTestBase<GENERATED_ArkUIMenuItemGroupModifier,
    &GENERATED_ArkUINodeModifiers::getMenuItemGroupModifier, GENERATED_ARKUI_MENU_ITEM_GROUP> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<SelectTheme>();
        AddResource("header", "Header");
        AddResource("footer", "Footer");
    }

    CustomNodeBuilder getBuilderCb(bool headerCb = true)
    {
        static std::optional<bool> isHeader;
        static std::optional<bool> isFooter;
        if (headerCb) {
            isHeader = true;
        } else {
            isFooter = true;
        }
        auto checkCallback = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            if (isHeader) {
                checkEventH = {.resourceId = resourceId, .parentNode = parentNode};
            }
            if (isFooter) {
                checkEventF = {.resourceId = resourceId, .parentNode = parentNode};
            }
            if (uiNode) {
                CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
            }
        };
        CustomNodeBuilder customBuilder =
            Converter::ArkValue<CustomNodeBuilder>(checkCallback, TEST_RESOURCE_ID);
        return customBuilder;
    }
};

/*
 * @tc.name: setMenuItemGroupOptionsStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemGroupOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupModifierTest, setMenuItemGroupOptionsStringTest, TestSize.Level1)
{
    auto headerValue = GetAttrValue<std::string>(node_, "header");
    auto footerValue = GetAttrValue<std::string>(node_, "footer");
    EXPECT_EQ(headerValue, "");
    EXPECT_EQ(footerValue, "");

    auto headerStr = Converter::ArkValue<Ark_String>("Header");
    auto headerResStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(headerStr);
    auto header = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, Ark_ResourceStr>(headerResStr);
    auto footerStr = Converter::ArkValue<Ark_String>("Footer");
    auto footerResStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(footerStr);
    auto footer = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, Ark_ResourceStr>(footerResStr);
    Ark_MenuItemGroupOptions options = {.header = header, .footer = footer};
    auto optionsOpt = Converter::ArkValue<Opt_MenuItemGroupOptions>(options);
    modifier_->setMenuItemGroupOptions(node_, &optionsOpt);
    headerValue = GetAttrValue<std::string>(node_, "header");
    footerValue = GetAttrValue<std::string>(node_, "footer");
    EXPECT_EQ(headerValue, "Header");
    EXPECT_EQ(footerValue, "Footer");
}

/*
 * @tc.name: setMenuItemGroupOptionsResourceTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemGroupOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupModifierTest, setMenuItemGroupOptionsResourceTest, TestSize.Level1)
{
    auto headerValue = GetAttrValue<std::string>(node_, "header");
    auto footerValue = GetAttrValue<std::string>(node_, "footer");
    EXPECT_EQ(headerValue, "");
    EXPECT_EQ(footerValue, "");

    const auto RES_NAME_HEADER = NamedResourceId{"header", ResourceType::STRING};
    Ark_ResourceStr headerResStr = CreateResourceUnion<Ark_ResourceStr>(RES_NAME_HEADER);
    auto header = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, Ark_ResourceStr>(headerResStr);

    const auto RES_NAME_FOOTER = NamedResourceId{"footer", ResourceType::STRING};
    Ark_ResourceStr footerResStr = CreateResourceUnion<Ark_ResourceStr>(RES_NAME_FOOTER);
    auto footer = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, Ark_ResourceStr>(footerResStr);

    Ark_MenuItemGroupOptions options = {.header = header, .footer = footer};
    auto optionsOpt = Converter::ArkValue<Opt_MenuItemGroupOptions>(options);
    modifier_->setMenuItemGroupOptions(node_, &optionsOpt);
    headerValue = GetAttrValue<std::string>(node_, "header");
    footerValue = GetAttrValue<std::string>(node_, "footer");
    EXPECT_EQ(headerValue, "Header");
    EXPECT_EQ(footerValue, "Footer");
}

/*
 * @tc.name: setMenuItemGroupOptionsCustomBuilderTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemGroupOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupModifierTest, setMenuItemGroupOptionsCustomBuilderTest, TestSize.Level1)
{
    uiNode = BlankModelNG::CreateFrameNode(NODE_ID);
    auto builder = getBuilderCb();
    auto header = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, CustomNodeBuilder>(builder);

    auto builder2 = getBuilderCb(false);
    auto footer = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, CustomNodeBuilder>(builder2);
    Ark_MenuItemGroupOptions options = {.header = header, .footer = footer};
    auto optionsOpt = Converter::ArkValue<Opt_MenuItemGroupOptions>(options);
    checkEventH = std::nullopt;
    checkEventF = std::nullopt;
    modifier_->setMenuItemGroupOptions(node_, &optionsOpt);
    ASSERT_EQ(checkEventH.has_value(), true);
    EXPECT_EQ(checkEventH->resourceId, TEST_RESOURCE_ID);
    ASSERT_EQ(checkEventF.has_value(), true);
    EXPECT_EQ(checkEventF->resourceId, TEST_RESOURCE_ID);
    uiNode = std::nullopt;
    checkEventH = std::nullopt;
    checkEventF = std::nullopt;
}
} // namespace OHOS::Ace::NG
