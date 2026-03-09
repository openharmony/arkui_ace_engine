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
#include "test/unittest/core/manager/safe_area_manager_test_ng.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: SafeAreaToPaddingTest1
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest1, TestSize.Level1)
{
    /**
     * @tc.steps: Call SafeAreaToPadding with different ignoreSafeArea_, isFullScreen_, isNeedAvoidWindow_.
     * @tc.expected: SafeAreaToPadding returns empty.
     */
    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest2
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest2, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest3
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest3, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * not valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest4
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest4, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and not valid navArea cutoutArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.left, SYSTEM_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - SYSTEM_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, SYSTEM_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - SYSTEM_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.left, SYSTEM_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - SYSTEM_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, SYSTEM_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - SYSTEM_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest5
 * @tc.desc: Test SafeAreaToPadding with default parameter false.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest5, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and cutoutArea and not valid navArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty or non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, CUTOUT_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - CUTOUT_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, CUTOUT_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - CUTOUT_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();

    EXPECT_EQ(paddingProperty.left, CUTOUT_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - CUTOUT_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, CUTOUT_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - CUTOUT_BOTTOM_START);

    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);

    safeAreaManager_->SetIgnoreSafeArea(true);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);
    paddingProperty = safeAreaManager_->SafeAreaToPadding();
    EXPECT_EQ(paddingProperty.Empty(), true);
}

