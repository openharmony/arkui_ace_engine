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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_OVERLAY_OVERLAY_MANAGER_IMPL_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_OVERLAY_OVERLAY_MANAGER_IMPL_H

#include "ui/view/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
class PipelineContext;
class OverlayManager;
}

namespace OHOS::Ace::Kit {

class OverlayManagerImpl : public OverlayManager {
    DECLARE_ACE_TYPE(OverlayManagerImpl, OverlayManager);
public:
    OverlayManagerImpl(NG::PipelineContext* context);
    ~OverlayManagerImpl();

    void Reset();

    void CloseDialog(RefPtr<FrameNode>& dialogNode) override;

    void ShowMenu(const int32_t targetId, const NG::OffsetF& offset, RefPtr<FrameNode>& menu) override;
private:
    NG::OverlayManager* overlayManager_ = nullptr;
};
} // OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_OVERLAY_OVERLAY_MANAGER_IMPL_H