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
const HOVER_TIME: number = 1000; // Hover time: 1000ms
const MENU_AUTO_DISAPPEAR_TIME: number = 2000; // Menu auto-disappear: 2000ms
const MENU_MOUSEOUT_DISAPPEAR_TIME: number = 1000; // Menu mouseout disappear: 1000ms

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
const EVENT_NAME_BUTTON_ICON_SIZE_CHANGE: string = 'arkui_button_icon_size_change'
const EVENT_NAME_BUTTON_BACKGROUND_CORNER_RADIUS_CHANGE: string = 'arkui_button_background_corner_radius_change'

const PC_TITLE_BAR_MAXIMIZE: string = 'pc_title_bar_maximize'
const PC_TITLE_BAR_MINIMIZE: string = 'pc_title_bar_minimize'
const PC_TITLE_BAR_RESTORE: string = 'pc_title_bar_restore'
const PC_TITLE_BAR_CLOSE: string = 'pc_title_bar_close'

const maximizeNormalResource: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125829923,
  type: 20000
}
const recoverNormalResource: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125829925,
  type: 20000
}

const buttonNormalBackgroundColor: Color = Color.Transparent

const buttonNormalIconFillColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125830991,
  type: 10001
}

const buttonHoverBackgroundColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125834289,
  type: 10001
}

const buttonHoverIconFillColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125830991,
  type: 10001
}

const closeNormalBackgroundColor: Color = Color.Transparent

const closeNormalIconFillColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125830991,
  type: 10001
}

const closeHoverBackgroundColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125830979,
  type: 10001
}

const closeHoverIconFillColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125831057,
  type: 10001
}

const menuHoverColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125831024,
  type: 10001
}

const splitItemFillColor: Resource = {
  bundleName: '',
  moduleName: '',
  params: [],
  id: 125830991,
  type: 10001
}

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

