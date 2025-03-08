/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

import { ButtonOptions } from '@ohos.arkui.advanced.Dialog';
import { BusinessError, Callback } from '@ohos.base';
import display from '@ohos.display';
import hilog from '@ohos.hilog';
import measure from '@ohos.measure';
import resourceManager from '@ohos.resourceManager';
import { CustomColors, CustomTheme, Theme } from '@ohos.arkui.theme';
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';
import { accessibility } from '@kit.AccessibilityKit';
import { KeyCode } from '@kit.InputKit';

class CustomThemeImpl implements CustomTheme {
  public colors?: CustomColors;

  constructor(colors: CustomColors) {
    this.colors = colors;
  }
}

const TITLE_MAX_LINES: number = 2;
const HORIZON_BUTTON_MAX_COUNT: number = 2;
const VERTICAL_BUTTON_MAX_COUNT: number = 4;
const BUTTON_LAYOUT_WEIGHT: number = 1;
const CONTENT_MAX_LINES: number = 2;
const LOADING_PROGRESS_WIDTH: number = 40;
const LOADING_PROGRESS_HEIGHT: number = 40;
const LOADING_MAX_LINES: number = 10;
const LOADING_MAX_LINES_BIG_FONT: number = 4;
const LOADING_TEXT_LAYOUT_WEIGHT: number = 1;
const LOADING_TEXT_MARGIN_LEFT: number = 12;
const LOADING_MIN_HEIGHT: number = 48;
const LIST_MIN_HEIGHT: number = 48;
const CHECKBOX_CONTAINER_LENGTH: number = 20;
const TEXT_MIN_HEIGHT: number = 48;
const MIN_CONTENT_HEIGHT: number = 100;
const MAX_CONTENT_HEIGHT: number = 30000;
const KEYCODE_UP: number = 2012;
const KEYCODE_DOWN: number = 2013;
const IGNORE_KEY_EVENT_TYPE: number = 1;
const FIRST_ITEM_INDEX: number = 0;
const VERSION_TWELVE: number = 50000012;
const MAX_FONT_SCALE: number = 2;
const FADEOUT_GRADIENT_WIDTH: number = 32;
const FADEOUT_ENABLE: string = 'true';

// 'sys.float.alert_container_max_width'
const MAX_DIALOG_WIDTH: number = getNumberByResourceId(125831042, 400);
// 'sys.float.alert_right_padding_horizontal'
const BUTTON_HORIZONTAL_MARGIN: number = getNumberByResourceId(125831054, 16);
// 'sys.float.padding_level8'
const BUTTON_HORIZONTAL_PADDING: number = getNumberByResourceId(125830927, 16);
// 'sys.float.alert_button_horizontal_space'
const BUTTON_HORIZONTAL_SPACE: number = getNumberByResourceId(125831051, 8);
// 'sys.float.Body_L'
const BODY_L = getNumberByResourceId(125830970, 16);
// 'sys.float.Body_M'
const BODY_M = getNumberByResourceId(125830971, 14);
// 'sys.float.Body_S'
const BODY_S = getNumberByResourceId(125830972, 12);
// 'sys.float.Title_S'
const TITLE_S = getNumberByResourceId(125830966, 20);
// 'sys.float.padding_level8'
const PADDING_LEVEL_8 = getNumberByResourceId(125830927, 16);

const BUTTON_MIN_FONT_SIZE = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_button_font_min_size'), 9);
});
const BUTTON_MAX_FONT_SIZE = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_button_font_max_size'), 16);
});
const DEFAULT_IMAGE_SIZE = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_tip_image_size'), 64);
});
const DEFAULT_IMAGE_RADIUS = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_tip_image_radius'), 12);
});
const TIP_TEXT_TOP_PADDING = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_tip_text_top_padding'), 16);
});
const TIP_CHECKBOX_TOP_PADDING = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_checkbox_top_padding'), 8);
});
const TIP_CHECKBOX_BOTTOM_PADDING = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_checkbox_bottom_padding'), 8, true);
});
const TIP_CHECKBOX_END_MARGIN = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_checkbox_end_margin'), 8);
});
const SUBTITLE_SIZE = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_subtitle_font_size'), 14);
});
const CHECKBOX_CONTAINER_HEIGHT = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_checkbox_min_height'), 48, true);
});
const CONTENT_END_MARGIN = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_content_right_margin'), 16);
});
const SCROLL_END_MARGIN = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_scroll_right_margin'), 16);
});
const DIALOG_DIVIDER_SHOW = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_divider_show'), 1, true);
});
const ALERT_BUTTON_STYLE = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.alert_button_style'), 2, true);
});
const ALERT_TITLE_ALIGNMENT = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.alert_title_alignment'), 1);
});
const ERROR_BUTTON_STYLE = lazyInit<number>(() => {
  return getLengthMetricsByResource($r('sys.float.dialog_error_button_style'), 2, true);
});
// 'sys.string.ohos_id_text_fadeout_enable_default'
const IS_FADEOUT_ENABLE = lazyInit<boolean>(() => {
  return getString(125831120) === FADEOUT_ENABLE;
});
// 'sys.string.dialog_title_font_weight'
const TITLE_FONT_WEIGHT = lazyInit<FontWeight>(() => {
  let fontWeight: FontWeight = FontWeight[getString(125834679) || 'Bold'];
  return fontWeight;
});
// 'sys.string.dialog_content_font_weight'
const CONTENT_FONT_WEIGHT = lazyInit<FontWeight>(() => {
  let fontWeight: FontWeight = FontWeight[getString(125834682) || 'Medium'];
  return fontWeight;
});
const SCROLL_BAR_OFFSET = 20;

