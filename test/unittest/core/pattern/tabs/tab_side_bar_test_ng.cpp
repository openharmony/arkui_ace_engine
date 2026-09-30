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

#include "tabs_test_ng.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/dialog/dialog_theme.h"
#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_node.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_side_bar_pattern.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<Theme> GetDisplayStyleTheme(ThemeType type)
{
    if (type == TabTheme::TypeId()) {
        auto themeConstants = TestNG::CreateThemeConstants(THEME_PATTERN_TAB);
        return TabTheme::Builder().Build(themeConstants);
    }
    return AceType::MakeRefPtr<DialogTheme>();
}

RefPtr<FrameNode> CreateTestNode(const std::string& tag = V2::COLUMN_ETS_TAG)
{
    return FrameNode::CreateFrameNode(tag, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>());
}

void SetupSideBarPattern(RefPtr<FrameNode>& sideBarNode, RefPtr<TabsSideBarPattern>& pattern)
{
    sideBarNode = FrameNode::CreateFrameNode(V2::TABS_SIDE_BAR_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TabsSideBarPattern>());
    pattern = sideBarNode ? sideBarNode->GetPattern<TabsSideBarPattern>() : nullptr;
    if (!pattern) {
        return;
    }
    auto footerContainer = CreateTestNode();
    pattern->footerContainerNode_ = footerContainer;
    footerContainer->MountToParent(sideBarNode);

    auto bottomBarContainer = CreateTestNode();
    pattern->bottomBarContainerNode_ = bottomBarContainer;
    bottomBarContainer->MountToParent(sideBarNode);

    auto maskBlur = CreateTestNode("BottomBarMaskBlur");
    pattern->bottomBarMaskBlurNode_ = maskBlur;
    maskBlur->MountToParent(sideBarNode);

    auto mask = CreateTestNode("BottomBarMask");
    pattern->bottomBarMaskNode_ = mask;
    mask->MountToParent(sideBarNode);

    auto headerMaskBlur = CreateTestNode("HeaderMaskBlur");
    pattern->headerContainerMaskBlurNode_ = headerMaskBlur;
    headerMaskBlur->MountToParent(sideBarNode);

    auto headerMask = CreateTestNode("HeaderMask");
    pattern->headerContainerMaskNode_ = headerMask;
    headerMask->MountToParent(sideBarNode);

    // Set initial visibility INVISIBLE for all mask nodes (matches CreateMaskNodeIfNeeded)
    for (const auto& maskNode : { maskBlur, mask, headerMaskBlur, headerMask }) {
        auto prop = maskNode->GetLayoutProperty();
        if (prop) {
            prop->UpdateVisibility(VisibleType::INVISIBLE);
        }
    }

    auto headerContainer = CreateTestNode();
    pattern->headerContainerNode_ = headerContainer;
    headerContainer->MountToParent(sideBarNode);

    auto tabList = CreateTestNode(V2::TABS_SIDE_BAR_TAB_LIST_TAG);
    pattern->tabListNode_ = tabList;
    tabList->MountToParent(sideBarNode);
}
} // namespace

class TabsSidebarTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite()
    {
        TestNG::SetUpTestSuite();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            return GetDisplayStyleTheme(type);
        });
        EXPECT_CALL(*themeManager, GetTheme(_, _))
            .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {
                return GetDisplayStyleTheme(type);
            });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }
    void FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
    {
        CHECK_NULL_VOID(frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        frameNode->SetActive();
        frameNode->isLayoutDirtyMarked_ = true;
        frameNode->CreateLayoutTask();
        auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
        if (paintProperty) {
            auto wrapper = frameNode->CreatePaintWrapper();
            if (wrapper != nullptr) {
                wrapper->FlushRender();
            }
            paintProperty->CleanDirty();
        }
        frameNode->SetActive(false);
    }
};

