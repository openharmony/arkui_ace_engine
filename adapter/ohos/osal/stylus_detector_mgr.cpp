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

namespace {
constexpr int32_t INDEX_S = 1;
constexpr int32_t INDEX_E = 2;
} // namespace

int32_t StylusDetectorMgr::StylusDetectorCallBack::RequestFocus(int32_t nodeId, RefPtr<TaskExecutor> taskScheduler)
{
    int32_t resultCode = -1;
    taskScheduler->PostSyncTask(
        [&resultCode, nodeId]() {
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
                resultCode = 0;
                return;
            }
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            bool needToRequestKeyBoardOnFocus = pattern->NeedToRequestKeyboardOnFocus();
            if (!needToRequestKeyBoardOnFocus) {
                pattern->RequestKeyboardNotByFocusSwitch(NG::RequestKeyboardReason::STYLUS_DETECTOR);
            }
            resultCode = 0;
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::SetText(int32_t nodeId, void* data,
    RefPtr<TaskExecutor> taskScheduler, std::shared_ptr<IAceStylusCallback> callback)
{
    std::string text = *static_cast<std::string*>(data);
    taskScheduler->PostTask(
        [text, callback, nodeId]() {
            ResultData res;
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            if (frameNode->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
                return;
            }
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            if (!text.empty()) {
                pattern->UpdateEditingValue(text, text.size());
                frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
            }
            if (callback) {
                callback->Callback(res);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
    return 0;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::GetText(int32_t nodeId, RefPtr<TaskExecutor> taskScheduler,
    std::shared_ptr<IAceStylusCallback> callback)
{
    taskScheduler->PostTask(
        [callback, nodeId]() {
            CHECK_NULL_VOID(callback);
            ResultData res;
            res.resultData = "";
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            if (!frameNode) {
                callback->Callback(res);
                return;
            }
            if (frameNode->GetTag() == V2::RICH_EDITOR_ETS_TAG) {
                callback->Callback(res);
                return;
            }
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            if (!pattern) {
                callback->Callback(res);
                return;
            }
            res.resultData = pattern->GetTextValue();
            callback->Callback(res);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
    return 0;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::Redo(int32_t nodeId, RefPtr<TaskExecutor> taskScheduler)
{
    taskScheduler->PostTask(
        [nodeId]() {
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            CHECK_EQUAL_VOID(frameNode->GetTag(), V2::RICH_EDITOR_ETS_TAG);
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnRedoAction();
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
    return 0;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::Undo(int32_t nodeId, RefPtr<TaskExecutor> taskScheduler)
{
    taskScheduler->PostTask(
        [nodeId]() {
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            CHECK_EQUAL_VOID(frameNode->GetTag(), V2::RICH_EDITOR_ETS_TAG);
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->HandleOnUndoAction();
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
    return 0;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::DeleteText(int32_t nodeId, void* data,
    RefPtr<TaskExecutor> taskScheduler)
{
    int32_t resultCode = -1;
    StylusGestureRect *rectPtr = static_cast<StylusGestureRect*>(data);
    CHECK_NULL_RETURN(rectPtr, resultCode);
    auto rect = *rectPtr;
    taskScheduler->PostSyncTask(
        [&resultCode, nodeId, rect]() {
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture rect:%{public}f, %{public}f, %{public}f, %{public}f",
                rect.Left, rect.Top, rect.Width, rect.Height);
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            auto pipeline = frameNode->GetContextRefPtr();
            CHECK_NULL_VOID(pipeline);
            auto windowRect = pipeline->GetCurrentWindowRect();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture windowRect:%{public}f, %{public}f",
                windowRect.Left(), windowRect.Top());
            Offset startCenterGlobalOffset = Offset(rect.Left - windowRect.Left(),
                rect.Top - windowRect.Top() + rect.Height / 2);
            Offset endCenterGlobalOffset = Offset(rect.Left - windowRect.Left() + rect.Width,
                rect.Top - windowRect.Top() + rect.Height / 2);
            auto sInd = GetGlyphPositionByGlobalOffset(frameNode, startCenterGlobalOffset);
            auto eInd = GetGlyphPositionByGlobalOffset(frameNode, endCenterGlobalOffset);
            auto textBase = frameNode->GetPattern<NG::TextBase>();
            CHECK_NULL_VOID(textBase);
            auto wtextLength = textBase->GetContentWideTextLength();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture wtextLength:%{public}d", wtextLength);
            auto ret = CalculateIntersectedRegion(sInd, eInd, wtextLength);
            if (std::get<0>(ret) == 0) {
                auto textInputClient = frameNode->GetPattern<TextInputClient>();
                CHECK_NULL_VOID(textInputClient);
                textInputClient->SetCaretOffset(std::get<INDEX_S>(ret));
                textInputClient->DeleteForward(std::get<INDEX_E>(ret) - std::get<INDEX_S>(ret));
                resultCode = 0;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::ChoiceText(int32_t nodeId, void* data,
    RefPtr<TaskExecutor> taskScheduler)
{
    int32_t resultCode = -1;
    ChoiceTextOption *optionPtr = static_cast<ChoiceTextOption*>(data);
    CHECK_NULL_RETURN(optionPtr, resultCode);
    auto choiceTextOption = *optionPtr;
    taskScheduler->PostSyncTask(
        [&resultCode, nodeId, choiceTextOption]() {
            auto rect = choiceTextOption.rect;
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture global rect:%{public}f, %{public}f, %{public}f, %{public}f",
                rect.Left, rect.Top, rect.Width, rect.Height);
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            auto pipeline = frameNode->GetContextRefPtr();
            CHECK_NULL_VOID(pipeline);
            auto windowRect = pipeline->GetCurrentWindowRect();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture windowRect:%{public}f, %{public}f",
                windowRect.Left(), windowRect.Top());
            Offset startCenterGlobalOffset = Offset(rect.Left - windowRect.Left(),
                rect.Top - windowRect.Top() + rect.Height / 2);
            Offset endCenterGlobalOffset = Offset(rect.Left - windowRect.Left() + rect.Width,
                rect.Top - windowRect.Top() + rect.Height / 2);
            auto sInd = GetGlyphPositionByGlobalOffset(frameNode, startCenterGlobalOffset);
            auto eInd = GetGlyphPositionByGlobalOffset(frameNode, endCenterGlobalOffset);
            auto textBase = frameNode->GetPattern<NG::TextBase>();
            CHECK_NULL_VOID(textBase);
            auto wtextLength = textBase->GetContentWideTextLength();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture wtextLength:%{public}d", wtextLength);
            auto ret = CalculateIntersectedRegion(sInd, eInd, wtextLength);
            if (std::get<0>(ret) == 0) {
                auto textInputClient = frameNode->GetPattern<TextInputClient>();
                CHECK_NULL_VOID(textInputClient);
                SelectionOptions option = { .menuPolicy = MenuPolicy::HIDE };
                if (choiceTextOption.showMenu) {
                    option = { .menuPolicy = MenuPolicy::SHOW };
                }
                textInputClient->SetSelection(std::get<INDEX_S>(ret), std::get<INDEX_E>(ret), option);
                resultCode = 0;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::InsertSpace(int32_t nodeId, void* data,
    RefPtr<TaskExecutor> taskScheduler)
{
    int32_t resultCode = -1;
    StylusGestureRect *rectPtr = static_cast<StylusGestureRect*>(data);
    CHECK_NULL_RETURN(rectPtr, resultCode);
    auto rect = *rectPtr;
    taskScheduler->PostSyncTask(
        [&resultCode, nodeId, rect]() {
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture global rect:%{public}f, %{public}f, %{public}f, %{public}f",
                rect.Left, rect.Top, rect.Width, rect.Height);
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            auto pipeline = frameNode->GetContextRefPtr();
            CHECK_NULL_VOID(pipeline);
            auto windowRect = pipeline->GetCurrentWindowRect();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture windowRect:%{public}f, %{public}f",
                windowRect.Left(), windowRect.Top());
            Offset centerGlobalOffset = Offset(rect.Left - windowRect.Left() + rect.Width / 2,
                rect.Top - windowRect.Top() + rect.Height / 2);
            auto sInd = GetGlyphPositionByGlobalOffset(frameNode, centerGlobalOffset);
            auto textInputClient = frameNode->GetPattern<TextInputClient>();
            CHECK_NULL_VOID(textInputClient);
            auto start = static_cast<int32_t>(sInd.position_);
            auto result = textInputClient->InsertOrDeleteSpace(start);
            if (result) {
                resultCode = 0;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::MoveCursor(int32_t nodeId, void* data,
    RefPtr<TaskExecutor> taskScheduler)
{
    int32_t resultCode = -1;
    MoveCursorOption *pointPtr = static_cast<MoveCursorOption*>(data);
    CHECK_NULL_RETURN(pointPtr, resultCode);
    auto point = *pointPtr;
    taskScheduler->PostSyncTask(
        [&resultCode, nodeId, point]() {
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture point:%{public}d, %{public}d", point.x, point.y);
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            auto pipeline = frameNode->GetContextRefPtr();
            CHECK_NULL_VOID(pipeline);
            auto windowRect = pipeline->GetCurrentWindowRect();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture windowRect:%{public}f, %{public}f",
                windowRect.Left(), windowRect.Top());
            Offset centerGlobalOffset = Offset(point.x - windowRect.Left(), point.y - windowRect.Top());
            auto sInd = GetGlyphPositionByGlobalOffset(frameNode, centerGlobalOffset);
            resultCode = HandleMoveCursor(frameNode, sInd, point.showHandle);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::HandleMoveCursor(const RefPtr<NG::FrameNode>& frameNode,
    NG::PositionWithAffinity sInd, bool showHandle)
{
    auto textBase = frameNode->GetPattern<NG::TextBase>();
    CHECK_NULL_RETURN(textBase, -1);
    auto wtextLength = textBase->GetContentWideTextLength();
    TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture wtextLength:%{public}d", wtextLength);
    auto start = static_cast<int32_t>(sInd.position_);
    if (start >= 0 && start <= wtextLength) {
        auto textInputClient = frameNode->GetPattern<TextInputClient>();
        CHECK_NULL_RETURN(textInputClient, -1);
        textInputClient->SetCaretOffset(start);
        frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
        return 0;
    }
    TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture do not cross");
    return -1;
}

NG::PositionWithAffinity StylusDetectorMgr::StylusDetectorCallBack::GetGlyphPositionByGlobalOffset(
    const RefPtr<NG::FrameNode>& frameNode, const Offset& offset)
{
    TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture offset:%{public}f, %{public}f", offset.GetX(), offset.GetY());
    NG::PositionWithAffinity finalResult(-1, TextAffinity::UPSTREAM);
    // transform point coords from global to local
    auto parentGlobalOffset_ = GetPaintRectGlobalOffset(frameNode);
    auto localOffset = offset - Offset(parentGlobalOffset_.GetX(), parentGlobalOffset_.GetY());
    if (NG::TextBase::HasRenderTransform(frameNode)) {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture pattern has select-overlay render transform");
        auto localOffsetF = NG::OffsetF(offset.GetX(), offset.GetY());
        NG::TextBase::RevertLocalPointWithTransform(frameNode, localOffsetF);
        localOffset.SetX(localOffsetF.GetX());
        localOffset.SetY(localOffsetF.GetY());
    }
    TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture localOffset:%{public}f, %{public}f", localOffset.GetX(),
        localOffset.GetY());
    // calculate the start and end indexes of the intersecting region.
    auto layoutInfo = StylusDetectorMgr::GetInstance()->layoutInfo_.Upgrade();
    CHECK_NULL_RETURN(layoutInfo, finalResult);
    return layoutInfo->GetGlyphPositionAtCoordinate(localOffset.GetX(), localOffset.GetY());
}

std::tuple<int32_t, int32_t, int32_t> StylusDetectorMgr::StylusDetectorCallBack::CalculateIntersectedRegion(
    NG::PositionWithAffinity sInd, NG::PositionWithAffinity eInd, int32_t wtextLength)
{
    TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture wtextLength:%{public}d", wtextLength);
    int32_t startPos = static_cast<int32_t>(std::min(eInd.position_, sInd.position_));
    int32_t endPos = static_cast<int32_t>(std::max(eInd.position_, sInd.position_));
    if (endPos < 1 || startPos >= wtextLength) {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture rect do not cross");
        return std::make_tuple(-1, 0, 0);
    }
    // calculate the cross length
    int32_t start = std::max(startPos, 0);
    int32_t end = std::min(endPos, wtextLength);
    if (start < end) {
        return std::make_tuple(0, start, end);
    } else {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture rect do not cross");
        return std::make_tuple(-1, 0, 0);
    }
}

NG::OffsetF StylusDetectorMgr::StylusDetectorCallBack::GetPaintRectGlobalOffset(
    const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, NG::OffsetF(0.0f, 0.0f));
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, NG::OffsetF(0.0f, 0.0f));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = frameNode->GetPaintRectOffset();
    return textPaintOffset - rootOffset;
}

int32_t StylusDetectorMgr::StylusDetectorCallBack::OnDetector(
    const CommandType& command, void* data, std::shared_ptr<IAceStylusCallback> callback)
{
    auto nodeId = StylusDetectorMgr::GetInstance()->GetDefaultNodeId();
    if (nodeId == 0) {
        return -1;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, -1);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, -1);
    auto taskScheduler = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskScheduler, -1);

    int32_t resultCode = -1;
    ResultData res;
    switch (command) {
        case COMMAND_REQUEST_FOCUS:
            return StylusDetectorMgr::StylusDetectorCallBack::RequestFocus(nodeId, taskScheduler);
        case COMMAND_MOVE_CURSOR:
            return StylusDetectorMgr::StylusDetectorCallBack::MoveCursor(nodeId, data, taskScheduler);
        case COMMAND_DELETE_TEXT:
            return StylusDetectorMgr::StylusDetectorCallBack::DeleteText(nodeId, data, taskScheduler);
        case COMMAND_CHOICE_TEXT:
            return StylusDetectorMgr::StylusDetectorCallBack::ChoiceText(nodeId, data, taskScheduler);
        case COMMAND_INSERT_SPACE:
            return StylusDetectorMgr::StylusDetectorCallBack::InsertSpace(nodeId, data, taskScheduler);
        case COMMAND_CLEAR_HIT:
            return resultCode;
        case COMMAND_SET_TEXT:
            return StylusDetectorMgr::StylusDetectorCallBack::SetText(nodeId, data, taskScheduler, callback);
        case COMMAND_GET_TEXT:
            return StylusDetectorMgr::StylusDetectorCallBack::GetText(nodeId, taskScheduler, callback);
        case COMMAND_UNDO:
            return StylusDetectorMgr::StylusDetectorCallBack::Undo(nodeId, taskScheduler);
        case COMMAND_REDO:
            return StylusDetectorMgr::StylusDetectorCallBack::Redo(nodeId, taskScheduler);
        case COMMAND_INVALID:
            TAG_LOGE(AceLogTag::ACE_STYLUS, "StylusDetector received error command.");
            return resultCode;
        default:
            return resultCode;
    }
}

bool StylusDetectorMgr::StylusDetectorCallBack::OnDetectorSync(const CommandType& command)
{
    bool result = false;
    auto nodeId = StylusDetectorMgr::GetInstance()->GetDefaultNodeId();
    CHECK_EQUAL_RETURN(nodeId, 0, result);
    auto container = Container::CurrentSafely();
    CHECK_NULL_RETURN(container, result);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, result);
    auto taskScheduler = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskScheduler, result);

    TAG_LOGI(AceLogTag::ACE_STYLUS, "Stylus received commandType:%{public}d", static_cast<int32_t>(command));
    taskScheduler->PostSyncTask(
        [nodeId, command, &result]() {
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            CHECK_EQUAL_VOID(frameNode->GetTag(), V2::RICH_EDITOR_ETS_TAG);
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);

            switch (command) {
                case COMMAND_CANUNDO:
                    result = pattern->CanUndo();
                    break;
                case COMMAND_CANREDO:
                    result = pattern->CanRedo();
                    break;
                default:
                    break;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return result;
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
        TAG_LOGI(AceLogTag::ACE_STYLUS, "Can't find pipeline for find hit node.");
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
        TAG_LOGI(AceLogTag::ACE_STYLUS, "TouchTestResult is empty");
        return false;
    }

    auto frameNode = FindHitFrameNode(touchEvent, iter->second);
    if (!frameNode) {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "Stylus hit position is (%{public}f, %{public}f). TargetNode is None",
            touchEvent.x, touchEvent.y);
        return false;
    }

    TAG_LOGI(AceLogTag::ACE_STYLUS,
        "Stylus hit position is (%{public}f, %{public}f). TargetNode is %{public}s, id is %{public}s", touchEvent.x,
        touchEvent.y, frameNode->GetTag().c_str(), frameNode->GetInspectorId()->c_str());

    if (!IsEnable()) {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "Stylus service is not enable");
        return false;
    }

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto bundleName = container->GetBundleName();
    NotifyInfo info;
    info.componentId = frameNode->GetId();
    nodeId_ = info.componentId;
    const auto layoutIter = textFieldLayoutInfos_.find(nodeId_);
    if (layoutIter != textFieldLayoutInfos_.end()) {
        layoutInfo_ = layoutIter->second;
    }
    info.x = touchEvent.screenX;
    info.y = touchEvent.screenY;
    info.bundleName = bundleName;
    if (!isRegistered_) {
        auto stylusDetectorCallback = std::make_shared<StylusDetectorCallBack>();
        isRegistered_ = RegisterStylusInteractionListener(bundleName, stylusDetectorCallback);
    }
    return Notify(info);
}

void StylusDetectorMgr::AddTextFieldFrameNode(const RefPtr<NG::FrameNode>& frameNode,
    const WeakPtr<NG::LayoutInfoInterface>& layoutInfo)
{
    CHECK_NULL_VOID(frameNode);
    auto tag = frameNode->GetTag();
    auto iter = TEXT_FIELD_COMPONENT_TAGS.find(tag);
    if (iter == TEXT_FIELD_COMPONENT_TAGS.end()) {
        return;
    }
    auto id = frameNode->GetId();
    auto destructor = [id]() { StylusDetectorMgr::GetInstance()->RemoveTextFieldFrameNode(id); };
    frameNode->PushDestroyCallbackWithTag(std::move(destructor), "DestroyCallbackForStylus");
    textFieldNodes_[id] = AceType::WeakClaim(AceType::RawPtr(frameNode));
    textFieldLayoutInfos_[id] = layoutInfo;
}

void StylusDetectorMgr::RemoveTextFieldFrameNode(const int32_t id)
{
    textFieldNodes_.erase(id);
    textFieldLayoutInfos_.erase(id);
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