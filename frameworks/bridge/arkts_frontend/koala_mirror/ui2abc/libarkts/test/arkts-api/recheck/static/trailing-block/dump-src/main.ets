
function main() {}



class C {
  public f(arg: (()=> void)): void {}
  
  public g(): void {
    (this).f((() => {
      const x = ((6) + (5));
    }));
  }
  
  public constructor() {}
  
}

