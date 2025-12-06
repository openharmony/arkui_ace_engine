/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani_signature_builder.h>
#include "ani_utils.h"
#include "movingphotoview_ani.h"

namespace OHOS::Ace {

std::unique_ptr<NG::MovingPhotoModelNG> NG::MovingPhotoModelNG::instance_ = nullptr;
std::mutex NG::MovingPhotoModelNG::mutex_;

ani_long MovingPhotoAni::CreateMovingPhotoNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_int peerId, ani_int flags)
{
    auto node = NG::MovingPhotoModelNG::CreateMovingPhotoNode(peerId, u"");
    node->IncRefCount();
    auto ptr = Ace::AceType::RawPtr(node);
    return reinterpret_cast<ani_long>(ptr);
}

ani_long MovingPhotoAni::CreateMovingPhotoController([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object)
{
    auto controller = Ace::AceType::MakeRefPtr<NG::MovingPhotoController>();
    controller->IncRefCount();
    return reinterpret_cast<ani_long>(Ace::AceType::RawPtr(controller));
}

NG::MovingPhotoController* MovingPhotoAni::GetMovingPhotoController(ani_env* env, ani_ref ref)
{
    auto object = static_cast<ani_object>(ref);
    if (AniUtils::GetIsUndefinedObject(env, object)) {
        return nullptr;
    }
    ani_ref peerOptRef;
    if (ANI_OK != env->Object_GetFieldByName_Ref(static_cast<ani_object>(object), "peer", &peerOptRef)) {
        return nullptr;
    }
    ani_long ptr;
    if (ANI_OK != env->Object_GetFieldByName_Long(static_cast<ani_object>(peerOptRef), "ptr", &ptr)) {
        return nullptr;
    }
    return reinterpret_cast<NG::MovingPhotoController*>(ptr);
}

void MovingPhotoAni::DestroyPeerImpl(MovingPhotoControllerPeer* peer)
{
    if () {
        peer->DecRefCount();
    }
}

ani_long MovingPhotoAni::GetFinalizer([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object)
{
    return reinterpret_cast<ani_long>(&DestroyPeerImpl);
}

void MovingPhotoAni::SetMuted([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetMuted(movingPhotoNode, false);
        return;
    }
    std::optional<bool> mutedOpt;
    if (!AniUtils::ParseOptionalBool(env, options, mutedOpt)) {
        NG::MovingPhotoModelNG::SetMuted(movingPhotoNode, false);
        return;
    }
    bool mutedValue = false;
    if (mutedOpt) {
        mutedValue = mutedOpt.value();
    }
    NG::MovingPhotoModelNG::SetMuted(movingPhotoNode, mutedValue);
}

void MovingPhotoAni::SetObjectFit([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetObjectFit(movingPhotoNode, ImageFit::COVER);
        return;
    }
    ani_int fitNum {};
    if (ANI_OK != env->Object_GetPropertyByName_Int(options, "value", &fitNum)) {
        NG::MovingPhotoModelNG::SetObjectFit(movingPhotoNode, ImageFit::COVER);
        return;
    }
    ImageFit imageFit = ImageFit::COVER;
    imageFit = static_cast<ImageFit>(static_cast<int32_t>(fitNum));
    NG::MovingPhotoModelNG::SetObjectFit(movingPhotoNode, imageFit);
}

void MovingPhotoAni::SetOnComplete([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnComplete(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onComplete = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnComplete(movingPhotoNode, std::move(onComplete));
}

void MovingPhotoAni::SetOnStart([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnStart(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onStart = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnStart(movingPhotoNode, std::move(onStart));
}

void MovingPhotoAni::SetOnStop([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnStop(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onStop = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnStop(movingPhotoNode, std::move(onStop));
}

void MovingPhotoAni::SetOnPause([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnPause(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onPause = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnPause(movingPhotoNode, std::move(onPause));
}

void MovingPhotoAni::SetOnFinish([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnFinish(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onFinish = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnFinish(movingPhotoNode, std::move(onFinish));
}

void MovingPhotoAni::SetOnError([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnError(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onError = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnError(movingPhotoNode, std::move(onError));
}

void MovingPhotoAni::SetOnPrepared([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetOnPrepared(movingPhotoNode, nullptr);
        return;
    }

    auto asyncEvent = std::make_shared<AniAsyncEvent>(env, options);
    CHECK_NULL_VOID(asyncEvent);
    auto onPrepared = [asyncEvent]() {
        asyncEvent->Call(0, nullptr);
    };
    NG::MovingPhotoModelNG::SetOnPrepared(movingPhotoNode, std::move(onPrepared));
}

void MovingPhotoAni::SetAutoPlayPeriod([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_long nodeptr, ani_double startTimeAni, ani_double endTimeAni)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    double startTime = static_cast<double>(startTimeAni);
    double endTime = static_cast<double>(endTimeAni);
    NG::MovingPhotoModelNG::AutoPlayPeriod(movingPhotoNode, static_cast<int64_t>(startTime),
        static_cast<int64_t>(endTime));
}

void MovingPhotoAni::SetAutoPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::AutoPlay(movingPhotoNode, false);
        return;
    }
    ani_boolean isAutoPlayAni {};
    bool isAutoPlay = false;
    if (ANI_OK == env->Object_GetPropertyByName_Boolean(options, "value", &isAutoPlayAni)) {
        isAutoPlay = static_cast<bool>(isAutoPlayAni);
    }
    NG::MovingPhotoModelNG::AutoPlay(movingPhotoNode, isAutoPlay);
}

void MovingPhotoAni::SetRepeatPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::RepeatPlay(movingPhotoNode, false);
        return;
    }
    ani_boolean isRepeatPlayAni {};
    bool isRepeatPlay = false;
    if (ANI_OK == env->Object_GetPropertyByName_Boolean(options, "value", &isRepeatPlayAni)) {
        isRepeatPlay = static_cast<bool>(isRepeatPlayAni);
    }
    NG::MovingPhotoModelNG::RepeatPlay(movingPhotoNode, isRepeatPlay);
}

void MovingPhotoAni::SetEnableAnalyzer([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_long nodeptr, ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        NG::MovingPhotoModelNG::EnableAnalyzer(movingPhotoNode, false);
        return;
    }
    ani_boolean enabledAni {};
    bool enabled = false;
    if (ANI_OK == env->Object_GetPropertyByName_Boolean(options, "value", &enabledAni)) {
        enabled = static_cast<bool>(enabledAni);
    }
    NG::MovingPhotoModelNG::EnableAnalyzer(movingPhotoNode, enabled);
}

void MovingPhotoAni::StartPlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->StartPlayback();
}

void MovingPhotoAni::StopPlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->StopPlayback();
}

void MovingPhotoAni::PausePlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->Pause();
}

void MovingPhotoAni::Reset([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->Reset();
}

void MovingPhotoAni::Restart([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->Restart();
}

void MovingPhotoAni::RefreshMovingPhoto([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->RefreshMovingPhoto();
}

void MovingPhotoAni::EnableTransition([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_long nodeptr, ani_boolean options)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->EnableTransition(static_cast<bool>(options));
}

void MovingPhotoAni::SetPlaybackPeriod([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_long nodeptr, ani_double startTimeAni, ani_double endTimeAni)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    double startTime = static_cast<double>(startTimeAni);
    double endTime = static_cast<double>(endTimeAni);
    controller->SetPlaybackPeriod(static_cast<int64_t>(startTime), static_cast<int64_t>(endTime));
}

void MovingPhotoAni::EnableAutoPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
    ani_boolean options)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->EnableAutoPlay(static_cast<bool>(options));
}

void MovingPhotoAni::SetMovingPhotoViewOptions([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
    ani_long nodeptr, ani_object options)
{
    if (AniUtils::GetIsUndefinedObject(env, options)) {
        return;
    }
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);

    // movingphoto
    ani_ref movingPhotoRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "movingPhoto", &movingPhotoRef)) {
        return;
    }
    ani_object movingPhotoObj = static_cast<ani_object>(movingPhotoRef);
    if (AniUtils::GetIsUndefinedObject(env, movingPhotoObj)) {
        return;
    }
    SetMovingPhotoUri(env, movingPhotoNode, movingPhotoObj);
    // controller
    ani_ref objRef;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "controller", &objRef)) {
        auto controller = Ace::Referenced::Claim(GetMovingPhotoController(env, objRef));
        NG::MovingPhotoModelNG::SetMovingPhotoController(movingPhotoNode, controller);
    }
    // imageAIOptions
    ani_ref imageAIOptionsRef;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "imageAIOptions", &imageAIOptionsRef)) {
        NG::MovingPhotoModelNG::SetImageAIOptions(movingPhotoNode, reinterpret_cast<void*>(imageAIOptionsRef));
    }
    // movingphotoFormat
    NG::MovingPhotoModelNG::SetMovingPhotoFormat(movingPhotoNode, ParsePixelMapFormat(env, options));
    // dynamicRangeMode
    NG::MovingPhotoModelNG::SetDynamicRangeMode(movingPhotoNode, ParseDynamicRangeMode(env, options));
    // waterMask
    ani_ref playWithMaskRef;
    bool playWithMaskValue = false;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "playWithMask", &playWithMaskRef)) {
        std::optional<bool> playWithMaskOpt;
        if (AniUtils::ParseOptionalBool(env, static_cast<ani_object>(playWithMaskRef), playWithMaskOpt)) {
            if (playWithMaskOpt) {
                playWithMaskValue = playWithMaskOpt.value();
            }
        }
    }
    NG::MovingPhotoModelNG::SetWaterMask(movingPhotoNode, playWithMaskValue);
}

