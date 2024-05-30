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

#ifndef ACE_FRAMEWORKDELEGATE_H
#define ACE_FRAMEWORKDELEGATE_H

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT CJRuntimeDelegate {
public:
    static CJRuntimeDelegate* GetInstance()
    {
        if (instance_ == nullptr) {
            instance_ = new CJRuntimeDelegate();
        }
        return instance_;
    }

private:
    static CJRuntimeDelegate* instance_;

public:
    ACE_DISALLOW_COPY_AND_MOVE(CJRuntimeDelegate);

private:
    CJRuntimeDelegate() = default;

public:
    void RegisterCJFuncs(AtCPackage funcs);
    const AtCPackage& GetCJFuncs() const
    {
        return atCPackage_;
    }

    bool LoadAppEntry(const std::string& name);

    void* LoadCJLibrary(const char* dlName);
    void* GetUIScheduler();

private:
    bool LoadAtCPackage();

    AtCPackage atCPackage_;
    bool atCPackageLoaded_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // ACE_FRAMEWORKDELEGATE_H
