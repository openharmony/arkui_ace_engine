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
#include "test/mock/base/mock_pixel_map.h"
#include "test/mock/core/common/mock_image_analyzer_manager.h"

#include "base/image/image_defines.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImagePatternTestNg : public ImageBases {};

class MockImageData : public ImageData {
public:
    MOCK_METHOD(size_t, GetSize, (), (const, override));
    MOCK_METHOD(const void*, GetData, (), (const, override));
};

class MockImageObject : public ImageObject {
public:
    MOCK_METHOD(void, MakeCanvasImage,
        (const WeakPtr<ImageLoadingContext>& ctxWp, const SizeF& resizeTarget, bool forceResize, bool syncLoad),
        (override));

    MOCK_METHOD(RefPtr<ImageObject>, Clone, (), (override));
    MockImageObject(const ImageSourceInfo& sourceInfo, const SizeF& imageSize, const RefPtr<ImageData>& data)
        : ImageObject(sourceInfo, imageSize, data)
    {}
    ~MockImageObject() override = default;
};

/**
 * @tc.name: TriggerVisibleAreaChangeForChild001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TriggerVisibleAreaChangeForChild001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    EXPECT_FALSE(flag);
}

/**
 * @tc.name: SetColorFilter001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetColorFilter001, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
}
/**
 * @tc.name: OnSensitiveStyleChange001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnSensitiveStyleChange001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
 * @tc.name: InitCopy001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitCopy001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
 * @tc.name: InitCopy002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitCopy002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call mouseEvent_.
     * @tc.expected:
     */
    imagePattern->InitCopy();
    ASSERT_NE(imagePattern->mouseEvent_, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    imagePattern->OpenSelectOverlay();
    SelectOverlayInfo& info1 = pipeline->GetSelectOverlayManager()->selectOverlayInfo_;
    RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
    bool isFirst = false;
    info1.onHandleMoveDone(rect, isFirst);
    imagePattern->HandleMoveDone(isFirst);
    EXPECT_TRUE(imagePattern->isSelected_);
    bool closedByGlobalEvent = true;
    info1.onClose(closedByGlobalEvent);
    EXPECT_FALSE(imagePattern->isSelected_);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ToJsonValue001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
 * @tc.name: TriggerFirstVisibleAreaChange003
 * @tc.desc: call TriggerFirstVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TriggerFirstVisibleAreaChange003, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call TriggerFirstVisibleAreaChange.
     * @tc.expected: previousVisibility_ is changed.
     */
    EXPECT_FALSE(imagePattern->previousVisibility_);
    imagePattern->TriggerFirstVisibleAreaChange();
    EXPECT_FALSE(imagePattern->previousVisibility_);
}

