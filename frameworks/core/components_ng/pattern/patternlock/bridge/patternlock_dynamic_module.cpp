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

#include "core/components_ng/pattern/patternlock/bridge/patternlock_dynamic_module.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/components_ng/pattern/patternlock/bridge/arkts_native_pattern_lock_bridge.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/patternlock/patternlock_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_PatternLock()
{
    return new OHOS::Ace::PatternLockDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIPatternLockModifier* GetPatternLockDynamicModifier();
const CJUIPatternLockModifier* GetCJUIPatternLockModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIPatternLockModifier* GetPatternLockStaticModifier();
}
#endif
} // namespace NG

void PatternLockDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::PatternLockBridge::RegisterPatternLockAttributes(object, vm);
}

const void* PatternLockDynamicModule::GetDynamicModifier()
{
    return NG::GetPatternLockDynamicModifier();
}

const void* PatternLockDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetPatternLockStaticModifier();
#else
    return nullptr;
#endif
}

const void* PatternLockDynamicModule::GetCjModifier()
{
    return NG::GetCJUIPatternLockModifier();
}

void* PatternLockDynamicModule::GetModel()
{
    static NG::PatternLockModelNG model;
    return &model;
}

} // namespace OHOS::Ace
