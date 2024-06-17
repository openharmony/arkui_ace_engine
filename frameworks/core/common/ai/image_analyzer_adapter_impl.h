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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_ANALYZER_ADAPTER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_ANALYZER_ADAPTER_IMPL_H

#include "napi/native_api.h"
#include "image_analyzer_adapter.h"

namespace OHOS::Ace {
class ImageAnalyzerAdapterImpl : public ImageAnalyzerAdapter {
public:
    ImageAnalyzerAdapterImpl();
    ~ImageAnalyzerAdapterImpl() override;
    void SetImageAnalyzerConfig(void* config, bool isOptions = false) override;
    void* GetImageAnalyzerConfig() override;
    void* ConvertPixmapNapi(const RefPtr<PixelMap>& pixelMap) override;
    bool HasImageAnalyzerConfig() override;
private:
    napi_env env_ = nullptr;
    napi_ref analyzerConfigRef_ = nullptr;
    bool hasOptions_ = false;
};
}
#endif
