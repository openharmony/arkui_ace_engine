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

#include <optional>
#include <string>

#include "gtest/gtest.h"
#include "ui/base/utils/utils.h"

#define private public
#define protected public

#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/base/mock_subwindow.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"
#include "ui/base/ace_type.h"
#include "ui/base/geometry/dimension.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension SHEET_SIDE_DEFAULT_WIDTH = 400.0_vp;
} // namespace
class SheetShowInSubwindowTestNg : public testing::Test {
public:
    static int32_t lastPlatformVersion_;

    static void SetUpTestSuite();
    static void TearDownTestSuite();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    // Before each TEST_F, the scope is a single test case
    void SetUp() override;
    // After each TEST_F, the scope is a single test case
    void TearDown() override;

protected:
    static RefPtr<FrameNode> InitTargetNodeEnv(RefPtr<FrameNode>& rootNode, const SizeF& rootSize,
        const OffsetF& rootOffset, const SizeF& targetSize, const OffsetF& targetOffset);
    static void CreateSheetStyle(SheetStyle& sheetStyle, const Dimension& width, const Dimension& height);
    void CreateSheetBuilder(float builderHeight = 800.f, float titleHeight = 800.f);
    static void InitSheetAndWrapperLayoutInfo(const RefPtr<FrameNode>& sheetPageNode,
        const RefPtr<FrameNode>& sheetWrapperNode, RefPtr<SheetPresentationLayoutAlgorithm>& sheetPageLayoutAlgorithm,
        RefPtr<SheetWrapperLayoutAlgorithm>& sheetWrapperLayoutAlgorithm);
};

int32_t SheetShowInSubwindowTestNg::lastPlatformVersion_ = 0;

/**
 * @brief: Called once before executing the entire test suite
 * @note: All TEST_F shared.
 *        Initialize the global commons.
 */
void SheetShowInSubwindowTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SheetShowInSubwindowTestNg::lastPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

/**
 * @brief: Called once after executing the entire test suite
 * @note: All TEST_F shared.
 *        Clean up the global commons.
 */
void SheetShowInSubwindowTestNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// Before each TEST_F, the scope is a single test case
void SheetShowInSubwindowTestNg::SetUp() {}

// After each TEST_F, the scope is a single test case
void SheetShowInSubwindowTestNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(SheetShowInSubwindowTestNg::lastPlatformVersion_);
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
}

void SheetShowInSubwindowTestNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(
        [sheetTheme = AceType::WeakClaim(AceType::RawPtr(sheetTheme))](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            return sheetTheme.Upgrade();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetShowInSubwindowTestNg::CreateSheetBuilder(float builderHeight, float titleHeight)
{
    auto builderFunc = [builderHeight]() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    auto buildTitleNodeFunc = [titleHeight]() -> RefPtr<UINode> {
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
        frameNode->AddChild(childFrameNode);
        return frameNode;
    };
    builderFunc_ = builderFunc;
    titleBuilderFunc_ = buildTitleNodeFunc;
}

void SheetShowInSubwindowTestNg::InitSheetAndWrapperLayoutInfo(const RefPtr<FrameNode>& sheetPageNode,
    const RefPtr<FrameNode>& sheetWrapperNode, RefPtr<SheetPresentationLayoutAlgorithm>& sheetPageLayoutAlgorithm,
    RefPtr<SheetWrapperLayoutAlgorithm>& sheetWrapperLayoutAlgorithm)
{
    auto sheetPagePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPagePattern, nullptr);
    sheetPageLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPagePattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetPageLayoutAlgorithm, nullptr);
    sheetPageNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sheetPageLayoutAlgorithm);

    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperLayoutAlgorithm =
        AceType::DynamicCast<SheetWrapperLayoutAlgorithm>(sheetWrapperPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sheetWrapperLayoutAlgorithm, nullptr);
    sheetWrapperNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(sheetWrapperLayoutAlgorithm);
}

