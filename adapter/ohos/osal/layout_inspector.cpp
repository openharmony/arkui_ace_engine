/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/common/layout_inspector.h"

#include <string>

#include "include/core/SkImage.h"
#include "include/core/SkString.h"
#include "include/core/SkColorSpace.h"
#include "include/utils/SkBase64.h"

#include "wm/window.h"

#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/connect_server_manager.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_v2/inspector/inspector.h"
#include "dm/display_manager.h"
#include "foundation/ability/ability_runtime/frameworks/native/runtime/connect_server_manager.h"

namespace OHOS::Ace {

namespace {

sk_sp<SkColorSpace> ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return SkColorSpace::MakeSRGB();
}

SkAlphaType AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return SkAlphaType::kUnknown_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return SkAlphaType::kOpaque_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return SkAlphaType::kPremul_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return SkAlphaType::kUnpremul_SkAlphaType;
        default:
            return SkAlphaType::kUnknown_SkAlphaType;
    }
}

SkColorType PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return SkColorType::kRGB_565_SkColorType;
        case PixelFormat::RGBA_8888:
            return SkColorType::kRGBA_8888_SkColorType;
        case PixelFormat::BGRA_8888:
            return SkColorType::kBGRA_8888_SkColorType;
        case PixelFormat::ALPHA_8:
            return SkColorType::kAlpha_8_SkColorType;
        case PixelFormat::RGBA_F16:
            return SkColorType::kRGBA_F16_SkColorType;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return SkColorType::kUnknown_SkColorType;
    }
}

SkImageInfo MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    SkColorType colorType = PixelFormatToSkColorType(pixmap);
    SkAlphaType alphaType = AlphaTypeToSkAlphaType(pixmap);
    sk_sp<SkColorSpace> colorSpace = ColorSpaceToSkColorSpace(pixmap);
    return SkImageInfo::Make(pixmap->GetWidth(), pixmap->GetHeight(), colorType, alphaType, colorSpace);
}
} // namespace

bool LayoutInspector::layoutInspectorStatus_ = false;
const char PNG_TAG[] = "png";

void LayoutInspector::SupportInspector()
{
    auto container = Container::Current();
    CHECK_NULL_VOID_NOLOG(container);
    if (!layoutInspectorStatus_) {
        return;
    }
    std::string treeJsonStr;
    GetInspectorTreeJsonStr(treeJsonStr, ContainerScope::CurrentId());
    if (treeJsonStr.empty()) {
        return;
    }
    auto message = JsonUtil::Create(true);
    GetSnapshotJson(ContainerScope::CurrentId(), message);
    CHECK_NULL_VOID(message);

    auto sendTask = [treeJsonStr, jsonSnapshotStr = message->ToString(), container]() {
        if (container->IsUseStageModel()) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        } else {
            OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendTask));
}

void LayoutInspector::SetStatus(bool layoutInspectorStatus)
{
    layoutInspectorStatus_ = layoutInspectorStatus;
}

void LayoutInspector::SetCallback(int32_t instanceId)
{
    LOGI("SetCallback start");
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID_NOLOG(container);
    if (container->IsUseStageModel()) {
        OHOS::AbilityRuntime::ConnectServerManager::Get().SetLayoutInspectorCallback(
            [](int32_t containerId) { return CreateLayoutInfo(containerId); },
            [](bool status) { return SetStatus(status); });
    } else {
        OHOS::Ace::ConnectServerManager::Get().SetLayoutInspectorCallback(
            [](int32_t containerId) { return CreateLayoutInfo(containerId); },
            [](bool status) { return SetStatus(status); });
    }
}

void LayoutInspector::CreateLayoutInfo(int32_t containerId)
{
    LOGI("CreateLayoutInfo start");
    ContainerScope sope(containerId);
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID_NOLOG(container);
    std::string treeJsonStr;
    GetInspectorTreeJsonStr(treeJsonStr, containerId);
    auto message = JsonUtil::Create(true);
    GetSnapshotJson(containerId, message);
    CHECK_NULL_VOID(message);

    auto sendTask = [treeJsonStr, jsonSnapshotStr = message->ToString(), container]() {
        if (container->IsUseStageModel()) {
            OHOS::AbilityRuntime::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        } else {
            OHOS::Ace::ConnectServerManager::Get().SendInspector(treeJsonStr, jsonSnapshotStr);
        }
    };
    BackgroundTaskExecutor::GetInstance().PostTask(std::move(sendTask));
}

void LayoutInspector::GetInspectorTreeJsonStr(std::string& treeJsonStr, int32_t containerId)
{
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID_NOLOG(container);
#ifdef NG_BUILD
    treeJsonStr = NG::Inspector::GetInspector(true);
#else
    if (container->IsUseNewPipeline()) {
        treeJsonStr = NG::Inspector::GetInspector(true);
    } else {
        auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_VOID(pipelineContext);
        treeJsonStr = V2::Inspector::GetInspectorTree(pipelineContext, true);
    }
#endif
}

void LayoutInspector::GetSnapshotJson(int32_t containerId, std::unique_ptr<JsonValue>& message)
{
    LOGI("GetSnapshotJson start");
    auto container = AceEngine::Get().GetContainer(containerId);
    CHECK_NULL_VOID_NOLOG(container);

    OHOS::sptr<OHOS::Rosen::Window> window = OHOS::Rosen::Window::GetTopWindowWithId(container->GetWindowId());
    CHECK_NULL_VOID_NOLOG(window);
    auto pixelMap = window->Snapshot();
    CHECK_NULL_VOID(pixelMap);
    auto acePixelMap = AceType::MakeRefPtr<PixelMapOhos>(pixelMap);
    CHECK_NULL_VOID(acePixelMap);
    auto imageInfo = MakeSkImageInfoFromPixelMap(acePixelMap);
    SkPixmap imagePixmap(
        imageInfo, reinterpret_cast<const void*>(acePixelMap->GetPixels()), acePixelMap->GetRowBytes());
    sk_sp<SkImage> image;
    image = SkImage::MakeFromRaster(imagePixmap, &PixelMap::ReleaseProc, PixelMap::GetReleaseContext(acePixelMap));
    CHECK_NULL_VOID(image);
    auto data = image->encodeToData(SkEncodedImageFormat::kPNG, 100);
    CHECK_NULL_VOID(data);
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    CHECK_NULL_VOID(defaultDisplay);
    auto deviceDpi = defaultDisplay->GetDpi();
    auto deviceWidth = defaultDisplay->GetWidth();
    auto deviceHeight = defaultDisplay->GetHeight();
    LOGI("GetSnapshotJson: deviceWidth: %{public}d, deviceHeight: %{public}d, dpi: %{public}d", deviceWidth,
        deviceHeight, deviceDpi);
    message->Put("type", "snapShot");
    message->Put("format", PNG_TAG);
    message->Put("width", (*pixelMap).GetWidth());
    message->Put("height", (*pixelMap).GetHeight());
    message->Put("posX", container->GetViewPosX());
    message->Put("posY", container->GetViewPosY());
    message->Put("deviceWidth", deviceWidth);
    message->Put("deviceHeight", deviceHeight);
    message->Put("deviceDpi", deviceDpi);
    int32_t encodeLength = SkBase64::Encode(data->data(), data->size(), nullptr);
    message->Put("size", data->size());
    SkString info(encodeLength);
    SkBase64::Encode(data->data(), data->size(), info.writable_str());
    message->Put("pixelMapBase64", info.c_str());
    LOGI("GetSnapshotJson pixelMapBase64:%{public}s", info.c_str());
}

} // namespace OHOS::Ace
