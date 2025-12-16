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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATILBE_COMPONENTS_DOM_MARQUEE_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATILBE_COMPONENTS_DOM_MARQUEE_H

#include "compatible/components/marquee/marquee_component.h"
#include "frameworks/bridge/common/dom/dom_node.h"

namespace OHOS::Ace::Framework {

// marquee attribute and style constants
extern const char DOM_MARQUEE_LOOP[];
extern const char DOM_MARQUEE_SCROLL_AMOUNT[];
extern const char DOM_MARQUEE_DIRECTION[];
extern const char DOM_MARQUEE_DIRECTION_RIGHT[];
extern const char DOM_MARQUEE_VALUE[];
extern const char DOM_MARQUEE_COLOR[];
extern const char DOM_MARQUEE_FONT_SIZE[];
extern const char DOM_MARQUEE_FONT_WEIGHT[];
extern const char DOM_MARQUEE_FONT_FAMILY[];
extern const char DOM_MARQUEE_TEXT_ALIGN[];
extern const char DOM_MARQUEE_EVENT_BOUNCE[];
extern const char DOM_MARQUEE_EVENT_FINISH[];
extern const char DOM_MARQUEE_EVENT_START[];
extern const char DOM_MARQUEE_METHOD_START[];
extern const char DOM_MARQUEE_METHOD_STOP[];

// remove later
extern const char DOM_TEXT_ALLOW_SCALE[];

class DOMMarquee final : public DOMNode {
    DECLARE_ACE_TYPE(DOMMarquee, DOMNode);

public:
    DOMMarquee(NodeId nodeId, const std::string& nodeName);
    ~DOMMarquee() override = default;

    void InitializeStyle() override;

    void CallSpecializedMethod(const std::string& method, const std::string& args) override;

    RefPtr<Component> GetSpecializedComponent() override
    {
        return marqueeChild_;
    }

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    bool AddSpecializedEvent(int32_t pageId, const std::string& event) override;
    void PrepareSpecializedComponent() override;
    void ResetInitializedStyle() override;

private:
    RefPtr<MarqueeComponent> marqueeChild_;
    TextStyle textStyle_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATILBE_COMPONENTS_DOM_MARQUEE_H
