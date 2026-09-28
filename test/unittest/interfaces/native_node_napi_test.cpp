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

#include <array>
#include <cstdint>
#include <string>

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_custom_env_view_white_list.h"
#include "frameworks/base/error/error_code.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "gtest/gtest.h"
#include "napi/napi_runtime.cpp"
#include "native_interface.h"
#include "native_interface_xcomponent.h"
#include "native_node.h"
#include "native_node_napi.h"
#include "native_type.h"
#include "node_model.h"
#include "node_model_safely.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"
#include "interfaces/native/node/config_manager.h"

using namespace testing;
using namespace testing::ext;

class NativeNodeNapiTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

void CallBack(uint64_t nanoTimestamp, uint32_t frameCount, void* userData)
{
    printf("nanoTimestamp = %llu\n", nanoTimestamp);
    printf("frameCount = %d\n", frameCount);
    if (userData) {
        int* myData = (int*)userData;
        printf("User data = %d\n", *myData);
    }
}

/**
 * @tc.name: NativeNodeNapiTest001
 * @tc.desc: Test OH_ArkUI_GetContextFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest001, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_ContextHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetContextFromNapiValue(env, value, context);
    EXPECT_EQ(code, 401);
}

/**
 * @tc.name: NativeNodeNapiTest002
 * @tc.desc: Test OH_ArkUI_GetNodeContentFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest002, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_NodeContentHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetNodeContentFromNapiValue(env, value, context);
    EXPECT_EQ(code, 401);
}

/**
 * @tc.name: NativeNodeNapiTest003
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest003, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_NodeHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, context);
    EXPECT_EQ(code, 401);
}

/**
 * @tc.name: NativeNodeNapiTest004
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest004, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(static_cast<ArkUI_NativeAPIVariantKind>(-1), "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest005
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest005, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest006
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest006, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_DIALOG, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest007
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest007, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_GESTURE, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest008
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest008, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_ANIMATE, "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest009
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest009, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(
        static_cast<ArkUI_NativeAPIVariantKind>(ARKUI_NATIVE_GESTURE + 1), "");
    EXPECT_EQ(object, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest010
 * @tc.desc: Test OH_ArkUI_QueryModuleInterfaceByName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest010, TestSize.Level1)
{
    void* object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_MULTI_THREAD_NATIVE_NODE, "");
    EXPECT_EQ(object, nullptr);
    object = OH_ArkUI_QueryModuleInterfaceByName(ARKUI_MULTI_THREAD_NATIVE_NODE, "ArkUI_NativeNodeAPI_1");
    EXPECT_NE(object, nullptr);
}

/**
 * @tc.name: NavigationAPITest001
 * @tc.desc: Test OH_ArkUI_GetNavigationId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest001, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavigationId(nullptr, nullptr, 0, nullptr);
    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavigationId"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest002
 * @tc.desc: Test OH_ArkUI_GetNavDestinationName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest002, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationName(nullptr, nullptr, 0, nullptr);
    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavDestinationName"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest003
 * @tc.desc: Test OH_ArkUI_GetNavStackLength function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest003, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavStackLength(nullptr, nullptr);
    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavStackLength"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest004
 * @tc.desc: Test OH_ArkUI_GetNavDestinationNameByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest004, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationNameByIndex(nullptr, 0, nullptr, 0, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavDestinationNameByIndex"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest005
 * @tc.desc: Test OH_ArkUI_GetNavDestinationId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest005, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationId(nullptr, nullptr, 0, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavDestinationId"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest006
 * @tc.desc: Test OH_ArkUI_GetNavDestinationState function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest006, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationState(nullptr, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavDestinationState"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest007
 * @tc.desc: Test OH_ArkUI_GetNavDestinationIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest007, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationIndex(nullptr, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetNavDestinationIndex"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest008
 * @tc.desc: Test OH_ArkUI_GetNavDestinationParam function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest008, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetNavDestinationParam(nullptr);
    EXPECT_EQ(ret, nullptr);
}

/**
 * @tc.name: NavigationAPITest009
 * @tc.desc: Test OH_ArkUI_GetRouterPageIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest009, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageIndex(nullptr, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetRouterPageIndex"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest010
 * @tc.desc: Test OH_ArkUI_GetRouterPageName function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest010, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageName(nullptr, nullptr, 0, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetRouterPageName"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest011
 * @tc.desc: Test OH_ArkUI_GetRouterPagePath function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest011, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPagePath(nullptr, nullptr, 0, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetRouterPagePath"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest012
 * @tc.desc: Test OH_ArkUI_GetRouterPageState function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest012, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageState(nullptr, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetRouterPageState"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NavigationAPITest013
 * @tc.desc: Test OH_ArkUI_GetRouterPageId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NavigationAPITest013, TestSize.Level1)
{
    auto ret = OH_ArkUI_GetRouterPageId(nullptr, nullptr, 0, nullptr);
    const char *errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    ASSERT_NE(errorMessage, nullptr);
    std::string errorMessageStr(errorMessage);
    EXPECT_NE(errorMessageStr.find(std::string("errorCode: ") + std::to_string(ret)), std::string::npos);
    EXPECT_NE(errorMessageStr.find("functionName: OH_ArkUI_GetRouterPageId"), std::string::npos);
    EXPECT_NE(errorMessageStr.find("errorMessage: Node is null"), std::string::npos);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: InitModuleForArkTSEnvAPITest001
 * @tc.desc: Test OH_ArkUI_InitModuleForArkTSEnv function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, InitModuleForArkTSEnvAPITest001, TestSize.Level1)
{
    NativeEngineMock engine;

    /**
     * @tc.steps: step1. Call OH_ArkUI_InitModuleForArkTSEnv with a null environment.
     * @tc.expected: The return value should be ARKUI_ERROR_CODE_PARAM_INVALID.
     */
    auto ret = OH_ArkUI_InitModuleForArkTSEnv(nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);

    /**
     * @tc.steps: step2. Call OH_ArkUI_InitModuleForArkTSEnv with a valid environment.
     * @tc.expected: The return value should be ARKUI_ERROR_CODE_NO_ERROR.
     */
    ret = OH_ArkUI_InitModuleForArkTSEnv(napi_env(engine));
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step3. Call OH_ArkUI_InitModuleForArkTSEnv again with the same environment.
     * @tc.expected: The return value should be ARKUI_ERROR_CODE_NO_ERROR.
     */
    ret = OH_ArkUI_InitModuleForArkTSEnv(napi_env(engine));
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_NO_ERROR);

    /**
     * @tc.steps: step4. Call OH_ArkUI_NotifyArkTSEnvDestroy.
     */
    OH_ArkUI_NotifyArkTSEnvDestroy(napi_env(engine));
    OH_ArkUI_NotifyArkTSEnvDestroy(nullptr);
}

