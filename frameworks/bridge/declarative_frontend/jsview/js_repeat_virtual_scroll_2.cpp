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

#include "bridge/declarative_frontend/jsview/js_repeat_virtual_scroll_2.h"

#include <string>

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<RepeatVirtualScroll2Model> RepeatVirtualScroll2Model::instance_ = nullptr;
#define UNUSED_CACHED_SIZE_PARAM 2

RepeatVirtualScroll2Model* RepeatVirtualScroll2Model::GetInstance()
{
    if (!instance_) {
        instance_.reset(new NG::RepeatVirtualScroll2ModelNG());
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

enum CreateParam {
    TOTAL_COUNT = 0,
    HANDLERS = 1,
    SIZE = 2,
};

static JSRef<JSFunc> GetJSFunc(JsiRef<JSObject> options, const char* propertyName)
{
    return JSRef<JSFunc>::Cast(options->GetProperty(propertyName));
}

static bool ParseAndVerifyParams(const JSCallbackInfo& info)
{
    if (info.Length() != CreateParam::SIZE ||
        !info[CreateParam::TOTAL_COUNT]->IsNumber() ||
        !info[CreateParam::HANDLERS]->IsObject()) {
        return false;
    }

    auto handlers = JSRef<JSObject>::Cast(info[CreateParam::HANDLERS]);
    return (handlers->GetProperty("onGetRid4Index")->IsFunction() &&
            handlers->GetProperty("onRecycleItems")->IsFunction() &&
            handlers->GetProperty("onActiveRange")->IsFunction() &&
            handlers->GetProperty("onPurge")->IsFunction());
}

void JSRepeatVirtualScroll2::Create(const JSCallbackInfo& info)
{
    if (!ParseAndVerifyParams(info)) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "Invalid arguments for RepeatVirtualScroll");
        return;
    }

    // arg 0 totalCount : number
    auto totalCount = info[CreateParam::TOTAL_COUNT]->ToNumber<uint32_t>();

    // arg 2 onGetRid4Index(number int32_t) : number(uint32_t)
    auto handlers = JSRef<JSObject>::Cast(info[CreateParam::HANDLERS]);
    auto onGetRid4Index = [execCtx = info.GetExecutionContext(), func = GetJSFunc(handlers, "onGetRid4Index")](
                              int32_t forIndex) -> std::pair<uint32_t, uint32_t> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, std::pair<uint32_t, uint32_t>(0, 0));
        auto params = ConvertToJSValues(forIndex);
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), params.size(), params.data());
        // convert js-array to std::pair
        if (!jsVal->IsArray() || JSRef<JSArray>::Cast(jsVal)->Length() != 2) {
            TAG_LOGW(AceLogTag::ACE_REPEAT, "jsVal should be array.");
            return std::pair<uint32_t, uint32_t>(0, 0);
        }
        JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(jsVal);
        return std::pair<uint32_t, uint32_t>(
            jsArr->GetValueAt(0)->ToNumber<uint32_t>(), jsArr->GetValueAt(1)->ToNumber<uint32_t>());
    };

    auto onRecycleItems = [execCtx = info.GetExecutionContext(), func = GetJSFunc(handlers, "onRecycleItems")](
                              int32_t fromIndex, int32_t toIndex) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(fromIndex, toIndex);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onActiveRange = [execCtx = info.GetExecutionContext(), func = GetJSFunc(handlers, "onActiveRange")](
        int32_t fromIndex, int32_t toIndex, bool isLoop) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(
            fromIndex != INT32_MAX ? fromIndex : std::numeric_limits<double>::quiet_NaN(),
            toIndex != INT32_MAX ? toIndex : std::numeric_limits<double>::quiet_NaN(),
            isLoop);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onPurge = [execCtx = info.GetExecutionContext(), func = GetJSFunc(handlers, "onPurge")]() {
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), 0, nullptr);
    };

    RepeatVirtualScroll2Model::GetInstance()->Create(totalCount, onGetRid4Index, onRecycleItems, onActiveRange,
        onPurge);
}

void JSRepeatVirtualScroll2::RemoveNode(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:RemoveNode");
    if (!info[0]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RemoveNode - invalid parameter ERROR.");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RemoveNode");
    auto rid = info[0]->ToNumber<uint32_t>();
    RepeatVirtualScroll2Model::GetInstance()->RemoveNode(rid);
}

// setInvalid(repeatElmtId : number, fromIndex : number)
void JSRepeatVirtualScroll2::SetInvalid(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:SetInvalid");
    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::SetInvalid - invalid parameter ERROR");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::SetInvalid");
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto rid = info[1]->ToNumber<uint32_t>();
    RepeatVirtualScroll2Model::GetInstance()->SetInvalid(repeatElmtId, rid);
}