/**
 * @tc.name: TriggerFirstVisibleAreaChange004
 * @tc.desc: call TriggerFirstVisibleAreaChange.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TriggerFirstVisibleAreaChange004, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call TriggerFirstVisibleAreaChange.
     * @tc.expected: previousVisibility_ is changed.
     */
    EXPECT_FALSE(imagePattern->previousVisibility_);
    imagePattern->TriggerFirstVisibleAreaChange();
    EXPECT_FALSE(imagePattern->previousVisibility_);
    imagePattern->OnVisibleAreaChange(true);
    EXPECT_TRUE(imagePattern->previousVisibility_);
    imagePattern->TriggerFirstVisibleAreaChange();
    EXPECT_TRUE(imagePattern->previousVisibility_);
}

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: call OnAreaChangedInner.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnAreaChangedInner001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
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
HWTEST_F(ImagePatternTestNg, DumpRenderInfo001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    imagePattern->TriggerFirstVisibleAreaChange();
    imagePattern->imageAnalyzerManager_ = nullptr;
    EXPECT_EQ(imagePattern->IsSupportImageAnalyzerFeature(), false);
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub->completeEvent_, nullptr);
    std::vector<float> matrix = { 1.1f };
    ImageModelNG::SetColorFilterMatrix(AceType::RawPtr(frameNode), matrix);
    imagePattern->DumpRenderInfo();
    auto imageRenderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
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
    auto frameNode = CreateImageNode("", "", nullptr);
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
HWTEST_F(ImagePatternTestNg, EnableAnalyzer001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
HWTEST_F(ImagePatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: CheckCallback001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CheckCallback001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    ImageErrorInfo errorInfo;
    callback3(sourceInfo, errorMsg, errorInfo);
    auto callback4 = imagePattern->CreateCompleteCallBackInDataReady();
    callback4(sourceInfo);
    currentSourceInfo.SetIsFromReset(true);
    ImageSourceInfo value1("testmsg");
    imageLayoutProperty->UpdateImageSourceInfo(value1);
    callback3(sourceInfo, errorMsg, errorInfo);
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
HWTEST_F(ImagePatternTestNg, CheckHandles001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
HWTEST_F(ImagePatternTestNg, ImagePatternInitOnKeyEvent001, TestSize.Level0)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
HWTEST_F(ImagePatternTestNg, ImagePatternOnKeyEvent001, TestSize.Level0)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN));
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto event = KeyEvent();
    event.action = KeyAction::UNKNOWN;
    imagePattern->OnKeyEvent(event);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);

    /**
     * @tc.steps: step1. init onKey event.
     */
    imagePattern->keyEventCallback_ = [](const KeyEvent& event) -> bool { return false; };
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    std::vector<std::vector<int>> cases = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } };
    ImageResizableSlice defaultImageResizableSlice = ImageResizableSlice {
        .left = Dimension(-1), .right = Dimension(-1), .top = Dimension(-1), .bottom = Dimension(-1)
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);
    auto imageRenderProperty = pattern->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(imageRenderProperty, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();

    /**
     * @tc.cases: case1. DynamicRangeMode::HIGH.
     */
    std::vector<std::vector<int>> cases = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } };
    ImageResizableSlice defaultImageResizableSlice = ImageResizableSlice {
        .left = Dimension(-1), .right = Dimension(-1), .top = Dimension(-1), .bottom = Dimension(-1)
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
HWTEST_F(ImagePatternTestNg, OnAreaChangedInner002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
HWTEST_F(ImagePatternTestNg, ImageRemoveAreaChangeInner001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    EXPECT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.pixmap_ = pixelMap;
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    LoadImageSuccessEvent info(300, 200, 400, 500);
    info.loadingStatus_ = 1;
    auto eventHub = imageNode->GetEventHub<ImageEventHub>();
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
HWTEST_F(ImagePatternTestNg, CheckCallback002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    std::function onProgress = [&testData](const uint32_t&, const uint32_t&) { testData = 1; };
    imagePattern->SetOnProgressCallback(std::move(onProgress));
    imagePattern->onProgressCallback_(uint32_t(0), uint32_t(1));
    imagePattern->LoadImage(ImageSourceInfo(""), false);
    EXPECT_EQ(testData, 1);
}

/**
 * @tc.name: TestCreateImageDfxConfig002
 * @tc.desc: Verify srcType is correctly mapped from ImageSourceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestCreateImageDfxConfig002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageSourceInfo info("http://example.com/test.png");
    auto imageDfxConfig = imagePattern->CreateImageDfxConfig(info);
    EXPECT_EQ(imageDfxConfig.srcType_, static_cast<int32_t>(info.GetSrcType()));
}

/**
 * @tc.name: ImageHandleCopyTest001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageHandleCopyTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
 * @tc.name: TestCreateImageDfxConfig001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestCreateImageDfxConfig001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call CreateImageDfxConfig.
     * @tc.expected:
     */
    auto imageDfxConfig = imagePattern->CreateImageDfxConfig(ImageSourceInfo(""));
    EXPECT_EQ(imageDfxConfig.imageSrc_, "empty source");
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
HWTEST_F(ImagePatternTestNg, PrepareAnimation, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(::testing::Return(true));
    imagePattern->image_ = mockImage;

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
HWTEST_F(ImagePatternTestNg, DumpFillColor, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
HWTEST_F(ImagePatternTestNg, SetImageAnalyzerConfig, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
HWTEST_F(ImagePatternTestNg, RecycleImageData001, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
 * @tc.name: RecycleImageData002
 * @tc.desc: RecycleImageData002
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, RecycleImageData002, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
    imagePattern->OnRecycle();
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
 * @tc.name: RecycleImageData003
 * @tc.desc: RecycleImageData003
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, RecycleImageData003, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
 * @tc.name: RecycleImageData004
 * @tc.desc: RecycleImageData004
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, RecycleImageData004, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
 * @tc.name: AllowVisibleAreaCheck001
 * @tc.desc: AllowVisibleAreaCheck001
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AllowVisibleAreaCheck001, TestSize.Level0)
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

/**
 * @tc.name: HasSceneChanged001
 * @tc.desc: hasSceneChanged returns true when layout property is valid and source changes.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, HasSceneChanged001, TestSize.Level0)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // Set a valid image source info
    layoutProperty->UpdateImageSourceInfo(ImageSourceInfo("test_src"));

    // Expect hasSceneChanged always returns true
    EXPECT_TRUE(imagePattern->hasSceneChanged());
}

/**
 * @tc.name: HasSceneChanged002
 * @tc.desc: hasSceneChanged returns true even if loadingCtx_ is set and source is the same.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, HasSceneChanged002, TestSize.Level0)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ImageSourceInfo sourceInfo("test_src");
    layoutProperty->UpdateImageSourceInfo(sourceInfo);

    // Setup loading context to match the same source
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);
    imagePattern->loadingCtx_ = loadingCtx;

    // Set srcRect_ and dstRect_ to same value (won't affect result now)
    imagePattern->srcRect_ = RectF(0, 0, 100, 100);
    imagePattern->dstRect_ = RectF(0, 0, 100, 100);

    // Still expect true because condition is removed
    EXPECT_TRUE(imagePattern->hasSceneChanged());
}

/**
 * @tc.name: HasSceneChanged003
 * @tc.desc: hasSceneChanged returns true even if loadingCtx_ is set and source is not the same.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, HasSceneChanged003, TestSize.Level0)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(frameNode, nullptr);

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    ImageSourceInfo sourceInfo("test_src");
    layoutProperty->UpdateImageSourceInfo(sourceInfo);

    // Setup loading context to match the same source
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);
    imagePattern->loadingCtx_ = loadingCtx;

    // Set srcRect_ and dstRect_ to not same value (won't affect result now)
    imagePattern->srcRect_ = RectF(0, 0, 200, 200);
    imagePattern->dstRect_ = RectF(0, 0, 100, 100);

    // Still expect true because condition is removed
    EXPECT_TRUE(imagePattern->hasSceneChanged());
}

/**
 * @tc.name: ConvertOrientationToString003
 * @tc.desc: Test ConvertOrientationToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString003, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetOrientation(ImageRotateOrientation::UP_MIRRORED);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation Msg = ImageRotateOrientation::UP_MIRRORED;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: ConvertOrientationToString004
 * @tc.desc: Test ConvertOrientationToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString004, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetOrientation(ImageRotateOrientation::RIGHT_MIRRORED);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation Msg = ImageRotateOrientation::RIGHT_MIRRORED;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: ConvertOrientationToString005
 * @tc.desc: Test ConvertOrientationToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString005, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetOrientation(ImageRotateOrientation::DOWN_MIRRORED);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation Msg = ImageRotateOrientation::DOWN_MIRRORED;
    EXPECT_EQ(res, Msg);
}

/**
 * @tc.name: ConvertOrientationToString006
 * @tc.desc: Test ConvertOrientationToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString006, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetOrientation(ImageRotateOrientation::DOWN);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation msg = ImageRotateOrientation::DOWN;
    EXPECT_EQ(res, msg);
}

/**
 * @tc.name: ConvertOrientationToString007
 * @tc.desc: Test ConvertOrientationToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString007, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetOrientation(ImageRotateOrientation::DOWN_MIRRORED);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation msg = ImageRotateOrientation::DOWN_MIRRORED;
    EXPECT_EQ(res, msg);
}

/**
 * @tc.name: ConvertOrientationToString008
 * @tc.desc: Test ConvertOrientationToString.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ConvertOrientationToString008, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->SetOrientation(ImageRotateOrientation::LEFT_MIRRORED);
    imagePattern->DumpInfo();
    auto res = imagePattern->GetOrientation();
    ImageRotateOrientation msg = ImageRotateOrientation::LEFT_MIRRORED;
    EXPECT_EQ(res, msg);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
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

    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    imagePattern->imageAnalyzerManager_ = imageAnalyzerManager;
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
    imagePattern->isEnableAnalyzer_ = true;

    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);
    imagePattern->loadingCtx_ = loadingCtx;
    EXPECT_EQ(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config), imagePattern->image_);
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(false);
    EXPECT_FALSE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: call DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpAdvanceInfo002, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    pattern->DumpAdvanceInfo(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: DumpAdvanceInfo003
 * @tc.desc: call DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, DumpAdvanceInfo003, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->loadingCtx_ = nullptr;
    pattern->DumpAdvanceInfo(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: ResetImageAndAlt001
 * @tc.desc: call ResetImageAndAlt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetImageAndAlt001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    frameNode->isInDestroying_ = true;
    frameNode->onMainTree_ = true;
    imagePattern->ResetImageAndAlt();
    EXPECT_TRUE(imagePattern->isNeedReset_);
}

/**
 * @tc.name: ResetImageAndAlt002
 * @tc.desc: call ResetImageAndAlt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetImageAndAlt002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    frameNode->isInDestroying_ = true;
    frameNode->onMainTree_ = false;
    imagePattern->ResetImageAndAlt();
    EXPECT_FALSE(imagePattern->isNeedReset_);
}

/**
 * @tc.name: ResetImageAndAlt003
 * @tc.desc: call ResetImageAndAlt.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetImageAndAlt003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    frameNode->isInDestroying_ = false;
    frameNode->onMainTree_ = false;
    imagePattern->ResetImageAndAlt();
    EXPECT_FALSE(imagePattern->isNeedReset_);
}

/**
 * @tc.name: PrepareAnimation001
 * @tc.desc: Prepare Animation
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, PrepareAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    const RefPtr<RenderContext>& renderContext = frameNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);

    /**
     * @tc.steps: step2. expect call IsStatic return false.
     */
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(::testing::Return(false));
    imagePattern->image_ = mockImage;

    /**
     * @tc.steps: step3. call PrepareAnimation.
     * @tc.expected: Returned value is false.
     */
    imagePattern->image_->SetPaintConfig(ImagePaintConfig());
    ImagePaintMethod imagePaintMethod(imagePattern->image_, { .selected = true });
    EXPECT_NE(imagePaintMethod.canvasImage_, nullptr);
    auto canvasImage = imagePaintMethod.canvasImage_;
    EXPECT_NE(canvasImage, nullptr);
    imagePattern->PrepareAnimation(canvasImage);
    bool res = canvasImage->IsStatic();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: ApplyAIModificationsToImage001
 * @tc.desc: call ApplyAIModificationsToImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ApplyAIModificationsToImage001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);

    /**
     * @tc.steps: step2. expect call IsStatic return true.
     */
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(::testing::Return(true));
    imagePattern->image_ = mockImage;

    /**
     * @tc.steps: step3. call ApplyAIModificationsToImage.
     * @tc.expected: Returned value is true.
     */
    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    imagePattern->imageAnalyzerManager_ = imageAnalyzerManager;
    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);
    imagePattern->loadingCtx_ = loadingCtx;
    imagePattern->ApplyAIModificationsToImage();
    EXPECT_TRUE(imagePattern->IsSupportImageAnalyzerFeature());
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(false);
}

/**
 * @tc.name: ApplyAIModificationsToImage002
 * @tc.desc: call ApplyAIModificationsToImage.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ApplyAIModificationsToImage002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    imagePattern->UpdateAnalyzerOverlayLayout();
    imagePattern->EnableAnalyzer(true);
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);

    /**
     * @tc.steps: step2. expect call IsStatic return true.
     */
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    EXPECT_CALL(*mockImage, IsStatic()).WillRepeatedly(::testing::Return(true));
    imagePattern->image_ = mockImage;

    /**
     * @tc.steps: step3. call ApplyAIModificationsToImage.
     * @tc.expected: Returned value is true.
     */
    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(true);
    imagePattern->imageAnalyzerManager_ = imageAnalyzerManager;
    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);
    imagePattern->loadingCtx_ = loadingCtx;
    imagePattern->isPixelMapChanged_ = true;
    imagePattern->ApplyAIModificationsToImage();
    EXPECT_TRUE(imagePattern->IsSupportImageAnalyzerFeature());
    imageAnalyzerManager->SetSupportImageAnalyzerFeature(false);
}

/**
 * @tc.name: UpdateOrientation001
 * @tc.desc: call UpdateOrientation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateOrientation001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    loadingCtx->imageObj_->SetFrameCount(2);
    imagePattern->loadingCtx_ = loadingCtx;

    imagePattern->userOrientation_ = ImageRotateOrientation::RIGHT;
    imagePattern->UpdateOrientation();
    EXPECT_EQ(imagePattern->loadingCtx_->imageObj_->userOrientation_, ImageRotateOrientation::UP);
}

/**
 * @tc.name: UpdateOrientation002
 * @tc.desc: call UpdateOrientation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateOrientation002, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    loadingCtx->imageObj_->SetFrameCount(1);
    imagePattern->loadingCtx_ = loadingCtx;

    imagePattern->userOrientation_ = ImageRotateOrientation::UP;
    imagePattern->UpdateOrientation();
    EXPECT_EQ(imagePattern->joinOrientation_, ImageRotateOrientation::UP);
}

/**
 * @tc.name: UpdateOrientation003
 * @tc.desc: call UpdateOrientation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateOrientation003, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    loadingCtx->imageObj_->SetFrameCount(1);
    imagePattern->loadingCtx_ = loadingCtx;

    imagePattern->userOrientation_ = ImageRotateOrientation::AUTO;
    imagePattern->selfOrientation_ = ImageRotateOrientation::UP;
    imagePattern->UpdateOrientation();
    EXPECT_EQ(imagePattern->joinOrientation_, ImageRotateOrientation::UP);
}

/**
 * @tc.name: UpdateOrientation004
 * @tc.desc: call UpdateOrientation.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateOrientation004, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = AceType::MakeRefPtr<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    ImageSourceInfo sourceInfo("test_src");
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    sourceInfo.isSvg_ = false;
    auto loadingCtx =
        AceType::MakeRefPtr<ImageLoadingContext>(sourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);

    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 100.0f), mockImageData);
    loadingCtx->imageObj_->SetFrameCount(1);
    imagePattern->loadingCtx_ = loadingCtx;

    imagePattern->userOrientation_ = ImageRotateOrientation::RIGHT;
    imagePattern->selfOrientation_ = ImageRotateOrientation::UP;
    imagePattern->UpdateOrientation();
    EXPECT_EQ(imagePattern->joinOrientation_, ImageRotateOrientation::RIGHT);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: call OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnModifyDone001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->imageType_ = ImageType::PIXELMAP_DRAWABLE;
    auto gestureHandler = [](GestureEvent& info) {};
    imagePattern->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>(gestureHandler);

    imagePattern->OnModifyDone();
    EXPECT_EQ(imagePattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: ImagePatternInitOnKeyEvent002
 * @tc.desc: Test Image InitOnKeyEvent method calls.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternInitOnKeyEvent002, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_FIFTEEN));
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);
    imagePattern->keyEventCallback_ = [](const KeyEvent& event) -> bool { return false; };
    imagePattern->InitOnKeyEvent();
    ASSERT_NE(imagePattern->keyEventCallback_, nullptr);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: UpdateOffsetForImageAnalyzerOverlay001
 * @tc.desc: call UpdateOffsetForImageAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateOffsetForImageAnalyzerOverlay001, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    imageAnalyzerManager->SetOverlayCreated(true);
    imagePattern->imageAnalyzerManager_ = imageAnalyzerManager;
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
    imagePattern->isEnableAnalyzer_ = false;

    imagePattern->UpdateOffsetForImageAnalyzerOverlay();
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_->IsOverlayCreated());
    imageAnalyzerManager->SetOverlayCreated(false);
}

/**
 * @tc.name: UpdateOffsetForImageAnalyzerOverlay002
 * @tc.desc: call UpdateOffsetForImageAnalyzerOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateOffsetForImageAnalyzerOverlay002, TestSize.Level1)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto imageAnalyzerManager = std::make_shared<MockImageAnalyzerManager>(frameNode, ImageAnalyzerHolder::IMAGE);
    imageAnalyzerManager->SetOverlayCreated(false);
    imagePattern->imageAnalyzerManager_ = imageAnalyzerManager;
    EXPECT_TRUE(imagePattern->imageAnalyzerManager_);
    imagePattern->isEnableAnalyzer_ = false;

    imagePattern->UpdateOffsetForImageAnalyzerOverlay();
    EXPECT_FALSE(imagePattern->imageAnalyzerManager_->IsOverlayCreated());
}

/**
 * @tc.name: TestImageJsonImageWidth_Height01
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestImageJsonImageWidth_Height01, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be width = 300 , height = 200.
     */
    auto imageWidth = StringUtils::StringToInt(json->GetString("imageWidth"));
    EXPECT_EQ(imageWidth, 300);
    auto imageHeight = StringUtils::StringToInt(json->GetString("imageHeight"));
    EXPECT_EQ(imageHeight, 200);
}

