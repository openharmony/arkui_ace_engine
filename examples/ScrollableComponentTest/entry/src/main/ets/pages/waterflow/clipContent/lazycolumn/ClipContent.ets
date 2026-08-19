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

// WaterFlow -> LazyColumnLayout (direct child) with clipContent.
// Verifies the WaterFlow clip extension covers the lazy child, while onScrollIndex (report range)
// and the lazy child's onVisibleIndexesChange are NOT polluted by the extension area.
import { LazyColumnLayout, LazyColumnLayoutAttribute, LengthMetrics, RectShape } from '@kit.ArkUI'
import { LazyNumberSource } from '../common/LazyDataSource'

@ComponentV2
export struct LazyColumnClipContentTest {
  @Local mode:boolean = true
  @Local clipContent: ContentClipMode | RectShape = ContentClipMode.SAFE_AREA;
  @Local modeString: string = 'M:SA';
  @Local scrollRange: string = 'idx:--';
  @Local visibleRange: string = 'vis:--';
  private source: LazyNumberSource = new LazyNumberSource(2000, 0);
  private scroller: Scroller = new Scroller();
  private reloaded: boolean = false;

  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Top }) {
        WaterFlow({ scroller: this.scroller,layoutMode:this.mode?0:1  }) {
          LazyColumnLayout() {
            LazyForEach(this.source, (item: number) => {
              Text('Item' + item.toString())
                .width('100%')
                .height(72)
                .borderRadius(12)
                .backgroundColor('#B0C0FF')
                .textAlign(TextAlign.Center)
            }, (item: number) => item.toString())
          }
          .space(LengthMetrics.vp(8))
          .onVisibleIndexesChange((start: number, end: number) => {
            this.visibleRange = `vis:${start}-${end}`;
            console.log(`FHF:LazyColumn:onVisibleIndexesChange:(${start}, ${end})`);
          })
        }
        .clipContent(this.clipContent)
        .cachedCount(0,true)
        .padding({ left: 12, right: 12 })
        .safeAreaPadding({ top: 50, bottom: 30 })
        .backgroundColor('#80FFD0B0')
        .onScrollIndex((start: number, end: number) => {
          this.scrollRange = `idx:${start}-${end}`;
          console.log(`FHF::onScrollIndex:(${start}, ${end})`);
        })

        Row() {
          Button(this.modeString).onClick(() => {
            this.switchMode();
          })
          Button(''+this.mode).onClick(() => {
            this.mode=!this.mode
          })
          Button('Reload').onClick(() => {
            this.reloaded = !this.reloaded;
            this.source.reload(30, this.reloaded ? 1000 : 0);
          })
          Text(this.scrollRange).fontSize(12)
          Text(this.visibleRange).fontSize(12)
        }.height(50).padding({ left: 12, right: 12 })
      }
      .background('#DCDCDC')
      .safeAreaPadding({ top: $r('sys.float.ohos_id_navigation_bar_height') })
    }.title('LazyColumnClipContent', {
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
