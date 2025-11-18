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

class MyModifier implements AttributeModifier<RichEditorAttribute> {
  enableSelectedDataDetector: boolean = false
  enableUrl: boolean = false;
  enablePhone: boolean = false;
  enableAddress: boolean = false;
  enableEmail: boolean = false;
  enableDate: boolean = false;
  config: SelectDataDetectorConfig | undefined = { types: [] }

  public getTypes() {
    let types: TextDataDetectorType[] = []
    if (this.enableUrl) {
      types.push(TextDataDetectorType.URL)
    }
    if (this.enablePhone) {
      types.push(TextDataDetectorType.PHONE_NUMBER)
    }
    if (this.enableAddress) {
      types.push(TextDataDetectorType.ADDRESS)
    }
    if (this.enableEmail) {
      types.push(TextDataDetectorType.EMAIL)
    }
    if (this.enableDate) {
      types.push(TextDataDetectorType.DATE_TIME)
    }
    return types
  }

  public updateConfig() {
    this.config = { types: this.getTypes() }
  }

  applyNormalAttribute(instance: RichEditorAttribute): void {
    instance
      .enableSelectedDataDetector(this.enableSelectedDataDetector)
      .selectedDataDetectorConfig(this.config)
  }
}

class Pair<T, U> {
  public name: T;
  public value: U;

  constructor(name: T, value: U) {
    this.name = name;
    this.value = value;
  }

  toString(): string {
    return `Pair(${this.name}, ${this.value})`;
  }
}

@Entry
@Component
struct WindowParams {
  public getTypes() {
    let types: TextDataDetectorType[] = []
    if (this.enableUrl) {
      types.push(TextDataDetectorType.URL)
    }
    if (this.enablePhone) {
      types.push(TextDataDetectorType.PHONE_NUMBER)
    }
    if (this.enableAddress) {
      types.push(TextDataDetectorType.ADDRESS)
    }
    if (this.enableEmail) {
      types.push(TextDataDetectorType.EMAIL)
    }
    if (this.enableDate) {
      types.push(TextDataDetectorType.DATE_TIME)
    }
    return types
  }

  public updateConfig() {
    this.config = { types: this.getTypes() }
  }

