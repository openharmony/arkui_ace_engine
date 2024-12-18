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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TEXT_INPUT_CONTROLLER_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TEXT_INPUT_CONTROLLER_PEER_H

#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/interfaces/native/implementation/text_content_controller_base_peer.h"

struct TextInputControllerPeer : public TextContentControllerBasePeer {
    const TextFieldController& GetController() const
    {
        return controller_;
    }

    void SetController(const TextFieldController& controller)
    {
        controller_ = controller;
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TEXT_INPUT_CONTROLLER_PEER_H
