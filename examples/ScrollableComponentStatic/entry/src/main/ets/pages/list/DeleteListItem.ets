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

import common from '@ohos.app.ability.common';
import util from '@ohos.util';
import { State, Link, Watch } from '@ohos.arkui.stateManagement';
import { PropRef, $r } from '@kit.ArkUI';
import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  Row,
  Text,
  Blank,
  Button,
  Flex,
  Checkbox,
  ForEach,
  NavDestination,
  GestureGroup,
  LongPressGesture,
  HorizontalAlign,
  FlexAlign,
  ItemAlign,
  GestureMode,
  Length,
  TextPickerResult,
  TextPickerDialogOptions,
  Color
} from '@kit.ArkUI';
import { ListOptions } from '@kit.ArkUI';

// Structure reference
export class ToDo {
  public key: string = util.generateRandomUUID(true);
  public name: string;
  public toDoData: ToDo[] = [];

  constructor(name: string) {
    this.name = name;
  }
}

@Component
export struct ToDoListItem {
  @Link isEditMode: boolean;
  @Link selectedItems: ToDo[];
  private toDoItem: ToDo = new ToDo('');

  build(): void {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
      Text(this.toDoItem.name)
        .fontSize(16)
        .width('80%')
        .margin({ left: 20 })
      if (this.isEditMode) {
        Checkbox()
          .onChange((isSelected) => {
            if (isSelected) {
              this.selectedItems.push(new ToDo(this.toDoItem.name));
              // this.selectedItems records the selected list items when checked, which can be constructed
              // according to the actual scenario
            } else {
              let index = this.selectedItems.indexOf(new ToDo(this.toDoItem.name));
              if (index !== -1) {
                this.selectedItems.splice(index, 1); // When unchecked, remove this item from selectedItems
              }
            }
          })
      }
    }
    .backgroundColor('#FFF1F3F5')
    .width('100%')
    .height(40)
    .borderRadius(12)
    .gesture(
      GestureGroup(GestureMode.Exclusive,
        LongPressGesture()
          .onAction(() => {
            if (!this.isEditMode) {
              this.isEditMode = true; // Enter edit mode
            }
          })
      )
    )
  }
}

@Entry
@Component
export struct DeleteListItem {
  @State arr: int[] = [0, 1, 2, 3];
  @State toDoData: ToDo[] = [] as ToDo[];
  @State @Watch('onEditModeChange') isEditMode: boolean = false;
  @State selectedItems: ToDo[] = [] as ToDo[]
  private availableThings: string [] = [];

  public deleteToDoData(): void {
    this.toDoData = [];
  }

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
    if (!this.isEditMode) {
      this.selectedItems = [];
    }
  }

  build(): void {
    NavDestination() {
      Column() {
        Column() {
          // Please replace $r('app.string.DeleteListItem_titleExample') with the actual resource file.
          // In this example, the value of this resource file is "Delete List Item Example"
          Text($r('app.string.DeleteListItem_titleExample'))
            .fontSize(14)
            .fontColor('#666')
          Column() {
            Row() {
              if (this.isEditMode) {
                Text('X')
                  .fontSize(20)
                  .onClick(() => {
                    this.isEditMode = false;
                  })
                  .margin({ left: 20, right: 20 })
              } else {
                // Please replace $r('app.string.TodoItem') with the actual resource file.
                // In this example, the value of this resource file is "Todo"
                Text($r('app.string.TodoItem'))
                  .fontSize(30)
                  .margin({ left: 20 })
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
            List(
              { space: 12 } as ListOptions
            ) {
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
            }.cachedCount(3)
          }
        }
        .alignItems(HorizontalAlign.Start)
        .backgroundColor('#fff')
        .borderRadius(12)
        .padding(12)
        .width('100%')

        if (this.isEditMode) {
          Column() {
            // The value of app.string.delete in resource file is 'Delete'
            Button($r('app.string.delete'))
              .width('90%')
              .backgroundColor(Color.Red)
              .onClick(() => {
                // this.toDoData is the list item of todos, which can be constructed according to the actual scenario.
                // After clicking, delete the toDoData data corresponding to the selected list items
                this.toDoData = this.toDoData.filter(toDoItem =>
                !this.selectedItems.some(selectedItem => selectedItem.name === toDoItem.name));
                this.isEditMode = false;
              })
          }
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Please replace $r('app.string.DeleteListItem_title') with the actual resource file.
    // In this example, the value of this resource file is "Delete List Item"
    .title($r('app.string.DeleteListItem_title'))
  }
}
