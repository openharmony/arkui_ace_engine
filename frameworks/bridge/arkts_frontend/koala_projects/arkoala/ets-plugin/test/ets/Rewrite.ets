/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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


// Bare empty struct

@Entry
@Component
export struct EntryExample {
    build(){ }
}

@Component
struct ComponentExample {
    build(){ }
}


// A builder call in the build() function

@Component
struct BuildExample {
    build(){
        Text("message")
            .fontColor(Color.Red)
            .width(100)
    }
}

// Simple state management annotations

@Component
struct StateExample {
    @State x: string = "hello"
    build(){
        Text(this.x)
    }
}

@Component
struct LinkExample {
    @Link x: string
    build(){
        Text(this.x)
    }
}

@Component
struct PropExample {
    @Prop x: string
    build(){
        Text(this.x)
    }
}

@Component
struct PropInitializedExample {
    @Prop x: string = "init"
    build(){
        Text(this.x)
    }
}

@Component
struct ProvideExample {
    @Provide("name") x: string = "text"

    build(){
        Text(this.x)
    }
}

@Component
struct ConsumeExample {
    @Consume("name") x: string
    build(){
        Text(this.x)
    }
}

// Builder functions

@Component
struct BuilderExample {
    @Builder foo() {
        Text("hello")
    }
    build() {
        this.foo()
    }
}

@Builder
function bar() {
    Text("hello")
}

@Component
struct GlobalBuilderExample {
    build() {
        bar()
    }
}

@Component
struct BuilderParamExample {
    @BuilderParam foo: () => {}
    build() {
        this.foo()
    }
}

// @Styles @Extend @AnimatableExtend

@Styles
function looks() {
    .height(500)
    .width(400)
    .backgroundColor(Color.Gray)
}

@Component
struct StylesExample {
    build() {
        Text()
            .width(17)
            .looks()
    }
}

@Component
struct StylesMethodExample {
    @Styles
    nice() {
        .height(500)
        .width(400)
        .backgroundColor(Color.Gray)
    }

    build() {
        Text()
            .width(17)
            .nice()
    }
}


@Extend(Column)
function clown() {
    .height(500)
    .width(400)
    .backgroundColor(Color.Gray)
}

@Component
struct ExtendExample {
    build() {
        Column()
            .width(17)
            .clown()
    }
}

@AnimatableExtend(Text)
function attributeExtend(n: number, unused: string) {
  .fontSize(n)
}

@Component
struct AnimatableExtendExample {
    build() {
        Text()
            .width(17)
            .attributeExtend(50, "unused")
    }
}


// Advanced state management

@Component
struct WatchExample {
    @State @Watch("watchFunction") x: string = "hello"
    watchFunction() {
        console.log("Watch function")
    }
    build() {
    }
}

@Component
struct StorageLinkExample {
    @StorageLink("storage") link: string = "Start"
    build() {
    }
}

@Component
struct StoragePropExample {
    @StorageProp("storage") prop: string = "Start"
    build() {
    }
}

// CustomDialog

@CustomDialog
struct CustomDialogExample {
  controller: CustomDialogController
  build() {
  }
}

@Component
export struct CustomDialogControllerExample {
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomDialogExample(),
    autoCancel: true,
    alignment: DialogAlignment.Default,
    offset: { dx: 0, dy: 0 },
    gridCount: 4,
    customStyle: false
  })

  aboutToAppear() {
    this.dialogController.open()
  }

  aboutToDisappear() {
      this.dialogController.close()
  }

  build() {
  }
}

// ObjectLink and Observed

@Observed
class ObservedExample {
  public c: number
  constructor(c: number) {
    this.c = c
  }
}

@Component
struct ObjectLinkExample {
  @ObjectLink a: ObservedExample

  build() {
    Button()
      .onClick(() => {
          this.a.c += 1
    })
  }
}

@Component
struct ObjectLinkExampleParent {
  @State a: ObservedExample[] = [new ObservedExample(0), new ObservedExample(0)]

  build() {
    ObjectLinkExample()
  }
}

@Component
struct PlainPropertyExample {
    field: number = 17
}

@Component
struct CallExample {
    @State
    state: number = 17
    build() {
        Child({counter: this.$state})
    }
}

@Component
struct Child {
    @Link
    counter: number
    build() {}
}

@Component
struct BuilderPropagationExample {
    build() {
        ChildWithBuilder().width(100)
    }
}

@Component
struct ChildWithBuilder {
    build() {
        Column() {}
    }
}

@Component
struct StaticField {
    static x: number = 17
    build() {}
}

