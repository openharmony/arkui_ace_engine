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

#pragma once

#undef UNITEST_FRIEND_CLASS
#define UNITEST_FRIEND_CLASS friend class FriendClassAccessor

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
class FriendClassAccessor {
public:
    template<typename T>
    static void OnUpdateOnCreateMenuCallback(SelectOverlayInfo& selectInfo, const T& pattern)
    {
        if (pattern) {
#ifdef WRONG_PRIVATE
            pattern->selectOverlay_->OnUpdateOnCreateMenuCallback(selectInfo);
#endif
        }
    }
};
}
