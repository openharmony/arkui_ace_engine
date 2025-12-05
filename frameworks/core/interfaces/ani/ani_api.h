/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/components/common/layout/constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ARKUI_ANI_API_VERSION 100
#define EXTRA_INFO_MAX_LENGTH 1024
#define ARKUI_ANI_MODIFIER_FUNCTION_NAME "GetArkUIAniModifiers"
const float DEFAULT_SNAPSHOT_SCALE = 1.f;
const int32_t DEFAULT_DELAY_TIME = 300;

struct _ArkUIStyledString;
struct _ArkUINode;
struct _ArkUIContentSlot;
struct _ArkUINodeContent;
struct _ArkUICanvasRenderer;
struct _ArkUIImageData;
struct _ArkUIImageBitmap;
struct _ArkUIDrawingRenderingContext;
struct _ArkUICanvasRenderingContext;
typedef class __ani_ref* ani_ref;
typedef class __ani_object* ani_object;
typedef struct __ani_env ani_env;
typedef uint8_t ani_boolean;
typedef int32_t ani_int;
typedef int64_t ani_long;
typedef double  ani_double;
typedef class __ani_fn_object *ani_fn_object;
typedef class __ani_string* ani_string;
typedef class __ani_enum_item* ani_enum_item;
typedef class __ani_error* ani_error;
typedef struct __ani_resolver *ani_resolver;
typedef struct napi_env__* napi_env;
typedef struct napi_value__* napi_value;
typedef class __ani_array* ani_array;
typedef _ArkUINode* ArkUINodeHandle;
typedef int ArkUI_Int32;
typedef uint32_t ArkUI_Uint32;
typedef size_t ani_size;
typedef _ArkUIContentSlot* ArkUIContentSlot;
typedef _ArkUINodeContent* ArkUINodeContent;
typedef _ArkUIStyledString* ArkUIStyledString;
typedef _ArkUICanvasRenderer* ArkUICanvasRenderer;
typedef _ArkUIImageData* ArkUIImageData;
typedef _ArkUIImageBitmap* ArkUIImageBitmap;
typedef _ArkUIDrawingRenderingContext* ArkUIDrawingRenderingContext;
typedef _ArkUICanvasRenderingContext* ArkUICanvasRenderingContext;
typedef void* ArkUIAniICurve;
typedef int32_t ArkUIAniCurve;
typedef const char* ArkUIAniString;
struct Array_ResourceColor;
struct Ark_ResourceColor;
typedef struct webview_WebviewControllerPeer {
    std::function<int32_t()> getWebIdFunc = nullptr;
    std::function<void(int32_t)> completeWindowNewFunc = nullptr;
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    std::function<void(int32_t)> setWebIdFunc = nullptr;
    std::function<void(const std::string&)> setHapPathFunc = nullptr;
    std::function<void(int32_t)> setWebDetachFunc = nullptr;
} WebviewControllerPeer;

typedef struct NodeAdapterInfo {
    std::function<void(ani_double)> onAttachToNode = nullptr;
    std::function<void(void)> onDetachFromNode = nullptr;
    std::function<int32_t(ani_double)> onGetId = nullptr;
    std::function<ani_long(ani_double)> onCreateChild = nullptr;
    std::function<void(ani_double, ani_double)> onDisposeChild = nullptr;
    std::function<void(ani_double, ani_double)> onUpdateChild = nullptr;
} NodeAdapterInfo;

typedef struct AniDoubleArray {
    std::unique_ptr<ani_double[]> data;
    ani_size size = 0;
} AniDoubleArray;

typedef ani_object (*ArkUIAniArithmeticAddFunction)(ani_env*, ani_object, ani_object);
typedef ani_object (*ArkUIAniArithmeticMinusFunction)(ani_env*, ani_object, ani_object);
typedef ani_object (*ArkUIAniArithmeticMultiplyFunction)(ani_env*, ani_object, float);
typedef bool (*ArkUIAniArithmeticEqualFunction)(ani_env*, ani_object, ani_object);
typedef ani_object (*ArkUIAniCreateObjectFunction)(ani_env*, ani_object);
typedef void (*ArkUIAniDeleteObjectFunction)(ani_env*, ani_object);

class SharedPointerWrapper {
public:
    SharedPointerWrapper() : ptr_(nullptr) {}
    SharedPointerWrapper(std::shared_ptr<void> ptr) : ptr_(ptr) {}

    std::shared_ptr<void> GetSharedPtr() const
    {
        return ptr_;
    }

    operator void*() const
    {
        return ptr_.get();
    }

private:
    std::shared_ptr<void> ptr_;
};

namespace OHOS::AbilityRuntime {
class Context;
}

namespace OHOS::Ace::Ani {
class DragAction;
class AniGlobalReference;
}
enum class ArkUIDragStatus { STARTED, ENDED };
enum class ArkUIDragResult { DRAG_SUCCESS, DRAG_FAIL, DRAG_CANCEL };
enum class ArkUIDragBehavior { UNKNOWN, COPY, MOVE };
enum ArkUISnapshotRegionMode {
    COMMON,
    LOCALIZED,
    NO_REGION
};
enum class ArkUIAniRouteType { NONE, PUSH, POP };
enum class ArkUIAniSlideEffect { NONE, LEFT, RIGHT, TOP, BOTTOM, START, END };