/**
 * @tc.name: SafeAreaToPaddingTest6
 * @tc.desc: Test SafeAreaToPadding with parameter true.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest6, TestSize.Level1)
{
    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     *  valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding(true);

    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * not valid safeAreaInsets before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemAreaNotValid);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true);
    EXPECT_EQ(paddingProperty.Empty(), true);

    /**
     * @tc.steps: Call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and not valid navArea cutoutArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutAreaNotValid);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true);

    EXPECT_EQ(paddingProperty.left, SYSTEM_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.top, SYSTEM_RIGHT_END - SYSTEM_RIGHT_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - SYSTEM_BOTTOM_START);

    /**
     * @tc.steps: step4 call UpdateSystemSafeArea, UpdateNavSafeArea, UpdateCutoutSafeArea with
     * valid systemArea and cutoutArea and not valid navArea before calling SafeAreaToPadding.
     * @tc.expected: SafeAreaToPadding returns non-empty.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navAreaNotValid);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true);

    EXPECT_EQ(paddingProperty.left, CUTOUT_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - CUTOUT_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, CUTOUT_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - CUTOUT_BOTTOM_START);
}

/**
 * @tc.name: SafeAreaToPaddingTest7
 * @tc.desc: Test SafeAreaToPadding with LayoutSafeAreaType.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest7, TestSize.Level1)
{
    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(false);
    safeAreaManager_->SetIsNeedAvoidWindow(true);

    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, KEYBOARD_HEIGHT);

    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_ALL);
    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, KEYBOARD_HEIGHT);

    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    float offset = -KEYBOARD_HEIGHT;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, std::nullopt);

    offset = -KEYBOARD_HEIGHT / 2.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_ALL);
    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);
}

/**
 * @tc.name: NeedExpandNodeListTest
 * @tc.desc: Build an UI tree and start layouting from the root
 * and test if set of nodes are added in the list correctly.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, NeedExpandNodeListTest, TestSize.Level1)
{
    // create nodes
    auto frameNode0 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 0, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);
    auto frameNode1 = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 1, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto frameNode2 = FrameNode::CreateFrameNode(V2::FLEX_ETS_TAG, 2, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto frameNode3 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    frameNode1->MountToParent(frameNode0);
    frameNode2->MountToParent(frameNode1);
    frameNode3->MountToParent(frameNode2);

    // make sure nodes mount correctly
    EXPECT_EQ(frameNode1->GetParent()->GetTag(), V2::PAGE_ETS_TAG);
    EXPECT_EQ(frameNode2->GetParent()->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(frameNode3->GetParent()->GetTag(), V2::FLEX_ETS_TAG);
    SafeAreaExpandOpts opts = { .type = SAFE_AREA_TYPE_SYSTEM, .edges = SAFE_AREA_EDGE_TOP };
    auto columnLayoutProperty = frameNode1->GetLayoutProperty();
    EXPECT_NE(columnLayoutProperty, nullptr);
    columnLayoutProperty->UpdateSafeAreaExpandOpts(opts);
    auto flexLayoutProperty = frameNode2->GetLayoutProperty();
    EXPECT_NE(flexLayoutProperty, nullptr);
    flexLayoutProperty->UpdateSafeAreaExpandOpts(opts);
    auto rowLayoutProperty = frameNode3->GetLayoutProperty();
    EXPECT_NE(rowLayoutProperty, nullptr);
    rowLayoutProperty->UpdateSafeAreaExpandOpts(opts);
    // page start to measure
    frameNode0->SetLayoutDirtyMarked(true);
    frameNode0->CreateLayoutTask();
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_NE(pipeline, nullptr);
    auto manager = pipeline->GetSafeAreaManager();
    EXPECT_NE(manager, nullptr);
    auto nodeSet = manager->GetExpandNodeSet();
    // page should not be added
    EXPECT_EQ(nodeSet.size(), 3);
    auto iter = nodeSet.begin();
    EXPECT_NE(iter, nodeSet.end());
    auto nodeIter = (*iter).Upgrade();
    EXPECT_NE(nodeIter, nullptr);
    EXPECT_EQ(nodeIter->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(nodeIter->GetId(), 1);
    iter++;
    EXPECT_NE(iter, nodeSet.end());
    nodeIter = (*iter).Upgrade();
    EXPECT_NE(nodeIter, nullptr);
    EXPECT_EQ(nodeIter->GetTag(), V2::FLEX_ETS_TAG);
    EXPECT_EQ(nodeIter->GetId(), 2);
    iter++;
    EXPECT_NE(iter, nodeSet.end());
    nodeIter = (*iter).Upgrade();
    EXPECT_NE(nodeIter, nullptr);
    EXPECT_EQ(nodeIter->GetTag(), V2::ROW_ETS_TAG);
    EXPECT_EQ(nodeIter->GetId(), 3);
}

/**
 * @tc.name: AddNodeToExpandListIfNeededTest
 * @tc.desc: test functionality of AddNodeToExpandListIfNeededTest interface
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, AddNodeToExpandListIfNeededTest, TestSize.Level1)
{
    auto frameNode0 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 0, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);
    auto frameNode1 =
        FrameNode::CreateFrameNode(V2::NAVIGATION_VIEW_ETS_TAG, 1, AceType::MakeRefPtr<NavigationPattern>(), false);
    auto frameNode2 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 2, AceType::MakeRefPtr<NavDestinationPattern>(), true);
    auto frameNode3 = FrameNode::CreateFrameNode(
        V2::NAVDESTINATION_CONTENT_ETS_TAG, 3, AceType::MakeRefPtr<LinearLayoutPattern>(true), false);
    auto frameNode4 = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 4, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), true);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), true);

    // repeat add should not work
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode0), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode1), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode2), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode3), false);
    EXPECT_EQ(safeAreaManager_->AddNodeToExpandListIfNeeded(frameNode4), false);
    EXPECT_EQ(safeAreaManager_->GetExpandNodeSet().size(), 5);
    safeAreaManager_->ClearNeedExpandNode();
    EXPECT_EQ(safeAreaManager_->GetExpandNodeSet().size(), 0);
}

/**
 * @tc.name: IsModeResizeOrIsModeOffset
 * @tc.desc: Test IsModeResize and IsModeOffset
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, IsModeResizeOrIsModeOffset, TestSize.Level1)
{
    std::vector<KeyBoardAvoidMode> modeArr = { KeyBoardAvoidMode::OFFSET, KeyBoardAvoidMode::RESIZE,
        KeyBoardAvoidMode::OFFSET_WITH_CARET, KeyBoardAvoidMode::RESIZE_WITH_CARET, KeyBoardAvoidMode::NONE };

    std::vector<std::pair<bool, bool>> expectedRes = { { true, false }, { false, true }, { true, false },
        { false, true }, { false, false } };

    for (int i = 0; i < modeArr.size(); ++i) {
        safeAreaManager_->SetKeyBoardAvoidMode(modeArr[i]);
        EXPECT_EQ(safeAreaManager_->IsModeOffset(), expectedRes[i].first);
        EXPECT_EQ(safeAreaManager_->IsModeResize(), expectedRes[i].second);
    }
}

/**
 * @tc.name: GetKeyboardWebInset
 * @tc.desc: test functionality of GetKeyboardWebInset interface
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetKeyboardWebInset, TestSize.Level1)
{
    SafeAreaInsets::Inset inset;
    safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::NONE;
    auto keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, inset.start);
    EXPECT_EQ(keyboardInset.end, inset.end);
    safeAreaManager_->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    keyboardInset = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(keyboardInset.start, safeAreaManager_->keyboardWebInset_.start);
    EXPECT_EQ(keyboardInset.end, safeAreaManager_->keyboardWebInset_.end);
}

/**
 * @tc.name: SetAndGetKeyboardInsetImplTest
 * @tc.desc: test Set And GetKeyboardInsetImplTest interface
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SetAndGetKeyboardInsetImplTest, TestSize.Level1)
{
    safeAreaManager_->SetKeyboardInsetImpl([](SafeAreaManager* manager) { return manager->GetKeyboardWebInset(); });
    EXPECT_NE(safeAreaManager_->getKeyboardInset, nullptr);
    auto ret = safeAreaManager_->GetKeyboardInsetImpl();
    auto compare = safeAreaManager_->GetKeyboardWebInset();
    EXPECT_EQ(ret, compare);
    safeAreaManager_->SetKeyboardInsetImpl(std::function<SafeAreaInsets::Inset(SafeAreaManager*)>());
    EXPECT_EQ(safeAreaManager_->getKeyboardInset, nullptr);
    ret = safeAreaManager_->GetKeyboardInsetImpl();
    compare = safeAreaManager_->GetKeyboardInset();
    EXPECT_EQ(ret, compare);
}

/**
 * @tc.name: KeyboardInfoTest
 * @tc.desc: Test SetKeyboardInfo, GetKeyboardOrientation and GetRawKeyboardHeight
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardInfoTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Set keyboard info and verify orientation and height.
     */
    MockContainer::SetUp();
    float height = 256.0f;
    safeAreaManager_->SetKeyboardInfo(height);
    EXPECT_EQ(safeAreaManager_->GetRawKeyboardHeight(), height);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOrientation(), static_cast<int32_t>(Rotation::ROTATION_0));

    /**
     * @tc.steps: step2 Set raw keyboard height directly and verify.
     */
    height = 320.0f;
    safeAreaManager_->SetRawKeyboardHeight(height);
    EXPECT_EQ(safeAreaManager_->GetRawKeyboardHeight(), height);
    MockContainer::TearDown();
}

