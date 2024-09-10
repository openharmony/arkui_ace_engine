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

export default async function scrollScrollableTest() {
  /*
 * Scroll组件 Scrollable属性
 * 找到画面id为scrollScrollable1,scrollScrollable2的Scroll组件
 * 找到画面文本为scrollScrollable的Button组件
 * 获取scrollScrollable1的Scrollable属性与期待值ScrollDirection.Horizontal比对
 * 获取scrollScrollable2的Scrollable属性与期待值ScrollDirection.Vertical比对
 * 点击button，变更scrollScrollable2的BarState属性值为ScrollDirection.None
 * 获取scrollScrollable2的Scrollable属性与期待值ScrollDirection.None比对
 */
  defineTest('scrollScrollableTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollScrollableTestDemo running')
    let driver: Tester = Tester.create()
    let scrollScrollable1: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollable1').enabled(true))
    let scrollScrollable2: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollable2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollScrollable').enabled(true))

    let scrollable1: string = await scrollScrollable1.getInspectorInfo()
    assertEqual(JSON.parse(scrollable1).$attrs.scrollable, 'ScrollDirection.Horizontal')
    let scrollable2: string = await scrollScrollable2.getInspectorInfo()
    assertEqual(JSON.parse(scrollable2).$attrs.scrollable, 'ScrollDirection.Vertical')
    await button.tap()
    let scrollable3: string = await scrollScrollable2.getInspectorInfo()
    assertEqual(JSON.parse(scrollable3).$attrs.scrollable, 'ScrollDirection.None')
  }, 0)
}