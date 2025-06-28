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

#include "core/components_ng/base/interop/view_stack_processor_interop.h"
 
namespace OHOS::Ace::NG {
void InteropViewStackProcessor::Init(int32_t containerId)
{
    std::swap(instance_, OHOS::Ace::NG::ViewStackProcessor::instance);
    OHOS::Ace::NG::ViewStackProcessor::GetInstance()->SetRebuildContainerId(containerId);
}

void InteropViewStackProcessor::SwapViewStackProcessor(std::unique_ptr<OHOS::Ace::NG::ViewStackProcessor>& instance)
{
    std::swap(instance, OHOS::Ace::NG::ViewStackProcessor::instance);
}

InteropViewStackProcessor::InteropViewStackProcessor(int32_t containerId)
{
    Init(containerId);
}

InteropViewStackProcessor::InteropViewStackProcessor(std::unique_ptr<OHOS::Ace::NG::ViewStackProcessor>& instance,
    int32_t containerId)
{
    std::swap(instance_, instance);
    Init(containerId);
}

InteropViewStackProcessor::~InteropViewStackProcessor()
{
    OHOS::Ace::NG::ViewStackProcessor::GetInstance()->SetRebuildContainerId(OHOS::Ace::INSTANCE_ID_UNDEFINED);
    std::swap(instance_, OHOS::Ace::NG::ViewStackProcessor::instance);
}
} // namespace OHOS::Ace::NG