@CustomDialog
export struct TipsDialog {
  controller: CustomDialogController;
  imageRes: ResourceStr | PixelMap | null = null;
  @State imageSize?: SizeOptions = { width: DEFAULT_IMAGE_SIZE(), height: DEFAULT_IMAGE_SIZE() };
  title?: ResourceStr | null = null;
  content?: ResourceStr | null = null;
  checkAction?: (isChecked: boolean) => void;
  onCheckedChange?: Callback<boolean>;
  checkTips?: ResourceStr | null = null;
  @State isChecked?: boolean = false;
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  buttons?: ButtonOptions[] | undefined = undefined;
  @State textAlignment: TextAlign = TextAlign.Start;
  marginOffset: number = 0;
  // the controller of content area scroll
  contentScroller: Scroller = new Scroller();
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State minContentHeight: number = 160;
  updateTextAlign: (maxWidth: number) => void = (maxWidth: number) => {
    if (this.content) {
      this.textAlignment = getTextAlign(maxWidth, this.content, `${BODY_L * this.fontSizeScale}vp`);
    }
  }
  imageIndex: number = 0;
  textIndex: number = 1;
  checkBoxIndex: number = 2;
  appMaxFontScale: number = 3.2;

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      minContentHeight: this.minContentHeight,
    }).constraintSize({ maxHeight: '100%' });
  }

  @Builder
  contentBuilder(): void {
    TipsDialogContentLayout({
      title: this.title,
      content: this.content,
      checkTips: this.checkTips,
      minContentHeight: this.minContentHeight,
      updateTextAlign: this.updateTextAlign,
    }) {
      ForEach([this.imageIndex, this.textIndex, this.checkBoxIndex], (index: number) => {
        if (index === this.imageIndex) {
          this.imagePart();
        } else if (index === this.textIndex) {
          Column() {
            WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
              this.textPart();
            }
          }
          .padding({ top: TIP_TEXT_TOP_PADDING() })
        } else {
          WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
            this.checkBoxPart();
          }
        }
      });
    }
  }

  @Builder
  checkBoxPart(): void {
    Row() {
      if (this.checkTips !== null) {
        Checkbox({ name: '', group: 'checkboxGroup' }).select(this.isChecked)
          .onChange((checked: boolean) => {
            this.isChecked = checked;
            if (this.checkAction) {
              this.checkAction(checked);
            }
            if (this.onCheckedChange) {
              this.onCheckedChange(checked);
            }
          })
          .margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(TIP_CHECKBOX_END_MARGIN()) })
        Text(this.checkTips)
          .fontSize(`${BODY_L}fp`)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.fontColorWithTheme)
          .maxLines(CONTENT_MAX_LINES)
          .layoutWeight(1)
          .focusable(false)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
      }
    }
    .accessibilityGroup(true)
    .accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isChecked))
    .accessibilityDescription(this.isChecked ? $r('sys.string.advanced_dialog_accessibility_cancel_checked_desc') :
    $r('sys.string.slider_accessibility_unselectedDesc'))
    .onClick(() => {
      this.isChecked = !this.isChecked;
      if (this.checkAction) {
        this.checkAction(this.isChecked);
      }
      try {
        let eventInfo: accessibility.EventInfo = ({
          type: 'announceForAccessibility',
          bundleName: (getContext() as common.UIAbilityContext)?.abilityInfo?.bundleName,
          triggerAction: 'common',
          textAnnouncedForAccessibility: this.isChecked ? getContext().resourceManager.getStringSync(125833934) :
          getContext().resourceManager.getStringSync(125833935)
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.info(`Accessibility send event`)
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
      }
    })
    .padding({ top: TIP_CHECKBOX_TOP_PADDING(), bottom: TIP_CHECKBOX_BOTTOM_PADDING() })
    .constraintSize({ minHeight: CHECKBOX_CONTAINER_HEIGHT() })
    .width('100%')
  }

  @Builder
  imagePart(): void {
    Column() {
      Image(this.imageRes)
        .objectFit(ImageFit.Contain)
        .borderRadius(DEFAULT_IMAGE_RADIUS())
        .constraintSize({
          maxWidth: this.imageSize?.width ?? DEFAULT_IMAGE_SIZE(),
          maxHeight: this.imageSize?.height ?? DEFAULT_IMAGE_SIZE()
        })
    }
    .width('100%')
  }

  @Builder
  textPart(): void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.title !== null) {
          Row() {
            Text(this.title)
              .fontSize(`${TITLE_S}fp`)
              .maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE))
              .fontWeight(TITLE_FONT_WEIGHT())
              .fontColor(this.fontColorWithTheme)
              .textAlign(TextAlign.Center)
              .maxLines(CONTENT_MAX_LINES)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .width('100%')
          }
          .padding({ bottom: $r('sys.float.padding_level8') })
        }
        if (this.content !== null) {
          Row() {
            Text(this.content)
              .focusable(true)
              .defaultFocus(!(this.primaryButton || this.secondaryButton))
              .focusBox({
                strokeWidth: LengthMetrics.px(0)
              })
              .fontSize(this.getContentFontSize())
              .fontWeight(CONTENT_FONT_WEIGHT())
              .fontColor(this.fontColorWithTheme)
              .textAlign(this.textAlignment)
              .width('100%')
              .onKeyEvent((event: KeyEvent) => {
                if (event) {
                  resolveKeyEvent(event, this.contentScroller);
                }
              })
          }
        }
      }
      .margin({ end: LengthMetrics.vp(CONTENT_END_MARGIN()) })
    }
    .fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) })
    .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
    .margin({ end: LengthMetrics.vp(this.marginOffset) })
  }

  aboutToAppear() {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    let uiContext: UIContext = this.getUIContext();
    this.appMaxFontScale = uiContext.getMaxFontScale();
    this.initButtons();
    this.initMargin();
  }

  getContentFontSize(): Length {
    return BODY_L + 'fp';
  }

  private initButtons(): void {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }

  private initMargin(): void {
    this.marginOffset = 0 - SCROLL_END_MARGIN();
  }
}

@Component
struct TipsDialogContentLayout {
  @Builder
  doNothingBuilder() {
  };

  title?: ResourceStr | null = null;
  content?: ResourceStr | null = null;
  checkTips?: ResourceStr | null = null;
  updateTextAlign: (maxWidth: number) => void = (maxWidth: number) => {
  };
  @Link minContentHeight: number;
  @BuilderParam dialogBuilder: () => void = this.doNothingBuilder;
  imageIndex: number = 0;
  textIndex: number = 1;
  checkBoxIndex: number = 2;
  childrenSize: number = 3;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: Number(constraint.maxWidth), height: 0 };
    if (children.length < this.childrenSize) {
      return sizeResult;
    }
    let height: number = 0;
    let checkBoxHeight: number = 0;
    if (this.checkTips !== null) {
      let checkboxChild: Measurable = children[this.checkBoxIndex];
      let checkboxConstraint: ConstraintSizeOptions = {
        maxWidth: constraint.maxWidth,
        minHeight: CHECKBOX_CONTAINER_HEIGHT(),
        maxHeight: constraint.maxHeight
      }
      let checkBoxMeasureResult: MeasureResult = checkboxChild.measure(checkboxConstraint);
      checkBoxHeight = checkBoxMeasureResult.height;
      height += checkBoxHeight;
    }

    let imageChild: Measurable = children[this.imageIndex];
    let textMinHeight: number = 0;
    if (this.title !== null || this.content !== null) {
      textMinHeight = TEXT_MIN_HEIGHT + PADDING_LEVEL_8;
    }
    let imageMaxHeight = Number(constraint.maxHeight) - checkBoxHeight - textMinHeight;
    let imageConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      maxHeight: imageMaxHeight
    }
    let imageMeasureResult: MeasureResult = imageChild.measure(imageConstraint);
    height += imageMeasureResult.height;

    if (this.title !== null || this.content !== null) {
      let textChild: Measurable = children[this.textIndex];
      this.updateTextAlign(sizeResult.width);
      let contentMaxHeight: number = Number(constraint.maxHeight) - imageMeasureResult.height - checkBoxHeight;
      let contentConstraint: ConstraintSizeOptions =
        {
          maxWidth: constraint.maxWidth,
          maxHeight: Math.max(contentMaxHeight, TEXT_MIN_HEIGHT)
        };
      let contentMeasureResult: MeasureResult = textChild.measure(contentConstraint);
      height += contentMeasureResult.height;
    }
    sizeResult.height = height;
    this.minContentHeight = Math.max(checkBoxHeight + imageMeasureResult.height + textMinHeight, MIN_CONTENT_HEIGHT);
    return sizeResult;
  }

  build() {
    this.dialogBuilder();
  }
}

@CustomDialog
export struct SelectDialog {
  controller: CustomDialogController;
  title: ResourceStr = '';
  content?: ResourceStr = '';
  confirm?: ButtonOptions | null = null;
  radioContent: Array<SheetInfo> = [];
  buttons?: ButtonOptions[] = [];
  contentPadding ?: Padding;
  isFocus: boolean = false;
  currentFocusIndex?: number = -1;
  radioHeight: number = 0;
  itemHeight: number = 0;
  @State selectedIndex?: number = -1;
  @BuilderParam contentBuilder: () => void = this.buildContent;
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @State dividerColorWithTheme: ResourceColor = $r('sys.color.comp_divider');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  // the controller of content list
  contentScroller: Scroller = new Scroller();
  @State fontSizeScale: number = 1;
  @State minContentHeight: number = MIN_CONTENT_HEIGHT;

  @Styles
  paddingContentStyle() {
    .padding({
      left: $r('sys.float.padding_level12'),
      right: $r('sys.float.padding_level12'),
      bottom: $r('sys.float.padding_level4')
    })
  }

  @Styles
  paddingStyle() {
    .padding({
      left: $r('sys.float.padding_level6'),
      right: $r('sys.float.padding_level6')
    })
  }

