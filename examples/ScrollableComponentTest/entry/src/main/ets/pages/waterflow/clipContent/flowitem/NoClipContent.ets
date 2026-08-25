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

// Baseline: WaterFlow + FlowItem WITHOUT clipContent. Compare against flowitem/ClipContent.ets:
// here content is clipped at the content edge (no extension into padding / safe area).
import { LazyNumberSource } from '../common/LazyDataSource'

@ComponentV2
export struct FlowItemNoClipContentTest {
  @Local scrollRange: string = 'idx:--';
  private source: LazyNumberSource = new LazyNumberSource(40, 0);
  private scroller: Scroller = new Scroller();
  private reloaded: boolean = false;

  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Top }) {
        WaterFlow({ scroller: this.scroller }) {
          LazyForEach(this.source, (item: number) => {
            FlowItem() {
              Text('Item' + item.toString())
                .textAlign(TextAlign.Center)
            }
            .width('100%')
            .height(72)
            .borderRadius(12)
            .backgroundColor('#B0C0FF')
          }, (item: number) => item.toString())
        }
        .columnsTemplate('1fr 1fr')
        .columnsGap(8)
        .rowsGap(8)
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
        }.height(50).padding({ left: 12, right: 12 })
      }
      .background('#DCDCDC')
      .safeAreaPadding({ top: $r('sys.float.ohos_id_navigation_bar_height') })
    }.title('FlowItemNoClipContent', {
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
      barStyle: BarStyle.STACK,
    })
  }
}
