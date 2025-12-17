/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"
#include "nav_path_stack_peer_impl.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_uiObserver_NavigationInfo& dst, const std::shared_ptr<OHOS::Ace::NG::NavigationInfo>& src,
    ConvContext *ctx)
{
    CHECK_NULL_VOID(src);
    dst.navigationId = ArkValue<Ark_String>(src->navigationId, ctx);
    dst.pathStack = new NavPathStackPeer(src->pathStack.Upgrade());
    dst.uniqueId = ArkValue<Opt_Int32>(src->uniqueId);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UIContextGetInfoAccessor {
Opt_uiObserver_NavigationInfo GetNavigationInfoByUniqueIdImpl(Ark_Int64 id)
{
    auto retVal = Converter::ArkValue<Opt_uiObserver_NavigationInfo>();
    CHECK_NULL_RETURN(id, retVal);
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, retVal);
    auto navigationMgr = pipeline->GetNavigationManager();
    CHECK_NULL_RETURN(navigationMgr, retVal);
    auto nodeId = Converter::Convert<int64_t>(id);
    auto nodePtr = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId));
    CHECK_NULL_RETURN(nodePtr, retVal);
    auto result = navigationMgr->GetNavigationInfo(nodePtr);
    CHECK_NULL_RETURN(result, retVal);
    return Converter::ArkValue<Opt_uiObserver_NavigationInfo>(result, Converter::FC);
}

void EnableSwipeBackImpl(const Opt_Boolean* enabled)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto enabledVal = Converter::OptConvertPtr<bool>(enabled);
    if (!enabledVal) {
        pipeline->SetEnableSwipeBack(true);
        return;
    }
    pipeline->SetEnableSwipeBack(*enabledVal);
}
} // UIContextGetInfoAccessor
const GENERATED_ArkUIUIContextGetInfoAccessor* GetUIContextGetInfoAccessor()
{
    static const GENERATED_ArkUIUIContextGetInfoAccessor UIContextGetInfoAccessorImpl {
        UIContextGetInfoAccessor::GetNavigationInfoByUniqueIdImpl,
        UIContextGetInfoAccessor::EnableSwipeBackImpl,
    };
    return &UIContextGetInfoAccessorImpl;
}

}