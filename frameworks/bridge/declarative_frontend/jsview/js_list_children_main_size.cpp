/*
Copyright (c) 2025 Huawei Device Co., Ltd.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "bridge/declarative_frontend/jsview/js_list_children_main_size.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

namespace {
bool ParseChange(
    const JSRef<JSObject>& changeObject, int32_t& start, int32_t& deleteCount, std::vector<float>& newChildrenSize)
{
    if (!JSViewAbstract::ParseJsInteger<int32_t>(changeObject->GetProperty("start"), start) || start < 0) {
        return false;
    }
    if (!(changeObject->HasProperty("deleteCount"))) {
        // If only input one parameter, set -1 to deleteCount for deleting elements after index 'start' in the array.
        deleteCount = -1;
    } else if (!JSViewAbstract::ParseJsInteger<int32_t>(changeObject->GetProperty("deleteCount"), deleteCount) ||
               deleteCount < 0) {
        deleteCount = 0;
    }
    auto childrenSizeValue = changeObject->GetProperty("childrenSize");
    if (childrenSizeValue->IsArray()) {
        auto childrenSize = JSRef<JSArray>::Cast(childrenSizeValue);
        auto childrenSizeCount = childrenSize->Length();
        for (size_t j = 0; j < childrenSizeCount; ++j) {
            // -1.0: represent default size.
            double childSize = -1.0;
            if (!JSViewAbstract::ParseJsDouble(childrenSize->GetValueAt(j), childSize) || Negative(childSize)) {
                // -1.0f: represent default size.
                newChildrenSize.emplace_back(-1.0f);
            } else {
                newChildrenSize.emplace_back(Dimension(childSize, DimensionUnit::VP).ConvertToPx());
            }
        }
    }
    return true;
}
} // namespace

void JSListChildrenMainSize::JSBind(BindingTarget globalObj)
{
    JSClass<JSListChildrenMainSize>::Declare("NativeChildrenMainSize");
    JSClass<JSListChildrenMainSize>::CustomMethod("onStateChanged", &JSListChildrenMainSize::OnStateChanged);
    JSClass<JSListChildrenMainSize>::CustomMethod("onDefaultSizeUpdate", &JSListChildrenMainSize::OnDefaultSizeUpdate);
    JSClass<JSListChildrenMainSize>::Bind(
        globalObj, &JSListChildrenMainSize::Constructor, &JSListChildrenMainSize::Destructor);
}

void JSListChildrenMainSize::Constructor(const JSCallbackInfo& info)
{
    auto stack = Referenced::MakeRefPtr<JSListChildrenMainSize>();
    stack->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(stack));
}

void JSListChildrenMainSize::Destructor(JSListChildrenMainSize* mainSize)
{
    if (mainSize != nullptr) {
        mainSize->DecRefCount();
    }
}

void JSListChildrenMainSize::SetNativeChildrenMainSize(JSRef<JSObject> jsStack, JSRef<JSObject> nativeChildrenSize)
{
    if (jsStack->IsEmpty() || nativeChildrenSize->IsEmpty()) {
        return;
    }

    auto property = jsStack->GetProperty("setNativeMainSize");
    if (!property->IsFunction()) {
        return;
    }

    auto setNativeStackFunc = JSRef<JSFunc>::Cast(property);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Cast(nativeChildrenSize);
    setNativeStackFunc->Call(jsStack, 1, params);
}

void JSListChildrenMainSize::OnStateChanged(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        LOGE("The arg must be object");
        return;
    }

    auto changeObject = JSRef<JSObject>::Cast(info[0]);

    int32_t start = 0;
    int32_t deleteCount = 0;
    std::vector<float> newChildrenSize;
    if (ParseChange(changeObject, start, deleteCount, newChildrenSize) && onStateChangedCallback_) {
        onStateChangedCallback_(start, deleteCount, std::move(newChildrenSize));
    }
}

void JSListChildrenMainSize::OnDefaultSizeUpdate(const JSCallbackInfo& info)
{
    double defaultSize = 0.0f;
    if (!JSViewAbstract::ParseJsDouble(info[0], defaultSize) || !NonNegative(defaultSize)) {
        TAG_LOGW(AceLogTag::ACE_LIST, "JSList input parameter defaultSize check failed.");
        return;
    }
    onDefaultSizeUpdate_(defaultSize);
}
} // namespace OHOS::Ace::Framework