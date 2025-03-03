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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_image_ffi.h"

#ifndef __NON_OHOS__
#include "pixel_map_impl.h"
#endif
#include "cj_lambda.h"
#include "core/components_ng/pattern/image/image_model_ng.h"

using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace;

namespace {
const std::vector<ImageRepeat> OBJECT_REPEATS = {
    ImageRepeat::NO_REPEAT,
    ImageRepeat::REPEAT_X,
    ImageRepeat::REPEAT_Y,
    ImageRepeat::REPEAT
};
const std::vector<ImageInterpolation> IMAGE_INTERPOLATIONS = {
    ImageInterpolation::NONE,
    ImageInterpolation::HIGH,
    ImageInterpolation::MEDIUM,
    ImageInterpolation::LOW
};
const std::vector<ImageRenderMode> IMAGE_RENDER_MODES = {
    ImageRenderMode::ORIGINAL,
    ImageRenderMode::TEMPLATE
};
const std::vector<DynamicRangeMode> IMAGE_DYNAMICRANGE_MODES = {
    DynamicRangeMode::HIGH,
    DynamicRangeMode::CONSTRAINT,
    DynamicRangeMode::STANDARD
};
const std::vector<CopyOptions> IMAGE_COPY_OPTIONS = {
    CopyOptions::None,
    CopyOptions::InApp,
    CopyOptions::Local,
    CopyOptions::Distributed
};
constexpr uint32_t FIT_MATRIX = 16;
} // namespace

extern "C" {
void FfiOHOSAceFrameworkImageCreateWithUrl(const char* url)
{
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = std::make_shared<std::string>(std::string(url));
    imageInfoConfig.bundleName = "";
    imageInfoConfig.moduleName = "";
    imageInfoConfig.isUriPureNumber = false;
    imageInfoConfig.isImageSpan = false;
    RefPtr<PixelMap> pixMap = nullptr;
    ImageModel::GetInstance()->Create(imageInfoConfig, pixMap);
}

void FfiOHOSAceFrameworkImageCreateWithPixelMap(int64_t id)
{
#ifndef __NON_OHOS__
    std::string bundleName;
    std::string moduleName;
    auto instance = OHOS::FFI::FFIData::GetData<OHOS::Media::PixelMapImpl>(id);
    if (!instance) {
        LOGE("[PixelMap] instance not exist %{public}" PRId64, id);
        return;
    }
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap = instance->GetRealPixelMap();
    RefPtr<PixelMap> pixelMapRef = PixelMap::CreatePixelMap(&pixelMap);
    ImageInfoConfig imageInfoConfig;
    imageInfoConfig.src = nullptr;
    imageInfoConfig.bundleName = "";
    imageInfoConfig.moduleName = "";
    imageInfoConfig.isUriPureNumber = false;
    imageInfoConfig.isImageSpan = false;
    ImageModel::GetInstance()->Create(imageInfoConfig, pixelMapRef);
#endif
}

void FfiOHOSAceFrameworkImageCreateWithContent(int32_t imageContent)
{
    if (imageContent != 0) {
        LOGE("invalid value for image content");
        return;
    }

    ImageModel::GetInstance()->ResetImage();
}

void FfiOHOSAceFrameworkImageSetAlt(const char* url)
{
    std::string bundleName;
    std::string moduleName;
    ImageModel::GetInstance()->SetAlt(ImageSourceInfo { url, bundleName, moduleName });
}

void FfiOHOSAceFrameworkImageSetAltWithPixelMap(int64_t pixelMapId)
{
#ifndef __NON_OHOS__
    auto instance = OHOS::FFI::FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (!instance) {
        LOGE("[PixelMap] instance not exist %{public}" PRId64, pixelMapId);
        return;
    }
    std::shared_ptr<OHOS::Media::PixelMap> pixelMap = instance->GetRealPixelMap();
    RefPtr<PixelMap> pixelMapRef = PixelMap::CreatePixelMap(&pixelMap);
    auto srcInfo = ImageSourceInfo(pixelMapRef);
    ImageModel::GetInstance()->SetAlt(srcInfo);
#endif
}

CJ_EXPORT void FfiOHOSAceFrameworkImageSetBorderRadius()
{
    ImageModel::GetInstance()->SetBackBorder();
}

void FfiOHOSAceFrameworkImageSetObjectFit(int32_t objectFit)
{
    int32_t parseRes = objectFit;
    if (parseRes < static_cast<int32_t>(ImageFit::FILL) || parseRes > static_cast<int32_t>(ImageFit::MATRIX)) {
        parseRes = static_cast<int32_t>(ImageFit::COVER);
    }
    auto fit = static_cast<ImageFit>(parseRes);
    if (parseRes == FIT_MATRIX) {
        fit = ImageFit::MATRIX;
    }
    ImageModel::GetInstance()->SetImageFit(fit);
}

void FfiOHOSAceFrameworkImageSetObjectRepeat(int32_t objectRepeat)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(objectRepeat, OBJECT_REPEATS.size())) {
        LOGE("invalid value for image repeat");
        return;
    }
    ImageModel::GetInstance()->SetImageRepeat(OBJECT_REPEATS[objectRepeat]);
}

