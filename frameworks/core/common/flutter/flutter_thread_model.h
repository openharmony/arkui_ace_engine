/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMMON_FLUTTER_FLUTTER_THREAD_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_COMMON_FLUTTER_FLUTTER_THREAD_MODEL_H

#include <memory>

#include "flutter/common/task_runners.h"
#include "flutter/shell/common/thread_host.h"

#include "base/utils/noncopyable.h"

namespace OHOS::Ace {

class FlutterThreadModel {
public:
    FlutterThreadModel(flutter::ThreadHost threadHost, flutter::TaskRunners taskRunners);
    ~FlutterThreadModel() = default;

    static std::unique_ptr<FlutterThreadModel> CreateThreadModel(
        bool useCurrentEventRunner, bool hasUiThread, bool useGpuThread);

    const flutter::TaskRunners& GetTaskRunners() const
    {
        return taskRunners_;
    }

private:
    const flutter::ThreadHost threadHost_;
    const flutter::TaskRunners taskRunners_;

    ACE_DISALLOW_COPY_AND_MOVE(FlutterThreadModel);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_COMMON_FLUTTER_FLUTTER_THREAD_MODEL_H
