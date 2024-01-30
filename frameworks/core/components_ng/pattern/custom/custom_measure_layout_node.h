/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_MEASURE_LAYOUT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_MEASURE_LAYOUT_NODE_H

#include <functional>
#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_param.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/custom/custom_node_base.h"
#include "core/components_ng/pattern/custom/custom_node_pattern.h"

namespace OHOS::Ace::NG {

// CustomMeasureLayoutNode is the frame node of @Component struct.
class ACE_EXPORT CustomMeasureLayoutNode : public FrameNode, public CustomNodeBase {
    DECLARE_ACE_TYPE(CustomMeasureLayoutNode, FrameNode, CustomNodeBase);

public:
    static RefPtr<CustomMeasureLayoutNode> CreateCustomMeasureLayoutNode(int32_t nodeId, const std::string& viewKey);

    CustomMeasureLayoutNode(int32_t nodeId, const std::string& viewKey);
    ~CustomMeasureLayoutNode() override = default;

    void SetRenderFunction(const RenderFunction& renderFunction) override
    {
        auto pattern = DynamicCast<CustomNodePattern>(GetPattern());
        if (pattern) {
            pattern->SetRenderFunction(renderFunction);
        }
    }

    bool FireOnMeasure(LayoutWrapper* layoutWrapper);

    bool FireOnLayout(LayoutWrapper* layoutWrapper);

    void SetLayoutFunction(std::function<void(LayoutWrapper* layoutWrapper)>&& layoutFunc)
    {
        layoutFunc_ = std::move(layoutFunc);
    }

    void SetMeasureFunction(std::function<void(LayoutWrapper* layoutWrapper)>&& measureFunc)
    {
        measureFunc_ = std::move(measureFunc);
    }
    void SetCompleteReloadFunc(RenderFunction&& func) override {}

    RefPtr<MeasureLayoutParam> GetMeasureLayoutParam() const
    {
        return measureLayoutParam_;
    }
    void SetMeasureLayoutParam(RefPtr<MeasureLayoutParam> param)
    {
        measureLayoutParam_ = param;
    }
    void SetUpdateParamFunc(std::function<void(LayoutWrapper* layoutWrapper)>&& updateParamFunc)
    {
        updateParamFunc_ = updateParamFunc;
    }
    bool FireOnUpdateParam(NG::LayoutWrapper* layoutWrapper);
    bool UpdateSize(int32_t index, SizeF size)
    {
        CHECK_NULL_RETURN(measureLayoutParam_, false);
        CHECK_NULL_RETURN(measureLayoutParam_->ChildIndexInRange(index), false);
        auto childParam = measureLayoutParam_->Get(index);
        childParam.UpdateSize(size);
        return true;
    }

private:
    void BuildChildren(const RefPtr<FrameNode>& child);
    std::function<void(LayoutWrapper* layoutWrapper)> layoutFunc_;
    std::function<void(LayoutWrapper* layoutWrapper)> measureFunc_;
    std::function<void(LayoutWrapper* layoutWrapper)> updateParamFunc_;
    std::string viewKey_;
    RefPtr<MeasureLayoutParam> measureLayoutParam_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H
