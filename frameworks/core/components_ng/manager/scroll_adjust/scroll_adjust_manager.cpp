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

#include "core/components_ng/manager/scroll_adjust/scroll_adjust_manager.h"

#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include <iostream>

namespace OHOS::Ace::NG {

ScrollAdjustmanager& ScrollAdjustmanager::GetInstance()
{
    static ScrollAdjustmanager scrollAdjustmanager;
    return scrollAdjustmanager;
}

bool ScrollAdjustmanager::ChangeScrollStateIfNeed(ScrollState scrollState)
{
    if (!SystemProperties::IsWhiteBlockIdleChange()) {
        LOGD("ScrollAdjustmanager Idle Change is false");
        return false;
    }
    if ((scrollState == ScrollState::SCROLL && !idle_) ||
        (scrollState == ScrollState::FLING && idle_) ||
        (scrollState == ScrollState::IDLE && idle_)) {
        return  false;
    }
    if (scrollState == ScrollState::SCROLL && idle_) {
        LOGD("ScrollAdjustmanager ChangeScrollStateIfNeed return IDLE");
        idle_ = false;
        return true;
    }
    if ((scrollState == ScrollState::FLING && !idle_) ||
        (scrollState == ScrollState::IDLE && !idle_)) {
        idle_ = true;
    }
    return false;
}

int32_t ScrollAdjustmanager::AdjustEndIndex(int32_t endIndex)
{
    LOGD("ScrollAdjustmanager GetWhiteBlockIndexValue is %{public}d",
        SystemProperties::GetWhiteBlockIndexValue());
    return endIndex + SystemProperties::GetWhiteBlockIndexValue();
}

int32_t ScrollAdjustmanager::AdjustCachedCount(int32_t cachedCount)
{
    LOGD("ScrollAdjustmanager GetWhiteBlockCacheCountValue is %{public}d",
        SystemProperties::GetWhiteBlockCacheCountValue());
    return cachedCount + SystemProperties::GetWhiteBlockCacheCountValue();
}

}