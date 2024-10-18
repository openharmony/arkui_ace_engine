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

export default async function listScrollSnapAlignTest() {
  /*
   * List组件 ScrollSnapAlign属性
   * 找到画面id为listScrollSnapAlign1,listScrollSnapAlign2,listScrollSnapAlign3的List组件
   * 找到画面文本为ListScrollSnapAlign1,ListScrollSnapAlign2的Button组件
   * 获取list1的ScrollSnapAlign属性与期待值ScrollSnapAlign.CENTER比对
   * 获取list2的ScrollSnapAlign属性与期待值ScrollSnapAlign.NONE比对
   * 获取list3的ScrollSnapAlign属性与期待值 ScrollSnapAlign.CENTER比对
   * 点击button1，变更list1的ScrollSnapAlign属性值为ScrollSnapAlign.END
   * 获取list1的ScrollSnapAlign属性与期待值ScrollSnapAlign.END比对
   * 点击button2，变更list1的ScrollSnapAlign属性值为ScrollSnapAlign.CENTER
   * 获取list1的ScrollSnapAlign属性与期待值ScrollSnapAlign.CENTER比对
   */
  defineTest('listScrollSnapAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('listScrollSnapAlignTestDemo running')
    let driver: Tester = Tester.create()
    let list1: Component = await driver.findComponent(Matcher.create().id('listScrollSnapAlign1').enabled(true))
    let list2: Component = await driver.findComponent(Matcher.create().id('listScrollSnapAlign2').enabled(true))
    let list3: Component = await driver.findComponent(Matcher.create().id('listScrollSnapAlign3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ListScrollSnapAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ListScrollSnapAlign2').enabled(true))

    let scrollSnapAlign1: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnapAlign1).$attrs.scrollSnapAlign, 'ScrollSnapAlign.CENTER')
    let scrollSnapAlign2: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnapAlign2).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    let scrollSnapAlign3: string = await list3.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnapAlign3).$attrs.scrollSnapAlign, 'ScrollSnapAlign.CENTER')
    await button1.tap()
    let scrollSnapAlign4: string = await list1.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnapAlign4).$attrs.scrollSnapAlign, 'ScrollSnapAlign.END')
    await button2.tap()
    let scrollSnapAlign5: string = await list2.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnapAlign5).$attrs.scrollSnapAlign, 'ScrollSnapAlign.CENTER')
  }, 0)
}