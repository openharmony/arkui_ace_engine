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

import { ImageGenerateState } from '../types/Declaration'

@Extend(Text)
function iconFontStyle() {
  .fontFamily("HarmonyHeiTi")
  .fontColor("#000000")
  .fontSize(10)
  .fontWeight(400)
  .lineHeight(12)
  .textAlign(TextAlign.Center)
}

@ComponentV2
export struct ContinueOperateArea  {
  @Param currentGenerateState: ImageGenerateState | undefined = undefined;
  @Event changeGenerateState: (state: ImageGenerateState) => void = (state: ImageGenerateState) => {};
  private limit: boolean = false;

  build() {
    Column() {
      Row() {
        Column() {
          Image($r('sys.media.reset_light'))
            .width(24)
            .height(24)
            .opacity(this.limit ? 0.3 : 1)
            .margin({
              bottom: 4
            })
          Text('重新编辑')
            .iconFontStyle()
            .fontColor(this.limit ? "#808080" : "#000000")
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.creat_light'))
            .width(24)
            .height(24)
            .opacity(this.limit ? 0.3 : 1)
            .margin({
              bottom: 4
            })
          Text('继续创作')
            .iconFontStyle()
            .fontColor(this.limit ? "#808080" : "#000000")
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.download_light'))
            .width(24)
            .height(24)
            .margin({
              bottom: 4
            })
          Text('下载')
            .iconFontStyle()
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.stickers_light'))
            .width(24)
            .height(24)
            .margin({
              bottom: 4
            })
          Text('添加至贴纸')
            .iconFontStyle()
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })

        Column() {
          Image($r('sys.media.add_to_text_light'))
            .width(24)
            .height(24)
            .margin({
              bottom: 4
            })
          Text('插入笔记')
            .iconFontStyle()
        }
        .width(123)
        .height(42)
        .alignItems(HorizontalAlign.Center)
        .onClick(() => {
        })
      }
      .justifyContent(FlexAlign.SpaceBetween)
      .width(618)
      .height(58)
      .margin({
        top: 18
      })
    }.width('100%')
  }
}

@ComponentV2
export struct HistoryArea {
  @Param resultList: string[] = [];
  private selectIndex: number = 0;

  build() {
    Column() {
      Scroll() {
        Column({ space: 12 }) {
          ForEach(this.resultList, (item: string, index: number) => {
            Column() {
              Image(item)
                .id('resultImage' + index)
                .width(56)
                .height(56)
                .borderRadius(10)
            }
            .width(60)
            .height(60)
            .padding(2)
            .borderRadius(11)
            .clip(true)
            .linearGradient(this.selectIndex == index ? {
              angle: 90,
              direction: GradientDirection.Left,
              colors: [['#44D1FF', 0.0], ['#A479FF', 0.52], ['#FF678C', 1.0]],
            } : undefined)
            .onClick(() => {
              this.selectIndex = index;
            })
          })
        }
        .width(79)
      }
      .scrollBar(BarState.Off)
      .scrollable(ScrollDirection.Vertical)
      .width(79)
      .height(386)
    }.width('100%')
  }
}