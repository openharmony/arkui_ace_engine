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
#include "form_renderer_dispatcher_impl.h"
#include <transaction/rs_interfaces.h>
#include <transaction/rs_transaction.h>
#include "base/log/ace_trace.h"

#include "form_renderer.h"
#include "form_renderer_hilog.h"
#include "wm_common.h"

namespace OHOS {
namespace Ace {
constexpr int32_t PROCESS_WAIT_TIME = 20;
constexpr float DOUBLE = 2.0;
constexpr int32_t DEFAULT_FORM_ROTATION_ANIM_DURATION = 600;
FormRendererDispatcherImpl::FormRendererDispatcherImpl(
    const std::shared_ptr<UIContent> uiContent,
    const std::shared_ptr<FormRenderer> formRenderer,
    std::weak_ptr<OHOS::AppExecFwk::EventHandler> eventHandler)
    : uiContent_(uiContent), formRenderer_(formRenderer), eventHandler_(eventHandler)
{}

std::recursive_mutex FormRendererDispatcherImpl::globalLock_;

void FormRendererDispatcherImpl::DispatchPointerEvent(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent,
    SerializedGesture& serializedGesture)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }
    serializedGesture.data.clear();

    if (pointerEvent && pointerEvent->GetPointerAction() == OHOS::MMI::PointerEvent::POINTER_ACTION_DOWN) {
        HILOG_INFO("renderer receive down event");
        auto uiContent = uiContent_.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }

        struct FormSerializedResultData {
            std::mutex mtx;
            std::condition_variable cv;
        };

        std::shared_ptr<FormSerializedResultData> serializedResultData = std::make_shared<FormSerializedResultData>();
        auto callback = [serializedResultData]() {
            std::unique_lock<std::mutex> lock(serializedResultData->mtx);
            serializedResultData->cv.notify_all();
        };
        {
            std::unique_lock<std::mutex> lock(serializedResultData->mtx);
            uiContent->ProcessPointerEventWithCallback(pointerEvent, callback);
            if (serializedResultData->cv.wait_for(lock, std::chrono::milliseconds(PROCESS_WAIT_TIME)) ==
                std::cv_status::timeout) {
                HILOG_ERROR("formRender ProcessPointerEvent dispatch timeout");
            } else {
                serializedGesture = uiContent->GetFormSerializedGesture();
            }
        }
    } else {
        handler->PostTask([content = uiContent_, pointerEvent]() {
            auto uiContent = content.lock();
            if (!uiContent) {
                HILOG_ERROR("uiContent is nullptr");
                return;
            }

            uiContent->ProcessPointerEvent(pointerEvent);
        });
    }
}

bool FormRendererDispatcherImpl::IsAllowUpdate()
{
    return allowUpdate_;
}

void FormRendererDispatcherImpl::SetAllowUpdate(bool allowUpdate)
{
    allowUpdate_ = allowUpdate;
}

void FormRendererDispatcherImpl::SetVisible(bool isVisible)
{
    isVisible_ = isVisible;
}

bool FormRendererDispatcherImpl::IsVisible()
{
    return isVisible_;
}

void FormRendererDispatcherImpl::DispatchSurfaceChangeEvent(float width, float height, uint32_t reason,
    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, float borderWidth)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }

    // form existed in Sceneboard window always get undefined sizeChangeReason, use Visible to control anim instead
    reason = isVisible_ ? static_cast<uint32_t>(Rosen::WindowSizeChangeReason::ROTATION) :
        static_cast<uint32_t>(Rosen::WindowSizeChangeReason::UNDEFINED);
    handler->PostTask([content = uiContent_, width, height, reason, rsTransaction, borderWidth, this]() {
        auto uiContent = content.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }

        HandleSurfaceChangeEvent(uiContent, width, height, reason, rsTransaction, borderWidth);
    });

    auto formRenderer = formRenderer_.lock();
    if (!formRenderer) {
        return;
    }
    formRenderer->OnSurfaceChange(width, height, borderWidth);
}

