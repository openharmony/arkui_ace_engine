/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_H

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_scrollable_base.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"

namespace OHOS::Ace::Framework {

class JSListScroller : public JSScroller {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSListScroller* scroller);

    void GetItemRectInGroup(const JSCallbackInfo& args);
    void GetVisibleListContentInfo(const JSCallbackInfo& args);
    void CloseAllSwipeActions(const JSCallbackInfo& args);
    void ScrollToItemInGroup(const JSCallbackInfo& args);
};

class JSList : public JSScrollableBase {
public:
    static void JSBind(BindingTarget globalObj);
    static void SetScroller(RefPtr<JSScroller> scroller);
    static void Create(const JSCallbackInfo& args);

    static void JsWidth(const JSCallbackInfo& info);
    static void JsHeight(const JSCallbackInfo& info);
    static void ScrollCallback(const JSCallbackInfo& args);
    static void ReachStartCallback(const JSCallbackInfo& args);
    static void ReachEndCallback(const JSCallbackInfo& args);
    static void ScrollStartCallback(const JSCallbackInfo& args);
    static void ScrollStopCallback(const JSCallbackInfo& args);
    static void ItemDeleteCallback(const JSCallbackInfo& args);
    static void ItemMoveCallback(const JSCallbackInfo& args);
    static void ScrollIndexCallback(const JSCallbackInfo& args);
    static void ScrollVisibleContentChangeCallback(const JSCallbackInfo& args);
    static void ScrollBeginCallback(const JSCallbackInfo& args);
    static void ScrollFrameBeginCallback(const JSCallbackInfo& args);

    static void SetDivider(const JSCallbackInfo& args);
    static void SetDirection(int32_t direction);
    static void SetScrollBar(const JSCallbackInfo& info);
    static void SetScrollBarColor(const JSCallbackInfo& info);
    static void SetScrollBarWidth(const JSCallbackInfo& scrollWidth);
    static void SetEdgeEffect(const JSCallbackInfo& info);
    static void SetEditMode(bool editMode);
    static void SetCachedCount(const JSCallbackInfo& info);
    static void SetChainAnimation(const JSCallbackInfo& args);
    static void SetChainAnimationOptions(const JSCallbackInfo& info);
    static void SetChildrenMainSize(const JSCallbackInfo& args);
    static void SetChildrenMainSize(const JSRef<JSObject>& childrenSizeObj);
    static void SetMultiSelectable(bool multiSelectable);
    static void SetListItemAlign(int32_t itemAlignment);
    static void SetLanes(const JSCallbackInfo& info);
    static void SetSticky(int32_t sticky);
    static void SetContentStartOffset(const JSCallbackInfo& info);
    static void SetContentEndOffset(const JSCallbackInfo& info);
    static void SetNestedScroll(const JSCallbackInfo& args);
    static void SetScrollEnabled(const JSCallbackInfo& args);
    static void SetScrollSnapAlign(int32_t scrollSnapAlign);
    static void SetFriction(const JSCallbackInfo& info);
    static void MaintainVisibleContentPosition(const JSCallbackInfo& args);

    static void ItemDragStartCallback(const JSCallbackInfo& info);
    static void ItemDragEnterCallback(const JSCallbackInfo& info);
    static void ItemDragMoveCallback(const JSCallbackInfo& info);
    static void ItemDragLeaveCallback(const JSCallbackInfo& info);
    static void ItemDropCallback(const JSCallbackInfo& info);
    static void SetListItemIndex(JSRef<JSObject> listItemInfo, ListItemIndex indexInfo);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_LIST_H
