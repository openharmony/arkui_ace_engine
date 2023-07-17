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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

/**
 * The structure of Atomic Service (install free):
 * |--AtomicService(Column)
 *   |--AppBar(Row)
 *
 *   |--Stage
 *     |--Page
 */

class ACE_EXPORT AppBarView {
public:
    static RefPtr<FrameNode> Create(RefPtr<FrameNode>& content);

private:
    static RefPtr<FrameNode> BuildBarTitle();
    static RefPtr<FrameNode> BuildIconButton(
        InternalResource::ResourceId icon, GestureEventFunc&& clickCallback, bool isBackButton);
    static void BindContentCover(int32_t targetId);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_APP_BAR_VIEW_H
