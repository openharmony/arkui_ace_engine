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

#include "core/components_ng/pattern/shape/bridge/shape_dynamic_module.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/components_ng/pattern/shape/bridge/arkts_native_shape_bridge.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/components_ng/pattern/shape/shape_model_ng.h"
#include "core/interfaces/ani/ani_api.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Shape()
{
    return new OHOS::Ace::ShapeDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIShapeModifier* GetShapeDynamicModifier();
const CJUIShapeModifier* GetCJUIShapeModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
const ArkUIAniShapeModifier* GetShapeAniModifier();
namespace GeneratedModifier {
const GENERATED_ArkUIShapeModifier* GetShapeStaticModifier();
}
#endif
} // namespace NG

void ShapeDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ShapeBridge::RegisterShapeAttributes(object, vm);
}

const void* ShapeDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetShapeDynamicModifier();
}

const void* ShapeDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetShapeStaticModifier();
#else
    return nullptr;
#endif
}

const void* ShapeDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIShapeModifier();
}

void* ShapeDynamicModule::GetModel()
{
    static NG::ShapeModelNG model;
    return &model;
}

const void* ShapeDynamicModule::GetAniModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GetShapeAniModifier();
#else
    return nullptr;
#endif
}

} // namespace OHOS::Ace