/**
 * @tc.name: WhiteListInCustomEnvTest001
 * @tc.desc: In custom env, white list check.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, WhiteListInCustomEnvTest001, TestSize.Level1)
{
    std::unordered_set<std::string> supportedTargetsInCustomEnvTest = {
        "Flex",
        "TextController",
        "Text",
        "Animator",
        "SpringProp",
        "SpringMotion",
        "ScrollMotion",
        "Span",
        "NativeCustomSpan",
        "SpanString",
        "MutableSpanString",
        "TextStyle",
        "DecorationStyle",
        "BaselineOffsetStyle",
        "LetterSpacingStyle",
        "UrlStyle",
        "NativeGestureStyle",
        "TextShadowSpan",
        "BackgroundColorStyle",
        "ImageAttachment",
        "ParagraphStyleSpan",
        "LineHeightSpan",
        "TextLayout",
        "Button",
        "Canvas",
        "LazyForEach",
        "LazyVGridLayout",
        "List",
        "ListItem",
        "ListItemGroup",
        "LoadingProgress",
        "Image",
        "ImageAnimator",
        "Counter",
        "Progress",
        "Column",
        "Row",
        "Grid",
        "GridItem",
        "GridContainer",
        "Slider",
        "Stack",
        "ForEach",
        "Divider",
        "Swiper",
        "Indicator",
        "Panel",
        "RepeatNative",
        "RepeatVirtualScrollNative",
        "RepeatVirtualScroll2Native",
        "NativeNavPathStack",
        "If",
        "Scroll",
        "ScrollBar",
        "GridRow",
        "GridCol",
        "Stepper",
        "StepperItem",
        "Toggle",
        "ToolBarItem",
        "Blank",
        "Calendar",
        "Rect",
        "Shape",
        "Path",
        "Circle",
        "Line",
        "Polygon",
        "Polyline",
        "Ellipse",
        "Tabs",
        "TabContent",
        "TextPicker",
        "TimePicker",
        "DatePicker",
        "PageTransitionEnter",
        "PageTransitionExit",
        "RowSplit",
        "ColumnSplit",
        "AlphabetIndexer",
        "Hyperlink",
        "Radio",
        "ActionSheet",
        "AlertDialog",
        "ContextMenu",
        "Particle",
        "__KeyboardAvoid__",
        "TextMenu",
        "TextArea",
        "TextInput",
        "TextClock",
        "SideBarContainer",
        "DataPanel",
        "Badge",
        "Gauge",
        "Marquee",
        "Menu",
        "MenuItem",
        "MenuItemGroup",
        "Gesture",
        "TapGesture",
        "LongPressGesture",
        "PanGesture",
        "SwipeGesture",
        "PinchGesture",
        "RotationGesture",
        "GestureGroup",
        "PanGestureOption",
        "PanGestureOptions",
        "NativeCustomDialogController",
        "Scroller",
        "ListScroller",
        "SwiperController",
        "IndicatorController",
        "TabsController",
        "CalendarController",
        "CanvasRenderingContext2D",
        "OffscreenCanvasRenderingContext2D",
        "CanvasGradient",
        "ImageData",
        "Path2D",
        "RenderingContextSettings",
        "Matrix2D",
        "CanvasPattern",
        "DrawingRenderingContext",
        "Search",
        "Select",
        "SearchController",
        "TextClockController",
        "Sheet",
        "JSClipboard",
        "PatternLock",
        "PatternLockController",
        "TextTimer",
        "TextAreaController",
        "TextInputController",
        "TextTimerController",
        "Checkbox",
        "CheckboxGroup",
        "Refresh",
        "WaterFlow",
        "FlowItem",
        "RelativeContainer",
        "__Common__",
        "__Recycle__",
        "LinearGradient",
        "ImageSpan",
        "RichEditor",
        "RichEditorController",
        "RichEditorStyledStringController",
        "LayoutManager",
        "NodeContainer",
        "__JSBaseNode__",
        "SymbolGlyph",
        "SymbolSpan",
        "ContainerSpan",
        "__RectShape__",
        "__CircleShape__",
        "__EllipseShape__",
        "__PathShape__",
        "ContentSlot",
        "ArkUINativeNodeContent",
        "GestureRecognizer",
        "EventTargetInfo",
        "ScrollableTargetInfo",
        "PanRecognizer",
        "LinearIndicator",
        "LinearIndicatorController",
        "TapRecognizer",
        "LongPressRecognizer",
        "SwipeRecognizer",
        "PinchRecognizer",
        "RotationRecognizer",
        "TouchRecognizer",
    };
    for (const auto& target : supportedTargetsInCustomEnvTest) {
        EXPECT_NE(OHOS::Ace::Framework::supportedTargetsInCustomEnv.find(target),
            OHOS::Ace::Framework::supportedTargetsInCustomEnv.end());
    }
}

/**
 * @tc.name: PostFrameCallbackAPITest001
 * @tc.desc: Test OH_ArkUI_PostFrameCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, PostFrameCallbackAPITest001, TestSize.Level1)
{
    ArkUI_ContextHandle uiContext = new ArkUI_Context({.id=10000});
    int userdata = 5;
    auto ret = OH_ArkUI_PostFrameCallback(uiContext, &userdata, CallBack);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
}

/**
 * @tc.name: PostFrameCallbackAPITest002
 * @tc.desc: Test OH_ArkUI_PostFrameCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, PostFrameCallbackAPITest002, TestSize.Level1)
{
    ArkUI_ContextHandle uiContext = new ArkUI_Context({.id=10000});
    int userdata = 6;
    auto ret = OH_ArkUI_PostFrameCallback(uiContext, &userdata, nullptr);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_CALLBACK_INVALID);
}

/**
 * @tc.name: PostFrameCallbackAPITest003
 * @tc.desc: Test OH_ArkUI_PostFrameCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, PostFrameCallbackAPITest003, TestSize.Level1)
{
    int userdata = 7;
    auto ret = OH_ArkUI_PostFrameCallback(nullptr, &userdata, CallBack);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
}

/**
 * @tc.name: GreatOrEqualTargetAPIVersion001
 * @tc.desc: Test GreatOrEqualTargetAPIVersion function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, GreatOrEqualTargetAPIVersion001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    auto ret = OHOS::Ace::AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(
        OHOS::Ace::PlatformVersion::VERSION_TWELVE);
    auto ret1 = OHOS::Ace::NodeModel::GreatOrEqualTargetAPIVersion(OHOS::Ace::PlatformVersion::VERSION_TWELVE);
    EXPECT_EQ(ret, ret1);
}

/**
 * @tc.name: OH_ArkUI_PostAsyncUITaskAPITest001
 * @tc.desc: Test OH_ArkUI_PostAsyncUITask function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, OH_ArkUI_PostAsyncUITaskAPITest001, TestSize.Level1)
{
    ArkUI_ContextHandle uiContext = new ArkUI_Context({.id=10000});
    auto ret = OH_ArkUI_PostAsyncUITask(uiContext, nullptr, [](void* asyncUITaskData){}, [](void* asyncUITaskData){});
    EXPECT_NE(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PostUITaskAPITest001
 * @tc.desc: Test OH_ArkUI_PostUITask function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, OH_ArkUI_PostUITaskAPITest001, TestSize.Level1)
{
    ArkUI_ContextHandle uiContext = new ArkUI_Context({.id=10000});
    auto ret = OH_ArkUI_PostUITask(uiContext, nullptr, [](void* asyncUITaskData){});
    EXPECT_NE(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: OH_ArkUI_PostUITaskAndWaitAPITest001
 * @tc.desc: Test OH_ArkUI_PostUITaskAndWait function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, OH_ArkUI_PostUITaskAndWaitAPITest001, TestSize.Level1)
{
    ArkUI_ContextHandle uiContext = new ArkUI_Context({.id=10000});
    auto ret = OH_ArkUI_PostUITaskAndWait(uiContext, nullptr, [](void* asyncUITaskData){});
    EXPECT_NE(ret, ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeBackgroundImagePositionTest001
 * @tc.desc: Test NativeBackgroundImagePositon
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeBackgroundImagePositionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto row = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(column, nullptr);
    ASSERT_NE(row, nullptr);
    nodeAPI->addChild(column, row);
    EXPECT_EQ(nodeAPI->getTotalChildCount(column), 1);

    /**
     * @tc.steps: step2. test backgroundImagePositon params error
     */
    ArkUI_NumberValue value[] = { { .f32 = 100.0 }, { .f32 = 100.0 } };
    ArkUI_AttributeItem backgroundImagePosition = { .value = value, .size = 0 };
    auto ret = nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition);
    EXPECT_EQ(ret, ARKUI_ERROR_CODE_PARAM_INVALID);
    ArkUI_AttributeItem backgroundImagePosition2 = { .value = value, .size = 5 };
    auto ret2 = nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition2);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeBackgroundImagePositionTest002
 * @tc.desc: Test NativeBackgroundImagePositon
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeBackgroundImagePositionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create node
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto row = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(column, nullptr);
    ASSERT_NE(row, nullptr);
    nodeAPI->addChild(column, row);
    EXPECT_EQ(nodeAPI->getTotalChildCount(column), 1);

    /**
     * @tc.steps: step2. test backgroundImagePositon with position
     */
    ArkUI_NumberValue value[] = { { .f32 = 100.0 }, { .f32 = 100.0 } };
    ArkUI_AttributeItem backgroundImagePosition = { .value = value, .size = 2 };
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition);
    auto ret = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_NEAR(ret->value[0].f32, 100.0f, 0.01f);
    EXPECT_NEAR(ret->value[1].f32, 100.0f, 0.01f);
}

