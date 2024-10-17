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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_THP_EXTRA_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_THP_EXTRA_MANAGER_H

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
class THPExtraManager : public virtual AceType {
    DECLARE_ACE_TYPE(THPExtraManager, AceType)
public:
    THPExtraManager() = default;
    virtual ~THPExtraManager() = default;
    virtual bool Init(void) = 0;
    virtual const char* ThpExtraRunCommand(const char* command, const char* parameters) = 0;
    virtual int32_t GetHeight(void) const = 0;
    virtual int32_t GetWidth(void) const = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_THP_EXTRA_MANAGER_H
