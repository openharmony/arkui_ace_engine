/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/qrcode/bridge/qrcode_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/qrcode/bridge/arkts_native_qrcode_bridge.h"
#include "core/components_ng/pattern/qrcode/qrcode_model_ng.h"


#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/qrcode/qrcode_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_QRCode()
{
    return new OHOS::Ace::QRCodeDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIQRCodeModifier* GetQRCodeDynamicModifier();
const CJUIQRCodeModifier* GetCJUIQRCodeModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIQRCodeModifier* GetQRCodeStaticModifier();
}
#endif
} // namespace NG

void QRCodeDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::QRCodeBridge::RegisterQRCodeAttributes(object, vm);
}

const void* QRCodeDynamicModule::GetDynamicModifier()
{
    return NG::GetQRCodeDynamicModifier();
}

const void* QRCodeDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetQRCodeStaticModifier();
#else
    return nullptr;
#endif
}

const void* QRCodeDynamicModule::GetCjModifier()
{
    return NG::GetCJUIQRCodeModifier();
}

void* QRCodeDynamicModule::GetModel()
{
    static NG::QRCodeModelNG model;
    return &model;
}

} // namespace OHOS::Ace
