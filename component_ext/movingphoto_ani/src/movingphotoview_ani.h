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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_ANI_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_ANI_H

#include <ani.h>
#include "movingphoto_controller.h"
#include "movingphoto_model_ng.h"

namespace OHOS::Ace {

constexpr const char* ANI_MOVINGPHOTO_NATIVE = "@ohos.multimedia.movingphotoview.MovingPhotoNative";
constexpr const char* ANI_MOVINGPHOTO_DYNAMICRANGEMODE = "@ohos.multimedia.movingphotoview.DynamicRangeMode";
constexpr const char* ANI_MOVINGPHOTO_PIXELMAPFORMAT = "@ohos.multimedia.movingphotoview.PixelMapFormat";
constexpr const char* ANI_ARKUI_COMPONENT_ENUMS_IMAGEFIT = "arkui.component.enums.ImageFit";

class MovingPhotoAni {
public:
    static ani_long CreateMovingPhotoNode([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_int peerId, ani_int flags);
    static void SetMovingPhotoViewOptions([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static ani_long GetFinalizer([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object);
    static void SetMuted([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetObjectFit([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnComplete([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnStart([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnStop([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnPause([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnFinish([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnError([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetOnPrepared([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetAutoPlayPeriod([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_double startTimeAni, ani_double endTimeAni);
    static void SetAutoPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetRepeatPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);
    static void SetEnableAnalyzer([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long nodeptr, ani_object options);

    static void StartPlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer);
    static void StopPlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer);
    static void PausePlayback([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer);
    static void Reset([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer);
    static void Restart([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer);
    static void EnableTransition([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer, ani_boolean options);
    static void RefreshMovingPhoto([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer);
    static void SetPlaybackPeriod([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer, ani_double startTimeAni, ani_double endTimeAni);
    static void EnableAutoPlay([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object,
                                                ani_long peer, ani_boolean options);

    static void MovingPhotoControllerConstructor([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object);
    static ani_long CreateMovingPhotoController([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class object);

private:
    static void DestroyPeerImpl(OHOS::Ace::NG::MovingPhotoController* peer);
    struct MovingPhotoControllerPeer {
        OHOS::Ace::RefPtr<OHOS::Ace::NG::MovingPhotoController> controller;
    };
    static MovingPhotoFormat ParsePixelMapFormat(ani_env *env, ani_object options);
    static DynamicRangeMode ParseDynamicRangeMode(ani_env *env, ani_object options);
    static void SetMovingPhotoUri(ani_env *env, NG::MovingPhotoNode *movingPhotoNode, ani_object obj);
    static OHOS::Ace::NG::MovingPhotoController* GetMovingPhotoController(ani_env* env, ani_ref ref);
};
}
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_ANI_H