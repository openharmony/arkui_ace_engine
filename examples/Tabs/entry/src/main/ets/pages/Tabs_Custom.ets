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
interface itemType {
  text: string,
  backgroundColor: Color
}

@Entry
@Component
struct Tabs_Custom {
  @State data: itemType[] = [
    {
      text: 'Red',
      backgroundColor: Color.Red
    },
    {
      text: 'Yellow',
      backgroundColor: Color.Yellow
    },
    {
      text: 'Blue',
      backgroundColor: Color.Blue
    }];
  @State opacityList: number[] = [];
  @State scaleList: number[] = [];
  private durationList: number[] = [];
  private timeoutList: number[] = [];
  private customContentTransition: (from: number, to: number) => TabContentAnimatedTransition =
    (from: number, to: number) => {
      let tabContentAnimatedTransition = {
        timeout: this.timeoutList[from],
        transition: (proxy: TabContentTransitionProxy) => {
          this.scaleList[from] = 1.0;
          this.scaleList[to] = 0.5;
          this.opacityList[from] = 1.0;
          this.opacityList[to] = 0.5;
          this.getUIContext()?.animateTo({
            duration: this.durationList[from],
            onFinish: () => {
              proxy.finishTransition();
            }
          }, () => {
            this.scaleList[from] = 0.5;
            this.scaleList[to] = 1.0;
            this.opacityList[from] = 0.5;
            this.opacityList[to] = 1.0;
          });
        }
      } as TabContentAnimatedTransition;
      return tabContentAnimatedTransition;
    };

  aboutToAppear(): void {
    let duration = 1000;
    let timeout = 1000;
    for (let i = 1; i <= this.data.length; i++) {
      this.opacityList.push(1.0);
      this.scaleList.push(1.0);
      this.durationList.push(duration * i);
      this.timeoutList.push(timeout * i);
    }
  }

  @State text: string = ''

  build() {
    Column() {
      // Text('onContentDidScroll: '+ this.text)

      Tabs() {
        ForEach(this.data, (item: itemType, index: number) => {
          TabContent() {
          }
          .tabBar(item.text)
          .backgroundColor(item.backgroundColor)
          // 自定义动画变化透明度、缩放页面等
          .opacity(this.opacityList[index])
          .scale({ x: this.scaleList[index], y: this.scaleList[index] })
        })
      }
      .onContentDidScroll((selectedIndex: number, index: number, position: number, mainAxisLength: number) => {
        // 监听Swiper页面滑动事件，在该回调中可以实现自定义导航点切换动画等
        console.info("ygl onContentDidScroll selectedIndex: " + selectedIndex + ", index: " + index +
          ", position: " + position + ", mainAxisLength: " + mainAxisLength);
      })

      .backgroundColor(0xf1f3f5)
      .width('100%')
      .height(500)
      .customContentTransition(this.customContentTransition)
    }
  }
}
