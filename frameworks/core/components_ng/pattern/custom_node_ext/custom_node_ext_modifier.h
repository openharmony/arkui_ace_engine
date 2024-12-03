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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_MODIFIER_H

#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
using DrawFunction = std::function<void(DrawingContext& context)>;
class CustomNodeExtContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(CustomNodeExtContentModifier, ContentModifier);
public:
    explicit CustomNodeExtContentModifier(DrawFunction&& drawCallback) : drawCallback_(std::move(drawCallback))
    {
        renderFlag_ = AceType::MakeRefPtr<PropertyInt>(0);
        AttachProperty(renderFlag_);
    }

    ~CustomNodeExtContentModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        if (drawCallback_) {
            drawCallback_(context);
        }
    }
private:
    DrawFunction drawCallback_;
    RefPtr<PropertyInt> renderFlag_;
};

class CustomNodeExtForegroundModifier : public ForegroundModifier {
    DECLARE_ACE_TYPE(CustomNodeExtForegroundModifier, ForegroundModifier);
public:
    explicit CustomNodeExtForegroundModifier(DrawFunction&& drawCallback) : drawCallback_(std::move(drawCallback))
    {
        renderFlag_ = AceType::MakeRefPtr<PropertyInt>(0);
        AttachProperty(renderFlag_);
    }

    ~CustomNodeExtForegroundModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        if (drawCallback_) {
            drawCallback_(context);
        }
    }
private:
    DrawFunction drawCallback_;
    RefPtr<PropertyInt> renderFlag_;
};

class CustomNodeExtOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(CustomNodeExtOverlayModifier, OverlayModifier);
public:
    explicit CustomNodeExtOverlayModifier(DrawFunction&& drawCallback) : drawCallback_(std::move(drawCallback))
    {
        renderFlag_ = AceType::MakeRefPtr<PropertyInt>(0);
        AttachProperty(renderFlag_);
    }

    ~CustomNodeExtOverlayModifier() override = default;

    void onDraw(DrawingContext& context) override
    {
        if (drawCallback_) {
            drawCallback_(context);
        }
    }
private:
    DrawFunction drawCallback_;
    RefPtr<PropertyInt> renderFlag_;
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_NODE_EXT_CUSTOM_NODE_EXT_MODIFIER_H