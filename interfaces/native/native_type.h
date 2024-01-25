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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief 提供ArkUI在Native侧的UI能力，如UI组件创建销毁、树节点操作，属性设置，事件监听等。
 *
 * @since 12
 */

/**
 * @file native_type.h
 *
 * @brief 提供NativeModule公共的类型定义。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_TYPE_H
#define ARKUI_NATIVE_TYPE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 提供ArkUI native组件实例对象定义。
 *
 * @since 12
 */
struct ArkUI_Node;

/**
 * @brief 定义ArkUI native组件实例对象指针定义。
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief ArkUI在native侧的数字类型定义。
 *
 * @since 12
 */
typedef union {
    /** 浮点类型。*/
    float f32;
    /** 有符号整型。*/
    int32_t i32;
    /** 无符号整型。*/
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief 定义布局对齐枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 顶部起始。 */
    ARKUI_ALIGNMENT_TOP_START = 0,
    /** 顶部居中。*/
    ARKUI_ALIGNMENT_TOP,
    /** 顶部尾端。*/
    ARKUI_ALIGNMENT_TOP_END,
    /** 起始端纵向居中。*/
    ARKUI_ALIGNMENT_START,
    /** 横向和纵向居中。*/
    ARKUI_ALIGNMENT_CENTER,
    /** 尾端纵向居中。*/
    ARKUI_ALIGNMENT_END,
    /** 底部起始端。*/
    ARKUI_ALIGNMENT_BOTTOM_START,
    /** 底部横向居中。*/
    ARKUI_ALIGNMENT_BOTTOM,
    /** 底部尾端。*/
    ARKUI_ALIGNMENT_BOTTOM_END,
} ArkUI_Alignment;

/**
 * @brief 定义图片重复铺设枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 不重复。 */
    ARKUI_IMAGEREPEAT_NO_REPEAT = 0,
    /** 在X轴方向重复。 */
    ARKUI_IMAGEREPEAT_X,
    /** 在Y轴方向重复。 */
    ARKUI_IMAGEREPEAT_Y,
    /** 在X轴和Y轴方向重复。 */
    ARKUI_IMAGEREPEAT_XY,
} ArkUI_ImageRepeat;

/**
 * @brief 定义字体样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 标准字体样式。 */
    ARKUI_FONT_STYLE_NORMAL = 0,
    /** 斜体字体样式。 */
    ARKUI_FONT_STYLE_ITALIC
} ArkUI_FontStyle;

/**
 * @brief 定义字体粗细/字重枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 100 */
    ARKUI_FONT_WEIGHT_W100 = 0,
    /** 200 */
    ARKUI_FONT_WEIGHT_W200,
    /** 300 */
    ARKUI_FONT_WEIGHT_W300,
    /** 400 */
    ARKUI_FONT_WEIGHT_W400,
    /** 500 */
    ARKUI_FONT_WEIGHT_W500,
    /** 600 */
    ARKUI_FONT_WEIGHT_W600,
    /** 700 */
    ARKUI_FONT_WEIGHT_W700,
    /** 800 */
    ARKUI_FONT_WEIGHT_W800,
    /** 900 */
    ARKUI_FONT_WEIGHT_W900,
    /** 字体较粗。 */
    ARKUI_FONT_WEIGHT_BOLD,
    /** 字体粗细正常 */
    ARKUI_FONT_WEIGHT_NORMAL,
    /** 字体非常粗。 */
    ARKUI_FONT_WEIGHT_BOLDER,
    /** 字体较细。 */
    ARKUI_FONT_WEIGHT_LIGHTER,
    /** 字体粗细适中。 */
    ARKUI_FONT_WEIGHT_MEDIUM,
    /** 字体粗细正常 */
    ARKUI_FONT_WEIGHT_REGULAR,
} ArkUI_FontWeight;

/**
 * @brief 定义字体水平对齐样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 水平对齐首部。 */
    ARKUI_TEXT_ALIGN_START = 0,
    /** 水平居中对齐。 */
    ARKUI_TEXT_ALIGN_CENTER,
    /** 水平对齐尾部。 */
    ARKUI_TEXT_ALIGN_END,
    /** 双端对齐。 */
    ARKUI_TEXT_ALIGN_JUSTIFY,
} ArkUI_TextAlign;

