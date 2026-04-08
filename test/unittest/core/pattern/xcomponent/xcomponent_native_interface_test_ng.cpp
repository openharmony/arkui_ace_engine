/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#include "core/components/xcomponent/native_interface_xcomponent_impl.h"

#include "base/error/error_code.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_surface_holder.h"
#include "frameworks/core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/native_interface_xcomponent.h"
#include "interfaces/native/node/node_model.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint64_t XCOMPONENT_WIDTH = 320;
constexpr uint64_t XCOMPONENT_HEIGHT = 180;
constexpr double XCOMPONENT_OFFSET_X = 10.5;
constexpr double XCOMPONENT_OFFSET_Y = 20.5;
constexpr float TILT_X = 11.0f;
constexpr float TILT_Y = 12.0f;
constexpr float WINDOW_X = 13.0f;
constexpr float WINDOW_Y = 14.0f;
constexpr float DISPLAY_X = 15.0f;
constexpr float DISPLAY_Y = 16.0f;
constexpr int32_t SOURCE_POINT_ID = 7;
constexpr uint64_t EXTRA_MOUSE_KEYS = 0x13;
constexpr uint64_t KEY_EVENT_KEYS = 0x25;
constexpr int32_t ROOT_NODE_ID = 1000;
constexpr int32_t AUTO_INITIALIZE_RESULT = 11;
constexpr int32_t INITIALIZE_RESULT = 12;
constexpr int32_t FINALIZE_RESULT = 13;
constexpr int32_t IS_INITIALIZED_RESULT = 14;
constexpr int32_t FRAME_RATE_RESULT = 15;
constexpr int32_t REGISTER_FRAME_RESULT = 16;
constexpr int32_t UNREGISTER_FRAME_RESULT = 17;
constexpr int32_t SOFT_KEYBOARD_RESULT = 18;
constexpr int32_t SURFACE_OPAQUE_RESULT = 19;
constexpr int32_t TOUCH_EVENT_ID = 1;
constexpr uint32_t TOUCH_POINT_COUNT = 1;
constexpr int32_t HISTORICAL_POINT_ID = 9;
constexpr float HISTORICAL_POINT_X = 31.0f;
constexpr float HISTORICAL_POINT_Y = 41.0f;
constexpr float MOUSE_EVENT_X = 51.0f;
constexpr float MOUSE_EVENT_Y = 61.0f;
constexpr int64_t KEY_EVENT_DEVICE_ID = 77;
constexpr int64_t KEY_EVENT_TIMESTAMP = 88;
constexpr int32_t INVALID_RANGE_MIN = 1;
constexpr int32_t INVALID_RANGE_MAX = 2;
constexpr int32_t INVALID_RANGE_EXPECTED = 2;
constexpr int32_t DEFAULT_RANGE_MIN = 30;
constexpr int32_t DEFAULT_RANGE_MAX = 60;
constexpr int32_t DEFAULT_RANGE_EXPECTED = 60;
constexpr int32_t CUSTOM_RANGE_MIN = 24;
constexpr int32_t CUSTOM_RANGE_EXPECTED = 48;
constexpr int32_t SINGLE_CALL_COUNT = 1;
constexpr int32_t CONTAINER_TOKEN = 99;
constexpr int32_t ANALYZER_USER_DATA = 5;
constexpr int32_t SURFACE_HOLDER_USER_DATA = 9;
constexpr int32_t NATIVE_WINDOW_TOKEN = 3;
constexpr uintptr_t FAKE_ACCESSIBILITY_PROVIDER = 0x1234;
constexpr uintptr_t DISPOSE_PROVIDER_PTR_1 = 0x1;
constexpr uintptr_t DISPOSE_PROVIDER_PTR_2 = 0x2;
constexpr uintptr_t DISPOSE_PROVIDER_PTR_3 = 0x3;
const char XCOMPONENT_ID[] = "native_xcomponent";

void DummyComponentWindowCallback(OH_NativeXComponent*, void*) {}

void DummyHoverCallback(OH_NativeXComponent*, bool) {}

bool DummyKeyResultCallback(OH_NativeXComponent*, void*)
{
    return true;
}

HitTestMode DummyTouchInterceptCallback(OH_NativeXComponent*, ArkUI_UIInputEvent*)
{
    return HitTestMode::HTMBLOCK;
}

void DummyNativeOnFrameCallback(OH_NativeXComponent*, uint64_t, uint64_t) {}

void DummyUIInputEventCallback(
    OH_NativeXComponent*, ArkUI_UIInputEvent*, ArkUI_UIInputEvent_Type)
{}

void DummyArkUIOnFrameCallback(ArkUI_NodeHandle, uint64_t, uint64_t) {}

void DummyImageAnalyzerCallback(
    ArkUI_NodeHandle, ArkUI_XComponent_ImageAnalyzerState, void*)
{}

void DummySurfaceCreatedCallback(OH_ArkUI_SurfaceHolder*) {}

void DummySurfaceChangedCallback(OH_ArkUI_SurfaceHolder*, uint64_t, uint64_t) {}

int g_attachCount = 0;
int g_detachCount = 0;
void* g_attachedContainer = nullptr;
void* g_detachedContainer = nullptr;
void* g_attachedRoot = nullptr;
void* g_detachedRoot = nullptr;

void ResetNativeNodeCallbackState()
{
    g_attachCount = 0;
    g_detachCount = 0;
    g_attachedContainer = nullptr;
    g_detachedContainer = nullptr;
    g_attachedRoot = nullptr;
    g_detachedRoot = nullptr;
}

void RecordAttach(void* container, void* root)
{
    ++g_attachCount;
    g_attachedContainer = container;
    g_attachedRoot = root;
}

void RecordDetach(void* container, void* root)
{
    ++g_detachCount;
    g_detachedContainer = container;
    g_detachedRoot = root;
}

enum class ModifierPatchMode {
    NULL_NODE_MODIFIERS,
    NULL_XCOMPONENT_MODIFIER,
    FAKE_XCOMPONENT_MODIFIER,
};

struct ModifierCallState {
    void* nativeXComponent = nullptr;
    ArkUINodeHandle nativeXComponentNode = nullptr;
    ArkUINodeHandle startAnalyzerNode = nullptr;
    ArkUI_NodeHandle startAnalyzerArkNode = nullptr;
    void* startAnalyzerUserData = nullptr;
    XComponentAnalyzerCallback startAnalyzerCallback = nullptr;
    int32_t startAnalyzerCount = 0;
    ArkUINodeHandle stopAnalyzerNode = nullptr;
    int32_t stopAnalyzerCount = 0;
    OH_ArkUI_SurfaceHolder* surfaceHolder = nullptr;
    ArkUINodeHandle disposeNode = nullptr;
    int32_t disposeCount = 0;
    ArkUINodeHandle autoInitializeNode = nullptr;
    bool autoInitializeArg = false;
    ArkUINodeHandle initializeNode = nullptr;
    ArkUINodeHandle finalizeNode = nullptr;
    ArkUINodeHandle isInitializedNode = nullptr;
    ArkUI_Bool initializedValue = true;
    ArkUINodeHandle frameRateNode = nullptr;
    int32_t frameRateMin = 0;
    int32_t frameRateMax = 0;
    int32_t frameRateExpected = 0;
    ArkUINodeHandle registerOnFrameNode = nullptr;
    void (*registerOnFrameCallback)(void*, uint64_t, uint64_t) = nullptr;
    void* registerOnFrameArkNode = nullptr;
    ArkUINodeHandle unregisterOnFrameNode = nullptr;
    ArkUINodeHandle needSoftKeyboardNode = nullptr;
    bool needSoftKeyboardArg = false;
    void* accessibilityProvider = reinterpret_cast<void*>(FAKE_ACCESSIBILITY_PROVIDER);
    ArkUINodeHandle accessibilityProviderNode = nullptr;
    void* disposedAccessibilityProvider = nullptr;
    int32_t disposeAccessibilityProviderCount = 0;
    void Reset()
    {
        *this = ModifierCallState();
    }
};

