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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "test/mock/frameworks/core/rosen/mock_canvas.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorTransformTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    void InitManagerAndBind(RefPtr<RichEditorPattern>& richEditorPattern, RefPtr<SelectContentOverlayManager>& manager);
    void SetupHandleInfoWithTransform(RefPtr<SelectContentOverlayManager>& manager,
        bool firstShow, bool secondShow, const RectF& firstRect, const RectF& secondRect);
    void SetupHandleInfoWithoutTransform(RefPtr<SelectContentOverlayManager>& manager,
        bool firstShow, bool secondShow, const RectF& firstRect, const RectF& secondRect);
};

void RichEditorTransformTestNg::SetUp()
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

void RichEditorTransformTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorTransformTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorTransformTestNg::InitManagerAndBind(RefPtr<RichEditorPattern>& richEditorPattern,
    RefPtr<SelectContentOverlayManager>& manager)
{
    manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    richEditorPattern->selectOverlay_->OnBind(manager);
}

void RichEditorTransformTestNg::SetupHandleInfoWithTransform(RefPtr<SelectContentOverlayManager>& manager,
    bool firstShow, bool secondShow, const RectF& firstRect, const RectF& secondRect)
{
    manager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>();
    manager->shareOverlayInfo_->firstHandle.isShow = firstShow;
    manager->shareOverlayInfo_->firstHandle.paintRect = firstRect;
    manager->shareOverlayInfo_->firstHandle.isPaintHandleWithPoints = true;
    manager->shareOverlayInfo_->firstHandle.paintInfo.startPoint =
        OffsetF(firstRect.GetX(), firstRect.GetY());
    manager->shareOverlayInfo_->firstHandle.paintInfo.endPoint =
        OffsetF(firstRect.GetX(), firstRect.GetY() + firstRect.Height());
    manager->shareOverlayInfo_->firstHandle.paintInfo.width = firstRect.Width();
    manager->shareOverlayInfo_->secondHandle.isShow = secondShow;
    manager->shareOverlayInfo_->secondHandle.paintRect = secondRect;
    manager->shareOverlayInfo_->secondHandle.isPaintHandleWithPoints = true;
    manager->shareOverlayInfo_->secondHandle.paintInfo.startPoint =
        OffsetF(secondRect.GetX(), secondRect.GetY());
    manager->shareOverlayInfo_->secondHandle.paintInfo.endPoint =
        OffsetF(secondRect.GetX(), secondRect.GetY() + secondRect.Height());
    manager->shareOverlayInfo_->secondHandle.paintInfo.width = secondRect.Width();
}

void RichEditorTransformTestNg::SetupHandleInfoWithoutTransform(RefPtr<SelectContentOverlayManager>& manager,
    bool firstShow, bool secondShow, const RectF& firstRect, const RectF& secondRect)
{
    manager->shareOverlayInfo_ = std::make_shared<SelectOverlayInfo>();
    manager->shareOverlayInfo_->firstHandle.isShow = firstShow;
    manager->shareOverlayInfo_->firstHandle.paintRect = firstRect;
    manager->shareOverlayInfo_->firstHandle.isPaintHandleWithPoints = false;
    manager->shareOverlayInfo_->secondHandle.isShow = secondShow;
    manager->shareOverlayInfo_->secondHandle.paintRect = secondRect;
    manager->shareOverlayInfo_->secondHandle.isPaintHandleWithPoints = false;
}

