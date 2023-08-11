/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "arkuiformrendergroup_fuzzer.h"

#define private public
#define protected public
#include "form_render/include/form_renderer_delegate_proxy.h"
#include "form_render/include/form_renderer_dispatcher_proxy.h"
#include "form_render/include/form_renderer_group.h"
#undef private
#undef protected

namespace OHOS::Ace {
const uint32_t u16m = 65535;
bool FormRenderGroup(const std::string data, size_t size)
{
    std::shared_ptr<OHOS::AbilityRuntime::Context> context;
    std::shared_ptr<OHOS::AbilityRuntime::Runtime> runtime;
    auto fromGroup = FormRendererGroup::Create(context, runtime);
    AAFwk::Want want;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    fromGroup->AddForm(want, formJsInfo);
    fromGroup->ReloadForm(formJsInfo);
    auto id = size % u16m;
    fromGroup->DeleteForm(std::to_string(id));
    return true;
}
}

using namespace OHOS;
using namespace OHOS::Ace;
/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    auto ri = size % u16m;
    std::string str(reinterpret_cast<const char*>(data), ri);
    /* Run your code on data */
    FormRenderGroup(str, size);
    return 0;
}
