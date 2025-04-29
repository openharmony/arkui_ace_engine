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
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
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
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
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
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
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
    if (xcPattern->HasGotSurfaceHolder()) {
        return nullptr;
    }
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

void SetXComponentEnableTransparentLayer(ArkUINodeHandle node, ArkUI_Bool enable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableTransparentLayer(frameNode, enable);
}

void ResetXComponentEnableTransparentLayer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::EnableTransparentLayer(frameNode, false);
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
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
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
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    if (type == XComponentType::TEXTURE) {
        ViewAbstract::SetRenderFit(frameNode, RenderFit::RESIZE_FILL);
        return;
    }
    XComponentModelNG::SetRenderFit(frameNode, RenderFit::RESIZE_FILL);
}

ArkUI_Int32 GetXComponentRenderFit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(RenderFit::RESIZE_FILL));
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type == XComponentType::TEXTURE) {
        return static_cast<ArkUI_Int32>(ViewAbstract::GetRenderFit(frameNode));
    }
    return static_cast<ArkUI_Int32>(XComponentModelNG::GetSurfaceRenderFit(frameNode));
}

void SetXComponentSurfaceRect(ArkUINodeHandle node, ArkUI_Int32 offsetX,
    ArkUI_Int32 offsetY, ArkUI_Int32 surfaceWidth, ArkUI_Int32 surfaceHeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (surfaceWidth <= 0 || surfaceHeight <= 0) {
        return;
    }
    XComponentModelNG::SetXComponentSurfaceRect(frameNode, static_cast<float>(offsetX), static_cast<float>(offsetY),
        static_cast<float>(surfaceWidth), static_cast<float>(surfaceHeight));
}

void GetXComponentSurfaceRect(ArkUINodeHandle node, ArkUI_Int32& offsetX, ArkUI_Int32& offsetY,
    ArkUI_Int32& surfaceWidth, ArkUI_Int32& surfaceHeight)
{
    float surfaceRectOffsetX = 0.0f;
    float surfaceRectOffsetY = 0.0f;
    float surfaceRectWidth = 0.0f;
    float surfaceRectHeight = 0.0f;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    XComponentModelNG::GetXComponentSurfaceRect(frameNode, surfaceRectOffsetX, surfaceRectOffsetY,
        surfaceRectWidth, surfaceRectHeight);
    offsetX = static_cast<ArkUI_Int32>(surfaceRectOffsetX);
    offsetY = static_cast<ArkUI_Int32>(surfaceRectOffsetY);
    surfaceWidth = static_cast<ArkUI_Int32>(surfaceRectWidth);
    surfaceHeight = static_cast<ArkUI_Int32>(surfaceRectHeight);
}

void ResetXComponentSurfaceRect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    float width  = ViewAbstract::GetWidth(frameNode).GetNativeValue(static_cast<DimensionUnit>(0));
    float height = ViewAbstract::GetHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(0));
    XComponentModelNG::SetXComponentSurfaceRect(frameNode, 0.0f, 0.0f, width, height);
}

ArkUI_Bool GetXComponentEnableAnalyzer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto type = XComponentModelNG::GetXComponentType(frameNode);
    if (type != XComponentType::SURFACE && type != XComponentType::TEXTURE) {
        return false;
    }
    ArkUI_Bool isEnable = XComponentModelNG::GetXComponentEnableAnalyzer(frameNode);
    return isEnable;
}

void StartImageAnalyzer(ArkUINodeHandle node, void* arkuiNode, void* userData,
    XComponentAnalyzerCallback callback)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    std::function<void(int32_t)> nativeAnalyzerCallback = [arkuiNode, userData, callback](int32_t statusCode) {
        if (callback) {
            callback(arkuiNode, statusCode, userData);
        }
    };
    xcPattern->NativeStartImageAnalyzer(nativeAnalyzerCallback);
}

void StopImageAnalyzer(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->StopImageAnalyzer();
}

void* CreateSurfaceHolder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, nullptr);
    if (xcPattern->IsCreateSurfaceHolderForbidden()) {
        return nullptr;
    }
    OH_ArkUI_SurfaceHolder* surfaceHolder = xcPattern->GetSurfaceHolder();
    if (surfaceHolder == nullptr) {
        surfaceHolder = new OH_ArkUI_SurfaceHolder();
        xcPattern->SetSurfaceHolder(surfaceHolder);
    }
    return reinterpret_cast<void*>(surfaceHolder);
}

void Dispose(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_VOID(xcPattern);
    xcPattern->SetSurfaceHolder(nullptr);
}

ArkUI_Int32 SetAutoInitialize(ArkUINodeHandle node, ArkUI_Bool autoInitialize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return xcPattern->SetAutoInitialize(autoInitialize);
}

ArkUI_Int32 Initialize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return xcPattern->Initialize();
}

