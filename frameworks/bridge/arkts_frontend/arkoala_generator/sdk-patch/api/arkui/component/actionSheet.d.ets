
'use static'
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * @file
 * @kit ArkUI
 */
import { Resource } from '../../global/resource';
import { VoidCallback, ResourceStr, ResourceColor, Dimension, BorderRadiuses, LocalizedEdgeColors, EdgeColors, EdgeWidths, LocalizedEdgeWidths, EdgeStyles, LocalizedBorderRadiuses } from './units';
// instructive change start
import { Callback, DismissReason, Rectangle, BlurStyle, TransitionEffect, ShadowOptions, HoverModeAreaType, ShadowStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, SystemUiMaterial } from './common';
// instructive change end
import { DialogButtonStyle, BorderStyle } from './enums';
import { DialogAlignment } from './alertDialog';
import { LevelOrder, LevelMode, ImmersiveMode } from '../../@ohos.promptAction';
import { AttributeModifier, CommonMethod } from './common';
/**
 * The information of sheet.
 *
 * @interface SheetInfo
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export interface SheetInfo {
    /**
     * Sheet text.
     *
     * @type { string | Resource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    title: string | Resource;
    /**
     * Sheet icon. By default, no icon is displayed.
     *
     * @type { ?(string | Resource) }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    icon?: string | Resource;
    /**
     * Callback when the sheet is selected.
     * Anonymous Object Rectification.
     *
     * @type { VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: VoidCallback;
}
/**
 * Provides information about the action to dismiss the dialog box.
 *
 * @interface DismissDialogAction
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface DismissDialogAction {
    /**
     * Defines dialog dismiss function.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    dismiss(): void;
    /**
     * Reason why the dialog box cannot be dismissed. You must specify whether to close the dialog box for each of the
     * listed actions.
     *
     * @type { DismissReason }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    reason: DismissReason;
}
/**
 * Base button params used for ActionSheet.
 *
 * @interface ActionSheetButtonOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export interface ActionSheetButtonOptions {
    /**
     * Whether to respond when the button is clicked. The value true means to respond when the button is clicked,
     * and false means the opposite.
     * Anonymous Object Rectification.
     *
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enabled?: boolean;
    /**
     * Whether the button is the default focus. The value true means that the button is the default focus,
     * and false means the opposite.
     * Anonymous Object Rectification.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    defaultFocus?: boolean;
    /**
     * Button style.
     * Anonymous Object Rectification.
     *
     * @type { ?DialogButtonStyle }
     * @default DialogButtonStyle.DEFAULT
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    style?: DialogButtonStyle;
    /**
     * Button text.
     * Anonymous Object Rectification.
     *
     * @type { string | Resource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    value: string | Resource;
    /**
     * Callback invoked when the button is selected.
     * Anonymous Object Rectification.
     *
     * @type { VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    action: VoidCallback;
}
/**
 * ActionSheet offset.
 *
 * @interface ActionSheetOffset
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export interface ActionSheetOffset {
    /**
     * Offset of the action sheet along the x-axis relative to the alignment position.
     * Anonymous Object Rectification.
     *
     * @type { double | string | Resource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    dx: double | string | Resource;
    /**
     * Offset of the action sheet along the y-axis relative to the alignment position.
     * Anonymous Object Rectification.
     *
     * @type { double | string | Resource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    dy: double | string | Resource;
}
/**
 * The options of ActionSheet.
 *
 * @interface ActionSheetOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export interface ActionSheetOptions {
    /**
     * Title of the dialog box.
     *
     * @type { string | Resource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    title: string | Resource;
    /**
     * Subtitle of the dialog box.
     * @type { ?ResourceStr }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    subtitle?: ResourceStr;
    /**
     * Content of the dialog box.
     *
     * @type { string | Resource }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    message: string | Resource;
    /**
     * Information about the confirm button. When the dialog box has focus and focus has not been shifted using the Tab
     * key, the button responds to the Enter key by default, and multiple dialog boxes can gain focus consecutively
     * to respond automatically. The default response to the Enter key does not work when defaultFocus is set to true.
     *
     * @type { ?ActionSheetButtonOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    confirm?: ActionSheetButtonOptions;
    /**
     * Callback invoked when the dialog box is closed after the overlay is clicked.
     * Anonymous Object Rectification.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    cancel?: VoidCallback;
    /**
     * Options in the dialog box. Each option supports the image, text, and callback.
     *
     * @type { Array<SheetInfo> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    sheets: Array<SheetInfo>;
    /**
     * Whether to close the dialog box when the overlay is clicked.
     *
     * @type { ?boolean }
     * @default true - The value true means to close the dialog box when the overlay is clicked, and false means
     * the opposite.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    autoCancel?: boolean;
    /**
     * Alignment mode of the dialog box in the vertical direction.
     * <p><strong>NOTE</strong>:
     * <br>If showInSubWindow is set to true in UIExtension, the dialog box is aligned with the host window based
     * on UIExtension.
     * </p>
     *
     * @type { ?DialogAlignment }
     * @default DialogAlignment.Bottom
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    alignment?: DialogAlignment;
    /**
     * Offset of the dialog box relative to the alignment position.
     * <br>When alignment is set to Top, TopStart, or TopEnd: {dx: 0,dy: "40vp"}
     * <br>When alignment is set to any other value: {dx: 0,dy: "-40vp"}
     *
     * @type { ?ActionSheetOffset }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offset?: ActionSheetOffset;
    /**
     * Mask area of the dialog box. Events outside the mask area are transparently transmitted,
     * and events within the mask area are not.
     * <p><strong>NOTE</strong>:
     * <br>maskRect does not take effect when showInSubWindow is set to true.
     * </p>
     *
     * @type { ?Rectangle }
     * @default - {x:0,y:0, width:'100%', height:'100%'}
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    maskRect?: Rectangle;
    /**
     * Whether to show the dialog box in a subwindow when the dialog box needs to be displayed outside the main window.
     * <p><strong>NOTE</strong>:
     * <br>A dialog box whose showInSubWindow attribute is true cannot trigger the display of another dialog box whose
     * showInSubWindow attribute is also true.
     * </p>
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    showInSubWindow?: boolean;
    /**
     * Whether the dialog box is a modal. A modal dialog box has a mask applied, while a non-modal dialog box does not.
     * @type { ?boolean }
     * @default true
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    isModal?: boolean;
    /**
     * Background color of the dialog box.
     * <p><strong>NOTE</strong>:
     * <br>When backgroundColor is set to a non-transparent color, backgroundBlurStyle must be set to BlurStyle.NONE;
     * otherwise, the color display may not meet the expected effect.
     * </p>
     *
     * @type { ?ResourceColor }
     * @default Color.Transparent
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundColor?: ResourceColor;
    /**
     * Background blur style of the dialog box.
     * <p><strong>NOTE</strong>:
     * <br>Setting this parameter to BlurStyle.NONE disables the background blur. When backgroundBlurStyle is set to a
     * value other than NONE, do not set backgroundColor. If you do, the color display may not produce the expected
     * visual effect.
     * </p>
     *
     * @type { ?BlurStyle }
     * @default BlurStyle.COMPONENT_ULTRA_THICK
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyle?: BlurStyle;
    /**
     * Defines the actionSheet's background blur style with options
     *
     * @type { ?BackgroundBlurStyleOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    /**
     * Defines the actionSheet's background effect with options
     *
     * @type { ?BackgroundEffectOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    backgroundEffect?: BackgroundEffectOptions;
    /**
     * Callback for interactive closure of the dialog box.
     * <p><strong>NOTE</strong>:
     * 1. If this callback is registered, the dialog box will not be closed immediately after the user touches the
     * mask or the Back button, presses the Esc key, or swipes left or right on the screen. The reason parameter in
     * the callback is used to determine whether the dialog box can be closed. The reason returned by the component
     * does not support the value CLOSE_BUTTON.
     * 2. In the onWillDismiss callback, another onWillDismiss callback is not allowed.
     * </p>
     *
     * @type { ?Callback<DismissDialogAction> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDismiss?: Callback<DismissDialogAction>;
    /**
     * Transition effect for the entrance and exit of the dialog box.
     * <p><strong>NOTE</strong>:
     * 1. If this parameter is not set, the default effect is used.
     * 2. Touching the Back button during the entrance animation pauses the entrance animation and starts the exit
     * animation. The final effect is one obtained after the curves of the entrance and exit animations are combined.
     * 3. Touching the Back button during the exit animation does not affect the animation playback. Touching the
     * Back button again closes the application.
     * </p>
     *
     * @type { ?TransitionEffect }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    transition?: TransitionEffect;
    /**
     * Corner radius of the background. You can set the radius for each of the four corners individually.
     *
     * @type { ?(Dimension | BorderRadiuses | LocalizedBorderRadiuses) }
     * @default - {topLeft:'32vp', topRight:'32vp', bottomLeft:'32vp', bottomRight:'32vp'}, The corner radius is subject
     * to the component size, with the maximum value being half of the component width or height. If the value is
     * negative, the default value is used. When set to a percentage, the value defines the radius as a percentage of
     * the parent component's width or height.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    cornerRadius?: Dimension | BorderRadiuses | LocalizedBorderRadiuses;
    /**
     * Width of the dialog box.
     *
     * @type { ?Dimension }
     * @default - Default maximum width of the dialog box: 400 vp,
     * When this parameter is set to a percentage, the reference width of the dialog box is the width of the window
     * where the dialog box is located. You can decrease or increase the width as needed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    width?: Dimension;
    /**
     * Height of the dialog box.
     *
     * @type { ?Dimension }
     * @default - Default maximum height of the dialog box: 0.9 x (Window height – Safe area)
     * <br>When this parameter is set to a percentage, the reference height of the dialog box is the height of the
     * window where the dialog box is located minus the safe area. You can decrease or increase the height as needed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    height?: Dimension;
    /**
     * Border width of the dialog box.
     * You can set the width for all four sides or set separate widths for individual sides.
     *
     * @type { ?(Dimension | EdgeWidths | LocalizedEdgeWidths) }
     * @default 0 - When set to a percentage, the value defines the border width as a percentage of the parent dialog
     * box's width. If the left and right borders are greater than its width, or the top and bottom borders are greater
     * than its height, the dialog box may not display as expected.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderWidth?: Dimension | EdgeWidths | LocalizedEdgeWidths;
    /**
     * Border color of the dialog box.
     * <p><strong>NOTE</strong>:
     * <br>When borderColor is of type LocalizedEdgeColors, the layout order can be dynamically adjusted based on the
     * user's language settings.
     * </p>
     *
     * @type { ?(ResourceColor | EdgeColors | LocalizedEdgeColors) }
     * @default Color.Black - borderColor must be used with borderWidth in pairs.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderColor?: ResourceColor | EdgeColors | LocalizedEdgeColors;
    /**
     * Border style of the dialog box.
     *
     * @type { ?(BorderStyle | EdgeStyles) }
     * @default BorderStyle.Solid - borderStyle must be used with borderWidth in pairs.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    borderStyle?: BorderStyle | EdgeStyles;
    /**
     * Shadow of the dialog box.
     *
     * @type { ?(ShadowOptions | ShadowStyle) }
     * @default - Default value on 2-in-1 devices: ShadowStyle.OUTER_FLOATING_MD when the dialog box is focused and
     * ShadowStyle.OUTER_FLOATING_SM otherwise.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    shadow?: ShadowOptions | ShadowStyle;
    /**
     * Whether to enable the hover mode.
     *
     * @type { ?boolean }
     * @default false - meaning not to enable the hover mode.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    enableHoverMode?: boolean;
    /**
     * Display area of the dialog box in hover mode.
     *
     * @type { ?HoverModeAreaType }
     * @default HoverModeAreaType.BOTTOM_SCREEN
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    hoverModeArea?: HoverModeAreaType;
    /**
     * Callback function when the dialog appears.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onDidAppear?: VoidCallback;
    /**
     * Callback function when the dialog disappears.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onDidDisappear?: VoidCallback;
    /**
     * Callback function before the dialog openAnimation starts.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillAppear?: VoidCallback;
    /**
     * Callback function before the dialog closeAnimation starts.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onWillDisappear?: VoidCallback;
    /**
     * Display level of the dialog box.
     *
     * @type { ?LevelMode }
     * @default LevelMode.OVERLAY - This parameter takes effect only when showInSubWindow is set to false.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    levelMode?: LevelMode;
    /**
     * Unique ID of the node under the display level for the page-level dialog box.
     * <p><strong>NOTE</strong>:
     * <br>This parameter takes effect only when levelMode is set to LevelMode.EMBEDDED.
     * </p>
     *
     * @type { ?int }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    levelUniqueId?: int;
    /**
     * Overlay effect for the page-level dialog box.
     *
     * @type { ?ImmersiveMode }
     * @default ImmersiveMode.DEFAULT - This parameter takes effect only when levelMode is set to LevelMode.EMBEDDED.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    immersiveMode?: ImmersiveMode;
    /**
     * Determine the display order of the dialog.
     *
     * @type { ?LevelOrder }
     * @default The value returns by LevelOrder.clamp(0)
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    levelOrder?: LevelOrder;
    systemMaterial?: SystemUiMaterial;
}
