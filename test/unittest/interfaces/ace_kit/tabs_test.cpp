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
#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "ui/view/components/tabs/tabs.h"
#include "ui/base/ace_type.h"
#include "ui/resource/resource_object.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_layout_property.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace;
using namespace OHOS::Ace::Kit;

namespace {
const Dimension TEST_TAB_BAR_WIDTH(100.0);
const Dimension TEST_TAB_BAR_HEIGHT(50.0);
const Dimension TEST_STROKE_WIDTH(2.0);
const Color TEST_BG_COLOR(0xFF112233);
const int32_t TEST_NODE_ID = 10001;
}

namespace OHOS::Ace::Kit {

class TabsResObjTest : public testing::Test {
protected:
    void SetUp() override
    {
        NG::MockPipelineContext::SetUp();
        g_isConfigChangePerform = true;
        auto aceNode = NG::TabsModelNG::CreateFrameNode(TEST_NODE_ID);
        ASSERT_NE(aceNode, nullptr);
        auto frameNodeImpl = AceType::MakeRefPtr<FrameNodeImpl>(aceNode);
        RefPtr<Kit::FrameNode> baseNode = frameNodeImpl;
        tabs_ = AceType::MakeRefPtr<Tabs>(baseNode);
    }

    void TearDown() override
    {
        tabs_ = nullptr;
        g_isConfigChangePerform = false;
        NG::MockPipelineContext::TearDown();
    }

    RefPtr<NG::TabsNode> GetAceTabsNode()
    {
        auto frameNodeImpl = AceType::DynamicCast<FrameNodeImpl>(tabs_->node_);
        if (!frameNodeImpl) {
            return nullptr;
        }
        auto aceNode = frameNodeImpl->GetAceNode();
        if (!aceNode) {
            return nullptr;
        }
        return AceType::DynamicCast<NG::TabsNode>(aceNode);
    }

    NG::TabsPattern* GetTabsPattern()
    {
        auto tabsNode = GetAceTabsNode();
        if (!tabsNode) {
            return nullptr;
        }
        auto pattern = tabsNode->GetPattern<NG::TabsPattern>();
        return pattern ? pattern.GetRawPtr() : nullptr;
    }