ModifierCallState g_modifierCallState;
ModifierPatchMode g_patchMode = ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER;
ArkUIXComponentModifier g_fakeXComponentModifier {};
ArkUINodeModifiers g_fakeNodeModifiers {};

void* FakeGetNativeXComponent(ArkUINodeHandle node)
{
    g_modifierCallState.nativeXComponentNode = node;
    return g_modifierCallState.nativeXComponent;
}

void FakeStartImageAnalyzer(
    ArkUINodeHandle node, void* arkuiNode, void* userData, XComponentAnalyzerCallback callback)
{
    ++g_modifierCallState.startAnalyzerCount;
    g_modifierCallState.startAnalyzerNode = node;
    g_modifierCallState.startAnalyzerArkNode = reinterpret_cast<ArkUI_NodeHandle>(arkuiNode);
    g_modifierCallState.startAnalyzerUserData = userData;
    g_modifierCallState.startAnalyzerCallback = callback;
}

void FakeStopImageAnalyzer(ArkUINodeHandle node)
{
    ++g_modifierCallState.stopAnalyzerCount;
    g_modifierCallState.stopAnalyzerNode = node;
}

void* FakeCreateSurfaceHolder(ArkUINodeHandle node)
{
    g_modifierCallState.nativeXComponentNode = node;
    return g_modifierCallState.surfaceHolder;
}

void FakeDisposeSurfaceHolder(ArkUINodeHandle node)
{
    ++g_modifierCallState.disposeCount;
    g_modifierCallState.disposeNode = node;
}

ArkUI_Int32 FakeSetAutoInitialize(ArkUINodeHandle node, ArkUI_Bool autoInitialize)
{
    g_modifierCallState.autoInitializeNode = node;
    g_modifierCallState.autoInitializeArg = autoInitialize;
    return AUTO_INITIALIZE_RESULT;
}

ArkUI_Int32 FakeInitialize(ArkUINodeHandle node)
{
    g_modifierCallState.initializeNode = node;
    return INITIALIZE_RESULT;
}

ArkUI_Int32 FakeIsInitialized(ArkUINodeHandle node, ArkUI_Bool* isInitialized)
{
    g_modifierCallState.isInitializedNode = node;
    *isInitialized = g_modifierCallState.initializedValue;
    return IS_INITIALIZED_RESULT;
}

ArkUI_Int32 FakeFinalize(ArkUINodeHandle node)
{
    g_modifierCallState.finalizeNode = node;
    return FINALIZE_RESULT;
}

ArkUI_Int32 FakeSetExpectedFrameRateRange(
    ArkUINodeHandle node, ArkUI_Int32 min, ArkUI_Int32 max, ArkUI_Int32 expected)
{
    g_modifierCallState.frameRateNode = node;
    g_modifierCallState.frameRateMin = min;
    g_modifierCallState.frameRateMax = max;
    g_modifierCallState.frameRateExpected = expected;
    return FRAME_RATE_RESULT;
}

ArkUI_Int32 FakeRegisterOnFrameCallback(
    ArkUINodeHandle node, void (*callback)(void*, uint64_t, uint64_t), void* arkuiNode)
{
    g_modifierCallState.registerOnFrameNode = node;
    g_modifierCallState.registerOnFrameCallback = callback;
    g_modifierCallState.registerOnFrameArkNode = arkuiNode;
    return REGISTER_FRAME_RESULT;
}

ArkUI_Int32 FakeUnregisterOnFrameCallback(ArkUINodeHandle node)
{
    g_modifierCallState.unregisterOnFrameNode = node;
    return UNREGISTER_FRAME_RESULT;
}

ArkUI_Int32 FakeSetNeedSoftKeyboard(ArkUINodeHandle node, bool needSoftKeyboard)
{
    g_modifierCallState.needSoftKeyboardNode = node;
    g_modifierCallState.needSoftKeyboardArg = needSoftKeyboard;
    return SOFT_KEYBOARD_RESULT;
}

void* FakeCreateAccessibilityProvider(ArkUINodeHandle node)
{
    g_modifierCallState.accessibilityProviderNode = node;
    return g_modifierCallState.accessibilityProvider;
}

void FakeDisposeAccessibilityProvider(void* provider)
{
    ++g_modifierCallState.disposeAccessibilityProviderCount;
    g_modifierCallState.disposedAccessibilityProvider = provider;
}

const ArkUIXComponentModifier* GetPatchedXComponentModifier()
{
    if (g_patchMode == ModifierPatchMode::NULL_XCOMPONENT_MODIFIER) {
        return nullptr;
    }
    return &g_fakeXComponentModifier;
}

const ArkUINodeModifiers* GetPatchedNodeModifiers()
{
    if (g_patchMode == ModifierPatchMode::NULL_NODE_MODIFIERS) {
        return nullptr;
    }
    return &g_fakeNodeModifiers;
}

void ConfigureFakeModifiers()
{
    static bool configured = false;
    if (configured) {
        return;
    }
    g_fakeNodeModifiers.getXComponentModifier = GetPatchedXComponentModifier;
    g_fakeXComponentModifier.getNativeXComponent = FakeGetNativeXComponent;
    g_fakeXComponentModifier.startImageAnalyzer = FakeStartImageAnalyzer;
    g_fakeXComponentModifier.stopImageAnalyzer = FakeStopImageAnalyzer;
    g_fakeXComponentModifier.createSurfaceHolder = FakeCreateSurfaceHolder;
    g_fakeXComponentModifier.dispose = FakeDisposeSurfaceHolder;
    g_fakeXComponentModifier.setAutoInitialize = FakeSetAutoInitialize;
    g_fakeXComponentModifier.initialize = FakeInitialize;
    g_fakeXComponentModifier.isInitialized = FakeIsInitialized;
    g_fakeXComponentModifier.finalize = FakeFinalize;
    g_fakeXComponentModifier.setExpectedFrameRateRange = FakeSetExpectedFrameRateRange;
    g_fakeXComponentModifier.registerOnFrameCallback = FakeRegisterOnFrameCallback;
    g_fakeXComponentModifier.unregisterOnFrameCallback = FakeUnregisterOnFrameCallback;
    g_fakeXComponentModifier.setNeedSoftKeyboard = FakeSetNeedSoftKeyboard;
    g_fakeXComponentModifier.createAccessibilityProvider = FakeCreateAccessibilityProvider;
    g_fakeXComponentModifier.disposeAccessibilityProvider = FakeDisposeAccessibilityProvider;
    configured = true;
}

