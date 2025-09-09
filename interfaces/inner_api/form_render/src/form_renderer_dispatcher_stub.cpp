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
#include "form_renderer_dispatcher_stub.h"
#include <transaction/rs_transaction.h>

#include "form_renderer_hilog.h"

namespace OHOS {
namespace Ace {
FormRendererDispatcherStub::FormRendererDispatcherStub()
{
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_POINTER_EVENT)] =
        &FormRendererDispatcherStub::HandleDispatchPointerEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_ALLOW_UPDATE)] =
        &FormRendererDispatcherStub::HandleSetAllowUpdate;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::DISPATCH_SURFACE_CHANGE_EVENT)] =
        &FormRendererDispatcherStub::HandleDispatchSurfaceChangeEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_OBSCURED)] =
        &FormRendererDispatcherStub::HandleSetObscured;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_CHILD_TREE_REGISTER)] =
        &FormRendererDispatcherStub::HandleOnAccessibilityChildTreeRegister;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_CHILD_TREE_DEREGISTER)] =
        &FormRendererDispatcherStub::HandleOnAccessibilityChildTreeDeregister;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_DUMP_CHILD_INFO)] =
        &FormRendererDispatcherStub::HandleOnAccessibilityDumpChildInfo;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::ACCESSIBILITY_TRANSFER_HOVER_EVENT)] =
        &FormRendererDispatcherStub::HandleOnAccessibilityTransferHoverEvent;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::NOTIFY_DUMP_INFO)] =
        &FormRendererDispatcherStub::HandleOnNotifyDumpInfo;
    memberFuncMap_[static_cast<uint32_t>(IFormRendererDispatcher::Message::SET_MULTI_INSTANCE_ENABLED)] =
        &FormRendererDispatcherStub::HandleSetMultiInstanceEnabled;
}

FormRendererDispatcherStub::~FormRendererDispatcherStub()
{
    memberFuncMap_.clear();
}

int32_t FormRendererDispatcherStub::OnRemoteRequest(
    uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    HILOG_DEBUG("FormRendererDispatcherStub::OnReceived, code = %{public}u, flags= %{public}d.",
        code, option.GetFlags());
    std::u16string descriptor = FormRendererDispatcherStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (descriptor != remoteDescriptor) {
        HILOG_ERROR("%{public}s failed, local descriptor is not equal to remote", __func__);
        return ERR_INVALID_VALUE;
    }

    auto itFunc = memberFuncMap_.find(code);
    if (itFunc != memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            return (this->*memberFunc)(data, reply);
        }
    }

    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
}

int32_t FormRendererDispatcherStub::HandleDispatchPointerEvent(MessageParcel &data, MessageParcel &reply)
{
    std::shared_ptr<MMI::PointerEvent> pointerEvent = MMI::PointerEvent::Create();
    if (pointerEvent == nullptr) {
        HILOG_ERROR("%{public}s, Create Pointer Event failed.", __func__);
        return ERR_INVALID_VALUE;
    }

    if (!pointerEvent->ReadFromParcel(data)) {
        HILOG_ERROR("%{public}s, Read Pointer Event failed.", __func__);
        return ERR_INVALID_VALUE;
    }
    SerializedGesture serializedGesture;
    DispatchPointerEvent(pointerEvent, serializedGesture);
    reply.WriteInt32(serializedGesture.data.size());
    reply.WriteRawData(serializedGesture.data.data(), serializedGesture.data.size());
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleSetAllowUpdate(MessageParcel &data, MessageParcel &reply)
{
    bool allowUpdate = data.ReadBool();
    SetAllowUpdate(allowUpdate);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleDispatchSurfaceChangeEvent(MessageParcel& data, MessageParcel& reply)
{
    OHOS::AppExecFwk::FormSurfaceInfo* formSurfaceInfo =
        data.ReadParcelable<OHOS::AppExecFwk::FormSurfaceInfo>();
    if (formSurfaceInfo == nullptr) {
        HILOG_ERROR("Read formSurfaceInfo failed");
        return ERR_INVALID_VALUE;
    }
    uint32_t reason = static_cast<uint32_t>(data.ReadUint32());
    bool hasRSTransaction = data.ReadBool();
    std::shared_ptr<Rosen::RSTransaction> transaction = nullptr;
    if (hasRSTransaction) {
        std::shared_ptr<Rosen::RSTransaction> transactionTmp(data.ReadParcelable<Rosen::RSTransaction>());
        transaction = transactionTmp;
    }
    DispatchSurfaceChangeEvent(*formSurfaceInfo, reason, transaction);
    reply.WriteInt32(ERR_OK);
    delete formSurfaceInfo;
    return ERR_OK;
}


int32_t FormRendererDispatcherStub::HandleSetObscured(MessageParcel &data, MessageParcel &reply)
{
    bool isObscured = data.ReadBool();
    SetObscured(isObscured);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleOnAccessibilityChildTreeRegister(MessageParcel &data, MessageParcel &reply)
{
    uint32_t windowId = data.ReadUint32();
    int32_t treeId = data.ReadInt32();
    int64_t accessibilityId = data.ReadInt64();
    OnAccessibilityChildTreeRegister(windowId, treeId, accessibilityId);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleOnAccessibilityChildTreeDeregister(MessageParcel &data, MessageParcel &reply)
{
    OnAccessibilityChildTreeDeregister();
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleOnAccessibilityDumpChildInfo(MessageParcel &data, MessageParcel &reply)
{
    std::vector<std::string> params;
    if (!data.ReadStringVector(&params)) {
        HILOG_ERROR("%{public}s, Read params failed.", __func__);
        return ERR_INVALID_VALUE;
    }
    std::vector<std::string> info;
    OnAccessibilityDumpChildInfo(params, info);
    reply.WriteStringVector(info);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleOnAccessibilityTransferHoverEvent(MessageParcel &data, MessageParcel &reply)
{
    float pointX = 0;
    float pointY = 0;
    int32_t sourceType = 0;
    int32_t eventType = 0;
    int64_t timeMs = 0;
    if (!data.ReadFloat(pointX) ||
        !data.ReadFloat(pointY) ||
        !data.ReadInt32(sourceType) ||
        !data.ReadInt32(eventType) ||
        !data.ReadInt64(timeMs)) {
        HILOG_ERROR("Read HandleTransferAccessibilityHoverEvent data failed!");
        return ERR_INVALID_VALUE;
    };
    OnAccessibilityTransferHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
    reply.WriteInt32(ERR_OK);
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleOnNotifyDumpInfo(MessageParcel &data, MessageParcel &reply)
{
    std::vector<std::string> params;
    if (!data.ReadStringVector(&params)) {
        HILOG_ERROR("%{public}s, Read params failed.", __func__);
        return ERR_INVALID_VALUE;
    }
    std::vector<std::string> info;
    OnNotifyDumpInfo(params, info);
    if (!reply.WriteStringVector(info)) {
        HILOG_ERROR("WriteStringVector<dumpInfos> failed");
        return ERR_INVALID_VALUE;
    }
    return ERR_OK;
}

int32_t FormRendererDispatcherStub::HandleSetMultiInstanceEnabled(MessageParcel &data, MessageParcel &reply)
{
    bool isMultiInstanceEnabled = data.ReadBool();
    SetMultiInstanceEnabled(isMultiInstanceEnabled);
    if (!reply.WriteInt32(ERR_OK)) {
        HILOG_ERROR("Write result failed");
    }
    return ERR_OK;
}
}  // namespace Ace
}  // namespace OHOS