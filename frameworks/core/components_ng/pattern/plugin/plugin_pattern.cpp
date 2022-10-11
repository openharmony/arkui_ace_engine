/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/plugin/plugin_pattern.h"

#include <string>

#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif // OS_ACCOUNT_EXISTS
#include "flutter/lib/ui/ui_dart_state.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/common/plugin_manager.h"
#include "core/components/plugin/plugin_component_manager.h"
#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/render_plugin.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#include "core/components_ng/pattern/plugin/plugin_event_hub.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {

namespace {
#ifndef OS_ACCOUNT_EXISTS
constexpr int32_t DEFAULT_OS_ACCOUNT_ID = 0; // 0 is the default id when there is no os_account part
#endif // OS_ACCOUNT_EXISTS

ErrCode GetActiveAccountIds(std::vector<int32_t>& userIds)
{
    userIds.clear();
#ifdef OS_ACCOUNT_EXISTS
    return AccountSA::OsAccountManager::QueryActiveOsAccountIds(userIds);
#else  // OS_ACCOUNT_EXISTS
    LOGE("os account part not exists, use default id.");
    userIds.push_back(DEFAULT_OS_ACCOUNT_ID);
    return ERR_OK;
#endif // OS_ACCOUNT_EXISTS
}
} // namespace

void PluginPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    InitPluginManagerDelegate();
}

bool PluginPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    auto size = dirty->GetGeometryNode()->GetFrameSize();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto info = layoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    info.width = Dimension(size.Width());
    info.height = Dimension(size.Height());
    layoutProperty->UpdateRequestPluginInfo(info);

    if (info.bundleName != pluginInfo_.bundleName || info.abilityName != pluginInfo_.abilityName ||
        info.moduleName != pluginInfo_.moduleName || info.pluginName != pluginInfo_.pluginName ||
        info.dimension != pluginInfo_.dimension) {
        pluginInfo_ = info;
        LOGI(" pluginInfo_ = info; pluginInfo_.width:: %{public}lf, pluginInfo_.height:: %{public}lf",
            pluginInfo_.width.Value(), pluginInfo_.height.Value());
    } else {
        // for update pluguin component
        if (pluginInfo_.allowUpdate != info.allowUpdate) {
            pluginInfo_.allowUpdate = info.allowUpdate;
            if (pluginSubContainer_) {
                pluginSubContainer_->SetAllowUpdate(pluginInfo_.allowUpdate);
            }
        }

        if (pluginInfo_.width != info.width || pluginInfo_.height != info.height) {
            pluginInfo_.width = info.width;
            pluginInfo_.height = info.height;
            if (pluginSubContainer_) {
                pluginSubContainer_->SetPluginPattern(WeakClaim(this));
                pluginSubContainer_->UpdateRootElementSize();
                pluginSubContainer_->UpdateSurfaceSize();
            }
        }
        return false;
    }
    CreatePluginSubContainer();
    if (pluginManagerBridge_) {
        pluginManagerBridge_->AddPlugin(host->GetContext(), info);
    }
    return false;
}

