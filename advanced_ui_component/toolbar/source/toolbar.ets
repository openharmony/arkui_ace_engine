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

import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node';
import { DividerModifier, SymbolGlyphModifier } from '@ohos.arkui.modifier';

export enum ItemState {
  ENABLE = 1,
  DISABLE = 2,
  ACTIVATE = 3,
}

const PUBLIC_MORE: Resource = $r('sys.media.ohos_ic_public_more');

interface MenuController {
  value: string;
  action: () => void;
  enabled?: boolean;
}

export interface ToolBarSymbolGlyphOptions {
  normal?: SymbolGlyphModifier;
  activated?: SymbolGlyphModifier;
}

@Observed
export class ToolBarOption {
  public content: string = '';
  public action?: () => void = undefined;
  public icon?: Resource = undefined;
  public state?: ItemState = 1;
  public iconColor?: ResourceColor = $r('sys.color.icon_primary');
  public activatedIconColor?: ResourceColor = $r('sys.color.icon_emphasize');
  public textColor?: ResourceColor = $r('sys.color.font_primary');
  public activatedTextColor?: ResourceColor = $r('sys.color.font_emphasize');
  public toolBarSymbolOptions?: ToolBarSymbolGlyphOptions = undefined;
}

@Observed
export class ToolBarOptions extends Array<ToolBarOption> {
}

export class ToolBarModifier implements AttributeModifier<ColumnAttribute> {
  public backgroundColorValue?: ResourceColor = $r('sys.color.ohos_id_color_toolbar_bg');
  public heightValue?: LengthMetrics = LengthMetrics.vp(56);
  public stateEffectValue?: boolean = true;
  public paddingValue?: LengthMetrics = LengthMetrics.vp(24);

  applyNormalAttribute(instance: ColumnAttribute):void {
    instance.backgroundColor(this.backgroundColorValue);
  }

  public backgroundColor(backgroundColor: ResourceColor): ToolBarModifier {
    this.backgroundColorValue = backgroundColor;
    return this;
  }

  public height(height: LengthMetrics): ToolBarModifier {
    this.heightValue = height;
    return this;
  }

  public stateEffect(stateEffect: boolean): ToolBarModifier {
    this.stateEffectValue = stateEffect;
    return this;
  }

  public padding(padding: LengthMetrics): ToolBarModifier {
    this.paddingValue = padding;
    return this;
  }
}

@Component
export struct ToolBar {
  @ObjectLink toolBarList: ToolBarOptions;
  controller: TabsController = new TabsController();
  @Prop activateIndex: number = -1;
  @Prop dividerModifier: DividerModifier = new DividerModifier();
  @Prop toolBarModifier: ToolBarModifier =
  new ToolBarModifier()
    .padding(LengthMetrics.vp(24))
    .stateEffect(true)
    .height(LengthMetrics.vp(56))
    .backgroundColor('sys.color.ohos_id_color_toolbar_bg');
  @Prop moreText: ResourceStr = $r('sys.string.ohos_toolbar_more');
  @State menuContent: MenuController[] = [];
  toolBarItemBackground: ResourceColor[] = [];
  @State itemBackground: ResourceColor = Color.Transparent;
  @State iconPrimaryColor: ResourceColor = $r('sys.color.icon_primary');
  @State iconActivePrimaryColor: ResourceColor = $r('sys.color.icon_emphasize');
  @State fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  @State fontActivatedPrimaryColor: ResourceColor = $r('sys.color.font_emphasize');
  @State symbolEffect: SymbolEffect = new SymbolEffect();

  onWillApplyTheme(theme: Theme) {
    this.iconPrimaryColor = theme.colors.iconPrimary;
    this.iconActivePrimaryColor = theme.colors.iconEmphasize;
    this.fontPrimaryColor = theme.colors.fontPrimary;
    this.fontActivatedPrimaryColor = theme.colors.fontEmphasize;
  }

