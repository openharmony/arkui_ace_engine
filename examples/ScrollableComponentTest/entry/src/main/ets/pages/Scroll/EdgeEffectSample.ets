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

@Entry
@Component
struct EdgeEffectSample {
  private items: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State edgeEffectName: string = 'Spring';

  private selectEdgeEffect(edgeEffect: EdgeEffect, name: string): void {
    this.edgeEffect = edgeEffect;
    this.edgeEffectName = name;
  }

  build() {
    Column({ space: 16 }) {
      Text('Edge Effect')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('当前边缘效果：' + this.edgeEffectName)
        .fontSize(16)

      Row({ space: 8 }) {
        Button('None')
          .onClick(() => {
            this.selectEdgeEffect(EdgeEffect.None, 'None');
          })
        Button('Spring')
          .onClick(() => {
            this.selectEdgeEffect(EdgeEffect.Spring, 'Spring');
          })
        Button('Fade')
          .onClick(() => {
            this.selectEdgeEffect(EdgeEffect.Fade, 'Fade');
          })
      }

      Scroll() {
        Column({ space: 12 }) {
          ForEach(this.items, (item: number) => {
            Text('滚动内容 ' + item)
              .width('100%')
              .height(96)
              .padding(16)
              .fontSize(18)
              .borderRadius(12)
              .backgroundColor(item % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
          }, (item: number) => item.toString())
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.Auto)
      .edgeEffect(this.edgeEffect)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
