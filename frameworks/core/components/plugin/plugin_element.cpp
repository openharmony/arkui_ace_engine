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

#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif // OS_ACCOUNT_EXISTS
#include "base/utils/string_utils.h"
#include "core/common/plugin_manager.h"
#include "core/components/plugin/plugin_component.h"
#include "core/components/plugin/plugin_component_manager.h"
#include "core/components/plugin/render_plugin.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"

namespace OHOS::Ace {
namespace {
#ifndef OS_ACCOUNT_EXISTS
constexpr int32_t DEFAULT_OS_ACCOUNT_ID = 0; // 0 is the default id when there is no os_account part
#endif                                       // OS_ACCOUNT_EXISTS

ErrCode GetActiveAccountIds(std::vector<int32_t>& userIds)
{
    userIds.clear();
#ifdef OS_ACCOUNT_EXISTS
    return AccountSA::OsAccountManager::QueryActiveOsAccountIds(userIds);
#else  // OS_ACCOUNT_EXISTS
    TAG_LOGW(AceLogTag::ACE_PLUGIN_COMPONENT, "os account part not exists, use default id.");
    userIds.push_back(DEFAULT_OS_ACCOUNT_ID);
    return ERR_OK;
#endif // OS_ACCOUNT_EXISTS
}
} // namespace

PluginElement::~PluginElement()
{
    PluginManager::GetInstance().RemovePluginSubContainer(pluginSubContainerId_);
    PluginManager::GetInstance().RemovePluginParentContainer(pluginSubContainerId_);
    pluginManagerBridge_.Reset();
    if (pluginSubContainer_) {
        pluginSubContainer_->Destroy();
        pluginSubContainer_.Reset();
    }
}

void PluginElement::Update()
{
    auto plugin = AceType::DynamicCast<PluginComponent>(component_);
    CHECK_NULL_VOID(plugin);

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
    loadFailState_ = false;
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
    if (loadFailState_) {
        return;
    }
    if (!onCompleteEvent_) {
        return;
    }
    onCompleteEvent_("");
}

void PluginElement::HandleOnErrorEvent(const std::string& code, const std::string& msg)
{
    loadFailState_ = true;
    if (!onErrorEvent_) {
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
        pluginManagerBridge_ = AceType::MakeRefPtr<PluginManagerDelegate>(GetContext());
        pluginManagerBridge_->AddPluginCompleteCallback([weak = WeakClaim(this)]() {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [weak] {
                    auto plugin = weak.Upgrade();
                    if (plugin) {
                        plugin->HandleOnCompleteEvent();
                    }
                }, "ArkUIPluginCompleteCallback");
        });
        pluginManagerBridge_->AddPluginUpdateCallback([weak = WeakClaim(this)](int64_t id, std::string data) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [data, weak] {
                    auto plugin = weak.Upgrade();
                    if (plugin) {
                        plugin->GetPluginSubContainer()->UpdatePlugin(data);
                    }
                }, "ArkUIPluginUpdateCallback");
        });
        pluginManagerBridge_->AddPluginErrorCallback([weak = WeakClaim(this)](std::string code, std::string msg) {
            auto element = weak.Upgrade();
            auto uiTaskExecutor = SingleTaskExecutor::Make(
                element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
            uiTaskExecutor.PostTask(
                [code, msg, weak] {
                    auto plugin = weak.Upgrade();
                    if (plugin) {
                        plugin->HandleOnErrorEvent(code, msg);
                    }

                    auto render = plugin->GetRenderNode();
                    if (!render) {
                        return;
                    }
                    auto renderPlugin = AceType::DynamicCast<RenderPlugin>(render);
                    if (renderPlugin) {
                        renderPlugin->RemoveChildren();
                    }
                }, "ArkUIPluginErrorCallback");
        });
    }
}

