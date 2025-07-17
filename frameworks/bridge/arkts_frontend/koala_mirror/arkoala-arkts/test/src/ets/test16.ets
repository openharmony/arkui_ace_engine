@Observed
class Info16 {
  count: number;

  constructor(count: number) {
    this.count = count;
  }
}

@Component
struct Child16 {
  @ObjectLink num: Info16;

  build() {
    Column() {
      Text(`num的值: ${this.num.count}`)
        .onClick(() => {
          // 正确写法，可以更改@ObjectLink装饰变量的成员属性
          this.num.count += 20;  // modify count can sync back its parent
        })
    }
  }
}

@Entry
@Component
struct Parent16 {
  @State num: Info16 = new Info16(10);

  build() {
    Column() {
      Text(`count的值: ${this.num.count}`)
      Button('click')
        .onClick(() => {
          // 可以在父组件做整体替换
          this.num = new Info16(30);  // modify ObjectLink object, can sync to its child
        })
      Child16({num: this.num})
    }
  }
}
