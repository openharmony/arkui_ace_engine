/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
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
#endif                                       // OS_ACCOUNT_EXISTS

ErrCode GetActiveAccountIds(std::vector<int32_t>& userIds)
{
    userIds.clear();
#ifdef OS_ACCOUNT_EXISTS
    return AccountSA::OsAccountManager::QueryActiveOsAccountIds(userIds);
#else  // OS_ACCOUNT_EXISTS
    userIds.push_back(DEFAULT_OS_ACCOUNT_ID);
    return ERR_OK;
#endif // OS_ACCOUNT_EXISTS
}
constexpr char JS_EXT[] = ".js";
constexpr char ETS_EXT[] = ".ets";
constexpr size_t SIZE_OF_ETS_EXT = 4;
} // namespace

PluginPattern::~PluginPattern()
{
    pluginManagerBridge_.Reset();
    if (pluginSubContainer_) {
        auto currentId = pluginSubContainer_->GetInstanceId();
        PluginManager::GetInstance().RemovePluginSubContainer(currentId);
        PluginManager::GetInstance().RemovePluginParentContainer(currentId);
        pluginSubContainer_->Destroy();
        pluginSubContainer_.Reset();
    }
}

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
    auto data = layoutProperty->GetData().value_or("");
    if (info.bundleName != pluginInfo_.bundleName || info.abilityName != pluginInfo_.abilityName ||
        info.moduleName != pluginInfo_.moduleName || info.pluginName != pluginInfo_.pluginName ||
        info.dimension != pluginInfo_.dimension || data_ != data) {
        pluginInfo_ = info;
        data_ = data;
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
    loadFialState_ = false;
    CreatePluginSubContainer();
    if (pluginManagerBridge_) {
        pluginManagerBridge_->AddPlugin(host->GetContextRefPtr(), info);
    }
    return false;
}

void PluginPattern::InitPluginManagerDelegate()
{
    CHECK_NULL_VOID(!pluginManagerBridge_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
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
        uiTaskExecutor.PostTask(
            [weak, instanceID] {
                ContainerScope scope(instanceID);
                auto plugin = weak.Upgrade();
                CHECK_NULL_VOID(plugin);
                plugin->FireOnCompleteEvent();
            },
            "ArkUIPluginCompleteEvent");
    });
    pluginManagerBridge_->AddPluginUpdateCallback([weak = WeakClaim(this), instanceID](int64_t id, std::string data) {
        ContainerScope scope(instanceID);
        auto plugin = weak.Upgrade();
        CHECK_NULL_VOID(plugin);
        auto host = plugin->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor =
            SingleTaskExecutor::Make(host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask(
            [data, weak] {
                auto plugin = weak.Upgrade();
                CHECK_NULL_VOID(plugin);
                plugin->GetPluginSubContainer()->UpdatePlugin(data);
            },
            "ArkUIPluginUpdate");
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
            uiTaskExecutor.PostTask(
                [code, msg, weak, instanceID] {
                    ContainerScope scope(instanceID);
                    auto plugin = weak.Upgrade();
                    CHECK_NULL_VOID(plugin);
                    plugin->FireOnErrorEvent(code, msg);
                },
                "ArkUIPluginErrorEvent");
        });
}

void PluginPattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("pluginInfo: ").append(pluginInfo_.ToString()));
    DumpLog::GetInstance().AddDesc(std::string("data: ").append(data_));
}

void PluginPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("pluginInfo: ", pluginInfo_.ToString().c_str());
    json->Put("data: ", data_.c_str());
}

