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
import { LengthMetrics } from '@ohos.arkui.node';

export enum ItemState {
  ENABLE = 1,
  DISABLE = 2,
  ACTIVATE = 3,
}

const PUBLIC_MORE: Resource = $r('sys.media.ohos_ic_public_more');

interface MenuController {
  value: string;
  action: () => void;
}

@Observed
export class ToolBarOption {
  public content: string = '';
  public action?: () => void = undefined;
  public icon?: Resource = undefined;
  public state?: ItemState = 1;
}

@Observed
export class ToolBarOptions extends Array<ToolBarOption> {
}

@Component
export struct ToolBar {
  @ObjectLink toolBarList: ToolBarOptions
  controller: TabsController = new TabsController();
  @Prop activateIndex: number = -1
  @Prop moreText: string = "更多"
  @State menuContent: MenuController[] = [];
  toolBarItemBackground: Resource[] = []
  @State itemBackground: Resource = $r('sys.color.ohos_id_color_toolbar_bg')
  @State iconPrimaryColor: ResourceColor = $r('sys.color.icon_primary');
  @State iconActivePrimaryColor: ResourceColor = $r('sys.color.icon_emphasize');
  @State fontPrimaryColor: ResourceColor = $r('sys.color.font_primary');
  @State fontActivatedPrimaryColor: ResourceColor = $r('sys.color.font_emphasize');

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
        .margin({ top: 8, bottom: 2 })
        .objectFit(ImageFit.Contain)
        .bindMenu(this.menuContent, { offset: { x: 5, y : -10 } })
      Text(this.moreText)
        .fontColor(this.fontPrimaryColor)
        .fontSize($r('sys.float.ohos_id_text_size_caption'))
        .fontWeight(FontWeight.Medium)
    }.width('100%').height('100%')
    .padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
  }

  @Builder TabBuilder(index: number) {
    Column() {
      Image(this.toolBarList[index]?.icon)
        .width(24)
        .height(24)
        .fillColor(this.activateIndex === index && !(this.toolBarList[index]?.state === 2)
          ? this.iconActivePrimaryColor : this.iconPrimaryColor)
        .opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1)
        .margin({ top: 8, bottom: 2 })
        .objectFit(ImageFit.Contain)
      Text(this.toolBarList[index]?.content)
        .fontColor(this.activateIndex === index && !(this.toolBarList[index]?.state === 2)
          ? this.fontActivatedPrimaryColor : this.fontPrimaryColor)
        .fontSize($r('sys.float.ohos_id_text_size_caption'))
        .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
        .minFontSize(9)
        .fontWeight(FontWeight.Medium)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .opacity((this.toolBarList[index]?.state === 2) ? 0.4 : 1)
    }
    .width('100%').height('100%')
    .focusable(!(this.toolBarList[index]?.state === 2))
    .focusOnTouch(!(this.toolBarList[index]?.state === 2))
    .padding({ start: LengthMetrics.vp(4), end: LengthMetrics.vp(4) })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.itemBackground)
    .onClick(() => {
      let toolbar = this.toolBarList[index];
      if (toolbar.state === ItemState.ACTIVATE) {
        if (this.activateIndex === index)
          this.activateIndex = -1;
        else {
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
          ? $r('sys.color.ohos_id_color_toolbar_bg') : $r('sys.color.ohos_id_color_hover')
      } else {
        this.toolBarItemBackground[index] = $r('sys.color.ohos_id_color_toolbar_bg')
      }
      this.itemBackground = this.toolBarItemBackground[index]
    })
    .stateStyles({
      pressed: {
        .backgroundColor((this.toolBarList[index]?.state === ItemState.DISABLE) ?
        this.toolBarItemBackground[index] : $r('sys.color.ohos_id_color_click_effect'))
      },
      normal: {
        .backgroundColor(this.toolBarItemBackground[index])
      }
    })
  }

  refreshData() {
    this.menuContent = []
    for (let i = 0; i < this.toolBarList.length; i++) {
      if (i >= 4 && this.toolBarList.length > 5) {
        this.menuContent[i - 4] = {
          value: this.toolBarList[i].content,
          action: this.toolBarList[i].action as () => void,
        }
      } else {
        this.toolBarItemBackground[i] = $r('sys.color.ohos_id_color_toolbar_bg')
        this.menuContent = []
      }
    }
    return true
  }

  aboutToAppear() {
    this.refreshData()
  }
  build() {
    Column() {
      Divider().width('100%').height(1)
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
        .constraintSize({ minHeight: 56, maxHeight: 56})
        .barMode(BarMode.Fixed)
        .onChange((index: number) => {
        })
        .width('100%')
        .padding({
          start: LengthMetrics.vp(this.toolBarList.length < 5 ? 24 : 0),
          end: LengthMetrics.vp(this.toolBarList.length < 5 ? 24 : 0)
        })
        .backgroundColor($r('sys.color.ohos_id_color_toolbar_bg'))
      }.width('100%')
    }
  }
}