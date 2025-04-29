/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function scrollScrollBarTest() {
  /*
 * Scroll组件 ScrollBar属性
 * 找到画面id为scrollScrollBar1,scrollScrollBar2,scrollScrollBar3的Scroll组件
 * 找到画面文本为scrollScrollBar的Button组件
 * 获取scrollScrollBar1的ScrollBar属性与期待值BarState.Off比对
 * 获取scrollScrollBar2的ScrollBar属性与期待值BarState.On比对
 * 点击button，变更scrollScrollBar2的ScrollBar属性值为BarState.Auto
 * 获取scrollScrollBar2的ScrollBar属性与期待值BarState.Auto比对
 * 获取scrollScrollBar3的ScrollBar属性与期待值BarState.On比对
 */
  defineTest('scrollScrollBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollScrollBarTestDemo running')
    let driver: Tester = Tester.create()
    let scrollScrollBar1: Component = await driver.findComponent(Matcher.create().id('scrollScrollBar1').enabled(true))
    let scrollScrollBar2: Component = await driver.findComponent(Matcher.create().id('scrollScrollBar2').enabled(true))
    let scrollScrollBar3: Component = await driver.findComponent(Matcher.create().id('scrollScrollBar3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollScrollBar').enabled(true))

    let scrollBar1: string = await scrollScrollBar1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar1).$attrs.scrollBar, 'BarState.Off')
    let scrollBar2: string = await scrollScrollBar2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar2).$attrs.scrollBar, 'BarState.On')
    await button.tap()
    let scrollBar3: string = await scrollScrollBar2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar3).$attrs.scrollBar, 'BarState.Auto')
    let scrollBar4: string = await scrollScrollBar3.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar4).$attrs.scrollBar, 'BarState.On')
  }, 0)
}