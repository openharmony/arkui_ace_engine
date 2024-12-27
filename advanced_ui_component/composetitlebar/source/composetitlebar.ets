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

import { KeyCode } from '@ohos.multimodalInput.keyCode';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';

export interface ComposeTitleBarMenuItem {
  value: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: () => void;
  label?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityLevel?: string;
  accessibilityDescription?: ResourceStr;
}

const PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
const PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL: number = 40000;

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource: Resource = resourceStr as Resource;
    return resource.type === RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr | Resource | undefined | null): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}

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
struct ComposeTitleBar {
  item: ComposeTitleBarMenuItem | undefined = undefined;
  title: ResourceStr = '';
  subtitle: ResourceStr = '';
  menuItems?: Array<ComposeTitleBarMenuItem> = [];
  @State titleMaxWidth: number = 0;
  @State fontSize: number = 1;
  private static readonly totalHeight = 56;
  private static readonly leftPadding = 12;
  private static readonly rightPadding = 12;
  private static readonly portraitImageSize = 40;
  private static readonly portraitImageLeftPadding = 4;
  private static readonly portraitImageRightPadding = 16;
  private static instanceCount = 0;
  @Provide('uniqueId') uniqueId?: number = -1;

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        ImageMenuItem({
          item: {
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.getUIContext()?.getRouter()?.back()
          },
          index: -1,
          itemIndex: -1
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
              .borderRadius(ImageMenuItem.buttonBorderRadius)
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
      .margin({ left: $r('sys.float.ohos_id_default_padding_start') })

      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        CollapsibleMenuSection({ menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ })
      }
    }
    .onAppear(() => {
      this.uniqueId = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId())?.getFirstChild()?.getUniqueId();
    })
    .width('100%')
    .height(ComposeTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth = Number(newValue.width);
      if (this.menuItems !== undefined) {
        let menusLength = this.menuItems.length;
        if (menusLength >= CollapsibleMenuSection.maxCountOfVisibleItems) {
          newWidth = newWidth - ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
        } else if (menusLength > 0) {
          newWidth = newWidth - ImageMenuItem.imageHotZoneWidth * menusLength;
        }
      }
      this.titleMaxWidth = newWidth;
      this.titleMaxWidth -= ComposeTitleBar.leftPadding;
      this.titleMaxWidth -= ImageMenuItem.imageHotZoneWidth;
      if (this.item !== undefined) {
        this.titleMaxWidth -= ComposeTitleBar.portraitImageLeftPadding +
        ComposeTitleBar.portraitImageSize +
        ComposeTitleBar.portraitImageRightPadding;
      }
      this.titleMaxWidth -= ComposeTitleBar.rightPadding;
    })
  }
}

