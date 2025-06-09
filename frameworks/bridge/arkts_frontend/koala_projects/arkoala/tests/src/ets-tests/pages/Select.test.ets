/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct SelectTest {
    @State text: string = "TTTTT"
    @State text2: string = "VVVVV"
    @State index: number = 2
    @State index2: number = 1
    build() {
        Column() {
            Select([{ value: 'aaa', icon: "/common/public_icon.svg" },
                    { value: 'bbb', icon: "/common/public_icon.svg" },
                    { value: 'ccc', icon: "/common/public_icon.svg" },
                    { value: 'ddd', icon: "/common/public_icon.svg" }])
            .selected(this.index)
            .value(this.text)
            .font({size:16, weight:FontWeight.Lighter, family:"testString", style:FontStyle.Normal})
            .fontColor('#E5182431')
            .selectedOptionBgColor('#182431')
            .selectedOptionFont({size:16, weight:FontWeight.Lighter, family:"testString", style:FontStyle.Normal})
            .selectedOptionFontColor(Color.White)
            .optionBgColor(Color.White)
            .optionFont({size:'16fp', weight:FontWeight.Regular, family:"testString", style:FontStyle.Normal})
            .optionFontColor('#ff182431')
            .space(8)
            .arrowPosition(ArrowPosition.END)
            .menuAlign(MenuAlignType.START,{dx:0, dy:0})
            Select([{ value: 'ddd', icon: "/common/public_icon.svg" },
                    { value: 'eee', icon: "/common/public_icon.svg" }])
            .selected(this.index2)
            .value(this.text2)
            .font({size:'18fp', weight:FontWeight.Lighter, family:"testString", style:FontStyle.Italic})
            .fontColor('#E5182431')
            .selectedOptionBgColor('#182431')
            .selectedOptionFont({size:16, weight:FontWeight.Lighter, family:"testString", style:FontStyle.Italic})
            .selectedOptionFontColor(Color.Red)
            .optionBgColor(Color.White)
            .optionFont({size:'16fp', weight:FontWeight.Regular, family:"testString", style:FontStyle.Italic})
            .optionFontColor(Color.White)
            .space('8px')
            .arrowPosition(ArrowPosition.START)
            .menuAlign(MenuAlignType.CENTER,{dx:'2px', dy:"2px"})
        }
    }
}