/**
 * @tc.name: KeyboardSafeAreaEnabledTest
 * @tc.desc: Test KeyboardSafeAreaEnabled with different modes.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardSafeAreaEnabledTest, TestSize.Level1)
{
    std::vector<KeyBoardAvoidMode> modeArr = { KeyBoardAvoidMode::OFFSET, KeyBoardAvoidMode::RESIZE,
        KeyBoardAvoidMode::OFFSET_WITH_CARET, KeyBoardAvoidMode::RESIZE_WITH_CARET, KeyBoardAvoidMode::NONE };

    std::vector<bool> expectedRes = {
        false, // OFFSET - disabled
        true,  // RESIZE - enabled
        false, // OFFSET_WITH_CARET - disabled
        true,  // RESIZE_WITH_CARET - enabled
        false  // NONE - disabled
    };

    for (size_t i = 0; i < modeArr.size(); ++i) {
        safeAreaManager_->SetKeyBoardAvoidMode(modeArr[i]);
        EXPECT_EQ(safeAreaManager_->KeyboardSafeAreaEnabled(), expectedRes[i]);
    }
}

/**
 * @tc.name: GetSafeAreaCurveTest
 * @tc.desc: Test GetSafeAreaCurve returns non-null curve.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetSafeAreaCurveTest, TestSize.Level1)
{
    auto curve = safeAreaManager_->GetSafeAreaCurve();
    EXPECT_NE(curve, nullptr);
}

/**
 * @tc.name: RemoveRestoreNodeTest
 * @tc.desc: Test RemoveRestoreNode functionality.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, RemoveRestoreNodeTest, TestSize.Level1)
{
    auto frameNode0 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 0, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);
    auto frameNode1 = FrameNode::CreateFrameNode(
        V2::PAGE_ETS_TAG, 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()), true);

    /**
     * @tc.steps: step1 Add nodes and verify they are in the set.
     */
    safeAreaManager_->AddGeoRestoreNode(frameNode0);
    safeAreaManager_->AddGeoRestoreNode(frameNode1);
    EXPECT_EQ(safeAreaManager_->GetGeoRestoreNodes().size(), 2);

    /**
     * @tc.steps: step2 Remove one node and verify set size.
     */
    safeAreaManager_->RemoveRestoreNode(frameNode0);
    EXPECT_EQ(safeAreaManager_->GetGeoRestoreNodes().size(), 1);

    /**
     * @tc.steps: step3 Remove all nodes and verify set is empty.
     */
    safeAreaManager_->RemoveRestoreNode(frameNode1);
    EXPECT_EQ(safeAreaManager_->GetGeoRestoreNodes().size(), 0);
}

