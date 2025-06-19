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

#include "adapter/ohos/osal/image_perf_ohos.h"

#include <cinttypes>

#include "base/image/image_perf.h"
#include "base/log/log_wrapper.h"
#include "perf_monitor_adapter.h"

namespace OHOS::Ace {
ImagePerf* ImagePerf::GetPerfMonitor()
{
    static ImagePerfOhos instance;
    return &instance;
}

void ImagePerfOhos::StartRecordImageLoadStat(int64_t id)
{
    HiviewDFX::PerfMonitorAdapter::GetInstance().StartRecordImageLoadStat(id);
    LOGD("ImagePerfOhos::StartRecordImageLoadStat id: %{public}" PRId64 "", id);
}

void ImagePerfOhos::EndRecordImageLoadStat(
    int64_t id, const std::string& imageType, std::pair<int, int> size, int state)
{
    HiviewDFX::PerfMonitorAdapter::GetInstance().EndRecordImageLoadStat(id, size, imageType, state);
    LOGD("ImagePerfOhos::EndRecordImageLoadStat id: %{public}" PRId64
         ", imageType: %{public}s, width: %{public}d, height: %{public}d, state: %{public}d",
        id, imageType.c_str(), size.first, size.second, state);
}
} // namespace OHOS::Ace
