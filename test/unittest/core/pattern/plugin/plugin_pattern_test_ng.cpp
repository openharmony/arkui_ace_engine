/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <memory>
#include <optional>

#include "gmock/gmock-actions.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

#include "core/common/container.h"

#define private public
#define protected public

#include "bundlemgr/bundle_mgr_interface.h"
#include "mock/mock_bundle_mgr_interface.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/plugin/plugin_component_manager.h"
#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/plugin/plugin_event_hub.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"
#include "core/components_ng/pattern/plugin/plugin_model.h"
#include "core/components_ng/pattern/plugin/plugin_model_ng.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
struct CreateProperty {
    std::optional<double> maxValue = std::nullopt;
    std::optional<double> value = std::nullopt;
};

struct TestProperty {};

namespace {
constexpr Dimension WIDTH = 200.0_vp;
constexpr Dimension HEIGHT = 200.0_vp;
PluginModelNG pluginModel;
RequestPluginInfo pluginInfo;
DirtySwapConfig config;
string testText = "testText";
} // namespace

class PluginPatternTestNg : public testing::Test {
public:
    void CheckValue(const RefPtr<FrameNode>& frameNode, const TestProperty& testProperty);
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override {}
    void TearDown() override {}

protected:
    RefPtr<FrameNode> CreatePluginParagraph();
};

void PluginPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    pluginInfo.pluginName = "plugin1";
    pluginInfo.bundleName = "com.example.plugin";
}

void PluginPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<FrameNode> PluginPatternTestNg::CreatePluginParagraph()
{
    pluginModel.Create(pluginInfo);
    pluginModel.SetPluginSize(WIDTH, HEIGHT);
    pluginModel.SetWidth(WIDTH);
    pluginModel.SetHeight(HEIGHT);
    pluginModel.SetData("{data}");
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: ReplaceAll
 * @tc.desc: Test SplitString in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, ReplaceAll, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    std::vector<std::string> strList;
    std::string oldPattern = "com";
    std::string newPattern = "sys";
    std::string string = "com.example.providerTest/assets/com.exampe.service";
    pattern->ReplaceAll(string, oldPattern, newPattern);
    EXPECT_EQ(string, "sys.example.providerTest/assets/sys.exampe.service");
}

/**
 * @tc.name: PluginPattern002
 * @tc.desc: Test SplitString in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, SplitString, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    std::vector<std::string> strList;
    pattern->SplitString("/com.example.providerTest/assets", '/', strList);
    std::vector<std::string> strList2 = { "com.example.providerTest", "assets" };
}

/**
 * @tc.name: PluginEventHubTestNg
 * @tc.desc: Test PluginEventHub.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, PluginEventHubTestNg, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = AceType::DynamicCast<PluginEventHub>(pattern->CreateEventHub());
    EXPECT_NE(eventHub, nullptr);
    auto onFuntion = [](const std::string& param) { EXPECT_EQ(param, "TestText"); };

    eventHub->FireOnComplete("");
    eventHub->FireOnError("");
    pluginModel.SetOnComplete(onFuntion);
    pluginModel.SetOnError(onFuntion);
    eventHub->FireOnComplete("TestText");
    eventHub->FireOnError("TestText");
    pattern->FireOnCompleteEvent();
    pattern->FireOnErrorEvent("", "TestText");
    pattern->FireOnCompleteEvent();
    auto allowUpdate = pattern->ISAllowUpdate();
    EXPECT_TRUE(allowUpdate);
}

/**
 * @tc.name: PluginPatternTestNg
 * @tc.desc: Test OnDirtyLayoutWrapperSwap in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, OnDirtyLayoutWrapperSwap2, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetContentSize(SizeF(100.0f, 100.0f));
    geometryNode->SetContentOffset(OffsetF(0, 0));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, nullptr);
    EXPECT_NE(layoutWrapper, nullptr);
    auto host = pattern->GetHost();
    EXPECT_NE(host, nullptr);

    /**
     *     case 1: info.bundleName == pluginInfo_.bundleName && pluginInfo_.allowUpdate != info.allowUpdate &&
     *          pluginInfo_.width != info.width && pluginSubContainer_ == nullptr ;
     */
    pattern->pluginInfo_.pluginName = "plugin1";
    pattern->pluginInfo_.bundleName = "com.example.plugin";

    pattern->pluginInfo_.width = WIDTH;
    pattern->pluginInfo_.height = HEIGHT;
    pattern->pluginInfo_.allowUpdate = false;

    config.skipMeasure = false;
    config.skipLayout = false;

    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    /**
     *     case 2: info.bundleName == pluginInfo_.bundleName && pluginInfo_.allowUpdate != info.allowUpdate &&
     *          pluginInfo_.width != info.width && pluginSubContainer_ != nullptr ;
     */
    config.skipMeasure = true;
    config.skipLayout = false;

    pattern->pluginInfo_.width = WIDTH;
    pattern->pluginInfo_.height = HEIGHT;
    pattern->pluginInfo_.allowUpdate = false;

    pattern->CreatePluginSubContainer();
    EXPECT_NE(pattern->pluginSubContainer_, nullptr);
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    /**
     *     case 3: info.bundleName == pluginInfo_.bundleName && pluginInfo_.allowUpdate == info.allowUpdate &&
     *          pluginInfo_.width == info.width;
     */
    config.skipMeasure = true;
    config.skipLayout = false;

    EXPECT_NE(pattern->pluginSubContainer_, nullptr);
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    /**
     *     case 4: info.pluginName != pluginInfo_.pluginName && pluginManagerBridge_ == nullptr ;
     */
    config.skipMeasure = false;
    config.skipLayout = true;
    pattern->pluginInfo_.pluginName = "plugin";
    pattern->pluginManagerBridge_ = nullptr;
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    /**
     *     case 5: info.pluginName != pluginInfo_.pluginName && pluginManagerBridge_ != nullptr ;
     */
    pattern->pluginInfo_.pluginName = "plugin";
    pattern->InitPluginManagerDelegate();
    EXPECT_NE(pattern->pluginManagerBridge_, nullptr);
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    /**
     *     case 6:  config.skipMeasure = true; && onfig.skipLayout = true;
     */
    config.skipMeasure = true;
    config.skipLayout = true;
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(isSwap, false);

    auto data = pattern->GetData();
    EXPECT_EQ(data, "{data}");

    auto pluginInfoOfPattern = pattern->GetPluginRequestInfo();
    EXPECT_EQ(pluginInfoOfPattern, pluginInfo);
}

