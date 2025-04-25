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
#include "image_base.h"

#include "base/image/image_defines.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImagePatternTestNg : public ImageBases {};

/**
 * @tc.name: TriggerVisibleAreaChangeForChild001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TriggerVisibleAreaChangeForChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    bool flag = false;
    auto callback = [&flag](bool visible, double opacity) { flag = true; };
    for (auto& child : frameNode->GetChildren()) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        EXPECT_NE(childNode, nullptr);
        childNode->GetOrCreateEventHub<EventHub>()->GetVisibleAreaCallback(true).callback = callback;
    }
    auto testNode = TestNode::CreateTestNode(ElementRegister::GetInstance()->MakeUniqueId());
    frameNode->AddChild(testNode);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
    EXPECT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    frameNode->GetLayoutProperty()->UpdateAlignment(Alignment::TOP_LEFT);
    frameNode->AddChild(imageNode);
    flag = false;
    imagePattern->TriggerVisibleAreaChangeForChild(frameNode, true, 1.0f);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: SetObscured001
 * @tc.desc: Test ResetImage and SetObscured for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetObscured001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto childNode = frameNode->GetFirstChild();
    EXPECT_NE(childNode, nullptr);
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    imageFrameNode->renderContext_.Reset();
    imagePattern->SetObscured();
    EXPECT_FALSE(frameNode->GetRenderContext()->HasObscured());
    imagePattern->altImage_ = AceType::MakeRefPtr<NG::MockCanvasImage>();
    imagePattern->ResetImage();
    ASSERT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: SetColorFilter001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetColorFilter001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    RefPtr<ImageRenderProperty> layoutProperty1 = imageNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(layoutProperty1, nullptr);

    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(ALT_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, { .selected = true });
    ASSERT_NE(imagePaintMethod.canvasImage_, nullptr);

    auto& config = imagePaintMethod.canvasImage_->paintConfig_;
    auto drawingColorFilter = config->colorFilter_.colorFilterDrawing_;
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetDrawingColorFilter(drawingColorFilter);
    /**
     * @tc.steps: step2. call SetColorFilter.
     * @tc.expected: DrawingColorFilter of imageNode is changed.
     */
    imagePattern->SetColorFilter(imageNode);
    EXPECT_TRUE(layoutProperty1->HasDrawingColorFilter());
}
/**
 * @tc.name: OnSensitiveStyleChange001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnSensitiveStyleChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    frameNode->isPrivacySensitive_ = true;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto renderContext = frameNode->renderContext_;
    EXPECT_NE(renderContext, nullptr);
    const auto& groupProperty = renderContext->GetOrCreateBackground();
    groupProperty->propBlurRadius = std::make_optional<Dimension>(1.0f);
    groupProperty->propBlurStyleOption = std::make_optional<BlurStyleOption>();
    /**
     * @tc.steps: step2. call OnSensitiveStyleChange.
     * @tc.expected: renderContext changed.
     */
    imagePattern->OnSensitiveStyleChange(true);
    EXPECT_TRUE(imagePattern->isSensitive_);
}