@Entry
@Component
struct custombutton {
  @State maximizeResource: Resource = maximizeNormalResource
  @State minimizeResource: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829924,
    type: 20000
  }
  @State closeResource: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125829917,
    type: 20000
  }
  @State menuLeftResource: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830147,
    type: 20000
  }
  @State menuRightResource: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830148,
    type: 20000
  }
  @State maximizeBackgroundColor: Resource | Color | string = buttonNormalBackgroundColor
  @State minimizeBackgroundColor: Resource | Color | string = buttonNormalBackgroundColor
  @State closeBackgroundColor: Resource | Color | string = buttonNormalBackgroundColor
  @State maximizeFillColor: Resource | Color | string = this.getResourceColor(buttonNormalIconFillColor)
  @State minimizeFillColor: Resource | Color | string = this.getResourceColor(buttonNormalIconFillColor)
  @State closeFillColor: Resource | Color | string = this.getResourceColor(buttonNormalIconFillColor)
  @State maximizeScale: number = 1.0
  @State minimizeScale: number = 1.0
  @State closeScale: number = 1.0
  @State rowVisibility: Visibility = Visibility.Visible
  @State maximizeVisibility: Visibility = Visibility.Visible
  @State minimizeVisibility: Visibility = Visibility.Visible
  @State closeVisibility: Visibility = Visibility.Visible
  @State closeStatus: boolean = true
  @State isShowMenu: boolean = false
  @State maximizeReadResource: string = PC_TITLE_BAR_MAXIMIZE
  @State maximizeRead: string = this.getStringByResourceToken(PC_TITLE_BAR_MAXIMIZE)
  @State minimizeRead: string = this.getStringByResourceToken(PC_TITLE_BAR_MINIMIZE)
  @State closeRead: string = this.getStringByResourceToken(PC_TITLE_BAR_CLOSE)
  @State leftSplitTitle: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125833961,
    type: 10003
  }
  @State rightSplitTitle: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125833962,
    type: 10003
  }

  @State splitFillColor: Resource | Color | string = this.getResourceColor(splitItemFillColor)
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
  // button icon size 20-24vp
  @State buttonIconSize: number = 20;
  // button background corner radius 4-8vp
  @State buttonBackgroundCornerRadius: number = 4;

  isFocused: boolean = true;
  isDark: boolean = false;
  isHoverShowMenu: boolean = false
  showMenuTimeoutId: number = -1
  menuDisappearTimeoutId: number = -1
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
      this.setMaximizeReadIsRecover(this.parseBoolean(param))
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
    } else if (eventName === EVENT_NAME_BUTTON_ICON_SIZE_CHANGE) {
        this.setButtonIconSize(param);
    } else if (eventName === EVENT_NAME_BUTTON_BACKGROUND_CORNER_RADIUS_CHANGE) {
        this.setButtonBackgroundCornerRadius(param);
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
    this.isDark = (colorMode === 0);
    this.colorConfigurationLocked = true;
    this.maximizeFillColor = this.getResourceColor(buttonNormalIconFillColor)
    this.minimizeFillColor = this.getResourceColor(buttonNormalIconFillColor)
    this.closeFillColor = this.getResourceColor(buttonNormalIconFillColor)
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
  setButtonIconSize(param:string) {
      this.buttonIconSize = parseInt(param);
  }

  setButtonBackgroundCornerRadius(param:string) {
      this.buttonBackgroundCornerRadius = parseInt(param);
  }

  onMaximizeButtonClick() {
    this.onCancelMenuTimer()
  }

  onMinimizeButtonClick() {
  }

  onCloseButtonClick() {

  }

  onMenuLeftSplitClick() {

  }

  onMenuRightSplitClick() {

  }

  addButtonPointLightAnim() {

  }

  onAreaChangeEvent(oldValue: SizeOptions, newValue: SizeOptions) {

  }

  onMenuWidthChange() {

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
  }

  setMinimizeVisibility(isHide: boolean) {
    this.minimizeVisibility = isHide ? Visibility.None : Visibility.Visible
  }

  setCloseVisibility(isHide: boolean) {
    this.closeVisibility = isHide ? Visibility.None : Visibility.Visible
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

  setMaximizeReadIsRecover(isRecover: boolean) {
    if (isRecover) {
      this.maximizeReadResource = PC_TITLE_BAR_RESTORE
    } else {
      this.maximizeReadResource = PC_TITLE_BAR_MAXIMIZE
    }
  }

  setMenuWidth(width: string) {
    this.menuWidth = (80 + parseInt(width)) + 'vp'
  }


  setRowVisibility() {
    if (this.maximizeVisibility === Visibility.None && this.minimizeVisibility === Visibility.None &&
      this.closeVisibility === Visibility.None) {
      this.rowVisibility = Visibility.None
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
          })
        Text(this.leftSplitTitle)
          .fontSize(MENU_TITLE_TEXT_FONT_SIZE)
          .textAlign(TextAlign.Start)
          .maxLines(1)
          .margin({ top: MENU_TITLE_MARGIN_V, bottom: MENU_TITLE_MARGIN_V, right: MENU_MARGIN_H })
      }
      .borderRadius('4vp')
      .width('100%')
      .backgroundColor(this.leftSplitBackgroundColor)
      .margin({
        top: '0vp',
        bottom: '2vp',
        left: '4vp',
        right: '4vp'
      })
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
          })
        Text(this.rightSplitTitle)
          .fontSize(MENU_TITLE_TEXT_FONT_SIZE)
          .textAlign(TextAlign.Start)
          .maxLines(1)
          .margin({ top: MENU_TITLE_MARGIN_V, bottom: MENU_TITLE_MARGIN_V, right: MENU_MARGIN_H })
      }
      .borderRadius('4vp')
      .width('100%')
      .backgroundColor(this.rightSplitBackgroundColor)
      .margin({
        top: '2vp',
        bottom: '0vp',
        left: '4vp',
        right: '4vp'
      })
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
    this.cancelMenuDisappearTimer()
    this.menuDisappearTimeoutId = setTimeout(() => {
      this.isShowMenu = false
    }, disappearTime)
  }

  cancelMenuDisappearTimer() {
    if (this.menuDisappearTimeoutId !== -1) {
      clearTimeout(this.menuDisappearTimeoutId)
    }
  }


  build() {
    Row() {
      Row({space: this.buttonSpacing}) {
        Button() {
          Image(this.maximizeResource)
            .width(this.buttonIconSize + 'vp')
            .height(this.buttonIconSize + 'vp')
            .fillColor(this.maximizeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.maximizeScale, y: this.maximizeScale })
        }
        .id('EnhanceMaximizeBtn')
        .backgroundColor(this.maximizeBackgroundColor)
        .width(this.buttonSize + 'vp')
        .height(this.buttonSize + 'vp')
        .type(ButtonType.Normal)
        .borderRadius(this.buttonBackgroundCornerRadius + 'vp')
        .hoverEffect(HoverEffect.None)
        .responseRegion({
          x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
          y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
          width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
          height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
        })
        .visibility(this.maximizeVisibility)
        .bindMenu(this.isShowMenu, this.MenuBuilder, {
          placement: Placement.BottomRight, aboutToDisappear: () => {
            this.isShowMenu = false;
            this.cancelMenuDisappearTimer();
          }
        })
        .gesture(GestureGroup(GestureMode.Exclusive, LongPressGesture({ repeat: false }).onAction(() => {
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
          this.getUIContext()?.animateTo({ duration: 0 }, () => {
            if (isHover) {
              this.maximizeScale = 1.1
            } else {
              this.maximizeScale = 1.0
            }
          })
        })
        .accessibilityText(this.maximizeRead)
        .onAccessibilityHover(() => {
          this.maximizeRead = this.getStringByResourceToken(this.maximizeReadResource);
        })

        Button() {
          Image(this.minimizeResource)
            .width(this.buttonIconSize + 'vp')
            .height(this.buttonIconSize + 'vp')
            .fillColor(this.minimizeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.minimizeScale, y: this.minimizeScale })
        }
        .id('EnhanceMinimizeBtn')
        .backgroundColor(this.minimizeBackgroundColor)
        .width(this.buttonSize + 'vp')
        .height(this.buttonSize + 'vp')
        .type(ButtonType.Normal)
        .borderRadius(this.buttonBackgroundCornerRadius + 'vp')
        .hoverEffect(HoverEffect.None)
        .responseRegion({
          x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
          y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
          width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
          height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
        })
        .visibility(this.minimizeVisibility)
        .gesture(TapGesture().onAction(() => {
          this.onMinimizeButtonClick()
        }))
        .onHover((isHover: boolean, event: HoverEvent) => {
          this.onHoverMinimizeButton(isHover)
          if (isHover) {
            event.stopPropagation()
          }
          this.getUIContext()?.animateTo({ duration: 0 }, () => {
            if (isHover) {
              this.minimizeScale = 1.1
            } else {
              this.minimizeScale = 1.0
            }
          })
        })
        .accessibilityText(this.minimizeRead)
        .onAccessibilityHover(() => {
          this.minimizeRead = this.getStringByResourceToken(PC_TITLE_BAR_MINIMIZE);
        })

        Button() {
          Image(this.closeResource)
            .width(this.buttonIconSize + 'vp')
            .height(this.buttonIconSize + 'vp')
            .fillColor(this.closeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.closeScale, y: this.closeScale })
        }
        .id('EnhanceCloseBtn')
        .backgroundColor(this.closeBackgroundColor)
        .width(this.buttonSize + 'vp')
        .height(this.buttonSize + 'vp')
        .type(ButtonType.Normal)
        .borderRadius(this.buttonBackgroundCornerRadius + 'vp')
        .hoverEffect(HoverEffect.None)
        .responseRegion({
          x: TITLE_BUTTON_RESPONSE_REGION_OFFSET_X,
          y: TITLE_BUTTON_RESPONSE_REGION_OFFSET_Y,
          width: TITLE_BUTTON_RESPONSE_REGION_WIDTH,
          height: TITLE_BUTTON_RESPONSE_REGION_HEIGHT
        })
        .visibility(this.closeVisibility)
        .gesture(TapGesture().onAction(() => {
          this.onCloseButtonClick()
        }))
        .onHover((isHover: boolean, event: HoverEvent) => {
          this.onHoverCloseButton(isHover)
          if (isHover) {
            event.stopPropagation()
          }
          this.getUIContext()?.animateTo({ duration: 0 }, () => {
            if (isHover) {
              this.closeScale = 1.1
            } else {
              this.closeScale = 1.0
            }
          })
        })
        .accessibilityText(this.closeRead)
        .onAccessibilityHover(() => {
          this.closeRead = this.getStringByResourceToken(PC_TITLE_BAR_CLOSE);
        })
      }.id('containerModalButtonRowId')
      .height('100%')
      .padding({ left: BUTTON_ELEMENT_MARGIN_HORIZONTAL, right: this.buttonRightOffset + 'vp' })
      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
        this.onAreaChangeEvent(oldValue, newValue)
      })
      .gesture(PanGesture())
      .onTouch((event?: TouchEvent) => {
        if(event) {
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

  getStringByResourceToken(f, ...g) {
      if (f) {
          try {
              return getContext(this).resourceManager.getStringByNameSync(f, ...g);
          } catch (h) {
              console.error(`Ace SegmentButton getAccessibilityDescription, error: ${h.toString()}`);
          }
      }
      return '';
  }
}
