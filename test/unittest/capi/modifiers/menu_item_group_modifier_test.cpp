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
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "test/mock/core/common/mock_theme_style.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

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
};

/*
 * @tc.name: setMenuItemGroupOptionsStringTest
 * @tc.desc: Check the functionality of MenuItemModifier.setMenuItemGroupOptions
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemGroupModifierTest, DISABLED_setMenuItemGroupOptionsStringTest, TestSize.Level1)
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
HWTEST_F(MenuItemGroupModifierTest, DISABLED_setMenuItemGroupOptionsResourceTest, TestSize.Level1)
{
    auto headerValue = GetAttrValue<std::string>(node_, "header");
    auto footerValue = GetAttrValue<std::string>(node_, "footer");
    EXPECT_EQ(headerValue, "");
    EXPECT_EQ(footerValue, "");

    const auto RES_NAME_HEADER = NamedResourceId{"header", NodeModifier::ResourceType::STRING};
    Ark_ResourceStr headerResStr = CreateResourceUnion<Ark_ResourceStr>(RES_NAME_HEADER);
    auto header = Converter::ArkUnion<Opt_Union_ResourceStr_CustomBuilder, Ark_ResourceStr>(headerResStr);

    const auto RES_NAME_FOOTER = NamedResourceId{"footer", NodeModifier::ResourceType::STRING};
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
} // namespace OHOS::Ace::NG
