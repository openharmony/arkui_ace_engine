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
  Component, SelectOption, Flex, FlexAlign, ItemAlign, Row, Column, Badge, BadgePosition, Select, Position, Margin,
  Color, Text, TextOverflow, HorizontalAlign, Area, ForEach, Button, ButtonType, SymbolGlyph, BadgeStyle, BorderStyle,
  KeyType, TouchType, Placement, GeometryInfo, Layoutable, ConstraintSizeOptions, Builder, focusControl, SymbolEffect,
  Image, TextAlign, BlurStyle, ShadowStyle, ButtonOptions, BorderOptions, HoverEvent, Padding, KeyEvent,
  TouchEvent, ClickEvent, CustomPopupOptions, BadgeParamWithNumber, CommonMethod, CustomDialog,
  CustomDialogControllerOptions, PopupStateChangeParam, ClassCastError
} from '@ohos.arkui.component';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import hilog from '@ohos.hilog';
import { UIContext } from '@ohos.arkui.UIContext';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import { State, Observed, PropRef, StorageProp, Watch, StorageLink } from '@ohos.arkui.stateManagement';
import { BusinessError } from '@ohos.base';

export class SelectTitleBarMenuItem {
  value: ResourceStr = '';
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: () => void;
  label?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityLevel?: string;
  accessibilityDescription?: ResourceStr;
}

const RESOURCE_TYPE_SYMBOL: number = 40000;

const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG_SIZE = '256vp';
const MIN_DIALOG_SIZE = '216vp';
const ERROR_CODE = 0x3900;
const LONG_PRESS_TIME: number = 500;

@Observed
class ButtonGestureModifier implements GestureModifier {
  public static readonly minFontSize: number = 1.75;
  public fontSize: number = 1;
  public controller: CustomDialogController | null = null;

