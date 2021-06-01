/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_ANIMATION_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_ANIMATION_H

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSAnimation {

public:
    JSAnimation()
    {
        LOGD("Constructor: JSAnimation");
        duration_ = 500;
        delay_ = 0;
        animationCurve_ = "linear";
        noAnimation_ = false;
    }

    ~JSAnimation()
    {
        LOGD("Destroy: JSAnimation");
    }

    // Getters.
    int GetDuration() const
    {
        return duration_;
    }

    int GetDelay() const
    {
        return delay_;
    }

    std::string GetAnimationCurve() const
    {
        return animationCurve_;
    }

    bool GetNone() const
    {
        return noAnimation_;
    }

public:
#ifdef USE_QUICKJS_ENGINE
    void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc);
    void ReleaseRT(JSRuntime* rt);

    static void QjsDestructor(JSRuntime* rt, JSAnimation* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif

    static void JSBind(BindingTarget globalObj);

protected:
    void SetDuration(int duration);
    void SetDelay(int delay);
    void SetAnimationCurve(const std::string& animationCurve);

    // Animation timing functions.
    void SetLinearCurve();
    void SetEaseCurve();
    void SetEaseInCurve();
    void SetEaseOutCurve();
    void SetEaseInOutCurve();
    void SetDecelerationCurve();
    void SetFastOutLinearInCurve();
    void SetFastOutSlowInCurve();
    void SetLinearOutSlowInCurve();
    void SetFrictionCurve();
    void SetRhythmCurve();
    void SetSharpCurve();
    void SetSmoothCurve();
    void SetNone();

private:
    int duration_;
    int delay_;
    std::string animationCurve_;
    bool noAnimation_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_ANIMATION_H