void PluginPattern::CreatePluginSubContainer()
{
    TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "CreatePluginSubContainer.");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto layoutProperty = host->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto parentcontainerId = Container::CurrentId();
    while (parentcontainerId >= MIN_PLUGIN_SUBCONTAINER_ID) {
        parentcontainerId = PluginManager::GetInstance().GetPluginParentContainerId(parentcontainerId);
    }

    if (pluginSubContainer_) {
        auto currentId = pluginSubContainer_->GetInstanceId();
        TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "destory old pluginSubContainer: %{public}d.", currentId);
        PluginManager::GetInstance().RemovePluginSubContainer(currentId);
        PluginManager::GetInstance().RemovePluginParentContainer(currentId);
        pluginSubContainer_->Destroy();
        pluginSubContainer_.Reset();
    }
    auto pluginSubContainerId_ = PluginManager::GetInstance().GetPluginSubContainerId();
    pluginSubContainer_ = AceType::MakeRefPtr<PluginSubContainer>(context, pluginSubContainerId_);
    CHECK_NULL_VOID(pluginSubContainer_);

    PluginManager::GetInstance().AddPluginSubContainer(pluginSubContainerId_, pluginSubContainer_);
    PluginManager::GetInstance().AddPluginParentContainer(pluginSubContainerId_, parentcontainerId);
    pluginSubContainer_->Initialize(GetPackageCodeLanguage(GetPluginRequestInfo()));
    auto weak = WeakClaim(this);
    pluginSubContainer_->SetPluginPattern(weak);
    auto pattern = weak.Upgrade();
    auto host_ = pattern->GetHost();
    CHECK_NULL_VOID(host_);
    pluginSubContainer_->SetPluginWindowId(GetHost()->GetId());
    pluginSubContainer_->SetPluginNode(GetHost());

    CHECK_NULL_VOID(host_->GetContext());
    auto uiTaskExecutor = SingleTaskExecutor::Make(host_->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    int32_t instanceID = context->GetInstanceId();
    uiTaskExecutor.PostTask(
        [weak, instanceID] {
            ContainerScope scope(instanceID);
            auto pluginPattern = weak.Upgrade();
            CHECK_NULL_VOID(pluginPattern);
            auto pluginSubContainer = pluginPattern->GetPluginSubContainer();
            RequestPluginInfo info = pluginPattern->GetPluginRequestInfo();
            TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "requestPluginInfo: %{public}s.", info.ToString().c_str());
            CHECK_NULL_VOID(pluginSubContainer);
            auto packagePathStr = pluginPattern->GetPackagePath(weak, info);
            if (packagePathStr.empty()) {
                pluginPattern->FireOnErrorEvent("1", "package path is empty.");
                return;
            }
            if (!info.bundleName.empty() && !info.moduleName.empty()) {
                pluginPattern->pluginSubContainer_->SetPluginBundleName(info.bundleName);
                pluginPattern->pluginSubContainer_->SetPluginModuleName(info.moduleName);
            }
            if (packagePathStr.rfind(".hap") != std::string::npos) {
                std::string sub = packagePathStr.substr(1, packagePathStr.size() - 5) + "/";
                pluginPattern->ReplaceAll(info.source, sub, "");
                pluginPattern->pluginSubContainer_->RunDecompressedPlugin(
                    packagePathStr, info.abilityName, info.source, info.moduleResPath, pluginPattern->GetData());
            } else {
                pluginPattern->pluginSubContainer_->RunPlugin(
                    packagePathStr, info.abilityName, info.source, info.moduleResPath, pluginPattern->GetData());
            }
        },
        "ArkUIPluginRun");
        TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "CreatePluginSubContainer end.");
}

void PluginPattern::ReplaceAll(std::string& str, const std::string& pattern, const std::string& newPattern)
{
    const size_t nSize = newPattern.size();
    const size_t pSize = pattern.size();
    for (size_t pos = str.find(pattern, 0); pos != std::string::npos; pos = str.find(pattern, pos + nSize)) {
        str.replace(pos, pSize, newPattern);
    }
}