/**
 * @tc.name: NativeBackgroundImagePositionTest003
 * @tc.desc: Test NativeBackgroundImagePositon
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeBackgroundImagePositionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create not thread safe native node
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto row = nodeAPI->createNode(ARKUI_NODE_STACK);
    ArkUI_NumberValue widthValue3[] = { 300 };
    ArkUI_AttributeItem widthItem3 = { widthValue3, 1 };
    ArkUI_NumberValue heightValue3[] = { 300 };
    ArkUI_AttributeItem heightItem3 = { heightValue3, 1 };
    ArkUI_NumberValue bgSizeVal[] = { { .f32 = 100 }, { .f32 = 100 } };
    ArkUI_AttributeItem bgSize = { bgSizeVal, 2 };
    nodeAPI->setLengthMetricUnit(row, ArkUI_LengthMetricUnit::ARKUI_LENGTH_METRIC_UNIT_PX);
    nodeAPI->setAttribute(row, NODE_WIDTH, &widthItem3);
    nodeAPI->setAttribute(row, NODE_HEIGHT, &heightItem3);
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_SIZE, &bgSize);
    ASSERT_NE(column, nullptr);
    ASSERT_NE(row, nullptr);
    nodeAPI->addChild(column, row);
    EXPECT_EQ(nodeAPI->getTotalChildCount(column), 1);

    /**
     * @tc.steps: step2. test backgroundImagePositon with position and alignment
     */
    ArkUI_NumberValue value[] = { { .f32 = 100.0 }, { .f32 = 100.0 }, { .i32 = 4 }, { .i32 = 0 } };
    ArkUI_AttributeItem backgroundImagePosition = { .value = value, .size = 3 };
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition);
    auto ret = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_NEAR(ret->value[0].f32, 100.0f, 0.01f);
    EXPECT_NEAR(ret->value[1].f32, 100.0f, 0.01f);
    EXPECT_EQ(ret->value[2].i32, 4);
    EXPECT_EQ(ret->value[3].i32, 3);

    /**
     * @tc.steps: step3. test align and direction default
     */
    nodeAPI->resetAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    value[2].i32 = -1;
    ArkUI_AttributeItem backgroundImagePosition2 = { .value = value, .size = 3 };
    auto ret2 = nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition2);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    nodeAPI->resetAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    value[2].i32 = 9;
    ArkUI_AttributeItem backgroundImagePosition3 = { .value = value, .size = 3 };
    auto ret3 = nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition3);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeBackgroundImagePositionTest004
 * @tc.desc: Test NativeBackgroundImagePositon
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeBackgroundImagePositionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create not thread safe native node
     */
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    ASSERT_NE(nodeAPI, nullptr);
    auto column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    auto row = nodeAPI->createNode(ARKUI_NODE_STACK);
    ArkUI_NumberValue widthValue3[] = { 300 };
    ArkUI_AttributeItem widthItem3 = { widthValue3, 1 };
    ArkUI_NumberValue heightValue3[] = { 300 };
    ArkUI_AttributeItem heightItem3 = { heightValue3, 1 };
    ArkUI_NumberValue bgSizeVal[] = { { .f32 = 100 }, { .f32 = 100 } };
    ArkUI_AttributeItem bgSize = {bgSizeVal, 2};
    nodeAPI->setLengthMetricUnit(row, ArkUI_LengthMetricUnit::ARKUI_LENGTH_METRIC_UNIT_PX);
    nodeAPI->setAttribute(row, NODE_WIDTH, &widthItem3);
    nodeAPI->setAttribute(row, NODE_HEIGHT, &heightItem3);
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_SIZE, &bgSize);
    ASSERT_NE(column, nullptr);
    ASSERT_NE(row, nullptr);
    nodeAPI->addChild(column, row);
    EXPECT_EQ(nodeAPI->getTotalChildCount(column), 1);

    /**
     * @tc.steps: step2. test backgroundImagePositon with position alignment and direction
     */
    ArkUI_NumberValue value[] = { { .f32 = 100.0 }, { .f32 = 100.0 }, { .i32 = 0 }, { .i32 = 0 } };
    ArkUI_AttributeItem backgroundImagePosition = { .value = value, .size = 4 };
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition);
    auto ret = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_NEAR(ret->value[0].f32, 100.0f, 0.01f);
    EXPECT_NEAR(ret->value[1].f32, 100.0f, 0.01f);
    EXPECT_EQ(ret->value[2].i32, 0);
    EXPECT_EQ(ret->value[3].i32, 0);

    /**
     * @tc.steps: step3. test align and direction default
     */
    nodeAPI->resetAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    value[3].i32 = -1;
    ArkUI_AttributeItem backgroundImagePosition2 = { .value = value, .size = 4 };
    auto ret2 = nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition2);
    EXPECT_EQ(ret2, ARKUI_ERROR_CODE_PARAM_INVALID);
    nodeAPI->resetAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    value[3].i32 = 2;
    ArkUI_AttributeItem backgroundImagePosition3 = { .value = value, .size = 4 };
    auto ret3 = nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition3);
    EXPECT_EQ(ret3, ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeNapiTest011
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest011, TestSize.Level1)
{
    napi_env__* env = nullptr;
    napi_value__* value = nullptr;
    ArkUI_NodeHandle* context = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, context);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: NativeNodeNapiTest012
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue with a null external pointer in builderNode_.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest012, TestSize.Level1)
{
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    napi_value value = nullptr;
    napi_value builderNode = nullptr;
    napi_value nodePtr = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);
    ASSERT_EQ(napi_create_object(env, &builderNode), napi_ok);
    ASSERT_EQ(napi_create_external(env, nullptr, nullptr, nullptr, &nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, builderNode, "nodePtr_", nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, value, "builderNode_", builderNode), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest014
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue with a value without nodePtr_/builderNode_ property.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest014, TestSize.Level1)
{
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    napi_value value = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest015
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue with a nodePtr_ property of the wrong type.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest015, TestSize.Level1)
{
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    napi_value value = nullptr;
    napi_value nodePtr = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);
    ASSERT_EQ(napi_create_string_utf8(env, "invalid", NAPI_AUTO_LENGTH, &nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, value, "nodePtr_", nodePtr), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest016
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue with a null external pointer in nodePtr_.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest016, TestSize.Level1)
{
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    napi_value value = nullptr;
    napi_value nodePtr = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);
    ASSERT_EQ(napi_create_external(env, nullptr, nullptr, nullptr, &nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, value, "nodePtr_", nodePtr), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest017
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue with a builderNode_ that has no nodePtr_ property.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest017, TestSize.Level1)
{
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    napi_value value = nullptr;
    napi_value builderNode = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);
    ASSERT_EQ(napi_create_object(env, &builderNode), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, value, "builderNode_", builderNode), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: NativeNodeNapiTest018
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue success path with a valid nodePtr_ external.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest018, TestSize.Level1)
{
    if (OHOS::Ace::NodeModel::GetFullImpl() != nullptr) {
        GTEST_SKIP() << "FullImpl is initialized, success path is not exercised in the mock environment";
    }
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    auto pattern = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    auto frameNode = OHOS::Ace::NG::FrameNode::CreateFrameNode("text", 100001, pattern, true);
    ASSERT_NE(frameNode, nullptr);
    napi_value value = nullptr;
    napi_value nodePtr = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);
    ASSERT_EQ(napi_create_external(env, OHOS::Ace::AceType::RawPtr(frameNode), nullptr, nullptr, &nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, value, "nodePtr_", nodePtr), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle->type, -1);
    EXPECT_TRUE(handle->buildNode);
    EXPECT_FALSE(handle->cNode);
    delete handle;
}

