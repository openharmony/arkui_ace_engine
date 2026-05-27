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

#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components/text_field/textfield_theme.h"
#include "test/mock/frameworks/core/common/mock_data_detector_mgr.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
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
 * @tc.name: MagnifierTest003
 * @tc.desc: Test magnifier position.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, MagnifierTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get rich editor pattern.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto frameSize = SizeF(600.f, 400.f);
    InitMagnifierParams(frameSize);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. get magnifier controller.
     */
    RefPtr<MagnifierController> controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->OpenMagnifier();
    auto magnifierNode = controller->magnifierFrameNode_;
    controller->colorModeChange_ = true;
    controller->OpenMagnifier();
    EXPECT_EQ(controller->colorModeChange_, false);
    EXPECT_NE(magnifierNode, controller->magnifierFrameNode_);
}

void RichEditorMagnifierTest::TestMagnifier(const RefPtr<RichEditorPattern>& richEditorPattern,
    const RefPtr<MagnifierController>& controller, const OffsetF& localOffset)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    MockPipelineContext::GetCurrent()->SetTextFieldManager(textFieldManager);
    richEditorPattern->selectOverlay_->isHandleMoving_ = false;
    EXPECT_FALSE(richEditorPattern->IsHandleMoving());
    richEditorPattern->HandleTouchUp();
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(controller->GetShowMagnifier());

    controller->SetLocalOffset(localOffset);
    richEditorPattern->HandleSurfaceChanged(1, 1, 1, 1);
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

    // The magnifier does not close by touch up while handle moving.
    richEditorPattern->selectOverlay_->isHandleMoving_ = true;
    richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(controller->GetShowMagnifier());
    EXPECT_TRUE(richEditorPattern->IsHandleMoving());
    richEditorPattern->HandleTouchUp();
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
HWTEST_F(RichEditorMagnifierTest, UpdateMagnifierStateAfterLayout001, TestSize.Level2)
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
HWTEST_F(RichEditorMagnifierTest, UpdateMagnifierStateAfterLayout002, TestSize.Level2)
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
HWTEST_F(RichEditorMagnifierTest, HandleSurfaceChanged001, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->magnifierController_.Reset();
    richEditorPattern->UpdateOriginIsMenuShow(true);
    richEditorPattern->HandleSurfaceChanged(1, 1, 2, 2);
    EXPECT_FALSE(richEditorPattern->originIsMenuShow_);
}

/**
 * @tc.name: HandleSurfaceChanged002
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorMagnifierTest, HandleSurfaceChanged002, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->UpdateOriginIsMenuShow(true);
    richEditorPattern->magnifierController_->isShowMagnifier_ = true;
    richEditorPattern->magnifierController_->magnifierNodeExist_ = true;
    richEditorPattern->HandleSurfaceChanged(0, 0, 0, 0);

    EXPECT_TRUE(richEditorPattern->originIsMenuShow_);
    EXPECT_FALSE(richEditorPattern->magnifierController_->GetMagnifierNodeExist());
    EXPECT_EQ(richEditorPattern->magnifierController_->GetShowMagnifier(), false);
}

}
