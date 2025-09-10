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
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_static.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
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
    RefPtr<SelectTheme> selectTheme_;
};
 
void MenuItemModelStaticTestNg::SetUpTestCase() {}
 
void MenuItemModelStaticTestNg::TearDownTestCase() {}
 
void MenuItemModelStaticTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme_));
    MockContainer::SetUp();
}
 
void MenuItemModelStaticTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    MockContainer::TearDown();
    selectTheme_ = nullptr;
}

 /**
 * @tc.name: AddChild001
 * @tc.desc: Test AddChild001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, AddChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. create content node.
     * @tc.expected: step2. All pointers non-null.
     */
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(content, nullptr);

    /**
     * @tc.steps: step3. call AddChild Function.
     */
    MenuItemModelStatic::AddChild(node, content);
    /**
     * @tc.steps: step4. do assert.
     * @tc.expected: step4. node->GetChildren().empty() is false.
     */
    ASSERT_FALSE(node->GetChildren().empty());
}


 /**
 * @tc.name: AddChild002
 * @tc.desc: Test AddChild002
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, AddChild002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. Init textNode node and mountToParent.
     * @tc.expected: step2. All pointers non-null.
     */
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textNode, nullptr);
    textNode->MountToParent(frameNode);

    /**
     * @tc.steps: step3. create content node.
     * @tc.expected: step3. All pointers non-null.
     */
    auto content = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(content, nullptr);
    /**
     * @tc.steps: step4. call AddChild Function.
     */
    MenuItemModelStatic::AddChild(node, content);
    /**
     * @tc.steps: step5. do assert.
     * @tc.expected: step5. node->GetChildren().empty() is false.
     */
    ASSERT_FALSE(node->GetChildren().empty());
}

 /**
 * @tc.name: DoMountRow001
 * @tc.desc: Test DoMountRow001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, DoMountRow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. call DoMountRow Function.
     */
    MenuItemModelStatic::DoMountRow(frameNode);
    /**
     * @tc.steps: step3. do assert.
     * @tc.expected: step3. frameNode has two child.
     */
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
}

 /**
 * @tc.name: UpdateRadius001
 * @tc.desc: Test UpdateRadius001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, UpdateRadius001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. mock selectTheme_ innerBorderRadius, menuDefaultInnerRadius_
     */
    selectTheme_->innerBorderRadius_ = Dimension(10, DimensionUnit::PX);
    selectTheme_->menuDefaultInnerRadius_ = Dimension(20, DimensionUnit::PX);

    /**
     * @tc.steps: step3. set api target verson<12 and call UpdateRadius Function.
     */
    MockContainer::Current()->SetApiTargetVersion(11);
    MenuItemModelStatic::UpdateRadius(frameNode);
    /**
     * @tc.steps: step4. do assert
     * @tc.expected: step4. renderContext->GetBorderRadius() eq selectTheme_->innerBorderRadius_.
     */
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(selectTheme_->innerBorderRadius_);
    EXPECT_EQ(renderContext->GetBorderRadius(), borderRadius);

    /**
     * @tc.steps: step5. set api target verson>12 and call UpdateRadius Function.
     */
    MockContainer::Current()->SetApiTargetVersion(13);
    MenuItemModelStatic::UpdateRadius(frameNode);
    /**
     * @tc.steps: step6. do assert
     * @tc.expected: step6. renderContext->GetBorderRadius() eq selectTheme_->menuDefaultInnerRadius_.
     */
    borderRadius.SetRadius(selectTheme_->menuDefaultInnerRadius_);
    EXPECT_EQ(renderContext->GetBorderRadius(), borderRadius);
}

 /**
 * @tc.name: AddRowChild001
 * @tc.desc: Test AddRowChild001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, AddRowChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. call AddRowChild when node has no child
     */
    MenuItemProperties itemOption;
    itemOption.content = "test content";
    MenuItemModelStatic::AddRowChild(node, itemOption);
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. frameNode has two child
     */
    EXPECT_EQ(frameNode->GetChildren().size(), 2);

    /**
     * @tc.steps: step4. set MenuItem builder property
     */
    auto builder = []() -> RefPtr<UINode> {
        return FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3,
            AceType::MakeRefPtr<MenuPattern>(2, "", MenuType::MENU));
    };
    itemOption.buildFunc = builder;
    /**
     * @tc.steps: step5. call AddRowChild when node has two child
     */
    MenuItemModelStatic::AddRowChild(node, itemOption);
    /**
     * @tc.steps: step6. do assert
     * @tc.expected: step6. frameNode has two child
     */
    EXPECT_EQ(frameNode->GetChildren().size(), 2);
}

 /**
 * @tc.name: UpdateMenuProperty001
 * @tc.desc: Test UpdateMenuProperty001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, UpdateMenuProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    /**
     * @tc.steps: step2. set MenuItemProperty content and call UpdateMenuProperty
     */
    MenuItemProperties itemOption;
    itemOption.content = "test content";
    MenuItemModelStatic::UpdateMenuProperty(node, itemOption);
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. menuProperty content = itemOption.content
     */
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
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    /**
     * @tc.steps: step2. set SetSelectedChangeEvent to MenuItem
     */
    auto func = [](bool param) {
        return true;
    };
    MenuItemModelStatic::SetSelectedChangeEvent(node, func);

    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem event hub GetSelectedChangeEvent not null
     */
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_NE(eventHub->GetSelectedChangeEvent(), nullptr);
}

 /**
 * @tc.name: SetSelected001
 * @tc.desc: Test SetSelected001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelected001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set SetSelected nullopt to MenuItem
     */
    MenuItemModelStatic::SetSelected(node, std::nullopt);
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem isSelected_ false
     */
    ASSERT_FALSE(pattern->isSelected_);
    /**
     * @tc.steps: step4. set SetSelected true to MenuItem
     */
    MenuItemModelStatic::SetSelected(node, std::optional<bool>(true));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem isSelected_ true
     */
    ASSERT_TRUE(pattern->isSelected_);
}

 /**
 * @tc.name: SetLabelFontColor001
 * @tc.desc: Test SetLabelFontColor001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetLabelFontColor(node, std::nullopt);
    /**
     * @tc.steps: step2. set Color black to MenuItem LabelFont
     */
    MenuItemModelStatic::SetLabelFontColor(node, std::optional<Color>(Color::BLACK));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont color is black
     */
    EXPECT_EQ(menuProperty->GetLabelFontColor(), Color::BLACK);
}

 /**
 * @tc.name: SetFontColor001
 * @tc.desc: Test SetFontColor001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetFontColor(node, std::nullopt);
    /**
     * @tc.steps: step2. set Color black to MenuItem Font
     */
    MenuItemModelStatic::SetFontColor(node, std::optional<Color>(Color::BLACK));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem Font color is black
     */
    EXPECT_EQ(menuProperty->GetFontColor(), Color::BLACK);
}

 /**
 * @tc.name: SetLabelFontSize001
 * @tc.desc: Test SetLabelFontSize001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    CalcDimension fontSize;
    MenuItemModelStatic::SetLabelFontSize(node, std::nullopt);
    MenuItemModelStatic::SetLabelFontSize(node, std::optional<Dimension>(fontSize));
    /**
     * @tc.steps: step2. set MenuItem labelFont size 16fp
     */
    MenuItemModelStatic::SetLabelFontSize(node, std::optional<Dimension>(16.0_fp));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont size is 16fp
     */
    EXPECT_EQ(menuProperty->GetLabelFontSize(), 16.0_fp);
}

 /**
 * @tc.name: SetLabelFontWeight001
 * @tc.desc: Test SetLabelFontWeight001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontWeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetLabelFontWeight(node, std::nullopt);
    /**
     * @tc.steps: step2. set MenuItem labelFont weight W500
     */
    MenuItemModelStatic::SetLabelFontWeight(node, std::optional<FontWeight>(FontWeight::W500));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont weight is W500
     */
    EXPECT_EQ(menuProperty->GetLabelFontWeight(), FontWeight::W500);
}

 /**
 * @tc.name: SetLabelFontFamily001
 * @tc.desc: Test SetLabelFontFamily001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontFamily001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    std::vector<std::string> fontFamilies;
    MenuItemModelStatic::SetLabelFontFamily(node, std::nullopt);
    /**
    * @tc.steps: step2. set MenuItem labelFont family fontFamilies
    */
    MenuItemModelStatic::SetLabelFontFamily(node, std::optional<std::vector<std::string>>(fontFamilies));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont family is fontFamilies
     */
    EXPECT_EQ(menuProperty->GetLabelFontFamily(), fontFamilies);
}

 /**
 * @tc.name: SetLabelFontStyle001
 * @tc.desc: Test SetLabelFontStyle001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetLabelFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetLabelFontStyle(node, std::nullopt);
    /**
    * @tc.steps: step2. set MenuItem labelFont style ITALIC
    */
    MenuItemModelStatic::SetLabelFontStyle(node, std::optional<Ace::FontStyle>(Ace::FontStyle::ITALIC));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont style is ITALIC
     */
    EXPECT_EQ(menuProperty->GetLabelItalicFontStyle(), Ace::FontStyle::ITALIC);
}

 /**
 * @tc.name: SetFontSize001
 * @tc.desc: Test SetFontSize001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    CalcDimension fontSize;
    MenuItemModelStatic::SetFontSize(node, std::nullopt);
    MenuItemModelStatic::SetFontSize(node, std::optional<Dimension>(fontSize));
    /**
    * @tc.steps: step2. set MenuItem font size 16fp
    */
    MenuItemModelStatic::SetFontSize(node, std::optional<Dimension>(16.0_fp));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont style is ITALIC
     */
    EXPECT_EQ(menuProperty->GetFontSize(), 16.0_fp);
}

 /**
 * @tc.name: SetFontWeight001
 * @tc.desc: Test SetFontWeight001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontWeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetFontWeight(node, std::nullopt);
    /**
    * @tc.steps: step2. set MenuItem font weight W500
    */
    MenuItemModelStatic::SetFontWeight(node, std::optional<FontWeight>(FontWeight::W500));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem labelFont style is ITALIC
     */
    EXPECT_EQ(menuProperty->GetFontWeight(), FontWeight::W500);
}

 /**
 * @tc.name: SetFontFamily001
 * @tc.desc: Test SetFontFamily001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontFamily001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    std::vector<std::string> fontFamilies;
    MenuItemModelStatic::SetFontFamily(node, std::nullopt);
    /**
    * @tc.steps: step2. set MenuItem font family fontFamilies
    */
    MenuItemModelStatic::SetFontFamily(node, std::optional<std::vector<std::string>>(fontFamilies));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem font family is fontFamilies
     */
    EXPECT_EQ(menuProperty->GetFontFamily(), fontFamilies);
}

 /**
 * @tc.name: SetFontStyle001
 * @tc.desc: Test SetFontStyle001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetFontStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetFontStyle(node, std::nullopt);
    /**
    * @tc.steps: step2. set MenuItem font style ITALIC
    */
    MenuItemModelStatic::SetFontStyle(node, std::optional<Ace::FontStyle>(Ace::FontStyle::ITALIC));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem font style is ITALIC
     */
    EXPECT_EQ(menuProperty->GetItalicFontStyle(), Ace::FontStyle::ITALIC);
}

 /**
 * @tc.name: SetSelectIcon001
 * @tc.desc: Test SetSelectIcon001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectIcon001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);
    /**
    * @tc.steps: step2. set MenuItem selectIcon true
    */
    MenuItemModelStatic::SetSelectIcon(node, true);
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem selectIcon is true
     */
    EXPECT_TRUE(menuProperty->GetSelectIcon());
}

 /**
 * @tc.name: SetSelectIconSrc001
 * @tc.desc: Test SetSelectIconSrc001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectIconSrc001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    MenuItemModelStatic::SetSelectIconSrc(node, std::nullopt);
    /**
    * @tc.steps: step2. set MenuItem selectIconSrc string "test"
    */
    MenuItemModelStatic::SetSelectIconSrc(node, std::optional<std::string>("test"));
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem selectIconSrc is string "test"
     */
    EXPECT_EQ(menuProperty->GetSelectIconSrc(), "test");
}

 /**
 * @tc.name: SetSelectIconSymbol001
 * @tc.desc: Test SetSelectIconSymbol001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetSelectIconSymbol001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
    ASSERT_NE(menuProperty, nullptr);

    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    MenuItemModelStatic::SetSelectIconSymbol(node, std::move(symbolApply));
    /**
    * @tc.steps: step2. set MenuItem selectIconSymbol
    */
    MenuItemModelStatic::SetSelectIconSymbol(node, [](WeakPtr<NG::FrameNode> weakPtr = nullptr) {});
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem selectSymbol not null
     */
    ASSERT_NE(menuProperty->GetSelectSymbol(), nullptr);
}

 /**
 * @tc.name: SetOnChange001
 * @tc.desc: Test SetOnChange001
 * @tc.type: FUNC
 */
HWTEST_F(MenuItemModelStaticTestNg, SetOnChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init MenuItem node.
     * @tc.expected: step1. All pointers non-null.
     */
    auto frameNode = MenuItemModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
    * @tc.steps: step2. set MenuItem onChange event
    */
    MenuItemModelStatic::SetOnChange(node, [](bool param) {

    });
    /**
     * @tc.steps: step3. do assert
     * @tc.expected: step3. Menuitem onChange event not null
     */
    ASSERT_NE(eventHub->GetOnChange(), nullptr);
}
} // namespace OHOS::Ace::NG