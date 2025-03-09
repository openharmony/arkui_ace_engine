/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

import { KeyCode } from '@ohos.multimodalInput.keyCode'
import MeasureText from '@ohos.measure'
import window from '@ohos.window'
import common from '@ohos.app.ability.common'
import { BusinessError } from '@kit.BasicServicesKit'
import { hilog } from '@kit.PerformanceAnalysisKit'
import { SymbolGlyphModifier } from '@kit.ArkUI'

export interface TabTitleBarMenuItem {
  value: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: () => void;
  label?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityLevel?: string;
  accessibilityDescription?: ResourceStr;
}

export interface TabTitleBarTabItem {
  title: ResourceStr;
  icon?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
}

const PUBLIC_MORE = $r('sys.symbol.dot_grid_2x2')
const TEXT_EDITABLE_DIALOG = '18.3fp'
const IMAGE_SIZE = '64vp'
const MAX_DIALOG = '256vp'
const MIN_DIALOG = '216vp'
const RESOURCE_TYPE_SYMBOL: number = 40000;

class ButtonGestureModifier implements GestureModifier {
  public static readonly longPressTime: number = 500;
  public static readonly minFontSize: number = 1.75;
  public fontSize: number = 1;
  public controller: CustomDialogController | null = null;

  constructor(controller: CustomDialogController | null) {
    this.controller = controller;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
          .onAction(() => {
            if (event) {
              this.controller?.open();
            }
          })
          .onActionEnd(() => {
            this.controller?.close();
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

@Component
export struct TabTitleBar {
  tabItems: Array<TabTitleBarTabItem> = [];
  menuItems: Array<TabTitleBarMenuItem> = [];
  @BuilderParam swiperContent: () => void

  @State tabWidth: number = 0
  @State currentIndex: number = 0
  @State fontSize: number = 1

  static readonly totalHeight = 56
  static readonly correctionOffset = -40.0
  static readonly gradientMaskWidth = 24
  private static instanceCount = 0

  private menuSectionWidth = 0
  private tabOffsets: Array<number> = [];
  private imageWidths: Array<number> = [];

  private scroller: Scroller = new Scroller()
  private swiperController: SwiperController = new SwiperController()
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private leftContext2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)
  private rightContext2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings)

  @Builder
  GradientMask(context2D: CanvasRenderingContext2D, x0: number, y0: number, x1: number, y1: number) {
    Column() {
      Canvas(context2D)
        .width(TabTitleBar.gradientMaskWidth)
        .height(TabTitleBar.totalHeight)
        .onReady(() => {
          let grad = context2D.createLinearGradient(x0, y0, x1, y1);
          grad.addColorStop(0.0, '#ffffffff')
          grad.addColorStop(1, '#00ffffff')
          context2D.fillStyle = grad
          context2D.fillRect(0, 0, TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight)
        })
    }
    .blendMode(BlendMode.DST_OUT)
    .width(TabTitleBar.gradientMaskWidth)
    .height(TabTitleBar.totalHeight)
  }

  @Builder
  emptyBuilder() {
  }

  aboutToAppear() {
    if (!this.swiperContent) {
      this.swiperContent = this.emptyBuilder;
    }
    this.tabItems.forEach((_elem) => {
      this.imageWidths.push(0)
    })
    this.loadOffsets()
  }

  loadOffsets() {
    this.tabOffsets.length = 0

    let tabOffset = 0
    this.tabOffsets.push(tabOffset)
    tabOffset += TabContentItem.marginFirst

    this.tabItems.forEach((tabItem, index) => {
      if (tabItem.icon !== undefined || tabItem.symbolStyle !== undefined) {
        if (Math.abs(this.imageWidths[index]) > TabContentItem.imageHotZoneWidth) {
          tabOffset += this.imageWidths[index]
        } else {
          tabOffset += TabContentItem.imageHotZoneWidth
        }
      } else {
        tabOffset += TabContentItem.paddingLeft
        tabOffset += px2vp(MeasureText.measureText({
          textContent: tabItem.title.toString(),
          fontSize: 18,
          fontWeight: FontWeight.Medium,
        }))
        tabOffset += TabContentItem.paddingRight
      }
      this.tabOffsets.push(tabOffset)
    })
  }

  build() {
    Column() {
      Flex({
        justifyContent: FlexAlign.SpaceBetween,
        alignItems: ItemAlign.Stretch
      }) {
        Stack({ alignContent: Alignment.End }) {
          Stack({ alignContent: Alignment.Start }) {
            Column() {
              List({ initialIndex: 0, scroller: this.scroller, space: 0 }) {
                ForEach(this.tabItems, (tabItem: TabTitleBarTabItem, index: number) => {
                  ListItem() {
                    TabContentItem({
                      item: tabItem,
                      index: index,
                      maxIndex: this.tabItems.length - 1,
                      currentIndex: this.currentIndex,
                      onCustomClick: (itemIndex) => this.currentIndex = itemIndex,
                      onImageComplete: (width) => {
                        this.imageWidths[index] = width
                        this.loadOffsets()
                      }
                    })
                  }
                })
              }
              .width('100%')
              .height(TabTitleBar.totalHeight)
              .constraintSize({ maxWidth: this.tabWidth })
              .edgeEffect(EdgeEffect.Spring)
              .listDirection(Axis.Horizontal)
              .scrollBar(BarState.Off)
            }
            this.GradientMask(this.leftContext2D, 0, TabTitleBar.totalHeight / 2,
              TabTitleBar.gradientMaskWidth, TabTitleBar.totalHeight / 2)
          }
          this.GradientMask(this.rightContext2D, TabTitleBar.gradientMaskWidth,
            TabTitleBar.totalHeight / 2, 0, TabTitleBar.totalHeight / 2)
        }
        .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)

        if (this.menuItems !== undefined && this.menuItems.length > 0) {
          CollapsibleMenuSection({ menuItems: this.menuItems, index: 1 + TabTitleBar.instanceCount++ })
            .height(TabTitleBar.totalHeight)
            .onAreaChange((_oldValue, newValue) => {
              this.menuSectionWidth = Number(newValue.width)
            })
        }
      }
      .backgroundColor($r('sys.color.ohos_id_color_background'))
      .margin({ right: $r('sys.float.ohos_id_max_padding_end') })
      .onAreaChange((_oldValue, newValue) => {
        this.tabWidth = Number(newValue.width) - this.menuSectionWidth
      })

      Column() {
        Swiper(this.swiperController) { this.swiperContent() }
        .index(this.currentIndex)
        .itemSpace(0)
        .indicator(false)
        .width('100%')
        .height('100%')
        .curve(Curve.Friction)
        .onChange((index) => {
          const offset = this.tabOffsets[index] + TabTitleBar.correctionOffset
          this.currentIndex = index
          this.scroller.scrollTo({
            xOffset: offset > 0 ? offset : 0,
            yOffset: 0,
            animation: {
              duration: 300,
              curve: Curve.EaseInOut
            }
          })
        })
        .onAppear(() => {
          this.scroller.scrollToIndex(this.currentIndex)
          this.scroller.scrollBy(TabTitleBar.correctionOffset, 0)
        })
      }
    }
  }
}

@Component
struct CollapsibleMenuSection {
  menuItems: Array<TabTitleBarMenuItem> = [];
  index: number = 0;
  item: TabTitleBarMenuItem = {
    value: PUBLIC_MORE,
    symbolStyle: new SymbolGlyphModifier(PUBLIC_MORE),
    label: $r('sys.string.ohos_toolbar_more'),
  } as TabTitleBarMenuItem;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;