/**
 * @tc.name: SetDuration001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call SetDuration.
     * @tc.expected: duration_ is changed.
     */
    imagePattern->durationTotal_ = 1;
    imagePattern->animator_->duration_ = imagePattern->durationTotal_ + 1;
    imagePattern->animator_->status_ = Animator::Status::RUNNING;
    imagePattern->SetDuration(1.0f);
    imagePattern->animator_->NotifyRepeatListener();
    EXPECT_EQ(imagePattern->animator_->duration_, 1);
}
/**
 * @tc.name: FindCacheImageNode001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, FindCacheImageNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call FindCacheImageNode.
     * @tc.expected:.
     */
    auto pixeMap = CreatePixelMap(IMAGE_SRC_URL);
    auto ret = imagePattern->FindCacheImageNode(pixeMap);
    EXPECT_EQ(ret, imagePattern->cacheImages_.end());
}
/**
 * @tc.name: UpdateCacheImageInfo001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateCacheImageInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateCacheImageInfo.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    auto imageFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().front());
    EXPECT_NE(imageFrameNode, nullptr);
    ImagePattern::CacheImageStruct newCacheImageStruct(imageFrameNode);
    newCacheImageStruct.isLoaded = true;
    int32_t index = 0;
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);
    EXPECT_NE(imagePattern->images_.size(), 0);

    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.pixmap_ = pixelMap;
    auto imageLayoutProperty = newCacheImageStruct.imageNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);

    void* voidPtr1 = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap1 = PixelMap::CreatePixelMap(voidPtr1);
    imageSourceInfo.pixmap_ = pixelMap1;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);
    if (!frameNode->layoutProperty_->calcLayoutConstraint_) {
        frameNode->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    }
    EXPECT_NE(frameNode->layoutProperty_->calcLayoutConstraint_, nullptr);
    CalcLength width(2.0f);
    CalcLength height(3.0f);
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize = std::make_optional<CalcSize>(width, height);
    imagePattern->UpdateCacheImageInfo(newCacheImageStruct, index);
    EXPECT_FALSE(newCacheImageStruct.isLoaded);
}

/**
 * @tc.name: AddImageLoadSuccessEvent001
 * @tc.desc: Test GetNextIndex and AddImageLoadSuccessEvent for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AddImageLoadSuccessEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call AddImageLoadSuccessEvent.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    imagePattern->AddImageLoadSuccessEvent(imageNode);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.pixmap_ = pixelMap;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    ImagePattern::CacheImageStruct cacheImageStruct(imageNode);
    imagePattern->cacheImages_.emplace_back(cacheImageStruct);
    LoadImageSuccessEvent info(300, 200, 400, 500);
    info.loadingStatus_ = 1;
    auto eventHub = imageNode->GetOrCreateEventHub<ImageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->FireCompleteEvent(info);
    auto ret = imagePattern->GetNextIndex(0);
    EXPECT_EQ(ret, 1);
    imagePattern->nowImageIndex_ = 2;
    eventHub->FireCompleteEvent(info);
    imagePattern->nowImageIndex_ = 1;
    eventHub->FireCompleteEvent(info);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = nullptr;
    }
    eventHub->FireCompleteEvent(info);
    EXPECT_TRUE(imagePattern->cacheImages_.back().isLoaded);
}

/**
 * @tc.name: AdaptSelfSize001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AdaptSelfSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call AdaptSelfSize.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    imagePattern->AdaptSelfSize();
    EXPECT_TRUE(imagePattern->hasSizeChanged);
    CalcLength width(2.0f);
    CalcLength height(3.0f);
    EXPECT_NE(frameNode->layoutProperty_->calcLayoutConstraint_, nullptr);
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize = std::make_optional<CalcSize>();
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize->SetHeight(height);
    imagePattern->AdaptSelfSize();
    frameNode->layoutProperty_->calcLayoutConstraint_->selfIdealSize->SetWidth(width);
    imagePattern->AdaptSelfSize();
    imagePattern->images_.clear();
    imagePattern->AdaptSelfSize();
    EXPECT_TRUE(imagePattern->hasSizeChanged);
}

/**
 * @tc.name: CreatePictureAnimation001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreatePictureAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call CreatePictureAnimation.
     * @tc.expected:
     */
    int32_t index = 0;
    int32_t size = 1;
    imagePattern->durationTotal_ = 1;
    auto pictureAnimation = imagePattern->CreatePictureAnimation(size);
    pictureAnimation->NotifyListener(index);
    EXPECT_EQ(imagePattern->nowImageIndex_, 0);
}

/**
 * @tc.name: OnVisibleAreaChange001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnVisibleAreaChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call OnVisibleAreaChange.
     * @tc.expected:
     */
    auto pipeline = frameNode->GetContextRefPtr();
    imagePattern->animator_->AttachScheduler(pipeline);
    SystemProperties::debugEnabled_ = true;
    imagePattern->animator_->status_ = OHOS::Ace::Animator::Status::PAUSED;
    imagePattern->imageType_ = ImageType::ANIMATED_DRAWABLE;
    imagePattern->OnVisibleAreaChange(true, 1.0f);
    EXPECT_EQ(imagePattern->animator_->status_, OHOS::Ace::Animator::Status::RUNNING);
}