/**
 * @tc.name: SidebarDisplayStyleTest001
 * @tc.desc: Test SetSidebarDisplayStyle with EMBED
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and set SidebarDisplayStyle to EMBED
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    TabsModelNG::SetSidebarDisplayStyle(AceType::RawPtr(frameNode_), SidebarDisplayStyle::EMBED);
    FlushUITasks();

    /**
     * @tc.expected: SidebarDisplayStyle is EMBED
     */
    EXPECT_TRUE(layoutProperty_->HasSidebarDisplayStyle());
    EXPECT_EQ(layoutProperty_->GetSidebarDisplayStyleValue(SidebarDisplayStyle::DISPLACE),
        SidebarDisplayStyle::EMBED);
}

/**
 * @tc.name: SidebarDisplayStyleTest002
 * @tc.desc: Test SetSidebarDisplayStyle with DISPLACE
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs and set SidebarDisplayStyle to DISPLACE
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    TabsModelNG::SetSidebarDisplayStyle(AceType::RawPtr(frameNode_), SidebarDisplayStyle::DISPLACE);
    FlushUITasks();

    /**
     * @tc.expected: SidebarDisplayStyle is DISPLACE
     */
    EXPECT_TRUE(layoutProperty_->HasSidebarDisplayStyle());
    EXPECT_EQ(layoutProperty_->GetSidebarDisplayStyleValue(SidebarDisplayStyle::EMBED),
        SidebarDisplayStyle::DISPLACE);
}

/**
 * @tc.name: SidebarDisplayStyleTest003
 * @tc.desc: Test SetSidebarDisplayStyle with nullptr frameNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call SetSidebarDisplayStyle with nullptr
     * @tc.expected: No crash
     */
    TabsModelNG::SetSidebarDisplayStyle(nullptr, SidebarDisplayStyle::EMBED);
    TabsModelNG::SetSidebarDisplayStyle(nullptr, SidebarDisplayStyle::DISPLACE);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SidebarDisplayStyleTest004
 * @tc.desc: Test default value when SidebarDisplayStyle is not set
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs without setting SidebarDisplayStyle
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.expected: SidebarDisplayStyle is not set, default value is EMBED
     */
    EXPECT_FALSE(layoutProperty_->HasSidebarDisplayStyle());
    EXPECT_EQ(layoutProperty_->GetSidebarDisplayStyleValue(SidebarDisplayStyle::EMBED),
        SidebarDisplayStyle::EMBED);
}

/**
 * @tc.name: SidebarDisplayStyleTest005
 * @tc.desc: Test ResetSidebarDisplayStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set SidebarDisplayStyle then reset
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    TabsModelNG::SetSidebarDisplayStyle(AceType::RawPtr(frameNode_), SidebarDisplayStyle::DISPLACE);
    FlushUITasks();
    EXPECT_TRUE(layoutProperty_->HasSidebarDisplayStyle());

    layoutProperty_->ResetSidebarDisplayStyle();
    FlushUITasks();

    /**
     * @tc.expected: SidebarDisplayStyle is reset
     */
    EXPECT_FALSE(layoutProperty_->HasSidebarDisplayStyle());
}

/**
 * @tc.name: SidebarDisplayStyleTest006
 * @tc.desc: Test Clone preserves SidebarDisplayStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set SidebarDisplayStyle then clone layoutProperty
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    TabsModelNG::SetSidebarDisplayStyle(AceType::RawPtr(frameNode_), SidebarDisplayStyle::DISPLACE);
    FlushUITasks();

    auto cloned = AceType::DynamicCast<TabsLayoutProperty>(layoutProperty_->Clone());
    ASSERT_NE(cloned, nullptr);

    /**
     * @tc.expected: Cloned property has same SidebarDisplayStyle
     */
    EXPECT_TRUE(cloned->HasSidebarDisplayStyle());
    EXPECT_EQ(cloned->GetSidebarDisplayStyleValue(SidebarDisplayStyle::EMBED),
        SidebarDisplayStyle::DISPLACE);
}

