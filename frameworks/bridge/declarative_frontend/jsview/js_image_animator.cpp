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

#include "bridge/declarative_frontend/jsview/js_image_animator.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/models/image_animator_model_impl.h"
#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace {
std::unique_ptr<ImageAnimatorModel> ImageAnimatorModel::instance_ = nullptr;
ImageAnimatorModel* ImageAnimatorModel::GetInstance()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
#ifdef NG_BUILD
        instance_.reset(new NG::ImageAnimatorModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ImageAnimatorModelNG());
        } else {
            instance_.reset(new Framework::ImageAnimatorModelImpl());
        }
#endif
    });
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr uint32_t DEFAULT_ITERATIONS = 1;
constexpr FillMode DEFAULT_FILL_MODE = FillMode::FORWARDS;

void JSImageAnimator::Create()
{
    ImageAnimatorModel::GetInstance()->Create();
}

void JSImageAnimator::JSBind(BindingTarget globalObj)
{
    JSClass<JSImageAnimator>::Declare("ImageAnimator");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSImageAnimator>::StaticMethod("create", &JSImageAnimator::Create, opt);
    JSClass<JSImageAnimator>::StaticMethod("images", &JSImageAnimator::SetImages, opt);
    JSClass<JSImageAnimator>::StaticMethod("state", &JSImageAnimator::SetState, opt);
    JSClass<JSImageAnimator>::StaticMethod("duration", &JSImageAnimator::SetDuration, opt);
    JSClass<JSImageAnimator>::StaticMethod("iterations", &JSImageAnimator::SetIteration, opt);
    JSClass<JSImageAnimator>::StaticMethod("reverse", &JSImageAnimator::SetIsReverse, opt);
    JSClass<JSImageAnimator>::StaticMethod("fixedSize", &JSImageAnimator::SetFixedSize, opt);
    JSClass<JSImageAnimator>::StaticMethod("fillMode", &JSImageAnimator::SetFillMode, opt);
    JSClass<JSImageAnimator>::StaticMethod("preDecode", &JSImageAnimator::SetPreDecode, opt);
    JSClass<JSImageAnimator>::StaticMethod("monitorInvisibleArea", &JSImageAnimator::SetAutoMonitorInvisibleArea, opt);

    JSClass<JSImageAnimator>::StaticMethod("onStart", &JSImageAnimator::OnStart, opt);
    JSClass<JSImageAnimator>::StaticMethod("onPause", &JSImageAnimator::OnPause, opt);
    JSClass<JSImageAnimator>::StaticMethod("onRepeat", &JSImageAnimator::OnRepeat, opt);
    JSClass<JSImageAnimator>::StaticMethod("onCancel", &JSImageAnimator::OnCancel, opt);
    JSClass<JSImageAnimator>::StaticMethod("onFinish", &JSImageAnimator::OnFinish, opt);
    JSClass<JSImageAnimator>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSImageAnimator>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSImageAnimator>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSImageAnimator>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSImageAnimator>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);

    JSClass<JSImageAnimator>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSImageAnimator::SetAutoMonitorInvisibleArea(const JSCallbackInfo& info)
{
    bool autoMonitorInvisibleArea = false;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        autoMonitorInvisibleArea = info[0]->ToBoolean();
    }
    ImageAnimatorModel::GetInstance()->SetAutoMonitorInvisibleArea(autoMonitorInvisibleArea);
}

void JSImageAnimator::SetImages(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (info[0]->IsNull()) {
        return;
    }
    if (!info[0]->IsArray()) {
        return;
    }
    JSRef<JSArray> imageArray = JSRef<JSArray>::Cast(info[0]);
    std::vector<ImageProperties> images;
    for (uint32_t i = 0; i < imageArray->Length(); ++i) {
        ImageProperties imageProperties;
        ParseImages(imageArray->GetValueAt(i), imageProperties);
        images.push_back(imageProperties);
    }

    ImageAnimatorModel::GetInstance()->SetImages(images);
}

void JSImageAnimator::SetState(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t state = static_cast<int32_t>(Animator::Status::IDLE);
    if (info[0]->IsNumber()) {
        state = info[0]->ToNumber<int32_t>();
        if (state < static_cast<int32_t>(Animator::Status::IDLE) ||
            state > static_cast<int32_t>(Animator::Status::STOPPED)) {
            state = static_cast<int32_t>(Animator::Status::IDLE);
        }
    }

    ImageAnimatorModel::GetInstance()->SetState(state);
}

void JSImageAnimator::SetDuration(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t duration = DEFAULT_DURATION;
    if (info[0]->IsNumber()) {
        duration = info[0]->ToNumber<int32_t>();
        if (duration < 0) {
            duration = DEFAULT_DURATION;
        }
    }

    ImageAnimatorModel::GetInstance()->SetDuration(duration);
}

