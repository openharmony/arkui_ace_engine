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

#include "core/common/stylus/stylus_detector_mgr.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/point.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/stylus/stylus_detector_default.h"
#include "core/common/stylus/stylus_detector_loader.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace {
namespace {
const Dimension HOT_AREA_ADJUST_SIZE = 20.0_vp;
}
const static std::unordered_set<std::string> TEXT_FIELD_COMPONENT_TAGS = {
    V2::TEXTINPUT_ETS_TAG,
    V2::TEXTAREA_ETS_TAG,
    V2::RICH_EDITOR_ETS_TAG,
    V2::SEARCH_Field_ETS_TAG,
};

void StylusDetectorMgr::StylusDetectorCallBack::RequestFocus(int32_t nodeId)
{
    auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
}

void StylusDetectorMgr::StylusDetectorCallBack::SetText(int32_t nodeId, std::string args)
{
    auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
        return;
    }
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (!args.empty()) {
        pattern->UpdateEditingValue(args, args.size());
        frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
    }
}

std::string StylusDetectorMgr::StylusDetectorCallBack::GetText(int32_t nodeId)
{
    auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
    CHECK_NULL_RETURN(frameNode, "");
    if (frameNode->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
        return "";
    }
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, "");
    return pattern->GetTextValue();
}