    RefPtr<ResourceObject> MakeResObj()
    {
        return AceType::MakeRefPtr<ResourceObject>();
    }

protected:
    RefPtr<Tabs> tabs_;
};

// ===== SetTabBarWidth resObj overload =====

HWTEST_F(TabsResObjTest, SetTabBarWidthResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    tabs_->SetTabBarWidth(TEST_TAB_BAR_WIDTH, resObj);
    auto tabsNode = GetAceTabsNode();
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProp = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetBarWidth().has_value());
    EXPECT_EQ(layoutProp->GetBarWidth().value(), TEST_TAB_BAR_WIDTH);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetTabBarWidthResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    tabs_->SetTabBarWidth(TEST_TAB_BAR_WIDTH, resObj);
    auto tabsNode = GetAceTabsNode();
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProp = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetBarWidth().has_value());
    EXPECT_EQ(layoutProp->GetBarWidth().value(), TEST_TAB_BAR_WIDTH);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetTabBarWidthResObj_NullResObj, TestSize.Level1)
{
    tabs_->SetTabBarWidth(TEST_TAB_BAR_WIDTH, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetTabBarHeight resObj overload =====

HWTEST_F(TabsResObjTest, SetTabBarHeightResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    tabs_->SetTabBarHeight(TEST_TAB_BAR_HEIGHT, resObj);
    auto tabsNode = GetAceTabsNode();
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProp = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetBarHeight().has_value());
    EXPECT_EQ(layoutProp->GetBarHeight().value(), TEST_TAB_BAR_HEIGHT);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetTabBarHeightResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    tabs_->SetTabBarHeight(TEST_TAB_BAR_HEIGHT, resObj);
    auto tabsNode = GetAceTabsNode();
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProp = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetBarHeight().has_value());
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetTabBarHeightResObj_NullResObj, TestSize.Level1)
{
    tabs_->SetTabBarHeight(TEST_TAB_BAR_HEIGHT, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetDivider resObj overload =====

HWTEST_F(TabsResObjTest, SetDividerResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    TabsItemDivider divider;
    divider.strokeWidth = TEST_STROKE_WIDTH;
    divider.isNull = false;
    tabs_->SetDivider(divider, resObj, resObj, resObj, resObj);
    auto tabsNode = GetAceTabsNode();
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProp = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetDivider().has_value());
    EXPECT_EQ(layoutProp->GetDivider().value().strokeWidth, TEST_STROKE_WIDTH);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetDividerResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    TabsItemDivider divider;
    divider.strokeWidth = TEST_STROKE_WIDTH;
    divider.isNull = false;
    tabs_->SetDivider(divider, resObj, resObj, resObj, resObj);
    auto tabsNode = GetAceTabsNode();
    ASSERT_NE(tabsNode, nullptr);
    auto layoutProp = tabsNode->GetLayoutProperty<NG::TabsLayoutProperty>();
    ASSERT_NE(layoutProp, nullptr);
    EXPECT_TRUE(layoutProp->GetDivider().has_value());
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetDividerResObj_NullResObj, TestSize.Level1)
{
    TabsItemDivider divider;
    divider.strokeWidth = TEST_STROKE_WIDTH;
    divider.isNull = false;
    tabs_->SetDivider(divider, nullptr, nullptr, nullptr, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetScrollableBarModeOptions resObj overload =====

HWTEST_F(TabsResObjTest, SetScrollableBarModeOptionsResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    ScrollableBarModeOptions option;
    option.margin = Dimension(10.0);
    tabs_->SetScrollableBarModeOptions(option, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetScrollableBarModeOptionsResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    ScrollableBarModeOptions option;
    tabs_->SetScrollableBarModeOptions(option, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetScrollableBarModeOptionsResObj_NullResObj, TestSize.Level1)
{
    ScrollableBarModeOptions option;
    tabs_->SetScrollableBarModeOptions(option, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetEffectNodeOption resObj overload =====

HWTEST_F(TabsResObjTest, SetEffectNodeOptionResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    TabsEffectNodeOption option;
    tabs_->SetEffectNodeOption(option, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetEffectNodeOptionResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    TabsEffectNodeOption option;
    tabs_->SetEffectNodeOption(option, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetEffectNodeOptionResObj_NullResObj, TestSize.Level1)
{
    TabsEffectNodeOption option;
    tabs_->SetEffectNodeOption(option, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetBarBackgroundBlurStyle resObj overload =====

HWTEST_F(TabsResObjTest, SetBarBackgroundBlurStyleResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    BlurStyleOption styleOption;
    tabs_->SetBarBackgroundBlurStyle(styleOption, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetBarBackgroundBlurStyleResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    BlurStyleOption styleOption;
    tabs_->SetBarBackgroundBlurStyle(styleOption, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetBarBackgroundBlurStyleResObj_NullResObj, TestSize.Level1)
{
    BlurStyleOption styleOption;
    tabs_->SetBarBackgroundBlurStyle(styleOption, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetBarBackgroundColor resObj overload =====

HWTEST_F(TabsResObjTest, SetBarBackgroundColorResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    tabs_->SetBarBackgroundColor(TEST_BG_COLOR, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetBarBackgroundColorResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    tabs_->SetBarBackgroundColor(TEST_BG_COLOR, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetBarBackgroundColorResObj_NullResObj, TestSize.Level1)
{
    tabs_->SetBarBackgroundColor(TEST_BG_COLOR, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

// ===== SetBarBackgroundEffect resObj overload =====

HWTEST_F(TabsResObjTest, SetBarBackgroundEffectResObj_Register, TestSize.Level1)
{
    auto resObj = MakeResObj();
    EffectOption effectOption;
    tabs_->SetBarBackgroundEffect(effectOption, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetBarBackgroundEffectResObj_Disabled, TestSize.Level1)
{
    g_isConfigChangePerform = false;
    auto resObj = MakeResObj();
    EffectOption effectOption;
    tabs_->SetBarBackgroundEffect(effectOption, resObj);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

HWTEST_F(TabsResObjTest, SetBarBackgroundEffectResObj_NullResObj, TestSize.Level1)
{
    EffectOption effectOption;
    tabs_->SetBarBackgroundEffect(effectOption, nullptr);
    auto pattern = GetTabsPattern();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

} // namespace OHOS::Ace::Kit
