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

export default async function GridRowItemAlignTest() {
  /*
   * GridRow组件 ItemAlign属性
   * 找到画面id为gridRowItemAlign1、gridRowItemAlign2、gridRowItemAlign3、gridRowItemAlign4的ItemAlign组件
   * 找到画面文本为GridRowItemAlign1、GridRowItemAlign2的Button组件
   * 获取gridRow1的ItemAlign属性与期待值ItemAlign.Center比对
   * 获取gridRow2的ItemAlign属性与期待值ItemAlign.Baseline比对
   * 获取gridRow3的ItemAlign属性与期待值ItemAlign.Auto比对
   * 获取gridRow4的ItemAlign属性与期待值ItemAlign.End比对
   * 点击button1，变更gridRow1的ItemAlign属性值为ItemAlign.Start
   * 获取gridRow1的ItemAlign属性与期待值ItemAlign.Start比对
   * 点击button2，变更gridRow1的ItemAlign属性值为ItemAlign.Stretch
   * 获取gridRow1的ItemAlign属性与期待值ItemAlign.Stretch比对
   */
  defineTest('GridRowItemAlignTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridRowItemAlignTestDemo running')
    let driver: Tester = Tester.create()
    let gridRow1: Component = await driver.findComponent(Matcher.create().id('gridRowItemAlign1').enabled(true))
    let gridRow2: Component = await driver.findComponent(Matcher.create().id('gridRowItemAlign2').enabled(true))
    let gridRow3: Component = await driver.findComponent(Matcher.create().id('gridRowItemAlign3').enabled(true))
    let gridRow4: Component = await driver.findComponent(Matcher.create().id('gridRowItemAlign4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GridRowItemAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GridRowItemAlign2').enabled(true))

    let itemAlign1: string = await gridRow1.getInspectorInfo()
    assertEqual(JSON.parse(itemAlign1).$attrs.itemAlign, 'ItemAlign.Center')

    let itemAlign2: string = await gridRow2.getInspectorInfo()
    assertEqual(JSON.parse(itemAlign2).$attrs.itemAlign, 'ItemAlign.Baseline')

    let itemAlign3: string = await gridRow3.getInspectorInfo()
    assertEqual(JSON.parse(itemAlign3).$attrs.itemAlign, 'ItemAlign.Auto')

    let itemAlign4: string = await gridRow4.getInspectorInfo()
    assertEqual(JSON.parse(itemAlign4).$attrs.itemAlign, 'ItemAlign.End')

    await button1.tap()
    let itemAlign5: string = await gridRow1.getInspectorInfo()
    assertEqual(JSON.parse(itemAlign5).$attrs.itemAlign, 'ItemAlign.Start')

    await button2.tap()
    let itemAlign6: string = await gridRow1.getInspectorInfo()
    assertEqual(JSON.parse(itemAlign6).$attrs.itemAlign, 'ItemAlign.Stretch')
  })
}