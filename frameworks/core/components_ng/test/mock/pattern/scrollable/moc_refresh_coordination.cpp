/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scrollable/refresh_coordination.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> RefreshCoordination::FindRefreshNode() const
{
    return nullptr;
}

RefPtr<ScrollableCoordinationEvent> RefreshCoordination::CreateCoordinationEvent()
{
    return nullptr;
}

void RefreshCoordination::OnScrollStart(bool isDrag) const {}

bool RefreshCoordination::OnScroll(float offset) const
{
    return false;
}

void RefreshCoordination::OnScrollEnd(float speed) const {}
bool RefreshCoordination::IsRefreshInScroll() const
{
    return false;
}
} // namespace OHOS::Ace::NG