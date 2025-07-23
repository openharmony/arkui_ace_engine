/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_CUSTOM_ANI_MEASURE_LAYOUT
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_CUSTOM_ANI_MEASURE_LAYOUT

#include <utility>
#include <memory>
#include "ani.h"

#include "log/log.h"
#include "utils/ani_utils.h"
#include "base/memory/ace_type.h"
#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/pipeline/pipeline_base.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/base/geometry_node.h"

namespace OHOS::Ace::Ani {

// used for ets interface onMeasureSize and onPlaceChildren
class ACE_FORCE_EXPORT JSMeasureLayoutParamNG : public NG::MeasureLayoutParam {
    DECLARE_ACE_TYPE(JSMeasureLayoutParamNG, NG::MeasureLayoutParam);
public:
    JSMeasureLayoutParamNG(NG::LayoutWrapper* layoutWrapper, ani_env* env);
    ~JSMeasureLayoutParamNG() {}

    void Init() override {};
    void Init(ani_env* env);

    void Update(NG::LayoutWrapper* layoutWrapper) override {};
    void Update(ani_env* env,  NG::LayoutWrapper* layoutWrapper);

    static RefPtr<JSMeasureLayoutParamNG> GetInstance(NG::LayoutWrapper* layoutWrapper, ani_env* env);
    ani_object GetSelfLayoutInfo(ani_env* env);
    ani_object GetConstraint(ani_env* env);
    ani_object GetPlaceChildrenConstraint(ani_env* env);
    ani_ref GetChildArray(ani_env* env) {
        return childArray_.get();
    }
    void GenChildArray(ani_env* env, int32_t start, int32_t end);
    
    using AniArrayRef =  std::remove_reference_t<decltype(*static_cast<ani_array_ref>(nullptr))>;

    std::shared_ptr<AniArrayRef> childArray_;
    std::function<void(ani_array_ref)> deleter_;

};

bool ParseAniDimensionVp(ani_env* env, ani_object obj, CalcDimension& result);
bool ParseAniDimension(ani_env* env, ani_object obj, CalcDimension& result, DimensionUnit defaultUnit);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_CUSTOM_ANI_MEASURE_LAYOUT