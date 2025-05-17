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

#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

#include "session_manager/include/scene_session_manager.h"
#include "start_window_option.h"
#include "ui/rs_surface_node.h"

#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/window_scene/scene/window_event_process.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_v2/inspector/inspector_constants.h"
#ifdef ATOMIC_SERVICE_ATTRIBUTION_ENABLE
#include "core/components_ng/pattern/window_scene/scene/atomicservice_basic_engine_plugin.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t COLOR_BLACK = 0xff000000;
constexpr uint32_t COLOR_WHITE = 0xffffffff;

#ifdef ATOMIC_SERVICE_ATTRIBUTION_ENABLE
constexpr uint32_t ASENGINE_ATTRIBUTIONS_COUNT = 3;
constexpr uint32_t CIRCLE_ICON_INDEX = 1;
constexpr uint32_t EYELASHRING_ICON_INDEX = 2;
constexpr float HALF_PERCENT_TAG = 0.5f;
constexpr float BASE_X_OFFSET = 0.25f;
constexpr float BASE_Y_OFFSET = 0.4f;
constexpr float ROTATION_ANGLE = 360.0f;
constexpr uint32_t TEXT_NODE_HEIGHT = 42;
constexpr uint32_t TEXT_OFFSET_Y = 44;
constexpr uint32_t TEXT_NODE_FONT_SIZE = 16;
constexpr uint32_t TEXT_MAX_LINE = 2;
constexpr uint32_t IMAGE_NODE_SIZE = 72;
constexpr uint32_t ANIMATION_DURATION = 1750;
constexpr Dimension IMAGE_NODE_OFFSET = Dimension(-36, DimensionUnit::VP);
const Rosen::RSAnimationTimingCurve NODE_ANIMATION_TIMING_CURVE =
    Rosen::RSAnimationTimingCurve::CreateCubicCurve(0.40f, 0.08f, 0.60f, 0.92f);
#endif

constexpr uint32_t COLOR_TRANSLUCENT_WHITE = 0x66ffffff;
constexpr uint32_t COLOR_TRANSLUCENT_BLACK = 0x66000000;
constexpr Dimension SNAPSHOT_RADIUS = 16.0_vp;
constexpr uint32_t SNAPSHOT_LOAD_COMPLETE = 1;
} // namespace

class LifecycleListener : public Rosen::ILifecycleListener {
public:
    explicit LifecycleListener(const WeakPtr<WindowPattern>& windowPattern) : windowPattern_(windowPattern) {}
    virtual ~LifecycleListener() = default;

    void OnActivation() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnActivation();
    }

    void OnConnect() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnConnect();
    }

    void OnForeground() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnForeground();
    }

    void OnBackground() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnBackground();
    }

    void OnDisconnect() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnDisconnect();
    }

    void OnLayoutFinished() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnLayoutFinished();
    }

    void OnDrawingCompleted() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnDrawingCompleted();
    }

    void OnRemoveBlank() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnRemoveBlank();
    }

    void OnAddSnapshot() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnAddSnapshot();
    }

    void OnRemoveSnapshot() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnRemoveSnapshot();
    }

    void OnAppRemoveStartingWindow() override
    {
        auto windowPattern = windowPattern_.Upgrade();
        CHECK_NULL_VOID(windowPattern);
        windowPattern->OnAppRemoveStartingWindow();
    }

private:
    WeakPtr<WindowPattern> windowPattern_;
};

void WindowPattern::CheckAndMeasureStartingWindow(const SizeF& currentParentSize)
{
    CHECK_NULL_VOID(startingWindow_);
    const auto& sessionInfo = session_->GetSessionInfo();
#ifdef ATOMIC_SERVICE_ATTRIBUTION_ENABLE
    CHECK_EQUAL_VOID(sessionInfo.isAtomicService_, true);
#endif
    bool parentSizeChanged = !NearEqual(currentParentSize.Width(), lastParentSize_.Width(), 1.0f) ||
                             !NearEqual(currentParentSize.Height(), lastParentSize_.Height(), 1.0f);
    lastParentSize_ = currentParentSize;
    CHECK_EQUAL_VOID(parentSizeChanged, false);
    startingWindowLayoutHelper_->MeasureChildNode(currentParentSize);
}

void WindowPattern::RegisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    lifecycleListener_ = std::make_shared<LifecycleListener>(WeakClaim(this));
    session_->RegisterLifecycleListener(lifecycleListener_);
}

