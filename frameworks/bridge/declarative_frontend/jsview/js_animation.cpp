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

#include "frameworks/bridge/declarative_frontend/jsview/js_animation.h"

namespace OHOS::Ace::Framework {

void JSAnimation::SetDuration(int duration)
{
    duration_ = duration;
}

void JSAnimation::SetDelay(int delay)
{
    delay_ = delay;
}

void JSAnimation::SetLinearCurve()
{
    SetAnimationCurve("linear");
}

void JSAnimation::SetEaseCurve()
{
    SetAnimationCurve("ease");
}

void JSAnimation::SetEaseInCurve()
{
    SetAnimationCurve("ease-in");
}

void JSAnimation::SetEaseOutCurve()
{
    SetAnimationCurve("ease-out");
}

void JSAnimation::SetEaseInOutCurve()
{
    SetAnimationCurve("ease-in-out");
}

void JSAnimation::SetDecelerationCurve()
{
    SetAnimationCurve("extreme-deceleration");
}

void JSAnimation::SetFastOutLinearInCurve()
{
    SetAnimationCurve("fast-out-linear-in");
}

void JSAnimation::SetFastOutSlowInCurve()
{
    SetAnimationCurve("fast-out-slow-in");
}

void JSAnimation::SetLinearOutSlowInCurve()
{
    SetAnimationCurve("linear-out-slow-in");
}

void JSAnimation::SetFrictionCurve()
{
    SetAnimationCurve("friction");
}

void JSAnimation::SetRhythmCurve()
{
    SetAnimationCurve("rhythm");
}

void JSAnimation::SetSharpCurve()
{
    SetAnimationCurve("sharp");
}

void JSAnimation::SetSmoothCurve()
{
    SetAnimationCurve("smooth");
}

void JSAnimation::SetNone()
{
    noAnimation_ = true;
}

void JSAnimation::SetAnimationCurve(const std::string& animationCurve)
{
    LOGD("JSAnimation::SetAnimationCurve() %s", animationCurve.c_str());
    animationCurve_ = animationCurve;
}

#ifdef USE_QUICKJS_ENGINE
void JSAnimation::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSAnimation => MarkGC");
}

void JSAnimation::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSAnimation => ReleaseRT");
}

void JSAnimation::QjsDestructor(JSRuntime* rt, JSAnimation* animationObj)
{
    if (!animationObj) {
        return;
    }

    animationObj->ReleaseRT(rt);
    delete animationObj;
    LOGD("JSAnimation(QjsDestructor) end");
}

void JSAnimation::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSAnimation(QjsGcMark) start");

    JSAnimation* animationObj = Unwrap<JSAnimation>(val);
    if (!animationObj) {
        return;
    }

    animationObj->MarkGC(rt, markFunc);
    LOGD("JSAnimation(QjsGcMark) end");
}
#endif

void JSAnimation::JSBind(BindingTarget globalObj)
{
    LOGD("JSAnimation::JSBind()");
    JSClass<JSAnimation>::Declare("Animation");

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSAnimation>::Method("duration", &JSAnimation::SetDuration, opt);
    JSClass<JSAnimation>::Method("delay", &JSAnimation::SetDelay, opt);

    JSClass<JSAnimation>::Method("linear", &JSAnimation::SetLinearCurve, opt);
    JSClass<JSAnimation>::Method("ease", &JSAnimation::SetEaseCurve, opt);
    JSClass<JSAnimation>::Method("easeIn", &JSAnimation::SetEaseInCurve, opt);
    JSClass<JSAnimation>::Method("easeOut", &JSAnimation::SetEaseOutCurve, opt);
    JSClass<JSAnimation>::Method("easeInOut", &JSAnimation::SetEaseInOutCurve, opt);
    JSClass<JSAnimation>::Method("deceleration", &JSAnimation::SetDecelerationCurve, opt);
    JSClass<JSAnimation>::Method("fastOutLinearIn", &JSAnimation::SetFastOutLinearInCurve, opt);
    JSClass<JSAnimation>::Method("fastOutSlowIn", &JSAnimation::SetFastOutSlowInCurve, opt);
    JSClass<JSAnimation>::Method("linearOutSlowIn", &JSAnimation::SetLinearOutSlowInCurve, opt);
    JSClass<JSAnimation>::Method("friction", &JSAnimation::SetFrictionCurve, opt);
    JSClass<JSAnimation>::Method("rhythm", &JSAnimation::SetRhythmCurve, opt);
    JSClass<JSAnimation>::Method("sharp", &JSAnimation::SetSharpCurve, opt);
    JSClass<JSAnimation>::Method("smooth", &JSAnimation::SetSmoothCurve, opt);
    JSClass<JSAnimation>::Method("none", &JSAnimation::SetNone, opt);

    JSClass<JSAnimation>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
