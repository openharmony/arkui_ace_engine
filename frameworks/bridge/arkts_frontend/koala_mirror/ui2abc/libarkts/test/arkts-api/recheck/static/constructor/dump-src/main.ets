
function main() {}



class XXX {
  constructor(x: (()=> void)) {
    (this)(x, undefined);
  }
  
  public constructor(x: (()=> void), y: (()=> void) | undefined) {}
  
}

