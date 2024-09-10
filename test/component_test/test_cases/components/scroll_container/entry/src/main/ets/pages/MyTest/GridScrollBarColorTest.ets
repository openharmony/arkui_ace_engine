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

export default async function gridScrollBarColorTest() {
  /*
  * Grid组件 ScrollBarColor属性
  * 找到画面id为gridScrollBarColor1，gridScrollBarColor2的Grid组件
  * 找到画面文本为GridScrollBarColor的Button组件
  * 获取gridScrollBarColor1的ScrollBarColor属性与期待值Color.Orange比对
  * 获取gridScrollBarColor2的ScrollBarColor属性与期待值'#FFFF64FF'比对
  * 点击button，变更gridScrollBarColor2的ScrollBarColor属性值为'#FFFFA500'
  * 获取gridScrollBarColor2的ScrollBarColor属性与期待值'#FFFFA500'比对
  */
  defineTest('gridScrollBarColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridScrollBarColorTestDemo running')
    let driver: Tester = Tester.create()
    let gridScrollBarColor1: Component =
      await driver.findComponent(Matcher.create().id('gridScrollBarColor1').enabled(true))
    let gridScrollBarColor2: Component =
      await driver.findComponent(Matcher.create().id('gridScrollBarColor2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridScrollBarColor').enabled(true))

    let scrollBarColor1: string = await gridScrollBarColor1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor1).$attrs.scrollBarColor.toLowerCase(), Color.Orange)
    let scrollBarColor2: string = await gridScrollBarColor2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor2).$attrs.scrollBarColor, '#FFFF64FF')
    await button.tap()
    let scrollBarColor3: string = await gridScrollBarColor2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor3).$attrs.scrollBarColor, '#FFFFA500')
  }, 0)
}