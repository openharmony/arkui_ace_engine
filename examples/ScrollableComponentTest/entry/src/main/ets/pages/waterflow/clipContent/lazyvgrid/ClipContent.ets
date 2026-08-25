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

// WaterFlow -> FlowItem -> LazyVGridLayout with clipContent.
// LazyVGridLayout is a global builtin (no component import). Its only allowed parents are
// WaterFlow / FlowItem, and a bare `WaterFlow(){ LazyVGridLayout() }` renders EMPTY, so the
// FlowItem wrapper is required.
import { LengthMetrics, RectShape } from '@kit.ArkUI'
import { LazyNumberSource } from '../common/LazyDataSource'

@ComponentV2
export struct LazyVGridClipContentTest {
  @Local clipContent: ContentClipMode | RectShape = ContentClipMode.SAFE_AREA;
  @Local modeString: string = 'M:SA';
  @Local scrollRange: string = 'idx:--';
  private source: LazyNumberSource = new LazyNumberSource(40, 0);
  private scroller: Scroller = new Scroller();
  private reloaded: boolean = false;

  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Top }) {
        WaterFlow({ scroller: this.scroller }) {
          FlowItem() {
            LazyVGridLayout() {
              LazyForEach(this.source, (item: number) => {
                Text('Item' + item.toString())
                  .width('100%')
                  .height(72)
                  .borderRadius(12)
                  .backgroundColor('#B0C0FF')
                  .textAlign(TextAlign.Center)
              }, (item: number) => item.toString())
            }
            .columnsTemplate('1fr 1fr 1fr')
            .columnsGap(LengthMetrics.vp(8))
            .rowsGap(LengthMetrics.vp(8))
          }.width('100%')
        }
        .clipContent(this.clipContent)
        .padding({ left: 12, right: 12 })
        .safeAreaPadding({ top: 50, bottom: 30 })
        .backgroundColor('#80FFD0B0')
        .onScrollIndex((start: number, end: number) => {
          this.scrollRange = `idx:${start}-${end}`;
          console.log(`FHF::onScrollIndex:(${start}, ${end})`);
        })

        Row({ space: 6 }) {
          Button(this.modeString).onClick(() => {
            this.switchMode();
          })
          Button('Reload').onClick(() => {
            this.reloaded = !this.reloaded;
            this.source.reload(40, this.reloaded ? 1000 : 0);
          })
          Button('jump0').onClick(() => {
            this.scroller.scrollToIndex(0);
          })
          Text(this.scrollRange).fontSize(12)
        }.height(50).padding({ left: 12, right: 12 })
      }
      .background('#DCDCDC')
      .safeAreaPadding({ top: $r('sys.float.ohos_id_navigation_bar_height') })
    }.title('LazyVGridClipContent', {
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
      barStyle: BarStyle.STACK,
    })
  }

  // Cycle: SAFE_AREA -> BOUNDARY -> CUSTOM(RectShape) -> CONTENT_ONLY -> SAFE_AREA
  private switchMode(): void {
    if (this.clipContent === ContentClipMode.SAFE_AREA) {
      this.clipContent = ContentClipMode.BOUNDARY;
      this.modeString = 'M:BD';
    } else if (this.clipContent === ContentClipMode.BOUNDARY) {
      this.clipContent = new RectShape().size({ width: '100%', height: '150%' }).offset({ x: 0, y: '-25%' });
      this.modeString = 'M:CT';
    } else if (this.clipContent === ContentClipMode.CONTENT_ONLY) {
      this.clipContent = ContentClipMode.SAFE_AREA;
      this.modeString = 'M:SA';
    } else {
      this.clipContent = ContentClipMode.CONTENT_ONLY;
      this.modeString = 'M:CO';
    }
  }
}