enum class ArkUIPreviewType {
    FOREGROUND_COLOR = 0,
    OPACITY = 1,
    RADIUS = 2,
    SCALE = 3
};

typedef struct ArkUIAniNumberString {
    int32_t selector = -1;
    union {
        double value0;
        const char* value1;
    };
} ArkUIAniNumberString;

struct ArkUIDragInfo {
    void* pixelMap;
    bool onlyForLifting = false;
    bool delayCreating = false;
};

struct ArkUINavigationInfo {
    std::string navigationId;
    ani_ref navPathStack;
};

struct ArkUINavDestinationInfo {
    ani_int uniqueId;
    ani_int index;
    std::string name;
    std::string navDestinationId;
    std::string navigationId;
    ani_size state;
    ani_size mode;
};

struct ArkUIRouterPageInfo {
    int32_t index;
    std::string name;
    std::string path;
    ani_size state;
    std::string pageId;
};

struct AniOverlayOptions {
    int32_t alignment = 0;
    float x = 0.0f;
    float y = 0.0f;
};

struct ArkUIDragNotifyMessage {
    ArkUIDragResult result;
    ArkUIDragBehavior dragBehavior;
};

struct ArkUIDragPreviewOption {
    bool isScaleEnabled = true;
    bool defaultAnimationBeforeLifting = false;
    bool isMultiSelectionEnabled = false;
    bool isNumber = false;
    bool isDefaultShadowEnabled = false;
    bool isDefaultRadiusEnabled = false;
    bool isDragPreviewEnabled = true;
    bool isDefaultDragItemGrayEffectEnabled = false;
    bool enableEdgeAutoScroll = true;
    bool enableHapticFeedback = false;
    bool isMultiTiled = false;
    bool isLiftingDisabled = false;
    bool isTouchPointCalculationBasedOnFinalPreviewEnable = false;
    int32_t sizeChangeEffect = 0;
    union {
        ArkUI_Int32 badgeNumber;
        bool isShowBadge = true;
    };
    std::function<void(void* ptr)> modifier;
    void ResetDragPreviewMode()
    {
        isScaleEnabled = true;
        isDefaultShadowEnabled = false;
        isDefaultRadiusEnabled = false;
        isDefaultDragItemGrayEffectEnabled = false;
        isMultiTiled = false;
    }
};

struct ArkUIDragPointerEvent {
    ArkUI_Int32 pointerEventId = 0;
    ArkUI_Int32 pointerId = 0;
    ArkUI_Int32 windowX = 0;
    ArkUI_Int32 windowY = 0;
    ArkUI_Int32 displayX = 0;
    ArkUI_Int32 displayY = 0;
    ArkUI_Int32 deviceId = 0;
    ArkUI_Int32 displayId = 0;
    ArkUI_Int32 sourceType = 0;
    ArkUI_Int32 originId = 0;
};

struct ArkUIDragControllerAsync {
    ani_env* env = nullptr;
    bool isArray = false;
    std::string extraParams;
    bool hasHandle = false;
    SharedPointerWrapper touchPoint;
    SharedPointerWrapper unifiedData;
    SharedPointerWrapper pixelMap;
    std::vector<SharedPointerWrapper> pixelMapList;
    ArkUINodeHandle customBuilderNode = nullptr;
    std::vector<ArkUINodeHandle> customBuilderNodeList;
    ani_fn_object asyncCallback = nullptr;
    ani_resolver deferred = nullptr;
    ArkUIDragPointerEvent dragPointerEvent;
    ArkUIDragPreviewOption dragPreviewOption;
    std::function<void(std::shared_ptr<ArkUIDragControllerAsync>, const ArkUIDragNotifyMessage&,
        const ArkUIDragStatus)> callBackJsFunction;
    std::shared_ptr<OHOS::Ace::Ani::DragAction> dragAction = nullptr;
};

struct ArkUIPreviewStyle {
    std::vector<ArkUIPreviewType> types;
    uint32_t foregroundColor = 0;
    int32_t opacity = -1;
    int32_t radius = -1;
    float scale = -1;
};

struct ArkUIPreviewAnimation {
    int32_t duration { -1 };
    std::string curveName;
    std::vector<float> curve;
};

struct ArkUIDragPreviewAsync {
    ArkUIPreviewStyle previewStyle;
    ArkUIPreviewAnimation previewAnimation;
    bool hasAnimation = false;
};

struct ArkUILocalizedSnapshotRegion {
    double start = -1.f;
    double top = -1.f;
    double end = -1.f;
    double bottom = -1.f;
};

struct ArkUIComponentSnapshotOptions {
    float scale = DEFAULT_SNAPSHOT_SCALE;
    bool waitUntilRenderFinished = false;
    ArkUILocalizedSnapshotRegion snapshotRegion;
    ArkUISnapshotRegionMode regionMode = ArkUISnapshotRegionMode::NO_REGION;
};

struct ArkUISnapshotParam {
    int32_t delay = DEFAULT_DELAY_TIME;
    bool checkImageStatus = false;
    ArkUIComponentSnapshotOptions options;
};

struct ArkUIComponentSnapshotAsync {
    int32_t errCode = -1;
    ani_env* env = nullptr;
    ani_resolver deferred = nullptr;
    ani_object callbackRef = nullptr;
    ani_object destroyCallbackRef = nullptr;
    std::shared_ptr<void> pixelMap;
    std::function<void(std::shared_ptr<ArkUIComponentSnapshotAsync>)> callBackJsFunction;
};

