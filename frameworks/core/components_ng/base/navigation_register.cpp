/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 
#include "core/components_ng/base/navigation_register.h"
 
namespace OHOS::Ace::NG {
thread_local NavigationRegister* NavigationRegister::instance_ = nullptr;
 
NavigationRegister *NavigationRegister::GetInstance()
{
    if (NavigationRegister::instance_ == nullptr) {
        NavigationRegister::instance_ = new NavigationRegister();
    }
    return NavigationRegister::instance_;
}
 
RefPtr<NavigationGroupNode> NavigationRegister::GetOrCreateGroupNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    return NavigationGroupNode::GetOrCreateGroupNode(tag, nodeId, patternCreator);
}
}