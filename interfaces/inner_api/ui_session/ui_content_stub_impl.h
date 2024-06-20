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

#ifndef FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_IMPL_H
#define FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_IMPL_H

#include <singleton.h>

#include "iremote_object.h"
#include "ui_content_errors.h"
#include "ui_content_stub.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UIContentServiceStubImpl : public UiContentStub {
private:
    int32_t OnGetInspectorTreeInner(MessageParcel& data, MessageParcel& reply, MessageOption& option) override;
    int32_t OnReportUnfocusEventInner(MessageParcel& data, MessageParcel& reply, MessageOption& option) override;
    int32_t RegisterRemoteObjectInner(MessageParcel& data, MessageParcel& reply, MessageOption& option) override;

    sptr<IRemoteObject> SAObject_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_IMPL_H