class ScopedModifierPatch {
public:
    explicit ScopedModifierPatch(ModifierPatchMode mode) : mode_(mode)
    {
        ConfigureFakeModifiers();
        auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
        originalGetNodeModifiers_ = fullImpl->getNodeModifiers;
        fullImpl->getNodeModifiers = GetPatchedNodeModifiers;
        g_patchMode = mode_;
    }

    ~ScopedModifierPatch()
    {
        auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
        fullImpl->getNodeModifiers = originalGetNodeModifiers_;
        g_patchMode = ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER;
    }

private:
    ModifierPatchMode mode_;
    const ArkUINodeModifiers* (*originalGetNodeModifiers_)() = nullptr;
};

class ScopedArkUINode {
public:
    ScopedArkUINode(int32_t type, bool valid, bool bindNative = false, bool cNode = true)
    {
        if (valid && OHOS::Ace::NodeModel::GetFullImpl() != nullptr) {
            node_ = OHOS::Ace::NodeModel::CreateNode(static_cast<ArkUI_NodeType>(type));
            createdByApi_ = node_ != nullptr;
            if (node_ != nullptr) {
                node_->isBindNative = bindNative;
                node_->cNode = cNode;
                return;
            }
        }
        node_ = new ArkUI_Node();
        node_->type = type;
        node_->cNode = cNode;
        node_->isBindNative = bindNative;
        node_->uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(node_);
        if (valid) {
            OHOS::Ace::NodeModel::RegisterBindNativeNode(node_);
            registeredByApi_ = true;
        }
    }

    ~ScopedArkUINode()
    {
        if (createdByApi_ && node_ != nullptr && OHOS::Ace::NodeModel::GetFullImpl() != nullptr) {
            OHOS::Ace::NodeModel::DisposeNode(node_);
            node_ = nullptr;
            return;
        }
        if (!registeredByApi_) {
            delete node_;
        }
    }

    ArkUI_NodeHandle Get() const
    {
        return node_;
    }

    void SetUiNodeHandle(void* handle)
    {
        node_->uiNodeHandle = reinterpret_cast<ArkUINodeHandle>(handle);
    }

private:
    ArkUI_NodeHandle node_ = nullptr;
    bool createdByApi_ = false;
    bool registeredByApi_ = false;
};

class MockSurfaceConfigInterface : public XComponentSurfaceConfigInterface {
    DECLARE_ACE_TYPE(MockSurfaceConfigInterface, XComponentSurfaceConfigInterface);

public:
    int32_t SetSurfaceIsOpaque(bool isOpaque) override
    {
        ++callCount_;
        lastOpaque_ = isOpaque;
        return SURFACE_OPAQUE_RESULT;
    }

    int32_t callCount_ = 0;
    bool lastOpaque_ = false;
};

struct NativeComponentBundle {
    std::unique_ptr<NativeXComponentImpl> implOwner;
    NativeXComponentImpl* impl = nullptr;
    std::unique_ptr<OH_NativeXComponent> component;
    int surfaceToken = 0;
};

OH_NativeXComponent_TouchEvent CreateTouchEvent()
{
    OH_NativeXComponent_TouchEvent touchEvent {};
    touchEvent.id = TOUCH_EVENT_ID;
    touchEvent.touchPoints[0].id = TOUCH_EVENT_ID;
    touchEvent.touchPoints[0].x = WINDOW_X;
    touchEvent.touchPoints[0].y = WINDOW_Y;
    touchEvent.numPoints = TOUCH_POINT_COUNT;
    return touchEvent;
}

std::vector<XComponentTouchPoint> CreateTouchPoints()
{
    XComponentTouchPoint point;
    point.tiltX = TILT_X;
    point.tiltY = TILT_Y;
    point.windowX = WINDOW_X;
    point.windowY = WINDOW_Y;
    point.displayX = DISPLAY_X;
    point.displayY = DISPLAY_Y;
    point.sourceToolType = OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN;
    return { point };
}

std::vector<OH_NativeXComponent_HistoricalPoint> CreateHistoricalPoints()
{
    OH_NativeXComponent_HistoricalPoint point {};
    point.id = HISTORICAL_POINT_ID;
    point.x = HISTORICAL_POINT_X;
    point.y = HISTORICAL_POINT_Y;
    return { point };
}

OH_NativeXComponent_MouseEvent CreateMouseEvent()
{
    OH_NativeXComponent_MouseEvent mouseEvent {};
    mouseEvent.x = MOUSE_EVENT_X;
    mouseEvent.y = MOUSE_EVENT_Y;
    mouseEvent.action = OH_NATIVEXCOMPONENT_MOUSE_MOVE;
    mouseEvent.button = OH_NATIVEXCOMPONENT_LEFT_BUTTON;
    return mouseEvent;
}

OH_NativeXComponent_KeyEvent CreateKeyEvent()
{
    OH_NativeXComponent_KeyEvent keyEvent;
    keyEvent.action = OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN;
    keyEvent.code = KEY_A;
    keyEvent.sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD;
    keyEvent.deviceId = KEY_EVENT_DEVICE_ID;
    keyEvent.timestamp = KEY_EVENT_TIMESTAMP;
    keyEvent.modifierKeyStates = KEY_EVENT_KEYS;
    keyEvent.isNumLockOn = true;
    keyEvent.isCapsLockOn = false;
    keyEvent.isScrollLockOn = true;
    return keyEvent;
}

NativeComponentBundle CreateNativeComponentBundle()
{
    NativeComponentBundle bundle;
    bundle.implOwner = std::make_unique<NativeXComponentImpl>();
    bundle.impl = bundle.implOwner.get();
    bundle.component = std::make_unique<OH_NativeXComponent>(bundle.impl);
    bundle.impl->SetXComponentId(XCOMPONENT_ID);
    bundle.impl->SetXComponentWidth(static_cast<int>(XCOMPONENT_WIDTH));
    bundle.impl->SetXComponentHeight(static_cast<int>(XCOMPONENT_HEIGHT));
    bundle.impl->SetXComponentOffsetX(XCOMPONENT_OFFSET_X);
    bundle.impl->SetXComponentOffsetY(XCOMPONENT_OFFSET_Y);
    bundle.impl->SetSurface(&bundle.surfaceToken);
    bundle.impl->SetTouchEvent(CreateTouchEvent());
    bundle.impl->SetTouchPoint(CreateTouchPoints());
    bundle.impl->SetHistoricalPoint(CreateHistoricalPoints());
    bundle.impl->SetMouseEvent(CreateMouseEvent());
    bundle.impl->SetKeyEvent(CreateKeyEvent());
    bundle.impl->SetCurrentSourceType(
        { SOURCE_POINT_ID, OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD });
    bundle.impl->SetExtraMouseEventInfo({ EXTRA_MOUSE_KEYS });
    return bundle;
}

