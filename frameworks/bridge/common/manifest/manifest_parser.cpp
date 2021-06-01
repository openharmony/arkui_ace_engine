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

#include "frameworks/bridge/common/manifest/manifest_parser.h"

namespace OHOS::Ace::Framework {

ManifestParser::ManifestParser()
    : manifestAppInfo_(Referenced::MakeRefPtr<ManifestAppInfo>()),
      manifestRouter_(Referenced::MakeRefPtr<ManifestRouter>()),
      manifestWidget_(Referenced::MakeRefPtr<ManifestWidgetGroup>()),
      manifestWindow_(Referenced::MakeRefPtr<ManifestWindow>())
{}

const RefPtr<ManifestAppInfo>& ManifestParser::GetAppInfo() const
{
    return manifestAppInfo_;
}

const RefPtr<ManifestRouter>& ManifestParser::GetRouter() const
{
    return manifestRouter_;
}

const RefPtr<ManifestWidgetGroup>& ManifestParser::GetWidget() const
{
    return manifestWidget_;
}

const WindowConfig& ManifestParser::GetWindowConfig() const
{
    return manifestWindow_->GetWindowConfig();
}

void ManifestParser::Parse(const std::string& contents)
{
    auto rootJson = JsonUtil::ParseJsonString(contents);
    manifestAppInfo_->AppInfoParse(rootJson);
    manifestRouter_->RouterParse(rootJson);
    manifestWidget_->WidgetParse(rootJson);
    manifestWindow_->WindowParse(rootJson);
}

void ManifestParser::Printer()
{
#ifdef ACE_DEBUG
    LOGD("appinfo:{");
    LOGD("  Icon:%{private}s", manifestAppInfo_->GetIcon().c_str());
    LOGD("  LogLevel:%{public}s", manifestAppInfo_->GetLogLevel().c_str());
    LOGD("  Name:%{public}s", manifestAppInfo_->GetAppName().c_str());
    LOGD("  AppID:%{public}s", manifestAppInfo_->GetAppID().c_str());
    LOGD("  VersionCode:%{public}d", manifestAppInfo_->GetVersionCode());
    LOGD("  VersionName:%{public}s", manifestAppInfo_->GetVersionName().c_str());
    LOGD("  minPlatformVersion:%{public}s", manifestAppInfo_->GetMinPlatformVersion().c_str());
    LOGD("}");

    LOGD("router:{");
    LOGD("  entry:%{private}s", manifestRouter_->GetEntry().c_str());
    LOGD("  pages:{");
    for (const auto& page : manifestRouter_->GetPageList()) {
        LOGD("    %{private}s", page.c_str());
    }
    LOGD("}");

    if (manifestWidget_->GetWidgetNum() > 0) {
        LOGD("widgets:{");
        for (const auto& widget : manifestWidget_->GetWidgetList()) {
            LOGD("  {");
            LOGD("    WidgetName:%{public}s", widget.second->GetWidgetName().c_str());
            LOGD("    WidgetPath:%{public}s", widget.second->GetWidgetPath().c_str());
            LOGD("  }");
        }
        LOGD("}");
    }
    manifestWindow_->PrintInfo();
#endif
}

} // namespace OHOS::Ace::Framework
