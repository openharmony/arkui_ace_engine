/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "text_base.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "core/components/hyperlink/hyperlink_theme.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TextTestFiveNg : public TextBases {
public:
};

/**
 * @tc.name: TextContentModifier030
 * @tc.desc: test text_content_modifier.cpp UpdateImageNodeVisible function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TextContentModifier030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 300; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        imageNodeLocalList.emplace_back(imageNode);
    }
    textPattern->SetImageSpanNodeList(imageNodeList);
    
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 300.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPaintMethod->textContentModifier_;
    ASSERT_NE(textContentModifier, nullptr);
    EXPECT_EQ(textContentModifier->imageNodeList_.size(), 300);
    textContentModifier->UpdateImageNodeVisible(VisibleType::INVISIBLE);
    for (const auto& imageWeak : textContentModifier->imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        ASSERT_NE(imageNode, nullptr);
        auto layoutProperty1 = imageNode->GetLayoutProperty();
        ASSERT_NE(layoutProperty1, nullptr);
        EXPECT_EQ(static_cast<int32_t>(layoutProperty1->GetVisibility().has_value() &&
            (layoutProperty1->GetVisibility().value() == VisibleType::INVISIBLE)), 1);
    }
    
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier031
 * @tc.desc: test text_content_modifier.cpp UpdateImageNodeVisible function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TextContentModifier031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 300; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        imageNodeLocalList.emplace_back(imageNode);
    }
    textPattern->SetImageSpanNodeList(imageNodeList);
    
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 300.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPaintMethod->textContentModifier_;
    ASSERT_NE(textContentModifier, nullptr);
  
    textContentModifier->UpdateImageNodeVisible(VisibleType::VISIBLE);
    EXPECT_EQ(textContentModifier->imageNodeList_.size(), 300);
    for (const auto& imageWeak : textContentModifier->imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        ASSERT_NE(imageNode, nullptr);
        auto layoutProperty2 = imageNode->GetLayoutProperty();
        ASSERT_NE(layoutProperty2, nullptr);
        EXPECT_EQ(static_cast<int32_t>(layoutProperty2->GetVisibility().has_value() &&
            (layoutProperty2->GetVisibility().value() == VisibleType::VISIBLE)), 1);
    }
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier032
 * @tc.desc: test text_content_modifier.cpp UpdateImageNodeVisible function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TextContentModifier032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 300; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        imageNodeLocalList.emplace_back(imageNode);
    }
    textPattern->SetImageSpanNodeList(imageNodeList);
    
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 300.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPaintMethod->textContentModifier_;
    ASSERT_NE(textContentModifier, nullptr);
  
    textContentModifier->UpdateImageNodeVisible(VisibleType::GONE);
    EXPECT_EQ(textContentModifier->imageNodeList_.size(), 300);
    for (const auto& imageWeak : textContentModifier->imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        ASSERT_NE(imageNode, nullptr);
        auto layoutProperty2 = imageNode->GetLayoutProperty();
        ASSERT_NE(layoutProperty2, nullptr);
        EXPECT_EQ(static_cast<int32_t>(layoutProperty2->GetVisibility().has_value() &&
            (layoutProperty2->GetVisibility().value() == VisibleType::GONE)), 1);
    }
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier033
 * @tc.desc: test text_content_modifier.cpp UpdateImageNodeVisible function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TextContentModifier033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 200; i++) {
        imageNodeList.emplace_back(nullptr);
    }
    textPattern->SetImageSpanNodeList(imageNodeList);
    
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 200.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPaintMethod->textContentModifier_;
    ASSERT_NE(textContentModifier, nullptr);
    EXPECT_EQ(textContentModifier->imageNodeList_.size(), 200);
    textContentModifier->UpdateImageNodeVisible(VisibleType::INVISIBLE);
    for (const auto& imageWeak : textContentModifier->imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        EXPECT_EQ(imageNode, nullptr);
    }
    
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier034
 * @tc.desc: test text_content_modifier.cpp UpdateImageNodeVisible function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TextContentModifier034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 200; i++) {
        imageNodeList.emplace_back(nullptr);
    }
    textPattern->SetImageSpanNodeList(imageNodeList);
    
    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 200.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPaintMethod->textContentModifier_;
    ASSERT_NE(textContentModifier, nullptr);
    
    textContentModifier->UpdateImageNodeVisible(VisibleType::VISIBLE);
    EXPECT_EQ(textContentModifier->imageNodeList_.size(), 200);
    for (const auto& imageWeak : textContentModifier->imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        EXPECT_EQ(imageNode, nullptr);
    }
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextContentModifier035
 * @tc.desc: test text_content_modifier.cpp UpdateImageNodeVisible function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TextContentModifier035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Create imageNodeList and add imageNode into imageNodeList.
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 200; i++) {
        imageNodeList.emplace_back(nullptr);
    }
    textPattern->SetImageSpanNodeList(imageNodeList);

    /**
     * @tc.steps: step3. call CreateNodePaintMethod func.
     * @tc.expected: The imageNodeList_ size is equal to 200.
     */
    auto textPaintMethod = AceType::DynamicCast<TextPaintMethod>(textPattern->CreateNodePaintMethod());
    ASSERT_NE(textPaintMethod, nullptr);
    RefPtr<RenderContext> renderContext = textFrameNode->GetRenderContext();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod->UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPaintMethod->textContentModifier_;
    ASSERT_NE(textContentModifier, nullptr);

    textContentModifier->UpdateImageNodeVisible(VisibleType::GONE);
    EXPECT_EQ(textContentModifier->imageNodeList_.size(), 200);
    for (const auto& imageWeak : textContentModifier->imageNodeList_) {
        auto imageNode = imageWeak.Upgrade();
        EXPECT_EQ(imageNode, nullptr);
    }
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: GetSpansInfoInStyledString001
 * @tc.desc: test text_pattern.cpp GetSpansInfoInStyledString function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSpansInfoInStyledString001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textSpanNode = CreateSpanNodeWithSetDefaultProperty(TEXT_FOR_AI);
    ASSERT_NE(textSpanNode, nullptr);
    textPattern->AddChildSpanItem(textSpanNode);
    ImageSpanNodeProperty firstProperty { .imageSrc = std::make_optional("image") };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    ASSERT_NE(imageSpanNode, nullptr);
    textPattern->AddChildSpanItem(imageSpanNode);

    auto resultObjects = textPattern->GetSpansInfoInStyledString(0, TEXT_SIZE_INT);
    ASSERT_NE(resultObjects.size(), 0);
}

