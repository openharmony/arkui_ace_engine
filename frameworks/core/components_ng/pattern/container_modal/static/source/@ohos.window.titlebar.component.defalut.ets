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

import {
  _r,
  Builder,
  Button,
  ButtonType,
  ClickEvent,
  Color,
  Column,
  Component,
  ContextMenuOptions,
  Entry,
  FlexAlign,
  GestureGroup,
  GestureMode,
  HitTestMode,
  HoverEffect,
  HoverEvent,
  Image,
  ImageInterpolation,
  LongPressGesture,
  Margin,
  Padding,
  PanGesture,
  Placement,
  Rectangle,
  Resource,
  ResourceColor,
  Row,
  RowOptions,
  ScaleOptions,
  SizeOptions,
  Stack,
  TapGesture,
  Text,
  TextAlign,
  TextOverflow,
  TouchEvent,
  VerticalAlign,
  Visibility,
  AnimateParam,
  UIContext
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

import image from '@ohos.multimedia.image';

const TITLE_ICON_SIZE: string = '20vp'
const TITLE_PADDING_START: string = '20vp'
const TITLE_ELEMENT_MARGIN_HORIZONTAL: string = '12vp'
const TITLE_TEXT_FONT_SIZE: string = '16vp'
const TITLE_TEXT_FONT_WEIGHT: string = '500px'
const TITLE_ROW_HEIGHT: string = '37vp'


const IMAGE_SIZE: string = '20vp'
const BUTTON_SIZE: string = '28vp'
const BUTTON_ELEMENT_MARGIN_HORIZONTAL: string = '12vp'
const BUTTON_ELEMENT_MARGIN_HORIZONTAL_END: string = '8vp'
const TITLE_BUTTON_RESPONSE_REGION_OFFSET_X: string = '-8vp'
const TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y: string = '-8vp'
const TITLE_BUTTON_RESPONSE_REGION_WIDTH: string = '40vp'
const TITLE_BUTTON_RESPONSE_REGION_HEIGHT: string = '40vp'

const MENU_ICON_SIZE: string = '24vp'
const MENU_MARGIN_V: string = '8vp'
const MENU_MARGIN_H: string = '12vp'
const MENU_TITLE_MARGIN_V: string = '10vp'
const MENU_TITLE_TEXT_FONT_SIZE: string = '16vp'
const HOVER_TIME: int = 1000; // Hover time: 1000ms
const MENU_AUTO_DISAPPEAR_TIME: int = 2000; // Menu auto-disappear: 2000ms
const MENU_MOUSEOUT_DISAPPEAR_TIME: int = 1000; // Menu mouseout disappear: 1000ms

const EVENT_NAME_CUSTOM_MAX_CLICK: string = 'arkui_custom_max_click'
const EVENT_NAME_MIN_CLICK: string = 'arkui_custom_min_click'
const EVENT_NAME_CLOSE_CLICK: string = 'arkui_custom_close_click'
const EVENT_NAME_LEFT_SPLIT_CLICK: string = 'arkui_custom_left_split_click'
const EVENT_NAME_RIGHT_SPLIT_CLICK: string = 'arkui_custom_right_split_click'
const EVENT_NAME_BUTTON_POINT_LIGHT_ANIM: string = 'arkui_custom_button_point_light_anim'
const EVENT_NAME_BUTTON_RECT_CHANGE: string = 'arkui_custom_button_rect_change'
const EVENT_NAME_CUSTOM_MENU_WIDTH_CHANGE: string = 'arkui_custom_menu_width_change'

const EVENT_NAME_COLOR_CONFIGURATION: string = 'arkui_color_configuration'
const EVENT_NAME_HIDE_SPLIT: string = 'arkui_hide_split'
const EVENT_NAME_MAXIMIZE_VISIBILITY: string = 'arkui_maximize_visibility'
const EVENT_NAME_MINIMIZE_VISIBILITY: string = 'arkui_minimize_visibility'
const EVENT_NAME_CLOSE_VISIBILITY: string = 'arkui_close_visibility'
const EVENT_NAME_CLOSE_STATUS: string = 'arkui_close_status'
const EVENT_NAME_MAXIMIZE_IS_RECOVER: string = 'arkui_maximize_is_recover'
const EVENT_NAME_MENU_WIDTH_CHANGE: string = 'arkui_menu_width_change'
const EVENT_NAME_BUTTON_SIZE_CHANGE: string = 'arkui_button_size_change'
const EVENT_NAME_BUTTON_SPACING_CHANGE: string = 'arkui_button_spacing_change'
const EVENT_NAME_COLOR_MODE_LOCKED: string = 'arkui_color_mode_locked'
const EVENT_NAME_BUTTON_RIGHT_OFFSET_CHANGE: string = 'arkui_button_right_offset_change'

const maximizeNormalResource: Resource = _r(125829923, 20000, '', '')

const recoverNormalResource: Resource = _r(125829925, 20000, '', '')

const buttonNormalBackgroundColor: Color = Color.Transparent

const buttonNormalIconFillColor: Resource = _r(125830991, 10001, '', '')

const buttonHoverBackgroundColor: Resource = _r(125834289, 10001, '', '')

const buttonHoverIconFillColor: Resource = _r(125830991, 10001, '', '')

const closeNormalBackgroundColor: Color = Color.Transparent

const closeNormalIconFillColor: Resource = _r(125830991, 10001, '', '')

const closeHoverBackgroundColor: Resource = _r(125830979, 10001, '', '')

const closeHoverIconFillColor: Resource = _r(125831057, 10001, '', '')

const menuHoverColor: Resource = _r(125831024, 10001, '', '')

const splitItemFillColor: Resource = _r(125830991, 10001, '', '')

// lock the dark or light color mode
class ColorGroup {
  public light: string = '#000000';
  public dark: string = '#FFFFFF';

  constructor(light: string, dark: string) {
    this.dark = dark;
    this.light = light;
  }
}

const colorMap: Map<Resource, ColorGroup> = new Map<Resource, ColorGroup>([
  [buttonNormalIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
  [buttonHoverBackgroundColor, new ColorGroup('#0C000000', '#26FFFFFF')],
  [buttonHoverIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
  [closeNormalIconFillColor, new ColorGroup('#182431', '#e5ffffff')],
  [closeHoverBackgroundColor, new ColorGroup('#FA2A2D', '#E64548')],
  [closeHoverIconFillColor, new ColorGroup('#ffffff', '#ffffff')],
  [menuHoverColor, new ColorGroup('#19182431', '#19ffffff')],
  [splitItemFillColor, new ColorGroup('#182431', '#e5ffffff')],
]);


@Component
struct System__Reserved_$$$__UI__TitleBar__Component {
  @State appLabel: string = '';
  @State appTitle: string = '';
  @State appLabelColor: string = '#ff000000';
  @State pixelMap: image.PixelMap | string = '';
  @State iconOpacity: number = 1;

  onWindowFocused() {
    this.appLabelColor = '#ff000000';
    this.iconOpacity = 1;
    hilog.info(0x0000, 'testTag', 'onWindowFocused');
  }

  onWindowUnfocused() {
    this.appLabelColor = '#66000000';
    this.iconOpacity = 0.4;
    hilog.info(0x0000, 'testTag', 'onWindowUnfocused');
  }

  setAppTitle(content: string) {
    this.appTitle = content;
  }

  setAppIcon(pixelMap: image.PixelMap) {
    this.pixelMap = pixelMap;
  }

  build() {
    Row() {
      Image(this.pixelMap)
        .id("enhanceAppIcon")
        .height(TITLE_ICON_SIZE)
        .width(TITLE_ICON_SIZE)
        .interpolation(ImageInterpolation.Medium)
        .focusable(false)
        .margin({ left: TITLE_ELEMENT_MARGIN_HORIZONTAL, right: TITLE_ELEMENT_MARGIN_HORIZONTAL } as Margin)
        .opacity(this.iconOpacity)
        .draggable(false)
      Text(this.appTitle ? this.appTitle : this.appLabel)
        .id("enhanceAppLabel")
        .fontSize(TITLE_TEXT_FONT_SIZE)
        .fontColor(this.appLabelColor)
        .fontWeight(TITLE_TEXT_FONT_WEIGHT)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .textAlign(TextAlign.Start)
        .opacity(this.iconOpacity)
        .flexShrink(1)
        .minFontScale(0.85)
        .maxFontScale(1.45)
    }
    .width('100%')
    .height(TITLE_ROW_HEIGHT)
    .justifyContent(FlexAlign.Start)
    .alignItems(VerticalAlign.Center)
    .clip(true)
    .padding({
      top: 6,
      bottom: 6,
      left: 8,
      right: 8
    } as Padding)
  }
}

@Component
struct System__Reserved_$$$__UI__ButtonBar__Component {
  @State maximizeResource: Resource = maximizeNormalResource
  @State minimizeResource: Resource = _r(125829924, 20000, '', '')
  @State closeResource: Resource = _r(125829917, 20000, '', '')
  @State menuLeftResource: Resource = _r(125830147, 20000, '', '')
  @State menuRightResource: Resource = _r(125830148, 20000, '', '')
  @State maximizeBackgroundColor: Resource | Color | string = buttonNormalBackgroundColor
  @State minimizeBackgroundColor: Resource | Color | string = buttonNormalBackgroundColor
  @State closeBackgroundColor: Resource | Color | string = buttonNormalBackgroundColor
  @State maximizeFillColor: Resource | Color | string = buttonNormalIconFillColor
  @State minimizeFillColor: Resource | Color | string = buttonNormalIconFillColor
  @State closeFillColor: Resource | Color | string = buttonNormalIconFillColor
  @State maximizeScale: number = 1.0
  @State minimizeScale: number = 1.0
  @State closeScale: number = 1.0
  @State rowVisibility: Visibility = Visibility.Visible
  @State maximizeVisibility: Visibility = Visibility.Visible
  @State minimizeVisibility: Visibility = Visibility.Visible
  @State closeVisibility: Visibility = Visibility.Visible
  @State closeStatus: boolean = true
  @State isShowMenu: boolean = false
  @State leftSplitTitle: Resource = _r(125833961, 10003, '', '')
  @State rightSplitTitle: Resource = _r(125833962, 10003, '', '')
  @State splitFillColor: Resource | Color | string = splitItemFillColor
  @State leftSplitBackgroundColor: ResourceColor = Color.Transparent
  @State rightSplitBackgroundColor: ResourceColor = Color.Transparent
  @State rowOpacity: number = 1.0
  @State menuWidth: string = '224vp';
  // button spacing between hotArea 12-28vp
  @State buttonSpacing: number = 12;
  // button size 20-28vp
  @State buttonSize: number = 28;
  // spacing from the last button to the right
  @State buttonRightOffset: number = 20;
  // lock the current color mode
  colorConfigurationLocked: boolean = false;
  isFocused: boolean = true;
  isDark: boolean = false;
  isHoverShowMenu: boolean = false
  showMenuTimeoutId: int = -1
  menuDisappearTimeoutId: int = -1
  hideSplit: boolean = false

  onWindowFocused() {
    this.rowOpacity = 1.0;
    this.isFocused = true;
  }

  onWindowUnfocused() {
    this.rowOpacity = 0.4;
    this.isFocused = false;
  }

  parseBoolean(value: string): boolean {
    if (value === 'true') {
      return true
    }
    return false
  }

  setCustomCallback(eventName: string, param: string) {
    if (eventName === EVENT_NAME_COLOR_CONFIGURATION) {
      this.onColorConfigurationUpdate(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_HIDE_SPLIT) {
      this.setHideSplit(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_MAXIMIZE_VISIBILITY) {
      this.setMaximizeVisibility(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_MINIMIZE_VISIBILITY) {
      this.setMinimizeVisibility(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_CLOSE_VISIBILITY) {
      this.setCloseVisibility(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_CLOSE_STATUS) {
      this.setCloseStatus(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_MAXIMIZE_IS_RECOVER) {
      this.setMaximizeIsRecover(this.parseBoolean(param))
    } else if (eventName === EVENT_NAME_MENU_WIDTH_CHANGE) {
      this.setMenuWidth(param)
    } else if (eventName === EVENT_NAME_BUTTON_SPACING_CHANGE) {
      this.setButtonSpacing(param);
    } else if (eventName === EVENT_NAME_COLOR_MODE_LOCKED) {
      this.setColorModeLocked(param);
    } else if (eventName === EVENT_NAME_BUTTON_RIGHT_OFFSET_CHANGE) {
      this.setButtonRightOffset(param);
    } else if (eventName === EVENT_NAME_BUTTON_SIZE_CHANGE) {
      this.setButtonButtonSize(param);
    }
  }

  // set the spacing between buttons
  setButtonSpacing(param: string) {
    this.buttonSpacing = parseInt(param);
  }

  // set button size
  setButtonButtonSize(param: string) {
    this.buttonSize = parseInt(param);
  }

  // the last button right offset
  setButtonRightOffset(param: string) {
    this.buttonRightOffset = parseInt(param);
  }

  // lock current button color
  setColorModeLocked(param: string) {
    const colorMode = parseInt(param);
    if (colorMode === -1) {
      this.colorConfigurationLocked = false;
      return;
    }
    // lock color mode
    this.isDark = (colorMode === 0);
    this.colorConfigurationLocked = true;
    this.maximizeFillColor = this.getResourceColor(buttonNormalIconFillColor)
    this.minimizeFillColor = this.getResourceColor(buttonNormalIconFillColor)
    this.closeFillColor = this.getResourceColor(buttonNormalIconFillColor)
    this.splitFillColor = this.getResourceColor(splitItemFillColor)
  }

  // get resource color for lock color mode
  getResourceColor(resource: Resource): Resource | string {
    if (this.colorConfigurationLocked && colorMap.has(resource)) {
      const colorGroup = colorMap.get(resource);
      if (colorGroup) {
        return this.isDark ? colorGroup.dark : colorGroup.light;
      }
    }
    return resource;
  }

  getMethodByName(objType: ClassType, name: string): Method | undefined {
    for (let methodIdx = 0; methodIdx < objType.getMethodsNum(); ++methodIdx) {
      const method = objType.getMethod(methodIdx)
      if (method.getName() == name) {
        return method
      }
    }
    return undefined
  }

  callNative(xBarType: int, eventType: string, message: string) {
    let reflectedType: Type | undefined = Type.resolve("arkui.XBarProxy.XBarProxy")
    if (reflectedType === undefined) {
      hilog.info(0x0000, 'testTag', "xBarType: " + xBarType);
      hilog.info(0x0000, 'testTag', "eventType: " + eventType);
      hilog.info(0x0000, 'testTag', "message: " + message);
      return
    }
    try {
      let objType: ClassType = reflectedType as ClassType
      let targetMethod: Method | undefined = this.getMethodByName(objType, "CallNative");
      if (targetMethod === undefined) {
        hilog.info(0x0000, 'testTag', "targetMethod === undefined");
        return;
      }
      targetMethod.invoke(null, [xBarType, eventType, message]);
    } catch (e) {
      hilog.info(0x0000, 'testTag', "exception: " + e);
    }
  }

  onMaximizeButtonClick() {
    this.onCancelMenuTimer()
    this.callNative(1, EVENT_NAME_CUSTOM_MAX_CLICK, '')
  }

  onMinimizeButtonClick() {
    this.callNative(1, EVENT_NAME_MIN_CLICK, '')
  }

  onCloseButtonClick() {
    this.callNative(1, EVENT_NAME_CLOSE_CLICK, '')
  }

  onMenuLeftSplitClick() {
    this.callNative(1, EVENT_NAME_LEFT_SPLIT_CLICK, '')
  }

  onMenuRightSplitClick() {
    this.callNative(1, EVENT_NAME_RIGHT_SPLIT_CLICK, '')
  }

  addButtonPointLightAnim() {
    this.callNative(1, EVENT_NAME_BUTTON_POINT_LIGHT_ANIM, '')
  }

  onAreaChangeEvent(oldValue: SizeOptions, newValue: SizeOptions) {
    this.callNative(1, EVENT_NAME_BUTTON_RECT_CHANGE, '')
  }

  onMenuWidthChange() {
    this.callNative(1, EVENT_NAME_CUSTOM_MENU_WIDTH_CHANGE, '125833961')
  }

  setHideSplit(hideSplit: boolean) {
    this.hideSplit = hideSplit
  }

  onColorConfigurationUpdate(isDark: boolean) {
    if (this.colorConfigurationLocked) {
      return;
    }
    this.isDark = isDark;
    this.maximizeBackgroundColor = buttonNormalBackgroundColor
    this.maximizeFillColor = buttonNormalIconFillColor
    this.minimizeBackgroundColor = buttonNormalBackgroundColor
    this.minimizeFillColor = buttonNormalIconFillColor
    this.closeBackgroundColor = buttonNormalBackgroundColor
    this.closeFillColor = buttonNormalIconFillColor
  }

  setMaximizeVisibility(isHide: boolean) {
    this.maximizeVisibility = isHide ? Visibility.None : Visibility.Visible
    this.setRowVisibility();
  }

  setMinimizeVisibility(isHide: boolean) {
    this.minimizeVisibility = isHide ? Visibility.None : Visibility.Visible
    this.setRowVisibility();
  }

  setCloseVisibility(isHide: boolean) {
    this.closeVisibility = isHide ? Visibility.None : Visibility.Visible
    this.setRowVisibility();
  }

  setCloseStatus(isEnabled: boolean) {
    this.closeStatus = isEnabled
  }

  setMaximizeIsRecover(isRecover: boolean) {
    if (isRecover) {
      this.maximizeResource = recoverNormalResource
    } else {
      this.maximizeResource = maximizeNormalResource
    }
  }

  setMenuWidth(width: string) {
    let widthNumber = (80 + parseInt(width)) + 'vp'
    if (widthNumber > this.menuWidth) {
      this.menuWidth = widthNumber
    }
  }

  setRowVisibility() {
    if (this.maximizeVisibility === Visibility.None && this.minimizeVisibility === Visibility.None &&
      this.closeVisibility === Visibility.None) {
      this.rowVisibility = Visibility.Hidden
    } else {
      this.rowVisibility = Visibility.Visible
    }
  }

  onHoverMaximizeButton(isHover: boolean) {
    if (isHover) {
      this.maximizeBackgroundColor = this.getResourceColor(buttonHoverBackgroundColor)
      this.maximizeFillColor = this.getResourceColor(buttonHoverIconFillColor)
    } else {
      this.maximizeBackgroundColor = buttonNormalBackgroundColor
      this.maximizeFillColor = this.getResourceColor(buttonNormalIconFillColor)
    }
  }

  onHoverMinimizeButton(isHover: boolean) {
    if (isHover) {
      this.minimizeBackgroundColor = this.getResourceColor(buttonHoverBackgroundColor)
      this.minimizeFillColor = this.getResourceColor(buttonHoverIconFillColor)
    } else {
      this.minimizeBackgroundColor = buttonNormalBackgroundColor
      this.minimizeFillColor = this.getResourceColor(buttonHoverIconFillColor)
    }
  }

  onHoverCloseButton(isHover: boolean) {
    if (isHover) {
      this.closeBackgroundColor = this.getResourceColor(closeHoverBackgroundColor)
      this.closeFillColor = this.getResourceColor(closeHoverIconFillColor)
    } else {
      this.closeBackgroundColor = closeNormalBackgroundColor
      this.closeFillColor = this.getResourceColor(closeNormalIconFillColor)
    }
  }

  onShowMenuWithTimer() {
    this.onCancelMenuTimer()
    if (!this.hideSplit && this.isFocused) {
      this.showMenuTimeoutId = setTimeout(() => {
        this.isShowMenu = true
      }, HOVER_TIME)
    }
  }

  onCancelMenuTimer() {
    if (this.showMenuTimeoutId !== -1) {
      clearTimeout(this.showMenuTimeoutId)
    }
  }

  aboutToAppear(): void {
  }

  @Builder
  MenuBuilder() {
    Column() {
      Row() {
        Image(this.menuLeftResource)
          .width(MENU_ICON_SIZE)
          .height(MENU_ICON_SIZE)
          .fillColor(this.splitFillColor)
          .margin({
            top: MENU_MARGIN_V,
            bottom: MENU_MARGIN_V,
            left: MENU_MARGIN_H,
            right: MENU_MARGIN_H
          } as Margin)
        Text(this.leftSplitTitle)
          .fontSize(MENU_TITLE_TEXT_FONT_SIZE)
          .textAlign(TextAlign.Start)
          .maxLines(1)
          .margin({ top: MENU_TITLE_MARGIN_V, bottom: MENU_TITLE_MARGIN_V, right: MENU_MARGIN_H } as Margin)
      }
      .borderRadius('4vp')
      .width('100%')
      .backgroundColor(this.leftSplitBackgroundColor)
      .margin({
        top: '0vp',
        bottom: '2vp',
        left: '4vp',
        right: '4vp'
      } as Margin)
      .justifyContent(FlexAlign.Start)
      .onClick(() => {
        this.onMenuLeftSplitClick()
      })
      .onHover((isHover: boolean, event: HoverEvent) => {
        if (isHover) {
          this.leftSplitBackgroundColor = this.getResourceColor(menuHoverColor)
        } else {
          this.leftSplitBackgroundColor = Color.Transparent
        }
      })

      Row() {
        Image(this.menuRightResource)
          .width(MENU_ICON_SIZE)
          .height(MENU_ICON_SIZE)
          .fillColor(this.splitFillColor)
          .margin({
            top: MENU_MARGIN_V,
            bottom: MENU_MARGIN_V,
            left: MENU_MARGIN_H,
            right: MENU_MARGIN_H
          } as Margin)
        Text(this.rightSplitTitle)
          .fontSize(MENU_TITLE_TEXT_FONT_SIZE)
          .textAlign(TextAlign.Start)
          .maxLines(1)
          .margin({ top: MENU_TITLE_MARGIN_V, bottom: MENU_TITLE_MARGIN_V, right: MENU_MARGIN_H } as Margin)
      }
      .borderRadius('4vp')
      .width('100%')
      .backgroundColor(this.rightSplitBackgroundColor)
      .margin({
        top: '2vp',
        bottom: '0vp',
        left: '4vp',
        right: '4vp'
      } as Margin)
      .justifyContent(FlexAlign.Start)
      .onClick(() => {
        this.onMenuRightSplitClick()
      })
      .onHover((isHover: boolean, event: HoverEvent) => {
        if (isHover) {
          this.rightSplitBackgroundColor = this.getResourceColor(menuHoverColor)
        } else {
          this.rightSplitBackgroundColor = Color.Transparent
        }
      })
    }.width(this.menuWidth)
    .onHover((isHover: boolean, event: HoverEvent) => {
      if (isHover) {
        this.cancelMenuDisappearTimer()
      } else {
        this.menuDisappearTimer(MENU_MOUSEOUT_DISAPPEAR_TIME)
      }
    })
  }

  menuDisappearTimer(disappearTime: number) {
    hilog.info(0x0000, 'testTag', 'menuDisappearTimer');
    this.cancelMenuDisappearTimer()
    this.menuDisappearTimeoutId = setTimeout(() => {
       this.isShowMenu = false
    }, disappearTime as Int)
  }

  cancelMenuDisappearTimer() {
    if (this.menuDisappearTimeoutId !== -1) {
       clearTimeout(this.menuDisappearTimeoutId)
    }
  }

  build() {
    Row() {
      Row({ space: this.buttonSpacing } as RowOptions) {
        Stack() {
          Image(this.maximizeResource)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.maximizeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.maximizeScale, y: this.maximizeScale } as ScaleOptions)
        }
        .id('EnhanceMaximizeBtn')
        .backgroundColor(this.maximizeBackgroundColor)
        .width(this.buttonSize + 'vp')
        .height(this.buttonSize + 'vp')
        .borderRadius('4vp')
        .hoverEffect(HoverEffect.None)
        .responseRegion({
          x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
          y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
          width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
          height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
        } as Rectangle)
        .visibility(this.maximizeVisibility)
        .bindContextMenu(this.isShowMenu, this.MenuBuilder, {
          aboutToDisappear: () => {
            this.isShowMenu = false;
            this.cancelMenuDisappearTimer();
          }, placement: Placement.BottomRight
        } as ContextMenuOptions)
        .gesture(GestureGroup(GestureMode.Exclusive, LongPressGesture({ repeat: false }).onAction(() => {
          this.menuWidth = '224vp'
          this.onMenuWidthChange()
          this.isShowMenu = !this.hideSplit
          this.menuDisappearTimer(MENU_AUTO_DISAPPEAR_TIME)
        }), TapGesture().onAction(() => {
          this.onMaximizeButtonClick()
        })))
        .onHover((isHover: boolean, event: HoverEvent) => {
          this.onHoverMaximizeButton(isHover)
          if (isHover) {
            this.onMenuWidthChange()
            this.onShowMenuWithTimer()
            this.cancelMenuDisappearTimer()
            event.stopPropagation()
          } else {
            this.onCancelMenuTimer()
            this.menuDisappearTimer(MENU_MOUSEOUT_DISAPPEAR_TIME)
          }
        })

        Stack() {
          Image(this.minimizeResource)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.minimizeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.minimizeScale, y: this.minimizeScale } as ScaleOptions)
        }
        .id('EnhanceMinimizeBtn')
        .backgroundColor(this.minimizeBackgroundColor)
        .width(this.buttonSize + 'vp')
        .height(this.buttonSize + 'vp')
        .borderRadius('4vp')
        .hoverEffect(HoverEffect.None)
        .responseRegion({
          x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
          y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
          width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
          height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
        } as Rectangle)
        .visibility(this.minimizeVisibility)
        .gesture(TapGesture().onAction(() => {
          this.onMinimizeButtonClick()
        }))
        .onHover((isHover: boolean, event: HoverEvent) => {
          this.onHoverMinimizeButton(isHover)
          if (isHover) {
            event.stopPropagation()
          }
          
        })

        Stack() {
          Image(this.closeResource)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.closeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.closeScale, y: this.closeScale } as ScaleOptions)
        }
        .id('EnhanceCloseBtn')
        .backgroundColor(this.closeBackgroundColor)
        .width(this.buttonSize + 'vp')
        .height(this.buttonSize + 'vp')
        .borderRadius('4vp')
        .hoverEffect(HoverEffect.None)
        .responseRegion({
          x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
          y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
          width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
          height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
        } as Rectangle)
        .visibility(this.closeVisibility)
        .gesture(TapGesture().onAction(() => {
          this.onCloseButtonClick()
        }))
        .onHover((isHover: boolean, event: HoverEvent) => {
          this.onHoverCloseButton(isHover)
          if (isHover) {
            event.stopPropagation()
          }
          let context = UIContext.getFocusedUIContext()
          if (context) {
            context.animateTo({ duration: 0 } as AnimateParam, () => {
              if (isHover) {
                this.maximizeScale = 1.1
              } else {
                this.maximizeScale = 1.0
              }
            })
          }
        })
      }
      .id('containerModalButtonRowId')
      .height('100%')
      .visibility(this.rowVisibility)
      .padding({ left: BUTTON_ELEMENT_MARGIN_HORIZONTAL, right: this.buttonRightOffset + 'vp' } as Padding)
      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
        this.onAreaChangeEvent(oldValue, newValue)
      })
      .gesture(PanGesture())
      .onTouch((event?: TouchEvent) => {
        if (event) {
          event.stopPropagation();
        }
      })
    }
    .justifyContent(FlexAlign.End)
    .visibility(this.rowVisibility)
    .height('100%')
    .width('100%')
    .opacity(this.rowOpacity)
    .hitTestBehavior(HitTestMode.Transparent)
    .onAppear(() => {
      this.addButtonPointLightAnim()
    })
  }
}
