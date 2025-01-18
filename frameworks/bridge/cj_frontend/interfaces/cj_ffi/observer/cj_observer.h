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

#ifndef OHOS_CJ_OBSERVER_H
#define OHOS_CJ_OBSERVER_H

#include <map>
#include <string>

namespace OHOS {
namespace Rosen {

class ObserverProcess {
public:
    ObserverProcess();
    ~ObserverProcess() = default;
    static ObserverProcess& GetInstance();

    void ProcessScrollEventRegister(int64_t callbackId);
    void ProcessScrollEventUnRegister(int64_t callbackId);
    void ProcessScrollEventRegisterWithOptions(const char* options, int64_t callbackId);
    void ProcessScrollEventUnRegisterWithOptions(const char* options, int64_t callbackId);
    void ProcessTabContentUpdateRegister(int64_t callbackId);
    void ProcessTabContentUpdateUnRegister(int64_t callbackId);
    void ProcessTabContentUpdateRegisterWithOptions(const char* options, int64_t callbackId);
    void ProcessTabContentUpdateUnRegisterWithOptions(const char* options, int64_t callbackId);

private:
    bool isScrollEventChangeFuncSetted_ = false;
    bool isTabContentUpdateFuncSetted_ = false;
};

} // namespace Rosen
} // namespace OHOS

#endif // OHOS_CJ_OBSERVER_H