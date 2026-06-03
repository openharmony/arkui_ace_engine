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

import { KeyCode } from '@ohos.multimodalInput.keyCode';
import window from '@ohos.window';
import common from '@ohos.app.ability.common';
import { BusinessError } from '@kit.BasicServicesKit';
import hilog from '@ohos.hilog';
import promptAction from '@ohos.promptAction';

type OnActionCallback = () => void;

export interface ComposeTitleBarV2MenuItemParams {
  value: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: OnActionCallback;
  label?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityLevel?: string;
  accessibilityDescription?: ResourceStr;
}

@ObservedV2
export class ComposeTitleBarV2MenuItem {
  @Trace
  public value: ResourceStr;
  @Trace
  public symbolStyle?: SymbolGlyphModifier;
  @Trace
  public isEnabled?: boolean = true;
  @Trace
  public action?: OnActionCallback;
  @Trace
  public label?: ResourceStr;
  @Trace
  public accessibilityText?: ResourceStr;
  @Trace
  public accessibilityLevel?: string = 'auto';
  @Trace
  public accessibilityDescription?: ResourceStr;

  constructor(params?: ComposeTitleBarV2MenuItemParams) {
    if (params) {
      this.value = params.value;
      this.symbolStyle = params.symbolStyle;
      this.isEnabled = params.isEnabled ?? true;
      this.action = params.action;
      this.label = params.label;
      this.accessibilityText = params.accessibilityText;
      this.accessibilityLevel = params.accessibilityLevel ?? 'auto';
      this.accessibilityDescription = params.accessibilityDescription;
    } else {
      this.value = '';
      this.isEnabled = true;
      this.accessibilityLevel = 'auto';
    }
  }
}

const PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
const PUBLIC_BACK: Resource = $r('sys.symbol.arrow_left');
const TEXT_EDITABLE_DIALOG: FP = '18.3fp';
const IMAGE_SIZE: VP = '64vp';
const MAX_DIALOG: VP = '256vp';
const MIN_DIALOG: VP = '216vp';
const RESOURCE_TYPE_SYMBOL: number = 40000;
const SCREEN_WIDTH_BREAK_POINT: number = 640;
const VERTICAL_SCREEN_TEXT_MAX_LINES: number = 6;
const HORIZONTAL_SCREEN_TEXT_MAX_LINES: number = 1;

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
  public gestureCallBack?: (event: UIGestureEvent) => void = undefined;

  applyGesture(event: UIGestureEvent): void {
    this.gestureCallBack?.(event);
  }
}

@ComponentV2
export struct ComposeTitleBarV2 {
  @Param
  item?: ComposeTitleBarV2MenuItem = undefined;
  @Param
  title: ResourceStr = '';
  @Param
  subtitle?: ResourceStr = '';
  @Param
  menuItems?: Array<ComposeTitleBarV2MenuItem> = [];
  @Local
  titleMaxWidth: number = 0;
  @Local
  fontSize: number = 1;
  @Provider('uniqueIdV2') uniqueId: number = -1;

