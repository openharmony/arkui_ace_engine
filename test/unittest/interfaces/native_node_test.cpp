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

#include <cstdint>
#include "gtest/gtest.h"
#include "native_interface.h"
#include "native_node.h"
#include "native_type.h"
#include "event_converter.h"

using namespace testing;
using namespace testing::ext;

class NativeNodeTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: NativeNodeTest001
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetEventType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest001, TestSize.Level1)
{
    ArkUI_NodeEvent event = { 0, -1 };
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(&event);
    EXPECT_EQ(eventType, ArkUI_NodeEventType::NODE_TOUCH_EVENT);
}

/**
 * @tc.name: NativeNodeTest002
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetEventType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest002, TestSize.Level1)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(nullptr);
    EXPECT_EQ(eventType, ArkUI_NodeEventType::NODE_TOUCH_EVENT);
}

/**
 * @tc.name: NativeNodeTest003
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetTargetId function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest003, TestSize.Level1)
{
    auto targetId = OH_ArkUI_NodeEvent_GetTargetId(nullptr);
    EXPECT_EQ(targetId, -1);
}

/**
 * @tc.name: NativeNodeTest004
 * @tc.desc: Test OH_ArkUI_NodeEvent_GetNodeHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest004, TestSize.Level1)
{
    auto handle = OH_ArkUI_NodeEvent_GetNodeHandle(nullptr);
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: NativeNodeTest005
 * @tc.desc: Test customNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest005, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    auto childNode = nodeAPI->createNode(ARKUI_NODE_STACK);
    ASSERT_NE(rootNode, nullptr);
    int32_t ret1 = nodeAPI->addChild(rootNode, childNode);
    EXPECT_EQ(ret1, ARKUI_ERROR_CODE_NO_ERROR);
    float size = 100.0f;
    float padding = 100.0f;
    float val0 = 0.0f;
    float val1 = 1.0f;
    float val10 = 10.0f;
    float val05 = 0.5f;
    uint32_t color = 0xFFFF0000;

    ArkUI_NumberValue value[] = {{.f32 = size}};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    nodeAPI->setAttribute(rootNode, NODE_WIDTH, &item);
    auto widthVal = nodeAPI->getAttribute(rootNode, NODE_WIDTH);
    EXPECT_EQ(widthVal->value[0].f32, size);

    nodeAPI->setAttribute(rootNode, NODE_HEIGHT, &item);
    auto heightVal = nodeAPI->getAttribute(rootNode, NODE_HEIGHT);
    EXPECT_EQ(heightVal->value[0].f32, size);

    value[0].u32 = color;
    nodeAPI->setAttribute(rootNode, NODE_BACKGROUND_COLOR, &item);
    auto colorVal = nodeAPI->getAttribute(rootNode, NODE_BACKGROUND_COLOR);
    EXPECT_EQ(colorVal->value[0].u32, color);

    value[0].f32 = padding;
    nodeAPI->setAttribute(rootNode, NODE_PADDING, &item);
    auto paddingVal = nodeAPI->getAttribute(rootNode, NODE_PADDING);
    EXPECT_EQ(paddingVal->value[0].f32, padding);

    nodeAPI->setAttribute(rootNode, NODE_MARGIN, &item);
    auto marginVal = nodeAPI->getAttribute(rootNode, NODE_MARGIN);
    EXPECT_EQ(marginVal->value[0].f32, padding);

    item.string = "test";
    ret1 = nodeAPI->setAttribute(rootNode, NODE_ID, &item);
    EXPECT_EQ(ret1, 0);

    value[0].i32 = true;
    nodeAPI->setAttribute(rootNode, NODE_ENABLED, &item);
    auto enableVal = nodeAPI->getAttribute(rootNode, NODE_ENABLED);
    EXPECT_EQ(enableVal->value[0].i32, 1);

    value[0].f32 = val0;
    nodeAPI->setAttribute(rootNode, NODE_BLUR, &item);
    auto blurVal = nodeAPI->getAttribute(rootNode, NODE_BLUR);
    EXPECT_EQ(blurVal->value[0].f32, val0);

    value[0].f32 = val0;
    nodeAPI->setAttribute(rootNode, NODE_SATURATION, &item);
    auto saturationVal = nodeAPI->getAttribute(rootNode, NODE_SATURATION);
    EXPECT_EQ(saturationVal->value[0].f32, val0);

    value[0].f32 = val0;
    nodeAPI->setAttribute(rootNode, NODE_BRIGHTNESS, &item);
    auto brightnessVal = nodeAPI->getAttribute(rootNode, NODE_BRIGHTNESS);
    EXPECT_EQ(brightnessVal->value[0].f32, val0);

    value[0].i32 = ARKUI_ALIGNMENT_CENTER;
    nodeAPI->setAttribute(rootNode, NODE_ALIGNMENT, &item);
    auto alignVal = nodeAPI->getAttribute(rootNode, NODE_ALIGNMENT);
    EXPECT_EQ(alignVal->value[0].i32, static_cast<int32_t>(ARKUI_ALIGNMENT_CENTER));

    value[0].f32 = val0;
    nodeAPI->setAttribute(rootNode, NODE_OPACITY, &item);
    auto opacityVal = nodeAPI->getAttribute(rootNode, NODE_OPACITY);
    EXPECT_EQ(opacityVal->value[0].f32, val0);

    value[0].f32 = val10;
    nodeAPI->setAttribute(rootNode, NODE_BORDER_WIDTH, &item);
    auto borderWidthVal = nodeAPI->getAttribute(rootNode, NODE_BORDER_WIDTH);
    EXPECT_EQ(borderWidthVal->value[0].f32, val10);

    value[0].f32 = val10;
    nodeAPI->setAttribute(rootNode, NODE_BORDER_RADIUS, &item);
    auto borderRadiusVal = nodeAPI->getAttribute(rootNode, NODE_BORDER_RADIUS);
    EXPECT_EQ(borderRadiusVal->value[0].f32, val10);

    value[0].u32 = color;
    nodeAPI->setAttribute(rootNode, NODE_BORDER_COLOR, &item);
    auto borderColorVal = nodeAPI->getAttribute(rootNode, NODE_BORDER_COLOR);
    EXPECT_EQ(borderColorVal->value[0].u32, color);

    value[0].i32 = ARKUI_BORDER_STYLE_SOLID;
    nodeAPI->setAttribute(rootNode, NODE_BORDER_STYLE, &item);
    auto borderStyleVal = nodeAPI->getAttribute(rootNode, NODE_BORDER_STYLE);
    EXPECT_EQ(borderStyleVal->value[0].i32, static_cast<int32_t>(ARKUI_BORDER_STYLE_SOLID));

    value[0].f32 = val1;
    nodeAPI->setAttribute(rootNode, NODE_Z_INDEX, &item);
    auto zIndexVal = nodeAPI->getAttribute(rootNode, NODE_Z_INDEX);
    EXPECT_EQ(zIndexVal->value[0].f32, val1);

    value[0].i32 = ARKUI_VISIBILITY_VISIBLE;
    nodeAPI->setAttribute(rootNode, NODE_VISIBILITY, &item);
    auto visibilityVal = nodeAPI->getAttribute(rootNode, NODE_VISIBILITY);
    EXPECT_EQ(visibilityVal->value[0].i32, static_cast<int32_t>(ARKUI_VISIBILITY_VISIBLE));

    value[0].i32 = true;
    nodeAPI->setAttribute(rootNode, NODE_CLIP, &item);
    auto clipVal = nodeAPI->getAttribute(rootNode, NODE_CLIP);
    EXPECT_EQ(clipVal->value[0].i32, true);

    value[0].i32 = ARKUI_HIT_TEST_MODE_DEFAULT;
    nodeAPI->setAttribute(rootNode, NODE_HIT_TEST_BEHAVIOR, &item);
    auto hitVal = nodeAPI->getAttribute(rootNode, NODE_HIT_TEST_BEHAVIOR);
    EXPECT_EQ(hitVal->value[0].i32, static_cast<int32_t>(ARKUI_HIT_TEST_MODE_DEFAULT));

    value[0].i32 = ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD;
    nodeAPI->setAttribute(rootNode, NODE_SHADOW, &item);
    auto shadowVal = nodeAPI->getAttribute(rootNode, NODE_SHADOW);
    EXPECT_EQ(shadowVal->value[0].i32, static_cast<int32_t>(ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD));

    value[0].i32 = ARKUI_IMAGE_SIZE_COVER;
    nodeAPI->setAttribute(rootNode, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE, &item);
    auto imagesizeVal = nodeAPI->getAttribute(rootNode, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE);
    EXPECT_EQ(imagesizeVal->value[0].i32, static_cast<int32_t>(ARKUI_IMAGE_SIZE_COVER));

    value[0].i32 = true;
    nodeAPI->setAttribute(rootNode, NODE_FOCUSABLE, &item);
    auto focusableVal = nodeAPI->getAttribute(rootNode, NODE_FOCUSABLE);
    EXPECT_EQ(focusableVal->value[0].i32, true);

    value[0].i32 = true;
    nodeAPI->setAttribute(rootNode, NODE_DEFAULT_FOCUS, &item);
    auto defaultFocusVal = nodeAPI->getAttribute(rootNode, NODE_DEFAULT_FOCUS);
    EXPECT_EQ(defaultFocusVal->value[0].i32, true);

    value[0].i32 = ARKUI_DIRECTION_LTR;
    nodeAPI->setAttribute(rootNode, NODE_DIRECTION, &item);
    auto directionVal = nodeAPI->getAttribute(rootNode, NODE_DIRECTION);
    EXPECT_EQ(directionVal->value[0].i32, static_cast<int32_t>(ARKUI_DIRECTION_LTR));

    value[0].f32 = val05;
    nodeAPI->setAttribute(rootNode, NODE_GRAY_SCALE, &item);
    auto grayScaleVal = nodeAPI->getAttribute(rootNode, NODE_GRAY_SCALE);
    EXPECT_EQ(grayScaleVal->value[0].f32, val05);

    value[0].f32 = val05;
    nodeAPI->setAttribute(rootNode, NODE_INVERT, &item);
    auto invertVal = nodeAPI->getAttribute(rootNode, NODE_INVERT);
    EXPECT_EQ(invertVal->value[0].f32, val05);

    value[0].f32 = val05;
    nodeAPI->setAttribute(rootNode, NODE_SEPIA, &item);
    auto sepiaVal = nodeAPI->getAttribute(rootNode, NODE_SEPIA);
    EXPECT_EQ(sepiaVal->value[0].f32, val05);

    value[0].f32 = val05;
    nodeAPI->setAttribute(rootNode, NODE_CONTRAST, &item);
    auto contrastVal = nodeAPI->getAttribute(rootNode, NODE_CONTRAST);
    EXPECT_EQ(contrastVal->value[0].f32, val05);

    value[0].i32 = ARKUI_ALIGNMENT_CENTER;
    nodeAPI->setAttribute(rootNode, NODE_STACK_ALIGN_CONTENT, &item);
    auto stackAlignVal = nodeAPI->getAttribute(rootNode, NODE_STACK_ALIGN_CONTENT);
    EXPECT_EQ(stackAlignVal->value[0].i32, static_cast<int32_t>(ARKUI_ALIGNMENT_CENTER));

    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_HEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PADDING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MARGIN), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ID), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ENABLED), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TRANSLATE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCALE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ROTATE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BRIGHTNESS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SATURATION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BLUR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_LINEAR_GRADIENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ALIGNMENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_OPACITY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_RADIUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_Z_INDEX), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_VISIBILITY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CLIP), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CLIP_SHAPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TRANSFORM), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_HIT_TEST_BEHAVIOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_POSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SHADOW), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CUSTOM_SHADOW), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_IMAGE_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_IMAGE_SIZE_WITH_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_BLUR_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TRANSFORM_CENTER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_OPACITY_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ROTATE_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SCALE_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TRANSLATE_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MOVE_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FOCUSABLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_DEFAULT_FOCUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_RESPONSE_REGION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_OVERLAY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SWEEP_GRADIENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_RADIAL_GRADIENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MASK), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BLEND_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_DIRECTION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CONSTRAINT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_GRAY_SCALE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_INVERT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SEPIA), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CONTRAST), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FOREGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_OFFSET), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MARK_ANCHOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_IMAGE_POSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ALIGN_RULES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ALIGN_SELF), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FLEX_GROW), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FLEX_SHRINK), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FLEX_BASIS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_GROUP), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_TEXT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_DESCRIPTION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FOCUS_STATUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ASPECT_RATIO), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_LAYOUT_WEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_DISPLAY_PRIORITY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_OUTLINE_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_WIDTH_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_HEIGHT_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PADDING_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MARGIN_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_GEOMETRY_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_RELATIVE_LAYOUT_CHAIN_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_RENDER_FIT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_OUTLINE_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_RENDER_GROUP), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_COLOR_BLEND), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FOREGROUND_BLUR_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_LAYOUT_RECT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FOCUS_ON_TOUCH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_WIDTH_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_RADIUS_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_ID), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_ACTIONS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_ROLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_STATE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_ACCESSIBILITY_VALUE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_EXPAND_SAFE_AREA), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_VISIBLE_AREA_CHANGE_RATIO), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TRANSITION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_NE(nodeAPI->getAttribute(rootNode, NODE_UNIQUE_ID), nullptr);
}

/**
 * @tc.name: NativeNodeTest006
 * @tc.desc: Test ConvertOriginEventType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest006, TestSize.Level1)
{
    int32_t ret;
    int32_t nodeType = static_cast<int32_t>(ARKUI_NODE_TEXT_INPUT);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_SUBMIT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_SUBMIT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_CUT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_CUT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_PASTE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_PASTE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_TEXT_SELECTION_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_EDIT_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_EDIT_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_CONTENT_SIZE_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_CONTENT_SIZE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_INPUT_FILTER_ERROR));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_CONTENT_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_CONTENT_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_WILL_INSERT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_WILL_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_DID_INSERT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_DID_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_WILL_DELETE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_WILL_DELETE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_INPUT_ON_DID_DELETE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_INPUT_DID_DELETE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_SCROLL);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_FRAME_BEGIN));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_WILL_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_WILL_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_DID_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_STOP, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_STOP));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_EDGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_EDGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_REACH_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_REACH_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_REACH_END, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SCROLL_REACH_END));

    nodeType = static_cast<int32_t>(ARKUI_NODE_LIST);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_SCROLL_FRAME_BEGIN));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_SCROLL_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_STOP, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_SCROLL_STOP));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_REACH_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_REACH_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_REACH_END, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_REACH_END));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_LIST_ON_SCROLL_INDEX, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_SCROLL_INDEX));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_LIST_ON_DID_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_LIST_ON_WILL_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_LIST_WILL_SCROLL));
    
    nodeType = static_cast<int32_t>(ARKUI_NODE_WATER_FLOW);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_SCROLL_FRAME_BEGIN));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_SCROLL_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_SCROLL_STOP, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_SCROLL_STOP));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_WILL_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_WILL_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_REACH_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_REACH_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SCROLL_EVENT_ON_REACH_END, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_REACH_END));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_WATER_FLOW_ON_DID_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_WATER_FLOW_ON_SCROLL_INDEX, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_WATER_FLOW_SCROLL_INDEX));

    nodeType = static_cast<int32_t>(ARKUI_NODE_STACK);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_EVENT_ON_APPEAR, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_APPEAR));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_EVENT_ON_DISAPPEAR, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DISAPPEAR));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_EVENT_ON_AREA_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_AREA_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_FOCUS, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_FOCUS));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_BLUR, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_BLUR));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TOUCH_EVENT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TOUCH));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_CLICK, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_CLICK));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_TOUCH_INTERCEPT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TOUCH_INTERCEPT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_EVENT_ON_VISIBLE_AREA_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_VISIBLE_AREA_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_HOVER, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_HOVER));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_MOUSE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_MOUSE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_EVENT_ON_ATTACH, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_ATTACH));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_EVENT_ON_DETACH, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DETACH));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_ON_ACCESSIBILITY_ACTIONS, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_ACCESSIBILITY_ACTIONS));

    nodeType = static_cast<int32_t>(ARKUI_NODE_TEXT_AREA);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXTAREA_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_AREA_INPUT_FILTER_ERROR));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_EDIT_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXTAREA_EDIT_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_SUBMIT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXTAREA_ON_SUBMIT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_CONTENT_SIZE_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXTAREA_CONTENT_SIZE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_PASTE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXTAREA_PASTE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXTAREA_TEXT_SELECTION_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_CONTENT_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_AREA_CONTENT_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_WILL_INSERT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_AREA_WILL_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_DID_INSERT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_AREA_DID_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_WILL_DELETE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_AREA_WILL_DELETE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_AREA_ON_DID_DELETE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_AREA_DID_DELETE));


    nodeType = static_cast<int32_t>(ARKUI_NODE_REFRESH);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_REFRESH_STATE_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_REFRESH_STATE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_REFRESH_ON_REFRESH, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_REFRESH_REFRESHING));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_REFRESH_ON_OFFSET_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_REFRESH_ON_OFFSET_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_TOGGLE);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TOGGLE_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TOGGLE_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_IMAGE);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ON_COMPLETE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_COMPLETE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ON_ERROR, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_ERROR));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ON_SVG_PLAY_FINISH, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_SVG_PLAY_FINISH));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ON_DOWNLOAD_PROGRESS, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_DOWNLOAD_PROGRESS));

    nodeType = static_cast<int32_t>(ARKUI_NODE_DATE_PICKER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DATE_PICKER_DATE_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_TIME_PICKER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TIME_PICKER_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TIME_PICKER_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_TEXT_PICKER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_PICKER_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_TEXT_PICKER_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_CALENDAR_PICKER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_CALENDAR_PICKER_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_CALENDAR_PICKER_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_CHECKBOX);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_CHECKBOX_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_CHECKBOX_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_SLIDER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SLIDER_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SLIDER_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_SWIPER);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SWIPER_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SWIPER_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SWIPER_EVENT_ON_ANIMATION_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SWIPER_ANIMATION_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SWIPER_EVENT_ON_ANIMATION_END, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SWIPER_ANIMATION_END));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SWIPER_EVENT_ON_GESTURE_SWIPE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SWIPER_GESTURE_SWIPE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_SWIPER_DID_CONTENT_SCROLL));

    nodeType = static_cast<int32_t>(ARKUI_NODE_TEXT);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_TEXT_ON_DETECT_RESULT_UPDATE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_DETECT_RESULT_UPDATE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_RADIO);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_RADIO_EVENT_ON_CHANGE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_RADIO_CHANGE));

    nodeType = static_cast<int32_t>(ARKUI_NODE_IMAGE_ANIMATOR);
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ANIMATOR_EVENT_ON_START, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_ANIMATOR_ON_START));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_ANIMATOR_ON_CANCEL));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_ANIMATOR_ON_PAUSE));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_ANIMATOR_ON_REPEAT));
    ret = OHOS::Ace::NodeModel::ConvertOriginEventType(NODE_IMAGE_ANIMATOR_EVENT_ON_FINISH, nodeType);
    EXPECT_EQ(ret, static_cast<int32_t>(ON_IMAGE_ANIMATOR_ON_FINISH));
}

/**
 * @tc.name: NativeNodeTest007
 * @tc.desc: Test ConvertToNodeEventType function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest007, TestSize.Level1)
{
    int32_t ret;
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_SUBMIT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_SUBMIT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_CUT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_CUT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_PASTE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_PASTE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_TEXT_SELECTION_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_TEXT_SELECTION_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_EDIT_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_EDIT_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_CONTENT_SIZE_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_CONTENT_SIZE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_INPUT_FILTER_ERROR);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_INPUT_FILTER_ERROR));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_CONTENT_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_CONTENT_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_WILL_INSERT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_WILL_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_DID_INSERT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_DID_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_WILL_DELETE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_WILL_DELETE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_INPUT_DID_DELETE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_INPUT_ON_DID_DELETE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_FRAME_BEGIN);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_WILL_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_WILL_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_DID_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_STOP);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_STOP));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_EDGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_EDGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_REACH_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_REACH_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SCROLL_REACH_END);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_REACH_END));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_SCROLL_FRAME_BEGIN);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_SCROLL_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_SCROLL_STOP);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_STOP));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_REACH_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_REACH_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_REACH_END);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_REACH_END));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_SCROLL_INDEX);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_LIST_ON_SCROLL_INDEX));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_DID_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_LIST_ON_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_LIST_WILL_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_LIST_ON_WILL_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_SCROLL_FRAME_BEGIN);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_SCROLL_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_SCROLL_STOP);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_SCROLL_STOP));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_WILL_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_WILL_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_REACH_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_REACH_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_REACH_END);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SCROLL_EVENT_ON_REACH_END));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_DID_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_WATER_FLOW_ON_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_WATER_FLOW_SCROLL_INDEX);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_WATER_FLOW_ON_SCROLL_INDEX));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_APPEAR);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_EVENT_ON_APPEAR));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DISAPPEAR);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_EVENT_ON_DISAPPEAR));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_AREA_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_EVENT_ON_AREA_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_FOCUS);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_FOCUS));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_BLUR);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_BLUR));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TOUCH);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TOUCH_EVENT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_CLICK);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_CLICK));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TOUCH_INTERCEPT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_TOUCH_INTERCEPT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_VISIBLE_AREA_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_EVENT_ON_VISIBLE_AREA_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_HOVER);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_HOVER));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_MOUSE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_MOUSE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_ATTACH);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_EVENT_ON_ATTACH));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DETACH);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_EVENT_ON_DETACH));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_ACCESSIBILITY_ACTIONS);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_ON_ACCESSIBILITY_ACTIONS));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXTAREA_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_AREA_INPUT_FILTER_ERROR);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_INPUT_FILTER_ERROR));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXTAREA_EDIT_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_EDIT_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXTAREA_ON_SUBMIT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_SUBMIT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXTAREA_CONTENT_SIZE_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_CONTENT_SIZE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXTAREA_PASTE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_PASTE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXTAREA_TEXT_SELECTION_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_TEXT_SELECTION_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_AREA_CONTENT_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_CONTENT_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_AREA_WILL_INSERT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_WILL_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_AREA_DID_INSERT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_DID_INSERT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_AREA_WILL_DELETE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_WILL_DELETE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_AREA_DID_DELETE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_AREA_ON_DID_DELETE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_REFRESH_STATE_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_REFRESH_STATE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_REFRESH_REFRESHING);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_REFRESH_ON_REFRESH));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_REFRESH_ON_OFFSET_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_REFRESH_ON_OFFSET_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TOGGLE_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TOGGLE_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_COMPLETE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ON_COMPLETE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_ERROR);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ON_ERROR));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_SVG_PLAY_FINISH);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ON_SVG_PLAY_FINISH));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_DOWNLOAD_PROGRESS);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ON_DOWNLOAD_PROGRESS));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DATE_PICKER_DATE_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TIME_PICKER_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TIME_PICKER_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_TEXT_PICKER_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_PICKER_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_CALENDAR_PICKER_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_CALENDAR_PICKER_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_CHECKBOX_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_CHECKBOX_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SLIDER_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SLIDER_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SWIPER_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SWIPER_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SWIPER_ANIMATION_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SWIPER_EVENT_ON_ANIMATION_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SWIPER_ANIMATION_END);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SWIPER_EVENT_ON_ANIMATION_END));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SWIPER_GESTURE_SWIPE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SWIPER_EVENT_ON_GESTURE_SWIPE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_SWIPER_DID_CONTENT_SCROLL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_SWIPER_EVENT_ON_CONTENT_DID_SCROLL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_DETECT_RESULT_UPDATE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_TEXT_ON_DETECT_RESULT_UPDATE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_RADIO_CHANGE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_RADIO_EVENT_ON_CHANGE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_ANIMATOR_ON_START);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ANIMATOR_EVENT_ON_START));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_ANIMATOR_ON_CANCEL);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_ANIMATOR_ON_PAUSE);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_ANIMATOR_ON_REPEAT);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT));
    ret = OHOS::Ace::NodeModel::ConvertToNodeEventType(ON_IMAGE_ANIMATOR_ON_FINISH);
    EXPECT_EQ(ret, static_cast<int32_t>(NODE_IMAGE_ANIMATOR_EVENT_ON_FINISH));
}

/**
 * @tc.name: NativeNodeTest008
 * @tc.desc: Test textNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest008, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_TEXT);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_CONTENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_WEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LINE_HEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_DECORATION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_CASE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LETTER_SPACING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MAX_LINES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_ALIGN), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_OVERFLOW), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_FAMILY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_COPY_OPTION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_BASELINE_OFFSET), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_TEXT_SHADOW), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MIN_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MAX_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_FONT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_HEIGHT_ADAPTIVE_POLICY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INDENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_WORD_BREAK), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_ELLIPSIS_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LINE_SPACING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_FONT_FEATURE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_ENABLE_DATA_DETECTOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_ENABLE_DATA_DETECTOR_CONFIG), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_SELECTED_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_CONTENT_WITH_STYLED_STRING), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest009
 * @tc.desc: Test spanNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest009, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_SPAN);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SPAN_CONTENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SPAN_TEXT_BACKGROUND_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_SPAN_BASELINE_OFFSET), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_DECORATION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_WEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LINE_HEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_CASE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LETTER_SPACING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_FAMILY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_TEXT_SHADOW), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest010
 * @tc.desc: Test imageSpanNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest010, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_IMAGE_SPAN);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_SPAN_SRC), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_SPAN_VERTICAL_ALIGNMENT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_SPAN_ALT), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest011
 * @tc.desc: Test imageNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest011, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_IMAGE);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_SRC), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_OBJECT_FIT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_INTERPOLATION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_OBJECT_REPEAT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_COLOR_FILTER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_AUTO_RESIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_ALT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_DRAGGABLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_RENDER_MODE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_FIT_ORIGINAL_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_FILL_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_IMAGE_RESIZABLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_RADIUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_RADIUS_PERCENT), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest012
 * @tc.desc: Test toggleNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest012, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_TOGGLE);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TOGGLE_SELECTED_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TOGGLE_SWITCH_POINT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TOGGLE_VALUE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TOGGLE_UNSELECTED_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest013
 * @tc.desc: Test loadingProgressNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest013, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_LOADING_PROGRESS);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_LOADING_PROGRESS_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_LOADING_PROGRESS_ENABLE_LOADING), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest014
 * @tc.desc: Test textinputNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest014, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_TEXT_INPUT);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_PLACEHOLDER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_TEXT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CARET_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CARET_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_SHOW_UNDERLINE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_MAX_LENGTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_ENTER_KEY_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_PLACEHOLDER_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_PLACEHOLDER_FONT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_ENABLE_KEYBOARD_ON_FOCUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_SELECTED_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_SHOW_PASSWORD_ICON), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_EDITING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CANCEL_BUTTON), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_TEXT_SELECTION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_UNDERLINE_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_ENABLE_AUTO_FILL), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CONTENT_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_PASSWORD_RULES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_SELECT_ALL), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_INPUT_FILTER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CARET_OFFSET), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CONTENT_RECT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CONTENT_LINE_COUNT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_SELECTION_MENU_HIDDEN), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_BLUR_ON_SUBMIT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_CUSTOM_KEYBOARD), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_WORD_BREAK), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_SHOW_KEYBOARD_ON_FOCUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_INPUT_NUMBER_OF_LINES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PADDING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MARGIN), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_RADIUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_WEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_FAMILY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MIN_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MAX_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LINE_HEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MAX_LINES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_ALIGN), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest015
 * @tc.desc: Test textareaNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest015, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_TEXT_AREA);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_PLACEHOLDER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_TEXT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_MAX_LENGTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_PLACEHOLDER_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_PLACEHOLDER_FONT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_CARET_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_EDITING), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_SHOW_COUNTER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_SELECTION_MENU_HIDDEN), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_BLUR_ON_SUBMIT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_INPUT_FILTER), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_SELECTED_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_ENTER_KEY_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_ENABLE_KEYBOARD_ON_FOCUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_CARET_OFFSET), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_CONTENT_RECT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_CONTENT_LINE_COUNT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_TEXT_SELECTION), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_ENABLE_AUTO_FILL), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_CONTENT_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_SHOW_KEYBOARD_ON_FOCUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_AREA_NUMBER_OF_LINES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_MARGIN), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_WIDTH), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_RADIUS), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BORDER_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_STYLE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_WEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_FAMILY), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MIN_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MAX_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_LINE_HEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_MAX_LINES), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_TEXT_ALIGN), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest016
 * @tc.desc: Test buttonNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest016, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_BUTTON);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BUTTON_LABEL), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BUTTON_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_BACKGROUND_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_FONT_WEIGHT), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest017
 * @tc.desc: Test progressNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest017, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_PROGRESS);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PROGRESS_VALUE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PROGRESS_TOTAL), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PROGRESS_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_PROGRESS_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest018
 * @tc.desc: Test checkboxNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest018, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_CHECKBOX);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CHECKBOX_SELECT), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CHECKBOX_SELECT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CHECKBOX_UNSELECT_COLOR), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CHECKBOX_MARK), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_CHECKBOX_SHAPE), ARKUI_ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: NativeNodeTest019
 * @tc.desc: Test checkboxNode function.
 * @tc.type: FUNC
 */
HWTEST_F(NativeNodeTest, NativeNodeTest019, TestSize.Level1)
{
    auto nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    auto rootNode = nodeAPI->createNode(ARKUI_NODE_XCOMPONENT);
    ASSERT_NE(rootNode, nullptr);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_XCOMPONENT_ID), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_XCOMPONENT_TYPE), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(nodeAPI->resetAttribute(rootNode, NODE_XCOMPONENT_SURFACE_SIZE), ARKUI_ERROR_CODE_NO_ERROR);
}

