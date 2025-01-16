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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_H

#include "bridge/declarative_frontend/jsview/js_scrollable_base.h"

namespace OHOS::Ace::Framework {
class JSWaterFlow : public JSScrollableBase {
public:
    static void Create(const JSCallbackInfo& args);
    static void JSBind(BindingTarget globalObj);
    static void UpdateWaterFlowSectionsByFrameNode(
        NG::FrameNode* frameNode, const JSCallbackInfo& args, const JSRef<JSVal>& sections);
    static void UpdateWaterFlowFooter(NG::FrameNode* frameNode, const JSRef<JSVal>& args);

protected:
    static void SetColumnsGap(const JSCallbackInfo& info);
    static void SetRowsGap(const JSCallbackInfo& info);
    static void SetLayoutDirection(const JSCallbackInfo& info);
    static void SetColumnsTemplate(const std::string& value);
    static void SetItemConstraintSize(const JSCallbackInfo& info);
    static void SetRowsTemplate(const std::string& value);
    static void SetNestedScroll(const JSCallbackInfo& args);
    static void SetScrollEnabled(const JSCallbackInfo& args);
    static void ReachStartCallback(const JSCallbackInfo& args);
    static void ReachEndCallback(const JSCallbackInfo& args);
    static void ScrollFrameBeginCallback(const JSCallbackInfo& args);
    static void SetFriction(const JSCallbackInfo& info);
    static void SetCachedCount(const JSCallbackInfo& info);
    static void SetEdgeEffect(const JSCallbackInfo& info);

    static void JsOnScroll(const JSCallbackInfo& args);
    static void JsOnScrollStart(const JSCallbackInfo& args);
    static void JsOnScrollStop(const JSCallbackInfo& args);
    static void JsOnScrollIndex(const JSCallbackInfo& args);

    static void SetScrollBar(const JSCallbackInfo& info);
    static void SetScrollBarColor(const JSCallbackInfo& info);
    static void SetScrollBarWidth(const JSCallbackInfo& scrollWidth);
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_WATER_FLOW_H
