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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INPUT_COMPATIBLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INPUT_COMPATIBLE_MANAGER_H

#include "ui/event/input_compatible_policy.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
class InputCompatibleManager final : public std::enable_shared_from_this<InputCompatibleManager>,
                                     public NonCopyable,
                                     public AceType {
public:
    static InputCompatibleManager& GetInstance();
    void LoadProductCompatiblePolicy();
    void UnloadProductCompatiblePolicy();
    virtual ~InputCompatibleManager();
    bool IsCompatibleConvertingEnabledFor(Kit::InputCompatibleSource source);

private:
    void Close();
    Kit::InputCompatiblePolicy* productPolicy_ = nullptr;
    void* libraryHandle_ = nullptr;
    bool transformSoLoaded_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_INPUT_COMPATIBLE_MANAGER_H
