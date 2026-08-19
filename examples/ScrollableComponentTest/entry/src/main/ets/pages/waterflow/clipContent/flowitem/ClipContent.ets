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

// WaterFlow + FlowItem with clipContent.
// NOTE: a WaterFlow with plain FlowItems needs columnsTemplate, enough items to scroll, and a bound
// scroller; otherwise the clip extension has no scrolled-in content to show and looks like a no-op.
import { RectShape } from '@kit.ArkUI';
import { LazyNumberSource } from '../common/LazyDataSource'

@ComponentV2
export struct FlowItemClipContentTest {
  @Local clipContent: ContentClipMode | RectShape = ContentClipMode.SAFE_AREA;
  @Local modeString: string = 'M:SA';
  @Local lanes: string = '1fr 1fr';
  @Local scrollRange: string = 'idx:--';
  @Local mode:boolean = true
  private source: LazyNumberSource = new LazyNumberSource(80, 0);
  private scroller: Scroller = new Scroller();

  build() {
    NavDestination() {
      Stack({ alignContent: Alignment.Top }) {
        WaterFlow({ scroller: this.scroller,layoutMode:this.mode?0:1 }) {
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
        .columnsTemplate(this.lanes)
        .columnsGap(8)
        .rowsGap(8)
        .clipContent(this.clipContent)
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
          Button('Bottom').onClick(() => {
            this.scroller.scrollEdge(Edge.Bottom)
          })
          Button('jump10').onClick(() => {
            this.scroller.scrollToIndex(10);
          })
          Text(this.scrollRange).fontSize(12)
        }.height(50)
      }
      .background('#DCDCDC')
      .safeAreaPadding({ top: $r('sys.float.ohos_id_navigation_bar_height') })
    }.title('FlowItemClipContent', {
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