RefPtr<FrameNode> CreateRootFrameNode()
{
    static int32_t nodeId = ROOT_NODE_ID;
    return FrameNode::CreateFrameNode(
        "native_root", nodeId++, AceType::MakeRefPtr<LinearLayoutPattern>(true));
}

bool EnsureFullImplInitialized()
{
    return OHOS::Ace::NodeModel::InitialFullImpl() && OHOS::Ace::NodeModel::GetFullImpl() != nullptr;
}

void ExpectArkUiIntWrappersReturnInvalid(ArkUI_NodeHandle node)
{
    bool isInitialized = false;
    OH_NativeXComponent_ExpectedRateRange range {
        INVALID_RANGE_MIN, INVALID_RANGE_MAX, INVALID_RANGE_EXPECTED
    };
    EXPECT_EQ(OH_ArkUI_XComponent_SetAutoInitialize(node, true), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_Initialize(node), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_Finalize(node), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_IsInitialized(node, &isInitialized), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_SetExpectedFrameRateRange(node, range), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_XComponent_RegisterOnFrameCallback(node, DummyArkUIOnFrameCallback),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_UnregisterOnFrameCallback(node), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_SetNeedSoftKeyboard(node, true), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

void ExpectArkUiPointerWrappersReturnNull(ArkUI_NodeHandle node)
{
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_Create(node), nullptr);
    EXPECT_EQ(OH_ArkUI_AccessibilityProvider_Create(node), nullptr);
}
} // namespace

class XComponentNativeInterfaceTestNg : public testing::Test {
public:
    void SetUp() override
    {
        g_modifierCallState.Reset();
        ResetNativeNodeCallbackState();
    }
};