std::unique_ptr<DrawDelegate> PluginPattern::GetDrawDelegate()
{
    auto drawDelegate = std::make_unique<DrawDelegate>();
#ifdef ENABLE_ROSEN_BACKEND
    drawDelegate->SetDrawRSFrameCallback(
        [weak = WeakClaim(this)](std::shared_ptr<RSNode>& node, const Rect& /* dirty */) {
            auto plugin = weak.Upgrade();
            if (!plugin) {
                TAG_LOGE(AceLogTag::ACE_PLUGIN_COMPONENT, "Failed to draw rs frame with invalid plugin pattern.");
                return;
            }
            auto host = plugin->GetHost();
            CHECK_NULL_VOID(host);
            auto context = DynamicCast<NG::RosenRenderContext>(host->GetRenderContext());
            CHECK_NULL_VOID(context);
            auto rsNode = context->GetRSNode();
            CHECK_NULL_VOID(rsNode);
            if (node) {
                node->SetBackgroundColor(Color::TRANSPARENT.GetValue());
            } else {
                TAG_LOGE(AceLogTag::ACE_PLUGIN_COMPONENT, "Failed to draw rs frame with invalid rs node.");
            }
            rsNode->AddChild(node, -1);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        });
#endif
    return drawDelegate;
}

void PluginPattern::FireOnCompleteEvent() const
{
    TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "FireOnCompleteEvent.");
    if (loadFialState_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto json = JsonUtil::Create(true);
    eventHub->FireOnComplete(json->ToString());
}

void PluginPattern::FireOnErrorEvent(const std::string& code, const std::string& msg)
{
    loadFialState_ = true;
    TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "code: %{public}s, msg: %{public}s", code.c_str(), msg.c_str());
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
    TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "action: %{public}s", action.c_str());
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

    CHECK_NULL_VOID(pluginManagerBridge_);
    pluginManagerBridge_->OnActionEvent(action);
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

std::string PluginPattern::GetPackageCodeLanguage(const RequestPluginInfo& info) const
{
    std::string codeLanguage;

    std::vector<std::string> strList;
    SplitString(info.bundleName, '/', strList);
    if (strList.empty()) {
        return codeLanguage;
    }

    std::vector<int32_t> userIds;
    GetActiveAccountIds(userIds);

    auto bms = PluginComponentManager::GetInstance()->GetBundleManager();
    if (!bms) {
        return codeLanguage;
    }

    AppExecFwk::BundleInfo bundleInfo;
    bool ret = bms->GetBundleInfo(strList[0], AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo,
        userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID);
    if (!ret) {
        return codeLanguage;
    }
    return bundleInfo.applicationInfo.arkTSMode;
}

