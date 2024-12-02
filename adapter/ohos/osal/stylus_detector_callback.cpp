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

#include "core/common/stylus/stylus_detector_callback.h"

#include "core/common/stylus/stylus_detector_mgr.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_base.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "frameworks/base/log/log_wrapper.h"

namespace OHOS::Ace {

namespace {
constexpr int32_t INDEX_S = 1;
constexpr int32_t INDEX_E = 2;
} // namespace

int32_t StylusDetectorCallBack::RequestFocus(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler)
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

int32_t StylusDetectorCallBack::SetText(int32_t nodeId, void* data,
    const RefPtr<TaskExecutor>& taskScheduler, std::shared_ptr<IAceStylusCallback> callback)
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

int32_t StylusDetectorCallBack::GetText(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler,
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

int32_t StylusDetectorCallBack::Redo(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler)
{
    taskScheduler->PostTask(
        [nodeId]() {
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            CHECK_EQUAL_VOID(frameNode->GetTag(), V2::RICH_EDITOR_ETS_TAG);
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->CloseSelectOverlay(true);
            pattern->HandleOnRedoAction();
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
    return 0;
}

int32_t StylusDetectorCallBack::Undo(int32_t nodeId, const RefPtr<TaskExecutor>& taskScheduler)
{
    taskScheduler->PostTask(
        [nodeId]() {
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            CHECK_EQUAL_VOID(frameNode->GetTag(), V2::RICH_EDITOR_ETS_TAG);
            auto pattern = frameNode->GetPattern<NG::TextFieldPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->CloseSelectOverlay(true);
            pattern->HandleOnUndoAction();
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE_SELF);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorStylusAction");
    return 0;
}

int32_t StylusDetectorCallBack::DeleteText(int32_t nodeId, void* data,
    const RefPtr<TaskExecutor>& taskScheduler)
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
            ContainerScope scope(frameNode->GetInstanceId());
            Offset startCenterGlobalOffset = Offset(rect.Left, rect.Top + rect.Height / 2);
            Offset endCenterGlobalOffset = Offset(rect.Left + rect.Width, rect.Top + rect.Height / 2);
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
                textInputClient->DeleteRange(std::get<INDEX_S>(ret), std::get<INDEX_E>(ret));
                resultCode = 0;
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorCallBack::ChoiceText(int32_t nodeId, void* data,
    const RefPtr<TaskExecutor>& taskScheduler)
{
    int32_t resultCode = -1;
    ChoiceTextOption *optionPtr = static_cast<ChoiceTextOption*>(data);
    CHECK_NULL_RETURN(optionPtr, resultCode);
    auto choiceTextOption = *optionPtr;
    taskScheduler->PostSyncTask(
        [&resultCode, nodeId, choiceTextOption]() {
            auto rect = choiceTextOption.rect;
            auto UiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
            auto frameNode = AceType::DynamicCast<NG::FrameNode>(UiNode);
            CHECK_NULL_VOID(frameNode);
            ContainerScope scope(frameNode->GetInstanceId());
            Offset startCenterGlobalOffset = Offset(rect.Left, rect.Top + rect.Height / 2);
            Offset endCenterGlobalOffset = Offset(rect.Left + rect.Width, rect.Top + rect.Height / 2);
            auto sInd = GetGlyphPositionByGlobalOffset(frameNode, startCenterGlobalOffset);
            auto eInd = GetGlyphPositionByGlobalOffset(frameNode, endCenterGlobalOffset);
            auto textBase = frameNode->GetPattern<NG::TextBase>();
            CHECK_NULL_VOID(textBase);
            auto wtextLength = textBase->GetContentWideTextLength();
            TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture wtextLength:%{public}d", wtextLength);
            if (!StylusDetectorMgr::GetInstance()->HasSelectChanged(static_cast<int32_t>(sInd.position_),
                static_cast<int32_t>(eInd.position_), choiceTextOption.showMenu)) {
                return;
            }
            StylusDetectorMgr::GetInstance()->SetSelectState(static_cast<int32_t>(sInd.position_),
                static_cast<int32_t>(eInd.position_), choiceTextOption.showMenu);
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

int32_t StylusDetectorCallBack::InsertSpace(int32_t nodeId, void* data,
    const RefPtr<TaskExecutor>& taskScheduler)
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
            ContainerScope scope(frameNode->GetInstanceId());
            Offset centerGlobalOffset = Offset(rect.Left + rect.Width / 2, rect.Top + rect.Height / 2);
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

int32_t StylusDetectorCallBack::MoveCursor(int32_t nodeId, void* data,
    const RefPtr<TaskExecutor>& taskScheduler)
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
            ContainerScope scope(frameNode->GetInstanceId());
            Offset centerGlobalOffset = Offset(point.x, point.y);
            auto sInd = GetGlyphPositionByGlobalOffset(frameNode, centerGlobalOffset);
            resultCode = HandleMoveCursor(frameNode, sInd, point.showHandle);
        },
        TaskExecutor::TaskType::UI, "ArkUIDetectorSyncStylusAction");
    return resultCode;
}

int32_t StylusDetectorCallBack::HandleMoveCursor(const RefPtr<NG::FrameNode>& frameNode,
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

NG::PositionWithAffinity StylusDetectorCallBack::GetGlyphPositionByGlobalOffset(
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
    auto textDragBase = frameNode->GetPattern<NG::TextDragBase>();
    CHECK_NULL_RETURN(textDragBase, finalResult);
    auto textRect = textDragBase->GetTextRect();
    if (localOffset.GetY() < textRect.GetY() || localOffset.GetY() > textRect.GetY() + textRect.Height()) {
        TAG_LOGI(AceLogTag::ACE_STYLUS, "stylusGesture point outside the area");
        return finalResult;
    }
    auto textContentRect = textDragBase->GetTextContentRect();
    localOffset.SetX(std::clamp(localOffset.GetX(), static_cast<double>(textContentRect.Left()),
        static_cast<double>(textContentRect.Right())));
    // calculate the start and end indexes of the intersecting region.
    auto layoutInfo = StylusDetectorMgr::GetInstance()->GetLayoutInfo().Upgrade();
    CHECK_NULL_RETURN(layoutInfo, finalResult);
    return layoutInfo->GetGlyphPositionAtCoordinate(localOffset.GetX(), localOffset.GetY());
}

std::tuple<int32_t, int32_t, int32_t> StylusDetectorCallBack::CalculateIntersectedRegion(
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

NG::OffsetF StylusDetectorCallBack::GetPaintRectGlobalOffset(
    const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, NG::OffsetF(0.0f, 0.0f));
    auto pipeline = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, NG::OffsetF(0.0f, 0.0f));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto textPaintOffset = frameNode->GetPaintRectOffset();
    return textPaintOffset - rootOffset;
}

int32_t StylusDetectorCallBack::OnDetector(
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
            return StylusDetectorCallBack::RequestFocus(nodeId, taskScheduler);
        case COMMAND_MOVE_CURSOR:
            return StylusDetectorCallBack::MoveCursor(nodeId, data, taskScheduler);
        case COMMAND_DELETE_TEXT:
            return StylusDetectorCallBack::DeleteText(nodeId, data, taskScheduler);
        case COMMAND_CHOICE_TEXT:
            return StylusDetectorCallBack::ChoiceText(nodeId, data, taskScheduler);
        case COMMAND_INSERT_SPACE:
            return StylusDetectorCallBack::InsertSpace(nodeId, data, taskScheduler);
        case COMMAND_CLEAR_HIT:
            return resultCode;
        case COMMAND_SET_TEXT:
            return StylusDetectorCallBack::SetText(nodeId, data, taskScheduler, callback);
        case COMMAND_GET_TEXT:
            return StylusDetectorCallBack::GetText(nodeId, taskScheduler, callback);
        case COMMAND_UNDO:
            return StylusDetectorCallBack::Undo(nodeId, taskScheduler);
        case COMMAND_REDO:
            return StylusDetectorCallBack::Redo(nodeId, taskScheduler);
        case COMMAND_INVALID:
            TAG_LOGE(AceLogTag::ACE_STYLUS, "StylusDetector received error command.");
            return resultCode;
        default:
            return resultCode;
    }
}

bool StylusDetectorCallBack::OnDetectorSync(const CommandType& command)
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
} // namespace OHOS::Ace