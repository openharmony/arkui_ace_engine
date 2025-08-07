/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_UTILS_H

#include "napi/native_api.h"
#include "native_engine/native_engine.h"

#include "base/image/drawing_color_filter.h"
#include "base/image/drawing_lattice.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

#if !defined(PREVIEW)
namespace OHOS::Rosen {
class RSNode;
}

namespace OHOS::Ace {
class WantWrap;
}
#endif

namespace OHOS::Rosen {
class VisualEffect;
class Filter;
class Blender;
}

namespace OHOS::Ace::Framework {
class ScopeRAII {
public:
    explicit ScopeRAII(napi_env env) : env_(env)
    {
        napi_open_handle_scope(env_, &scope_);
    }
    ~ScopeRAII()
    {
        napi_close_handle_scope(env_, scope_);
    };
private:
    napi_env env_;
    napi_handle_scope scope_;
};
#if !defined(PREVIEW)
const std::shared_ptr<Rosen::RSNode> CreateRSNodeFromNapiValue(JSRef<JSVal> obj);
RefPtr<OHOS::Ace::WantWrap> CreateWantWrapFromNapiValue(JSRef<JSVal> obj);
#endif

#ifdef PIXEL_MAP_SUPPORTED
JSRef<JSVal> ConvertPixmap(const RefPtr<PixelMap>& pixelMap);
napi_value ConvertPixmapNapi(const RefPtr<PixelMap>& pixelMap);
bool GetPixelMapListFromAnimatedDrawable(JSRef<JSVal> obj, std::vector<RefPtr<PixelMap>>& pixelMaps,
    int32_t& duration, int32_t& iterations);
#endif

const Rosen::VisualEffect* CreateRSEffectFromNapiValue(JSRef<JSVal> obj);
const Rosen::Filter* CreateRSFilterFromNapiValue(JSRef<JSVal> obj);
const Rosen::Blender* CreateRSBlenderFromNapiValue(JSRef<JSVal> obj);
std::optional<NG::BorderRadiusProperty> HandleDifferentRadius(JsiRef<JSVal> args);
std::optional<NG::BorderRadiusProperty> ParseBorderRadiusAttr(JsiRef<JSVal> args);
bool IsDisableEventVersion();
void ParseTextShadowFromShadowObject(const JSRef<JSVal>& shadowObject, std::vector<Shadow>& shadows);
bool IsDrawable(const JSRef<JSVal>& jsValue);
RefPtr<PixelMap> GetDrawablePixmap(JSRef<JSVal> obj);
RefPtr<PixelMap> CreatePixelMapFromNapiValue(const JSRef<JSVal>& obj, NativeEngine* localNativeEngine = nullptr);
RefPtr<DrawingColorFilter> CreateDrawingColorFilter(JSRef<JSVal> obj);
RefPtr<DrawingLattice> CreateDrawingLattice(JSRef<JSVal> obj);
bool CheckRegexValid(const std::string& pattern);
napi_env GetCurrentEnv();
void* UnwrapNapiValue(const JSRef<JSVal>& obj);
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_UTILS_H
