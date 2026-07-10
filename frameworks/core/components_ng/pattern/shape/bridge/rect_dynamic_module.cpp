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

#include "core/components_ng/pattern/shape/bridge/rect_dynamic_module.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/components_ng/pattern/shape/bridge/arkts_native_rect_bridge.h"
#include "core/components_ng/pattern/shape/bridge/arkts_native_common_shape_bridge.h"
#include "core/components_ng/pattern/shape/rect_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Rect()
{
    return new OHOS::Ace::RectDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIRectModifier* GetRectDynamicModifier();
const CJUIRectModifier* GetCJUIRectModifier();
}
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIRectModifier* GetRectStaticModifier();
}
#endif
} // namespace NG

void RectDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::RectBridge::RegisterRectAttributes(object, vm);
}

const void* RectDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetRectDynamicModifier();
}

const void* RectDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetRectStaticModifier();
#else
    return nullptr;
#endif
}

const void* RectDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIRectModifier();
}

void* RectDynamicModule::GetModel()
{
    static NG::RectModelNG model;
    return &model;
}

} // namespace OHOS::Ace