void FfiOHOSAceFrameworkImageSetInterpolation(int32_t interpolation)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(interpolation, IMAGE_INTERPOLATIONS.size())) {
        LOGE("invalid value for image interpolation");
        return;
    }
    ImageModel::GetInstance()->SetImageInterpolation(IMAGE_INTERPOLATIONS[interpolation]);
}

void FfiOHOSAceFrameworkImageSetRenderMode(int32_t renderMode)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(renderMode, IMAGE_RENDER_MODES.size())) {
        LOGE("invalid value for image render mode");
        return;
    }
    ImageModel::GetInstance()->SetImageRenderMode(IMAGE_RENDER_MODES[renderMode]);
}

void FfiOHOSAceFrameworkImageSetSourceSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthDime(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightDime(height, static_cast<DimensionUnit>(heightUnit));
    ImageModel::GetInstance()->SetImageSourceSize(std::pair<Dimension, Dimension>(widthDime, heightDime));
}

void FfiOHOSAceFrameworkImageSetSyncLoad(bool syncLoad)
{
    ImageModel::GetInstance()->SetSyncMode(syncLoad);
}

void FfiOHOSAceFrameworkImageSetImageFill(uint32_t color)
{
    ImageModel::GetInstance()->SetImageFill(Color(color));
}

void FfiOHOSAceFrameworkImageSetAutoResize(bool autoResize)
{
    ImageModel::GetInstance()->SetAutoResize(autoResize);
}

void FfiOHOSAceFrameworkImageSetMatchTextDirection(bool isMatchTextDirection)
{
    ImageModel::GetInstance()->SetMatchTextDirection(isMatchTextDirection);
}

void FfiOHOSAceFrameworkImageSetFitOriginalSize(bool isFitOriginalSize)
{
    ImageModel::GetInstance()->SetFitOriginSize(isFitOriginalSize);
}

void FfiOHOSAceFrameworkImageSetColorFilter(void* vectorHandle)
{
    const auto& matrix = *reinterpret_cast<std::vector<float>*>(vectorHandle);
    ImageModel::GetInstance()->SetColorFilterMatrix(matrix);
}

void FfiOHOSAceFrameworkImageDynamicRangeMode(int32_t value)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(value, IMAGE_DYNAMICRANGE_MODES.size())) {
        LOGE("invalid value for image dynamic rangeMode");
        return;
    }
    ImageModel::GetInstance()->SetDynamicRangeMode(IMAGE_DYNAMICRANGE_MODES[value]);
}

void FfiOHOSAceFrameworkImageCopyOption(int32_t value)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(value, IMAGE_COPY_OPTIONS.size())) {
        LOGE("invalid value for image copy option");
        return;
    }
    ImageModel::GetInstance()->SetCopyOption(IMAGE_COPY_OPTIONS[value]);
}

void FfiOHOSAceFrameworkImageDraggable(bool value)
{
    ImageModel::GetInstance()->SetDraggable(value);
}

void FfiOHOSAceFrameworkImageOnError(void (*callback)(CJImageError errorInfo))
{
    auto onError = [ffiOnError = CJLambda::Create(callback)](const LoadImageFailEvent& newInfo) -> void {
        CJImageError ffiErrorInfo {};
        ffiErrorInfo.componentWidth = newInfo.GetComponentWidth();
        ffiErrorInfo.componentHeight = newInfo.GetComponentHeight();
        ffiErrorInfo.message = newInfo.GetErrorMessage().c_str();
        ffiOnError(ffiErrorInfo);
    };
    ImageModel::GetInstance()->SetOnError(onError);
}

void FfiOHOSAceFrameworkImageOnFinish(void (*callback)())
{
    auto onFinish = [ffiOnFinish = CJLambda::Create(callback)]() -> void {
        ffiOnFinish();
    };
    ImageModel::GetInstance()->SetSvgAnimatorFinishEvent(onFinish);
}

void FfiOHOSAceFrameworkImageOnComplete(void (*callback)(CJImageComplete completeInfo))
{
    auto onComplete = [ffiOnComplete = CJLambda::Create(callback)](const LoadImageSuccessEvent& newInfo) -> void {
        CJImageComplete ffiCompleteInfo {};
        ffiCompleteInfo.width = newInfo.GetWidth();
        ffiCompleteInfo.height = newInfo.GetHeight();
        ffiCompleteInfo.componentWidth = newInfo.GetComponentWidth();
        ffiCompleteInfo.componentHeight = newInfo.GetComponentHeight();
        ffiCompleteInfo.loadingStatus = newInfo.GetLoadingStatus();
        ffiCompleteInfo.contentWidth = newInfo.GetContentWidth();
        ffiCompleteInfo.contentHeight = newInfo.GetContentHeight();
        ffiCompleteInfo.contentOffsetX = newInfo.GetContentOffsetX();
        ffiCompleteInfo.contentOffsetY = newInfo.GetContentOffsetY();
        ffiOnComplete(ffiCompleteInfo);
    };
    ImageModel::GetInstance()->SetOnComplete(onComplete);
}
}
