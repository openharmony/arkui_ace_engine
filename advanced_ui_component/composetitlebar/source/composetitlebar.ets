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

import {KeyCode} from '@ohos.multimodalInput.keyCode'
import window from '@ohos.window'
import common from '@ohos.app.ability.common'
import { BusinessError } from '@kit.BasicServicesKit'
import { hilog } from '@kit.PerformanceAnalysisKit'
import { SymbolGlyphModifier } from '@kit.ArkUI'

export interface ComposeTitleBarMenuItem {
  value: ResourceStr
  symbolStyle?: SymbolGlyphModifier
  isEnabled?: boolean
  action?: ()=> void
  label?: ResourceStr
  accessibilityText?: ResourceStr
  accessibilityLevel?: string
  accessibilityDescription?: ResourceStr
}

const PUBLIC_BACK = $r('sys.symbol.arrow_left')
const PUBLIC_MORE = $r('sys.symbol.dot_grid_2x2')

const TEXT_EDITABLE_DIALOG = '18.3fp'
const IMAGE_SIZE = '64vp'
const MAX_DIALOG = '256vp'
const MIN_DIALOG = '216vp'
const SYMBOL_SIZE = '24vp'

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
struct ComposeTitleBar{
  item: ComposeTitleBarMenuItem | undefined = undefined
  title: ResourceStr = ''
  subtitle: ResourceStr = ''
  menuItems?: Array<ComposeTitleBarMenuItem> = []

  @State titleMaxWidth: number = 0
  @State backActive: boolean = false
  @State fontSize: number = 1

  private static readonly totalHeight = 56
  private static readonly leftPadding = 12
  private static readonly rightPadding = 12
  private static readonly portraitImageSize = 40
  private static readonly portraitImageLeftPadding = 4
  private static readonly portraitImageRightPadding = 16
  private static instanceCount = 0

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        Navigator()
          .active(this.backActive)

        ImageMenuItem({ symbolItem: {
          value: PUBLIC_BACK,
          symbolStyle: new SymbolGlyphModifier(PUBLIC_BACK).fontColor([$r('sys.color.ohos_id_color_text_primary')]),
          isEnabled: true,
          action: () => this.backActive = true,
        },
          index: -1,
          isLeftBackFlag: true,
          isSymbol: true
        })

        Row() {
          if (this.item !== undefined) {
            Image(this.item.value)
              .width(ComposeTitleBar.portraitImageSize)
              .height(ComposeTitleBar.portraitImageSize)
              .margin({
                left: $r('sys.float.ohos_id_text_paragraph_margin_xs'),
                right: $r('sys.float.ohos_id_text_paragraph_margin_m')
              })
              .focusable(false)
              .borderRadius((ImageMenuItem.buttonBorderRadius))
          }

          Column() {
            if (this.title !== undefined) {
              Row() {
                Text(this.title)
                  .fontWeight(FontWeight.Medium)
                  .fontSize($r('sys.float.ohos_id_text_size_headline8'))
                  .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
                  .maxLines(this.subtitle !== undefined ? 1 : 2)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .constraintSize({ maxWidth: this.titleMaxWidth })
              }
              .justifyContent(FlexAlign.Start)
            }
            if (this.subtitle !== undefined) {
              Row() {
                Text(this.subtitle)
                  .fontSize($r('sys.float.ohos_id_text_size_over_line'))
                  .fontColor($r('sys.color.ohos_id_color_titlebar_subtitle_text'))
                  .maxLines(1)
                  .textOverflow({ overflow: TextOverflow.Ellipsis })
                  .constraintSize({ maxWidth: this.titleMaxWidth })
              }
              .justifyContent(FlexAlign.Start)
            }
          }
          .justifyContent(FlexAlign.Start)
          .alignItems(HorizontalAlign.Start)
          .constraintSize({ maxWidth: this.titleMaxWidth })
        }
        .accessibilityGroup(true)
      }
      .margin({ left: $r('sys.float.ohos_id_default_padding_start')})

      if(this.menuItems !== undefined && this.menuItems.length > 0){
        if(this.menuItems[0].symbolStyle !== undefined){
          CollapsibleMenuSection({
            symbolMenuItems: this.menuItems,
            index: 1+ ComposeTitleBar.instanceCount++ })
        }else{
          CollapsibleMenuSection({
            menuItems: this.menuItems,
            index: 1 + ComposeTitleBar.instanceCount++ })
        }
      }
    }
    .width('100%')
    .height(ComposeTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange(( _oldValue: Area, newValue: Area) => {
      let newWidth = Number(newValue.width)
      if(this.menuItems !== undefined){
        let menusLength = this.menuItems.length
        if(menusLength >= CollapsibleMenuSection.maxCountOfVisibleItems) {
          newWidth = newWidth - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems
        }else if (menusLength > 0){
          newWidth = newWidth - ImageMenuItem.imageHotZoneWidth * menusLength
        }
      }
      this.titleMaxWidth = newWidth
      this.titleMaxWidth -= ComposeTitleBar.leftPadding
      this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth
      if(this.item !== undefined) {
        this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
        ComposeTitleBar.portraitImageSize +
        ComposeTitleBar.portraitImageRightPadding
      }
      this.titleMaxWidth -= ComposeTitleBar.rightPadding
    })
  }
}