/**
 * @tc.name: InitCopy001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call mouseEvent_.
     * @tc.expected:
     */
    imagePattern->InitCopy();
    ASSERT_NE(imagePattern->mouseEvent_, nullptr);
    MouseInfo info;
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    imagePattern->mouseEvent_->GetOnMouseEventFunc()(info);
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    imagePattern->mouseEvent_->GetOnMouseEventFunc()(info);
    info.SetButton(MouseButton::RIGHT_BUTTON);
    info.SetAction(MouseAction::MOVE);
    imagePattern->mouseEvent_->GetOnMouseEventFunc()(info);
    info.SetButton(MouseButton::BACK_BUTTON);
    info.SetAction(MouseAction::PULL_UP);
    imagePattern->mouseEvent_->GetOnMouseEventFunc()(info);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    SelectOverlayInfo& info1 = pipeline->GetSelectOverlayManager()->selectOverlayInfo_;
    RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
    bool isFirst = false;
    info1.onHandleMoveDone(rect, isFirst);
    bool closedByGlobalEvent = true;
    info1.onClose(closedByGlobalEvent);
    EXPECT_FALSE(imagePattern->isSelected_);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected:
     */
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    InspectorFilter filter;
    filter.filterExt.clear();
    filter.filterFixed = 1;
    imagePattern->ToJsonValue(json, filter);
    filter.filterExt.emplace_back("test001");
    imagePattern->ToJsonValue(json, filter);
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    DynamicRangeMode value = DynamicRangeMode::CONSTRAINT;
    imageRenderProperty->UpdateDynamicMode(value);
    imagePattern->ToJsonValue(json, filter);
    DynamicRangeMode defaultValue = DynamicRangeMode::STANDARD;
    EXPECT_EQ(imageRenderProperty->GetDynamicModeValue(defaultValue), DynamicRangeMode::CONSTRAINT);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChange001
 * @tc.desc: call TriggerFirstVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TriggerFirstVisibleAreaChange001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    frameNode->onMainTree_ = true;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->isComponentSnapshotNode_ = true;
    imagePattern->TriggerFirstVisibleAreaChange();
    EXPECT_TRUE(imagePattern->isFormAnimationStart_);
}

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnAreaChangedInner001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OpenSelectOverlay();
    imagePattern->OnAreaChangedInner();
    imagePattern->selectOverlay_->Close();
    imagePattern->OnAreaChangedInner();
    EXPECT_NE(imagePattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: DumpRenderInfo001
 * @tc.desc: call DumpRenderInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpRenderInfo001, TestSize.Level1)
{
    auto [frameNode, imageLayoutProperty, imagePattern, imageRenderProperty] = GetCompoment();

    imagePattern->TriggerFirstVisibleAreaChange();
    imagePattern->imageAnalyzerManager_ = nullptr;
    EXPECT_EQ(imagePattern->IsSupportImageAnalyzerFeature(), false);
    auto frameNodePtr = AceType::Claim(frameNode);
    imagePattern->AddImageLoadSuccessEvent(frameNodePtr);
    auto eventHub = frameNode->GetOrCreateEventHub<ImageEventHub>();
    EXPECT_NE(eventHub->completeEvent_, nullptr);
    std::vector<float> matrix = { 1.1f };
    ImageModelNG::SetColorFilterMatrix(frameNode, matrix);
    imagePattern->SetColorFilter(frameNodePtr);
    imagePattern->DumpRenderInfo();
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), matrix);
    imageLayoutProperty->UpdateSourceSize(SizeF());
    imageLayoutProperty->UpdateAutoResize(false);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    renderProp->UpdateSmoothEdge(10.0f);
    imagePattern->DumpLayoutInfo();
    imagePattern->DumpRenderInfo();
    auto smoothEdge = renderProp->GetSmoothEdge();
    EXPECT_TRUE(smoothEdge.has_value());
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: call DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OnRecycle();
    imagePattern->DumpInfo();
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
    imagePattern->DumpAdvanceInfo();
    EXPECT_EQ(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: EnableAnalyzer001
 * @tc.desc: call EnableAnalyzer.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, EnableAnalyzer001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: call OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, imageLayoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = true;
    ImagePattern::CacheImageStruct cacheImageStruct(frameNode);
    imagePattern->cacheImages_.emplace_back(cacheImageStruct);
    DirtySwapConfig config;
    config.skipMeasure = false;
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    layoutWrapper->skipMeasureContent_ = false;
    config.skipMeasure = true;
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    config.skipMeasure = false;

    EXPECT_EQ(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), imagePattern->image_);
    imagePattern->images_.clear();
    EXPECT_TRUE(imagePattern->images_.size() == 0);
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: UpdateFormDurationByRemainder001
 * @tc.desc: call UpdateFormDurationByRemainder.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateFormDurationByRemainder001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    frameNode->onMainTree_ = true;
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    EXPECT_EQ(imagePattern->IsFormRender(), true);
    imagePattern->animator_->duration_ = 2000;
    imagePattern->ResetFormAnimationStartTime();
    imagePattern->UpdateFormDurationByRemainder();
    ASSERT_NE(imagePattern->animator_->duration_, 2000);
}