/**
 * @tc.name: NativeNodeNapiTest019
 * @tc.desc: Test OH_ArkUI_GetNodeHandleFromNapiValue success path with a valid builderNode_.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest019, TestSize.Level1)
{
    if (OHOS::Ace::NodeModel::GetFullImpl() != nullptr) {
        GTEST_SKIP() << "FullImpl is initialized, success path is not exercised in the mock environment";
    }
    NativeEngineMock engine;
    napi_env env = napi_env(engine);
    auto pattern = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    auto frameNode = OHOS::Ace::NG::FrameNode::CreateFrameNode("text", 100002, pattern, true);
    ASSERT_NE(frameNode, nullptr);
    napi_value value = nullptr;
    napi_value builderNode = nullptr;
    napi_value nodePtr = nullptr;
    ASSERT_EQ(napi_create_object(env, &value), napi_ok);
    ASSERT_EQ(napi_create_object(env, &builderNode), napi_ok);
    ASSERT_EQ(napi_create_external(env, OHOS::Ace::AceType::RawPtr(frameNode), nullptr, nullptr, &nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, builderNode, "nodePtr_", nodePtr), napi_ok);
    ASSERT_EQ(napi_set_named_property(env, value, "builderNode_", builderNode), napi_ok);

    ArkUI_NodeHandle handle = nullptr;
    int32_t code = OH_ArkUI_GetNodeHandleFromNapiValue(env, value, &handle);
    EXPECT_EQ(code, OHOS::Ace::ERROR_CODE_NO_ERROR);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle->type, -1);
    EXPECT_TRUE(handle->buildNode);
    EXPECT_FALSE(handle->cNode);
    delete handle;
}

/**
 * @tc.name: NativeNodeNapiTest013
 * @tc.desc: Test OH_ArkUI_EnableEventPassthrough function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeNapiTest, NativeNodeNapiTest013, TestSize.Level1)
{
    ArkUI_ContextHandle uiContext = new ArkUI_Context({ .id = 10000 });
    bool enable = true;
    ArkUI_RawInputEventType eventType = ArkUI_RawInputEventType::ARKUI_RAW_INPUT_EVENT_TYPE_MOUSE;
    auto code = OH_ArkUI_EnableEventPassthrough(uiContext, enable, eventType);
    EXPECT_EQ(code, ARKUI_ERROR_CODE_PARAM_INVALID);
}

namespace OHOS::Ace {
class NativeXComponentUafTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        // This file compiles without `#define private public`, so the mock
        // environment is wired through public APIs only: the container is
        // constructed with the mock pipeline via the SetUp overload, the task
        // executor is installed through the public setter, and the mock pipeline
        // already carries its own task executor from MockPipelineContext::SetUp.
        NG::MockPipelineContext::SetUp();
        MockContainer::SetUp(NG::MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>());
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
    void SetUp() {}
    void TearDown() {}
};

namespace {
constexpr int32_t RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE = 1;

// Leave detection disabled for subsequent tests.
void RestoreRuntimeCheckMode()
{
    EXPECT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED)));
}

void XComponentFrameCallback(ArkUI_NodeHandle node, uint64_t timestamp, uint64_t targetTimestamp)
{
    (void)node;
    (void)timestamp;
    (void)targetTimestamp;
}

void ImageAnalyzerCallback(
    ArkUI_NodeHandle node, ArkUI_XComponent_ImageAnalyzerState statusCode, void* userData)
{
    (void)node;
    (void)statusCode;
    (void)userData;
}

// Slot index of each listed API in the result arrays below; the order follows the
// requirement list and SLOT_COUNT is the number of listed APIs.
enum XComponentApiSlot : size_t {
    SLOT_ACCESSIBILITY_PROVIDER_CREATE = 0,
    SLOT_SURFACE_HOLDER_CREATE,
    SLOT_XCOMPONENT_FINALIZE,
    SLOT_XCOMPONENT_INITIALIZE,
    SLOT_XCOMPONENT_IS_INITIALIZED,
    SLOT_XCOMPONENT_REGISTER_ON_FRAME_CALLBACK,
    SLOT_XCOMPONENT_SET_AUTO_INITIALIZE,
    SLOT_XCOMPONENT_SET_EXPECTED_FRAME_RATE_RANGE,
    SLOT_XCOMPONENT_SET_NEED_SOFT_KEYBOARD,
    SLOT_XCOMPONENT_START_IMAGE_ANALYZER,
    SLOT_XCOMPONENT_STOP_IMAGE_ANALYZER,
    SLOT_XCOMPONENT_UNREGISTER_ON_FRAME_CALLBACK,
    SLOT_ATTACH_NATIVE_ROOT_NODE,
    SLOT_DETACH_NATIVE_ROOT_NODE,
    SLOT_GET_NATIVE_XCOMPONENT,
    SLOT_COUNT,
};

// The entries going through CheckValidXComponentNode and returning a plain code
// span from SLOT_XCOMPONENT_FINALIZE to SLOT_XCOMPONENT_UNREGISTER_ON_FRAME_CALLBACK.
constexpr size_t FIRST_VALIDATED_SLOT = SLOT_XCOMPONENT_FINALIZE;
constexpr size_t LAST_VALIDATED_SLOT = SLOT_XCOMPONENT_UNREGISTER_ON_FRAME_CALLBACK;

// Encodes a pointer result as 1 (non-null) or 0 (null) for the int32 result array.
int32_t EncodePointerResult(const void* pointer)
{
    return pointer != nullptr ? 1 : 0;
}

// Calls the 15 listed public C APIs one by one and records the observable results:
// int32 return codes are recorded as-is and pointer-returning entries record the
// encoded non-null flag. Attach/Detach use a stack OH_NativeXComponent holding a
// null implementation: for a controlled sample whose uiNodeHandle is null,
// AttachNativeRootNode/DetachNativeRootNode return on the null parameter before the
// implementation is touched, so the component is never dereferenced.
std::array<int32_t, SLOT_COUNT> CallAllXComponentApis(ArkUI_NodeHandle node)
{
    std::array<int32_t, SLOT_COUNT> results {};
    OH_NativeXComponent component(nullptr);
    bool isInitialized = false;
    OH_NativeXComponent_ExpectedRateRange range { 1, 120, 60 };
    results[SLOT_ACCESSIBILITY_PROVIDER_CREATE] =
        EncodePointerResult(OH_ArkUI_AccessibilityProvider_Create(node));
    results[SLOT_SURFACE_HOLDER_CREATE] = EncodePointerResult(OH_ArkUI_SurfaceHolder_Create(node));
    results[SLOT_XCOMPONENT_FINALIZE] = OH_ArkUI_XComponent_Finalize(node);
    results[SLOT_XCOMPONENT_INITIALIZE] = OH_ArkUI_XComponent_Initialize(node);
    results[SLOT_XCOMPONENT_IS_INITIALIZED] = OH_ArkUI_XComponent_IsInitialized(node, &isInitialized);
    results[SLOT_XCOMPONENT_REGISTER_ON_FRAME_CALLBACK] =
        OH_ArkUI_XComponent_RegisterOnFrameCallback(node, XComponentFrameCallback);
    results[SLOT_XCOMPONENT_SET_AUTO_INITIALIZE] = OH_ArkUI_XComponent_SetAutoInitialize(node, true);
    results[SLOT_XCOMPONENT_SET_EXPECTED_FRAME_RATE_RANGE] =
        OH_ArkUI_XComponent_SetExpectedFrameRateRange(node, range);
    results[SLOT_XCOMPONENT_SET_NEED_SOFT_KEYBOARD] = OH_ArkUI_XComponent_SetNeedSoftKeyboard(node, true);
    results[SLOT_XCOMPONENT_START_IMAGE_ANALYZER] =
        OH_ArkUI_XComponent_StartImageAnalyzer(node, nullptr, ImageAnalyzerCallback);
    results[SLOT_XCOMPONENT_STOP_IMAGE_ANALYZER] = OH_ArkUI_XComponent_StopImageAnalyzer(node);
    results[SLOT_XCOMPONENT_UNREGISTER_ON_FRAME_CALLBACK] =
        OH_ArkUI_XComponent_UnregisterOnFrameCallback(node);
    results[SLOT_ATTACH_NATIVE_ROOT_NODE] = OH_NativeXComponent_AttachNativeRootNode(&component, node);
    results[SLOT_DETACH_NATIVE_ROOT_NODE] = OH_NativeXComponent_DetachNativeRootNode(&component, node);
    results[SLOT_GET_NATIVE_XCOMPONENT] = EncodePointerResult(OH_NativeXComponent_GetNativeXComponent(node));
    return results;
}

// In this test environment the mock node modifier table leaves getXComponentModifier
// null, so entries reaching the modifier lookup deterministically return 401/nullptr;
// a stack object that is not in the node set deterministically returns 401 from
// CheckValidXComponentNode.
constexpr int32_t EXPECTED_INVALID_PARAM = ERROR_CODE_PARAM_INVALID;
constexpr int32_t EXPECTED_NULL_POINTER = 0;
constexpr int32_t EXPECTED_BAD_PARAMETER = OH_NATIVEXCOMPONENT_RESULT_BAD_PARAMETER;

void ExpectStackNodeResults(const std::array<int32_t, SLOT_COUNT>& results)
{
    // Entries going through CheckValidXComponentNode: a stack object is not in the
    // node set, so they return 401.
    for (size_t i = FIRST_VALIDATED_SLOT; i <= LAST_VALIDATED_SLOT; i++) {
        EXPECT_EQ(results[i], EXPECTED_INVALID_PARAM) << "slot " << i;
    }
    // Pointer-returning entries: the modifier is null, so they return nullptr.
    EXPECT_EQ(results[SLOT_ACCESSIBILITY_PROVIDER_CREATE], EXPECTED_NULL_POINTER);
    EXPECT_EQ(results[SLOT_SURFACE_HOLDER_CREATE], EXPECTED_NULL_POINTER);
    EXPECT_EQ(results[SLOT_GET_NATIVE_XCOMPONENT], EXPECTED_NULL_POINTER);
    // Attach/Detach: the controlled sample has a null uiNodeHandle, so the null
    // parameter path returns BAD_PARAMETER.
    EXPECT_EQ(results[SLOT_ATTACH_NATIVE_ROOT_NODE], EXPECTED_BAD_PARAMETER);
    EXPECT_EQ(results[SLOT_DETACH_NATIVE_ROOT_NODE], EXPECTED_BAD_PARAMETER);
}
} // namespace

/**
 * @tc.name: XComponentUafGuard001
 * @tc.desc: Controlled disposed samples hit the entry guard on all 15 listed APIs;
 *           LOG mode keeps the same return values as DISABLED and never pollutes
 *           the error message channel.
 * @tc.type: FUNC
 */
