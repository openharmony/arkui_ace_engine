/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#include <dlfcn.h>

#include "frameworks/bridge/common/utils/engine_helper.h"
#include "core/common/ai/image_analyzer_loader.h"

namespace OHOS::Ace {
namespace {
#ifdef __aarch64__
constexpr char IMAGE_ANALYZER_SO_PATH[] = "system/lib64/libai_image_analyzer_innerapi.z.so";
#else
constexpr char IMAGE_ANALYZER_SO_PATH[] = "system/lib/libai_image_analyzer_innerapi.z.so";
#endif
} // namespace

std::shared_ptr<ImageAnalyzerLoader> ImageAnalyzerLoader::Load()
{
    auto engLib(std::make_shared<ImageAnalyzerLoader>());
    return engLib->Init() ? engLib : nullptr;
}

ImageAnalyzerLoader::~ImageAnalyzerLoader()
{
    Close();
}

bool ImageAnalyzerLoader::Init()
{
    libraryHandle_ = dlopen(IMAGE_ANALYZER_SO_PATH, RTLD_LAZY);
    if (libraryHandle_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, " Could not dlopen %s: %s", IMAGE_ANALYZER_SO_PATH, dlerror());
        return false;
    }
    createImageAnalyzerInstance_ =
        (ImageAnalyzerInterface* (*)(napi_env)) dlsym(libraryHandle_, "createImageAnalyzerInstance");
    destroyImageAnalyzerInstance_ =
        (void (*)(ImageAnalyzerInterface *)) dlsym(libraryHandle_, "destroyImageAnalyzerInstance");
    if (createImageAnalyzerInstance_ == nullptr || destroyImageAnalyzerInstance_ == nullptr) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, " Could not find engine interface functions in %s", IMAGE_ANALYZER_SO_PATH);
        Close();
        return false;
    }
    return true;
}

ImageAnalyzerInstance ImageAnalyzerLoader::CreateImageAnalyzer()
{
    if (createImageAnalyzerInstance_ == nullptr || destroyImageAnalyzerInstance_ == nullptr) {
        return {};
    }
    auto engine = OHOS::Ace::EngineHelper::GetCurrentEngine();
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    return { createImageAnalyzerInstance_(env), [lib = shared_from_this(),
        destroy = destroyImageAnalyzerInstance_](ImageAnalyzerInterface *e) { destroy(e); } };
}

void ImageAnalyzerLoader::Close()
{
    if (libraryHandle_ != nullptr) {
        dlclose(libraryHandle_);
    }
    libraryHandle_ = nullptr;
    createImageAnalyzerInstance_ = nullptr;
    destroyImageAnalyzerInstance_ = nullptr;
}
}
