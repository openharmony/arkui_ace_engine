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
  ComponentV2, Flex, FlexAlign, ItemAlign, Row, Image, Column, Text, FontWeight,
  TextOverflow, HorizontalAlign, Area, Color, ForEach, Button, ButtonType, SymbolGlyph,
  BorderStyle, KeyType, TouchType, Placement, CustomPopupOptions,
  GeometryInfo, Layoutable, ConstraintSizeOptions, focusControl, PopupStateChangeParam,
  SymbolEffectStrategy, SymbolEffect, TextAlign, BlurStyle, ButtonOptions, HoverEvent,
  KeyEvent, TouchEvent, ClickEvent, ShadowStyle, Margin, $r,
  ResourceStr, Resource, GestureModifier, UIGestureEvent, LongPressGestureHandler, Padding
} from '@ohos.arkui.component';
import { Param, Local, Monitor, IMonitor } from '@ohos.arkui.stateManagement';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { UIContext } from '@ohos.arkui.UIContext';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import promptAction from '@ohos.promptAction';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import hilog from '@ohos.hilog';


export class ComposeTitleBarV2MenuItem {
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
const DIALOG_MAX_FONT_SIZE: number = 3.2;
const DIALOG_SCREEN_WIDTH: number = 640;
const DIALOG_VERTICAL_SCREEN_LINES: int = 6;
const DIALOG_HORIZONTAL_SCREEN_LINES: int = 1;

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
  private onDialogOpen: () => void;
  private onDialogClose: () => void;

  constructor(onDialogOpen: () => void, onDialogClose: () => void) {
    this.onDialogOpen = onDialogOpen;
    this.onDialogClose = onDialogClose;
  }

  applyGesture(event: UIGestureEvent): void {
    if (this.fontSize >= ButtonGestureModifier.minFontSize) {
      event.addGesture(
        new LongPressGestureHandler({ repeat: false, duration: Double.toInt(ButtonGestureModifier.longPressTime) })
          .onAction(() => {
            if (event) {
              this.onDialogOpen();
            }
          })
          .onActionEnd(() => {
            this.onDialogClose();
          })
      )
    } else {
      event.clearGestures();
    }
  }
}

@ComponentV2
export struct ComposeTitleBarV2 {
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  private static readonly totalHeight: number = 56;
  private static readonly leftPadding: number = 12;
  private static readonly rightPadding: number = 12;
  private static readonly portraitImageSize: number = 40;
  private static readonly portraitImageLeftPadding: number = 4;
  private static readonly portraitImageRightPadding: number = 16;
  private static instanceCount: number = 0;
  @Param item: ComposeTitleBarV2MenuItem | undefined = undefined;
  @Param title: ResourceStr = '';
  @Param subtitle: ResourceStr = '';
  @Param menuItems?: Array<ComposeTitleBarV2MenuItem> = [] as Array<ComposeTitleBarV2MenuItem>;
  @Local titleMaxWidth: number = 0;
  @Local uniqueIdValue?: int = undefined;
  @Local onUniqueIdUpdate?: (id: int) => void = undefined;

  build(): void {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        ImageMenuItemV2({
          item: {
            value: this.PUBLIC_BACK,
            isEnabled: true,
            action: () => {
              this.getUIContext()?.getRouter()?.back()
            }
          } as ComposeTitleBarV2MenuItem,
          index: -1,
          itemIndex: -1
        })

        Row() {
          if (this.item?.value) {
            Image(this.item?.value as Resource)
              .width(ComposeTitleBarV2.portraitImageSize)
              .height(ComposeTitleBarV2.portraitImageSize)
              .margin({
                left: $r('sys.float.ohos_id_text_paragraph_margin_xs'),
                right: $r('sys.float.ohos_id_text_paragraph_margin_m')
              } as Margin)
              .focusable(false)
              .borderRadius(ImageMenuItemV2.buttonBorderRadius)
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
        CollapsibleMenuSectionV2({ menuItems: this.menuItems, index: 1 + ComposeTitleBarV2.instanceCount++ })
      }
    }
    .onAppear(() => {
      try {
        this.uniqueIdValue =
          this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId())?.getFirstChild()?.getUniqueId();
      } catch (exception) {
        let code: undefined| int = (exception as ClassCastError)?.code;
        let message: undefined | string = (exception as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'ComposeTitleBarV2',
          `Failed to getFrameNodeByUniqueId,cause, code: ${code}, message: ${message}`);
      }
    })
    .width('100%')
    .height(ComposeTitleBarV2.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth = newValue.width as number;
      if (this.menuItems !== undefined) {
        const menusLength = this.menuItems!.length;
        if (menusLength >= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
          newWidth = newWidth - ImageMenuItemV2.imageHotZoneWidth * CollapsibleMenuSectionV2.maxCountOfVisibleItems;
        } else if (menusLength > 0) {
          newWidth = newWidth - ImageMenuItemV2.imageHotZoneWidth * menusLength;
        }
      }
      this.titleMaxWidth = newWidth;
      this.titleMaxWidth -= ComposeTitleBarV2.leftPadding;
      this.titleMaxWidth -= ImageMenuItemV2.imageHotZoneWidth;
      if (this.item !== undefined) {
        this.titleMaxWidth -= ComposeTitleBarV2.portraitImageLeftPadding +
        ComposeTitleBarV2.portraitImageSize +
        ComposeTitleBarV2.portraitImageRightPadding;
      }
      this.titleMaxWidth -= ComposeTitleBarV2.rightPadding;
    })
  }
}

