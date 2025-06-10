@Component
struct GrandSon15 {
  // @Consume装饰的变量通过相同的属性名绑定其祖先内的@Provide装饰的变量
  @Consume("reviewVotes") reviewVotes: number;

  build() {
    Column() {
      Text(`reviewVotes(${this.reviewVotes})`) // Text显示10
      Button(`reviewVotes(${this.reviewVotes}), give +1`)
        .onClick(() => this.reviewVotes += 1)
    }
    .width('50%')
  }
}

@Component
struct Child15 {
  // @Provide({ allowOverride: "reviewVotes" }) reviewVotes: number = 10;
  @Provide("reviewVotes") reviewVotes: number = 10;

  build() {
    Row({ space: 5 }) {
      GrandSon15()
    }
  }
}

@Component
struct Parent15 {
  // @Provide({ allowOverride: "reviewVotes" }) reviewVotes: number = 20;
  @Provide("reviewVotes") reviewVotes: number = 20;

  build() {
    Child15()
  }
}

@Entry
@Component
struct GrandParent15 {
  @Provide("reviewVotes") reviewVotes: number = 40;

  build() {
    Column() {
      Button(`reviewVotes(${this.reviewVotes}), give +1`)
        .onClick(() => this.reviewVotes += 1)
      Parent15()
    }
  }
}
