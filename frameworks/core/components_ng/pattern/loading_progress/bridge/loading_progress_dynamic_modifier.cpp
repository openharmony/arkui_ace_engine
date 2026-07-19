/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_loading_progress_modifier.h"

#include "base/error/error_code.h"
#include "base/utils/multi_thread.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "loading_progress_dynamic_modifier_multi_thread.h"
#ifndef CROSS_PLATFORM
#include "core/components_ng/pattern/loading_progress/bridge/loading_progress_model_impl.h"
#endif

namespace OHOS::Ace::NG {
namespace {

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

#ifndef CROSS_PLATFORM
Framework::LoadingProgressModelImpl* GetLoadingProgressModelImpl()
{
    static Framework::LoadingProgressModelImpl instance;
    return &instance;
}
#endif

void CreateLoadingProgress()
{
#ifdef NG_BUILD
    LoadingProgressModelNG::CreateModel();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        LoadingProgressModelNG::CreateModel();
        return;
    }
#ifndef CROSS_PLATFORM
    GetLoadingProgressModelImpl()->Create();
#endif
#endif
}

ArkUI_Uint32 GetLoadingProgressColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, 0x0);
    return LoadingProgressModelNG::GetColor(frameNode);
}

void SetLoadingProgressColor(ArkUINodeHandle node, uint32_t colorValue)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetColorByUser(frameNode, true);
    LoadingProgressModelNG::SetColor(frameNode, Color(colorValue));
}

void SetLoadingProgressColorPtr(ArkUINodeHandle node, uint32_t colorValue, void* colorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetColorByUser(frameNode, true);
    Color setColor = Color(colorValue);

    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> colorResObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                colorResObj, setColor, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            auto* color = static_cast<ResourceObject*>(colorRawPtr);
            colorResObj = AceType::Claim(color);
        }
        LoadingProgressModelNG::CreateWithResourceObj(frameNode, LoadingProgressResourceType::COLOR, colorResObj);
    }
    LoadingProgressModelNG::SetColor(frameNode, setColor);
}

void ResetLoadingProgressColor(ArkUINodeHandle node, bool isJsView)
{
    auto* frameNode = GetFrameNode(node);
    // This function has a mirror function (XxxMultiThread) and needs to be modified synchronously.
    FREE_NODE_CHECK(frameNode, ResetLoadingProgressColor, node, isJsView);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) && isJsView) {
        if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
            LoadingProgressModelNG::ResetColor(frameNode);
            LoadingProgressModelNG::SetColorByUser(frameNode, false);
        } else {
            auto progressTheme = frameNode->GetTheme<ProgressTheme>();
            CHECK_NULL_VOID(progressTheme);
            Color progressColor = progressTheme->GetLoadingColor();
            LoadingProgressModelNG::SetColor(frameNode, progressColor);
            LoadingProgressModelNG::SetColorByUser(frameNode, false);
        }
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) && !isJsView) {
        LoadingProgressModelNG::ResetColor(frameNode, isJsView);
    }
    if (SystemProperties::ConfigChangePerform()) {
        LoadingProgressModelNG::SetColorByUser(frameNode, false);
        LoadingProgressModelNG::CreateWithResourceObj(frameNode, LoadingProgressResourceType::COLOR, nullptr);
    }
}

ArkUI_Bool GetEnableLoading(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return LoadingProgressModelNG::GetEnableLoading(frameNode);
}

void SetEnableLoading(ArkUINodeHandle node, ArkUI_Bool enableLoadingValue)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetEnableLoading(frameNode, enableLoadingValue);
}

void ResetEnableLoading(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetEnableLoading(frameNode, true);
}

void SetLoadingProgressForegroundColor(ArkUINodeHandle node, ArkUI_Uint32 colorValue)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetForegroundColorParseFailed(frameNode, false);
    LoadingProgressModelNG::SetForegroundColor(frameNode, Color(colorValue));
}

void SetLoadingProgressForegroundColorPtr(
    ArkUINodeHandle node, ArkUI_Uint32 colorValue, void* foregroundColorRawPtr, bool isJsView)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    LoadingProgressModelNG::SetForegroundColorParseFailed(frameNode, false);
    LoadingProgressModelNG::SetForegroundColor(frameNode, Color(colorValue));

    if (SystemProperties::ConfigChangePerform()) {
        auto* color = reinterpret_cast<ResourceObject*>(foregroundColorRawPtr);
        auto colorResObj = AceType::Claim(color);
        LoadingProgressModelNG::CreateWithResourceObj(
            frameNode, LoadingProgressResourceType::FOREGROUNDCOLOR, colorResObj);
    }
}

void ResetLoadingProgressForegroundColor(ArkUINodeHandle node, bool isJsView, void* foregroundColorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (!isJsView) {
        LoadingProgressModelNG::SetForegroundColorParseFailed(frameNode, true);
        LoadingProgressModelNG::ResetColor(frameNode, isJsView);
    } else {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN) ||
            SystemProperties::ConfigChangePerform()) {
            LoadingProgressModelNG::SetForegroundColorParseFailed(frameNode, true);
            LoadingProgressModelNG::ResetColor(frameNode, isJsView);
        }
    }
    if (SystemProperties::ConfigChangePerform() && !isJsView) {
        LoadingProgressModelNG::CreateWithResourceObj(frameNode, LoadingProgressResourceType::FOREGROUNDCOLOR, nullptr);
    } else if (SystemProperties::ConfigChangePerform() && isJsView) {
        auto* color = reinterpret_cast<ResourceObject*>(foregroundColorRawPtr);
        auto colorResObj = AceType::Claim(color);
        LoadingProgressModelNG::SetColorByUser(frameNode, true);
        LoadingProgressModelNG::CreateWithResourceObj(
            frameNode, LoadingProgressResourceType::FOREGROUNDCOLOR, colorResObj);
    }
}

ArkUINodeHandle CreateLoadingProgressFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = LoadingProgressModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}
} // namespace

namespace NodeModifier {
const ArkUILoadingProgressModifier* GetLoadingProgressDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUILoadingProgressModifier modifier = {
        .getColor = GetLoadingProgressColor,
        .setColor = SetLoadingProgressColor,
        .setColorPtr = SetLoadingProgressColorPtr,
        .resetColor = ResetLoadingProgressColor,
        .getEnableLoading = GetEnableLoading,
        .setEnableLoading = SetEnableLoading,
        .resetEnableLoading = ResetEnableLoading,
        .setForegroundColor = SetLoadingProgressForegroundColor,
        .setForegroundColorPtr = SetLoadingProgressForegroundColorPtr,
        .resetForegroundColor = ResetLoadingProgressForegroundColor,
        .createLoadingProgressFrameNode = CreateLoadingProgressFrameNode,
        .createLoadingProgress = CreateLoadingProgress,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUILoadingProgressModifier* GetCJUILoadingProgressModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUILoadingProgressModifier modifier = {
        .getColor = GetLoadingProgressColor,
        .setColor = SetLoadingProgressColor,
        .setColorPtr = SetLoadingProgressColorPtr,
        .resetColor = ResetLoadingProgressColor,
        .getEnableLoading = GetEnableLoading,
        .setEnableLoading = SetEnableLoading,
        .resetEnableLoading = ResetEnableLoading,
        .setForegroundColor = SetLoadingProgressForegroundColor,
        .setForegroundColorPtr = SetLoadingProgressForegroundColorPtr,
        .resetForegroundColor = ResetLoadingProgressForegroundColor,
        .createLoadingProgressFrameNode = CreateLoadingProgressFrameNode,
        .createLoadingProgress = CreateLoadingProgress,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
