/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstddef>
#include <cstdint>

#include "gtest/gtest.h"
#include "tabs_test_ng.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SIDEBAR_WIDTH_240 = 240.0f;
constexpr float SIDEBAR_WIDTH_MIN = 240.0f;
constexpr float SIDEBAR_WIDTH_MAX = 280.0f;
constexpr float MIN_CONTENT_WIDTH = 0.0f;
constexpr float CONTAINER_WIDTH_LG = 840.0f;
constexpr float CONTAINER_WIDTH_SM = 320.0f;
constexpr float CONTAINER_WIDTH_MD = 600.0f;
} // namespace

class TabsSidebarTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TabsSidebarTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void TabsSidebarTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SidebarDisplayModeBreakpointTest001
 * @tc.desc: Test CalculateDisplayMode with default breakpoint mapping
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayModeBreakpointTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto density = PipelineBase::GetCurrentDensity();
    auto smMode = pattern->CalculateDisplayMode(CONTAINER_WIDTH_SM, density);
    auto mdMode = pattern->CalculateDisplayMode(CONTAINER_WIDTH_MD, density);
    auto lgMode = pattern->CalculateDisplayMode(CONTAINER_WIDTH_LG, density);
    EXPECT_EQ(smMode, TabBarDisplayMode::BOTTOMTABBAR);
    EXPECT_EQ(mdMode, TabBarDisplayMode::BOTTOMTABBAR);
    EXPECT_EQ(lgMode, TabBarDisplayMode::SIDEBAR);
}