typedef struct ArkUIAniTranslateOptions {
    ArkUIAniNumberString x;
    ArkUIAniNumberString y;
    ArkUIAniNumberString z;
} ArkUIAniTranslateOptions;

typedef struct ArkUIAniScaleOptions {
    double x = 1.0;
    double y = 1.0;
    double z = 1.0;
    ArkUIAniNumberString centerX;
    ArkUIAniNumberString centerY;
} ArkUIAniScaleOptions;

typedef struct ArkUIAniAnimatableArithmeticObject {
    ani_env* env = nullptr;
    ani_object property = nullptr;
} ArkUIAniAnimatableArithmeticObject;

typedef struct ArkUIAniAnimatableArithmeticFuncs {
    ArkUIAniArithmeticAddFunction addFunc;
    ArkUIAniArithmeticMinusFunction minusFunc;
    ArkUIAniArithmeticMultiplyFunction multiplyFunc;
    ArkUIAniArithmeticEqualFunction equalFunc;
    ArkUIAniCreateObjectFunction createFunc;
    ArkUIAniDeleteObjectFunction deleteFunc;
} ArkUIAniAnimatableArithmeticFuncs;

typedef struct ArkUIAniUnionCurveStringICurve {
    int32_t selector = -1;
    union {
        ArkUIAniCurve value0;
        ArkUIAniString value1;
        ArkUIAniICurve value2;
    };
} ArkUIAniUnionCurveStringICurve;

typedef struct ArkUIAniPageTransitionOption {
    ArkUIAniRouteType routeType = ArkUIAniRouteType::NONE;
    int32_t duration = 0;
    int32_t delay = 0;
    ArkUIAniUnionCurveStringICurve curve;
} ArkUIAniPageTransitionOption;

struct ArkUIXComponentParams {
    std::function<void(const std::string&)> onSurfaceCreated = nullptr;
    std::function<void(const std::string&, float, float, float, float)> onSurfaceChanged = nullptr;
    std::function<void(const std::string&)> onSurfaceDestroyed = nullptr;
};

struct ArkUIAniImageModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setDrawableDescriptor)(ArkUINodeHandle node, void* drawablem);
    void (*setResizableLattice)(ArkUINodeHandle node, void* lattice);
    void (*setDrawingColorFilter)(ArkUINodeHandle node, void* colorFilter);
    void* (*getPixelMapPeer)(void* pixelMap);
    ani_long (*createColorFilterPeer)(ani_long colorFilter);
    ani_long (*getColorFilter)(ani_long colorFilterPeer);
    void* (*getDrawingColorFilterPeer)(void* colorFilter);
    void* (*getDrawingLatticePeer)(void* latticePeer);
};

struct ArkUIWaterFlowSectionGap {
    int32_t unit = 1;
    float value = 0.0f;
};

struct ArkUIWaterFlowSectionPadding {
    ArkUIWaterFlowSectionGap top;
    ArkUIWaterFlowSectionGap right;
    ArkUIWaterFlowSectionGap bottom;
    ArkUIWaterFlowSectionGap left;
};