/**
 * @tc.name: OnRecycleTest001
 * @tc.desc: call DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnRecycleTest001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create Image frameNode.
    */
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
    * @tc.steps: step2. set image and create node paint method.
    */
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_ = mockImage;
    imagePattern->CreateNodePaintMethod();
    EXPECT_NE(imagePattern->imagePaintMethod_, nullptr);
    /**
    * @tc.steps: step3. call OnRecycle.
    * @tc.expected: imagePaintMethod_ is nullptr.
    */
    imagePattern->OnRecycle();
    EXPECT_EQ(imagePattern->imagePaintMethod_, nullptr);
}

/**
 * @tc.name: MaskUrl001
 * @tc.desc: Test MaskUrl for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, MaskUrl001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    std::string result = imagePattern->MaskUrl(URL_LENGTH_EQUAL_35);
    EXPECT_EQ(result, RESULT_FOR_URL_LENGTH_EQUAL_35);
}

/**
 * @tc.name: MaskUrl002
 * @tc.desc: Test MaskUrl for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, MaskUrl002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    std::string result = imagePattern->MaskUrl(URL_LENGTH_LESS_THAN_30);
    EXPECT_EQ(result, RESULT_FOR_URL_LENGTH_LESS_THAN_30);
}

/**
 * @tc.name: RecycleImageData006
 * @tc.desc: RecycleImageData006
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, RecycleImageData006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    ImageInfoConfig imageInfoConfig;
    image.Create(imageInfoConfig);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. set isShow false and call RecycleImageData.
     * @tc.expected: Returned value is true.
     */
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
 * @tc.name: ClearReloadFlagsAfterLoad001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ClearReloadFlagsAfterLoad001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call callbacks.
     * @tc.expected:
     */
    imagePattern->isImageReloadNeeded_ = true;
    imagePattern->isOrientationChange_ = true;
    imagePattern->renderedImageInfo_.renderSuccess = true;
    imagePattern->LoadImage(ImageSourceInfo(""), false);
    EXPECT_FALSE(imagePattern->isImageReloadNeeded_);
    EXPECT_FALSE(imagePattern->isOrientationChange_);
    EXPECT_FALSE(imagePattern->renderedImageInfo_.renderSuccess);
}