/**
 * @tc.name: PluginPatternTestNg
 * @tc.desc: Test CreatePluginSubContainer in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, CreatePluginSubContainerTestNg, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    Container::UpdateCurrent(MIN_PLUGIN_SUBCONTAINER_ID);
    pattern->CreatePluginSubContainer();
    auto pluginSubContainer = pattern->GetPluginSubContainer();
    EXPECT_NE(pluginSubContainer, nullptr);
}

/**
 * @tc.name: GetPackagePathTestNg1
 * @tc.desc: Test GetPackagePath throw GetPackagePathByAbsolutePath in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, GetPackagePathTestNg1, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "/data/bundle/index.js", bundleName: "com.example.plugin" },data:
     * {}})
     */
    pluginInfo.pluginName = "/data/bundle/index.js";
    auto packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "/data/bundle/");
    EXPECT_EQ(pluginInfo.abilityName, "/");
    EXPECT_EQ(pluginInfo.source, "index.js");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "/data/bundle/assets/js/index.js", bundleName: "com.example.plugin"
     * },data: {}})
     */
    pluginInfo.pluginName = "/data/bundle/assets/js/index.js";
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "/data/bundle/");
    EXPECT_EQ(pluginInfo.abilityName, "/");
    EXPECT_EQ(pluginInfo.source, "index.js");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "/data/bundle/assets/js/plugin/index.js",
     *                                  bundleName: "com.example.plugin" },data: {}})
     */
    pluginInfo.pluginName = "/data/bundle/assets/js/plugin/index.js";
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "/data/bundle/");
    EXPECT_EQ(pluginInfo.abilityName, "plugin");
    EXPECT_EQ(pluginInfo.source, "/index.js");
}

/**
 * @tc.name: GetPackagePathTestNg2
 * @tc.desc: Test GetPackagePath throw GetPackagePathByWant when hapPath is not empty in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, GetPackagePathTestNg2, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "", bundleName:""},data: {}})
     */
    pluginInfo.pluginName = "";
    pluginInfo.bundleName = "";
    auto packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin/index.js", bundleName:"com.example.plugin"},data: {}})
     */
    pluginInfo.pluginName = "plugin/index.js";
    pluginInfo.bundleName = "com.example.plugin";
    AppExecFwk::BundleInfo bundleInfo;
    AppExecFwk::HapModuleInfo hapModuleInfo;
    hapModuleInfo.hapPath = "/data/storage/com.example.plugin/";
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "");

    AppExecFwk::MOCKIBundleMgr::CreateInstance();

    auto bms = (PluginComponentManager::GetInstance()->GetBundleManager());
    auto* bundleMgr = static_cast<AppExecFwk::MOCKIBundleMgr*>(bms.GetRefPtr());

    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _)).WillOnce(Return(false));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);

    bundleInfo.hapModuleInfos.emplace_back(hapModuleInfo);
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "plugin/index.js");
    EXPECT_EQ(packagePathStr, "/data/storage/com.example.plugin/");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "pages/index.js&plugin", bundleName:"com.example.plugin"},data: {}})
     */
    pluginInfo.pluginName = "pages&plugin";
    pluginInfo.bundleName = "com.example.plugin";
    hapModuleInfo.moduleName = "plugin";
    hapModuleInfo.resourcePath = "resourcePath";
    bundleInfo.hapModuleInfos.emplace_back(hapModuleInfo);
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.abilityName, "pages");
    EXPECT_EQ(pluginInfo.moduleName, "plugin");
    EXPECT_EQ(pluginInfo.moduleResPath, "resourcePath");
    EXPECT_EQ(packagePathStr, "/data/storage/com.example.plugin/");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "pages/index.js&plugin", bundleName:"com.example.plugin"},data: {}})
     */
    pluginInfo.pluginName = "pages/plugin.js&plugin1";
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "pages/plugin.js");
    EXPECT_EQ(pluginInfo.moduleName, "plugin1");
    EXPECT_EQ(packagePathStr, "");

    AppExecFwk::MOCKIBundleMgr::ReleaseInstance();
}