void MovingPhotoAni::SetMovingPhotoUri(ani_env *env, NG::MovingPhotoNode* movingPhotoNode, ani_object obj)
{
    ani_ref fn_ref;
    if (ANI_OK == env->Object_CallMethodByName_Ref(obj, "getUri", ":C{std.core.String}", &fn_ref)) {
        return;
    }
    std::string imageUriStr = AniUtils::AniStringToStdString(env, static_cast<ani_string>(fn_ref));
    NG::MovingPhotoModelNG::SetImageSrc(movingPhotoNode, imageUriStr);
}

MovingPhotoFormat MovingPhotoAni::ParsePixelMapFormat(ani_env *env, ani_object options)
{
    ani_ref format_ref;
    auto format = MovingPhotoFormat::UNKNOWN;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "movingPhotoFormat", &format_ref)) {
        return format;
    }
    if (AniUtils::GetIsUndefinedObject(env, format_ref)) {
        return format;
    }
    if (AniUtils::GetIsEnum(env, format_ref, OHOS::Ace::ANI_MOVINGPHOTO_PIXELMAPFORMAT)) {
        ani_int formatAni;
        if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(format_ref), &formatAni)) {
            return format;
        }
        int32_t formatNum;
        if (ANI_OK != AniUtils::GetInt32(env, formatAni, formatNum)) {
            return format;
        }
        return static_cast<MovingPhotoFormat>(formatNum);
    }
    return format;
}