/**
 * @tc.name: KeyboardHeightConsideringUIExtensionTest
 * @tc.desc: Test SetkeyboardHeightConsideringUIExtension and GetkeyboardHeightConsideringUIExtension.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardHeightConsideringUIExtensionTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Get initial keyboard height and set new height.
     */
    uint32_t initialHeight = safeAreaManager_->GetkeyboardHeightConsideringUIExtension();
    EXPECT_EQ(initialHeight, 0);

    uint32_t newHeight = 256;
    safeAreaManager_->SetkeyboardHeightConsideringUIExtension(newHeight);
    EXPECT_EQ(safeAreaManager_->GetkeyboardHeightConsideringUIExtension(), newHeight);

    /**
     * @tc.steps: step2 Set same height again and verify no callback triggered.
     */
    safeAreaManager_->SetkeyboardHeightConsideringUIExtension(newHeight);
    EXPECT_EQ(safeAreaManager_->GetkeyboardHeightConsideringUIExtension(), newHeight);
}

/**
 * @tc.name: KeyboardChangeCallbackConsideringUIExtTest
 * @tc.desc: Test AddKeyboardChangeCallbackConsideringUIExt and RemoveKeyboardChangeCallbackConsideringUIExt.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardChangeCallbackConsideringUIExtTest, TestSize.Level1)
{
    int32_t callbackCount = 0;
    int32_t nodeId = 1;

    auto callback = [&callbackCount]() { callbackCount++; };

    /**
     * @tc.steps: step1 Add callback and set keyboard height to trigger callback.
     */
    safeAreaManager_->AddKeyboardChangeCallbackConsideringUIExt(nodeId, callback);
    safeAreaManager_->SetkeyboardHeightConsideringUIExtension(256);
    EXPECT_EQ(callbackCount, 1);

    /**
     * @tc.steps: step2 Set same height again and verify callback not triggered.
     */
    safeAreaManager_->SetkeyboardHeightConsideringUIExtension(256);
    EXPECT_EQ(callbackCount, 1);

    /**
     * @tc.steps: step3 Remove callback and verify no more callbacks.
     */
    safeAreaManager_->RemoveKeyboardChangeCallbackConsideringUIExt(nodeId);
    safeAreaManager_->SetkeyboardHeightConsideringUIExtension(320);
    EXPECT_EQ(callbackCount, 1);
}

