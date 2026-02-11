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

#ifndef FOUNDATION_ACE_INTERFACES_SAMPLER_MANAGER_H
#define FOUNDATION_ACE_INTERFACES_SAMPLER_MANAGER_H

#include "core/components_ng/render/adapter/sampler_manager.h"
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::Napi {
class SamplerManagerImpl : public NG::SamplerManager {
    DECLARE_ACE_TYPE(SamplerManagerImpl, NG::SamplerManager);
public:
    SamplerManagerImpl(napi_env env, napi_value jsInstance) : env_(env)
    {
        napi_create_reference(env_, jsInstance, 1, &jsInstance_);
    }
    ~SamplerManagerImpl()
    {
        if (jsInstance_) {
            napi_delete_reference(env_, jsInstance_);
        }
    }
    napi_value GetJSInstance()
    {
        CHECK_NULL_RETURN(jsInstance_, nullptr);
        napi_value jsInstancePtr = nullptr;
        napi_status status = napi_get_reference_value(env_, jsInstance_, &jsInstancePtr);
        if (status != napi_ok) {
            return nullptr;
        }
        return jsInstancePtr;
    }

private:
    napi_env env_ = nullptr;
    napi_ref jsInstance_ = nullptr;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACES_SAMPLER_MANAGER_H