void WindowPattern::UnregisterLifecycleListener()
{
    CHECK_NULL_VOID(session_);
    session_->UnregisterLifecycleListener(lifecycleListener_);
}

bool WindowPattern::IsMainWindow() const
{
    CHECK_NULL_RETURN(session_, false);
    return session_->GetWindowType() == Rosen::WindowType::WINDOW_TYPE_APP_MAIN_WINDOW;
}

void WindowPattern::OnAttachToFrameNode()
{
    CreateAppWindow();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto state = session_->GetSessionState();
    TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "OnAttachToFrameNode id: %{public}d, node id: %{public}d, "
        "name: %{public}s, state: %{public}u, in recents: %{public}d", session_->GetPersistentId(), host->GetId(),
        session_->GetSessionInfo().bundleName_.c_str(), state, session_->GetShowRecent());
    if (state == Rosen::SessionState::STATE_DISCONNECT) {
        CHECK_EQUAL_VOID(HasStartingPage(), false);
        if (session_->GetShowRecent() && session_->GetScenePersistence() &&
            (session_->GetScenePersistence()->IsSnapshotExisted() ||
            session_->GetScenePersistence()->IsSavingSnapshot())) {
            CreateSnapshotWindow();
            AddChild(host, snapshotWindow_, snapshotWindowName_);
            return;
        }
        CreateStartingWindow();
        AddChild(host, startingWindow_, startingWindowName_);
        return;
    }

    CHECK_EQUAL_VOID(CheckAndAddStartingWindowAboveLocked(), true);

    if ((state == Rosen::SessionState::STATE_BACKGROUND || session_->IsAnco()) &&
        session_->GetScenePersistence() &&
        session_->GetScenePersistence()->HasSnapshot()) {
        if (!session_->GetShowRecent()) {
            AddChild(host, appWindow_, appWindowName_, 0);
        }
        CreateSnapshotWindow();
        AddChild(host, snapshotWindow_, snapshotWindowName_);
        attachToFrameNodeFlag_ = true;
        return;
    }

    if (session_->GetShowRecent()) {
        CreateStartingWindow();
        AddChild(host, startingWindow_, startingWindowName_);
        return;
    }

    AddChild(host, appWindow_, appWindowName_, 0);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    if (!surfaceNode->IsBufferAvailable()) {
        CreateStartingWindow();
        AddChild(host, startingWindow_, startingWindowName_);
        surfaceNode->SetBufferAvailableCallback(callback_);
        return;
    }
    attachToFrameNodeFlag_ = true;
}

void WindowPattern::CreateBlankWindow(RefPtr<FrameNode>& window)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    ACE_SCOPED_TRACE("CreateBlankWindow[id:%d][self:%d]", session_->GetPersistentId(), host->GetId());
    window = FrameNode::CreateFrameNode(
        V2::WINDOW_SCENE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = window->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto backgroundColor = context->GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    window->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));
}

void WindowPattern::CreateAppWindow()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ACE_SCOPED_TRACE("CreateAppWindow[id:%d][self:%d]", session_->GetPersistentId(), host->GetId());
    RefPtr<FrameNode> tempWindow = FrameNode::CreateFrameNode(
        V2::WINDOW_SCENE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    tempWindow->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    tempWindow->SetHitTestMode(HitTestMode::HTMNONE);
    CHECK_NULL_VOID(session_);
    auto surfaceNode = session_->GetSurfaceNode();
    if (surfaceNode) {
        auto context = AceType::DynamicCast<NG::RosenRenderContext>(tempWindow->GetRenderContext());
        CHECK_NULL_VOID(context);
        context->SetRSNode(surfaceNode);
        surfaceNode->SetVisible(true);
    }
    (!appWindow_) ? appWindow_ = std::move(tempWindow) : (newAppWindow_ = std::move(tempWindow));
}

