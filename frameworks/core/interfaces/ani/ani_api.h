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
typedef _ArkUINode* ArkUINodeHandle;
typedef int ArkUI_Int32;
typedef size_t ani_size;
typedef _ArkUIContentSlot* ArkUIContentSlot;
typedef _ArkUINodeContent* ArkUINodeContent;
typedef _ArkUIStyledString* ArkUIStyledString;
typedef _ArkUICanvasRenderer* ArkUICanvasRenderer;
typedef _ArkUIImageData* ArkUIImageData;
typedef _ArkUIImageBitmap* ArkUIImageBitmap;
typedef struct WebviewControllerInfo {
    std::function<int32_t()> getWebIdFunc = nullptr;
    std::function<void(int32_t)> completeWindowNewFunc = nullptr;
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    std::function<void(int32_t)> setWebIdFunc = nullptr;
    std::function<void(const std::string&)> setHapPathFunc = nullptr;
} WebviewControllerInfo;

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

namespace OHOS::Ace::Ani {
class DragAction;
}
enum class ArkUIDragStatus { STARTED, ENDED };
enum class ArkUIDragResult { DRAG_SUCCESS, DRAG_FAIL, DRAG_CANCEL };
enum class ArkUIDragBehavior { UNKNOWN, COPY, MOVE };
enum ArkUISnapshotRegionMode {
    COMMON,
    LOCALIZED,
    NO_REGION
};

