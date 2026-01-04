/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "arkoala_api_generated.h"
#include "builder_node_ops_peer.h"
#include "frame_node_peer_impl.h"
#include "touch_event_peer.h"
#include "mouse_event_peer.h"
#include "axis_event_peer.h"
#include "ui/base/utils/utils.h"

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
const std::unordered_set<std::string> EXPORT_TEXTURE_SUPPORT_TYPES = { V2::JS_VIEW_ETS_TAG, V2::COMMON_VIEW_ETS_TAG };
}
namespace BuilderNodeOpsAccessor {
void DestroyPeerImpl(Ark_BuilderNodeOps peer)
{
    auto peerImpl = reinterpret_cast<BuilderNodeOpsPeer*>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_BuilderNodeOps CtorImpl()
{
    return new BuilderNodeOpsPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}
void CreateImpl(Ark_BuilderNodeOps peer, const Callback_Void* buildFunc)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(buildFunc);
    auto viewNode_ = peer->viewNode_;
    auto realNode_ = peer->realNode_;
    auto lazyBuilderFunc = [builder = CallbackHelper(*buildFunc), renderType = peer->renderType_]() mutable {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        NG::ViewStackProcessor::GetInstance()->SetIsBuilderNode(true);
        NG::ViewStackProcessor::GetInstance()->SetIsExportTexture(renderType == NodeRenderType::RENDER_TYPE_TEXTURE);
        builder.InvokeSync();
    };
    auto parent = viewNode_ ? viewNode_->GetParent() : nullptr;
    lazyBuilderFunc();
    auto newNode = peer->viewNode_;
    // replace preNode by newNode
    if (parent) {
        if (newNode) {
            parent->ReplaceChild(viewNode_, newNode);
            newNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
        } else {
            parent->RemoveChild(viewNode_);
            parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
        }
    }
    auto isSupportExportTexture = newNode ? EXPORT_TEXTURE_SUPPORT_TYPES.count(newNode->GetTag()) > 0 : false;
    if (newNode) {
        newNode->SetBuilderFunc(std::move(lazyBuilderFunc));
        newNode->SetIsRootBuilderNode(true);
        if (isSupportExportTexture) {
            newNode->CreateExportTextureInfoIfNeeded();
            auto exportTextureInfo = newNode->GetExportTextureInfo();
            if (exportTextureInfo) {
                exportTextureInfo->SetSurfaceId(peer->surfaceId_);
                exportTextureInfo->SetCurrentRenderType(peer->renderType_);
            }
        }
        if (peer->size_.IsValid()) {
            newNode->SetParentLayoutConstraint(peer->size_.ConvertToSizeT());
        }
    }
}
void DisposeNodeImpl(Ark_BuilderNodeOps peer)
{
    CHECK_NULL_VOID(peer);
    peer->viewNode_.Reset();
    peer->realNode_.Reset();
}
void SetUpdateConfigurationCallbackImpl(Ark_BuilderNodeOps peer, const Callback_Void* configurationUpdateFunc)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->viewNode_);
    CHECK_NULL_VOID(configurationUpdateFunc);
    auto updateNodeConfig = [updateTsConfig = CallbackHelper(*configurationUpdateFunc)]() mutable {
        updateTsConfig.InvokeSync();
    };
    peer->viewNode_->SetUpdateNodeConfig(std::move(updateNodeConfig));
}

void SetOptionsImpl(Ark_BuilderNodeOps peer, const Ark_BuilderNodeOptions* options)
{
    CHECK_NULL_VOID(peer);
    auto renderOptions = Converter::OptConvertPtr<Ark_BuilderNodeOptions>(options);
    if (!renderOptions.has_value()) {
        return;
    }
    auto selfIdealSize = Converter::Convert<Opt_Size>(options->selfIdealSize);
    NG::OptionalSizeF selfIdealSizeValue;
    auto sizeValue = Converter::Convert<Ark_Size>(selfIdealSize.value);
    if (selfIdealSize.tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto widthValue = Converter::Convert<float>(sizeValue.width);
        auto heightValue = Converter::Convert<float>(sizeValue.height);
        widthValue = LessNotEqual(widthValue, 0.0f) ? 0.0f : widthValue;
        heightValue = LessNotEqual(heightValue, 0.0f) ? 0.0f : heightValue;
        selfIdealSizeValue.SetWidth(PipelineBase::Vp2PxWithCurrentDensity(widthValue));
        selfIdealSizeValue.SetHeight(PipelineBase::Vp2PxWithCurrentDensity(heightValue));
        peer->size_ = selfIdealSizeValue;
    }
    auto nodeRenderType = Converter::Convert<Opt_Number>(options->type);
    if (nodeRenderType.tag == InteropTag::INTEROP_TAG_OBJECT) {
        peer->renderType_ = static_cast<NodeRenderType>(Converter::Convert<int32_t>(nodeRenderType.value));
    }
    auto surfaceId = Converter::OptConvert<std::string>(renderOptions->surfaceId);
    if (surfaceId) {
        peer->surfaceId_ = surfaceId.value();
    }
}