#ifdef ATOMIC_SERVICE_ATTRIBUTION_ENABLE
RefPtr<FrameNode> WindowPattern::BuildTextNode(const std::string& appNameInfo)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    // set size
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    auto textNodeHeight = CalcLength(Dimension(TEXT_NODE_HEIGHT, DimensionUnit::VP));
    auto textNodeWidth = CalcLength(Dimension(HALF_PERCENT_TAG, DimensionUnit::PERCENT));
    textLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(textNodeWidth, textNodeHeight));
    // set basic attributions
    textLayoutProperty->UpdateContent(appNameInfo);
    textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
    textLayoutProperty->UpdateFontSize(Dimension(TEXT_NODE_FONT_SIZE, DimensionUnit::FP));
    textLayoutProperty->UpdateFontWeight(FontWeight::MEDIUM);
    textLayoutProperty->UpdateMaxLines(TEXT_MAX_LINE);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
    // set position
    double textOffsetY = Dimension(TEXT_OFFSET_Y, DimensionUnit::VP).ConvertToPx();
    auto basePositionX = Dimension(BASE_X_OFFSET, DimensionUnit::PERCENT);
    auto basePositionY = Dimension(BASE_Y_OFFSET, DimensionUnit::PERCENT);
    auto textContext = AceType::DynamicCast<RosenRenderContext>(textNode->GetRenderContext());
    CHECK_NULL_RETURN(textContext, nullptr);
    textContext->UpdatePosition(OffsetT<Dimension>(basePositionX, basePositionY));
    textContext->SetTranslate(0, textOffsetY, 0);
    textNode->MarkModifyDone();
    return textNode;
}

RefPtr<FrameNode> WindowPattern::BuildAnimateNode(const std::string& base64Resource)
{
    CHECK_NULL_RETURN(session_, nullptr);
    const auto& sessionInfo = session_->GetSessionInfo();
    auto testImageSource = ImageSourceInfo(
        base64Resource, sessionInfo.bundleName_, sessionInfo.moduleName_);
    auto animateNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(animateNode, nullptr);
    auto animateLayoutProperty = animateNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(animateLayoutProperty, nullptr);
    animateLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    animateLayoutProperty->UpdateImageSourceInfo(testImageSource);
    animateLayoutProperty->UpdateImageFit(ImageFit::FILL);
    auto animateContext = AceType::DynamicCast<RosenRenderContext>(animateNode->GetRenderContext());
    CHECK_NULL_RETURN(animateContext, nullptr);
    auto animateRSNode = animateContext->GetRSNode();
    CHECK_NULL_RETURN(animateRSNode, nullptr);
    auto animatePaintProperty = animateNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(animatePaintProperty, nullptr);
    animatePaintProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    // set position
    auto basePositionX = Dimension(HALF_PERCENT_TAG, DimensionUnit::PERCENT);
    auto basePositionY = Dimension(BASE_Y_OFFSET, DimensionUnit::PERCENT);
    animateContext->UpdatePosition(OffsetT<Dimension>(basePositionX, basePositionY));
    animateContext->SetTranslate(IMAGE_NODE_OFFSET.ConvertToPx(), IMAGE_NODE_OFFSET.ConvertToPx(), 0);
    // set size
    auto animateNodeHeight = CalcLength(Dimension(IMAGE_NODE_SIZE, DimensionUnit::VP));
    auto animateNodeWidth = CalcLength(Dimension(IMAGE_NODE_SIZE, DimensionUnit::VP));
    animateLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(animateNodeWidth, animateNodeHeight));
    // set animation
    Rosen::RSAnimationTimingProtocol protocol;
    animateContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
    protocol.SetDuration(ANIMATION_DURATION);
    protocol.SetRepeatCount(-1);
    Rosen::RSNode::Animate(animateRSNode->GetRSUIContext(), protocol, NODE_ANIMATION_TIMING_CURVE, [animateContext] {
        animateContext->UpdateTransformRotate(Vector5F(0.0f, 0.0f, 1.0f, ROTATION_ANGLE, 0.0f));
    });
    animateNode->MarkModifyDone();
    return animateNode;
}