void JSImageAnimator::SetIteration(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t iteration = DEFAULT_ITERATIONS;
    if (info[0]->IsNumber()) {
        iteration = info[0]->ToNumber<int32_t>();
        if (iteration < -1) {
            iteration = DEFAULT_ITERATIONS;
        }
    }

    ImageAnimatorModel::GetInstance()->SetIteration(iteration);
}

void JSImageAnimator::SetFillMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t fillMode = static_cast<int32_t>(DEFAULT_FILL_MODE);
    if (info[0]->IsNumber()) {
        fillMode = info[0]->ToNumber<int32_t>();
        if (fillMode < static_cast<int32_t>(FillMode::NONE) || fillMode > static_cast<int32_t>(FillMode::BOTH)) {
            fillMode = static_cast<int32_t>(DEFAULT_FILL_MODE);
        }
    }

    ImageAnimatorModel::GetInstance()->SetFillMode(fillMode);
}

void JSImageAnimator::SetPreDecode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    int32_t preDecode = 0;
    if (info[0]->IsNumber()) {
        preDecode = info[0]->ToNumber<int32_t>();
    }
    ImageAnimatorModel::GetInstance()->SetPreDecode(preDecode);
}

void JSImageAnimator::SetIsReverse(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool isReverse = false;
    if (info[0]->IsBoolean()) {
        isReverse = info[0]->ToBoolean();
    }
    ImageAnimatorModel::GetInstance()->SetIsReverse(isReverse);
}

void JSImageAnimator::SetFixedSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool fixedSize = true;
    if (info[0]->IsBoolean()) {
        fixedSize = info[0]->ToBoolean();
    }
    ImageAnimatorModel::GetInstance()->SetFixedSize(fixedSize);
}

void JSImageAnimator::OnStart(const JSCallbackInfo& info)
{
    auto onStart = GetAnimatorEvent(info, "ImageAnimator.onStart");
    ImageAnimatorModel::GetInstance()->SetOnStart(std::move(onStart));
}

void JSImageAnimator::OnPause(const JSCallbackInfo& info)
{
    auto onPause = GetAnimatorEvent(info, "ImageAnimator.onPause");
    ImageAnimatorModel::GetInstance()->SetOnPause(std::move(onPause));
}

void JSImageAnimator::OnRepeat(const JSCallbackInfo& info)
{
    auto onRepeat = GetAnimatorEvent(info, "ImageAnimator.onRepeat");
    ImageAnimatorModel::GetInstance()->SetOnRepeat(std::move(onRepeat));
}

void JSImageAnimator::OnCancel(const JSCallbackInfo& info)
{
    auto onCancel = GetAnimatorEvent(info, "ImageAnimator.onCancel");
    ImageAnimatorModel::GetInstance()->SetOnCancel(std::move(onCancel));
}

void JSImageAnimator::OnFinish(const JSCallbackInfo& info)
{
    auto onFinish = GetAnimatorEvent(info, "ImageAnimator.onFinish");
    ImageAnimatorModel::GetInstance()->SetOnFinish(std::move(onFinish));
}

AnimatorEvent JSImageAnimator::GetAnimatorEvent(const JSCallbackInfo& info, std::string&& eventName)
{
    if (info.Length() != 1) {
        return {};
    }
    if (!info[0]->IsFunction()) {
        return {};
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto animatorEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                             event = std::move(eventName)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT(event);
        func->Execute();
    };
    return animatorEvent;
}

void JSImageAnimator::ParseImages(const JSRef<JSVal>& image, ImageProperties& imageProperties)
{
    if (!image->IsObject()) {
        return;
    }
    JSRef<JSObject> jsObjImage = JSRef<JSObject>::Cast(image);
    bool srcValid = ParseJsMedia(jsObjImage->GetProperty("src"), imageProperties.src);
    GetJsMediaBundleInfo(jsObjImage->GetProperty("src"), imageProperties.bundleName, imageProperties.moduleName);
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        imageProperties.pixelMap = CreatePixelMapFromNapiValue(jsObjImage->GetProperty("src"));
#endif
    }
    ParseJsDimensionVp(jsObjImage->GetProperty("width"), imageProperties.width);
    ParseJsDimensionVp(jsObjImage->GetProperty("height"), imageProperties.height);
    ParseJsDimensionVp(jsObjImage->GetProperty("top"), imageProperties.top);
    ParseJsDimensionVp(jsObjImage->GetProperty("left"), imageProperties.left);
    ParseJsInt32(jsObjImage->GetProperty("duration"), imageProperties.duration);
}

} // namespace OHOS::Ace::Framework
