/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/plugin/plugin_element.h"

#include "flutter/lib/ui/ui_dart_state.h"
#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif // OS_ACCOUNT_EXISTS
#include "core/common/plugin_manager.h"
#include "frameworks/base/utils/string_utils.h"
#include "frameworks/core/components/plugin/plugin_component.h"
#include "frameworks/core/components/plugin/plugin_component_manager.h"
#include "frameworks/core/components/plugin/render_plugin.h"
#include "frameworks/core/components/plugin/resource/plugin_manager_delegate.h"

namespace OHOS::Ace {
namespace {
#ifndef OS_ACCOUNT_EXISTS
constexpr int32_t DEFAULT_OS_ACCOUNT_ID = 0; // 0 is the default id when there is no os_account part
#endif // OS_ACCOUNT_EXISTS

ErrCode GetActiveAccountIds(std::vector<int32_t>& userIds)
{
    userIds.clear();
#ifdef OS_ACCOUNT_EXISTS
    return AccountSA::OsAccountManager::QueryActiveOsAccountIds(userIds);
#else // OS_ACCOUNT_EXISTS
    LOGE("os account part not exists, use default id.");
    userIds.push_back(DEFAULT_OS_ACCOUNT_ID);
    return ERR_OK;
#endif // OS_ACCOUNT_EXISTS
}
} // namespace

PluginElement::~PluginElement()
{
    PluginManager::GetInstance().RemovePluginParentContainer(pluginSubContainerId_);
    pluginManagerBridge_.Reset();
    pluginSubContainer_->Destroy();
    pluginSubContainer_.Reset();
}

void PluginElement::Update()
{
    auto plugin = AceType::DynamicCast<PluginComponent>(component_);
    if (!plugin) {
        LOGE("could not get plugin component for update");
        return;
    }

    auto info = plugin->GetPluginRequestInfo();
    if (info.bundleName != pluginInfo_.bundleName || info.abilityName != pluginInfo_.abilityName ||
        info.moduleName != pluginInfo_.moduleName || info.pluginName != pluginInfo_.pluginName ||
        info.dimension != pluginInfo_.dimension) {
        pluginInfo_ = info;
    } else {
        // for update plugin component
        if (pluginInfo_.allowUpdate != info.allowUpdate) {
            pluginInfo_.allowUpdate = info.allowUpdate;
            if (pluginSubContainer_) {
                pluginSubContainer_->SetAllowUpdate(pluginInfo_.allowUpdate);
            }
        }

        if (pluginInfo_.width != info.width || pluginInfo_.height != info.height) {
            pluginInfo_.width = info.width;
            pluginInfo_.height = info.height;
            GetRenderNode()->Update(component_);
            if (pluginSubContainer_) {
                pluginSubContainer_->SetPluginComponent(component_);
                pluginSubContainer_->UpdateRootElementSize();
                pluginSubContainer_->UpdateSurfaceSize();
            }
        }
        if (pluginSubContainer_) {
            pluginSubContainer_->UpdatePlugin(plugin->GetData());
        }
        return;
    }

    GetRenderNode()->Update(component_);
    RunPluginContainer();
    if (pluginManagerBridge_) {
        pluginManagerBridge_->AddPlugin(GetContext(), info);
    }

    InitEvent(plugin);
}

void PluginElement::PerformBuild()
{
    if (!pluginSubContainer_) {
        return;
    }
    pluginSubContainer_->SetPluginElement(AceType::WeakClaim(this));
}

void PluginElement::InitEvent(const RefPtr<PluginComponent>& component)
{
    if (!component->GetOnCompleteEventId().IsEmpty()) {
        onCompleteEvent_ = AceAsyncEvent<void(const std::string&)>::Create(component->GetOnCompleteEventId(), context_);
    }

    if (!component->GetOnErrorEvent().IsEmpty()) {
        onErrorEvent_ = AceAsyncEvent<void(const std::string&)>::Create(component->GetOnErrorEvent(), context_);
    }
}

void PluginElement::HandleOnCompleteEvent() const
{
    if (!onCompleteEvent_) {
        LOGE("could not find available event handle");
        return;
    }
    onCompleteEvent_("");
}

void PluginElement::HandleOnErrorEvent(const std::string code, const std::string msg) const
{
    if (!onErrorEvent_) {
        LOGE("could not find available event handle");
        return;
    }

    auto json = JsonUtil::Create(true);
    json->Put("errcode", code.c_str());
    json->Put("msg", msg.c_str());
    onErrorEvent_(json->ToString());
}

void PluginElement::Prepare(const WeakPtr<Element>& parent)
{
    RenderElement::Prepare(parent);

    if (!pluginManagerBridge_) {
        pluginManagerBridge_ =
            AceType::MakeRefPtr<PluginManagerDelegate>(GetContext());
        pluginManagerBridge_->AddPluginCompleteCallback(
            [weak = WeakClaim(this)] () {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([weak] {
                auto plugin = weak.Upgrade();
                if (plugin) {
                    plugin->HandleOnCompleteEvent();
                }
            });
        });
        pluginManagerBridge_->AddPluginUpdateCallback(
            [weak = WeakClaim(this)] (int64_t id, std::string data) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([id, data, weak] {
                auto plugin = weak.Upgrade();
                if (plugin) {
                    plugin->GetPluginSubContainer()->UpdatePlugin(data);
                }
            });
        });
        pluginManagerBridge_->AddPluginErrorCallback(
            [weak = WeakClaim(this)](std::string code, std::string msg) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask([code, msg, weak] {
                auto plugin = weak.Upgrade();
                if (plugin) {
                    plugin->HandleOnErrorEvent(code, msg);
                }

                auto render = plugin->GetRenderNode();
                if (!render) {
                    LOGE("remove plugin from screen fail, due to could not get plugin render node");
                    return;
                }
                auto renderPlugin = AceType::DynamicCast<RenderPlugin>(render);
                if (renderPlugin) {
                    renderPlugin->RemoveChildren();
                }
            });
        });
    }
}

