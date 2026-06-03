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
  Column, Row, ComponentV2, Button, Text, CustomDialog, $r, Flex, List, HoverEvent, ImageLoadResult,
  Canvas, BlendMode, Scroller, ForEach, AttributeModifier, GestureModifier, ListItem, BuilderParam,
  ResourceStr, UIGestureEvent, LongPressGestureHandler, PopupOptions, PopupStateChangeParam, CustomPopupOptions,
  CustomDialogController, ScrollOptions, ScrollAnimationOptions, SwiperController, ResourceColor, Area,
  RenderingContextSettings, CanvasRenderingContext2D, Builder, FontWeight, FlexAlign, KeyEvent,
  TouchEvent, ItemAlign, Stack, Alignment, EdgeEffect, Axis, BarState, BlendApplyType, Swiper, Curve,
  Color, ButtonType, SymbolGlyph, BorderStyle, TouchType, KeyType, Placement, GeometryInfo, Layoutable,
  ConstraintSizeOptions, focusControl, BorderOptions, HitTestMode, SymbolEffect, ImageCompleteEvent, Resource,
  Image, Callback, ImageFit, VerticalAlign, TextOverflow, TextAlign, ShadowStyle, BlurStyle, Margin, Padding,
  CommonMethod, ButtonOptions, ImageError, ImageOnCompleteCallback, ImageErrorCallback,
  ClickEvent, LocalizedPadding, LengthMetrics
} from "@ohos.arkui.component";
import { BusinessError } from '@ohos.base';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { Param, Local, Once } from '@ohos.arkui.stateManagement';
import { Context, UIContext, MeasureUtils } from "@ohos.arkui.UIContext";
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import resourceManager from '@ohos.resourceManager';
import { MeasureOptions } from '@ohos.measure';
import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import hilog from '@ohos.hilog';
import promptAction from '@ohos.promptAction';
import i18n from '@ohos.i18n';

export class TabTitleBarV2MenuItem {
  value: ResourceStr = '';
  symbolStyle?: SymbolGlyphModifier;
  isEnabled?: boolean;
  action?: () => void;
  label?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityLevel?: string;
  accessibilityDescription?: ResourceStr;
}

export class TabTitleBarV2TabItem {
  title: ResourceStr = '';
  icon?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
}

const PUBLIC_MORE: Resource = $r('sys.symbol.dot_grid_2x2');
const TEXT_EDITABLE_DIALOG = '18.3fp';
const IMAGE_SIZE = '64vp';
const MAX_DIALOG = '256vp';
const MIN_DIALOG = '216vp';
const RESOURCE_TYPE_SYMBOL = 40000;

export class ButtonGestureModifier implements GestureModifier {
  public static readonly longPressTime: number = 500;
  public static readonly minFontSize: number = 1.75;
  public gestureCallBack?: (event: UIGestureEvent) => void = undefined;

  applyGesture(event: UIGestureEvent): void {
    this.gestureCallBack?.(event);
  }
}

@ComponentV2
export struct TabTitleBarV2 {
  public static readonly totalHeight: number = 56;
  public static readonly correctionOffset: number = -40.0;
  public static readonly gradientMaskWidth: number = 24;
  private static instanceCount: number = 0;
  
  @Param tabItems: Array<TabTitleBarV2TabItem> = new Array<TabTitleBarV2TabItem>();
  @Param menuItems: Array<TabTitleBarV2MenuItem> = new Array<TabTitleBarV2MenuItem>();
  @BuilderParam swiperContent: () => void = this.emptyBuilder;

  @Local tabWidth: number = 0;
  @Local currentIndex: number = 0;
  @Local swiperCurrentIndex: int = 0;
  @Local fontSize: number = 1;