/**
 * @tc.name: GetSpansInfo001
 * @tc.desc: test text_pattern.cpp GetSpansInfo function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSpansInfo001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto spanString = AceType::MakeRefPtr<SpanString>(TEXT_CONTENT);
    ASSERT_NE(spanString, nullptr);
    textPattern->SetStyledString(spanString);

    auto selectionInfo = textPattern->GetSpansInfo(0, 0, GetSpansMethod::GETSPANS);
    ASSERT_NE(selectionInfo.selection_.resultObjects.size(), 0);

    selectionInfo = textPattern->GetSpansInfo(-1, 0, GetSpansMethod::GETSPANS);
    ASSERT_NE(selectionInfo.selection_.resultObjects.size(), 0);

    selectionInfo = textPattern->GetSpansInfo(0, -1, GetSpansMethod::GETSPANS);
    ASSERT_NE(selectionInfo.selection_.resultObjects.size(), 0);

    selectionInfo = textPattern->GetSpansInfo(-1, -1, GetSpansMethod::GETSPANS);
    ASSERT_NE(selectionInfo.selection_.resultObjects.size(), 0);

    selectionInfo = textPattern->GetSpansInfo(1, 0, GetSpansMethod::GETSPANS);
    ASSERT_NE(selectionInfo.selection_.resultObjects.size(), 0);

    selectionInfo = textPattern->GetSpansInfo(-1, -1, static_cast<GetSpansMethod>(-1));
    ASSERT_NE(selectionInfo.selection_.resultObjects.size(), 0);
}

/**
 * @tc.name: GetSelectedText001
 * @tc.desc: test text_pattern.cpp GetSelectedText function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSelectedText001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto textSpanNode1 = CreateSpanNodeWithSetDefaultProperty(CREATE_VALUE);
    ASSERT_NE(textSpanNode1, nullptr);
    textPattern->AddChildSpanItem(textSpanNode1);
    auto textSpanNode2 = CreateSpanNodeWithSetDefaultProperty(CREATE_VALUE);
    ASSERT_NE(textSpanNode2, nullptr);
    textSpanNode2->UpdateContent(1);
    textPattern->AddChildSpanItem(textSpanNode2);
    auto textSpanNode3 = CreateSpanNodeWithSetDefaultProperty(CREATE_VALUE);
    ASSERT_NE(textSpanNode3, nullptr);
    textSpanNode3->UpdateContent(1);
    textSpanNode3->spanItem_->position = 1;
    textPattern->AddChildSpanItem(textSpanNode3);
    auto textSpanNode4 = CreateSpanNodeWithSetDefaultProperty(CREATE_VALUE);
    ASSERT_NE(textSpanNode4, nullptr);
    textSpanNode4->spanItem_->placeholderIndex = 0;
    textPattern->AddChildSpanItem(textSpanNode4);
    auto textSpanNode5 = CreateSpanNodeWithSetDefaultProperty(CREATE_VALUE);
    ASSERT_NE(textSpanNode5, nullptr);
    textSpanNode5->spanItem_->position = 1;
    textSpanNode5->spanItem_->placeholderIndex = 0;
    textPattern->AddChildSpanItem(textSpanNode5);
    auto textSpanNode6 = CreateSpanNodeWithSetDefaultProperty(CREATE_VALUE);
    ASSERT_NE(textSpanNode6, nullptr);
    textSpanNode6->spanItem_->position = 1;
    textPattern->AddChildSpanItem(textSpanNode6);

    auto selectedText = textPattern->GetSelectedText(0, 10);
    ASSERT_EQ(selectedText, " ");
}

/**
 * @tc.name: GetTextHeight001
 * @tc.desc: test text_pattern.cpp GetTextHeight function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetTextHeight001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    ASSERT_NE(textPattern->pManager_, nullptr);

    Offset globalOffset;
    globalOffset.SetX(0);
    globalOffset.SetY(5);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(2));
    textPattern->pManager_->AddParagraph(
        { .paragraph = paragraph, .start = 0, .end = 2 });
    textPattern->pManager_->AddParagraph(
        { .paragraph = paragraph, .start = 2, .end = 4 });

    EXPECT_EQ(textPattern->GetTextHeight(0, false), 0.0);
    EXPECT_EQ(textPattern->GetTextHeight(0, true), 0.0);
}

/**
 * @tc.name: CheckHandleIsVisibleWithTransform001
 * @tc.desc: test base_text_select_overlay.cpp CheckHandleIsVisibleWithTransform function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CheckHandleIsVisibleWithTransform001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    OffsetF startPoint(0, 0);
    OffsetF endPoint(1, 1);

    EXPECT_EQ(textSelectOverlay->CheckHandleIsVisibleWithTransform(startPoint, endPoint, 10.0), true);

    startPoint.SetX(-11);
    startPoint.SetY(-11);
    endPoint.SetX(11);
    endPoint.SetY(11);

    EXPECT_EQ(textSelectOverlay->CheckHandleIsVisibleWithTransform(startPoint, endPoint, 10.0), false);

    startPoint.SetX(0);
    startPoint.SetY(0);
    endPoint.SetX(11);
    endPoint.SetY(11);

    EXPECT_EQ(textSelectOverlay->CheckHandleIsVisibleWithTransform(startPoint, endPoint, 10.0), false);

    startPoint.SetX(-11);
    startPoint.SetY(-11);
    endPoint.SetX(0);
    endPoint.SetY(0);

    EXPECT_EQ(textSelectOverlay->CheckHandleIsVisibleWithTransform(startPoint, endPoint, 10.0), false);
}

/**
 * @tc.name: IsPointsInRegion001
 * @tc.desc: test base_text_select_overlay.cpp IsPointsInRegion function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsPointsInRegion001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    std::vector<PointF> points;
    RectF regionRect(1, 1, 4, 4);

    EXPECT_EQ(textSelectOverlay->IsPointsInRegion(points, regionRect), true);

    points.emplace_back(PointF(0, 0));
    points.emplace_back(PointF(1, 1));
    points.emplace_back(PointF(3, 3));
    points.emplace_back(PointF(5, 5));
    points.emplace_back(PointF(6, 6));

    EXPECT_EQ(textSelectOverlay->IsPointsInRegion(points, regionRect), false);
}

/**
 * @tc.name: CheckHandleCanPaintInHost001
 * @tc.desc: test base_text_select_overlay.cpp CheckHandleCanPaintInHost function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CheckHandleCanPaintInHost001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    ASSERT_NE(frameNode->GetGeometryNode(), nullptr);

    frameNode->GetGeometryNode()->SetFrameSize(SizeF(10, 10));
    textSelectOverlay->isChangeToOverlayModeAtEdge_ = false;

    RectF firstRect(3, 3, 5, 5);
    RectF secondRect(4, 4, 6, 6);
    EXPECT_EQ(textSelectOverlay->CheckHandleCanPaintInHost(firstRect, secondRect), true);

    firstRect.SetRect(3, 3, 5, 5);
    secondRect.SetRect(11, 11, 15, 15);
    EXPECT_EQ(textSelectOverlay->CheckHandleCanPaintInHost(firstRect, secondRect), false);

    frameNode->GetGeometryNode()->SetFrameSize(SizeF(3, 3));

    firstRect.SetRect(11, 11, 15, 15);
    secondRect.SetRect(3, 3, 5, 5);
    EXPECT_EQ(textSelectOverlay->CheckHandleCanPaintInHost(firstRect, secondRect), false);

    firstRect.SetRect(11, 11, 15, 15);
    secondRect.SetRect(13, 13, 15, 15);
    EXPECT_EQ(textSelectOverlay->CheckHandleCanPaintInHost(firstRect, secondRect), false);
}

/**
 * @tc.name: IsTouchAtHandle001
 * @tc.desc: test base_text_select_overlay.cpp IsTouchAtHandle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsTouchAtHandle001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    textSelectOverlay->OnBind(manager);

    TouchEventInfo info0("touch0");
    TouchLocationInfo locationInfo0(1);
    locationInfo0.SetTouchType(TouchType::DOWN);
    locationInfo0.SetLocalLocation(Offset(0, 0));
    info0.AddTouchLocationInfo(std::move(locationInfo0));

    EXPECT_EQ(textSelectOverlay->IsTouchAtHandle(info0), false);

    TouchEventInfo info1("touch1");
    TouchLocationInfo locationInfo1(1);
    locationInfo1.SetTouchType(TouchType::UP);
    locationInfo1.SetLocalLocation(Offset(0, 0));
    info1.AddTouchLocationInfo(std::move(locationInfo1));

    EXPECT_EQ(textSelectOverlay->IsTouchAtHandle(info1), false);

    TouchEventInfo info2("touch2");
    TouchLocationInfo locationInfo2(1);
    locationInfo2.SetTouchType(TouchType::MOVE);
    locationInfo2.SetLocalLocation(Offset(0, 0));
    info2.AddTouchLocationInfo(std::move(locationInfo2));

    EXPECT_EQ(textSelectOverlay->IsTouchAtHandle(info2), false);

    TouchEventInfo info3("touch3");
    TouchLocationInfo locationInfo3(1);
    locationInfo3.SetTouchType(TouchType::UP);
    locationInfo3.SetLocalLocation(Offset(0, 0));
    locationInfo3.SetGlobalLocation(Offset(0, 0));
    info3.AddTouchLocationInfo(std::move(locationInfo3));

    EXPECT_EQ(textSelectOverlay->IsTouchAtHandle(info3), false);
}

/**
 * @tc.name: CheckSwitchToMode001
 * @tc.desc: test base_text_select_overlay.cpp CheckSwitchToMode function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CheckSwitchToMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    EXPECT_EQ(textSelectOverlay->CheckSwitchToMode(HandleLevelMode::OVERLAY), true);
    EXPECT_EQ(textSelectOverlay->CheckSwitchToMode(HandleLevelMode::EMBED), true);
}

/**
 * @tc.name: DrawImage001
 * @tc.desc: test text_content_modifier.cpp DrawImage function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, DrawImage001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()), pattern);
    ASSERT_NE(textContentModifier, nullptr);

    RSCanvas canvas;
    RectF rect(0, 0, 10, 10);

    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);

    frameNode->layoutProperty_->margin_ = std::make_unique<MarginProperty>();
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);

    frameNode->layoutProperty_->margin_->left = CalcLength("0vp");
    frameNode->layoutProperty_->margin_->top = CalcLength("0vp");
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);

    auto layoutProperty = frameNode->layoutProperty_;
    frameNode->layoutProperty_ = nullptr;
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);
    frameNode->layoutProperty_ = layoutProperty;

    pattern->altImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    ASSERT_NE(pattern->altImage_, nullptr);
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), true);

    pattern->image_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    ASSERT_NE(pattern->image_, nullptr);
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), true);

    auto geometryNode = frameNode->geometryNode_;
    frameNode->geometryNode_ = nullptr;
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);
    frameNode->geometryNode_ = geometryNode;

    auto& config = pattern->image_->GetPaintConfig();
    config.isSvg_ = !config.isSvg_;
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), true);
    config.isSvg_ = !config.isSvg_;

    pattern->image_ = AceType::MakeRefPtr<PixelMapImage>();
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), true);
}

/**
 * @tc.name: GetTextDirection001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp GetTextDirection function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetTextDirection001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    std::string content = "Hello World";
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(textLayoutProperty, nullptr);

    EXPECT_EQ(MultipleParagraphLayoutAlgorithm::GetTextDirection(
        content, layoutWrapper.GetRawPtr()), TextDirection::LTR);

    textLayoutProperty->UpdateLayoutDirection(TextDirection::LTR);
    EXPECT_EQ(MultipleParagraphLayoutAlgorithm::GetTextDirection(
        content, layoutWrapper.GetRawPtr()), TextDirection::LTR);

    textLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(MultipleParagraphLayoutAlgorithm::GetTextDirection(
        content, layoutWrapper.GetRawPtr()), TextDirection::RTL);

    textLayoutProperty->UpdateLayoutDirection(TextDirection::AUTO);
    AceApplicationInfo::GetInstance().isRightToLeft_ = !AceApplicationInfo::GetInstance().IsRightToLeft();
    EXPECT_EQ(MultipleParagraphLayoutAlgorithm::GetTextDirection(
        content, layoutWrapper.GetRawPtr()), TextDirection::LTR);
    AceApplicationInfo::GetInstance().isRightToLeft_ = !AceApplicationInfo::GetInstance().IsRightToLeft();
}

/**
 * @tc.name: InheritParentProperties001
 * @tc.desc: test span_node.cpp InheritParentProperties function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, InheritParentProperties001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto layoutProperty = AceType::DynamicCast<TextLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(10.0));
    layoutProperty->UpdateTextColor(Color::RED);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    auto oldTheme = pipeline->themeManager_;
    pipeline->themeManager_ = theme;

    auto spanNode = AceType::MakeRefPtr<SpanNode>(1);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);

    TextStyle textStyle;
    textStyle.SetFontSize(Dimension(10.0));
    textStyle.SetTextColor(Color::RED);

    pipeline->themeManager_ = oldTheme;
}

/**
 * @tc.name: AdaptMinFontSize001
 * @tc.desc: test text_adapt_font_sizer.cpp AdaptMinFontSize function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, AdaptMinFontSize001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto textAdaptFontSizer = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    ASSERT_NE(textAdaptFontSizer, nullptr);

    TextStyle textStyle;
    std::string content;
    Dimension stepUnit;
    LayoutConstraintF contentConstraint;

    EXPECT_EQ(textAdaptFontSizer->AdaptMinFontSize(
        textStyle, content, stepUnit, contentConstraint, layoutWrapper.GetRawPtr()), true);

    textStyle.SetAdaptTextSize(Dimension(100, DimensionUnit::PERCENT),
        Dimension(10, DimensionUnit::PERCENT), Dimension(10, DimensionUnit::PERCENT));

    contentConstraint.maxSize.SetWidth(-1.0);
    contentConstraint.maxSize.SetHeight(-1.0);

    EXPECT_EQ(textAdaptFontSizer->AdaptMinFontSize(
        textStyle, content, stepUnit, contentConstraint, layoutWrapper.GetRawPtr()), true);

    contentConstraint.maxSize.SetWidth(1.0);
    contentConstraint.maxSize.SetHeight(1.0);

    EXPECT_EQ(textAdaptFontSizer->AdaptMinFontSize(
        textStyle, content, stepUnit, contentConstraint, layoutWrapper.GetRawPtr()), true);

    TextStyle textStyleFP;
    textStyleFP.SetAdaptTextSize(Dimension(100, DimensionUnit::FP),
        Dimension(10, DimensionUnit::FP), Dimension(10, DimensionUnit::FP));
    textStyleFP.SetFontSize(Dimension(10, DimensionUnit::FP));

    EXPECT_EQ(textAdaptFontSizer->AdaptMinFontSize(
        textStyleFP, content, stepUnit, contentConstraint, layoutWrapper.GetRawPtr()), true);
}

/**
 * @tc.name: IsNeedAdaptFontSize001
 * @tc.desc: test text_adapt_font_sizer.cpp IsNeedAdaptFontSize function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsNeedAdaptFontSize001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto textAdaptFontSizer = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    ASSERT_NE(textAdaptFontSizer, nullptr);

    double maxFontSize = 0.0;
    double minFontSize = 0.0;
    EXPECT_EQ(textAdaptFontSizer->IsNeedAdaptFontSize(maxFontSize, minFontSize), false);

    maxFontSize = 1.0;
    minFontSize = 1.0;
    EXPECT_EQ(textAdaptFontSizer->IsNeedAdaptFontSize(maxFontSize, minFontSize), true);

    maxFontSize = -2.0;
    minFontSize = -1.0;
    EXPECT_EQ(textAdaptFontSizer->IsNeedAdaptFontSize(maxFontSize, minFontSize), false);

    maxFontSize = 0.0;
    minFontSize = -1.0;
    EXPECT_EQ(textAdaptFontSizer->IsNeedAdaptFontSize(maxFontSize, minFontSize), false);

    TextStyle textStyle;
    LayoutConstraintF contentConstraint;

    textAdaptFontSizer->IsNeedAdaptFontSize(textStyle, contentConstraint);

    textStyle.SetAdaptTextSize(Dimension(100, DimensionUnit::PERCENT),
        Dimension(10, DimensionUnit::PERCENT), Dimension(10, DimensionUnit::PERCENT));
    contentConstraint.maxSize.SetWidth(-1.0);
    contentConstraint.maxSize.SetHeight(-1.0);
    EXPECT_EQ(textAdaptFontSizer->IsNeedAdaptFontSize(textStyle, contentConstraint), false);
}

/**
 * @tc.name: IsAdaptFontSizeExceedLineHeight001
 * @tc.desc: test text_adapt_font_sizer.cpp IsAdaptFontSizeExceedLineHeight function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsAdaptFontSizeExceedLineHeight001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto textAdaptFontSizer = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    ASSERT_NE(textAdaptFontSizer, nullptr);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();

    textAdaptFontSizer->lineHeight_ = 0.0;
    EXPECT_EQ(textAdaptFontSizer->IsAdaptFontSizeExceedLineHeight(paragraph), false);

    textAdaptFontSizer->lineHeight_ = 1.0;
    EXPECT_EQ(textAdaptFontSizer->IsAdaptFontSizeExceedLineHeight(paragraph), false);
}

/**
 * @tc.name: EncodeTlv001
 * @tc.desc: test span_node.cpp EncodeTlv function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, EncodeTlv001, TestSize.Level1)
{
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute attr { .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);

    std::vector<uint8_t> buff;
    ImageSpanOptions options;

    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_EQ(imageSpanItem->EncodeTlv(buff), true);

    buff.clear();

    options.offset = 0;
    options.image = "textImage";
    options.bundleName = "textBundleName";
    options.moduleName = "textModuleName";
    options.imagePixelMap = nullptr;
    options.imageAttribute = attr;
    imageSpanItem->SetImageSpanOptions(options);
    EXPECT_EQ(imageSpanItem->EncodeTlv(buff), true);

    int32_t cursor = 1;
    auto newImageSpanItem = imageSpanItem->DecodeTlv(buff, cursor);
    EXPECT_NE(newImageSpanItem, nullptr);

    cursor = 0;
    newImageSpanItem = imageSpanItem->DecodeTlv(buff, cursor);
    EXPECT_NE(newImageSpanItem, nullptr);
}

/**
 * @tc.name: OnHandleLevelModeChanged001
 * @tc.desc: test text_select_overlay.cpp OnHandleLevelModeChanged function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, OnHandleLevelModeChanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    textSelectOverlay->OnAncestorNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);

    textSelectOverlay->handleLevelMode_ = HandleLevelMode::EMBED;
    textSelectOverlay->OnHandleLevelModeChanged(HandleLevelMode::OVERLAY);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    textSelectOverlay->handleLevelMode_ = HandleLevelMode::OVERLAY;
    textSelectOverlay->OnHandleLevelModeChanged(HandleLevelMode::EMBED);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::EMBED);

    textSelectOverlay->handleLevelMode_ = HandleLevelMode::EMBED;
    textSelectOverlay->OnHandleLevelModeChanged(HandleLevelMode::EMBED);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::EMBED);

    textSelectOverlay->handleLevelMode_ = HandleLevelMode::OVERLAY;
    textSelectOverlay->OnHandleLevelModeChanged(HandleLevelMode::OVERLAY);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: CreateParagraph001
 * @tc.desc: test text_layout_algorithm.cpp CreateParagraph function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CreateParagraph001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto maxSize = MultipleParagraphLayoutAlgorithm::GetMaxMeasureSize(contentConstraint);

    ParagraphStyle externalParagraphStyle;
    RefPtr<Paragraph> externalParagraph = Paragraph::Create(externalParagraphStyle, FontCollection::Current());
    ASSERT_NE(externalParagraph, nullptr);
    pattern->SetExternalParagraph(AceType::RawPtr(externalParagraph));

    EXPECT_EQ(textLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode), maxSize.Width()), true);

    pattern->textDetectEnable_ = true;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(textLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode), maxSize.Width()), true);

    pattern->SetExternalParagraphStyle(externalParagraphStyle);

    EXPECT_EQ(textLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode), maxSize.Width()), true);
}

/**
 * @tc.name: UpdateSymbolTextStyle001
 * @tc.desc: test text_layout_algorithm.cpp UpdateSymbolTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolTextStyle001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto layoutProperty = AceType::DynamicCast<TextLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo());

    TextStyle textStyle;
    ParagraphStyle paragraphStyle;
    NG::SymbolEffectOptions symbolEffectOptions;

    EXPECT_EQ(textLayoutAlgorithm->UpdateSymbolTextStyle(
        textStyle, paragraphStyle, AceType::RawPtr(frameNode), frameNode), true);

    textStyle.SetRenderStrategy(-1);
    textStyle.SetEffectStrategy(-1);
    textStyle.SetSymbolEffectOptions(symbolEffectOptions);
    EXPECT_EQ(textLayoutAlgorithm->UpdateSymbolTextStyle(
        textStyle, paragraphStyle, AceType::RawPtr(frameNode), frameNode), true);
}

/**
 * @tc.name: AdaptMinTextSize001
 * @tc.desc: test text_layout_algorithm.cpp AdaptMinTextSize function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, AdaptMinTextSize001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    TextStyle textStyle;
    std::string content;
    LayoutConstraintF contentConstraint;

    frameNode->pattern_ = nullptr;
    EXPECT_EQ(textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, content, contentConstraint, AceType::RawPtr(frameNode)), false);

    textStyle.SetAdaptTextSize(Dimension(100, DimensionUnit::PX),
        Dimension(10, DimensionUnit::PX), Dimension(10, DimensionUnit::PX));
    EXPECT_EQ(textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, content, contentConstraint, AceType::RawPtr(frameNode)), false);
    frameNode->pattern_ = pattern;

    textStyle.SetAdaptTextSize(Dimension(100, DimensionUnit::PERCENT),
        Dimension(10, DimensionUnit::PERCENT), Dimension(10, DimensionUnit::PERCENT));
    contentConstraint.maxSize.SetHeight(-1.0);
    contentConstraint.maxSize.SetWidth(-1.0);
    EXPECT_EQ(textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, content, contentConstraint, AceType::RawPtr(frameNode)), true);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(2));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(2));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(2));
    pattern->pManager_->AddParagraph(
        { .paragraph = paragraph, .start = 0, .end = 2 });

    contentConstraint.maxSize.SetHeight(1.0);
    contentConstraint.maxSize.SetWidth(1.0);
    EXPECT_EQ(textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, content, contentConstraint, AceType::RawPtr(frameNode)), true);
}

/**
 * @tc.name: GetGraphemeClusterLength001
 * @tc.desc: test text_base.cpp GetGraphemeClusterLength function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetGraphemeClusterLength001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    std::wstring text;

    EXPECT_EQ(pattern->GetGraphemeClusterLength(text, 0, false), 1);

    text = L"Test";

    EXPECT_EQ(pattern->GetGraphemeClusterLength(text, 0, true), 1);
    EXPECT_EQ(pattern->GetGraphemeClusterLength(text, 10, true), 1);
    EXPECT_EQ(pattern->GetGraphemeClusterLength(text, 0, false), 1);
    EXPECT_EQ(pattern->GetGraphemeClusterLength(text, 10, false), 1);
}

/**
 * @tc.name: CalculateSelectedRect001
 * @tc.desc: test text_base.cpp CalculateSelectedRect function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CalculateSelectedRect001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    std::vector<RectF> selectedRect;

    selectedRect.emplace_back(RectF(0, 0, 0, 0));
    pattern->CalculateSelectedRect(selectedRect, 0);
    EXPECT_EQ(selectedRect.size(), 1);

    selectedRect.emplace_back(RectF(0, 0, 1, 1));
    pattern->CalculateSelectedRect(selectedRect, 1);
    EXPECT_EQ(selectedRect.size(), 1);

    selectedRect.emplace_back(RectF(0, 0, 2, 2));
    pattern->CalculateSelectedRect(selectedRect, 2);
    EXPECT_EQ(selectedRect.size(), 1);

    selectedRect.emplace_back(RectF(10, 10, 20, 20));
    pattern->CalculateSelectedRect(selectedRect, 10);
    EXPECT_EQ(selectedRect.size(), 2);
}

/**
 * @tc.name: GetVisibleRect001
 * @tc.desc: test base_text_select_overlay.cpp GetVisibleRect function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetVisibleRect001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    auto parentPattern = AceType::MakeRefPtr<MockNestableScrollContainer>();
    ASSERT_NE(parentPattern, nullptr);
    auto parentFrameNode = FrameNode::CreateFrameNode("ParentTest", 1, parentPattern);
    ASSERT_NE(parentFrameNode, nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    pattern->GetHost()->SetParent(parentFrameNode);

    RectF visibleRect;
    visibleRect.SetRect(0, 0, 10, 10);

    EXPECT_NE(textSelectOverlay->GetVisibleRect(pattern->GetHost(), visibleRect), visibleRect);

    parentFrameNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentFrameNode, nullptr);
    pattern->GetHost()->SetParent(parentFrameNode);

    EXPECT_EQ(textSelectOverlay->GetVisibleRect(pattern->GetHost(), visibleRect), visibleRect);

    auto parentPattern1 = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(parentPattern1, nullptr);
    parentFrameNode = FrameNode::CreateFrameNode("ParentTest", 1, parentPattern1);
    ASSERT_NE(parentFrameNode, nullptr);
    pattern->GetHost()->SetParent(parentFrameNode);

    EXPECT_EQ(textSelectOverlay->GetVisibleRect(pattern->GetHost(), visibleRect), visibleRect);
}

/**
 * @tc.name: GetLocalPointsWithTransform001
 * @tc.desc: test base_text_select_overlay.cpp GetLocalPointsWithTransform function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetLocalPointsWithTransform001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    textSelectOverlay->hasTransform_ = true;

    std::vector<OffsetF> localPoints;

    textSelectOverlay->GetLocalPointsWithTransform(localPoints);
    EXPECT_EQ(localPoints.size(), 0);

    localPoints.emplace_back(OffsetF(0, 0));
    localPoints.emplace_back(OffsetF(1, 1));
    textSelectOverlay->GetLocalPointsWithTransform(localPoints);
    EXPECT_EQ(localPoints.size(), 2);
    EXPECT_EQ(localPoints[0].GetX(), 0);
    EXPECT_EQ(localPoints[0].GetY(), 0);
    EXPECT_EQ(localPoints[1].GetX(), 1);
    EXPECT_EQ(localPoints[1].GetY(), 1);
}

/**
 * @tc.name: GetAncestorNodeViewPort001
 * @tc.desc: test base_text_select_overlay.cpp GetAncestorNodeViewPort function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetAncestorNodeViewPort001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    auto parentPattern1 = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(parentPattern1, nullptr);
    auto parentFrameNode1 = FrameNode::CreateFrameNode("ParentTest", 1, parentPattern1);
    ASSERT_NE(parentFrameNode1, nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    pattern->GetHost()->SetParent(parentFrameNode1);

    EXPECT_EQ(textSelectOverlay->GetAncestorNodeViewPort(), RectF(0.0f, 0.0f, 0.0f, 0.0f));
}

/**
 * @tc.name: IsAcceptResetSelectionEvent001
 * @tc.desc: test base_text_select_overlay.cpp IsAcceptResetSelectionEvent function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, IsAcceptResetSelectionEvent001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    EXPECT_EQ(textSelectOverlay->IsAcceptResetSelectionEvent(SourceType::MOUSE, TouchType::DOWN), true);
    EXPECT_EQ(textSelectOverlay->IsAcceptResetSelectionEvent(SourceType::MOUSE, TouchType::UP), false);
    EXPECT_EQ(textSelectOverlay->IsAcceptResetSelectionEvent(SourceType::TOUCH, TouchType::DOWN), true);
    EXPECT_EQ(textSelectOverlay->IsAcceptResetSelectionEvent(SourceType::TOUCH, TouchType::UP), false);
    EXPECT_EQ(textSelectOverlay->IsAcceptResetSelectionEvent(SourceType::KEYBOARD, TouchType::DOWN), false);
    EXPECT_EQ(textSelectOverlay->IsAcceptResetSelectionEvent(SourceType::KEYBOARD, TouchType::UP), false);
}

/**
 * @tc.name: RevertLocalPointWithTransform001
 * @tc.desc: test base_text_select_overlay.cpp RevertLocalPointWithTransform function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, RevertLocalPointWithTransform001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    auto parentPattern1 = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(parentPattern1, nullptr);
    auto parentFrameNode1 = FrameNode::CreateFrameNode("ParentTest", 1, parentPattern1);
    ASSERT_NE(parentFrameNode1, nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    pattern->GetHost()->SetParent(parentFrameNode1);

    OffsetF point(10, 10);

    textSelectOverlay->hasTransform_ = true;
    textSelectOverlay->RevertLocalPointWithTransform(point);
    EXPECT_EQ(point.GetX(), 10);
    EXPECT_EQ(point.GetY(), 10);
}

/**
 * @tc.name: HasUnsupportedTransform001
 * @tc.desc: test base_text_select_overlay.cpp HasUnsupportedTransform function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, HasUnsupportedTransform001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto parentPattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(parentPattern, nullptr);
    auto parentFrameNode = FrameNode::CreateFrameNode(V2::WINDOW_SCENE_ETS_TAG, 1, parentPattern);
    ASSERT_NE(parentFrameNode, nullptr);
    ASSERT_NE(pattern->GetHost(), nullptr);
    pattern->GetHost()->SetParent(parentFrameNode);
    EXPECT_EQ(textSelectOverlay->HasUnsupportedTransform(), false);
    pattern->GetHost()->SetParent(nullptr);

    renderContext->UpdateTransformRotate(Vector5F(0, 0, 0, 0, 0));
    EXPECT_EQ(textSelectOverlay->HasUnsupportedTransform(), false);

    renderContext->UpdateTransformRotate(Vector5F(10, 0, 0, 0, 0));
    EXPECT_EQ(textSelectOverlay->HasUnsupportedTransform(), false);

    renderContext->UpdateTransformRotate(Vector5F(0, 10, 0, 0, 0));
    EXPECT_EQ(textSelectOverlay->HasUnsupportedTransform(), false);

    renderContext->UpdateTransformRotate(Vector5F(0, 0, 0, 0, 10));
    EXPECT_EQ(textSelectOverlay->HasUnsupportedTransform(), false);

    renderContext->UpdateTransformMatrix(Matrix4());
    EXPECT_EQ(textSelectOverlay->HasUnsupportedTransform(), false);
}

/**
 * @tc.name: CalcHandleLevelMode001
 * @tc.desc: test base_text_select_overlay.cpp CalcHandleLevelMode function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CalcHandleLevelMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);
    ASSERT_NE(frameNode->GetGeometryNode(), nullptr);

    frameNode->GetGeometryNode()->SetFrameSize(SizeF(10, 10));
    textSelectOverlay->isChangeToOverlayModeAtEdge_ = false;

    RectF firstRect(3, 3, 5, 5);
    RectF secondRect(4, 4, 6, 6);

    textSelectOverlay->CalcHandleLevelMode(firstRect, secondRect);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::EMBED);

    firstRect.SetRect(3, 3, 5, 5);
    secondRect.SetRect(11, 11, 15, 15);

    textSelectOverlay->CalcHandleLevelMode(firstRect, secondRect);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: OnAncestorNodeChanged001
 * @tc.desc: test base_text_select_overlay.cpp OnAncestorNodeChanged function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, OnAncestorNodeChanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    FrameNodeChangeInfoFlag frameNodeChangeInfoFlag = 0;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_START_SCROLL;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_START_ANIMATION;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_TRANSFORM_CHANGE;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);

    frameNodeChangeInfoFlag = FRAME_NODE_CHANGE_GEOMETRY_CHANGE;
    textSelectOverlay->OnAncestorNodeChanged(frameNodeChangeInfoFlag);
    EXPECT_EQ(textSelectOverlay->handleLevelMode_, HandleLevelMode::OVERLAY);
}

/**
 * @tc.name: OnHandleMarkInfoChange001
 * @tc.desc: test base_text_select_overlay.cpp OnHandleMarkInfoChange function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, OnHandleMarkInfoChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    SelectOverlayDirtyFlag flag = UPDATE_HANDLE_COLOR_FLAG;
    textSelectOverlay->OnHandleMarkInfoChange(shareOverlayInfo, flag);
    EXPECT_EQ(shareOverlayInfo->handlerColor, std::nullopt);
}

/**
 * @tc.name: GetSpanParagraphStyle001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp GetSpanParagraphStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSpanParagraphStyle001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    ParagraphStyle pStyle;

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->textLineStyle->UpdateMaxLines(1024);
    spanItem->textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);
    spanItem->textLineStyle->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    spanItem->textLineStyle->UpdateLeadingMargin(LeadingMargin());
    textLayoutAlgorithm->GetSpanParagraphStyle(nullptr, spanItem, pStyle);
    EXPECT_EQ(pStyle.maxLines, 1024);
    EXPECT_EQ(pStyle.ellipsisMode, EllipsisMode::HEAD);
    EXPECT_EQ(pStyle.lineBreakStrategy, LineBreakStrategy::GREEDY);
}

/**
 * @tc.name: FontRegisterCallback001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp FontRegisterCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, FontRegisterCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    auto oldFontManager = pipeline->fontManager_;
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();

    TextStyle textStyle;
    std::vector<std::string> fontFamilies;

    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    textStyle.SetFontFamilies(fontFamilies);

    textLayoutAlgorithm->FontRegisterCallback(frameNode, textStyle);
    EXPECT_EQ(pattern->GetIsCustomFont(), false);

    pipeline->fontManager_ = oldFontManager;
}

/**
 * @tc.name: UpdateTextColorIfForeground001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp UpdateTextColorIfForeground function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateTextColorIfForeground001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    TextStyle textStyle;

    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::INVERT);
    textLayoutAlgorithm->UpdateTextColorIfForeground(frameNode, textStyle);
    EXPECT_EQ(textStyle.GetTextColor(), Color::FOREGROUND);

    textStyle.SetTextColor(Color::BLACK);
    renderContext->UpdateForegroundColor(Color::BLACK);

    auto layoutProperty = AceType::DynamicCast<TextLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_NE(layoutProperty->GetTextColorValue(Color::RED), Color::BLACK);
}

/**
 * @tc.name: SetPropertyToModifier001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp SetPropertyToModifier function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, SetPropertyToModifier001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    TextStyle textStyle;

    auto layoutProperty = AceType::DynamicCast<TextLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    auto modifier = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(textStyle), pattern);
    ASSERT_NE(modifier, nullptr);

    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    layoutProperty->UpdateFontFamily(fontFamilies);
    layoutProperty->UpdateAdaptMaxFontSize(Dimension(1.0));
    layoutProperty->UpdateTextDecorationStyle(TextDecorationStyle::SOLID);
    textLayoutAlgorithm->SetPropertyToModifier(layoutProperty, modifier, textStyle);
    EXPECT_EQ(modifier->textDecorationStyle_, TextDecorationStyle::SOLID);
}

/**
 * @tc.name: UpdateParagraphBySpan001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp UpdateParagraphBySpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateParagraphBySpan001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto spanNode = AceType::MakeRefPtr<ImageSpanNode>("Test1", 1, pattern);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    textLayoutAlgorithm->spans_.emplace_back(spanItem);

    ParagraphStyle paraStyle;
    TextStyle textStyle;

    paraStyle.maxLines = 1024;
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    textLayoutAlgorithm->spanStringHasMaxLines_ = true;
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    textLayoutAlgorithm->spanStringHasMaxLines_ = false;
    textLayoutAlgorithm->isSpanStringMode_ = true;
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    textLayoutAlgorithm->paragraphManager_->AddParagraph(
        { .paragraph = paragraph, .start = 0, .end = 2 });
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);

    std::list<RefPtr<SpanItem>> group;
    spanNode = AceType::MakeRefPtr<ImageSpanNode>("Test2", 2, pattern);
    ASSERT_NE(spanNode, nullptr);
    spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanItem, nullptr);
    group.emplace_back(spanItem);
    auto spanNode1 = AceType::MakeRefPtr<PlaceholderSpanNode>("Test", 3, pattern);
    ASSERT_NE(spanNode1, nullptr);
    auto spanItem1 = spanNode1->GetSpanItem();
    ASSERT_NE(spanItem1, nullptr);
    group.emplace_back(spanItem1);
    textLayoutAlgorithm->spans_.emplace_back(group);
    EXPECT_EQ(textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle), true);
}

/**
 * @tc.name: UpdateParagraphByCustomSpan001
 * @tc.desc: test multiple_paragraph_layout_algorithm.cpp UpdateParagraphByCustomSpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateParagraphByCustomSpan001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    auto oldTheme = pipeline->themeManager_;
    pipeline->themeManager_ = theme;

    auto customSpanItem = AceType::MakeRefPtr<CustomSpanItem>();
    ASSERT_NE(customSpanItem, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t spanTextLength;
    CustomSpanPlaceholderInfo customSpanPlaceholder;

    textLayoutAlgorithm->UpdateParagraphByCustomSpan(
        customSpanItem, AceType::RawPtr(layoutWrapper), paragraph, spanTextLength, customSpanPlaceholder);
    EXPECT_EQ(customSpanPlaceholder.onDraw, nullptr);

    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateFontSize(Dimension(10.0));
    customSpanItem->onMeasure = [](CustomSpanMeasureInfo info)->CustomSpanMetrics {
        return CustomSpanMetrics();
    };
    customSpanItem->onDraw = [](NG::DrawingContext& context, CustomSpanOptions options) {
    };

    textLayoutAlgorithm->UpdateParagraphByCustomSpan(
        customSpanItem, AceType::RawPtr(layoutWrapper), paragraph, spanTextLength, customSpanPlaceholder);
    EXPECT_NE(customSpanPlaceholder.onDraw, nullptr);

    pipeline->themeManager_ = oldTheme;
}

/**
 * @tc.name: UpdateParagraph001
 * @tc.desc: test span_node.cpp UpdateParagraph function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateParagraph001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    auto fontManager = AceType::MakeRefPtr<MockFontManager>();
    ASSERT_NE(fontManager, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    auto oldFontManager = pipeline->fontManager_;
    pipeline->fontManager_ = fontManager;

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    spanItem->UpdateParagraph(frameNode, paragraph, true);

    pattern->textDetectEnable_ = true;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(spanItem->UpdateParagraph(frameNode, paragraph, true), -1);

    spanItem->aiSpanMap.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(spanItem->UpdateParagraph(frameNode, paragraph, true), -1);

    pipeline->fontManager_ = oldFontManager;
}

/**
 * @tc.name: UpdateSymbolSpanParagraph001
 * @tc.desc: test span_node.cpp UpdateSymbolSpanParagraph function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolSpanParagraph001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount](){ callPushStyleCount++; });

    EXPECT_EQ(callPushStyleCount, 0);

    spanItem->fontStyle->UpdateFontSize(Dimension(0));
    spanItem->UpdateSymbolSpanParagraph(nullptr, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 0);

    std::unique_ptr<FontStyle> oldFontStyle = std::move(spanItem->fontStyle);
    std::unique_ptr<TextLineStyle> oldTextLineStyle = std::move(spanItem->textLineStyle);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    spanItem->textLineStyle = std::move(oldTextLineStyle);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    spanItem->fontStyle = std::move(oldFontStyle);
    spanItem->UpdateSymbolSpanParagraph(frameNode, TextStyle(), paragraph);
    EXPECT_EQ(callPushStyleCount, 1);
}

/**
 * @tc.name: UpdateSymbolSpanColor001
 * @tc.desc: test span_node.cpp UpdateSymbolSpanColor function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateSymbolSpanColor001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    TextStyle symbolSpanStyle;

    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextColor(Color::BLACK);

    spanItem->SetIsParentText(true);
    symbolSpanStyle.renderColors_.clear();
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);

    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);

    spanItem->SetIsParentText(false);
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);
}

/**
 * @tc.name: FontRegisterCallback002
 * @tc.desc: test span_node.cpp FontRegisterCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, FontRegisterCallback002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    TextStyle textStyle;
    std::vector<std::string> fontFamilies;

    spanItem->FontRegisterCallback(frameNode, textStyle);

    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    auto oldFontManager = pipeline->fontManager_;
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();

    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    textStyle.SetFontFamilies(fontFamilies);

    spanItem->FontRegisterCallback(frameNode, textStyle);
    EXPECT_EQ(pattern->GetIsCustomFont(), false);

    pipeline->fontManager_ = oldFontManager;
}

/**
 * @tc.name: UpdateTextStyle001
 * @tc.desc: test span_node.cpp UpdateTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode and paragraph.
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetTextDetectEnable(true);
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->spanItem_->position = StringUtils::ToWstring(CREATE_VALUE).length();
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle).Times(AnyNumber());
    /**
     * @tc.steps: step2. call StartDrag
     * @tc.expected: IsDragging() return ture
     */
    spanNode->spanItem_->StartDrag(1, 2);
    EXPECT_TRUE(spanNode->spanItem_->IsDragging());
    /**
     * @tc.steps: step3. call UpdateTextStyle
     * @tc.expected: cover branch content is empty.
     */
    std::string spanContent;
    EXPECT_TRUE(spanNode->spanItem_->IsDragging());
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 1, 2);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step4. call UpdateTextStyle
     * @tc.expected: cover branch selStart > 0, selEnd < contentLength.
     */
    spanContent = CREATE_VALUE;
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 1, 2);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step5. call UpdateTextStyle
     * @tc.expected: cover branch selStart < 0, selEnd < 0.
     */
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, -1, -1);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step6. call UpdateTextStyle
     * @tc.expected: cover branch selStart > contentLength, selEnd > contentLength.
     */
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 20, 20);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    MockParagraph::TearDown();
}

