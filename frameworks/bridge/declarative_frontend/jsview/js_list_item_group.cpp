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

#include "bridge/declarative_frontend/jsview/js_list_item_group.h"

#include "bridge/declarative_frontend/jsview/js_list_item.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/list_item_group_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/list/list_item_group_component.h"
#include "core/components_ng/pattern/list/list_item_group_model.h"
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ListItemGroupModel> ListItemGroupModel::instance_ = nullptr;
std::mutex ListItemGroupModel::mutex_;

ListItemGroupModel* ListItemGroupModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ListItemGroupModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ListItemGroupModelNG());
            } else {
                instance_.reset(new Framework::ListItemGroupModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {

namespace {
bool ParseChange(const JSRef<JSObject>& changeObject, const float defaultSize, int32_t& start,
    int32_t& deleteCount, std::vector<float>& newChildrenSize)
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

void SyncChildrenSize(const JSRef<JSObject>& childrenSizeObj, RefPtr<NG::ListChildrenMainSize> childrenSize)
{
    auto sizeArray = childrenSizeObj->GetProperty("sizeArray");
    if (!sizeArray->IsArray()) {
        return;
    }
    childrenSize->ResizeChildrenSize(0);
    auto childrenSizeJSArray = JSRef<JSArray>::Cast(sizeArray);
    auto length = childrenSizeJSArray->Length();
    for (size_t i = 0; i < length; ++i) {
        // -1.0: represent default size.
        double childSize = -1.0;
        if (!JSViewAbstract::ParseJsDouble(childrenSizeJSArray->GetValueAt(i), childSize) || Negative(childSize)) {
            // -1.0f: represent default size.
            childrenSize->SyncChildrenSize(-1.0f);
        } else {
            childrenSize->SyncChildrenSize(Dimension(childSize, DimensionUnit::VP).ConvertToPx());
        }
    }
    childrenSize->SyncChildrenSizeOver();
}
} // namespace

void JSListItemGroup::SetChildrenMainSize(const JSCallbackInfo& args)
{
    if (args.Length() != 1 || !(args[0]->IsObject())) {
        return;
    }
    SetChildrenMainSize(JSRef<JSObject>::Cast(args[0]));
}

void JSListItemGroup::SetChildrenMainSize(const JSRef<JSObject>& childrenSizeObj)
{
    double defaultSize = 0.0f;
    if (!ParseJsDouble(childrenSizeObj->GetProperty("defaultMainSize"), defaultSize) || !NonNegative(defaultSize)) {
        LOGW("JSListItemGroup input parameter defaultSize check failed.");
        return;
    }
    auto listChildrenMainSize = ListItemGroupModel::GetInstance()->GetOrCreateListChildrenMainSize();
    CHECK_NULL_VOID(listChildrenMainSize);
    listChildrenMainSize->UpdateDefaultSize(Dimension(defaultSize, DimensionUnit::VP).ConvertToPx());

    if (listChildrenMainSize->NeedSync()) {
        SyncChildrenSize(childrenSizeObj, listChildrenMainSize);
    } else {
        auto changes = childrenSizeObj->GetProperty("changeArray");
        if (!changes->IsArray()) {
            return;
        }
        auto changeArray = JSRef<JSArray>::Cast(changes);
        auto length = changeArray->Length();
        for (size_t i = 0; i < length; ++i) {
            auto change = changeArray->GetValueAt(i);
            if (!change->IsObject()) {
                continue;
            }
            auto changeObject = JSRef<JSObject>::Cast(change);
            int32_t start = 0;
            int32_t deleteCount = 0;
            std::vector<float> newChildrenSize;
            if (!ParseChange(changeObject, defaultSize, start, deleteCount, newChildrenSize)) {
                SyncChildrenSize(childrenSizeObj, listChildrenMainSize);
                break;
            }
            listChildrenMainSize->ChangeData(start, deleteCount, newChildrenSize);
        }
    }
    auto clearFunc = childrenSizeObj->GetProperty("clearChanges");
    if (!clearFunc->IsFunction()) {
        return;
    }
    auto func = JSRef<JSFunc>::Cast(clearFunc);
    JSRef<JSVal>::Cast(func->Call(childrenSizeObj));
}

void JSListItemGroup::Create(const JSCallbackInfo& args)
{
    auto listItemGroupStyle = GetListItemGroupStyle(args);
    ListItemGroupModel::GetInstance()->Create(listItemGroupStyle);
    if (args.Length() < 1 || !args[0]->IsObject()) {
        NG::ListItemGroupModelNG::GetInstance()->RemoveHeader();
        NG::ListItemGroupModelNG::GetInstance()->RemoveFooter();
        args.ReturnSelf();
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

    Dimension space;
    if (ConvertFromJSValue(obj->GetProperty("space"), space) && space.IsNonNegative()) {
        ListItemGroupModel::GetInstance()->SetSpace(space);
    }

    if (obj->HasProperty("headerComponent")) {
        auto headerComponentObject = obj->GetProperty("headerComponent");
        if (!ParseHeaderAndFooterContent(headerComponentObject, true)) {
            NG::ListItemGroupModelNG::GetInstance()->RemoveHeader();
        }
    } else {
        if (!SetHeaderBuilder(args.GetVm(), obj)) {
            NG::ListItemGroupModelNG::GetInstance()->RemoveHeader();
        }
    }

    if (obj->HasProperty("footerComponent")) {
        auto footerComponentObject = obj->GetProperty("footerComponent");
        if (!ParseHeaderAndFooterContent(footerComponentObject, false)) {
            NG::ListItemGroupModelNG::GetInstance()->RemoveFooter();
        }
    } else {
        if (!SetFooterBuilder(args.GetVm(), obj)) {
            NG::ListItemGroupModelNG::GetInstance()->RemoveFooter();
        }
    }

    args.ReturnSelf();
}

void JSListItemGroup::SetDivider(const JSCallbackInfo& args)
{
    V2::ItemDivider divider;
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        RefPtr<ResourceObject> resObjStrokeWidth;
        RefPtr<ResourceObject> resObjColor;
        RefPtr<ResourceObject> resObjStartMargin;
        RefPtr<ResourceObject> resObjEndMargin;

        if (!ConvertFromJSValue(obj->GetProperty("strokeWidth"), divider.strokeWidth, resObjStrokeWidth)) {
            LOGW("Invalid strokeWidth of divider");
            divider.strokeWidth.Reset();
        }

        bool setByUser = false;
        if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color, resObjColor)) {
            // Failed to get color from param, using default color defined in theme
            RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
            if (listTheme) {
                divider.color = listTheme->GetDividerColor();
                setByUser = false;
            }
        } else {
            setByUser = true;
        }
        NG::ListItemGroupModelNG::GetInstance()->SetDividerColorByUser(setByUser);

        ConvertFromJSValue(obj->GetProperty("startMargin"), divider.startMargin, resObjStartMargin);

        ConvertFromJSValue(obj->GetProperty("endMargin"), divider.endMargin, resObjEndMargin);

        if (SystemProperties::ConfigChangePerform()) {
            NG::ListItemGroupModelNG::GetInstance()->ParseResObjDividerStrokeWidth(resObjStrokeWidth);
            NG::ListItemGroupModelNG::GetInstance()->ParseResObjDividerColor(resObjColor);
            NG::ListItemGroupModelNG::GetInstance()->ParseResObjDividerStartMargin(resObjStartMargin);
            NG::ListItemGroupModelNG::GetInstance()->ParseResObjDividerEndMargin(resObjEndMargin);
        }
    }
    ListItemGroupModel::GetInstance()->SetDivider(divider);
    args.ReturnSelf();
}

void JSListItemGroup::SetAspectRatio(const JSCallbackInfo& args) {}

bool JSListItemGroup::ParseHeaderAndFooterContent(const JSRef<JSVal>& contentParam, bool isHeader)
{
    if (!contentParam->IsObject()) {
        return false;
    }
    JSRef<JSObject> contentObject = JSRef<JSObject>::Cast(contentParam);
    JSRef<JSVal> builderNodeParam = contentObject->GetProperty("builderNode_");
    if (!builderNodeParam->IsObject()) {
        return false;
    }
    JSRef<JSObject> builderNodeObject = JSRef<JSObject>::Cast(builderNodeParam);
    JSRef<JSVal> nodeptr = builderNodeObject->GetProperty("nodePtr_");
    if (nodeptr.IsEmpty()) {
        return false;
    }
    const auto* vm = nodeptr->GetEcmaVM();
    CHECK_NULL_RETURN(nodeptr->GetLocalHandle()->IsNativePointer(vm), false);
    auto* node = nodeptr->GetLocalHandle()->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    RefPtr<NG::FrameNode> refPtrFrameNode = AceType::Claim(frameNode);
    if (isHeader) {
        NG::ListItemGroupModelNG::GetInstance()->SetHeaderComponent(refPtrFrameNode);
    } else {
        NG::ListItemGroupModelNG::GetInstance()->SetFooterComponent(refPtrFrameNode);
    }
    return true;
}

bool JSListItemGroup::SetHeaderBuilder(const panda::ecmascript::EcmaVM* vm, const JSRef<JSObject>& obj)
{
    auto headerObject = obj->GetProperty("header");
    if (headerObject->IsFunction()) {
        auto jsFunc = JSRef<JSFunc>::Cast(headerObject);
        auto func = jsFunc->GetLocalHandle();
        auto headerAction = [vm, func = panda::CopyableGlobal(vm, func)]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            func->Call(vm, func.ToLocal(), nullptr, 0);
        };
        ListItemGroupModel::GetInstance()->SetHeader(headerAction);
        return true;
    }
    return false;
}