@Component
struct CollapsibleMenuSection{
  menuItems: Array<ComposeTitleBarMenuItem> = []
  symbolMenuItems: Array<ComposeTitleBarMenuItem> = []
  item: ComposeTitleBarMenuItem = {
    value: PUBLIC_MORE,
    label: $r('sys.string.ohos_toolbar_more')
  } as ComposeTitleBarMenuItem
  index: number = 0
  minFontSize: number = 1.75
  isFollowingSystemFontScale: boolean = false
  maxFontScale: number = 1
  systemFontScale?: number = 1

  static readonly maxCountOfVisibleItems = 3
  private static readonly focusPadding = 4
  private static readonly marginsNum = 2
  private firstFocusableIndex = -1

  @State isPopupShown: boolean = false
  @State isMoreIconOnFocus: boolean = false
  @State isMoreIconOnHover: boolean = false
  @State isMoreIconOnClick: boolean = false
  @Prop @Watch('onFontSizeUpdated') fontSize: number = 1;
  @State publicMoreCounter: number = -1

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: ComposeTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      itemComposeTitleDialog: this.item,
      composeTitleBarDialog: this.item.label ? this.item.label : '',
      fontSize: this.fontSize
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true
  })

  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  getMoreIconFgColor() {
    return this.isMoreIconOnClick ?
    $r('sys.color.ohos_id_color_titlebar_icon_pressed') :
    $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    }else if (this.isMoreIconOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    }else {
      return Color.Transparent
    }
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext()
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale()
      this.maxFontScale = uiContent.getMaxFontScale()
    }catch (err) {
      let code: number = (err as BusinessError).code
      let message: string = (err as BusinessError).message
      hilog.error(0x3900, 'ComposeTitleBar', 'Failed to init fontsizescale info, cause, code: ${code}, message: ${message}')
    }
    if(this.menuItems) {
      this.menuItems.forEach((item, index) => {
        if (item.isEnabled && this.firstFocusableIndex == -1 &&
          index > CollapsibleMenuSection.maxCountOfVisibleItems - 2){
          this.firstFocusableIndex = this.index * 1000 + index + 1
        }
      })
    }
    this.fontSize = this.decideFontScale()
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext()
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1
      if (!this.isFollowingSystemFontScale) {
        return 1
      }
      return Math.min(this.systemFontScale, this.maxFontScale)
    }catch (exception) {
      let code: number = (exception as BusinessError).code
      let message: string = (exception as BusinessError).message
      hilog.error(0x3900, 'ComposeTitleBar', 'Failed to decideFontScale,cause, code: ${code}, message: ${message}')
      return 1
    }
  }

  onFontSizeUpdated(): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems != undefined && this.menuItems.length > 0 ) {
          if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
            ForEach(this.menuItems, (item: ComposeTitleBarMenuItem, index: number) => {
              ImageMenuItem({item: item, index: this.index *1000 + index + 1})
            })
          }else {
            ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              (item: ComposeTitleBarMenuItem, index: number) => {
                ImageMenuItem({item: item, index: this.index *1000 + index + 1})
              })

            Button({ type: ButtonType.Normal, stateEffect: true }) {
              SymbolGlyph(PUBLIC_MORE)
                .width(ImageMenuItem.imageSize)
                .draggable(false)
                .height(ImageMenuItem.imageSize)
                .fontColor([$r('sys.color.ohos_id_color_text_primary')])
                .focusable(true)
                .symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicMoreCounter)
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
              if (!this.item?.isEnabled) {
                return
              }
              if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return
              }
              if (event.type == KeyType.Down) {
                this.isMoreIconOnClick = true
              }
              if (event.type == KeyType.Up) {
                this.isMoreIconOnClick = false
              }
            })
            .onTouch((event) => {
              if (event.type === TouchType.Down) {
                this.isMoreIconOnClick = true
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                this.isMoreIconOnClick = false
                if (this.fontSize >= this.minFontSize ) {
                  this.dialogController?.close()
                }
              }
            })
            .onClick(() => {
              this.isPopupShown = true
              this.publicMoreCounter += 1
            })
            .gestureModifier(this.buttonGestureModifier)
            .bindPopup(this.isPopupShown, {
              builder: this.popupBuilder,
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (e) => {
                this.isPopupShown = e.isVisible
                if ( !e.isVisible ) {
                  this.isMoreIconOnClick = false
                }
              }
            })
          }
        }

        if (this.symbolMenuItems != undefined && this.symbolMenuItems.length > 0 ) {
          if (this.symbolMenuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
            ForEach(this.symbolMenuItems, (item: ComposeTitleBarMenuItem, index: number) => {
              ImageMenuItem({symbolItem: item, isSymbol: true, index: this.index *1000 + index + 1})
            })
          }else {
            ForEach(this.symbolMenuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              (item: ComposeTitleBarMenuItem, index: number) => {
                ImageMenuItem({symbolItem: item, isSymbol: true, index: this.index *1000 + index + 1})
              })

            Button({ type: ButtonType.Normal, stateEffect: true }) {
              SymbolGlyph(PUBLIC_MORE)
                .width(ImageMenuItem.imageSize)
                .draggable(false)
                .height(ImageMenuItem.imageSize)
                .fontColor([$r('sys.color.ohos_id_color_text_primary')])
                .focusable(true)
                .symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE, EffectDirection.DOWN), this.publicMoreCounter)
            }
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
              if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return
              }
              if (event.type == KeyType.Down) {
                this.isMoreIconOnClick = true
              }
              if (event.type == KeyType.Up) {
                this.isMoreIconOnClick = false
              }
            })
            .onTouch((event) => {
              if (event.type === TouchType.Down) {
                this.isMoreIconOnClick = true
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                this.isMoreIconOnClick = false
                if (this.fontSize >= this.minFontSize ) {
                  this.dialogController?.close()
                }
              }
            })
            .onClick(() => {
              this.isPopupShown = true
              this.publicMoreCounter += 1
            })
            .gestureModifier(this.buttonGestureModifier)
            .bindPopup(this.isPopupShown, {
              builder: this.popupBuilder,
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (e) => {
                this.isPopupShown = e.isVisible
                if ( !e.isVisible ) {
                  this.isMoreIconOnClick = false
                }
              }
            })
          }
        }
      }
    }
    .height('100%')
    .margin({ right: $r('sys.float.ohos_id_default_padding_end') })
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  popupBuilder() {
    Column() {
      if (this.symbolMenuItems != undefined && this.symbolMenuItems.length > 0){
        ForEach(this.symbolMenuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
          this.symbolMenuItems.length),
          (item: ComposeTitleBarMenuItem, index: number) => {
            ImageMenuItem({ symbolItem: item, isSymbol: true, index: this.index * 1000 +
            CollapsibleMenuSection.maxCountOfVisibleItems + index, isPopup: true})
          })
      }

      if (this.menuItems != undefined && this.menuItems.length > 0){
        ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
          this.menuItems.length),
          (item: ComposeTitleBarMenuItem, index: number) => {
            ImageMenuItem({ item: item, isSymbol: true, index: this.index * 1000 +
            CollapsibleMenuSection.maxCountOfVisibleItems + index, isPopup: true})
          })
      }
    }
    .width(ImageMenuItem.imageHotZoneWidth +
      CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding })
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItem.focusablePrefix +
      this.firstFocusableIndex)
    })
  }
}

