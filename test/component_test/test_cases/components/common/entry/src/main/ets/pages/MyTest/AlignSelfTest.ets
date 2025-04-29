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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function alignSelfTest() {
  /*
  * text组件 alignSelf属性
  * 找到画面id为textAlignSelf1,textAlignSelf2,textAlignSelf3的text组件
  * 找到画面文本为 ButtonAlignSelf1、ButtonAlignSelf2、ButtonAlignSelf3的Button组件
  * 获取textAlignSelf1的alignSelf属性与期待值ItemAlign.Baseline比对
  * 获取textAlignSelf2的alignSelf属性与期待值ItemAlign.End比对
  * 获取textAlignSelf3的alignSelf属性与期待值ItemAlign.Center比对
  * 点击button1，变更textAlignSelf3的alignSelf属性值为ItemAlign.Auto
  * 获取textAlignSelf3的alignSelf属性与期待值ItemAlign.Auto比对
  * 点击button2，变更textAlignSelf3的alignSelf属性值为ItemAlign.Start
  * 获取textAlignSelf3的alignSelf属性与期待值ItemAlign.Start比对
  * *点击button3，变更textAlignSelf3的alignSelf属性值为ItemAlign.Stretch
  * 获取textAlignSelf3的alignSelf属性与期待值ItemAlign.Stretch比对
  */
  defineTest('alignSelfTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alignSelfTestDemo running")
    let driver: Tester = Tester.create()
    let textAlignSelf1: Component = await driver.findComponent(Matcher.create().id('textAlignSelf1').enabled(true))
    let textAlignSelf2: Component = await driver.findComponent(Matcher.create().id('textAlignSelf2').enabled(true))
    let textAlignSelf3: Component = await driver.findComponent(Matcher.create().id('textAlignSelf3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonAlignSelf1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonAlignSelf2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonAlignSelf3').enabled(true))
    let alignSelf1: string = await textAlignSelf1.getInspectorInfo()
    assertEqual(JSON.parse(alignSelf1).$attrs.alignSelf, 'ItemAlign.Baseline')

    let alignSelf2: string = await textAlignSelf2.getInspectorInfo()
    assertEqual(JSON.parse(alignSelf2).$attrs.alignSelf, 'ItemAlign.End')

    let alignSelf3: string = await textAlignSelf3.getInspectorInfo()
    assertEqual(JSON.parse(alignSelf3).$attrs.alignSelf, 'ItemAlign.Center')

    await button1.tap()
    let alignSelf4: string = await textAlignSelf3.getInspectorInfo()
    assertEqual(JSON.parse(alignSelf4).$attrs.alignSelf, 'ItemAlign.Auto')

    await button2.tap()
    let alignSelf5: string = await textAlignSelf3.getInspectorInfo()
    assertEqual(JSON.parse(alignSelf5).$attrs.alignSelf, 'ItemAlign.Start')

    await button3.tap()
    let alignSelf6: string = await textAlignSelf3.getInspectorInfo()
    assertEqual(JSON.parse(alignSelf6).$attrs.alignSelf, 'ItemAlign.Stretch')
  }, 0)
}