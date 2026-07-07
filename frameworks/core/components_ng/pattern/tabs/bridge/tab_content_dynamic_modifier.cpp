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
#include "core/interfaces/native/node/tab_content_modifier.h"

#include "bridge/common/utils/engine_helper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/tabs/bridge/arkts_native_tabcontent_bridge.h"
#include "core/components_ng/pattern/tabs/tab_content_model.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/interfaces/native/node/view_model.h"

namespace OHOS::Ace::NG {
namespace {

#ifndef CROSS_PLATFORM
TabContentModel* GetTabContentModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("tab-content");
    static TabContentModel* instance = loader ? reinterpret_cast<TabContentModel*>(loader->CreateModel()) : nullptr;
    return instance;
}

void CreateTabContentImpl(void* builderRawPtr)
{
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    if (builderRawPtr) {
        auto builder = reinterpret_cast<std::function<void()>*>(builderRawPtr);
        tabContentModelImpl->Create(std::move(*builder));
        return;
    }
    tabContentModelImpl->Create();
}

void PopTabContentImpl()
{
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->Pop();
}

void CreateWithResourceObjImpl(ArkUINodeHandle node, void* paramRawPtr)
{
    (void)node;
    (void)paramRawPtr;
}

void SetCustomStyleNodeImpl(ArkUINodeHandle node, ArkUINodeHandle customNode)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* customFrameNode = reinterpret_cast<FrameNode*>(customNode);
    tabContentModelImpl->SetCustomStyleNode(customFrameNode ? AceType::Claim(customFrameNode) : nullptr);
}

void SetDrawableIndicatorConfigImpl(ArkUINodeHandle node, void* config)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* drawableConfig = reinterpret_cast<ImageInfoConfig*>(config);
    CHECK_NULL_VOID(drawableConfig);
    tabContentModelImpl->SetDrawableIndicatorConfig(*drawableConfig);
}

void SetDrawableIndicatorFlagImpl(ArkUINodeHandle node, ArkUI_Bool isDrawableIndicator)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetDrawableIndicatorFlag(isDrawableIndicator);
}

void SetIndicatorColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetIndicatorColorByUser(isByUser);
}

void SetIndicatorImpl(ArkUINodeHandle node, void* indicator)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* indicatorStyle = reinterpret_cast<IndicatorStyle*>(indicator);
    CHECK_NULL_VOID(indicatorStyle);
    tabContentModelImpl->SetIndicator(*indicatorStyle);
}

void SetSelectedModeImpl(ArkUINodeHandle node, ArkUI_Int32 selectedMode)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetSelectedMode(static_cast<SelectedMode>(selectedMode));
}

void SetBoardImpl(ArkUINodeHandle node, void* board)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* boardStyle = reinterpret_cast<BoardStyle*>(board);
    CHECK_NULL_VOID(boardStyle);
    tabContentModelImpl->SetBoard(*boardStyle);
}

void SetLabelStyleImpl(ArkUINodeHandle node, void* labelStyle, ArkUI_Bool isSubTabStyle)
{
    (void)node;
    (void)isSubTabStyle;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* style = reinterpret_cast<LabelStyle*>(labelStyle);
    CHECK_NULL_VOID(style);
    tabContentModelImpl->SetLabelStyle(*style);
}

void SetLabelUnselectedColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetLabelUnselectedColorByUser(isByUser);
}

void SetLabelSelectedColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetLabelSelectedColorByUser(isByUser);
}

void SetPaddingImpl(ArkUINodeHandle node, void* padding, ArkUI_Bool isSubTabStyle)
{
    (void)node;
    (void)isSubTabStyle;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* paddingProperty = reinterpret_cast<PaddingProperty*>(padding);
    CHECK_NULL_VOID(paddingProperty);
    tabContentModelImpl->SetPadding(*paddingProperty);
}

void SetUseLocalizedPaddingImpl(ArkUINodeHandle node, ArkUI_Bool useLocalizedPadding)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetUseLocalizedPadding(useLocalizedPadding);
}

void CreatePaddingHorWithResourceObjImpl(ArkUINodeHandle node, void* paramRawPtr)
{
    (void)node;
    (void)paramRawPtr;
}

