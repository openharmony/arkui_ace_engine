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

#include "drawing_color_filter_ohos.h"

#include "base/utils/utils.h"
#include "color_filter_napi/js_color_filter.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace {
RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* jsColorFilter = reinterpret_cast<OHOS::Rosen::Drawing::JsColorFilter*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingColorFilterOhos>(jsColorFilter->GetColorFilter());
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(const std::vector<float>& matrix)
{
    OHOS::Rosen::Drawing::ColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix.data());
    return AceType::MakeRefPtr<DrawingColorFilterOhos>(
        Rosen::Drawing::ColorFilter::CreateMatrixColorFilter(colorMatrix));
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilterFromNative(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* colorFilter = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter>*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingColorFilterOhos>(*colorFilter);
}

void* DrawingColorFilterOhos::GetDrawingColorFilterSptrAddr()
{
    return static_cast<void*>(&colorFilter_);
}

napi_value DrawingColorFilterOhos::GetDrawingColorFilterNapiValue(NativeEngine* nativeEngine)
{
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    void* sptrAddr = GetDrawingColorFilterSptrAddr();
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto* jsColorFilter = reinterpret_cast<OHOS::Rosen::Drawing::JsColorFilter*>(sptrAddr);
    return OHOS::Rosen::Drawing::JsColorFilter::Create(env, jsColorFilter->GetColorFilter());
}
} // namespace OHOS::Ace
