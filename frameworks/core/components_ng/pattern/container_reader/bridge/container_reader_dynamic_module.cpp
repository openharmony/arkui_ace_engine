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

#include "core/components_ng/pattern/container_reader/bridge/container_reader_dynamic_module.h"

#include "core/components_ng/pattern/container_reader/bridge/arkts_native_container_reader_bridge.h"
#include "core/components_ng/pattern/container_reader/container_reader_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_ContainerReader()
{
    return new OHOS::Ace::ContainerReaderDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIContainerReaderModifier* GetContainerReaderDynamicModifier();
} // namespace NG

void ContainerReaderDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ContainerReaderBridge::RegisterContainerReaderAttributes(object, vm);
}

const void* ContainerReaderDynamicModule::GetDynamicModifier()
{
    return NG::GetContainerReaderDynamicModifier();
}

const void* ContainerReaderDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* ContainerReaderDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* ContainerReaderDynamicModule::GetModel()
{
    static NG::ContainerReaderModelNG model;
    return &model;
}

const void* ContainerReaderDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

} // namespace OHOS::Ace
