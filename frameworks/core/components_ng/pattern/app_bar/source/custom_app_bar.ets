import { image } from '@kit.ImageKit'

const VIEW_WIDTH: string = '80vp'
const BUTTON_WIDTH: string = '40vp'
const VIEW_HEIGHT: string = '36vp'
const IMAGE_SIZE: string = '20vp'
const MENU_RADIUS: string = '20vp'
const DIVIDER_HEIGHT: string = '16vp'
const BORDER_WIDTH: string = '1px'
const VIEW_MARGIN_TOP: string = '10vp'
const VIEW_MARGIN_RIGHT: string = '8vp'

const ICON_FILL_COLOR_DEFAULT: string = '#182431'
const BORDER_COLOR_DEFAULT: string = '#33000000'
const MENU_BACK_COLOR: string = '#99FFFFFF'

const ARKUI_APP_BAR_COLOR_CONFIGURATION: string = 'arkui_app_bar_color_configuration';
const ARKUI_APP_BAR_MENU_SAFE_AREA: string = 'arkui_app_bar_menu_safe_area';
const ARKUI_APP_BAR_CONTENT_SAFE_AREA: string = 'arkui_app_bar_content_safe_area';
const ARKUI_APP_BAR_BAR_INFO: string = 'arkui_app_bar_info';
const ARKUI_APP_BAR_SCREEN: string = 'arkui_app_bar_screen';
const ARKUI_APP_BG_COLOR: string = 'arkui_app_bg_color';
const ARKUI_APP_BAR_SERVICE_PANEL: string = 'arkui_app_bar_service_panel'
const ARKUI_APP_BAR_CLOSE: string = 'arkui_app_bar_close'

const EVENT_NAME_CUSTOM_APP_BAR_MENU_CLICK = 'arkui_custom_app_bar_menu_click';
const EVENT_NAME_CUSTOM_APP_BAR_CLOSE_CLICK = 'arkui_custom_app_bar_close_click';
const EVENT_NAME_CUSTOM_APP_BAR_DID_BUILD = 'arkui_custom_app_bar_did_build';

const MENU_MARGIN_TOP: number = 10

class ColorGroup {
  public light: string = '#000000';
  public dark: string = '#FFFFFF';

  constructor(light: string, dark: string) {
    this.light = light;
    this.dark = dark;
  }
}

const colorMap: Map<string, ColorGroup> = new Map<string, ColorGroup>([
  [ICON_FILL_COLOR_DEFAULT, new ColorGroup('#182431', '#e5ffffff')],
  [BORDER_COLOR_DEFAULT, new ColorGroup('#33182431', '#4Dffffff')],
  [MENU_BACK_COLOR, new ColorGroup('#99FFFFFF', '#33000000')],
]);

@Entry
@Component
struct Index {
  @State menuResource: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125830217,
    type: 20000
  }
  @State closeResource: Resource = {
    bundleName: '',
    moduleName: '',
    params: [],
    id: 125831084,
    type: 20000
  }
  @State menuFillColor: string = this.getResourceColor(ICON_FILL_COLOR_DEFAULT)
  @State closeFillColor: string = this.getResourceColor(ICON_FILL_COLOR_DEFAULT)
  @State menubarBorderColor: string = this.getResourceColor(BORDER_COLOR_DEFAULT)
  @State menubarBackColor: string = this.getResourceColor(MENU_BACK_COLOR)
  @State dividerBackgroundColor: string = this.getResourceColor(BORDER_COLOR_DEFAULT)
  @State contentBgColor: string = '#FFFFFFFF'
  @State contentMarginTop: string = '0vp'
  @State contentMarginLeft: string = '0vp'
  @State contentMarginRight: string = '0vp'
  @State contentMarginBottom: string = '0vp'
  @State menuMarginTop: string = '10vp'
  @State serviceMenuRead: string = this.getStringByResourceToken(ARKUI_APP_BAR_SERVICE_PANEL)
  @State closeRead: string = this.getStringByResourceToken(ARKUI_APP_BAR_CLOSE)
  isDark: boolean = true;

  parseBoolean(value: string): boolean {
    if (value === 'true') {
      return true
    }
    return false
  }

  getResourceColor(defaultColor: string): string {
    if (colorMap.has(defaultColor)) {
      const colorGroup = colorMap.get(defaultColor);
      if (colorGroup) {
        return this.isDark ? colorGroup.dark : colorGroup.light;
      }
    }
    return defaultColor;
  }

  setCustomCallback(eventName: string, param: string) {
    if (eventName === ARKUI_APP_BAR_COLOR_CONFIGURATION) {
      this.onColorConfigurationUpdate(this.parseBoolean(param))
    } else if (eventName === ARKUI_APP_BAR_MENU_SAFE_AREA) {
      let value = Number(param) + MENU_MARGIN_TOP;
      this.menuMarginTop = value.toString();
    } else if (eventName === ARKUI_APP_BAR_CONTENT_SAFE_AREA) {
      //top left right bottom
      let splitArray: string[] = param.split('|');
      if (splitArray.length < 4) {
        return
      }
      this.contentMarginTop = splitArray[0]
      this.contentMarginLeft = splitArray[1];
      this.contentMarginRight = splitArray[2];
      this.contentMarginBottom = splitArray[3];
    } else if (eventName === ARKUI_APP_BAR_BAR_INFO) {
      //buildName,appname
      let splitArray: string[] = param.split('|');
    } else if (eventName === ARKUI_APP_BAR_SCREEN) {

    } else if (eventName === ARKUI_APP_BG_COLOR) {
      this.contentBgColor = param;
    }
  }

  onColorConfigurationUpdate(isDark: boolean) {
    this.isDark = isDark;
    this.menuFillColor = this.getResourceColor(ICON_FILL_COLOR_DEFAULT);
    this.closeFillColor = this.getResourceColor(ICON_FILL_COLOR_DEFAULT);
    this.menubarBorderColor = this.getResourceColor(BORDER_COLOR_DEFAULT);
    this.dividerBackgroundColor = this.getResourceColor(BORDER_COLOR_DEFAULT);
    this.menubarBackColor = this.getResourceColor(MENU_BACK_COLOR);
  }

  setAppIcon(pixelMap: image.PixelMap) {

  }

  onMenuButtonClick() {
  }

  onCloseButtonClick() {
  }

  onDidBuild(): void {
  }

  build() {
    Column() {
      Stack({ alignContent: Alignment.TopEnd }) {
        Row() {
        }
        .padding({
          top: this.contentMarginTop,
          left: this.contentMarginLeft,
          right: this.contentMarginRight,
          bottom: this.contentMarginBottom
        })
        .height('100%')
        .width('100%')
        .id('AtomicServiceStageId')

        Row() {
          Row() {
            Button() {
              Image(this.menuResource)
                .id('AtomicServiceMenuIconId')
                .width(IMAGE_SIZE)
                .height(IMAGE_SIZE)
                .fillColor(this.menuFillColor)
                .draggable(false)
                .interpolation(ImageInterpolation.High)
            }
            .id('AtomicServiceMenuId')
            .type(ButtonType.Normal)
            .borderRadius({ topLeft: MENU_RADIUS, bottomLeft: MENU_RADIUS })
            .backgroundColor(Color.Transparent)
            .width(BUTTON_WIDTH)
            .height(VIEW_HEIGHT)
            .gesture(TapGesture().onAction(() => {
              this.onMenuButtonClick()
            }))
            .accessibilityText(this.serviceMenuRead)
            .onAccessibilityHover(() => {
              this.serviceMenuRead = this.getStringByResourceToken(ARKUI_APP_BAR_SERVICE_PANEL);
            })

            Divider()
              .id('AtomicServiceDividerId')
              .vertical(true)
              .color(this.dividerBackgroundColor)
              .lineCap(LineCapStyle.Round)
              .strokeWidth(BORDER_WIDTH)
              .height(DIVIDER_HEIGHT)

            Button() {
              Image(this.closeResource)
                .id('AtomicServiceCloseIconId')
                .width(IMAGE_SIZE)
                .height(IMAGE_SIZE)
                .fillColor(this.closeFillColor)
                .draggable(false)
                .interpolation(ImageInterpolation.High)
            }
            .id('AtomicServiceCloseId')
            .type(ButtonType.Normal)
            .backgroundColor(Color.Transparent)
            .borderRadius({ topRight: MENU_RADIUS, bottomRight: MENU_RADIUS })
            .width(BUTTON_WIDTH)
            .height(VIEW_HEIGHT)
            .gesture(TapGesture().onAction(() => {
              this.onCloseButtonClick()
            }))
            .accessibilityText(this.closeRead)
            .onAccessibilityHover(() => {
              this.closeRead = this.getStringByResourceToken(ARKUI_APP_BAR_CLOSE);
            })
          }
          .borderRadius(MENU_RADIUS)
          .borderWidth(BORDER_WIDTH)
          .borderColor(this.menubarBorderColor)
          .backgroundColor(this.menubarBackColor)
          .height(VIEW_HEIGHT)
          .width(VIEW_WIDTH)
          .align(Alignment.Top)
          .draggable(false)
          .id('AtomicServiceMenubarId')
        }
        .id('AtomicServiceMenubarRowId')
        .justifyContent(FlexAlign.End)
        .margin({ top: this.menuMarginTop, left: VIEW_MARGIN_RIGHT, right: VIEW_MARGIN_RIGHT })
        .height(VIEW_HEIGHT)
        .hitTestBehavior(HitTestMode.Transparent)
        .width('100%')
      }
      .id('AtomicServiceContainerId')
      .height('100%')
      .width('100%')
      .backgroundColor(Color.Transparent)
      .hitTestBehavior(HitTestMode.Transparent)
    }
    .height('100%')
    .width('100%')
    .justifyContent(FlexAlign.End)
    .backgroundColor(this.contentBgColor)
    .hitTestBehavior(HitTestMode.Transparent)
  }

  getStringByResourceToken(value?: string, ...args: Array<string | number>): string {
    if (value) {
      try {
        return getContext(this).resourceManager.getStringByNameSync(value, ...args);
      } catch (error) {
        console.error(`Ace SegmentButton getAccessibilityDescription, error: ${error.toString()}`);
      }
    }
    return '';
  }
}