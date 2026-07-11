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

#include "core/components_ng/pattern/canvas/bridge/canvas_dynamic_module.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "arkoala_api_generated.h"
#endif

#include "core/components_ng/pattern/canvas/bridge/arkts_native_canvas_bridge.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/interfaces/native/canvas_runtime_bridge_api.h"
#include "core/interfaces/native/node/canvas_rendering_context_2d_modifier.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Canvas()
{
    return new OHOS::Ace::CanvasDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUICanvasModifier* GetCanvasDynamicModifier();
const ArkUICanvasRenderingContext2DModifier* GetCanvasRenderingContext2DDynamicModifier();
const CJUICanvasRenderingContext2DModifier* GetCJUICanvasRenderingContext2DDynamicModifier();
const ArkUICanvasRuntimeBridge* GetCanvasRuntimeBridge();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUICanvasModifier* GetCanvasStaticModifier();
}
#endif
} // namespace NG

void CanvasDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::CanvasBridge::RegisterCanvasAttributes(object, vm);
}


const void* CanvasDynamicModule::GetDynamicModifier()
{
    return NG::GetCanvasDynamicModifier();
}

const void* CanvasDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetCanvasStaticModifier();
#else
    return nullptr;
#endif
}

const void* CanvasDynamicModule::GetCjModifier()
{
    return NG::GetCJUICanvasRenderingContext2DDynamicModifier();
}

void* CanvasDynamicModule::GetModel()
{
    static NG::CanvasModelNG model;
    return &model;
}

const void* CanvasDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "canvasBridge") {
        return NG::GetCanvasRuntimeBridge();
    }
    if (name == "CanvasRenderingContext2D") {
        return NG::GetCanvasRenderingContext2DDynamicModifier();
    }
    if (name == "CJCanvasRenderingContext2D") {
        return NG::GetCJUICanvasRenderingContext2DDynamicModifier();
    }
    return nullptr;
}

} // namespace OHOS::Ace
