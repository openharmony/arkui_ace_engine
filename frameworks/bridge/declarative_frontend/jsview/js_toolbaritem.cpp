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

#include "frameworks/bridge/declarative_frontend/jsview/js_toolbaritem.h"

#include "core/components_ng/pattern/toolbaritem/toolbaritem_model.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ToolBarItemModel> ToolBarItemModel::instance_ = nullptr;
std::mutex ToolBarItemModel::mutex_;

ToolBarItemModel* ToolBarItemModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ToolBarItemModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ToolBarItemModelNG());
            } else {
                instance_.reset(new NG::ToolBarItemModelNG());
            }

#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {} // namespace

void JSToolBarItem::Create(const JSCallbackInfo& info)
{
    JSRef<JSObject> toolbaritemObj = JSRef<JSObject>::Cast(info[0]);
    int32_t value = static_cast<int32_t>(ToolBarItemPlacement::TOP_BAR_LEADING);
    if (toolbaritemObj->GetProperty(JSToolBarItem::PLACEMENT)->IsNumber()) {
        value = static_cast<int32_t>(toolbaritemObj->GetProperty(JSToolBarItem::PLACEMENT)->ToNumber<int32_t>());
    }
    if ((ToolBarItemPlacement)value == ToolBarItemPlacement::TOP_BAR_LEADING ||
        (ToolBarItemPlacement)value == ToolBarItemPlacement::TOP_BAR_TRAILING) {
        ToolBarItemModel::GetInstance()->Create(value);
    }
}

void JSToolBarItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSToolBarItem>::Declare("ToolBarItem");
    JSClass<JSToolBarItem>::StaticMethod("create", &JSToolBarItem::Create);
    JSClass<JSToolBarItem>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework