
function main(): void {}


function foo(): void {
  HasInstantiate.$_instantiate((() => {
    return new HasInstantiate();
  }), "foo");
}

function hasTrailing(first?: string, trailing?: (()=> void)): void {
  ({let gensym%%_994 = trailing;
  (((gensym%%_994) == (null)) ? undefined : gensym%%_994())});
}

function bar(zzz: string): void {
  hasTrailing("xxx");
  hasTrailing("xxx", (() => {
    const d = zzz;
  }));
}


class HasInstantiate {
  public static $_instantiate(factory: (()=> HasInstantiate), arg: string): void {}
  
  public constructor() {}
  
}