/**
 * @tc.name: TestImageLoadSuccessEvent001
 * @tc.desc: Test GetNextIndex and AddImageLoadSuccessEvent for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestImageLoadSuccessEvent001, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call AddImageLoadSuccessEvent.
     * @tc.expected:
     */
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    LoadImageSuccessEvent info(300, 200, 400, 500);
    info.loadingStatus_ = 1;
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto completeEvent = [imagePattern](const LoadImageSuccessEvent& info) {
        if (imagePattern) {
            imagePattern->image_ = nullptr;
        }
    };
    eventHub->SetOnComplete(completeEvent);
    imagePattern->OnImageLoadSuccess();

    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ImageCreateTest001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageCreateTest001, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. check isFullyInitializedFromTheme_ is false.
     * @tc.expected: isFullyInitializedFromTheme_ is false.
     */
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
    imagePattern->InitFromThemeIfNeed();
    /**
     * @tc.steps: step3. check isFullyInitializedFromTheme_ is true.
     * @tc.expected: isFullyInitializedFromTheme_ is true.
     */
    EXPECT_TRUE(imagePattern->isFullyInitializedFromTheme_);
    /**
     * @tc.steps: step4. call OnConfigurationUpdate.
     * @tc.expected: isFullyInitializedFromTheme_ is false.
     */
    imagePattern->OnConfigurationUpdate();
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
}

/**
 * @tc.name: TestImageLoadingCtxCreate
 * @tc.desc: Test Create imageLoadingCtx for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestImageLoadingCtxCreate, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto loadingCtx1 = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr), false, true);
    ASSERT_NE(loadingCtx1, nullptr);
    /**
     * @tc.steps: step2. check isSceneBoardWindow_ value.
     * @tc.expected: isSceneBoardWindow_ is true.
     */
    EXPECT_TRUE(loadingCtx1->isSceneBoardWindow_);
    auto loadingCtx2 = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr), false, false);
    ASSERT_NE(loadingCtx2, nullptr);
    /**
     * @tc.steps: step2. check isSceneBoardWindow_ value.
     * @tc.expected: isSceneBoardWindow_ is false.
     */
    EXPECT_FALSE(loadingCtx2->isSceneBoardWindow_);
}

/**
 * @tc.name: GetContentTransitionParam001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, GetContentTransitionParam001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "");
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call GetContentTransitionParam.
     */
    EXPECT_EQ(imagePattern->GetContentTransitionParam(), ContentTransitionType::IDENTITY);
}

/**
 * @tc.name: GetContentTransitionParam002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, GetContentTransitionParam002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "");
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_ = mockImage;
    imagePattern->CreateNodePaintMethod();
    EXPECT_NE(imagePattern->imagePaintMethod_, nullptr);
    EXPECT_NE(imagePattern->contentMod_, nullptr);
    ImageModelNG image;
    image.SetContentTransition(ContentTransitionType::IDENTITY);
    RefPtr<ImageRenderProperty> paintProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. call GetContentTransitionParam.
     */
    EXPECT_EQ(paintProperty->GetContentTransition().value_or(ContentTransitionType::IDENTITY),
        ContentTransitionType::IDENTITY);
    EXPECT_EQ(imagePattern->GetContentTransitionParam(), ContentTransitionType::IDENTITY);
    EXPECT_EQ(imagePattern->contentMod_->GetContentTransitionParam(), ContentTransitionType::IDENTITY);
}

/**
 * @tc.name: GetContentTransitionParam003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, GetContentTransitionParam003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "");
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);
    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_ = mockImage;
    imagePattern->CreateNodePaintMethod();
    EXPECT_NE(imagePattern->imagePaintMethod_, nullptr);
    EXPECT_NE(imagePattern->contentMod_, nullptr);
    ImageModelNG::SetContentTransition(AceType::RawPtr(frameNode), ContentTransitionType::OPACITY);

    /**
     * @tc.steps: step2. call GetContentTransitionParam.
     */
    EXPECT_EQ(ImageModelNG::GetContentTransition(AceType::RawPtr(frameNode)), ContentTransitionType::OPACITY);
    EXPECT_EQ(imagePattern->GetContentTransitionParam(), ContentTransitionType::IDENTITY);
    EXPECT_EQ(imagePattern->contentMod_->GetContentTransitionParam(), ContentTransitionType::IDENTITY);
}

