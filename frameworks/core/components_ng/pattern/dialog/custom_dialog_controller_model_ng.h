/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_CUSTOM_DIALOG_CONTROLLER_MODEL_NG_H

#include "core/components/dialog/dialog_component.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
enum class DialogOperation {
    DIALOG_OPEN = 0,
    DIALOG_CLOSE,
};

class ACE_EXPORT CustomDialogControllerMdoelNG : public OHOS::Ace::CustomDialogControllerMdoel {
public:
    CustomDialogControllerMdoelNG();
    void SetOpenDialog() override;
    void SetCloseDialog() override;
private:
    OHOS::Ace::RefPtr<OHOS::Ace::NG::OverlayManager> overlayManager;
    std::vector<WeakPtr<NG::FrameNode>> dialogs_;
    DialogProperties dialogProperties_;
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_DIALOG_JS_CUSTOM_DIALOG_CONTROLLER_H