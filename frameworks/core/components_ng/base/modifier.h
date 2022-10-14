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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H

#include <atomic>
#include <cstdint>
#include <functional>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/modifier_adapter.h"

namespace OHOS::Ace::NG {

class Modifier : public virtual AceType {
    DECLARE_ACE_TYPE(Modifier, AceType);

public:
    Modifier() {
        static std::atomic<int32_t> genId = 0;
        id_ = genId.fetch_add(1, std::memory_order_relaxed);
    }
    ~Modifier() override {
        ModifierAdapter::RemoveModifier(id_);
    }

    int32_t GetId() const
    {
        return id_;
    }

private:
    int32_t id_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(Modifier);
};

class AnimatablePropBase : public virtual AceType {
    DECLARE_ACE_TYPE(AnimatablePropBase, AceType);

public:
    AnimatablePropBase() = default;
    ~AnimatablePropBase() override = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(AnimatablePropBase);
};

struct AnimateConfig {
    float speed = 1.0f;
    int repeatTimes = -1;
    bool autoReverse = false;
};

struct DrawingContext {
    RSCanvas& canvas;
    float width = 0;
    float height = 0;
};

template<typename T>
class AnimatableProp : public AnimatablePropBase {
    DECLARE_ACE_TYPE(AnimatableProp, AnimatablePropBase);

public:
    AnimatableProp(const T& value) : value_(value) {}
    ~AnimatableProp() override = default;

    void SetUpCallbacks(std::function<T()>&& getFunc, std::function<void(const T&)>&& setFunc,
        std::function<void(const AnimateConfig&, const T&)> setWithAnimationFunc)
    {
        getFunc_ = getFunc;
        setFunc_ = setFunc;
        setWithAnimationFunc_ = setWithAnimationFunc;
    }

    T Get()
    {
        if (getFunc_) {
            return getFunc_();
        } else {
            return value_;
        }
    }

    void Set(const T& value)
    {
        if (setFunc_) {
            setFunc_(value);
        } else {
            value_ = value;
        }
    }

    void SetWithAnimation(const AnimateConfig& config, const T& value)
    {
        if (setWithAnimationFunc_) {
            setWithAnimationFunc_(config, value);
        } else {
            value_ = value;
        }
    }

private:
    T value_;
    std::function<T()> getFunc_;
    std::function<void(const T&)> setFunc_;
    std::function<void(const AnimateConfig&, const T&)> setWithAnimationFunc_;
    ACE_DISALLOW_COPY_AND_MOVE(AnimatableProp);
};

class ContentModifier : public Modifier {
    DECLARE_ACE_TYPE(ContentModifier, Modifier);

public:
    ContentModifier() = default;
    ~ContentModifier() override = default;
    virtual void onDraw(DrawingContext& Context) = 0;

    void AttachProp(const RefPtr<AnimatablePropBase>& prop)
    {
        attachedProps_.push_back(prop);
    }

    const std::vector<RefPtr<AnimatablePropBase>>& GetAttachedProps()
    {
        return attachedProps_;
    }

private:
    std::vector<RefPtr<AnimatablePropBase>> attachedProps_;
    ACE_DISALLOW_COPY_AND_MOVE(ContentModifier);
};

#define DECLARE_PROP_TYPED_CLASS(classname, template_class, type) \
    class classname : public template_class<type> {               \
        DECLARE_ACE_TYPE(classname, template_class);              \
                                                                  \
    public:                                                       \
        explicit classname(type value) : template_class(value) {} \
        ~classname() override = default;                          \
        ACE_DISALLOW_COPY_AND_MOVE(classname);                    \
    };

DECLARE_PROP_TYPED_CLASS(AnimatablePropFloat, AnimatableProp, float);

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H
