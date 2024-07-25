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

#include "core/components_ng/pattern/navigation/navigation_event_hub.h"

#include "core/components_ng/pattern/navigation/navigation_group_node.h"

namespace OHOS::Ace::NG {
void NavigationEventHub::FireOnAppear()
{
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(GetFrameNode());
    CHECK_NULL_VOID(navigationNode);
    auto pagePath = navigationNode->GetNavigationPathInfo();
    ACE_SCOPED_TRACE_COMMERCIAL("Navigation Main Page: %s", pagePath.c_str());
    EventHub::FireOnAppear();
}
} // namespace OHOS::Ace::NG