/**
 * @tc.name: EncodeTlv002
 * @tc.desc: test span_node.cpp EncodeTlv function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, EncodeTlv002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::vector<uint8_t> buff;
    int32_t cursor = 1;

    EXPECT_EQ(spanItem->EncodeTlv(buff), true);
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->fontStyle->HasFontSize(), false);

    cursor = 0;
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->fontStyle->HasFontSize(), false);

    cursor = 0;
    buff.clear();

    spanItem->fontStyle->UpdateFontSize(Dimension(10.0, DimensionUnit::PX));
    spanItem->fontStyle->UpdateTextColor(Color::WHITE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    spanItem->fontStyle->UpdateTextShadow({ textShadow });
    spanItem->fontStyle->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    spanItem->fontStyle->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    spanItem->fontStyle->UpdateFontFamily(fontFamilies);
    spanItem->fontStyle->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    spanItem->fontStyle->UpdateTextDecoration(TextDecoration::OVERLINE);
    spanItem->fontStyle->UpdateTextDecorationColor(Color::WHITE);
    spanItem->fontStyle->UpdateTextDecorationStyle(TextDecorationStyle::SOLID);
    spanItem->fontStyle->UpdateTextCase(TextCase::LOWERCASE);
    spanItem->fontStyle->UpdateAdaptMinFontSize(12.0_fp);
    spanItem->fontStyle->UpdateAdaptMaxFontSize(10.0_fp);
    spanItem->fontStyle->UpdateLetterSpacing(Dimension(10.0, DimensionUnit::PX));
    spanItem->backgroundStyle = TextBackgroundStyle();

    EXPECT_EQ(spanItem->EncodeTlv(buff), true);
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->fontStyle->HasFontSize(), true);
}

/**
 * @tc.name: EncodeTlv003
 * @tc.desc: test span_node.cpp EncodeTlv function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, EncodeTlv003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::vector<uint8_t> buff;
    int32_t cursor = 0;

    spanItem->textLineStyle->UpdateLineHeight(Dimension(10.0, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateLineSpacing(Dimension(1.0, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateTextBaseline(TextBaseline::MIDDLE);
    spanItem->textLineStyle->UpdateBaselineOffset(Dimension(20.0, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateTextOverflow(TextOverflow::DEFAULT);
    spanItem->textLineStyle->UpdateTextAlign(TextAlign::LEFT);
    spanItem->textLineStyle->UpdateMaxLength(1024);
    spanItem->textLineStyle->UpdateMaxLines(1024);
    spanItem->textLineStyle->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    spanItem->textLineStyle->UpdateTextIndent(Dimension(40, DimensionUnit::PX));
    spanItem->textLineStyle->UpdateLeadingMargin(LeadingMargin());
    spanItem->textLineStyle->UpdateWordBreak(WordBreak::NORMAL);
    spanItem->textLineStyle->UpdateLineBreakStrategy(LineBreakStrategy::GREEDY);
    spanItem->textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);

    TextBackgroundStyle textBackgroundStyle;
    textBackgroundStyle.backgroundColor = Color::BLACK;
    textBackgroundStyle.backgroundRadius = NG::BorderRadiusProperty();
    spanItem->backgroundStyle = textBackgroundStyle;

    EXPECT_EQ(spanItem->EncodeTlv(buff), true);
    EXPECT_EQ(spanItem->DecodeTlv(buff, cursor)->textLineStyle->HasLineHeight(), true);
}

/**
 * @tc.name: SymbolColorToString001
 * @tc.desc: test span_node.cpp SymbolColorToString function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, SymbolColorToString001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);

    std::vector<Color> colorList;
    colorList.emplace_back(Color::WHITE);
    colorList.emplace_back(Color::BLACK);
    spanItem->fontStyle->UpdateSymbolColorList(colorList);

    EXPECT_EQ(spanItem->SymbolColorToString(), "[#FFFFFFFF,#FF000000,]");
}

/**
 * @tc.name: GetSpanResultObject001
 * @tc.desc: test span_node.cpp GetSpanResultObject function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetSpanResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode.
     */
    RefPtr<ImageSpanItem> spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->interval = {0, 10};
    auto obj = spanItem->GetSpanResultObject(1, 10);
    EXPECT_FALSE(obj.isInit);
    obj = spanItem->GetSpanResultObject(0, 9);
    EXPECT_FALSE(obj.isInit);
    /**
     * @tc.steps: step2. call GetSpanResultObject
     * @tc.expected: cover branch imagePixelMap and image don't have value.
     */
    std::optional<std::string> image;
    std::optional<RefPtr<PixelMap>> pixelMap;
    ImageSpanOptions options1 = { .image = image, .imagePixelMap = pixelMap };
    spanItem->SetImageSpanOptions(options1);
    obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    /**
     * @tc.steps: step3. call GetSpanResultObject
     * @tc.expected: cover branch imagePixelMap and image have value.
     */
    image = std::make_optional("app.media.icon");
    pixelMap = PixelMap::CreatePixelMap(nullptr);
    ImageSpanOptions options2 = { .image = image, .imagePixelMap = pixelMap };
    spanItem->SetImageSpanOptions(options2);
    obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    EXPECT_EQ(obj.valueString, image);
    EXPECT_EQ(obj.valuePixelMap, pixelMap.value());
}

