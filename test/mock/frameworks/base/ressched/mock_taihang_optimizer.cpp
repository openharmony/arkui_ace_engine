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

#include "base/ressched/taihang_optimizer.h"

namespace OHOS::Ace {
void TaihangOptimizer::Init()
{
}

bool TaihangOptimizer::IsInited()
{
    return false;
}

void TaihangOptimizer::SetEnable(bool value)
{
}

bool TaihangOptimizer::IsEnable()
{
    return false;
}

bool TaihangOptimizer::CheckSwiperPageValid(const std::string& pageNames)
{
    return true;
}

void TaihangOptimizer::ComponentPreMake(const std::unordered_map<std::string, std::string> extInfo)
{
}

void TaihangOptimizer::HandleSwiperPreMake(const std::unordered_map<std::string, std::string> extInfo)
{
}

void TaihangOptimizer::PostSwiperPreMakeTask(RefPtr<NG::FrameNode>& node, int32_t index)
{
}

void TaihangOptimizer::ParseReplyPages(const std::unordered_map<std::string, std::string>& reply)
{
}
} // namespace OHOS::Ace