/**
 * @tc.name: NativeInterfaceGetXComponentId001
 * @tc.desc: Test OH_NativeXComponent_GetXComponentId parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceGetXComponentId001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    char id[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t size = sizeof(id);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentId(nullptr, id, &size), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetXComponentId(bundle.component.get(), nullptr, &size),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetXComponentId(bundle.component.get(), id, nullptr),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    size = 0;
    EXPECT_EQ(
        OH_NativeXComponent_GetXComponentId(bundle.component.get(), id, &size),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    size = OH_XCOMPONENT_ID_LEN_MAX + 2;
    EXPECT_EQ(
        OH_NativeXComponent_GetXComponentId(bundle.component.get(), id, &size),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: NativeInterfaceGetXComponentId002
 * @tc.desc: Test OH_NativeXComponent_GetXComponentId success path.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceGetXComponentId002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    char id[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
    uint64_t size = sizeof(id);
    EXPECT_EQ(
        OH_NativeXComponent_GetXComponentId(bundle.component.get(), id, &size),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(size, sizeof(XCOMPONENT_ID) - 1);
    EXPECT_STREQ(id, XCOMPONENT_ID);
}

/**
 * @tc.name: NativeInterfaceGeometryAndEvent001
 * @tc.desc: Test geometry and event wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceGeometryAndEvent001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    uint64_t width = 0;
    uint64_t height = 0;
    double x = 0.0;
    double y = 0.0;
    OH_NativeXComponent_TouchEvent touchEvent {};
    OH_NativeXComponent_MouseEvent mouseEvent {};
    int32_t size = 0;
    OH_NativeXComponent_HistoricalPoint* points = nullptr;
    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(nullptr, &bundle.surfaceToken, &width, &height),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(nullptr, &bundle.surfaceToken, &x, &y),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEvent(nullptr, &bundle.surfaceToken, &touchEvent),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetHistoricalPoints(nullptr, &bundle.surfaceToken, &size, &points),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetMouseEvent(nullptr, &bundle.surfaceToken, &mouseEvent),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: NativeInterfaceGeometryAndEvent002
 * @tc.desc: Test geometry and event wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceGeometryAndEvent002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    uint64_t width = 0;
    uint64_t height = 0;
    double x = 0.0;
    double y = 0.0;
    OH_NativeXComponent_TouchEvent touchEvent {};
    OH_NativeXComponent_MouseEvent mouseEvent {};
    int32_t size = 0;
    OH_NativeXComponent_HistoricalPoint* points = nullptr;
    EXPECT_EQ(OH_NativeXComponent_GetXComponentSize(bundle.component.get(), &bundle.surfaceToken, &width, &height),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(width, XCOMPONENT_WIDTH);
    EXPECT_EQ(height, XCOMPONENT_HEIGHT);
    EXPECT_EQ(OH_NativeXComponent_GetXComponentOffset(bundle.component.get(), &bundle.surfaceToken, &x, &y),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_DOUBLE_EQ(x, XCOMPONENT_OFFSET_X);
    EXPECT_DOUBLE_EQ(y, XCOMPONENT_OFFSET_Y);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEvent(bundle.component.get(), &bundle.surfaceToken, &touchEvent),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(touchEvent.numPoints, 1u);
    EXPECT_EQ(OH_NativeXComponent_GetHistoricalPoints(bundle.component.get(), &bundle.surfaceToken, &size, &points),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(size, static_cast<int32_t>(TOUCH_POINT_COUNT));
    EXPECT_EQ(points[0].id, HISTORICAL_POINT_ID);
    EXPECT_EQ(OH_NativeXComponent_GetMouseEvent(bundle.component.get(), &bundle.surfaceToken, &mouseEvent),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(mouseEvent.action, OH_NATIVEXCOMPONENT_MOUSE_MOVE);
}

/**
 * @tc.name: NativeInterfaceTouchPoint001
 * @tc.desc: Test touch point wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceTouchPoint001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_TouchPointToolType toolType = OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    float value = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointToolType(nullptr, 0, &toolType),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltX(nullptr, 0, &value), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltY(nullptr, 0, &value), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowX(nullptr, 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowY(nullptr, 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayX(nullptr, 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayY(nullptr, 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEventSourceType(nullptr, SOURCE_POINT_ID, &sourceType),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEventSourceType(bundle.component.get(), SOURCE_POINT_ID, nullptr),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: NativeInterfaceTouchPoint002
 * @tc.desc: Test touch point wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceTouchPoint002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_TouchPointToolType toolType = OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    float value = 0.0f;
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointToolType(bundle.component.get(), 0, &toolType),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(toolType, OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltX(bundle.component.get(), 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_FLOAT_EQ(value, TILT_X);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointTiltY(bundle.component.get(), 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_FLOAT_EQ(value, TILT_Y);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowX(bundle.component.get(), 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_FLOAT_EQ(value, WINDOW_X);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointWindowY(bundle.component.get(), 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_FLOAT_EQ(value, WINDOW_Y);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayX(bundle.component.get(), 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_FLOAT_EQ(value, DISPLAY_X);
    EXPECT_EQ(OH_NativeXComponent_GetTouchPointDisplayY(bundle.component.get(), 0, &value),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_FLOAT_EQ(value, DISPLAY_Y);
    EXPECT_EQ(OH_NativeXComponent_GetTouchEventSourceType(bundle.component.get(), SOURCE_POINT_ID, &sourceType),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(sourceType, OH_NATIVEXCOMPONENT_SOURCE_TYPE_TOUCHPAD);
}

/**
 * @tc.name: NativeInterfaceRegister001
 * @tc.desc: Test registration wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceRegister001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_Callback callback {};
    OH_NativeXComponent_MouseEvent_Callback mouseCallback {};
    EXPECT_EQ(OH_NativeXComponent_RegisterCallback(nullptr, &callback), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterMouseEventCallback(nullptr, &mouseCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterFocusEventCallback(nullptr, DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterKeyEventCallback(nullptr, DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterBlurEventCallback(nullptr, DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallbackWithResult(nullptr, DummyKeyResultCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterSurfaceShowCallback(nullptr, DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterSurfaceHideCallback(nullptr, DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_RegisterOnTouchInterceptCallback(nullptr, DummyTouchInterceptCallback),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterUIInputEventCallback(bundle.component.get(), nullptr,
            ARKUI_UIINPUTEVENT_TYPE_AXIS),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeInterfaceRegister002
 * @tc.desc: Test registration wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceRegister002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_Callback callback {
        DummyComponentWindowCallback, DummyComponentWindowCallback,
        DummyComponentWindowCallback, DummyComponentWindowCallback
    };
    OH_NativeXComponent_MouseEvent_Callback mouseCallback {
        DummyComponentWindowCallback, DummyHoverCallback
    };
    EXPECT_EQ(OH_NativeXComponent_RegisterCallback(bundle.component.get(), &callback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetCallback(), &callback);
    EXPECT_EQ(OH_NativeXComponent_RegisterMouseEventCallback(bundle.component.get(), &mouseCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetMouseEventCallback(), &mouseCallback);
    EXPECT_EQ(OH_NativeXComponent_RegisterFocusEventCallback(bundle.component.get(), DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetFocusEventCallback(), DummyComponentWindowCallback);
    EXPECT_EQ(OH_NativeXComponent_RegisterKeyEventCallback(bundle.component.get(), DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetKeyEventCallback(), DummyComponentWindowCallback);
    EXPECT_EQ(OH_NativeXComponent_RegisterBlurEventCallback(bundle.component.get(), DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetBlurEventCallback(), DummyComponentWindowCallback);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterKeyEventCallbackWithResult(bundle.component.get(), DummyKeyResultCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetKeyEventCallbackWithResult(), DummyKeyResultCallback);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterSurfaceShowCallback(bundle.component.get(), DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetSurfaceShowCallback(), DummyComponentWindowCallback);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterSurfaceHideCallback(bundle.component.get(), DummyComponentWindowCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetSurfaceHideCallback(), DummyComponentWindowCallback);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterOnTouchInterceptCallback(bundle.component.get(), DummyTouchInterceptCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetOnTouchInterceptCallback(), DummyTouchInterceptCallback);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterUIInputEventCallback(
            bundle.component.get(), DummyUIInputEventCallback, ARKUI_UIINPUTEVENT_TYPE_AXIS),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(bundle.impl->GetUIAxisEventCallback(), DummyUIInputEventCallback);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterUIInputEventCallback(
            bundle.component.get(), DummyUIInputEventCallback, ARKUI_UIINPUTEVENT_TYPE_TOUCH),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeInterfaceKeyEvent001
 * @tc.desc: Test key event wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceKeyEvent001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_KeyEvent* keyEvent = nullptr;
    OH_NativeXComponent_KeyAction action = OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    OH_NativeXComponent_KeyCode code = KEY_UNKNOWN;
    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    int64_t value = 0;
    uint64_t keys = 0;
    bool lockState = false;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEvent(nullptr, &keyEvent), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventAction(nullptr, &action), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCode(nullptr, &code), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventSourceType(nullptr, &sourceType),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventDeviceId(nullptr, &value), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventTimestamp(nullptr, &value),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventModifierKeyStates(nullptr, &keys),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventNumLockState(nullptr, &lockState),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventCapsLockState(nullptr, &lockState),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventScrollLockState(nullptr, &lockState),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeInterfaceKeyEvent002
 * @tc.desc: Test key event wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceKeyEvent002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_KeyEvent* keyEvent = nullptr;
    OH_NativeXComponent_KeyAction action = OH_NATIVEXCOMPONENT_KEY_ACTION_UNKNOWN;
    OH_NativeXComponent_KeyCode code = KEY_UNKNOWN;
    OH_NativeXComponent_EventSourceType sourceType = OH_NATIVEXCOMPONENT_SOURCE_TYPE_UNKNOWN;
    int64_t value = 0;
    uint64_t keys = 0;
    bool lockState = false;
    EXPECT_EQ(OH_NativeXComponent_GetKeyEvent(bundle.component.get(), &keyEvent), OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventAction(keyEvent, &action), OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(action, OH_NATIVEXCOMPONENT_KEY_ACTION_DOWN);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventCode(keyEvent, &code), OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(code, KEY_A);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventSourceType(keyEvent, &sourceType),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(sourceType, OH_NATIVEXCOMPONENT_SOURCE_TYPE_KEYBOARD);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventDeviceId(keyEvent, &value), OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(value, KEY_EVENT_DEVICE_ID);
    EXPECT_EQ(OH_NativeXComponent_GetKeyEventTimestamp(keyEvent, &value), OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(value, KEY_EVENT_TIMESTAMP);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventModifierKeyStates(keyEvent, &keys),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, KEY_EVENT_KEYS);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventNumLockState(keyEvent, &lockState),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(lockState);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventCapsLockState(keyEvent, &lockState),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(lockState);
    EXPECT_EQ(
        OH_NativeXComponent_GetKeyEventScrollLockState(keyEvent, &lockState),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(lockState);
}

/**
 * @tc.name: NativeInterfaceFrameRate001
 * @tc.desc: Test frame rate and soft keyboard wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceFrameRate001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    OH_NativeXComponent_ExpectedRateRange range {
        DEFAULT_RANGE_MIN, DEFAULT_RANGE_MAX, DEFAULT_RANGE_EXPECTED
    };
    EXPECT_EQ(
        OH_NativeXComponent_SetExpectedFrameRateRange(nullptr, &range),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_SetExpectedFrameRateRange(bundle.component.get(), nullptr),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_RegisterOnFrameCallback(nullptr, DummyNativeOnFrameCallback),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_UnregisterOnFrameCallback(nullptr), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_SetNeedSoftKeyboard(nullptr, true), OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: NativeInterfaceFrameRate002
 * @tc.desc: Test frame rate and soft keyboard wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceFrameRate002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    bool expectedCallbackCalled = false;
    bool registerFrameCalled = false;
    bool unregisterFrameCalled = false;
    OH_NativeXComponent_ExpectedRateRange range {
        DEFAULT_RANGE_MIN, DEFAULT_RANGE_MAX, DEFAULT_RANGE_EXPECTED
    };
    bundle.impl->SetExpectedRateRangeEventCallback([&expectedCallbackCalled]() { expectedCallbackCalled = true; });
    bundle.impl->SetOnFrameEventCallback([&registerFrameCalled]() { registerFrameCalled = true; });
    bundle.impl->SetUnregisterOnFrameEventCallback([&unregisterFrameCalled]() { unregisterFrameCalled = true; });
    EXPECT_EQ(OH_NativeXComponent_SetExpectedFrameRateRange(bundle.component.get(), &range),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_TRUE(expectedCallbackCalled);
    EXPECT_EQ(bundle.impl->GetRateRange(), &range);
    EXPECT_EQ(OH_NativeXComponent_RegisterOnFrameCallback(bundle.component.get(), DummyNativeOnFrameCallback),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_TRUE(registerFrameCalled);
    EXPECT_EQ(bundle.impl->GetOnFrameCallback(), DummyNativeOnFrameCallback);
    EXPECT_EQ(OH_NativeXComponent_UnregisterOnFrameCallback(bundle.component.get()),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_TRUE(unregisterFrameCalled);
    EXPECT_EQ(bundle.impl->GetOnFrameCallback(), nullptr);
    EXPECT_EQ(OH_NativeXComponent_SetNeedSoftKeyboard(bundle.component.get(), true),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_TRUE(bundle.impl->IsNeedSoftKeyboard());
}

/**
 * @tc.name: NativeInterfaceAttachDetach001
 * @tc.desc: Test attach and detach wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceAttachDetach001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    ScopedArkUINode nonCNode(ARKUI_NODE_TEXT, false, false, false);
    EXPECT_EQ(OH_NativeXComponent_AttachNativeRootNode(nullptr, nonCNode.Get()),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_AttachNativeRootNode(bundle.component.get(), nullptr),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_AttachNativeRootNode(bundle.component.get(), nonCNode.Get()),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_DetachNativeRootNode(nullptr, nonCNode.Get()),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_DetachNativeRootNode(bundle.component.get(), nullptr),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_DetachNativeRootNode(bundle.component.get(), nonCNode.Get()),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
}

/**
 * @tc.name: NativeInterfaceAttachDetach002
 * @tc.desc: Test attach and detach wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceAttachDetach002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    auto rootFrameNode = CreateRootFrameNode();
    ScopedArkUINode rootNode(ARKUI_NODE_TEXT, false);
    int containerToken = CONTAINER_TOKEN;
    rootNode.SetUiNodeHandle(AceType::RawPtr(rootFrameNode));
    bundle.impl->registerContaner(&containerToken);
    bundle.impl->registerNativeNodeCallbacks(RecordAttach, RecordDetach);
    EXPECT_EQ(OH_NativeXComponent_AttachNativeRootNode(bundle.component.get(), rootNode.Get()),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(g_attachCount, SINGLE_CALL_COUNT);
    EXPECT_EQ(g_attachedContainer, &containerToken);
    EXPECT_EQ(g_attachedRoot, AceType::RawPtr(rootFrameNode));
    EXPECT_EQ(OH_NativeXComponent_DetachNativeRootNode(bundle.component.get(), rootNode.Get()),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_EQ(g_detachCount, SINGLE_CALL_COUNT);
    EXPECT_EQ(g_detachedContainer, &containerToken);
    EXPECT_EQ(g_detachedRoot, AceType::RawPtr(rootFrameNode));
}

/**
 * @tc.name: NativeInterfaceAccessibility001
 * @tc.desc: Test accessibility and extra mouse wrapper parameter checks.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceAccessibility001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    ArkUI_AccessibilityProvider* provider = nullptr;
    OH_NativeXComponent_ExtraMouseEventInfo* extraInfo = nullptr;
    uint64_t keys = 0;
    EXPECT_EQ(
        OH_NativeXComponent_GetNativeAccessibilityProvider(nullptr, &provider),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetNativeAccessibilityProvider(bundle.component.get(), nullptr),
        OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER);
    EXPECT_EQ(
        OH_NativeXComponent_GetExtraMouseEventInfo(nullptr, &extraInfo),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_NativeXComponent_GetMouseEventModifierKeyStates(nullptr, &keys),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeInterfaceAccessibility002
 * @tc.desc: Test accessibility and extra mouse wrapper success paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceAccessibility002, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    ArkUI_AccessibilityProvider* provider = nullptr;
    OH_NativeXComponent_ExtraMouseEventInfo* extraInfo = nullptr;
    uint64_t keys = 0;
    EXPECT_EQ(
        OH_NativeXComponent_GetNativeAccessibilityProvider(bundle.component.get(), &provider),
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS);
    EXPECT_NE(provider, nullptr);
    EXPECT_EQ(
        OH_NativeXComponent_GetExtraMouseEventInfo(bundle.component.get(), &extraInfo),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_NE(extraInfo, nullptr);
    EXPECT_EQ(
        OH_NativeXComponent_GetMouseEventModifierKeyStates(extraInfo, &keys),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(keys, EXTRA_MOUSE_KEYS);
}

/**
 * @tc.name: NativeInterfaceArkUiPreInit001
 * @tc.desc: Test ArkUI wrappers when full node API is not initialized.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceArkUiPreInit001, TestSize.Level1)
{
    ASSERT_EQ(OHOS::Ace::NodeModel::GetFullImpl(), nullptr);
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ExpectArkUiIntWrappersReturnInvalid(node.Get());
}

/**
 * @tc.name: NativeInterfaceArkUiPreInit002
 * @tc.desc: Test ArkUI pointer wrappers when full node API is not initialized.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceArkUiPreInit002, TestSize.Level1)
{
    ASSERT_EQ(OHOS::Ace::NodeModel::GetFullImpl(), nullptr);
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ArkUI_XComponentSurfaceConfig config;
    auto* holder = new OH_ArkUI_SurfaceHolder();
    holder->node_ = node.Get();
    holder->config_ = &config;
    config.surfaceHolders_.insert(holder);
    ExpectArkUiPointerWrappersReturnNull(node.Get());
    OH_ArkUI_AccessibilityProvider_Dispose(
        reinterpret_cast<ArkUI_AccessibilityProvider*>(DISPOSE_PROVIDER_PTR_1));
    OH_ArkUI_SurfaceHolder_Dispose(holder);
    EXPECT_TRUE(config.surfaceHolders_.empty());
}

/**
 * @tc.name: NativeInterfaceGetNativeXComponent001
 * @tc.desc: Test OH_NativeXComponent_GetNativeXComponent branches.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceGetNativeXComponent001, TestSize.Level1)
{
    auto bundle = CreateNativeComponentBundle();
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode invalidTypeNode(ARKUI_NODE_TEXT, false);
    ScopedArkUINode validNode(ARKUI_NODE_XCOMPONENT, false);
    ScopedModifierPatch patch(ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER);
    g_modifierCallState.nativeXComponent = bundle.component.get();
    EXPECT_EQ(OH_NativeXComponent_GetNativeXComponent(nullptr), nullptr);
    EXPECT_EQ(OH_NativeXComponent_GetNativeXComponent(invalidTypeNode.Get()), nullptr);
    EXPECT_EQ(OH_NativeXComponent_GetNativeXComponent(validNode.Get()), bundle.component.get());
    EXPECT_EQ(g_modifierCallState.nativeXComponentNode, validNode.Get()->uiNodeHandle);
}

/**
 * @tc.name: NativeInterfaceArkUiNodeModifiers001
 * @tc.desc: Test ArkUI wrappers when node modifiers are unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceArkUiNodeModifiers001, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ScopedModifierPatch patch(ModifierPatchMode::NULL_NODE_MODIFIERS);
    ExpectArkUiIntWrappersReturnInvalid(node.Get());
    ExpectArkUiPointerWrappersReturnNull(node.Get());
    OH_ArkUI_AccessibilityProvider_Dispose(
        reinterpret_cast<ArkUI_AccessibilityProvider*>(DISPOSE_PROVIDER_PTR_2));
    EXPECT_EQ(g_modifierCallState.disposeAccessibilityProviderCount, 0);
}

/**
 * @tc.name: NativeInterfaceArkUiNodeModifiers002
 * @tc.desc: Test ArkUI wrappers when XComponent modifier is unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceArkUiNodeModifiers002, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ScopedModifierPatch patch(ModifierPatchMode::NULL_XCOMPONENT_MODIFIER);
    ExpectArkUiIntWrappersReturnInvalid(node.Get());
    ExpectArkUiPointerWrappersReturnNull(node.Get());
    OH_ArkUI_AccessibilityProvider_Dispose(
        reinterpret_cast<ArkUI_AccessibilityProvider*>(DISPOSE_PROVIDER_PTR_3));
    EXPECT_EQ(g_modifierCallState.disposeAccessibilityProviderCount, 0);
}

/**
 * @tc.name: NativeInterfaceSurfaceHolderDispose002
 * @tc.desc: Test surface holder dispose when node modifiers are unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceHolderDispose002, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ArkUI_XComponentSurfaceConfig config;
    auto* holder = new OH_ArkUI_SurfaceHolder();
    holder->node_ = node.Get();
    holder->config_ = &config;
    config.surfaceHolders_.insert(holder);
    ScopedModifierPatch patch(ModifierPatchMode::NULL_NODE_MODIFIERS);
    OH_ArkUI_SurfaceHolder_Dispose(holder);
    EXPECT_EQ(g_modifierCallState.disposeCount, 0);
    EXPECT_TRUE(config.surfaceHolders_.empty());
}

/**
 * @tc.name: NativeInterfaceSurfaceHolderDispose003
 * @tc.desc: Test surface holder dispose when XComponent modifier is unavailable.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceHolderDispose003, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ArkUI_XComponentSurfaceConfig config;
    auto* holder = new OH_ArkUI_SurfaceHolder();
    holder->node_ = node.Get();
    holder->config_ = &config;
    config.surfaceHolders_.insert(holder);
    ScopedModifierPatch patch(ModifierPatchMode::NULL_XCOMPONENT_MODIFIER);
    OH_ArkUI_SurfaceHolder_Dispose(holder);
    EXPECT_EQ(g_modifierCallState.disposeCount, 0);
    EXPECT_TRUE(config.surfaceHolders_.empty());
}

/**
 * @tc.name: NativeInterfaceImageAnalyzer001
 * @tc.desc: Test image analyzer wrapper branches.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceImageAnalyzer001, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode invalidNode(ARKUI_NODE_XCOMPONENT, false);
    ScopedArkUINode wrongTypeNode(ARKUI_NODE_TEXT, true);
    ScopedArkUINode validNode(ARKUI_NODE_XCOMPONENT, true);
    ScopedModifierPatch patch(ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER);
    int userData = ANALYZER_USER_DATA;
    EXPECT_EQ(OH_ArkUI_XComponent_StartImageAnalyzer(invalidNode.Get(), &userData, DummyImageAnalyzerCallback),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_StartImageAnalyzer(wrongTypeNode.Get(), &userData, DummyImageAnalyzerCallback),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_StartImageAnalyzer(validNode.Get(), &userData, nullptr),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_StartImageAnalyzer(validNode.Get(), &userData, DummyImageAnalyzerCallback),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(g_modifierCallState.startAnalyzerCount, SINGLE_CALL_COUNT);
    EXPECT_EQ(g_modifierCallState.startAnalyzerArkNode, validNode.Get());
    EXPECT_EQ(g_modifierCallState.startAnalyzerUserData, &userData);
    EXPECT_EQ(OH_ArkUI_XComponent_StopImageAnalyzer(invalidNode.Get()), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_StopImageAnalyzer(wrongTypeNode.Get()), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_XComponent_StopImageAnalyzer(validNode.Get()), OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(g_modifierCallState.stopAnalyzerCount, SINGLE_CALL_COUNT);
}

/**
 * @tc.name: NativeInterfaceSurfaceHolderCreate001
 * @tc.desc: Test surface holder creation branches.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceHolderCreate001, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode invalidNode(ARKUI_NODE_XCOMPONENT, false);
    ScopedArkUINode wrongTypeNode(ARKUI_NODE_TEXT, true);
    ScopedArkUINode validNode(ARKUI_NODE_XCOMPONENT, true);
    ScopedModifierPatch patch(ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_Create(invalidNode.Get()), nullptr);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_Create(wrongTypeNode.Get()), nullptr);
    g_modifierCallState.surfaceHolder = nullptr;
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_Create(validNode.Get()), nullptr);
    auto* rawHolder = new OH_ArkUI_SurfaceHolder();
    g_modifierCallState.surfaceHolder = rawHolder;
    auto* holder = OH_ArkUI_SurfaceHolder_Create(validNode.Get());
    ASSERT_EQ(holder, rawHolder);
    EXPECT_EQ(holder->node_, validNode.Get());
    delete holder;
}

/**
 * @tc.name: NativeInterfaceSurfaceHolderDispose001
 * @tc.desc: Test surface holder dispose branches.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceHolderDispose001, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode validNode(ARKUI_NODE_XCOMPONENT, true);
    ArkUI_XComponentSurfaceConfig invalidConfig;
    auto* invalidHolder = new OH_ArkUI_SurfaceHolder();
    invalidHolder->config_ = &invalidConfig;
    invalidConfig.surfaceHolders_.insert(invalidHolder);
    OH_ArkUI_SurfaceHolder_Dispose(nullptr);
    OH_ArkUI_SurfaceHolder_Dispose(invalidHolder);
    EXPECT_TRUE(invalidConfig.surfaceHolders_.empty());
    ArkUI_XComponentSurfaceConfig config;
    auto* holder = new OH_ArkUI_SurfaceHolder();
    holder->node_ = validNode.Get();
    holder->config_ = &config;
    config.surfaceHolders_.insert(holder);
    ScopedModifierPatch patch(ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER);
    OH_ArkUI_SurfaceHolder_Dispose(holder);
    EXPECT_EQ(g_modifierCallState.disposeCount, SINGLE_CALL_COUNT);
    EXPECT_TRUE(config.surfaceHolders_.empty());
}

/**
 * @tc.name: NativeInterfaceArkUiSuccess001
 * @tc.desc: Test ArkUI wrapper success paths with fake modifier.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceArkUiSuccess001, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ScopedModifierPatch patch(ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER);
    OH_NativeXComponent_ExpectedRateRange range {
        CUSTOM_RANGE_MIN, DEFAULT_RANGE_MAX, CUSTOM_RANGE_EXPECTED
    };
    bool isInitialized = false;
    EXPECT_EQ(OH_ArkUI_XComponent_SetAutoInitialize(node.Get(), true), AUTO_INITIALIZE_RESULT);
    EXPECT_TRUE(g_modifierCallState.autoInitializeArg);
    EXPECT_EQ(OH_ArkUI_XComponent_Initialize(node.Get()), INITIALIZE_RESULT);
    EXPECT_EQ(OH_ArkUI_XComponent_Finalize(node.Get()), FINALIZE_RESULT);
    EXPECT_EQ(OH_ArkUI_XComponent_IsInitialized(node.Get(), &isInitialized), IS_INITIALIZED_RESULT);
    EXPECT_TRUE(isInitialized);
    EXPECT_EQ(OH_ArkUI_XComponent_SetExpectedFrameRateRange(node.Get(), range), FRAME_RATE_RESULT);
    EXPECT_EQ(g_modifierCallState.frameRateExpected, CUSTOM_RANGE_EXPECTED);
    EXPECT_EQ(
        OH_ArkUI_XComponent_RegisterOnFrameCallback(node.Get(), DummyArkUIOnFrameCallback),
        REGISTER_FRAME_RESULT);
    EXPECT_EQ(g_modifierCallState.registerOnFrameArkNode, node.Get());
    EXPECT_EQ(OH_ArkUI_XComponent_UnregisterOnFrameCallback(node.Get()), UNREGISTER_FRAME_RESULT);
    EXPECT_EQ(OH_ArkUI_XComponent_SetNeedSoftKeyboard(node.Get(), true), SOFT_KEYBOARD_RESULT);
    EXPECT_TRUE(g_modifierCallState.needSoftKeyboardArg);
}

/**
 * @tc.name: NativeInterfaceAccessibilityProvider001
 * @tc.desc: Test ArkUI accessibility provider create and dispose paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceAccessibilityProvider001, TestSize.Level1)
{
    ASSERT_TRUE(EnsureFullImplInitialized());
    ScopedArkUINode node(ARKUI_NODE_XCOMPONENT, true);
    ScopedModifierPatch patch(ModifierPatchMode::FAKE_XCOMPONENT_MODIFIER);
    auto* provider = OH_ArkUI_AccessibilityProvider_Create(node.Get());
    EXPECT_EQ(provider, reinterpret_cast<ArkUI_AccessibilityProvider*>(g_modifierCallState.accessibilityProvider));
    OH_ArkUI_AccessibilityProvider_Dispose(nullptr);
    OH_ArkUI_AccessibilityProvider_Dispose(provider);
    EXPECT_EQ(g_modifierCallState.disposeAccessibilityProviderCount, SINGLE_CALL_COUNT);
    EXPECT_EQ(g_modifierCallState.disposedAccessibilityProvider, provider);
}

/**
 * @tc.name: NativeInterfaceSurfaceHolderHelper001
 * @tc.desc: Test surface holder helper wrappers.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceHolderHelper001, TestSize.Level1)
{
    OH_ArkUI_SurfaceHolder holder;
    ArkUI_XComponentSurfaceConfig config;
    auto interface = AceType::MakeRefPtr<MockSurfaceConfigInterface>();
    OH_ArkUI_SurfaceCallback callback {};
    int userData = SURFACE_HOLDER_USER_DATA;
    int nativeWindow = NATIVE_WINDOW_TOKEN;
    holder.xComponentSurfaceConfigInterface_ = interface;
    holder.nativeWindow_ = reinterpret_cast<OHNativeWindow*>(&nativeWindow);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_SetUserData(nullptr, &userData), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_SetUserData(&holder, &userData), OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_GetUserData(nullptr), nullptr);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_GetUserData(&holder), &userData);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_AddSurfaceCallback(nullptr, &callback), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_AddSurfaceCallback(&holder, &callback), OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(
        OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(nullptr, &callback),
        OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_SurfaceHolder_RemoveSurfaceCallback(&holder, &callback),
        OHOS::Ace::ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_XComponent_GetNativeWindow(nullptr), nullptr);
    EXPECT_EQ(OH_ArkUI_XComponent_GetNativeWindow(&holder), holder.nativeWindow_);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_SetSurfaceConfig(nullptr, &config), OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_SurfaceHolder_SetSurfaceConfig(&holder, &config), SURFACE_OPAQUE_RESULT);
    EXPECT_EQ(interface->callCount_, SINGLE_CALL_COUNT);
}

/**
 * @tc.name: NativeInterfaceSurfaceCallback001
 * @tc.desc: Test surface callback wrapper paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceCallback001, TestSize.Level1)
{
    auto* callback = OH_ArkUI_SurfaceCallback_Create();
    ASSERT_NE(callback, nullptr);
    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(nullptr, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(nullptr, DummySurfaceChangedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(nullptr, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(nullptr, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(nullptr, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceCreatedEvent(callback, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceChangedEvent(callback, DummySurfaceChangedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceDestroyedEvent(callback, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceShowEvent(callback, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_SetSurfaceHideEvent(callback, DummySurfaceCreatedCallback);
    EXPECT_EQ(callback->OnSurfaceCreated, DummySurfaceCreatedCallback);
    EXPECT_EQ(callback->OnSurfaceChanged, DummySurfaceChangedCallback);
    EXPECT_EQ(callback->OnSurfaceDestroyed, DummySurfaceCreatedCallback);
    EXPECT_EQ(callback->onSurfaceShow, DummySurfaceCreatedCallback);
    EXPECT_EQ(callback->onSurfaceHide, DummySurfaceCreatedCallback);
    OH_ArkUI_SurfaceCallback_Dispose(callback);
}

/**
 * @tc.name: NativeInterfaceSurfaceConfig001
 * @tc.desc: Test surface config wrapper paths.
 * @tc.type: FUNC
 */
HWTEST_F(XComponentNativeInterfaceTestNg, NativeInterfaceSurfaceConfig001, TestSize.Level1)
{
    auto* config = OH_ArkUI_XComponentSurfaceConfig_Create();
    ASSERT_NE(config, nullptr);
    auto interface = AceType::MakeRefPtr<MockSurfaceConfigInterface>();
    auto* holder = new OH_ArkUI_SurfaceHolder();
    holder->xComponentSurfaceConfigInterface_ = interface;
    config->surfaceHolders_.insert(nullptr);
    config->surfaceHolders_.insert(holder);
    OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(nullptr, true);
    OH_ArkUI_XComponentSurfaceConfig_SetIsOpaque(config, true);
    EXPECT_TRUE(config->isOpaque_);
    EXPECT_EQ(interface->callCount_, SINGLE_CALL_COUNT);
    EXPECT_TRUE(interface->lastOpaque_);
    EXPECT_EQ(holder->config_, config);
    OH_ArkUI_XComponentSurfaceConfig_Dispose(config);
    EXPECT_EQ(holder->config_, nullptr);
    delete holder;
}

} // namespace OHOS::Ace::NG