void PluginElement::OnActionEvent(const std::string& action) const
{
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

    if (type == "router") {
#ifdef OHOS_STANDARD_SYSTEM
        auto context = GetContext().Upgrade();
        if (context) {
            LOGI("send action evetn to ability to process");
            context->OnActionEvent(action);
        }
#endif
        return;
    }

    if (pluginManagerBridge_) {
        pluginManagerBridge_->OnActionEvent(action);
    }
}

void PluginElement::RunPluginContainer()
{
    if (pluginSubContainer_) {
        pluginSubContainer_->Destroy();
        pluginSubContainer_.Reset();
    }

    pluginSubContainer_ = AceType::MakeRefPtr<PluginSubContainer>(GetContext().Upgrade());
    if (!pluginSubContainer_) {
        LOGE("create plugin container fail.");
        return;
    }
    auto plugin = AceType::DynamicCast<PluginComponent>(component_);
    if (!plugin) {
        LOGE("plugin component is null when try adding nonmatched container to plugin manager.");
        return;
    }

    pluginSubContainerId_ = PluginManager::GetInstance().GetPluginSubContainerId();
    PluginManager::GetInstance().AddPluginSubContainer(pluginSubContainerId_, pluginSubContainer_);
    PluginManager::GetInstance().AddPluginParentContainer(pluginSubContainerId_, Container::CurrentId());
    flutter::UIDartState::Current()->AddPluginParentContainer(pluginSubContainerId_, Container::CurrentId());
    pluginSubContainer_->SetInstanceId(pluginSubContainerId_);
    pluginSubContainer_->Initialize();
    pluginSubContainer_->SetPluginComponent(component_);

    auto weak = WeakClaim(this);
    auto element = weak.Upgrade();
    auto uiTaskExecutor = SingleTaskExecutor::Make(
        element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    auto pluginNode = AceType::DynamicCast<RenderPlugin>(renderNode_);
    if (!pluginNode) {
        LOGE("plugin node is null.");
        return;
    }
    pluginNode->SetPluginSubContainer(pluginSubContainer_);

    uiTaskExecutor.PostTask([this, weak, plugin] {
        RunPluginTask(weak, plugin);
    });
}

RefPtr<RenderNode> PluginElement::CreateRenderNode()
{
    return RenderPlugin::Create();
}

std::string PluginElement::GetPackagePath(const WeakPtr<PluginElement>& weak, RequestPluginInfo& info) const
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

std::string PluginElement::GetPackagePathByAbsolutePath(
    const WeakPtr<PluginElement>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    auto pluginElement = weak.Upgrade();
    if (!pluginElement) {
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

std::string PluginElement::GetPackagePathByWant(const WeakPtr<PluginElement>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    auto pluginElement = weak.Upgrade();
    if (!pluginElement) {
        LOGE("pluginElement is nullptr.");
        return packagePathStr;
    }

    std::vector<std::string> strList;
    pluginElement->SplitString(info.bundleName, '/', strList);

    std::vector<int32_t> userIds;
    ErrCode errCode = GetActiveAccountIds(userIds);
    if (errCode != ERR_OK) {
        LOGE("Query Active OsAccountIds failed!");
        pluginElement->HandleOnErrorEvent("1", "Query Active OsAccountIds failed!");
        return packagePathStr;
    }
    GetModuleNameByWant(weak, info);
    packagePathStr = GerPackagePathByBms(weak, info, strList, userIds);

    return packagePathStr;
}

void PluginElement::GetModuleNameByWant(const WeakPtr<PluginElement>& weak, RequestPluginInfo& info) const
{
    auto pluginElement = weak.Upgrade();
    if (!pluginElement) {
        LOGE("pluginElement is nullptr.");
        return;
    }

    std::vector<std::string> strList;
    pluginElement->SplitString(info.pluginName, '&', strList);
    if (strList.empty()) {
        LOGE("Template source is empty.");
        pluginElement->HandleOnErrorEvent("1", "Template source is empty.");
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

void PluginElement::SplitString(const std::string& str, char tag, std::vector<std::string>& strList)
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

void PluginElement::RunPluginTask(const WeakPtr<PluginElement>& weak, const RefPtr<PluginComponent>& plugin)
{
    auto pluginElement = weak.Upgrade();
    if (!pluginElement) {
        LOGE("pluginElement is nullptr.");
        return;
    }

    auto container = pluginElement->GetPluginSubContainer();
    if (!container) {
        LOGE("PluginSubContainer is nullptr.");
        return;
    }

    RequestPluginInfo info = plugin->GetPluginRequestInfo();
    auto packagePathStr = pluginElement->GetPackagePath(weak, info);
    if (packagePathStr.empty()) {
        LOGE("package path is empty.");
        pluginElement->HandleOnErrorEvent("1", "package path is empty.");
        return;
    }
    container->RunPlugin(packagePathStr, info.moduleName, info.source, info.moduleResPath, plugin->GetData());
}

std::string PluginElement::GerPackagePathByBms(
    const WeakPtr<PluginElement>& weak, RequestPluginInfo& info,
    const std::vector<std::string>& strList, const std::vector<int32_t>& userIds) const
{
    std::string packagePathStr;
    auto pluginElement = weak.Upgrade();
    if (!pluginElement) {
        LOGE("pluginElement is nullptr.");
        return packagePathStr;
    }
    auto bms = PluginComponentManager::GetInstance()->GetBundleManager();
    if (!bms) {
        LOGE("Bms bundleManager is nullptr.");
        pluginElement->HandleOnErrorEvent("1", "Bms bundleManager is nullptr.");
        return packagePathStr;
    }

    if (strList.empty()) {
        LOGE("App bundleName or abilityName is empty.");
        pluginElement->HandleOnErrorEvent("1", "App bundleName is empty.");
        return packagePathStr;
    }
    if (strList.size() == 1) {
        AppExecFwk::BundleInfo bundleInfo;
        bool ret = bms->GetBundleInfo(strList[0], AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo,
            userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID);
        if (!ret) {
            LOGE("Bms get bundleName failed!");
            pluginElement->HandleOnErrorEvent("1", "Bms get bundleName failed!");
            return packagePathStr;
        }
        if (bundleInfo.moduleResPaths.size() == 1) {
            info.moduleResPath = bundleInfo.moduleResPaths[0];
        } else {
            LOGE("Bms moduleResPaths is empty.");
            pluginElement->HandleOnErrorEvent("1", "Bms moduleResPaths is empty.");
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
            pluginElement->HandleOnErrorEvent("1", "Bms get bundleName failed!");
            return packagePathStr;
        }
        packagePathStr = abilityInfo.applicationInfo.codePath + "/" + abilityInfo.package + "/";
        info.moduleResPath = abilityInfo.resourcePath;
    }
    return packagePathStr;
}
} // namespace OHOS::Ace
