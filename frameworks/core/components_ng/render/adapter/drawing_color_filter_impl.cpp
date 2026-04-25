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

#include "core/components_ng/render/adapter/drawing_color_filter_impl.h"

#include "color_filter_napi/js_color_filter.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

#ifdef DIFFERENCE
#undef DIFFERENCE
#endif

namespace OHOS::Ace {
namespace {
static const std::unordered_map<BlendMode, OHOS::Rosen::Drawing::BlendMode> BLEND_MODE_MAP = {
    { BlendMode::CLEAR,       OHOS::Rosen::Drawing::BlendMode::CLEAR },
    { BlendMode::SRC,         OHOS::Rosen::Drawing::BlendMode::SRC },
    { BlendMode::DST,         OHOS::Rosen::Drawing::BlendMode::DST },
    { BlendMode::SRC_OVER,    OHOS::Rosen::Drawing::BlendMode::SRC_OVER },
    { BlendMode::DST_OVER,    OHOS::Rosen::Drawing::BlendMode::DST_OVER },
    { BlendMode::SRC_IN,      OHOS::Rosen::Drawing::BlendMode::SRC_IN },
    { BlendMode::DST_IN,      OHOS::Rosen::Drawing::BlendMode::DST_IN },
    { BlendMode::SRC_OUT,     OHOS::Rosen::Drawing::BlendMode::SRC_OUT },
    { BlendMode::DST_OUT,     OHOS::Rosen::Drawing::BlendMode::DST_OUT },
    { BlendMode::SRC_ATOP,    OHOS::Rosen::Drawing::BlendMode::SRC_ATOP },
    { BlendMode::DST_ATOP,    OHOS::Rosen::Drawing::BlendMode::DST_ATOP },
    { BlendMode::XOR,         OHOS::Rosen::Drawing::BlendMode::XOR },
    { BlendMode::PLUS,        OHOS::Rosen::Drawing::BlendMode::PLUS },
    { BlendMode::MODULATE,    OHOS::Rosen::Drawing::BlendMode::MODULATE },
    { BlendMode::SCREEN,      OHOS::Rosen::Drawing::BlendMode::SCREEN },
    { BlendMode::OVERLAY,     OHOS::Rosen::Drawing::BlendMode::OVERLAY },
    { BlendMode::DARKEN,      OHOS::Rosen::Drawing::BlendMode::DARKEN },
    { BlendMode::LIGHTEN,     OHOS::Rosen::Drawing::BlendMode::LIGHTEN },
    { BlendMode::COLOR_DODGE, OHOS::Rosen::Drawing::BlendMode::COLOR_DODGE },
    { BlendMode::COLOR_BURN,  OHOS::Rosen::Drawing::BlendMode::COLOR_BURN },
    { BlendMode::HARD_LIGHT,  OHOS::Rosen::Drawing::BlendMode::HARD_LIGHT },
    { BlendMode::SOFT_LIGHT,  OHOS::Rosen::Drawing::BlendMode::SOFT_LIGHT },
    { BlendMode::DIFF,        OHOS::Rosen::Drawing::BlendMode::DIFFERENCE },
    { BlendMode::EXCLUSION,   OHOS::Rosen::Drawing::BlendMode::EXCLUSION },
    { BlendMode::MULTIPLY,    OHOS::Rosen::Drawing::BlendMode::MULTIPLY },
    { BlendMode::HUE,         OHOS::Rosen::Drawing::BlendMode::HUE },
    { BlendMode::SATURATION,  OHOS::Rosen::Drawing::BlendMode::STATURATION },
    { BlendMode::COLOR,       OHOS::Rosen::Drawing::BlendMode::COLOR_MODE },
    { BlendMode::LUMINOSITY,  OHOS::Rosen::Drawing::BlendMode::LUMINOSITY },
};

OHOS::Rosen::Drawing::BlendMode TransformToRosenMode(BlendMode mode)
{
    auto it = BLEND_MODE_MAP.find(mode);
    if (it != BLEND_MODE_MAP.end()) {
        return it->second;
    }
    return OHOS::Rosen::Drawing::BlendMode::SRC_ATOP;
}
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* jsColorFilter = reinterpret_cast<OHOS::Rosen::Drawing::JsColorFilter*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingColorFilterImpl>(jsColorFilter->GetColorFilter());
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(const std::vector<float>& matrix)
{
    OHOS::Rosen::Drawing::ColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix.data());
    return AceType::MakeRefPtr<DrawingColorFilterImpl>(
        Rosen::Drawing::ColorFilter::CreateMatrixColorFilter(colorMatrix));
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilter(Color color, BlendMode blendMode)
{
    auto rosenColor = color.GetValue();
    auto rosenBlendMode = TransformToRosenMode(blendMode);
    return AceType::MakeRefPtr<DrawingColorFilterImpl>(
        Rosen::Drawing::ColorFilter::CreateBlendModeColorFilter(rosenColor, rosenBlendMode));
}

RefPtr<DrawingColorFilter> DrawingColorFilter::CreateDrawingColorFilterFromNative(void* sptrAddr)
{
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto* colorFilter = reinterpret_cast<std::shared_ptr<OHOS::Rosen::Drawing::ColorFilter>*>(sptrAddr);
    return AceType::MakeRefPtr<DrawingColorFilterImpl>(*colorFilter);
}

void* DrawingColorFilterImpl::GetDrawingColorFilterSptrAddr()
{
    return static_cast<void*>(&colorFilter_);
}

napi_value DrawingColorFilterImpl::GetDrawingColorFilterNapiValue(NativeEngine* nativeEngine)
{
#ifdef PREVIEW
    return nullptr;
#else
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    void* sptrAddr = GetDrawingColorFilterSptrAddr();
    CHECK_NULL_RETURN(sptrAddr, nullptr);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto* jsColorFilter = reinterpret_cast<OHOS::Rosen::Drawing::JsColorFilter*>(sptrAddr);
    return OHOS::Rosen::Drawing::JsColorFilter::Create(env, jsColorFilter->GetColorFilter());
#endif
}
} // namespace OHOS::Ace
