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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DEPTH_COMPONENT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DEPTH_COMPONENT_H

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components/common/properties/depth_option.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::Framework {

class JSDepthComponent : public JSContainerBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void SetDepthMap(const JSCallbackInfo& info);
    static void SetCamera(const JSCallbackInfo& info);
    static void SetLight(const JSCallbackInfo& info);
    static void SetBackgroundOffset(const JSCallbackInfo& info);
    static void SetBackgroundScale(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

private:
    static OHOS::Ace::DepthBackgroundSource ParseBackgroundSource(const JSRef<JSVal>& imageInfo);
    static bool IsGltfSource(const std::string& src);
    static bool SetOhosPath(const std::string& uri, std::string& ohosPath);
    static void ParseAndSetDepthSpace(const JSRef<JSVal>& optionsValue);
    static OHOS::Ace::DepthVector3 ParseVector3(const JSRef<JSVal>& vectorValue);
    static OHOS::Ace::DepthVector4 ParseVector4(const JSRef<JSVal>& vectorValue);
    static OHOS::Ace::DepthColorRGB ParseLightColor(const JSRef<JSVal>& colorValue);
    static DepthBackgroundOffset ParseBackgroundOffset(const JSRef<JSVal>& offsetValue);
    static std::optional<NG::VectorF> ParseBackgroundScale(const JSRef<JSVal>& scaleValue);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DEPTH_COMPONENT_H