ArkUI_Int32 IsInitialized(ArkUINodeHandle node, ArkUI_Bool* isInitialized)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    bool value;
    auto res = xcPattern->IsInitialized(value);
    *isInitialized = value;
    return res;
}

ArkUI_Int32 Finalize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto xcPattern = frameNode->GetPattern<XComponentPatternV2>();
    CHECK_NULL_RETURN(xcPattern, ERROR_CODE_PARAM_INVALID);
    auto nodeType = xcPattern->GetXComponentNodeType();
    if (nodeType != XComponentNodeType::TYPE_NODE && nodeType != XComponentNodeType::CNODE) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return xcPattern->Finalize();
}

ArkUI_Bool GetXComponentIsBindNative(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto xcPattern = frameNode->GetPattern<XComponentPattern>();
    CHECK_NULL_RETURN(xcPattern, false);
    return static_cast<ArkUI_Bool>(xcPattern->IsBindNative());
}
} // namespace

namespace NodeModifier {
const ArkUIXComponentModifier* GetXComponentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIXComponentModifier modifier = {
        .setXComponentEnableAnalyzer = SetXComponentEnableAnalyzer,
        .resetXComponentEnableAnalyzer = ResetXComponentEnableAnalyzer,
        .setXComponentBackgroundColor = SetXComponentBackgroundColor,
        .resetXComponentBackgroundColor = ResetXComponentBackgroundColor,
        .setXComponentOpacity = SetXComponentOpacity,
        .resetXComponentOpacity = ResetXComponentOpacity,
        .setXComponentId = SetXComponentId,
        .setXComponentType = SetXComponentType,
        .setXComponentSurfaceSize = SetXComponentSurfaceSize,
        .getXComponentId = GetXComponentId,
        .getXComponentType = GetXComponentType,
        .getXComponentSurfaceWidth = GetXComponentSurfaceWidth,
        .getXComponentSurfaceHeight = GetXComponentSurfaceHeight,
        .getNativeXComponent = GetNativeXComponent,
        .setXComponentLibraryname = SetXComponentLibraryname,
        .setImageAIOptions = SetImageAIOptions,
        .initXComponent = InitXComponent,
        .setXComponentEnableSecure = SetXComponentEnableSecure,
        .resetXComponentEnableSecure = ResetXComponentEnableSecure,
        .setXComponentHdrBrightness = SetXComponentHdrBrightness,
        .resetXComponentHdrBrightness = ResetXComponentHdrBrightness,
        .setXComponentEnableTransparentLayer = SetXComponentEnableTransparentLayer,
        .resetXComponentEnableTransparentLayer = ResetXComponentEnableTransparentLayer,
        .setXComponentRenderFit = SetXComponentRenderFit,
        .resetXComponentRenderFit = ResetXComponentRenderFit,
        .getXComponentRenderFit = GetXComponentRenderFit,
        .setXComponentSurfaceRect = SetXComponentSurfaceRect,
        .getXComponentSurfaceRect = GetXComponentSurfaceRect,
        .resetXComponentSurfaceRect = ResetXComponentSurfaceRect,
        .getXComponentEnableAnalyzer = GetXComponentEnableAnalyzer,
        .startImageAnalyzer = StartImageAnalyzer,
        .stopImageAnalyzer = StopImageAnalyzer,
        .createSurfaceHolder = CreateSurfaceHolder,
        .dispose = Dispose,
        .setAutoInitialize = SetAutoInitialize,
        .initialize = Initialize,
        .isInitialized = IsInitialized,
        .finalize = Finalize,
        .getXComponentIsBindNative = GetXComponentIsBindNative,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIXComponentModifier* GetCJUIXComponentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIXComponentModifier modifier = {
        .loadXComponent = nullptr, // loadXComponent
        .setXComponentOptions = nullptr, // setXComponentOptions
        .getXComponentSurfaceId = nullptr, // getXComponentSurfaceId
        .getXComponentController = nullptr, // getXComponentController
        .setXComponentBackgroundColor = SetXComponentBackgroundColor,
        .resetXComponentBackgroundColor = ResetXComponentBackgroundColor,
        .setXComponentOpacity = SetXComponentOpacity,
        .resetXComponentOpacity = ResetXComponentOpacity,
        .setXComponentId = SetXComponentId,
        .setXComponentType = SetXComponentType,
        .setXComponentSurfaceSize = SetXComponentSurfaceSize,
        .getXComponentId = GetXComponentId,
        .getXComponentType = GetXComponentType,
        .getXComponentSurfaceWidth = GetXComponentSurfaceWidth,
        .getXComponentSurfaceHeight = GetXComponentSurfaceHeight,
        .getNativeXComponent = GetNativeXComponent,
        .setXComponentLibraryname = SetXComponentLibraryname,
        .setImageAIOptions = SetImageAIOptions,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