struct ArkUIWaterFlowSection {
    int32_t itemsCount = 0;
    int32_t crossCount = 1;
    ArkUIWaterFlowSectionGap columnsGap;
    ArkUIWaterFlowSectionGap rowsGap;
    ArkUIWaterFlowSectionPadding margin;
    std::function<float(int32_t)> onGetItemMainSizeByIndex;
};
struct ArkUIAniWebModifier {
    void (*setJavaScriptProxyController)(void* node, std::function<void()>&& callback);
    bool (*transferScreenCaptureHandlerToStatic)(void* peer, void* nativePtr);
    bool (*transferJsGeolocationToStatic)(void* peer, void* nativePtr);
    bool (*transferJsResultToStatic)(void* peer, void* nativePtr);
    bool (*transferEventResultToStatic)(void* peer, void* nativePtr);
    bool (*transferFileSelectorResultToStatic)(void* peer, void* nativePtr);
    bool (*transferFileSelectorParamToStatic)(void* peer, void* nativePtr);
    bool (*transferWebContextMenuResultToStatic)(void* peer, void* nativePtr);
    bool (*transferWebContextMenuParamToStatic)(void* peer, void* nativePtr);
    bool (*transferHttpAuthHandlerToStatic)(void* peer, void* nativePtr);
    bool (*transferWebResourceReponseToStatic)(void* peer, void* nativePtr);
    bool (*transferWebResourceRequestToStatic)(void* peer, void* nativePtr);
    bool (*transferConsoleMessageToStatic)(void* peer, void* nativePtr);
    bool (*transferDataResubmissionHandlerToStatic)(void* peer, void* nativePtr);
    bool (*transferClientAuthenticationHandlerToStatic)(void* peer, void* nativePtr);
    bool (*transferSslErrorHandlerToStatic)(void* peer, void* nativePtr);
    bool (*transferPermissionRequestToStatic)(void* peer, void* nativePtr);
    bool (*transferControllerHandlerToStatic)(void* peer, void* nativePtr);
    bool (*transferWebKeyboardControllerToStatic)(void* peer, void* nativePtr);
    napi_value (*transferScreenCaptureHandlerToDynamic)(napi_env env, void* peer);
    napi_value (*transferJsGeolocationToDynamic)(napi_env env, void* peer);
    napi_value (*transferJsResultToDynamic)(napi_env env, void* peer);
    napi_value (*transferEventResultToDynamic)(napi_env env, void* peer);
    napi_value (*transferFileSelectorResultToDynamic)(napi_env env, void* peer);
    napi_value (*transferFileSelectorParamToDynamic)(napi_env env, void* peer);
    napi_value (*transferWebContextMenuResultToDynamic)(napi_env env, void* peer);
    napi_value (*transferWebContextMenuParamToDynamic)(napi_env env, void* peer);
    napi_value (*transferHttpAuthHandlerToDynamic)(napi_env env, void* peer);
    napi_value (*transferWebResourceReponseToDynamic)(napi_env env, void* peer);
    napi_value (*transferWebResourceRequestToDynamic)(napi_env env, void* peer);
    napi_value (*transferConsoleMessageToDynamic)(napi_env env, void* peer);
    napi_value (*transferDataResubmissionHandlerToDynamic)(napi_env env, void* peer);
    napi_value (*transferClientAuthenticationHandlerToDynamic)(napi_env env, void* peer);
    napi_value (*transferSslErrorHandlerToDynamic)(napi_env env, void* peer);
    napi_value (*transferControllerHandlerToDynamic)(napi_env env, void* peer);
    napi_value (*transferPermissionRequestToDynamic)(napi_env env, void* peer);
    napi_value (*transferWebKeyboardControllerToDynamic)(napi_env env, void* peer);
};
struct ArkUIAniDragModifier {
    void (*setDragData)(ani_ref event, ani_ref data);
    ani_ref (*getDragData)(ani_ref event);
    void (*getDragSummary)(ani_ref event, ani_ref summaryPtr);
    void (*setDragDropInfoPixelMap)(ani_ref event, ani_ref pixelMap);
    void (*setDragDropInfoCustomNode)(ani_ref event, ArkUINodeHandle node);
    void (*setDragDropInfoExtraInfo)(ani_ref event, const char* ptr);
    void (*setDragAllowDropNull)(ArkUINodeHandle node);
    void (*setDragAllowDrop)(ArkUINodeHandle node, char** allowDrops, ArkUI_Int32 length);
    void (*setDragPreview)(ArkUINodeHandle node, ArkUIDragInfo dragInfo);
    void (*setDragPreviewOptions)(ArkUINodeHandle node, ArkUIDragPreviewOption options);
    const char* (*getUdKey)(ani_ref event);
    ani_long (*createUnifiedDataPeer)(void* data);
    ani_long (*getUnifiedData)(ani_long peer);
};
struct ArkUIAniXBarModifier {
    void (*setComponentCreateFunc)(std::function<int64_t(const int32_t&, const int32_t&)>&& fn);
    void (*setOnWindowFocusedFunc)(int64_t ptr, std::function<void()>&& fn);
    void (*setOnWindowUnFocusedFunc)(int64_t ptr, std::function<void()>&& fn);
    void (*setSetAppTitleFunc)(int64_t ptr, std::function<void(const std::string&)>&& fn);
    void (*setSetAppIconFunc)(int64_t ptr, std::function<void(void*)>&& fn);
    void (*setSetCustomCallbackFunc)(int64_t ptr, std::function<void(const std::string&, const std::string&)>&& fn);
    void (*callNative)(const int32_t& xBarType, const std::string callType, const std::string message);
};
struct ArkUIAniParallelizeUIModifier {
    ani_long (*constructAdapterNode)(ani_int);
    void (*reset)(ArkUINodeHandle);
    void (*registerCallback)(
        ArkUINodeHandle, std::function<int32_t()>&&, std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>&&);
};
struct ArkUIAniCommonModifier {
    ani_ref* (*getHostContext)(ArkUI_Int32 key);
    void (*setFrameRateRange)(ani_env* env, ani_long peerPtr, ani_object value, ArkUI_Int32 type);
    void (*syncInstanceId)(ArkUI_Int32 id);
    void (*restoreInstanceId)();
    void (*setDrawCallback)(ani_env* env, ani_long ptr, void* fnDrawCallbackFun);
    void (*setFrameNodeDrawCallback)(ani_env* env, ani_long ptr, void* fnDrawCallbackFun);
    ArkUI_Int32 (*getCurrentInstanceId)();
    ArkUI_Int32 (*getFocusedInstanceId)();
    ani_long (*builderProxyNodeConstruct)(ArkUI_Int32 id);
    ani_ref (*getSharedLocalStorage)();
    void (*setBackgroundImagePixelMap)(ani_env* env, ArkUINodeHandle node, ani_ref pixelMapPtr, ArkUI_Int32 repeat);
    void (*setCustomCallback)(ani_long ptr, void* fnMeasure, void* fnLayout);
    ArkUI_Int32 (*requireArkoalaNodeId)(ArkUI_Int32 capacity);
    ani_long (*getNodePtrWithPeerPtr)(ani_long ptr);
    ani_int (*getNodeIdWithNodePtr)(ani_long ptr);
    ani_int (*getNodeIdWithPeerPtr)(ani_long ptr);
    ani_long (*createRenderNodePeerWithNodePtr)(ani_long ptr);
    ani_int (*createWindowFreeContainer)(ani_env *env, std::shared_ptr<OHOS::AbilityRuntime::Context> context);
    void (*destroyWindowFreeContainer)(ani_int id);
    ani_boolean (*checkIsUIThread)(ArkUI_Int32 id);
    ani_boolean (*isDebugMode)(ArkUI_Int32 id);
    void (*onMeasureInnerMeasure)(ani_long ptr);
    void (*onLayoutInnerLayout)(ani_long ptr);
    void (*setParallelScoped)(ani_boolean parallel);
    void (*setCustomPropertyCallBack)(
        ArkUINodeHandle node, std::function<void()>&& func,
        std::function<std::string(const std::string&)>&& getFunc,
        std::function<std::string()>&& getAllCustomPropertiesFunc);
    std::optional<std::string> (*getCustomProperty)(ani_env* env, ArkUINodeHandle node, const std::string& key);
    void (*setOverlayComponent)(ani_long node, ani_long builderPtr, AniOverlayOptions options);
    ani_double (*vp2px)(ani_double value, ani_int instanceId);
    ani_double (*px2vp)(ani_double value, ani_int instanceId);
    ani_double (*fp2px)(ani_double value, ani_int instanceId);
    ani_double (*px2fp)(ani_double value, ani_int instanceId);
    ani_double (*lpx2px)(ani_double value, ani_int instanceId);
    ani_double (*px2lpx)(ani_double value, ani_int instanceId);
    std::optional<std::string> (*getWindowName)(ani_int instanceId);
    std::optional<std::uint32_t> (*getWindowId)(ani_int instanceId);
    ani_int (*getWindowWidthBreakpoint)();
    ani_int (*getWindowHeightBreakpoint)();
    void* (*transferKeyEventPointer)(ani_long nativePtr);
    void* (*createKeyEventAccessorWithPointer)(ani_long nativePtr);
    void* (*createEventTargetInfoAccessor)();
    void (*eventTargetInfoAccessorWithId)(ani_env* env, ani_long input, const std::string& id);
    void* (*createScrollableTargetInfoAccessor)();
    void (*scrollableTargetInfoAccessorWithId)(ani_env* env, ani_long input, const std::string& id);
    void (*scrollableTargetInfoAccessorWithPointer)(ani_long input, ani_long nativePtr);
    void* (*transferScrollableTargetInfoPointer)(ani_long nativePtr);
    void* (*createDragEventAccessor)(ani_long ptr);
    void* (*getDragEventPointer)(ani_long ptr);
    void* (*transferTouchEventPointer)(ani_long nativePtr);
    void* (*transferMouseEventPointer)(ani_long nativePtr);
    void* (*transferAxisEventPointer)(ani_long nativePtr);
    void* (*transferClickEventPointer)(ani_long nativePtr);
    void* (*transferHoverEventPointer)(ani_long nativePtr);
    void* (*getTouchEventPointer)(ani_long peer);
    void* (*getMouseEventPointer)(ani_long peer);
    void* (*getAxisEventPointer)(ani_long peer);
    void* (*getClickEventPointer)(ani_long peer);
    void* (*getHoverEventPointer)(ani_long peer);
    void (*frameNodeMarkDirtyNode)(ani_env* env, ani_long ptr);
    ArkUI_Uint32 (*getColorValueByString)(const std::string& src);
    ArkUI_Uint32 (*getColorValueByNumber)(ArkUI_Uint32 src);
    void (*sendThemeToNative)(ani_env* env, const std::vector<Ark_ResourceColor>& colors, ani_int id);
    void (*setDefaultTheme)(ani_env* env, const std::vector<Ark_ResourceColor>& colors, ani_boolean isDark);
    void (*removeThemeInNative)(ani_env* env, ani_int withThemeId);
    void (*updateColorMode)(ani_int colorMode);
    void (*restoreColorMode)();
    void (*setThemeScopeId)(ani_env* env, ani_int themeScopeId);
    void (*createAndBindTheme)(ani_env* env, ani_int themeScopeId, ani_int themeId,
        const std::vector<Ark_ResourceColor>& colors, ani_int colorMode, void* func);
    void (*applyParentThemeScopeId)(ani_env* env, ani_long self, ani_long parent);
    float (*getPx2VpWithCurrentDensity)(float px);
    void (*setImageCacheCount)(ani_int value, ani_int instanceId);
    void (*setImageRawDataCacheSize)(ani_int value, ani_int instanceId);
    void (*applyThemeScopeId)(ani_env* env, ani_long ptr, ani_int themeScopeId);
};
struct  ArkUICustomNodeInfo {
    std::function<void()> onPageShowFunc;
    std::function<void()> onPageHideFunc;
    std::function<bool()> onBackPressedFunc;
    std::function<void()> pageTransitionFunc;
    std::function<void()> onCleanupFunc;
    std::function<std::string()> onDumpInspectorFunc;
    std::function<void(bool, bool)> setActiveFunc;
};
struct ArkUIAniCustomNodeModifier {
    ani_long (*constructCustomNode)(ani_int id, ArkUICustomNodeInfo&& customNodeInfo);
    void (*requestFrame)();
    void (*queryNavigationInfo)(ani_long node, ArkUINavigationInfo& info);
    void (*queryNavDestinationInfo)(ani_long node, ArkUINavDestinationInfo& info);
    void (*queryNavDestinationInfo0)(ani_long node, ArkUINavDestinationInfo& info, ani_int isInner);
    void (*queryRouterPageInfo)(ani_long node, ArkUIRouterPageInfo& info);
    bool (*queryNavDestinationInfo1)(ArkUI_Int32 uniqueId, ArkUINavDestinationInfo& info);
    bool (*queryRouterPageInfo1)(ArkUI_Int32 uniqueId, ArkUIRouterPageInfo& info);
    void (*onReuse)(ani_long node);
    void (*onRecycle)(ani_long node);
};
struct ArkUIAniKeyboardAvoidModeModifier {
    ArkUI_Int32 (*getKeyboardAvoidMode)();
    void (*setKeyboardAvoidMode)(int32_t index);
};
struct ArkUIAniDrawModifier {
    void (*setDrawModifier)(ani_long ptr, uint32_t flag, void* fnDrawBehindFun, void* fnDrawContentFun,
        void* fnDrawFrontFun, void* fnDrawForegroundFun, void* fnDrawOverlayFun);
    void (*invalidate)(ani_env* env, ani_long ptr);
};
struct ArkUIAniContentSlotModifier {
    ArkUIContentSlot (*construct)(ArkUI_Int32 id);
    void (*setContentSlotOptions)(ArkUIContentSlot node, ArkUINodeContent value);
};
struct ArkUIAniLazyForEachNodeModifier {
    ani_long (*constructLazyForEachNode)(ani_int, ani_boolean);
};
struct ArkUIAniWaterFlowModifier {
    void (*setWaterFlowSection)(
        ArkUINodeHandle node, int32_t start, int32_t deleteCount, void* section, ArkUI_Int32 size);
    void (*setWaterFlowFooterContent)(ArkUINodeHandle node, ArkUINodeHandle footerPtr);
    void (*setWaterFlowFooter)(ArkUINodeHandle node, ArkUINodeHandle footerPtr);
    void (*resetWaterFlowFooter)(ArkUINodeHandle node);
    void (*setWaterFlowScroller)(ArkUINodeHandle node, void* scroller);
    void (*setWaterFlowLayoutMode)(ArkUINodeHandle node, int32_t mode);
};
struct ArkUIAniListModifier {
    bool (*updateDefaultSizeAndGetNeedSync)(ArkUINodeHandle node, double defaultSize);
    void (*syncChildrenSize)(ArkUINodeHandle node, double size);
    void (*notifyChange)(ArkUINodeHandle node, ArkUI_Int32 start,
        ArkUI_Int32 deleteCount, std::vector<float>& newSizeArr);
    void (*resizeChildrenSize)(ArkUINodeHandle node, int32_t size);
    void (*syncChildrenSizeOver)(ArkUINodeHandle node);
    void (*resetListChildrenMainSize)(ArkUINodeHandle node);
};
struct ArkUIAniComponentSnapshotModifier {
    void (*createFromBuilder)(
        ArkUINodeHandle node, const ArkUIComponentSnapshotAsync& asyncCtx, const ArkUISnapshotParam& param);
    void (*createFromComponent)(
        ArkUINodeHandle node, const ArkUIComponentSnapshotAsync& asyncCtx, const ArkUISnapshotParam& param);
};
struct ArkUIAniAnimationModifier {
    bool (*hasAnimatableProperty)(ArkUINodeHandle node, const char* name);
    void (*updateAnimatableFloat)(ArkUINodeHandle node, const char* propertyName, float property);
    void (*createAnimatableFloat)(ArkUINodeHandle node, const char* propertyName, float property, void* callback);
    void (*updateAnimatableArithmetic)(
        ArkUINodeHandle node, const char* propertyName, ArkUIAniAnimatableArithmeticObject property);
    void (*createAnimatableArithmetic)(
        ArkUINodeHandle node, const char* propertyName, ArkUIAniAnimatableArithmeticObject property, void* callback);
    void (*initAnimatableArithmeticClass)(const ArkUIAniAnimatableArithmeticFuncs* funcs);
    void (*createPageTransitionEnter)(const ArkUIAniPageTransitionOption* options);
    void (*pageTransitionSetOnEnter)(void* callback);
    void (*createPageTransitionExit)(const ArkUIAniPageTransitionOption* options);
    void (*pageTransitionSetOnExit)(void* callback);
    void (*pageTransitionSetSlide)(ArkUIAniSlideEffect slide);
    void (*pageTransitionSetTranslate)(const ArkUIAniTranslateOptions* options);
    void (*pageTransitionSetScale)(const ArkUIAniScaleOptions* options);
    void (*pageTransitionSetOpacity)(float opacity);
};
struct ArkUIAniInteropModifier {
    ani_long (*createViewStackProcessor)();
    ani_long (*popViewStackProcessor)();
    void (*deleteViewStackProcessor)(ani_long ptr);
};
struct ArkUIAniDragControllerModifier {
    bool (*aniHandleExecuteDrag)(ArkUIDragControllerAsync& asyncCtx, std::string &errMsg);
    bool (*aniHandleDragAction)(ArkUIDragControllerAsync& asyncCtx, std::string &errMsg);
    bool (*aniHandleDragActionStartDrag)(ArkUIDragControllerAsync& asyncCtx);
    void* (*createDragEventPeer)(const ArkUIDragNotifyMessage& dragNotifyMsg);
    void (*aniDragPreviewSetForegroundColor)(Ark_ResourceColor value, ArkUIDragPreviewAsync& asyncCtx);
    void (*aniDragPreviewAnimate)(ArkUIDragPreviewAsync& asyncCtx);
    void (*aniDragActionSetDragEventStrictReportingEnabled)(bool enable);
    void (*aniDragActionCancelDataLoading)(const char* key);
    void (*aniDragActionNotifyDragStartReques)(int requestStatus);
};
struct ArkUIAniImageSpanModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setAltPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setDrawingColorFilter)(ArkUINodeHandle node, void* colorFilter);
};
struct ArkUIAniTextBasedModifier {
    void* (*fromSymbolModifierPeer)(void* ptr);
    void* (*toSymbolModifierPeer)(std::function<void(OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>)>& symbolApply,
        void* symbolModifierAni);
    void* (*fromTextModifierPeer)(void* ptr);
    void* (*toTextModifierPeer)(std::function<void(OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode>)>& textApply,
        void* textModifierAni);
};
struct ArkUIAniStyledStringModifier {
    void (*setPixelMap)(ArkUIStyledString peer, void* nativePixelMap);
    void* (*getPixelMap)(ArkUIStyledString peer);
};
struct ArkUIAniVideoModifier {
    void (*setOnError)(ArkUINodeHandle node, std::function<void(const std::string&)>&& onError);
    void (*parseVideoError)(const std::string& jsonStr, int32_t& code, std::string& message);
};
struct ArkUIAniShapeModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelMap);
};
struct ArkUIAniRichEditorModifier {
    ani_long (*transferPixelMap)(void* pixelMap);
};
struct ArkUIAniStateMgmtModifier {
    std::string (*persistentStorageGet)(const std::string& key, const int32_t areaMode);
    void (*persistentStorageSet)(const std::string& key, const std::string& value, const int32_t areaMode);
    bool (*persistentStorageHas)(const std::string& key, const int32_t areaMode);
    void (*persistentStorageDelete)(const std::string& key, const int32_t areaMode);
    void (*persistentStorageClear)();
    int32_t (*getColorMode)();
    float (*getFontWeightScale)();
    float (*getFontScale)();
    bool (*getAccessibilityEnabled)();
    std::string (*getLayoutDirection)();
    std::string (*getLanguageCode)();
};
struct ArkUIAniXComponentModifier {
    void (*setXComponentControllerCallback)(void* peer, const ArkUIXComponentParams& params);
    void (*setScreenId)(ArkUINodeHandle node, uint64_t screenId);
    void (*markBindNative)(ArkUINodeHandle node);
};

