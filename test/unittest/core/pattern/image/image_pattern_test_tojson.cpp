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
#include "image_base.h"

#include "base/image/image_defines.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class ImagePatternTestToJson : public ImageBases {};

/**
 * @tc.name: TestImageDefaultJson
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageDefaultJson, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    std::string src = "https://test";
    std::string alt = "https://test";
    auto frameNode = CreateImageNode(src, alt, nullptr);
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the alt value.
     * @tc.expected: it should be the same with alt.
     */
    EXPECT_EQ(json->GetString("alt"), alt);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Cover");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.NoRepeat");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("interpolation"), "ImageInterpolation.None");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("renderMode"), "ImageRenderMode.Original");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("sourceSize"), "[0.00 x 0.00]");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("matchTextDirection"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("fitOriginalSize"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("fillColor"), "#FF000000");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("autoResize"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("syncLoad"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.None");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("colorFilter"), "");

    /**
     * @tc.steps: check the key value.Without init.
     * @tc.expected: it should be false.
     */
    EXPECT_EQ(json->GetString("draggable"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("enableAnalyzer"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetBool("privacySensitive"), false);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("dynamicRangeMode"), "STANDARD");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("orientation"), "1");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetDouble("hdrBrightness"), 1.0);
}

/**
 * @tc.name: TestImageInvalidJson
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageInvalidJson, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create Image frameNode.
     */
    std::string src = "https://test";
    RefPtr<PixelMap> pixMap = nullptr;
    ImageModelNG image;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(src);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    image.Create(imageInfoConfig, pixMap);
    image.SetSyncMode(false);
    image.SetDraggable(false);
    image.EnableAnalyzer(false);
    image.SetFitOriginSize(false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);
    GTEST_LOG_(INFO) << json->ToString();

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Cover");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.NoRepeat");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("interpolation"), "ImageInterpolation.None");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("renderMode"), "ImageRenderMode.Original");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("sourceSize"), "[0.00 x 0.00]");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("matchTextDirection"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("fitOriginalSize"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("fillColor"), "#FF000000");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("autoResize"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("syncLoad"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.None");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("colorFilter"), "");

    /**
     * @tc.steps: check the key value.Without init.
     * @tc.expected: it should be false.
     */
    EXPECT_EQ(json->GetString("draggable"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("enableAnalyzer"), "false");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetBool("privacySensitive"), false);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("dynamicRangeMode"), "STANDARD");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("orientation"), "1");

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetDouble("hdrBrightness"), 1.0);
}

/**
 * @tc.name: TestImageJsonObjectFitContain
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonObjectFitContain, TestSize.Level0)
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
    image.SetImageFit(ImageFit::CONTAIN);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Contain");
}

/**
 * @tc.name: TestImageJsonObjectFitFill
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonObjectFitFill, TestSize.Level0)
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
    image.SetImageFit(ImageFit::FILL);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.Fill");
}


/**
 * @tc.name: TestImageJsonObjectFitScaleDown
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonObjectFitScaleDown, TestSize.Level0)
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
    image.SetImageFit(ImageFit::SCALE_DOWN);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be the default value.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.ScaleDown");
}

/**
 * @tc.name: TestImageJsonObjectFitBOTTOM_START
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonObjectFitBottomStart, TestSize.Level0)
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
    image.SetImageFit(ImageFit::BOTTOM_START);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be BOTTOM_START.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.BOTTOM_START");
}

/**
 * @tc.name: TestImageJsonObjectFitBottomEnd
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonObjectFitBottomEnd, TestSize.Level0)
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
    image.SetImageFit(ImageFit::BOTTOM_END);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be BOTTOM_START.
     */
    EXPECT_EQ(json->GetString("objectFit"), "ImageFit.BOTTOM_END");
}

/**
 * @tc.name: TestImageJsonImageRepeatX
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonImageRepeatX, TestSize.Level0)
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
    image.SetImageRepeat(ImageRepeat::REPEAT_X);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be REPEAT_X.
     */
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.X");
}

/**
 * @tc.name: TestImageJsonImageRepeatY
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonImageRepeatY, TestSize.Level0)
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
    image.SetImageRepeat(ImageRepeat::REPEAT_Y);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be REPEAT_Y.
     */
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.Y");
}

/**
 * @tc.name: TestImageJsonImageRepeatXY
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonImageRepeatXY, TestSize.Level0)
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
    image.SetImageRepeat(ImageRepeat::REPEAT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be REPEAT_XY.
     */
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.XY");
}

