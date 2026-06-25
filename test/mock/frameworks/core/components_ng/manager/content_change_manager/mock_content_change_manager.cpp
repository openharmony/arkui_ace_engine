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

#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
namespace OHOS::Ace::NG {
ContentChangeManager::ContentChangeManager(const RefPtr<TaskExecutor>& taskExecutor) {}
void ContentChangeManager::OnImageChangeEnd(const WeakPtr<FrameNode>&, const std::string&, const RectF&) {}
void ContentChangeManager::OnVsyncStart() {}
void ContentChangeManager::OnVsyncEnd(const RectF& rootRect) {}
std::string ContentChangeManager::DumpInfo() const
{
    return "ContentChangeManager: DumpInfo is not implemented in mock.";
}
} // namespace OHOS::Ace::NG
