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

export default async function gridMaxCountTest() {
  /*
  * Grid组件 MaxCount属性
  * 找到画面id为gridMaxCount1，gridMaxCount2的Grid组件
  * 找到画面文本为GridMaxCount的Button组件
  * 获取gridMaxCount1的MaxCount属性与期待值1000000比对
  * 获取gridMaxCount2的MaxCount属性与期待值1000000比对
  * 点击button，变更gridMaxCount2的MaxCount属性值为3
  * 获取gridMaxCount2的MaxCount属性与期待值3比对
  */
  defineTest('gridMaxCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridMaxCountTestDemo running')
    let driver: Tester = Tester.create()
    let gridMaxCount1: Component = await driver.findComponent(Matcher.create().id('gridMaxCount1').enabled(true))
    let gridMaxCount2: Component = await driver.findComponent(Matcher.create().id('gridMaxCount2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridMaxCount').enabled(true))
    let maxCount1: string = await gridMaxCount1.getInspectorInfo()
    assertEqual(JSON.parse(maxCount1).$attrs.maxCount, 1000000)
    let maxCount2: string = await gridMaxCount2.getInspectorInfo()
    assertEqual(JSON.parse(maxCount2).$attrs.maxCount, 1000000)
    await button.tap()
    let maxCount3: string = await gridMaxCount2.getInspectorInfo()
    assertEqual(JSON.parse(maxCount3).$attrs.maxCount, 3)
  }, 0)
}