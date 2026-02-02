/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_UI_SESSION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_UI_SESSION_ADAPTER_H
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
enum class SwiperCommand {
    INVALID = 0,
    FORWARD,
    BACKWARD,
    INDEX
};

/* implements AI adapter functions for SwiperPattern */
class SwiperUISessionAdapter {
public:
    SwiperUISessionAdapter() = delete;
    explicit SwiperUISessionAdapter(RefPtr<OHOS::Ace::NG::SwiperPattern> pattern) : pattern_(pattern) {};

    int32_t OnInjectionEvent(const std::string& command);

    const char* GetScrollAbility();

private:
    SwiperCommand ParseCommand(const std::string& command);
    int32_t ParseIndexFromCommand(const std::string& command);
    void ReportComponentChangeEvent(bool result, SwiperCommand type);

    RefPtr<OHOS::Ace::NG::SwiperPattern> pattern_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_UI_SESSION_ADAPTER_H