DynamicRangeMode MovingPhotoAni::ParseDynamicRangeMode(ani_env *env, ani_object options)
{
    ani_ref dynamic_ref;
    auto dynamicRangeMode = DynamicRangeMode::HIGH;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "dynamicRangeMode", &dynamic_ref)) {
        return dynamicRangeMode;
    }
    if (AniUtils::GetIsUndefinedObject(env, dynamic_ref)) {
        return dynamicRangeMode;
    }
    if (AniUtils::GetIsEnum(env, dynamic_ref, OHOS::Ace::ANI_MOVINGPHOTO_DYNAMICRANGEMODE)) {
        ani_int dynamicAni;
        if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(dynamic_ref), &dynamicAni)) {
            return dynamicRangeMode;
        }
        int32_t dynamicRangeModeNum;
        if (ANI_OK != AniUtils::GetInt32(env, dynamicAni, dynamicRangeModeNum)) {
            return dynamicRangeMode;
        }
        return static_cast<DynamicRangeMode>(dynamicRangeModeNum);
    }
    return dynamicRangeMode;
}

} // namespace OHOS::Ace

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    ani_status isVersionOk = vm->GetEnv(ANI_VERSION_1, &env);
    if (ANI_OK != isVersionOk) {
        return isVersionOk;
    }
    ani_class cls;
    ani_status isOk = env->FindClass(OHOS::Ace::ANI_MOVINGPHOTO_NATIVE, &cls);
    if (ANI_OK != isOk) {
        return isOk;
    }
    std::array methods = {
        ani_native_function{"createMovingPhoto", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::CreateMovingPhotoNode)},
        ani_native_function{"setMovingPhotoViewOptions", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetMovingPhotoViewOptions)},
        ani_native_function{"muted", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetMuted)},
        ani_native_function{"objectFit", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetObjectFit)},
        ani_native_function{"autoPlayPeriod", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetAutoPlayPeriod)},
        ani_native_function{"autoPlay", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetAutoPlay)},
        ani_native_function{"repeatPlay", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetRepeatPlay)},
        ani_native_function{"enableAnalyzer", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetEnableAnalyzer)},
        ani_native_function{"onComplete", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnComplete)},
        ani_native_function{"onStart", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnStart)},
        ani_native_function{"onStop", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnStop)},
        ani_native_function{"onPause", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnPause)},
        ani_native_function{"onFinish", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnFinish)},
        ani_native_function{"onError", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnError)},
        ani_native_function{"onPrepared", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetOnPrepared)},
        ani_native_function{"createMovingPhotoController", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::CreateMovingPhotoController)},
        ani_native_function{"getFinalizer", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::GetFinalizer)},
        ani_native_function{"startPlayback", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::StartPlayback)},
        ani_native_function{"stopPlayback", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::StopPlayback)},
        ani_native_function{"refreshMovingPhoto", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::RefreshMovingPhoto)},
        ani_native_function{"pausePlayback", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::PausePlayback)},
        ani_native_function{"reset", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::Reset)},
        ani_native_function{"restart", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::Restart)},
        ani_native_function{"enableTransition", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::EnableTransition)},
        ani_native_function{"setPlaybackPeriod", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::SetPlaybackPeriod)},
        ani_native_function{"enableAutoPlay", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::MovingPhotoAni::EnableAutoPlay)},
    };
    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        return ANI_INVALID_TYPE;
    };
    *result = ANI_VERSION_1;
    return ANI_OK;
}