void FormRendererDispatcherImpl::HandleSurfaceChangeEvent(const std::shared_ptr<UIContent>& uiContent, float width,
    float height, uint32_t reason, const std::shared_ptr<Rosen::RSTransaction>& rsTransaction, float borderWidth)
{
    int32_t duration = DEFAULT_FORM_ROTATION_ANIM_DURATION;
    bool needSync = false;
    if (rsTransaction && rsTransaction->GetSyncId() > 0) {
        // extract high 32 bits of SyncId as pid
        auto SyncTransactionPid = static_cast<int32_t>(rsTransaction->GetSyncId() >> 32);
        if (rsTransaction->IsOpenSyncTransaction() || SyncTransactionPid != rsTransaction->GetParentPid()) {
            needSync = true;
        }
    }

    if (needSync) {
        duration = rsTransaction->GetDuration() ? rsTransaction->GetDuration() : duration;
        globalLock_.lock();
        Rosen::RSTransaction::FlushImplicitTransaction();
        rsTransaction->Begin();
    }
    Rosen::RSAnimationTimingProtocol protocol;
    protocol.SetDuration(duration);
    // animation curve: cubic [0.2, 0.0, 0.2, 1.0]
    auto curve = Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.2, 0.0, 0.2, 1.0);
    Rosen::RSNode::OpenImplicitAnimation(protocol, curve, []() {});
    
    float uiWidth = width - borderWidth * DOUBLE;
    float uiHeight = height - borderWidth * DOUBLE;
    uiContent->SetFormWidth(uiWidth);
    uiContent->SetFormHeight(uiHeight);
    uiContent->OnFormSurfaceChange(uiWidth, uiHeight, static_cast<OHOS::Rosen::WindowSizeChangeReason>(reason),
        rsTransaction);
    Rosen::RSNode::CloseImplicitAnimation();
    if (needSync) {
        rsTransaction->Commit();
        globalLock_.unlock();
    } else {
        Rosen::RSTransaction::FlushImplicitTransaction();
    }
}

void FormRendererDispatcherImpl::SetObscured(bool isObscured)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }
    handler->PostTask([content = uiContent_, isObscured]() {
        auto uiContent = content.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }
        HILOG_INFO("Update ChangeSensitiveNodes: %{public}s", isObscured ? "true" : "false");
        uiContent->ChangeSensitiveNodes(isObscured);
    });
}

void FormRendererDispatcherImpl::OnAccessibilityChildTreeRegister(
    uint32_t windowId, int32_t treeId, int64_t accessibilityId)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }

    handler->PostTask([content = uiContent_, formRenderer = formRenderer_, windowId, treeId, accessibilityId]() {
        auto uiContent = content.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }
        HILOG_INFO("OnAccessibilityChildTreeRegister: %{public}d %{public}" PRId64, treeId, accessibilityId);
        uiContent->RegisterAccessibilityChildTree(windowId, treeId, accessibilityId);
        uiContent->SetAccessibilityGetParentRectHandler([formRenderer](AccessibilityParentRectInfo &parentRectInfo) {
            auto formRendererPtr = formRenderer.lock();
            if (!formRendererPtr) {
                HILOG_ERROR("formRenderer is nullptr");
                return;
            }
            formRendererPtr->GetRectRelativeToWindow(parentRectInfo);
        });
    });
}

void FormRendererDispatcherImpl::OnAccessibilityChildTreeDeregister()
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }
    handler->PostTask([content = uiContent_]() {
        auto uiContent = content.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }
        HILOG_INFO("OnAccessibilityChildTreeDeregister");
        uiContent->DeregisterAccessibilityChildTree();
    });
}

void FormRendererDispatcherImpl::OnAccessibilityDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }
    handler->PostSyncTask([content = uiContent_, params, &info]() {
        auto uiContent = content.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }
        HILOG_INFO("OnAccessibilityDumpChildInfo");
        uiContent->AccessibilityDumpChildInfo(params, info);
    });
}

void FormRendererDispatcherImpl::OnAccessibilityTransferHoverEvent(float pointX, float pointY, int32_t sourceType,
    int32_t eventType, int64_t timeMs)
{
    auto handler = eventHandler_.lock();
    if (!handler) {
        HILOG_ERROR("eventHandler is nullptr");
        return;
    }
    handler->PostTask([content = uiContent_, pointX, pointY, sourceType, eventType, timeMs]() {
        auto uiContent = content.lock();
        if (!uiContent) {
            HILOG_ERROR("uiContent is nullptr");
            return;
        }
        HILOG_INFO("OnAccessibilityTransferHoverEvent");
        uiContent->HandleAccessibilityHoverEvent(pointX, pointY, sourceType, eventType, timeMs);
    });
}
} // namespace Ace
} // namespace OHOS
