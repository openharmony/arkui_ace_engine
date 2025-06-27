/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "custom_node_ani_modifier.h"
 
#include <memory>
 
#include "base/log/log.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_static.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/interfaces/native/implementation/nav_path_stack_peer_impl.h"
#include "core/interfaces/native/implementation/navigation_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ani_long ConstructCustomNode(ani_int id, std::function<void()>&& onPageShow, std::function<void()>&& onPageHide,
    std::function<bool()>&& onBackPress, std::function<void()>&& pageTransitionFunc,
    std::function<void()>&& onCleanupFunc, std::function<std::string()>&& onDumpInspectorFunc)
{
    std::string key = NG::ViewStackProcessor::GetInstance()->ProcessViewId(std::to_string(id));
    struct NodeKoalaInfo info {
        .onPageShowFunc = std::move(onPageShow),
        .onPageHideFunc = std::move(onPageHide),
        .onBackPressedFunc = std::move(onBackPress),
        .pageTransitionFunc = std::move(pageTransitionFunc),
        .onCleanupFunc = std::move(onCleanupFunc),
        .onDumpInspectorFunc = std::move(onDumpInspectorFunc),
        .jsViewName = key
    };
    auto customNode = NG::CustomNodeStatic::ConstructCustomNode(id, std::move(info));
    if (customNode) {
        return reinterpret_cast<ani_long>(customNode);
    }
    return 0;
}

void RequestFrame()
{
    auto context = NG::PipelineContext::GetCurrentContextSafely();
    if (context == nullptr) {
        TAG_LOGE(AceLogTag::ACE_STATE_MGMT, "RequestFrame-ani can not get current context.");
        return;
    }
    context->RequestFrame();
}

RefPtr<UINode> GetTargetNode(const RefPtr<AceType>& node, const std::string& tag, bool isInner, bool needCheckParent)
{
    // needChcekParent flag is intended to maintain the original logic unchanged, when tag is
    // V2::NAVDESTINATION_VIEW_ETS_TAG.
    auto current = AceType::DynamicCast<UINode>(node);
    while (current) {
        if (current->GetTag() == tag) {
            if (!needCheckParent) {
                break;
            }
            if (current->GetParent() && current->GetParent()->GetTag() == V2::NAVIGATION_CONTENT_ETS_TAG) {
                break;
            }
        }
        current = isInner ? current->GetFirstChild() : current->GetParent();
    }
    return current;
}

ani_object QueryNavigationInfo(ani_env* env, ani_long node)
{
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_RETURN(customNode, {});
    auto pipeline = customNode->GetContext();
    CHECK_NULL_RETURN(pipeline, {});
    auto navigationMgr = pipeline->GetNavigationManager();
    CHECK_NULL_RETURN(navigationMgr, {});
    auto result = navigationMgr->GetNavigationInfo(AceType::Claim(customNode));
    CHECK_NULL_RETURN(result, {});
    auto stack = result->pathStack.Upgrade();
    CHECK_NULL_RETURN(stack, {});
    NavPathStackPeer* ptr = new NavPathStackPeer(stack);

    ani_object res = {};
    static const char* className = "@ohos.arkui.observer.uiObserver.NavigationInfoImpl";
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method navInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &navInfoCtor);
    env->Object_New(cls, navInfoCtor, &res);

    // set navigationId
    std::string navigationId = result->navigationId;
    ani_string id_string{};
    env->String_NewUTF8(navigationId.c_str(), navigationId.size(), &id_string);
    env->Object_SetPropertyByName_Ref(res, "navigationId", id_string);
    
    // set pathStack
    ani_class interCls;
    env->FindClass("arkui.component.navigation.NavPathStackInternal", &interCls);
    ani_ref pathStack;
    env->Class_CallStaticMethodByName_Ref(interCls, "fromPtr", nullptr, &pathStack, reinterpret_cast<ani_ref>(ptr));
    env->Object_SetPropertyByName_Ref(res, "pathStack", static_cast<ani_object>(pathStack));
    
    return res;
}

ani_object QueryRouterPageInfo(ani_env* env, ani_long node)
{
    ani_object res = {};
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_RETURN(customNode, {});
    
    auto curNode = GetTargetNode(AceType::Claim(customNode), V2::PAGE_ETS_TAG, false, false);
    auto pageNode = AceType::DynamicCast<FrameNode>(curNode);
    CHECK_NULL_RETURN(pageNode, res);
    auto pattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pattern, res);
    auto pageInfo = pattern->GetPageInfo();
    static const char* className = "@ohos.arkui.observer.uiObserver.RouterPageInfo";
    ani_status status = ANI_OK;
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);

    env->Object_SetPropertyByName_Double(res, "index", static_cast<ani_double>(pageInfo->GetPageIndex()));

    ani_string pageName{};
    env->String_NewUTF8(pageInfo->GetPageUrl().c_str(), pageInfo->GetPageUrl().size(), &pageName);
    env->Object_SetPropertyByName_Ref(res, "name", pageName);

    ani_string pagePath{};
    env->String_NewUTF8(pageInfo->GetPagePath().c_str(), pageInfo->GetPagePath().size(), &pagePath);
    env->Object_SetPropertyByName_Ref(res, "path", pagePath);
    env->Object_SetPropertyByName_Int(res, "state", static_cast<ani_int>(pattern->GetPageState()));

    ani_string aniPageId{};
    std::string pageId = std::to_string(pageInfo->GetPageId());
    env->String_NewUTF8(pageId.c_str(), pageId.size(), &aniPageId);
    env->Object_SetPropertyByName_Ref(res, "pageId", aniPageId);

    ani_enum routerPgaeState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.RouterPageState", &routerPgaeState);
    ani_enum_item enumItem;
    env->Enum_GetEnumItemByIndex(routerPgaeState, static_cast<ani_size>(pattern->GetPageState()), &enumItem);
    env->Object_SetPropertyByName_Ref(res, "state", enumItem);

    return res;
}

