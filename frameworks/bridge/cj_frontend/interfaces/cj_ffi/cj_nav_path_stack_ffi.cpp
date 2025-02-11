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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_nav_path_stack_ffi.h"
#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"

namespace OHOS::Ace::Framework {

napi_value CJNavPathInfoNG::GetParamObj() const
{
    return nullptr;
}

void CJNavPathInfoNG::UpdateNavPathInfo(const RefPtr<NG::NavPathInfo>& info)
{
    NG::NavPathInfo::UpdateNavPathInfo(info);
    auto jsPathInfo = AceType::DynamicCast<CJNavPathInfoNG>(info);
    if (!jsPathInfo) {
        return;
    }
    param_ = jsPathInfo->GetParam();
}

} // namespace OHOS::Ace::Framework

CJNavPathInfo ConvertFFi2CJ(CJNavPathInfoFFi info)
{
    CJNavPathInfo ret = CJNavPathInfo();
    ret.name = info.name;
    ret.param = info.param;
    ret.index = info.index;
    ret.navDestinationId = info.navDestinationId;
    ret.isEntry = info.isEntry;
    ret.valid = info.valid;
    return ret;
}

CJNavPathInfoFFi ConvertCJ2FFi(CJNavPathInfo info)
{
    CJNavPathInfoFFi ret = CJNavPathInfoFFi();
    if (info.valid == -1) {
        ret.valid = info.valid;
    } else {
        ret.name = strdup(info.name.c_str());
        ret.param = strdup(info.param.c_str());
        ret.index = info.index;
        ret.navDestinationId = strdup(info.navDestinationId.c_str());
        ret.isEntry = info.isEntry;
        ret.valid = info.valid;
    }
    return ret;
}

extern "C" {
int64_t FfiOHOSAceFrameworkNavPathStackCreate()
{
    auto ret_ = OHOS::FFI::FFIData::Create<OHOS::Ace::Framework::CJNavPathStack>();
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}
void FfiOHOSAceFrameworkNavPathStackPushPath(int64_t id, CJNavPathInfoFFi info)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack pushPath!");
    }
    self_->PushPath(ConvertFFi2CJ(info));
}

CJNavPathInfoFFi FfiOHOSAceFrameworkNavPathStackPop(int64_t id)
{
    auto self_ = OHOS::FFI::FFIData::GetData<OHOS::Ace::Framework::CJNavPathStack>(id);
    if (self_ == nullptr) {
        LOGE("Failed to invoke ffi function: CJNavPathStack pop!");
    }
    auto ret = self_->Pop();
    return ConvertCJ2FFi(ret);
}
}