@Component
struct ImageMenuItem{
  isLeftBackFlag: boolean = false
  item: ComposeTitleBarMenuItem = {} as ComposeTitleBarMenuItem
  symbolItem: ComposeTitleBarMenuItem = {} as ComposeTitleBarMenuItem
  index: number = 0
  minFontSize: number = 1.75
  isFollowingSystemFontScale: boolean = false
  maxFontScale: number = 1
  systemFontScale?: number = 1
  isPopup: boolean = false
  isSymbol: boolean = false

  static readonly imageSize = 24
  static readonly imageHotZoneWidth = 48
  static readonly buttonBorderRadius = 8
  static readonly focusBorderWidth = 2
  static readonly disabledImageOpacity = 0.4
  static readonly focusablePrefix = "Id-ComposeTitleBar-ImageMenuItem-"

  @State isOnFocus: boolean = false
  @State isOnHover: boolean = false
  @State isOnClick: boolean = false
  @State publicBackCounter: number = -1
  @Prop @Watch('onFontSizeUpdated') fontSize: number = 1;

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: ComposeTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      itemComposeTitleDialog: this.item,
      itemComposeTitleSymbolDialog: this.symbolItem,
      isSymbol: this.isSymbol,
      composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
      composeTitleBarSymbolDialog: this.symbolItem.label ? this.symbolItem.label : this.textDialog(),
      fontSize: this.fontSize
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true
  })

  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  private textDialog(): ResourceStr {
    if(this.isSymbol){
      if (this.symbolItem.value === PUBLIC_BACK){
        return $r('sys.string.ohos_toolbar_more')
      }else if (this.symbolItem.value === PUBLIC_MORE){
        return $r('sys.string.icon_back')
      }else {
        return this.item.label ? this.item.label : '';
      }
    }else{
      return this.item.label ? this.item.label : '';
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
        hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_BACK) {
      return this.toStringFormat($r('sys.string.icon_back'));
    } else if (this.item.value === PUBLIC_MORE) {
      return this.toStringFormat($r('sys.string.ohos_toolbar_more'));
    } else if (this.item.accessibilityText) {
      return this.toStringFormat(this.item.accessibilityText);
    } else if (this.item.label) {
      return this.toStringFormat(this.item.label);
    }
    return ' ';
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Layoutable[], constraint: ConstraintSizeOptions): void {
    children.forEach((child) => {
      child.layout({ x: 0, y: 0 });
    })
    this.fontSize = this.decideFontScale();
  }

  getFgColor() {
    return this.isOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getBgColor() {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    }else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    }else {
      return Color.Transparent
    }
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext()
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale()
      this.maxFontScale = uiContent.getMaxFontScale()
    }catch (err) {
      let code: number = (err as BusinessError).code
      let message: string = (err as BusinessError).message
      hilog.error(0x3900, 'ComposeTitleBar', 'Failed to init fontsizescale info, cause, code: ${code}, message: ${message}')
    }
    this.fontSize = this.decideFontScale();
  }

  onFontSizeUpdated(): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext()
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1
      if (!this.isFollowingSystemFontScale) {
        return 1
      }
      return Math.min(this.systemFontScale, this.maxFontScale)
    }catch (exception) {
      let code: number = (exception as BusinessError).code
      let message: string = (exception as BusinessError).message
      hilog.error(0x3900, 'ComposeTitleBar', 'Failed to decideFontScale,cause, code: ${code}, message: ${message}')
      return 1
    }
  }

  build() {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
      if (this.isSymbol) {
        SymbolGlyph()
          .fontColor([$r('sys.color.icon_primary')])
          .attributeModifier(this.symbolItem.symbolStyle)
          .fontSize(SYMBOL_SIZE)
          .draggable(false)
          .focusable(this.symbolItem?.isEnabled)
          .key(ImageMenuItem.focusablePrefix + this.index)
          .symbolEffect(new BounceSymbolEffect(EffectScope.WHOLE,EffectDirection.DOWN),this.publicBackCounter)
      } else {
        Image(this.item?.value)
          .matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false)
          .width(ImageMenuItem.imageSize)
          .draggable(false)
          .height(ImageMenuItem.imageSize)
          .focusable(this.item?.isEnabled)
          .key(ImageMenuItem.focusablePrefix + this.index)
          .fillColor($r('sys.color.ohos_id_color_text_primary'))
      }
    }
    .accessibilityText(this.getAccessibilityReadText())
    .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
    .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription))
    .enabled(this.item.isEnabled ? this.item.isEnabled : false)
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius(ImageMenuItem.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .opacity(this.item?.isEnabled ? 1 : ImageMenuItem.disabledImageOpacity)
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
      if (!this.item?.isEnabled) {
        return
      }
      this.isOnFocus = true
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item?.isEnabled) {
        return
      }
      this.isOnHover = isOn
    })
    .onKeyEvent((event) => {
      if (!this.item?.isEnabled) {
        return
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
        event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return
      }
      if (event.type == KeyType.Down) {
        this.isOnClick = true
      }
      if (event.type == KeyType.Up) {
        this.isOnClick = false
      }
    })
    .onTouch((event) => {
      if (!this.item?.isEnabled) {
        return
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.isOnClick = false
        if (this.fontSize >= this.minFontSize && this.isPopup === false) {
          this.dialogController?.close()
        }
      }
    })
    .onClick(() => {
      if(this.isLeftBackFlag){
        this.publicBackCounter += 1
      }

      if(this.isSymbol) {
        return this.symbolItem.isEnabled && this.symbolItem.action?.()
      }else {
        return this.item.isEnabled && this.item.action?.()
      }
    })
    .gestureModifier(this.buttonGestureModifier)
  }
}