  private menuSectionWidth: number = 0;
  private tabOffsets: Array<number> = new Array<number>();
  private imageWidths: Array<number> = new Array<number>();
  private scroller: Scroller = new Scroller();
  private swiperController: SwiperController = new SwiperController();
  private settings: RenderingContextSettings = new RenderingContextSettings(true);
  private leftContext2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);
  private rightContext2D: CanvasRenderingContext2D = new CanvasRenderingContext2D(this.settings);

  @Builder
  GradientMask(context2D: CanvasRenderingContext2D, x0: number, y0: number, x1: number, y1: number) {
    Column() {
      Canvas(context2D)
        .width(TabTitleBarV2.gradientMaskWidth)
        .height(TabTitleBarV2.totalHeight)
        .onReady(() => {
          let grad = context2D.createLinearGradient(x0, y0, x1, y1);
          grad.addColorStop(0.0, '#ffffffff');
          grad.addColorStop(1, '#00ffffff');
          context2D.fillStyle = grad;
          context2D.fillRect(0, 0, TabTitleBarV2.gradientMaskWidth, TabTitleBarV2.totalHeight);
        } as () => void)
    }
    .blendMode(BlendMode.DST_OUT)
    .width(TabTitleBarV2.gradientMaskWidth)
    .height(TabTitleBarV2.totalHeight)
  }

  @Builder
  emptyBuilder() {
  }

  aboutToAppear() {
    if (!this.swiperContent) {
      this.swiperContent = this.emptyBuilder;
    }
    this.tabItems.forEach((_elem) => {
      this.imageWidths.push(0);
    })
    this.loadOffsets();
  }

  loadOffsets() {
    this.tabOffsets.length = 0;

    let tabOffset: number = 0;
    this.tabOffsets.push(tabOffset);
    tabOffset += TabContentItemV2.marginFirst;

    this.tabItems.forEach((tabItem: TabTitleBarV2TabItem, index: int) => {
      if (tabItem.icon !== undefined || tabItem.symbolStyle !== undefined) {
        if (Math.abs(this.imageWidths[index]) > TabContentItemV2.imageHotZoneWidth) {
          tabOffset += this.imageWidths[index.toInt()];
        } else {
          tabOffset += TabContentItemV2.imageHotZoneWidth;
        }
      } else {
        tabOffset += TabContentItemV2.paddingLeft;
        let uiContextMeasure: MeasureUtils = this.getUIContext().getMeasureUtils();
        tabOffset += this.getUIContext().px2vp(uiContextMeasure.measureText({
          textContent: tabItem.title.toString(),
          fontSize: 18,
          fontWeight: FontWeight.Medium,
        } as MeasureOptions));
        tabOffset += TabContentItemV2.paddingRight;
      }
      this.tabOffsets.push(tabOffset);
    })
  }

  private isRTL(): boolean {
    try {
      return i18n.isRTL(i18n.System.getSystemLanguage() as string) ?? false;
    } catch (exception) {
      const code: undefined | int = (exception as BusinessError)?.code;
      const message: undefined | string = (exception as BusinessError)?.message;
      hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
      return false;
    }
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
                ForEach(this.tabItems, (tabItem: TabTitleBarV2TabItem, index: int) => {
                  ListItem() {
                    TabContentItemV2({
                      item: tabItem,
                      index: index,
                      maxIndex: this.tabItems.length - 1,
                      currentIndex: this.currentIndex,
                      onCustomClick: (itemIndex: number) => {
                        this.currentIndex = itemIndex;
                      },
                      onImageComplete: (width: number) => {
                        this.imageWidths[index.toInt()] = width;
                        this.loadOffsets();
                      }
                    })
                  }
                }, (item: TabTitleBarV2TabItem, index: int) => {
                  return JSON.stringify(item.title + '-' + index)
                })
              }
              .width('100%')
              .height(TabTitleBarV2.totalHeight)
              .constraintSize({ maxWidth: this.tabWidth })
              .edgeEffect(EdgeEffect.Spring)
              .listDirection(Axis.Horizontal)
              .scrollBar(BarState.Off)
            }
            if (this.isRTL()) {
              this.GradientMask(this.rightContext2D, TabTitleBarV2.gradientMaskWidth,
                TabTitleBarV2.totalHeight / 2, 0, TabTitleBarV2.totalHeight / 2)
            } else {
              this.GradientMask(this.leftContext2D, 0, TabTitleBarV2.totalHeight / 2,
                TabTitleBarV2.gradientMaskWidth, TabTitleBarV2.totalHeight / 2)
            }
          }
          if (this.isRTL()) {
            this.GradientMask(this.leftContext2D, 0, TabTitleBarV2.totalHeight / 2,
              TabTitleBarV2.gradientMaskWidth, TabTitleBarV2.totalHeight / 2)
          } else {
            this.GradientMask(this.rightContext2D, TabTitleBarV2.gradientMaskWidth,
              TabTitleBarV2.totalHeight / 2, 0, TabTitleBarV2.totalHeight / 2)
          }
        }
        .blendMode(BlendMode.SRC_OVER, BlendApplyType.OFFSCREEN)

        if (this.menuItems !== undefined && this.menuItems.length > 0) {
          CollapsibleMenuSectionV2({
            menuItems: this.menuItems,
            index: 1 + TabTitleBarV2.instanceCount++,
          })
            .height(TabTitleBarV2.totalHeight)
            .onAreaChange((_oldValue: Area, newValue: Area) => {
              this.menuSectionWidth = newValue.width as number
            })
        }
      }
      .backgroundColor($r('sys.color.ohos_id_color_background'))
      .margin({
        end: LengthMetrics.resource($r('sys.float.ohos_id_max_padding_end'))
      } as LocalizedPadding)
      .onAreaChange((_oldValue: Area, newValue: Area) => {
        this.tabWidth = newValue.width as number - this.menuSectionWidth;
      })

      Column() {
        Swiper(this.swiperController as SwiperController) {
          this.swiperContent();
        }
        .index(this.currentIndex.toInt())
        .itemSpace(0)
        .indicator(false)
        .width('100%')
        .height('100%')
        .curve(Curve.Friction)
        .onChange((index: int) => {
          if (index < this.tabOffsets.length) {
            const offset = this.tabOffsets[index.toInt()] + TabTitleBarV2.correctionOffset;
            this.currentIndex = index;
            this.scroller.scrollTo({
              xOffset: offset > 0 ? offset : 0,
              yOffset: 0,
              animation: {
                duration: 300,
                curve: Curve.EaseInOut
              } as ScrollAnimationOptions
            } as ScrollOptions)
          }
        } as Callback<int>)
        .onAppear(() => {
          this.scroller.scrollToIndex(Double.toInt(this.currentIndex));
          this.scroller.scrollBy(TabTitleBarV2.correctionOffset, 0);
        })
      }
    }
  }
}

