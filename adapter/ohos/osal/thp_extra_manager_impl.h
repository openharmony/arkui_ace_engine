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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_THP_EXTRA_MANAGER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_THP_EXTRA_MANAGER_IMPL_H

#include "base/memory/ace_type.h"
#include "frameworks/core/common/thp_extra_manager.h"

namespace OHOS::Ace::NG {
    typedef const char* (*ThpExtraRunCommandFunc)(const char* command, const char* parameters);
    typedef const char* (*ThpExtraGetConfigStrFunc)(void);
class THPExtraManagerImpl : public THPExtraManager {
public:
    THPExtraManagerImpl() = default;
    ~THPExtraManagerImpl() override = default;
    bool Init(void) override;
    const char* ThpExtraRunCommand(const char* command, const char* parameters) override;
    int32_t GetHeight(void) const override;
    int32_t GetWidth(void) const override;
private:
    static void* lib_;
    bool enable_ = false;
    int32_t height_ = 0;
    int32_t width_ = 0;
    const char* (*ThpExtraRunCommand_)(const char* command, const char* parameters) {};
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_THP_EXTRA_MANAGER_IMPL_H