/**
 * @tc.name: SidebarDisplayStyleTest007
 * @tc.desc: Test ToJsonValue serializes SidebarDisplayStyle correctly
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleTest007, TestSize.Level2)
{
    /**
     * @tc.steps: step1. Test default ToJsonValue (EMBED)
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("sidebarDisplayStyle"), "SidebarDisplayStyle.EMBED");

    /**
     * @tc.steps: step2. Set to DISPLACE and test ToJsonValue
     */
    TabsModelNG::SetSidebarDisplayStyle(AceType::RawPtr(frameNode_), SidebarDisplayStyle::DISPLACE);
    FlushUITasks();
    json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("sidebarDisplayStyle"), "SidebarDisplayStyle.DISPLACE");

    /**
     * @tc.steps: step3. Set back to EMBED and test ToJsonValue
     */
    TabsModelNG::SetSidebarDisplayStyle(AceType::RawPtr(frameNode_), SidebarDisplayStyle::EMBED);
    FlushUITasks();
    json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("sidebarDisplayStyle"), "SidebarDisplayStyle.EMBED");
}

/**
 * @tc.name: SidebarDisplayStyleLayoutTest001
 * @tc.desc: Test MeasureSwiperInSideBarMode with EMBED (content width reduced)
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleLayoutTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs, set barStyle to SIDEBAR, set displayStyle to EMBED
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    model.SetBarLayoutStyle(TabBarLayoutStyle::SIDEBAR);
    model.SetSidebarDisplayStyle(SidebarDisplayStyle::EMBED);
    CreateTabsDone(model);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: EMBED mode reduces swiper width (content compressed by sidebar)
     */
    auto swiperRect = swiperNode_->GetGeometryNode()->GetFrameRect();
    EXPECT_TRUE(swiperRect.Width() < TABS_WIDTH);
}

/**
 * @tc.name: SidebarDisplayStyleLayoutTest002
 * @tc.desc: Test MeasureSwiperInSideBarMode with DISPLACE (content full width)
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs, set barStyle to SIDEBAR, set displayStyle to DISPLACE
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    model.SetBarLayoutStyle(TabBarLayoutStyle::SIDEBAR);
    model.SetSidebarDisplayStyle(SidebarDisplayStyle::DISPLACE);
    CreateTabsDone(model);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: swiper width = Tabs width (full width, not reduced)
     */
    auto swiperRect = swiperNode_->GetGeometryNode()->GetFrameRect();
    EXPECT_TRUE(NearEqual(swiperRect.Width(), TABS_WIDTH));
}

/**
 * @tc.name: SidebarDisplayStyleLayoutTest003
 * @tc.desc: Test LayoutOffsetListInSideBarMode with DISPLACE + End (negative offset)
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarDisplayStyleLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Tabs, set barStyle to SIDEBAR, position to End, displayStyle to DISPLACE
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    model.SetBarLayoutStyle(TabBarLayoutStyle::SIDEBAR);
    model.SetSidebarPosition(BarPosition::END);
    model.SetSidebarDisplayStyle(SidebarDisplayStyle::DISPLACE);
    CreateTabsDone(model);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.expected: DISPLACE mode keeps swiper full width even with End position
     */
    auto swiperRect = swiperNode_->GetGeometryNode()->GetFrameRect();
    EXPECT_TRUE(NearEqual(swiperRect.Width(), TABS_WIDTH));
}

/**
 * @tc.name: SidebarFooterTest001
 * @tc.desc: Test SetSidebarFooter API: null frameNode, set, replace, set null
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarFooterTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetSidebarFooter with null frameNode (no crash)
     */
    auto footer = CreateTestNode();
    TabsModelNG::SetSidebarFooter(nullptr, AceType::DynamicCast<AceType>(footer));
    EXPECT_TRUE(true);

    /**
     * @tc.steps: step2. SetSidebarFooter with valid footer
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    TabsModelNG::SetSidebarFooter(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(footer));
    EXPECT_EQ(pattern_->GetSidebarFooterNode(), footer);

    /**
     * @tc.steps: step3. Replace footer with a new one
     */
    auto footer2 = CreateTestNode();
    TabsModelNG::SetSidebarFooter(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(footer2));
    EXPECT_EQ(pattern_->GetSidebarFooterNode(), footer2);
    EXPECT_NE(pattern_->GetSidebarFooterNode(), footer);

    /**
     * @tc.steps: step4. Set footer to null
     */
    RefPtr<AceType> nullFooter;
    TabsModelNG::SetSidebarFooter(AceType::RawPtr(frameNode_), nullFooter);
    EXPECT_EQ(pattern_->GetSidebarFooterNode(), nullptr);
}

