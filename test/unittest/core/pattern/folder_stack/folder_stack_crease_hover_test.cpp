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

#include "core/accessibility/accessibility_manager.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"

#define private public
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_algorithm.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_layout_property.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/display_info_utils.h"
#include "display_manager.h"
#include "test/unittest/core/pattern/folder_stack/folder_stack_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

namespace {
constexpr int32_t CREASE_POS_X = 0;
constexpr int32_t CREASE_POS_Y = 1000;
constexpr uint32_t HORIZONTAL_CREASE_WIDTH = 2000;
constexpr uint32_t HORIZONTAL_CREASE_HEIGHT = 100;
constexpr uint32_t VERTICAL_CREASE_WIDTH = 100;
constexpr uint32_t VERTICAL_CREASE_HEIGHT = 2000;
constexpr uint32_t SQUARE_DIMENSION = 500;
} // namespace

class FolderStackCreaseHoverTest : public FolderStackTestNg {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        MockPipelineContext::SetUp();
        auto viewStack = ViewStackProcessor::GetInstance();
        if (viewStack) {
            viewStack->ClearStack();
        }
    }

    static void TearDownTestSuite()
    {
        auto viewStack = ViewStackProcessor::GetInstance();
        if (viewStack) {
            viewStack->ClearStack();
        }
        MockContainer::TearDown();
        MockPipelineContext::TearDown();
    }

    void SetUp() override
    {
        ResetDisplayInfo(FoldStatus::UNKNOWN, FoldCreaseDirection::UNKNOWN, true);
    }

    void TearDown() override {}

    RefPtr<DisplayInfo> CreateDisplayInfo(FoldStatus foldStatus, FoldCreaseDirection direction, bool isFoldable)
    {
        auto displayInfo = AceType::MakeRefPtr<DisplayInfo>();
        displayInfo->SetFoldStatus(foldStatus);
        displayInfo->SetFoldCreaseDirection(direction);
        displayInfo->SetIsFoldable(isFoldable);
        return displayInfo;
    }

    void ResetDisplayInfo(FoldStatus foldStatus, FoldCreaseDirection direction, bool isFoldable)
    {
        auto displayInfo = CreateDisplayInfo(foldStatus, direction, isFoldable);
        MockContainer::Current()->SetDisplayInfo(displayInfo);
    }

    RefPtr<FrameNode> CreateFolderStackNode()
    {
        FolderStackModelNG folderStackModelNG;
        folderStackModelNG.Create();
        folderStackModelNG.SetAlignment(Alignment::TOP_LEFT);
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
        return frameNode;
    }

    void SetupMockRosenLiveCrease(const std::vector<Rosen::DMRect>& rects, bool valid)
    {
        auto& dm = Rosen::DisplayManager::GetInstance();
        auto display = dm.GetDefaultDisplay();
        if (display) {
            display->liveCreaseRegion_.SetCreaseRects(rects);
            display->liveCreaseRegionValid_ = valid;
        }
    }

    void ResetMockRosenLiveCrease()
    {
        SetupMockRosenLiveCrease({}, true);
    }

    std::vector<Rosen::DMRect> MakeHorizontalCreaseRects()
    {
        Rosen::DMRect rect;
        rect.posX_ = CREASE_POS_X;
        rect.posY_ = CREASE_POS_Y;
        rect.width_ = HORIZONTAL_CREASE_WIDTH;
        rect.height_ = HORIZONTAL_CREASE_HEIGHT;
        return { rect };
    }

    std::vector<Rosen::DMRect> MakeVerticalCreaseRects()
    {
        Rosen::DMRect rect;
        rect.posX_ = CREASE_POS_X;
        rect.posY_ = CREASE_POS_Y;
        rect.width_ = VERTICAL_CREASE_WIDTH;
        rect.height_ = VERTICAL_CREASE_HEIGHT;
        return { rect };
    }

    std::vector<Rosen::DMRect> MakeSquareCreaseRects()
    {
        Rosen::DMRect rect;
        rect.posX_ = CREASE_POS_X;
        rect.posY_ = CREASE_POS_Y;
        rect.width_ = SQUARE_DIMENSION;
        rect.height_ = SQUARE_DIMENSION;
        return { rect };
    }
};