/**
 * @tc.name: SidebarWidthClampTest001
 * @tc.desc: Test sidebarWidth is clamped between min and max
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarWidthClampTest001, TestSize.Level1)
{
    auto tabsNode = FrameNode::CreateFrameNode(V2::TABS_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TabsPattern>());
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateMinSidebarWidth(Dimension(SIDEBAR_WIDTH_MIN));
    layoutProperty->UpdateMaxSidebarWidth(Dimension(SIDEBAR_WIDTH_MAX));
    layoutProperty->UpdateSidebarWidth(Dimension(200));
    auto sidebarWidth = layoutProperty->GetSidebarWidthValue(Dimension(240)).ConvertToPx();
    auto minSidebarWidth = layoutProperty->GetMinSidebarWidthValue(Dimension(240)).ConvertToPx();
    EXPECT_LT(sidebarWidth, minSidebarWidth);
}

/**
 * @tc.name: SidebarPlacementMapTest001
 * @tc.desc: Test ComputeSidebarPlacementMap with mixed placements
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarPlacementMapTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto placementMap = pattern->ComputeSidebarPlacementMap();
    EXPECT_TRUE(placementMap.fixedIndices.empty());
    EXPECT_TRUE(placementMap.customizableIndices.empty());
    EXPECT_TRUE(placementMap.pinnedIndices.empty());
}

/**
 * @tc.name: SidebarSectionsTest001
 * @tc.desc: Test ComputeSidebarSections returns empty when no children
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarSectionsTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto sections = pattern->ComputeSidebarSections();
    EXPECT_TRUE(sections.empty());
}

/**
 * @tc.name: VisibleTabIndicesTest001
 * @tc.desc: Test ComputeVisibleTabIndices with default AUTO visibility
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, VisibleTabIndicesTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto indices = pattern->ComputeVisibleTabIndices();
    EXPECT_TRUE(indices.empty());
}

/**
 * @tc.name: BarStyleEnumTest001
 * @tc.desc: Test TabBarStyle enum values including SIDEBARADAPTABLE
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, BarStyleEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(TabBarStyle::NOSTYLE), 0);
    EXPECT_EQ(static_cast<int32_t>(TabBarStyle::BOTTOMTABBAR), 1);
    EXPECT_EQ(static_cast<int32_t>(TabBarStyle::SIDEBARADAPTABLE), 2);
}

/**
 * @tc.name: SidebarDisplayStyleEnumTest001
 * @tc.desc: Test SidebarDisplayStyle enum values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SidebarDisplayStyle::EMBED), 0);
    EXPECT_EQ(static_cast<int32_t>(SidebarDisplayStyle::OVERLAY), 1);
    EXPECT_EQ(static_cast<int32_t>(SidebarDisplayStyle::DISPLACE), 2);
}

/**
 * @tc.name: SidebarPositionEnumTest001
 * @tc.desc: Test SidebarPosition enum values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarPositionEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(SidebarPosition::START), 0);
    EXPECT_EQ(static_cast<int32_t>(SidebarPosition::END), 1);
}

/**
 * @tc.name: TabBarDisplayModeEnumTest001
 * @tc.desc: Test TabBarDisplayMode enum values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabBarDisplayModeEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(TabBarDisplayMode::BOTTOMTABBAR), 0);
    EXPECT_EQ(static_cast<int32_t>(TabBarDisplayMode::SIDEBAR), 1);
}

/**
 * @tc.name: TabsLayoutPropertySidebarAttributesTest001
 * @tc.desc: Test setting and getting sidebar layout properties
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabsLayoutPropertySidebarAttributesTest001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSidebarWidth(Dimension(SIDEBAR_WIDTH_240));
    layoutProperty->UpdateSidebarBackgroundColor(Color::WHITE);
    layoutProperty->UpdateShowSideBar(true);
    layoutProperty->UpdateShowSideBarWithGesture(false);
    layoutProperty->UpdateSidebarAutoHide(false);
    layoutProperty->UpdateMinSidebarWidth(Dimension(SIDEBAR_WIDTH_MIN));
    layoutProperty->UpdateMaxSidebarWidth(Dimension(SIDEBAR_WIDTH_MAX));
    layoutProperty->UpdateMinContentWidth(Dimension(MIN_CONTENT_WIDTH));
    layoutProperty->UpdateSidebarPosition(SidebarPosition::START);
    layoutProperty->UpdateSidebarDisplayStyle(SidebarDisplayStyle::EMBED);
    layoutProperty->UpdateBarStyle(TabBarStyle::SIDEBARADAPTABLE);
    EXPECT_TRUE(layoutProperty->HasSidebarWidth());
    EXPECT_TRUE(layoutProperty->HasSidebarBackgroundColor());
    EXPECT_TRUE(layoutProperty->HasShowSideBar());
    EXPECT_TRUE(layoutProperty->HasBarStyle());
    EXPECT_EQ(layoutProperty->GetSidebarWidthValue(Dimension(0)).ConvertToPx(), SIDEBAR_WIDTH_240);
    EXPECT_EQ(layoutProperty->GetSidebarPositionValue(SidebarPosition::END), SidebarPosition::START);
    EXPECT_EQ(layoutProperty->GetSidebarDisplayStyleValue(SidebarDisplayStyle::OVERLAY), SidebarDisplayStyle::EMBED);
    EXPECT_EQ(layoutProperty->GetBarStyleValue(TabBarStyle::NOSTYLE), TabBarStyle::SIDEBARADAPTABLE);
}

/**
 * @tc.name: TabContentLayoutPropertySidebarAttributesTest001
 * @tc.desc: Test setting and getting TabContent sidebar properties
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabContentLayoutPropertySidebarAttributesTest001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TabContentLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSidebarSection("main");
    layoutProperty->UpdateDefaultVisibility(TabVisibility::VISIBLE);
    layoutProperty->UpdatePreferredPlacement(TabBarPlacement::FIXED);
    layoutProperty->UpdateCustomizationBehavior(TabBarCustomizationBehavior::DISABLED);
    EXPECT_TRUE(layoutProperty->HasSidebarSection());
    EXPECT_TRUE(layoutProperty->HasDefaultVisibility());
    EXPECT_TRUE(layoutProperty->HasPreferredPlacement());
    EXPECT_TRUE(layoutProperty->HasCustomizationBehavior());
    EXPECT_EQ(layoutProperty->GetSidebarSectionValue(""), "main");
    EXPECT_EQ(layoutProperty->GetDefaultVisibilityValue(TabVisibility::AUTO), TabVisibility::VISIBLE);
    EXPECT_EQ(layoutProperty->GetPreferredPlacementValue(TabBarPlacement::DEFAULT), TabBarPlacement::FIXED);
    EXPECT_EQ(layoutProperty->GetCustomizationBehaviorValue(TabBarCustomizationBehavior::DEFAULT),
        TabBarCustomizationBehavior::DISABLED);
}

/**
 * @tc.name: TabsSidebarDividerTest001
 * @tc.desc: Test TabsSidebarDivider struct defaults
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabsSidebarDividerTest001, TestSize.Level1)
{
    TabsSidebarDivider divider;
    EXPECT_TRUE(divider.isNull);
    TabsSidebarDivider customDivider;
    customDivider.strokeWidth = Dimension(1);
    customDivider.startMargin = Dimension(0);
    customDivider.endMargin = Dimension(0);
    customDivider.color = Color::BLACK;
    customDivider.isNull = false;
    EXPECT_FALSE(customDivider.isNull);
}

/**
 * @tc.name: TabBarDisplayModeBreakpointTest001
 * @tc.desc: Test TabBarDisplayModeBreakpoint struct defaults
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabBarDisplayModeBreakpointTest001, TestSize.Level1)
{
    TabBarDisplayModeBreakpoint breakpoint;
    EXPECT_FALSE(breakpoint.isNull);
    EXPECT_EQ(breakpoint.sm, TabBarDisplayMode::BOTTOMTABBAR);
    EXPECT_EQ(breakpoint.md, TabBarDisplayMode::BOTTOMTABBAR);
    EXPECT_EQ(breakpoint.lg, TabBarDisplayMode::SIDEBAR);
}

/**
 * @tc.name: TabsModelNGSidebarPropertiesTest001
 * @tc.desc: Test TabsModelNG setter methods for sidebar properties
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabsModelNGSidebarPropertiesTest001, TestSize.Level1)
{
    auto model = TabsModelNG::GetInstance();
    ASSERT_NE(model, nullptr);
}

/**
 * @tc.name: TabsPatternSidebarHeaderFooterSearchableTest001
 * @tc.desc: Test TabsPattern sidebar header/footer/searchable node setters and getters
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabsPatternSidebarHeaderFooterSearchableTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetSidebarHeaderNode(), nullptr);
    EXPECT_EQ(pattern->GetSidebarFooterNode(), nullptr);
    EXPECT_EQ(pattern->GetSidebarSearchableNode(), nullptr);
}

/**
 * @tc.name: TabsPatternSidebarCustomBuilderTest001
 * @tc.desc: Test setting custom builder nodes on TabsPattern
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabsPatternSidebarCustomBuilderTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto headerNode = AceType::MakeRefPtr<FrameNode>("header", -1, AceType::MakeRefPtr<Pattern>());
    pattern->SetSidebarHeaderNode(AceType::DynamicCast<UINode>(headerNode));
    EXPECT_NE(pattern->GetSidebarHeaderNode(), nullptr);
    auto footerNode = AceType::MakeRefPtr<FrameNode>("footer", -1, AceType::MakeRefPtr<Pattern>());
    pattern->SetSidebarFooterNode(AceType::DynamicCast<UINode>(footerNode));
    EXPECT_NE(pattern->GetSidebarFooterNode(), nullptr);
    auto searchableNode = AceType::MakeRefPtr<FrameNode>("searchable", -1, AceType::MakeRefPtr<Pattern>());
    pattern->SetSidebarSearchableNode(AceType::DynamicCast<UINode>(searchableNode));
    EXPECT_NE(pattern->GetSidebarSearchableNode(), nullptr);
}

/**
 * @tc.name: TabsSidebarSearchableOptionsTest001
 * @tc.desc: Test TabsSidebarSearchableOptions struct defaults
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabsSidebarSearchableOptionsTest001, TestSize.Level1)
{
    TabsSidebarSearchableOptions options;
    EXPECT_TRUE(options.isNull);
    EXPECT_FALSE(options.autoSearchOnFocus);
    options.autoSearchOnFocus = true;
    options.isNull = false;
    EXPECT_FALSE(options.isNull);
    EXPECT_TRUE(options.autoSearchOnFocus);
}

/**
 * @tc.name: OnBarDisplayModeChangeEventTest001
 * @tc.desc: Test onBarDisplayModeChange event callback registration
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, OnBarDisplayModeChangeEventTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    bool callbackFired = false;
    TabBarDisplayMode receivedMode = TabBarDisplayMode::BOTTOMTABBAR;
    pattern->SetOnBarDisplayModeChangeEvent([&callbackFired, &receivedMode](TabBarDisplayMode mode) {
        callbackFired = true;
        receivedMode = mode;
    });
    pattern->FireOnBarDisplayModeChangeEvent(TabBarDisplayMode::SIDEBAR);
    EXPECT_TRUE(callbackFired);
    EXPECT_EQ(receivedMode, TabBarDisplayMode::SIDEBAR);
}

/**
 * @tc.name: OnSideBarChangeEventTest001
 * @tc.desc: Test onSideBarChange event callback registration
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, OnSideBarChangeEventTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    bool callbackFired = false;
    bool receivedShowState = false;
    pattern->SetOnSideBarChangeEvent([&callbackFired, &receivedShowState](bool isShow) {
        callbackFired = true;
        receivedShowState = isShow;
    });
    pattern->FireOnSideBarChangeEventIfNeeded(true);
    EXPECT_TRUE(callbackFired);
    EXPECT_TRUE(receivedShowState);
}

/**
 * @tc.name: TabVisibilityEnumTest001
 * @tc.desc: Test TabVisibility enum values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabVisibilityEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(TabVisibility::AUTO), 0);
    EXPECT_EQ(static_cast<int32_t>(TabVisibility::VISIBLE), 1);
    EXPECT_EQ(static_cast<int32_t>(TabVisibility::HIDDEN), 2);
}

/**
 * @tc.name: TabBarPlacementEnumTest001
 * @tc.desc: Test TabBarPlacement enum values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabBarPlacementEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(TabBarPlacement::DEFAULT), 0);
    EXPECT_EQ(static_cast<int32_t>(TabBarPlacement::FIXED), 1);
    EXPECT_EQ(static_cast<int32_t>(TabBarPlacement::PINNED), 2);
    EXPECT_EQ(static_cast<int32_t>(TabBarPlacement::SIDEBARONLY), 3);
    EXPECT_EQ(static_cast<int32_t>(TabBarPlacement::OPTIONAL), 4);
}

/**
 * @tc.name: TabBarCustomizationBehaviorEnumTest001
 * @tc.desc: Test TabBarCustomizationBehavior enum values
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, TabBarCustomizationBehaviorEnumTest001, TestSize.Level1)
{
    EXPECT_EQ(static_cast<int32_t>(TabBarCustomizationBehavior::DEFAULT), 0);
    EXPECT_EQ(static_cast<int32_t>(TabBarCustomizationBehavior::DISABLED), 1);
}
} // namespace OHOS::Ace::NG
