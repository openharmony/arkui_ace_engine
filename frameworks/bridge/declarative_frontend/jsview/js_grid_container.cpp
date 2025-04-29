/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid_container.h"

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/models/grid_container_model_impl.h"
#include "frameworks/core/components/common/layout/grid_system_manager.h"
#include "frameworks/core/components_ng/base/view_stack_model.h"
#include "frameworks/core/components_ng/pattern/grid_container/grid_container_model_ng.h"

namespace OHOS::Ace {
GridContainerModel* GridContainerModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::GridContainerModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::GridContainerModelNG instance;
        return &instance;
    } else {
        static Framework::GridContainerModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSGridContainer::Create(const JSCallbackInfo& info)
{
    GridContainerInfo::Builder gridContainerInfoBuilder;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);

        // columns?: number | 'auto'
        JSRef<JSVal> columns = obj->GetProperty("columns");
        if (columns->IsNumber()) {
            gridContainerInfoBuilder.SetColumns(columns->ToNumber<int32_t>());
        }

        // sizeType?: SizeType
        JSRef<JSVal> sizeType = obj->GetProperty("sizeType");
        if (sizeType->IsNumber()) {
            auto value = sizeType->ToNumber<int32_t>();
            gridContainerInfoBuilder.SetSizeType(static_cast<GridSizeType>(value));
        }

        CalcDimension dim;
        // gutter?: Length
        if (ParseJsDimensionVp(obj->GetProperty("gutter"), dim)) {
            gridContainerInfoBuilder.SetGutterWidth(dim);
        }

        // margin?: Length
        if (ParseJsDimensionVp(obj->GetProperty("margin"), dim)) {
            gridContainerInfoBuilder.SetMarginLeft(dim);
            gridContainerInfoBuilder.SetMarginRight(dim);
        }
    }
    auto gridContainerInfo = gridContainerInfoBuilder.Build();
    GridContainerModel::GetInstance()->Create(gridContainerInfo);
}

void JSGridContainer::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSGridContainer][pop]", &JSGridContainer::Pop);
    }
    GridContainerModel::GetInstance()->Pop();
    JSColumn::Pop();
}

void JSGridContainer::JSBind(BindingTarget globalObj)
{
    JSClass<JSGridContainer>::Declare("GridContainer");
    JSClass<JSGridContainer>::StaticMethod("create", &JSGridContainer::Create, MethodOptions::NONE);
    JSClass<JSGridContainer>::StaticMethod("pop", &JSGridContainer::Pop, MethodOptions::NONE);
    JSClass<JSGridContainer>::InheritAndBind<JSColumn>(globalObj);
}

} // namespace OHOS::Ace::Framework