RefPtr<FrameNode> SheetShowInSubwindowTestNg::InitTargetNodeEnv(RefPtr<FrameNode>& rootNode, const SizeF& rootSize,
    const OffsetF& rootOffset, const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(targetNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    CHECK_NULL_RETURN(stageNode, nullptr);
    rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto rootGeometryNode = rootNode->GetGeometryNode();
    CHECK_NULL_RETURN(rootGeometryNode, nullptr);
    rootGeometryNode->SetFrameSize(rootSize);
    rootGeometryNode->SetMarginFrameOffset(rootOffset);
    auto targetGeometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_RETURN(targetGeometryNode, nullptr);
    targetGeometryNode->SetFrameSize(targetSize);
    targetGeometryNode->SetMarginFrameOffset(targetOffset);
    targetNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    auto renderContext = AceType::DynamicCast<MockRenderContext>(targetNode->renderContext_);
    renderContext->SetPaintRectWithTransform(RectF(targetOffset, targetSize));
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    return targetNode;
}

HWTEST_F(SheetShowInSubwindowTestNg, RemoveSheet001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node.
     */
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, -1, AceType::MakeRefPtr<SheetPresentationPattern>(-1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetWrapperNode = FrameNode::CreateFrameNode("sheetWrapper", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetWrapperPattern>(201, "SheetPresentation"));
    ASSERT_NE(sheetWrapperNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();
    EXPECT_EQ(rootNode->GetChildren().size(), 1);

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->RemoveSheet(sheetNode);
    EXPECT_EQ(rootNode->GetChildren().size(), 0);
}

HWTEST_F(SheetShowInSubwindowTestNg, RemoveSheet002, TestSize.Level1)
{
    auto sheetNode = FrameNode::CreateFrameNode(
        V2::SHEET_PAGE_TAG, 1, AceType::MakeRefPtr<SheetPresentationPattern>(1, V2::BUTTON_ETS_TAG, nullptr));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetWrapperNode =
        FrameNode::CreateFrameNode("sheetWrapper", 2, AceType::MakeRefPtr<SheetWrapperPattern>(2, "SheetPresentation"));
    ASSERT_NE(sheetWrapperNode, nullptr);
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 3, AceType::MakeRefPtr<RootPattern>());
    sheetNode->MountToParent(sheetWrapperNode);
    sheetWrapperNode->MountToParent(rootNode);
    rootNode->MarkDirtyNode();

    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    SheetStyle style;
    style.showInSubWindow = true;
    layoutProperty->UpdateSheetStyle(style);
    auto sheetMaskNode =
        FrameNode::CreateFrameNode("sheetMask", 3, AceType::MakeRefPtr<SheetMaskPattern>(3, "SheetMask"));
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->SetSheetMaskNode(sheetMaskNode);
    sheetWrapperPattern->subWindowId_ = 1000000;

    auto subwindow = AceType::MakeRefPtr<MockSubwindow>();
    std::vector<Rect> rects;
    auto rect = Rect(100, 100, 100, 100);
    rects.emplace_back(rect);
    SubwindowManager::GetInstance()->AddSubwindow(1000000, SubwindowType::TYPE_SHEET, subwindow);
    SubwindowManager::GetInstance()->SetHotAreas(
        rects, SubwindowType::TYPE_SHEET, sheetMaskNode->GetId(), sheetWrapperPattern->GetSubWindowId());
    SubwindowManager::GetInstance()->SetHotAreas(
        rects, SubwindowType::TYPE_SHEET, sheetNode->GetId(), sheetWrapperPattern->GetSubWindowId());

    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->RemoveSheet(sheetNode);
    EXPECT_EQ(rootNode->GetChildren().size(), 0);
}

HWTEST_F(SheetShowInSubwindowTestNg, InitSheetWrapperAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);
    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    CreateSheetBuilder();
    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    /**
     * @tc.steps: step3: measure and layout sheet page
     * @tc.expected: finalPlacement == Bottom and showArrow == true
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(
        sheetPageNode, sheetWrapperNode, sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(1000, 1000);
    parentLayoutConstrain.percentReference = SizeF(1000, 1000);
    sheetPageNode->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);
    sheetPageLayoutAlgorithm->sheetStyle_.showInSubWindow = true;
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    /**
     * @tc.steps: step4: measure and layout sheet page
     * @tc.expected: sheetWidth has default values and outlier handling.
     */
    sheetWrapperPattern->mainWindowRect_ = RectF(0, 0, 2000, 2000);
    sheetPageLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetTheme->centerDefaultWidth_ = 480.0_vp;
    sheetPageLayoutAlgorithm->ComputeWidthAndHeight(AceType::RawPtr(sheetPageNode));
    EXPECT_EQ(sheetPageLayoutAlgorithm->sheetWidth_, 480);

    sheetPageLayoutAlgorithm->sheetStyle_.width = Dimension(0.2, DimensionUnit::PERCENT);
    sheetPageLayoutAlgorithm->ComputeWidthAndHeight(AceType::RawPtr(sheetPageNode));
    EXPECT_EQ(sheetPageLayoutAlgorithm->sheetWidth_, 400);

    sheetPageLayoutAlgorithm->sheetStyle_.width = Dimension(500, DimensionUnit::PX);
    sheetPageLayoutAlgorithm->ComputeWidthAndHeight(AceType::RawPtr(sheetPageNode));
    EXPECT_EQ(sheetPageLayoutAlgorithm->sheetWidth_, 500);

    sheetPageLayoutAlgorithm->sheetStyle_.width = Dimension(5000, DimensionUnit::PX);
    sheetPageLayoutAlgorithm->ComputeWidthAndHeight(AceType::RawPtr(sheetPageNode));
    EXPECT_EQ(sheetPageLayoutAlgorithm->sheetWidth_, 480);
}

HWTEST_F(SheetShowInSubwindowTestNg, InitSheetWrapperAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);
    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    CreateSheetBuilder();
    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    /**
     * @tc.steps: step3: measure and layout sheet page
     * @tc.expected: finalPlacement == Bottom and showArrow == true
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(
        sheetPageNode, sheetWrapperNode, sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    LayoutConstraintF parentLayoutConstrain;
    parentLayoutConstrain.selfIdealSize = OptionalSize<float>(1000, 1000);
    parentLayoutConstrain.percentReference = SizeF(1000, 1000);
    sheetPageNode->GetGeometryNode()->SetParentLayoutConstraint(parentLayoutConstrain);
    sheetPageLayoutAlgorithm->sheetStyle_.showInSubWindow = true;
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->mainWindowRect_ = RectF(0, 0, 2000, 2000);
    sheetPageLayoutAlgorithm->sheetType_ = SheetType::SHEET_CENTER;
    sheetPageLayoutAlgorithm->sheetStyle_.sheetHeight.height = Dimension(0.2, DimensionUnit::PERCENT);
    sheetPageLayoutAlgorithm->ComputeWidthAndHeight(AceType::RawPtr(sheetPageNode));
    EXPECT_EQ(sheetPageLayoutAlgorithm->sheetHeight_, 360);

    sheetPageLayoutAlgorithm->sheetStyle_.sheetHeight.height = Dimension(800, DimensionUnit::PERCENT);
    sheetPageLayoutAlgorithm->ComputeWidthAndHeight(AceType::RawPtr(sheetPageNode));
    EXPECT_EQ(sheetPageLayoutAlgorithm->sheetHeight_, 1800);
}

HWTEST_F(SheetShowInSubwindowTestNg, InitSheetWrapperAction003, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);
    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    CreateSheetBuilder();
    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    /**
     * @tc.steps: step3: measure and layout sheet page
     * @tc.expected: finalPlacement == Bottom and showArrow == true
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    auto sheetMaskNode =
        FrameNode::CreateFrameNode("sheetMask", 3, AceType::MakeRefPtr<SheetMaskPattern>(3, "SheetMask"));
    sheetMaskNode->MountToParent(sheetWrapperNode);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(
        sheetPageNode, sheetWrapperNode, sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->SetSheetMaskNode(sheetMaskNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0, 0, 2000, 2000);
    sheetWrapperPattern->isShowInUEC_ = true;
    sheetWrapperLayoutAlgorithm->MeasureSheetMask(AceType::RawPtr(sheetWrapperNode));
    EXPECT_EQ(sheetMaskNode->GetGeometryNode()->GetFrameSize().Height(), 2000);

    sheetWrapperPattern->mainWindowRect_ = RectF(0, 0, 3000, 3000);
    sheetWrapperPattern->isShowInUEC_ = false;
    sheetWrapperLayoutAlgorithm->MeasureSheetMask(AceType::RawPtr(sheetWrapperNode));
    EXPECT_EQ(sheetMaskNode->GetGeometryNode()->GetFrameSize().Height(), 2000);
}

HWTEST_F(SheetShowInSubwindowTestNg, InitSheetWrapperAction004, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);
    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    CreateSheetBuilder();
    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());
    /**
     * @tc.steps: step3: measure and layout sheet mask
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    auto sheetMaskNode =
        FrameNode::CreateFrameNode("sheetMask", 3, AceType::MakeRefPtr<SheetMaskPattern>(3, "SheetMask"));
    auto maskPattern = sheetMaskNode->GetPattern<SheetMaskPattern>();
    ASSERT_NE(maskPattern, nullptr);
    sheetMaskNode->MountToParent(sheetWrapperNode);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(
        sheetPageNode, sheetWrapperNode, sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetWrapperPattern = sheetWrapperNode->GetPattern<SheetWrapperPattern>();
    ASSERT_NE(sheetWrapperPattern, nullptr);
    sheetWrapperPattern->SetSheetMaskNode(sheetMaskNode);
    sheetWrapperPattern->mainWindowRect_ = RectF(0, 0, 2000, 2000);
    sheetWrapperLayoutAlgorithm->LayoutMaskNode(AceType::RawPtr(sheetWrapperNode));
    EXPECT_TRUE(sheetWrapperNode->GetGeometryNode()->GetMarginFrameOffset() == OffsetF(0, 0));
    // Handle UEC
    sheetWrapperPattern->isShowInUEC_ = true;
    sheetWrapperLayoutAlgorithm->MeasureSheetMask(AceType::RawPtr(sheetWrapperNode));
    EXPECT_EQ(sheetMaskNode->GetGeometryNode()->GetFrameSize().Height(), 2000);
    sheetWrapperLayoutAlgorithm->LayoutMaskNode(AceType::RawPtr(sheetWrapperNode));
    EXPECT_TRUE(sheetMaskNode->GetGeometryNode()->GetMarginFrameRect() == RectF(0, 0, 2000, 2000));

    maskPattern->isMaskInteractive_ = true;
    auto mockSubwindow = AceType::MakeRefPtr<MockSubwindow>();
    EXPECT_CALL(*mockSubwindow, GetChildContainerId()).Times(1).WillOnce(Return(MIN_SUBCONTAINER_ID));
    SubwindowManager::GetInstance()->AddSubwindow(Container::CurrentId(), SubwindowType::TYPE_SHEET, mockSubwindow);
    // SubwindowManager::SetHotAreas(_,_) is mock in mock_subwindow_manager.cpp
    sheetWrapperLayoutAlgorithm->LayoutMaskNode(AceType::RawPtr(sheetWrapperNode));
    EXPECT_EQ(sheetMaskNode->GetGeometryNode()->GetFrameSize().Height(), 2000);

    mockSubwindow = nullptr;
    SubwindowManager::GetInstance()->subwindowMap_.clear();
    SubwindowManager::GetInstance()->instanceSubwindowMap_.clear();
}

/**
 * @tc.name: GetSheetTypeNumber1
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: The default is Bottom Type
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, GetSheetTypeNumber1, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(SheetStyle());
    /**
     * @tc.steps: step2. the device is like phone or base.
     */
    sheetPattern->sheetThemeType_ = "auto";
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 });
    /**
     * @tc.expected: the sheetType is bottom when window width is less than 600vp
     */
    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_BOTTOM);
    /**
     * @tc.steps: step2. Set preferType is Bottom.
     * @tc.expected: the sheetType is Bottom too.
     */
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType2 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType2, SheetType::SHEET_BOTTOM);
    /**
     * @tc.steps: step3. Set preferType is Bottom, and Set Offset property.
     * @tc.expected: the sheetType is SHEET_BOTTOM_OFFSET.
     */
    auto manager = pipelineContext->GetWindowManager();
    ASSERT_NE(manager, nullptr);
    auto isPcOrPadFreeMultiWindow = []() {
        return true;
    };
    manager->SetIsPcOrPadFreeMultiWindowModeCallback(std::move(isPcOrPadFreeMultiWindow));
    sheetStyle.bottomOffset = OffsetF(0, -10);
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType3 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType3, SheetType::SHEET_BOTTOM_OFFSET);
}

