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

#ifndef ACE_ENGINE_CJ_LAZYFOREACH_FUNC_H
#define ACE_ENGINE_CJ_LAZYFOREACH_FUNC_H

#include <string>

#include "base/utils/macros.h"
#include "ffi_remote_data.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

namespace OHOS {
namespace Ace {
namespace Framework {

class CJDataChangeListener;

class ACE_EXPORT LazyForEachFuncs : public FFI::RemoteData {
    CJ_REMOTE_CLASS(LazyForEachFuncs)

public :
    std::string GenerateKey(int64_t index);
    void GenerateItem(int64_t index);
    int64_t GetTotalCount();
    void RegisterListenerFunc(const sptr<CJDataChangeListener>& listener);
    void UnRegisterListenerFunc(const sptr<CJDataChangeListener>& listener);
    void MarkLazyForEachProcess(const std::string& key);
    void ResetLazyForEachProcess();
    void RemoveChildGroupById(const std::string& composedId);
};

} // namespace Framework
} // namespace Ace
} // namespace OHOS

#endif // ACE_ENGINE_CJ_LAZYFOREACH_H
