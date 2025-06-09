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

#include "base/log/log.h"
#include "core/components_ng/manager/whiteblock/whiteblock_manager.h"
#include "parameter.h"
#include "parameters.h"
#include <iostream>

namespace OHOS::Ace::NG {
namespace {
const std::string WHITE_BLOCK_PARAM_INDEX = "performance.enhance.whiteblock.index";
const std::string WHITE_BLOCK_PARAM_IDLE = "performance.enhance.whiteblock.idle";
const std::string WHITE_BLOCK_PARAM_CACHED_COUNT = "performance.enhance.whiteblock.cachedcount";
const std::string WHITE_BLOCK_SITWCH_OPEN = "1";
const std::string WHITE_BLOCK_SITWCH_CLOSE = "0";
const std::string WHITE_BLOCK_PARAM_INDEX_DEFAULT = "0";
} //namespace

WhiteBlockManager& WhiteBlockManager::GetInstance()
{
    static WhiteBlockManager whiteBlockManager;
    return whiteBlockManager;
}

ScrollState WhiteBlockManager::ChangeScrollStateIfNeed(ScrollState scrollState)
{
    if (!GetSwitch()) {
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

bool WhiteBlockManager::GetSwitch()
{
    std::string whiteBlockParamValue = OHOS::system::GetParameter(WHITE_BLOCK_PARAM_IDLE, WHITE_BLOCK_SITWCH_CLOSE);
    return whiteBlockParamValue == WHITE_BLOCK_SITWCH_OPEN;
}

int32_t WhiteBlockManager::AdjustEndIndex(int32_t endIndex)
{
    return endIndex + std::stoi(OHOS::system::GetParameter(WHITE_BLOCK_PARAM_INDEX, WHITE_BLOCK_PARAM_INDEX_DEFAULT));
}

int32_t WhiteBlockManager::AdjustCachedCount(int32_t cachedCount)
{
    return cachedCount + std::stoi(OHOS::system::GetParameter(WHITE_BLOCK_PARAM_CACHED_COUNT,
    WHITE_BLOCK_PARAM_INDEX_DEFAULT));
}

}