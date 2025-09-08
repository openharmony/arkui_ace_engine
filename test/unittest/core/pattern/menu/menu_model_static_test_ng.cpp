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
#include "core/components_ng/pattern/menu/menu_model_static.h"
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
const V2::ItemDivider ITEM_DIVIDER = { Dimension(5.f), Dimension(10), Dimension(20), Color(0x000000) };
} // namespace
class MenuModelStaticTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};
 
void MenuModelStaticTestNg::SetUpTestCase() {}
 
void MenuModelStaticTestNg::TearDownTestCase() {}
 
void MenuModelStaticTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}
 
void MenuModelStaticTestNg::TearDown()
{
    MockPipelineContext::TearDown();
    SystemProperties::SetDeviceType(DeviceType::PHONE);
    ScreenSystemManager::GetInstance().dipScale_ = 1.0;
    SystemProperties::orientation_ = DeviceOrientation::PORTRAIT;
    MockContainer::TearDown();
}

 /**
 * @tc.name: SetExpandingMode001
 * @tc.desc: Test SetExpandingMode001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetExpandingMode001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetExpandingMode(node, std::nullopt);
    MenuModelStatic::SetExpandingMode(node, std::optional<SubMenuExpandingMode>(SubMenuExpandingMode::SIDE));
}

 /**
 * @tc.name: SetItemDivider001
 * @tc.desc: Test SetItemDivider001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetItemDivider001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetItemDivider(node, std::nullopt, std::nullopt);
    MenuModelStatic::SetItemDivider(node, std::optional<V2::ItemDivider>(ITEM_DIVIDER),
        std::optional<DividerMode>(DividerMode::FLOATING_ABOVE_MENU));
}

 /**
 * @tc.name: SetItemGroupDivider001
 * @tc.desc: Test SetItemGroupDivider001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetItemGroupDivider001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetItemGroupDivider(node, std::nullopt, std::nullopt);
    MenuModelStatic::SetItemGroupDivider(node, std::optional<V2::ItemDivider>(ITEM_DIVIDER),
        std::optional<DividerMode>(DividerMode::FLOATING_ABOVE_MENU));
}

 /**
 * @tc.name: SetFontColor001
 * @tc.desc: Test SetFontColor001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetFontColor001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetFontColor(node, std::nullopt);
    MenuModelStatic::SetFontColor(node, std::optional<Color>(Color::BLACK));
}

 /**
 * @tc.name: SetFontSize001
 * @tc.desc: Test SetFontSize001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetFontSize001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetFontSize(node, std::nullopt);
    MenuModelStatic::SetFontSize(node, std::optional<Dimension>(16.0_fp));
}

 /**
 * @tc.name: SetFontWeight001
 * @tc.desc: Test SetFontWeight001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetFontWeight001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetFontWeight(node, std::nullopt);
    MenuModelStatic::SetFontWeight(node, std::optional<FontWeight>(FontWeight::W500));
}

 /**
 * @tc.name: SetFontStyle001
 * @tc.desc: Test SetFontStyle001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetFontStyle001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetFontStyle(node, std::nullopt);
    MenuModelStatic::SetFontStyle(node, std::optional<Ace::FontStyle>(Ace::FontStyle::ITALIC));
}

 /**
 * @tc.name: SetFontFamily001
 * @tc.desc: Test SetFontFamily001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetFontFamily001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetFontFamily(node, std::nullopt);
    std::vector<std::string> fontFamilies;
    MenuModelStatic::SetFontFamily(node, std::optional<std::vector<std::string>>(fontFamilies));
}

 /**
 * @tc.name: SetBorderRadius001
 * @tc.desc: Test SetBorderRadius001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetBorderRadius001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetBorderRadius(node, std::nullopt);
    MenuModelStatic::SetBorderRadius(node, std::optional<Dimension>(16.0_fp));
}

 /**
 * @tc.name: SetBorderRadius002
 * @tc.desc: Test SetBorderRadius002
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetBorderRadius002, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetBorderRadius(node, std::nullopt, std::nullopt, std::nullopt, std::nullopt);
}

 /**
 * @tc.name: SetWidth001
 * @tc.desc: Test SetWidth001
 * @tc.type: FUNC
 */
HWTEST_F(MenuModelStaticTestNg, SetWidth001, TestSize.Level1)
{
    auto frameNode = MenuModelStatic::CreateFrameNode(1);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    MenuModelStatic::SetWidth(node, 16.0_fp);
}
}