Ark_Boolean PostTouchEventImpl(Ark_BuilderNodeOps peer, Ark_TouchEvent event)
{
    return Converter::ArkValue<Ark_Boolean>(false);
}
Ark_Boolean GetTouchEvent(const TouchEventInfo* touchEventInfo, TouchEvent& touchEvent)
{
    // get changedTouches
    CHECK_NULL_RETURN(touchEventInfo, false);
    touchEvent = touchEventInfo->ConvertToTouchEvent();
    touchEvent.originalId = touchEvent.id;
    touchEvent.operatingHand = touchEventInfo->GetChangedTouches().front().GetOperatingHand();
    // get common
    touchEvent.sourceType = touchEventInfo->GetSourceDevice();
    touchEvent.sourceTool = touchEventInfo->GetSourceTool();
    touchEvent.force = touchEventInfo->GetForce();
    touchEvent.time = touchEventInfo->GetTimeStamp();
    touchEvent.deviceId = touchEventInfo->GetDeviceId();
    touchEvent.targetDisplayId = touchEventInfo->GetTargetDisplayId();
    touchEvent.tiltX = touchEventInfo->GetTiltX();
    touchEvent.tiltY = touchEventInfo->GetTiltY();
    touchEvent.rollAngle = touchEventInfo->GetRollAngle();
    touchEvent.SetPressedKeyCodes(touchEventInfo->GetPressedKeyCodes());
    // get touches property
    for (const auto& touch : touchEventInfo->GetTouches()) {
        TouchPoint point;
        point.id = touch.GetFingerId();
        point.x = touch.GetGlobalLocation().GetX();
        point.y = touch.GetGlobalLocation().GetY();
        point.screenX = touch.GetScreenLocation().GetX();
        point.screenY = touch.GetScreenLocation().GetY();
        point.originalId = touch.GetFingerId();
        point.force = touch.GetForce();
        point.width = touch.GetWidth();
        point.height = touch.GetHeight();
        point.globalDisplayX = touch.GetGlobalDisplayLocation().GetX();
        point.globalDisplayY = touch.GetGlobalDisplayLocation().GetY();
        point.operatingHand = touch.GetOperatingHand();
        point.downTime = touch.GetPressedTime();
        touchEvent.pointers.emplace_back(point);
    }
    return true;
}
 	 
Ark_Boolean PostInputEventImpl(Ark_BuilderNodeOps peer, const Opt_InputEventType* event)
{
    const auto errValue = Converter::ArkValue<Ark_Boolean>(false);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(event, errValue);
    if (InteropTag::INTEROP_TAG_UNDEFINED == event->tag) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEventImpl event is undefined");
        return errValue;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, errValue);
    auto postEventManager = pipelineContext->GetPostEventManager();
    CHECK_NULL_RETURN(postEventManager, errValue);
    bool result = false;
    auto arkEevent = event->value;
    switch (arkEevent.selector) {
        case SELECTOR_ID_0: {
            auto touchEventInfo = arkEevent.value0->GetEventInfo();
            CHECK_NULL_RETURN(touchEventInfo, errValue);
            TouchEvent touchEvent;
            if (!GetTouchEvent(touchEventInfo, touchEvent)) {
                return errValue;
            }
            result = postEventManager->PostTouchEvent(peer->realNode_, std::move(touchEvent));
            break;
        }
        case SELECTOR_ID_1: {
            auto mouseEventInfo = arkEevent.value1->GetEventInfo();
            auto mouseEvent = mouseEventInfo->ConvertToMouseEvent();
            mouseEvent.time = mouseEventInfo->GetTimeStamp();
            result = postEventManager->PostMouseEvent(peer->realNode_, std::move(mouseEvent));
            break;
        }
        case SELECTOR_ID_2: {
            auto axisEventInfo = arkEevent.value2->GetEventInfo();
            auto axisEvent = axisEventInfo->ConvertToAxisEvent();
            axisEvent.pressedCodes = axisEventInfo->GetPressedKeyCodes();
            result = postEventManager->PostAxisEvent(peer->realNode_, std::move(axisEvent));
            break;
        }
        default: {
            result = false;
            break;
        }
    }
    return Converter::ArkValue<Ark_Boolean>(result);
}
Ark_NativePointer SetRootFrameNodeInBuilderNodeImpl(Ark_BuilderNodeOps peer, Ark_NativePointer node)
{
    auto uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, nullptr);
    peer->realNode_ = AceType::Claim<UINode>(uiNode);
    if (AceType::InstanceOf<NG::FrameNode>(peer->realNode_)) {
        peer->viewNode_ = AceType::DynamicCast<NG::FrameNode>(peer->realNode_);
        peer->viewNode_->SetIsRootBuilderNode(true);
    }
    return FrameNodePeer::Create(peer->viewNode_);
}
} // namespace BuilderNodeOpsAccessor
const GENERATED_ArkUIBuilderNodeOpsAccessor* GetBuilderNodeOpsAccessor()
{
    static const GENERATED_ArkUIBuilderNodeOpsAccessor BuilderNodeOpsAccessorImpl {
        BuilderNodeOpsAccessor::DestroyPeerImpl,
        BuilderNodeOpsAccessor::CtorImpl,
        BuilderNodeOpsAccessor::GetFinalizerImpl,
        BuilderNodeOpsAccessor::CreateImpl,
        BuilderNodeOpsAccessor::DisposeNodeImpl,
        BuilderNodeOpsAccessor::SetUpdateConfigurationCallbackImpl,
        BuilderNodeOpsAccessor::SetOptionsImpl,
        BuilderNodeOpsAccessor::PostTouchEventImpl,
        BuilderNodeOpsAccessor::PostInputEventImpl,
        BuilderNodeOpsAccessor::SetRootFrameNodeInBuilderNodeImpl,
    };
    return &BuilderNodeOpsAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier
