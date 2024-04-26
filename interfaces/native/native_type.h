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
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file native_type.h
 *
 * @brief Defines the common types for the native module.
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
 * @brief Defines the ArkUI native component object.
 *
 * @since 12
 */
struct ArkUI_Node;
/**
 * @brief Defines the custom dialog box controller of ArkUI on the native side.
 *
 * @since 12
 */
struct ArkUI_NativeDialog;

/**
 * @brief Sets the size constraints of a component during component layout.
 *
 * @since 12
 */
typedef struct ArkUI_LayoutConstraint ArkUI_LayoutConstraint;

/**
 * @brief Defines the structure of the component drawing context.
 *
 * @since 12
 */
typedef struct ArkUI_DrawContext ArkUI_DrawContext;

/**
 * @brief Defines the pointer to the ArkUI native component object.
 *
 * @since 12
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Defines the pointer to the custom dialog box controller of ArkUI on the native side.
 *
 * @since 12
 */
typedef struct ArkUI_NativeDialog* ArkUI_NativeDialogHandle;

/**
 * @brief 提供ArkUI native UI的上下文实例对象定义。
 *
 * @since 12
 */

struct ArkUI_Context;

/**
 * @brief 定义ArkUI native UI的上下文实例对象指针定义。
 *
 * @since 12
 */
typedef struct ArkUI_Context* ArkUI_ContextHandle;

/**
 * @brief Defines the pointer type of the ArkUI native node content object.
 *
 * @since 12
 */
typedef struct ArkUI_NodeContent* ArkUI_NodeContentHandle;

/**
 * @brief Defines the event callback type.
 *
 * @since 12
 */
typedef struct {
    /** Custom type. */
    void* userData;
    /** Event callback. */
    void (*callback)(void* userData);
} ArkUI_ContextCallback;

/**
 * @brief Defines the water flow section configuration.
 *
 * @since 12
 */
typedef struct ArkUI_WaterFlowSectionOption ArkUI_WaterFlowSectionOption;

/**
 * @brief Provides the number types of ArkUI in the native code.
 *
 * @since 12
 */
typedef union {
    /** Floating-point type. */
    float f32;
    /** Signed integer. */
    int32_t i32;
    /** Unsigned integer. */
    uint32_t u32;
} ArkUI_NumberValue;

/**
 * @brief Enumerates the alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** Top start. */
    ARKUI_ALIGNMENT_TOP_START = 0,
    /** Top center. */
    ARKUI_ALIGNMENT_TOP,
    /** Top end. */
    ARKUI_ALIGNMENT_TOP_END,
    /** Vertically centered start. */
    ARKUI_ALIGNMENT_START,
    /** Horizontally and vertically centered. */
    ARKUI_ALIGNMENT_CENTER,
    /** Vertically centered end. */
    ARKUI_ALIGNMENT_END,
    /** Bottom start. */
    ARKUI_ALIGNMENT_BOTTOM_START,
    /** Horizontally centered on the bottom. */
    ARKUI_ALIGNMENT_BOTTOM,
    /** Bottom end. */
    ARKUI_ALIGNMENT_BOTTOM_END,
} ArkUI_Alignment;

/**
 * @brief Enumerates the image repeat patterns.
 *
 * @since 12
 */
typedef enum {
    /** The image is not repeatedly drawn. */
    ARKUI_IMAGE_REPEAT_NONE = 0,
    /** The image is repeatedly drawn only along the x-axis. */
    ARKUI_IMAGE_REPEAT_X,
    /** The image is repeatedly drawn only along the y-axis. */
    ARKUI_IMAGE_REPEAT_Y,
    /** The image is repeatedly drawn along both axes. */
    ARKUI_IMAGE_REPEAT_XY,
} ArkUI_ImageRepeat;

/**
 * @brief Enumerates the font styles.
 *
 * @since 12
 */
typedef enum {
    /** Standard font style. */
    ARKUI_FONT_STYLE_NORMAL = 0,
    /** Italic font style. */
    ARKUI_FONT_STYLE_ITALIC
} ArkUI_FontStyle;

/**
 * @brief Enumerates the font weights.
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
    /** The font weight is bold. */
    ARKUI_FONT_WEIGHT_BOLD,
    /** The font weight is normal. */
    ARKUI_FONT_WEIGHT_NORMAL,
    /** The font weight is bolder. */
    ARKUI_FONT_WEIGHT_BOLDER,
    /** The font weight is lighter. */
    ARKUI_FONT_WEIGHT_LIGHTER,
    /** The font weight is medium. */
    ARKUI_FONT_WEIGHT_MEDIUM,
    /** The font weight is normal. */
    ARKUI_FONT_WEIGHT_REGULAR,
} ArkUI_FontWeight;

/**
 * @brief Enumerates the text alignment mode.
 *
 * @since 12
 */
typedef enum {
    /** Aligned with the start. */
    ARKUI_TEXT_ALIGNMENT_START = 0,
    /** Horizontally centered. */
    ARKUI_TEXT_ALIGNMENT_CENTER,
    /** Aligned with the end. */
    ARKUI_TEXT_ALIGNMENT_END,
    /** Aligned with both margins. */
    ARKUI_TEXT_ALIGNMENT_JUSTIFY,
} ArkUI_TextAlignment;

/**
 * @brief Enumerates the types of the Enter key for a single-line text box.
 *
 * @since 12
 */
typedef enum {
    /** The Enter key is labeled "Go." */
    ARKUI_ENTER_KEY_TYPE_GO = 2,
    /** The Enter key is labeled "Search." */
    ARKUI_ENTER_KEY_TYPE_SEARCH = 3,
    /** The Enter key is labeled "Send." */
    ARKUI_ENTER_KEY_TYPE_SEND,
    /** The Enter key is labeled "Next." */
    ARKUI_ENTER_KEY_TYPE_NEXT,
    /** The Enter key is labeled "Done." */
    ARKUI_ENTER_KEY_TYPE_DONE,
    /** The Enter key is labeled "Previous." */
    ARKUI_ENTER_KEY_TYPE_PREVIOUS,
    /** The Enter key is labeled "New Line." */
    ARKUI_ENTER_KEY_TYPE_NEW_LINE,
} ArkUI_EnterKeyType;

/**
 * @brief Enumerates the text input types.
 *
 * @since 12
 */
typedef enum {
    /** Normal input mode. */
    ARKUI_TEXTINPUT_TYPE_NORMAL = 0,
    /** Number input mode. */
    ARKUI_TEXTINPUT_TYPE_NUMBER = 2,
    /** Phone number input mode. */
    ARKUI_TEXTINPUT_TYPE_PHONE_NUMBER = 3,
    /** Email address input mode. */
    ARKUI_TEXTINPUT_TYPE_EMAIL = 5,
    /** Password input mode. */
    ARKUI_TEXTINPUT_TYPE_PASSWORD = 7,
    /** Numeric password input mode. */
    ARKUI_TEXTINPUT_TYPE_NUMBER_PASSWORD = 8,
    /** Lock screen password input mode. */
    ARKUI_TEXTINPUT_TYPE_SCREEN_LOCK_PASSWORD = 9,
    /** Username input mode. */
    ARKUI_TEXTINPUT_TYPE_USER_NAME = 10,
    /** New password input mode. */
    ARKUI_TEXTINPUT_TYPE_NEW_PASSWORD = 11,
    /** Number input mode with a decimal point. */
    ARKUI_TEXTINPUT_TYPE_NUMBER_DECIMAL = 12,
} ArkUI_TextInputType;

/**
 * @brief Enumerates the text box types.
 *
 * @since 12
 */
typedef enum {
    /** Normal input mode. */
    ARKUI_TEXTAREA_TYPE_NORMAL = 0,
    /** Number input mode. */
    ARKUI_TEXTAREA_TYPE_NUMBER = 2,
    /** Phone number input mode. */
    ARKUI_TEXTAREA_TYPE_PHONE_NUMBER = 3,
    /** Email address input mode. */
    ARKUI_TEXTAREA_TYPE_EMAIL = 5,
} ArkUI_TextAreaType;

/**
 * @brief Enumerates the styles of the Cancel button.
 *
 * @since 12
 */
typedef enum {
    /** The Cancel button is always displayed. */
    ARKUI_CANCELBUTTON_STYLE_CONSTANT = 0,
    /** The Cancel button is always hidden. */
    ARKUI_CANCELBUTTON_STYLE_INVISIBLE,
    /** The Cancel button is displayed when there is text input. */
    ARKUI_CANCELBUTTON_STYLE_INPUT,
} ArkUI_CancelButtonStyle;

/**
 * @brief Enumerates the types of the <b><XComponent></b> component.
 *
 * @since 12
 */
typedef enum {
    /** The custom content of EGL/OpenGL ES and media data is displayed individually on the screen. */
    ARKUI_XCOMPONENT_TYPE_SURFACE = 0,
    /** The custom content of EGL/OpenGL ES and media data is grouped and displayed together with content
      * of the component.
      */
    ARKUI_XCOMPONENT_TYPE_TEXTURE = 2,
} ArkUI_XComponentType;

/**
 * @brief Enumerates the styles of the progress indicator.
 *
 * @since 12
 */
typedef enum {
    /** Linear style. */
    ARKUI_PROGRESS_TYPE_LINEAR = 0,
    /** Indeterminate ring style. */
    ARKUI_PROGRESS_TYPE_RING,
    /** Eclipse style. */
    ARKUI_PROGRESS_TYPE_ECLIPSE,
    /** Determinate ring style. */
    ARKUI_PROGRESS_TYPE_SCALE_RING,
    /** Capsule style. */
    ARKUI_PROGRESS_TYPE_CAPSULE,
}ArkUI_ProgressType;

/**
 * @brief Enumerates the text decoration styles.
 *
 * @since 12
 */
typedef enum {
    /** No text decoration. */
    ARKUI_TEXT_DECORATION_TYPE_NONE = 0,
    /** Line under the text. */
    ARKUI_TEXT_DECORATION_TYPE_UNDERLINE,
    /** Line over the text. */
    ARKUI_TEXT_DECORATION_TYPE_OVERLINE,
    /** Line through the text. */
    ARKUI_TEXT_DECORATION_TYPE_LINE_THROUGH,
} ArkUI_TextDecorationType;

/**
 * @brief Enumerates the text decoration line styles.
 *
 * @since 12
 */
typedef enum {
    /** Solid line. */
    ARKUI_TEXT_DECORATION_STYLE_SOLID = 0,
    /** Double line. */
    ARKUI_TEXT_DECORATION_STYLE_DOUBLE,
    /** Dotted line. */
    ARKUI_TEXT_DECORATION_STYLE_DOTTED,
    /** Dashed line. */
    ARKUI_TEXT_DECORATION_STYLE_DASHED,
    /** Wavy line. */
    ARKUI_TEXT_DECORATION_STYLE_WAVY,
} ArkUiTextDecorationStyle;

/**
 * @brief Enumerates the text cases.
 *
 * @since 12
 */
typedef enum {
    /** The original case of the text is retained. */
    ARKUI_TEXT_CASE_NORMAL = 0,
    /** All letters in the text are in lowercase. */
    ARKUI_TEXT_CASE_LOWER,
    /** All letters in the text are in uppercase. */
    ARKUI_TEXT_CASE_UPPER,
} ArkUI_TextCase;

/**
 * @brief Enumerates the text copy and paste modes.
 *
 * @since 12
 */
