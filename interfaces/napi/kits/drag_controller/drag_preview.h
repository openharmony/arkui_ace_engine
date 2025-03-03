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

#ifndef INTERFACES_NAPI_KITS_DRAG_CONTROLLER_DRAG_PREVIEW_H
#define INTERFACES_NAPI_KITS_DRAG_CONTROLLER_DRAG_PREVIEW_H

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "jsnapi.h"
#include "napi/native_common.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "native_value.h"
#include "node_api.h"
#include "interaction_manager.h"

#include "base/log/log_wrapper.h"
#include "bridge/common/utils/utils.h"
#include "core/common/ace_engine.h"
#include "frameworks/core/components/common/properties/color.h"

namespace OHOS::Ace::Napi {
using PreviewType = Msdp::DeviceStatus::PreviewType;
using PreviewStyle = Msdp::DeviceStatus::PreviewStyle;
using PreviewAnimation = Msdp::DeviceStatus::PreviewAnimation;
namespace {
constexpr int32_t ARG_COUNT_1 = 1;
constexpr int32_t ARG_COUNT_2 = 2;
constexpr int32_t DEFAULT_DURATION_VALUE = 1000;
} // namespace

class DragPreview {
public:
    DragPreview() = default;
    ~DragPreview() = default;

    static napi_value SetForegroundColor(napi_env env, napi_callback_info info)
    {
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_RETURN(scope, nullptr);
        size_t argc = ARG_COUNT_1;
        napi_value argv[ARG_COUNT_1] = { 0 };
        napi_value result = nullptr;
        void* data = nullptr;
        napi_get_cb_info(env, info, &argc, argv, &result, &data);
        NAPI_ASSERT(env, argc == ARG_COUNT_1, "require 1 parameter");

        Color foregroundColor;
        if (!ParseColor(env, argv[0], foregroundColor)) {
            LOGE("Parse foregroundColor failed");
            napi_close_handle_scope(env, scope);
            return nullptr;
        }

        DragPreview* dragPreview = nullptr;
        napi_unwrap(env, result, (void**)&dragPreview);
        if (dragPreview == nullptr) {
            LOGE("dragPreview is nullptr");
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        dragPreview->SetColor(foregroundColor);
        LOGI("foregroundColor is %{public}x", dragPreview->previewStyle_.foregroundColor);
        if (!dragPreview->hasAnimation_) {
            int32_t instanceId = Container::CurrentId();
            auto container = AceEngine::Get().GetContainer(instanceId);
            auto taskExecutor = container->GetTaskExecutor();
            taskExecutor->PostTask(
                [previewStyle = dragPreview->previewStyle_]() {
                    int32_t ret = Msdp::DeviceStatus::InteractionManager::
                        GetInstance()->UpdatePreviewStyle(previewStyle);
                    if (ret != 0) {
                        LOGE("Update preview style failed");
                        return;
                    };
                },
                TaskExecutor::TaskType::JS, "ArkUIDragUpdatePreviewStyle");
            dragPreview->previewStyle_.types.clear();
        }
        napi_close_handle_scope(env, scope);
        return nullptr;
    }

    static napi_value Animate(napi_env env, napi_callback_info info)
    {
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_RETURN(scope, nullptr);
        size_t argc = ARG_COUNT_2;
        napi_value argv[ARG_COUNT_2] = { 0 };
        napi_value result = nullptr;
        void* data = nullptr;
        napi_get_cb_info(env, info, &argc, argv, &result, &data);
        NAPI_ASSERT(env, argc == ARG_COUNT_2, "require 2 parameter");

        DragPreview* dragPreview = nullptr;
        napi_unwrap(env, result, (void**)&dragPreview);
        if (dragPreview == nullptr) {
            LOGE("dragPreview is nullptr");
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        dragPreview->hasAnimation_ = true;
        PreviewAnimation previewAnimation;
        ParseAnimationInfo(env, argv[0], previewAnimation);

        napi_call_function(env, nullptr, argv[1], 0, nullptr, nullptr);
        int32_t instanceId = Container::CurrentId();
        auto container = AceEngine::Get().GetContainer(instanceId);
        auto taskExecutor = container->GetTaskExecutor();
        taskExecutor->PostTask(
            [previewStyle = dragPreview->previewStyle_, previewAnimation]() {
                int32_t ret = Msdp::DeviceStatus::InteractionManager::
                    GetInstance()->UpdatePreviewStyleWithAnimation(previewStyle, previewAnimation);
                if (ret != 0) {
                    LOGE("Update preview style with animation failed");
                    return;
                };
            },
            TaskExecutor::TaskType::JS, "ArkUIDragUpdatePreviewAnimationStyle");
        dragPreview->hasAnimation_ = false;
        dragPreview->previewStyle_.types.clear();
        napi_close_handle_scope(env, scope);
        return nullptr;
    }

    void NapiSerializer(napi_env& env, napi_value& result)
    {
        napi_status status = napi_wrap(
            env, result, this,
            [](napi_env env, void* data, void* hint) {
                DragPreview* dragPreview = static_cast<DragPreview*>(data);
                if (dragPreview != nullptr) {
                    delete dragPreview;
                }
            },
            nullptr, nullptr);
        if (status != napi_ok) {
            LOGE("napi_wrap failed");
            return;
        }
        /* insert callback functions */
        const char* funName = "setForegroundColor";
        napi_value funcValue = nullptr;
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, SetForegroundColor, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);

        funName = "animate";
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, Animate, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);
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

    static napi_value ParseAnimationInfo(napi_env env, napi_value object, PreviewAnimation& animationInfo)
    {
        CHECK_NULL_RETURN(object, nullptr);
        napi_valuetype valueType = napi_undefined;
        bool hasProperty = false;
        double durationValue = 0;
        napi_has_named_property(env, object, "duration", &hasProperty);
        if (!hasProperty) {
            animationInfo.duration = DEFAULT_DURATION_VALUE;
        } else {
            napi_value durationNApi = nullptr;
            napi_get_named_property(env, object, "duration", &durationNApi);
            napi_typeof(env, durationNApi, &valueType);
            NAPI_ASSERT(env, valueType == napi_number, "The type of duration is incorrect");
            napi_status status = napi_get_value_double(env, durationNApi, &durationValue);
            NAPI_ASSERT(env, status == napi_ok, "Parse duration failed");
            if (GreatOrEqual(durationValue, INT32_MAX)) {
                durationValue = INT32_MAX;
            } else if (LessOrEqual(durationValue, 0)) {
                durationValue = 0;
            }
            animationInfo.duration = static_cast<int32_t>(durationValue);
        }
        LOGI("animationInfo duration is %{public}d", animationInfo.duration);

        napi_has_named_property(env, object, "curve", &hasProperty);
        if (!hasProperty) {
            ParseCurveInfo(Curves::EASE_IN_OUT->ToString(), animationInfo.curveName, animationInfo.curve);
            return nullptr;
        }
        napi_value curveNApi = nullptr;
        napi_get_named_property(env, object, "curve", &curveNApi);
        ParseCurve(env, curveNApi, animationInfo.curveName, animationInfo.curve);
        return nullptr;
    }
    PreviewStyle previewStyle_ { {}, 0, -1, -1, -1 };
    bool hasAnimation_ { false };
};
} // namespace OHOS::Ace::Napi
#endif // #define INTERFACES_NAPI_KITS_DRAG_CONTROLLER_DRAG_PREVIEW_H