void CreatePaddingVerWithResourceObjImpl(ArkUINodeHandle node, void* paramRawPtr)
{
    (void)node;
    (void)paramRawPtr;
}

void SetLayoutModeImpl(ArkUINodeHandle node, ArkUI_Int32 layoutMode)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetLayoutMode(static_cast<LayoutMode>(layoutMode));
}

void SetVerticalAlignImpl(ArkUINodeHandle node, ArkUI_Int32 verticalAlign)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetVerticalAlign(static_cast<FlexAlign>(verticalAlign));
}

void SetSymmetricExtensibleImpl(ArkUINodeHandle node, ArkUI_Bool isExtensible)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetSymmetricExtensible(isExtensible);
}

void SetIconStyleImpl(ArkUINodeHandle node, void* iconStyle)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* style = reinterpret_cast<IconStyle*>(iconStyle);
    CHECK_NULL_VOID(style);
    tabContentModelImpl->SetIconStyle(*style);
}

void SetIconUnselectedColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetIconUnselectedColorByUser(isByUser);
}

void SetIconSelectedColorByUserImpl(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetIconSelectedColorByUser(isByUser);
}

void SetIdImpl(ArkUINodeHandle node, ArkUI_CharPtr id)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    CHECK_NULL_VOID(id);
    tabContentModelImpl->SetId(std::string(id));
}

void SetTabBarImpl(ArkUINodeHandle node, void* paramRawPtr, bool fromJsView)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    auto* param = reinterpret_cast<TabContentTabBarParam*>(paramRawPtr);
    CHECK_NULL_VOID(param);
    tabContentModelImpl->SetTabBarStyle(param->style);
    if (param->builder) {
        tabContentModelImpl->SetTabBar(
            param->text, param->icon, param->tabBarSymbol, std::move(*param->builder), fromJsView);
    } else {
        tabContentModelImpl->SetTabBar(param->text, param->icon, param->tabBarSymbol, nullptr, fromJsView);
    }
    tabContentModelImpl->SetTabBarWithContent(param->content ? AceType::Claim(param->content) : nullptr);
}

void SetTabContentBuilderImpl(ArkUINodeHandle node, ArkUI_Int32 methodId)
{
    (void)node;
    (void)methodId;
}

void SetTabContentLabelImpl(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    (void)node;
    (void)label;
}

void SetTabContentOnWillShowImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    if (callback) {
        auto onWillShow = reinterpret_cast<std::function<void()>*>(callback);
        tabContentModelImpl->SetOnWillShow(std::move(*onWillShow));
        return;
    }
    tabContentModelImpl->SetOnWillShow(nullptr);
}

void ResetTabContentOnWillShowImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetOnWillShow(nullptr);
}

void SetTabContentOnWillHideImpl(ArkUINodeHandle node, void* callback)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    if (callback) {
        auto onWillHide = reinterpret_cast<std::function<void()>*>(callback);
        tabContentModelImpl->SetOnWillHide(std::move(*onWillHide));
        return;
    }
    tabContentModelImpl->SetOnWillHide(nullptr);
}

void ResetTabContentOnWillHideImpl(ArkUINodeHandle node)
{
    (void)node;
    auto tabContentModelImpl = GetTabContentModelImpl();
    CHECK_NULL_VOID(tabContentModelImpl);
    tabContentModelImpl->SetOnWillHide(nullptr);
}
#endif
} // namespace

void CreateTabContent(void* builderRawPtr)
{
    if (builderRawPtr) {
        auto builder = reinterpret_cast<std::function<void()>*>(builderRawPtr);
        TabContentModelNG::CreateTabContent(std::move(*builder));
        return;
    }
    TabContentModelNG::CreateTabContent();
}

void PopTabContent()
{
    TabContentModelNG::PopTabContent();
}

void CreateTabContentWithResourceObj(ArkUINodeHandle node, void* paramRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* param = reinterpret_cast<TabContentResourceObjParam*>(paramRawPtr);
    CHECK_NULL_VOID(param);
    auto resObj = param->resourceObj ? AceType::Claim(param->resourceObj) : nullptr;
    TabContentModelNG::CreateMoreWithResourceObj(param->jsResourceType, frameNode, resObj);
}