/**
 * @tc.name: GetSheetTypeNumber2
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: The default is Bottom Type in other scenarios
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, GetSheetTypeNumber2, TestSize.Level1)
{
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(SheetStyle());
    /**
     * @tc.steps: step2. the device is like phone or base, and rootHeight is less than rootWidth
     * @tc.expected: The Sheet Type is SHEET_BOTTOMLANDSPACE.
     */
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    sheetPattern->sheetThemeType_ = "auto";
    RefPtr<DisplayInfo> displayInfo = AceType::MakeRefPtr<DisplayInfo>();
    displayInfo->SetFoldStatus(FoldStatus::FOLDED);
    MockContainer::Current()->SetDisplayInfo(displayInfo);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 1600, 800 });
    sheetPattern->windowSize_ = SizeT<int32_t>(1600, 800);
    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_BOTTOMLANDSPACE);
    /**
     * @tc.steps: step3. the device is like phone or base, and its window width is great than 600vp.
     * @tc.expected: The Sheet Type is SHEET_BOTTOM.
     */
    sheetTheme->sheetBottom_ = "bottom";
    sheetPattern->windowSize_ = SizeT<int32_t>(800, 1600);
    auto sheetType2 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType2, SheetType::SHEET_BOTTOM);
    /**
     * @tc.steps: step4. the device is like tablet, and its window width is great than 800vp.
     * @tc.expected: The Sheet Type is SHEET_BOTTOM.
     */
    // if preferType property is null
    sheetPattern->sheetThemeType_ = "popup";
    sheetPattern->windowSize_ = SizeT<int32_t>(500, 1600);
    auto sheetType3 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType3, SheetType::SHEET_BOTTOM_FREE_WINDOW);
    // if preferType property is valid
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->windowSize_ = SizeT<int32_t>(1000, 1600);
    auto sheetType4 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType4, SheetType::SHEET_BOTTOM);
}

