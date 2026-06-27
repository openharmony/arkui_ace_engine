/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image_animator/bridge/image_animator_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/image_animator/bridge/arkts_native_image_animator_bridge.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/image_animator/image_animator_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_ImageAnimator()
{
    return new OHOS::Ace::ImageAnimatorDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIImageAnimatorModifier* GetImageAnimatorDynamicModifier();
const CJUIImageAnimatorModifier* GetCJUIImageAnimatorModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void ImageAnimatorDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ImageAnimatorBridge::RegisterImageAnimatorAttributes(object, vm);
}

const void* ImageAnimatorDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetImageAnimatorDynamicModifier();
}

const void* ImageAnimatorDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetImageAnimatorStaticModifier();
#else
    return nullptr;
#endif
}

const void* ImageAnimatorDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIImageAnimatorModifier();
}

void* ImageAnimatorDynamicModule::GetModel()
{
    static NG::ImageAnimatorModelNG model;
    return &model;
}

const void* ImageAnimatorDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

} // namespace OHOS::Ace
