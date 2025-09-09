
function main(): void {}



class C {
  public f(arg: (()=> void)): void {}
  
  public g(): void {
    this.f((() => {
      const x = 11;
    }));
  }
  
  public constructor() {}
  
}

