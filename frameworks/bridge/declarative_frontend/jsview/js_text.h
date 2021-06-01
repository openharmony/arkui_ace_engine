/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_H

#include "core/components/text/text_component.h"
#include "core/components/text/text_theme.h"
#include "core/event/ace_event_handler.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

class JSText : public JSViewAbstract, public JSInteractableView {
    DECLARE_ACE_TYPE(JSText, JSViewAbstract);

public:
    JSText() = delete;
    JSText(const std::string& text);

    ~JSText()
    {
        LOGD("Destroy: JSText");
    };

    virtual RefPtr<OHOS::Ace::Component> CreateSpecializedComponent() override;
    virtual std::vector<RefPtr<OHOS::Ace::SingleChild>> CreateInteractableComponents() override;

#ifdef USE_QUICKJS_ENGINE
    virtual void MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc) override;
    virtual void ReleaseRT(JSRuntime* rt) override;

    static void QjsDestructor(JSRuntime* rt, JSText* ptr);
    static void QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc);
#endif

    static void JSBind(BindingTarget globalObj);

protected:
    void SetFontSize(const std::string& value);
    void SetFontWeight(const std::string& value);
    void SetTextColor(const std::string& value);
    void SetTextOverflow(int value);
    void SetMaxLines(int value);
    void SetFontStyle(int value);
    void SetTextAlign(int value);
    void SetLineHeight(const std::string& value);
    void SetFontFamily(const std::string& fontFamiliy);
    void SetMinFontSize(const std::string& value);
    void SetMaxFontSize(const std::string& value);
    std::vector<std::string> ParseFontFamilies(const std::string& value) const;
    Dimension TextAttr2Dimension(const std::string& value, bool usefp);

    TextStyle GetTextStyle() const;
    void SetTextStyle(TextStyle);

private:
    RefPtr<TextComponent> textComponent_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_TEXT_H
