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

#include "core/common/ace_engine.h"
#include "base/geometry/dimension.h"
#include "frameworks/base/subwindow/subwindow_manager.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
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
class SheetShowInSubwindowTestOneNg : public testing::Test {
public:
    static int32_t lastPlatformVersion_;

    static void SetUpTestSuite();
    static void TearDownTestSuite();
    std::function<RefPtr<UINode>(int32_t id)> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
    static void SetSheetTheme(RefPtr<SheetTheme> sheetTheme);
    static void SetApiVersion(int32_t apiTargetVersion);
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

int32_t SheetShowInSubwindowTestOneNg::lastPlatformVersion_ = 0;

/**
 * @brief: Called once before executing the entire test suite
 * @note: All TEST_F shared.
 *        Initialize the global commons.
 */
void SheetShowInSubwindowTestOneNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    SheetShowInSubwindowTestOneNg::lastPlatformVersion_ = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
}

/**
 * @brief: Called once after executing the entire test suite
 * @note: All TEST_F shared.
 *        Clean up the global commons.
 */
void SheetShowInSubwindowTestOneNg::TearDownTestSuite()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

// Before each TEST_F, the scope is a single test case
void SheetShowInSubwindowTestOneNg::SetUp() {}

// After each TEST_F, the scope is a single test case
void SheetShowInSubwindowTestOneNg::TearDown()
{
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(SheetShowInSubwindowTestOneNg::lastPlatformVersion_);
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
}

void SheetShowInSubwindowTestOneNg::SetSheetTheme(RefPtr<SheetTheme> sheetTheme)
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

void SheetShowInSubwindowTestOneNg::CreateSheetBuilder(float builderHeight, float titleHeight)
{
    auto builderFunc = [builderHeight](int32_t id) -> RefPtr<UINode> {
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

void SheetShowInSubwindowTestOneNg::InitSheetAndWrapperLayoutInfo(const RefPtr<FrameNode>& sheetPageNode,
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

RefPtr<FrameNode> SheetShowInSubwindowTestOneNg::InitTargetNodeEnv(RefPtr<FrameNode>& rootNode, const SizeF& rootSize,
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

void SheetShowInSubwindowTestOneNg::SetApiVersion(int32_t apiTargetVersion)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(apiTargetVersion);
}

HWTEST_F(SheetShowInSubwindowTestOneNg, RemoveSheet001, TestSize.Level1)
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

HWTEST_F(SheetShowInSubwindowTestOneNg, RemoveSheet002, TestSize.Level1)
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

HWTEST_F(SheetShowInSubwindowTestOneNg, InitSheetWrapperAction001, TestSize.Level1)
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
    SheetShowInSubwindowTestOneNg::SetSheetTheme(sheetTheme);
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

HWTEST_F(SheetShowInSubwindowTestOneNg, InitSheetWrapperAction002, TestSize.Level1)
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
    SheetShowInSubwindowTestOneNg::SetSheetTheme(sheetTheme);
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

/**
 * @tc.name: GetSheetTypeNumber1
 * @tc.desc: Test SheetPresentationPattern::GetSheetType.
 *           Condition: The default is Bottom Type
 * @tc.type: FUNC
 */
HWTEST_F(SheetShowInSubwindowTestOneNg, GetSheetTypeNumber1, TestSize.Level1)
{
    SheetShowInSubwindowTestOneNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
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
    sheetStyle.bottomOffset = OffsetF(0, -10);
    SystemProperties::SetDeviceType(DeviceType::TWO_IN_ONE);
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
HWTEST_F(SheetShowInSubwindowTestOneNg, GetSheetTypeNumber2, TestSize.Level1)
{
    SheetShowInSubwindowTestOneNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
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
    SheetShowInSubwindowTestOneNg::SetSheetTheme(sheetTheme);
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
HWTEST_F(SheetShowInSubwindowTestOneNg, GetSheetTypeNumber3, TestSize.Level1)
{
    SheetShowInSubwindowTestOneNg::SetApiVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));

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
HWTEST_F(SheetShowInSubwindowTestOneNg, GetSheetTypeNumber4, TestSize.Level1)
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
    SheetShowInSubwindowTestOneNg::SetSheetTheme(sheetTheme);

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
HWTEST_F(SheetShowInSubwindowTestOneNg, GetSheetTypeNumber5, TestSize.Level1)
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
    SheetShowInSubwindowTestOneNg::SetSheetTheme(sheetTheme);

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
} // namespace OHOS::Ace::NG