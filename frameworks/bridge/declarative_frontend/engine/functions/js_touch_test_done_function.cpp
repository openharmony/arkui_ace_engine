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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_touch_test_done_function.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_should_built_in_recognizer_parallel_with_function.h"
#include "bridge/declarative_frontend/engine/functions/js_gesture_judge_function.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/gestures/base_gesture_event.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_common_utils.h"

namespace OHOS::Ace::Framework {

bool JsTouchTestDoneFunction::Execute(
    const std::shared_ptr<BaseGestureEvent>& info, const std::list<RefPtr<NG::NGGestureRecognizer>>& others)
{
    CHECK_NULL_RETURN(info, false);
    auto obj = CreateGestureEventObject(info);
    int32_t paramCount = 2;
    JSRef<JSVal> params[paramCount];
    params[0] = obj;
    JSRef<JSArray> othersArr = JSRef<JSArray>::New();
    uint32_t othersIdx = 0;
    for (const auto& item : others) {
        auto othersObj = JsShouldBuiltInRecognizerParallelWithFunction::CreateRecognizerObject(item);
        othersArr->SetValueAt(othersIdx++, othersObj);
    }
    params[1] = othersArr;
    JsFunction::ExecuteJS(paramCount, params);
    return true;
}

JSRef<JSObject> JsTouchTestDoneFunction::CreateGestureEventObject(const std::shared_ptr<BaseGestureEvent>& info)
{
    JSRef<JSObjTemplate> objTemp = JSRef<JSObjTemplate>::New();
    objTemp->SetInternalFieldCount(1);
    JSRef<JSObject> obj = objTemp->NewInstance();
    CommonUtils::SetBaseGestureEventInfo(obj, info);
    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    int32_t maxFingerId = -1;
    for (const FingerInfo& fingerInfo : fingerList) {
        JSRef<JSObject> element = CommonUtils::CreateFingerInfo(fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            fingerArr->SetValueAt(fingerInfo.fingerId_, element);
            if (fingerInfo.fingerId_ > maxFingerId) {
                maxFingerId = fingerInfo.fingerId_;
            }
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    auto idx = maxFingerId + 1;
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        JSRef<JSObject> element = CommonUtils::CreateFingerInfo(fingerInfo);
        fingerArr->SetValueAt(idx++, element);
    }
    obj->SetPropertyObject("fingerList", fingerArr);
    auto target = CommonUtils::CreateEventTargetObject(info);
    obj->SetPropertyObject("target", target);
    obj->Wrap<BaseGestureEvent>(info.get());
    return obj;
}
} // namespace OHOS::Ace::Framework
