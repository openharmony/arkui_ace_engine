/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * limitations under the License.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PATTERN_LOCK_CONTROLLER_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PATTERN_LOCK_CONTROLLER_BINDING_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_pattern_lock.h"

namespace OHOS::Ace::Framework {
class JSPatternLockControllerBinding : public JSPatternLockController {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSPatternLockController* scroller);
    void SetChallengeResult(const JSCallbackInfo& args);
    void Reset(const JSCallbackInfo& args);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSPatternLockControllerBinding);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_PATTERN_LOCK_CONTROLLER_BINDING_H