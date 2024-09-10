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

export default async function scrollScrollBarWidthTest() {
  /*
 * Scroll组件 ScrollBarWidth属性
 * 找到画面id为scrollScrollBarWidth1,scrollScrollBarWidth2的Scroll组件
 * 找到画面文本为scrollScrollBarWidth的Button组件
 * 获取scrollScrollBarWidth1的ScrollBarWidth属性与期待值'20.00vp'比对
 * 点击button，变更scrollScrollBarWidth2的ScrollBar属性值为'50.00vp'
 * 获取scrollScrollBarWidth1的ScrollBarWidth属性与期待值'50.00vp'比对
 * 获取scrollScrollBarWidth2的ScrollBarWidth属性与期待值'1000.00vp'比对
 */
  defineTest('scrollScrollBarWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollScrollBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let scrollScrollBarWidth1: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollBarWidth1').enabled(true))
    let scrollScrollBarWidth2: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollBarWidth2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollScrollBarWidth').enabled(true))

    let scrollBarWidth1: string = await scrollScrollBarWidth1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth1).$attrs.scrollBarWidth, '20.00vp')
    await button.tap()
    let scrollBarWidth2: string = await scrollScrollBarWidth1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth2).$attrs.scrollBarWidth, '50.00vp')
    let scrollBarWidth3: string = await scrollScrollBarWidth2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarWidth3).$attrs.scrollBarWidth, '1000.00vp')
  }, 0)
}