void PluginPattern::InitPluginManagerDelegate()
{
    if (pluginManagerBridge_) {
        LOGD("PluginInfo manager bridge is already initialized.");
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    pluginManagerBridge_ = AceType::MakeRefPtr<PluginManagerDelegate>(context);
    int32_t instanceID = context->GetInstanceId();
    pluginManagerBridge_->AddPluginCompleteCallback([weak = WeakClaim(this), instanceID]() {
        ContainerScope scope(instanceID);
        auto plugin = weak.Upgrade();
        CHECK_NULL_VOID(plugin);
        auto host = plugin->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([weak, instanceID] {
            ContainerScope scope(instanceID);
            auto plugin = weak.Upgrade();
            CHECK_NULL_VOID(plugin);
            plugin->FireOnCompleteEvent();
        });
    });
    pluginManagerBridge_->AddPluginUpdateCallback([weak = WeakClaim(this), instanceID](int64_t id, std::string data) {
        ContainerScope scope(instanceID);
        auto plugin = weak.Upgrade();
        CHECK_NULL_VOID(plugin);
        auto host = plugin->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([id, data, weak] {
            auto plugin = weak.Upgrade();
            CHECK_NULL_VOID(plugin);
            if (plugin) {
                plugin->GetPluginSubContainer()->UpdatePlugin(data);
            }
        });
    });
    pluginManagerBridge_->AddPluginErrorCallback(
        [weak = WeakClaim(this), instanceID](std::string code, std::string msg) {
            ContainerScope scope(instanceID);
            auto plugin = weak.Upgrade();
            CHECK_NULL_VOID(plugin);
            auto host = plugin->GetHost();
            CHECK_NULL_VOID(host);
            auto uiTaskExecutor =
                SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([code, msg, weak, instanceID] {
                ContainerScope scope(instanceID);
                auto plugin = weak.Upgrade();
                CHECK_NULL_VOID(plugin);
                plugin->FireOnErrorEvent(code, msg);
            });
        });
}

void PluginPattern::CreatePluginSubContainer()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto layoutProperty = host->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (pluginSubContainer_) {
        pluginSubContainer_->Destroy();
        pluginSubContainer_.Reset();
    }
    auto pluginSubContainerId_ = PluginManager::GetInstance().GetPluginSubContainerId();
    pluginSubContainer_ = AceType::MakeRefPtr<PluginSubContainer>(context, pluginSubContainerId_);
    CHECK_NULL_VOID(pluginSubContainer_);

    PluginManager::GetInstance().AddPluginSubContainer(pluginSubContainerId_, pluginSubContainer_);
    PluginManager::GetInstance().AddPluginParentContainer(pluginSubContainerId_, Container::CurrentId());
    flutter::UIDartState::Current()->AddPluginParentContainer(pluginSubContainerId_, Container::CurrentId());
    pluginSubContainer_->Initialize();
    pluginSubContainer_->SetPluginPattern(WeakClaim(this));
    pluginSubContainer_->SetPluginNode(GetHost());
    auto weak = WeakClaim(this);
    auto pattern = weak.Upgrade();
    auto host_ = pattern->GetHost();
    CHECK_NULL_VOID(host_);
    auto uiTaskExecutor = SingleTaskExecutor::Make(host_->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    int32_t instanceID = context->GetInstanceId();
    uiTaskExecutor.PostTask([this, weak, instanceID] {
        ContainerScope scope(instanceID);
        auto pluginPattern = weak.Upgrade();
        CHECK_NULL_VOID(pluginPattern);
        auto pluginSubContainer = pluginPattern->GetPluginSubContainer();
        RequestPluginInfo info = pluginPattern->GetPluginRequestInfo();
        CHECK_NULL_VOID(pluginSubContainer);
        auto packagePathStr = pluginPattern->GetPackagePath(weak, info);
        pluginSubContainer_->RunPlugin(
            packagePathStr, info.moduleName, info.source, info.moduleResPath, pluginPattern->GetData());
    });
}

std::unique_ptr<DrawDelegate> PluginPattern::GetDrawDelegate()
{
    auto drawDelegate = std::make_unique<DrawDelegate>();
    drawDelegate->SetDrawRSFrameCallback(
        [weak = WeakClaim(this)](std::shared_ptr<RSNode>& node, const Rect& /* dirty */) {
            auto plugin = weak.Upgrade();
            CHECK_NULL_VOID(plugin);
            auto host = plugin->GetHost();
            CHECK_NULL_VOID(host);
            auto context = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
            CHECK_NULL_VOID(context);
            auto rsNode = context->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            if (node) {
                node->SetBackgroundColor(Color::TRANSPARENT.GetValue());
            }
            rsNode->AddChild(node, -1);
            host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
        });
    return drawDelegate;
}

void PluginPattern::FireOnCompleteEvent() const
{
    LOGI("FireOnCompleteEvent");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto json = JsonUtil::Create(true);
    eventHub->FireOnComplete(json->ToString());
}

void PluginPattern::FireOnErrorEvent(const std::string& code, const std::string& msg) const
{
    LOGI("FireOnErrorEvent code: %{public}s, msg: %{public}s", code.c_str(), msg.c_str());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto json = JsonUtil::Create(true);
    json->Put("errcode", code.c_str());
    json->Put("msg", msg.c_str());
    eventHub->FireOnError(json->ToString());
}

void PluginPattern::OnActionEvent(const std::string& action) const
{
    LOGI("OnActionEvent action: %{public}s", action.c_str());
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        LOGE("get event action failed");
        return;
    }
    auto actionType = eventAction->GetValue("action");
    if (!actionType->IsValid()) {
        LOGE("get event key failed");
        return;
    }

    auto type = actionType->GetString();
    if (type != "router" && type != "message") {
        LOGE("undefined event type");
        return;
    }

    if (pluginManagerBridge_) {
        pluginManagerBridge_->OnActionEvent(action);
    }
}

bool PluginPattern::ISAllowUpdate() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto property = host->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_RETURN(property, true);
    auto pluginInfo = property->GetRequestPluginInfo();
    CHECK_NULL_RETURN(property, true);
    return pluginInfo->allowUpdate;
}

void PluginPattern::SplitString(const std::string& str, char tag, std::vector<std::string>& strList) const
{
    std::string subStr;
    for (size_t i = 0; i < str.length(); i++) {
        if (tag == str[i]) {
            if (!subStr.empty()) {
                strList.push_back(subStr);
                subStr.clear();
            }
        } else {
            subStr.push_back(str[i]);
        }
    }
    if (!subStr.empty()) {
        strList.push_back(subStr);
    }
}

std::string PluginPattern::GetPackagePath(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    size_t pos = info.pluginName.rfind(".js");
    if (info.pluginName.front() == '/' && pos != std::string::npos) {
        packagePathStr = GetPackagePathByAbsolutePath(weak, info);
    } else {
        packagePathStr = GetPackagePathByWant(weak, info);
    }
    return packagePathStr;
}

