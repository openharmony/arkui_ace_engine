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

/**
 * @brief 定义滑动选择文本选择器输入类型。
 *
 * @since 12
 */
typedef enum {
    /** 单列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /** 多列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_MULTI = 0,
    /** 支持图片资源的单列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_C0NTENT = 0,
    /** 支持联动的多列数据选择器。*/
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT = 0,
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

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
