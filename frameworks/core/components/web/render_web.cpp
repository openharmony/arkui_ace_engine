/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/web/render_web.h"

#include <iomanip>
#include <sstream>

#include "base/log/log.h"
#include "core/components/web/resource/web_resource.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

namespace {

constexpr char NTC_PARAM_ERROR_CODE[] = "errorCode";
constexpr char NTC_PARAM_URL[] = "url";
constexpr char NTC_PARAM_DESCRIPTION[] = "description";

}
void RenderWeb::OnAttachContext()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("OnAttachContext context null");
        return;
    }
    if (delegate_) {
        // web component is displayed in full screen by default.
        drawSize_ = Size(pipelineContext->GetRootWidth(), pipelineContext->GetRootHeight());
        position_ = Offset(0, 0);
        delegate_->CreatePlatformResource(drawSize_, position_, context_);
    }
}

void RenderWeb::Update(const RefPtr<Component>& component)
{
    const RefPtr<WebComponent> web = AceType::DynamicCast<WebComponent>(component);
    if (!web) {
        LOGE("WebComponent is null");
        return;
    }
    if (web->GetOnPageStart()) {
        onPageStartedV2_ = *web->GetOnPageStart();
    }
    if (web->GetOnPageFinish()) {
        onPageFinishedV2_ = *web->GetOnPageFinish();
    }
    if (web->GetOnError()) {
        onPageErrorV2_ = *web->GetOnError();
    }
    if (web->GetOnMessage()) {
        onPageMessageV2_ = *web->GetOnMessage();
    }

    if (!component) {
        return;
    }
    MarkNeedLayout();
}

void RenderWeb::PerformLayout()
{
    if (!NeedLayout()) {
        LOGI("RenderWeb::PerformLayout No Need to Layout");
        return;
    }

    // render web do not support child.
    drawSize_ = Size(GetLayoutParam().GetMaxSize().Width(),
                     (GetLayoutParam().GetMaxSize().Height() == Size::INFINITE_SIZE) ?
                     Size::INFINITE_SIZE :
                     (GetLayoutParam().GetMaxSize().Height()));
    SetLayoutSize(drawSize_);
    SetNeedLayout(false);
    MarkNeedRender();
}

void RenderWeb::OnPageStartedV2(const std::string& param)
{
    std::string paramStart = std::string(R"(")").append(param).append(std::string(R"(")"));
    std::string urlParam =
        std::string(R"("pagestart",{"url":)").append(paramStart.append("},null"));
    if (onPageStartedV2_) {
        onPageStartedV2_(urlParam);
    }
}

void RenderWeb::OnPageFinishedV2(const std::string& param)
{
    std::string paramFinish = std::string(R"(")").append(param).append(std::string(R"(")"));
    std::string urlParam =
        std::string(R"("pagefinish",{"url":)").append(paramFinish.append("},null"));
    if (onPageFinishedV2_) {
        onPageFinishedV2_(urlParam);
    }
}

void RenderWeb::OnPageErrorV2(const std::string& param)
{
    int32_t errorCode = GetIntParam(param, NTC_PARAM_ERROR_CODE);
    std::string url = GetUrlStringParam(param, NTC_PARAM_URL);
    std::string description = GetStringParam(param, NTC_PARAM_DESCRIPTION);

    std::string paramUrl = std::string(R"(")").append(url)
                                              .append(std::string(R"(")"))
                                              .append(",");

    std::string paramErrorCode = std::string(R"(")").append(NTC_PARAM_ERROR_CODE)
                                                    .append(std::string(R"(")"))
                                                    .append(":")
                                                    .append(std::to_string(errorCode))
                                                    .append(",");

    std::string paramDesc = std::string(R"(")").append(NTC_PARAM_DESCRIPTION)
                                                .append(std::string(R"(")"))
                                                .append(":")
                                                .append(std::string(R"(")")
                                                .append(description)
                                                .append(std::string(R"(")")));
    std::string errorParam = std::string(R"("error",{"url":)")
                                        .append((paramUrl + paramErrorCode + paramDesc)
                                        .append("},null"));
    if (onPageErrorV2_) {
        onPageErrorV2_(errorParam);
    }
}

void RenderWeb::OnMessageV2(const std::string& param)
{
    std::string removeQuotes;
    removeQuotes = param;
    removeQuotes.erase(std::remove(removeQuotes.begin(), removeQuotes.end(), '\"'),
                       removeQuotes.end());
    if (onPageMessageV2_) {
        std::string paramMessage = std::string(R"(")").append(removeQuotes).append(std::string(R"(")"));
        std::string messageParam =
                std::string(R"("message",{"message":)").append(paramMessage.append("},null"));
        onPageMessageV2_(messageParam);
    }
}

std::string RenderWeb::GetUrlStringParam(const std::string& param, const std::string& name) const
{
    size_t len = name.length();
    size_t posErrorCode = param.find(NTC_PARAM_ERROR_CODE);
    size_t pos = param.find(name);
    std::string result;

    if (pos != std::string::npos && posErrorCode != std::string::npos) {
        if (((pos + 1 + len) < (param.length() - 1)) && ((posErrorCode - 5) < (param.length() - pos - len))) {
            std::stringstream ss;
            ss << param.substr(pos + 1 + len, posErrorCode - 5);
            ss >> result;
        }
    }
    return result;
}

int32_t RenderWeb::GetIntParam(const std::string& param, const std::string& name) const
{
    size_t len = name.length();
    size_t pos = param.find(name);
    int32_t result = 0;

    if (pos != std::string::npos) {
        if ((pos + 1 + len) < (param.length() - 1)) {
            std::stringstream ss;
            ss << param.substr(pos + 1 + len);
            ss >> result;
        }
    }
    return result;
}

std::string RenderWeb::GetStringParam(const std::string& param, const std::string& name) const
{
    size_t len = name.length();
    size_t pos = param.find(name);
    std::string result;

    if (pos != std::string::npos) {
        if ((pos + 1 + len) < (param.length() - 1)) {
            std::stringstream ss;
            ss << param.substr(pos + 1 + len);
            ss >> result;
        }
    }
    return result;
}
} // namespace OHOS::Ace
