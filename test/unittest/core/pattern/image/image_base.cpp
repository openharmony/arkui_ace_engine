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
void ImageBases::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ImageBases::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<PixelMap> ImageBases::CreatePixelMap(const std::string& src)
{
    RefPtr<PixelMap> pixelMap = nullptr;
    return pixelMap;
}

RefPtr<FrameNode> ImageBases::CreatePixelMapAnimator(int32_t number)
{
    ImageModelNG imageModelNG;
    std::vector<ImageProperties> images;
    for (int32_t index = 0; index < number; index++) {
        ImageProperties imageProperties;
        imageProperties.pixelMap = ImageBases::CreatePixelMap(IMAGE_SRC_URL);
        imageProperties.width = IMAGE_WIDTH;
        imageProperties.height = IMAGE_HEIGHT;
        imageProperties.top = IMAGE_TOP;
        imageProperties.left = IMAGE_LEFT;
        images.push_back(imageProperties);
    }
    imageModelNG.CreateAnimation(std::move(images), DURATION_DEFAULT, ITERATION_DEFAULT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImageBases::CreateImageNode(const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap)
{
    ImageModelNG image;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(src);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    image.SetAlt(ImageSourceInfo { alt });
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImageBases::CreateImageNodeWithDefaultProp(
    const std::string& src, const std::string& alt, RefPtr<PixelMap> pixMap)
{
    ImageModelNG image;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(src);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    image.SetAlt(ImageSourceInfo { alt });
    image.SetImageFill(SVG_FILL_COLOR_DEFAULT);
    image.SetImageFit(IMAGE_FIT_DEFAULT);
    image.SetImageRenderMode(IMAGE_RENDERMODE_DEFAULT);
    image.SetImageInterpolation(IMAGE_INTERPOLATION_DEFAULT);
    image.SetMatchTextDirection(MATCHTEXTDIRECTION_DEFAULT);
    image.SetImageRepeat(IMAGE_REPEAT_DEFAULT);
    image.SetColorFilterMatrix(COLOR_FILTER_DEFAULT);
    auto onError = [](const LoadImageFailEvent& info) {};
    image.SetOnError(std::move(onError));
    auto onComplete = [](const LoadImageSuccessEvent& info) {};
    image.SetOnComplete(std::move(onComplete));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImageBases::CreateSyncImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(PNG_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    image.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    image.SetSyncMode(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

RefPtr<FrameNode> ImageBases::CreateSyncWebImageNode()
{
    ImageModelNG image;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(WEB_IMAGE);
    imageInfoConfig.bundleName = BUNDLE_NAME;
    imageInfoConfig.moduleName = MODULE_NAME;
    imageInfoConfig.pixelMap = pixMap;
    image.Create(imageInfoConfig);
    image.SetAlt(ImageSourceInfo { ALT_SRC_URL });
    image.SetSyncMode(true);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

std::vector<RefPtr<UINode>> PopUINodes()
{
    std::vector<RefPtr<UINode>> vec;
    auto* stack = ViewStackProcessor::GetInstance();
    for (auto uiNode = stack->Finish(); uiNode != nullptr;) {
        vec.push_back(uiNode);
        uiNode = stack->Finish();
    }
    return vec;
}

void PushUINodes(std::vector<RefPtr<UINode>>& vec)
{
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        ViewStackProcessor::GetInstance()->Push(*it);
    }
}
} // namespace OHOS::Ace::NG