  @Builder
  buildContent(): void {
    Scroll(this.contentScroller) {
      Column() {
        if (this.content) {
          Row() {
            Text(this.content)
              .fontSize(`${BODY_M}fp`)
              .fontWeight(FontWeight.Regular)
              .fontColor(this.fontColorWithTheme)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
          }.paddingContentStyle().width('100%')
        }
        List() {
          ForEach(this.radioContent, (item: SheetInfo, index: number) => {
            ListItem() {
              Column() {
                Button() {
                  Row() {
                    Text(item.title)
                      .fontSize(`${BODY_L}fp`)
                      .fontWeight(FontWeight.Medium)
                      .fontColor(this.fontColorWithTheme)
                      .layoutWeight(1)
                    Radio({ value: 'item.title', group: 'radioGroup' })
                      .size({ width: CHECKBOX_CONTAINER_LENGTH, height: CHECKBOX_CONTAINER_LENGTH })
                      .checked(this.selectedIndex === index)
                      .hitTestBehavior(HitTestMode.None)
                      .id(String(index))
                      .focusable(false)
                      .accessibilityLevel('no')
                      .onFocus(() => {
                        this.isFocus = true;
                        this.currentFocusIndex = index;
                        if (index === FIRST_ITEM_INDEX) {
                          this.contentScroller.scrollEdge(Edge.Top);
                        } else if (index === this.radioContent.length - 1) {
                          this.contentScroller.scrollEdge(Edge.Bottom);
                        }
                      })
                      .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
                        this.radioHeight = Number(newValue.height)
                      })
                  }.constraintSize({ minHeight: LIST_MIN_HEIGHT }).clip(false)
                  .padding({ top: $r('sys.float.padding_level4'), bottom: $r('sys.float.padding_level4') })
                }
                .type(ButtonType.Normal)
                .borderRadius($r('sys.float.corner_radius_level8'))
                .buttonStyle(ButtonStyleMode.TEXTUAL)
                .paddingStyle()

                if (index < this.radioContent.length - 1) {
                  Divider().color(this.dividerColorWithTheme).paddingStyle();
                }
              }
              .borderRadius($r('sys.float.corner_radius_level8'))
              .focusBox({
                margin: { value: -2, unit: LengthUnit.VP }
              })
              .accessibilityText(getAccessibilityText(item.title, this.selectedIndex === index))
              .onClick(() => {
                this.selectedIndex = index;
                item.action && item.action();
                this.controller?.close();
              })
            }
            .paddingStyle()
            .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
              this.itemHeight = Number(newValue.height)
            })
          })
        }.width('100%').clip(false)
        .onFocus(() => {
          if (!this.contentScroller.isAtEnd()) {
            this.contentScroller.scrollEdge(Edge.Top);
            focusControl.requestFocus(String(FIRST_ITEM_INDEX));
          }
        })
        .defaultFocus(this.buttons?.length === 0 ? true : false)
      }
    }.scrollBar(BarState.Auto)
    .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
    .onDidScroll((xOffset: number, yOffset: number) => {
      let scrollHeight: number = (this.itemHeight - this.radioHeight) / 2
      if (this.isFocus) {
        if (this.currentFocusIndex === this.radioContent.length - 1) {
          this.contentScroller.scrollEdge(Edge.Bottom);
          this.currentFocusIndex = -1;
        } else if (this.currentFocusIndex === FIRST_ITEM_INDEX) {
          this.contentScroller.scrollEdge(Edge.Top);
          this.currentFocusIndex = -1;
        } else {
          if (yOffset > 0) {
            this.contentScroller.scrollBy(0, scrollHeight)
          } else if (yOffset < 0) {
            this.contentScroller.scrollBy(0, 0 - scrollHeight)
          }
        }
        this.isFocus = false;
      }
    })
  }

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      primaryTitle: this.title,
      contentBuilder: () => {
        this.contentBuilder();
      },
      buttons: this.buttons,
      contentAreaPadding: this.contentPadding,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      minContentHeight: this.minContentHeight,
    }).constraintSize({ maxHeight: '100%' });
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.dividerColorWithTheme = this.theme?.colors?.compDivider ?
    this.theme.colors.compDivider : $r('sys.color.comp_divider');
    this.initContentPadding();
    this.initButtons();
  }

  private initContentPadding(): void {
    this.contentPadding = {
      left: $r('sys.float.padding_level0'),
      right: $r('sys.float.padding_level0')
    }

    if (!this.title && !this.confirm) {
      this.contentPadding = {
        top: $r('sys.float.padding_level12'),
        bottom: $r('sys.float.padding_level12')
      }
      return;
    }

    if (!this.title) {
      this.contentPadding = {
        top: $r('sys.float.padding_level12')
      }
    } else if (!this.confirm) {
      this.contentPadding = {
        bottom: $r('sys.float.padding_level12')
      }
    }
  }

  private initButtons(): void {
    this.buttons = [];
    if (this.confirm) {
      this.buttons.push(this.confirm);
    }
  }
}

@Component
struct ConfirmDialogContentLayout {
  textIndex: number = 0;
  checkboxIndex: number = 1;
  @Link minContentHeight: number;
  updateTextAlign: (maxWidth: number) => void = (maxWidth: number) => {
  };

  @Builder
  doNothingBuilder() {
  };

  @BuilderParam dialogBuilder: () => void = this.doNothingBuilder;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: Number(constraint.maxWidth), height: 0 };
    let childrenSize: number = 2;
    if (children.length < childrenSize) {
      return sizeResult;
    }
    this.updateTextAlign(sizeResult.width);
    let height: number = 0;
    let checkboxChild: Measurable = children[this.checkboxIndex];
    let checkboxConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      minHeight: CHECKBOX_CONTAINER_HEIGHT(),
      maxHeight: constraint.maxHeight
    }
    let checkBoxMeasureResult: MeasureResult = checkboxChild.measure(checkboxConstraint);
    height += checkBoxMeasureResult.height;

    let textChild: Measurable = children[this.textIndex];
    let textConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      maxHeight: Number(constraint.maxHeight) - height
    }
    let textMeasureResult: MeasureResult = textChild.measure(textConstraint);
    height += textMeasureResult.height;
    sizeResult.height = height;
    this.minContentHeight = Math.max(checkBoxMeasureResult.height + TEXT_MIN_HEIGHT, MIN_CONTENT_HEIGHT);
    return sizeResult;
  }

  build() {
    this.dialogBuilder();
  }
}

@CustomDialog
export struct ConfirmDialog {
  controller: CustomDialogController
  title: ResourceStr = ''
  content?: ResourceStr = ''
  checkTips?: ResourceStr = ''
  @State isChecked?: boolean = false
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  onCheckedChange?: Callback<boolean>;
  contentScroller: Scroller = new Scroller();
  buttons?: ButtonOptions[] | undefined = undefined;
  @State textAlign: TextAlign = TextAlign.Start;
  marginOffset: number = 0;
  @State fontSizeScale: number = 1;
  @State minContentHeight: number = MIN_CONTENT_HEIGHT;
  textIndex: number = 0;
  checkboxIndex: number = 1;
  updateTextAlign: (maxWidth: number) => void = (maxWidth: number) => {
    if (this.content) {
      this.textAlign = getTextAlign(maxWidth, this.content, `${BODY_L * this.fontSizeScale}vp`);
    }
  }