/**
 * @tc.name: GetNavSafeAreaTest
 * @tc.desc: Test GetNavSafeArea returns correct nav area.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetNavSafeAreaTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Update nav area and verify GetNavSafeArea.
     */
    auto ret = safeAreaManager_->UpdateNavSafeArea(navArea);
    EXPECT_EQ(ret, true);

    auto navSafeArea = safeAreaManager_->GetNavSafeArea();
    CommonExpectEQ(
        Rect { navSafeArea.left_.start, navSafeArea.right_.end, navSafeArea.top_.start, navSafeArea.bottom_.end },
        Rect { NAV_LEFT_START, NAV_RIGHT_END, NAV_TOP_START, NAV_BOTTOM_END });

    /**
     * @tc.steps: step2 Update same nav area again and verify.
     */
    ret = safeAreaManager_->UpdateNavSafeArea(navArea);
    EXPECT_EQ(ret, false);

    navSafeArea = safeAreaManager_->GetNavSafeArea();
    CommonExpectEQ(
        Rect { navSafeArea.left_.start, navSafeArea.right_.end, navSafeArea.top_.start, navSafeArea.bottom_.end },
        Rect { NAV_LEFT_START, NAV_RIGHT_END, NAV_TOP_START, NAV_BOTTOM_END });
}

/**
 * @tc.name: GetCutoutSafeAreaWithoutProcessTest
 * @tc.desc: Test GetCutoutSafeAreaWithoutProcess with SCB window type.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetCutoutSafeAreaWithoutProcessTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Update cutout area and verify with app window type.
     */
    safeAreaManager_->SetWindowTypeConfig(true, false, false);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    auto cutoutSafeArea = safeAreaManager_->GetCutoutSafeAreaWithoutProcess();
    EXPECT_EQ(cutoutSafeArea, cutoutAreaWithRoot);

    /**
     * @tc.steps: step2 Set window type to SCB and update SCB cutout area.
     */
    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    safeAreaManager_->UpdateScbCutoutSafeArea(cutoutArea);
    cutoutSafeArea = safeAreaManager_->GetCutoutSafeAreaWithoutProcess();
    EXPECT_EQ(cutoutSafeArea, cutoutAreaWithRoot);
}

/**
 * @tc.name: GetSafeAreaWithoutProcessTest
 * @tc.desc: Test GetSafeAreaWithoutProcess with different window types.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetSafeAreaWithoutProcessTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Update areas with app window type and verify GetSafeAreaWithoutProcess.
     */
    safeAreaManager_->SetWindowTypeConfig(true, false, false);
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);
    auto safeArea = safeAreaManager_->GetSafeAreaWithoutProcess();
    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT });

    /**
     * @tc.steps: step2 Set window type to SCB and update SCB areas.
     */
    safeAreaManager_->SetWindowTypeConfig(false, false, true);
    safeAreaManager_->UpdateScbSystemSafeArea(systemArea);
    safeAreaManager_->UpdateScbNavSafeArea(navArea);
    safeAreaManager_->UpdateScbCutoutSafeArea(cutoutArea);
    safeArea = safeAreaManager_->GetSafeAreaWithoutProcess();
    CommonExpectEQ(Rect { safeArea.left_.start, safeArea.right_.end, safeArea.top_.start, safeArea.bottom_.end },
        Rect { 0.0f, DISPLAY_WIDTH, 0.0f, DISPLAY_HEIGHT });
}