  static readonly maxCountOfVisibleItems = 1
  private static readonly focusPadding = 4
  private static readonly marginsNum = 2
  private firstFocusableIndex = -1

  @State isPopupShown: boolean = false

  @State isMoreIconOnFocus: boolean = false
  @State isMoreIconOnHover: boolean = false
  @State isMoreIconOnClick: boolean = false
  @Prop @Watch('onFontSizeUpdated') fontSize: number = 1;

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: TabTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      tabTitleDialog: this.item,
      tabTitleBarDialog: this.item.label ? this.item.label : '',
      fontSize: this.fontSize,
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true,
  })

  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  getMoreIconFgColor() {
    return this.isMoreIconOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isMoreIconOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
    }
    this.menuItems.forEach((item, index) => {
      if (item.isEnabled && this.firstFocusableIndex === -1 &&
        index > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + index + 1
      }
    })
    this.fontSize = this.decideFontScale()
  }

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale, this.maxFontScale);
  }

  onFontSizeUpdated(): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
          ForEach(this.menuItems, (item: TabTitleBarMenuItem, index: number) => {
            ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 })
          })
        } else {
          ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
            (item: TabTitleBarMenuItem, index: number) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 })
            })

          Button({ type: ButtonType.Normal, stateEffect: true }) {
            SymbolGlyph(PUBLIC_MORE)
              .fontSize(TabContentItem.symbolSize)
              .draggable(false)
              .fontColor([$r('sys.color.icon_primary')])
              .focusable(true)
          }
          .accessibilityText($r('sys.string.ohos_toolbar_more'))
          .width(ImageMenuItem.imageHotZoneWidth)
          .height(ImageMenuItem.imageHotZoneWidth)
          .borderRadius(ImageMenuItem.buttonBorderRadius)
          .foregroundColor(this.getMoreIconFgColor())
          .backgroundColor(this.getMoreIconBgColor())
          .stateStyles({
            focused: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: ImageMenuItem.focusBorderWidth,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
            },
            normal: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0
              })
            }
          })
          .onFocus(() => this.isMoreIconOnFocus = true)
          .onBlur(() => this.isMoreIconOnFocus = false)
          .onHover((isOn) => this.isMoreIconOnHover = isOn)
          .onKeyEvent((event) => {
            if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
              return
            }
            if (event.type === KeyType.Down) {
              this.isMoreIconOnClick = true
            }
            if (event.type === KeyType.Up) {
              this.isMoreIconOnClick = false
            }
          })
          .onTouch((event) => {
            if (event.type === TouchType.Down) {
              this.isMoreIconOnClick = true
            }
            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
              this.isMoreIconOnClick = false
              if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close()
              }
            }
          })
          .onClick(() => this.isPopupShown = true)
          .gestureModifier(this.buttonGestureModifier)
          .bindPopup(this.isPopupShown, {
            builder: this.popupBuilder,
            placement: Placement.Bottom,
            popupColor: Color.White,
            enableArrow: false,
            onStateChange: (e) => {
              this.isPopupShown = e.isVisible
              if (!e.isVisible) {
                this.isMoreIconOnClick = false
              }
            }
          })
        }
      }
    }
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
    this.fontSize = this.decideFontScale();
  }

  @Builder
  popupBuilder() {
    Column() {
      ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1, this.menuItems.length),
        (item: TabTitleBarMenuItem, index: number) => {
          ImageMenuItem({ item: item, index: this.index * 1000 +
          CollapsibleMenuSection.maxCountOfVisibleItems + index })
        })
    }
    .width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding })
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex)
    })
  }
}