void SetCustomStyleNode(ArkUINodeHandle node, ArkUINodeHandle customNode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* customFrameNode = reinterpret_cast<FrameNode*>(customNode);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetCustomStyleNode(frameNode, customFrameNode ? AceType::Claim(customFrameNode) : nullptr);
}

void SetDrawableIndicatorConfig(ArkUINodeHandle node, void* config)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* drawableConfig = reinterpret_cast<ImageInfoConfig*>(config);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(drawableConfig);
    TabContentModelNG::SetDrawableIndicatorConfig(frameNode, *drawableConfig);
}

void SetDrawableIndicatorFlag(ArkUINodeHandle node, ArkUI_Bool isDrawableIndicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetDrawableIndicatorFlag(frameNode, isDrawableIndicator);
}

void SetIndicatorColorByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetIndicatorColorByUser(frameNode, isByUser);
}

void SetIndicator(ArkUINodeHandle node, void* indicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* indicatorStyle = reinterpret_cast<IndicatorStyle*>(indicator);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(indicatorStyle);
    TabContentModelNG::SetIndicator(frameNode, *indicatorStyle);
}

void SetSelectedMode(ArkUINodeHandle node, ArkUI_Int32 selectedMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetSelectedMode(frameNode, static_cast<SelectedMode>(selectedMode));
}

void SetBoard(ArkUINodeHandle node, void* board)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* boardStyle = reinterpret_cast<BoardStyle*>(board);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(boardStyle);
    TabContentModelNG::SetBoard(frameNode, *boardStyle);
}

void SetLabelStyle(ArkUINodeHandle node, void* labelStyle, ArkUI_Bool isSubTabStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    (void)isSubTabStyle;
    auto* style = reinterpret_cast<LabelStyle*>(labelStyle);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(style);
    TabContentModelNG::SetLabelStyle(frameNode, *style);
}

void SetLabelUnselectedColorByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetLabelUnselectedColorByUser(frameNode, isByUser);
}

void SetLabelSelectedColorByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetLabelSelectedColorByUser(frameNode, isByUser);
}

void SetPadding(ArkUINodeHandle node, void* padding, ArkUI_Bool isSubTabStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    (void)isSubTabStyle;
    auto* paddingProperty = reinterpret_cast<PaddingProperty*>(padding);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(paddingProperty);
    TabContentModelNG::SetPadding(frameNode, *paddingProperty);
}

void SetUseLocalizedPadding(ArkUINodeHandle node, ArkUI_Bool useLocalizedPadding)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetUseLocalizedPadding(frameNode, useLocalizedPadding);
}

void CreatePaddingHorWithResourceObj(ArkUINodeHandle node, void* paramRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* param = reinterpret_cast<TabContentPaddingResourceObjParam*>(paramRawPtr);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(param);
    auto firstResObj = param->firstResourceObj ? AceType::Claim(param->firstResourceObj) : nullptr;
    auto secondResObj = param->secondResourceObj ? AceType::Claim(param->secondResourceObj) : nullptr;
    TabContentModelNG::CreatePaddingLeftWithResourceObj(frameNode, firstResObj,
        param->isSubTabStyle, param->useLocalizedPadding);
    TabContentModelNG::CreatePaddingRightWithResourceObj(frameNode, secondResObj,
        param->isSubTabStyle, param->useLocalizedPadding);
}

void CreatePaddingVerWithResourceObj(ArkUINodeHandle node, void* paramRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* param = reinterpret_cast<TabContentPaddingResourceObjParam*>(paramRawPtr);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(param);
    auto firstResObj = param->firstResourceObj ? AceType::Claim(param->firstResourceObj) : nullptr;
    auto secondResObj = param->secondResourceObj ? AceType::Claim(param->secondResourceObj) : nullptr;
    TabContentModelNG::CreatePaddingTopWithResourceObj(frameNode, firstResObj,
        param->isSubTabStyle, param->useLocalizedPadding);
    TabContentModelNG::CreatePaddingBottomWithResourceObj(frameNode, secondResObj,
        param->isSubTabStyle, param->useLocalizedPadding);
}

