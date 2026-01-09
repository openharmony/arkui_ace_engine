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

#include "core/components_ng/pattern/rating/bridge/rating_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/rating/bridge/arkts_native_rating_bridge.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/rating/rating_model_static.h"
#include "core/components_ng/pattern/rating/bridge/rating_content_modifier_helper.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Rating()
{
    return new OHOS::Ace::RatingDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIRatingModifier* GetRatingDynamicModifier();
const CJUIRatingModifier* GetCJUIRatingModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
const GENERATED_ArkUIRatingModifier* GetRatingStaticModifier();
const GENERATED_ArkUIRatingContentModifier* GetRatingStaticContentModifier();
}
#endif
} // namespace NG

void RatingDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::RatingBridge::RegisterRatingAttributes(object, vm);
}

const void* RatingDynamicModule::GetDynamicModifier()
{
    return NG::GetRatingDynamicModifier();
}

const void* RatingDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetRatingStaticModifier();
#else
    return nullptr;
#endif
}

const void* RatingDynamicModule::GetCjModifier()
{
    return NG::GetCJUIRatingModifier();
}

void* RatingDynamicModule::GetModel()
{
    static NG::RatingModelNG model;
    return &model;
}

const void* RatingDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetRatingStaticContentModifier();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
