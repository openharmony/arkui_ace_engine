class Info13 {
  info: string = 'Hello';
}

@Component
struct Child13 {
  @Link test: Info13;
  build() {
    Text(this.test.info)
  }
}

@Entry
@Component
struct LinkExample {
  @State info: Info13 = new Info13();
  build() {
    Column() {
      Child13({ test: this.info }) // also support this spec
      Child13({ test: $info })  // support $
    }
  }
}
