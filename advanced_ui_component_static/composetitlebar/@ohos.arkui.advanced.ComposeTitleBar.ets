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
  ResourceStr, Resource, GestureModifier, CustomDialogController, UIGestureEvent, LongPressGestureHandler, $r,
  Component, Flex, FlexAlign, ItemAlign, Row, Image, Column, Text, FontWeight, CustomDialogControllerOptions,
  TextOverflow, HorizontalAlign, Area, Color, ForEach, Button, CustomDialog, ButtonType, SymbolGlyph, CommonMethod,
  BorderStyle, KeyType, TouchType, Placement, CustomPopupOptions, GeometryInfo, Layoutable, ConstraintSizeOptions,
  Builder, focusControl, LocalizedPadding, Padding, PopupStateChangeParam, SymbolEffectStrategy, SymbolEffect,
  TextAlign, BlurStyle, ButtonOptions, HoverEvent, KeyEvent, TouchEvent, ClickEvent, ShadowStyle,
  Margin, ClassCastError
} from '@ohos.arkui.component';
import resourceManager from '@ohos.resourceManager';
import { State, Observed, PropRef, StorageProp, Watch, StorageLink, Provide, Consume, Link } from '@ohos.arkui.stateManagement'
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier'
import { UIContext } from '@ohos.arkui.UIContext';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import hilog from '@ohos.hilog';

export class ComposeTitleBarMenuItem {
  public value: ResourceStr = '';
  public symbolStyle?: SymbolGlyphModifier;
  public isEnabled?: boolean;
  public action?: () => void;
  public label?: ResourceStr;
  public accessibilityText?: ResourceStr;
  public accessibilityLevel?: string;
  public accessibilityDescription?: ResourceStr;
}

const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG_SIZE = '256vp';
const MIN_DIALOG_SIZE = '216vp';
const RESOURCE_TYPE_SYMBOL: int = 40000;
const ERROR_CODE: int = 0x3900;

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
        new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime as int})
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
export struct ComposeTitleBar {
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  private static readonly totalHeight: number = 56;
  private static readonly leftPadding: number = 12;
  private static readonly rightPadding: number = 12;
  private static readonly portraitImageSize: number = 40;
  private static readonly portraitImageLeftPadding: number = 4;
  private static readonly portraitImageRightPadding: number = 16;
  private static instanceCount: number = 0;
  item: ComposeTitleBarMenuItem | undefined = undefined;
  title: ResourceStr = '';
  subtitle: ResourceStr = '';
  menuItems?: Array<ComposeTitleBarMenuItem> = [] as Array<ComposeTitleBarMenuItem>;
  @State titleMaxWidth: number = 0;
  @State fontSize: number = 1;
  @Provide uniqueId?: number = -1;

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        ImageMenuItem({
          item: {
            value: this.PUBLIC_BACK,
            isEnabled: true,
            action: () => {
              this.getUIContext()?.getRouter()?.back()
            }
          } as ComposeTitleBarMenuItem,
          index: -1,
          itemIndex: -1
        })

