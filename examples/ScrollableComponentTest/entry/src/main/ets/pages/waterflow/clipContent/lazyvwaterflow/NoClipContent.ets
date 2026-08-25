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

// Baseline: WaterFlow -> LazyVWaterFlowLayout WITHOUT clipContent.
import { LazyVWaterFlowLayout, LazyVWaterFlowLayoutAttribute, LengthMetrics } from '@kit.ArkUI'
import { LazyNumberSource } from '../common/LazyDataSource'

@ComponentV2
export struct LazyVWaterFlowNoClipContentTest {
  @Local scrollRange: string = 'idx:--';
  @Local visibleRange: string = 'vis:--';
  private source: LazyNumberSource = new LazyNumberSource(40, 0);
  private scroller: Scroller = new Scroller();
  private reloaded: boolean = false;

  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Top }) {
        WaterFlow({ scroller: this.scroller }) {
          LazyVWaterFlowLayout() {
            LazyForEach(this.source, (item: number) => {
              Text('Item' + item.toString())
                .width('100%')
                .height(72 + (item % 3) * 24)
                .borderRadius(12)
                .backgroundColor('#B0C0FF')
                .textAlign(TextAlign.Center)
            }, (item: number) => item.toString())
          }
          .columnsTemplate('1fr 1fr')
          .columnsGap(LengthMetrics.vp(8))
          .rowsGap(LengthMetrics.vp(8))
          .onVisibleIndexesChange((start: number, end: number) => {
            this.visibleRange = `vis:${start}-${end}`;
            console.log(`FHF:LazyVWaterFlow:onVisibleIndexesChange:(${start}, ${end})`);
          })
        }
        .padding({ left: 12, right: 12 })
        .safeAreaPadding({ top: 50, bottom: 30 })
        .backgroundColor('#80FFD0B0')
        .onScrollIndex((start: number, end: number) => {
          this.scrollRange = `idx:${start}-${end}`;
          console.log(`FHF::onScrollIndex:(${start}, ${end})`);
        })

        Row({ space: 6 }) {
          Button('Reload').onClick(() => {
            this.reloaded = !this.reloaded;
            this.source.reload(40, this.reloaded ? 1000 : 0);
          })
          Button('jump10').onClick(() => {
            this.scroller.scrollToIndex(10);
          })
          Text(this.scrollRange).fontSize(12)
          Text(this.visibleRange).fontSize(12)
        }.height(50).padding({ left: 12, right: 12 })
      }
      .background('#DCDCDC')
      .safeAreaPadding({ top: $r('sys.float.ohos_id_navigation_bar_height') })
    }.title('LazyVWaterFlowNoClipContent', {
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
      barStyle: BarStyle.STACK,
    })
  }
}