void GetNavDestinationInfo(ani_env* env, ani_object& res, RefPtr<UINode> node)
{
    auto nav = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(nav);
    auto pattern = nav->GetPattern<NavDestinationPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = AceType::DynamicCast<NavDestinationGroupNode>(pattern->GetHost());
    CHECK_NULL_VOID(host);
    auto pathInfo = pattern->GetNavPathInfo();
    CHECK_NULL_VOID(pathInfo);
    NavDestinationState state = NavDestinationState::NONE;
    NavDestinationMode mode = host->GetNavDestinationMode();
    auto uniqueId = host->GetId();
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        state = pattern->GetNavDestinationState();
        if (state == NavDestinationState::NONE) {
            return;
        }
    } else {
        state = pattern->GetIsOnShow() ? NavDestinationState::ON_SHOWN : NavDestinationState::ON_HIDDEN;
    }

    static const char* className = "@ohos.arkui.observer.uiObserver.NavDestinationInfoImpl";
    ani_status status = ANI_OK;
    ani_class cls;
    env->FindClass(className, &cls);
    ani_method routerInfoCtor;
    env->Class_FindMethod(cls, "<ctor>", nullptr, &routerInfoCtor);
    env->Object_New(cls, routerInfoCtor, &res);

    env->Object_SetPropertyByName_Double(res, "uniqueId", static_cast<ani_double>(host->GetId()));
    env->Object_SetPropertyByName_Int(res, "index", static_cast<ani_int>(host->GetIndex()));

    ani_string navDesName {};
    env->String_NewUTF8(pattern->GetName().c_str(), pattern->GetName().size(), &navDesName);
    env->Object_SetPropertyByName_Ref(res, "name", navDesName);

    ani_string navDesId {};
    env->String_NewUTF8(std::to_string(pattern->GetNavDestinationId()).c_str(),
        std::to_string(pattern->GetNavDestinationId()).size(), &navDesId);
    env->Object_SetPropertyByName_Ref(res, "navDestinationId", navDesId);

    ani_string navigationId {};
    env->String_NewUTF8(pattern->GetNavigationId().c_str(), pattern->GetNavigationId().size(), &navigationId);
    env->Object_SetPropertyByName_Ref(res, "navigationId", navigationId);
    
    ani_enum navDesState;
    env->FindEnum("@ohos.arkui.observer.uiObserver.NavDestinationState", &navDesState);
    ani_enum_item navDesStateItem;
    env->Enum_GetEnumItemByIndex(navDesState, static_cast<ani_size>(state), &navDesStateItem);
    env->Object_SetPropertyByName_Ref(res, "state", navDesStateItem);
    
    ani_enum navMode;
    env->FindEnum("@ohos.arkui.component.navDestination.NavDestinationMode", &navMode);
    ani_enum_item navModeItem;
    env->Enum_GetEnumItemByIndex(navMode, static_cast<ani_size>(mode), &navModeItem);
    env->Object_SetPropertyByName_Ref(res, "mode", navModeItem);
}

ani_object QueryNavDestinationInfo(ani_env* env, ani_long node)
{
    ani_object res = {};
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_RETURN(customNode, res);
    
    // get navdestination node
    auto current = GetTargetNode(AceType::Claim(customNode), V2::NAVDESTINATION_VIEW_ETS_TAG, false, false);
    CHECK_NULL_RETURN(current, res);

    GetNavDestinationInfo(env, res, current);
    return res;
}

ani_object QueryNavDestinationInfo0(ani_env* env, ani_long node, ani_int isInner)
{
    ani_object res = {};
    auto customNode = reinterpret_cast<CustomNode*>(node);
    CHECK_NULL_RETURN(customNode, res);
    auto current =
        GetTargetNode(AceType::Claim(customNode), V2::NAVDESTINATION_VIEW_ETS_TAG, static_cast<bool>(isInner), true);
    CHECK_NULL_RETURN(current, res);

    GetNavDestinationInfo(env, res, current);
    return res;
}

const ArkUIAniCustomNodeModifier* GetCustomNodeAniModifier()
{
    static const ArkUIAniCustomNodeModifier impl = {
        .constructCustomNode = OHOS::Ace::NG::ConstructCustomNode,
        .requestFrame = OHOS::Ace::NG::RequestFrame,
        .queryNavigationInfo = OHOS::Ace::NG::QueryNavigationInfo,
        .queryNavDestinationInfo = OHOS::Ace::NG::QueryNavDestinationInfo,
        .queryNavDestinationInfo0 = OHOS::Ace::NG::QueryNavDestinationInfo0,
        .queryRouterPageInfo = OHOS::Ace::NG::QueryRouterPageInfo
    };
    return &impl;
}

} // namespace OHOS::Ace::NG