  @Builder
  textBuilder(): void {
    Column() {
      Scroll(this.contentScroller) {
        Column() {
          Text(this.content)
            .focusable(true)
            .defaultFocus(!(this.primaryButton?.value || this.secondaryButton?.value))
            .focusBox({
              strokeWidth: LengthMetrics.px(0)
            })
            .fontSize(`${BODY_L}fp`)
            .fontWeight(CONTENT_FONT_WEIGHT())
            .fontColor(this.fontColorWithTheme)
            .textAlign(this.textAlign)
            .onKeyEvent((event: KeyEvent) => {
              if (event) {
                resolveKeyEvent(event, this.contentScroller);
              }
            })
            .width('100%')
        }
        .margin({ end: LengthMetrics.vp(CONTENT_END_MARGIN()) })
      }
      .fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) })
      .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
      .margin({ end: LengthMetrics.vp(this.marginOffset) })
    }
  }

  @Builder
  checkBoxBuilder(): void {
    Row() {
      Checkbox({ name: '', group: 'checkboxGroup' })
        .select(this.isChecked)
        .onChange((checked: boolean) => {
          this.isChecked = checked;
          if (this.onCheckedChange) {
            this.onCheckedChange(this.isChecked);
          }
        })
        .hitTestBehavior(HitTestMode.Block)
        .margin({ start: LengthMetrics.vp(0), end: LengthMetrics.vp(TIP_CHECKBOX_END_MARGIN()) })

      Text(this.checkTips)
        .fontSize(`${SUBTITLE_SIZE()}fp`)
        .fontWeight(CONTENT_FONT_WEIGHT())
        .fontColor(this.fontColorWithTheme)
        .maxLines(CONTENT_MAX_LINES)
        .focusable(false)
        .layoutWeight(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .accessibilityGroup(true)
    .accessibilityText(getCheckTipsAccessibilityText(this.checkTips, this.isChecked))
    .accessibilityDescription(this.isChecked ? $r('sys.string.advanced_dialog_accessibility_cancel_checked_desc') :
    $r('sys.string.slider_accessibility_unselectedDesc'))
    .onClick(() => {
      this.isChecked = !this.isChecked;
      try {
        let eventInfo: accessibility.EventInfo = ({
          type: 'announceForAccessibility',
          bundleName: (getContext() as common.UIAbilityContext)?.abilityInfo?.bundleName,
          triggerAction: 'common',
          textAnnouncedForAccessibility: this.isChecked ? getContext().resourceManager.getStringSync(125833934) :
          getContext().resourceManager.getStringSync(125833935)
        });
        accessibility.sendAccessibilityEvent(eventInfo).then(() => {
          console.info(`Accessibility send event`)
        });
      } catch (exception) {
        let code: number = (exception as BusinessError).code;
        let message: string = (exception as BusinessError).message;
        hilog.error(0x3900, 'Ace', `Faild to send event, cause, code: ${code}, message: ${message}`);
      }
    })
    .width('100%')
    .padding({ top: TIP_CHECKBOX_TOP_PADDING(), bottom: TIP_CHECKBOX_BOTTOM_PADDING() })
  }

  @Builder
  buildContent(): void {
    ConfirmDialogContentLayout({ minContentHeight: this.minContentHeight, updateTextAlign: this.updateTextAlign }) {
      ForEach([this.textIndex, this.checkboxIndex], (index: number) => {
        if (index === this.textIndex) {
          WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
            this.textBuilder();
          }
        } else if (index === this.checkboxIndex) {
          WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
            this.checkBoxBuilder();
          }
        }
      });
    }
  }

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.title,
      controller: this.controller,
      contentBuilder: () => {
        this.buildContent();
      },
      minContentHeight: this.minContentHeight,
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
    }).constraintSize({ maxHeight: '100%' });
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.initButtons();
    this.initMargin();
  }

  private initMargin(): void {
    this.marginOffset = 0 - SCROLL_END_MARGIN();
  }

  private initButtons(): void {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }
}

@CustomDialog
export struct AlertDialog {
  controller: CustomDialogController;
  primaryTitle?: ResourceStr | undefined = undefined;
  secondaryTitle?: ResourceStr | undefined = undefined;
  content: ResourceStr = '';
  primaryButton?: ButtonOptions | null = null;
  secondaryButton?: ButtonOptions | null = null;
  buttons?: ButtonOptions[] | undefined = undefined;
  @State textAlign: TextAlign = TextAlign.Start;
  // the controller of content area
  contentScroller: Scroller = new Scroller();
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State minContentHeight: number = MIN_CONTENT_HEIGHT;

  build() {
    CustomDialogContentComponent({
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      controller: this.controller,
      contentBuilder: () => {
        this.AlertDialogContentBuilder();
      },
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      minContentHeight: this.minContentHeight,
    }).constraintSize({ maxHeight: '100%' });
  }

  @Builder
  AlertDialogContentBuilder(): void {
    Column() {
      Scroll(this.contentScroller) {
        Text(this.content)
          .focusable(true)
          .defaultFocus(!(this.primaryButton || this.secondaryButton))
          .focusBox({
            strokeWidth: LengthMetrics.px(0)
          })
          .fontSize(`${BODY_L}fp`)
          .fontWeight(this.getFontWeight())
          .fontColor(this.fontColorWithTheme)
          .margin({ end: LengthMetrics.vp(SCROLL_BAR_OFFSET) })
          .width(`calc(100% - ${SCROLL_BAR_OFFSET}vp)`)
          .textAlign(this.textAlign)
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            this.updateTextAlign(Number(newValue.width));
          })
          .onKeyEvent((event: KeyEvent) => {
            if (event) {
              resolveKeyEvent(event, this.contentScroller);
            }
          })
      }
      .fadingEdge(IS_FADEOUT_ENABLE(), { fadingEdgeLength: LengthMetrics.vp(FADEOUT_GRADIENT_WIDTH) })
      .nestedScroll({ scrollForward: NestedScrollMode.PARALLEL, scrollBackward: NestedScrollMode.PARALLEL })
      .width('100%')
    }
    .margin({ end: LengthMetrics.vp(0 - SCROLL_BAR_OFFSET) })
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.initButtons();
  }

  private updateTextAlign(maxWidth: number): void {
    this.textAlign = getTextAlign(maxWidth, this.content, `${BODY_L * this.fontSizeScale}vp`);
  }

  private initButtons(): void {
    if (!this.primaryButton && !this.secondaryButton) {
      return;
    }
    this.buttons = [];
    if (this.primaryButton) {
      this.buttons.push(this.primaryButton);
    }
    if (this.secondaryButton) {
      this.buttons.push(this.secondaryButton);
    }
  }

  private getFontWeight(): number {
    if (this.primaryTitle || this.secondaryTitle) {
      return FontWeight.Regular;
    }
    return CONTENT_FONT_WEIGHT();
  }
}

@CustomDialog
export struct CustomContentDialog {
  controller: CustomDialogController;
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  @BuilderParam contentBuilder: () => void;
  contentAreaPadding?: Padding;
  localizedContentAreaPadding?: LocalizedPadding;
  buttons?: ButtonOptions[];
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State minContentHeight: number = MIN_CONTENT_HEIGHT;

  build() {
    CustomDialogContentComponent({
      controller: this.controller,
      primaryTitle: this.primaryTitle,
      secondaryTitle: this.secondaryTitle,
      contentBuilder: () => {
        this.contentBuilder();
      },
      contentAreaPadding: this.contentAreaPadding,
      localizedContentAreaPadding: this.localizedContentAreaPadding,
      buttons: this.buttons,
      theme: this.theme,
      themeColorMode: this.themeColorMode,
      fontSizeScale: this.fontSizeScale,
      minContentHeight: this.minContentHeight,
      customStyle: false
    }).constraintSize({ maxHeight: '100%' });
  }
}

class CustomDialogControllerExtend extends CustomDialogController {
  public arg_: CustomDialogControllerOptions;

  constructor(value: CustomDialogControllerOptions) {
    super(value);
    this.arg_ = value;
  }
}

@Component
struct CustomDialogLayout {
  @Builder
  doNothingBuilder(): void {
  };

