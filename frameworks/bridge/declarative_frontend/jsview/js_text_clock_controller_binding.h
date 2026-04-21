/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * limitations under the License.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_CLOCK_CONTROLLER_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_CLOCK_CONTROLLER_BINDING_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_text_clock.h"

namespace OHOS::Ace::Framework {
class JSTextClockControllerBinding {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSTextClockController* scroller);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSTextClockControllerBinding);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_CLOCK_CONTROLLER_BINDING_H