/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_QUICKJS_QJS_PA_ENGINE_LOADER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_QUICKJS_QJS_PA_ENGINE_LOADER_H

#include "base/utils/singleton.h"
#include "frameworks/bridge/pa_backend/engine/common/js_backend_engine_loader.h"

namespace OHOS::Ace::Framework {
class QjsPaEngineLoader : public JsBackendEngineLoader, public Singleton<QjsPaEngineLoader> {
    DECLARE_SINGLETON(QjsPaEngineLoader)
public:
     virtual RefPtr<JsBackendEngine> CreateJsBackendEngine(int32_t instanceId) const final;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_QUICKJS_QJS_PA_ENGINE_LOADER_H
