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

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/text/text_model_ng.h"


namespace OHOS::Ace::NG {

namespace {
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
} // namespace

class TextTestThreeNg : public TextBases {
public:
};

/**
 * @tc.name: InitSpanItem001
 * @tc.desc: test test_pattern.h InitSpanItem function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, InitSpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    /**
     * @tc.steps: step2. construct different child SpanNode.
     */
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto childFrameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    host->AddChild(childFrameNode);
    childFrameNode->SetParent(host);

    auto spanNode = CreateSpanNodeWithSetDefaultProperty(u"spannode");
    auto spanOnClickFunc = [](GestureEvent& info) {};
    spanNode->UpdateOnClickEvent(std::move(spanOnClickFunc));
    host->AddChild(spanNode);
    spanNode->SetParent(host);

    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto symbolSpanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, nodeId);
    host->AddChild(symbolSpanNode);
    symbolSpanNode->SetParent(host);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    host->AddChild(placeholderSpanNode);
    placeholderSpanNode->SetParent(host);

    auto customSpanNode = CustomSpanNode::GetOrCreateSpanNode(V2::CUSTOM_SPAN_NODE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId());
    host->AddChild(customSpanNode);
    customSpanNode->SetParent(host);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. textFrameNode Measure will call InitSpanItem/CollectSpanNodes.
     * @tc.expect: expect childSpanNode MountToParagraph, add into TextPattern spans_.
     */
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    EXPECT_EQ(textPattern->spans_.size(), 6);
    auto gesture = childFrameNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(gesture->GetHitTestMode(), HitTestMode::HTMNONE);
}

/**
 * @tc.name: HandleDragEvent001
 * @tc.desc: test test_pattern.h InitDragEvent without any childSpan, then eventHub call
 *     OnDragStartNoChild/OnDragMove/OnDragEndNoChild.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, HandleDragEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern without childSpanNode, ViewStackProcessor Finish call
     *     InitDragEvent to set onDragStart/OnDragMove/OnDragEnd callback function.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step2. test text OnDragStart.
     * @tc.expect: expect OnDragStart result return GetSelectedText range [2, 6], status: Status::DRAGGING
     */
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(dragDropInfo.extraInfo, "3456");
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
    EXPECT_EQ(pattern->status_, Status::DRAGGING);

    /**
     * @tc.steps: step3. test OnDragMove.
     */
    eventHub->FireOnDragMove(event, "");
    EXPECT_EQ(pattern->showSelect_, false);
    /**
     * @tc.steps: step4. test text OnDragMoveEnd.
     * @tc.expect: expect onDragEnd will set status None, showSelect_ is true.
     */
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    EXPECT_EQ(pattern->showSelect_, true);
}

/**
 * @tc.name: HandleDragEvent002
 * @tc.desc: test test_pattern.h InitDragEvent with child spanNode, then eventHub call
 *     OnDragStart/OnDragMove/OnDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, HandleDragEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with child span node.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890abcdefghijklmnopqrstuvwxyz");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto childFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, 2, []() { return AceType::MakeRefPtr<TextPattern>(); });
    // need set, otherwise will crash.
    childFrameNode->SetLayoutProperty(AceType::MakeRefPtr<ImageLayoutProperty>());
    host->AddChild(childFrameNode);
    childFrameNode->SetParent(host);
    auto spanNode = CreateSpanNodeWithSetDefaultProperty(u"spannode");
    auto spanOnClickFunc = [](GestureEvent& info) {};
    spanNode->UpdateOnClickEvent(std::move(spanOnClickFunc));
    host->AddChild(spanNode);
    spanNode->SetParent(host);
    auto symbolSpanNode =
        SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId());
    host->AddChild(symbolSpanNode);
    symbolSpanNode->SetParent(host);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    host->AddChild(placeholderSpanNode);
    placeholderSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    pattern->textSelector_.Update(6, 15);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);

    /**
     * @tc.steps: step2. test textPattern OnDragStart.
     * @tc.expect: expect childSpanNode selected add into dragResultObjects.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(dragDropInfo.extraInfo, "");
    EXPECT_TRUE(!pattern->dragResultObjects_.empty());

    /**
     * @tc.steps: step3. test get text onDragMove.
     */
    eventHub->FireOnDragMove(dragEvent, "");
    EXPECT_EQ(pattern->showSelect_, false);

    /**
     * @tc.steps: step4. test textPattern onDragMove.
     * @expect: expect dragResultObjects_ empty OnDragEnd.
     */
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(dragEvent);
    EXPECT_TRUE(pattern->dragResultObjects_.empty());
}

