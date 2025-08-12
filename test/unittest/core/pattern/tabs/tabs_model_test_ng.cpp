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

#include "gtest/gtest.h"
#include "tabs_test_ng.h"
#include "ui/base/ace_type.h"

#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "frameworks/core/common/resource/resource_parse_utils.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_resource_adapter_v2.h"

namespace OHOS::Ace::NG {

class TabsModelTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: SetTabBarIndex001
 * @tc.desc: Test TabsModelNG SetTabBarIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetTabBarIndex001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    int32_t index = 2;
    tabsLayoutProperty->propIndex_ = index;
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    model.SetTabBarIndex(frameNode, 2);
    EXPECT_FALSE(tabsLayoutProperty->propIndexSetByUser_.has_value());
}

/**
 * @tc.name: SetTabBarIndex002
 * @tc.desc: Test TabsModelNG SetTabBarIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetTabBarIndex002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    int32_t index = -1;
    tabsLayoutProperty->propIndex_ = index;
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    model.SetTabBarIndex(frameNode, -1);
    EXPECT_FALSE(tabsLayoutProperty->propIndexSetByUser_.has_value());
}

/**
 * @tc.name: SetTabBarIndex003
 * @tc.desc: Test TabsModelNG SetTabBarIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetTabBarIndex003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    int32_t index = 2;
    tabsLayoutProperty->propIndex_ = index;
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    model.SetTabBarIndex(frameNode, -1);
    EXPECT_FALSE(tabsLayoutProperty->propIndexSetByUser_.has_value());
}

/**
 * @tc.name: SetTabBarIndex004
 * @tc.desc: Test TabsModelNG SetTabBarIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetTabBarIndex004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    int32_t index = 2;
    tabsLayoutProperty->propIndex_ = index;
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    model.SetTabBarIndex(frameNode, 1);
    EXPECT_EQ(tabsLayoutProperty->propIndexSetByUser_.value(), 1);
}

/**
 * @tc.name: SetTabBarIndex005
 * @tc.desc: Test TabsModelNG SetTabBarIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetTabBarIndex005, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    model.SetTabBarIndex(frameNode, 4);
    EXPECT_EQ(tabsLayoutProperty->propIndexSetByUser_.value(), 4);
}

/**
 * @tc.name: SetBarBackgroundEffect001
 * @tc.desc: Test TabsModelNG SetBarBackgroundEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetBarBackgroundEffect001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TABS_COMPONENT_TAG, 1, tabsPattern);
    ASSERT_NE(node, nullptr);
    int32_t nodeId = 1;
    node->nodeId_ = nodeId;
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    pipe->onWindowFocusChangedCallbacks_.clear();
    pipe->AddWindowFocusChangedCallback(node->GetId());
    node->context_ = AceType::RawPtr(pipe);
    tabsNode->children_.clear();
    tabsNode->children_.emplace_back(node);
    tabsNode->children_.emplace_back(node);
    tabsNode->children_.emplace_back(node);
    tabsNode->children_.emplace_back(node);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    EffectOption effectOption;
    effectOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    model.SetBarBackgroundEffect(frameNode, effectOption);
    EXPECT_TRUE(pipe->onWindowFocusChangedCallbacks_.empty());
}

/**
 * @tc.name: SetBarBackgroundEffect002
 * @tc.desc: Test TabsModelNG SetBarBackgroundEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, SetBarBackgroundEffect002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    RefPtr<TabsPattern> tabsPattern = AceType::MakeRefPtr<TabsPattern>();
    RefPtr<FrameNode> tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG, 2, tabsPattern, true);
    ASSERT_NE(tabsNode, nullptr);
    auto node = FrameNode::CreateFrameNode(V2::TABS_COMPONENT_TAG, 2, tabsPattern);
    ASSERT_NE(node, nullptr);
    int32_t nodeId = 2;
    node->nodeId_ = nodeId;
    RefPtr<PipelineContext> pipe = AceType::MakeRefPtr<PipelineContext>();
    pipe->onWindowFocusChangedCallbacks_.clear();
    pipe->onWindowFocusChangedCallbacks_.emplace(nodeId);
    pipe->RemoveWindowFocusChangedCallback(node->GetId());
    node->context_ = AceType::RawPtr(pipe);
    tabsNode->children_.clear();
    tabsNode->children_.emplace_back(node);
    tabsNode->children_.emplace_back(node);
    tabsNode->children_.emplace_back(node);
    tabsNode->children_.emplace_back(node);
    auto frameNode = AceType::RawPtr(tabsNode);
    RefPtr<TabsLayoutProperty> tabsLayoutProperty = AceType::MakeRefPtr<TabsLayoutProperty>();
    tabsLayoutProperty->Reset();
    tabsNode->layoutProperty_ = tabsLayoutProperty;
    tabsPattern->frameNode_ = tabsNode;
    EffectOption effectOption;
    effectOption.policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    model.SetBarBackgroundEffect(frameNode, effectOption);
    EXPECT_FALSE(pipe->onWindowFocusChangedCallbacks_.empty());
}

/**
 * @tc.name: HandleBarGridGutterTest001
 * @tc.desc: Verify TabsModelNG::HandleBarGridGutter
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBarGridGutterTest001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    BarGridColumnOptions columnOption;
    tabBarLayoutProperty_->UpdateBarGridAlign(columnOption);
    model.HandleBarGridGutter(frameNode, resObj);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(tabBarLayoutProperty_, nullptr);
    EXPECT_TRUE(tabBarLayoutProperty_->GetBarGridAlign().has_value());

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "0";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        -1, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    model.HandleBarGridGutter(frameNode, resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(tabBarLayoutProperty_->GetBarGridAlign()->gutter, Dimension(0.0_vp));
    CreateDone();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: HandleBarGridMarginTest001
 * @tc.desc: Verify TabsModelNG::HandleBarGridMargin
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBarGridMarginTest001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    BarGridColumnOptions columnOption;
    tabBarLayoutProperty_->UpdateBarGridAlign(columnOption);
    model.HandleBarGridMargin(frameNode, resObj);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(tabBarLayoutProperty_, nullptr);
    EXPECT_TRUE(tabBarLayoutProperty_->GetBarGridAlign().has_value());

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "0";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        -1, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    model.HandleBarGridMargin(frameNode, resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(tabBarLayoutProperty_->GetBarGridAlign()->margin, Dimension(0.0_vp));
    CreateDone();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: HandleScrollableBarMarginTest001
 * @tc.desc: Verify TabsModelNG::HandleScrollableBarMargin
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleScrollableBarMarginTest001, TestSize.Level1)
{
    g_isConfigChangePerform = true;
    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    ScrollableBarModeOptions option;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    model.HandleScrollableBarMargin(frameNode, resObj);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_NE(tabBarLayoutProperty_, nullptr);
    EXPECT_TRUE(tabBarLayoutProperty_->GetScrollableBarModeOptions().has_value());

    ResourceObjectParams param;
    param.type = ResourceObjectParamType::STRING;
    param.value = "0";
    std::vector<ResourceObjectParams> params;
    params.push_back(param);
    auto resObjWithString = AceType::MakeRefPtr<ResourceObject>(
        -1, static_cast<int32_t>(ResourceType::STRING), params, "", "", Container::CurrentIdSafely());
    model.HandleScrollableBarMargin(frameNode, resObjWithString);
    pattern_->resourceMgr_->ReloadResources();
    EXPECT_EQ(tabBarLayoutProperty_->GetScrollableBarModeOptions()->margin, Dimension(0.0_vp));
    CreateDone();
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: HandleBackgroundEffectColorTest001
 * @tc.desc: Verify TabsModelNG::HandleBackgroundEffectColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBackgroundEffectColorTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    TabsModelNG::HandleBackgroundEffectColor(frameNode, resObj);
    pattern_->resourceMgr_->ReloadResources();

    auto tabsNode = AceType::DynamicCast<TabsNode>(AceType::Claim<FrameNode>(frameNode));
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto target = tabBarNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    auto currentEffect = target->GetBackgroundEffect();

    EXPECT_TRUE(currentEffect.has_value());
    CreateDone();
}

/**
 * @tc.name: HandleBackgroundEffectInactiveColorTest001
 * @tc.desc: Verify TabsModelNG::HandleBackgroundEffectInactiveColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBackgroundEffectInactiveColorTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    TabsModelNG::HandleBackgroundEffectInactiveColor(frameNode, resObj);
    pattern_->resourceMgr_->ReloadResources();

    auto tabsNode = AceType::DynamicCast<TabsNode>(AceType::Claim<FrameNode>(frameNode));
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto target = tabBarNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    auto currentEffect = target->GetBackgroundEffect();

    EXPECT_TRUE(currentEffect.has_value());
    CreateDone();
}

/**
 * @tc.name: HandleBackgroundBlurStyleInactiveColorTest001
 * @tc.desc: Verify TabsModelNG::HandleBackgroundBlurStyleInactiveColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBackgroundBlurStyleInactiveColorTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto resObj = AceType::MakeRefPtr<ResourceObject>("", "", Container::CurrentIdSafely());
    TabsModelNG::HandleBackgroundBlurStyleInactiveColor(frameNode, resObj);
    pattern_->resourceMgr_->ReloadResources();

    auto tabsNode = AceType::DynamicCast<TabsNode>(AceType::Claim<FrameNode>(frameNode));
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto target = tabBarNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    auto currentOption = target->GetBackBlurStyle();

    EXPECT_TRUE(currentOption.has_value());
    CreateDone();
}

/**
 * @tc.name: HandleBackgroundEffectInactiveColorTest002
 * @tc.desc: Verify TabsModelNG::HandleBackgroundEffectInactiveColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBackgroundEffectInactiveColorTest002, TestSize.Level1)
{
    ResetMockResourceData();

    const int32_t resId = 0;
    const int32_t resType = static_cast<int32_t>(ResourceType::COLOR);
    const Color resData = Color::RED;
    AddMockResourceData(0, resData);

    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern_, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(AceType::Claim<FrameNode>(frameNode));
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto target = tabBarNode->GetRenderContext();
    ASSERT_NE(target, nullptr);

    TabsModelNG::HandleBackgroundEffectInactiveColor(frameNode, nullptr);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_TRUE(target->GetBackgroundEffect().has_value());
    EXPECT_TRUE(target->GetBackgroundEffect()->isWindowFocused);

    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(resId, resType, params, "", "", Container::CurrentIdSafely());
    TabsModelNG::HandleBackgroundEffectInactiveColor(frameNode, resObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_TRUE(target->GetBackgroundEffect().has_value());
    EXPECT_EQ(target->GetBackgroundEffect()->inactiveColor, resData);
    CreateDone();
    ResetMockResourceData();
}

/**
 * @tc.name: HandleBackgroundBlurStyleInactiveColorTest002
 * @tc.desc: Verify TabsModelNG::HandleBackgroundBlurStyleInactiveColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNg, HandleBackgroundBlurStyleInactiveColorTest002, TestSize.Level1)
{
    ResetMockResourceData();

    const int32_t resId = 0;
    const int32_t resType = static_cast<int32_t>(ResourceType::COLOR);
    const Color resData = Color::RED;
    AddMockResourceData(0, resData);

    TabsModelNG model = CreateTabs();
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern_, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(AceType::Claim<FrameNode>(frameNode));
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabBar());
    ASSERT_NE(tabBarNode, nullptr);
    auto target = tabBarNode->GetRenderContext();
    ASSERT_NE(target, nullptr);

    target->ResetBackBlurStyle();
    TabsModelNG::HandleBackgroundBlurStyleInactiveColor(frameNode, nullptr);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_TRUE(target->GetBackBlurStyle().has_value());
    EXPECT_TRUE(target->GetBackBlurStyle()->isWindowFocused);

    std::vector<ResourceObjectParams> params;
    auto resObj = AceType::MakeRefPtr<ResourceObject>(resId, resType, params, "", "", Container::CurrentIdSafely());
    target->ResetBackBlurStyle();
    TabsModelNG::HandleBackgroundBlurStyleInactiveColor(frameNode, resObj);
    ASSERT_NE(pattern_->resourceMgr_, nullptr);
    pattern_->resourceMgr_->ReloadResources();
    ASSERT_TRUE(target->GetBackBlurStyle().has_value());
    EXPECT_EQ(target->GetBackBlurStyle()->inactiveColor, resData);
    CreateDone();
    ResetMockResourceData();
}
} // namespace OHOS::Ace::NG