        Row() {
          if (this.item?.value) {
            Image(this.item?.value as Resource)
              .width(ComposeTitleBar.portraitImageSize)
              .height(ComposeTitleBar.portraitImageSize)
              .margin({
                left: $r('sys.float.ohos_id_text_paragraph_margin_xs'),
                right: $r('sys.float.ohos_id_text_paragraph_margin_m')
              } as Margin)
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
        .accessibilityDescription($r('sys.string.subheader_accessibility_title'))
      }
      .margin({ left: $r('sys.float.ohos_id_default_padding_start') } as Margin)
      if ((this.menuItems?.length ?? 0) > 0) {
        CollapsibleMenuSection({ menuItems: this.menuItems, index: 1 + ComposeTitleBar.instanceCount++ })
      }
    }
    .onAppear(() => {
      try {
        this.uniqueId = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId())?.getFirstChild()?.getUniqueId();
      } catch (exception) {
        let code: undefined| int = (exception as ClassCastError)?.code;
        let message: undefined | string = (exception as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'ComposeTitleBar',
          `Faild to getFrameNodeByUniqueId,cause, code: ${code}, message: ${message}`);
      }
    })
    .width('100%')
    .height(ComposeTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth = Number(newValue.width as number);
      if (this.menuItems !== undefined) {
        const menusLength = this.menuItems!.length;
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
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  static readonly maxCountOfVisibleItems: number = 3;
  private static readonly focusPadding: number = 4;
  private static readonly marginsNum: number = 2;
  private static readonly focusIndexOffset: number = 2;
  menuItems: Array<ComposeTitleBarMenuItem> = [] as Array<ComposeTitleBarMenuItem>;
  item: ComposeTitleBarMenuItem = {
    value: this.PUBLIC_MORE,
    label: $r('sys.string.ohos_toolbar_more'),
  } as ComposeTitleBarMenuItem;
  index: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  @State isPopupShown: boolean = false;
  @State isMoreIconOnFocus: boolean = false;
  @State isMoreIconOnHover: boolean = false;
  @State isMoreIconOnClick: boolean = false;
  @PropRef @Watch('onFontSizeUpdated') fontSize: number = 1;
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
  private firstFocusableIndex: number = -1;

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
      let code: undefined | int = (err as ClassCastError)?.code;
      let message: undefined | string = (err as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBar',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    if (this.menuItems) {
      this.menuItems!.forEach((item, index) => {
        if (item.isEnabled && this.firstFocusableIndex === -1 &&
          index > CollapsibleMenuSection.maxCountOfVisibleItems - CollapsibleMenuSection.focusIndexOffset) {
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
      return Math.min(this.systemFontScale as number, this.maxFontScale as number);
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  onFontSizeUpdated(flag: String): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems) {
          if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
            ForEach(this.menuItems, (item: ComposeTitleBarMenuItem, index: int) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
            })
          } else {
            ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems.toInt() - 1),
              (item: ComposeTitleBarMenuItem, index: int) => {
                ImageMenuItem({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
              })

            Button({ type: ButtonType.Normal, stateEffect: true } as ButtonOptions) {
              SymbolGlyph(this.PUBLIC_MORE)
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
              focused: (instance: CommonMethod): void => {
                instance.border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: ImageMenuItem.focusBorderWidth,
                  color: $r('sys.color.ohos_id_color_focused_outline'),
                  style: BorderStyle.Solid
                });
              },
              normal: (instance: CommonMethod): void => {
                instance.border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: 0
                });
              }
            })
            .onFocus(() => {
              this.isMoreIconOnFocus = true;
            })
            .onBlur(() => {
              this.isMoreIconOnFocus = false;
            })
            .onHover((isOn: boolean, event?: HoverEvent) => {
              this.isMoreIconOnHover = isOn;
            })
            .onKeyEvent((event: KeyEvent) => {
              if (event.keyCode !== KeyCode.KEYCODE_ENTER &&
                event.keyCode !== KeyCode.KEYCODE_SPACE) {
                return false;
              }
              if (event.type === KeyType.Down) {
                this.isMoreIconOnClick = true;
              }
              if (event.type === KeyType.Up) {
                this.isMoreIconOnClick = false;
              }
            })
            .onTouch((event: TouchEvent) => {
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
            .onClick((event?: ClickEvent) => {
              this.isPopupShown = true;
            })
            .gestureModifier(this.buttonGestureModifier)
            .bindPopup(this.isPopupShown as boolean, {
              builder: this.popupBuilder,
              placement: Placement.Bottom,
              popupColor: Color.White,
              enableArrow: false,
              onStateChange: (e: PopupStateChangeParam) => {
                this.isPopupShown = e.isVisible
                if (!e.isVisible) {
                  this.isMoreIconOnClick = false;
                }
              }
            } as CustomPopupOptions)
          }
        }
      }
    }
    .height('100%')
    .margin({ right: $r('sys.float.ohos_id_default_padding_end') } as Margin)
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
      if (this.menuItems) {
        ForEach(this.menuItems!.slice(CollapsibleMenuSection.maxCountOfVisibleItems.toInt() - 1,
          this.menuItems!.length),
          (item: ComposeTitleBarMenuItem, index: int) => {
            ImageMenuItem({
              item: item, index: this.index * 1000 +
              CollapsibleMenuSection.maxCountOfVisibleItems + index, isPopup: false
            })
          })
      }
    }
    .width(ImageMenuItem.imageHotZoneWidth +
      CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding } as Margin)
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItem.focusablePrefix as string +
      this!.firstFocusableIndex as string)
    })
  }
}