/**
 * @tc.name: GetSheetTypeNumber3
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: Test SheetType in device like TV
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, GetSheetTypeNumber3, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));

    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(SheetStyle());
    /**
     * @tc.steps: step2. the device is like TV, and its window width is less than 600vp
     * @tc.expected: The Sheet Type is default by SHEET_BOTTOM.
     */
    sheetPattern->sheetThemeType_ = "center";
    // DisplayWindowRectInfo is no refresh, the windowSize_ is the standard
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 });
    sheetPattern->windowSize_ = SizeT<int32_t>(500, 1600);
    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_BOTTOM);
    // if preferType property is valid
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    // DisplayWindowRectInfo is no refresh, the windowSize_ is the standard
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 });
    sheetPattern->windowSize_ = SizeT<int32_t>(1000, 1600);
    auto sheetType2 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType2, SheetType::SHEET_BOTTOM);
    /**
     * @tc.steps: step3. the device is like TV, and its window width is greater
     * @tc.expected: The Sheet Type is default by SHEET_CENTER.
     */
    layoutProperty->UpdateSheetStyle(SheetStyle());
    sheetPattern->windowSize_ = SizeT<int32_t>(2000, 1600);
    auto sheetType3 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType3, SheetType::SHEET_CENTER);
    // if preferType property is valid
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType4 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType4, SheetType::SHEET_BOTTOM);

    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType5 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType5, SheetType::SHEET_POPUP);
}

/**
 * @tc.name: GetSheetTypeNumber4
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: Test SheetType in base device like greater phone
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, GetSheetTypeNumber4, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(SheetStyle());
    /**
     * @tc.steps: step2. the device is like phone or base.
     * @tc.expected: The Sheet Type is default by SHEET_CENTER.
     */
    sheetPattern->sheetThemeType_ = "auto";
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 800, 800 });
    sheetPattern->windowSize_ = SizeT<int32_t>(800, 800);
    RefPtr<DisplayInfo> displayInfo = AceType::MakeRefPtr<DisplayInfo>();
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    MockContainer::Current()->SetDisplayInfo(displayInfo);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBottom_ = "auto";
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);

    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_CENTER);
    // if Center preferType is valid in this scenario.
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_CENTER;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType2 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType2, SheetType::SHEET_CENTER);
    // if Popup preferType is valid in this scenario.
    // if API13, SHEET_POPUP will not work in this scenario.
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);

    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType3 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType3, SheetType::SHEET_CENTER);

    // if API14, SHEET_POPUP will work in this scenario.
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
    auto sheetType4 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType4, SheetType::SHEET_POPUP);
}

/**
 * @tc.name: GetSheetTypeNumber5
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: Test SheetType in tablet device.
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, GetSheetTypeNumber5, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));

    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(SheetStyle());
    /**
     * @tc.steps: step2. the device is like greatest phone.
     * @tc.expected: The Sheet Type is default by SHEET_CENTER.
     */
    sheetPattern->sheetThemeType_ = "auto";
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 1600, 800 });
    sheetPattern->windowSize_ = SizeT<int32_t>(1600, 800);
    RefPtr<DisplayInfo> displayInfo = AceType::MakeRefPtr<DisplayInfo>();
    displayInfo->SetFoldStatus(FoldStatus::EXPAND);
    MockContainer::Current()->SetDisplayInfo(displayInfo);
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->sheetBottom_ = "auto";
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);

    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_CENTER);
    // if SHEET_POPUP preferType is valid in this scenario.
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_POPUP;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
    auto sheetType2 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType2, SheetType::SHEET_POPUP);
    /**
     * @tc.steps: step3. the device is like tablet.
     * @tc.expected: The Sheet Type is default by SHEET_POPUP.
     */
    layoutProperty->UpdateSheetStyle(SheetStyle());
    sheetPattern->sheetThemeType_ = "popup";
    auto sheetType3 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType3, SheetType::SHEET_POPUP);
    // if width > 600, width < 840, The Sheet Type is default by SHEET_CENTER
    // After the device is rotated horizontally and vertically
    sheetPattern->windowSize_ = SizeT<int32_t>(800, 1600);
    auto sheetType4 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType4, SheetType::SHEET_CENTER);
}

/**
 * @tc.name: GetSheetTypeNumber6
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: Test Side SheetType.
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, GetSheetTypeNumber6, TestSize.Level1)
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    /**
     * @tc.steps: step2. the device is like phone.
     * @tc.expected: The Sheet Type is default by SHEET_BOTTM, it can't be a Side type.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 500, 1600 });
    auto sheetType1 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType1, SheetType::SHEET_BOTTOM);
    // Even if SHEET_SIDE preferType is valid, it will still be SHEET_BOTTOM.
    SheetStyle sheetStyle;
    sheetStyle.sheetType = SheetType::SHEET_SIDE;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType2 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType2, SheetType::SHEET_BOTTOM);
    /**
     * @tc.steps: step3. the device is like tablet, width > 600.
     * @tc.expected: The Side Sheet Type will take effect.
     */
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 1000, 800 });
    auto sheetType3 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType3, SheetType::SHEET_SIDE);
    // If the developer sets the preferType property to a different type, it can still take effect of that type.
    // Such as SHEEET_BOTTOM
    sheetStyle.sheetType = SheetType::SHEET_BOTTOM;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    auto sheetType4 = sheetPattern->GetSheetType();
    EXPECT_EQ(sheetType4, SheetType::SHEET_BOTTOM);
}