/**
 * @brief 定义单行文本输入法回车键类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 显示为开始样式。 */
    ARKUI_ENTER_KEY_TYPE_GO = 2,
    /** 显示为搜索样式。 */
    ARKUI_ENTER_KEY_TYPE_SEARCH = 3,
    /** 显示为发送样式。 */
    ARKUI_ENTER_KEY_TYPE_SEND,
    /** 显示为下一个样式。 */
    ARKUI_ENTER_KEY_TYPE_NEXT,
    /** 显示为完成样式。 */
    ARKUI_ENTER_KEY_TYPE_DONE,
    /** 显示为上一个样式。 */
    ARKUI_ENTER_KEY_TYPE_PREVIOUS,
    /** 显示为换行样式。 */
    ARKUI_ENTER_KEY_TYPE_NEW_LINE,
} ArkUI_EnterKeyType;

/**
 * @brief 定义单行文本输入法类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 基本输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NORMAL = 0,
    /** 纯数字模式。 */
    ARKUI_TEXTINPUT_TYPE_NUMBER = 2,
    /** 电话号码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_PHONE_NUMBER = 3,
    /** 邮箱地址输入模式。 */
    ARKUI_TEXTINPUT_TYPE_EMAIL = 5,
    /** 密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_PASSWORD = 7,
    /** 纯数字密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD = 8,
    /** 锁屏应用密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /** 用户名输入模式。 */
    ARKUI_TEXTINPUT_TYPE_USER_NAME = 10,
    /** 新密码输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD = 11,
    /** 带小数点的数字输入模式。 */
    ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL = 12,
} ArkUI_TextInputType;

/**
 * @brief 定义清除按钮样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 清除按钮常显样式。*/
    ARKUI_CANCELBUTTON_STYLE_CONSTANT = 0,
    /** 清除按钮常隐样式。*/
    ARKUI_CANCELBUTTON_STYLE_INVISIBLE,
    /** 清除按钮输入样式。*/
    ARKUI_CANCELBUTTON_STYLE_INPUT,
} ArkUI_CancelButtonStyle;

/**
 * @brief 定义XComponent类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 用于EGL/OpenGLES和媒体数据写入，开发者定制绘制内容单独显示在屏幕上。*/
    ARKUI_XCOMPONENT_TYPE_SURFACE = 0,
    /** 用于EGL/OpenGLES和媒体数据写入，开发者定制绘制内容和XComponent组件内容合成后展示在屏幕上。*/
    ARKUI_XCOMPONENT_TYPE_TEXTURE = 2,
} ArkUI_XComponentType;

/**
 * @brief 定义进度条类型枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 线性样式。*/
    ARKUI_PROGRESS_LINEAR = 0,
    /** 环形无刻度样式。*/
    ARKUI_PROGRESS_RING,
    /** 圆形样式。*/
    ARKUI_PROGRESS_ECLIPSE,
    /** 唤醒有刻度样式。*/
    ARKUI_PROGRESS_SCALERING,
    /** 胶囊样式。*/
    ARKUI_PROGRESS_CAPSULE,
}ArkUI_ProgressType;

typedef enum {
    /** 不使用装饰线。*/
    ARKUI_TEXT_DECORATION_TYPE_NONE = 0,
    /** 文字下划线修饰。*/
    ARKUI_TEXT_DECORATION_TYPE_UNDERLINE,
    /** 文字上划线修饰。*/
    ARKUI_TEXT_DECORATION_TYPE_OVERLINE,
    /** 穿过文本的修饰线。*/
    ARKUI_TEXT_DECORATION_TYPE_LINETHROUGH,
} ArkUI_TextDecorationType;

typedef enum {
    /** 保持原有大小写。*/
    ARKUI_TEXT_CASE_NORMAL = 0,
    /** 文本全小写。*/
    ARKUI_TEXT_CASE_LOWER,
    /** 文本全大写。*/
    ARKUI_TEXT_CASE_UPPER,
} ArkUI_TextCase;