/**
 * @tc.name: CheckCallback001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CheckCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call callbacks.
     * @tc.expected:
     */
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto currentSourceInfo = imageLayoutProperty->GetImageSourceInfo().value_or(ImageSourceInfo(""));
    ImageSourceInfo value("");
    imageLayoutProperty->UpdateImageSourceInfo(value);
    ImageSourceInfo sourceInfo("testmsg");
    auto callback1 = imagePattern->CreateDataReadyCallback();
    callback1(sourceInfo);
    auto callback2 = imagePattern->CreateLoadSuccessCallback();
    callback2(sourceInfo);
    auto callback3 = imagePattern->CreateLoadFailCallback();
    std::string errorMsg = "erormsg";
    callback3(sourceInfo, errorMsg);
    auto callback4 = imagePattern->CreateCompleteCallBackInDataReady();
    callback4(sourceInfo);
    currentSourceInfo.SetIsFromReset(true);
    ImageSourceInfo value1("testmsg");
    imageLayoutProperty->UpdateImageSourceInfo(value1);
    callback3(sourceInfo, errorMsg);
    frameNode->draggable_ = true;
    SystemProperties::debugEnabled_ = true;
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    BorderRadiusProperty value2(Dimension(10.0f));
    renderContext->UpdateBorderRadius(value2);
    callback2(sourceInfo);
    frameNode->GetGeometryNode()->SetContentSize(SizeF(100.0f, 100.0f));
    auto props = AceType::DynamicCast<ImageLayoutProperty>(frameNode->GetLayoutProperty());
    ASSERT_NE(props, nullptr);
    props->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    props->calcLayoutConstraint_->selfIdealSize = std::make_optional<CalcSize>(CalcLength(100.0f), CalcLength(200.0f));
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    DynamicRangeMode value3 = DynamicRangeMode::CONSTRAINT;
    imageRenderProperty->UpdateDynamicMode(value3);
    callback1(sourceInfo);
    imageLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    imagePattern->isImageAnimator_ = false;
    callback1(sourceInfo);
    imagePattern->isImageAnimator_ = true;
    callback1(sourceInfo);
    EXPECT_EQ(imagePattern->altImage_, nullptr);
}

/**
 * @tc.name: CheckHandles001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CheckHandles001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call CheckHandles.
     * @tc.expected:
     */
    SelectHandleInfo handleInfo;
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(false);
    imagePattern->CheckHandles(handleInfo);
    EXPECT_FALSE(renderContext->GetClipEdge().value());
}