struct ArkUIDragInfo {
    void* pixelMap;
    bool onlyForLifting = false;
    bool delayCreating = false;
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
    bool isNumber = false;
    bool isDefaultShadowEnabled = false;
    bool isDefaultRadiusEnabled = false;
    union {
        ArkUI_Int32 badgeNumber;
        bool isShowBadge = true;
    };
    void ResetDragPreviewMode()
    {
        isScaleEnabled = true;
        isDefaultShadowEnabled = false;
        isDefaultRadiusEnabled = false;
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
    const char* extraParams;
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
    OHOS::Ace::Ani::DragAction* dragAction = nullptr;
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

struct ArkUIAniImageModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setDrawableDescriptor)(ArkUINodeHandle node, void* drawablem, int type);
    void (*setResizableLattice)(ArkUINodeHandle node, void* lattice);
    void (*setDrawingColorFilter)(ArkUINodeHandle node, void* colorFilter);
};
struct ArkUIAniWebModifier {
    void (*setWebOptions)(ArkUINodeHandle node, const WebviewControllerInfo& controllerInfo);
    void (*setWebControllerControllerHandler)(void* controllerHandler, const WebviewControllerInfo& controllerInfo);
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
    void (*setDragAllowDrop)(ArkUINodeHandle node, const char** allowDrops, ArkUI_Int32 length);
    void (*setDragPreview)(ArkUINodeHandle node, ArkUIDragInfo dragInfo);
    const char* (*getUdKey)(ani_ref event);
};
struct ArkUIAniCommonModifier {
    ani_ref* (*getHostContext)(ArkUI_Int32 key);
    void (*syncInstanceId)(ArkUI_Int32 id);
    void (*restoreInstanceId)();
    void (*setDrawCallback)(ani_env* env, ani_long ptr, ani_fn_object fnObj);
    ArkUI_Int32 (*getCurrentInstanceId)();
    ArkUI_Int32 (*getFocusedInstanceId)();
    ani_long (*builderProxyNodeConstruct)(ArkUI_Int32 id);
    ani_ref (*getSharedLocalStorage)();
    void (*setBackgroundImagePixelMap)(ani_env* env, ArkUINodeHandle node, ani_ref pixelMapPtr, ArkUI_Int32 repeat);
    void (*setCustomCallback)(ani_env* env, ani_long ptr, ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout);
    ArkUI_Int32 (*requireArkoalaNodeId)(ArkUI_Int32 capacity);
    ani_boolean (*checkIsUIThread)(ArkUI_Int32 id);
    ani_boolean (*isDebugMode)(ArkUI_Int32 id);
    void (*onMeasureInnerMeasure)(ani_env* env, ani_long ptr);
    void (*onLayoutInnerLayout)(ani_env* env, ani_long ptr);
    void (*setParallelScoped)(ani_boolean parallel);
    void (*setCustomPropertyCallBack)(
        ani_env* env, ArkUINodeHandle node, std::function<void()>&& func,
        std::function<std::string(const std::string&)>&& getFunc);
    std::optional<std::string> (*getCustomProperty)(ani_env* env, ArkUINodeHandle node, const std::string& key);
    void (*setOverlayComponent)(ani_long node, ani_long builderPtr, AniOverlayOptions options);
    ani_double (*vp2px)(ani_double value, ani_int instanceId);
    ani_double (*px2vp)(ani_double value, ani_int instanceId);
    ani_double (*fp2px)(ani_double value, ani_int instanceId);
    ani_double (*px2fp)(ani_double value, ani_int instanceId);
    ani_double (*lpx2px)(ani_double value, ani_int instanceId);
    ani_double (*px2lpx)(ani_double value, ani_int instanceId);
    void* (*transferKeyEventPointer)(ani_long nativePtr);
    void* (*createKeyEventAccessorWithPointer)(ani_long nativePtr);
    void* (*createEventTargetInfoAccessor)();
    void (*eventTargetInfoAccessorWithId)(ani_env* env, ani_long input, ani_string id);
    void* (*createScrollableTargetInfoAccessor)();
    void (*scrollableTargetInfoAccessorWithId)(ani_env* env, ani_long input, ani_string id);
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
};
struct ArkUIAniCustomNodeModifier {
    ani_long (*constructCustomNode)(ani_int, std::function<void()>&& onPageShow, std::function<void()>&& onPageHide,
        std::function<bool()>&& onBackPress, std::function<void()>&& pageTransitionFunc,
        std::function<void()>&& onCleanupFunc, std::function<std::string()>&& onDumpInspectorFunc);
    void (*requestFrame)();
    ani_object (*queryNavigationInfo)(ani_env* env, ani_long node);
    ani_object (*queryNavDestinationInfo)(ani_env* env, ani_long node);
    ani_object (*queryNavDestinationInfo0)(ani_env* env, ani_long node, ani_int isInner);
    ani_object (*queryRouterPageInfo)(ani_env* env, ani_long node);
};
struct ArkUIAniDrawModifier {
    void (*setDrawModifier)(ani_env* env, ani_long ptr, ani_int flag, ani_object fnObj);
    void (*invalidate)(ani_env* env, ani_long ptr);
};
struct ArkUIAniContentSlotModifier {
    ArkUIContentSlot (*construct)(ArkUI_Int32 id);
    void (*setContentSlotOptions)(ArkUIContentSlot node, ArkUINodeContent value);
};
struct ArkUIAniLazyForEachNodeModifier {
    ani_long (*constructLazyForEachNode)(ani_int);
};
struct ArkUIAniWaterFlowModifier {
    void (*setWaterFlowOptions)(ani_env* env, ani_long ptr, ani_object fnObj);
};
struct ArkUIAniListModifier {
    void (*setListChildrenMainSize)(ani_env* env, ani_long ptr, ani_object obj);
};
struct ArkUIAniComponentSnapshotModifier {
    void (*createFromBuilder)(
        ArkUINodeHandle node, const ArkUIComponentSnapshotAsync& asyncCtx, const ArkUISnapshotParam& param);
    void (*createFromComponent)(
        ArkUINodeHandle node, const ArkUIComponentSnapshotAsync& asyncCtx, const ArkUISnapshotParam& param);
};
struct ArkUIAniAnimationModifier {
    bool (*hasAnimatableProperty)(ani_env* env, ArkUINodeHandle node, ani_string name);
    void (*updateAnimatableProperty)(
        ani_env* env, ArkUINodeHandle node, ani_string propertyName, ani_object property);
    void (*createAnimatableProperty)(
        ani_env* env, ArkUINodeHandle node, ani_string propertyName, ani_object property, ani_fn_object callback);
    void (*createPageTransitionEnter)(ani_env* env, ani_object options);
    void (*pageTransitionSetOnEnter)(ani_env* env, ani_fn_object callback);
    void (*createPageTransitionExit)(ani_env* env, ani_object options);
    void (*pageTransitionSetOnExit)(ani_env* env, ani_fn_object callback);
    void (*pageTransitionSetSlide)(ani_env* env, ani_object slide);
    void (*pageTransitionSetTranslate)(ani_env* env, ani_object options);
    void (*pageTransitionSetScale)(ani_env* env, ani_object options);
    void (*pageTransitionSetOpacity)(ani_env* env, ani_double opacity);
};
struct ArkUIAniInteropModifier {
    ani_long (*createViewStackProcessor)();
    ani_long (*popViewStackProcessor)();
    void (*deleteViewStackProcessor)(ani_long ptr);
};
struct ArkUIAniDragControllerModifier {
    bool (*aniHandleExecuteDrag)(ArkUIDragControllerAsync& asyncCtx);
    bool (*aniHandleDragAction)(ArkUIDragControllerAsync& asyncCtx);
    bool (*aniHandleDragActionStartDrag)(ArkUIDragControllerAsync& asyncCtx);
    void (*createDragEventPeer)(const ArkUIDragNotifyMessage& dragNotifyMsg, ani_long& dragEventPeer);
    ani_object (*aniGetDragPreview)([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass);
    void (*aniDragPreviewSetForegroundColor)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object color, ani_long dragPreviewPtr);
    void (*aniDragPreviewAnimate)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object options, ani_object handler,
        ani_long dragPreviewPtr);
    void (*aniDragActionSetDragEventStrictReportingEnabled)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, bool enable);
    void (*aniDragActionCancelDataLoading)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key);
    void (*aniDragActionNotifyDragStartReques)(
        [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_enum_item requestStatus);
};
struct ArkUIAniImageSpanModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setAltPixelMap)(ArkUINodeHandle node, void* pixelmap);
    void (*setDrawingColorFilter)(ArkUINodeHandle node, void* colorFilter);
};
struct ArkUIAniStyledStringModifier {
    void (*setPixelMap)(ArkUIStyledString peer, void* nativePixelMap);
    void* (*getPixelMap)(ArkUIStyledString peer);
};
struct ArkUIAniVideoModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelMap);
};
struct ArkUIAniShapeModifier {
    void (*setPixelMap)(ArkUINodeHandle node, void* pixelMap);
};
struct ArkUIAniRichEditorModifier {
    ani_long (*transferPixelMap)(void* pixelMap);
};
struct ArkUIAniStateMgmtModifier {
    std::string (*persistentStorageGet)(const std::string& key);
    void (*persistentStorageSet)(const std::string& key, const std::string& value);
    bool (*persistentStorageHas)(const std::string& key);
    void (*persistentStorageDelete)(const std::string& key);
    void (*persistentStorageClear)();
    int32_t (*getColorMode)();
    float (*getFontWeightScale)();
    float (*getFontScale)();
    bool (*getAccessibilityEnabled)();
    std::string (*getLayoutDirection)();
    std::string (*getLanguageCode)();
};
struct ArkUIAniXComponentModifier {
    void (*setXComponentControllerCallback)(ArkUINodeHandle node,
        std::function<void(const std::string&)>&& onSurfaceCreated,
        std::function<void(const std::string&, float, float, float, float)>&& onSurfaceChanged,
        std::function<void(const std::string&)>&& onSurfaceDestroyed);
};