/**
 * @tc.name: GetTextResultObject001
 * @tc.desc: test test_pattern.h GetTextResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, GetTextResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with two spanNodes,
     *     firstChild is SPAN_URL, secondChild is SPAN_PHONE
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_URL_U16);
    host->AddChild(spanNode);
    spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_PHONE_U16);
    host->AddChild(spanNode);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);
    EXPECT_TRUE(gesture->GetTextDraggable());
    /**
     * @tc.steps: step2. textSpanNode dragResultObject range as expected.
     * @tc.expect: expect spanNode will be selected by drag, textSelector [0, 15] exceed the first spannode len,
     *    SPAN_URL dragResult range [0, 13], the SPAN_PHONE dragResult range [0, 2]
     */
    pattern->textSelector_.Update(0, 15);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dragResultObjects_.back().valueString), SPAN_PHONE);
    EXPECT_EQ(pattern->dragResultObjects_.back().offsetInSpan[RichEditorSpanRange::RANGEEND], 2);

    /**
     * @tc.steps: step2. update text selector and call OnDragStart.
     * @tc.expect: expect spanNode will be selected, textSelector [0, 5] not exceed the first spannode len,
     *     thus dragResultObject is [0, 5] and dragResult is SPAN_URL.
     */
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(0, 5);
    dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dragResultObjects_.front().valueString), SPAN_URL);
    EXPECT_EQ(pattern->dragResultObjects_.front().offsetInSpan[RichEditorSpanRange::RANGEEND], 5);

    /**
     * @tc.steps: step3. update text selector and call OnDragStart.
     * @tc.expect: expect dragResultObject [SPAN_URL, SPAN_PHONE], SPAN_URL ranged [0, 13], .
     */
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(8, 16);
    dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dragResultObjects_.back().valueString), SPAN_PHONE);
    EXPECT_EQ(pattern->dragResultObjects_.front().offsetInSpan[RichEditorSpanRange::RANGEEND], SPAN_URL.size());
    for (auto obj : pattern->dragResultObjects_) {
        EXPECT_EQ(obj.type, SelectSpanType::TYPESPAN);
    }
}

/**
 * @tc.name: GetSymbolSpanResultObject001
 * @tc.desc: test test_pattern.h GetSymbolSpanResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, GetSymbolSpanResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with child symbolSpanNodes.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto stack = ViewStackProcessor::GetInstance();
    auto host = AceType::Claim<FrameNode>(stack->GetMainFrameNode());
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    std::vector<uint32_t> unicodes = { 0x4F60, 0x597D, 0xFF0C, 0x4E16, 0x754C, 0xFF01 };
    for (auto code : unicodes) {
        auto symbolSpanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, stack->ClaimNodeId());
        symbolSpanNode->UpdateContent(code);
        host->AddChild(symbolSpanNode);
        symbolSpanNode->SetParent(host);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    // measure will call pattern InitDragEvent.
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);

    /**
     * @tc.steps: step2. symbol spanNode drag select range as expected.
     * @tc.expect: symbol spanNode len is 2, thus last dragResultObject is partial selected, range [0, 1]
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(0, 5);
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_TRUE(!pattern->dragResultObjects_.empty());
    // "20320" means: unicode string
    EXPECT_EQ(StringUtils::Str16ToStr8(pattern->dragResultObjects_.front().valueString), "20320");
    EXPECT_EQ(pattern->dragResultObjects_.back().offsetInSpan[RichEditorSpanRange::RANGEEND], 1);
    for (auto obj : pattern->dragResultObjects_) {
        EXPECT_EQ(obj.type, SelectSpanType::TYPESYMBOLSPAN);
    }

    /**
     * @tc.steps: step3. text selectstr OnDragStart as expected.
     * @tc.expect: expect dragResultObjects_ not empty.
     */
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(8, 12);
    dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_TRUE(!pattern->dragResultObjects_.empty());
}

/**
 * @tc.name: GetImageResultObject001
 * @tc.desc: test test_pattern.h GetImageResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, GetImageResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with three child ImageSpanNodes.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));

    MarginPropertyF margin { .left = 40.f, .right = 40.f, .top = 80.f, .bottom = 80.f };
    ImageSpanNodeProperty firstProperty { .imageSrc = std::make_optional("image"),
        .margin = std::make_optional(margin),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER) };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    host->AddChild(imageSpanNode);

    ImageSpanNodeProperty secondProperty { .pixelMap = std::make_optional(PixelMap::CreatePixelMap(nullptr)),
        .margin = std::make_optional(margin),
        .imageFit = std::make_optional(ImageFit::FILL),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER) };
    imageSpanNode = CreateImageSpanNode(secondProperty);
    host->AddChild(imageSpanNode);

    ImageSpanNodeProperty thirdProperty { .margin = std::make_optional(margin),
        .imageFit = std::make_optional(ImageFit::FILL),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER) };
    imageSpanNode = CreateImageSpanNode(thirdProperty);
    host->AddChild(imageSpanNode);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);

    /**
     * @tc.steps: step2. text selectstr OnDragStart as expected.
     * @tc.expect expect non-null imagesrc & pixelMap in dragResultObjects, properties as expected,
     *     dragResultObjects_ size is 2.
     */
    pattern->textSelector_.Update(0, 20);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(pattern->dragResultObjects_.size(), 2); // 2 means result list size.
    EXPECT_EQ(
        pattern->dragResultObjects_.front().imageStyle.verticalAlign, static_cast<int32_t>(VerticalAlign::CENTER));
    EXPECT_EQ(pattern->dragResultObjects_.front().imageStyle.objectFit, static_cast<int32_t>(ImageFit::FILL));
    for (auto obj : pattern->dragResultObjects_) {
        EXPECT_EQ(obj.type, SelectSpanType::TYPEIMAGE);
    }
}