/**
 * @tc.name: SideSheeteLayoutAlgorithm1
 * @tc.desc: Test SheetPresentationSideLayoutAlgorithm::GetSheetDefaultWidth.
 *           Condition: Test Side Sheet DefaultWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideSheeteLayoutAlgorithm1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page, get sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    /**
     * @tc.steps: step2. side's default width will change with the window size.
     */
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->rootWidth_ = 700.0;
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    EXPECT_FLOAT_EQ(algorithm->GetSheetDefaultWidth(sheetPattern), pipelineContext->rootWidth_ / 2);
    pipelineContext->rootWidth_ = 1000.0;
    EXPECT_FLOAT_EQ(algorithm->GetSheetDefaultWidth(sheetPattern), SHEET_SIDE_DEFAULT_WIDTH.ConvertToPx());

    sheetPattern->windowSize_ = SizeT<int32_t>(700, 800);
    EXPECT_FLOAT_EQ(algorithm->GetSheetDefaultWidth(sheetPattern), 700.0f / 2);
    sheetPattern->windowSize_ = SizeT<int32_t>(1000, 800);
    EXPECT_FLOAT_EQ(algorithm->GetSheetDefaultWidth(sheetPattern), SHEET_SIDE_DEFAULT_WIDTH.ConvertToPx());
}

/**
 * @tc.name: SideSheeteLayoutAlgorithm2
 * @tc.desc: SheetPresentationSideLayoutAlgorithm Width Measure
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideSheeteLayoutAlgorithm2, TestSize.Level1)
{
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1: create sheetNode, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetStyle style;
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = { 1000, 1000 };
    sheetNode->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    /**
     * @tc.steps: step2. side width = defaultWidth.
     */
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetMaxWidth_, 1000);
    EXPECT_FLOAT_EQ(algorithm->sheetMaxHeight_, 1000);
    EXPECT_FLOAT_EQ(algorithm->sheetWidth_, algorithm->GetSheetDefaultWidth(sheetPattern));
    EXPECT_EQ(sheetNode->GetGeometryNode()->GetFrameSize(), SizeF(algorithm->sheetWidth_, algorithm->sheetHeight_));
    EXPECT_EQ(sheetNode->GetGeometryNode()->GetContentSize(), SizeF(algorithm->sheetWidth_, algorithm->sheetHeight_));
    /**
     * @tc.steps: step3. side width is valid.
     */
    style.width = Dimension(0.5, DimensionUnit::PERCENT);
    layoutProperty->UpdateSheetStyle(style);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetWidth_, 1000 * 0.5);
    style.width = Dimension(300, DimensionUnit::PX);
    layoutProperty->UpdateSheetStyle(style);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetWidth_, Dimension(300, DimensionUnit::PX).ConvertToPx());
    /**
     * @tc.steps: step4. side width is invalid, such as width is greater than maxWidth.
     */
    style.width = Dimension(2000, DimensionUnit::PX);
    layoutProperty->UpdateSheetStyle(style);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetWidth_, algorithm->GetSheetDefaultWidth(sheetPattern));
}

/**
 * @tc.name: SideSheeteLayoutAlgorithm3
 * @tc.desc: SheetPresentationSideLayoutAlgorithm Height Measure
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideSheeteLayoutAlgorithm3, TestSize.Level1)
{
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1: create sheetNode, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetStyle style;
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = { 1000, 1000 };
    sheetNode->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    /**
     * @tc.steps: step2. side height = defaultHeight = maxHeight.
     */
    auto algorithm = AceType::MakeRefPtr<SheetPresentationSideLayoutAlgorithm>();
    ASSERT_NE(algorithm, nullptr);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetMaxWidth_, 1000);
    EXPECT_FLOAT_EQ(algorithm->sheetMaxHeight_, 1000);
    EXPECT_FLOAT_EQ(algorithm->sheetHeight_, algorithm->sheetMaxHeight_);
    EXPECT_EQ(sheetNode->GetGeometryNode()->GetFrameSize(), SizeF(algorithm->sheetWidth_, algorithm->sheetHeight_));
    EXPECT_EQ(sheetNode->GetGeometryNode()->GetContentSize(), SizeF(algorithm->sheetWidth_, algorithm->sheetHeight_));
    /**
     * @tc.steps: step3. side height is valid, and height will be not in effect.
     */
    style.sheetHeight.height = Dimension(0.5, DimensionUnit::PERCENT);
    layoutProperty->UpdateSheetStyle(style);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetHeight_, algorithm->sheetMaxHeight_);
    style.sheetHeight.height = Dimension(300, DimensionUnit::PX);
    layoutProperty->UpdateSheetStyle(style);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetHeight_, algorithm->sheetMaxHeight_);
    /**
     * @tc.steps: step4. side height is invalid, such as height is greater than maxHeight.
     */
    style.sheetHeight.height = Dimension(2000, DimensionUnit::PX);
    layoutProperty->UpdateSheetStyle(style);
    algorithm->Measure(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(algorithm->sheetHeight_, algorithm->sheetMaxHeight_);
}

