/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_PROPERTY_H

#include <optional>
#include <string>
#include <tuple>

#include "core/components/web/web_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

struct WebPatternProperty {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(JsEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MediaPlayGestureAccess, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FileAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OnLineImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DomStorageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MixedMode, MixedModeContent);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ZoomAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(GeolocationAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(UserAgent, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CacheMode, WebCacheMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DarkMode, WebDarkMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ForceDarkAccess, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AudioResumeInterval, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AudioExclusive, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OverviewModeAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(FileFromUrlAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DatabaseAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextZoomRatio, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebDebuggingAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BackgroundColor, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(InitialScale, float);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(PinchSmoothModeEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MultiWindowAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AllowWindowOpenMethod, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebCursiveFont, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebFantasyFont, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebFixedFont, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebSansSerifFont, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebSerifFont, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebStandardFont, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DefaultFixedFontSize, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DefaultFontSize, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(DefaultTextEncodingFormat, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MinFontSize, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MinLogicalFontSize, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlockNetwork, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(HorizontalScrollBarAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(VerticalScrollBarAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ScrollBarColor, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OverScrollMode, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(BlurOnKeyboardHideMode, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(CopyOptionMode, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MetaViewport, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NativeEmbedModeEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NativeEmbedRuleTag, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NativeEmbedRuleType, std::string);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(TextAutosizing, bool);
    using NativeVideoPlayerConfigType = std::tuple<bool, bool>;
    ACE_DEFINE_PROPERTY_GROUP_ITEM(NativeVideoPlayerConfig, NativeVideoPlayerConfigType);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SmoothDragResizeEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectionMenuOptions, WebMenuOptionsParam);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OverlayScrollbarEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(KeyboardAvoidMode, WebKeyboardAvoidMode);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(EnabledHapticFeedback, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(OptimizeParserBudgetEnabled, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(WebMediaAVSessionEnabled, bool);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_PROPERTY_H
