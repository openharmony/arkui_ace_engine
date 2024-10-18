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

export default async function listScrollBarTest() {
  /*
   * List组件 ScrollBar属性
   * 找到画面id为listScrollBar1,listScrollBar2,listScrollBar3的List组件
   * 找到画面文本为ListScrollBar的Button组件
   * 获取list1的ScrollBar属性与期待值BarState.Off比对
   * 获取list2的ScrollBar属性与期待值BarState.On比对
   * 获取list3的ScrollBar属性与期待值BarState.On比对
   * 点击button，变更list1的ScrollBar属性值为BarState.Auto
   * 获取list1的ScrollBar属性与期待值BarState.Auto比对
   */
  defineTest('listScrollBarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listScrollBarTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listScrollBar1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listScrollBar2').enabled(true))
    let list3: Component = await driver.findComponent(Matcher.create().id('listScrollBar3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ListScrollBar').enabled(true))

    let scrollBar1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar1).$attrs.scrollBar, 'BarState.Off')
    let scrollBar2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar2).$attrs.scrollBar, 'BarState.On')
    let scrollBar3: string = await list3.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar3).$attrs.scrollBar, 'BarState.On')
    await button.tap()
    let scrollBar4: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(scrollBar4).$attrs.scrollBar, 'BarState.Auto')
  }, 0)
}