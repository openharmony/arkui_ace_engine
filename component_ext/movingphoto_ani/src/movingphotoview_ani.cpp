/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "movingphotoview_ani.h"

extern const char _binary_multimedia_movingphotoview_js_start[];
extern const char _binary_multimedia_movingphotoview_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_multimedia_movingphotoview_js_end[];
extern const char _binary_multimedia_movingphotoview_abc_end[];
#else
extern const char* _binary_multimedia_movingphotoview_js_end;
extern const char* _binary_multimedia_movingphotoview_abc_end;
#endif

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

NG::MovingPhotoController* MovingPhotoAni::CreateMovingPhotoController(ani_env* env, ani_ref ref)
{
    auto object = static_cast<ani_object>(ref);
    if (MovingPhotoAni::GetIsUnderfinedObject(env, object)) {
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

void MovingPhotoAni::DestroyPeerImpl(void *peer)
{
    auto controller = static_cast<MovingPhotoControllerPeer *>(peer);
    CHECK_NULL_VOID(controller);
    delete controller;
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetMuted(movingPhotoNode, false);
        return;
    }
    std::optional<bool> mutedOpt;
    if (!MovingPhotoAni::ParseOptionalBool(env, options, mutedOpt)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetObjectFit(movingPhotoNode, ImageFit::COVER);
        return;
    }
    ani_ref objectFitAni;
    ImageFit imageFit = ImageFit::COVER;

    if (ANI_OK != env->Object_GetFieldByName_Ref(options, "value", &objectFitAni)) {
        if (GetIsImageFitEnum(env, objectFitAni)) {
            ani_int imageFitNum;
                if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(objectFitAni), &imageFitNum)) {
                    imageFit = ImageFit::COVER;
                }
        }
        imageFit = static_cast<ImageFit>(static_cast<int32_t>(imageFitNum));
    }
    NG::MovingPhotoModelNG::SetObjectFit(movingPhotoNode, imageFit);
}

void MovingPhotoAni::SetObjectFit([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                  ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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

void MovingPhotoAni::SetOnComplete([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                  ani_object options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
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

void MovingPhotoAni::SetAutoPlayPeriod([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                  ani_double startTimeAni, ani_double endTimeAni)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    double startTime = static_cast<double>(startTimeAni)
    double endTime = static_cast<double>(endTimeAni)
    NG::MovingPhotoModelNG::SetAutoPlayPeriod(movingPhotoNode, startTime, endTime);
}

void MovingPhotoAni::SetAutoPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                  ani_double options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
        NG::MovingPhotoModelNG::AutoPlay(movingPhotoNode, false);
        return;
    }
    ani_boolean isAutoPlayAni {};
    bool isAutoPlay = false;
    if (ANI_OK != env->Object_GetPropertyByName_Boolean(options, "value", &isAutoPlayAni)) {
        isAutoPlay = static_cast<bool>(isAutoPlayAni);
    }
    NG::MovingPhotoModelNG::AutoPlay(movingPhotoNode, isAutoPlay);
}

void MovingPhotoAni::SetRepeatPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                  ani_double options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
        NG::MovingPhotoModelNG::SetRepeatPlay(movingPhotoNode, false);
        return;
    }
    ani_boolean isRepeatPlayAni {};
    bool isRepeatPlay = false;
    if (ANI_OK != env->Object_GetPropertyByName_Boolean(options, "value", &isRepeatPlayAni)) {
        isRepeatPlay = static_cast<bool>(isRepeatPlayAni);
    }
    NG::MovingPhotoModelNG::RepeatPlay(movingPhotoNode, isRepeatPlay);
}

