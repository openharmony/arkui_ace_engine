/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock, useEnabled } from 'common';

class MyDataSource implements IDataSource {
  private list: number[] = []

  constructor(list: number[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): number {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Component
export struct SwiperBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State vertical: boolean = false;
  @State enableVertical: boolean = false;
  @State autoPlay: boolean = false;
  @State enableAutoPlay: boolean = false;
  @State loop: boolean = false;
  @State enableLoop: boolean = false;
  @State isDot: boolean = true;
  @State enableIsDot: boolean = false;
  @State textWidth: number = 200;
  @State enableTextWidth: boolean = false;
  @State textHeight: number = 100;
  @State enableTextHeight: boolean = false;
  @State textAlign: TextAlign = TextAlign.Center;
  @State enableTextAlign: boolean = false;
  @State fontSize: number = 30;
  @State enableFontSize: boolean = false;
  @State displayCount: number = 1;
  @State enableDisplayCount: boolean = false;
  @State swipeByGroup: boolean = false;
  @State enableSwipeByGroup: boolean = false;
  @State displayArrow: boolean = false;
  @State enableDisplayArrow: boolean = false;
  private scrollerForScroll: Scroller = new Scroller();
  private swiperController: SwiperController = new SwiperController();
  private data: MyDataSource = new MyDataSource([]);

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 1; i <= 12; i++) {
      list.push(i);
    }
    this.data = new MyDataSource(list)
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Scroll(this.scrollerForScroll) {
      Column() {
        Swiper(this.swiperController) {
          LazyForEach(this.data, (item: string, index: number) => {
            Text(item.toString())
              .width(useEnabled(this.enableTextWidth, this.textWidth))
              .height(useEnabled(this.enableTextHeight, this.textHeight))
              .textAlign(useEnabled(this.enableTextAlign, this.textAlign, TextAlign.Center))
              .fontSize(useEnabled(this.enableFontSize, this.fontSize))
          }, (item: string) => item)
        }
        .displayCount(this.displayCount, this.swipeByGroup)
        .vertical(useEnabled(this.enableVertical, this.vertical))
        .autoPlay(useEnabled(this.enableAutoPlay, this.autoPlay))
        .indicator(this.isDot ? new DotIndicator() : Indicator.digit())
        .displayArrow(useEnabled(this.enableDisplayArrow, this.displayArrow))
        .loop(useEnabled(this.enableLoop, this.loop))
      }.width('100%').height('50%')
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '设置导航点指示器',
          isEnabled: this.enableIsDot,
          value: this.isDot,
          dataSource: [{ label: '圆点指示器', value: true }, { label: '数字指示器', value: false }]
        })

        RadioBlock({
          title: '是否开启循环',
          isEnabled: this.enableLoop,
          value: this.loop,
          dataSource: [{ label: '是', value: true }, { label: '否', value: false }]
        })

        RadioBlock({
          title: '是否纵向滑动',
          isEnabled: this.enableVertical,
          value: this.vertical,
          dataSource: [{ label: '是', value: true }, { label: '否', value: false }]
        })

        RadioBlock({
          title: '子组件是否自动播放',
          isEnabled: this.enableAutoPlay,
          value: this.autoPlay,
          dataSource: [{ label: '是', value: true }, { label: '否', value: false }]
        })

        SliderBlock({
          title: '设置Swiper视窗内元素显示个数',
          isEnabled: this.enableDisplayCount,
          value: this.displayCount,
          min: 1,
          max: 12
        })

        RadioBlock({
          title: '是否按组进行翻页',
          isEnabled: this.enableSwipeByGroup,
          value: this.swipeByGroup,
          dataSource: [{ label: '是', value: true }, { label: '否', value: false }]
        })

        RadioBlock({
          title: '是否显示导航点箭头',
          isEnabled: this.enableDisplayArrow,
          value: this.displayArrow,
          dataSource: [{ label: '是', value: true }, { label: '否', value: false }]
        })

        SliderBlock({
          title: '设置子组件宽度',
          isEnabled: this.enableTextWidth,
          value: this.textWidth,
          min: 0,
          max: 300
        })
        SliderBlock({
          title: '设置子组件高度',
          isEnabled: this.enableTextHeight,
          value: this.textHeight,
          min: 0,
          max: 300
        })

        RadioBlock({
          title: '设置文本段落在水平方向的对齐方式',
          isEnabled: this.enableTextAlign,
          value: this.textAlign,
          dataSource: [
            { label: '水平对齐首部', value: TextAlign.Start },
            { label: '水平居中对齐', value: TextAlign.Center },
            { label: '水平对齐尾部', value: TextAlign.End }]
        })

        SliderBlock({
          title: '设置字体大小',
          isEnabled: this.enableFontSize,
          value: this.fontSize,
          min: 0,
          max: 60
        })

      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct SwiperBootcampPreviewer {
  build() {
    SwiperBootcamp({ title: '轮播/Swiper' })
  }
}