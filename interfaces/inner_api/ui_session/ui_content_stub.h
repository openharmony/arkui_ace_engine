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

#ifndef FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_H
#define FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_H

#include <iremote_object.h>
#include <iremote_stub.h>

#include "ui_content_service_interface.h"

namespace OHOS::Ace {
class UiContentStub : public IRemoteStub<IUiContentService> {
public:
    virtual int32_t OnRemoteRequest(
        uint32_t code, MessageParcel& data, MessageParcel& reply, MessageOption& option) override;

private:
    int32_t GetInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t ConnectInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t RegisterClickEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t RegisterRouterChangeEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t RegisterSearchEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t RegisterComponentChangeEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t RegisterWebUnfocusEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t SendCommandInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t SendCommandInnerAsync(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t SendCommandKeyCodeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t UnregisterClickEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t UnregisterSearchEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t UnregisterRouterChangeEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t UnregisterComponentChangeEventCallbackInner(
        MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t UnregisterWebUnfocusEventCallbackInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t ResetTranslateTextAllInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t ResetTranslateTextInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t GetWebViewCurrentLanguageInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t GetWebViewTranslateTextInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t StartWebViewTranslateInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t SendTranslateResultInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t SendTranslateResultStrInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t GetCurrentPageNameInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t EndWebViewTranslateInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t GetCurrentImagesShowingInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
    int32_t GetVisibleInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_H
