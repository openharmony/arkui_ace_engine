/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * limitations under the License.
 */

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_COLOR_METRICS_LINEAR_GRADIENT_BINDING_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_COLOR_METRICS_LINEAR_GRADIENT_BINDING_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/jsview/js_color_metrics_linear_gradient.h"

namespace OHOS::Ace::Framework {
class JSColorMetricsLinearGradientBinding {
public:
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSColorMetricsLinearGradient* jsLinearGradientPtr);
    static bool ParseColorMetricsStop(const JSRef<JSObject>& itemObject, ColorMetricsStop& stop);

private:
    ACE_DISALLOW_COPY_AND_MOVE(JSColorMetricsLinearGradientBinding);
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_COLOR_METRICS_LINEAR_GRADIENT_BINDING_H