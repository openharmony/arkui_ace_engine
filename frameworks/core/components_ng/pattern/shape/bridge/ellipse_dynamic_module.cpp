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

#include "core/components_ng/pattern/shape/bridge/ellipse_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#include "core/components_ng/pattern/shape/bridge/arkts_native_ellipse_bridge.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/components_ng/pattern/shape/ellipse_model_ng.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/shape/ellipse_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Ellipse()
{
    return new OHOS::Ace::EllipseDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIEllipseModifier* GetEllipseDynamicModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIEllipseModifier* GetEllipseStaticModifier();
}
#endif
} // namespace NG

void EllipseDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::EllipseBridge::RegisterEllipseAttributes(object, vm);
}

const void* EllipseDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetEllipseDynamicModifier();
}

const void* EllipseDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetEllipseStaticModifier();
#else
    return nullptr;
#endif
}

const void* EllipseDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* EllipseDynamicModule::GetModel()
{
    static NG::EllipseModelNG model;
    return &model;
}

} // namespace OHOS::Ace