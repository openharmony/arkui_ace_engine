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
#include <vector>

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/engine/functions/js_callback_state.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<RepeatVirtualScroll2Model> RepeatVirtualScroll2Model::instance_ = nullptr;

RepeatVirtualScroll2Model* RepeatVirtualScroll2Model::GetInstance()
{
    if (!instance_) {
        instance_.reset(new NG::RepeatVirtualScroll2ModelNG());
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {
void CallJsFuncWithIndex(const JSRef<JSFunc>& func, int32_t index)
{
    auto params = ConvertToJSValues(index);
    func->Call(JSRef<JSObject>(), params.size(), params.data());
}

void CallJsFuncWithFromTo(const JSRef<JSFunc>& func, int32_t from, int32_t to)
{
    auto params = ConvertToJSValues(from, to);
    func->Call(JSRef<JSObject>(), params.size(), params.data());
}
} // namespace

// RepeatVirtualScroll2Native.create() positional arguments:
//   0: arrLen (number)
//   1: totalCount (number)
//   2: memOptStrategy (number)
//   3: handlers (object; the handler functions it carries are validated in Create)
static bool ParseAndVerifyParams(const JSCallbackInfo& info)
{
    if (info.Length() != 4 || !info[0]->IsNumber() || !info[1]->IsNumber() ||
        !info[2]->IsNumber() || !info[3]->IsObject()) {
        return false;
    }
    return true;
}

void JSRepeatVirtualScroll2::Create(const JSCallbackInfo& info)
{
    if (!ParseAndVerifyParams(info)) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "Invalid arguments for RepeatVirtualScroll2");
        return;
    }

    // arg 0 arrLen : number
    auto arrLen = info[0]->ToNumber<uint32_t>();

    // arg 1 totalCount : number
    auto totalCount = info[1]->ToNumber<uint32_t>();

    // arg 2 memOptStrategy : number
    auto memOptStrategy = info[2]->ToNumber<int32_t>();

    // arg 3 onGetRid4Index(number int32_t) : number(uint32_t)
    // Each IsFunction check must stay immediately after its own GetProperty so it
    // validates the exact reference that gets bound below, not a re-fetched value.
    auto handlers = JSRef<JSObject>::Cast(info[3]);
    auto onGetRid4IndexFunc = handlers->GetProperty("onGetRid4Index");
    if (!onGetRid4IndexFunc->IsFunction()) {
        return;
    }
    auto onGetRid4Index = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onGetRid4IndexFunc)](
        int32_t forIndex, bool isImplicitAnimationOpen, bool forceCreateNewChild) -> std::pair<uint32_t, uint32_t> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, std::pair<uint32_t, uint32_t>(0, 0));
        auto params = ConvertToJSValues(forIndex, isImplicitAnimationOpen, forceCreateNewChild);
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

    auto onRecycleItemsFunc = handlers->GetProperty("onRecycleItems");
    if (!onRecycleItemsFunc->IsFunction()) {
        return;
    }
    auto onRecycleItems = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onRecycleItemsFunc)](
                              int32_t fromIndex, int32_t toIndex) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(fromIndex, toIndex);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onActiveRangeFunc = handlers->GetProperty("onActiveRange");
    if (!onActiveRangeFunc->IsFunction()) {
        return;
    }
    auto onActiveRange = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onActiveRangeFunc)](
        int32_t fromIndex, int32_t toIndex, int32_t vStart, int32_t vEnd, bool isLoop, bool forceUpdate) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(
            fromIndex != INT32_MAX ? fromIndex : std::numeric_limits<double>::quiet_NaN(),
            toIndex != INT32_MAX ? toIndex : std::numeric_limits<double>::quiet_NaN(),
            vStart != INT32_MAX ? vStart : std::numeric_limits<double>::quiet_NaN(),
            vEnd != INT32_MAX ? vEnd : std::numeric_limits<double>::quiet_NaN(),
            isLoop, forceUpdate);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onMoveFromToFunc = handlers->GetProperty("onMoveFromTo");
    if (!onMoveFromToFunc->IsFunction()) {
        return;
    }
    auto onMoveFromTo = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onMoveFromToFunc)](
                              int32_t moveFrom, int32_t moveTo) -> void {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto params = ConvertToJSValues(moveFrom, moveTo);
        func->Call(JSRef<JSObject>(), params.size(), params.data());
    };

    auto onPurgeFunc = handlers->GetProperty("onPurge");
    if (!onPurgeFunc->IsFunction()) {
        return;
    }
    auto onPurge = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onPurgeFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), 0, nullptr);
    };

    auto onPurgeAllFunc = handlers->GetProperty("onPurgeAll");
    if (!onPurgeAllFunc->IsFunction()) {
        return;
    }
    auto onPurgeAll = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onPurgeAllFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), 0, nullptr);
    };

    auto onUpdateDirtyFunc = handlers->GetProperty("onUpdateDirty");
    if (!onUpdateDirtyFunc->IsFunction()) {
        return;
    }
    auto onUpdateDirty = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(onUpdateDirtyFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> jsVal = func->Call(JSRef<JSObject>(), 0, nullptr);
    };

    RepeatVirtualScroll2Model::GetInstance()->Create(
        arrLen, totalCount, memOptStrategy, onGetRid4Index, onRecycleItems, onActiveRange, onMoveFromTo, onPurge,
        onPurgeAll, onUpdateDirty);
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