/**
 * @tc.name: SetTextDetectTypes001
 * @tc.desc: test test_pattern.h SetTextDetectTypes.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, SetTextDetectTypes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with child span node.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    TextDetectConfig textDetectConfig;
    textModelNG.SetTextDetectConfig(textDetectConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(pattern->dataDetectorAdapter_->aiDetectInitialized_, false);
    pattern->dataDetectorAdapter_->InitTextDetect(0, "orange");
}


/**
 * @tc.name: SetTextDetectConfig001
 * @tc.desc: test test_pattern.h SetTextDetectTypes.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, SetTextDetectConfig001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create frameNode and pattern with child span node.
    */
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    TextDetectConfig textDetectConfig;
    textDetectConfig.enablePreviewMenu = true;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();

    /**
     * @tc.steps: step2. call InitTextDetect.
     */
    pattern->SetTextDetectConfig(textDetectConfig);
    EXPECT_EQ(pattern->dataDetectorAdapter_->enablePreviewMenu_, true);
}

/**
 * @tc.name: SetTextDetectTypes002
 * @tc.desc: test test_pattern.h SetTextDetectTypes.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, SetTextDetectTypes002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create frameNode and pattern with child span node.
    */
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    TextDetectConfig textDetectConfig;
    textModelNG.SetTextDetectConfig(textDetectConfig);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    /**
     * @tc.steps: step2. call InitTextDetect.
     */
    pattern->dataDetectorAdapter_->InitTextDetect(0, "2023年12月30日 5点半 十二月三十日");
    EXPECT_EQ(pattern->dataDetectorAdapter_->aiDetectInitialized_, false);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    Shadow textShadow;
    textShadow.SetBlurRadius(3.f); // 3.f means BlurRadius.
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textModelNG.SetTextShadow({ textShadow });
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->GetRenderContext()->UpdateClipEdge(false);
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    frameNode->Layout();
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(200.f));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(80.f));
    pattern->pManager_->Reset();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    /**
     * @tc.steps: step2. test CreateNodePaintMethod.
     * @tc.expect: expect overlayModifier BoundsRect width std::max(frameWith, paragraph->GetLongestLine),
     *     GestureHub ResponseRegion list not empty.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    EXPECT_TRUE(gestureHub->GetResponseRegion().empty());
    pattern->CreateNodePaintMethod();
    EXPECT_EQ(pattern->overlayMod_->GetBoundsRect().Width(), 240.f);
    EXPECT_TRUE(!gestureHub->GetResponseRegion().empty());
    pattern->pManager_->Reset();
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, CreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(10); // 10 means min platformVersion.
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    frameNode->Layout();
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(200.f));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(80.f));
    pattern->pManager_->Reset();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 1 });

    /**
     * @tc.steps: step2. test CreateNodePaintMethod.
     * @tc.expect: RenderContext ClipEdge is true, expect gestureHub ResponseRegion equal to content size.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    pattern->CreateNodePaintMethod();
    EXPECT_TRUE(!gestureHub->GetResponseRegion().empty());

    auto geometryNode = frameNode->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    auto responseRegion = gestureHub->GetResponseRegion().front();

    EXPECT_EQ(responseRegion.GetWidth().Value(), frameSize.Width());
    EXPECT_EQ(responseRegion.GetHeight().Value(), frameSize.Height());

    /**
     * @tc.steps: step3. test CreateNodePaintMethod.
     * @tc.expect: RenderContext ClipEdge is false, expect gestureHub ResponseRegion equal to framesize.
     */
    auto renderContext = frameNode->GetRenderContext();
    renderContext->UpdateClipEdge(true);
    pattern->CreateNodePaintMethod();
    EXPECT_TRUE(!gestureHub->GetResponseRegion().empty());

    frameSize = geometryNode->GetFrameSize();
    responseRegion = gestureHub->GetResponseRegion().front();

    EXPECT_EQ(responseRegion.GetWidth().Value(), frameSize.Width());
    EXPECT_EQ(responseRegion.GetHeight().Value(), frameSize.Height());
    EXPECT_EQ(responseRegion.GetWidth().Value(), 240.0);
    EXPECT_EQ(responseRegion.GetHeight().Value(), 60.0);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: SurfaceChangeEvent001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, SurfaceChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    auto pattern = frameNode->GetPattern<TextPattern>();

    /**
     * @tc.steps: step2. expect.
     */
    EXPECT_TRUE(pattern->surfaceChangedCallbackId_.has_value());
    EXPECT_TRUE(pattern->surfacePositionChangedCallbackId_.has_value());
    MockPipelineContext::GetCurrent()->OnSurfacePositionChanged(10, 10);
}