std::string PluginPattern::GetPackagePathByWant(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    auto pluginPattern = weak.Upgrade();
    if (!pluginPattern) {
        LOGE("pluginPattern is nullptr.");
        return packagePathStr;
    }

    std::vector<std::string> strList;
    pluginPattern->SplitString(info.bundleName, '/', strList);

    std::vector<int32_t> userIds;
    ErrCode errCode = GetActiveAccountIds(userIds);
    if (errCode != ERR_OK) {
        LOGE("Query Active OsAccountIds failed!");
        pluginPattern->FireOnErrorEvent("1", "Query Active OsAccountIds failed!");
        return packagePathStr;
    }
    GetModuleNameByWant(weak, info);
    packagePathStr = GerPackagePathByBms(weak, info, strList, userIds);

    return packagePathStr;
}
std::string PluginPattern::GetPackagePathByAbsolutePath(
    const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    auto pluginPattern = weak.Upgrade();
    if (!pluginPattern) {
        return packagePathStr;
    }
    std::string assets = "assets/js/";
    size_t posAssets = info.pluginName.rfind(assets);
    if (posAssets != std::string::npos) {
        packagePathStr = info.pluginName.substr(0, posAssets);
        size_t posModule = info.pluginName.find("/", posAssets + assets.size());
        if (posModule != std::string::npos) {
            info.moduleName =
                info.pluginName.substr(posAssets + assets.size(), posModule - (posAssets + assets.size()));
            info.source = info.pluginName.substr(posModule);
        } else {
            info.moduleName = "/";
            info.source = info.pluginName.substr(posAssets + assets.size());
        }
    } else {
        size_t pos = info.pluginName.rfind("/");
        packagePathStr = info.pluginName.substr(0, pos + 1);
        info.source = info.pluginName.substr(pos + 1);
        info.moduleName = "/";
    }
    return packagePathStr;
}

void PluginPattern::GetModuleNameByWant(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    auto pluginPattern = weak.Upgrade();
    if (!pluginPattern) {
        LOGE("pluginPattern is nullptr.");
        pluginPattern->FireOnErrorEvent("1", "pluginPattern is nullptr.");
        return;
    }

    std::vector<std::string> strList;
    pluginPattern->SplitString(info.pluginName, '&', strList);
    if (strList.empty()) {
        LOGE("Template source is empty.");
        pluginPattern->FireOnErrorEvent("1", "Template source is empty.");
        return;
    }
    if (strList.size() == 1) {
        if (info.pluginName.rfind(".js") != std::string::npos) {
            info.moduleName = "default";
            info.source = info.pluginName;
        } else {
            info.moduleName = info.pluginName;
        }
    } else {
        if (strList[0].rfind(".js") != std::string::npos) {
            info.source = strList[1];
        }
        info.moduleName = strList[0];
    }
}

std::string PluginPattern::GerPackagePathByBms(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info,
    const std::vector<std::string>& strList, const std::vector<int32_t>& userIds) const
{
    std::string packagePathStr;
    auto pluginPattern = weak.Upgrade();
    if (!pluginPattern) {
        LOGE("pluginPattern is nullptr.");
        return packagePathStr;
    }
    auto bms = PluginComponentManager::GetInstance()->GetBundleManager();
    if (!bms) {
        LOGE("Bms bundleManager is nullptr.");
        pluginPattern->FireOnErrorEvent("1", "Bms bundleManager is nullptr.");
        return packagePathStr;
    }

    if (strList.empty()) {
        LOGE("App bundleName or abilityName is empty.");
        pluginPattern->FireOnErrorEvent("1", "App bundleName is empty.");
        return packagePathStr;
    }
    if (strList.size() == 1) {
        AppExecFwk::BundleInfo bundleInfo;
        bool ret = bms->GetBundleInfo(strList[0], AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo,
            userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID);
        if (!ret) {
            LOGE("Bms get bundleName failed!");
            pluginPattern->FireOnErrorEvent("1", "Bms get bundleName failed!");
            return packagePathStr;
        }
        if (bundleInfo.moduleResPaths.size() == 1) {
            info.moduleResPath = bundleInfo.moduleResPaths[0];
        } else {
            LOGE("Bms moduleResPaths is empty.");
            pluginPattern->FireOnErrorEvent("1", "Bms moduleResPaths is empty.");
            return packagePathStr;
        }
        packagePathStr = bundleInfo.applicationInfo.entryDir + "/";
    } else {
        AAFwk::Want want;
        AppExecFwk::AbilityInfo abilityInfo;
        AppExecFwk::ElementName element("", strList[0], strList[1]);
        want.SetElement(element);
        bool ret = bms->QueryAbilityInfo(want, AppExecFwk::AbilityInfoFlag::GET_ABILITY_INFO_DEFAULT,
            userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID, abilityInfo);
        if (!ret) {
            LOGE("Bms get abilityInfo failed!");
            pluginPattern->FireOnErrorEvent("1", "Bms get bundleName failed!");
            return packagePathStr;
        }
        packagePathStr = abilityInfo.applicationInfo.codePath + "/" + abilityInfo.package + "/";
        info.moduleResPath = abilityInfo.resourcePath;
    }
    return packagePathStr;
}

const RefPtr<PluginSubContainer>& PluginPattern::GetPluginSubContainer() const
{
    return pluginSubContainer_;
};
} // namespace OHOS::Ace::NG
