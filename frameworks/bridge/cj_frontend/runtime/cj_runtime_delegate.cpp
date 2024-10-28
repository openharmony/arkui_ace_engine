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

#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"

#include "cj_environment.h"

using namespace OHOS::Ace::Framework;

namespace {
constexpr int64_t VERIFY_VERSION = 10000;
}

CJRuntimeDelegate* CJRuntimeDelegate::instance_ = nullptr;

void* CJRuntimeDelegate::LoadCJLibrary(const char* dlName)
{
    return CJEnvironment::GetInstance()->LoadCJLibrary(dlName);
}

bool CJRuntimeDelegate::CheckLoadCJLibrary()
{
    return CJEnvironment::GetInstance()->CheckLoadCJLibrary();
}

void* CJRuntimeDelegate::GetUIScheduler()
{
    return CJEnvironment::GetInstance()->GetUIScheduler();
}

void CJRuntimeDelegate::RegisterCJFuncs(AtCPackage funcs)
{
    if (!atCPackageLoaded_) {
        atCPackage_ = funcs;
        atCPackageLoaded_ = true;
    }
}

bool CJRuntimeDelegate::LoadAtCPackage()
{
    if (!atCPackageLoaded_) {
        return false;
    }
    bool result = false;
    AtCOHOSAceFrameworkCJInstanceInitializeParams params(0, VERIFY_VERSION, &atCPackage_, &result);
    atCPackage_.atCOHOSAceFrameworkCJInstanceInitialize(&params);
    return result;
}

bool CJRuntimeDelegate::LoadAppEntry(const std::string& name)
{
    if (!atCPackageLoaded_ && !LoadAtCPackage()) {
        return false;
    }
    bool result = false;
    AtCOHOSAceFrameworkCJInstanceLoadEntryParams params(name.c_str(), &result);
    atCPackage_.atCOHOSAceFrameworkCJInstanceLoadEntry(&params);
    return result;
}
