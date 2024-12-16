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
#include "core/interfaces/native/node/node_xcomponent_modifier.h"

#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
namespace {
const uint32_t ERROR_UINT_CODE = -1;
std::string g_strValue;

void SetXComponentEnableAnalyzer(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableAnalyzer(frameNode, enable);
}

void ResetXComponentEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableAnalyzer(frameNode, false);
}

void SetXComponentBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    ViewAbstract::SetBackgroundColor(frameNode, Color(color));
}

void ResetXComponentBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetType(frameNode);
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    ViewAbstract::SetBackgroundColor(frameNode, (type == XComponentType::SURFACE) ? Color::BLACK : Color::TRANSPARENT);
}

void SetXComponentOpacity(ArkUINodeHandle node, ArkUI_Float32 opacity)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!XComponentModelNG::IsTexture(frameNode)) {
        return;
    }
    if ((LessNotEqual(opacity, 0.0)) || opacity > 1) {
        opacity = 1.0f;
    }
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void ResetXComponentOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!XComponentModelNG::IsTexture(frameNode)) {
        return;
    }
    ViewAbstract::SetOpacity(frameNode, 1.0f);
}

void SetXComponentId(ArkUINodeHandle node, const char* id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentId(frameNode, id);
}

void SetXComponentType(ArkUINodeHandle node, uint32_t type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentType(frameNode, static_cast<XComponentType>(type));
}

void SetXComponentSurfaceSize(ArkUINodeHandle node, uint32_t width, uint32_t height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentSurfaceSize(frameNode, width, height);
}

ArkUI_CharPtr GetXComponentId(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = XComponentModelNG::GetXComponentId(frameNode);
    return g_strValue.c_str();
}

ArkUI_Int32 GetXComponentType(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return static_cast<ArkUI_Int32>(XComponentModelNG::GetXComponentType(frameNode));
}

ArkUI_Uint32 GetXComponentSurfaceWidth(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return XComponentModelNG::GetXComponentSurfaceWidth(frameNode);
}

ArkUI_Uint32 GetXComponentSurfaceHeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return XComponentModelNG::GetXComponentSurfaceHeight(frameNode);
}

void* GetNativeXComponent(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, nullptr);
    auto pair = xcPattern->GetNativeXComponent();
    return reinterpret_cast<void*>(pair.second.lock().get());
}

void SetXComponentLibraryname(ArkUINodeHandle node, const char* libraryname)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetXComponentLibraryname(frameNode, libraryname);
}

void SetImageAIOptions(ArkUINodeHandle node, void* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::SetImageAIOptions(frameNode, options);
}

void InitXComponent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::InitXComponent(frameNode);
}

void SetXComponentEnableSecure(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableSecure(frameNode, enable);
}

void ResetXComponentEnableSecure(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableSecure(frameNode, false);
}

void SetXComponentHdrBrightness(ArkUINodeHandle node, ArkUI_Float32 hdrBrightness)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::HdrBrightness(frameNode, hdrBrightness);
}

void ResetXComponentHdrBrightness(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::HdrBrightness(frameNode, 1.0f);
}

void SetXComponentRenderFit(ArkUINodeHandle node, ArkUI_Int32 renderFitNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto renderFit = RenderFit::RESIZE_FILL;
    if (renderFitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
        renderFitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
        renderFit = static_cast<RenderFit>(renderFitNumber);
    }
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::TEXTURE) {
        ViewAbstract::SetRenderFit(frameNode, renderFit);
        return;
    }
    XComponentModelNG::SetRenderFit(frameNode, renderFit);
}

void ResetXComponentRenderFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::TEXTURE) {
        ViewAbstract::SetRenderFit(frameNode, RenderFit::RESIZE_FILL);
        return;
    }
    XComponentModelNG::SetRenderFit(frameNode, RenderFit::RESIZE_FILL);
}
} // namespace

namespace NodeModifier {
const ArkUIXComponentModifier* GetXComponentModifier()
{
    static const ArkUIXComponentModifier modifier = {
        nullptr, // loadXComponent
        nullptr, // setXComponentOptions
        nullptr, // getXComponentSurfaceId
        nullptr, // getXComponentController
        SetXComponentEnableAnalyzer,
        ResetXComponentEnableAnalyzer,
        SetXComponentBackgroundColor,
        ResetXComponentBackgroundColor,
        SetXComponentOpacity,
        ResetXComponentOpacity,
        SetXComponentId,
        SetXComponentType,
        SetXComponentSurfaceSize,
        GetXComponentId,
        GetXComponentType,
        GetXComponentSurfaceWidth,
        GetXComponentSurfaceHeight,
        GetNativeXComponent,
        SetXComponentLibraryname,
        SetImageAIOptions,
        InitXComponent,
        SetXComponentEnableSecure,
        ResetXComponentEnableSecure,
        SetXComponentHdrBrightness,
        ResetXComponentHdrBrightness,
        SetXComponentRenderFit,
        ResetXComponentRenderFit,
    };

    return &modifier;
}

const CJUIXComponentModifier* GetCJUIXComponentModifier()
{
    static const CJUIXComponentModifier modifier = {
        nullptr, // loadXComponent
        nullptr, // setXComponentOptions
        nullptr, // getXComponentSurfaceId
        nullptr, // getXComponentController
        SetXComponentBackgroundColor,
        ResetXComponentBackgroundColor,
        SetXComponentOpacity,
        ResetXComponentOpacity,
        SetXComponentId,
        SetXComponentType,
        SetXComponentSurfaceSize,
        GetXComponentId,
        GetXComponentType,
        GetXComponentSurfaceWidth,
        GetXComponentSurfaceHeight,
        GetNativeXComponent,
        SetXComponentLibraryname,
        SetImageAIOptions,
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG