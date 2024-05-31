/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_richtext_ffi.h"

#ifndef PREVIEW

#include "cj_lambda.h"
#include "core/components_ng/pattern/web/richtext_model_ng.h"

#include <string>

using namespace OHOS::Ace;

extern "C" {
void FfiOHOSAceFrameworkRichTextCreate(const char* content)
{
    auto string = static_cast<std::string>(content);
    RichTextModel::GetInstance()->Create(string);
}

void FfiOHOSAceFrameworkRichTextOnStart(void(*callback)())
{
    auto lambda = [onStart = CJLambda::Create(callback)](const BaseEventInfo* info) {
        onStart();
    };
    RichTextModel::GetInstance()->SetOnPageStart(lambda);
}

void FfiOHOSAceFrameworkRichTextOnComplete(void(*callback)())
{
    auto lambda = [onComplete = CJLambda::Create(callback)](const BaseEventInfo* info) {
        onComplete();
    };
    RichTextModel::GetInstance()->SetOnPageFinish(lambda);
}
}
#else
extern "C" {
void FfiOHOSAceFrameworkRichTextCreate(const char* content) {}
void FfiOHOSAceFrameworkRichTextOnStart(void(*callback)()) {}
void FfiOHOSAceFrameworkRichTextOnComplete(void(*callback)()) {}
}
#endif