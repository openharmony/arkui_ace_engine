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

#include "frameworks/bridge/js_frontend/frontend_delegate.h"

#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/core/components_ng/base/inspector.h"

namespace OHOS::Ace::Framework {
namespace {

const char SLASH = '/';
const char SLASHSTR[] = "/";
const char SUPDIRECTORY[] = "../";

void GetFileInfo(const std::string& fileUri, std::string& fileName, std::string& filePath)
{
    size_t slashPos = fileUri.find_last_of(SLASH);
    if (slashPos == std::string::npos) {
        fileName = fileUri;
    } else {
        fileName = fileUri.substr(slashPos + 1);
        filePath = fileUri.substr(0, slashPos + 1);
    }

    if (StartWith(filePath, SLASHSTR)) {
        filePath = filePath.substr(1);
    }
}

bool ParseWorkerUri(const RefPtr<AssetManager>& assetManager, const std::string& fileUri, std::string& assetsFilePath)
{
    if (!assetManager || fileUri.empty() || (fileUri.length() > PATH_MAX)) {
        return false;
    }

    std::string fileName;
    std::string filePath;
    GetFileInfo(fileUri, fileName, filePath);
    if (StartWith(filePath, SUPDIRECTORY)) {
        filePath = filePath.substr(3); // 3 : offset of filePath
    }
    std::vector<std::string> files;
    assetManager->GetAssetList(filePath, files);

    bool fileExist = false;
    for (const auto& file : files) {
        size_t filePos = file.find_last_of(SLASH);
        if (filePos != std::string::npos) {
            if (file.substr(filePos + 1) == fileName) {
                assetsFilePath = filePath + fileName;
                fileExist = true;
                break;
            }
        }
    }
    return fileExist;
}

bool ParseFileUri(const RefPtr<AssetManager>& assetManager, const std::string& fileUri, std::string& assetsFilePath)
{
    if (!assetManager || fileUri.empty() || (fileUri.length() > PATH_MAX)) {
        return false;
    }

    std::string fileName;
    std::string filePath;
    GetFileInfo(fileUri, fileName, filePath);
    std::vector<std::string> files;
    assetManager->GetAssetList(filePath, files);

    bool fileExist = false;
    for (const auto& file : files) {
        bool startWithSlash = StartWith(file, SLASHSTR);
        if ((startWithSlash && (file.substr(1) == fileName)) || (!startWithSlash && (file == fileName))) {
            assetsFilePath = filePath + file;
            fileExist = true;
            break;
        }
    }

    return fileExist;
}

} // namespace

template<typename T>
bool FrontendDelegate::GetResourceData(const std::string& fileUri, T& content)
{
    std::string targetFilePath;
    if (!ParseFileUri(assetManager_, fileUri, targetFilePath)) {
        LOGE("GetResourceData parse file uri failed.");
        return false;
    }
    if (!GetAssetContentAllowEmpty(assetManager_, targetFilePath, content)) {
        LOGE("GetResourceData GetAssetContent failed.");
        return false;
    }

    return true;
}

void FrontendDelegate::GetRectangleById(const std::string& key, NG::Rectangle& rectangle)
{
    NG::Inspector::GetRectangleById(key, rectangle);
}

void FrontendDelegate::ResetFocus()
{
    TAG_LOGI(AceLogTag::ACE_FOCUS, "user lost focus to view root scope");
    NG::FocusHub::LostFocusToViewRoot();
}

bool FrontendDelegate::RequestFocus(const std::string& value, bool isSyncRequest)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->RequestFocus(value, isSyncRequest);
}

void FrontendDelegate::SetRequestFocusCallback(
    std::function<void(NG::RequestFocusResult result)> callback)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetRequestFocusCallback(callback);
}

void FrontendDelegate::ResetRequestFocusCallback()
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->ResetRequestFocusCallback();
}

bool FrontendDelegate::Activate(bool isActive, bool autoInactive)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->SetIsFocusActive(isActive, NG::FocusActiveReason::USE_API, autoInactive);
}

void FrontendDelegate::SetAutoFocusTransfer(bool isAutoFocusTransfer)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetIsAutoFocusTransfer(isAutoFocusTransfer);
}

void FrontendDelegate::SetKeyProcessingMode(int32_t keyProcessingMode)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetKeyProcessingMode(static_cast<NG::KeyProcessingMode>(keyProcessingMode));
}

bool FrontendDelegate::ConfigWindowMask(bool enable)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    return NG::ContainerModalView::ConfigCustomWindowMask(pipeline, enable);
}

template<typename T>
bool FrontendDelegate::GetResourceData(const std::string& fileUri, T& content, std::string& ami)
{
    std::string targetFilePath;
    if (!ParseWorkerUri(assetManager_, fileUri, targetFilePath)) {
        LOGE("GetResourceData parse file uri failed.");
        return false;
    }
    ami = assetManager_->GetAssetPath(targetFilePath, true) + targetFilePath;
    LOGI("GetResourceData ami: %{private}s.", ami.c_str());
    if (!GetAssetContentAllowEmpty(assetManager_, targetFilePath, content)) {
        LOGE("GetResourceData GetAssetContent failed.");
        return false;
    }
    return true;
}

template<typename T>
bool FrontendDelegate::GetResourceData(const std::string& fileUri, const RefPtr<AssetManager>& assetManager, T& content)
{
    std::string targetFilePath;
    if (!ParseFileUri(assetManager, fileUri, targetFilePath)) {
        LOGE("GetResourceData parse file uri failed.");
        return false;
    }
    if (!GetAssetContentAllowEmpty(assetManager, targetFilePath, content)) {
        LOGE("GetResourceData GetAssetContent failed.");
        return false;
    }

    return true;
}

template bool FrontendDelegate::GetResourceData(const std::string& fileUri, std::string& content);
template bool FrontendDelegate::GetResourceData(const std::string& fileUri, std::vector<uint8_t>& content);
template bool FrontendDelegate::GetResourceData(
    const std::string& fileUri, std::vector<uint8_t>& content, std::string& ami);
template bool FrontendDelegate::GetResourceData(
    const std::string& fileUri, const RefPtr<AssetManager>& assetManager, std::vector<uint8_t>& content);

} // namespace OHOS::Ace::Framework
