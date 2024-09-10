/*
 * Copyright (c) 2024-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/transparent_node_detector.h"

#include "base/error/error_code.h"
#include "base/log/dump_log.h"
#include "core/common/ace_application_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DELAY_TIME = 2000;
constexpr double TRANSPARENT_NODE_SIZE_THRESHOLD = 0.85;
} // namespace

TransparentNodeDetector& TransparentNodeDetector::GetInstance()
{
    static TransparentNodeDetector instance;
    return instance;
}


void TransparentNodeDetector::PostCheckNodeTransparentTask(const RefPtr<FrameNode>& node, uint8_t detectCount)
{
    if (detectCount > TransparentNodeDetector::MAX_DETECT_COUNT || detectCount == 0) {
        return;
    }
    CHECK_NULL_VOID(node);
    auto pipelineContext = node->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto executor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    auto currentId = Container::CurrentIdSafely();
    auto container = Container::GetContainer(currentId);
    if (!(container && container->IsUIExtensionWindow())) {
        return;
    }
    detectCount--;
    auto task = [weakNode = AceType::WeakClaim(AceType::RawPtr(rootNode)), taskDetectCount = detectCount, currentId]() {
        ContainerScope scope(currentId);
        auto root = weakNode.Upgrade();
        CHECK_NULL_VOID(root);
        auto pipeline = root->GetContext();
        CHECK_NULL_VOID(pipeline);
        if (pipeline->GetRootWidth() * pipeline->GetRootHeight() < SystemProperties::GetDeviceWidth() *
            SystemProperties::GetDeviceHeight() * TRANSPARENT_NODE_SIZE_THRESHOLD || !root->IsContextTransparent()) {
            return;
        }
        if (taskDetectCount > 0) {
            LOGW("try detect again");
            TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(root, taskDetectCount);
            return;
        }
        LOGW("transparent node detected");
        auto window = pipeline->GetWindow();
        CHECK_NULL_VOID(window);
        std::string path = AceApplicationInfo::GetInstance().GetDataFileDirPath() + "/dump_info.log";
        std::unique_ptr<std::ofstream> out = std::make_unique<std::ofstream>(path);
        if (out) {
            DumpLog::GetInstance().Reset();
            DumpLog::GetInstance().SetDumpFile(std::move(out));
            DumpLog::GetInstance().Print(std::string("WindowId: ").append(std::to_string(window->GetWindowId())));
            DumpLog::GetInstance().Print(std::string("WindowName: ").append(window->GetWindowName()));
            root->DumpTree(0, true);
            DumpLog::GetInstance().OutPutDefault();
        }
        window->NotifyExtensionTimeout(ERROR_CODE_UIEXTENSION_TRANSPARENT);
    };
    executor->PostDelayedTask(std::move(task), TaskExecutor::TaskType::UI, DELAY_TIME, "ExtensionTransparentDetector");
}
} // namespace OHOS::Ace::NG