RefPtr<FrameNode> WindowPattern::BuildStaticImageNode(const std::string& base64Resource)
{
    CHECK_NULL_RETURN(session_, nullptr);
    const auto& sessionInfo = session_->GetSessionInfo();
    auto testImageSource = ImageSourceInfo(
        base64Resource, sessionInfo.bundleName_, sessionInfo.moduleName_);
    auto staticNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(staticNode, nullptr);
    auto staticLayoutProperty = staticNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(staticLayoutProperty, nullptr);
    staticLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    staticLayoutProperty->UpdateImageSourceInfo(testImageSource);
    staticLayoutProperty->UpdateImageFit(ImageFit::CONTAIN);
    // set size
    auto staticNodeHeight = CalcLength(Dimension(IMAGE_NODE_SIZE, DimensionUnit::VP));
    auto staticNodeWidth = CalcLength(Dimension(IMAGE_NODE_SIZE, DimensionUnit::VP));
    staticLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(staticNodeWidth, staticNodeHeight));
    // get context and property
    auto staticContext = AceType::DynamicCast<RosenRenderContext>(staticNode->GetRenderContext());
    CHECK_NULL_RETURN(staticContext, nullptr);
    auto staticPaintProperty = staticNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_RETURN(staticPaintProperty, nullptr);
    staticPaintProperty->UpdateImageInterpolation(ImageInterpolation::HIGH);
    // set position
    auto basePositionX = Dimension(HALF_PERCENT_TAG, DimensionUnit::PERCENT);
    auto basePositionY = Dimension(BASE_Y_OFFSET, DimensionUnit::PERCENT);
    staticContext->UpdatePosition(OffsetT<Dimension>(basePositionX, basePositionY));
    staticContext->SetTranslate(IMAGE_NODE_OFFSET.ConvertToPx(), IMAGE_NODE_OFFSET.ConvertToPx(), 0);
    staticNode->MarkModifyDone();
    return staticNode;
}

void WindowPattern::CreateASStartingWindow()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    ACE_SCOPED_TRACE("CreateASStartingWindow[id:%d][self:%d]", session_->GetPersistentId(), host->GetId());
    
    CHECK_NULL_VOID(session_);
    const auto& sessionInfo = session_->GetSessionInfo();
    // get atomic service resources
    std::string appNameInfo = "";
    std::string eyelashRingIcon = "";
    std::string circleIcon = "";

#ifdef ACE_ENGINE_PLUGIN_PATH
    std::vector<std::string> atomicServiceIconInfo = AtomicServiceBasicEnginePlugin::GetInstance().
        getParamsFromAtomicServiceBasicEngine(sessionInfo.bundleName_);
    if (atomicServiceIconInfo.size() >= ASENGINE_ATTRIBUTIONS_COUNT) {
        appNameInfo = atomicServiceIconInfo[0];
        circleIcon = atomicServiceIconInfo[CIRCLE_ICON_INDEX];
        eyelashRingIcon = atomicServiceIconInfo[EYELASHRING_ICON_INDEX];
    }
    AtomicServiceBasicEnginePlugin::GetInstance().releaseData();
#endif // ACE_ENGINE_PLUGIN_PATH

    startingWindow_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_VOID(startingWindow_);
    auto asStartingLayoutProperty = startingWindow_->GetLayoutProperty<StackLayoutProperty>();
    CHECK_NULL_VOID(asStartingLayoutProperty);
    asStartingLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingWindow_->SetHitTestMode(HitTestMode::HTMNONE);
    startingWindow_->GetRenderContext()->UpdateBackgroundColor(
        context->GetColorMode() == ColorMode::DARK ? Color::BLACK : Color::WHITE);

    auto staticNode = BuildStaticImageNode(circleIcon);
    CHECK_NULL_VOID(staticNode);
    auto animateNode = BuildAnimateNode(eyelashRingIcon);
    CHECK_NULL_VOID(animateNode);
    auto textNode = BuildTextNode(appNameInfo);
    CHECK_NULL_VOID(textNode);

    startingWindow_->AddChild(staticNode);
    startingWindow_->AddChild(animateNode);
    startingWindow_->AddChild(textNode);
    startingWindow_->MarkModifyDone();
}
#endif

void WindowPattern::UpdateStartingWindowProperty(const Rosen::SessionInfo& sessionInfo,
    Color &color, ImageSourceInfo &sourceInfo)
{
    if (sessionInfo.startWindowOption == nullptr || !sessionInfo.startWindowOption->hasStartWindow) {
        return;
    }
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "Get starting window info from session info");
    if (!sessionInfo.startWindowOption->startWindowBackgroundColor.empty()) {
        Color::ParseColorString(sessionInfo.startWindowOption->startWindowBackgroundColor, color);
    }
    if (sessionInfo.startWindowOption->startWindowIcon != nullptr) {
        auto pixelMap = PixelMap::CreatePixelMap(&(sessionInfo.startWindowOption->startWindowIcon));
        sourceInfo = ImageSourceInfo(pixelMap);
    }
}

