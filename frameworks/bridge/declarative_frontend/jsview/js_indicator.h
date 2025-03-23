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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDICATOR_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDICATOR_H

#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/base/ui_node.h"
#include "frameworks/core/components_ng/pattern/swiper_indicator/indicator_common/indicator_controller.h"

namespace OHOS::Ace::Framework {
class JSIndicator : public JSViewAbstract {
public:
    static void JSBind(BindingTarget globalObj);
    static void Create(const JSCallbackInfo& info);

protected:
    static void SetLoop(const JSCallbackInfo& info);
    static void SetOnChange(const JSCallbackInfo& info);
    static void SetInitialIndex(const JSCallbackInfo& info);
    static void SetStyle(const JSCallbackInfo& info);
    static void SetCount(const JSCallbackInfo& info);
    static void SetVertical(const JSCallbackInfo& info);
    static SwiperParameters GetDotIndicatorInfo(const JSRef<JSObject>& obj);
    static SwiperDigitalParameters GetDigitIndicatorInfo(const JSRef<JSObject>& obj);
    static std::optional<Dimension> ParseIndicatorDimension(const JSRef<JSVal>& value);
    static std::optional<Dimension> ParseIndicatorBottom(const JSRef<JSVal>& bottomValue, bool hasIgnoreSize);
    static void GetFontContent(const JSRef<JSVal>& font, bool isSelected, SwiperDigitalParameters& digitalParameters);
    static void SetDotIndicatorInfo(const JSRef<JSObject>& obj, SwiperParameters& swiperParameters,
        const RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme);
};

class JSIndicatorController final : public Referenced {
public:
    JSIndicatorController() = default;
    ~JSIndicatorController() override = default;
    static void JSBind(BindingTarget globalObj);
    static void Constructor(const JSCallbackInfo& args);
    static void Destructor(JSIndicatorController* scroller);

    void ShowNext(const JSCallbackInfo& args)
    {
        if (controller_.Upgrade()) {
            ContainerScope scope(instanceId_);
            controller_.Upgrade()->ShowNext();
        }
    }

    void ShowPrevious(const JSCallbackInfo& args)
    {
        if (controller_.Upgrade()) {
            ContainerScope scope(instanceId_);
            controller_.Upgrade()->ShowPrevious();
        }
    }

    void ChangeIndex(const JSCallbackInfo& args);
    void SetController(const RefPtr<NG::IndicatorController>& controller, RefPtr<NG::FrameNode>& indicatorNode)
    {
        auto resetFunc = [wp = WeakClaim(this)]() {
            auto JSController = wp.Upgrade();
            if (JSController) {
                JSController->controller_ = nullptr;
            }
        };
        if (controller_.Upgrade()) {
            controller_.Upgrade()->ResetIndicatorControllor(controller, indicatorNode);
        }
        controller_ = controller;
        controller->SetJSIndicatorController(resetFunc);
        controller->SetSwiperNode(swiperNode_.Upgrade());
    }

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

    std::function<void()> SetSwiperNodeBySwiper(const RefPtr<NG::FrameNode>& node)
    {
        if (controller_.Upgrade()) {
            controller_.Upgrade()->SetSwiperNode(node);
        }
        if (node != swiperNode_) {
            swiperNode_ = node;
            return [wp = WeakClaim(this)]() {
                auto JSController = wp.Upgrade();
                if (JSController) {
                    JSController->swiperNode_ = nullptr;
                }
            };
        }
        return nullptr;
    }

private:
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    WeakPtr<NG::IndicatorController> controller_;
    WeakPtr<NG::FrameNode> swiperNode_;
    ACE_DISALLOW_COPY_AND_MOVE(JSIndicatorController);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_INDICATOR_H