@Component
struct TabContentItem {
  item: TabTitleBarTabItem = { title: '' };
  index: number = 0;
  maxIndex: number = 0;
  onCustomClick?: (index: number) => void
  onImageComplete?: (width: number) => void

  @Prop currentIndex: number

  @State isOnFocus: boolean = false
  @State isOnHover: boolean = false
  @State isOnClick: boolean = false
  @State tabWidth: number = 0

  @State imageWidth: number = 24
  @State imageHeight: number = 24

  static readonly imageSize = 24
  static readonly symbolSize = '24vp'
  static readonly imageHotZoneWidth = 48
  static readonly imageMagnificationFactor = 1.4
  static readonly buttonBorderRadius = 8
  static readonly focusBorderWidth = 2
  static readonly paddingLeft = 8
  static readonly paddingRight = 8
  static readonly marginFirst = 16

  getBgColor() {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  getBorderAttr(): BorderOptions {
    if (this.isOnFocus) {
      return {
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: TabContentItem.focusBorderWidth,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
      }
    }
    return { width: 0 }
  }

  getImageScaleFactor(): number {
    return this.index === this.currentIndex ? TabContentItem.imageMagnificationFactor : 1
  }

  getImageLayoutWidth(): number {
    return TabContentItem.imageSize / Math.max(this.imageHeight, 1.0) * this.imageWidth
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource;
    } else if (typeof resource === 'undefined') {
      return '';
    } else {
      let resourceString: string = '';
      try {
        resourceString = getContext()?.resourceManager?.getStringSync(resource);
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  build() {
    Stack() {
      Row() {
        Column() {
          if (this.item.icon === undefined && this.item.symbolStyle === undefined) {
            Text(this.item.title)
              .fontSize(this.index === this.currentIndex
                ? $r('sys.float.ohos_id_text_size_headline7')
                : $r('sys.float.ohos_id_text_size_headline9'))
              .fontColor(this.index === this.currentIndex
                ? $r('sys.color.ohos_id_color_titlebar_text')
                : $r('sys.color.ohos_id_color_titlebar_text_off'))
              .fontWeight(FontWeight.Medium)
              .focusable(true)
              .animation({ duration: 300 })
              .padding({
                top: this.index === this.currentIndex ? 6 : 10,
                left: TabContentItem.paddingLeft,
                bottom: 2,
                right: TabContentItem.paddingRight
              })
              .onFocus(() => this.isOnFocus = true)
              .onBlur(() => this.isOnFocus = false)
              .onHover((isOn) => this.isOnHover = isOn)
              .onKeyEvent((event) => {
                if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                  return
                }
                if (event.type === KeyType.Down) {
                  this.isOnClick = true
                }
                if (event.type === KeyType.Up) {
                  this.isOnClick = false
                }
              })
              .onTouch((event) => {
                if (event.type === TouchType.Down) {
                  this.isOnClick = true
                }
                if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                  this.isOnClick = false
                }
              })
              .onClick(() => this.onCustomClick && this.onCustomClick(this.index))
              .accessibilitySelected(this.index === this.currentIndex)
          } else {
            Row() {
              if (this.item.symbolStyle) {
                SymbolGlyph()
                  .fontColor([$r('sys.color.icon_primary')])
                  .attributeModifier(this.item.symbolStyle)
                  .fontSize(TabContentItem.symbolSize)
                  .width(this.getImageLayoutWidth())
                  .height(TabContentItem.imageSize)
                  .accessibilityText(this.toStringFormat(this.item.title))
                  .scale({
                    x: this.getImageScaleFactor(),
                    y: this.getImageScaleFactor()
                  })
                  .animation({ duration: 300 })
                  .hitTestBehavior(HitTestMode.None)
                  .focusable(true)
                  .symbolEffect(new SymbolEffect(), false)
              } else {
                if (Util.isSymbolResource(this.item.icon)) {
                  SymbolGlyph(this.item.icon as Resource)
                    .fontColor([$r('sys.color.icon_primary')])
                    .fontSize(TabContentItem.symbolSize)
                    .width(this.getImageLayoutWidth())
                    .height(TabContentItem.imageSize)
                    .accessibilityText(this.toStringFormat(this.item.title))
                    .scale({
                      x: this.getImageScaleFactor(),
                      y: this.getImageScaleFactor()
                    })
                    .animation({ duration: 300 })
                    .hitTestBehavior(HitTestMode.None)
                    .focusable(true)
                } else {
                  Image(this.item.icon)
                    .alt(this.item.title)
                    .width(this.getImageLayoutWidth())
                    .height(TabContentItem.imageSize)
                    .objectFit(ImageFit.Fill)
                    .accessibilityText(this.toStringFormat(this.item.title))
                    .scale({
                      x: this.getImageScaleFactor(),
                      y: this.getImageScaleFactor()
                    })
                    .animation({ duration: 300 })
                    .hitTestBehavior(HitTestMode.None)
                    .focusable(true)
                    .onComplete((event) => {
                      if (!this.onImageComplete) {
                        return
                      }
                      this.imageWidth = px2vp(event?.width);
                      this.imageHeight = px2vp(event?.height);
                      this.onImageComplete(px2vp(event?.componentWidth) +
                      TabContentItem.paddingLeft + TabContentItem.paddingRight);
                    })
                    .onError((event) => {
                      if (!this.onImageComplete) {
                        return
                      }
                      this.onImageComplete(px2vp(event.componentWidth) +
                      TabContentItem.paddingLeft + TabContentItem.paddingRight)
                    })
                }
              }
            }
            .width(this.getImageLayoutWidth() * this.getImageScaleFactor() +
            TabContentItem.paddingLeft + TabContentItem.paddingRight)
            .constraintSize({
              minWidth: TabContentItem.imageHotZoneWidth,
              minHeight: TabContentItem.imageHotZoneWidth
            })
            .animation({ duration: 300 })
            .justifyContent(FlexAlign.Center)
            .onFocus(() => this.isOnFocus = true)
            .onBlur(() => this.isOnFocus = false)
            .onHover((isOn) => this.isOnHover = isOn)
            .onKeyEvent((event) => {
              if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return
              }
              if (event.type === KeyType.Down) {
                this.isOnClick = true
              }
              if (event.type === KeyType.Up) {
                this.isOnClick = false
              }
            })
            .onTouch((event) => {
              if (event.type === TouchType.Down) {
                this.isOnClick = true
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                this.isOnClick = false
              }
            })
            .onClick(() => this.onCustomClick && this.onCustomClick(this.index))
            .accessibilitySelected(this.index === this.currentIndex)
          }
        }
        .justifyContent(FlexAlign.Center)
      }
      .height(TabTitleBar.totalHeight)
      .alignItems(VerticalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .borderRadius(TabContentItem.buttonBorderRadius)
      .backgroundColor(this.getBgColor())
      .onAreaChange((_oldValue, newValue) => {
        this.tabWidth = Number(newValue.width)
      })

      if (this.isOnFocus && this.tabWidth > 0) {
        Row()
          .width(this.tabWidth)
          .height(TabTitleBar.totalHeight)
          .hitTestBehavior(HitTestMode.None)
          .borderRadius(TabContentItem.buttonBorderRadius)
          .stateStyles({
            focused: {
              .border(this.getBorderAttr())
            },
            normal: {
              .border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0
              })
            }
          })
      }
    }
    .margin({
      left: this.index === 0 ? TabContentItem.marginFirst : 0,
      right: this.index === this.maxIndex ? 12 : 0
    })
  }
}

