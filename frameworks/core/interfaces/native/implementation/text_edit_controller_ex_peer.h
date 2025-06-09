/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_EDIT_CONTROLLER_EX_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_EDIT_CONTROLLER_EX_PEER_H

#include "core/interfaces/native/implementation/text_base_controller_peer.h"

struct TextEditControllerExPeer : public TextBaseControllerPeer {
    virtual ~TextEditControllerExPeer() = default;
    virtual bool IsEditing() = 0;
    virtual void StopEditing() = 0;
    virtual bool SetCaretOffset(int32_t offset) = 0;
    virtual int32_t GetCaretOffset() = 0;
    virtual OHOS::Ace::PreviewTextInfo GetPreviewText() = 0;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_TEXT_EDIT_CONTROLLER_EX_PEER_H