/**
 * @tc.name: SidebarFooterTest002
 * @tc.desc: Test footer container exists, footer synced and removed in SIDEBAR mode
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarFooterTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    model.SetBarLayoutStyle(TabBarLayoutStyle::SIDEBAR);
    CreateTabsDone(model);

    auto sideBarNode = pattern_->GetSideBarNode();
    ASSERT_NE(sideBarNode, nullptr);
    auto sideBarPattern = sideBarNode->GetPattern<TabsSideBarPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step1. Footer container exists after sidebar creation
     */
    EXPECT_NE(sideBarPattern->GetFooterContainerNode(), nullptr);

    /**
     * @tc.steps: step2. Footer is synced to TabsSideBarPattern
     */
    auto footer = CreateTestNode();
    TabsModelNG::SetSidebarFooter(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(footer));
    pattern_->SyncPropertiesToSideBar();
    sideBarPattern->OnModifyDone();
    EXPECT_EQ(sideBarPattern->curFooterNode_, footer);

    /**
     * @tc.steps: step3. Footer is removed when set to null
     */
    RefPtr<AceType> nullFooter;
    TabsModelNG::SetSidebarFooter(AceType::RawPtr(frameNode_), nullFooter);
    pattern_->SyncPropertiesToSideBar();
    sideBarPattern->OnModifyDone();
    EXPECT_EQ(sideBarPattern->curFooterNode_, nullptr);
}

/**
 * @tc.name: SidebarFooterTest003
 * @tc.desc: Test UpdateFooterNodeIfNeeded: null container, no change, mount, replace, remove
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarFooterTest003, TestSize.Level1)
{
    RefPtr<FrameNode> sideBarNode;
    RefPtr<TabsSideBarPattern> pattern;
    SetupSideBarPattern(sideBarNode, pattern);
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. Null footerContainer (early return, no crash)
     */
    pattern->footerContainerNode_ = nullptr;
    pattern->SetFooterNode(CreateTestNode());
    pattern->UpdateFooterNodeIfNeeded();
    EXPECT_TRUE(true);
    SetupSideBarPattern(sideBarNode, pattern);
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. footerNode equals curFooterNode (no change)
     */
    pattern->SetFooterNode(nullptr);
    pattern->UpdateFooterNodeIfNeeded();
    EXPECT_EQ(pattern->curFooterNode_, nullptr);

    /**
     * @tc.steps: step3. Mount new footer when none exists
     */
    auto footer1 = CreateTestNode();
    pattern->SetFooterNode(footer1);
    pattern->UpdateFooterNodeIfNeeded();
    EXPECT_EQ(pattern->curFooterNode_, footer1);
    EXPECT_TRUE(pattern->footerContainerNode_->GetChildren().size() > 0);

    /**
     * @tc.steps: step4. Replace existing footer
     */
    auto footer2 = CreateTestNode();
    pattern->SetFooterNode(footer2);
    pattern->UpdateFooterNodeIfNeeded();
    EXPECT_EQ(pattern->curFooterNode_, footer2);
    EXPECT_NE(pattern->curFooterNode_, footer1);

    /**
     * @tc.steps: step5. Remove footer when set to null
     */
    pattern->SetFooterNode(nullptr);
    pattern->UpdateFooterNodeIfNeeded();
    EXPECT_EQ(pattern->curFooterNode_, nullptr);
}