/**
 * @tc.name: TextModelNgProperty001
 * @tc.desc: test text_model_ng.h static functions.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextModelNgProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = TextModelNG::CreateFrameNode(ViewStackProcessor::GetInstance()->ClaimNodeId(),
        StringUtils::Str8ToStr16(V2::TEXT_ETS_TAG));
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    auto node = frameNode.rawPtr_;
    std::u16string str = u"Hello, World!";
    Font font;
    TextModelNG::SetFont(node, font);
    TextModelNG::InitText(node, str);
    TextModelNG::SetFontWeight(node, Ace::FontWeight::BOLDER);
    TextModelNG::SetItalicFontStyle(node, Ace::FontStyle::ITALIC);
    TextModelNG::SetTextAlign(node, Ace::TextAlign::CENTER);
    TextModelNG::SetTextColor(node, Color::RED);
    TextModelNG::SetFontSize(node, FONT_SIZE_VALUE);
    TextModelNG::SetLineHeight(node, ADAPT_LINE_HEIGHT_VALUE);
    TextModelNG::SetTextOverflow(node, TextOverflow::ELLIPSIS);
    TextModelNG::SetTextDecoration(node, TextDecoration::UNDERLINE);
    TextModelNG::SetTextDecorationColor(node, Color::BLACK);
    TextModelNG::SetTextDecorationStyle(node, TextDecorationStyle::SOLID);
    TextModelNG::SetTextCase(node, TextCase::UPPERCASE);
    TextModelNG::SetMaxLines(node, 10); // 10 means maxlines.
    TextModelNG::SetMinLines(node, 2); // 2 means minlines.
    TextModelNG::SetLineSpacing(node, ADAPT_LINE_SPACING_VALUE, true);

    /**
     * @tc.steps: step2. test property.
     * @tc.expect： expect property as expect.
     */
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), Ace::FontWeight::BOLDER);
    EXPECT_EQ(layoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::ITALIC);
    EXPECT_EQ(layoutProperty->GetTextAlign().value(), Ace::TextAlign::CENTER);
    EXPECT_EQ(layoutProperty->GetTextColor().value(), Color::RED);
    EXPECT_EQ(layoutProperty->GetFontSize().value(), FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetLineHeight().value(), ADAPT_LINE_HEIGHT_VALUE);
    EXPECT_EQ(layoutProperty->GetTextOverflow().value(), TextOverflow::ELLIPSIS);
    EXPECT_EQ(layoutProperty->GetTextDecorationFirst(), TextDecoration::UNDERLINE);
    EXPECT_EQ(layoutProperty->GetTextDecorationColor().value(), Color::BLACK);
    EXPECT_EQ(layoutProperty->GetTextDecorationStyle().value(), TextDecorationStyle::SOLID);
    EXPECT_EQ(layoutProperty->GetTextCase().value(), TextCase::UPPERCASE);
    EXPECT_EQ(layoutProperty->GetMaxLines().value(), 10);
    EXPECT_EQ(layoutProperty->GetMinLines().value(), 2);
    EXPECT_EQ(layoutProperty->GetLineSpacing().value(), ADAPT_LINE_SPACING_VALUE);
    EXPECT_EQ(layoutProperty->GetIsOnlyBetweenLines().value(), true);
}

/**
 * @tc.name: TextModelNgProperty002
 * @tc.desc: test text_model_ng.h static functions.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextModelNgProperty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode.
     */
    auto frameNode = TextModelNG::CreateFrameNode(ViewStackProcessor::GetInstance()->ClaimNodeId(),
        StringUtils::Str8ToStr16(V2::TEXT_ETS_TAG));
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    auto node = frameNode.rawPtr_;
    TextModelNG::SetAdaptMinFontSize(node, ADAPT_MIN_FONT_SIZE_VALUE);
    TextModelNG::SetAdaptMaxFontSize(node, ADAPT_MAX_FONT_SIZE_VALUE);
    TextModelNG::SetFontFamily(node, FONT_FAMILY_VALUE);
    TextModelNG::SetCopyOption(node, CopyOptions::Distributed);
    std::vector<Shadow> textShadows;
    TextModelNG::SetTextShadow(node, textShadows);
    TextModelNG::SetHeightAdaptivePolicy(node, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    TextModelNG::SetTextIndent(node, TEXT_INDENT);
    TextModelNG::SetBaselineOffset(node, BASELINE_OFFSET_VALUE);
    TextModelNG::SetLetterSpacing(node, LETTER_SPACING);
    Font font;
    font.fontSize = FONT_SIZE_VALUE;
    font.fontWeight = FontWeight::BOLD;
    font.fontFamilies = FONT_FAMILY_VALUE;
    font.fontStyle = ITALIC_FONT_STYLE_VALUE;
    TextModelNG::SetFont(node, font);
    TextModelNG::SetWordBreak(node, WordBreak::BREAK_ALL);
    TextModelNG::SetLineBreakStrategy(node, LineBreakStrategy::BALANCED);

    /**
     * @tc.steps: step2. test property.
     * @tc.expect： expect property as expect.
     */
    EXPECT_EQ(layoutProperty->GetAdaptMinFontSize().value(), ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetAdaptMaxFontSize().value(), ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetFontFamily().value(), FONT_FAMILY_VALUE);
    EXPECT_EQ(layoutProperty->GetCopyOption().value(), CopyOptions::Distributed);
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicy().value(), TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    EXPECT_EQ(layoutProperty->GetTextIndent().value(), TEXT_INDENT);
    EXPECT_EQ(layoutProperty->GetBaselineOffset().value(), BASELINE_OFFSET_VALUE);
    EXPECT_EQ(layoutProperty->GetLetterSpacing().value(), LETTER_SPACING);
    EXPECT_EQ(layoutProperty->GetFontSize().value(), FONT_SIZE_VALUE);
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    EXPECT_EQ(layoutProperty->GetFontFamily().value(), FONT_FAMILY_VALUE);
    EXPECT_EQ(layoutProperty->GetItalicFontStyle().value(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(layoutProperty->GetWordBreak().value(), WordBreak::BREAK_ALL);
    EXPECT_EQ(layoutProperty->GetLineBreakStrategy().value(), LineBreakStrategy::BALANCED);
}

/**
 * @tc.name: DumpInfoTest001
 * @tc.desc: test text_pattern.h DumpInfo/DumpAdvanceInfo function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, DumpInfoTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    auto pattern = frameNode->GetPattern<TextPattern>();

    /**
     * @tc.steps: step2. expect pattern DumpInfo/DumpAdvanceInfo function run normally.
     */
    pattern->DumpInfo();
    SystemProperties::debugEnabled_ = true;
    pattern->DumpAdvanceInfo();
    EXPECT_TRUE(true);
}

/**
 * @tc.name: TextLayoutAlgorithmLayout001
 * @tc.desc: test text_pattern.h TextLayoutAlgorithm::Layout function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextLayoutAlgorithmLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with imageSpanNode&PlaceholderSpanNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto host = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = host->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> selectedRects { RectF(0, 0, 20, 20), RectF(30, 30, 20, 20), RectF(60, 60, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForPlaceholders(_)).WillRepeatedly(SetArgReferee<0>(selectedRects));
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    host->AddChild(placeholderSpanNode);
    placeholderSpanNode->SetParent(host);

    MarginPropertyF margin { .left = 40.f, .right = 40.f, .top = 80.f, .bottom = 80.f };
    ImageSpanNodeProperty firstProperty { .imageSrc = std::make_optional("image"),
        .margin = std::make_optional(margin),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER) };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. test textLayoutAlgorithm with imageSpanNode & PlaceholderSpanNode
     *     layout function run normally.
     * @tc.expect: expect layoutAlgorithm_ spanItemChildSize number 2.
     */
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    frameNode->Layout();

    auto layoutWrapper = frameNode->GetLayoutAlgorithm();
    ASSERT_NE(layoutWrapper, nullptr);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(textLayoutAlgorithm, nullptr);
    EXPECT_EQ(textLayoutAlgorithm->spans_.front().size(), 2); // 2 means:two child spannode
    pattern->pManager_->Reset();
}

