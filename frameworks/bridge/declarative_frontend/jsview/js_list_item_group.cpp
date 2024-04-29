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
    JSRef<JSObject> childrenSizeObj = JSRef<JSObject>::Cast(args[0]);
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
    V2::ListItemGroupStyle listItemGroupStyle = V2::ListItemGroupStyle::NONE;
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        auto styleObject = obj->GetProperty("style");
        listItemGroupStyle = styleObject->IsNumber()
                                 ? static_cast<V2::ListItemGroupStyle>(styleObject->ToNumber<int32_t>())
                                 : V2::ListItemGroupStyle::NONE;
    }
    ListItemGroupModel::GetInstance()->Create(listItemGroupStyle);
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

        Dimension space;
        if (ConvertFromJSValue(obj->GetProperty("space"), space) && space.IsNonNegative()) {
            ListItemGroupModel::GetInstance()->SetSpace(space);
        }

        auto headerObject = obj->GetProperty("header");
        if (headerObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(headerObject));
            auto headerAction = [builderFunc]() { builderFunc->Execute(); };
            ListItemGroupModel::GetInstance()->SetHeader(headerAction);
        }

        auto footerObject = obj->GetProperty("footer");
        if (footerObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(footerObject));
            auto footerAction = [builderFunc]() { builderFunc->Execute(); };
            ListItemGroupModel::GetInstance()->SetFooter(footerAction);
        }
    }
    args.ReturnSelf();
}

void JSListItemGroup::SetDivider(const JSCallbackInfo& args)
{
    V2::ItemDivider divider;
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        if (!ConvertFromJSValue(obj->GetProperty("strokeWidth"), divider.strokeWidth)) {
            LOGW("Invalid strokeWidth of divider");
            divider.strokeWidth.Reset();
        }
        if (!ConvertFromJSValue(obj->GetProperty("color"), divider.color)) {
            // Failed to get color from param, using default color defined in theme
            RefPtr<ListTheme> listTheme = GetTheme<ListTheme>();
            if (listTheme) {
                divider.color = listTheme->GetDividerColor();
            }
        }
        ConvertFromJSValue(obj->GetProperty("startMargin"), divider.startMargin);
        ConvertFromJSValue(obj->GetProperty("endMargin"), divider.endMargin);
    }
    ListItemGroupModel::GetInstance()->SetDivider(divider);
    args.ReturnSelf();
}

void JSListItemGroup::SetAspectRatio(const JSCallbackInfo& args)
{
}

void JSListItemGroup::JSBind(BindingTarget globalObj)
{
    JSClass<JSListItemGroup>::Declare("ListItemGroup");
    JSClass<JSListItemGroup>::StaticMethod("create", &JSListItemGroup::Create);

    JSClass<JSListItemGroup>::StaticMethod("aspectRatio", &JSListItemGroup::SetAspectRatio);
    JSClass<JSListItemGroup>::StaticMethod("childrenMainSize", &JSListItemGroup::SetChildrenMainSize);
    JSClass<JSListItemGroup>::StaticMethod("divider", &JSListItemGroup::SetDivider);
    JSClass<JSListItemGroup>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSListItemGroup>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSListItemGroup>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);

    JSClass<JSListItemGroup>::Inherit<JSInteractableView>();
    JSClass<JSListItemGroup>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
