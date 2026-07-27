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

#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/xcomponent/bridge/arkts_native_xcomponent_bridge.h"
#include "core/components_ng/pattern/xcomponent/bridge/arkts_native_xcomponent_node_bridge.h"
#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_dynamic_modifier.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/interfaces/ani/ani_api.h"
#include "core/interfaces/native/node/node_xcomponent_modifier.h"
#include "core/components_ng/pattern/xcomponent/bridge/xcomponent_model_impl.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_XComponent()
{
    return new OHOS::Ace::XComponentDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
#ifdef INCLUDE_GENERATED_SOURCES
const ArkUIAniXComponentModifier* GetXComponentStaticAniModifier();
namespace GeneratedModifier {
constexpr const char* XCOMPONENT_CONTROLLER_NATIVE_ACCESSOR = "xComponentControllerNativeAccessor";
constexpr const char* XCOMPONENT_CONTROLLER_EXTENDER_ACCESSOR = "xComponentControllerExtenderAccessor";
const GENERATED_ArkUIXComponentModifier* GetXComponentStaticModifier();
const GENERATED_ArkUIXComponentControllerNativeAccessor* GetXComponentControllerNativeStaticAccessor();
const GENERATED_ArkUIXComponentControllerExtenderAccessor* GetXComponentControllerExtenderStaticAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void XComponentDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::XComponentBridge::RegisterXComponentAttributes(object, vm);
    NG::XComponentNodeBridge::RegisterXComponentNodeAttributes(object, vm);
}

const void* XComponentDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetXComponentDynamicModifier();
}

const void* XComponentDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetXComponentStaticModifier();
#else
    return nullptr;
#endif
}

const void* XComponentDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIXComponentDynamicModifier();
}

const void* XComponentDynamicModule::GetAniModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GetXComponentStaticAniModifier();
#else
    return nullptr;
#endif
}

void* XComponentDynamicModule::GetModel()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifdef XCOMPONENT_SUPPORTED
#ifndef CROSS_PLATFORM
        static Framework::XComponentModelImpl model;
        return &model;
#endif
#endif
    }
    static NG::XComponentModelNG model;
    return &model;
}

const void* XComponentDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name.empty()) {
        return NG::NodeModifier::GetXComponentDynamicCustomModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::XCOMPONENT_CONTROLLER_NATIVE_ACCESSOR) {
        return NG::GeneratedModifier::GetXComponentControllerNativeStaticAccessor();
    }
    if (name == NG::GeneratedModifier::XCOMPONENT_CONTROLLER_EXTENDER_ACCESSOR) {
        return NG::GeneratedModifier::GetXComponentControllerExtenderStaticAccessor();
    }
#endif
    return nullptr;
}
} // namespace OHOS::Ace