/**
 * @tc.name: TestImageJsonImageRepeatNO
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonImageRepeatNO, TestSize.Level0)
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
    image.SetImageRepeat(ImageRepeat::NO_REPEAT);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be NO_REPEAT.
     */
    EXPECT_EQ(json->GetString("objectRepeat"), "ImageRepeat.NoRepeat");
}

/**
 * @tc.name: TestImageJsonRenderModeOriginal
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonRenderModeOriginal, TestSize.Level0)
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
    image.SetImageRenderMode(ImageRenderMode::ORIGINAL);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be ImageRenderMode::Original.
     */
    EXPECT_EQ(json->GetString("renderMode"), "ImageRenderMode.Original");
}

/**
 * @tc.name: TestImageJsonRenderModeTemplate
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonRenderModeTemplate, TestSize.Level0)
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
    image.SetImageRenderMode(ImageRenderMode::TEMPLATE);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto imagePattern = frameNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be ImageRenderMode::Template.
     */
    EXPECT_EQ(json->GetString("renderMode"), "ImageRenderMode.Template");
}


/**
 * @tc.name: TestImageJsonfillColor01
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonfillColor01, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);

    image.SetImageFill(frameNode, Color::BLUE);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be #FF0000FF.
     */
    EXPECT_EQ(json->GetString("fillColor"), "#FF0000FF");
}


/**
 * @tc.name: TestImageJsonfillColor02
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonfillColor02, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);

    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be default #FF000000.
     */
    EXPECT_EQ(json->GetString("fillColor"), "#FF000000");
}


/**
 * @tc.name: TestImageJsonfillColor03
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonfillColor03, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetImageFill(frameNode, Color::RED);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be default #FFFF0000.
     */
    EXPECT_EQ(json->GetString("fillColor"), "#FFFF0000");
}

/**
 * @tc.name: TestImageJsonfillColor04
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonfillColor04, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetImageFill(frameNode, Color::GREEN);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be default #FF00FF00.
     */
    EXPECT_EQ(json->GetString("fillColor"), "#FF00FF00");
}

/**
 * @tc.name: TestImageJsonCopyOption01
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonCopyOption01, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetCopyOption(CopyOptions::None);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be None.
     */
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.None");
}

/**
 * @tc.name: TestImageJsonCopyOption02
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonCopyOption02, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetCopyOption(CopyOptions::InApp);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be InApp.
     */
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.InApp");
}

/**
 * @tc.name: TestImageJsonCopyOption03
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonCopyOption03, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetCopyOption(CopyOptions::Local);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be Local.
     */
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.Local");
}

/**
 * @tc.name: TestImageJsonCopyOption04
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonCopyOption04, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetCopyOption(CopyOptions::Distributed);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be Distributed.
     */
    EXPECT_EQ(json->GetString("copyOption"), "CopyOptions.Distributed");
}

/**
 * @tc.name: TestImageJsonHdrBrightless001
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonHdrBrightless001, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetHdrBrightness(0.1);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be Distributed.
     */
    EXPECT_TRUE(NearEqual(json->GetDouble("hdrBrightness"), 0.1));
}

/**
 * @tc.name: TestImageJsonHdrBrightless002
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonHdrBrightless002, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetHdrBrightness(0.2);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be 0.2.
     */
    EXPECT_TRUE(NearEqual(json->GetDouble("hdrBrightness"), 0.2));
}

/**
 * @tc.name: TestImageJsonHdrBrightless003
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonHdrBrightless003, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    image.SetHdrBrightness(1.0);
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be 1.0.
     */
    EXPECT_TRUE(NearEqual(json->GetDouble("hdrBrightness"), 1.0));
}

/**
 * @tc.name: TestImageJsonWidth01
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonWidth01, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be -.
     */
    EXPECT_EQ(json->GetString("width"), "-");
}


/**
 * @tc.name: TestImageJsonHeight01
 * @tc.desc: Test image tojson.
 * @tc.type: FUNC
 */
HWTEST_F(ImagePatternTestToJson, TestImageJsonHeight01, TestSize.Level0)
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
    ASSERT_NE(imagePattern, nullptr);
    
    /**
     * @tc.steps: step2. call ToJsonValue.
     * @tc.expected: as follows
     */
    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    frameNode->ToJsonValue(json, filter);

    /**
     * @tc.steps: check the key value.
     * @tc.expected: it should be -.
     */
    EXPECT_EQ(json->GetString("height"), "-");
}

} // namespace OHOS::Ace::NG
