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
#include "core/common/container.h"
#include "core/common/stylus/stylus_detector_default.h"
#include "core/common/stylus/stylus_detector_loader.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace {
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
    if (frameNode->GetTag() == V2::SEARCH_Field_ETS_TAG) {
        auto searchTextFieldPattern = frameNode->GetPattern<NG::SearchTextFieldPattern>();
        CHECK_NULL_VOID(searchTextFieldPattern);
        focusHub = searchTextFieldPattern->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
    }
    if (!focusHub->IsCurrentFocus()) {
        focusHub->RequestFocusImmediately();
    }
    if (frameNode->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
        return;
    }
    auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    bool needToRequestKeyBoardOnFocus = pattern->NeedToRequestKeyboardOnFocus();
    if (!needToRequestKeyBoardOnFocus) {
        pattern->RequestKeyboardNotByFocusSwitch(NG::RequestKeyboardReason::STYLUS_DETECTOR);
    }
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

    LOGI("Stylus received commandType:%{public}d", static_cast<int32_t>(command));
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
bool StylusDetectorMgr::RegisterStylusInteractionListener(
    const std::string& bundleName, const std::shared_ptr<IStylusDetectorCallback>& callback)
{
    CHECK_NULL_RETURN(engine_, false);
    return engine_->RegisterStylusInteractionListener(bundleName, callback);
}
void StylusDetectorMgr::UnRegisterStylusInteractionListener(const std::string& bundleName)
{
    CHECK_NULL_VOID(engine_);
    return engine_->UnRegisterStylusInteractionListener(bundleName);
}
bool StylusDetectorMgr::Notify(const NotifyInfo& notifyInfo)
{
    CHECK_NULL_RETURN(engine_, false);
    return engine_->Notify(notifyInfo);
}

RefPtr<NG::FrameNode> StylusDetectorMgr::FindHitFrameNode(
    const TouchEvent& touchEvent, const TouchTestResult& touchTestResult)
{
    RefPtr<NG::FrameNode> frameNode;
    // TextField, textInput, search and richEditor has default touchEventTarget.
    for (const auto& entry : touchTestResult) {
        auto recognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(entry);
        if (recognizer) {
            continue;
        }
        auto nodeId = entry->GetNodeId();
        auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
        if (frameNode) {
            break;
        }
    }
    CHECK_NULL_RETURN(frameNode, nullptr);

    auto pipeline = frameNode->GetContextRefPtr();
    if (!pipeline) {
        LOGI("Can't find pipeline for find hit node.");
        return nullptr;
    }
    auto nanoTimestamp = pipeline->GetVsyncTime();
    auto textBasePattern = frameNode->GetPattern<NG::TextBase>();
    CHECK_NULL_RETURN(textBasePattern, nullptr);
    if (!textBasePattern->IsTextEditableForStylus() ||
        IsHitCleanNodeResponseArea({ touchEvent.x, touchEvent.y }, frameNode, nanoTimestamp)) {
        return nullptr;
    }
    return frameNode;
}

bool StylusDetectorMgr::IsNeedInterceptedTouchEvent(
    const TouchEvent& touchEvent, std::unordered_map<size_t, TouchTestResult> touchTestResults)
{
    if (!IsStylusTouchEvent(touchEvent)) {
        return false;
    }

    const auto iter = touchTestResults.find(touchEvent.id);
    if (iter == touchTestResults.end() || iter->second.empty()) {
        LOGI("TouchTestResult is empty");
        return false;
    }

    auto frameNode = FindHitFrameNode(touchEvent, iter->second);
    if (!frameNode) {
        LOGI("Stylus hit position is (%{public}f, %{public}f). TargetNode is None", touchEvent.x, touchEvent.y);
        return false;
    }

    LOGI("Stylus hit position is (%{public}f, %{public}f). TargetNode is %{public}s, id is %{public}s", touchEvent.x,
        touchEvent.y, frameNode->GetTag().c_str(), frameNode->GetInspectorId()->c_str());

    if (!IsEnable()) {
        LOGI("Stylus service is not enable");
        return false;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto bundleName = container->GetBundleName();
    NotifyInfo info;
    info.componentId = frameNode->GetId();
    nodeId_ = info.componentId;
    info.x = touchEvent.screenX;
    info.y = touchEvent.screenY;
    info.bundleName = bundleName;
    if (!isRegistered_) {
        auto stylusDetectorCallback = std::make_shared<StylusDetectorCallBack>();
        isRegistered_ = RegisterStylusInteractionListener(bundleName, stylusDetectorCallback);
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
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto bundleName = container->GetBundleName();
        isRegistered_ = false;
        UnRegisterStylusInteractionListener(bundleName);
    }
}

StylusDetectorMgr::StylusDetectorMgr() : engine_(nullptr), isRegistered_(false)
{
    auto lib = StylusDetectorLoader::Load();
    if (!lib || !(engine_ = lib->CreateStylusDetector())) {
        engine_ = StylusDetectorInstance(StylusDetectorDefault::GetInstance(), [](StylusDetectorInterface* e) {});
    }
}

bool StylusDetectorMgr::IsStylusTouchEvent(const TouchEvent& touchEvent) const
{
    return touchEvent.sourceTool == SourceTool::PEN && touchEvent.type == TouchType::DOWN;
}

bool StylusDetectorMgr::IsHitCleanNodeResponseArea(
    const NG::PointF& point, const RefPtr<NG::FrameNode>& frameNode, uint64_t nanoTimestamp)
{
    CHECK_NULL_RETURN(frameNode, false);
    if (frameNode->GetTag() != V2::TEXTINPUT_ETS_TAG) {
        return false;
    }

    auto textFieldPattern = frameNode->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);
    auto responseArea = textFieldPattern->GetCleanNodeResponseArea();
    CHECK_NULL_RETURN(responseArea, false);
    auto cleanNodeResponseArea = AceType::DynamicCast<NG::CleanNodeResponseArea>(responseArea);
    if (!cleanNodeResponseArea->IsShow()) {
        return false;
    }

    auto cleanNodeFrameNode = cleanNodeResponseArea->GetFrameNode();
    CHECK_NULL_RETURN(cleanNodeFrameNode, false);
    auto cleanNodeGeometryNode = cleanNodeFrameNode->GetGeometryNode();
    CHECK_NULL_RETURN(cleanNodeGeometryNode, false);
    auto globalFrameRect = cleanNodeGeometryNode->GetFrameRect();
    globalFrameRect.SetOffset(cleanNodeFrameNode->CalculateCachedTransformRelativeOffset(nanoTimestamp));
    return globalFrameRect.IsInRegion(point);
}
} // namespace OHOS::Ace