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

#include "bridge/arkts_frontend/ani_graphics_module.h"

#include <ani.h>

// #if !defined(PREVIEW)
// #include "canvas_ani/ani_canvas.h"
// #endif

#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/interfaces/native/implementation/render_node_peer_impl.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Framework {
namespace {
ani_object CreateSizeObject(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
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
    return sizeObject;
}

ani_object CreateSizeInPixelObject(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
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
    return sizeInPixelObject;
}
} // namespace

ani_object AniGraphicsModule::CreateDrawingContext(ani_env* env, const NG::DrawingContext& context)
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
    ani_object sizeObject = CreateSizeObject(env, context);
    env->Object_SetPropertyByName_Ref(result, "size_", (ani_ref)sizeObject);

    // sizeInPixel Object
    ani_object sizeInPixelObject = CreateSizeInPixelObject(env, context);
    env->Object_SetPropertyByName_Ref(result, "sizeInPixel_", (ani_ref)sizeInPixelObject);

    // canvas Object
#if !defined(PREVIEW)
    // ani_object aniCanvas = OHOS::Rosen::Drawing::AniCanvas::CreateAniCanvas(env, &context.canvas);
    // if (!aniCanvas) {
    //     LOGE("Create AniCanvas failed !");
    // }
    // env->Object_SetPropertyByName_Ref(result, "canvas_", (ani_ref)aniCanvas);
#endif

    return result;
}

void AniGraphicsModule::SetDrawCallback(ani_env* env, ani_long ptr, ani_fn_object fnObj)
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

void AniGraphicsModule::Invalidate(ani_env* env, ani_long ptr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode);
    const auto& extensionHandler = frameNode->GetExtensionHandler();
    if (extensionHandler) {
        extensionHandler->InvalidateRender();
    } else {
        frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
    }
}

void AniGraphicsModule::SetDrawModifier(ani_env* env, ani_long ptr, ani_object drawModifierObj)
{
    if (drawModifierObj == nullptr) {
        // drawModifierObj should not be nullptr;
        LOGF_ABORT("DrawModifier is undefined.");
    }
    ani_ref modifier;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(drawModifierObj), &modifier);
    auto drawBehindFunc = [env, object = modifier](const NG::DrawingContext& context) {
        auto drawingContext = Framework::AniGraphicsModule::CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(object), "drawBehind", "Larkui/Graphics/DrawContext;:V", drawingContext);
    };
    auto contentModifier = [env, object = modifier](const NG::DrawingContext& context) {
        auto drawingContext = Framework::AniGraphicsModule::CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(object), "drawContent", "Larkui/Graphics/DrawContext;:V", drawingContext);
    };
    auto frontModifier = [env, object = modifier](const NG::DrawingContext& context) {
        auto drawingContext = Framework::AniGraphicsModule::CreateDrawingContext(env, context);
        if (!drawingContext) {
            return;
        }
        env->Object_CallMethodByName_Void(
            reinterpret_cast<ani_fn_object>(object), "drawFront", "Larkui/Graphics/DrawContext;:V", drawingContext);
    };
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode && frameNode->IsSupportDrawModifier());
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    drawModifier->drawBehindFunc = drawBehindFunc;
    drawModifier->drawContentFunc = contentModifier;
    drawModifier->drawFrontFunc = frontModifier;
    frameNode->SetDrawModifier(drawModifier);
    if (frameNode) {
        const auto& extensionHandler = frameNode->GetExtensionHandler();
        if (extensionHandler) {
            extensionHandler->InvalidateRender();
        } else {
            frameNode->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
        }
    }
}
} // namespace OHOS::Ace::Framework
