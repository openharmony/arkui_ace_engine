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

#include "frameworks/bridge/js_frontend/engine/jsi/jsi_engine_loader.h"

#include "compatible/components/canvas/canvas_modifier_compatible.h"
#include "core/common/dynamic_module_helper.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_xcomponent_bridge.h"

namespace OHOS::Ace {
SINGLETON_INSTANCE_IMPL(Framework::JsiEngineLoader);
}

namespace OHOS::Ace::Framework {

namespace {

const ArkUICanvasModifierCompatible* GetCanvasInnerModifier()
{
    static const ArkUICanvasModifierCompatible* canvasModifier_ = nullptr;
    if (canvasModifier_) {
        return canvasModifier_;
    }
    auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("canvas");
    if (loader) {
        canvasModifier_ = reinterpret_cast<const ArkUICanvasModifierCompatible*>(loader->GetCustomModifier());
        return canvasModifier_;
    }
    return nullptr;
}
} // namespace

JsiEngineLoader::JsiEngineLoader() = default;
JsiEngineLoader::~JsiEngineLoader() = default;

RefPtr<JsEngine> JsiEngineLoader::CreateJsEngine(int32_t instanceId) const
{
    return AceType::MakeRefPtr<JsiEngine>(instanceId);
}

RefPtr<BaseCanvasBridge> JsiEngineLoader::CreateCanvasBridge() const
{
    CanvasBridgeParams params = { .pipeline = nullptr, .width = 0, .height = 0, .isOffscreen = false };
    const auto* modifier = GetCanvasInnerModifier();
    void* bridgePtr = modifier->createCanvasBridge(params);
    return AceType::Claim(reinterpret_cast<BaseCanvasBridge*>(bridgePtr));
}

RefPtr<BaseXComponentBridge> JsiEngineLoader::CreateXComponentBridge() const
{
#ifdef XCOMPONENT_SUPPORTED
    return AceType::MakeRefPtr<JsiXComponentBridge>();
#else
    return nullptr;
#endif
}

#if defined(BUILT_IN_JS_ENGINE)
JsEngineLoader& JsEngineLoader::Get(const char*)
{
    return JsiEngineLoader::GetInstance();
}
#else
extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_GetJsEngineLoader()
{
    return &JsiEngineLoader::GetInstance();
}
#endif

} // namespace OHOS::Ace::Framework