bool WindowPattern::CheckAndAddStartingWindowAboveLocked()
{
    CHECK_EQUAL_RETURN(
        Rosen::SceneSessionManager::GetInstance().IsScreenLocked() && session_->UseStartingWindowAboveLocked(),
        false, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto surfaceNode = session_->GetSurfaceNode();
    CHECK_NULL_RETURN(surfaceNode, false);
    AddChild(host, appWindow_, appWindowName_, 0);
    CreateStartingWindow();
    AddChild(host, startingWindow_, startingWindowName_);
    surfaceNode->SetBufferAvailableCallback(callback_);
    return true;
}

void WindowPattern::CreateStartingWindow()
{
    const auto& sessionInfo = session_->GetSessionInfo();
#ifdef ATOMIC_SERVICE_ATTRIBUTION_ENABLE
    if (sessionInfo.isAtomicService_) {
        CreateASStartingWindow();
        return;
    }
#endif

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    ACE_SCOPED_TRACE("CreateStartingWindow[id:%d][self:%d]", session_->GetPersistentId(), host->GetId());
    Rosen::StartingWindowInfo startingWindowInfo;
    startingWindowInfo.backgroundColorEarlyVersion_ =
        context->GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
    Rosen::SceneSessionManager::GetInstance().GetStartupPage(sessionInfo, startingWindowInfo);
    if (startingWindowInfo.configFileEnabled_) {
        CHECK_NULL_VOID(startingWindowLayoutHelper_);
        lastParentSize_ = { 0.0f, 0.0f };
        startingWindow_ = startingWindowLayoutHelper_->CreateStartingWindowNode(
            startingWindowInfo, sessionInfo.bundleName_, sessionInfo.moduleName_);
        return;
    }
    startingWindow_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = startingWindow_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    startingWindow_->SetHitTestMode(HitTestMode::HTMNONE);

    auto sourceInfo = ImageSourceInfo(
        startingWindowInfo.iconPathEarlyVersion_, sessionInfo.bundleName_, sessionInfo.moduleName_);
    auto color = Color(startingWindowInfo.backgroundColorEarlyVersion_);
    UpdateStartingWindowProperty(sessionInfo, color, sourceInfo);
    imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
    startingWindow_->GetRenderContext()->UpdateBackgroundColor(color);
    imageLayoutProperty->UpdateImageFit(ImageFit::NONE);
    startingWindow_->MarkModifyDone();
}

void WindowPattern::UpdateSnapshotWindowProperty()
{
    CHECK_NULL_VOID(snapshotWindow_ && session_);
    auto isExitSplitOnBackground = session_->IsExitSplitOnBackground();
    if (isExitSplitOnBackground) {
        Rosen::SceneSessionManager::GetInstance().SetDelayRemoveSnapshot(false);
        auto imagePattern = snapshotWindow_->GetPattern<ImagePattern>();
        auto renderContext = snapshotWindow_->GetRenderContext();
        auto imageRenderProperty = snapshotWindow_->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imagePattern && renderContext && imageRenderProperty);

        BorderRadiusProperty borderRadius;
        borderRadius.SetRadius(SNAPSHOT_RADIUS);
        borderRadius.multiValued = false;
        renderContext->UpdateBorderRadius(borderRadius);
        auto context = GetContext();
        CHECK_NULL_VOID(context);
        auto backgroundColor =
            context->GetColorMode() == ColorMode::DARK ? COLOR_TRANSLUCENT_BLACK : COLOR_TRANSLUCENT_WHITE;
        renderContext->UpdateBackgroundColor(Color(backgroundColor));
        imagePattern->SetNeedBorderRadius(true);
        imageRenderProperty->UpdateNeedBorderRadius(true);
    }
    auto imageLayoutProperty = snapshotWindow_->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    int32_t imageFit = 0;
    auto isPersistentImageFit = Rosen::SceneSessionManager::GetInstance().GetPersistentImageFit(
            session_->GetPersistentId(), imageFit);
    if (isPersistentImageFit) {
        imageLayoutProperty->UpdateImageFit(static_cast<ImageFit>(imageFit));
    } else {
        imageLayoutProperty->UpdateImageFit(isExitSplitOnBackground ? ImageFit::CONTAIN : ImageFit::COVER_TOP_LEFT);
    }
    snapshotWindow_->MarkModifyDone();
}

