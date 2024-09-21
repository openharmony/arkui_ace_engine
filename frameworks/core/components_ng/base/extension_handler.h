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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_EXTENSION_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_EXTENSION_HANDLER_H

#include <cmath>
#include <cstdint>
#include <functional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {
struct ExtensionLayoutConstraint {
    int32_t maxWidth { 0 };
    int32_t minWidth { 0 };
    int32_t maxHeight { 0 };
    int32_t minHeight { 0 };
    int32_t parentIdealWidth { 0 };  // 设置百分比基准
    int32_t parentIdealHeight { 0 }; // 设置百分比基准

    static ExtensionLayoutConstraint Create(const LayoutConstraintF& layoutConstraintF);
};

class FrameNode;

class ACE_EXPORT ExtensionHandler : public virtual AceType {
    DECLARE_ACE_TYPE(ExtensionHandler, AceType);

public:
    void Measure(const ExtensionLayoutConstraint& layoutConstraint);
    void Layout(int32_t width, int32_t height, int32_t positionX, int32_t positionY);
    void Draw(DrawingContext& context);
    void ForegroundDraw(DrawingContext& context);
    void OverlayDraw(DrawingContext& context);

    // 调用封装内部原始布局，绘制方法。
    void InnerMeasure(const ExtensionLayoutConstraint& layoutConstraint);
    void InnerLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY);
    void InnerDraw(DrawingContext& context);
    void InnerForegroundDraw(DrawingContext& context);
    void InnerOverlayDraw(DrawingContext& context);

    void SetInnerMeasureImpl(std::function<void(const ExtensionLayoutConstraint&)>&& impl)
    {
        innerMeasureImpl_ = std::move(impl);
    }

    void SetInnerLayoutImpl(std::function<void(int32_t, int32_t, int32_t, int32_t)>&& impl)
    {
        innerLayoutImpl_ = std::move(impl);
    }

    void SetInnerDrawImpl(std::function<void(DrawingContext& Context)>&& impl)
    {
        innerDrawImpl_ = std::move(impl);
    }

    void SetInnerForegroundDrawImpl(std::function<void(DrawingContext& Context)>&& impl)
    {
        innerForegroundDrawImpl_ = std::move(impl);
    }

    void SetInnerOverlayDrawImpl(std::function<void(DrawingContext& Context)>&& impl)
    {
        innerOverlayDrawImpl_ = std::move(impl);
    }

    void InvalidateRender();

    void OverlayRender();

    void ForegroundRender();
    
    void SetInvalidateRenderImpl(std::function<void()>&& impl)
    {
        invalidateRender_ = std::move(impl);
    }

    void SetOverlayRenderImpl(std::function<void()>&& impl)
    {
        overlayRender_ = std::move(impl);
    }

    void SetForeGroundRenderImpl(std::function<void()>&& impl)
    {
        foreGroundRender_ = std::move(impl);
    }

    void SetDrawModifier(const RefPtr<NG::DrawModifier>& drawModifier)
    {
        drawModifier_ = drawModifier;
    }

    virtual bool HasCustomerMeasure() const
    {
        return false;
    }

    virtual bool HasCustomerLayout() const
    {
        return false;
    }

    virtual bool NeedRender() const
    {
        return drawModifier_ || needRender_ ;
    }

    void ResetNeedRender()
    {
        needRender_  = false;
    }

    bool HasDrawModifier()
    {
        return drawModifier_;
    }

    void AttachFrameNode(FrameNode* node)
    {
        node_ = node;
    }

protected:
    virtual void OnMeasure(const ExtensionLayoutConstraint& layoutConstraint);
    virtual void OnLayout(int32_t width, int32_t height, int32_t positionX, int32_t positionY);
    virtual void OnForegroundDraw(DrawingContext& context);
    virtual void OnDraw(DrawingContext& context);
    virtual void OnOverlayDraw(DrawingContext& context);
    
private:
    std::function<void(const ExtensionLayoutConstraint&)> innerMeasureImpl_;
    std::function<void(int32_t, int32_t, int32_t, int32_t)> innerLayoutImpl_;
    std::function<void(DrawingContext&)> innerDrawImpl_;
    std::function<void(DrawingContext&)> innerForegroundDrawImpl_;
    std::function<void(DrawingContext&)> innerOverlayDrawImpl_;
    std::function<void()> invalidateRender_;
    std::function<void()> overlayRender_;
    std::function<void()> foreGroundRender_;
    bool needRender_  = true;

    RefPtr<NG::DrawModifier> drawModifier_;
    FrameNode* node_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_EXTENSION_HANDLER_H