/**
 * @tc.name: SidebarBottomBarTest001
 * @tc.desc: Test SetSidebarBottomBar API: null frameNode, set, replace, set null
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarBottomBarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetSidebarBottomBar with null frameNode (no crash)
     */
    auto bottomBar = CreateTestNode();
    TabsModelNG::SetSidebarBottomBar(nullptr, AceType::DynamicCast<AceType>(bottomBar));
    EXPECT_TRUE(true);

    /**
     * @tc.steps: step2. SetSidebarBottomBar with valid bottomBar
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    TabsModelNG::SetSidebarBottomBar(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(bottomBar));
    EXPECT_EQ(pattern_->GetSidebarBottomBarNode(), bottomBar);

    /**
     * @tc.steps: step3. Replace bottomBar with a new one
     */
    auto bottomBar2 = CreateTestNode();
    TabsModelNG::SetSidebarBottomBar(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(bottomBar2));
    EXPECT_EQ(pattern_->GetSidebarBottomBarNode(), bottomBar2);
    EXPECT_NE(pattern_->GetSidebarBottomBarNode(), bottomBar);

    /**
     * @tc.steps: step4. Set bottomBar to null
     */
    RefPtr<AceType> nullBottomBar;
    TabsModelNG::SetSidebarBottomBar(AceType::RawPtr(frameNode_), nullBottomBar);
    EXPECT_EQ(pattern_->GetSidebarBottomBarNode(), nullptr);
}

/**
 * @tc.name: SidebarBottomBarTest002
 * @tc.desc: Test bottomBar mask nodes created, bottomBar synced and removed in SIDEBAR mode
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarBottomBarTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    model.SetBarLayoutStyle(TabBarLayoutStyle::SIDEBAR);
    CreateTabsDone(model);

    auto sideBarNode = pattern_->GetSideBarNode();
    ASSERT_NE(sideBarNode, nullptr);
    auto sideBarPattern = sideBarNode->GetPattern<TabsSideBarPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step1. BottomBar mask nodes and container are created
     */
    EXPECT_NE(sideBarPattern->GetBottomBarMaskBlurNode(), nullptr);
    EXPECT_NE(sideBarPattern->GetBottomBarMaskNode(), nullptr);
    EXPECT_NE(sideBarPattern->GetBottomBarContainerNode(), nullptr);

    /**
     * @tc.steps: step2. BottomBar is synced to TabsSideBarPattern
     */
    auto bottomBar = CreateTestNode();
    TabsModelNG::SetSidebarBottomBar(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(bottomBar));
    pattern_->SyncPropertiesToSideBar();
    sideBarPattern->OnModifyDone();
    EXPECT_EQ(sideBarPattern->curBottomBarNode_, bottomBar);

    /**
     * @tc.steps: step3. BottomBar is removed when set to null
     */
    RefPtr<AceType> nullBottomBar;
    TabsModelNG::SetSidebarBottomBar(AceType::RawPtr(frameNode_), nullBottomBar);
    pattern_->SyncPropertiesToSideBar();
    sideBarPattern->OnModifyDone();
    EXPECT_EQ(sideBarPattern->curBottomBarNode_, nullptr);
}

/**
 * @tc.name: SidebarBottomBarTest003
 * @tc.desc: Test UpdateBottomBarNodeIfNeeded: null container, no change, mount, replace, remove
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarBottomBarTest003, TestSize.Level1)
{
    RefPtr<FrameNode> sideBarNode;
    RefPtr<TabsSideBarPattern> pattern;
    SetupSideBarPattern(sideBarNode, pattern);
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. Null bottomBarContainer (early return, no crash)
     */
    pattern->bottomBarContainerNode_ = nullptr;
    pattern->SetBottomBarNode(CreateTestNode());
    pattern->UpdateBottomBarNodeIfNeeded();
    EXPECT_TRUE(true);
    SetupSideBarPattern(sideBarNode, pattern);
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. bottomBarNode equals curBottomBarNode (no change)
     */
    pattern->SetBottomBarNode(nullptr);
    pattern->UpdateBottomBarNodeIfNeeded();
    EXPECT_EQ(pattern->curBottomBarNode_, nullptr);

    /**
     * @tc.steps: step3. Mount new bottomBar
     */
    auto bottomBar1 = CreateTestNode();
    pattern->SetBottomBarNode(bottomBar1);
    pattern->UpdateBottomBarNodeIfNeeded();
    EXPECT_EQ(pattern->curBottomBarNode_, bottomBar1);
    EXPECT_TRUE(pattern->bottomBarContainerNode_->GetChildren().size() > 0);

    /**
     * @tc.steps: step4. Replace existing bottomBar
     */
    auto bottomBar2 = CreateTestNode();
    pattern->SetBottomBarNode(bottomBar2);
    pattern->UpdateBottomBarNodeIfNeeded();
    EXPECT_EQ(pattern->curBottomBarNode_, bottomBar2);
    EXPECT_NE(pattern->curBottomBarNode_, bottomBar1);

    /**
     * @tc.steps: step5. Remove bottomBar when set to null
     */
    pattern->SetBottomBarNode(nullptr);
    pattern->UpdateBottomBarNodeIfNeeded();
    EXPECT_EQ(pattern->curBottomBarNode_, nullptr);
}