/**
 * @tc.name: ImagePatternInitOnKeyEvent001
 * @tc.desc: Test Image InitOnKeyEvent method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternInitOnKeyEvent001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);
    imagePattern->InitOnKeyEvent();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ImagePatternOnKeyEvent001
 * @tc.desc: Test Image OnKeyEvent method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternOnKeyEvent001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->OnKeyEvent();
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);

    /**
     * @tc.steps: step1. init onKey event.
     */
    imagePattern->keyEventCallback_ = [](const KeyEvent& event) -> bool {return false;};
    imagePattern->InitOnKeyEvent();
    ASSERT_NE(imagePattern->keyEventCallback_, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ImageDumpInfo001
 * @tc.desc: Output the dump info of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageDumpInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Out dump info.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->DumpInfo(json);
    ASSERT_NE(json, nullptr);

    /**
     * @tc.steps: step2. Out other dump info.
     */
    pattern->OnRecycle();
    EXPECT_EQ(pattern->loadingCtx_, nullptr);
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateSourceSize(SizeF());
    auto imageRenderProperty = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    DynamicRangeMode value3 = DynamicRangeMode::CONSTRAINT;
    imageRenderProperty->UpdateDynamicMode(value3);
    imageRenderProperty->UpdateSmoothEdge(10.0f);
    std::vector<std::vector<int>> cases = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    ImageResizableSlice defaultImageResizableSlice = ImageResizableSlice {
        .left = Dimension(-1),
        .right = Dimension(-1),
        .top = Dimension(-1),
        .bottom = Dimension(-1)
    };
    for (uint32_t i = 0; i < cases.size(); ++i) {
        ImageResizableSlice tmp;
        tmp.bottom = Dimension(cases[i][0]);
        tmp.top = Dimension(cases[i][1]);
        tmp.left = Dimension(cases[i][2]);
        tmp.right = Dimension(cases[i][3]);
        imageRenderProperty->UpdateImageResizableSlice(tmp);
        frameNode->MarkModifyDone();
        EXPECT_EQ(imageRenderProperty->GetImageResizableSliceValue(defaultImageResizableSlice), tmp);
    }
    pattern->DumpInfo(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: ImageDumpAdvanceInfo001
 * @tc.desc: Output the dump advance info of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageDumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->DumpAdvanceInfo(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: DumpRenderInfo002
 * @tc.desc: Output the dump interpolation of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpRenderInfo002, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageRenderProperty = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    /**
     * @tc.cases: case1. ImageInterpolation::LOW.
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::LOW);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), ImageInterpolation::LOW);

    /**
     * @tc.cases: case2. ImageInterpolation::MEDIUM.
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::MEDIUM);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), ImageInterpolation::MEDIUM);

    /**
     * @tc.cases: case3. ImageInterpolation::HIGH.
     */
    imageRenderProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetImageInterpolation().value(), ImageInterpolation::HIGH);
}

/**
 * @tc.name: DumpRenderInfo003
 * @tc.desc: Output the dump DynamicRangeMode of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpRenderInfo003, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageRenderProperty = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    /**
     * @tc.cases: case1. DynamicRangeMode::HIGH.
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::HIGH);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetDynamicMode().value(), DynamicRangeMode::HIGH);

    /**
     * @tc.cases: case2. DynamicRangeMode::CONSTRAINT.
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::CONSTRAINT);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetDynamicMode().value(), DynamicRangeMode::CONSTRAINT);

    /**
     * @tc.cases: case3. DynamicRangeMode::STANDARD.
     */
    imageRenderProperty->UpdateDynamicMode(DynamicRangeMode::STANDARD);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetDynamicMode().value(), DynamicRangeMode::STANDARD);
}

/**
 * @tc.name: DumpRenderInfo004
 * @tc.desc: Output the dump ImageResizableSlice of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpRenderInfo004, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageRenderProperty = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    /**
     * @tc.cases: case1. DynamicRangeMode::HIGH.
     */
    std::vector<std::vector<int>> cases = {
        {1, 2, 3, 4},
        {5, 6, 7, 8}
    };
    ImageResizableSlice defaultImageResizableSlice = ImageResizableSlice {
        .left = Dimension(-1),
        .right = Dimension(-1),
        .top = Dimension(-1),
        .bottom = Dimension(-1)
    };
    for (uint32_t i = 0; i < cases.size(); ++i) {
        ImageResizableSlice tmp;
        tmp.bottom = Dimension(cases[i][0]);
        tmp.top = Dimension(cases[i][1]);
        tmp.left = Dimension(cases[i][2]);
        tmp.right = Dimension(cases[i][3]);
        imageRenderProperty->UpdateImageResizableSlice(tmp);
        frameNode->MarkModifyDone();
        pattern->DumpRenderInfo(json);
        EXPECT_EQ(imageRenderProperty->GetImageResizableSliceValue(defaultImageResizableSlice), tmp);
    }
}

/**
 * @tc.name: DumpRenderInfo005
 * @tc.desc: Output the dump ImageRepeat of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpRenderInfo005, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageRenderProperty = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    /**
     * @tc.cases: case1. ImageRepeat::NO_REPEAT.
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), ImageRepeat::NO_REPEAT);

    /**
     * @tc.cases: case2. ImageRepeat::REPEAT_X.
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), ImageRepeat::REPEAT_X);

    /**
     * @tc.cases: case3. ImageRepeat::REPEAT_Y.
     */
    imageRenderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_Y);
    pattern->DumpRenderInfo(json);
    EXPECT_EQ(imageRenderProperty->GetImageRepeat().value(), ImageRepeat::REPEAT_Y);
}