void SetLayoutMode(ArkUINodeHandle node, ArkUI_Int32 layoutMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetLayoutMode(frameNode, static_cast<LayoutMode>(layoutMode));
}

void SetVerticalAlign(ArkUINodeHandle node, ArkUI_Int32 verticalAlign)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetVerticalAlign(frameNode, static_cast<FlexAlign>(verticalAlign));
}

void SetSymmetricExtensible(ArkUINodeHandle node, ArkUI_Bool isExtensible)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetSymmetricExtensible(frameNode, isExtensible);
}

void SetIconStyle(ArkUINodeHandle node, void* iconStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* style = reinterpret_cast<IconStyle*>(iconStyle);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(style);
    TabContentModelNG::SetIconStyle(frameNode, *style);
}

void SetIconUnselectedColorByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetIconUnselectedColorByUser(frameNode, isByUser);
}

void SetIconSelectedColorByUser(ArkUINodeHandle node, ArkUI_Bool isByUser)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetIconSelectedColorByUser(frameNode, isByUser);
}

void SetId(ArkUINodeHandle node, ArkUI_CharPtr id)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(id);
    TabContentModelNG::SetId(frameNode, std::string(id));
}

void SetTabBar(ArkUINodeHandle node, void* paramRawPtr, bool fromJsView)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* param = reinterpret_cast<TabContentTabBarParam*>(paramRawPtr);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(param);
    TabContentModelNG::SetTabBarStyle(frameNode, param->style);
    if (param->builder) {
        TabContentModelNG::SetTabBar(frameNode, param->text, param->icon, param->tabBarSymbol,
            std::move(*param->builder), fromJsView);
    } else {
        TabContentModelNG::SetTabBar(frameNode, param->text, param->icon, param->tabBarSymbol, nullptr, fromJsView);
    }
    if (param->content) {
        TabContentModelNG::SetTabBarWithContent(frameNode, AceType::Claim(param->content));
    } else {
        TabContentModelNG::SetTabBarWithContent(frameNode, nullptr);
    }
}

void SetTabContentBuilder(ArkUINodeHandle node, ArkUI_Int32 methodId)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto builder = [methodId]() {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        ArkUIEventCallbackArg args[] = {};
        auto dispatch = ViewModel::GetCallbackMethod();
        CHECK_NULL_VOID(dispatch);
        auto vmContext = reinterpret_cast<ArkUIVMContext>(nativeEngine);
        CHECK_NULL_VOID(vmContext);
        dispatch->CallInt(vmContext, methodId, 0, args);
    };
    TabContentModelNG::SetTabBarBuilder(frameNode, std::move(builder));
}

void SetTabContentLabel(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetTabBarLabel(frameNode, label);

    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    TabContentModelNG::CreateTextContentWithResourceObj(frameNode, nullptr);
}

void SetTabContentOnWillShow(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillShow = reinterpret_cast<std::function<void()>*>(callback);
        TabContentModelNG::SetOnWillShow(frameNode, std::move(*onWillShow));
    } else {
        TabContentModelNG::SetOnWillShow(frameNode, nullptr);
    }
}

void ResetTabContentOnWillShow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetOnWillShow(frameNode, nullptr);
}

void SetTabContentOnWillHide(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onWillHide = reinterpret_cast<std::function<void()>*>(callback);
        TabContentModelNG::SetOnWillHide(frameNode, std::move(*onWillHide));
    } else {
        TabContentModelNG::SetOnWillHide(frameNode, nullptr);
    }
}