/**
 * @tc.name: TestImageOnLoadSuccess001
 * @tc.desc: Test OnImageLoadSuccess for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestImageOnLoadSuccess001, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call AddImageLoadSuccessEvent.
     * @tc.expected:
     */
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    LoadImageSuccessEvent info(300, 200, 400, 500);
    info.loadingStatus_ = 1;
    auto eventHub = frameNode->GetEventHub<ImageEventHub>();
    EXPECT_NE(eventHub, nullptr);
    auto completeEvent = [imagePattern](const LoadImageSuccessEvent& info) {
        if (imagePattern) {
            imagePattern->image_ = nullptr;
        }
    };
    eventHub->SetOnComplete(completeEvent);
    imagePattern->OnImageLoadSuccess();

    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: altErrorCallback001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, altErrorCallback001, TestSize.Level0)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);

    frameNode->isActive_ = true;

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageModelNG image;
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    auto altImageSourceInfo = imageLayoutProperty->GetAltError().value_or(ImageSourceInfo(""));
    imagePattern->LoadAltErrorImage(altImageSourceInfo);

    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() != nullptr);
    auto callback1 = imagePattern->CreateDataReadyCallbackForAltError();
    callback1(altImageSourceInfo);

    ImageSourceInfo sourceInfo("testmsg");
    imagePattern->LoadAltErrorImage(ImageSourceInfo { PNG_IMAGE });
    auto callback2 = imagePattern->CreateDataReadyCallbackForAltError();
    callback2(sourceInfo);

    auto callback3 = imagePattern->CreateLoadSuccessCallbackForAltError();
    callback3(altImageSourceInfo);

    imagePattern->LoadAltErrorImage(ImageSourceInfo { PNG_IMAGE });
    callback3(sourceInfo);
    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() != nullptr);
}

/**
 * @tc.name: altErrorCallback002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, altErrorCallback002, TestSize.Level0)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->isActive_ = true;

    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    ImageModelNG image;
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    auto altImageSourceInfo = imageLayoutProperty->GetAltError().value_or(ImageSourceInfo(""));
    std::string errorMsg = "erormsg";
    ImageErrorInfo errorInfo;
    auto callback1 = imagePattern->CreateLoadFailCallbackForAltError();
    callback1(altImageSourceInfo, errorMsg, errorInfo);

    EXPECT_TRUE(imagePattern->CreateNodePaintMethod() != nullptr);

    ImageSourceInfo sourceInfo("testmsg");
    auto callback2 = imagePattern->CreateLoadFailCallbackForAltError();
    callback2(sourceInfo, errorMsg, errorInfo);
}

/**
 * @tc.name: ImagePatternAltError001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternAltError001, TestSize.Level0)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageModelNG image;
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    frameNode->GetGeometryNode()->SetContentSize(SizeF());
    auto altImageSourceInfo = imageLayoutProperty->GetAltError().value_or(ImageSourceInfo(""));
    imagePattern->LoadAltErrorImage(altImageSourceInfo);
    imagePattern->StartDecoding(SizeF());
    EXPECT_NE(frameNode->GetGeometryNode()->GetContent().get(), nullptr);
}

/**
 * @tc.name: ImagePatternAltError002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternAltError002, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageModelNG image;
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    auto altImageSourceInfo = imageLayoutProperty->GetAltError().value_or(ImageSourceInfo(""));
    imagePattern->LoadAltErrorImage(altImageSourceInfo);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(WIDTH, HEIGHT));
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, imageLayoutProperty);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(nullptr);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    layoutWrapper->skipMeasureContent_ = false;
    DirtySwapConfig config;
    config.skipMeasure = false;
    imagePattern->altErrorCtx_ =
        AceType::MakeRefPtr<ImageLoadingContext>(altImageSourceInfo, LoadNotifier(nullptr, nullptr, nullptr), true);
    imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    imagePattern->altErrorImage_ = imagePattern->altErrorCtx_->MoveCanvasImage();
    EXPECT_NE(imagePattern->altErrorImage_, nullptr);
    auto renderProp = frameNode->GetPaintProperty<ImageRenderProperty>();
    ImageResizableSlice imageResizableSlice {
        .left = Dimension(1),
    };
    image.SetResizableSlice(imageResizableSlice);
    EXPECT_TRUE(imagePattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
    imagePattern->LoadImageDataIfNeed();
}

/**
 * @tc.name: ImagePatternAltError003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternAltError003, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageModelNG image;
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->GetAltError();
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    auto altImageSourceInfo = imageLayoutProperty->GetAltError().value_or(ImageSourceInfo(""));
    image.SetAltError(ImageSourceInfo { ALT_SRC_URL });
    imagePattern->LoadAltErrorImage(altImageSourceInfo);
    imagePattern->altErrorImage_ = imagePattern->altErrorCtx_->MoveCanvasImage();
    imagePattern->loadFailed_ = true;
    EXPECT_EQ(frameNode->GetGeometryNode()->GetContent().get(), nullptr);
}

/**
 * @tc.name: ImagePatternAltError004
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternAltError004, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(pattern, nullptr);

    auto imageLayoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize.width_ = 100.0;
    layoutConstraint.parentIdealSize.height_ = 300.0;

    LayoutPolicyProperty layoutPolicyProperty;
    layoutPolicyProperty.heightLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;
    layoutPolicyProperty.widthLayoutPolicy_ = LayoutCalPolicy::NO_MATCH;

    imageLayoutProperty->layoutPolicy_ = layoutPolicyProperty;

    imageLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    auto altErrorCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(altErrorCtx_, nullptr);
    pattern->altErrorCtx_ = altErrorCtx_;

    EXPECT_FALSE(layoutConstraint.selfIdealSize.IsValid());
    EXPECT_TRUE(layoutConstraint.parentIdealSize.IsValid());

    auto imageSize = pattern->GetImageSizeForMeasure();
    EXPECT_EQ(imageSize->Width(), IMAGE_SOURCESIZE_WIDTH);
    EXPECT_EQ(imageSize->Height(), IMAGE_SOURCESIZE_HEIGHT);
}

/**
 * @tc.name: ImagePatternAltError005
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternAltError005, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();

    ImageModelNG image;
    image.SetAltError(ImageSourceInfo { RESOURCE_URL });
    imagePattern->OnConfigurationUpdate();

    image.SetAlt(ImageSourceInfo { RESOURCE_URL });
    imagePattern->OnConfigurationUpdate();

    image.SetAltPlaceholder(ImageSourceInfo { RESOURCE_URL });
    imagePattern->OnConfigurationUpdate();

    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
}

/**
 * @tc.name: ImageConfigurationChange001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImageConfigurationChange001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    ImageModelNG image;
    ImageInfoConfig imageInfoConfig;
    image.Create(imageInfoConfig);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. check isFullyInitializedFromTheme_ is false.
     * @tc.expected: isFullyInitializedFromTheme_ is false.
     */
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
    imagePattern->InitFromThemeIfNeed();
    EXPECT_TRUE(imagePattern->isFullyInitializedFromTheme_);
    imagePattern->OnConfigurationUpdate();
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
}

/**
 * @tc.name: TestImagePatternLoadImageTest001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestImagePatternLoadImageTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    auto frameNode = CreateImageNode("", "", nullptr);
    ;
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    /**
     * @tc.steps: step2. call callbacks.
     * @tc.expected:
     */
    imagePattern->isImageReloadNeeded_ = true;
    imagePattern->isOrientationChange_ = true;
    imagePattern->renderedImageInfo_.renderSuccess = true;
    imagePattern->LoadImage(ImageSourceInfo(""), false);
    EXPECT_FALSE(imagePattern->isImageReloadNeeded_);
    EXPECT_FALSE(imagePattern->isOrientationChange_);
    EXPECT_FALSE(imagePattern->renderedImageInfo_.renderSuccess);
}