void PluginElement::OnActionEvent(const std::string& action) const
{
    auto eventAction = JsonUtil::ParseJsonString(action);
    if (!eventAction->IsValid()) {
        return;
    }
    auto actionType = eventAction->GetValue("action");
    if (!actionType->IsValid()) {
        return;
    }

    auto type = actionType->GetString();
    if (type != "router" && type != "message") {
        return;
    }

    if (type == "router") {
#ifdef OHOS_STANDARD_SYSTEM
        auto context = GetContext().Upgrade();
        if (context) {
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
    auto parentContainerId = Container::CurrentId();
    while (parentContainerId >= MIN_PLUGIN_SUBCONTAINER_ID) {
        parentContainerId = PluginManager::GetInstance().GetPluginParentContainerId(parentContainerId);
    }
    if (pluginSubContainer_) {
        PluginManager::GetInstance().RemovePluginSubContainer(pluginSubContainerId_);
        PluginManager::GetInstance().RemovePluginParentContainer(pluginSubContainerId_);
        pluginSubContainer_->Destroy();
        pluginSubContainer_.Reset();
    }

    pluginSubContainer_ = AceType::MakeRefPtr<PluginSubContainer>(GetContext().Upgrade());
    CHECK_NULL_VOID(pluginSubContainer_);
    auto plugin = AceType::DynamicCast<PluginComponent>(component_);
    CHECK_NULL_VOID(plugin);
    pluginSubContainerId_ = PluginManager::GetInstance().GetPluginSubContainerId();
    PluginManager::GetInstance().AddPluginSubContainer(pluginSubContainerId_, pluginSubContainer_);
    PluginManager::GetInstance().AddPluginParentContainer(pluginSubContainerId_, parentContainerId);
    pluginSubContainer_->SetInstanceId(pluginSubContainerId_);
    pluginSubContainer_->SetPluginWindowId(GetElementId());
    pluginSubContainer_->Initialize();
    pluginSubContainer_->SetPluginComponent(component_);

    auto weak = WeakClaim(this);
    auto element = weak.Upgrade();
    auto uiTaskExecutor =
        SingleTaskExecutor::Make(element->GetContext().Upgrade()->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    auto pluginNode = AceType::DynamicCast<RenderPlugin>(renderNode_);
    CHECK_NULL_VOID(pluginNode);
    pluginNode->SetPluginSubContainer(pluginSubContainer_);

    uiTaskExecutor.PostTask([this, weak, plugin] { RunPluginTask(weak, plugin); }, "ArkUIPluginContainerRun");
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
            info.abilityName =
                info.pluginName.substr(posAssets + assets.size(), posModule - (posAssets + assets.size()));
            info.source = info.pluginName.substr(posModule);
        } else {
            info.abilityName = "/";
            info.source = info.pluginName.substr(posAssets + assets.size());
        }
    } else {
        size_t pos = info.pluginName.rfind("/");
        packagePathStr = info.pluginName.substr(0, pos + 1);
        info.source = info.pluginName.substr(pos + 1);
        info.abilityName = "/";
    }
    return packagePathStr;
}

std::string PluginElement::GetPackagePathByWant(const WeakPtr<PluginElement>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    auto pluginElement = weak.Upgrade();
    CHECK_NULL_RETURN(pluginElement, packagePathStr);
    std::vector<std::string> strList;
    pluginElement->SplitString(info.bundleName, '/', strList);

    std::vector<int32_t> userIds;
    ErrCode errCode = GetActiveAccountIds(userIds);
    if (errCode != ERR_OK) {
        pluginElement->HandleOnErrorEvent("1", "Query Active OsAccountIds failed!");
        return packagePathStr;
    }
    GetModuleNameByWant(weak, info);
    packagePathStr = GetPackagePathByBms(weak, info, strList, userIds);

    return packagePathStr;
}

void PluginElement::GetModuleNameByWant(const WeakPtr<PluginElement>& weak, RequestPluginInfo& info) const
{
    auto pluginElement = weak.Upgrade();
    CHECK_NULL_VOID(pluginElement);
    std::vector<std::string> strList;
    pluginElement->SplitString(info.pluginName, '&', strList);
    if (strList.empty()) {
        pluginElement->HandleOnErrorEvent("1", "Template source is empty.");
        return;
    }
    if (strList.size() == 1) {
        if (info.pluginName.rfind(".js") != std::string::npos) {
            info.source = info.pluginName;
        } else {
            info.abilityName = info.pluginName;
        }
    } else {
        if (strList[0].rfind(".js") != std::string::npos) {
            info.source = strList[0];
        } else {
            info.abilityName = strList[0];
        }
        info.moduleName = strList[1];
    }
}

std::string PluginElement::GetPackagePathByBms(const WeakPtr<PluginElement>& weak, RequestPluginInfo& info,
    const std::vector<std::string>& strList, const std::vector<int32_t>& userIds) const
{
    std::string packagePathStr;
    auto pluginElement = weak.Upgrade();
    CHECK_NULL_RETURN(pluginElement, packagePathStr);
    auto bms = PluginComponentManager::GetInstance()->GetBundleManager();
    if (!bms) {
        pluginElement->HandleOnErrorEvent("1", "Bms bundleManager is nullptr.");
        return packagePathStr;
    }

    if (strList.empty()) {
        TAG_LOGW(AceLogTag::ACE_PLUGIN_COMPONENT, "App bundleName or abilityName is empty.");
        pluginElement->HandleOnErrorEvent("1", "App bundleName is empty.");
        return packagePathStr;
    }
    AppExecFwk::BundleInfo bundleInfo;
    bool ret = bms->GetBundleInfo(strList[0], AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo,
        userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID);
    if (!ret) {
        pluginElement->HandleOnErrorEvent("1", "Bms get bundleName failed!");
        return packagePathStr;
    }

    if (bundleInfo.hapModuleInfos.empty() || bundleInfo.hapModuleInfos[0].hapPath.empty()) {
        if (strList.size() == 1) {
            if (bundleInfo.moduleResPaths.size() == 1) {
                info.moduleResPath = bundleInfo.moduleResPaths[0];
            } else {
                pluginElement->HandleOnErrorEvent("1", "Bms moduleResPaths is empty.");
                return packagePathStr;
            }
            packagePathStr = bundleInfo.moduleDirs[0] + "/";
        } else {
            AAFwk::Want want;
            AppExecFwk::AbilityInfo abilityInfo;
            AppExecFwk::ElementName element("", strList[0], strList[1]);
            want.SetElement(element);
            bool ret = bms->QueryAbilityInfo(want, AppExecFwk::AbilityInfoFlag::GET_ABILITY_INFO_DEFAULT,
                userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID, abilityInfo);
            if (!ret) {
                pluginElement->HandleOnErrorEvent("1", "Bms get bundleName failed!");
                return packagePathStr;
            }
            packagePathStr = abilityInfo.applicationInfo.codePath + "/" + abilityInfo.package + "/";
            info.moduleResPath = abilityInfo.resourcePath;
        }
        return packagePathStr;
    }
    if (info.moduleName.empty() || info.moduleName == "default") {
        info.moduleResPath = bundleInfo.hapModuleInfos[0].resourcePath;
        packagePathStr = bundleInfo.hapModuleInfos[0].hapPath;
        return packagePathStr;
    }
    auto result = std::find_if(bundleInfo.hapModuleInfos.begin(), bundleInfo.hapModuleInfos.end(),
        [moduleName = info.moduleName](
            AppExecFwk::HapModuleInfo hapModuleInfo) { return hapModuleInfo.moduleName == moduleName; });
    if (result != bundleInfo.hapModuleInfos.end()) {
        info.moduleResPath = result->resourcePath;
        packagePathStr = result->hapPath;
        return packagePathStr;
    }
    pluginElement->HandleOnErrorEvent(
        "1", "Bms get hapPath failed! Cannot find hap according to BundleName and ModuleName!");
    return packagePathStr;
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

void PluginElement::ReplaceAll(std::string& str, const std::string& pattern, const std::string& newPattern)
{
    const size_t nSize = newPattern.size();
    const size_t pSize = pattern.size();
    for (size_t pos = str.find(pattern, 0); pos != std::string::npos; pos = str.find(pattern, pos + nSize)) {
        str.replace(pos, pSize, newPattern);
    }
}

void PluginElement::RunPluginTask(const WeakPtr<PluginElement>& weak, const RefPtr<PluginComponent>& plugin)
{
    auto pluginElement = weak.Upgrade();
    CHECK_NULL_VOID(pluginElement);
    auto container = pluginElement->GetPluginSubContainer();
    CHECK_NULL_VOID(container);
    RequestPluginInfo info = plugin->GetPluginRequestInfo();
    auto packagePathStr = pluginElement->GetPackagePath(weak, info);
    if (packagePathStr.empty()) {
        pluginElement->HandleOnErrorEvent("1", "package path is empty.");
        return;
    }

    if (packagePathStr.rfind(".hap") != std::string::npos) {
        std::string sub = packagePathStr.substr(1, packagePathStr.size() - 5) + "/";
        ReplaceAll(info.source, sub, "");
        container->RunDecompressedPlugin(
            packagePathStr, info.abilityName, info.source, info.moduleResPath, plugin->GetData());
    } else {
        // the hap is decompressed
        container->RunPlugin(packagePathStr, info.abilityName, info.source, info.moduleResPath, plugin->GetData());
    }
}
} // namespace OHOS::Ace