/**
 * @tc.name: SidebarBottomBarTest004
 * @tc.desc: Test OnModifyDone visibility, scroll effect enable/disable, mask visibility, create idempotent
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarBottomBarTest004, TestSize.Level1)
{
    RefPtr<FrameNode> sideBarNode;
    RefPtr<TabsSideBarPattern> pattern;
    SetupSideBarPattern(sideBarNode, pattern);
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. IsBottomBarScrollEffectEnabled default false
     */
    EXPECT_FALSE(pattern->IsBottomBarScrollEffectEnabled());

    /**
     * @tc.steps: step2. OnModifyDone with no bottomBar -> container GONE, mask INVISIBLE
     */
    pattern->SetBottomBarNode(nullptr);
    pattern->OnModifyDone();
    auto property = pattern->bottomBarContainerNode_->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::GONE);

    auto maskBlurProp = pattern->bottomBarMaskBlurNode_->GetLayoutProperty();
    ASSERT_NE(maskBlurProp, nullptr);
    EXPECT_EQ(maskBlurProp->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    auto maskProp = pattern->bottomBarMaskNode_->GetLayoutProperty();
    ASSERT_NE(maskProp, nullptr);
    EXPECT_EQ(maskProp->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    /**
     * @tc.steps: step3. OnModifyDone with bottomBar -> container VISIBLE, mask VISIBLE
     */
    pattern->SetBottomBarNode(CreateTestNode());
    pattern->OnModifyDone();
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::GONE), VisibleType::VISIBLE);
    EXPECT_EQ(maskBlurProp->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(maskProp->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step4. InitBottomBarScrollEffect enable -> state true
     */
    pattern->isBottomBarScrollEffectEnabled_ = false;
    pattern->InitBottomBarScrollEffect(true);
    EXPECT_TRUE(pattern->IsBottomBarScrollEffectEnabled());

    /**
     * @tc.steps: step5. InitBottomBarScrollEffect no-op when state unchanged
     */
    pattern->bottomBarScrollScale_ = 0.5f;
    pattern->InitBottomBarScrollEffect(true);
    EXPECT_TRUE(pattern->isBottomBarScrollEffectEnabled_);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.5f);

    /**
     * @tc.steps: step6. InitBottomBarScrollEffect disable -> state false
     */
    pattern->InitBottomBarScrollEffect(false);
    EXPECT_FALSE(pattern->IsBottomBarScrollEffectEnabled());

    /**
     * @tc.steps: step7. CreateBottomBarContainerIfNeeded idempotent
     */
    auto containerBefore = pattern->bottomBarContainerNode_;
    pattern->CreateBottomBarContainerIfNeeded();
    EXPECT_EQ(pattern->bottomBarContainerNode_, containerBefore);

    /**
     * @tc.steps: step8. CreateBottomBarMaskNodeIfNeeded idempotent
     */
    auto maskBlurBefore = pattern->bottomBarMaskBlurNode_;
    auto maskBefore = pattern->bottomBarMaskNode_;
    pattern->CreateBottomBarMaskNodeIfNeeded();
    EXPECT_EQ(pattern->bottomBarMaskBlurNode_, maskBlurBefore);
    EXPECT_EQ(pattern->bottomBarMaskNode_, maskBefore);
}

