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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components/text_field/textfield_theme.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/rosen/mock_canvas.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Dimension MAGNIFIERNODE_WIDTH = 127.0_vp;
const Dimension MAGNIFIERNODE_HEIGHT = 95.0_vp;
} // namespace

class RichEditorMagnifierTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
private:
    void TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
        const RefPtr<MagnifierController>& controller, const OffsetF& localOffset);
    void InitMagnifierParams(const SizeF& frameSize);
};

void RichEditorMagnifierTest::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorMagnifierTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorMagnifierTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorMagnifierTest::InitMagnifierParams(const SizeF& frameSize)
{
    // set frameSize to RichEditor
    ASSERT_NE(richEditorNode_, nullptr);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(frameSize);

    // set frameSize to RootNode
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto rootUINode = pipeline->GetRootElement();
    ASSERT_NE(rootUINode, nullptr);
    auto rootGeometryNode = rootUINode->GetGeometryNode();
    ASSERT_NE(rootGeometryNode, nullptr);
    rootGeometryNode->SetFrameSize(frameSize);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textfieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textfieldTheme));
}

/**
 * @tc.name: MagnifierTest001
 * @tc.desc: Test magnifier position.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, MagnifierTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto frameSize = SizeF(600.f, 400.f);
    InitMagnifierParams(frameSize);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paintOffset = richEditorPattern->GetTextPaintOffset();

    /**
     * @tc.steps: step1. localOffset is on the far left.
     */
    RefPtr<MagnifierController> controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    float offsetX = MAGNIFIER_OFFSETX.ConvertToPx();
    OffsetF localOffset(offsetX, 0.f);
    OffsetF magnifierOffset(0.f, 0.f);
    controller->SetLocalOffset(localOffset);
    ASSERT_NE(controller->magnifierFrameNode_, nullptr);
    auto geometryNode = controller->magnifierFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetX(), paintOffset.GetX() - 1.0f);

    /**
     * @tc.steps: step2. localOffset is in the normal area.
     */
    localOffset.SetX(MAGNIFIERNODE_WIDTH.ConvertToPx());
    controller->SetLocalOffset(localOffset);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetX(),
        paintOffset.GetX() + localOffset.GetX() - MAGNIFIERNODE_WIDTH.ConvertToPx() / 2);

    /**
     * @tc.steps: step3. localOffset is on the far right.
     */
    localOffset.SetX(frameSize.Width());
    controller->SetLocalOffset(localOffset);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetX(), paintOffset.GetX() + frameSize.Width() - MAGNIFIERNODE_WIDTH.ConvertToPx());
}

/**
 * @tc.name: MagnifierTest002
 * @tc.desc: Test magnifier position.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, MagnifierTest002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto frameSize = SizeF(600.f, 400.f);
    InitMagnifierParams(frameSize);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paintOffset = richEditorPattern->GetTextPaintOffset();

    /**
     * @tc.steps: step1. localOffset is on the top.
     */
    float offsetY = 1.f;
    OffsetF localOffset(100.f, offsetY);
    OffsetF magnifierOffset(0.f, 0.f);
    RefPtr<MagnifierController> controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->SetLocalOffset(localOffset);
    ASSERT_NE(controller->magnifierFrameNode_, nullptr);
    auto geometryNode = controller->magnifierFrameNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetY(), 0.f);

    /**
     * @tc.steps: step2. localOffset is in the normal area.
     */
    localOffset.SetY(MAGNIFIER_OFFSETY.ConvertToPx() + MAGNIFIERNODE_HEIGHT.ConvertToPx());
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto displayInfo = container->GetDisplayInfo();
    ASSERT_NE(displayInfo, nullptr);
    auto height = displayInfo->GetHeight();
    displayInfo->SetHeight(1280);
    controller->SetLocalOffset(localOffset);
    displayInfo->SetHeight(height);
    magnifierOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(magnifierOffset.GetY(), paintOffset.GetY() + localOffset.GetY() - MAGNIFIERNODE_HEIGHT.ConvertToPx() / 2
        - MAGNIFIER_OFFSETY.ConvertToPx());

    /**
     * @tc.steps: step3. Test cases of magnifier.
     */
    TestMagnifier(richEditorPattern, controller, localOffset);
}

void RichEditorMagnifierTest::TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
    const RefPtr<MagnifierController>& controller, const OffsetF& localOffset)
{
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    richEditorPattern->HandleSurfaceChanged(1, 1, 1, 1, WindowSizeChangeReason::DRAG);
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutWrapper->skipMeasureContent_ = false;
    DirtySwapConfig config;
    config.frameSizeChange = true;

    richEditorPattern->selectOverlay_->isHandleMoving_ = true;
    richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(controller->GetShowMagnifier());

    richEditorPattern->selectOverlay_->isHandleMoving_ = false;
    richEditorPattern->isCursorAlwaysDisplayed_ = true;
    richEditorPattern->moveCaretState_.isMoveCaret = true;
    richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(controller->GetShowMagnifier());
    EXPECT_FALSE(richEditorPattern->isCursorAlwaysDisplayed_);
}

/**
 * @tc.name: UpdateMagnifierStateAfterLayout001
 * @tc.desc: test UpdateMagnifierStateAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, UpdateMagnifierStateAfterLayout001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<TextBase> textBase;
    richEditorPattern->selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(textBase);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->UpdateMagnifierStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: UpdateMagnifierStateAfterLayout002
 * @tc.desc: test UpdateMagnifierStateAfterLayout
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, UpdateMagnifierStateAfterLayout002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<TextBase> textBase;
    richEditorPattern->selectOverlay_ = AceType::MakeRefPtr<RichEditorSelectOverlay>(textBase);
    WeakPtr<Pattern> pattern;
    richEditorPattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    richEditorPattern->magnifierController_->magnifierNodeExist_ = true;
    richEditorPattern->UpdateMagnifierStateAfterLayout(true);
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->HandleSurfaceChanged(1, 1, 2, 2, WindowSizeChangeReason::DRAG);
    EXPECT_FALSE(richEditorPattern->originIsMenuShow_);
}

/**
 * @tc.name: HandleSurfaceChanged002
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, HandleSurfaceChanged002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    richEditorPattern->HandleSurfaceChanged(0, 0, 0, 0, WindowSizeChangeReason::DRAG);

    EXPECT_EQ(richEditorPattern->magnifierController_->GetShowMagnifier(), false);
}

}