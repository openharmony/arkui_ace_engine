/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ani.h>
#include <array>
#include <string>
#include <unistd.h>
#include <vector>

#include "canvas_ani/ani_canvas.h"

#include "base/log/log.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/common/container.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/interfaces/native/implementation/render_node_peer_impl.h"

namespace OHOS::Ace {
namespace {
ani_object CreateDrawingContext(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
    ani_object result = nullptr;

    // DrawContext object
    ani_class drawContextClass;
    if ((status = env->FindClass("Larkui/Graphics/DrawContext;", &drawContextClass)) != ANI_OK) {
        LOGE("FindClass DrawContext failed, %{public}d", status);
        return nullptr;
    }
    ani_method drawContextCtor;
    if ((status = env->Class_FindMethod(drawContextClass, "<ctor>", ":V", &drawContextCtor)) != ANI_OK) {
        LOGE("Class_FindMethod drawContextClass ctor failed, %{public}d", status);
        return nullptr;
    }
    if ((status = env->Object_New(drawContextClass, drawContextCtor, &result)) != ANI_OK) {
        LOGE("New DrawContext object failed, %{public}d", status);
        return nullptr;
    }

    // Size object
    ani_class sizeClass;
    if ((status = env->FindClass("Larkui/Graphics/SizeInternal;", &sizeClass)) != ANI_OK) {
        LOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method sizeCtor;
    if ((status = env->Class_FindMethod(sizeClass, "<ctor>", "DD:V", &sizeCtor)) != ANI_OK) {
        LOGE("Class_FindMethod sizeClass ctor failed, %{public}d", status);
        return nullptr;
    }
    ani_object sizeObject;
    ani_float width = PipelineBase::Px2VpWithCurrentDensity(context.height);
    ani_float height = PipelineBase::Px2VpWithCurrentDensity(context.width);
    if ((status = env->Object_New(sizeClass, sizeCtor, &sizeObject, width, height)) != ANI_OK) {
        LOGE("New Size object failed, %{public}d", status);
        return nullptr;
    }
    env->Object_SetPropertyByName_Ref(result, "size_", (ani_ref)sizeObject);

    // sizeInPixel Object
    ani_class sizeInPixelClass;
    if ((status = env->FindClass("Larkui/Graphics/SizeInternal;", &sizeInPixelClass)) != ANI_OK) {
        LOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method sizeInPixelCtor;
    if ((status = env->Class_FindMethod(sizeInPixelClass, "<ctor>", "DD:V", &sizeInPixelCtor)) != ANI_OK) {
        LOGE("Class_FindMethod sizeInPixelClass ctor failed, %{public}d", status);
        return nullptr;
    }
    ani_object sizeInPixelObject;
    ani_float widthInPixel = context.width;
    ani_float heightInPixel = context.height;
    if ((status = env->Object_New(
             sizeInPixelClass, sizeInPixelCtor, &sizeInPixelObject, widthInPixel, heightInPixel)) != ANI_OK) {
        LOGE("New SizeInPixel object failed, %{public}d", status);
        return nullptr;
    }
    env->Object_SetPropertyByName_Ref(result, "sizeInPixel_", (ani_ref)sizeInPixelObject);

    // canvas Object
    ani_object aniCanvas = OHOS::Rosen::Drawing::AniCanvas::CreateAniCanvas(env, &context.canvas);
    if (!aniCanvas) {
        LOGE("FZY Create AniCanvas failed !");
    }
    env->Object_SetPropertyByName_Ref(result, "canvas_", (ani_ref)aniCanvas);

    return result;
}
} // namespace
static void SetDrawCallback(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_long ptr, [[maybe_unused]] ani_fn_object fnObj)
{
    if (fnObj == nullptr) {
        LOGE("Draw callback is undefined.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    auto drawCallbackFunc = [env, fnObjGlobalRef](const NG::DrawingContext& context) -> void {
        auto drawingContext = CreateDrawingContext(env, context);
        if (!drawingContext) {
            LOGW("Create drawing context failed !");
            return;
        }
        std::vector<ani_ref> params;
        params.emplace_back((ani_ref)drawingContext);
        ani_ref fnReturnVal;
        env->FunctionalObject_Call(
            reinterpret_cast<ani_fn_object>(fnObjGlobalRef), params.size(), params.data(), &fnReturnVal);
    };

    auto* renderNodePeer = reinterpret_cast<RenderNodePeer*>(ptr);
    CHECK_NULL_VOID(renderNodePeer);
    auto renderNode = renderNodePeer->GetFrameNode();
    auto pattern = renderNode->GetPattern<NG::RenderNodePattern>();
    if (pattern) {
        pattern->SetDrawCallback(drawCallbackFunc);
    }
}
} // namespace OHOS::Ace

bool ANI_ConstructorForAni(ani_env* env)
{
    LOGE("FZY renderNode-ani ANI_ConstructorForAni");
    ani_class cls;
    if (ANI_OK != env->FindClass("L@ohos/arkui/graphics/Utils;", &cls)) {
        LOGE("renderNode-ani Not found graphics");
        return false;
    }
    std::array methods = {
        ani_native_function { "setDrawCallback", "JLstd/core/Function1;:V", reinterpret_cast<void*>(OHOS::Ace::SetDrawCallback) },
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        LOGE("renderNode-ani Module_BindNativeFunctions error");
        return false;
    }

    return true;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOGE("renderNode-ani Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }
    if (ANI_ConstructorForAni(env)) {
        *result = ANI_VERSION_1;
        return ANI_OK;
    }
    return ANI_ERROR;
}
