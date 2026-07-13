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

#include "core/components_ng/pattern/video/bridge/video_dynamic_module.h"

#include "core/components_ng/pattern/video/bridge/arkts_native_video_bridge.h"
#include "core/components_ng/pattern/video/bridge/video_controller_async_custom_modifier.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Video()
{
    return new OHOS::Ace::VideoDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIVideoModifier* GetVideoDynamicModifier();
const CJUIVideoModifier* GetCJUIVideoDynamicModifier();
const ArkUIVideoControllerAsyncModifier* GetVideoControllerAsyncDynamicModifier();
} // namespace NodeModifier

namespace GeneratedModifier {
const GENERATED_ArkUIVideoModifier* GetVideoStaticModifier();
} // namespace GeneratedModifier
} // namespace NG

void VideoDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::VideoBridge::RegisterVideoAttributes(object, vm);
}

const void* VideoDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetVideoDynamicModifier();
}

const void* VideoDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetVideoStaticModifier();
#else
    return nullptr;
#endif
}

const void* VideoDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIVideoDynamicModifier();
}

const void* VideoDynamicModule::GetCustomModifier(const std::string& /* name */)
{
    return NG::NodeModifier::GetVideoControllerAsyncDynamicModifier();
}

void* VideoDynamicModule::GetModel()
{
    static NG::VideoModelNG model;
    return &model;
}

} // namespace OHOS::Ace
