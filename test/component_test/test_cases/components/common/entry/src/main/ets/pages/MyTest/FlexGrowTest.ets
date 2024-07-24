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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function flexGrowTest() {
  /*
  * 使用Text组件 FlexGrow属性
  * 找到画面id为textFlexGrow的Text组件
  * 获取textFlexGrow的FlexGrow属性与期待值2比对
  */
  defineTest('flexGrowTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('flexGrowTestDemo running')
    let driver: Tester = Tester.create()
    let textFlexGrow: Component = await driver.findComponent(Matcher.create().id('textFlexGrow').enabled(true))
    let flexGrow: string = await textFlexGrow.getInspectorInfo()
    assertEqual(JSON.parse(flexGrow).$attrs.flexGrow, 2)
  }, 0)
}