/**
 * @tc.name: CreateParagphTest001
 * @tc.desc: test text_layout_algorithm.h CreateParagraph function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, CreateParagphTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateSymbolSourceInfo(SymbolSourceInfo(0x4F60));
    /**
     * @tc.steps: step2. test CreateParagraph.
     * @tc.expect: expect SYMBOL_ETS_TAG CreateParagraph run Normally.
     */
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    frameNode->Layout();
    EXPECT_TRUE(true);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: CreateParagphDragTest001
 * @tc.desc: test text_layout_algorithm.h CreateParagraphDrag function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, CreateParagphDragTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetCopyOption(CopyOptions::Local);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->Measure(LayoutConstraintF());
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step2. test text OnDragStart.
     * @tc.expect: expect createParagraphDrag run normally.
     */
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(pattern->status_, Status::DRAGGING);
    frameNode->Measure(LayoutConstraintF());
    EXPECT_EQ(pattern->GetDragContents().size(), 3);
}

/**
 * @tc.name: AdaptMaxTextSizeTest001
 * @tc.desc: test text_layout_algorithm.h AdaptMaxTextSize function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, AdaptMaxTextSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textModelNG.SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE_S);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = host->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    EXPECT_CALL(*paragraph, DidExceedMaxLines).WillRepeatedly(Return(false));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    frameNode->Layout();

    /**
     * @tc.steps: step2. test textLayoutAlgorithm MeasureContent function.
     * @tc.expect: expect textLayoutAlgorithm::AdaptMaxTextSize run normally.
     */
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    frameNode->Measure(layoutConstraintF);
    frameNode->Layout();
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_EQ(geometryNode->GetFrameRect().Width(), 240.f);
    EXPECT_EQ(geometryNode->GetFrameRect().Height(), 60.f);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: SetImageSpanTextStyleTest001
 * @tc.desc: test text_layout_algorithm.h SetImageSpanTextStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, SetImageSpanTextStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with ImageSpanNodes.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = host->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    std::vector<RectF> rects { RectF(0, 0, 20, 20), RectF(20, 20, 20, 20), RectF(40, 40, 20, 20),
        RectF(60, 60, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForPlaceholders(_)).WillRepeatedly(SetArgReferee<0>(rects));
    std::vector<RectF> selctRects { RectF(0, 0, 20, 20), RectF(0, 0, 30, 30) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    MarginPropertyF margin { .left = 40.f, .right = 40.f, .top = 80.f, .bottom = 80.f };
    std::vector<std::u16string> placeHolderStrings { u"please", u"input", u"text" };
    for (auto str : placeHolderStrings) {
        auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
        placeholderSpanNode->GetSpanItem()->content = str;
        host->AddChild(placeholderSpanNode);
        ImageSpanNodeProperty firstProperty { .imageSrc = std::make_optional("image"),
            .margin = std::make_optional(margin) };
        auto imageSpanNode = CreateImageSpanNode(firstProperty);
        imageSpanNode->GetSpanItem()->content = str;
        host->AddChild(imageSpanNode);
    }
    auto spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_URL_U16);
    host->AddChild(spanNode);
    spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_PHONE_U16);
    host->AddChild(spanNode);

    /**
     * @tc.steps: step2. test textLayoutAlgorithm SetImageSpanTextStyle function.
     * @tc.expect: expect textLayoutAlgorithm::SetImageSpanTextStyle run normally.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF { .selfIdealSize = OptionalSizeF(240.f, 60.f) };
    frameNode->Measure(layoutConstraintF);
    auto geometryNode = frameNode->GetGeometryNode();
    EXPECT_EQ(geometryNode->GetFrameRect().Width(), 240.f);
    EXPECT_EQ(geometryNode->GetFrameRect().Height(), 60.f);
    pattern->pManager_->Reset();
}

/**
 * @tc.name: UpdateFontFeature
 * @tc.desc: test fontFeature.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, UpdateFontFeature001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    textModelNG.SetFontFeature(FONT_FEATURE_VALUE_1);
    EXPECT_EQ(textLayoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_1);
    textLayoutProperty->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    TextModelNG::SetFontFeature(frameNode, FONT_FEATURE_VALUE_1);
    EXPECT_EQ(textLayoutProperty->GetFontFeature(), FONT_FEATURE_VALUE_1);
}

/**
 * @tc.name: UpdateMarqueeOptions001
 * @tc.desc: test MarqueeOptions.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, UpdateMarqueeOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. test property.
     * @tc.expect： expect property as expect.
     */
    TextMarqueeOptions options;
    options.UpdateTextMarqueeStart(true);
    options.UpdateTextMarqueeStep(3);
    options.UpdateTextMarqueeLoop(3);
    options.UpdateTextMarqueeDirection(MarqueeDirection::RIGHT);
    options.UpdateTextMarqueeDelay(3);
    options.UpdateTextMarqueeFadeout(false);
    options.UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::ON_FOCUS);
    textModelNG.SetMarqueeOptions(options);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStart().value(), true);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStep().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeLoop().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDirection().value(), MarqueeDirection::RIGHT);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeDelay().value(), 3);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeFadeout().value(), false);
    EXPECT_EQ(textLayoutProperty->GetTextMarqueeStartPolicy().value(), MarqueeStartPolicy::ON_FOCUS);
}