void MovingPhotoAni::SetEnableAnalyzer([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                  ani_double options)
{
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    if (MovingPhotoAni::GetIsUnderfinedObject(env, options)) {
        NG::MovingPhotoModelNG::EnableAnalyzer(movingPhotoNode, false);
        return;
    }
    ani_boolean enabledAni {};
    bool enabled = false;
    if (ANI_OK != env->Object_GetPropertyByName_Boolean(options, "value", &enabledAni)) {
        enabled = static_cast<bool>(enabledAni);
    }
    NG::MovingPhotoModelNG::EnableAnalyzer(movingPhotoNode, enabled);
}

void MovingPhotoAni::StartPlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->StartPlayback();
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
    controller->PausePlayback();
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

void MovingPhotoAni::RefreshMovingPhoto([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->RefreshMovingPhoto();
}

void MovingPhotoAni::EnableTransition([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr
                                      ani_boolean options)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->EnableTransition(static_cast<bool>(options));
}

void MovingPhotoAni::SetPlaybackPeriod([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                        ani_long options, ani_double startTimeAni, ani_double endTimeAni)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->SetPlaybackPeriod(static_cast<double>(startTimeAni), static_cast<double>(endTimeAni));
}

void MovingPhotoAni::EnableAutoPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                        ani_long options)
{
    NG::MovingPhotoController* controller = reinterpret_cast<NG::MovingPhotoController*>(nodeptr);
    controller->EnableAutoPlay(static_cast<bool>(options));
}

void MovingPhotoAni::SetMovingPhotoViewOptions([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object, ani_long nodeptr,
                                        ani_long options)
{
    if (GetIsUndefinedObject(env, options)) {
        return;
    }
    auto movingPhotoNode = reinterpret_cast<NG::MovingPhotoNode *>(nodeptr);
    CHECK_NULL_VOID(movingPhotoNode);
    ani_ref objRef;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "controller", &objRef)) {
        auto controller = Ace::Referenced::Claim(MovingPhotoAni::GetMovingPhotoController(env, objRef));
        NG::MovingPhotoModelNG::SetMovingPhotoController(movingPhotoNode, controller);
    }
    ani_ref imageAIOptionsRef;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "controller", &objRef)) {
        auto controller = Ace::Referenced::Claim(MovingPhotoAni::GetMovingPhotoController(env, objRef));
        NG::MovingPhotoModelNG::SetImageAIOptions(movingPhotoNode, reinterpret_cast<void*>(imageAIOptionRef));
    }
    NG::MovingPhotoModelNG::SetMovingPhotoFormat(movingPhotoNode, ParsePixelMapFormat(env, options));
    NG::MovingPhotoModelNG::SetDynamicRangeMode(movingPhotoNode, ParseDynamicRangeMode(env, options));
    ani_ref playWithMaskRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "playWithMask", &playWithMaskRef)) {
        return;
    }
    std::optional<bool> playWithMaskOpt;
    if (!MovingPhotoAni::ParseOptionalBool(env, static_cast<ani_object>(playWithMaskRef), playWithMaskOpt)) {
        return;
    }
    bool playWithMaskValue = false;
    if (playWithMaskRef) {
        playWithMaskValue = playWithMaskRef.value();
    }
    NG::MovingPhotoModelNG::SetWaterMask(movingPhotoNode, playWithMaskValue);
}

bool MovingPhotoAni::SetMovingPhotoObject(ani_env env, NG::MovingPhotoNode* movingPhotoNode, ani_object obj)
{
    if (GetIsUndefinedObject(env, options)) {
        return false;
    }
    arkts::ani_signature::Type classType = 
        arkts::ani_signature::Builder::BuildClass({"@ohos.file.photoAccessHelper.movingPhoto"});
    ani_class movingPhotoClass;
    if (ANI_OK != env->FindClass(classType.Descriptor().c_str(), &movingPhotoClass)) {
        return false;
    }
    arkts::ani_signature::SignatureBuilder sb{};
    ani_method getMethod;
    sb.SetReturnLong();
    if (env->Class_FindMethod(movingPhotoClass, "getUri", sb.BuildSignatureDescriptor().c_str(), &getMethod) !=
        ANI_OK) {
        return false;    
    }
    ani_ref imageUriRef;
    if (env->Object_CallMethod_Ref(obj, getMethod, &imageUriRef) != ANI_OK) {
        return false;
    }
    std::string imageUriStr = AniStringToStdString(env, static_cast<ani_string>(imageUriRef));
    NG::MovingPhotoModelNG::SetMovingPhotoObject(movingPhotoNode, imageUriStr);
    return true;
}

bool MovingPhotoAni::GetIsUndefinedObject(ani_env *env, ani_ref objectRef)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(objectRef, isUndefined)) {
        return true;
    }
    return (bool)isUndefined;
}

void MovingPhotoAni::GetIsImageFitEnum(ani_env *env, ani_ref objectRef) {
    ani_enum ImageFitEnum;
    if (ANI_OK != env->FindEnum('arkui.component.enums.ImageFit', &ImageFitEnum)) {
        return false;
    }
    ani_boolean isEnum;
    if (env->Object_InstanceOf(static_cast<ani_object>(objectRef), ImageFitEnum, &isEnum)) {
        return false;
    }
    return (bool)isEnum;
}

void MovingPhotoAni::GetIsPixelMapFormatEnum(ani_env *env, ani_ref objectRef) {
    arkts::ani_signature::Type enumType = 
        arkts::ani_signature::Builder::BuildClass({"@ohos.multimedia.movingphotoview.PixelMapFormat"});
    ani_enum formatEnum;
    if (ANI_OK != env->FindEnum(enumType.Descriptor().c_str(), &formatEnum)) {
        return false;
    }
    ani_boolean isEnum;
    if (env->Object_InstanceOf(static_cast<ani_object>(objectRef), formatEnum, &isEnum)) {
        return false;
    }
    return (bool)isEnum;
}

