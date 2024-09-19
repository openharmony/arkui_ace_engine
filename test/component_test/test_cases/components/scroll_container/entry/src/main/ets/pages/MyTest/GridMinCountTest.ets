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

export default async function gridMinCountTest() {
  /*
  * Grid组件 MinCount属性
  * 找到画面id为gridMinCount1的Grid组件
  * 找到画面文本为GridMinCount的Button组件
  * 获取gridMinCount1的MinCount属性与期待值1比对
  * 点击button，变更gridMinCount1，gridMinCount2的LayoutDirection属性值为GridDirection.Column
  * 获取gridMinCount1的MinCount属性与期待值4比对
  */
  defineTest('gridMinCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridMinCountTestDemo running')
    let driver: Tester = Tester.create()
    let gridMinCount1: Component = await driver.findComponent(Matcher.create().id('gridMinCount1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridMinCount').enabled(true))

    let minCount1: string = await gridMinCount1.getInspectorInfo()
    assertEqual(JSON.parse(minCount1).$attrs.minCount, 1)
    await button.tap()
    let minCount2: string = await gridMinCount1.getInspectorInfo()
    assertEqual(JSON.parse(minCount2).$attrs.minCount, 4)
  }, 0)
}