HWTEST_F(NativeXComponentUafTest, XComponentUafGuard001, TestSize.Level1)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    // Use a still-alive local object with an invalid magic as the controlled disposed
    // sample: the memory of this access is readable and the hit is stable.
    ArkUI_Node node;
    node.type = ARKUI_NODE_XCOMPONENT;
    node.cNode = true;
    node.uiNodeHandle = nullptr;
    node.magic = ARKUI_NODE_MAGIC_INVALID;

    ASSERT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED)));
    const auto disabledResults = CallAllXComponentApis(&node);
    ExpectStackNodeResults(disabledResults);

    ASSERT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG)));
    const auto logResults = CallAllXComponentApis(&node);
    // LOG only diagnoses and never short-circuits: the return values of all 15 entries
    // are identical to DISABLED.
    for (size_t i = 0; i < logResults.size(); i++) {
        EXPECT_EQ(logResults[i], disabledResults[i]) << "slot " << i;
    }
    // The error message query channel does not carry disposed content from this check.
    const char* errorMessage = OH_ArkUI_NativeModule_GetErrorMessage();
    if (errorMessage != nullptr) {
        EXPECT_EQ(std::string(errorMessage).find("has been disposed"), std::string::npos);
    }
    RestoreRuntimeCheckMode();
}

