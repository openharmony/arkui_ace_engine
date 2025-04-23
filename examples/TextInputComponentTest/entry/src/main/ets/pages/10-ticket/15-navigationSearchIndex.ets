/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

export enum SearchState {
  ENTRY = 'entry',
  ASSOCIATION = 'association',
  SEARCH = 'result',
  AFTER = 'after',
}

@Component
export struct SearchIndex {
  @Consume('pageInfos') pageInfos: NavPathStack;
  @State currentKeyword: string = ''

  @Builder
  navigationBuilder() {
    Column() {
      Image($r('app.media.startIcon'))
        .id('searchFrameBack')
        .fillColor($r('sys.color.ohos_id_color_titlebar_icon'))
        .width(24)
        .height(24)
        .focusable(false)
    }
    .focusable(false)
    .margin({ left: -12, right: 4 })
    .height(48)
    .width(48)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .onClick(() => {
      this.onBack();
    })
  }

  @Builder
  inputBuilder() {
    Column() {
      Stack({ alignContent: Alignment.Center }) {
        Search({
          value: this.currentKeyword,
          placeholder: '搜索...'
        })
          .id('searchFrameInput')
          .defaultFocus(true)
          .height(40)
          .width('100%')
          .backgroundColor($r('sys.color.ohos_id_color_text_field_bg'))
          .searchIcon({ color: $r('sys.color.ohos_id_color_secondary') })
          .searchButton('搜索', {
            fontColor: $r('sys.color.ohos_id_color_text_hyperlink'), fontSize: 16
          })
          .textFont({ size: $r('sys.float.ohos_id_text_size_body1') })
          .placeholderColor($r('sys.color.ohos_id_color_secondary'))
          .caretStyle({
            color: $r('sys.color.ohos_id_color_text_primary_activated')
          })
          .fontColor($r('sys.color.ohos_id_color_text_primary'))
          .cancelButton({
            icon: {
              color: $r('sys.color.ohos_id_color_secondary')
            }
          })
          .geometryTransition('transitionId123')
          .height(40)
          .zIndex(1)

        Text()
          .focusable(true)
          .id('hideText')
          .height(40)
          .zIndex(0)
      }
      .height(56)
    }
    .layoutWeight(1)
  }

  aboutToAppear() {
  }

  onBack() {
    animateTo({
      duration: 1000
    }, () => {
      this.pageInfos.pop()
    })
  }

  build() {
    NavDestination() {
      Stack() {
        Column() {
          Row() {
            this.navigationBuilder();
            this.inputBuilder();
          }
          .alignItems(VerticalAlign.Center)
          .justifyContent(FlexAlign.Start)
          .height(56)
          .margin({
            left: 16, right: 16
          })
          .zIndex(999)
        }.backgroundColor('#fff5f1f3')
      }.transition(TransitionEffect.OPACITY)
    }
    .hideTitleBar(true)
    .onBackPressed(() => {
      this.onBack()
      return true
    })
    .backgroundColor(Color.Transparent)
  }
}