bool WindowPattern::IsSnapshotSizeChanged()
{
    // pc and pad use the same snapshot size
    CHECK_EQUAL_RETURN(session_->GetSystemConfig().IsPcWindow(), true, false);
    CHECK_EQUAL_RETURN(session_->GetSystemConfig().freeMultiWindowEnable_, true, false);
    Rosen::WSRect lastRect = session_->GetLastLayoutRect();
    Rosen::WSRect curRect = session_->GetLayoutRect();
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "snapshot size changed id:%{public}d, last:%{public}s, cur:%{public}s",
             session_->GetPersistentId(), lastRect.ToString().c_str(), curRect.ToString().c_str());
    if (!session_->GetShowRecent() && !lastRect.IsInvalid() &&
        NearEqual(lastRect.width_, curRect.width_, 1.0f) && NearEqual(lastRect.height_, curRect.height_, 1.0f)) {
        return true;
    }
    return false;
}

void WindowPattern::CreateSnapshotWindow(std::optional<std::shared_ptr<Media::PixelMap>> snapshot)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto persistentId = session_->GetPersistentId();
    ACE_SCOPED_TRACE("CreateSnapshotWindow[id:%d][self:%d]", persistentId, host->GetId());
    session_->SetNeedSnapshot(false);
    isBlankForSnapshot_ = false;

    if (IsSnapshotSizeChanged()) {
        isBlankForSnapshot_ = true;
        CreateBlankWindow(snapshotWindow_);
        return;
    }

    snapshotWindow_ = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageLayoutProperty = snapshotWindow_->GetLayoutProperty<ImageLayoutProperty>();
    imageLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto imagePaintProperty = snapshotWindow_->GetPaintProperty<ImageRenderProperty>();
    imagePaintProperty->UpdateImageInterpolation(ImageInterpolation::LOW);
    snapshotWindow_->SetHitTestMode(HitTestMode::HTMNONE);

    if (snapshot) {
        auto pixelMap = PixelMap::CreatePixelMap(&snapshot.value());
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(pixelMap));
        snapshotWindow_->GetPattern<ImagePattern>()->SetSyncLoad(true);
    } else {
        if (session_->GetSystemConfig().IsPhoneWindow() && session_->GetShowRecent()) {
            auto context = GetContext();
            CHECK_NULL_VOID(context);
            auto backgroundColor = context->GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
            auto snapshotContext = snapshotWindow_->GetRenderContext();
            CHECK_NULL_VOID(snapshotContext);
            snapshotContext->UpdateBackgroundColor(Color(backgroundColor));
        }
        ImageSourceInfo sourceInfo;
        auto scenePersistence = session_->GetScenePersistence();
        CHECK_NULL_VOID(scenePersistence);
        auto isSaveingSnapshot = scenePersistence->IsSavingSnapshot();
        TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE,
            "id: %{public}d isSaveingSnapshot: %{public}d", persistentId, isSaveingSnapshot);
        if (isSaveingSnapshot) {
            auto snapshotPixelMap = session_->GetSnapshotPixelMap();
            CHECK_NULL_VOID(snapshotPixelMap);
            auto pixelMap = PixelMap::CreatePixelMap(&snapshotPixelMap);
            sourceInfo = ImageSourceInfo(pixelMap);
            snapshotWindow_->GetPattern<ImagePattern>()->SetSyncLoad(true);
            Rosen::SceneSessionManager::GetInstance().VisitSnapshotFromCache(persistentId);
        } else {
            sourceInfo = ImageSourceInfo("file://" + scenePersistence->GetSnapshotFilePath());
        }
        imageLayoutProperty->UpdateImageSourceInfo(sourceInfo);
        ClearImageCache(sourceInfo);
        auto eventHub = snapshotWindow_->GetOrCreateEventHub<ImageEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnError([weakThis = WeakClaim(this)](const LoadImageFailEvent& info) {
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self && self->snapshotWindow_);
            auto context = self->GetContext();
            CHECK_NULL_VOID(context);
            TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "load snapshot failed: %{public}s", info.GetErrorMessage().c_str());
            auto backgroundColor = context->GetColorMode() == ColorMode::DARK ? COLOR_BLACK : COLOR_WHITE;
            self->snapshotWindow_->GetRenderContext()->UpdateBackgroundColor(Color(backgroundColor));
            self->snapshotWindow_->MarkNeedRenderOnly();
        });
        eventHub->SetOnComplete([weakThis = WeakClaim(this)](const LoadImageSuccessEvent& info) {
            if (info.GetLoadingStatus() != SNAPSHOT_LOAD_COMPLETE) {
                return;
            }
            auto self = weakThis.Upgrade();
            CHECK_NULL_VOID(self);
            if (self->session_->IsExitSplitOnBackground()) {
                return;
            }
            CHECK_NULL_VOID(self->snapshotWindow_);
            TAG_LOGD(AceLogTag::ACE_WINDOW_SCENE, "load snapshot complete id: %{public}d",
                self->session_->GetPersistentId());
            auto context = self->snapshotWindow_->GetRenderContext();
            CHECK_NULL_VOID(context);
            context->UpdateBackgroundColor(Color::TRANSPARENT);
            self->snapshotWindow_->MarkNeedRenderOnly();
        });
    }
    UpdateSnapshotWindowProperty();
}