/**
 * @tc.name: DumpLayoutInfo001
 * @tc.desc: Output the dump DynamicRangeMode of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpLayoutInfo001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageLayoutProperty = pattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.cases: case1. ImageFit::CONTAIN.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::CONTAIN);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::CONTAIN);

    /**
     * @tc.cases: case2. ImageFit::COVER.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::COVER);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::COVER);

    /**
     * @tc.cases: case3. ImageFit::FILL.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::FILL);

    /**
     * @tc.cases: case3. ImageFit::FITWIDTH.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::FITWIDTH);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::FITWIDTH);

    /**
     * @tc.cases: case3. ImageFit::FITHEIGHT.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::FITHEIGHT);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::FITHEIGHT);

    /**
     * @tc.cases: case3. ImageFit::NONE.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::NONE);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::NONE);

    /**
     * @tc.cases: case3. ImageFit::SCALE_DOWN.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::SCALE_DOWN);

    /**
     * @tc.cases: case3. ImageFit::TOP_LEFT.
     */
    imageLayoutProperty->UpdateImageFit(ImageFit::TOP_LEFT);
    pattern->DumpRenderInfo();
    EXPECT_EQ(imageLayoutProperty->GetImageFit().value(), ImageFit::TOP_LEFT);
}

/**
 * @tc.name: ImageConvertOrientation001
 * @tc.desc: Output the orientation of ImagePattern object.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageConvertOrientation001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.cases: case1. default.
     */
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::UP);

    /**
     * @tc.cases: case2. ImageRotateOrientation::RIGHT.
     */
    pattern->SetOrientation(ImageRotateOrientation::RIGHT);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::RIGHT);

    /**
     * @tc.cases: case3. ImageRotateOrientation::DOWN.
     */
    pattern->SetOrientation(ImageRotateOrientation::DOWN);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::DOWN);

    /**
     * @tc.cases: case4. ImageRotateOrientation::LEFT.
     */
    pattern->SetOrientation(ImageRotateOrientation::LEFT);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::LEFT);

    /**
     * @tc.cases: case5. ImageRotateOrientation::AUTO.
     */
    pattern->SetOrientation(ImageRotateOrientation::AUTO);
    pattern->DumpInfo();
    EXPECT_EQ(pattern->GetOrientation(), ImageRotateOrientation::AUTO);
}

/**
 * @tc.name: ImageSetExternalDecodeFormat001
 * @tc.desc: Test SetExternalDecodeFormat.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageSetExternalDecodeFormat001, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();

    /**
     * @tc.cases: case1. default.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::UNKNOWN);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::UNKNOWN);

    /**
     * @tc.cases: case2. NV21.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::NV21);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::NV21);

    /**
     * @tc.cases: case3. RGBA_8888.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_8888);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::RGBA_8888);

    /**
     * @tc.cases: case4. RGBA_1010102.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_1010102);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::RGBA_1010102);

    /**
     * @tc.cases: case5. YCBCR_P010.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::YCBCR_P010);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::YCBCR_P010);

    /**
     * @tc.cases: case6. YCRCB_P010.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::YCRCB_P010);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::YCRCB_P010);

    /**
     * @tc.cases: case7. NV12.
     */
    pattern->SetExternalDecodeFormat(PixelFormat::NV12);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::UNKNOWN);
}

/**
 * @tc.name: OnAreaChangedInner002
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnAreaChangedInner002, TestSize.Level1)
{
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->OpenSelectOverlay();
    imagePattern->OnAreaChangedInner();
    imagePattern->selectOverlay_ = nullptr;
    imagePattern->OnAreaChangedInner();
    EXPECT_FALSE(imagePattern->selectOverlay_);
}

/**
 * @tc.name: ImageRemoveAreaChangeInner001
 * @tc.desc: Test RemoveAreaChangeInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageRemoveAreaChangeInner001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call AddImageLoadSuccessEvent.
     * @tc.expected:
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    for (auto& image : imagePattern->images_) {
        image.pixelMap = pixelMap;
    }
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.pixmap_ = pixelMap;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    ImagePattern::CacheImageStruct cacheImageStruct(imageNode);
    imagePattern->cacheImages_.emplace_back(cacheImageStruct);
    LoadImageSuccessEvent info(300, 200, 400, 500);
    info.loadingStatus_ = 1;
    auto eventHub = imageNode->GetOrCreateEventHub<ImageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    bool flag = false;
    OnAreaChangedFunc onAreaChanged = [&flag](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flag = !flag; };
    eventHub->SetOnAreaChanged(std::move(onAreaChanged));
    imagePattern->RemoveAreaChangeInner();
    EXPECT_NE(eventHub, nullptr);
}

/**
 * @tc.name: CheckCallback002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CheckCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call callbacks.
     * @tc.expected:
     */
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    int testData = 0;
    std::function onProgress = [&testData](const uint32_t&, const uint32_t&) {
        testData = 1;
    };
    imagePattern->SetOnProgressCallback(std::move(onProgress));
    imagePattern->onProgressCallback_(uint32_t(0), uint32_t(1));
    imagePattern->LoadImage(ImageSourceInfo(""), PROPERTY_UPDATE_NORMAL, VisibleType::GONE);
    EXPECT_EQ(testData, 1);
}

