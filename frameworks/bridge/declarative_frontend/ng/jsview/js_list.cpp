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

#include "bridge/declarative_frontend/jsview/js_list.h"

#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/pattern/list/list_view.h"

namespace OHOS::Ace::Framework {

void JSList::SetDirection(int32_t direction)
{
    NG::ListView::SetListDirection(static_cast<Axis>(direction));
}

void JSList::SetScrollBar(int32_t scrollBar) {}

void JSList::SetEdgeEffect(int32_t edgeEffect)
{
    NG::ListView::SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
}

void JSList::SetEditMode(bool editMode) {}

void JSList::SetCachedCount(int32_t cachedCount) {}

void JSList::Create(const JSCallbackInfo& args)
{
    NG::ListView::Create();
}

void JSList::SetChainAnimation(bool enableChainAnimation) {}

void JSList::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
}

void JSList::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
}

void JSList::SetSticky(int32_t sticky) {}

void JSList::SetListItemAlign(int32_t itemAlignment) {}

void JSList::SetLanes(const JSCallbackInfo& info) {}

void JSList::SetDivider(const JSCallbackInfo& args) {}

void JSList::ScrollCallback(const JSCallbackInfo& args) {}

void JSList::ReachStartCallback(const JSCallbackInfo& args) {}

void JSList::ReachEndCallback(const JSCallbackInfo& args) {}

void JSList::ScrollStopCallback(const JSCallbackInfo& args) {}

void JSList::ItemDeleteCallback(const JSCallbackInfo& args) {}

void JSList::ItemMoveCallback(const JSCallbackInfo& args) {}

void JSList::ScrollIndexCallback(const JSCallbackInfo& args) {}

void JSList::ItemDragStartCallback(const JSCallbackInfo& info) {}

void JSList::ItemDragEnterCallback(const JSCallbackInfo& info) {}

void JSList::ItemDragMoveCallback(const JSCallbackInfo& info) {}

void JSList::ItemDragLeaveCallback(const JSCallbackInfo& info) {}

void JSList::ItemDropCallback(const JSCallbackInfo& info) {}

void JSList::SetMultiSelectable(bool multiSelectable) {}

void JSList::ScrollBeginCallback(const JSCallbackInfo& args) {}

} // namespace OHOS::Ace::Framework
