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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_DRAG_FUNCTION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_DRAG_FUNCTION_H

#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
class JsDragFunction : public JsFunction {
    DECLARE_ACE_TYPE(JsDragFunction, JsFunction)

public:
    explicit JsDragFunction(const JSRef<JSFunc>& jsFunction) : JsFunction(JSRef<JSObject>(), jsFunction) {}
    static void JSBind(BindingTarget globalObj);

    ~JsDragFunction() override {};
    void Execute() override;
    JSRef<JSVal> Execute(const RefPtr<DragEvent>& info);
    JSRef<JSVal> ItemDragStartExecute(const ItemDragInfo& info, int32_t itemIndex);
    void ItemDragEnterExecute(const ItemDragInfo& info);
    void ItemDragMoveExecute(const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex);
    void ItemDragLeaveExecute(const ItemDragInfo& info, int32_t itemIndex);
    void ItemDropExecute(const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess);
    void PreDragExecute(const PreDragStatus preDragStatus);
    JSRef<JSVal> Execute(const RefPtr<DragEvent>& info, const std::string& extraParams);

private:
    JSRef<JSObject> CreateDragEvent(const RefPtr<DragEvent>& info);
    JSRef<JSObject> CreatePasteData(const RefPtr<PasteData>& info);
    JSRef<JSObject> CreateItemDragInfo(const ItemDragInfo& info);
};

class JsDragEvent : public Referenced {
public:
    static void JSBind(BindingTarget globalObj);
    void SetJsPasteData(const JSRef<JSObject>& jsPasteData);
    void GetJsPasteData(const JSCallbackInfo& args);
    void GetScreenX(const JSCallbackInfo& args);
    void GetScreenY(const JSCallbackInfo& args);
    void GetDisplayId(const JSCallbackInfo& args);
    void GetX(const JSCallbackInfo& args);
    void GetY(const JSCallbackInfo& args);
    void GetDragSource(const JSCallbackInfo& args);
    void IsRemote(const JSCallbackInfo& args);
    void GetDescription(const JSCallbackInfo& args);
    void SetDescription(const JSCallbackInfo& args);
    void GetVelocityX(const JSCallbackInfo& args);
    void GetVelocityY(const JSCallbackInfo& args);
    void GetModifierKeyState(const JSCallbackInfo& args);
    void ExecuteDropAnimation(const JSCallbackInfo& args);
    void GetVelocity(const JSCallbackInfo& args);
    void SetData(const JSCallbackInfo& args);
    void GetData(const JSCallbackInfo& args);
    void GetSummary(const JSCallbackInfo& args);
    void SetResult(const JSCallbackInfo& args);
    void GetResult(const JSCallbackInfo& args);
    void GetPreviewRect(const JSCallbackInfo& args);
    void SetUseCustomDropAnimation(const JSCallbackInfo& args);
    void GetUseCustomDropAnimation(const JSCallbackInfo& args);
    void SetDragInfo(const JSCallbackInfo& args);
    void GetDragInfo(const JSCallbackInfo& args);
    void SetDragBehavior(const JSCallbackInfo& args);
    void GetDragBehavior(const JSCallbackInfo& args);
    void SetDragEvent(const RefPtr<DragEvent>& dragEvent)
    {
        dragEvent_ = dragEvent;
    }

    RefPtr<DragEvent> GetDragEvent() const
    {
        return dragEvent_;
    }
    void StartDataLoading(const JSCallbackInfo& args);

private:
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JsDragEvent* dragEvent);
    JSRef<JSObject> CreateRectangle(const Rect& info);

    RefPtr<DragEvent> dragEvent_;
    JSRef<JSObject> jsPasteData_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_FUNCTION_JS_DRAG_FUNCTION_H
