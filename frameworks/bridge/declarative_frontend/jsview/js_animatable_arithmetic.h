/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_ANIMATABLE_ARITHMETIC_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_ANIMATABLE_ARITHMETIC_H

#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components_ng/animation/animatable_arithmetic.h"

namespace OHOS::Ace::Framework {
using OHOS::Ace::NG::CustomAnimatableArithmetic;

class JSAnimatableArithmetic : public CustomAnimatableArithmetic {
    DECLARE_ACE_TYPE(JSAnimatableArithmetic, CustomAnimatableArithmetic)
public:
    JSAnimatableArithmetic() = default;
    ~JSAnimatableArithmetic() override = default;

    explicit JSAnimatableArithmetic(const JSRef<JSObject>& jsObject, JSExecutionContext ctx)
        : jsObject_(jsObject), ctx_(ctx)
    {
        auto addVal = jsObject_->GetProperty("plus");
        if (addVal->IsFunction()) {
            addFunc_ = JSRef<JSFunc>::Cast(addVal);
        }
        auto minusVal = jsObject_->GetProperty("subtract");
        if (minusVal->IsFunction()) {
            minusFunc_ = JSRef<JSFunc>::Cast(minusVal);
        }
        auto multiplyVal = jsObject_->GetProperty("multiply");
        if (multiplyVal->IsFunction()) {
            multiplyFunc_ = JSRef<JSFunc>::Cast(multiplyVal);
        }
        auto equalsVal = jsObject_->GetProperty("equals");
        if (equalsVal->IsFunction()) {
            equalsFunc_ = JSRef<JSFunc>::Cast(equalsVal);
        }
    }

    RefPtr<CustomAnimatableArithmetic> Add(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<JSAnimatableArithmetic> rhs = AceType::DynamicCast<JSAnimatableArithmetic>(value);
        if (!rhs) {
            return {};
        }
        JAVASCRIPT_EXECUTION_SCOPE(ctx_);
        JSRef<JSVal> argv[1] = { rhs->jsObject_ };
        auto retVal = addFunc_->Call(jsObject_, 1, argv);
        if (!retVal->IsObject()) {
            return {};
        }

        return MakeRefPtr<JSAnimatableArithmetic>(JSRef<JSObject>::Cast(retVal), ctx_);
    }

    RefPtr<CustomAnimatableArithmetic> Minus(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<JSAnimatableArithmetic> rhs = AceType::DynamicCast<JSAnimatableArithmetic>(value);
        if (!rhs) {
            return {};
        }
        JAVASCRIPT_EXECUTION_SCOPE(ctx_);
        JSRef<JSVal> argv[1] = { rhs->jsObject_ };
        auto retVal = minusFunc_->Call(jsObject_, 1, argv);
        if (!retVal->IsObject()) {
            return {};
        }

        return MakeRefPtr<JSAnimatableArithmetic>(JSRef<JSObject>::Cast(retVal), ctx_);
    }

    RefPtr<CustomAnimatableArithmetic> Multiply(const float scale) const override
    {
        JAVASCRIPT_EXECUTION_SCOPE(ctx_);
        JSRef<JSVal> argv[1] = { JSRef<JSVal>::Make(ToJSValue(scale)) };
        auto retVal = multiplyFunc_->Call(jsObject_, 1, argv);
        if (!retVal->IsObject()) {
            return {};
        }

        return MakeRefPtr<JSAnimatableArithmetic>(JSRef<JSObject>::Cast(retVal), ctx_);
    }

    bool IsEqual(const RefPtr<CustomAnimatableArithmetic>& value) const override
    {
        RefPtr<JSAnimatableArithmetic> rhs = AceType::DynamicCast<JSAnimatableArithmetic>(value);
        if (!rhs) {
            return false;
        }

        JAVASCRIPT_EXECUTION_SCOPE(ctx_);
        JSRef<JSVal> argv[1] = { rhs->jsObject_ };
        auto retVal = equalsFunc_->Call(jsObject_, 1, argv);
        if (!retVal->IsBoolean()) {
            return false;
        }

        return retVal->ToBoolean();
    }

    JSRef<JSObject> GetObject() const
    {
        return jsObject_;
    }

private:
    JSRef<JSObject> jsObject_;
    JSExecutionContext ctx_;
    JSRef<JSFunc> addFunc_;
    JSRef<JSFunc> minusFunc_;
    JSRef<JSFunc> multiplyFunc_;
    JSRef<JSFunc> equalsFunc_;
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_ANIMATABLE_ARITHMETIC_H