/**
 * @tc.name: TextMarqueeEvents001
 * @tc.desc: Test initializing focus and hover events for marquee.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMarqueeEvents001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set the TextOverflow value to Marquee.
     */
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    textLayoutProperty->UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::ON_FOCUS);

    /**
     * @tc.steps: step3. call OnModifyDone function.
     * @tc.expected: The focus and hover events are initialized.
     */
    textPattern->OnModifyDone();
    EXPECT_EQ(textPattern->focusInitialized_, true);
    EXPECT_EQ(textPattern->hoverInitialized_, true);
}

/**
 * @tc.name: TextMarqueeEvents002
 * @tc.desc: Test initializing focus and hover events for marquee.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMarqueeEvents002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call OnModifyDone function.
     * @tc.expected: The focus and hover events are initialized.
     */
    textPattern->OnModifyDone();
    EXPECT_EQ(textPattern->focusInitialized_, false);
    EXPECT_EQ(textPattern->hoverInitialized_, false);
}

/**
 * @tc.name: PrepareAIMenuOptions
 * @tc.desc: test test_pattern.h PrepareAIMenuOptions function with valid textSelector
 *           check single ai entity in selection range
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, PrepareAIMenuOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and text textPattern
     */
    auto [frameNode, textPattern] = Init();
    textPattern->textSelector_.Update(0, 22);

    /**
     * @tc.steps: step2. prepare spanItem1
     */
    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->content = std::get<std::u16string>(U16_TEXT_FOR_AI_INFO.content);
    spanItem1->position = spanItem1->content.length();
    textPattern->spans_.emplace_back(spanItem1);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    textPattern->pManager_->AddParagraph({ .paragraph = mockParagraph, .start = 0, .end = 100 });

    textPattern->SetTextDetectEnable(true);
    textPattern->copyOption_ = CopyOptions::Local;

    auto aiSpan1 = U16_TEXT_FOR_AI_INFO.aiSpans[0];
    auto aiSpan2 = U16_TEXT_FOR_AI_INFO.aiSpans[1];
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[aiSpan1.start] = aiSpan1;
    aiSpanMap[aiSpan2.start] = aiSpan2;
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    textPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;

    /**
     * @tc.steps: step3. create GestureEvent and call PrepareAIMenuOptions function.
     * @tc.expected: aiMenuOptions is been setted true.
     */
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    textPattern->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_EQ(aiMenuOptions.size(), 0);
    textPattern->pManager_->Reset();
}