typedef enum {
    /** Copy is not allowed. */
    ARKUI_COPY_OPTIONS_NONE = 0,
    /** Intra-application copy is allowed. */
    ARKUI_COPY_OPTIONS_IN_APP,
    /** Intra-device copy is allowed. */
    ARKUI_COPY_OPTIONS_LOCAL_DEVICE,
    /** Cross-device copy is allowed. */
    ARKUI_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_CopyOptions;

/**
 * @brief Enumerates the shadow types.
 *
 * @since 12
 */
typedef enum {
    /** Color. */
    ARKUI_SHADOW_TYPE_COLOR = 0,
    /** Blur. */
    ARKUI_SHADOW_TYPE_BLUR
} ArkUI_ShadowType;

/**
 * @brief Enumerates the types of the text picker.
 *
 * @since 12
 */
typedef enum {
    /** Single-column text picker. */
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /** Multi-column text picker. */
    ARKUI_TEXTPICKER_RANGETYPE_MULTI,
    /** Single-column text picker with image resources. */
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT,
    /** Interconnected multi-column text picker. */
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT,
} ArkUI_TextPickerRangeType;

/**
 * @brief Defines the input structure of the single-column text picker with image resources.
 *
 * @since 12
 */
typedef struct {
    /** Image resource. */
    const char* icon;
    /** Text information. */
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief Defines the input structure of the interconnected multi-column text picker.
 *
 * @since 12
 */
typedef struct {
    /** Text information. */
    const char* text;
    /** Interconnected data. */
    const ARKUI_TextPickerRangeContent* children;
    /** Size of the interconnected data array. */
    int32_t size;
} ARKUI_TextPickerCascadeRangeContent;

/**
 * @brief Enumerates the effects used at the edges of the component when the boundary of the
 * scrollable content is reached.
 *
 * @since 12
 */
typedef enum {
    /** Spring effect. When at one of the edges, the component can move beyond the bounds based on the
     * initial speed or through touches, and produces a bounce effect when the user releases their finger.
     */
    ARKUI_EDGE_EFFECT_SPRING = 0,
    /** Fade effect. When at one of the edges, the component produces a fade effect. */
    ARKUI_EDGE_EFFECT_FADE,
    /** No effect after the scrollbar is moved to the edge. */
    ARKUI_EDGE_EFFECT_NONE,
} ArkUI_EdgeEffect;

/**
 * @brief Enumerates the scroll directions for the <b><Scroll></b> component.
 *
 * @since 12
 */
typedef enum {
    /** Only vertical scrolling is supported. */
    ARKUI_SCROLL_DIRECTION_VERTICAL = 0,
    /** Only horizontal scrolling is supported. */
    ARKUI_SCROLL_DIRECTION_HORIZONTAL,
    /** Scrolling is not allowed. */
    ARKUI_SCROLL_DIRECTION_NONE = 3,
} ArkUI_ScrollDirection;

/**
 * @brief Enumerates the alignment modes of list items when scrolling ends.
 *
 * @since 12
 */
typedef enum {
    /** No alignment. This is the default value. */
    ARKUI_SCROLL_SNAP_ALIGN_NONE = 0,
    /** The first item in the view is aligned at the start of the list. */
    ARKUI_SCROLL_SNAP_ALIGN_START,
    /** The middle items in the view are aligned in the center of the list. */
    ARKUI_SCROLL_SNAP_ALIGN_CENTER,
    /** The last item in the view is aligned at the end of the list. */
    ARKUI_SCROLL_SNAP_ALIGN_END,
} ArkUI_ScrollSnapAlign;

/**
 * @brief Enumerates the scrollbar display modes.
 *
 * @since 12
 */
typedef enum {
    /** Hide. */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF = 0,
    /** Display on demand (displays when the screen is touched and disappears after 2s). */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_AUTO,
    /** Always display. */
    ARKUI_SCROLL_BAR_DISPLAY_MODE_ON,
} ArkUI_ScrollBarDisplayMode;

/**
 * @brief Enumerates the scroll directions for the <b><List></b> component.
 *
 * @since 12
 */
typedef enum {
    /** Only vertical scrolling is supported. */
    ARKUI_AXIS_VERTICAL = 0,
    /** Only horizontal scrolling is supported. */
    ARKUI_AXIS_HORIZONTAL,
} ArkUI_Axis;

/**
 * @brief Enumerates the modes for pinning the header to the top or the footer to the bottom.
 *
 * @since 12
 */
typedef enum {
    /** In the list item group, the header is not pinned to the top, and the footer is not pinned to the bottom. */
    ARKUI_STICKY_STYLE_NONE = 0,
    /** In the list item group, the header is pinned to the top, and the footer is not pinned to the bottom. */
    ARKUI_STICKY_STYLE_HEADER = 1,
    /** In the list item group, the footer is pinned to the bottom, and the header is not pinned to the top. */
    ARKUI_STICKY_STYLE_FOOTER = 2,
    /** In the list item group, the footer is pinned to the bottom, and the header is pinned to the top. */
    ARKUI_STICKY_STYLE_BOTH = 3,
} ArkUI_StickyStyle;


/**
 * @brief Enumerates the border styles.
 *
 * @since 12
 */
typedef enum {
    /** Solid border. */
    ARKUI_BORDER_STYLE_SOLID = 0,
    /** Dashed border. */
    ARKUI_BORDER_STYLE_DASHED,
    /** Dotted border. */
    ARKUI_BORDER_STYLE_DOTTED,
} ArkUI_BorderStyle;

/**
 * @brief Enumerates the hit test modes.
 *
 * @since 12
 */
typedef enum {
    /** Both the node and its child node respond to the hit test of a touch event,
     * but its sibling node is blocked from the hit test.
     */
    ARKUI_HIT_TEST_MODE_DEFAULT = 0,
    /** The node responds to the hit test of a touch event, but its child node and sibling node are blocked from
     * the hit test.
     */
    ARKUI_HIT_TEST_MODE_BLOCK,
    /** Both the node and its child node respond to the hit test of a touch event, and its sibling node is also
     * considered during the hit test.
     */
    ARKUI_HIT_TEST_MODE_TRANSPARENT,
    /** The node does not respond to the hit test of a touch event. */
    ARKUI_HIT_TEST_MODE_NONE
} ArkUI_HitTestMode;

/**
 * @brief Enumerates the shadow styles.
 *
 * @since 12
 */
typedef enum {
    /** Mini shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_XS = 0,
    /** Little shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_SM,
    /** Medium shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_MD,
    /** Large shadow. */
    ARKUI_SHADOW_STYLE_OUTER_DEFAULT_LG,
    /** Floating small shadow. */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_SM,
    /** Floating medium shadow. */
    ARKUI_SHADOW_STYLE_OUTER_FLOATING_MD,
} ArkUI_ShadowStyle;

/**
 * @brief Enumerates the animation curves.
 *
 * @since 12
 */
typedef enum {
    /** The animation speed keeps unchanged. */
    ARKUI_CURVE_LINEAR = 0,
    /** The animation starts slowly, accelerates, and then slows down towards the end. */
    ARKUI_CURVE_EASE,
    /** The animation starts at a low speed and then picks up speed until the end. */
    ARKUI_CURVE_EASE_IN,
    /** The animation ends at a low speed. */
    ARKUI_CURVE_EASE_OUT,
    /** The animation starts and ends at a low speed. */
    ARKUI_CURVE_EASE_IN_OUT,
    /** The animation uses the standard curve */
    ARKUI_CURVE_FAST_OUT_SLOW_IN,
    /** The animation uses the deceleration curve. */
    ARKUI_CURVE_LINEAR_OUT_SLOW_IN,
    /** The animation uses the acceleration curve. */
    ARKUI_CURVE_FAST_OUT_LINEAR_IN,
    /** The animation uses the extreme deceleration curve. */
    ARKUI_CURVE_EXTREME_DECELERATION,
    /** The animation uses the sharp curve. */
    ARKUI_CURVE_SHARP,
    /** The animation uses the rhythm curve. */
    ARKUI_CURVE_RHYTHM,
    /** The animation uses the smooth curve. */
    ARKUI_CURVE_SMOOTH,
    /** The animation uses the friction curve */
    ARKUI_CURVE_FRICTION,
} ArkUI_AnimationCurve;

/**
 * @brief Enumerates arrow styles of the navigation point indicator.
 *
 * @since 12
 */
typedef enum {
    /** The arrow is not displayed for the navigation point indicator. */
    ARKUI_SWIPER_ARROW_HIDE = 0,
    /** The arrow is displayed for the navigation point indicator. */
    ARKUI_SWIPER_ARROW_SHOW,
    /** The arrow is displayed only when the mouse pointer hovers over the navigation point indicator. */
    ARKUI_SWIPER_ARROW_SHOW_ON_HOVER,
} ArkUI_SwiperArrow;


/**
 * @brief Enumerates the accessibility modes.
 *
 * @since 12
 */
typedef enum {
    /** Whether the component can be identified by the accessibility service is dependent on the component. */
    ARKUI_ACCESSIBILITY_MODE_AUTO = 0,
    /** The component can be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_ENABLED,
    /** The component cannot be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_DISABLED,
    /** The component and all its child components cannot be identified by the accessibility service. */
    ARKUI_ACCESSIBILITY_MODE_DISABLED_FOR_DESCENDANTS,
} ArkUI_AccessibilityMode;

/**
 * @brief Defines whether copy and paste is allowed for text content.
 *
 * @since 12
 */
typedef enum {
    /** Copy is not allowed. */
    ARKUI_TEXT_COPY_OPTIONS_NONE = 0,
    /** Intra-application copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_IN_APP,
    /** Intra-device copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_LOCAL_DEVICE,
    /** Cross-device copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_TextCopyOptions;


/**
 * @brief Defines how the adaptive height is determined for the text.
 *
 * @since 12
 */
typedef enum {
    /** Prioritize the <b>maxLines</b> settings. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST = 0,
    /** Prioritize the <b>minFontSize</b> settings. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
    /** Prioritize the layout constraint settings in terms of height. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST,
} ArkUI_TextHeightAdaptivePolicy;


/**
 * @brief Defines nested scrolling options.
 *
 * @since 12
 */
typedef enum {
    /** The scrolling is contained within the component, and no scroll chaining occurs, that is, the parent component
     * does not scroll when the component scrolling reaches the boundary.
     */
    ARKUI_SCROLL_NESTED_MODE_SELF_ONLY = 0,
    /** The component scrolls first, and when it hits the boundary, the parent component scrolls.
    * When the parent component hits the boundary, its edge effect is displayed. If no edge effect is specified for
     * the parent component, the edge effect of the child component is displayed instead.
     */
    ARKUI_SCROLL_NESTED_MODE_SELF_FIRST,
    /** The parent component scrolls first, and when it hits the boundary, the component scrolls.
     * When the component hits the boundary, its edge effect is displayed. If no edge effect is specified for the
     * component, the edge effect of the parent component is displayed instead.
     */
    ARKUI_SCROLL_NESTED_MODE_PARENT_FIRST,
    /** The component and its parent component scroll at the same time. When both the component and its parent component
     * hit the boundary, the edge effect of the component is displayed. If no edge effect is specified for the
     * component, the edge effect of the parent component is displayed instead.
     */
    ARKUI_SCROLL_NESTED_MODE_PARALLEL,
} ArkUI_ScrollNestedMode;


/**
 * @brief Defines the edge to which the component scrolls.
 *
 * @since 12
 */
typedef enum {
    /** Top edge in the vertical direction. */
    ARKUI_SCROLL_EDGE_TOP = 0,
    /** Bottom edge in the vertical direction. */
    ARKUI_SCROLL_EDGE_BOTTOM,
    /** Start position in the horizontal direction. */
    ARKUI_SCROLL_EDGE_START,
    /** End position in the horizontal direction. */
    ARKUI_SCROLL_EDGE_END,
} ArkUI_ScrollEdge;


/**
 * @brief item对齐方式
 *
 * @since 12
 */
typedef enum {
    /** 首部对齐。指定item首部与List首部对齐。*/
    ARKUI_SCROLL_ALIGN_START = 0,
    /** 居中对齐。指定item主轴方向居中对齐于List。*/
    ARKUI_SCROLL_ALIGN_CENTER,
    /** 尾部对齐。指定item尾部与List尾部对齐。*/
    ARKUI_SCROLL_ALIGN_END,
    /** 自动对齐。若指定item完全处于显示区，不做调整。否则依照滑动距离最短的原则，将指定item首部对齐或尾部对齐于List,使指定item完全处于显示区。*/
    ARKUI_SCROLL_ALIGN_AUTO,
} ArkUI_ScrollAlign;

/**
 * @brief Enumerates the types of the slider in the block direction.
 *
 * @since 12
 */
typedef enum {
    /** Round slider. */
    ARKUI_SLIDER_BLOCK_STYLE_DEFAULT = 0,
    /** Slider with an image background. */
    ARKUI_SLIDER_BLOCK_STYLE_IMAGE,
    /** Slider in a custom shape. */
    ARKUI_SLIDER_BLOCK_STYLE_SHAPE,
} ArkUI_SliderBlockStyle;

/**
 * @brief Enumerates the scroll directions of the slider.
 *
 * @since 12
 */
typedef enum {
    /** Vertical direction. */
    ARKUI_SLIDER_DIRECTION_VERTICAL = 0,
    /** Horizontal direction. */
    ARKUI_SLIDER_DIRECTION_HORIZONTAL,
} ArkUI_SliderDirection;

/**
 * @brief Enumerates the slider styles.
 *
 * @since 12
 */
typedef enum {
    /** The slider is on the slider track. */
    ARKUI_SLIDER_STYLE_OUT_SET = 0,
    /** The slider is in the slider track. */
    ARKUI_SLIDER_STYLE_IN_SET,
} ArkUI_SliderStyle;

/**
 * @brief Enumerates the shapes of the check box
 *
 * @since 12
 */
typedef enum {
    /** Circle. */
    ArkUI_CHECKBOX_SHAPE_CIRCLE = 0,
    /** Rounded square. */
    ArkUI_CHECKBOX_SHAPE_ROUNDED_SQUARE,
} ArkUI_CheckboxShape;

/**
 * @brief Enumerates the animation playback modes.
 *
 * @since 12
 */
typedef enum {
    /** The animation is played forwards. */
    ARKUI_ANIMATION_PLAY_MODE_NORMAL = 0,
    /** The animation is played reversely. */
    ARKUI_ANIMATION_PLAY_MODE_REVERSE,
    /** The animation is played normally for an odd number of times (1, 3, 5...) and reversely for an even number of
     * times (2, 4, 6...).
     */
    ARKUI_ANIMATION_PLAY_MODE_ALTERNATE,
    /** The animation is played reversely for an odd number of times (1, 3, 5...) and normally for an even number of
     * times (2, 4, 6...).
     */
    ARKUI_ANIMATION_PLAY_MODE_ALTERNATE_REVERSE,
} ArkUI_AnimationPlayMode;

/**
 * @brief Defines the image size.
 *
 * @since 12
 */
typedef enum {
    /** The original image aspect ratio is retained. */
    ARKUI_IMAGE_SIZE_AUTO = 0,
    /** Default value. The image is scaled with its aspect ratio retained for both sides to be greater than or equal to
     * the display boundaries.
     */
    ARKUI_IMAGE_SIZE_COVER,
    /** The image is scaled with its aspect ratio retained for the content to be completely displayed within the
     * display boundaries.
     */
    ARKUI_IMAGE_SIZE_CONTAIN,
} ArkUI_ImageSize;

/**
 * @brief Enumerates the adaptive color modes.
 *
 * @since 12
 */
typedef enum {
    /** Adaptive color mode is not used. */
    ARKUI_ADAPTIVE_COLOR_DEFAULT = 0,
    /** Adaptive color mode is used. */
    ARKUI_ADAPTIVE_COLOR_AVERAGE,
} ArkUI_AdaptiveColor;

/**
 * @brief Enumerates the color modes.
 *
 * @since 12
 */
typedef enum {
    /** Following the system color mode. */
    ARKUI_COLOR_MODE_SYSTEM = 0,
    /** Light color mode. */
    ARKUI_COLOR_MODE_LIGHT,
    /** Dark color mode. */
    ARKUI_COLOR_MODE_DARK,
} ArkUI_ColorMode;

/**
 * @brief Enumerates the blur styles.
 *
 * @since 12
 */
typedef enum {
    /** Thin material. */
    ARKUI_BLUR_STYLE_THIN = 0,
    /** Regular material. */
    ARKUI_BLUR_STYLE_REGULAR,
    /** Thick material. */
    ARKUI_BLUR_STYLE_THICK,
    /** Material that creates the minimum depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_THIN,
    /** Material that creates a medium shallow depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_REGULAR,
    /** Material that creates a high shallow depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_THICK,
    /** Material that creates the maximum depth of field effect. */
    ARKUI_BLUR_STYLE_BACKGROUND_ULTRA_THICK,
    /** No blur. */
    ARKUI_BLUR_STYLE_NONE,
    /** Component ultra-thin material. */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THIN,
    /** Component thin material. */
    ARKUI_BLUR_STYLE_COMPONENT_THIN,
    /** Component regular material. */
    ARKUI_BLUR_STYLE_COMPONENT_REGULAR,
    /** Component thick material. */
    ARKUI_BLUR_STYLE_COMPONENT_THICK,
    /** Component ultra-thick material. */
    ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK,
} ArkUI_BlurStyle;

/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** Top aligned. */
    ARKUI_VERTICAL_ALIGNMENT_TOP = 0,
    /** Center aligned. This is the default alignment mode. */
    ARKUI_VERTICAL_ALIGNMENT_CENTER,
    /** Bottom aligned. */
    ARKUI_VERTICAL_ALIGNMENT_BOTTOM,
} ArkUI_VerticalAlignment;

/**
 * @brief Enumerates the alignment mode in the horizontal direction.
 *
 * @since 12
 */
typedef enum {
    /** Aligned with the start edge in the same direction as the language in use. */
    ARKUI_HORIZONTAL_ALIGNMENT_START = 0,
    /** Center aligned. This is the default alignment mode. */
    ARKUI_HORIZONTAL_ALIGNMENT_CENTER,
    /** Aligned with the end edge in the same direction as the language in use. */
    ARKUI_HORIZONTAL_ALIGNMENT_END,
} ArkUI_HorizontalAlignment;

/**
 * @brief Enumerates the display modes when the text is too long.
 *
 * @since 12
 */
typedef enum {
    /** Extra-long text is not clipped. */
    ARKUI_TEXT_OVERFLOW_NONE = 0,
    /** Extra-long text is clipped. */
    ARKUI_TEXT_OVERFLOW_CLIP,
    /** An ellipsis (...) is used to represent text overflow. */
    ARKUI_TEXT_OVERFLOW_ELLIPSIS,
    /** Text continuously scrolls when text overflow occurs. */
    ARKUI_TEXT_OVERFLOW_MARQUEE,
} ArkUI_TextOverflow;

/**
 * @brief Enumerates the alignment mode of the image with the text.
 *
 * @since 12
 */
typedef enum {
    /** The image is bottom aligned with the text baseline. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_BASELINE = 0,
    /** The image is bottom aligned with the text. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_BOTTOM,
    /** The image is centered aligned with the text. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_CENTER,
    /** The image is top aligned with the text. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_TOP,
} ArkUI_ImageSpanAlignment;

/**
 * @brief Defines how the image is resized to fit its container.
 *ImageSpanAlignment
 * @since 12
 */
typedef enum {
    /** The image is scaled with its aspect ratio retained for the content to be completely displayed within the
     * display boundaries.
     */
    ARKUI_OBJECT_FIT_CONTAIN = 0,
    /** The image is scaled with its aspect ratio retained for both sides to be greater than or equal to the
     * display boundaries.
     */
    ARKUI_OBJECT_FIT_COVER,
    /** The image is scaled automatically to fit the display area. */
    ARKUI_OBJECT_FIT_AUTO,
    /** The image is scaled to fill the display area, and its aspect ratio is not retained. */
    ARKUI_OBJECT_FIT_FILL,
    /** The image content is displayed with its aspect ratio retained. The size is smaller than or equal to the
     * original size.
     */
    ARKUI_OBJECT_FIT_SCALE_DOWN,
    /** The original size is retained. */
    ARKUI_OBJECT_FIT_NONE,
} ArkUI_ObjectFit;

/**
 * @brief Enumerates the image interpolation effect.
 *
 * @since 12
 */
typedef enum {
    /** No image interpolation. */
    ARKUI_IMAGE_INTERPOLATION_NONE = 0,
    /** Low quality interpolation. */
    ARKUI_IMAGE_INTERPOLATION_LOW,
    /** Medium quality interpolation. */
    ARKUI_IMAGE_INTERPOLATION_MEDIUM,
    /** High quality interpolation. This mode produces scaled images of the highest possible quality. */
    ARKUI_IMAGE_INTERPOLATION_HIGH,
} ArkUI_ImageInterpolation;


/**
 * @brief Enumerates the blend modes.
 *
 * @since 12
 */
typedef enum {
    /** The top image is superimposed on the bottom image without any blending. */
    ARKUI_BLEND_MODE_NONE = 0,
    /** The target pixels covered by the source pixels are erased by being turned to completely transparent. */
    ARKUI_BLEND_MODE_CLEAR,
    /** r = s: Only the source pixels are displayed. */
    ARKUI_BLEND_MODE_SRC,
    /** r = d: Only the target pixels are displayed. */
    ARKUI_BLEND_MODE_DST,
    /** r = s + (1 - sa) * d: The source pixels are blended based on opacity and cover the target pixels. */
    ARKUI_BLEND_MODE_SRC_OVER,
    /** r = d + (1 - da) * s: The target pixels are blended based on opacity and cover on the source pixels. */
    ARKUI_BLEND_MODE_DST_OVER,
    /** r = s * da: Only the part of the source pixels that overlap with the target pixels is displayed. */
    ARKUI_BLEND_MODE_SRC_IN,
    /** r = d * sa: Only the part of the target pixels that overlap with the source pixels is displayed. */
    ARKUI_BLEND_MODE_DST_IN,
    /** r = s * (1 - da): Only the part of the source pixels that do not overlap with the target pixels is displayed. */
    ARKUI_BLEND_MODE_SRC_OUT,
    /** r = d * (1 - sa): Only the part of the target pixels that do not overlap with the source pixels is displayed. */
    ARKUI_BLEND_MODE_DST_OUT,
    /** r = s * da + d * (1 - sa): The part of the source pixels that overlap with the target pixels is displayed and
     * the part of the target pixels that do not overlap with the source pixels are displayed.
     */
    ARKUI_BLEND_MODE_SRC_ATOP,
    /** r = d * sa + s * (1 - da): The part of the target pixels that overlap with the source pixels and the part of
     * the source pixels that do not overlap with the target pixels are displayed.
     */
    ARKUI_BLEND_MODE_DST_ATOP,
    /** r = s * (1 - da) + d * (1 - sa): Only the non-overlapping part between the source pixels and the target pixels
     * is displayed.
     */
    ARKUI_BLEND_MODE_XOR,
    /** r = min(s + d, 1): New pixels resulting from adding the source pixels to the target pixels are displayed. */
    ARKUI_BLEND_MODE_PLUS,
    /** r = s * d: New pixels resulting from multiplying the source pixels with the target pixels are displayed. */
    ARKUI_BLEND_MODE_MODULATE,
    /** r = s + d - s * d: Pixels are blended by adding the source pixels to the target pixels and subtracting the
     * product of their multiplication.
     */
    ARKUI_BLEND_MODE_SCREEN,
    /** The MULTIPLY or SCREEN mode is used based on the target pixels. */
    ARKUI_BLEND_MODE_OVERLAY,
    /** rc = s + d - max(s * da, d * sa), ra = kSrcOver: When two colors overlap, whichever is darker is used. */
    ARKUI_BLEND_MODE_DARKEN,
    /** rc = s + d - min(s * da, d * sa), ra =
     * kSrcOver: The final pixels are composed of the lightest values of pixels.
     */
    ARKUI_BLEND_MODE_LIGHTEN,
    /** The colors of the target pixels are lightened to reflect the source pixels. */
    ARKUI_BLEND_MODE_COLOR_DODGE,
    /** The colors of the target pixels are darkened to reflect the source pixels. */
    ARKUI_BLEND_MODE_COLOR_BURN,
    /** The MULTIPLY or SCREEN mode is used, depending on the source pixels. */
    ARKUI_BLEND_MODE_HARD_LIGHT,
    /** The LIGHTEN or DARKEN mode is used, depending on the source pixels. */
    ARKUI_BLEND_MODE_SOFT_LIGHT,
    /** rc = s + d - 2 * (min(s * da, d * sa)), ra =
       kSrcOver: The final pixel is the result of subtracting the darker of the two pixels (source and target) from
       the lighter one. */
    ARKUI_BLEND_MODE_DIFFERENCE,
    /** rc = s + d - two(s * d), ra = kSrcOver: The final pixel is similar to <b>DIFFERENCE</b>, but with less contrast.
     */
    ARKUI_BLEND_MODE_EXCLUSION,
    /** r = s * (1 - da) + d * (1 - sa) + s * d: The final pixel is the result of multiplying the source pixel
     *  by the target pixel.	 */
    ARKUI_BLEND_MODE_MULTIPLY,
    /** The resultant image is created with the luminance and saturation of the source image and the hue of the target
     *  image. */
    ARKUI_BLEND_MODE_HUE,
    /** The resultant image is created with the luminance and hue of the target image and the saturation of the source
     *  image. */
    ARKUI_BLEND_MODE_SATURATION,
    /** The resultant image is created with the saturation and hue of the source image and the luminance of the target
     *  image. */
    ARKUI_BLEND_MODE_COLOR,
    /** The resultant image is created with the saturation and hue of the target image and the luminance of the source
     *  image. */
    ARKUI_BLEND_MODE_LUMINOSITY,
} ArkUI_BlendMode;

/**
 * @brief Enumerates the modes in which components are laid out along the main axis of the container.
 *
 * @since 12
 */
typedef enum {
    /** Components are arranged from left to right. */
    ARKUI_DIRECTION_LTR = 0,
    /** Components are arranged from right to left. */
    ARKUI_DIRECTION_RTL,
    /** The default layout direction is used. */
    ARKUI_DIRECTION_AUTO = 3,
} ArkUI_Direction;

/**
 * @brief Enumerates the modes in which components are laid out along the cross axis of the container.
 *
 * @since 12
 */
typedef enum {
    /** The default configuration in the container is used. */
    ARKUI_ITEM_ALIGNMENT_AUTO = 0,
    /** The items in the container are aligned with the cross-start edge. */
    ARKUI_ITEM_ALIGNMENT_START,
    /** The items in the container are centered along the cross axis. */
    ARKUI_ITEM_ALIGNMENT_CENTER,
    /** The items in the container are aligned with the cross-end edge. */
    ARKUI_ITEM_ALIGNMENT_END,
    /** The items in the container are stretched and padded along the cross axis. */
    ARKUI_ITEM_ALIGNMENT_STRETCH,
    /** The items in the container are aligned in such a manner that their text baselines are aligned along the
     *  cross axis. */
    ARKUI_ITEM_ALIGNMENT_BASELINE,
} ArkUI_ItemAlignment;

/**
 * @brief Enumerates the foreground colors.
 *
 * @since 12
 */
typedef enum {
    /** The foreground colors are the inverse of the component background colors. */
    ARKUI_COLOR_STRATEGY_INVERT = 0,
    /** The shadow colors of the component are the average color obtained from the component background shadow area. */
    ARKUI_COLOR_STRATEGY_AVERAGE,
    /** The shadow colors of the component are the primary color obtained from the component background shadow area. */
    ARKUI_COLOR_STRATEGY_PRIMARY,
} ArkUI_ColorStrategy;

/**
 * @brief Enumerates the vertical alignment modes.
 *
 * @since 12
 */
typedef enum {
    /** The child components are aligned with the start edge of the main axis. */
    ARKUI_FLEX_ALIGNMENT_START = 1,
    /** The child components are aligned in the center of the main axis. */
    ARKUI_FLEX_ALIGNMENT_CENTER = 2,
    /** The child components are aligned with the end edge of the main axis. */
    ARKUI_FLEX_ALIGNMENT_END = 3,
    /** The child components are evenly distributed along the main axis. The space between any two adjacent components
     * is the same. The first component is aligned with the main-start, and the last component is aligned with
     * the main-end.
     */
    ARKUI_FLEX_ALIGNMENT_SPACE_BETWEEN = 6,
    /** The child components are evenly distributed along the main axis. The space between any two adjacent components
     * is the same. The space between the first component and main-start, and that between the last component and
     * cross-main are both half the size of the space between two adjacent components.
     */
    ARKUI_FLEX_ALIGNMENT_SPACE_AROUND = 7,
    /** The child components are evenly distributed along the main axis. The space between the first component
     * and main-start, the space between the last component and main-end, and the space between any two adjacent
     * components are the same.
     */
    ARKUI_FLEX_ALIGNMENT_SPACE_EVENLY = 8,
} ArkUI_FlexAlignment;

/**
 * @brief Enumerates the directions of the main axis in the flex container.
 *
 * @since 12
 */
typedef enum {
    /** The child components are arranged in the same direction as the main axis runs along the rows. */
    ARKUI_FLEX_DIRECTION_ROW = 0,
    /** The child components are arranged in the same direction as the main axis runs down the columns. */
    ARKUI_FLEX_DIRECTION_COLUMN,
    /** The child components are arranged opposite to the <b>ROW</b> direction. */
    ARKUI_FLEX_DIRECTION_ROW_REVERSE,
    /** The child components are arranged opposite to the <b>COLUMN</b> direction. */
    ARKUI_FLEX_DIRECTION_COLUMN_REVERSE,
} ArkUI_FlexDirection;

/**
 * @brief Defines whether the flex container has a single line or multiple lines.
 *
 * @since 12
 */
typedef enum {
    /** The child components in the flex container are arranged in a single line, and they cannot overflow. */
    ARKUI_FLEX_WRAP_NO_WRAP = 0,
    /** The child components in the flex container are arranged in multiple lines, and they may overflow. */
    ARKUI_FLEX_WRAP_WRAP,
    /** The child components in the flex container are reversely arranged in multiple lines, and they may overflow. */
    ARKUI_FLEX_WRAP_WRAP_REVERSE,
} ArkUI_FlexWrap;

/**
 * @brief Enumerates the visibility values.
 *
 * @since 12
 */
typedef enum {
    /** The component is visible. */
    ARKUI_VISIBILITY_VISIBLE = 0,
    /** The component is hidden, and a placeholder is used for it in the layout. */
    ARKUI_VISIBILITY_HIDDEN,
    /** The component is hidden. It is not involved in the layout, and no placeholder is used for it. */
    ARKUI_VISIBILITY_NONE,
} ArkUI_Visibility;

/**
 * @brief Enumerates the alignment modes between the calendar picker and the entry component.
 *
 * @since 12
 */
typedef enum {
    /** Left aligned. */
    ARKUI_CALENDAR_ALIGNMENT_START = 0,
    /** Center aligned. */
    ARKUI_CALENDAR_ALIGNMENT_CENTER,
    /** Right aligned. */
    ARKUI_CALENDAR_ALIGNMENT_END,
} ArkUI_CalendarAlignment;

/**
 * @brief Enumerates the mask types.
 *
 * @since 12
 */
typedef enum {
    /** Rectangle. */
    ARKUI_MASK_TYPE_RECTANGLE = 0,
    /** Circle. */
    ARKUI_MASK_TYPE_CIRCLE,
    /** Ellipse. */
    ARKUI_MASK_TYPE_ELLIPSE,
    /** Path. */
    ARKUI_MASK_TYPE_PATH,
    /** Progress indicator. */
    ARKUI_MASK_TYPE_PROGRESS,
} ArkUI_MaskType;

/**
 * @brief Enumerates the clipping region types.
 *
 * @since 12
 */
typedef enum {
    /** Rectangle. */
    ARKUI_CLIP_TYPE_RECTANGLE = 0,
    /** Circle. */
    ARKUI_CLIP_TYPE_CIRCLE,
    /** Ellipse. */
    ARKUI_CLIP_TYPE_ELLIPSE,
    /** Path. */
    ARKUI_CLIP_TYPE_PATH,
} ArkUI_ClipType;

/**
 * @brief Defines the gradient color stop structure.
 *
 * @since 12
 */
typedef struct {
    /** Color array. */
    const uint32_t* colors;
    /** Position array. */
    float* stops;
    /** Length array. */
    int size;
} ArkUI_ColorStop;

/**
 * @brief Enumerates the custom shapes.
 *
 * @since 12
 */
typedef enum {
    /** Rectangle. */
    ARKUI_SHAPE_TYPE_RECTANGLE = 0,
    /** Circle. */
    ARKUI_SHAPE_TYPE_CIRCLE,
    /** Ellipse. */
    ARKUI_SHAPE_TYPE_ELLIPSE,
    /** Path. */
    ARKUI_SHAPE_TYPE_PATH,
} ArkUI_ShapeType;

/**
 * @brief Enumerates the gradient directions.
 *
 * @since 12
 */
typedef enum {
    /** From right to left. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT = 0,
    /** From bottom to top. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_TOP,
    /** From left to right. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT,
    /** From top to bottom. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_BOTTOM,
    /** From lower right to upper left. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_TOP,
    /** From upper right to lower left. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_LEFT_BOTTOM,
    /** From lower left to upper right. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_TOP,
    /** From upper left to lower right. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_RIGHT_BOTTOM,
    /** No gradient. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_NONE,
    /** Custom direction. */
    ARKUI_LINEAR_GRADIENT_DIRECTION_CUSTOM,
} ArkUI_LinearGradientDirection;

/**
 * @brief Enumerates the word break rules.
 *
 * @since 12
 */
typedef enum {
    /** Word breaks can occur between any two characters for Chinese, Japanese, and Korean (CJK) text, but can occur
     *  only at a space character for non-CJK text (such as English). */
    ARKUI_WORD_BREAK_NORMAL = 0,
    /** Word breaks can occur between any two characters for non-CJK text. CJK text behavior is the same as for
     *  <b>NORMAL</b>. */
    ARKUI_WORD_BREAK_BREAK_ALL,
    /** This option has the same effect as <b>BREAK_ALL</b> for non-CJK text, except that if it preferentially wraps
     *  lines at appropriate characters (for example, spaces) whenever possible.
        CJK text behavior is the same as for <b>NORMAL</b>. */
    ARKUI_WORD_BREAK_BREAK_WORD,
} ArkUI_WordBreak;

/**
 * @brief Enumerates the ellipsis positions.
 *
 * @since 12
 */
typedef enum {
    /** An ellipsis is used at the start of the line of text. */
    ARKUI_ELLIPSIS_MODE_START = 0,
    /** An ellipsis is used at the center of the line of text. */
    ARKUI_ELLIPSIS_MODE_CENTER,
    /** An ellipsis is used at the end of the line of text. */
    ARKUI_ELLIPSIS_MODE_END,
} ArkUI_EllipsisMode;

/**
 * @brief Enumerates the image rendering modes.
 *
 * @since 12
 */
typedef enum {
    /** Render image pixels as they are in the original source image. */
    ARKUI_IMAGE_RENDER_MODE_ORIGINAL = 0,
    /** Render image pixels to create a monochrome template image. */
    ARKUI_IMAGE_RENDER_MODE_TEMPLATE,
} ArkUI_ImageRenderMode;

/**
 * @brief Enumerates the slide-in and slide-out positions of the component from the screen edge during transition.
 *
 * @since 12
 */
typedef enum {
    /** Top edge of the window. */
    ARKUI_TRANSITION_EDGE_TOP = 0,
    /** Bottom edge of the window. */
    ARKUI_TRANSITION_EDGE_BOTTOM,
    /** Left edge of the window. */
    ARKUI_TRANSITION_EDGE_START,
    /** Right edge of the window. */
    ARKUI_TRANSITION_EDGE_END,
} ArkUI_TransitionEdge;

/**
 * @brief Defines how the specified blend mode is applied.
 *
 * @since 12
 */
typedef enum {
    /** The content of the view is blended in sequence on the target image. */
    BLEND_APPLY_TYPE_FAST = 0,
    /** The content of the component and its child components are drawn on the offscreen canvas, and then blended with
    the existing content on the canvas. */
    BLEND_APPLY_TYPE_OFFSCREEN,
} ArkUI_BlendApplyType;

/**
 * @brief Defines a mask area.
 *
 * @since 12
 */
typedef struct {
    /** X coordinate of the mask area. */
    float x;
    /** Y coordinate of the mask area. */
    float y;
    /** Width of the mask area. */
    float width;
    /** Height of the mask area. */
    float height;
} ArkUI_Rect;

/**
 * @brief Describes the width and height of a component.
 *
 * @since 12
 */
typedef struct {
    /** Width, in px. */
    int32_t width;
    /** Height, in px. */
    int32_t height;
} ArkUI_IntSize;

/**
 * @brief Describes the position of a component.
 *
 * @since 12
 */
typedef struct {
    /** Horizontal coordinate, in px. */
    int32_t x;
    /** Vertical coordinate, in px. */
    int32_t y;
} ArkUI_IntOffset;


/**
 * @brief Describes the margins of a component.
 *
 * @since 12
 */
typedef struct {
    /** Top margin, in vp. */
    float top;
    /** Right margin, in vp. */
    float right;
    /** Bottom margin, in vp. */
    float bottom;
    /** Left margin, in vp. */
    float left;
} ArkUI_Margin;

/**
 * @brief Enumerates the animation onFinish callback types.
 *
 * @since 12
 */
typedef enum {
    /** The callback is invoked when the entire animation is removed once it has finished. */
    ARKUI_FINISH_CALLBACK_REMOVED = 0,
    /** The callback is invoked when the animation logically enters the falling state, though it may still be in its
      * long tail state. */
    ARKUI_FINISH_CALLBACK_LOGICALLY,
} ArkUI_FinishCallbackType;

/**
 * @brief 交叉轴方向的布局方式。
  *
 * @since 12
 */
typedef enum {
     /** ListItem在List中，交叉轴方向首部对齐。 */
    ARKUI_LIST_ITEM_ALIGN_START = 0,
    /** ListItem在List中，交叉轴方向居中对齐。*/
    ARKUI_LIST_ITEM_ALIGN_CENTER,
    /** ListItem在List中，交叉轴方向尾部对齐。*/
    ARKUI_LIST_ITEM_ALIGN_END,
} ArkUI_ListItemAlign;

/**
 * @brief Enumerates the component units.
 *
 * @since 12
 */
typedef enum {
    /** Default, which is fp for fonts and vp for non-fonts. */
    ARKUI_LENGTH_METRIC_UNIT_DEFAULT = -1,
    /** px. */
    ARKUI_LENGTH_METRIC_UNIT_PX = 0,
    /** vp. */
    ARKUI_LENGTH_METRIC_UNIT_VP,
    /** fp. */
    ARKUI_LENGTH_METRIC_UNIT_FP
} ArkUI_LengthMetricUnit;

/**
* @brief Creates a size constraint.
*
* @since 12
*/
ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Create();

/**
* @brief Creates a deep copy of a size constraint.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the pointer to the new size constraint.
* @since 12
*/
ArkUI_LayoutConstraint* OH_ArkUI_LayoutConstraint_Copy(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Destroys the pointer to a size constraint.
*
* @param Constraint Indicates the pointer to the size constraint.
* @since 12
*/
void* OH_ArkUI_LayoutConstraint_Dispose(ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the maximum width for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the maximum width.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMaxWidth(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the minimum width for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the minimum width.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMinWidth(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the maximum height for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the maximum height.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMaxHeight(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the minimum height for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the minimum height.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetMinHeight(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the width percentage reference for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the width percentage reference.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceWidth(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Obtains the height percentage reference for a size constraint, in px.
*
* @param Constraint Indicates the pointer to the size constraint.
* @return Returns the height percentage reference.
* @since 12
*/
int32_t OH_ArkUI_LayoutConstraint_GetPercentReferenceHeight(const ArkUI_LayoutConstraint* Constraint);

/**
* @brief Sets the maximum width.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the maximum width, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMaxWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the minimum width.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the minimum width, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMinWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the maximum height.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the maximum height, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMaxHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the minimum height.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the minimum height, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetMinHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the width percentage reference.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the width percentage reference, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetPercentReferenceWidth(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Sets the height percentage reference.
*
* @param Constraint Indicates the pointer to the size constraint.
* @param value Indicates the height percentage reference, in px.
* @since 12
*/
void OH_ArkUI_LayoutConstraint_SetPercentReferenceHeight(ArkUI_LayoutConstraint* Constraint, int32_t value);

/**
* @brief Obtains the pointer to a canvas for drawing, which can be converted into the <b>OH_Drawing_Canvas</b> pointer
* in the <b>Drawing</b> module.
*
* @param context Indicates the pointer to the drawing context.
* @return Returns the pointer to the canvas for drawing.
* @since 12
*/
void* OH_ArkUI_DrawContext_GetCanvas(ArkUI_DrawContext* context);

/**
* @brief Obtains the size of a drawing area.
*
* @param context Indicates the pointer to the drawing context.
* @return Returns the size of the drawing area.
* @since 12
*/
ArkUI_IntSize OH_ArkUI_DrawContext_GetSize(ArkUI_DrawContext* context);

/**
* @brief Creates water flow section configuration.
*
* @return Returns the water flow section configuration.
* @since 12
*/
ArkUI_WaterFlowSectionOption* OH_ArkUI_WaterFlowSectionOption_Create();

/**
* @brief Destroys the pointer to a water flow section configuration.
*
* @param option Indicates the pointer to a water flow section configuration.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_Dispose(ArkUI_WaterFlowSectionOption* option);

/**
* @brief Sets the number of items in a water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param itemCount Indicates the number of items in the water flow section.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetItemCount(ArkUI_WaterFlowSectionOption* option,
    int32_t index, int32_t itemCount);

/**
* @brief Obtains the number of items in the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the number of items in the water flow section.
* @since 12
*/
int32_t OH_ArkUI_WaterFlowSectionOption_GetItemCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the number of columns (in a vertical layout) or rows (in a horizontal layout) of a water flow.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param crossCount Indicates the number of columns or rows, depending on the layout direction.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetCrossCount(ArkUI_WaterFlowSectionOption* option,
    int32_t index, int32_t crossCount);

/**
* @brief Obtains the number of columns (in a vertical layout) or rows (in a horizontal layout) in the water flow section
* that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the number of columns or rows.
* @since 12
*/
int32_t OH_ArkUI_WaterFlowSectionOption_GetCrossCount(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the gap between columns in the specified water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param columnGap Indicates the gap between columns to set.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetColumnGap(ArkUI_WaterFlowSectionOption* option,
    int32_t index, float columnGap);

/**
* @brief Obtains the gap between columns in the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the gap between columns.
* @since 12
*/
float OH_ArkUI_WaterFlowSectionOption_GetColumnGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the gap between rows in the specified water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param rowGap Indicates the gap between rows to set.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetRowGap(ArkUI_WaterFlowSectionOption* option,
    int32_t index, float rowGap);

/**
* @brief Obtains the gap between rows in the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the gap between rows.
* @since 12
*/
float OH_ArkUI_WaterFlowSectionOption_GetRowGap(ArkUI_WaterFlowSectionOption* option, int32_t index);

/**
* @brief Sets the margins for the specified water flow section.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @param marginTop Indicates the top margin of the water flow section.
* @param marginRight Indicates the right margin of the water flow section.
* @param marginBottom Indicates the bottom margin of the water flow section.
* @param marginLeft Indicates the left margin of the water flow section.
* @since 12
*/
void OH_ArkUI_WaterFlowSectionOption_SetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index,
    float marginTop, float marginRight, float marginBottom, float marginLeft);

/**
* @brief Obtains the margins of the water flow section that matches the specified index.
*
* @param option Indicates the pointer to a water flow section configuration.
* @param index Indicates the index of the target water flow section.
* @return Returns the margins.
* @since 12
*/
ArkUI_Margin OH_ArkUI_WaterFlowSectionOption_GetMargin(ArkUI_WaterFlowSectionOption* option, int32_t index);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_TYPE_H
/** @} */