@ComponentV2
struct CollapsibleMenuSectionV2 {
  @Param menuItems: Array<TabTitleBarV2MenuItem> = new Array<TabTitleBarV2MenuItem>();
  @Param index: number = 0;
  @Param item: TabTitleBarV2MenuItem = {
    value: PUBLIC_MORE,
    symbolStyle: new SymbolGlyphModifier(PUBLIC_MORE) as SymbolGlyphModifier,
    label: $r('sys.string.ohos_toolbar_more'),
  } as TabTitleBarV2MenuItem;
  @Param @Once fontSize: number = 1;

  minFontSize: number = 1.75;
  maxFontSize: number = 3.2;
  screenWidth: number = 640;
  verticalScreenLines: int = 6;
  horizontalsScreenLines: int = 1;
  isFollowingSystemFontScale: boolean = false;
  maxFontScale: number = 1;
  systemFontScale?: number = 1;
  public static readonly maxCountOfVisibleItems: number = 1;
  private static readonly focusPadding: number = 4;
  private static readonly marginsNum: number = 2;
  private firstFocusableIndex: number = -1;

  @Local isPopupShown: boolean = false;
  @Local isMoreIconOnFocus: boolean = false;
  @Local isMoreIconOnHover: boolean = false;
  @Local isMoreIconOnClick: boolean = false;
  @Local dialogId?: int = undefined;
  @Local buttonGestureModifier: ButtonGestureModifier = new ButtonGestureModifier();
  @Local maxLines: int = 1;

  @Local tabTitleDialogItem: TabTitleBarV2MenuItem = { value: '' } as TabTitleBarV2MenuItem;
  @Local tabTitleBarDialogText?: ResourceStr = '';

  getMoreIconFgColor(): ResourceColor {
    return this.isMoreIconOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon');
  }