/**
 * @tc.name: PrepareAIMenuOptions
 * @tc.desc: test test_pattern.h PrepareAIMenuOptions function with valid textSelector
 *           check multi ai entity in selection range
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, PrepareAIMenuOptions002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and text textPattern
     */
    auto [frameNode, textPattern] = Init();
    textPattern->textSelector_.Update(0, 40);

    /**
     * @tc.steps: step2. prepare spanItem with at least 2 ai entity
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = std::get<std::u16string>(U16_TEXT_FOR_AI_INFO_2.content);
    spanItem->position = spanItem->content.length();
    textPattern->spans_.emplace_back(spanItem);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> selectedRects { RectF(0, 0, 20, 20), RectF(30, 30, 20, 20), RectF(60, 60, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForPlaceholders(_)).WillRepeatedly(SetArgReferee<0>(selectedRects));
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    textPattern->SetTextDetectEnable(true);
    textPattern->copyOption_ = CopyOptions::Local;

    auto aiSpan1 = U16_TEXT_FOR_AI_INFO_2.aiSpans[0];
    auto aiSpan2 = U16_TEXT_FOR_AI_INFO_2.aiSpans[1];
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[aiSpan1.start] = aiSpan1;
    aiSpanMap[aiSpan2.start] = aiSpan2;
    ASSERT_NE(textPattern->GetDataDetectorAdapter(), nullptr);
    textPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;

    /**
     * @tc.steps: step3. create GestureEvent and call PrepareAIMenuOptions function.
     * @tc.expected: aiMenuOptions is been setted true.
     */
    std::unordered_map<TextDataDetectType, AISpan> aiMenuOptions;
    auto ret = textPattern->PrepareAIMenuOptions(aiMenuOptions);
    EXPECT_EQ(aiMenuOptions.size(), 0);
    EXPECT_EQ(ret, false);
    textPattern->pManager_->Reset();
}

/**
 * @tc.name: TextModelGetShaderStyleInJson001
 * @tc.desc: Test if GetShaderStyleInJson is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextModelGetShaderStyleInJson001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set type == RADIAL.
     */
    Gradient gradientLinear = Gradient();
    gradientLinear.type_ = GradientType::LINEAR;
    LinearGradient linearGradient;
    linearGradient.angle = std::make_optional(2.00_vp);
    gradientLinear.SetLinearGradient(linearGradient);
    textLayoutProperty->UpdateGradientShaderStyle(gradientLinear);
    std::string radialJson = pattern->GetShaderStyleInJson()->ToString();
    EXPECT_EQ(radialJson,
        "{\"angle\":\"2.00vp\",\"direction\":\"GradientDirection.None\",\"colors\":[],\"repeating\":\"false\"}");

    /**
     * @tc.steps: step3. Set type == RADIAL.
     */
    Gradient gradientRadial = Gradient();
    gradientRadial.type_ = GradientType::RADIAL;
    RadialGradient radialGradient;
    radialGradient.radialCenterX = std::make_optional(25.0_vp);
    radialGradient.radialCenterY = std::make_optional(25.0_vp);
    gradientRadial.SetRadialGradient(radialGradient);
    textLayoutProperty->UpdateGradientShaderStyle(gradientRadial);
    std::string linearJson = pattern->GetShaderStyleInJson()->ToString();
    EXPECT_EQ(linearJson, "{\"center\":[\"25.00vp\",\"25.00vp\"],\"colors\":[],\"repeating\":\"false\"}");

    /**
     * @tc.steps: step4. Set ColorShaderStyle.
     */
    Color color = Color::RED;
    textLayoutProperty->ResetGradientShaderStyle();
    textLayoutProperty->UpdateColorShaderStyle(color);
    std::string colorJson = pattern->GetShaderStyleInJson()->ToString();
    EXPECT_EQ(colorJson, "{\"color\":\"#FFFF0000\"}");

    /**
     * @tc.steps: step5. Set type == null.
     */
    Gradient gradient = Gradient();
    textLayoutProperty->UpdateGradientShaderStyle(gradient);
    std::string json = pattern->GetShaderStyleInJson()->ToString();
    EXPECT_EQ(json, "{}");
}