/**
 * @tc.name: ImageHandleCopyTest001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageHandleCopyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->HandleCopy();
    EXPECT_NE(imagePattern->clipboard_, nullptr);

    /**
     * @tc.steps: step5. HandleCopy again.
     */
    imagePattern->HandleCopy();
    EXPECT_NE(imagePattern->clipboard_, nullptr);
}

/**
 * @tc.name: GetImageInterpolation001
 * @tc.desc: Get Image Interpolation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, GetImageInterpolation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(false);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    imagePattern->DumpInfo(json);
    EXPECT_NE(json, nullptr);
    /**
     * @tc.steps: step2. call GetImageInterpolation.
     * @tc.expected: Returned value is LOW.
     */
    imagePattern->interpolationDefault_ = ImageInterpolation::LOW;
    imagePattern->DumpRenderInfo(json);
    auto res = imagePattern->GetDefaultInterpolation();
    ImageInterpolation Msg = ImageInterpolation::LOW;
    EXPECT_EQ(res, Msg);
    /**
     * @tc.steps: step3. call GetImageInterpolation.
     * @tc.expected: Returned value is MEDIUM.
     */
    imagePattern->interpolationDefault_ = ImageInterpolation::MEDIUM;
    imagePattern->DumpRenderInfo(json);
    res = imagePattern->GetDefaultInterpolation();
    Msg = ImageInterpolation::MEDIUM;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: GetImageInterpolation002
 * @tc.desc: Get Image Interpolation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, GetImageInterpolation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    imagePattern->DumpInfo(json);
    EXPECT_NE(json, nullptr);
    /**
     * @tc.steps: step2. call GetImageInterpolation.
     * @tc.expected: Returned value is HIGH.
     */
    imagePattern->interpolationDefault_ = ImageInterpolation::HIGH;
    imagePattern->DumpRenderInfo(json);
    auto res = imagePattern->GetDefaultInterpolation();
    ImageInterpolation Msg = ImageInterpolation::HIGH;
    EXPECT_EQ(res, Msg);
    /**
     * @tc.steps: step3. call GetImageInterpolation.
     * @tc.expected: Returned value is NONE.
     */
    imagePattern->interpolationDefault_ = ImageInterpolation::NONE;
    imagePattern->DumpRenderInfo(json);
    res = imagePattern->GetDefaultInterpolation();
    Msg = ImageInterpolation::NONE;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: ConvertOrientationToString001
 * @tc.desc: Convert Orientation To String
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);
    /**
     * @tc.steps: step2. call ConvertOrientationToString.
     * @tc.expected: Returned value is UP.
     */
    ImageRotateOrientation orientation = ImageRotateOrientation::UP;
    imagePattern->SetOrientation(orientation);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation Msg = ImageRotateOrientation::UP;
    EXPECT_EQ(res, Msg);
    /**
     * @tc.steps: step3. call GetImageInterpolation.
     * @tc.expected: Returned value is NONE.
     */
    orientation = ImageRotateOrientation::RIGHT;
    imagePattern->SetOrientation(orientation);
    imagePattern->DumpInfo();
    res = imagePattern->GetOrientation();
    Msg = ImageRotateOrientation::RIGHT;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: ConvertOrientationToString002
 * @tc.desc: Convert Orientation To String
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);
    /**
     * @tc.steps: step2. call ConvertOrientationToString.
     * @tc.expected: Returned value is DOWN.
     */
    ImageRotateOrientation orientation = ImageRotateOrientation::DOWN;
    imagePattern->SetOrientation(orientation);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation Msg = ImageRotateOrientation::DOWN;
    EXPECT_EQ(res, Msg);
    /**
     * @tc.steps: step3. call GetImageInterpolation.
     * @tc.expected: Returned value is LEFT.
     */
    orientation = ImageRotateOrientation::LEFT;
    imagePattern->SetOrientation(orientation);
    imagePattern->DumpInfo();
    res = imagePattern->GetOrientation();
    Msg = ImageRotateOrientation::LEFT;
    EXPECT_EQ(res, Msg);
    /**
     * @tc.steps: step3. call GetImageInterpolation.
     * @tc.expected: Returned value is AUTO.
     */
    orientation = ImageRotateOrientation::AUTO;
    imagePattern->SetOrientation(orientation);
    imagePattern->DumpInfo();
    res = imagePattern->GetOrientation();
    Msg = ImageRotateOrientation::AUTO;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: PrepareAnimation
 * @tc.desc: Prepare Animation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, PrepareAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator(2);
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);
    /**
     * @tc.steps: step2. call PrepareAnimation.
     * @tc.expected: Returned value is true.
     */
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, { .selected = true });
    EXPECT_NE(imagePaintMethod.canvasImage_, nullptr);
    auto canvasImage = imagePaintMethod.canvasImage_;
    EXPECT_NE(canvasImage, nullptr);
    imagePattern->PrepareAnimation(canvasImage);
    bool res = canvasImage->IsStatic();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: DumpFillColor
 * @tc.desc: Dump Fill Color
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpFillColor, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
     * @tc.steps: step2. call DumpFillColor.
     * @tc.expected: Returned color value is BLUE.
     */
    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    image.SetImageFill(Color::BLUE);
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(imageRenderProperty, nullptr);
    imagePattern->DumpRenderInfo();
    EXPECT_EQ(imageRenderProperty->GetSvgFillColor().value(), Color::BLUE);
}