/**
 * @tc.name: XComponentUafGuard002
 * @tc.desc: Valid magic never triggers the guard: LOG/DISABLED/CRASH modes keep
 *           identical return values on all 15 listed APIs for a valid handle.
 * @tc.type: FUNC
 */
HWTEST_F(NativeXComponentUafTest, XComponentUafGuard002, TestSize.Level1)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    ArkUI_Node node;
    node.type = ARKUI_NODE_XCOMPONENT;
    node.cNode = true;
    node.uiNodeHandle = nullptr;
    node.magic = ARKUI_NODE_MAGIC_VALID;

    ASSERT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG)));
    const auto logResults = CallAllXComponentApis(&node);
    ExpectStackNodeResults(logResults);

    ASSERT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_DISABLED)));
    const auto disabledResults = CallAllXComponentApis(&node);

    // A valid handle does not trigger the check in CRASH mode either (no termination).
    ASSERT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_CRASH)));
    const auto crashResults = CallAllXComponentApis(&node);

    for (size_t i = 0; i < logResults.size(); i++) {
        EXPECT_EQ(disabledResults[i], logResults[i]) << "slot " << i;
        EXPECT_EQ(crashResults[i], logResults[i]) << "slot " << i;
    }
    RestoreRuntimeCheckMode();
}

