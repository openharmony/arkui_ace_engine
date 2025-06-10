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
#include "core/components_ng/pattern/ui_extension/platform_container_handler.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool PlatformContainerHandler::GetAccessibilityParentRect(HandlerReply& reply)
{
    auto pattern = hostPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);

    auto getAccessibilityParentRect =
        [weak = hostPattern_, &reply] {
            auto hostPattern = weak.Upgrade();
            CHECK_NULL_VOID(hostPattern);
            auto hostNode = hostPattern->GetHost();
            CHECK_NULL_VOID(hostNode);
            auto rect = hostNode->GetTransformRectRelativeToWindow(true);
            VectorF finalScale = hostNode->GetTransformScaleRelativeToWindow();
            AccessibilityParentRectInfo parentRectInfo;
            parentRectInfo.left = static_cast<int32_t>(rect.Left());
            parentRectInfo.top = static_cast<int32_t>(rect.Top());
            parentRectInfo.scaleX = finalScale.x;
            parentRectInfo.scaleY = finalScale.y;
            auto pipeline = hostNode->GetContextRefPtr();
            if (pipeline) {
                auto accessibilityManager = pipeline->GetAccessibilityManager();
                if (accessibilityManager) {
                    parentRectInfo = accessibilityManager->GetTransformRectInfoRelativeToWindow(hostNode, pipeline);
                }
            }
            reply.SetParam<int32_t>("left", parentRectInfo.left);
            reply.SetParam<int32_t>("top", parentRectInfo.top);
            reply.SetParam<float>("scaleX", parentRectInfo.scaleX);
            reply.SetParam<float>("scaleY", parentRectInfo.scaleY);
            reply.SetParam<int32_t>("centerX", parentRectInfo.rotateTransform.centerX);
            reply.SetParam<int32_t>("centerY", parentRectInfo.rotateTransform.centerY);
            reply.SetParam<int32_t>("innerCenterX", parentRectInfo.rotateTransform.innerCenterX);
            reply.SetParam<int32_t>("innerCenterY", parentRectInfo.rotateTransform.innerCenterY);
            reply.SetParam<int32_t>("rotateDegree", parentRectInfo.rotateTransform.rotateDegree);
            TAG_LOGD(AceLogTag::ACE_DYNAMIC_COMPONENT,
                "Transform DC rect param[left:%{public}d, top:%{public}d, scaleX:%{public}f, scaleY:%{public}f].",
                parentRectInfo.left, parentRectInfo.top, parentRectInfo.scaleX, parentRectInfo.scaleY);
        };
    if (host->GetTag() == V2::ISOLATED_COMPONENT_ETS_TAG) {
        getAccessibilityParentRect();
    } else if (host->GetTag() == V2::DYNAMIC_COMPONENT_ETS_TAG) {
        GetDCAccessibilityParentRect(reply);
    }

    return true;
}

bool PlatformContainerHandler::OnReciveData(const HandlerData& data, HandlerReply& reply)
{
    switch (static_cast<DynamicContainerHandleAction>(data.actionCode)) {
        case DynamicContainerHandleAction::ACCESSIBILITY_GET_RECT:
            return GetAccessibilityParentRect(reply);
        default:
            break;
    }
    return false;
}

void PlatformContainerHandler::UpdateAccessibilityParentRectInfo(
    const AccessibilityParentRectInfo& info)
{
    std::unique_lock<std::shared_mutex> lock(rectInfoMutex_);
    rectInfo_ = info;
    OnAccessibilityParentRectInfoUpdate();
}

void PlatformContainerHandler::GetDCAccessibilityParentRect(HandlerReply& reply)
{
    std::shared_lock<std::shared_mutex> lock(rectInfoMutex_);
    reply.SetParam<int32_t>("left", rectInfo_.left);
    reply.SetParam<int32_t>("top", rectInfo_.top);
    reply.SetParam<float>("scaleX", rectInfo_.scaleX);
    reply.SetParam<float>("scaleY", rectInfo_.scaleY);
    reply.SetParam<int32_t>("centerX", rectInfo_.rotateTransform.centerX);
    reply.SetParam<int32_t>("centerY", rectInfo_.rotateTransform.centerY);
    reply.SetParam<int32_t>("innerCenterX", rectInfo_.rotateTransform.innerCenterX);
    reply.SetParam<int32_t>("innerCenterY", rectInfo_.rotateTransform.innerCenterY);
    reply.SetParam<int32_t>("rotateDegree", rectInfo_.rotateTransform.rotateDegree);
}

} // namespace OHOS::Ace::NG
