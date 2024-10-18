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

export default async function listScrollBarColorTest() {
  /*
   * List组件 ScrollBarColor属性
   * 找到画面id为listScrollBarColor1,listScrollBarColor2的List组件
   * 找到画面文本为ListScrollBarColor的Button组件
   * 获取list1的ScrollBarColor属性与期待值Color.Blue比对
   * 获取list2的ScrollBarColor属性与期待值#FFFF64FF比对
   * 点击button，变更list1的ScrollBarColor属性值为#FFFFFFFF
   * 获取list1的ScrollBarColor属性与期待值#FFFFFFFF比对
   */
  defineTest('listScrollBarColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listScrollBarColorTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listScrollBarColor1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listScrollBarColor2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListScrollBarColor').enabled(true))

    let scrollBarColor1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor1).$attrs.scrollBarColor.toLowerCase(), Color.Blue)
    let scrollBarColor2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor2).$attrs.scrollBarColor, '#FFFF64FF')
    await button.tap()
    let scrollBarColor3: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBarColor3).$attrs.scrollBarColor, '#FFFFFFFF')
  }, 0)
}