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


#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_INTEROP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_INTEROP_H
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT InteropViewStackProcessor final : public Referenced {
public:
    InteropViewStackProcessor(int32_t containerId = OHOS::Ace::INSTANCE_ID_UNDEFINED);
    InteropViewStackProcessor(std::unique_ptr<OHOS::Ace::NG::ViewStackProcessor>& instance,
        int32_t containerId = OHOS::Ace::INSTANCE_ID_UNDEFINED);
    ~InteropViewStackProcessor();
    void SwapViewStackProcessor(std::unique_ptr<OHOS::Ace::NG::ViewStackProcessor>& instance);

private:
    void Init(int32_t containerId);
    std::unique_ptr<OHOS::Ace::NG::ViewStackProcessor> instance_;

    ACE_DISALLOW_COPY_AND_MOVE(InteropViewStackProcessor);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_INTEROP_H