@Component
struct ImageMenuItem {
  item: TabTitleBarMenuItem = { value: '' };
  index: number = 0;

  static readonly imageSize = 24
  static readonly imageHotZoneWidth = 48
  static readonly buttonBorderRadius = 8
  static readonly focusBorderWidth = 2
  static readonly disabledImageOpacity = 0.4
  static readonly focusablePrefix = "Id-TabTitleBar-ImageMenuItem-"

  @State isOnFocus: boolean = false
  @State isOnHover: boolean = false
  @State isOnClick: boolean = false

  getFgColor() {
    return this.isOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getBgColor() {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource;
    } else if (typeof resource === 'undefined') {
      return '';
    } else {
      let resourceString: string = '';
      try {
        resourceString = getContext()?.resourceManager?.getStringSync(resource);
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to TabTitleBar toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_MORE) {
      return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
    } else if (this.item.accessibilityText) {
      return this.toStringFormat(this.item.accessibilityText);
    } else if (this.item.label) {
      return this.toStringFormat(this.item.label);
    }
    return ' ';
  }

  build() {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
      if (this.item.symbolStyle) {
        SymbolGlyph()
          .fontColor([$r('sys.color.font_primary')])
          .attributeModifier(this.item.symbolStyle)
          .fontSize(TabContentItem.symbolSize)
          .draggable(false)
          .focusable(this.item?.isEnabled)
          .key(ImageMenuItem.focusablePrefix + this.index)
          .symbolEffect(new SymbolEffect(), false)
      } else {
        if (Util.isSymbolResource(this.item.value)) {
          SymbolGlyph(this.item.value as Resource)
            .fontColor([$r('sys.color.font_primary')])
            .fontSize(TabContentItem.symbolSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index)
        } else {
          Image(this.item.value)
            .width(ImageMenuItem.imageSize)
            .height(ImageMenuItem.imageSize)
            .focusable(this.item.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index)
            .draggable(false)
        }
      }
    }
    .accessibilityText(this.getAccessibilityReadText())
    .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
    .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription))
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius(ImageMenuItem.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .opacity(this.item.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity)
    .enabled(this.item.isEnabled ? this.item.isEnabled : false)
    .stateStyles({
      focused: {
        .border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: ImageMenuItem.focusBorderWidth,
          color: $r('sys.color.ohos_id_color_focused_outline'),
          style: BorderStyle.Solid
        })
      },
      normal: {
        .border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: 0
        })
      }
    })
    .onFocus(() => {
      if (!this.item.isEnabled) {
        return
      }
      this.isOnFocus = true
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item.isEnabled) {
        return
      }
      this.isOnHover = isOn
    })
    .onKeyEvent((event) => {
      if (!this.item.isEnabled) {
        return
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return
      }
      if (event.type === KeyType.Down) {
        this.isOnClick = true
      }
      if (event.type === KeyType.Up) {
        this.isOnClick = false
      }
    })
    .onTouch((event) => {
      if (!this.item.isEnabled) {
        return
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.isOnClick = false
      }
    })
    .onClick(() => this.item.isEnabled && this.item.action && this.item.action())
  }
}