/**
 * @tc.name: ImagePatternLoadImageDataIfNeed001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternLoadImageDataIfNeed001, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageModelNG image;
    auto imageLayoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    auto altImageSourceInfo = imageLayoutProperty->GetAltError().value_or(ImageSourceInfo(""));
    imagePattern->LoadAltErrorImage(altImageSourceInfo);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    imagePattern->LoadImageDataIfNeed();
}

/**
 * @tc.name: TestImageSourceInfoGetSrcType001
 * @tc.desc: Verify srcType is correctly mapped from ImageSourceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, TestImageSourceInfoGetSrcType001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageSourceInfo info("http://example.com/test.png");
    auto imageDfxConfig = imagePattern->CreateImageDfxConfig(info);
    EXPECT_EQ(imageDfxConfig.srcType_, static_cast<int32_t>(info.GetSrcType()));
}

/**
 * @tc.name: RecycleImageData005
 * @tc.desc: RecycleImageData005
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, RecycleImageData005, TestSize.Level0)
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
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
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
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    EXPECT_FALSE(imagePattern->RecycleImageData());
}

/**
 * @tc.name: ImagePatternOnThemeScopeUpdate001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ImagePatternOnThemeScopeUpdate001, TestSize.Level0)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isFullyInitializedFromTheme_ = true;
    int32_t themeScopedId = 1;
    auto result = imagePattern->OnThemeScopeUpdate(themeScopedId);
    ASSERT_FALSE(imagePattern->isFullyInitializedFromTheme_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDetachFromFrameNode001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->InitCopy();
    ASSERT_NE(imagePattern->mouseEvent_, nullptr);
    MouseInfo info;
    info.SetButton(MouseButton::LEFT_BUTTON);
    info.SetAction(MouseAction::PRESS);
    imagePattern->mouseEvent_->GetOnMouseEventFunc()(info);
    
    imagePattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    EXPECT_FALSE(imagePattern->isSelected_);
}

/**
 * @tc.name: OnReuse001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnReuse001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    
    imagePattern->OnReuse();
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: CreateModifier001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreateModifier001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    
    imagePattern->CreateModifier();
    EXPECT_NE(imagePattern->contentMod_, nullptr);
    EXPECT_NE(imagePattern->overlayMod_, nullptr);
    EXPECT_NE(imagePattern->imagePaintMethod_, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreateNodePaintMethod001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto paintMethod = imagePattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    EXPECT_EQ(paintMethod, imagePattern->imagePaintMethod_);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreateNodePaintMethod002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    EXPECT_EQ(imagePattern->contentMod_, nullptr);
    EXPECT_EQ(imagePattern->overlayMod_, nullptr);

    imagePattern->CreateNodePaintMethod();
    EXPECT_NE(imagePattern->contentMod_, nullptr);
    EXPECT_NE(imagePattern->overlayMod_, nullptr);
    EXPECT_NE(imagePattern->imagePaintMethod_, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreateNodePaintMethod003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    auto mockImage = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->image_ = mockImage;
    imagePattern->loadFailed_ = false;

    auto paintMethod = imagePattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    EXPECT_EQ(imagePattern->image_, mockImage);
}

/**
 * @tc.name: HandleSrcForMemoryName001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, HandleSrcForMemoryName001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 200.0f), mockImageData);
    imagePattern->loadingCtx_ = loadingCtx;

    std::string url = URL_LENGTH_LESS_THAN_30;
    std::string result = imagePattern->HandleSrcForMemoryName(url);
    std::string expected = "100x200-" + imagePattern->MaskUrl(url);
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: HandleSrcForMemoryName002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, HandleSrcForMemoryName002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(300.0f, 400.0f), mockImageData);
    imagePattern->loadingCtx_ = loadingCtx;

    std::string url = URL_LENGTH_EQUAL_35;
    std::string result = imagePattern->HandleSrcForMemoryName(url);
    std::string expected = "300x400-" + imagePattern->MaskUrl(url);
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: HandleSrcForMemoryName003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, HandleSrcForMemoryName003, TestSize.Level0)
{
    const int32_t KERNEL_MAX_LENGTH_EXCEPT_OTHER = 245;
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(400.0f, 500.0f), mockImageData);
    imagePattern->loadingCtx_ = loadingCtx;

    std::string url;
    for (size_t i = 0; i <= 7; i++) {
        url += RESULT_FOR_URL_LENGTH_EQUAL_35;
    }
    std::string result = imagePattern->HandleSrcForMemoryName(url);
    url = url.substr(url.size() - KERNEL_MAX_LENGTH_EXCEPT_OTHER);
    std::string expected = "400x500-" + imagePattern->MaskUrl(url);
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: PreprocessYUVDecodeFormat001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, PreprocessYUVDecodeFormat001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 200.0f), mockImageData);
    imagePattern->loadingCtx_ = loadingCtx;

    SystemProperties::isOpenYuvDecode_ = false;
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsYUVDecode(true);
    imagePattern->PreprocessYUVDecodeFormat(frameNode);
    EXPECT_FALSE(loadingCtx->imageObj_->GetIsYUVDecode());
}

/**
 * @tc.name: PreprocessYUVDecodeFormat002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, PreprocessYUVDecodeFormat002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 200.0f), mockImageData);
    imagePattern->loadingCtx_ = loadingCtx;

    SystemProperties::isOpenYuvDecode_ = true;
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsYUVDecode(true);
    imagePattern->PreprocessYUVDecodeFormat(frameNode);
    EXPECT_TRUE(loadingCtx->imageObj_->GetIsYUVDecode());
}

/**
 * @tc.name: PreprocessYUVDecodeFormat003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, PreprocessYUVDecodeFormat003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    auto mockImageData = AceType::MakeRefPtr<MockImageData>();
    ImageSourceInfo sourceInfo(IMAGE_SRC_URL);
    loadingCtx->imageObj_ = AceType::MakeRefPtr<MockImageObject>(sourceInfo, SizeF(100.0f, 200.0f), mockImageData);
    imagePattern->loadingCtx_ = loadingCtx;

    SystemProperties::isOpenYuvDecode_ = true;
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsYUVDecode(false);
    imagePattern->PreprocessYUVDecodeFormat(frameNode);
    EXPECT_FALSE(loadingCtx->imageObj_->GetIsYUVDecode());
}

/**
 * @tc.name: InitializeStatus001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitializeStatus001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    DrawableDescriptorLoadResult result;
    result.imageWidth_ = 200;
    result.imageHeight_ = 300;
    result.errorCode = 0;
    imagePattern->InitializeStatus(result);
    EXPECT_EQ(imagePattern->imageSize_.Width(), 200.0f);
    EXPECT_EQ(imagePattern->imageSize_.Height(), 300.0f);
}

/**
 * @tc.name: InitializeStatus002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitializeStatus002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->isMeasured_ = true;
    DrawableDescriptorLoadResult result;
    result.imageWidth_ = 150;
    result.imageHeight_ = 250;
    result.errorCode = 0;
    imagePattern->InitializeStatus(result);
    EXPECT_FALSE(imagePattern->isMeasured_);
    EXPECT_EQ(imagePattern->imageSize_.Width(), 150.0f);
    EXPECT_EQ(imagePattern->imageSize_.Height(), 250.0f);
}

/**
 * @tc.name: InitializeStatus003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitializeStatus003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    DrawableDescriptorLoadResult result;
    result.imageWidth_ = 1920;
    result.imageHeight_ = 1080;
    result.errorCode = 0;
    imagePattern->InitializeStatus(result);
    EXPECT_EQ(imagePattern->imageSize_.Width(), 1920.0f);
    EXPECT_EQ(imagePattern->imageSize_.Height(), 1080.0f);
    result.imageWidth_ = 50;
    result.imageHeight_ = 50;
    result.errorCode = 0;
    imagePattern->InitializeStatus(result);
    EXPECT_EQ(imagePattern->imageSize_.Width(), 50.0f);
    EXPECT_EQ(imagePattern->imageSize_.Height(), 50.0f);
}

/**
 * @tc.name: SetFrameOffsetForOverlayNode001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetFrameOffsetForOverlayNode001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->SetFrameOffsetForOverlayNode();
    EXPECT_NE(frameNode, nullptr);
    EXPECT_NE(imagePattern, nullptr);
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnWindowHide001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isRecycledImage_ = true;
    SystemProperties::recycleImageEnabled_ = true;

    imagePattern->OnWindowHide();
    EXPECT_TRUE(imagePattern->isRecycledImage_);
}

/**
 * @tc.name: OnWindowHide002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnWindowHide002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_FALSE(imagePattern->isRecycledImage_);
    SystemProperties::recycleImageEnabled_ = false;
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->loadingCtx_ = loadingCtx;
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();

    imagePattern->OnWindowHide();
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    EXPECT_FALSE(imagePattern->isRecycledImage_);
}

/**
 * @tc.name: OnWindowHide003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnWindowHide003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isRecycledImage_ = true;
    SystemProperties::recycleImageEnabled_ = true;
    auto loadingCtx = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->loadingCtx_ = loadingCtx;

    imagePattern->OnWindowHide();
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
    EXPECT_TRUE(imagePattern->isRecycledImage_);
}

/**
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDetachFromMainTree001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isNeedReset_ = false;

    imagePattern->OnDetachFromMainTree();
    EXPECT_FALSE(imagePattern->isNeedReset_);
}

/**
 * @tc.name: OnDetachFromMainTree002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDetachFromMainTree002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    frameNode->isInDestroying_ = true;
    imagePattern->isNeedReset_ = true;
    imagePattern->ResetImageAndAlt();
    EXPECT_TRUE(imagePattern->isNeedReset_);
    imagePattern->OnDetachFromMainTree();
    EXPECT_FALSE(imagePattern->isNeedReset_);
}

/**
 * @tc.name: OnDpiConfigurationUpdate001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDpiConfigurationUpdate001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isFullyInitializedFromTheme_ = true;
    EXPECT_TRUE(imagePattern->isFullyInitializedFromTheme_);
    imagePattern->OnDpiConfigurationUpdate();
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
}

/**
 * @tc.name: OnDpiConfigurationUpdate002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnDpiConfigurationUpdate002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    ASSERT_NE(imagePattern->loadingCtx_, nullptr);

    imagePattern->isFullyInitializedFromTheme_ = true;
    EXPECT_TRUE(imagePattern->isFullyInitializedFromTheme_);
    imagePattern->OnDpiConfigurationUpdate();
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnColorConfigurationUpdate001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->isFullyInitializedFromTheme_ = true;
    EXPECT_TRUE(imagePattern->isFullyInitializedFromTheme_);

    imagePattern->OnColorConfigurationUpdate();
    EXPECT_FALSE(imagePattern->isFullyInitializedFromTheme_);
}

/**
 * @tc.name: GetImageRepeatStr001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, GetImageRepeatStr001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    ImageRepeat value = static_cast<ImageRepeat>(100);
    std::string result = imagePattern->GetImageRepeatStr(value);
    EXPECT_EQ(result, "NO_REPEAT");

    value = ImageRepeat::NO_REPEAT;
    result = imagePattern->GetImageRepeatStr(value);
    EXPECT_EQ(result, "NO_REPEAT");

    value = ImageRepeat::REPEAT;
    result = imagePattern->GetImageRepeatStr(value);
    EXPECT_EQ(result, "REPEAT_XY");

    value = ImageRepeat::REPEAT_X;
    result = imagePattern->GetImageRepeatStr(value);
    EXPECT_EQ(result, "REPEAT_X");

    value = ImageRepeat::REPEAT_Y;
    result = imagePattern->GetImageRepeatStr(value);
    EXPECT_EQ(result, "REPEAT_Y");
}

/**
 * @tc.name: UpdateAnalyzerOverlay001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateAnalyzerOverlay001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->imageAnalyzerManager_ = nullptr;
    imagePattern->UpdateAnalyzerOverlay();
    EXPECT_EQ(imagePattern->imageAnalyzerManager_, nullptr);
}

/**
 * @tc.name: UpdateAnalyzerOverlay002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateAnalyzerOverlay002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->EnableAnalyzer(true);
    ASSERT_NE(imagePattern->imageAnalyzerManager_, nullptr);
    imagePattern->isEnableAnalyzer_ = false;
    imagePattern->UpdateAnalyzerOverlay();
    EXPECT_FALSE(imagePattern->IsSupportImageAnalyzerFeature());
}

/**
 * @tc.name: UpdateAnalyzerOverlay003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateAnalyzerOverlay003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->EnableAnalyzer(true);
    ASSERT_NE(imagePattern->imageAnalyzerManager_, nullptr);
    imagePattern->image_ = nullptr;
    imagePattern->UpdateAnalyzerOverlay();
    EXPECT_FALSE(imagePattern->IsSupportImageAnalyzerFeature());
}

/**
 * @tc.name: UpdateAnalyzerOverlay004
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateAnalyzerOverlay004, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->EnableAnalyzer(true);
    ASSERT_NE(imagePattern->imageAnalyzerManager_, nullptr);
    imagePattern->loadingCtx_ = nullptr;
    imagePattern->UpdateAnalyzerOverlay();
    EXPECT_FALSE(imagePattern->IsSupportImageAnalyzerFeature());
}

/**
 * @tc.name: AddPixelMapToUiManager001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AddPixelMapToUiManager001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->image_ = nullptr;
    imagePattern->AddPixelMapToUiManager();
    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: AddPixelMapToUiManager002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, AddPixelMapToUiManager002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    ASSERT_NE(imagePattern->image_, nullptr);
    imagePattern->AddPixelMapToUiManager();
    EXPECT_NE(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ResetAltImageError001
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetAltImageError001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->altErrorImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altErrorCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    ASSERT_NE(imagePattern->altErrorImage_, nullptr);
    ASSERT_NE(imagePattern->altErrorCtx_, nullptr);
    imagePattern->ResetAltImageError();
    EXPECT_EQ(imagePattern->altErrorImage_, nullptr);
    EXPECT_EQ(imagePattern->altErrorCtx_, nullptr);
}

/**
 * @tc.name: ResetAltImageError002
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetAltImageError002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = nullptr;
    imagePattern->altErrorImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altErrorCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    imagePattern->ResetAltImageError();
    EXPECT_EQ(imagePattern->altErrorImage_, nullptr);
    EXPECT_EQ(imagePattern->altErrorCtx_, nullptr);
    EXPECT_EQ(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ResetAltImageError003
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetAltImageError003, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->image_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altErrorImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altErrorCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    ASSERT_NE(imagePattern->image_, nullptr);
    ASSERT_NE(imagePattern->altErrorImage_, nullptr);
    ASSERT_NE(imagePattern->altErrorCtx_, nullptr);
    imagePattern->ResetAltImageError();
    EXPECT_EQ(imagePattern->altErrorImage_, nullptr);
    EXPECT_EQ(imagePattern->altErrorCtx_, nullptr);
    EXPECT_NE(imagePattern->image_, nullptr);
}

/**
 * @tc.name: ResetAltImageError004
 * @tc.desc: Test function for ImagePattern.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ResetAltImageError004, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->altErrorImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altErrorCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);
    ASSERT_NE(imagePattern->altErrorImage_, nullptr);
    ASSERT_NE(imagePattern->altErrorCtx_, nullptr);
    imagePattern->ResetAltImageError();
    EXPECT_EQ(imagePattern->altErrorImage_, nullptr);
    EXPECT_EQ(imagePattern->altErrorCtx_, nullptr);
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: ClearAltData001
 * @tc.desc: Test ClearAltData function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, ClearAltData001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Set alt data
    imagePattern->altLoadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL), LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->altImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altDstRect_ = std::make_unique<RectF>();
    imagePattern->altSrcRect_ = std::make_unique<RectF>();
    imagePattern->altErrorCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL), LoadNotifier(nullptr, nullptr, nullptr));
    imagePattern->altErrorImage_ = AceType::MakeRefPtr<MockCanvasImage>();
    imagePattern->altErrorDstRect_ = std::make_unique<RectF>();
    imagePattern->altErrorSrcRect_ = std::make_unique<RectF>();

    // Call ClearAltData
    imagePattern->ClearAltData();

    // Verify all alt data is cleared
    EXPECT_EQ(imagePattern->altLoadingCtx_, nullptr);
    EXPECT_EQ(imagePattern->altImage_, nullptr);
    EXPECT_EQ(imagePattern->altDstRect_, nullptr);
    EXPECT_EQ(imagePattern->altSrcRect_, nullptr);
    EXPECT_EQ(imagePattern->altErrorCtx_, nullptr);
    EXPECT_EQ(imagePattern->altErrorImage_, nullptr);
    EXPECT_EQ(imagePattern->altErrorDstRect_, nullptr);
    EXPECT_EQ(imagePattern->altErrorSrcRect_, nullptr);
}

/**
 * @tc.name: CalAndUpdateSelectOverlay001
 * @tc.desc: Test CalAndUpdateSelectOverlay function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CalAndUpdateSelectOverlay001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Open select overlay to create selectOverlay_
    imagePattern->OpenSelectOverlay();

    ASSERT_NE(imagePattern->selectOverlay_, nullptr);

    // Call CalAndUpdateSelectOverlay - should not crash
    imagePattern->CalAndUpdateSelectOverlay();

    EXPECT_NE(imagePattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: SetPixelMapMemoryName001
 * @tc.desc: Test SetPixelMapMemoryName with inspector id
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetPixelMapMemoryName001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Set inspector id
    frameNode->UpdateInspectorId("test_image_id");

    // Create mock pixel map
    RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();

    // Call SetPixelMapMemoryName
    bool result = imagePattern->SetPixelMapMemoryName(pixelMap);

    EXPECT_TRUE(result);
    EXPECT_TRUE(imagePattern->hasSetPixelMapMemoryName_);
}

/**
 * @tc.name: SetPixelMapMemoryName002
 * @tc.desc: Test SetPixelMapMemoryName without inspector id
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, SetPixelMapMemoryName002, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Create loading context with source info
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    // Create mock pixel map
    RefPtr<PixelMap> pixelMap = AceType::MakeRefPtr<MockPixelMap>();

    // Call SetPixelMapMemoryName - should return false since no inspector id
    bool result = imagePattern->SetPixelMapMemoryName(pixelMap);

    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckIfNeedLayout001
 * @tc.desc: Test CheckIfNeedLayout returns true when content is null
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CheckIfNeedLayout001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // By default, content might be null when creating a node
    // Call CheckIfNeedLayout
    bool result = imagePattern->CheckIfNeedLayout();

    // Should return true if content is null or no layout constraint
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnImageDataReady001
 * @tc.desc: Test OnImageDataReady function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, OnImageDataReady001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Create loading context
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);

    // Call OnImageDataReady - should not crash
    imagePattern->OnImageDataReady();
}

/**
 * @tc.name: StartDecoding001
 * @tc.desc: Test StartDecoding function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, StartDecoding001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Create loading context
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL, IMAGE_SOURCEINFO_WIDTH, IMAGE_SOURCEINFO_HEIGHT),
        LoadNotifier(nullptr, nullptr, nullptr));

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);

    // Call StartDecoding with valid size
    SizeF dstSize(100.0f, 100.0f);
    imagePattern->StartDecoding(dstSize);

    // Should not crash
    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: CreateObscuredImage001
 * @tc.desc: Test CreateObscuredImage function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, CreateObscuredImage001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Set layout constraint with valid size
    auto layoutProperty = imagePattern->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize = OptionalSize(100.0f, 100.0f);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);

    // Set obscured reasons
    std::vector<ObscuredReasons> reasons = { ObscuredReasons::PLACEHOLDER };
    frameNode->GetRenderContext()->UpdateObscured(reasons);

    // Call CreateObscuredImage - should not crash
    imagePattern->CreateObscuredImage();
}

/**
 * @tc.name: LoadAltImage001
 * @tc.desc: Test LoadAltImage function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, LoadAltImage001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Enable alt loading
    imagePattern->needLoadAlt_ = true;

    // Call LoadAltImage
    ImageSourceInfo altSourceInfo(ALT_SRC_URL);
    imagePattern->LoadAltImage(altSourceInfo);

    // Should create alt loading context
    EXPECT_NE(imagePattern->altLoadingCtx_, nullptr);
}

/**
 * @tc.name: UpdateSvgSmoothEdgeValue001
 * @tc.desc: Test UpdateSvgSmoothEdgeValue function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, UpdateSvgSmoothEdgeValue001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Create loading context
    imagePattern->loadingCtx_ = AceType::MakeRefPtr<ImageLoadingContext>(
        ImageSourceInfo(IMAGE_SRC_URL), LoadNotifier(nullptr, nullptr, nullptr));

    ASSERT_NE(imagePattern->loadingCtx_, nullptr);

    // Call UpdateSvgSmoothEdgeValue - should not crash
    imagePattern->UpdateSvgSmoothEdgeValue();

    EXPECT_NE(imagePattern->loadingCtx_, nullptr);
}

/**
 * @tc.name: InitFromThemeIfNeed001
 * @tc.desc: Test InitFromThemeIfNeed function
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestNg, InitFromThemeIfNeed001, TestSize.Level0)
{
    auto frameNode = CreateImageNode("", "", nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    // Call InitFromThemeIfNeed - should not crash
    imagePattern->InitFromThemeIfNeed();
}

} // namespace OHOS::Ace::NG