typedef enum {
    /** 不支持复制。*/
    ARKUI_COPY_OPTIONS_NONE = 0,
    /** 支持应用内复制。*/
    ARKUI_COPY_OPTIONS_IN_APP,
    /** 支持设备内复制。*/
    ARKUI_COPY_OPTIONS_LOCAL_DEVICE,
    /** 支持跨设备复制。*/
    ARKUI_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_CopyOptions;

typedef enum {
    /** 颜色。*/
    ARKUI_SHADOW_TYPE_COLOR = 0,
    /** 模糊。*/
    ARKUI_SHADOW_TYPE_BLUR
} ArkUI_ShadowType;

/**
 * @brief 定义滑动选择文本选择器输入类型。
 *
 * @since 12
 */
typedef enum {
    /** 单列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /** 多列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_MULTI,
    /** 支持图片资源的单列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_C0NTENT,
    /** 支持联动的多列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT,
} ArkUI_TextPickerRangeType;

/**
 * @brief 定义单列滑动数据选择器支持图片资源的输入结构体。
 *
 * @since 12
 */
typedef struct {
    /** 图片资源。*/
    const char* icon;
    /** 文本信息。*/
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief 定义多列带联动能力的滑动数据选择器的输入结构体。
 *
 * @since 12
 */
typedef struct {
    /** 文本信息。*/
    const char* text;
    /** 联动数据。*/
    const ARKUI_TextPickerRangeContent* children;
    /** 联动数据数组大小。*/
    int32_t size;
} ARKUI_TextPickerCascadeRangeContent;

/**
 * @brief 定义边缘滑动效果枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 弹性物理动效，滑动到边缘后可以根据初始速度或通过触摸事件继续滑动一段距离，松手后回弹。*/
    ARKUI_EDGE_EFFECT_SPRING = 0,
    /** 阴影效果，滑动到边缘后会有圆弧状的阴影。*/
    ARKUI_EDGE_EFFECT_FADE,
    /** 滑动到边缘后无效果。*/
    ARKUI_EDGE_EFFECT_NONE,
} ArkUI_EdgeEffect;

/**
 * @brief 定义列表项滚动结束对齐效果枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 默认无项目滚动对齐效果。*/
    ARKUI_SCROLL_SNAP_ALIGN_NONE = 0,
    /** 视图中的第一项将在列表的开头对齐。*/
    ARKUI_SCROLL_SNAP_ALIGN_START,
    /** 视图中的中间项将在列表中心对齐。*/
    ARKUI_SCROLL_SNAP_ALIGN_CENTER,
    /** 视图中的最后一项将在列表末尾对齐。*/
    ARKUI_SCROLL_SNAP_ALIGN_END,
} ArkUI_ScrollSnapAlign;

/**
 * @brief 定义滚动条状态枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 不显示。*/
    ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF = 0,
    /** 按需显示(触摸时显示，2s后消失)。*/
    ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO,
    /** 常驻显示。*/
    ARKUI_SCROLL_BAR_DISPLAY_MODE_ON,
} ArkUI_ScrollBarDisplayMode;

/**
 * @brief 定义滚动方向和List组件排列方向枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 仅支持竖直方向滚动。*/
    ARKUI_AXIS_VERTICAL = 0,
    /** 仅支持水平方向滚动。*/
    ARKUI_AXIS_HORIZONTAL,
} ArkUI_Axis;

/**
 * @brief 定义列表是否吸顶和吸底枚举值。
 *
 * @since 12
 */
typedef enum {
    /** ListItemGroup的header不吸顶，footer不吸底。*/
    ARKUI_STICKYSTYLE_NONE = 0,
    /** ListItemGroup的header吸顶，footer不吸底。*/
    ARKUI_STICKYSTYLE_HEADER = 1,
    /** ListItemGroup的footer吸底，header不吸顶。*/
    ARKUI_STICKYSTYLE_FOOTER = 2,
    /** ListItemGroup的footer吸底，header吸顶。*/
    ARKUI_STICKYSTYLE_BOTH = 3,
} ArkUI_StickyStyle;


