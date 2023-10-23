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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_SCROLL_NOTIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_SCROLL_NOTIFIER_H

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class SelectOverlayScrollNotifier {
public:
    static inline void NotifyOnScrollCallback(WeakPtr<ScrollablePattern> pattern, float offset, int32_t source)
    {
        NotifyOnScrollEvent(pattern, offset, source);
    }

    static inline void NotifyOnScrollEnd(WeakPtr<ScrollablePattern> pattern)
    {
        NotifyOnScrollEvent(pattern, 0, -1);
    }

    static inline void NotifyOnScrollEvent(WeakPtr<ScrollablePattern> pattern, float offset, int32_t source)
    {
        auto scrollablePattern = pattern.Upgrade();
        CHECK_NULL_VOID(scrollablePattern);
        auto host = scrollablePattern->GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        context->GetSelectOverlayManager()->NotifyOnScrollCallback(
            host->GetId(), scrollablePattern->GetAxis(), offset, source);
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_OVERLAY_SELECT_OVERLAY_SCROLL_NOTIFIER_H