void ResetTabContentOnWillHide(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TabContentModelNG::SetOnWillHide(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUITabContentModifier* GetTabContentDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUITabContentModifier modifier = {
            .createTabContent = CreateTabContent,
            .popTabContent = PopTabContent,
            .setTabContentBuilder = SetTabContentBuilder,
            .setTabContentLabel = SetTabContentLabel,
            .setTabContentOnWillShow = SetTabContentOnWillShow,
            .resetTabContentOnWillShow = ResetTabContentOnWillShow,
            .setTabContentOnWillHide = SetTabContentOnWillHide,
            .resetTabContentOnWillHide = ResetTabContentOnWillHide,
            .createWithResourceObj = CreateTabContentWithResourceObj,
            .setCustomStyleNode = SetCustomStyleNode,
            .setDrawableIndicatorConfig = SetDrawableIndicatorConfig,
            .setDrawableIndicatorFlag = SetDrawableIndicatorFlag,
            .setIndicatorColorByUser = SetIndicatorColorByUser,
            .setIndicator = SetIndicator,
            .setSelectedMode = SetSelectedMode,
            .setBoard = SetBoard,
            .setLabelStyle = SetLabelStyle,
            .setLabelUnselectedColorByUser = SetLabelUnselectedColorByUser,
            .setLabelSelectedColorByUser = SetLabelSelectedColorByUser,
            .setPadding = SetPadding,
            .setUseLocalizedPadding = SetUseLocalizedPadding,
            .createPaddingHorWithResourceObj = CreatePaddingHorWithResourceObj,
            .createPaddingVerWithResourceObj = CreatePaddingVerWithResourceObj,
            .setLayoutMode = SetLayoutMode,
            .setVerticalAlign = SetVerticalAlign,
            .setSymmetricExtensible = SetSymmetricExtensible,
            .setIconStyle = SetIconStyle,
            .setIconUnselectedColorByUser = SetIconUnselectedColorByUser,
            .setIconSelectedColorByUser = SetIconSelectedColorByUser,
            .setId = SetId,
            .setTabBar = SetTabBar,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
#ifndef CROSS_PLATFORM
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITabContentModifier modifier = {
        .createTabContent = CreateTabContentImpl,
        .popTabContent = PopTabContentImpl,
        .setTabContentBuilder = SetTabContentBuilderImpl,
        .setTabContentLabel = SetTabContentLabelImpl,
        .setTabContentOnWillShow = SetTabContentOnWillShowImpl,
        .resetTabContentOnWillShow = ResetTabContentOnWillShowImpl,
        .setTabContentOnWillHide = SetTabContentOnWillHideImpl,
        .resetTabContentOnWillHide = ResetTabContentOnWillHideImpl,
        .createWithResourceObj = CreateWithResourceObjImpl,
        .setCustomStyleNode = SetCustomStyleNodeImpl,
        .setDrawableIndicatorConfig = SetDrawableIndicatorConfigImpl,
        .setDrawableIndicatorFlag = SetDrawableIndicatorFlagImpl,
        .setIndicatorColorByUser = SetIndicatorColorByUserImpl,
        .setIndicator = SetIndicatorImpl,
        .setSelectedMode = SetSelectedModeImpl,
        .setBoard = SetBoardImpl,
        .setLabelStyle = SetLabelStyleImpl,
        .setLabelUnselectedColorByUser = SetLabelUnselectedColorByUserImpl,
        .setLabelSelectedColorByUser = SetLabelSelectedColorByUserImpl,
        .setPadding = SetPaddingImpl,
        .setUseLocalizedPadding = SetUseLocalizedPaddingImpl,
        .createPaddingHorWithResourceObj = CreatePaddingHorWithResourceObjImpl,
        .createPaddingVerWithResourceObj = CreatePaddingVerWithResourceObjImpl,
        .setLayoutMode = SetLayoutModeImpl,
        .setVerticalAlign = SetVerticalAlignImpl,
        .setSymmetricExtensible = SetSymmetricExtensibleImpl,
        .setIconStyle = SetIconStyleImpl,
        .setIconUnselectedColorByUser = SetIconUnselectedColorByUserImpl,
        .setIconSelectedColorByUser = SetIconSelectedColorByUserImpl,
        .setId = SetIdImpl,
        .setTabBar = SetTabBarImpl,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
#else
    return nullptr;
#endif
}

const CJUITabContentModifier* GetCJUITabContentModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITabContentModifier modifier = {
        .setTabContentBuilder = SetTabContentBuilder,
        .setTabContentLabel = SetTabContentLabel,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