void WindowPattern::ClearImageCache(const ImageSourceInfo& sourceInfo)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto imageCache = pipelineContext->GetImageCache();
    CHECK_NULL_VOID(imageCache);
    imageCache->ClearCacheImgObj(sourceInfo.GetKey());
    if (!Rosen::ScenePersistence::IsAstcEnabled()) {
        auto snapshotSize = session_->GetScenePersistence()->GetSnapshotSize();
        imageCache->ClearCacheImage(
            ImageUtils::GenerateImageKey(sourceInfo, SizeF(snapshotSize.first, snapshotSize.second)));
        imageCache->ClearCacheImage(
            ImageUtils::GenerateImageKey(sourceInfo, SizeF(snapshotSize.second, snapshotSize.first)));
        imageCache->ClearCacheImage(sourceInfo.GetKey());
    }
}

void WindowPattern::DispatchPointerEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(pointerEvent);
    session_->TransferPointerEvent(pointerEvent);
    if (pointerEvent->GetPointerAction() >= MMI::PointerEvent::POINTER_ACTION_PULL_DOWN &&
        pointerEvent->GetPointerAction() <= MMI::PointerEvent::POINTER_ACTION_PULL_UP) {
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            auto manager = pipeline->GetDragDropManager();
            CHECK_NULL_VOID(manager);
            manager->SetIsWindowConsumed(true);
        }
    }
}

void WindowPattern::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    CHECK_NULL_VOID(session_);
    CHECK_NULL_VOID(keyEvent);
    session_->TransferKeyEvent(keyEvent);
}

void WindowPattern::DispatchKeyEventForConsumed(const std::shared_ptr<MMI::KeyEvent>& keyEvent, bool& isConsumed)
{
    CHECK_NULL_VOID(session_);
    session_->TransferKeyEventForConsumed(keyEvent, isConsumed);
}

void WindowPattern::DisPatchFocusActiveEvent(bool isFocusActive)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusActiveEvent(isFocusActive);
}

sptr<Rosen::Session> WindowPattern::GetSession()
{
    return session_;
}

bool WindowPattern::BorderUnoccupied() const
{
    CHECK_NULL_RETURN(session_, false);
    return session_->GetBorderUnoccupied();
}

void WindowPattern::TransferFocusState(bool focusState)
{
    CHECK_NULL_VOID(session_);
    session_->TransferFocusStateEvent(focusState);
}

std::vector<Rosen::Rect> WindowPattern::GetHotAreas()
{
    if (session_ == nullptr) {
        return std::vector<Rosen::Rect>();
    }
    return session_->GetTouchHotAreas();
}

void WindowPattern::AddChild(const RefPtr<FrameNode>& host, const RefPtr<FrameNode>& child,
    const std::string& nodeType, int32_t index)
{
    ACE_SCOPED_TRACE("WindowScene::AddChild[%s][self:%d]", nodeType.c_str(), host->GetId());
    host->AddChild(child, index);
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "AddChild %{public}s, %{public}d", nodeType.c_str(), host->GetId());
}

void WindowPattern::RemoveChild(const RefPtr<FrameNode>& host, const RefPtr<FrameNode>& child,
    const std::string& nodeType, bool allowTransition)
{
    ACE_SCOPED_TRACE("WindowScene::RemoveChild[%s][self:%d]", nodeType.c_str(), host->GetId());
    host->RemoveChild(child, allowTransition);
    TAG_LOGI(AceLogTag::ACE_WINDOW_SCENE, "RemoveChild %{public}s, %{public}d", nodeType.c_str(), host->GetId());
}
} // namespace OHOS::Ace::NG
