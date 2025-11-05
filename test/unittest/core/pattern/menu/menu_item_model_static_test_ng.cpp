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
 
#include <type_traits>
 
#include "gtest/gtest.h"
 
#define private public
#define protected public
 
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"
 
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/select/select_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_static.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
 
using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;
 
namespace OHOS::Ace::NG {
namespace {
} // namespace
class MenuItemModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};
 
void MenuItemModelStaticTestNg::SetUpTestCase() {}
 
void MenuItemModelStaticTestNg::TearDownTestCase() {}
 
void MenuItemModelStaticTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}
 
void MenuItemModelStaticTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    MockContainer::TearDown();
}

 /**
 * @tc.name: AddChild001
 * @tc.desc: Test AddChild001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, AddChild001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(content, nullptr);
    MenuItemModelStatic::AddChild(node, content);
    ASSERT_FALSE(node->GetChildren().empty());
}

 /**
 * @tc.name: AddChild002
 * @tc.desc: Test AddChild002
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, AddChild002, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode);
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(content, nullptr);
    MenuItemModelStatic::AddChild(node, content);
    ASSERT_FALSE(node->GetChildren().empty());
}

 /**
 * @tc.name: DoMountRow001
 * @tc.desc: Test DoMountRow001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, DoMountRow001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    MenuItemModelStatic::DoMountRow(frameNode);
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
}

 /**
 * @tc.name: UpdateRadius001
 * @tc.desc: Test UpdateRadius001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, UpdateRadius001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    MockContainer::Current()->SetApiTargetVersion(11);
    MenuItemModelStatic::UpdateRadius(frameNode);
    MockContainer::Current()->SetApiTargetVersion(13);
    MenuItemModelStatic::UpdateRadius(frameNode);
}

 /**
 * @tc.name: AddRowChild001
 * @tc.desc: Test AddRowChild001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, AddRowChild001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "test content";
    MenuItemModelStatic::AddRowChild(node, itemOption);
    EXPECT_EQ(frameNode->GetChildren().size(), 2);

    auto builder = []() -> RefPtr<UINode> {
        return FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3,
            AceType::MakeRefPtr<MenuPattern>(2, "", MenuType::MENU));
    };
    itemOption.buildFunc = builder;
    MenuItemModelStatic::AddRowChild(node, itemOption);
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
}

 /**
 * @tc.name: UpdateMenuProperty001
 * @tc.desc: Test UpdateMenuProperty001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, UpdateMenuProperty001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemProperties itemOption;
    itemOption.content = "test content";
    MenuItemModelStatic::UpdateMenuProperty(node, itemOption);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    EXPECT_EQ(menuProperty->GetContent(), itemOption.content);
}

 /**
 * @tc.name: SetSelectedChangeEvent001
 * @tc.desc: Test SetSelectedChangeEvent001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectedChangeEvent001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto func = [](bool param) {
        return true;
    };
    MenuItemModelStatic::SetSelectedChangeEvent(node, func);
}

 /**
 * @tc.name: SetSelected001
 * @tc.desc: Test SetSelected001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelected001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetSelected(node, std::nullopt);
    MenuItemModelStatic::SetSelected(node, std::optional<bool>(true));
}

 /**
 * @tc.name: SetLabelFontColor001
 * @tc.desc: Test SetLabelFontColor001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontColor001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetLabelFontColor(node, std::nullopt);
    MenuItemModelStatic::SetLabelFontColor(node, std::optional<Color>(Color::BLACK));
}

 /**
 * @tc.name: SetFontColor001
 * @tc.desc: Test SetFontColor001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontColor001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetFontColor(node, std::nullopt);
    MenuItemModelStatic::SetFontColor(node, std::optional<Color>(Color::BLACK));
}

 /**
 * @tc.name: SetLabelFontSize001
 * @tc.desc: Test SetLabelFontSize001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontSize001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    CalcDimension fontSize;
    MenuItemModelStatic::SetLabelFontSize(node, std::nullopt);
    MenuItemModelStatic::SetLabelFontSize(node, std::optional<Dimension>(fontSize));
    MenuItemModelStatic::SetLabelFontSize(node, std::optional<Dimension>(16.0_fp));
}

 /**
 * @tc.name: SetLabelFontWeight001
 * @tc.desc: Test SetLabelFontWeight001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontWeight001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetLabelFontWeight(node, std::nullopt);
    MenuItemModelStatic::SetLabelFontWeight(node, std::optional<FontWeight>(FontWeight::W500));
}

 /**
 * @tc.name: SetLabelFontFamily001
 * @tc.desc: Test SetLabelFontFamily001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontFamily001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    std::vector<std::string> fontFamilies;
    MenuItemModelStatic::SetLabelFontFamily(node, std::nullopt);
    MenuItemModelStatic::SetLabelFontFamily(node, std::optional<std::vector<std::string>>(fontFamilies));
}

 /**
 * @tc.name: SetLabelFontStyle001
 * @tc.desc: Test SetLabelFontStyle001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontStyle001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetLabelFontStyle(node, std::nullopt);
    MenuItemModelStatic::SetLabelFontStyle(node, std::optional<Ace::FontStyle>(Ace::FontStyle::ITALIC));
}

 /**
 * @tc.name: SetFontSize001
 * @tc.desc: Test SetFontSize001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontSize001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    CalcDimension fontSize;
    MenuItemModelStatic::SetFontSize(node, std::nullopt);
    MenuItemModelStatic::SetFontSize(node, std::optional<Dimension>(fontSize));
    MenuItemModelStatic::SetFontSize(node, std::optional<Dimension>(16.0_fp));
}

 /**
 * @tc.name: SetFontWeight001
 * @tc.desc: Test SetFontWeight001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontWeight001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetFontWeight(node, std::nullopt);
    MenuItemModelStatic::SetFontWeight(node, std::optional<FontWeight>(FontWeight::W500));
}

 /**
 * @tc.name: SetFontFamily001
 * @tc.desc: Test SetFontFamily001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontFamily001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    std::vector<std::string> fontFamilies;
    MenuItemModelStatic::SetFontFamily(node, std::nullopt);
    MenuItemModelStatic::SetFontFamily(node, std::optional<std::vector<std::string>>(fontFamilies));
}

 /**
 * @tc.name: SetFontStyle001
 * @tc.desc: Test SetFontStyle001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontStyle001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetFontStyle(node, std::nullopt);
    MenuItemModelStatic::SetFontStyle(node, std::optional<Ace::FontStyle>(Ace::FontStyle::ITALIC));
}

 /**
 * @tc.name: SetSelectIcon001
 * @tc.desc: Test SetSelectIcon001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectIcon001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetSelectIcon(node, true);
}

 /**
 * @tc.name: SetSelectIconSrc001
 * @tc.desc: Test SetSelectIconSrc001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectIconSrc001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuItemModelStatic::SetSelectIconSrc(node, std::nullopt);
    MenuItemModelStatic::SetSelectIconSrc(node, std::optional<std::string>("test"));
}

 /**
 * @tc.name: SetSelectIconSymbol001
 * @tc.desc: Test SetSelectIconSymbol001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectIconSymbol001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    MenuItemModelStatic::SetSelectIconSymbol(node, symbolApply);
    symbolApply = [](WeakPtr<NG::FrameNode>) {};
    MenuItemModelStatic::SetSelectIconSymbol(node, symbolApply);

    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    ASSERT_NE(menuProperty->GetSelectSymbol(), nullptr);
}

 /**
 * @tc.name: SetOnChange001
 * @tc.desc: Test SetOnChange001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetOnChange001, TestSize.Level1)
{
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    MenuItemModelStatic::SetOnChange(node, [](bool param) {

    });
}

 /**
 * @tc.name: SetSymbolStartIcon001
 * @tc.desc: Test SetSymbolStartIcon001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSymbolStartIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. call MenuItemModelStatic::SetSymbolStartIcon.
     */
    std::function<void(OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>)> symbolApply =
        [](OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>) {};
    MenuItemModelStatic::SetSymbolStartIcon(node, symbolApply);

    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    ASSERT_NE(menuProperty->GetStartSymbol(), nullptr);
}

 /**
 * @tc.name: SetSymbolEndIcon001
 * @tc.desc: Test SetSymbolEndIcon001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSymbolEndIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create menuItem.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. call MenuItemModelStatic::SetSymbolEndIcon.
     */
    std::function<void(OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>)> symbolApply =
        [](OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>) {};
    MenuItemModelStatic::SetSymbolEndIcon(node, symbolApply);

    /**
     * @tc.steps: step3. do assert.
     */
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    ASSERT_NE(menuProperty->GetEndSymbol(), nullptr);
}

} // namespace OHOS::Ace::NG