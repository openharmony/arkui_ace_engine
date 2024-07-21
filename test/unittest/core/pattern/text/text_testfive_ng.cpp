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
#include "core/components_ng/render/adapter/pixelmap_image.h"

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
    ASSERT_EQ(selectedText, "");
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
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);

    pattern->image_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    ASSERT_NE(pattern->image_, nullptr);
    EXPECT_EQ(textContentModifier->DrawImage(frameNode, canvas, 0, 0, rect), false);

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
        content, layoutWrapper.GetRawPtr()), TextDirection::RTL);
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
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    auto spanNode = AceType::MakeRefPtr<SpanNode>(1);
    ASSERT_NE(spanNode, nullptr);
    auto spanItem = spanNode->GetSpanItem();
    ASSERT_NE(spanNode, nullptr);

    EXPECT_EQ(spanItem->InheritParentProperties(frameNode, true), TextStyle());
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
        textStyle, content, stepUnit, contentConstraint, layoutWrapper.GetRawPtr()), false);

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
} // namespace OHOS::Ace::NG