/**
 * @tc.name: SetImageAnalyzerConfig
 * @tc.desc: SetImageAnalyzerConfig
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetImageAnalyzerConfig, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
     * @tc.steps: step2. call SetImageAnalyzerConfig.
     * @tc.expected: Returned value is true.
     */
    imagePattern->isEnableAnalyzer_ = true;
    void* voidPtr = static_cast<void*>(new char[0]);
    auto isEnableAnalyzer = imagePattern->isEnableAnalyzer_;
    imagePattern->SetImageAnalyzerConfig(voidPtr);
    EXPECT_TRUE(isEnableAnalyzer);
}

/**
 * @tc.name: RecycleImageData001
 * @tc.desc: RecycleImageData001
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, RecycleImageData001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create Image frameNode.
    */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
    * @tc.steps: step2. set isShow true and call RecycleImageData.
    * @tc.expected: Returned value is false.
    */
    imagePattern->isShow_ = true;
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
* @tc.name: RecycleImageData002
* @tc.desc: RecycleImageData002
* @tc.type: FUNC
*/
HWTEST_F(ImagePatternTestNg, RecycleImageData002, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create Image frameNode.
    */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
    * @tc.steps: step2. set isShow false and call RecycleImageData.
    * @tc.expected: Returned value is false.
    */
    imagePattern->isShow_ = false;
    imagePattern->OnRecycle();
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
* @tc.name: RecycleImageData003
* @tc.desc: RecycleImageData003
* @tc.type: FUNC
*/
HWTEST_F(ImagePatternTestNg, RecycleImageData003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create Image frameNode.
    */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
    * @tc.steps: step2. set isShow false and call RecycleImageData.
    * @tc.expected: Returned value is false.
    */
    imagePattern->isShow_ = false;
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
* @tc.name: RecycleImageData004
* @tc.desc: RecycleImageData004
* @tc.type: FUNC
*/
HWTEST_F(ImagePatternTestNg, RecycleImageData004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create Image frameNode.
    */
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(IMAGE_SRC_URL);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
    * @tc.steps: step2. set isShow false and call RecycleImageData.
    * @tc.expected: Returned value is true.
    */
    imagePattern->isShow_ = false;
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_TRUE(imagePattern->RecycleImageData());
}

/**
* @tc.name: AllowVisibleAreaCheck001
* @tc.desc: AllowVisibleAreaCheck001
* @tc.type: FUNC
*/
HWTEST_F(ImagePatternTestNg, AllowVisibleAreaCheck001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create Image frameNode.
    */
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    EXPECT_NE(frameNode, nullptr);
    RefPtr<FrameNode> parent = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(parent, nullptr);
    frameNode->SetParent(parent);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(imageLayoutProperty, nullptr);
    /**
    * @tc.steps: step2. call AllowVisibleAreaCheck.
    * @tc.expected: Returned value is false.
    */
    EXPECT_FALSE(imagePattern->AllowVisibleAreaCheck());
}
} // namespace OHOS::Ace::NG