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

#include <functional>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

class Modifier : public virtual AceType {
    DECLARE_ACE_TYPE(Modifier, AceType);

public:
    Modifier() = default;
    ~Modifier() override = default;

private:
    ACE_DISALLOW_COPY_AND_MOVE(Modifier);
};

struct AnimateConfig {
    float speed = 1.0f;
    int repeatTimes = -1;
    bool autoReverse = false;
};

template<typename T>
class ContentModifier : public Modifier {
    DECLARE_ACE_TYPE(ContentModifier, Modifier);

public:
    explicit ContentModifier(T prop) : initValue_(prop) {}
    ~ContentModifier() override = default;
    virtual void onDraw(RSCanvas& canvas, const T& prop) = 0;
    T GetInitValue()
    {
        return initValue_;
    }

    void SetUpdateFunc(const std::function<void(const AnimateConfig&, const T&)>& updateFunc)
    {
        updateFunc_ = updateFunc;
    }
    void UpdateModifier(const AnimateConfig& config, const T& prop)
    {
        if (updateFunc_) {
            updateFunc_(config, prop);
        }
    }

private:
    T initValue_;
    std::function<void(const AnimateConfig&, const T&)> updateFunc_;
    ACE_DISALLOW_COPY_AND_MOVE(ContentModifier);
};

#define DECLARE_MODIFIER_TYPED_CLASS(classname, template_class, type) \
    class classname : public template_class<type> {                   \
        DECLARE_ACE_TYPE(classname, template_class);                  \
                                                                      \
    public:                                                           \
        explicit classname(type value) : template_class(value) {}     \
        ~classname() override = default;                              \
        ACE_DISALLOW_COPY_AND_MOVE(classname);                        \
    };

DECLARE_MODIFIER_TYPED_CLASS(ContentModifierFloat, ContentModifier, float);

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIER_H
