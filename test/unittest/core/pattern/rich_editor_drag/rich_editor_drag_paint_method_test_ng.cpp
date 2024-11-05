/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "rich_editor_drag_paint_method_test_ng.h"

#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr float ROOT_WIDTH = 400.f;
    constexpr float ROOT_HEIGHT = 800.f;
}

void RichEditorDragPaintMethodTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void RichEditorDragPaintMethodTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void RichEditorDragPaintMethodTestNG::SetUp() {}

void RichEditorDragPaintMethodTestNG::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    dragNode_ = nullptr;
}

void RichEditorDragPaintMethodTestNG::ClearSpan()
{
    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    frameNode_->children_.clear();
    pattern_->spans_.clear();
    pattern_->caretPosition_ = 0;
}

void RichEditorDragPaintMethodTestNG::InitDate()
{
    ViewAbstract::SetWidth(CalcLength(ROOT_WIDTH));
    ViewAbstract::SetHeight(CalcLength(ROOT_HEIGHT));
    RichEditorModelNG model;
    model.Create();
    model.SetTextDetectEnable(true);
    frameNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    pattern_ = frameNode_->GetPattern<RichEditorPattern>();
    RefPtr<TextDragOverlayModifier> textGragOverlayModifier =
        AceType::MakeRefPtr<TextDragOverlayModifier>(pattern_);
    RefPtr<RichEditorDragContentModifier> richContentModifier =
        AceType::MakeRefPtr<RichEditorDragContentModifier>();
    RichEditorDragInfo info;
    richGragPaintMethod_ =
        AceType::MakeRefPtr<RichEditorDragPaintMethod>(pattern_, textGragOverlayModifier, richContentModifier, info);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test function UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragPaintMethodTestNG, UpdateContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init frameNode_ 、pattern_ and richGragPaintMethod_.
     */
    InitDate();

    /**
     * @tc.steps: step2. call function UpdateContentModifier.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = pattern_->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    richGragPaintMethod_->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_TRUE(richGragPaintMethod_->overlayModifier_ != nullptr);
}

/**
 * @tc.name: GetContentModifier001
 * @tc.desc: Test function GetContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorDragPaintMethodTestNG, GetContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init frameNode_ 、pattern_ and richGragPaintMethod_.
     */
    InitDate();

    /**
     * @tc.steps: step2. call function GetContentModifier.
     */
    auto testContentModifier = richGragPaintMethod_->GetContentModifier(nullptr);
    ASSERT_NE(testContentModifier, nullptr);
}
} // namespace OHOS::Ace::NG