void JSRepeatVirtualScroll2::RemoveNodes(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:RemoveNodes");
    if (!info[0]->IsArray() || !info[1]->IsArray()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RemoveNodes - invalid parameter ERROR.");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RemoveNodes");

    // Parse rids array from first parameter
    auto jsRidsArray = JSRef<JSArray>::Cast(info[0]);
    auto ridsArraySize = jsRidsArray->Length();
    std::vector<uint32_t> rids;
    rids.reserve(ridsArraySize);

    for (size_t i = 0; i < ridsArraySize; ++i) {
        auto element = jsRidsArray->GetValueAt(i);
        if (element->IsNumber()) {
            rids.push_back(element->ToNumber<uint32_t>());
        }
    }

    // Parse indexes array from second parameter
    auto jsIndexesArray = JSRef<JSArray>::Cast(info[1]);
    auto indexesArraySize = jsIndexesArray->Length();
    std::vector<int32_t> indexes;
    indexes.reserve(indexesArraySize);

    for (size_t i = 0; i < indexesArraySize; ++i) {
        auto element = jsIndexesArray->GetValueAt(i);
        if (element->IsNumber()) {
            indexes.push_back(element->ToNumber<int32_t>());
        }
    }

    // Call RemoveNodes with both rids and indexes
    RepeatVirtualScroll2Model::GetInstance()->RemoveNodes(rids, indexes);
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

// requestContainerReLayout positional arguments:
//   0: repeatElmtId (number)
//   1: arrLen (number)
//   2: totalCount (number)
//   3: invalidateContainerLayoutFromChildIndex (number, optional)
void JSRepeatVirtualScroll2::RequestContainerReLayout(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:RequestContainerReLayout");

    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RequestContainerReLayout - invalid parameters ERROR");
        return;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::RequestContainerReLayout");
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto arrLen = info[1]->ToNumber<uint32_t>();
    auto totalCount = info[2]->ToNumber<uint32_t>();

    if (!info[3]->IsNumber()) {
        RepeatVirtualScroll2Model::GetInstance()->RequestContainerReLayout(repeatElmtId, arrLen, totalCount);
    } else {
        auto invalidateContainerLayoutFromChildIndex = info[3]->ToNumber<int32_t>();
        RepeatVirtualScroll2Model::GetInstance()->RequestContainerReLayout(
            repeatElmtId, arrLen, totalCount, invalidateContainerLayoutFromChildIndex);
    }
}

// notifyContainerLayoutChange positional arguments:
//   0: repeatElmtId (number)
//   1: arrLen (number)
//   2: totalCount (number)
//   3: index (number)
//   4: count (number)
//   5: notificationType (number)
void JSRepeatVirtualScroll2::NotifyContainerLayoutChange(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:NotifyContainerLayoutChange");

    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
        !info[3]->IsNumber() || !info[4]->IsNumber() || !info[5]->IsNumber()) {
        TAG_LOGW(
            AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::NotifyContainerLayoutChange - invalid parameters ERROR");
        return;
    }

    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto arrLen = info[1]->ToNumber<uint32_t>();
    auto totalCount = info[2]->ToNumber<int32_t>();
    auto index = info[3]->ToNumber<int32_t>();
    auto count = info[4]->ToNumber<int32_t>();
    auto notificationType = static_cast<NG::UINode::NotificationType>(info[5]->ToNumber<int32_t>());

    RepeatVirtualScroll2Model::GetInstance()->NotifyContainerLayoutChange(
        repeatElmtId, arrLen, totalCount, index, count, notificationType);
}

// updateL1Rid4Index positional arguments:
//   0: repeatElmtId (number)
//   1: arrLen (number)
//   2: totalCount (number)
//   3: invalidateContainerLayoutFromChildIndex (number)
//   4: l1rid4index (Array<Array<number>>)
void JSRepeatVirtualScroll2::UpdateL1Rid4Index(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("RepeatVirtualScroll:UpdateL1Rid4Index");

    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
        !info[3]->IsNumber() || !info[4]->IsArray()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::UpdateL1Rid4Index - invalid parameters ERROR");
        return;
    }

    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::UpdateL1Rid4Index");
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto arrLen = info[1]->ToNumber<uint32_t>();
    auto totalCount = info[2]->ToNumber<uint32_t>();
    auto invalidateContainerLayoutFromChildIndex = info[3]->ToNumber<uint32_t>();

    auto arrayOfPairs = JSRef<JSArray>::Cast(info[4]);
    std::map<int32_t, uint32_t> l1Rid4Index;
    for (size_t i = 0; i < arrayOfPairs->Length(); i++) {
        JSRef<JSArray> pair = arrayOfPairs->GetValueAt(i);
        auto index = pair->GetValueAt(0)->ToNumber<int32_t>();
        auto rid = pair->GetValueAt(1)->ToNumber<uint32_t>();
        TAG_LOGD(AceLogTag::ACE_REPEAT, "   ... index: %{public}d rid: %{public}d", index, static_cast<uint32_t>(rid));
        l1Rid4Index[index] = rid;
    }

    RepeatVirtualScroll2Model::GetInstance()->UpdateL1Rid4Index(
        repeatElmtId, arrLen, totalCount, invalidateContainerLayoutFromChildIndex, l1Rid4Index);
}

