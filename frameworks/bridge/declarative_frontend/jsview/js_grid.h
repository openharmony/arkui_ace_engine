/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_H

#include "bridge/declarative_frontend/jsview/js_scrollable_base.h"
#include "frameworks/core/components/grid_layout/grid_layout_component.h"
#include "core/components_ng/pattern/grid/grid_model_ng.h"

namespace OHOS::Ace::Framework {

class JSGrid : public JSScrollableBase {
public:
    static void Create(const JSCallbackInfo& info);
    static void JSBind(BindingTarget globalObj);

    static void PopGrid();
    static void UseProxy(const JSCallbackInfo& args);
    static void SetColumnsTemplate(const std::string& value);
    static void SetRowsTemplate(const std::string& value);
    static void SetColumnsGap(const JSCallbackInfo& info);
    static void SetRowsGap(const JSCallbackInfo& info);
    static void SetScrollBar(const JSCallbackInfo& info);
    static void SetScrollBarColor(const JSCallbackInfo& info);
    static void SetScrollBarWidth(const JSCallbackInfo& scrollWidth);

    static void JsOnScrollBarUpdate(const JSCallbackInfo& info);
    static void SetCachedCount(const JSCallbackInfo& info);
    static void SetEditMode(const JSCallbackInfo& info);
    static void SetMultiSelectable(bool multiSelectable);
    static void SetMaxCount(const JSCallbackInfo& info);
    static void SetMinCount(const JSCallbackInfo& info);
    static void CellLength(int32_t cellLength);
    static void SetLayoutDirection(int32_t value);
    static void SetDirection(const std::string& dir);
    static void SetSupportAnimation(bool supportAnimation);
    static void SetDragAnimation(bool value);
    static void SetEdgeEffect(const JSCallbackInfo& info);
    static void JsOnGridDragEnter(const JSCallbackInfo& info);
    static void JsOnGridDragMove(const JSCallbackInfo& info);
    static void JsOnGridDragLeave(const JSCallbackInfo& info);
    static void JsOnGridDragStart(const JSCallbackInfo& info);
    static void JsOnGridDrop(const JSCallbackInfo& info);
    static void JsGridHeight(const JSCallbackInfo& info);
    static void SetNestedScroll(const JSCallbackInfo& args);
    static void SetScrollEnabled(const JSCallbackInfo& args);
    static void SetFriction(const JSCallbackInfo& info);
    static void SetFocusWrapMode(const JSCallbackInfo& args);
    static void SetAlignItems(const JSCallbackInfo& info);

    static void JsOnScroll(const JSCallbackInfo& args);
    static void JsOnReachStart(const JSCallbackInfo& args);
    static void JsOnReachEnd(const JSCallbackInfo& args);
    static void JsOnScrollStart(const JSCallbackInfo& args);
    static void JsOnScrollStop(const JSCallbackInfo& args);
    static void JsOnScrollIndex(const JSCallbackInfo& args);
    static void JsOnScrollFrameBegin(const JSCallbackInfo& args);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_GRID_H