/**
 * @tc.name: XComponentUafGuard003
 * @tc.desc: Null inputs keep the existing parameter-error contracts on all 15
 *           listed APIs; the entry guard is null-safe and stays silent.
 * @tc.type: FUNC
 */
HWTEST_F(NativeXComponentUafTest, XComponentUafGuard003, TestSize.Level1)
{
    ASSERT_TRUE(NodeModel::InitialFullImpl());
    ASSERT_TRUE(NodeModel::ConfigManager::SetRuntimeCheckMode(
        RUNTIME_CHECK_TYPE_NODE_DISPOSED_VALUE, static_cast<int32_t>(OH_ARKUI_NATIVEMODULE_CHECK_MODE_LOG)));
    // The guard macro returns silently for a null pointer, and the existing validation
    // keeps the original contracts (401/nullptr/BAD_PARAMETER) for null parameters.
    const auto nullResults = CallAllXComponentApis(nullptr);
    for (size_t i = FIRST_VALIDATED_SLOT; i <= LAST_VALIDATED_SLOT; i++) {
        EXPECT_EQ(nullResults[i], EXPECTED_INVALID_PARAM) << "slot " << i;
    }
    EXPECT_EQ(nullResults[SLOT_ACCESSIBILITY_PROVIDER_CREATE], EXPECTED_NULL_POINTER);
    EXPECT_EQ(nullResults[SLOT_SURFACE_HOLDER_CREATE], EXPECTED_NULL_POINTER);
    EXPECT_EQ(nullResults[SLOT_GET_NATIVE_XCOMPONENT], EXPECTED_NULL_POINTER);
    EXPECT_EQ(nullResults[SLOT_ATTACH_NATIVE_ROOT_NODE], EXPECTED_BAD_PARAMETER);
    EXPECT_EQ(nullResults[SLOT_DETACH_NATIVE_ROOT_NODE], EXPECTED_BAD_PARAMETER);

    // When the component is null, the existing null validation of Attach/Detach takes
    // effect before the entry guard.
    ArkUI_Node node;
    node.type = ARKUI_NODE_XCOMPONENT;
    node.cNode = true;
    node.uiNodeHandle = nullptr;
    node.magic = ARKUI_NODE_MAGIC_VALID;
    EXPECT_EQ(OH_NativeXComponent_AttachNativeRootNode(nullptr, &node), EXPECTED_BAD_PARAMETER);
    EXPECT_EQ(OH_NativeXComponent_DetachNativeRootNode(nullptr, &node), EXPECTED_BAD_PARAMETER);
    RestoreRuntimeCheckMode();
}
} // namespace OHOS::Ace