/**
 * @brief 边框线条样式枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 显示为一条实线。 */
    ARKUI_BORDER_STYLE_SOLID = 0,
    /** 显示为一系列短的方形虚线。*/
    ARKUI_BORDER_STYLE_DASHED,
    /** 显示为一系列圆点。*/
    ARKUI_BORDER_STYLE_DOTTED,
} ArkUI_BorderStyle;

/**
 * @brief 触摸测试控制枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 默认触摸测试效果。 */
    ARKUI_HIT_TEST_MODE_DEFAULT = 0,
    /** 自身响应触摸测试。*/
    ARKUI_HIT_TEST_MODE_BLOCK,
    /** 自身和子节点都响应触摸测试。*/
    ARKUI_HIT_TEST_MODE_TRANSPARENT,
    /** 自身不响应触摸测试。*/
    ARKUI_HIT_TEST_MODE_NONE
} ArkUI_HitTestMode;

/**
 * @brief 阴影效果枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 超小阴影。 */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
    /** 小阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
    /** 中阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
    /** 大阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
    /** 浮动小阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
    /** 浮动中阴影。*/
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
} ArkUI_ShadowStyle;

/**
 * @brief 动画曲线枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 动画从头到尾的速度都是相同。 */
    ARKUI_CURVE_LINEAR = 0,
    /** 动画以低速开始，然后加快，在结束前变慢。 */
    ARKUI_CURVE_EASE,
    /** 动画以低速开始。 */
    ARKUI_CURVE_EASE_IN,
    /** 动画以低速结束。 */
    ARKUI_CURVE_EASE_OUT,
    /** 动画以低速开始和结束。 */
    ARKUI_CURVE_EASE_IN_OUT,
    /** 动画标准曲线。 */
    ARKUI_CURVE_FAST_OUT_SLOW_IN,
    /** 动画减速曲线。 */
    ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
    /** 动画加速曲线。 */
    ARKUI_CURVE_FAST_OUT_LINEAR_IN,
    /** 动画急缓曲线。 */
    ARKUI_CURVE_EXTREME_DECELERATION,
    /** 动画锐利曲线。 */
    ARKUI_CURVE_SHARP,
    /** 动画节奏曲线。 */
    ARKUI_CURVE_RHYTHM,
    /** 动画平滑曲线。 */
    ARKUI_CURVE_SMOOTH,
    /** 动画阻尼曲线。 */
    ARKUI_CURVE_FRICTION,
} ArkUI_AnimationCurve;

/**
 * @brief Swiper导航点箭头枚举值。
 *
 * @since 12
 */
typedef enum {
    /** 不显示swiper中导航点箭头。 */
    ARKUI_SWIPER_ARROW_FALSE = 0,
    /** 显示swiper中导航点箭头。 */
    ARKUI_SWIPER_ARROW_TRUE,
    /** 在hover状态下显示swiper中导航点箭头。 */
    ARKUI_SWIPER_ARROW__SHOW_ON_HOVER,
} ArkUI_SwiperDisplayArrow;


/**
 * @brief 定义无障碍重要性。
 *
 * @since 12
 */
typedef enum {
    /** 根据组件不同会转换为“yes”或者“no”。 */
    ARKUI_ACCESSIBILITY_LEVEL_AUTO = 0,
    /** 当前组件可被无障碍辅助服务所识别。*/
    ARKUI_ACCESSIBILITY_LEVEL_YES,
    /** 当前组件不可被无障碍辅助服务所识别。*/
    ARKUI_ACCESSIBILITY_LEVEL_NO,
    /** 当前组件及其所有子组件不可被无障碍辅助服务所识别。*/
    ARKUI_ACCESSIBILITY_LEVEL_NO_HIDE_DESCENDANTS,
} ArkUI_AccessibilityLevel;

/**
 * @brief 定义组件支持设置文本是否可复制粘贴。
 *
 * @since 12
 */
