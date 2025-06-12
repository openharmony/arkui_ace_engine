/*
 * Copyright (c) 2025-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/whiteblock/whiteblock_manager.h"

#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include <iostream>

namespace OHOS::Ace::NG {

WhiteBlockManager& WhiteBlockManager::GetInstance()
{
    static WhiteBlockManager whiteBlockManager;
    return whiteBlockManager;
}

ScrollState WhiteBlockManager::ChangeScrollStateIfNeed(ScrollState scrollState)
{
    if (!SystemProperties::IsWhiteBlockIdleChange()) {
        LOGD("WhiteBlockManager Idle Change is false");
        return scrollState;
    }
    if ((scrollState == ScrollState::SCROLL && !idle_) ||
        (scrollState == ScrollState::FLING && idle_) ||
        (scrollState == ScrollState::IDLE && idle_)) {
        return  scrollState;
    }
    if (scrollState == ScrollState::SCROLL && idle_) {
        LOGD("WhiteBlockManager ChangeScrollStateIfNeed return IDLE");
        idle_ = false;
        return ScrollState::IDLE;
    }
    if ((scrollState == ScrollState::FLING && !idle_) ||
        (scrollState == ScrollState::IDLE && !idle_)) {
        idle_ = true;
    }
    return scrollState;
}

int32_t WhiteBlockManager::AdjustEndIndex(int32_t endIndex)
{
    LOGD("WhiteBlockManager GetWhiteBlockIndexValue is %{public}s",
    SystemProperties::GetWhiteBlockIndexValue().c_str());
    return endIndex + SystemProperties::GetWhiteBlockIndexValue();
}

int32_t WhiteBlockManager::AdjustCachedCount(int32_t cachedCount)
{
    LOGD("WhiteBlockManager GetWhiteBlockCacheCountValue is %{public}s",
    SystemProperties::GetWhiteBlockCacheCountValue().c_str());
    return cachedCount + SystemProperties::GetWhiteBlockCacheCountValue();
}

}