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

#include "base/geometry/calc_dimension.h"
#include "base/geometry/calc_dimension_rect.h"
#include "base/geometry/dimension_offset.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/response_region.h"
#include "base/image/image_resizable_slice.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/event/focus_box.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

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
    ViewStackProcessor::GetInstance()->Push(menuNode);
    MenuParam menuParam;
    menuParam.isShowInSubWindow = true;

    /**
     * @tc.steps: step2. execute OpenMenu that isShowInSubWindow is true
     * @tc.expected: result as expected
     */
    int32_t targetId = menuNode->GetId();
    auto result = ViewAbstract::OpenMenu(menuParam, selectNode, targetId);
    EXPECT_EQ(result, ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE);
    ViewStackProcessor::GetInstance()->ClearStack();
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

/**
 * @tc.name: GetChainStyleTest001
 * @tc.desc: Test GetChainStyle of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetChainStyleTest001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;

    ViewAbstract::SetChainStyle(frameNode, chainInfo);

    EXPECT_EQ(ViewAbstract::GetChainStyle(frameNode).direction, LineDirection::HORIZONTAL);
    EXPECT_EQ(ViewAbstract::GetChainStyle(frameNode).style, ChainStyle::SPREAD);
}

/**
 * @tc.name: GetBackgroundColor
 * @tc.desc: Test GetBackgroundColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTestNg0106, TestSize.Level1)
{
    Color color = Color::TRANSPARENT;
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    const RefPtr<FrameNode> backgroundNode =
        FrameNode::CreateFrameNode("backgroundNode", nodeId, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(backgroundNode, nullptr);
    Color result = ViewAbstract::GetBackgroundColor(AceType::RawPtr(backgroundNode));
    EXPECT_EQ(result, color);
}

/**
 * @tc.name: ViewAbstractLpxResponseRegionList001
 * @tc.desc: Test response region list APIs register and unregister LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxResponseRegionList001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();

    CalcDimension lpxDim(10.0, DimensionUnit::LPX);
    CalcDimension vpDim(10.0, DimensionUnit::VP);
    std::unordered_map<ResponseRegionSupportedTool, std::vector<CalcDimensionRect>> lpxRegionMap;
    lpxRegionMap[ResponseRegionSupportedTool::ALL].emplace_back(lpxDim, lpxDim, lpxDim, lpxDim);

    ViewAbstract::SetResponseRegionList(lpxRegionMap, true);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_WIDTH), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_HEIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_X), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_Y), 1);

    std::unordered_map<ResponseRegionSupportedTool, std::vector<CalcDimensionRect>> vpRegionMap;
    vpRegionMap[ResponseRegionSupportedTool::ALL].emplace_back(vpDim, vpDim, vpDim, vpDim);
    ViewAbstract::SetResponseRegionList(vpRegionMap, true);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_WIDTH), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_HEIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_X), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_Y), 0);

    std::vector<ResponseRegion> lpxRegions = {
        ResponseRegion(ResponseRegionSupportedTool::ALL, lpxDim, lpxDim, lpxDim, lpxDim) };
    ViewAbstract::SetResponseRegionList(frameNode, lpxRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_WIDTH), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_HEIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_X), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_Y), 1);

    std::vector<ResponseRegion> vpRegions = {
        ResponseRegion(ResponseRegionSupportedTool::ALL, vpDim, vpDim, vpDim, vpDim) };
    ViewAbstract::SetResponseRegionList(frameNode, vpRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_WIDTH), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_HEIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_X), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_LIST_Y), 0);
}

/**
 * @tc.name: ViewAbstractLpxResponseRegion001
 * @tc.desc: Test response region APIs register and unregister LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxResponseRegion001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);
    std::vector<DimensionRect> lpxRegions = {
        DimensionRect(lpxDim, lpxDim, DimensionOffset(lpxDim, lpxDim)) };

    ViewAbstract::SetResponseRegion(lpxRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_WIDTH), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_HEIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_X), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_Y), 1);

    std::vector<DimensionRect> vpRegions = {
        DimensionRect(vpDim, vpDim, DimensionOffset(vpDim, vpDim)) };
    ViewAbstract::SetResponseRegion(vpRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_WIDTH), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_HEIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_X), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_Y), 0);

    ViewAbstract::SetResponseRegion(frameNode, lpxRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_WIDTH), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_HEIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_X), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_Y), 1);

    ViewAbstract::SetResponseRegion(frameNode, vpRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_WIDTH), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_HEIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_X), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_RESPONSE_REGION_Y), 0);
}

/**
 * @tc.name: ViewAbstractLpxMouseResponseRegion001
 * @tc.desc: Test mouse response region APIs register and unregister LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxMouseResponseRegion001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);
    std::vector<DimensionRect> lpxRegions = {
        DimensionRect(lpxDim, lpxDim, DimensionOffset(lpxDim, lpxDim)) };
    std::vector<DimensionRect> vpRegions = {
        DimensionRect(vpDim, vpDim, DimensionOffset(vpDim, vpDim)) };

    ViewAbstract::SetMouseResponseRegion(lpxRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_WIDTH), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_HEIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_X), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_Y), 1);

    ViewAbstract::SetMouseResponseRegion(vpRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_WIDTH), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_HEIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_X), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_Y), 0);

    ViewAbstract::SetMouseResponseRegion(frameNode, lpxRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_WIDTH), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_HEIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_X), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_Y), 1);

    ViewAbstract::SetMouseResponseRegion(frameNode, vpRegions);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_WIDTH), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_HEIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_X), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_MOUSE_RESPONSE_REGION_Y), 0);
}

/**
 * @tc.name: ViewAbstractLpxFocusBoxStyle001
 * @tc.desc: Test focus box style APIs register and unregister LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxFocusBoxStyle001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();

    FocusBoxStyle lpxStyle;
    lpxStyle.strokeWidth = Dimension(10.0, DimensionUnit::LPX);
    lpxStyle.margin = Dimension(10.0, DimensionUnit::LPX);
    ViewAbstract::SetFocusBoxStyle(lpxStyle);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_STROKE), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_MARGIN), 1);

    FocusBoxStyle vpStyle;
    vpStyle.strokeWidth = Dimension(10.0, DimensionUnit::VP);
    vpStyle.margin = Dimension(10.0, DimensionUnit::VP);
    ViewAbstract::SetFocusBoxStyle(vpStyle);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_STROKE), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_MARGIN), 0);

    ViewAbstract::SetFocusBoxStyle(frameNode, lpxStyle, false);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_STROKE), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_MARGIN), 1);

    ViewAbstract::SetFocusBoxStyle(frameNode, vpStyle, false);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_STROKE), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_FOCUS_BOX_MARGIN), 0);
}

/**
 * @tc.name: ViewAbstractLpxBackgroundImageResizableSlice001
 * @tc.desc: Test background image resizable slice APIs register and unregister LPX attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxBackgroundImageResizableSlice001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);
    ImageResizableSlice lpxSlice { lpxDim, lpxDim, lpxDim, lpxDim };
    ViewAbstract::SetBackgroundImageResizableSlice(lpxSlice);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_LEFT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_RIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_TOP), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_BOTTOM), 1);

    ImageResizableSlice vpSlice { vpDim, vpDim, vpDim, vpDim };
    ViewAbstract::SetBackgroundImageResizableSlice(vpSlice);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_LEFT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_RIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_TOP), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_BOTTOM), 0);

    ViewAbstract::SetBackgroundImageResizableSlice(frameNode, lpxSlice, false);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_LEFT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_RIGHT), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_TOP), 1);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_BOTTOM), 1);

    ViewAbstract::SetBackgroundImageResizableSlice(frameNode, vpSlice, false);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_LEFT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_RIGHT), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_TOP), 0);
    EXPECT_EQ(frameNode->lpxAttributes_.count(LpxAttribute::LPX_BORDER_IMAGE_BOTTOM), 0);
}
} // namespace OHOS::Ace::NG