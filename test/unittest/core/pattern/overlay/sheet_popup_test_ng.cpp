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

#define private public
#define protected public
#include "test/mock/base/mock_foldable_window.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Dimension WINDOW_EDGE_SPACE = 6.0_vp;
} // namespace
class SheetPopupTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    std::function<RefPtr<UINode>()> builderFunc_;
    std::function<RefPtr<UINode>()> titleBuilderFunc_;
protected:
    static RefPtr<FrameNode> InitTargetNodeEnv(RefPtr<FrameNode>& rootNode, const SizeF& rootSize,
        const OffsetF& rootOffset, const SizeF& targetSize, const OffsetF& targetOffset);
    static void CreateSheetStyle(SheetStyle& sheetStyle, const Dimension& width, const Dimension& height);
    void CreateSheetBuilder(float builderHeight = 800.f, float titleHeight = 800.f);
    static void InitSheetAndWrapperLayoutInfo(
        const RefPtr<FrameNode>& sheetPageNode, const RefPtr<FrameNode>& sheetWrapperNode,
        RefPtr<SheetPresentationLayoutAlgorithm>& sheetPageLayoutAlgorithm,
        RefPtr<SheetWrapperLayoutAlgorithm>& sheetWrapperLayoutAlgorithm);
};

void SheetPopupTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_SIXTEEN));
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_SIXTEEN);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == SheetTheme::TypeId()) {
            auto sheetTheme = AceType::MakeRefPtr<SheetTheme>();
            sheetTheme->sheetType_ = "auto";
            sheetTheme->sheetBottom_ = "auto";
            return sheetTheme;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SheetPopupTestNg::TearDownTestCase()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> SheetPopupTestNg::InitTargetNodeEnv(RefPtr<FrameNode>& rootNode, const SizeF& rootSize,
    const OffsetF& rootOffset, const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto targetNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
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

void SheetPopupTestNg::CreateSheetStyle(SheetStyle& sheetStyle, const Dimension& width, const Dimension& height)
{
    if (!sheetStyle.showDragBar.has_value()) {
        sheetStyle.showDragBar = true;
    }
    if (!sheetStyle.sheetType.has_value()) {
        sheetStyle.sheetType = SheetType::SHEET_POPUP;
    }
    sheetStyle.sheetHeight.sheetMode.reset();
    sheetStyle.width = width;
    sheetStyle.sheetHeight.height = height;
}

void SheetPopupTestNg::CreateSheetBuilder(float builderHeight, float titleHeight)
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

void SheetPopupTestNg::InitSheetAndWrapperLayoutInfo(
    const RefPtr<FrameNode>& sheetPageNode, const RefPtr<FrameNode>& sheetWrapperNode,
    RefPtr<SheetPresentationLayoutAlgorithm>& sheetPageLayoutAlgorithm,
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

/**
 * @tc.name: GetPopupStyleSheetOffset001
 * @tc.desc: Branch: if (GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                      (CheckDirectionBottomNew == True);
 *           Condition: placement == Bottom, placemenntOnTarget == true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetPopupStyleSheetOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    // targetOffset determines bottom space is enough to layout sheetPage
    OffsetF targetOffset = OffsetF(1450.f, 200.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetCurrentWindowRect(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    sheetStyle.placement = Placement::BOTTOM;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
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
    sheetPattern->sheetThemeType_ = "popup";
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    sheetWrapperNode->Measure(sheetWrapperNode->GetLayoutConstraint());
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetHeight_, sheetPageHeight.ConvertToPx()));
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->placement_, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget, true);

    sheetWrapperNode->Layout();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow, true);
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    auto resizeHeight = sheetPageHeight.ConvertToPx() + SHEET_ARROW_HEIGHT.ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetHeight_, resizeHeight));
    auto expectedOffsetX = targetOffset.GetX() + targetSize.Width() / 2.0 - sheetPageWidth.ConvertToPx() / 2.0;
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetX, expectedOffsetX));
    auto expectedOffsetY = targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetY, expectedOffsetY));

    /**
     * @tc.steps: step4. recover container and pipeline info.
     */
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetOffset002
 * @tc.desc: Branch: if (GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                      (CheckDirectionBottomNew == False);
 *           Condition: placement == Bottom, placemenntOnTarget == true
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetPopupStyleSheetOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    // targetOffset determines every space is not enough to layout sheetPage
    OffsetF targetOffset = OffsetF(1450.f, 1500.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetCurrentWindowRect(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    sheetStyle.placement = Placement::BOTTOM;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: measure and layout sheet page
     * @tc.expected: finalPlacement == Bottom and showArrow == false
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetThemeType_ = "popup";
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    sheetWrapperNode->Measure(sheetWrapperNode->GetLayoutConstraint());
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetHeight_, sheetPageHeight.ConvertToPx()));
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->placement_, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget, true);

    sheetWrapperNode->Layout();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow, false);
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetHeight_, sheetPageHeight.ConvertToPx()));
    auto expectedOffsetX = targetOffset.GetX() + targetSize.Width() / 2.0 - sheetPageWidth.ConvertToPx() / 2.0;
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetX, expectedOffsetX));
    auto expectedOffsetY = sheetWrapperLayoutAlgorithm->windowGlobalRect_.Height() +
        sheetWrapperLayoutAlgorithm->windowGlobalRect_.Top() -
        sheetWrapperLayoutAlgorithm->sheetHeight_ - WINDOW_EDGE_SPACE.ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetY, expectedOffsetY));

    /**
     * @tc.steps: step4. recover container and pipeline info.
     */
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetOffset003
 * @tc.desc: Branch: if (GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                      (CheckDirectionBottomNew == False);
 *           Condition: placement == Bottom, placemenntOnTarget == false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetPopupStyleSheetOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    // targetOffset determines every space is not enough to layout sheetPage, but bottom height is biggest
    OffsetF targetOffset = OffsetF(1450.f, 1400.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetCurrentWindowRect(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    sheetStyle.placement = Placement::BOTTOM;
    sheetStyle.placementOnTarget = false;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: measure and layout sheet page
     * @tc.expected: finalPlacement == Bottom and showArrow == false
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetThemeType_ = "popup";
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    sheetWrapperNode->Measure(sheetWrapperNode->GetLayoutConstraint());
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetHeight_, sheetPageHeight.ConvertToPx()));
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->placement_, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget, false);

    sheetWrapperNode->Layout();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow, true);
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    auto resizeHeight = sheetWrapperLayoutAlgorithm->windowGlobalRect_.Height() +
        sheetWrapperLayoutAlgorithm->windowGlobalRect_.Top() - targetOffset.GetY() - targetSize.Height() -
        (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetHeight_, resizeHeight));
    auto expectedOffsetX = targetOffset.GetX() + targetSize.Width() / 2.0 - sheetPageWidth.ConvertToPx() / 2.0;
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetX, expectedOffsetX));
    auto expectedOffsetY = targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetY, expectedOffsetY));

    /**
     * @tc.steps: step4. recover container and pipeline info.
     */
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetPopupStyleSheetOffset004
 * @tc.desc: Branch: if (GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                      (CheckDirectionBottomNew == False);
 *           Condition: placement == Bottom, placemenntOnTarget == false
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetPopupStyleSheetOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    // targetOffset determines every space is not enough to layout sheetPage, but top height is biggest
    OffsetF targetOffset = OffsetF(1450.f, 1500.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetCurrentWindowRect(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    sheetStyle.placement = Placement::BOTTOM;
    sheetStyle.placementOnTarget = false;
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: measure and layout sheet page
     * @tc.expected: finalPlacement == Bottom and showArrow == false
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetPattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    sheetPattern->sheetThemeType_ = "popup";
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    sheetWrapperNode->Measure(sheetWrapperNode->GetLayoutConstraint());
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetHeight_, sheetPageHeight.ConvertToPx()));
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->placement_, Placement::BOTTOM);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.placementOnTarget, false);

    sheetWrapperNode->Layout();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.finalPlacement, Placement::TOP);
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.showArrow, true);
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetWidth_, sheetPageWidth.ConvertToPx()));
    auto resizeHeight = targetOffset.GetY() - sheetWrapperLayoutAlgorithm->windowGlobalRect_.Top() -
        (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetPageLayoutAlgorithm->sheetHeight_, resizeHeight));
    auto expectedOffsetX = targetOffset.GetX() + targetSize.Width() / 2.0 - sheetPageWidth.ConvertToPx() / 2.0;
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetX, expectedOffsetX));
    auto expectedOffsetY = sheetWrapperLayoutAlgorithm->windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx();
    EXPECT_TRUE(NearEqual(sheetWrapperLayoutAlgorithm->sheetPopupInfo_.sheetOffsetY, expectedOffsetY));

    /**
     * @tc.steps: step4. recover container and pipeline info.
     */
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetInAvoidanceRule001
 * @tc.desc: Branch: if (LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                  getOffsetFunc == GetOffsetWithBottom()
 *           Condition: sheetType == Popup
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetOffsetInAvoidanceRule001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    auto lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: create layout and pattern info
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);

    /**
     * @tc.steps: step4: create layout and pattern info
     * @tc.expected: get offset correctly
     */
    auto targetPlacement =
        sheetWrapperLayoutAlgorithm->AvoidanceRuleBottom(Placement::BOTTOM, targetSize, targetOffset);
    EXPECT_NE(sheetWrapperLayoutAlgorithm->getOffsetFunc_.find(targetPlacement),
        sheetWrapperLayoutAlgorithm->getOffsetFunc_.end());
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        sheetWrapperNode, sheetWrapperNode->GetGeometryNode(), sheetWrapperNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto realOffset =
        sheetWrapperLayoutAlgorithm->GetOffsetInAvoidanceRule(layoutWrapper.rawPtr_, targetSize, targetOffset);
    auto expectedOffset = OffsetF(
        targetOffset.GetX() + (targetSize.Width() - sheetWrapperLayoutAlgorithm->sheetWidth_) / 2.0,
        targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());
    EXPECT_EQ(realOffset, expectedOffset);

    sheetWrapperLayoutAlgorithm->getOffsetFunc_.clear();
    EXPECT_EQ(sheetWrapperLayoutAlgorithm->getOffsetFunc_.find(targetPlacement),
        sheetWrapperLayoutAlgorithm->getOffsetFunc_.end());
    realOffset = sheetWrapperLayoutAlgorithm->GetOffsetInAvoidanceRule(layoutWrapper.rawPtr_, targetSize, targetOffset);
    expectedOffset = OffsetF(0.f, 0.f);
    EXPECT_EQ(realOffset, expectedOffset);

    /**
     * @tc.steps: step5. recover api version info.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithBottomLeft001
 * @tc.desc: Branch: if (LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                  getOffsetFunc == GetOffsetWithBottomLeft()
 *           Condition: sheetType == Popup
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetOffsetWithBottomLeft001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    auto lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));


    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: create layout and pattern info
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);

    /**
     * @tc.steps: step4: test func GetOffsetWithBottomLeft
     * @tc.expected: get offset correctly and arrow offset set correctly
     */
    auto targetPlacement = Placement::BOTTOM_LEFT;
    EXPECT_NE(sheetWrapperLayoutAlgorithm->getOffsetFunc_.find(targetPlacement),
        sheetWrapperLayoutAlgorithm->getOffsetFunc_.end());
    sheetWrapperLayoutAlgorithm->sheetRadius_ = BorderRadiusProperty(Dimension(10));
    Dimension arrowVertical = 8.0_vp;
    float arrowOffsetX = 25.0;
    EXPECT_FALSE(LessNotEqual(arrowOffsetX - arrowVertical.ConvertToPx(),
        sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft->ConvertToPx()));

    auto realOffset = sheetWrapperLayoutAlgorithm->GetOffsetWithBottomLeft(targetSize, targetOffset);
    auto expectedOffset = OffsetF(targetOffset.GetX(),
        targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());
    EXPECT_EQ(realOffset, expectedOffset);

    sheetWrapperLayoutAlgorithm->sheetRadius_ = BorderRadiusProperty(Dimension(100));
    EXPECT_TRUE(LessNotEqual(arrowOffsetX - arrowVertical.ConvertToPx(),
        sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopLeft->ConvertToPx()));
    sheetWrapperLayoutAlgorithm->GetOffsetWithBottomLeft(targetSize, targetOffset);
    
    /**
     * @tc.steps: step5. recover api version info.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: GetOffsetWithBottomRight001
 * @tc.desc: Branch: if (LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                  getOffsetFunc == GetOffsetWithBottomRight001()
 *           Condition: sheetType == Popup
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, GetOffsetWithBottomRight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    auto lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: create layout and pattern info
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);
    auto layoutProperty = sheetPageNode->GetLayoutProperty<SheetPresentationProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSheetStyle(sheetStyle);

    /**
     * @tc.steps: step4: test func GetOffsetWithBottomRight
     * @tc.expected: get offset correctly and arrow offset set correctly
     */
    auto targetPlacement = Placement::BOTTOM_RIGHT;
    EXPECT_NE(sheetWrapperLayoutAlgorithm->getOffsetFunc_.find(targetPlacement),
        sheetWrapperLayoutAlgorithm->getOffsetFunc_.end());
    sheetWrapperLayoutAlgorithm->sheetRadius_ = BorderRadiusProperty(Dimension(10));
    Dimension arrowVertical = 8.0_vp;
    float arrowOffsetX = 25.0;
    sheetWrapperLayoutAlgorithm->sheetWidth_ = 200;
    EXPECT_FALSE(GreatNotEqual(arrowOffsetX + sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight->ConvertToPx() +
        arrowVertical.ConvertToPx(), sheetWrapperLayoutAlgorithm->sheetWidth_));

    auto realOffset = sheetWrapperLayoutAlgorithm->GetOffsetWithBottomRight(targetSize, targetOffset);
    auto expectedOffset = OffsetF(targetOffset.GetX(),
        targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());
    EXPECT_EQ(realOffset, expectedOffset);

    sheetWrapperLayoutAlgorithm->sheetRadius_ = BorderRadiusProperty(Dimension(200));
    EXPECT_TRUE(GreatNotEqual(arrowOffsetX + sheetWrapperLayoutAlgorithm->sheetRadius_.radiusTopRight->ConvertToPx() +
        arrowVertical.ConvertToPx(), sheetWrapperLayoutAlgorithm->sheetWidth_));
    sheetWrapperLayoutAlgorithm->GetOffsetWithBottomRight(targetSize, targetOffset);
    
    /**
     * @tc.steps: step5. recover api version info.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
    SheetPopupTestNg::TearDownTestCase();
}

/**
 * @tc.name: AvoidanceRuleBottom001
 * @tc.desc: Branch: if (LessThanAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) &&
 *                  getOffsetFunc == GetOffsetWithBottomRight001()
 *           Condition: sheetType == Popup
 * @tc.type: FUNC
 */