/**
 * @tc.name: TextModelNGMinLines001
 * @tc.desc: Test TextModelNGMinLines
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMinLines001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMinLines(5);
    EXPECT_EQ(textLayoutProperty->GetMinLines().value(), 5);
    textLayoutProperty->UpdateMinLines(9);
    EXPECT_EQ(textLayoutProperty->GetMinLines().value(), 9);
    textModelNG.ResetMinLines();
    EXPECT_EQ(textLayoutProperty->HasMinLines(), false);
}

/**
 * @tc.name: TextModelNGMinLines002
 * @tc.desc: Test TextModelNGMinLines
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMinLines002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMinLines(frameNode, 5);
    EXPECT_EQ(textModelNG.GetMinLines(frameNode), 5U);
    textLayoutProperty->UpdateMinLines(9);
    EXPECT_EQ(textLayoutProperty->GetMinLines().value(), 9);
    textModelNG.ResetMinLines(frameNode);
    EXPECT_EQ(textLayoutProperty->HasMinLines(), false);
}

/**
 * @tc.name: TextModelNGMinLines003
 * @tc.desc: Test TextModelNGMinLines
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMinLines003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMinLines(frameNode, 1);
    EXPECT_EQ(textModelNG.GetMinLines(frameNode), 1U);
    textLayoutProperty->UpdateMinLines(9);
    EXPECT_EQ(textLayoutProperty->GetMinLines().value(), 9);
    textModelNG.ResetMinLines(frameNode);
    EXPECT_EQ(textLayoutProperty->HasMinLines(), false);
}

/**
 * @tc.name: TextModelNGMinLineHeight001
 * @tc.desc: Test TextModelNGMinLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMinLineHeight001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMinimumLineHeight(Dimension(5));
    EXPECT_EQ(textLayoutProperty->GetMinimumLineHeight().value(), Dimension(5));
    textLayoutProperty->UpdateMinimumLineHeight(Dimension(9));
    EXPECT_EQ(textLayoutProperty->GetMinimumLineHeight().value(), Dimension(9));
    textModelNG.ResetMinimumLineHeight();
    EXPECT_EQ(textLayoutProperty->HasMinimumLineHeight(), false);
}

/**
 * @tc.name: TextModelNGMinLineHeight002
 * @tc.desc: Test TextModelNGMinLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMinLineHeight002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMinimumLineHeight(frameNode, Dimension(5));
    EXPECT_EQ(textModelNG.GetTextMinimumLineHeight(frameNode), 5.0);
    textLayoutProperty->UpdateMinimumLineHeight(Dimension(9));
    EXPECT_EQ(textLayoutProperty->GetMinimumLineHeight().value(), Dimension(9));
    textModelNG.ResetMinimumLineHeight(frameNode);
    EXPECT_EQ(textLayoutProperty->HasMinimumLineHeight(), false);
}

/**
 * @tc.name: TextModelNGMaxLineHeight001
 * @tc.desc: Test TextModelNGMaxLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMaxLineHeight001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMaximumLineHeight(Dimension(5));
    EXPECT_EQ(textLayoutProperty->GetMaximumLineHeight().value(), Dimension(5));
    textLayoutProperty->UpdateMaximumLineHeight(Dimension(9));
    EXPECT_EQ(textLayoutProperty->GetMaximumLineHeight().value(), Dimension(9));
    textModelNG.ResetMaximumLineHeight();
    EXPECT_EQ(textLayoutProperty->HasMaximumLineHeight(), false);
}

/**
 * @tc.name: TextModelNGMaxLineHeight002
 * @tc.desc: Test TextModelNGMaxLineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextMaxLineHeight002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetMaximumLineHeight(frameNode, Dimension(5));
    EXPECT_EQ(textModelNG.GetTextMaximumLineHeight(frameNode), 5.0);
    textLayoutProperty->UpdateMaximumLineHeight(Dimension(9));
    EXPECT_EQ(textLayoutProperty->GetMaximumLineHeight().value(), Dimension(9));
    textModelNG.ResetMaximumLineHeight(frameNode);
    EXPECT_EQ(textLayoutProperty->HasMaximumLineHeight(), false);
}

/**
 * @tc.name: TextModelNGLineHeightMultiply001
 * @tc.desc: Test TextModelNGLineHeightMultiply
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextLineHeightMultiply001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetLineHeightMultiply(5.0);
    EXPECT_EQ(textLayoutProperty->GetLineHeightMultiply().value(), 5.0);
    textLayoutProperty->UpdateLineHeightMultiply(9.0);
    EXPECT_EQ(textLayoutProperty->GetLineHeightMultiply().value(), 9.0);
    textModelNG.ResetLineHeightMultiply();
    EXPECT_EQ(textLayoutProperty->HasLineHeightMultiply(), false);
}

/**
 * @tc.name: TextModelNGLineHeightMultiply002
 * @tc.desc: Test TextModelNGLineHeightMultiply
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextLineHeightMultiply002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetLineHeightMultiply(frameNode, 5.0);
    EXPECT_EQ(textModelNG.GetTextLineHeightMultiply(frameNode), 5.0);
    textLayoutProperty->UpdateLineHeightMultiply(9.0);
    EXPECT_EQ(textLayoutProperty->GetLineHeightMultiply().value(), 9.0);
    textModelNG.ResetLineHeightMultiply(frameNode);
    EXPECT_EQ(textLayoutProperty->HasLineHeightMultiply(), false);
}

/**
 * @tc.name: TextModelNGLineHeightMultiply003
 * @tc.desc: Test TextModelNGLineHeightMultiply
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextLineHeightMultiply003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetLineHeightMultiply(frameNode, 5.0);
    textModelNG.SetLineHeight(frameNode, Dimension(-5));
    EXPECT_EQ(textModelNG.GetTextLineHeightMultiply(frameNode), 5.0);
    textLayoutProperty->UpdateLineHeightMultiply(9.0);
    EXPECT_EQ(textLayoutProperty->GetLineHeightMultiply().value(), 9.0);
    textModelNG.ResetLineHeightMultiply(frameNode);
    EXPECT_EQ(textLayoutProperty->HasLineHeightMultiply(), false);
}

/**
 * @tc.name: TextCompressLeadingPunctuation001
 * @tc.desc: Test TextCompressLeadingPunctuation
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextCompressLeadingPunctuation001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetCompressLeadingPunctuation(true);
    EXPECT_EQ(textLayoutProperty->GetCompressLeadingPunctuation().value(), true);
    textLayoutProperty->UpdateCompressLeadingPunctuation(false);
    EXPECT_EQ(textLayoutProperty->GetCompressLeadingPunctuation().value(), false);
}

/**
 * @tc.name: TextCompressLeadingPunctuation002
 * @tc.desc: Test TextCompressLeadingPunctuation
 * @tc.type: FUNC
 */
HWTEST_F(TextTestThreeNg, TextCompressLeadingPunctuation002, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textModelNG.SetCompressLeadingPunctuation(frameNode, true);
    EXPECT_EQ(textLayoutProperty->GetCompressLeadingPunctuation().value(), true);
    textLayoutProperty->UpdateCompressLeadingPunctuation(false);
    EXPECT_EQ(textLayoutProperty->GetCompressLeadingPunctuation().value(), false);
}
} // namespace OHOS::Ace::NG
