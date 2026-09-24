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

    /**
     * @tc.expected: DISPLACE mode keeps swiper full width even with End position
     */
    auto swiperRect = swiperNode_->GetGeometryNode()->GetFrameRect();
    EXPECT_TRUE(NearEqual(swiperRect.Width(), TABS_WIDTH));
}
} // namespace OHOS::Ace::NG
