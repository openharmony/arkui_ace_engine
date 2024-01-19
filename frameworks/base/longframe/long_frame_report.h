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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LONGFRAME_LONG_FRAME_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LONGFRAME_LONG_FRAME_REPORT_H

#include "base/utils/macros.h"

namespace OHOS::Ace {
typedef void* EventReport;

class ACE_EXPORT ILongFrame final {
public:
    ILongFrame() = default;
    ~ILongFrame() = default;
    void ReportStartEvent();
    void ReportEndEvent();

private:
    EventReport reporter = nullptr;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LONGFRAME_LONG_FRAME_REPORT_H