struct ArkUIAniConditionScopeModifier {
    ani_long (*constructConditionScope)(ani_int);
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
};

struct ArkUIAniModifiers {
    ArkUI_Int32 version;
    const ArkUIAniImageModifier* (*getImageAniModifier)();
    const ArkUIAniWebModifier* (*getWebAniModifier)();
    const ArkUIAniDragModifier* (*getDragAniModifier) ();
    const ArkUIAniCommonModifier* (*getCommonAniModifier)();
    const ArkUIAniCustomNodeModifier* (*getCustomNodeAniModifier)();
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
    const ArkUIAniImageSpanModifier* (*getImageSpanAniModifier)();
    const ArkUIAniVideoModifier* (*getArkUIAniVideoModifier)();
    const ArkUIAniShapeModifier* (*getArkUIAniShapeModifier)();
    const ArkUIAniRichEditorModifier* (*getRichEditorAniModifier)();
    const ArkUIAniStateMgmtModifier* (*getStateMgmtAniModifier)();
    const ArkUIAniXComponentModifier* (*getArkUIAniXComponentModifier)();
    const ArkUIAniConditionScopeModifier* (*getArkUIAniConditionScopeModifier)();
    const ArkUIAniComponentConentModifier* (*getArkUIAniComponentConentModifier)();
    const ArkUIAniCanvasModifier* (*getCanvasAniModifier)();
};

__attribute__((visibility("default"))) const ArkUIAniModifiers* GetArkUIAniModifiers(void);
#ifdef __cplusplus
};
#endif

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_ANI_API_H
