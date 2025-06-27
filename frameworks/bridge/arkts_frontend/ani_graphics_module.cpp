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

#if !defined(PREVIEW)
#include "canvas_ani/ani_canvas.h"
#endif

#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/render_node_peer_impl.h"
#include "core/interfaces/native/node/extension_custom_node.h"
#include "core/pipeline/pipeline_base.h"
#include "ui/base/geometry/ng/size_t.h"
#include "ui/base/referenced.h"

namespace OHOS::Ace::Framework {
namespace {
namespace {
const int32_t FLAG_DRAW_FRONT = 1;
const int32_t FLAG_DRAW_CONTENT = 1 << 1;
const int32_t FLAG_DRAW_BEHIND = 1 << 2;
} // namespace
ani_object CreateSizeObject(ani_env* env, const NG::DrawingContext& context)
{
    ani_status status;
    ani_class sizeClass;
    if ((status = env->FindClass("arkui.Graphics.SizeInternal", &sizeClass)) != ANI_OK) {
        LOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method sizeCtor;
    if ((status = env->Class_FindMethod(sizeClass, "<ctor>", "dd:", &sizeCtor)) != ANI_OK) {
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
    if ((status = env->FindClass("arkui.Graphics.SizeInternal", &sizeInPixelClass)) != ANI_OK) {
        LOGE("FindClass Size failed, %{public}d", status);
        return nullptr;
    }
    ani_method sizeInPixelCtor;
    if ((status = env->Class_FindMethod(sizeInPixelClass, "<ctor>", "dd:", &sizeInPixelCtor)) != ANI_OK) {
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
    if ((status = env->FindClass("arkui.Graphics.DrawContext", &drawContextClass)) != ANI_OK) {
        LOGE("FindClass DrawContext failed, %{public}d", status);
        return nullptr;
    }
    ani_method drawContextCtor;
    if ((status = env->Class_FindMethod(drawContextClass, "<ctor>", ":", &drawContextCtor)) != ANI_OK) {
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
    ani_object aniCanvas = OHOS::Rosen::Drawing::AniCanvas::CreateAniCanvas(env, &context.canvas);
    if (!aniCanvas) {
        LOGE("Create AniCanvas failed !");
    }
    env->Object_SetPropertyByName_Ref(result, "canvas_", (ani_ref)aniCanvas);
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

void AniGraphicsModule::SetDrawModifier(ani_env* env, ani_long ptr, ani_int flag, ani_object drawModifierObj)
{
    if (drawModifierObj == nullptr) {
        // drawModifierObj should not be nullptr;
        LOGF_ABORT("DrawModifier is undefined.");
    }
    ani_ref modifier;
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(ptr);
    CHECK_NULL_VOID(frameNode && frameNode->IsSupportDrawModifier());
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(drawModifierObj), &modifier);
    RefPtr<NG::DrawModifier> drawModifier = AceType::MakeRefPtr<NG::DrawModifier>();
    if (flag & FLAG_DRAW_BEHIND) {
        auto drawBehindFunc = [env, object = modifier](const NG::DrawingContext& context) {
            auto drawingContext = Framework::AniGraphicsModule::CreateDrawingContext(env, context);
            if (!drawingContext) {
                return;
            }
            env->Object_CallMethodByName_Void(reinterpret_cast<ani_fn_object>(object), "drawBehind",
                "C{arkui.Graphics.DrawContext}:", drawingContext);
        };
        drawModifier->drawBehindFunc = drawBehindFunc;
    }
    if (flag & FLAG_DRAW_CONTENT) {
        auto contentModifier = [env, object = modifier](const NG::DrawingContext& context) {
            auto drawingContext = Framework::AniGraphicsModule::CreateDrawingContext(env, context);
            if (!drawingContext) {
                return;
            }
            env->Object_CallMethodByName_Void(reinterpret_cast<ani_fn_object>(object), "drawContent",
                "C{arkui.Graphics.DrawContext}:", drawingContext);
        };
        drawModifier->drawContentFunc = contentModifier;
    }
    if (flag & FLAG_DRAW_FRONT) {
        auto frontModifier = [env, object = modifier](const NG::DrawingContext& context) {
            auto drawingContext = Framework::AniGraphicsModule::CreateDrawingContext(env, context);
            if (!drawingContext) {
                return;
            }
            env->Object_CallMethodByName_Void(
                reinterpret_cast<ani_fn_object>(object), "drawFront", "C{arkui.Graphics.DrawContext}:", drawingContext);
        };
        drawModifier->drawFrontFunc = frontModifier;
    }
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

void AniGraphicsModule::SetCustomCallback(
    ani_env* env, ani_long ptr, ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout)
{
    auto customFuncExisted = false;
    auto customNode = AceType::MakeRefPtr<NG::ExtensionCustomNode>();
    if (fnObjMeasure != nullptr) {
        customFuncExisted = true;
        ani_ref fnObjGlobalRef = nullptr;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObjMeasure), &fnObjGlobalRef);
        auto callbackFunc = [env, fnObjGlobalRef](const NG::LayoutConstraintF& context) -> void {
            std::vector<ani_ref> params;
            auto width1 = ArktsAniUtils::FloatToNumberObject(env, context.maxSize.Width());
            auto height1 = ArktsAniUtils::FloatToNumberObject(env, context.maxSize.Height());
            auto width2 = ArktsAniUtils::FloatToNumberObject(env, context.minSize.Width());
            auto height2 = ArktsAniUtils::FloatToNumberObject(env, context.minSize.Height());
            auto width3 = ArktsAniUtils::FloatToNumberObject(env, context.percentReference.Width());
            auto height3 = ArktsAniUtils::FloatToNumberObject(env, context.percentReference.Height());
            params.emplace_back((ani_ref)width1);
            params.emplace_back((ani_ref)height1);
            params.emplace_back((ani_ref)width2);
            params.emplace_back((ani_ref)height2);
            params.emplace_back((ani_ref)width3);
            params.emplace_back((ani_ref)height3);
            ani_ref fnReturnVal;
            env->FunctionalObject_Call(
                reinterpret_cast<ani_fn_object>(fnObjGlobalRef), params.size(), params.data(), &fnReturnVal);
        };
        customNode->SetMeasureCallback(callbackFunc);
    }
    if (fnObjLayout != nullptr) {
        customFuncExisted = true;
        ani_ref fnObjGlobalRef = nullptr;
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObjLayout), &fnObjGlobalRef);
        auto callbackFunc = [env, fnObjGlobalRef](const NG::OffsetF& context) -> void {
            std::vector<ani_ref> params;
            params.emplace_back((ani_ref)ArktsAniUtils::CreateDoubleObject(env, context.GetX()));
            params.emplace_back((ani_ref)ArktsAniUtils::CreateDoubleObject(env, context.GetY()));
            ani_ref fnReturnVal;
            env->FunctionalObject_Call(
                reinterpret_cast<ani_fn_object>(fnObjGlobalRef), params.size(), params.data(), &fnReturnVal);
        };
        customNode->SetLayoutCallback(callbackFunc);
    }
    if (!customFuncExisted) {
        return;
    }
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    frameNode->SetExtensionHandler(customNode);
}
void AniGraphicsModule::OnMeasureInnerMeasure(ani_env* env, ani_long ptr)
{
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_VOID(frameNode);
    auto layoutAlgorithm = frameNode->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithm);
    auto size = layoutAlgorithm->MeasureContent(frameNode->GetLayoutProperty()->CreateContentConstraint(),
        AceType::RawPtr(frameNode));
    if (size.has_value()) {
        frameNode->GetGeometryNode()->SetContentSize(size.value());
    }
    layoutAlgorithm->Measure(AceType::RawPtr(frameNode));
}
void AniGraphicsModule::OnLayoutInnerLayout(ani_env* env, ani_long ptr)
{
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(ptr);
    CHECK_NULL_VOID(frameNodePeer);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_VOID(frameNode);
    auto layoutAlgorithm = frameNode->GetLayoutAlgorithm();
    CHECK_NULL_VOID(layoutAlgorithm);
    layoutAlgorithm->Layout(AceType::RawPtr(frameNode));
}
} // namespace OHOS::Ace::Framework
