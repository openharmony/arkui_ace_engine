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

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_custom_env_view_white_list.h"
#include "gtest/gtest.h"
#include "napi/napi_runtime.cpp"
#include "native_interface.h"
#include "native_node_napi.h"
#include "native_type.h"
#include "node_model.h"
#include "node_model_safely.h"

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
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition2);
    auto ret2 = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_EQ(ret2->value[2].i32, 0);
    EXPECT_EQ(ret2->value[3].i32, 3);
    nodeAPI->resetAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    value[2].i32 = 9;
    ArkUI_AttributeItem backgroundImagePosition3 = { .value = value, .size = 3 };
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition3);
    auto ret3 = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_EQ(ret3->value[2].i32, 0);
    EXPECT_EQ(ret3->value[3].i32, 3);
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
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition2);
    auto ret2 = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_EQ(ret2->value[2].i32, 0);
    EXPECT_EQ(ret2->value[3].i32, 3);
    nodeAPI->resetAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    value[3].i32 = 2;
    ArkUI_AttributeItem backgroundImagePosition3 = { .value = value, .size = 4 };
    nodeAPI->setAttribute(row, NODE_BACKGROUND_IMAGE_POSITION, &backgroundImagePosition3);
    auto ret3 = nodeAPI->getAttribute(row, NODE_BACKGROUND_IMAGE_POSITION);
    EXPECT_EQ(ret3->value[2].i32, 0);
    EXPECT_EQ(ret3->value[3].i32, 3);
}