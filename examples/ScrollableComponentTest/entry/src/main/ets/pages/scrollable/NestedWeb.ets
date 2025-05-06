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

import webview from '@ohos.web.webview'

@Entry
@ComponentV2
struct NestedWeb {

  /* 典型场景：
     新闻浏览页面，新闻内容使用Web组件实现，评论区部分用ArkUI原生List组件实现。Web组件的滚动和List组件滚动能无缝衔接，像同一个滚动组件。
  */

  /* 实现思路：
      使用Scroll嵌套Web和List组件实现。Scroll作为父组件响应滚动手势，Web和List组件禁用滚动手势，滚动偏移量由父组件Scroll给Web和List组件派发。
    滚动偏移量派发逻辑：
    1、手指向上划动：
    1）如果Web没有滚动到底部，Scroll将滚动偏移量派发给Web，Scroll组件自身不滚动。
    2）如果Web滚动到底部，Scroll没有滚动到底部，则Scroll自身滚动，不给Web和List派发滚动偏移量。
    3）如果Scroll滚动到底部，则滚动偏移量派发给List，Scroll自身不滚动。
    2、手指向下划动：
    1）如果List没有滚动到顶部，则Scroll将滚动偏移量派发给List，Scroll自身不滚动。
    2）如果List滚动到顶部，Scroll没有滚动到顶部，则Scroll自身滚动，滚动偏移量不派发给List和Web。
    3）如果Scroll滚动到顶部，则滚动偏移量派发给Web，Scroll自身不滚动。
  */

  /* 关键实现：
    1、如禁用Web滚动手势？
    首先将调用Web滚动控制器方法，设置Web禁用触摸的滚动。
    this.webController.setScrollable(false, webview.ScrollType.EVENT);
    再使用onGestureRecognizerJudgeBegin方法，禁止web自带的pan手势触发。举例：
    .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
        others: Array<GestureRecognizer>) => {
      if (current.isBuiltIn() && current.getType() == GestureControl.GestureType.PAN_GESTURE) {
        return GestureJudgeResult.REJECT;
      }
        return GestureJudgeResult.CONTINUE;
    })

    2、如何禁止List组件的手势
    设置List组件enableScrollInteraction为false。

    3、如何检测List、Scroll组件是否滚动到边界
    滚动到上边界：scroller.currentOffset().yOffset 小于等于0。
    滚动到下边界：scroller.isAtEnd() 为true。

    4、如何检测Web组件是否滚动到边界
    获取Web组件自身高度、内容高度和当前滚动偏移量来判定。
    获取Web组件自身高度：webController.getPageHeight();
    获取Web组件内容高度：webController?.runJavaScriptExt('window.innerHeight'）
    获取Web组件的滚动偏移量：webController.runJavaScriptExt('document.documentElement.scrollTop || document.body.scrollTop')

    5、如何让Scroll组件不滚动
    Scroll组件绑定onScrollFrameBegin事件，将剩余滚动偏移量返回0，scroll就不会滚动，也不会停止惯性滚动动画。

    6、滚动偏移派发给List
    调用List滚动控制器的scrollBy接口。

    7、滚动偏移量派发给Web
    调用Web的webController.scrollBy接口。
    */

  private scroller: Scroller = new Scroller()
  private listScroller: Scroller = new Scroller()
  private webController: webview.WebviewController = new webview.WebviewController()
  private isWebAtEnd: boolean = false
  private webHeight: number = 0
  private scrollTop: number = 0
    @Local arr: Array<number> = []

    aboutToAppear(): void {
        for(let i = 0; i < 100; i++) {
        this.arr.push(i)
    }
}

getWebHeight() {
    try {
        this.webController?.runJavaScriptExt('window.innerHeight',
            (error, result) => {
                if (error || !result) {
                    return;
                }
                if (result.getType() === webview.JsMessageType.NUMBER) {
                    this.webHeight = result.getNumber()
                }
            })
    } catch (error) {
    }
}

getWebScrollTop() {
    try {
        this.webController.runJavaScriptExt('document.documentElement.scrollTop || document.body.scrollTop',
            (error, result) => {
                if (error || !result) {
                    return;
                }
                let type = result.getType();
                if (type === webview.JsMessageType.NUMBER) {
                    this.scrollTop = result.getNumber()
                    let pageHeight = this.webController.getPageHeight();
                    this.isWebAtEnd = false
                    if (this.scrollTop + this.webHeight >= pageHeight) {
                        this.isWebAtEnd = true;
                    }
                }
            });
    } catch (error) {
    }
}

build() {
    Scroll(this.scroller) {
        Column() {
            Web({
                src: '网络地址',
                controller: this.webController,
            })
                .height('100%')
                .onPageEnd(() => {
                    this.webController.setScrollable(false, webview.ScrollType.EVENT);
                    this.getWebHeight();
                })
                // 在识别器即将要成功时，根据当前组件状态，设置识别器使能状态
                .onGestureRecognizerJudgeBegin((event: BaseGestureEvent, current: GestureRecognizer,
                    others: Array<GestureRecognizer>) => {
                    if (current.isBuiltIn() && current.getType() == GestureControl.GestureType.PAN_GESTURE) {
                        return GestureJudgeResult.REJECT;
                    }
                    return GestureJudgeResult.CONTINUE;
                })
            List({ scroller: this.listScroller }) {
                Repeat<number>(this.arr)
                    .each((item: RepeatItem<number>) => {
                        ListItem() {
                            Text('item' + item.item.toString())
                        }
                    })
            }
        .height('100%')
                .maintainVisibleContentPosition(true)
                .enableScrollInteraction(false)
        }
    }
    .onScrollFrameBegin((offset: number, state: ScrollState) => {
        this.getWebScrollTop();
        if (offset > 0) {
            if (!this.isWebAtEnd) {
                this.webController.scrollBy(0, offset)
                return { offsetRemain: 0 }
            } else if (this.scroller.isAtEnd()) {
                this.listScroller.scrollBy(0, offset)
                return { offsetRemain: 0 }
            }
        } else if (offset < 0) {
            if (this.listScroller.currentOffset().yOffset > 0) {
                this.listScroller.scrollBy(0, offset)
                return { offsetRemain: 0 }
            } else if (this.scroller.currentOffset().yOffset <= 0) {
                this.webController.scrollBy(0, offset)
                return { offsetRemain: 0 }
            }
        }
        return { offsetRemain: offset }
    })
}
}