std::string PluginPattern::GetPackagePath(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    size_t pos_ets = info.pluginName.rfind(ETS_EXT);
    if (pos_ets != std::string::npos && info.pluginName.substr(pos_ets) == ETS_EXT) {
        info.pluginName = info.pluginName.substr(0, info.pluginName.length() - SIZE_OF_ETS_EXT);
        info.pluginName = info.pluginName + JS_EXT;
    }
    size_t pos = info.pluginName.rfind(JS_EXT);
    if (info.pluginName.front() == '/' && pos != std::string::npos && info.pluginName.substr(pos) == JS_EXT) {
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
    CHECK_NULL_RETURN(pluginPattern, packagePathStr);
    std::vector<std::string> strList;
    pluginPattern->SplitString(info.bundleName, '/', strList);

    std::vector<int32_t> userIds;
    ErrCode errCode = GetActiveAccountIds(userIds);
    if (errCode != ERR_OK) {
        pluginPattern->FireOnErrorEvent("1", "Query Active OsAccountIds failed!");
        return packagePathStr;
    }
    GetAbilityNameByWant(weak, info);
    packagePathStr = GetPackagePathByBms(weak, info, strList, userIds);

    return packagePathStr;
}
std::string PluginPattern::GetPackagePathByAbsolutePath(
    const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    std::string packagePathStr;
    auto pluginPattern = weak.Upgrade();
    CHECK_NULL_RETURN(pluginPattern, packagePathStr);
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

void PluginPattern::GetAbilityNameByWant(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info) const
{
    auto pluginPattern = weak.Upgrade();
    CHECK_NULL_VOID(pluginPattern);
    std::vector<std::string> strList;
    pluginPattern->SplitString(info.pluginName, '&', strList);
    if (strList.empty()) {
        pluginPattern->FireOnErrorEvent("1", "Template source is empty.");
        return;
    }
    if (strList.size() == 1) {
        auto pos = info.pluginName.rfind(JS_EXT);
        if (pos != std::string::npos && (strList[0].substr(pos) == JS_EXT)) {
            info.source = info.pluginName;
        } else {
            info.abilityName = info.pluginName;
        }
    } else {
        size_t pos_ets = strList[0].rfind(ETS_EXT);
        if (pos_ets != std::string::npos && strList[0].substr(pos_ets) == ETS_EXT) {
            strList[0] = strList[0].substr(0, strList[0].length() - SIZE_OF_ETS_EXT);
            strList[0] = strList[0] + JS_EXT;
        }
        auto pos = strList[0].rfind(JS_EXT);
        if (pos != std::string::npos && (strList[0].substr(pos) == JS_EXT)) {
            info.source = strList[0];
        } else {
            info.abilityName = strList[0];
        }
        info.moduleName = strList[1];
    }
}

std::string PluginPattern::GetPackagePathByBms(const WeakPtr<PluginPattern>& weak, RequestPluginInfo& info,
    const std::vector<std::string>& strList, const std::vector<int32_t>& userIds) const
{
    std::string packagePathStr;
    auto pluginPattern = weak.Upgrade();
    CHECK_NULL_RETURN(pluginPattern, packagePathStr);
    auto bms = PluginComponentManager::GetInstance()->GetBundleManager();
    if (!bms) {
        pluginPattern->FireOnErrorEvent("1", "Bms bundleManager is nullptr.");
        return packagePathStr;
    }

    if (strList.empty()) {
        pluginPattern->FireOnErrorEvent("1", "App bundleName is empty.");
        return packagePathStr;
    }

    AppExecFwk::BundleInfo bundleInfo;
    bool ret = bms->GetBundleInfo(strList[0], AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo,
        userIds.size() > 0 ? userIds[0] : AppExecFwk::Constants::UNSPECIFIED_USERID);
    if (!ret) {
        pluginPattern->FireOnErrorEvent("1", "Bms get bundleName failed!");
        return packagePathStr;
    }
    if (bundleInfo.hapModuleInfos.empty() || bundleInfo.hapModuleInfos[0].hapPath.empty()) {
        if (strList.size() == 1) {
            if (bundleInfo.moduleResPaths.size() == 1) {
                info.moduleResPath = bundleInfo.moduleResPaths[0];
            } else {
                pluginPattern->FireOnErrorEvent("1", "Bms moduleResPaths is empty.");
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
                pluginPattern->FireOnErrorEvent("1", "Bms get bundleName failed!");
                return packagePathStr;
            }
            packagePathStr = abilityInfo.applicationInfo.codePath + "/" + abilityInfo.package + "/";
            info.moduleResPath = abilityInfo.resourcePath;
        }
        return packagePathStr;
    }
    if (info.moduleName.empty() || info.moduleName == "default") {
        info.moduleResPath = bundleInfo.hapModuleInfos[0].resourcePath;
        info.moduleName = bundleInfo.hapModuleInfos[0].name;
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
    pluginPattern->FireOnErrorEvent(
        "1", "Bms get hapPath failed! Cannot find hap according to BundleName and ModuleName!");
    return packagePathStr;
}

const RefPtr<PluginSubContainer>& PluginPattern::GetPluginSubContainer() const
{
    return pluginSubContainer_;
};

void PluginPattern::FlushReload() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto customNode = DynamicCast<CustomNodeBase>(host->GetFirstChild());
    CHECK_NULL_VOID(customNode);
    customNode->FireReloadFunction(true);
}
} // namespace OHOS::Ace::NG