void MovingPhotoAni::GetIsDynamicRangeModeEnum(ani_env *env, ani_ref objectRef) {
    arkts::ani_signature::Type enumType = 
        arkts::ani_signature::Builder::BuildClass({"@ohos.multimedia.movingphotoview.DynamicRangeMode"});
    ani_enum dynamicRangeMode;
    if (ANI_OK != env->FindEnum(enumType.Descriptor().c_str(), &dynamicRangeMode)) {
        return false;
    }
    ani_boolean isEnum;
    if (env->Object_InstanceOf(static_cast<ani_object>(objectRef), dynamicRangeMode, &isEnum)) {
        return false;
    }
    return (bool)isEnum;
}

MovingPhotoFormat MovingPhotoAni::ParsePixelMapFormat(ani_env *env, ani_object options)
{
    ani_ref format_ref;
    auto format = MovingPhotoFormat::UNKNOWN;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "movingPhotoFormat", &format_ref)) {
        return format;
    }
    if (GetIsPixelMapFormatEnum(env, format_ref)) {
        ani_int formatAni;
        if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(format_ref), &formatAni)) {
            return format;
        }
        int32_t formatNum;
        if (ANI_OK != GetInt32(env, formatAni, formatNum)) {
            return format;
        }
        return static_cast<MovingPhotoFormat>(formatNum);
    }
    return format;
}

MovingPhotoFormat MovingPhotoAni::ParsePixelMapFormat(ani_env *env, ani_object options)
{
    ani_ref dynamicRangeMode_ref;
    auto dynamicRangeMode = DynamicRangeMode::HIGH;
    if (ANI_OK == env->Object_GetPropertyByName_Ref(options, "dynamicRangeMode", &dynamicRangeMode_ref)) {
        return dynamicRangeMode;
    }
    if (GetIsPixelMapFormatEnum(env, dynamicRangeMode_ref)) {
        ani_int dynamicRangeModeAni;
        if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(dynamicRangeMode_ref), &dynamicRangeModeAni)) {
            return dynamicRangeMode;
        }
        int32_t dynamicRangeModeNum;
        if (ANI_OK != GetInt32(env, dynamicRangeModeAni, dynamicRangeModeNum)) {
            return dynamicRangeMode;
        }
        return static_cast<MovingPhotoFormat>(dynamicRangeModeNum);
    }
    return dynamicRangeMode;
}

ani_status MovingPhotoAni::GetInt32(ani_env *env, ani_int arg, int32_t &value)
{
    value = static_cast<int32_t>(arg);
    return ANI_OK;
}

std::string MovingPhotoAni::AniStringToStdString(ani_env *env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);
    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();
    ani_size bytesWrittern = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytesWrittern);
    utf8Buffer[bytesWrittern] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

bool MovingPhotoAni::ParseOptionalBool(ani_env *env, ani_object object, std::optional<bool> &result)
{
    if (MovingPhotoAni::GetIsUndefinedObject(env, object)) {
        result.reset();
        return true;
    }
    bool boolValue;
    if (ANI_OK != MovingPhotoAni::GetBool(env, object, boolValue)) {
        return false;
    }
    result = boolValue;
    return true;
}

ani_status MovingPhotoAni::GetBool(ani_env *env, ani_boolean arg, bool &value)
{
    value = (arg == ANI_TRUE);
    return ANI_OK;
}

ani_status MovingPhotoAni::GetBool(ani_env *env, ani_object arg, bool &value)
{
    if (MovingPhotoAni::GetIsUndefinedObject(env, object)) {
        return ANI_ERROR;
    }

    ani_class cls {};
    static const std::string className = "std.core.Boolean";
    ani_status status = env->FindClass(className.c_str(), &cls);
    if (ANI_OK != status) {
        return status;
    }

    ani_method method {};
    status = env->Class_FindMethod(cls, "valueOf", nullptr, &method);
    if (ANI_OK != status) {
        return status;
    }
    
    ani_boolean result = 0;
    status = env->Object_CallMethod_Boolean(arg, method, &result);
    if (ANI_OK != status) {
        return status;
    }
    return GetBool(env, result, value);
}

} // namespace OHOS::Ace

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_OUT_OF_REF;
    }
    static const char *className = "@ohos.multimedia.movingphotoview.MovingPhotoNative";
    ani_class cls;
    ani_status isOk = env->FinClass(className, &cls);
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
    }
    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, method.data(), methods.size())) {
        return ANI_INVALID_TYPE;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