/**
 * @tc.name: SidebarBottomBarTest005
 * @tc.desc: Test UpdateBottomBarBlurStyle and OnTabListScroll with various scales and edge cases
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarBottomBarTest005, TestSize.Level1)
{
    RefPtr<FrameNode> sideBarNode;
    RefPtr<TabsSideBarPattern> pattern;
    SetupSideBarPattern(sideBarNode, pattern);
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. scrollScale = 0 when effect enabled (reset blur)
     */
    pattern->isBottomBarScrollEffectEnabled_ = true;
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->UpdateBottomBarBlurStyle(0.0f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.0f);

    /**
     * @tc.steps: step2. scrollScale > 0 when effect enabled (gradient blur)
     */
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->UpdateBottomBarBlurStyle(0.5f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.5f);

    /**
     * @tc.steps: step3. No-op when scale unchanged
     */
    pattern->UpdateBottomBarBlurStyle(0.5f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.5f);

    /**
     * @tc.steps: step4. When effect disabled, cache updates but no visual change
     */
    pattern->isBottomBarScrollEffectEnabled_ = false;
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->UpdateBottomBarBlurStyle(0.8f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.8f);

    /**
     * @tc.steps: step5. OnTabListScroll updates both header and bottomBar blur
     */
    pattern->isScrollEffectEnabled_ = true;
    pattern->isBottomBarScrollEffectEnabled_ = true;
    pattern->scrollScale_ = -1.0f;
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->OnTabListScroll(10.0f, 100.0f);
    EXPECT_GE(pattern->scrollScale_, 0.0f);
    EXPECT_GE(pattern->bottomBarScrollScale_, 0.0f);

    /**
     * @tc.steps: step6. OnTabListScroll with zero scrollableDistance
     */
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->OnTabListScroll(10.0f, 0.0f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.0f);

    /**
     * @tc.steps: step7. OnTabListScroll zero offset -> scrollScale = 0
     */
    pattern->scrollScale_ = -1.0f;
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->OnTabListScroll(0.0f, 100.0f);
    EXPECT_FLOAT_EQ(pattern->scrollScale_, 0.0f);
    EXPECT_GT(pattern->bottomBarScrollScale_, 0.0f);

    /**
     * @tc.steps: step8. OnTabListScroll exceed <= 0 -> bottomScrollScale = 0
     */
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->OnTabListScroll(100.0f, 50.0f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.0f);

    /**
     * @tc.steps: step9. OnTabListScroll large offset clamped to [0, 1]
     */
    pattern->scrollScale_ = -1.0f;
    pattern->bottomBarScrollScale_ = -1.0f;
    pattern->OnTabListScroll(10000.0f, 50.0f);
    EXPECT_FLOAT_EQ(pattern->scrollScale_, 1.0f);
    EXPECT_FLOAT_EQ(pattern->bottomBarScrollScale_, 0.0f);
}

/**
 * @tc.name: SidebarBottomBarTest006
 * @tc.desc: Test bottomBar container layout positioning and GONE when no bottomBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsSidebarTestNg, SidebarBottomBarTest006, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    model.SetBarLayoutStyle(TabBarLayoutStyle::SIDEBAR);
    CreateTabsDone(model);

    auto sideBarNode = pattern_->GetSideBarNode();
    ASSERT_NE(sideBarNode, nullptr);
    auto sideBarPattern = sideBarNode->GetPattern<TabsSideBarPattern>();
    ASSERT_NE(sideBarPattern, nullptr);

    /**
     * @tc.steps: step1. No bottomBar -> container is GONE
     */
    auto bottomBarContainer = sideBarPattern->GetBottomBarContainerNode();
    ASSERT_NE(bottomBarContainer, nullptr);
    auto property = bottomBarContainer->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::GONE);

    /**
     * @tc.steps: step2. Set bottomBar -> container positioned at bottom
     */
    auto bottomBar = CreateTestNode();
    ViewAbstract::SetWidth(CalcLength(100.0f));
    ViewAbstract::SetHeight(CalcLength(50.0f));
    TabsModelNG::SetSidebarBottomBar(AceType::RawPtr(frameNode_), AceType::DynamicCast<AceType>(bottomBar));
    FlushUITasks();

    auto containerRect = bottomBarContainer->GetGeometryNode()->GetFrameRect();
    auto sideBarRect = sideBarNode->GetGeometryNode()->GetFrameRect();
    EXPECT_TRUE(containerRect.Bottom() <= sideBarRect.Bottom() + 1.0f);
}
} // namespace OHOS::Ace::NG
