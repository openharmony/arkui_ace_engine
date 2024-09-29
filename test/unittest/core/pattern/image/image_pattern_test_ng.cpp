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
        childNode->GetEventHub<EventHub>()->GetVisibleAreaCallback(true).callback = callback;
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
    auto eventHub = imageNode->GetEventHub<ImageEventHub>();
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
    imagePattern->imageType_ = ImagePattern::ImageType::ANIMATION;
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
 * @tc.name: UpdateFillColorIfForegroundColor001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateFillColorIfForegroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreatePixelMapAnimator();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call UpdateFillColorIfForegroundColor.
     * @tc.expected:
     */
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ForegroundColorStrategy value2 = ForegroundColorStrategy::NONE;
    renderContext->UpdateForegroundColorStrategy(value2);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo value1;
    value1.isSvg_ = true;
    imageLayoutProperty->UpdateImageSourceInfo(value1);
    auto imageRenderProperty = imagePattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    imagePattern->UpdateFillColorIfForegroundColor();

    Color value(10);
    renderContext->UpdateForegroundColor(value);
    ImageSourceInfo value3;
    value3.isSvg_ = true;
    imageLayoutProperty->UpdateImageSourceInfo(value3);
    renderContext->ResetForegroundColorStrategy();
    imagePattern->UpdateFillColorIfForegroundColor();
    auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
    EXPECT_EQ(imageSourceInfo.fillColor_.value_or(Color::TRANSPARENT), Color::FOREGROUND);
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
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->isComponentSnapshotNode_ = true;
    imagePattern->TriggerFirstVisibleAreaChange();
    EXPECT_FALSE(imagePattern->isFormAnimationStart_);
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
    EXPECT_NE(imagePattern->selectOverlay_.GetRawPtr(), nullptr);
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
    EXPECT_EQ(imagePattern->gifAnimation_, false);
    imagePattern->imageAnalyzerManager_ = nullptr;
    EXPECT_EQ(imagePattern->IsSupportImageAnalyzerFeature(), false);
    auto frameNodePtr = AceType::Claim(frameNode);
    imagePattern->AddImageLoadSuccessEvent(frameNodePtr);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub->completeEvent_, nullptr);
    std::vector<float> matrix = { 1.1f };
    ImageModelNG::SetColorFilterMatrix(frameNode, matrix);
    imagePattern->SetColorFilter(frameNodePtr);
    imagePattern->DumpRenderInfo();
    EXPECT_EQ(imageRenderProperty->GetColorFilter().value(), matrix);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    renderProp->UpdateSmoothEdge(10.0f);
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
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrentContext();
    pipeline->SetIsFormRender(true);
    EXPECT_EQ(imagePattern->IsFormRender(), true);
    imagePattern->animator_->duration_ = 2000;
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
} // namespace OHOS::Ace::NG