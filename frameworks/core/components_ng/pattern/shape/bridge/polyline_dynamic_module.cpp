/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/shape/bridge/polyline_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/shape/bridge/arkts_native_polyline_bridge.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/components_ng/pattern/shape/polygon_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/shape/polygon_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Polyline()
{
    return new OHOS::Ace::PolylineDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIPolylineModifier* GetPolylineDynamicModifier();
const CJUIPolylineModifier* GetCJUIPolylineModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIPolylineModifier* GetPolylineStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void PolylineDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::PolylineBridge::RegisterPolylineAttributes(object, vm);
}

const void* PolylineDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetPolylineDynamicModifier();
}

const void* PolylineDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetPolylineStaticModifier();
#else
    return nullptr;
#endif
}

const void* PolylineDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIPolylineModifier();
}

void* PolylineDynamicModule::GetModel()
{
    static NG::PolygonModelNG model;
    return &model;
}

} // namespace OHOS::Ace
