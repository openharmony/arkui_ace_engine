/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "bridge/common/utils/engine_helper.h"
#include "core/common/ai/image_analyzer_adapter_impl.h"
#include "core/common/ai/image_analyzer_mgr.h"
#if defined(PIXEL_MAP_SUPPORTED)
#include "pixel_map_napi.h"
#endif

namespace OHOS::Ace {
ImageAnalyzerAdapterImpl::ImageAnalyzerAdapterImpl()
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    env_ = reinterpret_cast<napi_env>(nativeEngine);
}

ImageAnalyzerAdapterImpl::~ImageAnalyzerAdapterImpl()
{
    if (analyzerConfigRef_ != nullptr) {
        napi_delete_reference(env_, analyzerConfigRef_);
    }
}

void ImageAnalyzerAdapterImpl::SetImageAnalyzerConfig(void* config, bool isOptions)
{
    napi_ref configRef = nullptr;
    napi_value configValue = reinterpret_cast<napi_value>(config);
    napi_create_reference(env_, configValue, 1, &configRef);
    analyzerConfigRef_ = configRef;
    if (isOptions) {
        hasOptions_ = true;
    }
}

void* ImageAnalyzerAdapterImpl::GetImageAnalyzerConfig()
{
    napi_value analyzerConfig = nullptr;
    napi_get_reference_value(env_, analyzerConfigRef_, &analyzerConfig);

    // If config is not set, all types are enabled by default.
    if (analyzerConfig == nullptr) {
        std::vector<ImageAnalyzerType> types = {ImageAnalyzerType::SUBJECT, ImageAnalyzerType::TEXT};
        napi_value typeNapi = nullptr;
        napi_create_array(env_, &typeNapi);
        for (int i = 0; i < static_cast<int>(types.size()); ++i) {
            napi_value tmpValue = nullptr;
            napi_create_int32(env_, static_cast<int>(types[i]), &tmpValue);
            napi_set_element(env_, typeNapi, i, tmpValue);
        }
        napi_set_named_property(env_, analyzerConfig, "types", typeNapi);
    }
    return analyzerConfig;
}

void* ImageAnalyzerAdapterImpl::ConvertPixmapNapi(const RefPtr<PixelMap>& pixelMap)
{
#if defined(PIXEL_MAP_SUPPORTED)
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env_, &scope);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, {});
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMap->GetPixelMapSharedPtr());
    napi_ref napiValueRef = nullptr;
    napi_create_reference(env_, napiValue, 1, &napiValueRef);
    napi_close_handle_scope(env_, scope);
    return napiValueRef;
#else
    return nullptr;
#endif
}

bool ImageAnalyzerAdapterImpl::HasImageAnalyzerConfig()
{
    napi_value analyzerConfig = nullptr;
    napi_get_reference_value(env_, analyzerConfigRef_, &analyzerConfig);
    return analyzerConfig != nullptr && hasOptions_;
}

ImageAnalyzerAdapter* CreateImageAnalyzerAdapter()
{
    return new ImageAnalyzerAdapterImpl();
}
}