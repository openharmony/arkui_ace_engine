/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
  ResourceStr, Resource, GestureModifier, UIGestureEvent, LongPressGestureHandler, LongPressGestureHandlerOptions, $r,
  SelectOption, Flex, FlexAlign, ItemAlign, Row, Column, Badge, BadgePosition, Select, Position, Margin,
  Color, Text, TextOverflow, HorizontalAlign, Area, ForEach, Button, ButtonType, SymbolGlyph, BorderStyle,
  KeyType, TouchType, Placement, GeometryInfo, Layoutable, ConstraintSizeOptions, Builder, focusControl, SymbolEffect,
  Image, TextAlign, BlurStyle, ShadowStyle, ButtonOptions, BorderOptions, HoverEvent, Padding, KeyEvent,
  TouchEvent, ClickEvent, CustomPopupOptions, BadgeParamWithNumber, CommonMethod,
  PopupStateChangeParam, ComponentV2
} from '@ohos.arkui.component';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import hilog from '@ohos.hilog';
import { UIContext } from '@ohos.arkui.UIContext';
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import { Param, Local, Monitor, IMonitor, ObservedV2, Trace } from '@ohos.arkui.stateManagement';
import promptAction from '@ohos.promptAction';

export interface SelectTitleBarV2MenuItemParams {
  value: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  label?: ResourceStr;
  isEnabled?: boolean;
  action?: () => void;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

@ObservedV2
export class SelectTitleBarV2MenuItem {
  @Trace
  value: ResourceStr = '';
  @Trace
  symbolStyle?: SymbolGlyphModifier;
  @Trace
  label?: ResourceStr;
  @Trace
  isEnabled?: boolean;
  @Trace
  action?: () => void;
  @Trace
  accessibilityText?: ResourceStr;
  @Trace
  accessibilityDescription?: ResourceStr;
  @Trace
  accessibilityLevel?: string;

  constructor(params?: SelectTitleBarV2MenuItemParams) {
    if (params) {
      this.value = params.value;
      if (params.symbolStyle !== undefined) this.symbolStyle = params.symbolStyle;
      if (params.label !== undefined) this.label = params.label;
      if (params.isEnabled !== undefined) this.isEnabled = params.isEnabled;
      if (params.action !== undefined) this.action = params.action;
      if (params.accessibilityText !== undefined) this.accessibilityText = params.accessibilityText;
      if (params.accessibilityDescription !== undefined) this.accessibilityDescription = params.accessibilityDescription;
      if (params.accessibilityLevel !== undefined) this.accessibilityLevel = params.accessibilityLevel;
    }
  }
}

const RESOURCE_TYPE_SYMBOL: number = 40000;

const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG_SIZE = '256vp';
const MIN_DIALOG_SIZE = '216vp';
const ERROR_CODE = 0x3900;
const LONG_PRESS_TIME: number = 500;

export class ButtonGestureModifierV2 implements GestureModifier {
  public static readonly minFontSize: number = 1.75;
  public fontSize: number = 1;
  public openDialog: () => void = () => {};
  public closeDialog: () => void = () => {};