@CustomDialog
struct ComposeTitleBarDialog{
  itemComposeTitleDialog: ComposeTitleBarMenuItem = {} as ComposeTitleBarMenuItem
  itemComposeTitleSymbolDialog: ComposeTitleBarMenuItem = {} as ComposeTitleBarMenuItem
  isSymbol: boolean = false
  callbackId: number | undefined = undefined
  composeTitleBarDialog?: ResourceStr = ''
  composeTitleBarSymbolDialog?: ResourceStr = ''
  mainWindowStage: window.Window | undefined = undefined
  controller?: CustomDialogController
  minFontSize: number = 1.75
  maxFontSize: number = 3.2
  screenWidth: number = 640
  verticalScreenLines: number = 6
  horizontalsScreenLines: number = 1

  @StorageLink('mainWindow') mainWindow: Promise<window.Window> | undefined = undefined
  @State fontSize: number = 1
  @State maxLines: number = 1
  @StorageProp('windowStandardHeight') windowStandardHeight: number = 0

  cancel: () => void = () => {
  }

  confirm: () => void = () => {
  }

  build() {
    if(this.isSymbol) {
      if (this.composeTitleBarSymbolDialog) {
        Column() {
          SymbolGlyph()
            .fontColor([$r('sys.color.ohos_id_color_text_primary')])
            .attributeModifier(this.itemComposeTitleSymbolDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8')
            })
          Column() {
            Text(this.composeTitleBarSymbolDialog)
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
            bottom: $r('sys.float.padding_level12')
          })
        }
        .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
        .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
        .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
        .shadow(ShadowStyle.OUTER_DEFAULT_LG)
        .borderRadius($r('sys.float.corner_radius_level10'))
      }else {
        Column() {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.itemComposeTitleSymbolDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8')
            })
        }
        .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
        .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
        .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
        .shadow(ShadowStyle.OUTER_DEFAULT_LG)
        .borderRadius($r('sys.float.corner_radius_level10'))
        .justifyContent(FlexAlign.Center)
      }
    }else {
      if (this.composeTitleBarDialog) {
        Column() {
          Image(this.itemComposeTitleDialog.value)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8')
            })
          Column() {
            Text(this.composeTitleBarSymbolDialog)
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
            bottom: $r('sys.float.padding_level12')
          })
        }
        .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
        .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
        .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
        .shadow(ShadowStyle.OUTER_DEFAULT_LG)
        .borderRadius($r('sys.float.corner_radius_level10'))
      }else {
        Column() {
          Image(this.itemComposeTitleDialog.value)
            .width(IMAGE_SIZE)
            .height(IMAGE_SIZE)
            .fillColor($r('sys.color.icon_primary'))
        }
        .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
        .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
        .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK)
        .shadow(ShadowStyle.OUTER_DEFAULT_LG)
        .borderRadius($r('sys.float.corner_radius_level10'))
        .justifyContent(FlexAlign.Center)
      }
    }
  }

  async aboutToAppear(): Promise<void> {
    let context = this.getUIContext().getHostContext() as common.UIAbilityContext
    this.mainWindowStage = context.windowStage.getMainWindowSync()
    let properties: window.WindowProperties = this.mainWindowStage.getWindowProperties()
    let rect = properties.windowRect;
    if(px2vp(rect.height) > this.screenWidth) {
      this.maxLines = this.verticalScreenLines
    }else {
      this.maxLines = this.horizontalsScreenLines
    }
  }
}

export { ComposeTitleBar}




