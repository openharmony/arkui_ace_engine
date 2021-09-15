/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/image_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/image/image_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ImageComposedElement&)>> CREATE_JSON_MAP {
    { "uri", [](const ImageComposedElement& inspector) { return inspector.GetUri(); } },
    { "alt", [](const ImageComposedElement& inspector) { return inspector.GetAlt(); } },
    { "objectFit", [](const ImageComposedElement& inspector) { return inspector.GetObjectFit(); } },
    { "objectRepeat", [](const ImageComposedElement& inspector) { return inspector.GetObjectRepeat(); } },
    { "interpolation", [](const ImageComposedElement& inspector) { return inspector.GetInterpolation(); } },
    { "renderMode", [](const ImageComposedElement& inspector) { return inspector.GetRenderMode(); } },
    { "sourceSize", [](const ImageComposedElement& inspector) { return inspector.GetSourceSize(); } },
};

} // namespace

void ImageComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("uri: ").append(GetUri()));
    DumpLog::GetInstance().AddDesc(std::string("alt: ").append(GetAlt()));
    DumpLog::GetInstance().AddDesc(std::string("objectFit: ").append(GetObjectFit()));
    DumpLog::GetInstance().AddDesc(std::string("objectRepeat: ").append(GetObjectRepeat()));
    DumpLog::GetInstance().AddDesc(std::string("interpolation: ").append(GetInterpolation()));
    DumpLog::GetInstance().AddDesc(std::string("renderMode: ").append(GetRenderMode()));
    DumpLog::GetInstance().AddDesc(std::string("sourceSize: ").append(GetSourceSize()));
}

std::unique_ptr<JsonValue> ImageComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ImageComposedElement::GetUri() const
{
    auto renderImage = GetRenderImage();
    return renderImage ? renderImage->GetImageSrc() : "";
}

std::string ImageComposedElement::GetAlt() const
{
    auto renderImage = GetRenderImage();
    return renderImage ? renderImage->GetImageAlt() : "";
}

std::string ImageComposedElement::GetObjectFit() const
{
    auto renderImage = GetRenderImage();
    auto imageFit =
        renderImage ? renderImage->GetImageFit() : ImageFit::COVER;
    return ConvertWrapImageFitToString(imageFit);
}

std::string ImageComposedElement::GetObjectRepeat() const
{
    auto renderImage = GetRenderImage();
    auto imageRepeat =
        renderImage ? renderImage->GetImageRepeat() : ImageRepeat::NOREPEAT;
    return ConvertWrapImageRepeatToString(imageRepeat);
}

std::string ImageComposedElement::GetInterpolation() const
{
    auto renderImage = GetRenderImage();
    auto imageInterpolation =
        renderImage ? renderImage->GetImageInterpolation() : ImageInterpolation::NONE;
    return ConvertWrapImageInterpolationToString(imageInterpolation);
}

std::string ImageComposedElement::GetRenderMode() const
{
    auto renderImage = GetRenderImage();
    auto imageRenderMode =
        renderImage ? renderImage->GetImageRenderMode() : ImageRenderMode::ORIGINAL;
    return ConvertWrapImageRenderModeToString(imageRenderMode);
}

std::string ImageComposedElement::GetSourceSize() const
{
    auto renderImage = GetRenderImage();
    auto imageSourceSize = renderImage ? renderImage->GetImageSourceSize()
                        : Size();
    return imageSourceSize.ToString();
}

RefPtr<RenderImage> ImageComposedElement::GetRenderImage() const
{
    auto node = GetInspectorNode(ImageElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderImage>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2
