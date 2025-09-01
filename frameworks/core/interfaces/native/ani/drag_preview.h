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

#ifndef INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_PREVIEW_H
#define INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_PREVIEW_H

#include "ani.h"
#include <cstddef>

#include "interaction_manager.h"
#include "drag_controller_utils.h"

#include "core/common/ace_engine.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components/common/properties/color.h"

namespace OHOS::Ace::Ani {
using PreviewType = Msdp::DeviceStatus::PreviewType;
using PreviewStyle = Msdp::DeviceStatus::PreviewStyle;
using PreviewAnimation = Msdp::DeviceStatus::PreviewAnimation;
namespace {
constexpr int32_t DEFAULT_DURATION_VALUE = 1000;
constexpr int32_t SPECIFIED_CAPACITY = 16;
} // namespace

class DragPreview {
public:
    DragPreview() = default;
    ~DragPreview() = default;

    static void SetForegroundColor(
        [[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object colorObj, ani_long dragPreviewPtr)
    {
        CHECK_NULL_VOID(env);
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        Color foregroundColor;
        if (!ParseAniColor(env, colorObj, foregroundColor)) {
            AniThrow(env, "parse foreground color failed.", ERROR_CODE_PARAM_INVALID);
            TAG_LOGE(AceLogTag::ACE_DRAG, "parse foregroundColor failed.");
            env->DestroyLocalScope();
            return;
        }

        DragPreview* dragPreview = reinterpret_cast<DragPreview*>(dragPreviewPtr);
        if (!dragPreview) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "convert drag preview failed.");
            env->DestroyLocalScope();
            return;
        }
        dragPreview->SetColor(foregroundColor);
        TAG_LOGI(AceLogTag::ACE_DRAG, "foregroundColor is %{public}x", dragPreview->previewStyle_.foregroundColor);
        if (!dragPreview->hasAnimation_) {
            auto container = AceEngine::Get().GetContainer(Container::CurrentId());
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [previewStyle = dragPreview->previewStyle_]() {
                    int32_t result =
                        Msdp::DeviceStatus::InteractionManager::GetInstance()->UpdatePreviewStyle(previewStyle);
                    if (result != 0) {
                        TAG_LOGE(AceLogTag::ACE_DRAG, "update preview style failed. result = %{public}d", result);
                        return;
                    }
                },
                TaskExecutor::TaskType::JS, "ArkUIDragUpdatePreviewStyle");
            dragPreview->previewStyle_.types.clear();
        }
        env->DestroyLocalScope();
    }

    static void Animate(
        [[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object optionsObj, ani_object handlerObj,
        ani_long dragPreviewPtr)
    {
        CHECK_NULL_VOID(env);
        if (!IsFunctionObject(env, handlerObj)) {
            return;
        }
        if (ANI_OK != env->CreateLocalScope(SPECIFIED_CAPACITY)) {
            return;
        }
        DragPreview* dragPreview = reinterpret_cast<DragPreview*>(dragPreviewPtr);
        if (!dragPreview) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "convert drag preview failed.");
            env->DestroyLocalScope();
            return;
        }
        dragPreview->hasAnimation_ = true;
        PreviewAnimation previewAnimation;
        ParseAnimationInfo(env, optionsObj, previewAnimation);
        ani_ref fnReturnVal;
        env->FunctionalObject_Call(static_cast<ani_fn_object>(handlerObj), 0, nullptr, &fnReturnVal);

        auto container = AceEngine::Get().GetContainer(Container::CurrentId());
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [previewStyle = dragPreview->previewStyle_, previewAnimation]() {
                int32_t ret = Msdp::DeviceStatus::InteractionManager::
                    GetInstance()->UpdatePreviewStyleWithAnimation(previewStyle, previewAnimation);
                if (ret != 0) {
                    TAG_LOGE(AceLogTag::ACE_DRAG, "update preview style with animation failed. ret = %{public}d", ret);
                    return;
                };
            },
            TaskExecutor::TaskType::JS, "ArkUIDragUpdatePreviewAnimationStyle");
        dragPreview->hasAnimation_ = false;
        dragPreview->previewStyle_.types.clear();
        env->DestroyLocalScope();
    }

    void AniSerializer([[maybe_unused]] ani_env *env, ani_object& result)
    {
        static const char *className = "@ohos.arkui.dragController.dragController.DragPreviewInner";
        ani_class cls;
        if (ANI_OK != env->FindClass(className, &cls)) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "find DragPreviewInner calss fail");
            return;
        }
        ani_method method;
        if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &method)) {
            TAG_LOGE(AceLogTag::ACE_DRAG, "find constructor method failed.");
            return;
        }
        env->Object_New(cls, method, &result, reinterpret_cast<ani_long>(this));
    }

private:
    void SetColor(const Color& color)
    {
        auto iter = std::find(previewStyle_.types.begin(), previewStyle_.types.end(),
            PreviewType::FOREGROUND_COLOR);
        if (iter == previewStyle_.types.end()) {
            previewStyle_.types.emplace_back(PreviewType::FOREGROUND_COLOR);
        }
        previewStyle_.foregroundColor = color.GetValue();
    }

    static DragPreview* ConvertDragPreview(ani_env *env, ani_object object)
    {
        CHECK_NULL_RETURN(env, nullptr);
        ani_long serializer;
        if (ANI_OK != env->Object_GetFieldByName_Long(object, "dragPreview", &serializer)) {
            return nullptr;
        }
        return reinterpret_cast<DragPreview*>(serializer);
    }

    static void ParseAnimationInfo(ani_env *env, ani_object optionsObj, PreviewAnimation& animationInfo)
    {
        CHECK_NULL_VOID(env);
        if (IsUndefinedObject(env, optionsObj)) {
            return;
        }

        ani_status status = ANI_OK;
        ani_double duration = 0.0;
        ani_ref durationAni;
        env->Object_GetPropertyByName_Ref(optionsObj, "duration", &durationAni);
        if (Ani::IsUndefinedObject(env, durationAni)) {
            animationInfo.duration = DEFAULT_DURATION_VALUE;
        } else {
            if ((status = env->Object_CallMethodByName_Double(
                static_cast<ani_object>(durationAni), "unboxed", ":d", &duration)) != ANI_OK) {
                LOGE("AceDrag, Object_CallMethodByName_Double failed. status = %{public}d", status);
            } else {
                if (GreatOrEqual(static_cast<size_t>(duration), INT32_MAX)) {
                    duration = INT32_MAX;
                } else if (LessOrEqual(static_cast<size_t>(duration), 0)) {
                    duration = 0;
                }
                animationInfo.duration = static_cast<int32_t>(duration);
            }
        }
        TAG_LOGI(AceLogTag::ACE_DRAG, "animation duration is %{public}d", animationInfo.duration);

        ani_ref curveRef;
        env->Object_GetPropertyByName_Ref(optionsObj, "curve", &curveRef);
        if (Ani::IsUndefinedObject(env, curveRef)) {
            ParseCurveInfo(Curves::EASE_IN_OUT->ToString(), animationInfo.curveName, animationInfo.curve);
            return;
        }
        ParseCurve(env, static_cast<ani_object>(curveRef), animationInfo.curveName, animationInfo.curve);
    }

    PreviewStyle previewStyle_ { {}, 0, -1, -1, -1 };
    bool hasAnimation_ { false };
};
} // namespace OHOS::Ace::Ani
#endif // #define INTERFACES_ETS_ANI_DRAG_CONTROLLER_DRAG_PREVIEW_H