  @Link titleHeight: number;
  @Link buttonHeight: number;
  @Link titleMinHeight: Length;
  @BuilderParam dialogBuilder: () => void = this.doNothingBuilder;
  titleIndex: number = 0;
  contentIndex: number = 1;
  buttonIndex: number = 2;

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>,
    constraint: ConstraintSizeOptions) {
    let currentX: number = 0;
    let currentY: number = 0;
    for (let index = 0; index < children.length; index++) {
      let child = children[index];
      child.layout({ x: currentX, y: currentY });
      currentY += child.measureResult.height;
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: Number(constraint.maxWidth), height: 0 };
    let childrenSize: number = 3;
    if (children.length < childrenSize) {
      return sizeResult;
    }
    let height: number = 0;
    let titleChild: Measurable = children[this.titleIndex];
    let titleConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      minHeight: this.titleMinHeight,
      maxHeight: constraint.maxHeight
    };
    let titleMeasureResult: MeasureResult = titleChild.measure(titleConstraint);
    this.titleHeight = titleMeasureResult.height;
    height += this.titleHeight;

    let buttonChild: Measurable = children[this.buttonIndex];
    let buttonMeasureResult: MeasureResult = buttonChild.measure(constraint);
    this.buttonHeight = buttonMeasureResult.height;
    height += this.buttonHeight;

    let contentChild: Measurable = children[this.contentIndex];
    let contentConstraint: ConstraintSizeOptions = {
      maxWidth: constraint.maxWidth,
      maxHeight: Number(constraint.maxHeight) - height
    };

    let contentMeasureResult: MeasureResult = contentChild.measure(contentConstraint);
    height += contentMeasureResult.height;
    sizeResult.height = height;
    return sizeResult;
  }

  build() {
    this.dialogBuilder();
  }
}


@Component
struct CustomDialogContentComponent {
  controller?: CustomDialogController;
  primaryTitle?: ResourceStr;
  secondaryTitle?: ResourceStr;
  localizedContentAreaPadding?: LocalizedPadding;
  @BuilderParam contentBuilder: () => void = this.defaultContentBuilder;
  buttons?: ButtonOptions[];
  contentAreaPadding?: Padding;
  keyIndex: number = 0;
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @Link minContentHeight: number;

  @Builder
  defaultContentBuilder(): void {
  }

  @State titleHeight: number = 0;
  @State buttonHeight: number = 0;
  @State contentMaxHeight: Length = '100%';
  @Link fontSizeScale: number;
  @State customStyle: boolean | undefined = undefined;
  @State buttonMaxFontSize: Length = `${BODY_L}fp`;
  @State buttonMinFontSize: Length = 9;
  @State primaryTitleMaxFontSize: Length = `${TITLE_S}fp`;
  @State primaryTitleMinFontSize: Length = `${BODY_L}fp`;
  @State secondaryTitleMaxFontSize: Length = `${SUBTITLE_SIZE()}fp`;
  @State secondaryTitleMinFontSize: Length = `${BODY_S}fp`;
  @State primaryTitleFontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @State secondaryTitleFontColorWithTheme: ResourceColor = $r('sys.color.font_secondary');
  @State titleTextAlign: TextAlign = TextAlign.Center;
  @State isButtonVertical: boolean = false;
  @State titleMinHeight: Length = 0;
  isFollowingSystemFontScale: boolean = false;
  appMaxFontScale: number = 3.2;
  titleIndex: number = 0;
  contentIndex: number = 1;
  buttonIndex: number = 2;
  isHasDefaultFocus: boolean = false;
  isAllFocusFalse: boolean = false;

