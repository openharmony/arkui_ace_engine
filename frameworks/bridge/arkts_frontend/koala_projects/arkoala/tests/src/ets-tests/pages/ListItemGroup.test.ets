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
struct ListItemGroupTest {
    private timetable: any = [
      {
        title: 'Monday',
        projects: ['Language', 'Math', 'English']
      },
      {
        title: 'Tuesday',
        projects: ['Physics', 'Chemistry', 'Biologics']
      },
      {
        title: 'Wednesday',
        projects: ['History', 'Geography', 'Politics']
      },
      {
        title: 'Thursday',
        projects: ['Art', 'Music', 'Sports']
      }
    ]
  
    @Builder itemHead(text:string) {
      Text(text)
        .fontSize(20)
        .backgroundColor(0xAABBCC)
        .width("100%")
        .padding(10)
    }
  
    @Builder itemFoot(num: number) {
      Text('Total lessons: '+ num)
        .fontSize(16)
        .backgroundColor(0xAABBCC)
        .width("100%")
        .padding(5)
    }

    build() {
      Column() {
        List({ space: 20 }) {
          ForEach(this.timetable, (item) => {
            ListItemGroup({ header:this.itemHead(item.title), footer:this.itemFoot(item.projects.length) }) {
              ForEach(item.projects, (project) => {
                ListItem() {
                  Text(project)
                }
              }, item => item)
            }
            .divider ({ strokeWidth: 5, color: 0xff00ff, startMargin: "10vp", endMargin: "20px" })
          })
        }
      }
    }
  }