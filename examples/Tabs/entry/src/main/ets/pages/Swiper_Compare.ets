/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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

// xxx.ets

import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import { text } from '@kit.ArkGraphics2D';
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';

class MyDataSource implements IDataSource {
  private list: number[] = [];

  constructor(list: number[]) {
    this.list = list;
  }

  totalCount(): number {
    return this.list.length;
  }

  getData(index: number): number {
    return this.list[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct TabsSwiperExample {
  @State fontColor: string = '#182431';
  @State selectedFontColor: string = '#007DFF';
  private list: number[] = [];
  private controller: TabsController = new TabsController();
  private swiperController: SwiperController = new SwiperController();
  private swiperData: MyDataSource = new MyDataSource([]);

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  @State isOnContentDidScroll: Array<OnTabsContentDidScrollCallback | undefined> = [
    ((selectedIndex: number, index: number, position: number, mainAxisLength: number) => {
      // 监听Swiper页面滑动事件，在该回调中可以实现自定义导航点切换动画等
      console.info("ygl onContentDidScroll selectedIndex: " + selectedIndex + ", index: " + index +
        ", position: " + position + ", mainAxisLength: " + mainAxisLength);
    }),
    undefined]
  @State isOnContentDidScrollIndex: number = 0
  @State selfFadingFade: boolean = true;
  @State isVertical: boolean[] = [true, false]
  @State isVerticalIndex: number = 0
  @State disableSwipe: boolean[] = [false, true]
  @State disableSwipeIndex: number = 0
  @State text: string = ''
  // @State isAnimationMode:AnimationMode[] =
  //   [
  //     SwiperAnimationMode.NO_ANIMATION,
  //     SwiperAnimationMode.DEFAULT_ANIMATION,
  //     SwiperAnimationMode.FAST_ANIMATION,
  //     AnimationMode.CONTENT_FIRST_WITH_JUMP,
  //     AnimationMode.ACTION_FIRST_WITH_JUMP
  //   ]
  // @State isAnimationModeIndex:number = 0
  @State isPageFlipMode: PageFlipMode[] = [PageFlipMode.CONTINUOUS, PageFlipMode.SINGLE]
  @State isPageFlipModeIndex: number = 0
  @State clickedContent: string = ''
  @State onAnimationStart: string = ''
  @State onAnimationEnd: string = ''
  @State onGestureSwipe: string = ''
  @State onUnselected: number = 0
  @State selectedIndex: number = 0
  @State currentIndex: number = 0;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext
  @State duration: number[] = [600,0]
  @State durationIndex: number = 0

  aboutToAppear(): void {
    for (let i = 0; i <= 9; i++) {
      this.list.push(i);
    }
    this.swiperData = new MyDataSource(this.list);
  }

  @Builder
  tabBuilder(index: number, name: string) {
    Column() {
      Text(name)
        .fontColor(this.currentIndex === index ? this.selectedFontColor : this.fontColor)
        .fontSize(16)
        .fontWeight(this.currentIndex === index ? 500 : 400)
        .lineHeight(22)
        .margin({ top: 17, bottom: 7 })
      Divider()
        .strokeWidth(2)
        .color('#007DFF')
        .opacity(this.currentIndex === index ? 1 : 0)
    }.width('20%')
  }

  build() {
    Column() {
      Row() {
        Button("切换模式：浅色").width('45%').margin({ bottom: '12vp' })
          .onClick(() => {
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT);
          })
        Button("切换模式: 深色").width('45%').margin({ bottom: '12vp' })
          .onClick(() => {
            this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK);
          })
      }

      Row() {
        Button("竖屏").width('45%').margin({ bottom: '12vp' })
          .onClick(() => {
            this.changeOrientation(false)
          })
        Button("横屏").width('45%').margin({ bottom: '12vp' })
          .onClick(() => {
            this.changeOrientation(true)
          })
      }

      Row() {
        Button('Vertical:' + this.isVertical[this.isVerticalIndex]).width('45%').margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.isVerticalIndex++
            if (this.isVerticalIndex > this.isVertical.length - 1) {
              this.isVerticalIndex = 0
            }
          })
        Button('disableSwipe:' + this.disableSwipe[this.disableSwipeIndex]).width('45%').margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.disableSwipeIndex++
            if (this.disableSwipeIndex > this.disableSwipe.length - 1) {
              this.disableSwipeIndex = 0
            }
          })
      }

      Row() {
        Button('duration:' + this.duration[this.durationIndex]).width('45%').margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.durationIndex++
            if (this.durationIndex > this.duration.length - 1) {
              this.durationIndex = 0
            }
          })
        Button('PageFlipMode:' + this.isPageFlipMode[this.isPageFlipModeIndex]).width('45%').margin({ bottom: '12vp' })
          .onClick((event?: ClickEvent) => {
            this.isPageFlipModeIndex++
            if (this.isPageFlipModeIndex > this.isPageFlipMode.length - 1) {
              this.isPageFlipModeIndex = 0
            }
          })
      }

      Row() {
        Button('index++:' + this.currentIndex).width('45%').margin({ bottom: '12vp' })
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % 10;
          })

        Button('changeIndex').width('45%').margin({ bottom: '12vp' })
          .onClick(() => {
            this.currentIndex = (this.currentIndex + 1) % 10;
            this.controller.changeIndex(this.currentIndex);
            this.swiperController.changeIndex(this.currentIndex);

          })
      }

      Button('onContentDidScroll:' + this.isOnContentDidScroll[this.isOnContentDidScrollIndex])
        .margin({ bottom: '12vp' })
        .onClick((event?: ClickEvent) => {
          this.isOnContentDidScrollIndex++
          if (this.isOnContentDidScrollIndex > this.isOnContentDidScroll.length - 1) {
            this.isOnContentDidScrollIndex = 0
          }
        })
        Text('onContentWillScroll= 2')
      Row({ space: 12 }) {
        Button('showNext')
          .onClick(() => {
            this.swiperController.showNext();
          })
        Button('showPrevious')
          .onClick(() => {
            this.swiperController.showPrevious();
          })
      }
      Tabs({ barPosition: BarPosition.Start, controller: this.controller }) {
        ForEach(this.list, (index: number) => {
          TabContent().tabBar(this.tabBuilder(index, '页签 ' + this.list[index]))
        })
      }
      .onTabBarClick((index: number) => {
        this.currentIndex = index;
        this.swiperController.changeIndex(index, true);
      })
      .barMode(BarMode.Scrollable)
      .backgroundColor('#F1F3F5')
      .height(56)
      .width('100%')

      Swiper(this.swiperController) {
        LazyForEach(this.swiperData, (item: string) => {
          Text(item.toString())
            .onAppear(() => {
              console.info('onAppear ' + item.toString());
            })
            .onDisAppear(() => {
              console.info('onDisAppear ' + item.toString());
            })
            .width(360)
            .height(360)
            .backgroundColor(0xAFEEEE)
            .textAlign(TextAlign.Center)
            .fontSize(30)
        }, (item: string) => item)
      }
      .curve(Curve.Linear)
      .duration(this.duration[this.durationIndex])
      .loop(false)
      .onContentDidScroll(this.isOnContentDidScroll[this.isOnContentDidScrollIndex])
      // .onContentDidScroll(undefined)
      .vertical(this.isVertical[this.isVerticalIndex])
      .disableSwipe(this.disableSwipe[this.disableSwipeIndex])
      // .barMode(BarMode.Scrollable)
      // .animationDuration(600)
      // .barOverlap(true)
      // .barBackgroundBlurStyle(BlurStyle.COMPONENT_THICK)
      // .SwiperAnimationMode(this.isAnimationMode[this.isAnimationModeIndex])
      .pageFlipMode(this.isPageFlipMode[this.isPageFlipModeIndex])
      // .onChange((index: number) => {
      //   console.info(index.toString());
      // })
      .onAnimationStart((index: number, targetIndex: number, extraInfo: TabsAnimationEvent) => {
        if (index === targetIndex) {
          console.info("ygl onAnimationStart "
            + "index: " + index
            + "targetIndex: " + targetIndex
            + "currentOffset: " + extraInfo.currentOffset
            + 'targetOffset: ' + extraInfo.targetOffset
            + 'velocity: ' + extraInfo.velocity);
        }
      })
      .onAnimationEnd((index: number, extraInfo: TabsAnimationEvent) => {
        console.info("ygl onAnimationEnd "
          + "index: " + index
          + "currentOffset: " + extraInfo.currentOffset
          + 'targetOffset: ' + extraInfo.targetOffset
          + 'velocity: ' + extraInfo.velocity);
      })
      .onGestureSwipe((index: number, extraInfo: SwiperAnimationEvent) => {
        // 在页面跟手滑动过程中，逐帧触发该回调。
        console.info("ygl onGestureSwipe: "
          + "index: " + index
          + 'currentOffset: ' + extraInfo.currentOffset
          + 'targetOffset: ' + extraInfo.targetOffset
          + 'velocity: ' + extraInfo.velocity);
      })
      .onContentWillScroll((result: SwiperContentWillScrollResult) => {
        if (result.comingIndex == 2) {
          console.info('ygl onContentWillScroll = 2');
          return false;
        }
        return true;
      })
      .onSelected((index: number) => {
        console.log('ygl onSelected index:' + index);
        this.selectedIndex = index;
      })
      .onUnselected((index: number) => {
        console.log('ygl onUnselected index:' + index);
        this.onUnselected = index;
      })
      // .fadingEdge(this.selfFadingFade)
      .height(360)
      .width(360)
    }
  }
}
