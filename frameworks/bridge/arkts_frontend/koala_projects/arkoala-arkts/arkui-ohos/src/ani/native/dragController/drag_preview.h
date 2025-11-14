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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_SRC_ANI_NATIVE_DRAG_CONTROLLER_DRAG_PREVIEW_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_SRC_ANI_NATIVE_DRAG_CONTROLLER_DRAG_PREVIEW_H

#include "ani.h"

#include "bridge/arkts_frontend/koala_projects/arkoala-arkts/framework/native/src/resource_color_helper.h"
#include "core/common/ace_engine.h"
#include "frameworks/base/error/error_code.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr int32_t DEFAULT_DURATION_VALUE = 1000;
constexpr int32_t SPECIFIED_CAPACITY = 16;
} // namespace

class DragPreview {
public:
    DragPreview() = default;
    ~DragPreview() = default;

    static void SetForegroundColor([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
        Ark_ResourceColor color, ani_long dragPreviewPtr)
    {
        CHECK_NULL_VOID(env);
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        DragPreview* dragPreview = reinterpret_cast<DragPreview*>(dragPreviewPtr);
        if (!dragPreview) {
            HILOGE("AceDrag, convert drag preview failed.");
            env->DestroyLocalScope();
            return;
        }
        const auto* modifier = GetNodeAniModifier();
        if (!modifier || !modifier->getDragControllerAniModifier()) {
            env->DestroyLocalScope();
            return;
        }
        modifier->getDragControllerAniModifier()->aniDragPreviewSetForegroundColor(color, dragPreview->previewAsync_);
        env->DestroyLocalScope();
    }

    static void Animate(
        [[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object optionsObj, ani_object handlerObj,
        ani_long dragPreviewPtr)
    {
        CHECK_NULL_VOID(env);
        if (!AniUtils::IsFunction(env, handlerObj)) {
            return;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        DragPreview* dragPreview = reinterpret_cast<DragPreview*>(dragPreviewPtr);
        if (!dragPreview) {
            HILOGE("AceDrag, convert drag preview failed.");
            env->DestroyLocalScope();
            return;
        }
        dragPreview->previewAsync_.hasAnimation = true;
        ParseAnimationInfo(env, optionsObj, dragPreviewPtr);
        ani_ref fnReturnVal;
        env->FunctionalObject_Call(static_cast<ani_fn_object>(handlerObj), 0, nullptr, &fnReturnVal);
        const auto* modifier = GetNodeAniModifier();
        if (!modifier || !modifier->getDragControllerAniModifier()) {
            env->DestroyLocalScope();
            return;
        }
        modifier->getDragControllerAniModifier()->aniDragPreviewAnimate(dragPreview->previewAsync_);
        env->DestroyLocalScope();
    }

    bool AniSerializer([[maybe_unused]] ani_env *env, ani_object& result)
    {
        static const char *className = "@ohos.arkui.dragController.dragController.DragPreviewInner";
        ani_class cls;
        if (ANI_OK != env->FindClass(className, &cls)) {
            HILOGE("AceDrag, find DragPreviewInner calss fail");
            return false;
        }
        ani_method method;
        if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &method)) {
            HILOGE("AceDrag, find constructor method failed.");
            return false;
        }
        if (ANI_OK != env->Object_New(cls, method, &result, reinterpret_cast<ani_long>(this))) {
            HILOGE("AceDrag, create DragPreview failed.");
            return false;
        }
        return true;
    }

private:
    static DragPreview* ConvertDragPreview(ani_env *env, ani_object object)
    {
        CHECK_NULL_RETURN(env, nullptr);
        ani_long serializer;
        if (ANI_OK != env->Object_GetFieldByName_Long(object, "dragPreview", &serializer)) {
            return nullptr;
        }
        return reinterpret_cast<DragPreview*>(serializer);
    }

    static void ParseAnimationInfo(ani_env *env, ani_object optionsObj, ani_long dragPreviewPtr)
    {
        CHECK_NULL_VOID(env);
        DragPreview* dragPreview = reinterpret_cast<DragPreview*>(dragPreviewPtr);
        if (!dragPreview) {
            HILOGE("AceDrag, convert drag preview failed.");
            return;
        }
        if (AniUtils::IsUndefined(env, optionsObj)) {
            return;
        }

        ani_status status = ANI_OK;
        ani_double duration = 0.0;
        ani_ref durationAni;
        env->Object_GetPropertyByName_Ref(optionsObj, "duration", &durationAni);
        if (AniUtils::IsUndefined(env, static_cast<ani_object>(durationAni))) {
            dragPreview->previewAsync_.previewAnimation.duration = DEFAULT_DURATION_VALUE;
        } else {
            if ((status = env->Object_CallMethodByName_Double(
                static_cast<ani_object>(durationAni), "toDouble", ":d", &duration)) != ANI_OK) {
                HILOGE("AceDrag, Object_CallMethodByName_Double failed. status = %{public}d", status);
            } else {
                if (GreatOrEqual(static_cast<size_t>(duration), INT32_MAX)) {
                    duration = INT32_MAX;
                } else if (LessOrEqual(static_cast<size_t>(duration), 0)) {
                    duration = 0;
                }
                dragPreview->previewAsync_.previewAnimation.duration = static_cast<int32_t>(duration);
            }
        }
        HILOGI("AceDrag, animation duration is %{public}d", dragPreview->previewAsync_.previewAnimation.duration);
    }

    ArkUIDragPreviewAsync previewAsync_;
};
} // namespace OHOS::Ace::Ani
#endif // #define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_SRC_ANI_NATIVE_DRAG_CONTROLLER_DRAG_PREVIEW_H