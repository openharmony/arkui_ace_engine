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
 
export enum ItemState {
  ENABLE = 1,
  DISABLE = 2,
  ACTIVATE = 3
}

const PUBLIC_MORE = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAGAAAABgCAYAAADimHc4AAAAIGNIUk0AAHomAACAhAAA" +
  "+gAAAIDoAAB1MAAA6mAAADqYAAAXcJy6UTwAAAAEZ0FNQQAAsY58+1GTAAAAAXNSR0IArs4c6QAAAAZiS0dEAP8A/wD/oL2nkwAAAAlwSFlzA" +
  "AAOxAAADsQBlSsOGwAAAYFJREFUeNrt3CFLQ1EUB/CpCwYRo8G4j2IwCNrUYjH4AfwcfgBBwWZRMNgtFqPdILJgEhGDweAZvDjmJnfv3I" +
  "3fD/5l3DfOfWdv23vhdDoAAAAAAAAwzxam9L5rkePIdmSjee05chu5iHxXej5ar3saDdiJXDabGaYfOYg8VHbyU+peKryJvch1ZHnEmtXIY" +
  "eQ+8lrJyU+re7HgJtYj52Ou7Uau/thwW1LrLtmAk8jKBOsH37FHFTQgte6SDdht6ZjSUusu2YBeS8eUllr3YvLmuzP6971bYwP6/zjmpYKT" +
  "mVp3yQbctXRMaal1l2zAaeRngvUfkbMKGpBad8kbsffIZ2RrzPX7kacKGpBad+k74cfmE7I54ur6au4obyr6UU2re1oP43rNDc6wh1qDS/6t0" +
  "n83s1o3AAAAAAAAAAAAAEAysyKS6zYrIrlusyKS6zYrwqyIdGZFJDMrIplZETPIrIh5qdusCLMi0pkVkcysiAqYFVEJsyIAAAAAAAAAKOYXUlF" +
  "8EUcdfbsAAAAASUVORK5CYII=";

@Observed
export class ToolBarOption {
  content: string;
  action?: () => void;
  icon?: Resource;
  state?: ItemState = 1;
}

@Observed
export class ToolBarOptions extends Array<ToolBarOption> {
}

@Component
export struct ToolBar {
  @ObjectLink toolBarList: ToolBarOptions
  controller: TabsController
  @Prop activateIndex: number = -1
  @Prop moreText: string = "更多"
  @State menuContent: { value: string, action: () => void }[] = []
  toolBarItemBackground: Resource[] = []
  @State itemBackground: Resource = $r('sys.color.ohos_id_color_toolbar_bg')
  @Builder MoreTabBuilder(index: number) {
    Column() {
      Image(PUBLIC_MORE)
        .width(24)
        .height(24)
        .fillColor($r('sys.color.ohos_id_color_toolbar_icon'))
        .margin({ top: 8, bottom: 2 })
        .objectFit(ImageFit.Contain)
      Text(this.moreText)
        .fontColor($r('sys.color.ohos_id_color_toolbar_text'))
        .fontSize($r('sys.float.ohos_id_text_size_caption'))
        .fontWeight(FontWeight.Medium)
    }.width('100%').height('100%').bindMenu(this.menuContent, { offset: { x: 5, y : -10}})
    .padding({left: 4, right: 4})
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
  }

  @Builder TabBuilder(index: number) {
    Column() {
      Image(this.toolBarList[index].icon)
        .width(24)
        .height(24)
        .fillColor(this.activateIndex === index && !(this.toolBarList[index].state === 2)
          ? $r('sys.color.ohos_id_color_text_primary_activated') : $r('sys.color.ohos_id_color_primary'))
        .opacity((this.toolBarList[index].state === 2) ? 0.4 : 1)
        .margin({ top: 8, bottom: 2 })
        .objectFit(ImageFit.Contain)
      Text(this.toolBarList[index].content)
        .fontColor(this.activateIndex === index && !(this.toolBarList[index].state === 2)
          ? $r('sys.color.ohos_id_color_toolbar_text_actived') : $r('sys.color.ohos_id_color_toolbar_text'))
        .fontSize($r('sys.float.ohos_id_text_size_caption'))
        .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
        .minFontSize(9)
        .fontWeight(FontWeight.Medium)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .opacity((this.toolBarList[index].state === 2) ? 0.4 : 1)
    }
    .width('100%').height('100%')
    .focusable(!(this.toolBarList[index].state === 2))
    .focusOnTouch(!(this.toolBarList[index].state === 2))
    .padding({left: 4, right: 4})
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.itemBackground)
    .onClick(() => {
      if (this.toolBarList[index].state === 3) {
        if (this.activateIndex === index)
          this.activateIndex = -1
        else {
          this.activateIndex = index
        }
      }
      if (!(this.toolBarList[index].state === 2)) {
        this.toolBarList[index].action && this.toolBarList[index].action()
      }
    })
    .onHover((isHover: boolean) => {
      if (isHover ) {
        this.toolBarItemBackground[index] = (this.toolBarList[index].state === 2)
          ? $r('sys.color.ohos_id_color_toolbar_bg'): $r('sys.color.ohos_id_color_hover')
      } else {
        this.toolBarItemBackground[index] = $r('sys.color.ohos_id_color_toolbar_bg')
      }
      this.itemBackground = this.toolBarItemBackground[index]
    })
    .stateStyles({
      pressed: {
        .backgroundColor((this.toolBarList[index].state === 2) ? this.toolBarItemBackground[index] : $r('sys.color.ohos_id_color_click_effect'))
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
          action: this.toolBarList[i].action
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
              .enabled(!(this.toolBarList[index].state === 2))
              .focusOnTouch(!(this.toolBarList[index].state === 2))
            } else if (index < 4){
              TabContent() {
              }.tabBar(this.TabBuilder(index))
              .enabled(!(this.toolBarList[index].state === 2))
              .focusOnTouch(!(this.toolBarList[index].state === 2))
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
        .padding({ left: this.toolBarList.length < 5? 24 : 0, right: this.toolBarList.length < 5? 24 : 0})
        .backgroundColor($r('sys.color.ohos_id_color_toolbar_bg'))
      }.width('100%')
    }
  }
}