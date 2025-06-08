let NextID: number = 1;

@Observed
class Bag {
  public id: number;
  public size: number;

  constructor(size: number) {
    this.id = NextID++;
    this.size = size;
  }
}

@Observed
class User {
  public bag: Bag;

  constructor(bag: Bag) {
    this.bag = bag;
  }
}

@Observed
class Book {
  public bookName: BookName;

  constructor(bookName: BookName) {
    this.bookName = bookName;
  }
}

@Observed
class BookName extends Bag {
  public nameSize: number;

  constructor(nameSize: number) {
    // 调用父类方法对nameSize进行处理
    super(nameSize);
    this.nameSize = nameSize;
  }
}

@Component
struct Son17 {
  label: string = 'Son17';
  @ObjectLink bag: Bag;

  build() {
    Column() {
      Text(`Son17 [${this.label}] this.bag.size = ${this.bag.size}`)
        .fontColor('#ffffffff')
        .backgroundColor('#ff3d9dba')
        .width(320)
        .height(50)
        .borderRadius(25)
        .margin(10)
        .textAlign(TextAlign.Center)
      Button(`Son17: this.bag.size add 1`)
        .width(320)
        .backgroundColor('#ff17a98d')
        .margin(10)
        .onClick(() => {
          this.bag.size += 1;
        })
    }
  }
}

@Component
struct Father17 {
  label: string = 'Father17';
  @ObjectLink bookName: BookName;

  build() {
    Row() {
      Column() {
        Text(`Father17 [${this.label}] this.bookName.size = ${this.bookName.size}`)
          .fontColor('#ffffffff')
          .backgroundColor('#ff3d9dba')
          .width(320)
          .height(50)
          .borderRadius(25)
          .margin(10)
          .textAlign(TextAlign.Center)
        Button(`Father17: this.bookName.size add 1`)
          .width(320)
          .backgroundColor('#ff17a98d')
          .margin(10)
          .onClick(() => {
            this.bookName.size += 1;
            console.log('this.bookName.size:' + this.bookName.size);
          })
      }
      .width(320)
    }
  }
}

@Entry
@Component
struct GrandFather17 {
  @State user: User = new User(new Bag(0));
  @State child: Book = new Book(new BookName(0));

  build() {
    Column() {
      Son17({ label: 'Son17 #1', bag: this.user.bag })
        .width(320)
      Father17({ label: 'Father17 #3', bookName: this.child.bookName })
        .width(320)
      Button(`GrandFather17: this.child.bookName.size add 10`)
        .width(320)
        .backgroundColor('#ff17a98d')
        .margin(10)
        .onClick(() => {
          this.child.bookName.size += 10;
          console.log('this.child.bookName.size:' + this.child.bookName.size);
        })
    }
  }
}