/**
 * @tc.name: GetFontInJson001
 * @tc.desc: test text_pattern.cpp GetFontInJson function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetFontInJson001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    textPattern->textStyle_ = TextStyle();

    EXPECT_GT(textPattern->GetFontInJson().size(), 0);

    textPattern->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));

    EXPECT_GT(textPattern->GetFontInJson().size(), 0);
}

/**
 * @tc.name: InitClickEvent001
 * @tc.desc: test text_pattern.cpp InitClickEvent function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, InitClickEvent001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    eventHub->AttachHost(textFrameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    textPattern->InitClickEvent(gestureEventHub);

    KeyEvent event;
    event.code = KeyCode::KEY_TAB;
    event.action = KeyAction::DOWN;

    EXPECT_EQ(gestureEventHub->KeyBoardShortCutClick(event, textFrameNode), true);

    auto sysJudgeFunc = gestureEventHub->clickEventActuator_->GetSysJudgeFunc();
    ASSERT_NE(sysJudgeFunc.has_value(), false);

    auto gestureInfo = AceType::MakeRefPtr<GestureInfo>();
    ASSERT_NE(gestureInfo, nullptr);
    auto info = std::make_shared<BaseGestureEvent>();
    ASSERT_NE(info, nullptr);

    EXPECT_EQ(sysJudgeFunc.value()(gestureInfo, info), GestureJudgeResult::CONTINUE);

    std::list<FingerInfo> fingerList;
    fingerList.emplace_back(FingerInfo());
    info->SetFingerList(fingerList);

    EXPECT_EQ(sysJudgeFunc.value()(gestureInfo, info), GestureJudgeResult::REJECT);

    textPattern->textDetectEnable_ = true;
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(0, AISpan()));

    EXPECT_EQ(sysJudgeFunc.value()(gestureInfo, info), GestureJudgeResult::CONTINUE);
}

/**
 * @tc.name: SetOnClickMenu001
 * @tc.desc: test text_pattern.cpp SetOnClickMenu function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, SetOnClickMenu001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    bool calledCalculateHandleFunc = false;
    bool calledShowSelectOverlayFunc = false;

    AISpan aiSpan;
    CalculateHandleFunc calculateHandleFunc = [&calledCalculateHandleFunc]() {
        calledCalculateHandleFunc = true;
    };
    ShowSelectOverlayFunc showSelectOverlayFunc = [&calledShowSelectOverlayFunc](const RectF&, const RectF&) {
        calledShowSelectOverlayFunc = true;
    };

    textPattern->SetOnClickMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);

    auto func = textPattern->dataDetectorAdapter_->onClickMenu_;
    ASSERT_NE(func, nullptr);

    func("复制");
    EXPECT_EQ(calledCalculateHandleFunc, false);
    EXPECT_EQ(calledShowSelectOverlayFunc, false);

    textPattern->copyOption_ = CopyOptions::InApp;
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);

    func("");
    func("复制");
    func("选择文本");

    calledCalculateHandleFunc = false;
    calledShowSelectOverlayFunc = false;

    textPattern->SetOnClickMenu(aiSpan, nullptr, showSelectOverlayFunc);
    func = textPattern->dataDetectorAdapter_->onClickMenu_;
    ASSERT_NE(func, nullptr);

    func("选择文本");
    EXPECT_EQ(calledCalculateHandleFunc, false);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: test text_pattern.cpp ToJsonValue function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, ToJsonValue001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    InspectorFilter filter;

    auto firstJson = JsonUtil::Create(true);
    ASSERT_NE(firstJson, nullptr);
    textPattern->textStyle_ = TextStyle();

    textPattern->ToJsonValue(firstJson, filter);
    EXPECT_NE(firstJson->ToString(), "{}");

    auto secondJson = JsonUtil::Create(true);
    ASSERT_NE(secondJson, nullptr);
    textPattern->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));

    textPattern->ToJsonValue(secondJson, filter);
    EXPECT_NE(secondJson->ToString(), "{}");

    filter.AddFilterAttr("id");

    auto thirdJson = JsonUtil::Create(true);
    ASSERT_NE(thirdJson, nullptr);

    textPattern->ToJsonValue(thirdJson, filter);
    EXPECT_EQ(thirdJson->ToString(), "{}");
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test text_pattern.cpp GetThumbnailCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetThumbnailCallback001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    auto func = textPattern->GetThumbnailCallback();
    ASSERT_NE(func, nullptr);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_EQ(textPattern->dragNode_, nullptr);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    textFrameNode->draggable_ = true;
    textFrameNode->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(0, 3);
    textPattern->textForDisplay_ = TEXT_CONTENT;

    func = textPattern->GetThumbnailCallback();
    ASSERT_NE(func, nullptr);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_NE(textPattern->dragNode_, nullptr);

    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(childFrameNode, nullptr);
    auto childPattern = childFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(childPattern, nullptr);
    textPattern->childNodes_.emplace_back(childFrameNode);

    func = textPattern->GetThumbnailCallback();
    ASSERT_NE(func, nullptr);

    auto children = textPattern->GetChildNodes();
    EXPECT_EQ(children.size(), 1);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_NE(textPattern->dragNode_, nullptr);
}

/**
 * @tc.name: UpdateContainerChildren001
 * @tc.desc: test text_pattern.cpp UpdateContainerChildren function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateContainerChildren001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto parentNode = AceType::MakeRefPtr<ContainerSpanNode>(1);
    ASSERT_NE(parentNode, nullptr);

    auto textframeNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textframeNode, nullptr);
    frameNode->AddChild(textframeNode);
    textframeNode->SetParent(frameNode);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageSpanNode, nullptr);
    frameNode->AddChild(imageSpanNode);
    imageSpanNode->SetParent(frameNode);
    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(spanNode, nullptr);
    frameNode->AddChild(spanNode);
    spanNode->SetParent(frameNode);

    auto imageLayoutProperty = imageSpanNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    pattern->UpdateContainerChildren(parentNode, textframeNode);
    pattern->UpdateContainerChildren(parentNode, imageSpanNode);
    pattern->UpdateContainerChildren(parentNode, spanNode);
    EXPECT_EQ(imageLayoutProperty->HasPlaceHolderStyle(), false);

    spanNode->SetHasTextBackgroundStyle(true);
    pattern->UpdateContainerChildren(parentNode, spanNode);

    imageLayoutProperty->UpdateHasPlaceHolderStyle(true);
    pattern->UpdateContainerChildren(parentNode, imageSpanNode);
    EXPECT_EQ(imageLayoutProperty->HasPlaceHolderStyle(), false);
    imageLayoutProperty->UpdateHasPlaceHolderStyle(false);

    parentNode->SetTextBackgroundStyle(TextBackgroundStyle());
    pattern->UpdateContainerChildren(parentNode, imageSpanNode);
    EXPECT_EQ(imageLayoutProperty->HasPlaceHolderStyle(), true);
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test text_pattern.cpp HandleSurfaceChanged function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, HandleSurfaceChanged001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    pattern->selectOverlay_->OnBind(manager);
    SelectOverlayInfo info;
    manager->CreateSelectOverlay(info);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateMaxLines(0);

    pattern->HandleSurfaceChanged(100, 100, 100, 100);
    pattern->HandleSurfaceChanged(100, 100, 10, 100);
    pattern->HandleSurfaceChanged(100, 100, 100, 10);
    pattern->HandleSurfaceChanged(100, 100, 10, 10);

    manager->shareOverlayInfo_->menuInfo.menuType = OptionMenuType::MOUSE_MENU;

    pattern->HandleSurfaceChanged(100, 100, 10, 10);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
}

/**
 * @tc.name: MountImageNode001
 * @tc.desc: test text_pattern.cpp MountImageNode function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, MountImageNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto imageSpanItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    ASSERT_NE(imageSpanItem, nullptr);

    imageSpanItem->options.imageAttribute = ImageSpanAttribute();

    pattern->MountImageNode(imageSpanItem);

    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        imageSpanItem->imageNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_EQ(imageLayoutProperty->HasImageFit(), false);

    imageSpanItem->options.imageAttribute->size = ImageSpanSize();
    imageSpanItem->options.imageAttribute->verticalAlign = VerticalAlign();
    imageSpanItem->options.imageAttribute->objectFit = ImageFit();
    imageSpanItem->options.imageAttribute->marginProp = OHOS::Ace::NG::MarginProperty();
    imageSpanItem->options.imageAttribute->borderRadius = OHOS::Ace::NG::BorderRadiusProperty();
    imageSpanItem->options.imageAttribute->paddingProp = OHOS::Ace::NG::PaddingProperty();

    pattern->MountImageNode(imageSpanItem);

    imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        imageSpanItem->imageNodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->HasImageFit(), true);
}

/**
 * @tc.name: PaintImage001
 * @tc.desc: test text_content_modifier.cpp PaintImage function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, PaintImage001, TestSize.Level1)
{
    auto oldVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);

    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    int32_t callOnDrawCount = 0;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo {
        .customSpanIndex = 0,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) { callOnDrawCount++; }
    };
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholder);

    bool calledDrawRect = false;
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 10; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        auto imagePattern = imageNode->GetPattern<ImagePattern>();
        auto mockCanvasImage = AceType::MakeRefPtr<NG::MockCanvasImage>();
        EXPECT_CALL(
            *mockCanvasImage, DrawRect(_, _, _)).WillRepeatedly([&calledDrawRect]() { calledDrawRect = true; });
        imagePattern->altImage_ = mockCanvasImage;
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        if (i > 0) {
            imageNodeLocalList.emplace_back(imageNode);
        }
    }
    textContentModifier->SetImageSpanNodeList(imageNodeList);

    RSCanvas canvas;

    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, false);

    std::vector<int32_t> placeholderIndex = { 0 };
    std::vector<RectF> rectsForPlaceholders = { RectF(0, 0, 10, 10) };
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, OffsetF(0, 0));

    calledDrawRect = false;
    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, true);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(oldVersion);
}

/**
 * @tc.name: PaintImage002
 * @tc.desc: test text_content_modifier.cpp PaintImage function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, PaintImage002, TestSize.Level1)
{
    auto oldVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(13);

    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    int32_t callOnDrawCount = 0;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo {
        .customSpanIndex = 0,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) { callOnDrawCount++; }
    };
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholder);

    bool calledDrawRect = false;
    std::vector<RefPtr<FrameNode>> imageNodeLocalList;
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    for (int i = 0; i < 10; i++) {
        auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
			ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<ImagePattern>(); });
        auto imagePattern = imageNode->GetPattern<ImagePattern>();
        auto mockCanvasImage = AceType::MakeRefPtr<NG::MockCanvasImage>();
        EXPECT_CALL(
            *mockCanvasImage, DrawRect(_, _, _)).WillRepeatedly([&calledDrawRect]() { calledDrawRect = true; });
        imagePattern->altImage_ = mockCanvasImage;
        imageNodeList.emplace_back(AceType::WeakClaim(AceType::RawPtr(imageNode)));
        if (i > 0) {
            imageNodeLocalList.emplace_back(imageNode);
        }
    }
    textContentModifier->SetImageSpanNodeList(imageNodeList);

    std::vector<int32_t> placeholderIndex = { -1 };
    std::vector<RectF> rectsForPlaceholders = { RectF(0, 0, 10, 10) };
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, OffsetF(0, 0));

    RSCanvas canvas;

    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, false);

    placeholderIndex[0] = 1;
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, OffsetF(0, 0));

    textContentModifier->PaintImage(canvas, 10, 10);
    EXPECT_EQ(calledDrawRect, false);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(oldVersion);
}

/**
 * @tc.name: PaintCustomSpan001
 * @tc.desc: test text_content_modifier.cpp PaintCustomSpan function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, PaintCustomSpan001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    int32_t callOnDrawCount = 0;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholder;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo0;
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo1 {
        .customSpanIndex = 0,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) {
            callOnDrawCount++;
        }
    };
    CustomSpanPlaceholderInfo customSpanPlaceholderInfo2 {
        .customSpanIndex = 1,
        .onDraw = [&callOnDrawCount](NG::DrawingContext&, CustomSpanOptions) {
            callOnDrawCount++;
        }
    };
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo0);
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo1);
    customSpanPlaceholder.emplace_back(customSpanPlaceholderInfo2);
    pattern->InitCustomSpanPlaceholderInfo(customSpanPlaceholder);
    std::vector<int32_t> placeholderIndex = { 0 };
    std::vector<RectF> rectsForPlaceholders = { RectF(0, 0, 10, 10) };
    OffsetF contentOffset(0, 0);
    pattern->InitSpanImageLayout(placeholderIndex, rectsForPlaceholders, contentOffset);

    RSCanvas canvas;
    DrawingContext drawingContext = { canvas, 10, 10 };

    textContentModifier->PaintCustomSpan(drawingContext);
    EXPECT_EQ(callOnDrawCount, 1);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: test text_content_modifier.cpp onDraw function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, onDraw001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    bool calledClipRect = false;
    bool calledAttachBrush = false;
    Testing::TestingCanvas retCanvas;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly([&calledClipRect]() { calledClipRect = true; });
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(
        [&calledAttachBrush, &retCanvas](const Testing::TestingBrush& brush)->Testing::TestingCanvas& {
            calledAttachBrush = true;
            return retCanvas;
            }
        );
    DrawingContext drawingContext = { canvas, 10, 10 };

    textContentModifier->onDraw(drawingContext);
    EXPECT_EQ(calledClipRect, true);

    textContentModifier->animatableTextColor_ =
        AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    textContentModifier->ifPaintObscuration_ = true;
    textContentModifier->drawObscuredRects_.emplace_back(RectF(0, 0, 10, 10));

    textContentModifier->onDraw(drawingContext);
    EXPECT_EQ(calledAttachBrush, true);
}

/**
 * @tc.name: ModifyAdaptMinFontSizeInTextStyle001
 * @tc.desc: test text_content_modifier.cpp ModifyAdaptMinFontSizeInTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, ModifyAdaptMinFontSizeInTextStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    TextStyle textStyle;

    textContentModifier->adaptMinFontSize_ = Dimension(10);
    textContentModifier->ModifyAdaptMinFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize().Value(), 0);

    textContentModifier->adaptMinFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10);
    textContentModifier->ModifyAdaptMinFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize().Value(), 10);
}

/**
 * @tc.name: ModifyAdaptMaxFontSizeInTextStyle001
 * @tc.desc: test text_content_modifier.cpp ModifyAdaptMaxFontSizeInTextStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, ModifyAdaptMaxFontSizeInTextStyle001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    TextStyle textStyle;

    textContentModifier->adaptMaxFontSize_ = Dimension(10);
    textContentModifier->ModifyAdaptMaxFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize().Value(), 0);

    textContentModifier->adaptMaxFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(10);
    textContentModifier->ModifyAdaptMaxFontSizeInTextStyle(textStyle);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize().Value(), 10);
}

/**
 * @tc.name: UpdateAdaptMinFontSizeMeasureFlag001
 * @tc.desc: test text_content_modifier.cpp UpdateAdaptMinFontSizeMeasureFlag function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateAdaptMinFontSizeMeasureFlag001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    PropertyChangeFlag flag = PROPERTY_UPDATE_NORMAL;

    textContentModifier->adaptMinFontSize_ = Dimension(10);
    textContentModifier->UpdateAdaptMinFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_NORMAL);

    textContentModifier->adaptMinFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(20);
    textContentModifier->UpdateAdaptMinFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: UpdateAdaptMaxFontSizeMeasureFlag001
 * @tc.desc: test text_content_modifier.cpp UpdateAdaptMaxFontSizeMeasureFlag function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UpdateAdaptMaxFontSizeMeasureFlag001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    PropertyChangeFlag flag = PROPERTY_UPDATE_NORMAL;

    textContentModifier->adaptMaxFontSize_ = Dimension(10);
    textContentModifier->UpdateAdaptMaxFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_NORMAL);

    textContentModifier->adaptMaxFontSizeFloat_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(20);
    textContentModifier->UpdateAdaptMaxFontSizeMeasureFlag(flag);
    EXPECT_EQ(flag, PROPERTY_UPDATE_MEASURE);
}

/**
 * @tc.name: ResumeAnimation001
 * @tc.desc: test text_content_modifier.cpp ResumeAnimation function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, ResumeAnimation001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CreateModifier();
    auto textContentModifier = pattern->contentMod_;
    ASSERT_NE(textContentModifier, nullptr);

    AnimationOption option = AnimationOption();
    textContentModifier->raceAnimation_ = AnimationUtils::StartAnimation(option, [&]() {}, []() {});

    textContentModifier->marqueeState_ = MarqueeState::PAUSED;
    textContentModifier->ResumeAnimation();
    EXPECT_EQ(textContentModifier->marqueeState_, MarqueeState::RUNNING);
    textContentModifier->PauseAnimation();
    EXPECT_EQ(textContentModifier->marqueeState_, MarqueeState::PAUSED);
}

/**
 * @tc.name: UseSelfStyle001
 * @tc.desc: test text_styles.cpp UseSelfStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UseSelfStyle001, TestSize.Level1)
{
    auto fontStyle = std::make_unique<FontStyle>();
    TextStyle textStyle;

    fontStyle->UpdateFontSize(Dimension(10.0, DimensionUnit::PX));
    fontStyle->UpdateTextColor(Color::WHITE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    fontStyle->UpdateTextShadow({ textShadow });
    fontStyle->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    fontStyle->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    fontStyle->UpdateFontFamily(fontFamilies);
    fontStyle->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    fontStyle->UpdateTextDecoration(TextDecoration::OVERLINE);
    fontStyle->UpdateTextDecorationColor(Color::WHITE);
    fontStyle->UpdateTextDecorationStyle(TextDecorationStyle::SOLID);
    fontStyle->UpdateTextCase(TextCase::LOWERCASE);
    fontStyle->UpdateAdaptMinFontSize(12.0_fp);
    fontStyle->UpdateAdaptMaxFontSize(10.0_fp);
    fontStyle->UpdateLetterSpacing(Dimension(10.0, DimensionUnit::PX));
    std::vector<Color> colorList;
    colorList.emplace_back(Color::WHITE);
    colorList.emplace_back(Color::BLACK);
    fontStyle->UpdateSymbolColorList(colorList);
    fontStyle->UpdateSymbolRenderingStrategy(2);
    fontStyle->UpdateSymbolEffectStrategy(0);
    fontStyle->UpdateSymbolEffectOptions(SymbolEffectOptions(SymbolEffectType::BOUNCE));
    fontStyle->UpdateMinFontScale(1.0);
    fontStyle->UpdateMaxFontScale(2.0);

    EXPECT_EQ(textStyle.GetSymbolEffectOptions().has_value(), false);
    UseSelfStyle(fontStyle, nullptr, textStyle);
    EXPECT_EQ(textStyle.GetSymbolEffectOptions().has_value(), true);
}

/**
 * @tc.name: UseSelfStyle002
 * @tc.desc: test text_styles.cpp UseSelfStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UseSelfStyle002, TestSize.Level1)
{
    auto textLineStyle = std::make_unique<TextLineStyle>();
    TextStyle textStyle;

    textLineStyle->UpdateLineHeight(Dimension(10.0, DimensionUnit::PX));
    textLineStyle->UpdateLineSpacing(Dimension(1.0, DimensionUnit::PX));
    textLineStyle->UpdateTextBaseline(TextBaseline::MIDDLE);
    textLineStyle->UpdateBaselineOffset(Dimension(20.0, DimensionUnit::PX));
    textLineStyle->UpdateTextOverflow(TextOverflow::DEFAULT);
    textLineStyle->UpdateTextAlign(TextAlign::LEFT);
    textLineStyle->UpdateMaxLines(1024);
    textLineStyle->UpdateTextIndent(Dimension(40, DimensionUnit::PX));
    textLineStyle->UpdateWordBreak(WordBreak::NORMAL);
    textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);

    UseSelfStyle(nullptr, textLineStyle, textStyle);
    EXPECT_EQ(textStyle.GetLineSpacing(), Dimension(1.0, DimensionUnit::PX));
}

/**
 * @tc.name: CreateTextStyleUsingThemeWithText001
 * @tc.desc: test text_styles.cpp CreateTextStyleUsingThemeWithText function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, CreateTextStyleUsingThemeWithText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto fontStyle = std::make_unique<FontStyle>();
    auto textLineStyle = std::make_unique<TextLineStyle>();
    RefPtr<TextTheme> textTheme;

    auto textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, textTheme);
    EXPECT_EQ(textStyle, TextStyle());

    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::INVERT);
    textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, textTheme);
    EXPECT_EQ(textStyle.GetTextColor(), Color::FOREGROUND);

    renderContext->UpdateForegroundColor(Color::BLACK);
    textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, textTheme);
    EXPECT_EQ(textStyle.GetTextColor(), Color::FOREGROUND);
}

/**
 * @tc.name: GetLineBreakStrategyInJson001
 * @tc.desc: test text_styles.cpp GetLineBreakStrategyInJson function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, GetLineBreakStrategyInJson001, TestSize.Level1)
{
    std::optional<Ace::LineBreakStrategy> value = Ace::LineBreakStrategy::HIGH_QUALITY;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "HIGH_QUALITY");
    value = Ace::LineBreakStrategy::BALANCED;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "BALANCED");
    value = Ace::LineBreakStrategy::GREEDY;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "GREEDY");
}

/**
 * @tc.name: TxtParagraphUpdateColor001
 * @tc.desc: test txt_paragraph.cpp UpdateColor function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, TxtParagraphUpdateColor001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->UpdateFontColor(Color::BLACK);

    RefPtr<Paragraph> paragraph = Paragraph::Create(nullptr);
    ASSERT_NE(paragraph, nullptr);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });
    pattern->UpdateFontColor(Color::BLACK);
}

/**
 * @tc.name: UnRegisterAfterLayoutCallback001
 * @tc.desc: test text_pattern.cpp UnRegisterAfterLayoutCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestFiveNg, UnRegisterAfterLayoutCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->RegisterAfterLayoutCallback([]() {});
    EXPECT_EQ(pattern->afterLayoutCallback_.has_value(), true);
    pattern->UnRegisterAfterLayoutCallback();
    EXPECT_EQ(pattern->afterLayoutCallback_.has_value(), false);
}
} // namespace OHOS::Ace::NG
