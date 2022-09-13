/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_MOUSESTYLE_MOUSE_STYLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_MOUSESTYLE_MOUSE_STYLE_MANAGER_H

#include "base/memory/ace_type.h"
#include "core/components/declaration/common/style.h"

namespace OHOS::Ace {

enum class MouseFormat : int32_t {
    DEFAULT = 0,        // Default mouse style
    WEST_EAST = 5,      // Drag left-right mouse style
    NORTH_SOUTH = 6,    // Drag up-down mouse style
    HAND_POINTING = 19, // Hyperlink mouse style
    TEXT_CURSOR = 26,   // Text editing mouse style
};

class ACE_EXPORT MouseStyle : public AceType {
    DECLARE_ACE_TYPE(MouseStyle, AceType)

public:
    static RefPtr<MouseStyle> CreateMouseStyle();

    virtual bool SetPointerStyle(int32_t windowId, MouseFormat pointerStyle) const = 0;
    virtual int32_t GetPointerStyle(int32_t windowId, int32_t& pointerStyle) const = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_MOUSESTYLE_MOUSE_STYLE_MANAGER_H