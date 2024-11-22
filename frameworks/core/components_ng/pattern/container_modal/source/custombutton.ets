const IMAGE_SIZE: string = '28vp'
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
const MENU_TITLE_TEXT_FONT_SIZE: string = '16fp'
const HOVER_TIME: number = 1000

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

const buttonNormalBackgroundColor: Color =  Color.Transparent

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

const closeNormalBackgroundColor : Color =  Color.Transparent

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

@Entry
@Component
struct Index {
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
  @State maximizeBackgroundColor: Resource | Color = buttonNormalBackgroundColor
  @State minimizeBackgroundColor: Resource | Color = buttonNormalBackgroundColor
  @State closeBackgroundColor: Resource | Color = buttonNormalBackgroundColor
  @State maximizeFillColor: Resource = buttonNormalIconFillColor
  @State minimizeFillColor: Resource = buttonNormalIconFillColor
  @State closeFillColor: Resource = buttonNormalIconFillColor
  @State maximizeScale: number = 1.0
  @State minimizeScale: number = 1.0
  @State closeScale: number = 1.0
  @State rowVisibility: Visibility = Visibility.Visible
  @State maximizeVisibility: Visibility = Visibility.Visible
  @State minimizeVisibility: Visibility = Visibility.Visible
  @State closeVisibility: Visibility = Visibility.Visible
  @State closeStatus: boolean = true
  @State isShowMenu: boolean = false
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
  @State splitFillColor: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830991,
    type: 10001
  }
  @State leftSplitBackgroundColor: ResourceColor = Color.Transparent
  @State rightSplitBackgroundColor: ResourceColor = Color.Transparent
  @State rowOpacity: number = 1.0
  @State menuWidth: string = '224vp';
  isFocused: boolean = true;
  isDark: boolean = false;
  isHoverShowMenu: boolean = false
  showMenuTimeoutId: number = -1
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
    if (value == 'true') {
      return true
    }
    return false
  }

  setCustomCallback(eventName: string, param: string) {
    if (eventName == EVENT_NAME_COLOR_CONFIGURATION) {
      this.onColorConfigurationUpdate(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_HIDE_SPLIT) {
      this.setHideSplit(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_MAXIMIZE_VISIBILITY) {
      this.setMaximizeVisibility(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_MINIMIZE_VISIBILITY) {
      this.setMinimizeVisibility(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_CLOSE_VISIBILITY) {
      this.setCloseVisibility(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_CLOSE_STATUS) {
      this.setCloseStatus(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_MAXIMIZE_IS_RECOVER) {
      this.setMaximizeIsRecover(this.parseBoolean(param))
    } else if (eventName == EVENT_NAME_MENU_WIDTH_CHANGE) {
      this.setMenuWidth(param)
    }
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

  onAreaChangeEvent(oldValue: Area, newValue: Area) {

  }

  onMenuWidthChange() {

  }

  setHideSplit(hideSplit: boolean) {
    this.hideSplit = hideSplit
  }

  onColorConfigurationUpdate(isDark: boolean) {
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

  setMenuWidth(width: string) {
    this.menuWidth = (80 + parseInt(width)) + 'vp'
  }


  setRowVisibility() {
    if (this.maximizeVisibility == Visibility.None && this.minimizeVisibility == Visibility.None &&
      this.closeVisibility == Visibility.None) {
      this.rowVisibility = Visibility.None
    } else {
      this.rowVisibility = Visibility.Visible
    }
  }

  onHoverMaximizeButton(isHover: boolean) {
    if (isHover) {
      this.maximizeBackgroundColor = buttonHoverBackgroundColor
      this.maximizeFillColor = buttonHoverIconFillColor
    } else {
      this.maximizeBackgroundColor = buttonNormalBackgroundColor
      this.maximizeFillColor = buttonNormalIconFillColor
    }
  }

  onHoverMinimizeButton(isHover: boolean) {
    if (isHover) {
      this.minimizeBackgroundColor = buttonHoverBackgroundColor
      this.minimizeFillColor = buttonHoverIconFillColor
    } else {
      this.minimizeBackgroundColor = buttonNormalBackgroundColor
      this.minimizeFillColor = buttonNormalIconFillColor
    }
  }

  onHoverCloseButton(isHover: boolean) {
    if (isHover) {
      this.closeBackgroundColor = closeHoverBackgroundColor
      this.closeFillColor = closeHoverIconFillColor
    } else {
      this.closeBackgroundColor = closeNormalBackgroundColor
      this.closeFillColor = closeNormalIconFillColor
    }
  }

  onShowMenuWithTimer() {
    if (!this.hideSplit && this.isFocused) {
      this.showMenuTimeoutId = setTimeout(() => {
        this.isShowMenu = true
      }, HOVER_TIME)
    }
  }

  onCancelMenuTimer() {
    if (this.showMenuTimeoutId != -1) {
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
          this.leftSplitBackgroundColor = menuHoverColor
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
          this.rightSplitBackgroundColor = menuHoverColor
        } else {
          this.rightSplitBackgroundColor = Color.Transparent
        }
      })
    }.width(this.menuWidth)
  }

  build() {
    Row() {
      Row() {
        Button() {
          Image(this.maximizeResource)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.maximizeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.maximizeScale, y: this.maximizeScale })
        }
        .id('EnhanceMaximizeBtn')
        .backgroundColor(this.maximizeBackgroundColor)
        .width(BUTTON_SIZE)
        .height(BUTTON_SIZE)
        .type(ButtonType.Normal)
        .borderRadius('4vp')
        .margin({ right: BUTTON_ELEMENT_MARGIN_HORIZONTAL })
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
          }
        })
        .gesture(GestureGroup(GestureMode.Exclusive, LongPressGesture({ repeat: false }).onAction(() => {
          this.onMenuWidthChange()
          this.isShowMenu = true
        }), TapGesture().onAction(() => {
          this.onMaximizeButtonClick()
        })))
        .onHover((isHover: boolean, event: HoverEvent) => {
          this.onHoverMaximizeButton(isHover)
          if (isHover) {
            this.onMenuWidthChange()
            this.onShowMenuWithTimer()
          } else {
            this.onCancelMenuTimer()
          }
          this.getUIContext()?.animateTo({ duration: 0 }, () => {
            if (isHover) {
              this.maximizeScale = 1.1
            } else {
              this.maximizeScale = 1.0
            }
          })
        })

        Button() {
          Image(this.minimizeResource)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.minimizeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.minimizeScale, y: this.minimizeScale })
        }
        .id('EnhanceMinimizeBtn')
        .backgroundColor(this.minimizeBackgroundColor)
        .width(BUTTON_SIZE)
        .height(BUTTON_SIZE)
        .type(ButtonType.Normal)
        .borderRadius('4vp')
        .margin({ right: BUTTON_ELEMENT_MARGIN_HORIZONTAL })
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
          this.getUIContext()?.animateTo({ duration: 0 }, () => {
            if (isHover) {
              this.minimizeScale = 1.1
            } else {
              this.minimizeScale = 1.0
            }
          })
        })

        Button() {
          Image(this.closeResource)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor(this.closeFillColor)
            .draggable(false)
            .interpolation(ImageInterpolation.High)
            .scale({ x: this.closeScale, y: this.closeScale })
        }
        .id('EnhanceCloseBtn')
        .backgroundColor(this.closeBackgroundColor)
        .width(BUTTON_SIZE)
        .height(BUTTON_SIZE)
        .type(ButtonType.Normal)
        .borderRadius('4vp')
        .margin({ right: BUTTON_ELEMENT_MARGIN_HORIZONTAL })
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
          this.getUIContext()?.animateTo({ duration: 0 }, () => {
            if (isHover) {
              this.closeScale = 1.1
            } else {
              this.closeScale = 1.0
            }
          })
        })
      }.id('containerModalButtonRowId')
      .height('100%')
      .padding({ left: BUTTON_ELEMENT_MARGIN_HORIZONTAL, right: BUTTON_ELEMENT_MARGIN_HORIZONTAL_END })
      .onAreaChange((oldValue: Area, newValue: Area) => {
        this.onAreaChangeEvent(oldValue, newValue)
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