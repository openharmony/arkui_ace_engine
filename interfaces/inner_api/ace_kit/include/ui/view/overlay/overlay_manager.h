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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_OVERLAY_OVERLAY_MANAGER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_OVERLAY_OVERLAY_MANAGER_H

#include "ui/base/ace_type.h"
#include "ui/base/geometry/ng/offset_t.h"
#include "ui/base/macros.h"
#include "ui/properties/safe_area_insets.h"
#include "ui/view/frame_node.h"
#include "ui/view/ui_context.h"

namespace OHOS::Ace::Kit {

class OverlayManager : public AceType {
    DECLARE_ACE_TYPE(OverlayManager, AceType);
public:
    // dialogs
    virtual void CloseDialog(RefPtr<FrameNode>& dialogNode) = 0;

    // menus
    virtual void ShowMenu(const int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode>& menu) = 0;

    // safeArea
    virtual NG::SafeAreaInsets GetSafeAreaInsets(
        const RefPtr<FrameNode>& frameNode, bool useCurrentWindow = false) = 0;
};
} // OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_OVERLAY_OVERLAY_MANAGER_H