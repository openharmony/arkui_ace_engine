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
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"

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
 * @tc.name: ConvertLocalToGlobalRect001
 * @tc.desc: test ConvertLocalToGlobalRect with hasTransform=true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertLocalToGlobalRect001, TestSize.Level0)
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
    richEditorPattern->ConvertLocalToGlobalRect(localRect);

    EXPECT_FLOAT_EQ(localRect.Width(), 50.0f);
    EXPECT_FLOAT_EQ(localRect.Height(), 50.0f);
    EXPECT_FLOAT_EQ(localRect.GetX(), 35.0f);
    EXPECT_FLOAT_EQ(localRect.GetY(), 45.0f);
}

/**
 * @tc.name: ConvertLocalToGlobalRect002
 * @tc.desc: test ConvertLocalToGlobalRect with hasTransform=false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTransformTestNg, ConvertLocalToGlobalRect002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->selectOverlay_->hasTransform_ = false;

    RectF localRect(10.0f, 10.0f, 50.0f, 50.0f);
    richEditorPattern->ConvertLocalToGlobalRect(localRect);

    EXPECT_EQ(localRect.Width(), 50.0f);
    EXPECT_EQ(localRect.Height(), 50.0f);
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

    dragPattern->SetDragNodeScale(dragContext);
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

    auto info = std::make_shared<TextDragInfo>();
    auto dragPattern = AceType::MakeRefPtr<RichEditorDragPattern>(richEditorPattern, info);
    ASSERT_NE(dragPattern, nullptr);

    auto dragNode = FrameNode::CreateFrameNode(V2::TEXTDRAG_ETS_TAG, 100, AceType::MakeRefPtr<TextDragPattern>());
    ASSERT_NE(dragNode, nullptr);
    auto dragContext = dragNode->GetRenderContext();
    ASSERT_NE(dragContext, nullptr);

    dragPattern->SetDragNodeScale(dragContext);

    auto transformCenter = dragContext->GetTransformCenterValue(DimensionOffset(Offset(0.0, 0.0)));
    EXPECT_EQ(transformCenter.GetX(), Dimension(0.0));
    EXPECT_EQ(transformCenter.GetY(), Dimension(0.0));
}
}