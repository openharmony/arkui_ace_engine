/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CANVAS_PATTERN_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CANVAS_PATTERN_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_renderer.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/properties/paint_state.h"

namespace OHOS::Ace::Framework {
class JSCanvasPattern : public Referenced {
public:
    JSCanvasPattern() = default;
    ~JSCanvasPattern() override = default;

    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& info);
    static void Destructor(JSCanvasPattern* canvasPattern);

    void JSSetTransform(const JSCallbackInfo& info);

    TransformParam GetTransform() const;
    void SetTransform(const TransformParam& transform);

    std::shared_ptr<Pattern> GetPattern() const
    {
        return pattern_;
    }

    void SetPattern(const std::shared_ptr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    ACE_DISALLOW_COPY_AND_MOVE(JSCanvasPattern);

private:
    TransformParam transform_;
    std::shared_ptr<Pattern> pattern_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_CANVAS_PATTERN_H