struct ArkUIAniConditionScopeModifier {
    ani_long (*constructConditionScope)(ani_int);
    void (*markDirty)(ani_long);
};

struct ArkUIAniComponentConentModifier {
    void (*removeComponentFromFrameNode)(ani_long node, ani_long content);
    void (*addComponentToFrameNode)(ani_long node, ani_long content);
};
struct ArkUIAniCanvasModifier {
    void (*setPixelMap)(ArkUICanvasRenderer peer, void* nativePixelMap);
    void* (*getPixelMap)(ArkUICanvasRenderer peer, ani_double sx, ani_double sy, ani_double sw, ani_double sh);
    void (*drawPixelMap0)(ArkUICanvasRenderer peer, void* nativePixelMap, ani_double dx, ani_double dy);
    void (*drawPixelMap1)(
        ArkUICanvasRenderer peer, void* nativePixelMap, ani_double dx, ani_double dy, ani_double dw, ani_double dh);
    void (*drawPixelMap2)(ArkUICanvasRenderer peer, void* nativePixelMap, ani_double sx, ani_double sy, ani_double sw,
        ani_double sh, ani_double dx, ani_double dy, ani_double dw, ani_double dh);
    ArkUIImageBitmap (*imageBitmapConstruct)(const std::string& str, void* pixelMapPtr, ArkUI_Int32 unit);
    ani_double (*getCanvasDensity)(ArkUICanvasRenderer peer);
    ani_double (*getSystemDensity)();
    void (*getImageData)(
        ArkUICanvasRenderer peer, uint8_t* buffer, ani_double sx, ani_double sy, ani_double sw, ani_double sh);
    void (*putImageData0)(ArkUICanvasRenderer peer, uint8_t* data, ani_size length, ani_double dx, ani_double dy,
        ani_int width, ani_int height);
    void (*putImageData1)(ArkUICanvasRenderer peer, uint8_t* data, ani_size length, ani_double dx, ani_double dy,
        ani_int width, ani_int height, ani_double dirtyX, ani_double dirtyY, ani_double dirtyWidth,
        ani_double dirtyHeight);
    void* (*getDrawingCanvas)(ArkUIDrawingRenderingContext peer);
    ani_int (*getCanvasId)(ArkUICanvasRenderingContext peer);
    void (*setAttachCallbackId)(ArkUICanvasRenderingContext peer, ani_int attachCallbackId);
    void (*setDetachCallbackId)(ArkUICanvasRenderingContext peer, ani_int detachCallbackId);
};

