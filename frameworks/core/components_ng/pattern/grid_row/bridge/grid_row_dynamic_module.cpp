/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid_row/bridge/grid_row_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/grid_row/bridge/arkts_native_grid_row_bridge.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"
#include "core/components_ng/property/measure_utils.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/grid_row/grid_row_model_ng_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_GridRow()
{
    return new OHOS::Ace::GridRowDynamicModule();
}

namespace OHOS::Ace {

namespace V2 {
const char GRID_COL_ETS_TAG[] = "GridCol";
const char GRID_ROW_ETS_TAG[] = "GridRow";
} // namespace V2

namespace NG {
void CreateChildrenConstraint(SizeF& size, const PaddingPropertyF& padding)
{
    float width = 0;
    float height = 0;

    float paddingLeft = padding.left.value_or(0);
    float paddingRight = padding.right.value_or(0);
    float paddingTop = padding.top.value_or(0);
    float paddingBottom = padding.bottom.value_or(0);
    width += (paddingLeft + paddingRight);
    height += (paddingTop + paddingBottom);

    size.SetHeight(size.Height() - height);
    size.SetWidth(size.Width() - width);
}

const ArkUIGridRowModifier* GetGridRowDynamicModifier();
const CJUIGridRowModifier* GetCJUIGridRowModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIGridRowModifier* GetGridRowStaticModifier();
}
#endif
} // namespace NG

void GridRowDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::GridRowBridge::RegisterGridRowAttributes(object, vm);
}

const void* GridRowDynamicModule::GetDynamicModifier()
{
    return NG::GetGridRowDynamicModifier();
}

const void* GridRowDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetGridRowStaticModifier();
#else
    return nullptr;
#endif
}

const void* GridRowDynamicModule::GetCjModifier()
{
    return NG::GetCJUIGridRowModifier();
}

void* GridRowDynamicModule::GetModel()
{
    static NG::GridRowModelNG model;
    return &model;
}

} // namespace OHOS::Ace