// onMove positional arguments:
//   0: repeatElmtId (number)
//   1: onMove (function, optional)
//   2: itemDragHandler (object, optional)
void JSRepeatVirtualScroll2::OnMove(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::OnMove - invalid parameters ERROR");
        return;
    }
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    if (!info[1]->IsFunction()) {
        RepeatVirtualScroll2Model::GetInstance()->OnMove(repeatElmtId, nullptr);
        RepeatVirtualScroll2Model::GetInstance()->SetItemDragHandler(repeatElmtId, nullptr, nullptr, nullptr, nullptr);
        return;
    }
    auto context = info.GetExecutionContext();
    auto onMove = JsCallbackWithoutNode<void(int32_t, int32_t)>(
        context, JSRef<JSFunc>::Cast(info[1]), &CallJsFuncWithFromTo);
    RepeatVirtualScroll2Model::GetInstance()->OnMove(repeatElmtId, std::move(onMove));
    if ((info.Length() > 2) && info[2]->IsObject()) { // 2: Array length
        JsParseItemDragEventHandler(context, info[2], repeatElmtId);
    } else {
        RepeatVirtualScroll2Model::GetInstance()->SetItemDragHandler(repeatElmtId, nullptr, nullptr, nullptr, nullptr);
    }
}

// NOTE: this function and its CallJsFuncWithIndex/CallJsFuncWithFromTo helpers are duplicated
// verbatim in js_lazy_foreach.cpp, js_foreach.cpp and js_repeat.cpp; this variant additionally
// carries repeatElmtId. Any change here must be mirrored there; consolidating them into
// js_view_common_def.h is the tracked follow-up.
void JSRepeatVirtualScroll2::JsParseItemDragEventHandler(
    const JsiExecutionContext& context, const JSRef<JSObject>& itemDragEventObj, int32_t repeatElmtId)
{
    auto onLongPress = itemDragEventObj->GetProperty("onLongPress");
    std::function<void(int32_t)> onLongPressCallback;
    if (onLongPress->IsFunction()) {
        onLongPressCallback = JsCallbackWithoutNode<void(int32_t)>(
            context, JSRef<JSFunc>::Cast(onLongPress), &CallJsFuncWithIndex);
    }

    auto onDragStart = itemDragEventObj->GetProperty("onDragStart");
    std::function<void(int32_t)> onDragStartCallback;
    if (onDragStart->IsFunction()) {
        onDragStartCallback = JsCallbackWithoutNode<void(int32_t)>(
            context, JSRef<JSFunc>::Cast(onDragStart), &CallJsFuncWithIndex);
    }
    auto onMoveThrough = itemDragEventObj->GetProperty("onMoveThrough");
    std::function<void(int32_t, int32_t)> onMoveThroughCallback;
    if (onMoveThrough->IsFunction()) {
        onMoveThroughCallback = JsCallbackWithoutNode<void(int32_t, int32_t)>(
            context, JSRef<JSFunc>::Cast(onMoveThrough), &CallJsFuncWithFromTo);
    }
    auto onDrop = itemDragEventObj->GetProperty("onDrop");
    std::function<void(int32_t)> onDropCallback;
    if (onDrop->IsFunction()) {
        onDropCallback = JsCallbackWithoutNode<void(int32_t)>(
            context, JSRef<JSFunc>::Cast(onDrop), &CallJsFuncWithIndex);
    }
    RepeatVirtualScroll2Model::GetInstance()->SetItemDragHandler(repeatElmtId, std::move(onLongPressCallback),
        std::move(onDragStartCallback), std::move(onMoveThroughCallback), std::move(onDropCallback));
}