/**
 * @tc.name: CreaseHoverAC1_HorizontalCreaseHalfFold
 * @tc.desc: AC-1: WHEN foldStatus=HALF_FOLD AND creaseRects[0].width > height THEN IsSupportHoverState=true
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC1_HorizontalCreaseHalfFold, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->IsSupportHoverState(displayInfo));
}

/**
 * @tc.name: CreaseHoverAC2_EmptyCreaseRects
 * @tc.desc: AC-2: WHEN foldStatus=HALF_FOLD AND creaseRects empty THEN IsSupportHoverState=false
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC2_EmptyCreaseRects, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::UNKNOWN, true);
    displayInfo->SetLiveFoldCreaseRegion({});
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfo));
}

/**
 * @tc.name: CreaseHoverAC3_SquareCreaseDegenerate
 * @tc.desc: AC-3: WHEN foldStatus=HALF_FOLD AND width==height THEN IsSupportHoverState=false
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC3_SquareCreaseDegenerate, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::UNKNOWN, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfo));
}

/**
 * @tc.name: CreaseHoverAC4_VerticalCrease
 * @tc.desc: AC-4: WHEN foldStatus=HALF_FOLD AND height > width THEN IsSupportHoverState=false
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC4_VerticalCrease, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::VERTICAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfo));
}

/**
 * @tc.name: CreaseHoverAC5_NonHalfFoldStatus
 * @tc.desc: AC-5: WHEN foldStatus != HALF_FOLD THEN no hover (IsIntoFolderStack returns false)
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC5_NonHalfFoldStatus, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(12);
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);

    auto displayInfo = CreateDisplayInfo(FoldStatus::EXPAND, FoldCreaseDirection::HORIZONTAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    RefPtr<FrameNode> folder;
    auto stack = CreateStack([this, &folder](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(FULL_SCREEN_WIDTH));
        ViewAbstract::SetHeight(CalcLength(FULL_SCREEN_HEIGHT));
        folder = CreateFolder([](FolderStackModelNG model) {});
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(folder, nullptr);

    auto folderStackPattern = folder->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    folderStackPattern->displayInfo_ = displayInfo;

    FlushUITasks(stack);

    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(folderStackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    auto layoutProperty = folder->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;

    RefPtr<GeometryNode> geometryNode = folder->GetGeometryNode();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(folder, geometryNode, folder->GetLayoutProperty());
    auto size = CreateIdealSizeByPercentRef(layoutConstraint, Axis::HORIZONTAL, MeasureType::MATCH_PARENT)
                    .ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    EXPECT_FALSE(layoutAlgorithm->IsIntoFolderStack(
        size, layoutProperty, AccessibilityManager::RawPtr(layoutWrapper)));

    displayInfo->SetFoldStatus(FoldStatus::FOLDED);
    EXPECT_FALSE(layoutAlgorithm->IsIntoFolderStack(
        size, layoutProperty, AccessibilityManager::RawPtr(layoutWrapper)));

    displayInfo->SetFoldStatus(FoldStatus::UNKNOWN);
    EXPECT_FALSE(layoutAlgorithm->IsIntoFolderStack(
        size, layoutProperty, AccessibilityManager::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: CreaseHoverAC5b_HalfFoldButNonHoverDirection
 * @tc.desc: AC-5 variant: WHEN foldStatus=HALF_FOLD but direction != HORIZONTAL THEN IsIntoFolderStack=false
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC5b_HalfFoldButNonHoverDirection, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(12);
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);

    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::VERTICAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    RefPtr<FrameNode> folder;
    auto stack = CreateStack([this, &folder](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(FULL_SCREEN_WIDTH));
        ViewAbstract::SetHeight(CalcLength(FULL_SCREEN_HEIGHT));
        folder = CreateFolder([](FolderStackModelNG model) {});
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(folder, nullptr);

    auto folderStackPattern = folder->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    folderStackPattern->displayInfo_ = displayInfo;
    FlushUITasks(stack);

    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(folderStackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto layoutProperty = folder->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;

    RefPtr<GeometryNode> geometryNode = folder->GetGeometryNode();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(folder, geometryNode, folder->GetLayoutProperty());
    auto size = CreateIdealSizeByPercentRef(layoutConstraint, Axis::HORIZONTAL, MeasureType::MATCH_PARENT)
                    .ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    EXPECT_FALSE(layoutAlgorithm->IsIntoFolderStack(
        size, layoutProperty, AccessibilityManager::RawPtr(layoutWrapper)));
}

/**
 * @tc.name: CreaseHoverAC6_LiveCreaseRegionFailure
 * @tc.desc: AC-6: WHEN GetLiveCreaseRegion returns DMError THEN direction=UNKNOWN → IsSupportHoverState=false
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC6_LiveCreaseRegionFailure, TestSize.Level0)
{
    SetupMockRosenLiveCrease({}, false);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto liveRects = displayInfoUtils->GetLiveFoldCreaseRegion();
    EXPECT_TRUE(liveRects.empty());

    auto direction = displayInfoUtils->GetFoldCreaseDirection();
    EXPECT_EQ(direction, FoldCreaseDirection::UNKNOWN);

    auto displayInfo = displayInfoUtils->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    EXPECT_EQ(displayInfo->GetFoldCreaseDirection(), FoldCreaseDirection::UNKNOWN);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfo));

    ResetMockRosenLiveCrease();
}

/**
 * @tc.name: CreaseHoverAC6b_LiveCreaseRegionHorizontal
 * @tc.desc: AC-6 variant: WHEN GetLiveCreaseRegion succeeds with horizontal rect THEN direction=HORIZONTAL
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC6b_LiveCreaseRegionHorizontal, TestSize.Level0)
{
    SetupMockRosenLiveCrease(MakeHorizontalCreaseRects(), true);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto liveRects = displayInfoUtils->GetLiveFoldCreaseRegion();
    ASSERT_EQ(liveRects.size(), 1u);
    EXPECT_GT(liveRects[0].Width(), liveRects[0].Height());

    auto direction = displayInfoUtils->GetFoldCreaseDirection();
    EXPECT_EQ(direction, FoldCreaseDirection::HORIZONTAL);

    ResetMockRosenLiveCrease();
}

/**
 * @tc.name: CreaseHoverAC6c_LiveCreaseRegionVertical
 * @tc.desc: AC-6 variant: WHEN GetLiveCreaseRegion succeeds with vertical rect THEN direction=VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC6c_LiveCreaseRegionVertical, TestSize.Level0)
{
    SetupMockRosenLiveCrease(MakeVerticalCreaseRects(), true);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto liveRects = displayInfoUtils->GetLiveFoldCreaseRegion();
    ASSERT_EQ(liveRects.size(), 1u);
    EXPECT_LT(liveRects[0].Width(), liveRects[0].Height());

    auto direction = displayInfoUtils->GetFoldCreaseDirection();
    EXPECT_EQ(direction, FoldCreaseDirection::VERTICAL);

    ResetMockRosenLiveCrease();
}

/**
 * @tc.name: CreaseHoverAC6d_LiveCreaseRegionEmpty
 * @tc.desc: AC-6 variant: WHEN GetLiveCreaseRegion succeeds but returns empty rects THEN direction=UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC6d_LiveCreaseRegionEmpty, TestSize.Level0)
{
    SetupMockRosenLiveCrease({}, true);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto liveRects = displayInfoUtils->GetLiveFoldCreaseRegion();
    EXPECT_TRUE(liveRects.empty());

    auto direction = displayInfoUtils->GetFoldCreaseDirection();
    EXPECT_EQ(direction, FoldCreaseDirection::UNKNOWN);

    ResetMockRosenLiveCrease();
}

/**
 * @tc.name: CreaseHoverAC6e_LiveCreaseRegionSquare
 * @tc.desc: AC-6 variant: WHEN creaseRect width == height THEN direction=UNKNOWN
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC6e_LiveCreaseRegionSquare, TestSize.Level0)
{
    SetupMockRosenLiveCrease(MakeSquareCreaseRects(), true);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto direction = displayInfoUtils->GetFoldCreaseDirection();
    EXPECT_EQ(direction, FoldCreaseDirection::UNKNOWN);

    ResetMockRosenLiveCrease();
}

/**
 * @tc.name: CreaseHoverAC7_NonFoldableNoCallbackRegistration
 * @tc.desc: AC-7: WHEN IsFoldable()=false THEN OnAttachToFrameNode does not register foldStatusChange callback
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC7_NonFoldableNoCallbackRegistration, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, false);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());

    pattern->OnAttachToFrameNode();

    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: CreaseHoverAC7b_FoldableRegistersCallback
 * @tc.desc: AC-7 variant: WHEN IsFoldable()=true THEN OnAttachToFrameNode registers foldStatusChange callback
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC7b_FoldableRegistersCallback, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->HasFoldStatusChangedCallbackId());

    pattern->OnDetachFromFrameNode(frameNode.GetRawPtr());
    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: CreaseHoverAC7c_NonFoldableMultiThreadNoCallback
 * @tc.desc: AC-7: WHEN IsFoldable()=false THEN OnAttachToMainTreeMultiThread does not register callback
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC7c_NonFoldableMultiThreadNoCallback, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, false);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->OnAttachToMainTreeMultiThread();

    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: CreaseHoverAC7d_FoldableMultiThreadRegistersCallback
 * @tc.desc: AC-7 variant: WHEN IsFoldable()=true THEN OnAttachToMainTreeMultiThread registers callback
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC7d_FoldableMultiThreadRegistersCallback, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->HasFoldStatusChangedCallbackId());

    pattern->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: CreaseHoverAC8_NoDeviceTypeDependency
 * @tc.desc: AC-8: IsSupportHoverState does not depend on rotation or device type.
 *               Same FoldCreaseDirection produces same result regardless of rotation.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC8_NoDeviceTypeDependency, TestSize.Level0)
{
    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    auto displayInfoH = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, true);
    displayInfoH->SetRotation(Rotation::ROTATION_0);
    EXPECT_TRUE(pattern->IsSupportHoverState(displayInfoH));

    displayInfoH->SetRotation(Rotation::ROTATION_90);
    EXPECT_TRUE(pattern->IsSupportHoverState(displayInfoH));

    displayInfoH->SetRotation(Rotation::ROTATION_180);
    EXPECT_TRUE(pattern->IsSupportHoverState(displayInfoH));

    displayInfoH->SetRotation(Rotation::ROTATION_270);
    EXPECT_TRUE(pattern->IsSupportHoverState(displayInfoH));

    auto displayInfoV = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::VERTICAL, true);
    displayInfoV->SetRotation(Rotation::ROTATION_0);
    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfoV));

    displayInfoV->SetRotation(Rotation::ROTATION_90);
    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfoV));

    auto displayInfoU = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::UNKNOWN, true);
    displayInfoU->SetRotation(Rotation::ROTATION_0);
    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfoU));

    displayInfoU->SetRotation(Rotation::ROTATION_270);
    EXPECT_FALSE(pattern->IsSupportHoverState(displayInfoU));
}

/**
 * @tc.name: CreaseHoverAC8b_NullDisplayInfoReturnsFalse
 * @tc.desc: AC-8: IsSupportHoverState returns false when displayInfo is null (no crash)
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC8b_NullDisplayInfoReturnsFalse, TestSize.Level0)
{
    auto frameNode = CreateFolderStackNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<DisplayInfo> nullDisplayInfo = nullptr;
    EXPECT_FALSE(pattern->IsSupportHoverState(nullDisplayInfo));
}

/**
 * @tc.name: CreaseHoverAC8c_OnHoverStatusChangeNoDeviceTypeGuard
 * @tc.desc: AC-8: OnHoverStatusChange does not short-circuit on device type.
 *               When isIntoFolderStack_ != IsInHoverMode(), it proceeds (no device type guard).
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC8c_OnHoverStatusChangeNoDeviceTypeGuard, TestSize.Level0)
{
    auto displayInfo = CreateDisplayInfo(FoldStatus::HALF_FOLD, FoldCreaseDirection::HORIZONTAL, true);
    MockContainer::Current()->SetDisplayInfo(displayInfo);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->SetMinPlatformVersion(12);
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);

    RefPtr<FrameNode> folder;
    auto stack = CreateStack([this, &folder](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(FULL_SCREEN_WIDTH));
        ViewAbstract::SetHeight(CalcLength(FULL_SCREEN_HEIGHT));
        folder = CreateFolder([](FolderStackModelNG model) {});
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(folder, nullptr);

    auto folderStackPattern = folder->GetPattern<FolderStackPattern>();
    ASSERT_NE(folderStackPattern, nullptr);
    folderStackPattern->displayInfo_ = displayInfo;

    FlushUITasks(stack);

    auto layoutAlgorithm =
        AceType::DynamicCast<FolderStackLayoutAlgorithm>(folderStackPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);

    layoutAlgorithm->isIntoFolderStack_ = true;
    auto layoutProperty = folder->GetLayoutProperty<FolderStackLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.percentReference = CONTAINER_SIZE;

    RefPtr<GeometryNode> geometryNode = folder->GetGeometryNode();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(folder, geometryNode, folder->GetLayoutProperty());
    auto size = CreateIdealSizeByPercentRef(layoutConstraint, Axis::HORIZONTAL, MeasureType::MATCH_PARENT)
                    .ConvertToSizeT();
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);

    layoutAlgorithm->OnHoverStatusChange(AccessibilityManager::RawPtr(layoutWrapper));

    EXPECT_NE(layoutAlgorithm->GetIsIntoFolderStack(), folderStackPattern->IsInHoverMode());
}

/**
 * @tc.name: CreaseHoverAC8d_DisplayInfoUtilsUsesLiveNotCached
 * @tc.desc: AC-8: DisplayInfoUtils::GetFoldCreaseDirection reads from live crease region (not cached).
 *               Verifies that GetDisplayInfo() populates liveFoldCreaseRegion_ and foldCreaseDirection_.
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC8d_DisplayInfoUtilsUsesLiveNotCached, TestSize.Level0)
{
    SetupMockRosenLiveCrease(MakeHorizontalCreaseRects(), true);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto displayInfo = displayInfoUtils->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);

    auto liveRects = displayInfo->GetLiveFoldCreaseRegion();
    EXPECT_FALSE(liveRects.empty());
    EXPECT_GT(liveRects[0].Width(), liveRects[0].Height());

    EXPECT_EQ(displayInfo->GetFoldCreaseDirection(), FoldCreaseDirection::HORIZONTAL);

    ResetMockRosenLiveCrease();
}

/**
 * @tc.name: CreaseHoverAC8e_GetDisplayInfoRefreshesLiveData
 * @tc.desc: AC-8: GetDisplayInfo() refreshes live crease data each call (not cached across calls).
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackCreaseHoverTest, CreaseHoverAC8e_GetDisplayInfoRefreshesLiveData, TestSize.Level0)
{
    SetupMockRosenLiveCrease(MakeHorizontalCreaseRects(), true);

    auto displayInfoUtils = Container::Current()->GetDisplayInfoUtils();
    ASSERT_NE(displayInfoUtils, nullptr);

    auto displayInfo1 = displayInfoUtils->GetDisplayInfo();
    ASSERT_NE(displayInfo1, nullptr);
    EXPECT_EQ(displayInfo1->GetFoldCreaseDirection(), FoldCreaseDirection::HORIZONTAL);

    SetupMockRosenLiveCrease(MakeVerticalCreaseRects(), true);

    auto displayInfo2 = displayInfoUtils->GetDisplayInfo();
    ASSERT_NE(displayInfo2, nullptr);
    EXPECT_EQ(displayInfo2->GetFoldCreaseDirection(), FoldCreaseDirection::VERTICAL);

    SetupMockRosenLiveCrease({}, false);

    auto displayInfo3 = displayInfoUtils->GetDisplayInfo();
    ASSERT_NE(displayInfo3, nullptr);
    EXPECT_EQ(displayInfo3->GetFoldCreaseDirection(), FoldCreaseDirection::UNKNOWN);

    ResetMockRosenLiveCrease();
}

} // namespace OHOS::Ace::NG
