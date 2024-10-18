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

export default async function scrollScrollBarColorTest() {
  /*
   * Scroll组件 ScrollBarColor属性
   * 找到画面id为scrollScrollBarColor1,scrollScrollBarColor2的Scroll组件
   * 找到画面文本为scrollScrollBarColor的Button组件
   * 获取scrollScrollBarColor1的ScrollBarColor属性与期待值Color.Blue比对
   * 获取scrollScrollBarColor2的ScrollBarColor属性与期待值#66182431比对
   * 点击button，变更scrollScrollBarColor2的ScrollBarColor属性值为''#FFFF64FF''
   * 获取scrollScrollBarColor2的ScrollBarColor属性与期待值''#FFFF64FF''比对
   */
  defineTest('scrollScrollBarColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollScrollBarColorTestDemo running')
    let driver: Tester = Tester.create()
    let scrollScrollBarColor1: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollBarColor1').enabled(true))
    let scrollScrollBarColor2: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollBarColor2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollScrollBarColor').enabled(true))

    let scrollBarColor1: string = await scrollScrollBarColor1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor1).$attrs.scrollBarColor.toLowerCase(), Color.Blue)
    let scrollBarColor2: string = await scrollScrollBarColor2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor2).$attrs.scrollBarColor, '#66182431')
    await button.tap()
    let scrollBarColor3: string = await scrollScrollBarColor2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor3).$attrs.scrollBarColor, '#FFFF64FF')
  }, 0)
}