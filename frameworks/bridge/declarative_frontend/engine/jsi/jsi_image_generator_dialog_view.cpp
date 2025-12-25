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

#include <vector>

#include "jsnapi_expo.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t DEFAULT_IGD_MASK_COLOR = 0X33182431;
constexpr char SHEET_PAGE_TAG[] = "SheetPage";

const Dimension DIMENSION_ONE_HUNDRED_PERCENT = Dimension(1, DimensionUnit::PERCENT);
const Dimension DIMENSION_MINIMIZE_SHEET_SIZE = 125.0_vp;
const NG::SheetStyle GENERATOR_STYLE = NG::SheetStyle({ .height = DIMENSION_ONE_HUNDRED_PERCENT }, false, std::nullopt,
    Color::TRANSPARENT, Color(DEFAULT_IGD_MASK_COLOR), DIMENSION_ONE_HUNDRED_PERCENT);
} // namespace

bool ImageGeneratorDialogView::ExecuteImageGeneratorDialogAbc(int32_t instanceId)
{
    thread_local bool abcInitialized_ = false;
    if (abcInitialized_) {
        return true;
    }
    // run abc file
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(EngineHelper::GetEngine(instanceId));
    if (!jsiEngine) {
        TAG_LOGE(AceLogTag::ACE_IMAGE_GENERATION, "[imageGenerator] jsi engine is null!");
        return false;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    CHECK_NULL_RETURN(engineInstance, false);
    auto jsRuntime = engineInstance->GetJsRuntime();
    CHECK_NULL_RETURN(jsRuntime, false);

    const auto* ecmaVM = jsRuntime->GetEcmaVm();
    panda::EscapeLocalScope scope(ecmaVM);

    auto global = panda::JSNApi::GetGlobalObject(ecmaVM);
    panda::Local<panda::FunctionRef> requireNapiFunc(global->Get(ecmaVM, "requireNapi"));
    if (requireNapiFunc->IsUndefined()) {
        TAG_LOGE(AceLogTag::ACE_IMAGE_GENERATION, "[imageGenerator] fail to find requireNapi func!");
        return false;
    }
    std::vector<panda::Local<panda::JSValueRef>> argv = { panda::StringRef::NewFromUtf8(
        ecmaVM, "arkui.imagegeneratordialog") };
    auto result = requireNapiFunc->Call(ecmaVM, global, argv.data(), argv.size());
    bool isFail = result->IsUndefined();
    if (isFail) {
        TAG_LOGE(AceLogTag::ACE_IMAGE_GENERATION, "[imageGenerator] fail to call requireNapi func!");
    } else {
        abcInitialized_ = true;
    }
    if (panda::JSNApi::HasPendingException(ecmaVM)) {
        panda::JSNApi::PrintExceptionInfo(ecmaVM);
        panda::JSNApi::GetAndClearUncaughtException(ecmaVM);
    }
    return !isFail;
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
    overlayManager->OnBindSheetInner(nullptr, uiNode, nullptr, style, nullptr, nullptr, nullptr,
        std::move(shouldDismiss), nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, std::move(emptySpringBack),
        root, true);
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

RefPtr<NG::FrameNode> GetImageGenerateSheetNode(int32_t uniqueId)
{
    auto uiNode = ElementRegister::GetInstance()->GetSpecificItemById<NG::UINode>(uniqueId);
    CHECK_NULL_RETURN(uiNode, nullptr);
    RefPtr<NG::UINode> parent = uiNode->GetParent();
    while (parent) {
        if (parent->GetTag() == SHEET_PAGE_TAG) {
            break;
        }
        parent = parent->GetParent();
    }
    return AceType::DynamicCast<NG::FrameNode>(parent);
}

void ImageGeneratorDialogView::MinimizeDialog(int32_t instanceId, int32_t uniqueId)
{
    if (instanceId < 0 || uniqueId < 0) {
        return;
    }
    RefPtr<NG::PipelineContext> pipeline = NG::PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto sheetNode = GetImageGenerateSheetNode(uniqueId);
    CHECK_NULL_VOID(sheetNode);
    NG::SheetStyle style;
    style.sheetType = NG::SheetType::SHEET_MINIMIZE;
    style.sheetHeight.height = DIMENSION_MINIMIZE_SHEET_SIZE;
    style.width = DIMENSION_MINIMIZE_SHEET_SIZE;
    style.interactive = true;
    style.instanceId = instanceId;
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
    overlayManager->UpdateImageGeneratorSheetScale(
        sheetNode, style, pipeline->GetRootElement()->GetId(), std::move(shouldDismiss), std::move(emptySpringBack));
}

void ImageGeneratorDialogView::RecoverDialog(int32_t instanceId, int32_t uniqueId)
{
    if (instanceId < 0 || uniqueId < 0) {
        return;
    }
    RefPtr<NG::PipelineContext> pipeline = NG::PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto sheetNode = GetImageGenerateSheetNode(uniqueId);
    CHECK_NULL_VOID(sheetNode);
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
    NG::SheetStyle style = GENERATOR_STYLE;
    overlayManager->UpdateImageGeneratorSheetScale(
        sheetNode, style, pipeline->GetRootElement()->GetId(), std::move(shouldDismiss), std::move(emptySpringBack));
}
} // namespace OHOS::Ace::Framework
