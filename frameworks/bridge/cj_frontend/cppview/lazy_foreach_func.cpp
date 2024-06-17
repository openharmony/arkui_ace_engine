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

#include "bridge/cj_frontend/cppview/lazy_foreach_func.h"

#include "bridge/cj_frontend/cppview/data_change_listener.h"
#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using namespace OHOS::FFI;
using namespace std;

namespace OHOS::Ace::Framework {

string LazyForEachFuncs::GenerateKey(int64_t index)
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    if (!funcs.atCOHOSAceFrameworkLazyForEachFuncsGenerateKey) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs GenerateKey, return empty id!");
        return "";
    }
    auto cstr = funcs.atCOHOSAceFrameworkLazyForEachFuncsGenerateKey(GetID(), index);
    std::string res = cstr.value;
    cstr.free(cstr.value);
    return res;
}

void LazyForEachFuncs::GenerateItem(int64_t index)
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    void (*cjFunc)(int64_t, int64_t) = funcs.atCOHOSAceFrameworkLazyForEachFuncsGenerateItem;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs GenerateItem!");
        return;
    }
    cjFunc(GetID(), index);
}

int64_t LazyForEachFuncs::GetTotalCount()
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    auto cjFunc = funcs.atCOHOSAceFrameworkLazyForEachFuncsGetTotalCount;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs GetTotalCount, return 0!");
        return 0;
    }
    int64_t count = cjFunc(GetID());
    return count;
}

void LazyForEachFuncs::RegisterListenerFunc(const sptr<CJDataChangeListener>& listener)
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    auto cjFunc = funcs.atCOHOSAceFrameworkLazyForEachFuncsDataChangeListenerRegister;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs DataChangeListenerRegister!");
        return;
    }
    cjFunc(GetID(), listener->GetID());
}

void LazyForEachFuncs::UnRegisterListenerFunc(const sptr<CJDataChangeListener>& listener)
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    auto cjFunc = funcs.atCOHOSAceFrameworkLazyForEachFuncsDataChangeListenerUnregister;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs DataChangeListenerUnregister!");
        return;
    }
    cjFunc(GetID(), listener->GetID());
}

void LazyForEachFuncs::MarkLazyForEachProcess(const std::string& key)
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    auto cjFunc = funcs.atCOHOSAceFrameworkLazyForEachFuncsMarkLazy;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs MarkLazy!");
        return;
    }
    cjFunc(GetID(), key.c_str());
}

void LazyForEachFuncs::ResetLazyForEachProcess()
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    auto cjFunc = funcs.atCOHOSAceFrameworkLazyForEachFuncsResetLazy;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs ResetLazy!");
        return;
    }
    cjFunc(GetID());
}

void LazyForEachFuncs::RemoveChildGroupById(const std::string& composedId)
{
    auto funcs = CJRuntimeDelegate::GetInstance()->GetCJFuncs();
    auto cjFunc = funcs.atCOHOSAceFrameworkLazyForEachFuncsRemoveChildGroup;
    if (!cjFunc) {
        LOGE("Failed to invoke cj function: LazyForEachFuncs RemoveChildGroup!");
        return;
    }
    cjFunc(GetID(), composedId.c_str());
}

} // namespace OHOS::Ace::Framework
