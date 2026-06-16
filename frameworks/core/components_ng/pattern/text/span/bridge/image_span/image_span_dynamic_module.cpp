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

#include "core/components_ng/pattern/text/span/bridge/image_span/image_span_dynamic_module.h"

#include "arkoala_api_generated.h"
#include "ecmascript/napi/include/jsnapi.h"
#include "core/components_ng/pattern/text/span/bridge/image_span/arkts_native_image_span_bridge.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/pattern/text/span/image_span_view.h"
#include "core/components_ng/pattern/text/span/bridge/image_span/image_span_custom_modifier.h"
 	 
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/text/span/image_span_view_static.h"
#endif

namespace OHOS::Ace {

namespace NG {
struct ArkUIImageSpanModifier;
struct CJUIImageSpanModifier;

namespace NodeModifier {
const ArkUIImageSpanModifier* GetImageSpanDynamicModifier();
const CJUIImageSpanModifier* GetCJUIImageSpanModifier();
const ArkUIImageSpanCustomModifier* GetImageSpanCustomModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIImageSpanModifier* GetImageSpanStaticModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_ImageSpan()
{
    return new ImageSpanDynamicModule();
}

void ImageSpanDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ImageSpanBridge::RegisterImageSpanAttributes(object, vm);
}

const void* ImageSpanDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetImageSpanDynamicModifier();
}

const void* ImageSpanDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetImageSpanStaticModifier();
#else
    return nullptr;
#endif
}

const void* ImageSpanDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIImageSpanModifier();
}

const void* ImageSpanDynamicModule::GetCustomModifier(const std::string& name)
{
    return NG::NodeModifier::GetImageSpanCustomModifier();
}

void* ImageSpanDynamicModule::GetModel()
{
    static NG::ImageSpanView model;
    return &model;
}

} // namespace OHOS::Ace