/**
 * @tc.name: SideSheetLayoutAlgorithm4
 * @tc.desc: SheetPresentationSideLayoutAlgorithm Measure Scroll Height
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideSheetLayoutAlgorithm4, TestSize.Level1)
{
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 1000, 1600 });
    /**
     * @tc.steps: step1. create sheet node.
     */
    SheetStyle style;
    style.sheetType = SheetType::SHEET_SIDE;
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto* layoutWrapper = new LayoutWrapperNode(
        AceType::WeakClaim(AceType::RawPtr(sheetNode)), geometryNode->Clone(), layoutProperty->Clone());
    ASSERT_NE(layoutWrapper, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = { 1000, 1000 };
    geometryNode->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    /**
     * @tc.steps: step2. scroll height = maxHeight, scroll width = maxWidth.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    ASSERT_NE(scrollNode, nullptr);
    auto index = sheetNode->GetChildIndexById(scrollNode->GetId());
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(scrollWrapper);
    auto sideLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationSideLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sideLayoutAlgorithm, nullptr);
    sideLayoutAlgorithm->sheetHeight_ = 1000;
    sideLayoutAlgorithm->sheetWidth_ = 1000;
    sideLayoutAlgorithm->MeasureScrollNode(layoutWrapper, layoutConstraint);
    auto scrollGeometryNode = scrollWrapper->GetGeometryNode();
    ASSERT_NE(scrollGeometryNode, nullptr);
    EXPECT_FLOAT_EQ(scrollGeometryNode->GetFrameSize().Width(), 1000);
    EXPECT_FLOAT_EQ(scrollGeometryNode->GetFrameSize().Height(), 1000);
}

/**
 * @tc.name: SideSheetLayoutAlgorithm5
 * @tc.desc: SheetPresentationSideLayoutAlgorithm Layout
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideSheetLayoutAlgorithm5, TestSize.Level1)
{
    Dimension closeIconButtonWidth = 1.0_vp;
    Dimension titleTextMargin = 2.0_vp;
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 1000, 1600 });
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->closeIconButtonWidth_ = closeIconButtonWidth;
    sheetTheme->titleTextMargin_ = titleTextMargin;
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1. create sheet node.
     */
    SheetStyle style;
    style.sheetType = SheetType::SHEET_SIDE;
    style.sheetTitle = "mainTitle";
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = { 1000, 1000 };
    geometryNode->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    /**
     * @tc.steps: step2. test sheetNode Layout.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sideLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationSideLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sideLayoutAlgorithm, nullptr);
    sideLayoutAlgorithm->sheetHeight_ = 1000;
    sideLayoutAlgorithm->sheetWidth_ = 1000;
    sideLayoutAlgorithm->Layout(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(geometryNode->GetMarginFrameOffset().GetX(), 0);
    EXPECT_FLOAT_EQ(geometryNode->GetMarginFrameOffset().GetY(), 0);

    auto sheetCloseNode = sheetPattern->GetSheetCloseIcon();
    ASSERT_NE(sheetCloseNode, nullptr);
    auto closeGeometryNode = sheetCloseNode->GetGeometryNode();
    ASSERT_NE(closeGeometryNode, nullptr);
    EXPECT_FLOAT_EQ(closeGeometryNode->GetMarginFrameOffset().GetX(),
        geometryNode->GetFrameSize().Width() - closeIconButtonWidth.ConvertToPx() - titleTextMargin.ConvertToPx());
    EXPECT_FLOAT_EQ(closeGeometryNode->GetMarginFrameOffset().GetY(), titleTextMargin.ConvertToPx());

    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    auto builderNode = sheetPattern->GetTitleBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    auto buildGeometryNode = builderNode->GetGeometryNode();
    ASSERT_NE(buildGeometryNode, nullptr);
    EXPECT_FLOAT_EQ(buildGeometryNode->GetMarginFrameOffset().GetX(), 0.0f);
    EXPECT_FLOAT_EQ(buildGeometryNode->GetMarginFrameOffset().GetY(), padding.top.value_or(0.0f));
}

/**
 * @tc.name: SideSheetLayoutAlgorithm6
 * @tc.desc: SheetPresentationSideLayoutAlgorithm Layout when in mirror
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideSheetLayoutAlgorithm6, TestSize.Level1)
{
    Dimension closeIconButtonWidth = 1.0_vp;
    Dimension titleTextMargin = 2.0_vp;
    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    pipelineContext->SetDisplayWindowRectInfo({ 0, 0, 1000, 1600 });
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    sheetTheme->closeIconButtonWidth_ = closeIconButtonWidth;
    sheetTheme->titleTextMargin_ = titleTextMargin;
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1. create sheet node.
     */
    SheetStyle style;
    style.sheetType = SheetType::SHEET_SIDE;
    style.sheetTitle = "mainTitle";
    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto callback = [](const std::string&) {};
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto geometryNode = sheetNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = { 1000, 1000 };
    geometryNode->SetParentLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    /**
     * @tc.steps: step2. set RTL = true.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    /**
     * @tc.steps: step3. test sheetNode Layout.
     */
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto sideLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationSideLayoutAlgorithm>(sheetPattern->CreateLayoutAlgorithm());
    ASSERT_NE(sideLayoutAlgorithm, nullptr);
    sideLayoutAlgorithm->sheetHeight_ = 1000;
    sideLayoutAlgorithm->sheetWidth_ = 1000;
    sideLayoutAlgorithm->Layout(AceType::RawPtr(sheetNode));
    EXPECT_FLOAT_EQ(geometryNode->GetMarginFrameOffset().GetX(), 0);
    EXPECT_FLOAT_EQ(geometryNode->GetMarginFrameOffset().GetY(), 0);

    auto sheetCloseNode = sheetPattern->GetSheetCloseIcon();
    ASSERT_NE(sheetCloseNode, nullptr);
    auto closeGeometryNode = sheetCloseNode->GetGeometryNode();
    ASSERT_NE(closeGeometryNode, nullptr);
    auto padding = sheetPattern->GetSheetObject()->GetSheetSafeAreaPadding();
    EXPECT_FLOAT_EQ(closeGeometryNode->GetMarginFrameOffset().GetX(),
        titleTextMargin.ConvertToPx() + padding.left.value_or(0.0f));
    EXPECT_FLOAT_EQ(closeGeometryNode->GetMarginFrameOffset().GetY(), titleTextMargin.ConvertToPx());

    auto builderNode = sheetPattern->GetTitleBuilderNode();
    ASSERT_NE(builderNode, nullptr);
    auto buildGeometryNode = builderNode->GetGeometryNode();
    ASSERT_NE(buildGeometryNode, nullptr);
    EXPECT_FLOAT_EQ(buildGeometryNode->GetMarginFrameOffset().GetX(), padding.left.value_or(0.0f));
    EXPECT_FLOAT_EQ(buildGeometryNode->GetMarginFrameOffset().GetY(), padding.top.value_or(0.0f));
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

/**
 * @tc.name: SheetShowInSubwindowTestNg
 * @tc.desc: Test SheetSideObject::UpdateSidePosition().
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, UpdateSidePosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_SIDE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    /**
     * @tc.steps: step2. Sheet will not update side position, when it is onAppearing or onDisappearing.
     */
    sheetPattern->isOnDisappearing_ = true;
    sheetPattern->isOnAppearing_ = true;
    object->UpdateSidePosition();
    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);
    sheetPattern->isOnDisappearing_ = false;
    object->UpdateSidePosition();
    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);
    /**
     * @tc.steps: step3. Sheet will update side position, when it is not onAppearing and onDisappearing.
     */
    sheetPattern->isOnAppearing_ = false;
    object->UpdateSidePosition();
    EXPECT_FLOAT_EQ(
        renderContext->GetTransformTranslate()->x.ConvertToPx(), object->sheetMaxWidth_ - object->sheetWidth_);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    object->UpdateSidePosition();
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