bool JSListItemGroup::SetFooterBuilder(const panda::ecmascript::EcmaVM* vm, const JSRef<JSObject>& obj)
{
    auto footerObject = obj->GetProperty("footer");
    if (footerObject->IsFunction()) {
        auto jsFunc = JSRef<JSFunc>::Cast(footerObject);
        auto func = jsFunc->GetLocalHandle();
        auto footerAction = [vm, func = panda::CopyableGlobal(vm, func)]() {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            func->Call(vm, func.ToLocal(), nullptr, 0);
        };
        ListItemGroupModel::GetInstance()->SetFooter(footerAction);
        return true;
    }
    return false;
}

V2::ListItemGroupStyle JSListItemGroup::GetListItemGroupStyle(const JSCallbackInfo& args)
{
    V2::ListItemGroupStyle listItemGroupStyle = V2::ListItemGroupStyle::NONE;
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        auto styleObject = obj->GetProperty("style");
        listItemGroupStyle = styleObject->IsNumber()
                                 ? static_cast<V2::ListItemGroupStyle>(styleObject->ToNumber<int32_t>())
                                 : V2::ListItemGroupStyle::NONE;
    }
    return listItemGroupStyle;
}

void JSListItemGroup::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItemGroup>::Declare("ListItemGroup");
    JSClass<JSListItemGroup>::StaticMethod("create", &JSListItemGroup::Create);

    JSClass<JSListItemGroup>::StaticMethod("aspectRatio", &JSListItemGroup::SetAspectRatio);
    JSClass<JSListItemGroup>::StaticMethod("childrenMainSize", &JSListItemGroup::SetChildrenMainSize);
    JSClass<JSListItemGroup>::StaticMethod("divider", &JSListItemGroup::SetDivider);
    JSClass<JSListItemGroup>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSListItemGroup>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSListItemGroup>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSListItemGroup>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSListItemGroup>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);

    JSClass<JSListItemGroup>::Inherit<JSInteractableView>();
    JSClass<JSListItemGroup>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