typedef enum {
    /** 不支持复制。 */
    ARKUI_TEXT_COPY_OPTIONS_NONE = 0,
    /** 支持应用内复制。*/
    ARKUI_TEXT_COPY_OPTIONS_IN_APP,
    /** 支持设备内复制。*/
    ARKUI_TEXT_COPY_OPTIONS_LOCAL_DEVICE,
    /** 支持跨设备复制。*/
    ARKUI_TEXT_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_TextCopyOptions;


/**
 * @brief 定义文本自适应高度的方式。
 *
 * @since 12
 */
typedef enum {
    /** 设置文本高度自适应方式为以MaxLines优先。 */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST = 0,
    /** 设置文本高度自适应方式为以缩小字体优先。*/
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
    /** 设置文本高度自适应方式为以布局约束（高度）优先。*/
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST,
} ArkUI_TextHeightAdaptivePolicy;


/**
 * @brief 定义嵌套滚动选项。
 *
 * @since 12
 */
typedef enum {
    /** 只自身滚动，不与父组件联动。 */
    ARKUI_SCROLL_NESTED_MODE_SELF_ONLY = 0,
    /** 自身先滚动，自身滚动到边缘以后父组件滚动。父组件滚动到边缘以后
    如果父组件有边缘效果，则父组件触发边缘效果，否则子组件触发边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,
    /** 父组件先滚动，父组件滚动到边缘以后自身滚动。
    身滚动到边缘后，如果有边缘效果，会触发自身的边缘效果，否则触发父组件的边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST,
    /** 自身和父组件同时滚动，自身和父组件都到达边缘以后
    如果自身有边缘效果，则自身触发边缘效果，否则父组件触发边缘效果。*/
    ARKUI_SCROLL_NESTED_MODE_PARALLEL,
} ArkUI_ScrollNestedMode;


/**
 * @brief 定义滚动到的边缘位置。
 *
 * @since 12
 */
typedef enum {
    /** 竖直方向上边缘。*/
    ARKUI_SCROLL_EDGE_TOP = 0,
    /** 竖直方向居中位置。*/
    ARKUI_SCROLL_EDGE_CENTER,
    /** 竖直方向下边缘。*/
    ARKUI_SCROLL_EDGE_BOTTOM,
    /** 交叉轴方向文本基线位置。*/
    ARKUI_SCROLL_EDGE_BASELINE,
    /** 水平方向起始位置。*/
    ARKUI_SCROLL_EDGE_START,
    /** 水平方向居中位置。*/
    ARKUI_SCROLL_EDGE_MIDDLE,
    /** 水平方向末尾位置。*/
    ARKUI_SCROLL_EDGE_END,
} ArkUI_ScrollEdge;

/**
 * @brief 定义滑块形状。
 *
 * @since 12
 */
typedef enum {
    /** 使用默认滑块（圆形）。*/
    ARKUI_SLIDER_BLOCK_STYLE_DEFAULT = 0,
    /** 使用图片资源作为滑块。*/
    ARKUI_SLIDER_BLOCK_STYLE_IMAGE,
    /** 使用自定义形状作为滑块。*/
    ARKUI_SLIDER_BLOCK_STYLE_SHAPE,
} ArkUI_SliderBlockStyle;

/**
 * @brief 定义滑动条滑动方向。
 *
 * @since 12
 */
typedef enum {
    /** 方向为纵向。*/
    ARKUI_SLIDER_DIRECTION_VERTICAL = 0,
    /** 方向为横向。*/
    ARKUI_SLIDER_DIRECTION_HORIZONTAL,
} ArkUI_SliderDirection;

/**
 * @brief 定义滑块与滑轨显示样式。
 *
 * @since 12
 */
typedef enum {
    /** 滑块在滑轨上。*/
    ARKUI_SLIDER_STYLE_OUT_SET = 0,
    /** 滑块在滑轨内。*/
    ARKUI_SLIDER_STYLE_IN_SET,
} ArkUI_SliderStyle;

/**
 * @brief 定义CheckBox组件形状。
 *
 * @since 12
 */
typedef enum {
    /** 圆形。*/
    ArkUI_CHECKBOX_SHAPE_CIRCLE = 0,
    /** 圆角方形。*/
    ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE,
} ArkUI_CheckboxShape;

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