/**
 * @tc.name: SheetShowInSubwindowTestNg
 * @tc.desc: Test SheetSideObject::ClipSheetNode().
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, SideClipSheetNode, TestSize.Level1)
{
    auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
    SheetShowInSubwindowTestNg::SetSheetTheme(sheetTheme);
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    BorderRadiusProperty borderRadius(5.0_vp);
    SheetStyle sheetStyle;
    sheetStyle.radius = borderRadius;
    layoutProperty->UpdateSheetStyle(sheetStyle);
    sheetPattern->sheetType_ = SheetType::SHEET_SIDE;
    sheetPattern->InitSheetObject();
    auto object = sheetPattern->GetSheetObject();
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetBorderRadius() == std::nullopt);
    /**
     * @tc.steps: step2. test BorderRadius.
     */
    Dimension radius = 1.0_px;
    object->ClipSheetNode();
    ASSERT_NE(renderContext->GetBorderRadius(), std::nullopt);
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusTopRight->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusBottomRight->ConvertToPx(), radius.ConvertToPx());
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    object->ClipSheetNode();
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusTopLeft->ConvertToPx(), radius.ConvertToPx());
    EXPECT_FLOAT_EQ(renderContext->GetBorderRadius()->radiusBottomLeft->ConvertToPx(), radius.ConvertToPx());
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
}

/**
 * @tc.name: SheetShowInSubwindowTestNg
 * @tc.desc: Test SheetSideObject::TransformTranslate.
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, TransformTranslate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_SIDE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);
    /**
     * @tc.steps: step2. test TransformTranslateEnter.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    object->TransformTranslateEnter();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    object->TransformTranslateEnter();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_FLOAT_EQ(
        renderContext->GetTransformTranslate()->x.ConvertToPx(), object->sheetMaxWidth_ - object->sheetWidth_);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    /**
     * @tc.steps: step3. test TransformTranslateExit.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    object->TransformTranslateEnter();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), -object->sheetWidth_);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    object->TransformTranslateEnter();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), object->sheetMaxWidth_);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: SheetShowInSubwindowTestNg
 * @tc.desc: Test SheetSideObject::PostProcessBorderWidth.
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, PostProcessBorderWidth, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetType_ = SheetType::SHEET_SIDE;
    sheetPattern->InitSheetObject();
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    auto renderContext = sheetNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->GetTransformTranslate() == std::nullopt);
    sheetPattern->SetShowState(true);
    sheetPattern->isPlayTransition_ = false;
    /**
     * @tc.steps: step2. test RTL.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    auto borderWidth = object->PostProcessBorderWidth(NG::BorderWidthProperty());
    EXPECT_EQ(borderWidth.leftDimen, 0.0_vp);
    object->OnLanguageConfigurationUpdate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->x.ConvertToPx(), 0.0f);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
    /**
     * @tc.steps: step3. test LTR.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    auto borderWidth2 = object->PostProcessBorderWidth(NG::BorderWidthProperty());
    EXPECT_EQ(borderWidth2.rightDimen, 0.0_vp);
    object->OnLanguageConfigurationUpdate();
    ASSERT_NE(renderContext->GetTransformTranslate(), std::nullopt);
    EXPECT_FLOAT_EQ(
        renderContext->GetTransformTranslate()->x.ConvertToPx(), object->sheetMaxWidth_ - object->sheetWidth_);
    EXPECT_FLOAT_EQ(renderContext->GetTransformTranslate()->y.ConvertToPx(), 0.0f);
}

/**
 * @tc.name: SheetShowInSubwindowTestNg
 * @tc.desc: Test SheetPresentationPattern::UpdateSheetObject
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestNg, UpdateSheetObject, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet pattern and object.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    EXPECT_TRUE(sheetPattern->isFirstInit_);
    auto object1 = AceType::DynamicCast<SheetObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object1, nullptr);
    object1->sheetWidth_ = 10.0f;
    EXPECT_TRUE(object1->GetSheetType() == SheetType::SHEET_BOTTOM);
    auto object2 = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_EQ(object2, nullptr);
    /**
     * @tc.steps: step1. Test object not side sheet.
     */
    sheetPattern->UpdateSheetObject(SheetType::SHEET_BOTTOM);
    auto object3 = AceType::DynamicCast<SheetObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object3, nullptr);
    EXPECT_FLOAT_EQ(object3->sheetWidth_, 10.0f);
    EXPECT_TRUE(object3->GetSheetType() == SheetType::SHEET_BOTTOM);
    sheetPattern->UpdateSheetObject(SheetType::SHEET_CENTER);
    auto object4 = AceType::DynamicCast<SheetObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object4, nullptr);
    EXPECT_FLOAT_EQ(object4->sheetWidth_, 10.0f);
    EXPECT_TRUE(object4->GetSheetType() == SheetType::SHEET_CENTER);
    sheetPattern->ResetScrollUserDefinedIdealSize(object3, object4);
    /**
     * @tc.steps: step2. Test side sheet object, will copy data.
     */
    sheetPattern->UpdateSheetObject(SheetType::SHEET_SIDE);
    auto object5 = AceType::DynamicCast<SheetObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object5, nullptr);
    EXPECT_TRUE(object5->GetSheetType() == SheetType::SHEET_SIDE);
    EXPECT_FLOAT_EQ(object5->sheetWidth_, 10.0f);

    sheetPattern->ResetScrollUserDefinedIdealSize(object4, object5);
    object5->sheetWidth_ = 20.0f;
    sheetPattern->UpdateSheetObject(SheetType::SHEET_POPUP);
    auto object6 = AceType::DynamicCast<SheetObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object6, nullptr);
    EXPECT_TRUE(object6->GetSheetType() == SheetType::SHEET_POPUP);
    EXPECT_FLOAT_EQ(object6->sheetWidth_, 20.0f);
}

