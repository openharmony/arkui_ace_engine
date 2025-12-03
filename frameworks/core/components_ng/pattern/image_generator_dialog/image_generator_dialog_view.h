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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_GENERATOR_DIALOG_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_GENERATOR_DIALOG_VIEW_H

#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

extern const char _binary_imageGeneratorDialog_abc_start[];
extern const char _binary_imageGeneratorDialog_abc_end[];

namespace OHOS::Ace::NG {
class ACE_EXPORT ImageGeneratorDialogView {
public:
    static bool ExecuteImageGeneratorDialogAbc(int32_t instanceId)
    {
        uint8_t* binaryBuff = nullptr;
        int32_t binarySize = 0;
        std::vector<uint8_t> buffer;

        auto filePath = "/system/etc/abc/arkui/imageGeneratorDialog.abc";
        // read abc file
        std::ifstream readFile(filePath, std::ifstream::binary);
        bool isLoadSuccess = false;
        if (readFile.is_open()) {
            readFile.seekg(0, std::ios::end);
            binarySize = static_cast<int32_t>(readFile.tellg());
            readFile.seekg(0, std::ios::beg);
            buffer.resize(binarySize);
            if (readFile.read((char*)buffer.data(), binarySize)) {
                binaryBuff = buffer.data();
                readFile.close();
                isLoadSuccess = true;
            } else {
                TAG_LOGE(AceLogTag::ACE_SIDEBAR, "[imageGenerator] open abc file failed!");
            }
        }
        if (!isLoadSuccess) {
            // use default abc file
            binaryBuff = (uint8_t*)_binary_imageGeneratorDialog_abc_start;
            binarySize = _binary_imageGeneratorDialog_abc_end - _binary_imageGeneratorDialog_abc_start;
        }
        // run abc file
        RefPtr<Framework::JsEngine> jsEngine = nullptr;
        if (instanceId != -1) {
            jsEngine = EngineHelper::GetEngine(instanceId);
        } else {
            jsEngine = EngineHelper::GetCurrentEngine();
        }
        CHECK_NULL_RETURN(jsEngine, false);
        if (!jsEngine->ExecuteJs(binaryBuff, binarySize)) {
            TAG_LOGE(AceLogTag::ACE_SIDEBAR, "[imageGenerator] execute abc file failed!");
            return false;
        }
        return true;
    }

    static bool Create(const std::string& /* should be option here */options, int32_t instanceId)
    {
        auto viewStackProcessor = ViewStackProcessor::GetInstance();
        CHECK_NULL_RETURN(viewStackProcessor, false);
        auto isSuccess = ExecuteImageGeneratorDialogAbc(instanceId);
        if (!isSuccess) {
            return false;
        }
        auto uiNode = viewStackProcessor->GetImageGeneratorDialogNode();
        if (uiNode) {
            // reset RefPtr of mood canvas content node
            viewStackProcessor->SetImageGeneratorDialogNode(nullptr);
        } else {
            return false;
        }
        RefPtr<PipelineContext> pipeline = nullptr;
        if (instanceId != -1) {
            pipeline = PipelineContext::GetContextByContainerId(instanceId);
        } else {
            pipeline = PipelineContext::GetCurrentContext();
        }
        CHECK_NULL_RETURN(pipeline, false);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_RETURN(overlayManager, false);
        SheetStyle style;
        style.showCloseIcon = false;
        style.sheetHeight.height = 560.0_vp;
        style.width = 650.0_vp;
        overlayManager->OnBindSheetInner(nullptr, uiNode, nullptr, style, nullptr, nullptr, nullptr, nullptr,
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, pipeline->GetRootElement(), false);
        return true;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_IMAGE_GENERATOR_DIALOG_VIEW_H