/**
 *  TabTitleBarDialog
 */
@CustomDialog
struct TabTitleBarDialog {
  tabTitleDialog: TabTitleBarMenuItem = { value: '' };
  callbackId: number | undefined = undefined;
  tabTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: number = 6;
  horizontalsScreenLines: number = 1;
  @StorageLink('mainWindow') mainWindow: Promise<window.Window> | undefined = undefined;
  @State fontSize: number = 1;
  @State maxLines: number = 1;
  @StorageProp('windowStandardHeight') windowStandardHeight: number = 0;
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    if (this.tabTitleBarDialog) {
      Column() {
        if (this.tabTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.tabTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.tabTitleDialog?.isEnabled)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.tabTitleDialog.value) {
          if (Util.isSymbolResource(this.tabTitleDialog.value)) {
            SymbolGlyph(this.tabTitleDialog.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.tabTitleDialog?.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
          } else {
            Image(this.tabTitleDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
              .fillColor($r('sys.color.icon_primary'))
          }
        }
        Column() {
          Text(this.tabTitleBarDialog)
            .fontSize(TEXT_EDITABLE_DIALOG)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .maxLines(this.maxLines)
            .width('100%')
            .textAlign(TextAlign.Center)
            .fontColor($r('sys.color.font_primary'))
        }
        .width('100%')
        .padding({
          left: $r('sys.float.padding_level4'),
          right: $r('sys.float.padding_level4'),
          bottom: $r('sys.float.padding_level12'),
        })
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
    } else {
      Column() {
        if (this.tabTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.tabTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.tabTitleDialog?.isEnabled)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.tabTitleDialog.value){
          if (Util.isSymbolResource(this.tabTitleDialog.value)) {
            SymbolGlyph(this.tabTitleDialog.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.tabTitleDialog?.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
          } else {
            Image(this.tabTitleDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
      .justifyContent(FlexAlign.Center)
    }
  }

  async aboutToAppear(): Promise<void> {
    let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
    this.mainWindowStage = context.windowStage.getMainWindowSync();
    let properties: window.WindowProperties = this.mainWindowStage.getWindowProperties();
    let rect = properties.windowRect;
    if (px2vp(rect.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines;
    } else {
      this.maxLines = this.horizontalsScreenLines;
    }
  }
}

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr | Resource | undefined): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}