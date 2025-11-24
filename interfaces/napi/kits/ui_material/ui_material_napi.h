/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_UI_MATERIAL_NAPI_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_UI_MATERIAL_NAPI_H
 
#include "core/components_ng/common_napi_utils/common_napi_utils.h"
namespace OHOS::Ace::Napi {
 
class UiMaterialNapi {
public:
    UiMaterialNapi() = default;
    virtual ~UiMaterialNapi() = default;
    static napi_value Init(napi_env env, napi_value exports);

private:
    static napi_value JsEnumIntInit(napi_env env, napi_value exports);
    static napi_value GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName);
    static int32_t GetCInt32(napi_value value, napi_env env);
    static napi_valuetype GetValueType(napi_env env, napi_value value);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void* nativeObject, void* finalize);
    static void WrapMaterialObject(napi_env env, napi_value jsThis, int32_t materialType);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_UI_MATERIAL_NAPI_H