@Component
struct CollapsibleMenuSection {
  menuItems?: Array<ComposeTitleBarMenuItem> = [];
  item: ComposeTitleBarMenuItem = {
    value: PUBLIC_MORE,
    label: $r('sys.string.ohos_toolbar_more'),
  } as ComposeTitleBarMenuItem;
  index: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  static readonly maxCountOfVisibleItems = 3;
  private static readonly focusPadding = 4;
  private static readonly marginsNum = 2;
  private firstFocusableIndex = -1;
  @State isPopupShown: boolean = false;
  @State isMoreIconOnFocus: boolean = false;
  @State isMoreIconOnHover: boolean = false;
  @State isMoreIconOnClick: boolean = false;
  @Prop @Watch('onFontSizeUpdated') fontSize: number = 1;
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: ComposeTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      itemComposeTitleDialog: this.item,
      composeTitleBarDialog: this.item.label ? this.item.label : '',
      fontSize: this.fontSize,
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true,
  })

  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  getMoreIconFgColor() {
    return this.isMoreIconOnClick ?
    $r('sys.color.ohos_id_color_titlebar_icon_pressed') :
    $r('sys.color.ohos_id_color_titlebar_icon');
  }

  getMoreIconBgColor() {
    if (this.isMoreIconOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isMoreIconOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(0x3900, 'ComposeTitleBar',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    if (this.menuItems) {
      this.menuItems.forEach((item, index) => {
        if (item.isEnabled && this.firstFocusableIndex == -1 &&
          index > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
          this.firstFocusableIndex = this.index * 1000 + index + 1;
        }
      })
    }
    this.fontSize = this.decideFontScale()
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  onFontSizeUpdated(): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems) {
          if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
            ForEach(this.menuItems, (item: ComposeTitleBarMenuItem, index: number) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
            })
          } else {
            ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems - 1),
              (item: ComposeTitleBarMenuItem, index: number) => {
                ImageMenuItem({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
              })

            Button({ type: ButtonType.Normal, stateEffect: true }) {
              SymbolGlyph(PUBLIC_MORE)
                .fontSize(`${ImageMenuItem.imageSize}vp`)
                .fontColor([$r('sys.color.icon_primary')])
                .draggable(false)
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
              if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return;
              }
              if (event.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (event.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            })
            .onTouch((event) => {
              if (event.type === TouchType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
                this.isMoreIconOnClick = false;
                if (this.fontSize >= this.minFontSize) {
                  this.dialogController?.close();
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
                this.isPopupShown = e.isVisible;
                if (!e.isVisible) {
                  this.isMoreIconOnClick = false;
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
      if (this.menuItems) {
        ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems - 1,
          this.menuItems.length),
          (item: ComposeTitleBarMenuItem, index: number) => {
            ImageMenuItem({
              item: item, index: this.index * 1000 +
              CollapsibleMenuSection.maxCountOfVisibleItems + index, isPopup: true
            })
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
struct ImageMenuItem {
  item: ComposeTitleBarMenuItem = {} as ComposeTitleBarMenuItem;
  index: number = 0;
  itemIndex?: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  isPopup: boolean = false;
  static readonly imageSize = 24;
  static readonly imageHotZoneWidth = 48;
  static readonly buttonBorderRadius = 8;
  static readonly focusBorderWidth = 2;
  static readonly focusablePrefix = "Id-ComposeTitleBar-ImageMenuItem-";
  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;
  @Prop @Watch('onFontSizeUpdated') fontSize: number = 1;
  @Consume('uniqueId') parentParentUniqueId?: number;
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: ComposeTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      itemComposeTitleDialog: this.item,
      composeTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
      fontSize: this.fontSize,
    }),
    maskColor: Color.Transparent,
    isModal: true,
    customStyle: true,
  })

  @State buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier(this.dialogController);

  private textDialog(): ResourceStr {
    if (this.item.value === PUBLIC_MORE) {
      return $r('sys.string.ohos_toolbar_more');
    } else if (this.item.value === PUBLIC_BACK) {
      return $r('sys.string.icon_back');
    } else {
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
      return getContext()?.resourceManager?.getStringByNameSync('icon_back');
    } else if (this.item.value === PUBLIC_MORE) {
      return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
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
      : $r('sys.color.ohos_id_color_titlebar_icon');
  }

  getBgColor() {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(0x3900, 'ComposeTitleBar',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    this.fontSize = this.decideFontScale();
  }

  onFontSizeUpdated(): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale, this.maxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  build() {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
      if (this.item?.symbolStyle) {
        SymbolGlyph()
          .attributeModifier(this.item?.symbolStyle)
          .fontSize(`${ImageMenuItem.imageSize}vp`)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .draggable(false)
          .focusable(this.item?.isEnabled)
          .key(ImageMenuItem.focusablePrefix + this.index)
      } else {
        if (Util.isSymbolResource(this.item.value)) {
          SymbolGlyph(this.item.value as Resource)
            .fontSize(`${ImageMenuItem.imageSize}vp`)
            .fontColor([$r('sys.color.ohos_id_color_text_primary')])
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index)
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
    }
    .id(`ComposeTitleBar_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)
    .accessibilityText(this.getAccessibilityReadText())
    .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
    .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription))
    .enabled(this.item.isEnabled ? this.item.isEnabled : false)
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius(ImageMenuItem.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
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
        return;
      }
      this.isOnFocus = true;
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item?.isEnabled) {
        return;
      }
      this.isOnHover = isOn;
    })
    .onKeyEvent((event) => {
      if (!this.item?.isEnabled) {
        return;
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
        event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return;
      }
      if (event.type === KeyType.Down) {
        this.isOnClick = true;
      }
      if (event.type === KeyType.Up) {
        this.isOnClick = false;
      }
    })
    .onTouch((event) => {
      if (!this.item?.isEnabled) {
        return;
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.isOnClick = false;
        if (this.fontSize >= this.minFontSize && this.isPopup === false) {
          this.dialogController?.close();
        }
      }
    })
    .onClick(() => {
      if (this.item) {
        return this.item.isEnabled && this.item.action?.();
      }
    })
    .gestureModifier(this.buttonGestureModifier)
  }
}

/**
 *  ComposeTitleBarDialog
 */
@CustomDialog
struct ComposeTitleBarDialog {
  itemComposeTitleDialog: ComposeTitleBarMenuItem = {} as ComposeTitleBarMenuItem;
  callbackId: number | undefined = undefined;
  composeTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController;
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
    if (this.composeTitleBarDialog) {
      Column() {
        if (this.itemComposeTitleDialog.symbolStyle) {
          SymbolGlyph()
            .attributeModifier(this.itemComposeTitleDialog.symbolStyle)
            .fontSize(`${IMAGE_SIZE}vp`)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
        } else {
          if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
            SymbolGlyph(this.itemComposeTitleDialog.value as Resource)
              .fontSize(`${IMAGE_SIZE}vp`)
              .fontColor([$r('sys.color.icon_primary')])
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
          } else {
            Image(this.itemComposeTitleDialog.value)
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
          Text(this.composeTitleBarDialog)
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
        if (this.itemComposeTitleDialog.symbolStyle) {
          SymbolGlyph()
            .attributeModifier(this.itemComposeTitleDialog.symbolStyle)
            .fontSize(`${IMAGE_SIZE}vp`)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
            SymbolGlyph(this.itemComposeTitleDialog.value as Resource)
              .fontSize(`${IMAGE_SIZE}vp`)
              .fontColor([$r('sys.color.icon_primary')])
          } else {
            Image(this.itemComposeTitleDialog.value)
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

export { ComposeTitleBar }