  @State private enableSelectedDataDetector: boolean | undefined | null = true;
  @State private enableDataDetector: boolean = false;
  enableUrl: boolean = false;
  enablePhone: boolean = false;
  enableAddress: boolean = false;
  enableEmail: boolean = false;
  enableDate: boolean = false;
  controller: RichEditorController = new RichEditorController()
  @State config: SelectDataDetectorConfig | undefined = { types: [] }
  testStr: string = '网址：www.example.com，电话：13000000000，地址：北京天安门，邮箱：123456789@example.com，转测：2025年10月15日'
  idsToFilter: TextMenuItemId[] = [
    TextMenuItemId.TRANSLATE,
    TextMenuItemId.SHARE,
    TextMenuItemId.SEARCH,
    TextMenuItemId.AI_WRITER
  ]
  onCreateMenu = (menuItems: Array<TextMenuItem>) => {
    const idsToFilter: TextMenuItemId[] = [
      TextMenuItemId.url,
      TextMenuItemId.email,
      TextMenuItemId.phoneNumber,
      TextMenuItemId.address,
      TextMenuItemId.dateTime,
      TextMenuItemId.askAI,
      TextMenuItemId.SELECT_ALL
    ]
    const items = menuItems.filter(item => idsToFilter.some(id => id.equals(item.id)))
    return items;
  }
  onMenuItemClick = (menuItem: TextMenuItem, textRange: TextRange) => {
    return false;
  }
  copyOptionText: string = 'CopyOptions.LocalDevice'
  @State editMenuOptions: EditMenuOptions = {
    onCreateMenu: this.onCreateMenu,
    onMenuItemClick: this.onMenuItemClick,
  };
  @State copyOption: CopyOptions | undefined | null = CopyOptions.LocalDevice
  copyOptionList: CopyOptions[] =
    [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  copyOptionStrList: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State modifier: MyModifier = new MyModifier()
  @State enableModifier: boolean = false;
  copyOptions: Pair<string, CopyOptions | undefined | null>[] = [
    new Pair('None', CopyOptions.None),
    new Pair('InApp', CopyOptions.InApp),
    new Pair('Local', CopyOptions.LocalDevice),
    new Pair('Cross', CopyOptions.CROSS_DEVICE),
    new Pair('undef', undefined),
    new Pair('null', null),
  ]
  enableSelectedDataDetectorOptions: Pair<string, boolean | undefined | null>[] = [
    new Pair('true', true),
    new Pair('false', false),
    new Pair('undef', undefined),
    new Pair('null', null),
  ]
  selectedDataConfigStateOptions: Pair<string, (value: boolean) => void>[] = [
    new Pair('Url', (value: boolean) => {
      this.enableUrl = value
    }),
    new Pair('Email', (value: boolean) => {
      this.enableEmail = value
    }),
    new Pair('Phone', (value: boolean) => {
      this.enablePhone = value
    }),
    new Pair('Address', (value: boolean) => {
      this.enableUrl = value
    }),
    new Pair('Date', (value: boolean) => {
      this.enableUrl = value
    }),
  ]
  selectedDataConfigModifierOptions: Pair<string, (value: boolean) => void>[] = [
    new Pair('Url', (value: boolean) => {
      this.modifier.enableUrl = value
    }),
    new Pair('Email', (value: boolean) => {
      this.modifier.enableEmail = value
    }),
    new Pair('Phone', (value: boolean) => {
      this.modifier.enablePhone = value
    }),
    new Pair('Address', (value: boolean) => {
      this.modifier.enableUrl = value
    }),
    new Pair('Date', (value: boolean) => {
      this.modifier.enableUrl = value
    }),
  ]

  build() {
    Column() {
      Row() {
        Text('copyOption').fontSize(12)
        ForEach(this.copyOptions, (option: Pair<string, CopyOptions | undefined | null>) => {
          Column() {
            Text(option.name)
            Radio({ value: option.name, group: 'copyOptionGroup', indicatorType: RadioIndicatorType.DOT })
              .checked(this.copyOption === option.value)
              .onChange((isChecked: boolean) => {
                if (isChecked) {
                  this.copyOption = option.value
                }
              })
          }.margin({ left: 5, right: 5 })
        })
      }

      Row() {
        Column() { // state变量
          Text('State变量切换')
          Row() {
            Column() {
              Text('开关')
              ForEach(this.enableSelectedDataDetectorOptions, (option: Pair<string, boolean | undefined | null>) => {
                Row() {
                  Radio({
                    value: option.name,
                    group: 'enableState',
                    indicatorType: RadioIndicatorType.DOT
                  })
                    .checked(this.enableSelectedDataDetector === option.value)
                    .onChange((value: boolean) => {
                      if (value) {
                        this.enableSelectedDataDetector = value
                      }
                    })
                  Text(option.name)
                }
              })
            }.alignItems(HorizontalAlign.Start)

            Column() {
              Text('选项')
              ForEach(this.selectedDataConfigStateOptions, (option: Pair<string, (value: boolean) => void>) => {
                Row() {
                  Checkbox({ name: option.name, group: 'selectedDataConfigOptions' })
                    .select(false)
                    .selectedColor(0x39a2db)
                    .shape(CheckBoxShape.ROUNDED_SQUARE)
                    .onChange((value: boolean) => {
                      option.value(value)
                      this.updateConfig()
                    })
                  Text(option.name)
                }
              })
            }.alignItems(HorizontalAlign.Start)
          }.alignItems(VerticalAlign.Top)
        }

        Column() { // modifier
          Text('Modifier切换')
          Row() {
            Column() {
              Text('开关')
              ForEach(this.enableSelectedDataDetectorOptions, (option: Pair<string, boolean | undefined | null>) => {
                Row() {
                  Radio({
                    value: option.name,
                    group: 'enableModifier',
                    indicatorType: RadioIndicatorType.DOT
                  })
                    .checked(this.modifier.enableSelectedDataDetector === option.value)
                    .onChange((value: boolean) => {
                      if (value) {
                        this.modifier.enableSelectedDataDetector = value
                      }
                    })
                  Text(option.name)
                }
              })
            }.alignItems(HorizontalAlign.Start)

            Column() {
              Text('选项')
              ForEach(this.selectedDataConfigModifierOptions, (option: Pair<string, (value: boolean) => void>) => {
                Row() {
                  Checkbox({ name: option.name, group: 'selectedDataConfigOptions' })
                    .select(false)
                    .selectedColor(0x39a2db)
                    .shape(CheckBoxShape.ROUNDED_SQUARE)
                    .onChange((value: boolean) => {
                      option.value(value)
                      this.updateConfig()
                    })
                  Text(option.name)
                }
              })
            }.alignItems(HorizontalAlign.Start)
          }.alignItems(VerticalAlign.Top)
        }
      }

      Column() {
        List() {
          ListItem() {
            Row() {
              Text(this.testStr)
                .padding(10)
                .fontSize(20)
                .copyOption(this.copyOption)
                .enableSelectedDataDetector(undefined)
                .enableDataDetector(this.enableDataDetector)
                .selectedDataDetectorConfig(this.config)
                .editMenuOptions(this.editMenuOptions)
                .border({ width: 1, color: Color.Black })
            }
          }

          ListItem() {
            Row() {
            }.height(10)
          }

          ListItem() {
            Row() {
              RichEditor({ controller: this.controller })
                .customKeyboard()
                .attributeModifier(this.modifier)
                .copyOptions(this.copyOption)
                .enableSelectedDataDetector(this.enableSelectedDataDetector)
                .selectedDataDetectorConfig(this.config)
                .enableDataDetector(this.enableDataDetector)
                .border({ width: 1, color: Color.Black })
                .editMenuOptions(this.editMenuOptions)
                .onReady(() => {
                  this.controller.addTextSpan('\n\n' + this.testStr + '\n\n\n\n',
                    { style: { fontSize: 20 } })
                })
                .customKeyboard()
                .height(200)
                .margin(10)
            }
          }

          ListItem() {
            Row() {
              TextArea({
                text: this.testStr + '\n\n\n\n',
              })
                .copyOption(this.copyOption)
                .enableSelectedDataDetector(this.enableSelectedDataDetector)
                .selectedDataDetectorConfig(this.config)
                .border({ width: 1, color: Color.Black })
                .height(150)
                .margin(10)
            }
          }

          ListItem() {
            Row() {
              TextInput({ text: this.testStr })
            }
          }

          ListItem() {
            Row() {
            }.height(500)
          }

        }
      }
    }
  }
}