struct ArkUIAniTraceModifier {
    bool (*getAttributeSetTraceEnabled)();
    void (*traceBegin)(const std::string& traceName);
    void (*traceEnd)();
    void (*asyncTraceBegin)(const std::string& traceName, int taskId);
    void (*asyncTraceEnd)(const std::string& traceName, int taskId);
};

struct ArkUIAniUINodeOnUpdateDoneAniModifier {
    void (*onUpdateDone)(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node);
    void (*setUINodeIsStatic)(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long node);
};

struct ArkUIAniNodeAdapterModifier {
    ani_long (*nodeAdapterConstruct)(NodeAdapterInfo&& info);
    void (*nodeAdapterDetachNodeAdapter)(ani_long node);
    ani_boolean (*nodeAdapterAttachNodeAdapter)(ani_long ptr, ani_long node);
    void (*nodeAdapterDispose)(ani_long node);
    void (*nodeAdapterNotifyItemReloaded)(ani_long node);
    void (*nodeAdapterSetTotalNodeCount)(ani_long node, ani_double count);
    void (*nodeAdapterNotifyItemChanged)(ani_long node, ani_double start, ani_double count);
    void (*nodeAdapterNotifyItemRemoved)(ani_long node, ani_double start, ani_double count);
    void (*nodeAdapterNotifyItemInserted)(ani_long node, ani_double start, ani_double count);
    void (*nodeAdapterNotifyItemMoved)(ani_long node, ani_double from, ani_double to);
    AniDoubleArray (*nodeAdapterGetAllItems)(ani_long node);
};
struct ArkUIAniSyntaxItemModifier {
    ani_long (*constructSyntaxItem)(ani_int);
};
struct ArkUIAniForEachNodeModifier {
    ani_long (*construct)(ani_int, ani_boolean);
    void (*finishRender)(ani_long);
};