  getMoreIconBgColor(): ResourceColor {
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
      let context = uiContent.getHostContext() as common.UIAbilityContext;
      let mainWindowStage = context.windowStage.getMainWindowSync();
      let properties: window.WindowProperties = mainWindowStage.getWindowProperties() as window.WindowProperties;
      let rect = properties.windowRect;
      if (this.getUIContext().px2vp(rect.height) > this.screenWidth) {
        this.maxLines = this.verticalScreenLines;
      } else {
        this.maxLines = this.horizontalsScreenLines;
      }
    } catch (exception) {
      let code: int | undefined = (exception as ClassCastError)?.code;
      let message: string | undefined = (exception as ClassCastError)?.message;
      hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to decideFontScale,cause, code: ${code}, message: ${message}`);
    }
    this.menuItems.forEach((item: TabTitleBarV2MenuItem, index: int) => {
      if (item.isEnabled && this.firstFocusableIndex === -1 &&
        index > CollapsibleMenuSectionV2.maxCountOfVisibleItems - 2) {
        this.firstFocusableIndex = this.index * 1000 + index + 1
      }
    })
    this.fontSize = this.decideFontScale();
    this.tabTitleDialogItem = this.item;
    this.tabTitleBarDialogText = this.item.label ? this.item.label : '';
    this.buttonGestureModifier.gestureCallBack = (event: UIGestureEvent) => {
      if (this.fontSize >= ButtonGestureModifier.minFontSize) {
        event.addGesture(
          new LongPressGestureHandler({ repeat: false, duration: ButtonGestureModifier.longPressTime.toInt() })
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

  decideFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    if (uiContent.getHostContext()) {
      this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    }
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(this.systemFontScale as number, this.maxFontScale);
  }

  private openDialog(): void {
    this.getUIContext().getPromptAction().openCustomDialog({
      builder: () => {
        this.dialogBuilder();
      } as () => void,
      onWillDisappear: () => {
        this.isMoreIconOnClick = false;
      } as () => void,
      maskColor: Color.Transparent,
      isModal: true
    } as promptAction.CustomDialogOptions
    ).then((id: int) => {
      this.dialogId = id;
    });
  }

  private closeDialog(): void {
    if (this.dialogId !== undefined) {
      this.getUIContext().getPromptAction().closeCustomDialog(this.dialogId as int);
      this.dialogId = undefined;
    }
  }

  build() {
    Column() {
      Row() {
        if (this.menuItems.length <= CollapsibleMenuSectionV2.maxCountOfVisibleItems) {
          ForEach(this.menuItems, (item: TabTitleBarV2MenuItem, index: int) => {
            ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1 })
          }, (item: TabTitleBarV2MenuItem, index: int) => {
            return JSON.stringify(item.value + '' + index)
          })
        } else {
          ForEach(this.menuItems.slice(0, CollapsibleMenuSectionV2.maxCountOfVisibleItems.toInt() - 1),
            (item: TabTitleBarV2MenuItem, index: int) => {
              ImageMenuItemV2({ item: item, index: this.index * 1000 + index + 1 })
            }, (item: TabTitleBarV2MenuItem, index: int) => {
              return JSON.stringify(item.value + '' + index)
            })

          Button({ type: ButtonType.Normal, stateEffect: true } as ButtonOptions) {
            SymbolGlyph(PUBLIC_MORE)
              .fontSize(TabContentItemV2.symbolSize)
              .draggable(false)
              .fontColor([$r('sys.color.icon_primary')])
              .focusable(true)
          }
          .accessibilityText(this.toStringFormat($r('sys.string.ohos_toolbar_more')))
          .width(ImageMenuItemV2.imageHotZoneWidth)
          .height(ImageMenuItemV2.imageHotZoneWidth)
          .borderRadius(ImageMenuItemV2.buttonBorderRadius)
          .foregroundColor(this.getMoreIconFgColor())
          .backgroundColor(this.getMoreIconBgColor())
          .stateStyles({
            focused: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: ImageMenuItemV2.focusBorderWidth,
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
          .onHover((isOn: boolean, event: HoverEvent) => {
            this.isMoreIconOnHover = isOn;
          })
          .onKeyEvent((event: KeyEvent): boolean => {
            return Util.handleKeyEvent(event,
              () => { this.isMoreIconOnClick = true; },
              () => { this.isMoreIconOnClick = false; }
            );
          } as Callback<KeyEvent, boolean>)
          .onTouch((event: TouchEvent) => {
            Util.handleTouchEvent(event,
              () => { this.isMoreIconOnClick = true; },
              () => {
                this.isMoreIconOnClick = false;
                if (this.fontSize >= this.minFontSize) {
                  this.closeDialog();
                }
              }
            );
          })
          .onClick((event?: ClickEvent) => {
            this.isPopupShown = true;
          } as () => void)
          .gestureModifier(this.buttonGestureModifier)
          .bindPopup(this.isPopupShown as boolean, {
            builder: this.popupBuilder,
            placement: Placement.Bottom,
            popupColor: Color.White,
            enableArrow: false,
            onStateChange: (e: PopupStateChangeParam) => {
              this.isPopupShown = e.isVisible;
              if (!e.isVisible) {
                this.isMoreIconOnClick = false;
              }
            }
          } as CustomPopupOptions)
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

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return ' ';
    } else {
      let resourceString: undefined | string = ' ';
      try {
        resourceString = resourceManager.getSysResourceManager().getStringSync((resource as Resource).id as Long);
      } catch (exception) {
        let code: int | undefined = (exception as ClassCastError)?.code;
        let message: string | undefined = (exception as ClassCastError)?.message;
        hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to TabTitleBar toStringFormat,code: ${code},
        message:${message}`);
      }
      return resourceString;
    }
  }

  @Builder
  dialogBuilder() {
    Column() {
      if (this.tabTitleDialogItem.symbolStyle) {
        SymbolGlyph()
          .fontColor([$r('sys.color.font_primary')])
          .attributeModifier(this.tabTitleDialogItem.symbolStyle)
          .fontSize(IMAGE_SIZE)
          .draggable(false)
          .focusable(this.tabTitleDialogItem?.isEnabled)
          .margin({
            top: $r('sys.float.padding_level24'),
            bottom: $r('sys.float.padding_level8'),
          } as Margin)
          .symbolEffect(new SymbolEffect(), false)
      } else if (this.tabTitleDialogItem.value) {
        if (Util.isSymbolResource(this.tabTitleDialogItem.value)) {
          SymbolGlyph(this.tabTitleDialogItem.value as Resource)
            .fontColor([$r('sys.color.font_primary')])
            .fontSize(IMAGE_SIZE)
            .draggable(false)
            .focusable(this.tabTitleDialogItem?.isEnabled)
            .margin({
              top: $r('sys.float.padding_level24'),
              bottom: $r('sys.float.padding_level8'),
            } as Margin)
        } else {
          Image(this.tabTitleDialogItem.value)
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
        Text(this.tabTitleBarDialogText)
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
    .width(this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG)
    .constraintSize({ minHeight: this.fontSize === this.maxFontSize ? MAX_DIALOG : MIN_DIALOG })
    .backgroundBlurStyle(BlurStyle.COMPONENT_ULTRA_THICK, undefined, { disableSystemAdaptation: true })
    .shadow(ShadowStyle.OUTER_DEFAULT_LG)
    .borderRadius($r('sys.float.corner_radius_level10'))
  }

  @Builder
  popupBuilder() {
    Column() {
      ForEach(this.menuItems.slice(CollapsibleMenuSectionV2.maxCountOfVisibleItems.toInt() - 1, this.menuItems.length),
        (item: TabTitleBarV2MenuItem, index: int) => {
          ImageMenuItemV2({
            item: item as TabTitleBarV2MenuItem, index: this.index * 1000 +
              CollapsibleMenuSectionV2.maxCountOfVisibleItems + index
          });
        }, (item: TabTitleBarV2MenuItem, index: int) => {
          return JSON.stringify(item.value + '' + index)
        })
    }
    .width(ImageMenuItemV2.imageHotZoneWidth 
      + CollapsibleMenuSectionV2.focusPadding * CollapsibleMenuSectionV2.marginsNum)
    .margin({ top: CollapsibleMenuSectionV2.focusPadding, bottom: CollapsibleMenuSectionV2.focusPadding } as Margin)
    .onAppear(() => {
      focusControl.requestFocus(ImageMenuItemV2.focusablePrefix + this.firstFocusableIndex);
    })
  }
}

@ComponentV2
struct TabContentItemV2 {
  @Param item: TabTitleBarV2TabItem = { title: '' } as TabTitleBarV2TabItem;
  @Param index: number = 0;
  @Param maxIndex: number = 0;
  @Param onCustomClick?: (index: number) => void = undefined;
  @Param onImageComplete?: (width: number) => void = undefined;
  @Param currentIndex: number = 0;

  @Local isOnFocus: boolean = false;
  @Local isOnHover: boolean = false;
  @Local isOnClick: boolean = false;
  @Local tabWidth: number = 0;

  @Local imageWidth: number = 24;
  @Local imageHeight: number = 24;

  public static readonly imageSize: number = 24;
  public static readonly symbolSize: string = '24vp';
  public static readonly imageHotZoneWidth: number = 48;
  public static readonly imageMagnificationFactor: number = 1.4;
  public static readonly buttonBorderRadius: number = 8;
  public static readonly focusBorderWidth: number = 2;
  public static readonly paddingLeft: number = 8;
  public static readonly paddingRight: number = 8;
  public static readonly marginFirst: number = 16;

  getBgColor(): ResourceColor {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  getBorderAttr(): BorderOptions {
    if (this.isOnFocus) {
      return {
        radius: $r('sys.float.ohos_id_corner_radius_clicked'),
        width: TabContentItemV2.focusBorderWidth,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
      };
    }
    return { width: 0 }
  }

  getImageScaleFactor(): number {
    return this.index === this.currentIndex ? TabContentItemV2.imageMagnificationFactor : 1;
  }

  getImageLayoutWidth(): number {
    return TabContentItemV2.imageSize / Math.max(this.imageHeight, 1.0) * this.imageWidth;
  }

  private completeCallback: ImageOnCompleteCallback | undefined = (info?: ImageCompleteEvent) => {
    let onImageCompleteValue: number =
      this.getUIContext().px2vp(info?.componentWidth as int) 
        + TabContentItemV2.paddingLeft + TabContentItemV2.paddingRight;
    this.onImageComplete?.(onImageCompleteValue);
  }
  private onErrorCallback: ImageErrorCallback | undefined = (event: ImageError) => {
    if (!this.onImageComplete) {
      return;
    }
    let onImageComplete: number =
      this.getUIContext().px2vp(event.componentWidth as int) 
        + TabContentItemV2.paddingLeft + TabContentItemV2.paddingRight
    this.onImageComplete?.(onImageComplete);
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return ' ';
    } else {
      let resourceString: undefined | string = ' ';
      try {
        resourceString = resourceManager.getSysResourceManager().getStringSync((resource as Resource).id as Long);
      } catch (exception) {
        let code: int | undefined = (exception as ClassCastError)?.code;
        let message: string | undefined = (exception as ClassCastError)?.message;
        hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to TabTitleBar toStringFormat,code: ${code},
        message:${message}`);
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
                left: TabContentItemV2.paddingLeft,
                bottom: 2,
                right: TabContentItemV2.paddingRight
              } as Padding)
              .onFocus(() => {
                this.isOnFocus = true;
              })
              .onBlur(() => {
                this.isOnFocus = false;
              })
              .onHover((isOn: boolean, event: HoverEvent) => {
                this.isOnHover = isOn;
              })
              .onKeyEvent((event: KeyEvent): boolean => {
                return Util.handleKeyEvent(event,
                  () => { this.isOnClick = true; },
                  () => { this.isOnClick = false; }
                );
              } as Callback<KeyEvent, boolean>)
              .onTouch((event: TouchEvent) => {
                Util.handleTouchEvent(event,
                  () => { this.isOnClick = true; },
                  () => { this.isOnClick = false; }
                );
              })
              .onClick(() => {
                if (typeof this.onCustomClick === 'function') {
                  this.onCustomClick?.(this.index);
                }
              } as () => void)
              .accessibilitySelected(this.index === this.currentIndex)
          } else {
            Row() {
              if (this.item.symbolStyle) {
                SymbolGlyph()
                  .fontColor([$r('sys.color.icon_primary')])
                  .attributeModifier(this.item.symbolStyle)
                  .fontSize(TabContentItemV2.symbolSize)
                  .width(this.getImageLayoutWidth())
                  .height(TabContentItemV2.imageSize)
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
                    .fontSize(TabContentItemV2.symbolSize)
                    .width(this.getImageLayoutWidth())
                    .height(TabContentItemV2.imageSize)
                    .accessibilityText(this.toStringFormat(this.item.title))
                    .scale({
                      x: this.getImageScaleFactor(),
                      y: this.getImageScaleFactor()
                    })
                    .animation({ duration: 300 })
                    .hitTestBehavior(HitTestMode.None)
                    .focusable(true)
                } else {
                  Image((this.item?.icon ?? '') as ResourceStr)
                    .alt(this.item.title)
                    .width(this.getImageLayoutWidth())
                    .height(TabContentItemV2.imageSize)
                    .objectFit(ImageFit.Fill)
                    .accessibilityText(this.toStringFormat(this.item.title))
                    .scale({
                      x: this.getImageScaleFactor(),
                      y: this.getImageScaleFactor()
                    })
                    .animation({ duration: 300 })
                    .hitTestBehavior(HitTestMode.None)
                    .focusable(true)
                    .onComplete(this.completeCallback)
                    .onError(this.onErrorCallback)
                }
              }
            }
            .width(this.getImageLayoutWidth() * this.getImageScaleFactor() +
              TabContentItemV2.paddingLeft + TabContentItemV2.paddingRight)
            .constraintSize({
              minWidth: TabContentItemV2.imageHotZoneWidth,
              minHeight: TabContentItemV2.imageHotZoneWidth
            })
            .animation({ duration: 300 })
            .justifyContent(FlexAlign.Center)
            .onFocus(() => {
              this.isOnFocus = true;
            } as () => void)
            .onBlur(() => {
              this.isOnFocus = false;
            } as () => void)
            .onHover((isOn: boolean, event: HoverEvent) => {
              this.isOnHover = isOn;
            })
            .onKeyEvent((event: KeyEvent): boolean => {
              return Util.handleKeyEvent(event,
                () => { this.isOnClick = true; },
                () => { this.isOnClick = false; }
              );
            } as Callback<KeyEvent, boolean>)
            .onTouch((event: TouchEvent) => {
              Util.handleTouchEvent(event,
                () => { this.isOnClick = true; },
                () => { this.isOnClick = false; }
              );
            })
            .onClick(() => {
              if (typeof this.onCustomClick === 'function') {
                this.onCustomClick?.(this.index as number);
              }
            } as () => void)
            .accessibilitySelected(this.index === this.currentIndex)
          }
        }
        .justifyContent(FlexAlign.Center)
      }
      .height(TabTitleBarV2.totalHeight)
      .alignItems(VerticalAlign.Center)
      .justifyContent(FlexAlign.Center)
      .borderRadius(TabContentItemV2.buttonBorderRadius)
      .backgroundColor(this.getBgColor())
      .onAreaChange((_oldValue: Area, newValue: Area) => {
        this.tabWidth = newValue.width as number;
      })

      if (this.isOnFocus && this.tabWidth > 0) {
        Row()
          .width(this.tabWidth)
          .height(TabTitleBarV2.totalHeight)
          .hitTestBehavior(HitTestMode.None)
          .borderRadius(TabContentItemV2.buttonBorderRadius)
          .stateStyles({
            focused: (instance: CommonMethod) => {
              instance.border(this.getBorderAttr())
            },
            normal: (instance: CommonMethod) => {
              instance.border({
                radius: $r('sys.float.ohos_id_corner_radius_clicked'),
                width: 0
              })
            }
          })
      }
    }
    .margin({
      start: LengthMetrics.vp(this.index === 0 ? TabContentItemV2.marginFirst : 0),
      end: LengthMetrics.vp(this.index === this.maxIndex ? 12 : 0)
    } as LocalizedPadding)
  }
}

@ComponentV2
struct ImageMenuItemV2 {
  @Param item: TabTitleBarV2MenuItem = { value: '' } as TabTitleBarV2MenuItem;
  @Param index: number = 0;

  static readonly imageSize: number = 24;
  static readonly imageHotZoneWidth: number = 48;
  static readonly buttonBorderRadius: number = 8;
  static readonly focusBorderWidth: number = 2;
  static readonly disabledImageOpacity: number = 0.4;
  static readonly focusablePrefix: string = "Id-TabTitleBar-ImageMenuItem-";

  @Local isOnFocus: boolean = false;
  @Local isOnHover: boolean = false;
  @Local isOnClick: boolean = false;

  getFgColor(): ResourceColor {
    return this.isOnClick
      ? $r('sys.color.ohos_id_color_titlebar_icon_pressed')
      : $r('sys.color.ohos_id_color_titlebar_icon');
  }

  getBgColor(): ResourceColor {
    if (this.isOnClick) {
      return $r('sys.color.ohos_id_color_click_effect');
    } else if (this.isOnHover) {
      return $r('sys.color.ohos_id_color_hover');
    } else {
      return Color.Transparent;
    }
  }

  private toStringFormat(resource: ResourceStr | undefined): string | undefined {
    if (typeof resource === 'string') {
      return resource as string;
    } else if (typeof resource === 'undefined') {
      return ' ' as string;
    } else {
      let resourceString: undefined | string = ' ';
      try {
        resourceString = resourceManager.getSysResourceManager().getStringSync((resource as Resource).id as Long);
      } catch (exception) {
        let code: int | undefined = (exception as ClassCastError)?.code;
        let message: string | undefined = (exception as ClassCastError)?.message;
        hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to TabTitleBar toStringFormat,code: ${code},
        message:${message}`);
      }
      return resourceString;
    }
  }

  private getAccessibilityReadText(): string | undefined {
    if (this.item.value === PUBLIC_MORE) {
      try {
        return resourceManager.getSysResourceManager().getStringByNameSync('ohos_toolbar_more');
      } catch (exception) {
        let code: int | undefined = (exception as ClassCastError)?.code;
        let message: string | undefined = (exception as ClassCastError)?.message;
        hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to TabTitleBar toStringFormat,code: ${code},
        message:${message}`);
      }
    } else if (this.item.accessibilityText) {
      if (typeof this.item.accessibilityText === 'string') {
        return this.item.accessibilityText as string;
      } else if (typeof this.item.accessibilityText === 'undefined') {
        return ' ' as string;
      } else {
        let accessibilityText: string = ' ';
        try {
          accessibilityText = resourceManager.getSysResourceManager()
            .getStringSync((this.item.accessibilityText as Resource).id as Long);
        } catch (exception) {
          let code: int | undefined = (exception as ClassCastError)?.code;
          let message: string | undefined = (exception as ClassCastError)?.message;
          hilog.error(0x3900, 'AdvancedTabTitleBar',
            `Failed to TabTitleBar toStringFormat,code: ${code},message:${message}`);
        }
        return accessibilityText as string;
      }
    } else if (this.item.label) {
      if (typeof this.item.label === 'string') {
        return this.item.label as string;
      } else if (typeof this.item.label === 'undefined') {
        return ' ' as string;
      } else {
        let label: string = ' ';
        try {
          label = resourceManager.getSysResourceManager().getStringSync((this.item.label as Resource).id as Long);
        } catch (exception) {
          let code: int | undefined = (exception as ClassCastError)?.code;
          let message: string | undefined = (exception as ClassCastError)?.message;
          hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to TabTitleBar toStringFormat,code: ${
            code},message:${message}`);
        }
        return label as string;
      }
    }
    return ' ';
  }

  private getAccessibilityReadDescription(): string | undefined {
    if (this.item.accessibilityDescription) {
      if (typeof this.item.accessibilityDescription === 'string') {
        return this.item.accessibilityDescription as string;
      } else if (typeof this.item.accessibilityDescription === 'undefined') {
        return ' ' as string;
      } else {
        let accessibilityDescription: string = ' ';
        try {
          accessibilityDescription = resourceManager.getSysResourceManager()
            .getStringSync((this.item.accessibilityDescription as Resource).id as Long);
        } catch (exception) {
          let code: int | undefined = (exception as ClassCastError)?.code;
          let message: string | undefined = (exception as ClassCastError)?.message;
          hilog.error(0x3900, 'AdvancedTabTitleBar', `Failed to TabTitleBar toStringFormat,code: ${code},message:${message}`);
        }
        return accessibilityDescription as string;
      }
    }
    return ' ';
  }

  build() {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled } as ButtonOptions) {
      if (this.item.symbolStyle) {
        SymbolGlyph()
          .fontColor([$r('sys.color.font_primary')])
          .attributeModifier(this.item.symbolStyle)
          .fontSize(TabContentItemV2.symbolSize)
          .draggable(false)
          .focusable(this.item?.isEnabled)
          .key(ImageMenuItemV2.focusablePrefix + this.index)
          .symbolEffect(new SymbolEffect(), false)
      } else {
        if (Util.isSymbolResource(this.item.value)) {
          SymbolGlyph(this.item.value as Resource)
            .fontColor([$r('sys.color.font_primary')])
            .fontSize(TabContentItemV2.symbolSize)
            .draggable(false)
            .focusable(this.item?.isEnabled)
            .key(ImageMenuItemV2.focusablePrefix + this.index)
        } else {
          Image(this.item.value)
            .width(ImageMenuItemV2.imageSize)
            .height(ImageMenuItemV2.imageSize)
            .focusable(this.item.isEnabled)
            .key(ImageMenuItemV2.focusablePrefix + this.index)
            .draggable(false)
        }
      }
    }
    .accessibilityText(this.getAccessibilityReadText())
    .accessibilityLevel(this.item?.accessibilityLevel ?? 'auto')
    .accessibilityDescription(this.getAccessibilityReadDescription())
    .width(ImageMenuItemV2.imageHotZoneWidth)
    .height(ImageMenuItemV2.imageHotZoneWidth)
    .borderRadius(ImageMenuItemV2.buttonBorderRadius)
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .enabled(this.item.isEnabled ? this.item.isEnabled : false)
    .stateStyles({
      focused: (instance: CommonMethod) => {
        instance.border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: ImageMenuItemV2.focusBorderWidth,
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
    } as () => void)
    .onHover((isOn: boolean, event: HoverEvent) => {
      if (this.item.isEnabled) {
        this.isOnHover = isOn;
      }
    })
    .onKeyEvent((event: KeyEvent): boolean => {
      if (!this.item.isEnabled) {
        return false;
      }
      return Util.handleKeyEvent(event,
        () => { this.isOnClick = true; },
        () => { this.isOnClick = false; }
      );
    } as Callback<KeyEvent, boolean>)
    .onTouch((event: TouchEvent) => {
      if (!this.item.isEnabled) {
        return;
      }
      Util.handleTouchEvent(event,
        () => { this.isOnClick = true; },
        () => { this.isOnClick = false; }
      );
    })
    .onClick(() => {
      if (this.item.isEnabled && typeof this.item?.action === 'function') {
        (this.item?.action as () => void)();
      }
    } as () => void)
  }
}

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
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

  public static handleKeyEvent(event: KeyEvent, onPressDown: () => void, onPressUp: () => void): boolean {
    if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
      return false;
    }
    if (event.type === KeyType.Down) {
      onPressDown();
    }
    if (event.type === KeyType.Up) {
      onPressUp();
    }
    return true;
  }

  public static handleTouchEvent(event: TouchEvent, onPressDown: () => void, onPressUp: () => void): void {
    if (event.type === TouchType.Down) {
      onPressDown();
    }
    if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
      onPressUp();
    }
  }
}