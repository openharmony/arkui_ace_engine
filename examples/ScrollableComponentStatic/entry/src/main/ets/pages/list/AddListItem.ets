'use static'

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { ComponentCard } from '../../common/Card';
import common from '@ohos.app.ability.common';
import { ToDo } from './ToDo';
import { ToDoListItem } from './ToDoListItem';
import { State, Watch } from '@ohos.arkui.stateManagement';
import {
  Entry,
  $r,
  Component,
  Column,
  List,
  ListItem,
  Row,
  Text,
  Blank,
  ForEach,
  NavDestination,
  Length,
  TextPickerResult,
  TextPickerDialogOptions,
  ColumnOptions,
  ListOptions
} from '@kit.ArkUI';

@Entry
@Component
export struct AddListItem {
  @State toDoData: ToDo[] = [] as ToDo[];
  @State @Watch('onEditModeChange') isEditMode: boolean = false;
  @State selectedItems: ToDo[] = [] as ToDo[];
  private availableThings: string[] = [];

  aboutToAppear(): void {
    const context = this.getUIContext().getHostContext() as common.UIAbilityContext;
    const reading = context.resourceManager.getStringByNameSync('Reading')
    this.availableThings.push(reading)
    const exercise = context.resourceManager.getStringByNameSync('Exercise')
    this.availableThings.push(exercise)
    const travel = context.resourceManager.getStringByNameSync('Travel')
    this.availableThings.push(travel)
    const listening = context.resourceManager.getStringByNameSync('Listening_Music')
    this.availableThings.push(listening)
    const watching = context.resourceManager.getStringByNameSync('Watching_Films')
    this.availableThings.push(watching)
    const singing = context.resourceManager.getStringByNameSync('Singing')
    this.availableThings.push(singing)
  }

  onEditModeChange(propertyName: string): void {
    // @Watch callback: called when isEditMode changes
    if (!this.isEditMode) {
      this.selectedItems = [];
    }
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Please replace $r('app.string.AddListItem_titleExample') with the actual resource file.
        // In this example, the value of this resource file is "Add List Item Example"
        ComponentCard({ title: $r('app.string.AddListItem_titleExample') }) {
          Column({ space: 12 } as ColumnOptions) {
            Row() {
              if (this.isEditMode) {
                Text('X')
                  .fontSize(20)
                  .onClick(() => {
                    this.isEditMode = false;
                  })
                  .margin({ left: 20, right: 20 })
              } else {
                // The value of app.string.TodoItem in resource file is 'Todo'
                Text($r('app.string.TodoItem'))
                  .fontSize(36)
                  .margin({ left: 40 })
                Blank()
                Text('+')// Provide an entry for adding new list items, that is, add a click event to the add button
                  .fontSize(36)
                  .margin({ right: 20 })
                  .onClick(() => {
                    this.getUIContext().showTextPickerDialog({
                      range: this.availableThings,
                      onAccept: (value: TextPickerResult) => {
                        if (Array.isArray(value.index)) {
                          let indices: int[] = value.index as int[];
                          for (let i = 0; i < indices.length; i++) {
                            this.toDoData.push(new ToDo(this.availableThings[indices[i]]));
                          }
                        } else {
                          let index: int = value.index as int;
                          this.toDoData.push(new ToDo(this.availableThings[index]));
                        }
                        // Add new list item data toDoData (optional items)
                      },
                    } as TextPickerDialogOptions)
                  })
              }
            }
            .width('100%')
            .backgroundColor('#FFF1F3F5')
            .borderRadius(12)
            .height(45)

            List({ space: 10 } as ListOptions) {
              ForEach(this.toDoData, (toDoItem: ToDo) => {
                ListItem() {
                  // Put each data of toDoData into ListItem in the form of model
                  ToDoListItem({
                    isEditMode: this.isEditMode,
                    toDoItem: toDoItem,
                    selectedItems: this.selectedItems
                  })
                }
              }, (toDoItem: ToDo) => toDoItem.name.toString())
            }
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
      .backgroundColor('#f1f2f3')
    }
    // Please replace $r('app.string.AddListItem_title') with the actual resource file.
    // In this example, the value of this resource file is "Add List Item"
    .title($r('app.string.AddListItem_title'))
  }
}
