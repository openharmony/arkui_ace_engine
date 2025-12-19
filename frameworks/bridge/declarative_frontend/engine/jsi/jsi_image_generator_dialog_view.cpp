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
#include "bridge/declarative_frontend/engine/jsi/jsi_image_generator_dialog_view.h"

#include "bridge/common/utils/engine_helper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

extern const char _binary_imageGeneratorDialog_abc_start[];
extern const char _binary_imageGeneratorDialog_abc_end[];

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t DEFAULT_IGD_MASK_COLOR = 0X33182431;
constexpr char SHEET_PAGE_TAG[] = "SheetPage";

const Dimension DIMENSION_ONE_HUNDRED_PERCENT = Dimension(1, DimensionUnit::PERCENT);
const NG::SheetStyle GENERATOR_STYLE = NG::SheetStyle(
    { .height = DIMENSION_ONE_HUNDRED_PERCENT }, false, std::nullopt,
    Color::TRANSPARENT, Color(DEFAULT_IGD_MASK_COLOR), DIMENSION_ONE_HUNDRED_PERCENT);
}
bool ImageGeneratorDialogView::ExecuteImageGeneratorDialogAbc(int32_t instanceId)
{
    thread_local bool abcInitialized_ = false;
    if (abcInitialized_) {
        return true;
    }
    uint8_t* binaryBuff = (uint8_t*)_binary_imageGeneratorDialog_abc_start;
    int32_t binarySize = _binary_imageGeneratorDialog_abc_end - _binary_imageGeneratorDialog_abc_start;
    // run abc file
    RefPtr<Framework::JsEngine> jsEngine = nullptr;
    if (instanceId != -1) {
        // to_do: instance -1 case return false
        jsEngine = EngineHelper::GetEngine(instanceId);
    } else {
        jsEngine = EngineHelper::GetCurrentEngine();
    }
    CHECK_NULL_RETURN(jsEngine, false);
    if (!jsEngine->ExecuteJs(binaryBuff, binarySize)) {
        TAG_LOGE(AceLogTag::ACE_SIDEBAR, "[imageGenerator] execute abc file failed!");
        return false;
    }
    abcInitialized_ = true;
    return true;
}

bool ImageGeneratorDialogView::Create(int32_t instanceId)
{
    if (instanceId == -1) {
        return false;
    }
    auto viewStackProcessor = NG::ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(viewStackProcessor, false);
    auto uiNode = viewStackProcessor->GetImageGeneratorDialogNode();
    if (uiNode) {
        // reset RefPtr of mood canvas content node
        viewStackProcessor->SetImageGeneratorDialogNode(nullptr);
    } else {
        return false;
    }
    RefPtr<NG::PipelineContext> pipeline = NG::PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_RETURN(pipeline, false);
    auto root = pipeline->GetRootElement();
    CHECK_NULL_RETURN(root, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    auto shouldDismiss = [weakOverlayMgr = WeakPtr(overlayManager)](int32_t reason) {
        if (reason == static_cast<int32_t>(NG::BindSheetDismissReason::BACK_PRESSED) ||
            reason == static_cast<int32_t>(NG::BindSheetDismissReason::SLIDE_DOWN)) {
                auto overlayManager = weakOverlayMgr.Upgrade();
                if (overlayManager) {
                    overlayManager->DismissSheet();
                }
            }
    };
    auto emptySpringBack = []() {};
    auto style = GENERATOR_STYLE;
    overlayManager->OnBindSheetInner(
        nullptr, uiNode, nullptr, style, nullptr, nullptr, nullptr, std::move(shouldDismiss),
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, std::move(emptySpringBack), root, true);
    // after call onBindSheet, find sheetNode and set callback
    auto parent = uiNode->GetParent();
    while (parent) {
        if (parent->GetTag() == SHEET_PAGE_TAG) {
            break;
        }
        parent = parent->GetParent();
    }
    auto sheetNode = AceType::DynamicCast<NG::FrameNode>(parent);
    CHECK_NULL_RETURN(sheetNode, false);
    overlayManager->UpdateImageGeneratorSheetKey(sheetNode, root->GetId());
    TAG_LOGI(AceLogTag::ACE_SIDEBAR, "create canvas success");
    return true;
}
} // namespace OHOS::Ace::Framework
