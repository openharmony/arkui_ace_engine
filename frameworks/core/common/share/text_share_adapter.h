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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SHARE_TEXT_SHARE_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SHARE_TEXT_SHARE_ADAPTER_H

#include <string>

#include "base/geometry/ng/rect_t.h"
#include "interfaces/inner_api/ace/share/text_share_interface.h"

namespace OHOS::Ace {
class TextShareAdapter {
public:
    TextShareAdapter() = default;
    ~TextShareAdapter() = default;

    static void StartTextShareTask(const int32_t containerId, const NG::RectF& contentRect,
        const std::string& shareText);

    static uint64_t GetMaxTextShareLength();
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_SHARE_TEXT_SHARE_ADAPTER_H
