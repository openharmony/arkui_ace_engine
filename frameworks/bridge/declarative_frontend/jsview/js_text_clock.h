/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_CLOCK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_CLOCK_H

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/text_clock/text_clock_controller.h"

namespace OHOS::Ace::Framework {
class JSTextClock : public JSViewAbstract, public JSInteractableView {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);
    static void SetFormat(const JSCallbackInfo& info);
    static void JsOnDateChange(const JSCallbackInfo& info);
    static void SetTextColor(const JSCallbackInfo& info);
    static void SetFontSize(const JSCallbackInfo& info);
    static void SetFontWeight(const JSCallbackInfo& info);
    static void SetFontStyle(int32_t value);
    static void SetFontFamily(const JSCallbackInfo& info);
    static void SetTextShadow(const JSCallbackInfo& info);
    static void SetFontFeature(const JSCallbackInfo& info);
    static void SetDateTimeOptions(const JSCallbackInfo& info);
};

class JSTextClockController final : public Referenced {
public:
    JSTextClockController() = default;
    ~JSTextClockController() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSTextClockController* scroller);
    void Start();
    void Stop();
    void AddController(const RefPtr<TextClockController>& controller)
    {
        controller_.emplace_back(controller);
    }

    void removeController(const RefPtr<TextClockController>& controller);

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    std::vector<RefPtr<TextClockController>> controller_;
    ACE_DISALLOW_COPY_AND_MOVE(JSTextClockController);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_CLOCK_H