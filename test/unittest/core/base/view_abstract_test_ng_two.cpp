/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "base/geometry/calc_dimension_rect.h"
#include "base/geometry/response_region.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: OpenMenuTest001
 * @tc.desc: Test OpenMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, OpenMenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ASSERT_NE(rootNode, nullptr);
    auto selectNode = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    ASSERT_NE(selectNode, nullptr);
    auto menuNode =
        FrameNode::CreateFrameNode(V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, "Text", MenuType::MENU));
    ASSERT_NE(menuNode, nullptr);
    menuNode->MountToParent(selectNode);
    selectNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    ViewStackProcessor::GetInstance()->Push(menuNode);
    menuNode->onMainTree_ = true;
    menuNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    MenuParam menuParam;
    menuParam.isShowInSubWindow = true;

    /**
     * @tc.steps: step2. execute OpenMenu that isShowInSubWindow is true
     * @tc.expected: result as expected
     */
    int32_t targetId = menuNode->GetId();
    auto result = ViewAbstract::OpenMenu(menuParam, selectNode, targetId);
    EXPECT_EQ(result, ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: BindMenuTest001
 * @tc.desc: Test the BindMenuWithItems and BindMenuWithCustomNode
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, BindMenuTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create rootNode, then build some necessary params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->overlayManager_;
    ASSERT_NE(overlayManager, nullptr);
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    ViewStackProcessor::GetInstance()->Push(rootNode);
    ASSERT_NE(SubwindowManager::GetInstance(), nullptr);
    std::function<void()> buildFunc = nullptr;
    std::function<void()> previewBuildFunc = nullptr;
    auto themeManager = AceType::DynamicCast<MockThemeManager>(pipelineContext->GetThemeManager());
    ASSERT_NE(themeManager, nullptr);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    ASSERT_NE(selectTheme, nullptr);
    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));

    MenuParam menuParam;
    menuParam.isShowInSubWindow = true;
    menuParam.type = MenuType::MENU;
    std::vector<OptionParam> params;
    params.push_back(OptionParam());

    /**
     * @tc.steps: step2. execute BindMenuWithItems and BindMenuWithCustomNode
     * @tc.expected: result as expected
     */
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> targetNode =
        FrameNode::CreateFrameNode("targetNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(targetNode, nullptr);
    ViewAbstract::BindMenuWithItems(std::move(params), targetNode, OFFSETF, menuParam);
    ViewAbstract::BindMenuWithCustomNode(
        std::move(buildFunc), targetNode, OFFSETF, menuParam, std::move(previewBuildFunc));
    ASSERT_NE(targetNode->GetOrCreateGestureEventHub(), nullptr);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isShow, false);
}

/**
 * @tc.name: SetResponseRegionListWithMap001
 * @tc.desc: Test SetResponseRegionList and GetResponseRegionList
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetResponseRegionListWithMap001, TestSize.Level1)
{
    std::vector<ResponseRegion> regionNotRect;
    ViewAbstract::SetResponseRegionList(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(regionNotRect));
    auto regionMapResult = ViewAbstract::GetResponseRegionList(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_EQ(regionMapResult.size(), 1);

    std::unordered_map<ResponseRegionSupportedTool, std::vector<CalcDimensionRect>> regionMap;
    auto toolType = NG::ResponseRegionSupportedTool::ALL;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimensionRect dimenRect(widthDimen, heightDimen, xDimen, yDimen);
    regionMap[toolType].push_back(dimenRect);

    ViewAbstract::SetResponseRegionList(AceType::RawPtr(FRAME_NODE_REGISTER), std::move(regionMap));
    auto regionMapResult2 = ViewAbstract::GetResponseRegionList(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_EQ(regionMapResult2.size(), 1);

    auto region = regionMapResult[toolType][0];
    EXPECT_EQ(region.GetX().Value(), xDimen.Value());
    EXPECT_EQ(region.GetY().Value(), yDimen.Value());
    EXPECT_EQ(region.GetWidth().Value(), widthDimen.Value());
    EXPECT_EQ(region.GetHeight().Value(), heightDimen.Value());
}

/**
 * @tc.name: GetCommonLayoutTest001
 * @tc.desc: Test GetChainWeight of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetChainWeightTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(ViewAbstract::GetLayoutGravity(frameNode), Alignment::CENTER);
    EXPECT_EQ(ViewAbstract::GetRenderStrategy(frameNode), RenderStrategy::FAST);

    NG::ChainWeightPair chainWeightPair(2.0f, 5.0f);
    ViewAbstract::SetChainWeight(frameNode, chainWeightPair);
    EXPECT_EQ(ViewAbstract::GetChainWeight(frameNode), chainWeightPair);

    ViewAbstract::SetLayoutGravity(frameNode, Alignment::TOP_LEFT);
    EXPECT_EQ(ViewAbstract::GetLayoutGravity(frameNode), Alignment::TOP_LEFT);

    ViewAbstract::SetRenderStrategy(frameNode, RenderStrategy::OFFSCREEN);
    EXPECT_EQ(ViewAbstract::GetRenderStrategy(frameNode), RenderStrategy::OFFSCREEN);
}

/**
 * @tc.name: GetDashParamsTest001
 * @tc.desc: Test BorderDashParams of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetDashParamsTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ViewAbstract::SetDashGap(frameNode, Dimension(2));
    ViewAbstract::SetDashWidth(frameNode, Dimension(5));

    EXPECT_EQ(ViewAbstract::GetDashGap(frameNode).rightDimen, Dimension(2));
    EXPECT_EQ(ViewAbstract::GetDashWidth(frameNode).rightDimen, Dimension(5));
}
} // namespace OHOS::Ace::NG