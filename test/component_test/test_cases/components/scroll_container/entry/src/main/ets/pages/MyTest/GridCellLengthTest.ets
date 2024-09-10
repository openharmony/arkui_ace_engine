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

export default async function gridCellLengthTest() {
  /*
  * Grid组件 CellLength属性
  * 找到画面id为gridCellLength的Grid组件
  * 获取gridCellLength的CellLength属性与期待值100比对
  */
  defineTest('gridCellLengthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridCellLengthTestDemo running')
    let driver: Tester = Tester.create()
    let gridCellLength: Component = await driver.findComponent(Matcher.create().id('gridCellLength').enabled(true))

    let cellLength1: string = await gridCellLength.getInspectorInfo()
    assertEqual(JSON.parse(cellLength1).$attrs.cellLength, 100)
  }, 0)
}