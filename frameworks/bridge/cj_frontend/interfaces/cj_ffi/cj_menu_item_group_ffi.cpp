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

#include "cj_menu_item_group_ffi.h"
#include "cj_lambda.h"

#include "base/log/log_wrapper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
namespace OHOS::Ace {
// Should use CJUIModifier API later
NG::MenuItemGroupView* GetMenuItemGroupModel()
{
    static NG::MenuItemGroupView* model = nullptr;
    if (model == nullptr) {
    auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("MenuItemGroup");
        if (module == nullptr) {
            LOGF("Can't find MenuItem dynamic module");
            abort();
        }
        model = reinterpret_cast<NG::MenuItemGroupView*>(module->GetModel());
    }
    return model;
}
} // namespace OHOS::Ace

extern "C" {
void FfiOHOSAceFrameworkMenuItemGroupCreateByString(const char* header, const char* footer)
{
    GetMenuItemGroupModel()->CreateCJ();
    std::string headerStr = header;
    std::string footerStr = footer;
    if (!headerStr.empty()) {
        GetMenuItemGroupModel()->SetHeaderCJ(headerStr);
    }
    if (!footerStr.empty()) {
        GetMenuItemGroupModel()->SetFooterCJ(footerStr);
    }
}

void FfiOHOSAceFrameworkMenuItemGroupCreateByBuilder(void(*header)(), void(*footer)())
{
    GetMenuItemGroupModel()->CreateCJ();
    RefPtr<NG::UINode> rheader;
    {
        auto headerBuilderFunc = CJLambda::Create(header);
        CHECK_NULL_VOID(headerBuilderFunc);
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        headerBuilderFunc();
        rheader = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(rheader);
    }
    GetMenuItemGroupModel()->SetHeaderCJ(rheader);
    RefPtr<NG::UINode> rfooter;
    {
        auto footerBuilderFunc = CJLambda::Create(footer);
        CHECK_NULL_VOID(footerBuilderFunc);
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footerBuilderFunc();
        rfooter = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(rfooter);
    }
    GetMenuItemGroupModel()->SetFooterCJ(rfooter);
}
}