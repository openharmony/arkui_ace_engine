/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "tabs_test_ng.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/dialog/dialog_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_side_bar_tab_list_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<Theme> GetTabListTheme(ThemeType type)
{
    if (type == TabTheme::TypeId()) {
        auto themeConstants = TestNG::CreateThemeConstants(THEME_PATTERN_TAB);
        return TabTheme::Builder().Build(themeConstants);
    }
    return AceType::MakeRefPtr<DialogTheme>();
}

// Build a minimal sidebar tab list node tree:
//   hostNode (TabsSideBarTabListPattern)
//     └── columnNode
//           └── tabItemNode
//                 └── rowNode
//                       ├── iconNode (Image)
//                       └── textNode (Text)
struct SideBarTabListTestTree {
    RefPtr<FrameNode> hostNode;
    RefPtr<FrameNode> columnNode;
    RefPtr<FrameNode> tabItemNode;
    RefPtr<FrameNode> rowNode;
    RefPtr<FrameNode> iconNode;
    RefPtr<FrameNode> textNode;
    RefPtr<TabsSideBarTabListPattern> pattern;

    void Build()
    {
        // Create host node with TabsSideBarTabListPattern
        pattern = AceType::MakeRefPtr<TabsSideBarTabListPattern>();
        hostNode = FrameNode::CreateFrameNode(
            "SideBarTabList", ElementRegister::GetInstance()->MakeUniqueId(), pattern);
        ASSERT_NE(hostNode, nullptr);

        // Create column node
        columnNode = FrameNode::CreateFrameNode(
            V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(columnNode, nullptr);
        columnNode->MountToParent(hostNode);

        // Create tab item node (pattern type doesn't matter —
        // OnFontScaleConfigurationUpdate only checks child tag == ROW_ETS_TAG)
        tabItemNode = FrameNode::CreateFrameNode(
            "TabsSideBarTabItem", ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        ASSERT_NE(tabItemNode, nullptr);
        tabItemNode->MountToParent(columnNode);

        // Create row node
        rowNode = FrameNode::CreateFrameNode(
            V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        ASSERT_NE(rowNode, nullptr);
        rowNode->MountToParent(tabItemNode);

        // Create icon node
        iconNode = FrameNode::CreateFrameNode(
            V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<ImagePattern>());
        ASSERT_NE(iconNode, nullptr);
        iconNode->MountToParent(rowNode);

        // Create text node
        textNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<TextPattern>());
        ASSERT_NE(textNode, nullptr);
        textNode->MountToParent(rowNode);

        // Set columnNode to pattern
        pattern->SetColumnNode(columnNode);
    }
};

// Helper: get the top margin CalcLength from a text node, or nullopt if absent
std::optional<CalcLength> GetTextNodeMarginTop(const RefPtr<FrameNode>& textNode)
{
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    if (!textLayoutProperty) {
        return std::nullopt;
    }
    const auto& margin = textLayoutProperty->GetMarginProperty();
    if (!margin) {
        return std::nullopt;
    }
    return margin->top;
}
} // namespace

class TabsSideBarTabListTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite()
    {
        TestNG::SetUpTestSuite();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            return GetTabListTheme(type);
        });
        EXPECT_CALL(*themeManager, GetTheme(_, _))
            .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
                return GetTabListTheme(type);
            });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
        g_isConfigChangePerform = false;
    }
};

/**
 * @tc.name: OnFontScaleConfigurationUpdate001
 * @tc.desc: Test OnFontScaleConfigurationUpdate with default font scale (1.0)
 *           verticalMargin should be paddingLevel4 (8vp)
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, OnFontScaleConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build sidebar tab list node tree
     */
    SideBarTabListTestTree tree;
    tree.Build();

    /**
     * @tc.steps: step2. Set font scale to 1.0 and call OnFontScaleConfigurationUpdate
     */
    auto pipeline = tree.hostNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 1.0f;

    tree.pattern->OnFontScaleConfigurationUpdate();

    /**
     * @tc.steps: step3. Verify text node margin top equals paddingLevel4 (8vp)
     */
    auto marginTop = GetTextNodeMarginTop(tree.textNode);
    ASSERT_TRUE(marginTop.has_value());
    EXPECT_EQ(marginTop.value(), CalcLength(Dimension(8.0_vp)));
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate002
 * @tc.desc: Test OnFontScaleConfigurationUpdate with font scale 1.75
 *           verticalMargin should be paddingLevel8 (16vp)
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, OnFontScaleConfigurationUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build sidebar tab list node tree
     */
    SideBarTabListTestTree tree;
    tree.Build();

    /**
     * @tc.steps: step2. Set font scale to 1.75 and call OnFontScaleConfigurationUpdate
     */
    auto pipeline = tree.hostNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 1.75f;

    tree.pattern->OnFontScaleConfigurationUpdate();

    /**
     * @tc.steps: step3. Verify text node margin top equals paddingLevel8 (16vp)
     */
    auto marginTop = GetTextNodeMarginTop(tree.textNode);
    ASSERT_TRUE(marginTop.has_value());
    EXPECT_EQ(marginTop.value(), CalcLength(Dimension(16.0_vp)));
}

