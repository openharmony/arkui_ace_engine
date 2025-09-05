
function main(): void {}



class XXX {
  constructor(x: (()=> void)) {
    this(x, undefined);
  }
  
  public constructor(x: (()=> void), y: (()=> void) | undefined) {}
  
}