void StylusDetectorMgr::StylusDetectorCallBack::OnDetector(
    const CommandType& command, std::string args, std::shared_ptr<IAceStylusCallback> callback)
{
    ResultData res;
    auto nodeId = StylusDetectorMgr::GetInstance()->GetDefaultNodeId();
    if (nodeId == 0) {
        return;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto taskScheduler = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);

    taskScheduler->PostTask(
        [command, callback, nodeId, args]() {
            ResultData res;
            std::string inputText = "";
            switch (command) {
                case COMMAND_REQUEST_FOCUS:
                    StylusDetectorMgr::StylusDetectorCallBack::RequestFocus(nodeId);
                    break;
                case COMMAND_CLEAR_HIT:
                    break;
                case COMMAND_SET_TEXT:
                    StylusDetectorMgr::StylusDetectorCallBack::SetText(nodeId, args);
                    break;
                case COMMAND_GET_TEXT:
                    res.resultData = StylusDetectorMgr::StylusDetectorCallBack::GetText(nodeId);
                    break;
                case COMMAND_INVALID:
                    LOGE("StylusDetector received error command.");
                    res.errorMessage = "StylusDetector received error command.";
                    res.errorCode = 1;
                    break;
                default:
                    break;
            }
            if (callback.get() != nullptr) {
                callback->Callback(res);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
}

StylusDetectorMgr* StylusDetectorMgr::GetInstance()
{
    static StylusDetectorMgr instance;
    return &instance;
}

bool StylusDetectorMgr::IsEnable()
{
    CHECK_NULL_RETURN(engine_, false);
    auto isEnable = engine_->IsEnable();
    CHECK_NULL_RETURN(isEnable, false);
    return isEnable;
}
bool StylusDetectorMgr::RegisterStylusInteractionListener(const std::shared_ptr<IStylusDetectorCallback>& callback)
{
    CHECK_NULL_RETURN(engine_, false);
    return engine_->RegisterStylusInteractionListener(callback);
}
void StylusDetectorMgr::UnRegisterStylusInteractionListener()
{
    CHECK_NULL_VOID(engine_);
    return engine_->UnRegisterStylusInteractionListener();
}
bool StylusDetectorMgr::Notify(const NotifyInfo& notifyInfo)
{
    CHECK_NULL_RETURN(engine_, false);
    return engine_->Notify(notifyInfo);
}

bool StylusDetectorMgr::IsNeedInterceptedTouchEvent(const TouchEvent& touchEvent)
{
    if (!IsEnable()) {
        return false;
    }
    if (!IsStylusTouchEvent(touchEvent)) {
        return false;
    }

    auto frameNode = FindTextInputFrameNodeByPosition(touchEvent.x, touchEvent.y);
    CHECK_NULL_RETURN(frameNode, false);

    NotifyInfo info;
    info.componentId = frameNode->GetId();
    nodeId_ = info.componentId;
    info.x = touchEvent.x;
    info.y = touchEvent.y;
    if (!isRegistered_) {
        auto stylusDetectorCallback = std::make_shared<StylusDetectorCallBack>();
        isRegistered_ = RegisterStylusInteractionListener(stylusDetectorCallback);
    }
    return Notify(info);
}

void StylusDetectorMgr::AddTextFieldFrameNode(const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto tag = frameNode->GetTag();
    auto iter = TEXT_FIELD_COMPONENT_TAGS.find(tag);
    if (iter == TEXT_FIELD_COMPONENT_TAGS.end()) {
        return;
    }
    auto id = frameNode->GetId();
    auto destructor = [id]() { StylusDetectorMgr::GetInstance()->RemoveTextFieldFrameNode(id); };
    frameNode->PushDestroyCallback(std::move(destructor));
    textFieldNodes_[id] = AceType::WeakClaim(AceType::RawPtr(frameNode));
}
void StylusDetectorMgr::RemoveTextFieldFrameNode(const int32_t id)
{
    textFieldNodes_.erase(id);
    if (textFieldNodes_.empty()) {
        UnRegisterStylusInteractionListener();
    }
}

StylusDetectorMgr::StylusDetectorMgr() : engine_(nullptr), isRegistered_(false)
{
    auto lib = StylusDetectorLoader::Load();
    if (!lib || !(engine_ = lib->CreateStylusDetector())) {
        engine_ = StylusDetectorInstance(StylusDetectorDefault::GetInstance(), [](StylusDetectorInterface* e) {});
    }
}

bool StylusDetectorMgr::CheckTextEditable(const RefPtr<NG::FrameNode> parentNode)
{
    CHECK_NULL_RETURN(parentNode, false);
    auto focusHub = parentNode->GetFocusHub();
    if (!focusHub->IsFocusable() || !parentNode->IsVisible()) {
        return false;
    }
    if (parentNode->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
        return true;
    }
    auto pattern = parentNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return !pattern->IsInPasswordMode();
}

RefPtr<NG::FrameNode> StylusDetectorMgr::FindTargetInChildNodes(
    const RefPtr<NG::UINode> parentNode, const FrameNodeSet& hitFrameNodes)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    auto parentFrameNode = AceType::DynamicCast<NG::FrameNode>(parentNode);
    if (parentFrameNode && (!parentFrameNode->IsActive() || !parentFrameNode->IsVisible())) {
        return nullptr;
    }
    auto children = parentFrameNode->GetFrameChildren();

    for (auto iter = children.rbegin(); iter != children.rend(); iter++) {
        auto child = iter->Upgrade();
        if (child == nullptr) {
            continue;
        }
        auto childNode = AceType::DynamicCast<NG::UINode>(child);
        auto childFindResult = FindTargetInChildNodes(childNode, hitFrameNodes);
        if (childFindResult) {
            return childFindResult;
        }
    }

    CHECK_NULL_RETURN(parentFrameNode, nullptr);
    auto iter = hitFrameNodes.find(parentFrameNode);
    if (iter != hitFrameNodes.end() && CheckTextEditable(parentFrameNode)) {
        return *iter;
    }
    return nullptr;
}

RefPtr<NG::FrameNode> StylusDetectorMgr::FindTextInputFrameNodeByPosition(float globalX, float globalY)
{
    if (textFieldNodes_.empty()) {
        return nullptr;
    }

    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto nanoTimestamp = pipeline->GetVsyncTime();
    NG::PointF point(globalX, globalY);

    FrameNodeSet hitFrameNodes;
    for (auto iterOfFrameNode = textFieldNodes_.begin(); iterOfFrameNode != textFieldNodes_.end(); iterOfFrameNode++) {
        auto frameNode = iterOfFrameNode->second.Upgrade();
        if (!frameNode || !frameNode->IsVisible()) {
            continue;
        }
        auto geometryNode = frameNode->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }
        auto globalFrameRect = geometryNode->GetFrameRect() + NG::SizeF(0, HOT_AREA_ADJUST_SIZE.ConvertToPx() * 2);
        globalFrameRect.SetOffset(frameNode->CalculateCachedTransformRelativeOffset(nanoTimestamp) +
                                  NG::OffsetF(0, -HOT_AREA_ADJUST_SIZE.ConvertToPx()));
        if (globalFrameRect.IsInRegion(point)) {
            hitFrameNodes.insert(frameNode);
        }
    }

    if (hitFrameNodes.empty()) {
        LOGD("Cannot find targetNodes.");
        return nullptr;
    }

    auto rootNode = pipeline->GetRootElement();
    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow()) {
        rootNode = pipeline->GetFocusedWindowSceneNode();
    }

    auto result = FindTargetInChildNodes(rootNode, hitFrameNodes);
    if (result) {
        return result;
    }
    return nullptr;
}
bool StylusDetectorMgr::IsStylusTouchEvent(const TouchEvent& touchEvent) const
{
    return touchEvent.sourceTool == SourceTool::PEN && touchEvent.type == TouchType::DOWN;
}
} // namespace OHOS::Ace