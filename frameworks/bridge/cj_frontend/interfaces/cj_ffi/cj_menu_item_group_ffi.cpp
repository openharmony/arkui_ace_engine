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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkMenuItemGroupCreateByString(const char* header, const char* footer)
{
    NG::MenuItemGroupView::Create();
    std::string headerStr = header;
    std::string footerStr = footer;
    if (!headerStr.empty()) {
        NG::MenuItemGroupView::SetHeader(headerStr);
    }
    if (!footerStr.empty()) {
        NG::MenuItemGroupView::SetFooter(footerStr);
    }
}

void FfiOHOSAceFrameworkMenuItemGroupCreateByBuilder(void(*header)(), void(*footer)())
{
    NG::MenuItemGroupView::Create();
    RefPtr<NG::UINode> rheader;
    {
        auto headerBuilderFunc = CJLambda::Create(header);
        CHECK_NULL_VOID(headerBuilderFunc);
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        headerBuilderFunc();
        rheader = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(rheader);
    }
    NG::MenuItemGroupView::SetHeader(rheader);
    RefPtr<NG::UINode> rfooter;
    {
        auto footerBuilderFunc = CJLambda::Create(footer);
        CHECK_NULL_VOID(footerBuilderFunc);
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footerBuilderFunc();
        rfooter = NG::ViewStackProcessor::GetInstance()->Finish();
        CHECK_NULL_VOID(rfooter);
    }
    NG::MenuItemGroupView::SetFooter(rfooter);
}
}