HWTEST_F(SheetPopupTestNg, AvoidanceRuleBottom001, TestSize.Level1)
{
    /**
     * @tc.steps: step1: create root and target node, init builder func, set api version 12
     * @tc.expected: targetNode != nullptr
     */
    SheetPopupTestNg::SetUpTestCase();
    auto lastPlatformVersion = PipelineBase::GetCurrentContext()->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    SizeF rootSize = SizeF(3000.f, 3000.f);
    OffsetF rootOffset = OffsetF(0.f, 0.f);
    SizeF targetSize = SizeF(200.f, 80.f);
    OffsetF targetOffset = OffsetF(1450.f, 200.f);

    auto pipelineContext = MockPipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->SetDisplayWindowRectInfo(Rect(0.f, 0.f, 3000.f, 3000.f));
    MockPipelineContext::GetCurrent()->SetRootSize(rootSize.Width(), rootSize.Height());

    auto containerId = Container::CurrentId();
    auto foldablewindow = AceType::DynamicCast<MockFoldableWindow>(FoldableWindow::CreateFoldableWindow(containerId));
    EXPECT_CALL(*foldablewindow, IsFoldExpand()).WillRepeatedly([]() -> bool { return true; });

    RefPtr<FrameNode> rootNode;
    auto targetNode = InitTargetNodeEnv(rootNode, rootSize, rootOffset, targetSize, targetOffset);
    ASSERT_NE(targetNode, nullptr);
    
    CreateSheetBuilder();

    /**
     * @tc.steps: step2: init sheet size and bind sheet
     * @tc.expected: bindSheet create success
     */
    SheetStyle sheetStyle;
    Dimension sheetPageWidth = Dimension(1600.f, DimensionUnit::PX);
    Dimension sheetPageHeight = Dimension(1600.f, DimensionUnit::PX);
    CreateSheetStyle(sheetStyle, sheetPageWidth, sheetPageHeight);
    bool isShow = true;
    auto overlayManager = AceType::MakeRefPtr<OverlayManager>(rootNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->OnBindSheet(isShow, nullptr, std::move(builderFunc_), std::move(titleBuilderFunc_), sheetStyle,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, targetNode);
    EXPECT_FALSE(overlayManager->modalStack_.empty());

    /**
     * @tc.steps: step3: create layout and pattern info
     */
    auto sheetPageNode = overlayManager->modalStack_.top().Upgrade();
    ASSERT_NE(sheetPageNode, nullptr);
    auto sheetWrapperNode = AceType::DynamicCast<FrameNode>(sheetPageNode->GetParent());
    ASSERT_NE(sheetWrapperNode, nullptr);
    RefPtr<SheetPresentationLayoutAlgorithm> sheetPageLayoutAlgorithm;
    RefPtr<SheetWrapperLayoutAlgorithm> sheetWrapperLayoutAlgorithm;
    InitSheetAndWrapperLayoutInfo(sheetPageNode, sheetWrapperNode,
        sheetPageLayoutAlgorithm, sheetWrapperLayoutAlgorithm);

    /**
     * @tc.steps: step4: test different func of direction and placement check
     * @tc.expected: get offset correctly and arrow offset set correctly
     */
    sheetWrapperLayoutAlgorithm->directionCheckFunc_[Placement::BOTTOM] =
        &SheetWrapperLayoutAlgorithm::CheckPlacementBottomLeft;
    sheetWrapperLayoutAlgorithm->placementCheckFunc_[Placement::BOTTOM] =
        &SheetWrapperLayoutAlgorithm::CheckPlacementBottomLeft;
    targetOffset = OffsetF(WINDOW_EDGE_SPACE.ConvertToPx() - 1.0f, 1.0f);
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->CheckPlacementBottomLeft(SizeF(), targetOffset));
    sheetWrapperLayoutAlgorithm->AvoidanceRuleBottom(Placement::BOTTOM, SizeF(), targetOffset);

    targetOffset.x_ = WINDOW_EDGE_SPACE.ConvertToPx() + 1.0f;
    pipelineContext->displayWindowRectInfo_.width_ = 2 * WINDOW_EDGE_SPACE.ConvertToPx() +
        sheetWrapperLayoutAlgorithm->sheetWidth_ + 1.0f;
    EXPECT_FALSE(sheetWrapperLayoutAlgorithm->CheckPlacementBottomLeft(SizeF(), targetOffset));
    sheetWrapperLayoutAlgorithm->AvoidanceRuleBottom(Placement::BOTTOM, SizeF(), targetOffset);

    sheetWrapperLayoutAlgorithm->directionCheckFunc_[Placement::BOTTOM] = nullptr;
    sheetWrapperLayoutAlgorithm->placementCheckFunc_[Placement::BOTTOM] = nullptr;
    sheetWrapperLayoutAlgorithm->AvoidanceRuleBottom(Placement::BOTTOM, SizeF(), OffsetF());
    
    /**
     * @tc.steps: step5. recover api version info.
     */
    PipelineBase::GetCurrentContext()->SetMinPlatformVersion(lastPlatformVersion);
    MockContainer::Current()->SetApiTargetVersion(lastPlatformVersion);
    // SheetPopupTestNg::TearDownTestCase();
}
} // namespace OHOS::Ace::NG