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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JS_UI_INDEX_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JS_UI_INDEX_H

namespace OHOS::Ace::Framework {

#define ARK_UI_KEY(FUNCTION)      \
    FUNCTION("action", ACTION)       \
    FUNCTION("align", ALIGN)       \
    FUNCTION("angle", ANGLE)       \
    FUNCTION("backgroundColor", BACKGROUND_COLOR)       \
    FUNCTION("backgroundBlurStyle", BACKGROUND_BLUR_STYLE)       \
    FUNCTION("borderRadius", BORDER_RADIUS)       \
    FUNCTION("bottom", BOTTOM)       \
    FUNCTION("bottomValue", BOTTOM_VALUE)       \
    FUNCTION("bundleName", BUNDLE_NAME)       \
    FUNCTION("builder", BUILDER)       \
    FUNCTION("center", CENTER)       \
    FUNCTION("centerX", CENTER_X)       \
    FUNCTION("centerY", CENTER_Y)       \
    FUNCTION("centerZ", CENTER_Z)       \
    FUNCTION("color", COLOR)       \
    FUNCTION("colors", COLORS)       \
    FUNCTION("colorValue", COLOR_VALUE)       \
    FUNCTION("direction", DIRECTION)       \
    FUNCTION("end", END)       \
    FUNCTION("endValue", END_VALUE)       \
    FUNCTION("enabled", ENABLED)       \
    FUNCTION("family", FAMILY)       \
    FUNCTION("fill", FILL)       \
    FUNCTION("height", HEIGHT)       \
    FUNCTION("icon", ICON)       \
    FUNCTION("id", ID)       \
    FUNCTION("itemHeightValue", ITEM_HEIGHT_VALUE)       \
    FUNCTION("itemWidthValue", ITEM_WIDTH_VALUE)       \
    FUNCTION("left", LEFT)       \
    FUNCTION("leftValue", LEFT_VALUE)       \
    FUNCTION("length", LENGTH)       \
    FUNCTION("matrix4x4", MATRIX4X4)       \
    FUNCTION("maskValue", MASK_VALUE)       \
    FUNCTION("moduleName", MODULE_NAME)       \
    FUNCTION("offsetX", OFFSET_X)       \
    FUNCTION("offsetY", OFFSET_Y)       \
    FUNCTION("params", PARAMS)       \
    FUNCTION("perspective", PERSPECTIVE)       \
    FUNCTION("radius", RADIUS)       \
    FUNCTION("repeat", REPEAT)       \
    FUNCTION("repeating", REPEATING)       \
    FUNCTION("right", RIGHT)       \
    FUNCTION("rightValue", RIGHT_VALUE)       \
    FUNCTION("rotation", ROTATION)       \
    FUNCTION("selectedColorValue", SELECTED_COLOR_VALUE)       \
    FUNCTION("selectedItemHeightValue", SELECTED_ITEM_HEIGHT_VALUE)       \
    FUNCTION("selectedItemWidthValue", SELECTED_ITEM_WIDTH_VALUE)       \
    FUNCTION("maxDisplayCountValue", MAX_DISPLAY_COUNT_VALUE)       \
    FUNCTION("size", SIZE)       \
    FUNCTION("slice", SLICE)       \
    FUNCTION("source", SOURCE)       \
    FUNCTION("start", START)       \
    FUNCTION("startValue", START_VALUE)       \
    FUNCTION("style", STYLE)       \
    FUNCTION("symbolIcon", SYMBOL_ICON)       \
    FUNCTION("top", TOP)       \
    FUNCTION("topValue", TOP_VALUE)       \
    FUNCTION("topStart", TOP_START)       \
    FUNCTION("topEnd", TOP_END)       \
    FUNCTION("bottomStart", BOTTOM_START)       \
    FUNCTION("bottomEnd", BOTTOM_END)       \
    FUNCTION("type", TYPE)       \
    FUNCTION("unit", UNIT)       \
    FUNCTION("value", VALUE)       \
    FUNCTION("weight", WEIGHT)       \
    FUNCTION("width", WIDTH)       \
    FUNCTION("x", X)       \
    FUNCTION("y", Y)       \
    FUNCTION("z", Z)       \
    FUNCTION("spaceValue", SPACE_VALUE)       \
    FUNCTION("ignoreSizeValue", IGNORE_SIZE_VALUE)       \
    FUNCTION("setIgnoreSizeValue", SET_IGNORE_SIZE_VALUE)

#define PROPERTY_NAME_INDEX(propertyName, index) index,
enum class ArkUIIndex : uint32_t {
    ARK_UI_KEY(PROPERTY_NAME_INDEX)
};
#undef PROPERTY_NAME_INDEX
} // namespace OHOS::Ace::Framework
#endif  // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_JS_UI_INDEX_H
