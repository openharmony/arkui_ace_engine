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

#include "core/components_ng/pattern/bubble/bridge/bubble_dynamic_module.h"
#include "core/components_ng/pattern/bubble/bridge/inner_modifier/bubble_inner_modifier.h"

#include "ecmascript/napi/include/jsnapi.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Bubble()
{
    return new OHOS::Ace::BubbleDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace InnerModifier {
constexpr const char* BUBBLE_INNER_MODIFIER = "bubbleInnerModifier";
} // namespace InnerModifier
} // namespace NG

void BubbleDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
}

const void* BubbleDynamicModule::GetDynamicModifier()
{
    return nullptr;
}

const void* BubbleDynamicModule::GetStaticModifier()
{
    return nullptr;
}

const void* BubbleDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* BubbleDynamicModule::GetModel()
{
    return nullptr;
}

const void* BubbleDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::InnerModifier::BUBBLE_INNER_MODIFIER) {
        return NG::InnerModifier::GetBubbleInnerModifier();
    }
    return nullptr;
}

} // namespace OHOS::Ace
