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

extern const char _binary_imageGeneratorDialog_abc_start[];
extern const char _binary_imageGeneratorDialog_abc_end[];

namespace OHOS::Ace::Framework {
thread_local bool abcInitialized_ = false;

bool ImageGeneratorDialogView::ExecuteImageGeneratorDialogAbc(int32_t instanceId)
{
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
    auto viewStackProcessor = NG::ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(viewStackProcessor, false);
    auto uiNode = viewStackProcessor->GetImageGeneratorDialogNode();
    if (uiNode) {
        // reset RefPtr of mood canvas content node
        viewStackProcessor->SetImageGeneratorDialogNode(nullptr);
    } else {
        return false;
    }
    RefPtr<NG::PipelineContext> pipeline = nullptr;
    if (instanceId != -1) {
        pipeline = NG::PipelineContext::GetContextByContainerId(instanceId);
    } else {
        pipeline = NG::PipelineContext::GetCurrentContext();
    }
    CHECK_NULL_RETURN(pipeline, false);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, false);
    NG::SheetStyle style;
    style.showCloseIcon = false;
    style.sheetHeight.height = 560.0_vp;
    style.width = 650.0_vp;
    overlayManager->OnBindSheetInner(nullptr, uiNode, nullptr, style, nullptr, nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, pipeline->GetRootElement(), false);
    TAG_LOGI(AceLogTag::ACE_SIDEBAR, "create canvas success");
    return true;
}
} // namespace OHOS::Ace::Framework
