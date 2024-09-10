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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function gridScrollBarTest() {
  /*
  * Grid组件 ScrollBar属性
  * 找到画面id为gridScrollBar1，gridScrollBar2的Grid组件
  * 找到画面文本为GridScrollBar的Button组件
  * 获取gridScrollBar1的ScrollBar属性与期待值BarState.On比对
  * 获取gridScrollBar2的ScrollBar属性与期待值BarState.Off比对
  * 点击button，变更gridScrollBar2的ScrollBar属性值为BarState.Auto
  * 获取gridScrollBar2的ScrollBar属性与期待值BarState.Auto比对
  */
  defineTest('gridScrollBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridScrollBarTestDemo running')
    let driver: Tester = Tester.create()
    let gridScrollBar1: Component = await driver.findComponent(Matcher.create().id('gridScrollBar1').enabled(true))
    let gridScrollBar2: Component = await driver.findComponent(Matcher.create().id('gridScrollBar2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridScrollBar').enabled(true))

    let scrollBar1: string = await gridScrollBar1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar1).$attrs.scrollBar, 'BarState.On')
    let scrollBar2: string = await gridScrollBar2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar2).$attrs.scrollBar, 'BarState.Off')
    await button.tap()
    let scrollBar3: string = await gridScrollBar2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar3).$attrs.scrollBar, 'BarState.Auto')
  }, 0)
}