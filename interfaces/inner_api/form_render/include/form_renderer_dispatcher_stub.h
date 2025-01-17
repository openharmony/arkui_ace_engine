/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_STUB_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_STUB_H

#include <map>

#include "base/utils/macros.h"
#include "form_renderer_dispatcher_interface.h"
#include "iremote_object.h"
#include "iremote_stub.h"

namespace OHOS {
namespace Ace {
/**
 * @class FormRendererDispatcherStub
 * Form render service stub.
 */
class ACE_EXPORT FormRendererDispatcherStub : public IRemoteStub<IFormRendererDispatcher> {
public:
    FormRendererDispatcherStub();
    virtual ~FormRendererDispatcherStub();
    /**
     * @brief handle remote request.
     * @param data input param.
     * @param reply output param.
     * @param option message option.
     * @return Returns ERR_OK on success, others on failure.
     */
    virtual int32_t OnRemoteRequest(
        uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option);

private:
    int32_t HandleDispatchPointerEvent(MessageParcel &data, MessageParcel &reply);
    int32_t HandleSetAllowUpdate(MessageParcel &data, MessageParcel &reply);
    int32_t HandleDispatchSurfaceChangeEvent(MessageParcel &data, MessageParcel &reply);
    int32_t HandleSetObscured(MessageParcel &data, MessageParcel &reply);
    int32_t HandleOnAccessibilityChildTreeRegister(MessageParcel &data, MessageParcel &reply);
    int32_t HandleOnAccessibilityChildTreeDeregister(MessageParcel &data, MessageParcel &reply);
    int32_t HandleOnAccessibilityDumpChildInfo(MessageParcel &data, MessageParcel &reply);
    int32_t HandleOnAccessibilityTransferHoverEvent(MessageParcel &data, MessageParcel &reply);
    using FormRendererDispatcherFunc =
        int32_t (FormRendererDispatcherStub::*)(MessageParcel &data, MessageParcel &reply);
    std::map<uint32_t, FormRendererDispatcherFunc> memberFuncMap_;

    DISALLOW_COPY_AND_MOVE(FormRendererDispatcherStub);
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_FORM_RENDERER_DISPATCHER_STUB_H