/**
 * @tc.name: SetHandleInfo001
 * @tc.desc: test SetHandleInfo with hasTransform=true, isPaintHandleWithPoints=true, both handles shown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, SetHandleInfo001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    RectF firstRect(10.0f, 10.0f, 5.0f, 20.0f);
    RectF secondRect(100.0f, 10.0f, 5.0f, 20.0f);
    SetupHandleInfoWithTransform(manager, true, true, firstRect, secondRect);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    TextDragInfo info;
    richEditorPattern->SetHandleInfo(info);

    EXPECT_EQ(info.firstHandle.GetX(), 10.0f);
    EXPECT_EQ(info.firstHandle.GetY(), 10.0f);
    EXPECT_EQ(info.secondHandle.GetX(), 100.0f);
    EXPECT_EQ(info.secondHandle.GetY(), 10.0f);
}

/**
 * @tc.name: SetHandleInfo002
 * @tc.desc: test SetHandleInfo with hasTransform=true, isPaintHandleWithPoints=true, firstHandle not shown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, SetHandleInfo002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    RectF firstRect(10.0f, 10.0f, 5.0f, 20.0f);
    RectF secondRect(100.0f, 10.0f, 5.0f, 20.0f);
    SetupHandleInfoWithTransform(manager, false, true, firstRect, secondRect);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    TextDragInfo info;
    info.firstHandle = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    info.secondHandle = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    richEditorPattern->SetHandleInfo(info);

    EXPECT_EQ(info.firstHandle, RectF(0.0f, 0.0f, 0.0f, 0.0f));
    EXPECT_EQ(info.secondHandle.GetX(), 100.0f);
    EXPECT_EQ(info.secondHandle.GetY(), 10.0f);
}

/**
 * @tc.name: SetHandleInfo003
 * @tc.desc: test SetHandleInfo with hasTransform=true, isPaintHandleWithPoints=true, secondHandle not shown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, SetHandleInfo003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    RectF firstRect(10.0f, 10.0f, 5.0f, 20.0f);
    RectF secondRect(100.0f, 10.0f, 5.0f, 20.0f);
    SetupHandleInfoWithTransform(manager, true, false, firstRect, secondRect);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    TextDragInfo info;
    info.firstHandle = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    info.secondHandle = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    richEditorPattern->SetHandleInfo(info);

    EXPECT_EQ(info.firstHandle.GetX(), 10.0f);
    EXPECT_EQ(info.firstHandle.GetY(), 10.0f);
    EXPECT_EQ(info.secondHandle, RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: SetHandleInfo004
 * @tc.desc: test SetHandleInfo with shareOverlayInfo=nullptr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, SetHandleInfo004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    manager->shareOverlayInfo_ = nullptr;

    TextDragInfo info;
    info.firstHandle = RectF(1.0f, 1.0f, 1.0f, 1.0f);
    info.secondHandle = RectF(1.0f, 1.0f, 1.0f, 1.0f);
    richEditorPattern->SetHandleInfo(info);

    EXPECT_EQ(info.firstHandle, RectF(1.0f, 1.0f, 1.0f, 1.0f));
    EXPECT_EQ(info.secondHandle, RectF(1.0f, 1.0f, 1.0f, 1.0f));
}

/**
 * @tc.name: SetHandleInfo005
 * @tc.desc: test SetHandleInfo with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, SetHandleInfo005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    RectF firstRect(10.0f, 10.0f, 5.0f, 20.0f);
    RectF secondRect(100.0f, 10.0f, 5.0f, 20.0f);
    SetupHandleInfoWithoutTransform(manager, true, true, firstRect, secondRect);
    richEditorPattern->selectOverlay_->hasTransform_ = false;

    TextDragInfo info;
    richEditorPattern->SetHandleInfo(info);

    EXPECT_EQ(info.firstHandle, firstRect);
    EXPECT_EQ(info.secondHandle, secondRect);
}

/**
 * @tc.name: SetHandleInfo006
 * @tc.desc: test SetHandleInfo with hasTransform=true, both handles not shown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, SetHandleInfo006, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    RectF firstRect(10.0f, 10.0f, 5.0f, 20.0f);
    RectF secondRect(100.0f, 10.0f, 5.0f, 20.0f);
    SetupHandleInfoWithTransform(manager, false, false, firstRect, secondRect);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    TextDragInfo info;
    info.firstHandle = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    info.secondHandle = RectF(0.0f, 0.0f, 0.0f, 0.0f);
    richEditorPattern->SetHandleInfo(info);

    EXPECT_EQ(info.firstHandle, RectF(0.0f, 0.0f, 0.0f, 0.0f));
    EXPECT_EQ(info.secondHandle, RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: GetVisibleContentRect001
 * @tc.desc: test GetVisibleContentRect with hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, GetVisibleContentRect001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = true;
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(10.0f, 10.0f));

    auto result = richEditorPattern->GetVisibleContentRect();
    EXPECT_EQ(result.Width(), 0.0f);
    EXPECT_EQ(result.Height(), 0.0f);
}

/**
 * @tc.name: GetVisibleContentRect002
 * @tc.desc: test GetVisibleContentRect with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, GetVisibleContentRect002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = false;
    richEditorPattern->contentRect_ = RectF(10.0f, 10.0f, 100.0f, 100.0f);

    auto result = richEditorPattern->GetVisibleContentRect();
    EXPECT_EQ(result.Width(), 100.0f);
    EXPECT_EQ(result.Height(), 100.0f);
}

/**
 * @tc.name: ConvertToGlobalRect001
 * @tc.desc: test ConvertToGlobalRect with hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertToGlobalRect001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentRenderContext->UpdateTransformScale(VectorF(2.0f, 2.0f));

    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));

    RectF localRect(5.0f, 5.0f, 50.0f, 50.0f);
    auto globalRect = richEditorPattern->ConvertToGlobalRectWithTransform(localRect);

    EXPECT_EQ(globalRect.Width(), 50.0f);
    EXPECT_EQ(globalRect.Height(), 50.0f);
    EXPECT_EQ(globalRect.GetX(), 35.0f);
    EXPECT_EQ(globalRect.GetY(), 45.0f);
}

/**
 * @tc.name: ConvertToGlobalRect002
 * @tc.desc: test ConvertToGlobalRect with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertToGlobalRect002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = false;

    RectF localRect(10.0f, 10.0f, 50.0f, 50.0f);
    auto globalRect = richEditorPattern->ConvertToGlobalRectWithTransform(localRect);

    EXPECT_EQ(globalRect.Width(), 50.0f);
    EXPECT_EQ(globalRect.Height(), 50.0f);
}

/**
 * @tc.name: ConvertToGlobalOffsetWithTransform001
 * @tc.desc: test ConvertToGlobalOffsetWithTransform with hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertToGlobalOffsetWithTransform001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentRenderContext->UpdateTransformScale(VectorF(2.0f, 2.0f));

    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));

    OffsetF localOffset(5.0f, 5.0f);
    auto result = richEditorPattern->ConvertToGlobalOffsetWithTransform(localOffset);

    EXPECT_FLOAT_EQ(result.GetX(), 35.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 45.0f);
}

/**
 * @tc.name: ConvertToGlobalOffsetWithTransform002
 * @tc.desc: test ConvertToGlobalOffsetWithTransform with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertToGlobalOffsetWithTransform002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = false;

    OffsetF localOffset(10.0f, 10.0f);
    auto result = richEditorPattern->ConvertToGlobalOffsetWithTransform(localOffset);

    EXPECT_EQ(result.GetX(), 10.0f);
    EXPECT_EQ(result.GetY(), 10.0f);
}

/**
 * @tc.name: DragConvertToGlobalOffset001
 * @tc.desc: test RichEditorDragPattern::ConvertToGlobalOffset with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, DragConvertToGlobalOffset001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = false;

    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(5.0f, 5.0f, 200.0f, 200.0f));
    auto mockParentRenderContext = AceType::DynamicCast<MockRenderContext>(parentRenderContext);
    ASSERT_NE(mockParentRenderContext, nullptr);
    mockParentRenderContext->SetPaintRectWithTransform(RectF(5.0f, 5.0f, 200.0f, 200.0f));

    auto info = std::make_shared<TextDragInfo>();
    auto dragPattern = AceType::MakeRefPtr<RichEditorDragPattern>(richEditorPattern, info);
    ASSERT_NE(dragPattern, nullptr);

    OffsetF localOffset(10.0f, 10.0f);
    OffsetF parentGlobalOffset(5.0f, 5.0f);
    auto result = dragPattern->ConvertToGlobalOffset(localOffset, parentGlobalOffset);

    EXPECT_EQ(result.GetX(), 15.0f);
    EXPECT_EQ(result.GetY(), 15.0f);
}

/**
 * @tc.name: DragConvertToGlobalOffset002
 * @tc.desc: test RichEditorDragPattern::ConvertToGlobalOffset with hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, DragConvertToGlobalOffset002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentRenderContext->UpdateTransformScale(VectorF(2.0f, 2.0f));

    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));
    auto info = std::make_shared<TextDragInfo>();
    auto dragPattern = AceType::MakeRefPtr<RichEditorDragPattern>(richEditorPattern, info);
    ASSERT_NE(dragPattern, nullptr);

    OffsetF localOffset(5.0f, 5.0f);
    OffsetF parentGlobalOffset(0.0f, 0.0f);
    auto result = dragPattern->ConvertToGlobalOffset(localOffset, parentGlobalOffset);

    EXPECT_FLOAT_EQ(result.GetX(), 35.0f);
    EXPECT_FLOAT_EQ(result.GetY(), 45.0f);
}

/**
 * @tc.name: DragSetDragNodeScale001
 * @tc.desc: test RichEditorDragPattern::SetDragNodeScale with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, DragSetDragNodeScale001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = false;

    auto info = std::make_shared<TextDragInfo>();
    auto dragPattern = AceType::MakeRefPtr<RichEditorDragPattern>(richEditorPattern, info);
    ASSERT_NE(dragPattern, nullptr);

    auto dragNode = FrameNode::CreateFrameNode(V2::TEXTDRAG_ETS_TAG, 100, AceType::MakeRefPtr<TextDragPattern>());
    ASSERT_NE(dragNode, nullptr);
    auto dragContext = dragNode->GetRenderContext();
    ASSERT_NE(dragContext, nullptr);

    dragPattern->SetDragNodeScale(dragContext, richEditorNode_);
    EXPECT_EQ(info->scaleXY.first, 1.0f);
    EXPECT_EQ(info->scaleXY.second, 1.0f);

    dragPattern->CreateNodePaintMethod();
    auto overlayModifier = AceType::DynamicCast<RichEditorDragOverlayModifier>(dragPattern->overlayModifier_);
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetDragScaleXY(info->scaleXY);
    EXPECT_EQ(overlayModifier->dragScaleXY_.first, 1.0f);
    EXPECT_EQ(overlayModifier->dragScaleXY_.second, 1.0f);
}

/**
 * @tc.name: DragSetDragNodeScale002
 * @tc.desc: test RichEditorDragPattern::SetDragNodeScale with hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, DragSetDragNodeScale002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = true;

    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentRenderContext->UpdateTransformScale(VectorF(2.0f, 2.0f));

    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));

    auto info = std::make_shared<TextDragInfo>();
    auto dragPattern = AceType::MakeRefPtr<RichEditorDragPattern>(richEditorPattern, info);
    ASSERT_NE(dragPattern, nullptr);

    auto dragNode = FrameNode::CreateFrameNode(V2::TEXTDRAG_ETS_TAG, 100, AceType::MakeRefPtr<TextDragPattern>());
    ASSERT_NE(dragNode, nullptr);
    auto dragContext = dragNode->GetRenderContext();
    ASSERT_NE(dragContext, nullptr);

    dragPattern->SetDragNodeScale(dragContext, richEditorNode_);

    auto transformCenter = dragContext->GetTransformCenterValue(DimensionOffset(Offset(0.0, 0.0)));
    EXPECT_EQ(transformCenter.GetX(), Dimension(0.0));
    EXPECT_EQ(transformCenter.GetY(), Dimension(0.0));

    dragPattern->CreateNodePaintMethod();
    auto overlayModifier = AceType::DynamicCast<RichEditorDragOverlayModifier>(dragPattern->overlayModifier_);
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetDragScaleXY(info->scaleXY);
    EXPECT_FLOAT_EQ(overlayModifier->dragScaleXY_.first, 2.0f);
    EXPECT_FLOAT_EQ(overlayModifier->dragScaleXY_.second, 2.0f);

    // Branch: dragScaleXY != (1.0, 1.0), verify canvas.Scale(1/scaleX, 1/scaleY) then Restore
    overlayModifier->isAnimating_ = true;
    overlayModifier->type_ = DragAnimType::FLOATING;
    overlayModifier->SetFirstHandle(RectF(10.0f, 10.0f, 20.0f, 30.0f));
    overlayModifier->SetHandleOpacity(1.0f);
    Testing::MockCanvas mockCanvas;
    EXPECT_CALL(mockCanvas, Scale(0.5f, 0.5f)).Times(1);
    EXPECT_CALL(mockCanvas, Save());
    EXPECT_CALL(mockCanvas, Restore());
    EXPECT_CALL(mockCanvas, Translate(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(mockCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(mockCanvas));
    EXPECT_CALL(mockCanvas, DetachPen()).WillRepeatedly(ReturnRef(mockCanvas));
    EXPECT_CALL(mockCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(mockCanvas));
    EXPECT_CALL(mockCanvas, DetachBrush()).WillRepeatedly(ReturnRef(mockCanvas));
    SelectPositionInfo selectPosition;
    overlayModifier->PaintHandle(mockCanvas, true, selectPosition);
}

/**
 * @tc.name: ConvertToLocalOffsetWithTransform001
 * @tc.desc: test ConvertToLocalOffsetWithTransform with hasTransform=false then hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertToLocalOffsetWithTransform001, TestSize.Level0)
{
    // Branch: hasTransform=false
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->hasTransform_ = false;

    auto parentNodeWithoutTransform =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 100, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNodeWithoutTransform, nullptr);
    parentNodeWithoutTransform->AddChild(richEditorNode_);
    auto parentRenderContextWithoutTransform = parentNodeWithoutTransform->GetRenderContext();
    ASSERT_NE(parentRenderContextWithoutTransform, nullptr);
    parentRenderContextWithoutTransform->UpdatePaintRect(RectF(5.0f, 5.0f, 200.0f, 200.0f));
    auto mockParentRenderContextWithoutTransform =
        AceType::DynamicCast<MockRenderContext>(parentRenderContextWithoutTransform);
    ASSERT_NE(mockParentRenderContextWithoutTransform, nullptr);
    mockParentRenderContextWithoutTransform->SetPaintRectWithTransform(RectF(5.0f, 5.0f, 200.0f, 200.0f));

    Offset globalOffset(15, 15);
    auto result = richEditorPattern->ConvertToLocalOffsetWithTransform(globalOffset);
    EXPECT_EQ(result.GetX(), 10);
    EXPECT_EQ(result.GetY(), 10);

    // Branch: hasTransform=true
    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentRenderContext->UpdateTransformScale(VectorF(2.0f, 2.0f));

    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));

    richEditorPattern->selectOverlay_->hasTransform_ = true;
    Offset globalOffsetWithTransform(35, 45);
    auto resultWithTransform = richEditorPattern->ConvertToLocalOffsetWithTransform(globalOffsetWithTransform);
    EXPECT_FLOAT_EQ(resultWithTransform.GetX(), 5.0f);
    EXPECT_FLOAT_EQ(resultWithTransform.GetY(), 5.0f);
}

/**
 * @tc.name: ConvertToLocalRectWithTransform001
 * @tc.desc: test ConvertToLocalRectWithTransform with hasTransform=false then hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertToLocalRectWithTransform001, TestSize.Level0)
{
    // Branch: hasTransform=false
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->selectOverlay_->hasTransform_ = false;

    auto parentNodeWithoutTransform =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 100, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNodeWithoutTransform, nullptr);
    parentNodeWithoutTransform->AddChild(richEditorNode_);
    auto parentRenderContextWithoutTransform = parentNodeWithoutTransform->GetRenderContext();
    ASSERT_NE(parentRenderContextWithoutTransform, nullptr);
    parentRenderContextWithoutTransform->UpdatePaintRect(RectF(5.0f, 5.0f, 200.0f, 200.0f));
    auto mockParentRenderContextWithoutTransform =
        AceType::DynamicCast<MockRenderContext>(parentRenderContextWithoutTransform);
    ASSERT_NE(mockParentRenderContextWithoutTransform, nullptr);
    mockParentRenderContextWithoutTransform->SetPaintRectWithTransform(RectF(5.0f, 5.0f, 200.0f, 200.0f));

    RectF globalRect(15.0f, 15.0f, 50.0f, 50.0f);
    auto localRect = richEditorPattern->ConvertToLocalRectWithTransform(globalRect);
    EXPECT_EQ(localRect.Width(), 50.0f);
    EXPECT_EQ(localRect.Height(), 50.0f);
    EXPECT_EQ(localRect.GetX(), 10.0f);
    EXPECT_EQ(localRect.GetY(), 10.0f);

    // Branch: hasTransform=true
    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(parentNode, nullptr);
    parentNode->AddChild(richEditorNode_);
    auto parentRenderContext = parentNode->GetRenderContext();
    ASSERT_NE(parentRenderContext, nullptr);
    parentRenderContext->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentRenderContext->UpdateTransformScale(VectorF(2.0f, 2.0f));

    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));

    richEditorPattern->selectOverlay_->hasTransform_ = true;
    RectF globalRectWithTransform(35.0f, 45.0f, 50.0f, 50.0f);
    auto localRectWithTransform = richEditorPattern->ConvertToLocalRectWithTransform(globalRectWithTransform);
    EXPECT_EQ(localRectWithTransform.Width(), 50.0f);
    EXPECT_EQ(localRectWithTransform.Height(), 50.0f);
    EXPECT_EQ(localRectWithTransform.GetX(), 5.0f);
    EXPECT_EQ(localRectWithTransform.GetY(), 5.0f);
}

/**
 * @tc.name: ChangeHandleHeightWithTransform001
 * @tc.desc: test ChangeHandleHeight with HasRenderTransform=true, covering all branches
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ChangeHandleHeightWithTransform001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<SelectContentOverlayManager> manager;
    InitManagerAndBind(richEditorPattern, manager);
    auto parentNode =
        FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    parentNode->AddChild(richEditorNode_);
    parentNode->GetRenderContext()->UpdatePaintRect(RectF(20.0f, 30.0f, 200.0f, 200.0f));
    parentNode->GetRenderContext()->UpdateTransformScale(VectorF(2.0f, 2.0f));
    richEditorNode_->GetRenderContext()->UpdatePaintRect(RectF(10.0f, 10.0f, 100.0f, 100.0f));
    richEditorPattern->selectOverlay_->hasTransform_ = true;

    // Compute expected touchOffset Y via transform helpers
    auto localOffsetF = richEditorPattern->selectOverlay_->ConvertToLocalOffsetWithTransform(OffsetF(35.0f, 45.0f));
    auto paintOffset = richEditorPattern->selectOverlay_->GetPaintOffsetWithoutTransform();
    float touchY = localOffsetF.GetY() + paintOffset.GetY();
    GestureEvent event;
    event.SetGlobalLocation(Offset(35.0f, 45.0f));
    auto& textSelector = richEditorPattern->textSelector_;

    // isFirst=true, !StartGreaterDest => ChangeFirstHandleHeight(firstHandle)
    textSelector.baseOffset = 5;
    textSelector.destinationOffset = 10;
    textSelector.firstHandle = RectF(0, 10, 5, 20);
    richEditorPattern->selectOverlay_->ChangeHandleHeight(event, true);
    EXPECT_FLOAT_EQ(textSelector.firstHandle.GetY(), touchY - 10.0f);

    // isFirst=true, StartGreaterDest => ChangeSecondHandleHeight(firstHandle)
    textSelector.baseOffset = 10;
    textSelector.destinationOffset = 5;
    textSelector.firstHandle = RectF(0, 10, 5, 50);
    richEditorPattern->selectOverlay_->ChangeHandleHeight(event, true);
    EXPECT_FLOAT_EQ(textSelector.firstHandle.GetY(), touchY - 25.0f);

    // isFirst=false, StartGreaterDest => ChangeFirstHandleHeight(secondHandle)
    textSelector.baseOffset = 10;
    textSelector.destinationOffset = 5;
    textSelector.secondHandle = RectF(0, 10, 5, 20);
    richEditorPattern->selectOverlay_->ChangeHandleHeight(event, false);
    EXPECT_FLOAT_EQ(textSelector.secondHandle.GetY(), touchY - 10.0f);

    // isFirst=false, !StartGreaterDest => ChangeSecondHandleHeight(secondHandle)
    textSelector.baseOffset = 5;
    textSelector.destinationOffset = 10;
    textSelector.secondHandle = RectF(0, 10, 5, 50);
    richEditorPattern->selectOverlay_->ChangeHandleHeight(event, false);
    EXPECT_FLOAT_EQ(textSelector.secondHandle.GetY(), touchY - 25.0f);
}
}