@ComponentV2
struct CollapsibleMenuSectionV2 {
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  static readonly maxCountOfVisibleItems: number = 3;
  private static readonly focusPadding: number = 4;
  private static readonly marginsNum: number = 2;
  private static readonly focusIndexOffset: number = 2;
  @Param menuItems: Array<ComposeTitleBarV2MenuItem> = [] as Array<ComposeTitleBarV2MenuItem>;
  @Param item: ComposeTitleBarV2MenuItem = {
    value: $r('sys.symbol.dot_grid_2x2'),
    label: $r('sys.string.ohos_toolbar_more'),
  } as ComposeTitleBarV2MenuItem;
  @Param index: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  @Local isPopupShown: boolean = false;
  @Local isMoreIconOnFocus: boolean = false;
  @Local isMoreIconOnHover: boolean = false;
  @Local isMoreIconOnClick: boolean = false;
  @Local fontSize: number = 1;
  @Local dialogId?: int = undefined;
  @Local maxLines: int = 1;
  @Local buttonGestureModifier: ButtonGestureModifier | null = null;
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
    this.buttonGestureModifier = new ButtonGestureModifier(
      () => { this.openDialog(); },
      () => { this.closeDialog(); }
    );
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: undefined | int = (err as ClassCastError)?.code;
      let message: undefined | string = (err as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    if (this.menuItems) {
      this.menuItems!.forEach((item, index) => {
        if (item.isEnabled && this.firstFocusableIndex === -1 &&
          index > CollapsibleMenuSectionV2.maxCountOfVisibleItems - CollapsibleMenuSectionV2.focusIndexOffset) {
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
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  @Monitor(['fontSize'])
  onFontSizeUpdated(monitor: IMonitor): void {
    this.buttonGestureModifier!.fontSize = this.fontSize;
  }

  private openDialog(): void {
    try {
      let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
      let mainWindowStage = context.windowStage.getMainWindowSync();
      let properties: window.WindowProperties = mainWindowStage!.getWindowProperties();
      let rect = properties.windowRect;
      if (this.getUIContext().px2vp(rect.height) > DIALOG_SCREEN_WIDTH) {
        this.maxLines = DIALOG_VERTICAL_SCREEN_LINES;
      } else {
        this.maxLines = DIALOG_HORIZONTAL_SCREEN_LINES;
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to getMainWindowSync,cause, code: ${code}, message: ${message}`);
    }
    this.getUIContext().getPromptAction().openCustomDialog({
      builder: this.composeTitleBarDialogBuilder,
      maskColor: Color.Transparent,
      isModal: true,
    } as promptAction.CustomDialogOptions).then((id: int) => {
      this.dialogId = id;
    }).catch((error: Error) => {
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to openCustomDialog: ${error.message}`);
    });
  }

  private closeDialog(): void {
    if (this.dialogId !== undefined) {
      this.getUIContext().getPromptAction().closeCustomDialog(this.dialogId as int);
      this.dialogId = undefined;
    }
  }

  @Builder
  composeTitleBarDialogBuilder() {
    if (this.item.label) {
      Column() {
        if (this.item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.item.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
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
          Text(this.item.label ? this.item.label : '')
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
      .width(this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE)
      .constraintSize({ minHeight: this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
    } else {
      Column() {
        if (this.item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.item.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
          } else {
            Image(this.item.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .width(this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE)
      .constraintSize({ minHeight: this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
      .justifyContent(FlexAlign.Center)
    }
  }

  build(): void {
    Column() {
      Row() {
        if (this.menuItems) {
          if (this.menuItems.length <= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
            ForEach(this.menuItems, (item: ComposeTitleBarV2MenuItem, index: int) => {
              ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
            }, (item: ComposeTitleBarV2MenuItem) => { return JSON.stringify(item.value) })
          } else {
            ForEach(this.menuItems.slice(0, CollapsibleMenuSectionV2.maxCountOfVisibleItems.toInt() - 1),
              (item: ComposeTitleBarV2MenuItem, index: int) => {
                ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
              }, (item: ComposeTitleBarV2MenuItem) => { return JSON.stringify(item.value) })

            Button({ type: ButtonType.Normal, stateEffect: true } as ButtonOptions) {
              SymbolGlyph(this.PUBLIC_MORE)
                .fontSize(`${ImageMenuItemV2.imageSize}vp`)
                .fontColor([$r('sys.color.icon_primary')])
                .draggable(false)
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
                  this.closeDialog();
                }
              }
            })
            .onClick((event?: ClickEvent) => {
              this.isPopupShown = true;
            })
            .gestureModifier(this.buttonGestureModifier!)
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
        ForEach(this.menuItems!.slice(CollapsibleMenuSectionV2.maxCountOfVisibleItems.toInt() - 1,
          this.menuItems!.length),
          (item: ComposeTitleBarV2MenuItem, index: int) => {
            ImageMenuItemV2({
              item: item, index: this.index * 1000 +
              CollapsibleMenuSectionV2.maxCountOfVisibleItems + index, isPopup: false
            })
          })
      }
    }
    .width(ImageMenuItemV2.imageHotZoneWidth +
      CollapsibleMenuSectionV2.focusPadding * CollapsibleMenuSectionV2.marginsNum)
    .margin({ top: CollapsibleMenuSectionV2.focusPadding, bottom: CollapsibleMenuSectionV2.focusPadding } as Margin)
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItemV2.focusablePrefix as string +
      this!.firstFocusableIndex as string)
    })
  }
}

@ComponentV2
struct ImageMenuItemV2 {
  PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
  PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
  static readonly imageSize: number = 24;
  static readonly imageHotZoneWidth: number = 48;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly focusablePrefix: string = 'Id-ComposeTitleBar-ImageMenuItem-';
  @Param item: ComposeTitleBarV2MenuItem = {value: 'undefined'} as ComposeTitleBarV2MenuItem;
  @Param index: number = 0;
  @Param itemIndex?: number = 0;
  minFontSize: number = 1.75;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  @Param isPopup: boolean = true;
  @Local isOnFocus: boolean = false;
  @Local isOnHover: boolean = false;
  @Local isOnClick: boolean = false;
  @Local fontSize: number = 1;
  @Param uniqueIdValue?: int = undefined;
  @Local dialogId?: int = undefined;
  @Local maxLines: int = 1;
  @Local buttonGestureModifier: ButtonGestureModifier | null = null;

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
        hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to toStringFormat,code: ${code},message:${message}`);
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
        hilog.error(ERROR_CODE, 'ComposeTitleBarV2',
          `Failed to getStringByNameSync icon_back,code: ${code},message:${message}`);
      }
    } else if (this.item.value === this.PUBLIC_MORE) {
      try {
        return (this.getUIContext()
          .getHostContext() as common.UIAbilityContext)?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
      } catch(err) {
        let code: undefined | int = (err as ClassCastError)?.code;
        let message: undefined | string = (err as ClassCastError)?.message;
        hilog.error(ERROR_CODE, 'ComposeTitleBarV2',
          `Failed to getStringByNameSync ohos_toolbar_more,code: ${code},message:${message}`);
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
    this.buttonGestureModifier = new ButtonGestureModifier(
      () => { this.openDialog(); },
      () => { this.closeDialog(); }
    );
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: undefined | int = (err as ClassCastError)?.code;
      let message: undefined | string = (err as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    this.fontSize = this.decideFontScale();
  }

  @Monitor(['fontSize'])
  onFontSizeUpdated(monitor: IMonitor): void {
    this.buttonGestureModifier!.fontSize = this.fontSize;
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
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  private openDialog(): void {
    try {
      let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
      let mainWindowStage = context.windowStage.getMainWindowSync();
      let properties: window.WindowProperties = mainWindowStage!.getWindowProperties();
      let rect = properties.windowRect;
      if (this.getUIContext().px2vp(rect.height) > DIALOG_SCREEN_WIDTH) {
        this.maxLines = DIALOG_VERTICAL_SCREEN_LINES;
      } else {
        this.maxLines = DIALOG_HORIZONTAL_SCREEN_LINES;
      }
    } catch (exception) {
      let code: undefined | int = (exception as ClassCastError)?.code;
      let message: undefined | string = (exception as ClassCastError)?.message;
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to getMainWindowSync,cause, code: ${code}, message: ${message}`);
    }
    this.getUIContext().getPromptAction().openCustomDialog({
      builder: this.composeTitleBarDialogBuilder,
      maskColor: Color.Transparent,
      isModal: true,
    } as promptAction.CustomDialogOptions).then((id: int) => {
      this.dialogId = id;
    }).catch((error: Error) => {
      hilog.error(ERROR_CODE, 'ComposeTitleBarV2', `Failed to openCustomDialog: ${error.message}`);
    });
  }

  private closeDialog(): void {
    if (this.dialogId !== undefined) {
      this.getUIContext().getPromptAction().closeCustomDialog(this.dialogId as int);
      this.dialogId = undefined;
    }
  }

  @Builder
  composeTitleBarDialogBuilder() {
    if (this.item.label ? this.item.label : this.textDialog()) {
      Column() {
        if (this.item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.item.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
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
          Text(this.item.label ? this.item.label : this.textDialog())
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
      .width(this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE)
      .constraintSize({ minHeight: this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
    } else {
      Column() {
        if (this.item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(this.item.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
          } else {
            Image(this.item.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .width(this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE)
      .constraintSize({ minHeight: this.fontSize === DIALOG_MAX_FONT_SIZE ? MAX_DIALOG_SIZE : MIN_DIALOG_SIZE })
      .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
      .shadow(ShadowStyle.OUTER_DEFAULT_LG)
      .borderRadius($r('sys.float.corner_radius_level10'))
      .justifyContent(FlexAlign.Center)
    }
  }

  build(): void {
    if (this.isPopup) {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.item?.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.ohos_id_color_text_primary')])
            .attributeModifier(this.item?.symbolStyle)
            .fontSize(`${ImageMenuItemV2.imageSize}vp`)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItemV2.focusablePrefix + this.index)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(`${ImageMenuItemV2.imageSize}vp`)
              .fontColor([$r('sys.color.ohos_id_color_text_primary')])
              .draggable(false)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
          } else {
            Image(this.item!.value)
              .matchTextDirection(this.item?.value === this.PUBLIC_BACK ? true : false)
              .width(ImageMenuItemV2.imageSize)
              .draggable(false)
              .height(ImageMenuItemV2.imageSize)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
              .fillColor($r('sys.color.ohos_id_color_text_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .width(ImageMenuItemV2.imageHotZoneWidth)
      .height(ImageMenuItemV2.imageHotZoneWidth)
      .borderRadius(ImageMenuItemV2.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .border({
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: this.isOnFocus ? ImageMenuItemV2.focusBorderWidth : 0,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
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
            this.closeDialog();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      })
      .gestureModifier(this.buttonGestureModifier!)
    } else {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
        if (this.item?.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.ohos_id_color_text_primary')])
            .attributeModifier(this.item?.symbolStyle)
            .fontSize(`${ImageMenuItemV2.imageSize}vp`)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItemV2.focusablePrefix + this.index)
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(`${ImageMenuItemV2.imageSize}vp`)
              .fontColor([$r('sys.color.ohos_id_color_text_primary')])
              .draggable(false)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
          } else {
            Image(this.item!.value)
              .matchTextDirection(this.item?.value === this.PUBLIC_BACK ? true : false)
              .width(ImageMenuItemV2.imageSize)
              .draggable(false)
              .height(ImageMenuItemV2.imageSize)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
              .fillColor($r('sys.color.ohos_id_color_text_primary'))
          }
        }
      }
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.toStringFormat(this.item?.accessibilityDescription) as string)
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .width(ImageMenuItemV2.imageHotZoneWidth)
      .height(ImageMenuItemV2.imageHotZoneWidth)
      .borderRadius(ImageMenuItemV2.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .border({
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: this.isOnFocus ? ImageMenuItemV2.focusBorderWidth : 0,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
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
            this.closeDialog();
          }
        }
      })
      .onClick((event?: ClickEvent) => {
        this.item.isEnabled && this.item.action?.();
      })
    }
  }
}
