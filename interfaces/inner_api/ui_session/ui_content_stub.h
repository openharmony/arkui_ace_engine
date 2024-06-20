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
    virtual int32_t OnGetInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option) = 0;
    virtual int32_t OnReportUnfocusEventInner(MessageParcel& data, MessageParcel& reply, MessageOption& option) = 0;
    virtual int32_t RegisterRemoteObjectInner(MessageParcel& data, MessageParcel& reply, MessageOption& option) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_H