  constructor(controller: CustomDialogController | null) {
    this.controller = controller;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler({ repeat: false, duration: LONG_PRESS_TIME as int })
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
export struct SelectTitleBar {
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  @PropRef selected: int = 0
  options: Array<SelectOption> = [] as Array<SelectOption>;
  menuItems: Array<SelectTitleBarMenuItem> = [] as Array<SelectTitleBarMenuItem>;
  subtitle: ResourceStr = '';
  badgeValue: int = 0;
  hidesBackButton: boolean = false;
  messageDesc: string = '';
  onSelected: ((index: int) => void) = (index: int) => {
  };
  private static readonly badgeSize: number = 16;
  private static readonly totalHeight: number = 56;
  private static readonly leftPadding: number = 24;
  private static readonly leftPaddingWithBack: number = 12;
  private static readonly rightPadding: number = 24;
  private static readonly badgePadding: number = 16;
  private static readonly subtitleLeftPadding: number = 4;
  private static instanceCount: number = 0;
  @State selectMaxWidth: number = 0;
  @State fontSize: number = 1;

  getStringByNameSync(contextName: string): undefined | string {
    let uiContext: undefined | string = '';
    try {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = context.getHostContext() as common.UIAbilityContext;
        uiContext = hostContext?.resourceManager?.getStringByNameSync(contextName);
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Faild to getStringByNameSync,cause, code: ${code}, message: ${message}`);
    }
    return uiContext;
  }

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        if (!this.hidesBackButton) {
          ImageMenuItem({
            item: {
              value: '',
              symbolStyle: new SymbolGlyphModifier(this.PUBLIC_BACK),
              isEnabled: true,
              label: this.getStringByNameSync('icon_back'),
              action: () => {
                this.getUIContext()?.getRouter()?.back()
              }
            } as SelectTitleBarMenuItem,
            index: -1
          });
        }

        Column() {
          if (this.badgeValue) {
            Badge({
              count: this.badgeValue,
              position: BadgePosition.Right,
              style: {
                badgeColor: $r('sys.color.ohos_id_color_emphasize'),
                borderColor: $r('sys.color.ohos_id_color_emphasize'),
                borderWidth: 0
              }
            } as BadgeParamWithNumber) {
              Row() {
                Select(this.options)
                  .selected(this.selected)
                  .value(this.selected >= 0 && this.selected < this.options.length ?
                    this.options[this.selected.toInt()].value : '')
                  .font({
                    size: this.hidesBackButton && !this.subtitle
                      ? $r('sys.float.ohos_id_text_size_headline7')
                      : $r('sys.float.ohos_id_text_size_headline8')
                  })
                  .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
                  .backgroundColor(Color.Transparent)
                  .onSelect(this.onSelected)
                  .constraintSize({ maxWidth: this.selectMaxWidth })
                  .offset({ x: -4 } as Position)
                  .accessibilityLevel('yes')
                  .accessibilityDescription(this.messageDesc.replace('%d', this.badgeValue.toString()))
              }
              .justifyContent(FlexAlign.Start)
              .margin({ right: $r('sys.float.ohos_id_elements_margin_horizontal_l') } as Margin);
            }
            .accessibilityGroup(true)
            .accessibilityLevel('no')
          } else {
            Row() {
              Select(this.options)
                .selected(this.selected)
                .value(this.selected >= 0 && this.selected < this.options.length ?
                  this.options[this.selected.toInt()].value : '')
                .font({
                  size: this.hidesBackButton && !this.subtitle
                    ? $r('sys.float.ohos_id_text_size_headline7')
                    : $r('sys.float.ohos_id_text_size_headline8')
                })
                .fontColor($r('sys.color.ohos_id_color_titlebar_text'))
                .backgroundColor(Color.Transparent)
                .onSelect(this.onSelected)
                .constraintSize({ maxWidth: this.selectMaxWidth })
                .offset({ x: -4 } as Position);
            }
            .justifyContent(FlexAlign.Start);
          }
          if (this.subtitle !== undefined) {
            Row() {
              Text(this.subtitle)
                .fontSize($r('sys.float.ohos_id_text_size_over_line'))
                .fontColor($r('sys.color.ohos_id_color_titlebar_subtitle_text'))
                .maxLines(1)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .constraintSize({ maxWidth: this.selectMaxWidth })
                .offset({ y: -4 } as Position);
            }
            .justifyContent(FlexAlign.Start)
            .margin({ left: SelectTitleBar.subtitleLeftPadding } as Margin);
          }
        }
        .justifyContent(FlexAlign.Start)
        .alignItems(HorizontalAlign.Start)
        .constraintSize({ maxWidth: this.selectMaxWidth });
      }
      .margin({
        left: this.hidesBackButton ? $r('sys.float.ohos_id_max_padding_start') :
          $r('sys.float.ohos_id_default_padding_start')
      } as Margin);

      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        CollapsibleMenuSection({ menuItems: this.menuItems, index: 1 + SelectTitleBar.instanceCount++ });
      }
    }
    .width('100%')
    .height(SelectTitleBar.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth: number = Number(newValue.width as number);
      if (!this.hidesBackButton) {
        newWidth -= ImageMenuItem.imageHotZoneWidth;
        newWidth += SelectTitleBar.leftPadding;
        newWidth -= SelectTitleBar.leftPaddingWithBack;
      }
      if (this.menuItems !== undefined) {
        let menusLength: number = this.menuItems.length;
        if (menusLength >= CollapsibleMenuSection.maxCountOfVisibleItems) {
          newWidth -= ImageMenuItem.imageHotZoneWidth * CollapsibleMenuSection.maxCountOfVisibleItems;
        } else if (menusLength > 0) {
          newWidth -= ImageMenuItem.imageHotZoneWidth * menusLength;
        }
      }
      if (this.badgeValue) {
        this.selectMaxWidth = newWidth - SelectTitleBar.badgeSize - SelectTitleBar.leftPadding -
        SelectTitleBar.rightPadding - SelectTitleBar.badgePadding;
      } else {
        this.selectMaxWidth = newWidth - SelectTitleBar.leftPadding - SelectTitleBar.rightPadding;
      }
    })
  }

  aboutToAppear(): void {
    try {
      let resourceManager = (this.getUIContext().getHostContext() as common.UIAbilityContext).resourceManager;
      this.messageDesc =
        resourceManager?.getIntPluralStringByNameSync('selecttitlebar_accessibility_message_desc_new',
          this.badgeValue as Int) as string;
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Faild to getIntPluralStringByNameSync,cause, code: ${code}, message: ${message}`);
    }
  }
}


@Component
struct CollapsibleMenuSection {
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  menuItems: Array<SelectTitleBarMenuItem> = [] as Array<SelectTitleBarMenuItem>;
  item: SelectTitleBarMenuItem = {
    symbolStyle: new SymbolGlyphModifier(this.PUBLIC_MORE),
    label: $r('sys.string.ohos_toolbar_more'),
  } as SelectTitleBarMenuItem;
  index: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  static readonly maxCountOfVisibleItems: number = 3;
  private static readonly focusPadding: number = 4;
  private static readonly marginsNum: number = 2;
  private firstFocusableIndex: number = -1;
  @State isPopupShown: boolean = false;
  @State isMoreIconOnFocus: boolean = false;
  @State isMoreIconOnHover: boolean = false;
  @State isMoreIconOnClick: boolean = false;
  @PropRef @Watch('onFontSizeUpdated') fontSize: number = 1;
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: SelectTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      selectTitleDialog: this.item,
      selectTitleBarDialog: this.item.label ? this.item.label : '',
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
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
    }
    this.menuItems.forEach((item, index) => {
      if (item.isEnabled && this.firstFocusableIndex === -1 &&
        index > CollapsibleMenuSection.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + index + 1;
      }
    })
    this.fontSize = this.decideFontScale();
  }

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    if (uiContent.getHostContext() != null) {
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale as number, this.maxFontScale as number);
  }

  onFontSizeUpdated(flag: String): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems.length <= CollapsibleMenuSection.maxCountOfVisibleItems) {
          ForEach(this.menuItems, (item: SelectTitleBarMenuItem, index: int) => {
            ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 })
          })
        } else {
          ForEach(this.menuItems.slice(0, CollapsibleMenuSection.maxCountOfVisibleItems.toInt() - 1),
            (item: SelectTitleBarMenuItem, index: int) => {
              ImageMenuItem({ item: item, index: this.index * 1000 + index + 1 })
            })

          Button({ type: ButtonType.Normal, stateEffect: true } as ButtonOptions) {
            SymbolGlyph(this.PUBLIC_MORE)
              .fontSize(ImageMenuItem.imageSize)
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
            focused: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: ImageMenuItem.focusBorderWidth,
                color: $r('sys.color.ohos_id_color_focused_outline'),
                style: BorderStyle.Solid
              })
            },
            normal: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0
              })
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
            if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
              return false
            }
            if (event.type === KeyType.Down) {
              this.isMoreIconOnClick = true;
            }
            if (event.type === KeyType.Up) {
              this.isMoreIconOnClick = false
            }
          })
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down) {
              this.isMoreIconOnClick = true;
            }
            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
              this.isMoreIconOnClick = false
              if (this.fontSize >= this.minFontSize) {
                this.dialogController?.close();
              }
            }
          })
          .onClick((event?: ClickEvent) => {
            this.isPopupShown = true
          })
          .gestureModifier(this.buttonGestureModifier)
          .bindPopup(this.isPopupShown, {
            builder: this.popupBuilder,
            placement: Placement.Bottom,
            popupColor: Color.White,
            enableArrow: false,
            mask: false,
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
      ForEach(this.menuItems.slice(CollapsibleMenuSection.maxCountOfVisibleItems.toInt() - 1, this.menuItems.length),
        (item: SelectTitleBarMenuItem, index: int) => {
          ImageMenuItem({
            item: item, index: this.index * 1000 +
            CollapsibleMenuSection.maxCountOfVisibleItems + index, isPopup: false
          })
        })
    }
    .width(ImageMenuItem.imageHotZoneWidth + CollapsibleMenuSection.focusPadding * CollapsibleMenuSection.marginsNum)
    .margin({ top: CollapsibleMenuSection.focusPadding, bottom: CollapsibleMenuSection.focusPadding } as Margin)
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItem.focusablePrefix + this.firstFocusableIndex)
    })
  }
}

