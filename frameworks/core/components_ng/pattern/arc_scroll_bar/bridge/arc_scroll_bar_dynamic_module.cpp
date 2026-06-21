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

#include "core/components_ng/pattern/arc_scroll_bar/bridge/arc_scroll_bar_dynamic_module.h"
#include "core/components_ng/pattern/arc_scroll_bar/bridge/arc_scroll_bar_dynamic_modifier.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace {

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_ArcScrollBar()
{
    return new ArcScrollBarDynamicModule();
}

void ArcScrollBarDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm) {}
const void* ArcScrollBarDynamicModule::GetDynamicModifier() { return nullptr; }
const void* ArcScrollBarDynamicModule::GetStaticModifier() { return nullptr; }
const void* ArcScrollBarDynamicModule::GetCjModifier() { return nullptr; }

const void* ArcScrollBarDynamicModule::GetCustomModifier(const std::string& /* name */)
{
    return NG::NodeModifier::GetArcScrollBarCustomModifier();
}

void* ArcScrollBarDynamicModule::GetModel() { return nullptr; }
} // namespace OHOS::Ace
