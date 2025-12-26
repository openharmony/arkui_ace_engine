/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_COMMON_DECLARATION_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_COMMON_DECLARATION_CONSTANTS_H

#include <memory>

#include "core/components/declaration/button/button_declaration.h"
#include "core/components/declaration/common/attribute.h"
#include "core/components/declaration/common/event.h"
#include "core/components/declaration/common/method.h"
#include "core/components/declaration/common/style.h"
#include "core/components/declaration/div/div_declaration.h"
#include "core/components/declaration/richtext/rich_text_declaration.h"
#include "core/components/declaration/side_bar/side_bar_declaration.h"
#include "core/components/declaration/span/span_declaration.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/declaration/text/text_declaration.h"
#include "core/components/declaration/texttimer/texttimer_declaration.h"
#include "core/components/declaration/web/web_declaration.h"
#include "core/components/declaration/xcomponent/xcomponent_declaration.h"

namespace OHOS::Ace {

class DeclarationConstants {
public:
    // attributes, styles, events and methods supported default.
    static const std::vector<AttributeTag> DEFAULT_ATTRS;
    static const std::vector<StyleTag> DEFAULT_STYLES;
    static const std::vector<EventTag> DEFAULT_EVENTS;
    static const std::vector<MethodTag> DEFAULT_METHODS;

    // default value of common attribute
    static const std::shared_ptr<CommonAttribute> DEFAULT_COMMON_ATTR;
    static const std::shared_ptr<CommonDisabledAttribute> DEFAULT_DISABLED_ATTR;
    static const std::shared_ptr<CommonFocusableAttribute> DEFAULT_FOCUSABLE_ATTR;
    static const std::shared_ptr<CommonTouchableAttribute> DEFAULT_TOUCHABLE_ATTR;
    static const std::shared_ptr<CommonDataAttribute> DEFAULT_DATA_ATTR;
    static const std::shared_ptr<CommonClickEffectAttribute> DEFAULT_CLICK_EFFECT_ATTR;
    static const std::shared_ptr<CommonRenderAttribute> DEFAULT_RENDER_ATTR;
    static const std::shared_ptr<CommonMultimodalAttribute> DEFAULT_MULTI_MODAL_ATTR;

    // default value of common style
    static const std::shared_ptr<CommonStyle> DEFAULT_COMMON_STYLE;
    static const std::shared_ptr<CommonSizeStyle> DEFAULT_SIZE_STYLE;
    static const std::shared_ptr<CommonMarginStyle> DEFAULT_MARGIN_STYLE;
    static const std::shared_ptr<CommonPaddingStyle> DEFAULT_PADDING_STYLE;
    static const std::shared_ptr<CommonBorderStyle> DEFAULT_BORDER_STYLE;
    static const std::shared_ptr<CommonBackgroundStyle> DEFAULT_BACKGROUND_STYLE;
    static const std::shared_ptr<CommonFlexStyle> DEFAULT_FLEX_STYLE;
    static const std::shared_ptr<CommonPositionStyle> DEFAULT_POSITION_STYLE;
    static const std::shared_ptr<CommonOpacityStyle> DEFAULT_OPACITY_STYLE;
    static const std::shared_ptr<CommonVisibilityStyle> DEFAULT_VISIBILITY_STYLE;
    static const std::shared_ptr<CommonDisplayStyle> DEFAULT_DISPLAY_STYLE;
    static const std::shared_ptr<CommonShadowStyle> DEFAULT_SHADOW_STYLE;
    static const std::shared_ptr<CommonOverflowStyle> DEFAULT_OVERFLOW_STYLE;
    static const std::shared_ptr<CommonFilterStyle> DEFAULT_FILTER_STYLE;
    static const std::shared_ptr<CommonAnimationStyle> DEFAULT_ANIMATION_STYLE;
    static const std::shared_ptr<CommonShareTransitionStyle> DEFAULT_SHARE_TRANSITION_STYLE;
    static const std::shared_ptr<CommonCardTransitionStyle> DEFAULT_CARD_TRANSITION_STYLE;
    static const std::shared_ptr<CommonPageTransitionStyle> DEFAULT_PAGE_TRANSITION_STYLE;
    static const std::shared_ptr<CommonClipPathStyle> DEFAULT_CLIP_PATH_STYLE;
    static const std::shared_ptr<CommonMaskStyle> DEFAULT_MASK_STYLE;
    static const std::shared_ptr<CommonImageStyle> DEFAULT_IMAGE_STYLE;