  private static readonly totalHeight = 56;
  private static readonly leftPadding = 12;
  private static readonly rightPadding = 12;
  private static readonly portraitImageSize = 40;
  private static readonly portraitImageLeftPadding = 4;
  private static readonly portraitImageRightPadding = 16;
  private static instanceCount = 0;

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch
    }) {
      Row() {
        ImageMenuItemV2({
          item: new ComposeTitleBarV2MenuItem({
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.getUIContext()?.getRouter()?.back()
          }),
          index: -1,
          itemIndex: -1
        })

        Row() {
          if (this.item !== undefined) {
            Image(this.item.value)
              .width(ComposeTitleBarV2.portraitImageSize)
              .height(ComposeTitleBarV2.portraitImageSize)
              .margin({
                left: $r('sys.float.ohos_id_text_paragraph_margin_xs'),
                right: $r('sys.float.ohos_id_text_paragraph_margin_m')
              })
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
      .margin({ left: $r('sys.float.ohos_id_default_padding_start') })

      if (this.menuItems !== undefined && this.menuItems.length > 0) {
        CollapsibleMenuSectionV2({
          menuItems: this.menuItems,
          index: 1 + ComposeTitleBarV2.instanceCount++
        })
      }
    }
    .onAppear(() => {
      try {
        let frameNode = this.getUIContext().getFrameNodeByUniqueId(this.getUniqueId());
        if (frameNode) {
          let firstChild = frameNode.getFirstChild();
          if (firstChild) {
            this.uniqueId = firstChild.getUniqueId() ?? -1;
          }
        }
      } catch (exception) {
        let code: number = (exception as BusinessError)?.code;
        let message: string = (exception as BusinessError)?.message;
        hilog.error(0x3900, 'ComposeTitleBarV2',
          `Faild to getFrameNodeByUniqueId,cause, code: ${code}, message: ${message}`);
      }
    })
    .width('100%')
    .height(ComposeTitleBarV2.totalHeight)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let newWidth = Number(newValue.width);
      if (this.menuItems !== undefined) {
        let menusLength = this.menuItems.length;
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
  @Param
  menuItems?: Array<ComposeTitleBarV2MenuItem> = [];
  @Param
  item: ComposeTitleBarV2MenuItem = new ComposeTitleBarV2MenuItem({
    value: PUBLIC_MORE,
    label: $r('sys.string.ohos_toolbar_more'),
  });
  @Param
  index: number = 0;
  @Local
  isPopupShown: boolean = false;
  @Local
  isMoreIconOnFocus: boolean = false;
  @Local
  isMoreIconOnHover: boolean = false;
  @Local
  isMoreIconOnClick: boolean = false;
  @Local
  fontSize: number = 1;
  @Local
  itemDialogId?: number = undefined;
  @Local
  dialogTextMaxLine: number = 1;

  static readonly maxCountOfVisibleItems = 3;
  private static readonly focusPadding = 4;
  private static readonly marginsNum = 2;
  private minFontSize: number = 1.75;
  private isFollowingSystemFontScale: boolean = false;
  private maxFontScale: number = 1;
  private systemFontScale?: number = 1;
  private firstFocusableIndex = -1;
  private buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier();

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
      let code: number = (err as BusinessError)?.code;
      let message: string = (err as BusinessError)?.message;
      hilog.error(0x3900, 'ComposeTitleBarV2',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    if (this.menuItems) {
      this.menuItems.forEach((item, index) => {
        if (item.isEnabled && this.firstFocusableIndex === -1 &&
          index > CollapsibleMenuSectionV2.maxCountOfVisibleItems - 2) {
          this.firstFocusableIndex = this.index * 1000 + index + 1;
        }
      })
    }
    this.fontSize = this.decideFontScale();
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
      let code: number = (exception as BusinessError)?.code;
      let message: string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'ComposeTitleBarV2', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  @Builder
  itemCardDialogBuilder(item: ComposeTitleBarV2MenuItem): void {
    if (item.label) {
      Column() {
        if (item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(item.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            })
        } else {
          if (Util.isSymbolResource(item.value)) {
            SymbolGlyph(item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
          } else {
            Image(item.value)
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
          Text(item.label)
            .fontSize(TEXT_EDITABLE_DIALOG)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .maxLines(this.dialogTextMaxLine)
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
      .constraintSize({ minHeight: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG })
    } else {
      Column() {
        if (item.symbolStyle) {
          SymbolGlyph()
            .fontColor([$r('sys.color.icon_primary')])
            .attributeModifier(item.symbolStyle)
            .fontSize(IMAGE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
        } else {
          if (Util.isSymbolResource(item.value)) {
            SymbolGlyph(item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
          } else {
            Image(item.value)
              .width(IMAGE_SIZE)
              .height(IMAGE_SIZE)
              .fillColor($r('sys.color.icon_primary'))
          }
        }
      }
      .constraintSize({ minHeight: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG })
      .justifyContent(FlexAlign.Center)
    }
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems) {
          if (this.menuItems.length <= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
            ForEach(this.menuItems, (item: ComposeTitleBarV2MenuItem, index: number) => {
              ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
            })
          } else {
            ForEach(this.menuItems.slice(0, CollapsibleMenuSectionV2.maxCountOfVisibleItems - 1),
              (item: ComposeTitleBarV2MenuItem, index: number) => {
                ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1, itemIndex: index })
              })

            Button({ type: ButtonType.Normal, stateEffect: true }) {
              SymbolGlyph(PUBLIC_MORE)
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
            .stateStyles({
              focused: {
                .border({
                  radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                  width: ImageMenuItemV2.focusBorderWidth,
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
                if (this.fontSize >= this.minFontSize && this.itemDialogId) {
                  promptAction.closeCustomDialog(this.itemDialogId);
                }
              }
            })
            .onClick(() => this.isPopupShown = true)
            .gestureModifier(this.getItemGestureModifier())
          }
        }
      }
    }
    .height('100%')
    .margin({ right: $r('sys.float.ohos_id_default_padding_end') })
    .justifyContent(FlexAlign.Center)
  }

  private getItemGestureModifier(): ButtonGestureModifier {
    this.buttonGestureModifier.gestureCallBack = (event: UIGestureEvent) => {
      if (this.fontSize >= ButtonGestureModifier.minFontSize) {
        event.addGesture(
          new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
            .onAction(() => {
              promptAction.openCustomDialog({
                builder: () => {
                  this.itemCardDialogBuilder(this.item);
                },
                onWillAppear: () => {
                  try {
                    let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
                    let mainWindowStage = context.windowStage.getMainWindowSync();
                    let properties: window.WindowProperties = mainWindowStage.getWindowProperties();
                    if (px2vp(properties.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                      this.dialogTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                    } else {
                      this.dialogTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                    }
                  } catch (err) {
                    let code: number = (err as BusinessError)?.code;
                    let message: string = (err as BusinessError)?.message;
                    hilog.error(0x3900, 'ComposeTitleBarV2',
                      `Faild to get window height, code: ${code}, message: ${message}`);
                  }
                },
                maskColor: Color.Transparent,
                isModal: true,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                backgroundColor: Color.Transparent,
                shadow: ShadowStyle.OUTER_DEFAULT_LG,
                cornerRadius: $r('sys.float.corner_radius_level10'),
                width: this.fontSize === ButtonGestureModifier.minFontSize ? MAX_DIALOG : MIN_DIALOG
              }).then((dialogId: number) => {
                this.itemDialogId = dialogId;
              });
            })
            .onActionEnd(() => {
              if (this.itemDialogId) {
                promptAction.closeCustomDialog(this.itemDialogId);
              }
            })
            .onActionCancel(() => {
              if (this.itemDialogId) {
                promptAction.closeCustomDialog(this.itemDialogId);
              }
            })
        )
        return;
      }
      event.clearGestures();
    }
    return this.buttonGestureModifier;
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
        ForEach(this.menuItems.slice(CollapsibleMenuSectionV2.maxCountOfVisibleItems - 1,
          this.menuItems.length),
          (item: ComposeTitleBarV2MenuItem, index: number) => {
            ImageMenuItemV2({
              item: item, index: this.index * 1000 +
                CollapsibleMenuSectionV2.maxCountOfVisibleItems + index, isPopup: false
            })
          })
      }
    }
    .width(ImageMenuItemV2.imageHotZoneWidth +
      CollapsibleMenuSectionV2.focusPadding * CollapsibleMenuSectionV2.marginsNum)
    .margin({ top: CollapsibleMenuSectionV2.focusPadding, bottom: CollapsibleMenuSectionV2.focusPadding })
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItemV2.focusablePrefix +
        this.firstFocusableIndex)
    })
  }
}

@ComponentV2
struct ImageMenuItemV2 {
  @Param
  item: ComposeTitleBarV2MenuItem = new ComposeTitleBarV2MenuItem();
  @Param
  index: number = 0;
  @Param
  itemIndex?: number = 0;
  @Param
  isPopup: boolean = true;
  @Local
  isOnFocus: boolean = false;
  @Local
  isOnHover: boolean = false;
  @Local
  isOnClick: boolean = false;
  @Local
  fontSize: number = 1;
  @Local
  itemDialogId?: number = undefined;
  @Local
  dialogTextMaxLine: number = 1;
  @Consumer('uniqueIdV2') parentParentUniqueId: number = -1;

  static readonly imageSize = 24;
  static readonly imageHotZoneWidth = 48;
  static readonly buttonBorderRadius = 8;
  static readonly focusBorderWidth = 2;
  static readonly focusablePrefix = 'Id-ComposeTitleBarV2-ImageMenuItem-';

  private minFontSize: number = 1.75;
  private isFollowingSystemFontScale: boolean = false;
  private maxFontScale: number = 1;
  private systemFontScale?: number = 1;
  private buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier();

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
        if (resource.id === -1 ) {
          resourceString = getContext()?.resourceManager?.getStringByNameSync(resource.params?.[0].split('.').pop());
        } else {
          resourceString = getContext()?.resourceManager?.getStringSync(resource);
        }
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace', `Faild to ComposeTitleBarV2 toStringFormat,code: ${code},message:${message}`);
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_BACK) {
      try {
        return getContext()?.resourceManager?.getStringByNameSync('icon_back');
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace',
          `Faild to ComposeTitleBarV2 getStringByNameSync icon_back,code: ${code},message:${message}`);
      }
    } else if (this.item.value === PUBLIC_MORE) {
      try {
        return getContext()?.resourceManager?.getStringByNameSync('ohos_toolbar_more');
      } catch (err) {
        let code: number = (err as BusinessError)?.code;
        let message: string = (err as BusinessError)?.message;
        hilog.error(0x3900, 'Ace',
          `Faild to ComposeTitleBarV2 getStringByNameSync ohos_toolbar_more,code: ${code},message:${message}`);
      }
    } else if (this.item.accessibilityText) {
      return this.item.accessibilityText as string;
    } else if (this.item.label) {
      return this.item.label as string;
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
      let code: number = (err as BusinessError)?.code;
      let message: string = (err as BusinessError)?.message;
      hilog.error(0x3900, 'ComposeTitleBarV2',
        `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
    this.fontSize = this.decideFontScale();
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
      let code: number = (exception as BusinessError)?.code;
      let message: string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'ComposeTitleBarV2', `Faild to decideFontScale,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  @Builder
  itemCardDialogBuilder(): void {
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
            })
        } else {
          if (Util.isSymbolResource(this.item.value)) {
            SymbolGlyph(this.item.value as Resource)
              .fontSize(IMAGE_SIZE)
              .fontColor([$r('sys.color.icon_primary')])
              .margin({
                top: $r('sys.float.padding_level24'),
                bottom: $r('sys.float.padding_level8'),
              })
          } else {
            Image(this.item.value)
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
          Text(this.item.label)
            .fontSize(TEXT_EDITABLE_DIALOG)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .maxLines(this.dialogTextMaxLine)
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
      .constraintSize({ minHeight: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG })
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
      .constraintSize({ minHeight: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG })
      .justifyContent(FlexAlign.Center)
    }
  }

  private getItemGestureModifier(): ButtonGestureModifier {
    this.buttonGestureModifier.gestureCallBack = (event: UIGestureEvent) => {
      if (this.fontSize >= this.minFontSize) {
        event.addGesture(
          new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime })
            .onAction(() => {
              promptAction.openCustomDialog({
                builder: () => {
                  this.itemCardDialogBuilder();
                },
                onWillAppear: () => {
                  try {
                    let context = this.getUIContext().getHostContext() as common.UIAbilityContext;
                    let mainWindowStage = context.windowStage.getMainWindowSync();
                    let properties: window.WindowProperties = mainWindowStage.getWindowProperties();
                    if (px2vp(properties.windowRect.height) > SCREEN_WIDTH_BREAK_POINT) {
                      this.dialogTextMaxLine = VERTICAL_SCREEN_TEXT_MAX_LINES;
                    } else {
                      this.dialogTextMaxLine = HORIZONTAL_SCREEN_TEXT_MAX_LINES;
                    }
                  } catch (err) {
                    let code: number = (err as BusinessError)?.code;
                    let message: string = (err as BusinessError)?.message;
                    hilog.error(0x3900, 'ComposeTitleBarV2',
                      `Faild to get window height, code: ${code}, message: ${message}`);
                  }
                },
                maskColor: Color.Transparent,
                isModal: true,
                backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK,
                backgroundColor: Color.Transparent,
                shadow: ShadowStyle.OUTER_DEFAULT_LG,
                cornerRadius: $r('sys.float.corner_radius_level10'),
                width: this.fontSize === this.minFontSize ? MAX_DIALOG : MIN_DIALOG
              }).then((dialogId: number) => {
                this.itemDialogId = dialogId;
              });
            })
            .onActionEnd(() => {
              if (this.itemDialogId) {
                promptAction.closeCustomDialog(this.itemDialogId);
              }
            })
            .onActionCancel(() => {
              if (this.itemDialogId) {
                promptAction.closeCustomDialog(this.itemDialogId);
              }
            })
        )
        return;
      }
      event.clearGestures();
    }
    return this.buttonGestureModifier;
  }

  build() {
    if (this.isPopup) {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
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
            Image(this.item?.value)
              .matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false)
              .width(ImageMenuItemV2.imageSize)
              .draggable(false)
              .height(ImageMenuItemV2.imageSize)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
              .fillColor($r('sys.color.ohos_id_color_text_primary'))
          }
        }
      }
      .id(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.item?.accessibilityDescription as string)
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .width(ImageMenuItemV2.imageHotZoneWidth)
      .height(ImageMenuItemV2.imageHotZoneWidth)
      .borderRadius(ImageMenuItemV2.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: ImageMenuItemV2.focusBorderWidth,
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
          if (this.fontSize >= this.minFontSize && this.itemDialogId) {
            promptAction.closeCustomDialog(this.itemDialogId);
          }
        }
      })
      .onClick(() => {
        if (this.item) {
          return this.item.isEnabled && this.item.action?.();
        }
      })
      .gestureModifier(this.getItemGestureModifier())
    } else {
      Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
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
            Image(this.item?.value)
              .matchTextDirection(this.item?.value === PUBLIC_BACK ? true : false)
              .width(ImageMenuItemV2.imageSize)
              .draggable(false)
              .height(ImageMenuItemV2.imageSize)
              .focusable(this.item?.isEnabled)
              .key(ImageMenuItemV2.focusablePrefix + this.index)
              .fillColor($r('sys.color.ohos_id_color_text_primary'))
          }
        }
      }
      .id(`ComposeTitleBarV2_ImageMenuItem_${this.parentParentUniqueId}_${this.itemIndex}`)
      .accessibilityText(this.getAccessibilityReadText())
      .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
      .accessibilityDescription(this.item?.accessibilityDescription as string)
      .enabled(this.item.isEnabled ? this.item.isEnabled : false)
      .width(ImageMenuItemV2.imageHotZoneWidth)
      .height(ImageMenuItemV2.imageHotZoneWidth)
      .borderRadius(ImageMenuItemV2.buttonBorderRadius)
      .foregroundColor(this.getFgColor())
      .backgroundColor(this.getBgColor())
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_clicked'),
            width: ImageMenuItemV2.focusBorderWidth,
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
          if (this.fontSize >= this.minFontSize && this.itemDialogId) {
            promptAction.closeCustomDialog(this.itemDialogId);
          }
        }
      })
      .onClick(() => {
        if (this.item) {
          return this.item.isEnabled && this.item.action?.();
        }
      })
    }
  }
}