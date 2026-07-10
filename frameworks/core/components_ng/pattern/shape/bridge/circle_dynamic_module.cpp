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

#include "core/components_ng/pattern/shape/bridge/circle_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#include "core/components_ng/pattern/shape/bridge/arkts_native_circle_bridge.h"
#include "core/components_ng/pattern/shape/circle_model_ng.h"
#include "core/interfaces/native/node/common_shape_modifier.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Circle()
{
    return new OHOS::Ace::CircleDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUICircleModifier* GetCircleDynamicModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUICircleModifier* GetCircleStaticModifier();
}
#endif
} // namespace NG

void CircleDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::CircleBridge::RegisterCircleAttributes(object, vm);
}

const void* CircleDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetCircleDynamicModifier();
}

const void* CircleDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetCircleStaticModifier();
#else
    return nullptr;
#endif
}

const void* CircleDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* CircleDynamicModule::GetModel()
{
    static NG::CircleModelNG model;
    return &model;
}

} // namespace OHOS::Ace