struct ArkUIAniComponent3DModifier {
    void (*setScene)(ArkUINodeHandle node, void* scene, int32_t modelType);
    void (*setWidget)(ArkUINodeHandle node, const std::string& scenePath, int32_t modelType);
};

struct ArkUIAniCommonNodeAniModifier {
    ani_long (*construct)(ani_int id, ani_int flags);
    void (*setCommonOptions)(ani_long node);
};

struct ArkUIAniModifiers {
    ArkUI_Int32 version;
    const ArkUIAniImageModifier* (*getImageAniModifier)();
    const ArkUIAniWebModifier* (*getWebAniModifier)();
    const ArkUIAniDragModifier* (*getDragAniModifier) ();
    const ArkUIAniCommonModifier* (*getCommonAniModifier)();
    const ArkUIAniCustomNodeModifier* (*getCustomNodeAniModifier)();
    const ArkUIAniKeyboardAvoidModeModifier* (*getKeyboardAvoidModeAniModifier)();
    const ArkUIAniLazyForEachNodeModifier* (*getLazyForEachNodeAniModifier)();
    const ArkUIAniContentSlotModifier* (*getContentSlotAniModifier)();
    const ArkUIAniDrawModifier* (*getArkUIAniDrawModifier)();
    const ArkUIAniWaterFlowModifier* (*getArkUIAniWaterFlowModifier)();
    const ArkUIAniListModifier* (*getArkUIAniListModifier)();
    const ArkUIAniComponentSnapshotModifier* (*getComponentSnapshotAniModifier)();
    const ArkUIAniAnimationModifier* (*getAnimationAniModifier)();
    const ArkUIAniInteropModifier* (*getInteropAniModifier)();
    const ArkUIAniDragControllerModifier* (*getDragControllerAniModifier)();
    const ArkUIAniStyledStringModifier* (*getStyledStringAniModifier)();
    const ArkUIAniTextBasedModifier* (*getTextBasedAniModifier)();
    const ArkUIAniImageSpanModifier* (*getImageSpanAniModifier)();
    const ArkUIAniVideoModifier* (*getArkUIAniVideoModifier)();
    const ArkUIAniShapeModifier* (*getArkUIAniShapeModifier)();
    const ArkUIAniRichEditorModifier* (*getRichEditorAniModifier)();
    const ArkUIAniStateMgmtModifier* (*getStateMgmtAniModifier)();
    const ArkUIAniXComponentModifier* (*getArkUIAniXComponentModifier)();
    const ArkUIAniConditionScopeModifier* (*getArkUIAniConditionScopeModifier)();
    const ArkUIAniComponentConentModifier* (*getArkUIAniComponentConentModifier)();
    const ArkUIAniCanvasModifier* (*getCanvasAniModifier)();
    const ArkUIAniTraceModifier* (*getTraceAniModifier)();
    const ArkUIAniUINodeOnUpdateDoneAniModifier* (*getUINodeOnUpdateDoneAniModifier)();
    const ArkUIAniNodeAdapterModifier* (*getNodeAdapterAniModifier)();
    const ArkUIAniSyntaxItemModifier* (*getSyntaxItemAniModifier)();
    const ArkUIAniForEachNodeModifier* (*getForEachNodeAniModifier)();
    const ArkUIAniComponent3DModifier* (*getComponent3DModifier)();
    const ArkUIAniXBarModifier* (*getXBarAniModifier)();
    const ArkUIAniCommonNodeAniModifier* (*getCommonNodeAniModifier)();
    const ArkUIAniParallelizeUIModifier* (*getParallelizeUIModifier)();
};

__attribute__((visibility("default"))) const ArkUIAniModifiers* GetArkUIAniModifiers(void);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H