  constructor(openDialog: () => void, closeDialog: () => void) {
    this.openDialog = openDialog;
    this.closeDialog = closeDialog;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifierV2.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler(
          { repeat: false, duration: LONG_PRESS_TIME.toInt() } as LongPressGestureHandlerOptions )
          .onAction(() => {
            if (event) {
              this.openDialog();
            }
          })
          .onActionEnd(() => {
            this.closeDialog();
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

@ComponentV2
export struct SelectTitleBarV2 {
  private static readonly badgeSize: number = 16;
  private static readonly totalHeight: number = 56;
  private static readonly leftPadding: number = 24;
  private static readonly leftPaddingWithBack: number = 12;
  private static readonly rightPadding: number = 24;
  private static readonly badgePadding: number = 16;
  private static readonly subtitleLeftPadding: number = 4;
  private static instanceCount: int = 0;

  @Param selected: int = 0;
  @Param options: Array<SelectOption> = [] as Array<SelectOption>;
  @Param menuItems?: Array<SelectTitleBarV2MenuItem> = [] as Array<SelectTitleBarV2MenuItem>;
  @Param subtitle?: ResourceStr = '';
  @Param badgeValue?: int = 0;
  @Param hidesBackButton?: boolean = false;
  @Param onSelected?: (index: int) => void = undefined;

  @Local fontSize: number = 1;
  @Local messageDesc: string = '';
  @Local selectMaxWidth: number = 0;

  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');

  getStringByNameSync(contextName: string): undefined | string {
    let uiContext: undefined | string = '';
    try {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = context.getHostContext() as common.UIAbilityContext;
        uiContext = hostContext?.resourceManager?.getStringByNameSync(contextName);
      }
    } catch (exception) {
      let code: undefined | number = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to getStringByNameSync,cause, code: ${code}, message: ${message}`);
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
          ImageMenuItemV2({
            item: new SelectTitleBarV2MenuItem({
              value: '',
              symbolStyle: new SymbolGlyphModifier(this.PUBLIC_BACK),
              isEnabled: true,
              label: this.getStringByNameSync('icon_back'),
              action: () => {
                this.getUIContext()?.getRouter()?.back()
              }
            }),
            index: -1
          });
        }

        Column() {
          if (this.badgeValue) {
            Badge({
              count: this.badgeValue!,
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
                    this.options[this.selected].value : '')
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
                  .accessibilityDescription(this.messageDesc.replace('%d', this.badgeValue!.toString()))
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
                  this.options[this.selected].value : '')
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
            .margin({ left: SelectTitleBarV2.subtitleLeftPadding } as Margin);
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

      if (this.menuItems !== undefined && this.menuItems!.length > 0) {
        CollapsibleMenuSectionV2({ menuItems: this.menuItems, index: 1 + SelectTitleBarV2.instanceCount++ });
      }
    }
    .width('100%')
    .height(SelectTitleBarV2.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth: number = newValue.width as number;
      if (!this.hidesBackButton) {
        newWidth -= ImageMenuItemV2.imageHotZoneWidth;
        newWidth += SelectTitleBarV2.leftPadding;
        newWidth -= SelectTitleBarV2.leftPaddingWithBack;
      }
      if (this.menuItems!.length > 0) {
        let menusLength: number = this.menuItems!.length;
        if (menusLength >= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
          newWidth -= ImageMenuItemV2.imageHotZoneWidth * CollapsibleMenuSectionV2.maxCountOfVisibleItems;
        } else if (menusLength > 0) {
          newWidth -= ImageMenuItemV2.imageHotZoneWidth * menusLength;
        }
      }
      if (this.badgeValue) {
        this.selectMaxWidth = newWidth - SelectTitleBarV2.badgeSize - SelectTitleBarV2.leftPadding -
          SelectTitleBarV2.rightPadding - SelectTitleBarV2.badgePadding;
      } else {
        this.selectMaxWidth = newWidth - SelectTitleBarV2.leftPadding - SelectTitleBarV2.rightPadding;
      }
    })
  }

  aboutToAppear(): void {
    try {
      let resourceManager = (this.getUIContext().getHostContext() as common.UIAbilityContext).resourceManager;
      this.messageDesc =
        resourceManager?.getIntPluralStringByNameSync('selecttitlebar_accessibility_message_desc_new',
          (this.badgeValue??0).toInt()) as string;
    } catch (exception) {
      let code: undefined | number = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to getIntPluralStringByNameSync,cause, code: ${code}, message: ${message}`);
    }
  }
}


@ComponentV2
struct CollapsibleMenuSectionV2 {
  static readonly maxCountOfVisibleItems: int = 3;
  private static readonly focusPadding: number = 4;
  private static readonly marginsNum: number = 2;

  @Param menuItems: Array<SelectTitleBarV2MenuItem> = [] as Array<SelectTitleBarV2MenuItem>;
  @Param item: SelectTitleBarV2MenuItem = new SelectTitleBarV2MenuItem({
    value: '',
    symbolStyle: new SymbolGlyphModifier($r('sys.symbol.dot_grid_2x2')),
    label: $r('sys.string.ohos_toolbar_more')
  });
  @Param index: int = 0;

  @Local fontSize: number = 1;
  @Local maxLines: int = 1;
  @Local isPopupShown: boolean = false;
  @Local isMoreIconOnFocus: boolean = false;
  @Local isMoreIconOnHover: boolean = false;
  @Local isMoreIconOnClick: boolean = false;
  @Local dialogId?: int = undefined;
  @Local buttonGestureModifier: ButtonGestureModifierV2 = new ButtonGestureModifierV2(() => {}, () => {});
  @Local localSymbolStyle: SymbolGlyphModifier | undefined = undefined;

  private firstFocusableIndex: number = -1;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: number = 6;
  horizontalsScreenLines: number = 1;
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');

  getMoreIconFgColor(): Resource | Color {
    return this.isMoreIconOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getMoreIconBgColor(): Resource | Color {
    if (this.isMoreIconOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isMoreIconOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  aboutToAppear(): void {
    this.localSymbolStyle = this.item?.symbolStyle;
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: undefined | number = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
    }
    this.menuItems.forEach((item, index) => {
      if (item.isEnabled && this.firstFocusableIndex === -1 &&
        index > CollapsibleMenuSectionV2.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + index + 1;
      }
    })
    this.fontSize = this.decideFontScale();
    this.updateGestureModifier();
  }

  updateGestureModifier(): void {
    this.buttonGestureModifier = new ButtonGestureModifierV2(
      () => {
        this.openDialog();
      },
      () => {
        this.closeDialog();
      }
    );
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  openDialog(): void {
    this.getUIContext().getPromptAction().openCustomDialog({
      builder: this.dialogBuilder,
      maskColor: Color.Transparent,
      isModal: true,
    } as promptAction.CustomDialogOptions).then((dialogId: int) => {
      this.dialogId = dialogId;
    }).catch((error) => {
      hilog.error(ERROR_CODE, 'Ace', `Failed to openCustomDialog: ${error.message}`);
    });
  }

  closeDialog(): void {
    if (this.dialogId !== undefined) {
      this.getUIContext().getPromptAction().closeCustomDialog(this.dialogId as int);
      this.dialogId = undefined;
    }
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

  @Monitor(['fontSize'])
  onFontSizeUpdated(monitor: IMonitor): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems.length <= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
          ForEach(this.menuItems, (item: SelectTitleBarV2MenuItem, index: int) => {
            ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1 })
          })
        } else {
          ForEach(this.menuItems.slice(0, CollapsibleMenuSectionV2.maxCountOfVisibleItems.toInt() - 1),
            (item: SelectTitleBarV2MenuItem, index: int) => {
              ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1 })
            })

          Button({ type: ButtonType.Normal, stateEffect: true } as ButtonOptions) {
            SymbolGlyph(this.PUBLIC_MORE)
              .fontSize(ImageMenuItemV2.imageSize)
              .draggable(false)
              .fontColor([$r('sys.color.icon_primary')])
              .focusable(true)
          }
          .accessibilityText($r('sys.string.ohos_toolbar_more'))
          .width(ImageMenuItemV2.imageHotZoneWidth)
          .height(ImageMenuItemV2.imageHotZoneWidth)
          .borderRadius(ImageMenuItemV2.buttonBorderRadius)
          .foregroundColor(this.getMoreIconFgColor())
          .backgroundColor(this.getMoreIconBgColor())
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: this.isMoreIconOnFocus ? ImageMenuItemV2.focusBorderWidth : 0,
            color: $r('sys.color.ohos_id_color_focused_outline'),
            style: BorderStyle.Solid
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
            return true;
          })
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down) {
              this.isMoreIconOnClick = true;
            }
            if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
              this.isMoreIconOnClick = false
              if (this.fontSize >= this.minFontSize) {
                this.closeDialog();
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
      ForEach(this.menuItems.slice(CollapsibleMenuSectionV2.maxCountOfVisibleItems.toInt() - 1, this.menuItems.length),
        (item: SelectTitleBarV2MenuItem, index: int) => {
          ImageMenuItemV2({
            item: item, index: this.index * 1000 +
              CollapsibleMenuSectionV2.maxCountOfVisibleItems + index, isPopup: false
          })
        })
    }
    .width(ImageMenuItemV2.imageHotZoneWidth + CollapsibleMenuSectionV2.focusPadding * CollapsibleMenuSectionV2.marginsNum)
    .margin({ top: CollapsibleMenuSectionV2.focusPadding, bottom: CollapsibleMenuSectionV2.focusPadding } as Margin)
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItemV2.focusablePrefix + this.firstFocusableIndex)
    })
  }

  @Builder
  dialogBuilder() {
    if (this.item.label) {
      Column() {
        if (this.localSymbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.localSymbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.item.isEnabled)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.item.value) {
          if (UtilV2.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.item.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.item.value)
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
          Text(this.item.label)
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
        if (this.localSymbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.localSymbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.item.isEnabled)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.item.value) {
          if (UtilV2.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.item.isEnabled)
          } else {
            Image(this.item.value)
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

  aboutToDisappear(): void {
    this.closeDialog();
  }
}

@ComponentV2
struct ImageMenuItemV2 {
  static readonly imageSize: string = '24vp';
  static readonly imageHotZoneWidth: number = 48;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly focusablePrefix: string = 'Id-SelectTitleBar-ImageMenuItem-';

  @Param item: SelectTitleBarV2MenuItem = new SelectTitleBarV2MenuItem();
  @Param index: int = 0;
  @Param isPopup: boolean = true;

  @Local isOnFocus: boolean = false;
  @Local isOnHover: boolean = false;
  @Local isOnClick: boolean = false;
  @Local dialogId?: int = undefined;
  @Local buttonGestureModifier: ButtonGestureModifierV2 = new ButtonGestureModifierV2(() => {}, () => {});
  @Local localSymbolStyle: SymbolGlyphModifier | undefined = undefined;
  @Local fontSize: number = 1;

  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  maxLines: int = 1;
  maxFontSize: number = 3.2;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;

  private textDialog(): ResourceStr {
    if (this.item.value === this.PUBLIC_MORE) {
      return $r('sys.string.ohos_toolbar_more');
    } else if (this.item.value === this.PUBLIC_BACK) {
      return $r('sys.string.icon_back');
    } else {
      return this.item.label ? this.item.label as ResourceStr : '' as ResourceStr;
    }
  }

  getFgColor(): Resource | Color {
    return this.isOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon')
  }

  getBgColor(): Resource | Color {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect')
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover')
    } else {
      return Color.Transparent
    }
  }

  aboutToAppear(): void {
    this.localSymbolStyle = this.item?.symbolStyle;
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (exception) {
      let code: undefined | number = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'Ace', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
    }
    this.fontSize = this.decideFontScale();
    this.updateGestureModifier();
  }

  updateGestureModifier(): void {
    this.buttonGestureModifier = new ButtonGestureModifierV2(
      () => {
        this.openDialog();
      },
      () => {
        this.closeDialog();
      }
    );
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  openDialog(): void {
    this.getUIContext().getPromptAction().openCustomDialog({
      builder: this.dialogBuilder,
      maskColor: Color.Transparent,
      isModal: true,
    } as promptAction.CustomDialogOptions).then((dialogId: int) => {
      this.dialogId = dialogId;
    }).catch((error) => {
      hilog.error(ERROR_CODE, 'Ace', `Failed to openCustomDialog: ${error.message}`);
    });
  }

  closeDialog(): void {
    if (this.dialogId !== undefined) {
      this.getUIContext().getPromptAction().closeCustomDialog(this.dialogId as int);
      this.dialogId = undefined;
    }
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
        let code: undefined | number = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'Ace', `Failed to SelectTitleBarV2 toStringFormat,code: ${code},message:${message}`);
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
        let code: undefined | number = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'Ace', `Failed to SelectTitleBarV2 toStringFormat,code: ${code},message:${message}`);
      }
    } else if (this.item.value === this.PUBLIC_MORE) {
      try {
        return context?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
      } catch (err) {
        let code: undefined | number = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(0x3900, 'Ace', `Failed to SelectTitleBarV2 toStringFormat,code: ${code},message:${message}`);
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

  @Monitor(['fontSize'])
  onFontSizeUpdated(monitor: IMonitor): void {
    this.buttonGestureModifier.fontSize = this.fontSize;
  }

  build() {
    if (this.isPopup) {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.localSymbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.localSymbolStyle)
            .fontSize(ImageMenuItemV2.imageSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItemV2.focusablePrefix + this.index)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (UtilV2.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(ImageMenuItemV2.imageSize)
              .draggable(false)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
          } else {
            Image(this.item.value)
              .draggable(false)
              .width(ImageMenuItemV2.imageSize)
              .height(ImageMenuItemV2.imageSize)
              .focusable(this.item.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .width(ImageMenuItemV2.imageHotZoneWidth)
      .height(ImageMenuItemV2.imageHotZoneWidth)
      .borderRadius(ImageMenuItemV2.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .border({
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: this.isOnFocus ? ImageMenuItemV2.focusBorderWidth : 0,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
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
        return true;
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
            this.closeDialog();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      } as () => void)
      .gestureModifier(this.buttonGestureModifier)
    } else {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.localSymbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.localSymbolStyle)
            .fontSize(ImageMenuItemV2.imageSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItemV2.focusablePrefix + this.index)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (UtilV2.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(ImageMenuItemV2.imageSize)
              .draggable(false)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
          } else {
            Image(this.item.value)
              .draggable(false)
              .width(ImageMenuItemV2.imageSize)
              .height(ImageMenuItemV2.imageSize)
              .focusable(this.item.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .width(ImageMenuItemV2.imageHotZoneWidth)
      .height(ImageMenuItemV2.imageHotZoneWidth)
      .borderRadius(ImageMenuItemV2.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .border({
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: this.isOnFocus ? ImageMenuItemV2.focusBorderWidth : 0,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
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
        return true;
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
            this.closeDialog();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      } as () => void)
    }
  }

  @Builder
  dialogBuilder() {
    if (this.textDialog()) {
      Column() {
        if (this.localSymbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.localSymbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.item.isEnabled)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.item.value) {
          if (UtilV2.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.item.isEnabled)
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              } as Margin)
          } else {
            Image(this.item.value)
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
          Text(this.textDialog())
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
        if (this.localSymbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.font_primary')])
            .attributeModifier(this.localSymbolStyle)
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.item.isEnabled)
            .symbolEffect(new SymbolEffect(), false)
        } else if (this.item.value) {
          if (UtilV2.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontColor([$r('sys.color.font_primary')])
              .fontSize(IMAGE_SIZE)
              .draggable(false)
              .focusable(this.item.isEnabled)
          } else {
            Image(this.item.value)
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

  aboutToDisappear(): void {
    this.closeDialog();
  }
}

class UtilV2 {
  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (!UtilV2.isResourceType(resourceStr)) {
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