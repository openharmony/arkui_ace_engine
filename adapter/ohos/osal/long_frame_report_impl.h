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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_LONG_FRAME_REPORT_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_LONG_FRAME_REPORT_IMPL_H

#include "base/longframe/long_frame_report.h"
#include "ffrt.h"

namespace OHOS::Ace {
class LongFrameReportImpl {
public:
    LongFrameReportImpl();
    ~LongFrameReportImpl() = default;
    void SubmitEvent();
    void CancelEvent();

    std::unique_ptr<ffrt::queue> ffrtTaskQueue = nullptr;
    ffrt::task_handle ffrtTask;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_LONG_FRAME_REPORT_IMPL_H