/**
 * @tc.type: FUNC
 * @tc.name: Test BindSheet
 * @tc.desc: Test SheetSideObject::AvoidKeyboard.
 */
HWTEST_F(SheetShowInSubwindowTestNg, TestSideSheetAvoidKeyboard1, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node and initialize sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto builderContent =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    builderContent->MountToParent(scroll);
    scroll->MountToParent(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    sheetPattern->UpdateSheetObject(SheetType::SHEET_SIDE);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scroll));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::NONE;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    EXPECT_TRUE(object->GetSheetType() == SheetType::SHEET_SIDE);
    object->AvoidKeyboard(false);
    EXPECT_FALSE(sheetNode->GetFocusHub()->currentFocus_);
    EXPECT_EQ(sheetPattern->GetKeyboardAvoidMode(), SheetKeyboardAvoidMode::NONE);
    /**
     * @tc.cases: case1. sheet focuses but keyboard is not up.
     */
    sheetNode->GetFocusHub()->currentFocus_ = true;
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
    object->AvoidKeyboard(false);
    EXPECT_EQ(sheetPattern->GetKeyboardHeight(), 0);
    object->AvoidKeyboard(true);
    EXPECT_EQ(sheetPattern->GetKeyboardHeight(), 0);
    /**
     * @tc.cases: case2. sheet focuses and keyboard is up.
     */
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    SafeAreaInsets::Inset upKeyboard { 0, 200 };
    safeAreaManager->keyboardInset_ = upKeyboard;
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    object->AvoidKeyboard(false);
    EXPECT_EQ(sheetPattern->keyboardHeight_, 200);
    /**
     * @tc.cases: case3. sheet focuses and keyboard is down.
     */
    SafeAreaInsets::Inset downKeyboard { 0, 0 };
    safeAreaManager->keyboardInset_ = downKeyboard;
    object->AvoidKeyboard(false);
    EXPECT_EQ(sheetPattern->keyboardHeight_, 0);
}

/**
 * @tc.type: FUNC
 * @tc.name: Test BindSheet
 * @tc.desc: Test SheetSideObject::AvoidKeyboard.
 */
HWTEST_F(SheetShowInSubwindowTestNg, TestSideSheetAvoidKeyboard2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet node and initialize sheet pattern.
     */
    auto callback = [](const std::string&) {};
    auto sheetNode = FrameNode::CreateFrameNode(V2::SHEET_PAGE_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<SheetPresentationPattern>(0, "", std::move(callback)));
    ASSERT_NE(sheetNode, nullptr);
    auto scroll = FrameNode::CreateFrameNode(
        V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ScrollPattern>());
    auto builderContent =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    builderContent->MountToParent(scroll);
    scroll->MountToParent(sheetNode);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->InitSheetObject();
    sheetPattern->UpdateSheetObject(SheetType::SHEET_SIDE);
    sheetPattern->SetScrollNode(WeakPtr<FrameNode>(scroll));
    sheetPattern->keyboardAvoidMode_ = SheetKeyboardAvoidMode::RESIZE_ONLY;
    auto object = AceType::DynamicCast<SheetSideObject>(sheetPattern->GetSheetObject());
    ASSERT_NE(object, nullptr);
    EXPECT_TRUE(object->GetSheetType() == SheetType::SHEET_SIDE);
    object->AvoidKeyboard(false);
    EXPECT_FALSE(sheetNode->GetFocusHub()->currentFocus_);
    EXPECT_EQ(sheetPattern->GetKeyboardAvoidMode(), SheetKeyboardAvoidMode::RESIZE_ONLY);
    /**
     * @tc.cases: case1. sheet focuses and keyboard is up.
     */
    sheetNode->GetFocusHub()->currentFocus_ = true;
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    SafeAreaInsets::Inset upKeyboard { 0, 200 };
    safeAreaManager->keyboardInset_ = upKeyboard;
    MockPipelineContext::GetCurrent()->safeAreaManager_ = safeAreaManager;
    MockPipelineContext::GetCurrent()->SetRootSize(800, 2000);
    object->AvoidKeyboard(false);
    EXPECT_EQ(sheetPattern->keyboardHeight_, 200);
    EXPECT_TRUE(NearEqual(object->resizeDecreasedHeight_, 200.0f));
    /**
     * @tc.cases: case2. sheet focuses and keyboard is down.
     */
    SafeAreaInsets::Inset downKeyboard { 0, 0 };
    safeAreaManager->keyboardInset_ = downKeyboard;
    object->AvoidKeyboard(true);
    EXPECT_EQ(sheetPattern->keyboardHeight_, 0);
    EXPECT_TRUE(NearEqual(object->resizeDecreasedHeight_, 0.0f));
}
} // namespace OHOS::Ace::NG