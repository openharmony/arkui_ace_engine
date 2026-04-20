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

#include "image_base.h"

namespace OHOS::Ace::NG {

class ImagePatternSwitchCasesTestNg : public ImageBases {};

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrCover001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::COVER);
    EXPECT_EQ(result, "COVER");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrContain001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::CONTAIN);
    EXPECT_EQ(result, "CONTAIN");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrFill001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::FILL);
    EXPECT_EQ(result, "FILL");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrFitWidth001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::FITWIDTH);
    EXPECT_EQ(result, "FITWIDTH");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrFitHeight001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::FITHEIGHT);
    EXPECT_EQ(result, "FITHEIGHT");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrNone001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::NONE);
    EXPECT_EQ(result, "NONE");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrScaleDown001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::SCALE_DOWN);
    EXPECT_EQ(result, "SCALE_DOWN");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrTopLeft001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(ImageFit::TOP_LEFT);
    EXPECT_EQ(result, "TOP_LEFT");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageFitStrDefault001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageFitStr(static_cast<ImageFit>(999));
    EXPECT_EQ(result, "COVER");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageRepeatStrNoRepeat001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageRepeatStr(ImageRepeat::NO_REPEAT);
    EXPECT_EQ(result, "NO_REPEAT");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageRepeatStrRepeatX001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageRepeatStr(ImageRepeat::REPEAT_X);
    EXPECT_EQ(result, "REPEAT_X");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageRepeatStrRepeatY001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageRepeatStr(ImageRepeat::REPEAT_Y);
    EXPECT_EQ(result, "REPEAT_Y");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageRepeatStrRepeat001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageRepeatStr(ImageRepeat::REPEAT);
    EXPECT_EQ(result, "REPEAT_XY");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageRepeatStrDefault001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetImageRepeatStr(static_cast<ImageRepeat>(999));
    EXPECT_EQ(result, "NO_REPEAT");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageColorFilterStrEmpty001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::vector<float> emptyFilter;
    std::string result = pattern->GetImageColorFilterStr(emptyFilter);
    EXPECT_EQ(result, "");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageColorFilterStrSingle001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::vector<float> filter = {1.0f};
    std::string result = pattern->GetImageColorFilterStr(filter);
    EXPECT_EQ(result, "[1.000000]");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageColorFilterStrMultiple001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::vector<float> filter = {1.0f, 0.5f, 0.3f};
    std::string result = pattern->GetImageColorFilterStr(filter);
    EXPECT_NE(result, "");
    EXPECT_TRUE(result.find("1.000000") != std::string::npos);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringUnsupported001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::UNSUPPORTED);
    EXPECT_EQ(result, "unsupported");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringFile001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::FILE);
    EXPECT_EQ(result, "file");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringAsset001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::ASSET);
    EXPECT_EQ(result, "asset");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringNetwork001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::NETWORK);
    EXPECT_EQ(result, "network");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringMemory001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::MEMORY);
    EXPECT_EQ(result, "memory");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringBase64_001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::BASE64);
    EXPECT_EQ(result, "base64");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringInternal001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::INTERNAL);
    EXPECT_EQ(result, "internal");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringResource001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::RESOURCE);
    EXPECT_EQ(result, "resource");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringDataAbility001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::DATA_ABILITY);
    EXPECT_EQ(result, "dataAbility");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringDataAbilityDecoded001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::DATA_ABILITY_DECODED);
    EXPECT_EQ(result, "dataAbilityDecoded");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringResourceId001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::RESOURCE_ID);
    EXPECT_EQ(result, "resourceId");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringPixmap001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::PIXMAP);
    EXPECT_EQ(result, "pixmap");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringAstc001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::ASTC);
    EXPECT_EQ(result, "astc");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetSrcTypeToStringStream001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    std::string result = pattern->GetSrcTypeToString(SrcType::STREAM);
    EXPECT_EQ(result, "stream");
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpImageFitAllBranches001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    
    layoutProperty->UpdateImageFit(ImageFit::COVER);
    pattern->DumpLayoutInfo();
    
    layoutProperty->UpdateImageFit(ImageFit::CONTAIN);
    pattern->DumpLayoutInfo();
    
    layoutProperty->UpdateImageFit(ImageFit::FILL);
    pattern->DumpLayoutInfo();
    
    layoutProperty->UpdateImageFit(ImageFit::NONE);
    pattern->DumpLayoutInfo();
    
    layoutProperty->UpdateImageFit(ImageFit::SCALE_DOWN);
    pattern->DumpLayoutInfo();
    
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpImageRepeatAllBranches001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    renderProperty->UpdateImageRepeat(ImageRepeat::NO_REPEAT);
    pattern->DumpRenderInfo();
    
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT);
    pattern->DumpRenderInfo();
    
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_X);
    pattern->DumpRenderInfo();
    
    renderProperty->UpdateImageRepeat(ImageRepeat::REPEAT_Y);
    pattern->DumpRenderInfo();
    
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpRenderModeAllBranches001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    renderProperty->UpdateImageRenderMode(ImageRenderMode::ORIGINAL);
    pattern->DumpRenderInfo();
    
    renderProperty->UpdateImageRenderMode(ImageRenderMode::TEMPLATE);
    pattern->DumpRenderInfo();
    
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpDynamicRangeModeHigh001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    renderProperty->UpdateDynamicMode(DynamicRangeMode::HIGH);
    
    pattern->DumpRenderInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpDynamicRangeModeConstraint001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    renderProperty->UpdateDynamicMode(DynamicRangeMode::CONSTRAINT);
    
    pattern->DumpRenderInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpDynamicRangeModeStandard001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    renderProperty->UpdateDynamicMode(DynamicRangeMode::STANDARD);
    
    pattern->DumpRenderInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpImageColorFilterWithValue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    std::vector<float> colorFilter = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    renderProperty->UpdateColorFilter(colorFilter);
    
    pattern->DumpRenderInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpImageColorFilterEmpty001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    std::vector<float> emptyFilter;
    renderProperty->UpdateColorFilter(emptyFilter);
    
    pattern->DumpRenderInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpBorderColorFilterNoValue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);
    
    auto renderProperty = frameNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_NE(renderProperty, nullptr);
    
    pattern->DumpRenderInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationDown001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::DOWN);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationRight001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::RIGHT);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationLeft001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::LEFT);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationAuto001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::AUTO);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationUpMirrored001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::UP_MIRRORED);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationRightMirrored001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::RIGHT_MIRRORED);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationDownMirrored001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::DOWN_MIRRORED);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateOrientationLeftMirrored001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::LEFT_MIRRORED);
    pattern->UpdateOrientation();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetOrientation001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetOrientation(ImageRotateOrientation::RIGHT);
    auto orientation = pattern->GetOrientation();
    EXPECT_EQ(orientation, ImageRotateOrientation::RIGHT);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageQualityNone001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageQuality(AIImageQuality::NONE);
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::NONE);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageQualityLow001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageQuality(AIImageQuality::LOW);
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::LOW);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageQualityNormal001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageQuality(AIImageQuality::NORMAL);
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::NORMAL);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageQualityHigh001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageQuality(AIImageQuality::HIGH);
    EXPECT_EQ(pattern->GetImageQuality(), AIImageQuality::HIGH);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetCopyOptionNone001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetCopyOption(CopyOptions::None);
    EXPECT_EQ(pattern->GetCopyOption(), CopyOptions::None);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetCopyOptionLocal001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetCopyOption(CopyOptions::Local);
    EXPECT_EQ(pattern->GetCopyOption(), CopyOptions::Local);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetCopyOptionDistributed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetCopyOption(CopyOptions::Distributed);
    EXPECT_EQ(pattern->GetCopyOption(), CopyOptions::Distributed);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetSyncLoadTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetSyncLoad(true);
    EXPECT_TRUE(pattern->GetSyncLoad());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetSyncLoadFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetSyncLoad(false);
    EXPECT_FALSE(pattern->GetSyncLoad());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetNeedBorderRadiusTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetNeedBorderRadius(true);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetNeedBorderRadiusFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetNeedBorderRadius(false);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageTypeBase001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageType(ImageType::BASE);
    EXPECT_EQ(pattern->GetImageType(), ImageType::BASE);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageTypeDrawable001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageType(ImageType::DRAWABLE);
    EXPECT_EQ(pattern->GetImageType(), ImageType::DRAWABLE);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageTypePixelmapDrawable001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageType(ImageType::PIXELMAP_DRAWABLE);
    EXPECT_EQ(pattern->GetImageType(), ImageType::PIXELMAP_DRAWABLE);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, EnableAnalyzerTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->EnableAnalyzer(true);
    EXPECT_TRUE(pattern->IsEnableAnalyzer());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, EnableAnalyzerFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->EnableAnalyzer(false);
    EXPECT_FALSE(pattern->IsEnableAnalyzer());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageAnimatorTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageAnimator(true);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetImageAnimatorFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetImageAnimator(false);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetIsComponentSnapshotNodeTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetIsComponentSnapshotNode(true);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetIsComponentSnapshotNodeFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetIsComponentSnapshotNode(false);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetIsAnimation001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    bool result = pattern->GetIsAnimation();
    EXPECT_FALSE(result);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, TriggerThemeUpdate001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->TriggerThemeUpdate(1);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetNeedLoadAltTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetNeedLoadAlt(true);
    EXPECT_TRUE(pattern->GetNeedLoadAlt());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetNeedLoadAltFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetNeedLoadAlt(false);
    EXPECT_FALSE(pattern->GetNeedLoadAlt());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetDefaultAutoResize001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    bool result = pattern->GetDefaultAutoResize();
    EXPECT_TRUE(result);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetDefaultInterpolation001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto result = pattern->GetDefaultInterpolation();
    EXPECT_EQ(result, ImageInterpolation::NONE);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetExternalDecodeFormat001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetExternalDecodeFormat(PixelFormat::RGBA_8888);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::RGBA_8888);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetExternalDecodeFormatNV21_001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetExternalDecodeFormat(PixelFormat::NV21);
    EXPECT_EQ(pattern->GetExternalDecodeFormat(), PixelFormat::NV21);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetSupportSvg2True001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetSupportSvg2(true);
    EXPECT_TRUE(pattern->GetSupportSvg2());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, SetSupportSvg2False001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->SetSupportSvg2(false);
    EXPECT_FALSE(pattern->GetSupportSvg2());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetIsRecycleInvisibleImageMemory001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->GetIsRecycleInvisibleImageMemory());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnConfigurationUpdate001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnConfigurationUpdate();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, ResetImage001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->ResetImage();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, ResetAltImage001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->ResetAltImage();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, ResetImageAndAlt001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->ResetImageAndAlt();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, ResetAltImageError001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->ResetAltImageError();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateImageSourceInfo001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo newSourceInfo("new_image.png");
    pattern->UpdateImageSourceinfo(newSourceInfo);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateImageFill001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    Color fillColor = Color::RED;
    pattern->UpdateImageFill(fillColor);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, UpdateImageAlt001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    ImageSourceInfo altSourceInfo("new_alt.png");
    pattern->UpdateImageAlt(altSourceInfo);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetContentTransitionParam001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto result = pattern->GetContentTransitionParam();
    EXPECT_EQ(result, ContentTransitionType::IDENTITY);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnColorModeChange001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnColorModeChange(0);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnColorModeChangeDark001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnColorModeChange(1);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, FinishMeasureForOnComplete001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->FinishMeasureForOnComplete();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, IsAtomicNode001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    bool result = pattern->IsAtomicNode();
    EXPECT_TRUE(result);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, AllowVisibleAreaCheck001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->AllowVisibleAreaCheck());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetFocusPattern001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto focusPattern = pattern->GetFocusPattern();
    EXPECT_EQ(focusPattern.focusType_, FocusType::NODE);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnVisibleChangeTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnVisibleChange(true);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnVisibleChangeFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnVisibleChange(false);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnWindowHide001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnWindowHide();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnNotifyMemoryLevel001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnNotifyMemoryLevel(0);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnNotifyMemoryLevelCritical001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnNotifyMemoryLevel(2);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnRecycle001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnRecycle();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnReuse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnReuse();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnSensitiveStyleChangeTrue001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnSensitiveStyleChange(true);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnSensitiveStyleChangeFalse001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnSensitiveStyleChange(false);
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, EnableDrag001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->EnableDrag();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DefaultSupportDrag001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    bool result = pattern->DefaultSupportDrag();
    EXPECT_TRUE(result);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, IsEnableFix001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    bool result = pattern->IsEnableFix();
    EXPECT_TRUE(result);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, IsEnableMatchParent001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    bool result = pattern->IsEnableMatchParent();
    EXPECT_TRUE(result);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, LoadImageDataIfNeed001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->LoadImageDataIfNeed();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, RecycleImageData001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->RecycleImageData());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpInfo001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->DumpInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->DumpAdvanceInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, DumpSvgInfo001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->DumpSvgInfo();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetRawImageSize001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    SizeF size = pattern->GetRawImageSize();
    EXPECT_EQ(size.Width(), -1.0f);
    EXPECT_EQ(size.Height(), -1.0f);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageLoadingContext001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto loadingCtx = pattern->GetImageLoadingContext();
    EXPECT_TRUE(loadingCtx.Invalid() || !loadingCtx.Invalid());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetAltImageLoadingContext001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto altLoadingCtx = pattern->GetAltImageLoadingContext();
    EXPECT_TRUE(altLoadingCtx.Invalid() || !altLoadingCtx.Invalid());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetCanvasImage001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    const auto& canvasImage = pattern->GetCanvasImage();
    EXPECT_TRUE(canvasImage == nullptr || canvasImage != nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetAltCanvasImage001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    const auto& altCanvasImage = pattern->GetAltCanvasImage();
    EXPECT_TRUE(altCanvasImage == nullptr || altCanvasImage != nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetClientHost001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto clientHost = pattern->GetClientHost();
    EXPECT_NE(clientHost, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetImageSizeForMeasure001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto sizeOpt = pattern->GetImageSizeForMeasure();
    EXPECT_TRUE(sizeOpt.has_value() || !sizeOpt.has_value());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, GetContextParam001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto contextParam = pattern->GetContextParam();
    EXPECT_TRUE(contextParam.has_value());
}

HWTEST_F(ImagePatternSwitchCasesTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, CreateLayoutProperty001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto layoutProperty = pattern->CreateLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, CreatePaintProperty001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto paintProperty = pattern->CreatePaintProperty();
    EXPECT_NE(paintProperty, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, CreateEventHub001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    auto eventHub = pattern->CreateEventHub();
    EXPECT_NE(eventHub, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnAttachToMainRenderTree001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnAttachToMainRenderTree();
    EXPECT_NE(pattern, nullptr);
}

HWTEST_F(ImagePatternSwitchCasesTestNg, OnOffscreenProcessResource001, TestSize.Level1)
{
    auto frameNode = CreateImageNode(IMAGE_SRC_URL, ALT_SRC_URL, nullptr);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ImagePattern>();
    EXPECT_NE(pattern, nullptr);

    pattern->OnOffscreenProcessResource();
    EXPECT_NE(pattern, nullptr);
}

} // namespace OHOS::Ace::NG