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

#ifndef INTERFACES_ETS_ANI_PROMPTACTION_SRC_PROMPT_ACTION_CONTROLLER_H
#define INTERFACES_ETS_ANI_PROMPTACTION_SRC_PROMPT_ACTION_CONTROLLER_H

#include <ani.h>
#include <cstddef>
#include <string>

#include "frameworks/core/common/container_consts.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/dialog/dialog_pattern.h"

namespace OHOS::Ace::Ani {

class PromptActionController {
public:
    PromptActionController() = default;
    virtual ~PromptActionController() = default;

    void SetNode(const WeakPtr<NG::FrameNode> node)
    {
        node_ = node;
        auto dialogNode = node_.Upgrade();
        CHECK_NULL_VOID(dialogNode);
        auto pattern = dialogNode->GetPattern<NG::DialogPattern>();
        CHECK_NULL_VOID(pattern);
        if (PromptActionCommonState::UNINITIALIZED == pattern->GetState()) {
            pattern->SetState(PromptActionCommonState::INITIALIZED);
            TAG_LOGI(AceLogTag::ACE_DIALOG, "The current state of the dialog is INITIALIZED.");
        }
        hasBind_ = true;
    }
    virtual void Close() {};

    virtual PromptActionCommonState GetState()
    {
        return PromptActionCommonState::UNINITIALIZED;
    }
protected:
    WeakPtr<NG::FrameNode> node_;
    bool hasBind_ = false;
};

class PromptActionDialogController : public PromptActionController {
public:
    PromptActionDialogController() = default;
    ~PromptActionDialogController() override = default;

    void Close() override;
    PromptActionCommonState GetState() override;
};

ani_long ANICreateDialogController(ani_env* env, ani_object object);
void ANICloseDialog(ani_env* env, ani_object object);
ani_enum_item ANIDialogControllerGetState(ani_env* env, ani_object object);
void ANICleanDialogController(ani_env* env, ani_object object);
ani_status BindDialogController(ani_env* env);
ani_status BindCommonController(ani_env* env);
bool GetDialogController(ani_env* env, ani_object object,
    std::function<void(RefPtr<NG::FrameNode> dialogNode)>& result);

class DismissDialogAction {
public:
    DismissDialogAction() = default;
    ~DismissDialogAction() = default;

    void SetInstanceId(const int32_t instanceId)
    {
        instanceId_ = instanceId;
    }

    void Dismiss();

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
};

void ANIDismissDialog(ani_env* env, ani_object object);
ani_status BindDismissDialogAction(ani_env* env);
ani_object ANICreateDismissDialogAction(ani_env* env, const int32_t reason, const int32_t instanceId);

} // OHOS::Ace::Ani

#endif // INTERFACES_ETS_ANI_PROMPTACTION_SRC_PROMPT_ACTION_CONTROLLER_H