/**
 * @tc.name: GetKeyboardInsetWithoutProcessTest
 * @tc.desc: Test GetKeyboardInsetWithoutProcess returns raw keyboard inset regardless of mode.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetKeyboardInsetWithoutProcessTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Update keyboard safe area and set mode to NONE.
     */
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::NONE);
    auto keyboardInset = safeAreaManager_->GetKeyboardInsetWithoutProcess();
    EXPECT_EQ(keyboardInset.start, DISPLAY_HEIGHT - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, DISPLAY_HEIGHT);

    /**
     * @tc.steps: step2 Set mode to OFFSET and verify inset still returned.
     */
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    keyboardInset = safeAreaManager_->GetKeyboardInsetWithoutProcess();
    EXPECT_EQ(keyboardInset.start, DISPLAY_HEIGHT - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, DISPLAY_HEIGHT);

    /**
     * @tc.steps: step3 Set mode to RESIZE and verify inset still returned.
     */
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE);
    keyboardInset = safeAreaManager_->GetKeyboardInsetWithoutProcess();
    EXPECT_EQ(keyboardInset.start, DISPLAY_HEIGHT - KEYBOARD_HEIGHT);
    EXPECT_EQ(keyboardInset.end, DISPLAY_HEIGHT);
}

/**
 * @tc.name: SafeAreaToPaddingTest8
 * @tc.desc: Test SafeAreaToPadding with OFFSET_WITH_CARET and RESIZE_WITH_CARET modes.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, SafeAreaToPaddingTest8, TestSize.Level1)
{
    safeAreaManager_->SetIgnoreSafeArea(false);
    safeAreaManager_->SetIsFullScreen(true);
    safeAreaManager_->SetIsNeedAvoidWindow(false);
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    safeAreaManager_->UpdateNavSafeArea(navArea);
    safeAreaManager_->UpdateCutoutSafeArea(cutoutArea);

    /**
     * @tc.steps: step1 Test with OFFSET_WITH_CARET mode.
     */
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET_WITH_CARET);
    safeAreaManager_->UpdateKeyboardSafeArea(KEYBOARD_HEIGHT);
    float offset = -KEYBOARD_HEIGHT;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    PaddingPropertyF paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, std::nullopt);

    offset = -KEYBOARD_HEIGHT / 2.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, SYSTEM_BOTTOM_END - NAV_BOTTOM_START);

    /**
     * @tc.steps: step2 Test with RESIZE_WITH_CARET mode.
     */
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::RESIZE_WITH_CARET);
    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_KEYBOARD);
    EXPECT_EQ(paddingProperty.left, std::nullopt);
    EXPECT_EQ(paddingProperty.right, std::nullopt);
    EXPECT_EQ(paddingProperty.top, std::nullopt);
    EXPECT_EQ(paddingProperty.bottom, KEYBOARD_HEIGHT);

    paddingProperty = safeAreaManager_->SafeAreaToPadding(true, LAYOUT_SAFE_AREA_TYPE_ALL);
    EXPECT_EQ(paddingProperty.left, NAV_LEFT_END - SYSTEM_LEFT_START);
    EXPECT_EQ(paddingProperty.right, SYSTEM_RIGHT_END - NAV_RIGHT_START);
    EXPECT_EQ(paddingProperty.top, NAV_TOP_END - SYSTEM_TOP_START);
    EXPECT_EQ(paddingProperty.bottom, KEYBOARD_HEIGHT);
}

/**
 * @tc.name: GetWindowWrapperOffsetTest2
 * @tc.desc: Test GetWindowWrapperOffset with null windowManager.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetWindowWrapperOffsetTest2, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSafeAreaManager();

    /**
     * @tc.steps: step1 Test with CONTAINER_MODAL and null windowManager (expected to return OffsetF()).
     */
    pipeline->SetWindowModal(WindowModal::CONTAINER_MODAL);
    auto ret = manager->GetWindowWrapperOffset();
    EXPECT_EQ(ret, OffsetF());

    /**
     * @tc.steps: step2 Test with FULLSCREEN mode.
     */
    auto windowModeCallback = []() { return WindowMode::WINDOW_MODE_FULLSCREEN; };
    pipeline->SetWindowModal(WindowModal::CONTAINER_MODAL);
    auto windowManager = pipeline->GetWindowManager();
    if (windowManager) {
        windowManager->SetWindowGetModeCallBack(std::move(windowModeCallback));
    }
    ret = manager->GetWindowWrapperOffset();
    EXPECT_EQ(ret, OffsetF());
}