  @Builder MoreTabBuilder(index: number) {
    Column() {
      Image(PUBLIC_MORE)
        .width(24)
        .height(24)
        .fillColor(this.iconPrimaryColor)
        .margin({ bottom: 2 })
        .objectFit(ImageFit.Contain)
        .draggable(false)
      Text(this.moreText)
        .fontColor(this.fontPrimaryColor)
        .fontSize($r('sys.float.ohos_id_text_size_caption'))
        .fontWeight(FontWeight.Medium)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .textAlign(TextAlign.Center)
    }.width('100%').height('100%')
    .justifyContent(FlexAlign.Center)
    .bindMenu(this.menuContent, { placement: Placement.TopRight, offset: { x: -12, y : -10 } })
    .padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.itemBackground)
    .onHover((isHover: boolean) => {
      if (isHover) {
        this.toolBarItemBackground[index] = $r('sys.color.ohos_id_color_hover');
      } else {
        this.toolBarItemBackground[index] = Color.Transparent;
      }
      this.itemBackground = this.toolBarItemBackground[index];
    })
    .stateStyles({
      pressed: {
        .backgroundColor((!this.toolBarModifier.stateEffectValue) ?
        this.toolBarItemBackground[index] : $r('sys.color.ohos_id_color_click_effect'))
      },
      normal: {
        .backgroundColor(this.toolBarItemBackground[index])
      }
    })
  }

  @Builder TabBuilder(index: number) {
    Column() {
      if (this.toolBarList[index]?.toolBarSymbolOptions?.normal ||
        this.toolBarList[index]?.toolBarSymbolOptions?.activated) {
        SymbolGlyph()
          .fontSize('24vp')
          .symbolEffect(this.symbolEffect, false)
          .attributeModifier(this.getToolBarSymbolModifier(index))
          .opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1)
          .margin({ bottom: 2 })
      } else {
        Image(this.toolBarList[index]?.icon)
          .width(24)
          .height(24)
          .fillColor(this.getIconColor(index))
          .opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1)
          .margin({ bottom: 2 })
          .objectFit(ImageFit.Contain)
          .draggable(false)
      }
      Text(this.toolBarList[index]?.content)
        .fontColor(this.getTextColor(index))
        .fontSize($r('sys.float.ohos_id_text_size_caption'))
        .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
        .minFontSize(9)
        .fontWeight(FontWeight.Medium)
        .maxLines(1)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1)
        .textAlign(TextAlign.Center)
    }
    .justifyContent(FlexAlign.Center)
    .width('100%').height('100%')
    .focusable(!(this.toolBarList[index]?.state === 2))
    .focusOnTouch(!(this.toolBarList[index]?.state === 2))
    .padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.itemBackground)
    .onClick(() => {
      let toolbar = this.toolBarList[index];
      if (toolbar.state === ItemState.ACTIVATE) {
        if (this.activateIndex === index) {
          this.activateIndex = -1;
        } else {
          this.activateIndex = index;
        }
      }
      if (!(toolbar.state === ItemState.DISABLE)) {
        toolbar.action && toolbar.action();
      }
    })
    .onHover((isHover: boolean) => {
      if (isHover) {
        this.toolBarItemBackground[index] = (this.toolBarList[index]?.state === ItemState.DISABLE)
          ? Color.Transparent : $r('sys.color.ohos_id_color_hover');
      } else {
        this.toolBarItemBackground[index] = Color.Transparent;
      }
      this.itemBackground = this.toolBarItemBackground[index];
    })
    .stateStyles({
      pressed: {
        .backgroundColor((this.toolBarList[index]?.state === ItemState.DISABLE) ||
          (!this.toolBarModifier.stateEffectValue) ?
        this.toolBarItemBackground[index] : $r('sys.color.ohos_id_color_click_effect'))
      },
      normal: {
        .backgroundColor(this.toolBarItemBackground[index])
      }
    })
  }

  private getToolBarSymbolModifier(index: number): SymbolGlyphModifier | undefined {
    if (this.activateIndex === index) {
      return this.toolBarList[index]?.toolBarSymbolOptions?.activated;
    }
    return this.toolBarList[index]?.toolBarSymbolOptions?.normal;
  }

  private getIconColor(index: number): ResourceColor {
    if (this.activateIndex === index && !(this.toolBarList[index]?.state === 2)) {
      return this.toolBarList[index]?.activatedIconColor ?? this.iconActivePrimaryColor;
    }
    return this.toolBarList[index]?.iconColor ?? this.iconPrimaryColor;
  }

  private getTextColor(index: number): ResourceColor {
    if (this.activateIndex === index && !(this.toolBarList[index]?.state === 2)) {
      return this.toolBarList[index]?.activatedTextColor ?? this.fontActivatedPrimaryColor;
    }
    return this.toolBarList[index]?.textColor ?? this.fontPrimaryColor;
  }

  private toLengthString(value: LengthMetrics | undefined): string {
    if (value === void (0)) {
      return '';
    }
    const length: number = value.value;
    let lengthString: string = '';
    switch (value.unit) {
      case LengthUnit.PX:
        lengthString = `${length}px`;
        break;
      case LengthUnit.FP:
        lengthString = `${length}fp`;
        break;
      case LengthUnit.LPX:
        lengthString = `${length}lpx`;
        break;
      case LengthUnit.PERCENT:
        lengthString = `${length * 100}%`;
        break;
      case LengthUnit.VP:
        lengthString = `${length}vp`;
        break;
      default:
        lengthString = `${length}vp`;
        break;
    }
    return lengthString;
  }

  refreshData() {
    this.menuContent = [];
    for (let i = 0; i < this.toolBarList.length; i++) {
      if (i >= 4 && this.toolBarList.length > 5) {
        this.menuContent[i - 4] = {
          value: this.toolBarList[i].content,
          action: this.toolBarList[i].action as () => void,
          enabled: this.toolBarList[i].state !== ItemState.DISABLE,
        }
      } else {
        this.toolBarItemBackground[i] = Color.Transparent;
        this.menuContent = [];
      }
    }
    return true;
  }

  aboutToAppear() {
    this.refreshData();
  }
  build() {
    Column() {
      Divider()
        .width('100%').height(1)
        .attributeModifier(this.dividerModifier)
      Column() {
        Tabs({ barPosition: BarPosition.End, controller: this.controller}) {
          ForEach(this.toolBarList, (item: ToolBarOption, index: number) => {
            if (this.toolBarList.length <= 5) {
              TabContent() {
              }.tabBar(this.TabBuilder(index))
              .enabled(!(this.toolBarList[index]?.state === 2))
              .focusOnTouch(!(this.toolBarList[index]?.state === 2))
            } else if (index < 4){
              TabContent() {
              }.tabBar(this.TabBuilder(index))
              .enabled(!(this.toolBarList[index]?.state === 2))
              .focusOnTouch(!(this.toolBarList[index]?.state === 2))
            }
          })
          if (this.refreshData() && this.toolBarList.length > 5) {
            TabContent() {
            }.tabBar(this.MoreTabBuilder(4))
          }
        }
        .vertical(false)
        .constraintSize({
          minHeight: this.toLengthString(this.toolBarModifier.heightValue),
          maxHeight: this.toLengthString(this.toolBarModifier.heightValue),
        })
        .barHeight(this.toLengthString(this.toolBarModifier.heightValue))
        .barMode(BarMode.Fixed)
        .onChange((index: number) => {
        })
        .width('100%')
        .height(this.toLengthString(this.toolBarModifier.heightValue))
        .padding({
          start: this.toolBarList.length < 5 ? this.toolBarModifier.paddingValue : LengthMetrics.vp(0),
          end: this.toolBarList.length < 5 ? this.toolBarModifier.paddingValue : LengthMetrics.vp(0),
        })
      }
      .justifyContent(FlexAlign.Center)
      .width('100%')
    }
    .attributeModifier(this.toolBarModifier)
  }
}