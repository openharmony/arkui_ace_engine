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

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

#if !defined(PREVIEW)
#include "napi/native_api.h"
#include "native_engine/native_engine.h"
#endif

#if !defined(PREVIEW)
namespace OHOS::Rosen {
class RSNode;
}

namespace OHOS::Ace {
class WantWrap;
}
#endif

namespace OHOS::Ace::Framework {
#if !defined(PREVIEW)
    RefPtr<PixelMap> CreatePixelMapFromNapiValue(JSRef<JSVal> obj);
    const std::shared_ptr<Rosen::RSNode> CreateRSNodeFromNapiValue(JSRef<JSVal> obj);
    RefPtr<PixelMap> GetDrawablePixmap(JSRef<JSVal> obj);
    RefPtr<OHOS::Ace::WantWrap> CreateWantWrapFromNapiValue(JSRef<JSVal> obj);
#endif

    bool IsDisableEventVersion();
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_UTILS_H