/**
 * @tc.name: GetUseCutoutTest
 * @tc.desc: Test SetUseCutout and GetUseCutout.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetUseCutoutTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Verify initial useCutout value.
     */
    EXPECT_EQ(safeAreaManager_->GetUseCutout(), true); // Set to true in SetUp

    /**
     * @tc.steps: step2 Set useCutout to false and verify.
     */
    safeAreaManager_->SetUseCutout(false);
    EXPECT_EQ(safeAreaManager_->GetUseCutout(), false);

    /**
     * @tc.steps: step3 Set useCutout back to true and verify.
     */
    safeAreaManager_->SetUseCutout(true);
    EXPECT_EQ(safeAreaManager_->GetUseCutout(), true);
}

/**
 * @tc.name: GetWindowTypeConfigTest
 * @tc.desc: Test SetWindowTypeConfig and GetWindowTypeConfig.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, GetWindowTypeConfigTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Set window type config and verify.
     */
    safeAreaManager_->SetWindowTypeConfig(true, false, false);
    auto config = safeAreaManager_->GetWindowTypeConfig();
    EXPECT_EQ(config.isAppWindow, true);
    EXPECT_EQ(config.isSystemWindow, false);
    EXPECT_EQ(config.isSceneBoardWindow, false);

    /**
     * @tc.steps: step2 Set different config and verify.
     */
    safeAreaManager_->SetWindowTypeConfig(false, true, true);
    config = safeAreaManager_->GetWindowTypeConfig();
    EXPECT_EQ(config.isAppWindow, false);
    EXPECT_EQ(config.isSystemWindow, true);
    EXPECT_EQ(config.isSceneBoardWindow, true);
}

/**
 * @tc.name: CheckSystemSafeAreaTest2
 * @tc.desc: Test CheckSystemSafeArea returns correct boolean.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CheckSystemSafeAreaTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Update system area and check same area.
     */
    safeAreaManager_->UpdateSystemSafeArea(systemArea);
    auto ret = safeAreaManager_->CheckSystemSafeArea(systemArea);
    EXPECT_EQ(ret, false); // Same area, should return false

    /**
     * @tc.steps: step2 Check different area.
     */
    ret = safeAreaManager_->CheckSystemSafeArea(systemAreaNotValid);
    EXPECT_EQ(ret, true); // Different area, should return true
}

/**
 * @tc.name: CheckNavSafeAreaTest2
 * @tc.desc: Test CheckNavSafeArea returns correct boolean.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, CheckNavSafeAreaTest2, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Update nav area and check same area.
     */
    safeAreaManager_->UpdateNavSafeArea(navArea);
    auto ret = safeAreaManager_->CheckNavSafeArea(navArea);
    EXPECT_EQ(ret, false); // Same area, should return false

    /**
     * @tc.steps: step2 Check different area.
     */
    ret = safeAreaManager_->CheckNavSafeArea(navAreaNotValid);
    EXPECT_EQ(ret, true); // Different area, should return true
}

/**
 * @tc.name: KeyboardOffsetTest4
 * @tc.desc: Test GetKeyboardOffset behavior when mode is changed to/from NONE.
 * @tc.type: FUNC
 */
HWTEST_F(SafeAreaManagerTest, KeyboardOffsetTest4, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Set offset and change mode to NONE, verify offset is reset.
     */
    float offset = 200.0f;
    safeAreaManager_->UpdateKeyboardOffset(offset);
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::NONE);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOffset(), 0.0f);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOffset(true), 0.0f);

    /**
     * @tc.steps: step2 Change mode to OFFSET and verify offset behavior.
     */
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::OFFSET);
    safeAreaManager_->UpdateKeyboardOffset(offset);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOffset(), offset);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOffset(true), offset);

    /**
     * @tc.steps: step3 Change mode from OFFSET to NONE, verify offset is reset.
     */
    safeAreaManager_->SetKeyBoardAvoidMode(KeyBoardAvoidMode::NONE);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOffset(), 0.0f);
    EXPECT_EQ(safeAreaManager_->GetKeyboardOffset(true), 0.0f);
}
} // namespace OHOS::Ace::NG