@Component
struct ImageMenuItem {
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  item: SelectTitleBarMenuItem = {} as SelectTitleBarMenuItem;
  index: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  isPopup: boolean = true;
  static readonly imageSize: string = '24vp';
  static readonly imageHotZoneWidth: number = 48;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly focusablePrefix: string = 'Id-SelectTitleBar-ImageMenuItem-';
  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;
  @PropRef @Watch('onFontSizeUpdated') fontSize: number = 1;
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: SelectTitleBarDialog({
      cancel: () => {
      },
      confirm: () => {
      },
      selectTitleDialog: this.item,
      selectTitleBarDialog: this.item.label ? this.item.label : this.textDialog(),
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
      return this.item.label ? this.item.label as ResourceStr : '' as ResourceStr;
    }
  }

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

  aboutToAppear(): void {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
    }
    this.fontSize = this.decideFontScale();
  }

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale as number, this.maxFontScale as number);
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return '';
    } else {
      let resourceString: string = '';
      try {
        resourceString = (this.getUIContext().getHostContext() as common.UIAbilityContext)?.resourceManager?.
        getStringSync((resource as Resource).id) as string;
      } catch (err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    let context = this.getUIContext().getHostContext() as common.UIAbilityContext
    if (this.item.value === this.PUBLIC_BACK) {
      try {
        return context?.resourceManager?.getStringByNameSync('icon_back');
      } catch (err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${code},message:${message}`);
      }
    } else if (this.item.value === this.PUBLIC_MORE) {
      try {
        return context?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
      } catch (err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to SelectTitleBar toStringFormat,code: ${code},message:${message}`);
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

  onFontSizeUpdated(flag: String): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    if (this.isPopup) {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.item.symbolStyle)
            .fontSize(ImageMenuItem.imageSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(ImageMenuItem.imageSize)
              .draggable(false)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItem.focusablePrefix + this.index)
          } else {
            Image(this.item.value)
              .draggable(false)
              .width(ImageMenuItem.imageSize)
              .height(ImageMenuItem.imageSize)
              .focusable(this.item.isEnabled)
              .key(ImageMenuItem.focusablePrefix + this.index)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .width(ImageMenuItem.imageHotZoneWidth)
      .height(ImageMenuItem.imageHotZoneWidth)
      .borderRadius(ImageMenuItem.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .stateStyles({
        focused: (instance: CommonMethod) => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: ImageMenuItem.focusBorderWidth,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          })
        },
        normal: (instance: CommonMethod) => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0
          })
        }
      })
      .onFocus(() => {
        if (!this.item.isEnabled) {
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
          this.isOnClick = false
          if (this.fontSize >= this.minFontSize) {
            this.dialogController?.close();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      } as () => void)
      .gestureModifier(this.buttonGestureModifier)
    } else {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.item.symbolStyle)
            .fontSize(ImageMenuItem.imageSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItem.focusablePrefix + this.index)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(ImageMenuItem.imageSize)
              .draggable(false)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItem.focusablePrefix + this.index)
          } else {
            Image(this.item.value)
              .draggable(false)
              .width(ImageMenuItem.imageSize)
              .height(ImageMenuItem.imageSize)
              .focusable(this.item.isEnabled)
              .key(ImageMenuItem.focusablePrefix + this.index)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .width(ImageMenuItem.imageHotZoneWidth)
      .height(ImageMenuItem.imageHotZoneWidth)
      .borderRadius(ImageMenuItem.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .stateStyles({
        focused: (instance: CommonMethod) => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: ImageMenuItem.focusBorderWidth,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
          })
        },
        normal: (instance: CommonMethod) => {
          instance.border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: 0
          })
        }
      })
      .onFocus(() => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnFocus = true
      })
      .onBlur(() => {
        this.isOnFocus = false
      })
      .onHover((isOn: boolean, event?: HoverEvent) => {
        if (!this.item.isEnabled) {
          return;
        }
        this.isOnHover = isOn
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
      } as () => void)
    }
  }
}