@Component
struct ImageMenuItem {
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  static readonly imageSize: number = 24;
  static readonly imageHotZoneWidth: number = 48;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly focusablePrefix: string = 'Id-ComposeTitleBar-ImageMenuItem-';
  item: ComposeTitleBarMenuItem = {value: 'undefined'} as ComposeTitleBarMenuItem;
  index: number = 0;
  itemIndex?: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  isPopup: boolean = true;
  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;
  @PropRef @Watch('onFontSizeUpdated') fontSize: number = 1;
  @Consume uniqueId?: number;
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
    if (this.item.value === this.PUBLIC_MORE) {
      return $r('sys.string.ohos_toolbar_more');
    } else if (this.item.value === this.PUBLIC_BACK) {
      return $r('sys.string.icon_back');
    } else {
      return this.item?.label ?? '';
    }
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return '' as string;
    } else {
      let resourceString: undefined | string = '';
      try {
        resourceString = (this.getUIContext()
          .getHostContext() as common.UIAbilityContext)?.resourceManager?.getStringSync((resource as Resource).id);
      } catch (err) {
        let code: int = (err as ClassCastError)?.code ?? 0;
        let message: string = (err as ClassCastError)?.message ?? '';
        hilog.error(ERROR_CODE, 'Ace', `Faild to ComposeTitleBar toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === this.PUBLIC_BACK) {
      try {
        return (this.getUIContext()
          .getHostContext() as common.UIAbilityContext)?.resourceManager!.getStringByNameSync('icon_back');
      } catch (err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'Ace',
          `Faild to ComposeTitleBar getStringByNameSync icon_back,code: ${code},message:${message}`);
      }
    } else if (this.item.value === this.PUBLIC_MORE) {
      try {
        return (this.getUIContext()
          .getHostContext() as common.UIAbilityContext)?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
      } catch(err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'Ace',
          `Faild to ComposeTitleBar getStringByNameSync ohos_toolbar_more,code: ${code},message:${message}`);
      }
    } else if (this.item.accessibilityText) {
      return this.toStringFormat(this.item.accessibilityText) as string;
    } else if (this.item.label) {
      return this.toStringFormat(this.item.label) as string;
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
      let code: undefined | int = (err as ClassCastError)?.code;
      let message: undefined | string = (err as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBar',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    this.fontSize = this.decideFontScale();
  }

  onFontSizeUpdated(flag: string): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  decideFontScale(): number {
    try {
      let uiContent: UIContext = this.getUIContext();
      if (uiContent.getHostContext() != undefined) {
        this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      }
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale as number, this.maxFontScale as number);
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBar', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  build() {
    if (this.isPopup) {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.item?.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.ohos_id_color_text_primary')])
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
            Image(this.item!.value)
              .matchTextDirection(this.item?.value === this.PUBLIC_BACK ? true : false)
              .width(ImageMenuItem.imageSize)
              .draggable(false)
              .height(ImageMenuItem.imageSize)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItem.focusablePrefix + this.index)
              .fillColor($r('sys.color.ohos_id_color_text_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .width(ImageMenuItem.imageHotZoneWidth)
      .height(ImageMenuItem.imageHotZoneWidth)
      .borderRadius(ImageMenuItem.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .stateStyles({
        focused: (instance: CommonMethod): void => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: ImageMenuItem.focusBorderWidth,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          });
        },
        normal: (instance: CommonMethod): void => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0
          });
        }
      })
      .onFocus(() => {
        if (!this.item?.isEnabled) {
          return;
        }
        this.isOnFocus = true;
      })
      .onBlur(() => {
        this.isOnFocus = false;
      })
      .onHover((isOn: boolean, event?: HoverEvent) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = isOn;
      })
      .onKeyEvent((event: KeyEvent) => {
        if (!this.item.isEnabled) {
          return false;
        }
        if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
          return false;
        }
        if (event.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (event.type === KeyType.Up) {
          this.isOnClick = false;
        }
      })
      .onTouch((event: TouchEvent) => {
        if (!this.item.isEnabled) {
          return;
        }
        if (event.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          this.isOnClick = false;
          if (this.fontSize >= this.minFontSize) {
            this.dialogController?.close();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      })
      .gestureModifier(this.buttonGestureModifier)
    } else {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.item?.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.ohos_id_color_text_primary')])
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
            Image(this.item!.value)
              .matchTextDirection(this.item?.value === this.PUBLIC_BACK ? true : false)
              .width(ImageMenuItem.imageSize)
              .draggable(false)
              .height(ImageMenuItem.imageSize)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItem.focusablePrefix + this.index)
              .fillColor($r('sys.color.ohos_id_color_text_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .width(ImageMenuItem.imageHotZoneWidth)
      .height(ImageMenuItem.imageHotZoneWidth)
      .borderRadius(ImageMenuItem.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .stateStyles({
        focused: (instance: CommonMethod): void => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: ImageMenuItem.focusBorderWidth,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          });
        },
        normal: (instance: CommonMethod): void => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0
          });
        }
      })
      .onFocus(() => {
        if (!this.item?.isEnabled) {
          return;
        }
        this.isOnFocus = true;
      })
      .onBlur(() => {
        this.isOnFocus = false;
      })
      .onHover((isOn: boolean, event?: HoverEvent) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = isOn;
      })
      .onKeyEvent((event: KeyEvent) => {
        if (!this.item.isEnabled) {
          return false;
        }
        if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
          return false;
        }
        if (event.type === KeyType.Down) {
          this.isOnClick = true;
        }
        if (event.type === KeyType.Up) {
          this.isOnClick = false;
        }
      })
      .onTouch((event: TouchEvent) => {
        if (!this.item?.isEnabled) {
          return;
        }
        if (event.type === TouchType.Down) {
          this.isOnClick = true;
        }
        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          this.isOnClick = false;
          if (this.fontSize >= this.minFontSize) {
            this.dialogController?.close();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      })
    }
  }
}

/**
 *  ComposeTitleBarDialog
 */
@CustomDialog
struct ComposeTitleBarDialog {
  itemComposeTitleDialog: ComposeTitleBarMenuItem = {value: 'undefined'} as ComposeTitleBarMenuItem;
  callbackId: number | undefined = undefined;
  composeTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: int = 6;
  horizontalsScreenLines: int = 1;
  @StorageLink('mainWindow') mainWindow: Promise<window.Window> | undefined = undefined;
  @State fontSize: number = 1;
  @State maxLines: int = 1;
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
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.itemComposeTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
        } else {
          if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
            SymbolGlyph(this.itemComposeTitleDialog.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.itemComposeTitleDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
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
        } as Padding)
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
    } else {
      Column() {
        if (this.itemComposeTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.itemComposeTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(this.itemComposeTitleDialog.value)) {
            SymbolGlyph(this.itemComposeTitleDialog.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
          } else {
            Image(this.itemComposeTitleDialog.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .width(this.fontSize === this.maxFontSize ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE)
      .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
      .justifyContent(FlexAlign.Center)
    }
  }

  aboutToAppear(): void {
    try {
      let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
      this.mainWindowStage = context.windowStage.getMainWindowSync();
      let properties: window.WindowProperties = this.mainWindowStage!.getWindowProperties();
      let rect = properties.windowRect;
      if (this.getUIContext().px2vp(rect.height) > this.screenWidth) {
        this.maxLines = this.verticalScreenLines;
      } else {
        this.maxLines = this.horizontalsScreenLines;
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBar', `Faild to getMainWindowSync,cause, code: ${code}, message: ${message}`);
    }
  }
}