// requestContainerReLayout(repeatElmtId: number, totalCount: number, index: number): void;
void JSRepeatVirtualScroll2::RequestContainerReLayout(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:RequestContainerReLayout");
    enum RequestContainerReLayoutParam {
        ELMTID = 0,
        TOTAL_COUNT = 1,
        CHILD_INDEX = 2,
    };

    if (!info[RequestContainerReLayoutParam::ELMTID]->IsNumber() ||
        !info[RequestContainerReLayoutParam::TOTAL_COUNT]->IsNumber() ||
        !info[RequestContainerReLayoutParam::CHILD_INDEX]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RequestContainerReLayout - invalid parameters ERROR");
        return;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RequestContainerReLayout");
    auto repeatElmtId = info[RequestContainerReLayoutParam::ELMTID]->ToNumber<int32_t>();
    auto totalCount = info[RequestContainerReLayoutParam::TOTAL_COUNT]->ToNumber<int32_t>();
    auto invalidateContainerLayoutFromChildIndex =
        info[RequestContainerReLayoutParam::CHILD_INDEX]->ToNumber<int32_t>();
    RepeatVirtualScroll2Model::GetInstance()->RequestContainerReLayout(
        repeatElmtId, totalCount, invalidateContainerLayoutFromChildIndex);
}

// updateL1Rid4Index(repeatElmtId: number,
//   totalCount: number,
//   invalidateContainerLayoutFromChildIndex: number,
//   l1rid4index: Array<Array<number>>): void;
void JSRepeatVirtualScroll2::UpdateL1Rid4Index(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:UpdateL1Rid4Index");
    enum UpdateL1Rid4IndexParam {
        ELMTID = 0,
        TOTAL_COUNT = 1,
        CHILD_INDEX = 2,
        ARRAY_PAIRS = 3,
    };

    if (!info[UpdateL1Rid4IndexParam::ELMTID]->IsNumber() ||
        !info[UpdateL1Rid4IndexParam::TOTAL_COUNT]->IsNumber() ||
        !info[UpdateL1Rid4IndexParam::CHILD_INDEX]->IsNumber() ||
        !info[UpdateL1Rid4IndexParam::ARRAY_PAIRS]->IsArray()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::UpdateL1Rid4Index - invalid parameters ERROR");
        return;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::UpdateL1Rid4Index");
    auto repeatElmtId = info[UpdateL1Rid4IndexParam::ELMTID]->ToNumber<int32_t>();
    auto totalCount = info[UpdateL1Rid4IndexParam::TOTAL_COUNT]->ToNumber<uint32_t>();
    auto invalidateContainerLayoutFromChildIndex = info[UpdateL1Rid4IndexParam::CHILD_INDEX]->ToNumber<uint32_t>();

    auto arrayOfPairs = JSRef<JSArray>::Cast(info[UpdateL1Rid4IndexParam::ARRAY_PAIRS]);
    std::map<int32_t, uint32_t> l1Rid4Index;
    for (size_t i = 0; i < arrayOfPairs->Length(); i++) {
        JSRef<JSArray> pair = arrayOfPairs->GetValueAt(i);
        auto index = pair->GetValueAt(0)->ToNumber<int32_t>();
        auto rid = pair->GetValueAt(1)->ToNumber<uint32_t>();
        TAG_LOGD(AceLogTag::ACE_REPEAT, "   ... index: %{public}d rid: %{public}d", index, static_cast<uint32_t>(rid));
        l1Rid4Index[index] = rid;
    }
    RepeatVirtualScroll2Model::GetInstance()->UpdateL1Rid4Index(
        repeatElmtId, totalCount, invalidateContainerLayoutFromChildIndex, l1Rid4Index);
}

void JSRepeatVirtualScroll2::OnMove(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        RepeatVirtualScroll2Model::GetInstance()->OnMove(nullptr);
        return;
    }
    auto onMove = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(info[0])](
                      int32_t from, int32_t to) {
        auto params = ConvertToJSValues(from, to);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };
    RepeatVirtualScroll2Model::GetInstance()->OnMove(std::move(onMove));
}

void JSRepeatVirtualScroll2::JSBind(BindingTarget globalObj)
{
    JSClass<JSRepeatVirtualScroll2>::Declare("RepeatVirtualScroll2Native");
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("create", &JSRepeatVirtualScroll2::Create);

    JSClass<JSRepeatVirtualScroll2>::StaticMethod("removeNode", &JSRepeatVirtualScroll2::RemoveNode);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("setInvalid", &JSRepeatVirtualScroll2::SetInvalid);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod(
        "requestContainerReLayout", &JSRepeatVirtualScroll2::RequestContainerReLayout);

    JSClass<JSRepeatVirtualScroll2>::StaticMethod("updateL1Rid4Index", &JSRepeatVirtualScroll2::UpdateL1Rid4Index);

    JSClass<JSRepeatVirtualScroll2>::StaticMethod("onMove", &JSRepeatVirtualScroll2::OnMove);
    JSClass<JSRepeatVirtualScroll2>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
