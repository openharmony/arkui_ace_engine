/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_relative_container.h"

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/models/relative_container_model_impl.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {

constexpr int32_t LOCALIZED_BARRIER_DIRECTION_START = 4;

RelativeContainerModel* RelativeContainerModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::RelativeContainerModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::RelativeContainerModelNG instance;
        return &instance;
    } else {
        static Framework::RelativeContainerModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSRelativeContainer::JSBind(BindingTarget globalObj)
{
    JSClass<JSRelativeContainer>::Declare("RelativeContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRelativeContainer>::StaticMethod("create", &JSRelativeContainer::Create, opt);
    JSClass<JSRelativeContainer>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRelativeContainer>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRelativeContainer>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRelativeContainer>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRelativeContainer>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRelativeContainer>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRelativeContainer>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRelativeContainer>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRelativeContainer>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRelativeContainer>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSRelativeContainer>::StaticMethod("barrier", &JSRelativeContainer::JsBarrier);
    JSClass<JSRelativeContainer>::StaticMethod("guideLine", &JSRelativeContainer::JsGuideline);
    JSClass<JSRelativeContainer>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSRelativeContainer::Create(const JSCallbackInfo& info)
{
    RelativeContainerModel::GetInstance()->Create();
}

void JSRelativeContainer::ParseBarrierInfo(const JSRef<JSVal>& args, BarrierInfo& barrierInfoItem)
{
    if (!args->IsObject()) {
        return;
    }
    JSRef<JSObject> barrierInfoObj = JSRef<JSObject>::Cast(args);
    JSRef<JSVal> idVal = barrierInfoObj->GetProperty("id");
    JSRef<JSVal> directionVal = barrierInfoObj->GetProperty("direction");
    JSRef<JSVal> localizedDirectionVal = barrierInfoObj->GetProperty("localizedDirection");
    JSRef<JSVal> referencedIdVal = barrierInfoObj->GetProperty("referencedId");

    if (idVal->IsString()) {
        barrierInfoItem.id = idVal->ToString();
    }

    if (directionVal->IsNumber()) {
        auto direction = directionVal->ToNumber<int32_t>();
        barrierInfoItem.direction = static_cast<BarrierDirection>(direction);
    } else if (localizedDirectionVal->IsNumber()) {
        auto direction = localizedDirectionVal->ToNumber<int32_t>();
        if (direction > static_cast<int32_t>(BarrierDirection::RIGHT)) {
            barrierInfoItem.direction = static_cast<BarrierDirection>(direction);
        } else {
            barrierInfoItem.direction = static_cast<BarrierDirection>(direction + LOCALIZED_BARRIER_DIRECTION_START);
        }
    }

    if (referencedIdVal->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(referencedIdVal);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> idVal = array->GetValueAt(i);
            if (idVal->IsString()) {
                barrierInfoItem.referencedId.emplace_back(idVal->ToString());
            }
        }
    }
}

void JSRelativeContainer::JsBarrier(const JSCallbackInfo& info)
{
    auto tmpInfo = info[0];
    std::vector<BarrierInfo> barrierInfos;
    if (tmpInfo->IsUndefined()) {
        RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
        return;
    }
    if (!tmpInfo->IsArray() && !tmpInfo->IsObject()) {
        RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
        return;
    }

    if (tmpInfo->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(tmpInfo);
        for (size_t i = 0; i < array->Length(); i++) {
            BarrierInfo barrierInfoItem;
            ParseBarrierInfo(array->GetValueAt(i), barrierInfoItem);
            barrierInfos.emplace_back(barrierInfoItem);
        }
    }

    RelativeContainerModel::GetInstance()->SetBarrier(barrierInfos);
}

void JSRelativeContainer::ParseGuideline(const JSRef<JSVal>& args, GuidelineInfo& guidelineInfoItem)
{
    if (!args->IsObject()) {
        return;
    }
    JSRef<JSObject> guildLineInfoObj = JSRef<JSObject>::Cast(args);
    JSRef<JSVal> idVal = guildLineInfoObj->GetProperty("id");
    JSRef<JSVal> directionVal = guildLineInfoObj->GetProperty("direction");
    JSRef<JSVal> positionVal = guildLineInfoObj->GetProperty("position");

    if (idVal->IsString()) {
        guidelineInfoItem.id = idVal->ToString();
    }

    if (directionVal->IsNumber()) {
        auto direction = directionVal->ToNumber<int32_t>();
        guidelineInfoItem.direction = static_cast<LineDirection>(direction);
    }

    CalcDimension start;
    CalcDimension end;
    if (positionVal->IsObject()) {
        JSRef<JSObject> val = JSRef<JSObject>::Cast(positionVal);
        JSRef<JSVal> startVal = val->GetProperty("start");
        JSRef<JSVal> endVal = val->GetProperty("end");
        RefPtr<ResourceObject> startResObj;
        RefPtr<ResourceObject> endResObj;

        if (JSViewAbstract::ParseJsDimensionVpNG(startVal, start, startResObj)) {
            guidelineInfoItem.start = start;
        }
        if (SystemProperties::ConfigChangePerform() && startResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, GuidelineInfo& guidelineInfo) {
                CalcDimension result;
                ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
                guidelineInfo.start = result;
            };
            guidelineInfoItem.AddResource("relativeContainer.guideLine.position.start",
                startResObj, std::move(updateFunc));
        }
        if (JSViewAbstract::ParseJsDimensionVpNG(endVal, end, endResObj)) {
            guidelineInfoItem.end = end;
        }
        if (SystemProperties::ConfigChangePerform() && endResObj) {
            auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, GuidelineInfo& guidelineInfo) {
                CalcDimension result;
                ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
                guidelineInfo.end = result;
            };
            guidelineInfoItem.AddResource("relativeContainer.guideLine.position.end",
                endResObj, std::move(updateFunc));
        }
    }
}

void JSRelativeContainer::JsGuideline(const JSCallbackInfo& info)
{
    RelativeContainerModel::GetInstance()->ResetResObj("relativeContainer.guideLine");
    auto tmpInfo = info[0];
    std::vector<GuidelineInfo> guidelineInfos;
    if (tmpInfo->IsUndefined()) {
        RelativeContainerModel::GetInstance()->SetGuideline(guidelineInfos);
        return;
    }
    if (!tmpInfo->IsArray() && !tmpInfo->IsObject()) {
        RelativeContainerModel::GetInstance()->SetGuideline(guidelineInfos);
        return;
    }

    if (tmpInfo->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(tmpInfo);
        for (size_t i = 0; i < array->Length(); i++) {
            GuidelineInfo guidelineInfoItem;
            ParseGuideline(array->GetValueAt(i), guidelineInfoItem);
            guidelineInfos.emplace_back(guidelineInfoItem);
        }
    }
    RelativeContainerModel::GetInstance()->SetGuideline(guidelineInfos);
}
} // namespace OHOS::Ace::Framework
