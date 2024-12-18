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

#include "core/components_ng/manager/form_gesture/form_gesture_manager.h"
#include "core/components_ng/gestures/recognizers/recognizer_group.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void FormGestureManager::LinkGesture(const AxisEvent& event, PipelineContext* pipeline,
    const RefPtr<FrameNode>& node, std::unordered_map<size_t, TouchTestResult>& axisTouchTestResults,
    SerializedGesture& etsSerializedGesture, RefPtr<EventManager>& eventManager)
{
    if (!etsSerializedGesture.data.empty()) {
        GestureGroup rebirth(GestureMode::Exclusive);
        rebirth.Deserialize(etsSerializedGesture.data.data());
        auto recognizer = rebirth.CreateRecognizer();
        if (recognizer) {
            recognizer->SetInnerFlag(true);
            recognizer->BeginReferee(event.id, true);
            std::list<RefPtr<NGGestureRecognizer>> combined;
            combined.emplace_back(recognizer);
            for (auto iter = axisTouchTestResults[event.id].begin();
                iter != axisTouchTestResults[event.id].end(); iter++) {
                auto outRecognizer = AceType::DynamicCast<NGGestureRecognizer>(*iter);
                if (outRecognizer) {
                    combined.emplace_back(outRecognizer);
                    axisTouchTestResults[event.id].erase(iter);
                    break;
                }
            }
            auto exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(std::move(combined));
            exclusiveRecognizer->AttachFrameNode(node);
            exclusiveRecognizer->BeginReferee(event.id);
            axisTouchTestResults[event.id].emplace_back(exclusiveRecognizer);
            eventManager->SetAxisTouchTestResults(axisTouchTestResults);
            eventManager->SetInnerFlag(true);
        }
    }
    if (pipeline && pipeline->IsFormRender() && axisTouchTestResults.find(event.id) != axisTouchTestResults.end()) {
        for (const auto& touchResult : axisTouchTestResults[event.id]) {
            auto recognizer = AceType::DynamicCast<RecognizerGroup>(touchResult);
            if (recognizer) {
                auto gesture = recognizer->CreateGestureFromRecognizer();
                if (gesture) {
                    pipeline->serializedGesture_.data = std::vector<char>(gesture->SizeofMe());
                    gesture->Serialize(pipeline->serializedGesture_.data.data());
                }
                break;
            }
        }
    }
}

} // namespace OHOS::Ace::NG