/**
 * @tc.name: GetPackagePathTestNg3
 * @tc.desc: Test GetPackagePath throw GetPackagePathByWant when hapPath is empty  in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, GetPackagePathTestNg3, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "", bundleName:""},data: {}})
     */
    pluginInfo.pluginName = "";
    pluginInfo.bundleName = "";
    auto packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin/index.js", bundleName:"com.example.plugin"},data: {}})
     */
    pluginInfo.pluginName = "plugin/index.js";
    pluginInfo.bundleName = "com.example.plugin";
    AppExecFwk::BundleInfo bundleInfo;

    AppExecFwk::MOCKIBundleMgr::CreateInstance();

    auto bms = (PluginComponentManager::GetInstance()->GetBundleManager());
    auto* bundleMgr = static_cast<AppExecFwk::MOCKIBundleMgr*>(bms.GetRefPtr());

    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "");

    bundleInfo.moduleResPaths.emplace_back("moduleResPaths");
    bundleInfo.moduleDirs.emplace_back("/data/storage/com.example.plugin");
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "plugin/index.js");
    EXPECT_EQ(packagePathStr, "/data/storage/com.example.plugin/");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin/index.js", bundleName:"com.example.plugin/plugin"},data:
     * {}})
     */
    pluginInfo.pluginName = "plugin/index.js";
    pluginInfo.bundleName = "com.example.plugin/plugin";

    AppExecFwk::AbilityInfo abilityInfo;
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    EXPECT_CALL(*bundleMgr, QueryAbilityInfo(_, AppExecFwk::AbilityInfoFlag::GET_ABILITY_INFO_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<3>(abilityInfo), Return(false)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "");

    abilityInfo.applicationInfo.codePath = "/data/storage/com.example.plugin";
    abilityInfo.package = "data/plugin";
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    EXPECT_CALL(*bundleMgr, QueryAbilityInfo(_, AppExecFwk::AbilityInfoFlag::GET_ABILITY_INFO_DEFAULT, _, _))
        .WillOnce(DoAll(SetArgReferee<3>(abilityInfo), Return(true)));
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "/data/storage/com.example.plugin/data/plugin/");

    AppExecFwk::MOCKIBundleMgr::ReleaseInstance();
}

/**@tc.name : GetPackagePathTestNg4
 * @tc.desc : Test GetPackagePath.
 * @tc.type : FUNC
 */
HWTEST_F(PluginPatternTestNg, GetPackagePathTestNg4, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "", bundleName:""},data: {}})
     */
    pluginInfo.pluginName = "";
    pluginInfo.bundleName = "";
    AppExecFwk::BundleInfo bundleInfo;
    AppExecFwk::MOCKIBundleMgr::CreateInstance();

    auto packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(packagePathStr, "");

    AppExecFwk::MOCKIBundleMgr::ReleaseInstance();
}

/**@tc.name : GetPackagePathTestNg5
 * @tc.desc : Test GetPackagePath.
 * @tc.type : FUNC
 */
