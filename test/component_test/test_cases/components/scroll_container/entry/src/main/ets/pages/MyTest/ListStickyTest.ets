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

export default async function listStickyTest() {
  /*
   * List组件 Sticky属性
   * 找到画面id为listSticky1,listSticky2的List组件
   * 找到画面文本为ListSticky1,ListSticky2的Button组件
   * 获取list1的Sticky属性与期待值StickyStyle.Footer比对
   * 获取list2的Sticky属性与期待值StickyStyle.Footer|StickyStyle.Header比对
   * 点击button1，变更list1的Sticky属性值为StickyStyle.Header
   * 获取list1的Sticky属性与期待值StickyStyle.Header比对
   * 点击button，变更list1的Sticky属性值为StickyStyle.None
   * 获取list1的Sticky属性与期待值StickyStyle.None比对
   */
  defineTest('listStickyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listStickyTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listSticky1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listSticky2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ListSticky1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ListSticky2').enabled(true))

    let sticky1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(sticky1).$attrs.sticky, 'StickyStyle.Footer')
    let sticky2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(sticky2).$attrs.sticky, 'StickyStyle.Header | StickyStyle.Footer')
    await button1.tap()
    let sticky3: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(sticky3).$attrs.sticky, 'StickyStyle.Header')
    await button2.tap()
    let sticky4: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(sticky4).$attrs.sticky, 'StickyStyle.None')
  }, 0)
}