@CustomDialog
export struct SelectTitleBarDialog {
  selectTitleDialog: SelectTitleBarMenuItem = {} as SelectTitleBarMenuItem;
  callbackId: number | undefined = undefined;
  selectTitleBarDialog?: ResourceStr = '';
  mainWindowStage: window.Window | undefined = undefined;
  controller?: CustomDialogController
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
    if (this.selectTitleBarDialog) {
      Column() {
        if (this.selectTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.selectTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.selectTitleDialog.isEnabled)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.selectTitleDialog.value) {
          if (Util.isSymbolResource(this.selectTitleDialog.value)) {
            SymbolGlyph(this.selectTitleDialog.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.selectTitleDialog.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.selectTitleDialog.value)
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
          Text(this.selectTitleBarDialog)
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
        if (this.selectTitleDialog.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.selectTitleDialog.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.selectTitleDialog.isEnabled)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.selectTitleDialog.value) {
          if (Util.isSymbolResource(this.selectTitleDialog.value)) {
            SymbolGlyph(this.selectTitleDialog.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.selectTitleDialog.isEnabled)
          } else {
            Image(this.selectTitleDialog.value)
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
      let properties: window.WindowProperties = this.mainWindowStage?.getWindowProperties() as window.WindowProperties;
      let rect = properties.windowRect;
      if (this.getUIContext().px2vp(rect.height) > this.screenWidth) {
        this.maxLines = this.verticalScreenLines;
      } else {
        this.maxLines = this.horizontalsScreenLines;
      }
    } catch (err) {
      let code: undefined | int = (err as ClassCastError)?.code;
      let message: undefined | string = (err as ClassCastError)?.message;
      hilog.error(0x3900, 'Ace', `Faild to SelectTitleBar getMainWindowSync,code: ${code},message:${message}`);
    }
  }
}

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type == RESOURCE_TYPE_SYMBOL;
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