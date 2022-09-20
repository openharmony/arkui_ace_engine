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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_H

#include <optional>
#include <string>
#include <utility>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
namespace {

struct MouseClickInfo {
    double x = -1;
    double y = -1;
    TimeStamp start;
};

#ifdef OHOS_STANDARD_SYSTEM
struct TouchInfo {
    double x = -1;
    double y = -1;
    int32_t id = -1;
};

struct TouchHandleState {
    int32_t id = -1;
    int32_t x = -1;
    int32_t y = -1;
    int32_t edge_height = 0;
};

enum WebOverlayType {
    INSERT_OVERLAY,
    SELECTION_OVERLAY,
    INVALID_OVERLAY
};
#endif
}

class WebPattern : public Pattern {
    DECLARE_ACE_TYPE(WebPattern, Pattern);

public:
    WebPattern(std::string webSrc, const RefPtr<WebController>& webController);

    ~WebPattern() override = default;

    std::optional<std::string> GetSurfaceNodeName() const override
    {
        return "RosenWeb";
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<WebEventHub>();
    }

    void OnModifyDone() override;

    void SetWebSrc(const std::string& webSrc)
    {
        if (webSrc_ != webSrc_) {
            OnWebSrcUpdate();
            webSrc_ = webSrc;
        }
    }

    const std::optional<std::string>& GetWebSrc() const
    {
        return webSrc_;
    }

    void SetWebData(const std::string& webData)
    {
        if (webData_ != webData) {
            OnWebDataUpdate();
            webData_ = webData;
        }
    }

    const std::optional<std::string>& GetWebData() const
    {
        return webData_;
    }

    void SetWebController(const RefPtr<WebController>& webController)
    {
        // TODO: add web controller diff function.
        webController_ = webController;
    }

    RefPtr<WebController> GetWebController() const
    {
        return webController_;
    }

    RefPtr<WebEventHub> GetWebEventHub()
    {
        return GetEventHub<WebEventHub>();
    }

    ACE_DEFINE_PROPERTY_GROUP(WebProperty, WebPatternProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, JsEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MediaPlayGestureAccess, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, FileAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OnLineImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DomStorageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ImageAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, MixedMode, MixedModeContent);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, ZoomAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, GeolocationAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, UserAgent, std::string);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, CacheMode, WebCacheMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, OverviewModeAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, FileFromUrlAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, DatabaseAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, TextZoomRatio, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, WebDebuggingAccessEnabled, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, BackgroundColor, int32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(WebProperty, InitialScale, float);

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void OnAttachToFrameNode() override;

    void OnWebSrcUpdate();
    void OnWebDataUpdate();
    void OnJsEnabledUpdate(bool value);
    void OnMediaPlayGestureAccessUpdate(bool value);
    void OnFileAccessEnabledUpdate(bool value);
    void OnOnLineImageAccessEnabledUpdate(bool value);
    void OnDomStorageAccessEnabledUpdate(bool value);
    void OnImageAccessEnabledUpdate(bool value);
    void OnMixedModeUpdate(MixedModeContent value);
    void OnZoomAccessEnabledUpdate(bool value);
    void OnGeolocationAccessEnabledUpdate(bool value);
    void OnUserAgentUpdate(const std::string& value);
    void OnCacheModeUpdate(WebCacheMode value);
    void OnOverviewModeAccessEnabledUpdate(bool value);
    void OnFileFromUrlAccessEnabledUpdate(bool value);
    void OnDatabaseAccessEnabledUpdate(bool value);
    void OnTextZoomRatioUpdate(int32_t value);
    void OnWebDebuggingAccessEnabledUpdate(bool value);
    void OnBackgroundColorUpdate(int32_t value);
    void OnInitialScaleUpdate(float value);

    void InitEvent();
    void InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitMouseEvent(const RefPtr<InputEventHub>& inputHub);
    void HandleMouseEvent(MouseInfo& info);
    void OnMouseEvent(const MouseInfo& info);
    bool HandleDoubleClickEvent(const MouseInfo& info);
    void SendDoubleClickEvent(const MouseClickInfo& info);

    void HandleTouchDown(const TouchEventInfo& info, bool fromOverlay);

    void HandleTouchUp(const TouchEventInfo& info, bool fromOverlay);

    void HandleTouchMove(const TouchEventInfo& info, bool fromOverlay);

    void HandleTouchCancel(const TouchEventInfo& info);

    struct TouchInfo {
        float x = -1.0f;
        float y = -1.0f;
        int32_t id = -1;
    };
    static bool ParseTouchInfo(const TouchEventInfo& info, std::list<TouchInfo>& touchInfos);

    std::optional<std::string> webSrc_;
    std::optional<std::string> webData_;
    RefPtr<WebController> webController_;
    RefPtr<WebDelegate> delegate_;
    RefPtr<RenderSurface> renderSurface_ = RenderSurface::Create();
    RefPtr<TouchEventImpl> touchEvent_;
    RefPtr<InputEvent> mouseEvent_;
    RefPtr<InputEvent> mouseHoverEvent_;
    bool isUrlLoaded_ = false;
    std::queue<MouseClickInfo> doubleClickQueue_;

    ACE_DISALLOW_COPY_AND_MOVE(WebPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_PATTERN_H
