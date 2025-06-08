/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

// @State

@Component
struct StateToState {
  @State state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToProp {
  @State state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToProvide {
  @State state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToStorageLink {
  @State state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToLocalStorageLink {
  @State state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToStorageProp {
  @State state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToLocalStorageProp {
  @State state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StateToPlain {
  @State state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @Prop

@Component
struct PropToState {
  @Prop state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToProp {
  @Prop state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToProvide {
  @Prop state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToStorageLink {
  @Prop state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToLocalStorageLink {
  @Prop state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToStorageProp {
  @Prop state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToLocalStorageProp {
  @Prop state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PropToPlain {
  @Prop state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @Provide

@Component
struct ProvideToState {
  @Provide state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToProp {
  @Provide state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToProvide {
  @Provide state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToStorageLink {
  @Provide state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToLocalStorageLink {
  @Provide state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToStorageProp {
  @Provide state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToLocalStorageProp {
  @Provide state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct ProvideToPlain {
  @Provide state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @StorageLink

@Component
struct StorageLinkToState {
  @StorageLink("key") state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToProp {
  @StorageLink("key") state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToProvide {
  @StorageLink("key") state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToStorageLink {
  @StorageLink("key") state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToLocalStorageLink {
  @StorageLink("key") state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToStorageProp {
  @StorageLink("key") state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToLocalStorageProp {
  @StorageLink("key") state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StorageLinkToPlain {
  @StorageLink("key") state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @LocalStorageLink

@Component
struct LocalStorageLinkToState {
  @LocalStorageLink("key") state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToProp {
  @LocalStorageLink("key") state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToProvide {
  @LocalStorageLink("key") state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToStorageLink {
  @LocalStorageLink("key") state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToLocalStorageLink {
  @LocalStorageLink("key") state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToStorageProp {
  @LocalStorageLink("key") state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToLocalStorageProp {
  @LocalStorageLink("key") state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStorageLinkToPlain {
  @LocalStorageLink("key") state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @StorageProp

@Component
struct StoragePropToState {
  @StorageProp("key") state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToProp {
  @StorageProp("key") state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToProvide {
  @StorageProp("key") state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToStorageLink {
  @StorageProp("key") state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToLocalStorageLink {
  @StorageProp("key") state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToStorageProp {
  @StorageProp("key") state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToLocalStorageProp {
  @StorageProp("key") state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct StoragePropToPlain {
  @StorageProp("key") state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @LocalStorageProp

@Component
struct LocalStoragePropToState {
  @LocalStorageProp("key") state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToProp {
  @LocalStorageProp("key") state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToProvide {
  @LocalStorageProp("key") state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToStorageLink {
  @LocalStorageProp("key") state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToLocalStorageLink {
  @LocalStorageProp("key") state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToStorageProp {
  @LocalStorageProp("key") state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToLocalStorageProp {
  @LocalStorageProp("key") state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct LocalStoragePropToPlain {
  @LocalStorageProp("key") state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

// @BuilderParam

@Component
struct BuilderToBuilderParam {
  @Builder builder() {}
  @BuilderParam builderParam: () => void = this.builder
  @BuilderParam anotherParam: () => void = this.builder

  build() {
    this.builderParam()
    BuilderToBuilderParam({builderParam: this.anotherParam})
  }
}

@Component
struct BuilderParamToBuilderParam {
  @Builder builder() {}
  @BuilderParam builderParam: () => void = this.builder
  @BuilderParam anotherParam: () => void = this.builderParam

  build() {
    this.anotherBuilderParam()
    BuilderToBuilderParam({anotherParam: this.anotherParam})
  }
}

// plain property

@Component
struct PlainToState {
  state: string = 'Hello World'
  @State test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToProp {
  state: string = 'Hello World'
  @Prop test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToProvide {
  state: string = 'Hello World'
  @Provide test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToStorageLink {
  state: string = 'Hello World'
  @StorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToLocalStorageLink {
  state: string = 'Hello World'
  @LocalStorageLink("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToStorageProp {
  state: string = 'Hello World'
  @StorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToLocalStorageProp {
  state: string = 'Hello World'
  @LocalStorageProp("test") test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}

@Component
struct PlainToPlain {
  state: string = 'Hello World'
  test: string = this.state + "!"

  build() {
    Text(this.test)
  }
}