    // default value of common event
    static const std::shared_ptr<CommonRawEvent> DEFAULT_RAW_EVENT;
    static const std::shared_ptr<CommonGestureEvent> DEFAULT_GESTURE_EVENT;
    static const std::shared_ptr<CommonFocusEvent> DEFAULT_FOCUS_EVENT;
    static const std::shared_ptr<CommonKeyEvent> DEFAULT_KEY_EVENT;
    static const std::shared_ptr<CommonMouseEvent> DEFAULT_MOUSE_EVENT;
    static const std::shared_ptr<CommonSwipeEvent> DEFAULT_SWIPE_EVENT;
    static const std::shared_ptr<CommonAttachEvent> DEFAULT_ATTACH_EVENT;
    static const std::shared_ptr<CommonCrownEvent> DEFAULT_CROWN_EVENT;

    // default value of common event
    static const std::shared_ptr<CommonMethod> DEFAULT_METHOD;

    // default value of button
    static const std::shared_ptr<ButtonAttribute> DEFAULT_BUTTON_ATTR;
    static const std::shared_ptr<ButtonStyle> DEFAULT_BUTTON_STYLE;
    static const std::shared_ptr<ButtonEvent> DEFAULT_BUTTON_EVENT;
    static const std::shared_ptr<ButtonMethod> DEFAULT_BUTTON_METHOD;

    // default value of div
    static const std::shared_ptr<DivAttribute> DEFAULT_DIV_ATTR;
    static const std::shared_ptr<DivStyle> DEFAULT_DIV_STYLE;

    // default value of side bar
    static const std::shared_ptr<SideBarContainerAttribute> DEFAULT_SIDE_BAR_ATTR;
    static const std::shared_ptr<RegionEvent> DEFAULT_REGION_EVENT;

    // default value of span
    static const std::shared_ptr<SpanAttribute> DEFAULT_SPAN_ATTR;
    static const std::shared_ptr<SpanStyle> DEFAULT_SPAN_STYLE;

    // default value of swiper
    static const std::shared_ptr<SwiperAttribute> DEFAULT_SWIPER_ATTR;
    static const std::shared_ptr<SwiperStyle> DEFAULT_SWIPER_STYLE;
    static const std::shared_ptr<SwiperEvent> DEFAULT_SWIPER_EVENT;
    static const std::shared_ptr<SwiperMethod> DEFAULT_SWIPER_METHOD;

    // default value of text
    static const std::shared_ptr<TextSpecializedAttribute> DEFAULT_TEXT_ATTR;
    static const std::shared_ptr<TextSpecializedStyle> DEFAULT_TEXT_STYLE;

    // default value of texttimer
    static const std::shared_ptr<TextTimerAttribute> DEFAULT_TEXTTIMER_ATTR;
    static const std::shared_ptr<TextTimerStyle> DEFAULT_TEXTTIMER_STYLE;
    static const std::shared_ptr<TextTimerEvent> DEFAULT_TEXTTIMER_EVENT;
    static const std::shared_ptr<TextTimerMethod> DEFAULT_TEXTTIMER_METHOD;

    // default value of web
    static const std::shared_ptr<WebAttribute> DEFAULT_WEB_ATTR;
    static const std::shared_ptr<WebEvent> DEFAULT_WEB_EVENT;
    static const std::shared_ptr<WebMethod> DEFAULT_WEB_METHOD;

    // default value of richtext
    static const std::shared_ptr<RichTextAttribute> DEFAULT_RICH_TEXT_ATTR;
    static const std::shared_ptr<RichTextEvent> DEFAULT_RICH_TEXT_EVENT;

    // default value of xcomponent
    static const std::shared_ptr<XComponentAttribute> DEFAULT_XCOMPONENT_ATTR;
    static const std::shared_ptr<XComponentEvent> DEFAULT_XCOMPONENT_EVENT;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_COMMON_DECLARATION_CONSTANTS_H
