/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include "core/common/ai/text_translation_adapter.h"

#include "core/common/ai/text_translation_mgr.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {

void TextTranslationAdapter::StartAITextTranslationTask(const std::string& translateText, const std::string& rectStr)
{
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(context);

    auto backgroundExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::BACKGROUND);
    backgroundExecutor.PostTask(
        [translateText, rectStr] {
            TAG_LOGI(AceLogTag::ACE_TEXT, "TextTranslationAdapter::StartAITextTranslationTask, start AI text \
                translation");
            TextTranslationMgr::GetInstance().PullUpTranslationPanel(translateText, rectStr);
        },
        "ArkUITextInitTextTranslation");
}

} // namespace OHOS::Ace