HWTEST_F(PluginPatternTestNg, GetPackagePathTestNg5, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    AppExecFwk::BundleInfo bundleInfo;
    AppExecFwk::MOCKIBundleMgr::CreateInstance();
    auto bms = (PluginComponentManager::GetInstance()->GetBundleManager());
    auto* bundleMgr = static_cast<AppExecFwk::MOCKIBundleMgr*>(bms.GetRefPtr());

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin/index.ets", bundleName:"com.example.plugin/plugin"},data:
     * {}})
     */
    pluginInfo.pluginName = "plugin/index.ets";
    pluginInfo.bundleName = "com.example.plugin";

    bundleInfo.moduleResPaths.emplace_back("moduleResPaths");
    bundleInfo.moduleDirs.emplace_back("/data/storage/com.example.plugin");
    EXPECT_CALL(*bundleMgr, GetBundleInfo(_, AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<2>(bundleInfo), Return(true)));
    auto packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "plugin/index.js");
    EXPECT_EQ(packagePathStr, "/data/storage/com.example.plugin/");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin.ets/index.js", bundleName:"com.example.plugin/plugin"},data:
     * {}})
     */
    pluginInfo.pluginName = "plugin.ets/index.js";
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "plugin.ets/index.js");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin.ets/index.js&plugin",
     *     bundleName:"com.example.plugin/plugin"},data:{}})
     */
    pluginInfo.pluginName = "plugin.ets/index.ets&plugin";
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "plugin.ets/index.js");

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin/index.ets&plugin", bundleName:"com.example.plugin/plugin"},data:
     * {}})
     */
    pluginInfo.pluginName = "plugin/index.ets&plugin";
    packagePathStr = pattern->GetPackagePath(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.source, "plugin/index.js");

    AppExecFwk::MOCKIBundleMgr::ReleaseInstance();
}

/**@tc.name : GetAbilityNameByWant
 * @tc.desc : Test GetPackagePath.
 * @tc.type : FUNC
 */
HWTEST_F(PluginPatternTestNg, GetAbilityNameByWant, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     *     corresponding ets code:
     *     PluginComponent({template: { source: "plugin", bundleName:""},data: {}})
     */
    pluginInfo.pluginName = "plugin";
    pluginInfo.bundleName = "";
    AppExecFwk::BundleInfo bundleInfo;
    AppExecFwk::MOCKIBundleMgr::CreateInstance();
    pattern->GetAbilityNameByWant(AceType::WeakClaim(AceType::RawPtr(pattern)), pluginInfo);
    EXPECT_EQ(pluginInfo.abilityName, "plugin");

    AppExecFwk::MOCKIBundleMgr::ReleaseInstance();
}

/**
 * @tc.name: PluginPatternTestNg
 * @tc.desc: Test FireEvent in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, FireEvent, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->InitPluginManagerDelegate();
    pattern->pluginManagerBridge_->OnPluginUpdate("");
    pattern->pluginManagerBridge_->OnPluginError("");
}

/**
 * @tc.name: GetDrawDelegate
 * @tc.desc: Test OnActionEvent in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, GetDrawDelegate, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    std::shared_ptr<RSNode> rsNode = nullptr;
    auto drawRSFrame = pattern->GetDrawDelegate();
    drawRSFrame->DrawRSFrame(rsNode, Rect(100.0, 100.0, 100.0, 100.0));
}

/**
 * @tc.name: PluginCodeLanguageTestNg
 * @tc.desc: Test funcions in Plugin Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, PluginCodeLanguageTestNg, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    auto info = pattern->GetPluginRequestInfo();
    auto codeLanguage = pattern->GetPackageCodeLanguage(info);
    EXPECT_EQ(codeLanguage, "");
}

/**
 * @tc.name: PluginLayoutPropertyTestNg
 * @tc.desc: Test funcions in PluginLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, PluginLayoutTestNg, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layout = pattern->GetLayoutProperty<PluginLayoutProperty>();
    EXPECT_NE(layout, nullptr);
    layout->Clone();
    layout.Reset();
}

/**
 * @tc.name: JSPluginOnCompleteTest
 * @tc.desc: Test funcions in JSPlugin.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, JSPluginOnCompleteTest, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = AceType::DynamicCast<PluginEventHub>(pattern->CreateEventHub());
    EXPECT_NE(eventHub, nullptr);
    auto onComplete = [](const std::string& param) { EXPECT_EQ(param, "OnComplete"); };

    pluginModel.SetOnComplete(onComplete);
    eventHub->FireOnComplete("OnComplete");
    auto allowUpdate = pattern->ISAllowUpdate();
    EXPECT_TRUE(allowUpdate);
}

/**
 * @tc.name: JSPluginOnErrorTest
 * @tc.desc: Test funcions in JSPlugin.
 * @tc.type: FUNC
 */
HWTEST_F(PluginPatternTestNg, JSPluginOnErrorTest, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreatePluginParagraph();
    auto pattern = frameNode->GetPattern<PluginPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = AceType::DynamicCast<PluginEventHub>(pattern->CreateEventHub());
    EXPECT_NE(eventHub, nullptr);
    auto onError = [](const std::string& param) { EXPECT_EQ(param, "OnError"); };

    pluginModel.SetOnError(onError);
    eventHub->FireOnError("OnError");
    auto allowUpdate = pattern->ISAllowUpdate();
    EXPECT_TRUE(allowUpdate);
}
} // namespace OHOS::Ace::NG