  build() {
    WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
      Scroll() {
        Column() {
          CustomDialogLayout({
            buttonHeight: this.buttonHeight,
            titleHeight: this.titleHeight,
            titleMinHeight: this.titleMinHeight
          }) {
            ForEach([this.titleIndex, this.contentIndex, this.buttonIndex], (index: number) => {
              if (index === this.titleIndex) {
                WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
                  this.titleBuilder();
                }
              } else if (index === this.contentIndex) {
                Column() {
                  WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
                    this.contentBuilder();
                  }
                }.padding(this.getContentPadding())
              } else {
                WithTheme({ theme: this.theme, colorMode: this.themeColorMode }) {
                  this.ButtonBuilder();
                }
              }
            });
          }
        }
        .constraintSize({ maxHeight: this.contentMaxHeight })
        .backgroundBlurStyle(this.customStyle ? BlurStyle.Thick : BlurStyle.NONE)
        .borderRadius(this.customStyle ? $r('sys.float.ohos_id_corner_radius_dialog') : 0)
        .margin(this.customStyle ? {
          start: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_start')),
          end: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_end')),
          bottom: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_bottom')),
        } : { left: 0, right: 0, bottom: 0 })
        .backgroundColor(this.customStyle ? $r('sys.color.ohos_id_color_dialog_bg') : Color.Transparent)
      }
      .edgeEffect(EdgeEffect.None, { alwaysEnabled: false })
      .backgroundColor(this.themeColorMode === ThemeColorMode.SYSTEM || undefined ?
      Color.Transparent : $r('sys.color.comp_background_primary'))
    }
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>,
    constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { width: selfLayoutInfo.width, height: selfLayoutInfo.height };
    let maxWidth: number = Number(constraint.maxWidth);
    let maxHeight: number = Number(constraint.maxHeight);
    this.fontSizeScale = this.updateFontScale();
    this.updateFontSize();
    this.isButtonVertical = this.isVerticalAlignButton(maxWidth - BUTTON_HORIZONTAL_MARGIN * 2);
    this.titleMinHeight = this.getTitleAreaMinHeight();
    let height: number = 0;
    children.forEach((child) => {
      this.contentMaxHeight = '100%';
      let measureResult: MeasureResult = child.measure(constraint);
      if (maxHeight - this.buttonHeight - this.titleHeight < this.minContentHeight) {
        this.contentMaxHeight = MAX_CONTENT_HEIGHT;
        measureResult = child.measure(constraint);
      }
      height += measureResult.height;
    });
    sizeResult.height = height;
    sizeResult.width = maxWidth;
    return sizeResult;
  }

  aboutToAppear(): void {
    let uiContext: UIContext = this.getUIContext();
    this.isFollowingSystemFontScale = uiContext.isFollowingSystemFontScale();
    this.appMaxFontScale = uiContext.getMaxFontScale();
    this.fontSizeScale = this.updateFontScale();
    if (this.controller && this.customStyle === undefined) {
      let customController: CustomDialogControllerExtend = this.controller as CustomDialogControllerExtend;
      if (customController.arg_ && customController.arg_.customStyle && customController.arg_.customStyle === true) {
        this.customStyle = true;
      }
    }
    if (this.customStyle === undefined) {
      this.customStyle = false;
    }
    this.primaryTitleFontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.secondaryTitleFontColorWithTheme = this.theme?.colors?.fontSecondary ?
    this.theme.colors.fontSecondary : $r('sys.color.font_secondary');
    this.initTitleTextAlign();
    this.setDefaultFocusState(this.buttons);
  }

  private updateFontSize(): void {
    if (this.fontSizeScale > MAX_FONT_SCALE) {
      this.buttonMaxFontSize = BUTTON_MAX_FONT_SIZE() * MAX_FONT_SCALE + 'vp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE() * MAX_FONT_SCALE + 'vp';
    } else {
      this.buttonMaxFontSize = BUTTON_MAX_FONT_SIZE() + 'fp';
      this.buttonMinFontSize = BUTTON_MIN_FONT_SIZE() + 'fp';
    }
  }

  updateFontScale(): number {
    try {
      let uiContext: UIContext = this.getUIContext();
      let systemFontScale = (uiContext.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(systemFontScale, this.appMaxFontScale);
    } catch (exception) {
      let code: number = (exception as BusinessError).code;
      let message: string = (exception as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Faild to init fontsizescale info,cause, code: ${code}, message: ${message}`);
      return 1;
    }
  }

  /**
   * get dialog content padding
   *
   * @returns content padding
   */
  private getContentPadding(): Padding | LocalizedPadding {
    if (this.localizedContentAreaPadding) {
      return this.localizedContentAreaPadding;
    }
    if (this.contentAreaPadding) {
      return this.contentAreaPadding;
    }

    if ((this.primaryTitle || this.secondaryTitle) && this.buttons && this.buttons.length > 0) {
      return {
        top: 0,
        right: $r('sys.float.alert_content_default_padding'),
        bottom: 0,
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: 0,
        right: $r('sys.float.alert_content_default_padding'),
        bottom: $r('sys.float.alert_content_default_padding'),
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else if (this.buttons && this.buttons.length > 0) {
      return {
        top: $r('sys.float.alert_content_default_padding'),
        right: $r('sys.float.alert_content_default_padding'),
        bottom: 0,
        left: $r('sys.float.alert_content_default_padding'),
      };
    } else {
      return {
        top: $r('sys.float.alert_content_default_padding'),
        right: $r('sys.float.alert_content_default_padding'),
        bottom: $r('sys.float.alert_content_default_padding'),
        left: $r('sys.float.alert_content_default_padding'),
      };
    }
  }

  @Builder
  titleBuilder() {
    Column() {
      Row() {
        Text(this.primaryTitle)
          .fontWeight(TITLE_FONT_WEIGHT())
          .fontColor(this.primaryTitleFontColorWithTheme)
          .textAlign(this.titleTextAlign)
          .maxFontSize(this.primaryTitleMaxFontSize)
          .minFontSize(this.primaryTitleMinFontSize)
          .maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE))
          .maxLines(TITLE_MAX_LINES)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')

      if (this.primaryTitle && this.secondaryTitle) {
        Row() {
        }.height($r('sys.float.padding_level1'))
      }

      Row() {
        Text(this.secondaryTitle)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.secondaryTitleFontColorWithTheme)
          .textAlign(this.titleTextAlign)
          .maxFontSize(this.secondaryTitleMaxFontSize)
          .minFontSize(this.secondaryTitleMinFontSize)
          .maxFontScale(Math.min(this.appMaxFontScale, MAX_FONT_SCALE))
          .maxLines(TITLE_MAX_LINES)
          .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .width('100%')
      }
      .width('100%')
    }
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .padding(this.getTitleAreaPadding())
  }

  /**
   * get title area padding
   *
   * @returns padding
   */
  private getTitleAreaPadding(): Padding {
    if (this.primaryTitle || this.secondaryTitle) {
      return {
        top: $r('sys.float.alert_title_padding_top'),
        right: $r('sys.float.alert_title_padding_right'),
        left: $r('sys.float.alert_title_padding_left'),
        bottom: $r('sys.float.alert_title_padding_bottom'),
      };
    }

    return {
      top: 0,
      right: $r('sys.float.alert_title_padding_right'),
      left: $r('sys.float.alert_title_padding_left'),
      bottom: 0,
    };
  }

  /**
   * get tile TextAlign
   * @returns TextAlign
   */
  private initTitleTextAlign(): void {
    let textAlign: number = ALERT_TITLE_ALIGNMENT();
    if (textAlign === TextAlign.Start) {
      this.titleTextAlign = TextAlign.Start;
    } else if (textAlign === TextAlign.Center) {
      this.titleTextAlign = TextAlign.Center;
    } else if (textAlign === TextAlign.End) {
      this.titleTextAlign = TextAlign.End;
    } else if (textAlign === TextAlign.JUSTIFY) {
      this.titleTextAlign = TextAlign.JUSTIFY;
    } else {
      this.titleTextAlign = TextAlign.Center;
    }
  }

  /**
   * get title area min height
   *
   * @returns min height
   */
  private getTitleAreaMinHeight(): ResourceStr | number {
    if (this.secondaryTitle) {
      return $r('sys.float.alert_title_secondary_height');
    } else if (this.primaryTitle) {
      return $r('sys.float.alert_title_primary_height');
    } else {
      return 0;
    }
  }

  /**
   * set state of button focus
   */
  private setDefaultFocusState(buttonList?: ButtonOptions[]): void {
    if (!buttonList) {
      return;
    }
    let falseNum: number = 0;
    buttonList.forEach((button: ButtonOptions) => {
      // 遍历查询按钮中存在是否存在默认按钮
      if (button.defaultFocus) {
        this.isHasDefaultFocus = true;
      }
      if (button.defaultFocus === false) {
        falseNum++;
      }
    });
    // 所有按钮defaultFocus都设置为false
    if (falseNum === buttonList.length) {
      this.isAllFocusFalse = true;
    }
  }

  @Builder
  ButtonBuilder(): void {
    Column() {
      if (this.buttons && this.buttons.length > 0) {
        if (this.isButtonVertical) {
          this.buildVerticalAlignButtons();
        } else {
          this.buildHorizontalAlignButtons();
        }
      }
    }
    .width('100%')
    .padding(this.getOperationAreaPadding());
  }

  /**
   * get operation area padding
   *
   * @returns padding
   */
  private getOperationAreaPadding(): Padding {
    if (this.isButtonVertical) {
      return {
        top: $r('sys.float.alert_button_top_padding'),
        right: $r('sys.float.alert_right_padding_vertical'),
        left: $r('sys.float.alert_left_padding_vertical'),
        bottom: $r('sys.float.alert_button_bottom_padding_vertical'),
      };
    }

    return {
      top: $r('sys.float.alert_button_top_padding'),
      right: $r('sys.float.alert_right_padding_horizontal'),
      left: $r('sys.float.alert_left_padding_horizontal'),
      bottom: $r('sys.float.alert_button_bottom_padding_horizontal'),
    };
  }

  @Builder
  buildSingleButton(buttonOptions: ButtonOptions): void {
    if (this.isNewPropertiesHighPriority(buttonOptions)) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse, this.controller)
        .role(buttonOptions.role ?? ButtonRole.NORMAL)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({
          maxLines: 1,
          overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
          maxFontSize: this.buttonMaxFontSize,
          minFontSize: this.buttonMinFontSize
        })
    } else if (buttonOptions.background !== undefined && buttonOptions.fontColor !== undefined) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse, this.controller)
        .backgroundColor(buttonOptions.background)
        .fontColor(buttonOptions.fontColor)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({
          maxLines: 1,
          overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
          maxFontSize: this.buttonMaxFontSize,
          minFontSize: this.buttonMinFontSize
        })
    } else if (buttonOptions.background !== undefined) {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse, this.controller)
        .backgroundColor(buttonOptions.background)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({
          maxLines: 1,
          overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
          maxFontSize: this.buttonMaxFontSize,
          minFontSize: this.buttonMinFontSize
        })
    } else {
      Button(buttonOptions.value)
        .setButtonProperties(buttonOptions, this.isHasDefaultFocus, this.isAllFocusFalse, this.controller)
        .fontColor(buttonOptions.fontColor)
        .key(`advanced_dialog_button_${this.keyIndex++}`)
        .labelStyle({
          maxLines: 1,
          overflow: IS_FADEOUT_ENABLE() ? TextOverflow.MARQUEE : TextOverflow.Ellipsis,
          maxFontSize: this.buttonMaxFontSize,
          minFontSize: this.buttonMinFontSize
        })
    }
  }

  @Builder
  buildHorizontalAlignButtons(): void {
    if (this.buttons && this.buttons.length > 0) {
      Row() {
        this.buildSingleButton(this.buttons[0]);
        if (this.buttons.length === HORIZON_BUTTON_MAX_COUNT) {
          Row() {
            Divider()
              .width($r('sys.float.alert_divider_width'))
              .height($r('sys.float.alert_divider_height'))
              .color(this.getDividerColor())
              .vertical(true)
          }
          .width(BUTTON_HORIZONTAL_SPACE * 2)
          .justifyContent(FlexAlign.Center)

          this.buildSingleButton(this.buttons[HORIZON_BUTTON_MAX_COUNT - 1]);
        }
      }
    }
  }

  @Builder
  buildVerticalAlignButtons(): void {
    if (this.buttons) {
      Column() {
        ForEach(this.buttons.slice(0, VERTICAL_BUTTON_MAX_COUNT), (item: ButtonOptions, index: number) => {
          this.buildButtonWithDivider(this.buttons?.length === HORIZON_BUTTON_MAX_COUNT ?
            HORIZON_BUTTON_MAX_COUNT - index - 1 : index);
        }, (item: ButtonOptions) => item.value.toString());
      }
    }
  }

  /**
   * get divider color
   *
   * @returns divider color
   */
  private getDividerColor(): ResourceColor {
    if (!this.buttons || this.buttons.length === 0 || !DIALOG_DIVIDER_SHOW()) {
      return Color.Transparent;
    }

    if (this.buttons[0].buttonStyle === ButtonStyleMode.TEXTUAL || this.buttons[0].buttonStyle === undefined) {
      if (this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === ButtonStyleMode.TEXTUAL ||
        this.buttons[HORIZON_BUTTON_MAX_COUNT - 1].buttonStyle === undefined) {
        return $r('sys.color.alert_divider_color');
      }
    }
    return Color.Transparent;
  }

  /**
   * is button buttonStyle and role properties high priority
   *
   * @param buttonOptions button properties
   * @returns check result
   */
  private isNewPropertiesHighPriority(buttonOptions: ButtonOptions): boolean {
    if (buttonOptions.role === ButtonRole.ERROR) {
      return true;
    }
    if (buttonOptions.buttonStyle !== undefined &&
      buttonOptions.buttonStyle !== ALERT_BUTTON_STYLE()) {
      return true;
    }
    if (buttonOptions.background === undefined && buttonOptions.fontColor === undefined) {
      return true;
    }
    return false;
  }

  @Builder
  buildButtonWithDivider(index: number): void {
    if (this.buttons && this.buttons[index]) {
      Row() {
        this.buildSingleButton(this.buttons[index]);
      }

      if ((this.buttons.length === HORIZON_BUTTON_MAX_COUNT ? HORIZON_BUTTON_MAX_COUNT - index - 1 : index) <
        Math.min(this.buttons.length, VERTICAL_BUTTON_MAX_COUNT) - 1) {
        Row() {
        }
        .height($r('sys.float.alert_button_vertical_space'))
      }
    }
  }

  private isVerticalAlignButton(width: number): boolean {
    if (this.buttons) {
      if (this.buttons.length === 1) {
        return false;
      }
      if (this.buttons.length !== HORIZON_BUTTON_MAX_COUNT) {
        return true;
      }
      let isVertical: boolean = false;
      let maxButtonTextSize = vp2px(width / HORIZON_BUTTON_MAX_COUNT - BUTTON_HORIZONTAL_MARGIN -
        BUTTON_HORIZONTAL_SPACE - 2 * BUTTON_HORIZONTAL_PADDING);
      this.buttons.forEach((button) => {
        let contentSize: SizeOptions = measure.measureTextSize({
          textContent: button.value,
          fontSize: this.buttonMaxFontSize
        });
        if (Number(contentSize.width) > maxButtonTextSize) {
          isVertical = true;
        }
      });
      return isVertical;
    }
    return false;
  }
}

@Extend(Button)
function setButtonProperties(buttonOptions: ButtonOptions, isHasDefaultFocus: boolean, isAllFocusFalse: boolean,
  controller?: CustomDialogController) {
  .onKeyEvent((event: KeyEvent) => {
    if (!event) {
      return;
    }
    if ((event.keyCode === KeyCode.KEYCODE_SPACE || event.keyCode === KeyCode.KEYCODE_ENTER) &&
      event.type === KeyType.Down) {
      if (buttonOptions.action) {
        buttonOptions.action();
      }
      controller?.close();
      event.stopPropagation();
    }
  })
  .onClick(() => {
    if (buttonOptions.action) {
      buttonOptions.action();
    }
    controller?.close();
  })
  .defaultFocus(isDefaultFocus(buttonOptions, isHasDefaultFocus, isAllFocusFalse))
  .buttonStyle(buttonOptions.buttonStyle ??
    (buttonOptions.role === ButtonRole.ERROR ? ERROR_BUTTON_STYLE() : ALERT_BUTTON_STYLE()))
  .layoutWeight(BUTTON_LAYOUT_WEIGHT)
  .type(ButtonType.ROUNDED_RECTANGLE)
}

/**
 * is button set default focus
 *
 * @param singleButton button options
 * @param isHasDefaultFocus is button list has default focus button
 * @param isAllFocusFalse is all button in button list default focus false
 * @returns boolean
 */
function isDefaultFocus(singleButton: ButtonOptions, isHasDefaultFocus: boolean, isAllFocusFalse: boolean): boolean {
  try {
    // 当前按钮为默认按钮
    if (singleButton.defaultFocus) {
      return true;
    }
    let isDefaultFocus: boolean = false;
    if (isHasDefaultFocus || isAllFocusFalse) {
      isDefaultFocus = false; // 存在默认按钮或者所有按钮的defaultFocus都为false
    } else {
      isDefaultFocus = true; // 默认第一个按钮获焦
    }
    return isDefaultFocus;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `get defaultFocus exist error, code: ${code}, message: ${message}`);
    return true;
  }
}

/**
 * get resource size
 *
 * @param resourceId resource id
 * @param defaultValue default value
 * @returns resource size
 */
function getNumberByResourceId(resourceId: number, defaultValue: number, allowZero?: boolean): number {
  try {
    let sourceValue: number = resourceManager.getSystemResourceManager().getNumber(resourceId);
    if (sourceValue > 0 || allowZero) {
      return sourceValue;
    } else {
      return defaultValue;
    }
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `CustomContentDialog getNumberByResourceId error, code: ${code}, message: ${message}`);
    return defaultValue;
  }
}

/**
 * lazy init
 *
 * @param initializer  lazy initializer
 * @returns lazy init result
 */
function lazyInit<T>(initializer: () => T): () => T {
  let value: T | null = null;
  return () => {
    if (value === null) {
      value = initializer();
    }
    return value;
  };
}

/**
 * get LengthMetrics size
 *
 * @param resource resource
 * @param defaultValue default value
 * @param isAllowZero allow value zero
 * @returns LengthMetrics size
 */
function getLengthMetricsByResource(resource: Resource, defaultValue: number, isAllowZero?: boolean): number {
  if (!resource) {
    hilog.error(0x3900, 'Ace', 'CustomContentDialog getLengthMetricsByResource error');
    return defaultValue;
  }
  try {
    let sourceValue: number = LengthMetrics.resource(resource).value;
    if (sourceValue === 0) {
      return isAllowZero ? sourceValue : defaultValue;
    }
    return sourceValue;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace',
      `CustomContentDialog getLengthMetricsByResource error, code: ${code}, message: ${message}`);
    return defaultValue;
  }
}

/**
 * get string value
 *
 * @param resourceId Resource id
 * @returns resource value
 */
function getString(resourceId: number): string {
  let res = '';
  if (resourceId <= 0) {
    hilog.error(0x3900, 'Ace', 'CustomContentDialog getString error');
    return res;
  }
  try {
    res = getContext().resourceManager.getStringSync(resourceId);
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace',
      `CustomContentDialog getString error, code: ${code}, message: ${message}`);
  }
  return res;
}

/**
 * 获取SelectDialog无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getAccessibilityText(resource: ResourceStr, selected: boolean): string {
  try {
    let selectText: string = getContext().resourceManager.getStringSync(125833934);
    let resourceString: string = '';
    if (typeof resource === 'string') {
      resourceString = resource;
    } else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return selected ? `${selectText},${resourceString}` : resourceString;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}

/**
 * get Text Align
 *
 * @param maxWidth maxWidth
 * @param content textContent
 * @param fontSize fontSize
 * @returns textAlign
 */
function getTextAlign(maxWidth: number, content: ResourceStr, fontSize: number | string | Resource): TextAlign {
  let contentSize: SizeOptions = measure.measureTextSize({
    textContent: content,
    fontSize: fontSize,
    constraintWidth: maxWidth,
  });
  let oneLineSize: SizeOptions = measure.measureTextSize({
    textContent: content,
    fontSize: fontSize,
  });
  if (getTextHeight(contentSize) <= getTextHeight(oneLineSize)) {
    return TextAlign.Center;
  }
  return TextAlign.Start;
}

/**
 * get text height
 *
 * @param textSize textSize
 * @returns text height
 */
function getTextHeight(textSize: SizeOptions): number {
  if (textSize && textSize.height !== null && textSize.height !== undefined) {
    return Number(textSize.height);
  }
  return 0;
}

/**
 * resolve content area keyEvent
 *
 * @param event keyEvent
 * @param controller the controller of content area
 * @returns undefined
 */
function resolveKeyEvent(event: KeyEvent, controller: Scroller) {
  if (event.type === IGNORE_KEY_EVENT_TYPE) {
    return;
  }

  if (event.keyCode === KEYCODE_UP) {
    controller.scrollPage({ next: false });
    event.stopPropagation();
  } else if (event.keyCode === KEYCODE_DOWN) {
    if (controller.isAtEnd()) {
      return;
    } else {
      controller.scrollPage({ next: true });
      event.stopPropagation();
    }
  }
}

/**
 * 获取checkTips无障碍文本
 *
 * @param resource 资源
 * @param selected select state
 * @returns string
 */
function getCheckTipsAccessibilityText(resource: ResourceStr | null | undefined, selected?: boolean): string {
  try {
    // 'sys.string.slider_accessibility_selected'
    let selectText: string = getContext().resourceManager.getStringSync(125833934);
    // 'sys.string.slider_accessibility_unselected'
    let unselectText: string = getContext().resourceManager.getStringSync(125833935);
    // 'sys.string.advanced_dialog_accessibility_checkbox'
    let checkBoxText: string = getContext().resourceManager.getStringSync(125834354);
    let resourceString: string = '';
    if (typeof resource === 'string') {
      resourceString = resource
    } else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return selected ? `${selectText},${resourceString},${checkBoxText}` :
      `${unselectText},${resourceString},${checkBoxText}`;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getCheckTipsAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}

@CustomDialog
export struct LoadingDialog {
  controller: CustomDialogController;
  content?: ResourceStr = '';
  @State fontColorWithTheme: ResourceColor = $r('sys.color.font_primary');
  @State loadingProgressIconColorWithTheme: ResourceColor = $r('sys.color.icon_secondary');
  theme?: Theme | CustomTheme = new CustomThemeImpl({});
  themeColorMode?: ThemeColorMode = ThemeColorMode.SYSTEM;
  @State fontSizeScale: number = 1;
  @State minContentHeight: number = MIN_CONTENT_HEIGHT;

  build() {
    Column() {
      CustomDialogContentComponent({
        controller: this.controller,
        contentBuilder: () => {
          this.contentBuilder();
        },
        theme: this.theme,
        themeColorMode: this.themeColorMode,
        fontSizeScale: this.fontSizeScale,
        minContentHeight: this.minContentHeight,
      }).constraintSize({ maxHeight: '100%' });
    }
  }

  @Builder
  contentBuilder(): void {
    Column() {
      Row() {
        Text(this.content)
          .fontSize(`${BODY_L}fp`)
          .fontWeight(FontWeight.Regular)
          .fontColor(this.fontColorWithTheme)
          .layoutWeight(LOADING_TEXT_LAYOUT_WEIGHT)
          .maxLines(this.fontSizeScale > MAX_FONT_SCALE ? LOADING_MAX_LINES_BIG_FONT : LOADING_MAX_LINES)
          .focusable(true)
          .defaultFocus(true)
          .focusBox({
            strokeWidth: LengthMetrics.px(0)
          })
          .textOverflow({ overflow: TextOverflow.Ellipsis })
        LoadingProgress()
          .color(this.loadingProgressIconColorWithTheme)
          .width(LOADING_PROGRESS_WIDTH)
          .height(LOADING_PROGRESS_HEIGHT)
          .margin({ start: LengthMetrics.vp(LOADING_TEXT_MARGIN_LEFT) })
      }
      .constraintSize({ minHeight: LOADING_MIN_HEIGHT })
    }
  }

  aboutToAppear(): void {
    this.fontColorWithTheme = this.theme?.colors?.fontPrimary ?
    this.theme.colors.fontPrimary : $r('sys.color.font_primary');
    this.loadingProgressIconColorWithTheme = this.theme?.colors?.iconSecondary ?
    this.theme.colors.iconSecondary : $r('sys.color.icon_secondary');
  }
}

@Component
export struct PopoverDialog {
  @Link visible: boolean;
  @Prop popover: PopoverOptions;
  @BuilderParam targetBuilder: Callback<void>;
  @State dialogWidth: Dimension | undefined = this.popover?.width;

  @Builder
  emptyBuilder() {
  }

  aboutToAppear(): void {
    if (this.targetBuilder === undefined || this.targetBuilder === null) {
      this.targetBuilder = this.emptyBuilder;
    }
  }

  build() {
    Column() {
      this.targetBuilder();
    }
    .onClick(() => {
      try {
        let screenSize: display.Display = display.getDefaultDisplaySync();
        let screenWidth: number = px2vp(screenSize.width);
        if (screenWidth - BUTTON_HORIZONTAL_MARGIN - BUTTON_HORIZONTAL_MARGIN > MAX_DIALOG_WIDTH) {
          this.popover.width = this.popover?.width ?? MAX_DIALOG_WIDTH;
        } else {
          this.popover.width = this.dialogWidth;
        }
        this.visible = !this.visible;
      } catch (error) {
        let code: number = (error as BusinessError).code;
        let message: string = (error as BusinessError).message;
        hilog.error(0x3900, 'Ace', `dialog popup error, code: ${code}, message: ${message}`);
      }
    })
    .bindPopup(this.visible, {
      builder: this.popover?.builder,
      placement: this.popover?.placement ?? Placement.Bottom,
      popupColor: this.popover?.popupColor,
      enableArrow: this.popover?.enableArrow ?? true,
      autoCancel: this.popover?.autoCancel,
      onStateChange: this.popover?.onStateChange ?? ((e) => {
        if (!e.isVisible) {
          this.visible = false
        }
      }),
      arrowOffset: this.popover?.arrowOffset,
      showInSubWindow: this.popover?.showInSubWindow,
      mask: this.popover?.mask,
      targetSpace: this.popover?.targetSpace,
      offset: this.popover?.offset,
      width: this.popover?.width,
      arrowPointPosition: this.popover?.arrowPointPosition,
      arrowWidth: this.popover?.arrowWidth,
      arrowHeight: this.popover?.arrowHeight,
      radius: this.popover?.radius ?? $r('sys.float.corner_radius_level16'),
      shadow: this.popover?.shadow ?? ShadowStyle.OUTER_DEFAULT_MD,
      backgroundBlurStyle: this.popover?.backgroundBlurStyle ?? BlurStyle.COMPONENT_ULTRA_THICK,
      focusable: this.popover?.focusable,
      transition: this.popover?.transition,
      onWillDismiss: this.popover?.onWillDismiss
    })
  }
}

export declare interface PopoverOptions extends CustomPopupOptions {}