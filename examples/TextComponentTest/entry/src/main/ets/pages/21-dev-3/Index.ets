/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import router from '@ohos.router';

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct Index9716 {
  private items : ListCategories[] = [
    {title:'Text文本识别',utl:'pages/21DEV/Text'},
    {title:'TextInput',utl:'pages/21DEV/TextInput'},
    {title:'TextInput-补充',utl:'pages/21DEV/TextInput-1'},
    {title:'TextArea',utl:'pages/21DEV/TextArea'},
    // {title:'TextArea-补充',utl:'pages/21DEV/TextArea-1'},
    {title:'Search',utl:'pages/21DEV/Search'},
    {title:'SearchButtonModifier',utl:'pages/21DEV/SearchButtonModifier'},
    // {title:'子组件空白行',utl:'pages/21DEV/TextSpan'},
    {title:'Text自适应字体',utl:'pages/21DEV/minfontSize'},
    {title:'Text自适应字体modifier',utl:'pages/21DEV/minfontSizeModifier'},
    {title:'MinfontScale属性Modifier',utl:'pages/21DEV/halfleadingModifier'}

  ]

  build() {
    Column() {
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize('16vp').fontWeight(FontWeight.Bold).onClick(() => {
              router.pushUrl({url:item.utl})
            })
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%')
  }
}