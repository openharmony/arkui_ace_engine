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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_common_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::Framework::CommonUtils {

JSRef<JSObject> CreateFingerInfo(const FingerInfo& fingerInfo)
{
    JSRef<JSObject> fingerInfoObj = JSRef<JSObject>::New();
    const OHOS::Ace::Offset& globalLocation = fingerInfo.globalLocation_;
    const OHOS::Ace::Offset& localLocation = fingerInfo.localLocation_;
    const OHOS::Ace::Offset& screenLocation = fingerInfo.screenLocation_;
    fingerInfoObj->SetProperty<int32_t>("id", fingerInfo.fingerId_);
    fingerInfoObj->SetProperty<double>("globalX", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetX()));
    fingerInfoObj->SetProperty<double>("globalY", PipelineBase::Px2VpWithCurrentDensity(globalLocation.GetY()));
    fingerInfoObj->SetProperty<double>("localX", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetX()));
    fingerInfoObj->SetProperty<double>("localY", PipelineBase::Px2VpWithCurrentDensity(localLocation.GetY()));
    fingerInfoObj->SetProperty<double>("displayX", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetX()));
    fingerInfoObj->SetProperty<double>("displayY", PipelineBase::Px2VpWithCurrentDensity(screenLocation.GetY()));
    return fingerInfoObj;
}

JSRef<JSObject> CreateEventTargetObject(const std::shared_ptr<BaseGestureEvent>& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> target = objectTemplate->NewInstance();
    JSRef<JSObject> area = objectTemplate->NewInstance();
    JSRef<JSObject> offset = objectTemplate->NewInstance();
    JSRef<JSObject> globalOffset = objectTemplate->NewInstance();
    const auto& localOffset = info->GetTarget().area.GetOffset();
    const auto& origin = info->GetTarget().origin;
    offset->SetProperty<double>("x", localOffset.GetX().ConvertToVp());
    offset->SetProperty<double>("y", localOffset.GetY().ConvertToVp());
    globalOffset->SetProperty<double>("x", (origin.GetX().ConvertToVp() + localOffset.GetX().ConvertToVp()));
    globalOffset->SetProperty<double>("y", (origin.GetY().ConvertToVp() + localOffset.GetY().ConvertToVp()));
    area->SetPropertyObject("position", offset);
    area->SetPropertyObject("globalPosition", globalOffset);
    area->SetProperty<double>("width", info->GetTarget().area.GetWidth().ConvertToVp());
    area->SetProperty<double>("height", info->GetTarget().area.GetHeight().ConvertToVp());
    target->SetPropertyObject("area", area);
    if (!info->GetTarget().id.empty()) {
        target->SetProperty<const char*>("id", info->GetTarget().id.c_str());
    } else {
        target->SetPropertyObject("id", JsiValue::Undefined());
    }
    return target;
}

bool SetBaseGestureEventInfo(JSRef<JSObject> obj, const std::shared_ptr<BaseGestureEvent>& info)
{
    CHECK_NULL_RETURN(info, false);
    obj->SetProperty<double>("timestamp", info->GetTimeStamp().time_since_epoch().count());
    obj->SetProperty<double>("source", static_cast<int32_t>(info->GetSourceDevice()));
    obj->SetProperty<double>("pressure", info->GetForce());
    obj->SetProperty<double>("tiltX", info->GetTiltX().value_or(0.0f));
    obj->SetProperty<double>("tiltY", info->GetTiltY().value_or(0.0f));
    obj->SetProperty<double>("rollAngle", info->GetRollAngle().value_or(0.0f));
    obj->SetProperty<double>("sourceTool", static_cast<int32_t>(info->GetSourceTool()));
    obj->SetProperty<double>("deviceId", static_cast<int32_t>(info->GetDeviceId()));
    obj->SetProperty<int32_t>("targetDisplayId", info->GetTargetDisplayId());
    obj->SetProperty<float>("axisVertical", info->GetVerticalAxis());
    obj->SetProperty<float>("axisHorizontal", info->GetHorizontalAxis());
    obj->SetPropertyObject(
        "getModifierKeyState", JSRef<JSFunc>::New<FunctionCallback>(NG::ArkTSUtils::JsGetModifierKeyState));
    CreateFingerInfosObject(info, obj);
    return true;
}

JSRef<JSObject> CreateFingerInfosObject(const std::shared_ptr<BaseGestureEvent>& info, JSRef<JSObject>& obj)
{
    JSRef<JSArray> fingerArr = JSRef<JSArray>::New();
    const std::list<FingerInfo>& fingerList = info->GetFingerList();
    std::list<FingerInfo> notTouchFingerList;
    std::vector<JSRef<JSObject>> validFingers;
    for (const FingerInfo& fingerInfo : fingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        if (fingerInfo.sourceType_ == SourceType::TOUCH && fingerInfo.sourceTool_ == SourceTool::FINGER) {
            validFingers.emplace_back(element);
        } else {
            notTouchFingerList.emplace_back(fingerInfo);
        }
    }
    for (size_t i = 0; i < validFingers.size(); ++i) {
        fingerArr->SetValueAt(i, validFingers[i]);
    }
    auto idx = validFingers.size();
    for (const FingerInfo& fingerInfo : notTouchFingerList) {
        JSRef<JSObject> element = CreateFingerInfo(fingerInfo);
        fingerArr->SetValueAt(idx++, element);
    }
    obj->SetPropertyObject("fingerInfos", fingerArr);
    return obj;
}
} // namespace OHOS::Ace::Framework::CommonUtils