/**
 * @tc.name: OnFontScaleConfigurationUpdate003
 * @tc.desc: Test OnFontScaleConfigurationUpdate with font scale 2.0
 *           verticalMargin should be paddingLevel10 (20vp)
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, OnFontScaleConfigurationUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build sidebar tab list node tree
     */
    SideBarTabListTestTree tree;
    tree.Build();

    /**
     * @tc.steps: step2. Set font scale to 2.0 and call OnFontScaleConfigurationUpdate
     */
    auto pipeline = tree.hostNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontScale_ = 2.0f;

    tree.pattern->OnFontScaleConfigurationUpdate();

    /**
     * @tc.steps: step3. Verify text node margin top equals paddingLevel10 (20vp)
     */
    auto marginTop = GetTextNodeMarginTop(tree.textNode);
    ASSERT_TRUE(marginTop.has_value());
    EXPECT_EQ(marginTop.value(), CalcLength(Dimension(20.0_vp)));
}

/**
 * @tc.name: SetCurrentIndex001
 * @tc.desc: Test SetCurrentIndex updates the current index
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, SetCurrentIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a TabsSideBarTabListPattern directly
     */
    auto pattern = AceType::MakeRefPtr<TabsSideBarTabListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init to index 0 then set to index 2
     * @tc.expected: GetCurrentIndex returns the new index
     */
    pattern->InitCurrentIndex(0);
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);

    pattern->SetCurrentIndex(2);
    EXPECT_EQ(pattern->GetCurrentIndex(), 2);
}

/**
 * @tc.name: SetCurrentIndexSameValue001
 * @tc.desc: Test SetCurrentIndex with same value exercises early return
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, SetCurrentIndexSameValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a TabsSideBarTabListPattern directly
     */
    auto pattern = AceType::MakeRefPtr<TabsSideBarTabListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init to index 1, then SetCurrentIndex to same value
     * @tc.expected: Index remains 1 (early return path)
     */
    pattern->InitCurrentIndex(1);
    EXPECT_EQ(pattern->GetCurrentIndex(), 1);

    pattern->SetCurrentIndex(1);
    EXPECT_EQ(pattern->GetCurrentIndex(), 1);
}

/**
 * @tc.name: InitCurrentIndexSameValue001
 * @tc.desc: Test InitCurrentIndex with same value exercises early return
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, InitCurrentIndexSameValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a TabsSideBarTabListPattern directly
     */
    auto pattern = AceType::MakeRefPtr<TabsSideBarTabListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init to index 0, then InitCurrentIndex again with 0
     * @tc.expected: Index remains 0 (early return path)
     */
    pattern->InitCurrentIndex(0);
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);

    pattern->InitCurrentIndex(0);
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: InitCurrentIndexSequential001
 * @tc.desc: Test InitCurrentIndex with sequential different values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSideBarTabListTestNg, InitCurrentIndexSequential001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a TabsSideBarTabListPattern directly
     */
    auto pattern = AceType::MakeRefPtr<TabsSideBarTabListPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Init to different indices sequentially
     * @tc.expected: Each time GetCurrentIndex returns the latest value
     */
    EXPECT_EQ(pattern->GetCurrentIndex(), -1); // default value

    pattern->InitCurrentIndex(0);
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);

    pattern->InitCurrentIndex(3);
    EXPECT_EQ(pattern->GetCurrentIndex(), 3);
}

} // namespace OHOS::Ace::NG