void JSRepeatVirtualScroll2::SetCreateByTemplate(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::SetCreateByTemplate wrong parameter, internal error.");
        return;
    }
    RepeatVirtualScroll2Model::GetInstance()->SetCreateByTemplate(info[0]->ToBoolean());
}

void JSRepeatVirtualScroll2::IsAllowAnimation(const JSCallbackInfo& info)
{
    if (!info[0]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::IsAllowAnimation - invalid parameter ERROR");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::IsAllowAnimation");
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto result = RepeatVirtualScroll2Model::GetInstance()->IsAllowAnimation(repeatElmtId);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

void JSRepeatVirtualScroll2::IsImplicitAnimationOpen(const JSCallbackInfo& info)
{
    auto result = RepeatVirtualScroll2Model::GetInstance()->IsImplicitAnimationOpen();
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

// isChildInAnimation positional arguments:
//   0: repeatElmtId (number)
//   1: rid (number)
void JSRepeatVirtualScroll2::IsChildInAnimation(const JSCallbackInfo& info)
{
    if ((info.Length() < 2) || !info[0]->IsNumber() || !info[1]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::IsChildInAnimation - invalid parameter ERROR");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::IsChildInAnimation");
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto rid = info[1]->ToNumber<uint32_t>();
    auto result = RepeatVirtualScroll2Model::GetInstance()->IsChildInAnimation(repeatElmtId, rid);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

// isChildOnMainTree positional arguments:
//   0: repeatElmtId (number)
//   1: rid (number)
void JSRepeatVirtualScroll2::IsChildOnMainTree(const JSCallbackInfo& info)
{
    if ((info.Length() < 2) || !info[0]->IsNumber() || !info[1]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::IsChildOnMainTree - invalid parameter ERROR");
        return;
    }
    TAG_LOGD(AceLogTag::ACE_REPEAT, "JSRepeatVirtualScroll2::IsChildOnMainTree");
    auto repeatElmtId = info[0]->ToNumber<int32_t>();
    auto rid = info[1]->ToNumber<uint32_t>();
    auto result = RepeatVirtualScroll2Model::GetInstance()->IsChildOnMainTree(repeatElmtId, rid);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

void JSRepeatVirtualScroll2::JSBind(BindingTarget globalObj)
{
    JSClass<JSRepeatVirtualScroll2>::Declare("RepeatVirtualScroll2Native");
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("create", &JSRepeatVirtualScroll2::Create);

    JSClass<JSRepeatVirtualScroll2>::StaticMethod("removeNode", &JSRepeatVirtualScroll2::RemoveNode);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("removeNodes", &JSRepeatVirtualScroll2::RemoveNodes);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("setInvalid", &JSRepeatVirtualScroll2::SetInvalid);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod(
        "requestContainerReLayout", &JSRepeatVirtualScroll2::RequestContainerReLayout);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod(
        "notifyContainerLayoutChange", &JSRepeatVirtualScroll2::NotifyContainerLayoutChange);

    JSClass<JSRepeatVirtualScroll2>::StaticMethod("updateL1Rid4Index", &JSRepeatVirtualScroll2::UpdateL1Rid4Index);

    JSClass<JSRepeatVirtualScroll2>::StaticMethod("onMove", &JSRepeatVirtualScroll2::OnMove);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("setCreateByTemplate", &JSRepeatVirtualScroll2::SetCreateByTemplate);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("isAllowAnimation", &JSRepeatVirtualScroll2::IsAllowAnimation);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod(
        "isImplicitAnimationOpen", &JSRepeatVirtualScroll2::IsImplicitAnimationOpen);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("isChildInAnimation", &JSRepeatVirtualScroll2::IsChildInAnimation);
    JSClass<JSRepeatVirtualScroll2>::StaticMethod("isChildOnMainTree", &JSRepeatVirtualScroll2::IsChildOnMainTree);
    JSClass<JSRepeatVirtualScroll2>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
